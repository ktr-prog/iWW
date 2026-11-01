#include "types.h"
#include "host_tick.h"
#include "host_labels.h"
#include "Unk_020d8c7c.h"
#include "text/Unk_02050288.h"
#include "talk/MsgStringBase.h"
#include "talk/MsgStringAttr.h"
#include "ui/CursorMotion.h"
#include "sys/KeyRepeat.h"
#include "menu/MenuTween.h"
#include "menu/PopupChoiceIdList.h"
#include "ui/AddresseePageArg.h"
#include "nitro/gxoam.h"
#include "talk/TalkWindowState.h"
#include "gfx/SpriteAnim.h"
#include "ui/UiWidget.h"
#include "talk/LabelBalloonText.h"
#include "menu/MenuSlide.h"
#include "talk/MsgString.h"
#include "talk/MsgRequest.h"
#include "menu/MenuProc.h"
#include "ui/HandCursor.h"
#include "ui/ScrollKnob.h"
#include "ui/LabelButton.h"
#include "ui/LabelString.h"
#include "ui/LabelBalloon.h"
#include "ui/TouchPromptBalloon.h"
#include "menu/MenuTextButton.h"
#include "menu/MenuTitleBalloon.h"
#include "menu/MenuLabelButton.h"
#include "menu/MenuCursor.h"
#include "menu/MenuScrollKnob.h"
#include "menu/PopupChoiceRow.h"
#include "menu/MenuBottomButtons.h"
#include "menu/PopupChoiceMenu.h"
#include "talk/TalkMsgRequest.h"
#include "menu/MenuErrorMessage.h"
#include "npc/VillagerId.h"
#include "player/PlayerId.h"
#include "talk/MsgString9B.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_02065e88.h"
#include "proto/main/unk_0206db88.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0206f834.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov002/unk_ov002_022013ac.h"
#include "proto/ov002/unk_ov002_022025cc.h"
#include "proto/ov002/unk_ov002_02202fac.h"
#include "player/PlayerData.h"
#include "save/VillagerData.h"


extern "C" {
BOOL SaveVillagers_IsOccupied(u8 *base, s32 idx);
u8 *SaveVillagers_Get(u8 *base, s32 idx);
VillagerMemory *Villager_FindMemory(void *a, void *b);
void MIi_CpuCopy16(const void *src, void *dest, u32 size);
void MIi_CpuClear16(u16 data, void *dest, u32 size);

#define gSavePlayers HOST_LABEL(u8 (*)[], gSavePlayers)
#define gSaveVillagers HOST_LABEL(u8 (*)[], gSaveVillagers)
}


typedef PopupChoiceMenuBody Self;

extern "C" {
BOOL PopupChoice_MoveCursor(Self *self, s32 p, u8 *pos, u32 n);
BOOL PopupChoice_TickDecideDelay(Self *self);
void PopupChoice_DecideAddressee(Self *self, u32 x);
u8 PopupChoice_DecideCancel(Self *self, s32 x);
void PopupChoice_DecideRow(Self *self, s32 a, s32 b);
void PopupChoice_StartDecide(Self *self, s32 x);
void PopupChoice_ForceClose(Self *self);
void PopupChoice_Draw(Self *self);
void PopupChoice_Update(Self *self);
void PopupChoice_FitWidth(Self *self);
s32 PopupChoice_GetHeight(Self *self);
s32 PopupChoice_GetWidth(Self *self);
void PopupChoice_StepSlideClose(Self *self);
void PopupChoice_StepSlideOpen(Self *self);
void PopupChoice_ApplySlide(Self *self);
void PopupChoice_StepPopClose(Self *self);
void PopupChoice_StepPopOpen(Self *self);
void PopupChoice_BuildScreen(Self *self);
void PopupChoice_SetState(Self *self, u32 x);
void PopupChoice_Close(Self *self, s32 x);
void PopupChoice_Open(Self *self, s32 x);
void PopupChoice_OpenAddresseePage(Self *self, AddresseePageArg a, s32 x);
void PopupChoice_LoadFriendBg(Self *self);
void PopupChoice_LoadChoiceBg(Self *self);
void PopupChoice_SetPosClamped(Self *self, s32 x, s32 y);
void PopupChoice_SetPos(Self *self, s32 x, s32 y);
void PopupChoice_ApplyScroll(Self *self, s32 x, s32 y);
}

