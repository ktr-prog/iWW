#include "types.h"
#include "host_shared_calls.h"
#include "Unk_020d8c7c.h"
#include "ui/CursorMotion.h"
#include "item/Letter.h"
#include "menu/InventoryItemGrid.h"
#include "menu/LetterGrid.h"
#include "menu/InventoryBg.h"
#include "menu/MenuProc.h"
#include "ui/HandCursor.h"
#include "menu/MenuLauncher.h"
#include "ui/LabelBalloon.h"
#include "gfx/BgVramTask.h"
#include "ui/TouchPromptBalloon.h"
#include "menu/MenuCursor.h"
#include "menu/PopupChoiceMenu.h"
#include "menu/MenuErrorMessage.h"
#include "sys/ProcProfile.h"
#include "menu/PocketMenuUnk.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_020b7d10.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov002/unk_ov002_022013ac.h"
#include "proto/ov094/unk_ov094_02292360.h"
#include "proto/ov094/unk_ov094_02292da8.h"
#include "proto/ov094/unk_ov094_02293b90.h"
#include "proto/ov099/unk_ov099_02294c40.h"

extern "C" {
extern u16 gPad[];

BOOL PopupChoice_MoveCursor(PopupChoiceMenuBody *self, s32 p, u8 *pos, u32 n);
BOOL PopupChoice_TickDecideDelay(PopupChoiceMenuBody *self);
void PopupChoice_DecideRow(PopupChoiceMenuBody *self, s32 a, s32 b);
void PopupChoice_ForceClose(PopupChoiceMenuBody *self);
void PopupChoice_Draw(PopupChoiceMenuBody *self);
void PopupChoice_Update(PopupChoiceMenuBody *self);
void PopupChoice_Close(PopupChoiceMenuBody *self, s32 x);
void PopupChoice_Open(PopupChoiceMenuBody *self, s32 x);
}

static inline PopupChoiceMenuBody *PocketMenuUnk_Popup(PocketMenuUnk *s) {
    return static_cast<PopupChoiceMenuBody *>(&s->popup);
}

extern "C" ProcProfile sPocketMenuUnkProfile = {(void *(*)())PocketMenuUnk_Create, 0x92, 0x96};

static inline BOOL Unk_ov099_02296158_Both()
{
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" PocketMenuUnk *PocketMenuUnk_Create() { return new PocketMenuUnk(); }

BOOL PocketMenuUnk::onCreate() {
    initPocketMenuUnk();
    setTransitionState(0);
    setPhase(0);
    return TRUE;
}

BOOL PocketMenuUnk::onDelete() {
    ((MenuLauncher *)ProcBase_GetParent(this))->onChildClosed();
    releaseResources();
    return TRUE;
}

BOOL PocketMenuUnk::onDraw() {
    PopupChoice_Draw(PocketMenuUnk_Popup(this));
    if (!testFlags(1)) {
        return TRUE;
    }
    nameBalloon.draw();
    if (MenuCtrl_IsButtons()) {
        cursor.drawWrapped();
    }
    drawHand();
    if (testFlags(2)) {
        InventoryItemGrid_DrawPockets(&pocketGrid, 0, slideY);
        letterGrid.drawPocketLetters(0, slideY);
        Shared_InventoryBg_DrawSprite(&inventoryBg, slideY);
    }
    return TRUE;
}

BOOL PocketMenuUnk::execTransition() {
    static Unk_ov099_02296b00_Fn tbl[5] = {
        &PocketMenuUnk::stateLoad, &PocketMenuUnk::stateSlideIn,
        &PocketMenuUnk::stateWaitSlideIn, &PocketMenuUnk::stateSlideOut,
        &PocketMenuUnk::stateWaitSlideOut};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}

BOOL PocketMenuUnk::execMain() {
    preInputUpdate();
    static Unk_ov099_02296b00_Fn tbl[21] = {
        &PocketMenuUnk::mainAct00, &PocketMenuUnk::mainAct01,
        &PocketMenuUnk::mainAct02, &PocketMenuUnk::mainAct03,
        &PocketMenuUnk::mainAct04, &PocketMenuUnk::mainAct05,
        &PocketMenuUnk::mainAct06, &PocketMenuUnk::mainAct07,
        &PocketMenuUnk::mainAct08, &PocketMenuUnk::mainAct09,
        &PocketMenuUnk::mainAct0A, &PocketMenuUnk::mainAct0B,
        &PocketMenuUnk::mainAct0C, &PocketMenuUnk::mainAct0D,
        &PocketMenuUnk::mainAct0E, &PocketMenuUnk::mainAct0F,
        &PocketMenuUnk::mainAct10, &PocketMenuUnk::mainAct11,
        &PocketMenuUnk::mainAct12, &PocketMenuUnk::mainAct13,
        &PocketMenuUnk::mainAct14};
    (this->*tbl[mainState])();
    postInputUpdate();
    return TRUE;
}

BOOL PocketMenuUnk::execPhase3() { return TRUE; }

BOOL PocketMenuUnk::execPhase4() { return TRUE; }

BOOL PocketMenuUnk::execClosed() {
    ProcBase_RequestDelete(this);
    return TRUE;
}

void PocketMenuUnk::stateLoad() {
    setupBgLayer();
    loadInventoryBg();
    setTransitionState(1);
}

void PocketMenuUnk::stateSlideIn() {
    loadObjGraphics();
    Shared_InventoryItemGrid_LoadPockets(&pocketGrid);
    Shared_LetterGrid_LoadPocketLetters(&letterGrid);
    beginSubSlideIn(8, 0, 0, 0x30);
    Gfx2d_ShowLayer(6);
    applySlideOffset(6, 0, 0);
    setTransitionState(2);
    setFlags(1);
    setFlags(2);
    slideY = getSlideOffsetY();
}

void PocketMenuUnk::stateWaitSlideIn() {
    if (stepSlideIn(0)) {
        setPhase(2);
        PocketMenuUnk_ReturnToIdle(this);
    }
    applySlideOffset(6, 0, 0);
    slideY = getSlideOffsetY();
}

void PocketMenuUnk::stateSlideOut() {
    nameBalloon.hide(1);
    hideCursor();
    ((MenuLauncher *)ProcBase_GetParent(this))->setNextRequest(0x44, 1);
    beginSubSlideOut(8, 0, 0, 0x30);
    applySlideOffset(6, 0, 0);
    setTransitionState(4);
    slideY = getSlideOffsetY();
}

void PocketMenuUnk::stateWaitSlideOut() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(6);
        setPhase(5);
        clearFlags(1);
        clearFlags(2);
    } else {
        applySlideOffset(6, 0, 0);
    }
    slideY = getSlideOffsetY();
}

