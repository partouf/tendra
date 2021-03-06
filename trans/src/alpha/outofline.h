/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
  Data structure for take_out_of_line procedure
*/
#ifndef OUTOFLINE
#define OUTOFLINE 1

#include <local/ash.h>

#include <reader/exp.h>

#include "addr.h"

typedef struct outofline_t {
  struct outofline_t * next;
  where dest;
  ash stack;
  exp body;
  int regsinuse;
  exp jr;
  int fstack_pos;
  int labno;
  bool cond1_set;
  bool cond2_set;
  where cond1;
  where cond2a;
  where cond2b;
  int repeat_level;
  float scale;
  space sp;
} outofline;

#endif
