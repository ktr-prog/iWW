#include "types.h"
#include "host_shared_calls.h"
#include "Unk_020d8c7c.h"
#include "net/CommManager.h"
#include "ui/CursorMotion.h"
#include "menu/InventoryItemGrid.h"
#include "menu/LetterGrid.h"
#include "menu/InventoryBg.h"
#include "menu/MenuProc.h"
#include "ui/HandCursor.h"
#include "menu/MenuLauncher.h"
#include "ui/LabelString.h"
#include "ui/LabelBalloon.h"
#include "gfx/BgVramTask.h"
#include "ui/TouchPromptBalloon.h"
#include "menu/MenuCursor.h"
#include "menu/PopupChoiceMenu.h"
#include "menu/MenuErrorMessage.h"
#include "sys/ProcProfile.h"
#include "save/SaveData.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0206f834.h"
#include "proto/main/unk_020720f8.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov094/unk_ov094_02292360.h"
#include "proto/ov094/unk_ov094_02292da8.h"
#include "proto/ov094/unk_ov094_02293b90.h"
#include "proto/ov110/unk_ov110_02294c40.h"

class LostFoundRecycleMenu;

extern "C" {
extern CommManager *gCommManager;
extern SaveData gSaveData;
extern u16 gPad[];
BOOL Clock_GetWeekday();
void MI_CpuCopy8(void *a, void *b, u32 c);
BOOL PopupChoice_MoveCursor(void *p, s32 a, void *q, s32 b);
BOOL PopupChoice_TickDecideDelay(void *p);
s32 PopupChoice_DecideCancel(void *p, s32 x);
void PopupChoice_DecideRow(void *p, s32 a, s32 b);
void PopupChoice_ForceClose(void *a);
void PopupChoice_Update(void *a);
void PopupChoice_Close(void *p, s32 x);
}




















typedef void (LostFoundRecycleMenu::*Unk_ov110_02297778_Fn)();

class LostFoundRecycleMenu : public MenuProc {
public:
    LostFoundRecycleMenu()
        : vramTask(), itemGrid(), letterGrid(), inventoryBg(), nameBalloon(), flyMotion(), cursor(), choiceMenu(), errorMessage(), textLabels() {}

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
    BOOL isResultSent();
    void sendItemsRecord(u8 v);
    s32 packItemList(u16 *p);
    void confirm(s32 flag);
    void setOkLabel(s32 flag);
    LabelString *allocTextLabel();
    void resetTextLabels();
    BOOL moveCursorByPad(u32 pad, s32 mode);
    void moveCursorOnButtons(u32 pad);
    void moveCursorInBox(u32 pad, s32 mode);
    void moveCursorInPockets(u32 pad, s32 mode);
    void cancelChoiceList();
    void applyChoice();
    void startExchange(u8 v);
    void startPutDown(u8 v);
    void startPickUp();
    void releaseCursor();
    void pressCursor();
    void refreshCursor();
    void placeCursorAtTarget();
    void placeCursorOnFirstChoice();

    void mainAct00();
    void mainAct01();
    void mainAct02();
    void mainAct03();
    void mainAct04();
    void mainAct05();
    void mainAct06();
    void mainAct07();
    void updateCursorMove();
    void updateCursorPress();
    void updateCursorRelease();
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
    void transitionAct01();
    void transitionAct02();
    void transitionAct03();
    void transitionAct04();
    void transitionAct05();
    void transitionAct06();

    void transitionAct00();
    BOOL isForcedClose();
    void runMainState();

    /* 0x91 */ u8 unk_91[3];
    /* 0x94 */ u32 stateFlags;
    /* 0x98 */ s32 pocketsSlideY;
    /* 0x9c */ s32 boxSlideY;
    /* 0xa0 */ s32 grabOffsetX;
    /* 0xa4 */ s32 grabOffsetY;
    /* 0xa8 */ s32 heldX;
    /* 0xac */ s32 heldY;
    /* 0xb0 */ u16 boxItems[15];
    /* 0xce */ u16 initialBoxItems[15];
    /* 0xec */ u16 heldItem;
    /* 0xee */ s16 sendSeq;
    /* 0xf0 */ u8 heldItemFlags;
    /* 0xf1 */ u8 heldKind;
    /* 0xf2 */ u8 touchedSlot;
    /* 0xf3 */ u8 balloonSlot;
    /* 0xf4 */ u8 pickUpSlot;
    /* 0xf5 */ u8 cursorSlot;
    /* 0xf6 */ u8 unk_f6;
    /* 0xf7 */ u8 actionSlot;
    /* 0xf8 */ u8 returnState;
    /* 0xf9 */ u8 chosenAction;
    /* 0xfa */ u8 choiceRow;
    /* 0xfb */ u8 numTextLabels;
    /* 0xfc */ u8 delayTimer;
    /* 0xfd */ u8 unk_fd[3];
    /* 0x100 */ BgVramTaskPair vramTask[1];
    /* 0x138 */ InventoryItemGrid itemGrid;
    /* 0xb98 */ LetterGrid letterGrid;
    /* 0xbc0 */ InventoryBg inventoryBg;
    /* 0x21a0 */ TouchPromptBalloon nameBalloon;
    /* 0x2260 */ CursorMotion flyMotion;
    /* 0x2278 */ MenuCursorBuf0 cursor;
    /* 0x22dc */ PopupChoiceMenu choiceMenu;
    /* 0x25d0 */ PopupChoiceIdList choiceList;
    /* 0x25db */ u8 pad_25db[1];
    /* 0x25dc */ MenuErrorMessage errorMessage;
    /* 0x26e4 */ LabelString textLabels[2];
};

