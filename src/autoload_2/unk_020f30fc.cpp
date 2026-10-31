#include "uptr.h"
#include "types.h"
#include "gfx/VecFx32.h"
#include "snd/SndSeEmitterKind99.h"
#include "snd/SndSeEmitterKind1.h"
#include "sys/FndList.h"
#include "snd/SndSeEmitter.h"
#include "snd/SndSeGroup.h"
#include "snd/SndMgr.h"
#include "snd/SndSceneBase.h"
#include "snd/SndPosNode.h"
#include "snd/SndSeqHandle.h"
#include "snd/SndSeqPlayer.h"

struct SeqInfo {
    u8 pad[4];
    u8 playerPrio;
};

struct Pan4500 {
    u8 pad[0x10];
    s32 w10;
};

extern "C" {
void NNS_SndPlayerSetVolume(void *p, s32 v);
void NNS_SndPlayerStopSeqBySeqNo(s32 a, s32 b, u32 c);
s32 SndSeGroup_PlayHeld(SndHandle *h, u32 a, u32 b, s32 c, s16 d);
s32 SndSeGroup_Play(SndHandle *h, u32 a, u32 b, s32 c, s16 d);
void SndSeGroup_Update(SndHandle *h, void *src);
void SndSeGroup_Finish(SndHandle *h);
void SndSeGroup_Init(SndHandle *h);
void SndSeGroup_SetEnabled(SndHandle *h, s32 x);
void Snd_SetListenerVolumeCallback(s32 (*f)(void *));
void Snd_SetListenerDistanceCallback(s32 (*f)(void *));
void Snd_SetListenerPanCallback(s32 (*f)(void *));
s32 Snd_ListenerDistanceCallback(void *p);
s32 Snd_ListenerVolumeCallback(void *p);
s32 Snd_ListenerPanCallback(void *p);
}

inline SndSeEmitterKind1::~SndSeEmitterKind1() {}


class SndSeEmitterKind2 : public SndSeEmitter {
public:
    SndSeEmitterKind2();
};

extern "C" {
void SndList_InitLink(void **p);
void *SndList_GetLast(void **p);
void *SndList_GetFirst(void **p);
void *SndList_GetPrev(void *list, void *obj);
void *SndList_GetNext(void *list, void *obj);
void SndList_Remove(void *list, void *obj);
void SndList_Append(void *list, void *obj);
void NNS_FndInitList(void *list, u16 offset);
void NNS_SndPlayerWriteVariable(void *p, u32 a, s32 b);
void NNS_SndPlayerSetTrackPan(void *p, u32 a, s32 b);
void NNS_SndHandleReleaseSeq(void *p);
SeqInfo *NNS_SndArcGetSeqArcSeqParam(u32 a, u32 b);
s32 Snd_CalcListenerDistance(VecFx32 *p, s32 m);
s32 Snd_DistanceToVolume(s32 x);
s32 Snd_CalcPan(VecFx32 *p, s32 m);
Pan4500 *Snd_GetVolumeCurve(void);
void Snd_CalcDepthVolumes(s32 z, s32 *a, s32 *b);
void NNS_SndPlayerSetPlayerPriority(void *p, s32 v);
void NNS_SndPlayerSetTrackVolume(void *p, u32 a, s32 b);
}

SndPosList *gSndPosList;

static inline BOOL notNull(void *p) {
    return p != NULL;
}


#include "snd/SndEnvChannel.h"
#include "snd/RainSndChannel.h"
#include "snd/CreatureSndChannel.h"
#include "snd/SkySndChannel.h"
#include "proto/autoload_2/unk_020ed8cc.h"
#include "proto/autoload_2/unk_020ef150.h"
#include "proto/autoload_2/unk_020f0dec.h"
#include "proto/autoload_2/unk_020f30fc.h"
#include "proto/main/unk_0206d49c.h"


extern "C" void Snd_InstallListenerCallbacks(void) {
    Snd_SetListenerDistanceCallback(Snd_ListenerDistanceCallback);
    Snd_SetListenerVolumeCallback(Snd_ListenerVolumeCallback);
    Snd_SetListenerPanCallback(Snd_ListenerPanCallback);
}

extern "C" void Snd_ClearListenerCallbacks(void) {
    Snd_SetListenerDistanceCallback(0);
    Snd_SetListenerVolumeCallback(0);
    Snd_SetListenerPanCallback(0);
}

SndSeEmitter::SndSeEmitter() {
    kind = 0;
}

SndSeEmitter::~SndSeEmitter() {
}

void SndSeEmitter::init() {
    SndSeGroup_Init(this);
    SndSeGroup_SetEnabled(this, 1);
    lastRandomSeId = 0;
}

