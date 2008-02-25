/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */

#include <ctype.h>

#include "config.h"
#include "cstring.h"
#include "fmm.h"
#include "msgcat.h"

#include "filename.h"
#include "list.h"
#include "external.h"
#include "flags.h"
#include "startup.h"
#include "suffix.h"
#include "utility.h"


/*
 *    CASE SENSITIVITY FLAG
 *
 *    This flag may be set to true to make tcc ignore case in filename
 *    suffixes.
 */

boolean case_insensitive = 0;


/*
 *    CONVERT A STRING TO LOWER CASE
 *
 *    This routine converts the string s to lower case.
 */

static void
to_lower_case(char *s)
{
	while (*s != '\0') {
		*s = tolower ((unsigned char)*s);
		s++;
	}
	return;
}


/*
 *    SUFFIX OVERRIDES
 *
 *    This table contains the strings which are used when the suffix
 *    overrides are set from the command line.  Initially, it is
 *    empty.  This table needs to be kept in step with Table 1.
 */

char *suffixes [TYPE_ARRAY_SIZE] = {
	null,	/* C_SOURCE */
	null,	/* PREPROC_C */
	"cpp",	/* CPP_SOURCE */
	null,	/* PREPROC_CPP */
	null,	/* INDEP_TDF */
	null,	/* DEP_TDF */
	null,	/* AS_SOURCE */
	null,	/* PREPROC_AS */
	null,	/* BINARY_OBJ */
	null,	/* EXECUTABLE */
	null,	/* PRETTY_TDF */
	null,	/* PL_TDF */
	null,	/* TDF_ARCHIVE */
	null,	/* MIPS_G_FILE */
	null,	/* MIPS_T_FILE */
	null,	/* C_SPEC */
	null,	/* CPP_SPEC */
	null,  	/* ERROR_FILE */
	null,	/* STARTUP_FILE */
	null,	/* UNKNOWN_TYPE */
	null,	/* INDEP_TDF_COMPLEX (dummy type) */
	null,	/* C_SPEC_1 (dummy type) */
	null,	/* C_SPEC_2 (dummy type) */
	null,	/* INDEP_TDF_AUX (dummy type) */
	null	/* BINARY_OBJ_AUX (dummy type) */
};


/*
 *    FILE STORAGE LOCATIONS
 *
 *    Output files may be stored either in the temporary directory, tempdir,
 *    or the work directory, workdir.
 */

char *tempdir = null;
char *workdir = null;


/*
 *    FIND THE BASE NAME OF A FILE
 *
 *    This routine returns the basename of the file name s.
 */

char *
find_basename(char *s)
{
	char *r = strrchr (s, '/');
	if (r != NULL)
		return (r + 1);
	return (s);
}


/*
 *    FIND THE FULL NAME OF A FILE
 *
 *    This routine returns the full name of the file name s.
 */

char *
find_fullname(char *s)
{
	static char *pwd = null;
	if (*s == '/') return (s);
	if (pwd == null) {
		if (get_cwd (buffer, buffer_size)) {
			pwd = string_concat (buffer, "/");
		} else {
			MSG_cant_determine_current_working_directory ();
			pwd = "";
		}
	}
	return (string_concat (pwd, s));
}


/*
 *    SPLIT OFF THE SUFFIX OF A FILE NAME
 *
 *    This routine splits the file name s into two part, the base part and
 *    the file suffix, and returns the latter.
 */

static char *
split_name(char *s)
{
	char *p = strrchr (s, '.');
	if (p != NULL) {
		*p = '\0';
		if (case_insensitive) {
			/* Allow for case insensitive systems */
			to_lower_case (p + 1);
		}
		return (p + 1);
	}
	return ("");
}


/*
 *    CREATE A NEW FILENAME
 *
 *    This routine allocates a new filename structure.
 */

static filename *
new_filename(void)
{
	return (xalloc (sizeof (filename)));
}


/*
 *    ADD A FILENAME TO A LIST
 *
 *    This routine joins the two filename lists, p and q, returning the
 *    result.
 */

