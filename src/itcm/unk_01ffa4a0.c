#include "nitro/mtx.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "types64.h"
#include "nitro/io_access.h"
#include "proto/autoload_2/unk_02106f90.h"
#include "proto/itcm/unk_01ffa4a0.h"
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

#define reg_OS_IF  (*(vu32 *)0x04000214)

typedef struct OSIrqCallbackInfo {
    void (*func)(void *);
    u32 enable;
    void *arg;
} OSIrqCallbackInfo;

extern OSIrqCallbackInfo data_027e0058[];
extern u8 data_027e0000[];

extern u32 OS_DisableInterrupts(void);
extern u32 OS_RestoreInterrupts(u32 enabled);
extern u32 OS_EnableInterrupts(void);
extern void OS_Halt(void);
extern u32 OS_EnableIrqMask(u32 intr);

extern volatile u64 data_021fcf24;

typedef struct ResJntAnm {
    u32 anmHeader;
    u16 numFrame;
    u16 numNode;
    u32 flag;
    u32 ofsRot3;
    u32 ofsRot5;
    u16 ofsAnm[1];
} ResJntAnm;

typedef struct ScaleTmp { fx32 s; fx32 inv; } ScaleTmp;

extern RS *data_021f5cc0;
extern const u8 data_02135e5c[][4];

extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern fx32 FX_Div(fx32 a, fx32 b);
extern void VEC_Normalize(VecFx32 *src, VecFx32 *dst);
extern void VEC_CrossProduct(VecFx32 *a, VecFx32 *b, VecFx32 *dst);
extern void blendScaleVec_(VecFx32 *dst, const VecFx32 *src, fx32 ratio, u32 isOne);
extern void getRotDataEx_(MtxFx33 *dst, fx32 frame, const u32 *pData, const ResJntAnm *pJntAnm);
extern void getScaleDataEx_(ScaleTmp *dst, fx32 frame, const u32 *pData, const ResJntAnm *pJntAnm);
extern void getScaleData_(ScaleTmp *dst, fx32 frame, const u32 *pData, const ResJntAnm *pJntAnm);
extern void getRotData_(MtxFx33 *dst, fx32 frame, const u32 *pData, const ResJntAnm *pJntAnm);
extern void getJntSRTAnmResult_(const ResJntAnm *pJntAnm, u32 dataIdx, fx32 frame, JntAnm *pResult);

/* PROTOS */
/* END PROTOS */

#define reg_PXI_FIFO_CNT (*(vu16 *)0x04000184)
#define reg_PXI_SEND_FIFO (*(vu32 *)0x04000188)
#define reg_PXI_RECV_FIFO (*(vu32 *)0x04100000)

extern void (*data_027e0394[32])(u32 tag, u32 data, u32 err);

typedef union PXIFifoMessage {
    u32 raw;
    struct {
        u32 tag : 5;
        u32 err : 1;
        u32 data : 26;
    } e;
} PXIFifoMessage;

static inline int PXIi_RecvWordByFifo(PXIFifoMessage *data) {
    u32 enabled;
    if (IO_R(&reg_PXI_FIFO_CNT) & 0x4000) {
        IO_OR(&reg_PXI_FIFO_CNT, 0xc000);
        return -3;
    }
    enabled = OS_DisableInterrupts();
    if (IO_R(&reg_PXI_FIFO_CNT) & 0x100) {
        OS_RestoreInterrupts(enabled);
        return -4;
    }
    data->raw = IO_R(&reg_PXI_RECV_FIFO);
    OS_RestoreInterrupts(enabled);
    return 0;
}

static inline int PXIi_SendWordByFifo(u32 data) {
    u32 enabled;
    if (IO_R(&reg_PXI_FIFO_CNT) & 0x4000) {
        IO_OR(&reg_PXI_FIFO_CNT, 0xc000);
        return -3;
    }
    enabled = OS_DisableInterrupts();
    if (IO_R(&reg_PXI_FIFO_CNT) & 2) {
        OS_RestoreInterrupts(enabled);
        return -1;
    }
    IO_W(&reg_PXI_SEND_FIFO, data);
    OS_RestoreInterrupts(enabled);
    return 0;
}

typedef struct CbEntry {
    void (*func)(void *);
    void *arg;
    u8 tag;
} CbEntry;
extern CbEntry data_027e032c[];

