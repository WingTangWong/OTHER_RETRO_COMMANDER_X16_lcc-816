/********************************************
; File: Finder.h
;
; Copyright Apple Computer, Inc. 1991-92
; All Rights Reserved
;
********************************************/

#pragma once

#ifndef __TYPES__
#include <types.h>
#endif

#ifndef __QUICKDRAW__
#include <quickdraw.h>
#endif

#ifndef __EVENT__
#include <event.h>
#endif

#ifndef __WINDOW__
#include <window.h>
#endif

#ifndef __FINDER__
#define __FINDER__

/* target name for SendRequest to Finder */
#define NAME_OF_FINDER "\pApple~Finder~"

/* SendRequest codes sent by the Finder */
#define finderSaysHello                 0x0100
#define finderSaysGoodbye               0x0101
#define finderSaysSelectionChanged      0x0102
#define finderSaysMItemSelected         0x0103
#define finderSaysBeforeOpen            0x0104
#define finderSaysOpenFailed            0x0105
#define finderSaysBeforeCopy            0x0106
#define finderSaysIdle                  0x0107
#define finderSaysExtrasChosen          0x0108
#define finderSaysBeforeRename          0x0109
#define finderSaysKeyHit                0x010A

/************************************************************************************************/

/* SendRequest codes sent to the Finder (target = "Apple~Finder~") */
#define tellFinderGetDebugInfo          0x8000
#define tellFinderAreYouThere           0x8001
#define askFinderAreYouThere            0x8001
#define tellFinderOpenWindow            0x8002
#define tellFinderCloseWindow           0x8003
#define tellFinderGetSelectedIcons      0x8004
#define tellFinderSetSelectedIcons      0x8005
#define tellFinderLaunchThis            0x8006
#define tellFinderShutDown              0x8007
#define tellFinderMItemSelected         0x8008
#define tellFinderMatchFileToIcon       0x800A
#define tellFinderAddBundle             0x800B
#define tellFinderAboutChange           0x800C
#define tellFinderCheckDatabase         0x800D
#define tellFinderColorSelection        0x800E
#define tellFinderAddToExtras           0x800F
#define tellFinderIdleHowLong           0x8011
#define askFinderIdleHowLong            0x8011
#define tellFinderGetWindowIcons        0x8012
#define tellFinderGetWindowInfo         0x8013
#define tellFinderRemoveFromExtras      0x8014
#define tellFinderSpecialPreferences    0x8015

/************************************************************************************************/

/* Finder menu item IDs */
#define finderItemAbout 0x012D
#define finderItemHelp 0x012E
#define finderItemNewFolder 0x015F
#define finderItemOpen 0x0160
#define finderItemPrint 0x0161
#define finderItemClose 0x0162
#define finderItemCloseAll 0x0163
#define finderItemDuplicate 0x0164
#define finderItemPutAway 0x0165
#define finderItemValidate 0x0166
#define finderItemUndo 0x00FA
#define finderItemCut 0x00FB
#define finderItemCopy 0x00FC
#define finderItemPaste 0x00FD
#define finderItemClear 0x00FE
#define finderItemSelectAll 0x0191
#define finderItemShowClipboard 0x0192
#define finderItemStackWindows 0x01C3
#define finderItemByIcon 0x01F5
#define finderItemBySmallIcon 0x01F6
#define finderItemByName 0x01F7
#define finderItemByDate 0x01F8
#define finderItemBySize 0x01F9
#define finderItemByKind 0x01FA
#define finderItemFormat 0x0227
#define finderItemErase 0x0228
#define finderItemVerify 0x0229
#define finderItemEject 0x022A
#define finderItemCleanUp 0x0259
#define finderItemEmptyTrash 0x025A
#define finderItemPreferences 0x025B
#define finderItemIconInfo 0x025C
#define finderItemShutDown 0x025D
#define finderItemCleanUpByName 0x025E
#define finderItemColorBlack 0x028B
#define finderItemColorBlue 0x028C
#define finderItemColorYellowBrown 0x028D
#define finderItemColorGray1 0x028E
#define finderItemColorRed 0x028F
#define finderItemColorPurple 0x0290
#define finderItemColorOrange 0x0291
#define finderItemColorPink 0x0292
#define finderItemColorDarkGreen 0x0293
#define finderItemColorAqua 0x0294
#define finderItemColorBrightGreen 0x0295
#define finderItemColorPaleGreen 0x0296
#define finderItemColorPeriwinkleBlue 0x0298
#define finderItemColorYellow 0x0299
#define finderItemColorWhite 0x029A

