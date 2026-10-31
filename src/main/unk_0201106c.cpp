#include "types.h"
#include "gfx/HudObjGfx.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_0201106c.h"

extern "C" {
void DC_FlushRange(void *p, u32 size);
void GX_LoadOBJ(void *p, u32 src, u32 size);
void GXS_LoadOBJ(void *p, u32 src, u32 size);
BOOL FS_OpenFile(void *self, const void *path);
BOOL FS_SeekFile(void *self, u32 off, s32 z);
s32 FS_ReadFile(void *self, void *dst, u32 size);
BOOL FS_CloseFile(void *self);
}



extern const char sHudObjCharPathTen2[];
const char sHudObjCharPathTen2[] = "/a_mes/a_mes_ten2_obj_ncg.bin";

u32 sSlideIconCharOffsets[5] = {0x28c0, 0x100, 0x140, 0x180, 0x1c0};

void HudObjGfxIo::releaseKindChars() {
    freeChars();
}

void HudObjGfxIo::uploadKindChars(s32 which) {
    BOOL w, f1, f2;
    u32 src;
    s32 i;
    DC_FlushRange(charBuf, 0x500);
    w = which == 0;
    f1 = w || which == 1;
    f2 = w || which == 2;
    src = 0x1000;
    for (i = 0; (u32)i < 2; i++, src += 0x400) {
        u8 *p = charBuf + i * 0x280;
        if (f1) GX_LoadOBJ(p, src, 0x280);
        if (f2) GXS_LoadOBJ(p, src, 0x280);
    }
}

BOOL HudObjGfxIo::loadCameraButtonChars(s32 alt) {
    BOOL a = FS_OpenFile(this, alt != 0 ? sHudObjCharPathTen2 : ((HudObjGfx *)this)->getCharPath(2));
    BOOL ok;
    s32 z1 = 0, z2 = 0, z3 = 0, z4 = 0;
    u32 src;
    s32 i;
    ok = TRUE;
    if (alt != 0) {
        src = 0;
    } else {
        src = 0x180;
    }
    for (i = 0; (u32)i < 2; i++, src += 0x400) {
        if (!FS_SeekFile(this, src, z1)) ok = z2;
        if (FS_ReadFile(this, cameraButtonChars + i * 0x100, 0x100) == ~z4) ok = z3;
    }
    BOOL r = FS_CloseFile(this);
    if (a && ok && r) return TRUE;
    return FALSE;
}

void HudObjGfxIo::uploadCameraButtonChars(s32 which) {
    BOOL w, f1, f2;
    u32 src;
    s32 i;
    DC_FlushRange(cameraButtonChars, 0x200);
    w = which == 0;
    f1 = w || which == 1;
    f2 = w || which == 2;
    src = 0x1180;
    for (i = 0; (u32)i < 2; i++, src += 0x400) {
        u8 *p = cameraButtonChars + i * 0x100;
        if (f1) GX_LoadOBJ(p, src, 0x100);
        if (f2) GXS_LoadOBJ(p, src, 0x100);
    }
}

BOOL HudObjGfxIo::loadLinkIconChars(s32 alt) {
    BOOL a = FS_OpenFile(this, alt != 0 ? sHudObjCharPathTen2 : ((HudObjGfx *)this)->getCharPath(4));
    BOOL ok;
    s32 z1 = 0, z2 = 0, z3 = 0, z4 = 0;
    u32 src;
    s32 i;
    charBuf = (u8 *)Mem_AllocTail(0x200);
    ok = TRUE;
    if (alt != 0) {
        src = 0x200;
    } else {
        src = 0x2300;
    }
    for (i = 0; (u32)i < 2; i++, src += 0x400) {
        if (!FS_SeekFile(this, src, z1)) ok = z2;
        if (FS_ReadFile(this, charBuf + i * 0x100, 0x100) == ~z4) ok = z3;
    }
    BOOL r = FS_CloseFile(this);
    if (a && ok && r) return TRUE;
    return FALSE;
}

void HudObjGfxIo::uploadLinkIconChars() {
    u32 src;
    s32 i;
    DC_FlushRange(charBuf, 0x200);
    src = 0x3300;
    for (i = 0; (u32)i < 2; i++, src += 0x400) {
        u8 *p = charBuf + i * 0x100;
        GX_LoadOBJ(p, src, 0x100);
        GXS_LoadOBJ(p, src, 0x100);
    }
}

void HudObjGfxIo::releaseLinkIconChars() {
    freeChars();
}

BOOL HudObjGfxIo::loadSlideIconChars(s32 alt) {
    BOOL a = FS_OpenFile(this, alt == 0 ? ((HudObjGfx *)this)->getCharPath(1) : sHudObjCharPathTen2);
    BOOL ok;
    s32 z1 = 0, z2 = 0, z3 = 0, z4 = 0;
    u32 src;
    s32 i;
    charBuf = (u8 *)Mem_AllocTail(0x80);
    ok = TRUE;
    src = sSlideIconCharOffsets[alt];
    for (i = 0; (u32)i < 2; i++, src += 0x400) {
        if (!FS_SeekFile(this, src, z1)) ok = z2;
        if (FS_ReadFile(this, charBuf + i * 0x40, 0x40) == ~z4) ok = z3;
    }
    BOOL r = FS_CloseFile(this);
    if (a && ok && r) return TRUE;
    return FALSE;
}

void HudObjGfxIo::uploadSlideIconChars() {
    u32 src;
    s32 i;
    DC_FlushRange(charBuf, 0x80);
    src = 0x38c0;
    for (i = 0; (u32)i < 2; i++, src += 0x400) {
        u8 *p = charBuf + i * 0x40;
        GX_LoadOBJ(p, src, 0x40);
        GXS_LoadOBJ(p, src, 0x40);
    }
}

void HudObjGfxIo::releaseSlideIconChars() {
    freeChars();
}
