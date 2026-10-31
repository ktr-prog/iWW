#include "uptr.h"
#include "host_shared_calls.h"
#include "types.h"
#include "Unk_020d8c7c.h"
#include "ui/CursorMotion.h"
#include "item/Letter.h"
#include "menu/InventoryItemGrid.h"
#include "menu/LetterGrid.h"
#include "menu/InventoryBg.h"
#include "ui/LetterRenderer.h"
#include "menu/MenuProc.h"
#include "ui/HandCursor.h"
#include "item/LetterView.h"
#include "item/PlayerMailbox.h"
#include "ui/LabelButton.h"
#include "menu/MenuLauncher.h"
#include "ui/LabelBalloon.h"
#include "gfx/BgVramTask.h"
#include "ui/TouchPromptBalloon.h"
#include "menu/MenuLabelButton.h"
#include "menu/MenuCursor.h"
#include "player/PlayerData.h"
#include "menu/MenuBottomButtons.h"
#include "menu/PopupChoiceMenu.h"
#include "menu/MenuErrorMessage.h"
#include "sys/ProcProfile.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0203c23c.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_02095cdc.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov002/unk_ov002_022013ac.h"
#include "proto/ov002/unk_ov002_02202fac.h"
#include "proto/ov094/unk_ov094_02292360.h"
#include "proto/ov094/unk_ov094_02292da8.h"
#include "proto/ov094/unk_ov094_02293b90.h"
#include "proto/ov106/unk_ov106_02294c40.h"


class MailboxMenu;
typedef void (MailboxMenu::*Unk_ov106_02298180_Fn)();


extern "C" {
extern u8 gU8None;
extern u16 gPad[];

u16 Item_MakePaper(u32 a, s32 b);
s32 PopupChoice_MoveCursor(void *a, s32 b, void *c, u32 d);
s32 PopupChoice_TickDecideDelay(void *a);
u32 PopupChoice_DecideCancel(void *p, s32 a);
void PopupChoice_DecideRow(void *a, s32 b, s32 c);
void PopupChoice_ForceClose(void *a);
void PopupChoice_Update(void *a);
void PopupChoice_Close(void *p, u32 v);
void PopupChoice_Open(void *p, u32 v);

}

class LetterView;
class LetterRenderer;
class LetterView;
class PlayerMailbox;
class PlayerData;
class Letter;
class LabelBalloon;
class HandCursor;
class LabelButton;
class BgVramTask;
class BgVramTaskPair;
class PopupChoiceMenuBody;
class PopupChoiceIdList;
class MenuCursorBase;
class MenuBottomButtonsBody;
class MenuErrorMessage;
class TouchPromptBalloon;
class PopupChoiceMenu;
class CursorMotion;
class MenuCursorBuf0;
class MenuCursor;
class MenuBottomButtons;
class MenuLabelButton;
class MenuLauncher;
class InventoryBg;
class InventoryItemGrid;
class LetterGrid;



























class MailboxMenu : public MenuProc {
public:
    MailboxMenu()
        : bgTasks(), pocketGrid(), letterGrid(), inventoryBg(), nameBalloon(), flyMotion(), cursor(), popup(), errorMessage(), letterView(),
          letterCloseButton(), mailboxLetters(), unk_32ac(), bottomButtons(), heldLetter(), swapLetter() {}

    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onDraw();
    virtual BOOL execTransition();
    virtual BOOL execMain();
    virtual BOOL execPhase3();
    virtual BOOL execPhase4();
    virtual BOOL execClosed();

    BOOL hasTouchMoved();
    BOOL isSlotEmpty(u32 a);
    BOOL isSlotDisabled(u32 a);
    BOOL dropHeldOnSlot(u32 a);
    BOOL isButtonSlot(u32 a);
    BOOL isMailboxSlot(u32 v);
    BOOL isLetterSlot(u32 v);
    s32 getCursorTargetY();
    s32 getCursorTargetX();
    s32 getSlotY(u32 a);
    s32 getSlotX(u32 a);
    u32 getSlotAt(u32 a, s32 b, s32 c);
    u32 findFirstMailboxLetter();
    u32 findFreePocketSlot();
    u8 fromLetterGridIndex(u32 a);
    u8 toLetterGridIndex(u32 a);
    Letter *getSlotLetter(u32 a);
    void cursorToPopupTop();
    void cancelPopup();
    void moveCursorToPopupRow();
    void moveCursorToPoint(s32 a, s32 b);
    void moveCursorToTarget();
    void hideCursor();
    void showCursor();
    void exchangeHeldWith(u32 a);
    void releaseHeldTo(u32 a);
    void pickUpFrom(u32 a);
    void getFlyPos();
    void getHandPos();
    void getDragPos();
    void drawHeldItem();
    void updateBalloonForCursor();
    void placeBalloon();
    void setHoverSlot(u32 a);
    void clearHoverSlot();
    void setFocusSlot(u32 a);
    void clearFocusSlot();
    void disableAllPockets();
    void registerLetterPaper(LetterView *p);
    void putLetterInSlot(u32 a, Letter *p);
    void cancelBgTasks();
    void pressPromptTab4();
    void pressPromptTab3();
    void showMessage(u32 v);
    void pickUpAndFlyTo(u32 a, u32 b);
    void flyHeldToOtherList(u32 a, s32 c);
    void flyHeldTo(u32 a, u32 b);
    void pickUpAtSlot(u32 a);
    void beginDragFromSlot(u32 a);
    void beginTouchOnSlot(u32 a);
    void resumePromptInput();
    void startPromptButtonInput();
    void startPromptTouchInput();
    void resumeInput();
    void startButtonInput();
    void startTouchInput();
    void mainAct26();
    void mainAct25();
    void mainAct24();
    void mainAct23();
    void mainAct22();
    void mainAct21();
    void mainAct20();
    void mainAct1F();
    void mainAct1E();
    void mainAct1D();
    void mainAct1C();
    void mainAct1B();
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
    void mainAct05();
    void mainAct04();
    BOOL testFlags(u32 mask);
    BOOL moveCursorByPad(u32 pad, u32 x);
    void clearFlags(u32 mask);
    void setFlags(u32 mask);
    void pressCloseTab();
    void onChoiceDiscard();
    void startDiscardLetter();
    void forceCloseFromLetterView();
    void closeLetterView();
    void startReadLetter();
    void moveCursorOnButton(u32 pad);
    void moveCursorInMailbox(u32 pad, u32 x);
    void moveCursorInPocketLetters(u32 pad, u32 x);
    void openDiscardConfirm();
    void selectLetter(u32 idx, u32 x);
    void cancelPopupForButtons();
    void openPopup(u32 x);
    void onPopupChoice();
    void beginSwapAt(u32 v);
    void beginPutDownAt(u32 v);
    void beginMoveFromPopup();
    void releaseCursor();
    void pressCloseButton();
    void refreshCursor();
    void showCursorAtSlot();
    void mainAct03();
    void mainAct02();
    void mainAct01();
    void mainAct00();
    void loadObjGraphics();
    void loadBoxBg();
    void loadInventoryBg();
    void postStateUpdate();
    void preStateUpdate();
    void postInputUpdate();
    void preInputUpdate();
    void releaseResources();
    void initParts();
    void scrollBoxBg();
    void scrollMainBg();
    void scrollLetterViewBg();
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

