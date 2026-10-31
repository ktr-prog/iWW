#include "types.h"
#include "snd/Player.h"
#include "snd/SndSeBytes4.h"
#include "snd/SndSceneBase.h"
#include "snd/SndScenes.h"
#include "snd/SndMgr.h"
#include "snd/Melody.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/autoload_2/unk_020ed8cc.h"
#include "proto/autoload_2/unk_020edd58.h"
#include "proto/autoload_2/unk_020ef150.h"
#include "proto/autoload_2/unk_020f0dec.h"
#include "proto/autoload_2/unk_020f0fb4.h"
#include "proto/autoload_2/unk_020f30fc.h"
#include "proto/autoload_2/unk_020f4a5c.h"
#include "proto/autoload_2/unk_0210c084.h"

extern "C" {
s32 NNS_SndHeapSaveState(void *heap);
void NNS_SndHeapLoadState(void *heap, s32 level);
s32 NNS_SndHeapGetCurrentLevel(void *heap);
BOOL NNS_SndPlayerCreateHeap(s32 playerNo, void *heap, u32 size);
void NNS_SndPlayerSetPlayerVolume(s32 playerNo, s32 vol);
void NNS_SndPlayerStopSeqByPlayerNo(s32 playerNo, s32 frames);
void Snd_SetUnusedFlag(s32 v);
}

extern "C" Bytes4 data_0213b2c4 = {0x00, 0x02, 0xff, 0x00};



SndSceneBase::SndSceneBase() {
    gSndMgr.scene = this;
    gSndMgr.seDisabled = 0;
    gSndMgr.melody->b3c = 0;
    if (gSndMgr.melody != 0) MelodyPlayer_SetInstrument(gSndMgr.melody, 210);
    SndMgr_SetPlayerVolumes(&gSndMgr, 127, 127);
    NNS_SndPlayerSetPlayerVolume(15, 100);
    id = -1;
    f5 = 0;
    f6 = 0;
    Snd_SetUnusedFlag(0);
}

SndSceneBase::~SndSceneBase() {
    gSndMgr.scene = 0;
    NNS_SndHeapLoadState(gSndMgr.subHeap, 0);
}

void SndSceneBase::vfunc_08() {
}

void SndSceneBase::load() {
}

void SndSceneBase::update(s32 cameraDistance) {
    return SndMgr_UpdateVolumeCurve(&gSndMgr, cameraDistance);
}

void SndSceneBase::fadeOutAll() {
    MelodyPlayer_StopTrackB(gSndMgr.melody);
    gSndMgr.seDisabled = 1;
    stopPlayers(15);
    f5 = 1;
}

void SndSceneBase::stopPlayers(s32 v) {
    NNS_SndPlayerStopSeqByPlayerNo(11, v);
    NNS_SndPlayerStopSeqByPlayerNo(2, v);
    NNS_SndPlayerStopSeqByPlayerNo(4, v);
    NNS_SndPlayerStopSeqByPlayerNo(5, v);
    NNS_SndPlayerStopSeqByPlayerNo(6, v);
    NNS_SndPlayerStopSeqByPlayerNo(7, v);
    NNS_SndPlayerStopSeqByPlayerNo(8, v);
    NNS_SndPlayerStopSeqByPlayerNo(9, v);
    NNS_SndPlayerStopSeqByPlayerNo(10, v);
    NNS_SndPlayerStopSeqByPlayerNo(12, v);
    NNS_SndPlayerStopSeqByPlayerNo(15, v);
    NNS_SndPlayerStopSeqByPlayerNo(16, v);
    NNS_SndPlayerStopSeqByPlayerNo(17, v);
    NNS_SndPlayerStopSeqByPlayerNo(18, v);
    NNS_SndPlayerStopSeqByPlayerNo(19, v);
}

void SndSceneBase::unload() {
    Snd_ClearListenerCallbacks();
    void *t = Snd_GetHeap();
    SndSeSystem_Shutdown(&gSndSeSystem, 1);
    if (gSndMgr.keepHeap != 0) return;
    NNS_SndHeapLoadState(t, 1);
    gSndMgr.stopAll();
}

void SndSceneBase::beginTalk(s32 a) {
    s32 r;
    switch (a) {
    case 0:
    case 4:
        r = 133;
        break;
    case 1:
    case 3:
        r = 134;
        break;
    case 2:
        r = 135;
        break;
    }
    SndMgr_SetVoiceType(&gSndMgr, a);
    SndMgr_LoadBank(&gSndMgr, r);
    f6 = 1;
}

void SndSceneBase::endTalk() {
    Snd_RestoreHeapLevel(Snd_GetHeapLevel());
    f6 = 0;
}

