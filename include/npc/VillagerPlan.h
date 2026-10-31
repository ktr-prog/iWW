#ifndef NPC_VILLAGERPLAN_H
#define NPC_VILLAGERPLAN_H

#include "types.h"
#include "sys/ClockDateTime.h"
#include "npc/ErrandRecord.h"

class MsgString;

extern "C" void *TrendScores_Construct(void *p);
extern "C" void TrendScores_Destruct();
extern "C" void TrendScores_Clear(void *p);
class TrendScores {
public:
    u8 values[8];

    TrendScores() { TrendScores_Construct(this); }
    ~TrendScores() { TrendScores_Destruct(); }
    u32 get(u32 i);
    void set(u8 i, u32 v);
    void add(u8 i, u32 v);
    void resetAndHalve(u32 i);
    u8 pickTop();
    void copy(const u8 *src);
    void clear() { TrendScores_Clear(this); }
};

struct VillagerPlanFlags { u8 state2Flag : 1; u8 x : 7; };

class VillagerPlan {
public:
    ClockDateTimeWords planTime;
    ClockDateTimeWords stateTime;
    u8 planState;
    TrendScores scores;
    TrendScores pendingScores;
    VillagerPlanFlags flags;
    u8 unk_22[2];

    VillagerPlan();
    ~VillagerPlan();
    void addTrendOf(VillagerPlan *other, s16 *p);
    void addPendingScore(u8 idx, s32 delta);
    BOOL addRandomScores(s16 *p);
    void applyPendingScores(s16 *p);
    static s32 getTrendName(MsgString *out, s32 x);
    s32 finishMovingIn(ClockDateTime *now);
    s32 leaveState0B(VillagerPlan *o);
    s32 finishTrendChange();
    s32 updateTopTrend();
    BOOL isTrendOlderThanWeek(ClockDateTime *now);
    BOOL isTrendOlderThan(ClockDateTime *now, u32 days);
    void enterState0B();
    void startTrendChange();
    BOOL hasState2Flag();
    s32 getStateGroup();
    void setState(u32 v);
    u32 getState();
    void rollTrend(const u8 *trend, s32 flag);
    BOOL isValidState();
    BOOL hasTrend();
    void clear();
};

class VillagerPlanBlock {
public:
    /* 0x00 */ VillagerPlan plan;
    /* 0x24 */ PlanErrand errand;
};

#endif
