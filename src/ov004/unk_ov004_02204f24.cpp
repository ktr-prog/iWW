#include "uptr.h"
#include "host_overlay_vars.h"
#include "proto/main/unk_020b4828.h"
#include "types.h"
#include "gfx/VecFx32.h"
#include "gfx/Mtx43.h"
#include "gfx/DebugColor.h"
#include "actor/ActorProfile.h"
#include "actor/ActorListNode.h"
#include "actor/CharacterListNode.h"
#include "room/FtrActorParts.h"
#include "gfx/AnimFrameCtrl.h"
#include "item/ItemId.h"
#include "game/LightLevel.h"
#include "gfx/G3dResAccess.h"
#include "room/FtrVisNodes.h"
#include "room/FtrSwitch.h"
#include "room/FtrClockHands.h"
#include "room/FtrAnimSet.h"
#include "room/FtrStackedSet.h"
#include "game/BoxCollider.h"
#include "room/FtrTileList.h"
#include "room/FtrGlowMat.h"
#include "room/FtrStackLink.h"
#include "room/FtrTopItem.h"
#include "sys/ProcBase.h"
#include "gfx/ModelAnim.h"
#include "room/FtrCollider.h"
#include "room/FtrGlowMatSet.h"
#include "room/FtrTopItems.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "gfx/ModelResource.h"
#include "room/FtrModelRes.h"
#include "talk/MsgRequest.h"
#include "talk/TalkMsgRequest.h"
#include "game/CollisionVec2.h"
#include "game/CollisionEdge.h"

struct FxVec3 : VecFx32Copy {
    FxVec3() {}
    constexpr FxVec3(s32 a, s32 b, s32 c) : VecFx32Copy(a, b, c) {}
};

#include "room/FtrModelAnim.h"
#include "gfx/NNSG3dRS.h"

#include "room/FtrActor.h"
#include "game/TouchPicker.h"
#include "gfx/AnimModel.h"
#include "gfx/Model.h"
#include "gfx/ModelSlotPool.h"
#include "gfx/TwoLayerAnimModel.h"
#include "room/FtrActorTable.h"
#include "save/TownId.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/autoload_2/unk_02101048.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/itcm/unk_01ffcfc0.h"
#include "proto/main/unk_02002b1c.h"
#include "proto/main/unk_020514a4.h"
#include "proto/main/unk_02052b50.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_020815f8.h"
#include "proto/main/unk_02090268.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_0209c08c.h"
#include "proto/ov004/unk_ov004_02204f24.h"
#include "proto/ov004/unk_ov004_0222a500.h"
#include "proto/ov004/unk_ov004_0222bed0.h"
#include "proto/ov004/unk_ov004_02233074.h"
#include "proto/ov004/unk_ov004_02235fd0.h"
#include "player/PlayerData.h"
#include "player/PlayerId.h"
#include "actor/NpcActor.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/main/unk_0204cc1c.h"

#ifndef HOST64
#define FTR_AT(m, o) static_assert(__builtin_offsetof(FtrActor, m) == o, "FtrActor::" #m)
FTR_AT(modelSlot, 0x12e);
FTR_AT(modelOffset, 0x140);
FTR_AT(drawScale, 0x14c);
FTR_AT(targetPos, 0x16c);
FTR_AT(stackLink, 0x178);
FTR_AT(topItems, 0x188);
FTR_AT(topItemCylinders, 0x1cc);
FTR_AT(moveFlag, 0x24c);
FTR_AT(worldMtx, 0x250);
FTR_AT(ftrIndex, 0x280);
FTR_AT(touchBox, 0x288);
FTR_AT(baseAct, 0x530);
FTR_AT(model, 0x534);
FTR_AT(collider, 0x628);
FTR_AT(modelRes, 0x6c8);
FTR_AT(switchState, 0x73c);
FTR_AT(clockHands, 0x73e);
FTR_AT(lampMat, 0x744);
FTR_AT(visNodes, 0x760);
FTR_AT(spawnMode, 0x768);
FTR_AT(kind, 0x77c);
FTR_AT(lightKind, 0x790);
FTR_AT(soundEmitter, 0x794);
FTR_AT(centerPos, 0x7b4);
FTR_AT(anims, 0x7c0);
static_assert(sizeof(FtrActor) == 0x840, "FtrActor size");
#undef FTR_AT
#endif



struct Unk_ov004_02207ac4_Tmp {
    u16 v;
    u16 pad;
    Unk_ov004_02207ac4_Tmp() {}
    ~Unk_ov004_02207ac4_Tmp() {}
};

struct FtrSpawnArg {
    u32 tileX : 4;
    u32 tileZ : 4;
    u32 ftrIndex : 16;
    u32 dir : 2;
    u32 mode : 2;
    u32 layer : 1;
};

struct FtrCharIdBits {
    u16 tableIndex : 9;
    u16 sceneId : 7;
    u16 tileX : 4;
    u16 tileZ : 4;
    u16 layer : 1;
    u16 tileSceneId : 6;
    u16 pad : 1;
};

struct FtrSpawnArgBuf {
    u32 tileX : 4;
    u32 tileZ : 4;
    u32 ftrIndex : 16;
    u32 dir : 2;
    u32 mode : 2;
    u32 layer : 1;
    u32 w1;
};

typedef BOOL (FtrActor::*Unk_ov004_0224882c_Fn)();
struct FtrCenterPosBuf {
    VecFx32 pos;
    s32 pad;
};

static inline BOOL Unk_ov004_02205820_Is3d(u16 v) {
    if (v == 0x3d) return TRUE;
    return FALSE;
}


struct WallEdge;
class ModelSlot;
class TexVramSlot;

struct FtrG3dGlbView {
    /* 0x00 */ u8 pad_00[0x98];
    /* 0x98 */ u32 prmMatColor1;
    /* 0x9c */ u8 pad_9c[0xc];
    /* 0xa8 */ u32 lightColor[4];
};

extern "C" {
BOOL TalkRequest_SetTargetDone(void *p);
s32 FX_Div(s32 a, s32 b);
s32 FX_Sqrt(s32 a);
s32 func_01ffcb0c(s32 a, s32 b);
s16 Math_Atan2(s32 x, s32 y);
BOOL Math_StepS32(s32 *p, s32 target, s32 step);
BOOL Math_StepAngle(s16 *p, s16 target, s16 step);
u16 Item_MakeFurniture(s32 a, s32 b);
BOOL Item_IsFurnitureOrF031(u16 *p);
BOOL Item_IsNormalItem(u16 *p);
BOOL Item_IsFurniture(u16 *p);
s32 Item_GetFurnitureIndex(u16 *p);
u32 ItemInfo_GetIndoorUnk1(u16 *p);
void NNSi_G3dModifyMatFlag(void *res, BOOL on, u32 mask);
void NNS_G3dMdlSetMdlEmi(void *res, u32 i, u32 v);
void *NNS_G3dGetTex(void *p);
u8 *NNS_G3dGetMdlSet(u8 *p);
BOOL NNS_G3dBindMdlTex(void *mdl, void *tex);
BOOL NNS_G3dBindMdlPltt(void *mdl, void *tex);
BOOL NNS_FndMountArchive(NNSFndArchive *arc, const char *name, void *narc);
BOOL NNS_FndUnmountArchive(NNSFndArchive *arc);
u8 *func_021065dc(u8 *p);
u8 *func_021065f8(u8 *p, u32 i);
u8 *func_02106618(u8 *p);
u8 *func_02106634(u8 *p, u32 i);
u8 *func_02106788(u8 *p);
u8 *func_021067a4(u8 *p, u32 i);
u8 *func_02106654(u8 *p);
u8 *func_02106670(u8 *p, u32 i);
u8 *func_02106690(u8 *p);
u8 *func_021066ac(u8 *p, u32 i);
void MTX_Inverse43(const Mtx43 *src, Mtx43 *dst);
void MTX_MultVec43(const VecFx32 *src, const Mtx43 *m, VecFx32 *dst);
void Mtx43_Translate(Mtx43 *m, s32 x, s32 y, s32 z);
void Mtx43_SetTranslate(Mtx43 *m, s32 x, s32 y, s32 z);
void Mtx43_RotateX(Mtx43 *m, s32 angle);
void Mtx43_RotateY(Mtx43 *m, s32 angle);
void Mtx43_SetRotY(Mtx43 *m, s32 angle);
void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
void WallEdge_GetMidpoint(CollisionVec2 *out, CollisionEdge *e);
BOOL Gfx3d_LoadTexAndPltt(void *tex, TexVramSlot *slot);
void *Gfx3d_CopyTex(void *tex, void *heap);
void MI_CpuCopy8(const void *src, void *dst, u32 n);
s32 Scene_GetCurrent();
BOOL Scene_InHouseRoom(void);
BOOL Scene_InUnk6To8(void);
BOOL SceneId_IsHouseRoom(s32 scene);
BOOL SceneId_IsVillagerHouse(u32 scene);
s32 Ground_CanPlaceItem(s32 x, s32 y);
s32 Ground_GetExitAtPos(VecFx32 *p);
u16 GroundAttr_GetDragSe(s32 i);
void LightSwitch_SetOff(s32 i, u32 v);
void LightSwitch_SetOn(s32 i, u32 a, u32 b);
void JointCb_RotateClockHourHand(NNSG3dRS *rs);
void JointCb_RotateClockMinuteHand(NNSG3dRS *rs);
BOOL BoxCollider_Register(BoxCollider *c, s32 a, s32 b, s32 cc, VecFx32 *pos, s16 angle, VecFx32 *scale);
BOOL BoxCollider_Unregister(BoxCollider *c);
s32 Vec_DistXZ(VecFx32 *a, VecFx32 *b);
s32 Vec_Distance(VecFx32 *a, VecFx32 *b);
s32 Vec_NotEqual(VecFx32 *a, VecFx32 *b);
void Vec_RotateY(VecFx32 *v, s32 angle);
s32 Vec_SafeNormalize(VecFx32 *v);
void Vec_Sub(VecFx32 *out, VecFx32 *a, VecFx32 *b);
extern BlockMap *gSceneBlockMap;
extern Mtx43 data_021f47e0;
extern FtrG3dGlbView data_027e00c8;
extern const s16 data_02135f44[];
extern const s32 data_020c8cbc;
extern u8 gFieldSceneKind;
extern VecFx32 gCameraEye;
extern VecFx32 gCameraLookAt;
}

static inline BOOL BoxCollider_UpdateShape(BoxCollider *c, VecFx32 *pos, s32 angle, VecFx32 *scale) {
    return static_cast<BoxColliderShape *>(c)->updateTransform(pos, angle, scale);
}

extern "C" {
void FtrVisNodes_Destruct(void *);
void FtrVisNodes_Construct(void *);
u16 FtrGlowMat_GetBaseEmission();
BOOL FtrStack_CalcRelPlacement(s32 *idx, VecFx32 *pos, s16 *ang, s32 x, s32 a, s16 b);
void FtrActor_GetItemId(u16 *out, FtrActor *o);
s32 FtrActor_PredIsGyroid(FtrActor *p);
s32 FtrActor_PredIsSeatOrBed(FtrActor *p);
s32 FtrActor_PredIsStereo(FtrActor *p);
s32 FtrActor_PredIsLightSource(FtrActor *p);
void FtrActor_SpawnActorC0(VecFx32 *a, u32 x);
s32 FtrActor_GetDragSe(void);
s32 FtrActor_TestCurSceneUnk();
s32 FtrActor_TestSceneUnk(s32 a);
void FtrActor_MakeItemForAngle(u16 *out, FtrActor *obj, s32 ang);
u32 FtrActor_AngleToDir(s32 v);
void FtrActor_SetInitialAct(FtrActor *self);
void FtrActor_UpdateTopItemBoxes(FtrActor *self);
void FtrActor_UpdateBox(FtrActor *self);
void FtrActor_ReleaseCollider(FtrActor *self);
void FtrActor_InitCollider(FtrActor *self);
void FtrActor_GetBoxSize(FtrActor *self, VecFx32 *out);
void FtrActor_UpdateMtx(FtrActor *self);
void FtrActor_CalcWorldMtx(FtrActor *self, VecFx32 *a, s32 b);
u8 FtrActor_GetLayer(FtrActor *self);
BOOL FtrActor_RequestToggle(FtrActor *self);
s32 FtrActor_GetFtrIndex(FtrActor *self);
FtrActor *FtrActor_GetParent(FtrActor *self);
BOOL FtrActor_IsPosClearOfCharacters(VecFx32 *pos, s32 a, s32 b, s32 c, s32 d);
BOOL FtrActor_IsWithinDist(VecFx32 *pos, s32 a, VecFx32 *p, s32 b);
BOOL FtrActor_TestPlayerUnk();
void FtrActor_GetCenter(FtrActor *self, VecFx32 *out);
void FtrActor_GetCorner(FtrActor *self, VecFx32 *out, s32 i);
void FtrActor_LocalToWorld(FtrActor *self, VecFx32 *out, VecFx32 *src);
ModelSlot *FtrActor_GetHeap(FtrActor *self);
BOOL FtrActor_StepAnims(FtrActor *self);
void FtrActor_PlayAnimsFromLastFrame(FtrActor *self, u32 a, s32 b, s32 c);
BOOL FtrActor_IsStereo(FtrActor *p);
BOOL FtrActor_IsLightSource(FtrActor *p);
u32 FtrActor_GetArgMode(u32 v);
u32 FtrActor_GetArgFtrIndex(u32 v);
u32 FtrActor_MakeSpawnArg(u32 a, u32 b, u32 c, u32 d, u8 f, u32 e);
void FtrActor_TurnOnRoomLight(u32 a);
u32 FtrActor_IsLightKind1(u32 a);
void FtrActor_SetModelCallbacks(NNSG3dRS *o);
void FtrActor_NodeCallback(NNSG3dRS *o);
void FtrActor_NodeDescCallbackB(NNSG3dRS *self);
void FtrActor_NodeDescCallbackA(NNSG3dRS *self);
void FtrActor_MatCallback(NNSG3dRS *self);
void *FtrActor_Create();
}

static inline BOOL Unk_ov004_0220607c_IsEmpty(u16 *p) {
    BOOL r;
    if (Item_IsFurniture(p)) {
        u16 t = 0xfff1;
        r = (Item_GetFurnitureIndex(p) == Item_GetFurnitureIndex(&t)) ? TRUE : FALSE;
    } else {
        r = (*p == 0xfff1) ? TRUE : FALSE;
    }
    return r;
}

static inline BOOL Unk_ov004_02206a44_IsInvalid(u16 *a) {
    if (Item_IsFurniture(a)) {
        u16 t = 0xfff1;
        if (Item_GetFurnitureIndex(a) == Item_GetFurnitureIndex(&t)) {
            return TRUE;
        }
        return FALSE;
    }
    if (*a == 0xfff1) {
        return TRUE;
    }
    return FALSE;
}

