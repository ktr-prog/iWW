#ifndef TOWN_SCENEMAPMODULE_H
#define TOWN_SCENEMAPMODULE_H

#include "types.h"
#include "sys/ProcBase.h"
#include "town/MapBlockEntry.h"


class SceneMapModule : public GameProc {
public:
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();

    /* 0x50 */ u16 moduleParam;
    /* 0x52 */ u16 pad_52;
    /* 0x54 */ u16 **ownedGrids;
    /* 0x58 */ s32 numOwnedGrids;

    s32 buildSceneMap(void *heap);
    void getHouseUnk(u32 *out, s32 n);
    void setOwnedGrid(u16 *v, s32 idx);
    void freeOwnedGrids(void *heap);
    void allocOwnedGrids(void *heap);
    MapBlockEntry *buildEntries(u32 *src, s32 n, void *heap);
    u16 *loadLayoutGrid(u32 v, s32 idx, void *heap);
};

#endif