BOOL getRotDataByIdx_(MtxFx33 *pMtx, const fx16 *pArray3, const fx16 *pArray5, u32 idx) {
    if (idx & 0x8000) {
        u32 n;
        fx32 A;
        fx32 B;
        const fx16 *p;
        u32 pivot;
        pMtx->a[0] = pMtx->a[1] = pMtx->a[2] = pMtx->a[3] = pMtx->a[4] = pMtx->a[5] = pMtx->a[6] = pMtx->a[7] = pMtx->a[8] = 0;
        n = (idx & 0x7fff) * 3;
        p = pArray3 + n;
        A = p[1];
        B = p[2];
        pivot = pArray3[n] & 0xf;
        pMtx->a[pivot] = (pArray3[n] & 0x10) ? -FX32_ONE : FX32_ONE;
        pMtx->a[data_02135e5c[pivot][0]] = A;
        pMtx->a[data_02135e5c[pivot][1]] = B;
        if (p[0] & 0x20) {
            B = -B;
        }
        pMtx->a[data_02135e5c[pivot][2]] = B;
        if (p[0] & 0x40) {
            A = -A;
        }
        pMtx->a[data_02135e5c[pivot][3]] = A;
        return FALSE;
    } else {
        u32 n = (idx & 0x7fff) * 5;
        const fx16 *p = pArray5 + n;
        fx32 v0, v1, v2, v3, v4;
        s16 tmp;
        v4 = p[4];
        pMtx->a[4] = v4 >> 3;
        v0 = pArray5[n];
        pMtx->a[0] = v0 >> 3;
        tmp = v4 & 7;
        tmp = (v0 & 7) | (tmp << 3);
        v1 = p[1];
        pMtx->a[1] = v1 >> 3;
        tmp = (v1 & 7) | (tmp << 3);
        v2 = p[2];
        pMtx->a[2] = v2 >> 3;
        tmp = (v2 & 7) | (tmp << 3);
        v3 = p[3];
        tmp = (v3 & 7) | (tmp << 3);
        pMtx->a[3] = v3 >> 3;
        pMtx->a[5] = (tmp << 19) >> 19;
        return TRUE;
    }
}

void getJntSRTAnmResult_(const ResJntAnm *pJntAnm, u32 dataIdx, fx32 frame, JntAnm *pResult) {
    u32 ofs = pJntAnm->ofsAnm[dataIdx];
    BOOL interpolate;
    u32 info = *(const u32 *)((const u8 *)pJntAnm + ofs);
    const u32 *pData;
    ScaleTmp tx, ty, tz;
    fx32 scale[6];
    if (info & 1) {
        pResult->flag = 7;
        return;
    }
    pData = (const u32 *)((const u8 *)pJntAnm + ofs) + 1;
    if ((frame & 0xfff) && (pJntAnm->flag & 1)) {
        interpolate = TRUE;
    } else {
        interpolate = FALSE;
    }
    pResult->flag = 0;
    if (!(info & 6)) {
        if (!(info & 8)) {
            if (interpolate) {
                getTransDataEx_(&pResult->trans.x, frame, pData, pJntAnm);
            } else {
                getTransData_(&pResult->trans.x, frame, pData, pJntAnm);
            }
            pData += 2;
        } else {
            pResult->trans.x = *pData++;
        }
        if (!(info & 16)) {
            if (interpolate) {
                getTransDataEx_(&pResult->trans.y, frame, pData, pJntAnm);
            } else {
                getTransData_(&pResult->trans.y, frame, pData, pJntAnm);
            }
            pData += 2;
        } else {
            pResult->trans.y = *pData++;
        }
        if (!(info & 32)) {
            if (interpolate) {
                getTransDataEx_(&pResult->trans.z, frame, pData, pJntAnm);
            } else {
                getTransData_(&pResult->trans.z, frame, pData, pJntAnm);
            }
            pData += 2;
        } else {
            pResult->trans.z = *pData++;
        }
    } else {
        if (info & 2) {
            pResult->flag |= 4;
        } else {
            getMdlTrans_((G3dJntAnmResult *)pResult);
        }
    }
    if (!(info & 0xc0)) {
        if (!(info & 0x100)) {
            if (interpolate) {
                getRotDataEx_(&pResult->rot, frame, pData, pJntAnm);
            } else {
                getRotData_(&pResult->rot, frame, pData, pJntAnm);
            }
            pData += 2;
        } else {
            if (getRotDataByIdx_(&pResult->rot, (const fx16 *)((const u8 *)pJntAnm + pJntAnm->ofsRot3),
                              (const fx16 *)((const u8 *)pJntAnm + pJntAnm->ofsRot5), *pData)) {
                fx32 c0, c1, c2;
                c0 = (pResult->rot.a[1] * pResult->rot.a[5] - pResult->rot.a[2] * pResult->rot.a[4]) >> 12;
                c1 = (pResult->rot.a[2] * pResult->rot.a[3] - pResult->rot.a[0] * pResult->rot.a[5]) >> 12;
                c2 = (pResult->rot.a[0] * pResult->rot.a[4] - pResult->rot.a[1] * pResult->rot.a[3]) >> 12;
                pResult->rot.a[6] = c0;
                pResult->rot.a[7] = c1;
                pResult->rot.a[8] = c2;
            }
            pData++;
        }
    } else {
        if (info & 0x40) {
            pResult->flag |= 2;
        } else {
            getMdlRot_((G3dJntAnmResult *)pResult);
        }
    }
    if (!(info & 0x600)) {
        if (!(info & 0x800)) {
            if (interpolate) {
                getScaleDataEx_(&tx, frame, pData, pJntAnm);
            } else {
                getScaleData_(&tx, frame, pData, pJntAnm);
            }
            scale[0] = tx.s;
            scale[3] = tx.inv;
        } else {
            scale[0] = pData[0];
            scale[3] = pData[1];
        }
        if (!(info & 0x1000)) {
            if (interpolate) {
                getScaleDataEx_(&ty, frame, pData + 2, pJntAnm);
            } else {
                getScaleData_(&ty, frame, pData + 2, pJntAnm);
            }
            scale[1] = ty.s;
            scale[4] = ty.inv;
        } else {
            scale[1] = pData[2];
            scale[4] = pData[3];
        }
        if (!(info & 0x2000)) {
            if (interpolate) {
                getScaleDataEx_(&tz, frame, pData + 4, pJntAnm);
            } else {
                getScaleData_(&tz, frame, pData + 4, pJntAnm);
            }
            scale[2] = tz.s;
            scale[5] = tz.inv;
        } else {
            scale[2] = pData[4];
            scale[5] = pData[5];
        }
    } else {
        if (info & 0x200) {
            pResult->flag |= 1;
        } else {
            getMdlScale_((G3dJntAnmResult *)pResult);
            return;
        }
    }
    data_021f5cc0->funcJntScale(pResult, scale, data_021f5cc0->c, (pResult->flag & 1) ? 4 : 0);
}

