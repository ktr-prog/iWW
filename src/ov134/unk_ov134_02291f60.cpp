#include "types.h"
#include "host_tick.h"
#include "ui/ScrollKnob.h"
#include "ui/LabelString.h"
#include "gfx/BgVramTask.h"
#include "menu/MenuScrollKnob.h"
#include "menu/DateTimePicker.h"
#include "nitro/gxoam.h"
#include "sys/ClockDateTime.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_0206f834.h"
#include "proto/main/unk_02087e70.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov002/unk_ov002_022025cc.h"
#include "proto/autoload_2/unk_020e7500.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/ov134/unk_ov134_02291f60.h"







extern "C" {
extern u16 gPad;
void MIi_CpuCopy16(const void *src, void *dst, u32 n);
void MI_CpuCopy8(const void *src, void *dst, u32 n);
s32 _s32_div_f(s32 a, s32 b);
s32 Date_GetDaysInMonth(u32 y, u32 m);
s32 Date_GetWeekday(u32 a, u32 b, u32 c);
void DateTime_SubDays(ClockDateTime *p, s32 n);
void DateTime_AddDays(ClockDateTime *p, s32 n);
void DateTime_AddMinutes(ClockDateTime *p, s32 n);
void DateTime_SubMinutes(ClockDateTime *p, s32 n);
void DateTime_SubHours(ClockDateTime *p, s32 n);
void DateTime_AddHours(ClockDateTime *p, s32 n);
s32 DateTime_Compare(ClockDateTime *a, ClockDateTime *b, u32 mask);
s32 DateTime_DiffMinutes(ClockDateTime *a, ClockDateTime *b);
void Clock_GetDateTime(ClockDateTime *p);

extern const u8 sFieldNameTextIds[6];
extern const u8 sFieldValueCounts[6];
extern const u8 sWeekdayTextIds[7];
extern const u8 sMonthStringIds[12];
extern const u32 sFieldTopDefault[6];
extern const u32 sFieldWidths[6];
extern const u32 sFieldLeftBirthday[6];
extern const u32 sFieldLeftDefault[6];
extern const u32 sFieldLeftTime[6];
extern const u32 sFieldTopBirthday[6];
extern const u32 sFieldTopTime[6];
}

static inline s32 Unk_ov134_02293510_Hi(DateTimePicker *self, s32 i, s32 off) { return DateTimePicker_GetFieldRight(self, i) + off; }

DateTimePicker::DateTimePicker() {
}

DateTimePicker::~DateTimePicker() {
}

extern "C" void DateTimePicker_Init(DateTimePicker *s, u32 a, u32 b, u32 c, u8 d) {
    s->flags = 0;
    s->listKeyHoldCount = 0;
    s->mode = a;
    s->fieldFlash[0] = 0;
    switch (s->mode) {
    case 0:
    case 1:
        s->objVariant = 0;
        break;
    case 2:
        s->objVariant = 1;
        break;
    case 3:
        s->objVariant = 2;
        break;
    }
    s->mainLayer = b;
    s->fieldLayer = c;
    s->listLayer = d;
    s->pickedRowCell = 0;
    s->listTopCell = 0;
    s->listBottomCell = 0;
    s->knob.show();
    s->pendingScroll = 0;
    switch (s->mode) {
    case 0:
    case 3:
        s->cursorField = 0;
        break;
    case 1:
        s->cursorField = 3;
        s->setFlags(0x40);
        s->setFlags(0x80);
        break;
    case 2:
        s->cursorField = 1;
        break;
    }
    if (s->mode == 2) {
        s->dateTime.words[0] = 0;
        s->dateTime.words[1] = 0;
        s->dateTime.dt.year = 1;
        s->dateTime.dt.month = 1;
        s->dateTime.dt.day = 1;
    } else {
        Clock_GetDateTime(&s->dateTime.dt);
        s->dateTime.dt.second = 0;
        if (s->mode == 3) {
            DateTime_AddDays(&s->dateTime.dt, 1);
        }
        MI_CpuCopy8(&s->dateTime.dt, &s->minDateTime.dt, 8);
        MI_CpuCopy8(&s->dateTime.dt, &s->maxDateTime.dt, 8);
        DateTime_AddHours(&s->maxDateTime.dt, 0xc);
        s->minHour = s->minDateTime.dt.hour;
        s->maxHour = s->maxDateTime.dt.hour;
        s->minMinute = s->minDateTime.dt.minute;
        DateTimePicker_SyncHands(s);
    }
}

extern "C" void DateTimePicker_EnableMinLimit(DateTimePicker *s) {
    s->setFlags(0x80);
}

extern "C" void DateTimePicker_Shutdown(DateTimePicker *s) {
    DateTimePicker_ReleaseLabels(s);
    Gfx2d_HideLayer(s->listLayer);
    s->fieldScreenTask.cancel();
    s->listScreenTask.cancel();
    s->listPaletteTask.cancel();
}

extern "C" void DateTimePicker_BeginFrame(DateTimePicker *s) {
    DateTimePicker_ReleaseLabels(s);
    s->fieldScreenTask.cancel();
    s->listScreenTask.cancel();
    s->listPaletteTask.cancel();
    DateTimePicker_TickFieldFlash(s);
    s->knob.update();
}

extern "C" void DateTimePicker_EndFrame(DateTimePicker *s) {
    s->stepListScroll();
    s->knob.updateRelease();
    if (s->testFlags(2)) {
        if (s->fieldScreenTask.requestScreen(s->fieldScreen, s->fieldLayer, 0x800, 0)) {
            s->clearFlags(2);
        }
    }
    if (s->testFlags(1)) {
        if (s->listScreenTask.requestScreen(s->listScreen, s->listLayer, 0x800, 0)) {
            s->clearFlags(1);
        }
    }
    s32 t = s->listKeyHoldCount;
    if (t > 0) {
        if (gPad & 0x40) {
            s->listKeyHoldCount = 0;
        }
    } else if (t < 0) {
        if (gPad & 0x80) {
            s->listKeyHoldCount = 0;
        }
    }
}

extern "C" void DateTimePicker_GetDateTime(DateTimePicker *s, ClockDateTime *out) {
    MI_CpuCopy8(&s->dateTime.dt, out, 8);
}

extern "C" BOOL DateTimePicker_IsBeforeStart(DateTimePicker *s) {
    if (DateTime_Compare(&s->minDateTime.dt, &s->dateTime.dt, 0x3f) == 1) {
        return TRUE;
    }
    return FALSE;
}

extern "C" void DateTimePicker_LoadBgGraphics(DateTimePicker *s) {
    Heap *h = gCurrentHeap;
    Gfx2d_LoadCharFile("menu/clock/b_tim_bg.bch", h, s->mainLayer, 0x10, 0x10, 0x80);
    Gfx2d_LoadPaletteFile("menu/clock/b_tim_bg.bpl", h, s->mainLayer, 1, 1, 10);
    Gfx2d_LoadPaletteFile(sBgPaletteFiles[s->mode], h, s->mainLayer, 1, 1, 2);
    Gfx2d_LoadScreenFile("menu/clock/bga.bsc", h, s->mainLayer);
    File_LoadToBuffer(sFieldScreenFiles[s->mode], s->fieldScreen, 0x800);
    DateTimePicker_ResetFieldPalettes(s);
    File_LoadToBuffer("menu/clock/b_tim_b1_bg.bsc", s->listScreenBase, 0x800);
    File_LoadToBuffer("menu/clock/b_tim_bg_9.bpl", s->listPalette, 0x20);
}

extern "C" void DateTimePicker_DrawTitleAndFields(DateTimePicker *s, u8 a) {
    DateTimePicker_DrawFields(s);
    DateTimePicker_AddMenuText(s, s->mainLayer, 0x54, 0x10, a, 1, 0xf, 0xe);
}

extern "C" void DateTimePicker_LoadObjGraphics(DateTimePicker *s) {
    Heap *h = gCurrentHeap;
    Gfx2d_LoadPaletteFile("menu/clock/b_tim_obj.bpl", h, 8, 4, 4, 10);
    Gfx2d_LoadCharFile("menu/clock/b_tim_obj.bch", h, 8, 0xc0, 0xc0, 0x1df);
    u32 v = s->objVariant;
    u32 out;
    u8 *buf = (u8 *)File_LoadAlloc(sObjVariantFiles[v >> 2], h, -4, &out);
    u8 *p = buf + ((s32)v % 4) * 0x100;
    s32 x = 0xc0;
    s32 i = 0;
    do {
        Gfx2d_LoadCharRange(p, 8, x, x, x + 7);
        p += 0x400;
        x += 0x20;
        i++;
    } while (i < 8);
    Heap_Free(h, buf);
    Gfx2d_LoadPaletteFileSlot("menu/clock/b_tim_ten0_obj.bpl", h, 8, s->objVariant, 4);
}

extern "C" void DateTimePicker_DrawWeekday(DateTimePicker *s) {
    s32 i = Date_GetWeekday(s->dateTime.dt.year, s->dateTime.dt.month, s->dateTime.dt.day);
    DateTimePicker_AddMenuText(s, s->fieldLayer, 0x1a8, 7, sWeekdayTextIds[i], 1, 0xf, 0);
}

extern "C" void DateTimePicker_DrawFields(DateTimePicker *s) {
    DateTimePicker_DrawYear(s);
    DateTimePicker_DrawMonth(s);
    DateTimePicker_DrawDay(s);
    DateTimePicker_DrawHour(s);
    DateTimePicker_DrawMinute(s);
    DateTimePicker_DrawWeekday(s);
}

extern "C" void DateTimePicker_DrawField(DateTimePicker *s, u32 idx) {
    switch (idx) {
    case 0:
        DateTimePicker_DrawYear(s);
        break;
    case 1:
        DateTimePicker_DrawMonth(s);
        break;
    case 2:
        DateTimePicker_DrawDay(s);
        break;
    case 3:
        DateTimePicker_DrawHour(s);
        break;
    case 4:
        DateTimePicker_DrawMinute(s);
        break;
    case 5:
        DateTimePicker_DrawWeekday(s);
        break;
    }
}

extern "C" u32 DateTimePicker_GetField(DateTimePicker *s, u32 idx) {
    return DateTimePicker_GetFieldOf(s, idx, &s->dateTime.dt);
}

