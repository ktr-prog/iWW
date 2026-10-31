#ifndef SYS_DTORENTRY_H
#define SYS_DTORENTRY_H

#include "types.h"

struct DtorEntry {
    /* 0x0 */ struct DtorEntry *next;
    /* 0x4 */ void (*dtor)(void *);
    /* 0x8 */ void *obj;
};

#endif
