#include "types.h"
#include "snd/TvSound.h"
#include "snd/SndMgr.h"
#include "proto/autoload_2/unk_020ed8cc.h"
#include "proto/autoload_2/unk_020ef150.h"
#include "proto/autoload_2/unk_020f0dec.h"
#include "proto/autoload_2/unk_020f5b9c.h"
#include "proto/autoload_2/unk_0210c084.h"
#include "proto/main/unk_0206d49c.h"


extern "C" {
void NNS_SndPlayerWriteVariable(void *p, u32 a, u32 b);
void NNS_SndPlayerSetVolume(void *p, s32 v);
void NNS_SndHandleReleaseSeq(void *p);
void NNS_SndHandleInit(void *p);
void NNS_SndPlayerSetTrackVolume(void *p, u32 a, u32 b);
void NNS_SndPlayerSetTrackPan(void *p, u32 a, u32 b);
void NNS_SndPlayerMoveVolume(void *p, u32 a, u32 b);
void NNS_SndPlayerStopSeq(void *p, u32 a);
s32 Snd_CalcListenerDistance(void *a, u32 b);
u32 Snd_DistanceToVolume(s32 x);
u32 Snd_CalcPan(void *a, u32 b);
}

void TvSound::reset() {
    NNS_SndHandleInit(&a);
    NNS_SndHandleInit(&b);
    c12 = 0;
    startSounds();
    NNS_SndPlayerSetVolume(&a, 0);
    NNS_SndPlayerSetVolume(&b, 0);
}

void TvSound::release() {
    Snd_StopHandle(&a, 0);
    Snd_StopHandle(&b, 0);
    NNS_SndHandleReleaseSeq(&a);
    NNS_SndHandleReleaseSeq(&b);
}

void TvSound::vfunc_08(s32 id, void *arg) {
    updatePosition(arg);
}

void TvSound::turnOn(s32 v) {
    c12 = v;
    NNS_SndPlayerSetVolume(&a, 127);
    NNS_SndPlayerSetVolume(&b, 127);
}

void TvSound::turnOff() {
    NNS_SndPlayerSetVolume(&a, 0);
    NNS_SndPlayerSetVolume(&b, 0);
}

void TvSound::updatePosition(void *x) {
    u32 r5;
    u32 r4;
    if (x == 0) {
        NNS_SndPlayerSetVolume(&a, 0);
        NNS_SndPlayerSetVolume(&b, 0);
        return;
    }
    r5 = Snd_DistanceToVolume(Snd_CalcListenerDistance(x, 0));
    r4 = Snd_CalcPan(x, 0);
    NNS_SndPlayerSetVolume(&a, r5);
    NNS_SndPlayerSetVolume(&b, r5);
    NNS_SndPlayerSetTrackPan(&a, 15, r4);
    NNS_SndPlayerSetTrackPan(&b, 15, r4);
}

void TvSound::startSe(s32 code, void *slot) {
    if (slot == 0) Fatal_Trap();
    NNS_SndArcPlayerStartSeqArc(slot, 1, code % 1000);
}

void TvSoundProgram0::startSounds() {
    startSe(0x4f0, &a);
}

void TvSoundProgram1::startSounds() {
    startSe(0x4f1, &a);
}

void TvSoundProgram2::reset() {
    TvSound::reset();
    d13 = -1;
}

void TvSoundProgram2::startSounds() {
    startSe(0x4f2, &b);
}

void TvSoundProgram2::vfunc_08(s32 id, void *arg) {
    switch (id) {
    case 1:
        if (b == NULL) startSe(0x4f2, &b);
        d13++;
        if (d13 == 3) d13 = 0;
        switch (d13) {
        case 0:
            startSe(0x4f6, &a);
            break;
        case 1:
            NNS_SndArcPlayerStartSeq(&a, 247);
            break;
        case 2:
            NNS_SndPlayerMoveVolume(&a, 40, 15);
            break;
        }
        break;
    case 40:
        NNS_SndPlayerWriteVariable(&a, 1, 1);
        break;
    case 50:
        NNS_SndPlayerWriteVariable(&a, 0, 2);
        break;
    case 150:
        startSe(0x4f3, &b);
        NNS_SndPlayerWriteVariable(&a, 0, 0);
        break;
    case 200:
        startSe(0x4f4, &b);
        NNS_SndPlayerWriteVariable(&a, 1, 2);
        break;
    case 300:
        NNS_SndPlayerWriteVariable(&a, 0, 3);
        break;
    case 375:
        startSe(0x4f5, &b);
        break;
    case 385:
        if (d13 == 2) NNS_SndPlayerStopSeq(&a, 15);
        break;
    }
    switch (d13) {
    case 0:
        NNS_SndPlayerSetTrackVolume(&a, 0xfff, 127);
        NNS_SndPlayerSetTrackVolume(&b, 0xfff, 127);
        break;
    case 1:
        NNS_SndPlayerSetTrackVolume(&a, 0xfff, 100);
        NNS_SndPlayerSetTrackVolume(&b, 0xfff, 0);
        break;
    case 2:
        NNS_SndPlayerSetTrackVolume(&b, 0xfff, 100);
        break;
    }
    updatePosition(arg);
}

