#ifndef UI_FIELDINFOLABELBALLOON_H
#define UI_FIELDINFOLABELBALLOON_H

#include "types.h"
#include "ui/LabelBalloon.h"
#include "gfx/SpriteAnim.h"

class FieldInfoLabelBalloon : public LabelBalloon {
public:
    FieldInfoLabelBalloon();
    virtual ~FieldInfoLabelBalloon();
    virtual void draw();
    virtual void update();

    void restartMarkerAnim();
    BOOL isBlinkVisible();
    BOOL isBlinkCycleEnd();
    void setBlink(u8 v);
    void resetBalloon();
    void requestMarker();
    void updateBlink();

    /* 0xbc */ SpriteAnim markerAnim;
    /* 0xd0 */ s32 blinkFrame;
    /* 0xd4 */ u8 markerRequest;
    /* 0xd5 */ u8 markerShown;
    /* 0xd6 */ u8 markerDrawn;
    /* 0xd7 */ u8 markerDrawnPrev;
    /* 0xd8 */ u8 blinkEnabled;
};

#endif
