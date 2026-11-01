#include "types.h"
#include "host_tick.h"
#include "talk/MsgStringBase.h"
#include "gfx/SpriteAnim.h"
#include "ui/UiWidget.h"
#include "ui/LabelBalloon.h"
#include "ui/FieldInfoLabelBalloon.h"
#include "talk/MsgString.h"
#include "talk/MsgString33.h"
#include "gfx/Camera.h"
#include "item/ItemName.h"
#include "gfx/Mtx43.h"
#include "proto/autoload_2/unk_020e92f4.h"
#include "proto/main/unk_020d5d0c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02037734.h"
#include "proto/main/unk_0203ecec.h"
#include "proto/main/unk_02065e88.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/main/unk_020b7190.h"


extern "C" {
extern Camera *gCamera;
extern u8 gFieldSceneKind;

Mtx43 *Camera_GetViewMatrix(void);
void MTX_MultVec43(const VecFx32 *src, const Mtx43 *m, VecFx32 *dst);
s32 FX_Div(s32 a, s32 b);
u32 Scene_GetCurrent(void);
BOOL TalkRequest_IsTalking(void);
BOOL TalkRequest_IsSaveMenuRunning(void);
BOOL TalkRequest_IsPlayerMessage(void);
}
extern Mtx43 data_021f47e0;

class FieldInfoBalloon {
public:
    FieldInfoBalloon();
    virtual ~FieldInfoBalloon();

    void updateNetMsg();
    void enterNetMsg();
    void updateTimerMsg();
    void enterTimerMsg();
    void updateItemName();
    void enterItemName();
    void updateIdle();
    void enterIdle();
    BOOL hasNetMsg();
    BOOL hasTimerMsg();
    void startNetMsg();
    void startTimerMsg();
    void applyNetMsgBlink();
    void setNetMsgText(s32 a);
    void setTimerMsgText();
    void setItemNameText();
    void placeNetMsg();
    void placeTimerMsg();
    void placeOverPlayer();
    void updateFacingItem();
    void draw();
    void update();
    void release();
    void init();

    /* 0x04 */ s32 state;
    /* 0x08 */ FieldInfoLabelBalloon balloon;
    /* 0xe4 */ u16 *facingItem;
    /* 0xe8 */ u16 lastFacingItem;
    /* 0xec */ s32 netMsg;
    /* 0xf0 */ s32 timerMsg;
    /* 0xf4 */ s32 netMsgAltPhase;
    /* 0xf8 */ s32 msgFrames;
    /* 0xfc */ u8 netMsgChanged;
    /* 0xfd */ u8 timerMsgRestarted;
};

extern const u8 sFieldInfoBalloonTimerMsgs[4];
extern const u8 sFieldInfoBalloonNetMsgs[11];
extern const u8 sFieldInfoBalloonNetMsgBlink[12];
extern const s32 sFieldInfoBalloonSyncKindMsgs[4];
extern const s16 sFieldInfoBalloonNetMsgFrames[12];
const u8 sFieldInfoBalloonTimerMsgs[4] = {0x8f, 0xbe, 0xbf, 0xc0};
const u8 sFieldInfoBalloonNetMsgs[11] = {0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0xd9, 0xda, 0xdb, 0xed, 0xee, 0xe2};
const u8 sFieldInfoBalloonNetMsgBlink[12] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0};

const s32 sFieldInfoBalloonSyncKindMsgs[4] = {5, 6, 7, 8};
FieldInfoBalloon sFieldInfoBalloon;

void FieldInfoLabelBalloon::requestMarker() {
    markerRequest = 1;
}

void FieldInfoLabelBalloon::resetBalloon() {
    ((LabelBalloon *)(this))->reset();
    markerRequest = 0;
    markerShown = 0;
    blinkFrame = 0;
    markerDrawn = 0;
    markerDrawnPrev = 0;
    blinkEnabled = 0;
}

void FieldInfoLabelBalloon::setBlink(u8 v) {
    blinkEnabled = v;
}

BOOL FieldInfoLabelBalloon::isBlinkCycleEnd() {
    if (blinkEnabled != 0 && blinkFrame == 0x1d) {
        return TRUE;
    }
    return FALSE;
}

BOOL FieldInfoLabelBalloon::isBlinkVisible() {
    if (blinkEnabled != 0 && blinkFrame < 0x19) {
        return TRUE;
    }
    return FALSE;
}

