#include "ds_div.h"
#include "types.h"
#include "gfx/VecFx32.h"
#include "snd/Melody.h"
#include "snd/SndMgr.h"
#include "snd/SndScenes.h"
#include "proto/autoload_2/unk_020ed8cc.h"
#include "proto/autoload_2/unk_020ef150.h"
#include "proto/autoload_2/unk_020f0dec.h"
#include "proto/autoload_2/unk_020f4a5c.h"
#include "proto/autoload_2/unk_0210c084.h"

typedef SndScene10 MelodyScene;

extern "C" {
void NNS_SndPlayerSetVolume(void *p, s32 v);
void NNS_SndHandleReleaseSeq(void *p);
void NNS_SndPlayerSetTrackVolume(void *p, u32 a, s32 b);
void NNS_SndPlayerSetTrackPan(void *p, u32 a, s32 b);
void NNS_SndPlayerSetTempoRatio(void *p, s32 v);
void NNS_SndPlayerReadVariable(void *p, u32 a, void *out);
void NNS_SndHeapLoadState(void *a, u32 b);
s32 FX_Div(s32 a, s32 b);

s32 Snd_DistanceToVolume(s32 x);
s32 Snd_CalcPan(VecFx32 *p, s32 m);
s32 Snd_CalcListenerDistance(VecFx32 *p, s32 m);
}

extern const u8 sMelodyPresetPatterns[48][16];
extern const u8 sMelodyDefaultPattern[16];
extern const u8 data_0213597c[16];

static inline s32 FX_Mul(s32 a, s32 b) {
    return (s32)(((s64)a * b + 0x800) >> 12);
}

MelodyTrack::~MelodyTrack() {
    NNS_SndHandleReleaseSeq(this);
}

extern "C" void MelodyTrack_Init(MelodyTrack *self) {
    MelodyTrack_Reset(self);
    Snd_InitHandle(self);
}

extern "C" void MelodyTrack_Start(MelodyTrack *self, u16 id, u8 *pat) {
    MelodyTrack_Reset(self);
    if (self->handle != NULL) Snd_StopHandle(self, 0);
    self->id = id;
    self->pat = pat;
    self->active = 1;
    Snd_StartSeqArc(0, self->id, self);
}

extern "C" void MelodyTrack_StartPattern(MelodyTrack *self, u8 *pat) {
    MelodyTrack_Reset(self);
    if (self->handle != NULL) Snd_StopHandle(self, 0);
    self->pat = pat;
    self->active = 1;
    Snd_StartSeqArc(0, self->id, self);
}

extern "C" void MelodyTrack_PlayNote(MelodyTrack *self, u32 idx) {
    MelodyTrack_Reset(self);
    if (idx > 13) return;
    if (self->handle != NULL) Snd_StopHandle(self, 0);
    Snd_StartSeqArc(idx + 20, 0xd3, self);
}

extern "C" void MelodyTrack_SetInstrument(MelodyTrack *s, u16 v) {
    s->id = v;
}

extern "C" void MelodyTrack_Stop(MelodyTrack *p) {
    Snd_StopHandle(p, 5);
}

extern "C" void MelodyTrack_Reset(MelodyTrack *self) {
    self->active = 0;
    self->pos = -1;
    self->tick = 0;
    self->s14 = self->s15 = self->s16 = self->s17 = -1;
}

extern "C" void MelodyTrack_ReadParams(MelodyTrack *self) {
    s16 a, b, c, d;
    d = -1;
    c = -1;
    b = -1;
    a = -1;
    NNS_SndPlayerReadVariable(self, 0, &a);
    NNS_SndPlayerReadVariable(self, 1, &b);
    NNS_SndPlayerReadVariable(self, 2, &c);
    NNS_SndPlayerReadVariable(self, 3, &d);
    self->s14 = a;
    self->s15 = b;
    self->s16 = c;
    self->s17 = d;
}

