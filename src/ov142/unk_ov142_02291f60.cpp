#include "types.h"
#include "Unk_020d8c7c.h"
#include "talk/MsgStringBase.h"
#include "talk/MsgStringAttr.h"
#include "room/FtrPreviewer.h"
#include "talk/MsgString.h"
#include "menu/MenuProc.h"
#include "ui/HandCursor.h"
#include "ui/ScrollKnob.h"
#include "menu/MenuLauncher.h"
#include "item/ItemName.h"
#include "ui/LabelString.h"
#include "gfx/BgVramTask.h"
#include "menu/MenuCursor.h"
#include "menu/MenuScrollKnob.h"
#include "menu/MenuBottomButtons.h"
#include "sys/ProcProfile.h"
#include "player/PlayerData.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_0203c23c.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0206f834.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov002/unk_ov002_022025cc.h"
#include "proto/ov002/unk_ov002_02202fac.h"
#include "proto/ov004/unk_ov004_02233074.h"
#include "proto/ov142/unk_ov142_02291f60.h"

class CatalogMenu;





class TextLabel;






extern "C" {
extern u8 gFieldSceneKind;
extern u16 gPad[];

s32 Item_TestInfoFlag4(u16 *p);
s32 Item_GetMemberPrice(u16 *p);
s32 Item_TestInfoFlag3(u16 *p);
void MIi_CpuClear16(u32 v, void *dst, s32 n);
void MIi_CpuCopy16(void *dst, void *src, s32 n);
BOOL Math_StepS32(s32 *p, s32 target, s32 step);
s32 _s32_div_f(s32 a, s32 b);
}










typedef void (CatalogMenu::*Unk_ov142_02294da8_Fn)();

class CatalogMenu : public MenuProc {
public:
    CatalogMenu() : cursor(), scrollKnob(), bottomButtons(), textLabels(), vramTasks() {}

    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onDraw();
    virtual BOOL execTransition();
    virtual BOOL execMain();
    virtual BOOL execPhase3();
    virtual BOOL execPhase4();
    virtual BOOL execClosed();

    void clearFlags(u32 m);
    void setFlags(u32 m);
    BOOL testFlags(u32 m);
    void updateTabSwitch();
    void setTabFadeLevel(u32 t);
    u16 blendColor(s32 x, s32 y, s32 t);
    void scrollByArrow();
    void releaseArrows();
    void pressDownArrow();
    void pressUpArrow();
    void restoreListView();
    void focusSelectedItem();
    void hideScrollBar();
    void showScrollBar();
    void paintScrollBarArea(s32 a);
    void syncKnobToScroll();
    void syncScrollToKnob();
    void updateKnobPosition();
    BOOL finishKnobRelease();
    void moveKnobByKey();
    void releaseKnob();
    void dragKnob(s32 v, BOOL c);
    BOOL tryGrabKnob(s32 x, s32 y);
    BOOL moveCursorByPad(u32 pad);
    void targetTabAtCursor();
    void targetRowOrTab();
    void targetRowOrRight();
    BOOL targetRowAtCursor();
    void targetLeftOfButtons();
    void targetRightOfList();
    void targetScrollAtCursor();
    void targetButtonAtCursor();
    BOOL selectItem(u32 a, s32 b);
    u32 hitTestTarget(s32 x, s32 y);
    BOOL activateTarget(u32 a);
    void uploadListScreen();
    void updateScrollAnimation();
    void setScrollPos(s32 v);
    void flushDirty();
    void composeListScreen();
    u16 *getTabItemPtr(s32 idx);
    s32 getTabOwnedCount();
    s32 getTabTotalCount();
    s32 collectCatalogued(u16 *out, u16 start, s32 n, s32 off);
    s32 collectCataloguedFurniture(u16 *out, u16 start, s32 n, s32 off);
    void buildHeadwearList();
    void buildFossilList();
    void buildGyroidList();
    void buildPaperList();
    void buildUmbrellaList();
    void buildShirtList();
    void buildCarpetList();
    void buildWallpaperList();
    void buildFurnitureList();
    void requestTab(u32 v);
    void setTab(u8 v);
    void clearInfoLabel();
    void drawNotSellingLabel();
    void drawMessageLabel(s32 a, s32 b, s32 c, u8 d, s32 e);
    void drawPriceLabel(s32 a);
    void drawCountLabels();
    void drawItemNames();
    void resetTextLabels();
    LabelString *allocTextLabel();
    void releaseCursor();
    void pressCursor();
    void refreshCursor();
    void moveCursorTo(s32 a, s32 b);
    void moveCursorToTarget();
    void hideCursor();
    s32 getCursorTargetY();
    s32 getCursorTargetX();
    void showCursor();
    void startQuit();
    void startOrderConfirm();
    void beginClose();
    void resumeConfirmInput();
    void startConfirmButtons();
    void startConfirmTouch();
    void resumeInput();
    void startButtonInput();
    void startTouchInput();
    void updateBarTransition();
    void cancelOrderConfirm();
    void confirmOrder();
    void updateConfirmButtons();
    void updateConfirmTouch();
    void updateCursorRelease();
    void updateCursorPress();
    void updateCursorMove();
    void updateArrowKeys();
    void updateKnobKeysEnd();
    void updateKnobKeys();
    void updateButtons();
    void updateArrowTouch();
    void updateTrackTouch();
    void updateKnobTouch();
    void updateTouch();
    void loadObjGfx();
    void loadBgGfx();
    void postStateUpdate();
    void preStateUpdate();
    void preInputUpdate();
    void releaseResources();
    void initCatalog();
    void updateLayerSlide();
    void stateDialogBack();
    void stateDialogClose();
    void stateDialog();
    void stateDialogOpen();
    void stateClosing();
    void stateClose();
    void stateOpening();
    void stateOpen();
    void runMainState();

    /* 0x091 */ u8 unk_91[3];
    /* 0x094 */ s32 slideY;
    /* 0x098 */ u32 buttonsSlideY;
    /* 0x09c */ s32 scrollY;
    /* 0x0a0 */ s32 scrollTargetY;
    /* 0x0a4 */ s32 scrollMax;
    /* 0x0a8 */ s32 knobPos;
    /* 0x0ac */ s32 knobGrabOffset;
    /* 0x0b0 */ s32 knobLastTickPos;
    /* 0x0b4 */ s16 topRow;
    /* 0x0b6 */ u16 flags;
    /* 0x0b8 */ s16 selectedIndex;
    /* 0x0ba */ u8 returnState;
    /* 0x0bb */ u8 labelCount;
    /* 0x0bc */ u8 curTab;
    /* 0x0bd */ u8 targetTab;
    /* 0x0be */ u8 selectedTab;
    /* 0x0bf */ u8 orderButtonPal;
    /* 0x0c0 */ u8 cursorSlot;
    /* 0x0c1 */ u8 tabFadeLevel;
    /* 0x0c2 */ u8 tabSwitchState;
    /* 0x0c3 */ u8 pad_c3;
    /* 0x0c4 */ s16 tabOwnedCounts[9];
    /* 0x0d6 */ s16 tabTotalCounts[9];
    /* 0x0e8 */ MenuCursorBuf0 cursor;
    /* 0x14c */ MenuScrollKnob scrollKnob;
    /* 0x194 */ MenuBottomButtons bottomButtons;
    /* 0x2f8 */ LabelString textLabels[14];
    /* 0x678 */ BgVramTask vramTasks[4];
    /* 0x708 */ u16 furnitureItems[0x800 / 2];
    /* 0xf08 */ u16 wallpaperItems[0x88 / 2];
    /* 0xf90 */ u16 carpetItems[0x88 / 2];
    /* 0x1018 */ u16 shirtItems[0x200 / 2];
    /* 0x1218 */ u16 umbrellaItems[0x40 / 2];
    /* 0x1258 */ u16 headwearItems[0x140 / 2];
    /* 0x1398 */ u16 paperItems[0x80 / 2];
    /* 0x1418 */ u16 gyroidItems[0xfe / 2];
    /* 0x1516 */ u16 fossilItems[0x68 / 2];
    /* 0x157e */ u16 shownRowItems[9];
    /* 0x1590 */ u16 rowTemplateScreen[0x400];
    /* 0x1d90 */ u16 listScreen[0x400];
    /* 0x2590 */ u16 frameScreen[0x400];
    /* 0x2d90 */ u16 basePalette3[16];
    /* 0x2db0 */ u16 workPalette3[16];
    /* 0x2dd0 */ u16 basePalette4[16];
    /* 0x2df0 */ u16 workPalette4[16];
};


