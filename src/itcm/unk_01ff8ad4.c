#include "uptr.h"
#include "nitro/mtx.h"
#include "host_labels.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "types64.h"
#include "nitro/io_access.h"
#include "proto/autoload_2/unk_021053f4.h"
#include "proto/autoload_2/unk_0213bd28.h"
#include "proto/itcm/unk_01ff8000.h"
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
#define data_021f6ac4 HOST_LABEL(ScaleCache (*)[], data_021f6ac4)
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

void NNSi_G3dSendJointSRTMaya(JntAnm *pResult) {
    BOOL trFlag = FALSE;
    if (!(pResult->flag & 4)) {
        trFlag = TRUE;
    }
    if ((pResult->flag & 0x20) && !(pResult->flag & 8)) {
        if (trFlag) {
            NNS_G3dGeBufferOP_N(28, (const u32 *)&pResult->trans, 3);
            trFlag = FALSE;
        }
        NNS_G3dGeBufferOP_N(27, (const u32 *)&pResult->scaleEx0, 3);
    }
    if (!(pResult->flag & 2)) {
        if (trFlag) {
            NNS_G3dGeBufferOP_N(25, (const u32 *)&pResult->rot, 12);
        } else {
            NNS_G3dGeBufferOP_N(26, (const u32 *)&pResult->rot, 9);
        }
    } else {
        if (trFlag) {
            NNS_G3dGeBufferOP_N(28, (const u32 *)&pResult->trans, 3);
        }
    }
    if (!(pResult->flag & 1)) {
        NNS_G3dGeBufferOP_N(27, (const u32 *)&pResult->scale, 3);
    }
}

void NNSi_G3dGetJointScaleMaya(JntAnm *pResult, const fx32 *p, const u8 *cmd, u32 srtflag) {
    u32 nodeAttr = cmd[3];
    if (srtflag & 4) {
        pResult->flag |= 1;
        if (nodeAttr & 2) {
            BitVecSet(data_021f5cc0->isScaleCacheOne, cmd[1]);
        }
    } else {
        pResult->scale.x = p[0];
        pResult->scale.y = p[1];
        pResult->scale.z = p[2];
        if (nodeAttr & 2) {
            u32 idx = cmd[1];
            BitVecReset(data_021f5cc0->isScaleCacheOne, idx);
            data_021f6ac4[idx].inv.x = p[3];
            data_021f6ac4[idx].inv.y = p[4];
            data_021f6ac4[idx].inv.z = p[5];
        }
    }
    if (nodeAttr & 1) {
        u32 idxParent = cmd[2];
        pResult->flag |= 0x20;
        if (BitVecCheck(data_021f5cc0->isScaleCacheOne, idxParent)) {
            pResult->flag |= 8;
        } else {
            pResult->scaleEx0 = data_021f6ac4[idxParent].inv;
        }
    }
    pResult->flag |= 0x10;
}

void NNSi_G3dFuncSbc_SHP_InternalDefault(RS *rs, u32 opt, const ResShpData *shp, u32 idxShp) {
    u32 cbTiming;
    BOOL skip;
    cbTiming = rs->cbVecFunc[5] ? rs->cbVecTiming[5] : 0;
    if (cbTiming == 1) {
        rs->flag &= ~0x40;
        rs->cbVecFunc[5](rs);
        cbTiming = rs->cbVecFunc[5] ? rs->cbVecTiming[5] : 0;
        skip = rs->flag & 0x40;
    } else {
        skip = FALSE;
    }
    if (!skip && !(rs->flag & 0x100)) {
        NNS_G3dGeSendDL((const u8 *)shp + shp->ofsDL, shp->sizeDL);
    }
    if (cbTiming == 2) {
        rs->flag &= ~0x40;
        rs->cbVecFunc[5](rs);
        cbTiming = rs->cbVecFunc[5] ? rs->cbVecTiming[5] : 0;
    }
    if (cbTiming == 3) {
        rs->flag &= ~0x40;
        rs->cbVecFunc[5](rs);
    }
}

void NNSi_G3dFuncSbc_SHP(RS *rs, u32 opt) {
    if (!(rs->flag & 0x200) && (rs->flag & 1) && !(rs->flag & 2)) {
        u32 idxShp = *(rs->c + 1);
        const ResShpData *shp = GetShpDataByIdx(rs->pResShp, idxShp);
        data_0213bd70[shp->itemTag](rs, opt, shp, idxShp);
    }
    rs->c += 2;
}

void NNSi_G3dFuncSbc_RET(RS *rs, u32 opt) {
    if (rs->cbVecFunc[1]) {
        rs->cbVecFunc[1](rs);
    }
    rs->flag |= 0x20;
}

