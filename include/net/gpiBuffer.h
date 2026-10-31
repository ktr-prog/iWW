#ifndef NET_GPIBUFFER_H
#define NET_GPIBUFFER_H

#include "types.h"


struct GPIBuffer {
    /* 0x0 */ char *buffer;
    /* 0x4 */ s32 size;
    /* 0x8 */ s32 len;
    /* 0xc */ s32 pos;
};

#endif
