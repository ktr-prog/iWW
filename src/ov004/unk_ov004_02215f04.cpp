#include "uptr.h"
#include "host_tick.h"
#include "host_labels.h"
#include "types.h"
#include "npc/VillagerId.h"
#include "gfx/VecFx32.h"
#include "Unk_020d8c7c.h"
#include "gfx/DebugColor.h"
#include "actor/ActorProfile.h"
#include "town/Unk_0204e858_Grid.h"
#include "talk/MsgString9B.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/TalkMsgRequest.h"
#include "talk/ActorTalkRequest.h"
#include "talk/TalkWindowState.h"
#include "actor/NpcActor.h"
#include "actor/VillagerActor.h"
#include "talk/ActorTalkRequest.h"
#include "talk/VillagerTalk.h"
#include "npc/BirthdayHostVillager.h"
#include "npc/NpcActionCtrl.h"
#include "npc/NpcFootstepFx.h"
#include "npc/NpcLookAt.h"
#include "npc/NpcMoveCtrl.h"
#include "npc/NpcTalkCtrl.h"
#include "player/PlayerData.h"
#include "save/VillagerData.h"
#include "npc/BirthdayGuestVillager.h"
#include "proto/itcm/unk_01ffcfc0.h"
#include "proto/main/unk_02002b1c.h"
#include "proto/main/unk_0206269c.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_020815f8.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/ov004/unk_ov004_02214948.h"
#include "proto/ov004/unk_ov004_02215f04.h"
#include "proto/main/unk_0204cc1c.h"














extern "C" {
extern s32 data_020c8cbc;
extern u16 data_020c6cc8;
extern s32 data_020c6d1c;
extern u8 gVec3Zero[];
#define gSaveVillagers HOST_LABEL(u8 (*)[], gSaveVillagers)
extern Unk_0204e858_Grid *gSceneBlockMap;
s32 Vec_DistXZ(VecFx32 *a, VecFx32 *b);
s32 Vec_NotEqual(VecFx32 *a, VecFx32 *b);
s16 Math_Atan2(s32 x, s32 y);
s32 Math_AngleDiffAbs(s32 a, s32 b);
BOOL Camera_FocusOnPoint(VecFx32 *a);
void Camera_SetModeDefault();
void VillagerMemory_RecordTalk(VillagerMemory *self, void *a, u8 *b, u8 *c);
VillagerMemory *Villager_FindOrCreateMemory(VillagerMemory *t, void *b);
u16 *MapBlock_GetItemPtr(void *cell, u32 x, u32 y, u32 z);
BOOL Item_IsFurnitureOrF031(u16 *p);
void Ground_UnlinkUnit(s32 x, s32 z);
s32 Ground_GetWalkLinks(s32, s32);
s32 Scene_GetVillagerHouse();
BOOL SaveVillagers_IsOccupied(u8 *base, s32 idx);
u8 *SaveVillagers_Get(u8 *base, s32 idx);
s32 TalkRequest_SetTargetDone(void *);
}

extern "C" DebugColor data_ov004_02250588(0x1f, 0x14, 0x14, 0x1f);
extern "C" DebugColor data_ov004_02250598(0x14, 0x14, 0x1f, 0x1f);
extern "C" DebugColor data_ov004_0225057c(0x1f, 0x1f, 0x14, 0x1f);
extern "C" DebugColor data_ov004_02250580(0x14, 0x1f, 0x14, 0x1f);
extern "C" DebugColor data_ov004_0225058c(0x14, 0x1f, 0x1f, 0x1f);
extern "C" DebugColor data_ov004_02250594(0x14, 0x18, 0x18, 0x1f);
extern "C" ActorProfile sBirthdayGuestVillagerProfile = { (void *(*)())BirthdayGuestVillager_Create, 0x81, 0x85, 2, 0x5000, 0x5000, 0x3e800 };
extern "C" {
BirthdayGuestVillager *sBirthdayGuestVillager;
}
extern "C" Unk_ov004_0224c228_BFn data_ov004_0224c158 = &BirthdayGuestVillager::drawModel;
extern "C" {
u8 sBirthdayGuestMsgFile[0x28];
}



extern "C" BirthdayGuestVillager *BirthdayGuestVillager_Create() {
    return new BirthdayGuestVillager;
}

extern "C" BirthdayGuestVillager *BirthdayGuestVillager_Get() {
    return sBirthdayGuestVillager;
}

