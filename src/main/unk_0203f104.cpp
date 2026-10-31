#include "types.h"
#include "host_labels.h"
#include "save/VillagerData.h"
#include "sys/ProcProfile.h"
#include "Unk_020d8c7c.h"
#include "game/Unk_0203f3a0_L.h"
#include "game/EventDayEntry.h"
#include "game/Unk_0203f42c_L.h"
#include "sys/ClockDateTime.h"
#include "game/Unk_0203fe18_Date.h"
#include "game/EventWeekSlots.h"
#include "game/EventCalendarModule.h"
#include "game/EventScheduleRule.h"
#include "net/CommManager.h"
#include "npc/VillagerId.h"
#include "player/PlayerData.h"
#include "save/BlancaFaceRecord.h"
#include "proto/main/unk_0203f104.h"
#include "proto/main/unk_02085940.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_0209eb94.h"

extern "C" void MI_CpuCopy8(const void *src, void *dst, u32 size);

struct ClockDateTimeCopy {
    u8 b[8];
    ClockDateTimeCopy() {}
    ClockDateTimeCopy(const ClockDateTimeCopy &o) { MI_CpuCopy8(&o, this, 8); }
};

struct Unk_0203f554_CalB {
    u8 b0, b1, b2, b3;
};
union EventDate {
    u32 w;
    Unk_0203f554_CalB s;
    Unk_0203f554_CalB b;
};
typedef EventDate Unk_0203fe18_B4;

struct EventEntryView {
    u16 id;
    u16 kind;
    EventDate a;
    EventDate b;
};


class EventDayList {
public:
    EventDayList();
    ~EventDayList();

    /* 0x00 */ u8 date[4];
    /* 0x04 */ EventDayEntry entries[7];
};

struct Unk_0203f820_Date {
    u32 a;
    u32 b;
    Unk_0203f820_Date() {
        a = 0;
        b = 0;
    }
};

union Unk_0203fb1c_Pair {
    u16 h;
    u8 b[2];
};
struct EventWeekSlotView {
    Unk_0203fb1c_Pair pr;
    u8 id;
};





extern "C" {
extern u8 gSaveData[];
#define gSaveEventWeekSlots HOST_LABEL(u8 (*)[], gSaveEventWeekSlots)
#define gSaveBlancaFace HOST_LABEL(u8 (*)[], gSaveBlancaFace)
extern u8 gBackup[];
extern CommManager *gCommManager;
}

extern "C" {
s32 Backup_GetStatus(void *p);
s32 EventWeekSlots_UpdateToday(s32 v);
s32 EventWeekSlots_IsSeenToday(u32 id);
s32 DateTime_DiffMinutes(void *a, void *b);
s32 DateTime_DiffDays(void *a, void *b);
void Clock_GetDateTime(void *);
void DateTime_AddDays(void *, s32);
void DateTime_SubDays(void *, s32);
s32 Date_GetWeekday(u32, u32, u32);
s32 Date_GetDaysInMonth(u32, u32);
s32 Clock_GetWeekday(void);
s32 EventWeekSlots_FindId(EventWeekSlots *, u32);
s32 EventWeek_IsInLyleWeek(EventDate);
s32 EventWeek_IsInUnkWeek(EventDate);
s32 Villager_GetResidentStatus(void *);
s32 Villager_GetIndex(void *);
void *SaveVillagers_Get(void *, s32);
s32 SaveVillagers_GetUnk3830Index(void *);
u8 *Villager_GetBirthday(void *);

void Event_RefreshToday(s32);
s32 EventSchedule_CollectDay(EventEntryView *, ClockDateTimeCopy, s32);
s32 EventSchedule_Collect(EventEntryView *out, ClockDateTimeCopy d, s32 x, s32 y);
EventDate EventRule_ResolveStart(Unk_0203f554_Sub *, s32, EventDate, u32);
EventDate EventRule_ResolveEnd(Unk_0203f554_Sub *, s32, EventDate, u32);
EventDate EventRule_Resolve(Unk_0203f554_Sub *, s32, EventDate, u32);
s32 EventSchedule_Match(EventEntryView *, EventScheduleRule *, s32, EventDate);
void Event_AdjustToDay(EventEntryView *, EventDate);
s32 EventSchedule_IsBlocked(EventScheduleRule *, EventDate, EventEntryView *, EventEntryView *, s32, s32, s32);
void EventDayList_Clear(EventEntryView *, s32);
u8 EventRule_ResolveMonth(u32 *self, s32 w0, Unk_0203fe18_B4 d, s32 type);
u8 EventRule_ResolveDay(Unk_0203f554_Sub *, u32, EventDate, u32, u32);
void EventRule_GetPlayerBirthday(Unk_0203f554_Sub *, EventDate *);
void EventRule_GetVillagerBirthday(Unk_0203f554_Sub *, EventDate *, s32);
EventDate EventRule_GetWeekSlotDate(Unk_0203f554_Sub *, u32, EventDate);
void Event_RefreshIfDateChanged();
s32 Event_GetStateAt(s32 a, u8 *b, s32 c);
s32 EventDayList_GetState(s32 a, u8 *b, EventDayEntry *c);
EventDayEntry *EventDayList_Find(u32 id, EventDayEntry *tbl);
s32 Game_IsIntroPeriod(void);
EventWeekSlot *EventWeekSlots_Get(EventWeekSlots *, s32);
s32 EventWeekSlots_IsUnavailable(u32, s32);
void EventWeekSlot_Clear(EventWeekSlot *);
}

