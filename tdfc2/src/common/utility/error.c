/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#include <tdf/bitstream.h>
#include <tdf/capsule.h>

#include <utility/config.h>
#include <utility/version.h>
#include "c_types.h"
#include <utility/option.h>

#include <parse/preproc.h>

#include <utility/ustring.h>
#include <utility/version.h>
#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/option.h>
#include <utility/buffer.h>
#include <utility/print.h>
#include <utility/xalloc.h>

#include <parse/file.h>
#include <parse/lex.h>
#include <parse/literal.h>
#include <parse/preproc.h>

#include <construct/basetype.h>
#include <construct/statement.h>

#include <output/tdf.h>
#include <output/capsule.h>
#include <output/dump.h>

#include <spec/save.h>

#include "err_ext.h"
#include "exp_ops.h"
#include "loc_ext.h"


/*
    This routine prints the program name and version number plus the
    versions of C++ and the TDF specification it supports to the print
    buffer, returning the result.
*/

string
tdfc2_report_version(int vers)
{
	BUFFER *bf = clear_buffer(&print_buff, NIL(FILE));
	bfprintf(bf, "%x: Version %x", progname, progvers);
	if (vers) {
		char buff[20];
		char *v = LANGUAGE_VERSION;
		sprintf_v(buff, "%.4s-%.2s", v, v + 4);
		bfprintf(bf, " (%x %x", LANGUAGE_NAME, buff);
		bfprintf(bf, " to TDF %d.%d", TDF_major, TDF_minor);
#ifdef RELEASE
		bfprintf(bf, ", Release %x", RELEASE);
#endif
		bfprintf(bf, ")");
	}
	return bf->start;
}


/*
    This structure gives the current file position.  This consists of a
    string, giving the file name, an integer, giving the line number, and
    a pointer to any previous positions from which this is derived by a
    #include directive.
*/

LOCATION crt_loc = NULL_loc;
LOCATION builtin_loc = NULL_loc;


/*
    These variables are used by the error reporting routines.  exit_status
    gives the overall status of the program - it is EXIT_SUCCESS if no
    serious errors have occurred, and EXIT_FAILURE otherwise.  A count of
    the number of serious errors is kept in number_errors, up to a maximum
    of max_errors.
*/

FILE *error_file = NULL;
unsigned long number_warnings = 0;
unsigned long max_errors = 32;
int no_error_args = 0;
int verbose = 0;
static int print_short = 0;
static int print_error_loc = 0;
static int print_error_name = 0;
static int print_error_source = 0;
static int print_iso_ref = 1;
static int print_ansi_ref = 0;


/*
    This routine processes the error formatting options given by opt.
    This corresponds to the command-line option '-mopt'.
*/

void
error_option(string opt)
{
	int out = 1;
	character c;
	while (c = *(opt++), c != 0) {
		switch (c) {
		case 'a': print_ansi_ref     = out; break;
		case 'c': print_error_source = out; break;
		case 'e': print_error_name   = out; break;
		case 'g': record_location    = out; break;
		case 'k': output_spec        = out; break;
		case 'l': print_error_loc    = out; break;
		case 'm': allow_multibyte    = out; break;
		case 'p': preproc_space      = out; break;
		case 'q': print_short        = out; break;
		case 'r': allow_dos_newline  = out; break;
		case 's': print_iso_ref      = out; break;
		case 't': print_type_alias   = out; break;
		case 'x': print_c_style      = out; break;

		case '+': out = 1; break;
		case '-': out = 0; break;

		case 'o': {
			error_file = (out ? stdout : stderr);
			break;
		}
		case 'w': {
			OPTION sev = OPTION_WARN;
			if (out) {
				sev = OPTION_OFF;
			}
			OPT_CATALOG[OPT_warning].def[0] = sev;
			OPT_CATALOG[OPT_warning].def[1] = sev;
			break;
		}
		case 'z': {
			OPTION sev = OPTION_ON;
			if (out) {
				sev = OPTION_WARN;
			}
			OPT_CATALOG[OPT_error].def[0] = sev;
			OPT_CATALOG[OPT_error].def[1] = sev;
			break;
		}
		default : {
			/* Unknown output options */
			const char *err =
			    "Unknown error formatting option, '%c'";
			error(ERR_WARN, err,(int)c);
			break;
		}
		}
	}
	return;
}