void NNSi_G3dAnmCalcNsBca(JntAnm *pResult, const AnmObj *pAnmObj, u32 dataIdx) {
    const ResJntAnm *pJntAnm = (const ResJntAnm *)pAnmObj->resAnm;
    fx32 frame = pAnmObj->frame;
    if (frame >= (fx32)(pJntAnm->numFrame << 12)) {
        frame = (pJntAnm->numFrame << 12) - 1;
    } else if (frame < 0) {
        frame = 0;
    }
    getJntSRTAnmResult_(pJntAnm, dataIdx, frame, pResult);
}

BOOL NNSi_G3dAnmBlendJnt(JntAnm *pResult, const AnmObj *pAnmObj, u32 dataIdx) {
    if (!pAnmObj->next) {
        u16 mapData = pAnmObj->mapData[dataIdx];
        if ((mapData & 0x300) != 0x100) {
            return FALSE;
        }
        ((void (*)(JntAnm *, const AnmObj *, u32))pAnmObj->funcAnm)(pResult, pAnmObj, mapData & 0xff);
        return TRUE;
    } else {
        fx32 sumOfRatio = 0;
        const AnmObj *p;
        int cnt = 0;
        const AnmObj *pLast;
        p = pAnmObj;
        do {
            if ((p->mapData[dataIdx] & 0x300) == 0x100) {
                sumOfRatio += p->ratio;
                cnt++;
                pLast = p;
            }
            p = p->next;
        } while (p);
        if (sumOfRatio == 0) {
            return FALSE;
        }
        if (cnt == 1) {
            ((void (*)(JntAnm *, const AnmObj *, u32))pLast->funcAnm)(pResult, pLast, pLast->mapData[dataIdx] & 0xff);
            return TRUE;
        } else {
            JntAnm tmp;
            fx32 ratio;
            {
                volatile u32 zero = 0;
                MIi_CpuClearFast(zero, pResult, sizeof(JntAnm));
            }
            pResult->flag = 0xffffffff;
            do {
                u16 mapData = pAnmObj->mapData[dataIdx];
                if ((mapData & 0x300) != 0x100 || pAnmObj->ratio <= 0) {
                    continue;
                }
                ((void (*)(JntAnm *, const AnmObj *, u32))pAnmObj->funcAnm)(&tmp, pAnmObj, mapData & 0xff);
                if (sumOfRatio == 0x1000) {
                    ratio = pAnmObj->ratio;
                } else {
                    ratio = FX_Div(pAnmObj->ratio, sumOfRatio);
                }
                blendScaleVec_(&pResult->scale, &tmp.scale, ratio, tmp.flag & 1);
                blendScaleVec_(&pResult->scaleEx0, &tmp.scaleEx0, ratio, tmp.flag & 8);
                blendScaleVec_(&pResult->scaleEx1, &tmp.scaleEx1, ratio, tmp.flag & 16);
                if (!(tmp.flag & 4)) {
                    pResult->trans.x += (fx32)(((s64)ratio * tmp.trans.x) >> 12);
                    pResult->trans.y += (fx32)(((s64)ratio * tmp.trans.y) >> 12);
                    pResult->trans.z += (fx32)(((s64)ratio * tmp.trans.z) >> 12);
                }
                if (!(tmp.flag & 2)) {
                    pResult->rot.a[0] += (ratio * tmp.rot.a[0]) >> 12;
                    pResult->rot.a[1] += (ratio * tmp.rot.a[1]) >> 12;
                    pResult->rot.a[2] += (ratio * tmp.rot.a[2]) >> 12;
                    pResult->rot.a[3] += (ratio * tmp.rot.a[3]) >> 12;
                    pResult->rot.a[4] += (ratio * tmp.rot.a[4]) >> 12;
                    pResult->rot.a[5] += (ratio * tmp.rot.a[5]) >> 12;
                } else {
                    pResult->rot.a[0] += ratio;
                    pResult->rot.a[4] += ratio;
                }
                pResult->flag &= tmp.flag;
            } while ((pAnmObj = pAnmObj->next));
            VEC_CrossProduct((VecFx32 *)&pResult->rot.a[0], (VecFx32 *)&pResult->rot.a[3], (VecFx32 *)&pResult->rot.a[6]);
            VEC_Normalize((VecFx32 *)&pResult->rot.a[0], (VecFx32 *)&pResult->rot.a[0]);
            VEC_Normalize((VecFx32 *)&pResult->rot.a[6], (VecFx32 *)&pResult->rot.a[6]);
            VEC_CrossProduct((VecFx32 *)&pResult->rot.a[6], (VecFx32 *)&pResult->rot.a[0], (VecFx32 *)&pResult->rot.a[3]);
            return TRUE;
        }
    }
}

