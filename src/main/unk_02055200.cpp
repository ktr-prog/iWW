#include "uptr.h"
#include "host_labels.h"
#include "types.h"
#include "gfx/AnimFrameCtrl.h"
#include "gfx/TexVramSlot.h"
#include "gfx/ModelAnim.h"
#include "gfx/Model.h"
#include "gfx/Mtx43.h"
#include "gfx/NNSG3dResTex.h"
#include "gfx/NNSG3dResMdl.h"
#include "gfx/G3dResAccess.h"
#include "gfx/NNSG3dResAnmCommon.h"
#include "gfx/NNSG3dRS.h"
#include "proto/autoload_2/unk_02101048.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_021040ac.h"
#include "proto/main/unk_02055200.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_0206d49c.h"

struct ResCacheEntry {
    void *data;
    u32 key;
};


class ModelBase {
public:
    ModelBase();
    virtual ~ModelBase();
};


s32 sResCacheModelCount;
s32 sResCacheTexCount;
ResCacheEntry sResCacheTexs[0x3c];
ResCacheEntry sResCacheModels[0x96];

extern "C" {
void NNS_G3dRenderObjSetInitFunc(void *p, void (*fn)(NNSG3dRS *));
void NNS_G3dRenderObjSetCallBack(void *p, void (*fn)(NNSG3dRS *), u8 *addr, s32 cmd, s32 timing);
s32 NNS_G3dDraw(void *p);
void MI_Copy36B(void *p, void *q);
#define data_027e0184 HOST_LABEL(u8 (*)[], data_027e0184)
#define data_027e0148 HOST_LABEL(u32 (*)[], data_027e0148)
void NNS_G3dGlbSetBaseTrans(void *p);
void NNS_G3dGlbSetBaseScale(void *p);
s32 func_01ffcb0c(s32 a, s32 b);
void NNS_G3dDraw1Mat1Shp(void *p, s32 a, s32 b, s32 c);
s32 NNS_G3dGetSbcCmdLen(void *p);
void NNS_G3dBindMdlTex(void *p, void *tex);
void NNS_G3dBindMdlPltt(void *p, void *tex);
void NNS_G3dRenderObjInit(void *p, void *q);
u32 SceneLights_GetMatLightMask(void);
void NNSi_G3dModifyMatFlag(void *p, s32 a, s32 b);
void MTX_Identity43_(void *p);
u32 NNS_G3dPlttGetRequiredSize(void *p);
void NNS_G3dPlttSetPlttKey(void *p, u32 x);
void DC_FlushRange(void *p, u32 a);
void NNS_G3dPlttLoad(void *p, s32 a);
u32 NNS_G3dTexGetRequiredSize(void *p);
u32 NNS_G3dTex4x4GetRequiredSize(void *p);
void NNS_G3dTexSetTexKey(void *p, u32 y, u32 z);
void NNS_G3dTexLoad(void *p, s32 a);
void NNS_G3dRenderObjRemoveAnmObj(void *a, void *b);
void NNS_G3dRenderObjAddAnmObj(void *a, void *b);
void NNS_G3dAnmObjInit(void *p, void *q, void *r, void *s);
void MI_CpuCopy8(void *src, void *dst, u32 n);
s32 NNS_G3dGetResultMtx(void *a, void *b, s32 c, s32 d);
void *NNS_G3dGlbGetInvV(void);
void MTX_Concat43(void *a, void *b, void *c);
extern u8 gFieldSceneKind;
}

extern "C" {
BOOL Gfx3d_LoadTexAndPltt(NNSG3dResTex *a, TexVramSlot *b);
BOOL Gfx3d_LoadPltt(NNSG3dResTex *a, TexVramSlot *b);
BOOL Gfx3d_LoadPlttWithKey(NNSG3dResTex *a, u32 x);
BOOL Gfx3d_LoadTex(NNSG3dResTex *a, TexVramSlot *b);
BOOL Gfx3d_LoadTexWithKeys(NNSG3dResTex *a, u32 y, u32 z);
void *ResCache_FindTex(u32 key);
void *ResCache_FindModel(u32 key);
void *Gfx3d_CopyTex(void *a, void *heap);
void *Gfx3d_CopyModel(u32 *a, void *heap);
}

