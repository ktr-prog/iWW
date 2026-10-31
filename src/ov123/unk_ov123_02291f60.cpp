#include "ds_div.h"
#include "host_labels.h"
#include "host_overlay_vars.h"
#include "types.h"
#include "Unk_020d8c7c.h"
#include "menu/MenuProc.h"
#include "ui/HandCursor.h"
#include "menu/MenuLauncher.h"
#include "ui/LabelString.h"
#include "gfx/BgVramTask.h"
#include "menu/MenuCursor.h"
#include "menu/MenuBottomButtons.h"
#include "sys/ProcProfile.h"
#include "player/PlayerData.h"
#include "save/BlancaFaceRecord.h"
#include "save/Pattern.h"
#include "save/PatternOrder.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0206f834.h"
#include "proto/main/unk_02070560.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov123/unk_ov123_02291f60.h"

#include "nitro/gxoam.h"
#include "gfx/PatternTexCache.h"
#include "proto/autoload_2/unk_020e8558.h"

extern "C" {
#define gSaveBlancaFace HOST_LABEL(u8 *, gSaveBlancaFace)
extern u16 gPad[];

void MIi_CpuCopy32(const void *src, void *dst, u32 n);
}











struct PatternShapeCornerCell {
    u16 attr0;
    u16 a : 9;
    u16 b : 5;
    u16 c : 2;
    u16 attr2;
    u16 attr3;
};

struct Unk_ov123_02293010_Q {
    u8 a, b, c, d;
    Unk_ov123_02293010_Q() {}
};


class PatternEditorMenu;
typedef void (PatternEditorMenu::*Unk_ov123_022959c4_Fn)();

extern "C" {
extern const u8 sPatternEditorButtonTileX0[13];
extern const u8 sPatternEditorButtonTileX1[13];
extern const u8 sPatternEditorButtonTileY[13];
extern const u8 sPatternEditorCursorX[36];
extern const u8 sPatternEditorCursorY[36];
extern const u8 sPatternEditorNavUp[36];
extern const u8 sPatternEditorNavRight[36];
extern const u8 sPatternEditorNavDown[36];
extern const u8 sPatternEditorNavLeft[36];
extern const u8 sFillMask[128];
extern const u16 sStampRing[16];
extern const u16 sStampSquare[16];
extern const u16 sStampHeart[16];
extern const u16 sStampStar[16];
extern const u16 sPatternEditorSineTable[322];
extern PatternShapeCornerCell data_ov123_022958c0;
extern ProcProfile sPatternEditorMenuProfile;
}

class PatternEditorMenu : public MenuProc {
public:
    PatternEditorMenu() : paletteLabel(), bgTasks(), cursor(), bottomButtons() {}

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
    void endScreenDim();
    void beginScreenDim();
    void updateStylusStroke();
    void startStylusStroke();
    BOOL cycleColorByShoulder();
    void hideGrid();
    void showGrid();
    void toggleGrid();
    BOOL moveCanvasCursor(s32 unused, s32 flag);
    BOOL moveCursorByPad(u32 pad);
    void moveCursorToTarget();
    void releaseCursor();
    void pressCursor();
    void refreshCursor();
    void hideCursor();
    u32 getCursorTargetY();
    u32 getCursorTargetX();
    void showCursor();
    u8 *getCanvas();
    void toggleUndo();
    void saveUndoState();
    void cancelVramTasks();
    void endShapeAndResume();
    void resetShapeDrag();
    void startShape();
    void drawShapePreview();
    void drawLineEndMarker(s32 x, s32 y);
    void drawCanvasCursor(s32 x, s32 y);
    void drawPreviewDot(s32 x, s32 y);
    void drawShapeCorner(s32 x, s32 y, u32 i);
    void resetPaletteLabel();
    void updateButtonFlash();
    void stopButtonFlash();
    void flashButton(u32 v);
    void selectTool(u32 v);
    void flushButtonScreen();
    void setButtonPalette(u32 a, u32 b);
    void pickColorAtCursor();
    void drawPendingShape();
    void useToolAtCursor();
    void useToolAtTouch();
    void applyToolAt(u8 x, u8 y);
    void drawStamp(s32 x, s32 y, u32 a, u32 idx);
    u32 blendMasked(u32 v, u32 s, u32 t);
    void floodFill(u8 x, u8 y, u32 tgt);
    s32 findSpanEnd(s32 x, s32 y, s32 v);
    s32 findSpanStart(s32 x, s32 y, s32 v);
    s32 findColorInSpan(s32 x0, s32 x1, s32 y, s32 v);
    u8 getPixel(u8 x, u8 y);
    void fillWithMask(u32 c);
    void fillCanvas(s32 v);
    void drawEllipse(s32 x0, s32 y0, s32 x1, u8 y1, u32 c, u32 fill);
    void drawRect(u8 x0, u8 y0, u8 x1, u8 y1, u32 c);
    u32 drawLine(u32 x0, u32 y0, u32 x1, u8 y1, u32 c, s32 t);
    u32 plotBrush(u8 x, u8 y, u32 c, s32 t, s32 z);
    u32 setPixel(u8 x, u8 y, u32 c);
    void setCanvasPosFromTouch();
    s32 canvasToScreenY(s32 i);
    s32 canvasToScreenX(s32 i);
    void activateButton();
    u8 hitTestTouch();
    u8 hitTest(s32 x, s32 y);
    void setPalette(u8 a);
    void setColor(u8 v);
    void requestPaletteUpload();
    void flushCanvasGfx();
    void requestCanvasUpload();
    void loadCanvasChars();
    void buildCanvasChars();
    void requestPreviewUpload();
    void loadPreviewChars();
    void buildPreviewChars();
    void saveToExternalPattern();
    void loadFromExternalPattern();
    void saveToPlayerPattern();
    void loadFromPlayerPattern();
    void startBarTransition(u8 a, u8 b);
    void askQuit();
    void askSave();
    void resumeConfirmInput();
    void startConfirmButtons();
    void startConfirmTouch();
    void resumeInput();
    void startButtonInput();
    void startTouchInput();
    void updateBarTransition();
    void updateCursorRelease();
    void updateCursorPress();
    void updateCursorMove();
    void updateConfirmButtons();
    void updateEyedropper();
    void updateCanvasShape();
    void updateCanvasPaint();
    void updateCanvasCursor();
    void updateButtons();
    void updateTouchStroke();
    void updateConfirmTouch();
    void updateTouch();
    void loadObjGfx();
    void loadBgGfx();
    void setupBgLayers();
    void postStateUpdate();
    void preStateUpdate();
    void postInputUpdate();
    void preInputUpdate();
    void releaseResources();
    void initEditor();
    void applyLayerScroll();
    void updateLayerSlide();
    void stateConfirmBack();
    void stateConfirmClosing();
    void stateConfirmClose();
    void stateConfirm();
    void stateConfirmOpening();
    void stateConfirmOpen();
    void stateClosing();
    void stateClose();
    void stateWaitWear();
    void stateRewear();
    void stateOpening();
    void stateOpen();
    void runMainState();

    /* 0x91 */ u8 unk_91[3];
    /* 0x94 */ u32 slideY;
    /* 0x98 */ s32 confirmScrollY;
    /* 0x9c */ u32 flags;
    /* 0xa0 */ u8 returnState;
    /* 0xa1 */ u8 paletteIndex;
    /* 0xa2 */ u8 color;
    /* 0xa3 */ u8 colorMarkerX;
    /* 0xa4 */ u8 tool;
    /* 0xa5 */ u8 pressedButton;
    /* 0xa6 */ u8 flashButtonId;
    /* 0xa7 */ volatile u8 flashTimer;
    /* 0xa8 */ u8 penX;
    /* 0xa9 */ u8 penY;
    /* 0xaa */ u8 cursorTarget;
    /* 0xab */ u8 savedCursorTarget;
    /* 0xac */ u8 cursorMode;
    /* 0xad */ u8 shapeStartX;
    /* 0xae */ u8 shapeStartY;
    /* 0xaf */ u8 canvasCursorX;
    /* 0xb0 */ u8 canvasCursorY;
    /* 0xb1 */ u8 hoverTimer;
    /* 0xb2 */ u8 hoverButton;
    /* 0xb3 */ u8 moveDelay;
    /* 0xb4 */ u8 lastTouchX;
    /* 0xb5 */ u8 lastTouchY;
    /* 0xb6 */ u8 unk_b6[2];
    /* 0xb8 */ LabelString paletteLabel[1];
    /* 0xf8 */ BgVramTaskPair bgTasks[3];
    /* 0x1a0 */ MenuCursorBuf0 cursor;
    /* 0x204 */ u16 buttonScreen[0x400];
    /* 0xa04 */ u8 canvasA[0x200];
    /* 0xc04 */ u8 canvasB[0x200];
    /* 0xe04 */ u8 zoomedCanvas[0x2e04 - 0xe04];
    /* 0x2e04 */ u8 previewChars[0x200];
    /* 0x3004 */ u8 canvasChars[0x5004 - 0x3004];
    /* 0x5004 */ MenuBottomButtons bottomButtons;
};


static inline BOOL Unk_ov123_022946c4_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        return TRUE;
    }
    return FALSE;
}

static inline BOOL R1(u16 *p, u32 lo, u32 hi)
{
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) {
        r = TRUE;
    }
    return r;
}extern "C" ProcProfile sPatternEditorMenuProfile = {(void *(*)())PatternEditorMenu_Create, 0xa9, 0xad};

extern "C" u32 data_ov123_0229594c[4] = {0x400000f0, 0x000040c0, 0x41f800f8, 0xffff40c2};

extern "C" u32 data_ov123_0229596c[8] = {0x718d0040, 0x0000410e, 0x617e0040, 0x0000410e, 0x518d0030, 0x0000410e, 0x417e0030, 0xffff410e};

