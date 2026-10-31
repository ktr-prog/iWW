#ifndef MENU_POPUPCHOICEROW_H
#define MENU_POPUPCHOICEROW_H

#include "types.h"
#include "ui/LabelString.h"

class PopupChoiceRow : public LabelString {
public:
    PopupChoiceRow();
    virtual ~PopupChoiceRow();

    void setup(u32 a, u16 b, u8 c, u8 d);
    void render(s32 v);

    /* 0x40 */ u16 charBase;
    /* 0x42 */ u8 layer;
    /* 0x43 */ u8 fgColor;
    /* 0x44 */ u8 bgColor;
};

#endif