void ModelAnim::initFromResource(void *a, void *b, u32 c, u32 d, u16 e) {
    ((AnimFrameCtrl *)(this))->setup(((NNSG3dResAnmCommon *)a)->numFrame, c, d, e);
    NNS_G3dAnmObjInit(anmObj, a, resMdl, b);
    *(u32 *)anmObj = e << 12;
}

void ModelAnim::init(void *a, s32 b, s32 c, u16 e) {
    initFromResource(a, NULL, b, c, e);
}

void ModelAnim::replace(void *a, void *b, s32 c, s32 e, u16 f) {
    removeFromRenderObj(a);
    initFromResource(b, NULL, c, e, f);
    addToRenderObj(a);
}

void ModelAnim::initWithTex(void *a, void *b, s32 c, s32 e, u16 f) {
    initFromResource(a, b, c, e, f);
}

void ModelAnim::replaceWithTex(void *a, void *b, void *c, u8 d, s32 e, u16 f) {
    removeFromRenderObj(a);
    initFromResource(b, c, d, e, f);
    addToRenderObj(a);
}

void ModelAnim::addToRenderObj(void *a) {
    NNS_G3dRenderObjAddAnmObj(a, anmObj);
}

void ModelAnim::removeFromRenderObj(void *a) {
    NNS_G3dRenderObjRemoveAnmObj(a, anmObj);
}

ModelBase::ModelBase() {
}

ModelBase::~ModelBase() {
}

extern "C" void ResCache_Init(void) {
BOOL c; s32 i; s32 j;
    for (i = 0; i < 0x96; i++) { sResCacheModels[i].data = NULL; sResCacheModels[i].key = 0x4e554c4c; }
    for (j = 0; j < 0x3c; j++) { sResCacheTexs[j].data = NULL; sResCacheTexs[j].key = 0x4e554c4c; }
    sResCacheModelCount = 0; sResCacheTexCount = 0;
    c = FALSE;
    if (gFieldSceneKind == 0) c = TRUE;
    ModelCacheHeap_Create(c ? 0x7800 : 0x10400, 0);
}

extern "C" void ResCache_Destroy(void) {
    ModelCacheHeap_Destroy();
}

extern "C" void *ResCache_FindModel(u32 key) {
    s32 i;
    s32 n;
    if (key == 0x4e554c4c) {
        return NULL;
    }
    i = 0;
    n = sResCacheModelCount;
    for (; i < n; i++) {
        if (key == sResCacheModels[i].key) {
            return sResCacheModels[i].data;
        }
    }
    return NULL;
}

extern "C" void *ResCache_FindTex(u32 key) {
    s32 i;
    if (key == 0x4e554c4c) {
        return NULL;
    }
    for (i = 0; i < 0x3c; i++) {
        if (key == sResCacheTexs[i].key) {
            return sResCacheTexs[i].data;
        }
    }
    return NULL;
}

extern "C" void *Gfx3d_CopyModel(u32 *a, void *heap) {
    void *p = Heap_Alloc((Heap *)heap, *a);
    if (p == NULL) {
        return NULL;
    }
    MI_CpuCopy8(a, p, *a);
    return p;
}

extern "C" void *ResCache_GetModel(u32 *a, u32 key) {
    Heap *heap = gModelCacheHeap;
    void *r;
    if (key == 0x4e554c4c || (r = ResCache_FindModel(key)) == NULL) {
        if (sResCacheModelCount >= 0x96) {
            Fatal_Trap();
            return NULL;
        }
        r = Gfx3d_CopyModel(a, heap);
        if (r == NULL) {
            Fatal_Trap();
            return NULL;
        }
        s32 n = sResCacheModelCount;
        sResCacheModels[n].data = r;
        sResCacheModels[n].key = key;
        sResCacheModelCount++;
    }
    return r;
}

