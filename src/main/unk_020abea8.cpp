#include "types.h"
#include "ds_shift.h"
#include "sys/new.h"
#include "gfx/VecFx32.h"
#include "game/GroundInfoBase.h"
#include "gfx/ObjShadowTexture.h"
#include "gfx/NNSG3dResTex.h"
#include "gfx/ObjShadowTexDef.h"
#include "gfx/NNSG3dResMatData.h"
#include "gfx/ObjShadowBits.h"
#include "item/ShopPurchaseBits.h"
#include "gfx/Vec3Z.h"
#include "gfx/Mtx43.h"
#include "gfx/ObjShadowStrip.h"
#include "nitro/io_access.h"
#include "gfx/G3dResAccess.h"
#include "gfx/TexVramSlot.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_021104ac.h"
#include "proto/itcm/unk_01ff8ad4.h"
#include "proto/itcm/unk_01ffcfc0.h"
#include "proto/main/unk_020027b4.h"
#include "proto/main/unk_0203ecec.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_020643dc.h"
#include "proto/main/unk_020abea8.h"


extern "C" {
s32 FX_Div(s32 a, s32 b);
s32 func_01ffcb0c(s32 a, s32 b);
u32 _s32_div_f(u32 a, u32 b);
void Mtx43_SetTranslate(Mtx43 *m, s32 x, s32 y, s32 z);
void Mtx43_Scale(Mtx43 *m, s32 x, s32 y, s32 z);
void MTX_Concat43(const Mtx43 *a, const Mtx43 *b, Mtx43 *ab);
void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
s32 Ground_GetDefaultY(void);
u8 SceneLights_GetLightParam(u32 x);
void Clock_GetMinuteHour(u8 *out);
NNSG3dResTex *NNS_G3dGetTex(void *file);
BOOL Gfx3d_LoadTexAndPltt(NNSG3dResTex *tex, TexVramSlot *slot);
void *Gfx3d_CopyTex(void *tex, void *heap);
extern void *gCamera;
extern VecFx32 gCameraLookAt;
}
extern Mtx43 data_021f47e0;

#define REG(a) (*(volatile u32 *)(a))

extern const s32 sObjShadowCoordShift;
extern const ObjShadowTexDef sObjShadowTexDefs[];