EventDayList gTodayEvents;
s32 sEventsOnlineRefresh;
EventDayList data_021c3c30;

EventScheduleRule sEventSchedule[99] = {
    { 0x0, 5, { 0x4000, 0x0, 0x0 }, { 0x4000, 0x0, 0x18 } },
    { 0x4b, 5, { 0x4001, -4, 0x0 }, { 0x4001, -1, 0x18 } },
    { 0x1, 5, { 0x4000, 0x0, 0x0 }, { 0x4000, 0x0, 0x18 } },
    { 0x4c, 5, { 0x4001, -4, 0x0 }, { 0x4001, -1, 0x18 } },
    { 0x2, 5, { 0x4000, 0x0, 0x0 }, { 0x4000, 0x0, 0x18 } },
    { 0x4d, 5, { 0x4001, -4, 0x0 }, { 0x4001, -1, 0x18 } },
    { 0x3, 5, { 0x4000, 0x0, 0x0 }, { 0x4000, 0x0, 0x18 } },
    { 0x4e, 5, { 0x4001, -4, 0x0 }, { 0x4001, -1, 0x18 } },
    { 0x4, 5, { 0x4000, 0x0, 0x0 }, { 0x4000, 0x0, 0x18 } },
    { 0x4f, 5, { 0x4001, -4, 0x0 }, { 0x4001, -1, 0x18 } },
    { 0x5, 5, { 0x4000, 0x0, 0x0 }, { 0x4000, 0x0, 0x18 } },
    { 0x50, 5, { 0x4001, -4, 0x0 }, { 0x4001, -1, 0x18 } },
    { 0x6, 5, { 0x4000, 0x0, 0x0 }, { 0x4000, 0x0, 0x18 } },
    { 0x51, 5, { 0x4001, -4, 0x0 }, { 0x4001, -1, 0x18 } },
    { 0x7, 5, { 0x4000, 0x0, 0x0 }, { 0x4000, 0x0, 0x18 } },
    { 0x52, 5, { 0x4001, -4, 0x0 }, { 0x4001, -1, 0x18 } },
    { 0x8, 5, { 0x2000, 0x0, 0x0 }, { 0x2000, 0x0, 0x18 } },
    { 0x9, 5, { 0x7310, 0x0, 0xc }, { 0x7310, 0x0, 0x12 } },
    { 0x14, 0, { 0x7310, 0x0, 0xc }, { 0x7310, 0x0, 0x12 } },
    { 0x25, 5, { 0x7311, -6, 0x0 }, { 0x7311, -6, 0x18 } },
    { 0x26, 5, { 0x7311, -1, 0x0 }, { 0x7311, -1, 0x18 } },
    { 0x46, 5, { 0x7311, -4, 0x0 }, { 0x7311, -1, 0x18 } },
    { 0xa, 5, { 0x9320, 0x0, 0xc }, { 0x9320, 0x0, 0x12 } },
    { 0x15, 0, { 0x9320, 0x0, 0xc }, { 0x9320, 0x0, 0x12 } },
    { 0x27, 5, { 0x9321, -6, 0x0 }, { 0x9321, -6, 0x18 } },
    { 0x28, 5, { 0x9321, -1, 0x0 }, { 0x9321, -1, 0x18 } },
    { 0x47, 5, { 0x9321, -4, 0x0 }, { 0x9321, -1, 0x18 } },
    { 0xb, 5, { 0x90c, 0x0, 0x6 }, { 0x90d, 0x1, 0x6 } },
    { 0x29, 5, { 0x91d, -5, 0x0 }, { 0x91d, -5, 0x18 } },
    { 0x2a, 5, { 0x91d, -1, 0x0 }, { 0x91d, -1, 0x18 } },
    { 0x48, 5, { 0x91d, -4, 0x0 }, { 0x91d, -1, 0x18 } },
    { 0xc, 5, { 0x121c, 0x0, 0x6 }, { 0x121d, 0x1, 0x6 } },
    { 0x2b, 5, { 0x121d, -6, 0x0 }, { 0x121d, -6, 0x18 } },
    { 0x2c, 5, { 0x121d, -1, 0x0 }, { 0x121d, -1, 0x18 } },
    { 0x49, 5, { 0x121d, -4, 0x0 }, { 0x121d, -1, 0x18 } },
    { 0xd, 5, { 0x1410, 0x0, 0x6 }, { 0x1411, 0x1, 0x6 } },
    { 0x2d, 5, { 0x1411, -6, 0x0 }, { 0x1411, -6, 0x18 } },
    { 0x2e, 5, { 0x1411, -1, 0x0 }, { 0x1411, -1, 0x18 } },
    { 0x4a, 5, { 0x1411, -4, 0x0 }, { 0x1411, -1, 0x18 } },
    { 0xe, 5, { 0xa24d, -5, 0x6 }, { 0xa24d, 0x2, 0x6 } },
    { 0x16, 0, { 0xa24d, -5, 0x6 }, { 0xa24d, 0x1, 0x18 } },
    { 0x2f, 5, { 0x24d, -10, 0x0 }, { 0x24d, -10, 0x18 } },
    { 0x30, 5, { 0x24d, -6, 0x0 }, { 0x24d, -6, 0x18 } },
    { 0x31, 5, { 0x24d, -5, 0x0 }, { 0x24d, -5, 0x18 } },
    { 0x54, 5, { 0x24d, -12, 0x0 }, { 0x24d, -9, 0x18 } },
    { 0x55, 5, { 0x24d, -8, 0x0 }, { 0x24d, -7, 0x18 } },
    { 0x56, 5, { 0x24d, -6, 0x0 }, { 0x24d, -6, 0x18 } },
    { 0xf, 5, { 0x78c, 0x0, 0x13 }, { 0x78c, 0x0, 0x18 } },
    { 0x17, 0, { 0x78c, 0x0, 0x13 }, { 0x78c, 0x0, 0x18 } },
    { 0x32, 5, { 0x18d, -5, 0x0 }, { 0x18d, -5, 0x18 } },
    { 0x33, 5, { 0x78d, -1, 0x0 }, { 0x78d, -1, 0x18 } },
    { 0x57, 5, { 0x78d, -5, 0x0 }, { 0x78d, -4, 0x18 } },
    { 0x58, 5, { 0x78d, -3, 0x0 }, { 0x78d, -2, 0x18 } },
    { 0x59, 5, { 0x78d, -1, 0x0 }, { 0x78d, -1, 0x18 } },
    { 0x10, 5, { 0xa2ad, -5, 0x6 }, { 0xa2ad, 0x2, 0x6 } },
    { 0x18, 0, { 0xa2ad, -5, 0x6 }, { 0xa2ad, 0x1, 0x18 } },
    { 0x34, 5, { 0x2ad, -10, 0x0 }, { 0x2ad, -10, 0x18 } },
    { 0x35, 5, { 0x2ad, -6, 0x0 }, { 0x2ad, -6, 0x18 } },
    { 0x36, 5, { 0x2ad, -5, 0x0 }, { 0x2ad, -5, 0x18 } },
    { 0x5a, 5, { 0x2ad, -12, 0x0 }, { 0x2ad, -9, 0x18 } },
    { 0x5b, 5, { 0x2ad, -8, 0x0 }, { 0x2ad, -7, 0x18 } },
    { 0x5c, 5, { 0x2ad, -6, 0x0 }, { 0x2ad, -6, 0x18 } },
    { 0x11, 5, { 0xa22d, -5, 0x6 }, { 0xa22d, 0x2, 0x6 } },
    { 0x19, 0, { 0xa22d, -5, 0x6 }, { 0xa22d, 0x1, 0x18 } },
    { 0x37, 5, { 0x22d, -10, 0x0 }, { 0x22d, -10, 0x18 } },
    { 0x38, 5, { 0x22d, -6, 0x0 }, { 0x22d, -6, 0x18 } },
    { 0x39, 5, { 0x22d, -5, 0x0 }, { 0x22d, -5, 0x18 } },
    { 0x5d, 5, { 0x22d, -12, 0x0 }, { 0x22d, -9, 0x18 } },
    { 0x5e, 5, { 0x22d, -8, 0x0 }, { 0x22d, -7, 0x18 } },
    { 0x5f, 5, { 0x22d, -6, 0x0 }, { 0x22d, -6, 0x18 } },
    { 0x12, 5, { 0xc0, 0x1f, 0x6 }, { 0xc0, 0x1f, 0x18 } },
    { 0x1a, 0, { 0xc0, 0x1f, 0x6 }, { 0xc0, 0x1f, 0x18 } },
    { 0x53, 5, { 0xc0, 0x1b, 0x0 }, { 0xc0, 0x1e, 0x18 } },
    { 0x62, 5, { 0xc0c0, 0x1f, 0x6 }, { 0xc0c1, 0x1, 0x6 } },
    { 0x13, 5, { 0x10, 0x1, 0x0 }, { 0x10, 0x1, 0x18 } },
    { 0x1b, 0, { 0x10, 0x1, 0x0 }, { 0x10, 0x1, 0x18 } },
    { 0x61, 5, { 0xc0c0, 0x1f, 0x6 }, { 0xc0c1, 0x2, 0x6 } },
    { 0x1c, 5, { 0x10, 0x1, 0x0 }, { 0x10, 0x1, 0x18 } },
    { 0x1d, 5, { 0x10, 0xf, 0x0 }, { 0x10, 0xf, 0x18 } },
    { 0x1e, 5, { 0x30, 0xf, 0x0 }, { 0x30, 0xf, 0x18 } },
    { 0x1f, 5, { 0x50, 0x6, 0x0 }, { 0x50, 0x6, 0x18 } },
    { 0x20, 5, { 0x70, 0x1, 0x0 }, { 0x70, 0x1, 0x18 } },
    { 0x21, 5, { 0xb0, 0xc, 0x0 }, { 0xb0, 0xc, 0x18 } },
    { 0x22, 5, { 0xc0, 0x9, 0x0 }, { 0xc0, 0x9, 0x18 } },
    { 0x23, 5, { 0xc0, 0x1c, 0x0 }, { 0xc0, 0x1c, 0x18 } },
    { 0x24, 5, { 0xc0, 0x1f, 0x0 }, { 0xc0, 0x1f, 0x18 } },
    { 0x3a, 0, { 0xf0c, 0x0, 0x13 }, { 0xf0c, 0x0, 0x18 } },
    { 0x3b, 1, { 0xf00, 0x0, 0x6 }, { 0xf00, 0x0, 0xc } },
    { 0x3c, 1, { 0xf0c, 0x0, 0x6 }, { 0xf0c, 0x0, 0x12 } },
    { 0x3d, 1, { 0xcf00, 0x0, 0x6 }, { 0xcf01, 0x1, 0x6 } },
    { 0x3e, 2, { 0xcf00, 0x0, 0x6 }, { 0xcf00, 0x0, 0x18 } },
    { 0x3f, 2, { 0xcf00, 0x0, 0x6 }, { 0xcf01, 0x1, 0x6 } },
    { 0x40, 2, { 0xcf00, 0x0, 0x6 }, { 0xcf00, 0x0, 0x18 } },
    { 0x60, 4, { 0xcf00, 0x0, 0x6 }, { 0xcf01, 0x1, 0x6 } },
    { 0x41, 2, { 0xcf00, 0x0, 0x6 }, { 0xcf00, 0x0, 0x18 } },
    { 0x42, 2, { 0xcf00, 0x0, 0x6 }, { 0xcf01, 0x1, 0x6 } },
    { 0x43, 2, { 0xcf00, 0x0, 0x6 }, { 0xcf00, 0x0, 0x18 } },
    { 0x44, 2, { 0xcf00, 0x0, 0x6 }, { 0xcf01, 0x1, 0x6 } },
    { 0x45, 3, { 0xcf00, 0x0, 0x6 }, { 0xcf00, 0x0, 0x11 } },
};

