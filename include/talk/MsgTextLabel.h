#ifndef TALK_MSGTEXTLABEL_H
#define TALK_MSGTEXTLABEL_H

#include "types.h"
#include "text/Unk_02050288.h"

class MsgProcessor;

class MsgTextLabel : public TextLabel {
public:
    MsgTextLabel(u8 *buf, s32 widthTiles, s32 heightTiles);
    MsgTextLabel(u32 tileIndex, s32 widthTiles, s32 heightTiles);
    virtual ~MsgTextLabel();
    virtual void draw();
    virtual u32 measureWidth();

    void onTag(u8 *p);
    void onChar(u32 c);
    void onEnd();
    void onBegin();
    void setProcessor(MsgProcessor *v);

    /* 0x7c */ u32 mode;
    /* 0x80 */ MsgProcessor *processor;
};

#endif
