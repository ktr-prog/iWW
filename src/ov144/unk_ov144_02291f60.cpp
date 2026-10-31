#include "types.h"
#include "Unk_020d8c7c.h"
#include "menu/MenuProc.h"
#include "ui/LabelString.h"
#include "gfx/BgVramTask.h"
#include "menu/MenuScrollKnob.h"
#include "menu/MenuCursor.h"
#include "menu/MenuBottomButtons.h"
#include "menu/MenuErrorMessage.h"
#include "sys/ProcProfile.h"
#include "item/ItemName.h"
#include "menu/MenuLauncher.h"
#include "talk/MsgString.h"
#include "ui/HandCursor.h"
#include "ui/ScrollKnob.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02060034.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov002/unk_ov002_022025cc.h"
#include "proto/ov002/unk_ov002_02202fac.h"
#include "proto/ov004/unk_ov004_02233074.h"
#include "proto/ov144/unk_ov144_02291f60.h"

class MusicMenu;
typedef void (MusicMenu::*Unk_ov144_02293db8_Fn)();



extern "C" {
extern u16 gPad[];
extern u8 gFieldSceneKind;

void MIi_CpuClear16(u16 v, void *dst, u32 n);
void MIi_CpuCopy16(void *dst, void *src, u32 n);
s32 _s32_div_f(s32 a, s32 b);
BOOL Math_StepS32(s32 *p, s32 target, s32 step);
}

extern "C" ProcProfile sMusicMenuProfile = {(void *(*)())MusicMenu_Create, 0xb9, 0xbd};
extern "C" GXOamAttr data_ov144_02293d70[8] = {
    {0x20508028, 0xc0, 0, 0x5, 0x0},
    {0x00508018, 0xe0, 0, 0x5, 0x0},
    {0x00508008, 0xe0, 0, 0x5, 0x0},
    {0x005080f8, 0xe0, 0, 0x5, 0x0},
    {0x005080e8, 0xe0, 0, 0x5, 0x0},
    {0x005080d8, 0xe0, 0, 0x5, 0x0},
    {0x005080c8, 0xe0, 0, 0x5, 0x0},
    {0x005080b8, 0xc0, 0, 0x5, 0xffff},
};








class MusicMenu : public MenuProc {
public:
    MusicMenu()
        : cursor(), scrollKnob(), bottomButtons(), textLabels(), screenTasks(), errorMessage() {}

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
    void scrollToSong(s32 x);
    BOOL moveCursorByPad(u32 pad);
    void targetRowOrButton();
    void targetRowOrRight();
    BOOL targetRowAtCursor();
    void targetButtonAtCursor();
    u32 hitTestTarget(s32 x, s32 y);
    BOOL activateTarget(u32 a);
    BOOL selectSong(s32 v);
    void refreshButtons();
    void paintAddButton(u32 a);
    void paintTakeOutButton(u32 a);
    void paintPlayButton(u32 a);
    void setPlayButtonTiles(u16 v);
    void updateScrollAnimation();
    void uploadListScreen();
    void paintListRow(s32 idx, u32 col);
    void composeListScreen();
    void setScrollPos(s32 v);
    void initScroll();
    void flushDirty();
    void drawSongNames();
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
    void findCurrentSong();
    void buildSongList();
    void syncKnobToScroll();
    void syncScrollToKnob();
    void updateKnobPosition();
    BOOL finishKnobRelease();
    void moveKnobByKey();
    void releaseKnob();
    void dragKnob(s32 x, s32 flag);
    BOOL tryGrabKnob(s32 a, s32 b);
    void showMessage(u8 v);
    void startAddSongs();
    BOOL takeOutSong();
    void stopSong();
    BOOL playSelectedSong();
    void startQuit();
    void resumeInput();
    void startButtonInput();
    void startTouchInput();
    void updateMessage();
    void updateCloseDelay();
    void updateTakeOutDelay();
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
    void initMusic();
    void updateLayerSlide();
    void stateClosing();
    void stateClose();
    void stateOpening();
    void stateOpen();
    void runMainState();