u64 OS_GetTick(void) {
    u32 enabled = OS_DisableInterrupts();
    vu16 countL = IO_R((vu16 *)0x04000100);
    vu64 countH = data_021fcf24 & 0x0000ffffffffffffULL;
    if ((IO_R(&reg_OS_IF) & 8) && !(countL & 0x8000)) {
        countH++;
    }
    OS_RestoreInterrupts(enabled);
    return (countH << 16) | countL;
}

void SNDi_CallAlarmHandler(s32 msg) {
    CbEntry *e = &data_027e032c[msg & 0xff];
    if (((msg >> 8) & 0xff) != e->tag) {
        return;
    }
    if (e->func == 0) {
        return;
    }
    e->func(e->arg);
}

void PxiFifoCallback(u32 a, s32 msg) {
    u32 enabled = OS_DisableInterrupts();
    SNDi_CallAlarmHandler(msg);
    OS_RestoreInterrupts(enabled);
}

void PXIi_HandlerRecvFifoNotEmpty(void) {
    PXIFifoMessage data;
    int error;
    u32 tag;
    for (;;) {
        error = PXIi_RecvWordByFifo(&data);
        if (error == -4) {
            return;
        }
        if (error == -3) {
            continue;
        }
        tag = data.e.tag;
        if (tag == 0) {
            continue;
        }
        if (data_027e0394[tag]) {
            data_027e0394[tag](tag, data.e.data, data.e.err);
        } else if (!data.e.err) {
            data.e.err = 1;
            PXIi_SendWordByFifo(data.raw);
        }
    }
}

void OSi_IdleThreadProc(void) {
    OS_EnableInterrupts();
    while (1) {
        OS_Halt();
    }
}

void OSi_EnterDmaCallback(u32 dmaNo, void (*callback)(void *), void *arg) {
    u32 mask;
    data_027e0058[dmaNo].func = callback;
    data_027e0058[dmaNo].arg = arg;
    data_027e0058[dmaNo].enable = OS_EnableIrqMask(1 << (dmaNo + 8)) & (1 << (dmaNo + 8));
}

