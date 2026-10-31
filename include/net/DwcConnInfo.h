#ifndef NET_DWCCONNINFO_H
#define NET_DWCCONNINFO_H

#include "types.h"

#ifndef __cplusplus
typedef struct DwcConnInfo DwcConnInfo;
#endif

struct DwcConnInfo {
    /* 0x0 */ u8 slotIndex;
    /* 0x1 */ u8 aid;
    /* 0x2 */ u16 unk_02;
    /* 0x4 */ u32 unk_04;
};

#endif
