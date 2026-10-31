#include "types.h"
#include "host_shared_calls.h"
#include "Unk_020d8c7c.h"
#include "net/CommManager.h"
#include "player/PlayerId.h"
#include "menu/MenuProc.h"
#include "ui/HandCursor.h"
#include "ui/ScrollKnob.h"
#include "talk/EncodedString.h"
#include "menu/MenuLauncher.h"
#include "gfx/BgVramTask.h"
#include "talk/EncodedString192.h"
#include "talk/EncodedString41.h"
#include "menu/MenuCursor.h"
#include "menu/MenuScrollKnob.h"
#include "player/PlayerData.h"
#include "talk/MsgString.h"
#include "talk/MsgString193.h"
#include "talk/MsgString9B.h"
#include "ui/LabelString.h"
#include "menu/Keyboard.h"
#include "menu/MenuBottomButtons.h"
#include "menu/MenuErrorMessage.h"
#include "sys/ProcProfile.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02051218.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_0206cbdc.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0206f834.h"
#include "proto/main/unk_020720f8.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov095/unk_02292360.h"
#include "proto/ov112/unk_ov112_02296840.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_020501d4.h"
#include "proto/ov002/unk_ov002_022025cc.h"

class BbsWriteMenu;
typedef BbsWriteMenu S;

class EncodedString;
























typedef void (BbsWriteMenu::*Unk_ov112_02299b10_Fn)();

class BbsWriteMenu : public MenuProc {
public:
    BbsWriteMenu()
        : errorMessage(), textCharTask(), keyboard(), lineLabels(), scrollKnob(), bottomButtons(), cursor(),
          censorString(), encodedText() {}

    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onDraw();
    virtual BOOL execTransition();
    virtual BOOL execMain();
    virtual BOOL execPhase3();
    virtual BOOL execPhase4();
    virtual BOOL execClosed();

    BOOL isPostSendConfirmed();
    void sendPostToPeers();
    void endDialogDim();
    void beginDialogDim();
    void placeLabel(s32 idx, u32 a, u32 b, s32 c);
    void clearPostNumberLabel();
    void showTodayDate();
    void censorText();
    void refreshCursor();
    void releaseCursor();
    void pressCursor();
    void snapCursor();
    void moveCursorTo(s32 a, s32 b);
    void moveCursorToTarget();
    void hideCursor();
    void showCursor();
    void openDialog(u8 v, u8 x);
    void refreshKeys();
    BOOL navigateText(u32 pad);
    s32 getLineOfIndex(s32 v);
    void updateCaretPos();
    u8 getCharBeforeCursor();
    void setCursorIndex(u8 v);
    void resetTextCursor();
    BOOL dragSelection();
    void endTouch();
    BOOL touchTextArea();

    void preInputUpdate();
    void releaseResources();
    void init();
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
    void runMainState();

    void mainAct00();
    void mainAct01();
    void mainAct02();
    void mainAct03();
    void mainAct04();
    void mainAct05();
    void mainAct06();
    void mainAct07();
    void mainAct08();
    void mainAct09();
    void mainAct0A();
    void mainAct0B();
    void mainAct0C();
    void mainAct0D();
    void mainAct0E();
    void mainAct0F();
    void mainAct10();
    void mainAct11();
    void mainAct12();
    void mainAct13();
    void mainAct14();
    void mainAct15();
    void mainAct16();

    /* 0x91 */ u8 unk_91[3];
    /* 0x94 */ s32 lastLine;
    /* 0x98 */ s32 caretX;
    /* 0x9c */ s32 caretY;
    /* 0xa0 */ s32 keyboardSlideY;
    /* 0xa4 */ s32 pageSlideY;
    /* 0xa8 */ s32 buttonsSlideY;
    /* 0xac */ u32 flags;
    /* 0xb0 */ s32 lengthGauge;
    /* 0xb4 */ s16 sendSeq;
    /* 0xb6 */ u8 scrollY;
    /* 0xb7 */ u8 scrollTargetY;
    /* 0xb8 */ u8 scrollKnobY;
    /* 0xb9 */ u8 dragStartTouchY;
    /* 0xba */ u8 dragStartKnobY;
    /* 0xbb */ u8 lastTickScrollY;
    /* 0xbc */ u8 caretBlinkTimer;
    /* 0xbd */ u8 caretIndex;
    /* 0xbe */ u8 selectionStart;
    /* 0xbf */ u8 selectionEnd;
    /* 0xc0 */ u8 headerLength;
    /* 0xc1 */ u8 returnState;
    /* 0xc2 */ u8 confirmChoice;
    /* 0xc3 */ u8 text[0xc0];
    /* 0x183 */ u8 clipboard[0xc0];
    /* 0x243 */ u8 pad_243;
    /* 0x244 */ MenuErrorMessage errorMessage;
    /* 0x34c */ BgVramTask textCharTask[1];
    /* 0x370 */ Keyboard keyboard;
    /* 0x3f2c */ LabelString lineLabels[6];
    /* 0x40ac */ MenuScrollKnob scrollKnob;
    /* 0x40f4 */ MenuBottomButtons bottomButtons;
    /* 0x4258 */ MenuCursorBuf0 cursor;
    /* 0x42bc */ MsgString193 censorString;
    /* 0x4390 */ EncodedString192 encodedText;
    /* 0x4450 */ u8 unk_4450[0x10];
    /* 0x4460 */ u8 bgScreenBuf[0x800];
    /* 0x4c60 */ u8 lineCharBufs[6][0x500];
    /* 0x6a60 */ s32 lineStarts[7];
};

extern "C" {
extern u16 gPad[];
extern u8 gU8None;
extern CommManager *gCommManager;
}


extern "C" {
void Math_StepU8(void *p, u32 v, u32 n);
void func_0206fcc8(void *p);
void func_0206fca8(void *p);
void func_0206f874(void *p);
void func_0206f85c(void *p);
void func_02094030(void *p);
void func_02094018(void *p);
void MI_CpuFill8(void *p, u32 v, u32 n);
void MI_CpuCopy8(void *src, void *dst, u32 n);
void Clock_GetDate(void *p);
void EncodedString_SetRaw(void *dst, void *src, s32 n);
s32 func_02133150(s32 a, s32 b);
}

extern "C" void BbsWriteMenu_SetCaretFromPoint(S *s, s32 a, s32 b);
extern "C" u8 BbsWriteMenu_HitTestLine(S *s, s32 i, s32 *p);
extern "C" void BbsWriteMenu_DeleteSelection(S *s);
extern "C" void BbsWriteMenu_ClearSelection(S *s);
extern "C" BOOL BbsWriteMenu_HasSelection(S *s);
extern "C" void BbsWriteMenu_ScrollByPad(S *s);
extern "C" void BbsWriteMenu_ScrollToTouch(S *s);
extern "C" void BbsWriteMenu_DragScrollKnob(S *s);
extern "C" void BbsWriteMenu_SetScrollFromKnob(S *s, s32 v);
extern "C" BOOL BbsWriteMenu_IsTouchOnScrollBar(S *s);
extern "C" BOOL BbsWriteMenu_TouchScrollKnob(S *s);
extern "C" void BbsWriteMenu_ScrollToCaret(S *s);
extern "C" void BbsWriteMenu_UpdateScroll(S *s);
extern "C" BOOL BbsWriteMenu_IsScrolling(S *s);
extern "C" void BbsWriteMenu_SetScrollTarget(S *s, u32 v);
extern "C" void BbsWriteMenu_SetScroll(S *s, u32 v);
extern "C" void BbsWriteMenu_UploadTextChars(S *s);
extern "C" void BbsWriteMenu_Nop(S *s);
extern "C" void BbsWriteMenu_UpdateLineLabels(S *s);
extern "C" void BbsWriteMenu_DrawLineLabels(S *s);
extern "C" void BbsWriteMenu_HighlightRange(S *s, u8 a, u8 b, u32 c, u32 n);
extern "C" void BbsWriteMenu_HighlightSelection(S *s);
extern "C" void BbsWriteMenu_RedrawText(S *s);
extern "C" void BbsWriteMenu_ClearFlags(S *s, u32 m);
extern "C" void BbsWriteMenu_SetFlags(S *s, u32 m);
extern "C" BOOL BbsWriteMenu_HasFlags(S *s, u32 m);
extern "C" void BbsWriteMenu_EnterDialogButtons(S *s);
extern "C" void BbsWriteMenu_EnterDialogTouch(S *s);
extern "C" void BbsWriteMenu_ShowMessage(S *s, u32 a, u32 b);
extern "C" void BbsWriteMenu_ResumeInput(S *s);
extern "C" void BbsWriteMenu_StartButtonInput(S *s);
extern "C" void BbsWriteMenu_StartTouchInput(S *s);
extern "C" void BbsWriteMenu_PlayErrorSe(S *s);
extern "C" void BbsWriteMenu_ForceClose(S *s);
extern "C" void BbsWriteMenu_ConfirmNo(S *s);
extern "C" void BbsWriteMenu_ConfirmYes(S *s);
extern "C" void BbsWriteMenu_AskQuit(S *s);
extern "C" void BbsWriteMenu_AskPost(S *s);
extern "C" void BbsWriteMenu_Paste(S *s);
extern "C" void BbsWriteMenu_Copy(S *s);
extern "C" BOOL BbsWriteMenu_ApplyModifierKey(S *s, s32 key);
extern "C" BOOL BbsWriteMenu_InsertChar(S *s, u32 key);
extern "C" BOOL BbsWriteMenu_InsertCharRaw(S *s, u32 a, s32 b);
extern "C" BOOL BbsWriteMenu_Backspace(S *s, s32 flag);
extern "C" s32 BbsWriteMenu_PressKeyCode(S *s, s32 key);
extern "C" s32 BbsWriteMenu_TouchKey(S *s);
extern "C" BOOL BbsWriteMenu_TryStartPost(S *s);
extern "C" BOOL BbsWriteMenu_TryCopyButton(S *s);
extern "C" BOOL BbsWriteMenu_TryPasteButton(S *s);
extern "C" BOOL BbsWriteMenu_ToggleTextFocus(S *s);
extern "C" BOOL BbsWriteMenu_TryBackspaceButton(S *s);
extern "C" BOOL BbsWriteMenu_TryPressKey(S *s);
extern "C" void BbsWriteMenu_LoadBg(S *s);
extern "C" void BbsWriteMenu_SetupBgLayers(S *s);
extern "C" void BbsWriteMenu_PostInput(S *s);