extern "C" const u16 sPatternEditorSineTable[322] = {0, 6, 0x000c, 0x0012, 0x0019, 0x001f, 0x0025, 0x002b, 0x0031, 0x0038, 0x003e, 0x0044, 0x004a, 0x0050, 0x0056, 0x005c, 0x0061, 0x0067, 0x006d, 0x0073, 0x0078, 0x007e, 0x0083, 0x0088, 0x008e, 0x0093, 0x0098, 0x009d, 0x00a2, 0x00a7, 0x00ab, 0x00b0, 0x00b5, 0x00b9, 0x00bd, 0x00c1, 0x00c5, 0x00c9, 0x00cd, 0x00d1, 0x00d4, 0x00d8, 0x00db, 0x00de, 0x00e1, 0x00e4, 0x00e7, 0x00ea, 0x00ec, 0x00ee, 0x00f1, 0x00f3, 0x00f4, 0x00f6, 0x00f8, 0x00f9, 0x00fb, 0x00fc, 0x00fd, 0x00fe, 0x00fe, 0x00ff, 0x00ff, 0x00ff, 0x0100, 0x00ff, 0x00ff, 0x00ff, 0x00fe, 0x00fe, 0x00fd, 0x00fc, 0x00fb, 0x00f9, 0x00f8, 0x00f6, 0x00f4, 0x00f3, 0x00f1, 0x00ee, 0x00ec, 0x00ea, 0x00e7, 0x00e4, 0x00e1, 0x00de, 0x00db, 0x00d8, 0x00d4, 0x00d1, 0x00cd, 0x00c9, 0x00c5, 0x00c1, 0x00bd, 0x00b9, 0x00b5, 0x00b0, 0x00ab, 0x00a7, 0x00a2, 0x009d, 0x0098, 0x0093, 0x008e, 0x0088, 0x0083, 0x007e, 0x0078, 0x0073, 0x006d, 0x0067, 0x0061, 0x005c, 0x0056, 0x0050, 0x004a, 0x0044, 0x003e, 0x0038, 0x0031, 0x002b, 0x0025, 0x001f, 0x0019, 0x0012, 0x000c, 6, 0, 0xfffa, 0xfff4, 0xffee, 0xffe7, 0xffe1, 0xffdb, 0xffd5, 0xffcf, 0xffc8, 0xffc2, 0xffbc, 0xffb6, 0xffb0, 0xffaa, 0xffa4, 0xff9f, 0xff99, 0xff93, 0xff8d, 0xff88, 0xff82, 0xff7d, 0xff78, 0xff72, 0xff6d, 0xff68, 0xff63, 0xff5e, 0xff59, 0xff55, 0xff50, 0xff4b, 0xff47, 0xff43, 0xff3f, 0xff3b, 0xff37, 0xff33, 0xff2f, 0xff2c, 0xff28, 0xff25, 0xff22, 0xff1f, 0xff1c, 0xff19, 0xff16, 0xff14, 0xff12, 0xff0f, 0xff0d, 0xff0c, 0xff0a, 0xff08, 0xff07, 0xff05, 0xff04, 0xff03, 0xff02, 0xff02, 0xff01, 0xff01, 0xff01, 0xff00, 0xff01, 0xff01, 0xff01, 0xff02, 0xff02, 0xff03, 0xff04, 0xff05, 0xff07, 0xff08, 0xff0a, 0xff0c, 0xff0d, 0xff0f, 0xff12, 0xff14, 0xff16, 0xff19, 0xff1c, 0xff1f, 0xff22, 0xff25, 0xff28, 0xff2c, 0xff2f, 0xff33, 0xff37, 0xff3b, 0xff3f, 0xff43, 0xff47, 0xff4b, 0xff50, 0xff55, 0xff59, 0xff5e, 0xff63, 0xff68, 0xff6d, 0xff72, 0xff78, 0xff7d, 0xff82, 0xff88, 0xff8d, 0xff93, 0xff99, 0xff9f, 0xffa4, 0xffaa, 0xffb0, 0xffb6, 0xffbc, 0xffc2, 0xffc8, 0xffcf, 0xffd5, 0xffdb, 0xffe1, 0xffe7, 0xffee, 0xfff4, 0xfffa, 0, 6, 0x000c, 0x0012, 0x0019, 0x001f, 0x0025, 0x002b, 0x0031, 0x0038, 0x003e, 0x0044, 0x004a, 0x0050, 0x0056, 0x005c, 0x0061, 0x0067, 0x006d, 0x0073, 0x0078, 0x007e, 0x0083, 0x0088, 0x008e, 0x0093, 0x0098, 0x009d, 0x00a2, 0x00a7, 0x00ab, 0x00b0, 0x00b5, 0x00b9, 0x00bd, 0x00c1, 0x00c5, 0x00c9, 0x00cd, 0x00d1, 0x00d4, 0x00d8, 0x00db, 0x00de, 0x00e1, 0x00e4, 0x00e7, 0x00ea, 0x00ec, 0x00ee, 0x00f1, 0x00f3, 0x00f4, 0x00f6, 0x00f8, 0x00f9, 0x00fb, 0x00fc, 0x00fd, 0x00fe, 0x00fe, 0x00ff, 0x00ff, 0x00ff, 0x003f, 0};

extern "C" const u16 sStampRing[16] = {0, 0, 0, 0x0fc0, 0x1fe0, 0x3870, 0x3030, 0x3030, 0x3030, 0x3030, 0x3870, 0x1fe0, 0x0fc0, 0, 0, 0};

extern "C" const u16 sStampSquare[16] = {0, 0, 0, 0x1ff8, 0x1ff8, 0x1818, 0x1818, 0x1818, 0x1818, 0x1818, 0x1818, 0x1ff8, 0x1ff8, 0, 0, 0};

extern "C" u16 data_ov123_02295840[4] = {0, 0x0010, 8, 0x0018};

extern "C" u32 data_ov123_02295828[2] = {0x818840e0, 0xffff510a};

extern "C" u32 data_ov123_0229591c[4] = {0x81a880b0, 0x000050f9, 0x41a800d0, 0xffff5179};

extern "C" const u8 sPatternEditorNavUp[36] = {0, 0, 1, 2, 3, 4, 6, 6, 7, 8, 9, 0x0a, 0x0c, 0x0d, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x1d, 0x1e, 0, 0, 0, 0, 0};

extern "C" u32 data_ov123_022958b8[2] = {0x41f800f8, 0xffff4102};

extern "C" PatternShapeCornerCell data_ov123_022958c0 = {0xf8, 0x1f8, 0, 1, 0x40ca, 0xffff};

extern "C" const u16 sStampStar[16] = {0, 0, 0, 0x0100, 0x0100, 0x0380, 0x3ff8, 0x0fe0, 0x07c0, 0x07c0, 0x0ee0, 0x0c60, 0x1010, 0, 0, 0};

extern "C" u32 data_ov123_02295a94[36] = {0x60084028, 0x000040f4, 0x400840a0, 0x000040f4, 0x51b88008, 0x00004115, 0x51b880e8, 0x00004115, 0x51b880c8, 0x00004115, 0x51b880a8, 0x00004115, 0x71b84028, 0x000040f5, 0x61d84028, 0x000040f4, 0x61f84028, 0x000040f4, 0x60284028, 0x000040f5, 0x40408008, 0x00004115, 0x404080e8, 0x00004115, 0x51b840a0, 0x000040f5, 0x41d840a0, 0x000040f4, 0x41f840a0, 0x000040f4, 0x404080c8, 0x00004115, 0x404080a8, 0x00004115, 0x402840a0, 0xffff40f5};

extern "C" u32 data_ov123_02295a24[28] = {0x50428008, 0x00004115, 0x70424046, 0x000040f5, 0x50428026, 0x00004115, 0x504280e8, 0x00004115, 0x504280c8, 0x00004115, 0x504280a9, 0x00004115, 0x504240a1, 0x000040f5, 0x40788008, 0x00004115, 0x60604046, 0x000040f5, 0x40788026, 0x00004115, 0x407880e8, 0x00004115, 0x407880c8, 0x00004115, 0x407880a9, 0x00004115, 0x406040a1, 0xffff40f5};

extern "C" u32 data_ov123_02295b24[38] = {0x61984047, 0x000040f4, 0x11808038, 0x00004115, 0x01a88022, 0x00004115, 0x40234031, 0x000040f5, 0x40044031, 0x000040f4, 0x41e44031, 0x000040f4, 0x41c44031, 0x000040f4, 0x41ae4031, 0x000040f4, 0x01a8002e, 0x00004115, 0x01a0401a, 0x000040f7, 0x5180401a, 0x000040f5, 0x61e44047, 0x000040f4, 0x61c44047, 0x000040f4, 0x51808022, 0x00004115, 0x003b8038, 0x00004115, 0x60044047, 0x000040f4, 0x71804047, 0x000040f5, 0x61a44047, 0x000040f4, 0x60234047, 0xffff40f5};

extern "C" u32 data_ov123_02295848[2] = {0x018c0022, 0xffff4129};

extern "C" GXOamAttr *data_ov123_02295900[3] = {(GXOamAttr *)data_ov123_02295a24, (GXOamAttr *)data_ov123_02295b24, (GXOamAttr *)data_ov123_02295a94};

extern "C" const u8 sPatternEditorNavLeft[36] = {0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5, 0x0c, 0x0d, 0x0e, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1e, 0x1e, 0, 0, 0, 0, 0};

extern "C" u32 data_ov123_0229595c[4] = {0x400000f0, 0x000040c0, 0x41f800f8, 0xffff40c6};

extern "C" const u8 sPatternEditorCursorX[36] = {0xd5, 0xd5, 0xd5, 0xd5, 0xd5, 0xd5, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0x23, 0x22, 0x0e, 0x1a, 0x26, 0x32, 0x3e, 0x4a, 0x56, 0x62, 0x6e, 0x7a, 0x86, 0x92, 0x9e, 0xaa, 0xb6, 0xc4, 0x74, 0x62, 0xc2, 0x80, 0, 0};

extern "C" const u8 sPatternEditorCursorY[36] = {0x13, 0x2b, 0x43, 0x63, 0x7b, 0x9b, 0x13, 0x2b, 0x43, 0x63, 0x7b, 0x93, 0x86, 0x0e, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xb6, 0xb6, 0xa9, 0xa9, 0x50, 0, 0};

extern "C" u32 data_ov123_0229590c[4] = {0x018f0022, 0x00004129, 0x01880022, 0xffff4128};

extern "C" u32 data_ov123_02295830[2] = {0x400000f0, 0xffff4110};

extern "C" const u16 sStampHeart[16] = {0, 0, 0, 0, 0x1c70, 0x3ef8, 0x3ff8, 0x3ff8, 0x3ff8, 0x1ff0, 0x0fe0, 0x07c0, 0x0100, 0, 0, 0};

extern "C" const u8 sPatternEditorButtonTileX1[13] = {0x1b, 0x1b, 0x1b, 0x1b, 0x1b, 0x1b, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 4};

extern "C" const u8 sPatternEditorNavRight[36] = {6, 7, 8, 9, 0x0a, 0x0b, 6, 7, 8, 9, 0x0a, 0x0b, 0x0c, 0, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1d, 0x1d, 0, 0, 0, 0, 0};

extern "C" u32 data_ov123_0229593c[4] = {0x400000f0, 0x000040c0, 0x41f800f8, 0xffff40c4};

extern "C" u32 data_ov123_02295858[2] = {0x41f800f8, 0xffff4100};

extern "C" u32 data_ov123_02295850[2] = {0x400000f0, 0xffff40cc};

extern "C" u32 data_ov123_02295800[2] = {0x400000f0, 0xffff40c8};