    /* 0x91 */ u8 unk_91[3];
    /* 0x94 */ u32 stateFlags;
    /* 0x98 */ s32 slideY;
    /* 0x9c */ s32 boxSlideX;
    /* 0xa0 */ s32 buttonsSlideY;
    /* 0xa4 */ s32 dragOffsetX;
    /* 0xa8 */ s32 dragOffsetY;
    /* 0xac */ s32 handX;
    /* 0xb0 */ s32 handY;
    /* 0xb4 */ u8 handKind;
    /* 0xb5 */ u8 touchedSlot;
    /* 0xb6 */ u8 balloonSlot;
    /* 0xb7 */ u8 heldSlot;
    /* 0xb8 */ u8 cursorSlot;
    /* 0xb9 */ u8 selectedSlot;
    /* 0xba */ u8 targetSlot;
    /* 0xbb */ u8 returnState;
    /* 0xbc */ u8 popupChoice;
    /* 0xbd */ u8 popupRow;
    /* 0xbe */ u8 promptChoice;
    /* 0xbf */ u8 touchHoldDelay;
    /* 0x00c0 */ BgVramTaskPair bgTasks[1];
    /* 0x00f8 */ InventoryItemGrid pocketGrid;
    /* 0x0b58 */ LetterGrid letterGrid;
    /* 0x0b80 */ InventoryBg inventoryBg;
    /* 0x2160 */ TouchPromptBalloon nameBalloon;
    /* 0x2220 */ CursorMotion flyMotion;
    /* 0x2238 */ MenuCursorBuf0 cursor;
    /* 0x229c */ PopupChoiceMenu popup;
    /* 0x2590 */ PopupChoiceIdList choiceList;
    /* 0x259b */ u8 pad_259b[1];
    /* 0x259c */ MenuErrorMessage errorMessage;
    /* 0x26a4 */ LetterRenderer letterView;
    /* 0x28b4 */ MenuLabelButton letterCloseButton;
    /* 0x2924 */ Letter mailboxLetters[10];
    /* 0x32ac */ Letter unk_32ac[10];
    /* 0x3c34 */ MenuBottomButtons bottomButtons;
    /* 0x3d98 */ Letter heldLetter;
    /* 0x3e8c */ Letter swapLetter;
};

static inline BOOL Unk_ov106_022966b8_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        return TRUE;
    }
    return FALSE;
}

static inline BOOL Unk_ov106_02296ee4_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        return TRUE;
    }
    return FALSE;
}

static inline BOOL Unk_ov106_02297294_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" ProcProfile sMailboxMenuProfile = {(void *(*)())MailboxMenu_Create, 0x99, 0x9d};

extern "C" MailboxMenu *MailboxMenu_Create() { return new MailboxMenu(); }

BOOL MailboxMenu::onCreate() {
    initParts();
    setTransitionState(0);
    setPhase(0);
    return TRUE;
}

BOOL MailboxMenu::onDelete() {
    ((MenuLauncher *)ProcBase_GetParent(this))->onChildClosed();
    releaseResources();
    return TRUE;
}

BOOL MailboxMenu::onDraw() {
    if (!testFlags(1)) {
        return TRUE;
    }
    nameBalloon.draw();
    if (MenuCtrl_IsButtons()) {
        ((MenuCursorBase *)&cursor)->drawWrapped();
    }
    drawHeldItem();
    if (testFlags(2)) {
        ((MenuBottomButtons *)&bottomButtons)->drawAt(buttonsSlideY);
        s32 t = slideY - 0x10;
        InventoryItemGrid_DrawPockets(&pocketGrid, 0, t);
        ((LetterGrid *)&letterGrid)->drawPocketLetters(0, t);
        Shared_InventoryBg_DrawSprite(&inventoryBg, t);
    }
    if (testFlags(0x200)) {
        ((LetterGrid *)&letterGrid)->drawLetters23(boxSlideX, -0x10);
    }
    if (testFlags(0x80)) {
        ((LabelButton *)&letterCloseButton)->setPos(0, getSlideOffsetY());
        letterCloseButton.draw();
    }
    return TRUE;
}

BOOL MailboxMenu::execTransition() {
    static Unk_ov106_02298180_Fn tbl[11] = {
        &MailboxMenu::transitionAct00,
        &MailboxMenu::transitionAct01,
        &MailboxMenu::transitionAct02,
        &MailboxMenu::transitionAct03,
        &MailboxMenu::transitionAct04,
        &MailboxMenu::transitionAct05,
        &MailboxMenu::transitionAct06,
        &MailboxMenu::transitionAct07,
        &MailboxMenu::transitionAct08,
        &MailboxMenu::transitionAct09,
        &MailboxMenu::transitionAct0A};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}

void MailboxMenu::runMainState() {
    static Unk_ov106_02298180_Fn tbl[39] = {
        &MailboxMenu::mainAct00,
        &MailboxMenu::mainAct01,
        &MailboxMenu::mainAct02,
        &MailboxMenu::mainAct03,
        &MailboxMenu::mainAct04,
        &MailboxMenu::mainAct05,
        &MailboxMenu::mainAct06,
        &MailboxMenu::mainAct07,
        &MailboxMenu::mainAct08,
        &MailboxMenu::mainAct09,
        &MailboxMenu::mainAct0A,
        &MailboxMenu::mainAct0B,
        &MailboxMenu::mainAct0C,
        &MailboxMenu::mainAct0D,
        &MailboxMenu::mainAct0E,
        &MailboxMenu::mainAct0F,
        &MailboxMenu::mainAct10,
        &MailboxMenu::mainAct11,
        &MailboxMenu::mainAct12,
        &MailboxMenu::mainAct13,
        &MailboxMenu::mainAct14,
        &MailboxMenu::mainAct15,
        &MailboxMenu::mainAct16,
        &MailboxMenu::mainAct17,
        &MailboxMenu::mainAct18,
        &MailboxMenu::mainAct19,
        &MailboxMenu::mainAct1A,
        &MailboxMenu::mainAct1B,
        &MailboxMenu::mainAct1C,
        &MailboxMenu::mainAct1D,
        &MailboxMenu::mainAct1E,
        &MailboxMenu::mainAct1F,
        &MailboxMenu::mainAct20,
        &MailboxMenu::mainAct21,
        &MailboxMenu::mainAct22,
        &MailboxMenu::mainAct23,
        &MailboxMenu::mainAct24,
        &MailboxMenu::mainAct25,
        &MailboxMenu::mainAct26};
    (this->*tbl[mainState])();
}

BOOL MailboxMenu::execMain() {
    MenuCtrl_TickForceClose();
    if (MenuCtrl_IsForceCloseDue()) {
        u32 s = mainState;
        if (s == 0 || s == 1 || s == 7) {
            hideCursor();
            pressCloseTab();
            ((TouchPromptBalloon *)&nameBalloon)->hide(0);
            return TRUE;
        }
    }
    preInputUpdate();
    runMainState();
    postInputUpdate();
    return TRUE;
}

BOOL MailboxMenu::execPhase3() {
    return TRUE;
}

BOOL MailboxMenu::execPhase4() {
    return TRUE;
}

BOOL MailboxMenu::execClosed() {
    MenuCtrl_SetResult(1);
    LetterList_Compact(mailboxLetters, 10);
    Letter *p = ((PlayerMailbox *)PlayerData_GetMailbox(PlayerData_GetCurrent()))->getLetter(0);
    for (s32 i = 0; i < 10; i++) {
        Letter_Copy((LetterView *)&p[i], (LetterView *)&mailboxLetters[i]);
    }
    ProcBase_RequestDelete(this);
    return TRUE;
}

void MailboxMenu::transitionAct00() {
    MailboxMenu_SetupBgLayers();
    loadInventoryBg();
    setTransitionState(1);
}

void MailboxMenu::transitionAct01() {
    loadObjGraphics();
    Shared_InventoryItemGrid_LoadPockets(&pocketGrid);
    Shared_LetterGrid_LoadPocketLetters(&letterGrid);
    LetterGrid_SetLetters23(&letterGrid, (u8 *)mailboxLetters);
    disableAllPockets();
    beginSubSlideIn(8, 0, 0, 0x30);
    Gfx2d_ShowLayer(6);
    setTransitionState(2);
    setFlags(1);
    setFlags(2);
    scrollMainBg();
}

void MailboxMenu::transitionAct02() {
    s32 r = stepSlideIn(0);
    scrollMainBg();
    if (r != 0) {
        loadBoxBg();
        beginSubSlideIn(2, 0, 2, 0x30);
        setSlideExtent(0xc0);
        Gfx2d_ShowLayer(4);
        setFlags(0x200);
        scrollBoxBg();
        setTransitionState(3);
    }
}

void MailboxMenu::transitionAct03() {
    if (stepSlideIn(0)) {
        setPhase(2);
        if (testFlags(0x4000)) {
            clearFlags(0x4000);
            setMainState(0x24);
        } else {
            resumeInput();
        }
    }
    scrollBoxBg();
}

void MailboxMenu::transitionAct04() {
    ((TouchPromptBalloon *)&nameBalloon)->hide(1);
    hideCursor();
    if (!testFlags(0x100)) {
        ((MenuLauncher *)ProcBase_GetParent(this))->setNextRequest(0x44, 1);
    }
    beginSubSlideOut(2, 0, 2, 0x30);
    setSlideExtent(0xc0);
    setTransitionState(5);
}

