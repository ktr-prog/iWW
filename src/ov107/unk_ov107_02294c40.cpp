#include "types.h"
#include "host_shared_calls.h"
#include "Unk_020d8c7c.h"
#include "net/CommManager.h"
#include "ui/CursorMotion.h"
#include "menu/InventoryItemGrid.h"
#include "menu/LetterGrid.h"
#include "menu/InventoryBg.h"
#include "menu/MenuProc.h"
#include "gfx/BgVramTask.h"
#include "ui/TouchPromptBalloon.h"
#include "menu/MenuCursor.h"
#include "menu/MenuBottomButtons.h"
#include "menu/PopupChoiceMenu.h"
#include "menu/MenuErrorMessage.h"
#include "sys/ProcProfile.h"
#include "menu/MenuLauncher.h"
#include "ui/HandCursor.h"
#include "ui/LabelBalloon.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0203c23c.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov002/unk_ov002_022013ac.h"
#include "proto/ov002/unk_ov002_02202fac.h"
#include "proto/ov003/unk_ov003_0221ffb8.h"
#include "proto/ov003/unk_ov003_02204ce8.h"
#include "proto/ov003/unk_ov003_02225800.h"
#include "proto/ov094/unk_ov094_02292360.h"
#include "proto/ov094/unk_ov094_02292da8.h"
#include "proto/ov094/unk_ov094_02293b90.h"
#include "proto/ov107/unk_ov107_02294c40.h"
#include "player/PlayerData.h"
#include "actor/Actor.h"
#include "proto/main/unk_0204cc1c.h"


class PocketsFullMenu;
typedef void (PocketsFullMenu::*Unk_ov107_02296e78_Fn)();














extern "C" {
extern CommManager *gCommManager;
extern u8 gU8None;
extern u16 gPad[];

s32 PendingUnit_ClearActiveOfAid(u32 aid);
void MI_CpuCopy8(void *a, void *b, u32 n);
s32 FieldAction_PollResult(s32 v);
s32 FieldAction_PollDrop(s32 v);
void FieldAction_Release(s32 v);
s32 FieldAction_RequestPlaceAtPending(s32 a, s32 b);
s32 FieldAction_RequestDropOrPlace(s32 a, s32 b);
s32 FieldAction_RequestToolAtPending(s32 a, s32 b, s32 c, s32 d);
u16 *PendingUnit_GetActivePosOfAid(s32 a);
BOOL Ground_FindWaterAhead(VecFx32 *out, VecFx32 *pos, s32 dir, u32 dist, u32 s5, s32 s6);
void Item_FromPlacedForm(void *a, void *b);

u8 PopupChoice_DecideCancel(void *a, s32 b);
BOOL PopupChoice_MoveCursor(void *p, s32 a, void *q, s32 b);
BOOL PopupChoice_TickDecideDelay(void *p);
void PopupChoice_DecideRow(void *p, s32 a, s32 b);
void PopupChoice_ForceClose(void *p);
void PopupChoice_Draw(void *p);
void PopupChoice_Update(void *p);
void PopupChoice_Close(void *p, s32 x);
void PopupChoice_Open(void *a, s32 b);

s32 PlayerActor_LocalRequestBuryItem(VecFx32 *p, u16 *b);
BOOL FishCatch_EndForShadow(void *o);


}

static inline BOOL Unk_ov107_02296270_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        return TRUE;
    }
    return FALSE;
}

class PocketsFullMenu : public MenuProc {
public:
    PocketsFullMenu()
        : buryUnitX(0), buryUnitZ(0), bgTasks(), pocketGrid(), letterGrid(), inventoryBg(), nameBalloon(), flyMotion(), cursor(), popup(), errorMessage(), bottomButtons() {}

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
    void endNewItemAction(BOOL flag);
    u8 getLocalPlayerIndex();
    void mainAct17();
    void mainAct16();
    void onChoiceBury();
    void sendFishReleasePacket(u8 v);
    void mainAct11();
    void onChoiceReleaseFish();
    BOOL canReleaseFish();
    void sendInsectReleasePacket(u8 a, u8 b);
    void mainAct10();
    void onChoiceReleaseInsect();
    void mainAct15();
    void onChoiceDrop();
    BOOL moveCursorByPad(u32 pad);
    void moveCursorInGrid(u32 pad);
    void selectPocket(u32 idx, u32 flag);
    void setPopupChoices();
    void storeNewItem();
    void startCloseByTab();
    void closeWithSelection();
    void cancelPopupForButtons();
    void openPopup(s32 a);
    void onPopupChoice();
    void pressCloseButton();
    void refreshCursor();
    void showCursorAtSlot();
    void cursorToPopupTop();
    void cancelPopup();
    void moveCursorToPopupRow();
    void moveCursorToTarget();
    void hideCursor();
    s32 getCursorTargetY();
    s32 getCursorTargetX();
    void showCursor();
    void drawHeldItem();
    void updateBalloonForCursor();
    void placeBalloon();
    void setFocusSlot(s32 a);
    void clearFocusSlot();
    u32 getSlotItemFlags(s32 a);
    u32 getSlotItem(s32 a);
    BOOL isSlotEmpty(s32 a);
    BOOL isSlotDisabled(s32 a);
    BOOL isPocketLocked(s32 a);
    void disableLockedPockets();
    s32 getSlotY(s32 a);
    s32 getSlotX(s32 a);
    void putItemInSlot(s32 a, s32 b, s32 c);
    u32 getSlotAt(s32 a, s32 b, s32 c);
    u32 toSlotOrNone(s32 a);
    u32 toPocketIndex(s32 a);
    BOOL isPocketSlot(s32 a);
    void cancelBgTasks();
    void showMessage(s32 a, u32 b);
    void beginTouchOnSlot(u32 a);
    void resumeInput();
    void startButtonInput();
    void startTouchInput();
    void mainAct14();
    void mainAct13();
    void mainAct12();
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
    void loadInventoryBg();
    void setupBgLayer6();
    void postStateUpdate();
    void preStateUpdate();
    void postInputUpdate();
    void preInputUpdate();
    void releaseResources();
    void initParts();
    void transitionAct04();
    void transitionAct03();
    void transitionAct02();
    void transitionAct01();
    void transitionAct00();
    void runMainState();