void FieldInfoLabelBalloon::restartMarkerAnim() {
    s32 r4 = ((SpriteAnim *)(((LabelBalloon *)(this))->getAnim()))->getFrameIndex();
    ((SpriteAnim *)(&markerAnim))->setSeq(data_020d5d14);
    ((SpriteAnim *)(&markerAnim))->setPlayOnce(1);
    ((SpriteAnim *)(&markerAnim))->setSpeed(0);
    ((SpriteAnim *)(&markerAnim))->setFrame(r4, 0);
    ((SpriteAnim *)(&markerAnim))->update();
}

void FieldInfoLabelBalloon::updateBlink() {
    if (markerShown) {
        s32 r = ((LabelBalloon *)(this))->getState();
        if (r == 0) {
            markerRequest = 0;
            markerShown = 0;
            blinkFrame = 0;
        } else if (r == 2) {
            if (blinkFrame == 0) Snd_PlaySe(0x3d);
            if (FieldInfoBalloon_IsMenuTransition()) {
                blinkFrame = 0x19;
            } else if (blinkEnabled) {
                blinkFrame++;
                if (blinkFrame >= 0x1e) blinkFrame = 0;
            } else {
                blinkFrame = 1;
            }
        }
    } else if (markerRequest) {
        markerRequest = 0;
        markerShown = 1;
        if (FieldInfoBalloon_IsMenuTransition()) blinkFrame = 0x19;
        else blinkFrame = 0;
        restartMarkerAnim();
    }
}

extern "C" BOOL FieldInfoBalloon_IsMenuTransition() {
    BOOL a = MenuCtrl_IsScreenChanging() != 0;
    BOOL b = MenuCtrl_IsTransitionActive() != 0;
    s32 v = MenuCtrl_GetTransitionProgress();
    if (a || (b && v < 0x1000)) return TRUE;
    return FALSE;
}

extern "C" void FieldInfoBalloon_ShowSyncWaitMsg(s32 arg) {
    s32 v = 0;
    u32 r = Scene_GetCurrent();
    BOOL ok = v;
    if (!((u8)(r + 0xf4) <= 2 || (u8)(r + 0xd2) <= 1)) ok = TRUE;
    if (ok) {
        BOOL a = TalkRequest_IsTalking() || TalkRequest_IsSaveMenuRunning() || TalkRequest_IsPlayerMessage();
        s32 b = 0;
        if (a) {
            u32 *t = (u32 *)TalkWindow_Get(b);
            s32 c = b;
            if (t && t[1]) c = 1;
            if (MenuCtrl_IsMenuOpen()) {
                if (MenuCtrl_IsSyncMsgMenu()) b = 1;
                else v = 1;
            } else if (c) {
                v = 2;
            }
        } else {
            if (MenuCtrl_IsMenuOpen() && MenuCtrl_IsSyncMsgMenu()) b = 1;
        }
        if (b && arg < 4) v = sFieldInfoBalloonSyncKindMsgs[arg];
    }
    if (sFieldInfoBalloon.netMsg != 10) {
        sFieldInfoBalloon.netMsg = v;
        if (v) sFieldInfoBalloon.startNetMsg();
    }
}

extern "C" void FieldInfoBalloon_ShowSyncKindMsg(s32 i) {
    sFieldInfoBalloon.netMsg = sFieldInfoBalloonSyncKindMsgs[i];
    sFieldInfoBalloon.startNetMsg();
}

extern "C" void FieldInfoBalloon_ShowCancelled() {
    sFieldInfoBalloon.netMsg = 9;
    sFieldInfoBalloon.startNetMsg();
}

extern "C" void FieldInfoBalloon_ShowPleaseWait() {
    sFieldInfoBalloon.netMsg = 10;
    sFieldInfoBalloon.startNetMsg();
}

extern "C" void FieldInfoBalloon_ClearNetMsg() { sFieldInfoBalloon.netMsg = 0; }

extern "C" void FieldInfoBalloon_ShowTimerMsg(u32 arg) {
    u32 r = Scene_GetCurrent();
    BOOL ok = FALSE;
    if (!((u8)(r + 0xf4) <= 2 || (u8)(r + 0xd2) <= 1)) ok = TRUE;
    if (ok) {
        sFieldInfoBalloon.timerMsg = arg;
        sFieldInfoBalloon.startTimerMsg();
    }
}

