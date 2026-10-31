#include "uptr.h"
#include "types.h"
#include "gfx/VecFx32.h"
#include "Unk_020d8c7c.h"
#include "gfx/Mtx43.h"
#include "field/Unk_ov003_02217b78_Ent.h"
#include "gfx/AnimFrameCtrl.h"
#include "gfx/ModelAnim.h"
#include "gfx/TexPatVramAnim.h"
#include "field/FieldGroundBackdrop.h"
#include "gfx/Model.h"
#include "sys/ProcProfile.h"
#include "gfx/DebugColor.h"
#include "gfx/NNSG3dRS.h"
#include "town/Unk_0204e858_Grid.h"
#include "gfx/BgModelCache.h"
#include "gfx/Camera.h"
#include "gfx/G3dResAccess.h"
#include "field/GroundSoundSrc.h"
#include "snd/RainSndChannel.h"
#include "town/MapBlockAcre.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_02036c58.h"
#include "proto/main/unk_02037260.h"
#include "proto/main/unk_0203ecec.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_020abbcc.h"
#include "proto/main/unk_020abea8.h"
#include "proto/main/unk_02088b98.h"
#include "proto/ov003/unk_ov003_02217908.h"
#include "proto/ov003/unk_ov003_02217be8.h"
#include "proto/main/unk_0204cc1c.h"



struct NNSG3dResMdl;









class FieldGroundBlock {
public:
    static void *operator new(size_t, void *p) { return p; }
    FieldGroundBlock();
    BOOL release();
    BOOL draw();
    BOOL updateAnims();
    BOOL init(TownBlockCell *o, s32 a, s32 b);

    /* 0x00 */ s32 acreId;
    /* 0x04 */ CachedModel model;
    /* 0xa0 */ s32 blockX;
    /* 0xa4 */ s32 blockZ;
    /* 0xa8 */ ModelAnim matAnims[2];
    /* 0xe8 */ s8 beachMatIdx;
};

class FieldGroundPiece {
public:
    FieldGroundPiece();
    ~FieldGroundPiece();
    BOOL release();
    BOOL draw();
    BOOL updateAnims();
    BOOL setup(VecFx32 *pos, s32 idx);
    BOOL isActive();
    s32 getBlockZ();
    s32 getBlockX();
    VecFx32 *getPos();
    s32 getCurveAngle();

    /* 0x00 */ CachedModel model;
    /* 0x9c */ VecFx32 position;
    /* 0xa8 */ s16 curveAngle;
    /* 0xac */ s32 blockX;
    /* 0xb0 */ s32 blockZ;
    /* 0xb4 */ ModelAnim matAnims[2];
};

class FieldGround : public GameProc {
public:
    /* 0x50 */ FieldGroundBlock *blocks;
    /* 0x54 */ FieldGroundPiece piece;
    /* 0x148 */ s32 numBlocksX;
    /* 0x14c */ s32 numBlocksZ;
    /* 0x150 */ FieldGroundBackdrop backdrop;
    /* 0x1f0 */ TexPatVramAnim riverPatAnim;
    /* 0x280 */ TexPatVramAnim beachPatAnim;
    /* 0x310 */ RainSndChannel envChannel;

    FieldGround();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual ~FieldGround();
    void updateAmbientSe();
};

extern "C" {
extern Camera *gCamera;
extern VecFx32Ctor gCameraLookAt;
extern Unk_0204e858_Grid *gSceneBlockMap;
extern s32 data_020c8cbc;
extern Mtx43 data_021f47e0;

void Camera_GetLookAtBlock(Camera *, s32 *, s32 *);
s32 Ground_GetSpecialPieceKind(s32, s32);
void Mtx43_SetTranslate(Mtx43 *m, s32 x, s32 y, s32 z);
void Mtx43_RotateX(Mtx43 *m, s32 a);
void Ground_SetWaveLevel(s32 v);
s32 FX_Div(s32 a, s32 b);
}

static inline BgModelCache *BgCache() { return BgModelCache_Get(); }



