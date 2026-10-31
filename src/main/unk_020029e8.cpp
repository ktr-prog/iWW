#include "uptr.h"
#include "types.h"
#include "Unk_020d8c7c.h"
#include "gfx/ToonTable.h"
#include "gfx/Mtx43.h"
#include "actor/ActorListNode.h"
#include "gfx/AbAllObjGfx.h"
#include "npc/VillagerId.h"
#include "actor/Actor.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_02105d50.h"
#include "proto/autoload_2/unk_0210fa84.h"
#include "proto/autoload_2/unk_02110c98.h"
#include "proto/autoload_2/unk_02119434.h"
#include "proto/main/unk_020027b4.h"
#include "proto/main/unk_020029e8.h"
#include "proto/main/unk_02002b1c.h"
#include "proto/main/unk_02003008.h"
#include "proto/main/unk_0202e840.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_020a427c.h"
#include "proto/main/unk_020d477c.h"

extern "C" {
void DC_FlushRange(void *p, u32 n);
void GX_LoadOBJ(void *p, u32 a, u32 b);
void GXS_LoadOBJ(void *p, u32 a, u32 b);
void GX_LoadOBJPltt(void *p, u32 a, u32 b);
void GXS_LoadOBJPltt(void *p, u32 a, u32 b);
}


AbAllObjGfx sAbAllObjGfx;


AbAllObjGfx::AbAllObjGfx() : paletteBuf(0), charBuf(0) {}

AbAllObjGfx::~AbAllObjGfx() {
    freePalette();
    freeChars();
}

extern "C" void AbAllObjGfx_Upload(void) {
    AbAllObjGfx *p = &sAbAllObjGfx;
    AbAllObjGfx_InitFile(p);
    BOOL a = p->loadPalette();
    BOOL b = p->loadChars();
    if (a) p->uploadPalette();
    if (b) p->uploadChars();
    p->freePalette();
    p->freeChars();
}

extern "C" void AbAllObjGfx_InitFile(AbAllObjGfx *p) { FS_InitFile(&p->file); }

BOOL AbAllObjGfx::loadPalette() {
    paletteBuf = File_Load("/ab_all/ab_all_obj_ncl.bin");
    if (paletteBuf) return TRUE;
    return FALSE;
}

BOOL AbAllObjGfx::loadChars() {
    void *p = File_Load("/ab_all/ab_all_obj_ncg.bin");
    charBuf = p;
    if (p) return TRUE;
    return FALSE;
}

void AbAllObjGfx::freePalette() {
    if (paletteBuf) {
        Mem_Free(paletteBuf);
        paletteBuf = 0;
    }
}

void AbAllObjGfx::freeChars() {
    if (charBuf) {
        Mem_Free(charBuf);
        charBuf = 0;
    }
}

void AbAllObjGfx::uploadPalette() {
    DC_FlushRange(paletteBuf, 0x80);
    GX_LoadOBJPltt(paletteBuf, 0, 0x80);
    GXS_LoadOBJPltt(paletteBuf, 0, 0x80);
}

void AbAllObjGfx::uploadChars() {
    DC_FlushRange(charBuf, 0x1000);
    GX_LoadOBJ(charBuf, 0, 0x1000);
    GXS_LoadOBJ(charBuf, 0, 0x1000);
}

