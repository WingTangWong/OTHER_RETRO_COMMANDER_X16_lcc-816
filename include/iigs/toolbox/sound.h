/********************************************
*
* Sound Tool Set
*
* Copyright Apple Computer, Inc.1986-90
* All Rights Reserved
*
* Copyright 1992, Byte Works, Inc
*
********************************************/

#pragma once

#ifndef __TYPES__
#include <types.h>
#endif

#ifndef __SOUND__
#define __SOUND__

/* Error Codes */
#define noDOCFndErr 0x0810              /* no DOC chip found */
#define docAddrRngErr 0x0811            /* DOC address range error */
#define noSAppInitErr 0x0812            /* no SAppInit call made */
#define invalGenNumErr 0x0813           /* invalid generator number */
#define synthModeErr 0x0814             /* synthesizer mode error */
#define genBusyErr 0x0815               /* generator busy error */
#define mstrIRQNotAssgnErr 0x0817       /* master IRQ not assigned */
#define sndAlreadyStrtErr 0x0818        /* sound tools already started */
#define unclaimedSndIntErr 0x08FF       /* sound tools already started */

/* channelGenMode Codes */
#define ffSynthMode 0x0001              /* Free form synthesizer mode */
#define noteSynthMode 0x0002            /* Note synthesizer mode. */

/* genMask Codes; parameters tp FFStopSound */
#define gen0off 0x0001
#define gen1off 0x0002
#define gen2off 0x0004
#define gen3off 0x0008
#define gen4off 0x0010
#define gen5off 0x0020
#define gen6off 0x0040
#define gen7off 0x0080
#define gen8off 0x0100
#define gen9off 0x0200
#define gen10off 0x0400
#define gen11off 0x0800
#define gen12off 0x1000
#define gen13off 0x2000
#define gen14off 0x4000

/* genStatus Codes */
#define genAvail 0x0000                 /* Generator available status */
#define ffSynth 0x0100                  /* Free Form Synthesizer status */
#define noteSynth 0x0200                /* Note Synthesizer status */
#define lastBlock 0x8000                /* Last block of wave */

/* Jump Table Offsets */
#define smReadRegister 0x00             /* Read Register routine */
#define smWriteRegister 0x04            /* Write Register routine */
#define smReadRam 0x08                  /* Read Ram routine */
#define smWriteRam 0x0C                 /* Write Ram routine */
#define smReadNext 0x10                 /* Read Next routine */
#define smWriteNext 0x14                /* Write Next routine */
#define smOscTable 0x18                 /* Pointer to Oscillator table */
#define smGenTable 0x1C                 /* Pointer to generator table */
#define smGcbAddrTable 0x20             /* Pointer to GCB address table */
#define smDisableInc 0x24               /* Disable Increment routine */

struct SoundParamBlock {
   Pointer waveStart;                   /* starting address of wave */
   Word waveSize;                       /* waveform size in pages */
   Word freqOffset;                     /* ? formula to be provided */
   Word docBuffer;                      /* DOC buffer start address, low byte = 0 */
   Word bufferSize;                     /* DOC buffer start address, low byte = 0 */
   struct SoundParamBlock *nextWavePtr; /* Pointer to start of next wave's parameter block */
   Word volSetting;                     /* DOC volume setting. High byte = 0 */
   };
typedef struct SoundParamBlock SoundParamBlock, *SoundPBPtr, **SoundPBHndl;

struct DocRegParamBlk {
   Word oscGenType;
   Byte freqLow1;
   Byte freqHigh1;
   Byte vol1;
   Byte tablePtr1;
   Byte control1;
   Byte tableSize1;
   Byte freqLow2;
   Byte freqHigh2;
   Byte vol2;
   Byte tablePtr2;
   Byte control2;
   Byte tableSize2;
   };
typedef struct DocRegParamBlk DocRegParamBlk, *DocRegParamBlkPtr;

extern pascal void SoundBootInit(void) inline(0x0108,dispatcher);
extern pascal void SoundStartUp(Word) inline(0x0208,dispatcher);
extern pascal void SoundShutDown(void) inline(0x0308,dispatcher);
extern pascal Word SoundVersion(void) inline(0x0408,dispatcher);
extern pascal void SoundReset(void) inline(0x0508,dispatcher);
extern pascal Boolean SoundToolStatus(void) inline(0x0608,dispatcher);
extern pascal Word FFGeneratorStatus(Word) inline(0x1108,dispatcher);
extern pascal Boolean FFSoundDoneStatus(Word) inline(0x1408,dispatcher);
extern pascal Word FFSoundStatus(void) inline(0x1008,dispatcher);
extern pascal void FFStartSound(Word, Pointer) inline(0x0E08,dispatcher);
extern pascal void FFStopSound(Word) inline(0x0F08,dispatcher);
extern pascal Word GetSoundVolume(Word) inline(0x0C08,dispatcher);
extern pascal Pointer GetTableAddress(void) inline(0x0B08,dispatcher);
extern pascal void ReadRamBlock(Pointer, Word, Word) inline(0x0A08,dispatcher);
extern pascal void SetSoundMIRQV(VoidProcPtr) inline(0x1208,dispatcher);
extern pascal void SetSoundVolume(Word, Word) inline(0x0D08,dispatcher);
extern pascal ProcPtr SetUserSoundIRQV(VoidProcPtr) inline(0x1308,dispatcher);
extern pascal void WriteRamBlock(Pointer, Word, Word) inline(0x0908,dispatcher);

extern pascal void FFSetUpSound(Word, Pointer) inline(0x1508,dispatcher);
extern pascal void FFStartPlaying(Word) inline(0x1608,dispatcher);
extern pascal void ReadDOCReg(Pointer) inline(0x1808,dispatcher);
extern pascal void SetDOCReg(Pointer) inline(0x1708,dispatcher);

#endif
