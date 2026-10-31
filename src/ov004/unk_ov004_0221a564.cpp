#include "types.h"
#include "host_labels.h"
#include "gfx/VecFx32.h"
#include "actor/ActorProfile.h"
#include "npc/VillagerClothModel.h"
#include "room/RoomFreeUnitMap.h"
#include "npc/VillagerMood.h"
#include "snd/SndSeEmitter.h"
#include "npc/NpcAnimCtrl.h"
#include "npc/NpcSpeechState.h"
#include "npc/NpcLookAt.h"
#include "npc/NpcObstacleProbe.h"
#include "npc/NpcMoveCtrl.h"
#include "npc/NpcMoveAnimSet.h"
#include "npc/Unk_0201ad18.h"
#include "npc/NpcFootstepFx.h"
#include "sys/ProcBase.h"
#include "npc/NpcActionCtrl.h"
#include "snd/SndSeEmitterKind1.h"
#include "npc/NpcTalkCtrl.h"
#include "npc/NpcFaceAnim.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/TalkMsgRequest.h"
#include "talk/ActorTalkRequest.h"
#include "actor/NpcActor.h"
#include "actor/VillagerActor.h"
#include "talk/ActorTalkRequest.h"
#include "talk/VillagerTalk.h"
#include "talk/TalkTopicMsg.h"
#include "talk/TalkWindowState.h"
#include "gfx/DebugColor.h"
#include "npc/VillagerId.h"
#include "player/PlayerData.h"
#include "talk/ChoiceList.h"
#include "npc/SickVillagerRecord.h"
#include "save/VillagerData.h"
#include "town/BlockMap.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/ov004/unk_ov004_02215f04.h"
#include "proto/ov004/unk_ov004_0221a564.h"

class SickVillager;

class SickVillagerTalk;

typedef BOOL (SickVillager::*Unk_ov004_0224cb98_BFn)();
typedef void (SickVillager::*Unk_ov004_0224cb98_VFn)();

extern SickVillager *sSickVillager;
extern "C" {
extern u16 data_020c6cc8;
extern u32 gFrameCounter;
#define gSaveVillagers HOST_LABEL(u8 (*)[], gSaveVillagers)
extern u8 gTalkMsgIndexNone[];
extern u8 gVec3Zero[];
extern s32 data_020c6d1c;
extern BlockMap *gSceneBlockMap;
extern u8 data_ov004_0225095c[0x28];
extern u8 data_ov004_02250984[0x28];

s32 TalkRequest_SetTargetDone(void *);
s32 Vec_NotEqual(void *, void *);
s32 Vec_DistXZ(void *, void *);
SickVillagerRecord *SaveVillagers_GetUnk3830(void *p);
BOOL SickVillager_IsMedicine(u16 *p, s32 x);
BOOL SickVillager_HasCurrentVisitor(void *o);
void SickVillager_SetCurrentVisitor();
void *Villager_FindOrCreateMemory(void *, void *);
void VillagerMemory_RecordTalk(void *, s32, s32, s32);
u16 *MapBlock_GetItemPtr(void *, s32, s32, s32);
s32 Item_IsFurnitureOrF031(u16 *p);
void Ground_UnlinkUnit(s32, s32);
s32 Item_IsFurniture(void *);
u32 Item_GetFurnitureIndex(void *);
}













class SickVillagerTalk : public VillagerTalk {
public:
    SickVillagerTalk() {}
    virtual void onMessageStart(u32 attr);
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);
    virtual void update();
    virtual void onTaskDone(u32 a);

    void attachOwner(SickVillager *owner);
    u8 getSickStage();

    /* 0x1a0 */ u8 sickStage;
    /* 0x1a1 */ u8 pad_1a1[3];
    /* 0x1a4 */ SickVillager *villager;
};

