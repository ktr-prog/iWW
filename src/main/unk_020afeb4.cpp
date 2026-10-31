#include "uptr.h"
#include "host_labels.h"
#include "host_shared_calls.h"
#include "talk/ConstellationEncodedString16.h"
#include "types.h"
#include "sdk_linker_symbols.h"
#include "gfx/VecFx32.h"
#include "game/SceneInfo.h"
#include "actor/Actor.h"
#include "save/TownExchangeRecord.h"
#include "talk/MsgString.h"
#include "proto/itcm/unk_01ffa4a0.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_0204eeb4.h"
#include "proto/main/unk_02051218.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020afeb4.h"
#include "proto/main/unk_020b0774.h"
#include "proto/ov127/unk_ov127_02291f60.h"
#include "game/ConstellationStore.h"
#include "player/PlayerData.h"
#include "player/PlayerId.h"
#include "sys/ClockDateTime.h"


typedef ConstellationRecord Entry;
typedef ConstellationStore Base;



extern "C" {
#define data_021ec31c HOST_LABEL(Base *, data_021ec31c)
u32 sConstellationColumns[2];
#define data_021e7f8c HOST_LABEL(TownExchangeRecord *, data_021e7f8c)

s32 Sky_GetStarViewingTime(void *a, s32 x, s32 y);
s32 Sky_GetStarScrollX(void);
s32 Sky_GetStarScrollY(void);
void EncodedString_SetRaw(void *buf, const void *src, s32 len);
void Clock_GetDateTime(ClockDateTime *p);
void *func_020b87d0(void *p);
void MI_CpuCopy8(const void *src, void *dst, u32 size);
u64 func_02132ef8(u64 a, u64 b);

void Constellation_Store(Entry *e, s32 idx, s32 flag);
void Constellation_SetLinesPalette(u16 *p, Entry *e, s32 r);
BOOL Constellation_AddReceived(Entry *e);
Base *Constellation_GetData(void);
Entry *Constellation_GetRecordAlt(s32 i);
Entry *Constellation_GetRecord(s32 i);

inline void setv(VecFx32 *v, s32 x, s32 y, s32 z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

void Constellation_ClearColumns(void) {
    sConstellationColumns[1] = 0;
    sConstellationColumns[0] = 0;
}

void Constellation_MarkColumn(s32 n) {
    if (n >= 0x20) {
        sConstellationColumns[1] |= 1 << (n - 0x20);
    } else {
        sConstellationColumns[0] |= 1 << n;
    }
}

BOOL Constellation_TestColumn(s32 n) {
    if (n >= 0x20) {
        return (sConstellationColumns[1] & (1 << (n - 0x20))) != 0;
    }
    return (sConstellationColumns[0] & (1 << n)) != 0;
}

void Constellation_CalcCentre(u16 *p, s32 *outA, s32 *outB) {
    u8 *d;
    s32 minv, maxv, i, j, t, a, b;
    s32 f1, f2, f3, f4;
    Constellation_ClearColumns();
    minv = 0x20;
    maxv = -1;
    for (i = 0; i < 16; i++) {
        if (p[i] != 0xffff) {
            d = Constellation_GetLineCells(p[i]);
            for (j = 0; j < 4; j++) {
                u8 x = d[0];
                u8 y = d[1];
                d += 2;
                if (x != 0xff) {
                    Constellation_MarkColumn(x);
                    if (minv > y) {
                        minv = y;
                    }
                    if (maxv < y) {
                        maxv = y;
                    }
                } else {
                    j = 4;
                }
            }
        }
    }
    t = 0;
    while (t < 0x40 && !Constellation_TestColumn(t)) {
        t++;
    }
    a = (t - 1) & 0x3f;
    b = t;
    f1 = 0;
    f2 = 0;
    while (!f1 && a != b) {
        if (Constellation_TestColumn(a)) {
            f2 = 0;
            b = a;
        } else if (f2) {
            f1 = 1;
        } else {
            f2 = 1;
        }
        a = (a - 1) & 0x3f;
    }
    if (f1) {
        a = (t + 1) & 0x3f;
        f3 = 0;
        f4 = 0;
        while (!f3 && a != t) {
            if (Constellation_TestColumn(a)) {
                f4 = 0;
                t = a;
            } else if (f4) {
                f3 = 1;
            } else {
                f4 = 1;
            }
            a = (a + 1) & 0x3f;
        }
    } else {
        t = 0;
        b = 0;
    }
    if (b <= t) {
        *outA = (b + t + 1) * 4;
    } else {
        *outA = ((b + 0x41 + t) * 4) & 0x1ff;
    }
    *outB = (minv * 8 + (maxv * 8 + 8)) >> 1;
}

Base *Constellation_GetData(void) {
    return &data_021ec31c;
}

s32 Constellation_FindFreeSlot(void) {
    Base *base = Constellation_GetData();
    s32 i;
    for (i = 0; i < 16; i++) {
        if (!ConstellationStore_IsUsed(base, i)) {
            return i;
        }
    }
    return -1;
}

s32 Constellation_CountFreeSlots(void) {
    Base *base = Constellation_GetData();
    s32 i, n;
    i = n = 0;
    for (; i < 16; i++) {
        if (!ConstellationStore_IsUsed(base, i)) {
            n++;
        }
    }
    return n;
}

Entry *Constellation_GetRecord(s32 idx) {
    Base *base = Constellation_GetData();
    if (ConstellationStore_IsUsed(base, idx) == 0) {
        return NULL;
    }
    return base->records + idx;
}

void Constellation_Store(Entry *e, s32 idx, s32 flag) {
    Base *base = Constellation_GetData();
    ConstellationStore_SetUsed(base, idx);
    ConstellationRecord_Copy(&base->records[idx], e);
    if (flag) {
        base->newMask |= 1 << idx;
    }
}

void Constellation_Erase(s32 idx) {
    Base *base = Constellation_GetData();
    ConstellationStore_ClearUsed(base, idx);
    base->newMask &= ~(1 << idx);
}

Entry *Constellation_GetRecordAlt(s32 idx) {
    Base *base = Constellation_GetData();
    if (ConstellationStore_IsUsed(base, idx) == 0) {
        return NULL;
    }
    return base->records + idx;
}

void Constellation_SetCreator(u8 *dst) {
    PlayerId *src = PlayerData_GetCurrent()->getPlayerId();
    PlayerId *d = (PlayerId *)dst;
    d->townId = src->townId;
    Mem_Copy(src->townName, d->townName, 8);
    d->playerId = src->playerId;
    Mem_Copy(src->playerName, d->playerName, 8);
    d->gender = src->gender;
    dst[0x15] = ((u8 *)src)[0x15];
}

void Constellation_SetName(u8 *src, s32 idx) {
    Mem_Copy(src, Constellation_GetData()->records[idx].name, 16);
}

void Constellation_CopyName(u8 *dst, s32 idx) {
    Base *base = Constellation_GetData();
    Mem_Clear(dst, 16);
    if (ConstellationStore_IsUsed(base, idx)) {
        Mem_Copy(base->records[idx].name, dst, 16);
    }
}

BOOL Constellation_GetName(void *self, s32 idx) {
    Entry *e;
    if (!ConstellationStore_IsUsed(Constellation_GetData(), idx)) {
        return FALSE;
    }
    e = Constellation_GetRecord(idx);
    ConstellationEncodedString16 buf;
    EncodedString_SetRaw(&buf, e->name, 16);
    ((MsgString *)(self))->fromEncoded(&buf, 0, 0);
    return TRUE;
}

s32 Constellation_GetNewStatus(s32 *out) {
    Base *base;
    s32 i;
    *out = -1;
    base = Constellation_GetData();
    for (i = 0; i < 16; i++) {
        u32 bit = 1 << i;
        if (base->newMask & bit) {
            if (ConstellationStore_IsUsed(base, i)) {
                if (*out == -1) {
                    *out = i;
                } else {
                    return 2;
                }
            } else {
                base->newMask &= ~bit;
            }
        }
    }
    if (*out != -1) {
        return 1;
    }
    return 0;
}

void Constellation_ClearNewFlags(void) {
    Constellation_GetData()->newMask = 0;
}

void Constellation_GetViewingTime(void *a, s32 idx) {
    s32 x, y;
    Entry *e = Constellation_GetRecord(idx);
    Constellation_CalcCentre(e->lines, &x, &y);
    x -= 0x80;
    y -= 0x60;
    Sky_GetStarViewingTime(a, x, y);
}

BOOL Constellation_IsInView(s32 x, s32 y, s32 px, s32 py) {
    if (py < y + 0x10 || py > y + 0x88) {
        return FALSE;
    }
    if (px < x + 0x40 || px > x + 0xc0) {
        return FALSE;
    }
    return TRUE;
}

s32 Constellation_FindVisibleNow(void) {
    ClockDateTimeWords tm;
    s32 d, px, py, x, y, dx, i, bestd, dy, best;
    tm.words[0] = 0;
    tm.words[1] = 0;
    Clock_GetDateTime(&tm.dt);
    if (tm.dt.hour >= 6 && tm.dt.hour < 0x12) {
        return -1;
    }
    x = Sky_GetStarScrollX();
    y = Sky_GetStarScrollY();
    best = -1;
    for (i = 0; i < 16; i++) {
        Entry *e = Constellation_GetRecord(i);
        if (e) {
            Constellation_CalcCentre(e->lines, &px, &py);
            if (px < x) {
                px += 0x200;
            }
            if (Constellation_IsInView(x, y, px, py)) {
                dy = py - (y + 0x60);
                dx = px - (x + 0x80);
                d = dx * dx + dy * dy;
                if (best == -1 || bestd > d) {
                    best = i;
                    bestd = d;
                }
            }
        }
    }
    return best;
}

void Constellation_AcquireSkyOverlay(void) {
    OverlayMgr_Acquire(OVERLAY_127_ID);
}

void Constellation_ReleaseSkyOverlay(void) {
    OverlayMgr_Release(OVERLAY_127_ID);
}

BOOL Constellation_AddReceived(Entry *e) {
    s32 idx = Constellation_FindFreeSlot();
    s32 r;
    if (idx == -1) {
        return FALSE;
    }
    if (Constellation_IsNameTaken(e->name, -1)) {
        return FALSE;
    }
    Constellation_AcquireSkyOverlay();
    r = Shared_StarSky_IsConstellationFree(e);
    Constellation_ReleaseSkyOverlay();
    if (r) {
        Constellation_Store(e, idx, 1);
    }
    return r;
}

void Constellation_PrepareExchange(void) {
    Entry *e;
    Base *base;
    s32 n, i;
    e = (Entry *)data_021e7f8c.getConstellation();
    ConstellationRecord_Clear(e);
    n = 0;
    base = Constellation_GetData();
    for (i = 0; i < 16; i++) {
        if (ConstellationStore_IsUsed(base, i)) {
            n++;
        }
    }
    if (n != 0) {
        n = Random_GlobalBelow(n);
        for (i = 0; i < 16; i++) {
            if (ConstellationStore_IsUsed(base, i)) {
                if (n > 0) {
                    n--;
                } else {
                    ConstellationRecord_Copy(e, Constellation_GetRecord(i));
                    break;
                }
            }
        }
    }
}

void Constellation_ImportExchanged(void) {
    Entry *e;
    s32 i, j;
    s32 count;
    TownExchangeRecord *p = &data_021e7f8c;
    if (p->isValid()) {
        e = (Entry *)p->getConstellation();
        count = 0;
        for (i = 0; i < 16; i++) {
            if (e->lines[i] != 0xffff) {
                count++;
                for (j = 0; j < i; j++) {
                    if (e->lines[i] == e->lines[j]) {
                        ConstellationRecord_Clear(e);
                        return;
                    }
                }
            }
        }
        if (count != 0) {
            if (Constellation_AddReceived(e)) {
                ConstellationRecord_Clear(e);
            }
        }
    }
}

BOOL Constellation_IsNameTaken(const u8 *name, s32 skip) {
    s32 i;
    for (i = 0; i < 16; i++) {
        if (skip != i) {
            Entry *e = Constellation_GetRecord(i);
            if (e) {
                if (Text_EqualsTrimmed(name, e->name, 16)) {
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

BOOL Constellation_IsLineTile(s32 n) {
    if (n >= 0x13 && n <= 0x1f) {
        return TRUE;
    }
    return FALSE;
}

s32 Constellation_CellToScreenIndex(s32 x, s32 y) {
    s32 off = 0;
    if (x >= 0x20) {
        off += 0x400;
        x -= 0x20;
    }
    return off + (x + y * 32);
}

void Constellation_SetLinePalette(u16 *p, u32 slot, s32 r) {
    u8 *d = Constellation_GetLineCells(slot);
    s32 j, i;
    j = i = 0;
    r &= 0xf;
    for (; j < 4; j++) {
        u8 x, y;
        s32 idx;
        if (d[i] == 0xff) {
            break;
        }
        x = d[i];
        y = d[i + 1];
        i += 2;
        idx = Constellation_CellToScreenIndex(x, y);
        p[idx] = (p[idx] & 0xfff) | (r << 12);
    }
}

void Constellation_SetLinesPalette(u16 *p, Entry *e, s32 r) {
    s32 i;
    for (i = 0; i < 16; i++) {
        if (e->lines[i] != 0xffff) {
            Constellation_SetLinePalette(p, e->lines[i], r);
        }
    }
}

void Constellation_HighlightAll(u16 *p) {
    s32 i;
    for (i = 0; i < 16; i++) {
        Entry *e = Constellation_GetRecordAlt(i);
        if (e) {
            Constellation_SetLinesPalette(p, e, 7);
        }
    }
}

void Constellation_MaskSkyScreen(u16 *p) {
    s32 i;
    Constellation_HighlightAll(p);
    for (i = 0; i < 0x800; p++, i++) {
        if (Constellation_IsLineTile(*p & 0x3ff)) {
            if (((*p & 0xf000) >> 12) != 7) {
                *p = 0x4010;
            }
        }
    }
}

BOOL SceneSpawnGroup_SpawnActors(SceneSpawnGroup *self, u8 *idxp, u64 start) {
    s32 i;
    BOOL result;
    SceneSpawnRecord *n;
    if (idxp != NULL) {
        i = *idxp;
    } else {
        i = 0;
    }
    n = &((SceneSpawnRecord *)self->list)[i];
    result = TRUE;
    while (TRUE) {
        VecFx32 v;
        setv(&v, (n->actor.x << 12) >> 4, (n->actor.y << 12) >> 4, (n->actor.z << 12) >> 4);
        Actor::spawn(n->actor.profile, n->actor.spawnParam, &v, &n->actor.rot[0], NULL);
        n++;
        i++;
        if (idxp != NULL) {
            (*idxp)++;
        }
        if (i >= self->count) {
            goto end;
        }
        if (idxp != NULL) {
            if ((u32)(((OS_GetTick() - start) << 6) / 0x82ea) > 0x28) {
                result = FALSE;
                goto end;
            }
        }
    }
end:
    return result != 0;
}
}