static inline BOOL Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) return TRUE;
    return FALSE;
}

struct BbsRedrawStackPad {
    s32 v[8];
    BbsRedrawStackPad() {}
    ~BbsRedrawStackPad() {}
};


extern "C" BbsWriteMenu *BbsWriteMenu_Create() { return new BbsWriteMenu(); }

BOOL BbsWriteMenu::onCreate() {
    init();
    transitionState = 0;
    setPhase(0);
    return TRUE;
}

BOOL BbsWriteMenu::onDelete() {
    ((MenuLauncher *)ProcBase_GetParent(this))->onChildClosed();
    releaseResources();
    return TRUE;
}

BOOL BbsWriteMenu::onDraw() {
    if (BbsWriteMenu_IsScrolling((S *)this)) {
        BbsWriteMenu_UpdateScroll((S *)this);
        Gfx2d_SetLayerOffset(4, 0, scrollY + 8);
    }
    if (BbsWriteMenu_HasFlags((S *)this, 1)) {
        s32 p = keyboardSlideY + 0x60;
        Oam_DrawCell(1, &data_ov112_02299ad8[0], 0x80, p - 8, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        Keyboard_Draw(&keyboard, 0x80, p, 1);
        Shared_Keyboard_DrawCopyPasteKeys(&keyboard, 0x80, p);
        if (MenuCtrl_IsButtons()) {
            Oam_DrawObj(1, &data_ov112_02299ac0[0], 0x80, p, -1, 1, NULL);
        }
        Keyboard_DrawLengthGaugeAt(&keyboard, 0x80, p, lengthGauge);
        ((ScrollKnob *)(&scrollKnob))->moveTo(0x5d, scrollKnobY + (u32)(keyboardSlideY - 0x50));
        s32 t = scrollKnob.getGripX();
        Shared_Keyboard_SetTextFieldPos(&keyboard, t, scrollKnob.getGripY());
        scrollKnob.draw();
    }
    if (MenuCtrl_IsButtons()) {
        if (BbsWriteMenu_HasFlags((S *)this, 0x1000)) {
            s32 t = scrollKnob.getGripX();
            cursor.warpTo(t, scrollKnob.getGripY());
        }
        cursor.drawWrapped();
    }
    if (BbsWriteMenu_HasFlags((S *)this, 1)) {
        if (BbsWriteMenu_HasFlags((S *)this, 0x40)) {
            s32 a = caretX;
            s32 b = caretY - (scrollY + 8);
            caretBlinkTimer = caretBlinkTimer + 1;
            if ((caretBlinkTimer & 0x10) != 0) {
                Keyboard_DrawCaret(&keyboard, a, b, 2);
            }
        }
    }
    bottomButtons.drawAt(buttonsSlideY);
    return TRUE;
}
extern "C" ProcProfile data_ov112_022999b8;
extern "C" GXOamAttr data_ov112_02299ad8[6];
extern "C" GXOamAttr data_ov112_02299ac0[1];


extern "C" ProcProfile data_ov112_022999b8 = {(void *(*)())BbsWriteMenu_Create, 0xa6, 0xaa};

extern "C" GXOamAttr data_ov112_02299ad8[6] = {{0x6180b4, 0xc0, 0, 0xa, 0x0}, {0x206180e4, 0xc0, 0, 0xa, 0x0}, {0x6100c4, 0xe0, 0, 0xa, 0x0}, {0x6100cc, 0xe0, 0, 0xa, 0x0}, {0x6100d4, 0xe0, 0, 0xa, 0x0}, {0x6100dc, 0xe0, 0, 0xa, 0xffff}};

extern "C" GXOamAttr data_ov112_02299ac0[1] = {{0x802a40e6, 0xc1, 0, 0xc, 0xffff}};

BOOL BbsWriteMenu::execTransition() {
    static Unk_ov112_02299b10_Fn tbl[14] = {
        &BbsWriteMenu::transitionAct00, &BbsWriteMenu::transitionAct01,
        &BbsWriteMenu::transitionAct02, &BbsWriteMenu::transitionAct03,
        &BbsWriteMenu::transitionAct04, &BbsWriteMenu::transitionAct05,
        &BbsWriteMenu::transitionAct06, &BbsWriteMenu::transitionAct07,
        &BbsWriteMenu::transitionAct08, &BbsWriteMenu::transitionAct09,
        &BbsWriteMenu::transitionAct0A, &BbsWriteMenu::transitionAct0B,
        &BbsWriteMenu::transitionAct0C, &BbsWriteMenu::transitionAct0D};
    (this->*tbl[transitionState])();
    return TRUE;
}

void BbsWriteMenu::runMainState() {
    static Unk_ov112_02299b10_Fn tbl[23] = {
        &BbsWriteMenu::mainAct00, &BbsWriteMenu::mainAct01,
        &BbsWriteMenu::mainAct02, &BbsWriteMenu::mainAct03,
        &BbsWriteMenu::mainAct04, &BbsWriteMenu::mainAct05,
        &BbsWriteMenu::mainAct06, &BbsWriteMenu::mainAct07,
        &BbsWriteMenu::mainAct08, &BbsWriteMenu::mainAct09,
        &BbsWriteMenu::mainAct0A, &BbsWriteMenu::mainAct0B,
        &BbsWriteMenu::mainAct0C, &BbsWriteMenu::mainAct0D,
        &BbsWriteMenu::mainAct0E, &BbsWriteMenu::mainAct0F,
        &BbsWriteMenu::mainAct10, &BbsWriteMenu::mainAct11,
        &BbsWriteMenu::mainAct12, &BbsWriteMenu::mainAct13,
        &BbsWriteMenu::mainAct14, &BbsWriteMenu::mainAct15,
        &BbsWriteMenu::mainAct16};
    (this->*tbl[mainState])();
}

BOOL BbsWriteMenu::execMain() {
    MenuCtrl_TickForceClose();
    if (MenuCtrl_IsForceCloseDue()) {
        switch (mainState) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 9:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 17:
        case 19:
            BbsWriteMenu_ForceClose((S *)this);
            return TRUE;
        }
    }
    preInputUpdate();
    runMainState();
    BbsWriteMenu_PostInput((S *)this);
    return TRUE;
}

BOOL BbsWriteMenu::execPhase3() { return TRUE; }

BOOL BbsWriteMenu::execPhase4() { return TRUE; }

BOOL BbsWriteMenu::execClosed() {
    ProcBase_RequestDelete(this);
    return TRUE;
}

void BbsWriteMenu::transitionAct00() {
    BbsWriteMenu_SetupBgLayers((S *)this);
    BbsWriteMenu_LoadBg((S *)this);
    BbsWriteMenu_UploadTextChars((S *)this);
    BbsWriteMenu_SetFlags((S *)this, 0x4000);
    Shared_Keyboard_RestoreLastPage(&keyboard, 6);
    Keyboard_EndFrame(&keyboard, 6);
    beginSubSlideIn(0xa, 7, 0, 0x30);
    Gfx2d_ShowLayer(4);
    Gfx2d_ShowLayer(6);
    applySlideOffset(4, 0, -8);
    applySlideOffset(6, 0, 0);
    setTransitionState(1);
    keyboardSlideY = getSlideOffsetY();
    pageSlideY = keyboardSlideY;
    buttonsSlideY = pageSlideY;
    BbsWriteMenu_SetFlags((S *)this, 0x81);
    bottomButtons.setLayoutNeverMindConfirm();
    BbsWriteMenu_RedrawText((S *)this);
    BbsWriteMenu_PostInput((S *)this);
}

void BbsWriteMenu::transitionAct01() {
    if (BbsWriteMenu_HasFlags((S *)this, 0x4000)) {
        showTodayDate();
        clearPostNumberLabel();
        BbsWriteMenu_ClearFlags((S *)this, 0x4000);
    }
    if (stepSlideIn(0)) {
        resetTextCursor();
        setPhase(2);
        BbsWriteMenu_ResumeInput((S *)this);
        BbsWriteMenu_RedrawText((S *)this);
        BbsWriteMenu_PostInput((S *)this);
    }
    applySlideOffset(4, 0, -8);
    applySlideOffset(6, 0, 0);
    keyboardSlideY = getSlideOffsetY();
    pageSlideY = keyboardSlideY;
    buttonsSlideY = pageSlideY;
}

void BbsWriteMenu::transitionAct02() {
    BbsWriteMenu_ClearFlags((S *)this, 0x40);
    beginSubSlideOut(8, 0, 0, 0x30);
    applySlideOffset(6, 0, 0);
    setTransitionState(3);
    keyboardSlideY = getSlideOffsetY();
    buttonsSlideY = keyboardSlideY;
    BbsWriteMenu_SetScrollTarget((S *)this, 0);
    BbsWriteMenu_ClearFlags((S *)this, 0x80);
}

void BbsWriteMenu::transitionAct03() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(6);
        BbsWriteMenu_ClearFlags((S *)this, 1);
        setTransitionState(4);
    } else {
        applySlideOffset(6, 0, 0);
    }
    keyboardSlideY = getSlideOffsetY();
    buttonsSlideY = keyboardSlideY;
}

void BbsWriteMenu::transitionAct04() {
    beginDialogDim();
    if (BbsWriteMenu_HasFlags((S *)this, 0x2000)) {
        ((MenuBottomButtonsBody *)&bottomButtons)->setLayoutYesNo08(0x87);
    } else {
        ((MenuBottomButtonsBody *)&bottomButtons)->setLayoutYesNo08(0x22);
    }
    initSlideIn(5, 0);
    buttonsSlideY = getSlideOffsetY();
    setTransitionState(5);
}

