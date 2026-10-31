#ifndef PROTO_PROTO_MAIN_UNK_02097D1C_H
#define PROTO_PROTO_MAIN_UNK_02097D1C_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_PlayerData_HasStungFace
BOOL PlayerData_HasStungFace(void *p);
#endif
#ifndef PROTO_LOCAL_PlayerData_SetStungFace
void PlayerData_SetStungFace(void *p, u32 flag);
#endif
#ifndef PROTO_LOCAL_PlayerData_GetNookPoints
void *PlayerData_GetNookPoints(void *p);
#endif
#ifndef PROTO_LOCAL_PlayerData_UpdateDay
void PlayerData_UpdateDay();
#endif
#ifndef PROTO_LOCAL_Pocket_IsValidIndex
BOOL Pocket_IsValidIndex(s32 i);
#endif
#ifndef PROTO_LOCAL_Letter_IsValidIndex
BOOL Letter_IsValidIndex(s32 i);
#endif
#ifdef __cplusplus
}
#endif

#endif