static inline BOOL Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        return TRUE;
    }
    return FALSE;
}

static inline BOOL Unk_ov142_02293b34_IsOne() {
    if (gFieldSceneKind == 1) return TRUE;
    return FALSE;
}



extern "C" void *data_ov142_02294d00[2];
extern "C" void *data_ov142_02294d08[2];
extern "C" void *data_ov142_02294d10[2];


extern "C" CatalogMenu *CatalogMenu_Create() { return new CatalogMenu(); }

BOOL CatalogMenu::onCreate() {
    initCatalog();
    transitionState = 0;
    setPhase(0);
    return TRUE;
}

BOOL CatalogMenu::onDelete() {
    ((MenuLauncher *)ProcBase_GetParent(this))->onChildClosed();
    releaseResources();
    return TRUE;
}

BOOL CatalogMenu::onDraw() {
    s32 y;
    s32 t;
    s32 d;
    s32 i;
    s32 j;
    s32 x;
    s32 pal;
    if (MenuCtrl_IsButtons()) {
        cursor.drawWrapped();
    }
    if (!testFlags(1)) {
        return FALSE;
    }
    bottomButtons.drawAt(buttonsSlideY);
    y = slideY + 0x60;
    if (!testFlags(0x100)) {
        MenuScrollKnob *p = &scrollKnob;
        p->draw();
        t = testFlags(0x800) ? 9 : 8;
        x = y;
        if (testFlags(0x2000)) x = y + 2;
        Oam_DrawObj(1, data_ov142_02294d18, 0x80, x, t, 1, 0);
        t = testFlags(0x400) ? 9 : 8;
        x = y;
        if (testFlags(0x1000)) x = y + 2;
        Oam_DrawObj(1, data_ov142_02294d28, 0x80, x, t, 1, 0);
        Oam_DrawObj(1, data_ov142_02294d20, 0x80, y, -1, 1, 0);
        Oam_DrawObj(1, data_ov142_02294d30, 0x80, y, -1, 1, 0);
    }
    x = 0x10;
    for (i = 0; i < 9; i++, x -= 2) {
        if (i == targetTab) {
            pal = 6;
        } else {
            pal = 7;
        }
        Oam_DrawObj(1, data_ov142_02294e08 + x, 0x80, y, pal, 1, 0);
        Oam_DrawObj(1, data_ov142_02294e08 + (x + 1), 0x80, y, pal, 1, 0);
    }
    Oam_DrawCell(1, data_ov142_02294d38, 0x80, y, orderButtonPal, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    x = y - (scrollY & 0xf);
    getTabOwnedCount();
    d = -1;
    if (curTab == selectedTab) {
        d = selectedIndex - topRow;
        if (d < 0 || d >= 9) {
            d = -1;
        }
    }
    i = topRow;
    for (j = 0; j < 9; i++, x += 0x10, j++) {
        if (i >= 0 && d == j) {
            Oam_DrawCell(1, data_ov142_02294d78, 0x80, x, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        } else {
            Oam_DrawCell(1, data_ov142_02294d58, 0x80, x, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        }
    }
    return TRUE;
}

extern "C" GXOamAttr data_ov142_02294d58[4] = {
    {0x401440cd, 0x108, 2, 0x8, 0x0},
    {0x41f840cd, 0x108, 2, 0x8, 0x0},
    {0x41d840cd, 0x108, 2, 0x8, 0x0},
    {0x41b840cd, 0x108, 2, 0x8, 0xffff},
};
extern "C" GXOamAttr data_ov142_02294d30[1] = {
    {0x403800bb, 0x10e, 0, 0x1, 0xffff},
};
extern "C" GXOamAttr data_ov142_02294d28[1] = {
    {0x403800b9, 0x10e, 0, 0x9, 0x0},
};
extern "C" GXOamAttr data_ov142_02294d78[5] = {
    {0x41b800bc, 0x10c, 2, 0x8, 0x0},
    {0x401440cd, 0x128, 2, 0x8, 0x0},
    {0x41f840cd, 0x128, 2, 0x8, 0x0},
    {0x41d840cd, 0x128, 2, 0x8, 0x0},
    {0x41b840cd, 0x128, 2, 0x8, 0xffff},
};
extern "C" GXOamAttr data_ov142_02294d18[1] = {
    {0x40380035, 0x110, 0, 0x8, 0x0},
};
extern "C" GXOamAttr data_ov142_02294e08[18] = {
    {0x41820038, 0xd5, 1, 0x7, 0x0},
    {0x01928038, 0xd7, 1, 0x7, 0x0},
    {0x41820028, 0xd2, 1, 0x7, 0x0},
    {0x01928028, 0xd4, 1, 0x7, 0x0},
    {0x41820018, 0xcf, 1, 0x7, 0x0},
    {0x01928018, 0xd1, 1, 0x7, 0x0},
    {0x41820008, 0xd8, 1, 0x7, 0x0},
    {0x01928008, 0xda, 1, 0x7, 0x0},
    {0x418200f8, 0xcc, 1, 0x7, 0x0},
    {0x019280f8, 0xce, 1, 0x7, 0x0},
    {0x418200e8, 0xc9, 1, 0x7, 0x0},
    {0x019280e8, 0xcb, 1, 0x7, 0x0},
    {0x418200d8, 0xc6, 1, 0x7, 0x0},
    {0x019280d8, 0xc8, 1, 0x7, 0x0},
    {0x418200c8, 0xc3, 1, 0x7, 0x0},
    {0x019280c8, 0xc5, 1, 0x7, 0x0},
    {0x418200b8, 0xc0, 1, 0x6, 0x0},
    {0x019280b8, 0xc2, 1, 0x6, 0xffff},
};

BOOL CatalogMenu::execTransition() {
    static Unk_ov142_02294da8_Fn tbl[8] = {
        &CatalogMenu::stateOpen,
        &CatalogMenu::stateOpening,
        &CatalogMenu::stateClose,
        &CatalogMenu::stateClosing,
        &CatalogMenu::stateDialogOpen,
        &CatalogMenu::stateDialog,
        &CatalogMenu::stateDialogClose,
        &CatalogMenu::stateDialogBack};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}

extern "C" GXOamAttr data_ov142_02294d20[1] = {
    {0x40380037, 0x110, 0, 0x1, 0x0},
};

void CatalogMenu::runMainState() {
    static Unk_ov142_02294da8_Fn tbl[14] = {
        &CatalogMenu::updateTouch,
        &CatalogMenu::updateKnobTouch,
        &CatalogMenu::updateTrackTouch,
        &CatalogMenu::updateArrowTouch,
        &CatalogMenu::updateButtons,
        &CatalogMenu::updateKnobKeys,
        &CatalogMenu::updateKnobKeysEnd,
        &CatalogMenu::updateArrowKeys,
        &CatalogMenu::updateCursorMove,
        &CatalogMenu::updateCursorPress,
        &CatalogMenu::updateCursorRelease,
        &CatalogMenu::updateConfirmTouch,
        &CatalogMenu::updateConfirmButtons,
        &CatalogMenu::updateBarTransition};
    (this->*tbl[mainState])();
}

BOOL CatalogMenu::execMain() {
    preInputUpdate();
    runMainState();
    CatalogMenu_PostInputUpdate(this);
    return TRUE;
}

BOOL CatalogMenu::execPhase3() { return TRUE; }

BOOL CatalogMenu::execPhase4() { return TRUE; }

BOOL CatalogMenu::execClosed() {
    ProcBase_RequestDelete(this);
    return TRUE;
}

void CatalogMenu::stateOpen() {
    CatalogMenu_SetupBgLayers(this);
    loadBgGfx();
    setTab(0);
    loadObjGfx();
    beginSubSlideIn(0xa, 4, 0, 0x18);
    Gfx2d_ShowLayer(6);
    Gfx2d_ShowLayer(4);
    updateLayerSlide();
    bottomButtons.setLayoutSingle05(0x65);
    setTransitionState(1);
}

void CatalogMenu::stateOpening() {
    if (!testFlags(1)) {
        setFlags(1);
        drawMessageLabel(0xb8, 0x16d, 4, 0xf, 0);
        clearInfoLabel();
    }
    if (stepSlideIn(0)) {
        setPhase(2);
        resumeInput();
    }
    updateLayerSlide();
}

void CatalogMenu::stateClose() {
    ((MenuLauncher *)ProcBase_GetParent(this))->setNextRequest(0x44, 1);
    beginSubSlideOut(0xa, 0, 0, 0x18);
    updateLayerSlide();
    setTransitionState(3);
}

void CatalogMenu::stateClosing() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(6);
        Gfx2d_ResetLayer(4);
        setPhase(5);
    } else {
        updateLayerSlide();
    }
}

void CatalogMenu::stateDialogOpen() {
    if (stepSlideOut(-1)) {
        setTransitionState(5);
        initSlideIn(0, 0);
        ((MenuBottomButtonsBody *)&bottomButtons)->setLayoutYesNo0C(0x22);
    }
    buttonsSlideY = getSlideOffsetY();
}

void CatalogMenu::stateDialog() {
    if (stepSlideIn(-1)) {
        resumeConfirmInput();
        setPhase(2);
    }
    buttonsSlideY = getSlideOffsetY();
}

void CatalogMenu::stateDialogClose() {
    if (stepSlideOut(-1)) {
        setTransitionState(7);
        initSlideIn(0, 0);
        bottomButtons.setLayoutSingle05(0x65);
    }
    buttonsSlideY = getSlideOffsetY();
}

void CatalogMenu::stateDialogBack() {
    if (stepSlideIn(-1)) {
        resumeInput();
        setPhase(2);
    }
    buttonsSlideY = getSlideOffsetY();
}

void CatalogMenu::updateLayerSlide() {
    applySlideOffset(6, 0, 0);
    applySlideOffset(4, 0, 0x20 - scrollY);
    slideY = getSlideOffsetY();
    buttonsSlideY = slideY;
    updateKnobPosition();
}

void CatalogMenu::initCatalog() {
    s32 i;
    for (i = 0; i < 9; i++) {
        tabOwnedCounts[i] = 0;
        tabTotalCounts[i] = 0;
    }
    i = 0;
    for (; i < 9; i++) {
        shownRowItems[i] = 0xfff1;
    }
    flags = 0;
    curTab = 9;
    tabFadeLevel = 3;
    tabSwitchState = 0;
    selectItem(9, -1);
    buildFurnitureList();
    buildWallpaperList();
    buildCarpetList();
    buildShirtList();
    buildUmbrellaList();
    buildPaperList();
    buildHeadwearList();
    buildGyroidList();
    buildFossilList();
    scrollKnob.show();
}

void CatalogMenu::releaseResources() {
    resetTextLabels();
    bottomButtons.freeTexts();
    vramTasks[0].cancel();
    vramTasks[1].cancel();
    vramTasks[2].cancel();
    vramTasks[3].cancel();
}

void CatalogMenu::preInputUpdate() {
    preStateUpdate();
    cursor.update();
}

extern "C" void CatalogMenu_PostInputUpdate(CatalogMenu *p) { p->postStateUpdate(); }

void CatalogMenu::preStateUpdate() {
    vramTasks[0].cancel();
    vramTasks[1].cancel();
    vramTasks[2].cancel();
    vramTasks[3].cancel();
    resetTextLabels();
    bottomButtons.freeTexts();
    scrollKnob.update();
}

void CatalogMenu::postStateUpdate() {
    updateTabSwitch();
    updateScrollAnimation();
    flushDirty();
    scrollKnob.updateRelease();
}

extern "C" void CatalogMenu_SetupBgLayers(CatalogMenu *) {
    Gfx2d_SetSubBgModeState(0);
    Gfx2d_SetLayerPriority(6, 1);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
    Gfx2d_SetLayerPriority(4, 2);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
    Gfx2d_SetLayerPriority(3, 2);
    Gfx2d_SetLayerControl(3, 0, 0, 0);
}

void CatalogMenu::loadBgGfx() {
    void *h = gCurrentHeap;
    Gfx2d_LoadCharFile("menu/catalog/bg0.bch", h, 6, 0x11, 0x11, 0x51);
    Gfx2d_LoadCharFile("menu/catalog/bg1.bch", h, 6, 0x156, 0x156, 0x174);
    Gfx2d_LoadPaletteFile("menu/catalog/bg.bpl", h, 6, 1, 1, 5);
    File_LoadToBuffer("menu/catalog/bg_3.bpl", basePalette3, 0x20);
    File_LoadToBuffer("menu/catalog/bg_4.bpl", basePalette4, 0x20);
    File_LoadToBuffer("menu/catalog/b_bg.bsc", rowTemplateScreen, 0x800);
    File_LoadToBuffer("menu/catalog/a_bg.bsc", frameScreen, 0x800);
}

void CatalogMenu::loadObjGfx() {
    MenuButtons_LoadTextColors();
    void *h = gCurrentHeap;
    Gfx2d_LoadCharFile("menu/catalog/obj0.bch", h, 8, 0xc0, 0xc0, 0x11f);
    Gfx2d_LoadCharFile("menu/catalog/obj1.bch", h, 8, 0x120, 0x120, 0x17f);
    Gfx2d_LoadPaletteFile("menu/catalog/obj.bpl", h, 8, 4, 4, 9);
}

void CatalogMenu::updateTouch() {
    if (checkSwitchToButtons(1)) {
        startButtonInput();
        return;
    }
    if (Both()) {
        s32 x = gTouchCurX;
        s32 y = gTouchCurY;
        s32 r = hitTestTarget(x, y);
        if (r != 0x19) {
            activateTarget(r);
            return;
        }
        if (testFlags(0x100)) {
            return;
        }
        if (tryGrabKnob(x, y)) {
            setMainState(1);
            return;
        }
        if (x < 0xb8 || x >= 0xc8) {
            return;
        }
        if (!testFlags(0x400) && y >= 0x19 && y < 0x29) {
            pressUpArrow();
            setMainState(3);
            return;
        }
        if (!testFlags(0x800) && y >= 0x95 && y < 0xa5) {
            pressDownArrow();
            setMainState(3);
            return;
        }
        if (y >= 0x2c && y <= 0x86) {
            scrollKnob.grab();
            setMainState(2);
        }
    }
}

void CatalogMenu::updateKnobTouch() {
    if (gTouchHeld != 0) {
        dragKnob(gTouchCurY, 0);
    } else {
        releaseKnob();
        setMainState(0);
    }
}

void CatalogMenu::updateTrackTouch() {
    if (gTouchHeld != 0) {
        dragKnob(gTouchCurY, 1);
    } else {
        releaseKnob();
        setMainState(0);
    }
}

void CatalogMenu::updateArrowTouch() {
    if (gTouchHeld != 0) {
        scrollByArrow();
    } else {
        releaseArrows();
        setMainState(0);
    }
}

void CatalogMenu::updateButtons() {
    if (checkSwitchToTouch()) {
        startTouchInput();
        return;
    }
    if (moveCursorByPad(takeRepeatedKeys())) {
        moveCursorToTarget();
        return;
    }
    u32 k = gPad[1];
    if (k & 1) {
        pressCursor();
    } else if (k & 2) {
        hideCursor();
        startQuit();
    } else if (k & 8) {
        if (testFlags(0x20)) {
            hideCursor();
            startOrderConfirm();
        }
    }
}

void CatalogMenu::updateKnobKeys() {
    if (gPad[0] & 1) {
        moveKnobByKey();
        s32 a = getCursorTargetX();
        s32 b = getCursorTargetY();
        cursor.warpTo(a, b);
    } else {
        releaseKnob();
        setMainState(6);
    }
}

void CatalogMenu::updateKnobKeysEnd() {
    if (finishKnobRelease()) {
        setMainState(4);
        releaseCursor();
    }
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    cursor.warpTo(a, b);
}

void CatalogMenu::updateArrowKeys() {
    if (gPad[0] & 1) {
        scrollByArrow();
    } else {
        releaseArrows();
        setMainState(4);
        releaseCursor();
    }
}

void CatalogMenu::updateCursorMove() {
    if (!cursor.isMoving()) {
        setMainState(returnState);
        runMainState();
    }
}

void CatalogMenu::updateCursorPress() {
    if (cursor.isAnimDone()) {
        if (!activateTarget(cursorSlot)) {
            setMainState(4);
            releaseCursor();
        }
    }
}

void CatalogMenu::updateCursorRelease() {
    if (cursor.isAnimDone()) {
        refreshCursor();
        setMainState(returnState);
    }
}

void CatalogMenu::updateConfirmTouch() {
    if (checkSwitchToButtons(1)) {
        startConfirmButtons();
        return;
    }
    if (Both()) {
        if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(3)) {
            confirmOrder();
        } else if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(4)) {
            cancelOrderConfirm();
        }
    }
}