    /* 0x94 */ u32 stateFlags;
    /* 0x98 */ s32 slideY;
    /* 0x9c */ s32 dragOffsetX;
    /* 0xa0 */ s32 dragOffsetY;
    /* 0xa4 */ s32 handX;
    /* 0xa8 */ s32 handY;
    /* 0xac */ s32 fieldRequest;
    /* 0xb0 */ s32 unk_b0;
    /* 0xb4 */ u8 unk_b4;
    /* 0xb5 */ u8 handKind;
    /* 0xb6 */ u8 touchedSlot;
    /* 0xb7 */ u8 balloonSlot;
    /* 0xb8 */ u8 cursorSlot;
    /* 0xb9 */ u8 selectedSlot;
    /* 0xba */ u8 unk_ba;
    /* 0xbb */ u8 returnState;
    /* 0xbc */ u8 popupChoice;
    /* 0xbd */ u8 popupRow;
    /* 0xbe */ u8 waitTimer;
    /* 0xbf */ u8 touchHoldDelay;
    /* 0xc0 */ VecFx32 releasePos;
    /* 0xcc */ s32 buryUnitX;
    /* 0xd0 */ s32 buryUnitZ;
    /* 0xd4 */ BgVramTaskPair bgTasks[1];
    /* 0x10c */ InventoryItemGrid pocketGrid;
    /* 0xb6c */ LetterGrid letterGrid;
    /* 0xb94 */ InventoryBg inventoryBg;
    /* 0x2174 */ TouchPromptBalloon nameBalloon;
    /* 0x2234 */ CursorMotion flyMotion;
    /* 0x224c */ MenuCursorBuf0 cursor;
    /* 0x22b0 */ PopupChoiceMenu popup;
    /* 0x25a4 */ PopupChoiceIdList choiceList;
    /* 0x25af */ u8 pad_25af[1];
    /* 0x25b0 */ MenuErrorMessage errorMessage;
    /* 0x26b8 */ MenuBottomButtons bottomButtons;
};

static inline BOOL Unk_ov107_InRange(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) {
        r = TRUE;
    }
    return r;
}


extern "C" PocketsFullMenu *PocketsFullMenu_Create() { return new PocketsFullMenu(); }

BOOL PocketsFullMenu::onCreate() {
    initParts();
    setTransitionState(0);
    setPhase(0);
    return TRUE;
}

BOOL PocketsFullMenu::onDelete() {
    ((MenuLauncher *)(ProcBase_GetParent(this)))->onChildClosed();
    releaseResources();
    return TRUE;
}

BOOL PocketsFullMenu::onDraw() {
    PopupChoice_Draw(&popup);
    if (!testFlags(1)) {
        return TRUE;
    }
    nameBalloon.draw();
    if (MenuCtrl_IsButtons()) {
        ((MenuCursorBase *)(&cursor))->drawWrapped();
    }
    drawHeldItem();
    if (testFlags(2)) {
        ((MenuBottomButtons *)(&bottomButtons))->drawAt(slideY);
        s32 t = slideY - 0x10;
        InventoryItemGrid_DrawPockets(&pocketGrid, 0, t);
        ((LetterGrid *)(&letterGrid))->drawPocketLetters(0, t);
        Shared_InventoryBg_DrawSprite(&inventoryBg, t);
    }
    return TRUE;
}
extern "C" ProcProfile sPocketsFullMenuProfile;
extern "C" const s16 sFishReleaseProbeAngles[8];

extern "C" ProcProfile sPocketsFullMenuProfile = {(void *(*)())PocketsFullMenu_Create, 0x9a, 0x9e};

BOOL PocketsFullMenu::execTransition() {
    static Unk_ov107_02296e78_Fn tbl[5] = {
        &PocketsFullMenu::transitionAct00,
        &PocketsFullMenu::transitionAct01,
        &PocketsFullMenu::transitionAct02,
        &PocketsFullMenu::transitionAct03,
        &PocketsFullMenu::transitionAct04};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}

void PocketsFullMenu::runMainState() {
    static Unk_ov107_02296e78_Fn tbl[24] = {
        &PocketsFullMenu::mainAct00,
        &PocketsFullMenu::mainAct01,
        &PocketsFullMenu::mainAct02,
        &PocketsFullMenu::mainAct03,
        &PocketsFullMenu::mainAct04,
        &PocketsFullMenu::mainAct05,
        &PocketsFullMenu::mainAct06,
        &PocketsFullMenu::mainAct07,
        &PocketsFullMenu::mainAct08,
        &PocketsFullMenu::mainAct09,
        &PocketsFullMenu::mainAct0A,
        &PocketsFullMenu::mainAct0B,
        &PocketsFullMenu::mainAct0C,
        &PocketsFullMenu::mainAct0D,
        &PocketsFullMenu::mainAct0E,
        &PocketsFullMenu::mainAct0F,
        &PocketsFullMenu::mainAct10,
        &PocketsFullMenu::mainAct11,
        &PocketsFullMenu::mainAct12,
        &PocketsFullMenu::mainAct13,
        &PocketsFullMenu::mainAct14,
        &PocketsFullMenu::mainAct15,
        &PocketsFullMenu::mainAct16,
        &PocketsFullMenu::mainAct17};
    (this->*tbl[mainState])();
}

BOOL PocketsFullMenu::execMain() {
    preInputUpdate();
    runMainState();
    postInputUpdate();
    return TRUE;
}

BOOL PocketsFullMenu::execPhase3() { return TRUE; }

BOOL PocketsFullMenu::execPhase4() { return TRUE; }

BOOL PocketsFullMenu::execClosed() {
    ProcBase_RequestDelete(this);
    return TRUE;
}

