#ifndef NPC_NPCOBSTACLEPROBE_H
#define NPC_NPCOBSTACLEPROBE_H

#include "types.h"


class Character;

class NpcObstacleProbe {
public:
    /* 0x0 */ u8 blockedBits;
    /* 0x1 */ u8 pad_01;

    NpcObstacleProbe();
    void probe(Character *scene);
    void clear();
};

#endif
