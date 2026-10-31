#include "types.h"
#include "town/TownAcreIndex.h"
#include "town/TownAcreCell.h"
#include "town/TownAcreGrid.h"
#include "proto/main/unk_02037260.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0209b63c.h"


static inline BOOL Unk_0209b830_Bit(s32 t, s32 m)
{
    return (t & m) != 0 ? TRUE : FALSE;
}

static inline BOOL Unk_0209b830_Chk(s32 v)
{
    s32 t = AcreType_GetAttr(v);
    if (!Unk_0209b830_Bit(t, 8) && !Unk_0209b830_Bit(t, 4) && !Unk_0209b830_Bit(t, 0x80000) && AcreType_CountRiverBits(v) == 1) return TRUE;
    return FALSE;
}

struct Unk_0209ba90_Dir {
    s16 x, y;
    Unk_0209ba90_Dir(s16 a, s16 b) { x = a; y = b; }
};


TownAcreCell *TownAcreGrid::getCell(s32 x, s32 y)
{
    s32 idx = x + y * 6;
    if ((u32)idx < 0x24) return &cells[idx];
    static TownAcreCell dflt;
    return &dflt;
}

extern "C" s32 AcreType_GetRiverVariant(s32 v)
{
    s32 t = AcreType_GetAttr(v);
    t = AcreType_FindByAttr(t | 0x100);
    if (t == 0x36) t = v;
    return t;
}

BOOL TownAcreGrid::placeOnRandomGrass(s32 val)
{
    s32 cnt = 0;
    u32 y, x;
    for (y = 1; y < 5; y++) {
        for (x = 1; x < 5; x++) {
            if (getCell(x, y)->getType() == 9) cnt++;
        }
    }
    s32 r = Random_GlobalBelow(cnt);
    s32 k = 0;
    for (y = 1; y < 5; y++) {
        for (x = 1; x < 5; x++) {
            if (getCell(x, y)->getType() == 9) {
                if (r == k) {
                    getCell(x, y)->setType(val);
                    return TRUE;
                }
                k++;
            }
        }
    }
    return FALSE;
}

BOOL TownAcreGrid::placeNextTo(s32 a, s32 b)
{
    s32 found = 0;
    u32 x, y;
    for (y = 1; y < 5; y++) {
        for (x = 1; x < 5; x++) {
            if (a == getCell(x, y)->getType()) {
                found = 1;
                break;
            }
        }
        if (found) break;
    }
    if (found) {
        static Unk_0209ba90_Dir dirs[4] = { Unk_0209ba90_Dir(-1, 0), Unk_0209ba90_Dir(1, 0), Unk_0209ba90_Dir(0, 1), Unk_0209ba90_Dir(0, -1) };
        s32 cnt = 0;
        u32 i;
        for (i = 0; i < 4; i++) {
            if (getCell(x + dirs[i].x, y + dirs[i].y)->getType() == 9) cnt++;
        }
        if (cnt != 0) {
            s32 r = Random_GlobalBelow(cnt);
            s32 k = 0;
            for (i = 0; i < 4; i++) {
                Unk_0209ba90_Dir *d = &dirs[i];
                if (getCell(x + dirs[i].x, y + d->y)->getType() == 9) {
                    if (r == k) {
                        getCell(x + d->x, y + d->y)->setType(b);
                        return TRUE;
                    }
                    k++;
                }
            }
        }
    }
    return FALSE;
}

BOOL TownAcreGrid::placeFacilities(u32 mode)
{
    if (!placeOnRandomGrass(0xe)) return FALSE;
    if (!placeOnRandomGrass(0xd)) return FALSE;
    if (!placeOnRandomGrass(0xc)) return FALSE;
    if (mode == 1) return placeNextTo(0xd, 0xb);
    if (mode == 2) return placeNextTo(0xe, 0xb);
    if (mode == 3) return placeNextTo(0xa, 0xb);
    if (mode == 4) return placeNextTo(0xc, 0xb);
    s32 cnt = 0;
    u32 x;
    for (x = 1; x < 5; x++) {
        if (getCell(x, 3)->getType() == 9) cnt++;
    }
    if (cnt != 0) {
        s32 r = Random_GlobalBelow(cnt);
        s32 k = 0;
        for (x = 1; x < 5; x++) {
            if (getCell(x, 3)->getType() == 9) {
                if (r == k) {
                    getCell(x, 3)->setType(0xb);
                    return TRUE;
                }
                k++;
            }
        }
    }
    return FALSE;
}

BOOL TownAcreGrid::placeRiverVariant()
{
    s32 k, v, r;
    s32 cnt = 0;
    u32 y, x;
    for (y = 1; y < 5; y++) {
        for (x = 1; x < 5; x++) {
            v = getCell(x, y)->getType();
            if (Unk_0209b830_Chk(v)) cnt++;
        }
    }
    if (cnt != 0) {
        r = Random_GlobalBelow(cnt);
        k = 0;
        for (y = 1; y < 5; y++) {
            for (x = 1; x < 5; x++) {
                v = getCell(x, y)->getType();
                if (Unk_0209b830_Chk(v)) {
                    if (r == k) {
                        s32 n = AcreType_GetRiverVariant(getCell(x, y)->getType());
                        if (n != getCell(x, y)->getType()) {
                            getCell(x, y)->setType(n);
                            return TRUE;
                        }
                    }
                    k++;
                }
            }
        }
    }
    return FALSE;
}

BOOL TownAcreGrid::setBorder()
{
    getCell(0, 0)->setType(7);
    getCell(1, 0)->setType(0);
    getCell(2, 0)->setType(0);
    getCell(3, 0)->setType(0);
    getCell(4, 0)->setType(0);
    getCell(5, 0)->setType(8);
    getCell(0, 5)->setType(0x35);
    getCell(1, 5)->setType(0x35);
    getCell(2, 5)->setType(0x35);
    getCell(3, 5)->setType(0x35);
    getCell(4, 5)->setType(0x35);
    getCell(5, 5)->setType(0x35);
    getCell(0, 1)->setType(3);
    getCell(0, 2)->setType(3);
    getCell(0, 3)->setType(3);
    getCell(0, 4)->setType(4);
    getCell(5, 1)->setType(5);
    getCell(5, 2)->setType(5);
    getCell(5, 3)->setType(5);
    getCell(5, 4)->setType(6);
    u32 i;
    for (i = 1; i < 5; i++) {
        if (getCell(i, 1)->getType() == 0x14) {
            getCell(i, 0)->setType(2);
        }
    }
    s32 cnt = 0;
    u32 j;
    for (j = 2; j <= 3; j++) {
        if (AcreType_CountRiverBits(getCell(j, 1)->getType()) == 0) cnt++;
    }
    s32 r = Random_GlobalBelow(cnt);
    s32 k = 0;
    for (j = 2; j <= 3; j++) {
        if (AcreType_CountRiverBits(getCell(j, 1)->getType()) == 0) {
            if (k == r) {
                getCell(j, 0)->setType(1);
                getCell(j, 1)->setType(10);
                return TRUE;
            }
            k++;
        }
    }
    return FALSE;
}