extern "C" s32 sPopupChoicePopOffsets[3] = {-5, 1, 0};


PopupChoiceRow::PopupChoiceRow() {
    layer = 3;
    charBase = 0;
    fgColor = 1;
    bgColor = 9;
}

PopupChoiceRow::~PopupChoiceRow() {}

void PopupChoiceRow::render(s32 v) {
    u8 x = fgColor;
    if (v >= 0) {
        x = v & 0xf;
    }
    createLabel(layer, charBase, 0xd, x, bgColor, 0);
}

void PopupChoiceRow::setup(u32 a, u16 b, u8 c, u8 d) {
    layer = a;
    charBase = b;
    fgColor = c;
    bgColor = d;
}


PopupChoiceMenu::PopupChoiceMenu() {}

PopupChoiceMenu::~PopupChoiceMenu() {}

void PopupChoiceMenu::init(s32 a, s32 b, const char *path) {
    layer = a;
    bgPriority = b;
    scrollX = 0;
    scrollY = 0;
    state = 0;
    request = 0;
    stateStep = 0;
    openLeftward = 0;
    textWidthTiles = 0xd;
    numRows = 5;
    if (path == 0) {
        screenFile = (const char *)"menu/inventory/b_itm_bg_b.bsc";
    } else {
        screenFile = path;
    }
    Heap *heap = gCurrentHeap;
    u8 *buf = (u8 *)File_LoadAlloc(screenFile, heap, -4, 0);
    rowCharBase = *(u16 *)(buf + 0x44) & 0x3ff;
    Heap_Free(heap, buf);
    u16 v = rowCharBase;
    s32 i;
    for (i = 0; i < 5; i++) {
        rows[i].setup(a, v, 1, 9);
        v += 0x1a;
    }
    pageButton.setOrigin(0x60, 0x8c);
    pageButton.setPos(0, 0);
    pageButton.hideLayer2();
    pageButton.enableObjWindow();
    pageButton.setState(1);
    title.hideNow();
    title.showText(0x1f, 0x80, 0xc);
    title.enableObjWindow();
    flags = 0;
}

void PopupChoiceMenu::placeCentered(s32 a, s32 b) {
    a += 0x80;
    b += 0x60;
    s32 w = PopupChoice_GetWidth((Self *)this);
    s32 h = PopupChoice_GetHeight((Self *)this);
    a -= w >> 1;
    b -= h >> 1;
    PopupChoice_SetPos((Self *)this, a, b);
}

void PopupChoiceMenu::placeNearPoint(s32 a, s32 b) {
    s32 w = PopupChoice_GetWidth((Self *)this);
    s32 h = PopupChoice_GetHeight((Self *)this);
    s32 x = a - w + 0x20;
    if (x > 0) {
        openLeftward = 1;
    } else {
        x = a - 0x10;
        openLeftward = 0;
    }
    s32 y = b - h - 4;
    if (y < 10) {
        y = 10;
    }
    PopupChoice_SetPos((Self *)this, x, y);
}

void PopupChoiceMenu::placeAt(s32 a, s32 b) {
    PopupChoice_SetPosClamped((Self *)this, a, b);
}

void PopupChoiceMenu::placeAbove(s32 a, s32 b) {
    b -= PopupChoice_GetHeight((Self *)this);
    PopupChoice_SetPosClamped((Self *)this, a, b);
}

