#ifndef GFX_CAMERA_H
#define GFX_CAMERA_H

#include "types.h"
#include "uptr.h"
#include "gfx/VecFx32.h"
#include "sys/CameraBase.h"
#include "gfx/FxMtx43.h"
#include "gfx/CameraPose.h"
#include "gfx/CameraSway.h"
#include "gfx/CameraTownTour.h"

class Actor;
class Camera : public CameraBase, public FxMtx43 {
public:
    Camera() {}

    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();

    BOOL initModeShake();
    void updateModeRestore();
    BOOL initModeRestore();
    void updateModeTrackPair();
    BOOL initModeTrackPair();
    void updateMode4();
    BOOL initMode4();
    void updateMode3();
    BOOL initMode3();
    void updateModeFocus();
    BOOL initModeFocus();
    void updateMode1();
    BOOL initMode1();
    void popView();
    void pushView();
    void updateModeDefault();
    BOOL initModeDefault();

    void dragFocusTo(VecFx32 *p);
    void setLookAt(VecFx32 *a, VecFx32 *b);
    void setLookAtOrbit(VecFx32 *a, s32 r, s32 s, s32 z);
    void updateBlend();
    void setDefaultProjection();
    void updateMode();
    BOOL setMode(s32 idx);
    s32 getRoomEdgeSide(s32 *p);
    void setFocusPreset11(u8 *o, VecFx32 *v);
    BOOL clampToRoomBounds(s32 *p);
    void calcRoomBounds();
    void updateEyeCurveAngle();
    void setFovy(s32 a);
    s32 getBlendEaseOut();
    s32 getBlendEaseIn();
    s32 getBlendEnd();
    s32 getBlendDelay();
    s32 getFovTan();
    s32 getDistance();

    s32 getFollowSlack();
    s16 getYaw();
    s16 getPitch();
    s16 getEyeCurveAngle();
    VecFx32 *getEye();
    void resetOffsets();
    void setBlendParams(u32 *src);
    void setBlendPreset(s32 i);
    void lerpPoses(s32 a, s32 b, s32 n);
    void loadPose(s32 i, CameraPose *out);

    /* 0x80 */ s32 distanceOffset, unk_84, unk_88, unk_8c, nearOffset, farOffset;
    /* 0x98 */ s16 fovyOffset, pitchOffset, yawOffset, unk_9e;
    /* 0xa0 */ s32 followSlackOffset, unk_a4, blendDelayOffset, blendEndOffset, blendEaseInOffset, blendEaseOutOffset;
    /* 0xb8 */ s32 blendDelay, blendEnd, blendEaseIn, blendEaseOut;
    /* 0xc8 */ s32 blendTime;
    /* 0xcc */ s32 invViewMtx[9];
    /* 0xf0 */ u8 pad_f0[0xfc - 0xf0];
    /* 0xfc */ CameraPose target;
    /* 0x110 */ VecFx32 targetFocus;
    /* 0x11c */ s16 saved, savedPitch;
    /* 0x120 */ s32 savedDistance, savedOffset, savedOffsetY, savedOffsetZ, savedFocus, savedFocusY, savedFocusZ;
    /* 0x13c */ s32 savedEye, savedEyeY, savedEyeZ;
    /* 0x148 */ s16 current, currentPitch;
    /* 0x14c */ s32 currentDistance, currentOffset, currentOffsetY, currentOffsetZ, currentFocus, currentFocusY, currentFocusZ;
    /* 0x168 */ s32 eye, eyeY, eyeZ;
    /* 0x174 */ s16 roll;
    /* 0x176 */ s16 pad_176;
    /* 0x178 */ s32 roomMinX, roomMaxX, roomMinZ, roomMaxZ;
    /* 0x188 */ s32 lookTarget, lookTargetY, lookTargetZ, lookEye, lookEyeY, lookEyeZ, lookUp, lookUpY, lookUpZ;
    /* 0x1ac */ s16 eyeCurveAngle;
    /* 0x1ae */ s16 pad_1ae;
    /* 0x1b0 */ s32 aspect, nearClip, farClip;
    /* 0x1bc */ s32 fovSin, fovCos, fovTan;
    /* 0x1c8 */ s16 fovy;
    /* 0x1ca */ u8 focusIsPair;
    /* 0x1cb */ u8 pad_1cb;
    /* 0x1cc */ VecFx32 focusPointA;
    /* 0x1d8 */ VecFx32 focusPointB;
    /* 0x1e4 */ s32 closeUpFactorTarget, closeUpFactor, presetCol, presetRow;
    /* 0x1f4 */ u8 viewPushed, focusYawLocked, roomFocusSide, seMuted;
    /* 0x1f8 */ s32 mode, prevMode, startMode;
    /* 0x204 */ s32 restoreFocus, restoreFocusY, restoreFocusZ, restoreEye, restoreEyeY, restoreEyeZ;
    /* 0x21c */ union {
        sptr modeParam;
        Actor *followTarget;
        CameraSwayState sway;
        CameraTownTourState townTour;
        u8 modeParamBlock[0x18];
    };
};

#endif
