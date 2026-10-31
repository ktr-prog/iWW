#include "uptr.h"
#include "host_labels.h"
#include "proto/main/unk_020b4828.h"
#include "types.h"
#include "Unk_020d8c7c.h"
#include "gfx/DebugColor.h"
#include "actor/ActorProfile.h"
#include "gfx/VecFx32.h"
#include "game/Unk_ov004_022146ec_Bits.h"
#include "net/CommManager.h"
#include "talk/TalkWindowState.h"
#include "talk/MsgString9B.h"
#include "item/ItemName.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/MsgRequest.h"
#include "talk/TalkMsgRequest.h"
#include "room/MuseumExhibitInfo.h"
#include "game/TouchPickSphere.h"
#include "game/TouchPicker.h"
#include "save/MuseumData.h"
#include "talk/ChoiceList.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/itcm/unk_01ffcfc0.h"
#include "proto/main/unk_02094810.h"
#include "proto/ov004/unk_ov004_02213b90.h"

extern "C" {
extern u8 gTalkMsgIndexEnd;
extern char gTalkMsgIndexNone[];
extern u8 gVec3Zero[];
extern s16 data_02135f44[];
extern CommManager *gCommManager;
#define data_021ed0a0 HOST_LABEL(MuseumData *, data_021ed0a0)

s32 TalkRequest_SetTargetDone(void *self);
s32 TalkRequest_AddPlayerTalk6(void *self, s32 a);
s32 Vec_DistXZ(VecFx32 *a, VecFx32 *b);
s32 Math_AngleDiffAbs(s32 a, s32 b);
s32 Scene_GetCurrent(void);
}

typedef void (MuseumExhibitInfo::*Unk_ov004_02213ea8_Fn)();
typedef BOOL (MuseumExhibitInfo::*Unk_ov004_02213f34_Fn)();




extern "C" DebugColor data_ov004_022502f4(0x1f, 0x14, 0x14, 0x1f);
extern "C" DebugColor data_ov004_022502e4(0x14, 0x14, 0x1f, 0x1f);
extern "C" DebugColor data_ov004_022502ec(0x1f, 0x1f, 0x14, 0x1f);
extern "C" DebugColor data_ov004_022502dc(0x14, 0x1f, 0x14, 0x1f);
extern "C" DebugColor data_ov004_022502d0(0x14, 0x1f, 0x1f, 0x1f);
extern "C" DebugColor data_ov004_022502e0(0x14, 0x18, 0x18, 0x1f);
extern "C" ActorProfile sMuseumExhibitInfoProfile = { (void *(*)())MuseumExhibitInfo_Create, 0x19, 0x1e, 0, 0xc8000, 0x12c000, 0x258000 };
extern "C" {
s16 sMuseumExhibitSpawnMsg = -1;
char sMuseumExhibitMsgFile[] = "obj_etc_museum";
u8 sMuseumExhibitAutoTalkActive;
u8 sMuseumExhibitInfoCount;
u32 sMuseumExhibitSpawnKind;
u8 *sMuseumExhibitSpawnList;
u32 sMuseumExhibitSpawnCount;
u32 sMuseumExhibitSpawnFacingArc;
MuseumExhibitInfo *sMuseumExhibitInfos[0x20];
}

extern "C" void *MuseumExhibitInfo_SpawnAutoTalk() {
    if (sMuseumExhibitAutoTalkActive == 0) {
        sMuseumExhibitSpawnKind = 4;
        sMuseumExhibitSpawnMsg = 0;
        sMuseumExhibitSpawnList = 0;
        sMuseumExhibitSpawnCount = 0;
        sMuseumExhibitSpawnFacingArc = 0;
        return Actor::spawn(0x19, 0, gVec3Zero, 0, 0);
    }
    return 0;
}

extern "C" void MuseumExhibitInfo_Spawn(s32 a, void *b, s32 c, s32 d, s16 e, u8 *f, s32 g) {
    u16 loc[3];
    sMuseumExhibitSpawnKind = a;
    sMuseumExhibitSpawnMsg = e;
    sMuseumExhibitSpawnList = f;
    sMuseumExhibitSpawnCount = g;
    sMuseumExhibitSpawnFacingArc = d;
    loc[0] = 0;
    loc[1] = c;
    loc[2] = 0;
    Actor::spawn(0x19, 0, b, loc, 0);
}

