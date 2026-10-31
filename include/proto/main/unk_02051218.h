#ifndef PROTO_PROTO_MAIN_UNK_02051218_H
#define PROTO_PROTO_MAIN_UNK_02051218_H


#include "types.h"
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_BedSpot_RequestApproach
void BedSpot_RequestApproach(s32 *p);
#endif
#ifndef PROTO_LOCAL_BedSpot_GetApproachResult
u32 BedSpot_GetApproachResult();
#endif
#ifndef PROTO_LOCAL_BedSpot_RequestGetOut
void BedSpot_RequestGetOut(s32 *p);
#endif
#ifndef PROTO_LOCAL_BedSpot_GetGetOutResult
u32 BedSpot_GetGetOutResult();
#endif
#ifndef PROTO_LOCAL_BedSpot_Release
void BedSpot_Release();
#endif
#ifndef PROTO_LOCAL_BedSpot_RequestRoll
void BedSpot_RequestRoll(s32 *p);
#endif
#ifndef PROTO_LOCAL_BedSpot_GetRollResult
u32 BedSpot_GetRollResult();
#endif
#ifndef PROTO_LOCAL_Room_CanDropOnFurnitureAt
BOOL Room_CanDropOnFurnitureAt(s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_Text_BuildCharWidthTable
void Text_BuildCharWidthTable();
#endif
#ifndef PROTO_LOCAL_Text_GetCharWidth
u32 Text_GetCharWidth(u32 c);
#endif
#ifndef PROTO_LOCAL_Text_MeasureWidth
s32 Text_MeasureWidth(const u8 *p, s32 n);
#endif
#ifndef PROTO_LOCAL_Text_GetLineEnd
s32 Text_GetLineEnd(const u8 *p, s32 n, s32 k);
#endif
#ifndef PROTO_LOCAL_Text_GetTrimmedLength
s32 Text_GetTrimmedLength(const u8 *str, s32 len);
#endif
#ifndef PROTO_LOCAL_Text_GetLength
s32 Text_GetLength(const u8 *str, s32 len);
#endif
#ifndef PROTO_LOCAL_Text_FitToWidth
s32 Text_FitToWidth(const u8 *str, s32 maxLen, s32 maxWidth, s32 *outLen, s32 arg4);
#endif
#ifndef PROTO_LOCAL_Mem_Copy
void Mem_Copy(const void *src, void *dst, u32 size);
#endif
#ifndef PROTO_LOCAL_Mem_Clear
void Mem_Clear(void *dst, u32 size);
#endif
#ifndef PROTO_LOCAL_Text_EqualsTrimmed
BOOL Text_EqualsTrimmed(const u8 *a, const u8 *b, s32 len);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef PROTO_LOCAL_sTextCharWidths
extern u8 sTextCharWidths[0xe0];
#endif
#endif

#endif