void PocketsFullMenu::transitionAct00() {
    setupBgLayer6();
    loadInventoryBg();
    setTransitionState(1);
}

void PocketsFullMenu::transitionAct01() {
    loadObjGraphics();
    ((MenuBottomButtons *)(&bottomButtons))->setLayoutSingle05(0x65);
    Shared_InventoryItemGrid_LoadPockets(&pocketGrid);
    disableLockedPockets();
    Shared_LetterGrid_LoadPocketLetters(&letterGrid);
    ((LetterGrid *)(&letterGrid))->highlightLetterKinds(0xf);
    beginSubSlideIn(8, 0, 0, 0x30);
    Gfx2d_ShowLayer(6);
    applySlideOffset(6, 0, -16);
    setTransitionState(2);
    setFlags(1);
    setFlags(2);
    slideY = getSlideOffsetY();
}

void PocketsFullMenu::transitionAct02() {
    if (stepSlideIn(0)) {
        setPhase(2);
        resumeInput();
    }
    applySlideOffset(6, 0, -16);
    slideY = getSlideOffsetY();
}

void PocketsFullMenu::transitionAct03() {
    ((TouchPromptBalloon *)(&nameBalloon))->hide(1);
    hideCursor();
    ((MenuLauncher *)(ProcBase_GetParent(this)))->setNextRequest(0x44, 1);
    beginSubSlideOut(8, 0, 0, 0x30);
    applySlideOffset(6, 0, -16);
    setTransitionState(4);
    slideY = getSlideOffsetY();
}

void PocketsFullMenu::transitionAct04()
{
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(6);
        setPhase(5);
        clearFlags(1);
        clearFlags(2);
    } else {
        applySlideOffset(6, 0, -16);
    }
    slideY = getSlideOffsetY();
}

void PocketsFullMenu::initParts()
{
    stateFlags = 0;
    InventoryItemGrid_Init(&pocketGrid, 2);
    ((LetterGrid *)(&letterGrid))->init(2);
    Shared_InventoryBg_Init(&inventoryBg, 6);
    balloonSlot = 0x10;
    ((CursorMotion *)(&flyMotion))->reset();
    handKind = 0;
    cursorSlot = 0;
    ((PopupChoiceMenu *)(&popup))->init(3, 1, (const char *)(0));
    if (canReleaseFish()) {
        setFlags(0x40);
    }
    touchHoldDelay = 0;
}

void PocketsFullMenu::releaseResources()
{
    cancelBgTasks();
    InventoryBg_Exit(&inventoryBg);
    Shared_InventoryItemGrid_Exit(&pocketGrid);
    PopupChoice_ForceClose(&popup);
    ((MenuBottomButtons *)(&bottomButtons))->freeTexts();
}

void PocketsFullMenu::preInputUpdate()
{
    preStateUpdate();
    cursor.update();
}

void PocketsFullMenu::postInputUpdate()
{
    postStateUpdate();
}

void PocketsFullMenu::preStateUpdate()
{
    cancelBgTasks();
    Shared_InventoryBg_PreUpdate(&inventoryBg);
    InventoryItemGrid_PreUpdate(&pocketGrid);
    ((LetterGrid *)(&letterGrid))->updateCursorLift();
    ((MenuBottomButtons *)(&bottomButtons))->freeTexts();
}

void PocketsFullMenu::postStateUpdate()
{
    Shared_PopupChoice_Update(&popup);
    InventoryBg_Update(&inventoryBg);
    if (((TouchPromptBalloon *)(&nameBalloon))->updatePrompt()) {
        placeBalloon();
    }
}

void PocketsFullMenu::setupBgLayer6()
{
    Gfx2d_SetLayerPriority(6, 2);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
}

void PocketsFullMenu::loadInventoryBg()
{
    InventoryBg_Load(&inventoryBg, 0);
}

void PocketsFullMenu::loadObjGraphics()
{
    InventoryBg_LoadObjGraphics();
    MenuButtons_LoadTextColors();
}

void PocketsFullMenu::mainAct00()
{
    if (checkSwitchToButtons(1)) {
        startButtonInput();
    } else if (Unk_ov107_02296270_Both()) {
        s32 r = getSlotAt(gTouchCurX, gTouchCurY + 0x10, 1);
        if (r != 0x10) {
            beginTouchOnSlot(r);
        } else if (((MenuBottomButtonsBody *)(&bottomButtons))->isTouched(9)) {
            startCloseByTab();
        }
    }
}

void PocketsFullMenu::mainAct01()
{
    if (gTouchHeld == 0) {
        if (isSlotDisabled(touchedSlot)) {
            setMainState(0);
            ((TouchPromptBalloon *)(&nameBalloon))->setAutoCloseTimer(0x3c);
        } else {
            setMainState(3);
            runMainState();
        }
    } else if (isSlotDisabled(touchedSlot) == 0 && ((TouchPromptBalloon *)(&nameBalloon))->isOpenOrOpening()) {
        if (touchHoldDelay != 0) {
            touchHoldDelay = *(volatile u8 *)&touchHoldDelay - 1;
        } else {
            selectPocket(touchedSlot, 1);
            setMainState(2);
        }
    } else {
        ((TouchPromptBalloon *)(&nameBalloon))->commitOpen();
    }
}

void PocketsFullMenu::mainAct02()
{
    if (gTouchHeld == 0) {
        setMainState(4);
    }
}

void PocketsFullMenu::mainAct03()
{
    if (((TouchPromptBalloon *)(&nameBalloon))->isOpenOrOpening()) {
        if (touchHoldDelay != 0) {
            touchHoldDelay = *(volatile u8 *)&touchHoldDelay - 1;
        } else {
            selectPocket(touchedSlot, 1);
            setMainState(2);
        }
    }
}

