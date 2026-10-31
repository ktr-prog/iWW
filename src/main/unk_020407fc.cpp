#include "uptr.h"
#include "host_mem.h"
#include "host_labels.h"
#include "types.h"

#include "Unk_020d8c7c.h"
#include "talk/TalkMsgRequest.h"
#include "net/CommManager.h"
#include "talk/TalkWindowState.h"
#include "sys/ProcProfile.h"
#include "nitro/io_access.h"
#include "snd/BgmManager.h"
#include "gfx/ScreenTransition.h"
#include "town/ResettiVisitFlag.h"
#include "talk/MsgRequest.h"
#include "proto/autoload_2/unk_021104ac.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020411dc.h"
#include "proto/main/unk_0204cc1c.h"
#include "proto/main/unk_020407fc.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02065e88.h"
#include "proto/main/unk_0206d988.h"
#include "proto/main/unk_020850e0.h"
#include "proto/main/unk_020a427c.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/main/unk_020b4828.h"


class EventAnnouncer : public GameProc {
public:
    EventAnnouncer();
    virtual ~EventAnnouncer();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();

    /* 0x50 */ u32 unk_50;
    /* 0x54 */ TalkMsgRequest msgRequest;
};

struct ClockDateBytes { u8 b[4]; };

struct EventAnnounceState {
    EventAnnounceState() { announceState = 0; msgIndex = 0; isEnd = 0; }
    ~EventAnnounceState();
    u8 announceState;
    u8 isEnd;
    u8 busy;
    u8 dayChangePending;
    u8 msgIndex;
    u8 pad_05[3];
    s32 nextEvent;
};

struct Unk_02040974_Rtc { s32 a; s32 b; };
static inline s32 Unk_02040a84_Get(TalkWindowState *p)
{
    s32 v = p->state;
    return v;
}
static inline BOOL Unk_02040ad8_IsTwo(u8 v)
{
    return v == 2 ? TRUE : FALSE;
}

extern "C" {
void MI_CpuCopy8(void *, void *, u32);
void Clock_GetDate(void *);
s32 Date_DaysBetween(void *, void *);
void EventWeekSlots_UpdateWeek(void *, s32);
void Event_RefreshToday(s32);
void EventWeekSlots_ClearWeek(void *);
s32 Scene_GetCurrent(void);
void Clock_GetDateTime(void *);
s32 TalkRequestFlags_IsEventWarpStarted(void);
s32 TalkRequest_AddEventWarp(void);
s32 TalkRequestFlags_IsEventWarpReady(void);
s32 Event_GetStateAt(s32, void *, s32);
s32 Event_GetState(s32, void *, s32);
s32 TalkRequestFlags_IsSceneHold(void);
s32 TalkRequestFlags_ClearSceneHold(void);
s32 TalkRequestFlags_SetSceneHold(void);
s32 Scene_InTownUnk31(void);
void Town_RefreshEventsOffline(void);
void Town_UpdateDay(s32);
void MIi_CpuClear16(u16 v, void *dst, u32 size);
}

extern CommManager *gCommManager;
#define data_021ed170 HOST_LABEL(u8 (*)[], data_021ed170)
extern u8 gSaveData[];
extern BgmManager *data_021c1b3c;

static inline u8 Unk_02040cac_B2(u8 *p)
{
    return p[2];
}

s32 sEventAnnounceBusy;
ProcProfile sEventAnnouncerProfile = { (void *(*)())EventAnnouncer_Create, 0xd6, 0xd1 };
const char *sEventAnnounceMsgFiles[2] = { "obj_ev_start", "obj_ev_end" };
s32 sEventAnnounceWasOnline;
s32 sEventAnnounceBgmCode;
s32 sEventAnnouncePendingEvent = 99;
s32 sEventAnnounceActiveEvent = 99;
s32 sEventAnnounceCurEvent = 99;
extern const u8 sAnnouncedEventIds[12];
const u8 sAnnouncedEventIds[12] = {9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 0};
EventAnnounceState sEventAnnounceState;

static inline void Unk_02041104_Fill(u16 v, void *dst, u32 size) {
    volatile u16 t = v;
    MIi_CpuClear16(t, dst, size);
}