void TvSoundProgram3::startSounds() {
    NNS_SndArcPlayerStartSeq(&a, 0xac);
    d13 = 0;
}

void TvSoundProgram3::vfunc_08(s32 id, void *arg) {
    switch (id) {
    case 1:
        if (d13 == 0) startSe(0x4f7, &b);
        break;
    case 120:
        if (d13 == 1) startSe(0x4f8, &b);
        break;
    case 190:
        if (d13 == 0) startSe(0x4f9, &b);
        break;
    case 210:
        if (d13 == 1) startSe(0x4fb, &b);
        break;
    case 300:
        if (d13 == 0) startSe(0x4fa, &b);
        break;
    case 349:
        d13++;
        if (d13 == 2) d13 = 0;
        break;
    }
    updatePosition(arg);
}

void TvSoundProgram5::startSounds() {
    d13 = 0;
}

void TvSoundProgram5::vfunc_08(s32 id, void *arg) {
    switch (id) {
    case 1:
        if (d13 == 0) startSe(0x4fc, &a);
        else startSe(0x4fd, &a);
        if (b == NULL) startSe(0x500, &b);
        break;
    case 70:
        NNS_SndPlayerWriteVariable(&b, 1, 1);
        break;
    case 210:
        NNS_SndPlayerWriteVariable(&b, 2, 1);
        break;
    case 220:
        NNS_SndPlayerWriteVariable(&b, 1, 0);
        break;
    case 230:
        if (d13 == 0) startSe(0x4fe, &a);
        else startSe(0x4ff, &a);
        break;
    case 253:
        if (d13 == 1) NNS_SndPlayerWriteVariable(&b, 2, 2);
        break;
    case 258:
        if (d13 == 0) NNS_SndPlayerWriteVariable(&b, 2, 2);
        break;
    case 280:
        NNS_SndPlayerWriteVariable(&b, 1, 1);
        break;
    case 370:
        NNS_SndPlayerWriteVariable(&b, 1, 0);
        NNS_SndPlayerWriteVariable(&b, 2, 1);
        break;
    case 383:
        if (d13 == 1) NNS_SndPlayerWriteVariable(&a, 0, 2);
        break;
    case 390:
        if (d13 == 0) NNS_SndPlayerWriteVariable(&a, 0, 2);
        break;
    case 405:
        if (d13 == 1) NNS_SndPlayerWriteVariable(&b, 2, 3);
        break;
    case 425:
        if (d13 == 0) NNS_SndPlayerWriteVariable(&b, 2, 3);
        break;
    case 479:
        d13++;
        if (d13 == 2) d13 = 0;
        break;
    }
    updatePosition(arg);
}

void TvSoundProgram9::startSounds() {
    startSe(0x501, &a);
    startSe(0x502, &b);
}

void TvSoundProgram9::vfunc_08(s32 id, void *arg) {
    switch (id) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        if (a == NULL) startSe(0x501, &a);
        if (b == NULL) startSe(0x502, &b);
        NNS_SndPlayerWriteVariable(&a, 0, 1);
        NNS_SndPlayerWriteVariable(&b, 0, 1);
        break;
    case 90:
        NNS_SndPlayerWriteVariable(&a, 0, 2);
        NNS_SndPlayerWriteVariable(&b, 0, 2);
        break;
    case 140:
        NNS_SndPlayerWriteVariable(&a, 0, 3);
        break;
    case 225:
        NNS_SndPlayerWriteVariable(&a, 0, 4);
        break;
    case 235:
        NNS_SndPlayerWriteVariable(&a, 0, 5);
        break;
    case 245:
        NNS_SndPlayerWriteVariable(&b, 0, 3);
        break;
    }
    updatePosition(arg);
}

void TvSoundWeather::startSounds() {
    c13 = 0;
    c14 = SndMgr_Rand(&gSndMgr, 3);
    c15 = 0;
    NNS_SndArcPlayerStartSeq(&a, (u16)(c14 + 0xad));
}

void TvSoundWeather::pickNextLoop() {
    u8 v;
    do {
        v = SndMgr_Rand(&gSndMgr, 3);
    } while (v == c14);
    c14 = v;
    NNS_SndArcPlayerStartSeq(&a, (u16)(c14 + 0xad));
}

void TvSoundWeather::vfunc_08(s32 id, void *arg) {
    switch (id) {
    case 10:
        switch (c15) {
        case 0:
            startSe(0x503, &b);
            break;
        case 1:
            startSe(0x505, &b);
            break;
        }
        break;
    case 130:
        if (c15 == 0) startSe(0x504, &b);
        break;
    case 150:
        if (c15 == 1) startSe(0x506, &b);
        break;
    case 399:
        c13++;
        if (c13 == 7) {
            c13 = 0;
            pickNextLoop();
        }
        c15++;
        if (c15 == 3) c15 = 0;
        break;
    }
    updatePosition(arg);
}

void TvSound::startSounds() {
}