void PocketMenuUnk::initPocketMenuUnk() {
    u16 a;
    u16 b;
    stateFlags = 0;
    InventoryItemGrid_Init(&pocketGrid, 2);
    letterGrid.init(2);
    Shared_InventoryBg_Init(&inventoryBg, 6);
    balloonTarget = 0x1d;
    flyMotion.reset();
    handKind = 0;
    cursorTarget = 0;
    popup.init(3, 1, 0);
    a = 0x11a9;
    Pocket_SetItem(&a, 1, 0);
    b = 0x1548;
    Pocket_SetItem(&b, 0, 2);
}

void PocketMenuUnk::releaseResources() {
    PocketMenuUnk_CancelVramTasks(this);
    InventoryBg_Exit(&inventoryBg);
    Shared_InventoryItemGrid_Exit(&pocketGrid);
    PopupChoice_ForceClose(PocketMenuUnk_Popup(this));
}

void PocketMenuUnk::preInputUpdate() {
    preStateUpdate();
    cursor.update();
}

void PocketMenuUnk::postInputUpdate() {
    postStateUpdate();
}

void PocketMenuUnk::preStateUpdate() {
    PocketMenuUnk_CancelVramTasks(this);
    Shared_InventoryBg_PreUpdate(&inventoryBg);
    InventoryItemGrid_PreUpdate(&pocketGrid);
    letterGrid.updateCursorLift();
}

void PocketMenuUnk::postStateUpdate() {
    Shared_PopupChoice_Update(PocketMenuUnk_Popup(this));
    InventoryBg_Update(&inventoryBg);
    if (nameBalloon.updatePrompt()) {
        positionLabelBalloon();
    }
}

void PocketMenuUnk::setupBgLayer() {
    Gfx2d_SetLayerPriority(6, 2);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
}

void PocketMenuUnk::loadInventoryBg() {
    InventoryBg_Load(&inventoryBg, 0);
}

void PocketMenuUnk::loadObjGraphics() {
    InventoryBg_LoadObjGraphics();
}

void PocketMenuUnk::mainAct00() {
    if (checkSwitchToButtons(1)) {
        PocketMenuUnk_EnterButtonIdle(this);
    } else {
        if (Unk_ov099_02296158_Both()) {
            u8 x = gTouchCurX;
            u8 y = gTouchCurY;
            s32 r = PocketMenuUnk_HitPocket(this, x, y, 1);
            if (r != 0x1d) {
                PocketMenuUnk_BeginTouchOnTarget(this, r);
            } else {
                r = PocketMenuUnk_HitLetter(this, x, y, 1);
                if (r != 0x1d) {
                    PocketMenuUnk_BeginTouchOnTarget(this, r);
                }
            }
        }
    }
}

