#include "types.h"
#include "gfx/VecFx32.h"
#include "npc/NpcAnimCtrl.h"
#include "npc/NpcSpeechState.h"
#include "npc/NpcResHandle.h"
#include "npc/NpcObstacleProbe.h"
#include "npc/Unk_0201ad18.h"
#include "npc/NpcFootstepFx.h"
#include "sys/ProcBase.h"
#include "npc/NpcTalkCtrl.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "snd/SndSeEmitterKind1.h"
#include "actor/NpcActor.h"
#include "actor/SpNpcActor.h"
#include "actor/ActorFollowCollider.h"
#include "gfx/CachedModel.h"
#include "gfx/ThreeLayerAnimModel.h"
#include "net/CommManager.h"
#include "npc/NpcActionCtrl.h"
#include "npc/NpcFaceAnim.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0202e2d4.h"
#include "proto/main/unk_020815f8.h"
#include "proto/main/unk_020a427c.h"

inline SndSeEmitterKind1::~SndSeEmitterKind1() {}
inline NpcActor::~NpcActor() {}


extern "C" {
extern u32 data_020d6f54[];
extern CommManager *gCommManager;
extern u32 gVec3Zero;
extern const s32 data_020c6cf0;
extern u8 gFieldSceneKind;
}

s32 sSpNpcWalkAnimSpeedScale = data_020c6cf0 - 0x8000;

extern "C" {
s32 PM_GetBattery(s32 *out);
s32 SpNpc_GetInfoByte0(u16 *p);
BOOL Npc_GetName(MsgString *buf, u16 *p);
}







extern "C" {
BOOL Vec_NotEqual(void *a, void *b);
void *SpNpcAnimHeapRef_GetHeap(void *p);
}

static inline BOOL Unk_0202e318_IsOne(u8 v) {
    if (v == 1) {
        return TRUE;
    }
    return FALSE;
}


SpNpcActor::~SpNpcActor() {}

BOOL SpNpcActor::loadAnimSet() {
    void *p = animHeapHandle.getSpNpcAnimHeapRef();
    if (!((CachedModel *)(&model))->allocJointRecord(SpNpcAnimHeapRef_GetHeap(p))) {
        return FALSE;
    }
    if (((ThreeLayerAnimModel *)(&model))->allocLayer3Anims(SpNpcAnimHeapRef_GetHeap(p))) {
        return TRUE;
    }
    return FALSE;
}

void SpNpcActor::setColliderSize(s32 a, s32 b) {
    colliderRadius = a;
    colliderHeight = b;
}

BOOL SpNpcActor::preCreate() {
    if (!NpcActor::preCreate()) {
        return FALSE;
    }
    setColliderSize(0x1000, 0x2000);
    talkMelodyPlayed = 0;
    return TRUE;
}

BOOL SpNpcActor::onCreate() {
    if (!NpcActor::onCreate()) {
        return FALSE;
    }
    if (!NetArea_IsLocalOwner() && gCommManager->isOnline() && !netSyncOff) {
        VecFx32 v;
        s16 s;
        v.x = 0;
        v.y = 0;
        v.z = 0;
        s = 0;
        if (((NpcActor *)(this))->netReadPosition(&v, &s) && Vec_NotEqual(&v, &gVec3Zero)) {
            VecFx32 *p = (VecFx32 *)&position;
            p->x = v.x;
            p->y = v.y;
            p->z = v.z;
            rotY = s;
            moveAngleY = s;
        }
    }
    if (!animHeapHandle.getSpNpcAnimHeapRef()) {
        if (!animHeapHandle.acquire()) {
            return FALSE;
        }
        if (!loadAnimSet()) {
            return FALSE;
        }
    }
    if (!((NpcFaceAnim *)(&faceAnim))->load((NpcActor *)(this))) {
        return FALSE;
    }
    if (!((NpcAnimCtrl *)(&animCtrl))->initForActor((NpcActor *)(this), getWalkAnimSpeedScale())) {
        return FALSE;
    }
    ((NpcActionCtrl *)(&actionCtrl))->startAction(this, 0, 1, 0, 0, 0, 0, 0);
    ((ActorFollowCollider *)(&collider))->setupForActor(this, colliderRadius, colliderHeight, 8, 0x2fc, 3, (u8)getNpcIndex(), 0x1000);
    if (!NpcRegistry_AddSpNpc(this, &npcHandle)) {
        return FALSE;
    }
    ((NpcFootstepFx *)(&footstepFx))->enableFootsteps();
    return TRUE;
}

BOOL SpNpcActor::preDelete() {
    if (!NpcActor::preDelete()) {
        return FALSE;
    }
    NpcRegistry_RemoveSpNpc(&npcHandle);
    return TRUE;
}

BOOL SpNpcActor::onDelete() {
    if (!NpcActor::onDelete()) {
        return FALSE;
    }
    animHeapHandle.release();
    return TRUE;
}

void SpNpcActor::getName(MsgString *buf) { Npc_GetName(buf, &npcHandle); }

u32 SpNpcActor::getGender() { return SpNpc_GetInfoByte0(&npcHandle); }

BOOL SpNpcActor::canPlayTalkMelody() {
    if (!Unk_0202e318_IsOne(gFieldSceneKind) || talkMelodyPlayed == 0) {
        return TRUE;
    }
    return FALSE;
}

void SpNpcActor::onTalkMelodyPlayed() { talkMelodyPlayed = 1; }

u16 SpNpcActor::getSpecies() {
    u16 v = npcHandle;
    if (((v & 0xf000) >> 12) == 0xd) {
        return (v & 0xfff) + 0xc8;
    }
    return 0xffff;
}

BOOL SpNpcActor::getWalkAnimSpeedScale() { return sSpNpcWalkAnimSpeedScale; }