extern "C" u8 MelodyTrack_GetStepNote(MelodyTrack *self, u8 idx) {
    u8 r;
    switch (self->s16) {
    case 0:
        r = self->pat[idx];
        break;
    case 1: {
        u8 m = idx % 3;
        if (m == 1) {
            r = 14;
        } else {
            u8 q = idx / 3;
            if (m == 0) {
                r = self->pat[q * 2];
            } else {
                r = self->pat[q * 2 + 1];
            }
        }
        break;
    }
    case 2: {
        u8 m = idx % 3;
        if (m == 2) {
            r = 14;
        } else {
            u8 q = idx / 3;
            if (m == 0) {
                r = self->pat[q * 2];
            } else {
                r = self->pat[q * 2 + 1];
            }
        }
        break;
    }
    case 3: {
        s32 found = 0;
        s32 j;
        for (j = 0; j < 13; j++) {
            if (idx == data_0213597c[j]) {
                r = self->pat[j];
                found = 1;
            }
        }
        if (found == 0) r = 14;
        break;
    }
    }
    return r;
}

extern "C" void MelodyTrack_PlayStep(MelodyTrack *self) {
    u32 v = MelodyTrack_GetStepNote(self, self->pos);
    s32 d = DS_DIV(153600, (self->s14 * 120));
    switch (v) {
    case 13:
        Snd_StartSeqArc(v + 1 + SndMgr_Rand(&gSndMgr, 6), self->id, self);
        NNS_SndPlayerSetTempoRatio(self, d);
        break;
    case 14:
    case 15:
        break;
    default:
        Snd_StartSeqArc(v + 1, self->id, self);
        NNS_SndPlayerSetTempoRatio(self, d);
        break;
    }
    if (self->s16 != 3) return;
    {
        const u8 *t = data_0213597c;
        s32 p = self->pos;
        s32 vol;
        if (p == t[0]) vol = 64;
        else if (p == t[1]) vol = 80;
        else if (p == t[2]) vol = 96;
        else if (p == t[3]) vol = 112;
        else if (p == t[4]) vol = 127;
        else if (p == t[5]) vol = 127;
        else if (p == t[6]) vol = 112;
        else if (p == t[7]) vol = 96;
        else if (p == t[8]) vol = 80;
        else if (p == t[9]) vol = 64;
        else if (p == t[10]) vol = 48;
        else if (p == t[11]) vol = 32;
        else if (p == t[12]) vol = 16;
        else vol = -1;
        if (vol != -1) NNS_SndPlayerSetVolume(self, vol);
    }
    {
        MelodyPlayer *c = gSndMgr.melody;
        NNS_SndPlayerSetTrackVolume(self, 0xff, c->b39);
        NNS_SndPlayerSetTrackPan(self, 0xff, c->b3a);
    }
}

extern "C" BOOL MelodyTrack_CheckEnd(MelodyTrack *self) {
    s8 k = self->s16;
    u32 v;
    if (k == 0) {
        if (self->pos == 15) {
            Snd_StopHandle(self, 0);
            gSndMgr.melody->b3c = 0;
            return TRUE;
        }
    } else if ((u8)(s8)(k - 1) <= 1) {
        if (self->pos == 23) {
            Snd_StopHandle(self, 0);
            gSndMgr.melody->b3c = 0;
            return TRUE;
        }
    } else if (k == 3) {
        if (self->pos == data_0213597c[12] + 6) {
            Snd_StopHandle(self, 0);
            gSndMgr.melody->b3c = 0;
            return TRUE;
        }
    }
    v = MelodyTrack_GetStepNote(self, self->pos + 1);
    if (v != 14 && (v != 15 || self->s17 != 1)) Snd_StopHandle(self, 0);
    return FALSE;
}

extern "C" s32 MelodyTrack_Update(MelodyTrack *self) {
    s32 r = -1;
    if (self->active) {
        if (self->s14 == -1) {
            MelodyTrack_ReadParams(self);
        } else {
            BOOL t = 0;
            if (self->tick == self->s15) t = MelodyTrack_CheckEnd(self);
            if (t) {
                MelodyTrack_Reset(self);
            } else {
                if (self->tick == 0 || self->tick == self->s14) {
                    self->tick = 0;
                    self->pos++;
                    MelodyTrack_PlayStep(self);
                }
                self->tick++;
            }
            r = self->pos;
        }
    }
    return r;
}

extern "C" void MelodyPlayer_Init(MelodyPlayer *c) {
    gSndMgr.melody = c;
    MelodyTrack_Init(&c->b);
    MelodyTrack_Init(&c->a);
    MelodyTrack_SetInstrument(&c->a, 0);
    c->b38 = 0;
    c->b39 = -1;
    c->b3a = 0;
    c->b3b = 0;
}