void PocketMenuUnk::mainAct01() {
    if (gTouchHeld == 0) {
        setMainState(0);
        nameBalloon.setAutoCloseTimer(0x3c);
    } else {
        if (testFlags(4)) {
            if (PocketMenuUnk_HasTouchMoved(this)) {
                PocketMenuUnk_StartTouchDrag(this, touchedTarget);
                return;
            }
            if (PocketMenuUnk_IsTouchHeldFor(this, 9)) {
                openTargetOptions(touchedTarget);
                return;
            }
        }
        nameBalloon.commitOpen();
    }
}

void PocketMenuUnk::mainAct02() {
    if (checkSwitchToButtons(1)) {
        cancelOptions();
    } else {
        if (Unk_ov099_02296158_Both()) {
            s32 t = PocketMenuUnk_Popup(this)->hitTestRowOrLast(gTouchCurX, gTouchCurY);
            if (t >= 0) {
                PopupChoice_DecideRow(PocketMenuUnk_Popup(this), t, 1);
                chosenAction = choiceList.values[t];
                setMainState(0x12);
            }
        }
    }
}

void PocketMenuUnk::mainAct03() {
    syncHandFromTouch();
    PocketMenuUnk_ClearHighlights(this);
    s32 r = PocketMenuUnk_HitPocket(this, handX + 8, handY + 8, 0);
    if (r != 0x1d) {
        if (gTouchHeld == 0) {
            if (PocketMenuUnk_DropItemAt(this, r) == 0) {
                PocketMenuUnk_FlyHandTo(this, handSource, 4);
            }
            PocketMenuUnk_ReturnToIdle(this);
        } else {
            PocketMenuUnk_HighlightTarget(this, r);
        }
    } else if (gTouchHeld == 0) {
        PocketMenuUnk_FlyHandTo(this, handSource, 4);
    }
}

void PocketMenuUnk::mainAct04() {
    if (checkSwitchToTouch()) {
        PocketMenuUnk_EnterTouchIdle(this);
        nameBalloon.hide(1);
    } else if (moveCursorByPad(takeRepeatedKeys())) {
        updateLabelBalloon();
        moveCursorToTarget();
        nameBalloon.hide(0);
    } else if (PocketMenuUnk_IsSlotDisabled(this, cursorTarget) == 0 && (gPad[1] & 1) != 0) {
        if (PocketMenuUnk_IsPocketTarget(this, cursorTarget)) {
            if (PocketMenuUnk_IsSlotEmpty(this, cursorTarget) == 0) {
                openTargetOptions(cursorTarget);
            }
        }
    } else {
        if ((gPad[1] & 0x800) != 0) {
            transitionState = 3;
            setPhase(1);
            nameBalloon.hide(1);
            hideCursor();
        } else {
            nameBalloon.commitOpen();
        }
    }
}

void PocketMenuUnk::mainAct05() {
    if (moveCursorByPad(takeRepeatedKeys())) {
        updateLabelBalloon();
        moveCursorToTarget();
        nameBalloon.hide(0);
    } else {
        u16 f = gPad[1];
        if ((f & 1) != 0) {
            if (PocketMenuUnk_IsPocketTarget(this, cursorTarget)) {
                if (PocketMenuUnk_IsSlotEmpty(this, cursorTarget)) {
                    beginPutDownAt(cursorTarget);
                } else {
                    beginSwapAt(cursorTarget);
                }
            }
        } else if ((f & 2) != 0) {
            beginPutDownAt(handSource);
        } else {
            syncHandFromCursor();
            nameBalloon.commitOpen();
        }
    }
}

void PocketMenuUnk::mainAct06() {
    if (checkSwitchToTouch()) {
        cancelOptions();
    } else if (PopupChoice_MoveCursor(PocketMenuUnk_Popup(this), takeRepeatedKeys(), &popupRow, 0)) {
        moveCursorToPopupRow();
    } else {
        u16 f = gPad[1];
        if ((f & 1) != 0) {
            cursor.setPosePress();
            setMainState(7);
        } else if ((f & 2) != 0) {
            cancelOptions();
        }
    }
}

void PocketMenuUnk::mainAct07() {
    if (cursor.isAnimDone()) {
        PopupChoice_DecideRow(PocketMenuUnk_Popup(this), popupRow, 1);
        chosenAction = choiceList.values[popupRow];
        setMainState(0x12);
    }
}

void PocketMenuUnk::mainAct08() {
    if (cursor.isMoving() == 0) {
        setMainState(returnState);
        if ((u8)(returnState + 0xfc) <= 1) {
            PocketMenuUnk_SelectTarget(this, cursorTarget);
        }
    }
    syncHandFromCursor();
}

void PocketMenuUnk::mainAct09() {
    if (cursor.isAnimDone()) {
        releaseCursor();
    }
}

void PocketMenuUnk::mainAct0A() {
    if (cursor.isAnimDone()) {
        refreshCursor();
        setMainState(4);
    }
}

