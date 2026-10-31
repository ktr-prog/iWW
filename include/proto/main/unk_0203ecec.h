#ifndef PROTO_PROTO_MAIN_UNK_0203ECEC_H
#define PROTO_PROTO_MAIN_UNK_0203ECEC_H


#include "types.h"
#ifdef __cplusplus
#include "gfx/VecFx32.h"
#include "gfx/WorldCurve.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_EmotionSlots_Get
s32 EmotionSlots_Get(u8 *p, s32 i);
#endif
#ifndef PROTO_LOCAL_EmotionSlots_Set
void EmotionSlots_Set(u8 *p, s32 i, u32 v);
#endif
#ifndef PROTO_LOCAL_EmotionSlots_Clear
void EmotionSlots_Clear(u8 *p);
#endif
#ifndef PROTO_LOCAL_Emotion_CountLearned
s32 Emotion_CountLearned(void);
#endif
#ifndef PROTO_LOCAL_Emotion_FindFreeSlot
s32 Emotion_FindFreeSlot(void);
#endif
#ifndef PROTO_LOCAL_Emotion_SetSlot
void Emotion_SetSlot(s32 i, s32 v);
#endif
#ifndef PROTO_LOCAL_Emotion_GetSlot
s32 Emotion_GetSlot(s32 i);
#endif
#ifndef PROTO_LOCAL_Emotion_FindSlot
s32 Emotion_FindSlot(u32 id);
#endif
#ifndef PROTO_LOCAL_WorldCurve_AngleToDistance
u32 WorldCurve_AngleToDistance(u32 x);
#endif
#ifndef PROTO_LOCAL_WorldCurve_GetAngleScale
s32 WorldCurve_GetAngleScale(void);
#endif
#ifndef PROTO_LOCAL_WorldCurve_GetRadius
s32 WorldCurve_GetRadius(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_WorldCurve_ToCurved
s32 WorldCurve_ToCurved(VecFx32 *out, const VecFx32 *in);
#endif
#ifndef PROTO_LOCAL_WorldCurve_Apply
s32 WorldCurve_Apply(VecFx32 *out, const VecFx32 *in);
#endif
#ifndef PROTO_LOCAL_WorldCurve_FromCurved
s32 WorldCurve_FromCurved(VecFx32 *out, const VecFx32 *in);
#endif
#ifndef PROTO_LOCAL_WorldCurve_GetHorizonAngle
s16 WorldCurve_GetHorizonAngle(const VecFx32 *o);
#endif
#ifndef PROTO_LOCAL_WorldCurve_Update
void WorldCurve_Update(WorldCurve *o, const VecFx32 *in);
#endif
}
#ifndef PROTO_LOCAL_sWorldCurveZScale
extern s32 sWorldCurveZScale;
#endif
#ifndef PROTO_LOCAL_gWorldCurve
extern WorldCurve gWorldCurve;
#endif
#endif

#endif