void PocketsFullMenu::mainAct04()
{
    if (((PopupChoiceMenuBody *)(&popup))->isOpen()) {
        if (checkSwitchToButtons(1)) {
            cancelPopupForButtons();
        } else if (Unk_ov107_02296270_Both()) {
            s32 r = ((PopupChoiceMenuBody *)(&popup))->hitTestRowOrLast(gTouchCurX, gTouchCurY);
            if (r >= 0) {
                PopupChoice_DecideRow(&popup, r, 1);
                popupChoice = choiceList.values[r];
                setMainState(0xc);
            }
        }
    }
}

void PocketsFullMenu::mainAct05()
{
    if (checkSwitchToTouch()) {
        startTouchInput();
        ((TouchPromptBalloon *)(&nameBalloon))->hide(1);
    } else if (moveCursorByPad(takeRepeatedKeys())) {
        updateBalloonForCursor();
        moveCursorToTarget();
        ((TouchPromptBalloon *)(&nameBalloon))->hide(0);
    } else if (isSlotDisabled(cursorSlot) == 0 && (gPad[1] & 1) != 0) {
        if (isPocketSlot(cursorSlot)) {
            if (!isSlotEmpty(cursorSlot)) {
                selectPocket(cursorSlot, 0);
            }
        } else if (cursorSlot == 0xf) {
            pressCloseButton();
        }
    } else if ((gPad[1] & 2) != 0) {
        hideCursor();
        startCloseByTab();
        ((TouchPromptBalloon *)(&nameBalloon))->hide(0);
    } else {
        ((TouchPromptBalloon *)(&nameBalloon))->commitOpen();
    }
}

void PocketsFullMenu::mainAct06()
{
    if (checkSwitchToTouch()) {
        cancelPopupForButtons();
    } else if (PopupChoice_MoveCursor(&popup, takeRepeatedKeys(), &popupRow, 0)) {
        moveCursorToPopupRow();
    } else {
        u16 f = gPad[1];
        if ((f & 1) != 0) {
            ((MenuCursor *)(&cursor))->setPosePress();
            setMainState(7);
        } else if ((f & 2) != 0) {
            cancelPopup();
        }
    }
}

void PocketsFullMenu::mainAct07()
{
    if (((HandCursor *)(&cursor))->isAnimDone()) {
        PopupChoice_DecideRow(&popup, popupRow, 1);
        popupChoice = choiceList.values[popupRow];
        setMainState(0xc);
    }
}

void PocketsFullMenu::mainAct08()
{
    if (!((MenuCursorBase *)(&cursor))->isMoving()) {
        setMainState(returnState);
        if (returnState == 5) {
            setFocusSlot(cursorSlot);
        }
        runMainState();
    }
}

void PocketsFullMenu::mainAct09()
{
    if (((HandCursor *)(&cursor))->isAnimDone()) {
        ((MenuBottomButtonsBody *)(&bottomButtons))->setSelected(9);
        setMainState(0xf);
        Snd_PlaySe(0x28);
    }
}

void PocketsFullMenu::mainAct0A()
{
    if (((HandCursor *)(&cursor))->isAnimDone()) {
        refreshCursor();
        setMainState(5);
    }
}

void PocketsFullMenu::mainAct0B()
{
    if (((PopupChoiceMenuBody *)(&popup))->isOpen()) {
        if (MenuCtrl_IsButtons()) {
            cursorToPopupTop();
            setMainState(6);
        } else {
            setMainState(4);
        }
    }
}

void PocketsFullMenu::mainAct0C()
{
    if (PopupChoice_TickDecideDelay(&popup)) {
        PopupChoice_Close(&popup, 0);
        ((TouchPromptBalloon *)(&nameBalloon))->hide(1);
        if (((HandCursor *)(&cursor))->getAnim()) {
            showCursorAtSlot();
        }
        setMainState(0xd);
    }
}

void PocketsFullMenu::mainAct0D()
{
    if (((PopupChoiceMenuBody *)(&popup))->isClosed()) {
        onPopupChoice();
    }
}

void PocketsFullMenu::mainAct0E()
{
    if (((MenuErrorMessage *)(&errorMessage))->update(0)) {
        setMainState(returnState);
        ((HandCursor *)(&cursor))->enableObjWindow();
    }
}

void PocketsFullMenu::mainAct0F()
{
    if (((MenuBottomButtonsBody *)(&bottomButtons))->stepPress()) {
        if (((HandCursor *)(&cursor))->getAnim()) {
            s32 a = ((MenuBottomButtonsBody *)(&bottomButtons))->getPressOffset();
            s32 b = ((MenuBottomButtonsBody *)(&bottomButtons))->getTargetX(-1);
            s32 c = ((MenuBottomButtonsBody *)(&bottomButtons))->getTargetY(-1);
            ((MenuCursorBase *)(&cursor))->warpTo(a + b, a + c);
        }
    } else {
        MenuCtrl_SetResult(0);
        transitionState = 3;
        setPhase(1);
        ((TouchPromptBalloon *)(&nameBalloon))->hide(1);
        hideCursor();
    }
}

void PocketsFullMenu::mainAct12()
{
    if (HeldInsect_GetStage(getLocalPlayerIndex()) != 3) {
        waitTimer = 5;
        setMainState(0x13);
    }
}

void PocketsFullMenu::mainAct13()
{
    if (waitTimer != 0) {
        waitTimer = *(volatile u8 *)&waitTimer - 1;
    } else {
        closeWithSelection();
    }
}

void PocketsFullMenu::mainAct14()
{
    if (PlayerActor_IsInWaitMenu()) {
        closeWithSelection();
    }
}

void PocketsFullMenu::startTouchInput()
{
    hideCursor();
    clearFocusSlot();
    setMainState(0);
}

void PocketsFullMenu::startButtonInput()
{
    balloonSlot = 0x10;
    showCursor();
    restartKeyRepeat();
    updateBalloonForCursor();
    setMainState(5);
    setFocusSlot(cursorSlot);
}

void PocketsFullMenu::resumeInput()
{
    if (MenuCtrl_IsTouch()) {
        startTouchInput();
    } else {
        startButtonInput();
    }
}