void CatalogMenu::updateConfirmButtons() {
    u8 old;
    if (checkSwitchToTouch()) {
        startConfirmTouch();
        return;
    }
    old = cursorSlot;
    takeRepeatedKeys();
    if (isRepeatLeft()) {
        cursorSlot = 0x17;
    } else if (isRepeatRight()) {
        cursorSlot = 0x18;
    }
    if (old != cursorSlot) {
        moveCursorToTarget();
        return;
    }
    {
        u32 k = gPad[1];
        if (k & 1) {
            pressCursor();
            return;
        }
        if (k & 8) {
            hideCursor();
            confirmOrder();
        }
    }
    if (gPad[1] & 2) {
        hideCursor();
        cancelOrderConfirm();
    }
}

void CatalogMenu::confirmOrder() {
    Snd_PlaySe(0x29);
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(3);
    setMainState(0xd);
    MenuCtrl_SetResult(1);
    MenuCtrl_SetCatalogItem(*getTabItemPtr(selectedIndex));
    beginClose();
}

void CatalogMenu::cancelOrderConfirm() {
    Snd_PlaySe(0x2a);
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(4);
    transitionState = 6;
    initSlideOut(0, 0);
    setMainState(0xd);
    setFlags(0x80);
    cursorSlot = 0x12;
    orderButtonPal = 5;
    restoreListView();
}

