/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


#ifndef CONSFILE_INCLUDED
#define CONSFILE_INCLUDED


/* AUTOMATICALLY GENERATED BY make_tdf VERSION 2.0 FROM TDF 4.0 */

#include "defs.h"
extern Constructs constructs [] ;
extern void c_add_accesses PROTO_S ( ( void ) ) ;	/* 0 */
extern void c_constant PROTO_S ( ( void ) ) ;		/* 1 */
extern void c_long_jump_access PROTO_S ( ( void ) ) ;	/* 2 */
extern void c_no_other_read PROTO_S ( ( void ) ) ;	/* 3 */
extern void c_no_other_write PROTO_S ( ( void ) ) ;	/* 4 */
extern void c_out_par PROTO_S ( ( void ) ) ;		/* 5 */
extern void c_preserve PROTO_S ( ( void ) ) ;		/* 6 */
extern void c_register PROTO_S ( ( void ) ) ;		/* 7 */
extern void c_standard_access PROTO_S ( ( void ) ) ;	/* 8 */
extern void c_used_as_volatile PROTO_S ( ( void ) ) ;	/* 9 */
extern void c_visible PROTO_S ( ( void ) ) ;		/* 10 */
extern void c_alignment PROTO_S ( ( void ) ) ;		/* 11 */
extern void c_alloca_alignment PROTO_S ( ( void ) ) ;	/* 12 */
extern void c_callees_alignment PROTO_S ( ( void ) ) ;	/* 13 */
extern void c_callers_alignment PROTO_S ( ( void ) ) ;	/* 14 */
extern void c_code_alignment PROTO_S ( ( void ) ) ;	/* 15 */
extern void c_locals_alignment PROTO_S ( ( void ) ) ;	/* 16 */
extern void c_parameter_alignment PROTO_S ( ( void ) ) ;	/* 17 */
extern void c_unite_alignments PROTO_S ( ( void ) ) ;	/* 18 */
extern void c_var_param_alignment PROTO_S ( ( void ) ) ;	/* 19 */
extern void c_bfvar_bits PROTO_S ( ( void ) ) ;		/* 20 */
extern void c_false PROTO_S ( ( void ) ) ;		/* 21 */
extern void c_true PROTO_S ( ( void ) ) ;		/* 22 */
extern void c_nil_access PROTO_S ( ( void ) ) ;		/* 23 */
extern void c_overflow PROTO_S ( ( void ) ) ;		/* 24 */
extern void c_stack_overflow PROTO_S ( ( void ) ) ;	/* 25 */
extern void c_continue PROTO_S ( ( void ) ) ;		/* 26 */
extern void c_trap PROTO_S ( ( void ) ) ;		/* 27 */
extern void c_wrap PROTO_S ( ( void ) ) ;		/* 28 */
extern void c_impossible PROTO_S ( ( void ) ) ;		/* 29 */
extern void c_abs PROTO_S ( ( void ) ) ;		/* 30 */
extern void c_add_to_ptr PROTO_S ( ( void ) ) ;		/* 31 */
extern void c_and PROTO_S ( ( void ) ) ;		/* 32 */
extern void c_assign PROTO_S ( ( void ) ) ;		/* 33 */
extern void c_assign_with_mode PROTO_S ( ( void ) ) ;	/* 34 */
extern void c_bitfield_assign PROTO_S ( ( void ) ) ;	/* 35 */
extern void c_bitfield_assign_with_mode PROTO_S ( ( void ) ) ;	/* 36 */
extern void c_bitfield_contents PROTO_S ( ( void ) ) ;	/* 37 */
extern void c_bitfield_contents_with_mode PROTO_S ( ( void ) ) ;	/* 38 */
extern void c_change_bitfield_to_int PROTO_S ( ( void ) ) ;	/* 39 */
extern void c_change_floating_variety PROTO_S ( ( void ) ) ;	/* 40 */
extern void c_change_variety PROTO_S ( ( void ) ) ;	/* 41 */
extern void c_change_int_to_bitfield PROTO_S ( ( void ) ) ;	/* 42 */
extern void c_complex_conjugate PROTO_S ( ( void ) ) ;	/* 43 */
extern void c_component PROTO_S ( ( void ) ) ;		/* 44 */
extern void c_concat_nof PROTO_S ( ( void ) ) ;		/* 45 */
extern void c_conditional PROTO_S ( ( void ) ) ;	/* 46 */
extern void c_contents PROTO_S ( ( void ) ) ;		/* 47 */
extern void c_contents_with_mode PROTO_S ( ( void ) ) ;	/* 48 */
extern void c_current_env PROTO_S ( ( void ) ) ;	/* 49 */
extern void c_div0 PROTO_S ( ( void ) ) ;		/* 50 */
extern void c_div1 PROTO_S ( ( void ) ) ;		/* 51 */
extern void c_div2 PROTO_S ( ( void ) ) ;		/* 52 */
extern void c_env_offset PROTO_S ( ( void ) ) ;		/* 53 */
extern void c_env_size PROTO_S ( ( void ) ) ;		/* 54 */
extern void c_fail_installer PROTO_S ( ( void ) ) ;	/* 55 */
extern void c_float_int PROTO_S ( ( void ) ) ;		/* 56 */
extern void c_floating_abs PROTO_S ( ( void ) ) ;	/* 57 */
extern void c_floating_div PROTO_S ( ( void ) ) ;	/* 58 */
extern void c_floating_minus PROTO_S ( ( void ) ) ;	/* 59 */
extern void c_floating_maximum PROTO_S ( ( void ) ) ;	/* 60 */
extern void c_floating_minimum PROTO_S ( ( void ) ) ;	/* 61 */
extern void c_floating_mult PROTO_S ( ( void ) ) ;	/* 62 */
extern void c_floating_negate PROTO_S ( ( void ) ) ;	/* 63 */
extern void c_floating_plus PROTO_S ( ( void ) ) ;	/* 64 */
extern void c_floating_power PROTO_S ( ( void ) ) ;	/* 65 */
extern void c_floating_test PROTO_S ( ( void ) ) ;	/* 66 */
extern void c_goto PROTO_S ( ( void ) ) ;		/* 67 */
extern void c_goto_local_lv PROTO_S ( ( void ) ) ;	/* 68 */
extern void c_ignorable PROTO_S ( ( void ) ) ;		/* 69 */
extern void c_imaginary_part PROTO_S ( ( void ) ) ;	/* 70 */
extern void c_initial_value PROTO_S ( ( void ) ) ;	/* 71 */
extern void c_integer_test PROTO_S ( ( void ) ) ;	/* 72 */
extern void c_last_local PROTO_S ( ( void ) ) ;		/* 73 */
extern void c_local_alloc PROTO_S ( ( void ) ) ;	/* 74 */
extern void c_local_alloc_check PROTO_S ( ( void ) ) ;	/* 75 */
extern void c_local_free PROTO_S ( ( void ) ) ;		/* 76 */
extern void c_local_free_all PROTO_S ( ( void ) ) ;	/* 77 */
extern void c_long_jump PROTO_S ( ( void ) ) ;		/* 78 */
extern void c_make_complex PROTO_S ( ( void ) ) ;	/* 79 */
extern void c_make_compound PROTO_S ( ( void ) ) ;	/* 80 */
extern void c_make_local_lv PROTO_S ( ( void ) ) ;	/* 81 */
extern void c_make_nof PROTO_S ( ( void ) ) ;		/* 82 */
extern void c_make_nof_int PROTO_S ( ( void ) ) ;	/* 83 */
extern void c_make_null_local_lv PROTO_S ( ( void ) ) ;	/* 84 */
extern void c_make_null_proc PROTO_S ( ( void ) ) ;	/* 85 */
extern void c_make_null_ptr PROTO_S ( ( void ) ) ;	/* 86 */
extern void c_make_stack_limit PROTO_S ( ( void ) ) ;	/* 87 */
extern void c_make_top PROTO_S ( ( void ) ) ;		/* 88 */
extern void c_make_value PROTO_S ( ( void ) ) ;		/* 89 */
extern void c_maximum PROTO_S ( ( void ) ) ;		/* 90 */
extern void c_minimum PROTO_S ( ( void ) ) ;		/* 91 */
extern void c_minus PROTO_S ( ( void ) ) ;		/* 92 */
extern void c_move_some PROTO_S ( ( void ) ) ;		/* 93 */
extern void c_mult PROTO_S ( ( void ) ) ;		/* 94 */
extern void c_n_copies PROTO_S ( ( void ) ) ;		/* 95 */
extern void c_negate PROTO_S ( ( void ) ) ;		/* 96 */
extern void c_not PROTO_S ( ( void ) ) ;		/* 97 */
extern void c_offset_add PROTO_S ( ( void ) ) ;		/* 98 */
extern void c_offset_div PROTO_S ( ( void ) ) ;		/* 99 */
extern void c_offset_div_by_int PROTO_S ( ( void ) ) ;	/* 100 */
extern void c_offset_max PROTO_S ( ( void ) ) ;		/* 101 */
extern void c_offset_mult PROTO_S ( ( void ) ) ;	/* 102 */
extern void c_offset_negate PROTO_S ( ( void ) ) ;	/* 103 */
extern void c_offset_pad PROTO_S ( ( void ) ) ;		/* 104 */
extern void c_offset_subtract PROTO_S ( ( void ) ) ;	/* 105 */
extern void c_offset_test PROTO_S ( ( void ) ) ;	/* 106 */
extern void c_offset_zero PROTO_S ( ( void ) ) ;	/* 107 */
extern void c_or PROTO_S ( ( void ) ) ;			/* 108 */
extern void c_plus PROTO_S ( ( void ) ) ;		/* 109 */
extern void c_pointer_test PROTO_S ( ( void ) ) ;	/* 110 */
extern void c_power PROTO_S ( ( void ) ) ;		/* 111 */
extern void c_proc_test PROTO_S ( ( void ) ) ;		/* 112 */
extern void c_profile PROTO_S ( ( void ) ) ;		/* 113 */
extern void c_real_part PROTO_S ( ( void ) ) ;		/* 114 */
extern void c_rem0 PROTO_S ( ( void ) ) ;		/* 115 */
extern void c_rem1 PROTO_S ( ( void ) ) ;		/* 116 */
extern void c_rem2 PROTO_S ( ( void ) ) ;		/* 117 */
extern void c_repeat PROTO_S ( ( void ) ) ;		/* 118 */
extern void c_return PROTO_S ( ( void ) ) ;		/* 119 */
extern void c_return_to_label PROTO_S ( ( void ) ) ;	/* 120 */
extern void c_round_with_mode PROTO_S ( ( void ) ) ;	/* 121 */
extern void c_rotate_left PROTO_S ( ( void ) ) ;	/* 122 */
extern void c_rotate_right PROTO_S ( ( void ) ) ;	/* 123 */
extern void c_set_stack_limit PROTO_S ( ( void ) ) ;	/* 124 */
extern void c_shape_offset PROTO_S ( ( void ) ) ;	/* 125 */
extern void c_shift_left PROTO_S ( ( void ) ) ;		/* 126 */
extern void c_shift_right PROTO_S ( ( void ) ) ;	/* 127 */
extern void c_subtract_ptrs PROTO_S ( ( void ) ) ;	/* 128 */
extern void c_untidy_return PROTO_S ( ( void ) ) ;	/* 129 */
extern void c_xor PROTO_S ( ( void ) ) ;		/* 130 */
extern void c_flvar_parms PROTO_S ( ( void ) ) ;	/* 131 */
extern void c_complex_parms PROTO_S ( ( void ) ) ;	/* 132 */
extern void c_float_of_complex PROTO_S ( ( void ) ) ;	/* 133 */
extern void c_complex_of_float PROTO_S ( ( void ) ) ;	/* 134 */
extern void c_computed_nat PROTO_S ( ( void ) ) ;	/* 135 */
extern void c_error_val PROTO_S ( ( void ) ) ;		/* 136 */
extern void c_equal PROTO_S ( ( void ) ) ;		/* 137 */
extern void c_greater_than PROTO_S ( ( void ) ) ;	/* 138 */
extern void c_greater_than_or_equal PROTO_S ( ( void ) ) ;	/* 139 */
extern void c_less_than PROTO_S ( ( void ) ) ;		/* 140 */
extern void c_less_than_or_equal PROTO_S ( ( void ) ) ;	/* 141 */
extern void c_not_equal PROTO_S ( ( void ) ) ;		/* 142 */
extern void c_not_greater_than PROTO_S ( ( void ) ) ;	/* 143 */
extern void c_not_greater_than_or_equal PROTO_S ( ( void ) ) ;	/* 144 */
extern void c_not_less_than PROTO_S ( ( void ) ) ;	/* 145 */
extern void c_not_less_than_or_equal PROTO_S ( ( void ) ) ;	/* 146 */
extern void c_less_than_or_greater_than PROTO_S ( ( void ) ) ;	/* 147 */
extern void c_not_less_than_and_not_greater_than PROTO_S ( ( void ) ) ;	/* 148 */
extern void c_comparable PROTO_S ( ( void ) ) ;		/* 149 */
extern void c_not_comparable PROTO_S ( ( void ) ) ;	/* 150 */
extern void c_round_as_state PROTO_S ( ( void ) ) ;	/* 151 */
extern void c_to_nearest PROTO_S ( ( void ) ) ;		/* 152 */
extern void c_toward_larger PROTO_S ( ( void ) ) ;	/* 153 */
extern void c_toward_smaller PROTO_S ( ( void ) ) ;	/* 154 */
extern void c_toward_zero PROTO_S ( ( void ) ) ;	/* 155 */
extern void c_bitfield PROTO_S ( ( void ) ) ;		/* 156 */
extern void c_bottom PROTO_S ( ( void ) ) ;		/* 157 */
extern void c_compound PROTO_S ( ( void ) ) ;		/* 158 */
extern void c_floating PROTO_S ( ( void ) ) ;		/* 159 */
extern void c_integer PROTO_S ( ( void ) ) ;		/* 160 */
extern void c_nof PROTO_S ( ( void ) ) ;		/* 161 */
extern void c_offset PROTO_S ( ( void ) ) ;		/* 162 */
extern void c_pointer PROTO_S ( ( void ) ) ;		/* 163 */
extern void c_proc PROTO_S ( ( void ) ) ;		/* 164 */
extern void c_top PROTO_S ( ( void ) ) ;		/* 165 */
extern void c_computed_signed_nat PROTO_S ( ( void ) ) ;	/* 166 */
extern void c_make_signed_nat PROTO_S ( ( void ) ) ;	/* 167 */
extern void c_snat_from_nat PROTO_S ( ( void ) ) ;	/* 168 */
extern void c_add_modes PROTO_S ( ( void ) ) ;		/* 169 */
extern void c_overlap PROTO_S ( ( void ) ) ;		/* 170 */
extern void c_standard_transfer_mode PROTO_S ( ( void ) ) ;	/* 171 */
extern void c_trap_on_nil PROTO_S ( ( void ) ) ;	/* 172 */
extern void c_volatile PROTO_S ( ( void ) ) ;		/* 173 */
extern void c_complete PROTO_S ( ( void ) ) ;		/* 174 */
extern void c_var_limits PROTO_S ( ( void ) ) ;		/* 175 */
extern void c_var_width PROTO_S ( ( void ) ) ;		/* 176 */

#define no_of_cons					177


#endif
