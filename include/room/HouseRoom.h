#ifndef ROOM_HOUSEROOM_H
#define ROOM_HOUSEROOM_H

#include "types.h"
#include "room/RoomFtrState.h"

struct MapBlockEntry;

class RoomItemGrid {
public:
    u16 items[0x100];
    RoomItemGrid();
    ~RoomItemGrid();
    RoomItemGrid *getGrid();
    void clear();
};

class HouseRoom {
public:
    /* 0x000 */ RoomItemGrid layers[2];
    /* 0x400 */ RoomFtrState ftrState;
    /* 0x448 */ u16 wallpaper;
    /* 0x44a */ u16 carpet;
    /* 0x44c */ u16 song;
    /* 0x44e */ u8 wallpaperDesignKey : 1;
    /* 0x44e */ u8 carpetDesignKey : 1;
    HouseRoom();
    ~HouseRoom();
    void func_02060878_dummy();
    MapBlockEntry *buildBlockEntry(void *heap);
    void reset(s32 i);
    void setSong(u16 *src);
    u16 *getSong();
    void setCarpet(u16 *src, u32 flag);
    void setWallpaper(u16 *src, u32 flag);
    u16 *getCarpet(s32 *out);
    u16 *getWallpaper(s32 *out);
    RoomFtrState *getFtrState();
};

#endif
