#include "types.h"
#include "gfx/AnimFrameCtrl.h"
#include "gfx/JointBlend.h"
#include "gfx/NNSG3dRS.h"




struct NNSG3dAnmObj {
    u32 frame;
    u32 ratio;
    void *resAnm;
    void *funcAnm;
    NNSG3dAnmObj *next;
};


struct NNSG3dResJntAnm {
    u32 anmHeader;
    u16 numFrame;
    u16 pad_06;
    u32 flag;
};




#include "gfx/CachedModel.h"
#include "gfx/ModelSet.h"
#include "gfx/AnimModel.h"
#include "gfx/TwoLayerAnimModel.h"
#include "gfx/ThreeLayerAnimModel.h"
#include "gfx/Model.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_0212a120.h"
#include "proto/main/unk_020536dc.h"
#include "proto/main/unk_02053848.h"
#include "proto/main/unk_02055bcc.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_0206fc44.h"
#include "proto/main/unk_0206fde4.h"
#include "proto/main/unk_02070560.h"








extern "C" {
void MTX_Identity33_(void *p);
BOOL func_01ffcc10(void *a, NNSG3dRS *o);
void NNS_G3dAnmObjInit(void *a, void *b, void *c, void *d);
void NNS_G3dRenderObjRemoveAnmObj(void *a, void *b);
void NNS_G3dRenderObjAddAnmObj(void *a, void *b);
extern char sJointAnmHeader2[];
void *NNS_G3dGetMdlSet(void *p);
void *NNS_G3dGetTex(void *p);
void MI_CpuCopy8(void *src, void *dst, u32 size);
BOOL Gfx3d_LoadTexAndPltt(NNSG3dResTex *a, TexVramSlot *b);
void *Gfx3d_CopyTex(void *a, void *heap);
void *Gfx3d_CopyModel(void *a, void *heap);
void NNS_G3dBindMdlTex(void *a, void *b);
void NNS_G3dBindMdlPltt(void *a, void *b);
void NNS_G3dForceBindMdlTex(void *a, void *b, s32 c, s32 d);
BOOL NNS_G3dForceBindMdlPltt(void *mdl, void *tex, u32 i, u32 j);
void *ResCache_GetModel(void *a, u32 tag);
void *ResCache_FindModel(u32 key);
void AnimModel_SwitchAnmObj(void *p, void *q);
void ThreeLayerAnimModel_AssignJointsToLayer2(void *a, u32 b, u32 c);
u16 Anim_GetFrameCountForMode(u32 kind, NNSG3dResJntAnm *p);
}

char sJointAnmHeader2[4] = {0x4a, 0x00, 0x41, 0x43};

static inline u8 *Unk_02054b70_Off(u8 *p) {
    return p + *(u32 *)(p + *(u16 *)(p + 0xe) + 0xc);
}

CachedModel::CachedModel() : cacheKey(0x4e554c4c) {}

CachedModel::~CachedModel() {}

BOOL CachedModel::loadKeyed(void *res, void *name, u32 tag) {
    Heap *heap = gCurrentHeap;
    void *h = File_LoadAlloc((const char *)res, heap, -4, 0);
    if (h == NULL) {
        return FALSE;
    }
    u8 *p = Unk_02054b70_Off((u8 *)NNS_G3dGetMdlSet(h));
    void *q = NNS_G3dGetTex(h);
    if (name != NULL) {
        resMdl = (NNSG3dResMdl *)Gfx3d_CopyModel(p, name);
    } else {
        resMdl = (NNSG3dResMdl *)ResCache_GetModel(p, tag);
    }
    if (q != NULL) {
        Gfx3d_LoadTexAndPltt((NNSG3dResTex *)q, texVramSlot);
        NNS_G3dBindMdlTex(resMdl, q);
        NNS_G3dBindMdlPltt(resMdl, q);
    }
    Heap_Free(heap, h);
    initRenderObj();
    return TRUE;
}

