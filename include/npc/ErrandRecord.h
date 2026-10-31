#ifndef NPC_ERRANDRECORD_H
#define NPC_ERRANDRECORD_H

#include "types.h"
#include "player/PlayerId.h"
#include "sys/ClockDateTime.h"

class ErrandRecord {
public:
    ClockDateTimeWords dateTime;
    u16 item;
    u8 kind;
    u8 stepBits;

    ErrandRecord() { init(); }
    ~ErrandRecord() { func_0209ada0(); }
    void setItem(u16 *p);
    u16 *getItem();
    void setExtra(u8 v);
    u32 getExtra();
    void setStep(u8 v);
    u32 getStep();
    s32 getSubGroup();
    s32 getSlotIndex();
    void setTimeFromNow(s32 x);
    u32 getKind();
    BOOL getGroupIndex(s32 *out);
    s32 getGroup();
    BOOL getClassIndex(s32 *out);
    s32 getClass();
    void start(u8 a, u16 *p, u8 b);
    BOOL isActive();
    void clear();
    void func_0209ada0();
    void init();
};

class PlanErrand {
public:
    ErrandRecord errand;
    PlayerId player;
    u8 step;
    u8 pad_23;
    u16 shownItem;
    u8 count;
    u8 fossilGroup;
    u8 flags;
};

#endif
