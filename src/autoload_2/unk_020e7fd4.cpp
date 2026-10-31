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
extern "C" void TouchPanel_Init(void) {
    TPCalibrateParam calib;

    TP_Init();
    TP_GetUserInfo(&calib);
    TP_SetCalibrateParam(&calib);
    TP_RequestSetStabilityAsync(3, 30);
    TP_WaitBusy(8);
    if (TP_CheckError(8) != 0) Fatal_Trap();
    TP_RequestAutoSamplingStartAsync(0, 4, sTouchSampleBuf, 9);
    TP_WaitBusy(2);
    if (TP_CheckError(2) != 0) Fatal_Trap();
    gTouchHeld = 0;
    gTouchChanged = 0;
    gTouchX = 0xff;
    gTouchY = 0xff;
}

static u8 sInputReplayTouch;
extern "C" void Input_ReplayTouch(void) { sInputReplayTouch = 1; }

extern "C" void TouchPanel_Update(void) {
    TPData buf[4];
    s32 idx;
    s32 i;
    BOOL touched;

    idx = TP_GetLatestIndexInAuto();
    touched = FALSE;
    for (i = 0; i < 4; i++) {
        s32 j = idx - 4 + i;
        if (j < 0) j += 9;
        if (sTouchSampleBuf[j].touch != 0) touched = TRUE;
        if (sTouchSampleBuf[j].validity != 0) {
            buf[i].touch = 0;
        } else {
            buf[i] = sTouchSampleBuf[j];
        }
    }
#ifdef HOST
    if (sTouchSampleBuf[idx].touch != 0 && sTouchSampleBuf[idx].validity == 0) {
        TP_GetCalibratedPoint(&sTouchPoint, &sTouchSampleBuf[idx]);
    } else {
        sTouchPoint.touch = 0;
        sTouchPoint.x = 0xff;
        sTouchPoint.y = 0xff;
        sTouchPoint.validity = 0;
    }
#else
    if (buf[3].touch != 0 && buf[2].touch != 0 && buf[1].touch != 0) {
        TP_GetCalibratedPoint(&sTouchPoint, &buf[2]);
    } else if (buf[0].touch != 0 && buf[1].touch != 0 && buf[2].touch != 0) {
        TP_GetCalibratedPoint(&sTouchPoint, &buf[1]);
    } else if (!touched) {
        sTouchPoint.touch = 0;
        sTouchPoint.x = 0xff;
        sTouchPoint.y = 0xff;
        sTouchPoint.validity = 0;
    }
#endif
    gTouchChanged = sTouchPoint.touch ^ gTouchHeld;
    gTouchHeld = sTouchPoint.touch;
    if (sInputReplayTouch) {
        if (gTouchHeld) gTouchChanged = 1;
        sInputReplayTouch = 0;
    }
    gTouchX = sTouchPoint.x;
    gTouchY = sTouchPoint.y;
}

u8 gTouchChanged;
u8 gTouchHeld;
u16 gTouchY;
u16 gTouchX;
TPData sTouchPoint;
TPData sTouchSampleBuf[9];
