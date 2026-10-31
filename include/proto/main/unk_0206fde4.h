#ifndef PROTO_PROTO_MAIN_UNK_0206FDE4_H
#define PROTO_PROTO_MAIN_UNK_0206FDE4_H


#include "types.h"
#include "gfx/Mtx43.h"
#ifdef __cplusplus
#include "save/MuseumData.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_CpuMtx_StoreToStack
void CpuMtx_StoreToStack(u32 i);
#endif
#ifndef PROTO_LOCAL_CpuMtx_RestoreFromStack
void CpuMtx_RestoreFromStack(u32 i);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Museum_CountDonatedFossilsInGroup
s32 Museum_CountDonatedFossilsInGroup(MuseumData *a, s32 b);
#endif
}
#ifndef PROTO_LOCAL_sCpuMtxStack
extern Mtx43 sCpuMtxStack[31];
#endif
#endif

#endif