void PocketsFullMenu::beginTouchOnSlot(u32 a)
{
    touchedSlot = a;
    setMainState(1);
    u32 x = gTouchCurX;
    u32 y = gTouchCurY;
    dragOffsetX = getSlotX(touchedSlot) - x;
    dragOffsetY = getSlotY(touchedSlot) - y;
    balloonSlot = a;
    ((TouchPromptBalloon *)(&nameBalloon))->queueOpen();
    ((TouchPromptBalloon *)(&nameBalloon))->commitOpen();
    touchHoldDelay = 2;
    if (isSlotDisabled(a) == 0) {
        Inventory_PlayTouchSe();
    }
}

void PocketsFullMenu::showMessage(s32 a, u32 b) {
    volatile u8 v[1];
    if (b == 0xff) {
        returnState = mainState;
    } else {
        returnState = b;
    }
    v[0] = gU8None;
    v[0] = a;
    ((MenuErrorMessage *)(&errorMessage))->open((u8 *)((void *)v), 1, 0);
    setMainState(0xe);
    ((HandCursor *)(&cursor))->disableObjWindow();
}

void PocketsFullMenu::cancelBgTasks() {
    bgTasks[0].cancel();
}

BOOL PocketsFullMenu::isPocketSlot(s32 a) {
    if ((u32)a <= 0xe) return TRUE;
    return FALSE;
}

u32 PocketsFullMenu::toPocketIndex(s32 a) {
    if (isPocketSlot(a)) return (u8)a;
    return 0;
}

u32 PocketsFullMenu::toSlotOrNone(s32 a) {
    if ((u32)a <= 0xe) return (u8)a;
    return 0x10;
}

u32 PocketsFullMenu::getSlotAt(s32 a, s32 b, s32 c) {
    u32 t = InventoryItemGrid_FindPocketSlotAt(&pocketGrid, a, b);
    if (t != 0x23) {
        if (c != 0) {
            if (InventoryItemGrid_IsSlotEmpty(&pocketGrid, t)) return 0x10;
        }
        return toSlotOrNone(t);
    }
    return 0x10;
}

void PocketsFullMenu::putItemInSlot(s32 a, s32 b, s32 c) {
    if (isPocketSlot(a)) {
        s32 t = toPocketIndex(a);
        InventoryItemGrid_SetSlotItem(&pocketGrid, t, b, c);
        InventoryItemGrid_RefreshSlot(&pocketGrid, t);
    }
}

s32 PocketsFullMenu::getSlotX(s32 a) {
    if (isPocketSlot(a)) {
        return InventoryItemGrid_GetSlotX(&pocketGrid, toPocketIndex(a));
    } else if (a == 0xf) {
        return 0xbc;
    }
    return 0;
}

s32 PocketsFullMenu::getSlotY(s32 a) {
    if (isPocketSlot(a)) {
        return InventoryItemGrid_GetSlotY(&pocketGrid, toPocketIndex(a)) - 0x10;
    } else if (a == 0xf) {
        return 0xb6;
    }
    return 0;
}

void PocketsFullMenu::disableLockedPockets() {
    u8 i = 0;
    do {
        if (isPocketLocked(i)) {
            InventoryItemGrid_DisableSlot(&pocketGrid, toPocketIndex(i));
        }
        i++;
    } while (i <= 0xe);
}

BOOL PocketsFullMenu::isPocketLocked(s32 a) {
    u32 r;
    if (isSlotEmpty(a)) return FALSE;
    if (getSlotItemFlags(a)) return TRUE;
    r = getSlotItem(a);
    if ((r >= 0x137c && r <= 0x137c) || (r >= 0x1408 && r <= 0x1428) || (r >= 0x1471 && r <= 0x1491)) {
        return TRUE;
    }
    if (r >= 0x12e8 && r <= 0x131f) {
        if (!testFlags(0x40)) return TRUE;
    }
    return FALSE;
}

BOOL PocketsFullMenu::isSlotDisabled(s32 a) {
    if (isPocketSlot(a)) {
        return Shared_InventoryItemGrid_IsSlotDisabled(&pocketGrid, toPocketIndex(a));
    }
    return FALSE;
}

BOOL PocketsFullMenu::isSlotEmpty(s32 a) {
    if (isPocketSlot(a)) {
        return InventoryItemGrid_IsSlotEmpty(&pocketGrid, toPocketIndex(a));
    }
    return TRUE;
}

u32 PocketsFullMenu::getSlotItem(s32 a) {
    if (isPocketSlot(a)) {
        return Shared_InventoryItemGrid_GetSlotItem(&pocketGrid, toPocketIndex(a));
    }
    return 0xfff1;
}

u32 PocketsFullMenu::getSlotItemFlags(s32 a) {
    if (isPocketSlot(a)) {
        return InventoryItemGrid_GetSlotFlags(&pocketGrid, toPocketIndex(a));
    }
    return 0xf1;
}

void PocketsFullMenu::clearFocusSlot() {
    InventoryItemGrid_ClearCursorSlot(&pocketGrid);
    ((LetterGrid *)(&letterGrid))->clearCursorSlot();
}

void PocketsFullMenu::setFocusSlot(s32 a) {
    if (isPocketSlot(a)) {
        Shared_InventoryItemGrid_SetCursorSlot(&pocketGrid, toPocketIndex(a));
        ((LetterGrid *)(&letterGrid))->clearCursorSlot();
    } else {
        clearFocusSlot();
    }
}

void PocketsFullMenu::placeBalloon() {
    s32 r6 = getSlotX(balloonSlot) - 0x6d;
    s32 r4 = getSlotY(balloonSlot) - 0x78;
    if (MenuCtrl_IsButtons()) r4 -= 8;
    ((LabelBalloon *)(&nameBalloon))->setPos(r6, r4);
    if (isPocketSlot(balloonSlot)) {
        Shared_InventoryItemGrid_ShowSlotName(&pocketGrid, &nameBalloon, toPocketIndex(balloonSlot));
    }
}

