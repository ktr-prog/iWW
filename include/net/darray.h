#ifndef NET_DARRAY_H
#define NET_DARRAY_H

#include "types.h"


typedef void (*ArrayElementFreeFn)(void *);
typedef s32 (*ArrayCompareFn)(void *, void *);
typedef s32 (*GsArrayMapFn)(void *, void *);

struct DArrayImplementation {
    /* 0x00 */ s32 count;
    /* 0x04 */ s32 capacity;
    /* 0x08 */ s32 elemsize;
    /* 0x0c */ s32 growby;
    /* 0x10 */ ArrayElementFreeFn elemfreefn;
    /* 0x14 */ u8 *list;
};

#endif
