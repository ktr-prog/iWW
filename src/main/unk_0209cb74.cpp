#include "types.h"
#include "sys/ClockDateTime.h"
#include "nitro/os_rtc.h"
#include "save/SaveRecord4.h"
#include "town/VisitorPos.h"
#include "ui/HudController.h"
#include "item/LetterStorage.h"
#include "save/SaveData.h"
#include "town/KatieVisitState.h"
#include "town/PeteFallState.h"
#include "proto/main/unk_0206d988.h"
#include "proto/autoload_2/unk_0211d20c.h"
#include "proto/main/unk_0202e840.h"
#include "proto/main/unk_02034048.h"
#include "proto/main/unk_020407fc.h"
#include "proto/main/unk_020514a4.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_02082d74.h"
#include "proto/main/unk_020850e0.h"
#include "proto/main/unk_02089fbc.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_0209c3e0.h"
#include "proto/main/unk_0209cb74.h"
#include "proto/main/unk_020b0e60.h"

struct ClockOffset {
    s32 minutes;
    s16 seconds;
};

struct ClockDateInit {
    u8 day, month, year, pad_03;
    ClockDateInit() {
        day = 1;
        month = 1;
        year = 0;
        pad_03 = 0;
    }
};

union MinuteHour {
    struct {
        u8 minute;
        u8 hour;
    };
    u16 v;
};


extern const u8 sDaysInMonth[2][12];
extern const u16 sWeatherPeriodEnds[20];
extern const u16 sSeasonPeriodEnds[24];
extern const u16 sDaysBeforeMonth[26];

extern SaveData gSaveData;
extern s32 gClock[7];

extern "C" {
void Town_CheckDayChange();
void RTC_GetDateTime(void *date, void *time);
void MI_CpuCopy8(void *src, void *dst, u32 size);
void DateTime_SubSeconds(ClockDateTime *p, u32 n);
void DateTime_SubMinutes(ClockDateTime *p, s32 n);
void DateTime_SubHours(ClockDateTime *p, s32 n);
void DateTime_SubDays(ClockDateTime *p, s32 n);
void DateTime_SubMonths(ClockDateTime *p, s32 n);
void DateTime_SubYears(ClockDateTime *p, s32 n);
void DateTime_AddSeconds(ClockDateTime *p, s32 n);
void DateTime_AddMinutes(ClockDateTime *p, s32 n);
void DateTime_AddHours(ClockDateTime *p, s32 n);
void DateTime_AddDays(ClockDateTime *p, s32 n);
void DateTime_AddMonths(ClockDateTime *p, s32 n);
void DateTime_AddYears(ClockDateTime *p, s32 n);
s32 DateTime_DiffMinutes(ClockDateTime *a, ClockDateTime *b);
s32 DateTime_DiffDays(ClockDateTime *a, ClockDateTime *b);
void Clock_ReadAdjusted(s32 *out);
void Clock_ReadRtc(RTCDate *d, RTCTime *t);
s32 Date_GetWeatherPeriod(ClockDateInit *t);
s32 Date_GetSeasonPeriod(ClockDateInit *t);
s32 Date_IsAfterOrEqual(u8 *a, u8 *b);
s32 Date_DaysBetween(u8 *a, u8 *b);
void Clock_GetMinuteHour(u8 *out);
void Clock_GetRtcDateTime(ClockDateTime *out);
void Clock_GetDate(u8 *out);
s32 Clock_GetWeekday();
s32 Date_GetDaysInMonth(u32 y, u32 m);
s32 Date_GetWeekday(u32 a, u32 b, u32 c);

void SaveVillagers_ResetMoods(void *);
void Weather_Apply(void *);
void Town_OnLoad(void);
void NookShop_UpdateDaily(void *, s32);
void SaveVillagers_PickGreeter(void *);
void SaveVillagers_InitTalkUrges(void *, void *);
void VillagerStates_ResetIdleFrames(void);
void VillagerStates_ClearUnk1dBit2(void);
void VillagerStates_ResetTalkRepeats(void);
void VillagerStates_ClearUnk1dBit0(void);
}

