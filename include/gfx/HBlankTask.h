#ifndef GFX_HBLANKTASK_H
#define GFX_HBLANKTASK_H

#include "types.h"


struct HBlankTask {
    /* 0x00 */ u8 taskState;
    /* 0x01 */ u8 pad_01[3];
    /* 0x04 */ void (*unk_04)();
    /* 0x08 */ void (*unk_08)();
    /* 0x0c */ void (*param)();
    /* 0x10 */ void (*nextParam)();
    /* 0x14 */ void (*unk_14)();
    /* 0x18 */ HBlankTask *next;
};

#endif