class SickVillager : public VillagerActor {
public:
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL preDelete();
    virtual BOOL onDraw();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 idx, u8 v);
    virtual BOOL updateAct();
    virtual BOOL canPlayTalkMelody();
    virtual void onTalkMelodyPlayed();

    BOOL changeAct(s32 s);
    void execAct();
    void mainAct07();
    BOOL setupAct07();
    void mainAct06();
    BOOL setupAct06();
    void mainAct05();
    BOOL setupAct05();
    void mainAct04();
    BOOL setupAct04();
    void mainAct03();
    BOOL setupAct03();
    void mainAct02();
    BOOL setupAct02();
    void mainAct01();
    BOOL setupAct01();
    void mainAct00();
    BOOL setupAct00();
    void recordPlayerTalk();
    void blockFurnitureCells();
    BOOL drawModel();

    /* 0x894 */ u8 hasVisitor;
    /* 0x895 */ u8 isAnswered;
    /* 0x896 */ u8 talkMelodyPlayed;
    /* 0x897 */ u8 pad_897;
    /* 0x898 */ u32 act;
    /* 0x89c */ SickVillagerTalk talk;
    /* 0xa44 */ Unk_ov004_0224cb98_BFn drawFn;
    /* 0xa4c */ RoomFreeUnitMap freeUnitMap;
    /* 0xa6c */ s16 walkAngle;
    /* 0xa6e */ u16 walkTimer;
    /* 0xa70 */ VecFx32 waypoint;
    /* 0xa7c */ VecFx32 walkTarget;
    /* 0xa88 */ u8 emotionTimer;
    /* 0xa89 */ u8 pad_a89[3];
};

extern "C" SickVillager *SickVillager_Create();
DebugColor data_ov004_02250938(31, 20, 20, 31);
DebugColor data_ov004_02250940(20, 20, 31, 31);
extern "C" {
u8 data_ov004_0225095c[0x28];
}
DebugColor data_ov004_02250948(31, 31, 20, 31);
DebugColor data_ov004_02250944(20, 31, 20, 31);
DebugColor data_ov004_02250954(20, 31, 31, 31);
DebugColor data_ov004_02250958(20, 24, 24, 31);

static inline BOOL Unk_ov004_0221b3f8_Chk(u16 *p) {
    u16 v;
    BOOL r;
    if (Item_IsFurniture(p)) {
        v = 0x155e;
        if (Item_GetFurnitureIndex(p) == Item_GetFurnitureIndex(&v)) {
            r = TRUE;
        } else {
            r = FALSE;
        }
    } else {
        if (*p == 0x155e) {
            r = TRUE;
        } else {
            r = FALSE;
        }
    }
    return r;
}

extern "C" SickVillager *SickVillager_Create() {
    return new SickVillager;
}

