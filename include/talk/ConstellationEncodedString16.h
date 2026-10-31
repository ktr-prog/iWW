#ifndef TALK_CONSTELLATIONENCODEDSTRING16_H
#define TALK_CONSTELLATIONENCODEDSTRING16_H

#include "types.h"
#include "talk/EncodedString.h"

class ConstellationEncodedString16 : public EncodedString {
public:
    ConstellationEncodedString16();
    virtual ~ConstellationEncodedString16();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x0e */ u8 text[0x10];
};

#endif
