#ifndef MENU_MENUTITLEBALLOON_H
#define MENU_MENUTITLEBALLOON_H

#include "types.h"
#include "ui/LabelBalloon.h"

class MenuTitleBalloon : public LabelBalloon {
public:
    MenuTitleBalloon();
    virtual ~MenuTitleBalloon();
    virtual void setOrigin(s32 a, s32 b);

    void hideNow();
    void showText(u8 a, s32 b, s32 c);
};

#endif
