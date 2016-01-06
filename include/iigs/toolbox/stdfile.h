/********************************************
*
* Standard File Operations Tool Set
*
* Copyright Apple Computer, Inc.1986-92
* All Rights Reserved
*
* Copyright 1992, Byte Works, Inc
*
********************************************/

#pragma once

#ifndef __TYPES__
#include <types.h>
#endif

#ifndef __STDFILE__
#define __STDFILE__

/* Error Codes */
#define badPromptDesc 0x1701
#define badOrigNameDesc 0x1702
#define badReplyNameDesc 0x1704
#define badReplyPathDesc 0x1705
#define badCall 0x1706
#define sfNotStarted 0x17FF

/* filterProc Result Codes */
#define noDisplay 0x0000                /* file not to be displayed */
#define noSelect 0x0001                 /* file displayed, but not selectable */
#define displaySelect 0x0002            /* file displayed and selectable */

/* Other Constants */
#define sfWildAuxType 0x8000
#define sfMatchFileType 0x8000
#define sfWildFileType 0x4000
#define sfMatchAuxType 0x4000
#define sfDisplayGrey 0x2000

#ifndef sfFileTypeEntriesLength         /* SFTypeList - default number of FileTypeEntries */
#define sfFileTypeEntriesLength 0x0005
#endif

typedef struct SFReplyRec {
   Boolean good;
   Word fileType;
   Word auxFileType;
   char filename[16];
   char fullPathname[129];
   } SFReplyRec, *SFReplyRecPtr, **SFReplyRecHndl;

struct SFReplyRec2 {
   Boolean good;
   Word fileType;
   LongWord auxType;
   RefDescriptor nameRefDesc;
   Ref nameRef;
   RefDescriptor pathRefDesc;
   Ref pathRef;
   };
typedef struct SFReplyRec2 SFReplyRec2, *SFReplyRec2Ptr, **SFReplyRec2Hndl;

struct fileEntryRec {
   Word fileType;
   unsigned long auxType;
   Byte nameLength;
   Byte prefix1;
   Byte prefix2;
   char name[253];
   };
typedef struct fileEntryRec fileEntryRec, *fileEntryRecPtr;

struct namesHandleRec {
   Word bufferLength;
   fileEntryRec fileEntryArray[1];
   };
typedef struct namesHandleRec namesHandleRec, *namesHandleRecPtr, **namesHandleRecHndl;

struct MultiReplyRecord {
   Word good;
   namesHandleRecHndl namesHandle;
   };
typedef struct MultiReplyRecord MultiReplyRecord, *MultiReplyPtr;

struct SFTypeList {
   Byte numEntries;
   Byte fileTypeEntries[sfFileTypeEntriesLength];
   };
typedef struct SFTypeList SFTypeList, *SFTypeListPtr, **SFTypeListHndl;

struct TypeSelector2 {
   Word flags;
   Word fileType;
   LongWord auxType;
   };
typedef struct TypeSelector2 TypeSelector2;

struct SFTypeList2 {
   Word numEntries;
   TypeSelector2 fileTypeEntries[sfFileTypeEntriesLength];
   };
typedef struct SFTypeList2 SFTypeList2, *SFTypeList2Ptr, **SFTypeList2Hndl;

extern pascal void SFBootInit(void) inline(0x0117,dispatcher);
extern pascal void SFStartUp(Word, Word) inline(0x0217,dispatcher);
extern pascal void SFShutDown(void) inline(0x0317,dispatcher);
extern pascal Word SFVersion(void) inline(0x0417,dispatcher);
extern pascal void SFReset(void) inline(0x0517,dispatcher);
extern pascal Boolean SFStatus(void) inline(0x0617,dispatcher);
extern pascal void SFAllCaps(Boolean) inline(0x0D17,dispatcher);
extern pascal void SFGetFile(Integer, Integer, Pointer, WordProcPtr, Pointer, SFReplyRecPtr) inline(0x0917,dispatcher);
extern pascal void SFPGetFile(Integer, Integer, Pointer, WordProcPtr, Pointer, Pointer, VoidProcPtr, SFReplyRecPtr) inline(0x0B17,dispatcher);
extern pascal void SFPPutFile(Integer, Integer, Pointer, Pointer, Word, Pointer, VoidProcPtr, SFReplyRecPtr) inline(0x0C17,dispatcher);
extern pascal void SFPutFile(Integer, Integer, Pointer, Pointer, Word, SFReplyRecPtr) inline(0x0A17,dispatcher);

extern pascal void SFGetFile2(Integer, Integer, Word, Ref, WordProcPtr, SFTypeList2Ptr, SFReplyRec2Ptr) inline(0x0E17,dispatcher);
extern pascal void SFMultiGet2(Integer, Integer, Word, Ref, WordProcPtr, SFTypeList2Ptr, MultiReplyPtr) inline(0x1417,dispatcher);
extern pascal void SFPGetFile2(Integer, Integer, VoidProcPtr, Word, Ref, WordProcPtr, SFTypeList2Ptr, Pointer, VoidProcPtr, SFReplyRec2Ptr) inline(0x1017,dispatcher);
extern pascal void SFPMultiGet2(Integer, Integer, VoidProcPtr, Word, Ref, WordProcPtr, SFTypeList2Ptr, Pointer, VoidProcPtr, MultiReplyPtr) inline(0x1517,dispatcher);
extern pascal void SFPPutFile2(Integer, Integer, VoidProcPtr, Word, Ref, Word, Ref, Pointer, VoidProcPtr, SFReplyRec2Ptr) inline(0x1117,dispatcher);
extern pascal void SFPutFile2(Integer, Integer, Word, Ref, Word, Ref, SFReplyRec2Ptr) inline(0x0F17,dispatcher);
extern pascal void SFReScan(WordProcPtr, SFTypeList2Ptr) inline(0x1317,dispatcher);
extern pascal Boolean SFShowInvisible(Word) inline(0x1217,dispatcher);

#endif
