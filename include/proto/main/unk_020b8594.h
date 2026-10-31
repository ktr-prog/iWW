#ifndef PROTO_PROTO_MAIN_UNK_020B8594_H
#define PROTO_PROTO_MAIN_UNK_020B8594_H


#include "types.h"
#ifdef __cplusplus
#include "gfx/BgTransfer.h"
#include "gfx/TexTransfer.h"
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_TexTransfer_GetPlttCost
u8 TexTransfer_GetPlttCost(TexTransfer *p);
#endif
#ifndef PROTO_LOCAL_BgTransfer_GetScreenCost
u8 BgTransfer_GetScreenCost(BgTransfer *p);
#endif
#ifndef PROTO_LOCAL_BgTransfer_GetPaletteCost
u8 BgTransfer_GetPaletteCost(BgTransfer *p);
#endif
#ifndef PROTO_LOCAL_BgTransfer_GetPaletteRangeCost
u8 BgTransfer_GetPaletteRangeCost(BgTransfer *p);
#endif
}
#endif

#endif
