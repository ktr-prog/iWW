#ifndef GFX_TEXPATVRAMANIM_H
#define GFX_TEXPATVRAMANIM_H

#include "types.h"
#include "gfx/AnimFrameCtrl.h"
#include "gfx/TexVramTask.h"


struct ResName16 {
    /* 0x00 */ char chars[17];
    ResName16();
    ~ResName16();
    char *get();
    void set(const char *src);
};

class TexPatVramTasks {
public:
    TexPatVramTasks();
    ~TexPatVramTasks();

    /* 0x00 */ TexVramTask tasks[2];
};

class TexPatVramAnim : public AnimFrameCtrl {
public:
    /* 0x18 */ TexPatVramTasks vramTasks;
    /* 0x50 */ u8 *dstTex;
    /* 0x54 */ ResName16 texName;
    /* 0x65 */ ResName16 plttName;
    /* 0x78 */ u8 *srcTex;
    /* 0x7c */ u8 *patAnm;
    /* 0x80 */ s32 curPlttIdx;
    /* 0x84 */ s32 curTexIdx;
    /* 0x88 */ s32 prevTexIdx;
    /* 0x8c */ u8 plttOnly;

    TexPatVramAnim();
    virtual ~TexPatVramAnim();
    void clear();
    void getFrameIndices(s32 *a, s32 *b);
    BOOL update();
    BOOL init(u8 *hdr, const char *n1, const char *n2, u8 *x, u8 *y, u8 flag);
};

#endif