static inline void *Unk_020ac500_Data(const NNSG3dResDict *dict, u32 idx) {
    NNSG3dResDictEntryHeader *hdr = (NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
    return &hdr->data[hdr->sizeUnit * idx];
}
static inline u32 *Unk_020ac500_TexData(const NNSG3dResTex *tex, u32 idx) {
    return (u32 *)Unk_020ac500_Data(&tex->dict, idx);
}
static inline NNSG3dResDictPlttData *Unk_020ac500_PlttData(const NNSG3dResTex *tex, u32 idx) {
    return (NNSG3dResDictPlttData *)Unk_020ac500_Data((const NNSG3dResDict *)((u8 *)tex + tex->ofsPlttDict), idx);
}


extern "C" void ObjShadow_NormalizeAxes(Mtx43 *m, VecFx32 *axes) {
    VEC_Normalize((VecFx32 *)&m->m[0], &axes[0]);
    VEC_Normalize((VecFx32 *)&m->m[3], &axes[1]);
    VEC_Normalize((VecFx32 *)&m->m[6], &axes[2]);
}

extern "C" void ObjShadow_Init(BOOL outdoor) {
    u32 *texData;
    Heap *heap = (Heap *)gBgHeap;
    if (outdoor) {
        sObjShadowSkew = 0;
        ObjShadowTexture *e = sObjShadowTextures;
        void *file = File_Load("/shadow/tex_shadow.nsbtx");
        NNSG3dResTex *tex0 = NNS_G3dGetTex(file);
        Gfx3d_LoadTexAndPltt(tex0, NULL);
        u8 *res = (u8 *)Gfx3d_CopyTex(tex0, heap);
        Mem_Free(file);
        u32 i;
        for (i = 0; i < 3; i++) {
            char *name = sObjShadowTexDefs[i].texName;
            char buf[36];
            Str_SPrintf(buf, "%s_pl", name);
            e->texRes = 0;
            e->texImageParam = 0;
            e->plttBase = 0;
            e->texRes = res;
            e->polygonId = sObjShadowTexDefs[i].polygonId;
            u32 idx1 = ((G3dResAccess *)(e->texRes))->findTexIdx(name);
            u32 idx2 = ((G3dResAccess *)(e->texRes))->findPlttIdx(buf);
            NNSG3dResTex *tex = (NNSG3dResTex *)e->texRes;
            texData = Unk_020ac500_TexData(tex, idx1);
            u32 plttOfs = Unk_020ac500_PlttData(tex, idx2)->offset;
            u32 plttKey = (u16)tex->plttKey;
            u32 texParam = *texData;
            u32 texKey = (u16)tex->texKey;
            e->texImageParam = texParam + texKey;
            e->plttBase = plttOfs + plttKey;
            e->texImageParam |= sObjShadowTexDefs[i].texFlip << 18;
            e->texImageParam |= sObjShadowTexDefs[i].texRepeat << 16;
            e->texFormat = (*texData >> 26) & 7;
            if (e->texFormat != 2) {
                e->plttBase >>= 1;
            }
            e->width = 1 << (((*texData >> 20) & 7) + 3);
            e->height = 1 << (((*texData >> 23) & 7) + 3);
            e++;
        }
        static Vec3Z2 v;
        sTreeShadowStage2.build((VecFx32 *)&v, 0x119a, 0x119a, 2, 0x2000, 0, heap);
        sTreeShadowStage3.build((VecFx32 *)&v, 0x1666, 0x1666, 2, 0x2000, 0, heap);
        sTreeShadowStage4.build((VecFx32 *)&v, 0x2000, 0x2000, 2, 0x2000, 0, heap);
        sRockShadow.build((VecFx32 *)&v, 0x1ccc, 0x1ccc, 0, 0, 0, heap);
        sSignShadow.build((VecFx32 *)&v, 0x555, 0x1000, 0, 0, 0, heap);
    }
}

char sObjShadowTexNameFc[] = "obj_sdw_fc";
ObjShadowStrip sTreeShadowStage2;
ObjShadowTexture sObjShadowTextures[3];
u8 sObjShadowAlpha = 0xe;
ObjShadowStrip sTreeShadowStage3;
ObjShadowStrip sTreeShadowStage4;
ObjShadowStrip sRockShadow;
ObjShadowStrip sSignShadow;

extern "C" void ObjShadow_Update() {
    u8 t[2];
    Clock_GetMinuteHour(t);
    s32 x = (t[0] + ((t[1] + 6) % 12) * 60) << 12;
    x = FX_Div(x, 0x2d0000);
    sObjShadowSkew = func_01ffcb0c((x - 0x800) << 1, 0x1000);
    Mtx43_SetTranslate(&data_021f47e0, 0, 0, 0);
    Mtx43_Scale(&data_021f47e0, 0x20000, 0x20000, 0x20000);
    MTX_Concat43(&data_021f47e0, &gViewMtx, &sObjShadowViewMtx);
    ObjShadow_NormalizeAxes(&sObjShadowViewMtx, sObjShadowNormMtx);
    u16 c = SceneLights_GetFlashColor();
    u8 s = ((c >> 10) & 0x1f) + ((c & 0x1f) + ((c >> 5) & 0x1f));
    u8 r4 = func_01ffcb0c(0x10000, FX_Div(s << 12, 0x5d000)) >> 12;
    s32 base = SceneLights_GetLightParam(0);
    u8 v = base + r4;
    if (v > 0x1f) {
        v = 0x1f;
    }
    sObjShadowAlpha = v;
    sCharaShadowAlpha = v;
}

extern "C" void ObjShadow_Exit() {
    sObjShadowSkew = 0;
    ObjShadowTexture *e = sObjShadowTextures;
    u32 i;
    for (i = 0; i < 3; i++) {
        e->texRes = 0;
        e++;
    }
    Heap *heap = (Heap *)gBgHeap;
    sTreeShadowStage2.release(heap);
    sTreeShadowStage3.release(heap);
    sTreeShadowStage4.release(heap);
    sRockShadow.release(heap);
    sSignShadow.release(heap);
}

extern "C" u8 ObjShadow_CalcAlpha(VecFx32 *p, s32 q, u8 r4) {
    if (gCamera != NULL) {
        VecFx32CtorDtor v;
        v.x = gCameraLookAt.x;
        v.y = gCameraLookAt.y;
        v.z = gCameraLookAt.z;
        s32 d, e;
        s32 pz = p->z;
        if (v.z > pz) {
            d = v.z - pz;
            if (0xb000 < d) {
                r4 = r4 >> 5;
            } else {
                static s32 inv = FX_Div(0xf80, 0xb000);
                r4 = r4 - (u8)(func_01ffcb0c(func_01ffcb0c(r4 << 12, inv), d) >> 12);
            }
        } else {
            d = pz - v.z;
            if (d > q + 0xc000) {
                return 0;
            }
            e = p->x - v.x;
            if (e < 0) {
                e = -e;
            }
            if (e > q + 0xf000) {
                return 0;
            }
        }
    }
    return r4;
}

char sObjShadowTexNameTr[] = "obj_sdw_tr";
const ObjShadowTexDef sObjShadowTexDefs[3] = {
    {sObjShadowTexNameGr, 0, 1, 0x3d, 0},
    {sObjShadowTexNameFc, 0, 1, 0x3a, 0},
    {sObjShadowTexNameTr, 1, 1, 0x3a, 0},
};
char sObjShadowTexNameGr[] = "obj_sdw_gr";
s32 sObjShadowSkew;
u8 sCharaShadowAlpha = 0x12;
VecFx32 sObjShadowNormMtx[3];
Mtx43 sObjShadowViewMtx;

extern "C" u8 ObjShadow_GetObjAlpha(VecFx32 *p, s32 q) {
    return ObjShadow_CalcAlpha(p, q, sObjShadowAlpha);
}

extern "C" u8 ObjShadow_GetCharaAlpha(VecFx32 *p, s32 q) {
    return ObjShadow_CalcAlpha(p, q, sCharaShadowAlpha);
}

extern "C" void ObjShadow_DrawTree(VecFx32 *p, u32 n) {
    if (n >= 2) {
        static Vec3Z v;
        VecFx32 out;
        Vec_Add(&out, p, (VecFx32 *)&v);
        if (n == 2) {
            sTreeShadowStage2.draw(&out);
        } else if (n == 3) {
            sTreeShadowStage3.draw(&out);
        } else if (n == 4) {
            sTreeShadowStage4.draw(&out);
        }
    }
}

extern "C" void ObjShadow_DrawRock(VecFx32 *p) {
    sRockShadow.draw(p);
}

extern "C" void ObjShadow_DrawSign(VecFx32 *p) {
    VecFx32 local;
    VecFx32 out;
    local.x = 0x166;
    local.y = 0;
    local.z = 0xc80;
    Vec_Add(&out, p, &local);
    sSignShadow.draw(&out);
}

ObjShadowStrip::ObjShadowStrip() {
    basePos.x = 0;
    basePos.y = 0;
    basePos.z = 0;
    halfWidth = 0;
    cullExtent = 0;
    numRows = 0;
    rowDepths = 0;
    rowTexT = 0;
    rowVertices = 0;
    texture = 0;
}

ObjShadowStrip *ObjShadowStrip::func_020ac1e0() {
    new (this) ObjShadowStrip();
    return this;
}

ObjShadowStrip::~ObjShadowStrip() {}

BOOL ObjShadowStrip::build(VecFx32 *pos, s32 size, s32 shift, s32 idx, s32 a, s32 b, Heap *heap) {
    u32 i;
    if (heap == NULL) {
        heap = gCurrentHeap;
    }
    texture = &sObjShadowTextures[idx];
    basePos = *pos;
    halfWidth = size >> 1;
    s32 v = halfWidth;
    if (DS_ASR(v, shift) == 0) {
        v = shift;
    }
    cullExtent = v;
    cachedZ = 0;
    numRows = _s32_div_f(shift - 0x200, 0x2000) + 2;
    u32 n4 = numRows << 2;
    rowDepths = (s32 *)Heap_Alloc(heap, (n4 << 1) + numRows * sizeof(VecFx32));
    rowTexT = rowDepths + numRows;
    rowVertices = (VecFx32 *)(rowTexT + numRows);
    for (i = 0; i < numRows; i++) {
        if (i == numRows - 1) {
            rowDepths[i] = shift;
        } else {
            rowDepths[i] = i << 13;
        }
    }
    if (a == 0 && b == 0) {
        texLeftS = 0;
        texRightS = texture->width << 12;
    } else {
        texLeftS = func_01ffcb0c(texture->width << 12, a);
        texRightS = func_01ffcb0c(texture->width << 12, b);
    }
    s32 *p6 = rowDepths;
    s32 *p7 = rowTexT;
    for (i = 0; i < numRows; i++) {
        *p7++ = func_01ffcb0c(0x1000 - FX_Div(*p6, shift), texture->height << 12);
        p6++;
    }
    return TRUE;
}

void ObjShadowStrip::draw(VecFx32 *pos) {
    VecFx32 tmp;
    if (texture != 0 && texture->texRes != 0) {
        u8 lvl = ObjShadow_GetObjAlpha(pos, cullExtent);
        if (lvl > 1) {
            NNS_G3dGeFlushBuffer();
            IO_W(&REG(0x40004a8), texture->texImageParam);
            IO_W(&REG(0x40004ac), texture->plttBase);
            IO_W(&REG(0x4000440), 1);
            G3_LoadMtx43(&sObjShadowViewMtx);
            IO_W(&REG(0x40004a4), (lvl << 16) | ((texture->polygonId << 24) | 0x8080));
            s32 *p7 = rowDepths;
            s32 *p28 = rowTexT;
            VecFx32 *vp = rowVertices;
            IO_W(&REG(0x4000500), 3);
            s32 e1 = rowDepths[1];
            u32 i = 0;
            s32 lo, hi, neg;
            s32 shift = sObjShadowCoordShift;
            s32 z1 = i;
            s32 z2 = i;
            for (; i < numRows; i++) {
                s32 v;
                if (i != 0) {
                    v = e1;
                } else {
                    v = *p7;
                }
                s32 t = func_01ffcb0c(sObjShadowSkew, v);
                lo = t + (pos->x - halfWidth);
                hi = t + (pos->x + halfWidth);
                if (pos->z != cachedZ) {
                    neg = -*p7;
                    s32 y = Ground_GetDefaultY();
                    tmp.x = z2;
                    tmp.y = y;
                    tmp.z = neg;
                    tmp.z = neg + pos->z;
                    WorldCurve_Apply(vp, &tmp);
                    vp->y >>= shift;
                    vp->z >>= shift;
                }
                IO_W(&REG(0x4000480), (u16)SceneLights_GetRoomColor());
                IO_W(&REG(0x4000488), (u16)((texLeftS << 8) >> 16) | ((u16)((*p28 << 8) >> 16) << 16));
                s16 zz = vp->z;
                IO_W(&REG(0x400048c), (u16)((lo << 11) >> 16) | ((u16)(s16)vp->y << 16));
                IO_W(&REG(0x400048c), (u16)zz);
                IO_W(&REG(0x4000488), (u16)((texRightS << 8) >> 16) | ((u16)((*p28 << 8) >> 16) << 16));
                zz = vp->z;
                IO_W(&REG(0x400048c), (u16)((hi << 11) >> 16) | ((u16)(s16)vp->y << 16));
                IO_W(&REG(0x400048c), (u16)zz);
                p7++;
                p28++;
                vp++;
            }
            IO_W(&REG(0x4000504), 0);
            IO_W(&REG(0x4000448), 1);
            cachedZ = pos->z;
        }
    }
}

void ObjShadowStrip::release(Heap *heap) {
    if (heap == NULL) {
        heap = gCurrentHeap;
    }
    if (rowDepths != 0) {
        Heap_Free(heap, rowDepths);
        rowDepths = 0;
    }
    texture = 0;
}