extern "C" u8 *Melody_GetDefaultPattern(void) {
    return (u8 *)sMelodyDefaultPattern;
}

extern "C" void MelodyPlayer_SetPattern(MelodyPlayer *c, u8 *src) {
    s32 i;
    for (i = 0; i < 16; i++) {
        c->pat[i] = src[i];
    }
}

extern "C" u8 *MelodyPlayer_GetPattern(MelodyPlayer *c) {
    return c->pat;
}

extern "C" void MelodyPlayer_PlayPattern(MelodyPlayer *c, u32 v, u8 *pat) {
    u32 w;
    c->b3c = 1;
    c->b39 = -1;
    if (v == 400) {
        MelodyTrack_Start(&c->b, 0xd3, pat);
        return;
    }
    if (v < 200) {
        MelodyPlayer_LoadBank(c, v + 0x1df);
        w = v + 4;
        MelodyPlayer_LoadSeqArc(c, w);
        MelodyTrack_Start(&c->b, w, pat);
    } else {
        MelodyPlayer_LoadBank(c, v + 0x1ad);
        w = v - 0x2e;
        MelodyPlayer_LoadSeqArc(c, w);
        MelodyTrack_Start(&c->b, w, pat);
    }
}

extern "C" void MelodyPlayer_Play(MelodyPlayer *c, u32 v) {
    u32 w;
    c->b3c = 1;
    c->b39 = -1;
    if (v < 200) {
        MelodyPlayer_LoadBank(c, v + 0x1df);
        w = v + 4;
        MelodyPlayer_LoadSeqArc(c, w);
        MelodyTrack_Start(&c->b, w, c->pat);
    } else {
        MelodyPlayer_LoadBank(c, v + 0x1ad);
        w = v - 0x2e;
        MelodyPlayer_LoadSeqArc(c, w);
        MelodyTrack_Start(&c->b, w, c->pat);
    }
}

extern "C" void MelodyPlayer_PlayRandom(MelodyPlayer *c, u32 v) {
    u32 w;
    c->b3c = 1;
    c->b39 = -1;
    if (v > 200) return;
    MelodyPlayer_LoadBank(c, v + 0x1df);
    w = v + 4;
    MelodyPlayer_LoadSeqArc(c, w);
    c->b3b = SndMgr_Rand(&gSndMgr, 0x30);
    MelodyTrack_Start(&c->b, w, (u8 *)sMelodyPresetPatterns[c->b3b]);
}

extern "C" u8 *MelodyPlayer_ApplyRandomPattern(MelodyPlayer *c) {
    const u8 *src = sMelodyPresetPatterns[c->b3b];
    s32 i;
    for (i = 0; i < 16; i++) {
        c->pat[i] = src[i];
    }
    return c->pat;
}

extern "C" void MelodyPlayer_StopTrackB(MelodyPlayer *c) {
    MelodyTrack_Stop(&c->b);
    c->b.active = 0;
}

extern "C" void MelodyPlayer_StartTrackA(MelodyPlayer *c) {
    MelodyTrack_StartPattern(&c->a, c->pat);
}

extern "C" void MelodyPlayer_PlayAt(MelodyPlayer *c, VecFx32 *pos, u32 mode) {
    u32 a;
    u32 b;
    if ((u8)(c->b3c + 255) <= 1) return;
    c->b39 = Snd_DistanceToVolume(Snd_CalcListenerDistance(pos, 0));
    c->b3a = Snd_CalcPan(pos, 0);
    c->b3c = 4;
    switch (mode) {
    case 0:
        a = 0x1db;
        b = 0xd4;
        break;
    case 1:
        a = 0x1de;
        b = 0xd7;
        break;
    case 2:
        a = 0x1dc;
        b = 0xd5;
        break;
    case 3:
        a = 0x1dd;
        b = 0xd6;
        break;
    default:
        return;
    }
    MelodyPlayer_LoadBank(c, a);
    MelodyPlayer_LoadSeqArc(c, b);
    MelodyTrack_Start(&c->b, b, c->pat);
}

extern "C" void MelodyPlayer_PlayNote(MelodyPlayer *c, u32 idx) {
    MelodyTrack_PlayNote(&c->b, idx);
}

