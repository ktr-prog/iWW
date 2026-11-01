#include "uptr.h"
#include "host_tick.h"
#include "host_labels.h"
#include "host_overlay_vars.h"
#include "types.h"
#include "gfx/CachedModel.h"
#include "gfx/ModelSlotPool.h"
#include "room/FtrManager.h"
#include "gfx/VecFx32.h"
#include "room/Unk_ov004_0224882c_Buf.h"
#include "gfx/Mtx43.h"
#include "actor/ActorProfile.h"
#include "actor/ActorListNode.h"
#include "actor/CharacterListNode.h"
#include "room/FtrActorParts.h"
#include "gfx/AnimFrameCtrl.h"
#include "item/ItemId.h"
#include "game/CollisionVec2.h"
#include "game/LightLevel.h"
#include "gfx/G3dResAccess.h"
#include "room/FtrVisNodes.h"
#include "room/FtrSwitch.h"
#include "room/FtrClockHands.h"
#include "room/FtrAnimSet.h"
#include "room/FtrStackedSet.h"
#include "talk/TalkWindowState.h"
#include "game/BoxCollider.h"
#include "game/CollisionEdge.h"
#include "room/FtrTileList.h"
#include "room/FtrGlowMat.h"
#include "room/FtrStackLink.h"
#include "room/FtrTopItem.h"
#include "game/FxVec3.h"
#include "sys/ProcBase.h"
#include "snd/Melody.h"
#include "gfx/ModelAnim.h"
#include "room/FtrCollider.h"
#include "gfx/MatTexVramTask.h"
#include "room/FtrGlowMatSet.h"
#include "room/FtrTopItems.h"
#include "room/FtrModelAnim.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "gfx/ModelResource.h"
#include "room/FtrModelRes.h"
#include "talk/MsgRequest.h"
#include "talk/TalkMsgRequest.h"
#include "room/FtrActor.h"
#include "room/FtrNookway.h"
#include "room/FtrPhone.h"
#include "room/FtrSingingInsect.h"
#include "room/FtrComputer.h"
#include "room/FtrHeadwear.h"
#include "room/FtrKind25.h"
#include "room/FtrCarpetSample.h"
#include "net/CommManager.h"
#include "nitro/mtx.h"
#include "gfx/NNSG3dRS.h"
#include "game/GroundInfo.h"
#include "game/GroundInfoBase.h"
#include "gfx/AnimModel.h"
#include "gfx/Model.h"
#include "gfx/TwoLayerAnimModel.h"
#include "item/ItemName.h"
#include "player/PlayerData.h"
#include "player/PlayerId.h"
#include "player/PlayerInventory.h"
#include "room/FtrPreviewer.h"
#include "snd/SndSeEmitter.h"
#include "talk/ChoiceList.h"
#include "proto/main/unk_020b4828.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/ov004/unk_ov004_02209f70.h"
#include "proto/ov004/unk_ov004_02233074.h"
extern "C" void *FtrMoveAnim_GetHaniwaAnim(FtrMoveAnim *r);
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0203a0cc.h"
#include "proto/main/unk_02034438.h"
#include "proto/main/unk_0203c23c.h"
#include "proto/main/unk_020514a4.h"
#include "proto/main/unk_02052b50.h"
#include "proto/main/unk_02060034.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_0209eb94.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/ov004/unk_ov004_0221e7a8.h"
#include "proto/autoload_2/unk_020f4a5c.h"
#include "proto/main/unk_02070560.h"
#include "proto/main/unk_020b8cd0.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_0203c638.h"
#include "proto/itcm/unk_01ffb4e8.h"
#include "proto/main/unk_02055c38.h"
#include "proto/main/unk_0204cc1c.h"
#include "proto/ov004/unk_ov004_02204f24.h"
#include "proto/main/unk_0204a780.h"
#include "proto/main/unk_0203d4d8.h"
#include "proto/autoload_2/unk_020e92f4.h"


extern "C" {
extern CommManager *gCommManager;
u32 Scene_GetCurrent(void);
BOOL Math_StepS32(s32 *p, s32 target, s32 step);
}

extern "C" {
extern const u8 data_ov004_02240024[2];
extern const u8 data_ov004_02240028[2];
extern const u8 data_ov004_0224002c[2];
extern const u8 data_ov004_02240030[2];
extern const u8 data_ov004_02240034[2];
extern const u8 data_ov004_02240038[2];
extern const u8 data_ov004_0224003c[2];
extern const u8 data_ov004_02240040[3];
extern const u8 data_ov004_02240044[3];
extern const u8 data_ov004_02240048[4];
extern const u8 data_ov004_0224004c[4];
extern const u8 data_ov004_02240050[4];
extern const u8 data_ov004_02240054[4];
extern const u8 data_ov004_02240058[4];
extern const u8 data_ov004_0224005c[4];
extern const u8 data_ov004_02240060[4];
extern const u8 data_ov004_02240064[5];
extern const u32 sFtrStorageKinds[3];
}

struct FtrBedLieOffsetRow {
    FxVec3 *offsets;
    u32 count;
};
extern "C" {
extern const FtrBedLieOffsetRow sFtrBedLieOffsets[3];
}







































class TexVramSlot;













class FtrActor;
class ModelSlot;









namespace p10 {
extern "C" {
extern u16 gFtrSoundNone;




u32 ItemInfo_IsReady(void);
}
}



BOOL FtrNookway::onDelete() { return TRUE; }
BOOL FtrNookway::updateActive() { return TRUE; }

BOOL FtrNookway::initModel() {
    startFrame = p10::ItemInfo_IsReady();
    initAnims(0, 0, 0, (u16)startFrame);
    FtrActor_StepAnims(this);
    return TRUE;
}

FtrNookway::~FtrNookway() {}

FtrNookway::FtrNookway() {}

extern "C" void *FtrNookway_Create() {
    return new FtrNookway;
}

void FtrPhone::execTalkAct04() {
    if (talkDelay == 0) {
        TalkRequest_SetTargetDone(this);
    }
    if (talkDelay != 0) {
        talkDelay -= TICK_STEP_ENDS() ? 1 : 0;
    }
}

BOOL FtrPhone::enterTalkAct04() {
    changeAct(3, 0xff);
    talkDelay = 1;
    return TRUE;
}

void FtrPhone::execTalkAct03() {
    if (window != 0) {
        if (window->state == 0) {
            detachTalkRequest((TalkMsgRequest *)this);
            setTalkAct(4);
        }
    }
}

BOOL FtrPhone::enterTalkAct03() { return TRUE; }

void FtrPhone::execTalkAct02() {
    if (window != 0) {
        if (window->state != 0) {
            setTalkAct(3);
        }
    }
}


BOOL FtrPhone::enterTalkAct02() {
    StackPad8 pad;
    attachTalkRequest((TalkMsgRequest *)this);
    window->nextState = 1;
    TalkMsgRequest &s = *this;
    s.setFileName(data_ov004_0224bb44);
    msgIndex = 0;
    return TRUE;
}

void FtrPhone::execTalkAct01() {
    if (talkDelay == 0) {
        setTalkAct(2);
    }
    if (talkDelay != 0) {
        talkDelay -= TICK_STEP_ENDS() ? 1 : 0;
    }
}

BOOL FtrPhone::enterTalkAct01() {
    changeAct(1, 0xff);
    talkDelay = 1;
    return TRUE;
}

void FtrPhone::execTalkAct00() {
    if (switchState.isChanging()) {
        void *a = FtrContactSet_GetInstance();
        void *b = ((FtrContactSet *)(a))->findContact(this);
        s32 *v = &((FtrContact *)(b))->getClampedContactPoint()->x;
        contactPoint = v[0];
        contactPointY = v[1];
        contactPointZ = v[2];
        pushAngle = ((FtrContact *)(b))->getPushAngle();
        TalkRequest_AddPlayerTalk6(this, 0);
    }
    switchState.set(0, 0);
}

BOOL FtrPhone::enterTalkAct00() { return TRUE; }

typedef void (FtrPhone::*Unk_ov004_0220a1e8_Fn)();
typedef BOOL (FtrPhone::*Unk_ov004_0220a280_Fn)();

void FtrPhone::execTalkAct() {
    static Unk_ov004_0220a1e8_Fn tbl[5] = {
        &FtrPhone::execTalkAct00,
        &FtrPhone::execTalkAct01,
        &FtrPhone::execTalkAct02,
        &FtrPhone::execTalkAct03,
        &FtrPhone::execTalkAct04,
    };
    if (talkAct < 5) {
        (this->*tbl[talkAct])();
    }
}

BOOL FtrPhone::setTalkAct(s32 idx) {
    static Unk_ov004_0220a280_Fn tbl[5] = {
        &FtrPhone::enterTalkAct00,
        &FtrPhone::enterTalkAct01,
        &FtrPhone::enterTalkAct02,
        &FtrPhone::enterTalkAct03,
        &FtrPhone::enterTalkAct04,
    };
    if (idx < 5) {
        if ((this->*tbl[idx])()) {
            talkAct = idx;
            return TRUE;
        }
    }
    return FALSE;
}

void FtrPhone::execFtrAct03() {
    changeAct(0, 0xff);
}

BOOL FtrPhone::enterFtrAct03() {
    switchState.set(0, 0);
    playSound1();
    return TRUE;
}

void FtrPhone::execFtrAct02() {}

BOOL FtrPhone::enterFtrAct02() {
    switchState.set(1, 0);
    return TRUE;
}

void FtrPhone::execFtrAct01() {
    changeAct(2, 0xff);
}

BOOL FtrPhone::enterFtrAct01() {
    switchState.set(1, 0);
    playSound1();
    return TRUE;
}

void FtrPhone::execFtrAct00() {}

BOOL FtrPhone::enterFtrAct00() {
    switchState.set(0, 0);
    return TRUE;
}

void FtrPhone::execFtrAct() {
    static Unk_ov004_0220a1e8_Fn tbl[4] = {
        &FtrPhone::execFtrAct00,
        &FtrPhone::execFtrAct01,
        &FtrPhone::execFtrAct02,
        &FtrPhone::execFtrAct03,
    };
    if (ftrAct < 4) {
        (this->*tbl[ftrAct])();
    }
}

BOOL FtrPhone::changeAct(u32 a, u8 b) {
    FtrActor::changeAct(a, b);
    static Unk_ov004_0220a280_Fn tbl[4] = {
        &FtrPhone::enterFtrAct00,
        &FtrPhone::enterFtrAct01,
        &FtrPhone::enterFtrAct02,
        &FtrPhone::enterFtrAct03,
    };
    if (a < 4) {
        if ((this->*tbl[a])()) {
            ftrAct = a;
            return TRUE;
        }
    }
    return FALSE;
}

u8 FtrPhone::getActSwitchState(u32 a) {
    if (a < 4) {
        return data_ov004_0224004c[a];
    }
    return 0;
}

void FtrPhone::onInteractionEvent(u32 a, u8 b) {
    switch (a) {
    case 0:
    case 1:
        setTalkAct(1);
        break;
    case 8:
        setTalkAct(0);
        break;
    }
}

BOOL FtrPhone::onDelete() { return TRUE; }

BOOL FtrPhone::updateActive() {
    execTalkAct();
    execFtrAct();
    return TRUE;
}

BOOL FtrPhone::initModel() {
    if (spawnMode == 1) {
        switchState.set(0, 0);
    }
    if (switchState.isOn() != 0) {
        changeAct(2, 0xff);
    } else {
        changeAct(0, 0xff);
    }
    setTalkAct(0);
    return TRUE;
}

FtrPhone::~FtrPhone() {}

FtrPhone::FtrPhone() {}

extern "C" void *FtrPhone_Create() {
    return new FtrPhone;
}

BOOL FtrSingingInsect::onDelete() { return TRUE; }




namespace p11 {
extern "C" {
extern char data_ov004_0224bb50[];


}
}














extern "C" void *FtrSingingInsect_Create() {
    return new FtrSingingInsect;
}


void FtrComputer::execFtrAct01() {
    FtrActor_StepAnims(this);
    ((FtrGlowMatSet *)(&glowMats))->setLit(1, 1, 0);
    ((FtrActor *)(this))->playSound0();
    if (switchState.isChanging()) {
        FtrSync_RequestAct(this, 0, 0xff, 1);
    }
}

BOOL FtrComputer::enterFtrAct01() {
    ((FtrActor *)(this))->playSound1();
    switchState.set(1, 0);
    ((FtrActor *)(this))->playAnim(1, 0, 0x1000, 0);
    return TRUE;
}

void FtrComputer::execFtrAct00() {
    FtrActor_StepAnims(this);
    ((FtrGlowMatSet *)(&glowMats))->setLit(0, 1, 0);
    if (switchState.isChanging()) {
        FtrSync_RequestAct(this, 1, 0xff, 1);
    }
}

BOOL FtrComputer::enterFtrAct00() {
    ((FtrActor *)(this))->playSound2();
    switchState.set(0, 0);
    ((FtrActor *)(this))->playAnim(0, 1, 0x1000, 0);
    return TRUE;
}

void FtrComputer::execFtrAct() {
    static void (FtrComputer::*tbl[2])() = {&FtrComputer::execFtrAct00, &FtrComputer::execFtrAct01};
    if (ftrAct < 2) {
        (this->*tbl[ftrAct])();
    }
}

BOOL FtrComputer::changeAct(u32 a, u8 b) {
    FtrActor::changeAct(a, b);
    static BOOL (FtrComputer::*tbl[2])() = {&FtrComputer::enterFtrAct00, &FtrComputer::enterFtrAct01};
    if (a < 2) {
        if ((this->*tbl[a])()) {
            ftrAct = a;
            return TRUE;
        }
    }
    return FALSE;
}

u8 FtrComputer::getActSwitchState(u32 a) {
    if (a < 2) {
        return data_ov004_02240024[a];
    }
    return 0;
}

BOOL FtrComputer::onDelete() {
    return TRUE;
}

BOOL FtrComputer::updateActive() {
    execFtrAct();
    ((FtrGlowMatSet *)(&glowMats))->update();
    return TRUE;
}

BOOL FtrComputer::initModel() {
    ((FtrActor *)(this))->initAnims(0, 1, 0x1000, 0);
    void *t = model.resMdl;
    s32 r = switchState.isOn();
    ((FtrGlowMatSet *)(&glowMats))->init(t, r);
    if (spawnMode == 1) {
        FtrSync_ChangeAct(this, 0, 0xff, 1);
    } else if (switchState.isOn() && !FtrMgr_IsShopScene()) {
        changeAct(1, 0xff);
    } else {
        changeAct(0, 0xff);
    }
    return TRUE;
}

extern "C" void *FtrComputer_Create() {
    return new FtrComputer;
}


void FtrHeadwear::execFtrAct01() {
    switchState.set(1, 0);
    visNodes.setVisible(1);
}

BOOL FtrHeadwear::enterFtrAct01() {
    switchState.set(1, 0);
    return TRUE;
}

void FtrHeadwear::execFtrAct00() {
    switchState.set(0, 0);
    visNodes.setVisible(0);
}

BOOL FtrHeadwear::enterFtrAct00() {
    switchState.set(0, 0);
    return TRUE;
}

void FtrHeadwear::execFtrAct() {
    static void (FtrHeadwear::*tbl[2])() = {&FtrHeadwear::execFtrAct00, &FtrHeadwear::execFtrAct01};
    if (ftrAct < 2) {
        (this->*tbl[ftrAct])();
    }
}

BOOL FtrHeadwear::changeAct(u32 a, u8 b) {
    FtrActor::changeAct(a, b);
    static BOOL (FtrHeadwear::*tbl[2])() = {&FtrHeadwear::enterFtrAct00, &FtrHeadwear::enterFtrAct01};
    if (a < 2) {
        if ((this->*tbl[a])()) {
            ftrAct = a;
            return TRUE;
        }
    }
    return FALSE;
}

u8 FtrHeadwear::getActSwitchState(u32 a) {
    if (a < 2) {
        return data_ov004_02240038[a];
    }
    return 0;
}

s32 FtrHeadwear::syncAct1() {
    return FtrSync_RequestAct(this, 1, 0xff, 1);
}

s32 FtrHeadwear::syncAct0() {
    return FtrSync_RequestAct(this, 0, 0xff, 1);
}

BOOL FtrHeadwear::isVisible() {
    if (alwaysVisible != 0) {
        return TRUE;
    }
    if (ftrAct == 1) {
        return TRUE;
    }
    return FALSE;
}

BOOL FtrHeadwear::onDelete() {
    return TRUE;
}

BOOL FtrHeadwear::updateActive() {
    execFtrAct();
    return TRUE;
}

static inline BOOL Unk_ov004_0220af74_Range(volatile u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    u32 x = *p;
    if (x >= lo && x <= hi) {
        r = TRUE;
    }
    return r;
}

BOOL FtrHeadwear::initModel() {
    volatile u16 v = Item_MakeFurniture(FtrActor_GetFtrIndex(this), 0);
    if (Unk_ov004_0220af74_Range(&v, 0x4124, 0x4223)) {
        alwaysVisible = 1;
    }
    if (switchState.isOn()) {
        changeAct(1, 0xff);
    } else {
        changeAct(0, 0xff);
    }
    return TRUE;
}

extern "C" void *FtrHeadwear_Create() {
    return new FtrHeadwear;
}


BOOL FtrKind25::onDelete() {
    return TRUE;
}

BOOL FtrKind25::updateActive() {
    return TRUE;
}

BOOL FtrKind25::initModel() {
    sampleIndex = ((FtrPreviewer *)(FtrPreviewer_GetInstance()))->getSampleIndex();
    return TRUE;
}

extern "C" void *FtrKind25_Create() {
    return new FtrKind25;
}


BOOL FtrCarpetSample::isVisible() {
    if (initFrames >= 2) {
        return TRUE;
    }
    return FALSE;
}

BOOL FtrCarpetSample::onDelete() {
    return TRUE;
}

BOOL FtrCarpetSample::updateActive() {
    if (initFrames < 2) {
        initFrames += TICK_STEP_ENDS() ? 1 : 0;
    }
    return TRUE;
}

BOOL FtrCarpetSample::initModel() {
    sampleIndex = ((FtrPreviewer *)(FtrPreviewer_GetInstance()))->getSampleIndex();
    initFrames = 0;
    u16 t = sampleIndex;
    s32 w;
    if (t < 0x44) {
        w = (u16)(t + 0x1144);
    } else {
        w = 0x1144;
    }
    u16 v = w;
    CarpetTex_Load(((FtrPreviewer *)(FtrPreviewer_GetInstance()))->getFloorBuffer(), &v);
    void *h = model.resMdl;
    void *r = CarpetTex_GetTex(((FtrPreviewer *)(FtrPreviewer_GetInstance()))->getFloorBuffer());
    if (((MatTexVramTask *)(&texTask))->request((void *)(h), (const char *)p11::data_ov004_0224bb50, r, 0, 0)) {
        return TRUE;
    }
    return FALSE;
}

FtrSingingInsect::FtrSingingInsect() {}
FtrComputer::FtrComputer() {}
FtrHeadwear::FtrHeadwear() {}
FtrKind25::FtrKind25() {}
FtrComputer::~FtrComputer() {}
FtrHeadwear::~FtrHeadwear() {}
FtrKind25::~FtrKind25() {}
FtrSingingInsect::~FtrSingingInsect() {}

namespace p12 {
extern "C" {
}
}


namespace p12 {
extern "C" {

void Wallpaper_LoadTexture(void *o, u16 *p);
}
}


FtrCarpetSample::~FtrCarpetSample() {}

FtrCarpetSample::FtrCarpetSample() {}

extern "C" void *FtrCarpetSample_Create() {
    return new FtrCarpetSample;
}


class FtrWallpaperSample : public FtrActor {
public:
    FtrWallpaperSample();
    virtual ~FtrWallpaperSample();
    virtual BOOL onDelete();
    virtual BOOL initModel();
    virtual BOOL updateActive();
    virtual BOOL isVisible();

    /* 0x840 */ u16 sampleIndex;
    /* 0x842 */ u8 initFrames;
    /* 0x843 */ u8 pad_843;
    /* 0x844 */ MatTexVramTask texTask;
};

BOOL FtrWallpaperSample::isVisible() {
    if (initFrames >= 2) return 1;
    return 0;
}

BOOL FtrWallpaperSample::onDelete() {
    return TRUE;
}

BOOL FtrWallpaperSample::updateActive() {
    if (initFrames < 2) initFrames += TICK_STEP_ENDS() ? 1 : 0;
    return TRUE;
}

BOOL FtrWallpaperSample::initModel() {
    u16 v;
    u16 tmp;
    u32 s;
    u8 *t;
    sampleIndex = (u16)(u32)((FtrPreviewer *)(FtrPreviewer_GetInstance()))->getSampleIndex();
    initFrames = 0;
    if (sampleIndex < 0x44) {
        v = sampleIndex + 0x1100;
    } else {
        v = 0x1100;
    }
    tmp = v;
    p12::Wallpaper_LoadTexture(((FtrPreviewer *)(FtrPreviewer_GetInstance()))->getWallBuffer(), &tmp);
    t = Wallpaper_GetTex((u8 *)((FtrPreviewer *)(FtrPreviewer_GetInstance()))->getWallBuffer());
    if (((MatTexVramTask *)(&texTask))->request(model.resMdl, (const char *)(data_ov004_0224bb60), (void *)t, 0, 0) != 0) return TRUE;
    return FALSE;
}

FtrWallpaperSample::~FtrWallpaperSample() {}

FtrWallpaperSample::FtrWallpaperSample() {}

extern "C" void *FtrWallpaperSample_Create() {
    return new FtrWallpaperSample;
}


class FtrMetronome;
typedef void (FtrMetronome::*Unk_ov004_0220b73c_Fn)();
typedef BOOL (FtrMetronome::*Unk_ov004_0220b7d4_Fn)();

class FtrMetronome : public FtrActor {
public:
    FtrMetronome();
    virtual ~FtrMetronome();
    virtual BOOL onDelete();
    virtual BOOL changeAct(u32 a, u8 b);
    virtual u8 getActSwitchState(u32 a);
    virtual BOOL initModel();
    virtual BOOL updateActive();
    virtual BOOL updateAppearRemove();

    void execFtrAct04();
    BOOL enterFtrAct04();
    void execFtrAct03();
    BOOL enterFtrAct03();
    void execFtrAct02();
    BOOL enterFtrAct02();
    void execFtrAct01();
    BOOL enterFtrAct01();
    void execFtrAct00();
    BOOL enterFtrAct00();
    void execFtrAct();

    /* 0x840 */ u8 unk_840;
    /* 0x841 */ u8 tickCount;
    /* 0x842 */ u8 pitchResetPending;
    /* 0x843 */ u8 ftrAct;
};

void FtrMetronome::execFtrAct04() {
    if (isPreview() == 0) {
        soundEmitter.playOnce(0x42a, &centerPos);
        if (pitchResetPending != 0) {
            soundEmitter.setPitch(1);
            pitchResetPending = 0;
        }
    }
    switchState.set(0, 0);
    if (FtrActor_StepAnims(this) != 0) {
        changeAct(0, 0xff);
    }
}

BOOL FtrMetronome::enterFtrAct04() {
    switchState.set(0, 0);
    FtrActor_PlayAnimsFromLastFrame(this, 0, 3, 0x1000);
    pitchResetPending = 1;
    return TRUE;
}