filename *
add_filename(filename *p, filename *q)
{
	filename *r;
	if (p == null) return (q);
	if (q == null) return (p);
	for (r = p; r->next != null; r = r->next) /* empty */;
	r->next = q;
	return (p);
}


/*
 *    CONVERT A KEY LETTER TO A FILE TYPE
 *
 *    This routine converts the letter s, which can be a file suffix (if
 *    suff is true), or a stage identifier (otherwise), to a file type.
 *    This routine needs to be kept in step with Table 1 and Table 2.
 */

int
find_type(int s, int suff)
{
	switch (s) {
	case C_SOURCE_KEY : return (C_SOURCE);
	case PREPROC_C_KEY : return (PREPROC_C);
	case CPP_SOURCE_KEY : return (CPP_SOURCE);
	case PREPROC_CPP_KEY : return (PREPROC_CPP);
	case AS_SOURCE_KEY : return (AS_SOURCE);
	case PREPROC_AS_KEY : return (PREPROC_AS);
	case BINARY_OBJ_KEY : return (BINARY_OBJ);
	case C_SPEC_KEY : return (C_SPEC);
	case CPP_SPEC_KEY : return (CPP_SPEC);
	}
	if (!checker) {
		switch (s) {
		case INDEP_TDF_KEY : return (INDEP_TDF);
		case DEP_TDF_KEY : return (DEP_TDF);
		case PRETTY_TDF_KEY : return (PRETTY_TDF);
		}
	}
	if (suff) return (DEFAULT_TYPE);
	switch (s) {
	case MIPS_G_FILE_KEY : return (MIPS_G_FILE);
	case MIPS_T_FILE_KEY : return (MIPS_T_FILE);
	case STARTUP_FILE_KEY : return (STARTUP_FILE);
	case ALL_KEY : return (ALL_TYPES);
	}
	if (!checker) {
		switch (s) {
		case PL_TDF_KEY : return (PL_TDF);
		case TDF_ARCHIVE_KEY : return (TDF_ARCHIVE);
		}
	}
	MSG_unknown_file_type (s);
	return (UNKNOWN_TYPE);
}


/*
 *    FIND A FILE SUFFIX
 *
 *    This routine converts a file type, t, into the corresponding file
 *    suffix.  It needs to be kept in step with Table 1 and Table 2.
 */

static char *
file_suffix(int t)
{
	static char suff [3];
	suff [0] = 0;
	suff [1] = 0;
	suff [2] = 0;
	switch (t) {
	case C_SOURCE : suff [0] = C_SOURCE_KEY; break;
	case PREPROC_C : suff [0] = PREPROC_C_KEY; break;
	case CPP_SOURCE : suff [0] = CPP_SOURCE_KEY; break;
	case PREPROC_CPP : suff [0] = PREPROC_CPP_KEY; break;
	case INDEP_TDF : suff [0] = INDEP_TDF_KEY; break;
	case INDEP_TDF_AUX : {
		suff [0] = INDEP_TDF_KEY;
		suff [1] = EXTRA_KEY;
		break;
	}
	case DEP_TDF : suff [0] = DEP_TDF_KEY; break;
	case AS_SOURCE : suff [0] = AS_SOURCE_KEY; break;
	case PREPROC_AS : suff [0] = PREPROC_AS_KEY; break;
	case BINARY_OBJ : suff [0] = BINARY_OBJ_KEY; break;
	case BINARY_OBJ_AUX : {
		if ((use_sparc_cc == 1) && use_system_cc) {
			suff [0] = '.';
			suff [1] = BINARY_OBJ_KEY;
		} else {
			suff [0] = BINARY_OBJ_AUX_KEY;
		}
		break;
	}
	case PRETTY_TDF : suff [0] = PRETTY_TDF_KEY; break;
	case PL_TDF : suff [0] = PL_TDF_KEY; break;
	case MIPS_G_FILE : suff [0] = MIPS_G_FILE_KEY; break;
	case MIPS_T_FILE : suff [0] = MIPS_T_FILE_KEY; break;
	case C_SPEC : suff [0] = C_SPEC_KEY; break;
	case CPP_SPEC : suff [0] = CPP_SPEC_KEY; break;
	}
	if (suff [0]) {
		if (case_insensitive && isupper ((unsigned char) suff [0])) {
			/* Make allowances for case insensitive systems */
			to_lower_case (suff);
			suff [1] = suff [0];
		}
		return (suff);
	}
	MSG_illegal_file_type ();
	return (file_suffix (DEFAULT_TYPE));
}