extern "C" BOOL SickVillager_IsMedicine(u16 *p, s32 x) {
    if (x == 0) {
        if (Unk_ov004_0221b3f8_Chk(p)) {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL SickVillager::preCreate() {
    if (((VillagerActor *)(this))->VillagerActor::preCreate() == 0) {
        return FALSE;
    }
    sSickVillager = this;
    ((NpcActor *)(this))->setTalkRequest((ActorTalkRequest *)(&talk));
    talk.attachOwner(this);
    SickVillagerRecord *p = SaveVillagers_GetUnk3830(gSaveVillagers);
    talk.sickStage = p->sickDay;
    if (talk.getSickStage() > 1) {
        ((NpcMoveAnimSet *)(&moveAnimSet))->setWalkAnim(0xea);
        ((NpcMoveAnimSet *)(&moveAnimSet))->setStandAnim(0xe9);
        ((NpcMoveCtrl *)(&moveCtrl))->setSpeedPreset(1, 0xa4, 0x10, 0x10);
        ((NpcLookAt *)(&lookAt))->setTarget(0, 0, 0, (VecFx32 *)(gVec3Zero), 4, data_020c6d1c, 1);
        mood.severeSickness = 1;
    } else {
        ((NpcMoveCtrl *)(&moveCtrl))->setSpeedPreset(1, 0xcd, 0x14, 0x14);
        mood.severeSickness = 0;
    }
    changeAct(0);
    return TRUE;
}

BOOL SickVillager::onCreate() {
    if (((VillagerActor *)(this))->VillagerActor::onCreate() == 0) {
        return FALSE;
    }
    drawFn = &SickVillager::drawModel;
    blockFurnitureCells();
    ((NpcFootstepFx *)(&footstepFx))->enableFootsteps();
    return TRUE;
}

BOOL SickVillager::drawModel() {
    if (((NpcActor *)(this))->NpcActor::onDraw()) {
        return TRUE;
    }
    return FALSE;
}

BOOL SickVillager::onDraw() {
    if (drawFn) {
        return (this->*drawFn)();
    }
    return TRUE;
}

BOOL SickVillager::preDelete() {
    if (((VillagerActor *)(this))->VillagerActor::preDelete() == 0) {
        return FALSE;
    }
    sSickVillager = 0;
    return TRUE;
}

BOOL SickVillager::updateAct() {
    execAct();
    mood.updateSoundPos(this);
    return TRUE;
}

void SickVillager::blockFurnitureCells() {
    BlockMap *m = gSceneBlockMap;
    void *p;
    if (m->width > 0 && m->height > 0 && (p = m->blocks) != 0) {
    } else {
        p = 0;
    }
    s32 y = 0;
    s32 z = 0;
    for (; y < 16; y++) {
        for (s32 x = 0; x < 16; x++) {
            u16 *item;
            if ((item = MapBlock_GetItemPtr(p, x, y, z)) != NULL) {
                if (Item_IsFurnitureOrF031(item)) {
                    Ground_UnlinkUnit(x, y);
                }
            }
        }
    }
}

void SickVillager::recordPlayerTalk() {
    void *p = PlayerData_GetCurrent();
    if (p) {
        if (villagerData) {
            void *g = ((PlayerData *)(p))->getPlayerId();
            void *t = Villager_FindOrCreateMemory(villagerData, g);
            VillagerMemory_RecordTalk(t, 0, 0, 0);
        }
    }
}

BOOL SickVillager::acceptsInteraction(void *) {
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy()) {
        return FALSE;
    }
    if (act > 1) {
        return FALSE;
    }
    return TRUE;
}

void SickVillager::onInteractionEvent(u32 idx, u8 v) {
    VecFx32CtorDtor vec;
    vec.x = position.x;
    vec.y = position.y;
    vec.z = position.z;
    vec.y += 0x2000;
    switch (idx) {
    case 3:
        partnerPlayer = v;
        changeAct(2);
        break;
    case 0:
        partnerPlayer = v;
        ((ActorTalkRequest *)(&talk))->setTalkPlayer(((NpcActor *)(this))->getPlayerActor(4));
        changeAct(3);
        break;
    case 8:
        recordPlayerTalk();
        changeAct(0);
        break;
    case 4:
        changeAct(0);
        break;
    }
}

u8 SickVillagerTalk::getSickStage() { return sickStage; }

extern "C" BOOL SickVillager_HasCurrentVisitor(void *o) {
    if (SaveVillagers_GetUnk3830(gSaveVillagers)->hasTodaysVisitor()) {
        return TRUE;
    }
    return FALSE;
}

extern "C" void SickVillager_SetCurrentVisitor() {
    SickVillagerRecord *p = SaveVillagers_GetUnk3830(gSaveVillagers);
    p->setTodaysVisitor(PlayerData_GetCurrent()->getPlayerId());
}

void SickVillagerTalk::attachOwner(SickVillager *owner) {
    ((VillagerTalk *)(this))->begin((VillagerActor *)(owner), 0x11);
    villager = owner;
}

void SickVillagerTalk::onTaskDone(u32 a) {
    if (a == 4) {
        SickVillager_SetCurrentVisitor();
        ((TalkWindowState *)window)->nextState = 1;
    }
}

void SickVillagerTalk::update() {
    u8 buf[4];
    SickVillager *o = villager;
    if (o->act == 6) {
        if (MenuCtrl_IsFinished()) {
            if (MenuCtrl_IsResultOk() == 0) {
                ((TalkWindowState *)window)->nextState = 1;
                buf[0] = Random_GlobalBelow(3) + 13;
                ((TalkWindowState *)(window))->setNextMessage((u8 *)(buf), (void *)(void *)(0));
                villager->changeAct(4);
            } else {
                Pocket_RemoveItem(MenuCtrl_GetIndex());
                buf[1] = Random_GlobalBelow(3) + 16;
                ((TalkWindowState *)(window))->setNextMessage((u8 *)(&buf[1]), (void *)(void *)(0));
                *(u16 *)(buf + 2) = 0x155e;
                ((ActorTalkRequest *)(this))->requestTakeItem((u16 *)(buf + 2), 0, 6, 0);
                villager->changeAct(7);
            }
        }
    }
}

void SickVillagerTalk::start(TalkStartMsg *out_) {
    TalkStartMsg *out = out_;
    out->msgKey = (const char *)data_ov004_0225095c;
    getSickStage();
    if (villager->mood.severeSickness == 0) {
        ((VillagerData *)(villager->villagerData))->getVillagerId()->makeFileName((data_ov004_0225095c), 0x28, "q12_ask1_2");
    } else {
        ((VillagerData *)(villager->villagerData))->getVillagerId()->makeFileName((data_ov004_0225095c), 0x28, "q12_ask3_5");
    }
    villager->isAnswered = 0;
    if (SickVillager_HasCurrentVisitor(this)) {
        out->msgIndex = Random_GlobalBelow(3) + 3;
        villager->hasVisitor = 1;
    } else {
        out->msgIndex = Random_GlobalBelow(3);
        villager->hasVisitor = 0;
    }
}

void SickVillagerTalk::onMessageStart(u32) {
    SickVillagerRecord *p = SaveVillagers_GetUnk3830(gSaveVillagers);
    if (p != 0) {
        if (p->getTodaysVisitor() != 0) {
            ((ActorTalkRequest *)(this))->setPlayerNameSlot(p->getTodaysVisitor(), 0);
        }
    }
}

void SickVillagerTalk::onMessageEnd(u32) {
    u8 b[6];
    SickVillager *o = villager;
    if (o->isAnswered == 0) {
        switch (msgIndex) {
        case 0:
        case 1:
        case 2: {
            void *h = ((TalkWindowState *)(window))->getChoiceList();
            if (h == 0) break;
            ((ChoiceList *)(h))->reset(3, 2);
            b[0] = 0x15;
            ((ChoiceList *)(h))->setEntry(0, (const u8 *)(&b[0]), 0, (const u8 *)(void *)(gTalkMsgIndexNone), (const char *)(0), 0);
            b[1] = 0x16;
            ((ChoiceList *)(h))->setEntry(1, (const u8 *)(&b[1]), 0, (const u8 *)(void *)(gTalkMsgIndexNone), (const char *)(0), 0);
            b[2] = Random_GlobalBelow(10) + 10;
            ((ChoiceList *)(h))->setEntry(2, (const u8 *)(&b[2]), 0, (const u8 *)(void *)(gTalkMsgIndexNone), (const char *)(0), 0);
            ((ChoiceList *)(h))->loadTexts();
            ((TalkWindowState *)(window))->openChoices(1);
            break;
        }
        case 3:
        case 4:
        case 5: {
            void *h = ((TalkWindowState *)(window))->getChoiceList();
            if (h == 0) break;
            ((ChoiceList *)(h))->reset(2, 1);
            b[3] = 0x17;
            ((ChoiceList *)(h))->setEntry(0, (const u8 *)(&b[3]), 0, (const u8 *)(void *)(gTalkMsgIndexNone), (const char *)(0), 0);
            b[4] = Random_GlobalBelow(10) + 0x78;
            ((ChoiceList *)(h))->setEntry(1, (const u8 *)(&b[4]), 0, (const u8 *)(void *)(gTalkMsgIndexNone), (const char *)(0), 0);
            ((ChoiceList *)(h))->loadTexts();
            ((TalkWindowState *)(window))->openChoices(1);
            break;
        }
        }
    } else {
        switch (msgIndex) {
        case 7:
        case 8:
        case 9:
            o->changeAct(5);
            break;
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            break;
        case 16:
        case 17:
        case 18:
            Snd_PlaySe(0x5f);
            break;
        }
    }
}

void SickVillagerTalk::onChoice(u32) {
    u8 buf[6];
    s32 t = ((ChoiceList *)(((TalkWindowState *)(villager->talk.window))->getChoiceList()))->getResult();
    if (villager->mood.severeSickness == 0) {
        ((VillagerData *)(villager->villagerData))->getVillagerId()->makeFileName((data_ov004_02250984), 0x28, "q12_sick1_2");
        villager->isAnswered = 1;
    } else {
        ((VillagerData *)(villager->villagerData))->getVillagerId()->makeFileName((data_ov004_02250984), 0x28, "q12_sick3_5");
        villager->isAnswered = 1;
    }
    if (villager->hasVisitor == 0) {
        switch (t) {
        case 0:
            if (MenuCtrl_BuildPocketMask(SickVillager_IsMedicine) != 0) {
                buf[0] = Random_GlobalBelow(3) + 7;
                ((TalkWindowState *)(villager->talk.window))->setNextMessage((u8 *)(&buf[0]), (void *)(void *)(data_ov004_02250984));
            } else {
                buf[1] = Random_GlobalBelow(3) + 10;
                ((TalkWindowState *)(villager->talk.window))->setNextMessage((u8 *)(&buf[1]), (void *)(void *)(data_ov004_02250984));
            }
            break;
        case 1:
            buf[2] = Random_GlobalBelow(4);
            ((TalkWindowState *)(villager->talk.window))->setNextMessage((u8 *)(&buf[2]), (void *)(void *)(data_ov004_02250984));
            break;
        default:
            buf[3] = Random_GlobalBelow(3) + 4;
            ((TalkWindowState *)(villager->talk.window))->setNextMessage((u8 *)(&buf[3]), (void *)(void *)(data_ov004_02250984));
            break;
        }
    } else {
        if (t == 0) {
            buf[4] = Random_GlobalBelow(3) + 0x13;
            ((TalkWindowState *)(villager->talk.window))->setNextMessage((u8 *)(&buf[4]), (void *)(void *)(data_ov004_02250984));
        } else {
            buf[5] = Random_GlobalBelow(3) + 4;
            ((TalkWindowState *)(villager->talk.window))->setNextMessage((u8 *)(&buf[5]), (void *)(void *)(data_ov004_02250984));
        }
    }
}

BOOL SickVillager::changeAct(s32 s) {
    static Unk_ov004_0224cb98_BFn tbl[8] = {
        &SickVillager::setupAct00, &SickVillager::setupAct01,
        &SickVillager::setupAct02, &SickVillager::setupAct03,
        &SickVillager::setupAct04, &SickVillager::setupAct05,
        &SickVillager::setupAct06, &SickVillager::setupAct07,
    };
    if (s < 8) {
        if ((this->*tbl[s])()) {
            act = s;
            return TRUE;
        }
    }
    return FALSE;
}

extern "C" ActorProfile sSickVillagerProfile = {(void *(*)())SickVillager_Create, 0x83, 0x87, 2, 0x5000, 0x5000, 0x3e800};
SickVillager *sSickVillager;
extern "C" {
u8 data_ov004_02250984[0x28];
}

void SickVillager::execAct() {
    static Unk_ov004_0224cb98_VFn tbl[8] = {
        &SickVillager::mainAct00, &SickVillager::mainAct01,
        &SickVillager::mainAct02, &SickVillager::mainAct03,
        &SickVillager::mainAct04, &SickVillager::mainAct05,
        &SickVillager::mainAct06, &SickVillager::mainAct07,
    };
    s32 s = act;
    if (s < 8) {
        (this->*tbl[s])();
    }
}

BOOL SickVillager::setupAct00() {
    return ((NpcActionCtrl *)(&actionCtrl))->requestStand(1, data_020c6cc8);
}

void SickVillager::mainAct00() {
    VecFx32 v;
    if (mood.severeSickness != 0) {
        if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 1) {
            if (gFrameCounter % 14 == 0) {
                mood.playMood3Effect(this);
            }
        }
    }
    if (collider.isHit != 0) {
        if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 1) {
            if (changeAct(1)) {
                return;
            }
        }
    }
    if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 0) {
        if (walkTimer != 0) {
            walkTimer--;
        }
        if (walkTimer == 0) {
            walkAngle = Room_PickRandomWalkTarget(&walkTarget, &position, rotY);
            waypoint.x = walkTarget.x;
            waypoint.y = walkTarget.y;
            waypoint.z = walkTarget.z;
            if (walkAngle != rotY) {
                if (((NpcActionCtrl *)(&actionCtrl))->requestAction(3, 1, 0, 0, 0, walkAngle, 0, 0, data_020c6cc8, 0) == 0) {
                    return;
                }
                if (mood.severeSickness != 0) {
                    walkTimer = Random_GlobalBelow(0x46) + 0x32;
                } else {
                    walkTimer = Random_GlobalBelow(0x46) + 0x14;
                }
            } else {
                if (((NpcActionCtrl *)(&actionCtrl))->requestAction(1, 1, walkTarget.x, walkTarget.z, 0, 0, 0, 0, data_020c6cc8, 0) == 0) {
                    return;
                }
                if (mood.severeSickness != 0) {
                    walkTimer = Random_GlobalBelow(0x46) + 0x32;
                } else {
                    walkTimer = Random_GlobalBelow(0x50) + 0x14;
                }
            }
        } else {
            if (((NpcActionCtrl *)(&actionCtrl))->isActionDone() != 0) {
                ((NpcActionCtrl *)(&actionCtrl))->requestStand(1, data_020c6cc8);
            }
        }
    } else {
        if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 3) {
            if (((NpcActionCtrl *)(&actionCtrl))->isActionDone() != 0) {
                ((NpcActionCtrl *)(&actionCtrl))->requestAction(1, 1, walkTarget.x, walkTarget.z, 0, 0, 0, 0, data_020c6cc8, 0);
            }
        } else if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 1) {
            switch (((NpcActor *)(this))->findAvoidPos((VecFx32 *)(&v))) {
            case 1:
                ((NpcActionCtrl *)(&actionCtrl))->requestStand(1, data_020c6cc8);
                break;
            case 2:
                waypoint = v;
                ((NpcMoveCtrl *)(&moveCtrl))->setWaypoint((VecFx32 *)(&waypoint));
                break;
            default:
                if (Vec_NotEqual(&waypoint, &walkTarget) != 0) {
                    waypoint = walkTarget;
                    ((NpcMoveCtrl *)(&moveCtrl))->setWaypoint((VecFx32 *)(&walkTarget));
                } else if (Vec_DistXZ(&walkTarget, &position) < 0x200) {
                    changeAct(1);
                }
                break;
            }
        }
    }
}

