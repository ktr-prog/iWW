#ifndef GFX_ABALLOBJGFX_H
#define GFX_ABALLOBJGFX_H

#include "types.h"
#include "nitro/fs.h"

class AbAllObjGfx {
public:
    AbAllObjGfx();
    ~AbAllObjGfx();
    void uploadChars();
    void uploadPalette();
    void freeChars();
    void freePalette();
    BOOL loadChars();
    BOOL loadPalette();

    /* 0x00 */ FSFile file;
    /* 0x48 */ void *paletteBuf;
    /* 0x4c */ void *charBuf;
};

#endif
