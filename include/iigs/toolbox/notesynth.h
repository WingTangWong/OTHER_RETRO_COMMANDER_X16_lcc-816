/********************************************
*
* Note Synthesizer
*
* Copyright Apple Computer, Inc.1986-90
* All Rights Reserved
*
* Copyright 1992, Byte Works, Inc.
*
********************************************/

#pragma once

#ifndef __TYPES__
#include <types.h>
#endif

#ifndef __NOTESYN__
#define __NOTESYN__

/* Error Codes */
#define nsAlreadyInit 0x1901            /* Note Syn already initialized */
#define nsSndNotInit 0x1902             /* Sound Tools not initialized */
#define nsNotAvail 0x1921               /* generator not available */
#define nsBadGenNum 0x1922              /* bad generator number */
#define nsNotInit 0x1923                /* Note Syn not initialized */
#define nsGenAlreadyOn 0x1924           /* generator already on */
#define soundWrongVer 0x1925            /* incompatible versions of Sound  and NoteSyn */
struct Envelope {
   Byte st1BkPt;
   Word st1Increment;
   Byte st2BkPt;
   Word st2Increment;
   Byte st3BkPt;
   Word st3Increment;
   Byte st4BkPt;
   Word st4Increment;
   Byte st5BkPt;
   Word st5Increment;
   Byte st6BkPt;
   Word st6Increment;
   Byte st7BkPt;
   Word st7Increment;
   Byte st8BkPt;
   Word st8Increment;
   };
typedef struct Envelope Envelope, *EnvelopePtr, **EnvelopeHndl;

struct WaveForm {
   Byte wfTopKey;
   Byte wfWaveAddress;
   Byte wfWaveSize;
   Byte wfDocMode;
   Word wfRelPitch;
   };
typedef struct WaveForm WaveForm, *WaveFormPtr, **WaveFormHndl;

struct Instrument {
   Envelope theEnvelope;
   Byte releaseSegment;
   Byte priorityIncrement;
   Byte pitchBendRange;
   Byte vibratoDepth;
   Byte vibratoSpeed;
   Byte inSpare;
   Byte aWaveCount;
   Byte bWaveCount;
   WaveForm aWaveList[1];
   WaveForm bWaveList[1];
   };
typedef struct Instrument Instrument, *InstrumentPtr, **InstrumentHndl;

extern pascal void NSBootInit(void) inline(0x0119,dispatcher);
extern pascal void NSStartUp(Word, Pointer) inline(0x0219,dispatcher);
extern pascal void NSShutDown(void) inline(0x0319,dispatcher);
extern pascal Word NSVersion(void) inline(0x0419,dispatcher);
extern pascal void NSReset(void) inline(0x0519,dispatcher);
extern pascal Boolean NSStatus(void) inline(0x0619,dispatcher);
extern pascal void AllNotesOff(void) inline(0x0D19,dispatcher);
extern pascal Word AllocGen(Word) inline(0x0919,dispatcher);
extern pascal void DeallocGen(Word) inline(0x0A19,dispatcher);
extern pascal void NoteOff(Word, Word) inline(0x0C19,dispatcher);
extern pascal void NoteOn(Word, Word, Word, Pointer) inline(0x0B19,dispatcher);
extern pascal Word NSSetUpdateRate(Word) inline(0x0E19,dispatcher);
extern pascal VoidProcPtr NSSetUserUpdateRtn(Pointer) inline(0x0F19,dispatcher);

#endif