void MailboxMenu::transitionAct05() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(4);
        clearFlags(0x200);
        beginSubSlideOut(8, 0, 0, 0x30);
        setTransitionState(6);
        transitionAct06();
    } else {
        scrollBoxBg();
    }
}

void MailboxMenu::transitionAct06() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(6);
        clearFlags(2);
        if (testFlags(0x100)) {
            setTransitionState(7);
            transitionAct07();
        } else {
            clearFlags(1);
            setPhase(5);
        }
    } else {
        scrollMainBg();
    }
}

void MailboxMenu::transitionAct07() {
    LetterView *t = (LetterView *)getSlotLetter(selectedSlot);
    registerLetterPaper(t);
    Letter_MarkRead(t);
    letterView.show(t, 3, 4, 1);
    beginSubSlideIn(3, 0, 0, 0x30);
    Gfx2d_ShowLayer(3);
    Gfx2d_ShowLayer(4);
    scrollLetterViewBg();
    setTransitionState(8);
    ((MenuLabelButton *)&letterCloseButton)->showDefault(0x88);
    setFlags(0x80);
}

void MailboxMenu::transitionAct08() {
    if (stepSlideIn(0)) {
        setPhase(2);
        if (MenuCtrl_IsTouch()) {
            setMainState(5);
        } else {
            setMainState(9);
        }
    } else {
        scrollLetterViewBg();
    }
}

void MailboxMenu::transitionAct09() {
    beginSubSlideOut(3, 0, 0, 0x30);
    scrollLetterViewBg();
    setTransitionState(10);
}

void MailboxMenu::transitionAct0A() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(3);
        Gfx2d_ResetLayer(4);
        clearFlags(0x80);
        if (testFlags(0x8000)) {
            setPhase(5);
            clearFlags(1);
        } else {
            transitionAct00();
        }
    } else {
        scrollLetterViewBg();
    }
}

void MailboxMenu::scrollLetterViewBg() {
    applySlideOffset(3, 0, 0);
    applySlideOffset(4, 0, 0);
}

void MailboxMenu::scrollMainBg() {
    applySlideOffset(6, 0, -16);
    slideY = getSlideOffsetY();
    buttonsSlideY = getSlideOffsetY();
}

void MailboxMenu::scrollBoxBg() {
    applySlideOffset(4, 0, -16);
    boxSlideX = getSlideOffsetX();
}

void MailboxMenu::initParts() {
    s32 i;
    Letter *p;
    stateFlags = 0;
    InventoryItemGrid_Init(&pocketGrid, 2);
    ((LetterGrid *)&letterGrid)->init(1);
    Shared_InventoryBg_Init(&inventoryBg, 6);
    balloonSlot = 0x20;
    ((CursorMotion *)&flyMotion)->reset();
    handKind = 0;
    cursorSlot = 0xb;
    ((PopupChoiceMenu *)&popup)->init(3, 0, 0);
    ((LetterRenderer *)&letterView)->setLayer(3);
    for (i = 0; i < 10; i++) {
        Letter_Clear((LetterView *)&mailboxLetters[i]);
    }
    p = ((PlayerMailbox *)PlayerData_GetMailbox(PlayerData_GetCurrent()))->getLetter(0);
    for (i = 0; i < 10; i++) {
        Letter_Copy((LetterView *)&mailboxLetters[i], (LetterView *)&p[i]);
    }
    setFlags(0x4000);
    touchHoldDelay = 0;
}

void MailboxMenu::releaseResources() {
    cancelBgTasks();
    InventoryBg_Exit(&inventoryBg);
    Shared_InventoryItemGrid_Exit(&pocketGrid);
    PopupChoice_ForceClose(&popup);
    ((LetterRenderer *)&letterView)->release();
    ((MenuBottomButtons *)&bottomButtons)->freeTexts();
}

void MailboxMenu::preInputUpdate() {
    preStateUpdate();
    cursor.update();
}

void MailboxMenu::postInputUpdate() {
    postStateUpdate();
}

void MailboxMenu::preStateUpdate() {
    cancelBgTasks();
    Shared_InventoryBg_PreUpdate(&inventoryBg);
    InventoryItemGrid_PreUpdate(&pocketGrid);
    ((LetterGrid *)&letterGrid)->updateCursorLift();
    ((MenuBottomButtons *)&bottomButtons)->freeTexts();
}

void MailboxMenu::postStateUpdate() {
    Shared_PopupChoice_Update(&popup);
    InventoryBg_Update(&inventoryBg);
    if (((TouchPromptBalloon *)&nameBalloon)->updatePrompt()) {
        placeBalloon();
    }
}

extern "C" void MailboxMenu_SetupBgLayers() {
    Gfx2d_SetLayerPriority(6, 2);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
    Gfx2d_SetLayerPriority(4, 1);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
}

void MailboxMenu::loadInventoryBg() {
    InventoryBg_Load(&inventoryBg, 0);
}

void MailboxMenu::loadBoxBg() {
    void *h = gCurrentHeap;
    Gfx2d_LoadPaletteFile("menu/inventory/b_itm_post.bpl", h, 4, 4, 4, 4);
    Gfx2d_LoadScreenFile("menu/inventory/b_itm_bg_ltr2.bsc", h, 4);
    Gfx2d_LoadCharFile("menu/inventory/b_itm_post.bch", h, 4, 0x1e2, 0x1e2, 0x227);
}

void MailboxMenu::loadObjGraphics() {
    InventoryBg_LoadObjGraphics();
    MenuButtons_LoadTextColors();
    ((MenuBottomButtons *)&bottomButtons)->setLayoutSingle05(0x88);
}

void MailboxMenu::mainAct00() {
    if (checkSwitchToButtons(1)) {
        startButtonInput();
    } else {
        if (Unk_ov106_02297294_Both()) {
            s32 r = getSlotAt(gTouchCurX, gTouchCurY + 0x10, 1);
            if (r != 0x20) {
                beginTouchOnSlot(r);
            } else if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(9)) {
                pressCloseTab();
            }
        }
    }
}

void MailboxMenu::mainAct01() {
    if (gTouchHeld == 0) {
        if (testFlags(4)) {
            setMainState(3);
            runMainState();
        } else {
            setMainState(0);
            ((TouchPromptBalloon *)&nameBalloon)->setAutoCloseTimer(0x3c);
        }
    } else {
        if (testFlags(4)) {
            if (hasTouchMoved()) {
                beginDragFromSlot(touchedSlot);
                return;
            }
            if (((TouchPromptBalloon *)&nameBalloon)->isOpenOrOpening()) {
                if (touchHoldDelay != 0) {
                    touchHoldDelay--;
                } else {
                    selectLetter(touchedSlot, 1);
                    setMainState(2);
                }
                return;
            }
        }
        ((TouchPromptBalloon *)&nameBalloon)->commitOpen();
    }
}

void MailboxMenu::mainAct02() {
    if (MenuCtrl_IsForceCloseDue()) {
        setMainState(6);
    } else if (gTouchHeld == 0) {
        setMainState(6);
    } else if (testFlags(4) && hasTouchMoved()) {
        beginDragFromSlot(touchedSlot);
        PopupChoice_Close(&popup, 0);
        ((TouchPromptBalloon *)&nameBalloon)->hide(1);
    }
}

void MailboxMenu::mainAct03() {
    if (((TouchPromptBalloon *)&nameBalloon)->isOpenOrOpening()) {
        if (touchHoldDelay != 0) {
            touchHoldDelay--;
        } else {
            selectLetter(touchedSlot, 1);
            setMainState(2);
        }
    }
}

void MailboxMenu::mainAct04() {
    s32 p, t;
    if (MenuCtrl_IsForceCloseDue()) {
        releaseHeldTo(heldSlot);
        pressCloseTab();
        ((TouchPromptBalloon *)&nameBalloon)->hide(0);
    } else {
        getDragPos();
        clearHoverSlot();
        p = handX + 8;
        t = getSlotAt(p, handY + 0x18, 0);
        if (t != 0x20) {
            if (gTouchHeld == 0) {
                if (isLetterSlot(heldSlot) && isMailboxSlot(t)) {
                    flyHeldTo(heldSlot, 4);
                } else if (isMailboxSlot(heldSlot) && isLetterSlot(t)
                           && isSlotEmpty(t) == 0) {
                    flyHeldTo(heldSlot, 4);
                } else if (isSlotDisabled(t) != 0 || dropHeldOnSlot(t) == 0) {
                    flyHeldToOtherList(heldSlot, p);
                } else {
                    Inventory_PlayPutDownSe();
                    resumeInput();
                }
            } else {
                if (isLetterSlot(heldSlot) && isMailboxSlot(t)) {
                } else {
                    setHoverSlot(t);
                }
            }
        } else if (gTouchHeld == 0) {
            flyHeldToOtherList(heldSlot, p);
        }
    }
}

