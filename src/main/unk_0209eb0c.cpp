#include "types.h"
#include "save/SaveRecord4.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0209eb0c.h"


extern "C" {
}


class SaveChecksum {
public:
    u16 get();
    void set(u16 v);
    u16 checksum;
};

void SaveRecord4::construct() {}

void SaveRecord4::destruct() {}

void SaveRecord4::setStateValid() {
    unk_02 = 2;
}

void SaveRecord4::clearState() {
    unk_02 = 0;
}

void SaveRecord4::markInterrupted() {
    unk_02 = 0x1c;
}

void SaveRecord4::setStateValidAlt() {
    unk_02 = 2;
}

BOOL SaveRecord4::isStateValid() {
    if (unk_02 == 2) {
        return TRUE;
    }
    return FALSE;
}

BOOL SaveRecord4::isStateUnset() {
    if (unk_02 == 2 || unk_02 == 0x1c) {
        return FALSE;
    }
    return TRUE;
}

void SaveRecord4::newStamp() {
    u8 old = unk_03;
    unk_03 = Random_GlobalBelow(0xff);
    if (unk_03 == old) {
        if (unk_03 < 0xff) {
            unk_03++;
        } else {
            unk_03--;
        }
    }
}

void SaveRecord4::setStamp(u8 v) {
    unk_03 = v;
}

u8 SaveRecord4::getStamp() {
    return unk_03;
}

void SaveChecksum::set(u16 v) {
    checksum = v;
}

u16 SaveChecksum::get() {
    return checksum;
}
