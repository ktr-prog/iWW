#ifndef SYS_OVERLAYHANDLE_H
#define SYS_OVERLAYHANDLE_H

#include "types.h"

class OverlayHandle {
public:
    /* 0x00 */ s32 overlayId;
    /* 0x04 */ u8 isLoading;
    /* 0x05 */ u8 pad_05[0x7c - 0x05];
    OverlayHandle() { overlayId = -1; }
    ~OverlayHandle();
};

#endif
