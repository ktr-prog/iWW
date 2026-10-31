#ifndef PROTO_PROTO_OV068_UNK_OV068_0226B9A8_H
#define PROTO_PROTO_OV068_UNK_OV068_0226B9A8_H


#include "types.h"
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#include "gfx/AnimModel.h"
#include "gfx/NNSG3dRS.h"
#include "room/RoomObjRes.h"
class TaxiInterior;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_TaxiInterior_StopRain
BOOL TaxiInterior_StopRain();
#endif
#ifndef PROTO_LOCAL_TaxiInterior_StartDriverAnim
BOOL TaxiInterior_StartDriverAnim();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sTaxiInteriorProfile
extern ActorProfile sTaxiInteriorProfile;
#endif
#ifndef PROTO_LOCAL_sTaxiInterior
extern TaxiInterior *sTaxiInterior;
#endif
#ifndef PROTO_LOCAL_TaxiInterior_Create
TaxiInterior *TaxiInterior_Create();
#endif
#ifndef PROTO_LOCAL_TaxiInterior_ModelCallback
void TaxiInterior_ModelCallback(NNSG3dRS *p);
#endif
#ifndef PROTO_LOCAL_TaxiInterior_InitModelCallback
void TaxiInterior_InitModelCallback(NNSG3dRS *p);
#endif
#ifndef PROTO_LOCAL_TaxiInterior_OnModelNode
void TaxiInterior_OnModelNode(TaxiInterior *self, u32 node, NNSG3dRS *rs);
#endif
#ifndef PROTO_LOCAL_TaxiInterior_SetPartAnim
void TaxiInterior_SetPartAnim(TaxiInterior *self, u8 k, AnimModel *part, RoomObjRes *res, u8 s0, u32 s1, u16 s2, u16 s3);
#endif
}
#endif

#endif
