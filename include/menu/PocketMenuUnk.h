#ifndef MENU_POCKETMENUUNK_H
#define MENU_POCKETMENUUNK_H

#include "types.h"
#include "menu/MenuProc.h"
#include "gfx/BgVramTask.h"
#include "menu/InventoryItemGrid.h"
#include "menu/LetterGrid.h"
#include "menu/InventoryBg.h"
#include "ui/TouchPromptBalloon.h"
#include "ui/CursorMotion.h"
#include "menu/MenuCursor.h"
#include "menu/PopupChoiceMenu.h"
#include "menu/PopupChoiceIdList.h"
#include "menu/MenuErrorMessage.h"
#include "item/Letter.h"

class PocketMenuUnk;
typedef void (PocketMenuUnk::*Unk_ov099_02296b00_Fn)();

class PocketMenuUnk : public MenuProc {
public:
    PocketMenuUnk()
        : bgTasks(), pocketGrid(), letterGrid(), inventoryBg(), nameBalloon(), flyMotion(), cursor(), popup(), errorMessage(), heldLetter() {}

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
    BOOL moveCursorByPad(u32 keys);
    void moveCursorInPockets(u32 keys);
    void openTargetOptions(u32 idx);
    void addItemOptions();
    void cancelOptions();
    void showOptionList();
    void runChosenAction();
    void beginSwapAt(u32 v);
    void beginPutDownAt(u32 v);
    void beginMoveFromPopup();
    void releaseCursor();
    void refreshCursor();
    void placeCursorOnTarget();
    void cursorToPopupTop();
    void moveCursorToPopupRow();
    void moveCursorToTarget();
    void hideCursor();
    s32 getCursorTargetY();
    s32 getCursorTargetX();
    void showCursor();
    void swapHandWith(u32 idx);
    void putHandBack(u32 idx);
    void pickUp(u32 idx);
    void syncHandFromMover();
    void syncHandFromCursor();
    void syncHandFromTouch();
    void drawHand();
    void updateLabelBalloon();
    void positionLabelBalloon();

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
    void stateWaitSlideOut();
    void stateSlideOut();
    void stateWaitSlideIn();
    void stateSlideIn();
    void stateLoad();

    void loadObjGraphics();
    void loadInventoryBg();
    void setupBgLayer();
    void postStateUpdate();
    void preStateUpdate();
    void postInputUpdate();
    void preInputUpdate();
    void releaseResources();
    void initPocketMenuUnk();

    /* 0x91 */ u8 unk_91[3];
    /* 0x94 */ BgVramTaskPair bgTasks[1];
    /* 0xcc */ InventoryItemGrid pocketGrid;
    /* 0xb2c */ LetterGrid letterGrid;
    /* 0xb54 */ InventoryBg inventoryBg;
    /* 0x2134 */ TouchPromptBalloon nameBalloon;
    /* 0x21f4 */ CursorMotion flyMotion;
    /* 0x220c */ MenuCursorBuf0 cursor;
    /* 0x2270 */ PopupChoiceMenu popup;
    /* 0x2564 */ PopupChoiceIdList choiceList;
    /* 0x256f */ u8 pad_256f[1];
    /* 0x2570 */ MenuErrorMessage errorMessage;
    /* 0x2678 */ u32 stateFlags;
    /* 0x267c */ u32 slideY;
    /* 0x2680 */ s32 grabOffsetX;
    /* 0x2684 */ s32 grabOffsetY;
    /* 0x2688 */ s32 handX;
    /* 0x268c */ s32 handY;
    /* 0x2690 */ Letter heldLetter;
    /* 0x2784 */ u16 handItem;
    /* 0x2786 */ u8 handItemFlags;
    /* 0x2787 */ u8 handKind;
    /* 0x2788 */ u8 touchedTarget;
    /* 0x2789 */ u8 balloonTarget;
    /* 0x278a */ u8 handSource;
    /* 0x278b */ u8 cursorTarget;
    /* 0x278c */ u8 actionTarget;
    /* 0x278d */ u8 placeTarget;
    /* 0x278e */ u8 returnState;
    /* 0x278f */ u8 chosenAction;
    /* 0x2790 */ u8 popupRow;
};

#endif
