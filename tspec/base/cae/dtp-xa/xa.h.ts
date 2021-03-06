# Copyright 2014, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

+IFNDEF XA_H
+DEFINE XA_H %% %%;

+DEFINE XIDDATASIZE  128;
+DEFINE MAXGTRIDSIZE  64;
+DEFINE MAXBQUALSIZE  64;

+NAT ~xid_data_size; # TODO: can this be related to XIDDATASIZE above?
+FIELD struct xid_t {
	long formatID;
	long gtrid_length;
	long bqual_length;
	char data[~xid_data_size];
};
+TYPEDEF struct xid_t XID;

# +IFDEF __STDC__
	+FUNC int ax_reg(int, XID *, long);
	+FUNC int ax_unreg(int, long);
# +ELSE
#	+FUNC int ax_reg();
#	+FUNC int ax_unreg();
# +ENDIF

+DEFINE RMNAMESZ     32;
+DEFINE MAXINFOSIZE 256;

+NAT ~xa_switch_rmnamesz; # TODO: can this be related to RMNAMESZ above?
+FIELD struct xa_switch_t {
	char name[~xa_switch_rmnamesz];
	long flags;
	long version; # TODO: value must be 0
# +IFDEF __STDC__
	int (*xa_open_entry)(char *, int, long);
	int (*xa_close_entry)(char *, int, long);
	int (*xa_start_entry)(XID *, int, long);
	int (*xa_end_entry)(XID *, int, long);

	int (*xa_rollback_entry)(XID *, int, long);

	int (*xa_prepare_entry)(XID *, int, long);
	int (*xa_commit_entry)(XID *, int, long);
	int (*xa_recover_entry)(XID *, long, int, long);

	int (*xa_forget_entry)(XID *, int, long);
	int (*xa_complete_entry)(int *, int *, int, long);
# +ELSE
#	int (*xa_open_entry)();
#	int (*xa_close_entry)();
#	int (*xa_start_entry)();
#	int (*xa_end_entry)();
#
#	int (*xa_rollback_entry)();
#
#	int (*xa_prepare_entry)();
#	int (*xa_commit_entry)();
#	int (*xa_recover_entry)();
#
#	int (*xa_forget_entry)();
#	int (*xa_complete_entry)();
# +ENDIF
};

+DEFINE TMNOFLAGS    %% 0x00000000L %%;
+DEFINE TMREGISTER   %% 0x00000001L %%;
+DEFINE TMNOMIGRATE  %% 0x00000002L %%;
+DEFINE TMUSEASYNC   %% 0x00000004L %%;

+DEFINE TMASYNC      %% 0x80000000L %%;
+DEFINE TMONEPHASE   %% 0x40000000L %%;
+DEFINE TMFAIL       %% 0x20000000L %%;
+DEFINE TMNOWAIT     %% 0x10000000L %%;
+DEFINE TMRESUME     %% 0x08000000L %%;
+DEFINE TMSUCCESS    %% 0x04000000L %%;
+DEFINE TMSUSPEND    %% 0x02000000L %%;
+DEFINE TMSTARTRSCAN %% 0x01000000L %%;
+DEFINE TMENDRSCAN   %% 0x00800000L %%;
+DEFINE TMMULTIPLE   %% 0x00400000L %%;
+DEFINE TMJOIN       %% 0x00200000L %%;
+DEFINE TMMIGRATE    %% 0x00100000L %%;

+DEFINE TM_JOIN     2;
+DEFINE TM_RESUME   1;
+DEFINE TM_OK       0;
+DEFINE TMER_TMERR -1;
+DEFINE TMER_INVAL -2;
+DEFINE TMER_PROTO -3;

+DEFINE XA_RBBASE      100;
+DEFINE XA_RBROLLBACK  %% XA_RBBASE      %%;
+DEFINE XA_RBCOMMFAIL  %% XA_RBBASE + 1  %%;
+DEFINE XA_RBDEADLOCK  %% XA_RBBASE + 2  %%;
+DEFINE XA_RBINTEGRITY %% XA_RBBASE + 3  %%;
+DEFINE XA_RBOTHER     %% XA_RBBASE + 4  %%;
+DEFINE XA_RBPROTO     %% XA_RBBASE + 5  %%;
+DEFINE XA_RBTIMEOUT   %% XA_RBBASE + 6  %%;
+DEFINE XA_RBTRANSIENT %% XA_RBBASE + 7  %%;
+DEFINE XA_RBEND       %% XA_RBTRANSIENT %%;

+DEFINE XA_NOMIGRATE  9;
+DEFINE XA_HEURHAZ    8;
+DEFINE XA_HEURCOM    7;
+DEFINE XA_HEURRB     6;
+DEFINE XA_HEURMIX    5;
+DEFINE XA_RETRY      4;
+DEFINE XA_RDONLY     3;
+DEFINE XA_OK         0;

+DEFINE XAER_ASYNC   -2;
+DEFINE XAER_RMERR   -3;
+DEFINE XAER_NOTA    -4;
+DEFINE XAER_INVAL   -5;
+DEFINE XAER_PROTO   -6;
+DEFINE XAER_RMFAIL  -7;
+DEFINE XAER_DUPID   -8;
+DEFINE XAER_OUTSIDE -9;

+ENDIF

