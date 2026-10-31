#ifndef GFX_TEXVRAMSLOT_H
#define GFX_TEXVRAMSLOT_H

#include "types.h"

class TexVramSlot {
public:
    /* 0x04 */ u32 texKeyBase;
    /* 0x08 */ u32 tex4x4KeyBase;
    /* 0x0c */ u32 plttKeyBase;
    /* 0x10 */ u8 unk_10;
    /* 0x11 */ u8 unk_11;

    TexVramSlot();
    virtual ~TexVramSlot();
    void setKeys(u32 a, u32 b, u32 c);
    void clear(void);
    void relocateTexture(void *p);
    u32 makePlttKeyAt(u32 a, u32 b);
    u32 makeKeyAtOffset(u32 a, u32 b, u32 c);
    u32 makeTex4x4KeyAt(u32 a, u32 b);
    u32 makeTexKeyAt(u32 a, u32 b);
    u32 makePlttKey(u32 a);
    u32 makeKeyWithBase(u32 a, u32 b);
    u32 makeTex4x4Key(u32 a);
    u32 makeTexKey(u32 a);
    BOOL alloc(u32 texSize, u32 tex4x4Size, u32 plttSize);
};

#endif
