#include "uptr.h"
#include "types.h"
#include "snd/PlayCtx.h"
#include "snd/SndSeBytes4.h"
#include "snd/SndSeGroup.h"
#include "sys/FndList.h"
#include "snd/Player.h"
#include "proto/autoload_2/unk_020ede18.h"
#include "proto/autoload_2/unk_020ed8cc.h"
#include "proto/autoload_2/unk_020ef150.h"
#include "proto/autoload_2/unk_0210c084.h"
#include "proto/main/unk_0206d49c.h"

extern "C" {
void NNS_SndHandleInit(void *h);
void NNS_SndPlayerStopSeq(void *h, s32 frames);
void NNS_SndHandleReleaseSeq(void *h);
InfoB *NNS_SndArcGetSeqArcSeqParam(u32 seqArc, u32 idx);
void NNS_SndPlayerSetVolume(void *h, u8 v);
void NNS_SndPlayerSetPlayerPriority(void *h, u8 prio);
void NNS_SndPlayerSetTrackPan(void *h, u32 mask, u32 pan);
void NNS_SndPlayerSetTrackVolume(void *h, u32 mask, s32 v);
void NNS_SndPlayerSetTrackPitch(void *h, u32 mask, u32 pitch);
void *NNS_FndGetPrevListObject(void *list, void *obj);
void *NNS_FndGetNextListObject(void *list, void *obj);
void NNS_FndRemoveListObject(void *list, void *obj);
void NNS_FndAppendListObject(void *list, void *obj);

void SndSeGroup_StopHeld(Group *g, s32 a);
void SndSeGroup_StopAll(Group *g, s32 a);
void SndSeGroup_StopVoice(Group *g, s32 i, s32 a);
void SndSeGroup_ReleaseAll(Group *g);
void SndSeGroup_Shutdown(Group *g);
}

extern "C" void SndList_InitLink(void **p) {
    if (p == NULL) Fatal_Trap();
    p[0] = NULL;
    p[1] = NULL;
}

extern "C" void SndList_Append(void *list, void *obj) {
    NNS_FndAppendListObject(list, obj);
}

extern "C" void SndList_Remove(void *list, void *obj) {
    NNS_FndRemoveListObject(list, obj);
}

extern "C" void *SndList_GetNext(void *list, void *obj) {
    return NNS_FndGetNextListObject(list, obj);
}

extern "C" void *SndList_GetPrev(void *list, void *obj) {
    return NNS_FndGetPrevListObject(list, obj);
}

extern "C" void *SndList_GetFirst(void **p) {
    return p[0];
}

extern "C" void *SndList_GetLast(void **p) {
    return p[1];
}

extern "C" void SndSeGroup_StartVoice(Group *g, s32 i, s32 v) {
    Ent *e = &g->voices[i];
    if (g->numVoices == 0) Fatal_Trap();
    NNS_SndArcPlayerStartSeqArcEx(e, -1, -1, v, e->seqArc, e->index);
}

extern "C" void SndSeGroup_ApplyVoiceParams(Group *g, s32 i) {
    Ent *e = &g->voices[i];
    if (g->numVoices == 0) Fatal_Trap();
    NNS_SndPlayerSetTrackVolume(e, gSndPanTrackMask, e->trackVolume);
    NNS_SndPlayerSetTrackPitch(e, gSndPanTrackMask, e->trackPitch);
}

extern "C" void Snd_SetListenerPanCallback(s32 (*f)(PlayCtx *)) {
    gSndListenerPanCallback = f;
}

extern "C" void Snd_SetListenerDistanceCallback(s32 (*f)(PlayCtx *)) {
    gSndListenerDistanceCallback = f;
}

extern "C" void Snd_SetListenerVolumeCallback(s32 (*f)(PlayCtx *)) {
    gSndListenerVolumeCallback = f;
}

extern "C" void SndSeGroup_EvalListener(PlayCtx *p) {
    if (p->source == NULL) {
        p->distance = 0;
        p->volume = 127;
        p->baseVolume = 127;
        p->pan = 0;
        return;
    }
    if (gSndListenerDistanceCallback == NULL) Fatal_Trap();
    if (gSndListenerVolumeCallback == NULL) Fatal_Trap();
    if (gSndListenerPanCallback == NULL) Fatal_Trap();
    p->distance = gSndListenerDistanceCallback(p);
    p->volume = gSndListenerVolumeCallback(p);
    p->baseVolume = p->volume;
    p->pan = gSndListenerPanCallback(p);
}

extern "C" void SndSeVoice_Init(Ent *e) {
    NNS_SndHandleInit(e);
    e->seqArc = 0;
    e->index = 0;
    e->flags = 0;
    e->trackPitch = 0;
    e->trackVolume = 127;
}

extern "C" void SndSeVoice_SetParams(Ent *e, s32 c, s32 d) {
    e->trackVolume = c;
    e->trackPitch = d;
}

