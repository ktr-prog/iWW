#include "types.h"
#include "host_tick.h"
#include "host_labels.h"
#include "host_shared_calls.h"
#include "Unk_020d8c7c.h"
#include "menu/MenuProc.h"
#include "ui/HandCursor.h"
#include "item/ItemName.h"
#include "ui/LabelString.h"
#include "gfx/BgVramTask.h"
#include "talk/EncodedString41.h"
#include "menu/MenuCursor.h"
#include "menu/GeneralMenuHeader.h"
#include "menu/MenuBottomButtons.h"
#include "menu/Keyboard.h"
#include "menu/MenuErrorMessage.h"
#include "sys/ProcProfile.h"
#include "menu/MenuLauncher.h"
#include "menu/MenuTabBar.h"
#include "net/CommManager.h"
#include "player/PlayerData.h"
#include "player/PlayerId.h"
#include "save/BlancaFaceRecord.h"
#include "save/Pattern.h"
#include "talk/EncodedString.h"
#include "talk/MsgString.h"
#include "net/FriendEntry.h"
#include "nitro/gxoam.h"
#include "text/Unk_02050288.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e9a08.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_020501d4.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02051218.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0206f834.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020afeb4.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov002/unk_ov002_02202fac.h"
#include "proto/ov095/unk_02292360.h"
#include "proto/ov124/unk_ov124_02296840.h"
#include "proto/ov126/unk_02297060.h"


extern "C" {
extern u16 gPad[];
#define gSaveBlancaFace HOST_LABEL(BlancaFaceRecord *, gSaveBlancaFace)
#define gSaveTownId HOST_LABEL(u16 (*)[], gSaveTownId)
#define gSavePlayers HOST_LABEL(u8 (*)[], gSavePlayers)
extern u8 gU8None;
extern CommManager *gCommManager;

BOOL EncodedString_SetRaw(EncodedString *buf, const void *src, s32 len);
void *FriendList_GetEntries(void *list);
}

static inline BOOL Unk_ov126_02298c4c_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        return TRUE;
    }
    return FALSE;
}

class NameEntryMenu;
typedef void (NameEntryMenu::*Unk_ov126_02299ae8_Fn)();

class NameEntryMenu;

class NameEntryMenu : public MenuProc {
public:
    NameEntryMenu()
        : header(), keyboard(), bottomButtons(), cursor(), suffixLabel(), censorString(), encodedText(), errorMessage() {}
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
    void censorText();
    void commitEntry();
    void storeFriendField2();
    void storeFriendField1();
    void storeStatsPatternName();
    void storeConstellationName();
    void storeTownName();
    void storePlayerName();
    void checkPasswordAnswer();
    void checkItemNameAnswer();
    void checkGeneralAnswer();
    void storeDesignName();
    void loadInitialText();
    void loadFriendField2();
    void loadFriendField1();
    u8 * getFriendEntry();
    void loadConstellationName();
    void loadDesignName();
    BOOL tryStartConfirm();
    BOOL tryCopyButton();
    BOOL tryPasteButton();
    BOOL tryBackspaceButton();
    BOOL tryPressKey();
    void refreshCursor();
    void releaseCursor();
    void pressCursor();
    void snapCursor();
    void moveCursorToTarget();
    void hideCursor();
    void showCursor();
    void setupDialogButtons();
    BOOL touchDialogButtons();
    void playErrorSe();
    void highlightSelection();
    void redrawText();
    BOOL insertChar(u32 x);
    BOOL insertCharRaw(u32 x);
    BOOL backspace(s32 x);
    BOOL applyModifierKey(s32 x);
    s32 pressKeyCode(s32 x);
    s32 touchKey();
    void paste();
    void copy();
    void extendSelection();
    void startSelection();
    void deleteSelection();
    void clearSelection();
    BOOL hasSelection();
    s32 navigateText(s32 a);
    BOOL touchTextField();
    void setCursorFromTouchX(s32 v);
    void updateCaretX();
    u32 getCharBeforeCursor();
    void setCursorIndex(u32 v);
    void resetTextCursor();
    void refreshKeys();
    BOOL onBackspaceEmpty();
    BOOL confirm();
    void closeWithResult(s32 a);
    void enterDialogInput();
    void enterDialogButtons();
    void enterDialogTouch();
    void showMessage(u32 v, u32 w);
    void resumeInput();
    void startButtonInput();
    void startTouchInput();
    void mainAct10();
    void mainAct0F();
    void mainAct0E();
    void mainAct0D();
    void mainAct0C();
    void mainAct0B();
    void mainAct0A();
    void mainAct09();
    void mainAct08();
    void mainAct07();
    void leaveTextToKeys();
    void mainAct06();
    void mainAct05();
    void mainAct04();
    void mainAct03();
    void mainAct02();
    void mainAct01();
    void mainAct00();
    void loadObjGfx();
    void loadBg();
    void setupBgLayers();
    void postStateUpdate();
    void preStateUpdate();
    void postInputUpdate();
    void preInputUpdate();
    void releaseResources();
    void init();
    void updateBgScroll();
    void transitionAct0B();
    void transitionAct0A();
    void transitionAct09();
    void transitionAct08();
    void transitionAct07();
    void transitionAct06();
    void transitionAct05();
    void transitionAct04();
    void transitionAct03();
    void transitionAct02();
    void transitionAct01();
    void transitionAct00();
    void runMainState();

    /* 0x091 */ u8 unk_91[3];
    /* 0x094 */ u32 slideY;
    /* 0x098 */ s32 caretX;
    /* 0x09c */ s32 caretY;
    /* 0x0a0 */ s32 suffixLabelX;
    /* 0x0a4 */ u16 flags;
    /* 0x0a6 */ u8 maxLength;
    /* 0x0a7 */ u8 caretBlinkTimer;
    /* 0x0a8 */ u8 caretIndex;
    /* 0x0a9 */ u8 selectionStart;
    /* 0x0aa */ u8 selectionEnd;
    /* 0x0ab */ u8 textLeft;
    /* 0x0ac */ u8 textRight;
    /* 0x0ad */ u8 entryMode;
    /* 0x0ae */ u8 returnState;
    /* 0x0af */ u8 textWidth;
    /* 0x0b0 */ GeneralMenuHeader header;
    /* 0x144 */ Keyboard keyboard;
    /* 0x3d00 */ MenuBottomButtons bottomButtons;
    /* 0x3e64 */ MenuCursorBuf0 cursor;
    /* 0x3ec8 */ LabelString suffixLabel;
    /* 0x3f08 */ LabelString censorString;
    /* 0x3f48 */ EncodedString41 encodedText;
    /* 0x3f80 */ MenuErrorMessage errorMessage;
    /* 0x4088 */ u8 text[0x20];
    /* 0x40a8 */ u8 clipboard[0x20];
};

