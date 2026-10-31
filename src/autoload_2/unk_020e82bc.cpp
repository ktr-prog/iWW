#include "types.h"
#include "host_mem.h"
#include "sys/TreeNode.h"
#include "gfx/VecFx32.h"
#include "sys/ListNode.h"
#include "nitro/io_access.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e8208.h"
#include "proto/autoload_2/unk_020e82bc.h"
#include "proto/autoload_2/unk_0211bcdc.h"
#include "proto/main/unk_0206d49c.h"

struct Tree {
    TreeNode *root;
};
struct MtxFx43 {
    s32 m[4][3];
};
struct TPData {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
};
struct TPCalibrateParam {
    s16 x0, xDotSize, y0, yDotSize;
};
struct PadState {
    u16 cur;
    u16 trig;
    s16 dir;
};

extern "C" {
s32 func_02133150(s32, s32);
s32 FX_Div(s32, s32);
s32 VEC_Mag(const VecFx32 *v);
void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
void MTX_RotZ43_(MtxFx43 *m, s32 sin, s32 cos);
void MTX_RotY43_(MtxFx43 *m, s32 sin, s32 cos);
void MTX_RotX43_(MtxFx43 *m, s32 sin, s32 cos);
void MTX_Scale43_(MtxFx43 *m, s32 x, s32 y, s32 z);
void MTX_Concat43(const MtxFx43 *a, const MtxFx43 *b, MtxFx43 *ab);
void Vec_Sub(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);
s32 Vec_MagXZ(const VecFx32 *v);
void Vec_Scale(VecFx32 *v, s32 s);
u16 TP_GetLatestIndexInAuto(void);
void TP_GetCalibratedPoint(TPData *dst, const TPData *src);
BOOL TP_GetUserInfo(TPCalibrateParam *p);
void TP_SetCalibrateParam(const TPCalibrateParam *p);
void TP_RequestSetStabilityAsync(u32, u32);
void TP_WaitBusy(u32);
u32 TP_CheckError(u32);
void TP_RequestAutoSamplingStartAsync(u32, u32, TPData *, u32);

extern u16 data_0213a748[];
extern const s16 kPadDirAngleTable[];
extern const s16 data_02135f44[];
extern s32 gFrameCounter;
extern s32 data_021f476c;
extern TPData sTouchPoint;
extern TPData sTouchSampleBuf[9];
extern PadState gPad;

BOOL List_PushFront(List *list, ListNode *node);
void TreeNode_Init(TreeNode *n);
u32 Random_Next(u32 *seed);
void Mtx43_SetRotZ(MtxFx43 *m, s32 angle);
void Mtx43_SetRotY(MtxFx43 *m, s32 angle);
void Mtx43_SetRotX(MtxFx43 *m, s32 angle);
void Mtx43_SetTranslate(MtxFx43 *m, s32 x, s32 y, s32 z);
}

static inline s32 FX_Mul(s32 a, s32 b) {
    return (s32)(((s64)a * b + 0x800) >> 12);
}

static inline u16 PAD_Read(void) {
    return (u16)(((IO_R((vu16 *)0x04000130) | *HW_SYSWORK(vu16, buttonXY)) ^ 0x2fff) & 0x2fff);
}
static inline BOOL PAD_DetectFold(void) {
    return (*HW_SYSWORK(vu16, buttonXY) & 0x8000) >> 15;
}

#define FX_SinIdx(a) data_02135f44[((a) >> 4) * 2]
#define FX_CosIdx(a) data_02135f44[((a) >> 4) * 2 + 1]
extern "C" void Mtx43_Translate(MtxFx43 *m, s32 x, s32 y, s32 z) {
    MtxFx43 t;
    Mtx43_SetTranslate(&t, x, y, z);
    MTX_Concat43(&t, m, m);
}

extern "C" void Mtx43_Scale(MtxFx43 *m, s32 x, s32 y, s32 z) {
    MtxFx43 t;
    MTX_Scale43_(&t, x, y, z);
    MTX_Concat43(&t, m, m);
}

extern "C" void Mtx43_RotateXYZ(MtxFx43 *m, s32 x, s32 y, s32 z) {
    MtxFx43 t;
    if (z != 0) {
        Mtx43_SetRotZ(&t, z);
        MTX_Concat43(&t, m, m);
    }
    if (y != 0) {
        Mtx43_SetRotY(&t, y);
        MTX_Concat43(&t, m, m);
    }
    if (x != 0) {
        Mtx43_SetRotX(&t, x);
        MTX_Concat43(&t, m, m);
    }
}

extern "C" void Mtx43_RotateX(MtxFx43 *m, s32 angle) {
    MtxFx43 t;
    Mtx43_SetRotX(&t, angle);
    MTX_Concat43(&t, m, m);
}

extern "C" void Mtx43_RotateY(MtxFx43 *m, s32 angle) {
    MtxFx43 t;
    Mtx43_SetRotY(&t, angle);
    MTX_Concat43(&t, m, m);
}

extern "C" void Mtx43_RotateZ(MtxFx43 *m, s32 angle) {
    MtxFx43 t;
    Mtx43_SetRotZ(&t, angle);
    MTX_Concat43(&t, m, m);
}

extern "C" void Mtx43_SetTranslate(MtxFx43 *m, s32 x, s32 y, s32 z) {
    m->m[0][0] = 0x1000;
    m->m[0][1] = 0;
    m->m[0][2] = 0;
    m->m[1][0] = 0;
    m->m[1][1] = 0x1000;
    m->m[1][2] = 0;
    m->m[2][0] = 0;
    m->m[2][1] = 0;
    m->m[2][2] = 0x1000;
    m->m[3][0] = x;
    m->m[3][1] = y;
    m->m[3][2] = z;
}

extern "C" void Mtx43_SetRotX(MtxFx43 *m, s32 angle) {
    MTX_RotX43_(m, FX_SinIdx((u16)angle), FX_CosIdx((u16)angle));
}

extern "C" void Mtx43_SetRotY(MtxFx43 *m, s32 angle) {
    MTX_RotY43_(m, FX_SinIdx((u16)angle), FX_CosIdx((u16)angle));
}

extern "C" void Mtx43_SetRotZ(MtxFx43 *m, s32 angle) {
    MTX_RotZ43_(m, FX_SinIdx((u16)angle), FX_CosIdx((u16)angle));
}

extern const MtxFx43 data_02135934;
const MtxFx43 data_02135934 = {{{0x1000, 0, 0}, {0, 0x1000, 0}, {0, 0, 0x1000}, {0, 0, 0}}};
MtxFx43 data_021f47e0;
