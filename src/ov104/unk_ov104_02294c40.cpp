#include "types.h"
#include "host_tick.h"
#include "host_labels.h"
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
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_02065e88.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0206f4f0.h"
#include "proto/main/unk_02095cdc.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov002/unk_ov002_02202fac.h"
#include "proto/ov094/unk_ov094_02292360.h"
#include "proto/ov094/unk_ov094_02292da8.h"
#include "proto/ov094/unk_ov094_02293b90.h"
#include "proto/ov104/unk_ov104_02294c40.h"

class PostOfficeMenu;
class MenuLauncher;
class Letter;
typedef PostOfficeMenu S;


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
#define gSavePlayers HOST_LABEL(u8 (*)[], gSavePlayers)
}




extern "C" CommManager *gCommManager;



struct LetterView;










struct PopupChoiceIdList;








typedef void (PostOfficeMenu::*Unk_ov104_02298170_Fn)();

class PostOfficeMenu : public MenuProc {
public:
    PostOfficeMenu()
        : heldLetter(), swapLetter(), bgTasks(), pocketGrid(), letterGrid(), inventoryBg(), nameBalloon(), flyMotion(), cursor(), popup(),
          errorMessage(), letterView(), letterCloseButton(), boxLetters(), pocketLettersBackup(), bottomButtons() {}
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual BOOL execTransition();
    virtual BOOL execMain();
    virtual BOOL execPhase3();
    virtual BOOL execPhase4();
    virtual BOOL execClosed();

    void clearFlags(u32 mask);
    void setFlags(u32 mask);
    BOOL testFlags(u32 mask);
    BOOL sendLetterRecord(Letter *p);
    void updateOnlineSend();
    void beginOnlineSend();
    u32 deliverVillagerLettersNow(Letter *p);
    u32 deliverToMailboxes(Letter *p);
    s32 queueLetterForDelivery(Letter *p);
    u32 queueLetters(Letter *p);
    u32 checkSendLetters(Letter *p, s32 flag);
    u32 takeFutureLetter(Letter *p);
    BOOL hasFutureLetter(Letter *p);
    void pressCancelButton();
    void pressSendButton();
    void returnUnsentLetters(s32 flag);
    void exchangeHeldWith(u32 i);
    void releaseHeldTo(u32 i);
    void pickUpFrom(u32 i);
    void getFlyPos();
    void getHandPos();
    void getDragPos();
    void drawHeldItem();
    void updateBalloonForCursor();
    void placeBalloon();
    BOOL hasTouchMoved();
    void setHoverSlot(u32 i);
    void clearHoverSlot();
    void setFocusSlot(u32 i);
    void clearFocusSlot();
    BOOL isSlotEmpty(u32 i);
    BOOL isSlotDisabled(u32 i);
    void disableAllPockets();
    s32 getSlotY(u32 i);
    s32 getSlotX(u32 i);
    void * getSlotLetter(u32 i);
    void putLetterInSlot(u32 i, void *p);
    BOOL dropHeldOnSlot(u32 i);
    u8 getSlotAt(u32 i, s32 a, u32 flag);
    u8 fromLetterGridIndex(u32 i);
    u8 toLetterGridIndex(u32 i);
    BOOL isButtonSlot(u32 i);
    BOOL isBoxSlot(u32 i);
    BOOL isLetterSlot(u32 i);
    void cancelBgTasks();
    u8 findFreeBoxSlot();
    u8 findFreePocketSlot();
    void pickUpAndFlyTo(u32 i, u32 a);
    void flyHeldToOtherList(u32 i, s32 a);
    void flyHeldTo(u32 i, u32 a);
    void pickUpAtSlot(u32 i);
    void beginDragFromSlot(u32 i);
    void beginTouchOnSlot(u32 i);
    void resumeInput();
    void startButtonInput();
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
    /* 0xa0 */ s32 dragOffsetX;
    /* 0xa4 */ s32 dragOffsetY;
    /* 0xa8 */ s32 handX;
    /* 0xac */ s32 handY;
    /* 0xb0 */ u16 onlineSendResult;
    /* 0xb2 */ u16 sentLetterMask;
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
    /* 0xbe */ u8 sendIndex;
    /* 0xbf */ volatile u8 touchHoldDelay;
    /* 0x0c0 */ Letter heldLetter;
    /* 0x1b4 */ Letter swapLetter;
    /* 0x2a8 */ BgVramTaskPair bgTasks[1];
    /* 0x2e0 */ InventoryItemGrid pocketGrid;
    /* 0xd40 */ LetterGrid letterGrid;
    /* 0xd68 */ InventoryBg inventoryBg;
    /* 0x2348 */ TouchPromptBalloon nameBalloon;
    /* 0x2408 */ CursorMotion flyMotion;
    /* 0x2420 */ MenuCursorBuf0 cursor;
    /* 0x2484 */ PopupChoiceMenu popup;
    /* 0x2778 */ PopupChoiceIdList choiceList;
    /* 0x2783 */ u8 pad_2783[1];
    /* 0x2784 */ MenuErrorMessage errorMessage;
    /* 0x288c */ LetterRenderer letterView;
    /* 0x2a9c */ MenuLabelButton letterCloseButton;
    /* 0x2b0c */ Letter boxLetters[10];
    /* 0x3494 */ Letter pocketLettersBackup[10];
    /* 0x3e1c */ MenuBottomButtons bottomButtons;
};


extern "C" {
void PostOfficeMenu_RestorePocketLetters(S *s);
void PostOfficeMenu_BackupPocketLetters(S *s);
void PostOfficeMenu_OnChoiceDiscard(S *s);
void PostOfficeMenu_StartDiscardLetter(S *s);
void PostOfficeMenu_CloseLetterView(S *s);
void PostOfficeMenu_StartReadLetter(S *s);
BOOL PostOfficeMenu_MoveCursorByPad(S *s, s32 a, s32 b);
void PostOfficeMenu_MoveCursorOnButtons(S *s, s32 a);
void PostOfficeMenu_MoveCursorInBox(S *s, s32 a, s32 b);
void PostOfficeMenu_MoveCursorInPocketLetters(S *s, s32 a, s32 b);
void PostOfficeMenu_OpenDiscardConfirm(S *s);
void PostOfficeMenu_SelectLetter(S *s, u32 a, s32 b);
void PostOfficeMenu_CancelPopupForButtons(S *s);
void PostOfficeMenu_OpenPopup(S *s, s32 a);
void PostOfficeMenu_OnPopupChoice(S *s);
void PostOfficeMenu_BeginSwapAt(S *s, u32 a);
void PostOfficeMenu_BeginPutDownAt(S *s, u32 a);
void PostOfficeMenu_BeginMoveFromPopup(S *s);
void PostOfficeMenu_PressButton(S *s);
void PostOfficeMenu_RefreshCursor(S *s);
void PostOfficeMenu_ShowCursorAtSlot(S *s);
void PostOfficeMenu_CursorToPopupTop(S *s);
void PostOfficeMenu_CancelPopup(S *s);
void PostOfficeMenu_MoveCursorToPopupRow(S *s);
void PostOfficeMenu_MoveCursorToTarget(S *s);
void PostOfficeMenu_HideCursor(S *s);
s32 PostOfficeMenu_GetCursorTargetY(S *s);
s32 PostOfficeMenu_GetCursorTargetX(S *s);
void PostOfficeMenu_ShowCursor(S *s);
void PostOfficeMenu_StartTouchInput(S *s);
void PostOfficeMenu_LoadObjGraphics(S *s);
void PostOfficeMenu_LoadBoxBg(S *s);
void PostOfficeMenu_LoadInventoryBg(S *s);
void PostOfficeMenu_PostStateUpdate(S *s);
void PostOfficeMenu_PreStateUpdate(S *s);
void PostOfficeMenu_PostInputUpdate(S *s);
void PostOfficeMenu_PreInputUpdate(S *s);
void PostOfficeMenu_ReleaseResources(S *s);
void PostOfficeMenu_InitParts(S *s);
void PostOfficeMenu_ScrollBoxBg(S *s);
void PostOfficeMenu_ScrollMainBg(S *s);
void PostOfficeMenu_ScrollLetterViewBg(S *s);
}

static inline BOOL Unk_ov104_02296fdc_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) return TRUE;
    return FALSE;
}

static inline BOOL Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) return TRUE;
    return FALSE;
}


extern "C" PostOfficeMenu *PostOfficeMenu_Create() { return new PostOfficeMenu(); }

BOOL PostOfficeMenu::onCreate() {
    PostOfficeMenu_InitParts(this);
    setTransitionState(0);
    setPhase(0);
    return TRUE;
}

BOOL PostOfficeMenu::onDelete() {
    ((MenuLauncher *)ProcBase_GetParent(this))->onChildClosed();
    PostOfficeMenu_ReleaseResources(this);
    return TRUE;
}

BOOL PostOfficeMenu::onDraw() {
    if (!testFlags(1)) {
        return TRUE;
    }
    nameBalloon.draw();
    if (MenuCtrl_IsButtons()) {
        cursor.drawWrapped();
    }
    drawHeldItem();
    if (testFlags(2)) {
        bottomButtons.drawAt(slideY);
        s32 t = slideY - 0x10;
        InventoryItemGrid_DrawPockets(&pocketGrid, 0, t);
        letterGrid.drawPocketLetters(0, t);
        Shared_InventoryBg_DrawSprite(&inventoryBg, t);
    }
    if (testFlags(0x200)) {
        letterGrid.drawLetters2D(boxSlideX, -0x10);
    }
    if (testFlags(0x80)) {
        letterCloseButton.setPos(0, getSlideOffsetY());
        letterCloseButton.draw();
    }
    return TRUE;
}
extern "C" ProcProfile sPostOfficeMenuProfile;

extern "C" ProcProfile sPostOfficeMenuProfile = {(void *(*)())PostOfficeMenu_Create, 0x97, 0x9b};

BOOL PostOfficeMenu::execTransition() {
    static Unk_ov104_02298170_Fn tbl[11] = {
        &PostOfficeMenu::transitionAct00,
        &PostOfficeMenu::transitionAct01,
        &PostOfficeMenu::transitionAct02,
        &PostOfficeMenu::transitionAct03,
        &PostOfficeMenu::transitionAct04,
        &PostOfficeMenu::transitionAct05,
        &PostOfficeMenu::transitionAct06,
        &PostOfficeMenu::transitionAct07,
        &PostOfficeMenu::transitionAct08,
        &PostOfficeMenu::transitionAct09,
        &PostOfficeMenu::transitionAct0A};
    PostOfficeMenu_PreStateUpdate(this);
    (this->*tbl[transitionState])();
    PostOfficeMenu_PostStateUpdate(this);
    return TRUE;
}

void PostOfficeMenu::runMainState() {
    static Unk_ov104_02298170_Fn tbl[29] = {
        &PostOfficeMenu::mainAct00,
        &PostOfficeMenu::mainAct01,
        &PostOfficeMenu::mainAct02,
        &PostOfficeMenu::mainAct03,
        &PostOfficeMenu::mainAct04,
        &PostOfficeMenu::mainAct05,
        &PostOfficeMenu::mainAct06,
        &PostOfficeMenu::mainAct07,
        &PostOfficeMenu::mainAct08,
        &PostOfficeMenu::mainAct09,
        &PostOfficeMenu::mainAct0A,
        &PostOfficeMenu::mainAct0B,
        &PostOfficeMenu::mainAct0C,
        &PostOfficeMenu::mainAct0D,
        &PostOfficeMenu::mainAct0E,
        &PostOfficeMenu::mainAct0F,
        &PostOfficeMenu::mainAct10,
        &PostOfficeMenu::mainAct11,
        &PostOfficeMenu::mainAct12,
        &PostOfficeMenu::mainAct13,
        &PostOfficeMenu::mainAct14,
        &PostOfficeMenu::mainAct15,
        &PostOfficeMenu::mainAct16,
        &PostOfficeMenu::mainAct17,
        &PostOfficeMenu::mainAct18,
        &PostOfficeMenu::mainAct19,
        &PostOfficeMenu::mainAct1A,
        &PostOfficeMenu::mainAct1B,
        &PostOfficeMenu::mainAct1C};
    (this->*tbl[mainState])();
}

BOOL PostOfficeMenu::execMain() {
    PostOfficeMenu_PreInputUpdate(this);
    runMainState();
    PostOfficeMenu_PostInputUpdate(this);
    return TRUE;
}

BOOL PostOfficeMenu::execPhase3() { return TRUE; }

BOOL PostOfficeMenu::execPhase4() { return TRUE; }

BOOL PostOfficeMenu::execClosed() {
    u32 r4;
    if (testFlags(0x400)) {
        PostOfficeMenu_RestorePocketLetters(this);
        MenuCtrl_SetResult(0);
    } else if (testFlags(0x800)) {
        if (testFlags(0x1000)) return TRUE;
        if ((onlineSendResult & 4) != 0) {
            MenuCtrl_SetResult(0);
        } else {
            MenuCtrl_SetResult(1);
        }
        returnUnsentLetters(1);
        MenuCtrl_SetPostOfficeResult(onlineSendResult);
    } else {
        MenuCtrl_SetResult(1);
        r4 = 0;
        if (LetterList_Compact(boxLetters, 10) <= 0) r4 = 4;
        if (PlayerData_GetCurrent()->testFlag(1)) {
            r4 |= deliverVillagerLettersNow(boxLetters);
        }
        r4 |= takeFutureLetter(boxLetters);
        r4 |= checkSendLetters(boxLetters, 0);
        if ((r4 & 4) != 0) {
            MenuCtrl_SetResult(0);
        } else if ((r4 & 0x10) != 0) {
            LetterDelivery_DeliverOutgoing();
            r4 |= queueLetters(boxLetters);
            if ((r4 & 0x20) != 0) {
                r4 |= deliverToMailboxes(boxLetters);
            }
        }
        returnUnsentLetters(0);
        MenuCtrl_SetPostOfficeResult(r4);
        if (MenuCtrl_GetPostOfficeOutcome() == 1 || MenuCtrl_PostOfficeLettersSent() != 0) {
            Arbeit_NotifyLetterWritten();
        }
    }
    LetterDelivery_PostOfficeClosedNop();
    ProcBase_RequestDelete(this);
    return TRUE;
}

BOOL PostOfficeMenu::onExecute() {
    updateOnlineSend();
    return MenuProc::onExecute();
}

void PostOfficeMenu::transitionAct00() {
    PostOfficeMenu_SetupBgLayers();
    PostOfficeMenu_LoadInventoryBg(this);
    setTransitionState(1);
}

void PostOfficeMenu::transitionAct01() {
    PostOfficeMenu_LoadObjGraphics(this);
    Shared_InventoryItemGrid_LoadPockets(&pocketGrid);
    Shared_LetterGrid_LoadPocketLetters(&letterGrid);
    Shared_LetterGrid_SetLetters2D(&letterGrid, (u8 *)boxLetters);
    disableAllPockets();
    beginSubSlideIn(8, 0, 0, 0x30);
    Gfx2d_ShowLayer(6);
    setTransitionState(2);
    setFlags(1);
    setFlags(2);
    PostOfficeMenu_ScrollMainBg(this);
}

void PostOfficeMenu::transitionAct02() {
    u32 r = stepSlideIn(0);
    PostOfficeMenu_ScrollMainBg(this);
    if (r != 0) {
        PostOfficeMenu_LoadBoxBg(this);
        beginSubSlideIn(2, 0, 2, 0x30);
        setSlideExtent(0xc0);
        Gfx2d_ShowLayer(4);
        setFlags(0x200);
        PostOfficeMenu_ScrollBoxBg(this);
        setTransitionState(3);
    }
}

void PostOfficeMenu::transitionAct03() {
    if (stepSlideIn(0)) {
        setPhase(2);
        resumeInput();
    }
    PostOfficeMenu_ScrollBoxBg(this);
}

void PostOfficeMenu::transitionAct04() {
    nameBalloon.hide(1);
    PostOfficeMenu_HideCursor(this);
    if (!testFlags(0x100)) {
        ((MenuLauncher *)(void *)ProcBase_GetParent(this))->setNextRequest(0x44, 1);
    }
    beginSubSlideOut(2, 0, 2, 0x30);
    setSlideExtent(0xc0);
    setTransitionState(5);
}

