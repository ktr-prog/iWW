#ifndef SYS_FNDLIST_H
#define SYS_FNDLIST_H

#include "types.h"

struct FndList {
    /* 0x0 */ void *head;
    /* 0x4 */ void *tail;
    /* 0x8 */ u16 num;
    /* 0xa */ u16 offset;
};

#endif
