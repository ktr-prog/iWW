#include "types.h"
#include "gfx/VecFx32.h"
#include "Unk_020d8c7c.h"
#include "net/CommManager.h"
#include "menu/MenuProc.h"
#include "ui/HandCursor.h"
#include "menu/MenuLauncher.h"
#include "ui/LabelString.h"
#include "gfx/BgVramTask.h"
#include "menu/MenuCursor.h"
#include "menu/MenuBottomButtons.h"
#include "sys/ProcProfile.h"
#include "nitro/gxoam.h"
#include "save/SaveData.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_0206d988.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0206f834.h"
#include "proto/main/unk_020720f8.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov002/unk_ov002_02202fac.h"
#include "proto/ov143/unk_ov143_02291f60.h"

class MelodyMenu;

class MelodyMenu;
typedef void (MelodyMenu::*Unk_ov143_02293b80_Fn)();











extern "C" {
extern u16 gPad[];
extern CommManager *gCommManager;

void SaveVillagers_ClearTuneRequester(void *a);
void MI_CpuCopy8(void *dst, void *src, s32 n);
}
extern SaveData gSaveData;


extern "C" ProcProfile sMelodyMenuProfile = {(void *(*)())MelodyMenu_Create, 0xb8, 0xbc};
extern "C" GXOamAttr data_ov143_02293980[2] = {{0x8188404a, 0xc0, 0, 0xc, 0x0}, {0x81a8404a, 0xc4, 0, 0xc, 0xffff}};
extern "C" GXOamAttr data_ov143_02293950[1] = {
    {0x01a000f0, 0xde, 0, 0xc, 0xffff},
};
extern "C" GXOamAttr data_ov143_022939e8[3] = {{0x419800cf, 0xc9, 0, 0xc, 0x0}, {0x1a880cf, 0xcb, 0, 0xc, 0x0}, {0x819a00df, 0x144, 0, 0xb, 0xffff}};
extern "C" GXOamAttr data_ov143_02293a00[3] = {{0x419800cf, 0xc9, 0, 0xc, 0x0}, {0x1a880cf, 0xcb, 0, 0xc, 0x0}, {0x819a00df, 0x144, 0, 0xb, 0xffff}};
extern "C" GXOamAttr data_ov143_02293af0[3] = {{0x419800e1, 0xcc, 0, 0xc, 0x0}, {0x1a880e1, 0xce, 0, 0xc, 0x0}, {0x819a00df, 0x14c, 0, 0xa, 0xffff}};
extern "C" GXOamAttr data_ov143_02293a18[3] = {{0x419800e1, 0xcf, 0, 0xc, 0x0}, {0x1a880e1, 0xd1, 0, 0xc, 0x0}, {0x819a00df, 0x150, 0, 0x9, 0xffff}};
extern "C" GXOamAttr data_ov143_02293a30[3] = {{0x419800e1, 0xd2, 0, 0xc, 0x0}, {0x1a880e1, 0xd4, 0, 0xc, 0x0}, {0x819a00df, 0x150, 0, 0x8, 0xffff}};
extern "C" GXOamAttr data_ov143_02293a48[3] = {{0x419800e1, 0xd5, 0, 0xc, 0x0}, {0x1a880e1, 0xd7, 0, 0xc, 0x0}, {0x819a00df, 0x150, 0, 0x7, 0xffff}};
extern "C" GXOamAttr data_ov143_02293a60[3] = {{0x419800e1, 0xd8, 0, 0xc, 0x0}, {0x1a880e1, 0xda, 0, 0xc, 0x0}, {0x819a00df, 0x150, 0, 0x6, 0xffff}};
extern "C" GXOamAttr data_ov143_02293a78[3] = {{0x419800e1, 0xdb, 0, 0xc, 0x0}, {0x1a880e1, 0xdd, 0, 0xc, 0x0}, {0x819a00df, 0x150, 0, 0x5, 0xffff}};
extern "C" GXOamAttr data_ov143_02293a90[3] = {{0x419800e1, 0x100, 0, 0xc, 0x0}, {0x1a880e1, 0x102, 0, 0xc, 0x0}, {0x819a00df, 0x150, 0, 0x4, 0xffff}};
extern "C" GXOamAttr data_ov143_02293aa8[3] = {{0x419800e1, 0x103, 0, 0xc, 0x0}, {0x1a880e1, 0x105, 0, 0xc, 0x0}, {0x819a00df, 0x154, 0, 0xb, 0xffff}};
extern "C" GXOamAttr data_ov143_02293ac0[3] = {{0x419800e1, 0x106, 0, 0xc, 0x0}, {0x1a880e1, 0x108, 0, 0xc, 0x0}, {0x819a00df, 0x154, 0, 0xa, 0xffff}};
extern "C" GXOamAttr data_ov143_02293ad8[3] = {{0x419800e1, 0x109, 0, 0xc, 0x0}, {0x1a880e1, 0x10b, 0, 0xc, 0x0}, {0x819a00df, 0x154, 0, 0x9, 0xffff}};
extern "C" GXOamAttr data_ov143_02293b08[3] = {{0x419800e1, 0x10c, 0, 0xc, 0x0}, {0x1a880e1, 0x10e, 0, 0xc, 0x0}, {0x819a00df, 0x154, 0, 0x8, 0xffff}};
extern "C" GXOamAttr data_ov143_02293b20[3] = {{0x419800e1, 0x10f, 0, 0xc, 0x0}, {0x1a880e1, 0x111, 0, 0xc, 0x0}, {0x819a00df, 0x154, 0, 0x7, 0xffff}};
extern "C" GXOamAttr data_ov143_022939a0[3] = {{0x419800e1, 0x112, 0, 0xc, 0x0}, {0x1a880e1, 0x114, 0, 0xc, 0x0}, {0x819a00df, 0x154, 0, 0x6, 0xffff}};
extern "C" GXOamAttr data_ov143_022939b8[3] = {{0x419800e1, 0x115, 0, 0xc, 0x0}, {0x1a880e1, 0x117, 0, 0xc, 0x0}, {0x819a00df, 0x154, 0, 0x5, 0xffff}};
extern "C" GXOamAttr data_ov143_022939d0[3] = {{0x419800e4, 0x118, 0, 0xc, 0x0}, {0x1a880e4, 0x11a, 0, 0xc, 0x0}, {0x819a00df, 0x158, 0, 0x4, 0xffff}};
extern "C" GXOamAttr data_ov143_022938c8[1] = {
    {0x81f000f0, 0x140, 0, 0xb, 0xffff},
};


