#
# Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#
#   		 Crown Copyright (c) 1997
#   
#   This TenDRA(r) Computer Program is subject to Copyright
#   owned by the United Kingdom Secretary of State for Defence
#   acting through the Defence Evaluation and Research Agency
#   (DERA).  It is made available to Recipients with a
#   royalty-free licence for its use, reproduction, transfer
#   to other parties and amendment for any purpose not excluding
#   product development provided that any such use et cetera
#   shall be deemed to be acceptance of the following conditions:-
#   
#       (1) Its Recipients shall ensure that this Notice is
#       reproduced upon any copies or amended versions of it;
#   
#       (2) Any amended version of it shall be clearly marked to
#       show both the nature of and the organisation responsible
#       for the relevant amendment or amendments;
#   
#       (3) Its onward transfer from a recipient to another
#       party shall be deemed to be that party's acceptance of
#       these conditions;
#   
#       (4) DERA gives no warranty or assurance as to its
#       quality or suitability for any purpose and DERA accepts
#       no liability whatsoever in relation to any use to which
#       it may be put.
#
# $Id$
#

+IFNDEF __JUST_POSIX

+SUBSET "va_args" := {
    +SUBSET "va_list" := {
	# This is a hack to hide va_list
	+IFNDEF ~building_libs
	+TYPE ~va_list.1 | va_list.1 ;
	+ELSE
	+TYPE va_list.2 | va_list.2 ;
	+TYPEDEF va_list ~va_list.2 ;
	+ENDIF
    } ;

    %% #pragma TenDRA ident ... allow %%

    +IFNDEF ~building_libs
    +TYPEDEF ~va_list va_list ;
    +ENDIF

    +TYPE __va_t | "~__va_t"  ;
    +MACRO va_list __va_start ( __va_t ) ;

    +TOKEN va_arg # This is tricky
    %% PROC ( EXP lvalue : va_list : e , TYPE t ) EXP rvalue : t : %% ;

    +MACRO void va_end ( lvalue va_list ) ;

%%%
#include <stdarg.h>
#ifndef __COMPLEX_VA_LIST
typedef va_list __va_t ;
#define __va_start( X ) ( ( va_list ) ( X ) )
#endif
%%%

} ;

+DEFINE va_start ( l, i )  %% ( ( void ) ( l = __va_start ( ... ) ) ) %% ;

+ENDIF

# vim:set filetype=tspec: