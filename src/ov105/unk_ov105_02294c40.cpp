#include "types.h"
#include "host_shared_calls.h"
#include "Unk_020d8c7c.h"
#include "net/CommManager.h"
#include "player/PlayerData.h"
#include "ui/CursorMotion.h"
#include "talk/TalkWindowState.h"
#include "item/Letter.h"
#include "player/PlayerId.h"
#include "menu/InventoryItemGrid.h"
#include "menu/LetterGrid.h"
#include "menu/InventoryBg.h"
#include "ui/LetterRenderer.h"
#include "menu/MenuProc.h"
#include "item/LetterView.h"
#include "item/LetterStorage.h"
#include "ui/UiWidget.h"
#include "menu/MenuLauncher.h"
#include "ui/LabelBalloon.h"
#include "gfx/BgVramTask.h"
#include "ui/TouchPromptBalloon.h"
#include "player/PlayerData.h"
#include "talk/MsgString.h"
#include "talk/MsgString9B.h"
#include "ui/LabelButton.h"
#include "ui/HandCursor.h"
#include "menu/MenuCursor.h"
#include "menu/MenuLabelButton.h"
#include "menu/PopupChoiceMenu.h"
#include "menu/MenuBottomButtons.h"
#include "menu/MenuErrorMessage.h"
#include "sys/ProcProfile.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/ov002/unk_ov002_022013ac.h"
#include "proto/main/unk_02087e0c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_02065e88.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0206f4f0.h"
#include "proto/main/unk_02085940.h"
#include "proto/main/unk_02095cdc.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov002/unk_ov002_02202fac.h"
#include "proto/main/unk_02087e70.h"
#include "proto/ov094/unk_ov094_02292360.h"
#include "proto/ov094/unk_ov094_02292da8.h"
#include "proto/ov094/unk_ov094_02293b90.h"
#include "proto/ov105/unk_ov105_02294c40.h"

class LetterStorageMenu;
class MenuLauncher;
class Letter;
typedef LetterStorageMenu S;


extern "C" {
void MI_CpuCopy8(void *src, void *dst, u32 n);


BOOL PopupChoice_MoveCursor(void *p, s32 a, void *q, u32 b);
BOOL PopupChoice_TickDecideDelay(void *p);
u8 PopupChoice_DecideCancel(void *p, s32 a);
void PopupChoice_DecideRow(void *p, s32 a, s32 b);
void PopupChoice_ForceClose(void *p);
void PopupChoice_Update(void *p);
void PopupChoice_Close(void *p, s32 a);
void PopupChoice_Open(void *p, s32 a);

extern u16 gPad[];
extern u8 gSavePlayers[];
}




extern "C" CommManager *gCommManager;



struct LetterView;










struct PopupChoiceIdList;








extern "C" {
}

struct Unk_ov105_Ent {
    u32 a;
    u32 b;
};
extern "C" const u16 data_ov105_02298314[3];
extern "C" Unk_ov105_Ent data_ov105_02298544[9];
extern "C" char data_ov105_022984e4[];
extern "C" char data_ov105_02298504[];
extern "C" char data_ov105_02298524[];
extern "C" const char *sLetterStoragePageChars[3];


typedef void (LetterStorageMenu::*Unk_ov105_02298594_Fn)();

class LetterStorageMenu : public MenuProc {
public:
    LetterStorageMenu()
        : heldLetter(), swapLetter(), bgTasks(), pocketGrid(), letterGrid(), inventoryBg(), nameBalloon(), flyMotion(), cursor(), popup(),
          errorMessage(), letterView(), letterCloseButton(), storageLetters(), bottomButtons() {}
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onDraw();
    virtual BOOL execTransition();
    virtual BOOL execMain();
    virtual BOOL execPhase3();
    virtual BOOL execPhase4();
    virtual BOOL execClosed();

    void clearFlags(u32);
    void setFlags(u32);
    BOOL testFlags(u32);
    BOOL switchPageByShoulder();
    void endDimBackground();
    void beginDimBackground();
    void startPageSwitch();
    BOOL hitPageTab(s32, s32);
    void startPageSlideOut();
    void loadPage();
    void drawPageTabs();
    void pressTab4();
    void pressCloseTab();
    void pressTab9();
    void func_ov105_0229514c();
    void onChoiceDiscard();
    void startDiscardLetter();
    void closeLetterView();
    void startReadLetter();
    BOOL moveCursorByPad(u32, u32);
    void moveCursorOnPageTabs(u32);
    void moveCursorOnButton(u32);
    void moveCursorInStorage(u32, u32);
    void moveCursorInPocketLetters(u32, u32);
    void openDiscardConfirm();
    void selectLetter(u32 a, u32 b);
    void cancelPopupForButtons();
    void openPopup(u32 b);
    void onPopupChoice();
    void beginSwapAt(u32 b);
    void beginPutDownAt(u32 b);
    void beginMoveFromPopup();
    void releaseCursor();
    void pressCloseButton();
    void refreshCursor();
    void showCursorAtSlot();
    void cursorToPopupTop();
    void cancelPopup();
    void moveCursorToPopupRow();
    void moveCursorToPoint(s32 a, s32 b);
    void moveCursorToTarget();
    void hideCursor();
    s32 getCursorTargetY();
    s32 getCursorTargetX();
    void showCursor();
    void exchangeHeldWith(u32 b);
    void releaseHeldTo(u32 b);
    void pickUpFrom(u32 b);
    void getFlyPos();
    void getHandPos();
    void getDragPos();
    void drawHeldItem();
    void updateBalloonForCursor();
    void placeBalloon();
    BOOL hasTouchMoved();
    void setHoverSlot(u32 b);
    void clearHoverSlot();
    void setFocusSlot(u32 b);
    void clearFocusSlot();
    BOOL isSlotEmpty(u32);
    BOOL isSlotDisabled(u32);
    void disableAllPockets();
    s32 getSlotY(u32);
    s32 getSlotX(u32);
    void *getSlotLetter(u32);
    void putLetterInSlot(u32, void *);
    BOOL dropHeldOnSlot(u32);
    s32 getSlotAt(u32, u32, u32);
    u32 fromLetterGridIndex(u32);
    u32 toLetterGridIndex(u32);
    BOOL isPageTabSlot(u32);
    BOOL isButtonSlot(u32);
    BOOL isStorageSlot(u32);
    BOOL isLetterSlot(u32);
    void cancelBgTasks();
    u32 findFreeStorageSlot();
    u32 findFreePocketSlot();
    void pickUpAndFlyTo(u32, u32, u32);
    void flyHeldToOtherList(u32, s32);
    void flyHeldTo(u32, u32);
    void pickUpAtSlot(u8);
    void beginDragFromSlot(u8);
    void beginTouchOnSlot(u32);
    void resumePromptInput();
    void startPromptButtonInput();
    void startPromptTouchInput();
    void resumeInput();
    void startButtonInput();
    void startTouchInput();
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
    void transitionAct15();
    void transitionAct14();
    void transitionAct13();
    void transitionAct12();
    void transitionAct11();
    void transitionAct10();
    void transitionAct0F();
    void transitionAct0E();
    void scrollBoxBg();
    void scrollMainBg();
    void scrollLetterViewBg();
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

    /* 0x91 */ u8 unk_91[3];
    /* 0x94 */ u32 stateFlags;
    /* 0x98 */ s32 slideY;
    /* 0x9c */ s32 buttonsSlideY;
    /* 0xa0 */ u32 boxSlideX;
    /* 0xa4 */ s32 dragOffsetX;
    /* 0xa8 */ s32 dragOffsetY;
    /* 0xac */ s32 handX;
    /* 0xb0 */ s32 handY;
    /* 0xb4 */ Letter heldLetter;
    /* 0x1a8 */ Letter swapLetter;
    /* 0x29c */ u8 handKind;
    /* 0x29d */ u8 touchedSlot;
    /* 0x29e */ u8 balloonSlot;
    /* 0x29f */ u8 heldSlot;
    /* 0x2a0 */ u8 heldOriginPage;
    /* 0x2a1 */ u8 heldOriginSlot;
    /* 0x2a2 */ u8 cursorSlot;
    /* 0x2a3 */ u8 selectedSlot;
    /* 0x2a4 */ u8 targetSlot;
    /* 0x2a5 */ u8 returnState;
    /* 0x2a6 */ u8 popupChoice;
    /* 0x2a7 */ u8 popupRow;
    /* 0x2a8 */ u8 currentPage;
    /* 0x2a9 */ u8 pageLoadDelay;
    /* 0x2aa */ u8 promptChoice;
    /* 0x2ab */ u8 touchHoldDelay;
    /* 0x2ac */ BgVramTaskPair bgTasks[1];
    /* 0x2e4 */ InventoryItemGrid pocketGrid;
    /* 0xd44 */ LetterGrid letterGrid;
    /* 0xd6c */ InventoryBg inventoryBg;
    /* 0x234c */ TouchPromptBalloon nameBalloon;
    /* 0x240c */ CursorMotion flyMotion;
    /* 0x2424 */ MenuCursorBuf0 cursor;
    /* 0x2488 */ PopupChoiceMenu popup;
    /* 0x277c */ PopupChoiceIdList choiceList;
    /* 0x2787 */ u8 pad_2787[1];
    /* 0x2788 */ MenuErrorMessage errorMessage;
    /* 0x2890 */ LetterRenderer letterView;
    /* 0x2aa0 */ MenuLabelButton letterCloseButton;
    /* 0x2b10 */ Letter storageLetters[0x4b];
    /* 0x728c */ MenuBottomButtons bottomButtons;
};