extern "C" s32 MelodyPlayer_Update(MelodyPlayer *c) {
    c->b38 = MelodyTrack_Update(&c->a) >= 0;
    return MelodyTrack_Update(&c->b);
}

extern "C" u8 MelodyPlayer_IsPlaying(MelodyPlayer *c) {
    return c->b38;
}

extern "C" void MelodyPlayer_SetInstrument(MelodyPlayer *c, u16 v) {
    MelodyTrack_SetInstrument(&c->a, v);
}

extern "C" void MelodyPlayer_LoadBank(MelodyPlayer *c, u32 id) {
    void *h = gSndMgr.subHeap;
    NNS_SndHeapLoadState(h, 0);
    NNS_SndArcLoadBank(id, h);
}

extern "C" void MelodyPlayer_LoadSeqArc(MelodyPlayer *c, u32 id) {
    NNS_SndArcLoadSeqArc(id, gSndMgr.subHeap);
}

extern "C" void MelodyBeat_Construct(void) {
}

extern "C" void MelodyBeat_Destruct(void) {
}

extern "C" void MelodyBeat_Init(MelodyBeat *self) {
    sMelodyBeatPattern = MelodyPlayer_GetPattern(gSndMgr.melody);
    Snd_InitHandle(self);
    self->active = 0;
    self->step = -1;
    self->tick = 0;
    self->v8 = self->v9 = -1;
}

extern "C" void MelodyBeat_Stop(MelodyBeat *self) {
    self->active = 0;
    if (self->handle != NULL) Snd_StopHandle(self, 0);
    NNS_SndHandleReleaseSeq(self);
}

extern "C" void MelodyBeat_Start(MelodyBeat *self, u16 id) {
    MelodyPlayer *c = gSndMgr.melody;
    MelodyScene *o;
    void *h;
    u32 ok;
    if (c->b3c == 1) return;
    Snd_StopHandle(self, 0);
    c->b3c = 2;
    data_021f5c28 = self->id;
    self->id = id;
    ok = 0;
    self->active = 1;
    self->step = -1;
    if (NNS_SndArcPlayerStartSeqArc(self, self->id, ok)) {
        if (data_021f5c28 == self->id) ok = 1;
        Snd_StopHandle(self, 0);
    }
    if (ok) return;
    o = (MelodyScene *)gSndMgr.scene;
    if (o == 0) return;
    if (o->f6 != 0) {
        data_0213b9d8 = 2;
    } else {
        data_0213b9d8 = (data_0213b9d8 == 1) ? 2 : 1;
    }
    if (data_0213b9d8 == 1) {
        h = Snd_GetHeap();
        NNS_SndHeapLoadState(h, o->f1d + 1);
    } else if (data_0213b9d8 == 2) {
        h = gSndMgr.subHeap;
        Snd_GetHeap();
        NNS_SndHeapLoadState(h, 0);
    }
    {
        u32 sid = self->id;
        NNS_SndArcLoadSeqArc(sid, h);
        NNS_SndArcLoadBank(sid + 0x1db, h);
    }
}

extern "C" void MelodyBeat_Update(MelodyBeat *self, VecFx32 *pos) {
    MelodyScene *o;
    u8 flag;
    s32 v;
    s32 w;
    if (self->active == 0) return;
    if (self->v8 == -1) {
        if (self->handle == NULL) Snd_StartSeqArc(0, self->id, self);
        MelodyBeat_ReadParams(self);
        return;
    }
    self->tick++;
    o = (MelodyScene *)gSndMgr.scene;
    flag = o->tempo.c10;
    if (self->tick >= self->limit) {
        BOOL done = MelodyBeat_EndStep(self);
        self->tick = 0;
        if (done) return;
    }
    if (flag == 0) return;
    self->step++;
    self->tick = 0;
    if (self->step < 16) {
        MelodyBeat_PlayStep(self, pos);
    } else if (self->step >= 16) {
        MelodyBeat_EndStep(self);
        return;
    }
    v = self->v8;
    w = o->tempo.w4;
    if (v == 100) {
        self->limit = w >> 12;
        return;
    }
    self->limit = FX_Mul(w, FX_Div(v << 12, 100 << 12)) >> 12;
}