void PopupChoiceMenu::placeAboveBalloon(LabelBalloon *p) {
    openLeftward = 0;
    s32 x = p->getPosX() + 0x80;
    s32 y = p->getPosY() + 0x60;
    s32 h = PopupChoice_GetHeight((Self *)this);
    s32 hw = p->getWidth() >> 1;
    s32 r = x + hw;
    if (r > 0x100) {
        x -= r - 0x100;
    } else {
        r = x - hw;
        if (r < 0) {
            x -= r;
        }
    }
    x -= 2;
    x -= PopupChoice_GetWidth((Self *)this) >> 1;
    s32 t = y - h;
    if (t < 10) {
        y += 0x10;
    } else {
        y = t;
    }
    PopupChoice_SetPosClamped((Self *)this, x, y);
}

void PopupChoice_ApplyScroll(Self *self, s32 x, s32 y) {
    Gfx2d_SetLayerOffset(self->layer, x, y);
}

void PopupChoice_SetPos(Self *self, s32 x, s32 y) {
    PopupChoice_ApplyScroll(self, x, y);
    self->scrollX = -x;
    self->scrollY = -y;
}

void PopupChoice_SetPosClamped(Self *self, s32 x, s32 y) {
    s32 a = PopupChoice_GetWidth(self);
    s32 b = PopupChoice_GetHeight(self);
    if (x < 0) x = 0;
    if (y < 10) y = 10;
    if (x + a > 0xff) x = 0xff - a;
    if (y + b > 0xb6) y = 0xb6 - b;
    PopupChoice_SetPos(self, x, y);
}

void PopupChoice_LoadChoiceBg(Self *self) {
    Heap *h = gCurrentHeap;
    Gfx2d_LoadPaletteFile("menu/inventory/b_itm.bpl", h, self->layer, 0, 3, 3);
    Gfx2d_LoadCharFile("menu/inventory/b_choice.bch", h, self->layer, 0x242, 0x242, 0x2d7);
}

void PopupChoice_LoadFriendBg(Self *self) {
    Heap *h = gCurrentHeap;
    Gfx2d_LoadPaletteFile("menu/friend/bg1.bpl", h, self->layer, 0xe, 0xe, 0xe);
    Gfx2d_LoadCharFile("menu/friend/bg1.bch", h, self->layer, 0x26e, 0x26e, 0x27d);
}

void PopupChoice_OpenAddresseePage(Self *self, AddresseePageArg a, s32 x) {
    self->loadAddresseePage((PopupChoiceIdList *)&a);
    self->placeCentered(0, -12);
    PopupChoice_Open(self, x);
}

void PopupChoice_Open(Self *self, s32 x) {
    self->request = 1;
    Gfx2d_HideLayer(self->layer);
    if (x != 0) {
        self->setFlags(2);
    }
    Snd_PlaySe(0x13);
    self->clearFlags(0x10);
}

void PopupChoice_Close(Self *self, s32 x) {
    self->request = 2;
    if (x != 0) {
        self->setFlags(4);
    }
    if (self->testFlags(0x10)) {
        self->clearFlags(0x10);
    } else {
        Snd_PlaySe(0x14);
    }
}

void PopupChoice_SetState(Self *self, u32 x) {
    if (self->testFlags(2) && x == 1) {
        x = 2;
        self->clearFlags(x);
    } else if (self->testFlags(4) && x == 4) {
        x = 5;
        self->clearFlags(4);
    }
    self->state = x;
    self->stateStep = 0;
}

