#include "nitro/fs.h"
#include "types.h"
#include "nnsys/snd_arc.h"
#include "sys/CmdSeq.h"
#include "sys/FndList.h"
#include "snd/Player.h"
#include "snd/SndSeqHandle.h"
#include "snd/SndSeGroup.h"
#include "proto/autoload_2/unk_020ed8cc.h"
#include "proto/autoload_2/unk_020ede18.h"
#include "proto/autoload_2/unk_021093f4.h"
#include "proto/autoload_2/unk_0210c084.h"
#include "proto/main/unk_0206d49c.h"

extern "C" {
void NNS_SndHandleInit(SndSeqHandle *h);
void NNS_SndPlayerStopSeq(SndSeqHandle *h, s32 frames);
void NNS_SndHeapLoadState(void *heap, s32 level);
s32 NNS_SndHeapGetCurrentLevel(void *heap);
s32 NNS_SndHeapSaveState(void *heap);
void *NNS_SndHeapAlloc(void *heap, u32 size, void (*cb)(void *, u32, void *, u32), void *a, u32 b);
void *NNS_SndHeapCreate(void *start, u32 size);
void NNS_SndArcInit(NNSSndArc *arc, const char *path, void *heap, BOOL loadSymb);
void NNS_SndArcInitOnMemory(NNSSndArc *arc, void *base);
void NNS_SndCaptureStartOutputEffect(void *buf, u32 size, s32 effect);

void SndSeGroupList_StopAll(FndList *o);
void SndSeSystem_UnloadGroup(Player *o);
void SndSeGroup_Shutdown(Group *g);
extern NNSSndArc data_021f5a1c;
extern NNSSndArc data_021f5aac;
}

extern "C" void SndSeSystem_Shutdown(Player *o, s32 flag) {
    SndSeGroupList_StopAll(&o->list);
    if (flag != 0) SndSeSystem_UnloadGroup(o);
    o->active = 0;
}

extern "C" void SndSeSystem_UnloadGroup(Player *o) {
    if (o->groupParams.b0 == 255) Fatal_Trap();
    if (o->heapLevel == 255) return;
    Snd_RestoreHeapLevel(o->heapLevel);
}

extern "C" void SndSeGroupList_StopAll(FndList *o) {
    Group *p;
    if (o == NULL) Fatal_Trap();
    p = (Group *)SndList_GetFirst((void **)o);
    if (p == NULL) return;
    do {
        SndSeGroup_Shutdown(p);
        p = (Group *)SndList_GetNext(o, p);
    } while (p != NULL);
}

extern "C" void *Snd_GetHeap(void) {
    return gSndHeap;
}

extern "C" void Snd_InitSystem(void *heapStart, u32 heapSize, const char *arcPath, void *arcMem) {
    NNS_SndInit();
    if (gSndHeap != NULL) Fatal_Trap();
    gSndHeap = NNS_SndHeapCreate(heapStart, heapSize);
    if (gSndHeap == NULL) Fatal_Trap();
    Snd_AllocCaptureBuffer();
    if (arcPath != NULL) {
        NNS_SndArcInit(&data_021f5aac, arcPath, gSndHeap, 0);
    } else {
        if (arcMem == NULL) Fatal_Trap();
        NNS_SndArcInitOnMemory(&data_021f5a1c, arcMem);
    }
    if (NNS_SndArcPlayerSetup(gSndHeap) == 0) Fatal_Trap();
    NNS_SndHandleInit(&gSndDefaultHandle);
}

extern "C" void Snd_CaptureBufferDisposeCallback(void *mem, u32 size, void *a, u32 b) {
}

extern "C" void Snd_StartOutputEffect(s32 a) {
    if (gSndCaptureBuffer == NULL) Fatal_Trap();
    NNS_SndCaptureStartOutputEffect((void *)(((uptr)gSndCaptureBuffer + 31) & ~(uptr)31), 0x1000, a);
}

extern "C" void Snd_AllocCaptureBuffer(void) {
    gSndCaptureBuffer = NNS_SndHeapAlloc(Snd_GetHeap(), 0x1020, Snd_CaptureBufferDisposeCallback, 0, 0);
    if (gSndCaptureBuffer == NULL) Fatal_Trap();
}

extern "C" void Snd_Main(void) {
    NNS_SndMain();
}

extern "C" void Snd_StartSeqArcDefault(u32 idx, u32 arcNo) {
    Snd_StartSeqArc(idx, arcNo, &gSndDefaultHandle);
}

extern "C" void Snd_StartSeqArc(u32 idx, u32 arcNo, void *handle) {
    if (handle == NULL) Fatal_Trap();
    NNS_SndArcPlayerStartSeqArc(handle, arcNo, idx);
}

extern "C" void Snd_StartSeqArcEx(void *handle, s32 player, s32 bank, s32 prio, u32 arcNo, u32 idx) {
    if (handle == NULL) Fatal_Trap();
    NNS_SndArcPlayerStartSeqArcEx(handle, player, bank, prio, arcNo, idx);
}

extern "C" void Snd_InitHandle(void *a) {
    if (a == NULL) Fatal_Trap();
    NNS_SndHandleInit((SndSeqHandle *)a);
}

extern "C" void Snd_StopHandle(void *a, s32 frames) {
    if (a == NULL) Fatal_Trap();
    NNS_SndPlayerStopSeq((SndSeqHandle *)a, frames);
}

extern "C" s32 Snd_LoadGroup(u32 a) {
    s32 r = Snd_GetHeapLevel();
    if (NNS_SndArcLoadGroup(a, gSndHeap) == 0) return -1;
    if (NNS_SndHeapSaveState(gSndHeap) == -1) Fatal_Trap();
    return r;
}

extern "C" s32 Snd_RestoreHeapLevel(u32 a) {
    if (a == 255) Fatal_Trap();
    if (a == 0) Fatal_Trap();
    NNS_SndHeapLoadState(gSndHeap, a);
    if (a != (u32)Snd_GetHeapLevel()) Fatal_Trap();
    return Snd_GetHeapLevel();
}

extern "C" s32 Snd_GetHeapLevel(void) {
    return NNS_SndHeapGetCurrentLevel(gSndHeap);
}

extern "C" void CmdSeq_Undo(CmdSeq *o) {
    s16 *pi;
    if (o->cmds == NULL) return;
    if (o->state == 0) return;
    pi = &o->cmdIndex;
    o->cmdIndex -= 1;
    while (o->cmdIndex >= 0) {
        o->vfunc_0c(o->cmds[o->cmdIndex]);
        *pi -= 1;
    }
}

void *gSndHeap;
SndSeqHandle gSndDefaultHandle;
void *gSndCaptureBuffer;
Player gSndSeSystem;
NNSSndArc data_021f5a1c;
NNSSndArc data_021f5aac;
