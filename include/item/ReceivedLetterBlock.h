#ifndef ITEM_RECEIVEDLETTERBLOCK_H
#define ITEM_RECEIVEDLETTERBLOCK_H

#include "types.h"
#include "item/Letter.h"

class ReceivedLetterBlock {
public:
    ReceivedLetterBlock();
    ~ReceivedLetterBlock();

    /* 0x00 */ Letter letter;
    /* 0xf4 */ u8 unk_f4[4];
    /* 0xf8 */ u8 exchangeKind;
    /* 0xf9 */ u8 pad_f9[3];
};

static_assert(sizeof(ReceivedLetterBlock) == 0xfc, "ReceivedLetterBlock: DS layout");

#endif
