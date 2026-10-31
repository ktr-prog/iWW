#ifndef ROOM_FTRACTOR_H
#define ROOM_FTRACTOR_H
#include "game/TouchPickTriangle.h"
#include "room/FtrCollider.h"
#include "room/FtrGlowMat.h"
#include "room/FtrModelRes.h"
#include "room/FtrStackLink.h"
#include "room/FtrSwitch.h"
#include "room/FtrTopItems.h"
#include "room/FtrVisNodes.h"

#include "types.h"
#include "gfx/VecFx32.h"
#include "actor/Character.h"
#include "talk/TalkMsgRequest.h"
#include "gfx/Mtx43.h"
#include "room/FtrActorParts.h"
#include "room/FtrManager.h"
#include "room/FtrTileList.h"
#include "room/FtrModelAnim.h"
#include "room/FtrClockHands.h"
#include "game/TouchPickCylinder.h"
#include "gfx/TwoLayerAnimModel.h"

struct NNSG3dRS;

class FtrActor : public Character, public TalkMsgRequest {
public:
    FtrActor();
    virtual ~FtrActor();
    static void *operator new(size_t size);
    static void operator delete(void *p);

    virtual BOOL onCreate();
    virtual void postCreate(s32 a);
    virtual BOOL preDelete();
    virtual BOOL postDelete(s32 a);
    virtual BOOL onExecute();
    virtual BOOL preDraw();
    virtual VecFx32 *getInteractionPos();
    virtual BOOL onMatCalc(s32 matId, NNSG3dRS *rs);
    virtual void onNodeVisCalc(s32 a, NNSG3dRS *b);
    virtual BOOL onJointCalcPre(s32 nodeId, NNSG3dRS *rs);
    virtual void onJointCalcPost(s32 a, void *b);
    virtual BOOL changeAct(u32 a, u8 b);
    virtual u8 getActSwitchState(u32 a);
    virtual u8 getActAid();
    virtual BOOL initModel();
    virtual BOOL updateActive();
    virtual BOOL updateAppearRemove();
    virtual BOOL isVisible();
    virtual BOOL needsTexCopy();
    virtual void onRemove();
    virtual void onMoveStart(BOOL isPush);
    virtual void onRotateStart(BOOL negative);
    virtual void onRotateUpdate(BOOL negative);
    virtual BOOL isReady();

    void execPreview();
    BOOL enterPreview();
    void execHide();
    BOOL enterHide();
    void execRemove();
    BOOL enterRemove();
    void execPull();
    BOOL enterPull();
    void execPush();
    BOOL enterPush();

    void execRotate();
    BOOL enterRotate();
    void execIdle();
    BOOL enterIdle();
    void execAppear();
    BOOL enterAppear();
    void execAct();
    BOOL setAct(s32 idx);
    BOOL isAct(s32 s);
    BOOL isHidden();
    BOOL isRemoving();
    BOOL isNotReady();
    BOOL isNotIdle();
    BOOL isIdle();
    BOOL startHide();
    BOOL startPull(s16 a);
    BOOL startPush(s16 a);
    BOOL startRotate(s32 a);

    BOOL isPreview();
    void spawnEffectAtCorner(s32 a);
    void spawnEffectAt(VecFx32 *v);
    void spawnActorC0AtCenter();
    void spawnActorC0AtTile(s32 a);
    BOOL findOwnTile(s32 *ox, s32 *oy, VecFx32 *a, s32 b);
    u16 makeCharId(VecFx32 *a, s32 b);
    BOOL canMoveTo(VecFx32 *a, s32 b);
    BOOL canMoveBy(VecFx32 *a);
    BOOL canRotateBy(s32 a);
    BOOL hasItemOnTop();
    void releaseRoomLight();
    void updateLamp();

    void playAnim(s32 a, s32 b, s32 c, u32 d);
    void initAnims(s32 a, s32 b, s32 c, s32 d);
    u16 getAnimFrameCount(s32 a);
    BOOL playSound3();
    BOOL playSound2();
    BOOL playSound1();
    BOOL playSound0();
    u32 hasIndoorFlag6();
    BOOL isSoundingClock();
    BOOL isCabinClock();
    BOOL isGyroid();
    BOOL isSeatOrBed();
    BOOL isTvOn();
    BOOL isStereoOn();
    BOOL bindTvScreenTex(BOOL a);

    void initLamp();
    void moveTiles(VecFx32 *offset, s32 angle);
    void writeTiles(s32 unused, VecFx32 *offset, s32 angle, u8 flag);
    void clearTiles(s32 a, s32 b);
    void getTiles(FtrTileList *l, VecFx32 *offset, s32 angle);
    void applyPolygonId();
    void setupModel();
    void setupFromSpawnArg();

    /* 0x12e */ u16 modelSlot;
    /* 0x130 */ u8 pad_130[0x10];
    /* 0x140 */ VecFx32 modelOffset;
    /* 0x14c */ s32 drawScale;
    /* 0x150 */ s32 drawScaleY;
    /* 0x154 */ s32 drawScaleZ;
    /* 0x158 */ s32 colliderScale;
    /* 0x15c */ u16 appearFrame;
    /* 0x15e */ u16 wobblePhase;
    /* 0x160 */ s16 wobbleSpeed;
    /* 0x164 */ s32 wobbleAmp;
    /* 0x168 */ s16 targetAngle;
    /* 0x16c */ VecFx32 targetPos;
    /* 0x178 */ FtrStackLink stackLink;
    /* 0x188 */ FtrTopItems topItems;
    /* 0x1cc */ TouchPickCylinder topItemCylinders[4];
    /* 0x24c */ u8 moveFlag;
    /* 0x250 */ Mtx43 worldMtx;
    /* 0x280 */ u32 ftrIndex;
    /* 0x284 */ u8 mapLayer;
    /* 0x285 */ u8 isSetUp;
    /* 0x288 */ TouchPickBox touchBox;
    /* 0x530 */ s32 baseAct;
    /* 0x534 */ BlendAnimModel model;
    /* 0x628 */ FtrCollider collider;
    /* 0x6c8 */ FtrModelRes modelRes;
    /* 0x73c */ FtrSwitch switchState;
    /* 0x73e */ FtrClockHands clockHands;
    /* 0x744 */ FtrGlowMat lampMat;
    /* 0x760 */ FtrVisNodes visNodes;
    /* 0x768 */ s32 spawnMode;
    /* 0x76c */ u16 actFrame;
    /* 0x770 */ s32 commentPersonality;
    /* 0x774 */ s32 commentId;
    /* 0x778 */ u8 actAid;
    /* 0x779 */ u8 netRequestPending;
    /* 0x77a */ u8 isInitializing;
    /* 0x77c */ s32 kind;
    /* 0x780 */ s32 footprint;
    /* 0x784 */ s32 hasTopSurface;
    /* 0x788 */ u8 noCollision;
    /* 0x789 */ u8 startsOff;
    /* 0x78c */ s32 surfaceHeight;
    /* 0x790 */ s32 lightKind;
    /* 0x794 */ FtrSoundEmitter soundEmitter;
    /* 0x7b4 */ VecFx32 centerPos;
    /* 0x7c0 */ FtrModelAnim anims[4];
};

#endif
