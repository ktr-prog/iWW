#ifndef PROTO_PROTO_MAIN_UNK_02034048_H
#define PROTO_PROTO_MAIN_UNK_02034048_H


#include "types.h"
struct RoomWallFloorPacket;
#ifndef __cplusplus
typedef struct RoomWallFloorPacket RoomWallFloorPacket;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_RoomWallFloor_MakeDesignItem
void RoomWallFloor_MakeDesignItem(u16 *out, s32 a);
#endif
#ifndef PROTO_LOCAL_RoomWallFloor_Send
void RoomWallFloor_Send(u16 *id, s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_RoomWallFloor_SetWallpaper
void *RoomWallFloor_SetWallpaper(u16 *id, s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_RoomWallFloor_SetWallpaperDesign
void *RoomWallFloor_SetWallpaperDesign(s32 a, s32 b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_RoomWallFloor_SetCarpet
void *RoomWallFloor_SetCarpet(u16 *id, s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_RoomWallFloor_SetCarpetDesign
void *RoomWallFloor_SetCarpetDesign(s32 a, s32 b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_RoomWallFloor_RestoreWallpaper
BOOL RoomWallFloor_RestoreWallpaper(s32 a);
#endif
#ifndef PROTO_LOCAL_RoomWallFloor_RestoreCarpet
BOOL RoomWallFloor_RestoreCarpet(s32 a);
#endif
#ifndef PROTO_LOCAL_RoomWallFloor_Set
void RoomWallFloor_Set(u16 *a, s32 b, s32 c, s32 d, u8 e);
#endif
#ifndef PROTO_LOCAL_RoomWallFloor_ClearScenes
void RoomWallFloor_ClearScenes();
#endif
#ifndef PROTO_LOCAL_RoomWallFloor_SetSceneWallpaper
BOOL RoomWallFloor_SetSceneWallpaper(u32 i, u16 *v);
#endif
#ifndef PROTO_LOCAL_RoomWallFloor_GetSceneWallpaper
u16 *RoomWallFloor_GetSceneWallpaper(u32 i);
#endif
#ifndef PROTO_LOCAL_RoomWallFloor_SetSceneCarpet
BOOL RoomWallFloor_SetSceneCarpet(u32 i, u16 *v);
#endif
#ifndef PROTO_LOCAL_RoomWallFloor_GetSceneCarpet
u16 *RoomWallFloor_GetSceneCarpet(u32 i);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_RoomWallFloor_ApplyRecv
void RoomWallFloor_ApplyRecv(RoomWallFloorPacket *p);
#endif
}
#endif

#endif
