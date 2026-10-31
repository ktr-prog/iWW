#include "types.h"
#include "host_labels.h"
#include "gfx/Camera.h"
#include "gfx/VecFx32.h"
#include "snd/SndEnvChannel.h"
#include "snd/SndSeEmitter.h"
#include "snd/SndSceneBase.h"
#include "snd/BgmSceneFade.h"
#include "snd/SndMgr.h"
#include "snd/Melody.h"
struct Rb;
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/autoload_2/unk_020f4a5c.h"
#include "proto/autoload_2/unk_020f7a5c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0206d988.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/main/unk_02034438.h"
#include "proto/autoload_2/unk_020ee98c.h"
#include "proto/autoload_2/unk_020ef150.h"
#include "proto/autoload_2/unk_020f0dec.h"
#include "snd/SndScenes.h"
#include "snd/SndPos.h"


extern Camera *gCamera;
extern VecFx32 gCameraEye;
extern u8 gFieldSceneKind;
#define data_021f5be0 HOST_LABEL(u8 (*)[], data_021f5be0)



SndSceneBase *gSndScene;
u8 gSndHeapBuffer[0x80000];












extern "C" {
void Clock_GetMinuteHour(void *);
}

extern "C" {
s32 Scene_GetCurrent();
}



extern "C" {
s32 Scene_InTownUnk31();
}

extern "C" {
void Clock_GetDateTime(void *);
}

extern "C" {
void MI_CpuCopy8(void *, void *, u32);
}

extern "C" {
s32 Event_GetState(u32, void *, u32);
}






















































































#define NEW(T)                                                \
    do {                                                      \
        void *p = Mem_AllocForNew(sizeof(T));                 \
        gSndScene = p != NULL ? new (p) T() : NULL;           \
    } while (0)

static inline BOOL Unk_020040cc_check(u32 id, void *buf) {
    if (Event_GetState(id, buf, 0) != 0) {
        return TRUE;
    }
    return FALSE;
}

static inline BOOL Unk_020040cc_isA() { return gFieldSceneKind == 0; }
static inline BOOL Unk_020040cc_isB() { return gFieldSceneKind == 1; }

extern "C" {
extern s32 gCameraDistance;
}

extern "C" void Snd_Init() {
    gSndScene = 0;
    gSndMgr.init(gSndHeapBuffer, 0x80000, "/sound_dataENG.sdat");
    Melody_Init();
}

extern "C" void Snd_Update() {
    Melody_Update();
    gSndMgr.update();
    if (gSndScene != 0 && gCamera != 0) {
        gSndScene->update(gCameraDistance);
    }
}

extern "C" void func_020044dc() {}

extern "C" void Snd_CreateScene() {
    u8 st[4];
    u32 t[2];
    u32 b0[2], b1[2], b2[2];
    if (!Unk_020040cc_isA() && !Unk_020040cc_isB()) {
        NEW(SndScene99);
    } else {
        Clock_GetMinuteHour(st);
        switch (Scene_GetCurrent()) {
    case 6:
    case 7:
    case 8:
        NEW(SndScene19);
        break;
    case 9:
        NEW(SndScene20);
        break;
    case 10:
        NEW(SndScene21);
        break;
    case 11:
    case 12:
    case 13:
    case 14:
    case 47:
        NEW(SndScene22);
        break;
    case 15:
        NEW(SndScene23);
        break;
    case 16:
        NEW(SndScene24);
        break;
    case 26:
        NEW(SndScene30);
        break;
    case 27:
        NEW(SndScene31);
        break;
    case 28:
        NEW(SndScene32);
        break;
    case 29:
        NEW(SndScene33);
        break;
    case 30:
        NEW(SndScene34);
        break;
    case 31:
        NEW(SndScene35);
        break;
    case 32:
        NEW(SndScene40);
        break;
    case 33:
        NEW(SndScene41);
        break;
    case 34:
        NEW(SndScene42);
        break;
    case 35:
    case 36:
        NEW(SndScene43);
        break;
    case 37:
    case 38:
        NEW(SndScene44);
        break;
    case 39:
        NEW(SndScene45);
        break;
    case 40:
        if (st[1] >= 8 && st[1] < 0x11) {
            NEW(SndScene47);
        } else {
            NEW(SndScene46);
        }
        break;
    case 41:
        NEW(SndScene48);
        break;
    case 44:
        NEW(SndScene50);
        break;
    case 45:
        NEW(SndScene51);
        break;
    case 46:
    case 48:
        NEW(SndScene52);
        break;
    case 50:
        NEW(SndScene99);
        break;
        default: {
            if (!Unk_020040cc_isA()) {
                NEW(SndScene10);
                break;
            }
            if (Taxi_IsArriving() != 0 || Taxi_IsLeaving() != 0) {
                NEW(SndScene02);
            } else if (Scene_InTownUnk31() != 0) {
                NEW(SndScene60);
            } else {
                t[0] = 0;
                t[1] = 0;
                Clock_GetDateTime(t);
                MI_CpuCopy8(t, b0, 8);
                if (Unk_020040cc_check(0xf, b0)) {
                    NEW(SndScene03);
                } else {
                    MI_CpuCopy8(t, b1, 8);
                    if (Unk_020040cc_check(0x12, b1)) {
                        NEW(SndScene03);
                    } else {
                        MI_CpuCopy8(t, b2, 8);
                        if (Unk_020040cc_check(0x13, b2)) {
                            if (((u8 *)t)[2] < 2) {
                                NEW(SndScene03);
                            } else {
                                NEW(SndScene01);
                            }
                        } else {
                            NEW(SndScene01);
                        }
                    }
                }
            }
            break;
        }
        }
    }
    gSndScene->load();
}