extern "C" void MelodyBeat_ReadParams(MelodyBeat *self) {
    s16 a, b;
    b = -1;
    a = -1;
    NNS_SndPlayerReadVariable(self, 4, &a);
    NNS_SndPlayerReadVariable(self, 3, &b);
    self->v8 = a;
    self->v9 = b;
}

extern "C" void MelodyBeat_PlayStep(MelodyBeat *self, VecFx32 *pos) {
    u32 v = sMelodyBeatPattern[self->step];
    switch (v) {
    case 13:
        if (self->handle != NULL) Snd_StopHandle(self, 0);
        NNS_SndArcPlayerStartSeqArc(self, self->id, (u16)(v + 1 + SndMgr_Rand(&gSndMgr, 6)));
        MelodyBeat_ApplyPosition(self, pos);
        return;
    case 14:
    case 15:
        return;
    }
    if (self->handle != NULL) Snd_StopHandle(self, 0);
    NNS_SndArcPlayerStartSeqArc(self, self->id, (u16)(v + 1));
    MelodyBeat_ApplyPosition(self, pos);
}

extern "C" BOOL MelodyBeat_EndStep(MelodyBeat *self) {
    s32 s = self->step;
    if (s >= 15) {
        Snd_StopHandle(self, 0);
        gSndMgr.melody->b3c = 0;
        self->active = 0;
        self->step = -1;
        self->tick = 0;
        return TRUE;
    }
    u32 v = sMelodyBeatPattern[s + 1];
    if (v != 14) {
        if (v == 15) {
            if (self->v9 != 1) Snd_StopHandle(self, 0);
        } else {
            Snd_StopHandle(self, 0);
        }
    }
    return FALSE;
}

extern "C" void MelodyBeat_ApplyPosition(MelodyBeat *obj, VecFx32 *pos) {
    s32 a = Snd_DistanceToVolume(Snd_CalcListenerDistance(pos, 0));
    s32 b = Snd_CalcPan(pos, 0);
    NNS_SndPlayerSetTrackVolume(obj, 15, a);
    NNS_SndPlayerSetTrackPan(obj, 15, b);
}

