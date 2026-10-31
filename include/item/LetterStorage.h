#ifndef ITEM_LETTERSTORAGE_H
#define ITEM_LETTERSTORAGE_H

#include "types.h"
#include "item/Letter.h"

class LetterStorage {
public:
    void clear();
    Letter *getPage(s32 i);

    /* 0x000 */ Letter letters[75];
};

static_assert(sizeof(LetterStorage) == 75 * 0xf4, "LetterStorage: DS layout");

#endif