static inline void Unk_0209cdf8_Norm(MinuteHour *p, u16 *out) {
    while (p->hour >= 0x18) {
        p->hour -= 0x18;
    }
    *out = p->v;
}

static inline s32 Unk_0209d0e4_Abs(s32 v) {
    if (v < 0) {
        v = -v;
    }
    return v;
}

struct ZeroedClockDateTime : ClockDateTime {
    ZeroedClockDateTime() { ((u32 *)this)[0] = 0; ((u32 *)this)[1] = 0; }
};
struct ZeroedClockDateTime2 : ZeroedClockDateTime {
    ZeroedClockDateTime2() { ((u32 *)this)[0] = 0; ((u32 *)this)[1] = 0; }
};
static inline s16 Unk_0209d4c0_Abs16(s16 v) {
    if (v < 0) {
        v = -v;
    }
    return v;
}

class LetterStorageBlock {
public:
    LetterStorage storages[4];
    u8 validMarker;
};

extern "C" void SaveData_Apply(SaveData *p) {
    ((SaveRecord4 *)p->unk_15fc5)->expireDate();
    NpcSpawn_ResetAll();
    NpcNetRecords_InitVillagers();
    SaveVillagers_ResetMoods(p->villagers);
    TownSessionState_Reset(TownSessionState_Get());
    RoomFtrState_ResetAll();
    RoomObjSync_Reset();
    BuildingStates_Reset();
    BuildingOccupancy_Reset();
    RoomWallFloor_ClearScenes();
    EventWeekSlots_OnLoad(p->eventWeekSlots);
    Weather_Apply(&p->weather);
    Town_OnLoad();
    NookShop_UpdateDaily(p->nookShop, 0);
    Melody_SetPacked((u32 *)&p->townTune);
    TownSessionState_GetKatieState(TownSessionState_Get())->pickKatiePos();
    TownSessionState_GetPeteFall(TownSessionState_Get())->clear();
    TownSessionState_CheckTortimerReward(TownSessionState_Get());
    ((VisitorPos *)(TownSessionState_GetVisitorPos(TownSessionState_Get())))->pickRandomPos();
    ((HudCountdown *)(Hud_GetCountdown()))->start(0, 1);
    LowBattery_Reset();
    SaveVillagers_PickGreeter(p->villagers);
    MenuCtrl_InitKeyboardState();
    HouseVisitor_ClearPresent();
    SaveVillagers_InitTalkUrges(p->villagers, PlayerData_GetCurrent());
    VillagerStates_ResetIdleFrames();
    VillagerStates_ClearUnk1dBit2();
    VillagerStates_ResetTalkRepeats();
    VillagerStates_ClearUnk1dBit0();
}

extern "C" BOOL LetterStorage_IsValid(LetterStorageBlock *p) {
    if (p->validMarker == 2) {
        return TRUE;
    }
    return FALSE;
}

extern "C" void LetterStorage_MarkInterrupted(LetterStorageBlock *p) {
    p->validMarker = 0x1c;
}

extern "C" void LetterStorage_MarkValid(LetterStorageBlock *p) {
    p->validMarker = 2;
}

extern "C" void Clock_ReadRtc(RTCDate *d, RTCTime *t) {
    RTC_GetDateTime(d, t);
    if (d->year == 0 && d->month == 1 && d->day == 1) {
        d->week = 6;
    }
}