void PostOfficeMenu::transitionAct05() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(4);
        clearFlags(0x200);
        beginSubSlideOut(8, 0, 0, 0x30);
        setTransitionState(6);
        transitionAct06();
    } else {
        PostOfficeMenu_ScrollBoxBg(this);
    }
}

void PostOfficeMenu::transitionAct06() {
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
        PostOfficeMenu_ScrollMainBg(this);
    }
}

void PostOfficeMenu::transitionAct07() {
    void *t = getSlotLetter(selectedSlot);
    Letter_MarkRead((LetterView *)t);
    letterView.show((LetterView *)t, 3, 4, 1);
    beginSubSlideIn(3, 0, 0, 0x30);
    Gfx2d_ShowLayer(3);
    Gfx2d_ShowLayer(4);
    PostOfficeMenu_ScrollLetterViewBg(this);
    setTransitionState(8);
    letterCloseButton.showDefault(0x88);
    setFlags(0x80);
}

void PostOfficeMenu::transitionAct08() {
    if (stepSlideIn(0)) {
        setPhase(2);
        if (MenuCtrl_IsTouch()) {
            setMainState(5);
        } else {
            setMainState(9);
        }
    } else {
        PostOfficeMenu_ScrollLetterViewBg(this);
    }
}

void PostOfficeMenu::transitionAct09() {
    beginSubSlideOut(3, 0, 0, 0x30);
    PostOfficeMenu_ScrollLetterViewBg(this);
    setTransitionState(10);
}

void PostOfficeMenu::transitionAct0A() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(3);
        Gfx2d_ResetLayer(4);
        clearFlags(0x80);
        transitionAct00();
    } else {
        PostOfficeMenu_ScrollLetterViewBg(this);
    }
}

void PostOfficeMenu_ScrollLetterViewBg(S *s) {
    s->applySlideOffset(3, 0, 0);
    s->applySlideOffset(4, 0, 0);
}

void PostOfficeMenu_ScrollMainBg(S *s) {
    s->applySlideOffset(6, 0, -16);
    s->slideY = s->getSlideOffsetY();
}

void PostOfficeMenu_ScrollBoxBg(S *s) {
    s->applySlideOffset(4, 0, -16);
    s->boxSlideX = s->getSlideOffsetX();
}

void PostOfficeMenu_InitParts(S *s) {
    s32 i;
    s->stateFlags = 0;
    InventoryItemGrid_Init(&s->pocketGrid, 2);
    s->letterGrid.init(1);
    Shared_InventoryBg_Init(&s->inventoryBg, 6);
    s->balloonSlot = 0x21;
    s->flyMotion.reset();
    s->handKind = 0;
    s->cursorSlot = 0xb;
    s->popup.init(3, 0, 0);
    s->letterView.setLayer(3);
    for (i = 0; i < 10; i++) {
        Letter_Clear((LetterView *)&s->boxLetters[i]);
    }
    PostOfficeMenu_BackupPocketLetters(s);
    s->touchHoldDelay = 0;
}

void PostOfficeMenu_ReleaseResources(S *s) {
    s->cancelBgTasks();
    InventoryBg_Exit(&s->inventoryBg);
    Shared_InventoryItemGrid_Exit(&s->pocketGrid);
    PopupChoice_ForceClose(&s->popup);
    s->letterView.release();
    s->bottomButtons.freeTexts();
}

void PostOfficeMenu_PreInputUpdate(S *s) {
    PostOfficeMenu_PreStateUpdate(s);
    s->cursor.update();
}

void PostOfficeMenu_PostInputUpdate(S *s) {
    PostOfficeMenu_PostStateUpdate(s);
}

void PostOfficeMenu_PreStateUpdate(S *s) {
    s->cancelBgTasks();
    Shared_InventoryBg_PreUpdate(&s->inventoryBg);
    InventoryItemGrid_PreUpdate(&s->pocketGrid);
    s->letterGrid.updateCursorLift();
    s->bottomButtons.freeTexts();
}

void PostOfficeMenu_PostStateUpdate(S *s) {
    Shared_PopupChoice_Update(&s->popup);
    InventoryBg_Update(&s->inventoryBg);
    if (s->nameBalloon.updatePrompt()) {
        s->placeBalloon();
    }
}

void PostOfficeMenu_SetupBgLayers() {
    Gfx2d_SetLayerPriority(6, 2);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
    Gfx2d_SetLayerPriority(4, 1);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
}

void PostOfficeMenu_LoadInventoryBg(S *s) {
    InventoryBg_Load(&s->inventoryBg, 0);
}

void PostOfficeMenu_LoadBoxBg(S *s) {
    void *t = gCurrentHeap;
    Gfx2d_LoadPaletteFile("menu/inventory/b_itm_post.bpl", t, 4, 4, 4, 4);
    Gfx2d_LoadScreenFile("menu/inventory/b_itm_bg_ltr2.bsc", t, 4);
    Gfx2d_LoadCharFile("menu/inventory/b_itm_post.bch", t, 4, 0x1e2, 0x1e2, 0x227);
}

void PostOfficeMenu_LoadObjGraphics(S *s) {
    InventoryBg_LoadObjGraphics();
    MenuButtons_LoadTextColors();
    s->bottomButtons.setLayoutConfirmAnd06(0x65);
}

void PostOfficeMenu::mainAct00() {
    if (checkSwitchToButtons(1)) {
        startButtonInput();
    } else if (Both()) {
        s32 r = getSlotAt(gTouchCurX, gTouchCurY + 0x10, 1);
        if (r != 0x21) {
            beginTouchOnSlot(r);
        } else if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(9)) {
            pressSendButton();
        } else if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(7)) {
            pressCancelButton();
        }
    }
}

void PostOfficeMenu::mainAct01() {
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
                    touchHoldDelay = touchHoldDelay - (TICK_STEP_ENDS() ? 1 : 0);
                } else {
                    PostOfficeMenu_SelectLetter(this, touchedSlot, 1);
                    setMainState(2);
                }
                return;
            }
        }
        nameBalloon.commitOpen();
    }
}

