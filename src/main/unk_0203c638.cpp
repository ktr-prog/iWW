#include "uptr.h"
#include "types.h"
#include "game/Unk_0203c92c_Bits.h"
#include "game/Unk_0203ce24_Elem.h"
#include "player/PlayerOptions.h"
#include "item/ItemId.h"
#include "talk/BmgReader.h"
#include "talk/MailTextBuilder.h"
#include "talk/MsgString.h"
#include "talk/MsgRequest.h"
#include "talk/MailMsgRequest.h"
#include "gfx/G3dResAccess.h"
#include "player/PlayerData.h"
#include "save/Pattern.h"
#include "save/SaveData.h"
#include "proto/main/unk_0203c638.h"
#include "proto/main/unk_0203c92c.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020b2c50.h"



extern "C" {
void MI_CpuCopy8(void *src, void *dst, u32 n);
}

struct Catalog {
    u8 furnitureBits[0x100];
    u8 wallpaperBits[9];
    u8 carpetBits[9];
    u8 songBits[9];
    u8 paperBits[8];
};


extern "C" {
void Catalog_Clear(Catalog *p);
void *NNS_G3dGetTex(void *p);
}

extern SaveData gSaveData;

static inline AbleSistersPatterns *ClothTex_AblePatterns() {
    return (AbleSistersPatterns *)gSaveData.ableSistersPatterns;
}

static inline BOOL Unk_0203c764_InRange(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) r = TRUE;
    return r;
}

extern "C" void ClothTex_Construct() {}

extern "C" void ClothTex_Destruct() {}

extern "C" BOOL ClothTex_LoadItem(void *self, u16 *p, void *q) {
    s32 i1, i2, i3, i4;
    char buf[0x20];
    BOOL res;
    if (Unk_0203c764_InRange(p, 0x12a8, 0x12af)) {
        if (*p >= 0x12a8 && *p <= 0x12af) i1 = *p - 0x12a8;
        else i1 = -1;
        res = FALSE;
        if (i1 != -1) {
            if (q == 0) res = ClothTex_LoadPattern(self, ClothTex_AblePatterns()->getPattern((u8)i1));
            else res = ClothTex_LoadPattern(self, static_cast<PlayerPatterns *>(static_cast<PlayerData *>(q)->getPatterns())->getPattern((u8)i1));
        }
    } else if (*p >= 0x1429 && *p <= 0x1430) {
        if (*p >= 0x1429 && *p <= 0x1430) i2 = *p - 0x1429;
        else i2 = -1;
        res = FALSE;
        if (i2 != -1) {
            if (q == 0) res = ClothTex_LoadPattern(self, ClothTex_AblePatterns()->getPattern((u8)i2));
            else res = ClothTex_LoadPattern(self, static_cast<PlayerPatterns *>(static_cast<PlayerData *>(q)->getPatterns())->getPattern((u8)i2));
        }
    } else if (*p >= 0x13a0 && *p <= 0x13a7) {
        if (*p >= 0x13a0 && *p <= 0x13a7) i3 = *p - 0x13a0;
        else i3 = -1;
        res = FALSE;
        if (i3 != -1) {
            if (q == 0) res = ClothTex_LoadPattern(self, ClothTex_AblePatterns()->getPattern((u8)i3));
            else res = ClothTex_LoadPattern(self, static_cast<PlayerPatterns *>(static_cast<PlayerData *>(q)->getPatterns())->getPattern((u8)i3));
        }
    } else {
        if (*p >= 0x11a8 && *p <= 0x12a7) i4 = *p - 0x11a8;
        else i4 = -1;
        if (i4 != -1) {
            Str_SPrintf(buf, "/cloth/%d/cloth%03d.nsbtx", i4 >> 4, i4);
            if (File_LoadToBuffer(buf, self, -1)) return TRUE;
            return FALSE;
        } else {
            static ItemId def(0x11a8);
            return ClothTex_LoadItem(self, &def.id, q);
        }
    }
    return res;
}

extern "C" BOOL ClothTex_LoadPattern(void *a, void *b) {
    u16 id = 0x11a8;
    if (ClothTex_LoadItem(a, &id, 0)) {
        if (b != 0) {
            Pattern *pat = static_cast<Pattern *>(b);
            void *dst = pat->getPixels();
            MI_CpuCopy8(dst, ClothTex_GetTexData(a), 0x200);
            void *dst2 = pat->getInfo()->getPaletteData();
            MI_CpuCopy8(dst2, ClothTex_GetPlttData(a), 0x20);
            return TRUE;
        }
        return TRUE;
    }
    return FALSE;
}

extern "C" void *ClothTex_GetTexData(void *tex) { return ((G3dResAccess *)(ClothTex_GetTex(tex)))->getTexData(0); }

extern "C" void *ClothTex_GetPlttData(void *tex) { return ((G3dResAccess *)(ClothTex_GetTex(tex)))->getPlttData(0); }

extern "C" void *ClothTex_GetTex(void *tex) { return NNS_G3dGetTex(tex); }

extern "C" u32 ClothTex_GetBufferSize() { return 0x2c4; }

extern "C" BOOL ClothTex_LoadItemThunk(void *a, u16 *b, void *c) { return ClothTex_LoadItem(a, b, c); }

extern "C" BOOL ClothTex_LoadPatternThunk(void *a, void *b) { return ClothTex_LoadPattern(a, b); }

extern "C" void *ClothTex_GetTexThunk(void *tex) { return ClothTex_GetTex(tex); }

extern "C" void Catalog_Construct() {}

extern "C" void Catalog_Destruct() {}

extern "C" void Catalog_Clear(Catalog *p) {
    u32 i;
    for (i = 0; i < 0x100; i++) p->furnitureBits[i] = 0;
    for (i = 0; i < 9; i++) p->wallpaperBits[i] = 0;
    for (i = 0; i < 9; i++) p->carpetBits[i] = 0;
    for (i = 0; i < 9; i++) p->songBits[i] = 0;
    for (i = 0; i < 8; i++) p->paperBits[i] = 0;
}

extern "C" void Catalog_Init(Catalog *p) { Catalog_Clear(p); }