BOOL CachedModel::loadWithTexKeyed(void *res, void *name, void *tex, void *d, u32 *e, s32 f, u32 tag) {
    Heap *heap = gCurrentHeap;
    void *h = File_LoadAlloc((const char *)res, heap, -4, 0);
    if (h == NULL) {
        return FALSE;
    }
    u8 *p = Unk_02054b70_Off((u8 *)NNS_G3dGetMdlSet(h));
    if (name != NULL) {
        resMdl = (NNSG3dResMdl *)Gfx3d_CopyModel(p, name);
    } else {
        resMdl = (NNSG3dResMdl *)ResCache_GetModel(p, tag);
    }
    if (tex != NULL) {
        NNS_G3dBindMdlTex(resMdl, tex);
    } else {
        void *q = NNS_G3dGetTex(h);
        if (q != NULL) {
            Gfx3d_LoadTexAndPltt((NNSG3dResTex *)q, texVramSlot);
            NNS_G3dBindMdlTex(resMdl, q);
        }
    }
    if (d != NULL) {
        s32 i;
        for (i = 0; i < f; i++) {
            NNS_G3dForceBindMdlPltt(resMdl, d, i, e[i]);
        }
    }
    Heap_Free(heap, h);
    initRenderObj();
    return TRUE;
}

BOOL CachedModel::load(void *res, void *name) {
    return loadKeyed(res, name, 0x4e554c4c);
}

BOOL CachedModel::loadWithTex(void *res, void *name, void *tex, void *d, u32 *e, s32 f) {
    return loadWithTexKeyed(res, name, tex, d, e, f, 0x4e554c4c);
}

BOOL CachedModel::loadCached(u32 tag, void *path) {
    resMdl = (NNSG3dResMdl *)ResCache_FindModel(tag);
    if (resMdl != NULL) {
        initRenderObj();
        return TRUE;
    }
    cacheKey = tag;
    return loadKeyed(path, NULL, tag);
}

BOOL CachedModel::loadWithSharedTex(void *a, s32 player, s32 pattern) {
    Heap *heap = gCurrentHeap;
    void *h = File_LoadAlloc((const char *)a, heap, -4, 0);
    if (h == NULL) {
        return FALSE;
    }
    u8 *p = Unk_02054b70_Off((u8 *)NNS_G3dGetMdlSet(h));
    resMdl = (NNSG3dResMdl *)ResCache_GetModel(p, 0x4e554c4c);
    void *r = ((PatternTexCache *)PatternTexCache_Get())->getPlayerTexKey(player, pattern);
    NNS_G3dForceBindMdlTex(resMdl, r, 0, 0);
    NNS_G3dForceBindMdlPltt(resMdl, r, 0, 0);
    Heap_Free(heap, h);
    initRenderObj();
    return TRUE;
}

void CachedModel::setFromFile(void *a) {
    u8 *p = Unk_02054b70_Off((u8 *)NNS_G3dGetMdlSet(a));
    void *q = NNS_G3dGetTex(a);
    resMdl = (NNSG3dResMdl *)p;
    NNS_G3dBindMdlTex(resMdl, q);
    NNS_G3dBindMdlPltt(resMdl, q);
    initRenderObj();
}

BOOL CachedModel::allocJointRecord(void *heap) {
    u32 size = renderResMdl[0x17] * 0x58;
    if (heap == NULL) {
        heap = gCurrentHeap;
    }
    void *p = Heap_Alloc((Heap *)heap, size);
    if (p == NULL) {
        return FALSE;
    }
    renderJntRecord = p;
    renderObj |= 1;
    return TRUE;
}

BOOL CachedModel::release(void) {
    BOOL r = TRUE;
    r &= clearResource();
    cacheKey = 0x4e554c4c;
    return r;
}

ModelSet::ModelSet() : numModels(0), models(0) {}

ModelSet::~ModelSet() {}

