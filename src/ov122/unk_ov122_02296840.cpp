#include "ds_div.h"
#include "host_shared_calls.h"
#include "types.h"
#include "Unk_020d8c7c.h"
#include "ui/LetterRenderer.h"
#include "menu/MenuProc.h"
#include "ui/HandCursor.h"
#include "ui/ScrollKnob.h"
#include "talk/EncodedString.h"
#include "gfx/BgVramTask.h"
#include "talk/EncodedString128.h"
#include "menu/MenuCursor.h"
#include "menu/MenuScrollKnob.h"
#include "talk/MsgString.h"
#include "talk/MsgString129.h"
#include "ui/LabelString.h"
#include "menu/Keyboard.h"
#include "menu/PopupChoiceMenu.h"
#include "menu/MenuBottomButtons.h"
#include "menu/MenuErrorMessage.h"
#include "sys/ProcProfile.h"
#include "menu/MenuTabBar.h"
#include "player/PlayerData.h"
#include "player/PlayerInventory.h"
#include "ui/LetterLayout.h"
#include "ui/AddresseePageArg.h"
#include "item/LetterView.h"
#include "nitro/gxoam.h"
#include "text/Unk_02050288.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02051218.h"
#include "proto/main/unk_020501d4.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_0206cbdc.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov002/unk_ov002_022025cc.h"
#include "proto/ov095/unk_02292360.h"
#include "proto/ov122/unk_ov122_02296840.h"
#include "proto/main/unk_02097444.h"

class EncodedString;




















class LetterWriteMenu;
typedef void (LetterWriteMenu::*Unk_ov122_0229a1b8_Fn)();

extern "C" {
extern u16 gPad[];
extern u8 gU8None;
BOOL EncodedString_SetRaw(StrBuf *buf, const void *src, s32 len);

void PopupChoice_Close(PopupChoiceMenu *p, s32 x);
void PopupChoice_OpenAddresseePage(PopupChoiceMenu *p, AddresseePageArg a, s32 x);
void PopupChoice_DecideAddressee(PopupChoiceMenu *p, u32 x);
void PopupChoice_Draw(PopupChoiceMenu *p);
BOOL PopupChoice_TickDecideDelay(PopupChoiceMenu *p);
BOOL PopupChoice_MoveCursor(PopupChoiceMenu *p, s32 a, u8 *pos, u32 n);
void PopupChoice_ForceClose(PopupChoiceMenu *p);
void PopupChoice_Update(PopupChoiceMenu *p);
void PopupChoice_LoadChoiceBg(PopupChoiceMenu *p);
}

class LetterWriteMenu : public MenuProc {
public:
    LetterWriteMenu()
        : keyboard(), renderer(), scrollKnob(), cursor(), censorString(), encodedText(),
          addresseeMenu(), bottomButtons(), errorMessage() {}

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
    void censorLetter();
    void censorField(u8 *src, u32 n);
    void storeLetterDefaults();
    void closeAddresseeList();
    void openAddresseePage(u32 a);
    void moveCursorToPopupRow();
    void refreshCursor();
    void releaseCursor();
    void pressCursor();
    void snapCursor();
    void moveCursorTo(s32 a, s32 b);
    void moveCursorToTarget();
    void hideCursor();
    void showCursor();
    void openDialog(u32 i);
    void playErrorSe();
    void scrollToCaret();
    void updateScroll();
    BOOL isScrolling();
    void setScrollTarget(s32 v);
    void setScroll(s32 v);
    void scrollByPad();
    void dragScrollKnob();
    BOOL touchScrollKnob();
    void setCursorIndex(u32 v);
    u8 getFieldCursor();
    u32 getFieldCapacity();
    u8 *getFieldBuffer();
    u8 *getPartText();
    BOOL navigateText(u32 pad, s32 flag);
    void deleteSelection();
    void clearSelection();
    BOOL hasSelection();
    u8 getCharBeforeCursor();
    void updateCaretPos();
    void updateCaretPosSignature();
    void updateCaretPosBody();
    void updateCaretPosGreeting();
    void setCaretFromPoint(s32 a, s32 b, s32 c);
    BOOL dragSelection();
    void endTouch();
    BOOL touchTextArea();
    u8 hitTestSignature(u32 *p);
    void moveCaretToSignature();
    u8 hitTestBodyLine(s32 idx, u32 *p);
    void moveCaretToBody(s32 flag);
    u8 hitTestGreeting(s32 a, u8 *p);
    void moveCaretToGreeting();
    void resetTextCursor();
    void enterAddresseeButtons();
    void enterAddresseeTouch();
    void enterDialogButtons();
    void enterDialogTouch();
    void showMessage(u8 a, s32 b);
    void resumeInput();
    void startButtonInput();
    void startTouchInput();
    BOOL tryStartFinish();
    BOOL tryCopyButton();
    BOOL tryPasteButton();
    BOOL toggleTextFocus();
    BOOL tryBackspaceButton();
    BOOL tryPressKey();
    void mainAct1A();
    void mainAct19();
    void mainAct18();
    void mainAct17();
    void mainAct16();
    void mainAct15();
    void mainAct14();
    void mainAct13();
    void mainAct12();
    void mainAct11();
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
    void mainAct06();
    s32 pressKeyCode(s32 key);
    void paste();
    void copy();
    void askOpenList();
    void askFinish();
    void closeKeyboard();
    BOOL insertChar(u32 key);
    BOOL insertCharRaw(u32 a, u32 b);
    BOOL applyModifierKey(u32 key);
    BOOL backspace(BOOL flag);
    s32 touchKey();
    void mainAct05();
    void mainAct04();
    void mainAct03();
    void mainAct02();
    void mainAct01();
    void mainAct00();
    void refreshKeys();
    void redrawText(u32 a, u32 b);
    void showFinishDialog();
    void setupDialogButtons();
    void loadKeyboardObjGfx();
    void loadBg();
    void postStateUpdate();
    void preStateUpdate();
    void postInputUpdate();
    void preInputUpdate();
    void releaseResources();
    void init();
    void transitionAct0E();
    void transitionAct0D();
    void transitionAct0C();
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
    void forceClose();
    BOOL requestTab(s32 a);
    BOOL checkForcedClose();
    void runMainState();

    /* 0x91 */ u8 unk_91[3];
    /* 0x94 */ s32 keyboardSlideY;
    /* 0x98 */ s32 buttonsSlideY;
    /* 0x9c */ s32 caretX;
    /* 0xa0 */ s32 caretY;
    /* 0xa4 */ s32 lengthGauge;
    /* 0xa8 */ u16 flags;
    /* 0xaa */ u8 editPart;
    /* 0xab */ u8 caretBlinkTimer;
    /* 0xac */ u8 caretIndex;
    /* 0xad */ u8 selectionStart;
    /* 0xae */ u8 selectionEnd;
    /* 0xaf */ u8 lastTickScrollY;
    /* 0xb0 */ u8 dragStartTouchY;
    /* 0xb1 */ u8 dragStartScrollY;
    /* 0xb2 */ u8 scrollY;
    /* 0xb3 */ u8 scrollTargetY;
    /* 0xb4 */ u8 returnState;
    /* 0xb5 */ u8 nextTransitionState;
    /* 0xb6 */ u8 choiceIndex;
    /* 0xb7 */ u8 addresseePage;
    /* 0xb8 */ u8 dialogId;
    /* 0xb9 */ u8 unk_b9[3];
    /* 0xbc */ LetterView *letter;
    /* 0xc0 */ Keyboard keyboard;
    /* 0x3c7c */ LetterRenderer renderer;
    /* 0x3e8c */ MenuScrollKnob scrollKnob;
    /* 0x3ed4 */ MenuCursorBuf0 cursor;
    /* 0x3f38 */ MsgString129 censorString;
    /* 0x3fcc */ EncodedString128 encodedText;
    /* 0x405c */ u8 greetingBuf[0x28];
    /* 0x4084 */ u8 partTextBuf[0x80];
    /* 0x4104 */ PopupChoiceMenu addresseeMenu;
    /* 0x43f8 */ MenuBottomButtons bottomButtons;
    /* 0x455c */ MenuErrorMessage errorMessage;
};

extern "C" const u8 data_ov122_0229a004[4] = {3, 4, 0, 0};

extern "C" const u16 data_ov122_0229a010[6] = {0x27, 0x29, 0x29, 0x27, 0x2a, 0};

extern "C" ProcProfile data_ov122_0229a130 = {(void *(*)())LetterWriteMenu_Create, 0xa5, 0xa9};

extern "C" const u8 data_ov122_0229a008[8] = {0, 9, 9, 3, 4, 0, 0, 0};

extern "C" u32 data_ov122_0229a180[12] = {0x006880b4, 0x0000a0c0, 0x206880e4, 0x0000a0c0, 0x006800c4, 0x0000a0e0, 0x006800cc, 0x0000a0e0,
                                          0x006800d4, 0x0000a0e0, 0x006800dc, 0xffffa0e0};