    /* 0x091 */ u8 unk_91[3];
    /* 0x094 */ s32 slideY;
    /* 0x098 */ u32 unk_98;
    /* 0x09c */ s32 scrollY;
    /* 0x0a0 */ s32 scrollTargetY;
    /* 0x0a4 */ s32 scrollMax;
    /* 0x0a8 */ s32 knobPos;
    /* 0x0ac */ s32 knobGrabOffset;
    /* 0x0b0 */ s32 knobLastTickPos;
    /* 0x0b4 */ u16 flags;
    /* 0x0b6 */ s16 topRow;
    /* 0x0b8 */ s16 songCount;
    /* 0x0ba */ s16 selectedSong;
    /* 0x0bc */ s16 playingSong;
    /* 0x0be */ u8 returnState;
    /* 0x0bf */ volatile u8 labelCount;
    /* 0x0c0 */ u8 delayTimer;
    /* 0x0c1 */ u8 cursorSlot;
    /* 0x0c2 */ u8 unk_c2[2];
    /* 0x0c4 */ MenuCursorBuf0 cursor;
    /* 0x128 */ MenuScrollKnob scrollKnob;
    /* 0x170 */ MenuBottomButtons bottomButtons;
    /* 0x2d4 */ LabelString textLabels[9];
    /* 0x514 */ BgVramTask screenTasks[2];
    /* 0x55c */ MenuErrorMessage errorMessage;
    /* 0x664 */ u16 songs[0x46];
    /* 0x6f0 */ u16 shownRowItems[9];
    /* 0x702 */ u16 rowTemplateScreen[0x400];
    /* 0xf02 */ u16 listScreen[0x400];
    /* 0x1702 */ u16 frameScreen[0x400];
};

static inline BOOL IsZero(u8 v) {
    return v == 0 ? TRUE : FALSE;
}

#define C MusicMenu

static inline BOOL Unk_ov144_02292c5c_Rng(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) {
        r = TRUE;
    }
    return r;
}

static inline BOOL Unk_ov144_022934cc_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) return TRUE;
    return FALSE;
}


extern "C" MusicMenu *MusicMenu_Create() { return new MusicMenu(); }

BOOL MusicMenu::onCreate() {
    initMusic();
    transitionState = 0;
    setPhase(0);
    return TRUE;
}

BOOL MusicMenu::onDelete() {
    ((MenuLauncher *)(ProcBase_GetParent(this)))->onChildClosed();
    releaseResources();
    return TRUE;
}

BOOL MusicMenu::onDraw() {
    if (MenuCtrl_IsButtons()) {
        ((MenuCursorBase *)(&cursor))->drawWrapped();
    }
    if (!testFlags(1)) {
        return FALSE;
    }
    ((MenuBottomButtons *)(&bottomButtons))->drawAt(getSlideOffsetY());
    s32 p = slideY + 0x60;
    if (scrollMax > 0) {
        scrollKnob.draw();
        Oam_DrawCell(1, data_ov144_02293d70, 0x80, p, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
    return TRUE;
}

BOOL MusicMenu::execTransition() {
    static Unk_ov144_02293db8_Fn tbl[4] = {
        &MusicMenu::stateOpen, &MusicMenu::stateOpening,
        &MusicMenu::stateClose, &MusicMenu::stateClosing};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}

void C::runMainState() {
    static Unk_ov144_02293db8_Fn tbl[13] = {
        &C::updateTouch,
        &C::updateKnobTouch,
        &C::updateTrackTouch,
        &C::updateButtons,
        &C::updateKnobKeys,
        &C::updateKnobKeysEnd,
        &C::updateCursorMove,
        &C::updateCursorPress,
        &C::updateCursorRelease,
        &C::updateBarTransition,
        &C::updateTakeOutDelay,
        &C::updateCloseDelay,
        &C::updateMessage};
    (this->*tbl[mainState])();
}

BOOL C::execMain() {
    MenuCtrl_TickForceClose();
    if (MenuCtrl_IsForceCloseDue()) {
        switch (mainState) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            hideCursor();
            startQuit();
            setPhase(1);
        }
    }
    preInputUpdate();
    runMainState();
    postInputUpdate();
    return TRUE;
}

BOOL C::execPhase3() { return TRUE; }

BOOL C::execPhase4() { return TRUE; }

BOOL C::execClosed() {
    ProcBase_RequestDelete(this);
    return TRUE;
}

void C::stateOpen() {
    setupBgLayers();
    loadBgGfx();
    initScroll();
    loadObjGfx();
    beginSubSlideIn(0xa, 4, 0, 0x18);
    Gfx2d_ShowLayer(6);
    Gfx2d_ShowLayer(4);
    updateLayerSlide();
    setFlags(1);
    ((MenuBottomButtons *)(&bottomButtons))->setLayoutSingle05(0x65);
    setTransitionState(1);
}

void C::stateOpening() {
    if (stepSlideIn(0)) {
        setPhase(2);
        resumeInput();
    }
    updateLayerSlide();
}

void C::stateClose() {
    MenuLauncher *t = (MenuLauncher *)ProcBase_GetParent(this);
    if (testFlags(0x20)) {
        t->setNextRequest(0x23, 1);
    } else {
        t->setNextRequest(0x44, 1);
    }
    beginSubSlideOut(0xa, 0, 0, 0x18);
    updateLayerSlide();
    setTransitionState(3);
}

void C::stateClosing() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(6);
        Gfx2d_ResetLayer(4);
        setPhase(5);
    } else {
        updateLayerSlide();
    }
}

