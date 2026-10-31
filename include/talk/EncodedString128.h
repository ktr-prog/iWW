#ifndef TALK_ENCODEDSTRING128_H
#define TALK_ENCODEDSTRING128_H

#include "types.h"
#include "talk/EncodedString.h"

class EncodedString128 : public EncodedString {
public:
    EncodedString128();
    virtual ~EncodedString128();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x0e */ u8 text[0x82];
};

#endif