void CatalogMenu::updateBarTransition() {
    if (((MenuBottomButtonsBody *)&bottomButtons)->stepPress()) {
        if (cursor.getAnim()) {
            s32 a = ((MenuBottomButtonsBody *)&bottomButtons)->getPressOffset();
            s32 b = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(-1);
            s32 c = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(-1);
            cursor.warpTo(a + b, a + c);
        }
    } else {
        hideCursor();
        setPhase(1);
    }
}

void CatalogMenu::startTouchInput() {
    hideCursor();
    setMainState(0);
}

void CatalogMenu::startButtonInput() {
    if (testFlags(0x80)) {
        clearFlags(0x80);
    } else {
        cursorSlot = 0;
    }
    showCursor();
    restartKeyRepeat();
    setMainState(4);
}

void CatalogMenu::resumeInput() {
    if (MenuCtrl_IsTouch()) {
        startTouchInput();
    } else {
        startButtonInput();
    }
    clearFlags(0x80);
}

void CatalogMenu::startConfirmTouch() {
    hideCursor();
    setMainState(0xb);
}

void CatalogMenu::startConfirmButtons() {
    cursorSlot = 0x18;
    showCursor();
    restartKeyRepeat();
    setMainState(0xc);
}

void CatalogMenu::resumeConfirmInput() {
    if (MenuCtrl_IsTouch()) {
        startConfirmTouch();
    } else {
        startConfirmButtons();
    }
}

void CatalogMenu::beginClose() {
    setTransitionState(2);
    if (Unk_ov142_02293b34_IsOne()) {
        if (testFlags(0x40)) {
            clearFlags(0x40);
            ((FtrPreviewer *)FtrPreviewer_GetInstance())->clear();
        }
    }
}

void CatalogMenu::startOrderConfirm() {
    orderButtonPal = 7;
    hideCursor();
    setTransitionState(4);
    setPhase(1);
    initSlideOut(0, 0);
    focusSelectedItem();
    Snd_PlaySe(0x59);
}

void CatalogMenu::startQuit() {
    MenuCtrl_SetResult(0);
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(6);
    setMainState(0xd);
    beginClose();
}

void CatalogMenu::showCursor() {
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    cursor.warpTo(a, b);
    ((MenuCursor *)&cursor)->setAnimIfChanged(1);
    refreshCursor();
}

s32 CatalogMenu::getCursorTargetX() {
    u32 c = cursorSlot;
    if (c <= 8) {
        return 0x17;
    }
    if (c >= 9 && c <= 0x11) {
        return 0x40;
    }
    switch (c - 0x12) {
    case 1:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(6);
    case 0:
        return 0xe8;
    case 2:
        return scrollKnob.getGripX();
    case 5:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(3);
    case 6:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(4);
    case 3:
    case 4:
        return 0xc0;
    default:
        return 0x80;
    }
}

s32 CatalogMenu::getCursorTargetY() {
    u32 c = cursorSlot;
    if (c <= 8) {
        return c * 16 + 0x1f;
    }
    if (c >= 9 && c <= 0x11) {
        return (c - 9) * 16 + 0x28 - (scrollTargetY & 0xf);
    }
    switch (c - 0x12) {
    case 1:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(6);
    case 0:
        return 0x57;
    case 2:
        return scrollKnob.getGripY();
    case 5:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(3);
    case 6:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(4);
    case 3:
        return 0x23;
    case 4:
        return 0x9b;
    default:
        return 0x60;
    }
}

void CatalogMenu::hideCursor() {
    ((MenuCursor *)&cursor)->setAnimIfChanged(0);
    cursor.update();
}

