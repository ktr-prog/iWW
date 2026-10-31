#include "types.h"
#include "snd/SndMgr.h"
#include "snd/SndSceneBase.h"
#include "snd/BgmBeatSync.h"
#include "snd/SndSeqPlayer.h"
#include "proto/autoload_2/unk_020ed8cc.h"
#include "proto/autoload_2/unk_020ee98c.h"
#include "proto/autoload_2/unk_020ef150.h"
#include "proto/autoload_2/unk_0210c084.h"

struct SndEnt {
    u16 a;
    u16 b;
    u16 c;
    u16 d;
};

extern "C" {
s32 FX_Div(s32 a, s32 b);
void NNS_SndPlayerSetTrackPan(void *p, u32 a, u32 b);
void NNS_SndPlayerSetTrackPitch(void *p, u32 a, u32 b);
void NNS_SndPlayerSetTrackVolume(void *p, u32 a, u32 b);
void NNS_SndPlayerSetVolume(void *p, u32 a);
void NNS_SndPlayerSetPlayerVolume(u32 a, u32 b);
void NNS_SndPlayerStopSeq(void *p, s32 frames);
u32 func_0210e648(void *p);
void *Snd_GetVolumeCurve(void);
void SndVolumeCurve_Set(void *p, u32 a);

void NNS_SndPlayerMoveVolume(void *p, s32 v, u32 w);
void NNS_SndArcStrmMoveVolume(void *p, s32 v, u32 w);
void NNS_SndArcStrmStop(void *p, s32 v);
void NNS_SndArcStrmStart(void *p, u32 a, u32 b);
s32 func_0210e5fc(void *p);
void NNS_SndPlayerStopSeqBySeqNo(s32 a, s32 b, u32 c);

}

static inline BOOL isSet(void *p) {
    return p != NULL;
}

extern "C" void SndMgr_PlaySe(SndMgr *self, s32 id) {
    if (self->seDisabled != 0) {
        return;
    }
    switch (id) {
        case 3:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 21:
        case 25:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
        case 0x85f:
        case 0x865:
        case 0x866:
        case 0x867:
        case 0x868:
        case 0x869:
        case 0x86a:
        case 0x86b:
        case 0x86c:
        case 0x86d:
        case 0x86e:
        case 0x87f:
        case 0x880:
        case 0x881:
        case 0x882:
            Snd_StartSeqArc((u16)(id % 1000), (u16)(id / 1000), &self->seHandle);
            SndMgr_ApplyPan(self, 0);
            break;
        case 0x861:
            Snd_StartSeqArc((u16)(id % 1000), (u16)(id / 1000), &self->auxSeHandle);
            SndMgr_ApplyPan(self, 0);
            break;
        case 1:
        case 2:
            self->curveDelay = 15;
            Snd_StartSeqArcDefault((u16)(id % 1000), (u16)(id / 1000));
            break;
        default:
            Snd_StartSeqArcDefault((u16)(id % 1000), (u16)(id / 1000));
            break;
    }
}

extern "C" void SndMgr_PlaySeOnHandle(SndMgr *self, s32 a) {
    Snd_StartSeqArc((u16)(a % 1000), (u16)(a / 1000), &self->seHandle);
    if (a == 0x862) {
        NNS_SndPlayerSetVolume(&self->seHandle, 0);
    }
    SndMgr_ApplyPan(self, 1);
}

extern "C" void SndMgr_StopSe(SndMgr *self, s32 a, u32 b) {
    NNS_SndPlayerStopSeqBySeqNo(a / 1000, a % 1000, b);
}

extern "C" void SndMgr_SetVoiceType(SndMgr *self, u32 v) {
    self->voiceType = v;
}

extern "C" void SndMgr_PlayVoice(SndMgr *self, s32 a, u8 x, s32 y) {
    switch (self->voiceType) {
        case 3: {
            y -= 400;
            double k = 1.38;
            x = (u8)((double)x * k);
            if (x > 127) {
                x = 127;
            }
            break;
        }
        case 4: {
            y += 600;
            double k = 1.23;
            x = (u8)((double)x * k);
            if (x > 127) {
                x = 127;
            }
            break;
        }
    }
    Snd_StartSeqArc((u16)(a % 1000), (u16)(a / 1000), &self->voiceHandle);
    if (isSet(self->voiceHandle.p)) {
        NNS_SndPlayerSetVolume(&self->voiceHandle, x);
        NNS_SndPlayerSetTrackPitch(&self->voiceHandle, 15, y);
    }
}

