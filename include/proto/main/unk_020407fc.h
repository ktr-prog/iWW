#ifndef PROTO_PROTO_MAIN_UNK_020407FC_H
#define PROTO_PROTO_MAIN_UNK_020407FC_H


#include "types.h"
#include "sys/ProcProfile.h"
struct EventAnnounceState;
#ifndef __cplusplus
typedef struct EventAnnounceState EventAnnounceState;
#endif
#ifdef __cplusplus
class EventAnnouncer;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_ScreenTransition_ShowCover
void ScreenTransition_ShowCover();
#endif
#ifndef PROTO_LOCAL_EventAnnounce_Reset
void EventAnnounce_Reset(void);
#endif
#ifndef PROTO_LOCAL_EventAnnounce_Restart
void EventAnnounce_Restart(void);
#endif
#ifndef PROTO_LOCAL_EventAnnounce_CanCheck
BOOL EventAnnounce_CanCheck(void);
#endif
#ifndef PROTO_LOCAL_EventAnnounce_CheckEvents
void EventAnnounce_CheckEvents(void);
#endif
#ifndef PROTO_LOCAL_EventAnnounce_Update
void EventAnnounce_Update(void);
#endif
#ifndef PROTO_LOCAL_EventAnnounce_IsBusy
s32 EventAnnounce_IsBusy(void);
#endif
#ifndef PROTO_LOCAL_EventAnnounce_GetActiveEvent
s32 EventAnnounce_GetActiveEvent(void);
#endif
#ifndef PROTO_LOCAL_EventAnnounce_GetCurrentEvent
s32 EventAnnounce_GetCurrentEvent(void);
#endif
#ifndef PROTO_LOCAL_EventAnnounce_RequestWarp
BOOL EventAnnounce_RequestWarp(void);
#endif
#ifndef PROTO_LOCAL_EventAnnounce_SetState
void EventAnnounce_SetState(s32 v);
#endif
#ifndef PROTO_LOCAL_EventAnnounce_Request
void EventAnnounce_Request(s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_EventAnnounce_IsBlockedScene
BOOL EventAnnounce_IsBlockedScene(void);
#endif
#ifndef PROTO_LOCAL_EventWeekSlots_Construct
void EventWeekSlots_Construct(u8 *p);
#endif
#ifndef PROTO_LOCAL_EventWeekSlots_Destruct
void EventWeekSlots_Destruct(void);
#endif
#ifndef PROTO_LOCAL_EventWeekSlots_InitNew
void EventWeekSlots_InitNew(u8 *p);
#endif
#ifndef PROTO_LOCAL_EventWeekSlots_Reset
void EventWeekSlots_Reset(u8 *p);
#endif
#ifndef PROTO_LOCAL_EventWeekSlots_OnLoad
void EventWeekSlots_OnLoad(u8 *p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_EventAnnouncer_Create
EventAnnouncer *EventAnnouncer_Create();
#endif
#ifndef PROTO_LOCAL_EventAnnounce_RunIdle
void EventAnnounce_RunIdle(EventAnnouncer *);
#endif
#ifndef PROTO_LOCAL_EventAnnounce_RunWaitChimeStart
void EventAnnounce_RunWaitChimeStart(EventAnnouncer *);
#endif
#ifndef PROTO_LOCAL_EventAnnounce_RunWaitChimeEnd
void EventAnnounce_RunWaitChimeEnd(EventAnnouncer *);
#endif
#ifndef PROTO_LOCAL_EventAnnounce_RunWarp
void EventAnnounce_RunWarp(EventAnnouncer *);
#endif
#ifndef PROTO_LOCAL_EventAnnounce_RunShowMessage
void EventAnnounce_RunShowMessage(EventAnnouncer *o);
#endif
#ifndef PROTO_LOCAL_EventAnnounce_RunWaitMessageEnd
void EventAnnounce_RunWaitMessageEnd(EventAnnouncer *);
#endif
}
#ifndef PROTO_LOCAL_sEventAnnounceBusy
extern s32 sEventAnnounceBusy;
#endif
#ifndef PROTO_LOCAL_sEventAnnouncerProfile
extern ProcProfile sEventAnnouncerProfile;
#endif
#ifndef PROTO_LOCAL_sEventAnnounceWasOnline
extern s32 sEventAnnounceWasOnline;
#endif
#ifndef PROTO_LOCAL_sEventAnnounceBgmCode
extern s32 sEventAnnounceBgmCode;
#endif
#ifndef PROTO_LOCAL_sEventAnnouncePendingEvent
extern s32 sEventAnnouncePendingEvent;
#endif
#ifndef PROTO_LOCAL_sEventAnnounceActiveEvent
extern s32 sEventAnnounceActiveEvent;
#endif
#ifndef PROTO_LOCAL_sEventAnnounceCurEvent
extern s32 sEventAnnounceCurEvent;
#endif
#ifndef PROTO_LOCAL_sEventAnnounceState
extern EventAnnounceState sEventAnnounceState;
#endif
#endif

#endif