void SndSeEmitter::update(void *src) {
    SndSeGroup_Update(this, src);
}

BOOL SndSeEmitter::playOneShot(s32 id, s32 c, s16 d) {
    s32 x;
    if (kind == 99 && gSndMgr.menuDuck != 0) {
        SndSeqHandle *p = &gSndMgr.auxSeHandle;
        Snd_StartSeqArcEx(p, 10, -1, -1, id / 1000, id % 1000);
        NNS_SndPlayerSetVolume(p, 100);
        return TRUE;
    }
    switch (id) {
    case 0x838:
    case 0x839:
    case 0x83a:
        stopEffects();
        break;
    }
    x = id;
    if (id == 123 || id == 127) {
        x += SndMgr_Rand(&gSndMgr, 4);
        if (x == lastRandomSeId) {
            if (x == id) {
                x++;
            } else if (x == id + 3) {
                x--;
            }
        }
        lastRandomSeId = x;
    }
    return SndSeGroup_Play(this, id / 1000, x % 1000, c, d);
}

BOOL SndSeEmitter::playHeld(s32 id, s32 c, s16 d) {
    if (gSndMgr.seDisabled == 1) return FALSE;
    if (id == 0x7f6) stopEffects();
    return SndSeGroup_PlayHeld(this, id / 1000, id % 1000, c, d);
}

void SndSeEmitter::stop() {
    SndSeGroup_Finish(this);
}

void SndSeEmitter::stopEffects() {
    s32 i;
    for (i = 82; i < 97; i++) {
        NNS_SndPlayerStopSeqBySeqNo(2, i, 0);
    }
    NNS_SndPlayerStopSeqBySeqNo(2, 54, 0);
}

SndSeEmitterKind1::SndSeEmitterKind1() {
    volCb = onVolume;
    kind = 1;
    alternateFlags = 0;
}

void SndSeEmitterKind1::onVolume(SndHandle *h, s32 idx) {
    if (gSndMgr.menuDuck == 0) return;
    void *slot = &reinterpret_cast<Group *>(h)->voices[idx].handle;
    SndSeEmitterKind1 *o = static_cast<SndSeEmitterKind1 *>(h);
    NNS_SndPlayerSetVolume(slot, o->volume * 40 / 100);
}

u16 SndSeEmitter::nextAlternateId(u16 s) {
    u32 r = SndMgr_Rand(&gSndMgr, 4);
    u8 f = alternateFlags;
    u32 b = f & 2;
    u32 c = f & 4;
    if (f & 1) {
        if (r == 0 && b == 0 && c == 0) {
            s = s + 2;
            alternateFlags = f | 2;
        } else {
            alternateFlags &= ~2;
        }
    } else {
        if (r == 0 && b == 0 && c == 0) {
            s = s + 3;
            alternateFlags = f | 4;
        } else {
            s = s + 1;
            alternateFlags &= ~4;
        }
    }
    alternateFlags ^= 1;
    return s;
}

void SndSeEmitter::playAlternate(u16 s) {
    playOneShot(nextAlternateId(s), 127, 0);
}

SndSeEmitterKind99::SndSeEmitterKind99() {
    kind = 99;
}

SndSeEmitterKind99::~SndSeEmitterKind99() {
}

SndSeEmitterKind2::SndSeEmitterKind2() {
    kind = 2;
}

void SndPosNode::init(SndPosList *list) {
    gSndPosList = list;
    id = 0;
    b1a = b1b = 0;
    SndList_InitLink((void **)this);
    Snd_InitHandle(&h);
}

void SndPosNode::play(s32 v, VecFx32 *p) {
    if (gSndMgr.seDisabled != 0) return;
    pos = *p;
    if (v > 1001 && v < 1072) {
        id = v;
        b1a = 1;
        b1b = 1;
        gSndPosList->add(this);
    } else {
        stop();
        gSndPosList->playAt((u16)v, &pos);
        updatePan();
    }
}

void SndPosNode::restart() {
    BOOL start;
    BOOL halt = FALSE;
    void *p = h.p;
    if (notNull(p)) {
        if ((s32)((SndSeqPlayer *)p)->seqArcIndex != (id % 1000)) {
            start = TRUE;
            halt = start;
        } else {
            start = FALSE;
            halt = start;
        }
    } else {
        start = TRUE;
    }
    if (halt) Snd_StopHandle(&h, 5);
    if (start) Snd_StartSeqArc(id % 1000, 1, &h);
    updatePan();
}

void SndPosNode::stop() {
    if (gSndMgr.seDisabled != 0) {
        Snd_StopHandle(&h, 15);
    } else {
        Snd_StopHandle(&h, 0);
    }
}