extern "C" void Comm_ReportShutdownError() { Comm_SetShutdownErrorFlag(); }

FieldInfoBalloon::FieldInfoBalloon() : state(0) {
    facingItem = 0;
    lastFacingItem = 0xfff1;
    netMsg = 0;
    timerMsg = 0;
    netMsgAltPhase = 0;
    msgFrames = 0;
    netMsgChanged = 0;
    timerMsgRestarted = 0;
}

FieldInfoBalloon::~FieldInfoBalloon() {}

extern "C" void FieldInfoBalloon_Init() { sFieldInfoBalloon.init(); }

extern "C" void FieldInfoBalloon_Release() { sFieldInfoBalloon.release(); }

extern "C" void FieldInfoBalloon_Update() { sFieldInfoBalloon.update(); }

extern "C" void FieldInfoBalloon_Draw() { sFieldInfoBalloon.draw(); }

void FieldInfoBalloon::init() {
    state = 0;
    ((LabelBalloon *)(&balloon))->enableCenterText();
    facingItem = 0;
    lastFacingItem = 0xfff1;
    netMsg = 0;
    timerMsg = 0;
    netMsgAltPhase = 0;
    msgFrames = 0;
    netMsgChanged = 0;
    timerMsgRestarted = 0;
}

void FieldInfoBalloon::release() { balloon.resetBalloon(); }

void FieldInfoBalloon::update() {
    static void (FieldInfoBalloon::*tbl[4])() = {&FieldInfoBalloon::updateIdle, &FieldInfoBalloon::updateItemName,
                                             &FieldInfoBalloon::updateTimerMsg, &FieldInfoBalloon::updateNetMsg};
    updateFacingItem();
    (this->*tbl[state])();
    timerMsgRestarted = 0;
    balloon.update();
}

const s16 sFieldInfoBalloonNetMsgFrames[12] = {0, 0x1e, 0x1e, 0, 0, 0x78, 0x78, 0x78, 0x78, 0x63, -1, 0};

void FieldInfoBalloon::draw() { balloon.draw(); }

void FieldInfoBalloon::updateFacingItem() {
    u16 *p = 0;
    if (PlayerActor_IsInAction(2, 4)) p = PlayerActor_GetItemInFront();
    if (p) {
        s32 t = (*p & 0xf000) >> 12;
        BOOL b = gFieldSceneKind == 0;
        if (b) {
            if (t != 1 && t != 3 && t != 4) p = 0;
        } else {
            if (t != 1) p = 0;
        }
    }
    if (facingItem) lastFacingItem = *facingItem;
    else lastFacingItem = 0xfff1;
    facingItem = p;
}

void FieldInfoBalloon::placeOverPlayer() {
    data_021f47e0 = *Camera_GetViewMatrix();
    VecFx32 *p = PlayerActor_GetBodyPos(4);
    if (p) {
        VecFx32 v;
        v.x = p->x;
        v.y = p->y;
        v.z = p->z;
        VecFx32 w;
        VecFx32 x;
        v.y += 0x3c00;
        WorldCurve_Apply(&w, &v);
        MTX_MultVec43(&w, &data_021f47e0, &x);
        s32 d = gCamera->getFovTan();
        s32 q = FX_Div(0x60000, d);
        s32 r = FX_Div(-q, x.z);
        Vec_Scale(&x, r);
        ((LabelBalloon *)(&balloon))->setPos(x.x >> 12, -x.y >> 12);
    }
}

void FieldInfoBalloon::placeTimerMsg() { ((LabelBalloon *)(&balloon))->setPos(0, -0x30); }

void FieldInfoBalloon::placeNetMsg() { ((LabelBalloon *)(&balloon))->setPos(0x12, -0x30); }

void FieldInfoBalloon::setItemNameText() {
    ItemName obj((u16 *)(facingItem));
    ((LabelBalloon *)(&balloon))->setText((StrBuf *)(&obj));
}

void FieldInfoBalloon::setTimerMsgText() {
    u8 v = sFieldInfoBalloonTimerMsgs[timerMsg];
    MsgString33 buf;
    String_Load2d(&buf, &v, 0);
    ((LabelBalloon *)(&balloon))->setText((StrBuf *)(&buf));
}

