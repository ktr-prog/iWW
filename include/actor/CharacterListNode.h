#ifndef ACTOR_CHARACTERLISTNODE_H
#define ACTOR_CHARACTERLISTNODE_H

#include "types.h"


class Character;

struct CharacterListNode {
    /* 0x00 */ u32 prev;
    /* 0x04 */ CharacterListNode *next;
    /* 0x08 */ u32 charId;
    /* 0x0c */ Character *owner;
};

#endif