extern "C" ProcProfile data_ov126_022999e0 = {(void *(*)())NameEntryMenu_Create, 0xab, 0xaf};
extern "C" GXOamAttr data_ov126_02299ad0[2] = {{0x802040c8, 0x1c0, 0, 0x5, 0x0}, {0x404000c8, 0x1c4, 0, 0x5, 0xffff}};

extern "C" NameEntryMenu *NameEntryMenu_Create() { return new NameEntryMenu(); }

BOOL NameEntryMenu::onCreate() {
    init();
    transitionState = 0;
    setPhase(0);
    return TRUE;
}

BOOL NameEntryMenu::onDelete() {
    s32 t = MenuCtrl_GetMode();
    if ((u32)t >= 0x18 && (u32)t <= 0x1b) {
        void *h = ProcBase_GetParent(this);
        if (((MenuTabBar *)(h))->onTabMenuClosed() == 6) {
            ((MenuTabBar *)(h))->showTabs();
        }
    } else {
        ((MenuLauncher *)(ProcBase_GetParent(this)))->onChildClosed();
    }
    releaseResources();
    return TRUE;
}

BOOL NameEntryMenu::onDraw() {
    s32 y = slideY;
    if (!testFlags(1)) {
        return FALSE;
    }
    if (MenuCtrl_IsButtons()) {
        ((MenuCursorBase *)(&cursor))->drawWrapped();
    }
    ((GeneralMenuHeader *)(&header))->drawWithIcon(0, y);
    ((MenuBottomButtons *)(&bottomButtons))->drawAt(getSlideOffsetY());
    Keyboard_Draw(&keyboard, 0x80, y + 0x60, 1);
    Shared_Keyboard_DrawCopyPasteKeys(&keyboard, 0x80, y + 0x60);
    if (testFlags(0x100)) {
        Oam_DrawCell(1, data_ov126_02299ad0, (u32)suffixLabelX + 0x80, y + 0x60, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
    if (testFlags(2)) {
        s32 a = caretX;
        s32 b = caretY;
        caretBlinkTimer = caretBlinkTimer + (TICK_STEP_ENDS() ? 1 : 0);
        if ((caretBlinkTimer & 0x10) != 0) {
            Keyboard_DrawCaret(&keyboard, a, b, 2);
        }
    }
    return TRUE;
}

BOOL NameEntryMenu::execTransition() {
    static Unk_ov126_02299ae8_Fn tbl[12] = {&NameEntryMenu::transitionAct00, &NameEntryMenu::transitionAct01, &NameEntryMenu::transitionAct02, &NameEntryMenu::transitionAct03, &NameEntryMenu::transitionAct04, &NameEntryMenu::transitionAct05, &NameEntryMenu::transitionAct06, &NameEntryMenu::transitionAct07, &NameEntryMenu::transitionAct08, &NameEntryMenu::transitionAct09, &NameEntryMenu::transitionAct0A, &NameEntryMenu::transitionAct0B};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}

void NameEntryMenu::runMainState() {
    static Unk_ov126_02299ae8_Fn tbl[17] = {&NameEntryMenu::mainAct00, &NameEntryMenu::mainAct01, &NameEntryMenu::mainAct02, &NameEntryMenu::mainAct03, &NameEntryMenu::mainAct04, &NameEntryMenu::mainAct05, &NameEntryMenu::mainAct06, &NameEntryMenu::mainAct07, &NameEntryMenu::mainAct08, &NameEntryMenu::mainAct09, &NameEntryMenu::mainAct0A, &NameEntryMenu::mainAct0B, &NameEntryMenu::mainAct0C, &NameEntryMenu::mainAct0D, &NameEntryMenu::mainAct0E, &NameEntryMenu::mainAct0F, &NameEntryMenu::mainAct10};
    (this->*tbl[mainState])();
}

BOOL NameEntryMenu::execMain() {
    MenuCtrl_TickForceClose();
    if (MenuCtrl_IsForceCloseDue()) {
        u32 r5 = MenuCtrl_GetMode();
        switch (r5) {
        case 0x18:
        case 0x19:
        case 0x1a:
        case 0x1b:
            switch (mainState) {
            case 0: case 1: case 2: case 4: case 6: case 7: case 9: case 10: case 11: case 12: case 13: case 14:
                clearFlags(2);
                hideCursor();
                ((MenuTabBar *)(ProcBase_GetParent(this)))->selectTab(7);
                setFlags(0x40);
                beginSubSlideOut(0xa, 0, 0, 0x30);
                updateBgScroll();
                setTransitionState(5);
                setPhase(1);
                if (r5 == 0x19 || r5 == 0x1b) {
                    FriendEntry_Clear(getFriendEntry());
                }
                break;
            case 3:
            case 5:
            case 8:
                break;
            }
            break;
        }
    }
    preInputUpdate();
    runMainState();
    postInputUpdate();
    return TRUE;
}

BOOL NameEntryMenu::execPhase3() {
    return TRUE;
}

BOOL NameEntryMenu::execPhase4() {
    return TRUE;
}

BOOL NameEntryMenu::execClosed() {
    ProcBase_RequestDelete(this);
    return TRUE;
}

void NameEntryMenu::transitionAct00() {
    setupBgLayers();
    loadBg();
    setTransitionState(1);
}

void NameEntryMenu::transitionAct01() {
    Shared_Keyboard_RestoreLastPage(&keyboard, 6);
    loadObjGfx();
    redrawText();
    setupDialogButtons();
    beginSubSlideIn(0xa, 4, 0, 0x30);
    Gfx2d_ShowLayer(4);
    Gfx2d_ShowLayer(6);
    updateBgScroll();
    setFlags(1);
    setTransitionState(2);
}

void NameEntryMenu::transitionAct02() {
    if (stepSlideIn(0)) {
        setPhase(2);
        resumeInput();
        resetTextCursor();
    }
    updateBgScroll();
}

void NameEntryMenu::transitionAct03() {
    clearFlags(2);
    u32 r5 = MenuCtrl_GetMode();
    if (r5 >= 0x18 && r5 <= 0x1b) {
        void *r6 = ProcBase_GetParent(this);
        switch (r5) {
        case 0x18:
        case 0x1a:
            ((MenuTabBar *)(r6))->selectTab(6);
            if (!testFlags(0x40)) {
                MenuCtrl_SetFriendPageFromIndex();
            }
            break;
        case 0x19:
            if (testFlags(0x40)) {
                ((MenuTabBar *)(r6))->selectTab(0xc);
            } else {
                ((MenuTabBar *)(r6))->selectTab(6);
                MenuCtrl_SetFriendPageFromIndex();
                if (gCommManager->isSlotActive(gCommManager->myAid)) {
                    s32 t = Net_GetMode();
                    if (t == 3) goto yes;
                    if (t == 4) {
                    yes:
                        setTransitionState(4);
                        transitionAct04();
                        return;
                    }
                }
            }
            break;
        case 0x1b:
            if (testFlags(0x40)) {
                ((MenuTabBar *)(r6))->selectTab(0xe);
            } else {
                ((MenuTabBar *)(r6))->selectTab(0xa);
            }
            break;
        }
    } else {
        ((MenuLauncher *)(ProcBase_GetParent(this)))->setNextRequest(0x44, 1);
    }
    beginSubSlideOut(0xa, 0, 0, 0x30);
    updateBgScroll();
    setTransitionState(5);
}

void NameEntryMenu::transitionAct04() {
    void *r4 = getFriendEntry();
    s32 r6 = MenuCtrl_GetIndex();
    if (Net_WifiAddFriend(r6, DwcFriendData_GetBytes(FriendEntry_GetFriendData(r4)))) {
        beginSubSlideOut(0xa, 0, 0, 0x30);
        updateBgScroll();
        setTransitionState(5);
    }
}

void NameEntryMenu::transitionAct05() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(4);
        Gfx2d_ResetLayer(6);
        clearFlags(1);
        setPhase(5);
        if (testFlags(0x40)) {
            MenuCtrl_SetResult(0);
        } else {
            MenuCtrl_SetResult(1);
            commitEntry();
            MenuCtrl_SetText(text, maxLength);
            s32 t = MenuCtrl_GetMode();
            if (t != 0x18 && t != 0x19 && t != 0x1a) {
            } else {
                ((MenuTabBar *)(ProcBase_GetParent(this)))->requestSaveOnClose();
            }
        }
    } else {
        updateBgScroll();
    }
}