class MelodyMenu : public MenuProc {
public:
    MelodyMenu() : cursor(), bottomButtons(), textLabels(), screenTasks() {}

    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onDraw();
    virtual BOOL execTransition();
    virtual BOOL execMain();
    virtual BOOL execPhase3();
    virtual BOOL execPhase4();
    virtual BOOL execClosed();

    void clearFlags(u32 mask);
    void setFlags(u32 mask);
    BOOL testFlags(u32 mask);
    void endDialogDim();
    void beginDialogDim();
    void getNotePos(s32 *out, s32 idx);
    void createNoteLabels();
    void createNoteLabel(u32 id, u32 idx);
    u32 noteFromLevel(u32 idx);
    u32 levelFromNote(u32 idx);
    void drawNotes(s32 x, s32 y);
    void drawHighlightedNote(u32 idx, s32 x, s32 y);
    void drawNote(u32 idx, s32 x, s32 y);
    void drawSelectedNote(u32 idx, s32 x, s32 y);
    void drawPlayingNote(u32 idx, s32 x, s32 y);
    void resetTextLabels();
    LabelString *allocTextLabel();
    void closeEraseAllDialog();
    void openEraseAllDialog();
    void endPlayback();
    void startPlayback();
    void paintEraseAllButton(u32 v);
    void paintPlayButton(u32 v);
    void flushBgScreen();
    BOOL moveCursorByPad(u32 pad);
    BOOL activateTarget(u32 idx);

    u32 hitTestTarget(s32 x, s32 y);
    void releaseCursor();
    void pressCursor();
    void refreshCursor();
    void moveCursorTo(s32 a, s32 b);
    void moveCursorToTarget();
    void hideCursor();
    s32 getCursorTargetY();
    s32 getCursorTargetX();
    void showCursor();
    BOOL isTuneSendDone();
    void sendTune();
    void startQuit();
    void confirmTune();
    void resumeConfirmInput();
    void startConfirmButtons();
    void startConfirmTouch();
    void resumeInput();
    void startButtonInput();
    void startTouchInput();
    void updatePlayback();
    void updateBarTransition();
    void cancelEraseAll();
    void confirmEraseAll();
    void updateConfirmButtons();
    void updateConfirmTouch();
    void updateCursorRelease();
    void updateCursorPress();
    void updateCursorMove();
    void updateNoteKeys();
    void updateButtons();
    void updateNoteDrag();
    void updateTouch();

    void loadObjGfx();
    void loadBgGfx();
    void setupBgLayers();
    void postStateUpdate();
    void preStateUpdate();
    void postInputUpdate();
    void preInputUpdate();
    void releaseResources();
    void initMelody();
    void stateDialogBack();
    void stateDialogClose();
    void stateDialog();
    void stateDialogOpen();
    void updateLayerSlide();
    void stateClosing();
    void stateClose();
    void stateOpening();
    void stateOpen();
    void runMainState();