void BbsWriteMenu::transitionAct05() {
    if (stepSlideIn(-1)) {
        setPhase(2);
        if (MenuCtrl_IsTouch()) {
            BbsWriteMenu_EnterDialogTouch((S *)this);
        } else {
            BbsWriteMenu_EnterDialogButtons((S *)this);
        }
    }
    buttonsSlideY = getSlideOffsetY();
}

void BbsWriteMenu::transitionAct06() {
    endDialogDim();
    beginSubSlideOut(0, 0, 0, 0x30);
    setTransitionState(7);
    buttonsSlideY = getSlideOffsetY();
}

void BbsWriteMenu::transitionAct07() {
    if (stepSlideOut(0)) {
        setTransitionState(8);
    }
    buttonsSlideY = getSlideOffsetY();
}

void BbsWriteMenu::transitionAct08() {
    beginSubSlideIn(8, 0, 0, 0x30);
    Gfx2d_ShowLayer(6);
    applySlideOffset(6, 0, 0);
    setTransitionState(9);
    keyboardSlideY = getSlideOffsetY();
    buttonsSlideY = keyboardSlideY;
    BbsWriteMenu_SetFlags((S *)this, 1);
    bottomButtons.setLayoutNeverMindConfirm();
}

void BbsWriteMenu::transitionAct09() {
    if (stepSlideIn(0)) {
        resetTextCursor();
        setPhase(2);
        BbsWriteMenu_ResumeInput((S *)this);
        BbsWriteMenu_RedrawText((S *)this);
        BbsWriteMenu_PostInput((S *)this);
        BbsWriteMenu_SetFlags((S *)this, 0x80);
    }
    applySlideOffset(6, 0, 0);
    keyboardSlideY = getSlideOffsetY();
    buttonsSlideY = keyboardSlideY;
}

void BbsWriteMenu::transitionAct0A() {
    if (BbsWriteMenu_HasFlags((S *)this, 0x2000) || isPostSendConfirmed()) {
        BbsWriteMenu_ClearFlags((S *)this, 0x40);
        endDialogDim();
        ((MenuLauncher *)(ProcBase_GetParent(this)))->setNextRequest(0x44, 1);
        beginSubSlideOut(2, 0, 0, 0x30);
        applySlideOffset(4, 0, -8);
        setTransitionState(0xb);
        pageSlideY = getSlideOffsetY();
        buttonsSlideY = pageSlideY;
    }
}

void BbsWriteMenu::transitionAct0B() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(4);
        setPhase(5);
    } else {
        applySlideOffset(4, 0, -8);
    }
    pageSlideY = getSlideOffsetY();
    buttonsSlideY = pageSlideY;
}

void BbsWriteMenu::transitionAct0C() {
    if (BbsWriteMenu_IsScrolling((S *)this) == 0) {
        BbsWriteMenu_ClearFlags((S *)this, 0x40);
        endDialogDim();
        ((MenuLauncher *)(ProcBase_GetParent(this)))->setNextRequest(0x44, 1);
        beginSubSlideOut(0xa, 0, 0, 0x30);
        applySlideOffset(4, 0, -8);
        applySlideOffset(6, 0, -8);
        setTransitionState(0xd);
        pageSlideY = getSlideOffsetY();
        buttonsSlideY = pageSlideY;
    }
}

void BbsWriteMenu::transitionAct0D() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(4);
        Gfx2d_ResetLayer(6);
        setPhase(5);
    } else {
        applySlideOffset(4, 0, -8);
        applySlideOffset(6, 0, -8);
    }
    pageSlideY = getSlideOffsetY();
    buttonsSlideY = pageSlideY;
    keyboardSlideY = pageSlideY;
}

void BbsWriteMenu::init() {
    flags = 0;
    Keyboard_Init(&keyboard, 2);
    Mem_Clear(text, 0xc0);
    LabelString a;
    PlayerData *t = PlayerData_GetCurrent();
    MsgString9B b;
    t->getPlayerId()->getNameString(&b);
    String_SetSlot(0, &b);
    String_Load2dMenu(&a, 0x89);
    EncodedString41 c;
    ((EncodedString *)(&c))->fromMsgString(&a);
    s32 n = Text_GetLength(c.text, 0x28);
    Mem_Copy(c.text, text, n);
    text[n] = 0x86;
    n++;
    if (Text_MeasureWidth(text, n) > 0x96) {
        n--;
        text[n] = 0;
    }
    headerLength = n;
    scrollKnob.show();
    MI_CpuFill8(lineCharBufs, 0xdd, 0x1e00);
    scrollY = 0;
    scrollTargetY = 0;
    scrollKnobY = 0;
}

void BbsWriteMenu::releaseResources() {
    BbsWriteMenu_UpdateLineLabels((S *)this);
    Keyboard_Shutdown(&keyboard);
    ((BgVramTask *)(textCharTask))->cancel();
    bottomButtons.freeTexts();
}

void BbsWriteMenu::preInputUpdate() {
    BbsWriteMenu_UpdateLineLabels((S *)this);
    scrollKnob.update();
    cursor.update();
    bottomButtons.freeTexts();
}

extern "C" void BbsWriteMenu_PostInput(S *s) {
    Keyboard_EndFrame(&s->keyboard, 6);
    if (BbsWriteMenu_HasFlags(s, 4)) {
        BbsWriteMenu_DrawLineLabels(s);
        BbsWriteMenu_ClearFlags(s, 4);
        BbsWriteMenu_SetFlags(s, 2);
    }
    if (BbsWriteMenu_HasFlags(s, 8)) {
        BbsWriteMenu_ClearFlags(s, 8);
        BbsWriteMenu_SetFlags(s, 2);
    }
    if (BbsWriteMenu_HasFlags(s, 2)) {
        BbsWriteMenu_Nop(s);
        BbsWriteMenu_UploadTextChars(s);
        BbsWriteMenu_ClearFlags(s, 2);
    }
}

extern "C" void BbsWriteMenu_SetupBgLayers(S *s) {
    Gfx2d_SetSubBgModeState(0);
    Gfx2d_SetLayerPriority(4, 3);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
    Gfx2d_SetLayerPriority(6, 1);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
}

extern "C" void BbsWriteMenu_LoadBg(S *s) {
    void *g = gCurrentHeap;
    Gfx2d_LoadPaletteFile("menu/chat2/b_bbs.bpl", g, 4, 8, 8, 0xe);
    File_LoadToBuffer("menu/chat2/b_bbs_us.bsc", s->bgScreenBuf, 0x800);
    BgScreen_SetRectPalette((u16 *)s->bgScreenBuf, 6, 5, 0x19, 6, 0xa);
    Gfx2d_LoadScreen(s->bgScreenBuf, 4, 0x800, 0);
    Gfx2d_LoadCharFile("menu/chat2/b_cht.bch", g, 4, 0x13d, 0x13d, 0x1e9);
    Gfx2d_LoadCharFile("menu/chat2/b_bbs.bch", g, 4, 0x10, 0x10, 0x13f);
    Gfx2d_LoadCharFile("menu/chat2/b_bbs2.bch", g, 4, 0x101, 0x101, 0x110);
    Keyboard_LoadScreenFile(&s->keyboard, "menu/chat2/b_key0.bsc");
    ((BbsWriteMenu *)s)->refreshKeys();
    Keyboard_LoadScreenNow(&s->keyboard, 6);
    Shared_Keyboard_LoadLetterChars(&s->keyboard, 6);
    Keyboard_LoadObjGfx(&s->keyboard);
}

void BbsWriteMenu::mainAct00() {
    S *s = (S *)this;
    if (((MenuProc *)s)->checkSwitchToButtons(1)) {
        BbsWriteMenu_StartButtonInput(s);
    } else {
        u32 f = 0;
        s32 v;
        if (Keyboard_UpdatePressedKey(&s->keyboard)) f = 1;
        if (Both()) {
            v = gTouchCurY;
            if (((MenuBottomButtonsBody *)(&s->bottomButtons))->isTouched(9)) {
                BbsWriteMenu_AskPost(s);
            } else if (((MenuBottomButtonsBody *)(&s->bottomButtons))->isTouched(8)) {
                BbsWriteMenu_AskQuit(s);
            } else if (Keyboard_TouchPageTab(&s->keyboard)) {
                Keyboard_SetMode(&s->keyboard, 8, 6, 1);
                BbsWriteMenu_RedrawText(s);
            } else if (((BbsWriteMenu *)s)->touchTextArea()) {
                ((MenuProc *)s)->setMainState(3);
                Shared_Keyboard_ResetTypedRun(&s->keyboard);
                BbsWriteMenu_RedrawText(s);
            } else if (BbsWriteMenu_TouchScrollKnob(s)) {
                ((MenuScrollKnob *)(&s->scrollKnob))->grab();
                ((MenuProc *)s)->setMainState(1);
                BbsWriteMenu_ClearSelection(s);
                BbsWriteMenu_RedrawText(s);
            } else if (BbsWriteMenu_IsTouchOnScrollBar(s)) {
                ((MenuScrollKnob *)(&s->scrollKnob))->grab();
                ((MenuProc *)s)->setMainState(2);
                BbsWriteMenu_ClearSelection(s);
                BbsWriteMenu_RedrawText(s);
            } else if (v >= 0x48 && f == 0) {
                BOOL r = BbsWriteMenu_TouchKey(s);
                if (r == 0) {
                } else if (r == 1) {
                    ((MenuProc *)s)->setMainState(4);
                }
            }
        }
    }
}

void BbsWriteMenu::mainAct01() {
    S *s = (S *)this;
    s->caretBlinkTimer = 0;
    if (gTouchHeld == 0) {
        ((BbsWriteMenu *)s)->endTouch();
        ((MenuScrollKnob *)(&s->scrollKnob))->release();
        BbsWriteMenu_StartTouchInput(s);
    } else {
        BbsWriteMenu_DragScrollKnob(s);
    }
}

