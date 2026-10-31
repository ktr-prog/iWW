#ifndef PROTO_PROTO_OV001_UNK_OV001_0221CD74_H
#define PROTO_PROTO_OV001_UNK_OV001_0221CD74_H


#include "types.h"
struct WfcBgMap;
struct WfcPaletteCopy;
#ifndef __cplusplus
typedef struct WfcBgMap WfcBgMap;
typedef struct WfcPaletteCopy WfcPaletteCopy;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_WfcBgMap_Create
void WfcBgMap_Create(void *a);
#endif
#ifndef PROTO_LOCAL_WfcBgMap_Destroy
void WfcBgMap_Destroy();
#endif
#ifndef PROTO_LOCAL_WfcBgMap_RequestTransfer
void WfcBgMap_RequestTransfer();
#endif
#ifndef PROTO_LOCAL_WfcBgMap_Blit
void WfcBgMap_Blit(u8 *a, s32 b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_WfcBgMap_TransferTask
void WfcBgMap_TransferTask();
#endif
#ifndef PROTO_LOCAL_WfcUtil_RequestPaletteLine
void WfcUtil_RequestPaletteLine(void *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_WfcUtil_PaletteLineTask
void WfcUtil_PaletteLineTask(void *task);
#endif
#ifndef PROTO_LOCAL_WfcUtil_RequestBgPalette
void WfcUtil_RequestBgPalette(void *a);
#endif
#ifndef PROTO_LOCAL_WfcUtil_BgPaletteTask
void WfcUtil_BgPaletteTask(void *task);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sWfcBgMap
extern WfcBgMap *sWfcBgMap;
#endif
#ifndef PROTO_LOCAL_sWfcPaletteCopy
extern WfcPaletteCopy sWfcPaletteCopy;
#endif
}
#endif

#endif
