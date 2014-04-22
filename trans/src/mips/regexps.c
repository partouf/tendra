/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* regexps.c

For trivial 'peephole' optimisations

*/

#include <stddef.h>

#include <reader/basicread.h>

#include <construct/tags.h>
#include <construct/shapemacs.h>

#include "exptypes.h"
#include "expmacs.h"
#include "addrtypes.h"
#include "move.h"
#include "bitsmacs.h"
#include "maxminmacs.h"
#include "extratags.h"
#include "regexps.h"

regpeep regexps[48];		/* [0:31] fix pt - [32:47] floating pt */

bool sim_exp(exp a, exp b);

bool eq_sze
(shape as, shape bs)
{
  if (is_floating(name(as))) return name(as) ==name(bs);
  if (is_floating(name(bs))) return 0;
  return shape_size(as) == shape_size(bs) && shape_align(as) ==shape_align(bs);
}

bool sim_explist
(exp al, exp bl)
{
  if (al == nilexp && bl == nilexp)
    return 1;
  if (al == nilexp || bl == nilexp)
    return 0;
  if (!sim_exp(al, bl))
    return 0;
  if (last(al) && last(bl))
    return 1;
  if (last(al) || last(bl))
    return 0;
  return sim_explist(bro(al), bro(bl));
}

bool sim_exp
(exp a, exp b)
{	/* basically eq_exp except equal shapes
				   requirement  is weakened to equal sizes
				   and alignments */
  if (name(a) == name(b)) {
    if (name(a) == name_tag)
      return son(a) == son(b) && no(a) == no(b) &&
	  eq_sze(sh(a), sh(b));
    if (name(a) ==maxlike_tag || name(a) ==minlike_tag || name(a) ==abslike_tag) {
    	return props(son(a)) ==props(son(b)) &&
		shape_size(sh(a)) ==shape_size(sh(b)) &&
    			sim_explist(son(son(a)),son(son(b)));
    }
    if (!is_a(name(a)) || !eq_sze(sh(a), sh(b)))
      return 0;
    if (name(a) == float_tag) return eq_exp(son(a), son(b));
    return no(a) == no(b) &&
	sim_explist(son(a), son(b));
  };
  return 0;
}

void clear_all
(void)
{	/* forget all register - exp associations */
  int   i;
  for (i = 0; i < 48; i++) {
    regexps[i].keptexp = nilexp;
    setregalt(regexps[i].inans, 0);
  }
}


void clear_reg
(int i)
{	/* forget reg i - exp association */
  i = abs(i);
  if (i >= 0 && i < 48) {
    regexps[i].keptexp = nilexp;
    setregalt(regexps[i].inans, 0);
  }
}


ans iskept
(exp e)
{		/* find if e has already been evaluated
				   into a register */
  int   i;
  ans nilans;
  ans aa;
  setregalt(nilans, 0);
  aa = nilans;
  for (i = 0; i < 48; i++) {
    exp ke = regexps[i].keptexp;
    bool isc = regexps[i].iscont;
    if (ke != nilexp) {		/* there is an accociation with reg i */
      if (
	 ((!isc && sim_exp(ke, e)) ||
	   (name(e) == cont_tag && isc  &&
	      eq_sze(sh(ke), sh(e))
	      && sim_exp(ke, son(e)) && al1(sh(son(e))) == al1(sh(ke)))
	 )
	) {
	aa = (regexps[i].inans);
	switch (aa.discrim) {
	  case notinreg:
	    {
	      if (!aa.val.instoreans.adval) {
				/* the expression is given indirectly - it
				   may have also been loaded into a
				   register */
		continue;
	      }
	      /* else ... */
	    }
	  default:
	    return aa;
	}
      }
      else
	if (name(ke) == cont_tag && !isc) {
	  ans aq;
	  aq = regexps[i].inans;
	  if (aq.discrim == notinreg) {
	    instore is;
	    is = insalt(aq);
	    if (!is.adval && is.b.offset == 0 && is.b.base > 0 && is.b.base < 31
		&& sim_exp(son(ke), e)) {
				/* the contents of req expression is here
				   as a reg-offset */
	      is.adval = 1;
	      setinsalt(aq, is);
	      return aq;
	    }
	  }
	}
	else
	  if (name(ke) == reff_tag && !isc) {
	    ans aq;
	    aq = regexps[i].inans;
	    if (aq.discrim == notinreg) {
	      instore is;
	      is = insalt(aq);
	      if (is.adval && is.b.offset == (no(ke) / 8)
		  && is.b.base > 0 && is.b.base < 31
		  && sim_exp(son(ke), e)) {
				/* a ref select of req expression is here
				   as a reg-offset */
		is.adval = 1;
		is.b.offset = 0;
		setinsalt(aq, is);
		return aq;
	      }
	    }
	  }
    }
  }
  return aa;
}

