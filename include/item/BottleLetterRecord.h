#ifndef ITEM_BOTTLELETTERRECORD_H
#define ITEM_BOTTLELETTERRECORD_H

#include "types.h"
#include "item/Letter.h"

class BottleLetterRecord : public Letter {
public:
    s32 pickUnusedMessage();
    void clearUsedMessages();
    BOOL isMessageUsed(s32 i);
    void setMessageUsed(s32 i);
    void clearRecord();

    /* 0xf4 */ u8 usedMessageBits[5];
};

static_assert(sizeof(BottleLetterRecord) == 0xfc, "BottleLetterRecord: SaveData::bottleLetter");

#endif