BOOL SndPosNode::isFinished() {
    BOOL r = FALSE;
    if (b1b == 0) {
        if (notNull(h.p)) {
            if (b1a != 0) r = FALSE; else r = TRUE;
        } else {
            r = TRUE;
        }
    }
    return r;
}

void SndPosNode::updatePan() {
    s32 a = Snd_DistanceToVolume(Snd_CalcListenerDistance(&pos, 0));
    s32 b = Snd_CalcPan(&pos, 0);
    NNS_SndPlayerSetVolume(&h, a);
    NNS_SndPlayerSetTrackPan(&h, 255, b);
}

void SndPosNode::playOnce(u32 v, VecFx32 *p) {
    if (gSndMgr.seDisabled != 0) return;
    id = v;
    pos = *p;
    b1a = 0;
    b1b = 1;
    if (v == 1263) {
        restart();
    } else {
        gSndPosList->add(this);
    }
}

void SndPosNode::setPitch(s32 v) {
    return NNS_SndPlayerWriteVariable(&h, 0, v);
}

void SndPosNode::setBgmPan(VecFx32 *p) {
    s32 a;
    SndSeqHandle *bh = &gSndMgr.bgmHandle;
    if (!notNull(bh->p)) return;
    a = Snd_DistanceToVolume(Snd_CalcListenerDistance(p, 0));
    s32 b = Snd_CalcPan(p, 0);
    if (a < 40) a = 40;
    NNS_SndPlayerSetVolume(bh, a);
    NNS_SndPlayerSetTrackPan(bh, gSndPanTrackMask, b);
}

void SndPosNode::release() {
    gSndPosList->remove(this);
    Snd_StopHandle(&h, 5);
    NNS_SndHandleReleaseSeq(&h);
}

SndPosList *SndPosList::release() {
    NNS_SndHandleReleaseSeq(&h);
    return this;
}

void SndPosList::init() {
    NNS_FndInitList(this, 0);
    Snd_InitHandle(&h);
}

void SndPosList::add(SndPosNode *node) {
    BOOL add = TRUE;
    for (void *p = SndList_GetFirst((void **)&list); p != NULL; p = SndList_GetNext(&list, p)) {
        if (p == node) {
            add = FALSE;
            break;
        }
    }
    if (add) SndList_Append(&list, node);
}

void SndPosList::update() {
    for (void *p = SndList_GetFirst((void **)&list); p != NULL; p = SndList_GetNext(&list, p)) {
        if (((SndPosNode *)p)->isFinished()) {
            ((SndPosNode *)p)->stop();
            SndList_Remove(&list, p);
        }
    }
    s32 n = list.num;
    if (n == 1) {
        ((SndPosNode *)SndList_GetLast((void **)&list))->restart();
    } else if (n == 2) {
        void *t = SndList_GetLast((void **)&list);
        ((SndPosNode *)t)->restart();
        ((SndPosNode *)SndList_GetPrev(&list, t))->restart();
    } else if (n > 2) {
        void *p = SndList_GetFirst((void **)&list);
        s32 i;
        n -= 2;
        for (i = 0; i < n; i++) {
            ((SndPosNode *)p)->stop();
            p = SndList_GetNext(&list, p);
        }
        void *t = SndList_GetLast((void **)&list);
        ((SndPosNode *)t)->restart();
        ((SndPosNode *)SndList_GetPrev(&list, t))->restart();
    }
    for (SndPosNode *p = (SndPosNode *)SndList_GetFirst((void **)&list); p != NULL; p = (SndPosNode *)SndList_GetNext(&list, p)) {
        p->b1b = 0;
    }
    if (gSndMgr.scene->id != 10) return;
    SndSeqHandle *bh = &gSndMgr.bgmHandle;
    if (!bh) return;
    u32 id = SndSeqHandle_Player(bh)->seqNo;
    if (id < 176 || id > 245) NNS_SndPlayerStopSeqBySeqNo(1, 0x107, 5);
}

void SndPosList::remove(SndPosNode *node) {
    for (void *p = SndList_GetFirst((void **)&list); p != NULL; p = SndList_GetNext(&list, p)) {
        if (p == (void *)node) SndList_Remove(&list, node);
    }
}

void SndPosList::playAt(s32 v, VecFx32 *p) {
    Snd_StartSeqArc((u16)(v % 1000), 1, &h);
    s32 a = Snd_DistanceToVolume(Snd_CalcListenerDistance(p, 0));
    s32 b = Snd_CalcPan(p, 0);
    NNS_SndPlayerSetVolume(&h, a);
    NNS_SndPlayerSetTrackPan(&h, 255, b);
}

void SndEnvChannel::vfunc_00() {
    Snd_InitHandle(&h);
    v = 0;
    flags = 0;
}

void SndEnvChannel::vfunc_04() {
    Snd_StopHandle(&h, 5);
    NNS_SndHandleReleaseSeq(&h);
}