void FtrMetronome::execFtrAct03() {
    if (isPreview() == 0) {
        soundEmitter.playOnce(0x42a, &centerPos);
    }
    switchState.set(0, 0);
    if (isPreview() == 0) {
        if (model.hasPassedFrame(0) != 0) {
            soundEmitter.setPitch(1);
        } else if (model.hasPassedFrame(0x14) != 0) {
            if ((tickCount & 1) != 0) {
                soundEmitter.setPitch(2);
            } else {
                soundEmitter.setPitch(1);
            }
            tickCount++;
        }
    }
    if (FtrActor_StepAnims(this) != 0) {
        changeAct(4, 0xff);
    }
}

BOOL FtrMetronome::enterFtrAct03() {
    switchState.set(0, 0);
    playSound2();
    playAnim(1, 1, 0x1000, 0xffff);
    return TRUE;
}

void FtrMetronome::execFtrAct02() {
    if (isPreview() == 0) {
        soundEmitter.playOnce(0x42a, &centerPos);
    }
    FtrActor_StepAnims(this);
    if (isPreview() == 0) {
        if (model.hasPassedFrame(0) != 0) {
            soundEmitter.setPitch(1);
        } else if (model.hasPassedFrame(0x14) != 0) {
            if ((tickCount & 1) != 0) {
                soundEmitter.setPitch(2);
            } else {
                soundEmitter.setPitch(1);
            }
            tickCount++;
        }
    }
    if (switchState.isChanging() != 0) {
        FtrSync_RequestAct(this, 3, 0xff, 1);
    }
}

BOOL FtrMetronome::enterFtrAct02() {
    switchState.set(1, 0);
    FtrActor_PlayAnimsFromLastFrame(this, 1, 0, 0x1000);
    return TRUE;
}

void FtrMetronome::execFtrAct01() {
    if (isPreview() == 0) {
        soundEmitter.playOnce(0x42a, &centerPos);
    }
    switchState.set(1, 0);
    if (FtrActor_StepAnims(this) != 0) {
        changeAct(2, 0xff);
    }
}

BOOL FtrMetronome::enterFtrAct01() {
    switchState.set(1, 0);
    playAnim(0, 1, 0x1000, 0);
    playSound1();
    return TRUE;
}

void FtrMetronome::execFtrAct00() {
    if (switchState.isChanging() != 0) {
        FtrSync_RequestAct(this, 1, 0xff, 1);
    }
}

BOOL FtrMetronome::enterFtrAct00() {
    switchState.set(0, 0);
    playAnim(0, 3, 0x1000, 0);
    return TRUE;
}

void FtrMetronome::execFtrAct() {
    static Unk_ov004_0220b73c_Fn tbl[5] = {&FtrMetronome::execFtrAct00, &FtrMetronome::execFtrAct01,
                                           &FtrMetronome::execFtrAct02, &FtrMetronome::execFtrAct03,
                                           &FtrMetronome::execFtrAct04};
    u32 i = ftrAct;
    if (i < 5) {
        (this->*tbl[i])();
    }
}

BOOL FtrMetronome::changeAct(u32 idx, u8 b) {
    FtrActor::changeAct(idx, b);
    static Unk_ov004_0220b7d4_Fn tbl[5] = {&FtrMetronome::enterFtrAct00, &FtrMetronome::enterFtrAct01,
                                           &FtrMetronome::enterFtrAct02, &FtrMetronome::enterFtrAct03,
                                           &FtrMetronome::enterFtrAct04};
    if (idx < 5) {
        if ((this->*tbl[idx])() != 0) {
            ftrAct = idx;
            return TRUE;
        }
    }
    return FALSE;
}

u8 FtrMetronome::getActSwitchState(u32 idx) {
    if (idx < 5) return data_ov004_02240064[idx];
    return 0;
}

BOOL FtrMetronome::onDelete() {
    return TRUE;
}

BOOL FtrMetronome::updateAppearRemove() {
    if (isPreview() == 0) {
        if (isRemoving() == 0) {
            soundEmitter.playOnce(0x42a, &centerPos);
        }
    }
    return TRUE;
}

BOOL FtrMetronome::updateActive() {
    execFtrAct();
    return TRUE;
}

BOOL FtrMetronome::initModel() {
    unk_840 = 0;
    initAnims(0, 1, 0x1000, 0);
    if (switchState.isOn() != 0 && FtrMgr_IsShopScene() == 0) {
        changeAct(2, 0xff);
    } else {
        changeAct(0, 0xff);
    }
    return TRUE;
}

FtrMetronome::~FtrMetronome() {}

FtrMetronome::FtrMetronome() {}

extern "C" void *FtrMetronome_Create() {
    return new FtrMetronome;
}

class FtrPiggyBank : public FtrActor {
public:
    FtrPiggyBank();
    virtual ~FtrPiggyBank();
    virtual BOOL onDelete();
    virtual BOOL changeAct(u32 a, u8 v);
    virtual BOOL initModel();
    virtual BOOL updateActive();

    void execFtrAct01();
    BOOL enterFtrAct01();
    void execFtrAct00();
    BOOL enterFtrAct00();
    void execFtrAct();

    /* 0x840 */ u8 ftrAct;
    /* 0x841 */ u8 pad_841[3];
};
typedef void (FtrPiggyBank::*Unk_ov004_0220ba88_Fn)();

void FtrPiggyBank::execFtrAct01() {
    execFtrAct00();
}

BOOL FtrPiggyBank::enterFtrAct01() {
    void *r5;
    playSound1();
    if (actAid == gCommManager->localSlot) {
        r5 = PlayerData_GetCurrent();
        if (r5 != 0) {
            if (((PlayerInventory *)(((PlayerData *)(r5))->getInventory()))->getTotalBells(0) > 0) {
                PlayerInventory *r4 = (PlayerInventory *)((PlayerData *)(r5))->getInventory();
                PlayerInventory_SetWallet(r4, ((PlayerInventory *)(((PlayerData *)(r5))->getInventory()))->getTotalBells(0) - 1, 0);
            }
        }
    }
    return TRUE;
}

void FtrPiggyBank::execFtrAct00() {
    if (switchState.isChanging() != 0) {
        FtrSync_RequestAct(this, 1, gCommManager->localSlot, 1);
    } else if (isPreview() != 0) {
        changeAct(1, 0xff);
    }
}

BOOL FtrPiggyBank::enterFtrAct00() {
    return TRUE;
}

void FtrPiggyBank::execFtrAct() {
    static Unk_ov004_0220ba88_Fn tbl[2] = {&FtrPiggyBank::execFtrAct00, &FtrPiggyBank::execFtrAct01};
    u32 i = ftrAct;
    if (i < 2) {
        (this->*tbl[i])();
    }
}


namespace p13 {
extern "C" {
}
}

namespace p13 {
extern "C" {
extern u16 gFtrSoundNone;
extern char data_ov004_0224bb70[];
extern char data_ov004_0224bb80[];
extern s16 data_02135f44[];

s32 FX_Div(s32 a, s32 b);
s32 func_01ffcb0c(s32 a, s32 b);
void MTX_RotY33_(void *out, s32 a, s32 b);
}
}


typedef BOOL (FtrPiggyBank::*Unk_ov004_0220baf4_Fn)();

BOOL FtrPiggyBank::changeAct(u32 a, u8 v) {
    FtrActor::changeAct(a, v);
    static Unk_ov004_0220baf4_Fn tbl[2] = {
        &FtrPiggyBank::enterFtrAct00,
        &FtrPiggyBank::enterFtrAct01,
    };
    if ((u32)a < 2) {
        if ((this->*tbl[a])()) {
            ftrAct = a;
            return TRUE;
        }
    }
    return FALSE;
}

BOOL FtrPiggyBank::onDelete() {
    return TRUE;
}

BOOL FtrPiggyBank::updateActive() {
    execFtrAct();
    return TRUE;
}

BOOL FtrPiggyBank::initModel() {
    changeAct(0, 0xff);
    return TRUE;
}

FtrPiggyBank::~FtrPiggyBank() {}

FtrPiggyBank::FtrPiggyBank() {}

extern "C" void *FtrPiggyBank_Create() {
    return new FtrPiggyBank;
}


class FtrInstrument : public FtrActor {
public:
    FtrInstrument();
    virtual ~FtrInstrument();
    virtual BOOL onDelete();
    virtual BOOL changeAct(u32 a, u8 v);
    virtual BOOL initModel();
    virtual BOOL updateActive();
    virtual BOOL updateAppearRemove();

    /* 0x840 */ MelodyBeat melodyBeat;
};

BOOL FtrInstrument::changeAct(u32 a, u8 v) {
    FtrActor::changeAct(a, v);
    u32 c = FtrSound_GetSe1(FtrActor_GetFtrIndex(this));
    if (c != p13::gFtrSoundNone) {
        Snd_MelodyBeatStart(&melodyBeat, c);
    }
    return TRUE;
}

BOOL FtrInstrument::onDelete() {
    Snd_MelodyBeatStop(&melodyBeat);
    return TRUE;
}

BOOL FtrInstrument::updateAppearRemove() {
    VecFx32 v;
    v.x = centerPos.x;
    v.y = centerPos.y;
    v.z = centerPos.z;
    Snd_MelodyBeatUpdate(&melodyBeat, &v);
    return TRUE;
}

BOOL FtrInstrument::updateActive() {
    if (switchState.isChanging()) {
        FtrSync_RequestAct(this, 0, 0xff, 1);
    }
    updateAppearRemove();
    return TRUE;
}

BOOL FtrInstrument::initModel() {
    Snd_MelodyBeatInit(&melodyBeat);
    return TRUE;
}

FtrInstrument::~FtrInstrument() {
    MelodyBeat_Destruct();
}

FtrInstrument::FtrInstrument() {
    MelodyBeat_Construct();
}

extern "C" void *FtrInstrument_Create() {
    return new FtrInstrument;
}

class FtrVillagerPic : public FtrActor {
public:
    FtrVillagerPic();
    virtual ~FtrVillagerPic();
    virtual BOOL onDelete();
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual BOOL initModel();
    virtual BOOL updateActive();

    void execTalkAct03();
    BOOL enterTalkAct03();
    void execTalkAct02();
    BOOL enterTalkAct02();
    void execTalkAct01();
    BOOL enterTalkAct01();
    void execTalkAct00();
    BOOL enterTalkAct00();
    void execTalkAct();
    BOOL setTalkAct(s32 idx);

    /* 0x840 */ s32 talkAct;
};

typedef BOOL (FtrVillagerPic::*Unk_ov004_0224a500_Fn)();
typedef void (FtrVillagerPic::*Unk_ov004_0220bec8_Fn)();

void FtrVillagerPic::execTalkAct03() {
    if (((TalkWindowState *)window)) {
        if (((TalkWindowState *)window)->state == 0) {
            ((Character *)(this))->detachTalkRequest(this);
            TalkRequest_SetTargetDone(this);
        }
    }
}

BOOL FtrVillagerPic::enterTalkAct03() {
    return TRUE;
}

void FtrVillagerPic::execTalkAct02() {
    if (((TalkWindowState *)window)) {
        if (((TalkWindowState *)window)->state) {
            setTalkAct(3);
        }
    }
}

BOOL FtrVillagerPic::enterTalkAct02() {
    volatile u16 va[2];
    s32 idx;
    ((Character *)(this))->attachTalkRequest(this);
    ((TalkWindowState *)window)->nextState = 1;
    va[1] = Item_MakeFurniture(FtrActor_GetFtrIndex(this), 0);
    BOOL r = FALSE;
    u32 t = va[1];
    if (t >= 0x47d8 && t <= 0x4a47) r = TRUE;
    if (r) idx = (s32)(t - 0x47d8) >> 2;
    else idx = -1;
    MsgRequest::setFileName(p13::data_ov004_0224bb70);
    msgIndex = idx;
    return TRUE;
}

void FtrVillagerPic::execTalkAct01() {
    setTalkAct(2);
}

BOOL FtrVillagerPic::enterTalkAct01() {
    return TRUE;
}

void FtrVillagerPic::execTalkAct00() {
    if (switchState.isChanging()) {
        TalkRequest_AddPlayerTalk6(this, 0);
    }
}

BOOL FtrVillagerPic::enterTalkAct00() {
    return TRUE;
}

void FtrVillagerPic::execTalkAct() {
    static Unk_ov004_0220bec8_Fn tbl[4] = {
        &FtrVillagerPic::execTalkAct00,
        &FtrVillagerPic::execTalkAct01,
        &FtrVillagerPic::execTalkAct02,
        &FtrVillagerPic::execTalkAct03,
    };
    if (talkAct < 4) {
        (this->*tbl[talkAct])();
    }
}

BOOL FtrVillagerPic::setTalkAct(s32 idx) {
    static Unk_ov004_0224a500_Fn tbl[4] = {
        &FtrVillagerPic::enterTalkAct00,
        &FtrVillagerPic::enterTalkAct01,
        &FtrVillagerPic::enterTalkAct02,
        &FtrVillagerPic::enterTalkAct03,
    };
    if (idx < 4) {
        if ((this->*tbl[idx])()) {
            talkAct = idx;
            return TRUE;
        }
    }
    return FALSE;
}

void FtrVillagerPic::onInteractionEvent(u32 a, u8 b) {
    switch (a) {
    case 1:
        setTalkAct(1);
        break;
    case 8:
        setTalkAct(0);
        break;
    }
}

BOOL FtrVillagerPic::onDelete() {
    return TRUE;
}

BOOL FtrVillagerPic::updateActive() {
    execTalkAct();
    return TRUE;
}

BOOL FtrVillagerPic::initModel() {
    return TRUE;
}

FtrVillagerPic::~FtrVillagerPic() {}

FtrVillagerPic::FtrVillagerPic() {}

extern "C" void *FtrVillagerPic_Create() {
    return new FtrVillagerPic;
}

class FtrCompass : public FtrActor {
public:
    FtrCompass();
    virtual ~FtrCompass();
    virtual BOOL onDelete();
    virtual void onJointCalcPost(s32 a, void *b);
    virtual BOOL initModel();
    virtual BOOL updateActive();
    virtual void onRotateStart(BOOL negative);
    virtual void onRotateUpdate(BOOL negative);

    /* 0x840 */ s16 compassNode;
    /* 0x842 */ volatile s16 rotateFrames;
    /* 0x844 */ volatile s16 swingPhase;
    /* 0x846 */ s16 pad_846;
    /* 0x848 */ volatile s32 swingAmp;
    /* 0x84c */ s32 needleAngle;
};

void FtrCompass::onJointCalcPost(s32 a, void *b) {
    NNSG3dRS *p = (NNSG3dRS *)b;
    if (compassNode == a) {
        MtxFx33 *dst = &p->pJntAnmResult->rot;
        s32 t = p13::func_01ffcb0c(p13::FX_Div(needleAngle, 0x168000), 0x10000000);
        s32 r = (t << 4) >> 16;
        s32 ang;
        Actor *act = FtrActor_GetParent(this);
        if (act) {
            s32 e = act->rotY;
            ang = (s16)(r - (e + stackLink.getRelAngle()));
        } else {
            ang = (s16)(r - rotY);
        }
        s32 idx = ((u16)ang >> 4) * 2;
        MtxFx33 mtx;
        p13::MTX_RotY33_(&mtx, p13::data_02135f44[idx], p13::data_02135f44[idx + 1]);
        if (p->pJntAnmResult->flag & 2) {
            *dst = mtx;
        } else {
            MTX_Concat33(dst, &mtx, dst);
        }
        p->pJntAnmResult->flag &= ~2;
    }
}

void FtrCompass::onRotateUpdate(BOOL negative) {
    if (++this->rotateFrames == 8) {
        this->swingPhase = 0;
        if (negative) {
            this->swingAmp = p13::func_01ffcb0c(this->swingAmp, p13::data_02135f44[((u16)this->swingPhase >> 4) * 2]) + 0x2d000;
            if (this->swingAmp > 0x2d000) this->swingAmp = 0x2d000;
        } else {
            this->swingAmp = p13::func_01ffcb0c(this->swingAmp, p13::data_02135f44[((u16)this->swingPhase >> 4) * 2]) - 0x2d000;
            if (this->swingAmp < -0x2d000) this->swingAmp = -0x2d000;
        }
    }
}

void FtrCompass::onRotateStart(BOOL negative) {
    rotateFrames = 0;
}

BOOL FtrCompass::onDelete() {
    return TRUE;
}

BOOL FtrCompass::updateActive() {
    Math_StepS32((s32 *)&swingAmp, 0, 0x5a00);
    if (swingAmp == 0) {
        swingPhase = 0;
    } else {
        swingPhase = swingPhase + 0x960;
    }
    Math_StepS32(&needleAngle, p13::func_01ffcb0c(swingAmp, swingPhase), 0x5a00);
    return TRUE;
}

BOOL FtrCompass::initModel() {
    compassNode = ((G3dResAccess *)(model.resMdl))->findNodeIdx(p13::data_ov004_0224bb80);
    return TRUE;
}

FtrCompass::~FtrCompass() {}

FtrCompass::FtrCompass() {
    compassNode = -1;
}

extern "C" void *FtrCompass_Create() {
    return new FtrCompass;
}

class FtrDesignDisplay : public FtrActor {
public:
    FtrDesignDisplay();
    virtual ~FtrDesignDisplay();
    virtual BOOL onDelete();
    virtual BOOL initModel();
    virtual BOOL updateActive();

    /* 0x840 */ s32 designSlot;
    /* 0x844 */ SndSeEmitter seEmitter;
    /* 0x884 */ u8 seEmitterReady;
};

BOOL FtrDesignDisplay::onDelete() {
    if (seEmitterReady) {
        seEmitter.callStop();
    }
    return TRUE;
}

BOOL FtrDesignDisplay::updateActive() {
    if (seEmitterReady) {
        VecFx32 v = centerPos;
        if (PatternTexCache_Get()->testAndClearAbleDirty(designSlot)) {
            Snd_SeEmitterPlayOneShot(&seEmitter, 0x50, 0x7f, 0);
        }
        seEmitter.callUpdateRelative((VecFx32 *)(&v));
    }
    return TRUE;
}

BOOL FtrDesignDisplay::initModel() {
    volatile u16 va[2];
    va[0] = Item_MakeFurniture(FtrActor_GetFtrIndex(this), 0);
    designSlot = 0;
    BOOL r = FALSE;
    u32 t = va[0];
    if (t >= 0x3e04 && t <= 0x3e23) r = TRUE;
    if (r) {
        s32 x;
        if (t >= 0x3e04 && t <= 0x3e23) {
            x = (s32)(t - 0x3e04) >> 2;
        } else {
            x = -1;
        }
        designSlot = x & 7;
        u8 *q = PatternTexCache_Get()->getAbleTexKey((u8)designSlot);
        if (q != 0) {
            Model_BindMatTexByIdx(model.resMdl, (const char *)data_ov004_0224bb88, q, 0, 0);
            if (seEmitterReady == 0) {
                seEmitter.callInit();
                seEmitterReady = 1;
            }
            return TRUE;
        }
    }
    return FALSE;
}

namespace p14 {
extern "C" {
}
}


namespace p14 {
extern "C" {
}
}
namespace p14 {
extern "C" {
void GroundInfo_Destruct(void *);
}
}
namespace p14 {
extern "C" {
}
}


class FtrMyDesign : public FtrActor {
public:
    FtrMyDesign();
    virtual ~FtrMyDesign();

    virtual BOOL onDelete();
    virtual void onNodeVisCalc(s32 a, NNSG3dRS *b);
    virtual BOOL initModel();
    virtual BOOL updateActive();

    /* 0x840 */ s32 hiddenNode;
};

class FtrShirt : public FtrActor {
public:
    FtrShirt();
    virtual ~FtrShirt();

    virtual BOOL onDelete();
    virtual BOOL changeAct(u32 a, u8 b);
    virtual u8 getActSwitchState(u32 a);
    virtual BOOL initModel();
    virtual BOOL updateActive();
    virtual BOOL needsTexCopy();

    BOOL execFtrAct01();
    BOOL enterFtrAct01();
    BOOL execFtrAct00();
    BOOL enterFtrAct00();
    void execFtrAct();
    s32 syncAct0();
    s32 syncAct1();

    /* 0x840 */ void *clothTex;
    /* 0x844 */ MatTexVramTask texTask;
    /* 0x86c */ u8 unk_86c;
    /* 0x86d */ u8 unk_86d;
    /* 0x86e */ u8 pad_86e;
    /* 0x86f */ u8 inInitModel;
    /* 0x870 */ u8 ftrAct;
    /* 0x871 */ u8 pad_871[3];
};

class FtrCannon : public FtrActor {
public:
    FtrCannon();
    virtual ~FtrCannon();
    virtual BOOL onDelete();
    virtual void onJointCalcPost(s32 a, void *b);
    virtual BOOL changeAct(u32 a, u8 b);
    virtual BOOL initModel();
    virtual BOOL updateActive();
    virtual void onRemove();

    BOOL execFtrAct01();
    BOOL enterFtrAct01();
    BOOL execFtrAct00();
    BOOL enterFtrAct00();
    void execFtrAct();

    /* 0x840 */ u8 ftrAct;
};

namespace p14 {
extern "C" {
extern u8 data_021f47e0[];

void Item_FromPlacedForm(u16 *, u16 *);
void MTX_MultVec43(void *, void *, void *);
void GroundInfo_Destruct(void *);
}
}

static inline BOOL Unk_ov004_0220c554_InRange(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    u32 v = *p;
    if (v >= lo && v <= hi) r = TRUE;
    return r;
}

static inline BOOL Unk_ov004_0220c554_R(u32 v, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (v >= lo && v <= hi) r = TRUE;
    return r;
}

static inline s32 Unk_ov004_0220c554_Idx(u32 v, u32 lo, u32 hi) {
    if (v >= lo && v <= hi) {
        return (s32)(v - lo) >> 2;
    }
    return -1;
}

FtrDesignDisplay::~FtrDesignDisplay() {
}

FtrDesignDisplay::FtrDesignDisplay() {
}

extern "C" FtrDesignDisplay *FtrDesignDisplay_Create() {
    return new FtrDesignDisplay;
}

void FtrMyDesign::onNodeVisCalc(s32 a, NNSG3dRS *b) {
    if (a == hiddenNode) {
        *(s32 *)b->pVisAnmResult = 0;
    }
}

BOOL FtrMyDesign::onDelete() {
    return TRUE;
}

BOOL FtrMyDesign::updateActive() {
    return TRUE;
}

BOOL FtrMyDesign::initModel() {
    volatile u16 v;
    s32 t;
    s32 hi;
    v = Item_MakeFurniture(FtrActor_GetFtrIndex(this), 0);
    BOOL f = FALSE;
    t = -1;
    hiddenNode = t;
    u32 x = v;
    if (x >= 0x3d84 && x <= 0x3e03) f = TRUE;
    if (f) {
        if (x >= 0x3d84 && x <= 0x3e03) {
            t = (s32)(x - 0x3d84) >> 2;
        } else {
            t = -1;
        }
    } else if (x >= 0x3ea4 && x <= 0x3f23) {
        t = Unk_ov004_0220c554_Idx(x, 0x3ea4, 0x3f23);
    } else if (x >= 0x4224 && x <= 0x42a3) {
        t = Unk_ov004_0220c554_Idx(x, 0x4224, 0x42a3);
    } else if (x >= 0x3f24 && x <= 0x3fa3) {
        t = Unk_ov004_0220c554_Idx(x, 0x3f24, 0x3fa3);
    }
    if (t == -1) t = 0;
    hi = (t >> 3) & 3;
    s32 lo = t & 7;
    PlayerData *pd = PlayerData_Get(hi);
    if (pd) {
        if (pd->getPlayerId()->getGender() == 0) {
            hiddenNode = ((G3dResAccess *)(model.resMdl))->findNodeIdx((const char *)(data_ov004_0224bb8c));
        } else {
            hiddenNode = ((G3dResAccess *)(model.resMdl))->findNodeIdx((const char *)(data_ov004_0224bb90));
        }
    }
    void *o = model.resMdl;
    Model_BindMatTexByIdx(o, (const char *)data_ov004_0224bb88, PatternTexCache_Get()->getPlayerTexKey(hi, lo), 0, 0);
    return TRUE;
}