    /* 0x91 */ u8 unk_91[3];
    /* 0x94 */ s32 slideY;
    /* 0x98 */ u16 flags;
    /* 0x9a */ s16 activeNote;
    /* 0x9c */ s16 sendSeq;
    /* 0x9e */ u8 returnState;
    /* 0x9f */ volatile u8 labelCount;
    /* 0xa0 */ u8 *notes;
    /* 0xa4 */ volatile u8 cursorSlot;
    /* 0xa5 */ u8 dragStartLevel;
    /* 0xa6 */ u8 unk_a6[2];
    /* 0xa8 */ s32 dragStartY;
    /* 0xac */ MenuCursorBuf0 cursor;
    /* 0x110 */ MenuBottomButtons bottomButtons;
    /* 0x274 */ LabelString textLabels[16];
    /* 0x674 */ u16 bgScreen[0x400];
    /* 0xe74 */ BgVramTask screenTasks[1];
};

static inline BOOL Unk_ov143_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) return TRUE;
    return FALSE;
}

extern "C" MelodyMenu *MelodyMenu_Create() { return new MelodyMenu(); }

BOOL MelodyMenu::onCreate() {
    initMelody();
    transitionState = 0;
    setPhase(0);
    return TRUE;
}

BOOL MelodyMenu::onDelete() {
    ((MenuLauncher *)ProcBase_GetParent(this))->onChildClosed();
    releaseResources();
    return TRUE;
}

BOOL MelodyMenu::onDraw() {
    if (MenuCtrl_IsButtons()) {
        cursor.drawWrapped();
    }
    if (!testFlags(1)) return FALSE;
    bottomButtons.drawAt(getSlideOffsetY());
    s32 y = slideY + 0x60;
    Oam_DrawCell(1, data_ov143_02293980, 0x80, y, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    drawNotes(0x80, y);
    return TRUE;
}

BOOL MelodyMenu::execTransition() {
    static Unk_ov143_02293b80_Fn tbl[8] = {
        &MelodyMenu::stateOpen, &MelodyMenu::stateOpening,
        &MelodyMenu::stateClose, &MelodyMenu::stateClosing,
        &MelodyMenu::stateDialogOpen, &MelodyMenu::stateDialog,
        &MelodyMenu::stateDialogClose, &MelodyMenu::stateDialogBack};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}

void MelodyMenu::runMainState() {
    static Unk_ov143_02293b80_Fn tbl[11] = {
        &MelodyMenu::updateTouch, &MelodyMenu::updateNoteDrag,
        &MelodyMenu::updateButtons, &MelodyMenu::updateNoteKeys,
        &MelodyMenu::updateCursorMove, &MelodyMenu::updateCursorPress,
        &MelodyMenu::updateCursorRelease, &MelodyMenu::updateConfirmTouch,
        &MelodyMenu::updateConfirmButtons, &MelodyMenu::updateBarTransition,
        &MelodyMenu::updatePlayback};
    (this->*tbl[mainState])();
}

BOOL MelodyMenu::execMain() {
    preInputUpdate();
    runMainState();
    postInputUpdate();
    return TRUE;
}

BOOL MelodyMenu::execPhase3() { return TRUE; }

BOOL MelodyMenu::execPhase4() { return TRUE; }

BOOL MelodyMenu::execClosed() {
    if (isTuneSendDone() == 0) return TRUE;
    ProcBase_RequestDelete(this);
    return TRUE;
}

void MelodyMenu::stateOpen() {
    setupBgLayers();
    loadBgGfx();
    loadObjGfx();
    createNoteLabels();
    beginSubSlideIn(10, 4, 0, 0x18);
    Gfx2d_ShowLayer(6);
    Gfx2d_ShowLayer(4);
    updateLayerSlide();
    setFlags(1);
    bottomButtons.setLayoutConfirmQuit03();
    setTransitionState(1);
}

void MelodyMenu::stateOpening() {
    if (stepSlideIn(0)) {
        setPhase(2);
        resumeInput();
    }
    updateLayerSlide();
}

void MelodyMenu::stateClose() {
    ((MenuLauncher *)ProcBase_GetParent(this))->setNextRequest(0x44, 1);
    beginSubSlideOut(10, 0, 0, 0x18);
    updateLayerSlide();
    setTransitionState(3);
}

void MelodyMenu::stateClosing() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(6);
        Gfx2d_ResetLayer(4);
        setPhase(5);
    } else {
        updateLayerSlide();
    }
}

void MelodyMenu::updateLayerSlide() {
    applySlideOffset(6, 0, 0);
    applySlideOffset(4, 0, 0);
    slideY = getSlideOffsetY();
}

void MelodyMenu::stateDialogOpen() {
    if (stepSlideOut(-1)) {
        setTransitionState(5);
        initSlideIn(0, 0);
        ((MenuBottomButtonsBody *)&bottomButtons)->setLayoutYesNo0D(0x8d);
        beginDialogDim();
    }
}

void MelodyMenu::stateDialog() {
    if (stepSlideIn(-1)) {
        resumeConfirmInput();
        setPhase(2);
    }
}

void MelodyMenu::stateDialogClose() {
    if (stepSlideOut(-1)) {
        setTransitionState(7);
        initSlideIn(0, 0);
        bottomButtons.setLayoutConfirmQuit03();
    }
}

