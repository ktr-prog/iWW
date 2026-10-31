#ifndef NET_GPERSIST_H
#define NET_GPERSIST_H

#include "types.h"


typedef void (*PersAuthCallbackFn)(s32, s32, s32, void *, s32);
typedef void (*PersDataCallbackFn)(s32, s32, s32, s32, s32, s32, void *, s32, s32);
typedef void (*PersDataSaveCallbackFn)(s32, s32, s32, s32, s32, s32, s32);
typedef void (*ProfileCallbackFn)(s32, s32, s32, s32);

struct serverreq_t {
    /* 0x00 */ u32 reqtype;
    /* 0x04 */ s32 localid;
    /* 0x08 */ s32 profileid;
    /* 0x0c */ s32 pdtype;
    /* 0x10 */ s32 pdindex;
    /* 0x14 */ s32 instance;
    /* 0x18 */ void *callback;
};

struct GsPersistErrorMsg {
    /* 0x00 */ u8 b[16];
};

#endif
