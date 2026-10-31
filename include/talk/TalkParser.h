#ifndef TALK_TALKPARSER_H
#define TALK_TALKPARSER_H

#include "types.h"
#include "talk/MsgWalker.h"
#include "talk/MsgTag.h"

class TalkWindowState;
class TalkTextBox;
class MsgString;

class TalkCharStepper : public MsgWalker {
public:
    TalkCharStepper(TalkWindowState *owner, TalkTextBox *buf);
    virtual ~TalkCharStepper();
    virtual void onBegin();
    virtual void onEnd();
    virtual void onChar(u32 c);
    virtual void onTag(u8 *p);
    virtual BOOL canContinue();

    void stop();
    BOOL isIdle();
    void stepOnce();
    void startUntil(u8 *p, u8 *end, u8 flag);
    void startCount(u8 *p, s32 n, u8 flag);

    /* 0x24 */ TalkWindowState *window;
    /* 0x28 */ TalkTextBox *textBox;
    /* 0x2c */ s32 mode;
    /* 0x30 */ u8 *endPos;
    /* 0x34 */ s32 remaining;
    /* 0x38 */ u8 stepAllowed;
    /* 0x39 */ u8 printChars;
};

struct TalkParserSpeedState {
    /* 0x4c */ u8 fastForward, holdStep, instant, fastForwardLock;
    /* 0x50 */ s32 charCount, stepPhase, waitTimer, textColor;
    TalkParserSpeedState() {
        fastForward = 0;
        holdStep = 0;
        instant = 0;
        fastForwardLock = 0;
        charCount = 0;
        stepPhase = 0;
        waitTimer = 0;
        textColor = 0;
    }
};

class TalkParser : public MsgWalker {
public:
    TalkParser(TalkWindowState *owner, TalkTextBox *buf);
    virtual ~TalkParser();
    virtual void onBegin();
    virtual void onEnd();
    virtual void onChar(u32 c);
    virtual void onTag(u8 *p);
    virtual BOOL canContinue();

    void dispatchTag();
    void tagGroup00();
    void tagGroup01();
    void tagGroup02();
    void tagGroup03();
    void tagGroup04();
    void tagGroup05();
    void tagGroup06();
    void tagGroup07();
    void tagGroup08();
    void tagGroup09();
    void tagGroup0a();
    void tagGroup0b();
    void tagGroupFf();

    void jumpToMessage(u8 *p);
    void selectBySlotForm(MsgString *p);
    void selectByPlayerGender();
    void expandNamedSlot(s32 idx);
    void expandSlot(s32 idx);
    void expandArticle(MsgString *ent, BOOL flag);
    BOOL stepSpeed();
    void stepSteppers();
    BOOL steppersIdle();
    void debugPrintMissing(s32 line, const char *what);
    void resetColor();
    void clearFastForward();
    void setFastForward();
    void setPrintMode(s32 v);
    void stop();

    void tagNop();
    void tagGlyph0();
    void tagGlyph1();
    void tagGlyph6();
    void tagGlyph7();
    void tagGlyph8();
    void tagWait();
    void tagPageBreak();
    void tagFastOn();
    void tagFastOff();
    void tagFastLockOn();
    void tagFastLockOff();
    void tagGreeting();
    void tagGreetingEnd();
    void tagShakeSmall();
    void tagShakeMedium();
    void tagShakeLarge();
    void tagSignal0();
    void tagSignal1();
    void tagSignal2();
    void tagSignal3();
    void tagSignal4();
    void tagAutoAdvance();
    void tagChoice2();
    void tagChoice3();
    void tagChoice4();
    void tagChoice5();
    void tagChoice2B();
    void tagChoice3B();
    void tagChoice4B();
    void tagChoice5B();
    void tagAction0();
    void tagAction1();
    void tagAction2();
    void tagAction3();
    void tagAction4();
    void tagPlayerName();
    void tagSpeakerName();
    void tagCatchphrase();
    void tagTownName();
    void tagYear();
    void tagMonth();
    void tagDay();
    void tagWeekday();
    void tagHour();
    void tagMinute();
    void tagNumber1714();
    void tagFriendName();
    void tagEnemyName();
    void tagRandomVillagerName();
    void tagOtherResidentName();
    void tagSlot0();
    void tagSlot1();
    void tagSlot2();
    void tagSlot3();
    void tagSlot4();
    void tagSlot5();
    void tagSlot6();
    void tagSlot7();
    void tagSlot8();
    void tagSlot9();
    void tagSlot10();
    void tagNamedSlot0();
    void tagNamedSlot1();
    void tagNamedSlot2();
    void tagNamedSlot3();
    void tagImpression();
    void tagNickname();
    void tagNop0420();
    void tagCompliment();
    void tagTrend();
    void tagChoiceSlots();
    void tagBranchRandom2();
    void tagBranchRandom3();
    void tagBranchFriendship();
    void tagBranchPlayerGender();
    void tagBranchHouseUnk();
    void tagBranchInsectCount();
    void tagBranchFishCount();
    void tagBranchVillagerCount();
    void tagBranchUnk8();
    void tagBranchWeather();
    void tagBranchResidentCount();
    void tagBranchWeekday();
    void tagBranchVisitor();
    void tagBranchSpecies();
    void tagNop0800();
    void tagNop0801();
    void tagNop0802();
    void tagSignal09_0();
    void tagSignal09_1();
    void tagSignal09_2();
    void tagSignal09_3();
    void tagSignal09_4();
    void tagSignal09_5();
    void tagSignal09_6();
    void tagSignal09_7();
    void tagSignal09_8();
    void tagSignal09_9();
    void tagNop0a00();
    void tagArticleMode1();
    void tagArticleMode2();
    void tagCapitalizeNext();
    void tagSelectByPlayerGender();
    void tagSlotForm0();
    void tagSlotForm1();
    void tagSlotForm2();
    void tagSlotForm3();
    void tagSlotForm4();
    void tagSlotForm5();
    void tagSlotForm6();
    void tagSlotForm7();
    void tagSlotForm8();
    void tagSlotForm9();
    void tagSlotForm10();
    void tagNamedSlotForm0();
    void tagNamedSlotForm1();
    void tagNamedSlotForm2();
    void tagNamedSlotForm3();
    void tagColor();
    void tagAltText();

    /* 0x24 */ TalkWindowState *window;
    /* 0x28 */ TalkTextBox *textBox;
    /* 0x2c */ u32 lineCount;
    /* 0x30 */ s32 printStatus;
    /* 0x34 */ s32 printMode;
    /* 0x38 */ MsgTag tag;
    /* 0x4c */ TalkParserSpeedState printVars;
    /* 0x60 */ TalkCharStepper altTextStepper;
    /* 0x9c */ TalkCharStepper mainTextStepper;
    /* 0xd8 */ u8 choiceDeferred;
    /* 0xd9 */ u8 capitalizeNext;
    /* 0xdc */ u8 *selectEnd;
    /* 0xe0 */ s32 articleMode;
};

#endif