FtrMyDesign::~FtrMyDesign() {
}

FtrMyDesign::FtrMyDesign() {
}

extern "C" FtrMyDesign *FtrMyDesign_Create() {
    return new FtrMyDesign;
}

BOOL FtrShirt::execFtrAct01() {
    switchState.set(0, 0);
    return TRUE;
}

BOOL FtrShirt::enterFtrAct01() {
    s32 a, b;
    void *c;
    void *d;
    switchState.set(0, 0);
    a = ((G3dResAccess *)(((FtrAnimSet *)(modelRes.getAnimSet()))->getTexCopy()))->findTexIdx((const char *)data_ov004_0224bb94);
    b = ((G3dResAccess *)(((FtrAnimSet *)(modelRes.getAnimSet()))->getTexCopy()))->findPlttIdx((const char *)data_ov004_0224bb94);
    c = model.resMdl;
    d = ((FtrAnimSet *)(modelRes.getAnimSet()))->getTexCopy();
    if (texTask.request(c, (const char *)(data_ov004_0224bb88), d, a, b)) {
        unk_86c = 0;
    }
    return TRUE;
}

BOOL FtrShirt::execFtrAct00() {
    switchState.set(1, 0);
    return TRUE;
}

BOOL FtrShirt::enterFtrAct00() {
    switchState.set(1, 0);
    void *o = model.resMdl;
    texTask.request(o, (const char *)(data_ov004_0224bb88), ClothTex_GetTex(clothTex), 0, 0);
    return TRUE;
}

typedef BOOL (FtrShirt::*Unk_ov004_0224ad34_Fn)();

void FtrShirt::execFtrAct() {
    static Unk_ov004_0224ad34_Fn tbl[2] = { &FtrShirt::execFtrAct00, &FtrShirt::execFtrAct01 };
    u32 i = ftrAct;
    if (i < 2) {
        (this->*tbl[i])();
    }
}

BOOL FtrShirt::changeAct(u32 a, u8 b) {
    FtrActor::changeAct(a, b);
    static Unk_ov004_0224ad34_Fn tbl[2] = { &FtrShirt::enterFtrAct00, &FtrShirt::enterFtrAct01 };
    if (a < 2) {
        if ((this->*tbl[a])()) {
            ftrAct = a;
            return TRUE;
        }
    }
    return FALSE;
}

u8 FtrShirt::getActSwitchState(u32 a) {
    if (a < 2) {
        return data_ov004_0224002c[a];
    }
    return 0;
}

s32 FtrShirt::syncAct0() {
    return FtrSync_RequestAct(this, 0, 0xff, 1);
}

s32 FtrShirt::syncAct1() {
    return FtrSync_RequestAct(this, 1, 0xff, 1);
}

BOOL FtrShirt::needsTexCopy() {
    return 1;
}

BOOL FtrShirt::onDelete() {
    return TRUE;
}

BOOL FtrShirt::updateActive() {
    execFtrAct();
    return TRUE;
}

BOOL FtrShirt::initModel() {
    u16 v, w;
    inInitModel = 1;
    v = Item_MakeFurniture(FtrActor_GetFtrIndex(this), 0);
    BOOL r = FALSE;
    if (v >= 0x3984 && v <= 0x3d83) r = TRUE;
    if (r) {
        p14::Item_FromPlacedForm(&w, &v);
        ModelSlot *h = FtrActor_GetHeap(this);
        clothTex = Heap_Alloc(h->getHeap(), 0x2c4);
        ClothTex_LoadItem(clothTex, &w, 0);
        if (switchState.isOn()) {
            changeAct(0, 0xff);
        } else {
            changeAct(1, 0xff);
        }
    }
    changeAct(0, 0xff);
    inInitModel = 0;
    return TRUE;
}

FtrShirt::~FtrShirt() {
}

FtrShirt::FtrShirt() {
    clothTex = NULL;
    unk_86c = unk_86d = 0;
}

extern "C" FtrShirt *FtrShirt_Create() {
    return new FtrShirt;
}

BOOL FtrCannon::execFtrAct01() {
    model.stepBlend();
    BOOL r = model.isFinished();
    if (r) {
        return FtrSync_ChangeAct(this, 0, 0xff, 1);
    }
    return r;
}

BOOL FtrCannon::enterFtrAct01() {
    visNodes.setVisible(1);
    playAnim(0, 1, 0x1000, 0);
    playSound1();
    return TRUE;
}

BOOL FtrCannon::execFtrAct00() {
    BOOL r = switchState.isChanging();
    if (r) {
        return FtrSync_ChangeAct(this, 1, 0xff, 1);
    }
    return r;
}

BOOL FtrCannon::enterFtrAct00() {
    visNodes.setVisible(0);
    playAnim(0, 1, 0x1000, 0);
    return TRUE;
}

typedef BOOL (FtrCannon::*Unk_ov004_0224ae60_Fn)();

void FtrCannon::execFtrAct() {
    static Unk_ov004_0224ae60_Fn tbl[2] = { &FtrCannon::execFtrAct00, &FtrCannon::execFtrAct01 };
    u32 i = ftrAct;
    if (i < 2) {
        (this->*tbl[i])();
    }
}

BOOL FtrCannon::changeAct(u32 a, u8 b) {
    FtrActor::changeAct(a, b);
    static Unk_ov004_0224ae60_Fn tbl[2] = { &FtrCannon::enterFtrAct00, &FtrCannon::enterFtrAct01 };
    if (a < 2) {
        if ((this->*tbl[a])()) {
            ftrAct = a;
            return TRUE;
        }
    }
    return FALSE;
}

void FtrCannon::onJointCalcPost(s32 a, void *b) {
    VecFx32 v;
    VecFx32 o;
    if (visNodes.hasNode(a) && ftrAct == 1) {
        VecFx32 *pv = (VecFx32 *)&((NNSG3dRS *)b)->pJntAnmResult->trans;
        v.x = pv->x;
        v.y = pv->y;
        v.z = pv->z;
        *(Mtx43 *)p14::data_021f47e0 = model.mtx;
        p14::MTX_MultVec43(&v, p14::data_021f47e0, &o);
        u8 obj[0x44];
        ((GroundInfo *)(obj))->initAtPos((VecFx32 *)(&o), 0, 0);
        if (((GroundInfoBase *)(obj))->getHeight(0) > 0) {
            FtrSync_ChangeAct(this, 0, 0xff, 1);
        }
        p14::GroundInfo_Destruct(obj);
    }
}

void FtrCannon::onRemove() {
    playAnim(0, 1, 0x1000, 0);
}

BOOL FtrCannon::onDelete() {
    switchState.set(0, 0);
    return TRUE;
}

BOOL FtrCannon::updateActive() {
    execFtrAct();
    return TRUE;
}

namespace p15 {
extern "C" {
}
}

class FtrKind19 : public FtrActor {
public:
    FtrKind19();
    virtual ~FtrKind19();
    virtual BOOL onDelete();
    virtual BOOL changeAct(u32 a, u8 b);
    virtual u8 getActSwitchState(u32 a);
    virtual BOOL initModel();
    virtual BOOL updateActive();

    void execFtrAct03();
    BOOL enterFtrAct03();
    void execFtrAct02();
    BOOL enterFtrAct02();
    void execFtrAct01();
    BOOL enterFtrAct01();
    void execFtrAct00();
    BOOL enterFtrAct00();
    void execFtrAct();

    /* 0x840 */ u8 ftrAct;
    /* 0x841 */ u8 pad_841[3];
};

namespace p15 {
extern "C" {


}
}

BOOL FtrCannon::initModel() {
    initAnims(0, 1, 0x1000, 0);
    changeAct(0, 0xff);
    return TRUE;
}

FtrCannon::~FtrCannon() {
}

FtrCannon::FtrCannon() {
}

extern "C" void *FtrCannon_Create() {
    return new FtrCannon;
}

void FtrKind19::execFtrAct03() {
    switchState.set(0, 0);
    if (anims[0].getAnmObj()) {
        anims[0].step();
        ((G3dAnmObj *)anims[0].anmObj)->frame = anims[0].curFrame;
        if (anims[0].isFinished()) {
            changeAct(0, 0xff);
        }
    } else {
        changeAct(0, 0xff);
    }
}

BOOL FtrKind19::enterFtrAct03() {
    switchState.set(0, 0);
    if (((FtrAnimSet *)(modelRes.getAnimSet()))->getBma(0) != NULL) {
        NNSG3dResAnmCommon *r = ((FtrAnimSet *)(modelRes.getAnimSet()))->getBma(0);
        if (anims[0].getAnmObj()) {
            anims[0].replace(model.getRenderObj(), r, 3, 0x1000, (u16)(r->numFrame - 1));
        }
    }
    playSound2();
    return TRUE;
}

void FtrKind19::execFtrAct02() {
    hasIndoorFlag6();
    playSound0();
    if (switchState.isChanging()) {
        FtrSync_RequestAct(this, 3, 0xff, 1);
    }
}

BOOL FtrKind19::enterFtrAct02() {
    switchState.set(1, 0);
    if (((FtrAnimSet *)(modelRes.getAnimSet()))->getBma(0) != NULL) {
        NNSG3dResAnmCommon *r = ((FtrAnimSet *)(modelRes.getAnimSet()))->getBma(0);
        anims[0].replace(model.getRenderObj(), r, 1, 0x1000, (u16)(r->numFrame - 1));
    }
    return TRUE;
}

void FtrKind19::execFtrAct01() {
    switchState.set(1, 0);
    playSound0();
    if (anims[0].getAnmObj()) {
        anims[0].step();
        ((G3dAnmObj *)anims[0].anmObj)->frame = anims[0].curFrame;
        if (anims[0].isFinished()) {
            changeAct(2, 0xff);
        }
    } else {
        changeAct(2, 0xff);
    }
}

BOOL FtrKind19::enterFtrAct01() {
    switchState.set(1, 0);
    if (((FtrAnimSet *)(modelRes.getAnimSet()))->getBma(0) != NULL) {
        NNSG3dResAnmCommon *r = ((FtrAnimSet *)(modelRes.getAnimSet()))->getBma(0);
        if (anims[0].getAnmObj()) {
            anims[0].replace(model.getRenderObj(), r, 1, 0x1000, 0);
        }
    }
    playSound1();
    return TRUE;
}

void FtrKind19::execFtrAct00() {
    if (switchState.isChanging()) {
        FtrSync_RequestAct(this, 1, 0xff, 1);
    }
}

BOOL FtrKind19::enterFtrAct00() {
    switchState.set(0, 0);
    if (((FtrAnimSet *)(modelRes.getAnimSet()))->getBma(0) != NULL) {
        NNSG3dResAnmCommon *r = ((FtrAnimSet *)(modelRes.getAnimSet()))->getBma(0);
        anims[0].replace(model.getRenderObj(), r, 3, 0x1000, 0);
    }
    return TRUE;
}

void FtrKind19::execFtrAct() {
    typedef void (FtrKind19::*Fn)();
    static Fn tbl[4] = {
        &FtrKind19::execFtrAct00,
        &FtrKind19::execFtrAct01,
        &FtrKind19::execFtrAct02,
        &FtrKind19::execFtrAct03,
    };
    u32 i = ftrAct;
    if (i < 4) {
        (this->*tbl[i])();
    }
}

BOOL FtrKind19::changeAct(u32 a, u8 b) {
    typedef BOOL (FtrKind19::*Fn)();
    FtrActor::changeAct(a, b);
    static Fn tbl[4] = {
        &FtrKind19::enterFtrAct00,
        &FtrKind19::enterFtrAct01,
        &FtrKind19::enterFtrAct02,
        &FtrKind19::enterFtrAct03,
    };
    if ((u32)a < 4) {
        if ((this->*tbl[a])()) {
            ftrAct = a;
            return TRUE;
        }
    }
    return FALSE;
}

u8 FtrKind19::getActSwitchState(u32 a) {
    if (a < 4) {
        return data_ov004_02240058[a];
    }
    return 0;
}

BOOL FtrKind19::onDelete() {
    return TRUE;
}

BOOL FtrKind19::updateActive() {
    execFtrAct();
    if (model.getAnmObj()) {
        model.stepBlend();
    }
    if (anims[1].getAnmObj()) {
        anims[1].step();
        ((G3dAnmObj *)anims[1].anmObj)->frame = anims[1].curFrame;
    }
    if (anims[2].getAnmObj()) {
        anims[2].step();
        ((G3dAnmObj *)anims[2].anmObj)->frame = anims[2].curFrame;
    }
    if (anims[3].getAnmObj()) {
        anims[3].step();
        ((G3dAnmObj *)anims[3].anmObj)->frame = anims[3].curFrame;
    }
    return TRUE;
}

BOOL FtrKind19::initModel() {
    ModelSlot *r4 = FtrActor_GetHeap(this);
    if (((FtrAnimSet *)(modelRes.getAnimSet()))->getBva(0) != NULL) {
        void *t = model.resMdl;
        if (anims[3].allocJointAnm((NNSG3dResMdl *)(t), r4->getHeap())) {
            anims[3].init(((FtrAnimSet *)(modelRes.getAnimSet()))->getBva(0), 0, 0x1000, 0);
            anims[3].addToRenderObj(model.getRenderObj());
        }
    }
    if (((FtrAnimSet *)(modelRes.getAnimSet()))->getBta(0) != NULL) {
        void *t = model.resMdl;
        if (anims[1].allocMatAnm((NNSG3dResMdl *)(t), r4->getHeap())) {
            anims[1].init(((FtrAnimSet *)(modelRes.getAnimSet()))->getBta(0), 0, 0x1000, 0);
            anims[1].addToRenderObj(model.getRenderObj());
        }
    }
    if (((FtrAnimSet *)(modelRes.getAnimSet()))->getBca(0) != NULL) {
        if (model.allocAnmObj(r4->getHeap())) {
            model.initAnim(((FtrAnimSet *)(modelRes.getAnimSet()))->getBca(0), 0, 0x1000, 0, 0);
            model.attachAnim();
        }
    }
    if (((FtrAnimSet *)(modelRes.getAnimSet()))->getBtp(0) != NULL) {
        void *t = model.resMdl;
        if (anims[2].allocMatAnm((NNSG3dResMdl *)(t), r4->getHeap())) {
            NNSG3dResAnmCommon *r = ((FtrAnimSet *)(modelRes.getAnimSet()))->getBtp(0);
            anims[2].initWithTex(r, modelRes.getTexture(), 0, 0x1000, 0);
            anims[2].addToRenderObj(model.getRenderObj());
        }
    }
    if (((FtrAnimSet *)(modelRes.getAnimSet()))->getBma(0) != NULL) {
        void *t = model.resMdl;
        if (anims[0].allocMatAnm((NNSG3dResMdl *)(t), r4->getHeap())) {
            anims[0].init(((FtrAnimSet *)(modelRes.getAnimSet()))->getBma(0), 3, 0x1000, 0);
            anims[0].addToRenderObj(model.getRenderObj());
        }
    }
    if (switchState.isOn() != 0 && FtrMgr_IsShopScene() == 0) {
        changeAct(2, 0xff);
    } else {
        changeAct(0, 0xff);
    }
    return TRUE;
}

FtrKind19::~FtrKind19() {
}

FtrKind19::FtrKind19() {
}

extern "C" void *FtrKind19_Create() {
    return new FtrKind19;
}



class FtrGyroid;

namespace p16 {
extern "C" {


s32 Scene_InVillagerHouse(void);
}
}

class FtrGyroid : public FtrActor {
public:
    FtrGyroid();
    virtual ~FtrGyroid();
    virtual BOOL onDelete();
    virtual BOOL onJointCalcPre(s32 nodeId, NNSG3dRS *rs);
    virtual void onJointCalcPost(s32 idx, void *b);
    virtual BOOL changeAct(u32 idx, u8 x);
    virtual u8 getActSwitchState(u32 idx);
    virtual BOOL initModel();
    virtual BOOL updateActive();
    virtual BOOL updateAppearRemove();

    void execFtrAct02();
    BOOL enterFtrAct02();
    void execFtrAct01();
    BOOL enterFtrAct01();
    void execFtrAct00();
    BOOL enterFtrAct00();
    void execFtrAct();
    s32 pollSyncStarted();
    u32 readSyncBeat();
    void setSyncStartBeat(u32 v);
    void setSyncState(u32 v);
    void releaseSync();
    s32 updateSync(VecFx32 *v);
    void initSync(u32 v);

    /* 0x840 */ Rb bgmSync;
    /* 0x854 */ u8 bgmSyncActive;
    /* 0x855 */ u8 pad_855[3];
    /* 0x858 */ s32 frameCount;
    /* 0x85c */ u16 syncStartFrames;
    /* 0x85e */ u8 ftrAct;
    /* 0x85f */ u8 pad_85f;
};

typedef void (FtrGyroid::*Unk_ov004_0220da7c_Fn)();
typedef BOOL (FtrGyroid::*Unk_ov004_0220daf8_Fn)();

BOOL FtrGyroid::enterFtrAct02() {
    switchState.set(1, 0);
    ((FtrActor *)(this))->playAnim(0, 0, 0x1000, 0);
    NNSG3dResAnmCommon *r = ((FtrAnimSet *)(modelRes.getAnimSet()))->getBca(0);
    model.initAnim(r, 0, 0, 0, 0);
    return TRUE;
}

void FtrGyroid::execFtrAct01() {
    updateSync((VecFx32 *)&position);
    if (syncStartFrames != 0) {
        model.stepBlend();
        syncStartFrames -= TICK_STEP_ENDS() ? 1 : 0;
    }
    if (syncStartFrames == 0) {
        changeAct(2, getActAid());
    } else {
        s32 r = pollSyncStarted();
        if (r >= 0) {
            syncStartFrames = r;
            NNSG3dResAnmCommon *q = ((FtrAnimSet *)(modelRes.getAnimSet()))->getBca(0);
            model.playBlend(q, (u16)r, 0, 0, 0, 0);
        }
    }
    if (switchState.isChanging()) {
        switchState.set(1, 0);
        s32 s = Scene_GetCurrent();
        FtrSync_RequestToggleGyroid(s, &position, FtrActor_GetLayer(this));
    }
}

BOOL FtrGyroid::enterFtrAct01() {
    s32 a, b;
    ((FtrActor *)(this))->playSound1();
    switchState.set(1, 0);
    syncStartFrames = 0xffff;
    FieldPos_ToUnit(&a, &b, &position);
    if (isInitializing != 0) {
        if (spawnMode != 0 || p16::Scene_InVillagerHouse() != 0) {
            Snd_BgmSyncSetState(&bgmSync, 1);
            u32 r5 = Snd_BgmSyncReadBeat() & 0xf;
            RoomFtrState_SetGyroidBeat(a, b, (u8)r5, Scene_GetCurrent());
            actAid = r5;
            NNSG3dResAnmCommon *q = ((FtrAnimSet *)(modelRes.getAnimSet()))->getBca(0);
            model.initAnim(q, 0, 0, 0, 0);
            model.stepBlend();
            syncStartFrames = 0;
        } else {
            setSyncState(2);
            u32 r5 = RoomFtrState_GetGyroidBeat(a, b, Scene_GetCurrent()) & 0xf;
            setSyncStartBeat((u8)r5);
            actAid = r5;
            void *q = FtrMoveAnim_GetHaniwaAnim((FtrMoveAnim *)FurnitureManager_GetMoveAnim());
            model.initAnim(q, 0, 0, 0, 0);
            model.stepBlend();
        }
    } else if (((CommManager *)(gCommManager))->isOnline() != 0 && getActAid() != 0xff) {
        setSyncState(1);
        u32 r5 = getActAid();
        u32 t = r5 & 0xf;
        RoomFtrState_SetGyroidBeat(a, b, (u8)t, Scene_GetCurrent());
        void *q = FtrMoveAnim_GetHaniwaAnim((FtrMoveAnim *)FurnitureManager_GetMoveAnim());
        model.initAnim(q, 0, 0, 0, 0);
        model.stepBlend();
    } else {
        setSyncState(1);
        u32 r5 = readSyncBeat() & 0xf;
        RoomFtrState_SetGyroidBeat(a, b, (u8)r5, Scene_GetCurrent());
        actAid = r5;
        void *q = FtrMoveAnim_GetHaniwaAnim((FtrMoveAnim *)FurnitureManager_GetMoveAnim());
        model.initAnim(q, 0, 0, 0, 0);
        model.stepBlend();
    }
    return TRUE;
}

void FtrGyroid::execFtrAct00() {
    updateSync((VecFx32 *)&position);
    model.stepBlend();
    if (switchState.isChanging()) {
        switchState.set(0, 0);
        s32 s = Scene_GetCurrent();
        FtrSync_RequestToggleGyroid(s, &position, FtrActor_GetLayer(this));
    }
}

BOOL FtrGyroid::enterFtrAct00() {
    s32 a, b;
    FieldPos_ToUnit(&a, &b, &position);
    actAid = 0xff;
    RoomFtrState_RemoveGyroidBeat(a, b, Scene_GetCurrent());
    setSyncState(0);
    ((FtrActor *)(this))->playSound2();
    switchState.set(0, 0);
    if (FurnitureManager_GetMoveAnim() != 0) {
        void *q = FtrMoveAnim_GetHaniwaAnim((FtrMoveAnim *)FurnitureManager_GetMoveAnim());
        if (isInitializing != 0) {
            model.initAnim(q, 0, 0, 0, 0);
        } else {
            model.playBlend(q, 0x20, 0, 0, 0, 0);
        }
    }
    return TRUE;
}

void FtrGyroid::execFtrAct() {
    static Unk_ov004_0220da7c_Fn tbl[3] = {
        &FtrGyroid::execFtrAct00,
        &FtrGyroid::execFtrAct01,
        &FtrGyroid::execFtrAct02,
    };
    u32 i = ftrAct;
    if (i < 3) {
        (this->*tbl[i])();
    }
}

BOOL FtrGyroid::changeAct(u32 idx, u8 x) {
    FtrActor::changeAct(idx, x);
    static Unk_ov004_0220daf8_Fn tbl[3] = {
        &FtrGyroid::enterFtrAct00,
        &FtrGyroid::enterFtrAct01,
        &FtrGyroid::enterFtrAct02,
    };
    if (idx < 3) {
        if ((this->*tbl[idx])()) {
            ftrAct = idx;
            return TRUE;
        }
    }
    return FALSE;
}

u8 FtrGyroid::getActSwitchState(u32 idx) {
    if (idx < 3) {
        return data_ov004_02240040[idx];
    }
    return 0;
}

s32 FtrGyroid::pollSyncStarted() {
    if (bgmSyncActive != 0) {
        return Snd_BgmSyncPollStarted(&bgmSync);
    }
    return -1;
}