extern "C" void SndSeVoice_Start(Ent *e, u32 a, u32 b, s32 c, s16 d) {
    if (e == NULL) Fatal_Trap();
    e->seqArc = a;
    e->index = b;
    SndSeVoice_SetFlag(e, 1, 1);
    SndSeVoice_SetParams(e, c, d);
}

extern "C" void SndSeVoice_StartHeld(Ent *e, u32 a, u32 b, s32 c, s16 d) {
    SndSeVoice_Start(e, a, b, c, d);
    SndSeVoice_SetFlag(e, 2, 1);
    SndSeVoice_SetFlag(e, 3, 1);
}

extern "C" BOOL SndSeVoice_IsPlayingId(Ent *e, u32 a, u32 b) {
    if (e->handle != NULL && e->index == b && e->seqArc == a) return TRUE;
    return FALSE;
}

extern "C" void SndSeVoice_Stop(Ent *e, s32 x) {
    if (e->handle != NULL) NNS_SndPlayerStopSeq(e, x);
    SndSeVoice_SetFlag(e, 2, 0);
    SndSeVoice_SetFlag(e, 3, 0);
    SndSeVoice_SetFlag(e, 1, 0);
}

extern "C" void SndSeVoice_SetFlag(Ent *e, s32 bit, s32 on) {
    if (e == NULL) Fatal_Trap();
    if (on == 1) {
        e->flags |= (1 << bit);
    } else {
        e->flags &= ~(1 << bit);
    }
}

extern "C" BOOL SndSeVoice_IsHeld(Ent *e) {
    return (e->flags & 4) != 0;
}

extern "C" void SndSeGroup_SetFlag(Group *g, s32 bit, s32 on) {
    if (g == NULL) Fatal_Trap();
    if (on == 1) {
        g->flags |= (1 << bit);
    } else {
        g->flags &= ~(1 << bit);
    }
}

extern "C" void SndSeGroup_SetEnabled(Group *g, s32 x) {
    if (g == NULL) Fatal_Trap();
    SndSeGroup_SetFlag(g, 0, x);
}

extern "C" s32 SndSeGroup_FindFreeVoice(Group *g) {
    s32 i;
    s32 n = g->numVoices;
    for (i = 0; i < n; i++) {
        if (g->voices[i].handle == NULL && (g->voices[i].flags & 2) == 0) return i;
    }
    return n;
}
#ifdef HOST64
#include "snd/SndSeEmitter.h"
static_assert(sizeof(SndHandle) == sizeof(Group), "SndHandle views Group");
static_assert(__builtin_offsetof(SndHandle, volCb) == __builtin_offsetof(Group, applyParamsFn), "SndHandle::volCb");
#endif

extern "C" void SndSeGroup_Init(Group *g) {
    s32 i;
    Ent *e;
    g->numVoices = 3;
    g->startVoiceFn = (GroupFn)SndSeGroup_StartVoice;
    g->applyParamsFn = (GroupFn)SndSeGroup_ApplyVoiceParams;
    if (g->numVoices > 3) Fatal_Trap();
    g->flags = 0;
    i = 0;
    if ((s32)g->numVoices > 0) {
        e = g->voices;
        do {
            SndSeVoice_Init(e);
            i++;
            e++;
        } while (i < g->numVoices);
    }
    Player *c = &gSndSeSystem;
    if (!((s32)c->active >= 1 && (s32)c->active < 4)) Fatal_Trap();
}

extern "C" void SndSeGroup_Finish(Group *g) {
    SndSeGroup_Shutdown(g);
}

extern "C" void SndSeGroup_Update(Group *g, void *src) {
    PlayCtx ctx;
    s32 vol;
    s32 x;
    s32 i;
    BOOL inited = FALSE;
    Ent *e;
    if (g->numVoices == 0) Fatal_Trap();
    if ((g->flags & 1) == 0) {
        if ((g->flags & 2) == 0) return;
        SndSeGroup_StopHeld(g, 0);
        SndSeGroup_SetFlag(g, 1, 0);
        return;
    }
    i = 0;
    ctx.group = g;
    ctx.source = src;
    ctx.unk_20 = 0;
    ctx.volume = 0;
    ctx.baseVolume = 0;
    ctx.pan = 0;
    if ((s32)g->numVoices > 0) {
        e = g->voices;
        do {
            vol = -1;
            x = 0;
            if (SndSeVoice_IsHeld(e) != 0) {
                if ((e->flags & 8) == 0) {
                    SndSeGroup_StopVoice(g, i, 0);
                    goto next;
                }
                SndSeVoice_SetFlag(e, 3, 0);
                x = 2;
            }
            if ((e->flags & 2) != 0) {
                if (!inited) {
                    SndSeGroup_EvalListener(&ctx);
                    inited = TRUE;
                }
                if (ctx.volume > 0) {
                    s32 base = ctx.baseVolume;
                    InfoB *inf = NNS_SndArcGetSeqArcSeqParam(e->seqArc, e->index);
                    if (inf == NULL) Fatal_Trap();
                    vol = base + (inf->playerPrio - 64);
                    if (vol > 0) {
                        if (vol >= 127) vol = 127;
                    } else {
                        vol = 0;
                    }
                    g->startVoiceFn(g, i, vol);
                    x = 1;
                }
                SndSeVoice_SetFlag(e, 1, 0);
            }
            if (x == 0) {
                if ((e->flags & 1) != 0) {
                    x = 2;
                } else {
                    x = 0;
                }
            }
            if (x != 0 && e->handle != NULL) {
                if (!inited) {
                    SndSeGroup_EvalListener(&ctx);
                    inited = TRUE;
                }
                if (vol == -1) {
                    s32 base = ctx.baseVolume;
                    InfoB *inf = NNS_SndArcGetSeqArcSeqParam(e->seqArc, e->index);
                    if (inf == NULL) Fatal_Trap();
                    vol = base + (inf->playerPrio - 64);
                    if (vol > 0) {
                        if (vol >= 127) vol = 127;
                    } else {
                        vol = 0;
                    }
                }
                if (!inited) Fatal_Trap();
                NNS_SndPlayerSetVolume(e, ctx.volume);
                NNS_SndPlayerSetPlayerPriority(e, vol);
                NNS_SndPlayerSetTrackPan(e, gSndPanTrackMask, ctx.pan);
                g->applyParamsFn(g, i, vol);
            }
        next:
            e++;
            i++;
        } while (i < g->numVoices);
    }
    SndSeGroup_SetFlag(g, 1, 1);
}