void PopupChoice_BuildScreen(Self *self) {
    Gfx2d_SetLayerPriority(self->layer, self->bgPriority);
    Gfx2d_SetLayerControl(self->layer, 0, 0, 0);
    Heap *heap = gCurrentHeap;
    u8 *buf = (u8 *)File_LoadAlloc(self->screenFile, heap, -4, 0);
    u32 n = self->numRows;
    if (n != 5) {
        u16 v = *(u16 *)(buf + 0x22);
        u16 *src = (u16 *)(buf + 0x280);
        u16 *dst = (u16 *)(buf + (n << 7));
        dst[0] = src[0];
        dst[1] = src[1];
        dst[0xf] = src[0xf];
        dst[0x10] = src[0x10];
        u8 *t = buf + (((self->numRows << 1) + 1) << 6);
        u8 *q = buf + 0x2c0;
        MIi_CpuCopy16(q, t ? t : t, 0x40);
        n = self->numRows;
        volatile u16 tmp[1];
        tmp[0] = v;
        MIi_CpuClear16(tmp[0], buf + (((n << 1) + 2) << 6), (5 - n) << 7);
    }
    if (self->textWidthTiles != 0xd) {
        u8 *s;
        u8 *d;
        s32 i;
        s32 k;
        d = buf + (self->textWidthTiles + 1) * 2;
        s = buf + 0x1c;
        k = self->numRows * 2 + 2;
        MIi_CpuCopy16(s, d, 0x1e);
        d += 0x42;
        s += 0x42;
        for (i = 1; i < k - 1; i++) {
            MIi_CpuCopy16(s, d, 0x1e);
            d += 0x40;
            s += 0x40;
        }
        MIi_CpuCopy16(s - 2, d - 2, 0x1e);
    }
    Gfx2d_LoadScreen(buf, self->layer, 0x800, 0);
    Heap_Free(heap, buf);
}

void PopupChoice_StepPopOpen(Self *self) {
    if (self->stateStep == 0) {
        PopupChoice_BuildScreen(self);
        Gfx2d_ShowLayer(self->layer);
    }
    s32 d = sPopupChoicePopOffsets[self->stateStep];
    s32 x;
    if (self->openLeftward != 0) {
        x = self->scrollX - d;
    } else {
        x = self->scrollX + d;
    }
    if (x > 0) x = 0;
    if (-x + PopupChoice_GetWidth(self) > 0xff) {
        x = PopupChoice_GetWidth(self) - 0xff;
    }
    PopupChoice_ApplyScroll(self, x, self->scrollY - d);
    self->stateStep = self->stateStep + 1;
    if (self->stateStep >= 3) {
        PopupChoice_SetState(self, 3);
    }
}

void PopupChoice_StepPopClose(Self *self) {
    if (self->stateStep == 0) {
        s32 x;
        if (self->openLeftward != 0) {
            x = self->scrollX - 0xb;
        } else {
            x = self->scrollX + 0xb;
        }
        if (x > 0) x = 0;
        if (-x + PopupChoice_GetWidth(self) > 0xff) {
            x = PopupChoice_GetWidth(self) - 0xff;
        }
        PopupChoice_ApplyScroll(self, x, self->scrollY - 0xb);
        self->stateStep = self->stateStep + 1;
    } else {
        Gfx2d_HideLayer(self->layer);
        PopupChoice_SetState(self, 0);
    }
}

void PopupChoice_ApplySlide(Self *self) {
    ((MenuSlideView *)&self->slide)->applyLayerOffset(self->layer, -self->scrollX, -self->scrollY);
    s32 r = ((MenuSlideView *)&self->slide)->getOffsetY();
    self->pageButton.setPos(0, r);
    self->title.setPos(0, -(r >> 2));
}

void PopupChoice_StepSlideOpen(Self *self) {
    if (self->stateStep == 0) {
        PopupChoice_BuildScreen(self);
        Gfx2d_BeginSubObjWinBrightness();
        Gfx2d_ExcludeSubBrightnessPlanes(Gfx2d_GetLayerBlendMask(self->layer));
        Gfx2d_SetSubBrightness(-6);
        s32 r = Gfx2d_GetLayerPlaneMask(self->layer);
        ((MenuSlideView *)&self->slide)->beginSubSlideIn(r, 5, 0, 0x30);
        Gfx2d_ShowLayer(self->layer);
        self->setFlags(1);
        self->titleRefreshDelay = 2;
        PopupChoice_ApplySlide(self);
        self->stateStep = self->stateStep + 1;
    } else {
        if (((MenuSlideView *)&self->slide)->stepSlideIn(0)) {
            PopupChoice_SetState(self, 3);
            if (self->titleRefreshDelay != 0) {
                self->titleRefreshDelay = 1;
            }
        }
        if (self->titleRefreshDelay != 0) {
            self->titleRefreshDelay = self->titleRefreshDelay - (TICK_STEP_ENDS() ? 1 : 0);
            if (self->titleRefreshDelay == 0) {
                self->title.refreshText(0);
            }
        }
        PopupChoice_ApplySlide(self);
    }
}

