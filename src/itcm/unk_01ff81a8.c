#include "uptr.h"
#include "nitro/mtx.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "types64.h"
#include "nitro/io_access.h"
#include "proto/autoload_2/unk_021053f4.h"
#include "proto/autoload_2/unk_0213bd28.h"
#include "proto/itcm/unk_01ff8000.h"
#include "proto/itcm/unk_01ff81a8.h"
#include "proto/itcm/unk_01ff8228.h"
#include "proto/itcm/unk_01ff8ad4.h"
#include "proto/itcm/unk_01ff9e10.h"
#include "proto/main/unk_0206d49c.h"
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef int BOOL;
#define TRUE 1
#define FALSE 0
#define NULL 0
#define FX32_ONE ((fx32)0x00001000L)

typedef volatile u64 vu64;
typedef s32 fx32;
typedef s16 fx16;
typedef s64 fx64;

/* ---------------------------------------------------------------- NitroSDK CP / OS */
typedef struct CPContext {
    u64 div_numer;
    u64 div_denom;
    u64 sqrt;
    u16 div_mode;
    u16 sqrt_mode;
} CPContext;

#define reg_CP_DIVCNT     (*(vu16 *)0x04000280)
#define reg_CP_DIV_NUMER  (*(vu64 *)0x04000290)
#define reg_CP_DIV_DENOM  (*(vu64 *)0x04000298)
#define reg_CP_SQRTCNT    (*(vu16 *)0x040002b0)
#define reg_CP_SQRT_PARAM (*(vu64 *)0x040002b8)

#define reg_OS_IME (*(vu16 *)0x04000208)
#define reg_OS_IE  (*(vu32 *)0x04000210)
#define reg_OS_IF  (*(vu32 *)0x04000214)

typedef struct OSIrqCallbackInfo {
    void (*func)(void *);
    u32 enable;
    void *arg;
} OSIrqCallbackInfo;

extern OSIrqCallbackInfo data_027e0058[];
extern u16 data_027e00b8[];
extern u8 data_027e0000[];

static inline BOOL OS_DisableIrq(void) {
    u16 prep = IO_R(&reg_OS_IME);
    IO_W(&reg_OS_IME, 0);
    return (BOOL)prep;
}

static inline BOOL OS_RestoreIrq(BOOL enable) {
    u16 prep = IO_R(&reg_OS_IME);
    IO_W(&reg_OS_IME, (u16)enable);
    return (BOOL)prep;
}

/* ---------------------------------------------------------------- NitroSystem g3d */
typedef struct MtxFx44 {
    fx32 _00, _01, _02, _03;
    fx32 _10, _11, _12, _13;
    fx32 _20, _21, _22, _23;
    fx32 _30, _31, _32, _33;
} MtxFx44;

typedef struct MatAnm {
    u32 flag;
    u32 prmMatColor0;
    u32 prmMatColor1;
    u32 prmPolygonAttr;
    u32 prmTexImage;
    u32 prmTexPltt;
    fx32 scaleS;
    fx32 scaleT;
    fx16 sinR;
    fx16 cosR;
    fx32 transS;
    fx32 transT;
    u16 origW;
    u16 origH;
    fx32 magW;
    fx32 magH;
} MatAnm;

typedef struct AnmObj {
    fx32 frame;
    fx32 ratio;
    void *resAnm;
    void *funcAnm;
    struct AnmObj *next;
    void *resTex;
    u8 priority;
    u8 numMapData;
    u16 mapData[1];
} AnmObj;

typedef struct ResMdl {
    u32 size;
    u32 ofsSbc;
    u32 ofsMat;
    u32 ofsShp;
    u32 ofsEvpMtx;
    u8 sbcType;
    u8 scalingRule;
    u8 texMtxMode;
    u8 numNode;
    u32 pad18;
    fx32 posScale;
    fx32 invPosScale;
} ResMdl;

typedef struct ResDict { u8 revision; u8 numEntry; u16 sizeDictBlk; u16 dummy_; u16 ofsEntry; } ResDict;
typedef struct ResDictEntryHeader { u16 sizeUnit; u16 ofsName; u8 data[4]; } ResDictEntryHeader;