static inline BOOL IsOne(u8 v) { return v == 1 ? TRUE : FALSE; }
static inline BOOL IsZero(u8 v) { return v == 0 ? TRUE : FALSE; }

extern "C" EventWeekSlot *EventWeekSlots_Get(EventWeekSlots *s, s32 idx) {
    EventWeekSlot *r = 0;
    if (idx >= 0 && idx <= 6 && idx != 0 && idx != 6) {
        r = s->ent + (idx - 1);
    }
    return r;
}

extern "C" EventWeekSlot *EventWeekSlots_GetToday(EventWeekSlots *unused) {
    u8 *g = gSaveData;
    EventWeekSlot *r = 0;
    s32 r4 = Clock_GetWeekday();
    if (r4) {
        ClockDateTime d;
        ((s32*)&d)[0] = 0;
        ((s32*)&d)[1] = 0;
        Clock_GetDateTime(&d);
        if (d.hour < 6) r4--;
        r = EventWeekSlots_Get((EventWeekSlots *)(g + 0x15e18), r4);
    }
    return r;
}

extern "C" void EventWeekSlots_MarkPlayer(u32 id) {
    EventWeekSlots *s = (EventWeekSlots *)gSaveEventWeekSlots;
    EventWeekSlot *e = EventWeekSlots_Get(s, EventWeekSlots_FindId(s, id));
    if (e) {
        if (id == 0x44) {
            e->playerMask = 0xff;
        } else {
            u32 m = 1 << PlayerData_GetCurrentIndex();
            e->playerMask = (e->playerMask & ~m) | m;
        }
    }
}

