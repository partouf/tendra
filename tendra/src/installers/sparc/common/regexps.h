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




/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/regexps.h,v 1.2 1998/03/15 16:00:46 pwe Exp $
--------------------------------------------------------------------------
$Log: regexps.h,v $
 * Revision 1.2  1998/03/15  16:00:46  pwe
 * regtrack dwarf dagnostics added
 *
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/13  10:18:54  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:37  djch
 * Initial revision
 *
 * Revision 1.1  93/06/24  14:59:16  14:59:16  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef REGEXPS_INCLUDED
#define REGEXPS_INCLUDED

#include "exptypes.h"

typedef struct {
    ans inans ;
    exp keptexp ;
    bool iscont ;
} regpeep ;

extern regpeep regexps [];

extern ans iskept PROTO_S ( ( exp ) ) ;
extern bool couldbe PROTO_S ( ( exp, exp ) ) ;
extern bool couldeffect PROTO_S ( ( exp, exp ) ) ;
extern bool dependson PROTO_S ( ( exp, bool, exp ) ) ;
extern bool eq_sze PROTO_S ( ( shape, shape ) ) ;
extern bool sim_exp PROTO_S ( ( exp, exp ) ) ;
extern bool sim_explist PROTO_S ( ( exp, exp ) ) ;
extern void clear_all PROTO_S ( ( void ) ) ;
extern void clear_dep_reg PROTO_S ( ( exp ) ) ;
extern void clear_reg PROTO_S ( ( int ) ) ;
extern void keepcont PROTO_S ( ( exp, int ) ) ;
extern void keepexp PROTO_S ( ( exp, ans ) ) ;
extern void keepreg PROTO_S ( ( exp, int ) ) ;

#define clear_freg( R ) clear_reg ( ( ( R ) >> 1 ) + 32 )

#endif /* REGEXPS_INCLUDED */
