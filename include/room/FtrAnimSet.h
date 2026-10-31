#ifndef ROOM_FTRANIMSET_H
#define ROOM_FTRANIMSET_H

#include "types.h"

struct NNSG3dResAnmCommon;

struct FtrAnimSet {
    inline FtrAnimSet() { clear(); }
    ~FtrAnimSet();
    void *getTexCopy();
    NNSG3dResAnmCommon *getBtp(u32 i);
    NNSG3dResAnmCommon *getBta(u32 i);
    NNSG3dResAnmCommon *getBva(u32 i);
    NNSG3dResAnmCommon *getBma(u32 i);
    NNSG3dResAnmCommon *getBca(u32 i);
    void setTexCopy(void *v);
    void setBtp(void *v, u32 i);
    void setBta(void *v, u32 i);
    void setBva(void *v, u32 i);
    void setBma(void *v, u32 i);
    void setBca(void *v, u32 i);
    void clear();

    /* 0x00 */ void *bca[2];
    /* 0x08 */ void *bma[2];
    /* 0x10 */ void *bva[2];
    /* 0x18 */ void *bta[2];
    /* 0x20 */ void *btp[2];
    /* 0x28 */ void *texCopy;
};

#endif
