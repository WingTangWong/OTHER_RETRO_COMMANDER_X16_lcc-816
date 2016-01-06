/********************************************
; File: ProDOS.h
;
;
; Copyright Apple Computer, Inc.1986-90
; All Rights Reserved
;
********************************************/

#pragma once

#ifndef __TYPES__
#include <types.h>
#endif

#ifndef __PRODOS__
#define __PRODOS__


/* Error Codes */
#define invalidCallNum 0x0001  /* invalid call number */
#define unclaimedIntErr 0x01  /* fatal error - unclaimed interrupt */
#define badPBlockPtr 0x05  /* call pointer out of bounds */
#define pdosActiveErr 0x06  /* ProDOS is active */
#define pdosBusyErr 0x07  /* ProDOS is busy */
#define vcbUnusable 0x0A  /* fatal error - VCB unusable */
#define fcbUnusable 0x0B  /* fatal error - FCB unusable */
#define badBlockZero 0x0C  /* fatal error - block zero allocated illegally */
#define shdwInterruptErr 0x0D  /* fatal error - interrupt occured while I/O shadowing off */
#ifndef devNotFound  /* device not found */
#define devNotFound 0x10
#endif
#define badDevRefNum 0x11  /* invalid device reference number */
#define osVersionErr 0x11  /* Wrong OS version */
#define badReqCode 0x20  /* invalid request code */
#define intTableFull 0x25  /* interrupt table full */
#define invalidOperation 0x26  /* invalid operation */
#define ioError 0x27  /* I/O error */
#define noDevConnect 0x28  /* no device connected */
#define writeProtectErr 0x2B  /* write protect error */
#define diskSwitchErr 0x2E  /* disk switched error */
#define badPathname 0x40  /* invalid pathname syntax */
#define fcbFullErr 0x42  /* FCB full error */
#define badFileRefNum 0x43  /* invalid file reference number */
#ifndef pathNotFound  /* path not found */
#define pathNotFound 0x44
#endif
#define volumeNotFound 0x45  /* volume not found */
#ifndef fileNotFound  /* file not found */
#define fileNotFound 0x46
#endif
#define dupFileName 0x47  /* duplicate file name */
#define volumeFullErr 0x48  /* volume full error */
#define dirFullErr 0x49  /* directory full error */
#define versionErr 0x4A  /* version error (incompatible file format) */
#ifndef badStoreType  /* unsupported (or incorrect) storage type */
#define badStoreType 0x4B
#endif
#ifndef eofEncountered  /* end-of-file encountered */
#define eofEncountered 0x4C
#endif
#define positionRangeErr 0x4D  /* position out of range */
#define accessErr 0x4E  /* access not allowed */
#define fileOpenErr 0x50  /* file is open */
#define dirDamaged 0x51  /* directory structure is damaged */
#define badVolType 0x52  /* unsupported volume type */
#ifndef paramRangeErr  /* parameter out of range */
#define paramRangeErr 0x53
#endif
#define memoryFullErr 0x54  /* out of memory */
#define vcbFullErr 0x55  /* VCB full error */
#define dupVolumeErr 0x57  /* duplicate volume error */
#define notBlkDevErr 0x58  /* not a blocked device */
#ifndef invalidLevel  /* invalid level */
#define invalidLevel 0x59
#endif
#define blkNumRangeErr 0x5A  /* block number out of range */
#define notSameVolErr 0x5B  /* different volumes found on ChangePath call */
#define notExecSysFile 0x5C  /* not an executable system file */
#define osUnavailable 0x5D  /* Operating System/file system not available */
#define deallocateRamErr 0x5E  /* Cannot deallocate /RAM */
#ifndef stackOverflow  /* Return stack overflow */
#define stackOverflow 0x5F
#endif
#define dataUnavailable 0x60  /* Data unavailable */