extern "C" void *Gfx3d_CopyTex(void *a, void *heap) {
    u32 n = ((G3dResAccess *)(a))->getTexImageOffset();
    void *p = Heap_Alloc((Heap *)heap, n);
    if (p == NULL) {
        return NULL;
    }
    MI_CpuCopy8(a, p, n);
    return p;
}

extern "C" void *ResCache_GetTex(void *a, u32 key) {
    Heap *heap = gModelCacheHeap;
    void *r;
    if (key == 0x4e554c4c || (r = ResCache_FindTex(key)) == NULL) {
        if (sResCacheTexCount >= 0x3c) {
            Fatal_Trap();
            return NULL;
        }
        r = Gfx3d_CopyTex(a, heap);
        if (r == NULL) {
            Fatal_Trap();
            return NULL;
        }
        s32 n = sResCacheTexCount;
        sResCacheTexs[n].data = r;
        sResCacheTexs[n].key = key;
        sResCacheTexCount++;
    }
    return r;
}

extern "C" BOOL Gfx3d_LoadTexWithKeys(NNSG3dResTex *a, u32 y, u32 z) {
    NNS_G3dTexSetTexKey(a, y, z);
    DC_FlushRange(a, a->header.size);
    NNS_G3dTexLoad(a, 1);
    return TRUE;
}

extern "C" BOOL Gfx3d_LoadTex(NNSG3dResTex *a, TexVramSlot *b) {
    u32 y = NNS_G3dTexGetRequiredSize(a);
    u32 z = NNS_G3dTex4x4GetRequiredSize(a);
    if (b != NULL) {
        y = b->makeTexKey(y);
        z = b->makeTex4x4Key(z);
    } else {
        y = data_0213bc10(y, 0, 0);
        z = data_0213bc10(z, 1, 0);
    }
    return Gfx3d_LoadTexWithKeys(a, y, z);
}

extern "C" BOOL Gfx3d_LoadPlttWithKey(NNSG3dResTex *a, u32 x) {
    NNS_G3dPlttSetPlttKey(a, x);
    DC_FlushRange(a, a->header.size);
    NNS_G3dPlttLoad(a, 1);
    return TRUE;
}

extern "C" BOOL Gfx3d_LoadPltt(NNSG3dResTex *a, TexVramSlot *b) {
    u32 x = NNS_G3dPlttGetRequiredSize(a);
    if (b != NULL) {
        x = b->makePlttKey(x);
    } else {
        x = data_0213bc18(x, 0, 0);
    }
    return Gfx3d_LoadPlttWithKey(a, x);
}

extern "C" BOOL Gfx3d_LoadTexAndPltt(NNSG3dResTex *a, TexVramSlot *b) {
    BOOL r = Gfx3d_LoadTex(a, b);
    return r | Gfx3d_LoadPltt(a, b);
}

Model::Model() {
    reset();
}

Model::~Model() {
}

void Model::reset() {
    NNS_G3dRenderObjInit(unk_08, NULL);
    resMdl = NULL;
    resTex = NULL;
    MTX_Identity43_(unk_64);
    modelFlags = 0;
    texVramSlot = NULL;
}

void Model::initRenderObj() {
    NNS_G3dRenderObjInit(unk_08, resMdl);
    NNSG3dResMat *b = (NNSG3dResMat *)((u8 *)resMdl + resMdl->ofsMat);
    s32 i;
    for (i = 0; i < resMdl->info.numMat; i++) {
        u8 *ent = (u8 *)&b->dict + b->dict.ofsEntry;
        u16 sz = *(u16 *)ent;
        ent += sz * i;
        u32 *p = (u32 *)((u8 *)b + *(u32 *)(ent + 4));
        if ((p[3] & 0xf) != 0) {
            p[3] &= ~0xf;
            p[3] |= SceneLights_GetMatLightMask();
        }
    }
    NNSi_G3dModifyMatFlag(resMdl, 0, 0x400);
}