extern "C" BOOL EventWeekSlots_IsUnavailable(u32 id, s32 idx) {
    BOOL r;
    EventWeekSlot *e;
    u8 *g;
    if (id == 0x45) return FALSE;
    g = gSaveData;
    r = FALSE;
    if (id == 0x60) id = 0x40;
    e = EventWeekSlots_Get((EventWeekSlots *)(g + 0x15e18), idx);
    if (e) {
        if (id != e->eventId) {
            r = TRUE;
        } else if ((u8)((e->playerMask >> PlayerData_GetCurrentIndex()) & 1) != 0) {
            r = TRUE;
        }
    }
    return r;
}

extern "C" void EventWeekSlot_Clear(EventWeekSlot *e) {
    e->date = 1;
    e->eventId = 0x63;
    e->state = 0;
    e->occurred = 0;
    e->playerMask = 0;
}

extern "C" void EventWeekSlot_Set(EventWeekSlot *e, u8 id, ClockDateTime *d) {
    EventWeekSlot_Clear(e);
    ((u8*)e)[1] = d->month;
    ((u8*)e)[0] = d->day;
    e->eventId = id;
}

extern "C" void EventWeekSlot_MarkAllPlayers(EventWeekSlot *e) {
    if (e->eventId != 0x45) {
        e->playerMask = 0xff;
        e->state = 2;
    }
}

extern "C" EventCalendarModule *EventCalendarModule_New() {
    return new EventCalendarModule();
}

ProcProfile data_020d96ec = {(void *(*)())EventCalendarModule_New, 0x8c, 0x90};

EventDayList::EventDayList() {
    date[0] = 1;
    date[1] = 1;
    date[2] = 0;
    date[3] = 0;
}

EventDayList::~EventDayList() {}

extern "C" u8 EventRule_ResolveMonth(u32 *self, s32 w0, Unk_0203fe18_B4 d, s32 type) {
    u8 b7 = d.s.b3;
    u8 b6 = d.s.b2;
    u8 r = 0;
    u32 v = *self;
    u32 nib = (v >> 4) & 0xf;
    u32 mode = (v >> 11) & 3;
    switch (mode) {
    case 0:
        r = nib;
        break;
    case 1:
        if (nib == 0) {
            r = b7;
        } else {
            ClockDateTime t;
            s32 n;
            ((u32*)&t)[0] = 0;
            ((u32*)&t)[1] = 0;
            if (type == 0x48) n = -4; else n = self[1];
            ((u32*)&t)[0] = 0;
            ((u32*)&t)[1] = 0;
            t.year = w0;
            t.month = b7;
            t.day = b6;
            if (n < 0) n = -n;
            DateTime_AddDays(&t, n);
            r = t.month;
        }
        switch (type) {
        case 0x29:
        case 0x2a:
        case 0xb:
        case 0x48:
            if (r == 1 || r == 8) r = 2;
        }
        break;
    case 2:
        if (nib == 1) {

            r = (b7 & ~1) + 1;
        } else {
            r = (b7 + 1) & ~1;
        }
        break;
    }
    return r;
}

