#ifndef SYS_OVERLAYSLOT_H
#define SYS_OVERLAYSLOT_H

#include "types.h"

#ifndef __cplusplus
typedef struct OverlaySlot OverlaySlot;
#endif

struct OverlaySlot {
    /* 0x0 */ u8 overlayId;
    /* 0x1 */ u8 refCount;
    /* 0x2 */ u8 unk_02;
    /* 0x4 */ u32 ramStart;
    /* 0x8 */ u32 ramSize;
};

#endif