extern "C" {
}


static inline BOOL Unk_ov105_0229677c_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) return TRUE;
    return FALSE;
}

static inline BOOL Unk_ov105_022973c4_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) return TRUE;
    return FALSE;
}

extern "C" LetterStorageMenu *LetterStorageMenu_Create() { return new LetterStorageMenu(); }

BOOL LetterStorageMenu::onCreate() {
    initParts();
    setTransitionState(0);
    setPhase(0);
    return TRUE;
}

BOOL LetterStorageMenu::onDelete() {
    ((MenuLauncher *)ProcBase_GetParent(this))->onChildClosed();
    releaseResources();
    return TRUE;
}

BOOL LetterStorageMenu::onDraw() {
    if (!testFlags(1)) {
        return TRUE;
    }
    nameBalloon.draw();
    if (MenuCtrl_IsButtons()) {
        cursor.drawWrapped();
    }
    drawHeldItem();
    if (testFlags(2)) {
        bottomButtons.drawAt(buttonsSlideY);
        if (!testFlags(0x200)) {
            InventoryItemGrid_DrawPockets(&pocketGrid, 0, slideY - 0x10);
        } else {
            u32 t = boxSlideX;
            if (t != 0) {
                InventoryItemGrid_DrawPocketsClipped(&pocketGrid, 0, slideY - 0x10, t + 0xc0);
            }
        }
        letterGrid.drawPocketLetters(0, slideY - 0x10);
        Shared_InventoryBg_DrawSprite(&inventoryBg, slideY - 0x10);
    }
    if (testFlags(0x200)) {
        letterGrid.drawLetters0A(boxSlideX, -0x10);
        drawPageTabs();
    }
    if (testFlags(0x80)) {
        letterCloseButton.setPos(0, getSlideOffsetY());
        letterCloseButton.draw();
    }
    return TRUE;
}
extern "C" const u16 data_ov105_02298314[3];
extern "C" Unk_ov105_Ent data_ov105_02298544[9];
extern "C" const char *sLetterStoragePageChars[3];
extern "C" ProcProfile sLetterStorageMenuProfile;
extern "C" ProcProfile sLetterStorageMenuProfile;
extern "C" char data_ov105_02298524[];
extern "C" const char *sLetterStoragePageChars[3];
extern "C" char data_ov105_02298504[];
extern "C" const u16 data_ov105_02298314[3];
extern "C" char data_ov105_022984e4[];
extern "C" Unk_ov105_Ent data_ov105_02298544[9];

extern "C" ProcProfile sLetterStorageMenuProfile = {(void *(*)())LetterStorageMenu_Create, 0x98, 0x9c};

extern "C" char data_ov105_02298524[] = "menu/inventory/b_itm_post2.bch";

BOOL LetterStorageMenu::execTransition() {
    static Unk_ov105_02298594_Fn tbl[22] = {
        &LetterStorageMenu::transitionAct00,
        &LetterStorageMenu::transitionAct01,
        &LetterStorageMenu::transitionAct02,
        &LetterStorageMenu::transitionAct03,
        &LetterStorageMenu::transitionAct04,
        &LetterStorageMenu::transitionAct05,
        &LetterStorageMenu::transitionAct06,
        &LetterStorageMenu::transitionAct07,
        &LetterStorageMenu::transitionAct08,
        &LetterStorageMenu::transitionAct09,
        &LetterStorageMenu::transitionAct0A,
        &LetterStorageMenu::transitionAct0B,
        &LetterStorageMenu::transitionAct0C,
        &LetterStorageMenu::transitionAct0D,
        &LetterStorageMenu::transitionAct0E,
        &LetterStorageMenu::transitionAct0F,
        &LetterStorageMenu::transitionAct10,
        &LetterStorageMenu::transitionAct11,
        &LetterStorageMenu::transitionAct12,
        &LetterStorageMenu::transitionAct13,
        &LetterStorageMenu::transitionAct14,
        &LetterStorageMenu::transitionAct15
    };
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}

void LetterStorageMenu::runMainState() {
    static Unk_ov105_02298594_Fn tbl[32] = {
        &LetterStorageMenu::mainAct00,
        &LetterStorageMenu::mainAct01,
        &LetterStorageMenu::mainAct02,
        &LetterStorageMenu::mainAct03,
        &LetterStorageMenu::mainAct04,
        &LetterStorageMenu::mainAct05,
        &LetterStorageMenu::mainAct06,
        &LetterStorageMenu::mainAct07,
        &LetterStorageMenu::mainAct08,
        &LetterStorageMenu::mainAct09,
        &LetterStorageMenu::mainAct0A,
        &LetterStorageMenu::mainAct0B,
        &LetterStorageMenu::mainAct0C,
        &LetterStorageMenu::mainAct0D,
        &LetterStorageMenu::mainAct0E,
        &LetterStorageMenu::mainAct0F,
        &LetterStorageMenu::mainAct10,
        &LetterStorageMenu::mainAct11,
        &LetterStorageMenu::mainAct12,
        &LetterStorageMenu::mainAct13,
        &LetterStorageMenu::mainAct14,
        &LetterStorageMenu::mainAct15,
        &LetterStorageMenu::mainAct16,
        &LetterStorageMenu::mainAct17,
        &LetterStorageMenu::mainAct18,
        &LetterStorageMenu::mainAct19,
        &LetterStorageMenu::mainAct1A,
        &LetterStorageMenu::mainAct1B,
        &LetterStorageMenu::mainAct1C,
        &LetterStorageMenu::mainAct1D,
        &LetterStorageMenu::mainAct1E,
        &LetterStorageMenu::mainAct1F
    };
    (this->*tbl[mainState])();
}

BOOL LetterStorageMenu::execMain() {
    preInputUpdate();
    runMainState();
    postInputUpdate();
    return TRUE;
}

BOOL LetterStorageMenu::execPhase3() { return TRUE; }

BOOL LetterStorageMenu::execPhase4() { return TRUE; }

BOOL LetterStorageMenu::execClosed() {
    if (!testFlags(0x1000)) {
        MenuCtrl_SetResult(0);
    } else {
        MenuCtrl_SetResult(1);
        void *h = PlayerData_GetLetterStorage((void *)PlayerData_GetCurrent());
        if (h != 0) {
            s32 i;
            Letter *p = (Letter *)((LetterStorage *)h)->getPage(0);
            for (i = 0; i < 0x4b; i++) {
                Letter_Copy((LetterView *)p, (const LetterView *)&storageLetters[i]);
                p++;
            }
        }
    }
    ProcBase_RequestDelete(this);
    return TRUE;
}

void LetterStorageMenu::transitionAct00() {
    LetterStorageMenu_SetupBgLayers();
    loadInventoryBg();
    setTransitionState(1);
}

void LetterStorageMenu::transitionAct01() {
    loadObjGraphics();
    Shared_InventoryItemGrid_LoadPockets(&pocketGrid);
    Shared_LetterGrid_LoadPocketLetters(&letterGrid);
    disableAllPockets();
    beginSubSlideIn(8, 0, 0, 0x30);
    Gfx2d_ShowLayer(6);
    setTransitionState(2);
    setFlags(1);
    setFlags(2);
    scrollMainBg();
}

void LetterStorageMenu::transitionAct02() {
    BOOL b = stepSlideIn(0);
    scrollMainBg();
    if (b) {
        loadBoxBg();
        loadPage();
        setTransitionState(3);
    }
}

void LetterStorageMenu::transitionAct03() {
    if (stepSlideIn(0)) {
        setPhase(2);
        resumeInput();
        clearFlags(0x40);
        if (handKind != 0) {
            if (MenuCtrl_IsButtons()) {
                u32 v = cursorSlot;
                if (v < 0x3e || v > 0x40) {
                    cursor.setAnimAtEnd(4);
                }
                cursor.update();
                getHandPos();
                setMainState(8);
            }
        }
    }
    scrollBoxBg();
}

void LetterStorageMenu::transitionAct04() {
    endDimBackground();
    if (!testFlags(0x100)) {
        ((MenuLauncher *)ProcBase_GetParent(this))->setNextRequest(0x44, 1);
    }
    startPageSlideOut();
    setTransitionState(5);
}

void LetterStorageMenu::transitionAct05() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(4);
        clearFlags(0x200);
        beginSubSlideOut(8, 0, 0, 0x30);
        setTransitionState(6);
        transitionAct06();
        bottomButtons.hide();
    } else {
        scrollBoxBg();
        buttonsSlideY = -getSlideOffsetX();
    }
}

void LetterStorageMenu::transitionAct06() {
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
        applySlideOffset(6, 0, -0x10);
        slideY = getSlideOffsetY();
    }
}

void LetterStorageMenu::transitionAct07() {
    void *p = getSlotLetter(selectedSlot);
    switch (((LetterView *)p)->getState()) {
    case 2:
    case 5:
    case 7:
        setFlags(0x1000);
        break;
    }
    Letter_MarkRead((LetterView *)p);
    letterView.show((LetterView *)p, 3, 4, 1);
    beginSubSlideIn(3, 0, 0, 0x30);
    Gfx2d_ShowLayer(3);
    Gfx2d_ShowLayer(4);
    scrollLetterViewBg();
    setTransitionState(8);
    letterCloseButton.showDefault(0x88);
    setFlags(0x80);
}

void LetterStorageMenu::transitionAct08() {
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

void LetterStorageMenu::transitionAct09() {
    beginSubSlideOut(3, 0, 0, 0x30);
    scrollLetterViewBg();
    setTransitionState(0xa);
}

void LetterStorageMenu::transitionAct0A() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(3);
        Gfx2d_ResetLayer(4);
        clearFlags(0x80);
        transitionAct00();
    } else {
        scrollLetterViewBg();
    }
}

void LetterStorageMenu::transitionAct0B() {
    startPageSlideOut();
    setTransitionState(0xc);
    pageLoadDelay = 4;
    transitionAct0C();
}

void LetterStorageMenu::transitionAct0C() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(4);
        if (pageLoadDelay != 0) {
            pageLoadDelay--;
        } else {
            loadPage();
            setTransitionState(0xd);
        }
    } else {
        scrollBoxBg();
    }
}

void LetterStorageMenu::transitionAct0D() {
    transitionAct03();
}

void LetterStorageMenu::scrollLetterViewBg() {
    applySlideOffset(3, 0, 0);
    applySlideOffset(4, 0, 0);
}

void LetterStorageMenu::scrollMainBg() {
    applySlideOffset(6, 0, -16);
    slideY = getSlideOffsetY();
    buttonsSlideY = getSlideOffsetY();
}

void LetterStorageMenu::scrollBoxBg() {
    applySlideOffset(4, 0, -16);
    boxSlideX = getSlideOffsetX();
}

void LetterStorageMenu::transitionAct0E() {
    initSlideOut(0, 0);
    setTransitionState(0xf);
}

void LetterStorageMenu::transitionAct0F() {
    if (stepSlideOut(-1)) {
        transitionAct10();
    }
    buttonsSlideY = getSlideOffsetY();
}

void LetterStorageMenu::transitionAct10() {
    beginDimBackground();
    initSlideIn(0, 0);
    ((MenuBottomButtonsBody *)&bottomButtons)->setLayoutYesNo0B(0x22);
    setTransitionState(0x11);
}

void LetterStorageMenu::transitionAct11() {
    if (stepSlideIn(0)) {
        setPhase(2);
        resumePromptInput();
    }
    buttonsSlideY = getSlideOffsetY();
}

void LetterStorageMenu::transitionAct12() {
    endDimBackground();
    initSlideOut(0, 0);
    setTransitionState(0x13);
}

void LetterStorageMenu::transitionAct13() {
    if (stepSlideOut(-1)) {
        transitionAct14();
    }
    buttonsSlideY = getSlideOffsetY();
}

void LetterStorageMenu::transitionAct14() {
    initSlideIn(0, 0);
    bottomButtons.setLayoutSingle05(0x21);
    setTransitionState(0x15);
}

void LetterStorageMenu::transitionAct15() {
    if (stepSlideIn(0)) {
        setPhase(2);
        resumeInput();
    }
    buttonsSlideY = getSlideOffsetY();
}

void LetterStorageMenu::initParts() {
    s32 i;
    stateFlags = 0;
    InventoryItemGrid_Init(&pocketGrid, 2);
    letterGrid.init(1);
    Shared_InventoryBg_Init(&inventoryBg, 6);
    balloonSlot = 0x41;
    flyMotion.reset();
    handKind = 0;
    cursorSlot = 0x1a;
    popup.init(3, 0, 0);
    letterView.setLayer(3);
    i = 0;
    currentPage = 0;
    for (; i < 0x4b; i++) {
        Letter_Clear((LetterView *)&storageLetters[i]);
    }
    void *q = PlayerData_GetLetterStorage((void *)PlayerData_GetCurrent());
    if (q) {
        u8 *p = (u8 *)((LetterStorage *)q)->getPage(0);
        for (i = 0; i < 0x4b; i++) {
            Letter_Copy((LetterView *)&storageLetters[i], (const LetterView *)p);
            p += sizeof(Letter);
        }
    }
    func_ov105_0229514c();
    touchHoldDelay = 0;
}

void LetterStorageMenu::releaseResources() {
    cancelBgTasks();
    InventoryBg_Exit(&inventoryBg);
    Shared_InventoryItemGrid_Exit(&pocketGrid);
    PopupChoice_ForceClose(&popup);
    letterView.release();
    bottomButtons.freeTexts();
}

void LetterStorageMenu::preInputUpdate() {
    preStateUpdate();
    cursor.update();
}

void LetterStorageMenu::postInputUpdate() {
    postStateUpdate();
}

void LetterStorageMenu::preStateUpdate() {
    cancelBgTasks();
    Shared_InventoryBg_PreUpdate(&inventoryBg);
    InventoryItemGrid_PreUpdate(&pocketGrid);
    letterGrid.updateCursorLift();
    bottomButtons.freeTexts();
}

void LetterStorageMenu::postStateUpdate() {
    Shared_PopupChoice_Update(&popup);
    InventoryBg_Update(&inventoryBg);
    if (nameBalloon.updatePrompt()) {
        placeBalloon();
    }
}

extern "C" void LetterStorageMenu_SetupBgLayers() {
    Gfx2d_SetLayerPriority(6, 2);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
    Gfx2d_SetLayerPriority(4, 1);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
}

void LetterStorageMenu::loadInventoryBg() {
    InventoryBg_Load(&inventoryBg, 0);
}

void LetterStorageMenu::loadBoxBg() {
    void *h = gCurrentHeap;
    Gfx2d_LoadPaletteFile("menu/inventory/b_itm_post.bpl", h, 4, 4, 4, 4);
    Gfx2d_LoadScreenFile("menu/inventory/b_itm_bg_ltr0.bsc", h, 4);
    Gfx2d_LoadCharFile("menu/inventory/b_itm_post.bch", h, 4, 0x1e2, 0x1e2, 0x227);
}

void LetterStorageMenu::loadObjGraphics() {
    InventoryBg_LoadObjGraphics();
    MenuButtons_LoadTextColors();
    bottomButtons.setLayoutSingle05(0x21);
}

void LetterStorageMenu::mainAct00() {
    if (checkSwitchToButtons(1)) {
        startButtonInput();
    } else {
        if (Unk_ov105_022973c4_Both()) {
            s32 x = gTouchCurX;
            s32 y = gTouchCurY + 0x10;
            s32 r = getSlotAt(x, y, 1);
            if (r != 0x41) {
                beginTouchOnSlot(r);
            } else if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(9)) {
                pressTab9();
            } else if (hitPageTab(x, y)) {
                startPageSwitch();
            }
        }
    }
}

void LetterStorageMenu::mainAct01() {
    if (gTouchHeld == 0) {
        if (testFlags(4)) {
            setMainState(3);
            runMainState();
        } else {
            setMainState(0);
            nameBalloon.setAutoCloseTimer(0x3c);
        }
    } else {
        if (testFlags(4)) {
            if (hasTouchMoved()) {
                beginDragFromSlot(touchedSlot);
                return;
            }
            if (nameBalloon.isOpenOrOpening()) {
                if (touchHoldDelay != 0) {
                    touchHoldDelay--;
                } else {
                    selectLetter(touchedSlot, 1);
                    setMainState(2);
                }
                return;
            }
        }
        nameBalloon.commitOpen();
    }
}

void LetterStorageMenu::mainAct02() {
    if (gTouchHeld == 0) {
        setMainState(6);
    } else if (testFlags(4)) {
        if (hasTouchMoved()) {
            beginDragFromSlot(touchedSlot);
            PopupChoice_Close(&popup, 0);
            nameBalloon.hide(1);
        }
    }
}

void LetterStorageMenu::mainAct03() {
    if (nameBalloon.isOpenOrOpening()) {
        if (touchHoldDelay != 0) {
            touchHoldDelay--;
        } else {
            selectLetter(touchedSlot, 1);
            setMainState(2);
        }
    }
}