extern "C" void Snd_DestroyScene() {
    if (gSndScene != NULL) {
        if (Bgm_GetSceneFade()->isKeepingBgm() != 0) {
            data_021f5be0[2] = 1;
        }
        gSndScene->unload();
        delete gSndScene;
        gSndScene = NULL;
    }
}

extern "C" void Snd_VolumeOff() { gSndMgr.volumeOff(); }

extern "C" void Snd_VolumeOn() { gSndMgr.volumeOn(); }

extern "C" void Snd_FadeOutScene() { gSndScene->fadeOutAll(); }

extern "C" void Snd_PlaySe(u32 a) { SndMgr_PlaySe(&gSndMgr, a); }


extern "C" void Snd_PlaySePanned(u32 a, u32 b) { SndMgr_PlaySePanned(&gSndMgr, a, b); }

extern "C" void Snd_PlaySeOnHandle(u32 a) { SndMgr_PlaySeOnHandle(&gSndMgr, a); }

extern "C" void Snd_StopSe(u32 a, u32 b) { SndMgr_StopSe(&gSndMgr, a, b); }

extern "C" void Snd_SetOutputMode(u32 a) { gSndMgr.setOutputMode(a); }

extern "C" void Snd_BeginTalk(u32 a) { gSndScene->beginTalk(a); }

extern "C" void Snd_PlayTalkVoice(u32 a, u32 b, u32 c, u32 d) { SndMgr_PlayTalkVoice(&gSndMgr, a, b, c, d); }

extern "C" void Snd_EndTalk() { gSndScene->endTalk(); }

extern "C" void Snd_SetVoiceType(u32 a) { SndMgr_SetVoiceType(&gSndMgr, a); }

void SndSceneBase::setBankVariant(s32 a) {}

extern "C" void Snd_SetSceneBankVariant(u32 a) { gSndScene->setBankVariant(a); }

extern "C" void Snd_SetSeHandleVolumes(u32 a) { SndMgr_SetSeHandleVolumes(&gSndMgr, a); }

extern "C" void Snd_SetKeySeMode(u32 a) { SndMgr_SetKeySeMode(&gSndMgr, a); }

extern "C" void Snd_PlayKeySe(u32 a) { SndMgr_PlayKeySe(&gSndMgr, a); }

extern "C" void Snd_PlayAuxSe(u32 a) { SndMgr_PlayAuxSe(&gSndMgr, a); }

extern "C" void Snd_PlayAuxSeHeld(u32 a) { SndMgr_PlayAuxSeHeld(&gSndMgr, a); }

extern "C" void Snd_StopAuxSe() { SndMgr_StopAuxSe(&gSndMgr); }

extern "C" void Snd_StartBellRollSe() { SndMgr_StartBellRollSe(&gSndMgr); }

extern "C" void Snd_StopBellRollSe() { SndMgr_StopBellRollSe(&gSndMgr); }

void SndSeEmitter::callInit() { init(); }

void SndSeEmitter::callUpdateRelative(VecFx32 *v) {
    VecFx32 t;
    if (v != NULL) {
        if (gCamera != 0) {
            t.x = v->x - gCameraEye.x;
            t.y = v->y - gCameraEye.y;
            t.z = v->z - gCameraEye.z;
            update(&t);
        }
    } else {
        update(v);
    }
}

extern "C" void Snd_SeEmitterPlayOneShot(SndSeEmitter *a, u32 b, u32 c, u32 d) { a->playOneShot(b, c, d); }

extern "C" void Snd_SeEmitterPlayHeld(SndSeEmitter *a, u32 b, u32 c, u32 d) { a->playHeld(b, c, d); }