extern "C" u32 data_ov122_0229a030[2] = {0x802a40e6, 0xffffc0c1};

#define C LetterWriteMenu

static inline BOOL Unk_ov122_02298b70_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" LetterWriteMenu *LetterWriteMenu_Create() { return new LetterWriteMenu(); }

BOOL LetterWriteMenu::onCreate() {
    init();
    setTransitionState(0);
    setPhase(1);
    return TRUE;
}

BOOL LetterWriteMenu::onDelete() {
    MenuTabBar *t = (MenuTabBar *)ProcBase_GetParent(this);
    t->onTabMenuClosed();
    t->showTabs();
    releaseResources();
    return TRUE;
}

BOOL LetterWriteMenu::onDraw() {
    PopupChoice_Draw(&addresseeMenu);
    if (testFlags(1)) {
        s32 p = keyboardSlideY + 0x60;
        Oam_DrawCell(1, (GXOamAttr *)data_ov122_0229a180, 0x80, p - 0x10, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        Keyboard_Draw(&keyboard, 0x80, p, 1);
        Shared_Keyboard_DrawCopyPasteKeys(&keyboard, 0x80, p);
        if (MenuCtrl_IsButtons()) {
            Oam_DrawObj(1, data_ov122_0229a030, 0x80, p, -1, 1, 0);
        }
        Keyboard_DrawLengthGaugeAt(&keyboard, 0x80, p, lengthGauge);
    }
    if (isScrolling()) {
        updateScroll();
        Gfx2d_SetLayerOffset(4, 0, scrollY);
        Gfx2d_SetLayerOffset(3, 0, scrollY);
        if (scrollY > 0x40) {
            if (!testFlags(0x20)) {
                setFlags(0x20);
                Gfx2d_EnableSubWindows(1);
                Gfx2d_SetSubWin0Planes(0x1d, 1);
                Gfx2d_SetSubWinOutPlanes(0x1f);
                Gfx2d_SetWindowRect(2, 0, 0xb0, 0xfe, 0xc0);
            }
        } else if (testFlags(0x20)) {
            clearFlags(0x20);
            Gfx2d_DisableSubWindows(1);
        }
    }
    if (testFlags(1)) {
        scrollKnob.moveTo(0x64, keyboardSlideY - 0x58 + (scrollY >> 1));
        s32 t = ((MenuScrollKnob *)(&scrollKnob))->getGripX();
        Shared_Keyboard_SetTextFieldPos(&keyboard, t, ((MenuScrollKnob *)(&scrollKnob))->getGripY());
        scrollKnob.draw();
    }
    if (MenuCtrl_IsButtons()) {
        if (testFlags(0x200)) {
            s32 t = ((MenuScrollKnob *)(&scrollKnob))->getGripX();
            ((MenuCursorBase *)(&cursor))->warpTo(t, ((MenuScrollKnob *)(&scrollKnob))->getGripY());
        }
        ((MenuCursorBase *)(&cursor))->drawWrapped();
    }
    if (testFlags(1)) {
        bottomButtons.drawAt(keyboardSlideY);
    }
    if (testFlags(2)) {
        ((MenuBottomButtons *)(&bottomButtons))->drawAt(buttonsSlideY);
    }
    if (testFlags(4)) {
        s32 a = caretX;
        s32 b = caretY - scrollY;
        caretBlinkTimer = caretBlinkTimer + 1;
        if ((caretBlinkTimer & 0x10) != 0) {
            Keyboard_DrawCaret(&keyboard, a, b, 3);
        }
    }
    return TRUE;
}

BOOL LetterWriteMenu::execTransition() {
    static Unk_ov122_0229a1b8_Fn tbl[15] = {
        &LetterWriteMenu::transitionAct00, &LetterWriteMenu::transitionAct01,
        &LetterWriteMenu::transitionAct02, &LetterWriteMenu::transitionAct03,
        &LetterWriteMenu::transitionAct04, &LetterWriteMenu::transitionAct05,
        &LetterWriteMenu::transitionAct06, &LetterWriteMenu::transitionAct07,
        &LetterWriteMenu::transitionAct08, &LetterWriteMenu::transitionAct09,
        &LetterWriteMenu::transitionAct0A, &LetterWriteMenu::transitionAct0B,
        &LetterWriteMenu::transitionAct0C, &LetterWriteMenu::transitionAct0D,
        &LetterWriteMenu::transitionAct0E};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}

void LetterWriteMenu::runMainState() {
    static Unk_ov122_0229a1b8_Fn tbl[27] = {
        &LetterWriteMenu::mainAct00, &LetterWriteMenu::mainAct01,
        &LetterWriteMenu::mainAct02, &LetterWriteMenu::mainAct03,
        &LetterWriteMenu::mainAct04, &LetterWriteMenu::mainAct05,
        &LetterWriteMenu::mainAct06, &LetterWriteMenu::mainAct07,
        &LetterWriteMenu::mainAct08, &LetterWriteMenu::mainAct09,
        &LetterWriteMenu::mainAct0A, &LetterWriteMenu::mainAct0B,
        &LetterWriteMenu::mainAct0C, &LetterWriteMenu::mainAct0D,
        &LetterWriteMenu::mainAct0E, &LetterWriteMenu::mainAct0F,
        &LetterWriteMenu::mainAct10, &LetterWriteMenu::mainAct11,
        &LetterWriteMenu::mainAct12, &LetterWriteMenu::mainAct13,
        &LetterWriteMenu::mainAct14, &LetterWriteMenu::mainAct15,
        &LetterWriteMenu::mainAct16, &LetterWriteMenu::mainAct17,
        &LetterWriteMenu::mainAct18, &LetterWriteMenu::mainAct19,
        &LetterWriteMenu::mainAct1A};
    (this->*tbl[mainState])();
}

BOOL LetterWriteMenu::execMain() {
    if (checkForcedClose()) {
        return TRUE;
    }
    preInputUpdate();
    runMainState();
    postInputUpdate();
    return TRUE;
}

BOOL LetterWriteMenu::execPhase3() { return TRUE; }

BOOL LetterWriteMenu::execPhase4() { return TRUE; }

BOOL LetterWriteMenu::execClosed() {
    storeLetterDefaults();
    ProcBase_RequestDelete(this);
    return TRUE;
}

BOOL LetterWriteMenu::checkForcedClose() {
    MenuCtrl_TickForceClose();
    if (MenuCtrl_IsForceCloseDue()) {
        switch (mainState) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 6:
        case 9:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
            forceClose();
            return TRUE;
        case 5:
        case 7:
        case 8:
        case 10:
            break;
        }
    }
    return FALSE;
}

BOOL LetterWriteMenu::requestTab(s32 a) {
    MenuTabBar *r6 = (MenuTabBar *)ProcBase_GetParent(this);
    if (a != -1 && a != 8) {
        u32 r7 = MenuCtrl_GetSavedSlot();
        r6->selectTab((u8)a);
        MenuCtrl_SetSavedSlot(r7);
        transitionState = 2;
        setPhase(1);
        return TRUE;
    }
    return FALSE;
}

void LetterWriteMenu::forceClose() {
    ((MenuTabBar *)(ProcBase_GetParent(this)))->selectTab(7);
    setScrollTarget(0);
    clearFlags(4);
    transitionState = 0xd;
    setPhase(1);
    hideCursor();
    censorLetter();
}

void LetterWriteMenu::transitionAct00() {
    LetterWriteMenu_SetupBgLayers();
    loadBg();
    Shared_Keyboard_RestoreLastPage(&keyboard, 6);
    Keyboard_EndFrame(&keyboard, 6);
    beginSubSlideIn(0xb, 0, 0, 0x30);
    Gfx2d_ShowLayer(6);
    Gfx2d_ShowLayer(4);
    Gfx2d_ShowLayer(3);
    applySlideOffset(6, 0, 0);
    applySlideOffset(4, 0, -16);
    applySlideOffset(3, 0, -16);
    loadKeyboardObjGfx();
    setupDialogButtons();
    setFlags(1);
    keyboardSlideY = getSlideOffsetY();
    setTransitionState(1);
}

void LetterWriteMenu::transitionAct01() {
    if (stepSlideIn(0)) {
        setPhase(2);
        resetTextCursor();
        resumeInput();
    }
    applySlideOffset(6, 0, 0);
    applySlideOffset(4, 0, -16);
    applySlideOffset(3, 0, -16);
    keyboardSlideY = getSlideOffsetY();
}

void LetterWriteMenu::transitionAct02() {
    beginSubSlideOut(3, 0, 0, 0x30);
    applySlideOffset(4, 0, 0);
    applySlideOffset(3, 0, 0);
    setTransitionState(3);
}

