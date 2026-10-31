#include "types.h"
#include "snd/SndMgr.h"
#include "proto/autoload_2/unk_020ed8cc.h"
#include "proto/autoload_2/unk_020ef150.h"
#include "proto/autoload_2/unk_020f0dec.h"
#include "proto/autoload_2/unk_0210b1b0.h"
#include "proto/itcm/unk_01ffa4a0.h"
#include "proto/main/unk_0206d49c.h"


SndMgr gSndMgr;

extern "C" {
void *NNS_SndHeapCreate(void *a, u32 b);
u32 CARD_GetThreadPriority(void);
void NNS_SndCaptureCreateThread(u32 a);
void NNS_SndSetMasterVolume(u32 a);
void NNS_SndArcStrmInit(u32 a, void *b);
void NNS_SndStrmHandleInit(void *p);
void NNS_SndCaptureChangeOutputEffect(u32 a);
}

SndMgr::SndMgr() {
    randState = OS_GetTick();
    randMul = 0x5d588b65;
    randAdd = 0x00269ec3;
    seDisabled = 0;
    menuDuck = 0;
    keepHeap = 0;
}

void SndMgr::init(void *heap, u32 size, const char *arcPath) {
    subHeap = NULL;
    if (subHeap != NULL) Fatal_Trap();
    subHeap = NNS_SndHeapCreate(heap, 0x339c);
    if (subHeap == NULL) Fatal_Trap();
    Snd_InitSystem((u8 *)heap + 0x339c, size - 0x339c, arcPath, NULL);
    NNS_SndCaptureCreateThread(CARD_GetThreadPriority() - 1);
    outputMode = 1;
    startOutputEffect();
    NNS_SndSetMasterVolume(127);
    NNS_SndArcStrmInit(10, Snd_GetHeap());
    NNS_SndStrmHandleInit(&strmHandle);
    Snd_LoadGroup(0);
    Snd_InitHandle(&voiceHandle);
    Snd_InitHandle(&seHandle);
    Snd_InitHandle(&bgmHandle);
    Snd_InitHandle(&auxSeHandle);
    beatSync = 0;
    trackMask = 0;
    strmTotalTime = 0;
    variantTimer = -1;
    crossTrackMask = 0;
    pan = 0;
    keySeMode = 0;
}

void SndMgr::update() {
    Snd_Main();
    SndMgr_UpdateVoice(this);
    SndMgr_UpdateTrackRamps(this);
    SndMgr_UpdateVolumeRamps(this);
}

void SndMgr::volumeOff() {
    NNS_SndSetMasterVolume(0);
}

void SndMgr::volumeOn() {
    NNS_SndSetMasterVolume(127);
}

void SndMgr::setOutputMode(u32 v) {
    outputMode = v;
    NNS_SndCaptureChangeOutputEffect(outputMode);
}

void SndMgr::startOutputEffect() {
    Snd_StartOutputEffect(outputMode);
}

void SndMgr::stopAll() {
    NNS_SndCaptureStopEffect();
}

#include "host_labels.h"

HOST_LABEL_DEFINE(data_021f5be0, (char *)&gSndMgr.menuDuck);
HOST_LABEL_DEFINE(gSndBgmHandle, (char *)&gSndMgr.bgmHandle.p);
