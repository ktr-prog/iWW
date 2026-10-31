#ifndef PROTO_PROTO_OV068_UNK_OV068_0226DBE8_H
#define PROTO_PROTO_OV068_UNK_OV068_0226DBE8_H


#include "types.h"
struct HouseVisitStarText;
#ifndef __cplusplus
typedef struct HouseVisitStarText HouseVisitStarText;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#include "gfx/DebugColor.h"
class HouseVisitVillager;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_HouseVisit_IsAppointmentNow
BOOL HouseVisit_IsAppointmentNow(void *);
#endif
#ifndef PROTO_LOCAL_HouseVisit_SetFinished
void HouseVisit_SetFinished(void *);
#endif
#ifndef PROTO_LOCAL_HouseVisit_IsCalled
BOOL HouseVisit_IsCalled(void *);
#endif
#ifndef PROTO_LOCAL_HouseVisit_SetCalled
void HouseVisit_SetCalled(void *p);
#endif
#ifndef PROTO_LOCAL_HouseVisit_IsDoorTalkDone
BOOL HouseVisit_IsDoorTalkDone(void *);
#endif
#ifndef PROTO_LOCAL_HouseVisit_SetDoorTalkDone
void HouseVisit_SetDoorTalkDone(void *p);
#endif
#ifndef PROTO_LOCAL_HouseVisit_IsFirstTalkPending
BOOL HouseVisit_IsFirstTalkPending(void *);
#endif
#ifndef PROTO_LOCAL_HouseVisit_SetFirstTalkDone
void HouseVisit_SetFirstTalkDone(void *);
#endif
#ifndef PROTO_LOCAL_sHouseVisitMsgFileName
extern u8 sHouseVisitMsgFileName[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov068_022712b8
extern u8 data_ov068_022712b8[0x28];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sHouseVisitVillager
extern HouseVisitVillager *sHouseVisitVillager;
#endif
#ifndef PROTO_LOCAL_HouseVisitVillager_Create
HouseVisitVillager *HouseVisitVillager_Create();
#endif
#ifndef PROTO_LOCAL_data_ov068_022712a8
extern DebugColor data_ov068_022712a8;
#endif
#ifndef PROTO_LOCAL_sHouseVisitVillagerProfile
extern ActorProfile sHouseVisitVillagerProfile;
#endif
#ifndef PROTO_LOCAL_data_ov068_02271298
extern DebugColor data_ov068_02271298;
#endif
#ifndef PROTO_LOCAL_data_ov068_022712b0
extern DebugColor data_ov068_022712b0;
#endif
#ifndef PROTO_LOCAL_data_ov068_022712a0
extern DebugColor data_ov068_022712a0;
#endif
#ifndef PROTO_LOCAL_data_ov068_0227129c
extern DebugColor data_ov068_0227129c;
#endif
#ifndef PROTO_LOCAL_data_ov068_02270a3c
extern HouseVisitStarText data_ov068_02270a3c;
#endif
#ifndef PROTO_LOCAL_data_ov068_022712a4
extern DebugColor data_ov068_022712a4;
#endif
}
#endif

#endif
