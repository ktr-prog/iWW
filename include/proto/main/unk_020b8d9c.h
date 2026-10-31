#ifndef PROTO_PROTO_MAIN_UNK_020B8D9C_H
#define PROTO_PROTO_MAIN_UNK_020B8D9C_H


#include "types.h"
#include "nitro/gxoam.h"
#include "sys/ClockDateTime.h"
struct SkyGradient;
struct SkyLight;
struct SkyObjGfxLoader;
struct SkyObjGfxSlot;
struct SkyObjPalette;
struct SkySprite;
struct SkySpriteAnimDef;
struct SkySprites;
struct U234_Record;
struct Unk_020bee28_Vec2;
struct WeatherManager;
#ifndef __cplusplus
typedef struct SkyGradient SkyGradient;
typedef struct SkyLight SkyLight;
typedef struct SkyObjGfxLoader SkyObjGfxLoader;
typedef struct SkyObjGfxSlot SkyObjGfxSlot;
typedef struct SkyObjPalette SkyObjPalette;
typedef struct SkySprite SkySprite;
typedef struct SkySpriteAnimDef SkySpriteAnimDef;
typedef struct SkySprites SkySprites;
typedef struct U234_Record U234_Record;
typedef struct Unk_020bee28_Vec2 Unk_020bee28_Vec2;
typedef struct WeatherManager WeatherManager;
#endif
#ifdef __cplusplus
#include "game/SkyProc.h"
#include "gfx/HBlankTask.h"
#include "gfx/SpriteAnim.h"
#include "gfx/StarTwinkle.h"
#include "gfx/VecFx32.h"
#include "snd/RainSndChannel.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_SkySprite_ResetMoonPalette
void SkySprite_ResetMoonPalette(void);
#endif
#ifndef PROTO_LOCAL_SkySprite_GetFireworkPalIndex
s32 SkySprite_GetFireworkPalIndex(s32 a, s32 flag);
#endif
#ifndef PROTO_LOCAL_data_020e4c24
extern GXOamAttr data_020e4c24[2];
#endif
#ifndef PROTO_LOCAL_data_020e4644
extern GXOamAttr data_020e4644[1];
#endif
#ifndef PROTO_LOCAL_data_020e4c34
extern GXOamAttr data_020e4c34[2];
#endif
#ifndef PROTO_LOCAL_data_020e4d70
extern char *data_020e4d70[5];
#endif
#ifndef PROTO_LOCAL_data_020e4c54
extern GXOamAttr data_020e4c54[2];
#endif
#ifndef PROTO_LOCAL_data_020e497c
extern GXOamAttr data_020e497c[1];
#endif
#ifndef PROTO_LOCAL_sSnowSideToggle
extern s32 sSnowSideToggle;
#endif
#ifndef PROTO_LOCAL_data_020e5610
extern GXOamAttr data_020e5610[10];
#endif
#ifndef PROTO_LOCAL_data_020e5440
extern GXOamAttr data_020e5440[9];
#endif
#ifndef PROTO_LOCAL_data_020e4634
extern u8 data_020e4634[4];
#endif
#ifndef PROTO_LOCAL_data_020e48d4
extern GXOamAttr data_020e48d4[1];
#endif
#ifndef PROTO_LOCAL_data_020e470c
extern GXOamAttr data_020e470c[1];
#endif
#ifndef PROTO_LOCAL_data_020e5088
extern char data_020e5088[31];
#endif
#ifndef PROTO_LOCAL_data_020e52b8
extern GXOamAttr data_020e52b8[6];
#endif
#ifndef PROTO_LOCAL_data_020e5488
extern GXOamAttr data_020e5488[9];
#endif
#ifndef PROTO_LOCAL_data_020e4a5c
extern GXOamAttr data_020e4a5c[1];
#endif
#ifndef PROTO_LOCAL_data_020e4cc4
extern GXOamAttr data_020e4cc4[2];
#endif
#ifndef PROTO_LOCAL_data_020e4cd4
extern GXOamAttr data_020e4cd4[2];
#endif
#ifndef PROTO_LOCAL_data_020e4f88
extern char data_020e4f88[30];
#endif
#ifndef PROTO_LOCAL_data_020e4cf4
extern GXOamAttr data_020e4cf4[2];
#endif
#ifndef PROTO_LOCAL_data_020e4e10
extern char data_020e4e10[27];
#endif
#ifndef PROTO_LOCAL_data_020e47f4
extern GXOamAttr data_020e47f4[1];
#endif
#ifndef PROTO_LOCAL_data_020e4d14
extern GXOamAttr data_020e4d14[2];
#endif
#ifndef PROTO_LOCAL_data_020e4d24
extern GXOamAttr data_020e4d24[2];
#endif
#ifndef PROTO_LOCAL_sSkyOutdoors
extern u32 sSkyOutdoors;
#endif
#ifndef PROTO_LOCAL_data_020e487c
extern GXOamAttr data_020e487c[1];
#endif
#ifndef PROTO_LOCAL_data_020e4d98
extern char *data_020e4d98[5];
#endif
#ifndef PROTO_LOCAL_data_020e4fa8
extern char data_020e4fa8[30];
#endif
#ifndef PROTO_LOCAL_data_020e50c8
extern char data_020e50c8[31];
#endif
#ifndef PROTO_LOCAL_data_020e4a54
extern GXOamAttr data_020e4a54[1];
#endif
#ifndef PROTO_LOCAL_data_020e4a3c
extern GXOamAttr data_020e4a3c[1];
#endif
#ifndef PROTO_LOCAL_data_020e4984
extern GXOamAttr data_020e4984[1];
#endif
#ifndef PROTO_LOCAL_data_020e49ec
extern GXOamAttr data_020e49ec[1];
#endif
#ifndef PROTO_LOCAL_data_020e476c
extern GXOamAttr data_020e476c[1];
#endif
#ifndef PROTO_LOCAL_data_020e49d4
extern GXOamAttr data_020e49d4[1];
#endif
#ifndef PROTO_LOCAL_data_020e469c
extern GXOamAttr data_020e469c[1];
#endif
#ifndef PROTO_LOCAL_data_020e4e48
extern char data_020e4e48[30];
#endif
#ifndef PROTO_LOCAL_data_020e495c
extern GXOamAttr data_020e495c[1];
#endif
#ifndef PROTO_LOCAL_data_020e4764
extern GXOamAttr data_020e4764[1];
#endif
#ifndef PROTO_LOCAL_data_020e4874
extern GXOamAttr data_020e4874[1];
#endif
#ifndef PROTO_LOCAL_sMoonColors
extern u16 sMoonColors[6];
#endif
#ifndef PROTO_LOCAL_data_020e4e68
extern char data_020e4e68[30];
#endif
#ifndef PROTO_LOCAL_data_020e5378
extern GXOamAttr data_020e5378[7];
#endif
#ifndef PROTO_LOCAL_data_020e4e88
extern char data_020e4e88[30];
#endif
#ifndef PROTO_LOCAL_data_020e4ea8
extern char data_020e4ea8[30];
#endif
#ifndef PROTO_LOCAL_data_020e485c
extern GXOamAttr data_020e485c[1];
#endif
#ifndef PROTO_LOCAL_data_020e491c
extern GXOamAttr data_020e491c[1];
#endif
#ifndef PROTO_LOCAL_data_020e4b64
extern GXOamAttr data_020e4b64[2];
#endif
#ifndef PROTO_LOCAL_sSkyLineTablesReady
extern u8 sSkyLineTablesReady;
#endif
#ifndef PROTO_LOCAL_data_020e47b4
extern GXOamAttr data_020e47b4[1];
#endif
#ifndef PROTO_LOCAL_data_020e47ec
extern GXOamAttr data_020e47ec[1];
#endif
#ifndef PROTO_LOCAL_SkyShot_AddHit
void SkyShot_AddHit();
#endif
#ifndef PROTO_LOCAL_SkyShot_HasMaxHits
BOOL SkyShot_HasMaxHits();
#endif
#ifndef PROTO_LOCAL_SkySprites_GetMoonPhaseGfx
s32 SkySprites_GetMoonPhaseGfx();
#endif
#ifndef PROTO_LOCAL_data_020e46dc
extern GXOamAttr data_020e46dc[1];
#endif
#ifndef PROTO_LOCAL_data_020e46fc
extern GXOamAttr data_020e46fc[1];
#endif
#ifndef PROTO_LOCAL_data_020e4ba4
extern GXOamAttr data_020e4ba4[2];
#endif
#ifndef PROTO_LOCAL_data_020e4ec8
extern char data_020e4ec8[30];
#endif
#ifndef PROTO_LOCAL_data_020e4bb4
extern GXOamAttr data_020e4bb4[2];
#endif
#ifndef PROTO_LOCAL_data_020e4bc4
extern GXOamAttr data_020e4bc4[2];
#endif
#ifndef PROTO_LOCAL_data_020e4bd4
extern GXOamAttr data_020e4bd4[2];
#endif
#ifndef PROTO_LOCAL_data_020e5230
extern char *data_020e5230[10];
#endif
#ifndef PROTO_LOCAL_data_020e4a24
extern GXOamAttr data_020e4a24[1];
#endif
#ifndef PROTO_LOCAL_data_020e4be4
extern GXOamAttr data_020e4be4[2];
#endif
#ifndef PROTO_LOCAL_sCloudScreenFiles
extern char * *sCloudScreenFiles[3];
#endif
#ifndef PROTO_LOCAL_data_020e488c
extern GXOamAttr data_020e488c[1];
#endif
#ifndef PROTO_LOCAL_data_020e55c0
extern GXOamAttr data_020e55c0[10];
#endif
#ifndef PROTO_LOCAL_data_020e5048
extern char data_020e5048[31];
#endif
#ifndef PROTO_LOCAL_sSkyLineScrollY
extern s32 sSkyLineScrollY[2];
#endif
#ifndef PROTO_LOCAL_data_020e4df4
extern char data_020e4df4[27];
#endif
#ifndef PROTO_LOCAL_data_020e4bf4
extern GXOamAttr data_020e4bf4[2];
#endif
#ifndef PROTO_LOCAL_data_020e482c
extern GXOamAttr data_020e482c[1];
#endif
#ifndef PROTO_LOCAL_data_020e4684
extern GXOamAttr data_020e4684[1];
#endif
#ifndef PROTO_LOCAL_data_020e4c04
extern GXOamAttr data_020e4c04[2];
#endif
#ifndef PROTO_LOCAL_data_020e4674
extern GXOamAttr data_020e4674[1];
#endif
#ifndef PROTO_LOCAL_data_020e4ee8
extern char data_020e4ee8[30];
#endif
#ifndef PROTO_LOCAL_data_020e49a4
extern GXOamAttr data_020e49a4[1];
#endif
#ifndef PROTO_LOCAL_data_020e484c
extern GXOamAttr data_020e484c[1];
#endif
#ifndef PROTO_LOCAL_data_020e4f28
extern char data_020e4f28[30];
#endif
#ifndef PROTO_LOCAL_data_020e4c44
extern GXOamAttr data_020e4c44[2];
#endif
#ifndef PROTO_LOCAL_data_020e47fc
extern GXOamAttr data_020e47fc[1];
#endif
#ifndef PROTO_LOCAL_sSkyBlendLineCache
extern u16 sSkyBlendLineCache[2];
#endif
#ifndef PROTO_LOCAL_data_020e4c74
extern GXOamAttr data_020e4c74[2];
#endif
#ifndef PROTO_LOCAL_data_020e4c84
extern GXOamAttr data_020e4c84[2];
#endif
#ifndef PROTO_LOCAL_data_020e5a34
extern GXOamAttr data_020e5a34[24];
#endif
#ifndef PROTO_LOCAL_data_020e4a1c
extern GXOamAttr data_020e4a1c[1];
#endif
#ifndef PROTO_LOCAL_sSkyLineScrollX
extern s32 sSkyLineScrollX[2];
#endif
#ifndef PROTO_LOCAL_data_020e4814
extern GXOamAttr data_020e4814[1];
#endif
#ifndef PROTO_LOCAL_data_020e4ce4
extern GXOamAttr data_020e4ce4[2];
#endif
#ifndef PROTO_LOCAL_data_020e4d04
extern GXOamAttr data_020e4d04[2];
#endif
#ifndef PROTO_LOCAL_data_020e4630
extern u8 data_020e4630[4];
#endif
#ifndef PROTO_LOCAL_data_020e50a8
extern char data_020e50a8[31];
#endif
#ifndef PROTO_LOCAL_data_020e499c
extern GXOamAttr data_020e499c[1];
#endif
#ifndef PROTO_LOCAL_data_020e477c
extern GXOamAttr data_020e477c[1];
#endif
#ifndef PROTO_LOCAL_data_020e4774
extern GXOamAttr data_020e4774[1];
#endif
#ifndef PROTO_LOCAL_data_020e492c
extern GXOamAttr data_020e492c[1];
#endif
#ifndef PROTO_LOCAL_data_020e486c
extern GXOamAttr data_020e486c[1];
#endif
#ifndef PROTO_LOCAL_data_020e4a14
extern GXOamAttr data_020e4a14[1];
#endif
#ifndef PROTO_LOCAL_data_020e4dac
extern char data_020e4dac[23];
#endif
#ifndef PROTO_LOCAL_data_020e5520
extern GXOamAttr data_020e5520[10];
#endif
#ifndef PROTO_LOCAL_data_020e49f4
extern GXOamAttr data_020e49f4[1];
#endif
#ifndef PROTO_LOCAL_data_020e48f4
extern GXOamAttr data_020e48f4[1];
#endif
#ifndef PROTO_LOCAL_data_020e5028
extern char data_020e5028[31];
#endif
#ifndef PROTO_LOCAL_data_020e4734
extern GXOamAttr data_020e4734[1];
#endif
#ifndef PROTO_LOCAL_sSkyBlackBackdrop
extern u32 sSkyBlackBackdrop[1];
#endif
#ifndef PROTO_LOCAL_data_020e5570
extern GXOamAttr data_020e5570[10];
#endif
#ifndef PROTO_LOCAL_sRainSideToggle
extern s32 sRainSideToggle;
#endif
#ifndef PROTO_LOCAL_data_020e465c
extern GXOamAttr data_020e465c[1];
#endif
#ifndef PROTO_LOCAL_data_020e48bc
extern GXOamAttr data_020e48bc[1];
#endif
#ifndef PROTO_LOCAL_data_020e4f08
extern char data_020e4f08[30];
#endif
#ifndef PROTO_LOCAL_data_020e4884
extern GXOamAttr data_020e4884[1];
#endif
#ifndef PROTO_LOCAL_data_020e4c14
extern GXOamAttr data_020e4c14[2];
#endif
#ifndef PROTO_LOCAL_data_020e466c
extern GXOamAttr data_020e466c[1];
#endif
#ifndef PROTO_LOCAL_data_020e4f48
extern char data_020e4f48[30];
#endif
#ifndef PROTO_LOCAL_data_020e49cc
extern GXOamAttr data_020e49cc[1];
#endif
#ifndef PROTO_LOCAL_data_020e4c64
extern GXOamAttr data_020e4c64[2];
#endif
#ifndef PROTO_LOCAL_data_020e46ec
extern GXOamAttr data_020e46ec[1];
#endif
#ifndef PROTO_LOCAL_sSkyPaletteFiles
extern char *sSkyPaletteFiles[2][2];
#endif
#ifndef PROTO_LOCAL_data_020e49fc
extern GXOamAttr data_020e49fc[1];
#endif
#ifndef PROTO_LOCAL_data_020e4a0c
extern GXOamAttr data_020e4a0c[1];
#endif
#ifndef PROTO_LOCAL_data_020e48cc
extern GXOamAttr data_020e48cc[1];
#endif
#ifndef PROTO_LOCAL_data_020e475c
extern GXOamAttr data_020e475c[1];
#endif
#ifndef PROTO_LOCAL_data_020e4fe8
extern char data_020e4fe8[31];
#endif
#ifndef PROTO_LOCAL_data_020e4b54
extern GXOamAttr data_020e4b54[2];
#endif
#ifndef PROTO_LOCAL_data_020e47c4
extern GXOamAttr data_020e47c4[1];
#endif
#ifndef PROTO_LOCAL_data_020e498c
extern GXOamAttr data_020e498c[1];
#endif
#ifndef PROTO_LOCAL_data_020e489c
extern GXOamAttr data_020e489c[1];
#endif
#ifndef PROTO_LOCAL_sCloudCharFiles
extern char *sCloudCharFiles[5];
#endif
#ifndef PROTO_LOCAL_data_020e4854
extern GXOamAttr data_020e4854[1];
#endif
#ifndef PROTO_LOCAL_data_020e4c94
extern GXOamAttr data_020e4c94[2];
#endif
#ifndef PROTO_LOCAL_data_020e4cb4
extern GXOamAttr data_020e4cb4[2];
#endif
#ifndef PROTO_LOCAL_sSkyCrossingWidth
extern s32 sSkyCrossingWidth;
#endif
#ifndef PROTO_LOCAL_data_020e52e8
extern GXOamAttr data_020e52e8[6];
#endif
#ifndef PROTO_LOCAL_data_020e4fc8
extern char data_020e4fc8[30];
#endif
#ifndef PROTO_LOCAL_data_020e5008
extern char data_020e5008[31];
#endif
#ifndef PROTO_LOCAL_data_020e48ec
extern GXOamAttr data_020e48ec[1];
#endif
#ifndef PROTO_LOCAL_data_020e4b94
extern GXOamAttr data_020e4b94[2];
#endif
#ifndef PROTO_LOCAL_data_020e48c4
extern GXOamAttr data_020e48c4[1];
#endif
#ifndef PROTO_LOCAL_data_020e4844
extern GXOamAttr data_020e4844[1];
#endif
#ifndef PROTO_LOCAL_data_020e483c
extern GXOamAttr data_020e483c[1];
#endif
#ifndef PROTO_LOCAL_data_020e5068
extern char data_020e5068[31];
#endif
#ifndef PROTO_LOCAL_data_020e54d0
extern GXOamAttr data_020e54d0[10];
#endif
#ifndef PROTO_LOCAL_data_020e5208
extern GXOamAttr data_020e5208[5];
#endif
#ifndef PROTO_LOCAL_data_020e4864
extern GXOamAttr data_020e4864[1];
#endif
#ifndef PROTO_LOCAL_data_020e53f8
extern GXOamAttr data_020e53f8[9];
#endif
#ifndef PROTO_LOCAL_SkySprites_UpdateStub
void SkySprites_UpdateStub(void *);
#endif
#ifndef PROTO_LOCAL_Sky_CalcLightColors
void Sky_CalcLightColors(s32 a, s32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_Sky_CalcFogOffset
void Sky_CalcFogOffset(s32 a, s32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_Sky_CalcLightParams
void Sky_CalcLightParams(s32 a, s32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_Sky_UpdateLighting
void Sky_UpdateLighting(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Sky_GetLightColor
s16 Sky_GetLightColor(s32 i);
#endif
#ifndef PROTO_LOCAL_Sky_GetLightParam
u8 Sky_GetLightParam(s32 i);
#endif
#ifndef PROTO_LOCAL_Sky_LoadPaletteFiles
BOOL Sky_LoadPaletteFiles();
#endif
#ifndef PROTO_LOCAL_Sky_AllocPaletteBufs
BOOL Sky_AllocPaletteBufs(u16 **p);
#endif
#ifndef PROTO_LOCAL_Color_Lerp
void Color_Lerp(u16 *d, const u16 *s1, const u16 *s2, s32 t);
#endif
#ifndef PROTO_LOCAL_Color_Lerp6
void Color_Lerp6(u16 *d, u16 *s1, u16 *s2, s32 t);
#endif
#ifndef PROTO_LOCAL_Sky_ApplyPalettes
s32 Sky_ApplyPalettes(s32 x);
#endif
#ifndef PROTO_LOCAL_Sky_BlendPalettes
void Sky_BlendPalettes();
#endif
#ifndef PROTO_LOCAL_Sky_LoadPalettes
s32 Sky_LoadPalettes(s32 x);
#endif
#ifndef PROTO_LOCAL_SkyGradient_Build
void SkyGradient_Build();
#endif
#ifndef PROTO_LOCAL_Sky_UpdateLineTables
void Sky_UpdateLineTables();
#endif
#ifndef PROTO_LOCAL_Sky_VBlankSub
void Sky_VBlankSub();
#endif
#ifndef PROTO_LOCAL_Sky_VBlankMain
void Sky_VBlankMain();
#endif
#ifndef PROTO_LOCAL_Sky_VBlankDisabled
void Sky_VBlankDisabled(void);
#endif
#ifndef PROTO_LOCAL_Sky_FrameOutdoor
void Sky_FrameOutdoor(void);
#endif
#ifndef PROTO_LOCAL_Sky_FrameIndoor
void Sky_FrameIndoor(void);
#endif
#ifndef PROTO_LOCAL_Sky_LoadCloudBg
BOOL Sky_LoadCloudBg(u32 idx);
#endif
#ifndef PROTO_LOCAL_Sky_LoadNextCloudBg
BOOL Sky_LoadNextCloudBg(u32 idx);
#endif
#ifndef PROTO_LOCAL_Sky_LoadStarBg
BOOL Sky_LoadStarBg(u32 idx);
#endif
#ifndef PROTO_LOCAL_Sky_ResetObjGfx
void Sky_ResetObjGfx(void);
#endif
#ifndef PROTO_LOCAL_Sky_SetEngine
BOOL Sky_SetEngine(s32 arg);
#endif
#ifndef PROTO_LOCAL_Sky_Disable
void Sky_Disable(void);
#endif
#ifndef PROTO_LOCAL_Weather_GetFallingPrecip
s32 Weather_GetFallingPrecip(void);
#endif
#ifndef PROTO_LOCAL_Weather_GetCurrent
s32 Weather_GetCurrent(void);
#endif
#ifndef PROTO_LOCAL_Weather_GetLevels
void Weather_GetLevels(s32 *a, s32 *b);
#endif
#ifndef PROTO_LOCAL_Weather_GetPrecipKind
u32 Weather_GetPrecipKind(void);
#endif
#ifndef PROTO_LOCAL_Sky_GetCurrentPalette
u16 *Sky_GetCurrentPalette(void);
#endif
#ifndef PROTO_LOCAL_Sky_GetStarScrollX
u32 Sky_GetStarScrollX(void);
#endif
#ifndef PROTO_LOCAL_Sky_GetStarScrollY
u32 Sky_GetStarScrollY(void);
#endif
#ifndef PROTO_LOCAL_Sky_GetStarViewingTime
void Sky_GetStarViewingTime(ClockDateTime *out, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Weather_RerollRainSlantAlt3
void Weather_RerollRainSlantAlt3(void);
#endif
#ifndef PROTO_LOCAL_Weather_RerollRainSlantAlt2
void Weather_RerollRainSlantAlt2(void);
#endif
#ifndef PROTO_LOCAL_Weather_RerollRainSlantAlt
void Weather_RerollRainSlantAlt(void);
#endif
#ifndef PROTO_LOCAL_Weather_RerollRainSlant
void Weather_RerollRainSlant(void);
#endif
#ifndef PROTO_LOCAL_Sky_OnDayChange
void Sky_OnDayChange(u32 x);
#endif
#ifndef PROTO_LOCAL_Sky_OnSlingshotFired
void Sky_OnSlingshotFired(u32 x);
#endif
#ifndef PROTO_LOCAL_Sky_SwapBuffers
void Sky_SwapBuffers(void);
#endif
#ifndef PROTO_LOCAL_Sky_EndBalloonDrop
void Sky_EndBalloonDrop(void);
#endif
#ifndef PROTO_LOCAL_Sky_PlayBalloonDropSe
void Sky_PlayBalloonDropSe(BOOL x);
#endif
#ifndef PROTO_LOCAL_Sky_IsShootingStarVisible
u32 Sky_IsShootingStarVisible(void);
#endif
#ifndef PROTO_LOCAL_Sky_WishOnShootingStar
void Sky_WishOnShootingStar(void);
#endif
#ifndef PROTO_LOCAL_Sky_RequestBirds
void Sky_RequestBirds(void);
#endif
#ifndef PROTO_LOCAL_data_020e48dc
extern GXOamAttr data_020e48dc[1];
#endif
#ifndef PROTO_LOCAL_data_020e4f68
extern char data_020e4f68[30];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SkySprites_Destruct
SkySprites *SkySprites_Destruct(SkySprites *p);
#endif
#ifndef PROTO_LOCAL_SkyProc_Create
SkyProc *SkyProc_Create();
#endif
#ifndef PROTO_LOCAL_Sky_ProjectToScreenX
void Sky_ProjectToScreenX(s32 *out, VecFx32 *in);
#endif
#ifndef PROTO_LOCAL_SkySprite_FollowShootingStar
BOOL SkySprite_FollowShootingStar(SkySprite *this_);
#endif
#ifndef PROTO_LOCAL_SkySprite_CalcMoonPos
BOOL SkySprite_CalcMoonPos(VecFx32 *out);
#endif
#ifndef PROTO_LOCAL_SkySprite_CalcMoonColors
void SkySprite_CalcMoonColors(SkySprite *this_);
#endif
#ifndef PROTO_LOCAL_SkySprite_SetMoonClarity
void SkySprite_SetMoonClarity(SkySprite *this_);
#endif
#ifndef PROTO_LOCAL_SkySprite_FadeMoonClarity
void SkySprite_FadeMoonClarity(SkySprite *this_);
#endif
#ifndef PROTO_LOCAL_SkySprite_InitMoonPalette
void SkySprite_InitMoonPalette(SkySprite *this_);
#endif
#ifndef PROTO_LOCAL_SkySprite_UpdateMoonPalette
void SkySprite_UpdateMoonPalette(SkySprite *this_);
#endif
#ifndef PROTO_LOCAL_SkySprite_SpawnHitParticle
void SkySprite_SpawnHitParticle(VecFx32 *pos, s32 scale, s32 speed);
#endif
#ifndef PROTO_LOCAL_SkySprite_ProjectFirework
Unk_020bee28_Vec2 SkySprite_ProjectFirework(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_data_020e6124
extern SpriteAnimFrame data_020e6124[44];
#endif
#ifndef PROTO_LOCAL_data_020e4ae8
extern SpriteAnimFrame data_020e4ae8[1];
#endif
#ifndef PROTO_LOCAL_data_020e5258
extern SpriteAnimFrame data_020e5258[4];
#endif
#ifndef PROTO_LOCAL_data_020e58a8
extern SpriteAnimFrame data_020e58a8[9];
#endif
#ifndef PROTO_LOCAL_gWeatherManager
extern WeatherManager gWeatherManager;
#endif
#ifndef PROTO_LOCAL_data_020e4ac4
extern SpriteAnimFrame data_020e4ac4[1];
#endif
#ifndef PROTO_LOCAL_data_020e4a94
extern SpriteAnimFrame data_020e4a94[1];
#endif
#ifndef PROTO_LOCAL_sSkyProcProfile
extern U234_Record sSkyProcProfile;
#endif
#ifndef PROTO_LOCAL_sSkySpriteAnimSeqs
extern SkySpriteAnimDef sSkySpriteAnimSeqs[46];
#endif
#ifndef PROTO_LOCAL_data_020e4b30
extern SpriteAnimFrame data_020e4b30[1];
#endif
#ifndef PROTO_LOCAL_data_020e4b3c
extern SpriteAnimFrame data_020e4b3c[1];
#endif
#ifndef PROTO_LOCAL_data_020e53b0
extern SpriteAnimFrame data_020e53b0[6];
#endif
#ifndef PROTO_LOCAL_data_020e5980
extern SpriteAnimFrame data_020e5980[15];
#endif
#ifndef PROTO_LOCAL_sSkyLight
extern SkyLight sSkyLight;
#endif
#ifndef PROTO_LOCAL_SkySprite_StartAnim
void SkySprite_StartAnim(SkySprite* p);
#endif
#ifndef PROTO_LOCAL_SkySprite_Release
void SkySprite_Release(SkySprite* p);
#endif
#ifndef PROTO_LOCAL_SkySprite_BeginCrossing
void SkySprite_BeginCrossing(SkySprite* p, u8 a, s32 b);
#endif
#ifndef PROTO_LOCAL_SkySprite_AdvanceCrossing
BOOL SkySprite_AdvanceCrossing(SkySprite* p, s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_SkySprite_ProjectWorldPos
void SkySprite_ProjectWorldPos(SkySprite* p, VecFx32* q, s32 a);
#endif
#ifndef PROTO_LOCAL_SkySprite_ProjectCrossing
void SkySprite_ProjectCrossing(SkySprite* p, s32 a);
#endif
#ifndef PROTO_LOCAL_SkySprite_CheckShotHit
BOOL SkySprite_CheckShotHit(SkySprite* p, s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_SkySprite_MakeSoundPos
s32 SkySprite_MakeSoundPos(VecFx32* out, s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_SkySprite_GetSoundPos
void SkySprite_GetSoundPos(SkySprite* p, VecFx32* out);
#endif
#ifndef PROTO_LOCAL_SkySprite_GetPos
void SkySprite_GetPos(SkySprite* p, VecFx32* out);
#endif
#ifndef PROTO_LOCAL_SkySprite_RequestSeSustained
void SkySprite_RequestSeSustained(SkySprite* p, s32 a);
#endif
#ifndef PROTO_LOCAL_SkySprite_RequestSe
void SkySprite_RequestSe(SkySprite* p, s32 a);
#endif
#ifndef PROTO_LOCAL_SkySprite_RequestSeSustainedOn
void SkySprite_RequestSeSustainedOn(SkySprite* p, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_SkyObjGfxLoader_Init
void SkyObjGfxLoader_Init(SkyObjGfxLoader *p);
#endif
#ifndef PROTO_LOCAL_SkyObjGfxLoader_LoadChars
BOOL SkyObjGfxLoader_LoadChars(SkyObjGfxLoader *p, s32 idx);
#endif
#ifndef PROTO_LOCAL_SkyObjGfxLoader_LoadPalettes
BOOL SkyObjGfxLoader_LoadPalettes(SkyObjGfxLoader *p);
#endif
#ifndef PROTO_LOCAL_SkyObjGfxLoader_FlushChars
void SkyObjGfxLoader_FlushChars(SkyObjGfxLoader *p);
#endif
#ifndef PROTO_LOCAL_SkyObjGfxSlot_Init
void SkyObjGfxSlot_Init(SkyObjGfxSlot* p);
#endif
#ifndef PROTO_LOCAL_SkyObjGfxSlot_Upload
void SkyObjGfxSlot_Upload(SkyObjGfxSlot* p, SkyObjGfxLoader *base);
#endif
#ifndef PROTO_LOCAL_SkyObjGfxSlot_Acquire
void SkyObjGfxSlot_Acquire(SkyObjGfxSlot* p, s32 v, SkyObjPalette *x);
#endif
#ifndef PROTO_LOCAL_SkyObjGfxSlot_SetGfx
void SkyObjGfxSlot_SetGfx(SkyObjGfxSlot* p, s32 v);
#endif
#ifndef PROTO_LOCAL_SkyObjGfxSlot_RefreshPalette
void SkyObjGfxSlot_RefreshPalette(SkyObjGfxSlot* p, s32 a);
#endif
#ifndef PROTO_LOCAL_SkyObjGfxSlot_Release
void SkyObjGfxSlot_Release(SkyObjGfxSlot* p);
#endif
#ifndef PROTO_LOCAL_SkyObjPalette_Init
SkyObjPalette* SkyObjPalette_Init(SkyObjPalette* p);
#endif
#ifndef PROTO_LOCAL_SkyObjPalette_Load
void SkyObjPalette_Load(SkyObjPalette* p, SkyObjGfxLoader *base, u32 idx);
#endif
#ifndef PROTO_LOCAL_data_020e5704
extern SpriteAnimFrame data_020e5704[8];
#endif
#ifndef PROTO_LOCAL_data_020e4a70
extern SpriteAnimFrame data_020e4a70[1];
#endif
#ifndef PROTO_LOCAL_data_021efc18
extern StarTwinkle data_021efc18;
#endif
#ifndef PROTO_LOCAL_data_020e510c
extern SpriteAnimFrame data_020e510c[3];
#endif
#ifndef PROTO_LOCAL_data_020e4a88
extern SpriteAnimFrame data_020e4a88[1];
#endif
#ifndef PROTO_LOCAL_data_020e4aa0
extern SpriteAnimFrame data_020e4aa0[1];
#endif
#ifndef PROTO_LOCAL_data_020e4aac
extern SpriteAnimFrame data_020e4aac[1];
#endif
#ifndef PROTO_LOCAL_data_020e5130
extern SpriteAnimFrame data_020e5130[3];
#endif
#ifndef PROTO_LOCAL_data_020e5154
extern SpriteAnimFrame data_020e5154[3];
#endif
#ifndef PROTO_LOCAL_data_020e519c
extern SpriteAnimFrame data_020e519c[3];
#endif
#ifndef PROTO_LOCAL_data_020e51c0
extern SpriteAnimFrame data_020e51c0[3];
#endif
#ifndef PROTO_LOCAL_data_020e4af4
extern SpriteAnimFrame data_020e4af4[1];
#endif
#ifndef PROTO_LOCAL_data_020e4b00
extern SpriteAnimFrame data_020e4b00[1];
#endif
#ifndef PROTO_LOCAL_data_020e4ddc
extern SpriteAnimFrame data_020e4ddc[2];
#endif
#ifndef PROTO_LOCAL_sSkyGradient
extern SkyGradient sSkyGradient;
#endif
#ifndef PROTO_LOCAL_data_020e4b18
extern SpriteAnimFrame data_020e4b18[1];
#endif
#ifndef PROTO_LOCAL_data_020e51e4
extern SpriteAnimFrame data_020e51e4[3];
#endif
#ifndef PROTO_LOCAL_gSkySprites
extern SkySprites gSkySprites;
#endif
#ifndef PROTO_LOCAL_data_020e4b48
extern SpriteAnimFrame data_020e4b48[1];
#endif
#ifndef PROTO_LOCAL_data_020e56b0
extern SpriteAnimFrame data_020e56b0[7];
#endif
#ifndef PROTO_LOCAL_data_020e5d04
extern SpriteAnimFrame data_020e5d04[44];
#endif
#ifndef PROTO_LOCAL_data_020e57d0
extern SpriteAnimFrame data_020e57d0[9];
#endif
#ifndef PROTO_LOCAL_data_020e4ab8
extern SpriteAnimFrame data_020e4ab8[1];
#endif
#ifndef PROTO_LOCAL_sSkyHBlankTask
extern HBlankTask sSkyHBlankTask;
#endif
#ifndef PROTO_LOCAL_data_020e583c
extern SpriteAnimFrame data_020e583c[9];
#endif
#ifndef PROTO_LOCAL_data_020e5288
extern SpriteAnimFrame data_020e5288[4];
#endif
#ifndef PROTO_LOCAL_data_020e6334
extern SpriteAnimFrame data_020e6334[44];
#endif
#ifndef PROTO_LOCAL_data_020e5318
extern SpriteAnimFrame data_020e5318[4];
#endif
#ifndef PROTO_LOCAL_data_020e5348
extern SpriteAnimFrame data_020e5348[4];
#endif
#ifndef PROTO_LOCAL_data_020e5914
extern SpriteAnimFrame data_020e5914[9];
#endif
#ifndef PROTO_LOCAL_data_020e5764
extern SpriteAnimFrame data_020e5764[9];
#endif
#ifndef PROTO_LOCAL_data_020e5af4
extern SpriteAnimFrame data_020e5af4[44];
#endif
#ifndef PROTO_LOCAL_data_020e4a7c
extern SpriteAnimFrame data_020e4a7c[1];
#endif
#ifndef PROTO_LOCAL_data_020e5f14
extern SpriteAnimFrame data_020e5f14[44];
#endif
#ifndef PROTO_LOCAL_data_020e4adc
extern SpriteAnimFrame data_020e4adc[1];
#endif
#ifndef PROTO_LOCAL_data_020e4a64
extern SpriteAnimFrame data_020e4a64[1];
#endif
#ifndef PROTO_LOCAL_data_020e4b24
extern SpriteAnimFrame data_020e4b24[1];
#endif
#ifndef PROTO_LOCAL_data_020e5178
extern SpriteAnimFrame data_020e5178[3];
#endif
#ifndef PROTO_LOCAL_data_020e4b0c
extern SpriteAnimFrame data_020e4b0c[1];
#endif
#ifndef PROTO_LOCAL_data_020e50e8
extern SpriteAnimFrame data_020e50e8[3];
#endif
#ifndef PROTO_LOCAL_SkySprites_ApplyRainbowBlend
void SkySprites_ApplyRainbowBlend(SkySprites *obj);
#endif
#ifndef PROTO_LOCAL_SkySprites_OnStarWish
void SkySprites_OnStarWish(SkySprites *obj);
#endif
#ifndef PROTO_LOCAL_SkySprites_Start
void SkySprites_Start(SkySprites *obj);
#endif
#ifndef PROTO_LOCAL_SkySprites_Stop
void SkySprites_Stop(SkySprites *obj);
#endif
#ifndef PROTO_LOCAL_SkySprites_UpdateEvents
void SkySprites_UpdateEvents(SkySprites *obj);
#endif
#ifndef PROTO_LOCAL_SkySprites_UpdateEventsIndoor
void SkySprites_UpdateEventsIndoor(SkySprites *obj);
#endif
#ifndef PROTO_LOCAL_SkySprites_Update
void SkySprites_Update(SkySprites *obj);
#endif
#ifndef PROTO_LOCAL_SkySprites_UpdateIndoor
void SkySprites_UpdateIndoor(SkySprites *obj);
#endif
#ifndef PROTO_LOCAL_SkySprites_Draw
void SkySprites_Draw(SkySprites *obj);
#endif
#ifndef PROTO_LOCAL_RainSe_Init
void RainSe_Init(RainSndChannel *p);
#endif
#ifndef PROTO_LOCAL_RainSe_Update
void RainSe_Update(RainSndChannel *p);
#endif
#ifndef PROTO_LOCAL_RainSe_Release
void RainSe_Release(RainSndChannel *p);
#endif
#ifndef PROTO_LOCAL_RainSe_InitVolume
void RainSe_InitVolume(RainSndChannel *p);
#endif
#ifndef PROTO_LOCAL_RainSe_FadeVolume
void RainSe_FadeVolume(RainSndChannel *o);
#endif
#ifndef PROTO_LOCAL_Sky_CalcStarScrollX
u16 Sky_CalcStarScrollX(WeatherManager *self, ClockDateTime *date);
#endif
#ifndef PROTO_LOCAL_Sky_CalcStarScrollY
u32 Sky_CalcStarScrollY(WeatherManager *self, ClockDateTime *d);
#endif
#ifndef PROTO_LOCAL_Sky_GetStarScrollYNow
u32 Sky_GetStarScrollYNow(WeatherManager *self);
#endif
}
#endif

#endif