extern "C" s32 Room_PickRandomWalkTarget(VecFx32 *out, VecFx32 *in, s32 angle) {
    s32 gx, gy;
    s32 count, y, x, z;
    FieldPos_ToUnit(&gx, &gy, in);
    count = 0;
    y = count;
    z = count;
    do {
        x = z;
        do {
            if (x != gx && y != gy) {
                if (Ground_GetWalkLinks(x, y)) {
                    count++;
                }
            }
            x++;
        } while (x < 16);
        y++;
    } while (y < 14);
    out->x = in->x;
    out->y = in->y;
    out->z = in->z;
    if (count != 0) {
        s32 pick = Random_GlobalBelow(count);
        s32 k = 0;
        for (y = 0; y < 14; y++) {
            for (x = 0; x < 16; x++) {
                if (x != gx && y != gy) {
                    if (Ground_GetWalkLinks(x, y)) {
                        if (k == pick) {
                            FieldPos_FromUnitCenter(out, x, y);
                            s32 d = Math_Atan2(out->x - in->x, out->z - in->z);
                            if (Math_AngleDiffAbs(angle, d) < 0x2000) {
                                d = angle;
                            }
                            return d;
                        }
                        k++;
                    }
                }
            }
        }
    }
    return angle;
}

BOOL BirthdayGuestVillager::preCreate() {
    if (!VillagerActor::preCreate()) {
        return FALSE;
    }
    sBirthdayGuestVillager = this;
    setTalkRequest(&talk);
    talk.attachOwner(this);
    changeAct(0);
    return TRUE;
}

BOOL BirthdayGuestVillager::onCreate() {
    if (!VillagerActor::onCreate()) {
        return FALSE;
    }
    drawFn = data_ov004_0224c158;
    blockFurnitureCells();
    footstepFx.enableFootsteps();
    return TRUE;
}

BOOL BirthdayGuestVillager::drawModel() {
    if (NpcActor::onDraw()) {
        return TRUE;
    }
    return FALSE;
}

BOOL BirthdayGuestVillager::onDraw() {
    if (drawFn) {
        return (this->*drawFn)();
    }
    return TRUE;
}

BOOL BirthdayGuestVillager::preDelete() {
    if (!VillagerActor::preDelete()) {
        return FALSE;
    }
    sBirthdayGuestVillager = 0;
    return TRUE;
}

BOOL BirthdayGuestVillager::updateAct() {
    execAct();
    return TRUE;
}

void BirthdayGuestVillager::blockFurnitureCells() {
    Unk_0204e858_Grid *g = gSceneBlockMap;
    TownBlockCell *c;
    s32 y, x;
    if (g->width > 0 && g->height > 0 && g->blocks) {
        c = g->blocks;
    } else {
        c = 0;
    }
    y = 0;
    volatile s32 z = 0;
    for (; y < 16; y++) {
        for (x = 0; x < 16; x++) {
            u16 *it = MapBlock_GetItemPtr(c, x, y, z);
            if (it) {
                if (Item_IsFurnitureOrF031(it)) {
                    Ground_UnlinkUnit(x, y);
                }
            }
        }
    }
}

void BirthdayGuestVillager::recordPlayerTalk() {
    PlayerData *p = PlayerData_GetCurrent();
    if (p) {
        if (villagerData) {
            PlayerId *r = p->getPlayerId();
            VillagerMemory_RecordTalk(Villager_FindOrCreateMemory(((VillagerData *)villagerData)->memories, r), 0, 0, 0);
        }
    }
}

BOOL BirthdayGuestVillager::acceptsInteraction(void *) {
    if (talkCtrl.isBusy()) {
        return FALSE;
    }
    if (act <= 3) {
        return TRUE;
    }
    return FALSE;
}

void BirthdayGuestVillager::onInteractionEvent(u32 a, u8 b) {
    VecFx32 v;
    v.x = position.x;
    v.y = position.y;
    v.z = position.z;
    v.y += 0x2000;
    switch (a) {
    case 3:
        partnerPlayer = b;
        changeAct(4);
        break;
    case 0:
        partnerPlayer = b;
        Camera_FocusOnPoint(&v);
        changeAct(5);
        break;
    case 8:
        recordPlayerTalk();
        Camera_SetModeDefault();
        changeAct(0);
        break;
    case 4:
        changeAct(0);
        break;
    case 1:
    case 2:
    case 5:
    case 6:
    case 7:
        break;
    }
}