void MailboxMenu::mainAct05() {
    if (MenuCtrl_IsForceCloseDue()) {
        forceCloseFromLetterView();
    } else if (checkSwitchToButtons(1)) {
        setMainState(9);
    } else {
        if (((MenuLabelButton *)&letterCloseButton)->isTouched()) {
            closeLetterView();
        }
    }
}

void MailboxMenu::mainAct06() {
    if (((PopupChoiceMenuBody *)&popup)->isOpen()) {
        if (MenuCtrl_IsForceCloseDue()) {
            cancelPopupForButtons();
        } else if (checkSwitchToButtons(1)) {
            cancelPopupForButtons();
        } else {
            if (Unk_ov106_02296ee4_Both()) {
                s32 t = ((PopupChoiceMenuBody *)&popup)->hitTestRowOrLast(gTouchCurX, gTouchCurY);
                if (t >= 0) {
                    if (testFlags(0x10000) == 0 || t != 0) {
                        u32 r;
                        popupChoice = choiceList.values[t];
                        r = 1;
                        if (popupChoice == 2) {
                            r = 0;
                            Snd_PlaySe(0x24);
                        }
                        PopupChoice_DecideRow(&popup, t, r);
                        setMainState(0x17);
                    }
                }
            }
        }
    }
}

void MailboxMenu::mainAct07() {
    if (checkSwitchToTouch()) {
        startTouchInput();
        ((TouchPromptBalloon *)&nameBalloon)->hide(1);
    } else {
        s32 v = takeRepeatedKeys();
        if (moveCursorByPad(v, 0)) {
            updateBalloonForCursor();
            moveCursorToTarget();
            ((TouchPromptBalloon *)&nameBalloon)->hide(0);
        } else {
            if (isSlotDisabled(cursorSlot) != 0) goto tail;
            {
                u32 k = gPad[1];
                if (k & 1) {
                    if (isLetterSlot(cursorSlot) || isMailboxSlot(cursorSlot)) {
                        if (isSlotEmpty(cursorSlot) == 0) {
                            selectLetter(cursorSlot, 0);
                        }
                    } else if (isButtonSlot(cursorSlot)) {
                        pressCloseButton();
                    }
                } else if (k & 0x800) {
                    if (isMailboxSlot(cursorSlot)) {
                        if (isSlotEmpty(cursorSlot) == 0) {
                            s32 r = findFreePocketSlot();
                            if (r != 0x20) {
                                pickUpAndFlyTo(cursorSlot, r);
                                ((TouchPromptBalloon *)&nameBalloon)->hide(1);
                            }
                        }
                    }
                } else {
                    goto tail;
                }
            }
            return;
tail:
            {
                u32 k = gPad[1];
                if ((k & 8) || (k & 2)) {
                    hideCursor();
                    pressCloseTab();
                    ((TouchPromptBalloon *)&nameBalloon)->hide(0);
                } else {
                    ((TouchPromptBalloon *)&nameBalloon)->commitOpen();
                }
            }
        }
    }
}

void MailboxMenu::mainAct08() {
    if (MenuCtrl_IsForceCloseDue()) {
        releaseHeldTo(heldSlot);
        hideCursor();
        pressCloseTab();
        ((TouchPromptBalloon *)&nameBalloon)->hide(0);
    } else {
        s32 v = takeRepeatedKeys();
        if (moveCursorByPad(v, 1)) {
            updateBalloonForCursor();
            moveCursorToTarget();
            ((TouchPromptBalloon *)&nameBalloon)->hide(0);
        } else {
            u32 k = gPad[1];
            if (k & 1) {
                if (isLetterSlot(cursorSlot)) {
                    if (isMailboxSlot(heldSlot)) {
                        if (isSlotEmpty(cursorSlot) == 0) return;
                    }
                }
                if (isSlotDisabled(cursorSlot) == 0) {
                    if (isSlotEmpty(cursorSlot)) {
                        beginPutDownAt(cursorSlot);
                    } else {
                        beginSwapAt(cursorSlot);
                    }
                }
            } else if (k & 2) {
                beginPutDownAt(heldSlot);
            } else {
                getHandPos();
                ((TouchPromptBalloon *)&nameBalloon)->commitOpen();
            }
        }
    }
}

void MailboxMenu::mainAct09() {
    if (MenuCtrl_IsForceCloseDue()) {
        forceCloseFromLetterView();
    } else {
        if (((HandCursor *)&cursor)->getAnim() == 0) {
            s32 a = ((MenuLabelButton *)&letterCloseButton)->getAnchorX(1);
            s32 b = ((MenuLabelButton *)&letterCloseButton)->getAnchorY(1);
            ((MenuCursorBase *)&cursor)->warpTo(a, b);
            ((MenuCursor *)&cursor)->setAnimIfChanged(1);
        }
        if (checkSwitchToTouch()) {
            hideCursor();
            setMainState(5);
        } else {
            u32 k = gPad[1];
            if ((k & 1) || (k & 2)) {
                ((MenuCursor *)&cursor)->setPosePress();
                setMainState(10);
            }
        }
    }
}

void MailboxMenu::mainAct0A() {
    if (((HandCursor *)&cursor)->isAnimDone()) {
        closeLetterView();
    }
}

void MailboxMenu::mainAct0B() {
    if (MenuCtrl_IsForceCloseDue()) {
        cancelPopupForButtons();
    } else if (checkSwitchToTouch()) {
        cancelPopupForButtons();
    } else {
        s32 v = takeRepeatedKeys();
        u8 f = (u8)testFlags(0x10000);
        if (PopupChoice_MoveCursor(&popup, v, &popupRow, f)) {
            moveCursorToPopupRow();
        } else {
            u32 k = gPad[1];
            if (k & 1) {
                ((MenuCursor *)&cursor)->setPosePress();
                setMainState(0xc);
            } else if (k & 2) {
                cancelPopup();
            }
        }
    }
}

void MailboxMenu::mainAct0C() {
    if (((HandCursor *)&cursor)->isAnimDone()) {
        u32 r;
        popupChoice = choiceList.values[popupRow];
        r = 1;
        if (popupChoice == 2) {
            r = 0;
            Snd_PlaySe(0x24);
        }
        PopupChoice_DecideRow(&popup, popupRow, r);
        setMainState(0x17);
    }
}

void MailboxMenu::mainAct0D() {
    if (((MenuCursorBase *)&cursor)->isMoving() == 0) {
        setMainState(returnState);
        if (returnState == 7) {
            setFocusSlot(cursorSlot);
        }
        runMainState();
    }
    getHandPos();
}

void MailboxMenu::mainAct0E() {
    if (((HandCursor *)&cursor)->isAnimDone()) {
        if (cursorSlot == 0x1f) {
            pressCloseTab();
        } else {
            releaseCursor();
        }
    }
}

void MailboxMenu::mainAct0F() {
    if (((HandCursor *)&cursor)->isAnimDone()) {
        refreshCursor();
        setMainState(7);
    }
}

void MailboxMenu::mainAct10() {
    if (((MenuCursorBase *)&cursor)->isGripping()) {
        pickUpAtSlot(cursorSlot);
        setMainState(0x11);
    }
}

void MailboxMenu::mainAct11() {
    if (((HandCursor *)&cursor)->isAnimDone()) {
        setMainState(returnState);
    }
    getHandPos();
}

void MailboxMenu::mainAct12() {
    if (((MenuCursorBase *)&cursor)->isGripping() == 0) {
        u32 a = targetSlot;
        if (cursorSlot == a) {
            dropHeldOnSlot(a);
            updateBalloonForCursor();
            setMainState(7);
            Inventory_PlayPutDownSe();
        } else {
            flyHeldTo(a, 4);
        }
    } else {
        getHandPos();
    }
}