extern "C" void ScreenTransition_ShowCover() {
    volatile u16 *r;
    r = (volatile u16 *)0x400000c;
    IO_AND(r, ~3);
    IO_W(r, (IO_R(r) & 0x43) | 0x600);
    Unk_02041104_Fill(0, G2_GetBG2ScrPtr(), 0x800);
    Unk_02041104_Fill(0x1111, G2_GetBG2CharPtr(), 0x20);
    Unk_02041104_Fill(0x8000, (void *)HW_PLTT, 4);
    Gfx2d_ShowMainPlanes(4);
    r = (volatile u16 *)0x400100c;
    IO_AND(r, ~3);
    IO_W(r, (IO_R(r) & 0x43) | 0xe04);
    Unk_02041104_Fill(0, G2S_GetBG2ScrPtr(), 0x800);
    Unk_02041104_Fill(0x1111, G2S_GetBG2CharPtr(), 0x20);
    Unk_02041104_Fill(0x8000, (void *)(HW_PLTT + 0x400), 4);
    Gfx2d_ShowSubPlanes(4);
}

extern "C" EventAnnouncer *EventAnnouncer_Create() {
    return new EventAnnouncer();
}

EventAnnouncer::EventAnnouncer() {}

EventAnnouncer::~EventAnnouncer() {}

BOOL EventAnnouncer::onCreate()
{
    u8 *r5;
    Unk_02040974_Rtc t;
    u8 buf[8];
    s32 r;
    s32 v;
    if (EventAnnounce_IsBlockedScene()) {
        return FALSE;
    }
    r5 = gSaveData;
    if (gCommManager->isOnline() == 0 && Scene_GetCurrent() != 0xd) {
        if (sEventAnnounceWasOnline != 0) {
            u32 k;
            t.a = 0;
            t.b = 0;
            Clock_GetDateTime(&t);
            EventAnnounce_Reset();
            k = r5[0x15e29];
            MI_CpuCopy8(&t, buf, 8);
            r = Event_GetState(k, buf, 0);
            if (r != 0 && r != 3) {
                sEventAnnounceActiveEvent = k;
                sEventAnnouncePendingEvent = k;
                sEventAnnounceCurEvent = k;
            }
        }
        r5[0x15e29] = 99;
        sEventAnnounceWasOnline = 0;
        if (Scene_InTownUnk31() != 0 && sEventAnnounceState.dayChangePending == 0) {
            Town_RefreshEventsOffline();
        }
    } else {
        EventAnnounce_Reset();
        v = r5[0x15e29];
        sEventAnnounceActiveEvent = v;
        sEventAnnouncePendingEvent = v;
        sEventAnnounceCurEvent = v;
        sEventAnnounceWasOnline = 1;
    }
    switch (sEventAnnounceState.announceState) {
    case 0:
        break;
    case 1:
        EventAnnounce_Reset();
        break;
    case 2:
    case 3:
        break;
    default:
        if (Scene_InTownUnk31() == 0) {
            EventAnnounce_Reset();
        } else {
            TalkRequestFlags_SetSceneHold();
            sEventAnnounceState.announceState = 5;
            if (sEventAnnounceState.dayChangePending != 0) {
                Town_UpdateDay(0);
                sEventAnnounceState.dayChangePending = 0;
            }
            v = sEventAnnouncePendingEvent;
            if (v != 99) {
                sEventAnnounceActiveEvent = v;
            }
            HouseVisitor_ClearPresent();
        }
        break;
    }
    return TRUE;
}

BOOL EventAnnouncer::onExecute()
{
    EventAnnouncer *x = this;
    if (gCommManager->isOnline() == 0) {
        EventAnnounce_Update();
        switch (sEventAnnounceState.announceState) {
        case 0:
            EventAnnounce_RunIdle(x);
            break;
        case 1:
            EventAnnounce_RunWaitChimeStart(x);
            break;
        case 2:
            EventAnnounce_RunWaitChimeEnd(x);
            break;
        case 3:
            EventAnnounce_RunWarp(x);
            break;
        case 4:
            EventAnnounce_RunIdle(x);
            break;
        case 5:
            EventAnnounce_RunShowMessage(x);
            break;
        case 6:
            EventAnnounce_RunWaitMessageEnd(x);
            break;
        }
    }
    return TRUE;
}