extern "C" void SndMgr_LoadBank(SndMgr *self, u32 bankNo) {
    NNS_SndArcLoadBank(bankNo, Snd_GetHeap());
}

extern "C" u16 SndMgr_Rand(SndMgr *self, u32 n) {
    self->randState = self->randMul * self->randState + self->randAdd;
    if (n == 0) {
        return self->randState >> 16;
    }
    return ((self->randState >> 16) * n) >> 16;
}

extern "C" void SndMgr_PlayBgm(SndMgr *self, u32 k) {
    switch (k) {
        case 0:
        case 1:
            NNS_SndArcStrmStart(&self->strmHandle, k, 0);
            if (k != 0) {
                return;
            }
            self->strmTotalTime = func_0210e5fc(&self->strmHandle);
            return;
    }
    self->scene->onBgmChange(0, k);
    if (k >= 176 && k <= 245) {
        SndMgr_StartBgmSeq(self, k, 0);
        return;
    }
    SndMgr_StartBgmSeq(self, k, 127);
    if (k < 22) {
        return;
    }
    if (k <= 45) {
        self->variantDirty = 1;
    }
}

extern "C" void SndMgr_StopBgm(SndMgr *self, s32 v) {
    void *h = self->strmHandle.p;
    if (isSet(h)) {
        if (self->scene->id == 51) {
            v += 1;
        }
        NNS_SndArcStrmStop(&self->strmHandle, v);
        return;
    }
    SndMgr_StopBgmSeq(self, v);
    self->scene->onBgmChange(1, 9999);
}

extern "C" void SndMgr_MoveBgmVolume(SndMgr *self, s32 v, u32 w) {
    if (v > 127) {
        v = 127;
    } else if (v < 0) {
        v = 0;
    }
    void *h = self->strmHandle.p;
    if (isSet(h)) {
        NNS_SndArcStrmMoveVolume(&self->strmHandle, v, w);
        return;
    }
    NNS_SndPlayerMoveVolume(&self->bgmHandle, v, w);
}

extern "C" void SndMgr_FadeOutBgmTracks(SndMgr *self, s32 k) {
    SndRamp_Set(&self->fadeRamp, 127);
    switch (k) {
        case 1:
            self->trackMask = 0x84;
            break;
        case 2:
            self->trackMask = 24;
            break;
        case 3:
            self->trackMask = 0x1800;
            break;
        case 4:
            self->trackMask = 0x700;
            break;
        case 5:
            self->trackMask = 99;
            break;
        case 6:
            self->trackMask = 0xff18;
            break;
        case 11:
            self->trackMask = 0xff9c;
            break;
        case 12:
            self->trackMask = 0xff84;
            break;
        case 13:
            self->trackMask = 0xe79c;
            break;
        case 14:
            self->trackMask = 0xf89c;
            break;
        case 15:
            self->trackMask = 0xf8ff;
            break;
        default:
            return;
    }
    if (k >= 6) {
        NNS_SndPlayerSetTrackVolume(&self->bgmHandle, self->trackMask, 0);
        return;
    }
    SndRamp_Start(&self->fadeRamp, 0, 15);
}

extern "C" void SndMgr_FadeInBgmTracks(SndMgr *self, u32 k) {
    SndRamp_Set(&self->fadeRamp, 0);
    switch (k) {
        case 1:
            self->trackMask = 0x84;
            break;
        case 2:
            self->trackMask = 24;
            break;
        case 3:
            self->trackMask = 0x1800;
            break;
        case 4:
            self->trackMask = 0x700;
            break;
        case 5:
            self->trackMask = 99;
            break;
    }
    SndRamp_Start(&self->fadeRamp, 127, 15);
}