void keepexp
(exp e, ans loc)
{	/* set up exp - address association */
  int   pos;
  switch (loc.discrim) {
    case insomereg:
    case insomefreg: {
	failer("Keep ? reg");
      }
    case inreg:
      {
	pos = regalt(loc);
	break;
      }
    case infreg:
      {
	pos = fregalt(loc).fr + 32;
	break;
      }
    case notinreg:
      {
	pos = insalt(loc).b.base;
	if (pos < 0 || pos > 30)
	  return;
      }

  };
  if (pos==2 || pos == 32) return;
  regexps[pos].keptexp = e;
  regexps[pos].inans = loc;
  regexps[pos].iscont = 0;
}

void keepcont
(exp e, int reg)
{/* set up cont(e)-reg association */
  freg fr;
  int   z = abs(reg);
  if (z==2|| z==32) return;
  if (z > 31) {
    fr.dble = (reg < 0);
    fr.fr = z - 32;
    setfregalt(regexps[z].inans, fr);
  }
  else {
    instore is;
    is.b.base = reg;
    is.b.offset = 0;
    is.adval = 1;
    setinsalt(regexps[z].inans, is);
  }

  regexps[z].keptexp = e;

  regexps[z].iscont = 1;

}

void keepreg
(exp e, int reg)
{	/* set up e-reg association */
  freg fr;
  int   z = abs(reg);
  if (z==2 || z==32) return;
  if (z > 31) {
    fr.dble = (reg < 0);
    fr.fr = z - 32;
    setfregalt(regexps[z].inans, fr);
  }
  else {
    instore is;
    is.b.base = reg;
    is.b.offset = 0;
    is.adval = 1;
    setinsalt(regexps[z].inans, is);
  }

  regexps[z].keptexp = e;
  regexps[z].iscont = 0;
}

static bool couldeffect(exp e, exp z, int count);

static bool couldbe
(exp e, exp lhs, int count)
{ /* could e be lhs? */
  int   ne = name(e);
  exp s = son(e);

  if (ne == name_tag) {
    if (lhs != 0 && s == son(lhs)) {
	return 1;
    }
    if (isvar(s)) {
      return lhs == 0 && (isvis(s) || isglob(s));
    }
    if (name(s) == proc_tag)
      return lhs == 0;
    if (son(s) == nilexp)
      return 1;
    if (count > 5) return 1; /* pathological */
    return couldbe(son(s), lhs, count+1);
  }
  if (ne == cont_tag) {
    if (lhs != 0 && name(s) == name_tag && son(s)!= nilexp) {
      return son(s) == son(lhs) || isvis(son(lhs)) || isvis(son(s));
    }
    return 1;
  }
  if (ne == reff_tag || ne == field_tag) {
    return couldbe(s, lhs, count);
  }
  if (ne == addptr_tag || ne == subptr_tag) {
    return couldbe(s, lhs, count) || couldeffect(bro(s), lhs, count);
  }

  return 1;

}

static bool couldeffect
(exp e, exp z, int count)
{
				/* could alteration to z effect e? */
  int   ne = name(e);
  if (ne == cont_tag) {
    return couldbe(son(e), z, count);
  }
  if (ne == name_tag) {
    if (isvar(son(e)))
      return z == 0 && isvis(son(e));
    if (name(son(e)) == proc_tag)
      return 0;
    if (son(son(e)) == nilexp)
      return 1 /* could it happen? */ ;
    if (count > 5) return 1; /* pathological */
    return couldeffect(son(son(e)), z, count+1);

  }
  if (ne < plus_tag || ne == contvol_tag)
    return 1;

  e = son(e);

  while (e != nilexp) {
    if (couldeffect(e, z, count))
      return 1;
    if (last(e))
      return 0;
    e = bro(e);
  }
  return 0;
}

bool dependson
(exp e, bool isc, exp z)
{/* does e depend on z */
  if (e == nilexp) {
    return 0;
  }
  for (;;) {
    if (name(z) == reff_tag || name(z) == addptr_tag ||
	name(z) == subptr_tag) {
      z = son(z);
    }

   if (name(z)!= name_tag) {
    if (name(z)!= cont_tag)
      return 1;
    z = 0;
    break;
   }

    if (isvar(son(z)))
      break;
    if (name(son(z)) == proc_tag) {
      z = 0;
      break;
    }
    if (son(son(z)) == nilexp)
      return 1;			/* can it happen? */
    z = son(son(z));
  }

  /* z is now unambiguous variable name or 0 meaning some contents */

  return (isc)? couldbe(e, z, 0): couldeffect(e, z, 0);
}





void clear_dep_reg
(exp lhs)
{	/* remove association of any register
				   which depends on lhs */
  int   i;
  for (i = 0; i < 48; i++) {
    if (dependson(regexps[i].keptexp, regexps[i].iscont, lhs)) {
      regexps[i].keptexp = nilexp;
      setregalt(regexps[i].inans, 0);
    }
  }
}