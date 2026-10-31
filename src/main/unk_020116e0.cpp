#include "types.h"
#include "gfx/HudObjGfx.h"
#include "proto/autoload_2/unk_02119434.h"
#include "proto/main/unk_020116e0.h"
#include "proto/main/unk_02038474.h"
#include "proto/main/unk_0208eeac.h"



extern "C" {
s32 Scene_GetCurrent(void);
void MI_CpuFill8(void *dst, u32 v, u32 n);

extern const u8 sSceneHudKinds[0x34];
}

HudObjGfx sHudObjGfx;

extern "C" const u8 sSceneHudKinds[0x34] = {
    1, 2, 2, 2, 2, 2, 0, 1, 1, 3, 3, 1, 0, 0, 0, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2,
};

HudObjGfx::HudObjGfx() {
    paletteBuf = NULL;
    charBuf = NULL;
    pendingCameraButtonScreens = 3;
    msgUiActive = 0;
    countdownVariant = 0;
    MI_CpuFill8(&cameraButtonChars, 0, 0x200);
}

HudObjGfx::~HudObjGfx() {
    freePalette();
    freeChars();
}

extern "C" void HudObjGfx_LoadForScene(void) {
    sHudObjGfx.loadForScene(0);
    ChatBalloon_RefreshLabelsUnk();
}

extern "C" void HudObjGfx_LoadForSceneSub(void) {
    sHudObjGfx.loadForScene(2);
    ChatBalloon_RefreshLabelsUnk();
}

extern "C" void HudObjGfx_LoadKind(u32 a, u32 b) { sHudObjGfx.loadKind(a, b); }

extern "C" void HudObjGfx_LoadCameraButton(u32 a, u32 b, u32 c) { sHudObjGfx.loadCameraButton(a, b, c); }

extern "C" void HudObjGfx_SetCountdownVariant(u8 v) { sHudObjGfx.countdownVariant = v; }

extern "C" u8 HudObjGfx_GetCountdownVariant(void) { return sHudObjGfx.countdownVariant; }

extern "C" void HudObjGfx_LoadLinkIcon(u32 a) { sHudObjGfx.loadLinkIcon(a); }

extern "C" void HudObjGfx_LoadSlideIcon(u32 a) { sHudObjGfx.loadSlideIcon(a); }

extern "C" void HudObjGfx_FlushCameraButton(void) {
    HudObjGfx *p = &sHudObjGfx;
    if (sHudObjGfx.pendingCameraButtonScreens != 3) {
        p->uploadCameraButtonChars(p->pendingCameraButtonScreens);
        p->pendingCameraButtonScreens = 3;
    }
}

extern "C" s32 Hud_GetSceneHudKind(void) { return sSceneHudKinds[Scene_GetCurrent()]; }

extern "C" u8 HudObjGfx_IsMsgUiActive(void) { return sHudObjGfx.msgUiActive; }

extern "C" void HudObjGfx_SetMsgUiActive(void) { sHudObjGfx.msgUiActive = 1; }

extern "C" void HudObjGfx_ClearMsgUiActive(void) { sHudObjGfx.msgUiActive = 0; }

void HudObjGfx::loadForScene(u32 a) {
    HudObjGfx *p = &sHudObjGfx;
    HudObjGfx_InitFile(p);
    if (p->loadPalette(4)) p->uploadPalette(a);
    p->freePalette();
    if (p->loadChars()) p->uploadChars(a);
    p->freeChars();
    if (Hud_GetSceneHudKind() == 2) {
        if (InputMode_IsTouch()) loadCameraButton(1, 0, a);
    }
}

void HudObjGfx::loadKind(u32 a, u32 b) {
    HudObjGfx *p = &sHudObjGfx;
    HudObjGfx_InitFile(p);
    if (p->loadPalette(a)) p->uploadPalette(b);
    p->freePalette();
    if (p->loadKindChars(a)) p->uploadKindChars(b);
    p->releaseKindChars();
    if (a == 2 || (a == 4 && Hud_GetSceneHudKind() == 2)) {
        if (InputMode_IsTouch()) loadCameraButton(1, 0, b);
    }
}

void HudObjGfx::loadCameraButton(u32 a, u32 b, u32 c) {
    s32 r;
    HudObjGfx_InitFile(&sHudObjGfx);
    r = sHudObjGfx.loadCameraButtonChars(a);
    if (b != 0) {
        pendingCameraButtonScreens = c;
    } else if (r != 0) {
        sHudObjGfx.uploadCameraButtonChars(c);
    }
}

void HudObjGfx::loadLinkIcon(u32 v) {
    HudObjGfx *p = &sHudObjGfx;
    HudObjGfx_InitFile(p);
    if (p->loadLinkIconChars(v)) p->uploadLinkIconChars();
    releaseLinkIconChars();
}

void HudObjGfx::loadSlideIcon(u32 v) {
    HudObjGfx *p = &sHudObjGfx;
    HudObjGfx_InitFile(p);
    if (p->loadSlideIconChars(v)) p->uploadSlideIconChars();
    releaseSlideIconChars();
}

extern "C" void HudObjGfx_InitFile(HudObjGfx *p) { FS_InitFile(&p->file); }