static inline void func_02089ad8(void *p, s32 a, s32 b) { ((LabelBalloon *)p)->setPos((s32)a, (s32)b); }
static inline void func_02089af0(void *p) { ((LabelBalloon *)p)->setPopUpward(); }
static inline void func_02089af8(void *p) { ((LabelBalloon *)p)->setPopDownward(); }
static inline s32 func_0208d4fc(void *p) { return ((HandCursor *)p)->isAnimDone(); }
static inline s32 func_0208d534(void *p) { return ((HandCursor *)p)->getAnim(); }
static inline void func_0208d538(void *p, s32 a) { ((HandCursor *)p)->setAnimAtEnd((s32)a); }
static inline void func_0208d644(void *p) { ((HandCursor *)p)->enableObjWindow(); }
static inline void func_020b87d0(void *p) { ((BgVramTask *)p)->cancel(); }
static inline void func_ov002_022006a4(void *a, s32 b) { ((TouchPromptBalloon *)a)->setAutoCloseTimer((u8)b); }
static inline void func_ov002_022006b0(void *p) { ((TouchPromptBalloon *)p)->cancelQueuedOpen(); }
static inline void func_ov002_022006b8(void *p) { ((TouchPromptBalloon *)p)->queueOpen(); }
static inline void func_ov002_022006c0(void *p) { ((TouchPromptBalloon *)p)->commitOpen(); }
static inline void func_ov002_022006e4(void *self, s32 a) { ((TouchPromptBalloon *)self)->hide((s32)a); }
static inline s32 func_ov002_0220071c(void *a) { return ((TouchPromptBalloon *)a)->updatePrompt(); }
static inline void func_ov002_02200840(void *a, s32 b, s32 c, s32 d) { ((MenuProc *)a)->applySlideOffset((s32)b, (s32)c, (s32)d); }
static inline void func_ov002_02200850(void *a, s32 b) { ((MenuProc *)a)->setSlideExtent((s32)b); }
static inline void func_ov002_022008c4(void *a, s32 b, s32 c, s32 d, s32 e) { ((MenuProc *)a)->beginSubSlideOut((s32)b, (s32)c, (s32)d, (s32)e); }
static inline void func_ov002_022008e0(void *a, s32 b, s32 c, s32 d, s32 e) { ((MenuProc *)a)->beginSubSlideIn((s32)b, (s32)c, (s32)d, (s32)e); }
static inline s32 func_ov002_022008fc(void *a, s32 b) { return ((MenuProc *)a)->stepSlideOut((s32)b); }
static inline s32 func_ov002_02200908(void *a, s32 b) { return ((MenuProc *)a)->stepSlideIn((s32)b); }
static inline s32 func_ov002_02200920(void *a) { return ((MenuProc *)a)->getSlideOffsetY(); }
static inline void func_ov002_02200980(void *self) { ((MenuProc *)self)->restartKeyRepeat(); }
static inline u32 func_ov002_022009c8(void *self) { return ((MenuProc *)self)->takeRepeatedKeys(); }
static inline u32 func_ov002_022009d4(void *self) { return ((MenuProc *)self)->checkSwitchToTouch(); }
static inline s32 func_ov002_02200a14(void *a, s32 b) { return ((MenuProc *)a)->checkSwitchToButtons((s32)b); }
static inline void func_ov002_02200a50(void *a, s32 b) { ((MenuProc *)a)->setTransitionState((u8)b); }
static inline void func_ov002_02200a58(void *self, s32 s) { ((MenuProc *)self)->setMainState((u8)s); }
static inline void func_ov002_02200a60(void *self, s32 s) { ((MenuProc *)self)->setPhase((u8)s); }
static inline s32 func_ov002_02201498(void *p, u32 v) { return ((PopupChoiceMenuBody *)p)->getRowY((s32)v); }
static inline s32 func_ov002_022014a4(void *p) { return ((PopupChoiceMenuBody *)p)->getRowX(); }
static inline s32 func_ov002_022014c0(void *a, s32 b, s32 c) { return ((PopupChoiceMenuBody *)a)->hitTestRowOrLast((s32)b, (s32)c); }
static inline BOOL func_ov002_022017a4(void *p) { return ((PopupChoiceMenuBody *)p)->isClosed(); }
static inline BOOL func_ov002_022017b4(void *p) { return ((PopupChoiceMenuBody *)p)->isOpen(); }
static inline void func_ov002_022026c4(void *p, s32 a, s32 b, s32 c) { ((CursorMotion *)p)->startLinear((s32)a, (s32)b, (s32)c); }
static inline void func_ov002_022026f4(void *p, s32 a, s32 b) { ((CursorMotion *)p)->setPos((s32)a, (s32)b); }
static inline s32 func_ov002_02202708(void *p) { return ((CursorMotion *)p)->getY(); }
static inline s32 func_ov002_02202710(void *p) { return ((CursorMotion *)p)->getX(); }
static inline BOOL func_ov002_02202718(void *p) { return ((CursorMotion *)p)->update(); }
static inline void func_ov002_022027a4(void *a) { ((CursorMotion *)a)->reset(); }
static inline s32 func_ov002_022028a0(void *p) { return ((MenuCursorBase *)p)->getFrameScreenY(); }
static inline s32 func_ov002_022028c8(void *p) { return ((MenuCursorBase *)p)->getFrameScreenX(); }
static inline BOOL func_ov002_022028f0(void *p) { return ((MenuCursorBase *)p)->isMoving(); }
static inline BOOL func_ov002_022028fc(void *p) { return ((MenuCursorBase *)p)->func_ov002_022028fc(); }
static inline BOOL MenuCursor_IsGripping(void *p) { return ((MenuCursorBase *)p)->isGripping(); }
static inline void func_ov002_022029e8(void *p, s32 a, s32 b, s32 c, s32 d) { ((MenuCursorBase *)p)->moveToEase((s32)a, (s32)b, (s32)c, (s32)d); }
static inline void func_ov002_02202a18(void *p, s32 a, s32 b, s32 c) { ((MenuCursorBase *)p)->moveToLinear((s32)a, (s32)b, (s32)c); }
static inline void func_ov002_02202a40(void *p, s32 a, s32 b) { ((MenuCursorBase *)p)->warpTo((s32)a, (s32)b); }
static inline void func_ov002_02202b68(void *p) { ((MenuCursor *)p)->setPosePress(); }
static inline void func_ov002_02202d00(void *p, s32 a) { ((MenuCursor *)p)->setAnimIfChanged((s32)a); }
static inline void func_ov094_022941f8(void *a, s32 b) { ((LetterGrid *)a)->highlightLetterKinds((u32)b); }
static inline void func_ov094_022943b0(void *p) { ((LetterGrid *)p)->clearMarks(); }
static inline void func_ov094_022943f8(void *p) { ((LetterGrid *)p)->clearCursorSlot(); }
static inline void func_ov094_0229462c(void *a) { ((LetterGrid *)a)->updateCursorLift(); }
static inline void func_ov094_02294644(void *a, s32 b) { ((LetterGrid *)a)->init((s32)b); }
static inline void func_ov110_02294d68(LostFoundRecycleMenu *s, u32 m) { s->clearFlags((u32)m); }
static inline void func_ov110_02294d78(LostFoundRecycleMenu *s, u32 v) { s->setFlags((u32)v); }
static inline BOOL func_ov110_02294d88(LostFoundRecycleMenu *s, u32 m) { return s->testFlags((u32)m); }
static inline BOOL func_ov110_02294d9c(LostFoundRecycleMenu *s) { return s->isResultSent(); }
static inline void func_ov110_02294e78(LostFoundRecycleMenu *s, u32 v) { s->confirm((s32)v); }
static inline void func_ov110_02294fb8(LostFoundRecycleMenu *s, s32 a) { s->setOkLabel((s32)a); }
static inline void func_ov110_02295034(LostFoundRecycleMenu *s) { s->resetTextLabels(); }
static inline BOOL func_ov110_02295060(LostFoundRecycleMenu *s, u32 a, u32 b) { return s->moveCursorByPad(a, (s32)b); }
static inline void func_ov110_022953b4(LostFoundRecycleMenu *s) { s->cancelChoiceList(); }
static inline void func_ov110_022953e0(LostFoundRecycleMenu *s) { s->applyChoice(); }
static inline void func_ov110_02295404(LostFoundRecycleMenu *s, u32 v) { s->startExchange((u8)v); }
static inline void func_ov110_0229544c(LostFoundRecycleMenu *s, u32 v) { s->startPutDown((u8)v); }
static inline void func_ov110_02295488(LostFoundRecycleMenu *s) { s->startPickUp(); }
static inline void func_ov110_022954a8(LostFoundRecycleMenu *s) { s->releaseCursor(); }
static inline void func_ov110_022954c8(LostFoundRecycleMenu *s) { s->pressCursor(); }
static inline void func_ov110_022954e8(LostFoundRecycleMenu *s) { s->refreshCursor(); }
static inline void func_ov110_02295508(LostFoundRecycleMenu *s) { s->placeCursorAtTarget(); }
static inline void func_ov110_0229553c(LostFoundRecycleMenu *s) { s->placeCursorOnFirstChoice(); }
static inline void func_ov110_02296370(LostFoundRecycleMenu *s) { s->mainAct15(); }
static inline void func_ov110_022963b4(LostFoundRecycleMenu *s) { s->mainAct14(); }
static inline void func_ov110_022963e8(LostFoundRecycleMenu *s) { s->mainAct13(); }
static inline void func_ov110_02296408(LostFoundRecycleMenu *s) { s->mainAct12(); }
static inline void func_ov110_0229644c(LostFoundRecycleMenu *s) { s->mainAct11(); }
static inline void func_ov110_02296488(LostFoundRecycleMenu *s) { s->mainAct10(); }
static inline void func_ov110_022964c0(LostFoundRecycleMenu *s) { s->mainAct0F(); }
static inline void func_ov110_02296510(LostFoundRecycleMenu *s) { s->mainAct0E(); }
static inline void func_ov110_02296558(LostFoundRecycleMenu *s) { s->mainAct0D(); }
static inline void func_ov110_022965ac(LostFoundRecycleMenu *s) { s->mainAct0C(); }
static inline void func_ov110_022965d8(LostFoundRecycleMenu *s) { s->mainAct0B(); }
static inline void func_ov110_02296608(LostFoundRecycleMenu *s) { s->updateCursorRelease(); }
static inline void func_ov110_02296630(LostFoundRecycleMenu *s) { s->updateCursorPress(); }
static inline void func_ov110_02296664(LostFoundRecycleMenu *s) { s->updateCursorMove(); }
static inline void func_ov110_022966b4(LostFoundRecycleMenu *s) { s->mainAct07(); }
static inline void func_ov110_02296700(LostFoundRecycleMenu *s) { s->mainAct06(); }
static inline void func_ov110_02296780(LostFoundRecycleMenu *s) { s->mainAct05(); }
static inline void func_ov110_02296874(LostFoundRecycleMenu *s) { s->mainAct04(); }
static inline void func_ov110_022969ec(LostFoundRecycleMenu *s) { s->mainAct03(); }
static inline void func_ov110_02296b1c(LostFoundRecycleMenu *s) { s->mainAct02(); }
static inline void func_ov110_02296bb8(LostFoundRecycleMenu *s) { s->mainAct01(); }
static inline void func_ov110_02296c0c(LostFoundRecycleMenu *s) { s->mainAct00(); }
static inline void func_ov110_02296f70(LostFoundRecycleMenu *s) { s->transitionAct06(); }
static inline void func_ov110_02296fbc(LostFoundRecycleMenu *s) { s->transitionAct05(); }
static inline void func_ov110_02297024(LostFoundRecycleMenu *s) { s->transitionAct04(); }
static inline void func_ov110_02297094(LostFoundRecycleMenu *s) { s->transitionAct03(); }
static inline void func_ov110_022970cc(LostFoundRecycleMenu *s) { s->transitionAct02(); }
static inline void func_ov110_0229714c(LostFoundRecycleMenu *s) { s->transitionAct01(); }
static inline BOOL func_ov110_0229726c(LostFoundRecycleMenu *s) { return s->isForcedClose(); }
static inline void func_ov110_0229728c(LostFoundRecycleMenu *s) { s->runMainState(); }




extern "C" ProcProfile sLostFoundRecycleMenuProfile = {(void *(*)())LostFoundRecycleMenu_Create, 0x9d, 0xa1};

static inline BOOL Unk_ov110_02296b1c_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) return TRUE;
    return FALSE;
}

static inline BOOL R1(u16 *p, u32 lo, u32 hi)
{
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) {
        r = TRUE;
    }
    return r;
}

extern "C" LostFoundRecycleMenu *LostFoundRecycleMenu_Create() { return new LostFoundRecycleMenu(); }

BOOL LostFoundRecycleMenu::onCreate() {
    LostFoundRecycleMenu_Init(this);
    setTransitionState(0);
    setPhase(0);
    return TRUE;
}

BOOL LostFoundRecycleMenu::onDelete() {
    ((MenuLauncher *)ProcBase_GetParent(this))->onChildClosed();
    LostFoundRecycleMenu_Exit(this);
    return TRUE;
}

BOOL LostFoundRecycleMenu::onDraw() {
    if (!testFlags(1)) {
        return TRUE;
    }
    nameBalloon.draw();
    if (MenuCtrl_IsButtons()) {
        cursor.drawWrapped();
    }
    LostFoundRecycleMenu_DrawHeldItem(this);
    if (testFlags(0x80)) {
        InventoryItemGrid_DrawBox(&itemGrid, 0, boxSlideY);
    }
    if (testFlags(2)) {
        InventoryItemGrid_DrawPockets(&itemGrid, 0, pocketsSlideY);
        letterGrid.drawPocketLetters(0, pocketsSlideY);
        Shared_InventoryBg_DrawSprite(&inventoryBg, pocketsSlideY);
    }
    return TRUE;
}

BOOL LostFoundRecycleMenu::execTransition() {
    static Unk_ov110_02297778_Fn tbl[7] = {
        &LostFoundRecycleMenu::transitionAct00,
        &LostFoundRecycleMenu::transitionAct01,
        &LostFoundRecycleMenu::transitionAct02,
        &LostFoundRecycleMenu::transitionAct03,
        &LostFoundRecycleMenu::transitionAct04,
        &LostFoundRecycleMenu::transitionAct05,
        &LostFoundRecycleMenu::transitionAct06};
    LostFoundRecycleMenu_PreStateUpdate(this);
    (this->*tbl[transitionState])();
    LostFoundRecycleMenu_PostStateUpdate(this);
    return TRUE;
}