void MailboxMenu::mainAct13() {
    if (((MenuCursorBase *)&cursor)->func_ov002_022028fc() == 0) {
        exchangeHeldWith(targetSlot);
        setFlags(0x40);
        setMainState(0x14);
        updateBalloonForCursor();
    } else {
        setMainState(7);
    }
}

void MailboxMenu::mainAct14() {
    if (((HandCursor *)&cursor)->isAnimDone()) {
        setMainState(returnState);
    }
    if (((MenuCursorBase *)&cursor)->isGripping()) {
        if (testFlags(0x40)) {
            clearFlags(0x40);
            Shared_Inventory_PlayPickUpSe();
        }
        getHandPos();
    }
}

void MailboxMenu::mainAct15() {
    if (((CursorMotion *)&flyMotion)->update()) {
        releaseHeldTo(heldSlot);
        resumeInput();
        Inventory_PlayPutDownSe();
    } else {
        getFlyPos();
    }
}

void MailboxMenu::mainAct16() {
    if (((PopupChoiceMenuBody *)&popup)->isOpen()) {
        if (MenuCtrl_IsButtons()) {
            cursorToPopupTop();
            setMainState(0xb);
        } else {
            setMainState(6);
        }
    }
}

void MailboxMenu::mainAct17() {
    if (PopupChoice_TickDecideDelay(&popup)) {
        PopupChoice_Close(&popup, 0);
        ((TouchPromptBalloon *)&nameBalloon)->hide(1);
        if (((HandCursor *)&cursor)->getAnim()) {
            showCursorAtSlot();
        }
        setMainState(0x18);
    }
}

void MailboxMenu::mainAct18() {
    if (((PopupChoiceMenuBody *)&popup)->isClosed()) {
        onPopupChoice();
    }
}

void MailboxMenu::mainAct19() {
    if (((MenuErrorMessage *)&errorMessage)->update(1)) {
        setMainState(returnState);
        ((HandCursor *)&cursor)->enableObjWindow();
    }
}

void MailboxMenu::mainAct1A() {
    s32 a = ((MenuErrorMessage *)&errorMessage)->stepOpen();
    a &= stepSlideOut(-1);
    buttonsSlideY = getSlideOffsetY();
    if (a) {
        setMainState(0x1b);
        initSlideIn(0, 0);
        ((MenuBottomButtonsBody *)&bottomButtons)->setLayoutTossKeep();
        ((MenuBottomButtonsBody *)&bottomButtons)->enableObjWindow();
    }
}

void MailboxMenu::mainAct1B() {
    BOOL r4 = stepSlideIn(-1);
    buttonsSlideY = getSlideOffsetY();
    if (r4) {
        resumePromptInput();
    }
}

void MailboxMenu::mainAct1C() {
    if (MenuCtrl_IsForceCloseDue()) {
        pressPromptTab4();
    }
    if (checkSwitchToButtons(1)) {
        startPromptButtonInput();
    } else if (Unk_ov106_022966b8_Both()) {
        if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(3)) {
            pressPromptTab3();
        } else if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(4)) {
            pressPromptTab4();
        }
    }
}

void MailboxMenu::mainAct1D() {
    if (MenuCtrl_IsForceCloseDue()) {
        hideCursor();
        pressPromptTab4();
    } else if (checkSwitchToTouch()) {
        startPromptTouchInput();
    } else {
        u32 t = gPad[1];
        if (t & 1) {
            ((MenuCursor *)&cursor)->setPosePress();
            setMainState(0x1e);
        } else if (t & 2) {
            hideCursor();
            pressPromptTab4();
        } else if (t & 8) {
            hideCursor();
            pressPromptTab3();
        } else {
            u32 r4 = promptChoice;
            u32 r6 = takeRepeatedKeys();
            if (MenuKeys_HasLeft(r6)) {
                if (promptChoice != 0) {
                    promptChoice = ((volatile MailboxMenu *)this)->promptChoice - 1;
                }
            } else if (MenuKeys_HasRight(r6)) {
                if (promptChoice < 1) {
                    promptChoice = ((volatile MailboxMenu *)this)->promptChoice + 1;
                }
            }
            if (r4 != promptChoice) {
                if (promptChoice != 0) {
                    s32 a = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(4);
                    s32 b = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(4);
                    moveCursorToPoint(a, b);
                } else {
                    s32 a = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(3);
                    s32 b = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(3);
                    moveCursorToPoint(a, b);
                }
            }
        }
    }
}

void MailboxMenu::mainAct1E() {
    if (((HandCursor *)&cursor)->isAnimDone()) {
        setMainState(0x1f);
        if (promptChoice != 0) {
            ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(4);
            Snd_PlaySe(0x28);
        } else {
            ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(3);
            Snd_PlaySe(0x27);
        }
    }
}

void MailboxMenu::mainAct1F() {
    if (((MenuBottomButtonsBody *)&bottomButtons)->stepPress()) {
        if (((HandCursor *)&cursor)->getAnim()) {
            s32 r4 = ((MenuBottomButtonsBody *)&bottomButtons)->getPressOffset();
            s32 r6 = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(-1);
            s32 r2 = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(-1);
            ((MenuCursorBase *)&cursor)->warpTo(r4 + r6, r4 + r2);
        }
    } else {
        hideCursor();
        setMainState(0x20);
        initSlideOut(0, 0);
        ((MenuErrorMessage *)&errorMessage)->beginClose();
    }
}

void MailboxMenu::mainAct20() {
    BOOL r4 = ((MenuErrorMessage *)&errorMessage)->stepClose();
    r4 &= stepSlideOut(-1);
    buttonsSlideY = getSlideOffsetY();
    if (r4) {
        ((MenuBottomButtonsBody *)&bottomButtons)->disableObjWindow();
        if (promptChoice == 0) {
            initSlideIn(0, 0);
            ((MenuBottomButtons *)&bottomButtons)->setLayoutSingle05(0x88);
            setMainState(0x21);
        } else {
            ((MenuBottomButtons *)&bottomButtons)->hide();
            setTransitionState(4);
            setPhase(1);
        }
    }
}

void MailboxMenu::mainAct21() {
    BOOL r4 = stepSlideIn(-1);
    buttonsSlideY = getSlideOffsetY();
    if (r4) {
        resumeInput();
    }
}

void MailboxMenu::mainAct22() {
    if (((MenuLabelButton *)&letterCloseButton)->stepAnim()) {
        if (((HandCursor *)&cursor)->getAnim()) {
            s32 r4 = ((MenuLabelButton *)&letterCloseButton)->getAnchorX(1);
            s32 r2 = ((MenuLabelButton *)&letterCloseButton)->getAnchorY(1);
            ((MenuCursorBase *)&cursor)->warpTo(r4, r2);
        }
    } else {
        hideCursor();
        setTransitionState(9);
        setPhase(1);
    }
}

void MailboxMenu::mainAct23() {
    if (((MenuBottomButtonsBody *)&bottomButtons)->stepPress()) {
        if (((HandCursor *)&cursor)->getAnim()) {
            s32 r4 = ((MenuBottomButtonsBody *)&bottomButtons)->getPressOffset();
            s32 r6 = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(-1);
            s32 r2 = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(-1);
            ((MenuCursorBase *)&cursor)->warpTo(r4 + r6, r4 + r2);
        }
    } else {
        hideCursor();
        transitionState = 4;
        clearFlags(0x100);
        setPhase(1);
    }
}

void MailboxMenu::mainAct24() {
    u32 r5 = findFirstMailboxLetter();
    if (r5 == 0x20) {
        cursorSlot = 0x1f;
        resumeInput();
    } else {
        u32 r2 = findFreePocketSlot();
        if (r2 == 0x20) {
            showMessage(6);
        } else {
            pickUpAndFlyTo(r5, r2);
            setMainState(0x25);
        }
    }
}

void MailboxMenu::mainAct25() {
    if (((CursorMotion *)&flyMotion)->update()) {
        releaseHeldTo(heldSlot);
        setMainState(0x24);
        Inventory_PlayPutDownSe();
    } else {
        getFlyPos();
    }
}

void MailboxMenu::mainAct26() {
    if (Shared_LetterGrid_UpdatePopAnim(&letterGrid)) {
        handKind = 0;
        resumeInput();
    }
}

void MailboxMenu::startTouchInput() {
    hideCursor();
    clearFocusSlot();
    setMainState(0);
}