void SndEnvChannel::requestSustained(u32 nv) {
    if (v != nv) {
        flags |= 4;
    } else {
        flags &= ~4;
    }
    v = nv;
    flags |= 2;
    flags |= 1;
}

void SndEnvChannel::request(u32 nv) {
    if (v != nv) {
        flags |= 4;
    } else {
        flags &= ~4;
    }
    v = nv;
    flags &= ~2;
    flags |= 1;
}

extern "C" s32 Snd_CalcSeVolume(s32 a, s32 b) {
    SeqInfo *inf = NNS_SndArcGetSeqArcSeqParam(a / 1000, a % 1000);
    if (inf == NULL) Fatal_Trap();
    s32 v = b + (inf->playerPrio - 100);
    if (v > 0) {
        if (v >= 127) v = 127;
    } else {
        v = 0;
    }
    return v;
}

void SndEnvChannel::update(VecFx32 *pos) {
    s32 t;
    s32 w;
    s32 a, b;
    if (gSndMgr.seDisabled == 1) return;
    if (flags & 4) {
        if (notNull(h.p)) Snd_StopHandle(&h, 0);
        flags &= ~4;
    }
    if (flags & 1) {
        switch (v) {
        case 2061:
            t = Snd_CalcListenerDistance(pos, 1);
            break;
        case 2039:
        case 2040:
        case 2043:
        case 2044:
        case 2046:
        case 2047:
            t = Snd_CalcListenerDistance(pos, 2);
            break;
        case 1230:
        case 2041:
        case 2042:
        case 2045:
        case 2048:
        case 2049:
        case 2050:
        case 2051:
        case 2052:
        case 2053:
        case 2058:
            t = 0;
            break;
        case 2054:
        case 2055:
        case 2056:
        case 2057:
        case 2059:
        case 2060:
        default:
            t = Snd_CalcListenerDistance(pos, 0);
            break;
        }
        if (t > (Snd_GetVolumeCurve()->w10 >> 12)) {
            if (notNull(h.p)) Snd_StopHandle(&h, 0);
            flags &= ~1;
            return;
        }
        t = Snd_DistanceToVolume(t);
        if (t == 0) {
            if (notNull(h.p)) Snd_StopHandle(&h, 0);
            flags &= ~1;
            return;
        }
        if (!notNull(h.p) || (u16)(v + 0xf7fd) <= 1) {
            if (v == 2103) {
                Snd_StartSeqArc(v % 1000, v / 1000, &h);
            } else {
                w = Snd_CalcSeVolume(v, t);
                Snd_StartSeqArcEx(&h, -1, -1, w, v / 1000, v % 1000);
            }
        }
        if (notNull(h.p)) {
            if (v != 2103) NNS_SndPlayerSetPlayerPriority(&h, Snd_CalcSeVolume(v, t));
            switch (v) {
            case 2059:
                w = Snd_CalcPan(pos, 1);
                break;
            case 2053:
            case 2061:
                w = 0;
                break;
            case 2039:
            case 2040:
            case 2041:
            case 2042:
            case 2043:
            case 2044:
            case 2045:
            case 2046:
            case 2047:
            case 2048:
            case 2049:
            case 2050:
            case 2051:
            case 2052:
                w = Snd_CalcPan(pos, 2);
                break;
            case 2054:
            case 2055:
            case 2056:
            case 2057:
            case 2058:
            case 2060:
            default:
                w = Snd_CalcPan(pos, 0);
                break;
            }
            if (v == 1230 || v == 2058) {
                Snd_CalcDepthVolumes(pos->z, &a, &b);
                NNS_SndPlayerSetTrackVolume(&h, 3, a);
                NNS_SndPlayerSetTrackVolume(&h, 12, b);
            } else {
                NNS_SndPlayerSetVolume(&h, t);
                NNS_SndPlayerSetTrackPan(&h, gSndPanTrackMask, w);
            }
        }
        flags &= ~1;
    } else if (!(flags & 2)) {
        if (notNull(h.p)) Snd_StopHandle(&h, 0);
    }
    flags &= ~1;
}

void RainSndChannel::vfunc_00() {
    SndEnvChannel::vfunc_00();
}

void CreatureSndChannel::vfunc_00() {
    SndEnvChannel::vfunc_00();
}

void SkySndChannel::vfunc_00() {
    SndEnvChannel::vfunc_00();
}

void SkySndChannel::requestSustained(u32 nv) {
    SndEnvChannel::requestSustained(nv);
}

void SkySndChannel::request(u32 nv) {
    SndEnvChannel::request(nv);
}

void SkySndChannel::update(VecFx32 *pos) {
    SndEnvChannel::update(pos);
}