BOOL SickVillager::setupAct01() {
    if (((NpcActionCtrl *)(&actionCtrl))->requestStand(1, data_020c6cc8)) {
        emotionTimer = 0x46;
        return TRUE;
    }
    return FALSE;
}

void SickVillager::mainAct01() {
    switch (emotionTimer) {
    case 0x45:
        ((NpcActionCtrl *)(&actionCtrl))->requestEmotion(1, 7, data_020c6cc8);
        break;
    case 1:
        ((NpcActionCtrl *)(&actionCtrl))->requestEmotion(1, 0, data_020c6cc8);
        walkTimer = Random_GlobalBelow(0x14) + 0x14;
        break;
    case 0:
        if (changeAct(0)) {
            return;
        }
        break;
    }
    if (emotionTimer != 0) {
        emotionTimer--;
    }
}

BOOL SickVillager::setupAct02() {
    if (act == 1) {
        ((NpcActionCtrl *)(&actionCtrl))->requestEmotion(2, 0, data_020c6cc8);
    }
    return TRUE;
}

void SickVillager::mainAct02() {}

BOOL SickVillager::setupAct03() {
    BOOL r;
    void *o = PlayerActor_GetActor(4);
    if (o != 0) {
        ((NpcTalkCtrl *)(&talkCtrl))->requestTurnAndTalk(0, ((NpcActor *)(this))->getAngleTo((NpcActor *)(o)), 0);
        r = TRUE;
    } else {
        r = FALSE;
    }
    return r;
}

