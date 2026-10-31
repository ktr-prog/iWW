#ifndef TALK_BMGREADER_H
#define TALK_BMGREADER_H

#include "types.h"
#include "uptr.h"
#include "nitro/fs.h"

struct BmgInfEntryAttr {
    /* 0x0 */ u32 textOffset;
    /* 0x4 */ u8 attrs[6];
};

struct BmgInfHeader {
    /* 0x00 */ u32 magic;
    /* 0x04 */ u32 size;
    /* 0x08 */ u16 msgCount;
    /* 0x0a */ u16 entrySize;
    /* 0x0c */ u16 groupId;
    /* 0x0e */ u8 defaultColor;
    /* 0x0f */ u8 pad_0f[5];
};

struct BmgDatHeader {
    /* 0x0 */ u32 magic;
    /* 0x4 */ u32 size;
    /* 0x8 */ u32 unk_08;
};

struct BmgFileHeader {
    /* 0x00 */ u32 magic;
    /* 0x04 */ u32 type;
    /* 0x08 */ u32 fileSize;
    /* 0x0c */ u32 sectionCount;
    /* 0x10 */ u8 encoding;
    /* 0x11 */ u8 pad[0xb];
    /* 0x1c */ u32 unk_1c;
};

class BmgReader {
public:
    BmgReader(u8 arg1);
    virtual ~BmgReader();
    virtual u8 *getBuffer() = 0;
    virtual u32 getBufferSize() = 0;

    BOOL readText();
    BOOL readInfEntryWithAttr();
    BOOL readInfEntry();
    BOOL readDatHeader();
    BOOL readInfHeader();
    BOOL readFileHeader();
    void resetState();
    BOOL loadMessage(u8 *arg1);
    void close();
    u8 open(const char *path);

    /* 0x04 */ u8 hasAttributes;
    /* 0x05 */ u8 filePath[0x3f];
    /* 0x44 */ FSFile file;
    /* 0x8c */ u8 isOpen;
    /* 0x8d */ u8 msgIndex;
    /* 0x90 */ u32 entry[3];
    /* 0x9c */ u32 textOffset;
    /* 0xa0 */ u32 textSize;
};

#endif