void CatalogMenu::moveCursorToTarget() {
    u32 c = cursorSlot;
    if (c == 0x13 || (c >= 9 && c <= 0x11)) {
        ((MenuCursor *)&cursor)->switchToAnim07();
    } else {
        ((MenuCursor *)&cursor)->switchToAnim01();
    }
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    moveCursorTo(a, b);
}

void CatalogMenu::moveCursorTo(s32 a, s32 b) {
    cursor.moveToEase(a, b, 3, 1);
    returnState = mainState;
    setMainState(8);
}

void CatalogMenu::refreshCursor() {
    cursor.setPoseIdle();
    cursor.update();
}

void CatalogMenu::pressCursor() {
    ((MenuCursor *)&cursor)->setPosePress();
    setMainState(9);
}

void CatalogMenu::releaseCursor() {
    cursor.setPoseRelease();
    returnState = mainState;
    setMainState(10);
}

LabelString *CatalogMenu::allocTextLabel() {
    if (*(volatile u8 *)&labelCount >= 14) {
        return &textLabels[13];
    }
    *(volatile u8 *)&labelCount = *(volatile u8 *)&labelCount + 1;
    return &textLabels[*(volatile u8 *)&labelCount - 1];
}

void CatalogMenu::resetTextLabels() {
    s32 i = 0;
    labelCount = 0;
    LabelString *w = textLabels;
    for (; i < 14; i++) {
        (w + i)->destroyLabel();
    }
}

void CatalogMenu::drawItemNames() {
    ItemName buf;
    s32 i;
    LabelString *w;
    s32 cnt;
    s32 z1 = 0, z2 = 0, z3 = 0;
    s32 cur = topRow;
    u16 *list = getTabItemPtr(cur);
    s32 col = (cur + 9) % 9;
    cnt = getTabOwnedCount();
    for (i = 0; i < 9; i++) {
        w = NULL;
        if (cur < 0 || cur >= cnt) {
            shownRowItems[col] = 0xfff1;
            w = allocTextLabel();
            w->clear();
        } else {
            if (*list != shownRowItems[col]) {
                shownRowItems[col] = *list;
                w = allocTextLabel();
                u16 id = *list;
                buf.setFromItem(&id);
                w->copy(&buf);
            }
            list++;
        }
        if (w) {
            w->createLabel(4, col * 26 + 0x52, 0xd, 0xf, 8, z1);
            w->redrawAligned(z2, z2);
        }
        cur++;
        col++;
        if (col >= 9) col = z3;
    }
}

void CatalogMenu::drawCountLabels() {
    LabelString *w = allocTextLabel();
    String_FormatNumberWrapper(w, getTabOwnedCount(), 3, 0, 0, 0);
    w->createSmallLabel(6, 0x156, 3, 0xe, 4, 0);
    w->redrawRight();
    w = allocTextLabel();
    String_FormatNumberWrapper(w, getTabTotalCount(), 3, 0, 0, 0);
    w->createSmallLabel(6, 0x15a, 3, 0xe, 4, 0);
    w->redrawAligned(0, 0);
}

void CatalogMenu::drawPriceLabel(s32 a) {
    LabelString *w = allocTextLabel();
    String_FormatNumberWrapper(w, a, 8, 1, 0, 1);
    w->createLabel(6, 0x15d, 8, 0xe, 4, 1);
    w->redrawRight();
}

void CatalogMenu::drawMessageLabel(s32 a, s32 b, s32 c, u8 d, s32 e) {
    LabelString *w = allocTextLabel();
    String_Load2dMenu(w, a);
    w->createLabel(6, b, c, d, 4, 0);
    w->redrawAligned(e, 0);
}

void CatalogMenu::drawNotSellingLabel() {
    drawMessageLabel(0x53, 0x15d, 8, 0xe, 1);
}

void CatalogMenu::clearInfoLabel() {
    LabelString *w = allocTextLabel();
    w->clear();
    w->createLabel(6, 0x15d, 8, 0xe, 4, 0);
    w->redrawAligned(0, 0);
}

void CatalogMenu::setTab(u8 v) {
    if (curTab != v) {
        curTab = v;
        targetTab = v;
        scrollMax = (getTabOwnedCount() - 8) << 4;
        if (scrollMax < 0) {
            scrollMax = 0;
        }
        setScrollPos(0);
        scrollTargetY = 0;
        syncKnobToScroll();
        if (scrollMax == 0) {
            hideScrollBar();
        } else {
            showScrollBar();
        }
        updateKnobPosition();
        setFlags(8);
    }
}

void CatalogMenu::requestTab(u32 v) {
    if (v != targetTab) {
        targetTab = v;
        tabSwitchState = 1;
    }
}

void CatalogMenu::buildFurnitureList() {
    s32 n = 0;
    u32 cur;
    u16 id;
    PlayerData *h;
    s32 i;
    tabOwnedCounts[0] = 0;
    tabTotalCounts[0] = 0;
    cur = 0x3000;
    id = 0xfff1;
    h = PlayerData_GetCurrent();
    for (i = 0; i < 0x6e9; i++) {
        BOOL r;
        id = cur;
        r = FALSE;
        u32 v = id;
        if (*(volatile u16 *)&id >= 0x45dc && v <= 0x47d7) r = TRUE;
        if (r) goto next;
        r = (v >= 0x4384 && v <= 0x4463) ? TRUE : FALSE;
        if (r) goto next;
        r = (v >= 0x42a4 && v <= 0x4383) ? TRUE : FALSE;
        if (r) goto next;
        r = (v >= 0x3e24 && v <= 0x3ea3) ? TRUE : FALSE;
        if (r) goto next;
        r = (v >= 0x3984 && v <= 0x3d83) ? TRUE : FALSE;
        if (r) goto next;
        r = (v >= 0x450c && v <= 0x45db) ? TRUE : FALSE;
        if (r) goto next;
        r = (v >= 0x3fa4 && v <= 0x40a3) ? TRUE : FALSE;
        if (r) goto next;
        r = (v >= 0x4124 && v <= 0x4223) ? TRUE : FALSE;
        if (r) goto next;
        r = (v >= 0x40a4 && v <= 0x4123) ? TRUE : FALSE;
        if (r) goto next;
        if (Item_TestInfoFlag3(&id)) {
            tabTotalCounts[0] = tabTotalCounts[0] + 1;
            if (Catalog_HasItem(h->getCatalog(), &id)) {
                furnitureItems[n] = cur;
                n++;
            }
        }
    next:
        cur = (u16)(cur + 4);
    }
    tabOwnedCounts[0] = n;
}

void CatalogMenu::buildWallpaperList() {
    tabTotalCounts[1] = 0;
    tabOwnedCounts[1] = collectCatalogued(wallpaperItems, 0x1100, 0x44, 1);
}

void CatalogMenu::buildCarpetList() {
    tabTotalCounts[2] = 0;
    tabOwnedCounts[2] = collectCatalogued(carpetItems, 0x1144, 0x44, 2);
}

void CatalogMenu::buildShirtList() {
    tabTotalCounts[3] = 0;
    tabOwnedCounts[3] = collectCataloguedFurniture(shirtItems, 0x3984, 0x100, 3);
}

void CatalogMenu::buildUmbrellaList() {
    tabTotalCounts[4] = 0;
    tabOwnedCounts[4] = collectCataloguedFurniture(umbrellaItems, 0x3e24, 0x20, 4);
}

void CatalogMenu::buildPaperList() {
    tabTotalCounts[6] = 0;
    tabOwnedCounts[6] = collectCataloguedFurniture(paperItems, 0x1003, 0x40, 6);
}

