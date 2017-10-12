#pragma once

#ifndef __TYPES__
#include <types.h>
#endif

#ifndef __HASH__
#define __HASH__


typedef struct md2WorkBlock {
    unsigned char cksum[16];   /* checksum of the data block */
    unsigned char state[48];   /* intermediate digest state  */
    unsigned char buffer[16];  /* data block being processed */
    unsigned long left;        /* amount of data in buffer   */
} md2WorkBlock, *md2WorkBlockPtr;

typedef struct md4WorkBlock {
    unsigned long count[2];    /* message length in bits, lsw first */
    unsigned long abcd[4];	   /* digest buffer */
    unsigned char buf[64];	   /* accumulate block */
} md4WorkBlock, *md4WorkBlockPtr;

typedef struct md5WorkBlock {
    unsigned long count[2];	   /* message length in bits, lsw first */
    unsigned long abcd[4];	   /* digest buffer */
    unsigned char buf[64];	   /* accumulate block */
} md5WorkBlock, *md5WorkBlockPtr;

typedef struct sha1WorkBlock {
  unsigned long digest[5];              /* Message digest */
  unsigned long count_low, count_high;  /* 64-bit block count */
  unsigned char block[64];              /* SHA1 data buffer */
  unsigned long index;                  /* index into buffer */
} sha1WorkBlock, *sha1WorkBlockPtr;

typedef union mdWorkBlock{
     md2WorkBlock;
     md4WorkBlock;
     md5WorkBlock;
     sha1WorkBlock;
} mdWorkBlock, *mdWorkBlockPtr;

extern pascal void hashBootInit(void) inline(0x0180,dispatcher);
extern pascal void hashStartUp(void) inline(0x0280,dispatcher);
extern pascal void hashShutDown(void) inline(0x0380,dispatcher);
extern pascal Word hashVersion(void) inline(0x0480,dispatcher);
extern pascal void hashReset(void) inline(0x0580,dispatcher);
extern pascal void md5Init(md5WorkBlockPtr) inline(0x0980,dispatcher);
extern pascal void md5Append(md5WorkBlockPtr, Pointer, long) inline(0x0A80,dispatcher);
extern pascal void md5Finish(md5WorkBlockPtr, Pointer) inline(0x0B80,dispatcher);
extern pascal void md4Init(md4WorkBlockPtr) inline(0x0C80,dispatcher);
extern pascal void md4Append(md4WorkBlockPtr, Pointer, long) inline(0x0D80,dispatcher);
extern pascal void md4Finish(md4WorkBlockPtr, Pointer) inline(0x0E80,dispatcher);
extern pascal void md2Init(md2WorkBlockPtr) inline(0x0F80,dispatcher);
extern pascal void md2Update(md2WorkBlockPtr, Pointer, long) inline(0x1080,dispatcher);
extern pascal void md2Final(md2WorkBlockPtr, Pointer) inline(0x1180,dispatcher);
extern pascal void sha1Init(sha1WorkBlockPtr) inline(0x1280,dispatcher);
extern pascal void sha1Update(sha1WorkBlockPtr, Pointer, long) inline(0x1380,dispatcher);
extern pascal void sha1Final(sha1WorkBlockPtr, Pointer) inline(0x1480,dispatcher);


#endif
