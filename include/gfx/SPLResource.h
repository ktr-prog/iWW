#ifndef GFX_SPLRESOURCE_H
#define GFX_SPLRESOURCE_H

#include "types.h"
#include "gfx/VecFx32.h"


struct SPLResBase {
    /* 0x00 */ u32 flag;
    /* 0x04 */ VecFx32 pos;
    /* 0x10 */ u8 pad_10[0x40];
    /* 0x50 */ u8 tintFlags;
};

struct SPLResource {
    /* 0x00 */ SPLResBase *p_base;
};

#endif
