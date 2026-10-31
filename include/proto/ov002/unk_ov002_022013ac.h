#ifndef PROTO_PROTO_OV002_UNK_OV002_022013AC_H
#define PROTO_PROTO_OV002_UNK_OV002_022013AC_H


#include "types.h"
#ifdef __cplusplus
#include "npc/VillagerId.h"
#include "player/PlayerId.h"
#include "talk/MsgString.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sPopupChoicePopOffsets
extern s32 sPopupChoicePopOffsets[3];
#endif
#ifndef PROTO_LOCAL_ChoiceIdList_Add
BOOL ChoiceIdList_Add(u8 *p, u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_ChoiceIdList_Clear
void ChoiceIdList_Clear(u8 *p, u8 v);
#endif
#ifndef PROTO_LOCAL_ChoiceIdList_Count
s32 ChoiceIdList_Count(u8 *p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef PROTO_LOCAL_PopupChoice_CopyPlayerIdName
void PopupChoice_CopyPlayerIdName(MsgString *a, PlayerId *b);
#endif
#ifndef PROTO_LOCAL_PopupChoice_CopyResidentName
void PopupChoice_CopyResidentName(MsgString *x, s32 y);
#endif
#ifndef PROTO_LOCAL_PopupChoice_CopyVillagerIdName
void PopupChoice_CopyVillagerIdName(MsgString *a, VillagerId *b);
#endif
#ifndef PROTO_LOCAL_PopupChoice_CopyVillagerName
void PopupChoice_CopyVillagerName(MsgString *x, s32 y);
#endif
#endif

#endif