void NameEntryMenu::transitionAct06() {
    initSlideOut(0, 0);
    setTransitionState(7);
}

void NameEntryMenu::transitionAct07() {
    if (stepSlideOut(-1)) {
        initSlideIn(0, 0);
        if (testFlags(0x40)) {
            ((MenuBottomButtonsBody *)(&bottomButtons))->setLayoutYesNo09(0x87);
        } else {
            ((MenuBottomButtonsBody *)(&bottomButtons))->setLayoutYesNo09(0x22);
        }
        setTransitionState(8);
    }
}

void NameEntryMenu::transitionAct08() {
    if (stepSlideIn(-1)) {
        setPhase(2);
        enterDialogInput();
    }
}

void NameEntryMenu::transitionAct09() {
    initSlideOut(0, 0);
    setTransitionState(0xa);
}

void NameEntryMenu::transitionAct0A() {
    if (stepSlideOut(-1)) {
        initSlideIn(0, 0);
        setupDialogButtons();
        setTransitionState(0xb);
    }
}

void NameEntryMenu::transitionAct0B() {
    if (stepSlideIn(-1)) {
        setPhase(2);
        resumeInput();
    }
}

void NameEntryMenu::updateBgScroll() {
    applySlideOffset(4, 0, 0);
    applySlideOffset(6, 0, 0);
    slideY = getSlideOffsetY();
}

void NameEntryMenu::init() {
    flags = 0;
    suffixLabelX = 0;
    u32 r5 = MenuCtrl_GetMode();
    switch (r5) {
    case 0x0b: case 0x0c: case 0x0d: case 0x0e: case 0x0f: case 0x10: case 0x11: case 0x12:
    case 0x13: case 0x14: case 0x15: case 0x16: case 0x17: case 0x18: case 0x1a:
        entryMode = 2;
        break;
    case 0x19:
    case 0x1b:
        setFlags(0x20);
        entryMode = 0;
        break;
    }
    switch (entryMode) {
    case 0:
        Keyboard_Init(&keyboard, 5);
        break;
    case 1:
    case 2:
        Keyboard_Init(&keyboard, 4);
        break;
    case 3:
        Keyboard_Init(&keyboard, 3);
        break;
    }
    switch (Shared_GeneralMenuHeader_GetStyle()) {
    case 0:
        maxLength = 0x10;
        textLeft = 0x50;
        textRight = 0xb8;
        textWidth = 0x68;
        break;
    case 1:
        maxLength = 0x8;
        textLeft = 0x60;
        textRight = 0xa0;
        textWidth = 0x40;
        break;
    case 2:
        maxLength = 0x20;
        textLeft = 0x30;
        textRight = 0xd0;
        textWidth = 0xa0;
        break;
    case 3:
        maxLength = 0x4;
        textLeft = 0x68;
        textRight = 0x90;
        textWidth = 0x28;
        break;
    case 4:
        maxLength = 0xa;
        textLeft = 0x58;
        textRight = 0xa8;
        textWidth = 0x50;
        break;
    }
    Mem_Clear(text, 0x20);
    Mem_Clear(clipboard, 0x20);
    loadInitialText();
    if (Text_GetTrimmedLength(text, maxLength) == 0) {
        Mem_Clear(text, 0x20);
    }
    if (r5 == 0x10 || r5 == 0x18 || r5 == 0x19 || r5 == 0x12) {
        setFlags(0x100);
    }
}

void NameEntryMenu::releaseResources() {
    ((GeneralMenuHeader *)(&header))->resetFrame();
    Keyboard_Shutdown(&keyboard);
    ((MenuBottomButtons *)(&bottomButtons))->freeTexts();
    ((LabelString *)(&suffixLabel))->destroyLabel();
}

void NameEntryMenu::preInputUpdate() {
    preStateUpdate();
    (&cursor)->update();
}

void NameEntryMenu::postInputUpdate() {
    postStateUpdate();
}

void NameEntryMenu::preStateUpdate() {
    clearFlags(0x10);
    ((GeneralMenuHeader *)(&header))->resetFrame();
    ((MenuBottomButtons *)(&bottomButtons))->freeTexts();
    ((LabelString *)(&suffixLabel))->destroyLabel();
}

void NameEntryMenu::postStateUpdate() {
    Keyboard_EndFrame(&keyboard, 6);
}

void NameEntryMenu::setupBgLayers() {
    Gfx2d_SetSubBgModeState(0);
    Gfx2d_SetLayerPriority(4, 3);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
    Gfx2d_SetLayerPriority(6, 2);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
}

void NameEntryMenu::loadBg() {
    ((GeneralMenuHeader *)(&header))->loadBgGfxForStyle(4);
    Gfx2d_LoadCharFile("menu/chat2/b_cht.bch", gCurrentHeap, 4, 0x13d, 0x13d, 0x1e9);
    Keyboard_LoadScreenFile(&keyboard, "menu/letter/b_key.bsc");
    refreshKeys();
    Keyboard_LoadScreenNow(&keyboard, 6);
    Shared_Keyboard_LoadLetterChars(&keyboard, 6);
}