u32 FtrGyroid::readSyncBeat() {
    if (bgmSyncActive != 0) {
        return Snd_BgmSyncReadBeat();
    }
    return 0;
}

void FtrGyroid::setSyncStartBeat(u32 v) {
    if (bgmSyncActive != 0) {
        Snd_BgmSyncSetStartBeat(&bgmSync, v);
    }
}

void FtrGyroid::setSyncState(u32 v) {
    if (bgmSyncActive != 0) {
        Snd_BgmSyncSetState(&bgmSync, v);
    }
}

void FtrGyroid::releaseSync() {
    if (bgmSyncActive != 0) {
        Snd_BgmSyncRelease(&bgmSync);
        bgmSyncActive = 0;
    }
}

s32 FtrGyroid::updateSync(VecFx32 *v) {
    if (bgmSyncActive != 0) {
        VecFx32 t;
        t.x = v->x;
        t.y = v->y;
        t.z = v->z;
        return Snd_BgmSyncUpdate(&bgmSync, &t);
    }
    return -1;
}

void FtrGyroid::initSync(u32 v) {
    if (bgmSyncActive == 0) {
        Snd_BgmSyncInit(&bgmSync, v);
        bgmSyncActive = 1;
    }
}

void FtrGyroid::onJointCalcPost(s32 idx, void *b) {
    NNSG3dRS *o = (NNSG3dRS *)b;
    u8 *d = o->pResNodeInfo;
    u32 off = *(u16 *)(d + 6);
    u8 *tbl = d + off;
    u32 esz = *(u16 *)tbl;
    u8 *rec = d + *(u32 *)(tbl + esz * idx + 4);
    s32 *v = (s32 *)(rec + 4);
    NNSG3dJntAnmResult *m = o->pJntAnmResult;
    m->trans.x = v[0];
    m->trans.y = v[1];
    m->trans.z = v[2];
    model.onJointCalcPost(o);
}

BOOL FtrGyroid::onJointCalcPre(s32 nodeId, NNSG3dRS *rs) {
    this->model.onJointCalcPre(rs);
    return TRUE;
}

BOOL FtrGyroid::onDelete() {
    releaseSync();
    return TRUE;
}

BOOL FtrGyroid::updateAppearRemove() {
    updateActive();
    return TRUE;
}

BOOL FtrGyroid::updateActive() {
    execFtrAct();
    frameCount++;
    return TRUE;
}

BOOL FtrGyroid::initModel() {
    frameCount = 0;
    actAid = 0xff;
    initSync(FtrSound_GetSe3(FtrActor_GetFtrIndex(this)));
    ((FtrActor *)(this))->initAnims(0, 1, 0x1000, 0);
    model.allocJointRecord(FtrActor_GetHeap(this)->getHeap());
    if (spawnMode == 1) {
        switchState.set(0, 0);
        s32 s = Scene_GetCurrent();
        FtrSync_RequestToggleGyroid(s, &position, FtrActor_GetLayer(this));
    } else if (((FtrActor *)(this))->isPreview() != 0) {
        changeAct(0, 0xff);
    } else if (switchState.isOn() != 0) {
        changeAct(1, 0xff);
    } else {
        changeAct(0, 0xff);
    }
    return TRUE;
}

FtrGyroid::~FtrGyroid() {
}

FtrGyroid::FtrGyroid() {
    actAid = 0xff;
}

extern "C" void *FtrGyroid_Create() {
    return new FtrGyroid;
}


namespace p17 {
extern "C" {
}
}




namespace p17 {
extern "C" {
}
}

class FtrCart : public FtrActor {
public:
    FtrCart();
    virtual ~FtrCart();
    virtual BOOL onDelete();
    virtual BOOL initModel();
    virtual BOOL updateActive();
    virtual void onMoveStart(BOOL isPush);
};

class FtrTv : public FtrActor {
public:
    FtrTv();
    virtual ~FtrTv();
    virtual BOOL onDelete();
    virtual BOOL changeAct(u32 idx, u8 v);
    virtual u8 getActSwitchState(u32 idx);
    virtual BOOL initModel();
    virtual BOOL updateActive();

    void execFtrAct01();
    BOOL enterFtrAct01();
    void execFtrAct00();
    BOOL enterFtrAct00();
    void execFtrAct();
    void markNearestTv();

    /* 0x840 */ u8 ftrAct;
    /* 0x844 */ FtrGlowMat screenMat;
    /* 0x860 */ u8 isNearestTv;
};

class FtrTvVcr : public FtrTv {
public:
    FtrTvVcr();
    virtual ~FtrTvVcr();
    virtual BOOL onDelete();
    virtual BOOL changeAct(u32 idx, u8 v);
    virtual u8 getActSwitchState(u32 idx);
    virtual BOOL initModel();
    virtual BOOL updateActive();

    void execVcrAct03();
    BOOL enterVcrAct03();
    void execVcrAct02();
    BOOL enterVcrAct02();
    void execVcrAct01();
    BOOL enterVcrAct01();
    void execVcrAct00();
    BOOL enterVcrAct00();
    void execVcrAct();

    /* 0x861 */ u8 vcrAct;
};


BOOL FtrCart::onDelete() {
    return TRUE;
}

BOOL FtrCart::updateActive() {
    FtrActor_StepAnims(this);
    return TRUE;
}

BOOL FtrCart::initModel() {
    initAnims(0, 0, 0, 0);
    return TRUE;
}

FtrCart::~FtrCart() {
}

FtrCart::FtrCart() {
}

extern "C" FtrActor *FtrCart_Create() {
    return new FtrCart;
}

void FtrTvVcr::execVcrAct03() {
    switchState.set(0, 0);
    if (FtrActor_StepAnims(this)) {
        changeAct(0, 0xff);
    }
}

BOOL FtrTvVcr::enterVcrAct03() {
    switchState.set(0, 0);
    screenMat.setLit(0, 1, 0);
    bindTvScreenTex(0);
    FtrActor_PlayAnimsFromLastFrame(this, 0, 3, 0x1000);
    playSound2();
    return TRUE;
}

void FtrTvVcr::execVcrAct02() {
    if (switchState.isChanging()) {
        FtrSync_RequestAct(this, 3, 0xff, 1);
    }
}

BOOL FtrTvVcr::enterVcrAct02() {
    switchState.set(1, 0);
    screenMat.setLit(1, 1, 0);
    bindTvScreenTex(1);
    FtrActor_PlayAnimsFromLastFrame(this, 0, 1, 0x1000);
    return TRUE;
}

void FtrTvVcr::execVcrAct01() {
    switchState.set(1, 0);
    if (FtrActor_StepAnims(this)) {
        changeAct(2, 0xff);
    }
}

BOOL FtrTvVcr::enterVcrAct01() {
    switchState.set(1, 0);
    screenMat.setLit(1, 1, 0);
    bindTvScreenTex(1);
    playAnim(0, 1, 0x1000, 0);
    playSound1();
    return TRUE;
}

void FtrTvVcr::execVcrAct00() {
    if (switchState.isChanging()) {
        FtrSync_RequestAct(this, 1, 0xff, 1);
    }
}

BOOL FtrTvVcr::enterVcrAct00() {
    switchState.set(0, 0);
    screenMat.setLit(0, 1, 0);
    bindTvScreenTex(0);
    playAnim(0, 3, 0x1000, 0);
    return TRUE;
}

void FtrTvVcr::execVcrAct() {
    static void (FtrTvVcr::*tbl[4])() = {
        &FtrTvVcr::execVcrAct00,
        &FtrTvVcr::execVcrAct01,
        &FtrTvVcr::execVcrAct02,
        &FtrTvVcr::execVcrAct03,
    };
    u32 i = vcrAct;
    if (i < 4) {
        (this->*tbl[i])();
    }
}

BOOL FtrTvVcr::changeAct(u32 idx, u8 v) {
    FtrActor::changeAct(idx, v);
    static BOOL (FtrTvVcr::*tbl[4])() = {
        &FtrTvVcr::enterVcrAct00,
        &FtrTvVcr::enterVcrAct01,
        &FtrTvVcr::enterVcrAct02,
        &FtrTvVcr::enterVcrAct03,
    };
    if (idx < 4) {
        if ((this->*tbl[idx])()) {
            vcrAct = idx;
            return TRUE;
        }
    }
    return FALSE;
}

u8 FtrTvVcr::getActSwitchState(u32 idx) {
    if (idx < 4) {
        return data_ov004_0224005c[idx];
    }
    return 0;
}

BOOL FtrTvVcr::onDelete() {
    return TRUE;
}

BOOL FtrTvVcr::updateActive() {
    screenMat.updateEmission();
    execVcrAct();
    return TRUE;
}

BOOL FtrTvVcr::initModel() {
    initAnims(0, 1, 0x1000, 0);
    void *res = model.resMdl;
    u8 t = switchState.isOn();
    screenMat.bindMaterial((G3dResAccess *)res, (const char *)data_ov004_0224bb98, t);
    if (switchState.isOn() != 0 && FtrMgr_IsShopScene() == 0) {
        changeAct(2, 0xff);
    } else {
        changeAct(0, 0xff);
    }
    return TRUE;
}

FtrTvVcr::~FtrTvVcr() {
}

FtrTvVcr::FtrTvVcr() {
}

extern "C" FtrActor *FtrTvVcr_Create() {
    return new FtrTvVcr;
}

void FtrTv::execFtrAct01() {
    if (switchState.isChanging()) {
        FtrSync_RequestAct(this, 0, 0xff, 1);
    }
}

BOOL FtrTv::enterFtrAct01() {
    playSound1();
    screenMat.setLit(1, 1, 0);
    switchState.set(1, 0);
    bindTvScreenTex(1);
    return TRUE;
}

void FtrTv::execFtrAct00() {
    if (switchState.isChanging()) {
        FtrSync_RequestAct(this, 1, 0xff, 1);
    }
}

BOOL FtrTv::enterFtrAct00() {
    playSound2();
    screenMat.setLit(0, 1, 0);
    switchState.set(0, 0);
    bindTvScreenTex(0);
    return TRUE;
}

void FtrTv::execFtrAct() {
    static void (FtrTv::*tbl[2])() = {
        &FtrTv::execFtrAct00,
        &FtrTv::execFtrAct01,
    };
    u32 i = ftrAct;
    if (i < 2) {
        (this->*tbl[i])();
    }
}

BOOL FtrTv::changeAct(u32 idx, u8 v) {
    FtrActor::changeAct(idx, v);
    static BOOL (FtrTv::*tbl[2])() = {
        &FtrTv::enterFtrAct00,
        &FtrTv::enterFtrAct01,
    };
    if (idx < 2) {
        if ((this->*tbl[idx])()) {
            ftrAct = idx;
            return TRUE;
        }
    }
    return FALSE;
}

u8 FtrTv::getActSwitchState(u32 idx) {
    if (idx < 2) {
        return data_ov004_0224003c[idx];
    }
    return 0;
}

void FtrTv::markNearestTv() {
    isNearestTv = 1;
}

BOOL FtrTv::onDelete() {
    return TRUE;
}

BOOL FtrTv::updateActive() {
    screenMat.updateEmission();
    execFtrAct();
    isNearestTv = 0;
    return TRUE;
}

BOOL FtrTv::initModel() {
    void *res = model.resMdl;
    u8 t = switchState.isOn();
    screenMat.bindMaterial((G3dResAccess *)res, (const char *)data_ov004_0224bb98, t);
    if (switchState.isOn() != 0 && FtrMgr_IsShopScene() == 0) {
        changeAct(1, 0xff);
    } else {
        changeAct(0, 0xff);
    }
    return TRUE;
}

FtrTv::~FtrTv() {
}

FtrTv::FtrTv() {
}

extern "C" FtrActor *FtrTv_Create() {
    return new FtrTv;
}


BOOL FtrActor::bindTvScreenTex(BOOL a) {
    if (a != 0) {
        void *r = model.resMdl;
        void *t = FurnitureManager_GetTvTex();
        Model_BindMatTexByIdx(r, (const char *)data_ov004_0224bb98, t, 0, 0);
    } else {
        void *r = model.resMdl;
        void *t = modelRes.getTexture();
        Model_BindMatTexByName(r, (const char *)data_ov004_0224bb98, t, (const char *)data_ov004_0224bba0, (const char *)data_ov004_0224bba8);
    }
    return TRUE;
}

namespace p18 {
extern "C" {
}
}


class FtrStereo : public FtrActor {
public:
    FtrStereo();
    virtual ~FtrStereo();

    virtual BOOL onDelete();
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual BOOL changeAct(u32 a, u8 b);
    virtual u8 getActSwitchState(u32 a);
    virtual BOOL initModel();
    virtual BOOL updateActive();
    virtual BOOL updateAppearRemove();

    void execFtrAct01();
    BOOL enterFtrAct01();
    void execFtrAct00();
    BOOL enterFtrAct00();
    void execFtrAct();
    void execTalkAct05();
    BOOL enterTalkAct05();
    void execTalkAct04();
    BOOL enterTalkAct04();
    BOOL execTalkAct03();
    BOOL enterTalkAct03();
    void execTalkAct02();
    BOOL enterTalkAct02();
    BOOL execTalkAct01();
    BOOL enterTalkAct01();
    void execTalkAct00();
    BOOL enterTalkAct00();
    void execTalkAct();
    BOOL setTalkAct(s32 a);
    void stopSong(u32 a, BOOL b);
    void startSong(u32 a);
    /* 0x840 */ u8 songPlaying;
    /* 0x841 */ u8 curSong;
    /* 0x842 */ u8 pad_842[2];
    /* 0x844 */ FtrGlowMatSet glowMats;
    /* 0x89c */ u8 ftrAct;
    /* 0x89d */ u8 pad_89d[3];
    /* 0x8a0 */ s32 talkAct;
};

namespace p18 {
extern "C" {
#define gSaveVillagers HOST_LABEL(u8 (*)[], gSaveVillagers)
s32 Scene_InVillagerHouse();
s32 Scene_InHouseRoom();
void *SaveVillagers_Get(void *p, s32 a);
u32 Villager_GetInfo4d(void *v);
s32 FtrActor_TestPlayerUnk();
}
}

static BOOL FtrActor_IsStereoOn(FtrActor *a) { return a->isStereoOn(); }

typedef void (FtrStereo::*Unk_ov004_0220ead4_Fn)();
typedef BOOL (FtrStereo::*Unk_ov004_0220eb40_Fn)();

static inline BOOL Unk_ov004_0220eff4_InRange(volatile u16 *p) {
    u32 hi = *p;
    u32 lo = *p;
    BOOL r = FALSE;
    if (lo >= 0x1323 && hi <= 0x1368) r = TRUE;
    return r;
}

static inline u16 Unk_ov004_0220ec30_Val(u32 t) {
    if (t < 0x46) {
        return t + 0x1323;
    }
    return 0x1323;
}

BOOL FtrStereo::enterFtrAct01() {
    playSound1();
    FtrMgr_SetSwitchAll(0, FtrActor_IsStereoOn, 0);
    switchState.set(1, 0);
    u8 *p = &actAid;
    curSong = *p;
    startSong(*p);
    if (kind == 0x29) {
        playAnim(1, 0, 0x1000, 0);
    }
    return TRUE;
}

void FtrStereo::execFtrAct00() {
    if (kind == 0x29) {
        FtrActor_StepAnims(this);
    }
    glowMats.setLit(0, 1, 0);
    if (switchState.isChanging()) {
        switchState.set(0, 0);
        TalkRequest_AddPlayerTalk6(this, 0);
        PlayerActor_KeepAnimForNextAction();
    }
}

BOOL FtrStereo::enterFtrAct00() {
    playSound2();
    switchState.set(0, 0);
    if (isInitializing == 0) {
        stopSong(curSong, 1);
    }
    if (kind == 0x29) {
        playAnim(0, 1, 0x1000, 0);
    }
    return TRUE;
}

void FtrStereo::execFtrAct() {
    static Unk_ov004_0220ead4_Fn tbl[2] = {
        &FtrStereo::execFtrAct00,
        &FtrStereo::execFtrAct01,
    };
    if (ftrAct < 2) {
        (this->*tbl[ftrAct])();
    }
}

BOOL FtrStereo::changeAct(u32 a, u8 b) {
    FtrActor::changeAct(a, b);
    static Unk_ov004_0220eb40_Fn tbl[2] = {
        &FtrStereo::enterFtrAct00,
        &FtrStereo::enterFtrAct01,
    };
    if (a < 2) {
        if ((this->*tbl[a])()) {
            ftrAct = a;
            return TRUE;
        }
    }
    return FALSE;
}

u8 FtrStereo::getActSwitchState(u32 a) {
    if (a < 2) {
        return data_ov004_02240028[a];
    }
    return 0;
}

void FtrStereo::execTalkAct05() {
    if (window != NULL) {
        if (window->state == 0) {
            ((Character *)(this))->detachTalkRequest(this);
            TalkRequest_SetTargetDone(this);
        }
    }
}

BOOL FtrStereo::enterTalkAct05() {
    return TRUE;
}

void FtrStereo::execTalkAct04() {
    if (window != NULL) {
        if (window->state != 0) {
            setTalkAct(5);
        }
    }
}

BOOL FtrStereo::enterTalkAct04() {
    ((Character *)(this))->attachTalkRequest(this);
    window->nextState = 1;
    {
        TalkMsgRequest &sec = *this;
        ((MsgRequest *)(&sec))->setFileName((const char *)(data_ov004_0224bbb0));
    }
    struct { u32 pad; u16 v; } l;
    if (p18::Scene_InVillagerHouse()) {
        u32 t = 0;
        u32 r = Scene_GetVillagerHouse();
        void *v = p18::SaveVillagers_Get(gSaveVillagers, r);
        if (v) {
            t = p18::Villager_GetInfo4d(v);
        }
        l.v = Unk_ov004_0220ec30_Val(t);
        ItemName name(&l.v);
        msgIndex = 5;
        ((TalkWindowState *)(window))->setNamedSlot(0, &name, 7);
    } else {
        u16 *p = HouseRoom_GetCurrentSong();
        BOOL ok = FALSE;
        if (*p >= 0x1323 && *p <= 0x1368) ok = TRUE;
        if (ok) {
            ItemName name(p);
            msgIndex = 5;
            ((TalkWindowState *)(window))->setNamedSlot(0, &name, 7);
        } else {
            msgIndex = 6;
        }
    }
    return TRUE;
}

BOOL FtrStereo::execTalkAct03() {
    return setTalkAct(4);
}

BOOL FtrStereo::enterTalkAct03() {
    return TRUE;
}

void FtrStereo::execTalkAct02() {
    if (MenuCtrl_IsFinished()) {
        if (MenuCtrl_IsResultOk()) {
            volatile u16 vv;
            vv = MenuCtrl_GetSongItem();
            BOOL ok = FALSE;
            u32 v = vv;
            if (v < 0x1323 || v > 0x1368) {
            } else {
                ok = TRUE;
            }
            s32 t;
            if (ok) {
                t = v - 0x1323;
            } else {
                t = -1;
            }
            FtrSync_RequestAct(this, 1, t, 1);
        }
        TalkRequest_SetTargetDone(this);
    }
}

BOOL FtrStereo::enterTalkAct02() {
    if (MenuCtrl_OpenLauncher(0x40)) {
        return TRUE;
    }
    return FALSE;
}

BOOL FtrStereo::execTalkAct01() {
    return setTalkAct(2);
}

BOOL FtrStereo::enterTalkAct01() {
    return TRUE;
}

void FtrStereo::execTalkAct00() {
}

BOOL FtrStereo::enterTalkAct00() {
    return TRUE;
}

Unk_ov004_0220ead4_Fn FtrStereo_execTalkAct_tbl[6];
u8 FtrStereo_execTalkAct_tbl_init;
void FtrStereo::execTalkAct() {
    if (!FtrStereo_execTalkAct_tbl_init) {
        HOST_STATIC_INIT_ARRAY(FtrStereo_execTalkAct_tbl, {
        &FtrStereo::execTalkAct00,
        (Unk_ov004_0220ead4_Fn)&FtrStereo::execTalkAct01,
        &FtrStereo::execTalkAct02,
        (Unk_ov004_0220ead4_Fn)&FtrStereo::execTalkAct03,
        &FtrStereo::execTalkAct04,
        &FtrStereo::execTalkAct05,
    });
        FtrStereo_execTalkAct_tbl_init = 1;
    }
    if (talkAct < 6) {
        (this->*FtrStereo_execTalkAct_tbl[talkAct])();
    }
}

BOOL FtrStereo::setTalkAct(s32 a) {
    static Unk_ov004_0220eb40_Fn tbl[6] = {
        &FtrStereo::enterTalkAct00,
        &FtrStereo::enterTalkAct01,
        &FtrStereo::enterTalkAct02,
        &FtrStereo::enterTalkAct03,
        &FtrStereo::enterTalkAct04,
        &FtrStereo::enterTalkAct05,
    };
    if (a < 6) {
        if ((this->*tbl[a])()) {
            talkAct = a;
            return TRUE;
        }
    }
    return FALSE;
}

void FtrStereo::onInteractionEvent(u32 a, u8 b) {
    switch (a) {
    case 1:
        if (p18::Scene_InHouseRoom() && p18::FtrActor_TestPlayerUnk()) {
            setTalkAct(1);
        } else {
            setTalkAct(3);
        }
        break;
    case 8:
        setTalkAct(0);
        break;
    }
}

void FtrStereo::stopSong(u32 a, BOOL b) {
    if (songPlaying != 0) {
        if (a < 0x46) {
            Bgm_Release(a + 0xb0);
            if (b) {
                u16 v = 0xfff1;
                HouseRoom_SetCurrentSong(&v);
            }
            songPlaying = 0;
        }
    }
}

void FtrStereo::startSong(u32 a) {
    if (songPlaying == 0) {
        if (a < 0x46) {
            Bgm_Request(0x11, a + 0xb0, 0x7f, 0);
            u16 v = Unk_ov004_0220ec30_Val(a);
            HouseRoom_SetCurrentSong(&v);
            songPlaying = 1;
        }
    }
}

BOOL FtrStereo::onDelete() {
    BOOL t = isRemoving();
    stopSong(curSong, t);
    BOOL r = FALSE;
    volatile u16 *pg = &sStereoSong.id;
    u32 hi = *pg;
    u32 lo = *pg;
    if (lo >= 0x1323 && hi <= 0x1368) r = TRUE;
    if (r) {
        sStereoSong.id = 0xfff1;
    }
    return TRUE;
}

BOOL FtrStereo::updateAppearRemove() {
    return updateActive();
}

BOOL FtrStereo::updateActive() {
    execFtrAct();
    execTalkAct();
    glowMats.update();
    return TRUE;
}

