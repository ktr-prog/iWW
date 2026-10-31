#include "types.h"
#include "host_labels.h"
#include "Unk_020d8c7c.h"
#include "talk/MsgStringBase.h"
#include "talk/MsgStringAttr.h"
#include "talk/MsgString.h"
#include "menu/MenuProc.h"
#include "talk/MsgString9B.h"
#include "item/ItemName.h"
#include "ui/LabelString.h"
#include "gfx/BgVramTask.h"
#include "menu/MenuScrollKnob.h"
#include "menu/MenuCursor.h"
#include "menu/MenuBottomButtons.h"
#include "sys/ProcProfile.h"
#include "menu/MenuLauncher.h"
#include "save/MuseumData.h"
#include "ui/HandCursor.h"
#include "ui/ScrollKnob.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0206f834.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov002/unk_ov002_022025cc.h"
#include "proto/ov002/unk_ov002_02202fac.h"
#include "proto/ov145/unk_ov145_02291f60.h"

class DonationMenu;
typedef void (DonationMenu::*Unk_ov145_022937c0_Fn)();







class TextLabel;









extern "C" {
extern u8 gFieldSceneKind;
extern u16 gPad[];

void MIi_CpuCopy16(void *dst, void *src, u32 n);
void MIi_CpuClear16(u16 v, void *dst, u32 n);
s32 _s32_div_f(s32 a, s32 b);
BOOL Math_StepS32(s32 *p, s32 target, s32 step);
#define data_021ed0a0 HOST_LABEL(MuseumData *, data_021ed0a0)
}

extern "C" ProcProfile sDonationMenuProfile = {(void *(*)())DonationMenu_Create, 0xba, 0xbe};
extern "C" GXOamAttr data_ov145_02293820[16] = {
    {0x20678026, 0xc8, 0, 0x8, 0x0},
    {0x00678018, 0xe8, 0, 0x8, 0x0},
    {0x00678008, 0xe8, 0, 0x8, 0x0},
    {0x006780f8, 0xe8, 0, 0x8, 0x0},
    {0x006780e8, 0xe8, 0, 0x8, 0x0},
    {0x006780d8, 0xe8, 0, 0x8, 0x0},
    {0x006780c8, 0xe8, 0, 0x8, 0x0},
    {0x006780ba, 0xc8, 0, 0x8, 0xffff},
    {0x400d0045, 0x106, 0, 0x5, 0x0},
    {0x8005003d, 0xc0, 0, 0x5, 0xffff},
    {0x41e80045, 0x104, 0, 0x5, 0x0},
    {0x81e0003d, 0xc0, 0, 0x5, 0xffff},
    {0x41c40045, 0xc6, 0, 0x5, 0x0},
    {0x81bc003d, 0xc0, 0, 0x5, 0xffff},
    {0x41a00045, 0xc4, 0, 0x7, 0x0},
    {0x8198003d, 0xc0, 0, 0x7, 0xffff},
};

class DonationMenu : public MenuProc {
public:
    DonationMenu() : cursor(), scrollKnob(), bottomButtons(), textLabels(), vramTasks() {}

    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onDraw();
    virtual BOOL execTransition();
    virtual BOOL execMain();
    virtual BOOL execPhase3();
    virtual BOOL execPhase4();
    virtual BOOL execClosed();