void PopupChoice_StepSlideClose(Self *self) {
    if (self->stateStep == 0) {
        s32 r = Gfx2d_GetLayerPlaneMask(self->layer);
        ((MenuSlideView *)&self->slide)->beginSubSlideOut(r, 3, 0, 0x30);
        PopupChoice_ApplySlide(self);
        self->stateStep = self->stateStep + 1;
    }
    if (((MenuSlideView *)&self->slide)->stepSlideOut(0)) {
        Gfx2d_EndSubObjWinBrightness();
        self->clearFlags(1);
        Gfx2d_HideLayer(self->layer);
        PopupChoice_SetState(self, 0);
    } else {
        PopupChoice_ApplySlide(self);
    }
}

s32 PopupChoice_GetWidth(Self *self) {
    return (self->textWidthTiles + 4) << 3;
}

s32 PopupChoice_GetHeight(Self *self) {
    return (self->numRows * 2 + 2) << 3;
}

void PopupChoice_FitWidth(Self *self) {
    s32 max = 0;
    s32 i = 0;
    PopupChoiceRow *e = self->rows;
    for (; i < self->numRows; i++) {
        s32 v = e[i].getTextWidth();
        if (v > max) max = v;
    }
    self->textWidthTiles = (max + 7) >> 3;
}

void PopupChoice_Update(Self *self) {
    self->freeRowTexts();
    if (self->testFlags(8)) {
        self->clearFlags(8);
        self->rows[self->decidedRow].render(0xf);
        self->rows[self->decidedRow].redrawAligned(0, 0);
    }
    switch (self->request) {
    case 1:
        switch (self->state) {
        case 0:
            PopupChoice_SetState(self, 1);
            self->request = 0;
            self->renderRows();
            break;
        case 1:
        case 2:
            self->request = 0;
            break;
        case 3:
            PopupChoice_SetState(self, 4);
            break;
        }
        break;
    case 2:
        switch (self->state) {
        case 3:
            PopupChoice_SetState(self, 4);
            self->request = 0;
            break;
        case 1:
            Gfx2d_HideLayer(self->layer);
            PopupChoice_SetState(self, 0);
            self->request = 0;
            break;
        case 0:
        case 2:
            self->request = 0;
            break;
        }
        break;
    }
    switch (self->state) {
    case 1:
        PopupChoice_StepPopOpen(self);
        break;
    case 4:
        PopupChoice_StepPopClose(self);
        break;
    case 2:
        PopupChoice_StepSlideOpen(self);
        break;
    case 5:
        PopupChoice_StepSlideClose(self);
        break;
    case 0:
    case 3:
        break;
    }
}

void PopupChoice_Draw(Self *self) {
    if (self->testFlags(1)) {
        self->pageButton.draw();
        self->title.draw();
    }
}

void PopupChoice_ForceClose(Self *self) {
    self->request = 0;
    if (self->state != 0) {
        Gfx2d_HideLayer(self->layer);
        self->state = 0;
    }
    self->freeRowTexts();
}

void PopupChoice_StartDecide(Self *self, s32 x) {
    self->setFlags(8);
    if (MenuCtrl_IsButtons()) {
        self->decideDelay = 2;
    } else {
        self->decideDelay = 5;
    }
    self->decidedRow = x;
}

