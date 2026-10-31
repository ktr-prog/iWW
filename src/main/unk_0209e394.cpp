#include "types.h"
#include "Unk_020d8c7c.h"
#include "talk/TalkWindowState.h"
#include "save/SaveRecord4.h"
#include "talk/MsgRequest.h"
#include "talk/TalkMsgRequest.h"
#include "sys/ProcProfile.h"
#include "net/CommManager.h"
#include "player/PlayerData.h"
#include "player/PlayerInventory.h"
#include "talk/ChoiceList.h"
#include "gfx/ScreenTransition.h"
#include "proto/main/unk_020b4828.h"
#include "proto/main/unk_02000b7c.h"
#include "proto/main/unk_020411dc.h"
#include "proto/main/unk_02038474.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02065e88.h"
#include "proto/main/unk_020720f8.h"
#include "proto/main/unk_02097110.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_0209c37c.h"
#include "proto/main/unk_0209e394.h"
#include "proto/main/unk_0209eb94.h"
#include "proto/main/unk_020a427c.h"


class SaveMenu;

class SaveMenuTalk : public TalkMsgRequest {
public:
    SaveMenuTalk();
    virtual ~SaveMenuTalk();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);

    void setOwner(SaveMenu *owner);

    /* 0x44 */ SaveMenu *ownerMenu;
    /* 0x48 */ u16 unk_48;
};

class SaveMenu : public GameProc {
public:
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();

    void updateSaveB();
    void enterSaveB();
    void updateSaveA();
    void enterSaveA();
    void updateQuitting();
    void enterQuitting();
    void updateTalking();
    void enterTalking();
    void updateOpenTalk();
    void enterOpenTalk();
    void updateIdle();
    void enterIdle();
    void setState(s32 state);

    /* 0x50 */ s32 saveMenuState;
    /* 0x54 */ SaveMenuTalk talk;
};

typedef void (SaveMenu::*Unk_020e23fc_Fn)();
struct SaveMenuStateEntry {
    Unk_020e23fc_Fn enter;
    Unk_020e23fc_Fn update;
};


ProcProfile sSaveMenuProfile = {(void *(*)())SaveMenu_Create, 0xd5, 0xd0};

extern const s32 sSaveMenuDebugDonationLevels[22];
const s32 sSaveMenuDebugDonationLevels[22] = {0, 10000, 50000, 100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000, 1100000, 1200000, 1300000, 1400000, 1500000, 1600000, 3200000, 6400000, 9999999};

SaveMenuStateEntry sSaveMenuStates[6] = {
    {&SaveMenu::enterIdle, &SaveMenu::updateIdle},
    {&SaveMenu::enterOpenTalk, &SaveMenu::updateOpenTalk},
    {&SaveMenu::enterTalking, &SaveMenu::updateTalking},
    {&SaveMenu::enterQuitting, &SaveMenu::updateQuitting},
    {&SaveMenu::enterSaveA, &SaveMenu::updateSaveA},
    {&SaveMenu::enterSaveB, &SaveMenu::updateSaveB},
};

extern u8 gTalkMsgIndexEnd[];
extern void *gCommManager;
extern u16 gPad[];


extern "C" {
void TalkRequest_FinishSaveMenu();
s32 TalkRequest_IsSaveMenuRunning();
s32 Scene_GetCurrent();
s32 TalkRequestFlags_IsResetti();
s32 TalkRequestFlags_IsSceneHold();
s32 TalkRequest_IsActive();
s32 TalkRequest_AddSaveMenu();
void Clock_GetDateTime(void *p);
s32 DateTime_Compare(void *a, void *b, s32 c);
void DateTime_AddDays(void *a, s32 b);
void Clock_GetDate(void *p);
void MI_CpuCopy8(void *src, void *dst, s32 n);
}

static inline BOOL Unk_0209e7b4_Is2(u8 v) {
    if (v == 2) {
        return TRUE;
    }
    return FALSE;
}



extern "C" void SaveData_ConstructDateRecord() {}

extern "C" void SaveData_DestructDateRecord() {}

void SaveRecord4::resetDate() {
    unk_00 = 1;
    unk_01 = 1;
    unk_02 = 0;
    unk_03 = 0;
}

void SaveRecord4::setDateToday(void *src) {
    u8 buf[8];
    if (src == 0) {
        Clock_GetDate(buf);
        src = buf;
    }
    MI_CpuCopy8(src, this, 4);
    unk_03 = 1;
}

void SaveRecord4::expireDate() {
    if (isDateActive() != 0) {
        u32 w[4];
        w[0] = 0;
        w[1] = 0;
        w[2] = 0;
        w[3] = 0;
        Clock_GetDateTime(w);
        ((u8 *)w)[0xd] = unk_02;
        ((u8 *)w)[0xc] = unk_01;
        ((u8 *)w)[0xb] = unk_00;
        ((u8 *)w)[0xa] = 0;
        if (DateTime_Compare(&w[2], w, 0x3c) != 1) {
            ((u8 *)w)[0xa] = 6;
            DateTime_AddDays(&w[2], 1);
            if (DateTime_Compare(&w[2], w, 0x3c) != 1) {
                unk_03 = 0;
            }
        } else {
            unk_03 = 0;
        }
    }
}

