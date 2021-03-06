/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef TABLE_FNS_H
#define TABLE_FNS_H

#include <reader/exp.h>

#include <reader/token.h>

/* find the exp which is labelled by l */
exp get_lab(label l);

/* set the exp which is labelled by l */
void set_lab(label l, exp e);

/* find the exp known as tag */
exp get_tag(tag tag);

/* set the exp known as tag */
void set_tag(tag tag, exp e);

/* find the tag declaration indexed by tag */
dec *get_dec(int tag);

/* find the alignment tag value indexed by tag */
aldef *get_aldef(int tag);

/* find the token declaration indexed by tag */
tok_define *get_tok(int tk);

/* apply tk to its parameters in pars, and return the result */
tokval apply_tok(token tk, bitstream pars, int sortcode, tokval *actual_pars);

#endif /* TABLE_FNS_H */