void PocketMenuUnk::mainAct0B() {
    if (cursor.isGripping()) {
        PocketMenuUnk_StartButtonDrag(this, cursorTarget);
        setMainState(0xc);
    }
}

void PocketMenuUnk::mainAct0C() {
    if (cursor.isAnimDone()) {
        setMainState(returnState);
    }
    syncHandFromCursor();
}

void PocketMenuUnk::mainAct0D() {
    if (!cursor.isGripping()) {
        u32 a = placeTarget;
        if (cursorTarget == a) {
            PocketMenuUnk_DropItemAt(this, a);
            updateLabelBalloon();
            setMainState(4);
        } else {
            PocketMenuUnk_FlyHandTo(this, a, 4);
        }
    } else {
        syncHandFromCursor();
    }
}

void PocketMenuUnk::mainAct0E() {
    if (!cursor.func_ov002_022028fc()) {
        swapHandWith(placeTarget);
        setFlags(0x40);
        setMainState(0xf);
        updateLabelBalloon();
    } else {
        setMainState(4);
    }
}

void PocketMenuUnk::mainAct0F() {
    if (cursor.isAnimDone()) {
        setMainState(returnState);
    }
    if (cursor.isGripping()) {
        clearFlags(0x40);
        syncHandFromCursor();
    }
}

void PocketMenuUnk::mainAct10() {
    if (flyMotion.update()) {
        putHandBack(handSource);
        PocketMenuUnk_ReturnToIdle(this);
    } else {
        syncHandFromMover();
    }
}

void PocketMenuUnk::mainAct11() {
    if (PocketMenuUnk_Popup(this)->isOpen()) {
        if (MenuCtrl_IsButtons()) {
            cursorToPopupTop();
            setMainState(6);
        } else {
            setMainState(2);
        }
    }
}

void PocketMenuUnk::mainAct12() {
    if (PopupChoice_TickDecideDelay(PocketMenuUnk_Popup(this))) {
        PopupChoice_Close(PocketMenuUnk_Popup(this), 0);
        if (cursor.getAnim()) {
            placeCursorOnTarget();
        }
        setMainState(0x13);
    }
}

void PocketMenuUnk::mainAct13() {
    if (PocketMenuUnk_Popup(this)->isClosed()) {
        runChosenAction();
    }
}


void PocketMenuUnk::mainAct14() {
    if (errorMessage.update(0)) {
        setMainState(returnState);
        cursor.enableObjWindow();
    }
}

extern "C" void PocketMenuUnk_EnterTouchIdle(PocketMenuUnk *s) {
    s->hideCursor();
    PocketMenuUnk_ClearSelection(s);
    s->setMainState(0);
}

extern "C" void PocketMenuUnk_EnterButtonIdle(PocketMenuUnk *s) {
    s->balloonTarget = 0x1d;
    s->showCursor();
    s->restartKeyRepeat();
    s->updateLabelBalloon();
    s->setMainState(4);
    PocketMenuUnk_SelectTarget(s, s->cursorTarget);
}

extern "C" void PocketMenuUnk_ReturnToIdle(PocketMenuUnk *s) {
    if (MenuCtrl_IsTouch()) {
        PocketMenuUnk_EnterTouchIdle(s);
    } else {
        PocketMenuUnk_EnterButtonIdle(s);
    }
}

extern "C" void PocketMenuUnk_BeginTouchOnTarget(PocketMenuUnk *s, u32 a) {
    u32 r6, r7;
    s->touchedTarget = a;
    s->setMainState(1);
    r6 = gTouchCurX;
    r7 = gTouchCurY;
    s->grabOffsetX = PocketMenuUnk_GetTargetX(s, s->touchedTarget) - r6;
    s->grabOffsetY = PocketMenuUnk_GetTargetY(s, s->touchedTarget) - r7;
    s->balloonTarget = a;
    s->nameBalloon.queueOpen();
    if (PocketMenuUnk_IsLetterTarget(s, a)) {
        s->clearFlags(4);
    } else if (PocketMenuUnk_IsSlotDisabled(s, a)) {
        s->clearFlags(4);
    } else {
        s->setFlags(4);
    }
}

extern "C" void PocketMenuUnk_StartTouchDrag(PocketMenuUnk *s, u32 a) {
    s->handSource = a;
    s->nameBalloon.hide(1);
    s->pickUp(a);
    if (s->handKind != 1) {
        if (s->handKind == 2) s->setMainState(3);
    }
    s->syncHandFromTouch();
}

extern "C" void PocketMenuUnk_StartButtonDrag(PocketMenuUnk *s, u32 a) {
    s->handSource = a;
    s->nameBalloon.hide(1);
    s->pickUp(a);
    if (s->handKind != 1) {
        if (s->handKind == 2) s->returnState = 5;
    }
    s->syncHandFromCursor();
}

