/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef CONSFILE_INCLUDED
#define CONSFILE_INCLUDED


/* AUTOMATICALLY GENERATED BY make_tdf VERSION 2.0 FROM TDF 4.0 */

#include "defs.h"
extern Constructs constructs[];
extern void c_add_accesses(void);			/* 0 */
extern void c_constant(void);				/* 1 */
extern void c_long_jump_access(void);			/* 2 */
extern void c_no_other_read(void);			/* 3 */
extern void c_no_other_write(void);			/* 4 */
extern void c_out_par(void);				/* 5 */
extern void c_preserve(void);				/* 6 */
extern void c_register(void);				/* 7 */
extern void c_standard_access(void);			/* 8 */
extern void c_used_as_volatile(void);			/* 9 */
extern void c_visible(void);				/* 10 */
extern void c_alignment(void);				/* 11 */
extern void c_alloca_alignment(void);			/* 12 */
extern void c_callees_alignment(void);			/* 13 */
extern void c_callers_alignment(void);			/* 14 */
extern void c_code_alignment(void);			/* 15 */
extern void c_locals_alignment(void);			/* 16 */
extern void c_parameter_alignment(void);		/* 17 */
extern void c_unite_alignments(void);			/* 18 */
extern void c_var_param_alignment(void);		/* 19 */
extern void c_bfvar_bits(void);				/* 20 */
extern void c_false(void);				/* 21 */
extern void c_true(void);				/* 22 */
extern void c_nil_access(void);				/* 23 */
extern void c_overflow(void);				/* 24 */
extern void c_stack_overflow(void);			/* 25 */
extern void c_continue(void);				/* 26 */
extern void c_trap(void);				/* 27 */
extern void c_wrap(void);				/* 28 */
extern void c_impossible(void);				/* 29 */
extern void c_abs(void);				/* 30 */
extern void c_add_to_ptr(void);				/* 31 */
extern void c_and(void);				/* 32 */
extern void c_assign(void);				/* 33 */
extern void c_assign_with_mode(void);			/* 34 */
extern void c_bitfield_assign(void);			/* 35 */
extern void c_bitfield_assign_with_mode(void);		/* 36 */
extern void c_bitfield_contents(void);			/* 37 */
extern void c_bitfield_contents_with_mode(void);	/* 38 */
extern void c_change_bitfield_to_int(void);		/* 39 */
extern void c_change_floating_variety(void);		/* 40 */
extern void c_change_variety(void);			/* 41 */
extern void c_change_int_to_bitfield(void);		/* 42 */
extern void c_complex_conjugate(void);			/* 43 */
extern void c_component(void);				/* 44 */
extern void c_concat_nof(void);				/* 45 */
extern void c_conditional(void);			/* 46 */
extern void c_contents(void);				/* 47 */
extern void c_contents_with_mode(void);			/* 48 */
extern void c_current_env(void);			/* 49 */
extern void c_div0(void);				/* 50 */
extern void c_div1(void);				/* 51 */
extern void c_div2(void);				/* 52 */
extern void c_env_offset(void);				/* 53 */
extern void c_env_size(void);				/* 54 */
extern void c_fail_installer(void);			/* 55 */
extern void c_float_int(void);				/* 56 */
extern void c_floating_abs(void);			/* 57 */
extern void c_floating_div(void);			/* 58 */
extern void c_floating_minus(void);			/* 59 */
extern void c_floating_maximum(void);			/* 60 */
extern void c_floating_minimum(void);			/* 61 */
extern void c_floating_mult(void);			/* 62 */
extern void c_floating_negate(void);			/* 63 */
extern void c_floating_plus(void);			/* 64 */
extern void c_floating_power(void);			/* 65 */
extern void c_floating_test(void);			/* 66 */
extern void c_goto(void);				/* 67 */
extern void c_goto_local_lv(void);			/* 68 */
extern void c_ignorable(void);				/* 69 */
extern void c_imaginary_part(void);			/* 70 */
extern void c_initial_value(void);			/* 71 */
extern void c_integer_test(void);			/* 72 */
extern void c_last_local(void);				/* 73 */
extern void c_local_alloc(void);			/* 74 */
extern void c_local_alloc_check(void);			/* 75 */
extern void c_local_free(void);				/* 76 */
extern void c_local_free_all(void);			/* 77 */
extern void c_long_jump(void);				/* 78 */
extern void c_make_complex(void);			/* 79 */
extern void c_make_compound(void);			/* 80 */
extern void c_make_local_lv(void);			/* 81 */
extern void c_make_nof(void);				/* 82 */
extern void c_make_nof_int(void);			/* 83 */
extern void c_make_null_local_lv(void);			/* 84 */
extern void c_make_null_proc(void);			/* 85 */
extern void c_make_null_ptr(void);			/* 86 */
extern void c_make_stack_limit(void);			/* 87 */
extern void c_make_top(void);				/* 88 */
extern void c_make_value(void);				/* 89 */
extern void c_maximum(void);				/* 90 */
extern void c_minimum(void);				/* 91 */
extern void c_minus(void);				/* 92 */
extern void c_move_some(void);				/* 93 */
extern void c_mult(void);				/* 94 */
extern void c_n_copies(void);				/* 95 */
extern void c_negate(void);				/* 96 */
extern void c_not(void);				/* 97 */
extern void c_offset_add(void);				/* 98 */
extern void c_offset_div(void);				/* 99 */
extern void c_offset_div_by_int(void);			/* 100 */
extern void c_offset_max(void);				/* 101 */
extern void c_offset_mult(void);			/* 102 */
extern void c_offset_negate(void);			/* 103 */
extern void c_offset_pad(void);				/* 104 */
extern void c_offset_subtract(void);			/* 105 */
extern void c_offset_test(void);			/* 106 */
extern void c_offset_zero(void);			/* 107 */
extern void c_or(void);					/* 108 */
extern void c_plus(void);				/* 109 */
extern void c_pointer_test(void);			/* 110 */
extern void c_power(void);				/* 111 */
extern void c_proc_test(void);				/* 112 */
extern void c_profile(void);				/* 113 */
extern void c_real_part(void);				/* 114 */
extern void c_rem0(void);				/* 115 */
extern void c_rem1(void);				/* 116 */
extern void c_rem2(void);				/* 117 */
extern void c_repeat(void);				/* 118 */
extern void c_return(void);				/* 119 */
extern void c_return_to_label(void);			/* 120 */
extern void c_round_with_mode(void);			/* 121 */
extern void c_rotate_left(void);			/* 122 */
extern void c_rotate_right(void);			/* 123 */
extern void c_set_stack_limit(void);			/* 124 */
extern void c_shape_offset(void);			/* 125 */
extern void c_shift_left(void);				/* 126 */
extern void c_shift_right(void);			/* 127 */
extern void c_subtract_ptrs(void);			/* 128 */
extern void c_untidy_return(void);			/* 129 */
extern void c_xor(void);				/* 130 */
extern void c_flvar_parms(void);			/* 131 */
extern void c_complex_parms(void);			/* 132 */
extern void c_float_of_complex(void);			/* 133 */
extern void c_complex_of_float(void);			/* 134 */
extern void c_computed_nat(void);			/* 135 */
extern void c_error_val(void);				/* 136 */
extern void c_equal(void);				/* 137 */
extern void c_greater_than(void);			/* 138 */
extern void c_greater_than_or_equal(void);		/* 139 */
extern void c_less_than(void);				/* 140 */
extern void c_less_than_or_equal(void);			/* 141 */
extern void c_not_equal(void);				/* 142 */
extern void c_not_greater_than(void);			/* 143 */
extern void c_not_greater_than_or_equal(void);		/* 144 */
extern void c_not_less_than(void);			/* 145 */
extern void c_not_less_than_or_equal(void);		/* 146 */
extern void c_less_than_or_greater_than(void);		/* 147 */
extern void c_not_less_than_and_not_greater_than(void);	/* 148 */
extern void c_comparable(void);				/* 149 */
extern void c_not_comparable(void);			/* 150 */
extern void c_round_as_state(void);			/* 151 */
extern void c_to_nearest(void);				/* 152 */
extern void c_toward_larger(void);			/* 153 */
extern void c_toward_smaller(void);			/* 154 */
extern void c_toward_zero(void);			/* 155 */
extern void c_bitfield(void);				/* 156 */
extern void c_bottom(void);				/* 157 */
extern void c_compound(void);				/* 158 */
extern void c_floating(void);				/* 159 */
extern void c_integer(void);				/* 160 */
extern void c_nof(void);				/* 161 */
extern void c_offset(void);				/* 162 */
extern void c_pointer(void);				/* 163 */
extern void c_proc(void);				/* 164 */
extern void c_top(void);				/* 165 */
extern void c_computed_signed_nat(void);		/* 166 */
extern void c_make_signed_nat(void);			/* 167 */
extern void c_snat_from_nat(void);			/* 168 */
extern void c_add_modes(void);				/* 169 */
extern void c_overlap(void);				/* 170 */
extern void c_standard_transfer_mode(void);		/* 171 */
extern void c_trap_on_nil(void);			/* 172 */
extern void c_volatile(void);				/* 173 */
extern void c_complete(void);				/* 174 */
extern void c_var_limits(void);				/* 175 */
extern void c_var_width(void);				/* 176 */

#define no_of_cons					177


#endif