void LostFoundRecycleMenu::runMainState() {
    static Unk_ov110_02297778_Fn tbl[22] = {
        &LostFoundRecycleMenu::mainAct00, &LostFoundRecycleMenu::mainAct01,
        &LostFoundRecycleMenu::mainAct02, &LostFoundRecycleMenu::mainAct03,
        &LostFoundRecycleMenu::mainAct04, &LostFoundRecycleMenu::mainAct05,
        &LostFoundRecycleMenu::mainAct06, &LostFoundRecycleMenu::mainAct07,
        &LostFoundRecycleMenu::updateCursorMove, &LostFoundRecycleMenu::updateCursorPress,
        &LostFoundRecycleMenu::updateCursorRelease, &LostFoundRecycleMenu::mainAct0B,
        &LostFoundRecycleMenu::mainAct0C, &LostFoundRecycleMenu::mainAct0D,
        &LostFoundRecycleMenu::mainAct0E, &LostFoundRecycleMenu::mainAct0F,
        &LostFoundRecycleMenu::mainAct10, &LostFoundRecycleMenu::mainAct11,
        &LostFoundRecycleMenu::mainAct12, &LostFoundRecycleMenu::mainAct13,
        &LostFoundRecycleMenu::mainAct14, &LostFoundRecycleMenu::mainAct15};
    (this->*tbl[mainState])();
}

BOOL LostFoundRecycleMenu::isForcedClose() {
    if (MenuCtrl_IsForceCloseDue() && MenuCtrl_GetMode() == 0x20) {
        return TRUE;
    }
    return FALSE;
}

BOOL LostFoundRecycleMenu::execMain() {
    MenuCtrl_TickForceClose();
    if (isForcedClose()) {
        if (mainState == 0 || mainState == 1 || mainState == 4) {
            LostFoundRecycleMenu_HideCursor(this);
            nameBalloon.hide(0);
            confirm(0);
            return TRUE;
        }
    }
    LostFoundRecycleMenu_PreInputUpdate(this);
    runMainState();
    LostFoundRecycleMenu_PostInputUpdate(this);
    return TRUE;
}

BOOL LostFoundRecycleMenu::execPhase3() { return TRUE; }

BOOL LostFoundRecycleMenu::execPhase4() { return TRUE; }

BOOL LostFoundRecycleMenu::execClosed() {
    ProcBase_RequestDelete(this);
    return TRUE;
}

void LostFoundRecycleMenu::transitionAct00() {
    LostFoundRecycleMenu_SetupBgLayers();
    LostFoundRecycleMenu_LoadInventoryBg(this);
    setTransitionState(1);
}

void LostFoundRecycleMenu::transitionAct01() {
    LostFoundRecycleMenu *s = this;
    ::LostFoundRecycleMenu_LoadObjGraphics(s);
    ::Shared_InventoryItemGrid_LoadPockets(&s->itemGrid);
    ::InventoryItemGrid_LoadBox(&s->itemGrid, s->boxItems);
    ::LostFoundRecycleMenu_DisableRejectedItems(s);
    ::Shared_LetterGrid_LoadPocketLetters(&s->letterGrid);
    ::func_ov094_022941f8(&s->letterGrid, 0xf);
    ::func_ov002_022008e0(s, 8, 0, 0, 0x30);
    ::Gfx2d_ShowLayer(6);
    ::func_ov002_02200840(s, 6, 0, 0);
    ::func_ov002_02200a50(s, 2);
    ::func_ov110_02294d78(s, 1);
    ::func_ov110_02294d78(s, 2);
    s->pocketsSlideY = ::func_ov002_02200920(s);
}

void LostFoundRecycleMenu::transitionAct02() {
    LostFoundRecycleMenu *s = this;
    s32 v = ::func_ov002_02200908(s, 0);
    ::func_ov002_02200840(s, 6, 0, 0);
    s->pocketsSlideY = ::func_ov002_02200920(s);
    if (v) {
        ::LostFoundRecycleMenu_LoadTopBg(s);
        ::func_ov002_022008e0(s, 2, 0, 1, 0x30);
        ::func_ov002_02200850(s, 0x80);
        ::func_ov110_02294d78(s, 0x80);
        ::Gfx2d_ShowLayer(4);
        ::func_ov002_02200840(s, 4, 0, 0);
        s->boxSlideY = ::func_ov002_02200920(s);
        ::func_ov002_02200a50(s, 3);
    }
}

void LostFoundRecycleMenu::transitionAct03() {
    LostFoundRecycleMenu *s = this;
    if (::func_ov002_02200908(s, 0)) {
        ::func_ov002_02200a60(s, 2);
        ::LostFoundRecycleMenu_ResumeInput(s);
    }
    ::func_ov002_02200840(s, 4, 0, 0);
    s->boxSlideY = ::func_ov002_02200920(s);
}

void LostFoundRecycleMenu::transitionAct04() {
    LostFoundRecycleMenu *s = this;
    if (::func_ov110_02294d9c(s)) {
        ::func_ov002_022006e4(&s->nameBalloon, 1);
        ::LostFoundRecycleMenu_HideCursor(s);
        ((MenuLauncher *)::ProcBase_GetParent(s))->setNextRequest(0x44, 1);
        ::func_ov002_022008c4(s, 2, 4, 1, 0x30);
        ::func_ov002_02200850(s, 0x80);
        ::func_ov002_02200840(s, 4, 0, 0);
        s->boxSlideY = ::func_ov002_02200920(s);
        ::func_ov002_02200a50(s, 5);
    }
}

void LostFoundRecycleMenu::transitionAct05() {
    LostFoundRecycleMenu *s = this;
    if (::func_ov002_022008fc(s, 0)) {
        ::Gfx2d_ResetLayer(4);
        ::func_ov110_02294d68(s, 0x80);
        ::func_ov002_022008c4(s, 8, 0, 0, 0x30);
        ::func_ov002_02200840(s, 6, 0, 0);
        ::func_ov002_02200a50(s, 6);
        ::func_ov110_02296f70(s);
    } else {
        ::func_ov002_02200840(s, 4, 0, 0);
        s->boxSlideY = ::func_ov002_02200920(s);
    }
}

void LostFoundRecycleMenu::transitionAct06() {
    LostFoundRecycleMenu *s = this;
    if (::func_ov002_022008fc(s, 0)) {
        ::Gfx2d_ResetLayer(6);
        ::func_ov002_02200a60(s, 5);
        ::func_ov110_02294d68(s, 1);
        ::func_ov110_02294d68(s, 2);
    } else {
        ::func_ov002_02200840(s, 6, 0, 0);
    }
    s->pocketsSlideY = ::func_ov002_02200920(s);
}

extern "C" void LostFoundRecycleMenu_Init(LostFoundRecycleMenu *s) {
    s32 i;
    s->stateFlags = 0;
    InventoryItemGrid_Init(&s->itemGrid, 1);
    func_ov094_02294644(&s->letterGrid, 2);
    Shared_InventoryBg_Init(&s->inventoryBg, 6);
    s->balloonSlot = 0x1f;
    func_ov002_022027a4(&s->flyMotion);
    s->heldKind = 0;
    s->cursorSlot = 0;
    s->choiceMenu.init(3, 1, NULL);
    s->numTextLabels = 0;
    switch (MenuCtrl_GetMode()) {
    case 0x1d:
    case 0x1e:
        for (i = 0; i < 15; i++) {
            s->boxItems[i] = 0xfff1;
        }
        func_ov110_02294d78(s, 0x200);
        break;
    case 0x1f:
        MI_CpuCopy8(gSaveData.lostAndFound, s->boxItems, 0x1e);
        break;
    case 0x20:
        MI_CpuCopy8(gSaveData.recycleBin, s->boxItems, 0x1e);
        break;
    }
    MI_CpuCopy8(s->boxItems, s->initialBoxItems, 0x1e);
    MenuCtrl_BackupPockets();
}

extern "C" void LostFoundRecycleMenu_Exit(LostFoundRecycleMenu *s) {
    LostFoundRecycleMenu_CancelUploads(s);
    InventoryBg_Exit(&s->inventoryBg);
    Shared_InventoryItemGrid_Exit(&s->itemGrid);
    PopupChoice_ForceClose(&s->choiceMenu);
    func_ov110_02295034(s);
}

extern "C" void LostFoundRecycleMenu_PreInputUpdate(LostFoundRecycleMenu *s) {
    LostFoundRecycleMenu_PreStateUpdate(s);
    (&s->cursor)->update();
}

extern "C" void LostFoundRecycleMenu_PostInputUpdate(LostFoundRecycleMenu *s) {
    LostFoundRecycleMenu_PostStateUpdate(s);
}

extern "C" void LostFoundRecycleMenu_PreStateUpdate(LostFoundRecycleMenu *s) {
    LostFoundRecycleMenu_CancelUploads(s);
    Shared_InventoryBg_PreUpdate(&s->inventoryBg);
    InventoryItemGrid_PreUpdate(&s->itemGrid);
    func_ov094_0229462c(&s->letterGrid);
    func_ov110_02295034(s);
}

extern "C" void LostFoundRecycleMenu_PostStateUpdate(LostFoundRecycleMenu *s) {
    Shared_PopupChoice_Update(&s->choiceMenu);
    InventoryBg_Update(&s->inventoryBg);
    if (func_ov002_0220071c(&s->nameBalloon)) {
        LostFoundRecycleMenu_PlaceNameBalloon(s);
    }
}

void LostFoundRecycleMenu_SetupBgLayers() {
    Gfx2d_SetLayerPriority(6, 2);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
    Gfx2d_SetLayerPriority(4, 1);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
}

extern "C" void LostFoundRecycleMenu_LoadInventoryBg(LostFoundRecycleMenu *s) {
    InventoryBg_Load(&s->inventoryBg, 0);
}

