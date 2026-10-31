#include "types.h"
#include "net/CommManager.h"
#include "gfx/VecFx32.h"
#include "gfx/Mtx43.h"
#include "player/PlayerActor.h"
#include "player/Unk_02007694.h"
#include "proto/main/unk_020b4828.h"
#include "proto/main/unk_02000c2c.h"
#include "proto/main/unk_02004558.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_02094810.h"

typedef VecFx32Ctor Unk_02006d14_V3;

enum Unk_02094a08_Limit { Unk_02094a08_LIMIT_5 = 5 };
enum Unk_02094d60_Limit { Unk_02094d60_LIMIT_5 = 5, Unk_02094d60_LIMIT_6 = 6 };

struct Unk_02095338_D { u16 a : 7; u16 b : 4; u16 c : 5; };

class PlayerSessionTable {
public:
    PlayerActor *actors[4];
    u8 dataIndices[4];
    u8 gfxSlots[4];
    Unk_02095338_D lastPlayDate;
    u16 tanTimer;
    u8 sessionFlags;
    u8 pad_1d[3];
    s32 lastActions[4];
    u8 lastScenes[4];
    VecFx32 lastPositions[4];
    s16 lastAngles[4];
    PlayerSessionTable();
    ~PlayerSessionTable();
};

struct PlayerNetStateLocals { u32 out; u8 t[12]; };

extern "C" {
extern u8 gFieldSceneKind;
extern const u8 sEmotionHoldFrames[];
extern const u32 sPlayerPosSyncVars[];
extern const u32 sPlayerAngleSyncVars[];
extern const u32 sPlayerStateSyncVars[];
extern const s32 data_020d0428;
extern CommManager *gCommManager;
}

extern "C" {

s32 PlayerActor_RequestExitWalkOut(PlayerActor *o, VecFx32Ctor *v, u32 a, s32 b);

s32 Scene_InHouseRoom();
BOOL TalkRequestFlags_IsResetti();
s32 TalkRequest_IsSaveMenuRunning();
void PlayerActor_GetHeldItem(void *out, PlayerActor *o);
s32 Item_IsFurniture(void *p);
s32 Item_GetFurnitureIndex(void *p);
s32 PlayerActor_RequestStowItem(PlayerActor *o, u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, s32 g);
s32 PlayerActor_RequestFishReelIn(PlayerActor *o, u32 a, u32 b, s32 c);
void PlayerActor_EndStandUpFront(PlayerActor *o, s32 a);
void PlayerActor_EndStandUpSide1(PlayerActor *o, s32 a);
void PlayerActor_EndStandUpSide2(PlayerActor *o, s32 a);
void PlayerActor_EndGetOutOfBed(PlayerActor *o, s32 a);
void PlayerActor_EndGetIntoBed(PlayerActor *o, s32 a);
void PlayerActor_EndBedRoll(PlayerActor *o, s32 a);
void __cxa_vec_ctor(void *p, s32 n, s32 size, void *ctor, void *dtor);
void __cxa_vec_cleanup(void *p, s32 n, s32 size, void *dtor);
s32 Scene_GetCurrent();
void MI_CpuCopy8(const void *src, void *dst, s32 n);

}

extern "C" PlayerActor *PlayerActor_Get(s32 idx) {
    if (idx == 4) {
        idx = gCommManager->localSlot;
    }
    return PlayerSessionTable_GetActor(&gPlayerSessionTable, idx);
}

extern "C" u8 *PlayerActor_GetNetPosVar(s32 idx) { return gCommManager->getSyncVar(sPlayerPosSyncVars[idx]); }

extern "C" u8 *PlayerActor_GetNetAngleVar(s32 idx) { return gCommManager->getSyncVar(sPlayerAngleSyncVars[idx]); }

extern "C" u8 *PlayerActor_GetNetStateVar(s32 idx) { return gCommManager->getSyncVar(sPlayerStateSyncVars[idx]); }