typedef struct ResMat { u16 ofsDictTexToMatList; u16 ofsDictPlttToMatList; ResDict dict; } ResMat;
typedef struct ResDictMatData { u32 offset; } ResDictMatData;
typedef struct ResMatData {
    u16 itemTag;
    u16 size;
    u32 diffAmb;
    u32 specEmi;
    u32 polyAttr;
    u32 polyAttrMask;
    u32 texImageParam;
    u32 texImageParamMask;
    u16 texPlttBase;
    u16 flag;
    u16 origWidth, origHeight;
    fx32 magW, magH;
    fx32 texMtx[1];
} ResMatData;

typedef struct VecFx32 { fx32 x, y, z; } VecFx32;
typedef struct A3 { s32 a[3]; } A3;

typedef struct JntAnm {
    u32 flag;
    VecFx32 scale;
    VecFx32 scaleEx0;
    VecFx32 scaleEx1;
    MtxFx33 rot;
    VecFx32 trans;
} JntAnm;

typedef struct VisAnm { BOOL isVisible; } VisAnm;

typedef struct ResNodeInfo { ResDict dict; } ResNodeInfo;
typedef struct ResNodeData { u16 flag; fx16 _00; } ResNodeData;

typedef struct ResShp { ResDict dict; } ResShp;
typedef struct ResShpData {
    u16 itemTag;
    u16 size;
    u32 flag;
    u32 ofsDL;
    u32 sizeDL;
} ResShpData;

typedef struct ScaleCache { VecFx32 s; VecFx32 inv; } ScaleCache;

struct RS;
typedef struct RenderObj {
    u32 flag;
    ResMdl *resMdl;
    AnmObj *anmMat;
    void (*funcBlendMat)(MatAnm *, AnmObj *, u32);
    AnmObj *anmJnt;
    BOOL (*funcBlendJnt)(JntAnm *, AnmObj *, u32);
    AnmObj *anmVis;
    BOOL (*funcBlendVis)(VisAnm *, AnmObj *, u32);
    void (*cbFunc)(struct RS *);
    u8 cbCmd;
    u8 cbTiming;
    u16 dummy_;
    void (*cbInitFunc)(struct RS *);
    void *ptrUser;
    u8 *ptrUserSbc;
    JntAnm *recJntAnm;
    MatAnm *recMatAnm;
    u32 hintMatAnmExist[2];
    u32 hintJntAnmExist[2];
    u32 hintVisAnmExist[2];
} RenderObj;

typedef struct RS {
    u8 *c;
    RenderObj *pRenderObj;
    u32 flag;
    void (*cbVecFunc[32])(struct RS *);
    u8 cbVecTiming[32];
    u8 currentNode;
    u8 currentMat;
    u8 currentNodeDesc;
    u8 dummy_;
    MatAnm *pMatAnmResult;
    JntAnm *pJntAnmResult;
    VisAnm *pVisAnmResult;
    u32 isMatCached[2];
    u32 isScaleCacheOne[2];
    u32 isEnvCached[2];
    ResNodeInfo *pResNodeInfo;
    ResMat *pResMat;
    ResShp *pResShp;
    fx32 posScale;
    fx32 invPosScale;
    void (*funcJntScale)(JntAnm *, const fx32 *, const u8 *, u32);
    void (*funcJntMtx)(JntAnm *);
    void (*funcTexMtx)(MatAnm *);
    MatAnm tmpMatAnmResult;
    JntAnm tmpJntAnmResult;
    VisAnm tmpVisAnmResult;
} RS;

typedef struct GlbView {
    u8 pad[0x94];
    u32 prmMatColor0;
    u32 prmMatColor1;
    u32 prmPolygonAttr;
} GlbView;

typedef struct GeBuffer {
    u32 idx;
    u32 data[192];
} GeBuffer;

#define reg_G3X_GXFIFO (*(vu32 *)0x04000400)