void SndSeEmitter::callStop() { stop(); }

void SndSeEmitter::callInitAlt() { init(); }

void SndSeEmitter::callUpdateRelativeAlt(VecFx32 *v) {
    VecFx32 t;
    if (v != NULL) {
        if (gCamera != 0) {
            t.x = v->x - gCameraEye.x;
            t.y = v->y - gCameraEye.y;
            t.z = v->z - gCameraEye.z;
            update(&t);
        }
    } else {
        update(v);
    }
}

extern "C" void Snd_SeEmitterPlayAlternate(void *e, u16 s) { ((SndSeEmitter *)(e))->playAlternate(s); }

extern "C" void Snd_SeEmitterPlayOneShotAlt(SndSeEmitter *a, u32 b, u32 c, u32 d) { a->playOneShot(b, c, d); }

void SndSeEmitter::callStopAlt() { stop(); }

extern "C" void Snd_PosListInit(void *l) { ((SndPosList *)l)->init(); }

extern "C" void Snd_PosListUpdate(void *l) { ((SndPosList *)l)->update(); }

extern "C" void Snd_PosNodeInit(void *n, void *l) { ((SndPosNode *)n)->init((SndPosList *)l); }

extern "C" void Snd_PosNodePlay(void *a, u32 b, VecFx32 *v) {
    VecFx32 t;
    if (v != NULL && gCamera != 0) {
        t.x = v->x - gCameraEye.x;
        t.y = v->y - gCameraEye.y;
        t.z = v->z - gCameraEye.z;
        ((SndPosNode *)a)->play(b, &t);
    }
}

extern "C" void Snd_PosNodePlayOnce(void *a, u32 b, VecFx32 *v) {
    VecFx32 t;
    if (v != NULL && gCamera != 0) {
        t.x = v->x - gCameraEye.x;
        t.y = v->y - gCameraEye.y;
        t.z = v->z - gCameraEye.z;
        ((SndPosNode *)a)->playOnce(b, &t);
    }
}

extern "C" void Snd_SetBgmPan(void *a, VecFx32 *v) {
    if (v != NULL && gCamera != 0) {
        VecFx32 t = *v;
        t.x -= gCameraEye.x;
        t.y -= gCameraEye.y;
        t.z -= gCameraEye.z;
        ((SndPosNode *)a)->setBgmPan(&t);
    }
}

extern "C" void Snd_PosNodeRelease(void *n) { ((SndPosNode *)n)->release(); }

extern "C" void Snd_PosNodeSetPitch(void *n, s32 v) { ((SndPosNode *)n)->setPitch(v); }

extern "C" s32 Snd_PosListCanInit() { return 1; }

void SndEnvChannel::callReset() { vfunc_00(); }

void SndEnvChannel::callUpdateRelative(VecFx32 *pos) {
    VecFx32 t;
    if (pos != NULL) {
        if (gCamera != 0) {
            t.x = pos->x - gCameraEye.x;
            t.y = pos->y - gCameraEye.y;
            t.z = pos->z - gCameraEye.z;
            update((VecFx32 *)&t);
        }
    } else {
        update((VecFx32 *)pos);
    }
}

void SndEnvChannel::callUpdate(void *a) { update((VecFx32 *)a); }

void SndEnvChannel::callRequestSustained(u32 id) { requestSustained(id); }

void SndEnvChannel::callRequest(u32 id) { request(id); }

void SndEnvChannel::callRelease() { vfunc_04(); }

extern "C" void Snd_PlayBgm(u32 a) { SndMgr_PlayBgm(&gSndMgr, a); }

extern "C" void Snd_StopBgm(u32 a) { SndMgr_StopBgm(&gSndMgr, a); }

extern "C" void Snd_MoveBgmVolume(u32 a, u32 b) { SndMgr_MoveBgmVolume(&gSndMgr, a, b); }

extern "C" void Snd_FadeOutBgmTracks(u32 a) { SndMgr_FadeOutBgmTracks(&gSndMgr, a); }

extern "C" void Snd_FadeInBgmTracks(u32 a) { SndMgr_FadeInBgmTracks(&gSndMgr, a); }

extern "C" void Snd_SetBgmTrackVariant(u32 a) { SndMgr_SetBgmTrackVariant(&gSndMgr, a); }

extern "C" void *Snd_GetBeatState() { return SndMgr_GetBeatState(&gSndMgr); }

extern "C" void Snd_BeginMenuDuck() { SndMgr_BeginMenuDuck(&gSndMgr); }

extern "C" void Snd_EndMenuDuck() { SndMgr_EndMenuDuck(&gSndMgr); }