/*
    These macros are used to parameterise the form of the error messages.
*/

#define HEADER_FATAL		"Fatal error"
#define HEADER_SERIOUS		"Error"
#define HEADER_WARNING		"Warning"
#define HEADER_INTERNAL		"Internal error"
#define HEADER_ASSERT		"Assertion"

#define PRINT_HEADER(M, L, F)\
	print_location((L), (F));\
	fputs_v(": ",(F));\
	fputs_v((M), (F));\
	fputs_v(":\n",(F))

#define PRINT_SOURCE(L, F)\
	print_source((L), 1, 0, "    ",(F))

#define PRINT_FROM(L, F)\
	fputs_v("    (included from ",(F));\
	print_location((L), (F));\
	fputs_v(")\n",(F))

#define PRINT_START(M, F)\
	fputs_v((M), (F));\
	fputs_v(": ",(F))

#define MESSAGE_START		"  "
#define MESSAGE_END		".\n"
#define MESSAGE_TERM		"\n"
#define MESSAGE_NAME		"[%x]: "
#define MESSAGE_ISO		"[C90 %x]: "
#define MESSAGE_ANSI		"[C89 "
#define MESSAGE_ANSI_END	"]: "
#define MESSAGE_PRAGMA		"[Pragma]: "
#define MESSAGE_PRINTF		"[Printf]: "
#define MESSAGE_SYNTAX		"[Syntax]: "
#define MESSAGE_TOKEN		"[Token]: "


/*
    The following forward declaration is necessary.
*/

static void print_error_msg(ERROR, LOCATION *, FILE *);


/*
    This routine is called to terminate the program.  It tidies up any
    output files and error messages and then exits.  fatal is true after
    a memory allocation error when the amount of tidying up which can
    be done is limited, although some memory is freed to give a little
    leeway.
*/

void
term_error(int fatal)
{
	if (fatal) {
		/* Cope with memory allocation errors */
		exit_status = EXIT_FAILURE;
		output_capsule = 0;
		output_spec = 0;
		free_buffer(&token_buff);
	}
	if (do_dump) {
		/* End dump file */
		term_dump();
		do_dump = 0;
	}
	if (do_error) {
		/* Report errors in dump file */
		unsigned long e = number_errors;
		unsigned long w = number_warnings;
		int sev = (e ? ERR_SERIOUS : ERR_WARN);
		do_error = 0;
		error(sev, "%lu error(s), %lu warning(s)", e, w);
	}
	if (output_name[OUTPUT_SPEC]) {
		/* Write spec file */
		begin_spec();
		end_spec();
	}
	if (output_tdf) {
		/* Write capsule */
		write_capsule();
	}
	exit(exit_status);
}


/*
    This routine is intended to aid in debugging.  It is called just after
    any error message is printed.
*/

static void
error_break(void)
{
	return;
}


/*
    This routine returns the error message header for an error of severity
    sev.  It also updates the internal flags.
*/

static const char *
error_header(int sev)
{
	const char *msg;
	switch (sev) {
	case ERR_FATAL: {
		msg = HEADER_FATAL;
		exit_status = EXIT_FAILURE;
		output_capsule = 0;
		number_errors++;
		break;
	}
	case ERR_INTERNAL: {
		msg = HEADER_INTERNAL;
		if (error_severity[OPTION_ON] == ERR_SERIOUS) {
			exit_status = EXIT_FAILURE;
			output_capsule = 0;
		}
		number_errors++;
		break;
	}
	default : {
		msg = HEADER_SERIOUS;
		if (error_severity[OPTION_ON] == ERR_SERIOUS) {
			exit_status = EXIT_FAILURE;
			output_capsule = 0;
		}
		number_errors++;
		break;
	}
	case ERR_WARN: {
		msg = HEADER_WARNING;
		number_warnings++;
		break;
	}
	}
	return msg;
}


