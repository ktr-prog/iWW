#ifndef MENU_GENERALMENUHEADER_H
#define MENU_GENERALMENUHEADER_H

#include "types.h"
#include "ui/LabelString.h"
#include "menu/MenuTextButton.h"

class GeneralMenuHeader {
public:
    GeneralMenuHeader();
    ~GeneralMenuHeader();

    void resetFrame();
    void drawWithIcon(s32 x, s32 y);
    void drawPlain(s32 x, s32 y);
    void loadObjGfx(s32 v);
    void loadBgGfx(s32 a, s32 b);
    void setTitleHighlight(u8 a, u8 b, u32 c, u32 d);
    void setTitleText(void *s, s32 n);
    void redrawTitle();
    void placeTitleText();
    void loadBgGfxForStyle(s32 a);
    void loadTitleBg(s32 a, s32 b);

    /* 0x00 */ LabelString titleLabel[1];
    /* 0x40 */ MenuTextButton iconButton;
    /* 0x90 */ u8 pictureIndex;
    /* 0x91 */ u8 objPalette;
};

#endif