extern "C" void Clock_ReadAdjusted(s32 *out) {
    RTCDate d;
    RTCTime t;
    Clock_ReadRtc(&d, &t);
    RTCDate d2 = d;
    out[0] = d2.year; out[1] = d2.month; out[2] = d2.day; out[3] = d2.week;
    RTCTime t2 = t;
    out[4] = t2.hour; out[5] = t2.minute; out[6] = t2.second;
    ClockOffset *off = (ClockOffset *)gSaveData.clockOffset;
    s32 a = off->minutes;
    s16 b = off->seconds;
    ZeroedClockDateTime2 dtl;
    dtl.year = d.year;
    dtl.month = d.month;
    dtl.day = d.day;
    dtl.hour = t.hour;
    dtl.minute = t.minute;
    dtl.second = t.second;
    if (a < 0) {
        DateTime_SubMinutes(&dtl, Unk_0209d0e4_Abs(a));
    } else {
        DateTime_AddMinutes(&dtl, a);
    }
    if (b < 0) {
        b = Unk_0209d4c0_Abs16(b);
        DateTime_SubSeconds(&dtl, b);
    } else {
        DateTime_AddSeconds(&dtl, b);
    }
    d.year = dtl.year;
    d.month = dtl.month;
    d.day = dtl.day;
    t.hour = dtl.hour;
    t.minute = dtl.minute;
    t.second = dtl.second;
    d.week = Date_GetWeekday((u8)d.year, (u8)d.month, (u8)d.day);
    RTCDate d3 = d;
    out[0] = d3.year; out[1] = d3.month; out[2] = d3.day; out[3] = d3.week;
    RTCTime t3 = t;
    out[4] = t3.hour; out[5] = t3.minute; out[6] = t3.second;
}

extern "C" void Clock_GetDateTime(ClockDateTime *p) {
    s32 *t = gClock + 4;
    s32 *d = gClock;
    p->year = d[0];
    p->month = d[1];
    p->day = d[2];
    p->hour = t[0];
    p->minute = t[1];
    p->second = t[2];
}

extern "C" s32 DateTime_Compare(ClockDateTime *a, ClockDateTime *b, u32 mask) {
    if (mask & 0x20) {
        if (a->year < b->year) return -1;
        if (a->year > b->year) return 1;
    }
    if (mask & 0x10) {
        if (a->month < b->month) return -1;
        if (a->month > b->month) return 1;
    }
    if (mask & 0x8) {
        if (a->day < b->day) return -1;
        if (a->day > b->day) return 1;
    }
    if (mask & 0x4) {
        if (a->hour < b->hour) return -1;
        if (a->hour > b->hour) return 1;
    }
    if (mask & 0x2) {
        if (a->minute < b->minute) return -1;
        if (a->minute > b->minute) return 1;
    }
    if (mask & 0x1) {
        if (a->second < b->second) return -1;
        if (a->second > b->second) return 1;
    }
    return 0;
}

extern "C" s32 DateTime_DiffDays(ClockDateTime *a, ClockDateTime *b) {
    struct L {
        u8 x[3];
        u8 pad;
        u8 y[3];
    } l;
    l.x[2] = b->year;
    l.x[1] = b->month;
    l.x[0] = b->day;
    l.y[2] = a->year;
    l.y[1] = a->month;
    l.y[0] = a->day;
    return Date_DaysBetween((u8 *)&l.x, (u8 *)&l.y);
}

extern "C" s32 DateTime_DiffMinutes(ClockDateTime *a, ClockDateTime *b) {
    s32 days = DateTime_DiffDays(a, b);
    s32 t = (b->hour - a->hour) * 60 - a->minute;
    t += days * 0x5a0;
    return t + b->minute;
}

extern "C" void DateTime_GetWeekStart(ClockDateTime *p, ClockDateTime *q) {
    if (q) {
        s32 dow = Date_GetWeekday((u8)p->year, (u8)p->month, (u8)p->day);
        if (q != p) {
            MI_CpuCopy8(p, q, 8);
        }
        DateTime_SubDays(q, dow);
        q->hour = 0;
        q->minute = 0;
        q->second = 0;
    }
}

