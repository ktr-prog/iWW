#ifndef PLAYER_PLAYERSPNPCRECORD_H
#define PLAYER_PLAYERSPNPCRECORD_H

#include "types.h"


class PlayerSpNpcRecord {
public:
    void sendInsuranceLetters();
    BOOL sendInsuranceLetter(s32 idx, u16 *v);
    void addInsuranceClaim();
    u32 getInsuranceClaims();
    void clearFestivalGift();
    void setFestivalGift();
    u32 hasFestivalGift();
    void resetAcornCount();
    void resetFireworksGiven();
    void addFireworksGiven();
    u32 getFireworksGiven();
    void setEnteredBugOff(s32 v);
    u32 hasEnteredBugOff();
    void setEnteredFishingTourney(s32 v);
    u32 hasEnteredFishingTourney();
    void addStyleScore(u32 v);
    u32 getStyleScore();
    void addResetCount();
    u32 getResetCount();
    void advanceAcornPrizeStep();
    u32 getAcornPrizeStep();
    void addAcornsDelivered(s32 v);
    u32 getAcornsDelivered();
    void addHaircutCount(u32 v);
    u32 getHaircutCount();
    void setCafeVisits(u32 v);
    u32 getCafeVisits();
    void setSableTalkCount(u32 v);
    u32 getSableTalkCount();
    void stampArbeitDate();
    u8 *getArbeitDate();

    /* 0x00 */ u8 serviceDates[8];
    /* 0x08 */ u8 sableTalkCount;
    /* 0x09 */ u8 cafeVisits;
    /* 0x0a */ u8 haircutCount;
    /* 0x0b */ u8 acornsDelivered;
    /* 0x0c */ u8 acornPrizeStep;
    /* 0x0d */ u8 resetCount;
    /* 0x0e */ u8 styleScore;
    /* 0x0f */ u8 insuranceClaims;
    /* 0x10 */ union {
        u8 unk_10;
        struct {
            u8 unk_10_0 : 1;
            u8 unk_10_1 : 1;
            u8 unk_10_2 : 4;
            u8 unk_10_6 : 1;
            u8 unk_10_7 : 1;
        };
    };
};

#endif