extern "C" void *MuseumExhibitInfo_GetByIndex(s32 i) {
    if (i >= 0 && (u32)i < 0x20) {
        return sMuseumExhibitInfos[i];
    }
    return 0;
}

void MuseumExhibitInfo::mainAct03() {
    if (window) {
        if (window->state) {
            changeAct(2);
        }
    }
}

BOOL MuseumExhibitInfo::setupAct03() {
    u16 id[2];
    Character::attachTalkRequest(this);
    setFileName(sMuseumExhibitMsgFile);
    id[1] = 0x12e4;
    if (data_021ed0a0.getDonationState(&id[1]) <= 1) {
        MsgString9B obj;
        if (data_021ed0a0.getDonorName(&obj, &id[1])) {
            msgIndex = 3;
            window->setSlot(0, &obj);
        }
    } else {
        msgIndex = 4;
    }
    window->nextState = 1;
    talkCount++;
    return TRUE;
}

void MuseumExhibitInfo::mainAct02() {
    if (window) {
        if (window->state == 0) {
            Character::detachTalkRequest(this);
            TalkRequest_SetTargetDone(this);
        }
    }
}

void MuseumExhibitInfo::mainAct01() {
    if (window) {
        if (window->state) {
            changeAct(2);
        }
    }
}

BOOL MuseumExhibitInfo::setupAct01() {
    struct { u16 pad[3]; u16 w; u16 sel; } l;
    u32 i = 0;
    cursor = i;
    for (; i < itemCount; i++) {
        l.w = items[i];
        if (data_021ed0a0.isDonated(&l.w)) {
            cursor = i;
            break;
        }
    }
    l.sel = items[cursor];
    Character::attachTalkRequest(this);
    TalkMsgRequest &s = *this;
    s.setFileName(sMuseumExhibitMsgFile);
    if (isAnyDonated() == 0) {
        msgIndex = 0;
    } else if (kind == 3) {
        if (itemCount == 1) {
            msgIndex = 5;
        } else {
            msgIndex = infoMsgIndex;
        }
    } else if (kind <= 1) {
        u32 n = countDonatedFromCursor();
        if (n > 3) n = 3;
        msgIndex = (n - 1) % 3 + 5;
    } else {
        if (data_021ed0a0.getDonationState(&l.sel) != 2) {
            msgIndex = 1;
        } else {
            msgIndex = 2;
        }
    }
    window->nextState = 1;
    return TRUE;
}

void MuseumExhibitInfo::mainAct00() {
    if (isAutoTalkKind()) {
        if (talkCount == 0) {
            TalkRequest_AddPlayerTalk6(this, 0);
        } else {
            ProcBase_RequestDelete(this);
        }
    }
}

void MuseumExhibitInfo::execAct() {
    static Unk_ov004_02213ea8_Fn tbl[4] = {
        &MuseumExhibitInfo::mainAct00,
        &MuseumExhibitInfo::mainAct01,
        &MuseumExhibitInfo::mainAct02,
        &MuseumExhibitInfo::mainAct03,
    };
    if (act < 4) {
        (this->*tbl[act])();
    }
}

BOOL MuseumExhibitInfo::changeAct(s32 idx) {
    static Unk_ov004_02213f34_Fn tbl[4] = {
        &MuseumExhibitInfo::setupAct00,
        &MuseumExhibitInfo::setupAct01,
        &MuseumExhibitInfo::setupAct02,
        &MuseumExhibitInfo::setupAct03,
    };
    if (idx < 4) {
        if ((this->*tbl[idx])()) {
            act = idx;
            return TRUE;
        }
    }
    return FALSE;
}

void MuseumExhibitInfo::onChoice(u32) {
    if (isAutoTalkKind() == 0) {
        u8 a0, a1, a2, a3;
        u16 sel;
        if (window->getChoiceList()->getResult() == 0) {
            sel = items[cursor];
            if (kind <= 1) {
                u32 n = countDonatedFromCursor();
                if (n > 3) n = 3;
                a0 = (n - 1) % 3 + 5;
                window->setNextMessage(&a0, 0);
            } else if (data_021ed0a0.getDonationState(&sel) != 2) {
                a1 = 1;
                window->setNextMessage(&a1, 0);
            } else {
                a2 = 2;
                window->setNextMessage(&a2, 0);
            }
        } else {
            a3 = gTalkMsgIndexEnd;
            window->setNextMessage(&a3, 0);
        }
    }
}