void SndSceneBase::onBgmChange(u32 a, u32 c) {
}

void SndSceneBase::setupHeaps(u32 a, s32 b) {
    void *t = Snd_GetHeap();
    if (gSndMgr.keepHeap == 0) {
        gSndMgr.startOutputEffect();
        NNS_SndPlayerCreateHeap(0, t, a);
        NNS_SndHeapSaveState(t);
    }
    Bytes4 q = data_0213b2c4;
    q.b0 = b;
    gSndSeSystem.groupParams = q;
    SndSeSystem_Setup(&gSndSeSystem, 0, 0, q);
    Snd_InstallListenerCallbacks();
    NNS_SndHeapSaveState(t);
}

void SndSceneBase::createPlayer4Heap() {
    NNS_SndPlayerCreateHeap(4, Snd_GetHeap(), 0x206c);
}

void SndSceneBase::createPlayer11Heaps(s32 n) {
    void *t = Snd_GetHeap();
    for (s32 i = 0; i < n; i++) {
        NNS_SndPlayerCreateHeap(11, t, 0x650c);
    }
}

void SndSceneBase::createPlayer5Heap() {
    NNS_SndPlayerCreateHeap(5, Snd_GetHeap(), 0x31ac);
}

void SndSceneBase::createPlayer6Heaps() {
    void *t = Snd_GetHeap();
    for (s32 i = 0; i < 2; i++) {
        NNS_SndPlayerCreateHeap(6, t, 0x7a4c);
    }
}

void SndSceneBase::createPlayer17Heaps() {
    void *t = Snd_GetHeap();
    for (s32 i = 0; i < 4; i++) {
        NNS_SndPlayerCreateHeap(17, t, 0x356c);
    }
}

void SndSceneBase::createPlayer18And19Heaps() {
    void *t = Snd_GetHeap();
    NNS_SndPlayerCreateHeap(18, t, 0x5ecc);
    NNS_SndPlayerCreateHeap(19, t, 0x46bc);
}

void SndSceneBase::createPlayer13Heap() {
    NNS_SndPlayerCreateHeap(13, Snd_GetHeap(), 0x1f4c);
}

void SndSceneBase::createPlayer12Heaps() {
    void *t = Snd_GetHeap();
    for (s32 i = 0; i < 2; i++) {
        NNS_SndPlayerCreateHeap(12, t, 0x8cc);
    }
}

SndScene01::SndScene01() {
    if (gSndMgr.melody != 0) MelodyPlayer_SetInstrument(gSndMgr.melody, 209);
    id = 1;
    Snd_SetUnusedFlag(1);
    gSndMgr.trackVariant = 0;
}

SndScene01::~SndScene01() {
}

void SndScene01::load() {
    setupHeaps(0x21ef8, 1);
    createPlayer11Heaps(3);
    createPlayer13Heap();
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    SndMgr_LoadBank(&gSndMgr, 143);
    gSndMgr.keepHeap = 0;
}

void SndScene01::beginTalk(s32 a) {
    Snd_RestoreHeapLevel(Snd_GetHeapLevel());
    SndSceneBase::beginTalk(a);
}

void SndScene01::endTalk() {
    SndSceneBase::endTalk();
    SndMgr_LoadBank(&gSndMgr, 143);
}

void SndScene01::setBankVariant(s32 a) {
    Snd_RestoreHeapLevel(Snd_GetHeapLevel());
    if (a != 0) {
        if (a == 1) {
            SndMgr_LoadBank(&gSndMgr, 178);
        }
    } else {
        SndMgr_LoadBank(&gSndMgr, 143);
    }
}

SndScene02::SndScene02() {
    if (gSndMgr.melody != 0) MelodyPlayer_SetInstrument(gSndMgr.melody, 209);
    id = 2;
}

SndScene02::~SndScene02() {
}

void SndScene02::load() {
    setupHeaps(0x1f340, 2);
    createPlayer11Heaps(2);
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    SndMgr_LoadBank(&gSndMgr, 143);
    gSndMgr.keepHeap = 0;
}

SndScene03::SndScene03() {
    if (gSndMgr.melody != 0) MelodyPlayer_SetInstrument(gSndMgr.melody, 209);
    id = 3;
}

SndScene03::~SndScene03() {
}

void SndScene03::load() {
    setupHeaps(0x21ef8, 3);
    createPlayer11Heaps(2);
    createPlayer13Heap();
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    SndMgr_LoadBank(&gSndMgr, 143);
    gSndMgr.keepHeap = 0;
}

SndScene10::SndScene10() {
    id = 10;
    state = 0;
}