extern "C" void LostFoundRecycleMenu_LoadTopBg(LostFoundRecycleMenu *s) {
    void *h = gCurrentHeap;
    Gfx2d_LoadScreenFile("menu/inventory/b_itm_bg_tra2.bsc", h, 4);
    Gfx2d_LoadCharFile("menu/inventory/b_itm_sell.bch", h, 4, 0x1b9, 0x1b9, 0x238);
    s32 v = MenuCtrl_GetMode();
    const char *a = NULL;
    const char *b = NULL;
    switch (v) {
    case 0x1d:
        a = "menu/inventory/ten6.bpl";
        b = "menu/inventory/tanu.bch";
        break;
    case 0x1e:
        a = "menu/inventory/ten7.bpl";
        b = "menu/inventory/kinu.bch";
        break;
    case 0x1f:
        a = "menu/inventory/ten8.bpl";
        b = "menu/inventory/lost.bch";
        break;
    case 0x20:
        a = "menu/inventory/ten9.bpl";
        b = "menu/inventory/garb.bch";
        break;
    }
    if (a != NULL) {
        Gfx2d_LoadPaletteFile(a, h, 4, 3, 3, 5);
    }
    if (b != NULL) {
        Gfx2d_LoadCharFile(b, h, 4, 0x208, 0x208, 0x238);
    }
    func_ov110_02294fb8(s, 0);
}

extern "C" void LostFoundRecycleMenu_LoadObjGraphics(LostFoundRecycleMenu *s) {
    InventoryBg_LoadObjGraphics();
}

void LostFoundRecycleMenu::mainAct00() {
    LostFoundRecycleMenu *s = this;
    if (::func_ov002_02200a14(s, 1)) {
        ::LostFoundRecycleMenu_StartButtonInput(s);
    } else {
        if (Unk_ov110_02296b1c_Both()) {
            s32 x = gTouchCurX;
            s32 y = gTouchCurY;
            s32 r = ::LostFoundRecycleMenu_FindSlotAt(s, x, y, 1);
            if (r != 0x1f) {
                ::LostFoundRecycleMenu_TouchItem(s, r);
            } else if (x >= 0xc8 && x <= 0xf8 && y >= 0x60 && y <= 0x70) {
                ::func_ov110_02294e78(s, 1);
            }
        }
    }
}

void LostFoundRecycleMenu::mainAct01() {
    LostFoundRecycleMenu *s = this;
    if (gTouchHeld == 0) {
        ::func_ov002_02200a58(s, 0);
        ::func_ov002_022006a4(&s->nameBalloon, 0x3c);
    } else if (::func_ov110_02294d88(s, 4) && ::LostFoundRecycleMenu_HasTouchMoved(s)) {
        ::LostFoundRecycleMenu_PickUpWithTouch(s, s->touchedSlot);
    } else {
        ::func_ov002_022006c0(&s->nameBalloon);
    }
}

void LostFoundRecycleMenu::mainAct02() {
    LostFoundRecycleMenu *s = this;
    if (::func_ov110_0229726c(s)) {
        ::func_ov110_022953b4(s);
    } else if (::func_ov002_02200a14(s, 1)) {
        ::func_ov110_022953b4(s);
    } else {
        if (Unk_ov110_02296b1c_Both()) {
            s32 t = ::func_ov002_022014c0(&s->choiceMenu, gTouchCurX, gTouchCurY);
            if (t >= 0) {
                ::PopupChoice_DecideRow(&s->choiceMenu, t, 1);
                s->chosenAction = s->choiceList.values[t];
                ::func_ov002_02200a58(s, 0x12);
            }
        }
    }
}

void LostFoundRecycleMenu::mainAct03() {
    LostFoundRecycleMenu *s = this;
    if (::func_ov110_0229726c(s)) {
        ::LostFoundRecycleMenu_ReleaseHeldItem(s, s->pickUpSlot);
        ::LostFoundRecycleMenu_HideCursor(s);
        ::func_ov002_022006e4(&s->nameBalloon, 0);
        ::func_ov110_02294e78(s, 0);
    } else {
        ::LostFoundRecycleMenu_TrackTouch(s);
        ::LostFoundRecycleMenu_ClearMarks(s);
        s32 x = s->heldY + 8;
        s32 t = ::LostFoundRecycleMenu_FindSlotAt(s, s->heldX + 8, x, 0);
        if (::func_ov110_02294d88(s, 0x200)) {
            if ((::LostFoundRecycleMenu_IsBoxSlot(s, t) && ::LostFoundRecycleMenu_IsPocketSlot(s, s->pickUpSlot))
                || (::LostFoundRecycleMenu_IsPocketSlot(s, t) && ::LostFoundRecycleMenu_IsBoxSlot(s, s->pickUpSlot))) {
                if (::LostFoundRecycleMenu_GetSlotItem(s, t) != 0xfff1) {
                    t = 0x1f;
                }
            }
        }
        if (t != 0x1f) {
            if (gTouchHeld == 0) {
                if (::LostFoundRecycleMenu_IsSlotDisabled(s, t)) {
                    ::LostFoundRecycleMenu_FlyHeldToFreeSlot(s, s->pickUpSlot, x);
                } else {
                    s32 r = ::LostFoundRecycleMenu_DropHeldItem(s, t);
                    if (r == 0) {
                        ::LostFoundRecycleMenu_FlyHeldToFreeSlot(s, s->pickUpSlot, x);
                    } else {
                        ::Inventory_PlayPutDownSe();
                        ::LostFoundRecycleMenu_ResumeInput(s);
                    }
                }
            } else {
                ::LostFoundRecycleMenu_MarkSlot(s, t);
            }
        } else if (gTouchHeld == 0) {
            ::LostFoundRecycleMenu_FlyHeldToFreeSlot(s, s->pickUpSlot, x);
        }
    }
}

