#ifndef TALK_MAILTEXTBUILDER_H
#define TALK_MAILTEXTBUILDER_H

#include "types.h"
#include "talk/BmgReader.h"
#include "talk/MsgTag.h"
#include "talk/MsgWalker.h"
#include "talk/MsgString33.h"

class MailMsgRequest;
class MailTextBuilder;

class BmgReader512 : public BmgReader {
public:
    BmgReader512();
    virtual ~BmgReader512();
    virtual u8 *getBuffer();
    virtual u32 getBufferSize();
    void clearBuffer();

    /* 0xa4 */ u8 buffer[0x200];
};

class MailTextExpander;
typedef void (MailTextExpander::*MailTextExpanderFn)();

class MailTextExpander : public MsgWalker {
public:
    MailTextExpander(MailTextBuilder *owner);
    virtual ~MailTextExpander();
    virtual void onBegin();
    virtual void onEnd();
    virtual void onChar(u32 v);
    virtual void onTag(u8 *p);
    virtual BOOL canContinue();

    void selectBySlotForm(MsgString33 *e);
    void selectByUnkCondition(s32 sel);
    void setCapitalizeNext(s32 sel);
    void setUnkMode2(s32 sel);
    void setUnkMode1(s32 sel);
    void handleGrammarTag();
    void insertGlyphTag();
    void insertSlot();
    void appendChar();
    u8 expand(u8 flag);

    /* 0x24 */ MailTextBuilder *builder;
    /* 0x28 */ MsgTag tag;
    /* 0x3c */ s32 curChar;
    /* 0x40 */ s32 outLen;
    /* 0x44 */ u8 success;
    /* 0x45 */ u8 capitalizeNext;
    /* 0x48 */ u8 *selectEnd;
    /* 0x4c */ s32 articleMode;
    /* 0x50 */ u8 trackNamePos;
    /* 0x54 */ s32 charCount;
    /* 0x58 */ s32 newlineCount;
};

class MailTextBuilder {
public:
    MailTextBuilder();
    ~MailTextBuilder();
    BOOL load(MailMsgRequest *p);
    void reset();

    /* 0x000 */ MailTextExpander expander;
    /* 0x05c */ BmgReader512 reader;
    /* 0x300 */ u8 output[0x200];
    /* 0x500 */ s32 namePos;
    /* 0x504 */ MsgString33 slots[11];
};

#endif
