#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_020F92D4_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_020F92D4_H


#include "types.h"
#ifdef __cplusplus
#include "gfx/SplEmitterViews.h"
#include "gfx/SplManager.h"
#include "gfx/SplViews.h"
#include "gfx/V3.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_func_020f9690
void func_020f9690(void *e, void *l);
#endif
#ifndef PROTO_LOCAL_sAllocTex
u32 sAllocTex(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_sAllocTexPalette
u32 sAllocTexPalette(u32 a, u32 b);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_spl_calc
void spl_calc(MU *m, EU *e);
#endif
#ifndef PROTO_LOCAL_sDrawParent
void sDrawParent(Pm *mp, SplPosFn a);
#endif
#ifndef PROTO_LOCAL_sDrawChild
void sDrawChild(Pm *mp, SplPosFn a);
#endif
#ifndef PROTO_LOCAL_spl_draw
void spl_draw(Pm *m, SplPosFn a);
#endif
#ifndef PROTO_LOCAL_SPL_Init
PmNew *SPL_Init(void *(*alloc)(u32), s32 n1, s32 n2, u32 a3, u16 a4, u16 a5);
#endif
#ifndef PROTO_LOCAL_func_020f92d4
void func_020f92d4(Pm *self, u8 *base);
#endif
}
#endif

#endif