extern "C" u8 EventRule_ResolveDay(Unk_0203f554_Sub *e, u32 year, EventDate cal, u32 mon, u32 id) {
    s32 s;
    u32 b;
    s32 k;
    u32 c, cm;
    s32 dim, x, r6, r2;
    u32 w = e->flags;
    b = (w >> 8) & 7;
    c = (w >> 1) & 7;
    dim = Date_GetDaysInMonth(year, mon);
    cm = ((volatile Unk_0203f554_CalB *)&cal)->b3;
    x = Date_GetDaysInMonth(year, cm);
    switch (b) {
    case 0:
        return e->off;
    case 6: {
        s32 wd = Date_GetWeekday((u8)year, mon, (u8)dim);
        if (wd < cal.s.b0) {
            return dim - 7 + (cal.s.b0 - wd);
        } else {
            return dim - (wd - cal.s.b0);
        }
    }
    case 7: {
        s32 v;
        u32 t = cal.s.b0;
        if (c < t) {
            v = (u8)(cal.s.b2 + (c - t + 7));
        } else {
            v = (u8)(cal.s.b2 + (c - t));
        }
        if (cm != mon && v > x) {
            v -= x;
        }
        return v;
    }
    default:
        r6 = cal.s.b0 - ((cal.s.b2 - 1) % 7);
        if (r6 < 0) r6 += 7;
        if (mon != cm) {
            s = 0;
            k = mon;
            if (mon == 1 && cm == 12) k = 13;
            if (k < cm) {
                cm = cal.s.b3;
                for (; k < (s32)cm; k++) {
                    s += Date_GetDaysInMonth(year, (u8)k);
                }
                s = (s % 7);
                r6 = ((r6 - s + 7) % 7);
            } else {
                for (; (s32)cm < k; cm++) {
                    s += Date_GetDaysInMonth(year, (u8)cm);
                }
                r6 = ((r6 + s) % 7);
            }
        }
        if (r6 <= c) {
            r2 = c - r6 + 1;
        } else {
            r2 = c - r6 + 8;
        }
        switch ((s32)id) {
        case 9:
        case 0x14:
        case 0x25:
        case 0x26:
        case 0x46:
            if (mon == 2 || mon == 4 || mon == 10) {
                b = 4;
            }
        }
        return r2 + (b - 1) * 7;
    }
}

extern "C" void EventRule_GetPlayerBirthday(Unk_0203f554_Sub *e, EventDate *out) {
    if (PlayerData_GetCurrent()) {
        u8 *p = (u8 *)PlayerData_GetCurrent()->getBirthday();
        if (p) {
            out->s.b3 = p[1];
            out->s.b2 = p[0];
            out->s.b1 = e->hour;
        }
    }
}

extern "C" BOOL Villager_IsSettledExcept(void *a, s32 b) {
    BOOL r = FALSE;
    if (((VillagerData *)a)->getVillagerId()->isValid()) {
        if (Villager_GetResidentStatus(a) == 3) {
            s32 x = Villager_GetIndex(a);
            if (x != -1 && x != b) {
                r = TRUE;
            }
        }
    }
    return r;
}

extern "C" void EventRule_GetVillagerBirthday(Unk_0203f554_Sub *e, EventDate *out, s32 n) {
    u8 *base = gSaveData;
    out->w = 0;
    if (n < 0 || n > 7) n -= 0x4b;
    void *r6 = SaveVillagers_Get(base + 0x8a3c, n);
    if (Villager_IsSettledExcept(r6, SaveVillagers_GetUnk3830Index(base + 0x8a3c))) {
        u8 *p = Villager_GetBirthday(r6);
        if (p) {
            out->s.b3 = p[0];
            out->s.b2 = p[1];
            out->s.b1 = e->hour;
        }
    }
}

extern "C" EventDate EventRule_GetWeekSlotDate(Unk_0203f554_Sub *e, u32 id, EventDate cal) {
    Unk_0203fb1c_Pair x, y;
    u8 *base = gSaveData;
    EventDate ret;
    ret.w = 0;
    if (id == 0x45) {
        EventWeekSlotView *p = (EventWeekSlotView *)EventWeekSlots_Get((EventWeekSlots *)(base + 0x15e18), cal.s.b0);
        if (p && id == p->id) {
            x = p->pr;
            ret.s.b3 = x.b[1];
            ret.s.b2 = x.b[0];
            ret.s.b1 = e->hour;
        }
    } else {
        if (id == 0x60) id = 0x40;
        s32 n = cal.s.b0 - 1;
        for (s32 i = 0; i < 2; n++, i++) {
            EventWeekSlotView *p = (EventWeekSlotView *)EventWeekSlots_Get((EventWeekSlots *)(base + 0x15e18), n);
            if (p && id == p->id) {
                y = p->pr;
                ret.s.b3 = y.b[1];
                ret.s.b2 = y.b[0];
                ret.s.b1 = e->hour;
                break;
            }
        }
    }
    return ret;
}