/************************************************************************************************/

/* Finder SendRequest Result Error Codes */
#define fErrNoError         0x0000    /* no error */
#define fErrBadInput        0x4201    /* bad input value */
#define fErrFailed          0x4202    /* could not complete request */
#define fErrCancel          0x4203    /* user cancelled operation */
#define fErrDimmed          0x4204    /* menu item was dimmed */
#define fErrBusy            0x4205    /* not now, finder has headache */
#define fErrNotPrudent      0x4206    /* can't add Finder's resources to desktop file */
#define fErrBadBundle       0x4207    /* unknown rBundle version, or rBundle damaged */
#define fErrNotImp          0x42FF    /* request not implemented */

/************************************************************************************************/

/* general Finder data structures */

typedef struct iconObj *iconObjPtr, **iconObjHandle;
typedef struct iconObj {
    iconObjHandle icNext;               /* next icon in list (NIL = no more) */
    iconObjHandle icLast;               /* previous icon in list (NIL = no more) */
    WindowPtr icMom;                    /* window the icon is currently in (NIL = desktop) */
    WindowPtr icWind;                   /* window the icon is opened into */
    iconObjHandle icDisk;               /* disk iconObj which owns this icon */
    long icFlag;                        /* see below */
    word icFType;                       /* icon's file type */
    long icFileInfo;                    /* file's auxtype or disk's file system */
    char *icKind;                       /* pointer to Kind pstring, or NIL */
    word icy;                           /* vertical position of bottom of icon */
    word icx;                           /* horizontal position of center of icon */
    word icTextY;                       /* icon's vertical position when viewed by text */
    word icTitleLen;                    /* half the width of the icon's title */
    char icName[34];                    /* pstring name of icon */
    word icLocalAccess;                 /* icon's current local access */
    word icForked;                      /* bit 15 set if file is extended */
    long icFBlocks;                     /* file's size in blocks, or number of used blocks on disk */
    long icFBytes;                      /* file's size in bytes, or total blocks on disk */
    TimeRec icCDate;                    /* create date/time */
    TimeRec icMDate;                    /* last-modified date/time */
    long icIcon;                        /* index into Finder's list of icon images */
    long icSmallIcon;                   /* index into Finder's list of icon images */
    Handle icRBundle;                   /* handle of rBundle which matched this icon, or NIL */
    long icOneDocOffset;                /* offset to oneDoc within rBundle handle */
    WindowPtr icInfo;                   /* pointer to Icon Info window, or NIL */
    word icDevNum;                      /* device number (valid for disk/device icons) */
    word icDevInfo;                     /* device characteristics (valid for disk/device icons) */
    word icOptionList;                  /* beginning of option list--length */
    word icFST;                         /* FST ID (first data word of option list) */
    char bodyOfOptionList[36];          /* next 36 bytes of option list */
    long icNetworkAccess;               /* access information if FST ID is $0D (AppleShare) */
    } iconObj;

/* icFlag values */

#define ICSELECTED     0x00000001L
#define ICOPENED       0x00000002L
#define ICOFFLINE      0x00000004L
#define ICEXTENDED     0x00000008L
#define ICLOCKED       0x00000080L
#define ICFORECLR      0x00000f00L
#define ICBACKCLR      0x0000F000L
#define ICNETACCESS    0x000F0000L
#define ICNETWORK      0x01000000L
#define ICREADABLE     0x02000000L

typedef struct finderWindBlk {
    iconObjHandle windIcons;
    word windID;
    word windView;
    iconObjHandle windIc;
    iconObjHandle windDiskIc;
    word windItems;
    long windUsed;
    long windFree;
    word windFST;
    word windAccess;
    word windDirty;
    char windTitle[54];
    word windMenuItem;
    char windMenuText[52];
    TimeRec windDate;
    char windPath[991];
    } finderWindBlk, *finderWindBlkPtr;

/************************************************************************************************/

/* finderSays DataIn Structures */

typedef struct finderSaysHelloIn {
    word pCount;
    long versNum;
    word finderUserID;
    word iconObjectSize;
    } finderSaysHelloIn, *finderSaysHelloInPtr;