void LetterStorageMenu::mainAct04() {
    s32 a, b, r;
    getDragPos();
    clearHoverSlot();
    a = handX + 8;
    b = handY + 0x18;
    r = getSlotAt(a, b, 0);
    if (r != 0x41) {
        if (gTouchHeld == 0) {
            s32 q;
            if (isSlotDisabled(r) || (q = dropHeldOnSlot(r)) == 0) {
                flyHeldToOtherList(heldSlot, a);
            } else {
                Inventory_PlayPutDownSe();
                resumeInput();
            }
        } else {
            setHoverSlot(r);
        }
    } else if (gTouchHeld == 0) {
        flyHeldToOtherList(heldSlot, a);
    }
}

void LetterStorageMenu::mainAct05() {
    if (checkSwitchToButtons(1)) {
        setMainState(9);
    } else if (letterCloseButton.isTouched()) {
        closeLetterView();
    }
}

void LetterStorageMenu::mainAct06() {
    if (((PopupChoiceMenuBody *)&popup)->isOpen()) {
        if (checkSwitchToButtons(1)) {
            cancelPopupForButtons();
        } else if (Unk_ov105_022973c4_Both()) {
            s32 r = ((PopupChoiceMenuBody *)&popup)->hitTestRowOrLast(gTouchCurX, gTouchCurY);
            if (r >= 0) {
                if (testFlags(0x800) && r == 0) {
                } else {
                    s32 t;
                    popupChoice = choiceList.values[r];
                    t = 1;
                    if (popupChoice == 2) {
                        t = 0;
                        Snd_PlaySe(0x24);
                    }
                    PopupChoice_DecideRow(&popup, r, t);
                    setMainState(0x17);
                }
            }
        }
    }
}

void LetterStorageMenu::mainAct07() {
    S *s = this;
    if (s->checkSwitchToTouch()) {
        s->startTouchInput();
        s->nameBalloon.hide(1);
    } else {
        s32 r = s->takeRepeatedKeys();
        if (s->moveCursorByPad(r, 0)) {
            s->updateBalloonForCursor();
            s->moveCursorToTarget();
            s->nameBalloon.hide(0);
        } else {
            u32 k;
            if (s->isSlotDisabled(s->cursorSlot)) goto other;
            k = gPad[1];
            if (k & 1) {
                if (s->isLetterSlot(s->cursorSlot) || s->isStorageSlot(s->cursorSlot)) {
                    if (!s->isSlotEmpty(s->cursorSlot)) {
                        s->selectLetter(s->cursorSlot, 0);
                    }
                } else if (s->isButtonSlot(s->cursorSlot) || s->isPageTabSlot(s->cursorSlot)) {
                    s->pressCloseButton();
                }
            } else if (k & 0x800) {
                if (s->isLetterSlot(s->cursorSlot) || s->isStorageSlot(s->cursorSlot)) {
                    if (!s->isSlotEmpty(s->cursorSlot)) {
                        s32 t;
                        if (s->isLetterSlot(s->cursorSlot)) {
                            t = s->findFreeStorageSlot();
                        } else {
                            t = s->findFreePocketSlot();
                        }
                        if (t != 0x41) {
                            ((LetterStorageMenu *)(s))->pickUpAndFlyTo(s->cursorSlot, t, 0);
                            s->nameBalloon.hide(1);
                            s->setFlags(0x1000);
                        }
                    }
                }
            } else {
                goto other;
            }
            return;
other:
            k = gPad[1];
            if ((k & 8) || (k & 2)) {
                s->hideCursor();
                s->pressTab9();
                s->nameBalloon.hide(0);
            } else if (s->switchPageByShoulder() == 0) {
                s->nameBalloon.commitOpen();
            }
        }
    }
}

void LetterStorageMenu::mainAct08() {
    S *s = this;
    s32 r = s->takeRepeatedKeys();
    if (s->moveCursorByPad(r, 1)) {
        s->updateBalloonForCursor();
        s->moveCursorToTarget();
        s->nameBalloon.hide(0);
    } else {
        u32 k = gPad[1];
        if (k & 1) {
            if (s->isLetterSlot(s->cursorSlot) || s->isStorageSlot(s->cursorSlot)) {
                if (!s->isSlotDisabled(s->cursorSlot)) {
                    if (s->isSlotEmpty(s->cursorSlot)) {
                        s->beginPutDownAt(s->cursorSlot);
                    } else {
                        s->beginSwapAt(s->cursorSlot);
                    }
                }
            } else if (s->isPageTabSlot(s->cursorSlot)) {
                s->pressCloseButton();
            }
        } else if (k & 2) {
            if (s->isStorageSlot(s->heldSlot)) {
                u32 a = s->heldOriginPage;
                if (a != s->currentPage) {
                    s->flyHeldTo((u8)(a + 0x3e), 4);
                    return;
                }
            }
            if (s->cursor.getAnim() == 1) {
                s->flyHeldTo(s->heldSlot, 4);
            } else {
                s->beginPutDownAt(s->heldSlot);
            }
        } else {
            if (s->switchPageByShoulder() == 0) {
                s->getHandPos();
                s->nameBalloon.commitOpen();
            }
        }
    }
}

void LetterStorageMenu::mainAct09() {
    S *s = this;
    if (s->cursor.getAnim() == 0) {
        s32 a = s->letterCloseButton.getAnchorX(1);
        s32 b = s->letterCloseButton.getAnchorY(1);
        s->cursor.warpTo(a, b);
        s->cursor.setAnimIfChanged(1);
    }
    if (s->checkSwitchToTouch()) {
        s->hideCursor();
        s->setMainState(5);
    } else {
        u32 k = gPad[1];
        if ((k & 1) || (k & 2)) {
            s->cursor.setPosePress();
            s->setMainState(0xa);
        }
    }
}

void LetterStorageMenu::mainAct0A() {
    S *s = this;
    if (s->cursor.isAnimDone()) {
        s->closeLetterView();
    }
}

void LetterStorageMenu::mainAct0B() {
    S *s = this;
    if (s->checkSwitchToTouch()) {
        s->cancelPopupForButtons();
    } else {
        s32 r = s->takeRepeatedKeys();
        u8 t = (u8)s->testFlags(0x800);
        if (PopupChoice_MoveCursor(&s->popup, r, &s->popupRow, t)) {
            s->moveCursorToPopupRow();
        } else {
            u32 k = gPad[1];
            if (k & 1) {
                s->cursor.setPosePress();
                s->setMainState(0xc);
            } else if (k & 2) {
                s->cancelPopup();
            }
        }
    }
}

void LetterStorageMenu::mainAct0C() {
    S *s = this;
    if (s->cursor.isAnimDone()) {
        s32 r;
        s->popupChoice = s->choiceList.values[s->popupRow];
        r = 1;
        if (s->popupChoice == 2) {
            r = 0;
            Snd_PlaySe(0x24);
        }
        PopupChoice_DecideRow(&s->popup, s->popupRow, r);
        s->setMainState(0x17);
    }
}

void LetterStorageMenu::mainAct0D() {
    S *s = this;
    if (s->cursor.isMoving() == 0) {
        s->setMainState(s->returnState);
        if (s->returnState == 7) {
            s->setFocusSlot(s->cursorSlot);
        }
        s->runMainState();
    }
    s->getHandPos();
}

void LetterStorageMenu::mainAct0E() {
    S *s = this;
    if (s->cursor.isAnimDone()) {
        if (s->isButtonSlot(s->cursorSlot)) {
            s->pressTab9();
        } else if (s->isPageTabSlot(s->cursorSlot)) {
            s32 v = s->cursorSlot - 0x3e;
            if (v == s->currentPage) {
                s->releaseCursor();
            } else {
                s->currentPage = v;
                s->startPageSwitch();
            }
        } else {
            s->releaseCursor();
        }
    }
}

void LetterStorageMenu::mainAct0F() {
    S *s = this;
    if (s->cursor.isAnimDone()) {
        s->refreshCursor();
        if (s->handKind == 1) {
            s->setMainState(8);
        } else {
            s->setMainState(7);
        }
    }
}

void LetterStorageMenu::mainAct10() {
    S *s = this;
    if (s->cursor.isGripping()) {
        s->pickUpAtSlot(s->cursorSlot);
        s->setMainState(0x11);
    }
}

void LetterStorageMenu::mainAct11() {
    S *s = this;
    if (s->cursor.isAnimDone()) {
        s->setMainState(s->returnState);
    }
    s->getHandPos();
}

void LetterStorageMenu::mainAct12() {
    S *s = this;
    if (s->cursor.isGripping() == 0) {
        u32 a = s->targetSlot;
        if (s->cursorSlot == a) {
            ((LetterStorageMenu *)(s))->dropHeldOnSlot(a);
            s->updateBalloonForCursor();
            s->setMainState(7);
            Inventory_PlayPutDownSe();
        } else {
            s->flyHeldTo(a, 4);
        }
    } else {
        s->getHandPos();
    }
}

