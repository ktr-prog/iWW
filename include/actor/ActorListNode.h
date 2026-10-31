#ifndef ACTOR_ACTORLISTNODE_H
#define ACTOR_ACTORLISTNODE_H

#include "types.h"


struct ActorListNode {
    /* 0x00 */ void *prev;
    /* 0x04 */ void *next;
    /* 0x08 */ void *owner;
};

#endif
