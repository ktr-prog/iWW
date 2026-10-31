#ifndef PROTO_PROTO_MAIN_UNK_02040050_H
#define PROTO_PROTO_MAIN_UNK_02040050_H


#include "types.h"
#include "sys/ClockDateTime.h"
#ifdef __cplusplus
#include "game/EventWeekSlots.h"
#include "game/Unk_0203fe18_B4.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sEventWeekSeenMask
extern u16 sEventWeekSeenMask;
#endif
#ifndef PROTO_LOCAL_EventWeekSlots_MarkTodaySeen
void EventWeekSlots_MarkTodaySeen(u32 id);
#endif
#ifndef PROTO_LOCAL_Date_GetWeekBoundary
void Date_GetWeekBoundary(ClockDateTime *d, s32 n);
#endif
#ifndef PROTO_LOCAL_EventWeek_SetLyleWeek
void EventWeek_SetLyleWeek(u32 x, s32 flag);
#endif
#ifndef PROTO_LOCAL_EventWeekSlots_IsSeenToday
BOOL EventWeekSlots_IsSeenToday(u32 id);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_EventWeek_IsInLyleWeek
BOOL EventWeek_IsInLyleWeek(Unk_0203fe18_B4 d);
#endif
#ifndef PROTO_LOCAL_EventWeek_IsInUnkWeek
BOOL EventWeek_IsInUnkWeek(Unk_0203fe18_B4 d);
#endif
#ifndef PROTO_LOCAL_EventWeekSlots_SyncToday
void EventWeekSlots_SyncToday(EventWeekSlots *s);
#endif
#ifndef PROTO_LOCAL_EventWeekSlots_RefreshSeenMask
void EventWeekSlots_RefreshSeenMask(EventWeekSlots *s);
#endif
}
#endif

#endif
