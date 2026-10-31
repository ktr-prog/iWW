#ifndef PROTO_PROTO_MAIN_UNK_02060B9C_H
#define PROTO_PROTO_MAIN_UNK_02060B9C_H


#include "types.h"
#include "field/InsectSpawnList.h"
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Item_ToPlacedForm
void Item_ToPlacedForm(u16 *out, u16 *in, s32 n);
#endif
#ifndef PROTO_LOCAL_Item_ConvertFakePainting
void Item_ConvertFakePainting(u16 *out, u16 *in);
#endif
#ifndef PROTO_LOCAL_Grid_ConvertFakePaintings
void Grid_ConvertFakePaintings(void *g);
#endif
#ifndef PROTO_LOCAL_Save_ConvertFakePaintings
void Save_ConvertFakePaintings();
#endif
#ifndef PROTO_LOCAL_Insect_GetSpawnTable
InsectSpawnList *Insect_GetSpawnTable(s32 i);
#endif
#ifndef PROTO_LOCAL_Insect_HourToTimeSlot
s32 Insect_HourToTimeSlot(u32 x);
#endif
#ifndef PROTO_LOCAL_Insect_GetBaseSize
s32 Insect_GetBaseSize(u32 x);
#endif
#ifndef PROTO_LOCAL_Insect_GetHabitat
s32 Insect_GetHabitat(u32 x);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef PROTO_LOCAL_sInsectSpawnAugSlot3
extern InsectSpawnEntry sInsectSpawnAugSlot3[30];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnJulSlot3
extern InsectSpawnEntry sInsectSpawnJulSlot3[28];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnAugSlot2
extern InsectSpawnEntry sInsectSpawnAugSlot2[28];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnJul
extern InsectSpawnList sInsectSpawnJul[6];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnJan
extern InsectSpawnList sInsectSpawnJan[6];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnFeb
extern InsectSpawnList sInsectSpawnFeb[6];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnSep
extern InsectSpawnList sInsectSpawnSep[6];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnAug
extern InsectSpawnList sInsectSpawnAug[6];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnNov
extern InsectSpawnList sInsectSpawnNov[6];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnJulSlot2
extern InsectSpawnEntry sInsectSpawnJulSlot2[24];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnMar
extern InsectSpawnList sInsectSpawnMar[6];
#endif
#ifndef PROTO_LOCAL_gInsectSpawnTables
extern InsectSpawnList *gInsectSpawnTables[12];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnApr
extern InsectSpawnList sInsectSpawnApr[6];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnDec
extern InsectSpawnList sInsectSpawnDec[6];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnMay
extern InsectSpawnList sInsectSpawnMay[6];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnJun
extern InsectSpawnList sInsectSpawnJun[6];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnOct
extern InsectSpawnList sInsectSpawnOct[6];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnJulSlot0
extern InsectSpawnEntry sInsectSpawnJulSlot0[22];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnAugSlot0
extern InsectSpawnEntry sInsectSpawnAugSlot0[22];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnSepSlot2
extern InsectSpawnEntry sInsectSpawnSepSlot2[22];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnAugSlot1
extern InsectSpawnEntry sInsectSpawnAugSlot1[20];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnSepSlot3
extern InsectSpawnEntry sInsectSpawnSepSlot3[20];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnJulSlot1
extern InsectSpawnEntry sInsectSpawnJulSlot1[20];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnJunSlot2
extern InsectSpawnEntry sInsectSpawnJunSlot2[18];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnJunSlot3
extern InsectSpawnEntry sInsectSpawnJunSlot3[18];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnJulSlot5
extern InsectSpawnEntry sInsectSpawnJulSlot5[18];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnAugSlot5
extern InsectSpawnEntry sInsectSpawnAugSlot5[18];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnJunSlot1
extern InsectSpawnEntry sInsectSpawnJunSlot1[14];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnJunSlot4
extern InsectSpawnEntry sInsectSpawnJunSlot4[14];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnJunSlot5
extern InsectSpawnEntry sInsectSpawnJunSlot5[14];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnAugSlot4
extern InsectSpawnEntry sInsectSpawnAugSlot4[14];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnSepSlot5
extern InsectSpawnEntry sInsectSpawnSepSlot5[14];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnJunSlot0
extern InsectSpawnEntry sInsectSpawnJunSlot0[14];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnSepSlot0
extern InsectSpawnEntry sInsectSpawnSepSlot0[14];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnSepSlot4
extern InsectSpawnEntry sInsectSpawnSepSlot4[14];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnNovSlot2
extern InsectSpawnEntry sInsectSpawnNovSlot2[12];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnNovSlot3
extern InsectSpawnEntry sInsectSpawnNovSlot3[12];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnMarSlot2
extern InsectSpawnEntry sInsectSpawnMarSlot2[12];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnJulSlot4
extern InsectSpawnEntry sInsectSpawnJulSlot4[12];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnMarSlot3
extern InsectSpawnEntry sInsectSpawnMarSlot3[12];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnMaySlot3
extern InsectSpawnEntry sInsectSpawnMaySlot3[12];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnOctSlot2
extern InsectSpawnEntry sInsectSpawnOctSlot2[12];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnOctSlot3
extern InsectSpawnEntry sInsectSpawnOctSlot3[12];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnSepSlot1
extern InsectSpawnEntry sInsectSpawnSepSlot1[12];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnAprSlot3
extern InsectSpawnEntry sInsectSpawnAprSlot3[12];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnAprSlot2
extern InsectSpawnEntry sInsectSpawnAprSlot2[12];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnMaySlot2
extern InsectSpawnEntry sInsectSpawnMaySlot2[12];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnNovSlot4
extern InsectSpawnEntry sInsectSpawnNovSlot4[10];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnMarSlot4
extern InsectSpawnEntry sInsectSpawnMarSlot4[10];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnAprSlot4
extern InsectSpawnEntry sInsectSpawnAprSlot4[10];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnMaySlot1
extern InsectSpawnEntry sInsectSpawnMaySlot1[10];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnMaySlot4
extern InsectSpawnEntry sInsectSpawnMaySlot4[10];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnOctSlot4
extern InsectSpawnEntry sInsectSpawnOctSlot4[10];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnAprSlot1
extern InsectSpawnEntry sInsectSpawnAprSlot1[10];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnMarSlot1
extern InsectSpawnEntry sInsectSpawnMarSlot1[10];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnNovSlot1
extern InsectSpawnEntry sInsectSpawnNovSlot1[8];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnMaySlot5
extern InsectSpawnEntry sInsectSpawnMaySlot5[8];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnMaySlot0
extern InsectSpawnEntry sInsectSpawnMaySlot0[8];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnOctSlot1
extern InsectSpawnEntry sInsectSpawnOctSlot1[8];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnMarSlot0
extern InsectSpawnEntry sInsectSpawnMarSlot0[6];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnMarSlot5
extern InsectSpawnEntry sInsectSpawnMarSlot5[6];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnOctSlot5
extern InsectSpawnEntry sInsectSpawnOctSlot5[6];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnAprSlot0
extern InsectSpawnEntry sInsectSpawnAprSlot0[6];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnNovSlot0
extern InsectSpawnEntry sInsectSpawnNovSlot0[6];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnOctSlot0
extern InsectSpawnEntry sInsectSpawnOctSlot0[6];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnAprSlot5
extern InsectSpawnEntry sInsectSpawnAprSlot5[6];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnNovSlot5
extern InsectSpawnEntry sInsectSpawnNovSlot5[6];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnFebSlot0
extern InsectSpawnEntry sInsectSpawnFebSlot0[4];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnDecSlot3
extern InsectSpawnEntry sInsectSpawnDecSlot3[4];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnJanSlot5
extern InsectSpawnEntry sInsectSpawnJanSlot5[4];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnFebSlot4
extern InsectSpawnEntry sInsectSpawnFebSlot4[4];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnJanSlot1
extern InsectSpawnEntry sInsectSpawnJanSlot1[4];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnDecSlot1
extern InsectSpawnEntry sInsectSpawnDecSlot1[4];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnFebSlot3
extern InsectSpawnEntry sInsectSpawnFebSlot3[4];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnJanSlot0
extern InsectSpawnEntry sInsectSpawnJanSlot0[4];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnFebSlot1
extern InsectSpawnEntry sInsectSpawnFebSlot1[4];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnJanSlot2
extern InsectSpawnEntry sInsectSpawnJanSlot2[4];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnFebSlot2
extern InsectSpawnEntry sInsectSpawnFebSlot2[4];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnFebSlot5
extern InsectSpawnEntry sInsectSpawnFebSlot5[4];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnDecSlot2
extern InsectSpawnEntry sInsectSpawnDecSlot2[4];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnDecSlot4
extern InsectSpawnEntry sInsectSpawnDecSlot4[4];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnDecSlot5
extern InsectSpawnEntry sInsectSpawnDecSlot5[4];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnJanSlot3
extern InsectSpawnEntry sInsectSpawnJanSlot3[4];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnDecSlot0
extern InsectSpawnEntry sInsectSpawnDecSlot0[4];
#endif
#ifndef PROTO_LOCAL_sInsectSpawnJanSlot4
extern InsectSpawnEntry sInsectSpawnJanSlot4[4];
#endif
#endif

#endif