void NNSi_G3dFuncSbc_POSSCALE(RS *rs, u32 opt) {
    if (!(rs->flag & 0x100) && !(rs->flag & 0x200)) {
        VecFx32 s;
        if (opt == 0) {
            s.x = s.y = s.z = rs->posScale;
        } else {
            s.x = s.y = s.z = rs->invPosScale;
        }
        NNS_G3dGeBufferOP_N(27, (const u32 *)&s, 3);
    }
    rs->c += 1;
}

void NNSi_G3dFuncSbc_NOP(RS *rs, u32 opt) {
    if (rs->cbVecFunc[0]) {
        rs->cbVecFunc[0](rs);
    }
    rs->c += 1;
}

void NNSi_G3dFuncSbc_NODEDESC(RS *rs, u32 opt) {
    u32 cmdLen = 4;
    u32 curNode;
    JntAnm *pResult;
    u32 cbTiming;
    BOOL skip;

    curNode = *(rs->c + 1);
    rs->currentNodeDesc = (u8)curNode;
    rs->flag |= 0x10;

    if (rs->flag & 0x400) {
        if (opt == 0x40 || opt == 0x60) {
            ++cmdLen;
        }
        if (opt == 0x20 || opt == 0x60) {
            ++cmdLen;
            if (!(rs->flag & 0x100)) {
                u32 arg = *(rs->c + 4);
                NNS_G3dGeBufferOP_N(20, &arg, 1);
            }
        }
        rs->c += cmdLen;
        return;
    }

    if (opt == 0x40 || opt == 0x60) {
        u32 arg;
        ++cmdLen;
        if (opt == 0x40) {
            arg = *(rs->c + 4);
        } else {
            arg = *(rs->c + 5);
        }
        if (!(rs->flag & 0x100)) {
            NNS_G3dGeBufferOP_N(20, &arg, 1);
        }
    }

    rs->pJntAnmResult = &rs->tmpJntAnmResult;

    cbTiming = rs->cbVecFunc[6] ? rs->cbVecTiming[6] : 0;
    if (cbTiming == 1) {
        rs->flag &= ~0x40;
        rs->cbVecFunc[6](rs);
        cbTiming = rs->cbVecFunc[6] ? rs->cbVecTiming[6] : 0;
        skip = rs->flag & 0x40;
    } else {
        skip = FALSE;
    }
    if (!skip) {
        BOOL isUseRecord;
        if (rs->pRenderObj->recJntAnm) {
            pResult = &rs->pRenderObj->recJntAnm[curNode];
            isUseRecord = !(rs->flag & 0x80);
        } else {
            pResult = &rs->tmpJntAnmResult;
            isUseRecord = FALSE;
        }
        if (!isUseRecord) {
            pResult->flag = 0;
            if (!(rs->pRenderObj->anmJnt &&
                  rs->pRenderObj->funcBlendJnt(pResult, rs->pRenderObj->anmJnt, curNode))) {
                const ResNodeData *pNd = GetNodeDataByIdx(rs->pResNodeInfo, curNode);
                const u8 *p = (const u8 *)pNd + sizeof(ResNodeData);
                if (pNd->flag & 1) {
                    pResult->flag |= 4;
                } else {
                    pResult->trans.x = ((const fx32 *)p)[0];
                    pResult->trans.y = ((const fx32 *)p)[1];
                    pResult->trans.z = ((const fx32 *)p)[2];
                    p += 12;
                }
                if (pNd->flag & 2) {
                    pResult->flag |= 2;
                } else if (pNd->flag & 8) {
                    fx32 A, B;
                    u32 idxPivot = (pNd->flag & 0xf0) >> 4;
                    A = ((const fx16 *)p)[0];
                    B = ((const fx16 *)p)[1];
                    MI_Zero36B(&pResult->rot);
                    pResult->rot.a[idxPivot] = (pNd->flag & 0x100) ? -FX32_ONE : FX32_ONE;
                    pResult->rot.a[data_02135d38[idxPivot][0]] = A;
                    pResult->rot.a[data_02135d38[idxPivot][1]] = B;
                    if (pNd->flag & 0x200) B = -B;
                    pResult->rot.a[data_02135d38[idxPivot][2]] = B;
                    if (pNd->flag & 0x400) A = -A;
                    pResult->rot.a[data_02135d38[idxPivot][3]] = A;
                    p += 4;
                } else {
                    pResult->rot.a[0] = pNd->_00;
                    pResult->rot.a[1] = ((const fx16 *)p)[0];
                    pResult->rot.a[2] = ((const fx16 *)p)[1];
                    pResult->rot.a[3] = ((const fx16 *)p)[2];
                    pResult->rot.a[4] = ((const fx16 *)p)[3];
                    pResult->rot.a[5] = ((const fx16 *)p)[4];
                    pResult->rot.a[6] = ((const fx16 *)p)[5];
                    pResult->rot.a[7] = ((const fx16 *)p)[6];
                    pResult->rot.a[8] = ((const fx16 *)p)[7];
                    p += 16;
                }
                rs->funcJntScale(pResult, (const fx32 *)p, rs->c, pNd->flag);
            }
        }
        rs->pJntAnmResult = pResult;
    }

    if (cbTiming == 2) {
        rs->flag &= ~0x40;
        rs->cbVecFunc[6](rs);
        cbTiming = rs->cbVecFunc[6] ? rs->cbVecTiming[6] : 0;
        skip = rs->flag & 0x40;
    } else {
        skip = FALSE;
    }
    if (!skip) {
        if (!(rs->flag & 0x100)) {
            rs->funcJntMtx(rs->pJntAnmResult);
        }
    }
    rs->pJntAnmResult = NULL;

    if (cbTiming == 3) {
        rs->flag &= ~0x40;
        rs->cbVecFunc[6](rs);
        skip = rs->flag & 0x40;
    } else {
        skip = FALSE;
    }
    if (opt == 0x20 || opt == 0x60) {
        ++cmdLen;
        if (!skip && !(rs->flag & 0x100)) {
            u32 arg = *(rs->c + 4);
            NNS_G3dGeBufferOP_N(19, &arg, 1);
        }
    }
    rs->c += cmdLen;
}