extern "C" void SndMgr_SetBgmTrackVariant(SndMgr *self, u32 st) {
    if (self->trackVariant != st) {
        self->variantDirty = 1;
        switch (self->trackVariant) {
            case 0:
                self->pendingVariant = st;
                if (self->variantTimer > 0 || self->fadeRamp.frames != 0) {
                    self->variantDirty = 0;
                }
                break;
            case 11:
                switch (st) {
                    case 12:
                        self->pendingVariant = 1;
                        break;
                    case 13:
                        self->pendingVariant = 3;
                        break;
                }
                break;
            case 12:
                self->pendingVariant = 2;
                break;
            case 13:
                self->pendingVariant = 4;
                break;
        }
        self->trackVariant = st;
    }
    if (self->variantDirty == 0) {
        return;
    }
    SndSceneBase *o = self->scene;
    if (o == NULL) {
        return;
    }
    s32 t = o->id;
    if (t != 1 && t != 3 && t != 60) {
        return;
    }
    SndSeqPlayer *h = SndSeqHandle_Player(&self->bgmHandle);
    if (!isSet(h)) {
        return;
    }
    u16 idx = h->seqNo - 22;
    if (idx > 23) {
        return;
    }
    self->variantTimer = -1;
    SndRamp_Start(&self->fadeRamp, 0, 0);
    u32 mode;
    SndEnt *e;
    u32 mask;
    u32 flag;
    u32 a;
    a = sBgmTrackVariantTable[idx].a;
    e = &sBgmTrackVariantTable[idx];
    if (a == 0 && e->b == 0 && e->c == 0 && e->d == 0) {
        return;
    }
    mask = 255;
    flag = 0;
    mode = self->pendingVariant;
    switch (mode) {
        case 1:
            mask = (u16)(a | e->b);
            flag = 1;
            self->variantTimer = 200;
            self->trackMask = e->c;
            self->crossTrackMask = e->b;
            self->pendingVariant = 12;
            break;
        case 2:
            mask = (u16)(a | e->c);
            flag = 1;
            self->variantTimer = 200;
            self->trackMask = e->b;
            self->crossTrackMask = e->c;
            self->pendingVariant = 11;
            break;
        case 3:
            mask = (u16)(a | e->b);
            flag = 1;
            self->variantTimer = 200;
            self->trackMask = e->d;
            self->crossTrackMask = e->b;
            self->pendingVariant = 13;
            break;
        case 4:
            mask = (u16)(a | e->d);
            flag = 1;
            self->variantTimer = 200;
            self->trackMask = e->b;
            self->crossTrackMask = e->d;
            self->pendingVariant = 11;
            break;
        case 11:
            mask = (u16)(a | e->b);
            flag = 1;
            self->trackMask = mask;
            break;
        case 12:
            mask = (u16)(a | e->c);
            flag = 1;
            self->trackMask = mask;
            break;
        case 13:
            mask = (u16)(a | e->d);
            flag = 1;
            self->trackMask = mask;
            break;
    }
    if (flag == 0) {
        return;
    }
    NNS_SndPlayerSetTrackVolume(&self->bgmHandle, (u16)~mask, 0);
    self->variantDirty = 0;
}

extern "C" void SndMgr_StartBgmSeq(SndMgr *self, u32 a, u32 b) {
    NNS_SndArcPlayerStartSeq(&self->bgmHandle, a);
    NNS_SndPlayerSetVolume(&self->bgmHandle, b);
}

extern "C" void SndMgr_StopBgmSeq(SndMgr *self, s32 frames) {
    NNS_SndPlayerStopSeq(&self->bgmHandle, frames);
}

extern "C" void SndMgr_UpdateTrackRamps(SndMgr *self) {
    SndSceneBase *o = self->scene;
    if (o == NULL) {
        return;
    }
    s32 t = o->id;
    if (t >= 40 && t < 50) {
        if (self->fadeRamp.frames != 0) {
            NNS_SndPlayerSetTrackVolume(&self->bgmHandle, self->trackMask, SndRamp_Step(&self->fadeRamp));
        }
    }
    if (t != 1 && t != 3) {
        return;
    }
    s16 c = self->variantTimer;
    if (c > 0) {
        self->variantTimer = c - 1;
    } else if (c == 0) {
        SndRamp_Set(&self->fadeRamp, 0);
        SndRamp_Start(&self->fadeRamp, 127, 600);
        self->variantTimer = -1;
    }
    if (self->fadeRamp.frames == 0) {
        return;
    }
    s32 v = SndRamp_Step(&self->fadeRamp);
    NNS_SndPlayerSetTrackVolume(&self->bgmHandle, self->trackMask, v);
    NNS_SndPlayerSetTrackVolume(&self->bgmHandle, self->crossTrackMask, 127 - v);
}