extern "C" u32 DateTimePicker_GetFieldOf(DateTimePicker *s, u32 idx, ClockDateTime *p) {
    switch (idx) {
    case 0:
        return p->year;
    case 1:
        return p->month;
    case 2:
        return p->day;
    case 3:
        return p->hour;
    case 4:
        return p->minute;
    case 5:
        return 0;
    }
    return 0xff;
}

extern "C" void DateTimePicker_SetField(DateTimePicker *s, u32 idx, u32 v) {
    switch (idx) {
    case 0:
        s->dateTime.dt.year = v;
        break;
    case 1:
        s->dateTime.dt.month = v + 1;
        break;
    case 2:
        s->dateTime.dt.day = v + 1;
        break;
    case 3:
        s->dateTime.dt.hour = v;
        break;
    case 4:
        s->dateTime.dt.minute = v;
        break;
    case 5:
        break;
    }
}

extern "C" void DateTimePicker_DrawYear(DateTimePicker *s) {
    DateTimePicker_AddNumberText(s, s->fieldLayer, 0x180, 4, 0x7d0 + s->dateTime.dt.year, 0xf, 0);
}

extern "C" u32 DateTimePicker_GetMonthStringId(DateTimePicker *s, u32 a) {
    return sMonthStringIds[a - 1];
}

extern "C" void DateTimePicker_DrawMonth(DateTimePicker *s) {
    u32 r = DateTimePicker_GetMonthStringId(s, s->dateTime.dt.month);
    DateTimePicker_AddNamedText(s, s->fieldLayer, 0x18e, 8, "st_day_month", r, 0xf, 0);
}

extern "C" u32 DateTimePicker_GetDayStringId(DateTimePicker *s, u32 a) {
    return (u8)(a + 0xc);
}

extern "C" void DateTimePicker_DrawDay(DateTimePicker *s) {
    u32 r = DateTimePicker_GetDayStringId(s, s->dateTime.dt.day);
    DateTimePicker_AddNamedText(s, s->fieldLayer, 0x19e, 5, "st_day_month", r, 0xf, 0);
}

extern "C" void DateTimePicker_DrawHour(DateTimePicker *s) {
    u32 r4 = s->dateTime.dt.hour;
    u32 r1 = 0x37;
    if ((s32)r4 >= 0xc) {
        r1 = 0x38;
    }
    DateTimePicker_AddNamedText(s, s->fieldLayer, 0x1ce, 4, "st_general", r1, 0xf, 0);
    if ((s32)r4 > 0xc) {
        r4 -= 0xc;
    }
    if (r4 == 0) {
        r4 = 0xc;
    }
    DateTimePicker_AddNumberText(s, s->fieldLayer, 0x1b6, 6, r4, 0xf, 0);
}

extern "C" void DateTimePicker_DrawMinute(DateTimePicker *s) {
    DateTimePicker_AddPaddedNumberText(s, s->fieldLayer, 0x1c2, 6, s->dateTime.dt.minute, 0, 0xf, 0);
}

extern "C" void DateTimePicker_DrawPickedValue(DateTimePicker *s) {
    u32 r5 = DateTimePicker_GetFieldWidth(s, s->listField);
    u32 r1 = s->pickedRow;
    u32 r2 = s->listField;
    switch (r2) {
    case 0:
        r1 += 0x7d0;
        break;
    case 1:
    case 2:
        r1 += 1;
        break;
    }
    switch (r2) {
    case 1:
        DateTimePicker_AddNamedText(s, 8, 0xcb, r5, "st_day_month", DateTimePicker_GetMonthStringId(s, r1), 0xf, 0);
        break;
    case 2:
        DateTimePicker_AddNamedText(s, 8, 0xcb, r5, "st_day_month", DateTimePicker_GetDayStringId(s, r1), 0xf, 0);
        break;
    case 3:
        DateTimePicker_AddNamedTextAt(s, 8, 0xcb, r5, "st_general", r1 + 0x1e, 0xf, 0, 0, 6);
        break;
    case 4:
        DateTimePicker_AddPaddedNumberText(s, 8, 0xcb, r5, r1, 0, 0xf, 0);
        break;
    case 0:
    default:
        DateTimePicker_AddNumberText(s, 8, 0xcb, r5, r1, 0xf, 0);
        break;
    }
}

extern "C" void DateTimePicker_ReleaseLabels(DateTimePicker *s) {
    s32 i;
    s->labelCount = 0;
    for (i = 0; i < 0x11; i++) {
        s->labels[i].destroyLabel();
    }
}

extern "C" LabelString *DateTimePicker_AllocLabel(DateTimePicker *s) {
    if (s->labelCount >= 0x11) {
        return &s->labels[16];
    }
    s->labelCount = s->labelCount + 1;
    return &s->labels[s->labelCount - 1];
}

extern "C" void DateTimePicker_AddMenuText(DateTimePicker *s, u32 a, u32 b, u32 c, u8 d, s32 e, u8 f, u8 g) {
    LabelString *p = DateTimePicker_AllocLabel(s);
    String_Load2dMenu(p, d);
    p->createLabel(a, b, c, f, g, 0);
    p->redrawAligned(e, 0);
}

extern "C" void DateTimePicker_AddMenuTextAt(DateTimePicker *s, u32 a, u32 b, u32 c, u8 d, u32 e) {
    LabelString *p = DateTimePicker_AllocLabel(s);
    String_Load2dMenu(p, d);
    p->createLabel(a, b, c, 0xf, 0, 0);
    p->redrawOffset(1, -((c - e) * 4));
}

extern "C" void DateTimePicker_AddNamedText(DateTimePicker *s, u32 a, u32 b, u32 c, const char *d, u32 e, u8 f, u8 g) {
    LabelString *p = DateTimePicker_AllocLabel(s);
    String_LoadByIndex(p, d, e);
    p->createLabel(a, b, c, f, g, 0);
    p->redrawAligned(1, 0);
}

extern "C" void DateTimePicker_AddNamedTextAt(DateTimePicker *s, u32 a, u32 b, u32 c, const char *d, u32 e, u8 f, u8 g, s32 h, s32 i) {
    LabelString *p = DateTimePicker_AllocLabel(s);
    String_LoadByIndex(p, d, e);
    p->createLabel(a, b, c, f, g, 0);
    p->redrawOffset(h, i);
}

extern "C" void DateTimePicker_AddMonthText(DateTimePicker *s, u32 a, u32 b, u32 c, u32 d, u8 e, u8 f) {
    DateTimePicker_AddNamedText(s, a, b, c, "st_day_month", DateTimePicker_GetMonthStringId(s, d), e, f);
}

extern "C" void DateTimePicker_AddListDayText(DateTimePicker *s, u32 a, u32 b, u32 c, u32 d, u8 e, u8 f) {
    LabelString *p = DateTimePicker_AllocLabel(s);
    String_LoadByIndex(p, "st_day_month", DateTimePicker_GetDayStringId(s, d));
    p->createLabel(a, b, c, e, f, 0);
    p->redrawOffset(1, (c - 5) * 4);
}

extern "C" void DateTimePicker_AddListHourText(DateTimePicker *s, u32 a, u32 b, u32 c, u32 d, u8 e, u8 f) {
    LabelString *p = DateTimePicker_AllocLabel(s);
    String_LoadByIndex(p, "st_general", d + 0x1e);
    p->createLabel(a, b, c, e, f, 0);
    p->redrawOffset(0, (c - 6) * 8 + 6);
}

extern "C" void DateTimePicker_AddPaddedNumberText(DateTimePicker *s, u32 a, u32 b, u32 c, u32 d, u32 e, u8 f, u8 g) {
    LabelString *p = DateTimePicker_AllocLabel(s);
    String_FormatNumberWrapper(p, d, 2, 6, 0, 0);
    p->createLabel(a, b, c, f, g, 0);
    if (e != 0) {
        p->redrawOffset(1, (c - e) * 4);
    } else {
        p->redrawAligned(1, 0);
    }
}

extern "C" void DateTimePicker_AddNumberText(DateTimePicker *s, u32 a, u32 b, u32 c, u32 d, u8 e, u8 f) {
    LabelString *p = DateTimePicker_AllocLabel(s);
    String_FormatNumberWrapper(p, d, 4, 0, 0, 0);
    p->createLabel(a, b, c, e, f, 0);
    p->redrawAligned(1, 0);
}

extern "C" void DateTimePicker_AddListNumberText(DateTimePicker *s, u32 a, u32 b, u32 c, u32 d, u32 e, u8 f, u8 g) {
    LabelString *p = DateTimePicker_AllocLabel(s);
    String_FormatNumberWrapper(p, d, 4, 0, 0, 0);
    p->createLabel(a, b, c, f, g, 0);
    p->redrawOffset(1, (c - e) * 4);
}