void NNSi_G3dFuncSbc_NODE(RS *rs, u32 opt) {
    if (!(rs->flag & 0x200)) {
        u32 curNode;
        u32 cbTiming;
        BOOL skip;
        rs->currentNode = *(rs->c + 1);
        curNode = rs->currentNode;
        rs->flag |= 4;
        rs->pVisAnmResult = &rs->tmpVisAnmResult;

        cbTiming = rs->cbVecFunc[2] ? rs->cbVecTiming[2] : 0;
        if (cbTiming == 1) {
            rs->flag &= ~0x40;
            rs->cbVecFunc[2](rs);
            cbTiming = rs->cbVecFunc[2] ? rs->cbVecTiming[2] : 0;
            skip = rs->flag & 0x40;
        } else {
            skip = FALSE;
        }
        if (!skip) {
            if (!(rs->pRenderObj->anmVis && BitVecCheck(rs->pRenderObj->hintVisAnmExist, curNode) &&
                  rs->pRenderObj->funcBlendVis(rs->pVisAnmResult, rs->pRenderObj->anmVis, curNode))) {
                rs->pVisAnmResult->isVisible = *(rs->c + 2) & 1;
            }
        }

        if (cbTiming == 2) {
            rs->flag &= ~0x40;
            rs->cbVecFunc[2](rs);
            cbTiming = rs->cbVecFunc[2] ? rs->cbVecTiming[2] : 0;
            skip = rs->flag & 0x40;
        } else {
            skip = FALSE;
        }
        if (!skip) {
            if (rs->pVisAnmResult->isVisible) {
                rs->flag |= 1;
            } else {
                rs->flag &= ~1;
            }
        }

        if (cbTiming == 3) {
            rs->flag &= ~0x40;
            rs->cbVecFunc[2](rs);
        }
    }
    rs->c += 3;
}

void NNSi_G3dFuncSbc_MTX(RS *rs, u32 opt) {
    if (!(rs->flag & 0x200) && (rs->flag & 1)) {
        u32 cbTiming;
        BOOL skip;
        cbTiming = rs->cbVecFunc[3] ? rs->cbVecTiming[3] : 0;
        if (cbTiming == 1) {
            rs->flag &= ~0x40;
            rs->cbVecFunc[3](rs);
            cbTiming = rs->cbVecFunc[3] ? rs->cbVecTiming[3] : 0;
            skip = rs->flag & 0x40;
        } else {
            skip = FALSE;
        }
        if (!skip) {
            u32 arg = *(rs->c + 1);
            if (!(rs->flag & 0x100)) {
                NNS_G3dGeBufferOP_N(20, &arg, 1);
            }
        }
        if (cbTiming == 3) {
            rs->flag &= ~0x40;
            rs->cbVecFunc[3](rs);
        }
    }
    rs->c += 2;
}