void MuseumExhibitInfo::onMessageEnd(u32) {
    u8 b[7];
    if (isAutoTalkKind() == 0) {
        if (kind == 3) {
            if (msgIndex != 5) {
                if (isAllDonated()) {
                    u32 e = msgIndex;
                    if (infoMsgIndex == e) {
                        b[0] = e + 1;
                        window->setNextMessage(&b[0], 0);
                    } else {
                        b[1] = gTalkMsgIndexEnd;
                        window->setNextMessage(&b[1], 0);
                    }
                } else {
                    b[2] = gTalkMsgIndexEnd;
                    window->setNextMessage(&b[2], 0);
                }
            } else {
                b[3] = gTalkMsgIndexEnd;
                window->setNextMessage(&b[3], 0);
            }
        } else if (countDonatedFromCursor() != 0) {
            ChoiceList *o = window->getChoiceList();
            if (o) {
                o->reset(2, 1);
                b[4] = 0xe5;
                o->setEntry(0, &b[4], 0, (const u8 *)gTalkMsgIndexNone, 0, 0);
                b[5] = 0xe6;
                o->setEntry(1, &b[5], 0, (const u8 *)gTalkMsgIndexNone, 0, 0);
                o->loadTexts();
                window->openChoices(1);
            }
        } else {
            b[6] = gTalkMsgIndexEnd;
            window->setNextMessage(&b[6], 0);
        }
    }
}

void MuseumExhibitInfo::onMessageStart(u32) {
    if (isAutoTalkKind() == 0) {
        u16 w1, w2;
        if (kind <= 1) {
            u32 n = 0;
            switch (msgIndex) {
            case 5: n = 1; break;
            case 6: n = 2; break;
            case 7: n = 3; break;
            }
            u32 i;
            for (i = 0; i < n; i++) {
                w1 = items[cursor];
                ItemName o(&w1);
                window->setNamedSlot(i, &o, 7);
                advanceToNextDonated();
            }
        } else {
            u32 idx = cursor;
            if (idx < itemCount) {
                w2 = items[idx];
                MsgString9B e;
                data_021ed0a0.getDonorName(&e, &w2);
                window->setSlot(0, &e);
                ItemName o2(&w2);
                window->setNamedSlot(0, &o2, 7);
                if (kind != 3) {
                    advanceToNextDonated();
                }
            }
        }
    }
}

void MuseumExhibitInfo::onInteractionEvent(u32 a, u8 b) {
    switch (a) {
    case 1:
        changeAct(3);
        break;
    case 0:
        changeAct(1);
        break;
    case 8:
        changeAct(0);
        break;
    }
}

