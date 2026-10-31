#ifndef MENU_MENUTEXTBUTTON_H
#define MENU_MENUTEXTBUTTON_H

#include "types.h"
#include "ui/LabelString.h"
#include "nitro/gxoam.h"

class MenuTextButton {
public:
    MenuTextButton();
    virtual ~MenuTextButton();

    u32 getPressOffset();
    void freeText();
    void clearFlags(u32 m);
    void setFlags(u32 m);
    BOOL testFlags(u32 m);
    void renderText(u8 a, u8 b);
    void setLabelNoShadow(u8 v);
    void setLabelWithShadow(u8 v);
    void setLabel(u8 v);
    void setup(GXOamAttr *p, u8 a, u8 b);
    BOOL isDisabled();
    void setEnabled();
    void setDisabled();
    void disableObjWindow();
    void enableObjWindow();
    BOOL stepPress();
    void drawAt(s32 x, s32 y, s32 c);

    /* 0x04 */ LabelString caption;
    /* 0x44 */ GXOamAttr *cells;
    /* 0x48 */ u8 widthTiles;
    /* 0x49 */ u8 pressStep;
    /* 0x4a */ u8 frameCellCount;
    /* 0x4b */ u8 msgId;
    /* 0x4c */ u8 flags;
};

#endif
