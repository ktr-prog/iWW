#ifndef PROTO_PROTO_MAIN_UNK_02060034_H
#define PROTO_PROTO_MAIN_UNK_02060034_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_PlayerHouse_ReplaceStructure
BOOL PlayerHouse_ReplaceStructure(s32 x);
#endif
#ifndef PROTO_LOCAL_HouseData_IsValidRoomIndex
BOOL HouseData_IsValidRoomIndex(s32 i);
#endif
#ifndef PROTO_LOCAL_House_GetLevelAcreId
u16 House_GetLevelAcreId();
#endif
#ifndef PROTO_LOCAL_HouseData_GetRoomFlagMask
u32 HouseData_GetRoomFlagMask(u32 x);
#endif
#ifndef PROTO_LOCAL_HouseRoom_GetCurrentSong
u16 *HouseRoom_GetCurrentSong();
#endif
#ifndef PROTO_LOCAL_HouseRoom_SetSongForScene
BOOL HouseRoom_SetSongForScene(s32 a, u16 *p);
#endif
#ifndef PROTO_LOCAL_HouseRoom_SetCurrentSong
BOOL HouseRoom_SetCurrentSong(u16 *p);
#endif
#ifndef PROTO_LOCAL_HouseRoom_ClearSongForScene
BOOL HouseRoom_ClearSongForScene(s32 a);
#endif
#ifndef PROTO_LOCAL_HouseRoom_ClearCurrentSong
BOOL HouseRoom_ClearCurrentSong();
#endif
#ifndef PROTO_LOCAL_SongSet_TestBit
BOOL SongSet_TestBit(u8 *bits, u32 i);
#endif
#ifndef PROTO_LOCAL_SongSet_HasSong
BOOL SongSet_HasSong(u32 id);
#endif
#ifndef PROTO_LOCAL_SongSet_SetBit
void SongSet_SetBit(u8 *bits, u32 i);
#endif
#ifndef PROTO_LOCAL_SongSet_AddSong
void SongSet_AddSong(u32 id);
#endif
#ifndef PROTO_LOCAL_SongSet_ClearBit
void SongSet_ClearBit(u8 *bits, u32 i);
#endif
#ifndef PROTO_LOCAL_SongSet_RemoveSong
void SongSet_RemoveSong(u32 id);
#endif
#ifdef __cplusplus
}
#endif

#endif