/*
    This routine prints the location loc to the file f.
*/

static void
print_location(LOCATION *loc, FILE *f)
{
	BUFFER *bf = clear_buffer(&print_buff, f);
	IGNORE print_loc(loc, NIL(LOCATION), bf, 0);
	output_buffer(bf, 0);
	return;
}


/*
    The ISO C standard was based on the ANSI C standard but the sections
    were renumbered.  The ISO and ANSI C++ standards are identical.  This
    routine converts the ISO section number s to the corresponding ANSI
    section number, printing it to the buffer bf.
*/

static void
iso_to_ansi(BUFFER *bf, const char *s)
{
#if LANGUAGE_C
	char c;
	unsigned long n = 0;
	const char *p = "1.";
	const char *q = s;
	while (c = *q,(c >= '0' && c <= '9')) {
		n = 10 * n + (unsigned long)(c - '0');
		q++;
	}
	if (n == 0) {
		bfprintf(bf, "%x", s);
	} else {
		switch (n) {
		case 1: n = 2; break;
		case 2: n = 3; break;
		case 3: n = 6; break;
		case 4: n = 7; break;

		default:
			p = "";
			n -= 3;
			break;
		}
		bfprintf(bf, "%x%lu%x", p, n, q);
	}
#else
	bfprintf(bf, "%x", s);
#endif
	return;
}


/*
    This routine prints the start of an error message of severity sev and
    location loc to the file f.
*/

static void
print_error_start(FILE *f, LOCATION *loc, int sev)
{
	const char *msg = error_header(sev);
	if (loc) {
		PRINT_HEADER(msg, loc, f);
		if (print_error_loc) {
			/* Print full error location */
			LOCATION floc;
			LOCATION *ploc = loc;
			for (;;) {
				PTR(LOCATION)from;
				PTR(POSITION)posn = ploc->posn;
				if (IS_NULL_ptr(posn)) {
					break;
				}
				from = DEREF_ptr(posn_from(posn));
				if (IS_NULL_ptr(from)) {
					break;
				}
				DEREF_loc(from, floc);
				ploc = &floc;
				PRINT_FROM(ploc, f);
			}
		}
		if (print_error_source) {
			/* Print source line */
			PRINT_SOURCE(loc, f);
		}
	} else {
		PRINT_START(msg, f);
	}
	return;
}


/*
    This routine prints the end of an error message of severity sev to
    the file f.
*/

static void
print_error_end(FILE *f, int sev)
{
	unsigned long n = number_errors;
	if (n >= max_errors && sev != ERR_FATAL) {
		ERROR err = ERR_fail_too_many(n);
		print_error_msg(err, &crt_loc, f);
		sev = ERR_FATAL;
	}
	fputs_v(MESSAGE_TERM, f);
	error_break();
	if (sev == ERR_FATAL) {
		term_error(0);
	}
	return;
}


/*
    This table gives the mapping between options and error severity
    levels.
*/

int error_severity[] = {
	ERR_NONE,			/* OPTION_OFF */
	ERR_WARN,			/* OPTION_WARN */
	ERR_SERIOUS,			/* OPTION_ON */
	ERR_WHATEVER			/* OPTION_WHATEVER */
};

int default_severity[] = {
	ERR_NONE,			/* OPTION_OFF */
	ERR_WARN,			/* OPTION_WARN */
	ERR_SERIOUS,			/* OPTION_ON */
	ERR_WHATEVER			/* OPTION_WHATEVER */
};


/*
    This routine creates a structure for error n in the error catalogue.
    Any extra arguments needed by the error should also be given.  Because
    of restrictions imposed by the way that stdarg is implemented, any
    structure arguments need to be explicitly passed by reference.  Note
    that these arguments are stored in the result in reverse order.
*/

