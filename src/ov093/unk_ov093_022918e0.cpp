#include "types.h"
#include "host_tick.h"
#include "talk/MsgString.h"
#include "menu/StaffRoll.h"
#include "nitro/io_access.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/ov093/unk_ov093_022918e0.h"

extern "C" {
s8 *Msg_SkipLines(void *a, s32 b);
void MIi_CpuCopy16(void *a, void *b, s32 c);
void MIi_CpuClear16(u32 a, void *b, s32 c);
}

StaffRoll::StaffRoll()
{
}

StaffRoll::~StaffRoll()
{
}

void StaffRoll::init()
{
    flags = 0;
    labelCount = 0;
    Gfx2d_HideLayer(4);
    Gfx2d_HideLayer(0);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
    vu16 *r = (vu16 *)0x400000a;
    IO_W(r, (IO_R(r) & 0x43) | 0x700);
    state = 0;
    loadTemplate();
}

void StaffRoll::update()
{
    s32 v;
    resetLabels();
    switch (state) {
    case 1:
        state = 2;
        Gfx2d_ShowLayer(4);
        Gfx2d_ShowLayer(0);
        Gfx2d_SetLayerOffset(4, 8, -0xc0);
        Gfx2d_SetLayerOffset(0, 8, -0xc0);
        loadTextGraphics();
        break;
    case 2:
        scroll(TRUE);
        break;
    case 3:
        scroll(FALSE);
        Gfx2d_ShowLayer(0);
        Gfx2d_SetMainAlphaBlend(2, 0x21, 0);
        loadLogo();
        state = 5;
        break;
    case 4:
        scroll(FALSE);
        Gfx2d_ShowLayer(0);
        loadLogo();
        state = 6;
        break;
    case 5: {
        scroll(FALSE);
        u32 c = logoTimer;
        if (c < 0x48) {
            if (c >= 0x10) {
                if (c < 0x38) {
                    c = 0x10;
                } else {
                    c = 0x48 - c;
                }
            }
            logoTimer += TICK_STEP_ENDS() ? 1 : 0;
            Gfx2d_SetMainAlphaBlend(2, 0x21, c);
        } else {
            hide();
            Gfx2d_ResetMainBlend();
            setFlags(8);
        }
        break;
    }
    case 6:
        scroll(FALSE);
        logoScrollPos = logoScrollPos + logoScrollSpeed;
        v = logoScrollPos >> 12;
        if (v >= 0) {
            v = 0;
            logoTimer = 0x10;
            Gfx2d_DisableMainWindows(1);
            Gfx2d_SetMainWinOutPlanes(0x1f);
            state = 5;
        } else {
            Gfx2d_SetWindowRect(0, 0, -v, 0xfe, 0xbf);
        }
        Gfx2d_SetLayerOffset(0, 0, v);
        break;
    }
}

void StaffRoll::uploadScreens()
{
    if (layer4.testFlags(2)) {
        if (screenTasks[0].requestScreen(layer4.screen, 4, 0x800, 0)) {
            layer4.clearFlags(2);
        }
    }
    if (layer0.testFlags(2)) {
        if (screenTasks[1].requestScreen(layer0.screen, 0, 0x800, 0)) {
            layer0.clearFlags(2);
        }
    }
}

void StaffRoll::stop()
{
    hide();
    resetLabels();
}

void StaffRoll::loadTemplate()
{
    File_LoadToBuffer("menu/staff/bg.bsc", templateScreen, 0x800);
}

void StaffRoll::loadTextGraphics()
{
    void *h = gCurrentHeap;
    Gfx2d_LoadPaletteFile(sStaffRollPalettePath, h, 4, 1, 1, 3);
    Gfx2d_LoadPaletteFile(sStaffRollPalettePath, h, 0, 1, 1, 3);
    Gfx2d_LoadCharFile(sStaffRollLogoCharPath, h, 4, 0x10, 0x10, 0x10);
    Gfx2d_LoadCharFile(sStaffRollLogoCharPath, h, 0, 0x10, 0x10, 0x10);
}

void StaffRoll::start(s32 a)
{
    scrollSpeed = a;
    logoScrollSpeed = 0x2000;
    scrollPos = 0;
    layer0.reset();
    layer4.reset();
    MIi_CpuClear16(templateScreen[0], layer0.screen, 0x800);
    MIi_CpuClear16(templateScreen[0], layer4.screen, 0x800);
    state = 1;
}

