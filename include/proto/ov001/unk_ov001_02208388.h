#ifndef PROTO_PROTO_OV001_UNK_OV001_02208388_H
#define PROTO_PROTO_OV001_UNK_OV001_02208388_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWfcPathBuf
extern u8 sWfcPathBuf[0x40];
#endif
#ifndef PROTO_LOCAL_WfcUtil_LocalizePath
u8 *WfcUtil_LocalizePath(u8 *p);
#endif
#ifndef PROTO_LOCAL_WfcUtil_ShowStepIndicator
void WfcUtil_ShowStepIndicator(s32 a);
#endif
#ifndef PROTO_LOCAL_WfcUtil_OpenButtonBar
void WfcUtil_OpenButtonBar(s32 a);
#endif
#ifndef PROTO_LOCAL_WfcUtil_ShowBottomMessage
void WfcUtil_ShowBottomMessage(s32 a);
#endif
#ifndef PROTO_LOCAL_WfcUtil_ShowBottomMessageNum
void WfcUtil_ShowBottomMessageNum(const u16 *name, s32 b);
#endif
#ifndef PROTO_LOCAL_WfcUtil_GetTextFlags
u32 WfcUtil_GetTextFlags();
#endif
#ifdef __cplusplus
}
#endif

#endif