void NameEntryMenu::loadObjGfx() {
    Keyboard_LoadObjGfx(&keyboard);
    ((GeneralMenuHeader *)(&header))->loadObjGfx(6);
    Gfx2d_LoadPaletteFile("menu/han/obj.bpl", gCurrentHeap, 8, 5, 5, 5);
    MenuButtons_LoadTextColors();
    if (testFlags(0x100)) {
        LabelString buf;
        buf.clear();
        String_SetSlot(0, &buf);
        if (MenuCtrl_GetMode() == 0x12) {
            String_Load2dMenu(&suffixLabel, 0x80);
        } else {
            String_Load2dMenu(&suffixLabel, 0x66);
        }
        ((LabelString *)(&suffixLabel))->createLabel(8, 0x1c0, 6, 0xf, 0, 0);
        ((LabelString *)(&suffixLabel))->redrawAligned(0, 0);
    }
}

void NameEntryMenu::mainAct00() {
    if (checkSwitchToButtons(1)) {
        startButtonInput();
        return;
    }
    BOOL r4 = Keyboard_UpdatePressedKey(&keyboard);
    if (Unk_ov126_02298c4c_Both()) {
        if (!touchDialogButtons()) {
            if (!touchTextField()) {
                if (Keyboard_TouchPageTab(&keyboard)) {
                    Keyboard_SetMode(&keyboard, 8, 6, 1);
                    redrawText();
                } else if (gTouchCurY >= 0x48) {
                    if (!r4) {
                        s32 r = touchKey();
                        if (r != 0) {
                            if (r == 1) {
                                setMainState(2);
                            }
                        }
                    }
                }
            }
        }
    }
}

void NameEntryMenu::mainAct01() {
    if (gTouchHeld == 0) {
        setMainState(0);
    } else {
        u8 old = caretIndex;
        setCursorFromTouchX(gTouchCurX);
        if (old != caretIndex) {
            extendSelection();
            redrawText();
            Snd_PlaySe(0x15);
        }
    }
}

void NameEntryMenu::mainAct02() {
    if (gTouchHeld == 0) {
        setMainState(0);
    } else if (Shared_Keyboard_TickKeyRepeat(&keyboard)) {
        s32 t = Keyboard_GetPressedKey(&keyboard);
        s32 r = Keyboard_GetKeyCode(&keyboard, t, 8);
        pressKeyCode(r);
        Shared_Keyboard_HighlightKey(&keyboard, t);
    }
}

void NameEntryMenu::mainAct03() {
    if (checkSwitchToButtons(1)) {
        enterDialogButtons();
    } else if (((MenuBottomButtonsBody *)(&bottomButtons))->isTouched(3)) {
        ((MenuBottomButtonsBody *)(&bottomButtons))->setSelected(3);
        transitionState = 3;
        setMainState(0xf);
    } else if (((MenuBottomButtonsBody *)(&bottomButtons))->isTouched(4)) {
        ((MenuBottomButtonsBody *)(&bottomButtons))->setSelected(4);
        transitionState = 9;
        setMainState(0xf);
    }
}

void NameEntryMenu::mainAct04() {
    if (checkSwitchToTouch()) {
        startTouchInput();
    } else {
        switch (Keyboard_MoveCursor(&keyboard, takeRepeatedKeys())) {
        case 1:
            ((MenuCursor *)(&cursor))->switchToAnim01();
            moveCursorToTarget();
            break;
        case 2:
            ((MenuCursor *)(&cursor))->switchToAnim0D();
            moveCursorToTarget();
            break;
        case 3:
            ((MenuCursor *)(&cursor))->switchToAnim07();
            moveCursorToTarget();
            break;
        case 4:
            ((MenuCursor *)(&cursor))->switchToAnim01();
            setFlags(0x80);
            setMainState(6);
            moveCursorToTarget();
            break;
        case 0:
        default:
            if (tryPressKey()) { return; }
            if (tryBackspaceButton()) { return; }
            if (tryCopyButton()) { return; }
            if (tryPasteButton()) { return; }
            if (tryStartConfirm()) { return; }
        }
    }
}

void NameEntryMenu::mainAct05() {
    if (checkSwitchToTouch()) {
        enterDialogTouch();
    }
}

void NameEntryMenu::mainAct06() {
    if (checkSwitchToTouch()) {
        startTouchInput();
    } else {
        s32 r = navigateText(takeRepeatedKeys());
        switch (r) {
        case 1:
            Shared_Keyboard_ResetTypedRun(&keyboard);
            clearSelection();
            updateCaretX();
            redrawText();
            snapCursor();
            Snd_PlaySe(0xb);
            break;
        case 2:
            Shared_Keyboard_EnterTabRowAtX(&keyboard, ((MenuCursorBase *)(&cursor))->getScreenX());
            leaveTextToKeys();
            break;
        default: {
            u32 old = caretIndex;
            if (tryBackspaceButton()) {
                if (old != caretIndex) {
                    snapCursor();
                }
            } else if (tryCopyButton()) {
            } else if (tryPasteButton()) {
            } else if (tryStartConfirm()) {
            } else if ((gPad[1] & 1) != 0) {
                setMainState(7);
                startSelection();
            }
        }
        }
    }
}

void NameEntryMenu::leaveTextToKeys() {
    clearFlags(0x80);
    setMainState(4);
    moveCursorToTarget();
}

void NameEntryMenu::mainAct07() {
    if ((gPad[0] & 1) == 0) {
        setMainState(6);
    } else if (navigateText(takeRepeatedKeys()) == 1) {
        Shared_Keyboard_ResetTypedRun(&keyboard);
        extendSelection();
        updateCaretX();
        redrawText();
        snapCursor();
        Snd_PlaySe(0x15);
    }
}

void NameEntryMenu::mainAct08() {
    if (((MenuCursorBase *)(&cursor))->isMoving() == 0) {
        setMainState(returnState);
        runMainState();
    }
}

void NameEntryMenu::mainAct09() {
    if (((HandCursor *)(&cursor))->isAnimDone()) {
        s32 t = Shared_Keyboard_PressCursorKey(&keyboard);
        s32 r = pressKeyCode(Keyboard_GetKeyCode(&keyboard, t, 8));
        if (r == 1 && (gPad[0] & 1) != 0) {
            Keyboard_StartKeyRepeat(&keyboard);
            setMainState(0xa);
            Shared_Keyboard_HighlightKey(&keyboard, t);
        } else if (r == 4) {
            Shared_Keyboard_ClearHighlight(&keyboard);
        } else if (r != 3) {
            releaseCursor();
        }
    }
}

void NameEntryMenu::mainAct0A() {
    if ((gPad[0] & 1) == 0) {
        releaseCursor();
    } else if (Shared_Keyboard_TickKeyRepeat(&keyboard)) {
        s32 t = Keyboard_GetPressedKey(&keyboard);
        s32 r = Keyboard_GetKeyCode(&keyboard, t, 8);
        pressKeyCode(r);
        Shared_Keyboard_HighlightKey(&keyboard, t);
    }
}

