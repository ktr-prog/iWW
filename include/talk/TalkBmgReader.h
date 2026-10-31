#ifndef TALK_TALKBMGREADER_H
#define TALK_TALKBMGREADER_H

#include "types.h"
#include "talk/BmgReader.h"

class TalkBmgReader : public BmgReader {
public:
    TalkBmgReader();
    virtual ~TalkBmgReader();
    virtual u8 *getBuffer();
    virtual u32 getBufferSize();
    void clear();

    /* 0xa4 */ u8 buffer[0x800];
};

#endif