typedef struct finderSaysMItemSelectedIn {
    word pCount;
    word menuItemID;
    word menuID;
    word modifiers;
    } finderSaysMItemSelectedIn, *finderSaysMItemSelectedInPtr;

typedef struct finderSaysBeforeOpenIn {
    word pCount;
    pointer pathname;
    RectPtr zoomRect;
    word filetype;
    long auxtype;
    word modifiers;
    iconObjHandle theIconObj;
    word printFlag;
    } finderSaysBeforeOpenIn, *finderSaysBeforeOpenInPtr,
      finderSaysOpenFailedIn, *finderSaysOpenFailedInPtr;

typedef struct finderSaysBeforeCopyIn {
    word pCount;
    ptr sourcePathname;
    ptr destinationPathname;
    } finderSaysBeforeCopyIn, *finderSaysBeforeCopyInPtr;

typedef struct finderSaysBeforeRenameIn {
    word pCount;
    ptr oldPathname;
    ptr newPathname;
    word filetype;
    long auxtype;
    } finderSaysBeforeRenameIn, *finderSaysBeforeRenameInPtr;

typedef struct finderSaysKeyHitIn {
    word pCount;
    word message;
    word modifiers;
    } finderSaysKeyHitIn, *finderSaysKeyHitInPtr;

/************************************************************************************************/

/* finderSays DataOut Structures */

typedef struct finderSaysMItemSelectedOut {
    word recvCount;
    word abortItFlag;
    } finderSaysMItemSelectedOut, *finderSaysMItemSelectedOutPtr;

typedef struct finderSaysBeforeCopyOut {
    word recvCount;
    word abortFlag;    /* 0 = continue, 1 = abort, 2 - $FFFF reserved */
    } finderSaysBeforeCopyOut, *finderSaysBeforeCopyOutPtr;

typedef struct finderSaysBeforeRenameOut {
    word recvCount;
    word abortFlag;    /* boolean, non-zero to abort rename */
    } finderSaysBeforeRenameOut, *finderSaysBeforeRenameOutPtr;


/************************************************************************************************/

/* tellFinder DataIn Structures */

typedef struct tellFinderLaunchThisIn {
    word launchprint;
    ptr pathname;
    } tellFinderLaunchThisIn, *tellFinderLaunchThisInPtr;

typedef struct tellFinderMItemSelectedIn {
    word menuItemID;
    word modifiers;
    word flags;    /* bit 15 = hilite, all other bits reserved */
} tellFinderMItemSelectedIn, *tellFinderMItemSelectedInPtr;

typedef struct tellFinderMatchFileToIconIn {
    word pCount;               /* 11, minimum 10 */
    word votingBits;
    word whichMatch;           /* we want 1 or higher */
    word filetype;
    long auxtype;
    ptr matchFilenamePtr;
    ptr createFileInfoPtr;
    ptr modFileInfoPtr;
    word localAccess;
    word flags;                /* bit 15 = extended file, all other bits reserved */
    ptr optionListPtr;
    long combinedEOF;          /* resource and data fork EOF */
    } tellFinderMatchFileToIconIn, *tellFinderMatchFileToIconInPtr;

typedef struct tellFinderAddBundleIn {
    word addHow;               /* bit 15 = to Desktop file, bit 14 = to memory */
    ptr pathnamePtr;
    ptr desktopPathnamePtr;
    long rBundleID;            /* NIL if adding to memory only */
    } tellFinderAddBundleIn, *tellFinderAddBundleInPtr;

typedef struct tellFinderCheckDatabaseIn {
    word update;                  /* high bit set if update should take place if match found */
    ptr updatePathnamePtr;        /* ptr to use for update, NIL if no update */
    ptr rVersionPtr;              /* must lock this resource */
    } tellFinderCheckDatabaseIn, *tellFinderCheckDatabaseInPtr;

typedef struct tellFinderSpecialPreferencesIn {
    word pCount;                  /* minimum 1 */
    word dragHDtoTrash;           /* 0=disallow, 1=allow */
    } tellFinderSpecialPreferencesIn, *tellFinderSpecialPreferencesInPtr;

/************************************************************************************************/

/* tellFinder DataOut Structures */

typedef struct tellFinderGetDebugInfoOut {
    word recvCount;
    word finderResult;
    word pCount;
    word directPage;
    handle deskIcon;
    handle nameChainH;
    pointer filetypeBlock;
    pointer deviceBlock;
    handle masterChainH;
    handle rFPListHandle;
    word rFPCount;
    long reserved[64];
    } tellFinderGetDebugInfoOut, *tellFinderGetDebugInfoOutPtr;

