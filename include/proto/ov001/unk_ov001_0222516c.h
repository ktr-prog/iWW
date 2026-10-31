#ifndef PROTO_PROTO_OV001_UNK_OV001_0222516C_H
#define PROTO_PROTO_OV001_UNK_OV001_0222516C_H


#include "types.h"
#include "net/WfcObjGroup.h"
struct WfcTextCanvas;
struct WfcTextWork;
#ifndef __cplusplus
typedef struct WfcTextCanvas WfcTextCanvas;
typedef struct WfcTextWork WfcTextWork;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWfcFontPaths
extern void *sWfcFontPaths[2];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222b894
extern char data_ov001_0222b894[];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222b8a4
extern char data_ov001_0222b8a4[];
#endif
#ifndef PROTO_LOCAL_WfcText_Init
void WfcText_Init();
#endif
#ifndef PROTO_LOCAL_WfcText_Shutdown
void WfcText_Shutdown();
#endif
#ifndef PROTO_LOCAL_WfcText_BgTransferTask
void WfcText_BgTransferTask(u32 task, u8 *flag);
#endif
#ifndef PROTO_LOCAL_WfcText_DestroyBgCanvas
void WfcText_DestroyBgCanvas(u32 idx);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sWfcText
extern WfcTextWork *sWfcText;
#endif
#ifndef PROTO_LOCAL_WfcText_CreateObjCanvas
WfcTextCanvas *WfcText_CreateObjCanvas(u32 mode, u32 w, u32 h, u32 a3, u32 *out, u32 slot);
#endif
#ifndef PROTO_LOCAL_WfcText_DestroyObjCanvas
void WfcText_DestroyObjCanvas(WfcTextCanvas *o);
#endif
#ifndef PROTO_LOCAL_WfcText_CreateBgCanvas
WfcTextCanvas *WfcText_CreateBgCanvas(u32 idx, u32 slot);
#endif
#ifndef PROTO_LOCAL_WfcText_DrawText
void WfcText_DrawText(WfcTextCanvas *o, s32 x, s32 y, s32 color, u32 flags, const u16 *text);
#endif
#ifndef PROTO_LOCAL_WfcText_DrawChar
void WfcText_DrawChar(WfcTextCanvas *o, s32 x, s32 y, s32 color, u16 c, s32 font);
#endif
#ifndef PROTO_LOCAL_WfcText_DrawMonospace
void WfcText_DrawMonospace(WfcTextCanvas *o, s32 x, s32 y, s32 color, s32 w, u16 *p, s32 font);
#endif
#ifndef PROTO_LOCAL_WfcText_DrawTextRect
void WfcText_DrawTextRect(WfcTextCanvas *o, s32 x, s32 y, s32 w, s32 h, s32 color, u32 flags, const u16 *text);
#endif
#ifndef PROTO_LOCAL_WfcText_Clear
void WfcText_Clear(WfcTextCanvas *o, s32 a);
#endif
#ifndef PROTO_LOCAL_WfcText_ArrangeObj
void WfcText_ArrangeObj(WfcTextCanvas *o, s32 x, s32 y, WfcObjGroup *h, s32 priority);
#endif
#ifndef PROTO_LOCAL_WfcText_RequestTransfer
void WfcText_RequestTransfer(WfcTextCanvas *o);
#endif
}
#endif

#endif