void PopupChoice_DecideRow(Self *self, s32 a, s32 b) {
    PopupChoice_StartDecide(self, a);
    if (b == 0) {
        self->setFlags(0x10);
    } else if (self->numRows - 1 == a) {
        Snd_PlaySe(0x2a);
    } else {
        Snd_PlaySe(0x29);
    }
}

u8 PopupChoice_DecideCancel(Self *self, s32 x) {
    s32 t = self->numRows - 1;
    PopupChoice_StartDecide(self, t);
    if (x == 0) {
        self->setFlags(0x10);
    } else {
        Snd_PlaySe(0x2a);
    }
    return t;
}

void PopupChoice_DecideAddressee(Self *self, u32 x) {
    PopupChoice_StartDecide(self, x);
    if (self->pickAddressee(self->addresseePage, (u8)x) == 0xf) {
        Snd_PlaySe(0x2a);
    } else {
        Snd_PlaySe(0x29);
    }
}

BOOL PopupChoice_TickDecideDelay(Self *self) {
    u32 v = self->decideDelay;
    if (v != 0) {
        self->decideDelay = v - 1;
        return FALSE;
    }
    return TRUE;
}

BOOL PopupChoice_MoveCursor(Self *self, s32 p, u8 *pos, u32 n) {
    if (p != 0) {
        if (MenuKeys_HasUp(p)) {
            if (*pos > n) {
                *pos = *pos - 1;
            } else {
                *pos = self->numRows - 1;
            }
            return TRUE;
        }
        if (MenuKeys_HasDown(p)) {
            s32 t = *pos + 1;
            if (t < self->numRows) {
                *pos = t;
            } else {
                *pos = n;
            }
            return TRUE;
        }
    }
    return FALSE;
}

void PopupChoice_CopyPlayerIdName(MsgString *a, PlayerId *b) {
    MsgString9B buf;
    b->getNameString(&buf);
    a->copy(&buf);
}

void PopupChoice_CopyResidentName(MsgString *x, s32 y) {
    PopupChoice_CopyPlayerIdName(x, ((PlayerData *)(PlayerData_GetResident(gSavePlayers, y)))->getPlayerId());
}

void PopupChoice_CopyVillagerIdName(MsgString *a, VillagerId *b) {
    MsgString9B buf;
    b->getName(&buf);
    a->copy(&buf);
}

void PopupChoice_CopyVillagerName(MsgString *x, s32 y) {
    PopupChoice_CopyVillagerIdName(x, ((VillagerData *)SaveVillagers_Get(gSaveVillagers, y))->getVillagerId());
}

void PopupChoice_SetAddresseeName(Self *menu, MsgString *x, u32 id) {
    if (id >= 1 && id < 5) {
        PopupChoice_CopyResidentName(x, id - 1);
    } else if (id >= 5 && id < 0xd) {
        PopupChoice_CopyVillagerName(x, id - 5);
    } else {
        switch (id) {
        case 0xd:
            menu->load2dString(x, 0x25);
            break;
        case 0xe:
            menu->load2dString(x, 0x1e);
            break;
        case 0xf:
            menu->load2dString(x, 0x27);
            break;
        }
    }
}

void PopupChoiceMenuBody::buildAddresseeList()
{
    s32 i, n;
    s32 k, j;
    PlayerId *g;
    s32 t;
    numPages = 0;
    for (i = 0; i < 0x19; i++) {
        addresseeIds[i] = 0;
    }
    g = PlayerData_GetCurrent()->getPlayerId();
    t = PlayerDataArray_FindById(gSavePlayers, (u16 *)g);
    n = 0;
    k = 1;
    j = n;
    do {
        if (t != j) {
            if (PlayerDataArray_IsUsed(gSavePlayers, j)) {
                addresseeIds[n] = k;
                n++;
            }
        }
        k++;
        j++;
    } while (k < 5);
    if (n % 5 == 4) {
        addresseeIds[n] = 0xe;
        n++;
    }
    k = 5;
    j = 0;
    do {
        if (SaveVillagers_IsOccupied(gSaveVillagers, j)) {
            if (Villager_FindMemory(SaveVillagers_Get(gSaveVillagers, j), g)) {
                addresseeIds[n] = k;
                n++;
            }
        }
        if (n % 5 == 4) {
            addresseeIds[n] = 0xe;
            n++;
        }
        k++;
        j++;
    } while (k < 0xd);
    if (n % 5 != 0) {
        addresseeIds[n] = 0xe;
        n++;
    }
    while (n % 5 != 0) {
        addresseeIds[n] = 0;
        n++;
    }
    addresseeIds[n] = 0xd;
    addresseeIds[n + 1] = 0xf;
    n += 2;
    if (n > 2) {
        addresseeIds[n] = 0xe;
        n++;
    }
    numPages = (n + 4) / 5;
}