void PocketsFullMenu::updateBalloonForCursor() {
    if (isPocketSlot(cursorSlot)) {
        if (isSlotEmpty(cursorSlot)) {
            ((TouchPromptBalloon *)(&nameBalloon))->cancelQueuedOpen();
        } else {
            balloonSlot = cursorSlot;
            ((TouchPromptBalloon *)(&nameBalloon))->queueOpen();
        }
    } else {
        ((TouchPromptBalloon *)(&nameBalloon))->cancelQueuedOpen();
    }
}

void PocketsFullMenu::drawHeldItem() {
    if (!testFlags(0x20)) {
        if (handKind != 0) {
            if (handKind == 1) {
                InventoryItemGrid_DrawHeldItem(&pocketGrid, handX, handY);
            }
        }
    }
}

void PocketsFullMenu::showCursor() {
    s32 r4 = getCursorTargetX();
    s32 r2 = getCursorTargetY();
    ((MenuCursorBase *)(&cursor))->warpTo(r4, r2);
    if (cursorSlot == 0xf) {
        ((MenuCursor *)(&cursor))->setAnimIfChanged(7);
    } else {
        ((MenuCursor *)(&cursor))->setAnimIfChanged(1);
    }
    refreshCursor();
}

s32 PocketsFullMenu::getCursorTargetX() {
    s32 r4 = getSlotX(cursorSlot);
    if (testFlags(0x10)) {
        r4 += 0x100;
    } else if (testFlags(8)) {
        r4 -= 0x100;
    }
    r4 += 8;
    return r4;
}

s32 PocketsFullMenu::getCursorTargetY() {
    return getSlotY(cursorSlot);
}

void PocketsFullMenu::hideCursor() {
    ((MenuCursor *)(&cursor))->setAnimIfChanged(0);
    cursor.update();
}

void PocketsFullMenu::moveCursorToTarget() {
    if (testFlags(4)) {
        s32 r5 = getCursorTargetX();
        s32 r2 = getCursorTargetY();
        ((MenuCursorBase *)(&cursor))->warpTo(r5, r2);
        clearFlags(4);
    } else {
        s32 r5 = getCursorTargetX();
        s32 r2 = getCursorTargetY();
        ((MenuCursorBase *)(&cursor))->moveToEase(r5, r2, 3, 1);
        returnState = mainState;
        setMainState(8);
    }
}

void PocketsFullMenu::moveCursorToPopupRow() {
    s32 r4 = ((PopupChoiceMenuBody *)(&popup))->getRowX();
    s32 r2 = ((PopupChoiceMenuBody *)(&popup))->getRowY(popupRow);
    ((MenuCursorBase *)(&cursor))->moveToLinear(r4, r2, 2);
    returnState = mainState;
    setMainState(8);
}

void PocketsFullMenu::cancelPopup() {
    s32 r4;
    s32 r2;
    popupChoice = 4;
    popupRow = PopupChoice_DecideCancel(&popup, 1);
    r4 = ((PopupChoiceMenuBody *)(&popup))->getRowX();
    r2 = ((PopupChoiceMenuBody *)(&popup))->getRowY(popupRow);
    ((MenuCursorBase *)(&cursor))->warpTo(r4, r2);
    ((HandCursor *)(&cursor))->setAnimAtEnd(8);
    setMainState(0xc);
}

void PocketsFullMenu::cursorToPopupTop() {
    s32 r4;
    s32 r2;
    popupRow = 0;
    r4 = ((PopupChoiceMenuBody *)(&popup))->getRowX();
    r2 = ((PopupChoiceMenuBody *)(&popup))->getRowY(popupRow);
    ((MenuCursorBase *)(&cursor))->warpTo(r4, r2);
    ((MenuCursor *)(&cursor))->setAnimIfChanged(7);
}

void PocketsFullMenu::showCursorAtSlot() {
    s32 r4 = getCursorTargetX();
    s32 r2 = getCursorTargetY();
    ((MenuCursorBase *)(&cursor))->warpTo(r4, r2);
    ((MenuCursor *)(&cursor))->setAnimIfChanged(1);
}

void PocketsFullMenu::refreshCursor() {
    ((MenuCursorBase *)(&cursor))->setPoseIdle();
    cursor.update();
}

void PocketsFullMenu::pressCloseButton() {
    ((MenuCursor *)(&cursor))->setPosePress();
    setMainState(9);
}

void PocketsFullMenu::onPopupChoice() {
    if (popupChoice == 4) {
        resumeInput();
    } else {
        static Unk_ov107_02296e78_Fn tbl[4] = {
            &PocketsFullMenu::onChoiceReleaseInsect,
            &PocketsFullMenu::onChoiceDrop,
            &PocketsFullMenu::onChoiceReleaseFish,
            &PocketsFullMenu::onChoiceBury,
        };
        (this->*tbl[popupChoice])();
    }
}

void PocketsFullMenu::openPopup(s32 a) {
    s32 r6, r2;
    ((PopupChoiceMenuBody *)(&popup))->setRowsFromIds((PopupChoiceIdList *)(&choiceList), 0);
    r6 = getSlotX(selectedSlot);
    r2 = getSlotY(selectedSlot);
    if (a != 0) {
        ((PopupChoiceMenu *)(&popup))->placeAboveBalloon((LabelBalloon *)(&nameBalloon));
    } else {
        ((PopupChoiceMenu *)(&popup))->placeNearPoint(r6, r2);
    }
    PopupChoice_Open(&popup, 0);
    setMainState(0xb);
}

void PocketsFullMenu::cancelPopupForButtons() {
    popupChoice = 4;
    showCursorAtSlot();
    PopupChoice_Close(&popup, 0);
    setMainState(0xd);
}

void PocketsFullMenu::closeWithSelection() {
    MenuCtrl_SetIndex(selectedSlot);
    MenuCtrl_SetResult(1);
    transitionState = 3;
    setPhase(1);
    ((TouchPromptBalloon *)(&nameBalloon))->hide(1);
    hideCursor();
}

void PocketsFullMenu::startCloseByTab() {
    ((MenuBottomButtonsBody *)(&bottomButtons))->setSelected(9);
    setMainState(0xf);
    Snd_PlaySe(0x28);
}