/* Other Constants */
#define endofDirectory 0x0061
#define P_READ_ENABLE 0x01
#define P_WRITE_ENABLE 0x02
#define P_DESTROY_ENABLE 0x80
#define P_RENAME_ENABLE 0x40
struct BlockRec {
   Word blockDevNum; /*  */
   Ptr blockDataBuffer; /*  */
   Longint blockNum; /*  */
} ;
typedef struct BlockRec BlockRec, *BlockRecPtr;
struct DevNumRec {
   Ptr devName; /*  */
   Word devNum; /*  */
} ;
typedef struct DevNumRec DevNumRec, *DevNumRecPtr;
struct DInfoRec {
   Word devNum; /*  */
   Ptr devName; /*  */
} ;
typedef struct DInfoRec DInfoRec, *DInfoRecPtr;
struct DirEntryRec {
   Word refNum;
   Word flags;
   Word base;
   Word displacement;
   Pointer nameBuffer;
   Word entryNum;
   Word fileType;
   Longint endOfFile;
   LongWord blockCount;
   TimeRec createTime;
   TimeRec modTime;
   Word access;
   LongWord auxType;
   Word fileSysID;
} ;
typedef struct DirEntryRec DirEntryRec, *DirEntryRecPtr;
struct EOFRec {
   Word eofRefNum; /*  */
   Longint eofPosition; /*  */
} ;
typedef struct EOFRec EOFRec, *EOFRecPtr;
struct FileIORec {
   Word fileRefNum; /*  */
   Ptr dataBuffer; /*  */
   Longint requestCount; /*  */
   Longint transferCount; /*  */
} ;
typedef struct FileIORec FileIORec, *FileIORecPtr;
struct FileRec {
   Ptr pathname; /*  */
   Word fAccess; /*  */
   Word fileType; /*  */
   Longint auxType; /*  */
   Word storageType; /*  */
   Word createDate; /*  */
   Word createTime; /*  */
   Word modDate; /*  */
   Word modTime; /*  */
   Longint blocksUsed; /*  */
} ;
typedef struct FileRec FileRec, *FileRecPtr;
struct FormatRec {
   Ptr devName; /* device name pointer */
   Ptr volName; /* device name pointer */
   Word fileSysID; /* file system ID */
} ;
typedef struct FormatRec FormatRec, *FormatRecPtr;
struct EraseDiskRec {
   Ptr devName; /* device name pointer */
   Ptr volName; /* device name pointer */
   Word fileSysID; /* file system ID */
} ;
typedef struct EraseDiskRec EraseDiskRec, *EraseDiskRecPtr;
struct InterruptRec {
   Word intNum; /*  */
   Ptr intCode; /*  */
} ;
typedef struct InterruptRec InterruptRec, *InterruptRecPtr;
struct MarkRec {
   Word markRefNum; /*  */
   LongWord position; /*  */
} ;
typedef struct MarkRec MarkRec, *MarkRecPtr;
struct NewLineRec {
   Word newLRefNum; /*  */
   Word enableMask; /*  */
   Word newlineChar; /*  */
} ;
typedef struct NewLineRec NewLineRec, *NewLineRecPtr;
struct OpenRec {
   Word openRefNum; /*  */
   Ptr openPathname; /*  */
   Handle ioBuffer; /*  */
} ;
typedef struct OpenRec OpenRec, *OpenRecPtr;
struct PathNameRec {
   Ptr pathname; /*  */
   Ptr newPathname; /*  */
} ;
typedef struct PathNameRec PathNameRec, *PathNameRecPtr;
struct PrefixRec {
   Word prefixNum; /*  */
   Ptr prefix; /*  */
} ;
typedef struct PrefixRec PrefixRec, *PrefixRecPtr;
struct QuitRec {
   Ptr quitPathname; /*  */
   Word flags; /*  */
} ;
typedef struct QuitRec QuitRec, *QuitRecPtr;
struct VolumeRec {
   Ptr deviceName; /*  */
   Ptr volName; /*  */
   LongWord totalBlocks; /*  */
   LongWord freeBlocks; /*  */
   Word fileSysID; /*  */
} ;
typedef struct VolumeRec VolumeRec, *VolumeRecPtr;


#define __gsos(name, parm, x) \
extern void pascal name(void *) inline(x, 0xe100b0)


__gsos(ALLOC_INTERRUPT, InterruptRec *, 0x0031);
__gsos(CHANGE_PATH, PathNameRec *, 0x0004);
__gsos(CLEAR_BACKUP_BIT, void *, 0x000B);
__gsos(CLOSE, void *, 0x0014);
__gsos(CREATE, FileRec *, 0x0001);
__gsos(D_INFO, DInfoRec *, 0x002C);
__gsos(DEALLOC_INTERRUPT, void *, 0x0032);
__gsos(DESTROY, void *, 0x0002);
__gsos(ERASE_DISK, EraseDiskRec *, 0x0025);
__gsos(FLUSH, void *, 0x0015);
__gsos(FORMAT, FormatRec *, 0x0024);
__gsos(GET_BOOT_VOL, void *, 0x0028);
__gsos(GET_DEV_NUM, DevNumRec *, 0x0020);
__gsos(GET_DIR_ENTRY, DirEntryRec *, 0x001C);
__gsos(GET_EOF, EOFRec *, 0x0019);
__gsos(GET_FILE_INFO, FileRec *, 0x0006);
__gsos(GET_LAST_DEV, void *, 0x0021);
__gsos(GET_LEVEL, void *, 0x001B);
__gsos(GET_MARK, MarkRec *, 0x0017);
__gsos(GET_NAME, void *, 0x0027);
__gsos(GET_PREFIX, PrefixRec *, 0x000A);
__gsos(GET_VERSION, void *, 0x002A);
__gsos(NEWLINE, NewLineRec *, 0x0011);
__gsos(OPEN, OpenRec *, 0x0010);
__gsos(QUIT, QuitRec *, 0x0029);
__gsos(READ_BLOCK, BlockRec *, 0x0022);
__gsos(READ, FileIORec *, 0x0012);
__gsos(SET_EOF, EOFRec *, 0x0018);
__gsos(SET_FILE_INFO, FileRec *, 0x0005);
__gsos(SET_LEVEL, void *, 0x001A);
__gsos(SET_MARK, MarkRec *, 0x0016);
__gsos(SET_PREFIX, PrefixRec *, 0x0009);
__gsos(VOLUME, VolumeRec *, 0x0008);
__gsos(WRITE_BLOCK, BlockRec *, 0x0023);
__gsos(WRITE, FileIORec *, 0x0013);

#undef __gsos

#endif