extern "C" void PocketMenuUnk_FlyHandTo(PocketMenuUnk *s, u32 a, u32 b) {
    s->handSource = a;
    s->flyMotion.setPos(s->handX, s->handY);
    s32 x = PocketMenuUnk_GetTargetX(s, a);
    s->flyMotion.startLinear(x, PocketMenuUnk_GetTargetY(s, a), b);
    s->flyMotion.update();
    s->syncHandFromMover();
    s->setMainState(0x10);
}

extern "C" void PocketMenuUnk_CancelVramTasks(PocketMenuUnk *s) {
    s->bgTasks[0].cancel();
}

extern "C" BOOL PocketMenuUnk_IsPocketTarget(PocketMenuUnk *s, u32 a) {
    if (a <= 0xe) return TRUE;
    return FALSE;
}

extern "C" BOOL PocketMenuUnk_IsLetterTarget(PocketMenuUnk *s, u32 a) {
    if (a >= 0xf && a <= 0x18) return TRUE;
    return FALSE;
}

extern "C" u32 PocketMenuUnk_TargetToGridIndex(PocketMenuUnk *s, u32 a) {
    if (PocketMenuUnk_IsPocketTarget(s, a)) return (u8)a;
    return 0;
}

extern "C" u32 PocketMenuUnk_PocketIndexToTarget(PocketMenuUnk *s, u32 a) {
    if (a <= 0xe) return (u8)a;
    return 0x1d;
}

extern "C" u32 PocketMenuUnk_HitPocket(PocketMenuUnk *s, u32 a, u32 b, s32 c) {
    u32 t = InventoryItemGrid_FindPocketSlotAt(&s->pocketGrid, a, b);
    if (t != 0x23) {
        if (c != 0) {
            if (InventoryItemGrid_IsSlotEmpty(&s->pocketGrid, t)) return 0x1d;
        }
        return PocketMenuUnk_PocketIndexToTarget(s, t);
    }
    return 0x1d;
}

extern "C" BOOL PocketMenuUnk_DropItemAt(PocketMenuUnk *s, u32 a) {
    if (PocketMenuUnk_IsPocketTarget(s, a)) {
        u32 t = PocketMenuUnk_GetItem(s, a);
        if (t != 0xfff1) {
            PocketMenuUnk_SetSlotItem(s, s->handSource, t, PocketMenuUnk_GetItemFlags(s, a));
        }
        s->putHandBack(a);
        return TRUE;
    }
    return FALSE;
}

extern "C" void PocketMenuUnk_SetSlotItem(PocketMenuUnk *s, u32 a, u32 b, u32 c) {
    if (PocketMenuUnk_IsPocketTarget(s, a)) {
        u32 t = PocketMenuUnk_TargetToGridIndex(s, a);
        InventoryItemGrid_SetSlotItem(&s->pocketGrid, t, b, c);
        InventoryItemGrid_RefreshSlot(&s->pocketGrid, t);
    }
}

extern "C" u32 PocketMenuUnk_TargetToLetterIndex(PocketMenuUnk *s, u32 a) {
    if (a >= 0xf && a <= 0x18) return (u8)(a - 0xf);
    return 0;
}

extern "C" u32 PocketMenuUnk_LetterIndexToTarget(PocketMenuUnk *s, u32 a) {
    if (a <= 9) return (u8)(a + 0xf);
    return 0x1d;
}

extern "C" u32 PocketMenuUnk_HitLetter(PocketMenuUnk *s, u32 a, u32 b, s32 c) {
    u32 t = s->letterGrid.findPocketLetterAt(a, b);
    if (t != 0x37) {
        if (c != 0) {
            if (LetterGrid_IsSlotEmpty(&s->letterGrid, t)) return 0x1d;
        }
        return PocketMenuUnk_LetterIndexToTarget(s, t);
    }
    return 0x1d;
}

extern "C" s32 PocketMenuUnk_GetTargetX(PocketMenuUnk *s, u32 a) {
    if (PocketMenuUnk_IsPocketTarget(s, a)) {
        return InventoryItemGrid_GetSlotX(&s->pocketGrid, PocketMenuUnk_TargetToGridIndex(s, a));
    } else if (PocketMenuUnk_IsLetterTarget(s, a)) {
        return LetterGrid_GetSlotX(&s->letterGrid, PocketMenuUnk_TargetToLetterIndex(s, a));
    }
    return 0;
}

extern "C" s32 PocketMenuUnk_GetTargetY(PocketMenuUnk *s, u32 a) {
    if (PocketMenuUnk_IsPocketTarget(s, a)) {
        return InventoryItemGrid_GetSlotY(&s->pocketGrid, PocketMenuUnk_TargetToGridIndex(s, a));
    } else if (PocketMenuUnk_IsLetterTarget(s, a)) {
        return Shared_LetterGrid_GetSlotY(&s->letterGrid, PocketMenuUnk_TargetToLetterIndex(s, a));
    }
    return 0;
}

