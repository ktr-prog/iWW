#ifndef PROTO_PROTO_MAIN_UNK_0203F104_H
#define PROTO_PROTO_MAIN_UNK_0203F104_H


#include "types.h"
#include "game/EventDayEntry.h"
#include "sys/ClockDateTime.h"
#include "sys/ProcProfile.h"
struct ClockDateTimeCopy;
struct EventEntryView;
union EventDate;
#ifndef __cplusplus
typedef struct ClockDateTimeCopy ClockDateTimeCopy;
typedef struct EventEntryView EventEntryView;
#endif
#ifdef __cplusplus
#include "game/EventCalendarModule.h"
#include "game/EventScheduleRule.h"
#include "game/EventWeekSlots.h"
class EventDayList;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_EventWeekSlots_MarkPlayer
void EventWeekSlots_MarkPlayer(u32 id);
#endif
#ifndef PROTO_LOCAL_EventWeekSlots_IsUnavailable
BOOL EventWeekSlots_IsUnavailable(u32 id, s32 idx);
#endif
#ifndef PROTO_LOCAL_Villager_IsSettledExcept
BOOL Villager_IsSettledExcept(void *a, s32 b);
#endif
#ifndef PROTO_LOCAL_Event_RefreshToday
void Event_RefreshToday(s32 x);
#endif
#ifndef PROTO_LOCAL_Event_RefreshIfDateChanged
void Event_RefreshIfDateChanged();
#endif
#ifndef PROTO_LOCAL_Event_GetDaysSinceStart
s32 Event_GetDaysSinceStart(u32 id);
#endif
#ifndef PROTO_LOCAL_Event_GetStateAt
s32 Event_GetStateAt(s32 a, u8 *p, s32 c);
#endif
#ifndef PROTO_LOCAL_Event_GetState
s32 Event_GetState(s32 a, void *b, s32 c);
#endif
#ifndef PROTO_LOCAL_Event_GetRange
void Event_GetRange(s32 *a, s32 *b, u32 id);
#endif
#ifndef PROTO_LOCAL_Game_IsIntroPeriod
BOOL Game_IsIntroPeriod(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_EventWeekSlots_Get
EventWeekSlot *EventWeekSlots_Get(EventWeekSlots *s, s32 idx);
#endif
#ifndef PROTO_LOCAL_EventWeekSlots_GetToday
EventWeekSlot *EventWeekSlots_GetToday(EventWeekSlots *unused);
#endif
#ifndef PROTO_LOCAL_EventWeekSlot_Clear
void EventWeekSlot_Clear(EventWeekSlot *e);
#endif
#ifndef PROTO_LOCAL_EventWeekSlot_Set
void EventWeekSlot_Set(EventWeekSlot *e, u8 id, ClockDateTime *d);
#endif
#ifndef PROTO_LOCAL_EventWeekSlot_MarkAllPlayers
void EventWeekSlot_MarkAllPlayers(EventWeekSlot *e);
#endif
#ifndef PROTO_LOCAL_EventCalendarModule_New
EventCalendarModule *EventCalendarModule_New();
#endif
#ifndef PROTO_LOCAL_EventRule_ResolveDay
u8 EventRule_ResolveDay(Unk_0203f554_Sub *e, u32 year, EventDate cal, u32 mon, u32 id);
#endif
#ifndef PROTO_LOCAL_EventRule_GetPlayerBirthday
void EventRule_GetPlayerBirthday(Unk_0203f554_Sub *e, EventDate *out);
#endif
#ifndef PROTO_LOCAL_EventRule_GetVillagerBirthday
void EventRule_GetVillagerBirthday(Unk_0203f554_Sub *e, EventDate *out, s32 n);
#endif
#ifndef PROTO_LOCAL_EventRule_GetWeekSlotDate
EventDate EventRule_GetWeekSlotDate(Unk_0203f554_Sub *e, u32 id, EventDate cal);
#endif
#ifndef PROTO_LOCAL_EventRule_Resolve
EventDate EventRule_Resolve(Unk_0203f554_Sub *e, s32 year, EventDate cal, u32 id);
#endif
#ifndef PROTO_LOCAL_EventRule_ResolveStart
EventDate EventRule_ResolveStart(Unk_0203f554_Sub *e, s32 year, EventDate cal, u32 id);
#endif
#ifndef PROTO_LOCAL_EventRule_ResolveEnd
EventDate EventRule_ResolveEnd(Unk_0203f554_Sub *e, s32 year, EventDate cal, u32 id);
#endif
#ifndef PROTO_LOCAL_EventDayList_Clear
void EventDayList_Clear(EventEntryView *p, s32 n);
#endif
#ifndef PROTO_LOCAL_EventSchedule_IsBlocked
s32 EventSchedule_IsBlocked(EventScheduleRule *t, EventDate cal, EventEntryView *e, EventEntryView *out, s32 count, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_Event_AdjustToDay
void Event_AdjustToDay(EventEntryView *e, EventDate cal);
#endif
#ifndef PROTO_LOCAL_EventSchedule_Match
s32 EventSchedule_Match(EventEntryView *out, EventScheduleRule *t, s32 year, EventDate cal);
#endif
#ifndef PROTO_LOCAL_EventSchedule_Collect
s32 EventSchedule_Collect(EventEntryView *out, ClockDateTimeCopy d, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_EventSchedule_CollectDay
s32 EventSchedule_CollectDay(EventEntryView *a, ClockDateTimeCopy d, s32 x);
#endif
#ifndef PROTO_LOCAL_EventSchedule_CollectDayAll
s32 EventSchedule_CollectDayAll(EventEntryView *a, ClockDateTimeCopy d);
#endif
#ifndef PROTO_LOCAL_EventDayList_Find
EventDayEntry *EventDayList_Find(u32 id, EventDayEntry *e);
#endif
#ifndef PROTO_LOCAL_EventDayList_GetState
s32 EventDayList_GetState(s32 a, u8 *p, EventDayEntry *tbl);
#endif
#ifndef PROTO_LOCAL_Event_GetTodayList
EventDayEntry *Event_GetTodayList(void);
#endif
#ifndef PROTO_LOCAL_EventSchedule_CollectAtNoon
s32 EventSchedule_CollectAtNoon(EventEntryView *out, s32 n, u8 *p);
#endif
}
#ifndef PROTO_LOCAL_gTodayEvents
extern EventDayList gTodayEvents;
#endif
#ifndef PROTO_LOCAL_sEventsOnlineRefresh
extern s32 sEventsOnlineRefresh;
#endif
#ifndef PROTO_LOCAL_data_021c3c30
extern EventDayList data_021c3c30;
#endif
#ifndef PROTO_LOCAL_sEventSchedule
extern EventScheduleRule sEventSchedule[99];
#endif
#ifndef PROTO_LOCAL_data_020d96ec
extern ProcProfile data_020d96ec;
#endif
#endif

#endif
