#ifndef PROTO_PROTO_OV001_UNK_OV001_022265AC_H
#define PROTO_PROTO_OV001_UNK_OV001_022265AC_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWfcSavedVBlankHandler
extern void (*sWfcSavedVBlankHandler) (void);
#endif
#ifndef PROTO_LOCAL_sWfcSavedIrqMask
extern u32 sWfcSavedIrqMask;
#endif
#ifndef PROTO_LOCAL_WfcIrq_Init
void WfcIrq_Init();
#endif
#ifndef PROTO_LOCAL_WfcIrq_Restore
void WfcIrq_Restore();
#endif
#ifndef PROTO_LOCAL_WfcIrq_VBlank
void WfcIrq_VBlank();
#endif
#ifdef __cplusplus
}
#endif

#endif
