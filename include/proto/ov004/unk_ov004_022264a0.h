#ifndef PROTO_PROTO_OV004_UNK_OV004_022264A0_H
#define PROTO_PROTO_OV004_UNK_OV004_022264A0_H


#include "types.h"
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#include "game/FxVec3.h"
#include "gfx/AnimModel.h"
#include "room/RoomObjRes.h"
class CafeCoffeeSet;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_SyncToBrewster
void CafeCoffeeSet_SyncToBrewster(void);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_SetState00
s32 CafeCoffeeSet_SetState00(void);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_SetState01
s32 CafeCoffeeSet_SetState01(void);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_SetState02
s32 CafeCoffeeSet_SetState02(void);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_SetState03
s32 CafeCoffeeSet_SetState03(void);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_SetState04
s32 CafeCoffeeSet_SetState04(void);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_SetState05
s32 CafeCoffeeSet_SetState05(void);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_SetState06
s32 CafeCoffeeSet_SetState06(void);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_SetState07
s32 CafeCoffeeSet_SetState07(void);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_SetState08
s32 CafeCoffeeSet_SetState08(void);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_SetState09
s32 CafeCoffeeSet_SetState09(void);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_GetState
s32 CafeCoffeeSet_GetState(void);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_IsAnim0BAtFrame9
BOOL CafeCoffeeSet_IsAnim0BAtFrame9(void);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_IsAnim0CDone
BOOL CafeCoffeeSet_IsAnim0CDone(void);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_StartEffectB
void CafeCoffeeSet_StartEffectB(void);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_SetFlagEF8
void CafeCoffeeSet_SetFlagEF8(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sCafeCoffeeSet
extern CafeCoffeeSet *volatile sCafeCoffeeSet;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250d2c
extern FxVec3 data_ov004_02250d2c;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250d44
extern FxVec3 data_ov004_02250d44;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250d5c
extern FxVec3 data_ov004_02250d5c;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250cd8
extern FxVec3 data_ov004_02250cd8;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250cf0
extern FxVec3 data_ov004_02250cf0;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250d08
extern FxVec3 data_ov004_02250d08;
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_Create
CafeCoffeeSet *CafeCoffeeSet_Create();
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_UpdateMatrices
void CafeCoffeeSet_UpdateMatrices(CafeCoffeeSet *o);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_ChangeState
BOOL CafeCoffeeSet_ChangeState(CafeCoffeeSet *o, s32 n);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_UpdateState
void CafeCoffeeSet_UpdateState(CafeCoffeeSet *o);
#endif
#ifndef PROTO_LOCAL_sCafeCoffeeSetProfile
extern ActorProfile sCafeCoffeeSetProfile;
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_EnterState00
BOOL CafeCoffeeSet_EnterState00(CafeCoffeeSet *o);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_UpdateState00
void CafeCoffeeSet_UpdateState00(CafeCoffeeSet *o);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_EnterState01
BOOL CafeCoffeeSet_EnterState01(CafeCoffeeSet *o);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_UpdateState01
void CafeCoffeeSet_UpdateState01(CafeCoffeeSet *o);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_EnterState02
BOOL CafeCoffeeSet_EnterState02(CafeCoffeeSet *o);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_UpdateState02
void CafeCoffeeSet_UpdateState02(CafeCoffeeSet *o);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_EnterState03
BOOL CafeCoffeeSet_EnterState03(CafeCoffeeSet *o);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_UpdateState03
void CafeCoffeeSet_UpdateState03(CafeCoffeeSet *o);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_EnterState04
BOOL CafeCoffeeSet_EnterState04(CafeCoffeeSet *o);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_UpdateState04
void CafeCoffeeSet_UpdateState04(CafeCoffeeSet *o);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_EnterState05
BOOL CafeCoffeeSet_EnterState05(CafeCoffeeSet *o);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_UpdateState05
void CafeCoffeeSet_UpdateState05(CafeCoffeeSet *o);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_EnterState06
BOOL CafeCoffeeSet_EnterState06(CafeCoffeeSet *o);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_UpdateState06
void CafeCoffeeSet_UpdateState06(CafeCoffeeSet *o);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_EnterState08
BOOL CafeCoffeeSet_EnterState08(CafeCoffeeSet *o);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_UpdateState08
void CafeCoffeeSet_UpdateState08(CafeCoffeeSet *o);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_EnterState09
BOOL CafeCoffeeSet_EnterState09(CafeCoffeeSet *o);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_UpdateState09
void CafeCoffeeSet_UpdateState09(CafeCoffeeSet *o);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_LoadPart
void CafeCoffeeSet_LoadPart(CafeCoffeeSet *o, u32 idx, const char *id, const char *x);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_ReleasePart
void CafeCoffeeSet_ReleasePart(CafeCoffeeSet *o, u32 idx);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_InitPartAnim
void CafeCoffeeSet_InitPartAnim(CafeCoffeeSet *o, u32 idx);
#endif
#ifndef PROTO_LOCAL_CafeCoffeeSet_SwitchAnim
void CafeCoffeeSet_SwitchAnim(CafeCoffeeSet *self, u32 id, AnimModel *m, RoomObjRes *res, u8 a5, s32 a6, u32 a7, u32 a8);
#endif
}
#endif

#endif