extern "C" {
DebugColor data_ov003_022354a4(31, 20, 20, 31);
DebugColor data_ov003_022354a8(20, 20, 31, 31);
DebugColor data_ov003_02235498(31, 31, 20, 31);
DebugColor data_ov003_022354a0(20, 31, 20, 31);
DebugColor data_ov003_0223549c(20, 31, 31, 31);
DebugColor data_ov003_022354ac(20, 24, 24, 31);
const s32 sFieldGroundPieceAcres[2] = {0x84, 0x85};
u8 data_ov003_02235490;
s32 data_ov003_02235494;
char data_ov003_022323f4[0xc] = "m_grd_riv";
char data_ov003_02232400[0x10] = "m_grd_sea085";
char *sWaterMatNames[2] = {data_ov003_022323f4, data_ov003_02232400};
ProcProfile sFieldGroundProfile = {(void *(*)())FieldGround_Create, 0xd, 0x9};
}


extern "C" FieldGround *FieldGround_Create() {
    return new FieldGround;
}

extern "C" void FieldGround_OnBeachMaterial(NNSG3dRS *rs) {
    if (data_ov003_02235494 == 0) {
        NNSG3dRenderObj *in = rs->pRenderObj;
        FieldGroundBlock *blk = (FieldGroundBlock *)in->ptrUser;
        u8 b = rs->c[1];
        if (blk != 0) {
            if (blk->beachMatIdx == b) {
                Ground_SetWaveLevel(FX_Div(rs->pMatAnmResult->transT + 0xda2, 0xda2));
                data_ov003_02235494 = 1;
            }
        }
    }
}

extern "C" void FieldGround_OnModelInit(NNSG3dRS *rs) {
    rs->cbVecFunc[4] = (void *)FieldGround_OnBeachMaterial;
    rs->cbVecTiming[4] = 2;
}

FieldGround::FieldGround() {
}

FieldGround::~FieldGround() {
}

BOOL FieldGround::onCreate() {
    backdrop.clear();
    backdrop.init();
    u8 *r6 = (u8 *)BgCache()->getGroundTex();
    u8 *r4 = (u8 *)BgCache()->getRiverPatTex();
    u8 *r0 = (u8 *)BgCache()->getRiverPatAnm();
    riverPatAnim.init(r6, "grd_riv.0", "grd_riv_pl", r4, r0, 0);
    r6 = (u8 *)BgCache()->getGroundTex();
    r4 = (u8 *)BgCache()->getBeBPatTex();
    r0 = (u8 *)BgCache()->getBeBPatAnm();
    beachPatAnim.init(r6, "grd_beB", "grd_beB_pl", r4, r0, 1);
    Unk_0204e858_Grid *g = gSceneBlockMap;
    numBlocksX = g->width;
    numBlocksZ = g->height;
    blocks = (FieldGroundBlock *)Heap_Alloc((Heap *)gBgHeap, numBlocksZ * (numBlocksX * sizeof(FieldGroundBlock)));
    {
        FieldGroundBlock *e = blocks;
        for (; e < blocks + numBlocksX * numBlocksZ; e++) {
            e = new (e) FieldGroundBlock;
        }
    }
    u32 by, bx;
    u32 tx, ty;
    for (by = 0; by < numBlocksZ; by++) {
        for (bx = 0; bx < numBlocksX; bx++) {
            for (ty = 0; ty < 16; ty++) {
                for (tx = 0; tx < 16; tx++) {
                    s32 o1, o2;
                    FieldUnit_FromBlockUnit(&o1, &o2, bx, by, tx, ty);
                    s32 t = Ground_GetSpecialPieceKind(o1, o2);
                    if (t != -1) {
                        VecFx32 v;
                        v.x = 0;
                        v.y = 0;
                        v.z = 0;
                        FieldPos_FromBlockUnitCenter(&v, bx, by, tx, ty);
                        piece.setup(&v, t);
                    }
                }
            }
        }
    }
    s32 idx = 0;
    for (bx = 0; bx < numBlocksZ; bx++) {
        for (by = 0; by < numBlocksX; by++) {
            TownBlockCell *c;
            if (by < g->width && bx < g->height && g->blocks != 0) {
                c = &g->blocks[bx * g->width + by];
            } else {
                c = 0;
            }
            (blocks + idx++)->init(c, by, bx);
        }
    }
    FieldGround_ResetEnvChannel(&envChannel);
    return TRUE;
}

