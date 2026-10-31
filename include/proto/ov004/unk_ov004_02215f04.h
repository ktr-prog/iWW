#ifndef PROTO_PROTO_OV004_UNK_OV004_02215F04_H
#define PROTO_PROTO_OV004_UNK_OV004_02215F04_H


#include "types.h"
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#include "gfx/DebugColor.h"
#include "gfx/VecFx32.h"
#include "npc/BirthdayGuestVillager.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sBirthdayGuestMsgFile
extern u8 sBirthdayGuestMsgFile[0x28];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_data_ov004_02250588
extern DebugColor data_ov004_02250588;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250598
extern DebugColor data_ov004_02250598;
#endif
#ifndef PROTO_LOCAL_data_ov004_0225057c
extern DebugColor data_ov004_0225057c;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250580
extern DebugColor data_ov004_02250580;
#endif
#ifndef PROTO_LOCAL_data_ov004_0225058c
extern DebugColor data_ov004_0225058c;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250594
extern DebugColor data_ov004_02250594;
#endif
#ifndef PROTO_LOCAL_sBirthdayGuestVillagerProfile
extern ActorProfile sBirthdayGuestVillagerProfile;
#endif
#ifndef PROTO_LOCAL_sBirthdayGuestVillager
extern BirthdayGuestVillager *sBirthdayGuestVillager;
#endif
#ifndef PROTO_LOCAL_data_ov004_0224c158
extern Unk_ov004_0224c228_BFn data_ov004_0224c158;
#endif
#ifndef PROTO_LOCAL_BirthdayGuestVillager_Create
BirthdayGuestVillager *BirthdayGuestVillager_Create();
#endif
#ifndef PROTO_LOCAL_BirthdayGuestVillager_Get
BirthdayGuestVillager *BirthdayGuestVillager_Get();
#endif
#ifndef PROTO_LOCAL_Room_PickRandomWalkTarget
s32 Room_PickRandomWalkTarget(VecFx32 *out, VecFx32 *in, s32 angle);
#endif
}
#endif

#endif
