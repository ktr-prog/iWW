#ifndef GFX_BGMODELCACHE_H
#define GFX_BGMODELCACHE_H

#include "types.h"

struct BgAcreModel {
    /* 0x00 */ s32 acreId;
    /* 0x04 */ void *arc;
    /* 0x08 */ void *mdl;
    /* 0x0c */ void *bcl;
    /* 0x10 */ void *bsd;
    /* 0x14 */ void *jntAnm;
    /* 0x18 */ void *matAnm;
    /* 0x1c */ void *texSrtAnm;
    /* 0x20 */ void *tex;
    /* 0x24 */ u32 arcSize;
    /* 0x28 */ void *mgt;
    /* 0x2c */ s32 mgtCount;
};

struct BgAcreBcl {
    /* 0x0 */ s32 acreId;
    /* 0x4 */ void *bcl;
};

struct BgModelCache {
    /* 0x000 */ BgAcreModel acres[31];
    /* 0x5d0 */ BgAcreBcl bclCache[9];
    /* 0x618 */ u8 withAnims;
    /* 0x619 */ u8 pad_619[3];
    /* 0x61c */ u32 heapSize;
    /* 0x620 */ u32 unk_620;
    /* 0x624 */ u32 unk_624;
    /* 0x628 */ u32 unk_628;
    /* 0x62c */ u32 unk_62c;
    /* 0x630 */ void *groundTex;
    /* 0x634 */ void *groundMatAnm;
    /* 0x638 */ void *groundTexSrtAnm;
    /* 0x63c */ void *riverPatAnm;
    /* 0x640 */ void *riverPatTex;
    /* 0x644 */ void *beBPatAnm;
    /* 0x648 */ void *beBPatTex;

    BgModelCache();
    ~BgModelCache();
    BOOL setup(u32 flag);
    void clearEntries();
    void *getBeBPatTex();
    void *getBeBPatAnm();
    void *getRiverPatTex();
    void *getRiverPatAnm();
    void *getGroundTexSrtAnm();
    void *getGroundMatAnm();
    void *getGroundTex();
    BOOL reset();
    BgAcreModel *getAcre(s32 id);
    void *getAcreBcl(s32 id);
    void loadGroundAnims();
    void loadGroundTexture();
};

#endif
