#include "types.h"
#include "host_labels.h"
#include "Unk_020d8c7c.h"
#include "save/BbsPost.h"
#include "save/BbsBoard.h"
#include "nitro/gxoam.h"
#include "talk/MsgString.h"
#include "menu/MenuProc.h"
#include "ui/HandCursor.h"
#include "menu/MenuLauncher.h"
#include "ui/LabelString.h"
#include "gfx/BgVramTask.h"
#include "menu/MenuCursor.h"
#include "sys/ProcProfile.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_0206cbdc.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0206f834.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov113/unk_02291f60.h"

class BbsReadMenu;

extern "C" {
#define data_021e87d8 HOST_LABEL(u8 (*)[], data_021e87d8)
extern u16 gPad[];
void func_ov092_02291ce4(void *p, s32 a, s32 b);
void func_ov092_02291c5c();
void G2x_SetBlendBrightnessExt_(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f);
}










typedef void (BbsReadMenu::*Unk_ov113_02293640_Fn)();


class BbsReadMenu : public MenuProc {
public:
    BbsReadMenu() : bgTasks(), infoLabels(), lineLabels(), cursor() {}

    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onDraw();
    virtual BOOL execTransition();
    virtual BOOL execMain();
    virtual BOOL execPhase3();
    virtual BOOL execPhase4();
    virtual BOOL execClosed();

    BOOL moveFocusByPad(u32 pad);
    void refreshCursor();
    void releaseCursor();
    void pressCursor();
    void moveCursorToTarget();
    void hideCursor();
    s32 getFocusY();
    s32 getFocusX();
    s32 getFocusBaseX();
    void showCursor();
    void updatePostCount();
    BOOL activateFocus();
    void setFocusHighlight(s32 flag);
    BOOL touchButtons();
    void clearFlags(u32 mask);
    void setFlags(u32 mask);
    BOOL testFlags(u32 mask);
    void placeLabel(s32 idx, s32 a, s32 b, s32 c, s32 d);
    void setupButtonLabels();
    void showPost(s32 idx);
    void markPostRead(s32 idx);
    void showPostNumber(s32 i);
    void showPostDate(s32 idx);
    void showPostText(s32 idx);
    void startButtonInput();
    void startTouchInput();
    void mainAct04();
    void mainAct03();
    void mainAct02();
    void mainAct01();
    void mainAct00();
    void loadBg();
    void setupBgLayer();
    void postStateUpdate();
    void postInputUpdate();
    void preStateUpdate();
    void preInputUpdate();
    void releaseResources();
    void init();
    void transitionAct08();
    void transitionAct07();
    void transitionAct06();
    void transitionAct05();
    void transitionAct04();
    void transitionAct03();
    void transitionAct02();
    void transitionAct01();
    void transitionAct00();
    void drawPageDots(s32 a, s32 y);

    /* 0x091 */ u8 unk_91[3];
    /* 0x094 */ s32 slideY;
    /* 0x098 */ u16 flags;
    /* 0x09a */ volatile u8 postIndex;
    /* 0x09b */ volatile u8 focus;
    /* 0x09c */ u8 returnState;
    /* 0x09d */ u8 postCount;
    /* 0x09e */ u8 pageDotsX;
    /* 0x09f */ u8 pad_9f;
    /* 0x0a0 */ u16 bgScreenBuf[0x400];
    /* 0x8a0 */ u8 lineCharBufs[6][0x500];
    /* 0x26a0 */ BgVramTask bgTasks[2];
    /* 0x26e8 */ LabelString infoLabels[4];
    /* 0x27e8 */ LabelString lineLabels[6];
    /* 0x2968 */ MenuCursorBuf1 cursor;
};

static inline BOOL Unk_ov113_02292cc0_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BbsReadMenu *BbsReadMenu_Create() { return new BbsReadMenu(); }

BOOL BbsReadMenu::onCreate() {
    G2x_SetBlendBrightnessExt_(0x4000050, 0x1f, 0x20, 0x10, 0x10, 0);
    init();
    setTransitionState(0);
    setPhase(1);
    return TRUE;
}

BOOL BbsReadMenu::onDelete() {
    ((MenuLauncher *)ProcBase_GetParent(this))->onChildClosed();
    releaseResources();
    return TRUE;
}