extern "C" const u8 sFillMask[128] = {0, 0, 0x11, 0x11, 0x11, 0x11, 0, 0, 0, 0, 0x11, 0x11, 0x11, 0x11, 0, 0, 0, 0, 0x10, 0x11, 0x11, 1, 0, 0, 0, 0, 0, 0x11, 0x11, 0, 0, 0, 0x11, 0, 0, 0, 0, 0, 0, 0x11, 0x11, 1, 0, 0, 0, 0, 0x10, 0x11, 0x11, 0x11, 0, 0, 0, 0, 0x11, 0x11, 0x11, 0x11, 0, 0, 0, 0, 0x11, 0x11, 0x11, 0x11, 0, 0, 0, 0, 0x11, 0x11, 0x11, 0x11, 0, 0, 0, 0, 0x11, 0x11, 0x11, 1, 0, 0, 0, 0, 0x10, 0x11, 0x11, 0, 0, 0, 0, 0, 0, 0x11, 0, 0, 0, 0x11, 0x11, 0, 0, 0, 0, 0, 0x10, 0x11, 0x11, 1, 0, 0, 0, 0, 0x11, 0x11, 0x11, 0x11, 0, 0, 0, 0, 0x11, 0x11, 0x11, 0x11, 0, 0};

extern "C" const u8 sPatternEditorButtonTileY[13] = {1, 4, 7, 0x0b, 0x0e, 0x12, 1, 4, 7, 0x0b, 0x0e, 0x11, 0x10};

extern "C" const u8 sPatternEditorButtonTileX0[13] = {0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 1};

extern "C" u16 *sStampBitmaps[4] = {(u16 *)sStampHeart, (u16 *)sStampStar, (u16 *)sStampRing, (u16 *)sStampSquare};

extern "C" const u8 sPatternEditorNavDown[36] = {1, 2, 3, 4, 5, 0x1d, 7, 8, 9, 0x0a, 0x0b, 0x1d, 0x0e, 0x0c, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1d, 0x1e, 0, 0, 0, 0, 0};

extern "C" PatternEditorMenu *PatternEditorMenu_Create() { return new PatternEditorMenu(); }

BOOL PatternEditorMenu::onCreate() {
    initEditor();
    transitionState = 0;
    setPhase(0);
    return TRUE;
}

BOOL PatternEditorMenu::onDelete() {
    ((MenuLauncher *)ProcBase_GetParent(this))->onChildClosed();
    releaseResources();
    return TRUE;
}