extern "C" BOOL PocketMenuUnk_IsSlotDisabled(PocketMenuUnk *s, u32 a) {
    if (PocketMenuUnk_IsPocketTarget(s, a)) {
        return Shared_InventoryItemGrid_IsSlotDisabled(&s->pocketGrid, PocketMenuUnk_TargetToGridIndex(s, a));
    } else if (PocketMenuUnk_IsLetterTarget(s, a)) {
        return s->letterGrid.isHighlighted(PocketMenuUnk_TargetToLetterIndex(s, a));
    }
    return FALSE;
}

extern "C" BOOL PocketMenuUnk_IsSlotEmpty(PocketMenuUnk *s, u32 a) {
    if (PocketMenuUnk_IsPocketTarget(s, a)) {
        return InventoryItemGrid_IsSlotEmpty(&s->pocketGrid, PocketMenuUnk_TargetToGridIndex(s, a));
    } else if (PocketMenuUnk_IsLetterTarget(s, a)) {
        return LetterGrid_IsSlotEmpty(&s->letterGrid, PocketMenuUnk_TargetToLetterIndex(s, a));
    }
    return TRUE;
}

extern "C" u32 PocketMenuUnk_GetItem(PocketMenuUnk *s, u32 a) {
    if (PocketMenuUnk_IsPocketTarget(s, a)) {
        return Shared_InventoryItemGrid_GetSlotItem(&s->pocketGrid, PocketMenuUnk_TargetToGridIndex(s, a));
    }
    return 0xfff1;
}

extern "C" u32 PocketMenuUnk_GetItemFlags(PocketMenuUnk *s, u32 a) {
    if (PocketMenuUnk_IsPocketTarget(s, a)) {
        return InventoryItemGrid_GetSlotFlags(&s->pocketGrid, PocketMenuUnk_TargetToGridIndex(s, a));
    }
    return 0xf1;
}

extern "C" void PocketMenuUnk_ClearSelection(PocketMenuUnk *s) {
    InventoryItemGrid_ClearCursorSlot(&s->pocketGrid);
    s->letterGrid.clearCursorSlot();
}

extern "C" void PocketMenuUnk_SelectTarget(PocketMenuUnk *s, u32 a) {
    if (PocketMenuUnk_IsPocketTarget(s, a)) {
        Shared_InventoryItemGrid_SetCursorSlot(&s->pocketGrid, PocketMenuUnk_TargetToGridIndex(s, a));
        s->letterGrid.clearCursorSlot();
    } else if (PocketMenuUnk_IsLetterTarget(s, a)) {
        s->letterGrid.setCursorSlot(PocketMenuUnk_TargetToLetterIndex(s, a));
        InventoryItemGrid_ClearCursorSlot(&s->pocketGrid);
    } else {
        PocketMenuUnk_ClearSelection(s);
    }
}

extern "C" void PocketMenuUnk_ClearHighlights(PocketMenuUnk *s) {
    Shared_InventoryItemGrid_ClearMarks(&s->pocketGrid);
    s->letterGrid.clearMarks();
}

extern "C" void PocketMenuUnk_HighlightTarget(PocketMenuUnk *s, u32 a) {
    if (PocketMenuUnk_IsPocketTarget(s, a)) {
        InventoryItemGrid_MarkSlot(&s->pocketGrid, PocketMenuUnk_TargetToGridIndex(s, a));
    } else if (PocketMenuUnk_IsLetterTarget(s, a)) {
        s->letterGrid.markSlot(PocketMenuUnk_TargetToLetterIndex(s, a));
    }
}

extern "C" BOOL PocketMenuUnk_HasTouchMoved(PocketMenuUnk *s) {
    s32 d = gTouchPressX - gTouchCurX;
    if (d < 0) d = -d;
    if (d > 8) return TRUE;
    d = gTouchPressY - gTouchCurY;
    if (d < 0) d = -d;
    if (d > 8) return TRUE;
    return FALSE;
}


extern "C" BOOL PocketMenuUnk_IsTouchHeldFor(PocketMenuUnk *self, s32 v) {
    if (gTouchHoldFrames >= v) return TRUE;
    return FALSE;
}

