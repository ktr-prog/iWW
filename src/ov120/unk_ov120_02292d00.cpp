#include "ds_div.h"
#include "host_labels.h"
#include "host_shared_calls.h"
#include "host_overlay_vars.h"
#include "types.h"
#include "gfx/VecFx32.h"
#include "Unk_020d8c7c.h"
#include "town/TownMapMarkers.h"
#include "menu/MenuProc.h"
#include "ui/LabelString.h"
#include "gfx/BgVramTask.h"
#include "menu/MenuScrollKnob.h"
#include "menu/MenuCursor.h"
#include "sys/ProcProfile.h"
#include "menu/MenuLauncher.h"
#include "talk/MsgString.h"
#include "talk/MsgString9C.h"
#include "ui/HandCursor.h"
#include "ui/ScrollKnob.h"
#include "proto/main/unk_020b4828.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0206f834.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020637e4.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov002/unk_ov002_022013ac.h"
#include "proto/ov117/unk_ov117_02292360.h"
#include "proto/ov120/unk_ov120_02292d00.h"
#include "player/PlayerData.h"


#include "nitro/gxoam.h"

extern "C" {
BOOL SaveVillagers_IsOccupied(u8 *base, s32 idx);
void MIi_CpuCopy16(const void *src, void *dst, u32 n);
void MIi_CpuClear16(u32 v, void *dst, u32 n);
extern u8 gFieldSceneKind;
#define gSaveTownId HOST_LABEL(u8 (*)[], gSaveTownId)
#define gSavePlayers HOST_LABEL(u8 (*)[], gSavePlayers)
#define gSaveVillagers HOST_LABEL(u8 (*)[], gSaveVillagers)
extern u16 gPad[];
struct Unk_ov120_02293a2c_Oam {
    u16 attr0;
    u16 a : 9;
    u16 pal : 5;
    u16 b : 2;
    u16 tile : 10;
    u16 c : 6;
    u16 attr3;
};
extern Unk_ov120_02293a2c_Oam sMapViewIconCell;
extern const u8 sMapViewFacilityCells[5];
extern const u8 sMapViewPlaceMarkers[5];
}





class MapViewMarker {
public:
    MapViewMarker();
    ~MapViewMarker();
    u8 x;
    u8 y;
    u8 cell;
};



class MapViewerMenu;
typedef void (MapViewerMenu::*Unk_ov120_02295010_Fn)();

class MapViewerMenu : public MenuProc {
public:
    MapViewerMenu()
        : screenTasks(), textLabels(), scrollKnob(), cursor(), terrainMarkers(), buildingMarkers() {}

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
    void moveMapCursorToRow();
    s32 onCursorDecide();
    BOOL moveCursorByPad(u32 pad);
    void refreshCursor();
    void releaseCursor();
    void pressCursor();
    void moveCursorToTarget();
    void hideCursor();
    s32 getCursorTargetY();
    s32 getCursorTargetX();
    void showCursor();
    void stopBlink();
    void startBlink();
    void updateBlink();
    BOOL touchListTabs();
    void scrollListByPad();
    void scrollListToTouch();
    BOOL touchScrollKnob();
    void updateListScroll();
    BOOL isListScrolling();
    void setListScrollTarget(u32 v);
    void setListScroll(u32 v);
    void ensureSelectionVisible();
    u32 selectionToMarker(u8 v);
    void highlightListRow(u8 v);
    void selectEntry(u8 v);
    s32 getListScrollMax();
    s32 getListCount();
    void showPlacesList();
    void showResidentsList();
    u32 selectionToListRow(u8 v);
    void jumpToSelection();
    u32 findMarkerAt(s32 x, s32 y);
    BOOL touchMarker();
    void setupMarkers(TownMapMarkers *src);
    void drawMapIcon(s32 x, s32 y, s32 n, s32 flag, s32 pal);
    BOOL touchListRow();
    u8 *getListEntries();
    void rebuildList();
    void setEntryName(MsgString *p, u32 idx);
    void buildEntryLabels(u8 *tbl);
    void layoutListLabels();
    void buildEntryLists();
    LabelString *allocTextLabel();
    void resetTextLabels();
    u32 getEntryIconRow(u32 a, s32 b);
    void buildListScreen();
    void clipListScreen();
    void loadMapImage();
    void loadBgGfx();
    void setupBgLayers();
    void postInputUpdate();
    void preInputUpdate();
    void postStateUpdate();
    void preStateUpdate();
    void releaseResources();
    void initMapViewer();
    void stateOpen();
    void updateWaitClose();
    void updateKnobRelease();
    void updateKnobHold();
    void updateKnobGrab();
    void updateCursorRelease();
    void updateCursorPress();
    void updateCursorMove();
    void updateButtons();
    void updateKnobDrag();
    void updateTouch();
    void stateBuildList();
    void stateLoadMap();
    void stateLoadBg();
    BOOL requestClose();
    void runMainState();
    void startButtonInput();
    void startTouchInput();
    void loadObjGfx();
    void stateClosing();
    void stateClose();
    void stateOpening();

    /* 0x91 */ u8 unk_91[3];
    /* 0x94 */ u32 slideY;
    /* 0x98 */ u16 listScroll;
    /* 0x9a */ u16 listScrollTarget;
    /* 0x9c */ u16 flags;
    /* 0x9e */ u8 selfMarkerX;
    /* 0x9f */ u8 selfMarkerY;
    /* 0xa0 */ u8 labelCount;
    /* 0xa1 */ u8 residentCount;
    /* 0xa2 */ u8 placeCount;
    /* 0xa3 */ u8 listTopRow;
    /* 0xa4 */ u8 knobPos;
    /* 0xa5 */ u8 dragStartTouchY;
    /* 0xa6 */ u8 dragStartKnobPos;
    /* 0xa7 */ u8 blinkTimer;
    /* 0xa8 */ u8 selectedMarker;
    /* 0xa9 */ u8 selectedRow;
    /* 0xaa */ u8 returnState;
    /* 0xab */ u8 cursorTarget;
    /* 0xac */ u8 cursorMarker;
    /* 0xad */ u8 mapCursorX;
    /* 0xae */ u8 mapCursorY;
    /* 0xaf */ u8 selfBlinkCounter;
    /* 0xb0 */ BgVramTask screenTasks[2];
    /* 0xf8 */ LabelString textLabels[13];
    /* 0x438 */ MenuScrollKnob scrollKnob;
    /* 0x480 */ MenuCursorBuf0 cursor;
    /* 0x4e4 */ u16 frameScreen[0x400];
    /* 0xce4 */ u16 listScreen[0x400];
    /* 0x14e4 */ u16 listScreenWork[0x400];
    /* 0x1ce4 */ u16 listScreenBase[0x400];
    /* 0x24e4 */ u8 residentEntries[13];
    /* 0x24f1 */ u8 placeEntries[13];
    /* 0x24fe */ MapViewMarker terrainMarkers[3];
    /* 0x2507 */ MapViewMarker buildingMarkers[14];
};