void LetterWriteMenu::transitionAct03() {
    if (stepSlideOut(0)) {
        Gfx2d_HideLayer(4);
        Gfx2d_HideLayer(3);
        Gfx2d_SetLayerOffset(4, 0, 0);
        Gfx2d_SetLayerOffset(3, 0, 0);
        setPhase(5);
    } else {
        applySlideOffset(4, 0, 0);
        applySlideOffset(3, 0, 0);
        buttonsSlideY = getSlideOffsetY();
    }
}

void LetterWriteMenu::transitionAct04() {
    if (testFlags(0x20) == 0) {
        beginSubSlideOut(8, 0, 0, 0x30);
        applySlideOffset(6, 0, 0);
        transitionState = 5;
    } else {
        setScrollTarget(0);
    }
}

void LetterWriteMenu::transitionAct05() {
    if (stepSlideOut(0)) {
        Gfx2d_HideLayer(6);
        Gfx2d_SetLayerOffset(6, 0, 0);
        clearFlags(1);
        transitionState = nextTransitionState;
    } else {
        applySlideOffset(6, 0, 0);
        keyboardSlideY = getSlideOffsetY();
    }
}

void LetterWriteMenu::transitionAct06() {
    if (isScrolling() == 0) {
        showFinishDialog();
        setFlags(2);
        buttonsSlideY = 0xc0;
        transitionState = 7;
    }
}

void LetterWriteMenu::transitionAct07() {
    if (buttonsSlideY > 0x20) {
        buttonsSlideY = buttonsSlideY - 0x20;
    } else {
        buttonsSlideY = 0;
        setPhase(2);
        if (MenuCtrl_IsTouch()) {
            enterDialogTouch();
        } else {
            enterDialogButtons();
        }
    }
}

void LetterWriteMenu::transitionAct08() {
    buttonsSlideY = 0;
    transitionState = 9;
}

void LetterWriteMenu::transitionAct09() {
    if (buttonsSlideY < 0xa0) {
        buttonsSlideY = buttonsSlideY + 0x20;
    } else {
        clearFlags(2);
        transitionState = 0xa;
    }
}

void LetterWriteMenu::transitionAct0A() {
    Shared_Keyboard_Reload(&keyboard, 6);
    Gfx2d_SetLayerPriority(6, 1);
    beginSubSlideIn(8, 0, 0, 0x30);
    Gfx2d_ShowLayer(6);
    applySlideOffset(6, 0, 0);
    setupDialogButtons();
    setFlags(1);
    keyboardSlideY = getSlideOffsetY();
    transitionState = 0xb;
}

void LetterWriteMenu::transitionAct0B() {
    if (stepSlideIn(0)) {
        resetTextCursor();
        setPhase(2);
        resumeInput();
    }
    applySlideOffset(6, 0, 0);
    keyboardSlideY = getSlideOffsetY();
}

void LetterWriteMenu::transitionAct0C() {
    addresseePage = 0;
    PopupChoice_LoadChoiceBg(&addresseeMenu);
    openAddresseePage(1);
    setPhase(2);
}

void LetterWriteMenu::transitionAct0D() {
    if (isScrolling() == 0) {
        beginSubSlideOut(0xb, 0, 0, 0x30);
        applySlideOffset(6, 0, 0);
        applySlideOffset(4, 0, 0);
        applySlideOffset(3, 0, 0);
        setTransitionState(0xe);
    }
}

void LetterWriteMenu::transitionAct0E() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(6);
        Gfx2d_ResetLayer(4);
        Gfx2d_ResetLayer(3);
        setPhase(5);
    } else {
        applySlideOffset(6, 0, 0);
        applySlideOffset(4, 0, 0);
        applySlideOffset(3, 0, 0);
        keyboardSlideY = getSlideOffsetY();
        buttonsSlideY = keyboardSlideY;
    }
}

void LetterWriteMenu::init() {
    letter = (LetterView *)MenuCtrl_GetArg();
    Keyboard_Init(&keyboard, 1);
    ((LetterRenderer *)(&renderer))->setLayer(3);
    renderer.loadRecipientName(letter);
    setScroll(0x10);
    setScrollTarget(0x10);
    flags = 0;
    ((ScrollKnob *)(&scrollKnob))->setState(1);
    ((PopupChoiceMenu *)(&addresseeMenu))->init(6, 1, (const char *)(0));
    ((PopupChoiceMenuBody *)(&addresseeMenu))->buildAddresseeList();
    lengthGauge = 0;
    if (Letter_IsBottle(letter)) {
        Keyboard_SetAltWriteLayout(&keyboard);
        setFlags(0x10);
    }
}

void LetterWriteMenu::releaseResources() {
    Keyboard_Shutdown(&keyboard);
    ((LetterRenderer *)(&renderer))->release();
    PopupChoice_ForceClose(&addresseeMenu);
    ((MenuBottomButtons *)(&bottomButtons))->freeTexts();
}

void LetterWriteMenu::preInputUpdate() {
    preStateUpdate();
    scrollKnob.update();
    cursor.update();
}

void LetterWriteMenu::postInputUpdate() {
    ((LetterRenderer *)(&renderer))->redraw();
    Keyboard_EndFrame(&keyboard, 6);
    Shared_PopupChoice_Update(&addresseeMenu);
    postStateUpdate();
}

void LetterWriteMenu::preStateUpdate() { ((MenuBottomButtons *)(&bottomButtons))->freeTexts(); }

void LetterWriteMenu::postStateUpdate() {
    if (testFlags(0x1000)) {
        u32 n = getFieldCapacity();
        lengthGauge = DS_DIV(Text_GetLength(getFieldBuffer(), n) * 0x1f, (s32)n);
        if (lengthGauge > 0x1f) {
            lengthGauge = 0x1f;
        }
        clearFlags(0x1000);
    }
}

extern "C" void LetterWriteMenu_SetupBgLayers() {
    Gfx2d_SetLayerPriority(6, 1);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
    Gfx2d_SetLayerPriority(4, 3);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
    Gfx2d_SetLayerPriority(3, 3);
    Gfx2d_SetLayerControl(3, 0, 0, 0);
}

void LetterWriteMenu::loadBg() {
    Heap *h = gCurrentHeap;
    Gfx2d_LoadPaletteFile("menu/chat2/b_cht_bg.bpl", h, 6, 1, 1, 9);
    Keyboard_LoadScreenFile(&keyboard, "menu/chat2/b_key0.bsc");
    refreshKeys();
    Keyboard_LoadScreenNow(&keyboard, 6);
    Gfx2d_LoadCharFile("menu/chat2/b_cht.bch", h, 6, 0x13d, 0x13d, 0x1e9);
    Menu_LoadPaperBg(Letter_GetPaper(letter), 4);
    ((LetterRenderer *)(&renderer))->loadLetterScreen(3);
    redrawText(1, 1);
    ((LetterRenderer *)(&renderer))->redraw();
}

void LetterWriteMenu::loadKeyboardObjGfx() { Keyboard_LoadObjGfx(&keyboard); }

void LetterWriteMenu::setupDialogButtons() {
    if (testFlags(0x10)) {
        ((MenuBottomButtons *)(&bottomButtons))->setLayoutConfirm();
    } else {
        ((MenuBottomButtons *)(&bottomButtons))->setLayoutChangeAddressee();
    }
}

void LetterWriteMenu::showFinishDialog() {
    ((MenuBottomButtonsBody *)(&bottomButtons))->setLayoutYesNo07(0x22);
    ((MenuBottomButtonsBody *)(&bottomButtons))->showTitleLayer2();
}

void LetterWriteMenu::redrawText(u32 a, u32 b) {
    u32 lo;
    u32 n;
    u32 flag;
    setFlags(0x1000);
    if (a != 0) {
        renderer.setGreeting(letter, greetingBuf);
        renderer.setBody(letter->body, b);
        renderer.setSignature(letter->signature);
    } else {
        switch (editPart) {
        case 0:
        case 1:
            renderer.setGreeting(letter, greetingBuf);
            break;
        case 2:
            renderer.setBody(letter->body, b);
            break;
        case 3:
            renderer.setSignature(letter->signature);
            break;
        }
    }
    if (hasSelection()) {
        flag = 0;
        u32 y = selectionEnd;
        u32 x = selectionStart;
        if (x > y) {
            lo = y;
            n = x - y;
        } else {
            lo = x;
            n = y - x;
        }
    } else {
        flag = 1;
        n = Shared_Keyboard_GetTypedRunLength(&keyboard);
        if (n != 0) {
            lo = caretIndex - n;
        }
    }
    if (n != 0) {
        switch (editPart) {
        case 0:
            renderer.highlightGreeting(lo, n, flag);
            break;
        case 1:
            lo += letter->namePos + ((LetterRenderer *)(&renderer))->getRecipientNameLength();
            renderer.highlightGreeting(lo, n, flag);
            break;
        case 2:
            ((LetterLayout *)(&renderer))->highlightBodyRange(lo, n, flag);
            break;
        case 3:
            LetterLayout_HighlightSignature(&renderer, lo, n, flag);
            break;
        }
    }
    refreshKeys();
}

