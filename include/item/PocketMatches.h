#ifndef ITEM_POCKETMATCHES_H
#define ITEM_POCKETMATCHES_H

#include "types.h"


struct PocketMatches {
    /* 0x00 */ u16 pocketMask;
    /* 0x02 */ u8 count;
};
#ifndef __cplusplus
typedef struct PocketMatches PocketMatches;
#endif

#endif