void NameEntryMenu::mainAct0B() {
    if (((HandCursor *)(&cursor))->isAnimDone()) {
        refreshCursor();
        setMainState(4);
    }
}

void NameEntryMenu::mainAct0C() {
    if ((gPad[0] & 2) == 0) {
        setMainState(returnState);
    } else if (Shared_Keyboard_TickKeyRepeat(&keyboard)) {
        Keyboard_ShrinkTypedRun(&keyboard);
        if (backspace(0)) {
            if (testFlags(0x80)) {
                snapCursor();
            }
        } else {
            onBackspaceEmpty();
        }
    }
}

void NameEntryMenu::mainAct0D() {
    if ((gPad[0] & 0x200) == 0) {
        setMainState(returnState);
        refreshKeys();
    }
}

void NameEntryMenu::mainAct0E() {
    if ((gPad[0] & 0x100) == 0) {
        setMainState(returnState);
        refreshKeys();
    }
}

void NameEntryMenu::mainAct0F() {
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

void NameEntryMenu::mainAct10() {
    Keyboard_UpdatePressedKey(&keyboard);
    if (((MenuErrorMessage *)(&errorMessage))->update(1)) {
        resumeInput();
    }
}

void NameEntryMenu::startTouchInput() {
    hideCursor();
    setMainState(0);
}

void NameEntryMenu::startButtonInput() {
    restartKeyRepeat();
    showCursor();
    setMainState(4);
}

void NameEntryMenu::resumeInput() {
    if (MenuCtrl_IsTouch()) {
        startTouchInput();
    } else {
        startButtonInput();
    }
}

void NameEntryMenu::showMessage(u32 v, u32 w) {
    u8 buf[1];
    buf[0] = gU8None;
    buf[0] = v;
    ((MenuErrorMessage *)(&errorMessage))->open((u8 *)(buf), w, 0);
    setMainState(0x10);
    hideCursor();
}

void NameEntryMenu::enterDialogTouch() {
    hideCursor();
    setMainState(3);
}

void NameEntryMenu::enterDialogButtons() {
    restartKeyRepeat();
    setMainState(5);
}

void NameEntryMenu::enterDialogInput() {
    if (MenuCtrl_IsTouch()) {
        enterDialogTouch();
    } else {
        enterDialogButtons();
    }
}

void NameEntryMenu::closeWithResult(s32 a) {
    if (a == 0) {
        ((MenuBottomButtonsBody *)(&bottomButtons))->setSelected(6);
        if (entryMode == 1) {
            setFlags(0x40);
        } else {
            clearFlags(0x40);
        }
    } else {
        ((MenuBottomButtonsBody *)(&bottomButtons))->setSelected(7);
        setFlags(0x40);
    }
    if (testFlags(0x20)) {
        if (testFlags(0x40)) {
            Snd_PlaySe(0x2a);
        } else if (MenuCtrl_GetMode() == 0x19) {
            Snd_PlaySe(0x27);
        } else {
            Snd_PlaySe(0x29);
        }
    } else if (testFlags(0x40)) {
        Snd_PlaySe(0x28);
    } else {
        Snd_PlaySe(0x27);
    }
    transitionState = 3;
    setMainState(0xf);
}

BOOL NameEntryMenu::confirm() {
    if (((MenuBottomButtonsBody *)(&bottomButtons))->isButtonDisabled(6)) {
        playErrorSe();
        return FALSE;
    }
    if (entryMode == 0 || entryMode == 2) {
        hideCursor();
        closeWithResult(0);
        return TRUE;
    }
    playErrorSe();
    return FALSE;
}

BOOL NameEntryMenu::onBackspaceEmpty() {
    switch (entryMode) {
    case 0:
        hideCursor();
        closeWithResult(1);
        return TRUE;
    case 1:
        hideCursor();
        closeWithResult(0);
        return TRUE;
    default:
        playErrorSe();
        return FALSE;
    }
}

void NameEntryMenu::refreshKeys() {
    if (entryMode == 0 || entryMode == 2) {
        if (Text_GetTrimmedLength(text, maxLength) == 0) {
            ((MenuBottomButtonsBody *)(&bottomButtons))->disableButton(6);
        } else {
            ((MenuBottomButtonsBody *)(&bottomButtons))->enableButton(6);
        }
    }
    Keyboard_DisableKey(&keyboard, 0);
    if (hasSelection()) {
        Shared_Keyboard_EnableKey(&keyboard, 0xb);
    } else {
        Keyboard_DisableKey(&keyboard, 0xb);
    }
    if (testFlags(8)) {
        Shared_Keyboard_EnableKey(&keyboard, 0xc);
    } else {
        Keyboard_DisableKey(&keyboard, 0xc);
    }
    if (hasSelection()) {
        Shared_Keyboard_DisableModifierKeys(&keyboard);
        Shared_Keyboard_EnableKey(&keyboard, 6);
    } else if (caretIndex == 0) {
        Shared_Keyboard_DisableModifierKeys(&keyboard);
    } else {
        Keyboard_UpdateModifierKeys(&keyboard, getCharBeforeCursor());
    }
}

void NameEntryMenu::resetTextCursor() {
    setFlags(2);
    caretX = textLeft;
    caretY = 0x28;
    setCursorIndex(0);
    clearSelection();
    Keyboard_ResetKeyPalettes(&keyboard);
    refreshKeys();
}

void NameEntryMenu::setCursorIndex(u32 v) {
    caretIndex = v;
    caretBlinkTimer = 0x10;
}

u32 NameEntryMenu::getCharBeforeCursor() {
    if (caretIndex == 0) return 0;
    return text[caretIndex - 1];
}

void NameEntryMenu::updateCaretX() {
    caretX = textLeft;
    caretY = 0x28;
    caretX = caretX + (u8)Text_MeasureWidth(text, caretIndex);
}

void NameEntryMenu::setCursorFromTouchX(s32 v) {
    s32 t = v - textLeft;
    if (t < 0) t = 0;
    u8 out[8];
    caretX = Keyboard_HitTestText(&keyboard, text, maxLength, textWidth, (u8)t, out);
    caretX = caretX + textLeft;
    setCursorIndex(out[0]);
    refreshKeys();
}

BOOL NameEntryMenu::touchTextField() {
    s32 r1 = gTouchCurX;
    s32 r2 = gTouchCurY;
    if (r2 < 0x28 || r2 > 0x38) return FALSE;
    if (r1 < textLeft - 0xc) return FALSE;
    if (r1 > textRight + 0xc) return FALSE;
    setCursorFromTouchX(r1);
    startSelection();
    setMainState(1);
    Shared_Keyboard_ResetTypedRun(&keyboard);
    redrawText();
    return TRUE;
}

s32 NameEntryMenu::navigateText(s32 a) {
    u32 p = a;
    if (p == 0) return 0;
    u32 r4 = caretIndex;
    if (MenuKeys_HasLeft(p) != 0) {
        if (r4 != 0) {
            setCursorIndex((u8)(r4 - 1));
            return 1;
        }
        return 3;
    }
    if (MenuKeys_HasRight(p) != 0) {
        s32 n = Text_GetLength(text, maxLength);
        s32 t = r4 + 1;
        if (t <= n) {
            setCursorIndex((u8)t);
            return 1;
        }
        return 4;
    }
    if (MenuKeys_HasDown(p) != 0) return 2;
    return 0;
}

BOOL NameEntryMenu::hasSelection() {
    if (testFlags(4) == 0) goto no;
    if (selectionStart != selectionEnd) goto yes;
no:
    return FALSE;
yes:
    return TRUE;
}

void NameEntryMenu::clearSelection() {
    selectionStart = 0;
    selectionEnd = 0;
    clearFlags(4);
}

void NameEntryMenu::deleteSelection() {
    u32 e = selectionEnd;
    u32 s = selectionStart;
    u32 lo, hi;
    if (s > e) {
        lo = e;
        hi = s;
    } else {
        lo = s;
        hi = e;
    }
    u8 r = Shared_Keyboard_DeleteRange(&keyboard, text, lo, hi, maxLength);
    setCursorIndex(r);
    clearSelection();
}

void NameEntryMenu::startSelection() {
    selectionStart = caretIndex;
    selectionEnd = caretIndex;
    clearFlags(4);
}

void NameEntryMenu::extendSelection() {
    selectionEnd = caretIndex;
    if (selectionEnd != selectionStart) {
        setFlags(4);
    } else {
        clearFlags(4);
    }
}

void NameEntryMenu::copy() {
    if (hasSelection() != 0) {
        u32 e = selectionEnd;
        u32 s = selectionStart;
        s32 r6, r4;
        if (s > e) {
            r6 = e;
            r4 = s - e;
        } else {
            r6 = s;
            r4 = e - s;
        }
        Mem_Clear(clipboard, 0x20);
        Mem_Copy(text + r6, clipboard, r4);
        setFlags(8);
        Shared_Keyboard_PlayCopySe();
        refreshKeys();
    }
}

void NameEntryMenu::paste() {
    if (testFlags(8) != 0) {
        Keyboard_BeginPaste(&keyboard);
        Shared_Keyboard_ResetTypedRun(&keyboard);
        if (hasSelection() != 0) deleteSelection();
        s32 n = Text_GetLength(clipboard, 0x20);
        u8 v;
        v = caretIndex;
        s32 i;
        for (i = 0; i < n; i++) {
            if (Keyboard_InsertChar(&keyboard, text, clipboard[i], &v, maxLength, textWidth, 0, 0) == 0) {
                if (i == 0) playErrorSe();
                i = n;
            }
        }
        Keyboard_PlayPasteSe();
        setCursorIndex(v);
        updateCaretX();
        redrawText();
        Keyboard_EndPaste(&keyboard);
    }
}

s32 NameEntryMenu::touchKey() {
    Shared_Keyboard_ClearHighlight(&keyboard);
    s32 r4 = Shared_Keyboard_TouchKey(&keyboard, gTouchCurX, gTouchCurY);
    if (r4 != -1) {
        s32 r1 = Keyboard_GetKeyCode(&keyboard, r4, 8);
        s32 r6 = pressKeyCode(r1);
        Shared_Keyboard_HighlightKey(&keyboard, r4);
        Keyboard_StartKeyRepeat(&keyboard);
        return r6;
    }
    return 0;
}

s32 NameEntryMenu::pressKeyCode(s32 x) {
    s32 r6 = 1;
    s32 r7 = Shared_Keyboard_HandleModeKey(&keyboard, x, 6);
    if (r7 != 0) {
        redrawText();
        return r7;
    }
    if (Keyboard_IsControlCode(&keyboard, x) != 0) {
        switch (x) {
        case 0x100:
            backspace(r6);
            break;
        case 0x103:
        case 0x104:
        case 0x105:
            if (applyModifierKey(x) == 0) playErrorSe();
            r6 = 2;
            break;
        case 0x118:
            copy();
            r6 = 2;
            break;
        case 0x119:
            paste();
            r6 = 2;
            break;
        case 0x116:
            closeWithResult(0);
            r6 = 3;
            break;
        case 0x117:
            closeWithResult(r6);
            r6 = 3;
            break;
        default:
            r6 = 2;
            break;
        }
    } else {
        BOOL r4 = insertChar((u8)x);
        if (Keyboard_IsFull(&keyboard) != 0) {
            showMessage(0x1c, r6);
            return 4;
        }
        if (Keyboard_IsTooWide(&keyboard) != 0) {
            showMessage(0x1c, r6);
            return 4;
        }
        if (r4 == 0) playErrorSe();
    }
    return r6;
}

BOOL NameEntryMenu::applyModifierKey(s32 x) {
    u32 r2 = getCharBeforeCursor();
    if (r2 == 0) return FALSE;
    switch (x) {
    case 0x103:
        r2 = Keyboard_ModifyCharKey103(&keyboard, r2);
        break;
    case 0x104:
        r2 = Shared_Keyboard_ModifyCharKey104(&keyboard, r2);
        break;
    case 0x105:
        r2 = Keyboard_ModifyCharKey105(&keyboard, r2);
        break;
    }
    if (r2 == 0) return FALSE;
    if (Shared_Keyboard_ReplaceCharBeforeCursor(&keyboard, text, r2, caretIndex) == 0) return FALSE;
    redrawText();
    updateCaretX();
    return TRUE;
}

BOOL NameEntryMenu::backspace(s32 x) {
    if (hasSelection() != 0) {
        Shared_Keyboard_ResetTypedRun(&keyboard);
        Snd_PlaySe(0x35);
        goto done;
    }
    {
        u32 t = caretIndex;
        if (t != 0) {
            selectionStart = t;
            selectionEnd = caretIndex - 1;
            Snd_PlaySe(0x35);
            goto done;
        }
    }
    if (text[0] != 0) {
        selectionStart = 0;
        selectionEnd = 1;
        Snd_PlaySe(0x35);
        goto done;
    }
    if (x != 0) playErrorSe();
    return FALSE;
done:
    deleteSelection();
    redrawText();
    updateCaretX();
    return TRUE;
}

BOOL NameEntryMenu::insertCharRaw(u32 x) {
    u8 v[8];
    v[0] = caretIndex;
    if (Keyboard_InsertChar(&keyboard, text, x, v, maxLength, textWidth, 0, 1) != 0) {
        setCursorIndex(v[0]);
        return TRUE;
    }
    return FALSE;
}

BOOL NameEntryMenu::insertChar(u32 x) {
    if (hasSelection() != 0) {
        deleteSelection();
        Shared_Keyboard_ResetTypedRun(&keyboard);
    }
    BOOL r = insertCharRaw(x);
    redrawText();
    updateCaretX();
    return r;
}

void NameEntryMenu::redrawText() {
    ((GeneralMenuHeader *)(&header))->setTitleText(text, maxLength);
    if (testFlags(0x100) != 0) {
        s32 t = Text_MeasureWidth(text, maxLength);
        suffixLabelX = -(textWidth - t - 2);
    }
    ((GeneralMenuHeader *)(&header))->placeTitleText();
    highlightSelection();
    ((GeneralMenuHeader *)(&header))->redrawTitle();
    setFlags(0x10);
    refreshKeys();
}

void NameEntryMenu::highlightSelection() {
    s32 r0, r1, r2, r4;
    if (hasSelection() != 0) {
        u32 e = selectionEnd;
        u32 s = selectionStart;
        if (s > e) {
            r4 = e;
            r0 = s - e;
        } else {
            r4 = s;
            r0 = e - s;
        }
        r1 = 7;
        r2 = 6;
    } else {
        r0 = Shared_Keyboard_GetTypedRunLength(&keyboard);
        if (r0 != 0) {
            r4 = caretIndex - r0;
        }
        r1 = 5;
        r2 = 1;
    }
    if (r0 != 0) {
        ((GeneralMenuHeader *)(&header))->setTitleHighlight(r1, r2, r4, r0);
    }
}

void NameEntryMenu::playErrorSe() {
    Snd_PlaySe(0x34);
}

BOOL NameEntryMenu::touchDialogButtons() {
    if (entryMode == 3) return FALSE;
    if (((MenuBottomButtonsBody *)(&bottomButtons))->isButtonDisabled(6) == 0 && ((MenuBottomButtonsBody *)(&bottomButtons))->isTouched(6) != 0) {
        closeWithResult(0);
        return TRUE;
    }
    if (entryMode != 0) return FALSE;
    if (((MenuBottomButtonsBody *)(&bottomButtons))->isTouched(7) != 0) {
        closeWithResult(1);
        return TRUE;
    }
    return FALSE;
}

void NameEntryMenu::setupDialogButtons() {
    switch (entryMode) {
    case 0:
        ((MenuBottomButtons *)(&bottomButtons))->setLayoutConfirmAnd06(0xd8);
        break;
    case 2:
        ((MenuBottomButtons *)(&bottomButtons))->setLayoutSingle05(0x21);
        break;
    case 1:
        ((MenuBottomButtons *)(&bottomButtons))->setLayoutSingle05(0x65);
        break;
    case 3:
        break;
    }
}

void NameEntryMenu::showCursor() {
    clearFlags(0x80);
    Keyboard_ResetCursor(&keyboard);
    s32 a = Keyboard_GetCursorX(&keyboard);
    s32 b = Keyboard_GetCursorY(&keyboard);
    ((MenuCursorBase *)(&cursor))->warpTo(a, b);
    ((MenuCursor *)(&cursor))->setAnimIfChanged(1);
    refreshCursor();
}

void NameEntryMenu::hideCursor() {
    ((MenuCursor *)(&cursor))->setAnimIfChanged(0);
    cursor.update();
}

void NameEntryMenu::moveCursorToTarget() {
    if (testFlags(0x80)) {
        ((MenuCursorBase *)(&cursor))->moveToNear(caretX, 0x28, 3, 2);
        returnState = 6;
    } else {
        s32 a = Keyboard_GetCursorX(&keyboard);
        s32 b = Keyboard_GetCursorY(&keyboard);
        ((MenuCursorBase *)(&cursor))->moveToNear(a, b, 3, 2);
        returnState = 4;
    }
    setMainState(8);
}

void NameEntryMenu::snapCursor() {
    if (testFlags(0x80)) {
        ((MenuCursorBase *)(&cursor))->warpTo(caretX, 0x28);
    } else {
        s32 a = Keyboard_GetCursorX(&keyboard);
        s32 b = Keyboard_GetCursorY(&keyboard);
        ((MenuCursorBase *)(&cursor))->warpTo(a, b);
    }
    cursor.update();
}

void NameEntryMenu::pressCursor() {
    ((MenuCursor *)(&cursor))->setPosePress();
    setMainState(9);
}

void NameEntryMenu::releaseCursor() {
    Shared_Keyboard_ClearHighlight(&keyboard);
    ((MenuCursorBase *)(&cursor))->setPoseRelease();
    setMainState(0xb);
}

void NameEntryMenu::refreshCursor() {
    ((MenuCursorBase *)(&cursor))->setPoseIdle();
    cursor.update();
}

BOOL NameEntryMenu::tryPressKey() {
    if ((gPad[1] & 1) == 0) {
        return FALSE;
    }
    s32 t = Shared_Keyboard_PressCursorKey(&keyboard);
    if (t == -1) {
        return FALSE;
    }
    if (((MenuBottomButtonsBody *)(&bottomButtons))->isButtonDisabled(6) && t == 0xd9) {
        return FALSE;
    }
    Keyboard_GetKeyCode(&keyboard, t, 8);
    Shared_Keyboard_HighlightKey(&keyboard, t);
    pressCursor();
    return TRUE;
}

BOOL NameEntryMenu::tryBackspaceButton() {
    if ((gPad[0] & 2) == 0) {
        return FALSE;
    }
    Keyboard_ShrinkTypedRun(&keyboard);
    if (backspace(0)) {
        Keyboard_StartKeyRepeat(&keyboard);
        returnState = mainState;
        setMainState(0xc);
    } else {
        onBackspaceEmpty();
    }
    return TRUE;
}

BOOL NameEntryMenu::tryPasteButton() {
    if ((gPad[1] & 0x100) == 0) {
        return FALSE;
    }
    if (Keyboard_IsSlotDisabled(&keyboard, 0xc)) {
        return FALSE;
    }
    pressKeyCode(0x119);
    Shared_Keyboard_HighlightKey(&keyboard, 0xdc);
    snapCursor();
    returnState = mainState;
    setMainState(0xe);
    return FALSE;
}

BOOL NameEntryMenu::tryCopyButton() {
    if ((gPad[1] & 0x200) == 0) {
        return FALSE;
    }
    if (Keyboard_IsSlotDisabled(&keyboard, 0xb)) {
        return FALSE;
    }
    pressKeyCode(0x118);
    Shared_Keyboard_HighlightKey(&keyboard, 0xdb);
    returnState = mainState;
    setMainState(0xd);
    return FALSE;
}

BOOL NameEntryMenu::tryStartConfirm() {
    if ((gPad[1] & 8) == 0) {
        return FALSE;
    }
    confirm();
    return TRUE;
}

void NameEntryMenu::loadDesignName() {
    u8 buf[0x10];
    PlayerPatterns *a = (PlayerPatterns *)PlayerData_GetCurrent()->getPatterns();
    ((PatternInfo *)(((Pattern *)(a->getPatternByOrder(MenuCtrl_GetIndex())))->getInfo()))->getTitleRaw((u8 *)(buf));
    Mem_Copy(buf, text, 0x10);
}

void NameEntryMenu::loadConstellationName() {
    Constellation_CopyName(text, MenuCtrl_GetIndex());
}

u8 *NameEntryMenu::getFriendEntry() {
    PlayerData *t = PlayerData_GetCurrent();
    void *p = t->getFriendList();
    s32 idx = MenuCtrl_GetIndex();
    FriendEntry *q = (FriendEntry *)FriendList_GetEntries(p);
    return (u8 *)&q[idx];
}

void NameEntryMenu::loadFriendField1() {
    Mem_Copy(FriendEntry_GetTownName(getFriendEntry()), text, 8);
}

void NameEntryMenu::loadFriendField2() {
    Mem_Copy(FriendEntry_GetPlayerName(getFriendEntry()), text, 8);
}

void NameEntryMenu::loadInitialText() {
    switch (MenuCtrl_GetMode()) {
    case 0x11:
    case 0x15:
    case 0x16:
    case 0x17:
        Mem_Copy(MenuCtrl_GetText(), text, maxLength);
        break;
    case 0xb: loadDesignName(); break;
    case 0x12: loadConstellationName(); break;
    case 0x18:
    case 0x19: loadFriendField1(); break;
    case 0x1a:
    case 0x1b: loadFriendField2(); break;
    }
}

void NameEntryMenu::storeDesignName() {
    u8 buf[0x10];
    PlayerPatterns *a = (PlayerPatterns *)PlayerData_GetCurrent()->getPatterns();
    void *p = a->getPatternByOrder(MenuCtrl_GetIndex());
    Mem_Copy(text, buf, 0x10);
    ((PatternInfo *)(((Pattern *)(p))->getInfo()))->setTitleRaw((u8 *)(buf));
}

void NameEntryMenu::checkGeneralAnswer() {
    LabelString b;
    String_LoadByIndex(&b, "st_general", MenuCtrl_GetIndex());
    if (!String_EqualsEncodedBytes(&b, text, maxLength)) {
        MenuCtrl_SetResult(0);
    }
}

void NameEntryMenu::checkItemNameAnswer() {
    u16 id;
    ItemName rec;
    LabelString b;
    u16 i;
    for (i = 0x1323; i <= 0x1368; i++) {
        id = i;
        ((ItemName *)(&rec))->setFromItem((u16 *)(&id));
        ((MsgString *)(&b))->copy((MsgString *)(&rec));
        if (String_EqualsEncodedBytes(&b, text, maxLength)) {
            MenuCtrl_SetIndex((u8)(i - 0x1323));
            MenuCtrl_SetResult(1);
            return;
        }
    }
    MenuCtrl_SetResult(0);
}

void NameEntryMenu::checkPasswordAnswer() {
    LabelString b;
    String_LoadByIndex(&b, "st_password", MenuCtrl_GetIndex());
    if (!String_EqualsEncodedBytes(&b, text, maxLength)) {
        MenuCtrl_SetResult(0);
    }
}

void NameEntryMenu::storePlayerName() {
    PlayerData *t = PlayerData_GetCurrent();
    t->getPlayerId();
    PlayerId *u = t->getPlayerId();
    s32 n = PlayerDataArray_FindById(gSavePlayers, (u16 *)u);
    s32 i;
    for (i = 0; i < 4; i++) {
        if (i != n && PlayerDataArray_IsUsed(gSavePlayers, i)) {
            if (Text_EqualsTrimmed(((PlayerData *)PlayerData_GetResident(gSavePlayers, i))->getPlayerId()->getName(), text, 8)) {
                MenuCtrl_SetResult(2);
                return;
            }
        }
    }
    ((PlayerId *)(t->getPlayerId()))->setName(text);
}

void NameEntryMenu::storeTownName() {
    TownId_InitWithName(gSaveTownId, text);
}

void NameEntryMenu::storeConstellationName() {
    s32 t = MenuCtrl_GetIndex();
    if (Constellation_IsNameTaken(text, t)) {
        MenuCtrl_SetResult(0);
    }
    Constellation_SetName(text, t);
}

void NameEntryMenu::storeStatsPatternName() {
    u8 buf[0x10];
    void *p = gSaveBlancaFace.getPattern();
    Mem_Copy(text, buf, 0x10);
    ((PatternInfo *)(((Pattern *)(p))->getInfo()))->setTitleRaw((u8 *)(buf));
}

void NameEntryMenu::storeFriendField1() {
    Mem_Copy(text, FriendEntry_GetTownName(getFriendEntry()), 8);
}

void NameEntryMenu::storeFriendField2() {
    Mem_Copy(text, FriendEntry_GetPlayerName(getFriendEntry()), 8);
}

void NameEntryMenu::commitEntry() {
    s32 r = MenuCtrl_GetMode();
    if (r != 0xc && r != 0xd && r != 0xe) {
        censorText();
    }
    switch (r) {
    case 0xb: storeDesignName(); break;
    case 0xc: checkGeneralAnswer(); break;
    case 0xd: checkItemNameAnswer(); break;
    case 0xe: checkPasswordAnswer(); break;
    case 0xf: storePlayerName(); break;
    case 0x10: storeTownName(); break;
    case 0x11: break;
    case 0x12: storeConstellationName(); break;
    case 0x13: break;
    case 0x14: storeStatsPatternName(); break;
    case 0x15: break;
    case 0x16: break;
    case 0x17: break;
    case 0x18:
    case 0x19: storeFriendField1(); break;
    case 0x1a:
    case 0x1b: storeFriendField2(); break;
    }
}

void NameEntryMenu::censorText() {
    u8 *buf = text;
    u32 n = maxLength;
    EncodedString_SetRaw(&encodedText, buf, n);
    ((MsgString *)(&censorString))->fromEncoded((EncodedString *)(&encodedText), 0, 0);
    if (String_CensorTaboo(&censorString)) {
        ((EncodedString *)(&encodedText))->fromMsgString((MsgString *)(&censorString));
        StrBuf_GetBytes((StrBuf *)&encodedText, buf, n);
    }
}

BOOL NameEntryMenu::testFlags(u32 mask) {
    if ((flags & mask) != 0) {
        return TRUE;
    }
    return FALSE;
}

void NameEntryMenu::setFlags(u32 mask) {
    flags = flags | mask;
}

void NameEntryMenu::clearFlags(u32 mask) {
    flags = flags & ~mask;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_02297060) {
    HOST_OVERLAY_VAR(data_ov126_022999e0),
    HOST_OVERLAY_VAR(data_ov126_02299ad0),
    HOST_OVERLAY_VARS_END
};