extern "C" BOOL PlayerActor_GetSlotPosXZ(u8 *outb, s32 *x, s32 *y, s32 mode, s32 idx) {
    if (idx == 4) {
        idx = gCommManager->localSlot;
    }
    if ((gCommManager)->isLocalSlot(idx)) {
        PlayerActor *e = PlayerActor_Get(4);
        if (e != NULL) {
            s32 *p = (s32 *)&e->position;
            *outb = Scene_GetCurrent();
            *x = p[0];
            *y = p[2];
            return TRUE;
        }
        return FALSE;
    }
    u8 *t = PlayerActor_GetNetStateVar(idx);
    if (t == NULL) return FALSE;
    s32 v;
    if (!PlayerActor_GetSlotAction((u32 *)&v, mode, idx)) return FALSE;
    if (v >= 0x93) return FALSE;
    u8 *t2 = PlayerActor_GetNetPosVar(idx);
    if (t2 == NULL) return FALSE;
    u32 a, b;
    NetBuf_UnpackPair20(t2, &a, &b);
    *x = a;
    *y = b;
    CommRecord_UnpackSource(t, outb, 0);
    return TRUE;
}

extern "C" BOOL PlayerActor_GetSlotAngle(s16 *out, s32 a, s32 idx)
{
    u32 st;
    if (idx == 4) {
        idx = gCommManager->localSlot;
    }
    if ((gCommManager)->isLocalSlot(idx)) {
        PlayerActor *o = PlayerActor_Get(4);
        if (o) {
            *out = o->rotY;
            return TRUE;
        }
        return FALSE;
    }
    if (!PlayerActor_GetNetStateVar(idx)) {
        return FALSE;
    }
    if (!PlayerActor_GetSlotAction(&st, a, idx)) {
        return FALSE;
    }
    if ((s32)st >= 0x93) {
        return FALSE;
    }
    u8 *q = PlayerActor_GetNetAngleVar(idx);
    if (!q) {
        return FALSE;
    }
    *out = NetBuf_ReadS16B(q);
    return TRUE;
}

extern "C" BOOL PlayerActor_GetSlotAction(u32 *out, s32 a, s32 idx)
{
    u8 buf;
    if (idx == 4) {
        idx = gCommManager->localSlot;
    }
    if ((gCommManager)->isLocalSlot(idx)) {
        PlayerActor *o = PlayerActor_Get(4);
        if (o) {
            *out = o->action;
            return TRUE;
        }
        return FALSE;
    }
    u8 *p = PlayerActor_GetNetStateVar(idx);
    if (!p) {
        return FALSE;
    }
    MI_CpuCopy8(p + 1, &buf, 1);
    if (buf == 0) {
        return FALSE;
    }
    *out = buf - 1;
    return TRUE;
}

extern "C" void PlayerActor_PackNetState(void *dst, s32 x)
{
    PlayerNetStateLocals l;
    PlayerActor *o = PlayerActor_Get(4);
    if (o) {
        CommRecord_PackSource(l.t, Scene_GetCurrent(), 0);
        if (PlayerActor_GetSlotAction(&l.out, -1, 4)) {
            l.t[1] = l.out + 1;
        }
        NetBuf_WriteS16(l.t + 2, o->netSeq);
        MI_CpuCopy8(&o->netData, l.t + 4, 8);
    } else {
        l.t[1] = 0x94;
    }
    MI_CpuCopy8(l.t, dst, CommSyncVar_GetVarSize(x));
}

extern "C" void PlayerActor_PackClothesChange(u8 *p, u16 h, u8 v)
{
    NetBuf_WriteU16(p, h);
    p[2] = v;
}

extern "C" void PlayerActor_UnpackClothesChange(u8 *p, u16 *a, u32 *b)
{
    *a = NetBuf_ReadU16(p);
    *b = p[2];
}

extern "C" void PlayerActor_PackHair(u8 *p, u32 a, u32 b)
{
    *p = ((b << 4) & 0x70) | (a & 0xf);
}

