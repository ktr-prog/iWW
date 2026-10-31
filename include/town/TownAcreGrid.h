#ifndef TOWN_TOWNACREGRID_H
#define TOWN_TOWNACREGRID_H

#include "types.h"
#include "town/TownAcreCell.h"
#include "sys/RecordFile.h"

class TownAcreGrid {
public:
    void loadCandidate(s32 seed);
    BOOL setBorder();
    BOOL placeRiverVariant();
    BOOL placeFacilities(u32 mode);
    BOOL placeNextTo(s32 a, s32 b);
    BOOL placeOnRandomGrass(s32 val);
    TownAcreCell *getCell(s32 x, s32 y);
    BOOL hasPond();
    BOOL assignAcreIds();

    /* 0x000 */ TownAcreCell cells[36];
    /* 0x120 */ RecordFile candidates;
};

class TownAcreGenerator {
public:
    TownAcreGenerator();
    ~TownAcreGenerator();

    void writeAcreIds(u8 *out);
    u32 getTotalArchiveSize();
    BOOL generate(s32 v);
    void closeCandidates();
    BOOL openCandidates();

    /* 0x000 */ TownAcreCell cells[0x24];
    /* 0x120 */ RecordFile candidates;
};

#endif