extern "C" s32 SndSeGroup_Play(Group *g, u32 a, u32 b, s32 c, s16 d) {
    s32 r = 255;
    s32 i;
    Ent *e;
    if ((g->flags & 1) == 0) return -1;
    i = 0;
    if ((s32)g->numVoices > 0) {
        e = g->voices;
        do {
            if (SndSeVoice_IsPlayingId(e, a, b) != 0) {
                r = i;
                SndSeGroup_StopVoice(g, i, 0);
                break;
            }
            i++;
            e++;
        } while (i < g->numVoices);
    }
    if (r == 255) r = SndSeGroup_FindFreeVoice(g);
    if (r == g->numVoices) return -1;
    SndSeVoice_Start(&g->voices[r], a, b, c, d);
    return r;
}

extern "C" s32 SndSeGroup_PlayHeld(Group *g, u32 a, u32 b, s32 c, s16 d) {
    s32 i;
    Ent *e;
    s32 r;
    if ((g->flags & 1) == 0) return -1;
    i = 0;
    if ((s32)g->numVoices > 0) {
        e = g->voices;
        do {
            if (SndSeVoice_IsHeld(e) != 0) {
                if (SndSeVoice_IsPlayingId(e, a, b) != 0) {
                    SndSeVoice_SetFlag(e, 3, 1);
                    SndSeVoice_SetParams(e, c, d);
                    return i;
                }
            }
            i++;
            e++;
        } while (i < g->numVoices);
    }
    i = SndSeGroup_FindFreeVoice(g);
    if (i == g->numVoices) return -1;
    SndSeVoice_StartHeld(&g->voices[i], a, b, c, d);
    return i;
}

extern "C" void SndSeGroup_Shutdown(Group *g) {
    SndSeGroup_StopAll(g, 0);
    SndSeGroup_ReleaseAll(g);
}

extern "C" void SndSeGroup_ReleaseAll(Group *g) {
    s32 i;
    Ent *e;
    if (g == NULL) Fatal_Trap();
    i = 0;
    if ((s32)g->numVoices <= 0) return;
    e = g->voices;
    do {
        NNS_SndHandleReleaseSeq(e);
        i++;
        e++;
    } while (i < g->numVoices);
}

extern "C" void SndSeGroup_StopVoice(Group *g, s32 i, s32 a) {
    Ent *e = &g->voices[i];
    if (i >= g->numVoices) Fatal_Trap();
    SndSeVoice_Stop(e, a);
}

extern "C" void SndSeGroup_StopAll(Group *g, s32 a) {
    s32 i = 0;
    if ((s32)g->numVoices <= 0) return;
    do {
        SndSeGroup_StopVoice(g, i, a);
        i++;
    } while (i < g->numVoices);
}

extern "C" void SndSeGroup_StopHeld(Group *g, s32 a) {
    s32 i = 0;
    Ent *e;
    if ((s32)g->numVoices <= 0) return;
    e = g->voices;
    do {
        if (SndSeVoice_IsHeld(e) != 0) SndSeGroup_StopVoice(g, i, a);
        i++;
        e++;
    } while (i < g->numVoices);
}

extern "C" BOOL SndSeSystem_LoadGroup(Player *o) {
    u32 id;
    if (o->groupParams.b0 != 255) {
        id = Snd_LoadGroup(o->groupParams.b0);
        if (id == (u32)-1) return FALSE;
    } else {
        id = 255;
    }
    o->heapLevel = id;
    return TRUE;
}

s32 (*gSndListenerPanCallback)(PlayCtx *);
s32 (*gSndListenerDistanceCallback)(PlayCtx *);
s32 (*gSndListenerVolumeCallback)(PlayCtx *);