BOOL FieldGround::onExecute() {
    FieldGroundBlock *e;
    s32 i, j;
    backdrop.followCamera();
    piece.updateAnims();
    e = blocks;
    i = 0;
    goto test0;
loop0:
    {
        j = 0;
        s32 *volatile pw = &numBlocksX;
        goto test1;
    loop1:
        e->updateAnims();
        e++;
        j++;
    test1:
        if (j < *pw) goto loop1;
    }
    i++;
test0:
    if (i < numBlocksZ) goto loop0;
    riverPatAnim.update();
    beachPatAnim.update();
    updateAmbientSe();
    data_021ce63c = 0;
    return TRUE;
}

static inline BOOL Unk_ov003_022181bc_Chk(s32 x, s32 y, s32 cx, s32 cy) {
    if (x >= cx - 1 && x <= cx + 1 && y >= cy - 2 && y <= cy + 1) return TRUE;
    return FALSE;
}

BOOL FieldGround::onDraw() {
    s32 a, cx, cy, b, cam_r, found;
    s32 x, y, idx;
    Camera *cam;
    data_ov003_02235494 = 0;
    ObjShadow_Update();
    CharaShadow_UpdateColor();
    a = 0;
    cx = 0;
    cy = 0;
    b = piece.getPos()->z;
    cam_r = 0;
    cam = gCamera;
    if (cam != 0) {
        cam_r = cam->getEyeCurveAngle();
        Camera_GetLookAtBlock(cam, &cx, &cy);
        a = WorldCurve_AngleToDistance(cam_r);
    }
    found = 0;
    for (y = 0; y < numBlocksZ; y++) {
        for (x = 0; x < numBlocksX; x++) {
            BOOL r = FALSE;
            r = Unk_ov003_022181bc_Chk(x, y, cx, cy);
            if (r) {
                if (x == piece.getBlockX() && y == piece.getBlockZ()) {
                    found = 1;
                }
            }
        }
    }
    if (found == 0) {
        FieldGround_DrawBackdrop(&backdrop.model);
    }
    if (found == 0) {
        idx = 0;
        for (y = 0; y < numBlocksZ; y++) {
            for (x = 0; x < numBlocksX; x++) {
                BOOL r = FALSE;
                r = Unk_ov003_022181bc_Chk(x, y, cx, cy);
                if (r) (blocks + idx)->draw();
                idx++;
            }
        }
    } else {
        if (piece.getCurveAngle() < cam_r) {
            if (b < a) {
                piece.draw();
                FieldGround_DrawBackdrop(&backdrop.model);
            } else {
                FieldGround_DrawBackdrop(&backdrop.model);
                piece.draw();
            }
            idx = 0;
            for (y = 0; y < numBlocksZ; y++) {
                for (x = 0; x < numBlocksX; x++) {
                    BOOL r = FALSE;
                    r = Unk_ov003_022181bc_Chk(x, y, cx, cy);
                    if (r) (blocks + idx)->draw();
                    idx++;
                }
            }
        } else {
            FieldGround_DrawBackdrop(&backdrop.model);
            idx = 0;
            for (y = 0; y < numBlocksZ; y++) {
                for (x = 0; x < numBlocksX; x++) {
                    BOOL r = FALSE;
                    r = Unk_ov003_022181bc_Chk(x, y, cx, cy);
                    if (r) (blocks + idx)->draw();
                    idx++;
                }
            }
            piece.draw();
        }
    }
    return TRUE;
}

BOOL FieldGround::onDelete() {
    s32 i, j;
    s32 idx;
    piece.release();
    idx = 0;
    for (i = 0; i < numBlocksZ; i++) {
        for (j = 0; j < numBlocksX; j++) {
            (blocks + idx++)->release();
        }
    }
    FieldGround_ReleaseBackdrop(&backdrop.model);
    FieldGround_ReleaseEnvChannel(&envChannel);
    return TRUE;
}

