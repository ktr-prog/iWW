#ifndef PROTO_PROTO_MAIN_UNK_020406C4_H
#define PROTO_PROTO_MAIN_UNK_020406C4_H


#include "types.h"
#include "sys/ClockDateTime.h"
#ifdef __cplusplus
#include "game/EventWeekSlots.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_WeekVisitors_FindFreeDays
s32 WeekVisitors_FindFreeDays(void *, s32 *out, ClockDateTime *x);
#endif
#ifndef PROTO_LOCAL_WeekVisitors_PickFreeDay
s32 WeekVisitors_PickFreeDay(void *, s32 *arr, s32 n);
#endif
#ifndef PROTO_LOCAL_WeekVisitors_ListContains
BOOL WeekVisitors_ListContains(void *, u8 *p, u32 v);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_WeekVisitors_PickRandom
s32 WeekVisitors_PickRandom(EventWeekSlots *s, u8 *a);
#endif
}
#endif

#endif