BOOL EventAnnouncer::onDelete()
{
    if (EventAnnounce_IsBlockedScene()) {
        return TRUE;
    }
    if (TalkRequestFlags_IsSceneHold()) {
        TalkRequestFlags_ClearSceneHold();
        sEventAnnounceBusy = 0;
        sEventAnnounceState.announceState = 0;
        sEventAnnounceState.busy = 0;
    }
    switch (sEventAnnounceState.announceState) {
    case 0:
        if (sEventAnnounceCurEvent == 99) {
            EventAnnounce_Reset();
        }
        break;
    case 1:
        sEventAnnounceState.announceState = 2;
        break;
    }
    if (gCommManager->isOnline() == 0) {
        data_021ed170[9] = sEventAnnounceCurEvent;
    }
    return TRUE;
}

extern "C" void EventAnnounce_Reset(void)
{
    sEventAnnouncePendingEvent = 99;
    sEventAnnounceCurEvent = 99;
    sEventAnnounceActiveEvent = 99;
    sEventAnnounceState.announceState = 0;
    sEventAnnounceState.busy = 0;
    sEventAnnounceState.dayChangePending = 0;
}

extern "C" void EventAnnounce_Restart(void)
{
    EventAnnounce_Reset();
    if (gCommManager->isOnline() == 0) {
        EventAnnounce_CheckEvents();
    }
}

extern "C" BOOL EventAnnounce_CanCheck(void)
{
    if (!Unk_02040ad8_IsTwo(gScreenTransition.state)) {
        return FALSE;
    }
    if (Scene_GetCurrent() == 0x3f) {
        return FALSE;
    }
    if (Scene_GetCurrent() == 0x2c) {
        return FALSE;
    }
    if (Scene_GetCurrent() == 6) {
        return FALSE;
    }
    if (NetArea_IsUnsharedScene(Scene_GetCurrent()) != 0) {
        return FALSE;
    }
    if (gActorDefaultParent != 0 && gActorDefaultParent->profile != 6) {
        return FALSE;
    }
    return TRUE;
}

extern "C" void EventAnnounce_CheckEvents(void)
{
    s32 zero;
    Unk_02040974_Rtc t;
    u8 buf[8];
    u8 buf2[8];
    s32 i;
    t.a = 0;
    t.b = 0;
    Clock_GetDateTime(&t);
    if (sEventAnnouncePendingEvent == 99) {
        zero = 0;
        for (i = 0; i < 11; i++) {
            u32 k;
            s32 r;
            MI_CpuCopy8(&t, buf, 8);
            k = sAnnouncedEventIds[i];
            r = Event_GetStateAt(k, buf, 0);
            switch (r) {
            case 2:
                if (k == 0x13) {
                    sEventAnnouncePendingEvent = k;
                    sEventAnnounceCurEvent = k;
                } else if (Unk_02040cac_B2((u8 *)&t) < 6) {
                    sEventAnnounceCurEvent = k;
                } else {
                    EventAnnounce_Request(k, k, zero);
                }
                break;
            case 3:
                if (k == 0x12) {
                    sEventAnnouncePendingEvent = 0x12;
                    sEventAnnounceCurEvent = 0x12;
                    sEventAnnounceActiveEvent = 0x12;
                }
                break;
            }
        }
    }
    if (sEventAnnounceCurEvent != 99) {
        MI_CpuCopy8(&t, buf2, 8);
        if (Event_GetStateAt(sEventAnnounceCurEvent, buf2, 0) == 0) {
            if (sEventAnnounceCurEvent == 0x13) {
                sEventAnnouncePendingEvent = 99;
                sEventAnnounceCurEvent = 99;
            } else {
                EventAnnounce_Request(sEventAnnounceCurEvent, 99, 1);
            }
        }
    }
}

extern "C" void EventAnnounce_Update(void)
{
    if (EventAnnounce_CanCheck()) {
        EventAnnounce_CheckEvents();
    }
}

extern "C" s32 EventAnnounce_IsBusy(void)
{
    return sEventAnnounceBusy;
}

