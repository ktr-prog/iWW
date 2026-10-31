#ifndef SAVE_CONTESTRECORD_H
#define SAVE_CONTESTRECORD_H

#include "types.h"
#include "npc/VillagerId.h"
#include "save/Unk_02085810_Rec.h"

class ContestRecord {
public:
    u32 getSize();
    void setSize(s32 v);
    void setVotedVillager(VillagerId *src);
    VillagerId *getVotedVillager();
    void clearVotedVillager();
    VillagerId *getHolderVillager();
    void setHolderVillager(VillagerId *src);
    void setHolderPlayer(Unk_02085810_Base *src);
    void setKind(u32 v);
    void resetToday();
    void clear();
    void postResultNotice();
    void sendResultLetters();
    void *getHolderPlayer();
    ContestRecord *destruct();
    ContestRecord *construct();

    /* 0x00 */ Unk_02085810_Base holderPlayer;
    /* 0x16 */ VillagerId holderVillager;
    /* 0x22 */ VillagerId votedVillager;
    /* 0x2e */ u16 item;
    /* 0x30 */ s32 size;
    /* 0x34 */ u8 dateDay;
    /* 0x35 */ u8 dateMonth;
    /* 0x36 */ u8 dateYear;
    /* 0x37 */ u8 kind;
};

#endif