void MelodyMenu::stateDialogBack() {
    if (stepSlideIn(-1)) {
        resumeInput();
        setPhase(2);
    }
}

void MelodyMenu::initMelody() {
    flags = 0;
    notes = gMelodyEditPattern;
    Melody_Unpack((u32 *)&gSaveData.townTune, notes);
    data_ov143_02293a00[2].charNo = data_ov143_022939e8[2].charNo + 4;
    activeNote = -1;
    cursorSlot = 0;
}

void MelodyMenu::releaseResources() {
    screenTasks[0].cancel();
    resetTextLabels();
    bottomButtons.freeTexts();
}

void MelodyMenu::preInputUpdate() {
    preStateUpdate();
    cursor.update();
}

void MelodyMenu::postInputUpdate() { postStateUpdate(); }

void MelodyMenu::preStateUpdate() {
    screenTasks[0].cancel();
    resetTextLabels();
    bottomButtons.freeTexts();
}

void MelodyMenu::postStateUpdate() { flushBgScreen(); }

void MelodyMenu::setupBgLayers() {
    Gfx2d_SetSubBgModeState(0);
    Gfx2d_SetLayerPriority(6, 2);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
    Gfx2d_SetLayerPriority(4, 2);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
}

void MelodyMenu::loadBgGfx() {
    void *h = gCurrentHeap;
    Gfx2d_LoadCharFile("menu/melody/bg0.bch", h, 6, 0x11, 0x11, 0x9c);
    Gfx2d_LoadPaletteFile("menu/melody/bg.bpl", h, 6, 1, 1, 6);
    Gfx2d_LoadScreenFile("menu/melody/a_bg.bsc", h, 6);
    File_LoadToBuffer("menu/melody/b_bg.bsc", bgScreen, 0x800);
    Gfx2d_LoadScreen((u8 *)bgScreen, 4, 0x800, 0);
}

void MelodyMenu::loadObjGfx() {
    MenuButtons_LoadTextColors();
    void *h = gCurrentHeap;
    Gfx2d_LoadCharFile("menu/melody/obj.bch", h, 8, 0xc0, 0xc0, 0xff);
    Gfx2d_LoadCharFile("menu/melody/obj2.bch", h, 8, 0x140, 0x140, 0x1bf);
    Gfx2d_LoadPaletteFile("menu/melody/obj.bpl", h, 8, 4, 4, 0xd);
}

void MelodyMenu::updateTouch() {
    u32 r;
    if (checkSwitchToButtons(1) != 0) {
        startButtonInput();
        return;
    }
    if (Unk_ov143_Both()) {
        r = hitTestTarget(gTouchCurX, gTouchCurY);
        if (r != 0x16) {
            activateTarget(r);
        } else if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(1) != 0) {
            confirmTune();
        } else if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(2) != 0) {
            startQuit();
        }
    }
}

void MelodyMenu::updateNoteDrag() {
    s32 v;
    u32 idx;
    u32 cur, nw;
    if (gTouchHeld == 0) {
        resumeInput();
        return;
    }
    v = dragStartLevel + (dragStartY - gTouchCurY) / 3;
    if (v < 0) v = 0;
    else if (v > 0xf) v = 0xf;
    idx = cursorSlot;
    cur = notes[idx];
    nw = noteFromLevel((u8)v);
    if (cur != nw) {
        Melody_PlayNote(nw);
        notes[idx] = nw;
    }
}

void MelodyMenu::updateButtons() {
    u32 k;
    if (checkSwitchToTouch() != 0) {
        startTouchInput();
        return;
    }
    if (moveCursorByPad(takeRepeatedKeys()) != 0) {
        moveCursorToTarget();
        return;
    }
    k = gPad[1];
    if (k & 1) {
        pressCursor();
    } else if (k & 2) {
        hideCursor();
        startQuit();
    } else if (k & 8) {
        hideCursor();
        confirmTune();
    }
}

void MelodyMenu::updateNoteKeys() {
    if ((gPad[0] & 1) != 0) {
        u32 t = takeRepeatedKeys();
        if (t != 0) {
            u32 idx = cursorSlot;
            u32 n = levelFromNote(notes[idx]);
            u32 old = n;
            if (MenuKeys_HasUp(t) != 0) {
                if (n < 0xf) n = (u8)(n + 1);
            } else if (MenuKeys_HasDown(t) != 0) {
                if (n != 0) n = (u8)(n - 1);
            }
            if (n != old) {
                s32 a, b;
                notes[idx] = noteFromLevel(n);
                Melody_PlayNote(notes[idx]);
                a = getCursorTargetX();
                b = getCursorTargetY();
                cursor.warpTo(a, b);
            }
        }
    } else {
        resumeInput();
        releaseCursor();
    }
}

void MelodyMenu::updateCursorMove() {
    if (cursor.isMoving() == 0) {
        setMainState(returnState);
        runMainState();
    }
}