void PocketsFullMenu::storeNewItem() {
    u16 a;
    u16 b;
    u32 r6, r4;
    a = MenuCtrl_GetPocketsFullItem();
    Item_FromPlacedForm(&b, &a);
    r6 = b;
    r4 = 0;
    if (r6 == 0x156b) {
        r6 = Item_PickRandomPresent();
        r4 = 1;
    }
    Catalog_SetItem(PlayerData_GetCurrent()->getCatalog(), &b, 0, 1);
    MenuCtrl_SetPocketsFullItem(getSlotItem(selectedSlot));
    putItemInSlot(selectedSlot, r6, r4);
}

void PocketsFullMenu::setPopupChoices() {
    MenuCtrl_GetPocketSelectLabel();
    s32 r6 = getSlotItem(selectedSlot);
    volatile u16 v = r6;
    s32 t = MenuCtrl_GetMode();
    BOOL ok = FALSE;
    u32 a = v;
    u32 b = v;
    if (b < 0x12b0 || a > 0x12e7) {
    } else {
        ok = TRUE;
    }
    if (ok) {
        ChoiceIdList_Add((u8 *)&choiceList, 0x10, 0);
    } else if (a >= 0x12e8 && a <= 0x131f) {
        ChoiceIdList_Add((u8 *)&choiceList, 0x10, 2);
    } else if (t == 0x2a) {
        ChoiceIdList_Add((u8 *)&choiceList, 0x10, 3);
    }
    if (Shared_InvItem_IsNotFishInsectOrFlower(r6)) {
        if (t == 0x2a) {
            ChoiceIdList_Add((u8 *)&choiceList, 1, 1);
        } else {
            ChoiceIdList_Add((u8 *)&choiceList, 0x10, 1);
        }
    }
    ChoiceIdList_Add((u8 *)&choiceList, 2, 4);
}

void PocketsFullMenu::selectPocket(u32 idx, u32 flag) {
    selectedSlot = idx;
    ChoiceIdList_Clear((u8 *)&choiceList, 4);
    if (isPocketSlot(idx)) {
        setPopupChoices();
        hideCursor();
        if (flag == 0) {
            ((TouchPromptBalloon *)(&nameBalloon))->hide(1);
        }
        openPopup(flag);
    }
}

void PocketsFullMenu::moveCursorInGrid(u32 pad) {
    s32 n = cursorSlot;
    s32 q = 0;
    while (n >= 5) {
        n -= 5;
        q++;
    }
    if (MenuKeys_HasLeft(pad)) {
        if (MenuKeys_HasUp(pad) == 0 || q == 0) {
            if (n == 0) {
                cursorSlot = cursorSlot + 4;
                setFlags(8);
            } else {
                cursorSlot = cursorSlot - 1;
            }
        }
    } else if (MenuKeys_HasRight(pad)) {
        if (MenuKeys_HasDown(pad) == 0) {
            if (n == 4) {
                cursorSlot = cursorSlot - 4;
                setFlags(0x10);
            } else {
                cursorSlot = cursorSlot + 1;
            }
        }
    }
    if (testFlags(0x18) == 0) {
        if (MenuKeys_HasUp(pad)) {
            if (q > 0) {
                cursorSlot = cursorSlot - 5;
            }
        } else if (MenuKeys_HasDown(pad)) {
            if (q < 2) {
                cursorSlot = cursorSlot + 5;
            } else {
                cursorSlot = 0xf;
                ((MenuCursor *)(&cursor))->switchToAnim07();
            }
        }
    }
}

BOOL PocketsFullMenu::moveCursorByPad(u32 pad) {
    u8 old = cursorSlot;
    clearFlags(0x18);
    if (pad == 0) {
        return FALSE;
    }
    if (isPocketSlot(cursorSlot)) {
        moveCursorInGrid(pad);
    } else if (cursorSlot == 0xf) {
        if (MenuKeys_HasUp(pad)) {
            cursorSlot = 0xe;
            ((MenuCursor *)(&cursor))->switchToAnim01();
        }
    }
    if (old == cursorSlot) {
        return FALSE;
    }
    return TRUE;
}

void PocketsFullMenu::onChoiceDrop() {
    s32 t = getSlotItem(selectedSlot);
    if (MenuCtrl_GetMode() == 0x29) {
        fieldRequest = FieldAction_RequestPlaceAtPending(gCommManager->myAid, t);
    } else {
        fieldRequest = FieldAction_RequestDropOrPlace(gCommManager->myAid, t);
    }
    if (fieldRequest == -1) {
        resumeInput();
        showMessage(3, 0xff);
    } else {
        setMainState(0x15);
    }
}

void PocketsFullMenu::mainAct15() {
    switch (FieldAction_PollDrop(fieldRequest)) {
    case 1:
        endNewItemAction(0);
        storeNewItem();
        FieldAction_Release(fieldRequest);
        waitTimer = 10;
        setMainState(0x13);
        fieldRequest = -1;
        break;
    case 2:
        FieldAction_Release(fieldRequest);
        resumeInput();
        showMessage(3, 0xff);
        fieldRequest = -1;
        break;
    }
}

void PocketsFullMenu::onChoiceReleaseInsect() {
    endNewItemAction(1);
    setMainState(0x10);
    mainAct10();
}

void PocketsFullMenu::mainAct10() {
    s32 r7 = getLocalPlayerIndex();
    if (HeldInsect_GetStage(r7) == 0) {
        struct { u16 a; } l;
        l.a = getSlotItem(selectedSlot);
        BOOL ok = FALSE;
        volatile u16 *pv = &l.a;
        u16 a = *pv;
        u16 b = *pv;
        if (b >= 0x12b0 && a <= 0x12e7) {
            ok = TRUE;
        }
        s32 r5 = ok ? a - 0x12b0 : -1;
        u8 t = Random_GlobalBelow(0x3c);
        s16 x = (t - 0x1e) * 0xb6;
        x += ((Actor *)PlayerActor_GetActor(4))->rotY;
        HeldInsect_Start((u8)r5, r7);
        HeldInsect_Release(r7, x);
        PlayerActor_LocalReleaseCatch(0);
        sendInsectReleasePacket((u8)r5, t);
        setMainState(0x12);
        storeNewItem();
    }
}

