#ifndef PROTO_PROTO_MAIN_UNK_020ABBCC_H
#define PROTO_PROTO_MAIN_UNK_020ABBCC_H


#include "types.h"
#include "gfx/NNSG3dResMatData.h"
#ifdef __cplusplus
#include "gfx/CachedModel.h"
#include "gfx/VecFx32.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_CharaShadow_Load
BOOL CharaShadow_Load();
#endif
#ifndef PROTO_LOCAL_CharaShadow_UpdateColor
void CharaShadow_UpdateColor();
#endif
#ifndef PROTO_LOCAL_CharaShadow_Unload
void CharaShadow_Unload();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_CharaShadow_DrawFaded
void CharaShadow_DrawFaded(VecFx32 *pos, s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_CharaShadow_Draw
void CharaShadow_Draw(VecFx32 *pos, s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_CharaShadow_DrawPlayer
void CharaShadow_DrawPlayer(VecFx32 *pos, s32 a);
#endif
}
#ifndef PROTO_LOCAL_sCharaShadowPolyId
extern u32 sCharaShadowPolyId;
#endif
#ifndef PROTO_LOCAL_sCharaShadowMatData
extern NNSG3dResMatData *sCharaShadowMatData;
#endif
#ifndef PROTO_LOCAL_sCharaShadowModel
extern CachedModel sCharaShadowModel;
#endif
#endif

#endif