    void clearFlags(u32 m);
    void setFlags(u32 m);
    BOOL testFlags(u32 m);
    void updateTabSwitch();
    void setTabFadeLevel(u32 t);
    BOOL moveCursorByPad(u32 pad);
    u32 hitTestTarget(s32 x, s32 y);
    BOOL activateTarget(u32 t);
    void requestTab(u8 v);
    void setTab(u8 v);
    u16 *getTabItemPtr(s32 i);
    s32 getTabCount();
    void updateScrollAnimation();
    void uploadListScreen();
    void composeListScreen();
    void setScrollPos(s32 v);
    void flushDirty();
    void drawEntryNames();
    void resetTextLabels();
    LabelString *allocTextLabel();
    void releaseCursor();
    void pressCursor();
    void refreshCursor();
    void moveCursorTo(s32 a, s32 b);
    void moveCursorToTarget();
    void hideCursor();
    s32 getCursorTargetY();
    s32 getCursorTargetX();
    void showCursor();
    void buildInsectList();
    void buildFishList();
    void buildPaintingList();
    void buildFossilList();
    s32 collectDonatedFurniture(u16 *out, s32 start, s32 n);
    s32 collectDonatedItems(u16 *out, s32 start, s32 n);
    s32 collectDonated(u16 *out, s32 start, s32 n, s32 step);
    void syncKnobToScroll();
    void syncScrollToKnob();
    void updateKnobPosition();
    BOOL finishKnobRelease();
    void moveKnobByKey();
    void releaseKnob();
    void dragKnob(s32 a, s32 flag);
    BOOL tryGrabKnob(s32 x, s32 y);
    void startQuit();
    void resumeInput();
    void startButtonInput();
    void startTouchInput();
    void updateBarTransition();
    void updateCursorRelease();
    void updateCursorPress();
    void updateCursorMove();
    void updateKnobKeysEnd();
    void updateKnobKeys();
    void updateButtons();
    void updateTrackTouch();
    void updateKnobTouch();
    void updateTouch();
    void loadObjGfx();
    void loadBgGfx();
    void setupBgLayers();
    void postStateUpdate();
    void preStateUpdate();
    void postInputUpdate();
    void preInputUpdate();
    void releaseResources();
    void initDonation();
    void updateLayerSlide();
    void stateClosing();
    void stateClose();
    void stateOpening();
    void stateOpen();
    void runMainState();

    /* 0x091 */ u8 unk_91[3];
    /* 0x094 */ s32 slideY;
    /* 0x098 */ u8 unk_98[4];
    /* 0x09c */ s32 scrollY;
    /* 0x0a0 */ s32 scrollTargetY;
    /* 0x0a4 */ s32 scrollMax;
    /* 0x0a8 */ s32 knobPos;
    /* 0x0ac */ s32 knobGrabOffset;
    /* 0x0b0 */ s32 knobLastTickPos;
    /* 0x0b4 */ u16 flags;
    /* 0x0b6 */ s16 topRow;
    /* 0x0b8 */ s16 tabCounts[4];
    /* 0x0c0 */ u8 curTab;
    /* 0x0c1 */ u8 targetTab;
    /* 0x0c2 */ u8 cursorSlot;
    /* 0x0c3 */ u8 returnState;
    /* 0x0c4 */ u8 labelCount;
    /* 0x0c5 */ u8 tabFadeLevel;
    /* 0x0c6 */ u8 tabSwitchState;
    /* 0x0c7 */ u8 pad_c7;
    /* 0x0c8 */ MenuCursorBuf0 cursor;
    /* 0x12c */ MenuScrollKnob scrollKnob;
    /* 0x174 */ MenuBottomButtons bottomButtons;
    /* 0x2d8 */ LabelString textLabels[18];
    /* 0x758 */ BgVramTask vramTasks[3];
    /* 0x7c4 */ u16 fossilItems[0x34];
    /* 0x82c */ u16 fishItems[0x38];
    /* 0x89c */ u16 insectItems[0x38];
    /* 0x90c */ u16 paintingItems[0x14];
    /* 0x934 */ u16 shownRowItems[9];
    /* 0x946 */ u16 rowTemplateScreen[0x400];
    /* 0x1146 */ u16 listScreen[0x400];
    /* 0x1946 */ u16 frameScreen[0x400];
    /* 0x2146 */ u16 basePalette[16];
    /* 0x2166 */ u16 workPalette[16];
};

static inline BOOL Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" DonationMenu *DonationMenu_Create() { return new DonationMenu(); }

BOOL DonationMenu::onCreate() {
    initDonation();
    transitionState = 0;
    setPhase(0);
    return TRUE;
}

BOOL DonationMenu::onDelete() {
    ((MenuLauncher *)(ProcBase_GetParent(this)))->onChildClosed();
    releaseResources();
    return TRUE;
}