extern "C" s32 EventAnnounce_GetActiveEvent(void)
{
    return sEventAnnounceActiveEvent;
}

extern "C" s32 EventAnnounce_GetCurrentEvent(void)
{
    return sEventAnnounceCurEvent;
}

extern "C" void EventAnnounce_RunIdle(EventAnnouncer *)
{
}

extern "C" void EventAnnounce_RunWaitChimeStart(EventAnnouncer *)
{
    if (Melody_IsBusy() != 0) {
        sEventAnnounceState.announceState = 2;
    }
}

extern "C" void EventAnnounce_RunWaitChimeEnd(EventAnnouncer *)
{
    if (Melody_IsBusy() == 0) {
        EventAnnounce_SetState(3);
    }
}

extern "C" BOOL EventAnnounce_RequestWarp(void)
{
    BOOL r = FALSE;
    if (TalkRequest_AddEventWarp() == 0) {
        sEventAnnounceState.announceState = r;
        sEventAnnounceState.busy = r;
    } else {
        r = TRUE;
        sEventAnnounceState.busy = r;
    }
    return r;
}

extern "C" void EventAnnounce_RunWarp(EventAnnouncer *)
{
    VecFx32 pos;
    BOOL found;
    if (TalkRequestFlags_IsEventWarpStarted() == 0) {
        if (TalkRequest_AddEventWarp() == 0) {
            sEventAnnounceState.announceState = 0;
            sEventAnnounceState.busy = 0;
        }
    } else {
        s32 v = sEventAnnounceState.nextEvent;
        sEventAnnouncePendingEvent = v;
        sEventAnnounceCurEvent = v;
        if (TalkRequestFlags_IsEventWarpReady() != 0 && Melody_IsBusy() == 0) {
            BlockMap *map = TownBlockMap_Get();
            if (map != NULL) {
                if (sEventAnnounceState.msgIndex == 14) {
                    found = Town_FindGulliverShip(map, &pos);
                } else {
                    found = Town_FindTownHall(map, &pos, NULL, NULL);
                }
                if (found) {
                    Scene_SavePlayerPos(Scene_GetWarpRequest(), 0);
                    SceneWarp_RequestAt(Scene_GetWarpRequest(), 0x31, &pos, 0x400000, 0, 2, 2);
                    data_021c1b3c->sceneFade.prepareEventWarp(sEventAnnounceBgmCode, sEventAnnounceState.msgIndex);
                    sEventAnnounceState.announceState = 4;
                    sEventAnnounceBusy = 1;
                }
            }
        }
    }
}

extern "C" void EventAnnounce_RunShowMessage(EventAnnouncer *o)
{
    if (Unk_02040ad8_IsTwo(gScreenTransition.state)) {
        TalkWindowState *p = (TalkWindowState *)TalkWindow_Get(0);
        o->msgRequest.resetMsg();
        ((MsgRequest *)(&o->msgRequest))->setFileName((const char *)((void *)sEventAnnounceMsgFiles[sEventAnnounceState.isEnd]));
        o->msgRequest.msgIndex = sEventAnnounceState.msgIndex;
        ((TalkWindowState *)(p))->attachRequest((TalkMsgRequest *)(&o->msgRequest));
        p->nextState = 1;
        sEventAnnounceState.announceState = 6;
    }
}

extern "C" void EventAnnounce_RunWaitMessageEnd(EventAnnouncer *)
{
    TalkWindowState *p = (TalkWindowState *)TalkWindow_Get(0);
    if (p->state == 0) {
        ((TalkWindowState *)(p))->detachRequest();
        SceneWarp_RequestExit(Scene_GetWarpRequest(), 20);
        data_021c1b3c->sceneFade.prepareEventReturn(sEventAnnounceBgmCode, sEventAnnounceState.msgIndex);
        sEventAnnounceBgmCode = 0;
        sEventAnnounceState.announceState = 0;
        sEventAnnounceState.busy = 0;
    }
}

extern "C" void EventAnnounce_SetState(s32 v)
{
    BOOL r;
    if (v == 3) {
        r = EventAnnounce_RequestWarp();
    } else {
        r = TRUE;
    }
    if (r) {
        sEventAnnounceState.announceState = v;
    }
}

