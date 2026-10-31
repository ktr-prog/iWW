#include "types.h"
#include "host_labels.h"
#include "Unk_020d8c7c.h"
#include "talk/TalkStartMsg.h"
#include "talk/TalkWindowState.h"
#include "npc/NpcAnimCtrl.h"
#include "npc/NpcSpeechState.h"
#include "npc/NpcResHandle.h"
#include "npc/NpcObstacleProbe.h"
#include "npc/Unk_0201ad18.h"
#include "npc/NpcFootstepFx.h"
#include "npc/NpcActionCtrl.h"
#include "snd/SndSeEmitterKind1.h"
#include "npc/NpcTalkCtrl.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "gfx/ThreeLayerAnimModel.h"
#include "talk/TalkMsgRequest.h"
#include "talk/ActorTalkRequest.h"
#include "actor/NpcActor.h"
#include "actor/SpNpcActor.h"
#include "talk/ActorTalkRequest.h"
#include "talk/SpNpcTalkRequest.h"
#include "actor/ActorProfile.h"
#include "player/PlayerData.h"
#include "talk/ChoiceList.h"
#include "proto/main/unk_0203c23c.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/ov080/unk_ov080_022713c0.h"

class SpNpcTortimer;
class SpNpcTortimerTalk;

extern "C" {
BOOL TalkRequest_SetTargetDone(void *p);
void TalkRequestFlags_SetEventWarpBlock();
void ThreeLayerAnimModel_AssignJointsToLayer2(void *self, s32 a, s32 b);
extern u16 data_020c6cc8;
#define gSavePlayers HOST_LABEL(u8 (*)[], gSavePlayers)
}


struct TalkStartMsg;






class SpNpcTortimerTalk : public SpNpcTalkRequest {
public:
    SpNpcTortimerTalk();
    virtual ~SpNpcTortimerTalk();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);

    void attachOwner(SpNpcTortimer *owner);

    SpNpcTortimer *ownerNpc;
    s32 massageChairSlot;
};



class ActorTalkRequest;





class SpNpcTortimer : public SpNpcActor {
public:
    SpNpcTortimer() {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL onDelete();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual BOOL updateAct();
    virtual u8 *getTexturePath();
    virtual u8 *getModelPath();

    BOOL mainAct02();
    BOOL mainAct01();
    BOOL setupAct01();
    BOOL mainAct00();
    BOOL setupAct00();
    void changeAct(s32 state);

    s32 act;
    SpNpcTortimerTalk talk;
};

struct SpNpcTortimerActEntry {
    BOOL (SpNpcTortimer::*enter)();
    BOOL (SpNpcTortimer::*exit)();
};

SpNpcTortimerActEntry sSpNpcTortimerActTable[3] = {
    {&SpNpcTortimer::setupAct00, &SpNpcTortimer::mainAct00},
    {&SpNpcTortimer::setupAct01, &SpNpcTortimer::mainAct01},
    {NULL, &SpNpcTortimer::mainAct02},
};



extern "C" {
u8 sSpNpcTortimerTexturePath[27] = "npc_sp/model/ttl_tex.nsbtx";
u8 sSpNpcTortimerModelPath[23] = "npc_sp/model/ttl.nsbmd";
ActorProfile sSpNpcTortimerProfile = {(void *(*)())SpNpcTortimer_Create, 0x56, 0x5d, 2, 0x5000, 0x5000, 0x3e800};
}



struct SpNpcTortimerMsgEndLocal {
    u8 msgIndices[2];
    u16 items[8];
};

struct SpNpcTortimerChoiceLocal {
    u8 msgIndex;
    u8 pad_01;
    u16 item;
};

extern "C" SpNpcTortimer *SpNpcTortimer_Create() {
    return new SpNpcTortimer();
}

BOOL SpNpcTortimer::preCreate() {
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    setTalkRequest((ActorTalkRequest *)&talk);
    talk.attachOwner(this);
    return TRUE;
}

BOOL SpNpcTortimer::onCreate() {
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    changeAct(0);
    animCtrl.playAnim((NpcActor *)(this), 0x140, 0, 0, 0x1000, 0, 1);
    ThreeLayerAnimModel_AssignJointsToLayer2(&model, 0xc, 0xe);
    collider.groups |= 2;
    if (PlayerData_GetCurrent()->testFlag(1) == 0) {
        TalkRequestFlags_SetEventWarpBlock();
    }
    return TRUE;
}

BOOL SpNpcTortimer::onDelete() {
    if (SpNpcActor::onDelete()) {
        return TRUE;
    }
    return FALSE;
}

u8 *SpNpcTortimer::getTexturePath() { return sSpNpcTortimerTexturePath; }

u8 *SpNpcTortimer::getModelPath() { return sSpNpcTortimerModelPath; }

BOOL SpNpcTortimer::updateAct() {
    BOOL result = FALSE;
    if (sSpNpcTortimerActTable[act].exit != NULL) {
        result = (this->*sSpNpcTortimerActTable[act].exit)();
    }
    return result;
}

void SpNpcTortimer::changeAct(s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcTortimerActTable[state].enter != NULL) {
        ok = (this->*sSpNpcTortimerActTable[state].enter)();
    }
    if (ok) {
        act = state;
    }
}