void PocketMenuUnk::positionLabelBalloon() {
    s32 x = PocketMenuUnk_GetTargetX(this, balloonTarget) - 0x6d;
    s32 y = PocketMenuUnk_GetTargetY(this, balloonTarget) - 0x78;
    if (MenuCtrl_IsButtons()) {
        y -= 8;
    }
    nameBalloon.setPos(x, y);
    if (PocketMenuUnk_IsPocketTarget(this, balloonTarget)) {
        s32 r = PocketMenuUnk_TargetToGridIndex(this, balloonTarget);
        Shared_InventoryItemGrid_ShowSlotName(&pocketGrid, &nameBalloon, r);
    } else if (PocketMenuUnk_IsLetterTarget(this, balloonTarget)) {
        s32 r = PocketMenuUnk_TargetToLetterIndex(this, balloonTarget);
        letterGrid.showLetterName(&nameBalloon, r);
    }
}

void PocketMenuUnk::updateLabelBalloon() {
    if (PocketMenuUnk_IsPocketTarget(this, cursorTarget) || PocketMenuUnk_IsLetterTarget(this, cursorTarget)) {
        if (PocketMenuUnk_IsSlotEmpty(this, cursorTarget)) {
            nameBalloon.cancelQueuedOpen();
        } else {
            balloonTarget = cursorTarget;
            nameBalloon.queueOpen();
        }
    } else {
        nameBalloon.cancelQueuedOpen();
    }
}

void PocketMenuUnk::drawHand() {
    if (!testFlags(0x40)) {
        switch (handKind) {
        case 0:
            break;
        case 2:
            InventoryItemGrid_DrawHeldItem(&pocketGrid, handX, handY);
            break;
        }
    }
}

void PocketMenuUnk::syncHandFromTouch() {
    handX = grabOffsetX + gTouchCurX;
    handY = grabOffsetY + gTouchCurY;
}

void PocketMenuUnk::syncHandFromCursor() {
    handX = cursor.getFrameScreenX() - 2;
    handY = cursor.getFrameScreenY() - 4;
}

void PocketMenuUnk::syncHandFromMover() {
    handX = flyMotion.getX();
    handY = flyMotion.getY();
}

void PocketMenuUnk::pickUp(u32 idx) {
    if (PocketMenuUnk_IsPocketTarget(this, idx)) {
        s32 r4 = PocketMenuUnk_TargetToGridIndex(this, idx);
        handKind = 2;
        handItem = Shared_InventoryItemGrid_GetSlotItem(&pocketGrid, r4);
        handItemFlags = InventoryItemGrid_GetSlotFlags(&pocketGrid, r4);
        Shared_InventoryItemGrid_ClearSlot(&pocketGrid, r4);
        Shared_InventoryItemGrid_SetHeldItem(&pocketGrid, handItem, handItemFlags);
    } else {
        if (PocketMenuUnk_IsLetterTarget(this, idx) != 0) {
            return;
        }
    }
}

void PocketMenuUnk::putHandBack(u32 idx) {
    if (handKind == 1) {
    } else if (handKind == 2) {
        PocketMenuUnk_SetSlotItem(this, idx, handItem, handItemFlags);
    }
    handKind = 0;
}

void PocketMenuUnk::swapHandWith(u32 idx) {
    if (handKind == 1) {
    } else if (handKind == 2) {
        u16 a = handItem;
        u8 b = handItemFlags;
        pickUp(idx);
        PocketMenuUnk_SetSlotItem(this, idx, a, b);
    }
}

void PocketMenuUnk::showCursor() {
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    cursor.warpTo(a, b);
    cursor.setAnimIfChanged(1);
    refreshCursor();
}

s32 PocketMenuUnk::getCursorTargetX() {
    s32 r = PocketMenuUnk_GetTargetX(this, cursorTarget);
    if (testFlags(0x20)) {
        r += 0x100;
    } else if (testFlags(0x10)) {
        r -= 0x100;
    }
    return r + 8;
}

s32 PocketMenuUnk::getCursorTargetY() { return PocketMenuUnk_GetTargetY(this, cursorTarget); }

void PocketMenuUnk::hideCursor() {
    cursor.setAnimIfChanged(0);
    cursor.update();
}

void PocketMenuUnk::moveCursorToTarget() {
    if (testFlags(8)) {
        s32 a = getCursorTargetX();
        s32 b = getCursorTargetY();
        cursor.warpTo(a, b);
        clearFlags(8);
    } else {
        s32 a = getCursorTargetX();
        s32 b = getCursorTargetY();
        cursor.moveToEase(a, b, 3, 1);
        returnState = mainState;
        setMainState(8);
    }
}

void PocketMenuUnk::moveCursorToPopupRow() {
    s32 a = PocketMenuUnk_Popup(this)->getRowX();
    s32 b = PocketMenuUnk_Popup(this)->getRowY(popupRow);
    cursor.moveToLinear(a, b, 2);
    returnState = mainState;
    setMainState(8);
}

void PocketMenuUnk::cursorToPopupTop() {
    popupRow = 0;
    s32 a = PocketMenuUnk_Popup(this)->getRowX();
    s32 b = PocketMenuUnk_Popup(this)->getRowY(popupRow);
    cursor.warpTo(a, b);
    cursor.setAnimIfChanged(7);
}

