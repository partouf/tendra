/*
    COPYRIGHT NOTICE

    This program is the proprietary property of IXI Ltd, a subsidiary
    of the Santa Cruz Operation (SCO). Use, reproduction, production
    of amended versions and/or transfer of this program is permitted
    PROVIDED THAT:

    (a)  This legend be preserved on any such reproduction and amended
         version.

    (b)  Any recipient of such reproduction or amended version accept
         the conditions set out in this legend.

    IXI accepts no liability whatsoever in relation to any use to
    which this program may be put and gives no warranty as to the
    program's suitability for any purpose.

    All rights reserved.

    Copyright (c) 1995, 1996

*/



/* SCO CID (IXI) $ID$ */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/XmP.h";

+CONST char MATCH_CHAR;

+CONST String XMBINDDIR;
+CONST String XMBINDDIR_FALLBACK;
+CONST String XMBINDFILE;
+CONST String MOTIFBIND;

+DEFINE _XmOSProcessUnmappedCharsetAndText(tag, ctext, sep, outc, outl, prev) %% processCharsetAndText(XmFONTLIST_DEFAULT_TAG, ctext, sep, outc, outl, prev) %% ;

+FUNC String _XmOSFindPatternPart(String);
+FUNC void _XmOSQualifyFileSpec(String, String, String *, String *);
+FUNC void _XmOSGetDirEntries(String, String, unsigned char, Boolean, Boolean, String **, unsigned int *, unsigned int *);
+FUNC void _XmOSBuildFileList(String, String, unsigned char, String **, unsigned int *, unsigned int *);
+FUNC int _XmOSFileCompare(const void *, const void *);
+FUNC String _XmOSGetHomeDirName(void);
+FUNC String _XmOSInitPath(String, String, Boolean *);
+FUNC void _XmSleep(unsigned int);
+FUNC int _XmMicroSleep(long);
+FUNC String _XmOSSetLocale(String);
+FUNC XmString _XmOSGetLocalizedString(char *, Widget, char *, String);
+FUNC String _XmOSBuildFileName(String, String);
+FUNC int _XmOSPutenv(char *);