u8 data_0213b9d8 = 1;
u16 data_021f5c28;
u8 *sMelodyBeatPattern;
const u8 data_0213597c[16] = {0, 2, 3, 4, 5, 6, 7, 9, 11, 15, 19, 25, 33, 0, 0, 0};
const u8 sMelodyDefaultPattern[16] = {10, 12, 10, 7, 6, 7, 9, 11, 10, 15, 13, 15, 3, 14, 14, 15};
const u8 sMelodyPresetPatterns[48][16] = {
    {10, 14, 3, 14, 4, 9, 14, 3, 6, 7, 8, 9, 10, 14, 14, 14},
    {0, 2, 4, 7, 9, 14, 8, 14, 0, 2, 4, 7, 9, 14, 14, 14},
    {10, 9, 8, 7, 6, 5, 4, 3, 2, 3, 4, 5, 3, 15, 15, 15},
    {4, 7, 9, 7, 8, 11, 4, 7, 9, 7, 8, 11, 15, 15, 15, 15},
    {9, 9, 15, 9, 15, 7, 9, 15, 11, 15, 15, 15, 15, 15, 15, 15},
    {3, 7, 5, 7, 2, 7, 6, 7, 5, 7, 10, 9, 10, 14, 3, 15},
    {8, 7, 3, 15, 8, 7, 3, 15, 8, 7, 8, 7, 6, 15, 15, 15},
    {3, 15, 3, 4, 5, 15, 4, 3, 15, 7, 15, 5, 15, 10, 15, 15},
    {7, 15, 5, 15, 6, 4, 2, 4, 3, 5, 7, 13, 3, 14, 15, 15},
    {10, 9, 15, 8, 7, 8, 15, 9, 10, 15, 7, 15, 13, 15, 15, 15},
    {6, 8, 10, 15, 6, 8, 10, 15, 8, 10, 8, 10, 14, 14, 14, 14},
    {0, 0, 0, 0, 7, 15, 0, 0, 15, 5, 15, 0, 1, 14, 14, 14},
    {5, 15, 15, 5, 6, 15, 15, 6, 7, 15, 15, 8, 14, 7, 5, 3},
    {5, 14, 6, 5, 4, 14, 2, 4, 3, 14, 13, 14, 3, 14, 14, 14},
    {6, 3, 6, 7, 8, 3, 6, 8, 7, 3, 10, 7, 6, 5, 6, 14},
    {7, 14, 3, 2, 3, 4, 5, 6, 7, 15, 9, 15, 13, 15, 15, 15},
    {11, 9, 10, 11, 15, 15, 4, 10, 9, 7, 8, 9, 14, 15, 15, 15},
    {5, 14, 6, 14, 7, 14, 10, 14, 11, 14, 10, 14, 12, 14, 14, 15},
    {12, 14, 11, 14, 8, 14, 9, 14, 10, 14, 14, 14, 14, 15, 15, 15},
    {4, 5, 6, 4, 3, 14, 14, 15, 2, 3, 4, 14, 3, 14, 14, 14},
    {5, 8, 7, 8, 5, 15, 15, 15, 5, 8, 7, 8, 5, 15, 15, 15},
    {8, 12, 11, 10, 8, 15, 7, 15, 8, 14, 14, 14, 15, 15, 15, 15},
    {3, 6, 15, 6, 5, 15, 4, 15, 3, 15, 9, 15, 10, 15, 15, 15},
    {1, 1, 1, 2, 3, 2, 1, 5, 6, 8, 6, 4, 5, 14, 14, 15},
    {7, 7, 15, 7, 7, 15, 8, 15, 7, 6, 5, 13, 3, 15, 15, 15},
    {6, 15, 15, 6, 4, 15, 15, 4, 7, 15, 15, 7, 3, 3, 4, 5},
    {6, 15, 6, 7, 8, 15, 6, 8, 7, 15, 10, 7, 6, 5, 6, 15},
    {6, 15, 8, 10, 9, 15, 10, 15, 6, 6, 8, 10, 9, 11, 10, 15},
    {3, 5, 15, 6, 7, 15, 3, 6, 15, 7, 8, 15, 7, 10, 9, 10},
    {7, 7, 7, 9, 10, 10, 10, 15, 11, 9, 8, 9, 13, 15, 15, 15},
    {2, 4, 7, 9, 11, 15, 12, 14, 11, 10, 9, 13, 7, 15, 15, 15},
    {8, 14, 14, 7, 14, 14, 6, 14, 7, 5, 4, 3, 2, 14, 4, 3},
    {5, 14, 14, 8, 14, 7, 6, 14, 7, 5, 14, 14, 14, 15, 5, 8},
    {3, 5, 7, 10, 9, 7, 4, 5, 6, 8, 10, 12, 11, 9, 10, 14},
    {10, 15, 10, 9, 10, 15, 10, 9, 10, 15, 7, 15, 3, 15, 13, 15},
    {7, 14, 8, 9, 14, 10, 11, 14, 14, 7, 14, 14, 13, 14, 14, 14},
    {3, 14, 7, 14, 5, 14, 10, 14, 11, 14, 8, 11, 9, 14, 10, 15},
    {4, 11, 15, 10, 9, 15, 8, 15, 7, 15, 8, 15, 13, 15, 15, 15},
    {7, 8, 7, 8, 7, 15, 12, 15, 10, 15, 13, 15, 3, 14, 14, 14},
    {9, 11, 14, 9, 11, 14, 10, 12, 14, 10, 12, 14, 11, 9, 8, 7},
    {9, 9, 15, 9, 10, 15, 15, 11, 15, 9, 15, 8, 7, 15, 15, 15},
    {6, 10, 8, 15, 6, 10, 8, 7, 6, 10, 9, 10, 13, 14, 14, 14},
    {8, 15, 5, 7, 8, 15, 5, 7, 8, 8, 8, 10, 13, 14, 14, 15},
    {3, 5, 7, 15, 8, 14, 14, 7, 6, 5, 4, 13, 3, 15, 15, 15},
    {6, 3, 15, 6, 5, 3, 15, 5, 4, 15, 13, 15, 3, 15, 15, 15},
    {7, 14, 7, 7, 8, 7, 5, 4, 3, 15, 13, 15, 3, 14, 15, 15},
    {3, 15, 0, 15, 3, 15, 0, 15, 0, 0, 1, 2, 13, 15, 15, 15},
    {5, 15, 7, 6, 5, 15, 4, 15, 3, 4, 5, 7, 10, 15, 15, 15},
};