void FieldGround::updateAmbientSe() {
    data_ov003_02235490 = 0;
    if (gCamera != 0) {
        VecFx32Ctor v = gCameraLookAt;
        GroundSoundSrc q;
        FieldGround_FindSoundSrc(&q, &v);
        VecFx32 *r6 = FieldGround_GetSoundSrcPos(&q);
        if (r6 != 0) {
            u32 r4 = 0x80d;
            switch (FieldGround_GetSoundSrcKind(&q)) {
            case 0x11:
                r4 = 0x80b;
                break;
            case 0x12:
                data_ov003_02235490 = 1;
                break;
            case 5:
                r4 = 0x80e;
                break;
            case 0xf:
                r4 = 0x80c;
                break;
            }
            FieldGround_PlayEnvSe(&envChannel, r6, r4);
        }
        FieldGround_EndSoundSrc();
    }
}

extern "C" void FieldGround_SetWaterMatFlags(Model *o, s32 flag) {
    u32 i;
    u8 *base = (u8 *)o->resMdl;
    u8 *r4 = base + *(s32 *)(base + 8);
    for (i = 0; i < 2; i++) {
        u32 t = ((G3dResAccess *)(o->resMdl))->findMatIdx(sWaterMatNames[i]);
        if (t != (u32)-1) {
            u8 *r1 = r4 + 4;
            u32 hw = *(u16 *)(r4 + 0xa);
            u8 *r2 = r1 + hw;
            u32 st = *(u16 *)(r1 + hw);
            u8 *e = r4 + *(s32 *)(r2 + st * t + 4);
            if (e != 0) {
                *(u32 *)(e + 0x10) |= 0x800;
                if (flag != 0) {
                    *(u32 *)(e + 0xc) |= 0x800;
                } else {
                    *(u32 *)(e + 0xc) &= ~0x800;
                }
            }
        }
    }
}

FieldGroundPiece::FieldGroundPiece() {
    blockX = -1;
    blockZ = -1;
    position.x = 0;
    position.y = 0;
    position.z = 0;
}

FieldGroundPiece::~FieldGroundPiece() {
}

s32 FieldGroundPiece::getCurveAngle() {
    return curveAngle;
}

VecFx32 *FieldGroundPiece::getPos() {
    return &position;
}

s32 FieldGroundPiece::getBlockX() {
    return blockX;
}

s32 FieldGroundPiece::getBlockZ() {
    return blockZ;
}

BOOL FieldGroundPiece::isActive() {
    if (getBlockX() != -1 && getBlockZ() != -1) {
        return TRUE;
    }
    return FALSE;
}

BOOL FieldGroundPiece::setup(VecFx32 *pos, s32 idx) {
    if (isActive()) {
        return FALSE;
    }
    position.x = pos->x;
    position.y = pos->y;
    position.z = pos->z;
    BgAcreModel *e = BgCache()->getAcre(sFieldGroundPieceAcres[idx]);
    void *t = BgCache()->getGroundTex();
    NNSG3dResMdl *res = (NNSG3dResMdl *)e->mdl;
    model.setResourceAndBind(res, (NNSG3dResTex *)t);
    if (matAnims[0].allocMatAnm(res, gBgHeap)) {
        matAnims[0].init(BgCache()->getGroundMatAnm(), 0, 0x1000, 0);
        matAnims[0].addToRenderObj(model.getRenderObj());
    }
    if (matAnims[1].allocMatAnm(res, gBgHeap)) {
        matAnims[1].init(BgCache()->getGroundTexSrtAnm(), 0, 0x1000, 0);
        matAnims[1].addToRenderObj(model.getRenderObj());
    }
    VecFx32 tmp;
    curveAngle = WorldCurve_ToCurved(&tmp, &position);
    Mtx43_SetTranslate(&data_021f47e0, position.x, 0, 0);
    Mtx43_RotateX(&data_021f47e0, curveAngle);
    model.mtx = data_021f47e0;
    blockX = pos->x >> 17;
    blockZ = pos->z >> 17;
    return TRUE;
}

