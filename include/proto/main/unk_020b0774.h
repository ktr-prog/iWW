#ifndef PROTO_PROTO_MAIN_UNK_020B0774_H
#define PROTO_PROTO_MAIN_UNK_020B0774_H


#include "types.h"
#ifdef __cplusplus
#include "game/ConstellationRecord.h"
#include "game/ConstellationStore.h"
#include "gfx/StarTwinkle.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_ConstellationRecord_Copy
void *ConstellationRecord_Copy(void *p, const void *src);
#endif
#ifndef PROTO_LOCAL_StarTwinkle_Stop
void StarTwinkle_Stop(void *p);
#endif
#ifndef PROTO_LOCAL_Constellation_GetLineCells
u8 *Constellation_GetLineCells(s32 n);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_ConstellationRecord_Clear
void ConstellationRecord_Clear(ConstellationRecord *p);
#endif
#ifndef PROTO_LOCAL_ConstellationStore_Clear
void ConstellationStore_Clear(ConstellationStore *p);
#endif
#ifndef PROTO_LOCAL_ConstellationStore_SetUsed
void ConstellationStore_SetUsed(ConstellationStore *p, u32 bit);
#endif
#ifndef PROTO_LOCAL_ConstellationStore_ClearUsed
void ConstellationStore_ClearUsed(ConstellationStore *p, u32 bit);
#endif
#ifndef PROTO_LOCAL_ConstellationStore_IsUsed
BOOL ConstellationStore_IsUsed(ConstellationStore *p, u32 bit);
#endif
#ifndef PROTO_LOCAL_StarTwinkle_Update
void StarTwinkle_Update(StarTwinkle *p);
#endif
#ifndef PROTO_LOCAL_StarTwinkle_Init
void StarTwinkle_Init(StarTwinkle *self, s32 arg);
#endif
}
#ifndef PROTO_LOCAL_sConstellationLineCells
extern u16 sConstellationLineCells[0x718];
#endif
#ifndef PROTO_LOCAL_sStarPalPathA
extern char sStarPalPathA[0x14];
#endif
#ifndef PROTO_LOCAL_sStarPalPathB1
extern char sStarPalPathB1[0x14];
#endif
#ifndef PROTO_LOCAL_sStarPalPathB3
extern char sStarPalPathB3[0x14];
#endif
#ifndef PROTO_LOCAL_sStarPalPathB2
extern char sStarPalPathB2[0x14];
#endif
#ifndef PROTO_LOCAL_sStarTwinklePalettePaths
extern char *sStarTwinklePalettePaths[5];
#endif
#ifndef PROTO_LOCAL_sStarPalPathB4
extern char sStarPalPathB4[0x14];
#endif
#endif

#endif
