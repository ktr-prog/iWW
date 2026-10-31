#ifndef NET_WFCLOADFUNC_H
#define NET_WFCLOADFUNC_H

#include "types.h"

typedef void (*WfcLoadFunc)(const void *src, u32 offset, u32 size);

#ifdef __cplusplus
extern "C" {
#endif
void WfcUtil_LoadFileTo(void *path, WfcLoadFunc fn);
void GX_LoadBG2Char(const void *src, u32 offset, u32 size);
void GX_LoadBG3Char(const void *src, u32 offset, u32 size);
void GX_LoadBG2Scr(const void *src, u32 offset, u32 size);
void GX_LoadBG3Scr(const void *src, u32 offset, u32 size);
void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
void GX_LoadOBJPltt(const void *src, u32 offset, u32 size);
void GX_LoadOBJ(const void *src, u32 offset, u32 size);
#ifdef __cplusplus
}
#endif

#endif
