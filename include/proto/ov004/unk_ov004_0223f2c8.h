#ifndef PROTO_PROTO_OV004_UNK_OV004_0223F2C8_H
#define PROTO_PROTO_OV004_UNK_OV004_0223F2C8_H


#include "types.h"
#ifdef __cplusplus
#include "game/SceneInfo.h"
#include "game/SceneWarp.h"
#include "menu/StaffRoll.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_KkShowFx_Start
void KkShowFx_Start(void);
#endif
#ifndef PROTO_LOCAL_KkShowFx_Update
void KkShowFx_Update(void);
#endif
#ifndef PROTO_LOCAL_KkShowFx_CallUnk1f70
void KkShowFx_CallUnk1f70(void);
#endif
#ifndef PROTO_LOCAL_KkShowFx_Stop
void KkShowFx_Stop();
#endif
#ifndef PROTO_LOCAL_KkShowFx_SetParam
void KkShowFx_SetParam(s32 a);
#endif
#ifndef PROTO_LOCAL_KkShowFx_CallUnk1de4
void KkShowFx_CallUnk1de4();
#endif
#ifndef PROTO_LOCAL_KkShowFx_GetState
s32 KkShowFx_GetState();
#endif
#ifndef PROTO_LOCAL_data_ov004_0224f2d0
extern u32 data_ov004_0224f2d0;
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef PROTO_LOCAL_sKkShowFxActive
extern u8 sKkShowFxActive;
#endif
#ifndef PROTO_LOCAL_sKkShowFx
extern StaffRoll *sKkShowFx;
#endif
#ifndef PROTO_LOCAL_sRoomSceneEntries
extern SceneWarp sRoomSceneEntries[3];
#endif
#ifndef PROTO_LOCAL_sRoomSceneEntryList
extern SceneWarpList sRoomSceneEntryList;
#endif
#ifndef PROTO_LOCAL_sRoomCommonProfileCount
extern u32 sRoomCommonProfileCount;
#endif
#ifndef PROTO_LOCAL_sRoomCommonProfiles
extern u32 sRoomCommonProfiles[17];
#endif
#endif

#endif