void BbsWriteMenu::mainAct02() {
    S *s = (S *)this;
    s->caretBlinkTimer = 0;
    if (gTouchHeld == 0) {
        ((BbsWriteMenu *)s)->endTouch();
        ((MenuScrollKnob *)(&s->scrollKnob))->release();
        BbsWriteMenu_StartTouchInput(s);
    } else {
        BbsWriteMenu_ScrollToTouch(s);
    }
}

void BbsWriteMenu::mainAct03() {
    S *s = (S *)this;
    BOOL r;
    if (gTouchHeld == 0) {
        ((MenuProc *)s)->setMainState(0);
        if (s->selectionStart == s->selectionEnd) {
            BbsWriteMenu_ClearFlags(s, 0x100);
        }
        r = TRUE;
    } else {
        r = ((BbsWriteMenu *)s)->dragSelection();
        if (r) {
            Snd_PlaySe(0x15);
        }
    }
    if (r) {
        BbsWriteMenu_ScrollToCaret(s);
        BbsWriteMenu_RedrawText(s);
    }
}

void BbsWriteMenu::mainAct04() {
    S *s = (S *)this;
    if (gTouchHeld == 0) {
        ((MenuProc *)s)->setMainState(0);
    } else if (Shared_Keyboard_TickKeyRepeat(&s->keyboard)) {
        u32 r = Keyboard_GetPressedKey(&s->keyboard);
        BbsWriteMenu_PressKeyCode(s, Keyboard_GetKeyCode(&s->keyboard, r, 8));
        Shared_Keyboard_HighlightKey(&s->keyboard, r);
    }
}

void BbsWriteMenu::mainAct05() {
    S *s = (S *)this;
    if (((MenuProc *)s)->checkSwitchToButtons(1)) {
        BbsWriteMenu_EnterDialogButtons(s);
    } else if (Both()) {
        if (((MenuBottomButtonsBody *)(&s->bottomButtons))->isTouched(3)) {
            BbsWriteMenu_ConfirmYes(s);
        } else if (((MenuBottomButtonsBody *)(&s->bottomButtons))->isTouched(4)) {
            BbsWriteMenu_ConfirmNo(s);
        }
    }
}

void BbsWriteMenu::mainAct06() {
    S *s = (S *)this;
    if (((MenuProc *)s)->checkSwitchToTouch()) {
        BbsWriteMenu_StartTouchInput(s);
    } else {
        switch (Keyboard_MoveCursor(&s->keyboard, ((MenuProc *)s)->takeRepeatedKeys())) {
        case 1:
            ((MenuCursor *)(&s->cursor))->switchToAnim01();
            ((BbsWriteMenu *)s)->moveCursorToTarget();
            break;
        case 2:
            ((MenuCursor *)(&s->cursor))->switchToAnim0D();
            ((BbsWriteMenu *)s)->moveCursorToTarget();
            break;
        case 3:
            ((MenuCursor *)(&s->cursor))->switchToAnim07();
            ((BbsWriteMenu *)s)->moveCursorToTarget();
            break;
        case 0:
        default:
            if (BbsWriteMenu_TryPressKey(s)) return;
            if (BbsWriteMenu_TryBackspaceButton(s)) return;
            if (BbsWriteMenu_ToggleTextFocus(s)) return;
            if (BbsWriteMenu_TryCopyButton(s)) return;
            if (BbsWriteMenu_TryPasteButton(s)) return;
            if (BbsWriteMenu_TryStartPost(s) != 0) return;
            break;
        }
    }
}

void BbsWriteMenu::mainAct07() {
    S *s = (S *)this;
    if (!((MenuCursorBase *)(&s->cursor))->isMoving()) {
        ((MenuProc *)s)->setMainState(s->returnState);
        ((BbsWriteMenu *)s)->runMainState();
    }
}

void BbsWriteMenu::mainAct08() {
    S *s = (S *)this;
    if (((HandCursor *)(&s->cursor))->isAnimDone()) {
        u32 r = Shared_Keyboard_PressCursorKey(&s->keyboard);
        u32 v = Keyboard_GetKeyCode(&s->keyboard, r, 8);
        if (v == 0x112) {
            ((MenuProc *)s)->setMainState(0x10);
            ((MenuScrollKnob *)(&s->scrollKnob))->grab();
            Menu_PlayScrollGrabSe();
            if (BbsWriteMenu_HasSelection(s)) {
                BbsWriteMenu_RedrawText(s);
            }
            BbsWriteMenu_ClearSelection(s);
            BbsWriteMenu_SetFlags(s, 0x1000);
        } else {
            u32 t = BbsWriteMenu_PressKeyCode(s, v);
            if (t == 1 && (gPad[0] & 1) != 0) {
                Keyboard_StartKeyRepeat(&s->keyboard);
                ((MenuProc *)s)->setMainState(9);
                Shared_Keyboard_HighlightKey(&s->keyboard, r);
            } else if (t == 3) {
            } else if (t == 4) {
                Shared_Keyboard_ClearHighlight(&s->keyboard);
            } else {
                ((BbsWriteMenu *)s)->releaseCursor();
            }
        }
    }
}

void BbsWriteMenu::mainAct09() {
    S *s = (S *)this;
    if ((gPad[0] & 1) == 0) {
        ((BbsWriteMenu *)s)->releaseCursor();
    } else if (Shared_Keyboard_TickKeyRepeat(&s->keyboard)) {
        u32 r = Keyboard_GetPressedKey(&s->keyboard);
        BbsWriteMenu_PressKeyCode(s, Keyboard_GetKeyCode(&s->keyboard, r, 8));
        Shared_Keyboard_HighlightKey(&s->keyboard, r);
    }
}

void BbsWriteMenu::mainAct0A() {
    S *s = (S *)this;
    if (((HandCursor *)(&s->cursor))->isAnimDone()) {
        ((BbsWriteMenu *)s)->refreshCursor();
        ((MenuProc *)s)->setMainState(6);
    }
}

void BbsWriteMenu::mainAct0B() {
    S *s = (S *)this;
    if ((gPad[0] & 2) == 0) {
        ((MenuProc *)s)->setMainState(s->returnState);
    } else if (Shared_Keyboard_TickKeyRepeat(&s->keyboard)) {
        Keyboard_ShrinkTypedRun(&s->keyboard);
        if (BbsWriteMenu_Backspace(s, 0)) {
            if (BbsWriteMenu_HasFlags(s, 0x800)) {
                ((BbsWriteMenu *)s)->snapCursor();
            }
        } else {
            ((BbsWriteMenu *)s)->hideCursor();
            BbsWriteMenu_AskQuit(s);
        }
    }
}

void BbsWriteMenu::mainAct0C() {
    S *s = (S *)this;
    if (((MenuProc *)s)->checkSwitchToTouch()) {
        BbsWriteMenu_StartTouchInput(s);
    } else if (((BbsWriteMenu *)s)->navigateText(((MenuProc *)s)->takeRepeatedKeys())) {
        if (Shared_Keyboard_GetTypedRunLength(&s->keyboard) || BbsWriteMenu_HasSelection(s)) {
            Shared_Keyboard_ResetTypedRun(&s->keyboard);
            BbsWriteMenu_ClearSelection(s);
            BbsWriteMenu_RedrawText(s);
        } else {
            BbsWriteMenu_ClearSelection(s);
        }
        ((BbsWriteMenu *)s)->updateCaretPos();
        ((BbsWriteMenu *)s)->snapCursor();
        ((BbsWriteMenu *)s)->refreshKeys();
        Snd_PlaySe(0xb);
    } else if (!BbsWriteMenu_ToggleTextFocus(s)) {
        u32 old = s->caretIndex;
        if (BbsWriteMenu_TryBackspaceButton(s)) {
            if (old != s->caretIndex) {
                ((BbsWriteMenu *)s)->snapCursor();
            }
        } else {
            if ((gPad[1] & 1) != 0) {
                ((MenuProc *)s)->setMainState(0xd);
                BbsWriteMenu_SetFlags(s, 0x100);
                s->selectionStart = s->caretIndex;
                s->selectionEnd = s->caretIndex;
            }
            if (!BbsWriteMenu_TryCopyButton(s)) {
                if (!BbsWriteMenu_TryPasteButton(s)) {
                    if (BbsWriteMenu_TryStartPost(s) != 0) return;
                }
            }
        }
    }
}

void BbsWriteMenu::mainAct0D() {
    S *s = (S *)this;
    if ((gPad[0] & 1) == 0) {
        ((MenuProc *)s)->setMainState(0xc);
        if (s->selectionStart == s->selectionEnd) {
            BbsWriteMenu_ClearFlags(s, 0x100);
        }
    } else {
        if (((BbsWriteMenu *)s)->navigateText(((MenuProc *)s)->takeRepeatedKeys())) {
            s->selectionEnd = s->caretIndex;
            BbsWriteMenu_RedrawText(s);
            ((BbsWriteMenu *)s)->updateCaretPos();
            ((BbsWriteMenu *)s)->snapCursor();
            Snd_PlaySe(0x15);
        }
    }
}

void BbsWriteMenu::mainAct0E() {
    S *s = (S *)this;
    if ((gPad[0] & 0x200) == 0) {
        ((MenuProc *)s)->setMainState(s->returnState);
        ((BbsWriteMenu *)s)->refreshKeys();
    }
}

void BbsWriteMenu::mainAct0F() {
    S *s = (S *)this;
    if ((gPad[0] & 0x100) == 0) {
        ((MenuProc *)s)->setMainState(s->returnState);
        ((BbsWriteMenu *)s)->refreshKeys();
    }
}

void BbsWriteMenu::mainAct10() {
    S *s = (S *)this;
    if (((ScrollKnob *)(&s->scrollKnob))->areAnimsDone()) {
        ((MenuProc *)s)->setMainState(0x11);
    }
}