extern "C" void Snd_DuckSubPlayers() { SndMgr_DuckSubPlayers(&gSndMgr); }

extern "C" void Snd_RestoreSubPlayers() { SndMgr_RestoreSubPlayers(&gSndMgr); }

extern "C" void Snd_SetPanIfChanged(u32 a) { SndMgr_SetPanIfChanged(&gSndMgr, a); }

extern "C" void Snd_SetPan(u32 a) { SndMgr_SetPan(&gSndMgr, a); }

extern "C" void Snd_MelodyInit(void *c) { MelodyPlayer_Init((MelodyPlayer *)c); }

extern "C" void Snd_MelodySetPattern(void *c, u8 *src) { MelodyPlayer_SetPattern((MelodyPlayer *)c, src); }

extern "C" void Snd_MelodyPlayPattern(void *c, u32 v, u8 *pat) { MelodyPlayer_PlayPattern((MelodyPlayer *)c, v, pat); }

extern "C" void Snd_MelodyPlayAt(void *a, VecFx32 *v, u32 c) {
    VecFx32 t;
    if (gCamera != 0) {
        t.x = v->x - gCameraEye.x;
        t.y = v->y - gCameraEye.y;
        t.z = v->z - gCameraEye.z;
        MelodyPlayer_PlayAt((MelodyPlayer *)a, &t, c);
    }
}

extern "C" void Snd_MelodyPlay(void *c, u32 v) { MelodyPlayer_Play((MelodyPlayer *)c, v); }

extern "C" void Snd_MelodyStartTrackA(void *c) { MelodyPlayer_StartTrackA((MelodyPlayer *)c); }

extern "C" void Snd_MelodyPlayNote(void *c, u32 idx) { MelodyPlayer_PlayNote((MelodyPlayer *)c, idx); }

extern "C" s32 Snd_MelodyUpdate(void *c) { return MelodyPlayer_Update((MelodyPlayer *)c); }

extern "C" u8 Snd_MelodyIsPlaying(void *c) { return MelodyPlayer_IsPlaying((MelodyPlayer *)c); }

extern "C" void Snd_MelodyPlayRandom(void *c, u32 v) { MelodyPlayer_PlayRandom((MelodyPlayer *)c, v); }

extern "C" u8 *Snd_MelodyApplyRandomPattern(void *c) { return MelodyPlayer_ApplyRandomPattern((MelodyPlayer *)c); }

extern "C" u8 *Snd_MelodyGetDefaultPattern() { return Melody_GetDefaultPattern(); }

extern "C" void Snd_BgmSyncInit(void *r, u16 v) { BgmSyncSnd_Init((Rb *)r, v); }

extern "C" void Snd_BgmSyncSetState(void *r, u32 mode) { BgmSyncSnd_SetState((Rb *)r, mode); }

extern "C" s32 Snd_BgmSyncUpdate(Rb *a, VecFx32 *v) {
    VecFx32 t;
    s32 r;
    if (v != NULL) {
        if (gCamera == 0) {
            r = -1;
        } else {
            t.x = v->x - gCameraEye.x;
            t.y = v->y - gCameraEye.y;
            t.z = v->z - gCameraEye.z;
            r = BgmSyncSnd_Update(a, &t);
        }
    } else {
        r = -1;
    }
    return r;
}

extern "C" void Snd_BgmSyncRelease(void *r) { BgmSyncSnd_Release((Rb *)r); }

extern "C" void Snd_BgmSyncSetStartBeat(void *r, s8 v) { BgmSyncSnd_SetStartBeat((Rb *)r, v); }

extern "C" u32 Snd_BgmSyncReadBeat() { return BgmSyncSnd_ReadBeat(); }

extern "C" s32 Snd_BgmSyncPollStarted(void *r) { return BgmSyncSnd_PollStarted((Rb *)r); }

extern "C" void Snd_MelodyBeatInit(void *s) { MelodyBeat_Init((MelodyBeat *)s); }

extern "C" void Snd_MelodyBeatStart(void *s, u16 id) { MelodyBeat_Start((MelodyBeat *)s, id); }

extern "C" void Snd_MelodyBeatUpdate(MelodyBeat *a, VecFx32 *v) {
    VecFx32 t;
    if (v != NULL) {
        if (gCamera != 0) {
            t.x = v->x - gCameraEye.x;
            t.y = v->y - gCameraEye.y;
            t.z = v->z - gCameraEye.z;
            MelodyBeat_Update(a, &t);
        }
    } else {
        MelodyBeat_Update(a, v);
    }
}

extern "C" void Snd_MelodyBeatStop(void *s) { MelodyBeat_Stop((MelodyBeat *)s); }

