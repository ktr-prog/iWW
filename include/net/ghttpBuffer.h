#ifndef NET_GHTTPBUFFER_H
#define NET_GHTTPBUFFER_H

#include "types.h"


struct GHIConnection;
#ifndef __cplusplus
typedef struct GHIConnection GHIConnection;
typedef struct GHIBuffer GHIBuffer;
#endif

struct GHIBuffer {
    /* 0x00 */ GHIConnection *connection;
    /* 0x04 */ char *data;
    /* 0x08 */ s32 size;
    /* 0x0c */ s32 len;
    /* 0x10 */ s32 pos;
    /* 0x14 */ s32 sizeIncrement;
    /* 0x18 */ s32 fixed;
    /* 0x1c */ s32 dontFree;
    /* 0x20 */ s32 isEncrypted;
};

#endif
