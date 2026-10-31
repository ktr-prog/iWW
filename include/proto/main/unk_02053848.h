#ifndef PROTO_PROTO_MAIN_UNK_02053848_H
#define PROTO_PROTO_MAIN_UNK_02053848_H


#include "types.h"
struct NNSG3dResJntAnm;
#ifndef __cplusplus
typedef struct NNSG3dResJntAnm NNSG3dResJntAnm;
#endif
#ifdef __cplusplus
#include "gfx/ModelSet.h"
#include "gfx/NNSG3dRS.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_AnimModel_SwitchAnmObj
void AnimModel_SwitchAnmObj(void *pv, void *qv);
#endif
#ifndef PROTO_LOCAL_BlendAnimModel_Play
void BlendAnimModel_Play(void *p, void *a, s32 b, s32 c, s32 d, u16 e, u16 f);
#endif
#ifndef PROTO_LOCAL_BlendAnimModel_Play2
void BlendAnimModel_Play2(void *p, void *a, s32 b, s32 c, s32 d, u16 e, u16 f);
#endif
#ifndef PROTO_LOCAL_ThreeLayerAnimModel_AssignJointsToLayer2
void ThreeLayerAnimModel_AssignJointsToLayer2(void *a, u32 b, u32 c);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_ModelSet_Load
BOOL ModelSet_Load(ModelSet *t, void *file, void *heap);
#endif
#ifndef PROTO_LOCAL_ModelSet_Find
void *ModelSet_Find(ModelSet *t, void *name);
#endif
#ifndef PROTO_LOCAL_ModelSet_Release
BOOL ModelSet_Release(ModelSet *t);
#endif
#ifndef PROTO_LOCAL_Anim_GetFrameCountForMode
u16 Anim_GetFrameCountForMode(u32 kind, NNSG3dResJntAnm *p);
#endif
#ifndef PROTO_LOCAL_JointCb_UseRestTranslation
void JointCb_UseRestTranslation(NNSG3dRS *o, s32 x);
#endif
#ifndef PROTO_LOCAL_JointCb_CalcCpuMatrix
void JointCb_CalcCpuMatrix(void *unused, NNSG3dRS *o, void *p);
#endif
}
#endif

#endif