void PostOfficeMenu::mainAct02() {
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

void PostOfficeMenu::mainAct03() {
    if (nameBalloon.isOpenOrOpening()) {
        if (touchHoldDelay != 0) {
            touchHoldDelay = touchHoldDelay - (TICK_STEP_ENDS() ? 1 : 0);
        } else {
            PostOfficeMenu_SelectLetter(this, touchedSlot, 1);
            setMainState(2);
        }
    }
}

void PostOfficeMenu::mainAct04() {
    s32 p, t;
    getDragPos();
    clearHoverSlot();
    p = handX + 8;
    t = getSlotAt(p, handY + 0x18, 0);
    if ((isLetterSlot(t) && isBoxSlot(heldSlot))
        || (isBoxSlot(t) && isLetterSlot(heldSlot))) {
        if (isSlotEmpty(t) == 0) {
            t = 0x21;
        }
    }
    if (t != 0x21) {
        if (gTouchHeld == 0) {
            if (isSlotDisabled(t) != 0 || dropHeldOnSlot(t) == 0) {
                flyHeldToOtherList(heldSlot, p);
            } else {
                Inventory_PlayPutDownSe();
                resumeInput();
            }
        } else {
            setHoverSlot(t);
        }
    } else if (gTouchHeld == 0) {
        flyHeldToOtherList(heldSlot, p);
    }
}

void PostOfficeMenu::mainAct05() {
    if (checkSwitchToButtons(1)) {
        setMainState(9);
    } else {
        if (letterCloseButton.isTouched()) {
            PostOfficeMenu_CloseLetterView(this);
        }
    }
}

void PostOfficeMenu::mainAct06() {
    if (((PopupChoiceMenuBody *)&popup)->isOpen()) {
        if (checkSwitchToButtons(1)) {
            PostOfficeMenu_CancelPopupForButtons(this);
        } else {
            if (Unk_ov104_02296fdc_Both()) {
                s32 t = ((PopupChoiceMenuBody *)&popup)->hitTestRowOrLast(gTouchCurX, gTouchCurY);
                if (t >= 0) {
                    if (testFlags(0x8000) == 0 || t != 0) {
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

void PostOfficeMenu::mainAct07() {
    if (checkSwitchToTouch()) {
        PostOfficeMenu_StartTouchInput(this);
        nameBalloon.hide(1);
    } else {
        s32 v = takeRepeatedKeys();
        if (PostOfficeMenu_MoveCursorByPad(this, v, 0)) {
            updateBalloonForCursor();
            PostOfficeMenu_MoveCursorToTarget(this);
            nameBalloon.hide(0);
        } else {
            if (isSlotDisabled(cursorSlot) != 0) goto tail;
            {
                u32 k = gPad[1];
                if (k & 1) {
                    if (isLetterSlot(cursorSlot) || isBoxSlot(cursorSlot)) {
                        if (isSlotEmpty(cursorSlot) == 0) {
                            PostOfficeMenu_SelectLetter(this, cursorSlot, 0);
                        }
                    } else if (isButtonSlot(cursorSlot)) {
                        PostOfficeMenu_PressButton(this);
                    }
                } else if (k & 0x800) {
                    if (isLetterSlot(cursorSlot) || isBoxSlot(cursorSlot)) {
                        if (isSlotEmpty(cursorSlot) == 0) {
                            s32 r = isLetterSlot(cursorSlot) ? findFreeBoxSlot() : findFreePocketSlot();
                            if (r != 0x21) {
                                pickUpAndFlyTo(cursorSlot, r);
                                nameBalloon.hide(1);
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
                if (k & 2) {
                    PostOfficeMenu_HideCursor(this);
                    pressCancelButton();
                    nameBalloon.hide(0);
                } else if (k & 8) {
                    PostOfficeMenu_HideCursor(this);
                    pressSendButton();
                    nameBalloon.hide(0);
                } else {
                    nameBalloon.commitOpen();
                }
            }
        }
    }
}

void PostOfficeMenu::mainAct08() {
    if (PostOfficeMenu_MoveCursorByPad(this, takeRepeatedKeys(), 1)) {
        updateBalloonForCursor();
        PostOfficeMenu_MoveCursorToTarget(this);
        nameBalloon.hide(0);
    } else {
        u32 k = gPad[1];
        if (k & 1) {
            if (isSlotDisabled(cursorSlot) == 0) {
                if (isSlotEmpty(cursorSlot)) {
                    PostOfficeMenu_BeginPutDownAt(this, cursorSlot);
                } else {
                    PostOfficeMenu_BeginSwapAt(this, cursorSlot);
                }
            }
        } else if (k & 2) {
            PostOfficeMenu_BeginPutDownAt(this, heldSlot);
        } else {
            getHandPos();
            nameBalloon.commitOpen();
        }
    }
}

void PostOfficeMenu::mainAct09() {
    if (cursor.getAnim() == 0) {
        s32 a = letterCloseButton.getAnchorX(1);
        s32 b = letterCloseButton.getAnchorY(1);
        cursor.warpTo(a, b);
        cursor.setAnimIfChanged(1);
    }
    if (checkSwitchToTouch()) {
        PostOfficeMenu_HideCursor(this);
        setMainState(5);
    } else {
        u32 k = gPad[1];
        if ((k & 1) || (k & 2)) {
            cursor.setPosePress();
            setMainState(10);
        }
    }
}

void PostOfficeMenu::mainAct0A() {
    if (cursor.isAnimDone()) {
        PostOfficeMenu_CloseLetterView(this);
    }
}

void PostOfficeMenu::mainAct0B() {
    if (checkSwitchToTouch()) {
        PostOfficeMenu_CancelPopupForButtons(this);
    } else {
        s32 v = takeRepeatedKeys();
        u8 f = (u8)testFlags(0x8000);
        if (PopupChoice_MoveCursor(&popup, v, &popupRow, f)) {
            PostOfficeMenu_MoveCursorToPopupRow(this);
        } else {
            u32 k = gPad[1];
            if (k & 1) {
                cursor.setPosePress();
                setMainState(0xc);
            } else if (k & 2) {
                PostOfficeMenu_CancelPopup(this);
            }
        }
    }
}

void PostOfficeMenu::mainAct0C() {
    if (cursor.isAnimDone()) {
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

void PostOfficeMenu::mainAct0D() {
    if (cursor.isMoving() == 0) {
        setMainState(returnState);
        if (returnState == 7) {
            setFocusSlot(cursorSlot);
        }
        runMainState();
    }
    getHandPos();
}

void PostOfficeMenu::mainAct0E() {
    if (cursor.isAnimDone()) {
        if (cursorSlot == 0x1f) {
            pressSendButton();
        } else {
            pressCancelButton();
        }
    }
}

void PostOfficeMenu::mainAct0F() {
    if (cursor.isAnimDone()) {
        PostOfficeMenu_RefreshCursor(this);
        setMainState(7);
    }
}

void PostOfficeMenu::mainAct10() {
    if (cursor.isGripping()) {
        pickUpAtSlot(cursorSlot);
        setMainState(0x11);
    }
}

void PostOfficeMenu::mainAct11() {
    if (cursor.isAnimDone()) {
        setMainState(returnState);
    }
    getHandPos();
}

void PostOfficeMenu::mainAct12() {
    if (cursor.isGripping() == 0) {
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

void PostOfficeMenu::mainAct13() {
    if (cursor.func_ov002_022028fc() == 0) {
        exchangeHeldWith(targetSlot);
        setFlags(0x40);
        setMainState(0x14);
        updateBalloonForCursor();
    } else {
        setMainState(7);
    }
}

void PostOfficeMenu::mainAct14() {
    if (cursor.isAnimDone()) {
        setMainState(returnState);
    }
    if (cursor.isGripping()) {
        if (testFlags(0x40)) {
            clearFlags(0x40);
            Shared_Inventory_PlayPickUpSe();
        }
        getHandPos();
    }
}

void PostOfficeMenu::mainAct15() {
    if (flyMotion.update()) {
        releaseHeldTo(heldSlot);
        resumeInput();
        Inventory_PlayPutDownSe();
    } else {
        getFlyPos();
    }
}

void PostOfficeMenu::mainAct16() {
    if (((PopupChoiceMenuBody *)&popup)->isOpen()) {
        if (MenuCtrl_IsButtons()) {
            PostOfficeMenu_CursorToPopupTop(this);
            setMainState(0xb);
        } else {
            setMainState(6);
        }
    }
}

void PostOfficeMenu::mainAct17() {
    if (PopupChoice_TickDecideDelay(&popup)) {
        PopupChoice_Close(&popup, 0);
        nameBalloon.hide(1);
        if (cursor.getAnim()) {
            PostOfficeMenu_ShowCursorAtSlot(this);
        }
        setMainState(0x18);
    }
}

void PostOfficeMenu::mainAct18() {
    if (((PopupChoiceMenuBody *)&popup)->isClosed()) {
        PostOfficeMenu_OnPopupChoice(this);
    }
}

void PostOfficeMenu::mainAct19() {
    if (errorMessage.update(0)) {
        setMainState(returnState);
        cursor.enableObjWindow();
    }
}

void PostOfficeMenu::mainAct1A() {
    if (letterCloseButton.stepAnim()) {
        if (cursor.getAnim()) {
            s32 a = letterCloseButton.getAnchorX(1);
            s32 b = letterCloseButton.getAnchorY(1);
            cursor.warpTo(a, b);
        }
    } else {
        PostOfficeMenu_HideCursor(this);
        setTransitionState(9);
        setPhase(1);
    }
}

void PostOfficeMenu::mainAct1B() {
    if (((MenuBottomButtonsBody *)&bottomButtons)->stepPress()) {
        if (cursor.getAnim()) {
            s32 a = ((MenuBottomButtonsBody *)&bottomButtons)->getPressOffset();
            s32 b = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(-1);
            s32 c = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(-1);
            cursor.warpTo(a + b, a + c);
        }
    } else {
        PostOfficeMenu_HideCursor(this);
        setPhase(1);
    }
}

void PostOfficeMenu::mainAct1C() {
    if (Shared_LetterGrid_UpdatePopAnim(&letterGrid)) {
        handKind = 0;
        resumeInput();
    }
}

void PostOfficeMenu_StartTouchInput(S *s) {
    PostOfficeMenu_HideCursor(s);
    s->clearFocusSlot();
    s->setMainState(0);
}

void PostOfficeMenu::startButtonInput() {
    balloonSlot = 0x21;
    PostOfficeMenu_ShowCursor(this);
    restartKeyRepeat();
    updateBalloonForCursor();
    setMainState(7);
    setFocusSlot(cursorSlot);
}

void PostOfficeMenu::resumeInput() {
    if (MenuCtrl_IsTouch()) {
        PostOfficeMenu_StartTouchInput(this);
    } else {
        startButtonInput();
    }
}

void PostOfficeMenu::beginTouchOnSlot(u32 i) {
    touchedSlot = i;
    setMainState(1);
    u32 gx = gTouchCurX;
    u32 gy = gTouchCurY;
    dragOffsetX = getSlotX(touchedSlot) - gx;
    dragOffsetY = getSlotY(touchedSlot) - gy;
    balloonSlot = i;
    nameBalloon.queueOpen();
    nameBalloon.commitOpen();
    touchHoldDelay = 2;
    if (isSlotDisabled(i)) {
        clearFlags(4);
    } else {
        setFlags(4);
        Inventory_PlayTouchSe();
    }
}

void PostOfficeMenu::beginDragFromSlot(u32 i) {
    heldSlot = i;
    nameBalloon.hide(1);
    pickUpFrom(i);
    if (handKind == 1) {
        setMainState(4);
    }
    getDragPos();
    Shared_Inventory_PlayPickUpSe();
}

void PostOfficeMenu::pickUpAtSlot(u32 i) {
    heldSlot = i;
    nameBalloon.hide(1);
    pickUpFrom(i);
    if (handKind == 1) {
        returnState = 8;
    }
    getHandPos();
    Shared_Inventory_PlayPickUpSe();
}

void PostOfficeMenu::flyHeldTo(u32 i, u32 a) {
    heldSlot = i;
    flyMotion.setPos(handX, handY);
    s32 x = getSlotX(i);
    s32 y = getSlotY(i);
    flyMotion.startLinear(x, y, a);
    flyMotion.update();
    getFlyPos();
    setMainState(0x15);
}

void PostOfficeMenu::flyHeldToOtherList(u32 i, s32 a) {
    u32 r = 0x21;
    if (a >= 0xc0) {
        if (isBoxSlot(i)) {
            r = findFreePocketSlot();
        }
    } else {
        if (isLetterSlot(i)) {
            r = findFreeBoxSlot();
        }
    }
    if (r != 0x21) {
        i = r;
    }
    flyHeldTo(i, 4);
}

void PostOfficeMenu::pickUpAndFlyTo(u32 i, u32 a) {
    pickUpFrom(i);
    handX = getSlotX(i);
    handY = getSlotY(i);
    flyHeldTo(a, 4);
}

u8 PostOfficeMenu::findFreePocketSlot() {
    s32 r = Inventory_FindEmptyLetter();
    if (r == -1) {
        return 0x21;
    }
    return r + 0xb;
}

u8 PostOfficeMenu::findFreeBoxSlot() {
    Letter *p = boxLetters;
    s32 i;
    for (i = 0; i < 10; p++, i++) {
        if (((LetterView *)p)->getState() == 0) {
            return i + 0x15;
        }
    }
    return 0x21;
}

void PostOfficeMenu::cancelBgTasks() {
    bgTasks->cancel();
}

BOOL PostOfficeMenu::isLetterSlot(u32 i) {
    if (i >= 0xb && i <= 0x14) {
        return TRUE;
    }
    return FALSE;
}

BOOL PostOfficeMenu::isBoxSlot(u32 i) {
    if (i >= 0x15 && i <= 0x1e) {
        return TRUE;
    }
    return FALSE;
}

BOOL PostOfficeMenu::isButtonSlot(u32 i) {
    if ((u8)(i + 0xe1) <= 1) {
        return TRUE;
    }
    return FALSE;
}

u8 PostOfficeMenu::toLetterGridIndex(u32 i) {
    if (i >= 0xb && i <= 0x14) {
        return i - 0xb;
    }
    if (i >= 0x15 && i <= 0x1e) {
        return i + 0x18;
    }
    return 0;
}

u8 PostOfficeMenu::fromLetterGridIndex(u32 i) {
    if (i <= 9) {
        return i + 0xb;
    }
    if (i >= 0x2d && i <= 0x36) {
        return i - 0x18;
    }
    return 0x21;
}

u8 PostOfficeMenu::getSlotAt(u32 i, s32 a, u32 flag) {
    u32 r = letterGrid.findPocketLetterAt(i, a);
    if (r == 0x37) {
        r = letterGrid.findLetterAt2D(i, a);
    }
    if (r != 0x37) {
        if (flag != 0) {
            if (LetterGrid_IsSlotEmpty(&letterGrid, r) != 0) {
                return 0x21;
            }
        }
        return fromLetterGridIndex(r);
    }
    return 0x21;
}

BOOL PostOfficeMenu::dropHeldOnSlot(u32 i) {
    if (isSlotEmpty(i) == 0) {
        Letter_Copy((LetterView *)&swapLetter, (const LetterView *)getSlotLetter(i));
        putLetterInSlot(heldSlot, &swapLetter);
    }
    releaseHeldTo(i);
    return TRUE;
}

void PostOfficeMenu::putLetterInSlot(u32 i, void *p) {
    if (isLetterSlot(i) || isBoxSlot(i)) {
        letterGrid.setLetter(toLetterGridIndex(i), p);
    }
}

void * PostOfficeMenu::getSlotLetter(u32 i) {
    if (isLetterSlot(i) || isBoxSlot(i)) {
        return letterGrid.getLetter(toLetterGridIndex(i));
    } else {
        return 0;
    }
}

s32 PostOfficeMenu::getSlotX(u32 i) {
    if (isLetterSlot(i) || isBoxSlot(i)) {
        return LetterGrid_GetSlotX(&letterGrid, toLetterGridIndex(i));
    } else {
        if (i == 0x1f) {
            return 0xbc;
        }
        if (i == 0x20) {
            return 0x74;
        }
        return 0;
    }
}

s32 PostOfficeMenu::getSlotY(u32 i) {
    if (isLetterSlot(i) || isBoxSlot(i)) {
        return Shared_LetterGrid_GetSlotY(&letterGrid, toLetterGridIndex(i)) - 0x10;
    } else {
        if ((u8)(i + 0xe1) <= 1) {
            return 0xb6;
        }
        return 0;
    }
}

void PostOfficeMenu::disableAllPockets() {
    Shared_InventoryItemGrid_DisableSlotRange(&pocketGrid, 0, 0xe);
    letterGrid.highlightLetterKinds(0xe);
}

BOOL PostOfficeMenu::isSlotDisabled(u32 i) {
    if (isLetterSlot(i)) {
        return letterGrid.isHighlighted(toLetterGridIndex(i));
    } else {
        return FALSE;
    }
}

BOOL PostOfficeMenu::isSlotEmpty(u32 i) {
    if (isLetterSlot(i) || isBoxSlot(i)) {
        return LetterGrid_IsSlotEmpty(&letterGrid, toLetterGridIndex(i));
    } else {
        return TRUE;
    }
}

void PostOfficeMenu::clearFocusSlot() {
    InventoryItemGrid_ClearCursorSlot(&pocketGrid);
    letterGrid.clearCursorSlot();
}

void PostOfficeMenu::setFocusSlot(u32 i) {
    if (isLetterSlot(i) || isBoxSlot(i)) {
        letterGrid.setCursorSlot(toLetterGridIndex(i));
        InventoryItemGrid_ClearCursorSlot(&pocketGrid);
    } else {
        clearFocusSlot();
    }
}

void PostOfficeMenu::clearHoverSlot() {
    Shared_InventoryItemGrid_ClearMarks(&pocketGrid);
    letterGrid.clearMarks();
}

void PostOfficeMenu::setHoverSlot(u32 i) {
    if (isLetterSlot(i) || isBoxSlot(i)) {
        letterGrid.markSlot(toLetterGridIndex(i));
    }
}

BOOL PostOfficeMenu::hasTouchMoved() {
    s32 d = gTouchPressX - gTouchCurX;
    if (d < 0) d = -d;
    if (d > 8) return TRUE;
    d = gTouchPressY - gTouchCurY;
    if (d < 0) d = -d;
    if (d > 8) return TRUE;
    return FALSE;
}

void PostOfficeMenu::placeBalloon() {
    s32 x = getSlotX(balloonSlot) - 0x6d;
    s32 y = getSlotY(balloonSlot) - 0x78;
    if (MenuCtrl_IsButtons()) {
        y -= 8;
    }
    nameBalloon.setPos(x, y);
    if (isLetterSlot(balloonSlot) || isBoxSlot(balloonSlot)) {
        letterGrid.showLetterName(&nameBalloon, toLetterGridIndex(balloonSlot));
    }
}

void PostOfficeMenu::updateBalloonForCursor() {
    if (isLetterSlot(cursorSlot) || isBoxSlot(cursorSlot)) {
        if (isSlotEmpty(cursorSlot)) {
            nameBalloon.cancelQueuedOpen();
        } else {
            balloonSlot = cursorSlot;
            nameBalloon.queueOpen();
        }
    } else {
        nameBalloon.cancelQueuedOpen();
    }
}

void PostOfficeMenu::drawHeldItem() {
    if (testFlags(0x40) == 0) {
        if (handKind != 0) {
            if (handKind == 1) {
                letterGrid.drawHeldLetter(handX, handY, &heldLetter);
            }
        }
    }
}

void PostOfficeMenu::getDragPos() {
    handX = dragOffsetX + gTouchCurX;
    handY = dragOffsetY + gTouchCurY;
}

void PostOfficeMenu::getHandPos() {
    handX = cursor.getFrameScreenX() - 2;
    handY = cursor.getFrameScreenY() - 4;
}

void PostOfficeMenu::getFlyPos() {
    handX = flyMotion.getX();
    handY = flyMotion.getY();
}

void PostOfficeMenu::pickUpFrom(u32 i) {
    if (isLetterSlot(i) || isBoxSlot(i)) {
        u32 t = toLetterGridIndex(i);
        handKind = 1;
        Letter_Copy((LetterView *)&heldLetter, (const LetterView *)letterGrid.getLetter(t));
        letterGrid.clearLetter(t);
    }
}

void PostOfficeMenu::releaseHeldTo(u32 i) {
    if (handKind == 1) {
        putLetterInSlot(i, &heldLetter);
    }
    handKind = 0;
}

void PostOfficeMenu::exchangeHeldWith(u32 i) {
    if (handKind == 1) {
        Letter_Copy((LetterView *)&swapLetter, (const LetterView *)&heldLetter);
        pickUpFrom(i);
        putLetterInSlot(i, &swapLetter);
    }
}

void PostOfficeMenu_ShowCursor(S *s) {
    s32 r4 = PostOfficeMenu_GetCursorTargetX(s);
    s->cursor.warpTo(r4, PostOfficeMenu_GetCursorTargetY(s));
    if (s->isButtonSlot(s->cursorSlot)) {
        s->cursor.setAnimIfChanged(7);
    } else {
        s->cursor.setAnimIfChanged(1);
    }
    PostOfficeMenu_RefreshCursor(s);
}

s32 PostOfficeMenu_GetCursorTargetX(S *s) {
    s32 r4 = s->getSlotX(s->cursorSlot);
    if (s->testFlags(0x20)) {
        r4 += 0x100;
    } else if (s->testFlags(0x10)) {
        r4 -= 0x100;
    }
    r4 += 8;
    return r4;
}

s32 PostOfficeMenu_GetCursorTargetY(S *s) {
    return s->getSlotY(s->cursorSlot);
}

void PostOfficeMenu_HideCursor(S *s) {
    s->cursor.setAnimIfChanged(0);
    s->cursor.update();
}

void PostOfficeMenu_MoveCursorToTarget(S *s) {
    s32 r5;
    if (s->testFlags(8)) {
        r5 = PostOfficeMenu_GetCursorTargetX(s);
        s->cursor.warpTo(r5, PostOfficeMenu_GetCursorTargetY(s));
        s->clearFlags(8);
    } else {
        r5 = PostOfficeMenu_GetCursorTargetX(s);
        s->cursor.moveToEase(r5, PostOfficeMenu_GetCursorTargetY(s), 3, 1);
        s->returnState = s->mainState;
        s->setMainState(0xd);
    }
}

void PostOfficeMenu_MoveCursorToPopupRow(S *s) {
    s32 r4 = ((PopupChoiceMenuBody *)&s->popup)->getRowX();
    s->cursor.moveToLinear(r4, ((PopupChoiceMenuBody *)&s->popup)->getRowY(s->popupRow), 2);
    s->returnState = s->mainState;
    s->setMainState(0xd);
}

void PostOfficeMenu_CancelPopup(S *s) {
    s32 r4;
    s->popupChoice = 4;
    s->popupRow = PopupChoice_DecideCancel(&s->popup, 1);
    r4 = ((PopupChoiceMenuBody *)&s->popup)->getRowX();
    s->cursor.warpTo(r4, ((PopupChoiceMenuBody *)&s->popup)->getRowY(s->popupRow));
    s->cursor.setAnimAtEnd(8);
    s->setMainState(0x17);
}

void PostOfficeMenu_CursorToPopupTop(S *s) {
    s32 r4;
    if (s->testFlags(0x8000)) {
        s->popupRow = 1;
    } else {
        s->popupRow = 0;
    }
    r4 = ((PopupChoiceMenuBody *)&s->popup)->getRowX();
    s->cursor.warpTo(r4, ((PopupChoiceMenuBody *)&s->popup)->getRowY(s->popupRow));
    s->cursor.setAnimIfChanged(7);
}

void PostOfficeMenu_ShowCursorAtSlot(S *s) {
    s32 r4 = PostOfficeMenu_GetCursorTargetX(s);
    s->cursor.warpTo(r4, PostOfficeMenu_GetCursorTargetY(s));
    s->cursor.setAnimIfChanged(1);
}

void PostOfficeMenu_RefreshCursor(S *s) {
    s->cursor.setPoseIdle();
    s->cursor.update();
}

void PostOfficeMenu_PressButton(S *s) {
    s->cursor.setPosePress();
    s->setMainState(0xe);
}

void PostOfficeMenu_BeginMoveFromPopup(S *s) {
    s->cursor.setAnimIfChanged(4);
    s->setMainState(0x10);
}

void PostOfficeMenu_BeginPutDownAt(S *s, u32 a) {
    s->nameBalloon.hide(1);
    s->targetSlot = a;
    s->cursor.setAnimIfChanged(5);
    s->setMainState(0x12);
}

void PostOfficeMenu_BeginSwapAt(S *s, u32 a) {
    s->nameBalloon.hide(1);
    s->returnState = s->mainState;
    s->targetSlot = a;
    s->cursor.setAnimIfChanged(6);
    s->setMainState(0x13);
}

void PostOfficeMenu_OnPopupChoice(S *s) {
    switch (s->popupChoice) {
    case 0: PostOfficeMenu_BeginMoveFromPopup(s); break;
    case 1: PostOfficeMenu_StartReadLetter(s); break;
    case 2: PostOfficeMenu_StartDiscardLetter(s); break;
    case 3: PostOfficeMenu_OnChoiceDiscard(s); break;
    case 4:
    default: s->resumeInput(); break;
    }
}

void PostOfficeMenu_OpenPopup(S *s, s32 a) {
    s32 r6, r2;
    ((PopupChoiceMenuBody *)&s->popup)->setRowsFromIds(&s->choiceList, s->testFlags(0x8000));
    r6 = s->getSlotX(s->selectedSlot);
    r2 = s->getSlotY(s->selectedSlot);
    if (a != 0) {
        s->popup.placeAboveBalloon((LabelBalloon *)(&s->nameBalloon));
    } else {
        s->popup.placeNearPoint(r6, r2);
    }
    PopupChoice_Open(&s->popup, 0);
    s->setMainState(0x16);
}

void PostOfficeMenu_CancelPopupForButtons(S *s) {
    s->popupChoice = 4;
    PostOfficeMenu_ShowCursorAtSlot(s);
    PopupChoice_Close(&s->popup, 0);
    s->setMainState(0x18);
}

void PostOfficeMenu_SelectLetter(S *s, u32 a, s32 b) {
    void *r7;
    s32 r5;
    s->clearFlags(0x8000);
    s->selectedSlot = a;
    ChoiceIdList_Clear((u8 *)&s->choiceList, 4);
    r7 = s->getSlotLetter(a);
    if (MenuCtrl_IsButtons()) {
        ChoiceIdList_Add((u8 *)&s->choiceList, 0, 0);
    }
    r5 = ((LetterView *)r7)->getState();
    if (r5 != 0) {
        if (r5 == 7) {
            ChoiceIdList_Add((u8 *)&s->choiceList, 0x17, 1);
        } else {
            ChoiceIdList_Add((u8 *)&s->choiceList, 0x14, 1);
        }
    }
    if (((LetterView *)r7)->getPresent() == 0xfff1) {
        if (r5 == 3 || r5 == 6 || r5 == 1 || r5 == 4) {
            ChoiceIdList_Add((u8 *)&s->choiceList, 0x15, 3);
        }
    }
    ChoiceIdList_Add((u8 *)&s->choiceList, 2, 4);
    PostOfficeMenu_HideCursor(s);
    if (b == 0) {
        s->nameBalloon.hide(1);
    }
    PostOfficeMenu_OpenPopup(s, b);
}

void PostOfficeMenu_OpenDiscardConfirm(S *s) {
    s->setFlags(0x8000);
    ChoiceIdList_Clear((u8 *)&s->choiceList, 4);
    ChoiceIdList_Add((u8 *)&s->choiceList, 0x1a, 4);
    ChoiceIdList_Add((u8 *)&s->choiceList, 0x15, 2);
    ChoiceIdList_Add((u8 *)&s->choiceList, 0x19, 4);
    PostOfficeMenu_OpenPopup(s, 0);
}

void PostOfficeMenu_MoveCursorInPocketLetters(S *s, s32 a, s32 b) {
    s32 r4 = s->cursorSlot - 0xb;
    s32 r6 = r4 >> 1;
    if (MenuKeys_HasLeft(a)) {
        if ((r4 & 1) > 0) {
            s->cursorSlot = s->cursorSlot - 1;
        } else {
            s->cursorSlot = r6 * 2 + 0x16;
            return;
        }
    } else if (MenuKeys_HasRight(a)) {
        if ((r4 & 1) < 1) s->cursorSlot = s->cursorSlot + 1;
    }
    if (s->isLetterSlot(s->cursorSlot)) {
        if (s->testFlags(0x30) == 0) {
            if (MenuKeys_HasUp(a)) {
                if (r6 > 0) s->cursorSlot = s->cursorSlot - 2;
            } else if (MenuKeys_HasDown(a)) {
                if (r6 < 4) {
                    s->cursorSlot = s->cursorSlot + 2;
                } else if (b == 0) {
                    s->cursorSlot = 0x1f;
                    s->cursor.switchToAnim07();
                }
            }
        }
    }
}

void PostOfficeMenu_MoveCursorInBox(S *s, s32 a, s32 b) {
    s32 r4 = s->cursorSlot - 0x15;
    s32 r6 = 0;
    while (r4 >= 2) {
        r6++;
        r4 -= 2;
    }
    if (MenuKeys_HasLeft(a)) {
        if (r4 > 0) s->cursorSlot = s->cursorSlot - 1;
    } else if (MenuKeys_HasRight(a)) {
        if (r4 < 1) {
            s->cursorSlot = s->cursorSlot + 1;
        } else {
            s->cursorSlot = r6 * 2 + 0xb;
            return;
        }
    }
    if (s->isBoxSlot(s->cursorSlot)) {
        if (s->testFlags(0x30) == 0) {
            if (MenuKeys_HasUp(a)) {
                if (r6 > 0) s->cursorSlot = s->cursorSlot - 2;
            } else if (MenuKeys_HasDown(a)) {
                if (r6 < 4) {
                    s->cursorSlot = s->cursorSlot + 2;
                } else if (b == 0) {
                    s->cursorSlot = 0x20;
                    s->cursor.switchToAnim07();
                }
            }
        }
    }
}

void PostOfficeMenu_MoveCursorOnButtons(S *s, s32 a) {
    if (MenuKeys_HasLeft(a)) {
        s->cursorSlot = 0x20;
    } else if (MenuKeys_HasRight(a)) {
        s->cursorSlot = 0x1f;
    }
    if (MenuKeys_HasUp(a)) {
        s->cursor.switchToAnim01();
        if (s->cursorSlot == 0x20) {
            s->cursorSlot = 0x1d;
        } else {
            s->cursorSlot = 0x13;
        }
    }
}

BOOL PostOfficeMenu_MoveCursorByPad(S *s, s32 a, s32 b) {
    u32 old = s->cursorSlot;
    s->clearFlags(0x30);
    if (a == 0) return FALSE;
    if (s->isLetterSlot(s->cursorSlot)) {
        PostOfficeMenu_MoveCursorInPocketLetters(s, a, b);
    } else if (s->isBoxSlot(s->cursorSlot)) {
        PostOfficeMenu_MoveCursorInBox(s, a, b);
    } else if (s->isButtonSlot(s->cursorSlot)) {
        PostOfficeMenu_MoveCursorOnButtons(s, a);
    }
    if (old != s->cursorSlot) return TRUE;
    return FALSE;
}

void PostOfficeMenu_StartReadLetter(S *s) {
    s->setTransitionState(4);
    s->setPhase(1);
    s->setFlags(0x100);
}

void PostOfficeMenu_CloseLetterView(S *s) {
    s->setMainState(0x1a);
    s->letterCloseButton.setState(2);
    Snd_PlaySe(0x29);
}

void PostOfficeMenu_StartDiscardLetter(S *s) {
    u32 t = s->selectedSlot;
    s->pickUpFrom(t);
    s->handX = s->getSlotX(t);
    s->handY = s->getSlotY(t);
    if (MenuCtrl_IsButtons()) {
        s->handX = s->handX - 2;
        s->handY = s->handY - 2;
    }
    s->setMainState(0x1c);
    LetterGrid_StartPopAnim(&s->letterGrid);
}

void PostOfficeMenu_OnChoiceDiscard(S *s) {
    PostOfficeMenu_OpenDiscardConfirm(s);
}

void PostOfficeMenu_BackupPocketLetters(S *s) {
    u8 id;
    s32 i = 0;
    for (id = 0xb; id <= 0x14; i++, id++) {
        Letter_Copy((LetterView *)&s->pocketLettersBackup[i], (const LetterView *)s->getSlotLetter(id));
    }
}

void PostOfficeMenu_RestorePocketLetters(S *s) {
    u8 id;
    s32 i = 0;
    for (id = 0xb; id <= 0x14; i++, id++) {
        s->putLetterInSlot(id, &s->pocketLettersBackup[i]);
    }
}

void PostOfficeMenu::returnUnsentLetters(s32 flag) {
    s32 i;
    Letter *e = boxLetters;
    for (i = 0; i < 10; e++, i++) {
        if (flag != 0 && (sentLetterMask & (1 << i))) {
            Letter_Clear((LetterView *)e);
        } else if (((LetterView *)e)->getState() != 0) {
            s32 r = findFreePocketSlot();
            if (r != 0x21) {
                putLetterInSlot(r, e);
            }
        }
    }
}

void PostOfficeMenu::pressSendButton() {
    Snd_PlaySe(0x27);
    clearFlags(0x400);
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(9);
    setMainState(0x1b);
    transitionState = 4;
    clearFlags(0x100);
    if (gCommManager->isOnline()) {
        beginOnlineSend();
    }
}

void PostOfficeMenu::pressCancelButton() {
    Snd_PlaySe(0x28);
    setFlags(0x400);
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(7);
    setMainState(0x1b);
    transitionState = 4;
    clearFlags(0x100);
}

BOOL PostOfficeMenu::hasFutureLetter(Letter *p) {
    Letter *q = p;
    s32 i;
    for (i = 0; i < 10; q++, i++) {
        if (((LetterView *)q)->getState() == 1 && ((LetterView *)q)->isToFutureSelf() != 0) {
            return TRUE;
        }
    }
    return FALSE;
}

u32 PostOfficeMenu::takeFutureLetter(Letter *p) {
    u16 r = 0;
    s32 t = -1;
    Letter *q = p;
    s32 i;
    for (i = 0; i < 10; q++, i++) {
        if (((LetterView *)q)->getState() == 1 && ((LetterView *)q)->isToFutureSelf() != 0) {
            if (t == -1) {
                t = i;
            } else {
                t = -2;
            }
        }
    }
    if (t != -1) {
        if (t == -2) {
            r |= 2;
        } else {
            r |= 1;
            Letter *e = &p[t];
            MenuCtrl_SetFutureLetter(e);
            Letter_Clear((LetterView *)e);
        }
    }
    return r;
}

u32 PostOfficeMenu::checkSendLetters(Letter *p, s32 flag) {
    if (LetterList_CountUsed(p, 10) == 0) {
        return 0;
    }
    u16 r = 0;
    Letter *q = p;
    s32 i;
    for (i = 0; i < 10; q++, i++) {
        if (((LetterView *)q)->getState() != 0) {
            if (((LetterView *)q)->getState() != 1) {
                if (flag != 0) {
                    sentLetterMask |= 1 << i;
                } else {
                    Letter_Clear((LetterView *)q);
                }
            } else if (((LetterView *)q)->isToFutureSelf() == 0) {
                if (LetterDelivery_HasKnownAddressee(q) != 0) {
                    if (queueLetterForDelivery(q) != 0) {
                        if (flag != 0) {
                            sentLetterMask |= 1 << i;
                        } else {
                            Letter_Clear((LetterView *)q);
                        }
                        r |= 0x300;
                    } else {
                        r |= 0x110;
                    }
                } else {
                    r |= 0x108;
                }
            }
        }
    }
    return r;
}

u32 PostOfficeMenu::queueLetters(Letter *p) {
    u16 r = 0;
    s32 n = LetterList_Compact(p, 10);
    if (n == 0) {
        return 0;
    }
    Letter *q = p;
    s32 i;
    for (i = 0; i < n; q++, i++) {
        if (((LetterView *)q)->getState() != 1) {
            Letter_Clear((LetterView *)q);
        } else if (((LetterView *)q)->isToFutureSelf() == 0) {
            if (LetterDelivery_HasKnownAddressee(q) != 0) {
                if (queueLetterForDelivery(q) != 0) {
                    Letter_Clear((LetterView *)q);
                    r |= 0x200;
                } else {
                    r |= 0x20;
                }
            }
        }
    }
    return r;
}

s32 PostOfficeMenu::queueLetterForDelivery(Letter *p) {
    return LetterDelivery_QueueOutgoing(p, 1);
}

u32 PostOfficeMenu::deliverToMailboxes(Letter *p) {
    u16 r = 0;
    s32 n = LetterList_Compact(p, 10);
    if (n == 0) {
        return r;
    }
    s32 t;
    u32 mask = 0;
    Letter *q = p;
    s32 cnt = 0;
    s32 i = 0;
    TalkWindowState *obj;
    s32 z;
    s32 j;
    for (; i < n; q++, i++) {
        if (((LetterView *)q)->isToFutureSelf() == 0) {
            t = LetterDelivery_FindAddresseePlayer(q);
            if (t != -2) {
                if (t != -1) {
                    if (LetterDelivery_PutInMailbox(q, t, 1) != 0) {
                        Letter_Clear((LetterView *)q);
                        r |= 0x200;
                    } else {
                        u32 bit = 1 << t;
                        if ((mask & bit) == 0) {
                            mask |= bit;
                            cnt++;
                        }
                    }
                } else {
                    if (LetterDelivery_FindAddresseeVillager(q) >= 0) {
                        LetterDelivery_SendToVillager(q);
                        Letter_Clear((LetterView *)q);
                        r |= 0x200;
                    }
                }
            }
        }
    }
    if (cnt != 0) {
        z = 0;
        obj = TalkWindow_Get(0);
        MsgString9B buf;
        for (j = 0; j < 4; j++) {
            if (mask & (1 << j)) {
                ((PlayerId *)((PlayerData *)PlayerData_GetResident(gSavePlayers, j))->getPlayerId())->getNameString(&buf);
                switch (z) {
                case 0:
                    obj->setSlot(7, &buf);
                    break;
                case 1:
                    obj->setSlot(8, &buf);
                    break;
                case 2:
                    obj->setSlot(9, &buf);
                    break;
                }
                z++;
            }
        }
        r |= cnt << 6;
    }
    return r;
}

u32 PostOfficeMenu::deliverVillagerLettersNow(Letter *p) {
    u16 r = 0;
    s32 n = LetterList_Compact(p, 10);
    if (n == 0) {
        return 0;
    }
    Letter *q = p;
    s32 i;
    for (i = 0; i < n; q++, i++) {
        if (LetterDelivery_FindAddresseeVillager(q) >= 0) {
            LetterDelivery_SendToVillager(q);
            Letter_Clear((LetterView *)q);
            r |= 0x200;
        }
    }
    return r;
}

void PostOfficeMenu::beginOnlineSend() {
    CommManager *g = gCommManager;
    if (g->isOnline()) {
        setFlags(0x800);
        sentLetterMask = 0;
        s32 n = LetterList_CountUsed(boxLetters, 10);
        onlineSendResult = 0;
        if (n <= 0) {
            onlineSendResult = 4;
            clearFlags(0x1000);
            return;
        }
        if (hasFutureLetter(boxLetters)) {
            onlineSendResult |= 0x800;
        }
        if (g->myAid != 0) {
            setFlags(0x1000);
            sendIndex = 0;
            clearFlags(0x2000);
            updateOnlineSend();
        } else {
            setFlags(0x4000);
            u32 r = checkSendLetters(boxLetters, 1);
            onlineSendResult |= r;
            if (onlineSendResult & 0x10) {
                onlineSendResult |= 0x400;
            }
        }
    }
}

void PostOfficeMenu::updateOnlineSend() {
    if (testFlags(0x800) == 0) {
        clearFlags(0x1000);
        return;
    }
    if (testFlags(0x1000) == 0) {
        return;
    }
    s32 r6 = 0x18;
    if (testFlags(0x2000) != 0) {
        r6 = CommSub_GetPostReply();
        switch (r6 - 8) {
        case 0:
            return;
        case 3:
            onlineSendResult |= 0x400;
            clearFlags(0x1000);
            clearFlags(0x2000);
            return;
        case 1:
        case 2:
            onlineSendResult |= 0x200;
            sentLetterMask |= 1 << sendIndex;
            sendIndex++;
            clearFlags(0x2000);
            break;
        }
    }
    while (sendIndex < 10) {
        Letter *e = &boxLetters[sendIndex];
        if (((LetterView *)e)->isToFutureSelf() == 0) {
            if (((LetterView *)e)->getState() == 1) {
                onlineSendResult |= 0x100;
                if (LetterDelivery_HasKnownAddressee(e) != 0) {
                    if (r6 == 10) {
                        onlineSendResult |= 0x400;
                        clearFlags(0x1000);
                        return;
                    }
                    if (sendLetterRecord(e) != 0) {
                        setFlags(0x2000);
                        return;
                    }
                } else {
                    onlineSendResult |= 8;
                }
            }
        }
        sendIndex++;
    }
    clearFlags(0x1000);
}

BOOL PostOfficeMenu::sendLetterRecord(Letter *p) {
    Heap *heap = gMenuHeap;
    u8 *buf = (u8 *)Heap_AllocTail(heap, 0xf5);
    buf[0] = 8;
    MI_CpuCopy8(p, buf + 1, 0xf4);
    CommManager *g = gCommManager;
    g->beginRecord();
    g->writeRecord(buf, 0xf5);
    g->endRecord(0x16, 0);
    Heap_Free(heap, buf);
    CommSub_SetPostReply(8);
    return TRUE;
}

BOOL PostOfficeMenu::testFlags(u32 mask) {
    if (stateFlags & mask) {
        return TRUE;
    }
    return FALSE;
}

void PostOfficeMenu::setFlags(u32 mask) { stateFlags = stateFlags | mask; }

void PostOfficeMenu::clearFlags(u32 mask) { stateFlags = stateFlags & ~mask; }

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov104_02294c40) {
    HOST_OVERLAY_VAR(sPostOfficeMenuProfile),
    HOST_OVERLAY_VARS_END
};
