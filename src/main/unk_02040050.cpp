#include "types.h"
#include "host_labels.h"
#include "Unk_020d8c7c.h"
#include "game/Unk_020d96fc_G.h"
#include "sys/ClockDateTime.h"
#include "game/Unk_0203fe18_Date.h"
#include "game/Unk_0203fe18_B4.h"
#include "game/EventWeekSlots.h"
#include "game/ReddPassword.h"
#include "game/ReddShop.h"
#include "game/EventCalendarModule.h"
#include "proto/main/unk_02040050.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02097444.h"



extern "C" {
extern u8 gSaveData[];
}

extern "C" {
u16 sEventWeekSeenMask;
}

extern "C" {
extern u32 sEventWeekLastHour;
}

extern "C" {
#define gSaveEventWeekSlots HOST_LABEL(u8 (*)[], gSaveEventWeekSlots)
}

extern "C" {
#define data_021ed174 HOST_LABEL(u8 (*)[], data_021ed174)
}

extern "C" {
#define data_021ed170 HOST_LABEL(Unk_020d96fc_G *, data_021ed170)
}

extern "C" {
#define data_021ed2c0 HOST_LABEL(ReddShop *, data_021ed2c0)
}

extern "C" {
extern u32 sWeekVisitorWeights[];
}

extern "C" {
extern u32 sWeekVisitorIds[];
}

extern "C" {
s32 DateTime_AddDays(ClockDateTime*, s32);
}

extern "C" {
s32 DateTime_SubDays(ClockDateTime*, s32);
}

extern "C" {
void Clock_GetDateTime(ClockDateTime*);
}

extern "C" {
s32 Clock_GetWeekday(void);
}

extern "C" {
s32 Date_DaysBetween(Unk_0203fe18_B3*, u8*);
}

extern "C" {
void DateTime_GetWeekStart(ClockDateTime*, long long*);
}

extern "C" {
}

extern "C" {
void MI_CpuCopy8(const void*, void*, u32);
}

extern "C" {
s32 Game_IsIntroPeriod(void);
}

extern "C" {
s32 Event_GetStateAt(u32, ClockDateTime*, s32);
}

extern "C" {
s32 EventDayList_GetState(u32, ClockDateTime*, void*);
}

extern "C" {
s32 EventSchedule_CollectDayAll(void*, ClockDateTime*);
}

extern "C" {
s32 ReddShop_SendPasswordLetters(void);
}

extern "C" {
}

extern "C" {
s32 WeekVisitors_ListContains(void*, void*, s32);
}

extern "C" {
s32 WeekVisitors_PickFreeDay(void*, void*, s32);
}

extern "C" {
s32 WeekVisitors_FindFreeDays(void*, void*, void*);
}

extern "C" {
EventWeekSlot* EventWeekSlots_Get(EventWeekSlots*, s32);
}

extern "C" {
s32 EventWeekSlots_FindId(EventWeekSlots*, u32);
}

extern "C" {
EventWeekSlot* EventWeekSlots_GetToday(EventWeekSlots*);
}

extern "C" {
void EventWeekSlots_RefreshSeenMask(EventWeekSlots*);
}

extern "C" {
void EventWeekSlots_SyncToday(EventWeekSlots*);
}

extern "C" {
void EventWeekSlot_MarkAllPlayers(EventWeekSlot*);
}

extern "C" {
void EventWeekSlot_Clear(EventWeekSlot*);
}

extern "C" {
void EventWeekSlot_Set(EventWeekSlot*, u8, ClockDateTime*);
}

extern "C" {
void EventWeekSlots_ClearWeek(EventWeekSlots*);
}

extern "C" {
s32 WeekVisitors_PickRandom(EventWeekSlots*, u8*);
}

extern "C" {
void EventWeekSlots_MarkPastDays(EventWeekSlots*);
}

extern "C" {
void EventWeekSlots_PlaceRedd(EventWeekSlots*, s32*, s32*, ClockDateTime*);
}

extern "C" {
void EventWeekSlots_PlacePete(EventWeekSlots*, s32*, s32*, ClockDateTime*);
}

extern "C" {
void EventWeekSlots_PlaceVisitors(EventWeekSlots*, s32*, s32*, u8*, ClockDateTime*);
}

extern "C" {
void EventWeekSlots_UpdateWeek(EventWeekSlots*, s32);
}

extern "C" {
void Date_GetWeekBoundary(ClockDateTime*, s32);
}

extern "C" {
BOOL EventWeek_IsInUnkWeek(Unk_0203fe18_B4);
}

#define SLOT ((EventWeekSlots *)(gSaveData + 0x15e18))

