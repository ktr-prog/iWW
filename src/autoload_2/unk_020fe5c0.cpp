#include "gfx/SplReal.h"
#include "types.h"
#include "gfx/SplPtclTypes.h"
#include "gfx/SplParticleViews.h"
#include "gfx/VecFx32.h"
#include "gfx/SplTex.h"
#include "gfx/MagF.h"
#include "gfx/P.h"
#include "nitro/mtx.h"
#include "gfx/SplEmitterE.h"
#include "nitro/io_access.h"
#include "proto/autoload_2/unk_020fe4b4.h"
#include "proto/autoload_2/unk_020fe5c0.h"
#include "proto/autoload_2/unk_02117984.h"

struct P;







struct Res {
#ifdef HOST64
    Hdr * hdr;
    u8 p4[0x8];
    Tex * p8;
    u8 pc[0x8];
    Tab * p10;
#else
    Hdr *hdr;
    u8 p4[4];
    Tex *p8;
    u8 pc[4];
    Tab *p10;
#endif
};









extern "C" {
extern u32 data_021f5c3c;
extern const s16 data_02135f44[];
extern VecFx16 data_0213bba4;

void VEC_Fx16CrossProduct(const VecFx16 *a, const VecFx16 *b, VecFx16 *out);
s32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
void VEC_Fx16Normalize(const VecFx16 *src, VecFx16 *dst);
s32 VEC_Fx16DotProduct(const VecFx16 *a, const VecFx16 *b);
void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
void MTX_RotX33_(MtxFx33 *m, s32 s, s32 c);
void MTX_RotY33_(MtxFx33 *m, s32 s, s32 c);
void MTX_RotZ33_(MtxFx33 *m, s32 s, s32 c);
void MTX_MultVec33(const VecFx32 *v, const MtxFx33 *m, VecFx32 *dst);
u32 OS_DisableInterrupts(void);
void OS_RestoreInterrupts(u32 old);
void OSi_UnlockVram(u32 a, u32 b);
s32 OSi_TryLockVram(u32 a, u32 b);
s32 PXI_IsCallbackReady(u32 a, u32 b);
void PXI_SetFifoRecvCallback(u32 a, void *b);
s32 PXI_SendWordByFifo(u32 a, u32 b, u32 c);
s32 OS_GetLockID(void);
void WvrDummyAsyncCallback(u32 a, u32 b);
void spl_rndm_get_arb_vec_xyz(VecFx32 *v);
void spl_rndm_get_arb_vec_xy(VecFx32 *v);
void spl_push_front(PList *l, P *n);
P *spl_pop_front(PList *l);
void spl_set_cross_to_axis(E *e);
void spl_set_circle_axis(VecFx32 *out, const VecFx32 *in, E *e);
}

static inline s32 FX_Mul(s32 a, s32 b) {
    return (s32)(((s64)a * b + 0x800) >> 12);
}

#define SIN_IDX(i) (data_02135f44[((i) >> 4) * 2])
#define COS_IDX(i) (data_02135f44[((i) >> 4) * 2 + 1])

extern "C" s32 WVR_StartUpAsync(u32 cmd, void (*cb)(u32, u32), u32 arg) {
    PXI_Init();
    if (PXI_IsCallbackReady(15, 1) == 0) {
        return 2;
    }
    while (data_021f5c40 == 0) {
        s32 id = OS_GetLockID();
        if (id == -3) {
            return 7;
        }
        data_021f5c40 = id;
    }
    u32 old = OS_DisableInterrupts();
    if (data_021f5c4c != 0) {
        OS_RestoreInterrupts(old);
        return 5;
    }
    if (data_021f5c44 != 0) {
        OS_RestoreInterrupts(old);
        return 5;
    }
    switch (cmd) {
    case 4:
        if (OSi_TryLockVram(4, data_021f5c40) == 0) {
            OS_RestoreInterrupts(old);
            return 6;
        }
        data_021f5c44 = 4;
        IO_W((volatile u8 *)0x04000242, 0x82);
        break;
    case 8:
        if (OSi_TryLockVram(8, data_021f5c40) == 0) {
            OS_RestoreInterrupts(old);
            return 6;
        }
        data_021f5c44 = 8;
        IO_W((volatile u8 *)0x04000243, 0x82);
        break;
    case 12:
        if (OSi_TryLockVram(12, data_021f5c40) == 0) {
            OS_RestoreInterrupts(old);
            return 6;
        }
        data_021f5c44 = 12;
        IO_W((volatile u8 *)0x04000242, 0x82);
        IO_W((volatile u8 *)0x04000243, 0x8a);
        break;
    default:
        OS_RestoreInterrupts(old);
        return 3;
    }
    if (PXI_IsCallbackReady(15, 0) == 0) {
        PXI_SetFifoRecvCallback(15, (void *)WvrReceiveCallback);
    }
    if (cb == 0) {
        data_021f5c4c = WvrDummyAsyncCallback;
    } else {
        data_021f5c4c = cb;
    }
    data_021f5c48 = arg;
    if (PXI_SendWordByFifo(15, 0x10000, 0) < 0) {
        OSi_UnlockVram(data_021f5c44, data_021f5c40);
        data_021f5c44 = 0;
        data_021f5c4c = 0;
        OS_RestoreInterrupts(old);
        return 4;
    }
    OS_RestoreInterrupts(old);
    return 1;
}

#define LCG() (data_021f5c3c = data_021f5c3c * 0x5eedf715 + 0x1b0cb173)