BOOL PopupChoiceMenuBody::isOpen()
{
    if (state == 3) {
        return TRUE;
    }
    return FALSE;
}

BOOL PopupChoiceMenuBody::isClosed()
{
    if (state == 0) {
        return TRUE;
    }
    return FALSE;
}

void PopupChoiceMenuBody::freeRowTexts()
{
    s32 i;
    for (i = 0; i < 5; i++) {
        rows[i].destroyLabel();
    }
}

void PopupChoiceMenuBody::resetRowColors()
{
    s32 i;
    for (i = 0; i < 5; i++) {
        rows[i].render(-1);
    }
}

void PopupChoiceMenuBody::renderRows()
{
    resetRowColors();
    s32 i;
    for (i = 0; i < numRows; i++) {
        rows[i].redrawAligned(0, 0);
    }
}

extern "C" BOOL ChoiceIdList_Add(u8 *p, u32 a, u32 b)
{
    s32 i;
    for (i = 0; i < 5; i++) {
        u8 *q = &p[i];
        if (p[i] == 0xff) {
            q[0] = a;
            q[5] = b;
            return TRUE;
        }
    }
    return FALSE;
}

extern "C" void ChoiceIdList_Clear(u8 *p, u8 v)
{
    s32 i;
    for (i = 0; i < 5; i++) {
        u8 *q = &p[i];
        p[i] = 0xff;
        q[5] = v;
    }
    p[10] = 0;
}

extern "C" s32 ChoiceIdList_Count(u8 *p)
{
    s32 i;
    for (i = 0; i < 5; i++) {
        if (p[i] == 0xff) {
            return i;
        }
    }
    return i;
}

s32 PopupChoiceMenuBody::addCustomRow(PopupChoiceIdList *r, void *s, u32 v)
{
    s32 i;
    for (i = 0; i < 5; i++) {
        u8 *q = &r->msgIds[i];
        if (r->msgIds[i] == 0xff) {
            ((MsgString *)(&rows[i]))->copy((MsgString *)(s));
            r->values[i] = v;
            r->customMask |= 1 << i;
            q[0] = 0xfe;
            return 1;
        }
    }
    return 0;
}

void PopupChoiceMenuBody::setRowsFromIds(PopupChoiceIdList *r, s32 f)
{
    s32 n = 0;
    s32 i = n;
    for (; i < 5; i++) {
        u32 v = r->msgIds[i];
        if (v == 0xff) {
            i = 5;
        } else if ((1 << i) & r->customMask) {
            n++;
        } else {
            load2dString(&rows[n], v);
            n++;
        }
    }
    if (f != 0) {
        setFlags(0x20);
    } else {
        clearFlags(0x20);
    }
    numRows = n;
    PopupChoice_FitWidth(this);
}

