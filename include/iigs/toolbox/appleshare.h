/********************************************
; File: AppleShare.h
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

#ifndef __GSOS__
#include <gsos.h>
#endif

#ifndef __APPLESHARE__
#define __APPLESHARE__


/* Command Numbers */
#define ASBufferControl 0x0001
#define ASByteRangeLock 0x0002
#define ASSpecialOpenFork 0x0003
#define ASGetPrivileges 0x0004
#define ASSetPrivileges 0x0005
#define ASUserInfo 0x0006
#define ASCopyFile 0x0007
#define ASGetUserPath 0x0008
#define ASOpenDesktop 0x0009
#define ASCloseDesktop 0x000A
#define ASGetComment 0x000B
#define ASSetComment 0x000C
#define ASGetSrvrName 0x000D

/* Error Codes */
#define appleShareNetError 0x8888  /* AppleShare Network Error */
#define unknownUser 0x007E  /* specified user name not registered */
#define unknownGroup 0x007F  /* specified group name not the name of a group */

/* Masks */
#define lockRange 0x8000
#define relativeToEOF 0x4000
#define seeFolders 0x01
#define seeFiles 0x02
#define makeChanges 0x0004
#define folderOwner 0x80

/* File Info Masks */
#define onDesktop 0x0001
#define bFOwnAppl 0x0002  /* used internally */
#define bFNever 0x0010  /* never SwitchLaunch */
#define bFAlways 0x0020  /* always SwitchLaunch */
#define shareApplication 0x0040  /* set if file is a shareable application */
#define fileIsInited 0x0100  /* seen by Finder */
#define fileHasChanged 0x0200  /* used internally by Finder */
#define fileIsBusy 0x0400  /* copied from File System busy bit */
#define fileNoCopy 0x0800  /* not used in 5.0 and later, formally BOZO */
#define fileIsSystem 0x1000  /* set if file is a system file */
#define fileHasBundle 0x2000
#define fileIsInvisible 0x4000
#define fileIsLocked 0x8000

/* Window Info Masks */
#define inTrashWindow 0xFFFD
#define inDesktopWindow 0xFFFE
#define inDiskWindow 0x0000

/* accessWord Masks */
#define requestReadAccess 0x0001
#define requestWriteAccess 0x0002
#define denyReadAccess 0x0010
#define denyWriteAccess 0x0020

/* forkNum Masks */
#define dataForkNum 0x0000
#define resourceForkNum 0x0001

/* Other Constants */
#define disableBuffering 0x8000
#define enableBuffering 0x0000
struct BufferControlRec {
   Word pCount;
   Word fstNum;
   Word commandNum;
   Word refNum; /*   */
   Word flags; /*   */
} ;
typedef struct BufferControlRec BufferControlRec, *BufferControlRecPtr;
struct SpecialOpenForkRec {
   Word pCount;
   Word fstNum;
   Word commandNum;
   Word refNum;
   GSString255Ptr pathname;
   Word accessMode;
   Word forkNum;
} ;
typedef struct SpecialOpenForkRec SpecialOpenForkRec, *SpecialOpenForkRecPtr;
struct ByteRangeLockRec {
   Word pCount;
   Word fstNum;
   Word commandNum;
   Word refNum;
   Word lockFlag;
   LongWord fileOffset;
   LongWord rangeLength; /*   */
   LongWord rangeStart; /*   */
} ;
typedef struct ByteRangeLockRec ByteRangeLockRec, *ByteRangeLockRecPtr;
struct GetAccessRightsRec {
   Byte userSummary;
   Byte world;
   Byte group;
   Byte owner;
} ;
typedef struct GetAccessRightsRec GetAccessRightsRec, *GetAccessRightsRecPtr;
struct GetPrivilegesRec {
   Word pCount;
   Word fstNum;
   Word commandNum;
   GSString255Ptr pathname;
   GetAccessRightsRec accessRights;
   ResultBuf255Ptr ownerName;
   ResultBuf255Ptr groupName;
} ;
typedef struct GetPrivilegesRec GetPrivilegesRec, *GetPrivilegesRecPtr;
struct SetAccessRightsRec {
   Byte reserved;
   Byte world;
   Byte group;
   Byte owner;
} ;
typedef struct SetAccessRightsRec SetAccessRightsRec, *SetAccessRightsRecPtr;
struct SetPrivilegesRec {
   Word pCount;
   Word fstNum;
   Word commandNum;
   GSString255Ptr pathname;
   SetAccessRightsRec accessRights;
   ResultBuf255Ptr ownerName;
   ResultBuf255Ptr groupName;
} ;
typedef struct SetPrivilegesRec SetPrivilegesRec, *SetPrivilegesRecPtr;
struct UserInfoRec {
   Word pCount;
   Word fstNum;
   Word commandNum;
   Word deviceNum;
   ResultBuf255Ptr userName;
   ResultBuf255Ptr primaryGroupName;
} ;
typedef struct UserInfoRec UserInfoRec, *UserInfoRecPtr;
struct CopyFileRec {
   Word pCount;
   Word fstNum;
   Word commandNum;
   GSString255Ptr sourcePathname;
   GSString255Ptr destPathname;
} ;
typedef struct CopyFileRec CopyFileRec, *CopyFileRecPtr;
struct GetUserPathRec {
   Word pCount;
   Word fstNum;
   Word commandNum;
   GSString255Ptr prefix;
} ;
typedef struct GetUserPathRec GetUserPathRec, *GetUserPathRecPtr;
struct DesktopRec {
   Word pCount;
   Word fstNum;
   Word commandNum;
   Word desktopRefNum;
   GSString255Ptr pathname;
} ;
typedef struct DesktopRec DesktopRec, *DesktopRecPtr;
struct GetCommentRec {
   Word pCount;
   Word fstNum;
   Word commandNum;
   Word desktopRefNum;
   GSString255Ptr pathname;
   ResultBuf255Ptr comment;
} ;
typedef struct GetCommentRec GetCommentRec, *GetCommentRecPtr;
struct SetCommentRec {
   Word pCount;
   Word fstNum;
   Word commandNum;
   Word desktopRefNum;
   GSString255Ptr pathname;
   GSString255Ptr comment;
} ;
typedef struct SetCommentRec SetCommentRec, *SetCommentRecPtr;
struct GetServerNameRec {
   Word pCount;
   Word fstNum;
   Word commandNum;
   GSString255Ptr pathname;
   ResultBuf255Ptr serverName;
   ResultBuf255Ptr zoneName;
} ;
typedef struct GetServerNameRec GetServerNameRec, *GetServerNameRecPtr;
struct ASOptionListRec {
   Word bufferSize; /*   */
   Word dataSize; /*   */
   Word theFileSysID; /*   */
   Byte finderInfo[32]; /*   */
   LongWord parentDirID; /*   */
   LongWord accessRights; /*   */
} ;
typedef struct ASOptionListRec ASOptionListRec, *ASOptionListRecPtr;
#endif