ERROR
make_error(int n, ...) /* VARARGS */
{
	int sev;
	ERROR e;
	OPTION opt;
	va_list args;
	ERR_DATA *msg;
	const char *s;
	va_start(args, n);

	/* Check severity level */
	msg = ERR_CATALOG + n;
	if (crt_opt) {
		opt = crt_opt[msg->usage];
	} else {
		/* Can have errors before crt_opt is initialised */
		opt = OPT_CATALOG[msg->usage].def[0];
	}
	sev = error_severity[opt];
	if (sev == ERR_NONE) {
		va_end(args);
		return NULL_err;
	}

	/* Read arguments */
	s = msg->signature;
	if (s == NULL) {
		MAKE_err_simple(sev, n, e);
	} else {
		unsigned i, m = (unsigned)strlen(s);
		if (no_error_args)m = 0;
		MAKE_err_simple_args(sev, n, m, e);
		for (i = 0; i < m; i++) {
			switch (s[i]) {
			case ERR_KEY_BASE_TYPE: {
				BASE_TYPE arg = va_arg(args, BASE_TYPE);
				COPY_btype(err_arg(e, i, BASE_TYPE), arg);
				break;
			}
			case ERR_KEY_CLASS_TYPE: {
				CLASS_TYPE arg = va_arg(args, CLASS_TYPE);
				COPY_ctype(err_arg(e, i, CLASS_TYPE), arg);
				break;
			}
			case ERR_KEY_CV_SPEC: {
				CV_SPEC arg = va_arg(args, CV_SPEC);
				COPY_cv(err_arg(e, i, CV_SPEC), arg);
				break;
			}
			case ERR_KEY_ACCESS:
			case ERR_KEY_DECL_SPEC: {
				DECL_SPEC arg = va_arg(args, DECL_SPEC);
				COPY_dspec(err_arg(e, i, DECL_SPEC), arg);
				break;
			}
			case ERR_KEY_FLOAT: {
				FLOAT arg = va_arg(args, FLOAT);
				COPY_flt(err_arg(e, i, FLOAT), arg);
				break;
			}
			case ERR_KEY_HASHID: {
				HASHID arg = va_arg(args, HASHID);
				COPY_hashid(err_arg(e, i, HASHID), arg);
				break;
			}
			case ERR_KEY_IDENTIFIER:
			case ERR_KEY_LONG_ID: {
				IDENTIFIER arg = va_arg(args, IDENTIFIER);
				COPY_id(err_arg(e, i, IDENTIFIER), arg);
				break;
			}
			case ERR_KEY_LEX: {
				LEX arg = va_arg(args, LEX);
				COPY_int(err_arg(e, i, LEX), arg);
				break;
			}
			case ERR_KEY_NAMESPACE: {
				NAMESPACE arg = va_arg(args, NAMESPACE);
				COPY_nspace(err_arg(e, i, NAMESPACE), arg);
				break;
			}
			case ERR_KEY_NAT: {
				NAT arg = va_arg(args, NAT);
				COPY_nat(err_arg(e, i, NAT), arg);
				break;
			}
			case ERR_KEY_PPTOKEN_P: {
				PPTOKEN_P arg = va_arg(args, PPTOKEN_P);
				COPY_pptok(err_arg(e, i, PPTOKEN_P), arg);
				break;
			}
			case ERR_KEY_PTR_LOC: {
				PTR_LOC arg = va_arg(args, PTR_LOC);
				COPY_ptr(err_arg(e, i, PTR_LOC), arg);
				break;
			}
			case ERR_KEY_QUALIFIER: {
				QUALIFIER arg = va_arg(args, QUALIFIER);
				COPY_qual(err_arg(e, i, QUALIFIER), arg);
				break;
			}
			case ERR_KEY_STRING: {
				STRING arg = va_arg(args, STRING);
				COPY_str(err_arg(e, i, STRING), arg);
				break;
			}
			case ERR_KEY_TYPE: {
				TYPE arg = va_arg(args, TYPE);
				COPY_type(err_arg(e, i, TYPE), arg);
				break;
			}
			case ERR_KEY_cint: {
				cint arg = va_arg(args, cint);
				COPY_int(err_arg(e, i, cint), arg);
				break;
			}
			case ERR_KEY_cstring: {
				cstring arg = va_arg(args, cstring);
				string uarg = ustrlit(arg);
				COPY_string(err_arg(e, i, string), uarg);
				break;
			}
			case ERR_KEY_string: {
				string arg = va_arg(args, string);
				COPY_string(err_arg(e, i, string), arg);
				break;
			}
			case ERR_KEY_ulong:
			case ERR_KEY_ucint: {
				ulong arg = va_arg(args, ulong);
				COPY_ulong(err_arg(e, i, ulong), arg);
				break;
			}
			case ERR_KEY_unsigned:
			case ERR_KEY_plural: {
				unsigned arg = va_arg(args, unsigned);
				COPY_unsigned(err_arg(e, i, unsigned), arg);
				break;
			}
			default : {
				error(ERR_INTERNAL, "Bad signature");
				break;
			}
			}
		}
	}
	va_end(args);
	return e;
}


