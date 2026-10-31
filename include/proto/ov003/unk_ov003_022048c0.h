#ifndef PROTO_PROTO_OV003_UNK_OV003_022048C0_H
#define PROTO_PROTO_OV003_UNK_OV003_022048C0_H


#include "types.h"
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#include "gfx/DebugColor.h"
class VillagerBoard;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sVillagerBoardCount
extern u8 sVillagerBoardCount;
#endif
#ifndef PROTO_LOCAL_VillagerBoard_ResetTable
void VillagerBoard_ResetTable();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_data_ov003_02234f80
extern DebugColor data_ov003_02234f80;
#endif
#ifndef PROTO_LOCAL_data_ov003_02234f64
extern DebugColor data_ov003_02234f64;
#endif
#ifndef PROTO_LOCAL_data_ov003_02234f68
extern DebugColor data_ov003_02234f68;
#endif
#ifndef PROTO_LOCAL_data_ov003_02234f70
extern DebugColor data_ov003_02234f70;
#endif
#ifndef PROTO_LOCAL_data_ov003_02234f6c
extern DebugColor data_ov003_02234f6c;
#endif
#ifndef PROTO_LOCAL_data_ov003_02234f74
extern DebugColor data_ov003_02234f74;
#endif
#ifndef PROTO_LOCAL_VillagerBoard_Create
VillagerBoard *VillagerBoard_Create();
#endif
#ifndef PROTO_LOCAL_sVillagerBoardProfile
extern ActorProfile sVillagerBoardProfile;
#endif
#ifndef PROTO_LOCAL_sVillagerBoards
extern VillagerBoard *sVillagerBoards[8];
#endif
#ifndef PROTO_LOCAL_VillagerBoard_Get
VillagerBoard *VillagerBoard_Get(s32 i);
#endif
}
#endif

#endif
