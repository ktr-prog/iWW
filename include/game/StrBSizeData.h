#ifndef GAME_STRBSIZEDATA_H
#define GAME_STRBSIZEDATA_H

#include "types.h"

class StrBSizeData {
public:
    void getSolidBounds(s32 *outX, s32 *outY, s32 *outW, s32 *outH);
    BOOL getTriangle(s32 *a, s32 *b, s32 *c, u32 idx);
    u32 getTriangleCount();
    BOOL getSolidUnit(s32 *a, s32 *b, s32 *c, u32 idx);
    BOOL getFootprintUnit(s32 *a, s32 *b, u32 idx);
    BOOL getClearUnit(s32 *a, s32 *b, u32 idx);
    BOOL getLightUnit(s32 *a, s32 *b, u32 idx);
    u32 getFootprintUnitCount();
    u32 getSolidUnitCount();
    u32 getFloorUnitCount();
    u32 getClearUnitCount();
    u32 getLightUnitCount();
};

#endif