extern "C" EventDate EventRule_Resolve(Unk_0203f554_Sub *e, s32 year, EventDate cal, u32 id) {
    EventDate ret;
    ret.w = 0;
    u32 w = e->flags;
    u32 a = (w >> 4) & 0xf;
    u32 b = (w >> 8) & 7;
    u32 c = (w >> 1) & 7;
    u32 d = w & 1;
    u32 type = (w >> 13) & 7;
    switch (type) {
    case 3: {
        u32 m = cal.s.b3;
        switch (m) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 10:
        case 11:
        case 12:
            ret.s.b3 = m;
            break;
        default:
            ret.s.b3 = 1;
            break;
        }
        ret.s.b2 = EventRule_ResolveDay(e, year, cal, ret.s.b3, id);
        ret.s.b1 = e->hour;
        break;
    }
    case 4: {
        u32 m = cal.s.b3;
        switch (m) {
        case 6:
        case 7:
        case 8:
        case 9:
            ret.s.b3 = m;
            break;
        default:
            ret.s.b3 = 6;
            break;
        }
        ret.s.b2 = EventRule_ResolveDay(e, year, cal, ret.s.b3, id);
        ret.s.b1 = e->hour;
        break;
    }
    case 0:
        ret.s.b3 = EventRule_ResolveMonth((u32 *)e, year, cal, id);
        ret.s.b2 = EventRule_ResolveDay(e, year, cal, ret.s.b3, id);
        ret.s.b1 = e->hour;
        break;
    case 1:
        EventRule_GetPlayerBirthday(e, &ret);
        break;
    case 2:
        EventRule_GetVillagerBirthday(e, &ret, id);
        break;
    case 5: {
        s32 s;
        s32 r5;
        u32 r4;
        ret.s.b3 = a;
        r5 = cal.s.b0 - (cal.s.b2 - 1) % 7;
        if (r5 < 0) r5 += 7;
        r4 = cal.s.b3;
        if (a != r4) {
            s = 0;
            if (a < r4) {
                for (s32 m = a; m < (s32)r4; m++) {
                    s += Date_GetDaysInMonth(year, (u8)m);
                }
                s %= 7;
                r5 = (r5 - s + 7) % 7;
            } else {
                for (; r4 < a; r4++) {
                    s += Date_GetDaysInMonth(year, (u8)r4);
                }
                r5 = (r5 + s) % 7;
            }
        }
        {
            s32 r2;
            if (r5 <= c) {
                r2 = c - r5 + 1;
            } else {
                r2 = c - r5 + 8;
            }
            ret.s.b2 = r2 + (b - 1) * 7;
        }
        ret.s.b1 = e->hour;
        break;
    }
    case 6:
        switch ((s32)id) {
        case 0x3d:
        case 0x3e:
        case 0x3f:
        case 0x40:
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x44:
        case 0x45:
        case 0x60:
            ret = EventRule_GetWeekSlotDate(e, id, cal);
            break;
        case 0x61:
        case 0x62:
            if (d != 0) {
                if (cal.s.b3 == 1) {
                    ret.s.b3 = 12;
                    ret.s.b2 = 0x1f;
                    ret.s.b1 = 6;
                } else {
                    d = 0;
                    ret.s.b3 = 12;
                    ret.s.b2 = 0x1f;
                    ret.s.b1 = 0x18;
                }
            } else {
                if (cal.s.b3 == 1) {
                    ret.s.b3 = 1;
                    ret.s.b2 = 1;
                    ret.s.b1 = 0;
                } else {
                    ret.s.b3 = 12;
                    ret.s.b2 = 0x1f;
                    ret.s.b1 = 6;
                }
            }
            break;
        }
        break;
    }
    if (ret.w != 0) {
        Unk_0203f820_Date dt;
        dt.a = 0;
        dt.b = 0;
        ((u8 *)&dt)[5] = year;
        ((u8 *)&dt)[4] = ret.s.b3;
        ((u8 *)&dt)[3] = ret.s.b2;
        s32 dim = Date_GetDaysInMonth(year, ret.s.b3);
        if (ret.s.b2 > dim) {
            ((u8 *)&dt)[3] = dim;
            DateTime_AddDays(&dt, ret.s.b2 - dim);
        }
        if (d != 0) {
            s32 off = e->off;
            if (off < 0) {
                DateTime_SubDays(&dt, off < 0 ? -off : off);
            } else {
                DateTime_AddDays(&dt, off);
            }
        }
        ret.s.b3 = ((u8 *)&dt)[4];
        ret.s.b2 = ((u8 *)&dt)[3];
    }
    return ret;
}

extern "C" EventDate EventRule_ResolveStart(Unk_0203f554_Sub *e, s32 year, EventDate cal, u32 id) {
    return EventRule_Resolve(e, year, cal, id);
}

extern "C" EventDate EventRule_ResolveEnd(Unk_0203f554_Sub *e, s32 year, EventDate cal, u32 id) {
    return EventRule_Resolve(e, year, cal, id);
}

extern "C" void EventDayList_Clear(EventEntryView *p, s32 n) {
    for (s32 i = 0; i < n; p++, i++) {
        p->id = 0x63;
        p->kind = 5;
    }
}