extern void (*data_0213bd34[])(JntAnm *, const fx32 *, const u8 *, u32);
extern void (*data_0213bd28[])(JntAnm *);
extern void (*data_0213bd40[])(MatAnm *);
extern void (*data_0213be50[])(RS *, u32);
extern void (*data_0213bd60[])(RS *, u32, const ResMatData *, u32);
extern RS *data_021f5cc0;
extern ScaleCache data_021f6ac4[];
extern const u8 data_02135d38[][4];
extern void (*data_0213bd70[])(RS *, u32, const ResShpData *, u32);
extern void (*const data_01ff8ab4[8])(MtxFx44 *, const MatAnm *);
extern MatAnm data_021f5cc4[];
extern GlbView data_027e00c8;
extern const u32 data_02135d18[8];
extern GeBuffer *data_021f89c4;
extern volatile int data_021f89c8;
extern int data_021f89cc;
extern u32 data_0213bfec;

extern void MIi_CpuClear32(u32 data, void *dest, u32 size);
extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern void MIi_CpuCopyFast(const void *src, void *dest, u32 size);
extern void MIi_CpuSend32(const void *src, volatile void *dest, u32 size);
extern void MI_SendGXCommandAsyncFast(u32 dmaNo, const void *src, u32 size, void (*cb)(void *), void *arg);
extern void updateHintVec_(u32 *vec, AnmObj *anm);
extern void MI_SendGXCommandAsync(u32 dmaNo, const void *src, u32 size, void (*cb)(void *), void *arg);
extern void FX_DivAsync(fx32 numer, fx32 denom);
extern fx32 FX_GetDivResult(void);
extern void MI_Zero36B(void *dst);
extern void StrmCallback(void *p, u32 n);

