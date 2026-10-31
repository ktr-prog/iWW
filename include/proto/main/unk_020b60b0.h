#ifndef PROTO_PROTO_MAIN_UNK_020B60B0_H
#define PROTO_PROTO_MAIN_UNK_020B60B0_H


#include "types.h"
#ifdef __cplusplus
#include "game/TouchPicker.h"
#include "gfx/DebugColor.h"
#include "gfx/VecFx32.h"
struct TouchPickResult;
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_TouchPick_Cast
void TouchPick_Cast(TouchPicker *self, s32 sx, s32 sy, u8 flag);
#endif
#ifndef PROTO_LOCAL_TouchPick_GetGroundPos
BOOL TouchPick_GetGroundPos(TouchPickResult *r, VecFx32 *out);
#endif
}
#ifndef PROTO_LOCAL_sColorPaleRed
extern DebugColor sColorPaleRed;
#endif
#ifndef PROTO_LOCAL_sColorPaleBlue
extern DebugColor sColorPaleBlue;
#endif
#ifndef PROTO_LOCAL_sColorPaleYellow
extern DebugColor sColorPaleYellow;
#endif
#ifndef PROTO_LOCAL_sColorPaleGreen
extern DebugColor sColorPaleGreen;
#endif
#ifndef PROTO_LOCAL_sColorPaleCyan
extern DebugColor sColorPaleCyan;
#endif
#ifndef PROTO_LOCAL_sColorGreyCyan
extern DebugColor sColorGreyCyan;
#endif
#endif

#endif