extern "C" void PlayerActor_UnpackHair(u8 *src, u8 *a, u8 *b)
{
    *a = src[0] & 0xf;
    *b = (src[0] >> 4) & 7;
}

extern "C" void PlayerSessionTable_SetActor(PlayerSessionTable *p, s32 i, PlayerActor *v)
{
    p->actors[i] = v;
}

extern "C" void PlayerSessionTable_ClearActor(PlayerSessionTable *p, s32 i)
{
    PlayerSessionTable_SetActor(p, i, NULL);
}

extern "C" PlayerActor *PlayerSessionTable_GetActor(PlayerSessionTable *p, s32 i)
{
    if (i < 4) {
        return p->actors[i];
    }
    return NULL;
}

extern "C" void PlayerSessionTable_SetDataIndex(PlayerSessionTable *p, s32 i, s32 v)
{
    p->dataIndices[i] = v;
}

extern "C" void PlayerSessionTable_ClearDataIndex(PlayerSessionTable *p, s32 i)
{
    PlayerSessionTable_SetDataIndex(p, i, 7);
}

extern "C" u8 PlayerSessionTable_GetDataIndex(PlayerSessionTable *p, s32 i)
{
    if (i < 4) {
        return p->dataIndices[i];
    }
    return 7;
}

extern "C" void PlayerSessionTable_SetGfxSlot(PlayerSessionTable *p, s32 i, s32 v)
{
    p->gfxSlots[i] = v;
}

extern "C" void PlayerSessionTable_ClearGfxSlot(PlayerSessionTable *p, s32 i)
{
    PlayerSessionTable_SetGfxSlot(p, i, 4);
}

extern "C" u8 PlayerSessionTable_GetGfxSlot(PlayerSessionTable *p, s32 i)
{
    if (i < 4) {
        return p->gfxSlots[i];
    }
    return 4;
}

extern "C" u32 PlayerSessionTable_FindFreeGfxSlot(PlayerSessionTable *p)
{
    u32 i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == PlayerSessionTable_GetGfxSlot(p, j)) {
                break;
            }
        }
        if (j >= 4) {
            return i;
        }
    }
    return 4;
}

PlayerSessionTable::PlayerSessionTable()
{
    u32 i;
    __cxa_vec_ctor(lastPositions, 4, 12, (void *)FxVec3_Construct, (void *)FxVec3_Destruct);
    for (i = 0; i < 4; i++) {
        PlayerSessionTable_ClearDataIndex(&gPlayerSessionTable, i);
        PlayerSessionTable_ClearGfxSlot(&gPlayerSessionTable, i);
        lastActions[i] = 0x93;
        lastScenes[i] = 0x33;
        lastPositions[i].x = 0;
        lastPositions[i].y = 0;
        lastPositions[i].z = 0;
        lastAngles[i] = 0;
    }
    lastPlayDate.a = 0;
    lastPlayDate.b = 1;
    lastPlayDate.c = 1;
    tanTimer = 0;
    sessionFlags = 0;
}

PlayerSessionTable::~PlayerSessionTable()
{
    __cxa_vec_cleanup(lastPositions, 4, 12, (void *)FxVec3_Destruct);
}

extern "C" void PlayerSession_SetActor(s32 i, PlayerActor *v)
{
    PlayerSessionTable_SetActor(&gPlayerSessionTable, i, v);
}

extern "C" void PlayerSession_ClearActor(s32 i)
{
    PlayerSessionTable_ClearActor(&gPlayerSessionTable, i);
}

extern "C" void PlayerSession_SetDataIndex(s32 i, s32 v)
{
    PlayerSessionTable_SetDataIndex(&gPlayerSessionTable, i, v);
}

extern "C" void PlayerSession_ClearDataIndex(s32 i)
{
    PlayerSessionTable_ClearDataIndex(&gPlayerSessionTable, i);
}

