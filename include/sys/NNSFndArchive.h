#ifndef SYS_NNSFNDARCHIVE_H
#define SYS_NNSFNDARCHIVE_H

#include "types.h"

#include "nitro/fs.h"

struct NNSFndArchive {
    /* 0x00 */ FSArc arc;
    /* 0x5c */ void *arcBinary;
    /* 0x60 */ void *fatData;
    /* 0x64 */ void *fileImage;
};

#endif