extern "C" s32 EventSchedule_IsBlocked(EventScheduleRule *t, EventDate cal, EventEntryView *e, EventEntryView *out, s32 count, s32 x, s32 y) {
    u32 lo;
    u32 hi;
    u32 olo;
    u32 ohi;
    s32 i;
    s32 kind;
    kind = t->kind;
    if (kind == 5) return 0;
    if (x == 0) {
        if (EventWeekSlots_IsSeenToday(e->id)) return 1;
    }
    if (kind == 4) {
        if (y != 0) {
            if (EventWeekSlots_IsUnavailable(e->id, cal.s.b0)) return 1;
        } else {
            if (EventWeekSlots_IsUnavailable(e->id, cal.s.b0) && EventWeekSlots_IsUnavailable(e->id, (u8)(cal.s.b0 - 1))) return 1;
        }
        if (LostChild_IsKatieDue() || LostChild_IsKaitlinDue()) return 1;
        return 0;
    }
    lo = e->a.w & ~0xff;
    hi = e->b.w & ~0xff;
    for (i = 0; i < count; out++, i++) {
        if (out->kind != 5 && kind >= out->kind) {
            olo = out->a.w & ~0xff;
            ohi = out->b.w & ~0xff;
            if ((lo < ohi && hi > olo) || (olo < hi && ohi > lo)) return 1;
        }
    }
    if (kind >= 2) {
        if (LostChild_IsKatieDue() || LostChild_IsKaitlinDue()) return 1;
    }
    if (kind >= 3) {
        if (((BlancaFaceRecord *)(gSaveBlancaFace))->isBlancaDue()) return 1;
    }
    switch (e->id) {
    case 0x3c:
        return EventWeek_IsInLyleWeek(cal);
    case 0x3d:
        return EventWeek_IsInUnkWeek(cal);
    default:
        return 0;
    }
}

extern "C" void Event_AdjustToDay(EventEntryView *e, EventDate cal) {
    u8 v = cal.s.b2;
    switch (e->id) {
    case 0x16:
    case 0x18:
    case 0x19:
        e->a.s.b2 = v;
        e->a.s.b1 = 6;
        e->b.s.b2 = v;
        e->b.s.b1 = 0x18;
        break;
    }
}

extern "C" s32 EventSchedule_Match(EventEntryView *out, EventScheduleRule *t, s32 year, EventDate cal) {
    s32 ok = 0;
    u32 key = cal.w & 0xffff0000;
    u32 id = t->id;
    out->id = id;
    out->kind = t->kind;
    out->a = EventRule_ResolveStart(&t->a, year, cal, id);
    if (out->a.w != 0 && (out->a.w & 0xffff0000) <= key) {
        out->b = EventRule_ResolveEnd(&t->b, year, cal, id);
        if (out->b.w != 0 && (out->b.w & 0xffff0000) >= key) {
            ok = 1;
        }
    }
    return ok;
}

extern "C" s32 EventSchedule_Collect(EventEntryView *out, ClockDateTimeCopy d, s32 x, s32 y) {
    EventScheduleRule *t;
    s32 count = 0;
    u32 year = ((u8 *)&d)[5];
    EventDate cal;
    EventEntryView e;
    u32 m = ((u8 *)&d)[4];
    cal.s.b3 = m;
    u32 dd = ((u8 *)&d)[3];
    cal.s.b2 = dd;
    cal.s.b1 = ((u8 *)&d)[2];
    cal.s.b0 = Date_GetWeekday(year, m, dd);
    EventDayList_Clear(out, 7);
    t = sEventSchedule;
    for (s32 j = 0; j < 99; t++, j++) {
        if (EventSchedule_Match(&e, t, year, cal)) {
            if (!EventSchedule_IsBlocked(t, cal, &e, out, count, x, y)) {
                Event_AdjustToDay(&e, cal);
                out[count].id = e.id;
                out[count].kind = e.kind;
                out[count].a = e.a;
                out[count].b = e.b;
                count++;
                if (count == 7) break;
            }
        }
    }
    return count;
}

extern "C" s32 EventSchedule_CollectDay(EventEntryView *a, ClockDateTimeCopy d, s32 x) {
    return EventSchedule_Collect(a, d, 0, x);
}

extern "C" s32 EventSchedule_CollectDayAll(EventEntryView *a, ClockDateTimeCopy d) {
    return EventSchedule_Collect(a, d, 1, 0);
}

extern "C" void Event_RefreshToday(s32 x) {
    ClockDateTimeWords d;
    d.words[0] = 0;
    d.words[1] = 0;
    Clock_GetDateTime(&d);
    EventSchedule_CollectDay((EventEntryView *)gTodayEvents.entries, *(ClockDateTimeCopy *)&d, x);
    gTodayEvents.date[2] = d.dt.year;
    gTodayEvents.date[1] = d.dt.month;
    gTodayEvents.date[0] = d.dt.day;
}

extern "C" void Event_RefreshIfDateChanged() {
    ClockDateTimeWords d;
    d.words[0] = 0;
    d.words[1] = 0;
    Clock_GetDateTime(&d);
    if (d.dt.year != gTodayEvents.date[2] || d.dt.month != gTodayEvents.date[1] || d.dt.day != gTodayEvents.date[0]) {
        Event_RefreshToday(0);
    }
}

extern "C" s32 Event_GetDaysSinceStart(u32 id) {
    s32 r = -1;
    EventDayEntry *e = EventDayList_Find(id, gTodayEvents.entries);
    if (e) {
        Unk_0203f42c_L l;
        l.w[0] = 0;
        l.w[1] = 0;
        l.w[2] = 0;
        l.w[3] = 0;
        Clock_GetDateTime(&l);
        l.b[2] = 0;
        l.b[1] = 0;
        l.b[0] = 0;
        u8 *e4 = (u8 *)&e->start;
        l.w[2] = 0;
        l.w[3] = 0;
        l.b[13] = l.b[5];
        l.b[12] = e4[3];
        l.b[11] = e4[2];
        r = DateTime_DiffDays(&l.w[2], &l);
    }
    return r;
}

