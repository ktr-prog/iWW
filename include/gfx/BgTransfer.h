#ifndef GFX_BGTRANSFER_H
#define GFX_BGTRANSFER_H

#include "types.h"

struct BgTransfer {
    /* 0x00 */ void *buf;
    /* 0x04 */ u8 layer;
    /* 0x08 */ u32 loadArg0;
    /* 0x0c */ u32 loadArg1;
    /* 0x10 */ u32 loadArg2;

    void loadPaletteRange(void);
    void setPaletteRange(void *a, u8 b, u32 c, u8 d);
    void loadPalette(void);
    void setPalette(void *a, u8 b, u32 c);
    void loadScreen(void);
    void setScreen(void *a, u8 b, u32 c, u32 d);
    u8 getCharCost(void);
    void loadChars(void);
    void setChars(void *a, u8 b, u32 c, u32 d, u32 e);
    void clear(void);
};

#endif
