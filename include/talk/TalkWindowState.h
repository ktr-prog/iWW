#ifndef TALK_TALKWINDOWSTATE_H
#define TALK_TALKWINDOWSTATE_H

#include "types.h"
#include "talk/TalkFrame.h"
#include "talk/ChoiceMenu.h"
#include "talk/ChoiceList.h"
#include "talk/TalkTextBox.h"
#include "talk/TalkBmgReader.h"
#include "talk/TalkParser.h"
#include "talk/MsgRunner.h"
#include "talk/BmgMsgAttr.h"
#include "talk/MsgString33.h"
#include "talk/MsgString25.h"
#include "talk/MsgString11.h"
#include "talk/MsgString9C.h"
#include "talk/MsgString9B.h"
#include "talk/MsgString17.h"
#include "talk/MsgString17B.h"
#include "talk/TalkVoice.h"

class TalkMsgRequest;
class MsgTextLabel;

class TalkWindowState {
public:
    TalkWindowState();
    ~TalkWindowState();
    void advance();
    void onChoiceDone();
    void reloadMessage();
    void loadNextMessage();
    void resetTextVars();
    void execClosed();
    void enterClosed();
    void execClosing();
    void enterClosing();
    void execPrinting();
    void enterPrinting();
    void execWaitInput();
    void enterWaitInput();
    void execOpening();
    void enterOpening();
    void execIdle();
    void enterIdle();
    void applyStateChange();

    void stopText();
    void finish();
    void resetPrint();
    void captureClock();
    void updateShake();
    BOOL isSkipHeld();
    BOOL isAdvanceTriggered();
    BOOL checkDeviceSwitch();
    void storeInputMode();
    void loadInputMode();
    void refreshNameColor();
    void startShake(s32 a, s32 b, s32 c, s32 d);
    MsgString *getNumber1714Text();
    MsgString *getMinuteText();
    MsgString *getHourText();
    MsgString *getWeekdayText();
    MsgString *getDayText();
    MsgString *getMonthText();
    MsgString *getYearText();
    void resetVoice();
    void setVoicePlaying(BOOL v);
    void onCharPrinted(s32 c);
    void draw();
    void update();
    void setSilent();
    void setKeepSe();
    void disableInput();
    void detachRequest();
    void attachRequest(TalkMsgRequest *p);
    void hideBusyIcon();
    void showBusyIcon(u32 se);
    u8 isVoicePlaying();
    ChoiceList *getChoiceList();
    void openChoices(s32 v);
    void setNamedSlot(s32 idx, void *p, u32 color);
    void setSlotFromString(s32 idx, u8 *key, const char *bank);
    s32 setSlot(s32 idx, void *p);
    void clearAdvancePending();
    void setAdvancePending();
    void unlockAdvance();
    void lockAdvance();
    void setNextMessage(u8 *src, void *s);
    BOOL setNextMessageIfUnset(u8 *src, void *s);

    void startAutoAdvance(s32 frames);
    void stopAutoAdvance();
    BOOL tickAutoAdvance();

    void loadMessageAttr();
    const char *matchSubdirPrefix(const char *s);
    const char *matchDirPrefix(const char *s);
    char *buildMessagePath(const char *a, const char *b);
    void scanMessageTags();
    void startMessage();
    void playMessageSe();
    void notifyChoice();
    void notifyMessageEnd();
    void notifyMessageStart();
    void destroyNameLabel();
    void createNameLabel();
    void applyFriendshipDelta(s32 idx);
    BOOL buildGreeting();
    void clearGreeting();
    BOOL buildCompliment();
    void clearCompliment();
    BOOL buildNickname();
    void clearNickname();
    BOOL buildImpression();
    void clearImpression();
    BOOL buildTrend();
    void clearTrend();
    BOOL buildOtherResidentName();
    void clearOtherResidentName();
    BOOL buildRandomVillagerName();
    void clearRandomVillagerName();
    BOOL buildEnemyName();
    void clearEnemyName();
    BOOL buildFriendName();
    void clearFriendName();
    BOOL buildPlayerName();
    void clearPlayerName();
    BOOL buildTownName();
    void clearTownName();
    BOOL buildCatchphrase();
    void clearCatchphrase();
    void clearNamedSlots();
    void clearSlots();
    void reset();
    void resetVars();

    /* 0x0000 */ u32 index;
    /* 0x0004 */ s32 state;
    /* 0x0008 */ s32 nextState;
    /* 0x000c */ s32 stateStep;
    /* 0x0010 */ s32 autoAdvanceTimer;
    /* 0x0014 */ s32 openMode;
    /* 0x0018 */ u8 choicePending;
    /* 0x001c */ TalkFrame frame;
    /* 0x009c */ s32 scrollY;
    /* 0x00a0 */ s16 shakeAngle;
    /* 0x00a4 */ s32 shakeAmplitude;
    /* 0x00a8 */ s32 shakeDecay;
    /* 0x00ac */ s32 shakeScaleX;
    /* 0x00b0 */ s32 shakeScaleY;
    /* 0x00b4 */ ChoiceMenu choiceMenu;
    /* 0x0314 */ ChoiceList choiceList;
    /* 0x0588 */ MsgTextLabel *nameLabel;
    /* 0x058c */ TalkTextBox textBox;
    /* 0x0a1c */ TalkBmgReader msgBuffer;
    /* 0x12c0 */ TalkParser parser;
    /* 0x13a4 */ MsgRunner runner;
    /* 0x13b0 */ TalkMsgRequest *request;
    /* 0x13b4 */ BmgMsgAttr msgAttr;
    /* 0x13c0 */ MsgString33 slots[11];
    /* 0x15fc */ MsgString33 namedSlots[4];
    /* 0x16cc */ u32 namedSlotColors[4];
    /* 0x16dc */ TalkVoice voice;
    /* 0x1708 */ s32 year;
    /* 0x170c */ u8 day, month, minute, hour;
    /* 0x1710 */ s32 weekday, second, timeOfDay;
    /* 0x171c */ MsgString25 yearText;
    /* 0x1748 */ MsgString33 monthText;
    /* 0x177c */ MsgString25 dayText;
    /* 0x17a8 */ MsgString33 weekdayText;
    /* 0x17dc */ MsgString25 hourText, minuteText, secondText;
    /* 0x1860 */ MsgString11 catchphrase;
    /* 0x1880 */ MsgString9C townName;
    /* 0x189c */ MsgString9B playerName, friendName, enemyName, randomVillagerName, otherResidentName;
    /* 0x1928 */ MsgString33 trend, impression;
    /* 0x1990 */ MsgString9B nickname;
    /* 0x19ac */ MsgString17 compliment;
    /* 0x19d0 */ MsgString17B greeting;
    /* 0x19f4 */ u8 randomVillagerNameBuilt, otherResidentNameBuilt, otherResidentIsVillager, nextMsgIndex;
    /* 0x19f8 */ u8 nextFileName[0x1a];
    /* 0x1a12 */ u8 advancePending, advanceLocked, startNotifyPending, endNotifyPending, choiceNotifyPending,
        voicePlaying, inputDisabled, noOpenSe, silent;
};

#endif