void PocketMenuUnk::placeCursorOnTarget() {
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    cursor.warpTo(a, b);
    cursor.setAnimIfChanged(1);
}

void PocketMenuUnk::refreshCursor() {
    cursor.setPoseIdle();
    cursor.update();
}

void PocketMenuUnk::releaseCursor() {
    cursor.setPoseRelease();
    setMainState(0xa);
}

void PocketMenuUnk::beginMoveFromPopup() {
    cursor.setAnimIfChanged(4);
    setMainState(0xb);
}

void PocketMenuUnk::beginPutDownAt(u32 v) {
    nameBalloon.hide(1);
    placeTarget = v;
    cursor.setAnimIfChanged(5);
    setMainState(0xd);
}

void PocketMenuUnk::beginSwapAt(u32 v) {
    nameBalloon.hide(1);
    returnState = mainState;
    placeTarget = v;
    cursor.setAnimIfChanged(6);
    setMainState(0xe);
}

void PocketMenuUnk::runChosenAction() {
    switch (chosenAction) {
    case 0:
        beginMoveFromPopup();
        break;
    case 1:
    default:
        PocketMenuUnk_ReturnToIdle(this);
        break;
    }
}

void PocketMenuUnk::showOptionList() {
    PocketMenuUnk_Popup(this)->setRowsFromIds(&choiceList, 0);
    s32 a = PocketMenuUnk_GetTargetX(this, actionTarget);
    s32 b = PocketMenuUnk_GetTargetY(this, actionTarget);
    popup.placeNearPoint(a, b);
    PopupChoice_Open(PocketMenuUnk_Popup(this), 0);
    setMainState(0x11);
}

void PocketMenuUnk::cancelOptions() {
    chosenAction = 1;
    placeCursorOnTarget();
    PopupChoice_Close(PocketMenuUnk_Popup(this), 0);
    setMainState(0x13);
}

void PocketMenuUnk::addItemOptions() {
    if (MenuCtrl_IsButtons()) {
        ChoiceIdList_Add((u8 *)&choiceList, 0, 0);
    }
    ChoiceIdList_Add((u8 *)&choiceList, 1, 1);
    ChoiceIdList_Add((u8 *)&choiceList, 2, 1);
}

void PocketMenuUnk::openTargetOptions(u32 idx) {
    actionTarget = idx;
    ChoiceIdList_Clear((u8 *)&choiceList, 1);
    if (PocketMenuUnk_IsPocketTarget(this, idx)) {
        addItemOptions();
        hideCursor();
        nameBalloon.hide(1);
        showOptionList();
    }
}

void PocketMenuUnk::moveCursorInPockets(u32 pad) {
    s32 col = cursorTarget;
    s32 row = 0;
    while (col >= 5) {
        col -= 5;
        row++;
    }
    if (MenuKeys_HasLeft(pad)) {
        if (!MenuKeys_HasUp(pad) || row == 0) {
            if (col == 0) {
                cursorTarget = cursorTarget + 4;
                setFlags(0x10);
            } else {
                cursorTarget = cursorTarget - 1;
            }
        }
    } else if (MenuKeys_HasRight(pad)) {
        if (!MenuKeys_HasDown(pad)) {
            if (col == 4) {
                cursorTarget = cursorTarget - 4;
                setFlags(0x20);
            } else {
                cursorTarget = cursorTarget + 1;
            }
        }
    }
    if (!testFlags(0x30)) {
        if (MenuKeys_HasUp(pad)) {
            if (row > 0) {
                cursorTarget = cursorTarget - 5;
            }
        } else if (MenuKeys_HasDown(pad)) {
            if (row < 2) {
                cursorTarget = cursorTarget + 5;
            }
        }
    }
}

BOOL PocketMenuUnk::moveCursorByPad(u32 pad) {
    u8 old = cursorTarget;
    clearFlags(0x30);
    if (pad == 0) {
        return FALSE;
    }
    if (PocketMenuUnk_IsPocketTarget(this, cursorTarget)) {
        moveCursorInPockets(pad);
    }
    if (old != cursorTarget) {
        return TRUE;
    }
    return FALSE;
}

BOOL PocketMenuUnk::testFlags(u32 mask) {
    if (stateFlags & mask) {
        return TRUE;
    }
    return FALSE;
}

void PocketMenuUnk::setFlags(u32 mask) { stateFlags = stateFlags | mask; }

void PocketMenuUnk::clearFlags(u32 mask) { stateFlags = stateFlags & ~mask; }


#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov099_02294c40) {
    HOST_OVERLAY_VAR(sPocketMenuUnkProfile),
    HOST_OVERLAY_VARS_END
};