BOOL DonationMenu::onDraw() {
    s32 i;
    GXOamAttr *p;
    s32 y;
    if (MenuCtrl_IsButtons()) {
        ((MenuCursorBase *)(&cursor))->drawWrapped();
    }
    if (!testFlags(1)) {
        return FALSE;
    }
    ((MenuBottomButtons *)(&bottomButtons))->drawAt(getSlideOffsetY());
    y = slideY + 0x60;
    if (scrollMax > 0) {
        MenuScrollKnob *q = &scrollKnob;
        q->draw();
        Oam_DrawCell(1, data_ov145_02293820, 0x80, y, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
    p = &data_ov145_02293820[8];
    for (i = 0; i < 4; i++) {
        s32 pal;
        if (i == targetTab) {
            pal = 7;
        } else {
            pal = 5;
        }
        Oam_DrawCell(1, p, 0x80, y, pal, 1, 0x1000, 0x1000, 0, -1, 0, 0);
        p += 2;
    }
    return TRUE;
}

BOOL DonationMenu::execTransition() {
    static Unk_ov145_022937c0_Fn tbl[4] = {
        &DonationMenu::stateOpen,
        &DonationMenu::stateOpening,
        &DonationMenu::stateClose,
        &DonationMenu::stateClosing};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}

void DonationMenu::runMainState() {
    static Unk_ov145_022937c0_Fn tbl[10] = {
        &DonationMenu::updateTouch,
        &DonationMenu::updateKnobTouch,
        &DonationMenu::updateTrackTouch,
        &DonationMenu::updateButtons,
        &DonationMenu::updateKnobKeys,
        &DonationMenu::updateKnobKeysEnd,
        &DonationMenu::updateCursorMove,
        &DonationMenu::updateCursorPress,
        &DonationMenu::updateCursorRelease,
        &DonationMenu::updateBarTransition};
    (this->*tbl[mainState])();
}

BOOL DonationMenu::execMain() {
    preInputUpdate();
    runMainState();
    postInputUpdate();
    return TRUE;
}

BOOL DonationMenu::execPhase3() { return TRUE; }

BOOL DonationMenu::execPhase4() { return TRUE; }

BOOL DonationMenu::execClosed() {
    ProcBase_RequestDelete(this);
    return TRUE;
}

void DonationMenu::stateOpen() {
    setupBgLayers();
    loadBgGfx();
    curTab = 4;
    setTab(3);
    targetTab = 3;
    loadObjGfx();
    beginSubSlideIn(0xa, 4, 0, 0x28);
    Gfx2d_ShowLayer(6);
    Gfx2d_ShowLayer(4);
    updateLayerSlide();
    setFlags(1);
    ((MenuBottomButtons *)(&bottomButtons))->setLayoutSingle05(0x65);
    setTransitionState(1);
}

void DonationMenu::stateOpening() {
    if (stepSlideIn(0)) {
        setPhase(2);
        resumeInput();
    }
    updateLayerSlide();
}

void DonationMenu::stateClose() {
    ((MenuLauncher *)(ProcBase_GetParent(this)))->setNextRequest(0x44, 1);
    beginSubSlideOut(0xa, 0, 0, 0x28);
    updateLayerSlide();
    setTransitionState(3);
}

void DonationMenu::stateClosing() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(6);
        Gfx2d_ResetLayer(4);
        setPhase(5);
    } else {
        updateLayerSlide();
    }
}

void DonationMenu::updateLayerSlide() {
    applySlideOffset(6, 0, 0);
    applySlideOffset(4, 0, 0x18 - scrollY);
    slideY = getSlideOffsetY();
    updateKnobPosition();
}

void DonationMenu::initDonation() {
    s32 i;
    flags = 0;
    curTab = 0;
    for (i = 0; i < 9; i++) {
        shownRowItems[i] = 0xfff1;
    }
    tabFadeLevel = 3;
    tabSwitchState = 0;
    buildFossilList();
    buildPaintingList();
    buildFishList();
    buildInsectList();
    ((MenuScrollKnob *)(&scrollKnob))->show();
}

void DonationMenu::releaseResources() {
    resetTextLabels();
    ((MenuBottomButtons *)(&bottomButtons))->freeTexts();
    vramTasks[0].cancel();
    vramTasks[1].cancel();
    vramTasks[2].cancel();
}

void DonationMenu::preInputUpdate() {
    preStateUpdate();
    MenuCursorBuf0 *p = &cursor;
    p->update();
}

void DonationMenu::postInputUpdate() {
    postStateUpdate();
}

void DonationMenu::preStateUpdate() {
    resetTextLabels();
    ((MenuBottomButtons *)(&bottomButtons))->freeTexts();
    vramTasks[0].cancel();
    vramTasks[1].cancel();
    vramTasks[2].cancel();
    scrollKnob.update();
}