extern "C" void DateTimePicker_Draw(DateTimePicker *s, s32 a, s32 b) {
    s32 r6 = a + 0x80;
    s32 r7 = b + 0x60;
    if (s->objVariant == 0) {
        s32 p = a + 0x38;
        s32 q = b + 0x34;
        Oam_DrawObj(1, data_ov134_02294e84, p, q, -1, 2, 0);
        Oam_DrawObjRotated(1, &data_ov134_02294e84[1], p, q, -1, 2, 0x1000, s->minuteHandAngle, 0);
        Oam_DrawObjRotated(1, &data_ov134_02294e84[2], p, q, -1, 2, 0x1000, s->hourHandAngle, 0);
    }
    Oam_DrawCell(1, data_ov134_02294d44, r6, r7, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    if (s->testFlags(4)) {
        s->knob.draw();
    }
    if (s->listTopCell != 0) {
        Oam_DrawCell(1, data_ov134_02294d74, s->listX - 8, s->windowTop, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
        Oam_DrawCell(1, s->listTopCell, s->listX - 8, s->windowTop, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
    if (s->listBottomCell != 0) {
        Oam_DrawCell(1, s->listBottomCell, s->listX - 8, s->windowBottom, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
    if (s->pickedRowCell != 0) {
        Oam_DrawCell(1, s->pickedRowCell, s->listX, s->pickedRowY, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
    switch (s->mode) {
    case 0:
        Oam_DrawCell(1, data_ov134_02294db4, r6, r7, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    case 3: {
        s32 i;
        Oam_DrawCell(1, data_ov134_02294f44, r6, r7, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        for (i = 0; i < 5; i++) {
            if (s->mode == 3) {
                if (i == 3) continue;
                if (i == 4) continue;
            }
            Oam_DrawCell(1, data_ov134_02294e9c[i], r6, r7, i == s->cursorField ? 7 : -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        }
        Oam_DrawCell(1, data_ov134_02294e9c[5], r6, r7, s->testFlags(8) ? 10 : 9, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        break;
    }
    case 2: {
        s32 v1, v2;
        u32 b1 = s->cursorField;
        if (b1 == 1) {
            v1 = 7;
            v2 = 6;
        } else if (b1 == 2) {
            v2 = 7;
            v1 = 6;
        } else {
            v1 = 6;
            v2 = 6;
        }
        Oam_DrawCell(1, data_ov134_02295104, r6, r7, v1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        Oam_DrawCell(1, data_ov134_02295034, r6, r7, v2, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        break;
    }
    case 1: {
        s32 v1, v2;
        u32 b1;
        Oam_DrawCell(1, data_ov134_02294d54, r6, r7, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        Oam_DrawCell(1, data_ov134_02295204, r6, r7, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        b1 = s->cursorField;
        if (b1 == 3) {
            v1 = 7;
            v2 = 6;
        } else if (b1 == 4) {
            v2 = 7;
            v1 = 6;
        } else {
            v1 = 6;
            v2 = 6;
        }
        Oam_DrawCell(1, data_ov134_022950d4, r6, r7, v1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        Oam_DrawCell(1, data_ov134_02295014, r6, r7, v2, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        break;
    }
    }
}

extern "C" s32 DateTimePicker_GrabHand(DateTimePicker *s, u32 a, u32 b) {
    s32 r6, r0;
    s32 r4;
    if (!DateTimePicker_IsInClockFace(s, a, b, 0x28)) {
        return FALSE;
    }
    r6 = DateTimePicker_AngleAt(s, a, b);
    r0 = DateTimePicker_AngleDiff(s, r6, s->minuteHandAngle);
    r4 = 0;
    if (r0 >= -0x800 && r0 < 0x800) {
        s->grabbedHand = r4;
        r4 = 1;
        s->lastTickAngle = s->minuteHandAngle;
    } else {
        r0 = DateTimePicker_AngleDiff(s, r6, s->hourHandAngle);
        if (r0 >= -0x800 && r0 < 0x800) {
            r4 = 1;
            s->grabbedHand = r4;
            s->lastTickAngle = s->hourHandAngle;
        }
    }
    if (r4) {
        DateTimePicker_SetCursorField(s, 6);
        MI_CpuCopy8(&s->dateTime.dt, &s->dragDateTime.dt, 8);
        s->clearFlags(0x30);
        return TRUE;
    }
    return FALSE;
}

extern "C" void DateTimePicker_UpdateHandDrag(DateTimePicker *self, s32 x, s32 y) {
    u32 w;
    s32 t;
    switch (self->grabbedHand) {
    case 0:
        DateTimePicker_DragMinuteHand(self, x, y);
        w = self->minuteHandAngle;
        break;
    case 1:
        DateTimePicker_DragHourHand(self, x, y);
        w = self->hourHandAngle;
        break;
    default:
        return;
    }
    t = DateTimePicker_AngleDiff(self, self->lastTickAngle, w);
    if (t < -1000 || t > 1000) {
        Snd_PlaySe(0x1a);
        self->lastTickAngle = w;
    }
}

extern "C" BOOL DateTimePicker_EndHandDrag(DateTimePicker *self) {
    s32 a;
    DateTimePicker_ResetFieldPalettes(self);
    if (self->testFlags(0x40) && self->testFlags(0x10)) {
        a = DateTimePicker_GetField(self, 4);
        self->targetMinutes = a + DateTimePicker_GetField(self, 3) * 0x3c;
        while (self->targetMinutes > self->clockMinutes) {
            self->targetMinutes = self->targetMinutes - 0x2d0;
        }
        Snd_PlaySeOnHandle(0x54);
        return TRUE;
    }
    if (self->testFlags(0x80) && self->testFlags(0x20)) {
        a = DateTimePicker_GetField(self, 4);
        self->targetMinutes = a + DateTimePicker_GetField(self, 3) * 0x3c;
        while (self->targetMinutes < self->clockMinutes) {
            self->targetMinutes = self->targetMinutes + 0x2d0;
        }
        Snd_PlaySeOnHandle(0x54);
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL DateTimePicker_UpdateHandAnim(DateTimePicker *self) {
    if (DateTimePicker_StepHandAnim(self)) {
        DateTimePicker_SyncHands(self);
        return TRUE;
    }
    return FALSE;
}

extern "C" void DateTimePicker_DragMinuteHand(DateTimePicker *self, s32 x, s32 y) {
    s32 t = DateTimePicker_AngleDeltaAt(self, x, y, self->minuteHandAngle);
    if (t != 0) {
        DateTimePicker_AddMinutes(self, (t * 0x3c) >> 16);
    }
}

extern "C" void DateTimePicker_DragHourHand(DateTimePicker *self, s32 x, s32 y) {
    s32 t = DateTimePicker_AngleDeltaAt(self, x, y, self->hourHandAngle);
    if (t != 0) {
        DateTimePicker_AddMinutes(self, (t * 0x2d0) >> 16);
    }
}

extern "C" void DateTimePicker_SetHands(DateTimePicker *self, u8 a, u8 b) {
    self->clockMinutes = a * 0x3c + b;
    if (a >= 0xc) {
        a = a - 0xc;
    }
    self->hourHandAngle = ((b + a * 0x3c) << 16) / 0x2d0;
    self->minuteHandAngle = b * 0x444;
}

extern "C" void DateTimePicker_SyncHands(DateTimePicker *self) {
    DateTimePicker_SetHands(self, self->dateTime.dt.hour, self->dateTime.dt.minute);
}

extern "C" void DateTimePicker_SetHandsFromMinutes(DateTimePicker *self) {
    s32 t = self->clockMinutes;
    while (t < 0) t += 0x2d0;
    while (t >= 0x2d0) t -= 0x2d0;
    self->hourHandAngle = (t << 16) / 0x2d0;
    self->minuteHandAngle = (t % 0x3c) * 0x444;
}

extern "C" s32 DateTimePicker_AngleAt(void *self, s32 x, s32 y) {
    return Math_Atan2((x - 0x38) << 12, -(y - 0x34) << 12);
}

extern "C" s32 DateTimePicker_AngleDeltaAt(DateTimePicker *self, s32 x, s32 y, s32 t) {
    if (x == 0x38 && y == 0x34) {
        return 0;
    }
    return DateTimePicker_AngleDiff(self, DateTimePicker_AngleAt(self, x, y), t);
}

extern "C" s32 DateTimePicker_AngleDiff(void *self, s32 a, s32 b) {
    s32 x = a - b;
    s32 y = b - a;
    while (x < 0) x += 0x10000;
    while (x >= 0x10000) x -= 0x10000;
    while (y < 0) y += 0x10000;
    while (y >= 0x10000) y -= 0x10000;
    if (x > y) {
        x = -y;
    }
    return x;
}

extern "C" BOOL DateTimePicker_IsInClockFace(void *self, s32 x, s32 y, s32 r) {
    s32 dx = x - 0x38;
    dx = dx * dx;
    s32 dy = y - 0x34;
    dy = dy * dy;
    if (dx + dy < r * r) return TRUE;
    return FALSE;
}

extern "C" void DateTimePicker_AddMinutes(DateTimePicker *self, s32 delta) {
    u8 buf[6];
    s32 i;
    BOOL r;
    s32 v;
    ClockDateTime *pc;
    if (delta == 0) return;
    for (i = 0; i <= 4; i++) {
        buf[i] = DateTimePicker_GetField(self, i);
    }
    buf[5] = 0;
    if (delta > 0) {
        DateTime_AddMinutes(&self->dragDateTime.dt, delta);
    } else {
        DateTime_SubMinutes(&self->dragDateTime.dt, -delta);
    }
    r = TRUE;
    if (self->testFlags(0x40)) {
        if (DateTime_Compare(&self->maxDateTime.dt, &self->dragDateTime.dt, 0x3f) == -1) {
            v = DateTime_DiffMinutes(&self->maxDateTime.dt, &self->dragDateTime.dt);
            r = FALSE;
            MI_CpuCopy8(&self->maxDateTime.dt, &self->dateTime.dt, 8);
            self->setFlags(0x10);
            pc = &self->dragDateTime.dt;
            while (v >= 0x2d0) {
                DateTime_SubHours(pc, 0xc);
                v -= 0x2d0;
            }
        } else {
            self->clearFlags(0x10);
        }
    }
    if (self->testFlags(0x80)) {
        if (DateTime_Compare(&self->minDateTime.dt, &self->dragDateTime.dt, 0x3f) == 1) {
            v = DateTime_DiffMinutes(&self->dragDateTime.dt, &self->minDateTime.dt);
            r = FALSE;
            MI_CpuCopy8(&self->minDateTime.dt, &self->dateTime.dt, 8);
            self->setFlags(0x20);
            pc = &self->dragDateTime.dt;
            while (v >= 0x2d0) {
                DateTime_AddHours(pc, 0xc);
                v -= 0x2d0;
            }
        } else {
            self->clearFlags(0x20);
        }
    }
    if (r) {
        MI_CpuCopy8(&self->dragDateTime.dt, &self->dateTime.dt, 8);
        DateTimePicker_SyncHands(self);
    } else {
        DateTimePicker_SetHands(self, self->dragDateTime.dt.hour, self->dragDateTime.dt.minute);
    }
    for (i = 0; i <= 4; i++) {
        if (buf[i] != DateTimePicker_GetField(self, i)) {
            self->fieldFlash[i] = 10;
            DateTimePicker_SetFieldPalette(self, i, 5);
            DateTimePicker_DrawField(self, i);
            if (i >= 0 && i <= 2) {
                buf[5] = 1;
            }
        }
    }
    if (buf[5] != 0) {
        self->fieldFlash[5] = 10;
        DateTimePicker_SetFieldPalette(self, 5, 5);
        DateTimePicker_DrawWeekday(self);
    }
}

extern "C" BOOL DateTimePicker_Approach(void *self, s32 *p, s32 target, s32 maxstep, s32 minstep) {
    s32 d;
    s32 step;
    s32 cur = *p;
    if (cur > target) { d = cur - target; } else { d = target - cur; }
    if (d < minstep) { *p = target; return TRUE; }
    step = d >> 1;
    if (step > maxstep) { step = maxstep; } else if (step < minstep) { step = minstep; }
    if (cur > target) { *p = *p - step; } else { *p = *p + step; }
    return FALSE;
}

extern "C" BOOL DateTimePicker_StepHandAnim(DateTimePicker *self) {
    BOOL r;
    if (self->clockMinutes == self->targetMinutes) {
        r = TRUE;
    } else {
        r = DateTimePicker_Approach(self, &self->clockMinutes, self->targetMinutes, 0x30, 3);
        DateTimePicker_SetHandsFromMinutes(self);
    }
    if (r == TRUE) {
        Snd_StopSe(0x54, 1);
        Snd_PlaySe(0x2e);
    }
    return r;
}

extern "C" s32 DateTimePicker_HitTestField(DateTimePicker *self, s32 x, s32 y) {
    s32 i;
    s32 hx = x >> 3;
    s32 hy = y >> 3;
    for (i = 0; i <= 4; i++) {
        if (DateTimePicker_GetFieldLeft(self, i) > hx) continue;
        if (Unk_ov134_02293510_Hi(self, i, 0) < hx) continue;
        if (DateTimePicker_GetFieldTop(self, i) > hy) continue;
        if (DateTimePicker_GetFieldBottom(self, i) < hy) continue;
        return i;
    }
    return 6;
}

extern "C" s32 DateTimePicker_HitTestDateField(DateTimePicker *self, s32 x, s32 y) {
    s32 i;
    s32 hx = x >> 3;
    s32 hy = y >> 3;
    for (i = 0; i <= 2; i++) {
        if (DateTimePicker_GetFieldLeft(self, i) > hx) continue;
        if (Unk_ov134_02293510_Hi(self, i, 3) < hx) continue;
        if (DateTimePicker_GetFieldTop(self, i) > hy) continue;
        if (DateTimePicker_GetFieldBottom(self, i) < hy) continue;
        return i;
    }
    return 6;
}

extern "C" s32 DateTimePicker_HitTestMonthDayField(DateTimePicker *self, s32 x, s32 y) {
    s32 i;
    s32 hx = x >> 3;
    s32 hy = y >> 3;
    for (i = 1; i <= 2; i++) {
        if (DateTimePicker_GetFieldLeft(self, i) > hx) continue;
        if (Unk_ov134_02293510_Hi(self, i, 0) < hx) continue;
        if (DateTimePicker_GetFieldTop(self, i) > hy) continue;
        if (DateTimePicker_GetFieldBottom(self, i) < hy) continue;
        return i;
    }
    return 6;
}

extern "C" s32 DateTimePicker_HitTestTimeField(DateTimePicker *self, s32 x, s32 y) {
    s32 i;
    s32 hx = x >> 3;
    s32 hy = y >> 3;
    for (i = 3; i <= 4; i++) {
        if (DateTimePicker_GetFieldLeft(self, i) > hx) continue;
        if (Unk_ov134_02293510_Hi(self, i, 0) < hx) continue;
        if (DateTimePicker_GetFieldTop(self, i) > hy) continue;
        if (DateTimePicker_GetFieldBottom(self, i) < hy) continue;
        return i;
    }
    return 6;
}

extern "C" s32 DateTimePicker_GetFieldLeft(DateTimePicker *self, s32 i) {
    u32 m = self->mode;
    if (m == 2) return sFieldLeftBirthday[i];
    if (m == 1) return sFieldLeftTime[i];
    return sFieldLeftDefault[i];
}

extern "C" s32 DateTimePicker_GetFieldTop(DateTimePicker *self, s32 i) {
    u32 m = self->mode;
    if (m == 2) return sFieldTopBirthday[i];
    if (m == 1) return sFieldTopTime[i];
    return sFieldTopDefault[i];
}

extern "C" s32 DateTimePicker_GetFieldWidth(DateTimePicker *self, s32 i) {
    return sFieldWidths[i];
}

extern "C" s32 DateTimePicker_GetFieldRight(DateTimePicker *self, s32 i) {
    s32 a = DateTimePicker_GetFieldLeft(self, i);
    return a + DateTimePicker_GetFieldWidth(self, i) - 1;
}

extern "C" s32 DateTimePicker_GetFieldBottom(DateTimePicker *self, s32 i) {
    return DateTimePicker_GetFieldTop(self, i) + 1;
}

extern "C" void DateTimePicker_SetFieldPalette(DateTimePicker *self, s32 idx, s32 x) {
    s32 t;
    s32 a;
    s32 b;
    s32 c;
    if (self->mode == 1) {
        if (idx == 0) return;
        if (idx == 1 || idx == 2 || idx == 5) {
            if (x == 3) x = 4;
            if (x == 5) x = 7;
        }
    } else if (self->mode == 2) {
        if (idx != 1 && idx != 2) return;
    }
    if (idx == 5 && x == 3) {
        if (Date_GetWeekday(self->dateTime.dt.year, self->dateTime.dt.month, self->dateTime.dt.day) == 0) {
            x = 8;
            self->setFlags(x);
        } else {
            self->clearFlags(8);
        }
    }
    if (self->cursorField == idx && x == 3) x = 5;
    t = DateTimePicker_GetFieldLeft(self, idx);
    a = DateTimePicker_GetFieldTop(self, idx);
    b = DateTimePicker_GetFieldRight(self, idx);
    c = DateTimePicker_GetFieldBottom(self, idx);
    BgScreen_SetRectPalette(self->fieldScreen, t, a, b, c, x);
    self->setFlags(2);
}

extern "C" void DateTimePicker_SetDropButtonPalette(DateTimePicker *self, s32 a, s32 b) {
    s32 x = DateTimePicker_GetFieldRight(self, a) + 1;
    s32 y = DateTimePicker_GetFieldTop(self, a);
    s32 z;
    if (self->mode == 0 && a == 3) {
        z = x + 1;
    } else {
        z = x + 2;
    }
    BgScreen_SetRectPalette(self->fieldScreen, x, y, z, y + 1, b);
    self->setFlags(2);
}

extern "C" void DateTimePicker_ResetFieldPalettes(DateTimePicker *self) {
    s32 i;
    s32 j;
    for (i = 0; i <= 5; i++) {
        DateTimePicker_SetFieldPalette(self, i, 3);
    }
    for (j = 0; j <= 5; j++) {
        self->fieldFlash[j] = 0;
    }
}

extern "C" void DateTimePicker_TickFieldFlash(DateTimePicker *self) {
    s32 i;
    for (i = 0; i <= 5; i++) {
        if (self->fieldFlash[i] != 0) {
            self->fieldFlash[i] = self->fieldFlash[i] - 1;
            if (self->fieldFlash[i] == 0) {
                DateTimePicker_SetFieldPalette(self, i, 3);
            }
        }
    }
}

extern "C" u8 DateTimePicker_GetCursorField(DateTimePicker *self) {
    return self->cursorField;
}

extern "C" void DateTimePicker_SetCursorField(DateTimePicker *self, u8 v) {
    u32 old = self->cursorField;
    if (old == v) return;
    self->cursorField = v;
    if (old != 6) {
        DateTimePicker_SetFieldPalette(self, old, 3);
    }
    if (v != 6) {
        DateTimePicker_SetFieldPalette(self, v, 3);
    }
}

extern "C" void DateTimePicker_AdvanceCursorField(DateTimePicker *self) {
    switch (self->mode) {
    case 0:
    case 1:
        if (self->cursorField < 4) {
            DateTimePicker_SetCursorField(self, self->cursorField + 1);
        } else {
            DateTimePicker_SetCursorField(self, 6);
        }
        break;
    case 2:
    case 3:
        if (self->cursorField < 2) {
            DateTimePicker_SetCursorField(self, self->cursorField + 1);
        } else {
            DateTimePicker_SetCursorField(self, 6);
        }
        break;
    }
}

extern "C" void DateTimePicker_OpenList(DateTimePicker *self, s32 idx) {
    s32 h, lim, i, j, off;
    s32 z;
    s32 r6;
    u16 *row;
    Snd_PlaySe(0x13);
    self->listField = idx;
    self->listState = 0;
    Gfx2d_HideLayer(self->listLayer);
    self->listFieldLeft = DateTimePicker_GetFieldLeft(self, idx);
    self->listFieldTop = DateTimePicker_GetFieldTop(self, idx);
    MIi_CpuCopy16(self->listScreenBase, self->listScreenWork, 0x800);
    h = DateTimePicker_GetFieldWidth(self, idx);
    lim = 8 - h;
    row = self->listScreenWork;
    i = 0;
    off = (lim - 1) & 0x1f;
    z = 0;
    for (; i < 0x20; row += 0x20, i++) {
        for (j = z; j < lim; j++) {
            row[j] = 0x10;
        }
        row[off] = 0x3079;
    }
    self->listOffsetX = (self->listFieldLeft - lim) << 3;
    self->listTop = 0x28;
    self->listCount = sFieldValueCounts[idx];
    if (idx == 2) {
        self->listCount = Date_GetDaysInMonth(self->dateTime.dt.year, self->dateTime.dt.month);
    }
    self->scrollMax = (self->listCount - 8) << 4;
    for (i = 0; i < 0x10; i++) {
        self->rowCache[i] = 0xff;
    }
    r6 = DateTimePicker_GetField(self, self->listField);
    if ((u8)(self->listField + 0xff) <= 1) {
        r6 = (u8)(r6 - 1);
    }
    {
        s32 v = (r6 << 4) - ((self->listFieldTop << 3) - self->listTop);
        if (v < 0) {
            v = 0;
        } else if (v > self->scrollMax) {
            v = self->scrollMax;
        }
        DateTimePicker_SetListScroll(self, v);
    }
    self->syncKnobToScroll();
    DateTimePicker_SetCursorField(self, (u8)idx);
    self->listX = DateTimePicker_GetFieldLeft(self, self->listField) << 3;
    self->listFieldBottomY = DateTimePicker_GetFieldBottom(self, idx) << 3;
    self->windowTop = self->listFieldBottomY - 8;
    self->windowBottom = self->listFieldBottomY + 8;
    DateTimePicker_AddMenuTextAt(self, 8, 0x1aa, 8, sFieldNameTextIds[idx], h + 1);
    self->listTopCell = data_ov134_02294f14[idx];
    self->listBottomCell = data_ov134_02294f2c[idx];
    self->listAnimTimer = 3;
    Gfx2d_DisableSubWindows(1);
    Gfx2d_SetSubWin0Planes(0x1f, 1);
    Gfx2d_SetSubWinOutPlanes(~Gfx2d_GetLayerPlaneMask(self->listLayer) & 0x1f);
    self->blendListPalette(0);
    self->listCursorRow = r6 + 1;
    self->pendingScroll = 0;
}

extern "C" s32 DateTimePicker_UpdateListOpen(DateTimePicker *self) {
    switch (self->listState) {
    case 0:
        self->listState = 1;
        Gfx2d_ShowLayer(self->listLayer);
        Gfx2d_EnableSubWindows(1);
        self->listAnimTimer = self->listAnimTimer - (TICK_STEP_ENDS() ? 1 : 0);
        DateTimePicker_AnimOpenWindow(self);
        break;
    case 1:
        if (self->listAnimTimer != 0) {
            self->listAnimTimer = self->listAnimTimer - (TICK_STEP_ENDS() ? 1 : 0);
            DateTimePicker_AnimOpenWindow(self);
        } else {
            Gfx2d_DisableSubWindows(1);
            self->listState = 2;
            self->listAnimTimer = 0;
            self->setFlags(4);
            self->knobX = DateTimePicker_GetFieldRight(self, self->listField) << 3;
            self->placeKnob();
        }
        break;
    case 2:
        if (self->listAnimTimer < 3) {
            self->listAnimTimer = self->listAnimTimer + (TICK_STEP_ENDS() ? 1 : 0);
            self->blendListPalette(self->listAnimTimer);
        } else {
            self->listState = 8;
        }
        break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        break;
    case 8:
        return 1;
    }
    return 0;
}

extern "C" s32 DateTimePicker_HitTestRow(DateTimePicker *self, s32 x, s32 y) {
    s32 r6, u, m, t, r4;
    if (y <= 0x28 || y >= 0xa8) {
        return 0;
    }
    r6 = x >> 3;
    if (DateTimePicker_GetFieldLeft(self, self->listField) > r6 || DateTimePicker_GetFieldRight(self, self->listField) < r6) {
        return 0;
    }
    u = self->listScroll;
    m = u & 15;
    if (y >= 0xb2 - m) {
        return 2;
    }
    if (y <= (((16 - m) & 15) + 0x1e)) {
        return 2;
    }
    t = y - (self->listTop - u);
    if (t < 0) {
        return 2;
    }
    r4 = t >> 4;
    if (r4 >= self->listCount) {
        return 2;
    }
    if (self->isRowDisabled(r4)) {
        return 2;
    }
    self->pickedRow = r4;
    return 1;
}

extern "C" void DateTimePicker_DecideList(DateTimePicker *self) {
    Snd_PlaySe(0x29);
    self->listState = 3;
    self->listAnimTimer = 3;
    Gfx2d_DisableSubWindows(1);
    Gfx2d_SetSubWin0Planes(0x1f, 1);
    Gfx2d_SetSubWinOutPlanes(~Gfx2d_GetLayerPlaneMask(self->listLayer) & 0x1f);
    DateTimePicker_DrawPickedValue(self);
    self->pickedRowY = self->listTop + (self->pickedRow << 4) - self->listScroll;
    self->clearFlags(4);
}

extern "C" void DateTimePicker_CancelList(DateTimePicker *self) {
    Snd_PlaySe(0x2a);
    self->listState = 4;
    self->listAnimTimer = 3;
    Gfx2d_DisableSubWindows(1);
    Gfx2d_SetSubWin0Planes(0x1f, 1);
    Gfx2d_SetSubWinOutPlanes(~Gfx2d_GetLayerPlaneMask(self->listLayer) & 0x1f);
    self->clearFlags(4);
}

extern "C" s32 DateTimePicker_UpdateListClose(DateTimePicker *self) {
    switch (self->listState) {
    case 0:
    case 1:
    case 2:
        break;
    case 3:
        self->listState = 5;
        self->pickedRowCell = data_ov134_02294f5c[self->listField];
        break;
    case 4:
        self->listState = 5;
        break;
    case 5:
        if (self->listAnimTimer != 0) {
            self->listAnimTimer = self->listAnimTimer - (TICK_STEP_ENDS() ? 1 : 0);
            self->blendListPalette(self->listAnimTimer);
        } else {
            Snd_PlaySe(0x14);
            self->listState = 6;
            self->listAnimTimer = 3;
            Gfx2d_EnableSubWindows(1);
            self->listAnimTimer = self->listAnimTimer - (TICK_STEP_ENDS() ? 1 : 0);
            DateTimePicker_AnimCloseWindow(self);
        }
        break;
    case 6:
        if (self->listAnimTimer != 0) {
            self->listAnimTimer = self->listAnimTimer - (TICK_STEP_ENDS() ? 1 : 0);
            DateTimePicker_AnimCloseWindow(self);
        } else {
            Gfx2d_HideLayer(self->listLayer);
            Gfx2d_DisableSubWindows(1);
            DateTimePicker_SetDropButtonPalette(self, self->listField, 3);
            self->listTopCell = 0;
            self->listBottomCell = 0;
            if (self->pickedRowCell != 0) {
                if (self->applyPickedValue()) {
                    self->listState = 7;
                    Snd_PlaySeOnHandle(0x54);
                } else {
                    self->listState = 8;
                }
                self->pickedRowCell = 0;
                DateTimePicker_AdvanceCursorField(self);
            } else {
                self->listState = 8;
            }
        }
        break;
    case 7:
        if (DateTimePicker_StepHandAnim(self)) {
            DateTimePicker_SyncHands(self);
            self->listState = 8;
        }
        break;
    case 8:
        return 1;
    }
    return 0;
}

extern "C" s32 DateTimePicker_HitTestList(DateTimePicker *self, s32 x, s32 y) {
    switch (DateTimePicker_HitTestRow(self, x, y)) {
    case 1:
        return 0;
    case 2:
        return 4;
    }
    if (self->grabKnobAt(x, y)) {
        return 3;
    }
    if (y >= 0x20 && y <= 0xa8) {
        s32 t = self->knobX;
        if (x <= t + 0x18 && x >= t) {
            self->knob.grab();
            return 2;
        }
    }
    return 1;
}

extern "C" void DateTimePicker_SetListScroll(DateTimePicker *self, s32 a) {
    self->listScroll = a;
    DateTimePicker_ApplyListScroll(self);
    DateTimePicker_RedrawList(self);
}

extern "C" void DateTimePicker_ApplyListScroll(DateTimePicker *self) {
    Gfx2d_SetLayerOffset(self->listLayer, -self->listOffsetX, -(self->listTop - self->listScroll));
}

extern "C" void DateTimePicker_RedrawList(DateTimePicker *self) {
    u16 *row;
    s32 dx, h, lim, off, i, j, k, t;
    u32 c, ac;
    MIi_CpuCopy16(self->listScreenWork, self->listScreen, 0x800);
    dx = self->listTop - self->listScroll;
    h = DateTimePicker_GetFieldWidth(self, self->listField);
    lim = 8 - DateTimePicker_GetFieldWidth(self, self->listField);
    if (dx > 0) {
        i = (16 - ((dx + 15) >> 4)) * 2;
        row = &self->listScreen[i << 5];
        for (; i < 0x20; row += 0x20, i++) {
            for (j = lim; j < 8; j++) {
                row[j] = 0x3074;
            }
        }
    }
    off = (self->listScroll - self->listTop) >> 4;
    for (k = 0; k < 0x10; k++) {
        s32 r5 = k + off;
        s32 r6 = r5 & 15;
        if (r5 < 0 || r5 >= self->listCount) {
            continue;
        }
        if (self->isRowDisabled(r5)) {
            BgScreen_SetRectPalette(self->listScreen, lim, r6 * 2, 7, r6 * 2 + 1, 6);
        }
        if (r5 == self->rowCache[r6]) {
            continue;
        }
        self->rowCache[r6] = r5;
        c = self->listField;
        if (c == 0) {
            r5 += 0x7d0;
        }
        if ((u8)(c + 0xff) <= 1) {
            r5++;
        }
        switch (c) {
        case 1:
            DateTimePicker_AddMonthText(self, self->listLayer, (r6 << 4) + 0x80, 8, r5, 15, 14);
            break;
        case 2:
            DateTimePicker_AddListDayText(self, self->listLayer, (r6 << 4) + 0x80, 8, r5, 15, 14);
            break;
        case 3:
            DateTimePicker_AddListHourText(self, self->listLayer, (r6 << 4) + 0x80, 8, r5, 15, 14);
            break;
        case 4:
            DateTimePicker_AddPaddedNumberText(self, self->listLayer, (r6 << 4) + 0x80, 8, r5, h, 15, 14);
            break;
        case 0:
        default:
            DateTimePicker_AddListNumberText(self, self->listLayer, (r6 << 4) + 0x80, 8, r5, h, 15, 14);
            break;
        }
    }
    ac = self->listCount;
    t = self->listTop - self->listScroll;
    t = t + (ac << 4);
    if (t < 0xc0) {
        s32 yb;
        s32 n;
        u16 *rowb;
        s32 jb;
        s32 ib;
        n = ((0xcf - t) >> 4) << 1;
        yb = (ac << 1) & 0x1f;
        for (ib = 0; ib < n; ib++) {
            rowb = &self->listScreen[yb << 5];
            for (jb = lim; jb < 8; jb++) {
                rowb[jb] = 0x3074;
            }
            yb = (yb + 1) & 0x1f;
        }
    }
    {
        s32 y;
        u16 *row2;
        s32 i2;
        s32 j2;
        y = ((self->listScroll - self->listTop + 0x20) & 0xff) >> 3;
        for (i2 = 0; i2 < 5; i2++) {
            row2 = &self->listScreen[y << 5];
            for (j2 = 0; j2 < 10; j2++) {
                row2[j2] = 0x10;
            }
            row2[0x1f] = 0x10;
            y = (y - 1) & 0x1f;
        }
    }
    {
        s32 y;
        u16 *row2;
        s32 i2;
        s32 j2;
        y = ((self->listScroll - self->listTop + 0xb0) & 0xff) >> 3;
        for (i2 = 0; i2 < 3; i2++) {
            row2 = &self->listScreen[y << 5];
            for (j2 = 0; j2 < 10; j2++) {
                row2[j2] = 0x10;
            }
            row2[0x1f] = 0x10;
            y = (y + 1) & 0x1f;
        }
    }
    self->setFlags(1);
}

extern "C" void DateTimePicker_AnimOpenWindow(DateTimePicker *self) {
    if (self->listAnimTimer != 0) {
        self->windowTop = (self->windowTop + 0x28) >> 1;
        self->windowBottom = (self->windowBottom + 0xa8) >> 1;
    } else {
        self->windowTop = 0x28;
        self->windowBottom = 0xa8;
    }
    Gfx2d_SetWindowRect(2, 0, self->windowTop, 0xff, self->windowBottom);
}

extern "C" void DateTimePicker_AnimCloseWindow(DateTimePicker *self) {
    if (self->listAnimTimer != 0) {
        self->windowTop = (self->listFieldBottomY - 8 + self->windowTop) >> 1;
        self->windowBottom = (self->listFieldBottomY + 8 + self->windowBottom) >> 1;
    } else {
        self->windowTop = self->listFieldBottomY - 8;
        self->windowBottom = self->listFieldBottomY + 8;
    }
    Gfx2d_SetWindowRect(2, 0, self->windowTop, 0xff, self->windowBottom);
    s32 v = self->windowTop;
    if (self->pickedRowY < v) {
        self->pickedRowY = v;
    }
    v = self->windowBottom - 8;
    if (self->pickedRowY > v) {
        self->pickedRowY = v;
    }
}

BOOL DateTimePicker::applyPickedValue() {
    u16 m = 0;
    u32 cur = DateTimePicker_GetField(this, listField);
    DateTimePicker_SetField(this, listField, pickedRow);
    m |= 1 << listField;
    s32 r = Date_GetDaysInMonth(dateTime.dt.year, dateTime.dt.month);
    if (r < dateTime.dt.day) {
        dateTime.dt.day = r;
        m |= 4;
    }
    if (listField <= 2) {
        DateTimePicker_SetFieldPalette(this, 5, 3);
        m |= 0x20;
    }
    s32 dir = 0;
    if (listField == 3 && mode == 1) {
        u8 lo = minHour;
        if (cur < lo) {
            if (pickedRow >= lo) {
                DateTime_SubDays(&dateTime.dt, 1);
                dir = -1;
            }
        } else {
            if (pickedRow < lo) {
                DateTime_AddDays(&dateTime.dt, 1);
                dir = 1;
            }
        }
        if (dir != 0) {
            m |= 0x27;
        }
    }
    if (testFlags(0x80)) {
        if (DateTime_Compare(&minDateTime.dt, &dateTime.dt, 0x3f) == 1) {
            MI_CpuCopy8(&minDateTime.dt, &dateTime.dt, 8);
            m = 0xffff;
        }
    }
    if (testFlags(0x40)) {
        if (DateTime_Compare(&maxDateTime.dt, &dateTime.dt, 0x3f) == -1) {
            MI_CpuCopy8(&maxDateTime.dt, &dateTime.dt, 8);
            m = 0xffff;
        }
    }
    u8 i;
    for (i = 0; i <= 5; i++) {
        if (m & (1 << i)) {
            DateTimePicker_DrawField(this, i);
        }
    }
    if ((u8)(listField + 0xfd) <= 1) {
        if (cur == pickedRow) {
            return FALSE;
        }
        u32 a = DateTimePicker_GetField(this, 4);
        u32 b = DateTimePicker_GetField(this, 3);
        targetMinutes = a + b * 0x3c;
        targetMinutes = targetMinutes + dir * 0x5a0;
        return TRUE;
    }
    return FALSE;
}

BOOL DateTimePicker::isAboveMaximum(s32 v, u8 n) {
    u8 i;
    for (i = 0; i < n; i++) {
        u32 a = DateTimePicker_GetField(this, i);
        if (a != DateTimePicker_GetFieldOf(this, i, &maxDateTime.dt)) {
            return FALSE;
        }
    }
    if (v > (s32)DateTimePicker_GetFieldOf(this, n, &maxDateTime.dt)) {
        return TRUE;
    }
    return FALSE;
}

BOOL DateTimePicker::isBelowMinimum(s32 v, u8 n) {
    u8 i;
    for (i = 0; i < n; i++) {
        u32 a = DateTimePicker_GetField(this, i);
        if (a != DateTimePicker_GetFieldOf(this, i, &minDateTime.dt)) {
            return FALSE;
        }
    }
    if (v < (s32)DateTimePicker_GetFieldOf(this, n, &minDateTime.dt)) {
        return TRUE;
    }
    return FALSE;
}

BOOL DateTimePicker::isRowDisabled(s32 v) {
    u32 t = listField;
    if (t == 1) goto inc;
    if (t == 2) {
inc:
        v++;
    }
    if (mode == 1 && t == 3) {
        u8 hi = maxHour;
        u8 lo = minHour;
        if (lo < hi) {
            if (v < lo || v > hi) {
                return TRUE;
            }
        } else {
            if (v < lo && v > hi) {
                return TRUE;
            }
        }
        return FALSE;
    }
    if (testFlags(0x80)) {
        if (isBelowMinimum(v, listField)) {
            return TRUE;
        }
    }
    if (testFlags(0x40)) {
        return isAboveMaximum(v, listField);
    }
    return FALSE;
}

BOOL DateTimePicker::grabKnobAt(s32 x, s32 y) {
    if (knob.hitTest(x, y)) {
        knobGrabOffset = knobY - y;
        knob.grab();
        knobLastTickY = knobY;
        return TRUE;
    }
    return FALSE;
}

BOOL DateTimePicker::grabKnobByCursor() {
    if (listCursorRow == 0) {
        knob.grab();
        Menu_PlayScrollGrabSe();
        return TRUE;
    }
    return FALSE;
}

void DateTimePicker::onKnobMoved() {
    syncScrollToKnob();
    placeKnob();
    s32 t = knobLastTickY - knobY;
    if (t >= 4 || t <= -4) {
        Menu_PlayScrollTickSe();
        knobLastTickY = knobY;
    }
}

void DateTimePicker::dragKnob(s32 x) {
    knobY = x + knobGrabOffset;
    if (knobY < 0x20) {
        knobY = 0x20;
    }
    if (knobY > 0xa0) {
        knobY = 0xa0;
    }
    onKnobMoved();
}

void DateTimePicker::dragKnobToward(s32 x) {
    x -= 8;
    if (x < 0x20) {
        x = 0x20;
    }
    if (x > 0xa0) {
        x = 0xa0;
    }
    Math_StepS32(&knobY, x, 8);
    onKnobMoved();
}

void DateTimePicker::moveKnobByPad() {
    s32 old = knobY;
    u32 k = gPad;
    if (k & 0x40) {
        knobY = old - 4;
        if (knobY < 0x20) {
            knobY = 0x20;
        }
    } else if (k & 0x80) {
        knobY = old + 4;
        if (knobY > 0xa0) {
            knobY = 0xa0;
        }
    }
    if (old != knobY) {
        syncScrollToKnob();
        placeKnob();
        Menu_PlayScrollTickSe();
    }
}

void DateTimePicker::releaseKnob() {
    knob.release();
}

BOOL DateTimePicker::finishKnobRelease() {
    if (knob.areAnimsDone()) {
        knob.show();
        return TRUE;
    }
    return FALSE;
}

void DateTimePicker::syncKnobToScroll() {
    knobY = _s32_div_f(listScroll << 7, scrollMax) + 0x20;
    placeKnob();
}

void DateTimePicker::syncScrollToKnob() {
    DateTimePicker_SetListScroll(this, _s32_div_f(scrollMax * (knobY - 0x20), 0x80));
    pendingScroll = 0;
}

void DateTimePicker::placeKnob() {
    knob.moveTo(knobX - 0x78, knobY - 0x60);
}

s32 DateTimePicker::getListCursorX() {
    if (listCursorRow == 0) {
        return knob.getGripX();
    }
    return knobX;
}

s32 DateTimePicker::getListCursorY() {
    if (listCursorRow == 0) {
        return knob.getGripY();
    }
    return listTop + ((listCursorRow - 1) << 4) - listScroll + 8 - pendingScroll;
}

void DateTimePicker::setListCursorFromY(s32 y) {
    if (listCursorRow != 0) {
        if (y < 0x28) {
            y = 0x28;
        } else if (y > 0xa8) {
            y = 0xa8;
        }
        listCursorRow = rowAtY(y) + 1;
    }
}

s32 DateTimePicker::navigateList(u32 pad) {
    if (listCursorRow == 0) {
        listKeyHoldCount = 0;
        if (MenuKeys_HasLeft(pad)) {
            listCursorRow = 1;
            setListCursorFromY(knob.getGripY());
            return 1;
        }
    } else {
        if (MenuKeys_HasRight(pad)) {
            listCursorRow = 0;
            listKeyHoldCount = 0;
            return 1;
        }
        s32 v = listKeyHoldCount;
        if (v >= 6) {
            if (gPad & 0x40) {
                if (moveListCursorUp()) {
                    if (pendingScroll != 0) {
                        DateTimePicker_SetListScroll(this, listScroll + pendingScroll);
                        pendingScroll = 0;
                        syncKnobToScroll();
                    }
                    if (testFlags(0x100)) {
                        clearFlags(0x100);
                        Snd_PlaySe(0xb);
                    } else {
                        setFlags(0x100);
                    }
                    return 3;
                }
            } else {
                listKeyHoldCount = 0;
            }
        } else if (v <= -6) {
            if (gPad & 0x80) {
                if (moveListCursorDown()) {
                    if (pendingScroll != 0) {
                        DateTimePicker_SetListScroll(this, listScroll + pendingScroll);
                        pendingScroll = 0;
                        syncKnobToScroll();
                    }
                    if (testFlags(0x100)) {
                        clearFlags(0x100);
                        Snd_PlaySe(0xb);
                    } else {
                        setFlags(0x100);
                    }
                    return 3;
                }
            } else {
                listKeyHoldCount = 0;
            }
        }
        if (MenuKeys_HasUp(pad)) {
            s32 t = listKeyHoldCount;
            if (t < 0) {
                listKeyHoldCount = 1;
            } else {
                listKeyHoldCount = t + 1;
            }
            if (moveListCursorUp()) {
                return 2;
            }
        } else if (MenuKeys_HasDown(pad)) {
            s32 t = listKeyHoldCount;
            if (t > 0) {
                listKeyHoldCount = -1;
            } else {
                listKeyHoldCount = t - 1;
            }
            if (moveListCursorDown()) {
                return 2;
            }
        }
    }
    return 0;
}

BOOL DateTimePicker::pickListCursorRow() {
    s32 t = listCursorRow - 1;
    if (isRowDisabled(t)) {
        return FALSE;
    }
    pickedRow = t;
    return TRUE;
}

BOOL DateTimePicker::moveListCursorUp() {
    if (listCursorRow > 1) {
        listCursorRow = listCursorRow - 1;
        s32 t = getListCursorY();
        if (t < 0x30) {
            pendingScroll = pendingScroll - (0x30 - t);
        }
        return TRUE;
    }
    return FALSE;
}

BOOL DateTimePicker::moveListCursorDown() {
    if ((s32)listCursorRow < (s32)listCount) {
        listCursorRow = listCursorRow + 1;
        s32 t = getListCursorY();
        if (t > 0xa0) {
            pendingScroll = pendingScroll + (t - 0xa0);
        }
        return TRUE;
    }
    return FALSE;
}

s32 DateTimePicker::rowAtY(s32 y) {
    s32 d = listTop;
    d -= listScroll;
    s32 v = y - d;
    if (v < 0) {
        v = 0;
    }
    v >>= 4;
    s32 lim = listCount;
    if (v >= lim) {
        v = lim - 1;
    }
    return v;
}

void DateTimePicker::stepListScroll() {
    if (testFlags(1)) {
        return;
    }
    s32 a = listScroll;
    s32 b = pendingScroll;
    if (b > 0) {
        if (b < 8) {
            a += b;
            pendingScroll = 0;
        } else {
            a += 8;
            pendingScroll = b - 8;
        }
    } else if (b < 0) {
        if (b > -8) {
            a += b;
            pendingScroll = 0;
        } else {
            a -= 8;
            pendingScroll = b + 8;
        }
    }
    if (a != listScroll) {
        DateTimePicker_SetListScroll(this, a);
        syncKnobToScroll();
    }
}

void DateTimePicker::blendListPalette(s32 t) {
    MIi_CpuCopy16(listPalette, listPaletteWork, 0x20);
    s32 c1 = listPalette[14];
    u8 r = c1 & 0x1f;
    u8 g = (c1 & 0x3e0) >> 5;
    u8 b = (c1 & 0x7c00) >> 10;
    s32 w = 3 - t;
    s32 c2 = listPalette[15];
    r = ((u8)(c2 & 0x1f) * t + r * w) / 3;
    g = ((u8)((c2 & 0x3e0) >> 5) * t + g * w) / 3;
    b = ((u8)((c2 & 0x7c00) >> 10) * t + b * w) / 3;
    listPaletteWork[15] = r | (g << 5) | (b << 10);
    listPaletteTask.requestPalette(listPaletteWork, listLayer, 9);
}

BOOL DateTimePicker::testFlags(u32 m) {
    if (flags & m) {
        return TRUE;
    }
    return FALSE;
}

void DateTimePicker::setFlags(u32 m) {
    flags |= m;
}

void DateTimePicker::clearFlags(u32 m) {
    flags &= ~m;
}

extern "C" GXOamAttr data_ov134_02294dc4[2] = {{0x80004000, 0xcb, 0, 0x5, 0x0}, {0x208000, 0xcf, 0, 0x5, 0xffff}};
extern "C" GXOamAttr data_ov134_02294fb4[4] = {{0x81e84004, 0x154, 1, 0x6, 0x0}, {0x41e84014, 0x194, 1, 0x6, 0x0}, {0x81c84004, 0x154, 1, 0x6, 0x0}, {0x41c84014, 0x194, 1, 0x6, 0xffff}};
extern "C" char *sObjVariantFiles[1] = {data_ov134_02294f74};
extern "C" char data_ov134_02294e3c[22] = "menu/clock/bgb_us.bsc";
extern "C" GXOamAttr data_ov134_02294d44[1] = {{0xc19800b3, 0xc0, 1, 0x4, 0xffff}};
extern "C" GXOamAttr data_ov134_02294d4c[1] = {{0x80004000, 0xcb, 0, 0x5, 0xffff}};
extern "C" GXOamAttr *data_ov134_02294f5c[6] = {data_ov134_02294d4c, data_ov134_02294d84, data_ov134_02294dc4, data_ov134_02294da4, data_ov134_02294da4, data_ov134_02294ee4};
extern "C" GXOamAttr data_ov134_02294fd4[4] = {{0x80004004, 0x154, 1, 0x6, 0x0}, {0x40004014, 0x194, 1, 0x6, 0x0}, {0x800f4004, 0x154, 1, 0x6, 0x0}, {0x400f4014, 0x194, 1, 0x6, 0xffff}};
extern "C" char data_ov134_02294e6c[22] = "menu/clock/bgd_us.bsc";
extern "C" GXOamAttr data_ov134_02294ff4[4] = {{0x90264024, 0x152, 1, 0x6, 0x0}, {0x50264034, 0x192, 1, 0x6, 0x0}, {0x80084024, 0x152, 1, 0x6, 0x0}, {0x40084034, 0x192, 1, 0x6, 0xffff}};
extern "C" GXOamAttr data_ov134_022950a4[6] = {{0x1ff0030, 0x159, 1, 0x6, 0x0}, {0x1ff0028, 0x159, 1, 0x6, 0x0}, {0x91de4024, 0x152, 1, 0x6, 0x0}, {0x51de4034, 0x192, 1, 0x6, 0x0}, {0x81c04024, 0x152, 1, 0x6, 0x0}, {0x41c04034, 0x192, 1, 0x6, 0xffff}};
extern "C" GXOamAttr data_ov134_022950d4[6] = {{0x40028, 0x159, 1, 0x6, 0x0}, {0x40020, 0x159, 1, 0x6, 0x0}, {0x91e4401c, 0x152, 1, 0x6, 0x0}, {0x51e4402c, 0x192, 1, 0x6, 0x0}, {0x81cc401c, 0x152, 1, 0x6, 0x0}, {0x41cc402c, 0x192, 1, 0x6, 0xffff}};
extern "C" const u8 sWeekdayTextIds[7] = {0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0};
extern "C" GXOamAttr data_ov134_02295104[6] = {{0x81d0400c, 0x155, 1, 0x6, 0x0}, {0x41d0401c, 0x195, 1, 0x6, 0x0}, {0x91e8400c, 0x152, 1, 0x6, 0x0}, {0x51e8401c, 0x192, 1, 0x6, 0x0}, {0x81b8400c, 0x152, 1, 0x6, 0x0}, {0x41b8401c, 0x192, 1, 0x6, 0xffff}};
extern "C" GXOamAttr data_ov134_02294d54[2] = {{0x80444023, 0x1b2, 1, 0x6, 0x0}, {0x40640023, 0x1b6, 1, 0x6, 0xffff}};
extern "C" GXOamAttr data_ov134_02294db4[2] = {{0x8044402b, 0x1b2, 1, 0x6, 0x0}, {0x4064002b, 0x1b6, 1, 0x6, 0xffff}};
extern "C" GXOamAttr data_ov134_02295204[14] = {{0x268000, 0xca, 1, 0x8, 0x0}, {0x1e88000, 0xca, 1, 0x8, 0x0}, {0x81c740fc, 0x154, 1, 0x8, 0x0}, {0x41c7400c, 0x194, 1, 0x8, 0x0}, {0x81e740fc, 0x154, 1, 0x8, 0x0}, {0x41e7400c, 0x194, 1, 0x8, 0x0}, {0x801740fc, 0x154, 1, 0x8, 0x0}, {0x4017400c, 0x194, 1, 0x8, 0x0}, {0x81f740fc, 0x154, 1, 0x8, 0x0}, {0x41f7400c, 0x194, 1, 0x8, 0x0}, {0x903740fc, 0x152, 1, 0x8, 0x0}, {0x5037400c, 0x192, 1, 0x8, 0x0}, {0x81a740fc, 0x152, 1, 0x8, 0x0}, {0x41a7400c, 0x192, 1, 0x8, 0xffff}};
extern "C" GXOamAttr data_ov134_02295194[6] = {{0x800040e8, 0x108, 0, 0x6, 0x0}, {0x800a40e8, 0x10c, 0, 0x6, 0x0}, {0x402800e8, 0x110, 0, 0x6, 0x0}, {0x400040f8, 0x148, 0, 0x6, 0x0}, {0x400a40f8, 0x14c, 0, 0x6, 0x0}, {0x2840f8, 0x150, 0, 0x6, 0xffff}};
extern "C" GXOamAttr *data_ov134_02294f2c[6] = {data_ov134_02294efc, data_ov134_02295054, data_ov134_02294ecc, data_ov134_02294eb4, data_ov134_02294eb4, data_ov134_02294eb4};
extern "C" GXOamAttr *data_ov134_02294f14[6] = {data_ov134_02295194, data_ov134_022951c4, data_ov134_02295164, data_ov134_02295134, data_ov134_02295134, data_ov134_02295134};
extern "C" GXOamAttr data_ov134_02294efc[3] = {{0x80004000, 0x168, 0, 0x6, 0x0}, {0x800a4000, 0x16c, 0, 0x6, 0x0}, {0x40280000, 0x170, 0, 0x6, 0xffff}};
extern "C" const u32 sFieldTopTime[6] = {0x0, 0xc, 0xc, 0x10, 0x10, 0xc};
extern "C" GXOamAttr data_ov134_02294eb4[3] = {{0x80004000, 0x168, 0, 0x6, 0x0}, {0x80184000, 0x16c, 0, 0x6, 0x0}, {0x40380000, 0x170, 0, 0x6, 0xffff}};
extern "C" char data_ov134_02294dfc[19] = "menu/clock/bg2.bpl";
extern "C" GXOamAttr data_ov134_02294ecc[3] = {{0x80004000, 0x168, 0, 0x6, 0x0}, {0x80104000, 0x16c, 0, 0x6, 0x0}, {0x40300000, 0x170, 0, 0x6, 0xffff}};
extern "C" const u32 sFieldLeftTime[6] = {0x0, 0x6, 0xe, 0xa, 0x12, 0x13};
extern "C" char data_ov134_02294e24[22] = "menu/clock/bge_us.bsc";
extern "C" GXOamAttr data_ov134_02294d84[2] = {{0x80004000, 0xcb, 0, 0x5, 0x0}, {0x80204000, 0xcf, 0, 0x5, 0xffff}};
extern "C" GXOamAttr data_ov134_02295074[6] = {{0x902e4004, 0x154, 1, 0x6, 0x0}, {0x502e4014, 0x194, 1, 0x6, 0x0}, {0x90344004, 0x154, 1, 0x6, 0x0}, {0x50344014, 0x194, 1, 0x6, 0x0}, {0x904f4004, 0x152, 1, 0x6, 0x0}, {0x504f4014, 0x192, 1, 0x6, 0xffff}};
extern "C" const u32 sFieldWidths[6] = {0x4, 0x8, 0x5, 0x6, 0x6, 0x7};
extern "C" const u8 sMonthStringIds[12] = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb};
extern "C" GXOamAttr data_ov134_02294da4[2] = {{0x80004000, 0xcb, 0, 0x5, 0x0}, {0x40200000, 0xcf, 0, 0x5, 0xffff}};
extern "C" char data_ov134_02294e54[22] = "menu/clock/bgc_us.bsc";
extern "C" GXOamAttr data_ov134_02295014[4] = {{0x9024401c, 0x152, 1, 0x6, 0x0}, {0x5024402c, 0x192, 1, 0x6, 0x0}, {0x800c401c, 0x152, 1, 0x6, 0x0}, {0x400c402c, 0x192, 1, 0x6, 0xffff}};
extern "C" const u8 sFieldNameTextIds[6] = {0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xaa};
extern "C" GXOamAttr data_ov134_02295134[6] = {{0x800040e8, 0x108, 0, 0x6, 0x0}, {0x801840e8, 0x10c, 0, 0x6, 0x0}, {0x403800e8, 0x110, 0, 0x6, 0x0}, {0x400040f8, 0x148, 0, 0x6, 0x0}, {0x401840f8, 0x14c, 0, 0x6, 0x0}, {0x3840f8, 0x150, 0, 0x6, 0xffff}};
extern "C" char *sBgPaletteFiles[4] = {data_ov134_02294dd4, data_ov134_02294de8, data_ov134_02294dfc, data_ov134_02294e10};
extern "C" GXOamAttr data_ov134_02295164[6] = {{0x800040e8, 0x108, 0, 0x6, 0x0}, {0x801040e8, 0x10c, 0, 0x6, 0x0}, {0x403000e8, 0x110, 0, 0x6, 0x0}, {0x400040f8, 0x148, 0, 0x6, 0x0}, {0x401040f8, 0x14c, 0, 0x6, 0x0}, {0x3040f8, 0x150, 0, 0x6, 0xffff}};
extern "C" GXOamAttr *data_ov134_02294e9c[6] = {data_ov134_02295074, data_ov134_02294fb4, data_ov134_02294fd4, data_ov134_022950a4, data_ov134_02294ff4, data_ov134_02294f94};
extern "C" const u32 sFieldLeftBirthday[6] = {0x0, 0x8, 0x12, 0x0, 0x0, 0x0};
extern "C" GXOamAttr data_ov134_02294d74[2] = {{0x800a40ee, 0x1aa, 0, 0x6, 0x0}, {0x802a40ee, 0x1ae, 0, 0x6, 0xffff}};
extern "C" GXOamAttr data_ov134_02294ee4[3] = {{0x80004000, 0xcb, 0, 0x5, 0x0}, {0x40200000, 0xcf, 0, 0x5, 0x0}, {0x308000, 0xd1, 0, 0x5, 0xffff}};
extern "C" GXOamAttr data_ov134_02294f94[4] = {{0x91a84004, 0x154, 1, 0x9, 0x0}, {0x51a84014, 0x194, 1, 0x9, 0x0}, {0x81884004, 0x152, 1, 0x9, 0x0}, {0x41884014, 0x192, 1, 0x9, 0xffff}};
extern "C" GXOamAttr data_ov134_022951c4[8] = {{0x802840e8, 0x10c, 0, 0x6, 0x0}, {0x402840f8, 0x14c, 0, 0x6, 0x0}, {0x800040e8, 0x108, 0, 0x6, 0x0}, {0x802040e8, 0x10c, 0, 0x6, 0x0}, {0x404800e8, 0x110, 0, 0x6, 0x0}, {0x400040f8, 0x148, 0, 0x6, 0x0}, {0x402040f8, 0x14c, 0, 0x6, 0x0}, {0x4840f8, 0x150, 0, 0x6, 0xffff}};
extern "C" const u8 sFieldValueCounts[6] = {0x64, 0xc, 0x1f, 0x18, 0x3c, 0x7};
extern "C" GXOamAttr data_ov134_02295034[4] = {{0x9020400c, 0x152, 1, 0x6, 0x0}, {0x5020401c, 0x192, 1, 0x6, 0x0}, {0x8008400c, 0x152, 1, 0x6, 0x0}, {0x4008401c, 0x192, 1, 0x6, 0xffff}};
extern "C" GXOamAttr data_ov134_02294e84[3] = {{0x1fc00fc, 0xe8, 1, 0x5, 0x0}, {0x81f000e0, 0xd8, 1, 0x5, 0x0}, {0x81f000e0, 0xd4, 1, 0x5, 0xffff}};
extern "C" char data_ov134_02294dd4[19] = "menu/clock/bg0.bpl";
extern "C" const u32 sFieldLeftDefault[6] = {0x17, 0x9, 0x11, 0x9, 0x12, 0x2};
extern "C" const u32 sFieldTopBirthday[6] = {0x0, 0xe, 0xe, 0x0, 0x0, 0x0};
extern "C" char data_ov134_02294f74[30] = "menu/clock/b_tim_ten0_obj.bch";
extern "C" GXOamAttr data_ov134_02295054[4] = {{0x80284000, 0x16c, 0, 0x6, 0x0}, {0x80004000, 0x168, 0, 0x6, 0x0}, {0x80204000, 0x16c, 0, 0x6, 0x0}, {0x40480000, 0x170, 0, 0x6, 0xffff}};
extern "C" char data_ov134_02294e10[19] = "menu/clock/bg3.bpl";
extern "C" GXOamAttr data_ov134_02294f44[3] = {{0x2e8008, 0xca, 1, 0x6, 0x0}, {0x78008, 0xca, 1, 0x6, 0x0}, {0x1c88008, 0xca, 1, 0x6, 0xffff}};
extern "C" const u32 sFieldTopDefault[6] = {0xd, 0xd, 0xd, 0x11, 0x11, 0xd};
extern "C" char data_ov134_02294de8[19] = "menu/clock/bg1.bpl";
extern "C" char *sFieldScreenFiles[4] = {data_ov134_02294e3c, data_ov134_02294e54, data_ov134_02294e6c, data_ov134_02294e24};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov134_02291f60) {
    HOST_OVERLAY_VAR(data_ov134_02294dc4),
    HOST_OVERLAY_VAR(data_ov134_02294fb4),
    HOST_OVERLAY_VAR(sObjVariantFiles),
    HOST_OVERLAY_VAR(data_ov134_02294e3c),
    HOST_OVERLAY_VAR(data_ov134_02294d44),
    HOST_OVERLAY_VAR(data_ov134_02294d4c),
    HOST_OVERLAY_VAR(data_ov134_02294f5c),
    HOST_OVERLAY_VAR(data_ov134_02294fd4),
    HOST_OVERLAY_VAR(data_ov134_02294e6c),
    HOST_OVERLAY_VAR(data_ov134_02294ff4),
    HOST_OVERLAY_VAR(data_ov134_022950a4),
    HOST_OVERLAY_VAR(data_ov134_022950d4),
    HOST_OVERLAY_VAR(data_ov134_02295104),
    HOST_OVERLAY_VAR(data_ov134_02294d54),
    HOST_OVERLAY_VAR(data_ov134_02294db4),
    HOST_OVERLAY_VAR(data_ov134_02295204),
    HOST_OVERLAY_VAR(data_ov134_02295194),
    HOST_OVERLAY_VAR(data_ov134_02294f2c),
    HOST_OVERLAY_VAR(data_ov134_02294f14),
    HOST_OVERLAY_VAR(data_ov134_02294efc),
    HOST_OVERLAY_VAR(data_ov134_02294eb4),
    HOST_OVERLAY_VAR(data_ov134_02294dfc),
    HOST_OVERLAY_VAR(data_ov134_02294ecc),
    HOST_OVERLAY_VAR(data_ov134_02294e24),
    HOST_OVERLAY_VAR(data_ov134_02294d84),
    HOST_OVERLAY_VAR(data_ov134_02295074),
    HOST_OVERLAY_VAR(data_ov134_02294da4),
    HOST_OVERLAY_VAR(data_ov134_02294e54),
    HOST_OVERLAY_VAR(data_ov134_02295014),
    HOST_OVERLAY_VAR(data_ov134_02295134),
    HOST_OVERLAY_VAR(sBgPaletteFiles),
    HOST_OVERLAY_VAR(data_ov134_02295164),
    HOST_OVERLAY_VAR(data_ov134_02294e9c),
    HOST_OVERLAY_VAR(data_ov134_02294d74),
    HOST_OVERLAY_VAR(data_ov134_02294ee4),
    HOST_OVERLAY_VAR(data_ov134_02294f94),
    HOST_OVERLAY_VAR(data_ov134_022951c4),
    HOST_OVERLAY_VAR(data_ov134_02295034),
    HOST_OVERLAY_VAR(data_ov134_02294e84),
    HOST_OVERLAY_VAR(data_ov134_02294dd4),
    HOST_OVERLAY_VAR(data_ov134_02294f74),
    HOST_OVERLAY_VAR(data_ov134_02295054),
    HOST_OVERLAY_VAR(data_ov134_02294e10),
    HOST_OVERLAY_VAR(data_ov134_02294f44),
    HOST_OVERLAY_VAR(data_ov134_02294de8),
    HOST_OVERLAY_VAR(sFieldScreenFiles),
    HOST_OVERLAY_VARS_END
};
