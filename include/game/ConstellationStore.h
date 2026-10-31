#ifndef GAME_CONSTELLATIONSTORE_H
#define GAME_CONSTELLATIONSTORE_H

#include "types.h"
#include "game/ConstellationRecord.h"

class ConstellationStore {
public:
    ConstellationStore();
    ~ConstellationStore();
    /* 0x000 */ ConstellationRecord records[16];
    /* 0x460 */ u16 usedMask;
    /* 0x462 */ u16 newMask;
};

static_assert(sizeof(ConstellationStore) == 0x464, "ConstellationStore: the save layout");

#endif
