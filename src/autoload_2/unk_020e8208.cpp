#include "types.h"
#include "host_mem.h"
#include "sys/TreeNode.h"
#include "gfx/VecFx32.h"
#include "sys/ListNode.h"
#include "nitro/io_access.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e8208.h"
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
extern "C" void Gfx_InitNop(void) {
}

static u16 sInputReplayKeys;
extern "C" void Input_ReplayKeys(u16 keys) { sInputReplayKeys |= keys; }

extern "C" void Pad_Update(void) {
    u32 keys;

    if (PAD_DetectFold()) {
        keys = 0;
    } else {
        keys = PAD_Read();
    }
    data_021f47d0 = 0;
    gPad.trig = (u16)((keys & (keys ^ sPadPrevHeld)) | sInputReplayKeys);
    sInputReplayKeys = 0;
    sPadPrevHeld = keys;
    gPad.cur = keys;
    gPad.dir = kPadDirAngleTable[(keys & 0xf0) >> 4];
}

const s16 kPadDirAngleTable[16] = {
    0, 16384, -16384, 16384, -32768, 24576, -24576, 24576, 0, 8192, -8192, 8192, -32768, 24576, -24576, 24576,
};
u8 data_021f47d0;
u16 sPadPrevHeld;
PadState gPad;