void DonationMenu::postStateUpdate() {
    updateTabSwitch();
    updateScrollAnimation();
    flushDirty();
    ((MenuScrollKnob *)(&scrollKnob))->updateRelease();
}

void DonationMenu::setupBgLayers() {
    Gfx2d_SetSubBgModeState(0);
    Gfx2d_SetLayerPriority(6, 1);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
    Gfx2d_SetLayerPriority(4, 2);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
}

void DonationMenu::loadBgGfx() {
    void *heap = gCurrentHeap;
    Gfx2d_LoadCharFile("menu/donation/bg0.bch", heap, 6, 0x11, 0x11, 0x63);
    Gfx2d_LoadCharFile("menu/donation/bg1.bch", heap, 6, 0x26e, 0x26e, 0x27d);
    Gfx2d_LoadPaletteFile("menu/donation/bg.bpl", heap, 6, 1, 1, 7);
    File_LoadToBuffer("menu/donation/bg_3.bpl", basePalette, 0x20);
    File_LoadToBuffer("menu/donation/b_bg.bsc", rowTemplateScreen, 0x800);
    File_LoadToBuffer("menu/donation/a_bg.bsc", frameScreen, 0x800);
    Gfx2d_LoadScreen((u8 *)frameScreen, 6, 0x800, 0);
}

void DonationMenu::loadObjGfx() {
    MenuButtons_LoadTextColors();
    void *heap = gCurrentHeap;
    Gfx2d_LoadCharFile("menu/donation/obj.bch", heap, 8, 0xc0, 0xc0, 0x13f);
    Gfx2d_LoadPaletteFile("menu/donation/obj.bpl", heap, 8, 4, 4, 9);
}

void DonationMenu::updateTouch() {
    if (checkSwitchToButtons(1)) {
        startButtonInput();
        return;
    }
    if (Both()) {
        if (((MenuBottomButtonsBody *)(&bottomButtons))->isTouched(6)) {
            startQuit();
        } else {
            s32 x = gTouchCurX;
            s32 y = gTouchCurY;
            s32 r = hitTestTarget(x, y);
            if (r != 6) {
                activateTarget(r);
            } else if (scrollMax > 0) {
                if (tryGrabKnob(x, y)) {
                    setMainState(1);
                } else if (x >= 0xe4 && x <= 0xec && y >= 0x15 && y <= 0x8d) {
                    ((MenuScrollKnob *)(&scrollKnob))->grab();
                    setMainState(2);
                }
            }
        }
    }
}

void DonationMenu::updateKnobTouch() {
    if (gTouchHeld != 0) {
        dragKnob(gTouchCurY, 0);
    } else {
        releaseKnob();
        setMainState(0);
    }
}

void DonationMenu::updateTrackTouch() {
    if (gTouchHeld != 0) {
        dragKnob(gTouchCurY, 1);
    } else {
        releaseKnob();
        setMainState(0);
    }
}

void DonationMenu::updateButtons() {
    if (checkSwitchToTouch()) {
        startTouchInput();
        return;
    }
    if (moveCursorByPad(takeRepeatedKeys())) {
        moveCursorToTarget();
        return;
    }
    {
        u32 k = gPad[1];
        if (k & 1) {
            pressCursor();
            return;
        }
        if (k & 2) {
            hideCursor();
            startQuit();
        }
    }
}

void DonationMenu::updateKnobKeys() {
    if (gPad[0] & 1) {
        moveKnobByKey();
        s32 a = getCursorTargetX();
        s32 b = getCursorTargetY();
        ((MenuCursorBase *)(&cursor))->warpTo(a, b);
    } else {
        releaseKnob();
        setMainState(5);
    }
}

void DonationMenu::updateKnobKeysEnd() {
    if (finishKnobRelease()) {
        setMainState(3);
        releaseCursor();
    }
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    ((MenuCursorBase *)(&cursor))->warpTo(a, b);
}

void DonationMenu::updateCursorMove() {
    if (!((MenuCursorBase *)(&cursor))->isMoving()) {
        setMainState(returnState);
        runMainState();
    }
}