void PopupChoiceMenuBody::loadAddresseePage(PopupChoiceIdList *r)
{
    s32 i;
    s32 k = r->msgIds[0] * 5;
    numRows = 0;
    for (i = 0; i < 5; i++, k++) {
        u32 v = addresseeIds[k];
        if (v != 0) {
            PopupChoice_SetAddresseeName(this, &rows[i], v);
            numRows++;
        } else {
            i = 5;
        }
    }
    PopupChoice_FitWidth(this);
    u8 buf[4];
    buf[0] = r->msgIds[0] + 0x36;
    buf[1] = 0;
    buf[2] = numPages + 0x35;
    buf[3] = 0;
    LabelString a;
    LabelString b;
    String_FromEncodedBytes(&b, buf, 2);
    a.copy(&b);
    a.append((u8 *)"/");
    String_FromEncodedBytes(&b, buf + 2, 2);
    a.appendString(&b);
    pageButton.setLabelText(&a);
    pageButton.update();
    addresseePage = r->msgIds[0];
}

s32 PopupChoiceMenuBody::hitTestRowOr(s32 x, s32 y, s32 d)
{
    s32 l = -scrollX;
    s32 t = -scrollY;
    s32 r = l + PopupChoice_GetWidth((Self *)this);
    s32 b = t + PopupChoice_GetHeight((Self *)this);
    if (l > x || r < x) {
        return d;
    }
    if (t > y || b < y) {
        return d;
    }
    t += 0x18;
    s32 i = 0;
    s32 n = numRows - 1;
    for (; i < n; i++) {
        if (t > y) {
            break;
        }
        t += 0x10;
    }
    return i;
}

s32 PopupChoiceMenuBody::hitTestRowOrLast(s32 x, s32 y)
{
    return hitTestRowOr(x, y, numRows - 1);
}

s32 PopupChoiceMenuBody::hitTestRow(s32 x, s32 y)
{
    return hitTestRowOr(x, y, -1);
}

s32 PopupChoiceMenuBody::getRowX()
{
    return 0x10 - scrollX;
}

s32 PopupChoiceMenuBody::getRowY(s32 v)
{
    return ((v + 1) << 4) - scrollY;
}

u32 PopupChoiceMenuBody::getRowCount()
{
    return numRows;
}

u32 PopupChoiceMenuBody::getPageCount()
{
    return numPages;
}

u32 PopupChoiceMenuBody::pickAddressee(u32 a, u32 b)
{
    u32 t = addresseeIds[b + a * 5];
    if (t != 0xe) {
        setFlags(4);
    }
    switch (t) {
    case 0xf:
        Snd_PlaySe(0x28);
        break;
    case 0xe:
        Snd_PlaySe(0x29);
        break;
    default:
        Snd_PlaySe(0x27);
        break;
    }
    return t;
}

s32 PopupChoiceMenuBody::getAddresseeKind(u32 id)
{
    switch (id) {
    case 0xf:
        return 3;
    case 0xe:
        return 2;
    }
    return 1;
}

s32 PopupChoiceMenuBody::applyAddressee(void *p, u32 id)
{
    LetterView *letter = static_cast<LetterView *>(p);
    switch (id) {
    case 0xf:
        return 3;
    case 0xe:
        return 2;
    case 0xd:
        Letter_SetRecipientFutureSelf(letter);
        return 1;
    }
    if (id >= 1 && id < 5) {
        Letter_SetRecipientResident(letter, id - 1);
        return 1;
    }
    if (id >= 5 && id < 0xd) {
        Letter_SetRecipientVillager(letter, id - 5);
        return 1;
    }
    return 0;
}

BOOL PopupChoiceMenuBody::testFlags(u32 m)
{
    if (flags & m) {
        return TRUE;
    }
    return FALSE;
}

void PopupChoiceMenuBody::setFlags(u32 m)
{
    flags |= m;
}

void PopupChoiceMenuBody::clearFlags(u32 m)
{
    flags &= ~m;
}

void PopupChoiceMenuBody::load2dString(MsgString *buf, u32 c)
{
    u8 t = c;
    String_Load2d(buf, &t, 0);
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov002_022013ac) {
    HOST_OVERLAY_VAR(sPopupChoicePopOffsets),
    HOST_OVERLAY_VARS_END
};
