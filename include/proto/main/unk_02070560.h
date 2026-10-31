#ifndef PROTO_PROTO_MAIN_UNK_02070560_H
#define PROTO_PROTO_MAIN_UNK_02070560_H


#include "types.h"
#include "game/Unk_020702ec_Date.h"
#ifdef __cplusplus
#include "gfx/PatternTexCache.h"
#include "gfx/TexPatVramAnim.h"
#include "save/Pattern.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_TownFlagPattern_InitDefault
void TownFlagPattern_InitDefault(void *self);
#endif
#ifndef PROTO_LOCAL_TownFlagPattern_GetPattern
void *TownFlagPattern_GetPattern(void *p);
#endif
#ifndef PROTO_LOCAL_PlayerPatternDefaults_Ctor
void PlayerPatternDefaults_Ctor(void *p);
#endif
#ifndef PROTO_LOCAL_PlayerPatternDefaults_Load
void PlayerPatternDefaults_Load(void *p);
#endif
#ifndef PROTO_LOCAL_PlayerPatternDefaults_Extract
BOOL PlayerPatternDefaults_Extract(void *a, void *b, s32 x);
#endif
#ifndef PROTO_LOCAL_AblePatternDefaults_Ctor
void AblePatternDefaults_Ctor(void *p);
#endif
#ifndef PROTO_LOCAL_AblePatternDefaults_Load
void AblePatternDefaults_Load(void *p);
#endif
#ifndef PROTO_LOCAL_AblePatternDefaults_Extract
BOOL AblePatternDefaults_Extract(void *a, void *b, s32 x);
#endif
#ifndef PROTO_LOCAL_TownFlagPatternDefault_Ctor
void TownFlagPatternDefault_Ctor(void *p);
#endif
#ifndef PROTO_LOCAL_TownFlagPatternDefault_Load
void TownFlagPatternDefault_Load(void *p);
#endif
#ifndef PROTO_LOCAL_TownFlagPatternDefault_Extract
BOOL TownFlagPatternDefault_Extract(void *a, void *b);
#endif
#ifndef PROTO_LOCAL_PresetPatternFile_Ctor
void PresetPatternFile_Ctor(void *p);
#endif
#ifndef PROTO_LOCAL_PresetPatternFile_Load
void PresetPatternFile_Load(void *dst, s32 n);
#endif
#ifndef PROTO_LOCAL_PresetPatternFile_Extract
BOOL PresetPatternFile_Extract(void *a, void *b);
#endif
#ifndef PROTO_LOCAL_PatternSrc_OnChanged
BOOL PatternSrc_OnChanged(s32 cmd, s32 x);
#endif
#ifndef PROTO_LOCAL_Villager_MaybeCopyAblePattern
BOOL Villager_MaybeCopyAblePattern(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_PatternSrc_Copy
BOOL PatternSrc_Copy(u32 a, u32 b, u32 c, u32 d, u32 e);
#endif
#ifndef PROTO_LOCAL_PatternSrc_ResolveKind
s32 PatternSrc_ResolveKind(s32 t);
#endif
#ifndef PROTO_LOCAL_PatternSrc_Swap
BOOL PatternSrc_Swap(u32 a, u32 b, u32 c, u32 d, u32 e);
#endif
#ifndef PROTO_LOCAL_sPlayerPatternTexKeys
extern u8 *sPlayerPatternTexKeys[4][8];
#endif
#ifndef PROTO_LOCAL_Pattern_RemovePlayerItems
void Pattern_RemovePlayerItems(s32 p);
#endif
#ifndef PROTO_LOCAL_PatternTex_UploadPlayer
BOOL PatternTex_UploadPlayer(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_PatternTex_UploadAble
BOOL PatternTex_UploadAble(u32 x);
#endif
#ifndef PROTO_LOCAL_sAblePatternTexKeys
extern u8 *sAblePatternTexKeys[8];
#endif
#ifndef PROTO_LOCAL_data_021cbcac
extern u8 data_021cbcac[4];
#endif
#ifndef PROTO_LOCAL_sAbleDisplayDirtyBits
extern u8 sAbleDisplayDirtyBits;
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_PresetPatternBuffer_Get
PresetPatternBuffer *PresetPatternBuffer_Get(void);
#endif
#ifndef PROTO_LOCAL_PatternTexCache_ClearDirty
void PatternTexCache_ClearDirty(PatternTexCache *p);
#endif
#ifndef PROTO_LOCAL_PatternTexCache_Get
PatternTexCache *PatternTexCache_Get(void);
#endif
#ifndef PROTO_LOCAL_PatternPaletteFile_GetPalette
u8 *PatternPaletteFile_GetPalette(PatternPaletteFile *self, s32 i);
#endif
#ifndef PROTO_LOCAL_PatternTexKeys_Clear
void PatternTexKeys_Clear(PatternTexKeys *p);
#endif
#ifndef PROTO_LOCAL_PatternTexCache_ResetKeys
void PatternTexCache_ResetKeys(PatternTexCache *p);
#endif
#ifndef PROTO_LOCAL_PatternTexKeys_GetPlayer
u8 *PatternTexKeys_GetPlayer(PatternTexKeys *self, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_PatternTexKeys_GetAble
u8 *PatternTexKeys_GetAble(PatternTexKeys *self, s32 i);
#endif
#ifndef PROTO_LOCAL_PatternPresetInfo_Open
void PatternPresetInfo_Open(PatternPresetInfoFile *p);
#endif
#ifndef PROTO_LOCAL_PatternPresetInfo_Close
void PatternPresetInfo_Close(PatternPresetInfoFile *p);
#endif
#ifndef PROTO_LOCAL_PatternPresetInfo_Apply
BOOL PatternPresetInfo_Apply(PatternPresetInfoFile *tbl, PatternInfo *dst, s32 idx);
#endif
#ifndef PROTO_LOCAL_PatternPresetInfo_Get
PatternPresetInfoFile *PatternPresetInfo_Get(void);
#endif
#ifndef PROTO_LOCAL_sAblePatternTexWork
extern ClothTexStorage *sAblePatternTexWork;
#endif
#ifndef PROTO_LOCAL_sAblePatternVramTasks
extern TexPatVramTasks *sAblePatternVramTasks;
#endif
#ifndef PROTO_LOCAL_PatternSrc_GetSessionPlayer
Pattern *PatternSrc_GetSessionPlayer(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_PatternSrc_GetSessionPlayer0
Pattern *PatternSrc_GetSessionPlayer0(s32 x);
#endif
#ifndef PROTO_LOCAL_PatternSrc_GetSessionPlayer1
Pattern *PatternSrc_GetSessionPlayer1(s32 x);
#endif
#ifndef PROTO_LOCAL_PatternSrc_GetSessionPlayer2
Pattern *PatternSrc_GetSessionPlayer2(s32 x);
#endif
#ifndef PROTO_LOCAL_PatternSrc_GetSessionPlayer3
Pattern *PatternSrc_GetSessionPlayer3(s32 x);
#endif
#ifndef PROTO_LOCAL_PatternSrc_GetAble
Pattern *PatternSrc_GetAble(s32 x);
#endif
#ifndef PROTO_LOCAL_PatternSrc_GetTownFlag
Pattern *PatternSrc_GetTownFlag(s32 x);
#endif
#ifndef PROTO_LOCAL_PatternSrc_GetVillager
Pattern *PatternSrc_GetVillager(s32 x);
#endif
#ifndef PROTO_LOCAL_PatternSrc_GetPreset
Pattern *PatternSrc_GetPreset(s32 x);
#endif
#ifndef PROTO_LOCAL_PatternSrc_GetBlancaFace
Pattern *PatternSrc_GetBlancaFace(s32 x);
#endif
#ifndef PROTO_LOCAL_PatternSrc_GetCurrentPlayer
Pattern *PatternSrc_GetCurrentPlayer(s32 i);
#endif
#ifndef PROTO_LOCAL_PatternSrc_Get
Pattern *PatternSrc_Get(s32 i, s32 a);
#endif
#ifndef PROTO_LOCAL_PatternSrc_ApplyNetMove
void PatternSrc_ApplyNetMove(Unk_0206fe80_Bits *p);
#endif
#ifndef PROTO_LOCAL_sPlayerPatternTexWork
extern ClothTexStorage *sPlayerPatternTexWork;
#endif
#ifndef PROTO_LOCAL_sPlayerPatternVramTasks
extern TexPatVramTasks *sPlayerPatternVramTasks;
#endif
}
#ifndef PROTO_LOCAL_sPresetPatternBuffer
extern PresetPatternBuffer sPresetPatternBuffer;
#endif
#ifndef PROTO_LOCAL_sPatternTexCache
extern PatternTexCache sPatternTexCache;
#endif
#ifndef PROTO_LOCAL_sPatternPresetInfo
extern PatternPresetInfoFile sPatternPresetInfo;
#endif
#endif

#endif
