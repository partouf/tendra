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


#ifndef QUALITY_INCLUDED
#define QUALITY_INCLUDED


/*
    QUALITY CHECKING DECLARATIONS

    The routines in this module are concerned with quality style checks.
    These include detection of possible precedence errors.
*/

extern void check_logic PROTO_S ( ( EXP, EXP ) ) ;
extern void check_relation PROTO_S ( ( int, EXP, EXP ) ) ;
extern void check_paren PROTO_S ( ( int, int, EXP, EXP ) ) ;
extern int suppress_quality ;


/*
    PARENTHESIS CHECKING VALUES

    These values are used to specify the level of parenthesis checking
    to be applied by check_paren.
*/

#define PAREN_OR			0
#define PAREN_XOR			1
#define PAREN_AND			2
#define PAREN_EQUALITY			3
#define PAREN_RELATION			4
#define PAREN_PLUS			5
#define PAREN_MINUS			6


#endif
