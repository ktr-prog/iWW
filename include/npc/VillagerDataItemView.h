#ifndef NPC_VILLAGERDATAITEMVIEW_H
#define NPC_VILLAGERDATAITEMVIEW_H

#include "types.h"

class VillagerDataItemView;

typedef BOOL (VillagerDataItemView::*Unk_0207ed1c_Fn)(u16 *);

struct PlacedFurnitureItem {
    u16 v;
    PlacedFurnitureItem() {}
};

class VillagerDataItemView {
public:
    /* 0x000 */ u8 unk_000[0x6ac];
    /* 0x6ac */ u16 furniture[10];
    /* 0x6c0 */ u8 unk_6c0[0x14];
    /* 0x6d4 */ u8 movedFromTown[0x14];
    /* 0x6e8 */ u8 housePos[2];
    /* 0x6ea */ u8 unk_6ea[8];
    /* 0x6f2 */ u8 roomLayout;

    BOOL tryPlaceFossil(u16 *item, s32 mode, s32 type, u8 a, u8 b);
    s32 getFossilPartIndex(u16 *item);
    s32 freeSlotInRange(s32 mode, s32 type, u8 a, u8 c);
    s32 pickNonTrendSlot(s32 type, s32 lo, s32 hi);
    BOOL matchesTrend(u16 *p, s32 type);
    Unk_0207ed1c_Fn getTrendFilter(s32 type);
    BOOL isTasteFurniture(u16 *item);
    BOOL isShirtItem(u16 *p);
    BOOL isFossilItem(u16 *p);
    BOOL isFishItem(u16 *p);
    BOOL isInsectItem(u16 *p);
    s32 findCheapestSlot(s32 lo, s32 hi);
    s32 pickEmptySlot(s32 lo, s32 hi);
    BOOL getSlotRange(s32 *lo, s32 *hi, s32 mode, s32 type, u8 flag);
    u16 *getFurniture();
    PlacedFurnitureItem getFurnitureAt(s32 idx);
    s32 getSlotFromLayoutCode(u16 *p);
    BOOL isValidFurnitureIndex(s32 idx);
    s32 getInfo28Item();
    BOOL getRoomLayout(s32 *o1, s32 *o2);
    void placeHouseMarker();
    void setHousePos(u8 *p);
    u8 *getHousePos();
    s32 hasHousePos();
    void clearHousePos();
    u8 *getMovedFromTownId();
    void setGreetingFor(void *a, s32 n, void *c);
    BOOL getGreetingFor(void *a, void *c);
    void setComplimentFor(void *a, s32 n, void *c);
    void getComplimentFor(void *a, void *c);
};

#endif
