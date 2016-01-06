/********************************************
*
* Media Control Tool Set
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

#ifndef __MEDIACONTROL__
#define __MEDIACONTROL__

/* Position unit types for MCGetPosition and other calls: */
#define mcInChapters 1                  /* Position is measured in chapters */
#define mcInFrames 2                    /* Position is measured in frames */
#define mcInTimes 3                     /* Position is measured in hours,minutes,seconds,blocks */

/* Control values for MCControl: */
#define mcCInit 0x0001                  /* Initialize player */
#define mcCEject 0x0002                 /* Eject disc */
#define mcCVideoOn 0x0003               /* Turn video on */
#define mcCVideoOff 0x0004              /* Turn video off */
#define mcCDisplayOn 0x0005             /* Turn video position display on */
#define mcCDisplayOff 0x0006            /* Turn video position display off */
#define mcCBlankVideo 0x0007            /* Blank video for next MCSearchTo */
#define mcCDefaultCom 0x0008            /* Set default communications */
#define mcCLockDev 0x0009               /* Set the device to locked */
#define mcCUnLockDev 0x000A             /* Unlock the device */

#define mcC8Data1Stop 0x0028            /* Set 8 - data  1 - stop bit */
#define mcC7Data1Stop 0x0029            /* Set 7 - data  1 - stop bit */
#define mcC6Data1Stop 0x002A            /* Set 6 - data  1 - stop bit */
#define mcC5Data1Stop 0x002B            /* Set 5 - data  1 - stop bit */
#define mcC8Data2Stop 0x002C            /* Set 8 - data  2 - stop bit */
#define mcC7Data2Stop 0x002D            /* Set 7 - data  2 - stop bit */
#define mcC6Data2Stop 0x002E            /* Set 6 - data  2 - stop bit */
#define mcC5Data2Stop 0x002F            /* Set 5 - data  2 - stop bit */

#define mcCBaudDflt 0x0032              /* Set baud rate to control panel setting */
#define mcCBaud50 0x0033                /* Set 50 baud */
#define mcCBaud75 0x0034                /* Set 75 baud */
#define mcCBaud110 0x0035               /* Set 110 baud */
#define mcCBaud134 0x0036               /* Set 134 baud */
#define mcCBaud150 0x0037               /* Set 150 baud */
#define mcCBaud300 0x0038               /* Set 300 baud */
#define mcCBaud600 0x0039               /* Set 600 baud */
#define mcCBaud1200 0x003A              /* Set 1200 baud */
#define mcCBaud1800 0x003B              /* Set 1800 baud */
#define mcCBaud2400 0x003C              /* Set 2400 baud */
#define mcCBaud3600 0x003D              /* Set 3600 baud */
#define mcCBaud4800 0x003E              /* Set 4800 baud */
#define mcCBaud7200 0x003F              /* Set 7200 baud */
#define mcCBaud9600 0x0040              /* Set 9600 baud */
#define mcCBaud19200 0x0041             /* Set 19200 baud */

#define mcCModem 0x0064                 /* Set to modem port */
#define mcCPrinter 0x0065               /* Set to printer port */

#define mcCIgnoreDS 0x00C8              /* Ignore "disk switched" GSOS errors */
#define mcCReportDS 0x00C9              /* Report "disk switched" GSOS errors */

/* Values for MCGetFeatures: */
#define mcFTypes 0                      /* How the disc is organized (frames, chapters, etc.) */
#define mcFStep 1                       /* Maximum fps speed value (normal is 255) */
#define mcFRecord 2                     /* Device supports MCRecord */
#define mcFVideo 3                      /* Device supports toggling video */
#define mcFEject 4                      /* Device supports ejecting medium */
#define mcFLock 5                       /* Device supports user lock (locking user from physically operating the device) */
#define mcFVDisplay 6                   /* Device supports video display of location */
#define mcFVOverlay 7                   /* No. of lines of overlay characters device supports */
#define mcFVOChars 8                    /* No. of chars/line supported by overlay */
#define mcFVolume 9                     /* Does volume control? */


/* Status values for MCGetStatus: */
#define mcSUnknown 0x0000               /* Player unable to determine this status */

