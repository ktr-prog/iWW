#ifndef PROTO_PROTO_MAIN_UNK_0205F284_H
#define PROTO_PROTO_MAIN_UNK_0205F284_H


#include "types.h"
#include "gfx/Mtx43.h"
#ifdef __cplusplus
#include "gfx/VecFx32.h"
#include "player/FishBobber.h"
class FishBobberPool;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_FishBobberPool_Create
void FishBobberPool_Create(void *parent);
#endif
#ifndef PROTO_LOCAL_FishBobberPool_Destroy
void FishBobberPool_Destroy();
#endif
#ifndef PROTO_LOCAL_FishBobber_GetModelPath
char *FishBobber_GetModelPath(u32 n);
#endif
#ifndef PROTO_LOCAL_FishBobber_GetModelSize
u32 FishBobber_GetModelSize();
#endif
#ifndef PROTO_LOCAL_FishBobber_GetTexVramSize
u32 FishBobber_GetTexVramSize();
#endif
#ifndef PROTO_LOCAL_FishBobber_GetTex4x4VramSize
u32 FishBobber_GetTex4x4VramSize();
#endif
#ifndef PROTO_LOCAL_FishBobber_GetPlttVramSize
u32 FishBobber_GetPlttVramSize();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_FishBobber_GetFloating
FishBobber *FishBobber_GetFloating(s32 idx);
#endif
#ifndef PROTO_LOCAL_FishBobber_Draw
void FishBobber_Draw(FishBobber *self, Mtx43 *m, VecFx32 *arg);
#endif
#ifndef PROTO_LOCAL_Fishing_CalcArcSpeed
void Fishing_CalcArcSpeed(VecFx32 *a, VecFx32 *b, s32 *c, s32 *d, u8 mode);
#endif
}
#ifndef PROTO_LOCAL_sFishBobberPool
extern FishBobberPool sFishBobberPool;
#endif
#ifndef PROTO_LOCAL_sFishBobberPathBuf
extern char sFishBobberPathBuf[0x14];
#endif
#endif

#endif