extern "C" void SndMgr_UpdateVolumeRamps(SndMgr *self) {
    SndSceneBase *o = self->scene;
    if (o == NULL) {
        return;
    }
    if (o->id == 50) {
        u32 r = func_0210e648(&self->strmHandle);
        s32 vol = ((u32)(self->strmTotalTime - r) * 20) / 1000;
        if (r != 0) {
            if (vol > 127) {
                SndMgr_SetPlayerVolumes(self, 0, 0);
            } else if (vol == 127) {
                SndRamp_Set(&self->fadeRamp, 0);
                SndRamp_Start(&self->fadeRamp, 127, 160);
            }
        }
        if (self->fadeRamp.frames != 0) {
            s32 v = SndRamp_Step(&self->fadeRamp);
            SndMgr_SetPlayerVolumes(self, v, v);
        }
    }
    if (self->scene->id == 51) {
        if (self->fadeRamp.frames != 0) {
            s32 v = SndRamp_Step(&self->fadeRamp);
            SndMgr_SetPlayerVolumes(self, v, v);
        }
    }
    if (self->mainRamp.frames != 0) {
        s32 a = SndRamp_Step(&self->mainRamp);
        s32 b = SndRamp_Step(&self->subRamp);
        SndMgr_SetPlayerVolumes(self, a, b);
        return;
    }
    if (self->subRamp.frames != 0) {
        SndMgr_SetSubPlayerVolume(self, SndRamp_Step(&self->subRamp));
    }
}

extern "C" void SndMgr_ApplyPan(SndMgr *self, u32 flag) {
    s32 v = self->pan - 128;
    if (v < -128) {
        v = -128;
    } else if (v > 127) {
        v = 127;
    }
    if (flag == 0) {
        NNS_SndPlayerSetTrackPan(&self->seHandle, 255, v);
        NNS_SndPlayerSetTrackPan(&self->auxSeHandle, 255, v);
        return;
    }
    SndSeqPlayer *h = SndSeqHandle_Player(&self->seHandle);
    if (!isSet(h)) {
        return;
    }
    switch (h->seqArcIndex) {
        case 11:
        case 146:
        case 147:
        case 179:
            NNS_SndPlayerSetTrackPan(&self->seHandle, 255, v);
            break;
    }
}

extern "C" void SndMgr_SetPlayerVolumes(SndMgr *self, s32 a, s32 b) {
    if (a > 127) {
        a = 127;
    } else if (a < 0) {
        a = 0;
    }
    if (b > 127) {
        b = 127;
    } else if (b < 0) {
        b = 0;
    }
    s32 h = a >> 1;
    NNS_SndPlayerSetPlayerVolume(4, a);
    NNS_SndPlayerSetPlayerVolume(7, a);
    NNS_SndPlayerSetPlayerVolume(13, a);
    NNS_SndPlayerSetPlayerVolume(9, a);
    NNS_SndPlayerSetPlayerVolume(8, b);
    NNS_SndPlayerSetPlayerVolume(11, b);
    if (self->subDucked != 0) {
        return;
    }
    NNS_SndPlayerSetPlayerVolume(5, b);
    NNS_SndPlayerSetPlayerVolume(6, b);
    NNS_SndPlayerSetPlayerVolume(16, b);
    NNS_SndPlayerSetPlayerVolume(17, b);
    NNS_SndPlayerSetPlayerVolume(18, h);
    NNS_SndPlayerSetPlayerVolume(19, h);
    NNS_SndPlayerSetPlayerVolume(20, b);
}

extern "C" void SndMgr_SetSubPlayerVolume(SndMgr *self, s32 v) {
    if (v > 127) {
        v = 127;
    } else if (v < 0) {
        v = 0;
    }
    NNS_SndPlayerSetPlayerVolume(5, v);
    NNS_SndPlayerSetPlayerVolume(6, v);
    NNS_SndPlayerSetPlayerVolume(16, v);
    NNS_SndPlayerSetPlayerVolume(17, v);
    NNS_SndPlayerSetPlayerVolume(18, v);
    NNS_SndPlayerSetPlayerVolume(19, v);
    NNS_SndPlayerSetPlayerVolume(20, v);
}