BOOL FtrStereo::initModel() {
    if (kind == 0x29 || kind == 0x13) {
        initAnims(0, 0, 0x1000, 0);
    }
    void *r4 = model.resMdl;
    u32 c = switchState.isOn();
    glowMats.init(r4, c);
    if (spawnMode == 1) {
        FtrSync_ChangeAct(this, 0, 0xff, 1);
    } else if (switchState.isOn() != 0 && FtrMgr_IsShopScene() == 0) {
        if (p18::Scene_InVillagerHouse()) {
            u32 t = 0;
            u32 r = Scene_GetVillagerHouse();
            void *v = p18::SaveVillagers_Get(gSaveVillagers, r);
            if (v) {
                t = p18::Villager_GetInfo4d(v);
            }
            BOOL f = FALSE;
            volatile u16 *pg = &sStereoSong.id;
            u32 hi = *pg;
            u32 lo = *pg;
            if (lo >= 0x1323 && hi <= 0x1368) f = TRUE;
            if (f) {
                changeAct(0, 0xff);
            } else if (changeAct(1, t)) {
                sStereoSong.id = Unk_ov004_0220ec30_Val(t);
            }
        } else {
            volatile u16 v;
            v = *HouseRoom_GetCurrentSong();
            BOOL f = FALSE;
            u32 hi = v;
            u32 lo = v;
            if (lo >= 0x1323 && hi <= 0x1368) f = TRUE;
            if (f) {
                s32 x;
                if (hi >= 0x1323 && hi <= 0x1368) {
                    x = hi - 0x1323;
                } else {
                    x = -1;
                }
                changeAct(1, x);
            } else {
                HouseRoom_ClearCurrentSong();
                changeAct(0, 0xff);
            }
        }
    } else {
        changeAct(0, 0xff);
    }
    return TRUE;
}

FtrStereo::~FtrStereo() {}

FtrStereo::FtrStereo() {}

extern "C" void *FtrStereo_Create() {
    return new FtrStereo;
}

union Unk_ov004_0220f2c0_Pad {
    u16 h;
    u8 b[2];
};

class FtrClock : public FtrActor {
public:
    FtrClock();
    virtual ~FtrClock();
    virtual BOOL onDelete();
    virtual void onJointCalcPost(s32 a, void *b);
    virtual BOOL initModel();
    virtual BOOL updateActive();

    void markNearestCabinClock();
    void markNearestSoundingClock();

    /* 0x840 */ s8 chimesLeft;
    /* 0x841 */ s8 prevChimesLeft;
    /* 0x842 */ Unk_ov004_0220f2c0_Pad curTime;
    /* 0x844 */ Unk_ov004_0220f2c0_Pad prevTime;
    /* 0x846 */ u8 isNearestSoundingClock;
    /* 0x847 */ u8 isNearestCabinClock;
};

void FtrClock::markNearestCabinClock() {
    isNearestCabinClock = 1;
}

void FtrClock::markNearestSoundingClock() {
    isNearestSoundingClock = 1;
}


namespace p19 {
extern "C" {
}
}



namespace p19 {
extern "C" {
extern BlockMap *gSceneBlockMap;

void Clock_GetMinuteHour(void *);
}
}

BOOL FtrClock::onDelete() {
    return TRUE;
}

BOOL FtrClock::updateActive() {
    prevTime.h = curTime.h;
    p19::Clock_GetMinuteHour(&curTime);
    if (kind == 0x10) {
        if (!isPreview() && chimesLeft >= 0 && chimesLeft != prevChimesLeft && isNearestCabinClock != 0) {
            soundEmitter.setPitch(1);
        }
        prevChimesLeft = chimesLeft;
        if (chimesLeft == -1) {
            if (isPreview()) {
                chimesLeft = 1;
            } else if (!FtrMgr_IsShopScene() && prevTime.b[1] != curTime.b[1]) {
                s32 t = curTime.b[1];
                chimesLeft = t % 12;
                if (chimesLeft == 0) {
                    chimesLeft = 12;
                }
                if (!isPreview()) {
                    soundEmitter.playOnce(0x42d, &centerPos);
                }
                model.initAnim(((FtrAnimSet *)((void *)modelRes.getAnimSet()))->getBca(0), 1, 0x1000, 0, 0);
            }
        } else if (chimesLeft > 0) {
            if (!isPreview()) {
                soundEmitter.playOnce(0x42d, &centerPos);
            }
            model.stepBlend();
            if (model.isFinished()) {
                model.initAnim(((FtrAnimSet *)((void *)modelRes.getAnimSet()))->getBca(0), 1, 0x1000, 0, 0);
                if (!isPreview()) {
                    chimesLeft = chimesLeft - 1;
                }
                if (chimesLeft == 0) {
                    chimesLeft = -1;
                }
            }
        }
    } else if (kind == 0x2b) {
        FtrActor_StepAnims(this);
    }
    s32 s = FtrMgr_GetCycleCounter();
    if (kind == 0x11) {
        model.setFrame(s);
    }
    if (isNearestSoundingClock != 0 && (s == 9 || s == 0x1d)) {
        if (kind == 0x10) {
            soundEmitter.play(0x4d0, &centerPos);
        } else {
            playSound3();
        }
    }
    isNearestSoundingClock = 0;
    isNearestCabinClock = 0;
    return TRUE;
}

BOOL FtrClock::initModel() {
    ModelSlot *r4 = FtrActor_GetHeap(this);
    p19::Clock_GetMinuteHour(&prevTime);
    curTime.h = prevTime.h;
    chimesLeft = -1;
    if (kind == 0x10) {
        if (model.allocAnmObj(r4->getHeap())) {
            model.initAnim(((FtrAnimSet *)((void *)modelRes.getAnimSet()))->getBca(0), 1, 0x1000, 0, 0);
            model.attachAnim();
        }
    } else if (kind == 0x11) {
        if (model.allocAnmObj(r4->getHeap())) {
            model.initAnim(((FtrAnimSet *)((void *)modelRes.getAnimSet()))->getBca(0), 0, 0x1000, 0, 0);
            model.attachAnim();
        }
    } else if (kind == 0x2b) {
        initAnims(0, 0, 0x1000, 0);
    }
    return TRUE;
}

FtrClock::~FtrClock() {
}

FtrClock::FtrClock() {
}

extern "C" void *FtrClock_Create() {
    return new FtrClock;
}



























namespace p20 {
extern "C" {
}
}
namespace p20 {
extern "C" {
}
}

class FtrStorage : public FtrActor {
public:
    FtrStorage();
    virtual ~FtrStorage();

    virtual BOOL onDelete();
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual BOOL changeAct(u32 a, u8 b);
    virtual u8 getActSwitchState(u32 a);
    virtual BOOL initModel();
    virtual BOOL updateActive();
    virtual BOOL isReady();

    void execTalkAct0B();
    BOOL enterTalkAct0B();
    void execTalkAct0A();
    BOOL enterTalkAct0A();
    void execTalkAct09();
    BOOL enterTalkAct09();
    void execTalkAct08();
    BOOL enterTalkAct08();
    void execTalkAct07();
    BOOL enterTalkAct07();
    BOOL execTalkAct06();
    BOOL enterTalkAct06();
    void execTalkAct05();
    BOOL enterTalkAct05();
    void execTalkAct04();
    BOOL enterTalkAct04();
    void execTalkAct03();
    BOOL enterTalkAct03();
    void execTalkAct02();
    BOOL enterTalkAct02();
    BOOL execTalkAct01();
    BOOL enterTalkAct01();
    void execTalkAct00();
    BOOL enterTalkAct00();
    void execTalkAct();
    BOOL setTalkAct(s32 s);
    s32 getStorageType();
    void execFtrAct03();
    BOOL enterFtrAct03();
    void execFtrAct02();
    BOOL enterFtrAct02();
    void execFtrAct01();
    BOOL enterFtrAct01();
    void execFtrAct00();
    BOOL enterFtrAct00();
    void execFtrAct();

    /* 0x840 */ FtrGlowMat glowMat;
    /* 0x85c */ u8 ftrAct;
    /* 0x85d */ u8 pad_85d[3];
    /* 0x860 */ u32 talkAct;
};

namespace p20 {
extern "C" {
extern u8 gTalkMsgIndexEnd[];

BOOL FtrActor_TestPlayerUnk(void);
BOOL Scene_InHouseRoom(void);
s32 Ground_GetExitAt(s32, s32);
u32 FtrActor_MakeSpawnArg(u32, u32, u32, u32, u8, u32);
}
}

typedef void (FtrStorage::*Unk_ov004_0220ff44_Fn)();
typedef BOOL (FtrStorage::*Unk_ov004_0220ffd0_Fn)();

s32 FtrStorage::getStorageType() {
    u32 i;
    for (i = 0; i < 3; i++) {
        if (kind == sFtrStorageKinds[i]) {
            return i;
        }
    }
    return -1;
}

void FtrStorage::onInteractionEvent(u32 a, u8 b) {
    switch (a) {
    case 1:
        if (p20::Scene_InHouseRoom()) {
            if (p20::FtrActor_TestPlayerUnk()) {
                setTalkAct(1);
            } else {
                setTalkAct(6);
            }
        } else {
            setTalkAct(6);
        }
        break;
    case 8:
        setTalkAct(0);
        break;
    }
}

void FtrStorage::execFtrAct03() {
    visNodes.setVisible(1);
    if (FtrActor_StepAnims(this)) {
        changeAct(0, 0xff);
    }
}

BOOL FtrStorage::enterFtrAct03() {
    switchState.set(1, 0);
    playSound2();
    if (kind == 0xf) {
        playAnim(1, 1, 0x1000, 0);
    } else {
        FtrActor_PlayAnimsFromLastFrame(this, 0, 3, 0x1000);
    }
    return TRUE;
}

void FtrStorage::execFtrAct02() {
    visNodes.setVisible(1);
    if (isPreview()) {
        changeAct(3, 0xff);
    }
}

BOOL FtrStorage::enterFtrAct02() {
    switchState.set(0, 0);
    if (kind == 0xf) {
        ((FtrAnimSet *)(modelRes.getAnimSet()))->getBca(0);
        FtrActor_PlayAnimsFromLastFrame(this, 0, 1, 0x1000);
    } else {
        FtrActor_PlayAnimsFromLastFrame(this, 0, 1, 0x1000);
    }
    return TRUE;
}

void FtrStorage::execFtrAct01() {
    visNodes.setVisible(1);
    if (FtrActor_StepAnims(this)) {
        changeAct(2, 0xff);
    }
}

BOOL FtrStorage::enterFtrAct01() {
    switchState.set(0, 0);
    playSound1();
    playAnim(0, 1, 0x1000, 0);
    return TRUE;
}

void FtrStorage::execFtrAct00() {
    s32 t;
    u32 i;
    visNodes.setVisible(0);
    void *e = ((FtrContactSet *)(FtrContactSet_GetInstance()))->findContact(this);
    if (switchState.isChanging() && e != NULL && ((FtrContact *)(e))->getSide() == 0) {
        if (kind == 0xb) {
            FtrTileList arr;
            VecFx32 v;
            ((FtrActor *)(this))->getTiles((FtrTileList *)&arr, 0, 0);
            v.x = 0;
            v.y = 0;
            v.z = 0x2000;
            Vec_RotateY(&v, rotY);
            volatile Vec2 p;
            p.x = 0;
            p.y = 0;
            p.x = v.x >> 13;
            p.y = v.z >> 13;
            for (i = 0; i < arr.getCount(); i++) {
                s32 a = p.x + arr.get(i)->x;
                t = p.y + arr.get(i)->y;
                if (FtrMgr_GetSurfaceHeight(a, t) != 0 || p20::Ground_GetExitAt(a, t) != -1) {
                    switchState.set(1, 0);
                    arr.release();
                    return;
                }
            }
            arr.release();
        }
        TalkRequest_AddPlayerTalk6(this, 0);
        PlayerActor_KeepAnimForNextAction();
    } else {
        if (isPreview()) {
            changeAct(1, 0xff);
        }
    }
}

BOOL FtrStorage::enterFtrAct00() {
    switchState.set(1, 0);
    if (kind == 0xf) {
        FtrActor_PlayAnimsFromLastFrame(this, 1, 1, 0x1000);
    } else {
        playAnim(0, 3, 0x1000, 0);
    }
    return TRUE;
}

void FtrStorage::execFtrAct() {
    static Unk_ov004_0220ff44_Fn tbl[4] = {
        &FtrStorage::execFtrAct00,
        &FtrStorage::execFtrAct01,
        &FtrStorage::execFtrAct02,
        &FtrStorage::execFtrAct03,
    };
    if (ftrAct < 4) {
        (this->*tbl[ftrAct])();
    }
}

BOOL FtrStorage::changeAct(u32 a, u8 b) {
    FtrActor::changeAct(a, b);
    static Unk_ov004_0220ffd0_Fn tbl[4] = {
        &FtrStorage::enterFtrAct00,
        &FtrStorage::enterFtrAct01,
        &FtrStorage::enterFtrAct02,
        &FtrStorage::enterFtrAct03,
    };
    if ((u32)a < 4) {
        if ((this->*tbl[a])()) {
            ftrAct = a;
            return TRUE;
        }
    }
    return FALSE;
}

u8 FtrStorage::getActSwitchState(u32 a) {
    if (a < 4) {
        return data_ov004_02240048[a];
    }
    return 0;
}

