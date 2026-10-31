#ifndef TALK_ARTICLECACHEENTRY_H
#define TALK_ARTICLECACHEENTRY_H

#include "types.h"
#include "talk/MsgString.h"

class ArticleCacheEntry : public MsgString {
public:
    ArticleCacheEntry();
    virtual ~ArticleCacheEntry();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x12 */ u8 text[10];
    /* 0x1c */ u8 isLoaded;
};

#endif