extern "C" BOOL ModelSet_Load(ModelSet *t, void *file, void *heap)
{
    u32 size;
    void *fileHeap;
    void *res;
    void *hdr;
    u32 i;
    if (heap == 0) {
        heap = gModelCacheHeap;
    }
    fileHeap = gCurrentHeap;
    res = File_LoadAlloc((const char *)file, fileHeap, -4, 0);
    if (res == 0) {
        return FALSE;
    }
    u8 *hdr2 = (u8 *)NNS_G3dGetMdlSet(res);
    t->numModels = hdr2[9];
    size = t->numModels << 4;
    t->modelNames = (u8 *)Heap_Alloc((Heap *)heap, size);
    {
        u8 *p = hdr2 + 8;
        p = p + *(u16 *)(hdr2 + 0xe);
        MI_CpuCopy8(p + *(u16 *)(p + 2), t->modelNames, size);
    }
    t->models = (CachedModel *)Heap_Alloc((Heap *)heap, t->numModels * sizeof(CachedModel));
    for (i = 0; i < t->numModels; i++) {
        new (&t->models[i]) CachedModel();
    }
    hdr = NNS_G3dGetTex(res);
    Gfx3d_LoadTexAndPltt((NNSG3dResTex *)hdr, NULL);
    hdr = Gfx3d_CopyTex(hdr, heap);
    for (i = 0; i < t->numModels; i++) {
        u8 *h = (u8 *)NNS_G3dGetMdlSet(res);
        u8 *p = h + 8;
        u32 off = *(u16 *)(h + 0xe);
        u32 st = *(u16 *)(p + off);
        u8 *q = h + *(s32 *)(p + off + st * i + 4);
        void *r = Gfx3d_CopyModel(q, heap);
        ((Model *)(&t->models[i]))->setResourceAndBind((NNSG3dResMdl *)(r), (NNSG3dResTex *)hdr);
    }
    Heap_Free((Heap *)fileHeap, res);
    return TRUE;
}

extern "C" void *ModelSet_Find(ModelSet *t, void *name)
{
    u32 i = 0;
    u32 n = t->numModels;
    for (; i < n; i++) {
        if (strcmp((const char *)name, (const char *)t->modelNames + i * 16) == 0) {
            return &t->models[i];
        }
    }
    return 0;
}

extern "C" BOOL ModelSet_Release(ModelSet *t)
{
    BOOL r = TRUE;
    if (t->numModels == 0) {
        return r;
    }
    for (u32 i = 0; i < t->numModels; i++) {
        r &= t->models[i].release();
    }
    t->numModels = 0;
    return TRUE;
}

AnimModel::AnimModel()
{
    anmObj = 0;
}

AnimModel::~AnimModel() {}

BOOL AnimModel::allocAnmObj(void *x)
{
    if (anmObj != 0 || resMdl == 0) {
        return FALSE;
    }
    anmObj = (NNSG3dAnmObj *)Gfx3d_AllocAnmObj(resMdl, sJointAnmHeader2, x);
    if (anmObj != 0) {
        return TRUE;
    }
    return FALSE;
}

void AnimModel::stepAnim()
{
    AnimFrameCtrl &r = *this;
    ((AnimFrameCtrl *)(&r))->step();
    anmObj->frame = curFrame;
}

void AnimModel::drawAnimated(void *q)
{
    if (renderJntRecord != 0) {
        renderObj |= 1;
    }
    ((Model *)(this))->drawScaled((s32 *)(q));
}

void AnimModel::setFrame(s32 v)
{
    curFrame = v << 12;
    anmObj->frame = curFrame;
    if (renderJntRecord != 0) {
        renderObj |= 1;
    }
}

extern "C" u16 Anim_GetFrameCountForMode(u32 kind, NNSG3dResJntAnm *p)
{
    u16 r = p->numFrame;
    if (kind == 0 || kind == 2) {
        u32 f = p->flag;
        if (f & 2) {
            return r;
        }
        if (f & 1) {
            r = r - 1;
        }
    }
    return r;
}

void BlendAnimModel::initAnim(void *a, s32 b, s32 c, u16 d, u16 e)
{
    if (e == 0) {
        e = Anim_GetFrameCountForMode(b, (NNSG3dResJntAnm *)a);
    }
    AnimFrameCtrl &r = *this;
    ((AnimFrameCtrl *)(&r))->setup(e, b, c, d);
    NNS_G3dAnmObjInit(anmObj, a, resMdl, NULL);
    anmObj->frame = curFrame;
}

void AnimModel::attachAnim()
{
    NNS_G3dRenderObjAddAnmObj(&renderObj, anmObj);
}

void AnimModel::detachJointAnim()
{
    if (anmObj != 0) {
        NNS_G3dRenderObjRemoveAnmObj(&renderObj, renderAnmJnt);
        anmObj = 0;
    }
}

void AnimModel::detachVisAnim()
{
    if (anmObj != 0) {
        NNS_G3dRenderObjRemoveAnmObj(&renderObj, renderAnmVis);
        anmObj = 0;
    }
}

