/* $Id$ */

/*
 * Copyright 2002-2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef UTILITY_BITS_H
#define UTILITY_BITS_H

typedef unsigned long bitpattern;

extern int lsmask[33];
extern int msmask[33];

/*
 * Count the bits set.
 */
int
bits_in(bitpattern);

/*
 * Find the first non-zero bit
 *
 * Returns the bit number of the least significant set bit.
 * For 0 it returns -1.
 */
int
bit_one(bitpattern);

#endif

