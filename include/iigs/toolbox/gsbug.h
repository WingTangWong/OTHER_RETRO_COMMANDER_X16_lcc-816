/********************************************
; File: GSBug.h
;
;
; Copyright Apple Computer, Inc. 1991
; All Rights Reserved
;
********************************************/

#pragma once

#ifndef __TYPES__
#include <types.h>
#endif

#ifndef __GSBUG__
#define __GSBUG__

/* DebugGetInfo selectors */
#define dgiProgramCounter 0 /* returns program counter */
#define dgiEscapEntry 1 /* returns address to invoke gsbug */

/* DebugControl operations */
#define dcOpSet 0
#define dcOpClear 1
#define dcOpClearAll 2
#define dcOpIn 3
#define dcOpOut 4

#define dqGetInOutStatus 0
#define dqGetValue 1
#define dqGetAuxValue 2

/* for DebugControl / DebugQuery */

#define debugTypeToolBreak 0
#define debugTypeOSBreak 1
#define debugTypeRequestBreak 2
#define debugTypeBreakPoint 3
#define debugTypeMemoryProtect 4

extern pascal Word DebugVersion(void) inline(0x04FF,dispatcher);
extern pascal Word DebugStatus(void) inline(0x06FF,dispatcher);
extern pascal void DebugStr(Pointer) inline(0x09FF,dispatcher);
extern pascal void SetMileStone(Pointer) inline(0x0AFF,dispatcher);
extern pascal void DebugSetHook(Pointer) inline(0x0BFF,dispatcher);
extern pascal LongWord DebugGetInfo(Word) inline(0x0CFF,dispatcher);
extern pascal void DebugControl(LongWord, LongWord, Word, Word) inline(0x0DFF,dispatcher);
extern pascal LongWord DebugQuery(LongWord, Word, Word) inline(0x0EFF,dispatcher);

#endif
