#ifndef TALK_MSGREQUEST_H
#define TALK_MSGREQUEST_H

#include "types.h"

class MsgRequest {
public:
    MsgRequest();
    virtual ~MsgRequest();
    virtual void resetMsg();
    virtual const char *getMsgDir() = 0;
    void setFileName(const char *src);

    /* 0x04 */ char fileName[0x1a];
    /* 0x1e */ u8 msgIndex;
};

#endif
