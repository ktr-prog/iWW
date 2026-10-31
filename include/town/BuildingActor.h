#ifndef TOWN_BUILDINGACTOR_H
#define TOWN_BUILDINGACTOR_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "actor/Character.h"
#include "talk/TalkMsgRequest.h"
#include "gfx/Mtx43.h"
#include "town/Unk_ov009_0225b880.h"
#include "uptr.h"
#include "gfx/AnimModel.h"
#include "gfx/ModelSlotPool.h"
#include "snd/BuildingSeEmitter.h"
#include "town/BuildingLights.h"

class ObjShadowStrip;
struct TouchPickTriangle;
class BuildingCollider;
struct BuildingResources;

class BuildingActor : public Character, public TalkMsgRequest {
public:
    BuildingActor();
    virtual ~BuildingActor();
    virtual BOOL onCreate();
    virtual BOOL preDelete();
    virtual BOOL preExecute();
    virtual BOOL postExecute(u32 a);
    virtual BOOL preDraw();
    virtual BOOL acceptsInteraction(void *a);
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual VecFx32 *getInteractionPos();
    virtual void onJointCalcPost(u32 a, void *b);
    virtual void *getDoorInAnim();
    virtual void *getDoorOutAnim();
    virtual s32 setDoorState(s32 a);
    virtual BOOL initBuilding();
    virtual void updateDoorState();
    virtual void setupTalkMsg();
    virtual void onTalkOpened();
    virtual void updateTalk();
    virtual void onTalkEnded();
    virtual void onMessageEnd(u32 attr);
    virtual BOOL isOpen();
    virtual BOOL usesDoorApproach();
    virtual BOOL alignsPlayerToDoor();
    virtual BOOL playsDoorMelody();
    virtual BOOL areLightsOn();
    virtual s32 hasFlickeringLights();
    virtual char *getArcPath();
    virtual char *getTexPath();
    virtual char *getLightTexPath();
    virtual BOOL needsMatrixUpdate();
    virtual VecFx32Ctor getSoundPos();
    virtual BOOL calcCustomBaseMatrix(Mtx43 *out);

    s32 getEntranceType();
    s32 getViewRangeX();
    s32 getViewRangeFront();
    s32 getViewRangeBack();
    BOOL setEntryState(s32 a);
    void execEntryCheck();
    BOOL enterEntryCheck();
    void execEntryIdle();
    BOOL enterEntryIdle();
    void updateEntryState();
    void execDoorNoAnimOut();
    BOOL enterDoorNoAnimOut();
    void execDoorNoAnimIn();
    BOOL enterDoorNoAnimIn();
    void execDoorSlideClose();
    BOOL enterDoorSlideClose();
    void execDoorSlideOpen();
    BOOL enterDoorSlideOpen();
    void execDoorOpenOut();
    BOOL enterDoorOpenOut();
    void execDoorOpenIn();
    BOOL enterDoorOpenIn();
    void execDoorIdle();
    BOOL enterDoorIdle();

    void destroyColliders();
    void submitColliders();
    void createColliders(Mtx43 *m);
    void destroyShadows();
    void updateShadows(Mtx43 *m);
    void createShadows(Mtx43 *m);
    void updateBaseMatrix(Mtx43 *out);
    void updateDoorExit();
    BuildingResources *getResources();
    void makeCurvedMatrix(Mtx43 *out);
    BOOL loadResources(char *a, char *b, char *c);
    BOOL setupModel(char *a, char *b, char *c);
    void *getBtaAnim(u32 idx);
    void *getBca2Anim();
    void setupAnims();
    void initEntryArea();

    BOOL tryOpenDoorForExit();
    BOOL openDoorForExit();
    BOOL tryOpenDoorForEntry();
    BOOL openDoorForEntry();
    BOOL isDoorIdle();
    void updateOffscreen();
    BOOL isOffscreen();
    s32 callIsLit();
    u32 getGridZ();
    u32 getGridX();
    u16 *getItemId();
    s32 getInteriorScene();
    BOOL getDoorPos(VecFx32 *out, s16 *ang);
    void updateMatrix();
    void execEntry08();
    BOOL enterEntry08();
    void execEntry07();
    BOOL enterEntry07();
    void execEntryWarp();
    BOOL enterEntryWarp();
    void execEntry05();
    BOOL enterEntry05();
    void execEntry04();
    BOOL enterEntry04();
    void execEntryTalk();
    BOOL enterEntryTalk();
    void execEntryTalkOpen();
    BOOL enterEntryTalkOpen();

    /* 0x12e */ u16 doorCloseSeDelay;
    /* 0x130 */ u8 doorState;
    /* 0x131 */ u8 pad_131;
    /* 0x132 */ u16 itemId;
    /* 0x134 */ u32 buildingIndex;
    /* 0x138 */ AnimModel model;
    /* 0x1f0 */ BuildingLights lights;
    /* 0x228 */ u32 gridX;
    /* 0x22c */ u32 gridZ;
    /* 0x230 */ u8 exitDelay;
    /* 0x231 */ u8 colliderFlags;
    /* 0x232 */ BuildingEntryFlags entryFlags;
    /* 0x233 */ u8 visitRefused;
    /* 0x234 */ BuildingSeEmitter seEmitter;
    /* 0x278 */ s32 entryState;
    /* 0x27c */ u8 closedTalk;
    /* 0x27d */ u8 pad_27d;
    /* 0x27e */ u16 warpTimer;
    /* 0x280 */ ObjShadowStrip *shadows;
    /* 0x284 */ TouchPickTriangle *collisionShapes;
    /* 0x288 */ BuildingCollider *colliders;
    /* 0x28c */ u8 colliderCount;
    /* 0x28d */ u8 pad_28d;
    /* 0x28e */ ModelSlotHandle modelSlot;
    /* 0x290 */ s32 solidCenterX;
    /* 0x294 */ s32 solidCenterY;
    /* 0x298 */ s32 solidCenterZ;
    /* 0x29c */ s32 solidSizeX;
    /* 0x2a0 */ s32 solidSizeZ;
    /* 0x2a4 */ VecFx32 entryPos;
};

#endif
