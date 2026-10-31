#ifndef TALK_MAILMSGREQUEST_H
#define TALK_MAILMSGREQUEST_H

#include "types.h"
#include "talk/MsgRequest.h"

class MsgString;

class MailMsgRequest : public MsgRequest {
public:
    MailMsgRequest();
    virtual ~MailMsgRequest();
    virtual const char *getMsgDir();
    u32 *getNamePosOut();
    MsgString *getDest();
    void setNamePosOut(u32 *v);
    void setDest(MsgString *v);
    void setPart(u32 v);
    void setFolder(u32 v);
    const char *getPartDir();
    BOOL isAppendPart();

    /* 0x20 */ u32 folder;
    /* 0x24 */ u32 part;
    /* 0x28 */ MsgString *dest;
    /* 0x2c */ u32 *namePosOut;
};

#endif
