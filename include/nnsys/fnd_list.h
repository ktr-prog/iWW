#ifndef NNSYS_FND_LIST_H
#define NNSYS_FND_LIST_H

#include "types.h"

typedef struct NNSFndLink {
    void *prev;
    void *next;
} NNSFndLink;

typedef struct NNSFndList {
    void *head;
    void *tail;
    u16 num;
    u16 offset;
} NNSFndList;

#endif