void StaffRoll::hide()
{
    Gfx2d_HideLayer(4);
    Gfx2d_HideLayer(0);
    state = 0;
}

void StaffRoll::startLogo()
{
    Gfx2d_HideLayer(0);
    s32 v = Gfx2d_GetMainPlanes();
    vu32 *r = (vu32 *)0x4000000;
    IO_W(r, (IO_R(r) & ~0x1f00) | (v << 8));
    Gfx2d_EnableMainWindows(1);
    Gfx2d_SetMainWin0Planes(0x1f);
    Gfx2d_SetMainWinOutPlanes(0x1d);
    Gfx2d_SetWindowRect(0, 0, 0x78, 0xfe, 0xbf);
    Gfx2d_SetLayerOffset(0, 0, -0x78);
    state = 4;
    logoTimer = 0;
    logoScrollPos = 0xfff88000;
}

BOOL StaffRoll::isFinished()
{
    return testFlags(8);
}

void StaffRoll::scrollLayer(s32 which, s32 y)
{
    StaffRollLayer *s;
    if (y >= 0) {
        s32 lim = (y >> 3) + 1;
        if (which == 4) {
            s = &layer4;
        } else {
            s = &layer0;
        }
        for (; lim > s->rowCount;) {
            fillNextRow(which, s);
            s->setFlags(2);
        }
        Gfx2d_SetLayerOffset(which, 8, y - 0xc0);
    }
}

void StaffRoll::clearRow(u8 *dst, u32 row)
{
    MIi_CpuClear16(templateScreen[0], dst + row * 0x40, 0x40);
}

void StaffRoll::copyTemplateRow(u8 *src, u32 dstRow, u32 srcRow)
{
    MIi_CpuCopy16((u8 *)templateScreen + dstRow * 0x40, src + srcRow * 0x40, 0x40);
}

s8 *StaffRoll::getLine(s32 i)
{
    s32 q = i / 6;
    u8 b = q;
    String_Load(&staffText, &b, "st_staffroll");
    return Msg_SkipLines(staffText.text, i - q * 6);
}

void StaffRoll::fillNextRow(s32 a, StaffRollLayer *s)
{
    s32 t = s->lineIndex;
    if (t < 0) {
        s->lineIndex = 0;
        s->rowCount = 0;
        s->textSlot = 0;
    } else if (t >= 0xde) {
        if (s->blankLines < 0xd) {
            s->blankLines++;
        } else {
            s->setFlags(4);
        }
        clearRow(s->screen, s->rowCount & 0x1f);
        s->rowCount = s->rowCount + 1;
        return;
    }
    if (s->textSlot >= 0x19) {
        s->textSlot = 0;
    }
    s8 *p = getLine(s->lineIndex);
    BOOL end;
    if (p == NULL) {
        end = TRUE;
    } else {
        end = FALSE;
    }
    if (!end) {
        s32 c = *p;
        if (c == 0xa || c == 0) {
            end = TRUE;
            s->setFlags(1);
        }
    }
    if (end) {
        s32 i;
        for (i = 0; i < 2; i++) {
            clearRow(s->screen, s->rowCount & 0x1f);
            s->rowCount = s->rowCount + 1;
        }
        s->lineIndex = s->lineIndex + 1;
        if (s->blankLines < 0xd) {
            s->blankLines++;
        } else {
            s->setFlags(4);
        }
    } else {
        s->blankLines = 0;
        if (p[0] == 0x20 && p[1] == 0xa) {
            s->clearFlags(1);
        }
        if (s->testFlags(1)) {
            s->clearFlags(1);
            copyTemplateRow(s->screen, s->textSlot, s->rowCount & 0x1f);
            LabelString *e = allocLabel();
            ((MsgString *)e)->setLine((u8 *)p);
            e->createSmallLabel(a, s->textSlot * 16 + 0x11, 0x10, 1, 0, 0);
            e->redrawAligned(0, 0);
            s->textSlot = s->textSlot + 1;
            s->lineIndex = s->lineIndex + 1;
            s->rowCount = s->rowCount + 1;
            p = getLine(s->lineIndex);
            if (p == NULL || p[0] == 0xa || p[0] == 0) {
                s->lineIndex = s->lineIndex + 1;
                return;
            }
            copyTemplateRow(s->screen, s->textSlot, s->rowCount & 0x1f);
            e = allocLabel();
            ((MsgString *)e)->setLine((u8 *)p);
            e->createSmallLabel(a, s->textSlot * 16 + 0x11, 0x10, 1, 0, 0);
            e->redrawAligned(0, 0);
            s->textSlot = s->textSlot + 1;
            s->lineIndex = s->lineIndex + 1;
            s->rowCount = s->rowCount + 1;
        } else if (p[0] == 0x20 && p[1] == 0xa) {
            LabelString *e = allocLabel();
            ((MsgString *)e)->setLine((u8 *)p);
            e->createSmallLabel(a, s->textSlot * 16 + 0x11, 0x10, 1, 0, 0);
            e->redrawAligned(0, 0);
            s->textSlot = s->textSlot + 1;
            s->lineIndex = s->lineIndex + 1;
            s->rowCount = s->rowCount + 1;
        } else {
            copyTemplateRow(s->screen, s->textSlot, s->rowCount & 0x1f);
            s->rowCount = s->rowCount + 1;
            s->textSlot = s->textSlot + 1;
            copyTemplateRow(s->screen, s->textSlot, s->rowCount & 0x1f);
            s->rowCount = s->rowCount + 1;
            s->textSlot = s->textSlot + 1;
            LabelString *e = allocLabel();
            ((MsgString *)e)->setLine((u8 *)p);
            e->createLabel(a, (s->textSlot - 2) * 16 + 0x11, 0x10, 1, 0, 0);
            e->redrawRight();
            s->lineIndex = s->lineIndex + 1;
        }
    }
}