EventAnnounceState::~EventAnnounceState()
{
}

extern "C" void EventAnnounce_Request(s32 a, s32 b, s32 c)
{
    s32 r4;
    s32 r6;
    if (gCommManager->isOnline()) {
        return;
    }
    if (Scene_GetCurrent() == 0) {
        if (TownSessionState_GetResettiFlag(TownSessionState_Get())->isSet()) {
            if (!gCommManager->isSlotActive(gCommManager->myAid)) {
                return;
            }
        }
    }
    if (sEventAnnounceState.busy != 0) {
        return;
    }
    r4 = -1;
    if (a >= 9 && a <= 0x12) {
        r4 = a;
        r4 -= 9;
        if (c == 0) {
            sEventAnnounceBgmCode = 1;
        } else {
            sEventAnnounceBgmCode = 2;
        }
        r6 = 2;
    } else if (a == 0x44) {
        if (sEventAnnounceState.announceState == 0) {
            r4 = 14;
            sEventAnnounceBgmCode = 0;
            r6 = 2;
        }
    } else if (a < 0) {
        switch (sEventAnnounceState.announceState) {
        case 0: {
            Unk_02040974_Rtc t;
            t.a = 0;
            t.b = 0;
            r4 = 15;
            sEventAnnounceBgmCode = 0;
            sEventAnnounceState.dayChangePending = 1;
            Clock_GetDateTime(&t);
            if (((u8 *)&t)[1] == 0) {
                r6 = 1;
            } else {
                r6 = 3;
            }
            break;
        }
        case 2:
            sEventAnnounceState.dayChangePending = 1;
            break;
        }
    }
    if (r4 >= 0) {
        EventAnnounce_SetState(r6);
        sEventAnnounceState.msgIndex = r4;
        sEventAnnounceState.isEnd = c;
        sEventAnnounceState.nextEvent = b;
    }
}

extern "C" BOOL EventAnnounce_IsBlockedScene(void)
{
    switch (Scene_GetCurrent()) {
    case 6:
    case 12:
    case 13:
    case 14:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
    case 0x32:
        return TRUE;
    }
    return FALSE;
}

extern "C" void EventWeekSlots_Construct(u8 *p)
{
    *(s32 *)(p + 0x34) = 0;
    *(s32 *)(p + 0x38) = 0;
}

extern "C" void EventWeekSlots_Destruct(void)
{
}

extern "C" void EventWeekSlots_InitNew(u8 *p)
{
    ClockDateBytes t;
    Clock_GetDate(&t);
    ClockDateBytes t1 = t;
    p[0] = t1.b[0];
    p[1] = t1.b[1];
    p[2] = t1.b[2];
    p[3] = t1.b[3];
    ClockDateBytes t2 = t;
    p[4] = t2.b[0];
    p[5] = t2.b[1];
    p[6] = t2.b[2];
    p[7] = t2.b[3];
    p[8] = 1;
    p[9] = 1;
    p[10] = 0;
    p[11] = 0;
    p[12] = 1;
    p[13] = 1;
    p[14] = 0;
    p[15] = 0;
    p[16] = Random_GlobalBelow(5) + 1;
    p[17] = 99;
    *(s32 *)(p + 0x34) = 0;
    *(s32 *)(p + 0x38) = 0;
    EventWeekSlots_ClearWeek(p);
    EventWeekSlots_UpdateWeek(p, 1);
}

extern "C" void EventWeekSlots_Reset(u8 *p)
{
    EventWeekSlots_InitNew(p);
}

extern "C" void EventWeekSlots_OnLoad(u8 *p)
{
    ClockDateBytes a;
    ClockDateBytes b;
    Clock_GetDate(&a);
    if (Date_DaysBetween(&a, p + 8) >= 7) {
        p[8] = 1;
        p[9] = 1;
        p[10] = 0;
        p[11] = 0;
    }
    Clock_GetDate(&b);
    if (Date_DaysBetween(&b, p + 12) >= 7) {
        p[12] = 1;
        p[13] = 1;
        p[14] = 0;
        p[15] = 0;
    }
    EventWeekSlots_UpdateWeek(p, 0);
    Event_RefreshToday(1);
    EventAnnounce_Restart();
}

