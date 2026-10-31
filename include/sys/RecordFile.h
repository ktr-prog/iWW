#ifndef SYS_RECORDFILE_H
#define SYS_RECORDFILE_H

#include "types.h"
#include "nitro/fs.h"

class RecordFile {
public:
    RecordFile();
    ~RecordFile();
    void loadPage(u32 idx);
    u8 *getRecord(u32 idx);
    void close();
    void freeAll();
    void loadAll();
    BOOL open(void *path, s32 size, s32 count);

    /* 0x00 */ FSFileID fileId;
    /* 0x08 */ s32 recordSize;
    /* 0x0c */ s32 recordCount;
    /* 0x10 */ u8 *data;
    /* 0x14 */ s32 pageIndex;
    /* 0x18 */ u8 *pageBuf;
};

#endif