void LetterStorageMenu::mainAct13() {
    S *s = this;
    if (s->cursor.func_ov002_022028fc() == 0) {
        s->exchangeHeldWith(s->targetSlot);
        s->setFlags(0x40);
        s->setMainState(0x14);
        s->updateBalloonForCursor();
    } else {
        s->setMainState(7);
    }
}

void LetterStorageMenu::mainAct14() {
    S *s = this;
    if (s->cursor.isAnimDone()) {
        s->setMainState(s->returnState);
    }
    if (s->cursor.isGripping()) {
        if (s->testFlags(0x40)) {
            s->clearFlags(0x40);
            Shared_Inventory_PlayPickUpSe();
        }
        s->getHandPos();
    }
}

void LetterStorageMenu::mainAct15() {
    S *s = this;
    if (s->flyMotion.update()) {
        if (s->testFlags(0x2000)) {
            s->clearFlags(0x2000);
            s->getFlyPos();
        } else {
            s->releaseHeldTo(s->heldSlot);
            s->resumeInput();
            Inventory_PlayPutDownSe();
        }
    } else {
        s->getFlyPos();
    }
}

void LetterStorageMenu::mainAct16() {
    S *s = this;
    if (((PopupChoiceMenuBody *)&s->popup)->isOpen()) {
        if (MenuCtrl_IsButtons()) {
            s->cursorToPopupTop();
            s->setMainState(0xb);
        } else {
            s->setMainState(6);
        }
    }
}

void LetterStorageMenu::mainAct17() {
    S *s = this;
    if (PopupChoice_TickDecideDelay(&s->popup)) {
        PopupChoice_Close(&s->popup, 0);
        s->nameBalloon.hide(1);
        if (s->cursor.getAnim()) {
            s->showCursorAtSlot();
        }
        s->setMainState(0x18);
    }
}

void LetterStorageMenu::mainAct18() {
    S *s = this;
    if (((PopupChoiceMenuBody *)&s->popup)->isClosed()) {
        s->onPopupChoice();
    }
}

void LetterStorageMenu::mainAct19() {
    S *s = this;
    if (s->errorMessage.update(0)) {
        s->setMainState(s->returnState);
        s->cursor.enableObjWindow();
    }
}

void LetterStorageMenu::mainAct1A() {
    S *s = this;
    if (s->letterCloseButton.stepAnim()) {
        if (s->cursor.getAnim()) {
            s32 a = s->letterCloseButton.getAnchorX(1);
            s32 b = s->letterCloseButton.getAnchorY(1);
            s->cursor.warpTo(a, b);
        }
    } else {
        s->hideCursor();
        s->setTransitionState(9);
        s->setPhase(1);
    }
}

void LetterStorageMenu::mainAct1B() {
    S *s = this;
    if (((MenuBottomButtonsBody *)&s->bottomButtons)->stepPress()) {
        if (s->cursor.getAnim()) {
            s32 a = ((MenuBottomButtonsBody *)&s->bottomButtons)->getPressOffset();
            s32 b = ((MenuBottomButtonsBody *)&s->bottomButtons)->getTargetX(-1);
            s32 c = ((MenuBottomButtonsBody *)&s->bottomButtons)->getTargetY(-1);
            s->cursor.warpTo(a + b, a + c);
        }
    } else {
        s->hideCursor();
        s->setPhase(1);
    }
}

void LetterStorageMenu::mainAct1C() {
    S *s = this;
    if (Shared_LetterGrid_UpdatePopAnim(&s->letterGrid)) {
        s->setFlags(0x1000);
        s->handKind = 0;
        s->resumeInput();
    }
}

void LetterStorageMenu::mainAct1D() {
    if (checkSwitchToButtons(1)) {
        startPromptButtonInput();
    } else {
        if (Unk_ov105_0229677c_Both()) {
            if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(3)) {
                pressCloseTab();
            }
            if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(4)) {
                pressTab4();
            }
        }
    }
}