#define mcSDeviceType 0x0000            /* "Device type" selector */
#define mcSLaserDisc 0x0001             /* Video laser disc player */
#define mcSCDAudio 0x0002               /* Audio CD player */
#define mcSCDLaserCD 0x0003             /* Combination laser/CD player */
#define mcSVCR 0x0004                   /* VCR */
#define mcSCamCorder 0x0005             /* Video camera */

#define mcSPlayStatus 0x0001            /* "Play status" selector */
#define mcSPlaying 0x0001               /* The device is playing */
#define mcSStill 0x0002                 /* The device is not playing (paused) */
#define mcSParked 0x0003                /* The device is shut down */

#define mcSDoorStatus 0x0002            /* "Player door" status */
#define mcSDoorOpen 0x0001
#define mcSDoorClosed 0x0002

#define mcSDiscType 0x0003              /* "Disc type" selector */
#define mcS_CLV 0x0001
#define mcS_CAV 0x0002
#define mcS_CDV 0x0003
#define mcS_CD 0x0004

#define mcSDiscSize 0x0004              /* "Disc size" selector */
#define mcSDisc3inch 0x0003
#define mcSDisc5inch 0x0005
#define mcSDisc8inch 0x0008
#define mcSDisc12inch 0x000C

#define mcSDiscSide 0x0005              /* "Disc side" selector */
#define mcSSideOne 0x0001
#define mcSSideTwo 0x0002

#define mcSVolumeL 0x0006               /* Current left volume selector */
#define mcSVolumeR 0x0007               /* Current right volume selector */

/* Time parameter values for MCGetTimes: */
#define mcElapsedTrack 0x0000           /* Elapsed time on current track/chapter */
#define mcRemainTrack 0x0001            /* Remaining time on current track/chapter */
#define mcElapsedDisc 0x0002            /* Elapsed time on disc */
#define mcRemainDisc 0x0003             /* Remaining time on disc */
#define mcTotalDisc 0x0004              /* Total run time on disc */
#define mcTotalFrames 0x0005            /* Total number of frames on disc */
#define mcTracks 0x0006                 /* Binary start and ending track numbers (bits 31-16 = ending, bits 15-0 = starting track number.) */
#define mcDiscID 0x0007                 /* returns a disc identifier */

/* Audio values: */
#define mcAudioOff 0x0000               /* Audio off */
#define mcAudioRight 0x0001             /* Audio thru right channel only */
#define mcAudioLinR 0x0002              /* Audio left in right only */
#define mcAudioMinR 0x0003              /* Audio mixed in right only */
#define mcAudioRinL 0x0004              /* Audio right in left only */
#define mcAudioRinLR 0x0005             /* Audio right in left and right */
#define mcAudioReverse 0x0006           /* Audio right in left, left in right */
#define mcAudioRinLMR 0x0007            /* Audio right in left, mixed in right */
#define mcAudioLeft 0x0008              /* Audio left channel only */
#define mcAudioStereo 0x0009            /* Audio both channels (in stereo) */
#define mcAudioLinLR 0x000A             /* Audio left in left and right */
#define mcAudioLinLMR 0x000B            /* Audio left in left, mixed in right */
#define mcAudioMinL 0x000C              /* Audio mixed in left only */
#define mcAudioMinLRinR 0x000D          /* Audio mixed in left, right in right */
#define mcAudioMinLLinR 0x000E          /* Audio mixed in left, left in right */
#define mcAudioMonaural 0x000F          /* Audio mixed in left and right (monaural) */

/* Error codes: */
#define mcUnImp 0x2601                  /* Unimplemented for this device */
#define mcNotApplic 0x2601              /* <see UnImp> */
#define mcBadSpeed 0x2602               /* Invalid speed specified */
#define mcBadUnitType 0x2603            /* Invalid unit type specified */
#define mcTimeOutErr 0x2604             /* Timed out during device read */
#define mcNotLoaded 0x2605              /* No driver is currently loaded */
#define mcBadAudio 0x2606               /* Invalid audio value */
#define mcDevRtnError 0x2607            /* Device returned error (unable to perform) */
#define mcUnRecStatus 0x2608            /* Unrecognizable status from device */
#define mcBadSelector 0x2609            /* Invalid selector value specified */
#define mcFunnyData 0x260A              /* Funny data received (try again) */
#define mcInvalidPort 0x260B            /* Invalid port specified */
#define mcOnlyOnce 0x260C               /* Scans only once */
#define mcNoResMgr 0x260D               /* Resource manager not active */
#define mcItemNotThere 0x260E           /* Item not found in database */
#define mcWasShutDown 0x260F            /* Media Control Toolset was already shut down */
#define mcWasStarted 0x2610             /* Media Control Toolset was already started */
#define mcBadChannel 0x2611             /* Invalid channel number */
#define mcInvalidParam 0x2612           /* Invalid parameter */
#define mcCallNotSupported 0x2613       /* Call is not supported */

