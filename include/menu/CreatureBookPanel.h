#ifndef MENU_CREATUREBOOKPANEL_H
#define MENU_CREATUREBOOKPANEL_H

#include "types.h"
#include "item/ItemIconCache.h"
#include "talk/MsgString.h"
#include "ui/LabelString.h"
#include "gfx/BgVramTask.h"
#include "menu/MenuScrollKnob.h"
#include "menu/InventoryItemGrid.h"
#include "nitro/gxoam.h"

struct CreatureBookIconObj {
    /* 0x0 */ GXOamAttr cell;
    /* 0x8 */ s32 iconId;
};

class MsgString406 : public MsgString {
public:
    MsgString406();
    virtual ~MsgString406();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x12 */ u8 text[0x196];
};

class CreatureBookPanel {
public:
    CreatureBookPanel();
    ~CreatureBookPanel();

    BOOL beginScrollTouch(s32 x, s32 y);
    void syncScrollToKnob();
    void syncKnobToScroll();
    void placeScrollKnob(s32 x);
    void drawScrollKnob();
    BOOL hitDescPageButtons(s32 x, s32 y);
    void drawButtons(s32 y);
    void loadObjGraphics();
    void loadBgGraphics();
    void postUpdate();
    void preUpdate();
    void cleanup();
    void init(u8 a, u8 b, u8 c, u8 d);

    /* 0x000 */ ItemIconCache iconCache;
    /* 0x808 */ MsgString406 descText;
    /* 0x9b0 */ BgVramTask paletteTask;
    /* 0x9d4 */ u16 paletteFile[0x10];
    /* 0x9f4 */ u16 paletteBuf[0x10];
    /* 0xa14 */ ItemIconUploadChars iconUploadChars[9];
    /* 0xe94 */ BgVramTaskPair rowIconTasks[9];
    /* 0x108c */ CreatureBookIconObj rowIcons[9];
    /* 0x10f8 */ LabelString labels[4];
    /* 0x11f8 */ MenuScrollKnob scrollKnob;
    /* 0x1240 */ u32 caughtMask[3];
    /* 0x124c */ s32 knobPos;
    /* 0x1250 */ s32 knobGrabOffset;
    /* 0x1254 */ s32 knobLastTickPos;
    /* 0x1258 */ s32 scroll;
    /* 0x125c */ s32 pendingScroll;
    /* 0x1260 */ s32 firstIconX;
    /* 0x1264 */ s32 iconRowY;
    /* 0x1268 */ s32 firstVisibleEntry;
    /* 0x126c */ s32 firstIconSlot;
    /* 0x1270 */ s32 listLength;
    /* 0x1274 */ s32 scrollMax;
    /* 0x1278 */ s32 pageButtonPalettes[2];
    /* 0x1280 */ s32 listBlendMask;
    /* 0x1284 */ s32 pictureBlendMask;
    /* 0x1288 */ u16 flags;
    /* 0x128a */ u8 pageButtonFlashTimers[2];
    /* 0x128c */ u8 descPageCount;
    /* 0x128d */ u8 mainLayer;
    /* 0x128e */ u8 listLayer;
    /* 0x128f */ u8 pictureLayer;
    /* 0x1290 */ u8 iconTaskCount;
    /* 0x1291 */ u8 descPage;
    /* 0x1292 */ u8 labelCount;
    /* 0x1293 */ u8 mode;
    /* 0x1294 */ u8 shownEntry;
    /* 0x1295 */ u8 selectedEntry;
    /* 0x1296 */ u8 pictureFade;
    /* 0x1297 */ u8 touchTarget;
    /* 0x1298 */ u8 focus;
    /* 0x1299 */ u8 ownTabFocus;
};

#endif
