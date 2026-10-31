#ifndef PROTO_PROTO_OV117_UNK_OV117_02292360_H
#define PROTO_PROTO_OV117_UNK_OV117_02292360_H


#include "types.h"
#ifdef __cplusplus
#include "town/TownMapMarkers.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_TownMapImage_DrawAcre
void TownMapImage_DrawAcre(u8 *buf, s32 bx, s32 by);
#endif
#ifndef PROTO_LOCAL_TownMapImage_AllocGlobal
void TownMapImage_AllocGlobal();
#endif
#ifndef PROTO_LOCAL_TownMapImage_DrawRowGlobal
void TownMapImage_DrawRowGlobal(u32 i);
#endif
#ifndef PROTO_LOCAL_TownMapImage_BuildMarkersGlobal
void TownMapImage_BuildMarkersGlobal(u32 i);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sTownMapImage
extern TownMapImage *sTownMapImage;
#endif
#ifndef PROTO_LOCAL_TownMapMarkers_Clear
void TownMapMarkers_Clear(TownMapMarkers *self);
#endif
#ifndef PROTO_LOCAL_TownMapMarkers_Set
void TownMapMarkers_Set(TownMapMarkers *s, s32 i, s32 x, s32 y, u8 z);
#endif
#ifndef PROTO_LOCAL_TownMapMarkers_Get
TownMapMarker *TownMapMarkers_Get(TownMapMarkers *s, u32 i);
#endif
#ifndef PROTO_LOCAL_TownMapMarkers_GetKind
u8 TownMapMarkers_GetKind(TownMapMarkers *s, u32 i);
#endif
#ifndef PROTO_LOCAL_TownMapMarkers_AddTerrainMarkers
void TownMapMarkers_AddTerrainMarkers(TownMapMarkers *s);
#endif
#ifndef PROTO_LOCAL_TownMapMarkers_AddVillagerHouses
void TownMapMarkers_AddVillagerHouses(TownMapMarkers *s);
#endif
#ifndef PROTO_LOCAL_TownMapMarkers_AddPlayerHouse
void TownMapMarkers_AddPlayerHouse(TownMapMarkers *s);
#endif
#ifndef PROTO_LOCAL_TownMapMarkers_AddMuseum
void TownMapMarkers_AddMuseum(TownMapMarkers *s);
#endif
#ifndef PROTO_LOCAL_TownMapMarkers_AddGateHouse
void TownMapMarkers_AddGateHouse(TownMapMarkers *s);
#endif
#ifndef PROTO_LOCAL_TownMapMarkers_AddAbleSisters
void TownMapMarkers_AddAbleSisters(TownMapMarkers *s);
#endif
#ifndef PROTO_LOCAL_TownMapMarkers_AddTownHall
void TownMapMarkers_AddTownHall(TownMapMarkers *s);
#endif
#ifndef PROTO_LOCAL_TownMapMarkers_AddNookShop
void TownMapMarkers_AddNookShop(TownMapMarkers *s);
#endif
#ifndef PROTO_LOCAL_TownMapMarkers_Copy
void TownMapMarkers_Copy(TownMapMarkers *s, TownMapMarkers *d);
#endif
#ifndef PROTO_LOCAL_TownMapMarkers_AddHouses
void TownMapMarkers_AddHouses(TownMapMarkers *s);
#endif
#ifndef PROTO_LOCAL_TownMapMarkers_AddLandmarks
void TownMapMarkers_AddLandmarks(TownMapMarkers *s);
#endif
#ifndef PROTO_LOCAL_TownMapImage_DrawAcreRow
void TownMapImage_DrawAcreRow(TownMapImage *o, u32 i);
#endif
#ifndef PROTO_LOCAL_TownMapImage_BuildMarkers
void TownMapImage_BuildMarkers(TownMapImage *o, u32 sel);
#endif
#ifndef PROTO_LOCAL_TownMapImage_GetAcre
u8 *TownMapImage_GetAcre(TownMapImage *o, u32 x, u32 y);
#endif
#ifndef PROTO_LOCAL_TownMapImage_CopyPixels
void TownMapImage_CopyPixels(TownMapImage *o, void *a);
#endif
#ifndef PROTO_LOCAL_TownMapImage_GetMarkers
TownMapMarkers *TownMapImage_GetMarkers(TownMapImage *o);
#endif
#ifndef PROTO_LOCAL_TownMapImage_Build
void TownMapImage_Build(void *a, TownMapMarkers *b);
#endif
#ifndef PROTO_LOCAL_TownMapImage_FinishGlobal
void TownMapImage_FinishGlobal(void *a, TownMapMarkers *b);
#endif
}
#endif

#endif
