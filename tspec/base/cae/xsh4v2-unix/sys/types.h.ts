# Copyright 2002-2014, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

+IMPLEMENT "cae/xsh4-base", "sys/types.h.ts" ;

+SUBSET "id_t" := {
	+TYPE ( arith ) id_t ;
} ;

+SUBSET "useconds_t" := {
	+TYPE ( unsigned ) useconds_t ;
} ;

