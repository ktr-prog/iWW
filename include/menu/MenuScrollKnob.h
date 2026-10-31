#ifndef MENU_MENUSCROLLKNOB_H
#define MENU_MENUSCROLLKNOB_H

#include "types.h"
#include "ui/ScrollKnob.h"

class MenuScrollKnob : public ScrollKnob {
public:
    MenuScrollKnob();
    virtual ~MenuScrollKnob();

    s32 getGripY();
    s32 getGripX();
    s32 getScreenY();
    s32 getScreenX();
    void updateRelease();
    void release();
    void grab();
    void show();
    BOOL hitTest(s32 x, s32 y);
};

#endif
