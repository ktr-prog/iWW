#ifndef GFX_BGVRAMTASK_H
#define GFX_BGVRAMTASK_H

#include "types.h"
#include "gfx/VramTask.h"
#include "gfx/BgTransfer.h"

class BgVramTask : public VramTask {
public:
    /* 0x10 */ BgTransfer xfer;

    BgVramTask();
    virtual BOOL execute();
    virtual void clear();
    BOOL requestPaletteRange(void *a, u8 b, u32 c, u8 d);
    BOOL requestPalette(void *a, u8 b, u32 c);
    BOOL requestScreen(void *a, u8 b, u32 c, u32 d);
    BOOL requestChars(void *a, u8 b, u32 c, u32 d, u32 e);
    void prepare(void);
    void cancel(void);
};

class BgVramTaskPair : public BgVramTask {
public:
    /* 0x24 */ BgTransfer xfer2;

    BgVramTaskPair();
    virtual BOOL execute();
    virtual void clear();
    BOOL requestCharsAndPalette(void *a, u8 b, u32 c, u32 d, u32 e, void *f, u8 g);
    BOOL requestCharPair(void *a, void *b, u8 c, u32 d, u32 e, u32 f, u32 g);
};

#endif