typedef struct tellFinderAreYouThereOut {
    word recvCount;
    word finderResult;
    } tellFinderAreYouThereOut, *tellFinderAreYouThereOutPtr;

typedef struct tellFinderOpenWindowOut {
    word recvCount;
    word finderResult;
    WindowPtr window;
    } tellFinderOpenWindowOut, *tellFinderOpenWindowOutPtr;

typedef struct tellFinderCloseWindowOut {
    word recvCount;
    word finderResult;
    } tellFinderCloseWindowOut, *tellFinderCloseWindowOutPtr;

typedef struct tellFinderGetSelectedIconsOut {
    word recvCount;
    word finderResult;
    WindowPtr iconWindowPtr;
    Handle stringListHandle;
    } tellFinderGetSelectedIconsOut, *tellFinderGetSelectedIconsOutPtr;

typedef struct tellFinderSetSelectedIconsOut {
    word recvCount;
    word finderResult;
    } tellFinderSetSelectedIconsOut, *tellFinderSetSelectedIconsOutPtr;

typedef struct tellFinderLaunchThisOut {
    word recvCount;
    word finderResult;
    } tellFinderLaunchThisOut, *tellFinderLaunchThisOutPtr;

typedef struct tellFinderShutDownOut {
    word recvCount;
    word finderResult;
    } tellFinderShutDownOut, *tellFinderShutDownOutPtr;

typedef struct tellFinderMItemSelectedOut {
    word recvCount;
    word finderResult;
    } tellFinderMItemSelectedOut, *tellFinderMItemSelectedOutPtr;

typedef struct tellFinderMatchFileToIconOut {
    word recvCount;
    word finderResult;
    long oneDocOffset;                  /* NIL if no match */
    Handle rBundleHandle;               /* NIL if no match */
    Handle smallIconHandle;             /* Never NIL */
    Handle largeIconHandle;             /* Never NIL */
    Handle rFInderPathHandle;           /* NIL if no one owns icon */
    } tellFinderMatchFileToIconOut, *tellFinderMatchFileToIconOutPtr;

typedef struct tellFinderAddBundleOut {
    word recvCount;
    word finderResult;
    } tellFinderAddBundleOut, *tellFinderAddBundleOutPtr;

typedef struct tellFinderAboutChangeOut {
    word recvCount;
    word finderResult;
    } tellFinderAboutChangeOut, *tellFinderAboutChangeOutPtr;

typedef struct tellFinderCheckDatabaseOut {
    word recvCount;
    word finderResult;
    word match;  /* 0 if no match found, non-zero if match found */
    } tellFinderCheckDatabaseOut, *tellFinderCheckDatabaseOutPtr;

typedef struct tellFinderColorSelectionOut {
    word recvCount;
    word finderResult;
    } tellFinderColorSelectionOut, *tellFinderColorSelectionOutPtr;

typedef struct tellFinderAddToExtrasOut {
    word recvCount;
    word finderResult;
    word menuItemID;
    word menuID;
    } tellFinderAddToExtrasOut, *tellFinderAddToExtrasOutPtr;

typedef struct tellFinderIdleHowLongOut {
    word recvCount;
    word finderResult;
    long tickCount;
    } tellFinderIdleHowLongOut, *tellFinderIdleHowLongOutPtr;

typedef struct tellFinderGetWindowIconsOut {
    word recvCount;
    word finderResult;
    Handle stringListHandle;
    } tellFinderGetWindowIconsOut, *tellFinderGetWindowIconsOutPtr;

typedef struct tellFinderGetWindowInfoOut {
    word recvCount;
    word finderResult;
    word windowType;
    word windView;
    word windFST;
    char *windTitle;
    ptr windPath;
    long reserved1;
    long reserved2;
    } tellFinderGetWindowInfoOut, *tellFinderGetWindowInfoOutPtr;

typedef struct tellFinderRemoveFromExtrasOut {
    word recvCount;
    word finderResult;
    } tellFinderRemoveFromExtrasOut, *tellFinderRemoveFromExtrasOutPtr;

typedef struct tellFinderSpecialPreferencesOut {
    word recvCount;
    word finderResult;
    } tellFinderSpecialPreferencesOut, *tellFinderSpecialPreferencesOutPtr;


#endif