void StaffRoll::scroll(BOOL b)
{
    s32 v;
    scrollPos = scrollPos + scrollSpeed;
    v = scrollPos >> 12;
    scrollLayer(4, v - 0xc0);
    if (b) {
        scrollLayer(0, v);
    }
}

LabelString *StaffRoll::allocLabel()
{
    if (labelCount >= 26) {
        return &labels[25];
    }
    labelCount++;
    return &labels[labelCount - 1];
}

void StaffRoll::resetLabels()
{
    s32 i;
    labelCount = 0;
    for (i = 0; i < 26; i++) {
        labels[i].destroyLabel();
    }
    for (i = 0; i < 2; i++) {
        screenTasks[i].cancel();
    }
}

extern "C" char *sStaffRollLogoCharPath;
extern "C" char data_ov093_0229225c[];
extern "C" char *sStaffRollPalettePath;

void StaffRoll::loadLogo()
{
    void *h = gCurrentHeap;
    Gfx2d_LoadScreenFile("menu/staff/logo.bsc", h, 0);
    Gfx2d_LoadCharFile(sStaffRollLogoCharPath, h, 0, 0x10, 0x10, 0x78);
    Gfx2d_LoadCharFile("menu/staff/logo1.bch", h, 0, 0x79, 0x79, 0xf0);
    Gfx2d_LoadCharFile("menu/staff/logo2.bch", h, 0, 0xf1, 0xf1, 0x15f);
}

StaffRollLayer::StaffRollLayer() {}

StaffRollLayer::~StaffRollLayer() {}

void StaffRollLayer::reset()
{
    rowCount = -1;
    lineIndex = -1;
    flags = 0;
    blankLines = 0;
    setFlags(3);
}

BOOL StaffRollLayer::testFlags(u32 m)
{
    if ((flags & m) != 0) {
        return TRUE;
    }
    return FALSE;
}

void StaffRollLayer::setFlags(u32 m)
{
    flags |= m;
}

void StaffRollLayer::clearFlags(u32 m)
{
    flags &= ~m;
}

BOOL StaffRoll::testFlags(u32 m)
{
    if ((flags & m) != 0) {
        return TRUE;
    }
    return FALSE;
}

void StaffRoll::setFlags(u32 m)
{
    flags |= m;
}

extern "C" char data_ov093_0229225c[] = "menu/staff/logo.bch";

extern "C" char *sStaffRollLogoCharPath = data_ov093_0229225c;
extern "C" char *sStaffRollPalettePath = "menu/staff/sfr.bpl";

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov093_022918e0) {
    HOST_OVERLAY_VAR(data_ov093_0229225c),
    HOST_OVERLAY_VAR(sStaffRollLogoCharPath),
    HOST_OVERLAY_VAR(sStaffRollPalettePath),
    HOST_OVERLAY_VARS_END
};