void AnimModel::detachAnim()
{
    if (anmObj != 0) {
        if (renderAnmJnt == anmObj) {
            NNS_G3dRenderObjRemoveAnmObj(&renderObj, renderAnmJnt);
            anmObj = 0;
        } else if (renderAnmVis == anmObj) {
            NNS_G3dRenderObjRemoveAnmObj(&renderObj, renderAnmVis);
            anmObj = 0;
        }
    }
}

extern "C" void JointCb_UseRestTranslation(NNSG3dRS *o, s32 x)
{
    u32 idx = o->c[1];
    if (idx >= 2) {
        u8 *b = o->pResNodeInfo;
        u32 off = *(u16 *)(b + 6);
        u8 *t = b + off;
        u32 st = *(u16 *)(b + off);
        u8 *e = b + *(s32 *)(t + st * idx + 4);
        s32 *v = (s32 *)(e + 4);
        NNSG3dJntAnmResult *d = o->pJntAnmResult;
        d->trans.x = v[0];
        d->trans.y = v[1];
        d->trans.z = v[2];
    } else if (idx == 1) {
        if (x != 0) {
            u8 *b = o->pResNodeInfo;
            u32 off = *(u16 *)(b + 6);
            u8 *t = b + off;
            NNSG3dJntAnmResult *d = o->pJntAnmResult;
            s32 old = d->trans.y;
            u32 st = *(u16 *)(b + off);
            u8 *e = b + *(s32 *)(t + st * idx + 4);
            d->trans.y = old + (*(s32 *)(e + 8) - x);
        }
    }
}

extern "C" void JointCb_CalcCpuMatrix(void *unused, NNSG3dRS *o, void *p)
{
    u32 t = *o->c & 0xe0;
    if (t == 0x40) {
        CpuMtx_RestoreFromStack(o->c[4]);
    } else if (t == 0x60) {
        CpuMtx_RestoreFromStack(o->c[5]);
    }
    if (p != 0) {
        NNSG3dJntAnmResult *d = o->pJntAnmResult;
        CpuMtx_MultRotScaledTrans(&d->rot, &d->trans, (VecFx32 *)p);
    } else {
        NNSG3dJntAnmResult *d = o->pJntAnmResult;
        u32 f = d->flag;
        if (f & 2) {
            if (!(f & 4)) {
                CpuMtx_MultTrans(&d->trans);
            }
        } else if (f & 4) {
            CpuMtx_MultRot(&d->rot);
        } else {
            CpuMtx_MultRotTrans(&d->rot, &d->trans);
        }
    }
    if (t == 0x20 || t == 0x60) {
        CpuMtx_StoreToStack(o->c[4]);
    }
}

void *BlendAnimModel::getAnmRes()
{
    return anmObj->resAnm;
}

NNSG3dAnmObj *BlendAnimModel::getAnmObj()
{
    return anmObj;
}

BlendAnimModel::BlendAnimModel()
{
}

BlendAnimModel::~BlendAnimModel() {}

void BlendAnimModel::captureJointPose(NNSG3dRS *x)
{
    if (blendStep != 0) {
        JointBlend &r = *this;
        ((JointBlend *)(&r))->capturePose(x);
    }
}

void BlendAnimModel::onJointCalcPre(NNSG3dRS *x)
{
    if (func_01ffcc10(this, x) == 0) {
        captureJointPose(x);
    }
}

void BlendAnimModel::applyJointBlend(NNSG3dRS *x)
{
    NNSG3dJntAnmResult *d = x->pJntAnmResult;
    if (d->flag & 4) {
        d->trans.x = 0;
        d->trans.y = 0;
        d->trans.z = 0;
    }
    if (d->flag & 2) {
        MTX_Identity33_(&d->rot);
    }
    if (blendStep != 0) {
        JointBlend &r = *this;
        ((JointBlend *)(&r))->blendPose(x);
    }
}

void BlendAnimModel::onJointCalcPost(NNSG3dRS *x)
{
    if (func_01ffcc10(this, x) == 0) {
        applyJointBlend(x);
    }
}

void BlendAnimModel::stepBlend()
{
    JointBlend &r = *this;
    ((JointBlend *)(&r))->advance();
    stepAnim();
}

void BlendAnimModel::playBlend(void *a, s32 b, s32 c, s32 d, u16 e, u16 f)
{
    JointBlend &r = *this;
    ((JointBlend *)(&r))->start(b);
    initAnim(a, c, d, e, f);
}

