/****************************************************************
*
*  shell.h - ORCA/M Shell Interface File
*
*  Copyright Apple Computer and Megamax Inc.  1986, 1987
*  All rights reserved
*
*  Copyright 1989, 1990, 1992 Byte Works, Inc.
*
****************************************************************/

#ifndef __shell__
#define __shell__

/* CHANGE_VECTOR parameter block */
typedef struct {
   int reserved;
   int vector;                          /* vector number */
   void *procPtr;                       /* new vector handler */
   void *oldprocPtr;                    /* old vector handler */
   } Change_VectorPB;

typedef struct {
   int pCount;                          /* parameter count */
   int reserved;
   int vector;                          /* vector number */
   void *procPtr;                       /* new vector handler */
   void *oldprocPtr;                    /* old vector handler */
   } ChangeVectorGSPB;
   
/* WRITE_CONSOLE parameter block */
typedef struct {
   int ch;                              /* character to write */
   } Write_ConsolePB;

typedef struct {
   int pCount;                          /* parameter count */
   int ch;                              /* character to write */
   } ConsoleOutGSPB;

/* DIRECTION parameter block */
typedef struct {
   int device;                          /* device number */
   int direct;                          /* type of redirection */
   } DirectionPB;

typedef struct {
   int pCount;                          /* parameter count */
   int device;                          /* device number */
   int direct;                          /* type of redirection */
   } DirectionGSPB;

/* ERROR parameter block */
typedef struct {
   int error;                           /* error number */
   } ErrorPB;

typedef struct {
   int pCount;                          /* parameter count */
   int error;                           /* error number */
   } ErrorGSPB;

/* EXECUTE parameter block */
typedef struct {
   int flag;                            /* options flags */
   char *comm;                          /* command string */
   } ExecutePB;

typedef struct {
   int pCount;                          /* parameter count */
   int flag;                            /* options flags */
   char *comm;                          /* command string */
   } ExecuteGSPB;

/* EXPAND_DEVICES parameter block */
typedef struct {
   char *pathname;                      /* path name */
   } Expand_DevicesPB;

typedef struct {
   int pCount;                          /* parameter count */
   void *inName;                        /* input path name */
   void *outName;                       /* output path name */
   } ExpandDevicesGSPB;

/* EXPORT parameter block */
typedef struct {
   char *name;                          /* variable name */
   int flags;                           /* export flag */
   } ExportPB;

typedef struct {
   int pCount;                          /* parameter count */
   char *name;                          /* variable name */
   int flags;                           /* export flag */
   } ExportGSPB;

/* FASTFILE parameter block */
typedef struct {
   int action;                          /* action to take */
   int index;                           /* file index */
   int flags;                           /* FastFile options flags */
   void *file_handle;                   /* handle of RAM copy of file */
   long file_length;                    /* length of the file */
   char *pathname;                      /* file's pathname */
   int access;                          /* access */
   int file_type;                       /* file type */
   long aux_type;                       /* auxiliary type */
   int storage;                         /* storage flags */
   int create_date;                     /* creation */
   int create_time;
   int mod_date;                        /* last modification */
   int mod_time;
   long blocks_used;                    /* blocks used on disk */
   } FastFilePB;

typedef struct {
   int pCount;                          /* parameter count */
   int action;                          /* action to take */
   int index;                           /* file index */
   int flags;                           /* FastFile options flags */
   void *fileHandle;                    /* handle of RAM copy of file */
   void *pathName;                      /* file's pathname */
   int access;                          /* access */
   int fileType;                        /* file type */
   long auxType;                        /* auxiliary type */
   int storageType;                     /* storage flags */
   char createDate[8];                  /* creation */
   char modDate[8];                     /* last modification */
   void *option;                        /* option list */
   long fileLength;                     /* length of the file */
   long blocksUsed;                     /* blocks used on disk */
   } FastFileGSPB;

/* GET_COMMAND parameter block */
typedef struct {
   int index;                           /* command number */
   int restart;                         /* restartable? */
   int reserved;
   int command;                         /* command number */
   char name[16];                       /* command name (p-string) */
   } Get_CommandPB;

typedef struct {
   int pCount;                          /* parameter count */
   int index;                           /* command number */
   int restart;                         /* restartable? */
   int reserved;
   int command;                         /* command number */
   char name[16];                       /* command name (p-string) */
   } GetCommandGSPB;

/* GET_IODEVICES SET_IODEVICES parameter block */
typedef struct {
   int output_type;                     /* output device type */
   long output_addr;                    /* output device slot/addr */
   int error_type;                      /* error device type */
   long error_addr;                     /* error device slot/addr */
   int input_type;                      /* input device type */
   long input_addr;                     /* input device slot/addr */
   } Get_IODevicesPB, Set_IODevicesPB;

/* GET_LANG SET_LANG parameter block */
typedef struct {
   int lang;                            /* language number */
   } Get_LangPB, Set_LangPB;