BOOL FtrStorage::isReady() {
    if (FtrActor::isReady()) {
        if (talkAct == 0) {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL FtrStorage::onDelete() {
    return TRUE;
}

BOOL FtrStorage::updateActive() {
    execTalkAct();
    execFtrAct();
    return TRUE;
}

BOOL FtrStorage::initModel() {
    visNodes.setVisible(0);
    if (spawnMode == 1) {
        switchState.set(1, 0);
    }
    if (kind == 0xf) {
        initAnims(0, 1, 0x1000, 0);
    } else {
        initAnims(0, 3, 0x1000, 0);
    }
    if (switchState.isOn() || FtrMgr_IsShopScene()) {
        changeAct(0, 0xff);
    } else {
        changeAct(2, 0xff);
    }
    setTalkAct(0);
    return TRUE;
}

FtrStorage::~FtrStorage() {
}

FtrStorage::FtrStorage() {
    ftrAct = 0;
}

extern "C" void *FtrStorage_Create() {
    return new FtrStorage;
}









namespace p21 {
extern "C" {
}
}

struct Unk_ov004_0221076c_R {
    s32 x;
    s32 y;
    s32 z;
};

namespace p21 {
extern "C" {
void VEC_Add(void *a, void *b, void *c);
s32 Ground_GetExitAt(s32 a, s32 b);
s32 Ground_GetExitAtPos(void *p);
extern char data_ov004_0224bbd0[];
extern char data_ov004_0224bbe4[];
extern s32 data_020c8cbc;

}
}

struct Unk_ov004_02210d58_P {
    s32 x, y;
    Unk_ov004_02210d58_P() {
        x = 0;
        y = 0;
    }
};

extern "C" {
BOOL FtrBed_IsTileFree(Unk_ov004_02210d58_P *p);
}


class FtrTilePair {
public:
    FtrTilePair();
    ~FtrTilePair();
    Unk_ov004_02210d58_P *get(u32 i);

    Unk_ov004_02210d58_P v[2];
};

class FtrBedLieTiles : public FtrTilePair {
public:
    FtrBedLieTiles();
    ~FtrBedLieTiles();
};

class FtrBedSideTiles : public FtrTilePair {
public:
    FtrBedSideTiles();
    ~FtrBedSideTiles();
};

struct FtrBedKindCheck {
    static inline BOOL R(u16 v) {
        return v == 0x37 ? TRUE : FALSE;
    }
};

struct FtrBedStackPad {
    s32 v[2];
    FtrBedStackPad() {}
    ~FtrBedStackPad() {}
};

class FtrBed : public FtrActor {
public:
    FtrBed();
    virtual ~FtrBed();
    virtual BOOL onDelete();
    virtual BOOL onDraw();
    virtual BOOL acceptsInteraction(void *a);
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual BOOL changeAct(u32 a, u8 v);
    virtual BOOL initModel();
    virtual BOOL updateActive();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);

    void execFtrAct0D();
    BOOL enterFtrAct0D();
    void execFtrAct0C();
    BOOL enterFtrAct0C();
    void execFtrAct0B();
    BOOL enterFtrAct0B();
    void execFtrAct0A();
    BOOL enterFtrAct0A();
    void execFtrAct09();
    BOOL enterFtrAct09();
    void execFtrAct08();
    BOOL enterFtrAct08();
    void execFtrAct07();
    BOOL enterFtrAct07();
    void execFtrAct06();
    BOOL enterFtrAct06();
    void execFtrAct05();
    BOOL enterFtrAct05();
    void execFtrAct04();
    BOOL enterFtrAct04();
    void execFtrAct03();
    BOOL enterFtrAct03();
    void execFtrAct02();
    BOOL enterFtrAct02();
    void execFtrAct01();
    BOOL enterFtrAct01();
    void execFtrAct00();
    BOOL enterFtrAct00();
    void execFtrAct();
    void calcStepPos(VecFx32 *out, VecFx32 *in, s32 ang, VecFx32 *opt);
    s32 checkStepTile(VecFx32 *a, s32 b, VecFx32 *c);
    u32 getLieTiles(void *o);
    u32 getSideTiles(void *o);
    BOOL isInUse();

    /* 0x840 */ u16 pushFrames;
    /* 0x842 */ u8 inLeftHalf;
    /* 0x843 */ u8 inFrontHalf;
    /* 0x844 */ u8 ownerPlayer;
    /* 0x845 */ u8 pad_845;
    /* 0x846 */ u16 approachTimer;
    /* 0x848 */ u16 leaveTimer;
    /* 0x84a */ u16 pad_84a;
    /* 0x84c */ s32 ownTileX;
    /* 0x850 */ s32 ownTileY;
    /* 0x854 */ s32 useMode;
    /* 0x858 */ u16 newBedItem;
    /* 0x85a */ u8 ftrAct;
    /* 0x85b */ u8 pad_85b;
    /* 0x85c */ FtrGlowMatSet glowMats;
};

extern "C" BOOL FtrBed_IsDma06Is5(u16 *p, s32 b) {
    if (b == 0) {
        if (Item_IsFurniture(p)) {
            if (Ftr_GetUnk06(p) == 5) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

BOOL FtrBed::enterFtrAct0B() {
    return TRUE;
}

void FtrBed::execFtrAct0A() {
    if (((TalkWindowState *)window)) {
        if (((TalkWindowState *)window)->state == 0) {
            if (MenuCtrl_OpenPocketSelect(MenuCtrl_BuildPocketMask(FtrBed_IsDma06Is5), 0x28)) {
                changeAct(0xb, 0xff);
            }
        }
    }
}

BOOL FtrBed::enterFtrAct0A() {
    return TRUE;
}

void FtrBed::execFtrAct09() {
    if (((TalkWindowState *)window)) {
        if (((TalkWindowState *)window)->state == 0) {
            ((Character *)(this))->detachTalkRequest(this);
            TalkRequest_SetTargetDone(this);
        }
    }
}

BOOL FtrBed::enterFtrAct09() {
    return TRUE;
}

void FtrBed::execFtrAct08() {
}

BOOL FtrBed::enterFtrAct08() {
    FtrBedStackPad pad;
    ((Character *)(this))->attachTalkRequest(this);
    ((TalkWindowState *)window)->nextState = 1;
    MsgRequest::setFileName(data_ov004_0224bbb0);
    msgIndex = 4;
    return TRUE;
}

void FtrBed::execFtrAct07() {
    changeAct(8, 0xff);
}

BOOL FtrBed::enterFtrAct07() {
    return TRUE;
}

void FtrBed::execFtrAct06() {
    if (((TalkWindowState *)window)) {
        if (((TalkWindowState *)window)->state == 0) {
            ((Character *)(this))->detachTalkRequest(this);
            TalkRequest_SetTargetDone(this);
            SceneWarp_RequestFade(Scene_GetWarpRequest(), 0x2e, 2, 0);
            SaveManager_RequestAct01();
        }
    }
}

BOOL FtrBed::enterFtrAct06() {
    return TRUE;
}

void FtrBed::execFtrAct05() {
    if (((TalkWindowState *)window)) {
        if (((TalkWindowState *)window)->state == 0) {
            PlayerActor_LocalRequestGetOutOfBed(inLeftHalf, 0);
            ((Character *)(this))->detachTalkRequest(this);
            TalkRequest_SetTargetDone(this);
        }
    }
}

BOOL FtrBed::enterFtrAct05() {
    return TRUE;
}

void FtrBed::execFtrAct04() {
}

BOOL FtrBed::enterFtrAct04() {
    FtrBedStackPad pad;
    ((Character *)(this))->attachTalkRequest(this);
    ((TalkWindowState *)window)->nextState = 1;
    if (GameStart_IsNewTown() || GameStart_IsNewResident()) {
        MsgRequest::setFileName(p21::data_ov004_0224bbd0);
        msgIndex = 0x19;
    } else {
        MsgRequest::setFileName(p21::data_ov004_0224bbe4);
        msgIndex = 0;
    }
    return TRUE;
}

void FtrBed::execFtrAct03() {
    if (approachTimer < 0x18) {
        approachTimer += TICK_STEP_ENDS() ? 1 : 0;
    }
    if (approachTimer == 0x18) {
        changeAct(4, 0xff);
    }
}

BOOL FtrBed::enterFtrAct03() {
    approachTimer = 0;
    return TRUE;
}

void FtrBed::execFtrAct02() {
    void *o = ((FtrContactSet *)(FtrContactSet_GetInstance()))->findContact(this);
    s16 v = ((FtrContact *)(o))->getPushAngle();
    Unk_ov004_0221076c_R *a = (Unk_ov004_0221076c_R *)((FtrContact *)(o))->getContactPoint();
    Unk_ov004_0221076c_R *b = (Unk_ov004_0221076c_R *)((FtrContact *)(o))->getContactPoint();
    if (PlayerActor_LocalRequestBedApproach(&a->x, &b->z, &v, (s16)(rotY - 0x4000), 1)) {
        changeAct(3, 0xff);
    }
}

BOOL FtrBed::enterFtrAct02() {
    return TRUE;
}

void FtrBed::execFtrAct01() {
    BOOL r4 = FALSE;
    useMode = 0;
    void *o = ((FtrContactSet *)(FtrContactSet_GetInstance()))->findContact(this);
    if (o) {
        if (ownerPlayer == PlayerData_GetCurrentIndex()) {
            if (((FtrContact *)(o))->getSide() == 2 || ((FtrContact *)(o))->getSide() == 0) {
                useMode = 1;
                if (pushFrames < 7) {
                    r4 = TRUE;
                    pushFrames += TICK_STEP_ENDS() ? 1 : 0;
                }
                if (((FtrContact *)(o))->getStepDistance() > 0x200) {
                    if (pushFrames >= 7) {
                        if (((CommManager *)(gCommManager))->isOnline() == 0) {
                            TalkRequest_AddPlayerTalk6(this, 0);
                        }
                    }
                }
            } else {
                if (Room_CountOccupants() <= 1) {
                    useMode = 2;
                }
            }
        }
    }
    if (r4 == 0) {
        pushFrames = 0;
    }
}

BOOL FtrBed::enterFtrAct01() {
    inLeftHalf = (position.x < (p21::data_020c8cbc >> 1)) ? 1 : 0;
    inFrontHalf = (position.z < 0x16000) ? 1 : 0;
    if (inLeftHalf) {
        if (inFrontHalf) {
            ownerPlayer = 0;
        } else {
            ownerPlayer = 2;
        }
    } else {
        if (inFrontHalf) {
            ownerPlayer = 1;
        } else {
            ownerPlayer = 3;
        }
    }
    return TRUE;
}

BOOL FtrBed::enterFtrAct00() {
    pushFrames = 0;
    return TRUE;
}

void FtrBed::execFtrAct00() {
    u16 v;
    BOOL r7 = FALSE;
    void *o = ((FtrContactSet *)(FtrContactSet_GetInstance()))->findContact(this);
    Actor *pl = (Actor *)PlayerActor_GetActor(4);
    if (o != 0) {
        if (pl != 0) {
            if (FtrMgr_IsFurnitureUsable() != 0) {
                if (((FtrContact *)(o))->getSide() == 2 || ((FtrContact *)(o))->getSide() == 0) {
                    FtrBedSideTiles q;
                    VecFx32 a, b, c, e, f;
                    getSideTiles(&q);
                    Unk_ov004_02210d58_P *p0 = q.get(0);
                    FieldPos_FromUnitCenter(&a, p0->x, p0->y);
                    Unk_ov004_02210d58_P *p1 = q.get(1);
                    FieldPos_FromUnitCenter(&b, p1->x, p1->y);
                    s32 *pv = &pl->position.x;
                    c.x = pl->position.x;
                    c.y = pv[1];
                    c.z = pv[2];
                    s32 d0 = Vec_DistXZ(&c, &a);
                    s32 d1 = Vec_DistXZ(&c, &b);
                    Unk_ov004_02210d58_P sel;
                    if (d0 < d1) {
                        Unk_ov004_02210d58_P *t = q.get(0);
                        sel.x = t->x;
                        sel.y = t->y;
                    } else {
                        Unk_ov004_02210d58_P *t = q.get(1);
                        sel.x = t->x;
                        sel.y = t->y;
                    }
                    if (FtrBed_IsTileFree(&sel)) {
                        e.x = 0;
                        e.y = 0;
                        e.z = 0x2000;
                        Vec_RotateY(&e, ((FtrContact *)(o))->getPushAngle());
                        s32 z = e.z + ((FtrContact *)(o))->getContactPoint()->z;
                        f.x = e.x + ((FtrContact *)(o))->getContactPoint()->x;
                        f.y = 0;
                        f.z = z;
                        if (FtrActor_IsPosClearOfCharacters(&f, 0x800, 0x2000, 0x800, 0)) {
                            if (pushFrames < 7) {
                                r7 = TRUE;
                                pushFrames += TICK_STEP_ENDS() ? 1 : 0;
                            }
                            if (((FtrContact *)(o))->getStepDistance() > 0x200) {
                                if (pushFrames >= 7) {
                                    v = ((FtrContact *)(o))->getPushAngle();
                                    Unk_ov004_0221076c_R *ra = (Unk_ov004_0221076c_R *)((FtrContact *)(o))->getContactPoint();
                                    Unk_ov004_0221076c_R *rb = (Unk_ov004_0221076c_R *)((FtrContact *)(o))->getContactPoint();
                                    PlayerActor_LocalRequestBedApproach(&ra->x, &rb->z, (s16 *)&v, (s16)(rotY - 0x4000), 0);
                                    pushFrames = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (r7 == 0) {
        pushFrames = 0;
    }
}

s32 FtrBed::checkStepTile(VecFx32 *a, s32 b, VecFx32 *c) {
    VecFx32 out;
    s32 x, y;
    calcStepPos(&out, a, b, c);
    FieldPos_ToUnit(&x, &y, &out);
    FtrActor *obj = ((FtrActorGrid *)(FtrActorGrid_GetInstance()))->getActor(x, y, 0);
    if (FtrActor_IsPosClearOfCharacters(&out, 0x800, 0x2000, 0x800, 0) == 0) {
        return 0;
    }
    if (obj != 0) {
        if (obj == this) {
            return 1;
        }
        if (FtrInfo_TestIndoorFlag2(FtrActor_GetFtrIndex(obj)) != 0) {
            return 2;
        }
        if (rotY == obj->rotY) {
            if (FtrBedKindCheck::R(obj->profile)) {
                FtrBedLieTiles q1, q2;
                u32 n1 = getLieTiles(&q1);
                u32 n2 = ((FtrBed *)obj)->getLieTiles(&q2);
                u32 i, j;
                for (i = 0; i < n1; i++) {
                    Unk_ov004_02210d58_P *p = q1.get(i);
                    s32 px = p->x;
                    s32 py = p->y;
                    for (j = 0; j < n2; j++) {
                        Unk_ov004_02210d58_P *q = q2.get(j);
                        s32 qy = q->y;
                        s32 qx = q->x;
                        qx = px - qx;
                        if (qx < 0) qx = -qx;
                        qy = py - qy;
                        if (qy < 0) qy = -qy;
                        if (qx + qy == 1) {
                            return 1;
                        }
                    }
                }
            }
        }
    } else {
        if (FtrMgr_GetSurfaceHeightAtPos(&out) == 0) {
            if (p21::Ground_GetExitAtPos(&out) == -1) {
                return 2;
            }
        }
    }
    return 0;
}

extern "C" BOOL FtrBed_IsTileFree(Unk_ov004_02210d58_P *p) {
    if (FtrMgr_GetSurfaceHeight(p->x, p->y) == 0) {
        if (p21::Ground_GetExitAt(p->x, p->y) == -1) {
            return TRUE;
        }
    }
    return FALSE;
}

typedef void (FtrBed::*Unk_ov004_02210ad4_Fn)();
typedef BOOL (FtrBed::*Unk_ov004_02210bec_Fn)();

void FtrBed::execFtrAct() {
    static Unk_ov004_02210ad4_Fn tbl[14] = {
        &FtrBed::execFtrAct00,
        &FtrBed::execFtrAct01,
        &FtrBed::execFtrAct02,
        &FtrBed::execFtrAct03,
        &FtrBed::execFtrAct04,
        &FtrBed::execFtrAct05,
        &FtrBed::execFtrAct06,
        &FtrBed::execFtrAct07,
        &FtrBed::execFtrAct08,
        &FtrBed::execFtrAct09,
        &FtrBed::execFtrAct0A,
        &FtrBed::execFtrAct0B,
        &FtrBed::execFtrAct0C,
        &FtrBed::execFtrAct0D,
    };
    if (ftrAct < 14) {
        (this->*tbl[ftrAct])();
    }
}

BOOL FtrBed::changeAct(u32 a, u8 v) {
    FtrActor::changeAct(a, v);
    static Unk_ov004_02210bec_Fn tbl[14] = {
        &FtrBed::enterFtrAct00,
        &FtrBed::enterFtrAct01,
        &FtrBed::enterFtrAct02,
        &FtrBed::enterFtrAct03,
        &FtrBed::enterFtrAct04,
        &FtrBed::enterFtrAct05,
        &FtrBed::enterFtrAct06,
        &FtrBed::enterFtrAct07,
        &FtrBed::enterFtrAct08,
        &FtrBed::enterFtrAct09,
        &FtrBed::enterFtrAct0A,
        &FtrBed::enterFtrAct0B,
        &FtrBed::enterFtrAct0C,
        &FtrBed::enterFtrAct0D,
    };
    if ((u32)a < 14) {
        if ((this->*tbl[a])()) {
            ftrAct = a;
            return TRUE;
        }
    }
    return FALSE;
}

void FtrBed::calcStepPos(VecFx32 *out, VecFx32 *in, s32 ang, VecFx32 *opt) {
    out->x = in->x;
    out->y = in->y;
    out->z = in->z;
    VecFx32CtorDtor t;
    t.x = 0;
    t.y = 0;
    t.z = 0;
    if (opt) {
        t.x = opt->x;
        t.y = opt->y;
        t.z = opt->z;
    }
    VecFx32CtorDtor w;
    w.x = t.x;
    w.y = t.y;
    w.z = t.z + 0x1000;
    Vec_RotateY(&w, ang);
    p21::VEC_Add(out, &w, out);
}

Unk_ov004_02210d58_P *FtrTilePair::get(u32 i) {
    return &v[i & 1];
}

FtrTilePair::FtrTilePair() {
}

FtrTilePair::~FtrTilePair() {
}

FtrBedLieTiles::FtrBedLieTiles() {
}

FtrBedLieTiles::~FtrBedLieTiles() {
}

FtrBedSideTiles::FtrBedSideTiles() {
}

FtrBedSideTiles::~FtrBedSideTiles() {
}




namespace p22 {
extern "C" {

BOOL PlayerActor_GetPosIfInBed(void *out, u32 i);
BOOL PlayerActor_GetPosIfSitting(void *out, u32 i);
BOOL Scene_InUnk6To8(void);
void VEC_Add(void *a, void *b, void *c);
}
}

class FtrSeat : public FtrActor {
public:
    FtrSeat();
    virtual ~FtrSeat();
    virtual BOOL onDelete();
    virtual BOOL initModel();
    virtual BOOL updateActive();

    void getSitterPos(VecFx32 *out, void *o);

    /* 0x840 */ u16 pushFrames;
    /* 0x842 */ u16 pad_842;
};


class FtrKind07 : public FtrActor {
public:
    FtrKind07();
    virtual ~FtrKind07();
    virtual BOOL onDelete();
    virtual BOOL changeAct(u32 a, u8 b);
    virtual u8 getActSwitchState(u32 a);
    virtual BOOL initModel();
    virtual BOOL updateActive();

    void execFtrAct03();
    BOOL enterFtrAct03();
    void execFtrAct02();
    BOOL enterFtrAct02();
    void execFtrAct01();
    BOOL enterFtrAct01();
    void execFtrAct00();
    BOOL enterFtrAct00();
    void execFtrAct();

    /* 0x840 */ u8 unk_840;
    /* 0x841 */ u8 ftrAct;
    /* 0x842 */ u8 pad_842[2];
};

typedef void (FtrKind07::*Unk_ov004_022116ac_Fn)();
typedef BOOL (FtrKind07::*Unk_ov004_02211738_Fn)();

u32 FtrBed::getLieTiles(void *o) {
    VecFx32 *p = sFtrBedLieOffsets[footprint].offsets;
    if (p) {
        u32 i;
        for (i = 0; i < sFtrBedLieOffsets[footprint].count; i++) {
            VecFx32 v;
            FtrActor_LocalToWorld(this, &v, &p[i]);
            s32 *q = (s32 *)((FtrTilePair *)o)->get(i);
            FieldPos_ToUnit(q, q + 1, &v);
        }
        return sFtrBedLieOffsets[footprint].count;
    }
    return 0;
}

u32 FtrBed::getSideTiles(void *o) {
    VecFx32 *p = data_ov004_02249028[footprint];
    if (p) {
        u32 i;
        for (i = 0; i < 2; i++) {
            VecFx32 v;
            FtrActor_LocalToWorld(this, &v, &p[i]);
            s32 *q = (s32 *)((FtrTilePair *)o)->get(i);
            FieldPos_ToUnit(q, q + 1, &v);
        }
        return 2;
    }
    return 0;
}

BOOL FtrBed::onDelete() {
    return TRUE;
}

BOOL FtrBed::onDraw() {
    return TRUE;
}

BOOL FtrBed::updateActive() {
    if (kind == 0x2a) {
        visNodes.setVisible(0);
        s32 z = 0;
        u32 i;
        u32 j;
        for (i = 0; i < 4; i++) {
            VecFx32 v;
            s32 x, y;
            if (p22::PlayerActor_GetPosIfInBed(&v, i)) {
                FieldPos_ToUnit(&x, &y, &v);
                FtrTileList list;
                ((FtrActor *)(this))->getTiles(&list, NULL, z);
                for (j = 0; j < list.getCount(); j++) {
                    if (x == list.get(j)->x && y == list.get(j)->y) {
                        visNodes.setVisible(1);
                        ((FtrGlowMatSet *)(&glowMats))->update();
                        FtrActor_StepAnims(this);
                        ((FtrActor *)(this))->playSound0();
                        break;
                    }
                }
                list.release();
            }
        }
    }
    execFtrAct();
    return TRUE;
}

BOOL FtrBed::initModel() {
    visNodes.setVisible(0);
    if (kind == 0x2a) {
        ((FtrActor *)(this))->initAnims(0, 0, 0x1000, 0);
        glowMats.init(model.resMdl, 1);
    }
    if (p22::Scene_InUnk6To8()) {
        changeAct(1, 0xff);
    }
    return TRUE;
}

BOOL FtrBed::acceptsInteraction(void *a) {
    if (!((CommManager *)(gCommManager))->isOnline() && isInUse() && useMode != 0) {
        return TRUE;
    }
    return FALSE;
}

BOOL FtrBed::isInUse() {
    if (ftrAct >= 1) {
        return TRUE;
    }
    return FALSE;
}

FtrBed::~FtrBed() {
}

FtrBed::FtrBed() : newBedItem(0xfff1) {
}

extern "C" void *FtrBed_Create() {
    return new FtrBed;
}

void FtrSeat::getSitterPos(VecFx32 *out, void *o) {
    if (footprint == 0) {
        out->x = position.x;
        out->y = position.y;
        out->z = position.z;
    } else {
        s32 *p = (s32 *)((FtrContact *)(o))->getClampedContactPoint();
        out->x = p[0];
        out->y = p[1];
        out->z = p[2];
        VecFx32 v;
        s32 t = ((FtrContact *)(o))->getDepth() + 0x1000;
        v.x = 0;
        v.y = 0;
        v.z = t;
        Vec_RotateY(&v, ((FtrContact *)(o))->getPushAngle());
        p22::VEC_Add(out, &v, out);
    }
}

BOOL FtrSeat::onDelete() {
    return TRUE;
}

BOOL FtrSeat::updateActive() {
    s32 x, y;
    if (kind == 0x2c) {
        visNodes.setVisible(0);
        s32 z = 0;
        u32 i;
        u32 j;
        for (i = 0; i < 4; i++) {
            VecFx32 v;
            if (p22::PlayerActor_GetPosIfSitting(&v, i)) {
                FieldPos_ToUnit(&x, &y, &v);
                FtrTileList list;
                ((FtrActor *)(this))->getTiles(&list, NULL, z);
                for (j = 0; j < list.getCount(); j++) {
                    if (x == list.get(j)->x && y == list.get(j)->y) {
                        visNodes.setVisible(1);
                        FtrActor_StepAnims(this);
                        ((FtrActor *)(this))->playSound0();
                        break;
                    }
                }
                list.release();
            }
        }
    } else if (kind == 9) {
        FtrActor_StepAnims(this);
        ((FtrActor *)(this))->playSound0();
    }
    BOOL hit = FALSE;
    void *r6 = ((FtrContactSet *)(FtrContactSet_GetInstance()))->findContact(this);
    if (r6 && FtrMgr_IsFurnitureUsable()) {
        BOOL ok = FALSE;
        u8 mode = 0;
        if (kind != 0x26) {
            if (((FtrContact *)(r6))->getSide() == 0) {
                ok = TRUE;
                mode = 0;
            }
        } else {
            s32 t = ((FtrContact *)(r6))->getSide();
            if (t == 0) {
                ok = TRUE;
                mode = 0;
            } else if (((FtrContact *)(r6))->getSide() == 3) {
                ok = TRUE;
                mode = 1;
            } else if (((FtrContact *)(r6))->getSide() == 1) {
                ok = TRUE;
                mode = 2;
            }
        }
        if (ok) {
            VecFx32 pos;
            getSitterPos(&pos, r6);
            if (FtrActor_IsPosClearOfCharacters(&pos, 0x800, 0x2000, 0x800, 0)) {
                if (pushFrames < 7) {
                    hit = TRUE;
                    pushFrames += TICK_STEP_ENDS() ? 1 : 0;
                }
                if (((FtrContact *)(r6))->getStepDistance() > 0x200) {
                    if (pushFrames >= 7) {
                        PlayerActor_LocalRequestSeatApproach(&pos.x, &pos.z, &rotY, &mode);
                        pushFrames = 0;
                    }
                }
            }
        }
    }
    if (!hit) {
        pushFrames = 0;
    }
    return TRUE;
}

BOOL FtrSeat::initModel() {
    visNodes.setVisible(0);
    if (kind == 9 || kind == 0x2c) {
        ((FtrActor *)(this))->initAnims(0, 0, 0x1000, 0);
    }
    return TRUE;
}

FtrSeat::~FtrSeat() {
}

FtrSeat::FtrSeat() {
}

extern "C" void *FtrSeat_Create() {
    return new FtrSeat;
}

void FtrKind07::execFtrAct03() {
    switchState.set(0, 0);
    if (FtrActor_StepAnims(this)) {
        changeAct(0, 0xff);
    }
}

BOOL FtrKind07::enterFtrAct03() {
    switchState.set(0, 0);
    ((FtrActor *)(this))->playSound2();
    FtrActor_PlayAnimsFromLastFrame(this, 0, 3, 0x1000);
    return TRUE;
}

void FtrKind07::execFtrAct02() {
    FtrActor_StepAnims(this);
    (this)->hasIndoorFlag6();
    ((FtrActor *)(this))->playSound0();
    if (switchState.isChanging()) {
        FtrSync_RequestAct(this, 3, 0xff, 1);
    } else if (((FtrActor *)(this))->isPreview()) {
        changeAct(3, 0xff);
    }
}

BOOL FtrKind07::enterFtrAct02() {
    switchState.set(1, 0);
    FtrActor_PlayAnimsFromLastFrame(this, 1, 0, 0x1000);
    return TRUE;
}

void FtrKind07::execFtrAct01() {
    switchState.set(1, 0);
    if (FtrActor_StepAnims(this)) {
        changeAct(2, 0xff);
    }
}

BOOL FtrKind07::enterFtrAct01() {
    switchState.set(1, 0);
    ((FtrActor *)(this))->playSound1();
    ((FtrActor *)(this))->playAnim(0, 1, 0x1000, 0);
    return TRUE;
}

void FtrKind07::execFtrAct00() {
    if (switchState.isChanging()) {
        FtrSync_RequestAct(this, 1, 0xff, 1);
    } else if (((FtrActor *)(this))->isPreview()) {
        changeAct(1, 0xff);
    }
}

BOOL FtrKind07::enterFtrAct00() {
    switchState.set(0, 0);
    ((FtrActor *)(this))->playAnim(0, 3, 0x1000, 0);
    return TRUE;
}

void FtrKind07::execFtrAct() {
    static Unk_ov004_022116ac_Fn tbl[4] = {
        &FtrKind07::execFtrAct00,
        &FtrKind07::execFtrAct01,
        &FtrKind07::execFtrAct02,
        &FtrKind07::execFtrAct03,
    };
    u32 i = ftrAct;
    if (i < 4) {
        (this->*tbl[i])();
    }
}

BOOL FtrKind07::changeAct(u32 a, u8 b) {
    FtrActor::changeAct(a, b);
    static Unk_ov004_02211738_Fn tbl[4] = {
        &FtrKind07::enterFtrAct00,
        &FtrKind07::enterFtrAct01,
        &FtrKind07::enterFtrAct02,
        &FtrKind07::enterFtrAct03,
    };
    if ((u32)a < 4) {
        if ((this->*tbl[a])()) {
            ftrAct = a;
            return TRUE;
        }
    }
    return FALSE;
}

u8 FtrKind07::getActSwitchState(u32 a) {
    if (a < 4) {
        return data_ov004_02240050[a];
    }
    return 0;
}

BOOL FtrKind07::onDelete() {
    return TRUE;
}

BOOL FtrKind07::updateActive() {
    execFtrAct();
    return TRUE;
}

BOOL FtrKind07::initModel() {
    unk_840 = 0;
    ((FtrActor *)(this))->initAnims(0, 1, 0x1000, 0);
    if (switchState.isOn() && !FtrMgr_IsShopScene()) {
        changeAct(2, 0xff);
    } else {
        changeAct(0, 0xff);
    }
    return TRUE;
}

namespace p23 {
extern "C" {
}
}

class FtrKind06 : public FtrActor {
public:
    FtrKind06();
    virtual ~FtrKind06();
    virtual BOOL onDelete();
    virtual BOOL changeAct(u32 a, u8 b);
    virtual u8 getActSwitchState(u32 a);
    virtual BOOL initModel();
    virtual BOOL updateActive();

    void execFtrAct03();
    BOOL enterFtrAct03();
    void execFtrAct02();
    BOOL enterFtrAct02();
    void execFtrAct01();
    BOOL enterFtrAct01();
    void execFtrAct00();
    BOOL enterFtrAct00();
    void execFtrAct();
    /* 0x840 */ u8 pad_840;
    /* 0x841 */ u8 ftrAct;
    /* 0x842 */ u8 pad_842[2];
};

class FtrKind05 : public FtrActor {
public:
    FtrKind05();
    virtual ~FtrKind05();
    virtual BOOL onDelete();
    virtual BOOL changeAct(u32 a, u8 b);
    virtual u8 getActSwitchState(u32 a);
    virtual BOOL initModel();
    virtual BOOL updateActive();

    void execFtrAct03();
    BOOL enterFtrAct03();
    void execFtrAct02();
    BOOL enterFtrAct02();
    void execFtrAct01();
    BOOL enterFtrAct01();
    void execFtrAct00();
    BOOL enterFtrAct00();
    void execFtrAct();
    /* 0x840 */ u8 ftrAct;
    /* 0x841 */ u8 pad_841[3];
};

class FtrKind04 : public FtrActor {
public:
    FtrKind04();
    virtual ~FtrKind04();
    virtual BOOL onDelete();
    virtual BOOL changeAct(u32 idx, u8 v);
    virtual u8 getActSwitchState(u32 idx);
    virtual BOOL initModel();
    virtual BOOL updateActive();

    void execFtrAct02();
    BOOL enterFtrAct02();
    void execFtrAct01();
    BOOL enterFtrAct01();
    void execFtrAct00();
    BOOL enterFtrAct00();
    void execFtrAct();

    /* 0x840 */ u8 ftrAct;
    /* 0x841 */ u8 pad_841[3];
    /* 0x844 */ s32 animSpeed;
    /* 0x848 */ FtrGlowMatSet glowMats;
};

namespace p23 {
extern "C" {
}
}

typedef void (FtrKind06::*Unk_ov004_02211af4_Fn)();
typedef BOOL (FtrKind06::*Unk_ov004_02211b80_Fn)();
typedef void (FtrKind05::*Unk_ov004_02211ed8_Fn)();
typedef BOOL (FtrKind05::*Unk_ov004_02211f64_Fn)();

FtrKind07::~FtrKind07() {
}

FtrKind07::FtrKind07() {
}

extern "C" void *FtrKind07_Create() {
    return new FtrKind07;
}

void FtrKind06::execFtrAct03() {
    visNodes.setVisible(1);
    playSound0();
    switchState.set(0, 0);
    if (FtrActor_StepAnims(this)) {
        changeAct(0, 0xff);
    }
}

BOOL FtrKind06::enterFtrAct03() {
    switchState.set(0, 0);
    visNodes.setVisible(1);
    playAnim(1, 1, 0x1000, 0);
    playSound2();
    return TRUE;
}

void FtrKind06::execFtrAct02() {
    playSound0();
    if (switchState.isChanging()) {
        FtrSync_RequestAct(this, 3, 0xff, 1);
    } else if (isPreview()) {
        changeAct(3, 0xff);
    }
}

BOOL FtrKind06::enterFtrAct02() {
    switchState.set(1, 0);
    FtrActor_PlayAnimsFromLastFrame(this, 0, 1, 0x1000);
    visNodes.setVisible(1);
    return TRUE;
}

void FtrKind06::execFtrAct01() {
    switchState.set(1, 0);
    playSound0();
    if (FtrActor_StepAnims(this)) {
        changeAct(2, 0xff);
    }
}

BOOL FtrKind06::enterFtrAct01() {
    switchState.set(1, 0);
    visNodes.setVisible(1);
    playAnim(0, 1, 0x1000, 0);
    playSound1();
    return TRUE;
}

void FtrKind06::execFtrAct00() {
    if (switchState.isChanging()) {
        FtrSync_RequestAct(this, 1, 0xff, 1);
    } else if (isPreview()) {
        changeAct(1, 0xff);
    }
}

BOOL FtrKind06::enterFtrAct00() {
    switchState.set(0, 0);
    FtrActor_PlayAnimsFromLastFrame(this, 1, 1, 0x1000);
    visNodes.setVisible(0);
    return TRUE;
}

void FtrKind06::execFtrAct() {
    static Unk_ov004_02211af4_Fn tbl[4] = {
        &FtrKind06::execFtrAct00,
        &FtrKind06::execFtrAct01,
        &FtrKind06::execFtrAct02,
        &FtrKind06::execFtrAct03,
    };
    if (ftrAct < 4) {
        (this->*tbl[ftrAct])();
    }
}

BOOL FtrKind06::changeAct(u32 a, u8 b) {
    FtrActor::changeAct(a, b);
    static Unk_ov004_02211b80_Fn tbl[4] = {
        &FtrKind06::enterFtrAct00,
        &FtrKind06::enterFtrAct01,
        &FtrKind06::enterFtrAct02,
        &FtrKind06::enterFtrAct03,
    };
    if ((u32)a < 4) {
        if ((this->*tbl[a])()) {
            ftrAct = a;
            return TRUE;
        }
    }
    return FALSE;
}

u8 FtrKind06::getActSwitchState(u32 a) {
    if (a < 4) {
        return data_ov004_02240060[a];
    }
    return 0;
}

BOOL FtrKind06::onDelete() {
    return TRUE;
}

BOOL FtrKind06::updateActive() {
    execFtrAct();
    return TRUE;
}

BOOL FtrKind06::initModel() {
    initAnims(0, 1, 0x1000, 0);
    if (!switchState.isOn() || FtrMgr_IsShopScene()) {
        changeAct(0, 0xff);
    } else {
        changeAct(2, 0xff);
    }
    return TRUE;
}

FtrKind06::~FtrKind06() {
}

FtrKind06::FtrKind06() {
}

extern "C" void *FtrKind06_Create() {
    return new FtrKind06;
}

void FtrKind05::execFtrAct03() {
    switchState.set(0, 0);
    if (FtrActor_StepAnims(this)) {
        changeAct(0, 0xff);
    }
}

BOOL FtrKind05::enterFtrAct03() {
    switchState.set(0, 0);
    FtrActor_PlayAnimsFromLastFrame(this, 0, 3, 0x1000);
    playSound2();
    return TRUE;
}

void FtrKind05::execFtrAct02() {
    if (switchState.isChanging()) {
        FtrSync_RequestAct(this, 3, 0xff, 1);
    } else if (isPreview()) {
        changeAct(3, 0xff);
    }
}

BOOL FtrKind05::enterFtrAct02() {
    switchState.set(1, 0);
    FtrActor_PlayAnimsFromLastFrame(this, 0, 1, 0x1000);
    return TRUE;
}

void FtrKind05::execFtrAct01() {
    switchState.set(1, 0);
    if (FtrActor_StepAnims(this)) {
        changeAct(2, 0xff);
    }
}

BOOL FtrKind05::enterFtrAct01() {
    switchState.set(1, 0);
    playAnim(0, 1, 0x1000, 0);
    playSound1();
    return TRUE;
}

void FtrKind05::execFtrAct00() {
    if (switchState.isChanging()) {
        FtrSync_RequestAct(this, 1, 0xff, 1);
    } else if (isPreview()) {
        changeAct(1, 0xff);
    }
}

BOOL FtrKind05::enterFtrAct00() {
    switchState.set(0, 0);
    playAnim(0, 3, 0x1000, 0);
    return TRUE;
}

void FtrKind05::execFtrAct() {
    static Unk_ov004_02211ed8_Fn tbl[4] = {
        &FtrKind05::execFtrAct00,
        &FtrKind05::execFtrAct01,
        &FtrKind05::execFtrAct02,
        &FtrKind05::execFtrAct03,
    };
    if (ftrAct < 4) {
        (this->*tbl[ftrAct])();
    }
}

BOOL FtrKind05::changeAct(u32 a, u8 b) {
    FtrActor::changeAct(a, b);
    static Unk_ov004_02211f64_Fn tbl[4] = {
        &FtrKind05::enterFtrAct00,
        &FtrKind05::enterFtrAct01,
        &FtrKind05::enterFtrAct02,
        &FtrKind05::enterFtrAct03,
    };
    if ((u32)a < 4) {
        if ((this->*tbl[a])()) {
            ftrAct = a;
            return TRUE;
        }
    }
    return FALSE;
}

u8 FtrKind05::getActSwitchState(u32 a) {
    if (a < 4) {
        return data_ov004_02240054[a];
    }
    return 0;
}

BOOL FtrKind05::onDelete() {
    return TRUE;
}

BOOL FtrKind05::updateActive() {
    execFtrAct();
    return TRUE;
}

BOOL FtrKind05::initModel() {
    initAnims(0, 1, 0x1000, 0);
    if (switchState.isOn() && !FtrMgr_IsShopScene()) {
        changeAct(2, 0xff);
    } else {
        changeAct(0, 0xff);
    }
    return TRUE;
}

FtrKind05::~FtrKind05() {
}

FtrKind05::FtrKind05() {
}

extern "C" void *FtrKind05_Create() {
    return new FtrKind05;
}

void FtrKind04::execFtrAct02() {
    Math_StepS32(&animSpeed, 0, 0xcc);
    if (animSpeed == 0) {
        changeAct(0, 0xff);
    }
}

BOOL FtrKind04::enterFtrAct02() {
    switchState.set(0, 0);
    playSound2();
    ((FtrGlowMatSet *)(&glowMats))->setLit(1, 1, 0);
    return TRUE;
}

namespace p24 {
extern "C" {
}
}



namespace p24 {
extern "C" {
}
}

class FtrKind02 : public FtrActor {
public:
    FtrKind02();
    virtual ~FtrKind02();
    virtual BOOL onDelete();
    virtual BOOL changeAct(u32 idx, u8 v);
    virtual BOOL initModel();
    virtual BOOL updateActive();

    void execFtrAct01();
    BOOL enterFtrAct01();
    void execFtrAct00();
    BOOL enterFtrAct00();
    void execFtrAct();

    /* 0x840 */ u8 ftrAct;
};

class FtrKind03 : public FtrActor {
public:
    FtrKind03();
    virtual ~FtrKind03();
    virtual BOOL onDelete();
    virtual BOOL changeAct(u32 idx, u8 v);
    virtual u8 getActSwitchState(u32 idx);
    virtual BOOL initModel();
    virtual BOOL updateActive();

    void execFtrAct01();
    BOOL enterFtrAct01();
    void execFtrAct00();
    BOOL enterFtrAct00();
    void execFtrAct();

    /* 0x840 */ u8 ftrAct;
    /* 0x841 */ u8 pad_841[3];
    /* 0x844 */ FtrGlowMatSet glowMats;
};


void FtrKind04::execFtrAct01() {
    hasIndoorFlag6();
    playSound0();
    if (switchState.isChanging()) {
        FtrSync_RequestAct(this, 2, 0xff, 1);
    }
}

BOOL FtrKind04::enterFtrAct01() {
    animSpeed = 0x1000;
    switchState.set(1, 0);
    playSound1();
    glowMats.setLit(1, 1, 0);
    return TRUE;
}

void FtrKind04::execFtrAct00() {
    if (switchState.isChanging()) {
        FtrSync_RequestAct(this, 1, 0xff, 1);
    }
}

BOOL FtrKind04::enterFtrAct00() {
    animSpeed = 0;
    switchState.set(0, 0);
    glowMats.setLit(0, 1, 0);
    return TRUE;
}

void FtrKind04::execFtrAct() {
    static void (FtrKind04::*tbl[3])() = {
        &FtrKind04::execFtrAct00,
        &FtrKind04::execFtrAct01,
        &FtrKind04::execFtrAct02,
    };
    u32 i = ftrAct;
    if (i < 3) {
        (this->*tbl[i])();
    }
}

BOOL FtrKind04::changeAct(u32 idx, u8 v) {
    FtrActor::changeAct(idx, v);
    static BOOL (FtrKind04::*tbl[3])() = {
        &FtrKind04::enterFtrAct00,
        &FtrKind04::enterFtrAct01,
        &FtrKind04::enterFtrAct02,
    };
    if (idx < 3) {
        if ((this->*tbl[idx])()) {
            ftrAct = idx;
            return TRUE;
        }
    }
    return FALSE;
}

u8 FtrKind04::getActSwitchState(u32 idx) {
    if (idx < 3) {
        return data_ov004_02240044[idx];
    }
    return 0;
}

BOOL FtrKind04::onDelete() {
    return TRUE;
}

BOOL FtrKind04::updateActive() {
    u32 i;
    glowMats.update();
    execFtrAct();
    model.frameStep = animSpeed;
    for (i = 0; i < 4; i++) {
        if (anims[i].getAnmObj()) {
            anims[i].frameStep = animSpeed;
        }
    }
    FtrActor_StepAnims(this);
    return TRUE;
}

BOOL FtrKind04::initModel() {
    initAnims(0, 0, 0x1000, 0);
    void *res = model.resMdl;
    u8 t = switchState.isOn();
    glowMats.init(res, t);
    if (switchState.isOn() != 0 && FtrMgr_IsShopScene() == 0) {
        changeAct(1, 0xff);
    } else {
        changeAct(0, 0xff);
    }
    return TRUE;
}

FtrKind04::~FtrKind04() {
}

FtrKind04::FtrKind04() {
}

extern "C" FtrActor *FtrKind04_Create() {
    return new FtrKind04;
}

void FtrKind03::execFtrAct01() {
    FtrActor_StepAnims(this);
    hasIndoorFlag6();
    playSound0();
    if (switchState.isChanging()) {
        FtrSync_RequestAct(this, 0, 0xff, 1);
    }
}

BOOL FtrKind03::enterFtrAct01() {
    switchState.set(1, 0);
    playSound1();
    glowMats.setLit(1, 1, 0);
    return TRUE;
}

void FtrKind03::execFtrAct00() {
    if (switchState.isChanging()) {
        FtrSync_RequestAct(this, 1, 0xff, 1);
    }
}

BOOL FtrKind03::enterFtrAct00() {
    switchState.set(0, 0);
    playSound2();
    glowMats.setLit(0, 1, 0);
    return TRUE;
}

void FtrKind03::execFtrAct() {
    static void (FtrKind03::*tbl[2])() = {
        &FtrKind03::execFtrAct00,
        &FtrKind03::execFtrAct01,
    };
    u32 i = ftrAct;
    if (i < 2) {
        (this->*tbl[i])();
    }
}

BOOL FtrKind03::changeAct(u32 idx, u8 v) {
    FtrActor::changeAct(idx, v);
    static BOOL (FtrKind03::*tbl[2])() = {
        &FtrKind03::enterFtrAct00,
        &FtrKind03::enterFtrAct01,
    };
    if (idx < 2) {
        if ((this->*tbl[idx])()) {
            ftrAct = idx;
            return TRUE;
        }
    }
    return FALSE;
}

u8 FtrKind03::getActSwitchState(u32 idx) {
    if (idx < 2) {
        return data_ov004_02240030[idx];
    }
    return 0;
}

BOOL FtrKind03::onDelete() {
    return TRUE;
}

BOOL FtrKind03::updateActive() {
    glowMats.update();
    execFtrAct();
    return TRUE;
}

BOOL FtrKind03::initModel() {
    initAnims(0, 0, 0x1000, 0);
    void *res = model.resMdl;
    u8 t = switchState.isOn();
    glowMats.init(res, t);
    if (switchState.isOn() == 0 || FtrMgr_IsShopScene() != 0) {
        changeAct(0, 0xff);
    } else {
        changeAct(1, 0xff);
    }
    return TRUE;
}

FtrKind03::~FtrKind03() {
}

FtrKind03::FtrKind03() {
}

extern "C" FtrActor *FtrKind03_Create() {
    return new FtrKind03;
}

void FtrKind02::execFtrAct01() {
    u32 t = FtrActor_GetFtrIndex(this);
    if (t != 0xb9 && t != 0xba) goto rest;
    if (switchState.isChanging()) {
        FtrSync_RequestAct(this, 1, 0xff, 1);
        goto end;
    }
rest:
    switchState.toggle(0);
    if (FtrActor_StepAnims(this)) {
        FtrSync_RequestAct(this, 0, 0xff, 1);
    } else {
        playSound0();
    }
    if (FtrActor_GetFtrIndex(this) == 0x207) {
        if (model.hasPassedFrame(0x30)) {
            playSound2();
        }
    }
end:;
}

BOOL FtrKind02::enterFtrAct01() {
    playAnim(0, 1, 0x1000, 0);
    playSound1();
    return TRUE;
}

void FtrKind02::execFtrAct00() {
    if (switchState.isChanging()) {
        FtrSync_RequestAct(this, 1, 0xff, 1);
    }
}

BOOL FtrKind02::enterFtrAct00() {
    FtrActor_PlayAnimsFromLastFrame(this, 0, 1, 0x1000);
    if (FtrActor_GetFtrIndex(this) != 0x207) {
        playSound2();
    }
    return TRUE;
}

BOOL (FtrKind02::*FtrKind02_execFtrAct_tbl[2])();
u8 FtrKind02_execFtrAct_tbl_init;
void FtrKind02::execFtrAct() {
    if (!FtrKind02_execFtrAct_tbl_init) {
        HOST_STATIC_INIT_ARRAY(FtrKind02_execFtrAct_tbl, {
        (BOOL (FtrKind02::*)())&FtrKind02::execFtrAct00,
        (BOOL (FtrKind02::*)())&FtrKind02::execFtrAct01,
    });
        FtrKind02_execFtrAct_tbl_init = 1;
    }
    u32 i = ftrAct;
    if (i < 2) {
        (this->*FtrKind02_execFtrAct_tbl[i])();
    }
}

BOOL FtrKind02::changeAct(u32 idx, u8 v) {
    FtrActor::changeAct(idx, v);
    static BOOL (FtrKind02::*tbl[2])() = {
        &FtrKind02::enterFtrAct00,
        &FtrKind02::enterFtrAct01,
    };
    if (idx < 2) {
        if ((this->*tbl[idx])()) {
            ftrAct = idx;
            return TRUE;
        }
    }
    return FALSE;
}

BOOL FtrKind02::onDelete() {
    switchState.set(0, 0);
    return TRUE;
}

BOOL FtrKind02::updateActive() {
    execFtrAct();
    return TRUE;
}

BOOL FtrKind02::initModel() {
    switchState.set(0, 0);
    initAnims(0, 1, 0x1000, 0);
    FtrActor_PlayAnimsFromLastFrame(this, 0, 1, 0x1000);
    changeAct(0, 0xff);
    return TRUE;
}

namespace p25 {
extern "C" {
}
}

class FtrBasic : public FtrActor {
public:
    FtrBasic();
    virtual ~FtrBasic();
    virtual BOOL onDelete();
    virtual BOOL changeAct(u32 a, u8 b);
    virtual u8 getActSwitchState(u32 a);
    virtual BOOL initModel();
    virtual BOOL updateActive();

    void execFtrAct01();
    BOOL enterFtrAct01();
    void execFtrAct00();
    BOOL enterFtrAct00();
    void execFtrAct();

    /* 0x840 */ u8 ftrAct;
    /* 0x841 */ u8 pad_841[3];
    /* 0x844 */ FtrGlowMatSet glowMats;
};


namespace p25 {
extern "C" {
}
}

typedef void (FtrBasic::*Unk_ov004_02212b98_Fn)();
typedef BOOL (FtrBasic::*Unk_ov004_02212c04_Fn)();

FtrKind02::~FtrKind02() {
}

FtrKind02::FtrKind02() {
}

extern "C" void *FtrKind02_Create() {
    return new FtrKind02;
}

void FtrBasic::execFtrAct01() {
    execFtrAct00();
}

BOOL FtrBasic::enterFtrAct01() {
    switchState.set(1, 0);
    playSound1();
    return TRUE;
}

void FtrBasic::execFtrAct00() {
    if (switchState.isChanging()) {
        FtrSync_RequestAct(this, (ftrAct + 1) & 1, 0xff, 1);
    }
}

BOOL FtrBasic::enterFtrAct00() {
    switchState.set(0, 0);
    playSound2();
    return TRUE;
}

void FtrBasic::execFtrAct() {
    static Unk_ov004_02212b98_Fn tbl[2] = {
        &FtrBasic::execFtrAct00,
        &FtrBasic::execFtrAct01,
    };
    if (ftrAct < 2) {
        (this->*tbl[ftrAct])();
    }
}

BOOL FtrBasic::changeAct(u32 a, u8 b) {
    FtrActor::changeAct(a, b);
    static Unk_ov004_02212c04_Fn tbl[2] = {
        &FtrBasic::enterFtrAct00,
        &FtrBasic::enterFtrAct01,
    };
    if ((u32)a < 2) {
        if ((this->*tbl[a])()) {
            ftrAct = a;
            return TRUE;
        }
    }
    return FALSE;
}

u8 FtrBasic::getActSwitchState(u32 a) {
    if (a < 2) {
        return data_ov004_02240034[a];
    }
    return 0;
}

BOOL FtrBasic::onDelete() {
    return TRUE;
}

BOOL FtrBasic::updateActive() {
    if (kind == 1) {
        FtrActor_StepAnims(this);
    }
    glowMats.update();
    glowMats.setLit(1, 0, 0);
    hasIndoorFlag6();
    execFtrAct();
    switch (FtrActor_GetFtrIndex(this)) {
    case 0x123:
        if (!isPreview()) {
            soundEmitter.playOnce(0x429, &centerPos);
            if (model.hasPassedFrame(0x43)) {
                soundEmitter.setPitch(1);
            }
        }
        break;
    case 0x1fb:
        if (!isPreview()) {
            soundEmitter.playOnce(0x42b, &centerPos);
            if (model.hasPassedFrame(4)) {
                soundEmitter.setPitch(1);
            } else if (model.hasPassedFrame(0x16)) {
                soundEmitter.setPitch(2);
            }
        }
        break;
    case 0x1fc:
        if (!isPreview()) {
            soundEmitter.playOnce(0x42c, &centerPos);
            if (model.hasPassedFrame(5) || model.hasPassedFrame(0x12)) {
                soundEmitter.setPitch(1);
            }
        }
        break;
    default:
        playSound0();
        break;
    }
    return TRUE;
}

BOOL FtrBasic::initModel() {
    if (kind == 1) {
        s32 k = getAnimFrameCount(0);
        u32 t = (spawnMode == 1) ? 0 : Random_GlobalBelow(k);
        initAnims(0, 0, 0x1000, (u16)t);
        glowMats.init(model.resMdl, 1);
    }
    if (switchState.isOn()) {
        changeAct(1, 0xff);
    } else {
        changeAct(0, 0xff);
    }
    return TRUE;
}

FtrBasic::~FtrBasic() {
}

FtrBasic::FtrBasic() {
}

extern "C" void *FtrBasic_Create() {
    return new FtrBasic;
}


void FtrGyroid::execFtrAct02() {
    s32 v = updateSync((VecFx32 *)&position.x);
    if (v >= 0) {
        s32 i = v >> 12;
        model.initAnim(((FtrAnimSet *)(modelRes.getAnimSet()))->getBca(0), 0, v - (i << 12), (u16)i, 0);
        model.stepBlend();
    }
    if (switchState.isChanging()) {
        switchState.set(1, 0);
        u32 r4 = Scene_GetCurrent();
        FtrSync_RequestToggleGyroid(r4, &position, FtrActor_GetLayer(this));
    }
}

void FtrCart::onMoveStart(BOOL isPush) {
    void *p = ((FtrContactSet *)(FtrContactSet_GetInstance()))->findContact(this);
    BOOL c = FALSE;
    if (p != 0) {
        NNSG3dResAnmCommon *rec = ((FtrAnimSet *)(this->modelRes.getAnimSet()))->getBca(c);
        if (this->kind == 0x16) {
            if (((FtrContact *)(p))->getSide() == 2) {
                if (isPush) {
                    if (((FtrActor *)(this))->playSound1() != 0) c = TRUE;
                    ((FtrActor *)(this))->playAnim(0, 1, 0x1000, 0);
                } else {
                    if (((FtrActor *)(this))->playSound1() != 0) c = TRUE;
                    ((FtrActor *)(this))->playAnim(0, 3, 0x1000, rec->numFrame - 1);
                }
            } else if (((FtrContact *)(p))->getSide() == 0) {
                if (isPush) {
                    if (((FtrActor *)(this))->playSound1() != 0) c = TRUE;
                    ((FtrActor *)(this))->playAnim(0, 3, 0x1000, rec->numFrame - 1);
                } else {
                    if (((FtrActor *)(this))->playSound1() != 0) c = TRUE;
                    ((FtrActor *)(this))->playAnim(0, 1, 0x1000, 0);
                }
            }
        } else {
            if (((FtrContact *)(p))->getSide() == 3) {
                if (isPush) {
                    if (((FtrActor *)(this))->playSound1() != 0) c = TRUE;
                    ((FtrActor *)(this))->playAnim(0, 1, 0x1000, 0);
                } else {
                    if (((FtrActor *)(this))->playSound1() != 0) c = TRUE;
                    ((FtrActor *)(this))->playAnim(0, 3, 0x1000, rec->numFrame - 1);
                }
            } else if (((FtrContact *)(p))->getSide() == 1) {
                if (isPush) {
                    if (((FtrActor *)(this))->playSound1() != 0) c = TRUE;
                    ((FtrActor *)(this))->playAnim(0, 3, 0x1000, rec->numFrame - 1);
                } else {
                    if (((FtrActor *)(this))->playSound1() != 0) c = TRUE;
                    ((FtrActor *)(this))->playAnim(0, 1, 0x1000, 0);
                }
            }
        }
    }
    if (c == 0) {
        s32 se = FtrActor_GetDragSe();
        if (se != 0xffff) {
            PlayerActor_PlayLocalSe(se);
        }
    }
}

void FtrStereo::execFtrAct01() {
    FtrActor_StepAnims(this);
    playSound0();
    glowMats.setLit(1, 1, 0);
    soundEmitter.setPan(&centerPos);
    if (switchState.isChanging()) {
        switchState.set(1, 0);
        TalkRequest_AddPlayerTalk6(this, 0);
        PlayerActor_KeepAnimForNextAction();
    }
}

void FtrClock::onJointCalcPost(s32 a, void *b) {
    FtrActor::onJointCalcPost(a, b);
}

void FtrStorage::execTalkAct0B() {
    u32 f = ftrAct;
    if (f == 0) {
        ((Character *)(this))->detachTalkRequest(this);
        TalkRequest_SetTargetDone(this);
    }
}

BOOL FtrStorage::enterTalkAct0B() {
    s32 v = getStorageType();
    if (v != -1) {
        if (PlayerActor_LocalRequestStorageClose(&v)) {
            return FtrSync_ChangeAct(this, 3, 0xff, 1);
        }
        return FALSE;
    }
    return FtrSync_ChangeAct(this, 3, 0xff, 1);
}

void FtrStorage::execTalkAct0A() {
    if (window && window->state == 0) {
        setTalkAct(11);
    }
}

BOOL FtrStorage::enterTalkAct0A() {
    return TRUE;
}

void FtrStorage::execTalkAct09() {
    if (window && window->state != 0) {
        setTalkAct(10);
    }
}

BOOL FtrStorage::enterTalkAct09() {
    s32 y, x;
    ((Character *)(this))->attachTalkRequest(this);
    window->nextState = 1;
    static_cast<MsgRequest &>(*this).setFileName((const char *)data_ov004_0224bbc0);
    u32 t = FtrActor_GetFtrIndex(this);
    u32 r5 = t + Scene_GetCurrent();
    r5 &= 0xf;
    struct {
        u32 pad;
        FtrTileList list;
    } l;
    FtrTileList &list = l.list;
    ((FtrActor *)(this))->getTiles(&list, NULL, 0);
    BlockMap *grid = p19::gSceneBlockMap;
    if (grid != NULL) {
        u32 i;
        for (i = 0; i < list.getCount(); i++) {
            x = list.get(i)->x;
            y = list.get(i)->y;
            s32 hx = x >> 4;
            s32 hy = y >> 4;
            u16 *cell = BlockMap_GetItemPtr(grid, hx, hy, x - (hx << 4), y - (hy << 4), 0);
            if (cell != NULL && Item_IsFurniture(cell)) {
                r5 = (r5 + (x + (y << 4))) & 0xf;
                break;
            }
        }
    }
    msgIndex = r5;
    list.release();
    return TRUE;
}

void FtrStorage::execTalkAct08() {
    if (ftrAct == 2) {
        setTalkAct(9);
    }
}

BOOL FtrStorage::enterTalkAct08() {
    return FtrSync_ChangeAct(this, 1, 0xff, 1);
}

void FtrStorage::execTalkAct07() {
    s32 v = getStorageType();
    if (v == -1) {
        setTalkAct(8);
    } else if (PlayerActor_TestLocalFlag02()) {
        setTalkAct(8);
    }
}

BOOL FtrStorage::enterTalkAct07() {
    void *r4 = ((FtrContactSet *)(FtrContactSet_GetInstance()))->findContact(this);
    s32 v = getStorageType();
    if (v != -1) {
        s16 h = ((FtrContact *)(r4))->getPushAngle();
        VecFx32 *a = (VecFx32 *)((FtrContact *)(r4))->getClampedContactPoint();
        PlayerActor_LocalRequestStorageOpen(&v, &a->x, &((VecFx32 *)((FtrContact *)(r4))->getClampedContactPoint())->z, &h);
        return TRUE;
    }
    return TRUE;
}

BOOL FtrStorage::execTalkAct06() {
    return setTalkAct(7);
}

BOOL FtrStorage::enterTalkAct06() {
    return TRUE;
}

void FtrStorage::execTalkAct05() {
    if (ftrAct == 0) {
        TalkRequest_SetTargetDone(this);
    }
}

BOOL FtrStorage::enterTalkAct05() {
    s32 v = getStorageType();
    if (v != -1) {
        if (PlayerActor_LocalRequestStorageClose(&v)) {
            return FtrSync_ChangeAct(this, 3, 0xff, 1);
        }
        return FALSE;
    }
    return FtrSync_ChangeAct(this, 3, 0xff, 1);
}

void FtrStorage::execTalkAct04() {
    if (MenuCtrl_IsFinished()) {
        setTalkAct(5);
    }
}

BOOL FtrStorage::enterTalkAct04() {
    if (MenuCtrl_OpenLauncher(0x22)) {
        return TRUE;
    }
    return FALSE;
}

void FtrStorage::execTalkAct03() {
    if (ftrAct == 2) {
        setTalkAct(4);
    }
}

BOOL FtrStorage::enterTalkAct03() {
    return FtrSync_ChangeAct(this, 1, 0xff, 1);
}

void FtrStorage::execTalkAct02() {
    s32 v = getStorageType();
    if (v == -1) {
        setTalkAct(3);
    } else if (PlayerActor_TestLocalFlag02()) {
        setTalkAct(3);
    }
}

BOOL FtrStorage::enterTalkAct02() {
    void *r4 = ((FtrContactSet *)(FtrContactSet_GetInstance()))->findContact(this);
    s32 v = getStorageType();
    if (v != -1) {
        s16 h = ((FtrContact *)(r4))->getPushAngle();
        VecFx32 *a = (VecFx32 *)((FtrContact *)(r4))->getClampedContactPoint();
        if (PlayerActor_LocalRequestStorageOpen(&v, &a->x, &((VecFx32 *)((FtrContact *)(r4))->getClampedContactPoint())->z, &h)) {
            return TRUE;
        }
        return FALSE;
    }
    return TRUE;
}

BOOL FtrStorage::execTalkAct01() {
    return setTalkAct(2);
}

BOOL FtrStorage::enterTalkAct01() {
    return TRUE;
}

void FtrStorage::execTalkAct00() {
}

BOOL FtrStorage::enterTalkAct00() {
    return TRUE;
}

typedef BOOL (FtrStorage::*FtrStorage_execTalkAct_Fn)();
FtrStorage_execTalkAct_Fn FtrStorage_execTalkAct_tbl[12];
u8 FtrStorage_execTalkAct_tbl_init;
void FtrStorage::execTalkAct() {
    typedef BOOL (FtrStorage::*Fn)();
    if (!FtrStorage_execTalkAct_tbl_init) {
        HOST_STATIC_INIT_ARRAY(FtrStorage_execTalkAct_tbl, {
        (Fn)&FtrStorage::execTalkAct00,
        &FtrStorage::execTalkAct01,
        (Fn)&FtrStorage::execTalkAct02,
        (Fn)&FtrStorage::execTalkAct03,
        (Fn)&FtrStorage::execTalkAct04,
        (Fn)&FtrStorage::execTalkAct05,
        &FtrStorage::execTalkAct06,
        (Fn)&FtrStorage::execTalkAct07,
        (Fn)&FtrStorage::execTalkAct08,
        (Fn)&FtrStorage::execTalkAct09,
        (Fn)&FtrStorage::execTalkAct0A,
        (Fn)&FtrStorage::execTalkAct0B,
    });
        FtrStorage_execTalkAct_tbl_init = 1;
    }
    s32 s = talkAct;
    if (s < 12) {
        (this->*FtrStorage_execTalkAct_tbl[s])();
    }
}

BOOL FtrStorage::setTalkAct(s32 s) {
    typedef BOOL (FtrStorage::*Fn)();
    static Fn tbl[12] = {
        &FtrStorage::enterTalkAct00,
        &FtrStorage::enterTalkAct01,
        &FtrStorage::enterTalkAct02,
        &FtrStorage::enterTalkAct03,
        &FtrStorage::enterTalkAct04,
        &FtrStorage::enterTalkAct05,
        &FtrStorage::enterTalkAct06,
        &FtrStorage::enterTalkAct07,
        &FtrStorage::enterTalkAct08,
        &FtrStorage::enterTalkAct09,
        &FtrStorage::enterTalkAct0A,
        &FtrStorage::enterTalkAct0B,
    };
    if (s < 12) {
        if ((this->*tbl[s])()) {
            talkAct = s;
            return TRUE;
        }
    }
    return FALSE;
}

void FtrBed::onChoice(u32) {
    u32 r = ((ChoiceList *)(window->getChoiceList()))->getResult();
    if (useMode == 1) {
        switch (r) {
        case 0:
            window->setNextMessage(p20::gTalkMsgIndexEnd, 0);
            changeAct(6, 0xff);
            break;
        case 1:
            changeAct(5, 0xff);
            break;
        }
    } else {
        switch (r) {
        case 0:
            window->setNextMessage(p20::gTalkMsgIndexEnd, 0);
            changeAct(0xa, 0xff);
            break;
        case 1:
            window->setNextMessage(p20::gTalkMsgIndexEnd, 0);
            changeAct(9, 0xff);
            break;
        }
    }
}

void FtrBed::onMessageEnd(u32) {
    if (msgIndex == 0) {
        TalkWindowState *o = window;
        ChoiceList *h = o->getChoiceList();
        ((ChoiceList *)(h))->reset(2, 1);
        u8 buf[4];
        buf[0] = 0xc;
        buf[1] = p20::gTalkMsgIndexEnd[0];
        ((ChoiceList *)(h))->setEntry(0, (const u8 *)(&buf[0]), 1, (const u8 *)(&buf[1]), (const char *)(0), 2);
        buf[2] = 0xd;
        buf[3] = p20::gTalkMsgIndexEnd[0];
        ((ChoiceList *)(h))->setEntry(1, (const u8 *)(&buf[2]), 1, (const u8 *)(&buf[3]), (const char *)(0), 0);
        ((ChoiceList *)(h))->loadTexts();
        ((TalkWindowState *)(o))->openChoices(1);
    }
    if (msgIndex == 0x19) {
        changeAct(5, 0xff);
    }
}

void FtrBed::onInteractionEvent(u32 a, u8 b) {
    switch (a) {
    case 0:
    case 1:
        if (useMode == 1) {
            changeAct(2, 0xff);
        } else {
            changeAct(7, 0xff);
        }
        break;
    case 8:
        changeAct(1, 0xff);
        break;
    }
}

void FtrBed::execFtrAct0D() {
    if (leaveTimer < 0x16) {
        leaveTimer += TICK_STEP_ENDS() ? 1 : 0;
    }
    if (leaveTimer == 0x16) {
        ((Character *)this)->detachTalkRequest(static_cast<TalkMsgRequest *>(this));
        TalkRequest_SetTargetDone(this);
        ProcBase_RequestDelete(this);
    }
}

BOOL FtrBed::enterFtrAct0D() {
    leaveTimer = 0;
    return TRUE;
}

void FtrBed::execFtrAct0C() {
    if (isHidden()) {
        s32 r4 = ownTileX;
        s32 r6 = ownTileY;
        if (footprint == 2) {
            if (inLeftHalf != 0) {
                r4++;
            }
        }
        u32 t = Ftr_GetUnk05(&newBedItem);
        if (inLeftHalf != 0) {
            if (t == 2) {
                r4--;
            }
        }
        u32 c = Item_GetFurnitureIndex(&newBedItem);
        if (FtrMgr_SpawnFromArg(p20::FtrActor_MakeSpawnArg(r4, r6, c, 3, 0, 1))) {
            changeAct(0xd, 0xff);
        }
    }
}

BOOL FtrBed::enterFtrAct0C() {
    findOwnTile(&ownTileX, &ownTileY, 0, 0);
    startHide();
    return TRUE;
}

void FtrBed::execFtrAct0B() {
    if (MenuCtrl_IsFinished()) {
        if (MenuCtrl_IsResultOk() == 0) {
            ((Character *)this)->detachTalkRequest(static_cast<TalkMsgRequest *>(this));
            TalkRequest_SetTargetDone(this);
        } else {
            u32 r4 = MenuCtrl_GetIndex();
            newBedItem = Pocket_GetItem(r4);
            void *p = PlayerData_GetCurrent();
            if (p) {
                ((PlayerData *)(p))->setBed((u16 *)(&newBedItem));
            }
            u16 v = Item_MakeFurniture(FtrActor_GetFtrIndex(this), 0);
            Pocket_SetItem(&v, 0, r4);
            changeAct(0xc, 0xff);
        }
    }
}

const u8 data_ov004_02240024[2] = {0, 1};
const u8 data_ov004_02240028[2] = {0, 1};
const u8 data_ov004_0224002c[2] = {1, 0};
const u8 data_ov004_02240030[2] = {0, 1};
const u8 data_ov004_02240034[2] = {0, 1};
const u8 data_ov004_02240038[2] = {0, 1};
const u8 data_ov004_0224003c[2] = {0, 1};
const u8 data_ov004_02240040[3] = {0, 1, 1};
const u8 data_ov004_02240044[3] = {0, 1, 0};
const u8 data_ov004_02240048[4] = {1, 0, 0, 1};
const u8 data_ov004_0224004c[4] = {0, 1, 1, 0};
const u8 data_ov004_02240050[4] = {0, 1, 1, 0};
const u8 data_ov004_02240054[4] = {0, 1, 1, 0};
const u8 data_ov004_02240058[4] = {0, 1, 1, 0};
const u8 data_ov004_0224005c[4] = {0, 1, 1, 0};
const u8 data_ov004_02240060[4] = {0, 1, 1, 0};
const u8 data_ov004_02240064[5] = {0, 1, 1, 0, 0};
const u32 sFtrStorageKinds[3] = {0xb, 0xc, 0xd};

FxVec3 data_ov004_0224fc84[2] = {FxVec3(0x2000, 0, 0x2000), FxVec3(0x2000, 0, -0x2000)};
FxVec3 data_ov004_0224fc9c[2] = {FxVec3(0x1000, 0, 0x3000), FxVec3(0x1000, 0, -0x3000)};
FxVec3 data_ov004_0224fac0[1] = {FxVec3(0, 0, 0)};
FxVec3 data_ov004_0224fcb4[2] = {FxVec3(-0x1000, 0, -0x1000), FxVec3(-0x1000, 0, 0x1000)};
ItemId sStereoSong(0xfff1);

const FtrBedLieOffsetRow sFtrBedLieOffsets[3] = {{0, 0}, {data_ov004_0224fac0, 1}, {data_ov004_0224fcb4, 2}};

FxVec3 *data_ov004_02249028[3] = {0, data_ov004_0224fc84, data_ov004_0224fc9c};

extern "C" {
ActorProfile sFtrCompassProfile = {(void *(*)())FtrCompass_Create, 0x44, 0x4b, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrVillagerPicProfile = {(void *(*)())FtrVillagerPic_Create, 0x45, 0x4c, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrPhoneProfile = {(void *(*)())FtrPhone_Create, 0x4f, 0x56, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrClockProfile = {(void *(*)())FtrClock_Create, 0x39, 0x40, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrStereoProfile = {(void *(*)())FtrStereo_Create, 0x3a, 0x41, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrInstrumentProfile = {(void *(*)())FtrInstrument_Create, 0x46, 0x4d, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrPiggyBankProfile = {(void *(*)())FtrPiggyBank_Create, 0x47, 0x4e, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrMetronomeProfile = {(void *(*)())FtrMetronome_Create, 0x48, 0x4f, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrBasicProfile = {(void *(*)())FtrBasic_Create, 0x2f, 0x36, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrTvProfile = {(void *(*)())FtrTv_Create, 0x3b, 0x42, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrKind02Profile = {(void *(*)())FtrKind02_Create, 0x30, 0x37, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrKind03Profile = {(void *(*)())FtrKind03_Create, 0x31, 0x38, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrTvVcrProfile = {(void *(*)())FtrTvVcr_Create, 0x3c, 0x43, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrKind04Profile = {(void *(*)())FtrKind04_Create, 0x32, 0x39, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrKind05Profile = {(void *(*)())FtrKind05_Create, 0x33, 0x3a, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrCartProfile = {(void *(*)())FtrCart_Create, 0x3d, 0x44, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrGyroidProfile = {(void *(*)())FtrGyroid_Create, 0x3e, 0x45, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrWallpaperSampleProfile = {(void *(*)())FtrWallpaperSample_Create, 0x49, 0x50, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrKind06Profile = {(void *(*)())FtrKind06_Create, 0x34, 0x3b, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrCarpetSampleProfile = {(void *(*)())FtrCarpetSample_Create, 0x4a, 0x51, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrKind25Profile = {(void *(*)())FtrKind25_Create, 0x4b, 0x52, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrHeadwearProfile = {(void *(*)())FtrHeadwear_Create, 0x4c, 0x53, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrKind07Profile = {(void *(*)())FtrKind07_Create, 0x35, 0x3c, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrKind19Profile = {(void *(*)())FtrKind19_Create, 0x3f, 0x46, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrSeatProfile = {(void *(*)())FtrSeat_Create, 0x36, 0x3d, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrBedProfile = {(void *(*)())FtrBed_Create, 0x37, 0x3e, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrCannonProfile = {(void *(*)())FtrCannon_Create, 0x40, 0x47, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrComputerProfile = {(void *(*)())FtrComputer_Create, 0x4d, 0x54, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrNookwayProfile = {(void *(*)())FtrNookway_Create, 0x50, 0x57, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrShirtProfile = {(void *(*)())FtrShirt_Create, 0x41, 0x48, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrStorageProfile = {(void *(*)())FtrStorage_Create, 0x38, 0x3f, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrMyDesignProfile = {(void *(*)())FtrMyDesign_Create, 0x42, 0x49, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrSingingInsectProfile = {(void *(*)())FtrSingingInsect_Create, 0x4e, 0x55, 0x0, 0xc8000, 0x12c000, 0x258000};
ActorProfile sFtrDesignDisplayProfile = {(void *(*)())FtrDesignDisplay_Create, 0x43, 0x4a, 0x0, 0xc8000, 0x12c000, 0x258000};
}

extern "C" {
char data_ov004_0224bb44[12] = "obj_etc_tel";
char data_ov004_0224bb50[14] = "m_dummy_floor";
char data_ov004_0224bb60[13] = "m_dummy_wall";
char data_ov004_0224bb70[16] = "obj_etc_bromide";
char data_ov004_0224bb80[8] = "compass";
char data_ov004_0224bb88[2] = "w";
char data_ov004_0224bb8c[2] = "g";
char data_ov004_0224bb90[2] = "b";
char data_ov004_0224bb94[4] = "myD";
char data_ov004_0224bb98[5] = "tv_m";
char data_ov004_0224bba0[5] = "tv.0";
char data_ov004_0224bba8[6] = "tv_pl";
char data_ov004_0224bbb0[15] = "obj_etc_player";
char data_ov004_0224bbc0[15] = "obj_etc_nchest";
char data_ov004_0224bbd0[17] = "sp_etc_sequence4";
char data_ov004_0224bbe4[17] = "sp_etc_sequence2";
}

extern "C" s32 FtrShirt_SyncAct0(FtrActor *o) { return static_cast<FtrShirt *>(o)->FtrShirt::syncAct0(); }
extern "C" s32 FtrShirt_SyncAct1(FtrActor *o) { return static_cast<FtrShirt *>(o)->FtrShirt::syncAct1(); }
extern "C" void FtrTv_MarkNearestTv(FtrActor *o) { static_cast<FtrTv *>(o)->FtrTv::markNearestTv(); }
extern "C" void FtrClock_MarkNearestCabinClock(FtrActor *o) { static_cast<FtrClock *>(o)->FtrClock::markNearestCabinClock(); }
extern "C" void FtrClock_MarkNearestSoundingClock(FtrActor *o) { static_cast<FtrClock *>(o)->FtrClock::markNearestSoundingClock(); }
extern "C" s32 FtrBed_CheckStepTile(FtrActor *o, VecFx32 *pos, s32 ang, VecFx32 *out) {
    return static_cast<FtrBed *>(o)->FtrBed::checkStepTile(pos, ang, out);
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_02209f70) {
    HOST_OVERLAY_VAR(FtrStereo_execTalkAct_tbl),
    HOST_OVERLAY_VAR(FtrStereo_execTalkAct_tbl_init),
    HOST_OVERLAY_VAR(FtrKind02_execFtrAct_tbl),
    HOST_OVERLAY_VAR(FtrKind02_execFtrAct_tbl_init),
    HOST_OVERLAY_VAR(FtrStorage_execTalkAct_tbl),
    HOST_OVERLAY_VAR(FtrStorage_execTalkAct_tbl_init),
    HOST_OVERLAY_VAR(data_ov004_0224fc84),
    HOST_OVERLAY_VAR(data_ov004_0224fc9c),
    HOST_OVERLAY_VAR(data_ov004_0224fac0),
    HOST_OVERLAY_VAR(data_ov004_0224fcb4),
    HOST_OVERLAY_VAR(sStereoSong),
    HOST_OVERLAY_VAR(data_ov004_02249028),
    HOST_OVERLAY_VAR(sFtrCompassProfile),
    HOST_OVERLAY_VAR(sFtrVillagerPicProfile),
    HOST_OVERLAY_VAR(sFtrPhoneProfile),
    HOST_OVERLAY_VAR(sFtrClockProfile),
    HOST_OVERLAY_VAR(sFtrStereoProfile),
    HOST_OVERLAY_VAR(sFtrInstrumentProfile),
    HOST_OVERLAY_VAR(sFtrPiggyBankProfile),
    HOST_OVERLAY_VAR(sFtrMetronomeProfile),
    HOST_OVERLAY_VAR(sFtrBasicProfile),
    HOST_OVERLAY_VAR(sFtrTvProfile),
    HOST_OVERLAY_VAR(sFtrKind02Profile),
    HOST_OVERLAY_VAR(sFtrKind03Profile),
    HOST_OVERLAY_VAR(sFtrTvVcrProfile),
    HOST_OVERLAY_VAR(sFtrKind04Profile),
    HOST_OVERLAY_VAR(sFtrKind05Profile),
    HOST_OVERLAY_VAR(sFtrCartProfile),
    HOST_OVERLAY_VAR(sFtrGyroidProfile),
    HOST_OVERLAY_VAR(sFtrWallpaperSampleProfile),
    HOST_OVERLAY_VAR(sFtrKind06Profile),
    HOST_OVERLAY_VAR(sFtrCarpetSampleProfile),
    HOST_OVERLAY_VAR(sFtrKind25Profile),
    HOST_OVERLAY_VAR(sFtrHeadwearProfile),
    HOST_OVERLAY_VAR(sFtrKind07Profile),
    HOST_OVERLAY_VAR(sFtrKind19Profile),
    HOST_OVERLAY_VAR(sFtrSeatProfile),
    HOST_OVERLAY_VAR(sFtrBedProfile),
    HOST_OVERLAY_VAR(sFtrCannonProfile),
    HOST_OVERLAY_VAR(sFtrComputerProfile),
    HOST_OVERLAY_VAR(sFtrNookwayProfile),
    HOST_OVERLAY_VAR(sFtrShirtProfile),
    HOST_OVERLAY_VAR(sFtrStorageProfile),
    HOST_OVERLAY_VAR(sFtrMyDesignProfile),
    HOST_OVERLAY_VAR(sFtrSingingInsectProfile),
    HOST_OVERLAY_VAR(sFtrDesignDisplayProfile),
    HOST_OVERLAY_VAR(data_ov004_0224bb44),
    HOST_OVERLAY_VAR(data_ov004_0224bb50),
    HOST_OVERLAY_VAR(data_ov004_0224bb60),
    HOST_OVERLAY_VAR(data_ov004_0224bb70),
    HOST_OVERLAY_VAR(data_ov004_0224bb80),
    HOST_OVERLAY_VAR(data_ov004_0224bb88),
    HOST_OVERLAY_VAR(data_ov004_0224bb8c),
    HOST_OVERLAY_VAR(data_ov004_0224bb90),
    HOST_OVERLAY_VAR(data_ov004_0224bb94),
    HOST_OVERLAY_VAR(data_ov004_0224bb98),
    HOST_OVERLAY_VAR(data_ov004_0224bba0),
    HOST_OVERLAY_VAR(data_ov004_0224bba8),
    HOST_OVERLAY_VAR(data_ov004_0224bbb0),
    HOST_OVERLAY_VAR(data_ov004_0224bbc0),
    HOST_OVERLAY_VAR(data_ov004_0224bbd0),
    HOST_OVERLAY_VAR(data_ov004_0224bbe4),
    HOST_OVERLAY_VARS_END
};