BOOL SpNpcTortimer::setupAct00() {
    actionCtrl.requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcTortimer::mainAct00() { return TRUE; }

BOOL SpNpcTortimer::setupAct01() {
    Character *p = talk.getTalkPlayer();
    u32 x = 0;
    if (p != NULL) {
        x = getAngleTo((NpcActor *)p);
    }
    talkCtrl.requestTurnAndTalk(0, x, 0);
    return TRUE;
}

BOOL SpNpcTortimer::mainAct01() {
    if (talkCtrl.isBusy() == 0) {
        TalkRequest_SetTargetDone(this);
        changeAct(2);
    }
    return TRUE;
}

BOOL SpNpcTortimer::mainAct02() { return TRUE; }

SpNpcTortimerTalk::SpNpcTortimerTalk() {}

SpNpcTortimerTalk::~SpNpcTortimerTalk() {}

void SpNpcTortimerTalk::attachOwner(SpNpcTortimer *owner) {
    resetMsg();
    ownerNpc = owner;
    massageChairSlot = -1;
}

void SpNpcTortimerTalk::start(TalkStartMsg *out) {
    PlayerData *g = PlayerData_GetCurrent();
    if (g->testFlag(1)) {
        out->msgKey = "sp_etc_sequence5_2";
        if (g->testFlag(0xd) == 0) {
            out->msgIndex = 0;
            g->setFlag(0xd);
        } else {
            out->msgIndex = Random_GlobalBelow(4) + 3;
        }
        g->setFlag(0xa);
    } else {
        if (massageChairSlot == -1) {
            u16 v = 0x37e0;
            massageChairSlot = Pocket_FindItem(&v);
            if (massageChairSlot >= 0) {
                out->msgKey = "sp_npc_turtle";
                out->msgIndex = 0;
                return;
            }
        }
        out->msgKey = "sp_npc_turtle7";
        if (g->testFlag(0x21) == 0 && Catalog_HasAllFish()) {
            out->msgIndex = 0;
            if (Pocket_FindEmpty() < 0) {
                out->msgIndex = 9;
            } else {
                s32 i;
                for (i = 0; i < 4; i++) {
                    PlayerData *p = (PlayerData *)PlayerData_GetResident(gSavePlayers, i);
                    if (p != NULL && p->isUsed() && p != g && p->testFlag(0x21)) {
                        out->msgIndex = 2;
                        break;
                    }
                }
            }
        } else if (g->testFlag(0x22) == 0 && Catalog_HasAllInsects()) {
            out->msgIndex = 3;
            if (Pocket_FindEmpty() < 0) {
                out->msgIndex = 0xa;
            } else {
                s32 i;
                for (i = 0; i < 4; i++) {
                    PlayerData *p = (PlayerData *)PlayerData_GetResident(gSavePlayers, i);
                    if (p != NULL && p->isUsed() && p != g && p->testFlag(0x22)) {
                        out->msgIndex = 5;
                        break;
                    }
                }
            }
        } else {
            out->msgIndex = Random_GlobalBelow(3) + 6;
        }
    }
}

void SpNpcTortimerTalk::onMessageEnd(u32) {
    SpNpcTortimerMsgEndLocal buf;
    u32 r = 0xff;
    if (massageChairSlot >= 0) {
        if (msgIndex == 1 || msgIndex == 4) {
            massageChairSlot = -2;
        }
        if (msgIndex == 2) {
            buf.items[0] = 0x1559;
            this->requestGiveItem(&buf.items[0], 0, 5, 0);
            buf.items[1] = 0x1559;
            Pocket_AddItem(&buf.items[1], 0);
            buf.msgIndices[0] = 4;
            window->setNextMessage(&buf.msgIndices[0], (u8 *)"sp_npc_turtle");
        }
    } else {
        PlayerData *g = PlayerData_GetCurrent();
        u8 *str;
        if (g->testFlag(1)) {
            str = (u8 *)"sp_etc_sequence5_2";
        } else {
            str = (u8 *)"sp_npc_turtle7";
            switch (msgIndex) {
            case 0:
            case 2:
                buf.items[2] = 0x1375;
                if (Pocket_AddItem(&buf.items[2], 0)) {
                    buf.items[3] = 0x1375;
                    this->requestGiveItem(&buf.items[3], 0, 5, 0);
                    g->setFlag(0x21);
                    buf.items[4] = 0x1375;
                    this->setItemNameSlot(&buf.items[4], 0, 7);
                    r = 1;
                }
                break;
            case 3:
            case 5:
                buf.items[5] = 0x1377;
                if (Pocket_AddItem(&buf.items[5], 0)) {
                    buf.items[6] = 0x1377;
                    this->requestGiveItem(&buf.items[6], 0, 5, 0);
                    g->setFlag(0x22);
                    buf.items[7] = 0x1377;
                    this->setItemNameSlot(&buf.items[7], 0, 7);
                    r = 4;
                }
                break;
            }
        }
        if (r != 0xff) {
            buf.msgIndices[1] = r;
            window->setNextMessage(&buf.msgIndices[1], str);
        }
    }
}

void SpNpcTortimerTalk::onChoice(u32) {
    SpNpcTortimerChoiceLocal buf;
    s32 t = getChoiceList()->getResult();
    PlayerData *g = PlayerData_GetCurrent();
    u8 r = 0xff;
    if (massageChairSlot >= 0) {
        u8 *const str = (u8 *)"sp_npc_turtle";
        if (msgIndex == 0 && t == 0) {
            if (massageChairSlot >= 0) {
                Pocket_RemoveItem(massageChairSlot);
                buf.item = 0x37e0;
                requestTakeItem(&buf.item, 0, 5, 0);
            }
            r = 2;
        }
        if (r != 0xff) {
            buf.msgIndex = r;
            window->setNextMessage(&buf.msgIndex, str);
        }
    } else {
        g->testFlag(1);
    }
}

BOOL SpNpcTortimer::acceptsInteraction(void *) {
    BOOL r = FALSE;
    if (talkCtrl.isBusy() == 0) {
        r = TRUE;
    }
    return r;
}

void SpNpcTortimer::onInteractionEvent(u32 a, u8 b) {
    switch (a) {
    case 0:
        talk.resetMsg();
        talk.setTalkPlayer(getPlayerActor(4));
        changeAct(1);
        break;
    case 8:
        changeAct(0);
        break;
    }
}


#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov080_022713c0) {
    HOST_OVERLAY_VAR(sSpNpcTortimerActTable),
    HOST_OVERLAY_VAR(sSpNpcTortimerTexturePath),
    HOST_OVERLAY_VAR(sSpNpcTortimerModelPath),
    HOST_OVERLAY_VAR(sSpNpcTortimerProfile),
    HOST_OVERLAY_VARS_END
};
