#ifndef PROTO_PROTO_ITCM_UNK_01FFCB2C_H
#define PROTO_PROTO_ITCM_UNK_01FFCB2C_H


#include "types.h"
struct CellGrid;
#ifndef __cplusplus
typedef struct CellGrid CellGrid;
#endif
#ifdef __cplusplus
#include "game/CollisionMap.h"
#include "gfx/Camera.h"
#include "gfx/VecFx32.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_HBlank_Handler
void HBlank_Handler(void);
#endif
#ifndef PROTO_LOCAL_Ground_GetUnitAttr
u32 Ground_GetUnitAttr(s32 x, s32 y);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_TownBlockMap_IsBuried
BOOL TownBlockMap_IsBuried(CellGrid *g, s32 x, s32 z);
#endif
#ifndef PROTO_LOCAL_Camera_GetLookAtPoint
void Camera_GetLookAtPoint(VecFx32 *out, Camera *c);
#endif
#ifndef PROTO_LOCAL_Camera_GetLookAtOffset
void Camera_GetLookAtOffset(VecFx32 *out, Camera *c);
#endif
#ifndef PROTO_LOCAL_CollisionMap_GetBlockRef
CollisionBlockRef *CollisionMap_GetBlockRef(s32 x, s32 z);
#endif
}
#endif

#endif
