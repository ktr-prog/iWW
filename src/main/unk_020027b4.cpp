#include "uptr.h"
#include "types.h"
#include "Unk_020d8c7c.h"
#include "gfx/ToonTable.h"
#include "gfx/Mtx43.h"
#include "actor/ActorListNode.h"
#include "gfx/AbAllObjGfx.h"
#include "npc/VillagerId.h"
#include "actor/Actor.h"
#include "nitro/io_access.h"
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

typedef volatile u16 vu16;
typedef volatile u32 vu32;




extern "C" {
}


extern "C" {
extern u8 data_02135934[];
}

extern "C" {
extern u32 sAbAllObjCharPath[];
}

extern "C" {
extern u32 sAbAllObjPalettePath[];
}

extern "C" {
extern u32 sPersonalityFileNameFmt[];
}

extern "C" {
}

extern "C" {
extern s16 data_02135f44[];
}

extern "C" {
extern u32 **gProfileTable;
}

extern "C" {
extern u32 gSaveTownId;
}

extern "C" {
extern u32 sPersonalityVoiceTypes[];
}

extern "C" {
}

extern "C" {
extern u8 gViewFrustum[];
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
void G3X_SetClearColor(u16 a, u32 b, u32 c, u32 d, u32 e);
}

extern "C" {
void DC_FlushRange(void *p, u32 n);
}

extern "C" {
}

extern "C" {
void MTX_Inverse43(void *a, void *b);
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
void OS_EnableDTCM(void);
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
void G3i_PerspectiveW_(s32 fovySin, s32 fovyCos, s32 aspect, s32 near, s32 far, s32 scale, s32 load, s32 *mtx);
}

extern "C" {
}

extern "C" {
void GX_LoadOBJ(void *p, u32 a, u32 b);
}

extern "C" {
void GXS_LoadOBJ(void *p, u32 a, u32 b);
}

extern "C" {
void GX_LoadOBJPltt(void *p, u32 a, u32 b);
}

extern "C" {
void GXS_LoadOBJPltt(void *p, u32 a, u32 b);
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
void List_Remove(void *list, void *node);
}

extern "C" {
void List_PushBack(void *list, void *node);
}

extern "C" {
void Mtx43_SetTranslate(void *m, s32 a, s32 b, s32 c);
}

extern "C" {
void Mtx43_RotateX(void *m, s32 a);
}

extern "C" {
void Mtx43_RotateY(void *m, s32 a);
}

extern "C" {
void Math_Atan2(s32 a, s32 b);
}

extern "C" {
s32 func_01ffcb0c(s32 a, s32 b);
}

extern "C" {
void VEC_Add(void *a, void *b, void *c);
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
u32 Villager_GetSpeciesName(u32 a, u32 b);
}

extern "C" {
}

extern "C" {
void MI_CpuFill8(void *p, u32 v, u32 n);
}

extern "C" {
void *ProcList_FindByProfile(void *list, u32 id, void *p);
}

extern "C" {
void *ProcList_FindById(void *list, u32 id);
}

extern "C" {
}

extern "C" {
s32 func_02039eb8(void *a, void *b, void *c, void *d, void *e);
}

extern "C" {
void func_020030b4_dummy(void);
}



extern Mtx43 data_02135934_;

u16 sGfx3dClearColor;
u32 sGfx3dClearDepth;
u8 gViewMtxInv[0x30];
Mtx43 gViewMtx;











extern "C" void Gfx3d_InitEngine(void) {
    G3X_Init();
    G3X_InitTable();
    G3X_InitMtxStack();
    IO_AND((vu16 *)0x4000060, 0xffffcffd);
    IO_W((vu16 *)0x4000060, (IO_R((vu16 *)0x4000060) & 0xffffcfff) | 0x10);
    IO_W((vu16 *)0x4000060, (IO_R((vu16 *)0x4000060) & 0xffffcfff) | 8);
    IO_AND((vu16 *)0x4000060, 0xcfdf);
    IO_W((vu32 *)0x4000580, 0xbfff0000);
    G3i_PerspectiveW_(0x579, 0xf09, 0x1555, 0x1000, 0x3e8000, 0x1000, 1, 0);
    IO_W((vu32 *)0x400044c, 0);
    IO_W((vu32 *)0x4000540, 3);
    NNS_G3dInit();
    Gfx3d_LoadDefaultToonTable();
    G3X_SetClearColor(0, 0, 0x7fff, 0x3f, 1);
    sGfx3dClearColor = 0;
    sGfx3dClearDepth = 0x7fff;
}

extern "C" void Gfx3d_Init(void) {
    Gfx3d_InitEngine();
    GX_SetBankForTex(6);
    GX_SetBankForTexPltt(0x10);
    OS_EnableDTCM();
    IO_W((vu16 *)0x4000060, (IO_R((vu16 *)0x4000060) & 0xffffcfff) | 4);
    IO_W((vu16 *)0x4000340, 0);
    IO_W((vu16 *)0x4000060, (IO_R((vu16 *)0x4000060) & 0xffffcfff) | 8);
    G3X_SetClearColor(0, 0, 0x7fff, 0, 1);
    gViewMtx = *(Mtx43 *)data_02135934;
    MTX_Inverse43(&gViewMtx, gViewMtxInv);
}

extern "C" void Gfx3d_BeginFrame(void) {
    G3X_Reset();
    IO_W((vu32 *)0x4000440, 3);
    IO_W((vu32 *)0x4000454, 0);
    IO_W((vu32 *)0x4000440, 2);
}

extern "C" void Gfx3d_SetViewMatrix(Mtx43 *src) {
    gViewMtx = *src;
    MTX_Inverse43(&gViewMtx, gViewMtxInv);
}

extern "C" void Gfx3d_LoadDefaultToonTable(void) {
    ToonTable buf = *(ToonTable *)sDefaultToonTable;
    DC_FlushRange(&buf, 0x40);
    vu16 *reg = (vu16 *)0x4000060;
    IO_W(reg, IO_R(reg) & 0xffffcffd);
    G3X_SetToonTable(&buf);
}

extern "C" void Gfx3d_SetClearDepth(u32 v) { sGfx3dClearDepth = v; }

extern "C" void Gfx3d_SetClearColor(u16 v) { sGfx3dClearColor = v; }

extern "C" void Gfx3d_ApplyClearColor(void) {
    G3X_SetClearColor(sGfx3dClearColor, 0, sGfx3dClearDepth, 0x3f, 1);
}


extern "C" BOOL Gfx2d_IsMainScreenLayer(u32 x) {
    if (x <= 2 || x == 7) return TRUE;
    return FALSE;
}