/*
 *    NEXT FILENAME IS ACTUALLY AN INPUT OPTION
 *
 *    Some command-line options, for example, system libraries, are treated
 *    like input files.  This flag is set to indicate that the next input
 *    file is actually an input option.
 */

boolean option_next = 0;


/*
 *    COUNT OF NUMBER OF INPUT FILES
 *
 *    The number of calls to find_filename is recorded.  Input options are
 *    excluded from this count.
 */

int no_input_files = 0;


/*
 *    ALLOCATE A NEW UNIQUE IDENTIFIER
 *
 *    Each file is assigned a unique number which identifies it and all the
 *    files derived from it.  This macro assigns a new unique number.
 */

static int uniq_no = 0;
#define new_unique()	(uniq_no++)


/*
 *    CREATE A FILENAME FROM A PATHNAME
 *
 *    This routine creates a new filename structure, corresponding to the
 *    file with name s and type t.  If t is UNKNOWN_TYPE then the actual
 *    file type is deduced from the file suffix.  This routine needs to
 *    be kept in step with Table 1, Table 2 and Table 3.
 */

filename *
find_filename(char *s, int t)
{
	filename *p = new_filename ();
	char *b = string_copy (find_basename (s));
	char *e = split_name (b);
	int i;

	/* Find the file type */
	if (suffix_overrides && t == UNKNOWN_TYPE) {
		for (i = 0; i < TYPE_ARRAY_SIZE; i++) {
			if (suffixes [i] != null && streq (e, suffixes [i])) {
				if (checker) {
					if (i == PL_TDF || i == TDF_ARCHIVE) continue;
				}
				t = i;
				break;
			}
		}
	}
	if (t == UNKNOWN_TYPE) {
		if (e [0]) {
			if (e [1]) {
				if (e [2]) {
					/* Length >= 3 */
					if (streq (e, CPP_2_SUFFIX)) {
						t = CPP_SOURCE;
					} else if (streq (e, PREPROC_CPP_2_SUFFIX)) {
						t = PREPROC_CPP;
					} else if (streq (e, AS_2_SUFFIX)) {
						t = AS_SOURCE;
					} else {
						t = DEFAULT_TYPE;
					}
				} else {
					/* Length == 2 */
					if (e [1] == EXTRA_KEY) {
						t = find_type (e [0], 1);
					} else if (streq (e, CPP_1_SUFFIX)) {
						t = CPP_SOURCE;
					} else if (streq (e, PREPROC_CPP_1_SUFFIX)) {
						t = PREPROC_CPP;
					} else if (streq (e, CPP_SPEC_1_SUFFIX)) {
						t = CPP_SPEC;
					} else if (checker) {
						t = DEFAULT_TYPE;
					} else if (streq (e, PL_TDF_SUFFIX)) {
						t = PL_TDF;
					} else if (streq (e, TDF_ARCHIVE_SUFFIX)) {
						t = TDF_ARCHIVE;
					} else {
						t = DEFAULT_TYPE;
					}
				}
			} else {
				/* Length == 1 */
				t = find_type (e [0], 1);
			}
		} else {
			/* Length == 0 */
			t = DEFAULT_TYPE;
		}
	}

	/* Return the result */
	p->name = s;
	p->bname = b;
	p->uniq = new_unique ();
	p->type = t;
	if (option_next) {
		p->storage = INPUT_OPTION;
		option_next = 0;
	} else {
		p->storage = INPUT_FILE;
		no_input_files++;
	}
	p->final = 0;
	p->aux = null;
	p->next = null;
	return (p);
}


