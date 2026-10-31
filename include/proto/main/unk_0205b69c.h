#ifndef PROTO_PROTO_MAIN_UNK_0205B69C_H
#define PROTO_PROTO_MAIN_UNK_0205B69C_H


#include "types.h"
#ifdef __cplusplus
#include "gfx/HBlankTask.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_HBlank_Reset
void HBlank_Reset();
#endif
#ifndef PROTO_LOCAL_HBlank_Init
void HBlank_Init();
#endif
#ifndef PROTO_LOCAL_HBlank_RunFrame
void HBlank_RunFrame();
#endif
#ifndef PROTO_LOCAL_HBlank_RunVBlank
void HBlank_RunVBlank();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_HBlank_Add
BOOL HBlank_Add(HBlankTask *t, void (*a)(), void (*b)(), void (*c)());
#endif
#ifndef PROTO_LOCAL_HBlank_Remove
BOOL HBlank_Remove(HBlankTask *t);
#endif
}
#ifndef PROTO_LOCAL_sHBlankListHead
extern HBlankTask *sHBlankListHead;
#endif
#ifndef PROTO_LOCAL_sHBlankListTail
extern HBlankTask *sHBlankListTail;
#endif
#endif

#endif