void LetterWriteMenu::refreshKeys() {
    if (editPart == 2) {
        u8 c = caretIndex;
        if (Shared_Keyboard_InsertCharMultiline(&keyboard, letter->body, 0x86, &c, 0x80, 0x28, 4, 0x96, 1, 1)) {
            Shared_Keyboard_EnableKey(&keyboard, 0);
        } else {
            Keyboard_DisableKey(&keyboard, 0);
        }
    } else {
        Keyboard_DisableKey(&keyboard, 0);
    }
    if (hasSelection()) {
        Shared_Keyboard_EnableKey(&keyboard, 0xb);
    } else {
        Keyboard_DisableKey(&keyboard, 0xb);
    }
    if (testFlags(0x400)) {
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

void C::mainAct00() {
    if (checkSwitchToButtons(1)) {
        startButtonInput();
        return;
    }
    BOOL hit = FALSE;
    if (Keyboard_UpdatePressedKey(&keyboard)) {
        hit = TRUE;
    }
    if (Unk_ov122_02298b70_Both()) {
        s32 x = gTouchCurX;
        s32 y = gTouchCurY;
        if (((MenuBottomButtonsBody *)(&bottomButtons))->isTouched(9)) {
            askFinish();
            return;
        }
        if (!testFlags(0x10)) {
            if (((MenuBottomButtonsBody *)(&bottomButtons))->isTouched(0)) {
                askOpenList();
                return;
            }
        }
        if (Keyboard_TouchPageTab(&keyboard)) {
            Keyboard_SetMode(&keyboard, 8, 6, 1);
            redrawText(0, 1);
            return;
        }
        if (y < 0x48) {
            if (x < 0xe0) {
                if (touchTextArea()) {
                    setMainState(3);
                    Shared_Keyboard_ResetTypedRun(&keyboard);
                    redrawText(1, 1);
                    return;
                }
            } else {
                if (touchScrollKnob()) {
                    ((MenuScrollKnob *)(&scrollKnob))->grab();
                    setMainState(2);
                    clearSelection();
                    redrawText(1, 1);
                    return;
                }
            }
        }
        if (y >= 0x48) {
            if (!hit) {
                s32 r = touchKey();
                if (r == 0) {
                } else if (r == 1) {
                    setMainState(1);
                }
            }
        }
    }
}

void C::mainAct01() {
    if (gTouchHeld == 0) {
        setMainState(0);
    } else if (Shared_Keyboard_TickKeyRepeat(&keyboard)) {
        s32 t = Keyboard_GetPressedKey(&keyboard);
        s32 h = Keyboard_GetKeyCode(&keyboard, t, 8);
        pressKeyCode(h);
        Shared_Keyboard_HighlightKey(&keyboard, t);
    }
}

void C::mainAct02() {
    caretBlinkTimer = 0;
    if (gTouchHeld == 0) {
        endTouch();
        ((MenuScrollKnob *)(&scrollKnob))->release();
        startTouchInput();
    } else {
        dragScrollKnob();
    }
}

void C::mainAct03() {
    BOOL r;
    if (gTouchHeld == 0) {
        setMainState(0);
        if (selectionStart == selectionEnd) {
            clearFlags(8);
        }
        r = TRUE;
    } else {
        r = dragSelection();
        if (r) {
            Snd_PlaySe(0x15);
        }
    }
    if (r) {
        scrollToCaret();
        redrawText(0, 1);
    }
}

void C::mainAct04() {
    if (checkSwitchToButtons(1)) {
        enterDialogButtons();
    } else if (Unk_ov122_02298b70_Both()) {
        if (((MenuBottomButtonsBody *)(&bottomButtons))->isTouched(3)) {
            openDialog(3);
        } else if (((MenuBottomButtonsBody *)(&bottomButtons))->isTouched(4)) {
            openDialog(4);
        }
    }
}

void C::mainAct05() {
    if (MenuCtrl_IsForceCloseDue()) {
        setFlags(0x2000);
        closeAddresseeList();
    } else if (checkSwitchToButtons(1)) {
        enterAddresseeButtons();
    } else if (Unk_ov122_02298b70_Both()) {
        s32 t = ((PopupChoiceMenuBody *)(&addresseeMenu))->hitTestRow(gTouchCurX, gTouchCurY);
        if (t >= 0) {
            PopupChoice_DecideAddressee(&addresseeMenu, t);
            choiceIndex = ((PopupChoiceMenuBody *)(&addresseeMenu))->pickAddressee(addresseePage, (u8)t);
            setMainState(0x17);
        } else {
            closeAddresseeList();
        }
    }
}

s32 C::touchKey() {
    Shared_Keyboard_ClearHighlight(&keyboard);
    s32 t = Shared_Keyboard_TouchKey(&keyboard, gTouchCurX, gTouchCurY);
    if (t == -1) {
        return 0;
    }
    s32 h = Keyboard_GetKeyCode(&keyboard, t, 8);
    s32 r = pressKeyCode(h);
    Shared_Keyboard_HighlightKey(&keyboard, t);
    Keyboard_StartKeyRepeat(&keyboard);
    return r;
}

BOOL C::backspace(BOOL flag) {
    if (hasSelection()) {
        Shared_Keyboard_ResetTypedRun(&keyboard);
        Snd_PlaySe(0x35);
    } else {
        u8 a = caretIndex;
        if (a != 0) {
            selectionStart = a;
            selectionEnd = caretIndex - 1;
            Snd_PlaySe(0x35);
        } else {
            u8 *q = getPartText();
            u8 m = editPart;
            if ((m == 0 && letter->namePos == 0) || (m == 1 && letter->namePos == 0x18) || q[0] == 0) {
                if (flag) {
                    playErrorSe();
                }
                return FALSE;
            }
            selectionStart = 0;
            selectionEnd = 1;
            Snd_PlaySe(0x35);
        }
    }
    deleteSelection();
    redrawText(0, 1);
    updateCaretPos();
    return TRUE;
}

BOOL C::applyModifierKey(u32 key) {
    s32 p = getCharBeforeCursor();
    if (p == 0) {
        return FALSE;
    }
    switch (key) {
    case 0x103:
        p = Keyboard_ModifyCharKey103(&keyboard, p);
        break;
    case 0x104:
        p = Shared_Keyboard_ModifyCharKey104(&keyboard, p);
        break;
    case 0x105:
        p = Keyboard_ModifyCharKey105(&keyboard, p);
        break;
    }
    if (p == 0) {
        return FALSE;
    }
    u8 v = getFieldCursor();
    u8 *q = getFieldBuffer();
    u32 sz = getFieldCapacity();
    if (!Shared_Keyboard_ReplaceCharBeforeCursor(&keyboard, q, p, v)) {
        return FALSE;
    }
    redrawText(0, 1);
    updateCaretPos();
    return TRUE;
}

BOOL C::insertCharRaw(u32 a, u32 b) {
    u8 v;
    v = getFieldCursor();
    u8 old = v;
    u8 *p = getFieldBuffer();
    u32 sz = getFieldCapacity();
    if (editPart == 2) {
        if (Shared_Keyboard_InsertCharMultiline(&keyboard, p, a, &v, 0x80, 0x28, 4, 0x96, 0, b)) {
            setCursorIndex(v);
            goto ok;
        }
        return FALSE;
    }
    s32 h;
    h = 0xa0;
    if (editPart != 3) {
        h = h - 0x40;
    }
    if (Keyboard_InsertChar(&keyboard, p, a, &v, sz, h, 0, 1)) {
        switch (editPart) {
        case 0:
            if (old != v) {
                letter->namePos = letter->namePos + v - old;
            }
            break;
        case 1:
            v = v - letter->namePos;
            break;
        }
        setCursorIndex(v);
        goto ok;
    }
    return FALSE;
ok:
    return TRUE;
}

BOOL C::insertChar(u32 key) {
    if (hasSelection()) {
        deleteSelection();
        Shared_Keyboard_ResetTypedRun(&keyboard);
    }
    BOOL r = insertCharRaw(key, 1);
    redrawText(0, 1);
    updateCaretPos();
    return r;
}

void C::closeKeyboard() {
    transitionState = 4;
    setPhase(1);
    setScrollTarget(0);
    clearFlags(4);
    clearSelection();
    Shared_Keyboard_ResetTypedRun(&keyboard);
    redrawText(1, 0);
    hideCursor();
}

void C::askFinish() { openDialog(1); }

void C::askOpenList() { openDialog(0); }

void C::copy() {
    if (hasSelection()) {
        u32 a = selectionEnd;
        u32 b = selectionStart;
        u32 lo, n;
        if (b > a) {
            lo = a;
            n = b - a;
        } else {
            lo = b;
            n = a - b;
        }
        Mem_Clear(partTextBuf, 0x80);
        Mem_Copy(getPartText() + lo, partTextBuf, n);
        setFlags(0x400);
        Shared_Keyboard_PlayCopySe();
        refreshKeys();
    }
}

void C::paste() {
    if (testFlags(0x400)) {
        if (hasSelection()) {
            deleteSelection();
        }
        Shared_Keyboard_ResetTypedRun(&keyboard);
        Keyboard_BeginPaste(&keyboard);
        s32 n = Text_GetLength(partTextBuf, 0x80);
        s32 i;
        for (i = 0; i < n; i++) {
            if (!insertCharRaw(partTextBuf[i], 0)) {
                if (i == 0) {
                    playErrorSe();
                }
                i = n;
            }
        }
        Keyboard_PlayPasteSe();
        redrawText(0, 1);
        updateCaretPos();
        Keyboard_EndPaste(&keyboard);
    }
}

s32 C::pressKeyCode(s32 key) {
    s32 r = 1;
    s32 t = Shared_Keyboard_HandleModeKey(&keyboard, key, 6);
    if (t != 0) {
        redrawText(0, r);
        return t;
    }
    if (Keyboard_IsControlCode(&keyboard, key)) {
        switch (key) {
        case 0x100:
            backspace(r);
            break;
        case 0x103:
        case 0x104:
        case 0x105:
            if (!applyModifierKey(key)) {
                playErrorSe();
            }
            r = 2;
            break;
        case 0x113:
            askFinish();
            r = 3;
            break;
        case 0x114:
            askOpenList();
            r = 3;
            break;
        case 0x118:
            copy();
            r = 2;
            break;
        case 0x119:
            paste();
            r = 2;
            break;
        }
    } else {
        BOOL ok = insertChar((u8)key);
        if (Keyboard_IsFull(&keyboard)) {
            showMessage(0x1c, r);
            return 4;
        }
        if (Keyboard_IsTooWide(&keyboard)) {
            showMessage(0x1c, r);
            return 4;
        }
        if (!ok) {
            playErrorSe();
        }
        if (key == 0x86) {
            r = 2;
        }
    }
    return r;
}

void C::mainAct06() {
    if (checkSwitchToTouch()) {
        startTouchInput();
        return;
    }
    u8 b = takeRepeatedKeys();
    if (testFlags(0x10) == 1) {
        if (Shared_Keyboard_PressCursorKey(&keyboard) == 0xd6) {
            if (isRepeatLeft()) {
                b &= ~0x20;
            }
        }
    }
    switch (Keyboard_MoveCursor(&keyboard, b)) {
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
    case 0:
    default:
        if (tryPressKey()) return;
        if (tryBackspaceButton()) return;
        if (toggleTextFocus()) return;
        if (tryCopyButton()) return;
        if (tryPasteButton()) return;
        if (tryStartFinish()) return;
        break;
    }
}

void LetterWriteMenu::mainAct07()
{
    if (!((MenuCursorBase *)(&cursor))->isMoving()) {
        setMainState(returnState);
        runMainState();
    }
}

void LetterWriteMenu::mainAct08()
{
    s32 r4;
    s32 t;
    s32 r;

    if (!((HandCursor *)(&cursor))->isAnimDone()) {
        return;
    }
    r4 = Shared_Keyboard_PressCursorKey(&keyboard);
    t = Keyboard_GetKeyCode(&keyboard, r4, 8);
    if (t == 0x112) {
        setMainState(0x10);
        ((MenuScrollKnob *)(&scrollKnob))->grab();
        Menu_PlayScrollGrabSe();
        if (hasSelection()) {
            clearSelection();
            redrawText(1, 1);
        } else {
            clearSelection();
        }
        setFlags(0x200);
        return;
    }
    r = pressKeyCode(t);
    if (r == 1 && (gPad[0] & 1)) {
        Keyboard_StartKeyRepeat(&keyboard);
        setMainState(9);
        Shared_Keyboard_HighlightKey(&keyboard, r4);
    } else if (r == 3) {
    } else if (r == 4) {
        Shared_Keyboard_ClearHighlight(&keyboard);
    } else {
        releaseCursor();
    }
}

void LetterWriteMenu::mainAct09()
{
    s32 r5;

    if ((gPad[0] & 1) == 0) {
        releaseCursor();
    } else if (Shared_Keyboard_TickKeyRepeat(&keyboard)) {
        r5 = Keyboard_GetPressedKey(&keyboard);
        pressKeyCode(Keyboard_GetKeyCode(&keyboard, r5, 8));
        Shared_Keyboard_HighlightKey(&keyboard, r5);
    }
}

void LetterWriteMenu::mainAct0A()
{
    if (((HandCursor *)(&cursor))->isAnimDone()) {
        refreshCursor();
        setMainState(6);
    }
}

void LetterWriteMenu::mainAct0B()
{
    if ((gPad[0] & 2) == 0) {
        setMainState(returnState);
    } else if (Shared_Keyboard_TickKeyRepeat(&keyboard)) {
        pressKeyCode(0x100);
        if (testFlags(0x100)) {
            snapCursor();
        }
    }
}

void LetterWriteMenu::mainAct0C()
{
    u32 a;
    u32 b;
    if (checkSwitchToTouch()) {
        startTouchInput();
        return;
    }
    if (navigateText(takeRepeatedKeys(), 1)) {
        if (Shared_Keyboard_GetTypedRunLength(&keyboard) || hasSelection()) {
            Shared_Keyboard_ResetTypedRun(&keyboard);
            clearSelection();
            redrawText(1, 1);
        } else {
            clearSelection();
        }
        updateCaretPos();
        snapCursor();
        refreshKeys();
        Snd_PlaySe(0xb);
    } else if (!toggleTextFocus()) {
        a = caretX;
        b = caretY;
        if (tryBackspaceButton()) {
            if (a != caretX || b != caretY) {
                snapCursor();
            }
        } else {
            if (gPad[1] & 1) {
                setMainState(0xd);
                setFlags(8);
                selectionStart = caretIndex;
                selectionEnd = caretIndex;
            }
            if (tryCopyButton()) {
                return;
            }
            if (tryPasteButton()) {
                return;
            }
            if (tryStartFinish()) {
                return;
            }
        }
    }
}

void LetterWriteMenu::mainAct0D()
{
    if ((gPad[0] & 1) == 0) {
        setMainState(0xc);
        if (selectionStart == selectionEnd) {
            clearFlags(8);
        }
    } else {
        if (navigateText(takeRepeatedKeys(), 0)) {
            selectionEnd = caretIndex;
            redrawText(0, 1);
            updateCaretPos();
            snapCursor();
            Snd_PlaySe(0x15);
        }
    }
}

void LetterWriteMenu::mainAct0E()
{
    if ((gPad[0] & 0x200) == 0) {
        setMainState(returnState);
        refreshKeys();
    }
}

void LetterWriteMenu::mainAct0F()
{
    if ((gPad[0] & 0x100) == 0) {
        setMainState(returnState);
        refreshKeys();
    }
}

void LetterWriteMenu::mainAct10()
{
    if (((ScrollKnob *)(&scrollKnob))->areAnimsDone()) {
        setMainState(0x11);
    }
}

void LetterWriteMenu::mainAct11()
{
    if ((gPad[0] & 1) == 0) {
        ((MenuScrollKnob *)(&scrollKnob))->release();
        setMainState(0x12);
        endTouch();
    } else {
        scrollByPad();
    }
}

void LetterWriteMenu::mainAct12()
{
    if (((ScrollKnob *)(&scrollKnob))->areAnimsDone()) {
        releaseCursor();
        clearFlags(0x200);
    }
}

void LetterWriteMenu::mainAct13()
{
    s32 r4;
    s32 r6;
    s32 r5;
    u32 f;

    if (checkSwitchToTouch()) {
        enterDialogTouch();
        return;
    }
    r4 = takeRepeatedKeys();
    if (gPad[1] & 1) {
        switch (choiceIndex) {
        case 0:
            openDialog(3);
            break;
        case 1:
            openDialog(4);
            break;
        }
        ((MenuCursor *)(&cursor))->setPosePress();
        return;
    }
    r6 = choiceIndex;
    if (MenuKeys_HasLeft(r4)) {
        if (choiceIndex != 0) {
            choiceIndex = *(volatile u8 *)&choiceIndex - 1;
        }
    } else if (MenuKeys_HasRight(r4)) {
        if (choiceIndex < 1) {
            choiceIndex = *(volatile u8 *)&choiceIndex + 1;
        }
    }
    r4 = choiceIndex;
    if (r6 != r4) {
        r6 = ((MenuBottomButtonsBody *)(&bottomButtons))->getTargetX(data_ov122_0229a004[r4]);
        r5 = ((MenuBottomButtonsBody *)(&bottomButtons))->getTargetY(data_ov122_0229a004[r4]);
        moveCursorTo(r6, r5);
    } else {
        f = gPad[1];
        if (f & 8) {
            hideCursor();
            openDialog(3);
        } else if (f & 2) {
            hideCursor();
            openDialog(4);
        }
    }
}

void LetterWriteMenu::mainAct14()
{
    u32 f;

    if (MenuCtrl_IsForceCloseDue()) {
        setFlags(0x2000);
        closeAddresseeList();
    } else if (checkSwitchToTouch()) {
        enterAddresseeTouch();
    } else {
        if (PopupChoice_MoveCursor(&addresseeMenu, takeRepeatedKeys(), &choiceIndex, 0)) {
            moveCursorToPopupRow();
        }
        f = gPad[1];
        if (f & 1) {
            ((MenuCursor *)(&cursor))->setPosePress();
            setMainState(0x15);
        } else if (f & 2) {
            closeAddresseeList();
        }
    }
}

void LetterWriteMenu::mainAct15()
{
    if (((HandCursor *)(&cursor))->isAnimDone()) {
        PopupChoice_DecideAddressee(&addresseeMenu, choiceIndex);
        choiceIndex = ((PopupChoiceMenuBody *)(&addresseeMenu))->pickAddressee(addresseePage, choiceIndex);
        setMainState(0x17);
    }
}

void LetterWriteMenu::mainAct16()
{
    if (((PopupChoiceMenuBody *)(&addresseeMenu))->isOpen()) {
        if (MenuCtrl_IsButtons()) {
            enterAddresseeButtons();
        } else {
            enterAddresseeTouch();
        }
    }
}

void LetterWriteMenu::mainAct17()
{
    if (PopupChoice_TickDecideDelay(&addresseeMenu)) {
        PopupChoice_Close(&addresseeMenu, 0);
        setMainState(0x18);
        hideCursor();
    }
}

void LetterWriteMenu::mainAct18()
{
    s32 r;

    if (!((PopupChoiceMenuBody *)(&addresseeMenu))->isClosed()) {
        return;
    }
    r = ((PopupChoiceMenuBody *)(&addresseeMenu))->applyAddressee(letter, choiceIndex);
    switch (r) {
    case 1:
        renderer.loadRecipientName(letter);
        redrawText(1, 0);
        transitionState = 0xa;
        setPhase(1);
        break;
    case 2:
        addresseePage = addresseePage + 1;
        if (addresseePage >= ((PopupChoiceMenuBody *)(&addresseeMenu))->getPageCount()) {
            addresseePage = 0;
        }
        openAddresseePage(0);
        break;
    case 3:
        if (testFlags(0x2000)) {
            forceClose();
        } else {
            transitionState = 0xa;
            setPhase(1);
        }
        break;
    default:
        transitionState = 0xa;
        setPhase(1);
        break;
    }
}

void LetterWriteMenu::mainAct19()
{
    s32 a;
    s32 b;
    s32 c;

    if (((HandCursor *)(&cursor))->getAnim()) {
        if (!((HandCursor *)(&cursor))->isAnimDone()) {
            return;
        }
    }
    if (((MenuBottomButtonsBody *)(&bottomButtons))->stepPress()) {
        if (!((HandCursor *)(&cursor))->getAnim()) {
            return;
        }
        a = ((MenuBottomButtonsBody *)(&bottomButtons))->getPressOffset();
        b = ((MenuBottomButtonsBody *)(&bottomButtons))->getTargetX(-1);
        c = ((MenuBottomButtonsBody *)(&bottomButtons))->getTargetY(-1);
        ((MenuCursorBase *)(&cursor))->warpTo(a + b, a + c);
        return;
    }
    switch (dialogId) {
    case 0:
        nextTransitionState = 0xc;
        closeKeyboard();
        break;
    case 1:
        nextTransitionState = 6;
        censorLetter();
        closeKeyboard();
        break;
    case 2:
        break;
    case 3:
        requestTab(0);
        break;
    case 4:
        transitionState = 8;
        setPhase(1);
        redrawText(1, 1);
        break;
    }
    hideCursor();
}

void LetterWriteMenu::mainAct1A()
{
    Keyboard_UpdatePressedKey(&keyboard);
    if (((MenuErrorMessage *)(&errorMessage))->update(1)) {
        resumeInput();
    }
}

BOOL LetterWriteMenu::tryPressKey()
{
    s32 r4;

    if ((gPad[1] & 1) == 0) {
        return FALSE;
    }
    r4 = Shared_Keyboard_PressCursorKey(&keyboard);
    if (r4 == -1) {
        return FALSE;
    }
    Keyboard_GetKeyCode(&keyboard, r4, 8);
    Shared_Keyboard_HighlightKey(&keyboard, r4);
    pressCursor();
    return TRUE;
}

BOOL LetterWriteMenu::tryBackspaceButton()
{
    if ((gPad[0] & 2) == 0) {
        return FALSE;
    }
    pressKeyCode(0x100);
    Keyboard_StartKeyRepeat(&keyboard);
    returnState = mainState;
    setMainState(0xb);
    return TRUE;
}

BOOL C::toggleTextFocus() {
    if ((gPad[1] & 0x800) == 0) return FALSE;
    if (testFlags(0x100)) {
        clearFlags(0x100);
    } else {
        setFlags(0x100);
        scrollToCaret();
    }
    if (Shared_Keyboard_IsOnButtonKey(&keyboard, -1)) {
        if (testFlags(0x100)) {
            ((MenuCursor *)(&cursor))->switchToAnim01();
            setMainState(0xc);
        } else {
            ((MenuCursor *)(&cursor))->switchToAnim07();
            setMainState(6);
        }
        moveCursorToTarget();
    } else {
        moveCursorToTarget();
    }
    return TRUE;
}

BOOL C::tryPasteButton() {
    if ((gPad[1] & 0x100) == 0) return FALSE;
    if (Keyboard_IsSlotDisabled(&keyboard, 0xc)) return FALSE;
    pressKeyCode(0x119);
    Shared_Keyboard_HighlightKey(&keyboard, 0xdc);
    snapCursor();
    returnState = mainState;
    setMainState(0xf);
    return TRUE;
}

BOOL C::tryCopyButton() {
    if ((gPad[1] & 0x200) == 0) return FALSE;
    if (Keyboard_IsSlotDisabled(&keyboard, 0xb)) return FALSE;
    pressKeyCode(0x118);
    Shared_Keyboard_HighlightKey(&keyboard, 0xdb);
    returnState = mainState;
    setMainState(0xe);
    return TRUE;
}

BOOL C::tryStartFinish() {
    if ((gPad[1] & 8) == 0) return FALSE;
    hideCursor();
    askFinish();
    return TRUE;
}

void C::startTouchInput() {
    hideCursor();
    setMainState(0);
}

void C::startButtonInput() {
    restartKeyRepeat();
    showCursor();
    setMainState(6);
}

void C::resumeInput() {
    if (MenuCtrl_IsTouch()) {
        startTouchInput();
    } else {
        startButtonInput();
    }
}

void C::showMessage(u8 a, s32 b) {
    volatile u8 buf[1];
    buf[0] = gU8None;
    buf[0] = a;
    ((MenuErrorMessage *)(&errorMessage))->openHigh((u8 *)buf, b, 0);
    setMainState(0x1a);
    hideCursor();
}

void C::enterDialogTouch() {
    hideCursor();
    setMainState(4);
}

void C::enterDialogButtons() {
    restartKeyRepeat();
    showCursor();
    s32 a = ((MenuBottomButtonsBody *)(&bottomButtons))->getTargetX(4);
    s32 b = ((MenuBottomButtonsBody *)(&bottomButtons))->getTargetY(4);
    ((MenuCursorBase *)(&cursor))->warpTo(a, b);
    choiceIndex = 1;
    setMainState(0x13);
}

void C::enterAddresseeTouch() {
    hideCursor();
    setMainState(5);
}

void C::enterAddresseeButtons() {
    restartKeyRepeat();
    showCursor();
    choiceIndex = ((PopupChoiceMenuBody *)(&addresseeMenu))->getRowCount() - 1;
    s32 a = ((PopupChoiceMenuBody *)(&addresseeMenu))->getRowX();
    s32 b = ((PopupChoiceMenuBody *)(&addresseeMenu))->getRowY(choiceIndex);
    ((MenuCursorBase *)(&cursor))->warpTo(a, b);
    ((MenuCursor *)(&cursor))->setAnimIfChanged(7);
    setMainState(0x14);
}

void C::resetTextCursor() {
    setFlags(4);
    caretX = 0x30;
    caretY = 0x40;
    editPart = 2;
    setFlags(0x1000);
    setCursorIndex(0);
    clearSelection();
    Keyboard_ResetKeyPalettes(&keyboard);
    refreshKeys();
}

void C::moveCaretToGreeting() {
    u8 r = hitTestGreeting(caretX, &editPart);
    setFlags(0x1000);
    setCursorIndex(r);
    updateCaretPosGreeting();
}

u8 C::hitTestGreeting(s32 a, u8 *p) {
    u8 out;
    Keyboard_HitTestText(&keyboard, greetingBuf, 0x28, 0xa0, (u8)(a - 0x30), &out);
    s32 e = letter->namePos;
    s32 s = e + ((LetterRenderer *)(&renderer))->getRecipientNameLength();
    s32 h = (e + s) >> 1;
    if (out < h) {
        *p = 0;
        if (out > e) out = e;
    } else {
        *p = 1;
        if (out < s) out = 0;
        else out = out - s;
    }
    return out;
}

void C::moveCaretToBody(s32 flag) {
    editPart = 2;
    setFlags(0x1000);
    if (caretY < 0x40) caretY = 0x40;
    if (caretY >= 0x80) caretY = 0x7f;
    s32 i = (caretY - 0x40) >> 4;
    s32 m = ((LetterLayout *)(&renderer))->getBodyLineCount();
    if (i > m) i = m;
    else flag = 0;
    caretY = i * 16 + 0x40;
    if (flag != 0 && caretY - scrollY < 8) {
        moveCaretToSignature();
    } else {
        u8 r = hitTestBodyLine(i, (u32 *)&caretX);
        setCursorIndex(r);
    }
}

u8 C::hitTestBodyLine(s32 idx, u32 *p) {
    s32 o = ((LetterLayout *)(&renderer))->getBodyLineStarts()[idx];
    u8 out;
    s32 t = Keyboard_HitTestText(&keyboard, letter->body + o, 0x28, 0x96, (u8)(*p - 0x30), &out);
    *p = t + 0x30;
    return (u8)(out + o);
}

void C::moveCaretToSignature() {
    editPart = 3;
    setFlags(0x1000);
    caretY = 0x88;
    u8 r = hitTestSignature((u32 *)&caretX);
    setCursorIndex(r);
}

u8 C::hitTestSignature(u32 *p) {
    u8 v = (u8)(*p - 0x30);
    s32 r4 = 0xa0 - Text_MeasureWidth(letter->signature, 0x20);
    u8 out;
    if (r4 > v) {
        out = 0;
        *p = r4 + 0x30;
    } else {
        s32 t = Keyboard_HitTestText(&keyboard, letter->signature, 0x20, 0xa0, (u8)(v - r4), &out);
        *p = r4 + (t + 0x30);
    }
    return out;
}

BOOL C::touchTextArea() {
    s32 x = gTouchCurX;
    s32 y = gTouchCurY;
    if (y < 0) return FALSE;
    if (y > 0x4f) y = 0x4f;
    y += scrollTargetY;
    if (x < 0x20 || x >= 0xe0) return FALSE;
    if (x < 0x30) x = 0x30;
    setCaretFromPoint(x, y, 1);
    setFlags(8);
    selectionStart = caretIndex;
    selectionEnd = caretIndex;
    return TRUE;
}

void C::endTouch() {
}

BOOL C::dragSelection() {
    s32 a = gTouchCurX;
    s32 b = gTouchCurY;
    u8 old = caretIndex;
    if (a < 0x30) a = 0x30;
    b += scrollTargetY;
    u8 m = editPart;
    switch (m) {
    case 0:
    case 1:
        caretX = a;
        moveCaretToGreeting();
        if (editPart != m) {
            editPart = m;
            setFlags(0x1000);
            if (m == 0) {
                setCursorIndex(letter->namePos);
            } else {
                setCursorIndex(0);
            }
            updateCaretPosGreeting();
        }
        break;
    case 2:
        caretX = a;
        caretY = b;
        moveCaretToBody(0);
        break;
    case 3:
        caretX = a;
        moveCaretToSignature();
        break;
    }
    selectionEnd = caretIndex;
    if (caretIndex != old) return TRUE;
    return FALSE;
}

void C::setCaretFromPoint(s32 a, s32 b, s32 c) {
    if (!testFlags(0x10) && b < 0x3c) {
        caretX = a;
        moveCaretToGreeting();
    } else if (b < 0x84) {
        if (b < 0x40) b = 0x40;
        else if (b >= 0x80) b = 0x7f;
        caretX = a;
        caretY = b;
        moveCaretToBody(c);
    } else {
        caretX = a;
        moveCaretToSignature();
    }
    scrollToCaret();
}

void C::updateCaretPosGreeting() {
    u32 v = caretIndex;
    if (editPart == 1) {
        s32 t = ((LetterRenderer *)(&renderer))->getRecipientNameLength();
        v += letter->namePos + t;
    }
    caretX = (u8)(Text_MeasureWidth(greetingBuf, v) + 0x30);
    caretY = 0x28;
}

void C::updateCaretPosBody() {
    s32 t = ((LetterLayout *)(&renderer))->getBodyLineOfPos(caretIndex);
    caretY = t * 16 + 0x40;
    s32 o = ((LetterLayout *)(&renderer))->getBodyLineStarts()[t];
    caretX = (u8)(Text_MeasureWidth(letter->body + o, caretIndex - o) + 0x30);
}

void C::updateCaretPosSignature() {
    u8 t = (u8)(Text_MeasureWidth(letter->signature, caretIndex) + 0x30);
    caretX = t;
    caretX = caretX + (0xa0 - Text_MeasureWidth(letter->signature, 0x20));
    caretY = 0x88;
}

void C::updateCaretPos() {
    switch (editPart) {
    case 0:
    case 1:
        updateCaretPosGreeting();
        break;
    case 2:
        updateCaretPosBody();
        break;
    case 3:
        updateCaretPosSignature();
        break;
    }
    scrollToCaret();
}

u8 C::getCharBeforeCursor() {
    if (caretIndex == 0) return 0;
    return getPartText()[caretIndex - 1];
}

BOOL C::hasSelection() {
    if (!testFlags(8) || selectionStart == selectionEnd) return FALSE;
    return TRUE;
}

void C::clearSelection() {
    selectionStart = 0;
    selectionEnd = 0;
    clearFlags(8);
}

void C::deleteSelection() {
    u32 a = selectionEnd;
    u32 b = selectionStart;
    u32 lo, hi;
    if (b > a) {
        lo = a;
        hi = b;
    } else {
        lo = b;
        hi = a;
    }
    u8 *p = getFieldBuffer();
    s32 q = getFieldCapacity();
    switch (editPart) {
    case 0:
        letter->namePos = letter->namePos - (hi - lo);
        break;
    case 1: {
        u32 o = letter->namePos;
        lo += o;
        hi += o;
        break;
    }
    }
    u8 r = (u8)Shared_Keyboard_DeleteRange(&keyboard, p, lo, hi, q);
    if (editPart == 1) {
        r = (u8)(r - letter->namePos);
    }
    setCursorIndex(r);
    clearSelection();
}

BOOL LetterWriteMenu::navigateText(u32 pad, s32 flag) {
    if (pad == 0) {
        return FALSE;
    }
    u8 mode = editPart;
    u8 idx = caretIndex;
    s32 cnt = ((LetterLayout *)(&renderer))->getBodyLineCount();
    s32 lim;
    s32 sel;
    s32 n;
    u32 saved;
    switch (mode) {
    case 0:
    case 1:
        sel = -1;
        lim = sel;
        if (MenuKeys_HasDown(pad)) {
            sel = 0;
        }
        break;
    case 2:
        sel = (caretY - 0x40) >> 4;
        lim = sel;
        if (MenuKeys_HasUp(pad)) {
            sel = sel - 1;
        } else if (MenuKeys_HasDown(pad)) {
            sel = sel + 1;
            if (sel > cnt) {
                sel = 4;
            }
        }
        break;
    case 3:
        sel = 4;
        lim = sel;
        if (MenuKeys_HasUp(pad)) {
            sel = sel - 1;
        }
        break;
    default:
        sel = 0;
        lim = sel;
        break;
    }
    saved = caretX;
    if (testFlags(0x10)) {
        if (sel == -1) {
            sel = 0;
        }
    }
    if (sel != lim) {
        if (sel == -1) {
            idx = hitTestGreeting(saved, &mode);
        } else if (sel >= 4) {
            mode = 3;
            idx = hitTestSignature(&saved);
        } else {
            mode = 2;
            idx = hitTestBodyLine(sel, &saved);
        }
    }
    if (MenuKeys_HasLeft(pad)) {
        if (idx != 0) {
            idx = idx - 1;
        } else if (mode == 1) {
            idx = letter->namePos;
            mode = 0;
        }
    } else if (MenuKeys_HasRight(pad)) {
        switch (mode) {
        case 0:
            n = letter->namePos;
            break;
        case 1:
            n = Text_GetLength(letter->greeting, 0x18) - letter->namePos;
            break;
        case 2:
            n = Text_GetLength(letter->body, 0x80);
            break;
        case 3:
            n = Text_GetLength(letter->signature, 0x20);
            break;
        }
        if (idx + 1 <= n) {
            idx = idx + 1;
        } else if (mode == 0) {
            idx = 0;
            mode = 1;
        }
    }
    if (mode != editPart && flag == 0) {
        return FALSE;
    }
    if (mode == editPart && idx == caretIndex) {
        return FALSE;
    }
    editPart = mode;
    setFlags(0x1000);
    setCursorIndex(idx);
    return TRUE;
}

u8 *LetterWriteMenu::getPartText() {
    switch (editPart) {
    case 0:
        return letter->greeting;
    case 1:
        return letter->greeting + letter->namePos;
    case 2:
        return letter->body;
    case 3:
        return letter->signature;
    default:
        return 0;
    }
}

u8 *LetterWriteMenu::getFieldBuffer() {
    switch (editPart) {
    case 0:
    case 1:
        return letter->greeting;
    case 2:
        return letter->body;
    case 3:
        return letter->signature;
    default:
        return 0;
    }
}

u32 LetterWriteMenu::getFieldCapacity() {
    switch (editPart) {
    case 0:
    case 1:
        return 0x18;
    case 2:
        return 0x80;
    case 3:
        return 0x20;
    default:
        return 0;
    }
}

u8 LetterWriteMenu::getFieldCursor() {
    if (editPart == 1) {
        return caretIndex + letter->namePos;
    }
    return caretIndex;
}

void LetterWriteMenu::setCursorIndex(u32 v) {
    caretIndex = v;
    caretBlinkTimer = 0x10;
}

BOOL LetterWriteMenu::touchScrollKnob() {
    if (((MenuScrollKnob *)(&scrollKnob))->hitTest(gTouchCurX, gTouchCurY)) {
        dragStartTouchY = gTouchCurY;
        dragStartScrollY = scrollY;
        lastTickScrollY = scrollY;
        return TRUE;
    }
    return FALSE;
}

void LetterWriteMenu::dragScrollKnob() {
    s32 n = dragStartScrollY + (((s32)(gTouchCurY - dragStartTouchY) >> 1) << 2);
    if (n < 0) {
        n = 0;
    }
    if (n > 0x58) {
        n = 0x58;
    }
    setScroll(n);
    s32 d = lastTickScrollY - n;
    if (d >= 4 || d <= -4) {
        Menu_PlayScrollTickSe();
        lastTickScrollY = n;
    }
}

void LetterWriteMenu::scrollByPad() {
    s32 n;
    s32 old = scrollY;
    n = old;
    u32 k = gPad[0];
    if (k & 0x40) {
        n = old - 4;
    } else if (k & 0x80) {
        n = old + 4;
    }
    if (n < 0) {
        n = 0;
    }
    if (n > 0x58) {
        n = 0x58;
    }
    if (n != old) {
        Menu_PlayScrollTickSe();
    }
    setScroll(n);
}

void LetterWriteMenu::setScroll(s32 v) {
    scrollY = v;
    scrollTargetY = scrollY;
    setFlags(0x800);
}

void LetterWriteMenu::setScrollTarget(s32 v) {
    scrollTargetY = v;
    setFlags(0x800);
}

BOOL LetterWriteMenu::isScrolling() { return testFlags(0x800); }

void LetterWriteMenu::updateScroll() {
    u32 b3 = scrollTargetY;
    u32 b2 = scrollY;
    if (b2 == b3) {
        clearFlags(0x800);
    } else if (b2 < b3) {
        *(volatile u8 *)&scrollY = *(volatile u8 *)&scrollY + 8;
        u32 t3 = *(volatile u8 *)&scrollTargetY;
        if (*(volatile u8 *)&scrollY > t3) {
            scrollY = t3;
        }
    } else if (b2 < 8) {
        scrollY = b3;
    } else {
        *(volatile u8 *)&scrollY = *(volatile u8 *)&scrollY - 8;
        u32 t3 = *(volatile u8 *)&scrollTargetY;
        if (*(volatile u8 *)&scrollY < t3) {
            scrollY = t3;
        }
    }
}

void LetterWriteMenu::scrollToCaret() {
    s32 v = caretY - scrollTargetY;
    if (v < 0x18) {
        setScrollTarget(scrollTargetY - (0x18 - v));
    } else if (v > 0x30) {
        setScrollTarget(scrollTargetY + (v - 0x30));
    }
}

void LetterWriteMenu::playErrorSe() { Snd_PlaySe(0x34); }

void LetterWriteMenu::openDialog(u32 i) {
    ((MenuBottomButtonsBody *)(&bottomButtons))->setSelected(data_ov122_0229a008[i]);
    dialogId = i;
    setMainState(0x19);
    Snd_PlaySe(data_ov122_0229a010[i]);
}

void LetterWriteMenu::showCursor() {
    clearFlags(0x100);
    Keyboard_ResetCursor(&keyboard);
    s32 a = Keyboard_GetCursorX(&keyboard);
    s32 b = Keyboard_GetCursorY(&keyboard);
    ((MenuCursorBase *)(&cursor))->warpTo(a, b);
    ((MenuCursor *)(&cursor))->setAnimIfChanged(1);
    refreshCursor();
}

void LetterWriteMenu::hideCursor() {
    ((MenuCursor *)(&cursor))->setAnimIfChanged(0);
    cursor.update();
}

void LetterWriteMenu::moveCursorToTarget() {
    if (testFlags(0x100)) {
        ((MenuCursorBase *)(&cursor))->moveToNear(caretX, caretY - scrollTargetY, 3, 2);
        returnState = 0xc;
    } else {
        s32 a = Keyboard_GetCursorX(&keyboard);
        s32 b = Keyboard_GetCursorY(&keyboard);
        ((MenuCursorBase *)(&cursor))->moveToNear(a, b, 3, 2);
        returnState = 6;
    }
    setMainState(7);
}

void LetterWriteMenu::moveCursorTo(s32 a, s32 b) {
    ((MenuCursorBase *)(&cursor))->moveToNear(a, b, 3, 2);
    returnState = mainState;
    setMainState(7);
}

void LetterWriteMenu::snapCursor() {
    if (testFlags(0x100)) {
        ((MenuCursorBase *)(&cursor))->warpTo(caretX, caretY - scrollTargetY);
    } else {
        s32 a = Keyboard_GetCursorX(&keyboard);
        s32 b = Keyboard_GetCursorY(&keyboard);
        ((MenuCursorBase *)(&cursor))->warpTo(a, b);
    }
    cursor.update();
}

void LetterWriteMenu::pressCursor() {
    ((MenuCursor *)(&cursor))->setPosePress();
    setMainState(8);
}

void LetterWriteMenu::releaseCursor() {
    Shared_Keyboard_ClearHighlight(&keyboard);
    ((MenuCursorBase *)(&cursor))->setPoseRelease();
    setMainState(0xa);
}

void LetterWriteMenu::refreshCursor() {
    ((MenuCursorBase *)(&cursor))->setPoseIdle();
    cursor.update();
}

void LetterWriteMenu::moveCursorToPopupRow() {
    s32 a = ((PopupChoiceMenuBody *)(&addresseeMenu))->getRowX();
    s32 b = ((PopupChoiceMenuBody *)(&addresseeMenu))->getRowY(choiceIndex);
    ((MenuCursorBase *)(&cursor))->moveToLinear(a, b, 2);
    returnState = 0x14;
    setMainState(7);
}

void LetterWriteMenu::openAddresseePage(u32 a) {
    AddresseePageArg page;
    page.v = addresseePage;
    PopupChoice_OpenAddresseePage(&addresseeMenu, page, a);
    setMainState(0x16);
}

void LetterWriteMenu::closeAddresseeList() {
    Snd_PlaySe(0x28);
    choiceIndex = 0xf;
    PopupChoice_Close(&addresseeMenu, 1);
    setMainState(0x18);
    hideCursor();
}

void LetterWriteMenu::storeLetterDefaults() {
    LetterDefaults_Store((LetterDefaults *)((PlayerInventory *)(PlayerData_GetCurrent()->getInventory()))->getUnk988(), letter);
}

void LetterWriteMenu::censorField(u8 *src, u32 n) {
    EncodedString_SetRaw((StrBuf *)&encodedText, src, n);
    ((MsgString *)(&censorString))->fromEncoded((EncodedString *)(&encodedText), 0, 0);
    if (String_CensorTaboo(&censorString)) {
        ((EncodedString *)(&encodedText))->fromMsgString((MsgString *)(&censorString));
        StrBuf_GetBytes((StrBuf *)&encodedText, src, n);
    }
}

void LetterWriteMenu::censorLetter() {
    censorField(letter->greeting, 0x18);
    censorField(letter->signature, 0x20);
    censorField(letter->body, 0x80);
}

BOOL LetterWriteMenu::testFlags(u32 mask) {
    if (flags & mask) {
        return TRUE;
    }
    return FALSE;
}

void LetterWriteMenu::setFlags(u32 mask) { flags = flags | mask; }

void LetterWriteMenu::clearFlags(u32 mask) { flags = flags & ~mask; }

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov122_02296840) {
    HOST_OVERLAY_VAR(data_ov122_0229a130),
    HOST_OVERLAY_VAR(data_ov122_0229a180),
    HOST_OVERLAY_VAR(data_ov122_0229a030),
    HOST_OVERLAY_VARS_END
};
