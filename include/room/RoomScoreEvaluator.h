#ifndef ROOM_ROOMSCOREEVALUATOR_H
#define ROOM_ROOMSCOREEVALUATOR_H

#include "types.h"

class BlockMap;
class RoomFengShui;

class RoomScoreEvaluator {
public:
    u32 minX;
    u32 minZ;
    u32 maxX;
    u32 maxZ;
    u16 wallpaper;
    u16 carpet;
    void collectLuckyItems(BlockMap *grid);
    s32 calcPenalty(BlockMap *grid, u8 *f1, u8 *f2);
    s32 scoreCollection(BlockMap *grid, s32 *out);
    s32 scoreFlagPairThemes(BlockMap *grid, s32 *out1, s32 *out2);
    s32 scoreColorTheme(BlockMap *grid);
    s32 scoreFengShui(RoomFengShui *o);
    s32 scoreBasePoints(BlockMap *grid);
    void collectUnk06Kinds(BlockMap *grid);
    s32 scoreSets(BlockMap *grid);
    s32 scoreThemes(BlockMap *grid);
    s32 scoreSeries(BlockMap *grid, u32 *out);
};

#endif