void LetterStorageMenu::mainAct1E() {
    if (checkSwitchToTouch()) {
        startPromptTouchInput();
    } else {
        u16 f = gPad[1];
        if ((f & 1) != 0) {
            cursor.setPosePress();
            setMainState(0x1f);
        } else if ((f & 2) != 0) {
            hideCursor();
            pressTab4();
        } else if ((f & 8) != 0) {
            hideCursor();
            pressCloseTab();
        } else {
            u32 old = promptChoice;
            s32 t = takeRepeatedKeys();
            if (MenuKeys_HasLeft(t)) {
                if (promptChoice != 0) {
                    promptChoice--;
                }
            } else if (MenuKeys_HasRight(t)) {
                if (promptChoice < 1) {
                    promptChoice++;
                }
            }
            if (old != promptChoice) {
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

void LetterStorageMenu::mainAct1F() {
    if (cursor.isAnimDone()) {
        if (promptChoice != 0) {
            pressTab4();
        } else {
            pressCloseTab();
        }
    }
}

void LetterStorageMenu::startTouchInput() {
    hideCursor();
    clearFocusSlot();
    setMainState(0);
}

void LetterStorageMenu::startButtonInput() {
    balloonSlot = 0x41;
    showCursor();
    restartKeyRepeat();
    updateBalloonForCursor();
    setMainState(7);
    setFocusSlot(cursorSlot);
}

void LetterStorageMenu::resumeInput() {
    if (MenuCtrl_IsTouch()) {
        startTouchInput();
    } else {
        startButtonInput();
    }
}

void LetterStorageMenu::startPromptTouchInput() {
    hideCursor();
    setMainState(0x1d);
}

void LetterStorageMenu::startPromptButtonInput() {
    restartKeyRepeat();
    promptChoice = 1;
    cursor.setAnimIfChanged(1);
    cursor.update();
    s32 a = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(4);
    s32 b = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(4);
    cursor.warpTo(a, b);
    setMainState(0x1e);
}

void LetterStorageMenu::resumePromptInput() {
    if (MenuCtrl_IsTouch()) {
        startPromptTouchInput();
    } else {
        startPromptButtonInput();
    }
}

void LetterStorageMenu::beginTouchOnSlot(u32 a) {
    touchedSlot = a;
    setMainState(1);
    u32 x = gTouchCurX;
    u32 y = gTouchCurY;
    dragOffsetX = getSlotX(touchedSlot) - x;
    dragOffsetY = getSlotY(touchedSlot) - y;
    balloonSlot = a;
    nameBalloon.queueOpen();
    nameBalloon.commitOpen();
    touchHoldDelay = 2;
    if (isSlotDisabled(a)) {
        clearFlags(4);
    } else {
        setFlags(4);
        Inventory_PlayTouchSe();
    }
}

void LetterStorageMenu::beginDragFromSlot(u8 a) {
    setFlags(0x1000);
    heldSlot = a;
    heldOriginSlot = a;
    heldOriginPage = currentPage;
    nameBalloon.hide(1);
    pickUpFrom(a);
    if (handKind == 1) {
        setMainState(4);
    }
    getDragPos();
    Shared_Inventory_PlayPickUpSe();
}

void LetterStorageMenu::pickUpAtSlot(u8 a) {
    heldSlot = a;
    heldOriginSlot = a;
    heldOriginPage = currentPage;
    nameBalloon.hide(1);
    pickUpFrom(a);
    if (handKind == 1) {
        returnState = 8;
    }
    getHandPos();
    Shared_Inventory_PlayPickUpSe();
}

void LetterStorageMenu::flyHeldTo(u32 a, u32 c) {
    heldSlot = a;
    flyMotion.setPos(handX, handY);
    s32 t = getSlotY(a);
    if (isPageTabSlot(a)) {
        t -= 8;
    }
    flyMotion.startLinear(getSlotX(a), t, c);
    flyMotion.update();
    getFlyPos();
    if (isPageTabSlot(a)) {
        setFlags(0x2000);
    } else {
        clearFlags(0x2000);
    }
    setMainState(0x15);
}

void LetterStorageMenu::flyHeldToOtherList(u32 a, s32 b) {
    u32 r = 0x41;
    if (b >= 0xc0) {
        if (isStorageSlot(a)) {
            r = findFreePocketSlot();
        }
    } else {
        if (isLetterSlot(a)) {
            r = findFreeStorageSlot();
        }
    }
    if (r != 0x41) {
        a = r;
    }
    flyHeldTo(a, 4);
}

void LetterStorageMenu::pickUpAndFlyTo(u32 a, u32 b, u32 c) {
    pickUpFrom(a);
    handX = getSlotX(a);
    handY = getSlotY(a);
    flyHeldTo(b, 4);
}

u32 LetterStorageMenu::findFreePocketSlot() {
    s32 r = Inventory_FindEmptyLetter();
    if (r == -1) {
        return 0x41;
    }
    return (u8)(r + 0x1a);
}

u32 LetterStorageMenu::findFreeStorageSlot() {
    Letter *p = &storageLetters[currentPage * 0x19];
    s32 i;
    for (i = 0; i < 0x19; p++, i++) {
        if (((LetterView *)p)->getState() == 0) {
            return (u8)(i + 0x24);
        }
    }
    return 0x41;
}

void LetterStorageMenu::cancelBgTasks() {
    ((BgVramTask *)bgTasks)->cancel();
}

BOOL LetterStorageMenu::isLetterSlot(u32 a) {
    if (a >= 0x1a && a <= 0x23) {
        return TRUE;
    }
    return FALSE;
}

BOOL LetterStorageMenu::isStorageSlot(u32 a) {
    if (a >= 0x24 && a <= 0x3c) {
        return TRUE;
    }
    return FALSE;
}

BOOL LetterStorageMenu::isButtonSlot(u32 a) {
    if (a == 0x3d) {
        return TRUE;
    }
    return FALSE;
}

BOOL LetterStorageMenu::isPageTabSlot(u32 a) {
    if ((u8)(a + 0xc2) <= 2) {
        return TRUE;
    }
    return FALSE;
}

u32 LetterStorageMenu::toLetterGridIndex(u32 a) {
    if (a >= 0x1a && a <= 0x23) {
        return (u8)(a - 0x1a);
    }
    if (a >= 0x24 && a <= 0x3c) {
        return (u8)(a - 0x1a);
    }
    return 0;
}

u32 LetterStorageMenu::fromLetterGridIndex(u32 a) {
    if (a <= 9) {
        return (u8)(a + 0x1a);
    }
    if (a >= 0xa && a <= 0x22) {
        return (u8)(a + 0x1a);
    }
    return 0x41;
}

s32 LetterStorageMenu::getSlotAt(u32 a, u32 b, u32 c) {
    s32 r = letterGrid.findPocketLetterAt(a, b);
    if (r == 0x37) {
        r = letterGrid.findLetterAt0A(a, b);
    }
    if (r != 0x37) {
        if (c != 0 && LetterGrid_IsSlotEmpty(&letterGrid, r)) {
            return 0x41;
        }
        return fromLetterGridIndex(r);
    }
    return 0x41;
}

BOOL LetterStorageMenu::dropHeldOnSlot(u32 a) {
    if (!isSlotEmpty(a)) {
        Letter_Copy((LetterView *)&swapLetter, (const LetterView *)getSlotLetter(a));
        putLetterInSlot(heldSlot, &swapLetter);
    }
    releaseHeldTo(a);
    return TRUE;
}

void LetterStorageMenu::putLetterInSlot(u32 a, void *c) {
    if (isLetterSlot(a) || isStorageSlot(a)) {
        letterGrid.setLetter(toLetterGridIndex(a), c);
    } else if (isPageTabSlot(a)) {
        Letter_Copy((LetterView *)&storageLetters[(heldOriginSlot - 0x24) + heldOriginPage * 0x19], (const LetterView *)c);
    }
}

void *LetterStorageMenu::getSlotLetter(u32 a) {
    if (isLetterSlot(a) || isStorageSlot(a)) {
        return letterGrid.getLetter(toLetterGridIndex(a));
    }
    return NULL;
}

s32 LetterStorageMenu::getSlotX(u32 a) {
    if (isLetterSlot(a) || isStorageSlot(a)) {
        return LetterGrid_GetSlotX(&letterGrid, toLetterGridIndex(a));
    }
    if (a == 0x3d) {
        return 0xbc;
    }
    if (isPageTabSlot(a)) {
        return Oam_GetObjX(&data_ov105_02298544[(a - 0x3e) * 3].a) + 0x80;
    }
    return 0;
}

s32 LetterStorageMenu::getSlotY(u32 a) {
    if (isLetterSlot(a) || isStorageSlot(a)) {
        return Shared_LetterGrid_GetSlotY(&letterGrid, toLetterGridIndex(a)) - 0x10;
    }
    if (a == 0x3d) {
        return 0xb6;
    }
    if (isPageTabSlot(a)) {
        return Oam_GetObjY((s8 *)&data_ov105_02298544[(a - 0x3e) * 3]) + 0x58;
    }
    return 0;
}

void LetterStorageMenu::disableAllPockets() {
    Shared_InventoryItemGrid_DisableSlotRange(&pocketGrid, 0, 0xe);
    letterGrid.highlightLetterKinds(4);
}

BOOL LetterStorageMenu::isSlotDisabled(u32 a) {
    if (isLetterSlot(a)) {
        return letterGrid.isHighlighted(toLetterGridIndex(a));
    }
    return FALSE;
}

BOOL LetterStorageMenu::isSlotEmpty(u32 a) {
    if (isLetterSlot(a) || isStorageSlot(a)) {
        return LetterGrid_IsSlotEmpty(&letterGrid, toLetterGridIndex(a));
    }
    return TRUE;
}

void LetterStorageMenu::clearFocusSlot() {
    InventoryItemGrid_ClearCursorSlot(&pocketGrid);
    letterGrid.clearCursorSlot();
}

void LetterStorageMenu::setFocusSlot(u32 b) {
    S *s = this;
    if (s->isLetterSlot(b) || s->isStorageSlot(b)) {
        s->letterGrid.setCursorSlot(s->toLetterGridIndex(b));
        InventoryItemGrid_ClearCursorSlot(&s->pocketGrid);
    } else {
        s->clearFocusSlot();
    }
}

void LetterStorageMenu::clearHoverSlot() {
    S *s = this;
    Shared_InventoryItemGrid_ClearMarks(&s->pocketGrid);
    s->letterGrid.clearMarks();
}

void LetterStorageMenu::setHoverSlot(u32 b) {
    S *s = this;
    if (s->isLetterSlot(b) || s->isStorageSlot(b)) {
        s->letterGrid.markSlot(s->toLetterGridIndex(b));
    }
}

BOOL LetterStorageMenu::hasTouchMoved() {
    s32 d = gTouchPressX - gTouchCurX;
    if (d < 0) d = -d;
    if (d > 8) return TRUE;
    d = gTouchPressY - gTouchCurY;
    if (d < 0) d = -d;
    if (d > 8) return TRUE;
    return FALSE;
}

void LetterStorageMenu::placeBalloon() {
    S *s = this;
    s32 r6 = s->getSlotX(s->balloonSlot) - 0x6d;
    s32 r4 = s->getSlotY(s->balloonSlot) - 0x78;
    if (MenuCtrl_IsButtons()) r4 -= 8;
    s->nameBalloon.setPos(r6, r4);
    if (s->isLetterSlot(s->balloonSlot) || s->isStorageSlot(s->balloonSlot)) {
        s->letterGrid.showLetterName(&s->nameBalloon,
 s->toLetterGridIndex(s->balloonSlot));
    }
}

void LetterStorageMenu::updateBalloonForCursor() {
    S *s = this;
    if (s->isLetterSlot(s->cursorSlot) || s->isStorageSlot(s->cursorSlot)) {
        if (s->isSlotEmpty(s->cursorSlot)) {
            s->nameBalloon.cancelQueuedOpen();
        } else {
            s->balloonSlot = s->cursorSlot;
            s->nameBalloon.queueOpen();
        }
    } else {
        s->nameBalloon.cancelQueuedOpen();
    }
}

void LetterStorageMenu::drawHeldItem() {
    S *s = this;
    if (s->testFlags(0x40) == 0) {
        u32 v = s->handKind;
        if (v == 0) {
        } else if (v == 1) {
            s->letterGrid.drawHeldLetter(s->handX, s->handY, &s->heldLetter)
;
        }
    }
}

void LetterStorageMenu::getDragPos() {
    S *s = this;
    s->handX = s->dragOffsetX + gTouchCurX;
    s->handY = s->dragOffsetY + gTouchCurY;
}

void LetterStorageMenu::getHandPos() {
    S *s = this;
    s->handX = s->cursor.getFrameScreenX() - 2;
    s->handY = s->cursor.getFrameScreenY() - 4;
    if (s->cursor.getAnim() == 1) {
        s->handY -= 0x16;
    }
}

void LetterStorageMenu::getFlyPos() {
    S *s = this;
    s->handX = s->flyMotion.getX();
    s->handY = s->flyMotion.getY();
}

void LetterStorageMenu::pickUpFrom(u32 b) {
    S *s = this;
    if (s->isLetterSlot(b) || s->isStorageSlot(b)) {
        u32 r4 = s->toLetterGridIndex(b);
        s->handKind = 1;
        Letter_Copy((LetterView *)&s->heldLetter, (const LetterView *)s->letterGrid.getLetter(r4));
        s->letterGrid.clearLetter(r4);
    }
}

void LetterStorageMenu::releaseHeldTo(u32 b) {
    S *s = this;
    if (s->handKind == 1) {
        s->putLetterInSlot(b, &s->heldLetter);
    }
    s->handKind = 0;
}

void LetterStorageMenu::exchangeHeldWith(u32 b) {
    S *s = this;
    if (s->handKind == 1) {
        Letter_Copy((LetterView *)&s->swapLetter, (const LetterView *)&s->heldLetter);
        s->pickUpFrom(b);
        s->putLetterInSlot(b, &s->swapLetter);
    }
}

void LetterStorageMenu::showCursor() {
    S *s = this;
    s32 r4 = s->getCursorTargetX();
    s32 r2 = s->getCursorTargetY();
    s->cursor.warpTo(r4, r2);
    if (s->isButtonSlot(s->cursorSlot)) {
        s->cursor.setAnimIfChanged(7);
    } else {
        s->cursor.setAnimIfChanged(1);
    }
    s->refreshCursor();
}

s32 LetterStorageMenu::getCursorTargetX() {
    S *s = this;
    s32 r4 = s->getSlotX(s->cursorSlot);
    if (s->testFlags(0x20)) {
        r4 += 0x100;
    } else if (s->testFlags(0x10)) {
        r4 -= 0x100;
    }
    r4 += 8;
    return r4;
}

s32 LetterStorageMenu::getCursorTargetY() {
    S *s = this;
    return s->getSlotY(s->cursorSlot);
}

void LetterStorageMenu::hideCursor() {
    S *s = this;
    s->cursor.setAnimIfChanged(0);
    s->cursor.update();
}

void LetterStorageMenu::moveCursorToTarget() {
    S *s = this;
    if (s->testFlags(8)) {
        s32 r5 = s->getCursorTargetX();
        s32 r2 = s->getCursorTargetY();
        s->cursor.warpTo(r5, r2);
        s->clearFlags(8);
    } else {
        s32 r5 = s->getCursorTargetX();
        s32 r2 = s->getCursorTargetY();
        s->cursor.moveToEase(r5, r2, 3, 1);
        s->returnState = s->mainState;
        s->setMainState(0xd);
    }
}

void LetterStorageMenu::moveCursorToPoint(s32 a, s32 b) {
    S *s = this;
    s->cursor.moveToEase(a, b, 3, 1);
    s->returnState = s->mainState;
    s->setMainState(0xd);
}

void LetterStorageMenu::moveCursorToPopupRow() {
    S *s = this;
    s32 r4 = ((PopupChoiceMenuBody *)&s->popup)->getRowX();
    s32 r2 = ((PopupChoiceMenuBody *)&s->popup)->getRowY(s->popupRow);
    s->cursor.moveToLinear(r4, r2, 2);
    s->returnState = s->mainState;
    s->setMainState(0xd);
}

void LetterStorageMenu::cancelPopup() {
    S *s = this;
    s->popupChoice = 4;
    s->popupRow = PopupChoice_DecideCancel(&s->popup, 1);
    s32 r4 = ((PopupChoiceMenuBody *)&s->popup)->getRowX();
    s32 r2 = ((PopupChoiceMenuBody *)&s->popup)->getRowY(s->popupRow);
    s->cursor.warpTo(r4, r2);
    s->cursor.setAnimAtEnd(8);
    s->setMainState(0x17);
}

void LetterStorageMenu::cursorToPopupTop() {
    S *s = this;
    if (s->testFlags(0x800)) {
        s->popupRow = 1;
    } else {
        s->popupRow = 0;
    }
    s32 r4 = ((PopupChoiceMenuBody *)&s->popup)->getRowX();
    s32 r2 = ((PopupChoiceMenuBody *)&s->popup)->getRowY(s->popupRow);
    s->cursor.warpTo(r4, r2);
    s->cursor.setAnimIfChanged(7);
}

void LetterStorageMenu::showCursorAtSlot() {
    S *s = this;
    s32 r4 = s->getCursorTargetX();
    s32 r2 = s->getCursorTargetY();
    s->cursor.warpTo(r4, r2);
    s->cursor.setAnimIfChanged(1);
}

void LetterStorageMenu::refreshCursor() {
    S *s = this;
    s->cursor.setPoseIdle();
    s->cursor.update();
}

void LetterStorageMenu::pressCloseButton() {
    S *s = this;
    s->cursor.setPosePress();
    s->setMainState(0xe);
}

void LetterStorageMenu::releaseCursor() {
    S *s = this;
    s->cursor.setPoseRelease();
    s->setMainState(0xf);
}

void LetterStorageMenu::beginMoveFromPopup() {
    S *s = this;
    s->cursor.setAnimIfChanged(4);
    s->setMainState(0x10);
    s->setFlags(0x1000);
}

void LetterStorageMenu::beginPutDownAt(u32 b) {
    S *s = this;
    s->nameBalloon.hide(1);
    s->targetSlot = b;
    s->cursor.setAnimIfChanged(5);
    s->setMainState(0x12);
}

void LetterStorageMenu::beginSwapAt(u32 b) {
    S *s = this;
    s->nameBalloon.hide(1);
    s->returnState = s->mainState;
    s->targetSlot = b;
    s->cursor.setAnimIfChanged(6);
    s->setMainState(0x13);
}

void LetterStorageMenu::onPopupChoice() {
    S *s = this;
    switch (s->popupChoice) {
    case 0:
        s->beginMoveFromPopup();
        break;
    case 1:
        s->startReadLetter();
        break;
    case 2:
        s->startDiscardLetter();
        break;
    case 3:
        s->onChoiceDiscard();
        break;
    case 4:
    default:
        s->resumeInput();
        break;
    }
}

void LetterStorageMenu::openPopup(u32 b) {
    S *s = this;
    u32 r2 = s->testFlags(0x800);
    ((PopupChoiceMenuBody *)&s->popup)->setRowsFromIds(&s->choiceList, r2);
    s32 r6 = s->getSlotX(s->selectedSlot);
    s32 r2b = s->getSlotY(s->selectedSlot);
    if (b != 0) {
        s->popup.placeAboveBalloon((LabelBalloon *)(&s->nameBalloon));
    } else {
        s->popup.placeNearPoint(r6, r2b);
    }
    PopupChoice_Open(&s->popup, 0);
    s->setMainState(0x16);
}

void LetterStorageMenu::cancelPopupForButtons() {
    S *s = this;
    s->popupChoice = 4;
    s->showCursorAtSlot();
    PopupChoice_Close(&s->popup, 0);
    s->setMainState(0x18);
}

void LetterStorageMenu::selectLetter(u32 a, u32 b) {
    S *s = this;
    s->clearFlags(0x800);
    s->selectedSlot = a;
    ChoiceIdList_Clear((u8 *)&s->choiceList, 4);
    LetterView *r7 = (LetterView *)s->getSlotLetter(a);
    if (MenuCtrl_IsButtons()) {
        ChoiceIdList_Add((u8 *)&s->choiceList, 0, 0);
    }
    u32 r5 = r7->getState();
    if (r5 != 0) {
        if (r5 == 7) {
            ChoiceIdList_Add((u8 *)&s->choiceList, 0x17, 1);
        } else {
            ChoiceIdList_Add((u8 *)&s->choiceList, 0x14, 1);
        }
    }
    if (r7->getPresent() == 0xfff1) {
        if (r5 == 3 || r5 == 6 || r5 == 1 || r5 == 4) {
            ChoiceIdList_Add((u8 *)&s->choiceList, 0x15, 3);
        }
    }
    ChoiceIdList_Add((u8 *)&s->choiceList, 2, 4);
    s->hideCursor();
    if (b == 0) {
        s->nameBalloon.hide(1);
    }
    s->openPopup(b);
}

void LetterStorageMenu::openDiscardConfirm() {
    setFlags(0x800);
    ChoiceIdList_Clear((u8 *)&choiceList, 4);
    ChoiceIdList_Add((u8 *)&choiceList, 0x1a, 4);
    ChoiceIdList_Add((u8 *)&choiceList, 0x15, 2);
    ChoiceIdList_Add((u8 *)&choiceList, 0x19, 4);
    openPopup(0);
}

void LetterStorageMenu::moveCursorInPocketLetters(u32 pad, u32 x) {
    s32 r6 = cursorSlot - 0x1a;
    s32 r4 = r6 >> 1;
    if (MenuKeys_HasLeft(pad)) {
        if ((r6 & 1) > 0) {
            cursorSlot = cursorSlot - 1;
        } else {
            cursorSlot = r4 * 5 + 0x28;
            return;
        }
    } else if (MenuKeys_HasRight(pad)) {
        if ((r6 & 1) < 1) {
            cursorSlot = cursorSlot + 1;
        } else {
            cursorSlot = r4 * 5 + 0x24;
            setFlags(0x20);
            return;
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
                    cursorSlot = 0x3d;
                    cursor.switchToAnim07();
                }
            }
        }
    }
}

void LetterStorageMenu::moveCursorInStorage(u32 pad, u32 x) {
    s32 r4 = cursorSlot - 0x24;
    s32 r6 = 0;
    while (r4 >= 5) {
        r6++;
        r4 -= 5;
    }
    if (MenuKeys_HasLeft(pad)) {
        if (r4 > 0) {
            cursorSlot = cursorSlot - 1;
            r4 = r4 - 1;
        } else {
            cursorSlot = r6 * 2 + 0x1b;
            setFlags(0x10);
            return;
        }
    } else if (MenuKeys_HasRight(pad)) {
        if (r4 < 4) {
            cursorSlot = cursorSlot + 1;
            r4 = r4 + 1;
        } else {
            cursorSlot = r6 * 2 + 0x1a;
            return;
        }
    }
    if (isStorageSlot(cursorSlot)) {
        if (!testFlags(0x30)) {
            if (MenuKeys_HasUp(pad)) {
                if (r6 > 0) {
                    cursorSlot = cursorSlot - 5;
                } else if (r4 < 3) {
                    cursorSlot = r4 + 0x3e;
                } else {
                    cursorSlot = 0x40;
                }
            } else if (MenuKeys_HasDown(pad)) {
                if (r6 < 4) {
                    cursorSlot = cursorSlot + 5;
                } else if (x == 0) {
                    cursorSlot = 0x3d;
                    cursor.switchToAnim07();
                }
            }
        }
    }
}

void LetterStorageMenu::moveCursorOnButton(u32 pad) {
    if (MenuKeys_HasUp(pad)) {
        cursor.switchToAnim01();
        cursorSlot = 0x22;
    }
}

void LetterStorageMenu::moveCursorOnPageTabs(u32 pad) {
    if (MenuKeys_HasLeft(pad)) {
        if (cursorSlot > 0x3e) {
            cursorSlot = cursorSlot - 1;
        }
    } else if (MenuKeys_HasRight(pad)) {
        if (cursorSlot < 0x40) {
            cursorSlot = cursorSlot + 1;
        }
    }
    if (MenuKeys_HasDown(pad)) {
        cursorSlot = cursorSlot - 0x1a;
    }
}

BOOL LetterStorageMenu::moveCursorByPad(u32 pad, u32 x) {
    u8 old = cursorSlot;
    clearFlags(0x30);
    if (pad == 0) {
        return FALSE;
    }
    if (isLetterSlot(cursorSlot)) {
        moveCursorInPocketLetters(pad, x);
    } else if (isStorageSlot(cursorSlot)) {
        moveCursorInStorage(pad, x);
        if (isPageTabSlot(cursorSlot)) {
            if (x == 1) {
                cursor.setAnimIfChanged(1);
            }
        }
    } else if (isButtonSlot(cursorSlot)) {
        moveCursorOnButton(pad);
    } else if (isPageTabSlot(cursorSlot)) {
        moveCursorOnPageTabs(pad);
        if (!isPageTabSlot(cursorSlot)) {
            if (x == 1) {
                cursor.setAnimAtEnd(4);
            }
        }
    }
    if (old != cursorSlot) {
        return TRUE;
    }
    return FALSE;
}

void LetterStorageMenu::startReadLetter() {
    setTransitionState(4);
    setPhase(1);
    setFlags(0x100);
}

void LetterStorageMenu::closeLetterView() {
    setMainState(0x1a);
    letterCloseButton.setState(2);
    Snd_PlaySe(0x29);
}

void LetterStorageMenu::startDiscardLetter() {
    u8 r4 = selectedSlot;
    pickUpFrom(r4);
    handX = getSlotX(r4);
    handY = getSlotY(r4);
    if (MenuCtrl_IsButtons()) {
        handX -= 2;
        handY -= 2;
    }
    setMainState(0x1c);
    LetterGrid_StartPopAnim(&letterGrid);
}

void LetterStorageMenu::onChoiceDiscard() { openDiscardConfirm(); }

void LetterStorageMenu::func_ov105_0229514c() {}

void LetterStorageMenu::pressTab9() {
    Snd_PlaySe(0x29);
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(9);
    setMainState(0x1b);
    transitionState = 0xe;
}

void LetterStorageMenu::pressCloseTab() {
    Snd_PlaySe(0x27);
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(3);
    transitionState = 4;
    clearFlags(0x100);
    setMainState(0x1b);
}

void LetterStorageMenu::pressTab4() {
    Snd_PlaySe(0x2a);
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(4);
    transitionState = 0x12;
    setMainState(0x1b);
}

void LetterStorageMenu::drawPageTabs() {
    s32 i, j;
    s32 a, b;
    s32 p = boxSlideX + 0x80;
    for (i = 0, j = i; i < 3; i++, j += 3) {
        if (i == currentPage) {
            a = 0x52;
            b = 4;
        } else {
            a = 0x50;
            b = 5;
        }
        Oam_DrawObj(1, &data_ov105_02298544[j], p, a, -1, 1, NULL);
        Oam_DrawObj(1, &data_ov105_02298544[j + 1], p, a, b, 1, NULL);
        Oam_DrawObj(1, &data_ov105_02298544[j + 2], p, 0x50, -1, 1, NULL);
    }
}

void LetterStorageMenu::loadPage() {
    Shared_LetterGrid_SetLetters0A(&letterGrid, (u8 *)&storageLetters[currentPage * 0x19]);
    Gfx2d_LoadCharFile(sLetterStoragePageChars[currentPage], gCurrentHeap, 4, 0x1e2, 0x1e2, 0x1ed);
    beginSubSlideIn(2, 0, 2, 0x30);
    setSlideExtent(0xc0);
    Gfx2d_ShowLayer(4);
    setFlags(0x200);
    scrollBoxBg();
}

void LetterStorageMenu::startPageSlideOut() {
    nameBalloon.hide(1);
    hideCursor();
    beginSubSlideOut(2, 0, 2, 0x30);
    setSlideExtent(0xc0);
}

BOOL LetterStorageMenu::hitPageTab(s32 x, s32 y) {
    s32 i, j;
    s32 xs = x - 0x80;
    volatile s32 yv = y;
    yv = y - 0x60;
    for (i = 0, j = i; i < 3; i++, j += 3) {
        if (i != currentPage) {
            if (Cell_HitTest(&data_ov105_02298544[j], xs, yv, 2, 2)) {
                currentPage = i;
                return TRUE;
            }
        }
    }
    return FALSE;
}

void LetterStorageMenu::startPageSwitch() {
    Snd_PlaySe(data_ov105_02298314[currentPage]);
    nameBalloon.hide(1);
    hideCursor();
    transitionState = 0xb;
    setPhase(1);
    setFlags(0x40);
}

void LetterStorageMenu::beginDimBackground() {
    Gfx2d_BeginSubObjWinBrightness();
    Gfx2d_SetSubBrightness(-6);
    ((MenuBottomButtonsBody *)&bottomButtons)->enableObjWindow();
}

void LetterStorageMenu::endDimBackground() {
    Gfx2d_EndSubObjWinBrightness();
    ((MenuBottomButtonsBody *)&bottomButtons)->disableObjWindow();
}

BOOL LetterStorageMenu::switchPageByShoulder() {
    s32 d = 0;
    u32 k = gPad[1];
    if (k & 0x200) {
        d = -1;
    } else if (k & 0x100) {
        d = 1;
    }
    if (d != 0) {
        d += currentPage;
        if (d < 0) {
            d = 2;
        } else if (d > 2) {
            d = 0;
        }
        currentPage = d;
        startPageSwitch();
    }
    return FALSE;
}

BOOL LetterStorageMenu::testFlags(u32 mask) {
    if (stateFlags & mask) {
        return TRUE;
    }
    return FALSE;
}

void LetterStorageMenu::setFlags(u32 mask) { stateFlags = stateFlags | mask; }

void LetterStorageMenu::clearFlags(u32 mask) { stateFlags = stateFlags & ~mask; }

extern "C" const char *sLetterStoragePageChars[3] = {data_ov105_022984e4, data_ov105_02298504, data_ov105_02298524};

extern "C" char data_ov105_02298504[] = "menu/inventory/b_itm_post1.bch";

extern "C" const u16 data_ov105_02298314[3] = {0x1b, 0x1c, 0x1d};

extern "C" char data_ov105_022984e4[] = "menu/inventory/b_itm_post0.bch";

extern "C" Unk_ov105_Ent data_ov105_02298544[9] = {
    {0x41ac00c0, 0x000041c0}, {0x41ac00c1, 0x0000411e}, {0x41ac00c3, 0x0000111e},
    {0x41c400c0, 0x000041c2}, {0x41c400c1, 0x0000511e}, {0x41c400c3, 0x0000111e},
    {0x41dc00c0, 0x000041c4}, {0x41dc00c1, 0x0000511e}, {0x41dc00c3, 0xffff111e},
};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov105_02294c40) {
    HOST_OVERLAY_VAR(sLetterStorageMenuProfile),
    HOST_OVERLAY_VAR(data_ov105_02298524),
    HOST_OVERLAY_VAR(sLetterStoragePageChars),
    HOST_OVERLAY_VAR(data_ov105_02298504),
    HOST_OVERLAY_VAR(data_ov105_022984e4),
    HOST_OVERLAY_VAR(data_ov105_02298544),
    HOST_OVERLAY_VARS_END
};
