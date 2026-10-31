#ifndef TALK_MSGQUERY_H
#define TALK_MSGQUERY_H

#include "types.h"
#include "talk/MsgWalker.h"
#include "talk/MsgTag.h"

class MsgQuery : public MsgWalker {
public:
    MsgQuery();
    virtual ~MsgQuery();
    virtual void onBegin();
    virtual void onEnd();
    virtual void onChar(u32 v);
    virtual void onTag(u8 *cmd);
    virtual BOOL canContinue();

    void onTagFind();
    void onCharCountLines();
    void onCharCount();
    void onCharFindNth();
    void resetQuery();

    /* 0x24 */ u32 mode;
    /* 0x28 */ MsgTag tag;
    /* 0x3c */ u32 curChar;
    /* 0x40 */ s32 findGroup;
    /* 0x44 */ s32 findId;
    /* 0x48 */ u32 targetIndex;
    /* 0x4c */ u32 charCount;
    /* 0x50 */ u32 targetLines;
    /* 0x54 */ u32 lineCount;
    /* 0x58 */ u8 isDone;
};

#endif