BOOL MuseumExhibitInfo::acceptsInteraction(void *a0) {
    Actor *a = (Actor *)a0;
    if (a) {
        if (Vec_DistXZ(&a->position, &position) < 0x2333) {
            if (Math_AngleDiffAbs((s16)(rotY + 0x8000), a->rotY) < facingArc) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

BOOL MuseumExhibitInfo::unregisterSelf() {
    if (isAutoTalkKind() == 0) {
        u32 idx = index;
        if (idx < 0x20) {
            sMuseumExhibitInfos[idx] = 0;
            sMuseumExhibitInfoCount--;
            index = 0xff;
            return TRUE;
        }
    } else {
        sMuseumExhibitAutoTalkActive = 0;
    }
    return FALSE;
}

BOOL MuseumExhibitInfo::registerSelf() {
    if (isAutoTalkKind()) {
        index = 0xff;
        sMuseumExhibitAutoTalkActive = 1;
        return TRUE;
    }
    index = sMuseumExhibitInfoCount;
    if (index < 0x20) {
        sMuseumExhibitInfos[index] = this;
        sMuseumExhibitInfoCount++;
        return TRUE;
    }
    return FALSE;
}

BOOL MuseumExhibitInfo::setupAct02() {
    return TRUE;
}

BOOL MuseumExhibitInfo::setupAct00() {
    return TRUE;
}

void MuseumExhibitInfo::advanceToNextDonated() {
    u32 i = cursor + 1;
    for (; i < itemCount; i++) {
        u16 w = items[i];
        if (data_021ed0a0.isDonated(&w)) {
            cursor = i;
            return;
        }
    }
    cursor = itemCount;
}

u32 MuseumExhibitInfo::countDonatedFromCursor() {
    u32 cnt = 0;
    u32 i = cursor;
    for (; i < itemCount; i++) {
        u16 w = items[i];
        if (data_021ed0a0.isDonated(&w)) {
            cnt++;
        }
    }
    return cnt;
}

BOOL MuseumExhibitInfo::isAllDonated() {
    u32 i;
    for (i = 0; i < itemCount; i++) {
        u16 w = items[i];
        if (data_021ed0a0.isDonated(&w) == 0) {
            return FALSE;
        }
    }
    return TRUE;
}

BOOL MuseumExhibitInfo::isAnyDonated() {
    u32 i;
    for (i = 0; i < itemCount; i++) {
        u16 w = items[i];
        if (data_021ed0a0.isDonated(&w)) {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL MuseumExhibitInfo::isAutoTalkKind() {
    if (kind == 4) {
        return TRUE;
    }
    return FALSE;
}

extern "C" void MuseumExhibitInfo_ClearRegistry(void) {
    if (sMuseumExhibitInfoCount == 0) {
        u32 i;
        for (i = 0; i < 0x20; i++) {
            sMuseumExhibitInfos[i] = 0;
        }
    }
}

BOOL MuseumExhibitInfo::onDelete() {
    unregisterSelf();
    if (items != 0) {
        Mem_Free(items);
    }
    return TRUE;
}

BOOL MuseumExhibitInfo::onDraw() {
    return TRUE;
}

BOOL MuseumExhibitInfo::onExecute() {
    execAct();
    if (isAutoTalkKind() == 0) {
        Scene_GetTouchPicker()->addSphere(&touchSphere, &position, 0xc00, 0xe, index);
    }
    return TRUE;
}

BOOL MuseumExhibitInfo::onCreate() {
    Unk_ov004_022146ec_Bits l;
    VecFx32 v;
    VecFx32 out;
    BOOL r;
    MuseumExhibitInfo_ClearRegistry();
    kind = sMuseumExhibitSpawnKind;
    infoMsgIndex = sMuseumExhibitSpawnMsg;
    itemCount = sMuseumExhibitSpawnCount;
    facingArc = sMuseumExhibitSpawnFacingArc;
    if (registerSelf() != 0) {
        if (isAutoTalkKind() != 0) {
            Actor *o = (Actor *)PlayerActor_GetCharacter(4);
            if (o != 0) {
                s32 idx = ((u16)o->rotY >> 4) * 2;
                v.x = data_02135f44[idx];
                v.y = 0;
                v.z = data_02135f44[idx + 1];
                Vec_Add(&out, &o->position, &v);
                position.x = out.x;
                position.y = out.y;
                position.z = out.z;
            }
        }
        l.a = (u16)gCommManager->myAid;
        *(u16 *)&l = (*(u16 *)&l & ~0xfc) | ((Scene_GetCurrent() & 0x3f) << 2);
        l.c = index;
        Character::setCharId(*(u16 *)&l);
        changeAct(0);
        r = buildItemList();
    } else {
        r = FALSE;
    }
    return r;
}

MuseumExhibitInfo::~MuseumExhibitInfo() {
}

MuseumExhibitInfo::MuseumExhibitInfo() {
}

extern "C" MuseumExhibitInfo *MuseumExhibitInfo_Create(void) {
    return new MuseumExhibitInfo;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_02213b90) {
    HOST_OVERLAY_VAR(data_ov004_022502f4),
    HOST_OVERLAY_VAR(data_ov004_022502e4),
    HOST_OVERLAY_VAR(data_ov004_022502ec),
    HOST_OVERLAY_VAR(data_ov004_022502dc),
    HOST_OVERLAY_VAR(data_ov004_022502d0),
    HOST_OVERLAY_VAR(data_ov004_022502e0),
    HOST_OVERLAY_VAR(sMuseumExhibitInfoProfile),
    HOST_OVERLAY_VAR(sMuseumExhibitSpawnMsg),
    HOST_OVERLAY_VAR(sMuseumExhibitMsgFile),
    HOST_OVERLAY_VAR(sMuseumExhibitAutoTalkActive),
    HOST_OVERLAY_VAR(sMuseumExhibitInfoCount),
    HOST_OVERLAY_VAR(sMuseumExhibitSpawnKind),
    HOST_OVERLAY_VAR(sMuseumExhibitSpawnList),
    HOST_OVERLAY_VAR(sMuseumExhibitSpawnCount),
    HOST_OVERLAY_VAR(sMuseumExhibitSpawnFacingArc),
    HOST_OVERLAY_VAR(sMuseumExhibitInfos),
    HOST_OVERLAY_VARS_END
};
