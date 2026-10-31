#ifndef FIELD_UNK_OV003_02217B78_ENT_H
#define FIELD_UNK_OV003_02217B78_ENT_H

#include "types.h"

struct NNSG3dResMdl;

struct Unk_ov003_02217b78_Ent {
    s32 acreId;
    void *arc;
    /* 0x08 */ NNSG3dResMdl *modelRes;
};

#endif