void BbsWriteMenu::mainAct11() {
    S *s = (S *)this;
    if ((gPad[0] & 1) == 0) {
        ((MenuScrollKnob *)(&s->scrollKnob))->release();
        ((MenuProc *)s)->setMainState(0x12);
        ((BbsWriteMenu *)s)->endTouch();
    } else {
        BbsWriteMenu_ScrollByPad(s);
    }
}

void BbsWriteMenu::mainAct12() {
    S *s = (S *)this;
    if (((ScrollKnob *)(&s->scrollKnob))->areAnimsDone()) {
        ((BbsWriteMenu *)s)->releaseCursor();
        BbsWriteMenu_ClearFlags(s, 0x1000);
    }
}

void BbsWriteMenu::mainAct13() {
    S *s = (S *)this;
    u32 old;
    s32 r;
    s32 a;
    s32 b;
    u32 t;

    if (((MenuProc *)s)->checkSwitchToTouch()) {
        BbsWriteMenu_EnterDialogTouch(s);
        return;
    }
    if (gPad[1] & 1) {
        ((MenuCursor *)(&s->cursor))->setPosePress();
        ((MenuProc *)s)->setMainState(0x14);
        return;
    }
    old = s->confirmChoice;
    r = ((MenuProc *)s)->takeRepeatedKeys();
    if (MenuKeys_HasLeft(r)) {
        if (s->confirmChoice != 0) {
            s->confirmChoice = *(volatile u8 *)&s->confirmChoice - 1;
        }
    } else if (MenuKeys_HasRight(r)) {
        if (s->confirmChoice < 1) {
            s->confirmChoice = *(volatile u8 *)&s->confirmChoice + 1;
        }
    }
    if (old != s->confirmChoice) {
        if (s->confirmChoice != 0) {
            a = ((MenuBottomButtonsBody *)(&s->bottomButtons))->getTargetX(4);
            b = ((MenuBottomButtonsBody *)(&s->bottomButtons))->getTargetY(4);
            ((BbsWriteMenu *)s)->moveCursorTo(a, b);
        } else {
            a = ((MenuBottomButtonsBody *)(&s->bottomButtons))->getTargetX(3);
            b = ((MenuBottomButtonsBody *)(&s->bottomButtons))->getTargetY(3);
            ((BbsWriteMenu *)s)->moveCursorTo(a, b);
        }
    }
    t = gPad[1];
    if (t & 2) {
        ((BbsWriteMenu *)s)->hideCursor();
        BbsWriteMenu_ConfirmNo(s);
    } else if (t & 8) {
        ((BbsWriteMenu *)s)->hideCursor();
        BbsWriteMenu_ConfirmYes(s);
    }
}

void BbsWriteMenu::mainAct14() {
    S *s = (S *)this;
    if (((HandCursor *)(&s->cursor))->isAnimDone()) {
        if (s->confirmChoice != 0) {
            BbsWriteMenu_ConfirmNo(s);
        } else {
            BbsWriteMenu_ConfirmYes(s);
        }
    }
}

void BbsWriteMenu::mainAct15() {
    S *s = (S *)this;
    s32 a;
    s32 b;
    s32 c;

    if (((MenuBottomButtonsBody *)(&s->bottomButtons))->stepPress()) {
        if (((HandCursor *)(&s->cursor))->getAnim()) {
            a = ((MenuBottomButtonsBody *)(&s->bottomButtons))->getPressOffset();
            b = ((MenuBottomButtonsBody *)(&s->bottomButtons))->getTargetX(-1);
            c = ((MenuBottomButtonsBody *)(&s->bottomButtons))->getTargetY(-1);
            ((MenuCursorBase *)(&s->cursor))->warpTo(a + b, a + c);
        }
    } else {
        ((BbsWriteMenu *)s)->hideCursor();
        ((MenuProc *)s)->setPhase(1);
    }
}

void BbsWriteMenu::mainAct16() {
    S *s = (S *)this;
    Keyboard_UpdatePressedKey(&s->keyboard);
    if (((MenuErrorMessage *)(&s->errorMessage))->update(1)) {
        BbsWriteMenu_ResumeInput(s);
    }
}