BOOL Model::setResourceAndBind(NNSG3dResMdl *a, NNSG3dResTex *b) {
    resMdl = a;
    resTex = b;
    if (resTex != NULL) {
        NNS_G3dBindMdlTex(resMdl, resTex);
        NNS_G3dBindMdlPltt(resMdl, resTex);
    }
    initRenderObj();
    return TRUE;
}

BOOL Model::setResource(NNSG3dResMdl *a, NNSG3dResTex *b) {
    resMdl = a;
    resTex = b;
    initRenderObj();
    return TRUE;
}

BOOL Model::clearResource() {
    reset();
    return TRUE;
}

void Model::drawShapesDirect(s32 *p) {
    s32 save;
    s32 v[3];
    u8 *hdr = (u8 *)resMdl;
    u8 *cmd = hdr + *(u32 *)(hdr + 4);
    s32 lim = *(s32 *)(hdr + 0x1c);
    if (lim == 0x1000) {
        applyTransform(p);
    } else {
        if (p == NULL) {
            v[0] = v[1] = v[2] = lim;
        } else {
            v[0] = func_01ffcb0c(p[0], lim);
            v[1] = func_01ffcb0c(p[1], lim);
            v[2] = func_01ffcb0c(p[2], lim);
        }
        applyTransform(v);
    }
    for (;;) {
        switch (*cmd & 0x1f) {
        case 1:
            return;
        case 4:
            save = cmd[1];
            break;
        case 5:
            NNS_G3dDraw1Mat1Shp(resMdl, save, cmd[1], 1);
            break;
        }
        cmd += NNS_G3dGetSbcCmdLen(cmd);
    }
}

void Model::drawScaled(s32 *p) {
    applyTransform(p);
    draw();
}

void Model::drawNoGeCmd() {
    *(u32 *)unk_08 |= 2;
    NNS_G3dDraw(unk_08);
}

void Model::applyTransform(s32 *p) {
    s32 v[3];
    MI_Copy36B(unk_64, data_027e0184);
    data_027e0148[0x7c / 4] &= ~0xa4;
    NNS_G3dGlbSetBaseTrans(baseTrans);
    if (p == NULL) {
        v[0] = v[1] = v[2] = 0x1000;
        NNS_G3dGlbSetBaseScale(v);
    } else {
        NNS_G3dGlbSetBaseScale(p);
    }
    NNS_G3dGlbFlushP();
}

void Model::draw() {
    NNS_G3dDraw(unk_08);
}

void *Model::getRenderObj() {
    return unk_08;
}

void Model::setCallback(void (*a)(NNSG3dRS *), s32 b, s32 c, void *d, u8 *e) {
    NNS_G3dRenderObjSetCallBack(unk_08, a, e, b, c);
    renderUserPtr = d;
}

void Model::setInitCallback(void (*a)(NNSG3dRS *), void *b) {
    NNS_G3dRenderObjSetInitFunc(unk_08, a);
    renderUserPtr = b;
}

void Model::setPolygonId(u32 v) {
    s32 i;
    NNSG3dResMat *b;
    b = (NNSG3dResMat *)((u8 *)resMdl + resMdl->ofsMat);
    i = 0;
    u32 sh = v << 24;
    for (; i < resMdl->info.numMat; i++) {
        u8 *ent = (u8 *)&b->dict + b->dict.ofsEntry;
        u16 sz = *(u16 *)ent;
        ent += sz * i;
        u32 *p = (u32 *)((u8 *)b + *(u32 *)(ent + 4));
        p[3] &= 0xc0ffffff;
        p[3] |= sh;
    }
}