void BbsReadMenu::drawPageDots(s32 a, s32 y) {
    u8 i;
    for (i = 0; i < postCount; i++) {
        Oam_DrawObj(0, &data_ov113_022936a0[8 + i], a, y, i == postIndex ? 11 : 10, 1, NULL);
    }
}

BOOL BbsReadMenu::onDraw() {
    if (!testFlags(8)) {
        return TRUE;
    }
    if (MenuCtrl_IsButtons()) {
        cursor.drawWrapped();
    }
    s32 x = 0x80;
    s32 y = slideY + 0x60;
    s32 p0 = 10;
    s32 p1 = 10;
    if (testFlags(2)) {
        p0 = 11;
    } else if (testFlags(4)) {
        p1 = 11;
    }
    Oam_DrawCell(0, &data_ov113_022936a0[0], 0x80, y, p0, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    Oam_DrawCell(0, &data_ov113_022936a0[4], 0x80, y, p1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    x += pageDotsX;
    if (testFlags(0x100)) {
        x += getSlideOffsetX();
    }
    drawPageDots(x, y);
    return TRUE;
}
extern "C" ProcProfile data_ov113_022935c8;
extern "C" GXOamAttr data_ov113_022936a0[23];

extern "C" ProcProfile data_ov113_022935c8 = {(void *(*)())BbsReadMenu_Create, 0xa7, 0xab};

extern "C" GXOamAttr data_ov113_022936a0[23] = {{0x406600f0, 0x1c0, 0, 0xb, 0x0}, {0x7680f0, 0x1c2, 0, 0xb, 0x0}, {0x60660000, 0x1c0, 0, 0xb, 0x0}, {0x20768000, 0x1c2, 0, 0xb, 0xffff}, {0x518a00f0, 0x1c0, 0, 0xa, 0x0}, {0x118280f0, 0x1c2, 0, 0xa, 0x0}, {0x718a0000, 0x1c0, 0, 0xa, 0x0}, {0x31828000, 0x1c2, 0, 0xa, 0xffff}, {0x1c40038, 0x1e3, 0, 0xa, 0x0}, {0x1cc0038, 0x1e3, 0, 0xa, 0x0}, {0x1d40038, 0x1e3, 0, 0xa, 0x0}, {0x1dc0038, 0x1e3, 0, 0xa, 0x0}, {0x1e40038, 0x1e3, 0, 0xa, 0x0}, {0x1ec0038, 0x1e3, 0, 0xa, 0x0}, {0x1f40038, 0x1e3, 0, 0xa, 0x0}, {0x1fc0038, 0x1e3, 0, 0xb, 0x0}, {0x40038, 0x1e3, 0, 0xa, 0x0}, {0xc0038, 0x1e3, 0, 0xa, 0x0}, {0x140038, 0x1e3, 0, 0xa, 0x0}, {0x1c0038, 0x1e3, 0, 0xa, 0x0}, {0x240038, 0x1e3, 0, 0xa, 0x0}, {0x2c0038, 0x1e3, 0, 0xa, 0x0}, {0x340038, 0x1e3, 0, 0xa, 0xffff}};

BOOL BbsReadMenu::execTransition() {
    static Unk_ov113_02293640_Fn tbl[9] = {
        &BbsReadMenu::transitionAct00,
        &BbsReadMenu::transitionAct01,
        &BbsReadMenu::transitionAct02,
        &BbsReadMenu::transitionAct03,
        &BbsReadMenu::transitionAct04,
        &BbsReadMenu::transitionAct05,
        &BbsReadMenu::transitionAct06,
        &BbsReadMenu::transitionAct07,
        &BbsReadMenu::transitionAct08};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}

BOOL BbsReadMenu::execMain() {
    MenuCtrl_TickForceClose();
    if (MenuCtrl_IsForceCloseDue()) {
        if (mainState == 0) goto st;
        if (mainState == 1) {
        st:
            focus = 3;
            hideCursor();
            activateFocus();
            return TRUE;
        }
    }
    preInputUpdate();
    static Unk_ov113_02293640_Fn tbl[5] = {
        &BbsReadMenu::mainAct00,
        &BbsReadMenu::mainAct01,
        &BbsReadMenu::mainAct02,
        &BbsReadMenu::mainAct03,
        &BbsReadMenu::mainAct04};
    (this->*tbl[mainState])();
    postInputUpdate();
    return TRUE;
}

BOOL BbsReadMenu::execPhase3() { return TRUE; }

BOOL BbsReadMenu::execPhase4() { return TRUE; }

BOOL BbsReadMenu::execClosed() {
    ProcBase_RequestDelete(this);
    return TRUE;
}

void BbsReadMenu::transitionAct00() {
    setupBgLayer();
    loadBg();
    beginMainSlideIn(8, 6, 0, 0x30);
    Gfx2d_ShowLayer(2);
    applySlideOffset(2, 0, 0);
    setTransitionState(1);
    setupButtonLabels();
}

void BbsReadMenu::transitionAct01() {
    setTransitionState(2);
    showPost(postIndex);
    slideY = getSlideOffsetY();
    setFlags(8);
}

void BbsReadMenu::transitionAct02() {
    if (stepSlideIn(1)) {
        setPhase(2);
        if (MenuCtrl_IsTouch()) {
            startTouchInput();
        } else {
            startButtonInput();
        }
    }
    applySlideOffset(2, 0, 0);
    slideY = getSlideOffsetY();
}

void BbsReadMenu::transitionAct03() {
    beginMainSlideOut(8, 0, 0, 0x30);
    applySlideOffset(2, 0, 0);
    setTransitionState(4);
}

void BbsReadMenu::transitionAct04() {
    if (stepSlideOut(1)) {
        Gfx2d_HideLayer(2);
        Gfx2d_SetLayerOffset(2, 0, 0);
        setPhase(5);
        clearFlags(8);
    } else {
        applySlideOffset(2, 0, 0);
        slideY = getSlideOffsetY();
    }
}

void BbsReadMenu::transitionAct05() {
    s32 m;
    setFlags(0x100);
    switch (focus) {
    case 1:
    case 4:
        m = 2;
        break;
    case 0:
    case 5:
        m = 3;
        break;
    default:
        if (testFlags(0x40)) {
            m = 2;
        } else {
            m = 3;
        }
        break;
    }
    switch (focus) {
    case 0:
    case 1:
        Snd_PlaySe(0x3c);
        break;
    default:
        Snd_PlaySe(0x39);
        break;
    }
    beginMainSlideOut(8, 0, m, 0x30);
    applySlideOffset(2, 0, 0);
    setTransitionState(6);
}

void BbsReadMenu::transitionAct06() {
    if (stepSlideOut(1)) {
        Gfx2d_HideLayer(2);
        setTransitionState(7);
    } else {
        applySlideOffset(2, 0, 0);
    }
}

void BbsReadMenu::transitionAct07() {
    s32 m;
    switch (focus) {
    case 1:
        setFocusHighlight(0);
    case 4:
        m = 3;
        break;
    case 0:
        setFocusHighlight(0);
    case 5:
        m = 2;
        break;
    default:
        if (testFlags(0x40) == 0) {
            m = 2;
        } else {
            m = 3;
        }
        break;
    }
    beginMainSlideIn(8, 6, m, 0x30);
    Gfx2d_ShowLayer(2);
    applySlideOffset(2, 0, 0);
    setTransitionState(8);
    showPost(postIndex);
}

void BbsReadMenu::transitionAct08() {
    if (stepSlideIn(1)) {
        setPhase(2);
        setFocusHighlight(0);
        if (MenuCtrl_IsTouch()) {
            startTouchInput();
        } else {
            restartKeyRepeat();
            setMainState(1);
            clearFlags(0x100);
            showCursor();
        }
    }
    applySlideOffset(2, 0, 0);
}

void BbsReadMenu::init() {
    slideY = 0;
    flags = 0;
    focus = 3;
    updatePostCount();
    postIndex = postCount - 1;
}

void BbsReadMenu::releaseResources() {
    bgTasks[0].cancel();
    bgTasks[1].cancel();
    infoLabels[0].destroyLabel();
    infoLabels[1].destroyLabel();
    infoLabels[2].destroyLabel();
    infoLabels[3].destroyLabel();
    for (s32 i = 0; i < 6; i++) {
        lineLabels[i].destroyLabel();
    }
}

void BbsReadMenu::preInputUpdate() { preStateUpdate(); }

void BbsReadMenu::preStateUpdate() {
    cursor.update();
    infoLabels[0].destroyLabel();
    infoLabels[1].destroyLabel();
    infoLabels[2].destroyLabel();
    infoLabels[3].destroyLabel();
    for (s32 i = 0; i < 6; i++) {
        lineLabels[i].destroyLabel();
    }
}

void BbsReadMenu::postInputUpdate() { postStateUpdate(); }

void BbsReadMenu::postStateUpdate() {
    if (testFlags(1)) {
        if (bgTasks[1].requestScreen(bgScreenBuf, 2, 0x800, 0)) {
            clearFlags(1);
        }
    }
}

void BbsReadMenu::setupBgLayer() {
    Gfx2d_SetMainBgModeState(0);
    Gfx2d_SetLayerPriority(2, 1);
    Gfx2d_SetLayerControl(2, 0, 0, 0);
}

void BbsReadMenu::loadBg() {
    void *h = gCurrentHeap;
    Gfx2d_LoadPaletteFile("menu/bbs/b_bbs.bpl", h, 2, 8, 8, 0xe);
    File_LoadToBuffer("menu/bbs/b_bbs_us.bsc", bgScreenBuf, 0x800);
    Gfx2d_LoadScreen((u8 *)bgScreenBuf, 2, 0x800, 0);
    Gfx2d_LoadCharFile("menu/bbs/b_bbs.bch", h, 2, 0x10, 0x10, 0x13f);
}

void BbsReadMenu::mainAct00() {
    if (checkSwitchToButtons(1)) {
        startButtonInput();
    } else if (Unk_ov113_02292cc0_Both()) {
        if (touchButtons()) {
            activateFocus();
        }
    }
}

void BbsReadMenu::mainAct01() {
    if (checkSwitchToTouch()) {
        startTouchInput();
    } else if (moveFocusByPad(takeRepeatedKeys())) {
        moveCursorToTarget();
    } else {
        u16 v = gPad[1];
        if ((v & 1) != 0) {
            pressCursor();
        } else if ((v & 2) != 0) {
            focus = 3;
            hideCursor();
            activateFocus();
        } else if ((v & 0x200) != 0) {
            focus = 5;
            if (activateFocus()) {
                hideCursor();
            }
        } else if ((v & 0x100) != 0) {
            focus = 4;
            if (activateFocus()) {
                hideCursor();
            }
        }
    }
}

void BbsReadMenu::mainAct02() {
    if (!cursor.isMoving()) {
        setMainState(returnState);
    }
}

void BbsReadMenu::mainAct03() {
    if (cursor.isAnimDone()) {
        if (activateFocus()) {
            if ((u8)(focus + 0xfe) <= 1) {
                hideCursor();
            } else {
                cursor.setPoseRelease();
            }
        } else {
            releaseCursor();
        }
    }
}

void BbsReadMenu::mainAct04() {
    if (cursor.isAnimDone()) {
        refreshCursor();
        setMainState(1);
    }
}

void BbsReadMenu::startTouchInput() {
    hideCursor();
    setMainState(0);
}

void BbsReadMenu::startButtonInput() {
    showCursor();
    restartKeyRepeat();
    setMainState(1);
}

void BbsReadMenu::showPostText(s32 idx) {
    BbsPost *p = ((BbsBoard *)data_021e87d8)->getPost(idx);
    s32 starts[7];
    s32 cnt;
    s32 i;
    s32 z1 = 0;
    s32 z2 = 0;
    Text_SplitLines(BbsPost_GetText(p), starts, &cnt, 0xc0, 0x28, 0x96, 6);
    for (i = 0; i < 6; i++) {
        s32 len = starts[i + 1] - starts[i];
        LabelString *o = &lineLabels[i];
        ((MsgString *)o)->clear();
        if (len != 0) {
            String_FromEncodedBytesEx(o, BbsPost_GetText(p) + starts[i], len, z1, z1);
        }
    }
    for (i = 0; i < 6; i++) {
        LabelString *o = &lineLabels[i];
        o->createBufferLabel(lineCharBufs[i], 0x14, 0xe, 0xd);
        o->redrawAligned(z2, z2);
    }
    bgTasks[0].requestChars(lineCharBufs, 2, 0x11, 0x11, 0x100);
}

void BbsReadMenu::showPostDate(s32 idx) {
    BbsPost *p = ((BbsBoard *)data_021e87d8)->getPost(idx);
    u8 buf[8];
    buf[0] = 0x37;
    buf[1] = 0x35;
    buf[2] = p->getYear() / 10 + 0x35;
    buf[3] = p->getYear() % 10 + 0x35;
    buf[4] = 0;
    String_FromEncodedBytes(&infoLabels[0], buf, 5);
    placeLabel(0, 0x111, 4, 0, 1);
    buf[0] = p->getMonth() / 10 + 0x35;
    buf[1] = p->getMonth() % 10 + 0x35;
    buf[2] = p->getDay() / 10 + 0x35;
    buf[3] = p->getDay() % 10 + 0x35;
    String_FromEncodedBytes(&infoLabels[1], buf, 5);
    placeLabel(1, 0x116, 4, 0, 1);
}

void BbsReadMenu::showPostNumber(s32 i) {
    u8 buf[4];
    if (i + 1 >= 10) {
        buf[0] = (i + 1) / 10 + 0x35;
        buf[1] = (i + 1) % 10 + 0x35;
        buf[2] = 0;
    } else {
        buf[0] = i + 0x36;
        buf[1] = 0;
    }
    LabelString str;
    String_FromEncodedBytes(&str, buf, 3);
    String_SetSlot(0, &str);
    String_Load2dMenu(&infoLabels[2], 0x86);
    placeLabel(2, 0x11a, 5, 1, 0);
}

void BbsReadMenu::markPostRead(s32 idx) {
    BbsPost *p = ((BbsBoard *)data_021e87d8)->getPost(idx);
    s32 n = PlayerData_GetCurrentIndex();
    s32 m;
    if (p->isRead(n)) {
        m = 8;
    } else {
        m = 0xa;
    }
    BgScreen_SetRectPalette(bgScreenBuf, 0x10, 0, 0x12, 3, m);
    if (p->isFreeText()) {
        m = 0xa;
    } else {
        m = 8;
    }
    BgScreen_SetRectPalette(bgScreenBuf, 6, 5, 0x19, 6, m);
    setFlags(1);
    p->setRead(n);
}

void BbsReadMenu::showPost(s32 idx) {
    showPostDate(idx);
    showPostNumber(idx);
    showPostText(idx);
    markPostRead(idx);
}

void BbsReadMenu::setupButtonLabels() {
    String_Load2dMenu(&infoLabels[0], 0x83);
    placeLabel(0, 0x101, 4, 1, 0);
    String_Load2dMenu(&infoLabels[1], 0x82);
    placeLabel(1, 0x105, 4, 1, 0);
    String_Load2dMenu(&infoLabels[2], 0x84);
    placeLabel(2, 0x109, 4, 1, 0);
    String_Load2dMenu(&infoLabels[3], 0x88);
    placeLabel(3, 0x10d, 4, 1, 0);
}

void BbsReadMenu::placeLabel(s32 idx, s32 a, s32 b, s32 c, s32 d) {
    LabelString *o = &infoLabels[idx];
    o->createSmallLabel(2, a, b, 0xf, 0xa, d);
    o->redrawAligned(c, 0);
}

BOOL BbsReadMenu::testFlags(u32 mask) {
    if (flags & mask) {
        return TRUE;
    }
    return FALSE;
}

void BbsReadMenu::setFlags(u32 mask) { flags = flags | mask; }

void BbsReadMenu::clearFlags(u32 mask) { flags = flags & ~mask; }

BOOL BbsReadMenu::touchButtons() {
    s32 x = gTouchCurX;
    s32 y = gTouchCurY;
    if (y >= 0x54 && y <= 0x70) {
        if (x <= 0x18) {
            focus = 5;
            return TRUE;
        }
        if (x < 0xe8) {
            goto fail;
        }
        focus = 4;
        return TRUE;
    }
    if (y >= 0xa4 && y <= 0xb4) {
        if (x < 0x20) {
            return FALSE;
        }
        if (x < 0x50) {
            focus = 0;
            return TRUE;
        }
        if (x < 0x80) {
            focus = 1;
            return TRUE;
        }
        if (x < 0xb0) {
            focus = 2;
            return TRUE;
        }
        if (x >= 0xe0) {
            goto fail;
        }
        focus = 3;
        return TRUE;
    }
    if (y >= 0x92 && y <= 0x9e) {
        s32 t = pageDotsX + 0x44;
        if (x < t) {
            goto fail;
        }
        u32 idx = (u32)((x - t) << 21) >> 24;
        if (idx >= postCount) {
            return FALSE;
        }
        focus = idx + 6;
        return TRUE;
    }
fail:
    return FALSE;
}

void BbsReadMenu::setFocusHighlight(s32 flag) {
    u32 st = focus;
    switch (st) {
    case 0:
    case 1:
    case 2:
    case 3: {
        s32 e = flag ? 0xe : 0xd;
        s32 x = st * 6 + 4;
        BgScreen_SetRectPalette(bgScreenBuf, x, 0x14, x + 5, 0x16, e);
        setFlags(1);
        break;
    }
    default:
        if (st == 4) {
            if (flag) {
                setFlags(2);
            } else {
                clearFlags(2);
            }
        } else {
            if (flag) {
                setFlags(4);
            } else {
                clearFlags(4);
            }
        }
        break;
    }
}

BOOL BbsReadMenu::activateFocus() {
    updatePostCount();
    u32 st = focus;
    switch (st) {
    case 2:
        Snd_PlaySe(0x29);
    case 3: {
        setFocusHighlight(1);
        transitionState = 3;
        setPhase(1);
        void *r = ProcBase_GetParent(this);
        if (focus == 3) {
            ((MenuLauncher *)r)->setNextRequest(0x43, 0);
            Snd_PlaySe(0x12);
        } else {
            ((MenuLauncher *)r)->setNextRequest(1, 1);
        }
        return TRUE;
    }
    case 4:
        if (postCount > postIndex + 1) {
            postIndex = postIndex + 1;
            setFocusHighlight(1);
            transitionState = 5;
            setPhase(1);
            return TRUE;
        }
        break;
    case 5:
        if (postIndex != 0) {
            postIndex = postIndex - 1;
            setFocusHighlight(1);
            transitionState = 5;
            setPhase(1);
            return TRUE;
        }
        break;
    case 1: {
        s32 t = postCount - 1;
        if (postIndex != t) {
            postIndex = t;
            setFocusHighlight(1);
            transitionState = 5;
            setPhase(1);
            return TRUE;
        }
        break;
    }
    case 0:
        if (postIndex != 0) {
            postIndex = 0;
            setFocusHighlight(1);
            transitionState = 5;
            setPhase(1);
            return TRUE;
        }
        break;
    }
    if (st >= 6 && st <= 0x14) {
        u8 idx = (u8)(st - 6);
        u32 cur = postIndex;
        if (idx == cur) {
            return FALSE;
        }
        if (cur < idx) {
            setFlags(0x40);
        } else {
            clearFlags(0x40);
        }
        postIndex = idx;
        transitionState = 5;
        setPhase(1);
        return TRUE;
    }
    return FALSE;
}

void BbsReadMenu::updatePostCount() {
    postCount = Bbs_GetPostCount();
    pageDotsX = (0xf - postCount) * 4;
}

void BbsReadMenu::showCursor() {
    s32 a = getFocusX();
    s32 b = getFocusY();
    cursor.warpTo(a, b);
    ((MenuCursor *)&cursor)->setAnimIfChanged(1);
    refreshCursor();
}

s32 BbsReadMenu::getFocusBaseX() {
    u32 st = focus;
    if (st <= 3) {
        return st * 0x30 + 0x47;
    }
    if (st == 5) {
        return 0x10;
    }
    if (st == 4) {
        return 0xf0;
    }
    if (st <= 0x14) {
        return pageDotsX + 0x48 + (st - 6) * 8;
    }
    return 0x80;
}

s32 BbsReadMenu::getFocusX() {
    s32 r = getFocusBaseX();
    if (testFlags(0x10)) {
        r -= 0x100;
    } else if (testFlags(0x20)) {
        r += 0x100;
    }
    clearFlags(0x30);
    return r;
}

s32 BbsReadMenu::getFocusY() {
    u32 st = focus;
    if (st <= 3) {
        return 0xaa;
    }
    if (st <= 5) {
        return 0x56;
    }
    if (st <= 0x14) {
        return 0x98;
    }
    return 0x60;
}

void BbsReadMenu::hideCursor() {
    ((MenuCursor *)&cursor)->setAnimIfChanged(0);
    cursor.update();
}

void BbsReadMenu::moveCursorToTarget() {
    if (testFlags(0x80)) {
        s32 a = getFocusX();
        s32 b = getFocusY();
        cursor.warpTo(a, b);
        clearFlags(0x80);
    } else {
        s32 a = getFocusX();
        s32 b = getFocusY();
        cursor.moveToEase(a, b, 4, 1);
        returnState = mainState;
        setMainState(2);
    }
}

void BbsReadMenu::pressCursor() {
    ((MenuCursor *)&cursor)->setPosePress();
    setMainState(3);
}

void BbsReadMenu::releaseCursor() {
    cursor.setPoseRelease();
    setMainState(4);
}

void BbsReadMenu::refreshCursor() {
    cursor.setPoseIdle();
    cursor.update();
}

BOOL BbsReadMenu::moveFocusByPad(u32 pad) {
    u32 st = focus;
    if (st <= 3) {
        if (MenuKeys_HasLeft(pad)) {
            if (focus != 0) {
                focus = focus - 1;
            } else {
                focus = 3;
                setFlags(0x10);
            }
        } else if (MenuKeys_HasRight(pad)) {
            if (focus < 3) {
                focus = focus + 1;
            } else {
                focus = 0;
                setFlags(0x20);
            }
        } else if (MenuKeys_HasUp(pad)) {
            s32 t = pageDotsX + 0x44;
            s32 v = cursor.getFrameScreenX() - t;
            if (v < 0) {
                v = 0;
            }
            s32 i = v >> 3;
            s32 n = postCount;
            if (i >= n) {
                i = n - 1;
            }
            focus = i + 6;
        }
    } else if (st == 5) {
        if (MenuKeys_HasDown(pad)) {
            focus = 6;
        } else if (MenuKeys_HasLeft(pad)) {
            focus = 4;
            setFlags(0x10);
        } else if (MenuKeys_HasRight(pad)) {
            focus = 4;
        }
    } else if (st == 4) {
        if (MenuKeys_HasDown(pad)) {
            focus = postCount + 5;
        } else if (MenuKeys_HasLeft(pad)) {
            focus = 5;
        } else if (MenuKeys_HasRight(pad)) {
            focus = 5;
            setFlags(0x20);
        }
    } else if (st <= 0x14) {
        if (MenuKeys_HasUp(pad)) {
            if (MenuKeys_HasRight(pad) != 0 || (cursor.getFrameScreenX() > 0x80 && MenuKeys_HasLeft(pad) == 0)) {
                focus = 4;
            } else {
                focus = 5;
            }
        } else if (MenuKeys_HasDown(pad)) {
            if (MenuKeys_HasRight(pad) != 0 || (cursor.getFrameScreenX() > 0x80 && MenuKeys_HasLeft(pad) == 0)) {
                focus = 2;
            } else {
                focus = 1;
            }
        } else if (MenuKeys_HasLeft(pad)) {
            if (focus > 6) {
                focus = focus - 1;
                setFlags(0x80);
                Snd_PlaySe(0xb);
            } else {
                focus = 5;
            }
        } else if (MenuKeys_HasRight(pad)) {
            if (focus + 1 < postCount + 6) {
                focus = focus + 1;
                setFlags(0x80);
                Snd_PlaySe(0xb);
            } else {
                focus = 4;
            }
        }
    }
    if (focus != st) {
        return TRUE;
    }
    return FALSE;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_02291f60) {
    HOST_OVERLAY_VAR(data_ov113_022935c8),
    HOST_OVERLAY_VAR(data_ov113_022936a0),
    HOST_OVERLAY_VARS_END
};