extern "C" void SndMgr_BeginMenuDuck(SndMgr *self) {
    self->menuDuck = 1;
    SndRamp_Set(&self->mainRamp, 127);
    SndRamp_Set(&self->subRamp, 127);
    SndRamp_Start(&self->mainRamp, 70, 15);
    SndRamp_Start(&self->subRamp, 40, 15);
}

extern "C" void SndMgr_EndMenuDuck(SndMgr *self) {
    self->menuDuck = 0;
    SndRamp_Set(&self->mainRamp, 70);
    SndRamp_Set(&self->subRamp, 40);
    SndRamp_Start(&self->mainRamp, 127, 5);
    SndRamp_Start(&self->subRamp, 127, 5);
}

extern "C" void SndMgr_DuckSubPlayers(SndMgr *self) {
    self->subDucked = 1;
    if (self->menuDuck != 0) {
        return;
    }
    SndRamp_Set(&self->subRamp, 127);
    SndRamp_Start(&self->subRamp, 40, 15);
}

extern "C" void SndMgr_RestoreSubPlayers(SndMgr *self) {
    self->subDucked = 0;
    if (self->menuDuck != 0) {
        return;
    }
    SndRamp_Set(&self->subRamp, 40);
    SndRamp_Start(&self->subRamp, 127, 15);
}

extern "C" void SndMgr_StartVolumeFadeIn(SndMgr *self) {
    SndRamp_Set(&self->fadeRamp, 0);
    SndRamp_Start(&self->fadeRamp, 127, 60);
}

extern "C" BgmBeatPhase *SndMgr_GetBeatState(SndMgr *self) {
    if (self->beatSync != NULL) {
        return &self->beatSync->sub;
    }
    return NULL;
}

extern "C" void SndMgr_UpdateVolumeCurve(SndMgr *self, u32 a) {
    u8 c = self->curveDelay;
    if (c != 0) {
        self->curveDelay = c - 1;
        return;
    }
    if (c != 0) {
        return;
    }
    SndVolumeCurve_Set(Snd_GetVolumeCurve(), a);
}

extern "C" void SndMgr_SetPanIfChanged(SndMgr *self, u8 v) {
    if (self->pan == v) {
        return;
    }
    self->pan = v;
    SndMgr_ApplyPan(self, 1);
}

extern "C" void SndMgr_SetPan(SndMgr *self, u8 v) {
    self->pan = v;
    SndMgr_ApplyPan(self, 1);
}

extern "C" void SndMgr_SetKeySeMode(SndMgr *self, u32 v) {
    switch (v) {
        case 1:
            self->keySeMode = 1;
            break;
        default:
            self->keySeMode = 0;
            break;
    }
}

extern "C" void SndMgr_PlayKeySe(SndMgr *self, u32 id) {
    u16 t = id - 1;
    if (t > 36) {
        Snd_StartSeqArcDefault(44, 0);
        return;
    }
    u8 m = self->keySeMode;
    if (m == 0) {
    } else if (m == 1) {
        t = t + 36;
    }
    Snd_StartSeqArcDefault(t, 3);
}

extern "C" void SndMgr_SetSeHandleVolumes(SndMgr *self, s32 v) {
    s32 a;
    s32 b;
    if (v < 0) {
        a = 16;
        b = 80;
    } else {
        a = v * 2 + 16;
        b = v + 80;
    }
    if (a > 127) {
        a = 127;
    }
    if (b > 127) {
        b = 127;
    }
    NNS_SndPlayerSetVolume(&self->seHandle, a);
    NNS_SndPlayerSetVolume(&self->auxSeHandle, b);
}

extern "C" void SndMgr_PlayAuxSe(SndMgr *self, u32 a) {
    Snd_StartSeqArcEx(&self->auxSeHandle, 10, -1, -1, 0, a);
}

extern "C" void SndMgr_PlayAuxSeHeld(SndMgr *self, u32 a) {
    Snd_StartSeqArcEx(&self->auxSeHandle, 10, -1, -1, 0, a);
}

