#ifndef PROTO_PROTO_OV003_UNK_OV003_02224E68_H
#define PROTO_PROTO_OV003_UNK_OV003_02224E68_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Field_IsGrownTreeItem
BOOL Field_IsGrownTreeItem(u16 *p);
#endif
#ifndef PROTO_LOCAL_Field_IsGrownSpecialTreeItem
BOOL Field_IsGrownSpecialTreeItem(u16 *p);
#endif
#ifndef PROTO_LOCAL_Field_IsGrownPalmTreeItem
BOOL Field_IsGrownPalmTreeItem(u16 *p);
#endif
#ifndef PROTO_LOCAL_SpawnMask_PickFreeUnit
void SpawnMask_PickFreeUnit(u32 n0, u16 *tbl, s32 *px, s32 *py);
#endif
#ifndef PROTO_LOCAL_SpawnMask_MarkRect
void SpawnMask_MarkRect(u16 *buf, s32 x, s32 y, s32 rad, u8 a, u8 b);
#endif
#ifdef __cplusplus
}
#endif

#endif