typedef struct {
   int pCount;                          /* parameter count */
   int lang;                            /* language number */
   } GetLangGSPB, SetLangGSPB;

/* GET_LINFO SET_LINFO parameter block */
typedef struct {
   char *sfile;                         /* address of source file name */
   char *dfile;                         /* address of output file name */
   char *parms;                         /* address of paramter list */
   char *istring;                       /* address of language specific input string */
   char merr;                           /* max error level allowed */
   char merrf;                          /* max error level found */
   char lops;                           /* operations flag */
   char kflag;                          /* KEEP flag */
   unsigned long mflags;                /* set of letters selected with '-' */
   unsigned long pflags;                /* set of letters selected with '+' */
   unsigned long org;                   /* abs start address of non-relloc load file */
} GetLInfoPB, Get_LInfoPB, Set_LInfoPB;

typedef struct {
   int pCount;                          /* parameter count */
   void *sFile;                         /* address of source file name */
   void *dFile;                         /* address of output file name */
   void *parms;                         /* address of paramter list */
   void *iString;                       /* address of language specific input string */
   char merr;                           /* max error level allowed */
   char merrf;                          /* max error level found */
   char lops;                           /* operations flag */
   char kflag;                          /* KEEP flag */
   unsigned long mFlags;                /* set of letters selected with '-' */
   unsigned long pFlags;                /* set of letters selected with '+' */
   unsigned long org;                   /* abs start address of non-relloc load file */
} GetLInfoGSPB, SetLInfoGSPB;

/* GET_VAR SET_VAR parameter block */
typedef struct {
   char *var_name;                      /* variable name */
   char *value;                         /* variable value */
   } Get_VarPB, Set_VarPB;

typedef struct {
   int pCount;                          /* parameter count */
   void *name;                          /* variable name */
   void *value;                         /* variable value */
   int export;                          /* export flag */
   } ReadVariableGSPB, SetGSPB;

/* KeyPress parameter block */
typedef struct {
   int key;                             /* key read */
   int modifiers;                       /* key modifiers */
   int available;                       /* key available flag */
   } KeyPressPB;

typedef struct {
   int pCount;                          /* parameter count */
   int key;                             /* key read */
   int modifiers;                       /* key modifiers */
   int available;                       /* key available flag */
   } KeyPressGSPB;

/* INIT_WILDCARD parameter block */
typedef struct {
   char *w_file;                        /* file name */
   int flags;                           /* options flags */
   } Init_WildcardPB;

typedef struct {
   int pCount;                          /* parameter count */
   void *wFile;                         /* file name */
   int flags;                           /* options flags */
   } Init_WildcardGSPB;

/* NEXT_WILDCARD parameter block */
typedef struct {
   char *nextfile;                      /* file name */
   } Next_WildcardPB;

typedef struct {
   int pCount;                          /* parameter count */
   void *pathName;                      /* file's pathname */
   int access;                          /* access */
   int fileType;                        /* file type */
   long auxType;                        /* auxiliary type */
   int storageType;                     /* storage flags */
   char createDate[8];                  /* creation */
   char modDate[8];                     /* last modification */
   void *option;                        /* option list */
   long eof;                            /* end of file */
   long blocksUsed;                     /* blocks used on disk */
   long resourceeof;                    /* eof for resource fork */
   long resourceBlocks;                 /* blocksUsed for resource fork */
   } NextWildcardGSPB;
   
/* POP_VARIABLES */
typedef struct {
   int pCount;                          /* parameter count */
   } PopVariablesGSPB;

/* PUSH_VARIABLES */
typedef struct {
   int pCount;                          /* parameter count */
   } PushVariablesGSPB;

/* READ_INDEXED parameter block */
typedef struct {
   char *var_name;                      /* variable name */
   char *value;                         /* variable value */
   int index;                           /* variable index */
   } Read_IndexedPB;

typedef struct {
   int pCount;                          /* parameter count */
   void *name;                          /* variable name */
   void *value;                         /* variable value */
   int index;                           /* variable index */
   int export;                          /* export flag */
   } ReadIndexedGSPB;

/* ReadKey parameter block */
typedef struct {
   int key;                             /* key read */
   int modifiers;                       /* key modifiers */
   } ReadKeyPB;

typedef struct {
   int pCount;                          /* parameter count */
   int key;                             /* key read */
   int modifiers;                       /* key modifiers */
   } ReadKeyGSPB;

/* REDIRECT parameter block */
typedef struct {
   int device;                          /* device number */
   int append;                          /* append? (or replace) */
   char *file;                          /* file to redirect to */
   } RedirectPB;

typedef struct {
   int pCount;                          /* parameter count */
   int device;                          /* device number */
   int append;                          /* append? (or replace) */
   void *file;                          /* file to redirect to */
   } RedirectGSPB;

/* SET_STOP_FLAG STOP parameter block */
typedef struct {
   int stop;                            /* stop flag */
   } Set_Stop_FlagPB, StopPB;

