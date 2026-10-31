#ifndef SAVE_SAVECHECKSUM_H
#define SAVE_SAVECHECKSUM_H

#include "types.h"

class SaveChecksum {
public:
    u16 get();
    void set(u16 v);
    u16 checksum;
};

#endif