void DonationMenu::updateCursorPress() {
    if (((HandCursor *)(&cursor))->isAnimDone()) {
        if (!activateTarget(cursorSlot)) {
            setMainState(3);
            releaseCursor();
        }
    }
}

void DonationMenu::updateCursorRelease() {
    if (((HandCursor *)(&cursor))->isAnimDone()) {
        refreshCursor();
        setMainState(returnState);
    }
}

void DonationMenu::updateBarTransition() {
    if (((MenuBottomButtonsBody *)(&bottomButtons))->stepPress()) {
        if (((HandCursor *)(&cursor))->getAnim()) {
            s32 a = ((MenuBottomButtonsBody *)(&bottomButtons))->getPressOffset();
            s32 b = ((MenuBottomButtonsBody *)(&bottomButtons))->getTargetX(-1);
            s32 c = ((MenuBottomButtonsBody *)(&bottomButtons))->getTargetY(-1);
            ((MenuCursorBase *)(&cursor))->warpTo(a + b, a + c);
        }
    } else {
        hideCursor();
        setPhase(1);
    }
}

void DonationMenu::startTouchInput() {
    hideCursor();
    setMainState(0);
}

void DonationMenu::startButtonInput() {
    cursorSlot = targetTab;
    showCursor();
    restartKeyRepeat();
    setMainState(3);
}

void DonationMenu::resumeInput() {
    if (MenuCtrl_IsTouch()) {
        startTouchInput();
    } else {
        startButtonInput();
    }
}

void DonationMenu::startQuit() {
    MenuCtrl_SetResult(1);
    ((MenuBottomButtonsBody *)(&bottomButtons))->setSelected(6);
    setTransitionState(2);
    setMainState(9);
}

BOOL DonationMenu::tryGrabKnob(s32 x, s32 y) {
    if (((MenuScrollKnob *)(&scrollKnob))->hitTest(x, y)) {
        knobGrabOffset = knobPos - y;
        ((MenuScrollKnob *)(&scrollKnob))->grab();
        knobLastTickPos = knobPos;
        return TRUE;
    }
    return FALSE;
}

void DonationMenu::dragKnob(s32 a, s32 flag) {
    if (flag) {
        a -= 0x1d;
    } else {
        a += knobGrabOffset;
    }
    if (a < 0) {
        a = 0;
    }
    if (a > 0x78) {
        a = 0x78;
    }
    if (flag) {
        Math_StepS32(&knobPos, a, 8);
    } else {
        knobPos = a;
    }
    syncScrollToKnob();
    updateKnobPosition();
    s32 d = knobLastTickPos - knobPos;
    if (d >= 4 || d <= -4) {
        Menu_PlayScrollTickSe();
        knobLastTickPos = knobPos;
    }
}

void DonationMenu::releaseKnob() {
    ((MenuScrollKnob *)(&scrollKnob))->release();
}

void DonationMenu::moveKnobByKey() {
    s32 old = knobPos;
    u32 k = gPad[0];
    if (k & 0x40) {
        knobPos = knobPos - 4;
        if (knobPos < 0) {
            knobPos = 0;
        }
    } else if (k & 0x80) {
        knobPos = knobPos + 4;
        if (knobPos > 0x78) {
            knobPos = 0x78;
        }
    }
    if (old != knobPos) {
        syncScrollToKnob();
        updateKnobPosition();
        Menu_PlayScrollTickSe();
    }
}

BOOL DonationMenu::finishKnobRelease() {
    if (((ScrollKnob *)(&scrollKnob))->areAnimsDone()) {
        ((MenuScrollKnob *)(&scrollKnob))->show();
        return TRUE;
    }
    return FALSE;
}

void DonationMenu::updateKnobPosition() {
    ((ScrollKnob *)(&scrollKnob))->moveTo(0x63, slideY + (knobPos - 0x4b));
}

void DonationMenu::syncScrollToKnob() {
    s32 t;
    s32 n = scrollMax;
    t = _s32_div_f(knobPos * n, 0x78);
    if (t < 0) {
        t = 0;
    }
    if (t > n) {
        t = n;
    }
    setScrollPos(t);
    scrollTargetY = t;
}

void DonationMenu::syncKnobToScroll() {
    if (scrollMax > 0) {
        knobPos = _s32_div_f(scrollY * 0x78, scrollMax);
        updateKnobPosition();
    }
}

