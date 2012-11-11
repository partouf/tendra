/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CONFIG_INCLUDED
#define CONFIG_INCLUDED


/* API SPECIFICATION */
#include <reader/ossg_api.h>
#include <reader/ossg.h>

#ifndef FS_LITTLE_ENDIAN
#define FS_LITTLE_ENDIAN	0
#endif

#define null			NULL


/* Settings for Solaris 2 */
#define SYSV_ABI		1
#define DWARF			0
#define ADDUNDERSCORE		0

#define NEEDS_DEBUG_ALIGN	1


/* CONFIGURATION OPTIONS */

#define GENCOMPAT		1
#define NEWDIAGS		1
#define NEWDWARF		1

#define has_asm			1


#define dont_unpad_apply	1
#define has_byte_ops		0
#define has_byte_regs		0
#define has_neg_shift		0
#define has_setcc		0
#define has64bits		0
#define keep_PIC_vars		1
#define no_bitfield_ops		0
#define only_lengthen_ops	0
#define remove_zero_offsets	0
#define replace_compound	0
#define substitute_params	0
#define substitute_complex	1
#define div0_implemented 	1

/* foralls config */
#define remove_unused_counters 0
#define remove_unused_index_counters 1

#define good_index_factor(f) 0
#define good_pointer_factor(f) 1

#if SYSV_ABI
#define target_dbl_maxexp	16384
#define use_long_double		1
#else
#define target_dbl_maxexp	308
#define use_long_double		0
#endif

#define value_of_null 0

#define has_rotate 0

#define diagnose_registers 1

#define promote_pars 1

	/* condition for shape to be treated as a struct */
#define sparccpd(s) (name(s) == cpdhd || name(s) == nofhd || \
			name(s) == shcomplexhd || shape_size(s)>64 || \
			name(s) == u64hd || name(s) == s64hd)

#endif /* CONFIG_INCLUDED */


