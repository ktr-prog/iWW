#ifndef GFX_G3DRESACCESS_H
#define GFX_G3DRESACCESS_H

#include "types.h"

class G3dResAccess {
public:
    u32 findNodeIdx(const char *name);
    u32 getPlttSize(s32 idx);
    void *getPlttData(s32 idx);
    s32 findPlttIdx(const char *name);
    u32 getTexSize(s32 idx);
    void *getTexData(s32 idx);
    s32 findTexIdx(const char *name);
    void *findTexData(const char *name);
    void *findPlttData(const char *name);
    u32 getTexImageOffset(void);
    s32 findMatIdx(const char *name);

    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u32 unk_04;
    /* 0x08 */ u32 unk_08;
    /* 0x0c */ u32 unk_0c[2];
    /* 0x14 */ u32 texDataOffset;
    /* 0x18 */ u8 unk_18[0x18];
    /* 0x30 */ u16 plttDataSize;
    /* 0x32 */ u16 unk_32;
    /* 0x34 */ u16 plttDictOffset;
    /* 0x36 */ u16 unk_36;
    /* 0x38 */ u32 plttDataOffset;
    /* 0x3c */ u8 unk_3c[6];
    /* 0x42 */ u16 texDictEntryOffset;
};

#endif
