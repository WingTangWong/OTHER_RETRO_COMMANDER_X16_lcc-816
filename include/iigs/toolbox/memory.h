/********************************************
*
* Memory Manager
*
* Copyright Apple Computer, Inc.1986-91
* All Rights Reserved
*
* Copyright 1992, Byte Works, Inc.
*
********************************************/

#pragma once

#ifndef __TYPES__
#include <types.h>
#endif

#ifndef __MEMORY__
#define __MEMORY__

/* Error Codes */
#define memErr 0x0201                   /* unable to allocate block */
#define emptyErr 0x0202                 /* illegal operation, empty handle */
#define notEmptyErr 0x0203              /* an empty handle was expected for this operation */
#define lockErr 0x0204                  /* illegal operation on a locked block */
#define purgeErr 0x0205                 /* attempt to purge an unpurgable block */
#define handleErr 0x0206                /* an invalid handle was given */
#define idErr 0x0207                    /* an invalid owner ID was given */
#define attrErr 0x0208                  /* operation illegal on block with given attributes */

/* Handle Attribute Bits */
#define attrNoPurge 0x0000              /* Not purgeable */
#define attrBank 0x0001                 /* fixed bank */
#define attrAddr 0x0002                 /* fixed address */
#define attrPage 0x0004                 /* page aligned */
#define attrNoSpec 0x0008               /* may not use special memory */
#define attrNoCross 0x0010              /* may not cross banks */
#define attrPurge1 0x0100               /* Purge level 1 */
#define attrPurge2 0x0200               /* Purge level 2 */
#define attrPurge3 0x0300               /* Purge level 3 */
#define attrPurge 0x0300                /* test or set both purge bits */
#define attrHandle 0x1000               /* block of master pointers */
#define attrSystem 0x2000               /* system handle */
#define attrFixed 0x4000                /* not movable */
#define attrLocked 0x8000               /* locked */

extern pascal void MMBootInit(void) inline(0x0102,dispatcher);
extern pascal Word MMStartUp(void) inline(0x0202,dispatcher);
extern pascal void MMShutDown(Word) inline(0x0302,dispatcher);
extern pascal Word MMVersion(void) inline(0x0402,dispatcher);
extern pascal void MMReset(void) inline(0x0502,dispatcher);
extern pascal Boolean MMStatus(void) inline(0x0602,dispatcher);
extern pascal void BlockMove(Pointer, Pointer, LongWord) inline(0x2B02,dispatcher);
extern pascal void CheckHandle(Handle) inline(0x1E02,dispatcher);
extern pascal void CompactMem(void) inline(0x1F02,dispatcher);
extern pascal void DisposeAll(Word) inline(0x1102,dispatcher);
extern pascal void DisposeHandle(Handle) inline(0x1002,dispatcher);
extern pascal Handle FindHandle(Pointer) inline(0x1A02,dispatcher);
extern pascal LongWord FreeMem(void) inline(0x1B02,dispatcher);
extern pascal LongWord GetHandleSize(Handle) inline(0x1802,dispatcher);
extern pascal void HandToHand(Handle, Handle, LongWord) inline(0x2A02,dispatcher);
extern pascal void HandToPtr(Handle, Pointer, LongWord) inline(0x2902,dispatcher);
extern pascal void HLock(Handle) inline(0x2002,dispatcher);
extern pascal void HLockAll(Word) inline(0x2102,dispatcher);
extern pascal void HUnlock(Handle) inline(0x2202,dispatcher);
extern pascal void HUnlockAll(Word) inline(0x2302,dispatcher);
extern pascal LongWord MaxBlock(void) inline(0x1C02,dispatcher);
extern pascal Handle NewHandle(LongWord, Word, Word, Pointer) inline(0x0902,dispatcher);
extern pascal void PtrToHand(Pointer, Handle, LongWord) inline(0x2802,dispatcher);
extern pascal void PurgeAll(Word) inline(0x1302,dispatcher);
extern pascal void PurgeHandle(Handle) inline(0x1202,dispatcher);
extern pascal void ReAllocHandle(LongWord, Word, Word, Pointer, Handle) inline(0x0A02,dispatcher);
extern pascal void RestoreHandle(Handle) inline(0x0B02,dispatcher);
extern pascal void SetHandleSize(LongWord, Handle) inline(0x1902,dispatcher);
extern pascal void SetPurge(Word, Handle) inline(0x2402,dispatcher);
extern pascal void SetPurgeAll(Word, Word) inline(0x2502,dispatcher);
extern pascal LongWord TotalMem(void) inline(0x1D02,dispatcher);

extern pascal void AddToOOMQueue(Pointer) inline(0x0C02,dispatcher);
extern pascal LongWord RealFreeMem(void) inline(0x2F02,dispatcher);
extern pascal void RemoveFromOOMQueue(Pointer) inline(0x0D02,dispatcher);

extern pascal Word SetHandleID(Word, Handle) inline(0x3002,dispatcher);

#endif