/*
    This routine prints the body of the simple error message e to the
    buffer bf.
*/

static void
print_error_body(ERROR e, LOCATION *loc, BUFFER *bf)
{
	char c;
	QUALIFIER qual = qual_none;

	/* Extract error information */
	int n = DEREF_int(err_simple_number(e));
	unsigned sz = DEREF_unsigned(err_simple_size(e));

	/* Look up error in catalogue */
	ERR_DATA *msg = ERR_CATALOG + n;
	const char *sig = msg->signature;
	const char *s = msg->key_STD;

	/* Print the error message */
	if (s == NULL) return;
	while (c = *(s++), c != 0) {
		if (c == '%') {
			/* Error argument - find number */
			unsigned a;
			c = *(s++);
			if (c >= '0' && c <= '9') {
				/* Arguments 0 to 9 */
				a = (unsigned)(c - '0');
			} else {
				if (c != '%')bfputc(bf, '%');
				bfputc(bf, c);
				continue;
			}

			/* Find argument type */
			if (a < sz) {
				c = sig[a];
			} else {
				c = '?';
			}

			/* Print appropriate argument */
			switch (c) {
			case ERR_KEY_ACCESS: {
				ACCESS arg = DEREF_dspec(err_arg(e, a, ACCESS));
				IGNORE print_access(arg, bf, 0);
				break;
			}
			case ERR_KEY_BASE_TYPE: {
				BASE_TYPE arg;
				arg = DEREF_btype(err_arg(e, a, BASE_TYPE));
				IGNORE print_btype(arg, bf, 0);
				break;
			}
			case ERR_KEY_CLASS_TYPE: {
				CLASS_TYPE arg;
				arg = DEREF_ctype(err_arg(e, a, CLASS_TYPE));
				IGNORE print_ctype(arg, qual_none, 0, bf, 0);
				break;
			}
			case ERR_KEY_CV_SPEC: {
				CV_SPEC arg = DEREF_cv(err_arg(e, a, CV_SPEC));
				if (!print_cv(arg, bf, 0)) {
					bfprintf(bf, "<none>");
				}
				break;
			}
			case ERR_KEY_DECL_SPEC: {
				DECL_SPEC arg;
				arg = DEREF_dspec(err_arg(e, a, DECL_SPEC));
				if (!print_dspec(arg, bf, 0)) {
					bfprintf(bf, "<none>");
				}
				break;
			}
			case ERR_KEY_FLOAT: {
				FLOAT arg = DEREF_flt(err_arg(e, a, FLOAT));
				IGNORE print_flt(arg, bf, 0);
				break;
			}
			case ERR_KEY_HASHID: {
				HASHID arg = DEREF_hashid(err_arg(e, a, HASHID));
				IGNORE print_hashid(arg, 1, 1, bf, 0);
				break;
			}
			case ERR_KEY_IDENTIFIER: {
				IDENTIFIER arg;
				arg = DEREF_id(err_arg(e, a, IDENTIFIER));
				IGNORE print_id_short(arg, qual, bf, 0);
				qual = qual_none;
				break;
			}
			case ERR_KEY_LEX: {
				LEX arg = DEREF_int(err_arg(e, a, LEX));
				IGNORE print_lex(arg, bf, 0);
				break;
			}
			case ERR_KEY_LONG_ID: {
				LONG_ID arg = DEREF_id(err_arg(e, a, LONG_ID));
				IGNORE print_id_long(arg, qual, bf, 0);
				qual = qual_none;
				break;
			}
			case ERR_KEY_NAMESPACE: {
				NAMESPACE arg;
				arg = DEREF_nspace(err_arg(e, a, NAMESPACE));
				IGNORE print_nspace(arg, qual_none, 0, bf, 0);
				break;
			}
			case ERR_KEY_NAT: {
				NAT arg = DEREF_nat(err_arg(e, a, NAT));
				IGNORE print_nat(arg, 0, bf, 0);
				break;
			}
			case ERR_KEY_PPTOKEN_P: {
				PPTOKEN_P arg;
				arg = DEREF_pptok(err_arg(e, a, PPTOKEN_P));
				IGNORE print_pptok(arg, bf, 0);
				break;
			}
			case ERR_KEY_PTR_LOC: {
				PTR_LOC arg;
				arg = DEREF_ptr(err_arg(e, a, PTR_LOC));
				if (!IS_NULL_ptr(arg)) {
					LOCATION ploc;
					DEREF_loc(arg, ploc);
					IGNORE print_loc(&ploc, loc, bf, 0);
				} else {
					IGNORE print_loc(loc, loc, bf, 0);
				}
				break;
			}
			case ERR_KEY_QUALIFIER: {
				QUALIFIER arg;
				arg = DEREF_qual(err_arg(e, a, QUALIFIER));
				qual = arg;
				break;
			}
			case ERR_KEY_STRING: {
				STRING arg = DEREF_str(err_arg(e, a, STRING));
				IGNORE print_str(arg, bf, 0);
				break;
			}
			case ERR_KEY_TYPE: {
				TYPE arg = DEREF_type(err_arg(e, a, TYPE));
				IGNORE print_type(arg, bf, 0);
				break;
			}
			case ERR_KEY_cint: {
				cint arg = DEREF_int(err_arg(e, a, cint));
				unsigned long ca = (unsigned long)arg;
				print_char(ca, CHAR_SIMPLE, 0, bf);
				break;
			}
			case ERR_KEY_plural: {
				plural arg = DEREF_unsigned(err_arg(e, a, plural));
				if (arg != 1)bfputc(bf, 's');
				break;
			}
			case ERR_KEY_cstring:
			case ERR_KEY_string: {
				string arg =
				    DEREF_string(err_arg(e, a, string));
				if (arg) {
					ulong u;
					while (u = (ulong)*(arg++), u != 0) {
						print_char(u, CHAR_SIMPLE, 0,
							   bf);
					}
				}
				break;
			}
			case ERR_KEY_ucint: {
				ucint arg = DEREF_ulong(err_arg(e, a, ucint));
				if (arg <= (ucint)0xffff) {
					print_char(arg, CHAR_UNI4, 0, bf);
				} else {
					print_char(arg, CHAR_UNI8, 0, bf);
				}
				break;
			}
			case ERR_KEY_ulong: {
				ulong arg = DEREF_ulong(err_arg(e, a, ulong));
				bfprintf(bf, "%lu", arg);
				break;
			}
			case ERR_KEY_unsigned: {
				unsigned arg;
				arg = DEREF_unsigned(err_arg(e, a, unsigned));
				bfprintf(bf, "%u", arg);
				break;
			}
			default : {
				bfprintf(bf, "<arg%u>", a);
				break;
			}
			}
		} else {
			/* Other characters */
			bfputc(bf, c);
		}
	}
	return;
}