s32 DonationMenu::collectDonated(u16 *out, s32 start, s32 n, s32 step) {
    s32 cnt = 0;
    u16 v = 0xfff1;
    s32 i;
    for (i = cnt; i < n; i++) {
        v = start;
        if (data_021ed0a0.isDonated(&v)) {
            out[cnt] = start;
            cnt++;
        }
        start = (u16)(start + step);
    }
    return cnt;
}

s32 DonationMenu::collectDonatedItems(u16 *out, s32 start, s32 n) {
    return collectDonated(out, start, n, 1);
}

s32 DonationMenu::collectDonatedFurniture(u16 *out, s32 start, s32 n) {
    return collectDonated(out, start, n, 4);
}

void DonationMenu::buildFossilList() {
    tabCounts[3] = collectDonatedFurniture(fossilItems, 0x450c, 0x34);
}

void DonationMenu::buildPaintingList() {
    tabCounts[0] = collectDonatedFurniture(paintingItems, 0x3894, 0x14);
}

void DonationMenu::buildFishList() {
    tabCounts[1] = collectDonatedItems(fishItems, 0x12e8, 0x38);
}

void DonationMenu::buildInsectList() {
    tabCounts[2] = collectDonatedItems(insectItems, 0x12b0, 0x38);
}

void DonationMenu::showCursor() {
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    ((MenuCursorBase *)(&cursor))->warpTo(a, b);
    if (cursorSlot == 4) {
        ((MenuCursor *)(&cursor))->setAnimIfChanged(7);
    } else {
        ((MenuCursor *)(&cursor))->setAnimIfChanged(1);
    }
    refreshCursor();
}

s32 DonationMenu::getCursorTargetX() {
    u32 c = cursorSlot;
    if (c <= 3) {
        return (s32)c * -0x24 + 0x94;
    }
    switch (c) {
    case 4:
        return ((MenuBottomButtonsBody *)(&bottomButtons))->getTargetX(6);
    case 5:
        return ((MenuScrollKnob *)(&scrollKnob))->getGripX();
    default:
        return 0x80;
    }
}

s32 DonationMenu::getCursorTargetY() {
    u32 c = cursorSlot;
    if (c <= 3) {
        return 0xad;
    }
    switch (c) {
    case 4:
        return ((MenuBottomButtonsBody *)(&bottomButtons))->getTargetY(6);
    case 5:
        return ((MenuScrollKnob *)(&scrollKnob))->getGripY();
    default:
        return 0x60;
    }
}

void DonationMenu::hideCursor() {
    ((MenuCursor *)(&cursor))->setAnimIfChanged(0);
    cursor.update();
}

void DonationMenu::moveCursorToTarget() {
    if (cursorSlot == 4) {
        ((MenuCursor *)(&cursor))->switchToAnim07();
    } else {
        ((MenuCursor *)(&cursor))->switchToAnim01();
    }
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    moveCursorTo(a, b);
}

void DonationMenu::moveCursorTo(s32 a, s32 b) {
    ((MenuCursorBase *)(&cursor))->moveToEase(a, b, 3, 1);
    returnState = mainState;
    setMainState(6);
}

void DonationMenu::refreshCursor() {
    ((MenuCursorBase *)(&cursor))->setPoseIdle();
    cursor.update();
}

void DonationMenu::pressCursor() {
    ((MenuCursor *)(&cursor))->setPosePress();
    setMainState(7);
}

void DonationMenu::releaseCursor() {
    ((MenuCursorBase *)(&cursor))->setPoseRelease();
    returnState = mainState;
    setMainState(8);
}

LabelString *DonationMenu::allocTextLabel() {
    if (*(volatile u8 *)&labelCount >= 18) {
        return &textLabels[17];
    }
    *(volatile u8 *)&labelCount = *(volatile u8 *)&labelCount + 1;
    return &textLabels[*(volatile u8 *)&labelCount - 1];
}

void DonationMenu::resetTextLabels() {
    s32 i = 0;
    labelCount = 0;
    for (; i < 18; i++) {
        textLabels[i].destroyLabel();
    }
}

