#ifndef NET_HASHTABLE_H
#define NET_HASHTABLE_H

#include "types.h"
#include "net/darray.h"


typedef s32 (*TableHashFn)(void *, s32);

struct HashImplementation {
    /* 0x00 */ DArrayImplementation **buckets;
    /* 0x04 */ s32 nbuckets;
    /* 0x08 */ ArrayElementFreeFn freefn;
    /* 0x0c */ TableHashFn hashfn;
    /* 0x10 */ ArrayCompareFn compfn;
};

#endif
