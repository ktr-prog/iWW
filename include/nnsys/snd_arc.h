#ifndef NNSYS_SND_ARC_H
#define NNSYS_SND_ARC_H

#include "types.h"
#include "nitro/fs.h"

struct Fat;
typedef struct NNSSndArc {
    u8 sig[4];
    u32 magic;
    u32 fileSize;
    u16 hdrSize;
    u16 nBlocks;
    u32 symbOff;
    u32 symbSize;
    u32 infoOff;
    u32 infoSize;
    u32 fatOff;
    u32 fatSize;
    u32 fileOff;
    u32 fileBlkSize;
    s32 fromFile;
    FSFile file;
    FSFileID id;
    struct Fat *fat;
    u8 *symb;
    u8 *info;
} NNSSndArc;

#endif