static inline BOOL IsZero(u8 v) {
    if (v == 0) return TRUE;
    return FALSE;
}

static inline BOOL Unk_ov120_022942c0_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) return TRUE;
    return FALSE;
}

extern "C" u8 sMapViewPlacesButtonCells[32];
extern "C" u8 sMapViewResidentsButtonCells[32];
extern "C" u8 sMapViewFrameCells[80];


extern "C" MapViewerMenu *MapViewerMenu_Create() { return new MapViewerMenu(); }

BOOL MapViewerMenu::onCreate() {
    initMapViewer();
    setTransitionState(0);
    setPhase(1);
    return TRUE;
}

BOOL MapViewerMenu::onDelete() {
    ((MenuLauncher *)(ProcBase_GetParent(this)))->onChildClosed();
    releaseResources();
    return TRUE;
}

BOOL MapViewerMenu::onDraw() {
    u32 h = slideY + 0x60;
    if (testFlags(4)) {
        if (testFlags(8)) {
            ((ScrollKnob *)(&scrollKnob))->moveTo(0x67, slideY - 0x12 + knobPos);
        }
        ((MenuCursorBase *)(&cursor))->drawWrapped();
        Oam_DrawCell(1, (GXOamAttr *)sMapViewFrameCells, 0x80, h, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        s32 a, b;
        if (testFlags(1)) {
            b = 0xc;
            a = 0xd;
        } else {
            b = 0xb;
            a = 0xe;
        }
        Oam_DrawCell(1, (GXOamAttr *)sMapViewPlacesButtonCells, 0x80, h, a, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        Oam_DrawCell(1, (GXOamAttr *)sMapViewResidentsButtonCells, 0x80, h, b, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        u32 t = cursorMarker;
        if (t != 0xe) {
            MapViewMarker *e = &buildingMarkers[t];
            if (e->cell != 0xc) {
                drawMapIcon(e->x, slideY + e->y, 0xb, 0, -1);
            }
        }
        selfBlinkCounter = (selfBlinkCounter + 1) & 0xf;
        if ((selfBlinkCounter & 0xc) != 0) {
            drawMapIcon(selfMarkerX, selfMarkerY + slideY, 0xa, 0, -1);
        }
        for (s32 i = 0; i < 3; i++) {
            MapViewMarker *e = &terrainMarkers[i];
            u32 c = e->cell;
            if (c != 0xc) {
                drawMapIcon(e->x, slideY + e->y, (u8)(c & 0x7f), (c & 0x80) ? 1 : 0, -1);
            }
        }
        for (s32 i = 0; i < 14; i++) {
            MapViewMarker *e = &buildingMarkers[i];
            u8 *q = &e->cell;
            if (*q != 0xc) {
                s32 v;
                if (i == selectedMarker && !testFlags(0x100)) {
                    v = 8;
                } else {
                    v = -1;
                }
                drawMapIcon(e->x, slideY + e->y, *q, 0, v);
            }
        }
        if (testFlags(8)) {
            scrollKnob.draw();
        }
    }
    return TRUE;
}

extern "C" const u8 sMapViewFacilityCells[5] = {2, 3, 4, 5, 6};
extern "C" u8 sMapViewPlacesButtonCells[32] = {0xd3, 0x00, 0x2a, 0x40, 0xa2, 0xe1, 0x00, 0x00, 0xd3, 0x80, 0x3a, 0x00, 0xa4, 0xe1, 0x00, 0x00, 0xe3, 0x40, 0x2a, 0x00, 0xe2, 0xe1, 0x00, 0x00, 0xe3, 0x00, 0x3a, 0x00, 0xe4, 0xe1, 0xff, 0xff};
extern "C" const u8 sMapViewPlaceMarkers[5] = {0xb, 0xc, 9, 0xa, 0xd};

BOOL MapViewerMenu::execTransition() {
    static Unk_ov120_02295010_Fn tbl[7] = {
        &MapViewerMenu::stateLoadBg,  &MapViewerMenu::stateLoadMap, &MapViewerMenu::stateBuildList,
        &MapViewerMenu::stateOpen,    &MapViewerMenu::stateOpening, &MapViewerMenu::stateClose,
        &MapViewerMenu::stateClosing};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}




extern "C" Unk_ov120_02293a2c_Oam sMapViewIconCell = {0xf8, 0x1f8, 0, 1, 0xc0, 0x1c, 0xffff};
extern "C" u8 sMapViewFrameCells[80] = {0xb8, 0x40, 0x9d, 0x81, 0xab, 0x61, 0x00, 0x00, 0xb8, 0x40, 0xbd, 0x81, 0xaf, 0x61, 0x00, 0x00, 0xb8, 0x40, 0xdd, 0x81, 0xb3, 0x61, 0x00, 0x00, 0xb8, 0x40, 0xfd, 0x81, 0xb7, 0x61, 0x00, 0x00, 0xb8, 0x00, 0x1d, 0x40, 0xbb, 0x61, 0x00, 0x00, 0xb8, 0x40, 0xf5, 0x81, 0xd9, 0x60, 0x00, 0x00, 0xb8, 0x40, 0xd5, 0x81, 0xd9, 0x60, 0x00, 0x00, 0xb8, 0x40, 0xb5, 0x81, 0xd9, 0x60, 0x00, 0x00, 0xb8, 0x40, 0x15, 0x90, 0xd8, 0x60, 0x00, 0x00, 0xb8, 0x40, 0x95, 0x81, 0xd8, 0x60, 0xff, 0xff};
extern "C" u8 sMapViewResidentsButtonCells[32] = {0xd3, 0x00, 0x4d, 0x40, 0xa5, 0xc1, 0x00, 0x00, 0xd3, 0x80, 0x5d, 0x00, 0xa7, 0xc1, 0x00, 0x00, 0xe3, 0x40, 0x4d, 0x00, 0xe5, 0xc1, 0x00, 0x00, 0xe3, 0x00, 0x5d, 0x00, 0xe7, 0xc1, 0xff, 0xff};
extern "C" ProcProfile sMapViewerMenuProfile = {(void *(*)())MapViewerMenu_Create, 0xa3, 0xa7};

void MapViewerMenu::runMainState() {
    static Unk_ov120_02295010_Fn tbl[10] = {
        &MapViewerMenu::updateTouch,         &MapViewerMenu::updateKnobDrag,    &MapViewerMenu::updateButtons,
        &MapViewerMenu::updateCursorMove,    &MapViewerMenu::updateCursorPress, &MapViewerMenu::updateCursorRelease,
        &MapViewerMenu::updateKnobGrab,      &MapViewerMenu::updateKnobHold,    &MapViewerMenu::updateKnobRelease,
        &MapViewerMenu::updateWaitClose};
    (this->*tbl[mainState])();
}

BOOL MapViewerMenu::execMain() {
    preInputUpdate();
    runMainState();
    postInputUpdate();
    return TRUE;
}

BOOL MapViewerMenu::execPhase3() { return TRUE; }

BOOL MapViewerMenu::execPhase4() { return TRUE; }

BOOL MapViewerMenu::execClosed() {
    ProcBase_RequestDelete(this);
    return TRUE;
}

BOOL MapViewerMenu::requestClose() {
    ((MenuLauncher *)(ProcBase_GetParent(this)))->setNextRequest(0x44, 1);
    transitionState = 5;
    setPhase(1);
    return TRUE;
}

void MapViewerMenu::stateLoadBg() {
    setupBgLayers();
    loadBgGfx();
    setTransitionState(1);
}

void MapViewerMenu::stateLoadMap() {
    loadMapImage();
    setTransitionState(2);
}

void MapViewerMenu::stateBuildList() {
    showResidentsList();
    clipListScreen();
    setTransitionState(3);
}

void MapViewerMenu::stateOpen() {
    loadObjGfx();
    {
        MsgString9C townName;
        TownId_GetNameString(gSaveTownId, &townName);
        String_SetSlot(0, &townName);
        LabelString *q = allocTextLabel();
        q->createLabel(8, 0x1ab, 0x12, 0xf, 0, 0);
        String_Load2dMenu(q, 0xa9);
        q->redrawAligned(1, 0);
    }
    beginSubSlideIn(0xa, 0, 0, 0x30);
    Gfx2d_ShowLayer(4);
    applySlideOffset(4, 0, 0);
    Gfx2d_ShowLayer(6);
    applySlideOffset(6, 0, 0x50 - listScroll);
    setFlags(4);
    slideY = getSlideOffsetY();
    setTransitionState(4);
}

void MapViewerMenu::stateOpening() {
    if (stepSlideIn(0)) {
        setPhase(2);
        cursorMarker = 8;
        mapCursorX = buildingMarkers[cursorMarker].x;
        mapCursorY = buildingMarkers[cursorMarker].y;
        if (*(volatile u8 *)&mapCursorY > 4) {
            mapCursorY = *(volatile u8 *)&mapCursorY - 4;
        } else {
            mapCursorY = 0;
        }
        if (*(volatile u8 *)&mapCursorX < 0xfc) {
            mapCursorX = *(volatile u8 *)&mapCursorX + 4;
        } else {
            mapCursorX = 0xff;
        }
        setFlags(0x800);
        startButtonInput();
    }
    applySlideOffset(4, 0, 0);
    applySlideOffset(6, 0, 0x50 - listScroll);
    slideY = getSlideOffsetY();
}

void MapViewerMenu::stateClose() {
    hideCursor();
    beginSubSlideOut(0xa, 0, 0, 0x30);
    applySlideOffset(4, 0, 0);
    applySlideOffset(6, 0, 0x50 - listScroll);
    setTransitionState(6);
    slideY = getSlideOffsetY();
}

void MapViewerMenu::stateClosing() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(4);
        Gfx2d_ResetLayer(6);
        clearFlags(4);
        setPhase(5);
    } else {
        applySlideOffset(4, 0, 0);
        applySlideOffset(6, 0, 0x50 - listScroll);
        slideY = getSlideOffsetY();
    }
}

void MapViewerMenu::initMapViewer() {
    volatile VecFx32 v;
    labelCount = 0;
    flags = 0;
    listScroll = 0;
    listScrollTarget = 0;
    knobPos = 0;
    slideY = 0;
    blinkTimer = 0;
    cursorTarget = 0;
    mapCursorX = 0x58;
    mapCursorY = 0x70;
    cursorMarker = 0xe;
    selectEntry(0);
    buildEntryLists();
    if (IsZero(gFieldSceneKind)) {
        VecFx32 *p = (VecFx32 *)PlayerActor_GetBodyPos(4);
        v.x = p->x;
        v.y = p->y;
        v.z = p->z;
    } else {
        Scene_GetWarpRequest();
        VecFx32 *p = ScenePos_GetPos(&gTownReturnPos);
        v.x = p->x;
        v.y = p->y;
        v.z = p->z;
    }
    s32 z = (v.z + 0x800) >> 12;
    s32 x = (v.x + 0x800) >> 12;
    selfMarkerX = x - 8;
    selfMarkerY = z + 13;
    ((ScrollKnob *)(&scrollKnob))->setState(1);
}

void MapViewerMenu::releaseResources() {
    resetTextLabels();
    screenTasks[0].cancel();
    screenTasks[1].cancel();
}

void MapViewerMenu::preStateUpdate() {
    resetTextLabels();
}

void MapViewerMenu::postStateUpdate() {
    if (isListScrolling()) {
        updateListScroll();
        Gfx2d_SetLayerOffset(6, 0, listScroll - 0x50);
        if (listTopRow != (listScroll >> 4)) {
            setFlags(0x80);
        }
    }
    updateBlink();
    if (testFlags(0x80)) {
        clipListScreen();
        clearFlags(0x80);
    }
    if (testFlags(0x20)) {
        if (((BgVramTask *)(screenTasks + 1))->requestScreen(frameScreen, 4, 0x800, 0)) {
            clearFlags(0x20);
        }
    }
    if (testFlags(2)) {
        if (((BgVramTask *)(screenTasks))->requestScreen(listScreen, 6, 0x800, 0)) {
            clearFlags(2);
        }
    }
}

void MapViewerMenu::preInputUpdate() {
    preStateUpdate();
    scrollKnob.update();
    cursor.update();
}

void MapViewerMenu::postInputUpdate() {
    postStateUpdate();
}

void MapViewerMenu::setupBgLayers() {
    Gfx2d_SetLayerPriority(4, 2);
    Gfx2d_SetLayerPriority(6, 2);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
}

void MapViewerMenu::loadBgGfx() {
    Heap *h = gCurrentHeap;
    Gfx2d_LoadPaletteFile("menu/map/b_map_bg.bpl", h, 4, 1, 1, 0xf);
    Gfx2d_LoadCharFile("menu/map/b_map_bg_0.bch", h, 4, 0x11, 0x11, 0x5f);
    Gfx2d_LoadCharFile("menu/map/b_map_bg_1.bch", h, 4, 0x230, 0x230, 0x25f);
    File_LoadToBuffer("menu/map/b_map_a_bg.bsc", frameScreen, 0x800);
    Gfx2d_LoadScreen((u8 *)frameScreen, 4, 0x800, 0);
    File_LoadToBuffer("menu/map/b_map_b_bg.bsc", listScreenBase, 0x800);
    BgScreen_SetRectPalette(listScreenBase, 0x13, 0, 0x1c, 1, 4);
}


TownMapMarkers MapViewerMenu_loadMapImage_obj;
u8 MapViewerMenu_loadMapImage_obj_init;
void MapViewerMenu::loadMapImage() {
    Heap *h = gCurrentHeap;
    u8 *p = (u8 *)Heap_AllocTail(h, 0x2000);
    if (!MapViewerMenu_loadMapImage_obj_init) {
        HOST_STATIC_CONSTRUCT(MapViewerMenu_loadMapImage_obj);
        MapViewerMenu_loadMapImage_obj_init = 1;
    }
    Shared_TownMapMarkers_Clear(&MapViewerMenu_loadMapImage_obj);
    TownMapImage_Build(p, &MapViewerMenu_loadMapImage_obj);
    Gfx2d_LoadCharRange(p, 4, 0x60, 0x60, 0x15f);
    setupMarkers(&MapViewerMenu_loadMapImage_obj);
    Heap_Free(h, p);
}

void MapViewerMenu::loadObjGfx() {
    Heap *h = gCurrentHeap;
    Gfx2d_LoadPaletteFile("menu/map/b_map_obj.bpl", h, 8, 6, 6, 0xe);
    Gfx2d_LoadCharFile("menu/map/b_map_obj_0.bch", h, 8, 0xc0, 0xc0, 0xff);
    Gfx2d_LoadCharFile("menu/map/b_map_obj_1.bch", h, 8, 0x180, 0x180, 0x1ff);
}

void MapViewerMenu::updateTouch() {
    if (checkSwitchToButtons(1)) {
        startButtonInput();
        return;
    }
    if (Unk_ov120_022942c0_Both()) {
        if (touchListTabs() == 0) {
            if (touchScrollKnob()) {
                ((ScrollKnob *)(&scrollKnob))->setState(2);
                setMainState(1);
            } else if (touchMarker() == 0) {
                s32 t = touchListRow();
                if (t != 0) {
                    return;
                }
            }
        }
    }
}

void MapViewerMenu::updateKnobDrag() {
    if (gTouchHeld == 0) {
        ((ScrollKnob *)(&scrollKnob))->setState(3);
        startTouchInput();
    }
    scrollListToTouch();
}

void MapViewerMenu::updateButtons() {
    if (checkSwitchToTouch()) {
        startTouchInput();
        return;
    }
    if (moveCursorByPad(takeRepeatedKeys())) {
        if (testFlags(8)) {
            if (cursorTarget >= 2 && cursorTarget <= 7) {
                setListScrollTarget(listScroll & ~0xf);
            }
        }
        moveCursorToTarget();
        return;
    }
    u32 k = gPad[1];
    if ((k & 1) != 0) {
        pressCursor();
    } else if ((k & 0x800) != 0) {
        selectEntry(0);
        highlightListRow(0xe);
        if (cursorTarget >= 2 && cursorTarget <= 7) {
            moveMapCursorToRow();
        }
        cursorMarker = findMarkerAt(mapCursorX, mapCursorY);
        setFlags(0x800);
        setMainState(9);
        moveCursorToTarget();
    }
}

void MapViewerMenu::updateCursorMove() {
    if (((MenuCursorBase *)(&cursor))->isMoving() == 0) {
        setMainState(returnState);
        runMainState();
    }
}

void MapViewerMenu::updateCursorPress() {
    if (((HandCursor *)(&cursor))->isAnimDone()) {
        s32 r = onCursorDecide();
        if (r == 1) {
        } else if (r == 2) {
            setListScroll(0);
            listTopRow = 0xff;
            releaseCursor();
        } else {
            releaseCursor();
        }
    }
}

void MapViewerMenu::updateCursorRelease() {
    if (((HandCursor *)(&cursor))->isAnimDone()) {
        refreshCursor();
        if (testFlags(0x800)) {
            setMainState(9);
        } else {
            setMainState(2);
        }
    }
}

void MapViewerMenu::updateKnobGrab() {
    if (((ScrollKnob *)(&scrollKnob))->areAnimsDone()) {
        setMainState(7);
    }
}

void MapViewerMenu::updateKnobHold() {
    if ((gPad[0] & 1) == 0) {
        ((ScrollKnob *)(&scrollKnob))->setState(3);
        setMainState(8);
    } else {
        scrollListByPad();
    }
}

void MapViewerMenu::updateKnobRelease() {
    if (((ScrollKnob *)(&scrollKnob))->areAnimsDone()) {
        releaseCursor();
        clearFlags(0x1000);
    }
}

void MapViewerMenu::updateWaitClose() {
    u32 v = gPad[1];
    BOOL r = TRUE;
    if ((v & 1) != 0) goto call;
    if ((v & 0x400) != 0) goto call;
    if ((v & 2) != 0) goto call;
    if (gTouchHeld == 0 || gTouchChanged == 0) r = FALSE;
    if (r) {
    call:
        requestClose();
    }
}

void MapViewerMenu::startTouchInput() {
    hideCursor();
    setMainState(0);
}

void MapViewerMenu::startButtonInput() {
    ((ScrollKnob *)(&scrollKnob))->setState(1);
    showCursor();
    restartKeyRepeat();
    if (testFlags(0x800)) {
        setMainState(9);
    } else {
        setMainState(2);
    }
}

void MapViewerMenu::clipListScreen() {
    volatile u16 v0, v1, v2, v3;
    s32 off, j, i, n;
    MIi_CpuCopy16(listScreenWork, listScreen, 0x800);
    n = listScroll >> 4;
    listTopRow = n;
    off = 0x13;
    for (i = 0; i < n; i++) {
        v0 = 0x10;
        MIi_CpuClear16(v0, listScreen + off, 0x14);
        v1 = 0x10;
        MIi_CpuClear16(v1, listScreen + (off + 0x20), 0x14);
        off += 0x40;
    }
    j = n + 7;
    off = j * 0x40 + 0x13;
    for (; j < 13; j++) {
        v2 = 0x10;
        MIi_CpuClear16(v2, listScreen + off, 0x14);
        v3 = 0x10;
        MIi_CpuClear16(v3, listScreen + (off + 0x20), 0x14);
        off += 0x40;
    }
    setFlags(2);
}

void MapViewerMenu::buildListScreen() {
    s32 i;
    u8 *tbl;
    MIi_CpuCopy16(listScreenBase, listScreenWork, 0x800);
    tbl = getListEntries();
    for (i = 0; i < 13; i++) {
        s32 a = getEntryIconRow(tbl[i], i) * 0x40 + 0x13;
        s32 b = i * 0x40 + 0x13;
        listScreenWork[b] = listScreenBase[a];
        listScreenWork[b + 1] = listScreenBase[a + 1];
        listScreenWork[b + 0x20] = listScreenBase[a + 0x20];
        listScreenWork[b + 0x21] = listScreenBase[a + 0x21];
    }
    setFlags(2);
}

u32 MapViewerMenu::getEntryIconRow(u32 x, s32 idx) {
    if (x == 0) return 7;
    if (x < 6) return 0;
    if (x >= 6 && x < 14) return 1;
    switch (x - 14) {
    case 2: return 2;
    case 0: return 3;
    case 3: return 4;
    case 1: return 5;
    case 4: return 6;
    }
    return 7;
}

void MapViewerMenu::resetTextLabels() {
    s32 i = 0;
    labelCount = 0;
    do {
        ((LabelString *)(&textLabels[i]))->destroyLabel();
        i++;
    } while (i < 13);
}

LabelString *MapViewerMenu::allocTextLabel() {
    if (labelCount >= 13) {
        return &textLabels[12];
    }
    labelCount = *(volatile u8 *)&labelCount + 1;
    return &textLabels[labelCount - 1];
}

void MapViewerMenu::buildEntryLists() {
    s32 n = 0;
    s32 m, i;
    m = PlayerDataArray_FindById(gSavePlayers, (u16 *)PlayerData_GetCurrent()->getPlayerId());
    if (m != -1) {
        residentEntries[0] = 1;
        n++;
    }
    for (i = 0; i < 4; i++) {
        if (i == m) {
            continue;
        }
        if (!PlayerDataArray_IsUsed(gSavePlayers, i)) {
            continue;
        }
        residentEntries[n] = i + 2;
        n++;
    }
    for (i = 0; i < 8; i++) {
        if (SaveVillagers_IsOccupied(gSaveVillagers, i)) {
            residentEntries[n] = i + 6;
            n++;
        }
    }
    residentCount = n;
    for (; n < 0xd; n++) {
        placeEntries[n] = 0;
    }
    n = 0;
    for (i = 0; i < 5; i++) {
        placeEntries[n] = i + 0xe;
        n++;
    }
    placeCount = n;
    for (; n < 0xd; n++) {
        placeEntries[n] = 0;
    }
}

void MapViewerMenu::layoutListLabels() {
    if (testFlags(1)) {
        buildEntryLabels(placeEntries);
    } else {
        buildEntryLabels(residentEntries);
    }
}

void MapViewerMenu::buildEntryLabels(u8 *tbl) {
    s32 i;
    for (i = 0; i < 0xd; i++) {
        LabelString *w = allocTextLabel();
        w->createLabel(6, (i << 4) + 0x160, 8, 1, 0xf, 0);
        setEntryName(w, tbl[i]);
        w->redrawAligned(0, 0);
    }
}

void MapViewerMenu::setEntryName(MsgString *p, u32 idx) {
    if (idx == 0) {
        p->clear();
    } else if (idx == 1) {
        PopupChoice_CopyPlayerIdName(p, PlayerData_GetCurrent()->getPlayerId());
    } else if (idx >= 2 && idx < 6) {
        PopupChoice_CopyResidentName(p, idx - 2);
    } else if (idx >= 6 && idx < 0xe) {
        PopupChoice_CopyVillagerName(p, idx - 6);
    } else if (idx >= 0xe && idx < 0x13) {
        String_Load2dMenu(p, idx + 0x88);
    } else {
        p->clear();
    }
}

void MapViewerMenu::showResidentsList() {
    clearFlags(1);
    rebuildList();
}

void MapViewerMenu::showPlacesList() {
    setFlags(1);
    rebuildList();
}

void MapViewerMenu::rebuildList() {
    s32 k;
    buildListScreen();
    layoutListLabels();
    if (getListScrollMax() == 0) {
        clearFlags(8);
        k = 4;
    } else {
        setFlags(8);
        k = 3;
    }
    BgScreen_SetRectPalette(frameScreen, 0x1d, 0xa, 0x1d, 0x15, k);
    setFlags(0x20);
    highlightListRow(selectedRow);
}

u8 *MapViewerMenu::getListEntries() {
    if (testFlags(1)) {
        return placeEntries;
    }
    return residentEntries;
}

s32 MapViewerMenu::getListCount() {
    if (testFlags(1)) {
        return placeCount;
    }
    return residentCount;
}

s32 MapViewerMenu::getListScrollMax() {
    u32 r = getListCount();
    if (r <= 6) {
        return 0;
    }
    return (r - 6) << 4;
}

BOOL MapViewerMenu::touchListRow() {
    s32 x = gTouchCurX;
    s32 y = gTouchCurY;
    if (x < 0x98 || x > 0xe8) {
        return FALSE;
    }
    if (y < 0x50 || y >= 0xb0) {
        return FALSE;
    }
    selectEntry(((y + (listScroll - 0x50)) >> 4) + 0xf);
    return TRUE;
}

void MapViewerMenu::drawMapIcon(s32 x, s32 y, s32 n, s32 flag, s32 pal) {
    u16 t;
    sMapViewIconCell.tile = n * 2 + 0xc0;
    if (flag != 0) {
        t = sMapViewIconCell.pal | 8;
        sMapViewIconCell.pal = t;
    }
    Oam_DrawObj(1, &sMapViewIconCell, x, y, pal, 1, 0);
    if (flag != 0) {
        sMapViewIconCell.pal = t & 0x17;
    }
}

void MapViewerMenu::setupMarkers(TownMapMarkers *src) {
    s32 k, i;
    u32 j;
    TownMapMarker *rec;
    i = 0;
    k = i;
    for (; k < 3; i++, k++) {
        rec = (TownMapMarker *)Shared_TownMapMarkers_Get(src, i);
        if (rec != 0) {
            switch (TownMapMarkers_GetKind(src, i)) {
            case 0:
                terrainMarkers[k].cell = 8;
                break;
            case 1:
                terrainMarkers[k].cell = 7;
                break;
            case 2:
                terrainMarkers[k].cell = 9;
                break;
            case 3:
                terrainMarkers[k].cell = 0x89;
                break;
            default:
                terrainMarkers[k].cell = 0xc;
                break;
            }
            terrainMarkers[k].x = rec->x - 8;
            terrainMarkers[k].y = rec->y + 0x10;
        } else {
            terrainMarkers[k].cell = 0xc;
        }
    }
    j = 3;
    k = 0;
    for (; k < 0xe; j++, k++) {
        rec = (TownMapMarker *)Shared_TownMapMarkers_Get(src, j);
        if (rec != 0) {
            if (j >= 3 && j <= 0xa) {
                buildingMarkers[k].cell = 0;
            } else if (j == 0xb) {
                buildingMarkers[k].cell = 1;
            } else {
                buildingMarkers[k].cell = *(sMapViewFacilityCells + j - 0xc);
            }
            buildingMarkers[k].x = rec->x - 8;
            buildingMarkers[k].y = rec->y + 0x10;
        } else {
            buildingMarkers[k].cell = 0xc;
        }
    }
}

BOOL MapViewerMenu::touchMarker() {
    u32 r = findMarkerAt(gTouchCurX, gTouchCurY);
    if (r == 0xe) {
        return FALSE;
    }
    selectEntry(r + 1);
    return TRUE;
}

u32 MapViewerMenu::findMarkerAt(s32 x, s32 y) {
    s32 i;
    for (i = 0; i < 0xe; i++) {
        MapViewMarker *e = &buildingMarkers[i];
        if (e->cell != 0xc) {
            s32 px = e->x;
            if (px - 8 < x && px + 8 > x) {
                s32 py = e->y;
                if (py - 8 < y && py + 8 > y) {
                    return (u8)i;
                }
            }
        }
    }
    return 0xe;
}

void MapViewerMenu::selectEntry(u8 v) {
    if (v == 0) {
        selectedMarker = 0xe;
        selectedRow = 0xe;
        stopBlink();
        return;
    }
    startBlink();
    selectedRow = selectionToListRow(v);
    selectedMarker = selectionToMarker(v);
    if (v >= 1 && v < 0xf) {
        clearFlags(0x200);
        if (testFlags(1)) {
            if (v >= 1 && v <= 9) {
                showResidentsList();
                jumpToSelection();
                return;
            }
        } else {
            if (v < 1 || v > 9) {
                showPlacesList();
                jumpToSelection();
                return;
            }
        }
    } else {
        setFlags(0x200);
    }
    ensureSelectionVisible();
    highlightListRow(0xe);
    highlightListRow(selectedRow);
}

void MapViewerMenu::highlightListRow(u8 v) {
    setFlags(0x80);
    if (v == 0xe) {
        BgScreen_SetRectPalette(listScreenWork, 0x13, 0, 0x1c, 0x19, 4);
    } else if (v == 0xd) {
        BgScreen_SetRectPalette(listScreenWork, 0x13, 0, 0x1c, 7, 3);
    } else {
        BgScreen_SetRectPalette(listScreenWork, 0x13, v * 2, 0x1c, v * 2 + 1, 3);
    }
}

u32 MapViewerMenu::selectionToListRow(u8 v) {
    if (v == 9) {
        return 0xd;
    }
    if (v >= 1 && v < 9) {
        s32 t = v + 5;
        s32 i = 0;
        s32 n = residentCount;
        for (; i < n; i++) {
            if (t == residentEntries[i]) {
                return (u8)i;
            }
        }
        return 0xe;
    }
    if (v < 0xf && v >= 0xa) {
        return (u8)(v - 0xa);
    }
    if (v < 0x1c && v >= 0xf) {
        return (u8)(v - 0xf);
    }
    return 0xe;
}

u32 MapViewerMenu::selectionToMarker(u8 v) {
    if (v >= 1 && v < 0xf) {
        return (u8)(v - 1);
    }
    if (v >= 0xf && v < 0x1c) {
        u32 b = getListEntries()[v - 0xf];
        if (b == 0) {
            return 0xe;
        }
        if (b == 1 || (b >= 2 && b < 6)) {
            return 8;
        }
        if (b >= 6 && b < 0xe) {
            return (u8)(b - 6);
        }
        if (b >= 0xe && b < 0x13) {
            return sMapViewPlaceMarkers[b - 0xe];
        }
    }
    return 0xe;
}

void MapViewerMenu::jumpToSelection() {
    u32 a = selectedRow;
    u32 v;
    if (a <= 5 || a == 0xd) {
        v = 0;
    } else {
        v = (a - 5) << 4;
    }
    setListScroll(v);
    listTopRow = 0xff;
}

void MapViewerMenu::ensureSelectionVisible() {
    u32 a = selectedRow;
    if (a != 0xe) {
        if (a == 0xd) {
            setListScrollTarget(0);
        } else {
            if ((s32)a < (listScroll + 0xf) >> 4) {
                setListScrollTarget(a << 4);
            }
            s32 h = listScroll >> 4;
            s32 lo;
            if (selectedRow <= 5) {
                lo = 0;
            } else {
                lo = selectedRow - 5;
            }
            if (h < lo) {
                setListScrollTarget(lo << 4);
            }
        }
    }
}

void MapViewerMenu::setListScroll(u32 v) {
    listScroll = v;
    listScrollTarget = listScroll;
    setFlags(0x10);
}

void MapViewerMenu::setListScrollTarget(u32 v) {
    listScrollTarget = v;
    setFlags(0x10);
}

BOOL MapViewerMenu::isListScrolling() { return testFlags(0x10); }

void MapViewerMenu::updateListScroll() {
    s32 n = getListScrollMax();
    if (n == 0) {
        clearFlags(0x10);
        knobPos = 0;
    } else {
        u32 tg = listScrollTarget;
        u32 cur = listScroll;
        if (cur == tg) {
            clearFlags(0x10);
        } else if (cur < tg) {
            listScroll = *(volatile u16 *)&listScroll + 8;
            if (listScroll > listScrollTarget) {
                listScroll = listScrollTarget;
            }
        } else if (cur < 8) {
            listScroll = tg;
        } else {
            listScroll = *(volatile u16 *)&listScroll - 8;
            if (listScroll < listScrollTarget) {
                listScroll = listScrollTarget;
            }
        }
        knobPos = DS_DIV(listScroll * 0x58, n);
    }
}

BOOL MapViewerMenu::touchScrollKnob() {
    if (!testFlags(8)) {
        return FALSE;
    }
    if (((MenuScrollKnob *)(&scrollKnob))->hitTest(gTouchCurX, gTouchCurY)) {
        dragStartTouchY = gTouchCurY;
        dragStartKnobPos = knobPos;
        return TRUE;
    }
    return FALSE;
}

void MapViewerMenu::scrollListToTouch() {
    s32 t = dragStartKnobPos + (gTouchCurY - dragStartTouchY);
    if (t < 0) {
        t = 0;
    } else if (t > 0x58) {
        t = 0x58;
    }
    setListScroll(t * getListScrollMax() / 0x58);
}

void MapViewerMenu::scrollListByPad() {
    s32 t = listScrollTarget;
    u32 keys = gPad[0];
    if (keys & 0x40) {
        t = t - 4;
    } else if (keys & 0x80) {
        t = t + 4;
    }
    s32 m = getListScrollMax();
    if (t < 0) {
        t = 0;
    } else if (t > m) {
        t = m;
    }
    setListScroll(t);
}

BOOL MapViewerMenu::touchListTabs() {
    s32 x = gTouchCurX;
    s32 y = gTouchCurY;
    if (y < 0x38 || y > 0x4c) {
        return FALSE;
    }
    if (testFlags(1)) {
        if (x < 0xcc || x > 0xe4) {
            return FALSE;
        }
        selectEntry(0);
        showResidentsList();
    } else {
        if (x < 0xb0 || x > 0xc8) {
            return FALSE;
        }
        selectEntry(0);
        showPlacesList();
    }
    setListScroll(0);
    listTopRow = 0xff;
    return TRUE;
}

void MapViewerMenu::updateBlink() {
    if (testFlags(0x40)) {
        if (blinkTimer != 0) {
            blinkTimer = *(volatile u8 *)&blinkTimer - 1;
        }
        if (blinkTimer == 0) {
            if (testFlags(0x200)) {
                clearFlags(0x100);
            } else {
                highlightListRow(selectedRow);
            }
            blinkTimer = 0xf;
        } else if (blinkTimer == 5) {
            if (testFlags(0x200)) {
                setFlags(0x100);
            } else {
                highlightListRow(0xe);
            }
        }
    }
}

void MapViewerMenu::startBlink() {
    setFlags(0x40);
    clearFlags(0x100);
    blinkTimer = 0xf;
}

void MapViewerMenu::stopBlink() {
    clearFlags(0x40);
    clearFlags(0x100);
}

void MapViewerMenu::showCursor() {
    if (!testFlags(8) && cursorTarget == 8) {
        cursorTarget = 0;
    }
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    ((MenuCursorBase *)(&cursor))->warpTo(a, b);
    if (cursorTarget >= 2 && cursorTarget <= 7) {
        setListScrollTarget(listScroll & ~0xf);
    }
    ((MenuCursor *)(&cursor))->setAnimIfChanged(1);
    refreshCursor();
}

s32 MapViewerMenu::getCursorTargetX() {
    if (testFlags(0x800)) {
        return mapCursorX;
    }
    u32 t = cursorTarget;
    if (t >= 2 && t <= 7) {
        return 0xa0;
    }
    if (t == 0) {
        return 0xd8;
    }
    if (t == 1) {
        return 0xbc;
    }
    if (t == 8) {
        return ((MenuScrollKnob *)(&scrollKnob))->getGripX();
    }
    return 0x80;
}

s32 MapViewerMenu::getCursorTargetY() {
    if (testFlags(0x800)) {
        return mapCursorY;
    }
    u32 t = cursorTarget;
    if (t >= 2 && t <= 7) {
        return (t - 2) * 16 + 0x58;
    }
    if (t <= 1) {
        return 0x40;
    }
    if (t == 8) {
        return ((MenuScrollKnob *)(&scrollKnob))->getGripY();
    }
    return 0x60;
}

void MapViewerMenu::hideCursor() {
    ((MenuCursor *)(&cursor))->setAnimIfChanged(0);
    cursor.update();
}

void MapViewerMenu::moveCursorToTarget() {
    if (testFlags(0x4000)) {
        s32 a = getCursorTargetX();
        s32 b = getCursorTargetY();
        ((MenuCursorBase *)(&cursor))->warpTo(a, b);
        clearFlags(0x4000);
    } else {
        s32 a = getCursorTargetX();
        s32 b = getCursorTargetY();
        ((MenuCursorBase *)(&cursor))->moveToEase(a, b, 3, 1);
        returnState = mainState;
        setMainState(3);
    }
}

void MapViewerMenu::pressCursor() {
    ((MenuCursor *)(&cursor))->setPosePress();
    setMainState(4);
}

void MapViewerMenu::releaseCursor() {
    ((MenuCursorBase *)(&cursor))->setPoseRelease();
    setMainState(5);
}

void MapViewerMenu::refreshCursor() {
    ((MenuCursorBase *)(&cursor))->setPoseIdle();
    cursor.update();
}

BOOL MapViewerMenu::moveCursorByPad(u32 pad) {
    u32 old = cursorTarget;
    if (old >= 2 && old <= 7) {
        if (testFlags(8) && MenuKeys_HasRight(pad)) {
            cursorTarget = 8;
        } else if (MenuKeys_HasUp(pad)) {
            if (*(volatile u8 *)&cursorTarget > 2) {
                cursorTarget = *(volatile u8 *)&cursorTarget - 1;
            } else {
                cursorTarget = 1;
            }
        } else if (MenuKeys_HasDown(pad)) {
            s32 n = getListCount() - 1;
            if (cursorTarget < 7 && cursorTarget < n + 2) {
                cursorTarget = *(volatile u8 *)&cursorTarget + 1;
            }
        }
    } else if (old == 8) {
        if (MenuKeys_HasUp(pad)) {
            cursorTarget = 0;
        } else if (MenuKeys_HasLeft(pad)) {
            s32 v = ((MenuScrollKnob *)(&scrollKnob))->getGripY();
            if (v < 0x50) {
                v = 0x50;
            }
            if (v >= 0xb0) {
                v = 0xaf;
            }
            cursorTarget = ((v - 0x50) >> 4) + 2;
        }
    } else if (old <= 1) {
        if (MenuKeys_HasDown(pad)) {
            cursorTarget = 2;
        } else if (MenuKeys_HasLeft(pad)) {
            cursorTarget = 1;
        } else if (MenuKeys_HasRight(pad)) {
            if (cursorTarget == 0 && testFlags(8)) {
                cursorTarget = 8;
            } else {
                cursorTarget = 0;
            }
        }
    }
    if (old != cursorTarget) {
        return TRUE;
    }
    return FALSE;
}

s32 MapViewerMenu::onCursorDecide() {
    if (testFlags(0x800)) {
        selectEntry(cursorMarker + 1);
        return 0;
    }
    u32 t = cursorTarget;
    if (t == 8) {
        setMainState(6);
        ((ScrollKnob *)(&scrollKnob))->setState(2);
        setFlags(0x1000);
        return 1;
    } else if (t == 0) {
        if (testFlags(1)) {
            selectEntry(0);
            showResidentsList();
            return 2;
        }
        return 0;
    } else if (t == 1) {
        if (!testFlags(1)) {
            selectEntry(0);
            showPlacesList();
            return 2;
        }
        return 0;
    } else if (t >= 2 && t <= 7) {
        selectEntry(listTopRow + t + 0xd);
        return 0;
    }
    return 0;
}

void MapViewerMenu::moveMapCursorToRow() {
    u32 idx = selectionToMarker(listTopRow + cursorTarget + 0xd);
    MapViewMarker *e = &buildingMarkers[idx];
    if (e->cell == 0xc) {
        mapCursorX = 0x58;
        mapCursorY = 0x70;
    } else {
        mapCursorX = e->x;
        mapCursorY = e->y;
    }
}

BOOL MapViewerMenu::testFlags(u32 mask) {
    if (flags & mask) {
        return TRUE;
    }
    return FALSE;
}

void MapViewerMenu::setFlags(u32 mask) { flags = flags | mask; }

void MapViewerMenu::clearFlags(u32 mask) { flags = flags & ~mask; }

MapViewMarker::MapViewMarker() {}

MapViewMarker::~MapViewMarker() {}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov120_02292d00) {
    HOST_OVERLAY_VAR(sMapViewPlacesButtonCells),
    HOST_OVERLAY_VAR(sMapViewIconCell),
    HOST_OVERLAY_VAR(sMapViewFrameCells),
    HOST_OVERLAY_VAR(sMapViewResidentsButtonCells),
    HOST_OVERLAY_VAR(sMapViewerMenuProfile),
    HOST_OVERLAY_VAR(MapViewerMenu_loadMapImage_obj),
    HOST_OVERLAY_VAR(MapViewerMenu_loadMapImage_obj_init),
    HOST_OVERLAY_VARS_END
};
