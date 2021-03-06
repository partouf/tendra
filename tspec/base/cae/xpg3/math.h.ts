# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "c/c89", "math.h.ts" ;

+EXP double MAXFLOAT ;
+CONST double M_1_PI, M_2_PI, M_2_SQRTPI, M_E, M_LN2, M_LN10 ;
+CONST double M_LOG2E, M_LOG10E, M_PI, M_PI_2, M_PI_4, M_SQRT2, M_SQRT1_2 ;

+FUNC double erf ( double ) ;
+FUNC double erfc ( double ) ;
+FUNC double gamma ( double ) ;
+FUNC double hypot ( double, double ) ;
+FUNC int isnan ( double ) ;
+FUNC double j0 ( double ) ;
+FUNC double j1 ( double ) ;
+FUNC double jn ( int, double ) ;
+FUNC double lgamma ( double ) ;
+FUNC double y0 ( double ) ;
+FUNC double y1 ( double ) ;
+FUNC double yn ( int, double ) ;

+EXP (extern) int signgam ;
