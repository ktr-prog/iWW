#ifndef GAME_TURNIPMARKET_H
#define GAME_TURNIPMARKET_H

#include "types.h"

struct TurnipMarket {
    u8 weekStartDay, weekStartMonth, weekStartYear, unk_03, purchaseDay, purchaseMonth, purchaseYear, unk_07;
    u16 peakPrice;
    u8 prices[14];
    u8 pattern;
    void setPurchaseDate(void *src);
    void checkTurnipExpiry();
    void setWeekDate(void *src);
    void updateDay(s32 d);
    void spoilOnReset();
    u16 getPrice();
    void generateWeek(s32 flag);
    s32 rollPeakPrice();
    void generateSmallSpike();
    u8 calcHighPrice();
    u8 calcMidPrice();
    u8 calcLowPrice();
    void fillDecreasing(s32 i, s32 n);
    u8 calcPrice(s32 k, s32 z);
    void init();
    void clear();
};

#endif