void LostFoundRecycleMenu::mainAct04() {
    LostFoundRecycleMenu *s = this;
    if (::func_ov002_022009d4(s)) {
        ::LostFoundRecycleMenu_StartTouchInput(s);
        ::func_ov002_022006e4(&s->nameBalloon, 1);
    } else {
        s32 v = ::func_ov002_022009c8(s);
        if (::func_ov110_02295060(s, v, 0)) {
            ::LostFoundRecycleMenu_UpdateNameBalloon(s);
            ::LostFoundRecycleMenu_MoveCursorToTarget(s);
            ::func_ov002_022006e4(&s->nameBalloon, 0);
        } else {
            if (::LostFoundRecycleMenu_IsSlotDisabled(s, s->cursorSlot) != 0) goto tail;
            {
                u32 k = gPad[1];
                if (k & 1) {
                    if (::LostFoundRecycleMenu_IsPocketSlot(s, s->cursorSlot) || ::LostFoundRecycleMenu_IsBoxSlot(s, s->cursorSlot)) {
                        if (!::LostFoundRecycleMenu_IsSlotEmpty(s, s->cursorSlot)) {
                            ::func_ov110_02295488(s);
                        }
                    } else if (::LostFoundRecycleMenu_IsButtonSlot(s, s->cursorSlot)) {
                        ::func_ov110_022954c8(s);
                    }
                } else if (k & 0x800) {
                    if (::LostFoundRecycleMenu_IsPocketSlot(s, s->cursorSlot) || ::LostFoundRecycleMenu_IsBoxSlot(s, s->cursorSlot)) {
                        if (!::LostFoundRecycleMenu_IsSlotEmpty(s, s->cursorSlot)) {
                            s32 r = ::LostFoundRecycleMenu_IsPocketSlot(s, s->cursorSlot) ? ::LostFoundRecycleMenu_FindFreeBoxSlot(s) : ::LostFoundRecycleMenu_FindFreePocket(s);
                            if (r != 0x1f) {
                                ::LostFoundRecycleMenu_QuickMove(s, s->cursorSlot, r);
                                ::func_ov002_022006e4(&s->nameBalloon, 1);
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
                    ::LostFoundRecycleMenu_HideCursor(s);
                    ::func_ov002_022006e4(&s->nameBalloon, 0);
                    ::func_ov110_02294e78(s, 1);
                } else {
                    ::func_ov002_022006c0(&s->nameBalloon);
                }
            }
        }
    }
}

void LostFoundRecycleMenu::mainAct05() {
    LostFoundRecycleMenu *s = this;
    if (::func_ov110_0229726c(s)) {
        ::LostFoundRecycleMenu_ReleaseHeldItem(s, s->pickUpSlot);
        ::LostFoundRecycleMenu_HideCursor(s);
        ::func_ov002_022006e4(&s->nameBalloon, 0);
        ::func_ov110_02294e78(s, 0);
    } else if (::func_ov110_02295060(s, ::func_ov002_022009c8(s), 1)) {
        ::LostFoundRecycleMenu_UpdateNameBalloon(s);
        ::LostFoundRecycleMenu_MoveCursorToTarget(s);
        ::func_ov002_022006e4(&s->nameBalloon, 0);
    } else {
        u32 k = gPad[1];
        if ((k & 1) != 0) {
            if (::LostFoundRecycleMenu_IsPocketSlot(s, s->cursorSlot) || ::LostFoundRecycleMenu_IsBoxSlot(s, s->cursorSlot)) {
                if (!::LostFoundRecycleMenu_IsSlotDisabled(s, s->cursorSlot)) {
                    if (::LostFoundRecycleMenu_IsSlotEmpty(s, s->cursorSlot)) {
                        ::func_ov110_0229544c(s, s->cursorSlot);
                    } else {
                        ::func_ov110_02295404(s, s->cursorSlot);
                    }
                }
            }
        } else if ((k & 2) != 0) {
            ::func_ov110_0229544c(s, s->pickUpSlot);
        } else {
            ::LostFoundRecycleMenu_TrackCursor(s);
            ::func_ov002_022006c0(&s->nameBalloon);
        }
    }
}

void LostFoundRecycleMenu::mainAct06() {
    LostFoundRecycleMenu *s = this;
    if (::func_ov002_022009d4(s) || ::func_ov110_0229726c(s)) {
        ::func_ov110_022953b4(s);
    } else if (::PopupChoice_MoveCursor(&s->choiceMenu, ::func_ov002_022009c8(s), &s->choiceRow, 0)) {
        ::LostFoundRecycleMenu_MoveCursorToChoice(s);
    } else {
        u32 k = gPad[1];
        if ((k & 1) != 0) {
            ::func_ov002_02202b68(&s->cursor);
            ::func_ov002_02200a58(s, 7);
        } else if ((k & 2) != 0) {
            ::LostFoundRecycleMenu_PickCancelChoice(s);
        }
    }
}

void LostFoundRecycleMenu::mainAct07() {
    LostFoundRecycleMenu *s = this;
    if (::func_0208d4fc(&s->cursor)) {
        ::PopupChoice_DecideRow(&s->choiceMenu, s->choiceRow, 1);
        s->chosenAction = s->choiceList.values[s->choiceRow];
        ::func_ov002_02200a58(s, 0x12);
    }
}

void LostFoundRecycleMenu::updateCursorMove() {
    LostFoundRecycleMenu *s = this;
    if (!::func_ov002_022028f0(&s->cursor)) {
        ::func_ov002_02200a58(s, s->returnState);
        if ((u8)(s->returnState + 0xfc) <= 1) {
            ::LostFoundRecycleMenu_SetCursorSlot(s, s->cursorSlot);
        }
        ::func_ov110_0229728c(s);
    }
    ::LostFoundRecycleMenu_TrackCursor(s);
}

void LostFoundRecycleMenu::updateCursorPress() {
    LostFoundRecycleMenu *s = this;
    if (::func_0208d4fc(&s->cursor)) {
        u32 t = s->cursorSlot;
        if (t == 0x1e) {
            ::func_ov110_02294e78(s, 1);
        } else {
            ::func_ov110_022954a8(s);
        }
    }
}

void LostFoundRecycleMenu::updateCursorRelease() {
    LostFoundRecycleMenu *s = this;
    if (::func_0208d4fc(&s->cursor)) {
        ::func_ov110_022954e8(s);
        ::func_ov002_02200a58(s, 4);
    }
}

void LostFoundRecycleMenu::mainAct0B() {
    LostFoundRecycleMenu *s = this;
    if (::MenuCursor_IsGripping(&s->cursor)) {
        ::LostFoundRecycleMenu_PickUpWithHand(s, s->cursorSlot);
        ::func_ov002_02200a58(s, 0xc);
    }
}

void LostFoundRecycleMenu::mainAct0C() {
    LostFoundRecycleMenu *s = this;
    if (::func_0208d4fc(&s->cursor)) {
        ::func_ov002_02200a58(s, s->returnState);
    }
    ::LostFoundRecycleMenu_TrackCursor(s);
}

void LostFoundRecycleMenu::mainAct0D() {
    LostFoundRecycleMenu *s = this;
    if (!::MenuCursor_IsGripping(&s->cursor)) {
        u32 a = s->actionSlot;
        if (s->cursorSlot == a) {
            ::LostFoundRecycleMenu_DropHeldItem(s, a);
            ::LostFoundRecycleMenu_UpdateNameBalloon(s);
            ::func_ov002_02200a58(s, 4);
            ::Inventory_PlayPutDownSe();
        } else {
            ::LostFoundRecycleMenu_StartFlyHeldItem(s, a, 4);
        }
    } else {
        ::LostFoundRecycleMenu_TrackCursor(s);
    }
}

void LostFoundRecycleMenu::mainAct0E() {
    LostFoundRecycleMenu *s = this;
    if (!::func_ov002_022028fc(&s->cursor)) {
        ::LostFoundRecycleMenu_ExchangeHeldItem(s, s->actionSlot);
        ::func_ov110_02294d78(s, 0x40);
        ::func_ov002_02200a58(s, 0xf);
        ::LostFoundRecycleMenu_UpdateNameBalloon(s);
    } else {
        ::func_ov002_02200a58(s, 4);
    }
}

void LostFoundRecycleMenu::mainAct0F() {
    LostFoundRecycleMenu *s = this;
    if (::func_0208d4fc(&s->cursor)) {
        ::func_ov002_02200a58(s, s->returnState);
    }
    if (::MenuCursor_IsGripping(&s->cursor)) {
        if (::func_ov110_02294d88(s, 0x40)) {
            ::func_ov110_02294d68(s, 0x40);
            ::Shared_Inventory_PlayPickUpSe();
        }
        ::LostFoundRecycleMenu_TrackCursor(s);
    }
}

void LostFoundRecycleMenu::mainAct10() {
    LostFoundRecycleMenu *s = this;
    if (::func_ov002_02202718(&s->flyMotion)) {
        ::LostFoundRecycleMenu_ReleaseHeldItem(s, s->pickUpSlot);
        ::LostFoundRecycleMenu_ResumeInput(s);
        ::Inventory_PlayPutDownSe();
    } else {
        ::LostFoundRecycleMenu_TrackFlyingItem(s);
    }
}

void LostFoundRecycleMenu::mainAct11() {
    LostFoundRecycleMenu *s = this;
    if (::func_ov002_022017b4(&s->choiceMenu)) {
        if (::MenuCtrl_IsButtons()) {
            ::func_ov110_0229553c(s);
            ::func_ov002_02200a58(s, 6);
        } else {
            ::func_ov002_02200a58(s, 2);
        }
    }
}

void LostFoundRecycleMenu::mainAct12() {
    LostFoundRecycleMenu *s = this;
    if (::PopupChoice_TickDecideDelay(&s->choiceMenu)) {
        ::PopupChoice_Close(&s->choiceMenu, 0);
        if (::func_0208d534(&s->cursor)) {
            ::func_ov110_02295508(s);
        }
        ::func_ov002_02200a58(s, 0x13);
    }
}

void LostFoundRecycleMenu::mainAct13() {
    LostFoundRecycleMenu *s = this;
    if (::func_ov002_022017a4(&s->choiceMenu)) {
        ::func_ov110_022953e0(s);
    }
}

void LostFoundRecycleMenu::mainAct14() {
    LostFoundRecycleMenu *s = this;
    if (s->errorMessage.update(1)) {
        ::func_ov002_02200a58(s, s->returnState);
        ::func_0208d644(&s->cursor);
    }
}

void LostFoundRecycleMenu::mainAct15() {
    LostFoundRecycleMenu *s = this;
    if (s->delayTimer != 0) {
        s->delayTimer--;
    } else {
        s->transitionState = 4;
        ::func_ov002_02200a60(s, 1);
        ::func_ov002_022006e4(&s->nameBalloon, 0);
        ::LostFoundRecycleMenu_HideCursor(s);
    }
}

extern "C" void LostFoundRecycleMenu_StartTouchInput(LostFoundRecycleMenu *s) {
    LostFoundRecycleMenu_HideCursor(s);
    LostFoundRecycleMenu_ClearCursorSlots(s);
    func_ov002_02200a58(s, 0);
}

extern "C" void LostFoundRecycleMenu_StartButtonInput(LostFoundRecycleMenu *s) {
    s->balloonSlot = 0x1f;
    LostFoundRecycleMenu_ShowCursor(s);
    func_ov002_02200980(s);
    LostFoundRecycleMenu_UpdateNameBalloon(s);
    func_ov002_02200a58(s, 4);
    LostFoundRecycleMenu_SetCursorSlot(s, s->cursorSlot);
}

extern "C" void LostFoundRecycleMenu_ResumeInput(LostFoundRecycleMenu *s) {
    if (MenuCtrl_IsTouch()) {
        LostFoundRecycleMenu_StartTouchInput(s);
    } else {
        LostFoundRecycleMenu_StartButtonInput(s);
    }
}

extern "C" void LostFoundRecycleMenu_TouchItem(LostFoundRecycleMenu *s, u32 a) {
    u32 r6, r7;
    s->touchedSlot = a;
    func_ov002_02200a58(s, 1);
    r6 = gTouchCurX;
    r7 = gTouchCurY;
    s->grabOffsetX = LostFoundRecycleMenu_GetSlotX(s, s->touchedSlot) - r6;
    s->grabOffsetY = LostFoundRecycleMenu_GetSlotY(s, s->touchedSlot) - r7;
    s->balloonSlot = a;
    func_ov002_022006b8(&s->nameBalloon);
    if (LostFoundRecycleMenu_IsSlotDisabled(s, a)) {
        func_ov110_02294d68(s, 4);
    } else {
        func_ov110_02294d78(s, 4);
        Inventory_PlayTouchSe();
    }
}

extern "C" void LostFoundRecycleMenu_PickUpWithTouch(LostFoundRecycleMenu *s, u32 a) {
    s->pickUpSlot = a;
    func_ov002_022006e4(&s->nameBalloon, 1);
    LostFoundRecycleMenu_PickUpItem(s, a);
    if (s->heldKind == 1) {
        func_ov002_02200a58(s, 3);
    }
    LostFoundRecycleMenu_TrackTouch(s);
    Shared_Inventory_PlayPickUpSe();
}

extern "C" void LostFoundRecycleMenu_PickUpWithHand(LostFoundRecycleMenu *s, u32 a) {
    s->pickUpSlot = a;
    func_ov002_022006e4(&s->nameBalloon, 1);
    LostFoundRecycleMenu_PickUpItem(s, a);
    if (s->heldKind == 1) {
        s->returnState = 5;
    }
    LostFoundRecycleMenu_TrackCursor(s);
    Shared_Inventory_PlayPickUpSe();
}

extern "C" void LostFoundRecycleMenu_StartFlyHeldItem(LostFoundRecycleMenu *s, u32 a, u32 b) {
    s->pickUpSlot = a;
    func_ov002_022026f4(&s->flyMotion, s->heldX, s->heldY);
    u32 x = LostFoundRecycleMenu_GetSlotX(s, a);
    u32 y = LostFoundRecycleMenu_GetSlotY(s, a);
    func_ov002_022026c4(&s->flyMotion, x, y, b);
    func_ov002_02202718(&s->flyMotion);
    LostFoundRecycleMenu_TrackFlyingItem(s);
    func_ov002_02200a58(s, 0x10);
}

extern "C" void LostFoundRecycleMenu_FlyHeldToFreeSlot(LostFoundRecycleMenu *s, u32 a, s32 b) {
    u32 r = 0x1f;
    if (b >= 0x6c) {
        if (LostFoundRecycleMenu_IsBoxSlot(s, a)) r = LostFoundRecycleMenu_FindFreePocket(s);
    } else {
        if (LostFoundRecycleMenu_IsPocketSlot(s, a)) r = LostFoundRecycleMenu_FindFreeBoxSlot(s);
    }
    if (r != 0x1f) a = r;
    LostFoundRecycleMenu_StartFlyHeldItem(s, a, 4);
}

extern "C" void LostFoundRecycleMenu_QuickMove(LostFoundRecycleMenu *s, u32 a, u32 b) {
    LostFoundRecycleMenu_PickUpItem(s, a);
    s->heldX = LostFoundRecycleMenu_GetSlotX(s, a);
    s->heldY = LostFoundRecycleMenu_GetSlotY(s, a);
    LostFoundRecycleMenu_StartFlyHeldItem(s, b, 4);
}

extern "C" u32 LostFoundRecycleMenu_FindFreePocket(LostFoundRecycleMenu *s) {
    s32 t = Pocket_FindEmpty();
    s32 m = -1;
    if (t == m) return 0x1f;
    return (u8)t;
}

extern "C" u32 LostFoundRecycleMenu_FindFreeBoxSlot(LostFoundRecycleMenu *s) {
    s32 i;
    for (i = 0; i < 0xf; i++) {
        if (s->boxItems[i] == 0xfff1) return (u8)(i + 0xf);
    }
    return 0x1f;
}

extern "C" void LostFoundRecycleMenu_CancelUploads(LostFoundRecycleMenu *s) {
    func_020b87d0(s->vramTask);
}

extern "C" BOOL LostFoundRecycleMenu_IsPocketSlot(LostFoundRecycleMenu *s, u32 a) {
    if (a <= 0xe) return TRUE;
    return FALSE;
}

extern "C" BOOL LostFoundRecycleMenu_IsBoxSlot(LostFoundRecycleMenu *s, u32 a) {
    if (a >= 0xf && a <= 0x1d) return TRUE;
    return FALSE;
}

extern "C" BOOL LostFoundRecycleMenu_IsButtonSlot(LostFoundRecycleMenu *s, u32 a) {
    if (a == 0x1e) return TRUE;
    return FALSE;
}

extern "C" u32 LostFoundRecycleMenu_ToGridSlot(LostFoundRecycleMenu *s, u32 a) {
    if (LostFoundRecycleMenu_IsPocketSlot(s, a)) return (u8)a;
    if (LostFoundRecycleMenu_IsBoxSlot(s, a)) return LostFoundRecycleMenu_GridToBoxSlotOr0F(s, a);
    return 0;
}

extern "C" u32 LostFoundRecycleMenu_GridToPocketSlot(LostFoundRecycleMenu *s, u32 a) {
    if (a <= 0xe) return (u8)a;
    return 0x1f;
}

extern "C" u32 LostFoundRecycleMenu_FindSlotAt(LostFoundRecycleMenu *s, u32 a, u32 b, s32 c) {
    u32 t = InventoryItemGrid_FindPocketSlotAt(&s->itemGrid, a, b);
    if (t != 0x23) {
        if (c != 0) {
            if (InventoryItemGrid_IsSlotEmpty(&s->itemGrid, t)) return 0x1f;
        }
        return LostFoundRecycleMenu_GridToPocketSlot(s, t);
    }
    t = Shared_InventoryItemGrid_FindBoxSlotAt(&s->itemGrid, a, b);
    if (t != 0x23) {
        if (c != 0) {
            if (InventoryItemGrid_IsSlotEmpty(&s->itemGrid, t)) return 0x1f;
        }
        return LostFoundRecycleMenu_GridToBoxSlot(s, t);
    }
    return 0x1f;
}

extern "C" BOOL LostFoundRecycleMenu_DropHeldItem(LostFoundRecycleMenu *s, u32 a) {
    if (LostFoundRecycleMenu_IsPocketSlot(s, a) || LostFoundRecycleMenu_IsBoxSlot(s, a)) {
        u32 t = LostFoundRecycleMenu_GetSlotItem(s, a);
        if (t != 0xfff1) {
            LostFoundRecycleMenu_SetSlotItem(s, s->pickUpSlot, t, LostFoundRecycleMenu_GetSlotFlags(s, a));
        }
        LostFoundRecycleMenu_ReleaseHeldItem(s, a);
        return TRUE;
    }
    return FALSE;
}

extern "C" void LostFoundRecycleMenu_SetSlotItem(LostFoundRecycleMenu *s, u32 a, u32 b, u32 c) {
    if (LostFoundRecycleMenu_IsPocketSlot(s, a) || LostFoundRecycleMenu_IsBoxSlot(s, a)) {
        u32 t = LostFoundRecycleMenu_ToGridSlot(s, a);
        InventoryItemGrid_SetSlotItem(&s->itemGrid, t, b, c);
        InventoryItemGrid_RefreshSlot(&s->itemGrid, t);
    }
}

extern "C" u32 LostFoundRecycleMenu_GridToBoxSlotOr0F(LostFoundRecycleMenu *s, u32 a) {
    if (LostFoundRecycleMenu_IsBoxSlot(s, a)) return (u8)a;
    return 0xf;
}

extern "C" u32 LostFoundRecycleMenu_GridToBoxSlot(LostFoundRecycleMenu *s, u32 a) {
    if (a >= 0xf && a <= 0x1d) return (u8)a;
    return 0x1f;
}

extern "C" u32 LostFoundRecycleMenu_GetSlotX(LostFoundRecycleMenu *s, u32 a) {
    if (LostFoundRecycleMenu_IsPocketSlot(s, a) || LostFoundRecycleMenu_IsBoxSlot(s, a)) {
        return InventoryItemGrid_GetSlotX(&s->itemGrid, LostFoundRecycleMenu_ToGridSlot(s, a));
    }
    if (LostFoundRecycleMenu_IsButtonSlot(s, a)) return 0xc4;
    return 0;
}

extern "C" s32 LostFoundRecycleMenu_GetSlotY(LostFoundRecycleMenu *s, u32 a)
{
    if (LostFoundRecycleMenu_IsPocketSlot(s, a) || LostFoundRecycleMenu_IsBoxSlot(s, a)) {
        return InventoryItemGrid_GetSlotY(&s->itemGrid, LostFoundRecycleMenu_ToGridSlot(s, a));
    }
    if (LostFoundRecycleMenu_IsButtonSlot(s, a)) {
        return 0x68;
    }
    return 0;
}

extern "C" BOOL LostFoundRecycleMenu_IsItemRejected(LostFoundRecycleMenu *s, u32 a)
{
    volatile u16 v;
    if (LostFoundRecycleMenu_IsSlotEmpty(s, a)) {
        return FALSE;
    }
    if (LostFoundRecycleMenu_GetSlotFlags(s, a)) {
        return TRUE;
    }
    u32 t = LostFoundRecycleMenu_GetSlotItem(s, a);
    if (Shared_InvItem_IsNonTransferable(t)) {
        return TRUE;
    }
    v = t;
    switch (MenuCtrl_GetMode()) {
    case 0x1e: {
        BOOL f = FALSE;
        u16 x = v;
        u16 y = v;
        if (y >= 0x1492 && x <= 0x14fd) f = TRUE;
        if (f) return TRUE;
        if ((x >= 0x11a8 && x <= 0x12a7) || (x >= 0x13c8 && x <= 0x1407) || (x >= 0x13a8 && x <= 0x13c7)
            || (x >= 0x1408 && x <= 0x1428) || (x >= 0x1431 && x <= 0x1470) || (x >= 0x1471 && x <= 0x1491)
            || (x >= 0x1380 && x <= 0x139f)) {
            return FALSE;
        }
        return TRUE;
    }
    case 0x1d: {
        BOOL f = FALSE;
        u16 x = v;
        u16 y = v;
        if (y >= 0x1492 && x <= 0x14fd) f = TRUE;
        if (f) return TRUE;
        if (!Clock_GetWeekday()) {
            BOOL g = FALSE;
            u16 x2 = v;
            u16 y2 = v;
            if (y2 >= 0x1531 && x2 <= 0x153a) g = TRUE;
            if (g) return TRUE;
        }
        return FALSE;
    }
    case 0x1f:
        return TRUE;
    case 0x20:
        if (Shared_InvItem_IsTurnipFishOrInsect(t)) {
            BOOL f = FALSE;
            u16 x = v;
            u16 y = v;
            if (y >= 0x1531 && x <= 0x153a) f = TRUE;
            if (f || (x >= 0x153b && x <= 0x1541) || (x >= 0x154a && x <= 0x1553)) {
                return FALSE;
            }
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

extern "C" void LostFoundRecycleMenu_DisableRejectedItems(LostFoundRecycleMenu *s)
{
    u32 i = 0;
    do {
        if (LostFoundRecycleMenu_IsItemRejected(s, i)) {
            InventoryItemGrid_DisableSlot(&s->itemGrid, LostFoundRecycleMenu_ToGridSlot(s, i));
        }
        i = (u8)(i + 1);
    } while (i <= 0xe);
}

extern "C" BOOL LostFoundRecycleMenu_IsSlotDisabled(LostFoundRecycleMenu *s, u32 a)
{
    if (LostFoundRecycleMenu_IsPocketSlot(s, a) || LostFoundRecycleMenu_IsBoxSlot(s, a)) {
        return Shared_InventoryItemGrid_IsSlotDisabled(&s->itemGrid, LostFoundRecycleMenu_ToGridSlot(s, a));
    }
    return FALSE;
}

extern "C" BOOL LostFoundRecycleMenu_IsSlotEmpty(LostFoundRecycleMenu *s, u32 a)
{
    if (LostFoundRecycleMenu_IsPocketSlot(s, a) || LostFoundRecycleMenu_IsBoxSlot(s, a)) {
        return InventoryItemGrid_IsSlotEmpty(&s->itemGrid, LostFoundRecycleMenu_ToGridSlot(s, a));
    }
    return TRUE;
}

extern "C" u32 LostFoundRecycleMenu_GetSlotItem(LostFoundRecycleMenu *s, u32 a)
{
    if (LostFoundRecycleMenu_IsPocketSlot(s, a) || LostFoundRecycleMenu_IsBoxSlot(s, a)) {
        return Shared_InventoryItemGrid_GetSlotItem(&s->itemGrid, LostFoundRecycleMenu_ToGridSlot(s, a));
    }
    return 0xfff1;
}

extern "C" u32 LostFoundRecycleMenu_GetSlotFlags(LostFoundRecycleMenu *s, u32 a)
{
    if (LostFoundRecycleMenu_IsPocketSlot(s, a) || LostFoundRecycleMenu_IsBoxSlot(s, a)) {
        return InventoryItemGrid_GetSlotFlags(&s->itemGrid, LostFoundRecycleMenu_ToGridSlot(s, a));
    }
    return 0xf1;
}

extern "C" void LostFoundRecycleMenu_ClearCursorSlots(LostFoundRecycleMenu *s)
{
    InventoryItemGrid_ClearCursorSlot(&s->itemGrid);
    func_ov094_022943f8(&s->letterGrid);
}

extern "C" void LostFoundRecycleMenu_SetCursorSlot(LostFoundRecycleMenu *s, u32 a)
{
    if (LostFoundRecycleMenu_IsPocketSlot(s, a) || LostFoundRecycleMenu_IsBoxSlot(s, a)) {
        Shared_InventoryItemGrid_SetCursorSlot(&s->itemGrid, LostFoundRecycleMenu_ToGridSlot(s, a));
        func_ov094_022943f8(&s->letterGrid);
    } else if (LostFoundRecycleMenu_IsButtonSlot(s, a)) {
        LostFoundRecycleMenu_ClearCursorSlots(s);
    }
}

extern "C" void LostFoundRecycleMenu_ClearMarks(LostFoundRecycleMenu *s)
{
    Shared_InventoryItemGrid_ClearMarks(&s->itemGrid);
    func_ov094_022943b0(&s->letterGrid);
}

extern "C" void LostFoundRecycleMenu_MarkSlot(LostFoundRecycleMenu *s, u32 a)
{
    if (LostFoundRecycleMenu_IsPocketSlot(s, a) || LostFoundRecycleMenu_IsBoxSlot(s, a)) {
        InventoryItemGrid_MarkSlot(&s->itemGrid, LostFoundRecycleMenu_ToGridSlot(s, a));
    }
}

extern "C" BOOL LostFoundRecycleMenu_HasTouchMoved(LostFoundRecycleMenu *s)
{
    s32 d = gTouchPressX - gTouchCurX;
    if (d < 0) d = -d;
    if (d > 8) return TRUE;
    d = gTouchPressY - gTouchCurY;
    if (d < 0) d = -d;
    if (d > 8) return TRUE;
    return FALSE;
}

extern "C" void LostFoundRecycleMenu_PlaceNameBalloon(LostFoundRecycleMenu *s)
{
    s32 a = LostFoundRecycleMenu_GetSlotX(s, s->balloonSlot) - 0x6d;
    s32 b = LostFoundRecycleMenu_GetSlotY(s, s->balloonSlot) - 0x78;
    if (MenuCtrl_IsButtons()) {
        b -= 8;
    }
    if (b < -0x5c) {
        func_02089af8(&s->nameBalloon);
        b = LostFoundRecycleMenu_GetSlotY(s, s->balloonSlot) - 0x50;
    } else {
        func_02089af0(&s->nameBalloon);
    }
    func_02089ad8(&s->nameBalloon, a, b);
    if (LostFoundRecycleMenu_IsPocketSlot(s, s->balloonSlot) || LostFoundRecycleMenu_IsBoxSlot(s, s->balloonSlot)) {
        u32 t = LostFoundRecycleMenu_ToGridSlot(s, s->balloonSlot);
        Shared_InventoryItemGrid_ShowSlotName(&s->itemGrid, &s->nameBalloon, t);
    }
}

extern "C" void LostFoundRecycleMenu_UpdateNameBalloon(LostFoundRecycleMenu *s)
{
    if (LostFoundRecycleMenu_IsPocketSlot(s, s->cursorSlot) || LostFoundRecycleMenu_IsBoxSlot(s, s->cursorSlot)) {
        if (LostFoundRecycleMenu_IsSlotEmpty(s, s->cursorSlot)) {
            func_ov002_022006b0(&s->nameBalloon);
        } else {
            s->balloonSlot = s->cursorSlot;
            func_ov002_022006b8(&s->nameBalloon);
        }
    } else {
        func_ov002_022006b0(&s->nameBalloon);
    }
}

extern "C" void LostFoundRecycleMenu_DrawHeldItem(LostFoundRecycleMenu *s)
{
    if (!func_ov110_02294d88(s, 0x40)) {
        u32 t = s->heldKind;
        if (t != 0) {
            if (t == 1) {
                InventoryItemGrid_DrawHeldItem(&s->itemGrid, s->heldX, s->heldY);
            }
        }
    }
}

extern "C" void LostFoundRecycleMenu_TrackTouch(LostFoundRecycleMenu *s)
{
    s->heldX = s->grabOffsetX + gTouchCurX;
    s->heldY = s->grabOffsetY + gTouchCurY;
}

extern "C" void LostFoundRecycleMenu_TrackCursor(LostFoundRecycleMenu *s)
{
    s->heldX = func_ov002_022028c8(&s->cursor) - 2;
    s->heldY = func_ov002_022028a0(&s->cursor) - 4;
}

extern "C" void LostFoundRecycleMenu_TrackFlyingItem(LostFoundRecycleMenu *s)
{
    s->heldX = func_ov002_02202710(&s->flyMotion);
    s->heldY = func_ov002_02202708(&s->flyMotion);
}

extern "C" void LostFoundRecycleMenu_PickUpItem(LostFoundRecycleMenu *s, u32 a)
{
    if (LostFoundRecycleMenu_IsPocketSlot(s, a) || LostFoundRecycleMenu_IsBoxSlot(s, a)) {
        u32 t = LostFoundRecycleMenu_ToGridSlot(s, a);
        s->heldKind = 1;
        s->heldItem = Shared_InventoryItemGrid_GetSlotItem(&s->itemGrid, t);
        s->heldItemFlags = InventoryItemGrid_GetSlotFlags(&s->itemGrid, t);
        Shared_InventoryItemGrid_ClearSlot(&s->itemGrid, t);
        Shared_InventoryItemGrid_SetHeldItem(&s->itemGrid, s->heldItem, s->heldItemFlags);
    }
}

extern "C" void LostFoundRecycleMenu_ReleaseHeldItem(LostFoundRecycleMenu *s, u32 a)
{
    if (s->heldKind == 1) {
        LostFoundRecycleMenu_SetSlotItem(s, a, s->heldItem, s->heldItemFlags);
    }
    s->heldKind = 0;
}

extern "C" void LostFoundRecycleMenu_ExchangeHeldItem(LostFoundRecycleMenu *s, u32 a)
{
    if (s->heldKind == 1) {
        u32 h = s->heldItem;
        u32 b = s->heldItemFlags;
        LostFoundRecycleMenu_PickUpItem(s, a);
        LostFoundRecycleMenu_SetSlotItem(s, a, h, b);
    }
}

extern "C" void LostFoundRecycleMenu_ShowCursor(LostFoundRecycleMenu *s)
{
    s32 a = LostFoundRecycleMenu_GetCursorTargetX(s);
    s32 b = LostFoundRecycleMenu_GetCursorTargetY(s);
    func_ov002_02202a40(&s->cursor, a, b);
    if (LostFoundRecycleMenu_IsButtonSlot(s, s->cursorSlot)) {
        func_ov002_02202d00(&s->cursor, 7);
    } else {
        func_ov002_02202d00(&s->cursor, 1);
    }
    func_ov110_022954e8(s);
}

extern "C" s32 LostFoundRecycleMenu_GetCursorTargetX(LostFoundRecycleMenu *s)
{
    s32 r = LostFoundRecycleMenu_GetSlotX(s, s->cursorSlot);
    if (func_ov110_02294d88(s, 0x20)) {
        r += 0x100;
    } else if (func_ov110_02294d88(s, 0x10)) {
        r -= 0x100;
    }
    r += 8;
    return r;
}

extern "C" s32 LostFoundRecycleMenu_GetCursorTargetY(LostFoundRecycleMenu *s)
{
    return LostFoundRecycleMenu_GetSlotY(s, s->cursorSlot);
}

extern "C" void LostFoundRecycleMenu_HideCursor(LostFoundRecycleMenu *s)
{
    func_ov002_02202d00(&s->cursor, 0);
    (&s->cursor)->update();
}

extern "C" void LostFoundRecycleMenu_MoveCursorToTarget(LostFoundRecycleMenu *s)
{
    s32 a = LostFoundRecycleMenu_GetCursorTargetX(s);
    s32 b = LostFoundRecycleMenu_GetCursorTargetY(s);
    func_ov002_022029e8(&s->cursor, a, b, 3, 1);
    s->returnState = s->mainState;
    func_ov002_02200a58(s, 8);
    if (func_ov110_02294d88(s, 0x100)) {
        (&s->cursor)->update();
        func_ov110_02294d68(s, 0x100);
    }
}

extern "C" void LostFoundRecycleMenu_MoveCursorToChoice(LostFoundRecycleMenu *s)
{
    s32 a = func_ov002_022014a4(&s->choiceMenu);
    s32 b = func_ov002_02201498(&s->choiceMenu, s->choiceRow);
    func_ov002_02202a18(&s->cursor, a, b, 2);
    s->returnState = s->mainState;
    func_ov002_02200a58(s, 8);
}

extern "C" void LostFoundRecycleMenu_PickCancelChoice(LostFoundRecycleMenu *s)
{
    s->chosenAction = 1;
    s->choiceRow = PopupChoice_DecideCancel(&s->choiceMenu, 1);
    s32 a = func_ov002_022014a4(&s->choiceMenu);
    s32 b = func_ov002_02201498(&s->choiceMenu, s->choiceRow);
    func_ov002_02202a40(&s->cursor, a, b);
    func_0208d538(&s->cursor, 8);
    func_ov002_02200a58(s, 0x12);
}

void LostFoundRecycleMenu::placeCursorOnFirstChoice() {
    choiceRow = 0;
    s32 a = func_ov002_022014a4(&choiceMenu);
    s32 b = func_ov002_02201498(&choiceMenu, choiceRow);
    cursor.warpTo(a, b);
    ((MenuCursor *)&cursor)->setAnimIfChanged(7);
}

void LostFoundRecycleMenu::placeCursorAtTarget() {
    s32 a = LostFoundRecycleMenu_GetCursorTargetX(this);
    s32 b = LostFoundRecycleMenu_GetCursorTargetY(this);
    cursor.warpTo(a, b);
    ((MenuCursor *)&cursor)->setAnimIfChanged(1);
}

void LostFoundRecycleMenu::refreshCursor() {
    cursor.setPoseIdle();
    cursor.update();
}

void LostFoundRecycleMenu::pressCursor() {
    ((MenuCursor *)&cursor)->setPosePress();
    setMainState(9);
}

void LostFoundRecycleMenu::releaseCursor() {
    cursor.setPoseRelease();
    setMainState(0xa);
}

void LostFoundRecycleMenu::startPickUp() {
    ((MenuCursor *)&cursor)->setAnimIfChanged(4);
    setMainState(0xb);
}

void LostFoundRecycleMenu::startPutDown(u8 v) {
    nameBalloon.hide(1);
    actionSlot = v;
    ((MenuCursor *)&cursor)->setAnimIfChanged(5);
    setMainState(0xd);
}

void LostFoundRecycleMenu::startExchange(u8 v) {
    nameBalloon.hide(1);
    returnState = mainState;
    actionSlot = v;
    ((MenuCursor *)&cursor)->setAnimIfChanged(6);
    setMainState(0xe);
}

void LostFoundRecycleMenu::applyChoice() {
    switch (chosenAction) {
    case 0:
        startPickUp();
        break;
    case 1:
    default:
        LostFoundRecycleMenu_ResumeInput(this);
        break;
    }
}

void LostFoundRecycleMenu::cancelChoiceList() {
    chosenAction = 1;
    placeCursorAtTarget();
    PopupChoice_Close(&choiceMenu, 0);
    setMainState(0x13);
}

void LostFoundRecycleMenu::moveCursorInPockets(u32 pad, s32 mode) {
    s32 r = cursorSlot;
    s32 q = 0;
    while (r >= 5) {
        r -= 5;
        q++;
    }
    if (MenuKeys_HasLeft(pad)) {
        if (!MenuKeys_HasUp(pad) || q == 0) {
            if (r == 0) {
                if (mode == 1) {
                    cursorSlot += 4;
                } else {
                    cursorSlot = 0x1e;
                }
                setFlags(0x10);
                return;
            }
            cursorSlot--;
            r--;
        }
    } else if (MenuKeys_HasRight(pad)) {
        if (!MenuKeys_HasDown(pad)) {
            if (r == 4) {
                if (mode == 1) {
                    cursorSlot -= 4;
                    setFlags(0x20);
                } else {
                    cursorSlot = 0x1e;
                }
                return;
            }
            cursorSlot++;
            r++;
        }
    }
    if (MenuKeys_HasUp(pad)) {
        if (q > 0) {
            cursorSlot -= 5;
        } else {
            cursorSlot = r + 0x19;
        }
    } else if (MenuKeys_HasDown(pad)) {
        if (q < 2) {
            cursorSlot += 5;
        }
    }
}

void LostFoundRecycleMenu::moveCursorInBox(u32 pad, s32 mode) {
    s32 r = cursorSlot - 0xf;
    s32 q = 0;
    while (r >= 5) {
        r -= 5;
        q++;
    }
    if (MenuKeys_HasLeft(pad)) {
        if (!MenuKeys_HasUp(pad) || q == 0) {
            if (r == 0) {
                if (mode == 1) {
                    cursorSlot += 4;
                } else {
                    cursorSlot = 0x1e;
                }
                setFlags(0x10);
                return;
            }
            cursorSlot--;
            r--;
        }
    } else if (MenuKeys_HasRight(pad)) {
        if (!MenuKeys_HasDown(pad)) {
            if (r == 4) {
                if (mode == 1) {
                    cursorSlot -= 4;
                    setFlags(0x20);
                } else {
                    cursorSlot = 0x1e;
                }
                return;
            }
            cursorSlot++;
            r++;
        }
    }
    if (MenuKeys_HasUp(pad)) {
        if (q > 0) {
            cursorSlot -= 5;
        }
    } else if (MenuKeys_HasDown(pad)) {
        if (q < 2) {
            cursorSlot += 5;
        } else {
            cursorSlot = r;
        }
    }
}

void LostFoundRecycleMenu::moveCursorOnButtons(u32 pad) {
    if (MenuKeys_HasRight(pad)) {
        if (MenuKeys_HasUp(pad)) {
            cursorSlot = 0x19;
        } else {
            cursorSlot = 0;
        }
        setFlags(0x20);
    } else if (MenuKeys_HasLeft(pad)) {
        if (MenuKeys_HasUp(pad)) {
            cursorSlot = 0x1d;
        } else {
            cursorSlot = 4;
        }
    } else if (MenuKeys_HasUp(pad)) {
        cursorSlot = 0x1d;
    }
}

BOOL LostFoundRecycleMenu::moveCursorByPad(u32 pad, s32 mode) {
    u8 old = cursorSlot;
    clearFlags(0x30);
    clearFlags(0x100);
    if (pad == 0) {
        return FALSE;
    }
    if (LostFoundRecycleMenu_IsPocketSlot(this, cursorSlot)) {
        moveCursorInPockets(pad, mode);
    } else if (LostFoundRecycleMenu_IsBoxSlot(this, cursorSlot)) {
        moveCursorInBox(pad, mode);
    } else if (LostFoundRecycleMenu_IsButtonSlot(this, cursorSlot)) {
        moveCursorOnButtons(pad);
    }
    BOOL a = LostFoundRecycleMenu_IsButtonSlot(this, cursorSlot);
    if (a != LostFoundRecycleMenu_IsButtonSlot(this, old)) {
        if (LostFoundRecycleMenu_IsButtonSlot(this, cursorSlot)) {
            ((MenuCursor *)&cursor)->switchToAnim07();
        } else {
            ((MenuCursor *)&cursor)->switchToAnim01();
        }
        setFlags(0x100);
    }
    if (old != cursorSlot) {
        return TRUE;
    }
    return FALSE;
}

void LostFoundRecycleMenu::resetTextLabels() {
    s32 i;
    numTextLabels = 0;
    for (i = 0; i < 2; i++) {
        textLabels[i].destroyLabel();
    }
}

LabelString *LostFoundRecycleMenu::allocTextLabel() {
    if (numTextLabels >= 2) {
        return &textLabels[1];
    }
    numTextLabels++;
    return &textLabels[numTextLabels - 1];
}

void LostFoundRecycleMenu::setOkLabel(s32 flag) {
    u8 v = 1;
    if (flag != 0) {
        v = 0xf;
    }
    LabelString *p = allocTextLabel();
    p->createLabel(4, 0x1ca, 6, v, 9, 0);
    String_Load2dMenu(p, 0x88);
    p->redrawAligned(1, 0);
}

void LostFoundRecycleMenu::confirm(s32 flag) {
    clearFlags(8);
    s32 r = MenuCtrl_GetMode();
    if (r == 0x20) {
        Snd_PlaySe(0x28);
    } else {
        Snd_PlaySe(0x27);
    }
    if (flag != 0) {
        delayTimer = 5;
    } else {
        delayTimer = 0;
    }
    setMainState(0x15);
    setOkLabel(1);
    s32 n = packItemList(boxItems);
    switch (r) {
    case 0x1d:
    case 0x1e:
        if (n == 0) {
            MenuCtrl_SetResult(0);
        } else {
            MenuCtrl_SetResult(1);
            MenuCtrl_SetChosenItems(boxItems);
        }
        break;
    case 0x1f: {
        s32 i, j;
        for (i = 0; i < 15; i++) {
            if (boxItems[i] != 0xfff1) {
                for (j = 0; j < 15; j++) {
                    if (boxItems[i] == initialBoxItems[j]) {
                        initialBoxItems[j] = 0xfff1;
                        j = 15;
                    }
                }
            }
        }
        n = packItemList(initialBoxItems);
        if (n == 0) {
            MenuCtrl_SetResult(0);
        } else {
            MenuCtrl_SetResult(1);
            MenuCtrl_SetIndex((u8)n);
            MenuCtrl_SetChosenItems(initialBoxItems);
            MI_CpuCopy8(boxItems, gSaveData.lostAndFound, 0x1e);
            sendItemsRecord(3);
        }
        break;
    }
    case 0x20:
        MI_CpuCopy8(boxItems, gSaveData.recycleBin, 0x1e);
        sendItemsRecord(4);
        MenuCtrl_SetResult(1);
        break;
    }
}

s32 LostFoundRecycleMenu::packItemList(u16 *p) {
    s32 i = 0;
    s32 n = i;
    for (; i < 15; i++) {
        u16 v = p[i];
        if (v != 0xfff1) {
            if (i != n) {
                p[n] = v;
                p[i] = 0xfff1;
            }
            n++;
        }
    }
    return n;
}

void LostFoundRecycleMenu::sendItemsRecord(u8 v) {
    u8 buf[0x24];
    if (gCommManager->isOnline()) {
        setFlags(8);
        buf[0] = v;
        MI_CpuCopy8(boxItems, &buf[1], 0x1e);
        CommManager *g = gCommManager;
        g->beginRecord();
        g->writeRecord(buf, 0x1f);
        g->endRecord(0x16, 4);
        sendSeq = g->getSendSeq();
    }
}

BOOL LostFoundRecycleMenu::isResultSent() {
    if (MenuCtrl_IsResultOk() == 0) {
        return TRUE;
    }
    if (testFlags(8) == 0) {
        return TRUE;
    }
    if (gCommManager->isOnline()) {
        if (Comm_IsSeqConfirmed(sendSeq) == 0) {
            return FALSE;
        }
    }
    return TRUE;
}

BOOL LostFoundRecycleMenu::testFlags(u32 mask) {
    if (stateFlags & mask) {
        return TRUE;
    }
    return FALSE;
}

void LostFoundRecycleMenu::setFlags(u32 mask) { stateFlags |= mask; }

void LostFoundRecycleMenu::clearFlags(u32 mask) { stateFlags &= ~mask; }

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov110_02294c40) {
    HOST_OVERLAY_VAR(sLostFoundRecycleMenuProfile),
    HOST_OVERLAY_VARS_END
};
