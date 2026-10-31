#ifndef PROTO_PROTO_OV004_UNK_OV004_0221A564_H
#define PROTO_PROTO_OV004_UNK_OV004_0221A564_H


#include "types.h"
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#include "gfx/DebugColor.h"
class SickVillager;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov004_0225095c
extern u8 data_ov004_0225095c[0x28];
#endif
#ifndef PROTO_LOCAL_SickVillager_IsMedicine
BOOL SickVillager_IsMedicine(u16 *p, s32 x);
#endif
#ifndef PROTO_LOCAL_SickVillager_HasCurrentVisitor
BOOL SickVillager_HasCurrentVisitor(void *o);
#endif
#ifndef PROTO_LOCAL_SickVillager_SetCurrentVisitor
void SickVillager_SetCurrentVisitor();
#endif
#ifndef PROTO_LOCAL_data_ov004_02250984
extern u8 data_ov004_02250984[0x28];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SickVillager_Create
SickVillager *SickVillager_Create();
#endif
#ifndef PROTO_LOCAL_sSickVillagerProfile
extern ActorProfile sSickVillagerProfile;
#endif
}
#ifndef PROTO_LOCAL_data_ov004_02250938
extern DebugColor data_ov004_02250938;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250940
extern DebugColor data_ov004_02250940;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250948
extern DebugColor data_ov004_02250948;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250944
extern DebugColor data_ov004_02250944;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250954
extern DebugColor data_ov004_02250954;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250958
extern DebugColor data_ov004_02250958;
#endif
#ifndef PROTO_LOCAL_sSickVillager
extern SickVillager *sSickVillager;
#endif
#endif

#endif