void NNSi_G3dFuncSbc_MAT_InternalDefault(RS *rs, u32 opt, const ResMatData *mat, u32 idxMat) {
    MatAnm *pResult;
    u32 cbTiming;
    BOOL skip;
    rs->currentMat = (u8)idxMat;
    rs->flag |= 8;
    rs->pMatAnmResult = &rs->tmpMatAnmResult;

    cbTiming = rs->cbVecFunc[4] ? rs->cbVecTiming[4] : 0;
    if (cbTiming == 1) {
        rs->flag &= ~0x40;
        rs->cbVecFunc[4](rs);
        cbTiming = rs->cbVecFunc[4] ? rs->cbVecTiming[4] : 0;
        skip = rs->flag & 0x40;
    } else {
        skip = FALSE;
    }
    if (!skip) {
        if (rs->pRenderObj->recMatAnm && !(rs->flag & 0x80)) {
            pResult = &rs->pRenderObj->recMatAnm[idxMat];
        } else if ((opt == 0x20 || opt == 0x40) && BitVecCheck(rs->isMatCached, idxMat)) {
            if (rs->pRenderObj->recMatAnm) {
                pResult = &rs->pRenderObj->recMatAnm[idxMat];
            } else {
                pResult = &data_021f5cc4[idxMat];
            }
        } else {
            if (rs->pRenderObj->recMatAnm) {
                BitVecSet(rs->isMatCached, idxMat);
                pResult = &rs->pRenderObj->recMatAnm[idxMat];
            } else if (opt == 0x40) {
                BitVecSet(rs->isMatCached, idxMat);
                pResult = &data_021f5cc4[idxMat];
            } else {
                pResult = &rs->tmpMatAnmResult;
            }
            pResult->flag = 0;
            if (GetMatDataByIdx(rs->pResMat, idxMat)->flag & 0x20) {
                pResult->flag |= 0x20;
            }
            pResult->prmMatColor0 = (data_027e00c8.prmMatColor0 & ~data_02135d18[(mat->flag >> 6) & 7]) |
                                    (mat->diffAmb & data_02135d18[(mat->flag >> 6) & 7]);
            pResult->prmMatColor1 = (data_027e00c8.prmMatColor1 & ~data_02135d18[(mat->flag >> 9) & 7]) |
                                    (mat->specEmi & data_02135d18[(mat->flag >> 9) & 7]);
            pResult->prmPolygonAttr = (data_027e00c8.prmPolygonAttr & ~mat->polyAttrMask) | (mat->polyAttr & mat->polyAttrMask);
            pResult->prmTexImage = mat->texImageParam;
            pResult->prmTexPltt = mat->texPlttBase;
            if (mat->flag & 1) {
                const fx32 *p = &mat->texMtx[0];
                if (!(mat->flag & 2)) {
                    pResult->scaleS = p[0];
                    pResult->scaleT = p[1];
                    p += 2;
                } else {
                    pResult->flag |= 1;
                }
                if (!(mat->flag & 4)) {
                    pResult->sinR = ((const fx16 *)p)[0];
                    pResult->cosR = ((const fx16 *)p)[1];
                    p += 1;
                } else {
                    pResult->flag |= 2;
                }
                if (!(mat->flag & 8)) {
                    pResult->transS = p[0];
                    pResult->transT = p[1];
                } else {
                    pResult->flag |= 4;
                }
                pResult->flag |= 8;
            }
            if (rs->pRenderObj->anmMat && BitVecCheck(rs->pRenderObj->hintMatAnmExist, idxMat)) {
                rs->pRenderObj->funcBlendMat(pResult, rs->pRenderObj->anmMat, idxMat);
            }
            if (pResult->flag & 0x18) {
                pResult->origW = mat->origWidth;
                pResult->origH = mat->origHeight;
                pResult->magW = mat->magW;
                pResult->magH = mat->magH;
            }
        }
        rs->pMatAnmResult = pResult;
    }

    if (cbTiming == 2) {
        rs->flag &= ~0x40;
        rs->cbVecFunc[4](rs);
        cbTiming = rs->cbVecFunc[4] ? rs->cbVecTiming[4] : 0;
        skip = rs->flag & 0x40;
    } else {
        skip = FALSE;
    }
    if (!skip) {
        pResult = rs->pMatAnmResult;
        if (pResult->prmPolygonAttr & 0x1f0000) {
            if (pResult->flag & 0x20) {
                pResult->prmPolygonAttr &= ~0x1f0000;
            }
            rs->flag &= ~2;
            if (!(rs->flag & 0x100)) {
                u32 cmd[7];
                cmd[0] = 0x00293130;
                cmd[1] = pResult->prmMatColor0;
                cmd[2] = pResult->prmMatColor1;
                cmd[3] = pResult->prmPolygonAttr;
                cmd[4] = 0x00002b2a;
                cmd[5] = pResult->prmTexImage;
                cmd[6] = pResult->prmTexPltt;
                NNS_G3dGeBufferOP_N(cmd[0], &cmd[1], 6);
                if (pResult->flag & 0x18) {
                    rs->funcTexMtx(pResult);
                }
            }
        } else {
            rs->flag |= 2;
        }
    }

    if (cbTiming == 3) {
        rs->flag &= ~0x40;
        rs->cbVecFunc[4](rs);
    }
}