void PocketsFullMenu::sendInsectReleasePacket(u8 a, u8 b) {
    u8 buf[3];
    if (gCommManager->isOnline()) {
        buf[0] = 1;
        buf[1] = a;
        buf[2] = b;
        CommManager *g = gCommManager;
        g->beginRecord();
        g->writeRecord(buf, 3);
        g->endRecord(0x16, 4);
    }
}

BOOL PocketsFullMenu::canReleaseFish() {
    s32 t = MenuCtrl_GetMode();
    u8 k = getLocalPlayerIndex();
    if (t == 0x2c) {
        return FishCatch_GetReelTarget(&releasePos, k);
    }
    Actor *p = (Actor *)PlayerActor_GetActor(4);
    VecFx32 *q = &p->position;
    s32 i = 0;
    s32 base = p->rotY;
    for (; i < 8; i++) {
        if (Ground_FindWaterAhead(&releasePos, q, (s16)(base + sFishReleaseProbeAngles[i]), 0x7800, 0xa00, 0xc)) {
            return TRUE;
        }
    }
    return FALSE;
}

void PocketsFullMenu::onChoiceReleaseFish() {
    endNewItemAction(1);
    waitTimer = 5;
    setMainState(0x11);
    mainAct11();
}

void PocketsFullMenu::mainAct11() {
    if (*(volatile u8 *)&waitTimer != 0) {
        waitTimer = waitTimer - 1;
    } else {
        u8 k = getLocalPlayerIndex();
        s32 t = getSlotItem(selectedSlot);
        if (FishCatch_StartRelease(k, t, &releasePos)) {
            volatile u16 v = t;
            BOOL ok = FALSE;
            u32 a = v;
            u32 b = v;
            s32 idx;
            if (b < 0x12e8 || a > 0x131f) {
            } else {
                ok = TRUE;
            }
            if (ok) {
                idx = a - 0x12e8;
            } else {
                idx = -1;
            }
            sendFishReleasePacket((u8)idx);
            waitTimer = 0x14;
            setMainState(0x13);
            storeNewItem();
        }
    }
}

void PocketsFullMenu::sendFishReleasePacket(u8 v) {
    u8 buf[7];
    u8 tmp[5];
    if (gCommManager->isOnline()) {
        buf[0] = 2;
        buf[1] = v;
        NetBuf_PackPair20(tmp, releasePos.x, releasePos.z);
        MI_CpuCopy8(tmp, &buf[2], 5);
        CommManager *g = gCommManager;
        g->beginRecord();
        g->writeRecord(buf, 7);
        g->endRecord(0x16, 4);
    }
}

void PocketsFullMenu::onChoiceBury() {
    s32 t = getSlotItem(selectedSlot);
    CommManager *g = gCommManager;
    fieldRequest = FieldAction_RequestToolAtPending(g->myAid, 2, 0, t);
    if (fieldRequest == -1) {
        resumeInput();
        showMessage(3, 0xff);
    } else {
        u16 *p = PendingUnit_GetActivePosOfAid(g->localSlot);
        u32 w = *p;
        buryUnitX = (s32)w >> 8;
        buryUnitZ = w & 0xff;
        setMainState(0x16);
    }
}

void PocketsFullMenu::mainAct16() {
    switch (FieldAction_PollResult(fieldRequest)) {
    case 1:
        setMainState(0x17);
        mainAct17();
        break;
    case 2:
        resumeInput();
        showMessage(3, 0xff);
        break;
    default:
        return;
    }
    FieldAction_Release(fieldRequest);
    fieldRequest = -1;
}

void PocketsFullMenu::mainAct17() {
    u16 v;
    VecFx32 buf;
    FieldPos_FromUnitCenter(&buf, buryUnitX, buryUnitZ);
    v = getSlotItem(selectedSlot);
    if (PlayerActor_LocalRequestBuryItem(&buf, &v)) {
        storeNewItem();
        setMainState(0x14);
    }
}

u8 PocketsFullMenu::getLocalPlayerIndex() {
    CommManager *g = gCommManager;
    u32 v = g->myAid;
    if (g->isSlotActive(v)) {
        return (u8)v;
    }
    return 0;
}

void PocketsFullMenu::endNewItemAction(BOOL flag) {
    u8 buf[2];
    s32 t = MenuCtrl_GetMode();
    u8 k = getLocalPlayerIndex();
    switch (t) {
    case 0x29:
    case 0x2a:
        if (flag == 0) {
            break;
        }
        PendingUnit_ClearActiveOfAid(k);
        if (gCommManager->isOnline()) {
            buf[0] = 0x17;
            buf[1] = k;
            CommManager *g = gCommManager;
            g->beginRecord();
            g->writeRecord(buf, 2);
            g->endRecord(0x16, 4);
        }
        break;
    case 0x2b:
        HeldInsect_Remove(k, 1);
        break;
    case 0x2c:
        FishCatch_EndForShadow(MenuCtrl_GetPtrArg0());
        break;
    }
}

BOOL PocketsFullMenu::testFlags(u32 mask) {
    if (stateFlags & mask) {
        return TRUE;
    }
    return FALSE;
}

void PocketsFullMenu::setFlags(u32 mask) { stateFlags = stateFlags | mask; }


void PocketsFullMenu::clearFlags(u32 mask) { stateFlags = stateFlags & ~mask; }

extern "C" const s16 sFishReleaseProbeAngles[8] = {0, 0x2000, -0x2000, 0x4000, -0x4000, 0x6000, -0x6000, 0x7fff};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov107_02294c40) {
    HOST_OVERLAY_VAR(sPocketsFullMenuProfile),
    HOST_OVERLAY_VARS_END
};
