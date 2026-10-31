#ifndef PROTO_PROTO_MAIN_UNK_0204C318_H
#define PROTO_PROTO_MAIN_UNK_0204C318_H


#include "types.h"
#include "sys/ClockDate.h"
#ifdef __cplusplus
#include "town/TownState.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_TownState_Construct
void TownState_Construct();
#endif
#ifndef PROTO_LOCAL_TownState_Destruct
void TownState_Destruct();
#endif
#ifndef PROTO_LOCAL_TownState_ClampDate
void TownState_ClampDate(ClockDate *p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_TownState_InitNew
void TownState_InitNew(TownState *p);
#endif
#ifndef PROTO_LOCAL_TownState_Reset
void TownState_Reset(TownState *p);
#endif
#ifndef PROTO_LOCAL_Town_SetNativeFruitTrees
void Town_SetNativeFruitTrees(TownState *p);
#endif
}
#endif

#endif