/*
 *    FIND WHERE TO STORE FILES OF A GIVEN TYPE
 *
 *    This routine returns the storage class for files of type t.  Note
 *    that this may be PRESERVED_FILE which is only a legal storage type
 *    when it is passed to make_filename (which turns it into OUTPUT_FILE).
 */

int
where(int t)
{
	if (!keeps [t]) return (TEMP_FILE);
	if (!stops [t]) return (PRESERVED_FILE);
	return (OUTPUT_FILE);
}


/*
 *    CREATE A FILENAME FROM ANOTHER FILENAME
 *
 *    This routine creates a new filename structure by forming the file
 *    derived from p which has type t and storage s.  This routine needs
 *    to be kept in step with Table 1 and Table 2.
 */

filename *
make_filename(filename *p, int t, int s)
{
	boolean f = 0;
	char *b, *d, *e;
	char *nm = null;
	filename *q = new_filename ();

	/* Examine the storage class */
	switch (s) {
	case INPUT_FILE :
	case INPUT_OPTION : {
		/* This shouldn't occur */
		d = null;
		break;
	}
	case OUTPUT_FILE : {
		/* Check output file name */
		if (final_name) {
			static boolean used_final_name = 0;
			if (used_final_name) {
				MSG_can_only_name_one_file_with_o ();
			} else {
				nm = final_name;
				b = find_basename (nm);
#ifdef EXECUTABLE_SUFFIX
				if (t == EXECUTABLE && strchr (b, '.') == null) {
					/* Add '.exe' suffix if necessary */
					nm = string_concat (nm, EXECUTABLE_SUFFIX);
					b = string_concat (b, EXECUTABLE_SUFFIX);
				}
#endif
				used_final_name = 1;
				f = 1;
			}
		}
		d = workdir;
		break;
	}
	case PRESERVED_FILE : {
		/* Preserved files are turned into output files */
		d = workdir;
		s = OUTPUT_FILE;
		break;
	}
	case TEMP_FILE : {
		/* Temporary files */
		d = tempdir;
		break;
	}
	default : {
		MSG_illegal_storage_type ();
		d = null;
		break;
	}
	}

	/* Find the file name */
	if (nm == null) {
		if (p != null && p->type == t) {
			nm = find_basename (p->name);
			if (d != null) {
				IGNORE sprintf (buffer, "%s/%s", d, nm);
				nm = string_copy (buffer);
			}
			b = p->bname;
		} else if (s == TEMP_FILE && p != null && !verbose) {
			switch (t) {
			case BINARY_OBJ_AUX :
			case BINARY_OBJ : break;
			case C_SPEC : break;
			case CPP_SPEC : break;
			case INDEP_TDF_AUX :
			case INDEP_TDF : {
				if (make_archive || make_complex || make_pretty ||
					tokdef_name) {
					break;
				}
				goto default_lab;
			}
			default :
				default_lab : {
					b = p->bname;
					e = file_suffix (t);
					IGNORE sprintf (buffer, "%s/%s.%s", d, TEMP_NAME, e);
					nm = string_copy (buffer);
					break;
				}
			}
		}
	}

	/* Find the file name */
	if (nm == null) {
		if (p == null || make_up_names) {
			static int seq = 0;
			IGNORE sprintf (buffer, MADE_UP_NAME, seq++);
			b = string_copy (buffer);
		} else {
			b = p->bname;
		}
		e = file_suffix (t);
		if (d == null) {
			IGNORE sprintf (buffer, "%s.%s", b, e);
		} else {
			IGNORE sprintf (buffer, "%s/%s.%s", d, b, e);
		}
		nm = string_copy (buffer);
	}

	/* Fill in the fields of the result */
	SET (b);
	q->name = nm;
	q->bname = b;
	q->uniq = (p ? p->uniq : new_unique ());
	q->type = t;
	q->storage = s;
	q->final = f;
	q->aux = null;
	q->next = null;
	return (q);
}