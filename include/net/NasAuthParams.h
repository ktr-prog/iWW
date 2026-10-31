#ifndef NET_NASAUTHPARAMS_H
#define NET_NASAUTHPARAMS_H

#include "types.h"
#include "net/DwcHttp.h"


typedef struct NasAuthParams NasAuthParams;
struct NasAuthParams {
    /* 0x00 */ u8 inGameName[0x16];
    /* 0x16 */ char gsbrcd[14];
    /* 0x24 */ DwcAllocFunc allocFunc;
    /* 0x28 */ DwcFreeFunc freeFunc;
};

#endif
