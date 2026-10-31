#ifndef PROTO_PROTO_MAIN_UNK_0209CB74_H
#define PROTO_PROTO_MAIN_UNK_0209CB74_H


#include "types.h"
#include "nitro/os_rtc.h"
#include "sys/ClockDateTime.h"
#include "types64.h"
struct ClockDateInit;
struct ClockOffset;
#ifndef __cplusplus
typedef struct ClockDateInit ClockDateInit;
typedef struct ClockOffset ClockOffset;
#endif
#ifdef __cplusplus
#include "save/SaveData.h"
class LetterStorageBlock;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Clock_ReadRtc
void Clock_ReadRtc(RTCDate *d, RTCTime *t);
#endif
#ifndef PROTO_LOCAL_Clock_ReadAdjusted
void Clock_ReadAdjusted(s32 *out);
#endif
#ifndef PROTO_LOCAL_Clock_GetDateTime
void Clock_GetDateTime(ClockDateTime *p);
#endif
#ifndef PROTO_LOCAL_DateTime_Compare
s32 DateTime_Compare(ClockDateTime *a, ClockDateTime *b, u32 mask);
#endif
#ifndef PROTO_LOCAL_DateTime_DiffDays
s32 DateTime_DiffDays(ClockDateTime *a, ClockDateTime *b);
#endif
#ifndef PROTO_LOCAL_DateTime_DiffMinutes
s32 DateTime_DiffMinutes(ClockDateTime *a, ClockDateTime *b);
#endif
#ifndef PROTO_LOCAL_DateTime_GetWeekStart
void DateTime_GetWeekStart(ClockDateTime *p, ClockDateTime *q);
#endif
#ifndef PROTO_LOCAL_DateTime_AddYears
void DateTime_AddYears(ClockDateTime *p, s32 n);
#endif
#ifndef PROTO_LOCAL_DateTime_AddMonths
void DateTime_AddMonths(ClockDateTime *p, s32 n);
#endif
#ifndef PROTO_LOCAL_DateTime_AddDays
void DateTime_AddDays(ClockDateTime *p, s32 n);
#endif
#ifndef PROTO_LOCAL_DateTime_AddHours
void DateTime_AddHours(ClockDateTime *p, s32 n);
#endif
#ifndef PROTO_LOCAL_DateTime_AddMinutes
void DateTime_AddMinutes(ClockDateTime *p, s32 n);
#endif
#ifndef PROTO_LOCAL_DateTime_AddSeconds
void DateTime_AddSeconds(ClockDateTime *p, s32 n);
#endif
#ifndef PROTO_LOCAL_DateTime_SubYears
void DateTime_SubYears(ClockDateTime *p, s32 n);
#endif
#ifndef PROTO_LOCAL_DateTime_SubMonths
void DateTime_SubMonths(ClockDateTime *p, s32 n);
#endif
#ifndef PROTO_LOCAL_DateTime_SubDays
void DateTime_SubDays(ClockDateTime *p, s32 n);
#endif
#ifndef PROTO_LOCAL_DateTime_SubHours
void DateTime_SubHours(ClockDateTime *p, s32 n);
#endif
#ifndef PROTO_LOCAL_DateTime_SubMinutes
void DateTime_SubMinutes(ClockDateTime *p, s32 n);
#endif
#ifndef PROTO_LOCAL_DateTime_SubSeconds
void DateTime_SubSeconds(ClockDateTime *t, u32 sub);
#endif
#ifndef PROTO_LOCAL_DateTime_Sub
void DateTime_Sub(ClockDateTime *t, ClockDateTime *p);
#endif
#ifndef PROTO_LOCAL_DateTime_IsInvalid
BOOL DateTime_IsInvalid(u8 *p);
#endif
#ifndef PROTO_LOCAL_DateTime_Make
void DateTime_Make(u8 *out, u8 *in, u8 a, u8 b, u8 c);
#endif
#ifndef PROTO_LOCAL_Clock_Init
void Clock_Init();
#endif
#ifndef PROTO_LOCAL_Clock_Update
void Clock_Update(u32 x);
#endif
#ifndef PROTO_LOCAL_Clock_GetDayMonth
void Clock_GetDayMonth(u8 *out);
#endif
#ifndef PROTO_LOCAL_Clock_GetCalendarKey
void Clock_GetCalendarKey(u8 *out);
#endif
#ifndef PROTO_LOCAL_Clock_GetDate
void Clock_GetDate(u8 *out);
#endif
#ifndef PROTO_LOCAL_Clock_GetDateTimeCleared
void Clock_GetDateTimeCleared(u8 *out);
#endif
#ifndef PROTO_LOCAL_Clock_GetRtcDateTime
void Clock_GetRtcDateTime(ClockDateTime *out);
#endif
#ifndef PROTO_LOCAL_Clock_GetMinuteHour
void Clock_GetMinuteHour(u8 *out);
#endif
#ifndef PROTO_LOCAL_Clock_GetYear
u32 Clock_GetYear();
#endif
#ifndef PROTO_LOCAL_Clock_GetSecond
u32 Clock_GetSecond();
#endif
#ifndef PROTO_LOCAL_Clock_GetWeekday
s32 Clock_GetWeekday();
#endif
#ifndef PROTO_LOCAL_Date_GetWeekday
s32 Date_GetWeekday(u32 a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_Date_GetNthWeekdayDay
s32 Date_GetNthWeekdayDay(u32 a, u32 b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_Date_GetDaysInMonth
s32 Date_GetDaysInMonth(u32 y, u32 m);
#endif
#ifndef PROTO_LOCAL_Date_IsAfterOrEqual
s32 Date_IsAfterOrEqual(u8 *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_Date_DaysBetween
s32 Date_DaysBetween(u8 *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_Clock_GetTimeOfDay
s32 Clock_GetTimeOfDay();
#endif
#ifndef PROTO_LOCAL_DateTime_GetSeasonPeriod
s32 DateTime_GetSeasonPeriod(u8 *p);
#endif
#ifndef PROTO_LOCAL_DateTime_GetWeatherPeriod
s32 DateTime_GetWeatherPeriod(u8 *p);
#endif
#ifndef PROTO_LOCAL_Clock_GetTimeSeed
u32 Clock_GetTimeSeed();
#endif
#ifndef PROTO_LOCAL_ClockOffset_CalcMinutes
s32 ClockOffset_CalcMinutes(void *unused, u64 *b);
#endif
#ifndef PROTO_LOCAL_ClockOffset_CalcSeconds
s32 ClockOffset_CalcSeconds(void *unused, u8 *b);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SaveData_Apply
void SaveData_Apply(SaveData *p);
#endif
#ifndef PROTO_LOCAL_LetterStorage_IsValid
BOOL LetterStorage_IsValid(LetterStorageBlock *p);
#endif
#ifndef PROTO_LOCAL_LetterStorage_MarkInterrupted
void LetterStorage_MarkInterrupted(LetterStorageBlock *p);
#endif
#ifndef PROTO_LOCAL_LetterStorage_MarkValid
void LetterStorage_MarkValid(LetterStorageBlock *p);
#endif
#ifndef PROTO_LOCAL_Date_GetSeasonPeriod
s32 Date_GetSeasonPeriod(ClockDateInit *p);
#endif
#ifndef PROTO_LOCAL_Date_GetWeatherPeriod
s32 Date_GetWeatherPeriod(ClockDateInit *p);
#endif
#ifndef PROTO_LOCAL_ClockOffset_Clear
void ClockOffset_Clear(ClockOffset *t);
#endif
}
#ifndef PROTO_LOCAL_gClock
extern s32 gClock[7];
#endif
#endif

#endif