extern "C" void SndMgr_StopAuxSe(SndMgr *self) {
    Snd_StopHandle(&self->auxSeHandle, 0);
}

extern "C" void SndMgr_StartBellRollSe(SndMgr *self) {
    Snd_StartSeqArc(45, 0, &self->seHandle);
}

extern "C" void SndMgr_StopBellRollSe(SndMgr *self) {
    SndMgr_StopSe(self, 45, 1);
}

extern "C" void SndMgr_PlaySePanned(SndMgr *self, u16 a, u32 b) {
    Snd_StartSeqArc(a, 0, &self->seHandle);
    NNS_SndPlayerSetTrackPan(&self->seHandle, gSndPanTrackMask, b);
}

extern "C" void SndRamp_Set(SndRamp *r, s32 v) {
    r->value = v << 12;
    r->frames = 0;
}

extern "C" void SndRamp_Start(SndRamp *r, s16 target, u32 frames) {
    r->target = target;
    r->frames = frames;
    s32 t = r->target << 12;
    s32 d = t - r->value;
    if (frames == 0) {
        r->value = t;
        return;
    }
    r->step = FX_Div(d, frames << 12);
}

extern "C" s16 SndRamp_Step(SndRamp *r) {
    if (r->frames != 0) {
        r->frames--;
        if (r->frames != 0) {
            r->value += r->step;
        } else {
            r->value = r->target << 12;
        }
    }
    return (s16)(r->value >> 12);
}

extern "C" u8 SndMgr_ClampVolume(SndMgr *self, u8 v) {
    if (v > 127) {
        v = 127;
    }
    return v;
}

extern "C" void SndMgr_UpdateVoice(SndMgr *self) {
    if (sVoicePendingSyllable != 0) {
        u16 a = SndMgr_GetVoiceSeqIndex(self, sVoicePendingSyllable);
        u8 b = SndMgr_ClampVolume(self, sVoicePendingVolume);
        SndMgr_PlayVoice(self, (u16)(a + 1), b, sVoicePendingPitch);
    }
    sVoicePendingSyllable = 0;
}

extern "C" u16 SndMgr_GetVoiceSeqIndex(SndMgr *self, u16 id) {
    switch (self->voiceType) {
        case 0:
        case 4:
            id = id + 206;
            break;
        case 1:
        case 3:
            id = id + 301;
            break;
        case 2:
            id = id + 396;
            break;
    }
    return id;
}