void MelodyMenu::updateCursorPress() {
    if (cursor.isAnimDone() != 0) {
        if (activateTarget(cursorSlot) == 0) {
            setMainState(2);
            releaseCursor();
        }
    }
}

void MelodyMenu::updateCursorRelease() {
    if (cursor.isAnimDone() != 0) {
        refreshCursor();
        setMainState(returnState);
    }
}

void MelodyMenu::updateConfirmTouch() {
    if (checkSwitchToButtons(1) != 0) {
        startConfirmButtons();
        return;
    }
    if (Unk_ov143_Both()) {
        if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(3) != 0) {
            confirmEraseAll();
        } else if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(4) != 0) {
            cancelEraseAll();
        }
    }
}

void MelodyMenu::updateConfirmButtons() {
    u32 old;
    u32 k;
    if (checkSwitchToTouch() != 0) {
        startConfirmTouch();
        return;
    }
    old = cursorSlot;
    takeRepeatedKeys();
    if (isRepeatLeft() != 0) {
        cursorSlot = 0x14;
    } else if (isRepeatRight() != 0) {
        cursorSlot = 0x15;
    }
    if (old != cursorSlot) {
        moveCursorToTarget();
        return;
    }
    k = gPad[1];
    if (k & 1) {
        pressCursor();
    } else if (k & 2) {
        hideCursor();
        cancelEraseAll();
    } else if (k & 8) {
        hideCursor();
        confirmEraseAll();
    }
}

void MelodyMenu::confirmEraseAll() {
    s32 i;
    closeEraseAllDialog();
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(3);
    Snd_PlaySe(0x5a);
    i = 0;
    do {
        notes[i] = 0xf;
        i++;
    } while (i < 16);
}

void MelodyMenu::cancelEraseAll() {
    closeEraseAllDialog();
    Snd_PlaySe(0x2a);
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(4);
}

void MelodyMenu::updateBarTransition() {
    if (((MenuBottomButtonsBody *)&bottomButtons)->stepPress() != 0) {
        if (cursor.getAnim() != 0) {
            s32 a = ((MenuBottomButtonsBody *)&bottomButtons)->getPressOffset();
            s32 b = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(-1);
            s32 c = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(-1);
            cursor.warpTo(a + (b - 6), a + c);
        }
    } else {
        hideCursor();
        setPhase(1);
    }
}

void MelodyMenu::updatePlayback() {
    s32 v = data_020ddf8c;
    if (v == -1 || v >= 0x10) {
        if (testFlags(8) == 0) {
            endPlayback();
        }
    } else {
        clearFlags(8);
        activeNote = v;
    }
}

void MelodyMenu::startTouchInput() {
    hideCursor();
    setMainState(0);
}

void MelodyMenu::startButtonInput() {
    showCursor();
    restartKeyRepeat();
    setMainState(2);
}

void MelodyMenu::resumeInput() {
    if (MenuCtrl_IsTouch() != 0) {
        startTouchInput();
    } else {
        startButtonInput();
    }
}

void MelodyMenu::startConfirmTouch() {
    hideCursor();
    setMainState(7);
}

void MelodyMenu::startConfirmButtons() {
    cursorSlot = 0x15;
    showCursor();
    restartKeyRepeat();
    setMainState(8);
}

void MelodyMenu::resumeConfirmInput() {
    if (MenuCtrl_IsTouch() != 0) {
        startConfirmTouch();
    } else {
        startConfirmButtons();
    }
}

void MelodyMenu::confirmTune() {
    MenuCtrl_SetResult(1);
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(1);
    setTransitionState(2);
    setMainState(9);
    Melody_Pack((u32 *)&gSaveData.townTune, notes);
    Melody_ApplyEditPattern();
    SaveVillagers_ClearTuneRequester(gSaveData.villagers);
    sendTune();
}

void MelodyMenu::startQuit() {
    MenuCtrl_SetResult(0);
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(2);
    setTransitionState(2);
    setMainState(9);
}

void MelodyMenu::sendTune() {
    u8 buf[0x11];
    if (gCommManager->isOnline() != 0) {
        CommManager *g;
        buf[0] = 0xc;
        MI_CpuCopy8(notes, buf + 1, 0x10);
        g = gCommManager;
        g->beginRecord();
        g->writeRecord(buf, 0x11);
        g->endRecord(0x16, 4);
        sendSeq = g->getSendSeq();
    }
}

BOOL MelodyMenu::isTuneSendDone() {
    if (MenuCtrl_IsResultOk() == 0) return TRUE;
    if (gCommManager->isOnline() != 0) {
        if (Comm_IsSeqConfirmed(sendSeq) == 0) return FALSE;
    }
    return TRUE;
}

void MelodyMenu::showCursor() {
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    cursor.warpTo(a, b);
    ((MenuCursor *)&cursor)->setAnimIfChanged(1);
    refreshCursor();
}