TwoLayerAnimModel::TwoLayerAnimModel()
{
    layer2AnmObj = 0;
    layer2JointMask = 0;
    layer2JointMaskHi = 0;
}

TwoLayerAnimModel::~TwoLayerAnimModel() {}

extern "C" void AnimModel_SwitchAnmObj(void *pv, void *qv) {
    Model *p = (Model *)pv;
    NNSG3dAnmObj *q = (NNSG3dAnmObj *)qv;
    NNSG3dAnmObj *cur = p->renderAnmJnt;
    if (cur != q && cur != NULL && cur->next == 0) {
        NNS_G3dRenderObjRemoveAnmObj(&p->renderObj, cur);
        NNS_G3dRenderObjAddAnmObj(&p->renderObj, q);
    }
}

void TwoLayerAnimModel::onJointLayerRelease(u32 i) {}

void TwoLayerAnimModel::onJointLayerAssign(u32 i) {}

void TwoLayerAnimModel::setLayer2Joint(u32 i) {
    if (i >= 0x20) {
        layer2JointMaskHi |= 1 << (i - 0x20);
    } else {
        layer2JointMask |= 1 << i;
    }
}

void TwoLayerAnimModel::clearLayer2Joint(u32 i) {
    if (i >= 0x20) {
        layer2JointMaskHi &= ~(1 << (i - 0x20));
    } else {
        layer2JointMask &= ~(1 << i);
    }
}

BOOL TwoLayerAnimModel::isLayer2Joint(u32 i) {
    if (i >= 0x20) {
        if ((layer2JointMaskHi & (1 << (i - 0x20))) == 0) {
            return FALSE;
        }
        return TRUE;
    }
    if ((layer2JointMask & (1 << i)) == 0) {
        return FALSE;
    }
    return TRUE;
}

void TwoLayerAnimModel::captureLayer2Pose(NNSG3dRS *m) {
    if (layer2Blend.blendStep != 0) {
        ((JointBlend *)(&layer2Blend))->capturePose((NNSG3dRS *)(m));
    }
}

void TwoLayerAnimModel::onJointCalcPreLayer2(NNSG3dRS *m) {
    if (func_01ffcc10(this, m) == 0) {
        if (isLayer2Joint(m->c[1])) {
            AnimModel_SwitchAnmObj(this, layer2AnmObj);
            captureLayer2Pose(m);
        } else {
            AnimModel_SwitchAnmObj(this, anmObj);
            captureJointPose(m);
        }
    }
}

void TwoLayerAnimModel::applyLayer2Blend(NNSG3dRS *m) {
    if ((m->pJntAnmResult->flag & 4) != 0) {
        m->pJntAnmResult->trans.x = 0;
        m->pJntAnmResult->trans.y = 0;
        m->pJntAnmResult->trans.z = 0;
    }
    if (layer2Blend.blendStep != 0) {
        ((JointBlend *)(&layer2Blend))->blendPose((NNSG3dRS *)(m));
    }
}

void TwoLayerAnimModel::onJointCalcPostLayer2(NNSG3dRS *m) {
    if (func_01ffcc10(this, m) == 0) {
        if (isLayer2Joint(m->c[1])) {
            applyLayer2Blend(m);
        } else {
            applyJointBlend(m);
        }
    }
}

BOOL TwoLayerAnimModel::allocLayerAnims(void *a) {
    if (!allocAnmObj(a)) {
        return FALSE;
    }
    layer2AnmObj = Gfx3d_AllocAnmObj(resMdl, sJointAnmHeader2, a);
    if (layer2AnmObj != NULL) {
        return TRUE;
    }
    return FALSE;
}

void TwoLayerAnimModel::updateLayers() {
    stepBlend();
    if (layer2JointMask != 0 || layer2JointMaskHi != 0) {
        if (((JointBlend *)(&layer2Blend))->advance() != 0 && (modelFlags & 0x4000) != 0) {
            clearLayer2Mask();
            modelFlags = modelFlags & 0xffffbfff;
        }
        ((AnimFrameCtrl *)(&layer2Frame))->step();
        *(u32 *)layer2AnmObj = layer2Frame.curFrame;
    }
}

