#ifndef SAVE_BACKUP_H
#define SAVE_BACKUP_H

#include "types.h"

struct Backup {
    /* 0x00 */ u32 totalSize;
    /* 0x04 */ s32 lockId;
    /* 0x08 */ u8 unk_08;
    Backup() {
        totalSize = 0;
        lockId = -3;
    }
};

#endif