BOOL FieldGroundPiece::updateAnims() {
    if (isActive()) {
        ModelAnim *p = &matAnims[0];
        ModelAnim *e = &matAnims[2];
        for (; p < e; p++) {
            p->step();
            *(s32 *)p->anmObj = p->curFrame;
        }
        return TRUE;
    }
    return FALSE;
}

BOOL FieldGroundPiece::draw() {
    if (isActive()) {
        model.drawScaled(0);
        return TRUE;
    }
    return FALSE;
}

BOOL FieldGroundPiece::release() {
    if (isActive()) {
        model.clearResource();
        blockZ = -1;
        blockX = blockZ;
        return TRUE;
    }
    return FALSE;
}

FieldGroundBlock::FieldGroundBlock() {
    acreId = 0;
    blockX = 0;
    blockZ = 0;
}

BOOL FieldGroundBlock::init(TownBlockCell *o, s32 a, s32 b) {
    blockX = a;
    blockZ = b;
    acreId = ((MapBlockAcre *)o)->getAcreId();
    void *t = BgCache()->getGroundTex();
    BgAcreModel *p = o->bgModel;
    void *q = p->tex;
    if (q != 0) t = q;
    NNSG3dResMdl *res = (NNSG3dResMdl *)p->mdl;
    model.setResourceAndBind(res, (NNSG3dResTex *)t);
    if (matAnims[0].allocMatAnm(res, gBgHeap)) {
        matAnims[0].init(BgCache()->getGroundMatAnm(), 0, 0x1000, 0);
        matAnims[0].addToRenderObj(model.getRenderObj());
    }
    if (matAnims[1].allocMatAnm(res, gBgHeap)) {
        matAnims[1].init(BgCache()->getGroundTexSrtAnm(), 0, 0x1000, 0);
        matAnims[1].addToRenderObj(model.getRenderObj());
    }
    Mtx43_SetTranslate(&data_021f47e0, a * data_020c8cbc, 0, 0);
    s16 ang = b * WorldCurve_GetAngleScale();
    Mtx43_RotateX(&data_021f47e0, ang);
    model.mtx = data_021f47e0;
    if (Acre_GetAttr(acreId) & 8) {
        beachMatIdx = ((G3dResAccess *)res)->findMatIdx("m_grd_beA");
        if (beachMatIdx != -1) {
            model.setInitCallback(FieldGround_OnModelInit, this);
        }
    }
    FieldGround_SetWaterMatFlags(&model, 1);
    return TRUE;
}

BOOL FieldGroundBlock::updateAnims() {
    ModelAnim *e;
    ModelAnim *p;
    p = &matAnims[0];
    e = &matAnims[2];
    for (; p < e; p++) {
        p->step();
        *(s32 *)p->anmObj = p->curFrame;
    }
    return TRUE;
}

BOOL FieldGroundBlock::draw() {
    model.drawScaled(0);
    return TRUE;
}

BOOL FieldGroundBlock::release() {
    model.clearResource();
    return TRUE;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov003_02217be8) {
    HOST_OVERLAY_VAR(data_ov003_022354a4),
    HOST_OVERLAY_VAR(data_ov003_022354a8),
    HOST_OVERLAY_VAR(data_ov003_02235498),
    HOST_OVERLAY_VAR(data_ov003_022354a0),
    HOST_OVERLAY_VAR(data_ov003_0223549c),
    HOST_OVERLAY_VAR(data_ov003_022354ac),
    HOST_OVERLAY_VAR(data_ov003_02235490),
    HOST_OVERLAY_VAR(data_ov003_02235494),
    HOST_OVERLAY_VAR(data_ov003_022323f4),
    HOST_OVERLAY_VAR(data_ov003_02232400),
    HOST_OVERLAY_VAR(sWaterMatNames),
    HOST_OVERLAY_VAR(sFieldGroundProfile),
    HOST_OVERLAY_VARS_END
};