VillagerMemory *BirthdayGuestVillagerTalk::getPlayerMemory() {
    BirthdayGuestVillager *o = villager;
    if (o && o->villagerData) {
        PlayerId *r = PlayerData_GetCurrent()->getPlayerId();
        return Villager_FindOrCreateMemory(((VillagerData *)villager->villagerData)->memories, r);
    }
    return 0;
}

BOOL BirthdayGuestVillagerTalk::isNotTalkedYet() {
    VillagerMemory *p = getPlayerMemory();
    if (p) {
        if (p->isTalkedToday()) {
            return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}

void BirthdayGuestVillagerTalk::setTalked() {
    VillagerMemory *p = getPlayerMemory();
    if (p) {
        p->setTalkedToday();
    }
}

void BirthdayGuestVillagerTalk::attachOwner(VillagerActor *owner) {
    begin(owner, 0x11);
    villager = static_cast<BirthdayGuestVillager *>(owner);
}

void BirthdayGuestVillagerTalk::start(TalkStartMsg *arg) {
    BirthdayGuestVillager *o = villager;
    ((VillagerData *)o->villagerData)->getVillagerId()->makeFileName(sBirthdayGuestMsgFile, 0x28, "ev_nbirth");
    arg->msgKey = (const char *)sBirthdayGuestMsgFile;
    s32 r6 = 2;
    if (isNotTalkedYet()) {
        r6 = 0;
    } else if (BirthdayHostVillager_HasReceivedGift()) {
        r6 = 1;
    }
    setTalked();
    switch (r6) {
    case 0:
        arg->msgIndex = Random_GlobalBelow(2) + 0x1a;
        break;
    case 1:
        arg->msgIndex = Random_GlobalBelow(4) + 0x1e;
        break;
    default:
        arg->msgIndex = Random_GlobalBelow(2) + 0x1c;
        break;
    }
    o = villager;
    if (o->talk.window) {
        s32 p = Scene_GetVillagerHouse();
        if (SaveVillagers_IsOccupied(gSaveVillagers, p)) {
            MsgString9B loc;
            o->talk.setVillagerNameSlot(((VillagerData *)SaveVillagers_Get(gSaveVillagers, p))->getVillagerId(), 1);
        }
        BirthdayGuestVillager *o2 = villager;
        if (o2) {
            void *m = o2->villagerData;
            if (m) {
                o->talk.setVillagerNameSlot(((VillagerData *)m)->getVillagerId(), 0);
            }
        }
    }
}

void BirthdayGuestVillagerTalk::onMessageStart(u32) {}

void BirthdayGuestVillagerTalk::onMessageEnd(u32) {}

void BirthdayGuestVillagerTalk::onChoice(u32) {}

BOOL BirthdayGuestVillager::changeAct(s32 idx) {
    static Unk_ov004_0224c228_BFn tbl[7] = {
        &BirthdayGuestVillager::setupAct00, &BirthdayGuestVillager::setupAct01,
        &BirthdayGuestVillager::setupAct02, &BirthdayGuestVillager::setupAct03,
        &BirthdayGuestVillager::setupAct04, &BirthdayGuestVillager::setupAct05,
        &BirthdayGuestVillager::setupAct06,
    };
    if (idx < 7) {
        if ((this->*tbl[idx])()) {
            act = idx;
            return TRUE;
        }
    }
    return FALSE;
}

void BirthdayGuestVillager::execAct() {
    static Unk_ov004_0224c228_VFn tbl[7] = {
        &BirthdayGuestVillager::mainAct00, &BirthdayGuestVillager::mainAct01,
        &BirthdayGuestVillager::mainAct02, &BirthdayGuestVillager::mainAct03,
        &BirthdayGuestVillager::mainAct04, &BirthdayGuestVillager::mainAct05,
        &BirthdayGuestVillager::mainAct06,
    };
    s32 s = act;
    if (s < 7) {
        (this->*tbl[s])();
    }
}

BOOL BirthdayGuestVillager::setupAct00() {
    if (actionCtrl.requestStand(1, data_020c6cc8)) {
        lookAt.setTarget(1, 0, 0, (VecFx32 *)(gVec3Zero), 4, data_020c6d1c, 1);
        return TRUE;
    }
    return FALSE;
}

void BirthdayGuestVillager::mainAct00() {
    VecFx32 v;
    BirthdayHostVillager *a = BirthdayHostVillager_Get();
    s32 d;
    if (a) {
        d = Vec_DistXZ(&a->position, &position);
    } else {
        d = data_020c8cbc;
    }
    if (chatCooldown != 0) {
        chatCooldown -= TICK_STEP_ENDS() ? 1 : 0;
    }
    if (collider.isHit != 0) {
        if (actionCtrl.getAction() == 1) {
            if (actionCtrl.requestStand(1, data_020c6cc8)) {
                goto end;
            }
        }
    }
    if (d < 0x3334) {
        if (changeAct(1)) {
            goto end;
        }
    }
    if (actionCtrl.getAction() == 0) {
        if (walkTimer != 0) {
            walkTimer -= TICK_STEP_ENDS() ? 1 : 0;
        }
        if (walkTimer == 0) {
            walkAngle = Room_PickRandomWalkTarget(&walkTarget, &position, rotY);
            waypoint.x = walkTarget.x;
            waypoint.y = walkTarget.y;
            waypoint.z = walkTarget.z;
            if (a && d >= 0x6000 && Random_GlobalBelow(2) == 0) {
                d = Math_Atan2(a->position.x - position.x, a->position.z - position.z);
                s32 df = Math_AngleDiffAbs(rotY, d);
                VecFx32 *pa = (VecFx32 *)&a->position;
                s32 xx = *(volatile s32 *)&a->position.x;
                VecFx32 *pq = &walkTarget;
                pq->x = xx;
                walkTarget.y = pa->y;
                walkTarget.z = pa->z;
                waypoint.x = pq->x;
                waypoint.y = pq->y;
                waypoint.z = pq->z;
                if (df >= 0x2000) {
                    walkAngle = d;
                }
            }
            s16 t = walkAngle;
            if (t != rotY) {
                if (!actionCtrl.requestAction(3, 1, 0, 0, 0, t, 0, 0, data_020c6cc8, 0)) {
                    goto end;
                }
                walkTimer = Random_GlobalBelow(0x46) + 0x14;
            } else {
                if (!actionCtrl.requestAction(1, 1, walkTarget.x, walkTarget.z, 0, 0, 0, 0, data_020c6cc8, 0)) {
                    goto end;
                }
                walkTimer = Random_GlobalBelow(0x50) + 0x14;
            }
        } else {
            if (actionCtrl.isActionDone()) {
                actionCtrl.requestStand(1, data_020c6cc8);
            }
        }
    } else {
        if (actionCtrl.getAction() == 3) {
            if (actionCtrl.isActionDone()) {
                actionCtrl.requestAction(1, 1, walkTarget.x, walkTarget.z, 0, 0, 0, 0, data_020c6cc8, 0);
            }
        } else if (actionCtrl.getAction() == 1) {
            switch (findAvoidPos(&v)) {
            case 1:
                actionCtrl.requestStand(1, data_020c6cc8);
                break;
            case 2: {
                VecFx32 *pv = &waypoint;
                pv->x = v.x;
                waypoint.y = v.y;
                waypoint.z = v.z;
                moveCtrl.setWaypoint(&waypoint);
                break;
            }
            default:
                if (Vec_NotEqual(&waypoint, &walkTarget)) {
                    VecFx32 *pw = &walkTarget;
                    waypoint.x = pw->x;
                    waypoint.y = walkTarget.y;
                    waypoint.z = walkTarget.z;
                    moveCtrl.setWaypoint(pw);
                } else if (Vec_DistXZ(&walkTarget, &position) < 0x200) {
                    actionCtrl.requestStand(1, data_020c6cc8);
                }
                break;
            }
        }
    }
end:;
}

BOOL BirthdayGuestVillager::setupAct01() {
    if (chatCooldown == 0) {
        BirthdayHostVillager *o = BirthdayHostVillager_Get();
        if (o != NULL) {
            walkAngle = Math_Atan2(o->position.x - position.x, o->position.z - position.z);
            BirthdayHostVillager *g = sBirthdayHostVillager;
            BOOL r;
            if (g != NULL && (u32)g->act <= 1) {
                r = g->changeAct(1);
            } else {
                r = FALSE;
            }
            if (r) {
                actionCtrl.requestAction(3, 1, 0, 0, 0, walkAngle, 0, 0, data_020c6cc8, 0);
                lookAt.setTarget(2, 0, o, (VecFx32 *)(gVec3Zero), 4, data_020c6d1c, 1);
                return TRUE;
            }
        }
    }
    return FALSE;
}

void BirthdayGuestVillager::mainAct01() {
    s32 a = walkAngle;
    s32 b = (s16)(a + 0x8000);
    BirthdayHostVillager *o = BirthdayHostVillager_Get();
    if (o != NULL) {
        s32 da = Math_AngleDiffAbs(a, rotY);
        s32 db = Math_AngleDiffAbs(b, o->rotY);
        if (da <= 0x500 && db <= 0x500) {
            if (Random_GlobalBelow(2)) {
                if (changeAct(3)) {
                    chatCooldown = 0x12c;
                }
            } else {
                if (changeAct(2)) {
                    chatCooldown = 0x12c;
                }
            }
        }
    }
}

BOOL BirthdayGuestVillager::setupAct02() {
    BirthdayHostVillager *o = sBirthdayHostVillager;
    BOOL r;
    if (o != NULL && (u32)o->act <= 1) {
        r = o->changeAct(2);
    } else {
        r = FALSE;
    }
    if (r) {
        if (actionCtrl.requestEmotion(1, 3, data_020c6cc8)) {
            emotionTimer = 0x1e;
            return TRUE;
        }
    }
    return FALSE;
}

void BirthdayGuestVillager::mainAct02() {
    if (emotionTimer != 0) {
        emotionTimer -= TICK_STEP_ENDS() ? 1 : 0;
    }
    switch (emotionTimer) {
    case 1:
        actionCtrl.requestEmotion(1, 0, data_020c6cc8);
        break;
    case 0:
        changeAct(0);
    }
}

BOOL BirthdayGuestVillager::setupAct03() {
    BirthdayHostVillager *o = sBirthdayHostVillager;
    BOOL r;
    if (o != NULL && (u32)o->act <= 1) {
        r = o->changeAct(3);
    } else {
        r = FALSE;
    }
    if (r) {
        if (actionCtrl.requestEmotion(1, 0x1a, data_020c6cc8)) {
            emotionTimer = 0x32;
            return TRUE;
        }
    }
    return FALSE;
}

void BirthdayGuestVillager::mainAct03() {
    if (emotionTimer != 0) {
        emotionTimer -= TICK_STEP_ENDS() ? 1 : 0;
    }
    switch (emotionTimer) {
    case 1:
        actionCtrl.requestEmotion(1, 0, data_020c6cc8);
        break;
    case 0:
        changeAct(0);
    }
}

BOOL BirthdayGuestVillager::setupAct04() {
    if ((u32)(act - 1) <= 2) {
        actionCtrl.requestEmotion(2, 0, data_020c6cc8);
    }
    return TRUE;
}

void BirthdayGuestVillager::mainAct04() {}

BOOL BirthdayGuestVillager::setupAct05() {
    void *p = PlayerActor_GetActor(4);
    if (p != NULL) {
        talkCtrl.requestTurnAndTalk(0, getAngleTo((NpcActor *)p), 0);
        return TRUE;
    }
    return FALSE;
}

void BirthdayGuestVillager::mainAct05() { changeAct(6); }

BOOL BirthdayGuestVillager::setupAct06() { return TRUE; }

void BirthdayGuestVillager::mainAct06() {
    TalkWindowState *p = talk.window;
    if (p != NULL && p->state == 0) {
        TalkRequest_SetTargetDone(this);
    }
}

void BirthdayGuestVillager::onTalkMelodyPlayed() {
    mood.severeSickness = 1;
}

BOOL BirthdayGuestVillager::canPlayTalkMelody() {
    if (mood.severeSickness == 0) {
        return TRUE;
    }
    return FALSE;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_02215f04) {
    HOST_OVERLAY_VAR(data_ov004_02250588),
    HOST_OVERLAY_VAR(data_ov004_02250598),
    HOST_OVERLAY_VAR(data_ov004_0225057c),
    HOST_OVERLAY_VAR(data_ov004_02250580),
    HOST_OVERLAY_VAR(data_ov004_0225058c),
    HOST_OVERLAY_VAR(data_ov004_02250594),
    HOST_OVERLAY_VAR(sBirthdayGuestVillagerProfile),
    HOST_OVERLAY_VAR(sBirthdayGuestVillager),
    HOST_OVERLAY_VAR(data_ov004_0224c158),
    HOST_OVERLAY_VAR(sBirthdayGuestMsgFile),
    HOST_OVERLAY_VARS_END
};
