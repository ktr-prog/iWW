#ifndef GFX_HUDOBJGFX_H
#define GFX_HUDOBJGFX_H

#include "types.h"
#include "nitro/fs.h"

class HudObjGfxIo {
public:
    void releaseSlideIconChars();
    void uploadSlideIconChars();
    BOOL loadSlideIconChars(s32 alt);
    void releaseLinkIconChars();
    void uploadLinkIconChars();
    BOOL loadLinkIconChars(s32 alt);
    void uploadCameraButtonChars(s32 which);
    BOOL loadCameraButtonChars(s32 alt);
    void uploadKindChars(s32 which);
    void releaseKindChars();
    BOOL loadKindChars(s32 k);
    void uploadChars(s32 which);
    void uploadPalette(s32 which);
    void freeChars();
    void freePalette();

    /* 0x00 */ FSFile file;
    /* 0x48 */ u8 *paletteBuf;
    /* 0x4c */ u8 *charBuf;
    /* 0x50 */ u8 cameraButtonChars[0x200];
};

struct HudObjGfx : public HudObjGfxIo {
    /* 0x250 */ s32 pendingCameraButtonScreens;
    /* 0x254 */ u8 msgUiActive;
    /* 0x255 */ u8 countdownVariant;

    HudObjGfx();
    ~HudObjGfx();
    BOOL loadChars();
    BOOL loadPalette(s32 mode);
    const char *getCharPath(s32 mode);
    const char *getPalettePath(s32 mode);
    void loadSlideIcon(u32 v);
    void loadLinkIcon(u32 v);
    void loadCameraButton(u32 a, u32 b, u32 c);
    void loadKind(u32 a, u32 b);
    void loadForScene(u32 a);
};

#endif