extern pascal void MCBootInit(void) inline(0x0126,dispatcher);
extern pascal void MCStartUp(Word) inline(0x0226,dispatcher);
extern pascal void MCShutDown(void) inline(0x0326,dispatcher);
extern pascal Word MCVersion(void) inline(0x0426,dispatcher);
extern pascal void MCReset(void) inline(0x0526,dispatcher);
extern pascal Boolean MCStatus(void) inline(0x0626,dispatcher);
extern pascal Long MCBinToTime(Long) inline(0x0D26,dispatcher);
extern pascal void MCControl(Word, Word) inline(0x1B26,dispatcher);
extern pascal void MCDShutDown(Word) inline(0x1526,dispatcher);
extern pascal void MCDStartUp(Word, Ptr, Word) inline(0x1426,dispatcher);
extern pascal Long MCGetDiscID(Word) inline(0x2826,dispatcher);
extern pascal void MCGetDiscTitle(Long, Ptr) inline(0x1226,dispatcher);
extern pascal Long MCGetDiscTOC(Word, Word) inline(0x2726,dispatcher);
extern pascal void MCGetErrorMsg(Word, Ptr) inline(0x0926,dispatcher);
extern pascal Long MCGetFeatures(Word, Word) inline(0x1626,dispatcher);
extern pascal void MCGetName(Word, Ptr) inline(0x2D26,dispatcher);
extern pascal Word MCGetNoTracks(Word) inline(0x2926,dispatcher);
extern pascal Long MCGetPosition(Word, Word) inline(0x2426,dispatcher);
extern pascal void MCGetProgram(Long, Ptr) inline(0x1026,dispatcher);
extern pascal void MCGetSpeeds(Word, Ptr) inline(0x1D26,dispatcher);
extern pascal Word MCGetStatus(Word, Word) inline(0x1A26,dispatcher);
extern pascal Long MCGetTimes(Word, Word) inline(0x2626,dispatcher);
extern pascal void MCGetTrackTitle(Long, Word, Ptr) inline(0x0E26,dispatcher);
extern pascal void MCJog(Word, Long, Word) inline(0x2026,dispatcher);
extern pascal void MCLoadDriver(Word) inline(0x0A26,dispatcher);
extern pascal void MCPause(Word) inline(0x1826,dispatcher);
extern pascal void MCPlay(Word) inline(0x1726,dispatcher);
extern pascal void MCRecord(Word) inline(0x2A26,dispatcher);
extern pascal void MCScan(Word, Word) inline(0x1C26,dispatcher);
extern pascal Boolean MCSearchDone(Word) inline(0x2226,dispatcher);
extern pascal void MCSearchTo(Word, Word, Long) inline(0x2126,dispatcher);
extern pascal void MCSearchWait(Word) inline(0x2326,dispatcher);
extern pascal void MCSendRawData(Word, Long) inline(0x1926,dispatcher);
extern pascal void MCSetAudio(Word, Word) inline(0x2526,dispatcher);
extern pascal void MCSetDiscTitle(Long, Long) inline(0x1326,dispatcher);
extern pascal void MCSetProgram(Long, Long) inline(0x1126,dispatcher);
extern pascal void MCSetTrackTitle(Long, Word, Ptr) inline(0x0F26,dispatcher);
extern pascal void MCSetVolume(Word, Word, Word) inline(0x2E26,dispatcher);
extern pascal void MCSpeed(Word, Word) inline(0x1E26,dispatcher);
extern pascal void MCStop(Word) inline(0x2B26,dispatcher);
extern pascal void MCStopAt(Word, Word, Long) inline(0x1F26,dispatcher);
extern pascal Long MCTimeToBin(Long) inline(0x0C26,dispatcher);
extern pascal void MCUnLoadDriver(Word) inline(0x0B26,dispatcher);
extern pascal void MCWaitRawData(Word, Ptr, Word, Word) inline(0x2C26,dispatcher);

#endif