BOOL PatternEditorMenu::onDraw() {
    if (MenuCtrl_IsButtons()) {
        if (cursorMode == 2) {
            if (!testFlags(0x100)) {
                drawCanvasCursor(canvasCursorX, canvasCursorY);
            }
        } else {
            cursor.drawWrapped();
        }
    }
    if (testFlags(0x100)) {
        drawShapePreview();
    }
    bottomButtons.drawAt(getSlideOffsetY());
    if (testFlags(1)) {
        s32 y = confirmScrollY + (slideY + 0x60);
        if (MenuCtrl_IsButtons()) {
            Oam_DrawObj(1, data_ov123_02295828, 0x80, y, -1, -1, 0);
            Oam_DrawCell(1, (GXOamAttr *)data_ov123_0229591c, 0x80, y, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        }
        Oam_DrawCell(1, (GXOamAttr *)data_ov123_0229596c, colorMarkerX + 0x80, y, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        if (paletteIndex < 9) {
            Oam_DrawCell(1, (GXOamAttr *)data_ov123_02295848, 0x80, y, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        } else {
            Oam_DrawCell(1, (GXOamAttr *)data_ov123_0229590c, 0x80, y, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        }
        if (MenuCtrl_IsButtons()) {
            Oam_DrawCell(1, data_ov123_02295900[cursorMode], 0x80, y, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        }
    }
    return TRUE;
}

BOOL PatternEditorMenu::execTransition() {
    static Unk_ov123_022959c4_Fn tbl[12] = {
        &PatternEditorMenu::stateOpen,
        &PatternEditorMenu::stateOpening,
        &PatternEditorMenu::stateRewear,
        &PatternEditorMenu::stateWaitWear,
        &PatternEditorMenu::stateClose,
        &PatternEditorMenu::stateClosing,
        &PatternEditorMenu::stateConfirmOpen,
        &PatternEditorMenu::stateConfirmOpening,
        &PatternEditorMenu::stateConfirm,
        &PatternEditorMenu::stateConfirmClose,
        &PatternEditorMenu::stateConfirmClosing,
        &PatternEditorMenu::stateConfirmBack};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}extern "C" u32 data_ov123_022958a8[2] = {0x01fc00fc, 0xffff4108};

void PatternEditorMenu::runMainState() {
    static Unk_ov123_022959c4_Fn tbl[13] = {
        &PatternEditorMenu::updateTouch,
        &PatternEditorMenu::updateConfirmTouch,
        &PatternEditorMenu::updateTouchStroke,
        &PatternEditorMenu::updateButtons,
        &PatternEditorMenu::updateCanvasCursor,
        &PatternEditorMenu::updateCanvasPaint,
        &PatternEditorMenu::updateCanvasShape,
        &PatternEditorMenu::updateEyedropper,
        &PatternEditorMenu::updateConfirmButtons,
        &PatternEditorMenu::updateCursorMove,
        &PatternEditorMenu::updateCursorPress,
        &PatternEditorMenu::updateCursorRelease,
        &PatternEditorMenu::updateBarTransition};
    (this->*tbl[mainState])();
}

BOOL PatternEditorMenu::execMain() {
    preInputUpdate();
    runMainState();
    postInputUpdate();
    return TRUE;
}

BOOL PatternEditorMenu::execPhase3() { return TRUE; }

BOOL PatternEditorMenu::execPhase4() { return TRUE; }

BOOL PatternEditorMenu::execClosed() {
    ProcBase_RequestDelete(this);
    return TRUE;
}

void PatternEditorMenu::stateOpen() {
    setupBgLayers();
    loadBgGfx();
    tool = 0x22;
    selectTool(0);
    loadObjGfx();
    switch (MenuCtrl_GetMode()) {
    case 2:
        loadFromPlayerPattern();
        break;
    case 3:
        loadFromExternalPattern();
        break;
    }
    buildPreviewChars();
    buildCanvasChars();
    loadPreviewChars();
    loadCanvasChars();
    bottomButtons.setLayoutNeverMindConfirm();
    beginSubSlideIn(0xb, 4, 0, 0x30);
    Gfx2d_ShowLayer(6);
    Gfx2d_ShowLayer(4);
    showGrid();
    updateLayerSlide();
    setFlags(1);
    setTransitionState(1);
}

void PatternEditorMenu::stateOpening() {
    if (stepSlideIn(0)) {
        setPhase(2);
        resumeInput();
    }
    updateLayerSlide();
}

void PatternEditorMenu::stateRewear() {
    if (!testFlags(0x8000) && !testFlags(0x10000)) {
        setTransitionState(4);
        stateClose();
        return;
    }
    PlayerData *p = PlayerData_GetCurrent();
    if (testFlags(0x8000)) {
        if (!PlayerActor_RequestWearShirtAlt(p->getShirt())) return;
        clearFlags(0x8000);
    }
    if (testFlags(0x10000)) {
        if (!PlayerActor_RequestWearHatAlt(p->getHat())) return;
        clearFlags(0x8000);
    }
    setTransitionState(3);
}

void PatternEditorMenu::stateWaitWear() {
    if (PlayerActor_IsChangingClothes() == 0) {
        setTransitionState(4);
    }
}

void PatternEditorMenu::stateClose() {
    endScreenDim();
    ((MenuLauncher *)ProcBase_GetParent(this))->setNextRequest(0x44, 1);
    beginSubSlideOut(0xb, 0, 0, 0x30);
    updateLayerSlide();
    setTransitionState(5);
}

void PatternEditorMenu::stateClosing() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(6);
        Gfx2d_ResetLayer(4);
        Gfx2d_ResetLayer(3);
        setPhase(5);
        Gfx2d_ResetSubBlend();
        clearFlags(1);
        bottomButtons.hide();
    } else {
        updateLayerSlide();
    }
}

void PatternEditorMenu::stateConfirmOpen() {
    initSlideOut(0, 0);
    setTransitionState(7);
    confirmScrollY = 0;
    setFlags(0x400);
}

void PatternEditorMenu::stateConfirmOpening() {
    if (stepSlideOut(-1)) {
        initSlideIn(0, 0);
        if (testFlags(8)) {
            ((MenuBottomButtonsBody *)&bottomButtons)->setLayoutYesNo07(0x87);
        } else {
            ((MenuBottomButtonsBody *)&bottomButtons)->setLayoutYesNo07(0x22);
        }
        setTransitionState(8);
    }
    if (testFlags(0x400)) {
        if (confirmScrollY < 0x10) {
            confirmScrollY = confirmScrollY + 2;
        } else {
            beginScreenDim();
            confirmScrollY = 0x10;
            clearFlags(0x400);
        }
    }
    applyLayerScroll();
}

void PatternEditorMenu::stateConfirm() {
    if (stepSlideIn(-1)) {
        setPhase(2);
        resumeConfirmInput();
        if (testFlags(0x400)) {
            beginScreenDim();
            confirmScrollY = 0x10;
            clearFlags(0x400);
        }
    } else if (testFlags(0x400)) {
        if (confirmScrollY < 0x10) {
            confirmScrollY = confirmScrollY + 2;
        } else {
            beginScreenDim();
            confirmScrollY = 0x10;
            clearFlags(0x400);
        }
    }
    applyLayerScroll();
}

void PatternEditorMenu::stateConfirmClose() {
    endScreenDim();
    if (testFlags(0x20000)) {
        clearFlags(0x20000);
        showGrid();
    }
    initSlideOut(0, 0);
    setTransitionState(0xa);
    confirmScrollY = 0x10;
}

void PatternEditorMenu::stateConfirmClosing() {
    if (stepSlideOut(-1)) {
        initSlideIn(0, 0);
        bottomButtons.setLayoutNeverMindConfirm();
        setTransitionState(0xb);
    }
    if (confirmScrollY >= 2) {
        confirmScrollY = confirmScrollY - 2;
    } else {
        confirmScrollY = 0;
    }
    applyLayerScroll();
}

void PatternEditorMenu::stateConfirmBack() {
    if (stepSlideIn(-1)) {
        setPhase(2);
        resumeInput();
        confirmScrollY = 0;
    } else if (confirmScrollY >= 2) {
        confirmScrollY = confirmScrollY - 2;
    } else {
        confirmScrollY = 0;
    }
    applyLayerScroll();
}

void PatternEditorMenu::updateLayerSlide() {
    applySlideOffset(6, 0, confirmScrollY);
    applySlideOffset(4, 0, confirmScrollY);
    applySlideOffset(3, 0, confirmScrollY);
    slideY = getSlideOffsetY();
}

void PatternEditorMenu::applyLayerScroll() {
    Gfx2d_SetLayerOffset(6, 0, -confirmScrollY);
    Gfx2d_SetLayerOffset(4, 0, -confirmScrollY);
    Gfx2d_SetLayerOffset(3, 0, -confirmScrollY);
}

void PatternEditorMenu::initEditor() {
    setColor(1);
    flags = 0;
    flashButtonId = 0x22;
    stopButtonFlash();
    cursorTarget = 0;
    savedCursorTarget = 0;
    cursorMode = 0;
    resetShapeDrag();
    canvasCursorX = 0x10;
    canvasCursorY = 0x10;
    MenuCtrl_SetResult(0);
    PlayerActor_RequestAct05();
    confirmScrollY = 0;
    moveDelay = 0;
}

void PatternEditorMenu::releaseResources() {
    bottomButtons.freeTexts();
    resetPaletteLabel();
    cancelVramTasks();
    PlayerActor_RequestAct10();
    if (MenuCtrl_GetMode() == 3) {
        Snd_SetSceneBankVariant(0);
    }
}

void PatternEditorMenu::preInputUpdate() {
    preStateUpdate();
    MenuCursorBuf0 *p = &cursor;
    p->update();
}

void PatternEditorMenu::postInputUpdate() {
    postStateUpdate();
}

void PatternEditorMenu::preStateUpdate() {
    bottomButtons.freeTexts();
    resetPaletteLabel();
    updateButtonFlash();
}

void PatternEditorMenu::postStateUpdate() {
    flushCanvasGfx();
    flushButtonScreen();
}

void PatternEditorMenu::setupBgLayers() {
    Gfx2d_SetSubBgModeState(0);
    Gfx2d_SetLayerPriority(6, 2);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
    Gfx2d_SetLayerPriority(4, 2);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
    Gfx2d_SetLayerPriority(3, 2);
    Gfx2d_SetLayerControl(3, 0, 0, 0);
}

void PatternEditorMenu::loadBgGfx() {
    Heap *p = gCurrentHeap;
    Gfx2d_LoadPaletteFile("menu/edit/bg.bpl", p, 6, 4, 4, 0xe);
    File_LoadToBuffer("menu/edit/a.bsc", buttonScreen, 0x800);
    Gfx2d_LoadScreen((u8 *)buttonScreen, 6, 0x800, 0);
    Gfx2d_LoadScreenFile("menu/edit/b.bsc", p, 4);
    Gfx2d_LoadScreenFile("menu/edit/c.bsc", p, 3);
    Gfx2d_LoadCharFile("menu/edit/bg1.bch", p, 6, 0x120, 0x120, 0x1ff);
    Gfx2d_LoadCharFile("menu/edit/bg0.bch", p, 6, 0x10, 0x10, 0x1f);
}

void PatternEditorMenu::loadObjGfx() {
    Heap *p = gCurrentHeap;
    Gfx2d_LoadPaletteFile("menu/edit/obj.bpl", p, 8, 4, 4, 0xc);
    Gfx2d_LoadCharFile("menu/edit/obj0.bch", p, 8, 0xc0, 0xc0, 0x12f);
    Gfx2d_LoadCharFile("menu/edit/obj1.bch", p, 8, 0x130, 0x130, 0x19f);
}

void PatternEditorMenu::updateTouch() {
    if (checkSwitchToButtons(1)) {
        startButtonInput();
    } else if (Unk_ov123_022946c4_Both()) {
        u32 r = hitTestTouch();
        if (r == 0x21) {
            useToolAtTouch();
        } else if (r != 0x22) {
            pressedButton = r;
            activateButton();
        }
    }
}

void PatternEditorMenu::updateConfirmTouch() {
    if (checkSwitchToButtons(1)) {
        startConfirmButtons();
    } else if (Unk_ov123_022946c4_Both()) {
        if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(3)) {
            pressedButton = 0x1f;
            activateButton();
        } else if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(4)) {
            pressedButton = 0x20;
            activateButton();
        }
    }
}

void PatternEditorMenu::updateTouchStroke() {
    if (gTouchHeld == 0) {
        if (testFlags(0x80000)) {
            clearFlags(0x80000);
            Snd_StopSe(0x862, 1);
        }
        endShapeAndResume();
    } else {
        clearFlags(0x100000);
        updateStylusStroke();
        lastTouchX = gTouchCurX;
        lastTouchY = gTouchCurY;
        if (testFlags(0x100000)) {
            if (!testFlags(0x80000)) {
                setFlags(0x80000);
                Snd_PlaySeOnHandle(0x862);
            }
        } else if (testFlags(0x80000)) {
            clearFlags(0x80000);
            Snd_StopSe(0x862, 1);
        }
    }
}

void PatternEditorMenu::updateButtons() {
    if (checkSwitchToTouch()) {
        startTouchInput();
    } else {
        if (moveCursorByPad(takeRepeatedKeys())) {
            if (cursorMode == 0) {
                savedCursorTarget = cursorTarget;
            }
            moveCursorToTarget();
        } else {
            u32 t = gPad[1];
            if (t & 1) {
                pressCursor();
            } else if (t & 0x800) {
                Snd_PlaySe(0x864);
                if (cursorMode == 0) {
                    cursorMode = 1;
                    cursorTarget = color + 0xd;
                } else {
                    cursorMode = 2;
                }
                resumeInput();
            } else if (!cycleColorByShoulder()) {
                u32 k = gPad[1];
                if (k & 0x400) {
                    toggleGrid();
                } else if (k & 2) {
                    hideCursor();
                    askQuit();
                } else if (k & 8) {
                    hideCursor();
                    askSave();
                }
            }
        }
    }
}

void PatternEditorMenu::updateCanvasCursor() {
    if (checkSwitchToTouch()) {
        startTouchInput();
    } else {
        moveCanvasCursor(takeRepeatedKeys(), 0);
        u32 t = gPad[1];
        if (t & 1) {
            useToolAtCursor();
        } else if (t & 2) {
            setFlags(0x800);
            pickColorAtCursor();
            setMainState(7);
        } else if (t & 0x800) {
            Snd_PlaySe(0x864);
            cursorMode = 0;
            cursorTarget = savedCursorTarget;
            resumeInput();
        } else if (!cycleColorByShoulder()) {
            u32 k = gPad[1];
            if (k & 0x400) {
                toggleGrid();
            } else if (k & 8) {
                hideCursor();
                askSave();
            }
        }
    }
}

void PatternEditorMenu::updateCanvasPaint()
{
    if ((gPad[0] & 1) == 0) {
        resumeInput();
        if (testFlags(0x40000)) {
            clearFlags(0x40000);
            Snd_StopSe(0x863, 1);
        }
    } else {
        s32 r = takeRepeatedKeys();
        s32 flag = 0;
        if (moveCanvasCursor(r, 1)) {
            plotBrush(canvasCursorX, canvasCursorY, color, tool, 1);
            setFlags(0x40);
            Snd_PlaySe(0x861);
            if (moveDelay == 0) {
                flag = 1;
            } else {
                Snd_PlaySe(0x860);
            }
        }
        if (flag) {
            if (testFlags(0x40000) == 0) {
                setFlags(0x40000);
                Snd_PlaySeOnHandle(0x863);
            }
        } else {
            if (testFlags(0x40000)) {
                clearFlags(0x40000);
                Snd_StopSe(0x863, 1);
            }
        }
    }
}

void PatternEditorMenu::updateCanvasShape()
{
    if (checkSwitchToTouch()) {
        Snd_PlaySe(0x86e);
        resetShapeDrag();
        startTouchInput();
        return;
    }
    s32 r = takeRepeatedKeys();
    if (moveCanvasCursor(r, 0)) {
        penX = canvasCursorX;
        penY = canvasCursorY;
        return;
    }
    u32 k = gPad[1];
    if (k & 1) {
        endShapeAndResume();
    } else if (k & 2) {
        Snd_PlaySe(0x86e);
        resetShapeDrag();
        resumeInput();
    } else if (k & 0x800) {
        Snd_PlaySe(0x864);
        resetShapeDrag();
        cursorMode = 0;
        resumeInput();
    } else if (k & 0x400) {
        toggleGrid();
    }
}

void PatternEditorMenu::updateEyedropper()
{
    if ((gPad[0] & 2) == 0) {
        clearFlags(0x800);
        resumeInput();
        Snd_PlaySe(0x86d);
    } else {
        s32 r = takeRepeatedKeys();
        if (moveCanvasCursor(r, 0)) {
            pickColorAtCursor();
        }
    }
}

void PatternEditorMenu::updateConfirmButtons()
{
    if (checkSwitchToTouch()) {
        startConfirmTouch();
        return;
    }
    u32 old = cursorTarget;
    takeRepeatedKeys();
    if (isRepeatLeft()) {
        cursorTarget = 0x1f;
    } else if (isRepeatRight()) {
        cursorTarget = 0x20;
    }
    if (old != cursorTarget) {
        moveCursorToTarget();
        return;
    }
    u32 k = gPad[1];
    if (k & 1) {
        pressCursor();
    } else if (k & 2) {
        hideCursor();
        pressedButton = 0x20;
        activateButton();
    } else if (k & 8) {
        hideCursor();
        pressedButton = 0x1f;
        activateButton();
    }
}

void PatternEditorMenu::updateCursorMove()
{
    if (cursor.isMoving() == 0) {
        setMainState(returnState);
        runMainState();
    }
}

void PatternEditorMenu::updateCursorPress()
{
    if (cursor.isAnimDone()) {
        pressedButton = cursorTarget;
        activateButton();
        if (mainState == 0xa) {
            releaseCursor();
        }
    }
}

void PatternEditorMenu::updateCursorRelease()
{
    if (cursor.isAnimDone()) {
        refreshCursor();
        setMainState(3);
    }
}

void PatternEditorMenu::updateBarTransition()
{
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

void PatternEditorMenu::startTouchInput()
{
    setMainState(0);
    hideCursor();
}

void PatternEditorMenu::startButtonInput()
{
    if (cursorMode == 2) {
        hideCursor();
        initKeyRepeat(5, 0, 5);
        setMainState(4);
        Snd_SetPanIfChanged((u8)canvasToScreenX(canvasCursorX));
    } else {
        showCursor();
        restartKeyRepeat();
        setMainState(3);
    }
}

void PatternEditorMenu::resumeInput()
{
    if (MenuCtrl_IsTouch()) {
        startTouchInput();
    } else {
        startButtonInput();
    }
}

void PatternEditorMenu::startConfirmTouch()
{
    hideCursor();
    setMainState(1);
}

void PatternEditorMenu::startConfirmButtons()
{
    restartKeyRepeat();
    cursorTarget = 0x20;
    showCursor();
    setMainState(8);
}

void PatternEditorMenu::resumeConfirmInput()
{
    if (MenuCtrl_IsTouch()) {
        startConfirmTouch();
    } else {
        startConfirmButtons();
    }
}

void PatternEditorMenu::askSave()
{
    Snd_PlaySe(0x29);
    clearFlags(8);
    if (cursorMode == 2) {
        cursorMode = 0;
    }
    startBarTransition(6, 9);
}

void PatternEditorMenu::askQuit()
{
    Snd_PlaySe(0x2a);
    setFlags(8);
    if (cursorMode == 2) {
        cursorMode = 0;
    }
    startBarTransition(6, 8);
}

void PatternEditorMenu::startBarTransition(u8 a, u8 b)
{
    setTransitionState(a);
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(b);
    setMainState(0xc);
}

void PatternEditorMenu::loadFromPlayerPattern()
{
    PlayerPatterns *b = (PlayerPatterns *)PlayerData_GetCurrent()->getPatterns();
    Pattern *d = b->getPatternByOrder(MenuCtrl_GetIndex());
    MIi_CpuCopy32(d->getPixels(), canvasA, 0x200);
    MIi_CpuCopy32(d->getPixels(), canvasB, 0x200);
    u8 r = d->getInfo()->getPalette();
    setPalette(r);
}

void PatternEditorMenu::saveToPlayerPattern()
{
    PlayerData *a = PlayerData_GetCurrent();
    PlayerPatterns *b = (PlayerPatterns *)a->getPatterns();
    u32 c = MenuCtrl_GetIndex();
    Pattern *d = b->getPatternByOrder(c);
    d->setPixels(getCanvas());
    d->getInfo()->setAuthorToCurrentPlayer();
    d->getInfo()->setPalette(paletteIndex);
    s32 e = b->getPatternOrder()->getSlot(c);
    u16 *p = a->getShirt();
    s32 r;
    if (R1(p, 0x12a8, 0x12af)) {
        r = *p - 0x12a8;
    } else {
        r = -1;
    }
    if (r != -1 && r == e) {
        setFlags(0x8000);
    }
    p = a->getHat();
    if (R1(p, 0x1429, 0x1430)) {
        r = *p - 0x1429;
    } else {
        r = -1;
    }
    if (r != -1 && r == e) {
        setFlags(0x10000);
    }
}

void PatternEditorMenu::loadFromExternalPattern()
{
    Pattern *o = (Pattern *)((BlancaFaceRecord *)(&gSaveBlancaFace))->getPattern();
    MIi_CpuCopy32(o->getPixels(), canvasA, 0x200);
    MIi_CpuCopy32(o->getPixels(), canvasB, 0x200);
    u8 r = o->getInfo()->getPalette();
    setPalette(r);
}

void PatternEditorMenu::saveToExternalPattern()
{
    Pattern *o = (Pattern *)((BlancaFaceRecord *)(&gSaveBlancaFace))->getPattern();
    o->setPixels(getCanvas());
    o->getInfo()->setAuthorToCurrentPlayer();
    o->getInfo()->setPalette(paletteIndex);
}

void PatternEditorMenu::buildPreviewChars()
{
    Gfx2d_LinearToTiles4bpp((u32 *)getCanvas(), (u32 *)previewChars, 4, 4);
}

void PatternEditorMenu::loadPreviewChars()
{
    Gfx2d_LoadCharRange(previewChars, 6, 0x120, 0x120, 0x12f);
}

void PatternEditorMenu::requestPreviewUpload()
{
    ((BgVramTask *)(bgTasks))->requestChars(previewChars, 6, 0x120, 0x120, 0x12f);
}

void PatternEditorMenu::buildCanvasChars()
{
    u32 sh, lo, v;
    u32 *src = (u32 *)getCanvas();
    u32 *dst = (u32 *)zoomedCanvas;
    s32 j, i, k, m;
    i = 0;
Li:
    {
        u32 *d2 = dst;
        for (j = 0; j < 4; j++) {
            sh = 0;
            u32 *d3 = d2;
            for (k = 0; k < 4; k++) {
                u32 w = *src;
                lo = (u8)((w >> sh) & 0xf);
                u32 hi = (u8)((w >> (sh + 4)) & 0xf);
                sh += 8;
                v = lo | ((lo << 4) | ((lo << 8) | ((lo << 12) | ((hi << 16) | ((hi << 20) | ((hi << 28) | (hi << 24)))))));
                u32 *p = d3;
                for (m = 0; m < 4; m++) {
                    *p = v;
                    p += 0x10;
                }
                d3++;
            }
            src++;
            d2 += 4;
        }
        dst += 0x40;
    }
    i++;
    if (i < 0x20) goto Li;
    Gfx2d_LinearToTiles4bpp((u32 *)zoomedCanvas, (u32 *)canvasChars, 0x10, 0x10);
}

void PatternEditorMenu::loadCanvasChars()
{
    Gfx2d_LoadCharRange(canvasChars, 6, 0x20, 0x20, 0x11f);
}

void PatternEditorMenu::requestCanvasUpload()
{
    ((BgVramTask *)(&bgTasks[1]))->requestChars(canvasChars, 6, 0x20, 0x20, 0x11f);
}

void PatternEditorMenu::flushCanvasGfx()
{
    if (testFlags(0x40)) {
        buildPreviewChars();
        buildCanvasChars();
        requestPreviewUpload();
        requestCanvasUpload();
        clearFlags(0x40);
    }
}

void PatternEditorMenu::requestPaletteUpload()
{
    PatternTexCache *a = PatternTexCache_Get();
    u8 *b = a->getPalette(paletteIndex);
    ((BgVramTask *)(bgTasks))->requestPalette(b, 6, 0xe);
}

void PatternEditorMenu::setColor(u8 v)
{
    color = v;
    colorMarkerX = (v - 1) * 12;
}

void PatternEditorMenu::setPalette(u8 a) {
    u8 buf[5];
    paletteIndex = a;
    requestPaletteUpload();
    if (a < 9) {
        buf[0] = 0x85;
    } else {
        buf[0] = 0x36;
    }
    buf[1] = (a + 1) % 10 + 0x35;
    buf[2] = 0;
    String_FromEncodedBytes(paletteLabel, buf, 5);
    paletteLabel[0].createSmallLabel(8, 0x128, 2, 6, 0, 1);
    paletteLabel[0].redrawAligned(0, 0);
}

u8 PatternEditorMenu::hitTest(s32 x, s32 y) {
    if (((MenuBottomButtonsBody *)&bottomButtons)->hitTest(9, x, y)) {
        return 0x1d;
    }
    if (((MenuBottomButtonsBody *)&bottomButtons)->hitTest(8, x, y)) {
        return 0x1e;
    }
    if (x >= 0x8 && x <= 0x28 && y >= 0x18 && y <= 0x38) {
        return 0xd;
    }
    if (x >= 0x40 && x < 0xc0 && y >= 0x8 && y < 0x88) {
        return 0x21;
    }
    if (x >= 0xca && y >= 0x8) {
        if (x < 0xe1) {
            if (y < 0x50) {
                if (y < 0x20) {
                    return 0;
                }
                if (y < 0x38) {
                    return 1;
                }
                return 2;
            }
            if (y >= 0x58 && y < 0x88) {
                if (y < 0x70) {
                    return 3;
                }
                return 4;
            }
            if (y >= 0x90 && y < 0xa8) {
                return 5;
            }
        } else if (x < 0xf9) {
            if (y < 0x50) {
                if (y < 0x20) {
                    return 6;
                }
                if (y < 0x38) {
                    return 7;
                }
                return 8;
            }
            if (y >= 0x58 && y < 0xa0) {
                if (y < 0x70) {
                    return 9;
                }
                if (y < 0x88) {
                    return 10;
                }
                return 11;
            }
        }
    }
    if (x >= 0x8 && x <= 0x28 && y >= 0x80 && y <= 0x94) {
        return 12;
    }
    if (x >= 0x8 && x < 0xbc && y >= 0x94 && y <= 0xa4) {
        return (u8)((x - 8) / 12 + 14);
    }
    return 0x22;
}

u8 PatternEditorMenu::hitTestTouch() { return hitTest(gTouchCurX, gTouchCurY); }

void PatternEditorMenu::activateButton() {
    u32 s = pressedButton;
    if (s == 0x1d) {
        askSave();
    } else if (s == 0x1e) {
        askQuit();
    } else if (s <= 0xb && s != 5) {
        selectTool(s);
    } else if (s == 0xc) {
        flashButton(s);
        setPalette((paletteIndex + 1) & 0xf);
        Snd_PlaySe(0x868);
    } else if (s == 5) {
        flashButton(s);
        toggleUndo();
    } else if (s >= 0xe && s <= 0x1c) {
        setColor(s - 0xd);
        Snd_PlaySe(0x86a);
    } else {
        if (s == 0xd) {
            toggleGrid();
        }
        u32 t = pressedButton;
        if (t == 0x1f) {
            startBarTransition(2, 3);
            if (testFlags(8)) {
                MenuCtrl_SetResult(0);
                Snd_PlaySe(0x28);
            } else {
                switch (MenuCtrl_GetMode()) {
                case 2:
                    saveToPlayerPattern();
                    break;
                case 3:
                    saveToExternalPattern();
                    break;
                }
                MenuCtrl_SetResult(1);
                Snd_PlaySe(0x27);
            }
        } else if (t == 0x20) {
            startBarTransition(9, 4);
            if (testFlags(8)) {
                cursorTarget = 0x1e;
                Snd_PlaySe(0x29);
            } else {
                cursorTarget = 0x1d;
                Snd_PlaySe(0x2a);
            }
        }
    }
}

s32 PatternEditorMenu::canvasToScreenX(s32 i) { return i * 4 + 0x42; }

s32 PatternEditorMenu::canvasToScreenY(s32 i) { return i * 4 + 10; }

void PatternEditorMenu::setCanvasPosFromTouch() {
    s32 x = gTouchCurX;
    s32 y = gTouchCurY + 16;
    if (tool == 1) {
        x += 2;
        y += 2;
    }
    x -= 0x40;
    if (x < 0) {
        x = 0;
    } else if (x > 0x7f) {
        x = 0x7f;
    }
    y -= 0x18;
    if (y < 0) {
        y = 0;
    } else if (y > 0x7f) {
        y = 0x7f;
    }
    penX = x >> 2;
    penY = y >> 2;
}

u32 PatternEditorMenu::setPixel(u8 x, u8 y, u32 c) {
    if (x >= 32 || y >= 32) {
        return 0;
    }
    u32 *g = (u32 *)getCanvas();
    u32 sh = (x & 7) << 2;
    u32 *row = g;
    row += y * 4;
    u32 *p = &row[x >> 3];
    u32 mask = 0xf << sh;
    u32 w = row[x >> 3];
    u32 cur = (u8)(((w & mask) >> sh) & 0xf);
    if (cur == c) {
        return 0;
    }
    *p = w & ~mask;
    *p = *p | (c << sh);
    return 1;
}

u32 PatternEditorMenu::plotBrush(u8 x, u8 y, u32 c, s32 t, s32 z) {
    u32 r = 0;
    if (t < 0 || t > 3) {
        return 0;
    }
    switch (t) {
    case 0:
        r |= setPixel(x, y, c);
        break;
    case 1: {
        r |= setPixel(x, y, c);
        s32 xm = x - 1;
        r |= setPixel(xm, y, c);
        s32 ym = y - 1;
        r |= setPixel(x, ym, c);
        r |= setPixel(xm, ym, c);
        break;
    }
    case 2: {
        s32 ym = y - 1;
        s32 xm = x - 1;
        r |= setPixel(xm, ym, c);
        r |= setPixel(x, ym, c);
        s32 xp = x + 1;
        r |= setPixel(xp, ym, c);
        r |= setPixel(xm, y, c);
        r |= setPixel(x, y, c);
        r |= setPixel(xp, y, c);
        s32 yp = y + 1;
        r |= setPixel(xm, yp, c);
        r |= setPixel(x, yp, c);
        r |= setPixel(xp, yp, c);
        break;
    }
    case 3:
        drawPreviewDot(x, y);
        break;
    }
    return r;
}

u32 PatternEditorMenu::drawLine(u32 x0, u32 y0, u32 x1, u8 y1, u32 c, s32 t) {
    u32 dx, dy;
    s32 err1;
    s32 sx, sy;
    s32 i1;
    u32 r;
    s32 dx2b;
    s32 dy2b;
    s32 dy2;
    s32 dx2;
    s32 err2;
    s32 i2;
    s32 z1, z2;
    r = 0;
    if (x1 > x0) {
        sx = 1;
        dx = x1 - x0;
    } else {
        sx = -1;
        dx = x0 - x1;
    }
    if (y1 > y0) {
        sy = 1;
        dy = y1 - y0;
    } else {
        sy = -1;
        dy = y0 - y1;
    }
    if ((s32)dx >= (s32)dy) {
        err1 = -(s32)dx;
        i1 = 0;
        z1 = i1;
        dy2 = dy << 1;
        dx2 = dx << 1;
        for (; i1 <= (s32)dx; i1++) {
            r |= plotBrush(x0, y0, c, t, z1);
            x0 += sx;
            err1 += dy2;
            if (err1 >= 0) {
                y0 += sy;
                err1 -= dx2;
            }
        }
    } else {
        err2 = -(s32)dy;
        i2 = 0;
        z2 = i2;
        dx2b = dx << 1;
        dy2b = dy << 1;
        for (; i2 <= (s32)dy; i2++) {
            r |= plotBrush(x0, y0, c, t, z2);
            y0 += sy;
            err2 += dx2b;
            if (err2 >= 0) {
                x0 += sx;
                err2 -= dy2b;
            }
        }
    }
    return r;
}

void PatternEditorMenu::drawRect(u8 x0, u8 y0, u8 x1, u8 y1, u32 c) {
    u8 x;
    for (x = x0; x <= x1; x++) {
        setPixel(x, y0, c);
        setPixel(x, y1, c);
    }
    u8 y;
    for (y = y0; y <= y1; y++) {
        setPixel(x0, y, c);
        setPixel(x1, y, c);
    }
}

void PatternEditorMenu::drawEllipse(s32 x0, s32 y0, s32 x1, u8 y1, u32 c, u32 fill) {
    s32 w;
    s32 cx;
    s16 i;
    s32 cy;
    s32 hw;
    s32 hh;
    s32 d;
    s32 a;
    s32 b;
    s32 step;
    s32 df;
    s32 sum;
    w = x1 - x0;
    d = y1 - y0;
    hw = w >> 1;
    hh = d >> 1;
    cx = x0 + hw;
    cy = y0 + hh;
    df = hw - hh;
    if (df < 0) {
        df = -df;
    }
    sum = hw + hh;
    step = DS_DIV(0x40, (s16)(sum - ((sum >> 1) - (sum >> 3) - (df >> 1) - 5) | 1));
    d &= 1;
    w &= 1;
    for (i = 0; i < 0x40; i = i + step) {
        a = (((u16 *)sPatternEditorSineTable)[i + 0x40] * hw + 0x2d) >> 8;
        b = (((u16 *)sPatternEditorSineTable)[i] * hh + 0x2d) >> 8;
        if (fill) {
            s32 x = cx - a;
            s32 ya = cy - b;
            s32 yb = cy + b + d;
            s32 xe = cx + a + w;
            for (; x <= xe; x++) {
                setPixel(x, ya, c);
                setPixel(x, yb, c);
            }
        } else {
            s32 yb, xl, xr, yt;
            xr = cx + a + w;
            yb = cy + b + d;
            setPixel(xr, yb, c);
            yt = cy - b;
            setPixel(xr, yt, c);
            xl = cx - a;
            setPixel(xl, yb, c);
            setPixel(xl, yt, c);
        }
    }
}

void PatternEditorMenu::fillCanvas(s32 v) {
    u32 *p = (u32 *)getCanvas();
    u32 t = v * 0x11111111;
    s32 i;
    for (i = 0; i < 32; i++) {
        p[0] = t;
        p[1] = t;
        p[2] = t;
        p[3] = t;
        p += 4;
    }
}

void PatternEditorMenu::fillWithMask(u32 c) {
    u32 *p = (u32 *)getCanvas();
    s32 j, i;
    for (j = 0; j < 2; j++) {
        u32 *t = (u32 *)sFillMask;
        for (i = 0; i < 16; i++) {
            p[0] = blendMasked(p[0], t[0], c);
            p[1] = blendMasked(p[1], t[1], c);
            p[2] = blendMasked(p[2], t[0], c);
            p[3] = blendMasked(p[3], t[1], c);
            p += 4;
            t += 2;
        }
    }
}

u8 PatternEditorMenu::getPixel(u8 x, u8 y) {
    if (x >= 32 || y >= 32) {
        return 1;
    }
    u8 *row = (u8 *)getCanvas() + (y << 4);
    return (u8)((*(u32 *)(row + (((s32)x >> 3) << 2)) >> ((x & 7) << 2)) & 0xf);
}

s32 PatternEditorMenu::findColorInSpan(s32 x0, s32 x1, s32 y, s32 v) {
    s32 x = x0;
    u32 *p = (u32 *)((u8 *)getCanvas() + (y << 4)) + (x >> 3);
    s32 sh = (x & 7) << 2;
    for (; x <= x1; x++) {
        if (v == (u8)((*p >> sh) & 0xf)) {
            return x;
        }
        sh += 4;
        if (sh >= 32) {
            sh = 0;
            p++;
        }
    }
    return -1;
}

s32 PatternEditorMenu::findSpanStart(s32 x, s32 y, s32 v) {
    if (x <= 0) {
        return 0;
    }
    s32 i = x - 1;
    u32 *p = (u32 *)((u8 *)getCanvas() + (y << 4)) + (i >> 3);
    s32 sh = (i & 7) << 2;
    for (; i >= 0; i--) {
        if (v != (u8)((*p >> sh) & 0xf)) {
            return i + 1;
        }
        sh -= 4;
        if (sh < 0) {
            sh = 28;
            p--;
        }
    }
    return 0;
}

s32 PatternEditorMenu::findSpanEnd(s32 x, s32 y, s32 v) {
    if (x >= 31) {
        return 31;
    }
    s32 i = x + 1;
    u32 *p = (u32 *)((u8 *)getCanvas() + (y << 4)) + (i >> 3);
    s32 sh = (i & 7) << 2;
    for (; i <= 31; i++) {
        if (v != (u8)((*p >> sh) & 0xf)) {
            return i - 1;
        }
        sh += 4;
        if (sh > 28) {
            sh = 0;
            p++;
        }
    }
    return 31;
}extern "C" GXOamAttr *sPatternEditorToolCursors[12] = {(GXOamAttr *)data_ov123_0229594c, (GXOamAttr *)data_ov123_0229593c, (GXOamAttr *)data_ov123_0229595c, (GXOamAttr *)data_ov123_02295858, (GXOamAttr *)data_ov123_022958b8, 0, (GXOamAttr *)&data_ov123_022958c0, (GXOamAttr *)&data_ov123_022958c0, (GXOamAttr *)data_ov123_02295850, (GXOamAttr *)data_ov123_02295800, (GXOamAttr *)data_ov123_02295800, (GXOamAttr *)data_ov123_02295800};

Unk_ov123_02293010_Q PatternEditorMenu_floodFill_q[64];
u8 PatternEditorMenu_floodFill_q_init;
void PatternEditorMenu::floodFill(u8 x, u8 y, u32 tgt) {
    u32 cur;
    s32 head;
    s32 i;
    s32 ym;
    s32 b;
    u32 m;
    s32 left;
    getCanvas();
    cur = getPixel(x, y);
    if (cur != tgt) {
        if (!PatternEditorMenu_floodFill_q_init) {
            HOST_STATIC_CONSTRUCT(PatternEditorMenu_floodFill_q);
            PatternEditorMenu_floodFill_q_init = 1;
        }
        s32 tail;
        head = 0;
        tail = 1;
        PatternEditorMenu_floodFill_q[0].a = x;
        PatternEditorMenu_floodFill_q[0].b = x;
        PatternEditorMenu_floodFill_q[0].c = y;
        m = *(const u32 *)(sPatternEditorSineTable + 0x140);
        do {
            s32 a = PatternEditorMenu_floodFill_q[head].a;
            b = PatternEditorMenu_floodFill_q[head].b;
            s32 yy = PatternEditorMenu_floodFill_q[head].c;
            head = (head + 1) & m;
            if (tgt != getPixel(a, yy)) {
                left = findSpanStart(a, yy, cur);
                s32 right = findSpanEnd(b, yy, cur);
                for (i = left; i <= right; i++) {
                    setPixel(i, yy, tgt);
                }
                if (yy > 0) {
                    s32 xs = left;
                    ym = yy - 1;
                    do {
                        s32 t = findColorInSpan(xs, right, ym, cur);
                        if (t < 0) {
                            xs = 0xff;
                        } else {
                            s32 r = findSpanEnd(t, ym, cur);
                            PatternEditorMenu_floodFill_q[tail].a = t;
                            PatternEditorMenu_floodFill_q[tail].b = r;
                            PatternEditorMenu_floodFill_q[tail].c = ym;
                            tail = (tail + 1) & m;
                            xs = r + 2;
                        }
                    } while (xs <= right);
                }
                if (yy < 0x1f) {
                    s32 y1 = yy + 1;
                    do {
                        s32 t = findColorInSpan(left, right, y1, cur);
                        if (t < 0) {
                            left = 0xff;
                        } else {
                            s32 r = findSpanEnd(t, y1, cur);
                            PatternEditorMenu_floodFill_q[tail].a = t;
                            PatternEditorMenu_floodFill_q[tail].b = r;
                            PatternEditorMenu_floodFill_q[tail].c = y1;
                            tail = (tail + 1) & m;
                            left = r + 2;
                        }
                    } while (left <= right);
                }
            }
        } while (head != tail);
    }
}

u32 PatternEditorMenu::blendMasked(u32 v, u32 s, u32 t) {
    return (v & ~(s * 15)) | (s * t);
}

void PatternEditorMenu::drawStamp(s32 x, s32 y, u32 a, u32 idx) {
    s32 yy;
    s32 xx;
    u16 *p;
    s32 j;
    u32 mask;
    s32 i;
    s32 xs;
    yy = y - 8;
    p = sStampBitmaps[idx];
    j = 0;
    xs = x - 7;
    for (; j < 16; p++, yy++, j++) {
        mask = 0x8000;
        xx = xs;
        for (i = 0; i < 16; xx++, i++) {
            if ((mask & *p) != 0) {
                setPixel(xx, yy, a);
            }
            mask = (mask << 15) >> 16;
        }
    }
}

void PatternEditorMenu::applyToolAt(u8 x, u8 y) {
    u32 st = tool;
    if (st <= 2) {
        plotBrush(x, y, color, st, 1);
    } else if (st >= 3 && st <= 4) {
        drawStamp(x, y, color, st - 3);
        Snd_PlaySe(0x867);
    } else {
        if (st >= 9 && st <= 0xb) {
            Snd_PlaySe(0x867);
        }
        switch (tool) {
        case 9:
            floodFill(x, y, color);
            break;
        case 0xb:
            fillCanvas(color);
            break;
        case 0xa:
            fillWithMask(color);
            break;
        }
    }
}

void PatternEditorMenu::useToolAtTouch() {
    setCanvasPosFromTouch();
    if (tool >= 6 && tool <= 8) {
        startShape();
        startStylusStroke();
    } else {
        saveUndoState();
        applyToolAt(penX, penY);
        if (tool <= 2) {
            Snd_PlaySe(0x85f);
            Snd_PlaySe(0x861);
            setFlags(0x1000);
        }
        startStylusStroke();
        setFlags(0x40);
    }
}

void PatternEditorMenu::useToolAtCursor() {
    penX = canvasCursorX;
    penY = canvasCursorY;
    if (tool >= 6 && tool <= 8) {
        startShape();
        setMainState(6);
    } else {
        saveUndoState();
        applyToolAt(penX, penY);
        if (tool <= 2) {
            Snd_PlaySe(0x85f);
            Snd_PlaySe(0x861);
            setMainState(5);
        }
        setFlags(0x40);
    }
}

void PatternEditorMenu::drawPendingShape() {
    if (testFlags(0x100)) {
        if (tool >= 6 && tool <= 8) {
            u8 xa, yhi, xb, yb, xlo, xhi, ylo, ya;
            saveUndoState();
            xa = penX;
            xb = shapeStartX;
            if (xb >= xa) {
                xlo = xa;
                xhi = xb;
            } else {
                xhi = xa;
                xlo = xb;
            }
            ya = penY;
            yb = shapeStartY;
            if (yb >= ya) {
                ylo = ya;
                yhi = yb;
            } else {
                yhi = ya;
                ylo = yb;
            }
            switch (tool) {
            case 8:
                drawLine(xb, yb, xa, ya, color, 0);
                break;
            case 6:
                drawRect(xlo, ylo, xhi, yhi, color);
                break;
            case 7:
                drawEllipse(xlo, ylo, xhi, yhi, color, 0);
                break;
            }
            setFlags(0x40);
            Snd_PlaySe(0x867);
        }
    }
}

void PatternEditorMenu::pickColorAtCursor() {
    setColor(getPixel(canvasCursorX, canvasCursorY));
}

void PatternEditorMenu::setButtonPalette(u32 a, u32 b) {
    if (a <= 0xc) {
        u32 t = sPatternEditorButtonTileY[a];
        BgScreen_SetRectPalette(buttonScreen, sPatternEditorButtonTileX0[a], t, sPatternEditorButtonTileX1[a], t + 2, b);
        setFlags(0x10);
    }
}

void PatternEditorMenu::flushButtonScreen() {
    if (testFlags(0x10)) {
        if (((BgVramTask *)(&bgTasks[2]))->requestScreen(buttonScreen, 6, 0x800, 0)) {
            clearFlags(0x10);
        }
    }
}

void PatternEditorMenu::selectTool(u32 v) {
    if (tool != v) {
        if (tool != 0x22) {
            setButtonPalette(tool, 4);
            Snd_PlaySe(0xb);
        }
        tool = v;
        setButtonPalette(tool, 5);
    }
}

void PatternEditorMenu::flashButton(u32 v) {
    stopButtonFlash();
    flashButtonId = v;
    flashTimer = 4;
    setButtonPalette(flashButtonId, 5);
}

void PatternEditorMenu::stopButtonFlash() {
    setButtonPalette(flashButtonId, 4);
    flashButtonId = 0x22;
    flashTimer = 0;
}

void PatternEditorMenu::updateButtonFlash() {
    if (flashTimer != 0) {
        flashTimer = flashTimer - 1;
        if (flashTimer == 0) {
            stopButtonFlash();
        }
    }
}

void PatternEditorMenu::resetPaletteLabel() {
    paletteLabel[0].destroyLabel();
}

void PatternEditorMenu::drawShapeCorner(s32 x, s32 y, u32 i) {
    s32 a = canvasToScreenX(x);
    s32 b = canvasToScreenY(y);
    u16 t = data_ov123_022958c0.b;
    t &= ~0x18;
    t |= data_ov123_02295840[i];
    data_ov123_022958c0.b = t;
    Oam_DrawObj(1, &data_ov123_022958c0, a, b, -1, -1, 0);
}

void PatternEditorMenu::drawPreviewDot(s32 x, s32 y) {
    s32 a = canvasToScreenX(x);
    s32 b = canvasToScreenY(y);
    Oam_DrawObj(1, data_ov123_022958a8, a, b, -1, -1, 0);
}

void PatternEditorMenu::drawCanvasCursor(s32 x, s32 y) {
    s32 a = canvasToScreenX(x);
    s32 b = canvasToScreenY(y);
    GXOamAttr *p = sPatternEditorToolCursors[tool];
    if (testFlags(0x800)) {
        p = (GXOamAttr *)data_ov123_02295830;
    }
    if (tool == 1) {
        a -= 2;
        b -= 2;
    }
    if (p != NULL) {
        Oam_DrawCell(1, p, a, b, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
}

void PatternEditorMenu::drawLineEndMarker(s32 x, s32 y) {
    s32 a = canvasToScreenX(x);
    s32 b = canvasToScreenY(y);
    Oam_DrawObj(1, data_ov123_02295850, a, b, -1, -1, 0);
}

void PatternEditorMenu::drawShapePreview() {
    if (tool == 8) {
        drawLineEndMarker(penX, penY);
        drawLineEndMarker(shapeStartX, shapeStartY);
        drawLine(penX, penY, shapeStartX, shapeStartY, 1, 3);
    } else {
        u8 xlo = shapeStartX;
        u8 xa = penX;
        u8 xhi;
        u32 cx0, cx1;
        if (xa >= xlo) {
            cx1 = 2;
            cx0 = 0;
            xhi = xa;
        } else {
            cx1 = 0;
            cx0 = 2;
            xhi = xlo;
            xlo = xa;
        }
        u8 ylo = shapeStartY;
        u8 ya = penY;
        u8 yhi;
        if (ya >= ylo) {
            cx0 = cx0 + 1;
            yhi = ya;
        } else {
            cx1 = cx1 + 1;
            yhi = ylo;
            ylo = ya;
        }
        drawShapeCorner(xa, ya, cx0);
        drawShapeCorner(shapeStartX, shapeStartY, cx1);
        u8 i = xlo;
        for (; i <= xhi; i = i + 2) {
            drawPreviewDot(i, ylo);
        }
        if (ylo != yhi) {
            i = xlo;
            if (((yhi - ylo) & 1) != 0) {
                i = xlo + 1;
            }
            for (; i <= xhi; i = i + 2) {
                drawPreviewDot(i, yhi);
            }
        }
        u32 t = ylo + 2;
        u8 j = t;
        for (; j < yhi; j = j + 2) {
            drawPreviewDot(xlo, j);
        }
        if (xlo != xhi) {
            j = t;
            if (((xhi - xlo) & 1) != 0) {
                j = j - 1;
            }
            for (; j < yhi; j = j + 2) {
                drawPreviewDot(xhi, j);
            }
        }
    }
}

void PatternEditorMenu::startShape() {
    Snd_PlaySe(0x866);
    setFlags(0x100);
    shapeStartX = penX;
    shapeStartY = penY;
}

void PatternEditorMenu::resetShapeDrag() {
    clearFlags(0x100);
    u16 t = data_ov123_022958c0.b;
    t &= ~0x18;
    t |= 8;
    data_ov123_022958c0.b = t;
}

void PatternEditorMenu::endShapeAndResume() {
    drawPendingShape();
    resetShapeDrag();
    resumeInput();
}

void PatternEditorMenu::cancelVramTasks() {
    s32 i;
    for (i = 0; i < 3; i++) {
        bgTasks[i].cancel();
    }
}

void PatternEditorMenu::saveUndoState() {
    clearFlags(0x4000);
    if (testFlags(0x80)) {
        MIi_CpuCopy32(canvasA, canvasB, 0x200);
        clearFlags(0x80);
    } else {
        MIi_CpuCopy32(canvasB, canvasA, 0x200);
        setFlags(0x80);
    }
}

void PatternEditorMenu::toggleUndo() {
    if (testFlags(0x80)) {
        clearFlags(0x80);
    } else {
        setFlags(0x80);
    }
    if (testFlags(0x4000)) {
        Snd_PlaySe(0x86c);
        clearFlags(0x4000);
    } else {
        Snd_PlaySe(0x86b);
        setFlags(0x4000);
    }
    setFlags(0x40);
}

u8 *PatternEditorMenu::getCanvas() {
    if (testFlags(0x80)) {
        return canvasA;
    }
    return canvasB;
}

void PatternEditorMenu::showCursor() {
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    cursor.warpTo(a, b);
    if ((u8)(cursorTarget + 0xe3) <= 1) {
        ((MenuCursor *)&cursor)->setAnimIfChanged(7);
    } else {
        ((MenuCursor *)&cursor)->setAnimIfChanged(1);
    }
    refreshCursor();
}

u32 PatternEditorMenu::getCursorTargetX() { return sPatternEditorCursorX[cursorTarget]; }

u32 PatternEditorMenu::getCursorTargetY() { return sPatternEditorCursorY[cursorTarget]; }

void PatternEditorMenu::hideCursor() {
    ((MenuCursor *)&cursor)->setAnimIfChanged(0);
    cursor.update();
}


void PatternEditorMenu::refreshCursor() {
    cursor.setPoseIdle();
    cursor.update();
}

void PatternEditorMenu::pressCursor() {
    ((MenuCursor *)&cursor)->setPosePress();
    setMainState(0xa);
}

void PatternEditorMenu::releaseCursor() {
    cursor.setPoseRelease();
    setMainState(0xb);
}

void PatternEditorMenu::moveCursorToTarget() {
    if ((u8)(cursorTarget + 0xe3) <= 1) {
        ((MenuCursor *)&cursor)->switchToAnim07();
    } else {
        ((MenuCursor *)&cursor)->switchToAnim01();
    }
    if (testFlags(0x200)) {
        s32 a = getCursorTargetX();
        s32 b = getCursorTargetY();
        cursor.warpTo(a, b);
        clearFlags(0x200);
    } else {
        s32 a = getCursorTargetX();
        s32 b = getCursorTargetY();
        cursor.moveToEase(a, b, 3, 1);
        returnState = mainState;
        setMainState(9);
    }
}

BOOL PatternEditorMenu::moveCursorByPad(u32 pad) {
    if (pad == 0) {
        return FALSE;
    }
    u32 old = cursorTarget;
    if (MenuKeys_HasUp(pad)) {
        if (cursorTarget != 0x1d) {
            if (cursorTarget == 0x1e) {
                if (cursorMode == 0) {
                    cursorTarget = 5;
                } else {
                    cursorTarget = 0x16;
                }
                return TRUE;
            }
        } else {
            if (cursorMode == 0) {
                cursorTarget = 5;
            } else {
                cursorTarget = 0x1c;
            }
            return TRUE;
        }
    }
    if (MenuKeys_HasLeft(pad)) {
        cursorTarget = sPatternEditorNavLeft[cursorTarget];
    } else if (MenuKeys_HasRight(pad)) {
        cursorTarget = sPatternEditorNavRight[cursorTarget];
    }
    if (old == cursorTarget || cursorTarget <= 0xb) {
        if (MenuKeys_HasUp(pad)) {
            cursorTarget = sPatternEditorNavUp[cursorTarget];
        } else if (MenuKeys_HasDown(pad)) {
            cursorTarget = sPatternEditorNavDown[cursorTarget];
        }
    }
    u32 now = cursorTarget;
    if (old != now) {
        if (now >= 0xe && now <= 0x1c && old >= 0xe && old <= 0x1c) {
            setFlags(0x200);
            Snd_PlaySe(0x869);
        }
        return TRUE;
    }
    return FALSE;
}

BOOL PatternEditorMenu::moveCanvasCursor(s32 unused, s32 flag) {
    u32 cx = canvasCursorX;
    u32 cy = canvasCursorY;
    u32 t0 = gPad[0];
    if (t0 & 0x20) {
        if (gPad[1] & 0x20) {
            moveDelay = 4;
        }
        if (cx != 0) {
            cx = (u8)(cx - 1);
        }
    } else if (t0 & 0x10) {
        if (gPad[1] & 0x10) {
            moveDelay = 4;
        }
        if (cx < 0x1f) {
            cx = (u8)(cx + 1);
        }
    }
    u32 t1 = *(volatile u16 *)&gPad[0];
    if (t1 & 0x40) {
        if (gPad[1] & 0x40) {
            moveDelay = 4;
        }
        if (cy != 0) {
            cy = (u8)(cy - 1);
        }
    } else if (t1 & 0x80) {
        if (gPad[1] & 0x80) {
            moveDelay = 4;
        }
        if (cy < 0x1f) {
            cy = (u8)(cy + 1);
        }
    }
    if (canvasCursorX != cx || canvasCursorY != cy) {
        u32 b3 = moveDelay;
        if (b3 == 0) {
        } else if (b3 == 4) {
            moveDelay = *(volatile u8 *)&moveDelay - 1;
        } else {
            moveDelay = *(volatile u8 *)&moveDelay - 1;
            return FALSE;
        }
        canvasCursorX = cx;
        canvasCursorY = cy;
        if (flag == 0) {
            Snd_PlaySe(0x865);
        }
        Snd_SetPanIfChanged((u8)canvasToScreenX(cx));
        return TRUE;
    }
    moveDelay = 0;
    return FALSE;
}

void PatternEditorMenu::toggleGrid() {
    if (testFlags(0x20)) {
        hideGrid();
        Snd_PlaySe(0x42);
    } else {
        showGrid();
        Snd_PlaySe(0x41);
    }
}

void PatternEditorMenu::showGrid() {
    if (!testFlags(0x20)) {
        setFlags(0x20);
        Gfx2d_ShowLayer(3);
        Gfx2d_SetSubAlphaBlend(1, 8, 12);
    }
}

void PatternEditorMenu::hideGrid() {
    if (testFlags(0x20)) {
        clearFlags(0x20);
        Gfx2d_HideLayer(3);
    }
}

BOOL PatternEditorMenu::cycleColorByShoulder() {
    u32 t = gPad[1];
    if (t & 0x200) {
        u32 v = color;
        if (v > 1) {
            setColor(v - 1);
        } else {
            setColor(0xf);
        }
        return TRUE;
    }
    if (t & 0x100) {
        u32 v = color;
        if (v < 0xf) {
            setColor(v + 1);
        } else {
            setColor(1);
        }
        return TRUE;
    }
    return FALSE;
}

void PatternEditorMenu::startStylusStroke() {
    hoverTimer = 0;
    hoverButton = 0x22;
    setMainState(2);
    clearFlags(0x2000);
    lastTouchX = gTouchCurX;
    lastTouchY = gTouchCurY;
}

void PatternEditorMenu::updateStylusStroke() {
    u8 old_a8 = penX;
    u8 old_a9 = penY;
    setCanvasPosFromTouch();
    if (testFlags(0x1000)) {
        if (tool <= 2) {
            s32 cx = gTouchCurX;
            s32 cy = gTouchCurY;
            s32 bx = lastTouchX;
            if (cx != bx || cy != lastTouchY) {
                s32 d = bx - cx;
                if (d < 0) {
                    d = -d;
                }
                s32 by = lastTouchY;
                if (by > cy) {
                    d = d + (by - cy);
                } else {
                    d = d - (by - cy);
                }
                Snd_SetSeHandleVolumes(d);
                setFlags(0x100000);
            }
            if (penX != old_a8 || penY != old_a9) {
                if (drawLine(penX, penY, old_a8, old_a9, color, tool)) {
                    Snd_PlaySe(0x861);
                }
                setFlags(0x40);
            }
        }
    }
    u32 r = hitTestTouch();
    if ((u8)(r + 0xdf) <= 1) {
        hoverButton = 0x22;
    } else if (testFlags(0x2000)) {
        if (r != hoverButton) {
            clearFlags(0x2000);
            hoverTimer = 0;
        }
    } else if (r == hoverButton) {
        hoverTimer = hoverTimer + 1;
        if (hoverTimer >= 0x14) {
            if (testFlags(0x80000)) {
                clearFlags(0x80000);
                clearFlags(0x100000);
                Snd_StopSe(0x862, 1);
            }
            pressedButton = hoverButton;
            activateButton();
            resetShapeDrag();
            clearFlags(0x1000);
            setFlags(0x2000);
        }
    } else {
        hoverButton = r;
        hoverTimer = 0;
    }
}

void PatternEditorMenu::beginScreenDim() {
    if (testFlags(0x20)) {
        hideGrid();
        setFlags(0x20000);
    }
    Gfx2d_BeginSubObjWinBrightness();
    Gfx2d_SetSubBrightness(-6);
    ((MenuBottomButtonsBody *)&bottomButtons)->enableObjWindow();
    Gfx2d_SetSubWin1Planes(0x1f, 0);
    Gfx2d_EnableSubWindows(2);
    Gfx2d_SetSubWin1Rect(0x40, 0x18, 0xc0, 0x98);
}


void PatternEditorMenu::endScreenDim() {
    Gfx2d_EndSubObjWinBrightness();
    ((MenuBottomButtonsBody *)&bottomButtons)->disableObjWindow();
    Gfx2d_DisableSubWindows(2);
}

BOOL PatternEditorMenu::testFlags(u32 mask) {
    if (flags & mask) {
        return TRUE;
    }
    return FALSE;
}

void PatternEditorMenu::setFlags(u32 mask) { flags = flags | mask; }

void PatternEditorMenu::clearFlags(u32 mask) { flags = flags & ~mask; }

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov123_02291f60) {
    HOST_OVERLAY_VAR(sPatternEditorMenuProfile),
    HOST_OVERLAY_VAR(data_ov123_0229594c),
    HOST_OVERLAY_VAR(data_ov123_0229596c),
    HOST_OVERLAY_VAR(data_ov123_02295840),
    HOST_OVERLAY_VAR(data_ov123_02295828),
    HOST_OVERLAY_VAR(data_ov123_0229591c),
    HOST_OVERLAY_VAR(data_ov123_022958b8),
    HOST_OVERLAY_VAR(data_ov123_022958c0),
    HOST_OVERLAY_VAR(data_ov123_02295a94),
    HOST_OVERLAY_VAR(data_ov123_02295a24),
    HOST_OVERLAY_VAR(data_ov123_02295b24),
    HOST_OVERLAY_VAR(data_ov123_02295848),
    HOST_OVERLAY_VAR(data_ov123_02295900),
    HOST_OVERLAY_VAR(data_ov123_0229595c),
    HOST_OVERLAY_VAR(data_ov123_0229590c),
    HOST_OVERLAY_VAR(data_ov123_02295830),
    HOST_OVERLAY_VAR(data_ov123_0229593c),
    HOST_OVERLAY_VAR(data_ov123_02295858),
    HOST_OVERLAY_VAR(data_ov123_02295850),
    HOST_OVERLAY_VAR(data_ov123_02295800),
    HOST_OVERLAY_VAR(sStampBitmaps),
    HOST_OVERLAY_VAR(data_ov123_022958a8),
    HOST_OVERLAY_VAR(sPatternEditorToolCursors),
    HOST_OVERLAY_VAR(PatternEditorMenu_floodFill_q),
    HOST_OVERLAY_VAR(PatternEditorMenu_floodFill_q_init),
    HOST_OVERLAY_VARS_END
};
