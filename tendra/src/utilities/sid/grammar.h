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


/*** grammar.h --- Grammar transforms frontend.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "grammar.c" for more information.
 *
 *** Change Log:
 * $Log: grammar.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:58:15  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:34  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_GRAMMAR
#define H_GRAMMAR

#include "os-interface.h"
#include "entry.h"
#include "entry-list.h"
#include "ostream.h"
#include "table.h"
#include "types.h"

/*--------------------------------------------------------------------------*/

typedef struct GrammarT {
    TableT			table;
    EntryListT			entry_list;
    unsigned			terminal;
    EntryP			predicate_type;
    EntryP			predicate_id;
} GrammarT, *GrammarP;

/*--------------------------------------------------------------------------*/

extern void			grammar_init
	PROTO_S ((GrammarP));
extern TableP			grammar_table
	PROTO_S ((GrammarP));
extern EntryListP		grammar_entry_list
	PROTO_S ((GrammarP));
extern unsigned			grammar_max_terminal
	PROTO_S ((GrammarP));
extern unsigned			grammar_next_terminal
	PROTO_S ((GrammarP));
extern EntryP			grammar_get_predicate_type
	PROTO_S ((GrammarP));
extern void			grammar_set_predicate_type
	PROTO_S ((GrammarP, EntryP));
extern EntryP			grammar_get_predicate_id
	PROTO_S ((GrammarP));
extern void			grammar_check_complete
	PROTO_S ((GrammarP));
extern void			grammar_remove_left_recursion
	PROTO_S ((GrammarP));
extern void			grammar_compute_first_sets
	PROTO_S ((GrammarP));
extern void			grammar_factor
	PROTO_S ((GrammarP));
extern void			grammar_simplify
	PROTO_S ((GrammarP));
extern void			grammar_compute_inlining
	PROTO_S ((GrammarP));
extern void			grammar_check_collisions
	PROTO_S ((GrammarP));
extern void			grammar_recompute_alt_names
	PROTO_S ((GrammarP));
extern void			grammar_compute_mutations
	PROTO_S ((GrammarP));

extern void			write_grammar
	PROTO_S ((OStreamP, GrammarP));

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#define grammar_table(g) (&((g)->table))
#define grammar_entry_list(g) (&((g)->entry_list))
#define grammar_max_terminal(g) ((g)->terminal)
#define grammar_get_predicate_type(g) ((g)->predicate_type)
#define grammar_set_predicate_type(g, t) ((g)->predicate_type = (t))
#define grammar_get_predicate_id(g) ((g)->predicate_id)
#endif /* defined (FS_FAST) */

#endif /* !defined (H_GRAMMAR) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