extern "C" void EventWeekSlots_MarkTodaySeen(u32 id);
extern "C" void Date_GetWeekBoundary(ClockDateTime *d, s32 n);
extern "C" BOOL EventWeek_IsInLyleWeek(Unk_0203fe18_B4 d);
extern "C" void EventWeek_SetLyleWeek(u32 x, s32 flag);
extern "C" BOOL EventWeek_IsInUnkWeek(Unk_0203fe18_B4 d);
extern "C" BOOL EventWeekSlots_IsSeenToday(u32 id);
extern "C" void EventWeekSlots_SyncToday(EventWeekSlots *s);
extern "C" void EventWeekSlots_RefreshSeenMask(EventWeekSlots *s);

extern "C" void EventWeekSlots_MarkTodaySeen(u32 id) {
    if (id >= 0x3e && id < 0x46) {
        EventWeekSlot *e = EventWeekSlots_GetToday((EventWeekSlots *)gSaveEventWeekSlots);
        if (e) {
            if (id == e->eventId) e->occurred = 1;
        }
    }
}

extern "C" void Date_GetWeekBoundary(ClockDateTime *d, s32 n) {
    Clock_GetDateTime(d);
    if (n == 1) {
        s32 t = Clock_GetWeekday() + 1;
        DateTime_SubDays(d, t);
    }
    else {
        s32 t = 7 - Clock_GetWeekday();
        DateTime_AddDays(d, t);
    }
}

extern "C" BOOL EventWeek_IsInLyleWeek(Unk_0203fe18_B4 d) {
    BOOL r = FALSE;
    u8 b3 = d.b.b3;
    u8 b2 = d.b.b2;
    u8 *g = (u8 *)&data_021ed170;
    u8 c = g[2];
    if (c != 0 || g[1] != 1 || g[0] != 1) {
        Unk_0203fe18_B3 t;
        s32 n;
        t.b2 = c;
        t.b1 = b3;
        t.b0 = b2;
        n = Date_DaysBetween(&t, g);
        if (n >= 0 && n < 7) r = TRUE;
    }
    return r;
}

extern "C" void EventWeek_SetLyleWeek(u32 x, s32 flag) {
    Unk_020d96fc_G *g = &data_021ed170;
    if (flag == 0) {
        g->b0 = 1;
        g->b1 = 1;
        g->b2 = 0;
        g->b3 = 0;
    } else {
        ClockDateTime d;
        ((s32*)&d)[0] = 0;
        ((s32*)&d)[1] = 0;
        Date_GetWeekBoundary(&d, x);
        g->b0 = d.day;
        g->b1 = d.month;
        g->b2 = d.year;
    }
}

extern "C" BOOL EventWeek_IsInUnkWeek(Unk_0203fe18_B4 d) {
    BOOL r = FALSE;
    u8 b3 = d.b.b3;
    u8 b2 = d.b.b2;
    u8 *g = data_021ed174;
    u8 c = g[2];
    if (c != 0 || g[1] != 1 || g[0] != 1) {
        Unk_0203fe18_B3 t;
        s32 n;
        t.b2 = c;
        t.b1 = b3;
        t.b0 = b2;
        n = Date_DaysBetween(&t, g);
        if (n >= 0 && n < 7) r = TRUE;
    }
    return r;
}

extern "C" BOOL EventWeekSlots_IsSeenToday(u32 id) {
    u8 *g = gSaveData;
    BOOL r = FALSE;
    s32 o = id ? 0x15e2a : 0x15e2a;
    if (id == g[o]) {
        s32 n = PlayerData_GetCurrentIndex();
        if (n == 7) {
            if (sEventWeekSeenMask == 0xff) r = TRUE;
        } else if (((sEventWeekSeenMask >> n) & 1) != 0) {
            r = TRUE;
        }
    }
    return r;
}

extern "C" void EventWeekSlots_SyncToday(EventWeekSlots *s) {
    s32 r4 = Clock_GetWeekday();
    EventWeekSlot *e = EventWeekSlots_GetToday(s);
    if (e) {
        u8 t = e->eventId;
        if (r4 != s->todayWeekday || t != s->todayEventId) {
            s->todayEventId = t;
            s->todayWeekday = r4;
        }
        EventWeekSlots_RefreshSeenMask(s);
    }
}

extern "C" void EventWeekSlots_RefreshSeenMask(EventWeekSlots *s) {
    EventWeekSlot *e;
    sEventWeekSeenMask = 0xff;
    e = EventWeekSlots_GetToday((EventWeekSlots *)gSaveEventWeekSlots);
    if (e) sEventWeekSeenMask = e->playerMask;
}