void CatalogMenu::buildGyroidList() {
    tabTotalCounts[7] = 0;
    tabOwnedCounts[7] = collectCataloguedFurniture(gyroidItems, 0x45dc, 0x7f, 7);
}

void CatalogMenu::buildFossilList() {
    tabTotalCounts[8] = 0;
    s32 n = collectCataloguedFurniture(fossilItems, 0x450c, 0x34, 8);
    tabOwnedCounts[8] = n;
}

void CatalogMenu::buildHeadwearList() {
    tabTotalCounts[5] = 0;
    s32 a = collectCataloguedFurniture(headwearItems, 0x3fa4, 0x40, 5);
    s32 b = collectCataloguedFurniture(headwearItems + a, 0x40a4, 0x20, 5);
    a += b;
    s32 c = collectCataloguedFurniture(headwearItems + a, 0x4124, 0x40, 5);
    tabOwnedCounts[5] = a + c;
}

s32 CatalogMenu::collectCataloguedFurniture(u16 *out, u16 start, s32 n, s32 off) {
    s32 cnt = 0;
    PlayerData *p = PlayerData_GetCurrent();
    u16 tmp = 0xfff1;
    s32 i = 0;
    for (; i < n; i++) {
        tmp = start;
        if (Item_TestInfoFlag3(&tmp)) {
            tabTotalCounts[off] = tabTotalCounts[off] + 1;
            if (Catalog_HasItem(p->getCatalog(), &tmp)) {
                out[cnt] = start;
                cnt++;
            }
        }
        start = start + 4;
    }
    return cnt;
}

s32 CatalogMenu::collectCatalogued(u16 *out, u16 start, s32 n, s32 off) {
    s32 cnt = 0;
    u16 tmp = 0xfff1;
    PlayerData *p = PlayerData_GetCurrent();
    s32 i = 0;
    for (; i < n; i++) {
        tmp = start;
        if (Item_TestInfoFlag3(&tmp)) {
            tabTotalCounts[off] = tabTotalCounts[off] + 1;
            if (Catalog_HasItem(p->getCatalog(), &tmp)) {
                out[cnt] = start;
                cnt++;
            }
        }
        start = start + 1;
    }
    return cnt;
}

s32 CatalogMenu::getTabTotalCount() {
    return tabTotalCounts[curTab];
}

s32 CatalogMenu::getTabOwnedCount() {
    return tabOwnedCounts[curTab];
}

extern "C" ProcProfile sCatalogMenuProfile = {(void *(*)())CatalogMenu_Create, 0xb7, 0xbb};

u16 *CatalogMenu::getTabItemPtr(s32 idx) {
    u16 *tbl[9] = {furnitureItems, wallpaperItems, carpetItems, shirtItems, umbrellaItems,
                   headwearItems, paperItems, gyroidItems, fossilItems};
    if (idx < 0) {
        idx = 0;
    }
    return tbl[curTab] + idx;
}

void CatalogMenu::composeListScreen() {
    s32 a = topRow;
    s32 i = (a + 9) % 9;
    s32 j = a & 0xf;
    volatile u16 fill = 0x10;
    MIi_CpuClear16(fill, listScreen, 0x800);
    s32 z = 0;
    for (s32 n = 0; n < 9; n++) {
        MIi_CpuCopy16(&rowTemplateScreen[i * 0x40], &listScreen[j * 0x40], 0x80);
        i++;
        if (i >= 9) {
            i = z;
        }
        j = (j + 1) & 0xf;
    }
    setFlags(2);
}

void CatalogMenu::flushDirty() {
    if (testFlags(2)) {
        uploadListScreen();
    }
    if (testFlags(0x10)) {
        if (vramTasks[1].requestScreen(frameScreen, 6, 0x800, 0)) {
            clearFlags(0x10);
        }
    }
    if (testFlags(4)) {
        clearFlags(4);
        drawItemNames();
    }
    if (testFlags(8)) {
        clearFlags(8);
        drawCountLabels();
    }
}

void CatalogMenu::setScrollPos(s32 v) {
    clearFlags(0xc00);
    if (v <= 0) {
        setFlags(0x400);
    }
    if (v >= scrollMax) {
        setFlags(0x800);
    }
    scrollY = v;
    Gfx2d_SetLayerOffset(4, 0, scrollY - 0x20);
    topRow = v >> 4;
    composeListScreen();
    setFlags(4);
}

void CatalogMenu::updateScrollAnimation() {
    s32 a = scrollTargetY;
    if (scrollY != a) {
        if (scrollY > a) {
            scrollY = scrollY - 6;
            if (scrollY < scrollTargetY) {
                scrollY = scrollTargetY;
            }
        } else {
            scrollY = scrollY + 6;
            if (scrollY > scrollTargetY) {
                scrollY = scrollTargetY;
            }
        }
        setScrollPos(scrollY);
        syncKnobToScroll();
    }
}

void CatalogMenu::uploadListScreen() {
    s32 v;
    if (testFlags(0x200)) {
        v = 5;
    } else {
        v = 3;
    }
    BgScreen_SetRectPalette(listScreen, 0, 0, 0x1f, 0x1f, v);
    if (curTab == selectedTab) {
        s32 b = selectedIndex;
        s32 d = b - topRow;
        if (d >= 0 && d < 9) {
            s32 m = (b & 0xf) * 2;
            BgScreen_SetRectPalette(listScreen, 0, m, 0x1f, m + 1, 4);
        }
    }
    if (vramTasks[0].requestScreen(listScreen, 4, 0x800, 0)) {
        clearFlags(2);
    }
}

BOOL CatalogMenu::activateTarget(u32 a) {
    switch (a) {
    case 0x13:
        startQuit();
        return TRUE;
    case 0x12:
        if (testFlags(0x20)) {
            startOrderConfirm();
            return TRUE;
        }
        return FALSE;
    case 0x14:
        scrollKnob.grab();
        Menu_PlayScrollGrabSe();
        setMainState(5);
        return TRUE;
    case 0x17:
        confirmOrder();
        return TRUE;
    case 0x18:
        cancelOrderConfirm();
        return TRUE;
    case 0x15:
        if (testFlags(0x400)) {
            return FALSE;
        }
        pressUpArrow();
        setMainState(7);
        return TRUE;
    case 0x16:
        if (testFlags(0x800)) {
            return FALSE;
        }
        pressDownArrow();
        setMainState(7);
        return TRUE;
    default:
        break;
    }
    if (a <= 8) {
        if (targetTab != a) {
            Snd_PlaySe(0xc);
            requestTab((u8)a);
        }
        return FALSE;
    }
    if (a >= 9 && a <= 0x11) {
        if (tabSwitchState != 0) {
            return FALSE;
        }
        if (selectItem(curTab, (s16)(topRow + (a - 9)))) {
            Snd_PlaySe(0x29);
        }
    }
    return FALSE;
}

u32 CatalogMenu::hitTestTarget(s32 x, s32 y) {
    if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(6)) {
        return 0x13;
    }
    if (testFlags(0x20)) {
        if (x >= 0xc4 && x < 0xe8 && y >= 0x4d && y < 0x71) {
            return 0x12;
        }
    }
    if (x <= 0x1b) {
        if (y >= 0x18 && y < 0xa8) {
            return (u8)((y - 0x18) >> 4);
        }
        return 0x19;
    }
    if (x >= 0x38 && x <= 0x9c) {
        if (y >= 0x20 && y < 0xa0) {
            s32 k = (y - (0x20 - (scrollTargetY & 0xf))) >> 4;
            if (k >= getTabOwnedCount()) {
                return 0x19;
            }
            return (u8)(k + 9);
        }
        return 0x19;
    }
    return 0x19;
}

