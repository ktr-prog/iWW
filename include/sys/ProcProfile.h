#ifndef SYS_PROCPROFILE_H
#define SYS_PROCPROFILE_H

#include "types.h"

struct ProcProfile {
    /* 0x00 */ void *(*create)();
    /* 0x04 */ u16 executePriority;
    /* 0x06 */ u16 drawPriority;
};

#endif
