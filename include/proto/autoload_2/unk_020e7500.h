#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_020E7500_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_020E7500_H


#include "types.h"
#include "sys/ListNode.h"
struct Tree;
#ifndef __cplusplus
typedef struct Tree Tree;
#endif
#ifdef __cplusplus
#include "gfx/VecFx32.h"
#include "sys/TreeNode.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Random_SetSeed
void Random_SetSeed(u32 *seed, u32 v);
#endif
#ifndef PROTO_LOCAL_Random_Next
u32 Random_Next(u32 *seed);
#endif
#ifndef PROTO_LOCAL_Random_NextBelow
u32 Random_NextBelow(u32 *seed, u32 n);
#endif
#ifndef PROTO_LOCAL_Main_ResetFrameCounter
void Main_ResetFrameCounter(void);
#endif
#ifndef PROTO_LOCAL_Math_Atan2
s16 Math_Atan2(s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_List_InsertAfter
BOOL List_InsertAfter(List *list, ListNode *node, ListNode *after);
#endif
#ifndef PROTO_LOCAL_List_Remove
BOOL List_Remove(List *list, ListNode *node);
#endif
#ifndef PROTO_LOCAL_List_PushBack
BOOL List_PushBack(List *list, ListNode *node);
#endif
#ifndef PROTO_LOCAL_List_PushFront
BOOL List_PushFront(List *list, ListNode *node);
#endif
#ifndef PROTO_LOCAL_Math_ApproachS32
s32 Math_ApproachS32(s32 *p, s32 target, s32 ratio, s32 max, s32 min);
#endif
#ifndef PROTO_LOCAL_Math_ApproachS32Max
void Math_ApproachS32Max(s32 *p, s32 target, s32 ratio, s32 max);
#endif
#ifndef PROTO_LOCAL_Math_AngleDiffAbs
s32 Math_AngleDiffAbs(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Math_IsInRange
BOOL Math_IsInRange(s32 v, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Math_ApproachS16Div
void Math_ApproachS16Div(s16 *p, s16 target, s16 div, s16 max);
#endif
#ifndef PROTO_LOCAL_Math_StepU8
BOOL Math_StepU8(u8 *p, s16 target, s16 step);
#endif
#ifndef PROTO_LOCAL_Math_StepS16
BOOL Math_StepS16(s16 *p, s16 target, s16 step);
#endif
#ifndef PROTO_LOCAL_Math_StepS32
BOOL Math_StepS32(s32 *p, s32 target, s32 step);
#endif
#ifndef PROTO_LOCAL_Math_StepS32Alt
BOOL Math_StepS32Alt(s32 *p, s32 target, s32 step);
#endif
#ifndef PROTO_LOCAL_Math_StepAngle
BOOL Math_StepAngle(s16 *p, s16 target, s16 step);
#endif
#ifndef PROTO_LOCAL_Math_CountDownU8
u8 Math_CountDownU8(u8 *p);
#endif
#ifndef PROTO_LOCAL_Math_CountDownU16
u16 Math_CountDownU16(u16 *p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Math_ApproachVec
s32 Math_ApproachVec(VecFx32 *p, VecFx32 *target, s32 ratio, s32 max, s32 min);
#endif
#ifndef PROTO_LOCAL_Math_ApproachVecXZ
s32 Math_ApproachVecXZ(VecFx32 *p, VecFx32 *target, s32 ratio, s32 max, s32 min);
#endif
#ifndef PROTO_LOCAL_TreeNode_Construct
TreeNode *TreeNode_Construct(TreeNode *n);
#endif
#ifndef PROTO_LOCAL_TreeNode_Init
void TreeNode_Init(TreeNode *n);
#endif
#ifndef PROTO_LOCAL_TreeNode_Attach
BOOL TreeNode_Attach(Tree *tree, TreeNode *node, TreeNode *parent);
#endif
#ifndef PROTO_LOCAL_TreeNode_Detach
BOOL TreeNode_Detach(Tree *tree, TreeNode *node);
#endif
}
#ifndef PROTO_LOCAL_data_0213a748
extern u16 data_0213a748[1025];
#endif
#ifndef PROTO_LOCAL_gFrameCounter
extern s32 gFrameCounter;
#endif
#ifndef PROTO_LOCAL_data_021f476c
extern s32 data_021f476c;
#endif
#endif

#endif
