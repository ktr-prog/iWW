#ifndef TALK_LABELBALLOONTEXT_H
#define TALK_LABELBALLOONTEXT_H

#include "types.h"
#include "talk/MsgStringBase.h"

class LabelBalloonText : public MsgStringBase {
public:
    LabelBalloonText();
    virtual ~LabelBalloonText();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x04 */ u8 unk_04[0x24];
};

#endif
