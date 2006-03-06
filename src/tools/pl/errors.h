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


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:57:24 $
$Revision: 1.1.1.1 $
$Log: errors.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:24  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.2  1994/07/21  10:36:10  currie
 * Added banner
 *
***********************************************************************/
#ifndef ERRORS_INCLUDED
#define ERRORS_INCLUDED


extern void fail PROTO_W((char *, ...));
extern void assert_sort PROTO_S((unsigned int));
extern void assert_sort_or_empty PROTO_S((unsigned int));


/* These macros can be given empty bodies if required;
   Better make sure your SORTs are right first!
*/

#define SET_RSORT(x) current_TDF->sort = x
#define ASSERT_SORT(x) assert_sort((unsigned int)x)
#define ASSERT_SORT_OR_EMPTY(x) assert_sort_or_empty((unsigned int)x)

#if FS_STDC_HASH
#define Assert(x) if (!(x)) {fail("Assertion %s failed", #x);}
#else
#define Assert(x) if (!(x)) {fail("Assertion %s failed", "x");}
#endif


#endif