void TwoLayerAnimModel::drawLayered(void *a) {
    ((AnimModel *)(this))->drawAnimated(a);
    AnimModel_SwitchAnmObj(this, anmObj);
}

extern "C" void BlendAnimModel_Play(void *p, void *a, s32 b, s32 c, s32 d, u16 e, u16 f) {
    ((BlendAnimModel *)p)->playBlend(a, b, c, d, e, f);
}

void TwoLayerAnimModel::playLayer2(void *a, u32 b, u32 c, u32 d, u32 e, u32 f, BOOL g) {
    ((JointBlend *)(&layer2Blend))->start(b);
    if (*(u16 *)&f == 0) {
        *(u16 *)&f = Anim_GetFrameCountForMode(c, (NNSG3dResJntAnm *)a);
    }
    ((AnimFrameCtrl *)(&layer2Frame))->setup(*(u16 *)&f, c, d, *(u16 *)&e);
    NNS_G3dAnmObjInit(layer2AnmObj, a, resMdl, NULL);
    if (g != 0) {
        modelFlags = modelFlags | 0x4000;
    } else {
        modelFlags = modelFlags & 0xffffbfff;
    }
}

void TwoLayerAnimModel::playLayer2FromBase(u32 a, u32 b) {
    if (a == 0) {
        clearLayer2Mask();
    } else {
        playLayer2(getAnmRes(), a, playMode, frameStep, ((u32)curFrame << 4) >> 16, b, 1);
    }
}

void TwoLayerAnimModel::assignJointsToLayer2(u32 a, u32 b) {
    u32 i = a;
    for (; i <= b; i++) {
        onJointLayerAssign(i);
        setLayer2Joint(i);
    }
}

void TwoLayerAnimModel::releaseJointsFromLayer2(u32 a, u32 b) {
    u32 i = a;
    for (; i <= b; i++) {
        onJointLayerRelease(i);
        clearLayer2Joint(i);
    }
}

void TwoLayerAnimModel::clearLayer2Mask() {
    layer2JointMaskHi = 0;
    layer2JointMask = layer2JointMaskHi;
}

ThreeLayerAnimModel::ThreeLayerAnimModel() {
    layer3AnmObj = NULL;
    layer3JointMask = 0;
    layer3JointMaskHi = 0;
}

ThreeLayerAnimModel::~ThreeLayerAnimModel() {
}

void ThreeLayerAnimModel::setLayer3Joint(u32 i) {
    if (i >= 0x20) {
        layer3JointMaskHi |= 1 << (i - 0x20);
    } else {
        layer3JointMask |= 1 << i;
    }
}

void ThreeLayerAnimModel::clearLayer3Joint(u32 i) {
    if (i >= 0x20) {
        layer3JointMaskHi &= ~(1 << (i - 0x20));
    } else {
        layer3JointMask &= ~(1 << i);
    }
}

BOOL ThreeLayerAnimModel::isLayer3Joint(u32 i) {
    if (i >= 0x20) {
        if ((layer3JointMaskHi & (1 << (i - 0x20))) == 0) {
            return FALSE;
        }
        return TRUE;
    }
    if ((layer3JointMask & (1 << i)) == 0) {
        return FALSE;
    }
    return TRUE;
}

void ThreeLayerAnimModel::captureLayer3Pose(NNSG3dRS *m) {
    if (layer3Blend.blendStep != 0) {
        ((JointBlend *)(&layer3Blend))->capturePose((NNSG3dRS *)(m));
    }
}

void ThreeLayerAnimModel::onJointCalcPreLayer3(NNSG3dRS *m) {
    if (func_01ffcc10(this, m) == 0) {
        u32 t = m->c[1];
        u32 v;
        if (t >= 0x20) {
            v = layer3JointMaskHi & (1 << (t - 0x20));
        } else {
            v = layer3JointMask & (1 << t);
        }
        if (v != 0) {
            AnimModel_SwitchAnmObj(this, layer3AnmObj);
            captureLayer3Pose(m);
        } else {
            u32 w;
            if (t >= 0x20) {
                w = layer2JointMaskHi & (1 << (t - 0x20));
            } else {
                w = layer2JointMask & (1 << t);
            }
            if (w != 0) {
                AnimModel_SwitchAnmObj(this, layer2AnmObj);
                captureLayer2Pose(m);
            } else {
                AnimModel_SwitchAnmObj(this, anmObj);
                captureJointPose(m);
            }
        }
    }
}