s32 MelodyMenu::getCursorTargetX() {
    VecFx32 v;
    u32 t = cursorSlot;
    if (t <= 0xf) {
        getNotePos(&v.x, t);
        return v.x + 0xa;
    }
    switch (t - 0x10) {
    case 0:
        return 0x2e;
    case 1:
        return 0x94;
    case 2:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(1) - 6;
    case 3:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(2) - 6;
    case 4:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(3);
    case 5:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(4);
    }
    return 0x80;
}

s32 MelodyMenu::getCursorTargetY() {
    VecFx32 v;
    u32 t = cursorSlot;
    if (t <= 0xf) {
        getNotePos(&v.x, t);
        return v.y + 3;
    }
    switch (t - 0x10) {
    case 0:
        return 0xa0;
    case 1:
        return 0xa0;
    case 2:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(1);
    case 3:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(2);
    case 4:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(3);
    case 5:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(4);
    }
    return 0x60;
}

void MelodyMenu::hideCursor() {
    ((MenuCursor *)&cursor)->setAnimIfChanged(0);
    cursor.update();
}

void MelodyMenu::moveCursorToTarget() {
    s32 a, b;
    switch (cursorSlot) {
    case 0x12:
    case 0x13:
        ((MenuCursor *)&cursor)->switchToAnim07();
        break;
    default:
        ((MenuCursor *)&cursor)->switchToAnim01();
        break;
    }
    a = getCursorTargetX();
    b = getCursorTargetY();
    moveCursorTo(a, b);
}

void MelodyMenu::moveCursorTo(s32 a, s32 b) {
    cursor.moveToEase(a, b, 3, 1);
    returnState = mainState;
    setMainState(4);
}

void MelodyMenu::refreshCursor() {
    cursor.setPoseIdle();
    cursor.update();
}

void MelodyMenu::pressCursor() {
    ((MenuCursor *)&cursor)->setPosePress();
    setMainState(5);
}

void MelodyMenu::releaseCursor() {
    cursor.setPoseRelease();
    returnState = mainState;
    setMainState(6);
}

u32 MelodyMenu::hitTestTarget(s32 x, s32 y) {
    VecFx32 v;
    s32 i;
    for (i = 0; i < 16; i++) {
        getNotePos(&v.x, i);
        if (v.x <= x && v.x + 0x14 > x && v.y <= y && v.y + 0x12 > y) {
            return (u8)i;
        }
    }
    if (x >= 0 && x < 0x38 && y >= 0x90 && y < 0xac) return 0x10;
    if (x >= 0x60 && x < 0xb0 && y >= 0x90 && y < 0xb8) return 0x11;
    return 0x16;
}

BOOL MelodyMenu::activateTarget(u32 idx) {
    if (idx <= 0xf) {
        activeNote = idx;
        cursorSlot = idx;
        if (MenuCtrl_IsTouch()) {
            dragStartY = gTouchCurY;
            dragStartLevel = levelFromNote(notes[idx]);
            setMainState(1);
        } else {
            setMainState(3);
        }
        Melody_PlayNote(notes[idx]);
        return TRUE;
    }
    switch (idx) {
    case 0x10:
        openEraseAllDialog();
        Snd_PlaySe(0x2a);
        return TRUE;
    case 0x11:
        startPlayback();
        return TRUE;
    case 0x12:
        confirmTune();
        return TRUE;
    case 0x13:
        startQuit();
        return TRUE;
    case 0x14:
        confirmEraseAll();
        return TRUE;
    case 0x15:
        cancelEraseAll();
        return TRUE;
    }
    return FALSE;
}

BOOL MelodyMenu::moveCursorByPad(u32 pad) {
    if (pad == NULL) return FALSE;
    u32 cur = cursorSlot;
    if (cur < 8) {
        if (MenuKeys_HasDown(pad)) {
            cursorSlot = cursorSlot + 8;
        } else if (MenuKeys_HasLeft(pad)) {
            if (cursorSlot != 0) cursorSlot = cursorSlot - 1;
        } else if (MenuKeys_HasRight(pad)) {
            cursorSlot = cursorSlot + 1;
        }
    } else if (cur >= 8 && cur <= 0xf) {
        if (MenuKeys_HasDown(pad)) {
            s32 t = cursorSlot - 8;
            if (t < 2) {
                cursorSlot = 0x10;
            } else if (t < 6) {
                cursorSlot = 0x11;
            } else {
                cursorSlot = 0x12;
            }
        } else if (MenuKeys_HasUp(pad)) {
            cursorSlot = cursorSlot - 8;
        } else if (MenuKeys_HasLeft(pad)) {
            cursorSlot = cursorSlot - 1;
        } else if (MenuKeys_HasRight(pad)) {
            if (cursorSlot < 0xf) cursorSlot = cursorSlot + 1;
        }
    } else {
        switch (cur) {
        case 0x10:
            if (MenuKeys_HasUp(pad)) {
                cursorSlot = 8;
            } else if (MenuKeys_HasRight(pad)) {
                cursorSlot = 0x11;
            }
            break;
        case 0x11:
            if (MenuKeys_HasUp(pad)) {
                cursorSlot = 0xb;
            } else if (MenuKeys_HasRight(pad)) {
                cursorSlot = 0x12;
            } else if (MenuKeys_HasLeft(pad)) {
                cursorSlot = 0x10;
            }
            break;
        case 0x12:
            if (MenuKeys_HasUp(pad)) {
                cursorSlot = 0xe;
            } else if (MenuKeys_HasDown(pad)) {
                cursorSlot = 0x13;
            } else if (MenuKeys_HasLeft(pad)) {
                cursorSlot = 0x11;
            }
            break;
        case 0x13:
            if (MenuKeys_HasUp(pad)) {
                cursorSlot = 0x12;
            } else if (MenuKeys_HasLeft(pad)) {
                cursorSlot = 0x11;
            }
            break;
        }
    }
    if (cur != cursorSlot) return TRUE;
    return FALSE;
}

