#ifndef PROTO_PROTO_OV004_UNK_OV004_02213B90_H
#define PROTO_PROTO_OV004_UNK_OV004_02213B90_H


#include "types.h"
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#include "gfx/DebugColor.h"
#include "room/MuseumExhibitInfo.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sMuseumExhibitSpawnMsg
extern s16 sMuseumExhibitSpawnMsg;
#endif
#ifndef PROTO_LOCAL_sMuseumExhibitMsgFile
extern char sMuseumExhibitMsgFile[];
#endif
#ifndef PROTO_LOCAL_sMuseumExhibitAutoTalkActive
extern u8 sMuseumExhibitAutoTalkActive;
#endif
#ifndef PROTO_LOCAL_sMuseumExhibitInfoCount
extern u8 sMuseumExhibitInfoCount;
#endif
#ifndef PROTO_LOCAL_sMuseumExhibitSpawnKind
extern u32 sMuseumExhibitSpawnKind;
#endif
#ifndef PROTO_LOCAL_sMuseumExhibitSpawnList
extern u8 *sMuseumExhibitSpawnList;
#endif
#ifndef PROTO_LOCAL_sMuseumExhibitSpawnCount
extern u32 sMuseumExhibitSpawnCount;
#endif
#ifndef PROTO_LOCAL_sMuseumExhibitSpawnFacingArc
extern u32 sMuseumExhibitSpawnFacingArc;
#endif
#ifndef PROTO_LOCAL_MuseumExhibitInfo_SpawnAutoTalk
void *MuseumExhibitInfo_SpawnAutoTalk();
#endif
#ifndef PROTO_LOCAL_MuseumExhibitInfo_Spawn
void MuseumExhibitInfo_Spawn(s32 a, void *b, s32 c, s32 d, s16 e, u8 *f, s32 g);
#endif
#ifndef PROTO_LOCAL_MuseumExhibitInfo_GetByIndex
void *MuseumExhibitInfo_GetByIndex(s32 i);
#endif
#ifndef PROTO_LOCAL_MuseumExhibitInfo_ClearRegistry
void MuseumExhibitInfo_ClearRegistry(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_data_ov004_022502f4
extern DebugColor data_ov004_022502f4;
#endif
#ifndef PROTO_LOCAL_data_ov004_022502e4
extern DebugColor data_ov004_022502e4;
#endif
#ifndef PROTO_LOCAL_data_ov004_022502ec
extern DebugColor data_ov004_022502ec;
#endif
#ifndef PROTO_LOCAL_data_ov004_022502dc
extern DebugColor data_ov004_022502dc;
#endif
#ifndef PROTO_LOCAL_data_ov004_022502d0
extern DebugColor data_ov004_022502d0;
#endif
#ifndef PROTO_LOCAL_data_ov004_022502e0
extern DebugColor data_ov004_022502e0;
#endif
#ifndef PROTO_LOCAL_sMuseumExhibitInfoProfile
extern ActorProfile sMuseumExhibitInfoProfile;
#endif
#ifndef PROTO_LOCAL_sMuseumExhibitInfos
extern MuseumExhibitInfo *sMuseumExhibitInfos[0x20];
#endif
#ifndef PROTO_LOCAL_MuseumExhibitInfo_Create
MuseumExhibitInfo *MuseumExhibitInfo_Create(void);
#endif
}
#endif

#endif