extern "C" u8 PlayerSession_GetDataIndex(s32 i)
{
    return PlayerSessionTable_GetDataIndex(&gPlayerSessionTable, i);
}

extern "C" Unk_02095338_D *PlayerSession_GetLastPlayDate()
{
    return &gPlayerSessionTable.lastPlayDate;
}

extern "C" u16 *PlayerSession_GetTanTimer()
{
    return &gPlayerSessionTable.tanTimer;
}

extern "C" u8 *PlayerSession_GetSessionFlags()
{
    return &gPlayerSessionTable.sessionFlags;
}

extern "C" s32 *PlayerSession_GetLastAction(s32 i)
{
    return &gPlayerSessionTable.lastActions[i];
}

extern "C" u8 *PlayerSession_GetLastScene(s32 i)
{
    return &gPlayerSessionTable.lastScenes[i];
}

extern "C" VecFx32 *PlayerSession_GetLastPos(s32 i)
{
    return &gPlayerSessionTable.lastPositions[i];
}

extern "C" s16 *PlayerSession_GetLastAngle(s32 i)
{
    return &gPlayerSessionTable.lastAngles[i];
}

extern "C" void PlayerSession_ResetLastState(s32 i)
{
    *PlayerSession_GetLastAction(i) = 0x93;
    *PlayerSession_GetLastScene(i) = 0x33;
    VecFx32 *e = PlayerSession_GetLastPos(i);
    e->x = 0;
    e->y = 0;
    e->z = 0;
    *PlayerSession_GetLastAngle(i) = 0;
}

extern "C" void PlayerSession_SetGfxSlot(s32 i, s32 v)
{
    PlayerSessionTable_SetGfxSlot(&gPlayerSessionTable, i, v);
}

extern "C" void PlayerSession_ClearGfxSlot(s32 i)
{
    PlayerSessionTable_ClearGfxSlot(&gPlayerSessionTable, i);
}

extern "C" u8 PlayerSession_GetGfxSlot(s32 i)
{
    return PlayerSessionTable_GetGfxSlot(&gPlayerSessionTable, i);
}

extern "C" u32 PlayerSession_FindFreeGfxSlot()
{
    return PlayerSessionTable_FindFreeGfxSlot(&gPlayerSessionTable);
}

extern "C" void PlayerActor_GetActorNop() {}

extern "C" void *PlayerActor_GetActor(s32 id)
{
    void *r = (void *)PlayerActor_Get(id);
    PlayerActor_GetActorNop();
    return r;
}

extern "C" void PlayerActor_GetCharacterNop() {}

extern "C" void *PlayerActor_GetCharacter(s32 id)
{
    void *r = (void *)PlayerActor_Get(id);
    PlayerActor_GetCharacterNop();
    return r;
}

extern "C" u32 PlayerActor_ParamGetSlot(u32 v)
{
    return (v >> 30) & 3;
}

extern "C" u32 PlayerActor_ParamGetAction(u32 v)
{
    return (v >> 22) & 0xff;
}

extern "C" BOOL PlayerActor_IsStowFinished()
{
    return PlayerActor_TestSlotFlag(1, 4);
}

extern "C" BOOL PlayerActor_IsEnteringDoor()
{
    return PlayerActor_TestSlotFlag(4, 4);
}

extern "C" BOOL PlayerActor_IsScriptedWalking(s32 a)
{
    return PlayerActor_TestSlotFlag(5, a);
}

extern "C" BOOL PlayerActor_IsInAct05()
{
    return PlayerActor_IsInAction(5, 4);
}

extern "C" BOOL PlayerActor_IsInWaitMenu()
{
    return PlayerActor_IsInAction(0x90, 4);
}

extern "C" BOOL PlayerActor_TestSlotFlag(s32 a, s32 b)
{
    PlayerActor *o = PlayerActor_Get(b);
    if (o) {
        return (o)->testActionFlag(a);
    }
    return FALSE;
}

