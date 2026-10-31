#include "types.h"
#include "proto/autoload_2/unk_021093f4.h"
#include "proto/autoload_2/unk_0210c084.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_02223fc4.h"
#include "proto/ov001/unk_ov001_02226f68.h"

#include "nitro/fs.h"
#include "snd/SndSeqHandle.h"

struct WfcSoundArc {
    u8 header[0x30];
    s32 fromFile;
    FSFile file;
    FSFileID id;
    void *fat;
    void *symb;
    void *info;
};

struct WfcSound {
    WfcSoundArc arc;
    SndSeqHandle handle;
    void *data;
    void *task;
};

#pragma thumb off

extern "C" {
s32 NNS_SndPlayerStopSeq(SndSeqHandle *, u32);
s32 NNS_SndPlayerSetTrackPitch(SndSeqHandle *, s32, s32);
s32 NNS_SndPlayerSetVolume(SndSeqHandle *, s32);
s32 NNS_SndArcInitOnMemory(WfcSoundArc *, void *);
s32 NNS_SndHandleInit(SndSeqHandle *);
void WfcHeap_FreeAndClear(void *);
void *WfcHeap_Alloc(u32, u32);

}

WfcSound *sWfcSound;

void WfcSound_Init()
{
    u32 t;
    sWfcSound = (WfcSound *)WfcHeap_Alloc(sizeof(WfcSound), 4);
    sWfcSound->data = WfcFs_LoadFile((void *)"sound/sound_data.sdat.l", &t, 0x20);
    NNS_SndInit();
    NNS_SndArcInitOnMemory(&sWfcSound->arc, sWfcSound->data);
    NNS_SndArcPlayerSetup(0);
    NNS_SndHandleInit(&sWfcSound->handle);
    sWfcSound->task = WfcTask_Add(0, (void *)WfcSound_MainTask, 0, 0xc8);
}

void WfcSound_Shutdown()
{
    WfcTask_RequestDelete(0, sWfcSound->task);
    WfcHeap_FreeAndClear(&sWfcSound);
}

s32 WfcSound_Play(s32 a) { return NNS_SndArcPlayerStartSeqArc(&sWfcSound->handle, 0, a); }

void WfcSound_SetVolume(s32 a) { NNS_SndPlayerSetVolume(&sWfcSound->handle, a); }

void WfcSound_SetTrackPitch(s32 a, s32 b) { NNS_SndPlayerSetTrackPitch(&sWfcSound->handle, a, b); }

void WfcSound_Stop() { NNS_SndPlayerStopSeq(&sWfcSound->handle, 0); }

void WfcSound_MainTask() { NNS_SndMain(); }

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0221e930) {
    HOST_OVERLAY_VAR(sWfcSound),
    HOST_OVERLAY_VARS_END
};