/*
    This routine prints the body of the error message given by e to the
    file f.
*/

static void
print_error_msg(ERROR e, LOCATION *loc, FILE *f)
{
	if (IS_err_simple(e)) {
		/* Print simple error message */
		BUFFER *bf;
		int n = DEREF_int(err_simple_number(e));
		ERR_DATA *msg = ERR_CATALOG + n;
		ERR_PROPS props = msg->props;
		int sev = DEREF_int(err_severity(e));
		if (sev == ERR_WHATEVER && print_short) return;
		bf = clear_buffer(&print_buff, f);
		if (loc)bfprintf(bf, MESSAGE_START);
		if (print_error_name) {
			const char *name = msg->name;
			if (name)bfprintf(bf, MESSAGE_NAME, name);
		}
		if (!(props & ERR_PROP_non_iso) && print_iso_ref) {
			const char *iso;
			ERR_DATA *prev = msg;
			while (iso = prev->key_ISO, iso == NULL) {
				/* Scan back to current section number */
				if (prev == ERR_CATALOG)break;
				prev--;
			}
			msg->key_ISO = iso;
			if (iso && iso[0]) {
				if (print_ansi_ref) {
					bfprintf(bf, MESSAGE_ANSI);
					iso_to_ansi(bf, iso);
					bfprintf(bf, MESSAGE_ANSI_END);
				} else {
					bfprintf(bf, MESSAGE_ISO, iso);
				}
			}
		}
		if (props) {
			if (props & ERR_PROP_pragma) {
				bfprintf(bf, MESSAGE_PRAGMA);
			}
			if (props & ERR_PROP_printf) {
				bfprintf(bf, MESSAGE_PRINTF);
			}
			if (props & ERR_PROP_token) {
				bfprintf(bf, MESSAGE_TOKEN);
			}
			if (props & ERR_PROP_syntax) {
				bfprintf(bf, MESSAGE_SYNTAX);
			}
		}
		print_error_body(e, loc, bf);
		bfprintf(bf, MESSAGE_END);
		output_buffer(bf, 1);

	} else {
		/* Print composite error message */
		ERROR e1 = DEREF_err(err_compound_head(e));
		ERROR e2 = DEREF_err(err_compound_tail(e));
		print_error_msg(e1, loc, f);
		print_error_msg(e2, loc, f);
	}
	return;
}


