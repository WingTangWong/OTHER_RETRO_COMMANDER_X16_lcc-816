/********************************************
*
* Tool Locator
*
* Copyright Apple Computer, Inc.1986-92
* All Rights Reserved
*
* Copyright 1992, 1993, Byte Works, Inc.
*
********************************************/

#pragma once

#ifndef __TYPES__
#include <types.h>
#endif

#ifndef __LOCATOR__
#define __LOCATOR__

/* Error Codes */
#define toolNotFoundErr 0x0001
#define funcNotFoundErr 0x0002
#define sysStrtMtErr 0x0100             /* can't mount system startup volume */
#define tlBadRecFlag 0x0103             /* StartStop record invalid */
#define tlCantLoad 0x0104               /* A tool cannot be loaded */
#define toolVersionErr 0x0110
#define messNotFoundErr 0x0111
#define messageOvfl 0x0112              /* No message numbers available */
#define nameTooLong 0x0113              /* Message name too long */
#define reqNotAccepted 0x0120           /* SendRequest request not accepted */
#define duplicateName 0x0121            /* duplicate name for AcceptRequests */
#define invalidSendRequest 0x0122       /* bad combo of target and sendHow */

/* MessageCenter Codes */
#define fileInfoType 0x0001             /* Message type parameter */
#define addMessage 0x0001               /* action parameter */
#define getMessage 0x0002               /* action parameter */
#define deleteMessage 0x0003            /* action parameter */
#define fileInfoTypeGS 0x0011           /* Message type parameter (GS/OS strings) */

/* GetMsgHandle flags values */
#define gmhByIndex 0
#define gmhByType 1
#define gmhByName 2

/* SendRequest/AcceptRequests codes */
#define systemSaysBeep 0x0001           /* used by SysBeep2 */
#define systemSaysUnknownDisk 0x0002    /* used by HandleDiskInsert */
#define srqGoAway 0x0003
#define srqGetrSoundSample 0x0004
#define srqSynchronize 0x0005
#define srqPlayrSoundSample 0x0006
#define systemSaysNewDeskMsg 0x0008
#define systemSaysEjectingDev 0x000E
#define systemSaysDeskStartUp 0x0502
#define systemSaysDeskShutDown 0x0503
#define systemSaysFixedAppleMenu 0x051E
#define systemSaysMenuKey 0x0F01
#define systemSaysDoClipboard 0x000C
#define systemSaysForceUndim 0x000D
#define srqOpenOrPrint 0x0010
#define srqQuit 0x0011
#define systemSaysGetSysIcon 0x1201

/* SendRequest sendHow values */
#define stopAfterOne 0x8000
#define sendToAll 0
#define sendToName 1
#define sendToUserID 2

/* StartUpTools flag bits */
#define leaveScreenClean 0x0004
#define openResAsAllowed 0x0008
#define noResourceMgr 0x0010            /* for ShutDownTools, too */

/* TLMountVolume Codes */
#define mvReturn 0x0001                 /* like ok for dialogs */
#define mvEscape 0x0002                 /* like cancel for dialogs */

/* Tool Set Spec Codes */
#define sysTool 0x0000
#define userTool 0x8000
#ifndef theToolsLength                  /* ToolTable - default number of ToolSpecs */
#define theToolsLength 0x0010
#endif

struct MessageRec {
   struct MessageRec **messageNext;
   Word messageType;
   Word messageData;
   Str255 fileNames[1];
   };
typedef struct MessageRec MessageRec, *MessageRecPtr, **MessageRecHndl;

typedef struct wString {
   Word length;                         /* Number of Chars in text field  */
   char text[255];
   } wString, *wStringPtr, **wStringHndl;
typedef wStringHndl *wStringHndlPtr;

typedef struct MessageRecGS {
   long reserved;                       /* reserved */
   Word messageType;
   Word printFlag;
   wString fileNames[1];
   } MessageRecGS, *MessageRecGSPtr, **MessageRecGSHndl;

struct ToolSpec {
   Word toolNumber;
   Word minVersion;
   };
typedef struct ToolSpec ToolSpec;

struct ToolTable {
   Word toolCount;
   ToolSpec theTools[theToolsLength];
   };
typedef struct ToolTable ToolTable, *ToolTablePtr;

struct StartStopRecord {
   Word flags;
   Word videoMode;
   Word resFileID;
   Handle dPageHandle;
   Word numTools;
   ToolSpec theTools[theToolsLength];
   };
typedef struct StartStopRecord StartStopRecord, *StartStopRecordPtr;

typedef Long ResponseRecord;

struct srqGoAwayOut {
   Word recvCount;
   Word resultID;                       /* returned UserID */
   Word resultFlags;                    /* returned flags--bit 15=Restartable, 14-0=reserved */
   };
typedef struct srqGoAwayOut srqGoAwayOut, *srqGoAwayOutPtr;

extern pascal void TLBootInit(void) inline(0x0101,dispatcher);
extern pascal void TLStartUp(void) inline(0x0201,dispatcher);
extern pascal void TLShutDown(void) inline(0x0301,dispatcher);
extern pascal Word TLVersion(void) inline(0x0401,dispatcher);
extern pascal void TLReset(void) inline(0x0501,dispatcher);
extern pascal Boolean TLStatus(void) inline(0x0601,dispatcher);
extern pascal Pointer GetFuncPtr(Word, Word) inline(0x0B01,dispatcher);
extern pascal Pointer GetTSPtr(Word, Word) inline(0x0901,dispatcher);
extern pascal Pointer GetWAP(Word, Word) inline(0x0C01,dispatcher);
extern pascal void LoadOneTool(Word, Word) inline(0x0F01,dispatcher);
extern pascal void LoadTools(Pointer) inline(0x0E01,dispatcher);
extern pascal void MessageCenter(Word, Word, Handle) inline(0x1501,dispatcher);
extern pascal void RestoreTextState(Handle) inline(0x1401,dispatcher);
extern pascal Handle SaveTextState(void) inline(0x1301,dispatcher);
extern pascal void SetTSPtr(Word, Word, Pointer) inline(0x0A01,dispatcher);
extern pascal void SetWAP(Word, Word, Pointer) inline(0x0D01,dispatcher);
extern pascal Word TLMountVolume(Integer, Integer, Pointer, Pointer, Pointer, Pointer) inline(0x1101,dispatcher);
extern pascal Word TLTextMountVolume(Pointer, Pointer, Pointer, Pointer) inline(0x1201,dispatcher);
extern pascal void UnloadOneTool(Word) inline(0x1001,dispatcher);

extern pascal ResponseRecord MessageByName(Boolean, Pointer) inline(0x1701,dispatcher);
extern pascal void SetDefaultTPT(void) inline(0x1601,dispatcher);
extern pascal void ShutDownTools(Word, Ref) inline(0x1901,dispatcher);
extern pascal Ref StartUpTools(Word, Word, Ref) inline(0x1801,dispatcher);

extern pascal void AcceptRequests(Pointer, Word, WordProcPtr) inline(0x1B01,dispatcher);
extern pascal Handle GetMsgHandle(Word, Long) inline(0x1A01,dispatcher);
extern pascal void SendRequest(Word, Word, Long, Long, Ptr) inline(0x1C01,dispatcher);

#endif