BOOL CatalogMenu::selectItem(u32 a, s32 b) {
    BOOL r = TRUE;
    volatile u16 tmp;
    if (selectedTab == a && selectedIndex == b) {
        r = FALSE;
    }
    selectedTab = a;
    selectedIndex = b;
    if (b == -1) {
        clearInfoLabel();
        clearFlags(0x20);
        orderButtonPal = 6;
        BOOL t;
        if (gFieldSceneKind == 1) {
            t = TRUE;
        } else {
            t = FALSE;
        }
        if (t) {
            if (testFlags(0x40)) {
                clearFlags(0x40);
                ((FtrPreviewer *)FtrPreviewer_GetInstance())->clear();
            }
        }
    } else {
        u16 v = *getTabItemPtr(b);
        tmp = 0xfff1;
        tmp = v;
        if (Item_TestInfoFlag4((u16 *)&tmp)) {
            drawNotSellingLabel();
            orderButtonPal = 6;
            clearFlags(0x20);
        } else {
            drawPriceLabel(Item_GetMemberPrice((u16 *)&tmp));
            setFlags(0x20);
            orderButtonPal = 5;
        }
        BOOL t;
        if (gFieldSceneKind == 1) {
            t = TRUE;
        } else {
            t = FALSE;
        }
        if (t) {
            setFlags(0x40);
            ((FtrPreviewer *)FtrPreviewer_GetInstance())->showItem((u16 *)&tmp);
        }
    }
    setFlags(2);
    return r;
}

void CatalogMenu::targetButtonAtCursor() {
    if (cursor.getScreenY() > 0x89) {
        cursorSlot = 0x13;
    } else {
        cursorSlot = 0x12;
    }
}

void CatalogMenu::targetScrollAtCursor() {
    if (cursor.getScreenY() < 0x2b) {
        cursorSlot = 0x15;
    } else if (cursor.getScreenY() > 0x93) {
        cursorSlot = 0x16;
    } else {
        cursorSlot = 0x14;
    }
}

void CatalogMenu::targetRightOfList() {
    if (scrollMax == 0) {
        targetButtonAtCursor();
    } else {
        targetScrollAtCursor();
    }
}

void CatalogMenu::targetLeftOfButtons() {
    if (scrollMax == 0) {
        targetRowOrTab();
    } else {
        targetScrollAtCursor();
    }
}

BOOL CatalogMenu::targetRowAtCursor() {
    s32 n = getTabOwnedCount();
    if (n == 0) {
        return FALSE;
    }
    if (n > 9) {
        n = 9;
    }
    s32 y = cursor.getScreenY();
    if (y < 0x20) {
        y = 0x20;
    }
    if (y >= 0xa0) {
        y = 0x9f;
    }
    s32 r = scrollTargetY & 0xf;
    s32 k = (y - (0x20 - r)) >> 4;
    if (k >= n) {
        k = n - 1;
    }
    cursorSlot = k + 9;
    if (r != 0) {
        if (k == 0) {
            scrollTargetY = scrollTargetY - r;
        } else if (k == n - 1) {
            cursorSlot = cursorSlot - 1;
            scrollTargetY = scrollTargetY + (0x10 - (scrollTargetY & 0xf));
        }
    }
    return TRUE;
}

void CatalogMenu::targetRowOrRight() {
    if (targetRowAtCursor() == 0) {
        targetRightOfList();
    }
}

void CatalogMenu::targetRowOrTab() {
    if (targetRowAtCursor() == 0) {
        targetTabAtCursor();
    }
}

void CatalogMenu::targetTabAtCursor() {
    s32 t = cursor.getScreenY();
    if ((t & 0xf) == 0) {
        t = t - 1;
    }
    if (t < 0x18) {
        t = 0x18;
    }
    if (t >= 0xa8) {
        t = 0xa7;
    }
    cursorSlot = (t - 0x18) >> 4;
}

BOOL CatalogMenu::moveCursorByPad(u32 pad) {
    u32 old = cursorSlot;
    if (pad == 0) {
        return FALSE;
    }
    if (old <= 8) {
        if (MenuKeys_HasRight(pad)) {
            targetRowOrRight();
        } else if (MenuKeys_HasUp(pad)) {
            if (cursorSlot != 0) {
                cursorSlot = *(volatile u8 *)&cursorSlot - 1;
            }
        } else if (MenuKeys_HasDown(pad)) {
            if (cursorSlot < 8) {
                cursorSlot = *(volatile u8 *)&cursorSlot + 1;
            }
        }
    } else if (old >= 9 && old <= 0x11) {
        if (MenuKeys_HasLeft(pad)) {
            targetTabAtCursor();
        } else if (MenuKeys_HasRight(pad)) {
            targetRightOfList();
        } else if (MenuKeys_HasUp(pad)) {
            if (cursorSlot > 9) {
                cursorSlot = *(volatile u8 *)&cursorSlot - 1;
                if (cursorSlot == 9) {
                    s32 r = scrollTargetY & 0xf;
                    if (r != 0) {
                        scrollTargetY = scrollTargetY - r;
                    }
                }
            } else {
                if (scrollTargetY >= 0x10) {
                    scrollTargetY = scrollTargetY - 0x10;
                    return TRUE;
                }
            }
        } else if (MenuKeys_HasDown(pad)) {
            if (scrollMax == 0) {
                if (cursorSlot < getTabOwnedCount() + 8) {
                    cursorSlot = *(volatile u8 *)&cursorSlot + 1;
                }
            } else if (cursorSlot < 0x10) {
                cursorSlot = *(volatile u8 *)&cursorSlot + 1;
            } else {
                s32 t = scrollTargetY;
                s32 r = t & 0xf;
                if (r != 0) {
                    scrollTargetY = scrollTargetY + (0x10 - r);
                    return TRUE;
                } else if (t <= scrollMax - 0x10) {
                    scrollTargetY = scrollTargetY + 0x10;
                    return TRUE;
                }
            }
        }
    } else {
        switch (old - 0x12) {
        case 1:
            if (MenuKeys_HasLeft(pad)) {
                targetLeftOfButtons();
            } else if (MenuKeys_HasUp(pad)) {
                cursorSlot = 0x12;
            }
            break;
        case 0:
            if (MenuKeys_HasLeft(pad)) {
                targetLeftOfButtons();
            } else if (MenuKeys_HasDown(pad)) {
                cursorSlot = 0x13;
            }
            break;
        case 2:
            if (MenuKeys_HasUp(pad)) {
                cursorSlot = 0x15;
            } else if (MenuKeys_HasDown(pad)) {
                cursorSlot = 0x16;
            } else if (MenuKeys_HasRight(pad)) {
                cursorSlot = 0x12;
            } else if (MenuKeys_HasLeft(pad)) {
                targetRowOrTab();
            }
            break;
        case 3:
            if (MenuKeys_HasDown(pad)) {
                cursorSlot = 0x14;
            } else if (MenuKeys_HasRight(pad)) {
                cursorSlot = 0x12;
            } else if (MenuKeys_HasLeft(pad)) {
                targetRowOrTab();
            }
            break;
        case 4:
            if (MenuKeys_HasUp(pad)) {
                cursorSlot = 0x14;
            } else if (MenuKeys_HasRight(pad)) {
                cursorSlot = 0x12;
            } else if (MenuKeys_HasLeft(pad)) {
                targetRowOrTab();
            } else if (MenuKeys_HasDown(pad)) {
                cursorSlot = 0x13;
            }
            break;
        }
    }
    if (old != cursorSlot) {
        return TRUE;
    }
    return FALSE;
}