typedef struct {
   int pCount;                          /* parameter count */
   int flag;                            /* stop flag */
   } SetStopFlagGSPB, StopGSPB;

/* UNSET_VARIABLE parameter block */
typedef struct {
   char *name;                          /* variable name */
   } Unset_VariablePB;

typedef struct {
   int pCount;                          /* parameter count */
   void *name;                          /* variable name */
   } UnsetVariableGSPB;

/* VERSION parameter block */
typedef struct {
   char version[4];                     /* shell version number */
   } VersionPB;

typedef struct {
   int pCount;                          /* parameter count */
   char version[4];                     /* shell version number */
   } VersionGSPB;


extern void __call_gsos(void *, unsigned) [[pascal, inline(0xE100B0)]];


#define CHANGE_VECTOR(parm)     __call_gsos(parm,0x010C)
#define DIRECTION(parm)         __call_gsos(parm,0x010F)
#define ERROR(parm)             __call_gsos(parm,0x0105)
#define EXECUTE(parm)           __call_gsos(parm,0x010D)
#define EXPAND_DEVICES(parm)    __call_gsos(parm,0x0114)
#define EXPORT(parm)            __call_gsos(parm,0x0116)
#define FASTFILE(parm)          __call_gsos(parm,0x010E)
#define GET_COMMAND(parm)       __call_gsos(parm,0x011D)
#define GET_IODEVICES(parm)     __call_gsos(parm,0x011C)
#define GET_LANG(parm)          __call_gsos(parm,0x0103)
#define GET_LINFO(parm)         __call_gsos(parm,0x0101)
#define GET_VAR(parm)           __call_gsos(parm,0x010B)
#define INIT_WILDCARD(parm)     __call_gsos(parm,0x0109)
#define KEYPRESS(parm)          __call_gsos(parm,0x011E)
#define NEXT_WILDCARD(parm)     __call_gsos(parm,0x010A)
#define POP_VARIABLES(parm)     __call_gsos(parm,0x0117)
#define PUSH_VARIABLES(parm)    __call_gsos(parm,0x0118)
#define READ_INDEXED(parm)      __call_gsos(parm,0x0108)
#define READKEY(parm)           __call_gsos(parm,0x011F)
#define REDIRECT(parm)          __call_gsos(parm,0x0110)
#define SET_IODEVICES(parm)     __call_gsos(parm,0x011B)
#define SET_LANG(parm)          __call_gsos(parm,0x0104)
#define SET_LINFO(parm)         __call_gsos(parm,0x0102)
#define SET_STOP_FLAG(parm)     __call_gsos(parm,0x0119)
#define SET_VAR(parm)           __call_gsos(parm,0x0106)
#define STOP(parm)              __call_gsos(parm,0x0113)
#define UNSET_VARIABLE(parm)    __call_gsos(parm,0x0115)
#define VERSION(parm)           __call_gsos(parm,0x0107)
#define WRITE_CONSOLE(parm)     __call_gsos(parm,0x011A)

#define ChangeVectorGS(parm)    __call_gsos(parm,0x014C)
#define ConsoleOutGS(parm)      __call_gsos(parm,0x015A)
#define DirectionGS(parm)       __call_gsos(parm,0x014F)
#define ErrorGS(parm)           __call_gsos(parm,0x0145)
#define ExecuteGS(parm)         __call_gsos(parm,0x014D)
#define ExpandDevicesGS(parm)   __call_gsos(parm,0x0154)
#define ExportGS(parm)          __call_gsos(parm,0x0156)
#define FastFileGS(parm)        __call_gsos(parm,0x014E)
#define GetCommandGS(parm)      __call_gsos(parm,0x015D)
#define GetLangGS(parm)         __call_gsos(parm,0x0143)
#define GetLInfoGS(parm)        __call_gsos(parm,0x0141)
#define InitWildcardGS(parm)    __call_gsos(parm,0x0149)
#define KeyPressGS(parm)        __call_gsos(parm,0x015E)
#define NextWildcardGS(parm)    __call_gsos(parm,0x014A)
#define PopVariablesGS(parm)    __call_gsos(parm,0x0157)
#define PushVariablesGS(parm)   __call_gsos(parm,0x0158)
#define ReadIndexedGS(parm)     __call_gsos(parm,0x0148)
#define ReadKeyGS(parm)         __call_gsos(parm,0x015F)
#define ReadVariableGS(parm)    __call_gsos(parm,0x014B)
#define RedirectGS(parm)        __call_gsos(parm,0x0150)
#define SetGS(parm)             __call_gsos(parm,0x0146)
#define SetLangGS(parm)         __call_gsos(parm,0x0144)
#define SetLInfoGS(parm)        __call_gsos(parm,0x0142)
#define SetStopFlagGS(parm)     __call_gsos(parm,0x0159)
#define StopGS(parm)            __call_gsos(parm,0x0153)
#define UnsetVariableGS(parm)   __call_gsos(parm,0x0155)
#define VersionGS(parm)         __call_gsos(parm,0x0147)

#endif
