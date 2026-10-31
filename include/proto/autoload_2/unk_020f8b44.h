#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_020F8B44_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_020F8B44_H


#include "types.h"
struct Fp;
struct Mgr;
#ifndef __cplusplus
typedef struct Fp Fp;
typedef struct Mgr Mgr;
#endif
#ifdef __cplusplus
#include "gfx/V3.h"
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SPL_Load
void SPL_Load(Fp *self, u8 *base);
#endif
#ifndef PROTO_LOCAL_SPL_LoadTexByVRAMManager
s32 SPL_LoadTexByVRAMManager(Fp *self);
#endif
#ifndef PROTO_LOCAL_SPL_LoadTexPlttByVRAMManager
s32 SPL_LoadTexPlttByVRAMManager(Fp *self);
#endif
#ifndef PROTO_LOCAL_SPL_Draw
void SPL_Draw(Mgr *m, s32 *viewMtx, SplPosFn cb);
#endif
}
#ifndef PROTO_LOCAL_data_021f5c38
extern u16 data_021f5c38;
#endif
#endif

#endif