extern "C" EventDayEntry *EventDayList_Find(u32 id, EventDayEntry *e) {
    EventDayEntry *r = NULL;
    for (s32 i = 0; i < 7; e++, i++) {
        if (e->eventId == id) {
            r = e;
            break;
        }
    }
    return r;
}

extern "C" s32 EventDayList_GetState(s32 a, u8 *p, EventDayEntry *tbl) {
    s32 r = 0;
    EventDayEntry *e = EventDayList_Find(a, tbl);
    if (e) {
        Unk_0203f3a0_L l;
        u32 z = 0;
        l.w[0] = z;
        l.b[3] = p[4];
        l.b[2] = p[3];
        l.b[1] = p[2];
        u32 lim = e->start;
        if (lim <= l.w[0]) {
            l.w[1] = z;
            l.w[2] = z;
            l.w[1] = z;
            l.w[2] = z;
            l.b[9] = p[5];
            l.b[8] = ((u8 *)e)[0xb];
            l.b[7] = ((u8 *)e)[0xa];
            l.b[6] = ((u8 *)e)[9];
            s32 v = DateTime_DiffMinutes(p, &l.w[1]);
            if (v > 0) {
                if (v <= 5) {
                    r = 3;
                } else {
                    r = 2;
                }
            }
        } else {
            r = 1;
        }
    }
    return r;
}

extern "C" s32 Event_GetStateAt(s32 a, u8 *p, s32 c) {
    s32 r = 0;
    u8 d1[8];
    u8 d2[8];
    u8 d3[8];
    u8 tbl[0x58];
    if (p[5] == gTodayEvents.date[2] && p[4] == gTodayEvents.date[1] && p[3] == gTodayEvents.date[0]) {
        if (c != 0 || Game_IsIntroPeriod() == 0) {
            MI_CpuCopy8(p, d1, 8);
            r = EventDayList_GetState(a, d1, gTodayEvents.entries);
        }
    } else {
        MI_CpuCopy8(p, d2, 8);
        ((void (*)(void *, void *, s32))EventSchedule_CollectDay)(tbl, d2, 0);
        MI_CpuCopy8(p, d3, 8);
        r = EventDayList_GetState(a, d3, (EventDayEntry *)tbl);
    }
    return r;
}

extern "C" s32 Event_GetState(s32 a, void *b, s32 c) {
    s32 r = 0;
    u8 buf[8];
    if (EventWeekSlots_IsSeenToday(a) == 0) {
        MI_CpuCopy8(b, buf, 8);
        r = Event_GetStateAt(a, buf, c);
        if (r == 1) {
            r = 0;
        }
    }
    return r;
}

extern "C" EventDayEntry *Event_GetTodayList(void) { return gTodayEvents.entries; }

extern "C" s32 EventSchedule_CollectAtNoon(EventEntryView *out, s32 n, u8 *p) {
    u32 p5;
    EventDate w;
    EventEntryView tmp;
    EventScheduleRule *e;
    s32 cnt;
    s32 zero;
    cnt = 0;
    p5 = p[5];
    w.s.b3 = p[4];
    w.s.b2 = p[3];
    w.s.b1 = 0xc;
    w.s.b0 = Date_GetWeekday(p5, p[4], p[3]);
    EventDayList_Clear(out, n);
    zero = 0;
    e = sEventSchedule;
    for (s32 i = 0; i < 99; e++, i++) {
        if (e->kind == 5) {
            continue;
        }
        if (EventSchedule_Match(&tmp, e, p5, w) == 0) {
            continue;
        }
        if (tmp.a.w >= w.w) {
            continue;
        }
        if (tmp.b.w <= w.w) {
            continue;
        }
        if (EventSchedule_IsBlocked(e, w, &tmp, out, cnt, 1, zero) != 0) {
            continue;
        }
        Event_AdjustToDay(&tmp, w);
        out[cnt].id = tmp.id;
        out[cnt].kind = tmp.kind;
        out[cnt].a.w = tmp.a.w;
        out[cnt].b.w = tmp.b.w;
        cnt++;
        if (cnt == n) {
            break;
        }
    }
    return cnt;
}

extern "C" void Event_GetRange(s32 *a, s32 *b, u32 id) {
    EventDayEntry *e = EventDayList_Find(id, gTodayEvents.entries);
    if (e) {
        *a = e->start;
        *b = e->end;
    } else {
        *a = 1;
        *b = 1;
    }
}

BOOL EventCalendarModule::onCreate() {
    if (gCommManager->isOnline() == 0) {
        if (sEventsOnlineRefresh) {
            Event_RefreshToday(0);
        }
        sEventsOnlineRefresh = 0;
    } else {
        Event_RefreshToday(0);
        sEventsOnlineRefresh = 1;
    }
    return TRUE;
}

BOOL EventCalendarModule::onExecute() {
    if (Backup_GetStatus(gBackup) != 3) {
        EventWeekSlots_UpdateToday(((s32 (*)(void *))Event_RefreshIfDateChanged)(this));
    }
    return TRUE;
}

BOOL EventCalendarModule::onDraw() { return TRUE; }

BOOL EventCalendarModule::onDelete() { return TRUE; }

extern "C" BOOL Game_IsIntroPeriod(void) {
    BOOL r = FALSE;
    if (GameStart_IsActive()) {
        r = TRUE;
    } else {
        PlayerData *p = PlayerData_GetCurrent();
        if (p == NULL || p->testFlag(1) != 0) {
            r = TRUE;
        }
    }
    return r;
}