void MailboxMenu::startButtonInput() {
    balloonSlot = 0x20;
    showCursor();
    restartKeyRepeat();
    updateBalloonForCursor();
    setMainState(7);
    setFocusSlot(cursorSlot);
}

void MailboxMenu::resumeInput() {
    if (MenuCtrl_IsTouch()) {
        startTouchInput();
    } else {
        startButtonInput();
    }
}

void MailboxMenu::startPromptTouchInput() {
    hideCursor();
    setMainState(0x1c);
}

void MailboxMenu::startPromptButtonInput() {
    restartKeyRepeat();
    promptChoice = 1;
    ((MenuCursor *)&cursor)->setAnimIfChanged(1);
    cursor.update();
    s32 t = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(4);
    s32 u = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(4);
    ((MenuCursorBase *)&cursor)->warpTo(t, u);
    setMainState(0x1d);
}

void MailboxMenu::resumePromptInput() {
    if (MenuCtrl_IsTouch()) {
        startPromptTouchInput();
    } else {
        startPromptButtonInput();
    }
}

void MailboxMenu::beginTouchOnSlot(u32 a) {
    touchedSlot = a;
    setMainState(1);
    u32 r6 = gTouchCurX;
    u32 r7 = gTouchCurY;
    dragOffsetX = getSlotX(touchedSlot) - r6;
    dragOffsetY = getSlotY(touchedSlot) - r7;
    balloonSlot = a;
    ((TouchPromptBalloon *)&nameBalloon)->queueOpen();
    ((TouchPromptBalloon *)&nameBalloon)->commitOpen();
    touchHoldDelay = 2;
    if (isSlotDisabled(a)) {
        clearFlags(4);
    } else {
        setFlags(4);
        Inventory_PlayTouchSe();
    }
}

void MailboxMenu::beginDragFromSlot(u32 a) {
    heldSlot = a;
    ((TouchPromptBalloon *)&nameBalloon)->hide(1);
    pickUpFrom(a);
    if (handKind == 1) {
        setMainState(4);
    }
    getDragPos();
    Shared_Inventory_PlayPickUpSe();
}

void MailboxMenu::pickUpAtSlot(u32 a) {
    heldSlot = a;
    ((TouchPromptBalloon *)&nameBalloon)->hide(1);
    pickUpFrom(a);
    if (handKind == 1) {
        returnState = 8;
    }
    getHandPos();
    Shared_Inventory_PlayPickUpSe();
}

void MailboxMenu::flyHeldTo(u32 a, u32 b) {
    heldSlot = a;
    ((CursorMotion *)&flyMotion)->setPos(handX, handY);
    s32 x = getSlotX(a);
    s32 y = getSlotY(a);
    ((CursorMotion *)&flyMotion)->startLinear(x, y, b);
    ((CursorMotion *)&flyMotion)->update();
    getFlyPos();
    setMainState(0x15);
}

void MailboxMenu::flyHeldToOtherList(u32 a, s32 c) {
    u32 r = 0x20;
    if (c >= 0xc0) {
        if (isMailboxSlot(a)) {
            r = findFreePocketSlot();
        }
    }
    if (r != 0x20) {
        a = r;
    }
    flyHeldTo(a, 4);
}

void MailboxMenu::pickUpAndFlyTo(u32 a, u32 b) {
    pickUpFrom(a);
    handX = getSlotX(a);
    handY = getSlotY(a);
    flyHeldTo(b, 4);
}

u32 MailboxMenu::findFreePocketSlot() {
    s32 r = Inventory_FindEmptyLetter();
    if (r == -1) {
        return 0x20;
    }
    return (u8)(r + 0xb);
}

u32 MailboxMenu::findFirstMailboxLetter() {
    Letter *p = mailboxLetters;
    s32 i;
    for (i = 0; i < 10; p++, i++) {
        if (((LetterView *)p)->getState()) {
            return (u8)(i + 0x15);
        }
    }
    return 0x20;
}

void MailboxMenu::showMessage(u32 v) {
    volatile u8 buf[2];
    buf[0] = gU8None;
    buf[0] = v;
    ((MenuErrorMessage *)&errorMessage)->startTalk((u8 *)buf, 1);
    setMainState(0x1a);
    initSlideOut(0, 0);
}

void MailboxMenu::pressPromptTab3() {
    Snd_PlaySe(0x27);
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(3);
    setMainState(0x1f);
    promptChoice = 0;
}

void MailboxMenu::pressPromptTab4() {
    Snd_PlaySe(0x28);
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(4);
    setMainState(0x1f);
    promptChoice = 1;
}

void MailboxMenu::cancelBgTasks() {
    ((BgVramTask *)bgTasks)->cancel();
}

BOOL MailboxMenu::isLetterSlot(u32 v) {
    if (v >= 0xb && v <= 0x14) {
        return TRUE;
    }
    return FALSE;
}

BOOL MailboxMenu::isMailboxSlot(u32 v) {
    if (v >= 0x15 && v <= 0x1e) {
        return TRUE;
    }
    return FALSE;
}

BOOL MailboxMenu::isButtonSlot(u32 a) {
    if (a == 0x1f) return TRUE;
    return FALSE;
}

u8 MailboxMenu::toLetterGridIndex(u32 a) {
    if (a >= 0xb && a <= 0x14) return a - 0xb;
    if (a >= 0x15 && a <= 0x1e) return a + 0xe;
    return 0;
}

u8 MailboxMenu::fromLetterGridIndex(u32 a) {
    if (a <= 9) return a + 0xb;
    if (a >= 0x23 && a <= 0x2c) return a - 0xe;
    return 0x20;
}

u32 MailboxMenu::getSlotAt(u32 a, s32 b, s32 c) {
    s32 r4 = ((LetterGrid *)(&letterGrid))->findPocketLetterAt(a, b);
    if (r4 == 0x37) {
        r4 = ((LetterGrid *)&letterGrid)->findLetterAt23(a, b);
    }
    if (r4 != 0x37) {
        if (c != 0 && LetterGrid_IsSlotEmpty(&letterGrid, r4)) return 0x20;
        return fromLetterGridIndex(r4);
    }
    return 0x20;
}

BOOL MailboxMenu::dropHeldOnSlot(u32 a) {
    if (isSlotEmpty(a) == 0) {
        Letter_Copy((LetterView *)&swapLetter, (LetterView *)getSlotLetter(a));
        putLetterInSlot(heldSlot, &swapLetter);
    }
    releaseHeldTo(a);
    return TRUE;
}

void MailboxMenu::putLetterInSlot(u32 a, Letter *p) {
    if (isLetterSlot(a) || isMailboxSlot(a)) {
        letterGrid.setLetter(toLetterGridIndex(a), p);
        if (isLetterSlot(a)) {
            registerLetterPaper((LetterView *)p);
        }
    }
}

Letter *MailboxMenu::getSlotLetter(u32 a) {
    if (isLetterSlot(a) || isMailboxSlot(a)) {
        return (Letter *)letterGrid.getLetter(toLetterGridIndex(a));
    }
    return 0;
}

void MailboxMenu::registerLetterPaper(LetterView *p) {
    if (p->getState() == 2 || p->getState() == 3) {
        PlayerData *r4 = PlayerData_GetCurrent();
        u16 v = 0xfff1;
        v = Item_MakePaper(Letter_GetPaper(p), 4);
        Catalog_SetItem(r4->getCatalog(), &v, 0, 1);
    }
}

s32 MailboxMenu::getSlotX(u32 a) {
    if (isLetterSlot(a) || isMailboxSlot(a)) {
        return LetterGrid_GetSlotX(&letterGrid, toLetterGridIndex(a));
    }
    if (a == 0x1f) return 0xbc;
    return 0;
}

s32 MailboxMenu::getSlotY(u32 a) {
    if (isLetterSlot(a) || isMailboxSlot(a)) {
        return Shared_LetterGrid_GetSlotY(&letterGrid, toLetterGridIndex(a)) - 0x10;
    }
    if (a == 0x1f) return 0xb6;
    return 0;
}

void MailboxMenu::disableAllPockets() {
    Shared_InventoryItemGrid_DisableSlotRange(&pocketGrid, 0, 0xe);
    ((LetterGrid *)&letterGrid)->highlightLetterKinds(4);
}

BOOL MailboxMenu::isSlotDisabled(u32 a) {
    if (isLetterSlot(a)) {
        return ((LetterGrid *)&letterGrid)->isHighlighted(toLetterGridIndex(a));
    }
    return FALSE;
}

