#ifndef PROTO_PROTO_OV099_UNK_OV099_02294C40_H
#define PROTO_PROTO_OV099_UNK_OV099_02294C40_H


#include "types.h"
#include "sys/ProcProfile.h"
#ifdef __cplusplus
#include "menu/PocketMenuUnk.h"
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sPocketMenuUnkProfile
extern ProcProfile sPocketMenuUnkProfile;
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_Create
PocketMenuUnk *PocketMenuUnk_Create();
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_EnterTouchIdle
void PocketMenuUnk_EnterTouchIdle(PocketMenuUnk *s);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_EnterButtonIdle
void PocketMenuUnk_EnterButtonIdle(PocketMenuUnk *s);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_ReturnToIdle
void PocketMenuUnk_ReturnToIdle(PocketMenuUnk *s);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_BeginTouchOnTarget
void PocketMenuUnk_BeginTouchOnTarget(PocketMenuUnk *s, u32 a);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_StartTouchDrag
void PocketMenuUnk_StartTouchDrag(PocketMenuUnk *s, u32 a);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_StartButtonDrag
void PocketMenuUnk_StartButtonDrag(PocketMenuUnk *s, u32 a);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_FlyHandTo
void PocketMenuUnk_FlyHandTo(PocketMenuUnk *s, u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_CancelVramTasks
void PocketMenuUnk_CancelVramTasks(PocketMenuUnk *s);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_IsPocketTarget
BOOL PocketMenuUnk_IsPocketTarget(PocketMenuUnk *s, u32 a);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_IsLetterTarget
BOOL PocketMenuUnk_IsLetterTarget(PocketMenuUnk *s, u32 a);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_TargetToGridIndex
u32 PocketMenuUnk_TargetToGridIndex(PocketMenuUnk *s, u32 a);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_PocketIndexToTarget
u32 PocketMenuUnk_PocketIndexToTarget(PocketMenuUnk *s, u32 a);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_HitPocket
u32 PocketMenuUnk_HitPocket(PocketMenuUnk *s, u32 a, u32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_DropItemAt
BOOL PocketMenuUnk_DropItemAt(PocketMenuUnk *s, u32 a);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_SetSlotItem
void PocketMenuUnk_SetSlotItem(PocketMenuUnk *s, u32 a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_TargetToLetterIndex
u32 PocketMenuUnk_TargetToLetterIndex(PocketMenuUnk *s, u32 a);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_LetterIndexToTarget
u32 PocketMenuUnk_LetterIndexToTarget(PocketMenuUnk *s, u32 a);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_HitLetter
u32 PocketMenuUnk_HitLetter(PocketMenuUnk *s, u32 a, u32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_GetTargetX
s32 PocketMenuUnk_GetTargetX(PocketMenuUnk *s, u32 a);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_GetTargetY
s32 PocketMenuUnk_GetTargetY(PocketMenuUnk *s, u32 a);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_IsSlotDisabled
BOOL PocketMenuUnk_IsSlotDisabled(PocketMenuUnk *s, u32 a);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_IsSlotEmpty
BOOL PocketMenuUnk_IsSlotEmpty(PocketMenuUnk *s, u32 a);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_GetItem
u32 PocketMenuUnk_GetItem(PocketMenuUnk *s, u32 a);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_GetItemFlags
u32 PocketMenuUnk_GetItemFlags(PocketMenuUnk *s, u32 a);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_ClearSelection
void PocketMenuUnk_ClearSelection(PocketMenuUnk *s);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_SelectTarget
void PocketMenuUnk_SelectTarget(PocketMenuUnk *s, u32 a);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_ClearHighlights
void PocketMenuUnk_ClearHighlights(PocketMenuUnk *s);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_HighlightTarget
void PocketMenuUnk_HighlightTarget(PocketMenuUnk *s, u32 a);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_HasTouchMoved
BOOL PocketMenuUnk_HasTouchMoved(PocketMenuUnk *s);
#endif
#ifndef PROTO_LOCAL_PocketMenuUnk_IsTouchHeldFor
BOOL PocketMenuUnk_IsTouchHeldFor(PocketMenuUnk *self, s32 v);
#endif
}
#endif

#endif