static inline void *GetResDataByIdx(const ResDict *dict, u32 idx)
{
    const ResDictEntryHeader *hdr = (const ResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
    return (void *)&hdr->data[hdr->sizeUnit * idx];
}

static inline ResMatData *GetMatDataByIdx(const ResMat *pResMat, u32 idx)
{
    ResDictMatData *pDictData = (ResDictMatData *)GetResDataByIdx(&pResMat->dict, idx);
    return (ResMatData *)((u8 *)pResMat + pDictData->offset);
}

static inline BOOL BitVecCheck(const u32 *vec, u32 idx)
{
    return (BOOL)(vec[idx >> 5] & (1 << (idx & 31)));
}

static inline void BitVecReset(u32 *vec, u32 idx)
{
    vec[idx >> 5] &= ~(1 << (idx & 31));
}

static inline ResNodeData *GetNodeDataByIdx(const ResNodeInfo *info, u32 idx)
{
    ResDictMatData *pDictData = (ResDictMatData *)GetResDataByIdx(&info->dict, idx);
    return (ResNodeData *)((u8 *)info + pDictData->offset);
}

static inline ResShpData *GetShpDataByIdx(const ResShp *shp, u32 idx)
{
    ResDictMatData *pDictData = (ResDictMatData *)GetResDataByIdx(&shp->dict, idx);
    return (ResShpData *)((u8 *)shp + pDictData->offset);
}

static inline void BitVecSet(u32 *vec, u32 idx)
{
    vec[idx >> 5] |= 1 << (idx & 31);
}

/* ---------------------------------------------------------------- NitroSDK MI (GX command DMA) */
#include "nitro/mi_gxdma.h"
extern MIGXDmaParams data_027e0414;

#define reg_G3X_GXSTAT (*(vu32 *)0x04000600)

static inline u32 G3X_GetCommandFifoStatus(void) {
    return (IO_R(&reg_G3X_GXSTAT) & 0x07000000) >> 24;
}

static inline void G3X_SetFifoIntrCond(u32 cond) {
    IO_W(&reg_G3X_GXSTAT, ((IO_R(&reg_G3X_GXSTAT) & ~0xc0000000) | (cond << 30)));
}

typedef enum { GX_FIFOINTR_COND_DISABLE = 0, GX_FIFOINTR_COND_UNDERHALF = 1, GX_FIFOINTR_COND_EMPTY = 2 } GXFifoIntrCond;

static inline void G3X_SetFifoIntrCond2(GXFifoIntrCond cond) {
    IO_W(&reg_G3X_GXSTAT, ((IO_R(&reg_G3X_GXSTAT) & ~0xc0000000) | (cond << 30)));
}

static inline void G3X_SetFifoIntrCond3(u32 cond) {
    u32 v = IO_R(&reg_G3X_GXSTAT) & ~0xc0000000;
    IO_W(&reg_G3X_GXSTAT, v | (cond << 30));
}

static inline void MIi_CallCallback(void (*callback)(void *), void *arg) {
    if (callback) {
        callback(arg);
    }
}

extern u32 OS_DisableInterrupts(void);
extern u32 OS_RestoreInterrupts(u32 enabled);
extern void (*OS_GetIrqFunction(u32 intrBit))(void);
extern void OS_SetIrqFunction(u32 intrBit, void (*function)(void));
extern void OSi_EnterDmaCallback(u32 dmaNo, void (*callback)(void *), void *arg);

/* PROTOS */
void CPi_RestoreContext(const CPContext *context);
void CP_SaveContext(CPContext *context);
u32 OS_DisableIrqMask(u32 intr);
u32 OS_EnableIrqMask(u32 intr);
u32 OS_ResetRequestIrqMask(u32 intr);
u32 OS_SetIrqMask(u32 intr);
void texmtxCalc_flagRS_(MtxFx44 *m, const MatAnm *a);
void texmtxCalc_flagR_(MtxFx44 *m, const MatAnm *a);
void texmtxCalc_flagS_(MtxFx44 *m, const MatAnm *a);
void texmtxCalc_flagTRS_(MtxFx44 *m, const MatAnm *a);
void texmtxCalc_flagTR_(MtxFx44 *m, const MatAnm *a);
void texmtxCalc_flagTS_(MtxFx44 *m, const MatAnm *a);
void texmtxCalc_flagT_(MtxFx44 *m, const MatAnm *a);
void texmtxCalc_flag_(MtxFx44 *m, const MatAnm *a);
void updateHintVec___kernel(u32 *vec, const AnmObj *anm);
void G3dDrawInternal_(RS *rs, RenderObj *obj);
void G3dDrawInternal_Loop_(RS *rs);
void NNS_G3dDraw(RenderObj *obj);
void NNS_G3dGeBufferOP_N(u32 op, const u32 *args, u32 num);
void NNS_G3dGeSendDL(const void *src, u32 szByte);
void NNSi_G3dFuncSbc_MAT(RS *rs, u32 opt);
void NNSi_G3dFuncSbc_MAT_InternalDefault(RS *rs, u32 opt, const ResMatData *mat, u32 idxMat);
void NNSi_G3dFuncSbc_MTX(RS *rs, u32 opt);
void NNSi_G3dFuncSbc_NODE(RS *rs, u32 opt);
void NNSi_G3dFuncSbc_NODEDESC(RS *rs, u32 opt);
void NNSi_G3dFuncSbc_NOP(RS *rs, u32 opt);
void NNSi_G3dFuncSbc_POSSCALE(RS *rs, u32 opt);
void NNSi_G3dFuncSbc_RET(RS *rs, u32 opt);
void NNSi_G3dFuncSbc_SHP(RS *rs, u32 opt);
void NNSi_G3dFuncSbc_SHP_InternalDefault(RS *rs, u32 opt, const ResShpData *shp, u32 idxShp);
void NNSi_G3dGetJointScaleMaya(JntAnm *pResult, const fx32 *p, const u8 *cmd, u32 srtflag);
void NNSi_G3dSendJointSRTMaya(JntAnm *pResult);
void NNSi_G3dSendTexSRTMaya(MatAnm *pResult);
void MI_SendGXCommandAsync(u32 dmaNo, const void *src, u32 commandLength, void (*callback)(void *), void *arg);
void MI_WaitDma(u32 dmaNo);
void MIi_CheckDma0SourceAddress(u32 dmaNo, uptr src, u32 size, u32 dir);
void MIi_DmaSetParams(u32 dmaNo, uptr src, uptr dest, u32 ctrl);

u32 OS_ResetRequestIrqMask(u32 intr) {
    BOOL ime = OS_DisableIrq();
    u32 prep = IO_R(&reg_OS_IF);
    IO_W(&reg_OS_IF, intr);
    (void)OS_RestoreIrq(ime);
    return prep;
}

