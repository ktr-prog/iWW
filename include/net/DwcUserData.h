#ifndef NET_DWCUSERDATA_H
#define NET_DWCUSERDATA_H

#include "types.h"


typedef struct DwcLoginId {
    /* 0x0 */ u32 v[3];
} DwcLoginId;

typedef struct DwcUserData {
    /* 0x00 */ u8 unk_00[4];
    /* 0x04 */ DwcLoginId tempLoginId;
    /* 0x10 */ DwcLoginId loginId;
    /* 0x1c */ u32 profileId;
    /* 0x20 */ u8 unk_20[4];
    /* 0x24 */ u32 gameCode;
} DwcUserData;

#endif
