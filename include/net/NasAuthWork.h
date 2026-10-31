#ifndef NET_NASAUTHWORK_H
#define NET_NASAUTHWORK_H

#include "types.h"
#include "net/DwcHttp.h"
#include "net/NasAuthParams.h"
#include "sys/OSThread.h"


typedef struct NasUserIdInfo NasUserIdInfo;
struct NasUserIdInfo {
    /* 0x00 */ u64 userId;
    /* 0x08 */ u64 tempUserId;
    /* 0x10 */ u16 password;
};

typedef struct NasAuthWork NasAuthWork;
struct NasAuthWork {
    /* 0x000 */ u32 unk_00;
    /* 0x004 */ s32 state;
    /* 0x008 */ s32 resultCode;
    /* 0x00c */ char returnCd[4];
    /* 0x010 */ char datetime[0xf];
    /* 0x01f */ char locator[0x33];
    /* 0x052 */ char token[0x12d];
    /* 0x17f */ char challenge[9];
    /* 0x188 */ char cookie[0x41];
    /* 0x1c9 */ u8 pad_1c9[0x1cc - 0x1c9];
    /* 0x1cc */ NasAuthParams config;
    /* 0x1f8 */ DwcHttpField httpFields[0x20];
    /* 0x2f8 */ DwcHttp *http;
    /* 0x2fc */ OSThread thread;
    /* 0x3bc */ OSMutex mutex;
    /* 0x3d4 */ s32 isAborting;
    /* 0x3d8 */ u8 unk_3d8[8];
    /* 0x3e0 */ u8 stack[0x1000];
};

#endif