/*
    This routine destroys the error structure e.  If d is false then the
    first component of a compound error is not destroyed.
*/

void
destroy_error(ERROR e, int d)
{
	if (!IS_NULL_err(e)) {
		if (IS_err_simple(e)) {
			if (d)DESTROY_err_simple_args(e);
		} else {
			int sev;
			ERROR e1, e2;
			DESTROY_err_compound(destroy, sev, e1, e2, e);
			if (d)destroy_error(e1, 1);
			destroy_error(e2, 1);
			UNUSED(sev);
		}
	}
	return;
}


/*
    This routine joins the error structures e1 and e2 into a single compound
    error structure.
*/

ERROR
concat_error(ERROR e1, ERROR e2)
{
	ERROR e;
	int s1, s2;
	if (IS_NULL_err(e1)) {
		return e2;
	}
	if (IS_NULL_err(e2)) {
		return e1;
	}
	s1 = DEREF_int(err_severity(e1));
	s2 = DEREF_int(err_severity(e2));
	if (s2 > s1) {
		s1 = s2;
	}
	MAKE_err_compound(s1, e1, e2, e);
	return e;
}


/*
    This routine joins the error structures e1 and e2 into a single compound
    error structure if e1 represents a serious error.  Otherwise e2 is
    destroyed and e1 is returned.
*/