void ThreeLayerAnimModel::applyLayer3Blend(NNSG3dRS *m) {
    if ((m->pJntAnmResult->flag & 4) != 0) {
        m->pJntAnmResult->trans.x = 0;
        m->pJntAnmResult->trans.y = 0;
        m->pJntAnmResult->trans.z = 0;
    }
    if (layer3Blend.blendStep != 0) {
        ((JointBlend *)(&layer3Blend))->blendPose((NNSG3dRS *)(m));
    }
}

void ThreeLayerAnimModel::onJointCalcPostLayer3(NNSG3dRS *m) {
    if (func_01ffcc10(this, m) == 0) {
        u32 x = layer3JointMaskHi | (layer3JointMask | (layer2JointMask | layer2JointMaskHi));
        if (x == 0) {
            applyJointBlend(m);
        } else {
            u32 t = m->c[1];
            if ((x & (1 << (t & 0x1f))) == 0) {
                applyJointBlend(m);
            } else if (isLayer3Joint(t)) {
                applyLayer3Blend(m);
            } else if (isLayer2Joint(t)) {
                applyLayer2Blend(m);
            } else {
                applyJointBlend(m);
            }
        }
    }
}

BOOL ThreeLayerAnimModel::allocLayer3Anims(void *a) {
    if (!allocLayerAnims(a)) {
        return FALSE;
    }
    layer3AnmObj = Gfx3d_AllocAnmObj(resMdl, sJointAnmHeader2, a);
    if (layer3AnmObj != NULL) {
        return TRUE;
    }
    return FALSE;
}

void ThreeLayerAnimModel::updateLayers3() {
    updateLayers();
    if (layer3JointMask != 0 || layer3JointMaskHi != 0) {
        if (((JointBlend *)(&layer3Blend))->advance() != 0 && (modelFlags & 0x8000) != 0) {
            ThreeLayerAnimModel_ClearLayer3Mask(this);
            modelFlags = modelFlags & 0xffff7fff;
        }
        ((AnimFrameCtrl *)(&layer3Frame))->step();
        *(u32 *)layer3AnmObj = layer3Frame.curFrame;
    }
}

extern "C" void BlendAnimModel_Play2(void *p, void *a, s32 b, s32 c, s32 d, u16 e, u16 f) { BlendAnimModel_Play(p, a, b, c, d, e, f); }

void ThreeLayerAnimModel::playLayer3(void *a, u32 b, u32 c, u32 d, u32 e, u32 f, BOOL g) {
    ((JointBlend *)(&layer3Blend))->start(b);
    if (*(u16 *)&f == 0) {
        *(u16 *)&f = Anim_GetFrameCountForMode(c, (NNSG3dResJntAnm *)a);
    }
    ((AnimFrameCtrl *)(&layer3Frame))->setup(*(u16 *)&f, c, d, *(u16 *)&e);
    NNS_G3dAnmObjInit(layer3AnmObj, a, resMdl, NULL);
    if (g != 0) {
        modelFlags = modelFlags | 0x8000;
    } else {
        modelFlags = modelFlags & 0xffff7fff;
    }
}

BOOL ThreeLayerAnimModel::checkLayer3Finished() { return ((AnimFrameCtrl *)(&layer3Frame))->isFinished(); }

void ThreeLayerAnimModel::playLayer3FromBase(u32 a, u32 b) {
    if (a == 0) {
        ThreeLayerAnimModel_ClearLayer3Mask(this);
    } else {
        playLayer3(getAnmRes(), a, playMode, frameStep, ((u32)curFrame << 4) >> 16, b, 1);
    }
}

void ThreeLayerAnimModel::assignJointsToLayer3(u32 a, u32 b) {
    u32 i = a;
    for (; i <= b; i++) {
        onJointLayerAssign(i);
        clearLayer2Joint(i);
        setLayer3Joint(i);
    }
}

extern "C" void ThreeLayerAnimModel_AssignJointsToLayer2(void *a, u32 b, u32 c)
{
    ThreeLayerAnimModel *o = (ThreeLayerAnimModel *)a;
    for (; b <= c; b++) {
        o->onJointLayerAssign(b);
        o->setLayer2Joint(b);
        o->clearLayer3Joint(b);
    }
}