void C::updateLayerSlide() {
    applySlideOffset(6, 0, 0);
    applySlideOffset(4, 0, 0x18 - scrollY);
    slideY = getSlideOffsetY();
    updateKnobPosition();
}

void C::initMusic() {
    s32 i = 0;
    flags = i;
    for (; i < 9; i++) {
        shownRowItems[i] = 0xfff1;
    }
    buildSongList();
    findCurrentSong();
    ((MenuScrollKnob *)(&scrollKnob))->show();
}

void C::releaseResources() {
    resetTextLabels();
    ((MenuBottomButtons *)(&bottomButtons))->freeTexts();
    screenTasks[0].cancel();
    screenTasks[1].cancel();
}

void C::preInputUpdate() {
    preStateUpdate();
    cursor.update();
}

void C::postInputUpdate() {
    postStateUpdate();
}

void C::preStateUpdate() {
    resetTextLabels();
    ((MenuBottomButtons *)(&bottomButtons))->freeTexts();
    screenTasks[0].cancel();
    screenTasks[1].cancel();
    scrollKnob.update();
}

void C::postStateUpdate() {
    updateScrollAnimation();
    flushDirty();
    ((MenuScrollKnob *)(&scrollKnob))->updateRelease();
}

void C::setupBgLayers() {
    Gfx2d_SetSubBgModeState(0);
    Gfx2d_SetLayerPriority(6, 1);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
    Gfx2d_SetLayerPriority(4, 2);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
    Gfx2d_SetLayerPriority(3, 2);
    Gfx2d_SetLayerControl(3, 0, 0, 0);
}

void C::loadBgGfx() {
    void *h = gCurrentHeap;
    Gfx2d_LoadCharFile("menu/music/bg0.bch", h, 6, 0x11, 0x11, 0x98);
    Gfx2d_LoadCharFile("menu/music/bg1.bch", h, 6, 0x26e, 0x26e, 0x27e);
    Gfx2d_LoadPaletteFile("menu/music/bg.bpl", h, 6, 1, 1, 0xa);
    File_LoadToBuffer("menu/music/b_bg.bsc", rowTemplateScreen, 0x800);
    File_LoadToBuffer("menu/music/a_bg.bsc", frameScreen, 0x800);
    refreshButtons();
}

void C::loadObjGfx() {
    MenuButtons_LoadTextColors();
    void *h = gCurrentHeap;
    Gfx2d_LoadCharFile("menu/music/obj.bch", h, 8, 0xc0, 0xc0, 0x120);
    Gfx2d_LoadPaletteFile("menu/music/obj.bpl", h, 8, 4, 4, 5);
}

void C::updateTouch() {
    if (checkSwitchToButtons(1)) {
        startButtonInput();
        return;
    }
    if (Unk_ov144_022934cc_Both()) {
        s32 x = gTouchCurX;
        s32 y = gTouchCurY;
        s32 r = hitTestTarget(x, y);
        if (r != 0xe) {
            activateTarget(r);
            return;
        }
        if (scrollMax > 0) {
            if (tryGrabKnob(x, y)) {
                setMainState(1);
            } else if (x >= 0xcf && x <= 0xdf && y >= 0x1d && y <= 0x93) {
                ((MenuScrollKnob *)(&scrollKnob))->grab();
                knobLastTickPos = knobPos;
                setMainState(2);
            }
        }
    }
}

void C::updateKnobTouch() {
    if (gTouchHeld != 0) {
        dragKnob(gTouchCurY, 0);
    } else {
        releaseKnob();
        setMainState(0);
    }
}

void C::updateTrackTouch() {
    if (gTouchHeld != 0) {
        dragKnob(gTouchCurY, 1);
    } else {
        releaseKnob();
        setMainState(0);
    }
}

void C::updateButtons() {
    if (checkSwitchToTouch()) {
        startTouchInput();
    } else if (moveCursorByPad(takeRepeatedKeys())) {
        moveCursorToTarget();
    } else {
        u32 t = gPad[1];
        if (t & 1) {
            pressCursor();
        } else if (t & 2) {
            hideCursor();
            startQuit();
        }
    }
}

