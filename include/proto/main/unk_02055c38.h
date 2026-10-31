#ifndef PROTO_PROTO_MAIN_UNK_02055C38_H
#define PROTO_PROTO_MAIN_UNK_02055C38_H


#include "types.h"
#include "nitro/mtx.h"
#ifdef __cplusplus
#include "gfx/MatTexPatAnim.h"
#include "gfx/VecFx32.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Model_BindMatTexByName
s32 Model_BindMatTexByName(void *hdr, const char *name, void *tex, const char *texName, const char *plttName);
#endif
#ifndef PROTO_LOCAL_Model_BindMatTexByIdx
s32 Model_BindMatTexByIdx(void *hdr, const char *name, void *tex, s32 texIdx, s32 plttIdx);
#endif
#ifndef PROTO_LOCAL_Anim_LerpRotMtx
void Anim_LerpRotMtx(MtxFx33 *a, MtxFx33 *b, MtxFx33 *out, s32 t);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Anim_NormalizeVec
void Anim_NormalizeVec(VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_Anim_LerpVec
void Anim_LerpVec(VecFx32 *a, VecFx32 *b, VecFx32 *out, s32 t);
#endif
#ifndef PROTO_LOCAL_MatTexPatAnim_ResumeMaterial
void MatTexPatAnim_ResumeMaterial(MatTexPatAnim *p, void *q);
#endif
}
#ifndef PROTO_LOCAL_G3dRes_FindDictIdx
s32 G3dRes_FindDictIdx(void *p, const char *a);
#endif
#endif

#endif