void Model::setAlpha(u32 v) {
    s32 i;
    NNSG3dResMat *b;
    b = (NNSG3dResMat *)((u8 *)resMdl + resMdl->ofsMat);
    i = 0;
    u32 sh = v << 16;
    for (; i < resMdl->info.numMat; i++) {
        u8 *ent = (u8 *)&b->dict + b->dict.ofsEntry;
        u16 sz = *(u16 *)ent;
        ent += sz * i;
        u32 *p = (u32 *)((u8 *)b + *(u32 *)(ent + 4));
        p[3] &= 0xffe0ffff;
        p[3] |= sh;
    }
}

extern "C" BOOL Model_GetJointWorldMtx(Model *p, Mtx43 *a, s32 b) {
    if (!NNS_G3dGetResultMtx(p->getRenderObj(), a, 0, b)) {
        return FALSE;
    }
    MTX_Concat43(a, NNS_G3dGlbGetInvV(), a);
    return TRUE;
}

TexVramSlot::TexVramSlot() {
    clear();
}

TexVramSlot::~TexVramSlot() {}

BOOL TexVramSlot::alloc(u32 texSize, u32 tex4x4Size, u32 plttSize) {
    if (texSize != 0) {
        texKeyBase = data_0213bc10(texSize, 0, 0);
    }
    if (tex4x4Size != 0) {
        tex4x4KeyBase = data_0213bc10(tex4x4Size, 1, 0);
    }
    if (plttSize != 0) {
        plttKeyBase = data_0213bc18(plttSize, 0, 0);
    }
    unk_10 = 1;
    return TRUE;
}

u32 TexVramSlot::makeTexKey(u32 a) {
    return makeKeyWithBase(a, texKeyBase);
}

u32 TexVramSlot::makeTex4x4Key(u32 a) {
    return makeKeyWithBase(a, tex4x4KeyBase);
}

u32 TexVramSlot::makeKeyWithBase(u32 a, u32 b) {
    return (b & 0x8000ffff) | ((a >> 4) << 16);
}

u32 TexVramSlot::makePlttKey(u32 a) {
    return (plttKeyBase & 0xffff) | ((a >> 3) << 16);
}

u32 TexVramSlot::makeTexKeyAt(u32 a, u32 b) {
    return makeKeyAtOffset(b, texKeyBase, a);
}

u32 TexVramSlot::makeTex4x4KeyAt(u32 a, u32 b) {
    return makeKeyAtOffset(b, tex4x4KeyBase, a);
}

u32 TexVramSlot::makeKeyAtOffset(u32 a, u32 b, u32 c) {
    u32 v = (b & 0xffff) << 3;
    v += ((c & 0x7fff0000) >> 16) << 4;
    u32 top = (c & 0x80000000) >> 31;
    top <<= 31;
    u32 r = (a >> 4) << 16;
    return top | (r | ((v >> 3) & 0xffff));
}

u32 TexVramSlot::makePlttKeyAt(u32 a, u32 b) {
    u32 v = (plttKeyBase & 0xffff) << 3;
    v += ((a & 0xffff0000) >> 16) << 3;
    u32 r = (b >> 3) << 16;
    return r | ((v >> 3) & 0xffff);
}

void TexVramSlot::relocateTexture(void *p) {
    s32 a = NNS_G3dTexGetRequiredSize(p);
    s32 b = NNS_G3dTex4x4GetRequiredSize(p);
    s32 c = NNS_G3dPlttGetRequiredSize(p);
    s32 x = makeTexKey(a);
    s32 y = makeTex4x4Key(b);
    s32 z = makePlttKey(c);
    NNS_G3dTexSetTexKey(p, x, y);
    NNS_G3dPlttSetPlttKey(p, z);
    unk_10 = 1;
}

void TexVramSlot::clear(void) {
    texKeyBase = 0;
    tex4x4KeyBase = 0;
    plttKeyBase = 0;
    unk_10 = 0;
    unk_11 = 0;
}