static inline BOOL Unk_ov004_02206a44_Same(u16 *a, u16 *b) {
    if (Item_IsFurniture(a)) {
        if (Item_GetFurnitureIndex(a) == Item_GetFurnitureIndex(b)) {
            return TRUE;
        }
        return FALSE;
    }
    if (*a == *b) {
        return TRUE;
    }
    return FALSE;
}

static inline BOOL Unk_ov004_02207650_IsOne(u8 v) {
    return v == 1 ? TRUE : FALSE;
}

static inline BOOL Unk_ov004_02207650_InRange(u16 *p) {
    BOOL r = FALSE;
    u32 v = *p;
    if (v >= 0x1144 && v <= 0x1187) {
        r = TRUE;
    }
    return r;
}

#define UNK_OV004_022072B4_FAIL()   \
    {                               \
        writeTiles(0, 0, 0, 0);     \
        c2.release();               \
        c1.release();               \
        return FALSE;               \
    }



extern "C" {
extern const u32 sFtrInitialActByMode[3];
extern const u8 sFtrPolygonIds[0x1c];
extern u16 gFtrSoundNone;
extern char data_ov004_022486fc[2];
extern char data_ov004_02248700[3];
extern char data_ov004_02248704[3];
extern char data_ov004_02248708[3];
extern char sFtrModelName[15];
extern char *sFtrModelNamePtr;
extern char data_ov004_02248710[5];
extern char data_ov004_02248718[6];
extern char data_ov004_02248720[6];
extern char *sFtrGlowMatNames[3];
extern char *sFtrVisNodeNames[4];
extern ActorProfile sFtrActorProfile;
extern s16 sFtrPreviewYaw;
extern s16 sFtrPreviewPitch;
extern char sFtrArcPathBuf[0x28];
extern char sFtrTexPathBuf[0x28];
extern DebugColor data_ov004_0224f60c;
extern DebugColor data_ov004_0224f62c;
extern DebugColor data_ov004_0224f63c;
extern DebugColor data_ov004_0224f608;
extern DebugColor data_ov004_0224f61c;
extern DebugColor data_ov004_0224f618;
extern FxVec3 data_ov004_0224f88c[4];
extern FxVec3 data_ov004_0224f8bc[4];
extern FxVec3 data_ov004_0224f8ec[4];
extern FxVec3 *sFtrFootprintCorners[3];
}


extern "C" void *FtrActor_Create() {
    return new FtrActor;
}

void *FtrActor::operator new(size_t size) {
    void *p = FtrActorHeap_GetInstance()->alloc();
    if (p == 0) {
        return 0;
    }
    memset(p, 0, size);
    return p;
}

void FtrActor::operator delete(void *p) {
    FtrActorHeap_GetInstance()->free(p);
}

extern "C" void FtrActor_MatCallback(NNSG3dRS *self) {
    FtrActor *t = (FtrActor *)self->pRenderObj->ptrUser;
    if (t != 0) {
        t->onMatCalc(self->c[1], self);
    }
}

extern "C" void FtrActor_NodeDescCallbackA(NNSG3dRS *self) {
    FtrActor *t = (FtrActor *)self->pRenderObj->ptrUser;
    if (t != 0) {
        t->onJointCalcPre(self->c[1], self);
    }
    self->cbVecFunc[6] = (void *)FtrActor_NodeDescCallbackB;
    self->cbVecTiming[6] = 2;
}

extern "C" void FtrActor_NodeDescCallbackB(NNSG3dRS *self) {
    FtrActor *t = (FtrActor *)self->pRenderObj->ptrUser;
    if (t != 0) {
        t->onJointCalcPost(self->c[1], self);
    }
    self->cbVecFunc[6] = (void *)FtrActor_NodeDescCallbackA;
    self->cbVecTiming[6] = 1;
}

extern "C" void FtrActor_NodeCallback(NNSG3dRS *o) {
    FtrActor *t = (FtrActor *)o->pRenderObj->ptrUser;
    if (t != NULL) {
        t->onNodeVisCalc(o->c[1], o);
    }
}

extern "C" void FtrActor_SetModelCallbacks(NNSG3dRS *o) {
    o->cbVecFunc[4] = (void *)FtrActor_MatCallback;
    o->cbVecTiming[4] = 2;
    o->cbVecFunc[2] = (void *)FtrActor_NodeCallback;
    o->cbVecTiming[2] = 2;
    o->cbVecFunc[6] = (void *)FtrActor_NodeDescCallbackA;
    o->cbVecTiming[6] = 1;
}

extern "C" u32 FtrActor_IsLightKind1(u32 a) {
    if (a == 1) {
        return 1;
    }
    return 0;
}

extern "C" void FtrActor_TurnOnRoomLight(u32 a) {
    u32 t = FtrActor_IsLightKind1(a);
    if (a == 2) {
        LightSwitch_SetOn(0, 8, t);
    } else {
        LightSwitch_SetOn(0, 0xc, t);
    }
    FtrSync_SetRoomLight(Scene_GetCurrent(), 1);
}

extern "C" u32 FtrActor_MakeSpawnArg(u32 a, u32 b, u32 c, u32 d, u8 f, u32 e) {
    FtrSpawnArgBuf l;
    l.tileX = a;
    l.tileZ = b;
    l.ftrIndex = c;
    l.dir = d;
    l.mode = e;
    l.layer = f;
    l.w1 = (l.w1 & ~0x1f) | 1;
    return *(u32 *)&l;
}

extern "C" u32 FtrActor_GetArgFtrIndex(u32 v) {
    FtrSpawnArgBuf l;
    *(u32 *)&l = v;
    return l.ftrIndex;
}

extern "C" u32 FtrActor_GetArgMode(u32 v) {
    FtrSpawnArgBuf l;
    *(u32 *)&l = v;
    return l.mode;
}

extern "C" BOOL FtrActor_IsLightSource(FtrActor *p) {
    if (p != NULL) {
        if (FtrInfo_GetIndoorFlagPair(FtrActor_GetFtrIndex(p)) != 0) {
            if (p->isPreview() == 0) {
                return TRUE;
            }
        }
        return FALSE;
    }
    return FALSE;
}

extern "C" BOOL FtrActor_IsStereo(FtrActor *p) {
    if (p != NULL) {
        u32 v = p->profile;
        BOOL r;
        if (v == 0x3a) r = TRUE; else r = FALSE;
        if (r != 0) return TRUE;
        return FALSE;
    }
    return FALSE;
}

BOOL FtrActor::isStereoOn() {
    if (FtrActor_IsStereo(this)) {
        return switchState.isOn();
    }
    return FALSE;
}

BOOL FtrActor::isTvOn() {
    u32 v = profile;
    BOOL a;
    BOOL b;
    BOOL r;
    if (v == 0x3b) a = TRUE; else a = FALSE;
    if (a != 0 || ((v == 0x3c ? (b = TRUE) : (b = FALSE)), b != 0)) {
        if (switchState.isOn()) r = TRUE; else r = FALSE;
    } else {
        r = FALSE;
    }
    return r;
}

BOOL FtrActor::isSeatOrBed() {
    BOOL r = TRUE;
    u32 v = profile;
    BOOL a;
    if (v == 0x36) a = TRUE; else a = FALSE;
    if (a == 0) {
        BOOL b;
        if (v == 0x37) b = TRUE; else b = FALSE;
        if (b == 0) r = FALSE;
    }
    if (r != 0) return TRUE;
    return FALSE;
}

BOOL FtrActor::isGyroid() {
    if (kind == 0x18) {
        return TRUE;
    }
    return FALSE;
}