void DonationMenu::drawEntryNames() {
    MsgString9B a;
    ItemName b;
    u16 s[2];
    s32 k;
    LabelString *w;
    LabelString *w2;
    s32 cur = topRow;
    u16 *list = getTabItemPtr(cur);
    s32 col = (cur + 9) % 9;
    s32 cnt = getTabCount();
    for (k = 0; k < 9; k++) {
        w = 0;
        if (cur < 0 || cur >= cnt) {
            shownRowItems[col] = 0xfff1;
            w = allocTextLabel();
            w->clear();
            w2 = allocTextLabel();
            w2->clear();
        } else {
            if (*list != shownRowItems[col]) {
                shownRowItems[col] = *list;
                w = allocTextLabel();
                s[0] = *list;
                b.setFromItem(&s[0]);
                w->copy(&b);
                w2 = allocTextLabel();
                s[1] = *list;
                if (data_021ed0a0.getDonorName(&a, &s[1])) {
                    w2->copy(&a);
                } else {
                    String_Load2dMenu(w2, 0xcc);
                }
            }
            list++;
        }
        if (w) {
            w->createLabel(4, col * 26 + 0x184, 0xd, 0xf, 7, 0);
            w->redrawAligned(0, 0);
            w2->createLabel(4, col * 16 + 0xf4, 8, 0xf, 7, 0);
            w2->redrawAligned(0, 0);
        }
        cur++;
        col++;
        if (col >= 9) {
            col = 0;
        }
    }
}

void DonationMenu::flushDirty() {
    if (testFlags(8)) {
        uploadListScreen();
    }
    if (testFlags(2)) {
        if (((BgVramTask *)(&vramTasks[1]))->requestScreen(frameScreen, 6, 0x800, 0)) {
            clearFlags(2);
        }
    }
    if (testFlags(4)) {
        clearFlags(4);
        drawEntryNames();
    }
}

void DonationMenu::setScrollPos(s32 v) {
    scrollY = v;
    Gfx2d_SetLayerOffset(4, 0, scrollY - 0x18);
    topRow = (s16)(v >> 4);
    composeListScreen();
    setFlags(4);
}

void DonationMenu::composeListScreen() {
    s32 cur = topRow;
    s32 r6 = (cur + 9) % 9;
    s32 r4 = cur & 0xf;
    volatile u16 fill = 0x10;
    s32 i;
    MIi_CpuClear16(fill, listScreen, 0x800);
    for (i = 0; i < 9; i++) {
        MIi_CpuCopy16(&rowTemplateScreen[r6 * 0x40], &listScreen[r4 * 0x40], 0x80);
        r6++;
        if (r6 >= 9) {
            r6 = 0;
        }
        r4 = (r4 + 1) & 0xf;
    }
    setFlags(8);
}

void DonationMenu::uploadListScreen() {
    BgScreen_SetRectPalette(listScreen, 0, 0, 0x1f, 0x1f, 3);
    s32 n = getTabCount();
    if (n < 9) {
        BgScreen_SetRectPalette(listScreen, 0, n * 2, 0x1f, 0x12, 4);
    }
    if (((BgVramTask *)(vramTasks))->requestScreen(listScreen, 4, 0x800, 0)) {
        clearFlags(8);
    }
}

void DonationMenu::updateScrollAnimation() {
    if (scrollY != scrollTargetY) {
        if (scrollY > scrollTargetY) {
            scrollY = scrollY - 4;
            if (scrollY < scrollTargetY) {
                scrollY = scrollTargetY;
            }
        } else {
            scrollY = scrollY + 4;
            if (scrollY > scrollTargetY) {
                scrollY = scrollTargetY;
            }
        }
        setScrollPos(scrollY);
        syncKnobToScroll();
    }
}

s32 DonationMenu::getTabCount() {
    return tabCounts[curTab];
}

u16 *DonationMenu::getTabItemPtr(s32 i) {
    u16 *tbl[4] = {paintingItems, fishItems, insectItems, fossilItems};
    if (i < 0) {
        i = 0;
    }
    return tbl[curTab] + i;
}

void DonationMenu::setTab(u8 v) {
    if (curTab != v) {
        curTab = v;
        scrollMax = (getTabCount() - 8) << 4;
        if (scrollMax < 0) {
            scrollMax = 0;
        }
        setScrollPos(0);
        scrollTargetY = 0;
        syncKnobToScroll();
        updateKnobPosition();
    }
}

