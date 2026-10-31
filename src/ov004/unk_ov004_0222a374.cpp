#include "types.h"
#include "Unk_020d8c7c.h"
#include "sys/ProcProfile.h"
#include "player/PlayerData.h"
#include "proto/main/unk_02052b50.h"
#include "proto/main/unk_02097444.h"
#include "proto/ov004/unk_ov004_0222a374.h"
#include "proto/main/unk_0204cc1c.h"


struct Unk_ov004_0222a374_Loc {
    u16 a;
    u16 b;
};

struct Unk_ov004_0222a374_Pair {
    s32 a, b;
    constexpr Unk_ov004_0222a374_Pair(s32 x, s32 y) : a(x), b(y) {}
};


class PlayerBedSetter : public GameProc {
public:
    PlayerBedSetter();
    virtual BOOL onCreate();
    virtual ~PlayerBedSetter();
};

extern "C" {
extern BlockMap *gSceneBlockMap;
s32 Item_IsFurniture(u16 *p);
s32 Item_GetFurnitureIndex(u16 *p);
void Item_SetFurnitureDirection(u16 *p, s32 v);
}


extern "C" ProcProfile sPlayerBedSetterProfile = { (void *(*)())PlayerBedSetter_Create, 0x2b, 0x31 };

extern "C" PlayerBedSetter *PlayerBedSetter_Create() {
    return new PlayerBedSetter;
}

PlayerBedSetter::PlayerBedSetter() {}

PlayerBedSetter::~PlayerBedSetter() {}

BOOL PlayerBedSetter::onCreate() {
    Room_PlacePlayerBeds();
    return TRUE;
}

extern "C" {
Unk_ov004_0222a374_Pair Room_PlacePlayerBeds_tbl[4] = { Unk_ov004_0222a374_Pair(6, 9), Unk_ov004_0222a374_Pair(9, 9), Unk_ov004_0222a374_Pair(6, 12), Unk_ov004_0222a374_Pair(9, 12) };
void Room_PlacePlayerBeds() {
    BlockMap *g = gSceneBlockMap;
    if (g != 0) {
        s32 i;
        BOOL z1 = FALSE, z0 = FALSE, z2 = FALSE;
        for (i = 0; i < 4; i++) {
            PlayerData *p = PlayerData_Get(i);
            if (p != 0) {
                Unk_ov004_0222a374_Pair &e = Room_PlacePlayerBeds_tbl[i & 3];
                s32 x = e.a;
                s32 y = e.b;
                Unk_ov004_0222a374_Loc l;
                l.a = *p->getBed();
                BOOL r;
                if (Item_IsFurniture(&l.a) != 0) {
                    l.b = 0xfff1;
                    s32 t = Item_GetFurnitureIndex(&l.a);
                    r = (t == Item_GetFurnitureIndex(&l.b)) ? 1 : z1;
                } else {
                    if (l.a == 0xfff1) {
                        r = TRUE;
                    } else {
                        r = z0;
                    }
                }
                if (r == 0) {
                    Item_SetFurnitureDirection(&l.a, 3);
                    if (x < 8) {
                        if (Ftr_GetUnk05(&l.a) == 2) {
                            x--;
                        }
                    }
                    BlockMap_SetItemAtUnit(g, &l.a, x, y, z2);
                }
            }
        }
    }
}
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_0222a374) {
    HOST_OVERLAY_VAR(sPlayerBedSetterProfile),
    HOST_OVERLAY_VAR(Room_PlacePlayerBeds_tbl),
    HOST_OVERLAY_VARS_END
};