SndScene10::~SndScene10() {
}

void SndScene10::load() {
    setupHeaps(0x10ea0, 5);
    createPlayer4Heap();
    createPlayer5Heap();
    createPlayer6Heaps();
    createPlayer17Heaps();
    createPlayer18And19Heaps();
    void *t = Snd_GetHeap();
    NNS_SndArcLoadWaveArc(9, t);
    NNS_SndHeapSaveState(t);
    f1d = (u8)NNS_SndHeapGetCurrentLevel(t);
    SndMgr_LoadBank(&gSndMgr, 144);
    createPlayer12Heaps();
    NNS_SndHeapSaveState(t);
    state = 1;
    gSndMgr.keepHeap = 0;
    tempo.setMode(1);
    NNS_SndPlayerSetPlayerVolume(18, 63);
    NNS_SndPlayerSetPlayerVolume(19, 63);
}

void SndScene10::update(s32 cameraDistance) {
    SndSceneBase::update(cameraDistance);
    tempo.update();
}

void SndScene10::onBgmChange(u32 v, u32 c) {
    return tempo.setMode(v);
}

void SndScene10::beginTalk(s32 a) {
    Snd_RestoreHeapLevel(f1d);
    SndSceneBase::beginTalk(a);
    state = 2;
}

void SndScene10::endTalk() {
    SndSceneBase::endTalk();
    SndMgr_LoadBank(&gSndMgr, 144);
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    state = 1;
}

SndScene19::SndScene19() {
    id = 19;
}

SndScene19::~SndScene19() {
}

void SndScene19::load() {
    setupHeaps(0x2a824, 6);
    createPlayer4Heap();
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    gSndMgr.keepHeap = 0;
}

SndScene20::SndScene20() {
    id = 20;
}

SndScene20::~SndScene20() {
}

void SndScene20::load() {
    setupHeaps(0x2a824, 7);
    createPlayer4Heap();
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    gSndMgr.keepHeap = 0;
}

SndScene21::SndScene21() {
    id = 21;
}

SndScene21::~SndScene21() {
}

void SndScene21::load() {
    setupHeaps(0x2a824, 8);
    createPlayer4Heap();
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    gSndMgr.keepHeap = 0;
}

SndScene22::SndScene22() {
    id = 22;
}

SndScene22::~SndScene22() {
}

void SndScene22::load() {
    setupHeaps(0x2a824, 9);
    createPlayer4Heap();
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    gSndMgr.keepHeap = 0;
}

SndScene23::SndScene23() {
    id = 23;
}

SndScene23::~SndScene23() {
}

void SndScene23::load() {
    setupHeaps(0x2a824, 10);
    createPlayer4Heap();
    createPlayer5Heap();
    createPlayer6Heaps();
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    gSndMgr.keepHeap = 0;
}

SndScene24::SndScene24() {
    id = 24;
}

SndScene24::~SndScene24() {
}

void SndScene24::load() {
    setupHeaps(0x2a824, 11);
    createPlayer4Heap();
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    gSndMgr.keepHeap = 0;
}

SndScene30::SndScene30() {
    id = 30;
}

SndScene30::~SndScene30() {
}

void SndScene30::load() {
    setupHeaps(0x232f4, 12);
    createPlayer4Heap();
    createPlayer5Heap();
    createPlayer6Heaps();
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    gSndMgr.keepHeap = 0;
}

SndScene31::SndScene31() {
    id = 31;
}

SndScene31::~SndScene31() {
}

void SndScene31::load() {
    setupHeaps(0x232f4, 13);
    createPlayer4Heap();
    createPlayer5Heap();
    createPlayer6Heaps();
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    gSndMgr.keepHeap = 0;
}

SndScene32::SndScene32() {
    id = 32;
}

SndScene32::~SndScene32() {
}

void SndScene32::load() {
    setupHeaps(0x232f4, 14);
    createPlayer4Heap();
    createPlayer5Heap();
    createPlayer6Heaps();
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    gSndMgr.keepHeap = 0;
}

SndScene33::SndScene33() {
    id = 33;
}

SndScene33::~SndScene33() {
}

void SndScene33::load() {
    setupHeaps(0x232f4, 15);
    createPlayer4Heap();
    createPlayer5Heap();
    createPlayer6Heaps();
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    gSndMgr.keepHeap = 0;
}

SndScene34::SndScene34() {
    id = 34;
}

SndScene34::~SndScene34() {
}

void SndScene34::load() {
    setupHeaps(0x232f4, 16);
    createPlayer4Heap();
    createPlayer5Heap();
    createPlayer6Heaps();
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    gSndMgr.keepHeap = 0;
}

