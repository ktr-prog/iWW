#ifndef NPC_SICKVILLAGERRECORD_H
#define NPC_SICKVILLAGERRECORD_H

#include "types.h"
#include "npc/VillagerId.h"
#include "player/PlayerId.h"
#include "npc/ErrandRecord.h"

struct ClockDate;

class SickVillagerRecord {
public:
    ErrandRecord errand;
    VillagerId villagerId;
    PlayerId visitors[5];
    u8 startDate[4];
    u8 statusDate[4];
    u8 sickDay;
    PlayerId *getTopVisitor();
    BOOL isRecentlyRecovered(ClockDate *d);
    BOOL isRecovered();
    void setTodaysVisitor(PlayerId *e);
    BOOL hasTodaysVisitor();
    BOOL hasVisitor(PlayerId *e);
    PlayerId *getTodaysVisitor();
    PlayerId *getVisitor(u32 i);
    void startSickness(VillagerId *a, u8 *b);
    VillagerId *getVillagerId();
    SickVillagerRecord *destructRecord();
    SickVillagerRecord *constructRecord();
    ErrandRecord *getErrand();
    void resetRecord();
};

#endif
