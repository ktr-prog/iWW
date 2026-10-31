#ifndef PROTO_PROTO_MAIN_UNK_02003850_H
#define PROTO_PROTO_MAIN_UNK_02003850_H


#include "types.h"
#ifdef __cplusplus
#include "snd/TvSound.h"
#include "sys/Heap.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_TvSound_GetMaxSize
u32 TvSound_GetMaxSize();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_TvSound_Create
TvSound *TvSound_Create(Heap *heap, s32 type);
#endif
}
#endif

#endif