void NNSi_G3dFuncSbc_MAT(RS *rs, u32 opt) {
    u32 flag = rs->flag;
    if (!(flag & 0x200)) {
        u32 idxMat = rs->c[1];
        if ((flag & 1) || !(flag & 8) || idxMat != rs->currentMat) {
            const ResMatData *mat = GetMatDataByIdx(rs->pResMat, idxMat);
            data_0213bd60[mat->itemTag](rs, opt, mat, idxMat);
        }
    }
    rs->c += 2;
}

void NNS_G3dGeWaitSendDL(void) {
    while (data_021f89c8) {
    }
}

void NNS_G3dGeSendDL(const void *src, u32 szByte) {
    if (szByte < 256 || data_0213bfec == (u32)-1) {
        NNS_G3dGeBufferOP_N(*(const u32 *)src, (const u32 *)src + 1, (szByte >> 2) - 1);
        return;
    }
    NNS_G3dGeFlushBuffer();
    data_021f89c8 = 1;
    if (data_021f89cc) {
        MI_SendGXCommandAsyncFast(data_0213bfec, src, szByte, simpleUnlock_, (void *)&data_021f89c8);
    } else {
        MI_SendGXCommandAsync(data_0213bfec, src, szByte, simpleUnlock_, (void *)&data_021f89c8);
    }
}

void NNS_G3dGeFlushBuffer(void) {
    if (data_021f89c8) {
        NNS_G3dGeWaitSendDL();
    }
    if (data_021f89c4 && data_021f89c4->idx) {
        MIi_CpuSend32(&data_021f89c4->data[0], &reg_G3X_GXFIFO, data_021f89c4->idx << 2);
        data_021f89c4->idx = 0;
    }
}

void NNS_G3dGeBufferOP_N(u32 op, const u32 *args, u32 num) {
    if (data_021f89c4) {
        if (data_021f89c8 && data_021f89c4->idx + 1 + num <= 192) {
            u32 idx = data_021f89c4->idx;
            data_021f89c4->idx = idx + 1;
            data_021f89c4->data[idx] = op;
            if (num) {
                MIi_CpuCopyFast(args, &data_021f89c4->data[data_021f89c4->idx], num << 2);
                data_021f89c4->idx += num;
            }
            return;
        }
        if (data_021f89c4->idx) {
            NNS_G3dGeFlushBuffer();
        } else if (data_021f89c8) {
            NNS_G3dGeWaitSendDL();
        }
    } else {
        if (data_021f89c8) {
            NNS_G3dGeWaitSendDL();
        }
    }
    IO_W(&reg_G3X_GXFIFO, op);
    MIi_CpuSend32(args, &reg_G3X_GXFIFO, num << 2);
}

void NNS_G3dDraw(RenderObj *obj) {
    RS rs;
    if ((obj->flag & 0x10) == 0x10) {
        {
            volatile u32 zero = 0;
            MIi_CpuClear32(zero, obj->hintMatAnmExist, 8);
        }
        {
            volatile u32 zero = 0;
            MIi_CpuClear32(zero, obj->hintJntAnmExist, 8);
        }
        {
            volatile u32 zero = 0;
            MIi_CpuClear32(zero, obj->hintVisAnmExist, 8);
        }
        if (obj->anmMat) updateHintVec_(obj->hintMatAnmExist, obj->anmMat);
        if (obj->anmJnt) updateHintVec_(obj->hintJntAnmExist, obj->anmJnt);
        if (obj->anmVis) updateHintVec_(obj->hintVisAnmExist, obj->anmVis);
        obj->flag &= ~0x10;
    }
    if (data_021f5cc0) {
        G3dDrawInternal_(data_021f5cc0, obj);
    } else {
        data_021f5cc0 = &rs;
        G3dDrawInternal_(&rs, obj);
        data_021f5cc0 = NULL;
    }
}

int data_021f89cc;
GeBuffer *data_021f89c4;
volatile int data_021f89c8;
