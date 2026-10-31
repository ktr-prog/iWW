#ifndef PROTO_PROTO_MAIN_UNK_02052B50_H
#define PROTO_PROTO_MAIN_UNK_02052B50_H


#include "types.h"
#ifdef __cplusplus
#include "game/InfoTableSet.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Gfx_DisableAllBanks
void Gfx_DisableAllBanks();
#endif
#ifndef PROTO_LOCAL_Gfx_ResetDisplayRegs
void Gfx_ResetDisplayRegs();
#endif
#ifndef PROTO_LOCAL_FtrInfoTables_Open
void FtrInfoTables_Open(void *p);
#endif
#ifndef PROTO_LOCAL_FtrInfoTables_Close
void FtrInfoTables_Close(void *p);
#endif
#ifndef PROTO_LOCAL_FtrInfoTables_LoadIndoor
void FtrInfoTables_LoadIndoor(void *p, s32 a);
#endif
#ifndef PROTO_LOCAL_FtrInfoTables_FreeIndoor
void FtrInfoTables_FreeIndoor(void *p);
#endif
#ifndef PROTO_LOCAL_FtrInfo_Init
void FtrInfo_Init();
#endif
#ifndef PROTO_LOCAL_FtrInfo_Exit
void FtrInfo_Exit();
#endif
#ifndef PROTO_LOCAL_FtrInfo_LoadIndoor
void FtrInfo_LoadIndoor(s32 a);
#endif
#ifndef PROTO_LOCAL_FtrInfo_FreeIndoor
void FtrInfo_FreeIndoor();
#endif
#ifndef PROTO_LOCAL_FtrInfo_GetPrice
s32 FtrInfo_GetPrice(s32 n);
#endif
#ifndef PROTO_LOCAL_FtrInfo_GetDmaUnk02
s32 FtrInfo_GetDmaUnk02(s32 n);
#endif
#ifndef PROTO_LOCAL_FtrInfo_GetDmaUnk03Fx
s32 FtrInfo_GetDmaUnk03Fx(s32 n);
#endif
#ifndef PROTO_LOCAL_FtrInfo_GetNameForm
s32 FtrInfo_GetNameForm();
#endif
#ifndef PROTO_LOCAL_FtrInfo_GetNameAttrB
s32 FtrInfo_GetNameAttrB(s32 n);
#endif
#ifndef PROTO_LOCAL_FtrInfo_GetNameAttrA
s32 FtrInfo_GetNameAttrA(s32 n);
#endif
#ifndef PROTO_LOCAL_FtrInfo_GetDmaUnk07
s32 FtrInfo_GetDmaUnk07(s32 n);
#endif
#ifndef PROTO_LOCAL_FtrInfo_GetDmaUnk08
s32 FtrInfo_GetDmaUnk08(s32 n);
#endif
#ifndef PROTO_LOCAL_FtrInfo_GetColor1
s32 FtrInfo_GetColor1(s32 n);
#endif
#ifndef PROTO_LOCAL_FtrInfo_GetColor2
s32 FtrInfo_GetColor2(s32 n);
#endif
#ifndef PROTO_LOCAL_FtrInfo_GetSeries
s32 FtrInfo_GetSeries(s32 n);
#endif
#ifndef PROTO_LOCAL_Ftr_GetSeries
s32 Ftr_GetSeries(u16 *item);
#endif
#ifndef PROTO_LOCAL_FtrInfo_GetClass
s32 FtrInfo_GetClass(s32 n);
#endif
#ifndef PROTO_LOCAL_Ftr_GetClass
s32 Ftr_GetClass(u16 *item);
#endif
#ifndef PROTO_LOCAL_FtrInfo_GetUnk05
s32 FtrInfo_GetUnk05(s32 n);
#endif
#ifndef PROTO_LOCAL_Ftr_GetUnk05
s32 Ftr_GetUnk05(u16 *item);
#endif
#ifndef PROTO_LOCAL_FtrInfo_GetCollectionGroup
s32 FtrInfo_GetCollectionGroup(s32 n);
#endif
#ifndef PROTO_LOCAL_Ftr_GetCollectionGroup
s32 Ftr_GetCollectionGroup(u16 *item);
#endif
#ifndef PROTO_LOCAL_FtrInfo_TestAlwaysFlag4
s32 FtrInfo_TestAlwaysFlag4(s32 n);
#endif
#ifndef PROTO_LOCAL_FtrInfo_GetFlagPairA
s32 FtrInfo_GetFlagPairA(s32 n);
#endif
#ifndef PROTO_LOCAL_Ftr_GetFlagPairA
s32 Ftr_GetFlagPairA(u16 *item);
#endif
#ifndef PROTO_LOCAL_FtrInfo_GetFlagPairB
s32 FtrInfo_GetFlagPairB(s32 n);
#endif
#ifndef PROTO_LOCAL_Ftr_GetFlagPairB
s32 Ftr_GetFlagPairB(u16 *item);
#endif
#ifndef PROTO_LOCAL_FtrInfo_GetUnk06
s32 FtrInfo_GetUnk06(s32 n);
#endif
#ifndef PROTO_LOCAL_Ftr_GetUnk06
s32 Ftr_GetUnk06(u16 *item);
#endif
#ifndef PROTO_LOCAL_FtrInfo_GetDmaUnk04
s32 FtrInfo_GetDmaUnk04(s32 n);
#endif
#ifndef PROTO_LOCAL_FtrInfo_IsLucky
s32 FtrInfo_IsLucky(s32 n);
#endif
#ifndef PROTO_LOCAL_FtrInfo_TestIndoorFlag2
s32 FtrInfo_TestIndoorFlag2(s32 n);
#endif
#ifndef PROTO_LOCAL_FtrInfo_TestIndoorFlag3
BOOL FtrInfo_TestIndoorFlag3(s32 i);
#endif
#ifndef PROTO_LOCAL_FtrInfo_GetIndoorFlagPair
s32 FtrInfo_GetIndoorFlagPair(s32 i);
#endif
#ifndef PROTO_LOCAL_FtrInfo_GetName
u8 *FtrInfo_GetName(s32 i);
#endif
#ifndef PROTO_LOCAL_FtrInfo_TestIndoorFlag6
BOOL FtrInfo_TestIndoorFlag6(s32 i);
#endif
#ifndef PROTO_LOCAL_FtrInfo_TestIndoorFlag7
BOOL FtrInfo_TestIndoorFlag7(s32 i);
#endif
#ifndef PROTO_LOCAL_Ftr_TestIndoorFlag7
BOOL Ftr_TestIndoorFlag7(u16 *p);
#endif
#ifndef PROTO_LOCAL_FtrInfo_TestIndoorFlagC
BOOL FtrInfo_TestIndoorFlagC(s32 i);
#endif
#ifndef PROTO_LOCAL_Ftr_TestIndoorFlagC
BOOL Ftr_TestIndoorFlagC(u16 *p);
#endif
#ifndef PROTO_LOCAL_FtrInfo_GetDmaUnk05Fx
u32 FtrInfo_GetDmaUnk05Fx(s32 i);
#endif
#ifndef PROTO_LOCAL_FtrInfo_GetDmaUnk06
s8 FtrInfo_GetDmaUnk06(s32 i);
#endif
#ifndef PROTO_LOCAL_FtrInfo_GetIndoorUnk0
u8 FtrInfo_GetIndoorUnk0(s32 i);
#endif
#ifndef PROTO_LOCAL_Item_GetFossilGroup
s32 Item_GetFossilGroup(u16 *p);
#endif
#ifndef PROTO_LOCAL_Fossil_CountInGroup
u32 Fossil_CountInGroup(u32 v);
#endif
#ifndef PROTO_LOCAL_Ftr_GetIndexInSeries
u32 Ftr_GetIndexInSeries(u16 *p);
#endif
#ifndef PROTO_LOCAL_FtrInfo_CountInSeries
u32 FtrInfo_CountInSeries(u32 v);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef PROTO_LOCAL_gFtrInfo
extern InfoTableSet gFtrInfo;
#endif
#endif

#endif