extern "C" void DateTime_AddYears(ClockDateTime *p, s32 n) {
    s32 y = p->year + n;
    if (y > 99) {
        y -= 100;
    }
    p->year = y;
}

extern "C" void DateTime_AddMonths(ClockDateTime *p, s32 n) {
    s32 s = p->month + n;
    if (s > 12) {
        DateTime_AddYears(p, s / 12);
        s = s % 12;
    }
    p->month = s;
}

extern "C" void DateTime_AddDays(ClockDateTime *p, s32 n) {
    s32 dim = Date_GetDaysInMonth(p->year, p->month);
    s32 d = p->day + n;
    while (d > dim) {
        d -= dim;
        DateTime_AddMonths(p, 1);
        dim = Date_GetDaysInMonth(p->year, p->month);
    }
    p->day = d;
}

extern "C" void DateTime_AddHours(ClockDateTime *p, s32 n) {
    s32 s = p->hour + n;
    if (s >= 24) {
        DateTime_AddDays(p, s / 24);
        s = s % 24;
    }
    p->hour = s;
}

extern "C" void DateTime_AddMinutes(ClockDateTime *p, s32 n) {
    s32 s = p->minute + n;
    if (s >= 60) {
        DateTime_AddHours(p, s / 60);
        s = s % 60;
    }
    p->minute = s;
}

extern "C" void DateTime_AddSeconds(ClockDateTime *p, s32 n) {
    s32 s = p->second + n;
    if (s >= 60) {
        DateTime_AddMinutes(p, s / 60);
        s = s % 60;
    }
    p->second = s;
}

extern "C" void DateTime_SubYears(ClockDateTime *p, s32 n) {
    s32 y = p->year - n;
    if (y < 0) {
        y += 100;
    }
    p->year = y;
}

extern "C" void DateTime_SubMonths(ClockDateTime *p, s32 n) {
    s32 m = p->month - n;
    if (m < 1) {
        s32 k;
        if (m == 0) {
            m = 12;
            k = 1;
        } else {
            m = Unk_0209d0e4_Abs(m);
            k = m / 12 + 1;
            m = 12 - m % 12;
        }
        DateTime_SubYears(p, k);
    }
    p->month = m;
}

extern "C" void DateTime_SubDays(ClockDateTime *p, s32 n) {
    s32 d = p->day;
    s32 dim;
    if (p->month == 1) {
        dim = Date_GetDaysInMonth(p->year, 12);
    } else {
        dim = Date_GetDaysInMonth(p->year, (u8)(p->month - 1));
    }
    d -= n;
    while (d <= 0) {
        if (d == 0) {
            d = dim;
        } else {
            d += dim;
        }
        DateTime_SubMonths(p, 1);
        if (p->month == 1) {
            dim = Date_GetDaysInMonth(p->year, 12);
        } else {
            dim = Date_GetDaysInMonth(p->year, (u8)(p->month - 1));
        }
    }
    p->day = d;
}

extern "C" void DateTime_SubHours(ClockDateTime *p, s32 n) {
    s32 r = p->hour - n;
    if (r < 0) {
        s32 q;
        r = Unk_0209d0e4_Abs(r);
        q = r / 24 + 1;
        r = 24 - r % 24;
        if (r == 24) {
            r = 0;
            q--;
        }
        DateTime_SubDays(p, q);
    }
    p->hour = r;
}

extern "C" void DateTime_SubMinutes(ClockDateTime *p, s32 n) {
    s32 r = p->minute - n;
    if (r < 0) {
        s32 q;
        r = Unk_0209d0e4_Abs(r);
        q = r / 60 + 1;
        r = 60 - r % 60;
        if (r == 60) {
            r = 0;
            q--;
        }
        DateTime_SubHours(p, q);
    }
    p->minute = r;
}