BOOL MailboxMenu::isSlotEmpty(u32 a) {
    if (isLetterSlot(a) || isMailboxSlot(a)) {
        return LetterGrid_IsSlotEmpty(&letterGrid, toLetterGridIndex(a));
    }
    return TRUE;
}

void MailboxMenu::clearFocusSlot() {
    InventoryItemGrid_ClearCursorSlot(&pocketGrid);
    ((LetterGrid *)&letterGrid)->clearCursorSlot();
}

void MailboxMenu::setFocusSlot(u32 a) {
    if (isLetterSlot(a) || isMailboxSlot(a)) {
        ((LetterGrid *)&letterGrid)->setCursorSlot(toLetterGridIndex(a));
        InventoryItemGrid_ClearCursorSlot(&pocketGrid);
    } else {
        clearFocusSlot();
    }
}

void MailboxMenu::clearHoverSlot() {
    Shared_InventoryItemGrid_ClearMarks(&pocketGrid);
    ((LetterGrid *)&letterGrid)->clearMarks();
}

void MailboxMenu::setHoverSlot(u32 a) {
    if (isLetterSlot(a) || isMailboxSlot(a)) {
        ((LetterGrid *)&letterGrid)->markSlot(toLetterGridIndex(a));
    }
}

BOOL MailboxMenu::hasTouchMoved() {
    s32 d = gTouchPressX - gTouchCurX;
    if (d < 0) d = -d;
    if (d > 8) return TRUE;
    d = gTouchPressY - gTouchCurY;
    if (d < 0) d = -d;
    if (d > 8) return TRUE;
    return FALSE;
}

void MailboxMenu::placeBalloon() {
    s32 r6 = getSlotX(balloonSlot) - 0x6d;
    s32 r4 = getSlotY(balloonSlot) - 0x78;
    if (MenuCtrl_IsButtons()) {
        r4 -= 8;
    }
    ((LabelBalloon *)&nameBalloon)->setPos(r6, r4);
    if (isLetterSlot(balloonSlot) || isMailboxSlot(balloonSlot)) {
        ((LetterGrid *)&letterGrid)->showLetterName(&nameBalloon, toLetterGridIndex(balloonSlot));
    }
}

void MailboxMenu::updateBalloonForCursor() {
    if (isLetterSlot(cursorSlot) || isMailboxSlot(cursorSlot)) {
        if (isSlotEmpty(cursorSlot)) {
            ((TouchPromptBalloon *)&nameBalloon)->cancelQueuedOpen();
        } else {
            balloonSlot = cursorSlot;
            ((TouchPromptBalloon *)&nameBalloon)->queueOpen();
        }
    } else {
        ((TouchPromptBalloon *)&nameBalloon)->cancelQueuedOpen();
    }
}

void MailboxMenu::drawHeldItem() {
    if (testFlags(0x40) == 0) {
        if (handKind != 0) {
            if (handKind == 1) {
                ((LetterGrid *)&letterGrid)->drawHeldLetter(handX, handY, &heldLetter);
            }
        }
    }
}

void MailboxMenu::getDragPos() {
    handX = dragOffsetX + gTouchCurX;
    handY = dragOffsetY + gTouchCurY;
}

void MailboxMenu::getHandPos() {
    handX = ((MenuCursorBase *)&cursor)->getFrameScreenX() - 2;
    handY = ((MenuCursorBase *)&cursor)->getFrameScreenY() - 4;
}

void MailboxMenu::getFlyPos() {
    handX = ((CursorMotion *)&flyMotion)->getX();
    handY = ((CursorMotion *)&flyMotion)->getY();
}

void MailboxMenu::pickUpFrom(u32 a) {
    if (isLetterSlot(a) || isMailboxSlot(a)) {
        u32 r4 = toLetterGridIndex(a);
        handKind = 1;
        Letter_Copy((LetterView *)&heldLetter, (LetterView *)letterGrid.getLetter(r4));
        ((LetterGrid *)&letterGrid)->clearLetter(r4);
    }
}

void MailboxMenu::releaseHeldTo(u32 a) {
    if (handKind == 1) {
        putLetterInSlot(a, &heldLetter);
    }
    handKind = 0;
}

void MailboxMenu::exchangeHeldWith(u32 a) {
    if (handKind == 1) {
        Letter_Copy((LetterView *)&swapLetter, (LetterView *)&heldLetter);
        pickUpFrom(a);
        putLetterInSlot(a, &swapLetter);
    }
}

void MailboxMenu::showCursor() {
    s32 r4 = getCursorTargetX();
    ((MenuCursorBase *)&cursor)->warpTo(r4, getCursorTargetY());
    if (isButtonSlot(cursorSlot)) {
        ((MenuCursor *)&cursor)->setAnimIfChanged(7);
    } else {
        ((MenuCursor *)&cursor)->setAnimIfChanged(1);
    }
    refreshCursor();
}

s32 MailboxMenu::getCursorTargetX() {
    s32 r4 = getSlotX(cursorSlot);
    if (testFlags(0x20)) {
        r4 += 0x100;
    } else if (testFlags(0x10)) {
        r4 -= 0x100;
    }
    r4 += 8;
    return r4;
}

s32 MailboxMenu::getCursorTargetY() {
    return getSlotY(cursorSlot);
}

void MailboxMenu::hideCursor() {
    ((MenuCursor *)&cursor)->setAnimIfChanged(0);
    cursor.update();
}

void MailboxMenu::moveCursorToTarget() {
    s32 r5;
    if (testFlags(8)) {
        r5 = getCursorTargetX();
        ((MenuCursorBase *)&cursor)->warpTo(r5, getCursorTargetY());
        clearFlags(8);
    } else {
        r5 = getCursorTargetX();
        ((MenuCursorBase *)&cursor)->moveToEase(r5, getCursorTargetY(), 3, 1);
        returnState = mainState;
        setMainState(0xd);
    }
}

void MailboxMenu::moveCursorToPoint(s32 a, s32 b) {
    ((MenuCursorBase *)&cursor)->moveToEase(a, b, 3, 1);
    returnState = mainState;
    setMainState(0xd);
}

void MailboxMenu::moveCursorToPopupRow() {
    s32 r4 = ((PopupChoiceMenuBody *)&popup)->getRowX();
    ((MenuCursorBase *)&cursor)->moveToLinear(r4, ((PopupChoiceMenuBody *)&popup)->getRowY(popupRow), 2);
    returnState = mainState;
    setMainState(0xd);
}

void MailboxMenu::cancelPopup() {
    s32 r4;
    popupChoice = 4;
    popupRow = PopupChoice_DecideCancel(&popup, 1);
    r4 = ((PopupChoiceMenuBody *)&popup)->getRowX();
    ((MenuCursorBase *)&cursor)->warpTo(r4, ((PopupChoiceMenuBody *)&popup)->getRowY(popupRow));
    ((HandCursor *)&cursor)->setAnimAtEnd(8);
    setMainState(0x17);
}

void MailboxMenu::cursorToPopupTop() {
    s32 r4;
    if (testFlags(0x10000)) {
        popupRow = 1;
    } else {
        popupRow = 0;
    }
    r4 = ((PopupChoiceMenuBody *)&popup)->getRowX();
    ((MenuCursorBase *)&cursor)->warpTo(r4, ((PopupChoiceMenuBody *)&popup)->getRowY(popupRow));
    ((MenuCursor *)&cursor)->setAnimIfChanged(7);
}

void MailboxMenu::showCursorAtSlot() {
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    ((MenuCursorBase *)&cursor)->warpTo(a, b);
    ((MenuCursor *)&cursor)->setAnimIfChanged(1);
}

void MailboxMenu::refreshCursor() {
    ((MenuCursorBase *)&cursor)->setPoseIdle();
    cursor.update();
}

void MailboxMenu::pressCloseButton() {
    ((MenuCursor *)&cursor)->setPosePress();
    setMainState(0xe);
}

void MailboxMenu::releaseCursor() {
    ((MenuCursorBase *)&cursor)->setPoseRelease();
    setMainState(0xf);
}

void MailboxMenu::beginMoveFromPopup() {
    ((MenuCursor *)&cursor)->setAnimIfChanged(4);
    setMainState(0x10);
}