BOOL FtrActor::isCabinClock() {
    if (isAct(0) == 0) {
        if (isAct(5) == 0) {
            if (kind == 0x10) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

BOOL FtrActor::isSoundingClock() {
    if (isAct(0) == 0) {
        if (isAct(5) == 0) {
            switch (kind) {
            case 0x10:
                return TRUE;
            case 0x11:
            case 0x2b:
                u32 c = FtrSound_GetSe3(FtrActor_GetFtrIndex(this));
                if (c != gFtrSoundNone) {
                    return TRUE;
                }
                return FALSE;
            }
        }
    }
    return FALSE;
}

BOOL FtrActor::initModel() {
    return TRUE;
}

FtrActor::FtrActor() {
    ModelSlotHandle_Init(&modelSlot);
    stackLink.clear();
    FtrMoveFlag_Init(&moveFlag);
    switchState.clear();
    clockHands.clear();
    FtrVisNodes_Construct(&visNodes);
    soundEmitter.resetAttached();
}

FtrActor::~FtrActor() {
    FtrSoundEmitter_Destroy();
    FtrVisNodes_Destruct(&visNodes);
    FtrMoveFlag_Destroy(&moveFlag);
    ModelSlotHandle_Destroy(&modelSlot);
}

BOOL FtrActor::onCreate() {
    FtrSpawnArgBuf l;
    *(u32 *)&l = param;
    u32 t = l.mode;
    spawnMode = t;
    FtrActorTable_GetInstance()->add(this);
    ModelSlot *r = sFtrMgrPool.acquire(&modelSlot);
    setupFromSpawnArg();
    if (getCharId() == 0) {
        setCharId(makeCharId(0, 0));
    }
    if (spawnMode == 0) {
        modelRes.loadSync(r, ftrIndex, needsTexCopy());
        void *p = modelRes.getModel();
        model.setResource((NNSG3dResMdl *)(p), (NNSG3dResTex *)(modelRes.getTexture()));
        isInitializing = 1;
        setupModel();
        if (initModel()) {
            isInitializing = 0;
            return 1;
        }
        return 0;
    } else {
        if (modelRes.loadAsync(r, ftrIndex, needsTexCopy()) != 0) {
            void *p = modelRes.getModel();
            model.setResource((NNSG3dResMdl *)(p), (NNSG3dResTex *)(modelRes.getTexture()));
            isInitializing = 1;
            setupModel();
            if (initModel()) {
                isInitializing = 0;
                return 1;
            }
            return 0;
        }
        return -1;
    }
}

void FtrActor::postCreate(s32 a) {
    if (a == 2) {
        initLamp();
    }
    Character::postCreate(a);
}

BOOL FtrActor::onExecute() {
    FtrCenterPosBuf v;
    if (isPreview() == 0) {
        soundEmitter.attach();
        FtrActor_GetCenter(this, &v.pos);
        centerPos.x = v.pos.x;
        centerPos.y = v.pos.y;
        centerPos.z = v.pos.z;
    }
    execAct();
    FtrActor_UpdateBox(this);
    FtrActor_UpdateMtx(this);
    if (isAct(0) == 0 && isAct(5) == 0) {
        if (kind == 0) {
            hasIndoorFlag6();
        }
        updateActive();
    } else {
        updateAppearRemove();
        if (switchState.isChanging()) {
            switchState.toggle(0);
        }
    }
    if (isPreview() == 0) {
        updateLamp();
        switchState.commit(this);
        FtrActor_UpdateTopItemBoxes(this);
    }
    return TRUE;
}

BOOL FtrActor::updateActive() { return TRUE; }

BOOL FtrActor::updateAppearRemove() { return TRUE; }

BOOL FtrActor::preDraw() {
    if (Actor::preDraw() == 0) {
        return FALSE;
    }
    if (isVisible() == 0) {
        return FALSE;
    }
    if (drawScale != 0 || drawScaleY != 0 || drawScaleZ != 0) {
        u32 saved[4];
        u32 i;
        if (isPreview()) {
            for (i = 0; i < 4; i++) {
                saved[i] = data_027e00c8.lightColor[i];
                data_027e00c8.lightColor[i] = (i << 30) | 0x7fff;
            }
        }
        model.drawAnimated(&drawScale);
        if (isPreview()) {
            for (i = 0; i < 4; i++) {
                data_027e00c8.lightColor[i] = saved[i];
            }
        }
    }
    if (isPreview() == 0) {
        topItems.drawAll(this);
    }
    return TRUE;
}

BOOL FtrActor::preDelete() {
    if (Character::preDelete()) {
        return TRUE;
    }
    return FALSE;
}

BOOL FtrActor::postDelete(s32 a) {
    if (a == 2) {
        soundEmitter.release();
        releaseRoomLight();
        FtrActor_ReleaseCollider(this);
        if (isRemoving() == 0) {
            if (isHidden() == 0) {
                switchState.saveToMap(this);
            }
        }
        modelRes.release();
        sFtrMgrPool.release(&modelSlot);
        if (isRemoving()) {
            s32 x, y;
            findOwnTile(&x, &y, 0, 0);
            u32 r = Scene_GetCurrent();
            if (FtrMgr_IsSaleMode() && !SceneId_IsVillagerHouse(r) && !SceneId_IsHouseRoom(r)) {
                BlockMap *g = gSceneBlockMap;
                clearTiles(0, 0);
                if (g) {
                    u16 v = 0x1547;
                    BlockMap_SetItemAtUnit(g, &v, x, y, 0);
                }
            } else {
                clearTiles(1, 0);
            }
            spawnActorC0AtCenter();
        }
        FtrActorTable_GetInstance()->remove(this);
    }
    return Actor::postDelete(a);
}

BOOL FtrActor::needsTexCopy() { return FALSE; }

BOOL FtrActor::isVisible() { return TRUE; }

void FtrActor::onRemove() {}

void FtrActor::onMoveStart(BOOL isPush) {}

void FtrActor::onRotateStart(BOOL negative) {}

void FtrActor::onRotateUpdate(BOOL negative) {}

DebugColor data_ov004_0224f60c(31, 20, 20, 31);
DebugColor data_ov004_0224f62c(20, 20, 31, 31);
DebugColor data_ov004_0224f63c(31, 31, 20, 31);
DebugColor data_ov004_0224f608(20, 31, 20, 31);
DebugColor data_ov004_0224f61c(20, 31, 31, 31);
DebugColor data_ov004_0224f618(20, 24, 24, 31);
ActorProfile sFtrActorProfile = {(void *(*)())FtrActor_Create, 0x2e, 0x35, 0, 0xc8000, 0x12c000, 0x258000};
FxVec3 data_ov004_0224f88c[4] = {FxVec3(-0x1000, 0, -0x1000), FxVec3(-0x1000, 0, 0x1000),
                                       FxVec3(0x1000, 0, 0x1000), FxVec3(0x1000, 0, -0x1000)};
FxVec3 data_ov004_0224f8bc[4] = {FxVec3(-0x1000, 0, -0x1000), FxVec3(-0x1000, 0, 0x1000),
                                       FxVec3(0x3000, 0, 0x1000), FxVec3(0x3000, 0, -0x1000)};
FxVec3 data_ov004_0224f8ec[4] = {FxVec3(-0x2000, 0, -0x2000), FxVec3(-0x2000, 0, 0x2000),
                                       FxVec3(0x2000, 0, 0x2000), FxVec3(0x2000, 0, -0x2000)};
s16 sFtrPreviewYaw;
FxVec3 *sFtrFootprintCorners[3] = {data_ov004_0224f88c, data_ov004_0224f8bc, data_ov004_0224f8ec};
u16 gFtrSoundNone = 0xffff;

FxVec3 FtrActor_getInteractionPos_v;
u8 FtrActor_getInteractionPos_v_init;
VecFx32 *FtrActor::getInteractionPos() {
    if (!FtrActor_getInteractionPos_v_init) {
        HOST_STATIC_CONSTRUCT(FtrActor_getInteractionPos_v);
        FtrActor_getInteractionPos_v_init = 1;
    }
    FtrActor_getInteractionPos_v.x = position.x;
    FtrActor_getInteractionPos_v.y = position.y;
    FtrActor_getInteractionPos_v.z = position.z;
    Actor *o = (Actor *)PlayerActor_GetActor(4);
    if (o) {
        s32 i = (u16)o->rotY >> 4;
        s32 k = i * 2;
        FtrActor_getInteractionPos_v.x = o->position.x + data_02135f44[k];
        FtrActor_getInteractionPos_v.y = o->position.y;
        FtrActor_getInteractionPos_v.z = o->position.z + data_02135f44[k + 1];
    }
    return (VecFx32 *)&FtrActor_getInteractionPos_v;
}

u8 FtrActor::getActAid() {
    return actAid;
}

u32 FtrActor::hasIndoorFlag6() {
    return FtrInfo_TestIndoorFlag6(ftrIndex);
}

BOOL FtrActor::playSound0() {
    if (isPreview() == 0) {
        u32 t = FtrSound_GetSe0(ftrIndex);
        if (t != gFtrSoundNone) {
            soundEmitter.playOnce(t, &centerPos);
            return TRUE;
        }
    }
    return FALSE;
}

BOOL FtrActor::playSound1() {
    if (isPreview() == 0) {
        u32 t = FtrSound_GetSe1(ftrIndex);
        if (t != gFtrSoundNone) {
            soundEmitter.play(t, &centerPos);
            return TRUE;
        }
    }
    return FALSE;
}

BOOL FtrActor::playSound2() {
    if (isPreview() == 0) {
        u32 t = FtrSound_GetSe2(ftrIndex);
        if (t != gFtrSoundNone) {
            soundEmitter.play(t, &centerPos);
            return TRUE;
        }
    }
    return FALSE;
}

BOOL FtrActor::playSound3() {
    if (isPreview() == 0) {
        u32 t = FtrSound_GetSe3(ftrIndex);
        if (t != gFtrSoundNone) {
            soundEmitter.play(t, &centerPos);
            return TRUE;
        }
    }
    return FALSE;
}

u16 FtrActor::getAnimFrameCount(s32 a) {
    u32 i = a & 1;
    if (modelRes.getAnimSet()->getBca(i)) {
        return modelRes.getAnimSet()->getBca(i)->numFrame;
    }
    if (modelRes.getAnimSet()->getBma(i)) {
        return modelRes.getAnimSet()->getBma(i)->numFrame;
    }
    if (modelRes.getAnimSet()->getBta(i)) {
        return modelRes.getAnimSet()->getBta(i)->numFrame;
    }
    if (modelRes.getAnimSet()->getBtp(i)) {
        return modelRes.getAnimSet()->getBtp(i)->numFrame;
    }
    if (modelRes.getAnimSet()->getBva(i)) {
        return modelRes.getAnimSet()->getBva(i)->numFrame;
    }
    return 0;
}

void FtrActor::initAnims(s32 a, s32 b, s32 c, s32 d) {
    ModelSlot *m = FtrActor_GetHeap(this);
    u32 i = a & 1;
    if (modelRes.getAnimSet()->getBva(i)) {
        if (anims[3].allocJointAnm(model.resMdl, m->getHeap())) {
            anims[3].init(modelRes.getAnimSet()->getBva(i), b, c, d);
            anims[3].addToRenderObj(model.getRenderObj());
        }
    }
    if (modelRes.getAnimSet()->getBma(i)) {
        if (anims[0].allocMatAnm(model.resMdl, m->getHeap())) {
            anims[0].init(modelRes.getAnimSet()->getBma(i), b, c, d);
            anims[0].addToRenderObj(model.getRenderObj());
        }
    }
    if (modelRes.getAnimSet()->getBta(i)) {
        if (anims[1].allocMatAnm(model.resMdl, m->getHeap())) {
            anims[1].init(modelRes.getAnimSet()->getBta(i), b, c, d);
            anims[1].addToRenderObj(model.getRenderObj());
        }
    }
    if (modelRes.getAnimSet()->getBtp(i)) {
        if (anims[2].allocMatAnm(model.resMdl, m->getHeap())) {
            NNSG3dResAnmCommon *rec = modelRes.getAnimSet()->getBtp(i);
            anims[2].initWithTex(rec, modelRes.getTexture(), b, c, d);
            anims[2].addToRenderObj(model.getRenderObj());
        }
    }
    if (modelRes.getAnimSet()->getBca(i)) {
        if (model.allocAnmObj(m->getHeap())) {
            model.initAnim(modelRes.getAnimSet()->getBca(i), b, c, d, 0);
            model.attachAnim();
        }
    }
}

void FtrActor::playAnim(s32 a, s32 b, s32 c, u32 d) {
    u32 i = a & 1;
    if (modelRes.getAnimSet()->getBva(i)) {
        NNSG3dResAnmCommon *rec = modelRes.getAnimSet()->getBva(i);
        u32 v;
        if (d == 0xffff) {
            v = ((u32)anims[3].curFrame << 4) >> 16;
        } else {
            u32 n = rec->numFrame;
            v = (u16)(d >= n ? n - 1 : d);
        }
        anims[3].replace(model.getRenderObj(), rec, b, c, v);
    }
    if (modelRes.getAnimSet()->getBma(i)) {
        NNSG3dResAnmCommon *rec = modelRes.getAnimSet()->getBma(i);
        u32 v;
        if (d == 0xffff) {
            v = ((u32)anims[0].curFrame << 4) >> 16;
        } else {
            u32 n = rec->numFrame;
            v = (u16)(d >= n ? n - 1 : d);
        }
        anims[0].replace(model.getRenderObj(), rec, b, c, v);
    }
    if (modelRes.getAnimSet()->getBta(i)) {
        NNSG3dResAnmCommon *rec = modelRes.getAnimSet()->getBta(i);
        u32 v;
        if (d == 0xffff) {
            v = ((u32)anims[1].curFrame << 4) >> 16;
        } else {
            u32 n = rec->numFrame;
            v = (u16)(d >= n ? n - 1 : d);
        }
        anims[1].replace(model.getRenderObj(), rec, b, c, v);
    }
    if (modelRes.getAnimSet()->getBtp(i)) {
        NNSG3dResAnmCommon *rec = modelRes.getAnimSet()->getBtp(i);
        u32 v;
        if (d == 0xffff) {
            v = ((u32)anims[2].curFrame << 4) >> 16;
        } else {
            u32 n = rec->numFrame;
            v = (u16)(d >= n ? n - 1 : d);
        }
        void *p = model.getRenderObj();
        anims[2].replaceWithTex(p, rec, modelRes.getTexture(), b, c, v);
    }
    if (modelRes.getAnimSet()->getBca(i)) {
        NNSG3dResAnmCommon *rec = modelRes.getAnimSet()->getBca(i);
        u32 v;
        if (d == 0xffff) {
            v = ((u32)model.curFrame << 4) >> 16;
        } else {
            u32 n = rec->numFrame;
            if (d >= n) {
                d = n - 1;
            }
            v = (u16)d;
        }
        model.initAnim(rec, b, c, v, 0);
    }
}

extern "C" void FtrActor_PlayAnimsFromLastFrame(FtrActor *self, u32 a, s32 b, s32 c) {
    s32 k = a & 1;
    NNSG3dResAnmCommon *q;
    if (self->modelRes.getAnimSet()->getBva(k)) {
        q = self->modelRes.getAnimSet()->getBva(k);
        self->anims[3].replace(self->model.getRenderObj(), q, b, c, (u16)(q->numFrame - 1));
    }
    if (self->modelRes.getAnimSet()->getBma(k)) {
        q = self->modelRes.getAnimSet()->getBma(k);
        self->anims[0].replace(self->model.getRenderObj(), q, b, c, (u16)(q->numFrame - 1));
    }
    if (self->modelRes.getAnimSet()->getBta(k)) {
        q = self->modelRes.getAnimSet()->getBta(k);
        self->anims[1].replace(self->model.getRenderObj(), q, b, c, (u16)(q->numFrame - 1));
    }
    if (self->modelRes.getAnimSet()->getBtp(k)) {
        void *obj;
        q = self->modelRes.getAnimSet()->getBtp(k);
        obj = self->model.getRenderObj();
        self->anims[2].replaceWithTex(obj, q, self->modelRes.getTexture(), b, c, (u16)(q->numFrame - 1));
    }
    if (self->modelRes.getAnimSet()->getBca(k)) {
        q = self->modelRes.getAnimSet()->getBca(k);
        self->model.initAnim(q, b, c, (u16)(q->numFrame - 1), 0);
    }
}

extern "C" BOOL FtrActor_StepAnims(FtrActor *self) {
    BOOL k = TRUE;
    BOOL r4 = TRUE;
    BOOL z = FALSE;
    u32 i;
    if (self->model.getAnmObj()) {
        self->model.stepBlend();
        if (!self->model.isFinished()) {
            r4 = FALSE;
        }
    }
    for (i = z; i < 4; i++) {
        if (self->anims[i].getAnmObj()) {
            FtrModelAnim *p = &self->anims[i];
            p->step();
            ((G3dAnmObj *)p->anmObj)->frame = p->curFrame;
            if (!p->isFinished()) {
                k = z;
            }
        }
    }
    if (k && r4) {
        return TRUE;
    }
    return FALSE;
}

extern "C" ModelSlot *FtrActor_GetHeap(FtrActor *self) {
    return sFtrMgrPool.acquire(&self->modelSlot);
}

extern "C" void FtrActor_LocalToWorld(FtrActor *self, VecFx32 *out, VecFx32 *src) {
    data_021f47e0 = self->worldMtx;
    MTX_MultVec43(src, &data_021f47e0, out);
}

extern "C" void FtrActor_GetCorner(FtrActor *self, VecFx32 *out, s32 i) {
    FxVec3 *tbl = sFtrFootprintCorners[self->footprint];
    FtrActor_LocalToWorld(self, out, &tbl[i & 3]);
}

extern "C" void FtrActor_GetCenter(FtrActor *self, VecFx32 *out) {
    u32 i = 0;
    VecFx32 v;
    VecFx32 t;
    v.x = i;
    v.y = i;
    v.z = i;
    for (; i < 4; i++) {
        FtrActor_GetCorner(self, &t, i);
        VEC_Add(&v, &t, &v);
    }
    v.x = v.x >> 2;
    v.y = v.y >> 2;
    v.z = v.z >> 2;
    out->x = v.x;
    out->y = v.y;
    out->z = v.z;
}

extern "C" BOOL FtrActor_TestPlayerUnk() {
    PlayerData *pd;
    PlayerId *id;
    if ((pd = PlayerData_GetCurrent()) != NULL) {
        if ((id = pd->getPlayerId()) != NULL) {
            if (id->getTownRelation() == 0) {
                return TRUE;
            }
            return FALSE;
        }
    }
    return FALSE;
}

extern "C" BOOL FtrActor_IsWithinDist(VecFx32 *pos, s32 a, VecFx32 *p, s32 b) {
    if (Vec_DistXZ(pos, p) < a + b) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL FtrActor_IsPosClearOfCharacters(VecFx32 *pos, s32 a, s32 b, s32 c, s32 d) {
    void *p;
    u32 i;
    u32 j;
    u32 n;
    p = PlayerActor_GetActor(4);
    if (p) {
        for (i = 0; i < 4; i++) {
            Actor *q = (Actor *)PlayerActor_GetActor(i);
            if (q && p != q) {
                if (FtrActor_IsWithinDist(pos, a, &q->position, c)) {
                    return FALSE;
                }
            }
        }
        n = NpcRegistry_GetSlotCount();
        for (j = 0; j < n; j++) {
            NpcActor *q = NpcRegistry_GetBySlot(j);
            if (q) {
                if (FtrActor_IsWithinDist(pos, b, &q->position, d)) {
                    return FALSE;
                }
            }
        }
        return TRUE;
    }
    return FALSE;
}

extern "C" FtrActor *FtrActor_GetParent(FtrActor *self) {
    if (self->stackLink.isAttached()) {
        return FtrActorTable_GetInstance()->get(self->stackLink.getParentIndex());
    }
    return 0;
}

extern "C" s32 FtrActor_GetFtrIndex(FtrActor *self) {
    return self->ftrIndex;
}

BOOL FtrActor::changeAct(u32 a, u8 v) {
    actAid = v;
    netRequestPending = 0;
    return 1;
}

u8 FtrActor::getActSwitchState(u32 a) {
    return 0;
}

extern "C" BOOL FtrActor_RequestToggle(FtrActor *self) {
    if (self->netRequestPending == 0) {
        self->switchState.toggle(1);
        return TRUE;
    }
    return FALSE;
}

extern "C" u8 FtrActor_GetLayer(FtrActor *self) {
    return self->mapLayer;
}

extern "C" void FtrActor_CalcWorldMtx(FtrActor *self, VecFx32 *a, s32 b) {
    if (self->stackLink.isAttached()) {
        FtrActor *q = FtrActorTable_GetInstance()->get(self->stackLink.getParentIndex());
        s32 r4, r6;
        if (a != 0 || b != 0) {
            FtrActor_CalcWorldMtx(q, a, b);
        } else {
            data_021f47e0 = q->worldMtx;
        }
        r6 = self->stackLink.getRelPos()->z;
        r4 = self->stackLink.getRelPos()->y;
        s32 x = self->stackLink.getRelPos()->x;
        Mtx43_Translate(&data_021f47e0, x, r4, r6);
        Mtx43_RotateY(&data_021f47e0, self->stackLink.getRelAngle());
    } else {
        VecFx32 v;
        s32 ang;
        v.x = self->position.x;
        v.y = self->position.y;
        v.z = self->position.z;
        if (a != 0) {
            VEC_Add(&v, a, &v);
        }
        ang = (s16)(self->rotY + b);
        Mtx43_SetTranslate(&data_021f47e0, v.x, v.y, v.z);
        Mtx43_RotateY(&data_021f47e0, ang);
        Mtx43_Translate(&data_021f47e0, self->modelOffset.x, self->modelOffset.y, self->modelOffset.z);
    }
}

extern "C" void FtrActor_UpdateMtx(FtrActor *self) {
    if (self->isPreview()) {
        Mtx43_SetTranslate(&data_021f47e0, self->position.x, self->position.y, self->position.z);
        Mtx43_RotateX(&data_021f47e0, sFtrPreviewPitch);
        Mtx43_RotateY(&data_021f47e0, (s16)(self->rotY + sFtrPreviewYaw));
        if (self->footprint == 1) {
            Mtx43_Translate(&data_021f47e0, func_01ffcb0c(self->drawScale, -0x1000), 0, 0);
        }
        s32 y = FtrInfo_GetDmaUnk06(FtrActor_GetFtrIndex(self)) * 100 - 0x258;
        Mtx43_Translate(&data_021f47e0, 0, y, 0);
        self->model.mtx = data_021f47e0;
    } else {
        FtrActor_CalcWorldMtx(self, 0, 0);
        self->worldMtx = data_021f47e0;
        if (self->footprint == 1) {
            Mtx43_Translate(&data_021f47e0, func_01ffcb0c(0x1000 - self->drawScale, 0x1000), 0, 0);
        }
        self->model.mtx = data_021f47e0;
    }
}

s16 sFtrPreviewPitch;

extern "C" void FtrActor_GetBoxSize(FtrActor *self, VecFx32 *out) {
    static FxVec3 vs[3] = {FxVec3(0x2000, 0x2000, 0x2000),
                                         FxVec3(0x4000, 0x2000, 0x2000),
                                         FxVec3(0x4000, 0x2000, 0x4000)};
    volatile VecFx32 r;
    Scene_GetCurrent();
    {
        FxVec3 *q = &vs[self->footprint];
        r.x = q->x;
        r.y = q->y;
        r.z = q->z;
    }
    if (self->surfaceHeight == 0) {
        r.y = 0x200;
    } else if (FtrMgr_IsSaleMode() != 0) {
        r.y = self->surfaceHeight;
    } else {
        r.y = self->surfaceHeight >> 1;
    }
    out->x = r.x;
    out->y = r.y;
    out->z = r.z;
}

extern "C" void FtrActor_InitCollider(FtrActor *self) {
    VecFx32 a;
    VecFx32 b;
    VecFx32 c;
    if (!self->isPreview()) {
        u32 r6;
        s32 k;
        FtrActor_GetBoxSize(self, &a);
        {
            s32 t = self->colliderScale;
            b.x = t;
            b.y = t;
            b.z = t;
        }
        FtrActor_GetCenter(self, &c);
        if (self->noCollision == 0) {
            self->collider.setOwner(self);
            FtrActorTable_GetInstance()->get(self->stackLink.getParentIndex());
            BoxCollider_Register(&self->collider, a.x, a.z, 0x4000, &c, self->rotY, &b);
        }
        r6 = (u8)FtrActorTable_GetInstance()->indexOf(self);
        a.x = func_01ffcb0c(a.x, 0xc00);
        a.z = func_01ffcb0c(a.z, 0xc00);
        if (Scene_InUnk6To8() != 0) {
            k = 0xf;
        } else {
            k = 8;
        }
        Scene_GetTouchPicker()->addBox(&self->touchBox, &c, a.x, a.z, a.y, self->rotY, k, r6);
    }
}

extern "C" void FtrActor_ReleaseCollider(FtrActor *self) {
    if (!self->isPreview()) {
        if (self->noCollision == 0) {
            BoxCollider_Unregister(&self->collider);
            self->collider.clearOwner();
        }
    }
}

extern "C" void FtrActor_UpdateBox(FtrActor *self) {
    VecFx32 a;
    VecFx32 b;
    VecFx32 c;
    if (!self->isPreview()) {
        s32 r4;
        s32 t;
        FtrActor_GetBoxSize(self, &a);
        t = self->colliderScale;
        b.x = t;
        b.y = t;
        b.z = t;
        FtrActor_GetCenter(self, &c);
        r4 = 0;
        if (self->noCollision == 0) {
            if (self->collider.isActive != 0) {
                r4 = BoxCollider_UpdateShape(&self->collider, &c, self->rotY, &b);
            } else {
                r4 = 1;
            }
        }
        a.x = func_01ffcb0c(a.x, 0xc00);
        a.z = func_01ffcb0c(a.z, 0xc00);
        if (r4 != 0) {
            u32 r6 = (u8)FtrActorTable_GetInstance()->indexOf(self);
            s32 k;
            if (Scene_InUnk6To8() != 0) {
                k = 0xf;
            } else {
                k = 8;
            }
            Scene_GetTouchPicker()->addBox(&self->touchBox, &c, a.x, a.z, a.y, self->rotY, k, r6);
        } else {
            Scene_GetTouchPicker()->pushBox(&self->touchBox);
        }
    }
}

extern "C" void FtrActor_UpdateTopItemBoxes(FtrActor *self) {
    if (self->mapLayer == 0 && self->hasTopSurface == 1) {
        FtrTileList l;
        VecFx32 v;
        BlockMap *grid;
        u32 i;
        self->getTiles(&l, 0, 0);
        grid = gSceneBlockMap;
        for (i = 0; i < l.getCount(); i++) {
            s32 x = l.get(i)->x;
            s32 y = l.get(i)->y;
            s32 hx = x >> 4;
            s32 hy = y >> 4;
            u16 *c = BlockMap_GetItemPtr(grid, hx, hy, x - (hx << 4), y - (hy << 4), 1);
            if (c) {
                if (Item_IsNormalItem(c)) {
                    FieldPos_FromUnitCenter(&v, x, y);
                    v.y = FtrMgr_GetSurfaceHeight(x, y);
                    Scene_GetTouchPicker()->addCylinder(&self->topItemCylinders[i], &v, 0xccd, 0x100, 10, 0xff);
                }
            }
        }
        l.release();
    }
}

extern "C" void FtrActor_SetInitialAct(FtrActor *self) {
    self->setAct(sFtrInitialActByMode[self->spawnMode]);
}

void FtrActor::setupFromSpawnArg() {
    if (isSetUp == 0) {
        struct {
            volatile u16 tmp;
            u16 pad;
            FtrSpawnArg bits;
            u32 pad2;
        } f;
        f.bits = *(FtrSpawnArg *)&param;
        VecFx32 p1, p2, r;
        volatile VecFx32 q;
        if (!isPreview()) {
            FieldPos_FromBlockUnitCenter(&position, 0, 0, f.bits.tileX, f.bits.tileZ);
            position.y = FtrMgr_GetSurfaceHeightAtPos(&position);
            drawScale = 0x1000;
            drawScaleY = 0x1000;
            drawScaleZ = 0x1000;
            colliderScale = 0x1000;
        } else {
            p1 = gCameraEye;
            p2 = gCameraLookAt;
            Vec_Sub(&r, &p2, &p1);
            Vec_SafeNormalize(&r);
            s32 qz = func_01ffcb0c(r.z, 0x4000);
            s32 qy = func_01ffcb0c(r.y, 0x4000);
            s32 qx = func_01ffcb0c(r.x, 0x4000);
            q.x = qx;
            q.y = qy;
            q.z = qz;
            position.x = p1.x + qx;
            position.y = p1.y + q.y;
            position.z = p1.z + q.z;
            drawScale = 0x400;
            drawScaleY = 0x400;
            drawScaleZ = 0x400;
            colliderScale = 0x1000;
            sFtrPreviewPitch = Math_Atan2(r.z, r.y) - 0xb000;
            sFtrPreviewYaw = Math_Atan2(r.x, r.z) + 0x8000;
        }
        rotY = f.bits.dir << 14;
        ftrIndex = f.bits.ftrIndex;
        if ((s32)ftrIndex >= 0x6e9) {
            ftrIndex = 0x6e8;
        }
        f.tmp = Item_MakeFurniture(ftrIndex, 0);
        mapLayer = f.bits.layer;
        if (!isPreview() && mapLayer == 0) {
            position.y = 0;
            if (Scene_GetCurrent() == 10) {
                position.y = FtrMgr_GetSurfaceHeightAtPos(&position);
            }
        }
        kind = FtrInfo_GetDmaUnk02(ftrIndex);
        surfaceHeight = FtrInfo_GetDmaUnk03Fx(ftrIndex);
        footprint = FtrInfo_GetUnk05(ftrIndex);
        commentPersonality = FtrInfo_GetDmaUnk07(ftrIndex);
        commentId = FtrInfo_GetDmaUnk08(ftrIndex);
        noCollision = FtrInfo_TestIndoorFlag2(ftrIndex);
        startsOff = FtrInfo_TestIndoorFlag3(ftrIndex);
        hasTopSurface = FtrInfo_GetDmaUnk04(ftrIndex);
        lightKind = FtrInfo_GetIndoorFlagPair(ftrIndex);
        if (!isPreview()) {
            if (footprint == 2) {
                position.x += 0x1000;
                position.z += 0x1000;
            }
            if (mapLayer == 1) {
                stackLink.attachAt(f.bits.tileX, f.bits.tileZ, rotY);
            }
        }
        FtrActor_UpdateMtx(this);
        switchState.loadFromMap(this);
        writeTiles(1, 0, 0, 0);
        FtrActor_SetInitialAct(this);
        FtrActor_InitCollider(this);
        isSetUp = 1;
    }
}

void FtrActor::setupModel() {
    void *p = model.resMdl;
    s32 a = ((G3dResAccess *)(p))->findNodeIdx((const char *)("kh_j"));
    s32 b = ((G3dResAccess *)(p))->findNodeIdx((const char *)("km_j"));
    clockHands.set((s8)a, (s8)b);
    model.setInitCallback((void (*)(NNSG3dRS *))(FtrActor_SetModelCallbacks), this);
    visNodes.init(model.resMdl, 1);
    void *t = modelRes.getModel();
    NNS_G3dBindMdlTex(t, modelRes.getTexture());
    t = modelRes.getModel();
    NNS_G3dBindMdlPltt(t, modelRes.getTexture());
    applyPolygonId();
}

void FtrActor::applyPolygonId() {
    s32 r = FtrActorTable_GetInstance()->indexOf(this);
    if (r != -1) {
        model.setPolygonId(sFtrPolygonIds[r]);
    }
}

const u32 sFtrInitialActByMode[3] = {1, 0, 8};
const u8 sFtrPolygonIds[0x1c] = {0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13,
                                      0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c};

FxVec3 FtrActor_getTiles_s(0, 0, 0);
void FtrActor::getTiles(FtrTileList *l, VecFx32 *x, s32 y) {
    VecFx32 c;
    VecFx32 d;
    VecFx32 e;
    s32 ox, oy;
    c.x = position.x;
    c.y = position.y;
    c.z = position.z;
    if (x != 0) {
        VEC_Add(&c, x, &c);
    }
    static FxVec3 arr[2] = {FxVec3(0, 0, 0), FxVec3(0x2000, 0, 0)};
    d.x = c.x;
    d.y = c.y;
    d.z = c.z;
    switch (footprint) {
    case 0:
        if (x != 0 || y != 0) {
            FtrActor_CalcWorldMtx(this, x, y);
        } else {
            data_021f47e0 = worldMtx;
        }
        {
            MTX_MultVec43(&FtrActor_getTiles_s, &data_021f47e0, &d);
        }
        FieldPos_ToUnit(&ox, &oy, &d);
        l->add(ox, oy);
        break;
    case 1: {
        if (x != 0 || y != 0) {
            FtrActor_CalcWorldMtx(this, x, y);
        } else {
            data_021f47e0 = worldMtx;
        }
        s32 i;
        for (i = 0; i < 2; i++) {
            e.x = arr[i].x;
            e.y = arr[i].y;
            e.z = arr[i].z;
            MTX_MultVec43(&e, &data_021f47e0, &d);
            FieldPos_ToUnit(&ox, &oy, &d);
            l->add(ox, oy);
        }
        break;
    }
    default:
        d.x = c.x - 0x1000;
        d.z = c.z - 0x1000;
        FieldPos_ToUnit(&ox, &oy, &d);
        l->add(ox, oy);
        l->add(ox + 1, oy);
        l->add(ox, oy + 1);
        l->add(ox + 1, oy + 1);
        break;
    }
}

extern "C" u32 FtrActor_AngleToDir(s32 v) {
    u32 x = (u16)v;
    if (x >= 0xe000 || x < 0x2000) {
        return 0;
    }
    if (x < 0x6000) {
        return 1;
    }
    if (x < 0xa000) {
        return 2;
    }
    return 3;
}

extern "C" void FtrActor_MakeItemForAngle(u16 *out, FtrActor *obj, s32 ang) {
    *out = Item_MakeFurniture(obj->ftrIndex, FtrActor_AngleToDir(ang));
}

void FtrActor::clearTiles(s32 a, s32 b) {
    if (!isPreview()) {
        FtrTileList l;
        BlockMap *grid;
        u32 i;
        getTiles(&l, 0, 0);
        grid = gSceneBlockMap;
        {
            volatile u16 tmp[1];
            tmp[0] = 0xfff1;
            Scene_GetCurrent();
            FtrMgr_IsSaleMode();
            i = 0;
            for (; i < l.getCount(); i++) {
                s32 x = l.get(i)->x;
                s32 y = l.get(i)->y;
                s32 hx = x >> 4;
                s32 hy = y >> 4;
                u16 *p = BlockMap_GetItemPtr(grid, hx, hy, x - (hx << 4), y - (hy << 4), mapLayer);
                if (p != 0 && Item_IsFurniture(p)) {
                    s32 t = Scene_GetCurrent();
                    FtrSync_RemoveFurniture(t, x, y, mapLayer, switchState.isOn(), p, b, a);
                }
                FtrActorGrid_GetInstance()->clearCell(this, x, y, mapLayer);
                if (b != 0 && mapLayer == 0) {
                    s32 c = FtrActorGrid_GetInstance()->getIndex(x, y, 1);
                    if (c != -1) {
                        FtrActorGrid_GetInstance()->clearCell(this, x, y, 1);
                    }
                }
            }
        }
        l.release();
    }
}

FxVec3 FtrActor_writeTiles_s0(0, 0, 0);
FxVec3 FtrActor_writeTiles_s1(0, 0, 0x1000);
void FtrActor::writeTiles(s32 unused, VecFx32 *x, s32 y, u8 flag) {
    if (!isPreview()) {
        FtrTileList l;
        u16 a, b, c;
        u32 r7;
        s32 v18;
        u32 i;
        getTiles(&l, x, y);
        a = 0xfff1;
        if (mapLayer == 1) {
            VecFx32 v1, v2;
            MTX_MultVec43(&FtrActor_writeTiles_s0, &data_021f47e0, &v1);
            MTX_MultVec43(&FtrActor_writeTiles_s1, &data_021f47e0, &v2);
            s32 ang = Math_Atan2(v2.x - v1.x, v2.z - v1.z);
            FtrActor_MakeItemForAngle(&b, this, ang);
            a = b;
        } else {
            FtrActor_MakeItemForAngle(&c, this, (s16)(rotY + y));
            a = c;
        }
        Scene_GetCurrent();
        FtrMgr_IsSaleMode();
        if (isSetUp == 0) {
            r7 = 0;
        } else {
            r7 = FtrActor_PredIsGyroid(this);
        }
        v18 = getActAid();
        for (i = 0; i < l.getCount(); i++) {
            if (i == 0) {
                u32 s = switchState.isOn();
                s32 t = Scene_GetCurrent();
                Unk_ov004_02206520_Ent *p1 = l.get(i);
                Unk_ov004_02206520_Ent *p2 = l.get(i);
                FtrSync_PlaceFurniture(t, p1->x, p2->y, mapLayer, s, r7, v18, &a, 1);
            }
            FtrActorGrid *o = FtrActorGrid_GetInstance();
            Unk_ov004_02206520_Ent *p3 = l.get(i);
            Unk_ov004_02206520_Ent *p4 = l.get(i);
            o->setCell(this, p3->x, p4->y, mapLayer);
        }
        if (flag != 0) {
            u32 r = makeCharId(x, y);
            if (r != getCharId()) {
                setCharId(r);
            }
        }
        l.release();
    }
}

void FtrActor::moveTiles(VecFx32 *a, s32 b) {
    FtrTileList l;
    u32 i;
    getTiles(&l, 0, 0);
    FtrStackedSet set(&l, mapLayer);
    clearTiles(1, 1);
    writeTiles(1, a, b, 1);
    for (i = 0; i < set.getCount(); i++) {
        FtrActor *o = set.get(i);
        if (o != 0) {
            o->writeTiles(1, a, b, 1);
        }
    }
    set.clear();
    l.release();
}

extern "C" s32 FtrActor_TestSceneUnk(s32 a) {
    return SceneId_IsHouseRoom(a);
}

extern "C" s32 FtrActor_TestCurSceneUnk() {
    return FtrActor_TestSceneUnk(Scene_GetCurrent());
}

void FtrActor::initLamp() {
    if (FtrActor_PredIsLightSource(this)) {
        void *v = model.resMdl;
        u32 t = switchState.isOn();
        lampMat.bindMaterial((G3dResAccess *)v, "lp_m", t);
        if (FtrActor_TestCurSceneUnk()) {
            s32 r = FtrMgr_CountSwitchedOn(FtrActor_IsLightSource);
            if (switchState.isOn() != 0 && r == 1) {
                if (spawnMode != 0) {
                    FtrActor_TurnOnRoomLight(lightKind);
                    FtrSync_SetRoomLight(Scene_GetCurrent(), 1);
                } else {
                    LightSwitch_SetOn(0, 1, 0);
                }
            }
        }
    }
}

void FtrActor::updateLamp() {
    if (FtrActor_PredIsLightSource(this)) {
        if (FtrActor_TestCurSceneUnk()) {
            u32 b = switchState.isOn();
            u32 f = lightKind == 1 ? 1 : 0;
            if (lampMat.setLit(b, 1, f)) {
                s32 m = FtrMgr_CountSwitchedOn(FtrActor_IsLightSource);
                if (switchState.isOn()) {
                    if (m == 1) {
                        FtrActor_TurnOnRoomLight(lightKind);
                        FtrSync_SetRoomLight(Scene_GetCurrent(), 1);
                    }
                } else if (m == 0) {
                    LightSwitch_SetOff(0, 8);
                    FtrSync_SetRoomLight(Scene_GetCurrent(), 0);
                }
            }
        }
    }
    lampMat.updateEmission();
}

void FtrActor::releaseRoomLight() {
    if (FtrActor_PredIsLightSource(this)) {
        if (FtrActor_TestCurSceneUnk()) {
            if (switchState.isOn()) {
                if (FtrMgr_CountSwitchedOn(FtrActor_IsLightSource) == 1) {
                    LightSwitch_SetOff(0, 1);
                    if (isRemoving()) {
                        FtrSync_SetRoomLight(Scene_GetCurrent(), 0);
                    }
                }
            }
        }
    }
}

extern "C" s32 FtrActor_GetDragSe(void) {
    if (Unk_ov004_02207650_IsOne(gFieldSceneKind)) {
        u16 *p = RoomShell_GetCarpet();
        if (Unk_ov004_02207650_InRange(p)) {
            s32 q = GroundAttr_GetDragSe(ItemInfo_GetIndoorUnk1(p));
            if (q != 0xffff) {
                return q;
            }
        }
        return 0x4c1;
    }
    return 0xffff;
}

BOOL FtrActor::hasItemOnTop() {
    FtrTileList c;
    getTiles(&c, 0, 0);
    BlockMap *grid = gSceneBlockMap;
    if (mapLayer == 0 && hasTopSurface == 1) {
        u32 i;
        for (i = 0; i < c.getCount(); i++) {
            s32 y = c.get(i)->y;
            s32 x = c.get(i)->x;
            s32 hx = x >> 4;
            s32 hy = y >> 4;
            u16 *cell = BlockMap_GetItemPtr(grid, hx, hy, x - (hx << 4), y - (hy << 4), 1);
            if (cell && *cell != 0xfff1) {
                c.release();
                return TRUE;
            }
        }
    }
    c.release();
    return FALSE;
}

BOOL FtrActor::canRotateBy(s32 a) {
    return canMoveTo(0, a);
}

BOOL FtrActor::canMoveBy(VecFx32 *a) {
    return canMoveTo(a, 0);
}

BOOL FtrActor::canMoveTo(VecFx32 *a, s32 b) {
    s32 x0, y0, x1, y1;
    VecFx32 v1;
    VecFx32 v2;
    FtrTileList c1;
    FtrTileList c2;
    FtrActor *obj;
    s32 y;
    s32 y2;
    BlockMap *grid;
    u16 *cell1;
    s32 x2;
    s32 x;
    if (netRequestPending != 0) {
        return FALSE;
    }
    if (!Scene_InHouseRoom()) {
        return FALSE;
    }
    if (!FtrActor_TestPlayerUnk()) {
        return FALSE;
    }
    grid = gSceneBlockMap;
    Actor *cam = (Actor *)PlayerActor_GetActor(4);
    if (mapLayer == 1) {
        return FALSE;
    }
    if (grid == 0 || cam == 0) {
        return FALSE;
    }
    if (!topItems.canPickUp(this)) {
        return FALSE;
    }
    VecFx32 *pp = &cam->position;
    v1.x = pp->x;
    v1.y = pp->y;
    v1.z = pp->z;
    FieldPos_ToUnit(&x0, &y0, &v1);
    v2.x = v1.x;
    v2.y = v1.y;
    v2.z = v1.z;
    if (a) {
        VEC_Add(&v2, a, &v2);
    }
    FieldPos_ToUnit(&x1, &y1, &v2);
    obj = FtrActorGrid_GetInstance()->getActor(x1, y1, 0);
    clearTiles(0, 0);
    getTiles(&c1, a, b);
    getTiles(&c2, a, b >> 1);
    u32 i;
    for (i = 0; i < c1.getCount(); i++) {
        x = c1.get(i)->x;
        y = c1.get(i)->y;
        s32 hx = x >> 4;
        s32 hy = y >> 4;
        cell1 = BlockMap_GetItemPtr(grid, hx, hy, x - (hx << 4), y - (hy << 4), 0);
        if (a == 0 && x0 == x && y0 == y) UNK_OV004_022072B4_FAIL()
        if (a == 0) {
            y2 = c2.get(i)->y;
            x2 = c2.get(i)->x;
            s32 hx2 = x2 >> 4;
            s32 hy2 = y2 >> 4;
            u16 *cell2 = BlockMap_GetItemPtr(grid, hx2, hy2, x2 - (hx2 << 4), y2 - (hy2 << 4), 0);
            if (cell2 && *cell2 != 0xfff1) UNK_OV004_022072B4_FAIL()
        }
        if (cell1 && *cell1 != 0xfff1) UNK_OV004_022072B4_FAIL()
        if (!Ground_CanPlaceItem(x, y)) UNK_OV004_022072B4_FAIL()
        FtrActor *gridActor = FtrActorGrid_GetInstance()->getActor(x, y, 1);
        if (gridActor && gridActor->isNotIdle()) UNK_OV004_022072B4_FAIL()
        if (b == 0) {
            if ((obj && obj->noCollision == 0 && obj != this) || Ground_GetExitAtPos(&v2) != -1 || FtrMgr_GetSurfaceHeightAtPos(&v2)) UNK_OV004_022072B4_FAIL()
        }
    }
    writeTiles(0, 0, 0, 0);
    c2.release();
    c1.release();
    return TRUE;
}

u16 FtrActor::makeCharId(VecFx32 *a, s32 b) {
    FtrCharIdBits p;
    s32 x;
    s32 y;
    if (Scene_InUnk6To8() != 0 || isPreview()) {
        (*(u16 *)&p) = ((*(u16 *)&p) & 0xfffffe00) | ((u16)FtrActorTable_GetInstance()->indexOf(this) & 0x1ff);
        (*(u16 *)&p) = ((*(u16 *)&p) & 0xffff01ff) | ((Scene_GetCurrent() & 0x7f) << 9);
        return (*(u16 *)&p);
    } else {
        if (findOwnTile(&x, &y, a, b)) {
            (((u16 *)&p)[1]) = ((((u16 *)&p)[1]) & ~0xf) | ((u16)(x & 0xf) & 0xf);
            (((u16 *)&p)[1]) = ((((u16 *)&p)[1]) & ~0xf0) | (((u16)(y & 0xf) & 0xf) << 4);
            (((u16 *)&p)[1]) = ((((u16 *)&p)[1]) & 0xfffffeff) | (((u16)(mapLayer & 1) & 1) << 8);
            (((u16 *)&p)[1]) = ((((u16 *)&p)[1]) & 0xffff81ff) | ((Scene_GetCurrent() & 0x3f) << 9);
            return (((u16 *)&p)[1]);
        }
        return 0;
    }
}

BOOL FtrActor::findOwnTile(s32 *ox, s32 *oy, VecFx32 *a, s32 b) {
    FtrTileList c;
    getTiles(&c, a, *(s16 *)&b);
    BlockMap *grid = gSceneBlockMap;
    u32 i;
    for (i = 0; i < c.getCount(); i++) {
        s32 y, x, hx, hy;
        u8 layer;
        layer = mapLayer;
        y = c.get(i)->y;
        x = c.get(i)->x;
        hx = x >> 4;
        hy = y >> 4;
        u16 *cell = BlockMap_GetItemPtr(grid, hx, hy, x - (hx << 4), y - (hy << 4), layer);
        if (cell) {
            if (Item_IsFurniture(cell)) {
                *ox = c.get(i)->x;
                *oy = c.get(i)->y;
                c.release();
                return TRUE;
            }
        }
    }
    c.release();
    return FALSE;
}

extern "C" void FtrActor_SpawnActorC0(VecFx32 *a, u32 x) {
    u16 s[3];
    s[0] = 0;
    s[1] = x;
    s[2] = 0;
    HouseRoach_SpawnFromFurniture(a, s);
}

void FtrActor::spawnActorC0AtTile(s32 a) {
    VecFx32 *cam = (VecFx32 *)PlayerActor_GetBodyPos(4);
    if (cam) {
        FtrTileList c;
        VecFx32 v1;
        VecFx32 v2;
        getTiles(&c, 0, 0);
        s32 hi = 0;
        s32 hiIdx = ~hi;
        s32 loIdx = hiIdx;
        s32 lo = data_020c8cbc;
        u32 i;
        for (i = 0; i < c.getCount(); i++) {
            Unk_ov004_02206520_Ent *e1 = c.get(i);
            Unk_ov004_02206520_Ent *e2 = c.get(i);
            FieldPos_FromUnitCenter(&v1, e1->x, e2->y);
            s32 d = Vec_DistXZ(cam, &v1);
            if (d > hi) {
                hiIdx = i;
                hi = d;
            }
            if (d < lo) {
                loIdx = i;
                lo = d;
            }
        }
        if (a == 0) {
            hiIdx = loIdx;
        }
        if (hiIdx != -1) {
            Unk_ov004_02206520_Ent *p = c.get(hiIdx);
            Unk_ov004_02206520_Ent *q = c.get(hiIdx);
            FieldPos_FromUnitCenter(&v2, p->x, q->y);
            FtrActor_SpawnActorC0(&v2, Math_AngleXZ(&v2, cam));
        }
        c.release();
    }
}

void FtrActor::spawnActorC0AtCenter() {
    VecFx32 *cam = (VecFx32 *)PlayerActor_GetBodyPos(4);
    if (cam) {
        VecFx32 v;
        FtrActor_GetCenter(this, &v);
        FtrActor_SpawnActorC0(&v, Math_AngleXZ(&v, cam));
    }
}

void FtrActor::spawnEffectAt(VecFx32 *v) {
    VecFx32 t;
    t.x = v->x;
    t.y = v->y;
    t.z = v->z;
    Effect_PlayById2(0x3d, &t, 0, 0);
}

void FtrActor::spawnEffectAtCorner(s32 a) {
    VecFx32 p;
    VecFx32 q;
    VecFx32 r;
    FtrActor_GetCorner(this, &p, a);
    FtrActor_GetCenter(this, &q);
    s32 y = position.y;
    r.x = (p.x + q.x) >> 1;
    r.y = y;
    r.z = (p.z + q.z) >> 1;
    spawnEffectAt(&r);
}

BOOL FtrActor::isPreview() {
    if (spawnMode == 2) {
        return TRUE;
    }
    return FALSE;
}

extern "C" s32 FtrActor_PredIsLightSource(FtrActor *p) {
    return FtrActor_IsLightSource(p);
}

extern "C" s32 FtrActor_PredIsStereo(FtrActor *p) {
    return FtrActor_IsStereo(p);
}

extern "C" s32 FtrActor_PredIsSeatOrBed(FtrActor *p) {
    return (p)->isSeatOrBed();
}

extern "C" s32 FtrActor_PredIsGyroid(FtrActor *p) {
    return (p)->isGyroid();
}

extern "C" void FtrActor_GetItemId(u16 *out, FtrActor *o) {
    if (o->kind == 0x1c) {
        *out = 0xfff1;
    } else {
        *out = Item_MakeFurniture(FtrActor_GetFtrIndex(o), 0);
    }
}

BOOL FtrActor::onMatCalc(s32 matId, NNSG3dRS *rs) {
    return TRUE;
}

BOOL FtrActor::onJointCalcPre(s32 nodeId, NNSG3dRS *rs) {
    return TRUE;
}

void FtrActor::onJointCalcPost(s32 a, void *b) {
    if (clockHands.valid != 0) {
        if (clockHands.hourJnt == a) {
            JointCb_RotateClockHourHand((NNSG3dRS *)b);
        } else if (clockHands.minJnt == a) {
            JointCb_RotateClockMinuteHand((NNSG3dRS *)b);
        }
    }
}

void FtrActor::onNodeVisCalc(s32 a, NNSG3dRS *b) {
    if (visNodes.hasNode(a)) {
        u32 v = visNodes.isVisible();
        *(u32 *)b->pVisAnmResult = v;
    }
}

FtrModelAnim::FtrModelAnim() {
}

FtrModelAnim::~FtrModelAnim() {
}

NNSG3dAnmObj *FtrModelAnim::getAnmObj() {
    return anmObj;
}

FtrModelRes::FtrModelRes() : item(0xfff1) {
    texFile = 0;
    arcFile = 0;
    model = 0;
    texture = 0;
    item = 0xfff1;
    keepTexCopy = 0;
}

FtrModelRes::~FtrModelRes() {
}

BOOL FtrModelRes::isLoaded() {
    if (texture != 0) {
        return TRUE;
    }
    return FALSE;
}

char *FtrModelRes::makeArcPath(s32 id) {
    Str_SPrintf(sFtrArcPathBuf, "/ftr/%d/%d/%04x.arc", id >> 8, (id & 0xff) >> 4, id);
    return sFtrArcPathBuf;
}

char *FtrModelRes::makeTexPath(s32 id) {
    Str_SPrintf(sFtrTexPathBuf, "/ftr/%d/%d/%04x.nsbtx", id >> 8, (id & 0xff) >> 4, id);
    return sFtrTexPathBuf;
}

BOOL FtrModelRes::loadFiles(ModelSlot *obj, s32 id) {
    u32 size0;
    u32 size1;
    char name[0x20];
    NNSFndArchive blk;
    if (texFile == 0) {
        texFile = File_LoadAlloc(makeTexPath(id), gCurrentHeap, -4, &size0);
        if (keepTexCopy != 0) {
            void *r7 = Heap_Alloc((Heap *)obj->getHeap(), size0);
            MI_CpuCopy8(texFile, r7, size0);
            animSet.setTexCopy(r7);
        }
    }
    if (arcFile == 0) {
        char *p = makeArcPath(id);
        arcFile = File_LoadAlloc(p, obj->getHeap(), 4, &size1);
    }
    if (model == 0 && arcFile != 0) {
        if (NNS_FndMountArchive(&blk, "FTR", arcFile)) {
            u8 *pb = (u8 *)NNS_G3dGetMdlSet((u8 *)NNS_FndGetArchiveFileByName(sFtrModelNamePtr));
            model = pb + *(u32 *)(pb + *(u16 *)(pb + 0xe) + 0xc);
            u32 i = 0;
            s32 z0 = 0, z1 = 0, z2 = 0, z3 = 0, z4 = 0;
            do {
                u8 *h;
                Str_SPrintf(name, "FTR:a/bca/bca%d", i);
                h = (u8 *)NNS_FndGetArchiveFileByName(name);
                if (h) {
                    animSet.setBca(func_021065f8(func_021065dc(h), z0), i);
                }
                Str_SPrintf(name, "FTR:a/bma/bma%d", i);
                h = (u8 *)NNS_FndGetArchiveFileByName(name);
                if (h) {
                    animSet.setBma(func_02106634(func_02106618(h), z1), i);
                }
                Str_SPrintf(name, "FTR:a/bva/bva%d", i);
                h = (u8 *)NNS_FndGetArchiveFileByName(name);
                if (h) {
                    animSet.setBva(func_021067a4(func_02106788(h), z2), i);
                }
                Str_SPrintf(name, "FTR:a/bta/bta%d", i);
                h = (u8 *)NNS_FndGetArchiveFileByName(name);
                if (h) {
                    animSet.setBta(func_02106670(func_02106654(h), z3), i);
                }
                Str_SPrintf(name, "FTR:a/btp/btp%d", i);
                h = (u8 *)NNS_FndGetArchiveFileByName(name);
                if (h) {
                    animSet.setBtp(func_021066ac(func_02106690(h), z4), i);
                }
                i++;
            } while (i < 2);
            NNS_FndUnmountArchive(&blk);
        }
    }
    if (texFile != 0 && model != 0) {
        return TRUE;
    }
    return FALSE;
}

FtrAnimSet *FtrModelRes::getAnimSet() {
    return &animSet;
}

void FtrModelRes::freeTexFile() {
    if (texFile != 0) {
        Mem_Free(texFile);
        texFile = 0;
    }
}

BOOL FtrModelRes::loadSync(ModelSlot *obj, s32 a, s32 flag) {
    void *h;
    keepTexCopy = flag;
    if (isLoaded()) {
        return TRUE;
    }
    item = Item_MakeFurniture(a, 0);
    loadFiles(obj, a);
    h = NNS_G3dGetTex(texFile);
    Gfx3d_LoadTexAndPltt(h, obj->getVramSlot());
    texture = Gfx3d_CopyTex(h, obj->getHeap());
    release();
    return TRUE;
}

BOOL FtrModelRes::loadAsync(ModelSlot *obj, s32 a, s32 flag) {
    if (isLoaded()) {
        return TRUE;
    }
    u16 t2;
    if (Unk_ov004_02206a44_IsInvalid(&item)) {
        item = Item_MakeFurniture(a, 0);
        keepTexCopy = flag;
    } else {
        t2 = Item_MakeFurniture(a, 0);
        if (!Unk_ov004_02206a44_Same(&t2, &item)) {
            return FALSE;
        }
    }
    loadFiles(obj, a);
    if (texture == 0) {
        void *p = NNS_G3dGetTex(texFile);
        TexVramSlot *x = obj->getVramSlot();
        void *y = obj->getHeap();
        if (texLoader.loadTexture(p, x, y) == 3) {
            texture = texLoader.getTexture();
            release();
            return TRUE;
        }
    }
    return FALSE;
}

void *FtrModelRes::getModel() {
    if (isLoaded()) {
        return model;
    }
    return 0;
}

void *FtrModelRes::getTexture() {
    if (isLoaded()) {
        return texture;
    }
    return 0;
}

void FtrModelRes::release() {
    item = 0xfff1;
    freeTexFile();
    texLoader.release();
    keepTexCopy = 0;
}

FtrCollider::FtrCollider() {
    clearOwner();
}

FtrCollider::~FtrCollider() {
}

void FtrCollider::setOwner(FtrActor *p) {
    owner = p;
}

void FtrCollider::clearOwner() {
    owner = 0;
}

void FtrCollider::onEdgeContact(CollisionEdge *a, Actor *b, s32 c) {
    CollisionVec2 v0, v1, v2, mid, d1, d2;
    volatile VecFx32Ctor pos;
    VecFx32Ctor w1, w2, buf;
    s32 t18, t1c, t20, t24, len2;
    s32 r7;
    s32 r5;
    s32 px, pz;
    void *chk = PlayerActor_GetActor(4);
    if (b != NULL && (void *)b == chk) {
        if (owner != NULL && owner->isAct(1)) {
            VecFx32Ctor *pv;
            t20 = Math_Atan2(a->normal.x, a->normal.y);
            t24 = t20 + 0x8000;
            r7 = (u16)(t24 - b->rotY);
            pv = (VecFx32Ctor *)&b->prevPosition;
            px = b->prevPosition.x;
            pos.x = px;
            pos.y = pv->y;
            pz = pv->z;
            pos.z = pz;
            v0.set(px, pz);
            v1.set(pos.x + a->normal.x, pos.z + a->normal.y);
            v2.set(0, 0);
            if ((u32)r7 < 0x1700 || (u32)r7 > 0xe900) {
                if (a->intersectLine(&v2, &v0, &v1)) {
                    r7 = FX_Sqrt(a->start.distSq(&v2));
                    len2 = FX_Sqrt(a->start.distSq(&a->end));
                    if (r7 >= 0x666) {
                        if (r7 <= len2 - 0x666) {
                            if (a->isBetweenEnds(&v2)) {
                                WallEdge_GetMidpoint(&mid, a);
                                t1c = mid.y + func_01ffcb0c(a->normal.y, c);
                                s32 x = mid.x + func_01ffcb0c(a->normal.x, c);
                                w1.x = x;
                                w1.y = 0;
                                w1.z = t1c;
                                w2.x = x;
                                w2.y = 0;
                                w2.z = t1c;
                                if (len2 > 0x3000) {
                                    if (r7 < 0x1000) {
                                        d1.setDiff(&a->end, &a->start);
                                        d1.normalize();
                                        v2.x = a->start.x + func_01ffcb0c(d1.x, 0x1000);
                                        v2.y = a->start.y + func_01ffcb0c(d1.y, 0x1000);
                                    } else if (r7 > 0x3000) {
                                        d2.setDiff(&a->end, &a->start);
                                        d2.normalize();
                                        v2.x = a->start.x + func_01ffcb0c(d2.x, 0x3000);
                                        v2.y = a->start.y + func_01ffcb0c(d2.y, 0x3000);
                                    }
                                    r7 = v2.y + func_01ffcb0c(a->normal.y, c);
                                    w2.x = v2.x + func_01ffcb0c(a->normal.x, c);
                                    w2.y = 0;
                                    w2.z = r7;
                                }
                                slideOwnerForWideFtr(b);
                                t18 = (s32)FtrActorTable_GetInstance()->indexOf(owner);
                                r5 = (s16)(t20 - owner->rotY);
                                if (FtrActor_GetLayer(owner) == 1) {
                                    FtrActor *q;
                                    FtrActor_GetCenter(owner, &buf);
                                    q = FtrActorGrid_GetInstance()->getActorAtPos(&buf, 0);
                                    if (q != NULL) {
                                        r5 = (s16)(t20 - q->rotY - owner->stackLink.getRelAngle());
                                    }
                                }
                                r5 = FtrActor_AngleToDir(r5);
                                FtrContactSet_GetInstance()->setContact(t18, &b->prevPosition, &b->position, c, &w1, &w2, (s16)t24, r5);
                            }
                        }
                    }
                }
            }
        }
    }
}

char sFtrArcPathBuf[0x28];
char sFtrTexPathBuf[0x28];
char sFtrModelName[] = "FTR:a/bmd/bmd0";
char *sFtrModelNamePtr = sFtrModelName;

FxVec3 FtrCollider_slideOwnerForWideFtr_tbl0[2] = {FxVec3(0, 0, 0), FxVec3(-0x2000, 0, 0)};
FxVec3 FtrCollider_slideOwnerForWideFtr_tbl1[2] = {FxVec3(0, 0, 0), FxVec3(0x2000, 0, 0)};
FxVec3 FtrCollider_slideOwnerForWideFtr_one(0x2000, 0, 0);
void FtrCollider::slideOwnerForWideFtr(Actor *b) {
    FtrActor *o;
    VecFx32Ctor tmp[2];
    o = owner;
    if (o->footprint == 1) {
        s32 r6;
        Mtx43_SetRotY(&data_021f47e0, owner->rotY);
        MTX_MultVec43(&FtrCollider_slideOwnerForWideFtr_one, &data_021f47e0, &tmp[0]);
        FtrActor_LocalToWorld(owner, &tmp[1], &FtrCollider_slideOwnerForWideFtr_tbl1[0]);
        r6 = Vec_Distance(&b->position, &tmp[1]);
        FtrActor_LocalToWorld(owner, &tmp[1], &FtrCollider_slideOwnerForWideFtr_tbl1[1]);
        if (r6 < Vec_Distance(&b->position, &tmp[1])) {
            if (Vec_NotEqual(&owner->modelOffset, &FtrCollider_slideOwnerForWideFtr_tbl0[0])) {
                VecFx32 *d = &owner->modelOffset;
                FxVec3 *s = &FtrCollider_slideOwnerForWideFtr_tbl0[0];
                d->x = s->x;
                d->y = s->y;
                d->z = s->z;
                VEC_Subtract(&owner->position, &tmp[0], &owner->position);
            }
        } else {
            if (Vec_NotEqual(&owner->modelOffset, &FtrCollider_slideOwnerForWideFtr_tbl0[1])) {
                VecFx32 *d = &owner->modelOffset;
                d->x = FtrCollider_slideOwnerForWideFtr_tbl0[1].x;
                d->y = FtrCollider_slideOwnerForWideFtr_tbl0[1].y;
                d->z = FtrCollider_slideOwnerForWideFtr_tbl0[1].z;
                VEC_Add(&owner->position, &tmp[0], &owner->position);
            }
        }
    }
}

FtrTileList::FtrTileList() {
    count = 0;
}

void FtrTileList::release() {}

BOOL FtrTileList::add(u32 a, u32 b) {
    if (count < 4) {
        tiles[count].x = a;
        tiles[count].y = b;
        count++;
        return TRUE;
    }
    return FALSE;
}

u32 FtrTileList::getCount() {
    return count;
}

Unk_ov004_02206520_Ent *FtrTileList::get(s32 i) {
    return &tiles[i & 3];
}

void FtrStackedSet::clear() {
    u32 i;
    count = 0;
    for (i = 0; i < 4; i++) {
        actors[i] = 0;
    }
}

void FtrStackedSet::collect(FtrTileList *l, s32 flag) {
    u32 i;
    if (flag == 0) {
        for (i = 0; i < l->getCount(); i++) {
            Unk_ov004_02206520_Ent *a = l->get(i);
            Unk_ov004_02206520_Ent *b = l->get(i);
            FtrActor *o = FtrActorGrid_GetInstance()->getActor(a->x, b->y, 1);
            if (o != NULL) {
                add(o);
            }
        }
    }
}

FtrStackedSet::FtrStackedSet(FtrTileList *l, s32 flag) {
    ((FtrStackedSet *)(this))->clear();
    collect(l, flag);
}

FtrStackedSet::FtrStackedSet() {
    ((FtrStackedSet *)(this))->clear();
}

u32 FtrStackedSet::getCount() {
    return count;
}

FtrActor *FtrStackedSet::get(u32 i) {
    return actors[i & 3];
}

BOOL FtrStackedSet::add(FtrActor *o) {
    u32 i;
    u32 n;
    if (o == NULL) {
        return FALSE;
    }
    n = count;
    if (n >= 4) {
        return FALSE;
    }
    for (i = 0; i < n; i++) {
        if (actors[i] == o) {
            return FALSE;
        }
    }
    count = count + 1;
    actors[n] = o;
    return TRUE;
}

void FtrAnimSet::clear() {
    u32 i;
    texCopy = 0;
    for (i = 0; i < 2; i++) {
        bca[i] = NULL;
        bma[i] = NULL;
        bta[i] = NULL;
        btp[i] = NULL;
    }
}

FtrAnimSet::~FtrAnimSet() {
}

void FtrAnimSet::setBca(void *v, u32 i) {
    bca[i & 1] = v;
}

void FtrAnimSet::setBma(void *v, u32 i) {
    bma[i & 1] = v;
}

void FtrAnimSet::setBva(void *v, u32 i) {
    bva[i & 1] = v;
}

void FtrAnimSet::setBta(void *v, u32 i) {
    bta[i & 1] = v;
}

void FtrAnimSet::setBtp(void *v, u32 i) {
    btp[i & 1] = v;
}

void FtrAnimSet::setTexCopy(void *v) {
    texCopy = v;
}

NNSG3dResAnmCommon *FtrAnimSet::getBca(u32 i) {
    return (NNSG3dResAnmCommon *)bca[i & 1];
}

NNSG3dResAnmCommon *FtrAnimSet::getBma(u32 i) {
    return (NNSG3dResAnmCommon *)bma[i & 1];
}

NNSG3dResAnmCommon *FtrAnimSet::getBva(u32 i) {
    return (NNSG3dResAnmCommon *)bva[i & 1];
}

NNSG3dResAnmCommon *FtrAnimSet::getBta(u32 i) {
    return (NNSG3dResAnmCommon *)bta[i & 1];
}

NNSG3dResAnmCommon *FtrAnimSet::getBtp(u32 i) {
    return (NNSG3dResAnmCommon *)btp[i & 1];
}

void *FtrAnimSet::getTexCopy() {
    if (texCopy != 0) {
        return NNS_G3dGetTex(texCopy);
    }
    return 0;
}

FtrTopItem::FtrTopItem() {
    item = 0xfff1;
    clear();
}

FtrTopItem::~FtrTopItem() {
}

BOOL FtrTopItem::isSet() {
    BOOL r;
    if (Item_IsFurniture(&item)) {
        u16 t = 0xfff1;
        if (Item_GetFurnitureIndex(&item) == Item_GetFurnitureIndex(&t)) {
            r = TRUE;
        } else {
            r = FALSE;
        }
    } else {
        if (item == 0xfff1) {
            r = TRUE;
        } else {
            r = FALSE;
        }
    }
    if (r) {
        return FALSE;
    }
    return TRUE;
}

void FtrTopItem::clear() {
    item = 0xfff1;
    relPos.x = 0;
    relPos.y = 0;
    relPos.z = 0;
}

VecFx32 *FtrTopItem::getPos() {
    return &relPos;
}

u16 *FtrTopItem::getItem() {
    return &item;
}

BOOL FtrTopItem::set(u16 *id, VecFx32 *pos) {
    if (isSet() == 0) {
        item = *id;
        relPos.x = pos->x;
        relPos.y = pos->y;
        relPos.z = pos->z;
        return TRUE;
    }
    return FALSE;
}

void FtrTopItem::draw(FtrActor *o) {
    if (isSet()) {
        VecFx32 z, d;
        VecFx32Copy p, s;
        data_021f47e0 = o->model.mtx;
        s32 x, y, c;
        c = getPos()->z;
        y = getPos()->y;
        x = getPos()->x;
        Mtx43_Translate(&data_021f47e0, x, y, c);
        z.x = 0;
        z.y = 0;
        z.z = 0;
        MTX_MultVec43(&z, &data_021f47e0, &d);
        p.x = d.x;
        p.y = d.y;
        p.z = d.z;
        s.x = 0x1000;
        s.y = 0x1000;
        s.z = 0x1000;
        RoomItemIcons_DrawItem(*getItem(), &p, &s, 0, 0, 0);
    }
}

FtrTopItems::FtrTopItems() {
    clearAll();
}

FtrTopItems::~FtrTopItems() {
}

void FtrTopItems::clearAll() {
    u32 i;
    for (i = 0; i < 4; i++) {
        get(i)->clear();
    }
}

FtrTopItem *FtrTopItems::get(u32 i) {
    if (i < 4) {
        return &items[i];
    }
    return &items[0];
}

void FtrTopItems::drawAll(FtrActor *o) {
    u32 i;
    for (i = 0; i < 4; i++) {
        get(i)->draw(o);
    }
}

BOOL FtrTopItems::add(u16 *id, VecFx32 *pos) {
    u32 i;
    for (i = 0; i < 4; i++) {
        if (get(i)->isSet() == 0) {
            get(i)->set(id, pos);
            return TRUE;
        }
    }
    return FALSE;
}

BOOL FtrTopItems::canPickUp(FtrActor *o) {
    FtrTileList list;
    o->getTiles((FtrTileList *)&list, 0, 0);
    BlockMap *grid = gSceneBlockMap;
    u32 i;
    for (i = 0; i < list.getCount(); i++) {
        s32 y = list.get(i)->y;
        s32 x = list.get(i)->x;
        s32 hx = x >> 4;
        s32 hy = y >> 4;
        u16 *cell = BlockMap_GetItemPtr(grid, hx, hy, x - (hx << 4), y - (hy << 4), 1);
        if (cell != NULL && !Item_IsFurnitureOrF031(cell) && !Item_IsNormalItem(cell)) {
            if (Unk_ov004_0220607c_IsEmpty(cell) == 0) {
                list.release();
                return FALSE;
            }
        }
    }
    list.release();
    return TRUE;
}

ItemId FtrTopItems_pickUpAll_dflt;
u8 FtrTopItems_pickUpAll_dflt_init;
BOOL FtrTopItems::pickUpAll(FtrActor *o) {
    if (!FtrTopItems_pickUpAll_dflt_init) {
        HOST_STATIC_INIT(FtrTopItems_pickUpAll_dflt, ItemId(0xfff1));
        FtrTopItems_pickUpAll_dflt_init = 1;
    }
    BOOL res = TRUE;
    FtrTileList list;
    o->getTiles((FtrTileList *)&list, 0, 0);
    BlockMap *grid = gSceneBlockMap;
    if (canPickUp(o)) {
        clearAll();
        FtrActor_CalcWorldMtx((FtrActor *)o, 0, 0);
        MTX_Inverse43(&data_021f47e0, &data_021f47e0);
        u32 i;
        for (i = 0; i < list.getCount(); i++) {
            s32 x = list.get(i)->x;
            s32 y = list.get(i)->y;
            s32 hx = x >> 4;
            s32 hy = y >> 4;
            u16 *cell = BlockMap_GetItemPtr(grid, hx, hy, x - (hx << 4), y - (hy << 4), 1);
            if (cell != NULL && Item_IsNormalItem(cell)) {
                VecFx32 v, d;
                FieldPos_FromUnitCenter(&v, x, y);
                v.y = o->surfaceHeight;
                MTX_MultVec43(&v, &data_021f47e0, &d);
                res &= add(cell, &d);
                if (res != 0) {
                    res = 1;
                } else {
                    res = 0;
                }
            }
        }
        if (res == 0) {
            clearAll();
        }
    }
    list.release();
    return res;
}

void FtrTopItems::dropAll(FtrActor *o) {
    u32 i;
    for (i = 0; i < 4; i++) {
        FtrTopItem *e = get(i);
        if (e->isSet()) {
            VecFx32 z, d;
            s32 a, b;
            z.x = 0;
            z.y = 0;
            z.z = 0;
            data_021f47e0 = o->model.mtx;
            s32 x, y, c;
            c = e->getPos()->z;
            y = e->getPos()->y;
            x = e->getPos()->x;
            Mtx43_Translate(&data_021f47e0, x, y, c);
            MTX_MultVec43(&z, &data_021f47e0, &d);
            FieldPos_ToUnit(&a, &b, &d);
            u32 mgr = Scene_GetCurrent();
            FtrSync_SetTopItem(mgr, a, b, e->getItem(), 1);
        }
    }
    clearAll();
}

void FtrStackLink::clear() {
    parentIndex = -1;
    relPos.x = 0;
    relPos.y = 0;
    relPos.z = 0;
    relAngle = 0;
}

FtrStackLink::~FtrStackLink() {
}

BOOL FtrStackLink::isAttached() {
    BOOL r = FALSE;
    if (parentIndex != -1) {
        r = TRUE;
    }
    return r;
}

s32 FtrStackLink::getParentIndex() {
    return parentIndex;
}

VecFx32 *FtrStackLink::getRelPos() {
    return &relPos;
}

s32 FtrStackLink::getRelAngle() {
    return relAngle;
}

BOOL FtrStackLink::set(s32 idx, VecFx32 *pos, s32 ang) {
    if (idx >= 0 && (u32)idx < 0x1c) {
        parentIndex = idx;
        relPos.x = pos->x;
        relPos.y = pos->y;
        relPos.z = pos->z;
        relAngle = ang;
        return TRUE;
    }
    return FALSE;
}

BOOL FtrStackLink::attachAt(s32 x, s32 y, s16 z) {
    s32 idx;
    VecFx32 pos;
    s16 ang;
    if (FtrStack_CalcRelPlacement(&idx, &pos, &ang, x, y, z)) {
        return set(idx, &pos, ang);
    }
    return FALSE;
}

extern "C" BOOL FtrStack_CalcRelPlacement(s32 *idx, VecFx32 *pos, s16 *ang, s32 x, s32 a, s16 b) {
    FtrActor *e = FtrActorGrid_GetInstance()->getActor(x, a, 0);
    s32 i = FtrActorTable_GetInstance()->indexOf(e);
    if (e != NULL && i != -1) {
        VecFx32 t;
        VecFx32 d;
        FieldPos_FromUnitCenter(&t, x, a);
        t.y = e->surfaceHeight;
        FtrActor_CalcWorldMtx((FtrActor *)e, 0, 0);
        MTX_Inverse43(&data_021f47e0, &data_021f47e0);
        MTX_MultVec43(&t, &data_021f47e0, &d);
        *idx = i;
        pos->x = d.x;
        pos->y = d.y;
        pos->z = d.z;
        *ang = b - e->rotY;
        return TRUE;
    }
    return FALSE;
}

void FtrClockHands::clear() {
    minJnt = -1;
    hourJnt = minJnt;
    valid = 0;
}

FtrClockHands::~FtrClockHands() {
}

void FtrClockHands::set(s32 a, s32 b) {
    hourJnt = a;
    minJnt = b;
    if (hourJnt == -1 && minJnt == -1) {
    } else {
        valid = 1;
    }
}

void FtrSwitch::clear() {
    next = 0;
    cur = next;
}

FtrSwitch::~FtrSwitch() {
}

void FtrSwitch::loadFromMap(FtrActor *o) {
    s32 r = 0;
    s32 x, y;
    if (o->spawnMode == 1 || o->isPreview() != 0) {
        if (o->startsOff == 0) {
            r = 1;
        } else {
            r = 0;
        }
    } else {
        if (o->findOwnTile(&x, &y, NULL, 0)) {
            u32 mgr = Scene_GetCurrent();
            r = RoomFtrState_GetSwitch(x, y, o->mapLayer, mgr);
        }
    }
    set(r, 0);
}

void FtrSwitch::commit(FtrActor *o) {
    if (o->isPreview() == 0) {
        cur = next;
    }
}

void FtrSwitch::saveToMap(FtrActor *o) {
    if (o->isPreview() == 0) {
        s32 x, y;
        if (o->findOwnTile(&x, &y, 0, 0)) {
            RoomFtrState_SetSwitch(x, y, o->mapLayer, next, Scene_GetCurrent());
        }
    }
}

u8 FtrSwitch::isOn() {
    return next;
}

BOOL FtrSwitch::isChanging() {
    if (cur != next) {
        return TRUE;
    }
    return FALSE;
}

void FtrSwitch::toggle(s32 flag) {
    set(((next + 1) & 1) != 0 ? TRUE : FALSE, flag);
}

void FtrSwitch::set(u32 v, s32 flag) {
    if (flag != 0) {
        next = v;
    } else {
        cur = v;
        next = cur;
    }
}

FtrGlowMat::FtrGlowMat() {
    matIdx = -1;
    resMdl = NULL;
}

FtrGlowMat::~FtrGlowMat() {
}

BOOL FtrGlowMat::bindMaterial(G3dResAccess *res, const char *idx, BOOL on) {
    if (res != NULL) {
        matIdx = res->findMatIdx(idx);
        if (matIdx != -1) {
            switchLightAnimated(on);
            resMdl = res;
            return TRUE;
        }
    }
    return FALSE;
}

BOOL FtrGlowMat::setLit(BOOL on, s32 a, s32 b) {
    return switchLight(on, a, b, 0x800);
}

void FtrGlowMat::updateEmission() {
    if (matIdx != -1) {
        ((LightLevel *)(this))->update();
        s32 x = ((LightLevel *)(this))->getLevel();
        if (x) {
            NNSi_G3dModifyMatFlag(resMdl, 1, 0x400);
            s32 col = FtrGlowMat_GetBaseEmission();
            s32 r7 = Math_LerpFx(x, ((col >> 10) & 0x1f) << 12, 0x1f000);
            s32 g = Math_LerpFx(x, (col & 0x1f) << 12, 0x1f000);
            s32 b = Math_LerpFx(x, ((col >> 5) & 0x1f) << 12, 0x1f000);
            u32 r7c = (u16)(((r7 >> 12) << 10) | ((g >> 12) | ((b >> 12) << 5)));
            for (s32 i = 0; i < ((Unk_ov004_02205b14_Obj *)resMdl)->numMat; i++) {
                NNS_G3dMdlSetMdlEmi(resMdl, i, i == matIdx ? r7c : col);
            }
        } else {
            NNSi_G3dModifyMatFlag(resMdl, 0, 0x400);
        }
    }
}

extern "C" u16 FtrGlowMat_GetBaseEmission() {
    return (u16)(data_027e00c8.prmMatColor1 >> 16);
}

FtrGlowMatSet::FtrGlowMatSet() {
    anyBound = 0;
}

FtrGlowMatSet::~FtrGlowMatSet() {}

u32 FtrGlowMatSet::init(void *a, u32 b) {
    u32 i = 0;
    anyBound = 0;
    u8 *pf = &anyBound;
    u32 z = 0;
    for (i = 0; i < 3; i++) {
        u32 r = mats[i].bindMaterial((G3dResAccess *)a, sFtrGlowMatNames[i], b);
        u32 t = *pf | r;
        if (t != 0) t = 1; else t = z;
        *pf = t;
    }
    return anyBound;
}

u32 FtrGlowMatSet::setLit(u32 a, u32 b, u32 c) {
    u32 r = 0;
    if (anyBound != 0) {
        u32 z = 0;
        for (FtrGlowMat *p = mats; p < (FtrGlowMat *)&anyBound; p++) {
            r |= p->setLit(a, b, c);
            if (r != 0) r = 1; else r = z;
        }
    }
    return r;
}

void FtrGlowMatSet::update() {
    if (anyBound != 0) {
        FtrGlowMat *p = mats;
        FtrGlowMat *end = (FtrGlowMat *)&anyBound;
        for (; p < end; p++) p->updateEmission();
    }
}

extern "C" void FtrVisNodes_Construct(void *) {}

extern "C" void FtrVisNodes_Destruct(void *) {}

void FtrVisNodes::init(void *p, u32 v) {
    if (p) {
        for (u32 i = 0; i < 4; i++) {
            nodeIds[i] = ((G3dResAccess *)(p))->findNodeIdx((const char *)(sFtrVisNodeNames[i]));
        }
        setVisible(v);
    }
}

void FtrVisNodes::setVisible(u32 v) { visible = v; }

BOOL FtrVisNodes::hasNode(s32 v) {
    for (u32 i = 0; i < 4; i++) {
        if (v == nodeIds[i]) return TRUE;
    }
    return FALSE;
}

u8 FtrVisNodes::isVisible() { return visible; }

BOOL FtrActor::startRotate(s32 a) {
    if (canRotateBy(a)) {
        targetAngle = rotY + a;
        setAct(2);
        PlayerActor_PlayLocalSe(0x4c4);
        return TRUE;
    }
    return FALSE;
}

BOOL FtrActor::startPush(s16 a) {
    VecFx32 v;
    v.x = 0;
    v.y = 0;
    v.z = 0x2000;
    Vec_RotateY(&v, a);
    if (canMoveBy(&v)) {
        VecFx32 w;
        Vec_Add(&w, (VecFx32 *)&position, &v);
        targetPos.x = w.x;
        targetPos.y = w.y;
        targetPos.z = w.z;
        targetAngle = a;
        setAct(3);
        if (!Unk_ov004_02205820_Is3d(profile)) {
            u32 t = FtrActor_GetDragSe();
            if (t != 0xffff) PlayerActor_PlayLocalSe(t);
        }
        return TRUE;
    }
    return FALSE;
}

BOOL FtrActor::startPull(s16 a) {
    VecFx32 v;
    v.x = 0;
    v.y = 0;
    v.z = 0x2000;
    Vec_RotateY(&v, (s16)(a + 0x8000));
    if (canMoveBy(&v)) {
        VecFx32 w;
        Vec_Add(&w, (VecFx32 *)&position, &v);
        targetPos.x = w.x;
        targetPos.y = w.y;
        targetPos.z = w.z;
        targetAngle = a;
        setAct(4);
        if (!Unk_ov004_02205820_Is3d(profile)) {
            u32 t = FtrActor_GetDragSe();
            if (t != 0xffff) PlayerActor_PlayLocalSe(t);
        }
        return TRUE;
    }
    return FALSE;
}

BOOL FtrActor::startHide() { return setAct(6); }

BOOL FtrActor::isIdle() { return isAct(1); }

BOOL FtrActor::isNotIdle() {
    if (isIdle() == 0) return TRUE;
    return FALSE;
}

BOOL FtrActor::isReady() { return isAct(1); }

BOOL FtrActor::isNotReady() {
    if (isReady() == 0) return TRUE;
    return FALSE;
}

BOOL FtrActor::isRemoving() { return isAct(5); }

BOOL FtrActor::isHidden() { return isAct(7); }

BOOL FtrActor::isAct(s32 s) {
    if (baseAct == s) return TRUE;
    return FALSE;
}

char data_ov004_02248710[] = "mn_m";
char data_ov004_02248718[] = "mn_m0";
char data_ov004_02248720[] = "mn_m1";
char *sFtrGlowMatNames[3] = {data_ov004_02248710, data_ov004_02248718, data_ov004_02248720};
char data_ov004_022486fc[] = "v";
char data_ov004_02248704[] = "v1";
char data_ov004_02248708[] = "v2";
char data_ov004_02248700[] = "v3";
char *sFtrVisNodeNames[4] = {data_ov004_022486fc, data_ov004_02248704, data_ov004_02248708, data_ov004_02248700};

BOOL FtrActor::setAct(s32 idx) {
    static Unk_ov004_0224882c_Fn tbl[9] = {
        &FtrActor::enterAppear, &FtrActor::enterIdle,
        &FtrActor::enterRotate, &FtrActor::enterPush,
        &FtrActor::enterPull, &FtrActor::enterRemove,
        &FtrActor::enterHide, &FtrActor::enterIdle,
        &FtrActor::enterPreview,
    };
    if (idx < 9) {
        if ((this->*tbl[idx])()) {
            baseAct = idx;
            return TRUE;
        }
    }
    return FALSE;
}

Unk_ov004_0224882c_Fn FtrActor_execAct_tbl[9];
u8 FtrActor_execAct_tbl_init;
void FtrActor::execAct() {
    if (!FtrActor_execAct_tbl_init) {
        HOST_STATIC_INIT_ARRAY(FtrActor_execAct_tbl, {
        (Unk_ov004_0224882c_Fn)&FtrActor::execAppear, (Unk_ov004_0224882c_Fn)&FtrActor::execIdle,
        (Unk_ov004_0224882c_Fn)&FtrActor::execRotate, (Unk_ov004_0224882c_Fn)&FtrActor::execPush,
        (Unk_ov004_0224882c_Fn)&FtrActor::execPull, (Unk_ov004_0224882c_Fn)&FtrActor::execRemove,
        (Unk_ov004_0224882c_Fn)&FtrActor::execHide, (Unk_ov004_0224882c_Fn)&FtrActor::execIdle,
        (Unk_ov004_0224882c_Fn)&FtrActor::execPreview,
    });
        FtrActor_execAct_tbl_init = 1;
    }
    if (baseAct < 9) (this->*FtrActor_execAct_tbl[baseAct])();
}

BOOL FtrActor::enterAppear() {
    colliderScale = 0x555;
    drawScale = 0;
    drawScaleY = 0;
    drawScaleZ = 0;
    appearFrame = 0;
    wobblePhase = 0;
    wobbleSpeed = 0x2710;
    wobbleAmp = 0x800;
    if (PlayerActor_GetActor(4)) {
        VecFx32 pos;
        u16 t;
        FtrActor_GetCenter(this, &pos);
        if (mapLayer == 0) pos.y = 0;
        else pos.y = FtrMgr_GetSurfaceHeightAtPos(&pos);
        pos.y += 0x800;
        t = Item_MakeFurniture(ftrIndex, 0);
        VecFx32Copy c;
        c.x = pos.x;
        c.y = pos.y;
        c.z = pos.z;
        return ItemDrop_StartFromLocalPlayer(&t, &c);
    }
    return TRUE;
}

void FtrActor::execAppear() {
    Math_StepS32(&colliderScale, 0x1000, 0x88);
    if (appearFrame < 0xf) {
        appearFrame = appearFrame + 1;
        actFrame = 0;
        if (appearFrame == 0xc) PlayerActor_PlayLocalSe(0x4c7);
        if (appearFrame == 0xf) {
            FtrCenterPosBuf buf;
            FtrActor_GetCenter(this, &buf.pos);
            spawnEffectAt(&buf.pos);
        }
    } else if (appearFrame < 0x11) {
        appearFrame = appearFrame + 1;
    } else {
        s16 r6 = wobblePhase;
        u16 r4;
        u16 *q = (u16 *)&wobblePhase;
        *q = *q + wobbleSpeed;
        r4 = *q;
        s32 m = func_01ffcb0c(wobbleAmp, data_02135f44[((u16)(volatile s16)r4 >> 4) * 2]);
        s32 t = 0x1000;
        drawScaleY = m + t;
        s32 *pp = &drawScale;
        *pp = t - m;
        drawScaleZ = *pp;
        s32 c = func_01ffcb0c(data_02135f44[((u16)r6 >> 4) * 2], data_02135f44[((u16)(volatile s16)r4 >> 4) * 2]);
        if (c < 0) {
            wobbleAmp = func_01ffcb0c(wobbleAmp, 0x4cd);
            wobbleSpeed = wobbleSpeed + 0x960;
        }
        if (colliderScale == 0x1000) {
            s32 v = wobbleAmp;
            if (v < 0) v = -v;
            if (v < 0x52) setAct(1);
        }
        switch (actFrame) {
        case 0:
            spawnEffectAtCorner(0);
            spawnEffectAtCorner(2);
            break;
        case 2:
            spawnEffectAtCorner(1);
            spawnEffectAtCorner(3);
            break;
        }
        actFrame = actFrame + 1;
    }
}

BOOL FtrActor::enterIdle() { return TRUE; }

void FtrActor::execIdle() {}

BOOL FtrActor::enterRotate() {
    topItems.pickUpAll(this);
    s32 d = (s16)(targetAngle - rotY);
    moveTiles(0, d);
    if (d < 0) d = 1; else d = 0;
    onRotateStart(d);
    if (mapLayer == 0 && hasTopSurface == 1) {
        FtrTileList v;
        getTiles((FtrTileList *)&v, 0, 0);
        for (u32 i = 0; i < v.getCount(); i++) {
            Unk_ov004_02206520_Ent *e = v.get(i);
            FtrActor *o = FtrActorGrid_GetInstance()->getActor(e->x, v.get(i)->y, 1);
            if (o) o->onRotateStart(d);
        }
        v.release();
    }
    return TRUE;
}

void FtrActor::execRotate() {
    s32 d = (s16)(targetAngle - rotY);
    BOOL neg;
    if (d < 0) neg = TRUE; else neg = FALSE;
    onRotateUpdate(neg);
    if (mapLayer == 0 && hasTopSurface == 1) {
        FtrTileList v;
        getTiles((FtrTileList *)&v, 0, 0);
        for (u32 i = 0; i < v.getCount(); i++) {
            Unk_ov004_02206520_Ent *e = v.get(i);
            FtrActor *o = FtrActorGrid_GetInstance()->getActor(e->x, v.get(i)->y, 1);
            if (o) o->onRotateUpdate(neg);
        }
        v.release();
    }
    if (Math_StepAngle(&rotY, targetAngle, 0x700)) {
        setAct(1);
        topItems.dropAll(this);
    }
}

BOOL FtrActor::enterPush() {
    FtrCenterPosBuf buf;
    Vec_Sub(&buf.pos, &targetPos, &position);
    topItems.pickUpAll(this);
    moveTiles(&buf.pos, 0);
    FtrMoveAnim *g = (FtrMoveAnim *)FurnitureManager_GetMoveAnim();
    if (g) {
        if (FtrMoveAnim_StartPush(g, &moveFlag, &position, targetAngle)) {
            onMoveStart(TRUE);
            spawnActorC0AtTile(0);
            return TRUE;
        }
    }
    return FALSE;
}

void FtrActor::execPush() {
    VecFx32 buf;
    FtrMoveAnim *g = (FtrMoveAnim *)FurnitureManager_GetMoveAnim();
    if (g) {
        if (FtrMoveAnim_Step(g, &moveFlag, &buf)) {
            position.x = targetPos.x;
            position.y = targetPos.y;
            position.z = targetPos.z;
            setAct(1);
            topItems.dropAll(this);
        } else {
            position.x = buf.x;
            position.y = buf.y;
            position.z = buf.z;
        }
    }
}

BOOL FtrActor::enterPull() {
    FtrCenterPosBuf buf;
    Vec_Sub(&buf.pos, &targetPos, &position);
    topItems.pickUpAll(this);
    moveTiles(&buf.pos, 0);
    FtrMoveAnim *g = (FtrMoveAnim *)FurnitureManager_GetMoveAnim();
    if (g) {
        if (FtrMoveAnim_StartPull(g, &moveFlag, &position, targetAngle)) {
            onMoveStart(FALSE);
            spawnActorC0AtTile(1);
            return TRUE;
        }
    }
    return FALSE;
}

void FtrActor::execPull() {
    execPush();
}

BOOL FtrActor::enterRemove() {
    VecFx32 buf;
    onRemove();
    actFrame = 0;
    FtrActor_GetCenter(this, &buf);
    FtrMgr_SetRemovePos(&buf);
    PlayerActor_PlayLocalSe(0x4c8);
    return TRUE;
}

void FtrActor::execRemove() {
    FtrCenterPosBuf buf;
    Math_StepS32(&drawScale, 0, 0x400);
    drawScaleY = drawScaleZ = drawScale;
    if (drawScale == 0) {
        ProcBase_RequestDelete(this);
    }
    if (actFrame == 1) {
        FtrActor_GetCenter(this, &buf.pos);
        spawnEffectAt(&buf.pos);
    }
    actFrame++;
}

BOOL FtrActor::enterHide() {
    return enterRemove();
}

void FtrActor::execHide() {
    FtrCenterPosBuf buf;
    Math_StepS32(&drawScale, 0, 0x400);
    drawScaleY = drawScaleZ = drawScale;
    if (drawScale == 0) {
        setAct(7);
    } else if (actFrame == 1) {
        FtrActor_GetCenter(this, &buf.pos);
        spawnEffectAt(&buf.pos);
    }
    actFrame++;
}

BOOL FtrActor::enterPreview() {
    return TRUE;
}

void FtrActor::execPreview() {
    if (kind != 0x23 && kind != 0x24 && kind != 0x25) {
        rotY += 0x400;
    }
    s32 v = FX_Div(FtrInfo_GetDmaUnk05Fx(FtrActor_GetFtrIndex(this)), 0x64000) >> 2;
    drawScale = drawScaleY = drawScaleZ = v;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_02204f24) {
    HOST_OVERLAY_VAR(data_ov004_0224f60c),
    HOST_OVERLAY_VAR(data_ov004_0224f62c),
    HOST_OVERLAY_VAR(data_ov004_0224f63c),
    HOST_OVERLAY_VAR(data_ov004_0224f608),
    HOST_OVERLAY_VAR(data_ov004_0224f61c),
    HOST_OVERLAY_VAR(data_ov004_0224f618),
    HOST_OVERLAY_VAR(sFtrActorProfile),
    HOST_OVERLAY_VAR(data_ov004_0224f88c),
    HOST_OVERLAY_VAR(data_ov004_0224f8bc),
    HOST_OVERLAY_VAR(data_ov004_0224f8ec),
    HOST_OVERLAY_VAR(sFtrPreviewYaw),
    HOST_OVERLAY_VAR(sFtrFootprintCorners),
    HOST_OVERLAY_VAR(gFtrSoundNone),
    HOST_OVERLAY_VAR(FtrActor_getInteractionPos_v),
    HOST_OVERLAY_VAR(FtrActor_getInteractionPos_v_init),
    HOST_OVERLAY_VAR(sFtrPreviewPitch),
    HOST_OVERLAY_VAR(FtrActor_getTiles_s),
    HOST_OVERLAY_VAR(FtrActor_writeTiles_s0),
    HOST_OVERLAY_VAR(FtrActor_writeTiles_s1),
    HOST_OVERLAY_VAR(sFtrArcPathBuf),
    HOST_OVERLAY_VAR(sFtrTexPathBuf),
    HOST_OVERLAY_VAR(sFtrModelName),
    HOST_OVERLAY_VAR(sFtrModelNamePtr),
    HOST_OVERLAY_VAR(FtrCollider_slideOwnerForWideFtr_tbl0),
    HOST_OVERLAY_VAR(FtrCollider_slideOwnerForWideFtr_tbl1),
    HOST_OVERLAY_VAR(FtrCollider_slideOwnerForWideFtr_one),
    HOST_OVERLAY_VAR(FtrTopItems_pickUpAll_dflt),
    HOST_OVERLAY_VAR(FtrTopItems_pickUpAll_dflt_init),
    HOST_OVERLAY_VAR(data_ov004_02248710),
    HOST_OVERLAY_VAR(data_ov004_02248718),
    HOST_OVERLAY_VAR(data_ov004_02248720),
    HOST_OVERLAY_VAR(sFtrGlowMatNames),
    HOST_OVERLAY_VAR(data_ov004_022486fc),
    HOST_OVERLAY_VAR(data_ov004_02248704),
    HOST_OVERLAY_VAR(data_ov004_02248708),
    HOST_OVERLAY_VAR(data_ov004_02248700),
    HOST_OVERLAY_VAR(sFtrVisNodeNames),
    HOST_OVERLAY_VAR(FtrActor_execAct_tbl),
    HOST_OVERLAY_VAR(FtrActor_execAct_tbl_init),
    HOST_OVERLAY_VARS_END
};