SndScene35::SndScene35() {
    id = 35;
}

SndScene35::~SndScene35() {
}

void SndScene35::load() {
    setupHeaps(0x232f4, 17);
    createPlayer4Heap();
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    gSndMgr.keepHeap = 0;
}

SndScene40::SndScene40() {
    id = 40;
}

SndScene40::~SndScene40() {
}

void SndScene40::load() {
    setupHeaps(0x245c0, 18);
    createPlayer4Heap();
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    gSndMgr.keepHeap = 0;
}

SndScene41::SndScene41() {
    id = 41;
}

SndScene41::~SndScene41() {
}

void SndScene41::load() {
    setupHeaps(0x2a824, 19);
    createPlayer4Heap();
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    gSndMgr.keepHeap = 0;
}

void SndScene41::update(s32 cameraDistance) {
    SndSceneBase::update(cameraDistance);
    beatSync.update();
}

void SndScene41::onBgmChange(u32 a, u32 c) {
    if (c >= 99 && c <= 171) {
        beatSync.setMode(a);
        beatSync.setEnable(1);
    } else {
        beatSync.setEnable(0);
    }
}

SndScene42::SndScene42() {
    id = 42;
}

SndScene42::~SndScene42() {
}

void SndScene42::load() {
    setupHeaps(0x245c0, 20);
    createPlayer4Heap();
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    gSndMgr.keepHeap = 0;
}

SndScene43::SndScene43() {
    id = 43;
}

SndScene43::~SndScene43() {
}

void SndScene43::load() {
    setupHeaps(0x245c0, 21);
    createPlayer4Heap();
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    gSndMgr.keepHeap = 0;
}

SndScene44::SndScene44() {
    id = 44;
}

SndScene44::~SndScene44() {
}

void SndScene44::load() {
    setupHeaps(0x245c0, 22);
    createPlayer4Heap();
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    gSndMgr.keepHeap = 0;
}

SndScene45::SndScene45() {
    id = 45;
}

SndScene45::~SndScene45() {
}

void SndScene45::load() {
    setupHeaps(0x245c0, 23);
    createPlayer4Heap();
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    gSndMgr.keepHeap = 0;
}

SndScene46::SndScene46() {
    id = 46;
}

SndScene46::~SndScene46() {
}

void SndScene46::load() {
    setupHeaps(0x245c0, 24);
    createPlayer4Heap();
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    gSndMgr.keepHeap = 0;
}

SndScene47::SndScene47() {
    id = 47;
}

SndScene47::~SndScene47() {
}

void SndScene47::load() {
    setupHeaps(0x245c0, 25);
    createPlayer4Heap();
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    gSndMgr.keepHeap = 0;
}

SndScene48::SndScene48() {
    id = 48;
}

SndScene48::~SndScene48() {
}

void SndScene48::load() {
    setupHeaps(0x245c0, 26);
    createPlayer4Heap();
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    gSndMgr.keepHeap = 0;
}

SndScene50::SndScene50() {
    id = 50;
    Snd_SetUnusedFlag(1);
}

SndScene50::~SndScene50() {
}

void SndScene50::load() {
    setupHeaps(0x0, 27);
    createPlayer11Heaps(3);
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    gSndMgr.keepHeap = 0;
}

SndScene51::SndScene51() {
    id = 51;
}

SndScene51::~SndScene51() {
}

void SndScene51::load() {
    setupHeaps(0x0, 28);
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    gSndMgr.keepHeap = 0;
    SndMgr_StartVolumeFadeIn(&gSndMgr);
}

void SndScene51::fadeOutAll() {
    MelodyPlayer_StopTrackB(gSndMgr.melody);
    gSndMgr.seDisabled = 1;
    stopPlayers(17);
}

SndScene52::SndScene52() {
    id = 52;
}

SndScene52::~SndScene52() {
}

void SndScene52::load() {
    setupHeaps(0x2a824, 29);
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    gSndMgr.keepHeap = 0;
}

SndScene60::SndScene60() {
    id = 60;
}

SndScene60::~SndScene60() {
}

void SndScene60::load() {
    setupHeaps(0x21ef8, 4);
    createPlayer11Heaps(2);
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    SndMgr_LoadBank(&gSndMgr, 143);
    gSndMgr.keepHeap = 0;
}

SndScene99::SndScene99() {
    id = 99;
}

SndScene99::~SndScene99() {
}

void SndScene99::load() {
    setupHeaps(0x2a824, 29);
    createPlayer12Heaps();
    NNS_SndHeapSaveState(Snd_GetHeap());
    gSndMgr.keepHeap = 0;
}
