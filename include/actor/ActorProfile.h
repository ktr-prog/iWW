#ifndef ACTOR_ACTORPROFILE_H
#define ACTOR_ACTORPROFILE_H

#include "types.h"
#include "sys/ProcProfile.h"

struct ActorProfile {
    /* 0x00 */ ProcProfile proc;
    /* 0x08 */ u32 actorFlags;
    /* 0x0c */ u32 cullHeight;
    /* 0x10 */ u32 cullRadius;
    /* 0x14 */ u32 cullDepth;
};

#endif