BOOL SaveRecord4::isDateActive() {
    if (unk_03 != 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" SaveMenu *SaveMenu_Create() {
    SaveMenu *p = new SaveMenu;
    return p;
}

BOOL SaveMenu::onCreate() {
    talk.setOwner(this);
    return TRUE;
}

BOOL SaveMenu::onDelete() {
    return TRUE;
}

BOOL SaveMenu::onExecute() {
    s16 *p;
    s32 t;
    PlayerData *r6;
    s32 r4;

    if (*DebugVar_GetPtr(0, 0x4b) != 0) {
        PlayerData *pd = PlayerData_GetCurrent();
        if (pd != 0) {
            PlayerBank *bank = pd->getBankAccount();
            switch (*DebugVar_GetPtr(0, 0x4b)) {
            case 0:
                break;
            case 1:
                PlayerBank_SetBalance(bank, 1000000);
                break;
            case 2:
                PlayerBank_SetBalance(bank, 10000000);
                break;
            case 3:
                PlayerBank_SetBalance(bank, 100000000);
                break;
            case 4:
                PlayerBank_SetBalance(bank, 500000000);
                break;
            case 5:
                PlayerBank_SetBalance(bank, 999999999);
                break;
            }
        }
    }
    if (*DebugVar_GetPtr(0, 0x4c) != 0) {
        PlayerData *pd = PlayerData_GetCurrent();
        if (pd != 0) {
            pd->getBankAccount();
            if (*DebugVar_GetPtr(0, 0x4c) != 0) {
                t = *DebugVar_GetPtr(0, 0x4c);
                if (t < 1) {
                    t = 1;
                } else if (t > 0x15) {
                    t = 0x15;
                }
                s32 c = Donation_GetTotal();
                s32 v = sSaveMenuDebugDonationLevels[t];
                if (v > c) {
                    Donation_SetTotal(v - 100);
                }
            }
        }
    }
    if (*DebugVar_GetPtr(0, 0x48) != 0) {
        r6 = PlayerData_GetCurrent();
        r4 = ((PlayerInventory *)(r6->getInventory()))->getTotalBells(1);
        r4 += *DebugVar_GetPtr(0, 0x48);
        if (r4 < 0) {
            r4 = 0;
        } else if (r4 > 0x1869f) {
            r4 = 0x1869f;
        }
        PlayerInventory_SetWallet((PlayerInventory *)r6->getInventory(), r4, 1);
        *DebugVar_GetPtr(0, 0x48) = 0;
    }
    if (sSaveMenuStates[saveMenuState].update != 0) {
        (this->*sSaveMenuStates[saveMenuState].update)();
    }
    return TRUE;
}

void SaveMenu::setState(s32 state) {
    if (sSaveMenuStates[state].enter != 0) {
        (this->*sSaveMenuStates[state].enter)();
    }
    saveMenuState = state;
}

void SaveMenu::enterIdle() {}

void SaveMenu::updateIdle() {
    if ((gPad[1] & 8) != 0) {
        if (Scene_GetCurrent() != 0x2d) {
            if (TalkRequestFlags_IsResetti() == 0) {
                if (TalkRequestFlags_IsSceneHold() == 0) {
                    if (Unk_0209e7b4_Is2(gScreenTransition.state) != 0) {
                        if (TalkRequest_IsActive() == 0) {
                            void *g = gCommManager;
                            if (((CommManager *)(g))->isOnline() != 0 && ((CommManager *)(g))->isMyAid(0) == 0) {
                                ChatQuickMsg_PostWantToSave();
                            } else if (TalkRequest_AddSaveMenu() != 0) {
                                setState(1);
                            }
                        }
                    }
                }
            }
        }
    }
}

void SaveMenu::enterOpenTalk() {}

void SaveMenu::updateOpenTalk() {
    if (TalkRequest_IsSaveMenuRunning() != 0) {
        TalkWindowState *o = TalkWindow_Get(0);
        SaveMenuTalk *p = &talk;
        p->resetMsg();
        if (GameStart_IsNewTown() != 0 || GameStart_IsNewResident() != 0) {
            ((MsgRequest *)(&talk))->setFileName((const char *)((u8 *)"sp_etc_sequence4"));
            talk.msgIndex = 4;
        } else if (((CommManager *)(gCommManager))->isOnline() != 0) {
            ((MsgRequest *)(&talk))->setFileName((const char *)((u8 *)"sp_etc_sequence2"));
            talk.msgIndex = 4;
        } else {
            ((MsgRequest *)(&talk))->setFileName((const char *)((u8 *)"sp_etc_sequence2"));
            talk.msgIndex = 0;
        }
        (o)->attachRequest(&talk);
        o->nextState = 1;
        setState(2);
    } else {
        setState(0);
    }
}

void SaveMenu::enterTalking() {}

void SaveMenu::updateTalking() {
    TalkWindowState *o = TalkWindow_Get(0);
    if (o->state == 0) {
        o->detachRequest();
        TalkRequest_FinishSaveMenu();
        setState(0);
    }
}

void SaveMenu::enterQuitting() {}

void SaveMenu::updateQuitting() {
    TalkWindowState *o = TalkWindow_Get(0);
    if (o->state == 0) {
        o->detachRequest();
        SceneWarp_RequestFade(Scene_GetWarpRequest(), 0x2e, 2, 3);
        if (((CommManager *)(gCommManager))->isOnline() != 0) {
            Scene_SavePlayerPos(Scene_GetWarpRequest(), 0);
            SaveManager_RequestAct1A();
        } else {
            SaveManager_RequestAct01();
        }
    }
}

void SaveMenu::enterSaveA() {
    talk.unk_48 = 200;
    Comm_RequestSync(2);
}

void SaveMenu::updateSaveA() {
    TalkWindowState *o = (TalkWindowState *)talk.window;
    s32 r = Comm_GetSyncState();
    if (r == 5 || r == 6) {
        o->hideBusyIcon();
        o->unlockAdvance();
        if (r == 5) {
            NetSession_SetMemberSyncReply(0, 6);
            NetSession_SetActiveSyncKind(NetSession_GetSyncKind());
            o->setNextMessage(gTalkMsgIndexEnd, 0);
            SaveManager_SetEndSessionSave(0);
            setState(3);
        } else {
            u8 b = 5;
            o->setNextMessage(&b, (u8 *)"sp_etc_sequence2");
            setState(2);
        }
        Comm_ClearSyncState();
    }
}

void SaveMenu::enterSaveB() {
    talk.unk_48 = 200;
    Comm_RequestSync(3);
}


void SaveMenu::updateSaveB() {
    TalkWindowState *o = (TalkWindowState *)talk.window;
    s32 r = Comm_GetSyncState();
    if (r == 5 || r == 6) {
        o->hideBusyIcon();
        o->unlockAdvance();
        if (r == 5) {
            NetSession_SetMemberSyncReply(0, 6);
            NetSession_SetActiveSyncKind(NetSession_GetSyncKind());
            o->setNextMessage(gTalkMsgIndexEnd, 0);
            SaveManager_SetEndSessionSave(1);
            setState(3);
        } else {
            u8 b = 5;
            o->setNextMessage(&b, (u8 *)"sp_etc_sequence2");
            setState(2);
        }
        Comm_ClearSyncState();
    }
}

SaveMenuTalk::SaveMenuTalk() {}

SaveMenuTalk::~SaveMenuTalk() {}

void SaveMenuTalk::setOwner(SaveMenu *owner) {
    ownerMenu = owner;
}

void SaveMenuTalk::onMessageEnd(u32) {
    if (msgIndex == 0) {
        TalkWindowState *o = (TalkWindowState *)window;
        void *h = o->getChoiceList();
        ((ChoiceList *)(h))->reset(2, 1);
        u8 buf[4];
        buf[0] = 0xc;
        buf[1] = gTalkMsgIndexEnd[0];
        ((ChoiceList *)(h))->setEntry(0, (const u8 *)(buf), 1, (const u8 *)(&buf[1]), (const char *)(0), 2);
        buf[2] = 0xd;
        buf[3] = gTalkMsgIndexEnd[0];
        ((ChoiceList *)(h))->setEntry(1, (const u8 *)(&buf[2]), 1, (const u8 *)(&buf[3]), (const char *)(0), 0);
        ((ChoiceList *)(h))->loadTexts();
        o->openChoices(1);
    }
}


void SaveMenuTalk::onChoice(u32) {
    TalkWindowState *o = (TalkWindowState *)window;
    s32 r = ((ChoiceList *)(o->getChoiceList()))->getResult();
    switch (msgIndex) {
    case 4:
        switch (r) {
        case 0:
            o->lockAdvance();
            (o)->showBusyIcon(1);
            ownerMenu->setState(4);
            break;
        case 1: {
            u8 b = 8;
            o->setNextMessage(&b, (u8 *)"sp_etc_sequence2");
            break;
        }
        }
        break;
    case 8:
        switch (r) {
        case 0:
            o->lockAdvance();
            (o)->showBusyIcon(1);
            ownerMenu->setState(5);
            break;
        case 1:
            o->setNextMessage(gTalkMsgIndexEnd, 0);
            break;
        }
        break;
    case 0:
        if (r == 0) {
            o->setNextMessage(gTalkMsgIndexEnd, 0);
            ownerMenu->setState(3);
        }
        break;
    }
}