extern "C" BOOL BbsWriteMenu_TryPressKey(S *s) {
    s32 a;

    if ((gPad[1] & 1) == 0) {
        return FALSE;
    }
    a = Shared_Keyboard_PressCursorKey(&s->keyboard);
    if (a != -1) {
        Keyboard_GetKeyCode(&s->keyboard, a, 8);
        Shared_Keyboard_HighlightKey(&s->keyboard, a);
        ((BbsWriteMenu *)s)->pressCursor();
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL BbsWriteMenu_TryBackspaceButton(S *s) {
    if ((gPad[0] & 2) == 0) {
        return FALSE;
    }
    Keyboard_ShrinkTypedRun(&s->keyboard);
    if (BbsWriteMenu_Backspace(s, 0)) {
        Keyboard_StartKeyRepeat(&s->keyboard);
        s->returnState = s->mainState;
        ((MenuProc *)s)->setMainState(0xb);
    } else {
        ((BbsWriteMenu *)s)->hideCursor();
        BbsWriteMenu_AskQuit(s);
    }
    return TRUE;
}

extern "C" BOOL BbsWriteMenu_ToggleTextFocus(S *s) {
    if ((gPad[1] & 0x800) == 0) {
        return FALSE;
    }
    if (BbsWriteMenu_HasFlags(s, 0x800)) {
        BbsWriteMenu_ClearFlags(s, 0x800);
    } else {
        BbsWriteMenu_SetFlags(s, 0x800);
        BbsWriteMenu_ScrollToCaret(s);
    }
    if (Shared_Keyboard_IsOnButtonKey(&s->keyboard, -1)) {
        if (BbsWriteMenu_HasFlags(s, 0x800)) {
            ((MenuCursor *)(&s->cursor))->switchToAnim01();
            ((MenuProc *)s)->setMainState(0xc);
        } else {
            ((MenuCursor *)(&s->cursor))->switchToAnim07();
            ((MenuProc *)s)->setMainState(6);
        }
        ((BbsWriteMenu *)s)->moveCursorToTarget();
    } else {
        ((BbsWriteMenu *)s)->moveCursorToTarget();
    }
    return TRUE;
}

extern "C" BOOL BbsWriteMenu_TryPasteButton(S *s) {
    if ((gPad[1] & 0x100) == 0) {
        return FALSE;
    }
    if (Keyboard_IsSlotDisabled(&s->keyboard, 0xc)) {
        return FALSE;
    }
    BbsWriteMenu_PressKeyCode(s, 0x119);
    Shared_Keyboard_HighlightKey(&s->keyboard, 0xdc);
    ((BbsWriteMenu *)s)->snapCursor();
    s->returnState = s->mainState;
    ((MenuProc *)s)->setMainState(0xf);
    return TRUE;
}

extern "C" BOOL BbsWriteMenu_TryCopyButton(S *s) {
    if ((gPad[1] & 0x200) == 0) {
        return FALSE;
    }
    if (Keyboard_IsSlotDisabled(&s->keyboard, 0xb)) {
        return FALSE;
    }
    BbsWriteMenu_PressKeyCode(s, 0x118);
    Shared_Keyboard_HighlightKey(&s->keyboard, 0xdb);
    s->returnState = s->mainState;
    ((MenuProc *)s)->setMainState(0xe);
    return TRUE;
}

extern "C" BOOL BbsWriteMenu_TryStartPost(S *s) {
    if ((gPad[1] & 8) == 0) {
        return FALSE;
    }
    ((BbsWriteMenu *)s)->hideCursor();
    BbsWriteMenu_AskPost(s);
    return TRUE;
}

extern "C" s32 BbsWriteMenu_TouchKey(S *s) {
    s32 a;
    s32 b;
    s32 r;

    Shared_Keyboard_ClearHighlight(&s->keyboard);
    a = Shared_Keyboard_TouchKey(&s->keyboard, gTouchCurX, gTouchCurY);
    if (a != -1) {
        b = Keyboard_GetKeyCode(&s->keyboard, a, 8);
        r = BbsWriteMenu_PressKeyCode(s, b);
        Shared_Keyboard_HighlightKey(&s->keyboard, a);
        Keyboard_StartKeyRepeat(&s->keyboard);
        return r;
    }
    return 0;
}

extern "C" s32 BbsWriteMenu_PressKeyCode(S *s, s32 key) {
    s32 r = 1;
    s32 t = Shared_Keyboard_HandleModeKey(&s->keyboard, key, 6);

    if (t != 0) {
        BbsWriteMenu_RedrawText(s);
        return t;
    }
    if (Keyboard_IsControlCode(&s->keyboard, key)) {
        switch (key) {
        case 0x100:
            BbsWriteMenu_Backspace(s, r);
            break;
        case 0x103:
        case 0x104:
        case 0x105:
            if (!BbsWriteMenu_ApplyModifierKey(s, key)) {
                BbsWriteMenu_PlayErrorSe(s);
            }
            r = 2;
            break;
        case 0x118:
            BbsWriteMenu_Copy(s);
            r = 2;
            break;
        case 0x119:
            BbsWriteMenu_Paste(s);
            r = 2;
            break;
        case 0x113:
            BbsWriteMenu_AskPost(s);
            r = 3;
            break;
        case 0x115:
            BbsWriteMenu_AskQuit(s);
            r = 3;
            break;
        case 0x101:
        case 0x102:
        default:
            r = 2;
            break;
        }
    } else {
        t = BbsWriteMenu_InsertChar(s, (u8)key);
        if (Keyboard_IsFull(&s->keyboard)) {
            BbsWriteMenu_ShowMessage(s, 0x1c, r);
            return 4;
        }
        if (Keyboard_IsTooWide(&s->keyboard)) {
            BbsWriteMenu_ShowMessage(s, 0x1c, r);
            return 4;
        }
        if (t == 0) {
            BbsWriteMenu_PlayErrorSe(s);
        }
        if (key == 0x86) {
            r = 2;
        }
    }
    return r;
}

extern "C" BOOL BbsWriteMenu_Backspace(S *s, s32 flag) {
    if (BbsWriteMenu_HasSelection(s)) {
        Shared_Keyboard_ResetTypedRun(&s->keyboard);
        Snd_PlaySe(0x35);
    } else {
        u32 c0 = s->headerLength;
        u32 bd = s->caretIndex;

        if (bd > c0) {
            s->selectionStart = bd;
            s->selectionEnd = s->caretIndex - 1;
            Snd_PlaySe(0x35);
        } else if (s->text[c0] != 0) {
            s->selectionStart = c0;
            s->selectionEnd = s->headerLength + 1;
            Snd_PlaySe(0x35);
        } else {
            if (flag != 0) {
                BbsWriteMenu_PlayErrorSe(s);
            }
            return FALSE;
        }
    }
    BbsWriteMenu_DeleteSelection(s);
    BbsWriteMenu_RedrawText(s);
    ((BbsWriteMenu *)s)->updateCaretPos();
    return TRUE;
}

extern "C" BOOL BbsWriteMenu_InsertCharRaw(S *s, u32 a, s32 b) {
    u8 x = s->caretIndex;

    if (Shared_Keyboard_InsertCharMultiline(&s->keyboard, s->text, a, &x, 0xc0, 0x28, 6, 0x96, 0, b)) {
        ((BbsWriteMenu *)s)->setCursorIndex(x);
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL BbsWriteMenu_InsertChar(S *s, u32 key) {
    BOOL r;

    if (BbsWriteMenu_HasSelection(s)) {
        BbsWriteMenu_DeleteSelection(s);
        Shared_Keyboard_ResetTypedRun(&s->keyboard);
    }
    r = BbsWriteMenu_InsertCharRaw(s, key, 1);
    BbsWriteMenu_RedrawText(s);
    ((BbsWriteMenu *)s)->updateCaretPos();
    return r;
}

extern "C" BOOL BbsWriteMenu_ApplyModifierKey(S *s, s32 key) {
    s32 r = ((BbsWriteMenu *)s)->getCharBeforeCursor();

    if (r == 0) {
        return FALSE;
    }
    switch (key) {
    case 0x103:
        r = Keyboard_ModifyCharKey103(&s->keyboard, r);
        break;
    case 0x104:
        r = Shared_Keyboard_ModifyCharKey104(&s->keyboard, r);
        break;
    case 0x105:
        r = Keyboard_ModifyCharKey105(&s->keyboard, r);
        break;
    }
    if (r == 0) {
        return FALSE;
    }
    if (!Shared_Keyboard_ReplaceCharBeforeCursor(&s->keyboard, s->text, r, s->caretIndex)) {
        return FALSE;
    }
    BbsWriteMenu_RedrawText(s);
    ((BbsWriteMenu *)s)->updateCaretPos();
    return TRUE;
}

extern "C" void BbsWriteMenu_Copy(S *s) {
    u32 a;
    u32 b;
    u32 x;
    u32 y;

    if (BbsWriteMenu_HasSelection(s)) {
        b = s->selectionEnd;
        a = s->selectionStart;
        if (a > b) {
            x = b;
            y = a - b;
        } else {
            x = a;
            y = b - a;
        }
        Mem_Clear(s->clipboard, 0xc0);
        Mem_Copy(s->text + x, s->clipboard, y);
        BbsWriteMenu_SetFlags(s, 0x200);
        Shared_Keyboard_PlayCopySe();
        ((BbsWriteMenu *)s)->refreshKeys();
    }
}

extern "C" void BbsWriteMenu_Paste(S *s) {
    s32 n;
    s32 i;

    if (BbsWriteMenu_HasFlags(s, 0x200)) {
        if (BbsWriteMenu_HasSelection(s)) {
            BbsWriteMenu_DeleteSelection(s);
        }
        Shared_Keyboard_ResetTypedRun(&s->keyboard);
        Keyboard_BeginPaste(&s->keyboard);
        n = Text_GetLength(s->clipboard, 0xc0);
        for (i = 0; i < n; i++) {
            if (!BbsWriteMenu_InsertCharRaw(s, s->clipboard[i], 0)) {
                if (i == 0) {
                    BbsWriteMenu_PlayErrorSe(s);
                }
                i = n;
            }
        }
        Keyboard_PlayPasteSe();
        BbsWriteMenu_RedrawText(s);
        ((BbsWriteMenu *)s)->updateCaretPos();
        Keyboard_EndPaste(&s->keyboard);
    }
}

extern "C" void BbsWriteMenu_AskPost(S *s) {
    Snd_PlaySe(0x29);
    BbsWriteMenu_ClearFlags(s, 0x2000);
    ((BbsWriteMenu *)s)->openDialog(2, 9);
    BbsWriteMenu_SetFlags(s, 0x400);
    ((BbsWriteMenu *)s)->censorText();
    BbsWriteMenu_ClearSelection(s);
    BbsWriteMenu_RedrawText(s);
}

extern "C" void BbsWriteMenu_AskQuit(S *s) {
    Snd_PlaySe(0x2a);
    BbsWriteMenu_SetFlags(s, 0x2000);
    ((BbsWriteMenu *)s)->openDialog(2, 8);
    BbsWriteMenu_SetFlags(s, 0x400);
    BbsWriteMenu_ClearSelection(s);
    BbsWriteMenu_RedrawText(s);
}

extern "C" void BbsWriteMenu_ConfirmYes(S *s) {
    ((BbsWriteMenu *)s)->openDialog(0xa, 3);
    if (BbsWriteMenu_HasFlags(s, 0x2000)) {
        Snd_PlaySe(0x28);
    } else {
        Bbs_AddPost(s->text);
        Snd_PlaySe(0x27);
        ((BbsWriteMenu *)s)->sendPostToPeers();
        Arbeit_OnBbsPosted(PlayerData_GetCurrent()->getErrands());
    }
}

extern "C" void BbsWriteMenu_ConfirmNo(S *s) {
    if (BbsWriteMenu_HasFlags(s, 0x2000)) {
        Snd_PlaySe(0x29);
    } else {
        Snd_PlaySe(0x2a);
    }
    ((BbsWriteMenu *)s)->openDialog(6, 4);
    BbsWriteMenu_ClearFlags(s, 0x400);
}

extern "C" void BbsWriteMenu_ForceClose(S *s) {
    Snd_PlaySe(0x28);
    BbsWriteMenu_ClearFlags(s, 0x40);
    ((BbsWriteMenu *)s)->hideCursor();
    BbsWriteMenu_SetScrollTarget(s, 0);
    ((MenuProc *)s)->setTransitionState(0xc);
    ((MenuProc *)s)->setPhase(1);
    BbsWriteMenu_SetFlags(s, 0x2000);
}

extern "C" void BbsWriteMenu_PlayErrorSe(S *s) {
    Snd_PlaySe(0x34);
}

extern "C" void BbsWriteMenu_StartTouchInput(S *s) {
    ((BbsWriteMenu *)s)->hideCursor();
    ((MenuProc *)s)->setMainState(0);
}

extern "C" void BbsWriteMenu_StartButtonInput(S *s) {
    ((MenuProc *)s)->restartKeyRepeat();
    ((BbsWriteMenu *)s)->showCursor();
    ((MenuProc *)s)->setMainState(6);
}

extern "C" void BbsWriteMenu_ResumeInput(S *s) {
    if (MenuCtrl_IsTouch()) {
        BbsWriteMenu_StartTouchInput(s);
    } else {
        BbsWriteMenu_StartButtonInput(s);
    }
}

extern "C" void BbsWriteMenu_ShowMessage(S *s, u32 a, u32 b) {
    volatile u8 v;
    v = gU8None;
    v = a;
    ((MenuErrorMessage *)(&s->errorMessage))->open((u8 *)&v, b, 0);
    ((MenuProc *)s)->setMainState(0x16);
    ((BbsWriteMenu *)s)->hideCursor();
}

extern "C" void BbsWriteMenu_EnterDialogTouch(S *s) {
    ((BbsWriteMenu *)s)->hideCursor();
    ((MenuProc *)s)->setMainState(5);
}

extern "C" void BbsWriteMenu_EnterDialogButtons(S *s) {
    u32 r4;
    ((MenuProc *)s)->restartKeyRepeat();
    s->confirmChoice = 1;
    ((MenuCursor *)(&s->cursor))->setAnimIfChanged(1);
    ((UiWidget *)(&s->cursor))->update();
    r4 = ((MenuBottomButtonsBody *)(&s->bottomButtons))->getTargetX(4);
    ((MenuCursorBase *)(&s->cursor))->warpTo(r4, ((MenuBottomButtonsBody *)(&s->bottomButtons))->getTargetY(4));
    ((MenuProc *)s)->setMainState(0x13);
}

extern "C" BOOL BbsWriteMenu_HasFlags(S *s, u32 m) {
    if (s->flags & m) return TRUE;
    return FALSE;
}

extern "C" void BbsWriteMenu_SetFlags(S *s, u32 m) {
    s->flags = s->flags | m;
}

extern "C" void BbsWriteMenu_ClearFlags(S *s, u32 m) {
    s->flags = s->flags & ~m;
}

extern "C" void BbsWriteMenu_RedrawText(S *s) {
    BbsRedrawStackPad pad;
    s32 i;
    u32 r6;
    u8 zb;
    u32 z14, z18;
    Text_SplitLines(s->text, s->lineStarts, &s->lastLine, 0xc0, 0x28, 0x96, 6);
    if (BbsWriteMenu_HasFlags(s, 0x10)) {
        r6 = 0;
    } else if (BbsWriteMenu_HasFlags(s, 0x400)) {
        r6 = 0;
    } else {
        r6 = 1;
    }
    i = 0;
    zb = 0;
    z14 = 0;
    z18 = 0;
    for (; i < 6; i++) {
        s32 *pp = &s->lineStarts[i];
        u32 d = s->lineStarts[i + 1] - *pp;
        LabelString *obj = &s->lineLabels[i];
        obj->clear();
        if (d != 0) {
            u32 a3 = (i == 0) ? z14 : r6;
            u32 st = (i == s->lastLine) ? 1 : z18;
            String_FromEncodedBytesEx(obj, s->text + *pp, d, a3, st);
        } else if (r6 != 0) {
            if (i == s->lastLine) {
                String_FromEncodedBytesEx(obj, &zb, 1, r6, 1);
            }
        }
    }
    for (i = 0; i < 6; i++) {
        s->lineLabels[i].createBufferLabel(s->lineCharBufs[i], 0x14, 0xe, 0xd);
    }
    BbsWriteMenu_HighlightSelection(s);
    BbsWriteMenu_SetFlags(s, 4);
    ((BbsWriteMenu *)s)->refreshKeys();
    s->lengthGauge = (Text_GetLength(s->text, 0xc0) * 0x1f) / 0xc0;
    if (s->lengthGauge > 0x1f) s->lengthGauge = 0x1f;
}

extern "C" void BbsWriteMenu_HighlightSelection(S *s) {
    u32 r4;
    u32 r0;
    u8 r1, r2;
    if (BbsWriteMenu_HasSelection(s)) {
        u32 a = s->selectionEnd;
        u32 b = s->selectionStart;
        if (b > a) {
            r4 = a;
            r0 = b - a;
        } else {
            r4 = b;
            r0 = a - b;
        }
        r1 = 0xd;
        r2 = 0xe;
    } else {
        r0 = Shared_Keyboard_GetTypedRunLength(&s->keyboard);
        if (r0 != 0) r4 = s->caretIndex - r0;
        r1 = 0xb;
        r2 = 0xd;
    }
    if (r0 != 0) BbsWriteMenu_HighlightRange(s, r1, r2, r4, r0);
}

extern "C" void BbsWriteMenu_HighlightRange(S *s, u8 a, u8 b, u32 c, u32 n) {
    s32 i;
    u32 off = 0;
    i = off;
    for (; i < 6; i++) {
        u32 d = s->lineStarts[i + 1] - s->lineStarts[i];
        if (d == 0) return;
        if (c >= off) {
            u32 cnt, e;
            e = off + d;
            if (c < e) {
                if (e > c + n) cnt = n;
                else cnt = d - (c - off);
                s->lineLabels[i].setHighlight(a, b, c - off, cnt);
                c = (u8)e;
                n -= cnt;
                if (n == 0) return;
            }
        }
        off += d;
    }
}

extern "C" void BbsWriteMenu_DrawLineLabels(S *s) {
    s32 i = 0;
    s32 z = 0;
    for (; i < 6; i++) {
        s->lineLabels[i].redrawAligned(z, z);
    }
}

extern "C" void BbsWriteMenu_UpdateLineLabels(S *s) {
    s32 i = 0;
    for (; i < 6; i++) {
        s->lineLabels[i].destroyLabel();
    }
}

extern "C" void BbsWriteMenu_Nop(S *s) {
}

extern "C" void BbsWriteMenu_UploadTextChars(S *s) {
    ((BgVramTask *)(s->textCharTask))->requestChars(s->lineCharBufs, 4, 0x11, 0x11, 0x100);
}

extern "C" void BbsWriteMenu_SetScroll(S *s, u32 v) {
    s->scrollY = v;
    s->scrollTargetY = s->scrollY;
    BbsWriteMenu_SetFlags(s, 0x20);
    s->scrollKnobY = (s->scrollY * 2) / 3;
}

extern "C" void BbsWriteMenu_SetScrollTarget(S *s, u32 v) {
    s->scrollTargetY = v;
    BbsWriteMenu_SetFlags(s, 0x20);
}

extern "C" BOOL BbsWriteMenu_IsScrolling(S *s) {
    return BbsWriteMenu_HasFlags(s, 0x20);
}

extern "C" void BbsWriteMenu_UpdateScroll(S *s) {
    u32 b7 = *(volatile u8 *)&s->scrollTargetY;
    u32 b6 = *(volatile u8 *)&s->scrollY;
    if (b6 == b7) {
        BbsWriteMenu_ClearFlags(s, 0x20);
    } else if (b6 < b7) {
        s->scrollY = s->scrollY + 8;
        if (s->scrollY > s->scrollTargetY) s->scrollY = s->scrollTargetY;
    } else if (b6 < 8) {
        s->scrollY = b7;
    } else {
        s->scrollY = s->scrollY - 8;
        if (s->scrollY < s->scrollTargetY) s->scrollY = s->scrollTargetY;
    }
    s->scrollKnobY = (s->scrollY * 2) / 3;
}

extern "C" void BbsWriteMenu_ScrollToCaret(S *s) {
    u32 a = s->scrollTargetY;
    s32 d = s->caretY - a;
    if (d < 0x18) {
        BbsWriteMenu_SetScrollTarget(s, a - (0x18 - d));
    } else if (d > 0x40) {
        BbsWriteMenu_SetScrollTarget(s, a + (d - 0x38));
    }
}

extern "C" BOOL BbsWriteMenu_TouchScrollKnob(S *s) {
    if (((MenuScrollKnob *)(&s->scrollKnob))->hitTest(gTouchCurX, gTouchCurY)) {
        s->dragStartTouchY = gTouchCurY;
        s->dragStartKnobY = (s->scrollY * 2) / 3;
        s->lastTickScrollY = s->scrollY;
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL BbsWriteMenu_IsTouchOnScrollBar(S *s) {
    s32 a = gTouchCurX;
    s32 t = gTouchCurY - 8;
    if (t < 0x10 || t > 0x38) return FALSE;
    if (a < 0xdd || a > 0xed) return FALSE;
    return TRUE;
}

extern "C" void BbsWriteMenu_SetScrollFromKnob(S *s, s32 v) {
    s32 d;
    v = (v * 3) >> 1;
    if (v < 0) v = 0;
    if (v > 0x3c) v = 0x3c;
    BbsWriteMenu_SetScroll(s, v);
    d = s->lastTickScrollY - v;
    if (d >= 4 || d <= -4) {
        Menu_PlayScrollTickSe();
        s->lastTickScrollY = v;
    }
}

extern "C" void BbsWriteMenu_DragScrollKnob(S *s) {
    BbsWriteMenu_SetScrollFromKnob(s, s->dragStartKnobY + (gTouchCurY - s->dragStartTouchY));
}

extern "C" void BbsWriteMenu_ScrollToTouch(S *s) {
    s32 t = gTouchCurY - 0x18;
    if (t < 0) t = 0;
    if (t > 0x28) t = 0x28;
    Math_StepU8(&s->scrollKnobY, (u8)t, 2);
    BbsWriteMenu_SetScrollFromKnob(s, s->scrollKnobY);
}

extern "C" void BbsWriteMenu_ScrollByPad(S *s) {
    s32 r, v;
    u16 k;
    v = s->scrollY;
    r = v;
    k = gPad[0];
    if (k & 0x40) {
        r = v - 4;
    } else if (k & 0x80) {
        r = v + 4;
    }
    if (r < 0) r = 0;
    if (r > 0x3c) r = 0x3c;
    if (v != r) Menu_PlayScrollTickSe();
    BbsWriteMenu_SetScroll(s, r);
}

extern "C" BOOL BbsWriteMenu_HasSelection(S *s) {
    if (!BbsWriteMenu_HasFlags(s, 0x100) || s->selectionStart == s->selectionEnd) return FALSE;
    return TRUE;
}

extern "C" void BbsWriteMenu_ClearSelection(S *s) {
    s->selectionStart = 0;
    s->selectionEnd = 0;
    BbsWriteMenu_ClearFlags(s, 0x100);
}

extern "C" void BbsWriteMenu_DeleteSelection(S *s) {
    u32 lo, hi;
    u32 b = s->selectionEnd;
    u32 a = s->selectionStart;
    if (a > b) {
        lo = b;
        hi = a;
    } else {
        lo = a;
        hi = b;
    }
    u8 v = (u8)Shared_Keyboard_DeleteRange(&s->keyboard, s->text, lo, hi, 0xc0);
    ((BbsWriteMenu *)s)->setCursorIndex(v);
    BbsWriteMenu_ClearSelection(s);
}

extern "C" u8 BbsWriteMenu_HitTestLine(S *s, s32 i, s32 *p) {
    u32 off = s->lineStarts[i];
    u8 out;
    u32 r = Keyboard_HitTestText(&s->keyboard, s->text + off, 0xc0 - off, 0x96, (u8)(*p - 0x30), &out);
    *p = r + 0x30;
    return (u8)(out + off);
}

extern "C" void BbsWriteMenu_SetCaretFromPoint(S *s, s32 a, s32 b) {
    s32 t;
    if (b < 0x38) b = 0x38;
    if (b >= 0x88) b = 0x87;
    s->caretX = a;
    s->caretY = b;
    t = (s->caretY - 0x28) >> 4;
    if (t > s->lastLine) t = s->lastLine;
    s->caretY = t * 16 + 0x28;
    ((BbsWriteMenu *)s)->setCursorIndex(BbsWriteMenu_HitTestLine(s, t, &s->caretX));
    BbsWriteMenu_ScrollToCaret(s);
}

BOOL BbsWriteMenu::touchTextArea() {
    s32 a = gTouchCurX;
    s32 b = gTouchCurY;
    if (b >= 0x48) {
        return FALSE;
    }
    if (a < 0x20 || a >= 0xe0) {
        return FALSE;
    }
    b += scrollTargetY + 8;
    if (a < 0x30) {
        a = 0x30;
    }
    BbsWriteMenu_SetCaretFromPoint((S *)this, a, b);
    BbsWriteMenu_SetFlags((S *)this, 0x100);
    selectionStart = caretIndex;
    selectionEnd = caretIndex;
    return TRUE;
}

void BbsWriteMenu::endTouch() {}

BOOL BbsWriteMenu::dragSelection() {
    s32 a = gTouchCurX;
    s32 b = gTouchCurY;
    u8 old = caretIndex;
    if (a < 0x30) {
        a = 0x30;
    }
    b += scrollTargetY + 8;
    BbsWriteMenu_SetCaretFromPoint((S *)this, a, b);
    selectionEnd = caretIndex;
    if (caretIndex != old) {
        return TRUE;
    }
    return FALSE;
}

void BbsWriteMenu::resetTextCursor() {
    BbsWriteMenu_SetFlags((S *)this, 0x40);
    caretX = 0x30;
    caretY = 0x38;
    setCursorIndex(headerLength);
    BbsWriteMenu_ClearSelection((S *)this);
    Keyboard_ResetKeyPalettes(&keyboard);
    refreshKeys();
}

void BbsWriteMenu::setCursorIndex(u8 v) {
    caretIndex = v;
    caretBlinkTimer = 0x10;
}

u8 BbsWriteMenu::getCharBeforeCursor() {
    if (caretIndex == 0) {
        return 0;
    }
    return text[caretIndex - 1];
}

void BbsWriteMenu::updateCaretPos() {
    s32 k = getLineOfIndex(caretIndex);
    caretY = k * 16 + 0x28;
    s32 b = lineStarts[k];
    caretX = (u8)(Text_MeasureWidth(&text[b], caretIndex - b) + 0x30);
    BbsWriteMenu_ScrollToCaret((S *)this);
}

s32 BbsWriteMenu::getLineOfIndex(s32 v) {
    s32 n, i;
    i = 0;
    n = lastLine;
    for (; i < n; i++) {
        if (v < lineStarts[i + 1]) {
            return i;
        }
    }
    if (n >= 6) {
        n = 5;
    }
    return n;
}

BOOL BbsWriteMenu::navigateText(u32 pad) {
    if (pad == 0) {
        return FALSE;
    }
    u8 cur = caretIndex;
    s32 t = getLineOfIndex(cur);
    volatile s32 old = t;
    if (MenuKeys_HasUp(pad)) {
        if (t > 1) {
            t--;
        }
    } else if (MenuKeys_HasDown(pad)) {
        t++;
        if (t > lastLine || t >= 6) {
            t--;
        }
    }
    s32 v = caretX;
    if (t != old) {
        cur = BbsWriteMenu_HitTestLine((S *)this, t, &v);
    }
    if (MenuKeys_HasLeft(pad)) {
        if (cur > headerLength) {
            cur = cur - 1;
        }
    } else if (MenuKeys_HasRight(pad)) {
        s32 n = Text_GetLength(text, 0xc0);
        s32 nx = cur + 1;
        if (nx <= n) {
            cur = nx;
        }
    }
    if (cur == caretIndex) {
        return FALSE;
    }
    setCursorIndex(cur);
    return TRUE;
}

void BbsWriteMenu::refreshKeys() {
    if (Shared_Keyboard_InsertCharMultiline(&keyboard, text, 0x86, &caretIndex, 0xc0, 0x28, 6, 0x96, 1, 1)) {
        Shared_Keyboard_EnableKey(&keyboard, 0);
    } else {
        Keyboard_DisableKey(&keyboard, 0);
    }
    if (BbsWriteMenu_HasSelection((S *)this)) {
        Shared_Keyboard_EnableKey(&keyboard, 0xb);
    } else {
        Keyboard_DisableKey(&keyboard, 0xb);
    }
    if (BbsWriteMenu_HasFlags((S *)this, 0x200)) {
        Shared_Keyboard_EnableKey(&keyboard, 0xc);
    } else {
        Keyboard_DisableKey(&keyboard, 0xc);
    }
    if (BbsWriteMenu_HasSelection((S *)this)) {
        Shared_Keyboard_DisableModifierKeys(&keyboard);
        Shared_Keyboard_EnableKey(&keyboard, 6);
    } else if (caretIndex <= headerLength) {
        Shared_Keyboard_DisableModifierKeys(&keyboard);
    } else {
        Keyboard_UpdateModifierKeys(&keyboard, getCharBeforeCursor());
    }
}

void BbsWriteMenu::openDialog(u8 v, u8 x) {
    setTransitionState(v);
    ((MenuBottomButtonsBody *)(&bottomButtons))->setSelected(x);
    setMainState(0x15);
}

void BbsWriteMenu::showCursor() {
    BbsWriteMenu_ClearFlags((S *)this, 0x800);
    Keyboard_ResetCursor(&keyboard);
    u32 a = Keyboard_GetCursorX(&keyboard);
    u32 b = Keyboard_GetCursorY(&keyboard);
    cursor.warpTo(a, b);
    ((MenuCursor *)&cursor)->setAnimIfChanged(1);
    refreshCursor();
}

void BbsWriteMenu::hideCursor() {
    ((MenuCursor *)&cursor)->setAnimIfChanged(0);
    cursor.update();
}

void BbsWriteMenu::moveCursorToTarget() {
    if (BbsWriteMenu_HasFlags((S *)this, 0x800)) {
        cursor.moveToNear(caretX, caretY - scrollTargetY, 3, 2);
        returnState = 0xc;
    } else {
        u32 a = Keyboard_GetCursorX(&keyboard);
        u32 b = Keyboard_GetCursorY(&keyboard);
        cursor.moveToNear(a, b, 3, 2);
        returnState = 6;
    }
    setMainState(7);
}

void BbsWriteMenu::moveCursorTo(s32 a, s32 b) {
    cursor.moveToNear(a, b, 3, 2);
    returnState = mainState;
    setMainState(7);
}

void BbsWriteMenu::snapCursor() {
    if (BbsWriteMenu_HasFlags((S *)this, 0x800)) {
        cursor.warpTo(caretX, caretY - scrollTargetY);
    } else {
        u32 a = Keyboard_GetCursorX(&keyboard);
        u32 b = Keyboard_GetCursorY(&keyboard);
        cursor.warpTo(a, b);
    }
    cursor.update();
}

void BbsWriteMenu::pressCursor() {
    ((MenuCursor *)&cursor)->setPosePress();
    setMainState(8);
}

void BbsWriteMenu::releaseCursor() {
    Shared_Keyboard_ClearHighlight(&keyboard);
    cursor.setPoseRelease();
    setMainState(10);
}

void BbsWriteMenu::refreshCursor() {
    cursor.setPoseIdle();
    cursor.update();
}

void BbsWriteMenu::censorText() {
    u8 *c3 = text;
    EncodedString_SetRaw(&encodedText, c3, 0xc0);
    censorString.fromEncoded(&encodedText, 0, 0);
    if (String_CensorTaboo(&censorString)) {
        encodedText.fromMsgString(&censorString);
        StrBuf_GetBytes(reinterpret_cast<StrBuf *>(static_cast<EncodedStringBase *>(&encodedText)), c3, 0xc0);
    }
}

void BbsWriteMenu::showTodayDate() {
    u8 t[16];
    s32 v;
    Clock_GetDate(t);
    t[4] = 0x37;
    t[5] = 0x35;
    v = t[2];
    t[6] = v / 10 + 0x35;
    t[7] = v % 10 + 0x35;
    t[8] = 0;
    String_FromEncodedBytes(&lineLabels[0], &t[4], 5);
    placeLabel(0, 0x111, 4, 1);
    v = t[1];
    t[4] = v / 10 + 0x35;
    t[5] = v % 10 + 0x35;
    v = t[0];
    t[6] = v / 10 + 0x35;
    t[7] = v % 10 + 0x35;
    String_FromEncodedBytes(&lineLabels[1], &t[4], 5);
    placeLabel(1, 0x116, 4, 1);
}

void BbsWriteMenu::clearPostNumberLabel() {
    ((MsgString *)(&lineLabels[2]))->clear();
    placeLabel(2, 0x11a, 5, 0);
}

void BbsWriteMenu::placeLabel(s32 idx, u32 a, u32 b, s32 c) {
    LabelString *p = &lineLabels[idx];
    ((LabelString *)(p))->createSmallLabel(4, a, b, 0xf, 0xa, c);
    ((LabelString *)(p))->redrawAligned(0, 0);
}

void BbsWriteMenu::beginDialogDim() {
    Gfx2d_BeginSubObjWinBrightness();
    Gfx2d_SetSubBrightness(-6);
    ((MenuBottomButtonsBody *)(&bottomButtons))->enableObjWindow();
    Gfx2d_SetSubWin1Planes(0x1f, 0);
    Gfx2d_EnableSubWindows(2);
    Gfx2d_SetSubWin1Rect(0x2c, 0x20, 0xd4, 0x80);
}

void BbsWriteMenu::endDialogDim() {
    Gfx2d_EndSubObjWinBrightness();
    ((MenuBottomButtonsBody *)(&bottomButtons))->disableObjWindow();
    Gfx2d_DisableSubWindows(2);
}

void BbsWriteMenu::sendPostToPeers() {
    if (((CommManager *)(gCommManager))->isOnline()) {
        Heap *heap = gMenuHeap;
        u8 *buf = (u8 *)Heap_AllocTail(heap, 0xc1);
        buf[0] = 0;
        MI_CpuCopy8(text, &buf[1], 0xc0);
        void *g = gCommManager;
        ((CommManager *)(g))->beginRecord();
        ((CommManager *)(g))->writeRecord(buf, 0xc1);
        ((CommManager *)(g))->endRecord(0x16, 4);
        sendSeq = ((CommManager *)(g))->getSendSeq();
        Heap_Free(heap, buf);
    }
}

BOOL BbsWriteMenu::isPostSendConfirmed() {
    if (((CommManager *)(gCommManager))->isOnline()) {
        if (Comm_IsSeqConfirmed(sendSeq) == 0) {
            return FALSE;
        }
    }
    return TRUE;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov112_02296840) {
    HOST_OVERLAY_VAR(data_ov112_022999b8),
    HOST_OVERLAY_VAR(data_ov112_02299ad8),
    HOST_OVERLAY_VAR(data_ov112_02299ac0),
    HOST_OVERLAY_VARS_END
};
