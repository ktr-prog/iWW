#ifndef SND_SNDBGMVIEWS_H
#define SND_SNDBGMVIEWS_H

#include "types.h"

typedef struct Rb Rb;

struct Rb {
    /* 0x00 */ void *handle;
    /* 0x04 */ u16 h4;
    /* 0x06 */ u16 h6;
    /* 0x08 */ u8 c8;
    /* 0x09 */ s8 c9;
    /* 0x0a */ s8 c10;
    /* 0x0b */ s8 c11;
    /* 0x0c */ s8 c12;
    /* 0x0d */ s8 c13;
    /* 0x0e */ s8 c14;
    /* 0x0f */ u8 c15;
    /* 0x10 */ u8 c16;
};

#endif