void FieldInfoBalloon::setNetMsgText(s32 a) {
    u8 v;
    MsgString33 buf;
    v = sFieldInfoBalloonNetMsgs[netMsg];
    BOOL is1 = netMsg == 1;
    BOOL is2 = netMsg == 2;
    BOOL c = TRUE;
    if (!is1 && !is2) c = FALSE;
    s32 t = netMsgChanged;
    netMsgChanged = 0;
    if (a) {
        netMsgAltPhase = 0;
        t = 1;
    } else if (c) {
        t = 1;
    }
    if (t) {
        if (netMsgAltPhase == 1) {
            if (is1) v = 0x93;
            else if (is2) v = 0x94;
        }
        String_Load2d(&buf, &v, 0);
        ((LabelBalloon *)(&balloon))->setText((StrBuf *)(&buf));
        if (a == 0) {
            ((LabelBalloon *)(&balloon))->refreshText(1);
            balloon.restartMarkerAnim();
        }
    }
    if (c) {
        netMsgAltPhase++;
        if (netMsgAltPhase >= 2) netMsgAltPhase = 0;
    }
}

void FieldInfoBalloon::applyNetMsgBlink() { balloon.setBlink(sFieldInfoBalloonNetMsgBlink[netMsg]); }

void FieldInfoBalloon::startTimerMsg() {
    msgFrames = 0x3c;
    timerMsgRestarted = 1;
}

void FieldInfoBalloon::startNetMsg() {
    msgFrames = sFieldInfoBalloonNetMsgFrames[netMsg];
    netMsgChanged = 1;
}

BOOL FieldInfoBalloon::hasTimerMsg() {
    BOOL r = timerMsg != 0;
    if (msgFrames == 0) r = FALSE;
    return r;
}

BOOL FieldInfoBalloon::hasNetMsg() {
    BOOL r = netMsg != 0;
    if (msgFrames == 0) r = FALSE;
    return r;
}

void FieldInfoBalloon::enterIdle() { state = 0; }

void FieldInfoBalloon::updateIdle() {
    if (hasNetMsg()) {
        placeNetMsg();
        setNetMsgText(1);
        applyNetMsgBlink();
        if (((LabelBalloon *)(&balloon))->requestOpen()) enterNetMsg();
    } else if (hasTimerMsg()) {
        placeTimerMsg();
        setTimerMsgText();
        balloon.setBlink(0);
        if (((LabelBalloon *)(&balloon))->requestOpen()) enterTimerMsg();
    } else if (facingItem != 0) {
        placeOverPlayer();
        setItemNameText();
        balloon.setBlink(0);
        if (((LabelBalloon *)(&balloon))->requestOpen()) enterItemName();
    }
}

void FieldInfoBalloon::enterItemName() { state = 1; }

void FieldInfoBalloon::updateItemName() {
    if (((LabelBalloon *)(&balloon))->getState() == 0) {
        enterIdle();
    } else if (facingItem == 0 || (lastFacingItem != 0xfff1 && lastFacingItem != *facingItem) || hasNetMsg() != 0 ||
               hasTimerMsg() != 0) {
        ((LabelBalloon *)(&balloon))->requestClose();
    } else {
        placeOverPlayer();
    }
}

void FieldInfoBalloon::enterTimerMsg() { state = 2; }

void FieldInfoBalloon::updateTimerMsg() {
    if (msgFrames > 0) msgFrames -= TICK_STEP_ENDS() ? 1 : 0;
    if (((LabelBalloon *)(&balloon))->getState() == 0) {
        enterIdle();
    } else if (hasNetMsg() != 0 || hasTimerMsg() == 0 || timerMsgRestarted != 0) {
        ((LabelBalloon *)(&balloon))->requestClose();
    }
}

void FieldInfoBalloon::enterNetMsg() {
    balloon.requestMarker();
    state = 3;
}

void FieldInfoBalloon::updateNetMsg() {
    if (msgFrames > 0) msgFrames -= TICK_STEP_ENDS() ? 1 : 0;
    if (((LabelBalloon *)(&balloon))->getState() == 0) {
        enterIdle();
    } else if (hasNetMsg() == 0) {
        if (balloon.isBlinkVisible() == 0) ((LabelBalloon *)(&balloon))->requestClose();
    } else if (balloon.isBlinkCycleEnd() != 0) {
        setNetMsgText(0);
    }
}

