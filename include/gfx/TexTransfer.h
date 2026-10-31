#ifndef GFX_TEXTRANSFER_H
#define GFX_TEXTRANSFER_H

#include "types.h"

struct TexTransfer {
    /* 0x00 */ u32 dstAddr;
    /* 0x04 */ void *src;
    /* 0x08 */ u32 size;

    u8 getResCost(void);
    u8 getTexCost(void);
    void loadTexResource(void);
    void loadTexPltt(void);
    void loadTex(void);
    void set(u32 dst, void *src, u32 size);
    void clear(void);
};

#endif
