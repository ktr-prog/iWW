#include "types.h"
#include "gfx/HudObjGfx.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_02011410.h"
#include "proto/main/unk_020116e0.h"

extern "C" {
void DC_FlushRange(void *p, u32 size);
void GX_LoadOBJ(void *p, u32 src, u32 size);
void GXS_LoadOBJ(void *p, u32 src, u32 size);
void GX_LoadOBJPltt(void *p, u32 src, u32 size);
void GXS_LoadOBJPltt(void *p, u32 src, u32 size);
BOOL FS_OpenFile(FSFile *file, const char *path);
BOOL FS_SeekFile(FSFile *file, s32 off, s32 whence);
s32 FS_ReadFile(FSFile *file, void *dst, s32 len);
BOOL FS_CloseFile(FSFile *file);
}



const char *HudObjGfx::getCharPath(s32 mode) {
    if (mode >= 4) mode = Hud_GetSceneHudKind();
    const char *b = "/a_mes/a_mes_ten0_obj_ncg.bin";
    const char *a = "/a_mes/a_mes_ten1_obj_ncg.bin";
    const char *c = "/a_mes/a_mes_ten3_obj_ncg.bin";
    const char *r = "/a_mes/a_mes_obj_ncg.bin";
    if (mode == 2) r = a;
    else if (mode == 3) r = b;
    else if (countdownVariant != 0) r = c;
    return r;
}

BOOL HudObjGfx::loadPalette(s32 mode) {
    BOOL opened = FS_OpenFile(&file, getPalettePath(mode));
    BOOL ok;
    paletteBuf = (u8 *)Mem_AllocTail(0x180);
    if (paletteBuf != NULL) {
        ok = FS_ReadFile(&file, paletteBuf, 0x180) != -1 ? TRUE : FALSE;
    } else {
        ok = FALSE;
    }
    BOOL closed = FS_CloseFile(&file);
    if (opened != 0 && ok != 0 && closed != 0 && paletteBuf != NULL) return TRUE;
    return FALSE;
}

BOOL HudObjGfx::loadChars() {
    BOOL opened = FS_OpenFile(&file, getCharPath(4));
    BOOL ok;
    charBuf = (u8 *)Mem_AllocTail(0x3000);
    if (charBuf != NULL) {
        ok = FS_ReadFile(&file, charBuf, 0x3000) != -1 ? TRUE : FALSE;
    } else {
        ok = FALSE;
    }
    BOOL closed = FS_CloseFile(&file);
    if (opened != 0 && ok != 0 && closed != 0 && charBuf != NULL) return TRUE;
    return FALSE;
}

void HudObjGfxIo::freePalette() {
    if (paletteBuf != NULL) {
        Mem_Free(paletteBuf);
        paletteBuf = NULL;
    }
}

void HudObjGfxIo::freeChars() {
    if (charBuf != NULL) {
        Mem_Free(charBuf);
        charBuf = NULL;
    }
}

void HudObjGfxIo::uploadPalette(s32 which) {
    u8 *base;
    u8 *p2;
    DC_FlushRange(paletteBuf, 0x180);
    base = paletteBuf;
    p2 = base + 0x160;
    if ((u32)which <= 1) {
        GX_LoadOBJPltt(base, 0x80, 0x100);
        GX_LoadOBJPltt(p2, 0x1e0, 0x20);
    }
    if (which == 0 || which == 2) {
        GXS_LoadOBJPltt(base, 0x80, 0x100);
        GXS_LoadOBJPltt(p2, 0x1e0, 0x20);
    }
}

void HudObjGfxIo::uploadChars(s32 which) {
    DC_FlushRange(charBuf, 0x3000);
    if ((u32)which <= 1) {
        GX_LoadOBJ(charBuf, 0x1000, 0x3000);
    }
    if (which == 0 || which == 2) {
        GXS_LoadOBJ(charBuf, 0x1000, 0x3000);
    }
}

BOOL HudObjGfxIo::loadKindChars(s32 k) {
    BOOL a = FS_OpenFile(&file, static_cast<HudObjGfx *>(this)->getCharPath(k));
    BOOL ok;
    s32 z1 = 0, z2 = 0, z3 = 0, z4 = 0, z5 = 0;
    u32 src;
    s32 i;
    charBuf = (u8 *)Mem_AllocTail(0x500);
    ok = TRUE;
    if (charBuf != NULL) {
        src = z1;
        for (i = 0; (u32)i < 2; i++, src += 0x400) {
            if (!FS_SeekFile(&file, src, z1)) ok = z2;
            if (FS_ReadFile(&file, charBuf + i * 0x280, 0x280) == ~z4) ok = z3;
        }
    }
    BOOL r = FS_CloseFile(&file);
    if (a && ok && r && charBuf != NULL) return TRUE;
    return FALSE;
}