extern "C" s32 SndVoice_GetSyllable(s32 a, s32 b) {
    s32 r = 95;
    switch (a) {
        case 42:
            switch (b) {
                case 1: r = 59; break;
                case 2: r = 60; break;
                case 3: r = 61; break;
                case 4: r = 62; break;
                case 5: r = 63; break;
                case 6: r = 64; break;
                case 7: r = 65; break;
                case 8: r = 66; break;
                case 9: r = 67; break;
                case 10: r = 68; break;
                case 11: r = 0; break;
                case 12: r = 3; break;
                case 13: r = 7; break;
                case 14: r = 8; break;
                case 15: r = 12; break;
                case 16: r = 13; break;
                case 17: r = 14; break;
                case 18: r = 17; break;
                case 19: r = 22; break;
                case 20: r = 25; break;
                case 21: r = 27; break;
                case 22: r = 29; break;
                case 23: r = 30; break;
                case 24: r = 33; break;
                case 25: r = 42; break;
                case 26: r = 44; break;
                case 27: r = 28; break;
                case 28: r = 45; break;
                case 29: r = 46; break;
                case 30: r = 51; break;
                case 31: r = 54; break;
                case 32: r = 55; break;
                case 33: r = 56; break;
                case 34: r = 28; break;
                case 35: r = 57; break;
                case 36: r = 58; break;
                case 0:
                case 42:
                    r = 95;
                    break;
            }
            break;
        case 1: r = 59; break;
        case 2: r = 60; break;
        case 3: r = 61; break;
        case 4: r = 62; break;
        case 5: r = 63; break;
        case 6: r = 64; break;
        case 7: r = 65; break;
        case 8: r = 66; break;
        case 9: r = 67; break;
        case 10: r = 68; break;
        case 11:
            r = 0;
            switch (b) {
                case 24:
                    r = 1;
                    break;
                case 31:
                    r = 2;
                    break;
            }
            break;
        case 12:
            r = 3;
            switch (b) {
                case 15:
                    r = 4;
                    break;
                case 19:
                    r = 5;
                    break;
                case 35:
                    r = 6;
                    break;
            }
            break;
        case 13: r = 7; break;
        case 14:
            r = 8;
            if (b == 25) {
                r = 9;
            }
            break;
        case 15:
            r = 10;
            switch (b) {
                case 19:
                    r = 11;
                    break;
                case 28:
                    r = 12;
                    break;
            }
            break;
        case 16: r = 13; break;
        case 17:
            r = 14;
            if (b == 25) {
                r = 15;
            }
            break;
        case 18:
            r = 16;
            switch (b) {
                case 15:
                    r = 17;
                    break;
                case 19:
                    r = 18;
                    break;
                case 25:
                    r = 19;
                    break;
            }
            break;
        case 19:
            r = 20;
            switch (b) {
                case 24: r = 21; break;
                case 28: r = 22; break;
                case 29: r = 23; break;
                case 30: r = 24; break;
                case 42: r = 0; break;
            }
            break;
        case 20:
            r = 25;
            if (b == 31) {
                r = 26;
            }
            break;
        case 21:
            r = 27;
            if (b == 19) {
                r = 28;
            }
            break;
        case 22: r = 29; break;
        case 23:
            r = 30;
            switch (b) {
                case 15:
                    r = 31;
                    break;
                case 35:
                    r = 32;
                    break;
            }
            break;
        case 24: r = 33; break;
        case 25:
            r = 37;
            switch (b) {
                case 16: r = 38; break;
                case 18: r = 39; break;
                case 21: r = 40; break;
                case 24: r = 41; break;
                case 25: r = 42; break;
                case 28: r = 43; break;
            }
            break;
        case 26: r = 44; break;
        case 28: r = 45; break;
        case 29:
            r = 46;
            switch (b) {
                case 19:
                    r = 47;
                    break;
                case 25:
                    r = 48;
                    break;
                case 31:
                    r = 49;
                    break;
            }
            break;
        case 30:
            r = 50;
            switch (b) {
                case 18:
                    r = 51;
                    break;
                case 25:
                    r = 52;
                    break;
            }
            break;
        case 31:
            r = 53;
            if (b == 28) {
                r = 54;
            }
            break;
        case 32: r = 55; break;
        case 33: r = 56; break;
        case 34: r = 28; break;
        case 35: r = 57; break;
        case 36: r = 58; break;
    }
    return r;
}

u16 gSndPanTrackMask = 0x000f;
SndEnt sBgmTrackVariantTable[24] = {
    {0x00a0, 0x005f, 0x0100, 0x0604}, {0x07f8, 0x0007, 0x0000, 0x0800}, {0x0007, 0x0078, 0x0180, 0x07a0}, {0x00b8, 0x0347, 0x1c00, 0x6c00},
    {0x0084, 0x001b, 0x0060, 0x0360}, {0x0024, 0x000b, 0x00d0, 0x0380}, {0x0048, 0x05b7, 0x1a00, 0x7a00}, {0x083c, 0x01c3, 0x1600, 0x7600},
    {0x0443, 0x403c, 0x0180, 0xa180}, {0x000d, 0x0092, 0x0060, 0x0320}, {0x00d5, 0x042a, 0x0300, 0x1b00}, {0x02dc, 0x1123, 0x0c00, 0x6c00},
    {0x0038, 0x00c7, 0x0300, 0x0f04}, {0x00b0, 0x004f, 0x4f00, 0x7a00}, {0x0328, 0x00d7, 0x0c00, 0x3c02}, {0x002c, 0x0053, 0x0380, 0x0f80},
    {0x0570, 0x028f, 0x3800, 0xf000}, {0x005c, 0x02a3, 0x0d00, 0x3d00}, {0x032c, 0x0453, 0x0080, 0x1840}, {0x0152, 0x00ad, 0x0600, 0x1e00},
    {0x0078, 0x0007, 0x0080, 0x0380}, {0x0b41, 0x143e, 0x6080, 0xe080}, {0x1870, 0x018f, 0x0000, 0x1e00}, {0x003c, 0x0003, 0x1800, 0xfc00},
};