extern "C" BOOL PlayerActor_IsInAction(s32 v, s32 id)
{
    PlayerActor *o = PlayerActor_Get(id);
    if (o) {
        if (o->action == v) {
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

extern "C" s32 PlayerActor_GetAction(s32 id)
{
    PlayerActor *o = PlayerActor_Get(id);
    if (o) {
        return o->action;
    }
    return 0x93;
}

extern "C" s32 PlayerActor_GetResumeTransform(Unk_02006d14_V3 *out, s16 *outAng)
{
    PlayerActor *o = PlayerActor_Get(4);
    if (o) {
        Unk_02006d14_V3 saved;
        Unk_02006d14_V3 tmp;
        s16 ang;
        s32 st;
        {
            Unk_02006d14_V3 *pv = (Unk_02006d14_V3 *)&o->position;
            saved = *pv;
        }
        ang = o->rotY;
        st = o->action;
        switch (st) {
        case 16:
            st = 2;
            break;
        case 0x2c:
            st = 2;
            PlayerActor_EndStandUpFront(o, st);
            break;
        case 0x29:
        case 0x2a:
            if (st == 0x29) {
                PlayerActor_EndStandUpSide1(o, 0x2c);
            } else {
                PlayerActor_EndStandUpSide2(o, 0x2c);
            }
            st = 2;
            PlayerActor_OffsetByAngle(&tmp, o, &saved, &o->rotY, (s32 *)&data_020d0428);
            {
                Unk_02006d14_V3 *pv = (Unk_02006d14_V3 *)&o->position;
                *pv = tmp;
            }
            break;
        case 14:
            st = 2;
            break;
        case 9: case 11: case 12:
            st = 8;
            break;
        case 10:
            st = 2;
            PlayerActor_EndGetOutOfBed(o, st);
            break;
        case 15:
            st = 8;
            PlayerActor_EndGetIntoBed(o, st);
            break;
        case 13:
            st = 8;
            PlayerActor_EndBedRoll(o, st);
            break;
        }
        {
            Unk_02006d14_V3 *pv = (Unk_02006d14_V3 *)&o->position;
            *out = *pv;
            *outAng = o->rotY;
            *pv = saved;
        }
        o->rotY = ang;
        return st;
    }
    return 0x93;
}

extern "C" s32 PlayerActor_GetActionOrSpawnAction()
{
    PlayerActor *o = PlayerActor_Get(4);
    if (o) {
        s32 v = o->action;
        if (v == 0) {
            v = (o->param >> 22) & 0xff;
        }
        return v;
    }
    return 0x93;
}

extern "C" BOOL PlayerActor_IsChangingClothes()
{
    PlayerActor *o = PlayerActor_Get(4);
    if (o && o->action == 7 && o->bodyModel.curFrame < 0x13000) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL PlayerActor_IsChangingHeldItem()
{
    return PlayerActor_IsInAction(0x3f, 4);
}

extern "C" s32 PlayerActor_CanAcceptTalk()
{
    PlayerActor *o = PlayerActor_Get(4);
    if (o) {
        return (o)->canAcceptTalk(o->action);
    }
    return 0;
}

extern "C" BOOL PlayerActor_SetEventLock(s32 c)
{
    if (c) {
        return PlayerActor_SetSlotFlag(0xb, 4);
    }
    return PlayerActor_ClearSlotFlag(0xb, 4);
}

extern "C" BOOL PlayerActor_SetNoFaceTalkTarget(s32 c, s32 b)
{
    if (c) {
        return PlayerActor_SetSlotFlag(0xe, b);
    }
    return PlayerActor_ClearSlotFlag(0xe, b);
}

extern "C" BOOL PlayerActor_SetNetFollowPaused(s32 c, s32 b)
{
    if (c) {
        return PlayerActor_SetSlotFlag(0x10, b);
    }
    return PlayerActor_ClearSlotFlag(0x10, b);
}

extern "C" BOOL PlayerActor_KeepAnimForNextAction()
{
    return PlayerActor_SetSlotFlag(0x17, 4);
}

extern "C" BOOL PlayerActor_SetSlotFlag(s32 a, s32 b)
{
    PlayerActor *o = PlayerActor_Get(b);
    if (o) {
        (o)->setActionFlag(a);
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL PlayerActor_ClearSlotFlag(s32 a, s32 b)
{
    PlayerActor *o = PlayerActor_Get(b);
    if (o) {
        (o)->clearActionFlag(a);
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL PlayerActor_CanOpenMenu()
{
    PlayerActor *o = PlayerActor_Get(4);
    if (o) {
        if ((o)->testActionFlag(0xb)) {
            return FALSE;
        }
        if (TalkRequestFlags_IsResetti() || (o)->testActionFlag(0x13)) {
            return FALSE;
        }
        if (o->action == 0x3d || (o)->testActionFlag(7) || (o)->testActionFlag(8)) {
            return FALSE;
        }
        Unk_02094d60_Limit n = Unk_02094d60_LIMIT_5;
        if (n > (o)->getEffectivePriority()) {
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

extern "C" BOOL PlayerActor_IsInterruptibleByMenu()
{
    PlayerActor *o = PlayerActor_Get(4);
    if (o) {
        Unk_02094d60_Limit n = Unk_02094d60_LIMIT_6;
        if (n > (o)->getEffectivePriority()) {
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

extern "C" BOOL PlayerActor_CanStartTalk()
{
    PlayerActor *o = PlayerActor_Get(4);
    if (o) {
        if ((o)->testActionFlag(0xb)) {
            if (o->action == 0x28 || o->action == 0x7c) {
                return TRUE;
            }
        }
        if ((o)->testActionFlag(0x13)) {
            return FALSE;
        }
        Unk_02094d60_Limit n = Unk_02094d60_LIMIT_5;
        if (n > (o)->getEffectivePriority()) {
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

extern "C" BOOL PlayerActor_IsEventIdle()
{
    PlayerActor *o = PlayerActor_Get(4);
    if (o) {
        s32 st = o->action;
        if (TalkRequestFlags_IsResetti() || (o)->testActionFlag(0x13)) {
            return FALSE;
        }
        if ((o)->testActionFlag(0xb)) {
            if (st == 0x28 || st == 2 || st == 8) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

extern "C" BOOL PlayerActor_IsInterruptible()
{
    PlayerActor *o = PlayerActor_Get(4);
    if (o) {
        Unk_02094d60_Limit n = Unk_02094d60_LIMIT_5;
        if (n > (o)->getEffectivePriority()) {
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

extern "C" s32 PlayerActor_RequestAct05()
{
    PlayerActor *o = PlayerActor_Get(4);
    if (o) {
        return ((Unk_02007694 *)(void *)(o))->requestAct05(3, 5, -1);
    }
    return 0;
}

extern "C" s32 PlayerActor_RequestReturnToWait() {
    PlayerActor *o = PlayerActor_Get(4);
    if (o) {
        s32 r4 = o->action;
        s32 r6 = o->pendingAct76Kind;
        o->pendingAct76Kind = 0;
        if (r4 == 0x2c || (u32)(r4 - 0x29) <= 1) return 1;
        o->actionPriority = ((Unk_02007694 *)(void *)(o))->getActionDonePriority(r4);
        if (r6 > 0) {
            return (o)->requestAct76((u8)(r6 + 3), 0, 0, 6, -1);
        }
        u16 buf[2];
        BOOL c = gFieldSceneKind == 0 ? TRUE : FALSE;
        if (c) {
            PlayerActor_GetHeldItem(buf, o);
            BOOL c2;
            if (Item_IsFurniture(buf)) {
                buf[1] = 0xfff1;
                c2 = Item_GetFurnitureIndex(buf) == Item_GetFurnitureIndex(&buf[1]) ? TRUE : FALSE;
            } else {
                c2 = buf[0] == 0xfff1 ? TRUE : FALSE;
            }
            if (!c2 && !(o)->getHeldHoldableIndex() && r4 != 0x39) {
                return PlayerActor_RequestStowItem(o, 2, 2, 0, 0, 0, 6, -1);
            }
        }
        return (o)->requestWait(3, 5, -1);
    }
    return 0;
}

extern "C" s32 PlayerActor_RequestChangeClothes(u16 *p, s32 a, s32 b) {
    PlayerActor *o = PlayerActor_Get(4);
    if (o) return ((Unk_02007694 *)(void *)(o))->requestChangeClothes(*p, a, b, 6, -1);
    return 0;
}

extern "C" s32 PlayerActor_RequestWearShirt(u16 *p) { return PlayerActor_RequestChangeClothes(p, 0, 5); }

extern "C" s32 PlayerActor_RequestWearFaceItem(u16 *p) { return PlayerActor_RequestChangeClothes(p, 1, 5); }

extern "C" s32 PlayerActor_RequestWearHat(u16 *p) { return PlayerActor_RequestChangeClothes(p, 2, 5); }

extern "C" s32 PlayerActor_RequestFaceChange() {
    u16 v = 0xfff1;
    return PlayerActor_RequestChangeClothes(&v, 3, 5);
}

extern "C" s32 PlayerActor_RequestWearShirtAlt(u16 *p) { return PlayerActor_RequestChangeClothes(p, 0, 0x10); }

extern "C" s32 PlayerActor_RequestWearFaceItemAlt(u16 *p) { return PlayerActor_RequestChangeClothes(p, 1, 0x10); }

extern "C" s32 PlayerActor_RequestWearHatAlt(u16 *p) { return PlayerActor_RequestChangeClothes(p, 2, 0x10); }

extern "C" s32 PlayerActor_RequestChangeHeldItem(u16 *p) {
    PlayerActor *o = PlayerActor_Get(4);
    if (o) return (o)->requestChangeHeldItem(*p, 6, -1);
    return 0;
}

extern "C" s32 PlayerActor_RequestHoldUpItem(u16 *p) {
    PlayerActor *o = PlayerActor_Get(4);
    if (o) {
        u16 h = *p;
        return (o)->requestHoldUpItem(&h, 6, -1);
    }
    return 0;
}

extern "C" s32 PlayerActor_RequestWalkTo(VecFx32Ctor *v, u32 b, u32 idx) {
    PlayerActor *o = PlayerActor_Get(idx);
    if (o) {
        VecFx32Ctor t;
        t.x = v->x;
        t.y = v->y;
        t.z = v->z;
        return (o)->requestWalkTo(&t, b, 5, -1);
    }
    return 0;
}

extern "C" s32 PlayerActor_RequestTurnTo(s32 a, u32 idx) {
    PlayerActor *o = PlayerActor_Get(idx);
    if (o) return (o)->requestTurnTo(a, 5, -1);
    return 0;
}

extern "C" s32 PlayerActor_RequestAct30(u16 *a, u32 *b, u8 *c, u32 *d, Character *e) {
    PlayerActor *o = PlayerActor_Get(4);
    if (o) {
        return o->requestAct30(a, *b, *c, *d, e, 6, -1);
    }
    return 0;
}

extern "C" s32 PlayerActor_RequestAct32() {
    PlayerActor *o = PlayerActor_Get(4);
    if (o) return (o)->requestAct32(6, -1);
    return 0;
}

extern "C" s32 PlayerActor_RequestAct79() {
    if (TalkRequest_IsSaveMenuRunning()) return 0;
    PlayerActor *o = PlayerActor_Get(4);
    if (o) {
        if ((o)->testActionFlag(0xb)) return 0;
        Unk_02094a08_Limit k = Unk_02094a08_LIMIT_5;
        if (!(k > (o)->getRequiredPriority())) {
            if (o->action == 0x4f && o->heldItemModel.bobber.curState != 5) {
                PlayerActor_RequestFishReelIn(o, 1, 6, -1);
                return 1;
            }
            return 0;
        }
        return (o)->requestAct79(k, -1);
    }
    return 0;
}

extern "C" void PlayerActor_RequestStowThenAct10(u32 a) {
    PlayerActor *o = PlayerActor_Get(4);
    if (o) {
        s32 t = (o)->getHeldToolKind();
        if (t == 0) goto A;
        if (t == 0xa) {
            if (a == 1) goto A;
        }
        if (a < 2) goto B;
    A:
        (o)->setActionFlag(1);
        (o)->requestAct10(3, 5, -1);
        return;
    B:
        PlayerActor_RequestStowItem(o, 0x10, a, o->position.x, o->position.z, o->rotY, 6, -1);
    }
}

extern "C" s32 PlayerActor_RequestAct10() {
    PlayerActor *o = PlayerActor_Get(4);
    if (o) {
        if (o->action == 0x28) {
            if ((o)->testActionFlag(0xb)) return 1;
        }
        return (o)->requestAct10(3, 5, -1);
    }
    return 0;
}

extern "C" s32 PlayerActor_LocalRequestExitWalkOut() {
    PlayerActor *o = PlayerActor_Get(4);
    s16 h;
    u32 pad;
    VecFx32Ctor v;
    if (o) {
        o->actionPriority = ((Unk_02007694 *)(void *)(o))->getActionDonePriority(o->action);
        if (o->exitMode == 3) {
            s32 r5 = o->exitIndex;
            h = o->rotY;
            if (r5 != -1) {
                SceneExit_GetDoor(Scene_GetWarpRequest(), r5, &pad, &h);
            }
            s32 t = Math_AngleToDir4(h);
            VecFx32Ctor *pv = (VecFx32Ctor *)&o->position;
            v.x = o->position.x;
            v.y = pv->y;
            v.z = pv->z;
            switch (t) {
            case 2: v.z -= 0x6000; break;
            case 0: v.z += 0x6000; break;
            case 3: v.x -= 0x6000; break;
            case 1: v.x += 0x6000; break;
            }
            return PlayerActor_RequestExitWalkOut(o, &v, 6, -1);
        }
    }
    return 0;
}

extern "C" s32 PlayerActor_RequestAct13() {
    PlayerActor *o = PlayerActor_Get(4);
    if (o) {
        o->actionPriority = ((Unk_02007694 *)(void *)(o))->getActionDonePriority(o->action);
        return (o)->requestAct13(5, -1);
    }
    return 0;
}

extern "C" s32 PlayerActor_RequestEmotion(u8 *p) {
    PlayerActor *o = PlayerActor_Get(4);
    u32 v = *p;
    u8 t = sEmotionHoldFrames[v - 1];
    if (o) {
        o->actionPriority = ((Unk_02007694 *)(void *)(o))->getActionDonePriority(o->action);
        return (o)->requestEmotion(*p, t, 5, -1);
    }
    return 0;
}

extern const u32 sPlayerAngleSyncVars[4];
extern const u32 sPlayerStateSyncVars[4];
extern const u8 sEmotionHoldFrames[0x20];
extern const u32 sPlayerPosSyncVars[4];

const u32 sPlayerAngleSyncVars[4] = {4, 5, 6, 7};

const u32 sPlayerStateSyncVars[4] = {8, 9, 10, 11};

const u8 sEmotionHoldFrames[0x20] = {
    0x0f, 0x0f, 0x14, 0x0f, 0x22, 0x22, 0x19, 0x22, 0x22, 0x2c, 0x14, 0x14, 0x24, 0x2c, 0x1c, 0x18,
    0x1a, 0x26, 0x1e, 0x0f, 0x0f, 0x0f, 0x28, 0x0f, 0x1b, 0x14, 0x22, 0x28, 0x14, 0x00, 0x00, 0x00,
};

const u32 sPlayerPosSyncVars[4] = {0, 1, 2, 3};

PlayerSessionTable gPlayerSessionTable;