ERROR
concat_warning(ERROR e1, ERROR e2)
{
	ERROR e;
	int s1, s2;
	if (IS_NULL_err(e1)) {
		return e2;
	}
	if (IS_NULL_err(e2)) {
		return e1;
	}
	s1 = DEREF_int(err_severity(e1));
	if (s1 > ERR_WARN) {
		s2 = DEREF_int(err_severity(e2));
		if (s2 > s1) {
			s1 = s2;
		}
		MAKE_err_compound(s1, e1, e2, e);
	} else {
		destroy_error(e2, 1);
		e = e1;
	}
	return e;
}


/*
    This routine adds the error e to the end of the list indicated by err.
    If err is the null pointer then e is destroyed.
*/

void
add_error(ERROR *err, ERROR e)
{
	if (!IS_NULL_err(e)) {
		if (err) {
			ERROR e1 = *err;
			if (IS_NULL_err(e1)) {
				*err = e;
			} else {
				int s1 = DEREF_int(err_severity(e1));
				int s2 = DEREF_int(err_severity(e));
				if (s2 > s1) {
					s1 = s2;
				}
				MAKE_err_compound(s1, e1, e, *err);
			}
		} else {
			destroy_error(e, 1);
		}
	}
	return;
}


/*
    These variables give an error message which is added to the start
    of any error before it is printed.  The prefix error severity is not
    taken into account in the overall error severity.
*/

static ERROR error_prefix = NULL_err;


/*
    This routine sets the error prefix to be e, returning the previous
    value.
*/

ERROR
set_prefix(ERROR e)
{
	ERROR p = error_prefix;
	error_prefix = e;
	return p;
}


/*
    This routine restores the error prefix to e, destroying the previous
    value.
*/

void
restore_prefix(ERROR e)
{
	destroy_error(error_prefix, 1);
	error_prefix = e;
	return;
}


/*
    This routine prints the error e at location loc.
*/

void
print_error(LOCATION *loc, ERROR e)
{
	if (!IS_NULL_err(e)) {
		int d = 1;
		int sev = DEREF_int(err_severity(e));
		ERROR p = error_prefix;
		if (!IS_NULL_err(p)) {
			/* Add error prefix */
			MAKE_err_compound(sev, p, e, e);
			d = 0;
		}
		if (do_error && dump_error(e, loc, sev, 0)) {
			/* Dump error to file */
			unsigned long n;
			IGNORE error_header(sev);
			n = number_errors;
			error_break();
			if (sev == ERR_FATAL)term_error(0);
			if (n >= max_errors)term_error(0);
		} else {
			/* Print error to standard error */
			FILE *f = error_file;
			print_error_start(f, loc, sev);
			print_error_msg(e, loc, f);
			print_error_end(f, sev);
		}
		destroy_error(e, d);
	}
	return;
}


/*
    This routine creates an install-time error expression for the error
    e at the location loc.
*/

EXP
install_error(LOCATION *loc, ERROR e)
{
	EXP a = NULL_exp;
	if (!IS_NULL_err(e)) {
		int sev = DEREF_int(err_severity(e));
		if (sev > ERR_WARN) {
			string s;
			BUFFER *bf = clear_buffer(&print_buff, NIL(FILE));
			if (loc) {
				IGNORE print_loc(loc, NIL(LOCATION), bf, 0);
				bfprintf(bf, ": ");
			}
			print_error_body(e, loc, bf);
			bfputc(bf, 0);
			s = xustrcpy(bf->start);
			MAKE_exp_fail(type_bottom, s, a);
		}
		destroy_error(e, 1);
	}
	return a;
}


/*
    This routine is used in verbose mode to print a running commentary of
    the compilation of the object id.
*/

void
commentary(IDENTIFIER id)
{
	if (verbose && !IS_NULL_id(id)) {
		BUFFER *bf = clear_buffer(&print_buff, stdout);
		print_id_desc++;
		IGNORE print_id_long(id, qual_none, bf, 0);
		print_id_desc--;
		bfprintf(bf, " ;\n");
		output_buffer(bf, 1);
	}
	return;
}

