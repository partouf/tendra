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



/* SCO CID (IXI) MenuShellP.h,v 1.1 1996/08/08 14:13:04 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/MenuShell.h";
+USE "motif/1_2", "Xm/XmP.h";
+USE "x5/t", "X11/ShellP.h";

+FIELD (struct) XmMenuShellPart := {

	unsigned char	focus_policy;
	XmFocusData	focus_data;
	Boolean		private_shell;
	XmFontList	default_font_list;
	XmFontList	button_font_list;
	XmFontList	label_font_list;
};


+FIELD (struct) _XmMenuShellRec := {

	CorePart		core;
	CompositePart		composite;
	ShellPart		shell;
	OverrideShellPart	override;
	XmMenuShellPart		menu_shell;
};

+TYPEDEF _XmMenuShellRec XmMenuShellRec;

/* OBSOLETE for combatability only */
+FIELD (struct) _XmMenuShellWidgetRec := {

	CorePart		core;
	CompositePart		composite;
	ShellPart		shell;
	OverrideShellPart	override;
	XmMenuShellPart		menu_shell;
};

+TYPEDEF _XmMenuShellWidgetRec XmMenuShellWidgetRec;


+FIELD (struct) XmMenuShellClassPart := { 

	XtActionProc		popdownOne;
	XtActionProc		popdownEveryone;
	XtActionProc		popdownDone;
	XmMenuPopupProc		popupSharedMenupane;

	XtPointer		extension;
};


+FIELD (struct) _XmMenuShellClassRec := {

	CoreClassPart		core_class;
	CompositeClassPart	composite_class;
	ShellClassPart		shell_class;
	OverrideShellClassPart	override_shell_class;
	XmMenuShellClassPart	menu_shell_class;
};

+TYPEDEF _XmMenuShellClassRec XmMenuShellClassRec;

+EXP lvalue XmMenuShellClassRec xmMenuShellClassRec;

+MACRO unsigned char MS_FocusPolicy(Widget);

+FUNC void _XmEnterRowColumn(Widget, XtPointer, XEvent *, Boolean *);
+FUNC void _XmClearTraversal(Widget, XEvent *, String *, Cardinal *);
+FUNC void _XmSetLastManagedMenuTime(Widget, Time);




