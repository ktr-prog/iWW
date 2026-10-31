#ifndef NET_WIFIAPCONTROL_H
#define NET_WIFIAPCONTROL_H

#include "types.h"


struct WifiApControl {
    /* 0x00 */ void *(*unk_00)(u32, u32);
    /* 0x04 */ void (*unk_04)(u32, void *, u32);
    /* 0x08 */ u8 allocMask;
    /* 0x09 */ u8 state;
    /* 0x0a */ u8 errorState;
    /* 0x0b */ u8 anyApFound;
    /* 0x0c */ u32 errorCode;
    /* 0x10 */ s32 netCheckError;
    /* 0x14 */ u8 furthestApStatus;
    /* 0x15 */ u8 furthestApIndex;
    /* 0x16 */ u8 furthestState;
    /* 0x17 */ u8 connectedApType;
};

#endif
