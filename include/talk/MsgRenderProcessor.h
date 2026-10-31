#ifndef TALK_MSGRENDERPROCESSOR_H
#define TALK_MSGRENDERPROCESSOR_H

#include "types.h"
#include "talk/MsgProcessor.h"

class MsgRenderProcessor : public MsgProcessor {
public:
    MsgRenderProcessor();
    virtual ~MsgRenderProcessor();
    virtual void onBegin();
    virtual void onEnd();
    virtual void onChar(u32 c);
    virtual void onTag(u8 *p);

    /* 0x2c */ u8 *altTextEnd;
};

#endif
