#ifndef PROTO_PROTO_OV004_UNK_OV004_02214948_H
#define PROTO_PROTO_OV004_UNK_OV004_02214948_H


#include "types.h"
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#include "gfx/DebugColor.h"
#include "npc/BirthdayHostVillager.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_BirthdayHostVillager_HasReceivedGift
BOOL BirthdayHostVillager_HasReceivedGift();
#endif
#ifndef PROTO_LOCAL_BirthdayHost_GiftFilter
BOOL BirthdayHost_GiftFilter(u16 *p, s32 flag);
#endif
#ifndef PROTO_LOCAL_sBirthdayHostMsgFile
extern u8 sBirthdayHostMsgFile[0x28];
#endif
#ifndef PROTO_LOCAL_BirthdayHost_PickReturnGift
u16 BirthdayHost_PickReturnGift(s32 n);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_data_ov004_022503c0
extern DebugColor data_ov004_022503c0;
#endif
#ifndef PROTO_LOCAL_data_ov004_022503dc
extern DebugColor data_ov004_022503dc;
#endif
#ifndef PROTO_LOCAL_data_ov004_022503c4
extern DebugColor data_ov004_022503c4;
#endif
#ifndef PROTO_LOCAL_data_ov004_022503bc
extern DebugColor data_ov004_022503bc;
#endif
#ifndef PROTO_LOCAL_data_ov004_022503cc
extern DebugColor data_ov004_022503cc;
#endif
#ifndef PROTO_LOCAL_data_ov004_022503d0
extern DebugColor data_ov004_022503d0;
#endif
#ifndef PROTO_LOCAL_sBirthdayHostVillagerProfile
extern ActorProfile sBirthdayHostVillagerProfile;
#endif
#ifndef PROTO_LOCAL_sBirthdayHostVillager
extern BirthdayHostVillager *sBirthdayHostVillager;
#endif
#ifndef PROTO_LOCAL_BirthdayHostVillager_Create
BirthdayHostVillager *BirthdayHostVillager_Create();
#endif
#ifndef PROTO_LOCAL_BirthdayHostVillager_Get
BirthdayHostVillager *BirthdayHostVillager_Get();
#endif
#ifndef PROTO_LOCAL_data_ov004_0224befc
extern Unk_ov004_0224c034_Fn data_ov004_0224befc;
#endif
}
#endif

#endif