void MelodyMenu::flushBgScreen() {
    if (testFlags(4)) {
        if (screenTasks[0].requestScreen(bgScreen, 4, 0x800, 0)) {
            clearFlags(4);
        }
    }
}

void MelodyMenu::paintPlayButton(u32 v) {
    setFlags(4);
    BgScreen_SetRectPalette(bgScreen, 0xc, 0x12, 0x15, 0x16, v);
}

void MelodyMenu::paintEraseAllButton(u32 v) {
    setFlags(4);
    BgScreen_SetRectPalette(bgScreen, 0, 0x11, 9, 0x17, v);
}

void MelodyMenu::startPlayback() {
    Melody_PlayEditPattern(0x190);
    activeNote = -1;
    setMainState(0xa);
    setFlags(2);
    setFlags(8);
    paintPlayButton(4);
    hideCursor();
}

void MelodyMenu::endPlayback() {
    clearFlags(2);
    activeNote = -1;
    resumeInput();
    paintPlayButton(3);
}

void MelodyMenu::openEraseAllDialog() {
    paintEraseAllButton(6);
    hideCursor();
    setTransitionState(4);
    setPhase(1);
    initSlideOut(0, 0);
}

void MelodyMenu::closeEraseAllDialog() {
    cursorSlot = 0x10;
    setMainState(9);
    initSlideOut(0, 0);
    setTransitionState(6);
    paintEraseAllButton(5);
    endDialogDim();
}

LabelString *MelodyMenu::allocTextLabel() {
    if (labelCount >= 0x10) {
        return &textLabels[15];
    }
    labelCount = labelCount + 1;
    return &textLabels[labelCount - 1];
}

void MelodyMenu::resetTextLabels() {
    s32 i;
    labelCount = 0;
    for (i = 0; i < 16; i++) {
        textLabels[i].destroyLabel();
    }
}

