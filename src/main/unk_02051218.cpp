#include "types.h"
#include "room/FtrActorGrid.h"
#include "proto/main/unk_02051218.h"
#include "proto/main/unk_020514a4.h"
#include "proto/main/unk_02052b50.h"
#include "proto/main/unk_020a427c.h"
#include "proto/ov004/unk_ov004_02233074.h"
#include "proto/main/unk_0204cc1c.h"

extern "C" const u32 data_020ca638;

extern "C" {
void MI_CpuFill8(void *dst, u32 value, u32 size);
void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern u8 gFieldSceneKind;
extern BlockMap *gSceneBlockMap;

u32 Msg_DecodeGameChar(u8 *buf, u32 c);
u8 Msg_MeasureWidth(u8 *buf);
s32 FtrActor_GetFtrIndex(void *p);
s32 Item_IsFurniture(void *p);
u32 Item_GetFurnitureIndex(void *p);


}

extern "C" void BedSpot_RequestApproach(s32 *p) { SpotSync_RequestReserve(p); }

extern "C" u32 BedSpot_GetApproachResult() { return SpotSync_GetReserveResult(); }

extern "C" void BedSpot_RequestGetOut(s32 *p) { SpotSync_RequestReserve(p); }

extern "C" u32 BedSpot_GetGetOutResult() { return SpotSync_GetReserveResult(); }

extern "C" void BedSpot_Release() { SpotSync_Release(0); }

extern "C" void BedSpot_RequestRoll(s32 *p) { SpotSync_RequestReserve(p); }

extern "C" u32 BedSpot_GetRollResult() { return SpotSync_GetReserveResult(); }

extern "C" BOOL Room_CanDropOnFurnitureAt(s32 x, s32 y) {
    BOOL r;
    if (gFieldSceneKind == 1 ? TRUE : FALSE) {
        BlockMap *p = gSceneBlockMap;
        FtrActor *q = FtrActorGrid_GetInstance()->getActor(x, y, 0);
        if (p != NULL && q != NULL) {
            s32 hx = x >> 4;
            s32 hy = y >> 4;
            u16 code;
            u16 *o = BlockMap_GetItemPtr(p, hx, hy, x - (hx << 4), y - (hy << 4), 1);
            if (FtrInfo_GetDmaUnk04(FtrActor_GetFtrIndex(q)) == 1 && o != NULL) {
                if (Item_IsFurniture(o) != 0) {
                    code = 0xfff1;
                    r = Item_GetFurnitureIndex(o) == Item_GetFurnitureIndex(&code) ? TRUE : FALSE;
                } else {
                    r = *(u16 *)o == 0xfff1 ? TRUE : FALSE;
                }
                if (r) {
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

extern "C" void Text_BuildCharWidthTable() {
    s32 i;
    u8 buf[12];
    for (i = 0; (u32)i < 0xe0; i++) {
        buf[Msg_DecodeGameChar(buf, (u8)i)] = 0;
        sTextCharWidths[i] = Msg_MeasureWidth(buf);
    }
}

extern "C" u32 Text_GetCharWidth(u32 c) {
    return sTextCharWidths[c];
}

extern "C" s32 Text_MeasureWidth(const u8 *p, s32 n) {
    s32 sum = 0;
    s32 i;
    for (i = 0; i < n; i++) {
        sum += Text_GetCharWidth(p[i]);
    }
    return sum;
}

extern "C" s32 Text_GetLineEnd(const u8 *p, s32 n, s32 k) {
    s32 i;
    for (i = 0; i < n; i++) {
        u8 c = p[i];
        if (c == 0) {
            return i;
        }
        if (c == 0x86) {
            return i + k;
        }
    }
    return i;
}

extern "C" s32 Text_GetTrimmedLength(const u8 *str, s32 len) {
    s32 i;
    s32 last = 0;
    for (i = 0; i < len; i++) {
        u8 c = str[i];
        if (c == 0) {
            return last;
        }
        if (c != 0x85) {
            last = i + 1;
        }
    }
    return last;
}

extern "C" s32 Text_GetLength(const u8 *str, s32 len) {
    s32 i;
    for (i = 0; i < len; i++) {
        if (str[i] == 0) {
            return i;
        }
    }
    return i;
}

extern "C" s32 Text_FitToWidth(const u8 *str, s32 maxLen, s32 maxWidth, s32 *outLen, s32 arg4) {
    s32 width = 0;
    s32 i;
    s32 n = Text_GetLineEnd(str, maxLen, arg4);
    for (i = 0; i < n; i++) {
        width += Text_GetCharWidth(str[i]);
        if (width > maxWidth) {
            *outLen = i;
            return 1;
        }
    }
    *outLen = n;
    if (n == maxLen) {
        if (str[n - 1] == 0x86) {
            return 3;
        }
        return 2;
    }
    if (n == 0) {
        return 0;
    }
    if (str[n - 1] == 0x86) {
        return 3;
    }
    return 0;
}

extern "C" void Mem_Copy(const void *src, void *dst, u32 size) {
    MI_CpuCopy8(src, dst, size);
}

extern "C" void Mem_Clear(void *dst, u32 size) {
    MI_CpuFill8(dst, 0, size);
}

extern "C" BOOL Text_EqualsTrimmed(const u8 *a, const u8 *b, s32 len) {
    s32 n = Text_GetTrimmedLength(a, len);
    s32 i;
    if (n != Text_GetTrimmedLength(b, len)) {
        return FALSE;
    }
    for (i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            return FALSE;
        }
    }
    return TRUE;
}

u8 sTextCharWidths[0xe0];


const u32 data_020ca638 = 0x80000000;