void DonationMenu::requestTab(u8 v) {
    if (v != targetTab) {
        targetTab = v;
        tabSwitchState = 1;
    }
}

BOOL DonationMenu::activateTarget(u32 t) {
    if (t <= 3) {
        if (t != targetTab) {
            Snd_PlaySe(0xc);
            requestTab((u8)t);
        }
        return FALSE;
    } else {
        switch (t) {
        case 4:
            startQuit();
            return TRUE;
        case 5:
            ((MenuScrollKnob *)(&scrollKnob))->grab();
            Menu_PlayScrollGrabSe();
            setMainState(4);
            return TRUE;
        }
    }
    return FALSE;
}

u32 DonationMenu::hitTestTarget(s32 x, s32 y) {
    if (y >= 0x9d && y < 0xbd) {
        s32 i;
        y = 0x84;
        for (i = 0; i < 4; i++) {
            if (y <= x && y + 0x20 > x) {
                return (u8)i;
            }
            y -= 0x24;
        }
    }
    return 6;
}

BOOL DonationMenu::moveCursorByPad(u32 pad) {
    u32 old = cursorSlot;
    if (old <= 3) {
        if (MenuKeys_HasLeft(pad)) {
            if (cursorSlot < 3) {
                cursorSlot = *(volatile u8 *)&cursorSlot + 1;
            }
        } else if (MenuKeys_HasRight(pad)) {
            if (cursorSlot != 0) {
                cursorSlot = *(volatile u8 *)&cursorSlot - 1;
            } else {
                cursorSlot = 4;
            }
        } else if (MenuKeys_HasUp(pad)) {
            if (scrollMax > 0) {
                cursorSlot = 5;
            }
        }
    } else {
        switch (old) {
        case 4:
            if (MenuKeys_HasUp(pad)) {
                if (scrollMax > 0) {
                    cursorSlot = 5;
                }
            } else if (MenuKeys_HasLeft(pad)) {
                cursorSlot = 0;
            }
            break;
        case 5:
            if (MenuKeys_HasDown(pad)) {
                cursorSlot = 4;
            } else if (MenuKeys_HasLeft(pad)) {
                cursorSlot = 0;
            }
            break;
        }
    }
    if (old != cursorSlot) {
        return TRUE;
    }
    return FALSE;
}

void DonationMenu::setTabFadeLevel(u32 t) {
    MIi_CpuCopy16(basePalette, workPalette, 0x20);
    s32 y = basePalette[7];
    u8 r = y & 0x1f;
    u8 g = (y & 0x3e0) >> 5;
    u8 b = (y & 0x7c00) >> 10;
    s32 n = 3 - t;
    s32 x = basePalette[15];
    r = ((u8)(x & 0x1f) * (s32)t + r * n) / 3;
    g = ((u8)((x & 0x3e0) >> 5) * (s32)t + g * n) / 3;
    b = ((u8)((x & 0x7c00) >> 10) * (s32)t + b * n) / 3;
    workPalette[15] = r | (g << 5) | (b << 10);
    ((BgVramTask *)(&vramTasks[2]))->requestPalette(workPalette, 4, 3);
}

void DonationMenu::updateTabSwitch() {
    switch (tabSwitchState) {
    case 0:
        return;
    case 1:
        if (tabFadeLevel != 0) {
            tabFadeLevel = *(volatile u8 *)&tabFadeLevel - 1;
        } else {
            tabSwitchState = 2;
            setTab(targetTab);
        }
        break;
    case 2:
        if (tabFadeLevel < 3) {
            tabFadeLevel = *(volatile u8 *)&tabFadeLevel + 1;
        } else {
            tabSwitchState = 0;
            return;
        }
        break;
    }
    setTabFadeLevel(tabFadeLevel);
}

BOOL DonationMenu::testFlags(u32 m) {
    if (flags & m) {
        return TRUE;
    }
    return FALSE;
}

void DonationMenu::setFlags(u32 m) { flags = flags | m; }

void DonationMenu::clearFlags(u32 m) { flags = flags & ~m; }

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov145_02291f60) {
    HOST_OVERLAY_VAR(sDonationMenuProfile),
    HOST_OVERLAY_VAR(data_ov145_02293820),
    HOST_OVERLAY_VARS_END
};
