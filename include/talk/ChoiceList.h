#ifndef TALK_CHOICELIST_H
#define TALK_CHOICELIST_H

#include "types.h"
#include "talk/BmgMsgAttr.h"
#include "talk/ChoiceString.h"

class ChoiceEntry {
public:
    ChoiceEntry();
    ~ChoiceEntry();
    void loadText();
    void setSeType(s32 v);
    void setName(const char *src);
    void setValue(const u8 *p);
    void setBmgName(const void *p);
    void setMsgIndex(const u8 *p);
    s32 getSeType();
    u8 *getWeightPtr();
    BmgMsgAttr *getAttr();
    char *getName();
    u8 *getValuePtr();
    ChoiceString *getText();
    void clear();

    /* 0x00 */ u8 msgIndex;
    /* 0x04 */ const void *bmgName;
    /* 0x08 */ ChoiceString text;
    /* 0x3c */ BmgMsgAttr attr;
    /* 0x48 */ u8 value;
    /* 0x49 */ char name[0x1a];
    /* 0x63 */ u8 weight;
    /* 0x64 */ s32 seType;
};

class ChoiceList {
public:
    ChoiceList();
    ~ChoiceList();
    void pickBySliderPos(s32 arg);
    void pick(s32 idx);
    void setCancelToLast();
    void setCount(s32 v);
    BmgMsgAttr *getResultAttr();
    ChoiceString *getResultText();
    char *getResultName();
    u8 *getResultValue();
    s32 getSliderValue();
    s32 getResult();
    s32 getCancelIndex();
    s32 getCount();
    ChoiceString *getLastText();
    ChoiceString *getFirstText();
    ChoiceEntry *getEntry(s32 i);
    void clearEntries();
    void clearResult();
    void clear();
    void loadTexts();
    void setEntry(s32 idx, const u8 *a, s32 b, const u8 *c, const char *d, s32 e);
    void reset(s32 a, s32 b);

    /* 0x000 */ ChoiceEntry entries[5];
    /* 0x208 */ s32 count;
    /* 0x20c */ s32 cancelIndex;
    /* 0x210 */ s32 result;
    /* 0x214 */ u8 resultValue;
    /* 0x215 */ char resultName[0x1a];
    /* 0x230 */ ChoiceString resultText;
    /* 0x264 */ BmgMsgAttr resultAttr;
    /* 0x270 */ s32 sliderValue;
};

#endif