void MelodyMenu::drawPlayingNote(u32 idx, s32 x, s32 y) {
    GXOamAttr *e = sMelodyNoteSprites[idx];
    u32 t = levelFromNote(idx);
    s32 ym = y - t * 2;
    if (idx == 0xf) {
        Oam_DrawObjRotated(1, data_ov143_022938c8, x - 0x5c, ym - 0x18, -1, 2, 0x1000, 0xeaab, 0);
    } else {
        u32 n = e[2].cParam;
        GXOamAttr *p;
        if (idx < 6 || idx == 0xe) {
            p = &data_ov143_022939e8[2];
        } else {
            p = &data_ov143_02293a00[2];
        }
        Oam_DrawCell(1, p, x, ym, n, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    }
}

void MelodyMenu::drawSelectedNote(u32 idx, s32 x, s32 y) {
    GXOamAttr *e = sMelodyNoteSprites[idx];
    s32 ty;
    u32 t = levelFromNote(idx);
    ty = y - t * 2;
    Oam_DrawObj(1, e, x, ty, 0xd, 2, 0);
    Oam_DrawObj(1, e + 1, x, ty, 0xd, 2, 0);
    Oam_DrawCell(1, e + 2, x, ty, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
}

void MelodyMenu::drawNote(u32 idx, s32 x, s32 y) {
    u32 t = levelFromNote(idx);
    y -= t * 2;
    Oam_DrawCell(1, sMelodyNoteSprites[idx], x, y, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
}

void MelodyMenu::drawHighlightedNote(u32 idx, s32 x, s32 y) {
    if (testFlags(2)) {
        drawPlayingNote(notes[idx], x, y);
    } else {
        drawSelectedNote(notes[idx], x, y);
    }
    Oam_DrawObj(1, data_ov143_02293950, x, y, -1, -1, 0);
}

void MelodyMenu::drawNotes(s32 x, s32 y) {
    s32 i;
    s32 cx = x;
    for (i = 0; i < 8; i++) {
        if (i == activeNote) {
            drawHighlightedNote(i, cx, y);
        } else {
            drawNote(notes[i], cx, y);
        }
        cx += 0x18;
    }
    x += 0x10;
    for (; i < 16; i++) {
        if (i == activeNote) {
            drawHighlightedNote(i, x, y + 0x38);
        } else {
            drawNote(notes[i], x, y + 0x38);
        }
        x += 0x18;
    }
}

extern "C" GXOamAttr *sMelodyNoteSprites[16] = {data_ov143_02293a18, data_ov143_02293a30, data_ov143_02293a48, data_ov143_02293a60, data_ov143_02293a78, data_ov143_02293a90, data_ov143_02293aa8, data_ov143_02293ac0, data_ov143_02293ad8, data_ov143_02293b08, data_ov143_02293b20, data_ov143_022939a0, data_ov143_022939b8, data_ov143_022939d0, data_ov143_02293af0, data_ov143_022939e8};

u32 MelodyMenu::levelFromNote(u32 idx) {
    u8 t[16] = {2, 3, 4, 5, 6, 7, 8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 1, 0};
    return t[idx];
}

u32 MelodyMenu::noteFromLevel(u32 idx) {
    u8 t[16] = {0xf, 0xe, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xa, 0xb, 0xc, 0xd};
    return t[idx];
}

void MelodyMenu::createNoteLabel(u32 id, u32 idx) {
    GXOamAttr *p = sMelodyNoteSprites[idx];
    LabelString *e = allocTextLabel();
    String_Load2dMenu(e, id);
    e->createLabel(8, p[0].charNo, 3, 0xf, 0, 0);
    e->redrawAligned(1, 0);
}

void MelodyMenu::createNoteLabels() {
    s32 j;
    u32 i;
    i = 0xc7;
    j = 0;
    do {
        createNoteLabel(i, j);
        i = (u8)(i + 1);
        if (i > 0xc9) i = 0xc3;
        j++;
    } while (j < 0xd);
    createNoteLabel(0xca, 0xd);
    createNoteLabel(0xcb, 0xe);
    LabelString *e = allocTextLabel();
    String_Load2dMenu(e, 0x8d);
    e->createLabel(8, data_ov143_02293980[0].charNo, 8, 0xf, 0, 0);
    e->redrawAligned(1, 0);
}

void MelodyMenu::getNotePos(s32 *out, s32 idx) {
    s32 x = 0x1a;
    s32 y = 0x3f;
    u32 t = levelFromNote(notes[idx]);
    if (idx < 8) {
        x += idx * 0x18;
        y -= t * 2;
    } else {
        x += (idx - 8) * 0x18 + 0x10;
        y += 0x38 - t * 2;
    }
    out[0] = x;
    out[1] = y;
}

void MelodyMenu::beginDialogDim() {
    Gfx2d_BeginSubObjWinBrightness();
    Gfx2d_SetSubBrightness(-6);
    ((MenuBottomButtonsBody *)&bottomButtons)->enableObjWindow();
}

void MelodyMenu::endDialogDim() {
    Gfx2d_EndSubObjWinBrightness();
    ((MenuBottomButtonsBody *)&bottomButtons)->disableObjWindow();
}

BOOL MelodyMenu::testFlags(u32 mask) {
    if (flags & mask) return TRUE;
    return FALSE;
}

void MelodyMenu::setFlags(u32 mask) {
    flags = flags | mask;
}


void MelodyMenu::clearFlags(u32 mask) {
    flags = flags & ~mask;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov143_02291f60) {
    HOST_OVERLAY_VAR(sMelodyMenuProfile),
    HOST_OVERLAY_VAR(data_ov143_02293980),
    HOST_OVERLAY_VAR(data_ov143_02293950),
    HOST_OVERLAY_VAR(data_ov143_022939e8),
    HOST_OVERLAY_VAR(data_ov143_02293a00),
    HOST_OVERLAY_VAR(data_ov143_02293af0),
    HOST_OVERLAY_VAR(data_ov143_02293a18),
    HOST_OVERLAY_VAR(data_ov143_02293a30),
    HOST_OVERLAY_VAR(data_ov143_02293a48),
    HOST_OVERLAY_VAR(data_ov143_02293a60),
    HOST_OVERLAY_VAR(data_ov143_02293a78),
    HOST_OVERLAY_VAR(data_ov143_02293a90),
    HOST_OVERLAY_VAR(data_ov143_02293aa8),
    HOST_OVERLAY_VAR(data_ov143_02293ac0),
    HOST_OVERLAY_VAR(data_ov143_02293ad8),
    HOST_OVERLAY_VAR(data_ov143_02293b08),
    HOST_OVERLAY_VAR(data_ov143_02293b20),
    HOST_OVERLAY_VAR(data_ov143_022939a0),
    HOST_OVERLAY_VAR(data_ov143_022939b8),
    HOST_OVERLAY_VAR(data_ov143_022939d0),
    HOST_OVERLAY_VAR(data_ov143_022938c8),
    HOST_OVERLAY_VAR(sMelodyNoteSprites),
    HOST_OVERLAY_VARS_END
};
