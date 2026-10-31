#ifndef TALK_TALKTEXTBOX_H
#define TALK_TALKTEXTBOX_H

#include "types.h"
#include "talk/MsgProcessor.h"
#include "talk/MsgTag.h"

class TalkWindowState;
class TextLabel;
class MsgTextLabel;
class MsgString;
class MsgString33;

class TalkRenderProcessor : public MsgProcessor {
public:
    TalkRenderProcessor(TalkWindowState *owner);
    virtual ~TalkRenderProcessor();
    virtual void onBegin();
    virtual void onEnd();
    virtual void onChar(u32 c);
    virtual void onTag(u8 *p);

    void tagGroup0b();
    void tagGroup04();
    void tagGroup02();
    void tagGroup01();
    void tagGroup00();
    void tagGroupFf();
    void dispatchTag();
    void selectBySlotForm(MsgString *a);
    void tagAltText();
    void selectByPlayerGender();
    void expandNamedSlot(s32 idx);
    void expandSlot(s32 idx);
    void pushArticle(MsgString *e);
    s32 measureLine(u8 *text, BOOL centered);
    void tagNamedSlotForm3();
    void tagNamedSlotForm2();
    void tagNamedSlotForm1();
    void tagNamedSlotForm0();
    void tagSlotForm10();
    void tagSlotForm9();
    void tagSlotForm8();
    void tagSlotForm7();
    void tagSlotForm6();
    void tagSlotForm5();
    void tagSlotForm4();
    void tagSlotForm3();
    void tagSlotForm2();
    void tagSlotForm1();
    void tagSlotForm0();
    void tagSelectByPlayerGender();
    void tagArticleMode2();
    void tagArticleMode1();
    void tagTrend();
    void tagCompliment();
    void tagNickname();
    void tagImpression();
    void tagNamedSlot3();
    void tagNamedSlot2();
    void tagNamedSlot1();
    void tagNamedSlot0();
    void tagSlot10();
    void tagSlot9();
    void tagSlot8();
    void tagSlot7();
    void tagSlot6();
    void tagSlot5();
    void tagSlot4();
    void tagSlot3();
    void tagSlot2();
    void tagSlot1();
    void tagSlot0();
    void tagOtherResidentName();
    void tagRandomVillagerName();
    void tagEnemyName();
    void tagFriendName();
    void tagNumber1714();
    void tagMinute();
    void tagHour();
    void tagWeekday();
    void tagDay();
    void tagMonth();
    void tagYear();
    void tagTownName();
    void tagCatchphrase();
    void tagSpeakerName();
    void tagPlayerName();
    void tagGreetingEnd();
    void tagGreeting();
    void tagGlyph8();
    void tagGlyph7();
    void tagGlyph6();
    void tagGlyph1();
    void tagGlyph0();

    /* 0x2c */ TalkWindowState *window;
    /* 0x30 */ MsgTextLabel *measureLabel;
    /* 0x34 */ MsgTag tag;
    /* 0x48 */ u8 *altTextEnd;
    /* 0x4c */ u8 *selectEnd;
    /* 0x50 */ u32 articleMode;
};

class TalkTextBox {
public:
    TalkTextBox(TalkWindowState *o);
    ~TalkTextBox();
    void markLineDirty();
    void endText();
    void redrawLines();
    void clearLabels();
    void destroyLabels();
    void createLabels();
    void setCentered(u8 v);
    void setRemainingLineColors(u32 v);
    void beginLine(u8 *src);
    void appendTag(MsgTag *m);
    BOOL appendChar(s32 c0);
    BOOL appendBytes(s8 *src, u32 n);
    void setAllLineColors(u32 v);
    void clearWithColor(u32 v);
    void clear();

    /* 0x000 */ u8 text[0x400];
    /* 0x400 */ u32 length;
    /* 0x404 */ u8 *lineStarts[3];
    /* 0x410 */ u32 numLines;
    /* 0x414 */ u32 lineColors[3];
    /* 0x420 */ MsgTextLabel *labels[3];
    /* 0x42c */ u32 lineOffsets[3];
    /* 0x438 */ u8 lineDirty[3];
    /* 0x43b */ u8 centered;
    /* 0x43c */ TalkRenderProcessor renderer;
};

#endif
