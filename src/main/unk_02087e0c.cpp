#include "types.h"
#include "proto/main/unk_02087e0c.h"
#include "proto/main/unk_02087e60.h"


extern "C" {
extern const s32 sOamObjHeights[12];

}

extern "C" const s32 sOamObjHeights[12] = {8, 0x10, 0x20, 0x40, 8, 8, 0x10, 0x20, 0x10, 0x20, 0x20, 0x40};

extern "C" s32 Oam_GetObjWidth(u32 *p) {
    u32 v = *p;
    return Oam_GetWidth((v << 16) >> 30, v >> 30);
}

extern "C" s32 Oam_GetHeight(s32 a, s32 b) {
    return sOamObjHeights[b + (a << 2)];
}

extern "C" s32 Oam_GetObjHeight(u32 *p) {
    u32 v = *p;
    return Oam_GetHeight((v << 16) >> 30, v >> 30);
}

extern "C" s32 Oam_GetObjX(const void *obj) {
    s32 v = (*(const u32 *)obj << 7) >> 23;
    if (v >= 0x100) {
        v -= 0x200;
    }
    return v;
}

extern "C" s32 Oam_GetObjY(const void *obj) {
    return *(const s8 *)obj;
}