extern "C" void DateTime_SubSeconds(ClockDateTime *t, u32 sub) {
    s32 r5 = t->second - sub;
    s32 r4;
    if (r5 < 0) {
        if (r5 < 0) {
            r5 = -r5;
        }
        r4 = r5 / 0x3c + 1;
        r5 = 0x3c - r5 % 0x3c;
        if (r5 == 0x3c) {
            r5 = 0;
            r4 = r4 - 1;
        }
        DateTime_SubMinutes(t, r4);
    }
    t->second = r5;
}

extern "C" void DateTime_Sub(ClockDateTime *t, ClockDateTime *p) {
    DateTime_SubSeconds(t, p->second);
    DateTime_SubMinutes(t, p->minute);
    DateTime_SubHours(t, p->hour);
    DateTime_SubDays(t, p->day);
    DateTime_SubMonths(t, p->month);
    DateTime_SubYears(t, p->year);
}

extern "C" BOOL DateTime_IsInvalid(u8 *p) {
    BOOL bad = FALSE;
    BOOL ok = FALSE;
    if (p[0] < 0x3c && p[1] < 0x3c && p[2] < 0x18 && p[3] >= 1 && p[3] <= 0x1f && p[4] >= 1 && p[4] <= 0xc) {
        ok = TRUE;
    }
    if (ok) {
        if (p[5] <= 0x63) {
            bad = TRUE;
        }
    }
    if (bad == 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" void DateTime_Make(u8 *out, u8 *in, u8 a, u8 b, u8 c) {
    out[5] = in[2];
    out[4] = in[1];
    out[3] = in[0];
    out[2] = a;
    out[1] = b;
    out[0] = c;
}

extern "C" void Clock_Init() {
    RTC_Init();
    Clock_ReadAdjusted(gClock);
}

extern "C" void Clock_Update(u32 x) {
    Clock_ReadAdjusted(gClock);
    if (x == 0) {
        Town_CheckDayChange();
    }
}

extern "C" void Clock_GetDayMonth(u8 *out) {
    out[0] = gClock[2];
    out[1] = gClock[1];
}

extern "C" void Clock_GetCalendarKey(u8 *out) {
    out[0] = gClock[3];
    out[1] = gClock[4];
    out[2] = gClock[2];
    out[3] = gClock[1];
}

extern "C" void Clock_GetDate(u8 *out) {
    out[0] = gClock[2];
    out[1] = gClock[1];
    out[2] = gClock[0];
    out[3] = 0;
}

extern "C" void Clock_GetDateTimeCleared(u8 *out) {
    s32 *const q = gClock + 4;
    *(u32 *)out = 0;
    *(u32 *)(out + 4) = 0;
    out[5] = gClock[0];
    out[4] = gClock[1];
    out[3] = gClock[2];
    out[2] = q[0];
    out[1] = q[1];
    out[0] = q[2];
}

extern "C" void Clock_GetRtcDateTime(ClockDateTime *out) {
    RTCDate a;
    RTCTime b;
    Clock_ReadRtc(&a, &b);
    *out = ClockDateTime();
    out->year = a.year;
    out->month = a.month;
    out->day = a.day;
    out->hour = b.hour;
    out->minute = b.minute;
    out->second = b.second;
}

extern "C" void Clock_GetMinuteHour(u8 *out) {
    s32 *const p = gClock + 4;
    out[0] = p[1];
    out[1] = p[0];
}

extern "C" u32 Clock_GetYear() {
    return gClock[0];
}

extern "C" u32 Clock_GetSecond() {
    return gClock[6];
}

extern "C" s32 Clock_GetWeekday() {
    return gClock[3];
}

extern "C" s32 Date_GetWeekday(u32 a, u32 b, u32 c) {
    u8 l1[4];
    u8 l2[4];
    l1[2] = a;
    l1[1] = b;
    l1[0] = c;
    Clock_GetDate(l2);
    s32 v = Date_DaysBetween(l1, l2);
    s32 m = (v < 0 ? -v : v) % 7;
    if (v < 0) {
        m = 7 - m;
    }
    s32 e = Clock_GetWeekday();
    return (e + m) % 7;
}

extern "C" s32 Date_GetNthWeekdayDay(u32 a, u32 b, s32 c, s32 d) {
    s32 r = -1;
    s32 x;
    s32 w = Date_GetWeekday(a, b, 1);
    s32 y;
    if (c < w) {
        y = c - w + 8;
    } else {
        y = c + 1 - w;
    }
    x = y + (d - 1) * 7;
    if (x < Date_GetDaysInMonth(a, b)) {
        r = x;
    }
    return r;
}

extern "C" s32 Date_GetDaysInMonth(u32 y, u32 m) {
    s32 i = ((y & 3) == 0 ? 0 : 12) + (s32)m - 1;
    if (i < 0) return 0;
    if (i >= 24) return (u8)sWeatherPeriodEnds[0];
    return (&sDaysInMonth[0][0])[i];
}

extern "C" void Time_AddHourMinute(MinuteHour a, MinuteHour b, u16 *out) {
    MinuteHour t = a;
    t.minute += b.minute;
    t.hour += b.hour;
    while (t.minute >= 0x3c) {
        t.hour++;
        t.minute -= 0x3c;
    }
    Unk_0209cdf8_Norm(&t, out);
}

extern "C" s32 Date_IsAfterOrEqual(u8 *a, u8 *b) {
    BOOL r = TRUE;
    u32 y = b[2];
    u32 x = a[2];
    if (x < y) {
        r = FALSE;
    } else if (x == y) {
        y = b[1];
        x = a[1];
        if (x < y) {
            r = FALSE;
        } else if (x == y) {
            x = a[0];
            y = b[0];
            if (x < y) {
                r = FALSE;
            }
        }
    }
    return r;
}

extern "C" s32 Date_DaysBetween(u8 *a, u8 *b) {
    s32 sign;
    s32 rem;
    s32 ex;
    s32 dy;
    s32 d0;
    s32 m0;
    s32 d1;
    s32 m1;
    s32 y0;
    s32 y1;
    s32 days;
    const u16 (*tbl)[13] = (const u16 (*)[13])sDaysBeforeMonth;
    sign = 1;
    if (Date_IsAfterOrEqual(a, b)) {
        d0 = b[0];
        m0 = b[1];
        y0 = b[2];
        d1 = a[0];
        m1 = a[1];
        y1 = a[2];
    } else {
        d0 = a[0];
        m0 = a[1];
        y0 = a[2];
        d1 = b[0];
        m1 = b[1];
        y1 = b[2];
        sign = -1;
    }
    dy = y1 - y0;
    rem = dy & 3;
    y0 &= 3;
    ex = ((4 - y0) & 3) < rem ? 1 : 0;
    days = ex + ((dy >> 2) * 0x5b5 + rem * 0x16d);
    days += d1 - 1;
    days += tbl[(y1 & 3) == 0 ? 1 : 0][m1 - 1];
    days -= d0 - 1;
    days -= tbl[y0 == 0 ? 1 : 0][m0 - 1];
    return days * sign;
}

extern "C" s32 Clock_GetTimeOfDay() {
    u8 t[4];
    Clock_GetMinuteHour(t);
    u32 h = t[1];
    if (h < 5) {
        return 3;
    }
    if (h < 0xc) {
        return 0;
    }
    if (h < 0x11) {
        return 1;
    }
    return 2;
}

extern "C" s32 Date_GetSeasonPeriod(ClockDateInit *p) {
    u8 s[2];
    u16 v;
    s32 r;
    const u16 *pt;
    s32 i;
    r = 0;
    s[1] = p->month;
    s[0] = p->day;
    v = *(u16 *)s;
    pt = sSeasonPeriodEnds;
    i = r;
    for (; i < 0x17; pt++, i++) {
        if (v <= *pt) {
            r = i;
            break;
        }
    }
    return r;
}

extern "C" s32 DateTime_GetSeasonPeriod(u8 *p) {
    ClockDateInit t;
    t.year = p[5];
    t.month = p[4];
    t.day = p[3];
    return Date_GetSeasonPeriod(&t);
}

extern "C" s32 Date_GetWeatherPeriod(ClockDateInit *p) {
    u8 s[2];
    u16 v;
    s32 r;
    const u16 *pt;
    s32 i;
    r = 0;
    s[1] = p->month;
    s[0] = p->day;
    v = *(u16 *)s;
    pt = sWeatherPeriodEnds;
    i = r;
    for (; i < 0x13; pt++, i++) {
        if (v <= *pt) {
            r = i;
            break;
        }
    }
    return r;
}

extern "C" s32 DateTime_GetWeatherPeriod(u8 *p) {
    ClockDateInit t;
    t.year = p[5];
    t.month = p[4];
    t.day = p[3];
    return Date_GetWeatherPeriod(&t);
}

extern "C" u32 Clock_GetTimeSeed() {
    s32 *const a = gClock + 4;
    return a[1] | ((gClock[2] << 8) | ((a[2] << 24) | (a[0] << 16)));
}

extern "C" void ClockOffset_Clear(ClockOffset *t) {
    t->minutes = 0;
    t->seconds = 0;
}

extern "C" s32 ClockOffset_CalcMinutes(void *unused, u64 *b) {
    ClockDateTime t;
    Clock_GetRtcDateTime(&t);
    if (*(u64 *)&t < *b) {
        return DateTime_DiffMinutes(&t, (ClockDateTime *)b);
    }
    return -DateTime_DiffMinutes((ClockDateTime *)b, &t);
}

extern "C" s32 ClockOffset_CalcSeconds(void *unused, u8 *b) {
    ClockDateTime t;
    Clock_GetRtcDateTime(&t);
    return (s16)(b[0] - t.second);
}

extern const u8 sDaysInMonth[2][12];
extern const u16 sWeatherPeriodEnds[20];
extern const u16 sSeasonPeriodEnds[24];
extern const u16 sDaysBeforeMonth[26];
extern s32 gClock[7];

const u8 sDaysInMonth[2][12] = {
    { 0x1f, 0x1d, 0x1f, 0x1e, 0x1f, 0x1e, 0x1f, 0x1f, 0x1e, 0x1f, 0x1e, 0x1f },
    { 0x1f, 0x1c, 0x1f, 0x1e, 0x1f, 0x1e, 0x1f, 0x1f, 0x1e, 0x1f, 0x1e, 0x1f },
};

const u16 sWeatherPeriodEnds[20] = {
    0x0104, 0x0217, 0x0218, 0x031f, 0x0408, 0x060f, 0x0716, 0x071f, 0x081f, 0x090f,
    0x091e, 0x0b0e, 0x0b18, 0x0b19, 0x0c09, 0x0c0a, 0x0c17, 0x0c1e, 0x0c1f, 0
};

const u16 sSeasonPeriodEnds[24] = {
    0x0203, 0x0211, 0x0218, 0x031f, 0x0403, 0x0408, 0x0716, 0x090f, 0x091e, 0x0a04, 0x0a0a, 0x0a10,
    0x0a14, 0x0a19, 0x0a1e, 0x0b02, 0x0b09, 0x0b0d, 0x0b13, 0x0b19, 0x0c01, 0x0c0a, 0x0c1f, 0
};

const u16 sDaysBeforeMonth[26] = {
    0x0000, 0x001f, 0x003b, 0x005a, 0x0078, 0x0097, 0x00b5, 0x00d4, 0x00f3, 0x0111, 0x0130, 0x014e, 0x016d,
    0x0000, 0x001f, 0x003c, 0x005b, 0x0079, 0x0098, 0x00b6, 0x00d5, 0x00f4, 0x0112, 0x0131, 0x014f, 0x016e
};

s32 gClock[7];
