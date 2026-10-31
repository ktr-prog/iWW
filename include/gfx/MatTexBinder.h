#ifndef GFX_MATTEXBINDER_H
#define GFX_MATTEXBINDER_H

#include "types.h"

struct MatTexBinder {
    /* 0x00 */ u8 *resMdl;
    /* 0x04 */ s8 matIdx;

    MatTexBinder();
    ~MatTexBinder();
    void clear();
    BOOL hasMaterial();
    BOOL setMaterial(u8 *hdr, s32 idx);
    BOOL setMaterialByName(u8 *hdr, const char *name);
    s8 getMaterial();
    BOOL bindPltt(u8 *hdr2, s32 idx2);
    BOOL bindPlttByName(u8 *hdr2, const char *name);
    BOOL bindTex(u8 *hdr2, s32 idx2);
    BOOL bindTexByName(u8 *hdr2, const char *name);
    BOOL bindByIdx(u8 *hdr2, s32 a, s32 idx);
    BOOL bindByName(u8 *hdr2, const char *n, const char *n2);
};

#endif