void MailboxMenu::beginPutDownAt(u32 v) {
    ((TouchPromptBalloon *)&nameBalloon)->hide(1);
    targetSlot = v;
    ((MenuCursor *)&cursor)->setAnimIfChanged(5);
    setMainState(0x12);
}

void MailboxMenu::beginSwapAt(u32 v) {
    ((TouchPromptBalloon *)&nameBalloon)->hide(1);
    returnState = mainState;
    targetSlot = v;
    ((MenuCursor *)&cursor)->setAnimIfChanged(6);
    setMainState(0x13);
}

void MailboxMenu::onPopupChoice() {
    switch (popupChoice) {
    case 0:
        beginMoveFromPopup();
        break;
    case 1:
        startReadLetter();
        break;
    case 2:
        startDiscardLetter();
        break;
    case 3:
        onChoiceDiscard();
        break;
    case 4:
    default:
        resumeInput();
        break;
    }
}

void MailboxMenu::openPopup(u32 x) {
    ((PopupChoiceMenuBody *)&popup)->setRowsFromIds(&choiceList, testFlags(0x10000));
    s32 a = getSlotX(selectedSlot);
    s32 b = getSlotY(selectedSlot);
    if (x != 0) {
        ((PopupChoiceMenu *)(&popup))->placeAboveBalloon((LabelBalloon *)(&nameBalloon));
    } else {
        ((PopupChoiceMenu *)&popup)->placeNearPoint(a, b);
    }
    PopupChoice_Open(&popup, 0);
    setMainState(0x16);
}

void MailboxMenu::cancelPopupForButtons() {
    popupChoice = 4;
    showCursorAtSlot();
    PopupChoice_Close(&popup, 0);
    setMainState(0x18);
}

void MailboxMenu::selectLetter(u32 idx, u32 x) {
    clearFlags(0x10000);
    selectedSlot = idx;
    ChoiceIdList_Clear((u8 *)&choiceList, 4);
    void *r7 = getSlotLetter(idx);
    if (MenuCtrl_IsButtons()) {
        ChoiceIdList_Add((u8 *)&choiceList, 0, 0);
    }
    s32 r5 = ((LetterView *)r7)->getState();
    if (r5 != 0) {
        if (r5 == 7) {
            ChoiceIdList_Add((u8 *)&choiceList, 0x17, 1);
        } else {
            ChoiceIdList_Add((u8 *)&choiceList, 0x14, 1);
        }
    }
    if (((LetterView *)r7)->getPresent() == 0xfff1) {
        if (r5 == 3 || r5 == 6 || r5 == 1 || r5 == 4) {
            ChoiceIdList_Add((u8 *)&choiceList, 0x15, 3);
        }
    }
    ChoiceIdList_Add((u8 *)&choiceList, 2, 4);
    hideCursor();
    if (x == 0) {
        ((TouchPromptBalloon *)&nameBalloon)->hide(1);
    }
    openPopup(x);
}

void MailboxMenu::openDiscardConfirm() {
    setFlags(0x10000);
    ChoiceIdList_Clear((u8 *)&choiceList, 4);
    ChoiceIdList_Add((u8 *)&choiceList, 0x1a, 4);
    ChoiceIdList_Add((u8 *)&choiceList, 0x15, 2);
    ChoiceIdList_Add((u8 *)&choiceList, 0x19, 4);
    openPopup(0);
}

void MailboxMenu::moveCursorInPocketLetters(u32 pad, u32 x) {
    s32 r6 = cursorSlot - 0xb;
    s32 r4 = r6 >> 1;
    if (MenuKeys_HasLeft(pad)) {
        if ((r6 & 1) > 0) {
            cursorSlot = cursorSlot - 1;
        } else {
            if (x != 1 || !isLetterSlot(heldSlot)) {
                cursorSlot = r4 * 2 + 0x16;
                return;
            }
        }
    } else if (MenuKeys_HasRight(pad)) {
        if ((r6 & 1) < 1) {
            cursorSlot = cursorSlot + 1;
        } else {
            if (x != 1 || !isLetterSlot(heldSlot)) {
                cursorSlot = r4 * 2 + 0x15;
                setFlags(0x20);
                return;
            }
        }
    }
    if (isLetterSlot(cursorSlot)) {
        if (!testFlags(0x30)) {
            if (MenuKeys_HasUp(pad)) {
                if (r4 > 0) {
                    cursorSlot = cursorSlot - 2;
                }
            } else if (MenuKeys_HasDown(pad)) {
                if (r4 < 4) {
                    cursorSlot = cursorSlot + 2;
                } else if (x == 0) {
                    cursorSlot = 0x1f;
                    ((MenuCursor *)&cursor)->switchToAnim07();
                }
            }
        }
    }
}

void MailboxMenu::moveCursorInMailbox(u32 pad, u32 x) {
    s32 r6 = cursorSlot - 0x15;
    s32 r4 = 0;
    for (; r6 >= 2; r4++, r6 -= 2) {
    }
    if (MenuKeys_HasLeft(pad)) {
        if (r6 > 0) {
            cursorSlot = cursorSlot - 1;
        } else {
            cursorSlot = r4 * 2 + 0xc;
            setFlags(0x10);
            return;
        }
    } else if (MenuKeys_HasRight(pad)) {
        if (r6 < 1) {
            cursorSlot = cursorSlot + 1;
        } else {
            cursorSlot = r4 * 2 + 0xb;
            return;
        }
    }
    if (isMailboxSlot(cursorSlot)) {
        if (!testFlags(0x30)) {
            if (MenuKeys_HasUp(pad)) {
                if (r4 > 0) {
                    cursorSlot = cursorSlot - 2;
                }
            } else if (MenuKeys_HasDown(pad)) {
                if (r4 < 4) {
                    cursorSlot = cursorSlot + 2;
                } else if (x == 0) {
                    cursorSlot = 0x1f;
                    ((MenuCursor *)&cursor)->switchToAnim07();
                }
            }
        }
    }
}

void MailboxMenu::moveCursorOnButton(u32 pad) {
    if (MenuKeys_HasUp(pad)) {
        ((MenuCursor *)&cursor)->switchToAnim01();
        cursorSlot = 0x13;
    }
}

BOOL MailboxMenu::moveCursorByPad(u32 pad, u32 x) {
    u8 old = cursorSlot;
    clearFlags(0x30);
    if (pad == 0) {
        return FALSE;
    }
    if (isLetterSlot(cursorSlot)) {
        moveCursorInPocketLetters(pad, x);
    } else if (isMailboxSlot(cursorSlot)) {
        moveCursorInMailbox(pad, x);
    } else if (isButtonSlot(cursorSlot)) {
        moveCursorOnButton(pad);
    }
    if (old != cursorSlot) {
        return TRUE;
    }
    return FALSE;
}

void MailboxMenu::startReadLetter() {
    setTransitionState(4);
    setPhase(1);
    setFlags(0x100);
}

void MailboxMenu::closeLetterView() {
    setMainState(0x22);
    ((LabelButton *)&letterCloseButton)->setState(2);
    Snd_PlaySe(0x29);
}

void MailboxMenu::forceCloseFromLetterView() {
    closeLetterView();
    setFlags(0x8000);
    hideCursor();
    setTransitionState(9);
    setPhase(1);
    ((MenuLauncher *)ProcBase_GetParent(this))->setNextRequest(0x44, 1);
}

void MailboxMenu::startDiscardLetter() {
    u8 idx = selectedSlot;
    pickUpFrom(idx);
    handX = getSlotX(idx);
    handY = getSlotY(idx);
    if (MenuCtrl_IsButtons()) {
        handX = handX - 2;
        handY = handY - 2;
    }
    setMainState(0x26);
    LetterGrid_StartPopAnim(&letterGrid);
}

void MailboxMenu::onChoiceDiscard() { openDiscardConfirm(); }

void MailboxMenu::pressCloseTab() {
    Snd_PlaySe(0x27);
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(9);
    setMainState(0x23);
}

BOOL MailboxMenu::testFlags(u32 mask) {
    if (stateFlags & mask) {
        return TRUE;
    }
    return FALSE;
}

void MailboxMenu::setFlags(u32 mask) { stateFlags = stateFlags | mask; }

void MailboxMenu::clearFlags(u32 mask) { stateFlags = stateFlags & ~mask; }

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov106_02294c40) {
    HOST_OVERLAY_VAR(sMailboxMenuProfile),
    HOST_OVERLAY_VARS_END
};