void C::updateKnobKeys() {
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

void C::updateKnobKeysEnd() {
    if (finishKnobRelease()) {
        setMainState(3);
        releaseCursor();
    }
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    ((MenuCursorBase *)(&cursor))->warpTo(a, b);
}

void C::updateCursorMove() {
    if (!((MenuCursorBase *)(&cursor))->isMoving()) {
        setMainState(returnState);
        runMainState();
    }
}

void C::updateCursorPress() {
    if (((HandCursor *)(&cursor))->isAnimDone()) {
        if (!activateTarget(cursorSlot)) {
            setMainState(3);
            releaseCursor();
        }
    }
}

void C::updateCursorRelease() {
    if (((HandCursor *)(&cursor))->isAnimDone()) {
        refreshCursor();
        setMainState(returnState);
    }
}

void C::updateBarTransition() {
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

void C::updateTakeOutDelay() {
    if (delayTimer != 0) {
        delayTimer = *(volatile u8 *)&delayTimer - 1;
    } else {
        SongSet_RemoveSong(songs[selectedSong]);
        s32 p = *(volatile s16 *)&selectedSong;
        s32 q = *(volatile s16 *)&playingSong;
        if (p < q) {
            playingSong = q - 1;
        }
        selectSong(-1);
        buildSongList();
        scrollMax = (songCount - 8) << 4;
        if (scrollMax < 0) {
            scrollMax = 0;
        }
        s32 t = scrollMax;
        if (scrollY > t) {
            scrollY = t;
        }
        setScrollPos(scrollY);
        scrollTargetY = scrollY;
        syncKnobToScroll();
        resumeInput();
    }
}

void C::updateCloseDelay() {
    if (delayTimer != 0) {
        delayTimer = *(volatile u8 *)&delayTimer - 1;
    } else {
        hideCursor();
        setPhase(1);
    }
}

void C::updateMessage() {
    if (((MenuErrorMessage *)(&errorMessage))->update(1)) {
        resumeInput();
        ((HandCursor *)(&cursor))->enableObjWindow();
    }
}

void C::startTouchInput() {
    hideCursor();
    setMainState(0);
}

void MusicMenu::startButtonInput() {
    if (testFlags(0x10)) {
        clearFlags(0x10);
    } else {
        cursorSlot = 0xb;
    }
    showCursor();
    ((MenuProc *)(this))->restartKeyRepeat();
    setMainState(3);
}

void MusicMenu::resumeInput() {
    if (MenuCtrl_IsTouch()) {
        startTouchInput();
    } else {
        startButtonInput();
    }
}

void MusicMenu::startQuit() {
    MenuCtrl_SetResult(0);
    ((MenuBottomButtonsBody *)(&bottomButtons))->setSelected(6);
    setTransitionState(2);
    setMainState(9);
}

BOOL MusicMenu::playSelectedSong() {
    if (selectedSong == -1) {
        return FALSE;
    }
    if (playingSong != -1) {
        stopSong();
        return FALSE;
    }
    clearFlags(0x20);
    delayTimer = 5;
    paintPlayButton(8);
    setMainState(0xb);
    scrollToSong(selectedSong);
    MenuCtrl_SetResult(1);
    MenuCtrl_SetSongItem(songs[selectedSong]);
    setTransitionState(2);
    Snd_PlaySe(0x55);
    return TRUE;
}

void MusicMenu::stopSong() {
    if (IsZero(gFieldSceneKind) == 0) {
        FtrMgr_BroadcastStereosAct0();
    }
    scrollToSong(playingSong);
    playingSong = -1;
    setFlags(8);
    refreshButtons();
    resumeInput();
    Snd_PlaySe(0x56);
}

BOOL MusicMenu::takeOutSong() {
    if (selectedSong == -1) {
        return FALSE;
    }
    s32 t = Pocket_FindEmpty();
    s32 m = -1;
    if (t == m) {
        showMessage(0x10);
        return TRUE;
    }
    u16 v = songs[selectedSong];
    Pocket_SetItem(&v, 0, t);
    if (selectedSong == playingSong) {
        if (IsZero(gFieldSceneKind) == 0) {
            FtrMgr_BroadcastStereosAct0();
        }
        playingSong = -1;
    }
    SongSet_RemoveSong(songs[selectedSong]);
    scrollToSong(selectedSong);
    delayTimer = 10;
    paintTakeOutButton(8);
    setMainState(10);
    setFlags(0x10);
    Snd_PlaySe(0x58);
    return TRUE;
}

void MusicMenu::startAddSongs() {
    setFlags(0x20);
    paintAddButton(8);
    delayTimer = 5;
    setMainState(0xb);
    setTransitionState(2);
    Snd_PlaySe(0x57);
}

void MusicMenu::showMessage(u8 v) {
    u8 l = v;
    ((MenuErrorMessage *)(&errorMessage))->open((u8 *)(&l), 1, 0);
    setMainState(0xc);
    ((HandCursor *)(&cursor))->disableObjWindow();
}

BOOL MusicMenu::tryGrabKnob(s32 a, s32 b) {
    if (((MenuScrollKnob *)(&scrollKnob))->hitTest(a, b)) {
        knobGrabOffset = knobPos - b;
        ((MenuScrollKnob *)(&scrollKnob))->grab();
        knobLastTickPos = knobPos;
        return TRUE;
    }
    return FALSE;
}

void MusicMenu::dragKnob(s32 x, s32 flag) {
    if (flag) {
        x -= 0x1d;
    } else {
        x += knobGrabOffset;
    }
    if (x < 0) {
        x = 0;
    }
    if (x > 0x78) {
        x = 0x78;
    }
    if (flag) {
        Math_StepS32(&knobPos, x, 8);
    } else {
        knobPos = x;
    }
    syncScrollToKnob();
    updateKnobPosition();
    s32 d = knobLastTickPos - knobPos;
    if (d >= 4 || d <= -4) {
        Menu_PlayScrollTickSe();
        knobLastTickPos = knobPos;
    }
}

void MusicMenu::releaseKnob() {
    scrollKnob.release();
}

void MusicMenu::moveKnobByKey() {
#define A8 (*(volatile s32 *)&knobPos)
    s32 old = A8;
    u32 keys = gPad[0];
    if (keys & 0x40) {
        A8 = A8 - 4;
        if (A8 < 0) {
            A8 = 0;
        }
    } else if (keys & 0x80) {
        A8 = A8 + 4;
        if (A8 > 0x78) {
            A8 = 0x78;
        }
    }
    if (old != A8) {
        syncScrollToKnob();
        updateKnobPosition();
        Menu_PlayScrollTickSe();
    }
#undef A8
}

BOOL MusicMenu::finishKnobRelease() {
    if (((ScrollKnob *)(&scrollKnob))->areAnimsDone()) {
        ((MenuScrollKnob *)(&scrollKnob))->show();
        return TRUE;
    }
    return FALSE;
}

void MusicMenu::updateKnobPosition() {
    ((ScrollKnob *)(&scrollKnob))->moveTo(0x4f, slideY + (knobPos - 0x4b));
}

void MusicMenu::syncScrollToKnob() {
    s32 v;
    s32 n = scrollMax;
    v = _s32_div_f(knobPos * n, 0x78);
    if (v < 0) {
        v = 0;
    }
    if (v > n) {
        v = n;
    }
    setScrollPos(v);
    scrollTargetY = v;
}

void MusicMenu::syncKnobToScroll() {
    if (scrollMax > 0) {
        knobPos = _s32_div_f(scrollY * 0x78, scrollMax);
        updateKnobPosition();
    }
}

void MusicMenu::buildSongList() {
    s32 i;
    u16 id;
    id = 0x1323;
    i = 0;
    songCount = 0;
    s16 *pc = &songCount;
    for (; i < 0x46; i++) {
        if (SongSet_HasSong(id)) {
            songs[songCount] = id;
            *pc = *pc + 1;
        }
        id++;
    }
}

void MusicMenu::findCurrentSong() {
    s32 i;
    s32 target;
    s32 n;
    u16 id;
    id = 0x1323;
    n = 0;
    playingSong = -1;
    if (*HouseRoom_GetCurrentSong() != 0xfff1) {
        u16 *pv = HouseRoom_GetCurrentSong();
        if (Unk_ov144_02292c5c_Rng(pv, id, 0x1368)) {
            target = *pv - 0x1323;
        } else {
            target = -1;
        }
        for (i = 0; i < 0x46; i++) {
            if (SongSet_HasSong(id)) {
                if (i == target) {
                    playingSong = n;
                    i = 0x46;
                }
                n++;
            }
            id++;
        }
    }
    selectedSong = playingSong;
}

void MusicMenu::showCursor() {
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    ((MenuCursorBase *)(&cursor))->warpTo(a, b);
    ((MenuCursor *)(&cursor))->setAnimIfChanged(1);
    refreshCursor();
}

s32 MusicMenu::getCursorTargetX() {
    u32 c = cursorSlot;
    if (c <= 8) {
        return 0x48;
    }
    switch (c) {
    case 9:
        return ((MenuBottomButtonsBody *)(&bottomButtons))->getTargetX(6);
    case 11:
    case 12:
    case 13:
        return 0x26;
    case 10:
        return ((MenuScrollKnob *)(&scrollKnob))->getGripX();
    default:
        return 0x80;
    }
}

s32 MusicMenu::getCursorTargetY() {
    u32 c = cursorSlot;
    if (c <= 8) {
        return c * 16 + 0x20 - (scrollTargetY & 0xf);
    }
    switch (c) {
    case 9:
        return ((MenuBottomButtonsBody *)(&bottomButtons))->getTargetY(6);
    case 11:
        return 0x2a;
    case 12:
        return 0x7d;
    case 13:
        return 0x65;
    case 10:
        return ((MenuScrollKnob *)(&scrollKnob))->getGripY();
    default:
        return 0x60;
    }
}

void MusicMenu::hideCursor() {
    ((MenuCursor *)(&cursor))->setAnimIfChanged(0);
    cursor.update();
}

void MusicMenu::moveCursorToTarget() {
    if (cursorSlot == 9) {
        ((MenuCursor *)(&cursor))->switchToAnim07();
    } else if (cursorSlot <= 8) {
        ((MenuCursor *)(&cursor))->switchToAnim07();
    } else {
        ((MenuCursor *)(&cursor))->switchToAnim01();
    }
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    moveCursorTo(a, b);
}

void MusicMenu::moveCursorTo(s32 a, s32 b) {
    ((MenuCursorBase *)(&cursor))->moveToEase(a, b, 3, 1);
    returnState = mainState;
    setMainState(6);
}

void MusicMenu::refreshCursor() {
    ((MenuCursorBase *)(&cursor))->setPoseIdle();
    cursor.update();
}

void MusicMenu::pressCursor() {
    ((MenuCursor *)(&cursor))->setPosePress();
    setMainState(7);
}

void MusicMenu::releaseCursor() {
    ((MenuCursorBase *)(&cursor))->setPoseRelease();
    returnState = mainState;
    setMainState(8);
}

LabelString *MusicMenu::allocTextLabel() {
    if (labelCount >= 9) {
        return &textLabels[8];
    }
    labelCount = labelCount + 1;
    return &textLabels[labelCount - 1];
}

void MusicMenu::resetTextLabels() {
    s32 i = 0;
    labelCount = 0;
    for (; i < 9; i++) {
        ((LabelString *)(&textLabels[i]))->destroyLabel();
    }
}

void MusicMenu::drawSongNames() {
    u16 t;
    s32 i;
    LabelString *obj;
    s32 cnt;
    s32 idx;
    u16 *p;
    s32 slot;
    ItemName name;
    idx = topRow;
    if (idx < 0) {
        p = songs;
    } else {
        p = &songs[idx];
    }
    slot = (idx + 9) % 9;
    cnt = songCount;
    for (i = 0; i < 9; i++) {
        obj = NULL;
        if (idx < 0 || idx >= cnt) {
            shownRowItems[slot] = 0xfff1;
            obj = allocTextLabel();
            obj->clear();
        } else {
            if (*p != shownRowItems[slot]) {
                shownRowItems[slot] = *p;
                obj = allocTextLabel();
                t = *p;
                name.setFromItem(&t);
                obj->copy(&name);
            }
            p++;
        }
        if (obj) {
            obj->createLabel(4, slot * 0x1a + 0x184, 0xd, 0xf, 7, 0);
            obj->redrawAligned(0, 0);
        }
        idx++;
        slot++;
        if (slot >= 9) {
            slot = 0;
        }
    }
}

void MusicMenu::flushDirty() {
    if (testFlags(8)) {
        uploadListScreen();
    }
    if (testFlags(2)) {
        if (((BgVramTask *)(&screenTasks[1]))->requestScreen(frameScreen, 6, 0x800, 0)) {
            clearFlags(2);
        }
    }
    if (testFlags(4)) {
        clearFlags(4);
        drawSongNames();
    }
}

void MusicMenu::initScroll() {
    scrollMax = (songCount - 8) << 4;
    if (scrollMax < 0) {
        scrollMax = 0;
    }
    scrollToSong(playingSong);
}

void MusicMenu::setScrollPos(s32 v) {
    scrollY = v;
    Gfx2d_SetLayerOffset(4, 0, scrollY - 0x18);
    topRow = v >> 4;
    composeListScreen();
    setFlags(4);
}

void MusicMenu::composeListScreen() {
    s32 n = topRow;
    s32 i = (n + 9) % 9;
    s32 j = n & 0xf;
    s32 k;
    volatile u16 fill = 0x10;
    MIi_CpuClear16(fill, listScreen, 0x800);
    s32 z = 0;
    k = z;
    do {
        MIi_CpuCopy16(&rowTemplateScreen[i * 0x40], &listScreen[j * 0x40], 0x80);
        i++;
        if (i >= 9) {
            i = z;
        }
        j = (j + 1) & 0xf;
        k++;
    } while (k < 9);
    setFlags(8);
}

void MusicMenu::paintListRow(s32 idx, u32 col) {
    s32 z = 0;
    if (idx != -1) {
        s32 d = idx - topRow;
        if (d >= 0 && d < 9) {
            s32 y = (idx & 0xf) << 1;
            BgScreen_SetRectPalette(listScreen, z, y, 0x1f, y + 1, col);
        }
    }
}

void MusicMenu::uploadListScreen() {
    BgScreen_SetRectPalette(listScreen, 0, 0, 0x1f, 0x1f, 4);
    if (playingSong == selectedSong) {
        paintListRow(playingSong, 0xa);
    } else {
        paintListRow(playingSong, 9);
        paintListRow(selectedSong, 5);
    }
    if (((BgVramTask *)(screenTasks))->requestScreen(listScreen, 4, 0x800, 0)) {
        clearFlags(8);
    }
}

void MusicMenu::updateScrollAnimation() {
    s32 t = scrollTargetY;
    s32 c = scrollY;
    if (c != t) {
        if (c > t) {
            scrollY = scrollY - 6;
            t = scrollTargetY;
            if (scrollY < t) {
                scrollY = t;
            }
        } else {
            scrollY = scrollY + 6;
            t = scrollTargetY;
            if (scrollY > t) {
                scrollY = t;
            }
        }
        setScrollPos(scrollY);
        syncKnobToScroll();
    }
}

void MusicMenu::setPlayButtonTiles(u16 v) {
    s32 k, idx, j, i;
    for (k = 0x82, i = 4; i <= 7; k += 0x20, i++) {
        idx = k;
        for (j = 2; j <= 5; j++) {
            frameScreen[idx] = v;
            idx++;
            v = v + 1;
        }
    }
}

void MusicMenu::paintPlayButton(u32 a) {
    setFlags(2);
    BgScreen_SetRectPalette(frameScreen, 2, 4, 5, 7, a);
}

void MusicMenu::paintTakeOutButton(u32 a) {
    setFlags(2);
    BgScreen_SetRectPalette(frameScreen, 2, 0xf, 5, 0x10, a);
}

void MusicMenu::paintAddButton(u32 a) {
    setFlags(2);
    BgScreen_SetRectPalette(frameScreen, 2, 0xc, 5, 0xd, a);
}

void MusicMenu::refreshButtons() {
    if (selectedSong == -1) {
        paintTakeOutButton(7);
        if (playingSong == -1) {
            setPlayButtonTiles(0x59);
            paintPlayButton(7);
        } else {
            setPlayButtonTiles(0x69);
            paintPlayButton(8);
        }
    } else {
        paintTakeOutButton(6);
        if (playingSong == -1) {
            setPlayButtonTiles(0x59);
            paintPlayButton(6);
        } else {
            setPlayButtonTiles(0x69);
            paintPlayButton(8);
        }
    }
}

BOOL MusicMenu::selectSong(s32 v) {
    BOOL r;
    if (selectedSong == v) {
        r = FALSE;
    } else {
        r = TRUE;
    }
    selectedSong = v;
    setFlags(8);
    refreshButtons();
    return r;
}

BOOL MusicMenu::activateTarget(u32 a) {
    if (a <= 8) {
        if (selectSong(a + topRow)) {
            Snd_PlaySe(0x29);
        }
        return FALSE;
    }
    switch (a - 9) {
    case 0:
        startQuit();
        return TRUE;
    case 2:
        return playSelectedSong();
    case 3:
        return takeOutSong();
    case 4:
        startAddSongs();
        return TRUE;
    case 1:
        ((MenuScrollKnob *)(&scrollKnob))->grab();
        Menu_PlayScrollGrabSe();
        setMainState(4);
        return TRUE;
    }
    return FALSE;
}

u32 MusicMenu::hitTestTarget(s32 x, s32 y) {
    if (((MenuBottomButtonsBody *)(&bottomButtons))->isTouched(6)) {
        return 9;
    }
    if (x >= 0x10 && x <= 0x30 && y >= 0x20 && y <= 0x40) {
        return 0xb;
    }
    if (x >= 0x10 && x <= 0x30 && y >= 0x78 && y <= 0x88) {
        return 0xc;
    }
    if (x >= 0x10 && x <= 0x30 && y >= 0x60 && y <= 0x70) {
        return 0xd;
    }
    if (x >= 0x40 && x <= 0xc0 && y >= 0x18 && y < 0x98) {
        s32 t = (y - (0x18 - (scrollTargetY & 0xf))) >> 4;
        if (t < songCount) {
            return (u8)t;
        }
    }
    return 0xe;
}

void MusicMenu::targetButtonAtCursor() {
    s32 x = ((MenuCursorBase *)(&cursor))->getScreenY();
    if (x < 0x4c) {
        cursorSlot = 0xb;
    } else if (x < 0x74) {
        cursorSlot = 0xd;
    } else {
        cursorSlot = 0xc;
    }
}

BOOL MusicMenu::targetRowAtCursor() {
    s32 n = songCount;
    s32 x, r, t;
    if (n == 0) {
        return FALSE;
    }
    if (n > 9) {
        n = 9;
    }
    x = ((MenuCursorBase *)(&cursor))->getScreenY();
    if (x < 0x20) {
        x = 0x20;
    }
    if (x >= 0xa0) {
        x = 0x9f;
    }
    r = scrollTargetY & 0xf;
    t = (x - (0x20 - r)) >> 4;
    if (t >= n) {
        t = n - 1;
    }
    cursorSlot = t;
    if (r != 0) {
        if (t == 0) {
            scrollTargetY = scrollTargetY - r;
        } else if (t == n - 1) {
            cursorSlot = cursorSlot - 1;
            scrollTargetY = scrollTargetY + (0x10 - (scrollTargetY & 0xf));
        }
    }
    return TRUE;
}

void MusicMenu::targetRowOrRight() {
    if (!targetRowAtCursor()) {
        if (scrollMax > 0) {
            cursorSlot = 10;
        } else {
            cursorSlot = 9;
        }
    }
}

void MusicMenu::targetRowOrButton() {
    if (!targetRowAtCursor()) {
        targetButtonAtCursor();
    }
}

BOOL MusicMenu::moveCursorByPad(u32 pad) {
    u32 st = cursorSlot;
    if (pad == 0) {
        return FALSE;
    }
    if (st <= 8) {
        if (MenuKeys_HasLeft(pad)) {
            targetButtonAtCursor();
        } else if (MenuKeys_HasRight(pad)) {
            if (scrollMax > 0) {
                cursorSlot = 10;
            } else {
                cursorSlot = 9;
            }
        } else if (MenuKeys_HasUp(pad)) {
            if (cursorSlot != 0) {
                cursorSlot = *(volatile u8 *)&cursorSlot - 1;
                if (cursorSlot == 0) {
                    s32 r = scrollTargetY & 0xf;
                    if (r != 0) {
                        scrollTargetY = scrollTargetY - r;
                    }
                }
            } else {
                if (scrollTargetY >= 0x10) {
                    scrollTargetY = scrollTargetY - 0x10;
                    return TRUE;
                }
            }
        } else if (MenuKeys_HasDown(pad)) {
            s32 t = scrollMax;
            if (t == 0) {
                if (cursorSlot < songCount - 1) {
                    cursorSlot = *(volatile u8 *)&cursorSlot + 1;
                }
            } else if (cursorSlot < 7) {
                cursorSlot = *(volatile u8 *)&cursorSlot + 1;
            } else {
                s32 a0 = scrollTargetY;
                s32 r = a0 & 0xf;
                if (r != 0) {
                    scrollTargetY = scrollTargetY + (0x10 - r);
                    return TRUE;
                } else if (a0 <= t - 0x10) {
                    scrollTargetY = scrollTargetY + 0x10;
                    return TRUE;
                }
            }
        }
    }
    switch (cursorSlot) {
    case 9:
        if (MenuKeys_HasLeft(pad)) {
            targetRowOrButton();
        } else if (MenuKeys_HasUp(pad)) {
            if (scrollMax > 0) {
                cursorSlot = 10;
            }
        }
        break;
    case 10:
        if (MenuKeys_HasDown(pad)) {
            cursorSlot = 9;
        } else if (MenuKeys_HasLeft(pad)) {
            targetRowOrButton();
        }
        break;
    case 11:
        if (MenuKeys_HasDown(pad)) {
            cursorSlot = 13;
        } else if (MenuKeys_HasRight(pad)) {
            targetRowOrRight();
        }
        break;
    case 12:
        if (MenuKeys_HasUp(pad)) {
            cursorSlot = 13;
        } else if (MenuKeys_HasRight(pad)) {
            targetRowOrRight();
        }
        break;
    case 13:
        if (MenuKeys_HasUp(pad)) {
            cursorSlot = 11;
        } else if (MenuKeys_HasDown(pad)) {
            cursorSlot = 12;
        } else if (MenuKeys_HasRight(pad)) {
            targetRowOrRight();
        }
        break;
    }
    if (st != cursorSlot) {
        return TRUE;
    }
    return FALSE;
}

void MusicMenu::scrollToSong(s32 x) {
    x = x - 3;
    s32 m = songCount - 8;
    if (m < 0) {
        m = 0;
    }
    if (x < 0) {
        x = 0;
    } else if (x > m) {
        x = m;
    }
    setScrollPos(x << 4);
    scrollTargetY = scrollY;
    syncKnobToScroll();
}

BOOL MusicMenu::testFlags(u32 m) {
    if (flags & m) {
        return TRUE;
    }
    return FALSE;
}

void MusicMenu::setFlags(u32 m) { flags = flags | m; }

void MusicMenu::clearFlags(u32 m) { flags = flags & ~m; }

#undef C

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov144_02291f60) {
    HOST_OVERLAY_VAR(sMusicMenuProfile),
    HOST_OVERLAY_VAR(data_ov144_02293d70),
    HOST_OVERLAY_VARS_END
};
