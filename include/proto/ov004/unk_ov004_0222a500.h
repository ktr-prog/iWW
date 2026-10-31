#ifndef PROTO_PROTO_OV004_UNK_OV004_0222A500_H
#define PROTO_PROTO_OV004_UNK_OV004_0222A500_H


#include "types.h"
#include "item/ItemId.h"
#include "sys/ProcProfile.h"
#ifdef __cplusplus
#include "gfx/Model.h"
#include "gfx/ModelAnim.h"
class RoomShell;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_RoomShell_GetSceneWallFloor
void RoomShell_GetSceneWallFloor(void *self, u16 *a, s32 *b, u16 *c, s32 *d);
#endif
#ifndef PROTO_LOCAL_RoomWallpaper_SaveToHouseRoom
void RoomWallpaper_SaveToHouseRoom(void *self, u16 *a, u32 b);
#endif
#ifndef PROTO_LOCAL_RoomEntranceColliders_InHouseScene
BOOL RoomEntranceColliders_InHouseScene();
#endif
#ifndef PROTO_LOCAL_sRoomCarpetMatNameStr
extern char sRoomCarpetMatNameStr[];
#endif
#ifndef PROTO_LOCAL_sRoomNoItem
extern ItemId sRoomNoItem;
#endif
#ifndef PROTO_LOCAL_sRoomWallpaperMatNameStr
extern char sRoomWallpaperMatNameStr[];
#endif
#ifndef PROTO_LOCAL_RoomShell_SetWallpaper
u16 *RoomShell_SetWallpaper(u16 *p, s32 key, u32 flag);
#endif
#ifndef PROTO_LOCAL_RoomShell_SetCarpet
u16 *RoomShell_SetCarpet(u16 *p, s32 key, u32 flag);
#endif
#ifndef PROTO_LOCAL_RoomShell_GetCarpet
u16 *RoomShell_GetCarpet();
#endif
#ifndef PROTO_LOCAL_RoomShell_GetPrevCarpet
u16 *RoomShell_GetPrevCarpet();
#endif
#ifndef PROTO_LOCAL_RoomShell_GetWallpaper
u16 *RoomShell_GetWallpaper();
#endif
#ifndef PROTO_LOCAL_RoomShell_GetPrevWallpaper
u16 *RoomShell_GetPrevWallpaper();
#endif
#ifndef PROTO_LOCAL_RoomShell_SpawnBoardSigns
void RoomShell_SpawnBoardSigns(void *self);
#endif
#ifndef PROTO_LOCAL_RoomShell_CalcWdColor
s16 RoomShell_CalcWdColor(void *self);
#endif
#ifndef PROTO_LOCAL_RoomShell_MatCallback
void RoomShell_MatCallback(void *p);
#endif
#ifndef PROTO_LOCAL_RoomShell_NodeDescCallback
void RoomShell_NodeDescCallback(void *p);
#endif
#ifndef PROTO_LOCAL_RoomShell_InitRenderObj
void RoomShell_InitRenderObj(void *p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sRoomShellProfile
extern ProcProfile sRoomShellProfile;
#endif
#ifndef PROTO_LOCAL_sRoomShell
extern RoomShell *sRoomShell;
#endif
#ifndef PROTO_LOCAL_RoomShell_Create
RoomShell *RoomShell_Create();
#endif
#ifndef PROTO_LOCAL_RoomShellMatAnim_GetAnmObj
NNSG3dAnmObj *RoomShellMatAnim_GetAnmObj(ModelAnim *o);
#endif
}
#endif

#endif
