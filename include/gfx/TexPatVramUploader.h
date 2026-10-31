#ifndef GFX_TEXPATVRAMUPLOADER_H
#define GFX_TEXPATVRAMUPLOADER_H

#include "types.h"
#include "gfx/TexVramTask.h"

struct TexPatVramUploader {
    TexVramTask tasks[2];
    BOOL uploadByName(u8 *hdr, const char *n1, const char *n2, u8 *x, s32 a, s32 b);
    BOOL uploadByIdx(u8 *hdr, s32 i1, s32 i2, u8 *x, s32 a, s32 b);
};

#endif