void SickVillager::mainAct03() {
    changeAct(4);
}

BOOL SickVillager::setupAct04() { return TRUE; }

void SickVillager::mainAct04() {
    TalkWindowState *o = talk.window;
    if (o != 0) {
        if (o->state == 0) {
            TalkRequest_SetTargetDone(this);
        }
    }
}

BOOL SickVillager::setupAct05() {
    talk.window->openMode = 1;
    return TRUE;
}

void SickVillager::mainAct05() {
    TalkWindowState *m = talk.window;
    if (m->state == 5) {
        if (MenuCtrl_OpenPocketSelect(MenuCtrl_BuildPocketMask(SickVillager_IsMedicine), 0xd) != 0) {
            changeAct(6);
        }
    }
}

BOOL SickVillager::setupAct06() { return TRUE; }

void SickVillager::mainAct06() {}

BOOL SickVillager::setupAct07() { return TRUE; }

void SickVillager::mainAct07() {
    changeAct(4);
}

void SickVillager::onTalkMelodyPlayed() { talkMelodyPlayed = 1; }

BOOL SickVillager::canPlayTalkMelody() {
    if (talkMelodyPlayed == 0) {
        return TRUE;
    }
    return FALSE;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_0221a564) {
    HOST_OVERLAY_VAR(data_ov004_02250938),
    HOST_OVERLAY_VAR(data_ov004_02250940),
    HOST_OVERLAY_VAR(data_ov004_0225095c),
    HOST_OVERLAY_VAR(data_ov004_02250948),
    HOST_OVERLAY_VAR(data_ov004_02250944),
    HOST_OVERLAY_VAR(data_ov004_02250954),
    HOST_OVERLAY_VAR(data_ov004_02250958),
    HOST_OVERLAY_VAR(sSickVillagerProfile),
    HOST_OVERLAY_VAR(sSickVillager),
    HOST_OVERLAY_VAR(data_ov004_02250984),
    HOST_OVERLAY_VARS_END
};