BOOL CatalogMenu::tryGrabKnob(s32 x, s32 y) {
    if (scrollKnob.hitTest(x, y)) {
        knobGrabOffset = knobPos - y;
        scrollKnob.grab();
        knobLastTickPos = knobPos;
        return TRUE;
    }
    return FALSE;
}

void CatalogMenu::dragKnob(s32 v, BOOL c) {
    if (c) {
        v = v - 0x34;
    } else {
        v = v + knobGrabOffset;
    }
    if (v < 0) {
        v = 0;
    }
    if (v > 0x5a) {
        v = 0x5a;
    }
    if (c) {
        Math_StepS32(&knobPos, v, 8);
    } else {
        knobPos = v;
    }
    syncScrollToKnob();
    updateKnobPosition();
    s32 d = knobLastTickPos - knobPos;
    if (d >= 4 || d <= -4) {
        Menu_PlayScrollTickSe();
        knobLastTickPos = knobPos;
    }
}

void CatalogMenu::releaseKnob() { scrollKnob.release(); }

void CatalogMenu::moveKnobByKey() {
    s32 old = knobPos;
    u32 k = gPad[0];
    if (k & 0x40) {
        knobPos = knobPos - 4;
        if (knobPos < 0) {
            knobPos = 0;
        }
    } else if (k & 0x80) {
        knobPos = knobPos + 4;
        if (knobPos > 0x5a) {
            knobPos = 0x5a;
        }
    }
    if (old != knobPos) {
        syncScrollToKnob();
        updateKnobPosition();
        Menu_PlayScrollTickSe();
    }
}

BOOL CatalogMenu::finishKnobRelease() {
    if (scrollKnob.areAnimsDone()) {
        scrollKnob.show();
        return TRUE;
    }
    return FALSE;
}

void CatalogMenu::updateKnobPosition() {
    scrollKnob.moveTo(0x38, slideY + (knobPos - 0x34));
}

void CatalogMenu::syncScrollToKnob() {
    s32 v;
    s32 n = scrollMax;
    v = _s32_div_f(knobPos * n, 0x5a);
    if (v < 0) {
        v = 0;
    }
    if (v > n) {
        v = n;
    }
    setScrollPos(v);
    scrollTargetY = v;
}

void CatalogMenu::syncKnobToScroll() {
    if (scrollMax > 0) {
        knobPos = _s32_div_f(scrollY * 0x5a, scrollMax);
        updateKnobPosition();
    }
}

void CatalogMenu::paintScrollBarArea(s32 a) {
    BgScreen_SetRectPalette(frameScreen, 0x17, 4, 0x18, 0x13, a);
    setFlags(0x10);
}

void CatalogMenu::showScrollBar() {
    clearFlags(0x100);
    paintScrollBarArea(2);
}

void CatalogMenu::hideScrollBar() {
    setFlags(0x100);
    paintScrollBarArea(3);
}

void CatalogMenu::focusSelectedItem() {
    setTab(selectedTab);
    setScrollPos((selectedIndex - 3) << 4);
    scrollTargetY = scrollY;
    syncKnobToScroll();
    hideScrollBar();
    setFlags(0x200);
}

void CatalogMenu::restoreListView() {
    s32 a = topRow;
    s32 b = getTabOwnedCount() - 8;
    if (b < 0) {
        b = 0;
    }
    if (a < 0) {
        a = 0;
    } else if (a > b) {
        a = b;
    }
    setScrollPos(a << 4);
    scrollTargetY = scrollY;
    syncKnobToScroll();
    if (scrollMax == 0) {
        hideScrollBar();
    } else {
        showScrollBar();
    }
    clearFlags(0x200);
}

void CatalogMenu::pressUpArrow() { setFlags(0x1000); }

void CatalogMenu::pressDownArrow() { setFlags(0x2000); }

void CatalogMenu::releaseArrows() { clearFlags(0x3000); }

void CatalogMenu::scrollByArrow() {
    s32 old = scrollY;
    if (testFlags(0x1000)) {
        s32 r = scrollY & 0xf;
        if (r != 0) {
            scrollY = scrollY - r;
        } else {
            scrollY = scrollY - 0x10;
        }
        if (scrollY < 0) {
            scrollY = 0;
        }
    } else {
        s32 r = scrollY & 0xf;
        if (r != 0) {
            scrollY = scrollY + (0x10 - r);
        } else {
            scrollY = scrollY + 0x10;
        }
        s32 lim = scrollMax;
        if (scrollY > lim) {
            scrollY = lim;
        }
    }
    if (old != scrollY) {
        setScrollPos(scrollY);
        scrollTargetY = scrollY;
        syncKnobToScroll();
        Menu_PlayScrollTickSe();
    }
}

u16 CatalogMenu::blendColor(s32 x, s32 y, s32 t) {
    u8 r = y & 0x1f;
    u8 g = (y & 0x3e0) >> 5;
    u8 b = (y & 0x7c00) >> 10;
    s32 n = 3 - t;
    r = ((u8)(x & 0x1f) * t + r * n) / 3;
    g = ((u8)((x & 0x3e0) >> 5) * t + g * n) / 3;
    b = ((u8)((x & 0x7c00) >> 10) * t + b * n) / 3;
    return r | (g << 5) | (b << 10);
}

void CatalogMenu::setTabFadeLevel(u32 t) {
    MIi_CpuCopy16(basePalette3, workPalette3, 0x20);
    MIi_CpuCopy16(basePalette4, workPalette4, 0x20);
    workPalette3[15] = blendColor(basePalette3[15], basePalette3[8], t);
    workPalette4[15] = blendColor(basePalette4[15], basePalette4[8], t);
    vramTasks[2].requestPalette(workPalette3, 4, 3);
    vramTasks[3].requestPalette(workPalette4, 4, 4);
}

void CatalogMenu::updateTabSwitch() {
    switch (tabSwitchState) {
    case 0:
        return;
    case 1:
        if (tabFadeLevel != 0) {
            tabFadeLevel = *(volatile u8 *)&tabFadeLevel - 1;
        } else {
            tabSwitchState = 2;
            setTab(targetTab);
        }
        break;
    case 2:
        if (tabFadeLevel < 3) {
            tabFadeLevel = *(volatile u8 *)&tabFadeLevel + 1;
        } else {
            tabSwitchState = 0;
            return;
        }
        break;
    }
    setTabFadeLevel(tabFadeLevel);
}

BOOL CatalogMenu::testFlags(u32 m) {
    if (flags & m) {
        return TRUE;
    }
    return FALSE;
}

void CatalogMenu::setFlags(u32 m) { flags = flags | m; }

void CatalogMenu::clearFlags(u32 m) { flags = flags & ~m; }

extern "C" GXOamAttr data_ov142_02294d38[4] = {
    {0x804b00eb, 0xdb, 1, 0x6, 0x0},
    {0x406b80eb, 0xdf, 1, 0x6, 0x0},
    {0x404b400b, 0x15b, 1, 0x6, 0x0},
    {0x006b000b, 0x15f, 1, 0x6, 0xffff},
};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov142_02291f60) {
    HOST_OVERLAY_VAR(data_ov142_02294d58),
    HOST_OVERLAY_VAR(data_ov142_02294d30),
    HOST_OVERLAY_VAR(data_ov142_02294d28),
    HOST_OVERLAY_VAR(data_ov142_02294d78),
    HOST_OVERLAY_VAR(data_ov142_02294d18),
    HOST_OVERLAY_VAR(data_ov142_02294e08),
    HOST_OVERLAY_VAR(data_ov142_02294d20),
    HOST_OVERLAY_VAR(sCatalogMenuProfile),
    HOST_OVERLAY_VAR(data_ov142_02294d38),
    HOST_OVERLAY_VARS_END
};
