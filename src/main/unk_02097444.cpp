#include "types.h"
#include "sys/StackPad.h"
#include "item/ItemId.h"
#include "player/PlayerData.h"
#include "net/CommManager.h"
#include "player/PlayerInventory.h"
#include "item/PlayerMailbox.h"
#include "player/PlayerId.h"
#include "item/LetterStorage.h"
#include "save/SaveData.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02093ff0.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_0209eb94.h"


class GuestPlayerArray {
public:
    GuestPlayerArray();
    ~GuestPlayerArray();
    PlayerData players[3];
};

extern SaveData gSaveData;

extern "C" {
extern CommManager *gCommManager;

void *MI_CpuFill8(void *, s32, u32);
s32 Item_GetPrice(u16 *);
}

static inline PlayerData *SavePlayers() { return (PlayerData *)gSaveData.players; }
static inline PlayerData *PlayerAt(u8 *base, s32 i) { return (PlayerData *)base + i; }


extern "C" s32 PlayerInventory_GetBellsRoom(u8 *p, s32 mode, s32 arg) {
    s32 x = 99999 - ((PlayerInventory *)(p))->getTotalBells(0);
    if (x < 0) x = 0;
    if (mode == 1) x += ((PlayerInventory *)(p))->getBellsSpace(arg);
    return x;
}

extern "C" s32 PlayerInventory_FindSmallestBag(u8 *p, s32 mode) {
    StackPad8 pad;
    u16 *q = ((PlayerInventory *)(p))->getPocket(0);
    s32 lim = mode == 1 ? 0x6b : 0x6a;
    s32 i = 0;
    s32 best = -1;
    for (; i < 15; q++, i++) {
        BOOL f1 = FALSE;
        u32 h = *q;
        if (h >= 0x1492 && h <= 0x14fd) f1 = TRUE;
        if (f1 && ((PlayerInventory *)(p))->getPocketFlags(i) == 0) {
            BOOL f2 = FALSE;
            s32 v;
            h = *q;
            if (h >= 0x1492 && h <= 0x14fd) f2 = TRUE;
            if (f2) v = h - 0x1492;
            else v = -1;
            if (v < lim || (best == ~0 && v == lim)) {
                lim = v;
                best = i;
            }
        }
    }
    return best;
}

extern "C" s32 PlayerInventory_FindBagSlot(u8 *p) {
    u16 *q = ((PlayerInventory *)(p))->getPocket(0);
    s32 i = 0;
    s32 r = -1;
    for (; i < 15; q++, i++) {
        if (*q == 0xfff1) {
            r = i;
            break;
        }
    }
    if (r == -1) r = PlayerInventory_FindSmallestBag(p, 0);
    return r;
}

extern "C" s32 PlayerInventory_StoreExcessInBags(u8 *p, s32 n) {
    u16 b[2];
    s32 a;
    b[0] = 0x14fd;
    a = Item_GetPrice(b);
    b[1] = 0xfff1;
    while ((u32)n > 99999) {
        s32 t = PlayerInventory_FindBagSlot(p);
        if (t == -1) break;
        b[1] = *((PlayerInventory *)(p))->getPocket(t);
        volatile u16 *vp = b;
        BOOL rr = FALSE;
        u32 c = vp[1];
        u32 a2 = vp[1];
        if (a2 >= 0x1492 && c <= 0x14fd) rr = TRUE;
        if (rr) {
            ((PlayerInventory *)(p))->setPocket(b, t, 0);
            n -= a - Item_GetPrice(&b[1]);
        } else {
            if (c != 0xfff1) break;
            ((PlayerInventory *)(p))->setPocket(b, t, 0);
            n -= a;
        }
    }
    return n;
}

extern "C" s32 PlayerInventory_PayWithBags(u8 *p, s32 n) {
    u16 b[2];
    if (n < 0) n = 0;
    b[0] = 0xfff1;
    while (n > 0) {
        s32 t = PlayerInventory_FindSmallestBag(p, 1);
        if (t == -1) break;
        b[0] = *((PlayerInventory *)(p))->getPocket(t);
        b[1] = 0xfff1;
        ((PlayerInventory *)(p))->setPocket(&b[1], t, 0);
        n -= Item_GetPrice(b);
    }
    if (n != 0) n = -n;
    return n;
}

extern "C" void PlayerInventory_SetWallet(PlayerInventory *p, s32 v, s32 mode) {
    if (v < 0) v = 0;
    if ((u32)v > 99999) {
        if (mode == 1) {
            v = PlayerInventory_StoreExcessInBags((u8 *)p, v);
            if ((u32)v > 99999) v = 99999;
        } else {
            v = 99999;
        }
    }
    p->wallet = v;
}

extern "C" BOOL PlayerInventory_CanAddBells(u8 *p, s32 v, s32 a, s32 b) {
    BOOL r = FALSE;
    if (v >= 0) {
        if (v <= PlayerInventory_GetBellsRoom(p, a, b)) r = TRUE;
    } else {
        if (-v <= ((PlayerInventory *)(p))->getTotalBells(a)) r = TRUE;
    }
    return r;
}

extern "C" void PlayerInventory_AddBells(u8 *p, s32 v, s32 mode) {
    s32 x = v + ((PlayerInventory *)(p))->getTotalBells(0);
    if (x < 0) {
        if (mode == 1) {
            x = PlayerInventory_PayWithBags(p, -x);
            if (x < 0) x = 0;
            else if ((u32)x > 99999) x = 99999;
        } else {
            x = 0;
        }
    }
    PlayerInventory_SetWallet((PlayerInventory *)p, x, mode);
}

extern "C" u8 *PlayerData_GetFutureLetter(PlayerData *p) { return p->futureLetter; }

extern "C" u8 *PlayerData_GetMotherLetterState(PlayerData *p) { return p->motherLetterState; }

extern "C" u8 *PlayerData_GetLetterStorage(void *p) {
    s32 s = ((PlayerData *)(p))->getIndex();
    if (s >= 0 && s < 4) {
        u8 *q = SaveManager_GetLetterStorage();
        if (q != 0) return (u8 *)((LetterStorage *)q + s);
    }
    return 0;
}

extern "C" u8 *PlayerData_GetMailbox(void *p) {
    s32 s = ((PlayerData *)(p))->getIndex();
    if (s >= 0 && s < 4) return gSaveData.mailboxes[s];
    return 0;
}

extern "C" u8 *PlayerData_GetDresser(void *p) {
    s32 s = ((PlayerData *)(p))->getIndex();
    if (s >= 0 && s < 4) return gSaveData.dressers[s];
    return 0;
}

extern "C" s32 PlayerData_GetLastWifiMailId(void *p) {
    s32 s = ((PlayerData *)(p))->getIndex();
    if (s >= 0 && s < 4) return ((PlayerMailbox *)gSaveData.mailboxes[s])->getLastWifiMailId();
    return 0;
}

extern "C" void PlayerData_SetLastWifiMailId(void *p, s32 v) {
    s32 s = ((PlayerData *)(p))->getIndex();
    if (s >= 0 && s < 4) ((PlayerMailbox *)gSaveData.mailboxes[s])->setLastWifiMailId(v);
}

extern "C" void *PlayerDataArray_Construct(void *p) {
    for (s32 i = 0; i < 4; i++) {
        new ((PlayerData *)p + i) PlayerData();
    }
    return p;
}

extern "C" void *PlayerDataArray_Destruct(void *p) {
    for (s32 i = 4 - 1; i >= 0; i--) {
        ((PlayerData *)p + i)->~PlayerData();
    }
    return p;
}

extern "C" s32 PlayerData_IsResidentIndex(u32 idx) {
    if (idx < 4) return 1;
    return 0;
}

extern "C" s32 PlayerDataArray_IsUsed(u8 *base, s32 idx) {
    if (PlayerData_IsResidentIndex(idx) != 0) {
        if (PlayerAt(base, idx)->isUsed() != 0) return 1;
    }
    return 0;
}

extern "C" u32 PlayerDataArray_CountUsed(u8 *base) {
    s32 i;
    u32 n = 0;
    for (i = n; i < 4; i++) {
        if (PlayerDataArray_IsUsed(base, i) != 0) n++;
    }
    return n;
}

extern "C" u8 *PlayerDataArray_GetById(u8 *base, u16 *p) { return PlayerData_GetResident(base, PlayerDataArray_FindById(base, p)); }

extern "C" u8 *PlayerData_GetResident(u8 *base, s32 idx) {
    u8 *r = 0;
    if (PlayerData_IsResidentIndex(idx) != 0) r = (u8 *)PlayerAt(base, idx);
    return r;
}

extern "C" u8 *PlayerDataArray_GetRandomOther(u8 *base, u16 *p) {
    u8 *r;
    s32 n;
    if (p == 0 || PlayerDataArray_GetById(base, p) == 0) n = PlayerDataArray_CountUsed(base);
    else n = PlayerDataArray_CountUsed(base) - 1;
    r = 0;
    if (n > 0) {
        u32 t = Random_GlobalBelow(n);
        s32 i;
        for (i = 0; i < 4; i++) {
            PlayerData *e = PlayerAt(base, i);
            if (e->isUsed() == 1) {
                if (p != 0) {
                    u16 *q = (u16 *)e->getPlayerId();
                    if (p[0] == q[0]) {
                        if (memcmp(p + 1, q + 1, 8) == 0) {
                            if (((PlayerId *)(p))->equals((PlayerId *)(q)) != 0) continue;
                        }
                    }
                }
                if (t == 0) {
                    r = (u8 *)e;
                    break;
                }
                t--;
            }
        }
    }
    return r;
}

extern "C" void PlayerDataArray_ResetAll(void *p) {
    s32 i;
    for (i = 0; i < 4; i++) ((PlayerData *)p + i)->reset();
}

extern "C" s32 PlayerDataArray_FindUnused(void *p) { return ((PlayerData *)(p))->findUnusedSlot(4); }

extern "C" s32 PlayerDataArray_FindById(u8 *base, u16 *p) {
    if (((PlayerId *)(p))->isValid() == 1) {
        s32 i;
        for (i = 0; i < 4; i++) {
            u16 *q = (u16 *)PlayerAt(base, i)->getPlayerId();
            if (p[0] == q[0]) {
                if (memcmp(p + 1, q + 1, 8) == 0) {
                    if (((PlayerId *)(p))->equals((PlayerId *)(q)) != 0) return i;
                }
            }
        }
    }
    return -1;
}

extern "C" u8 *PlayerDataArray_CreateResident(u8 *base, void *name, s32 a2, u32 idx) {
    u8 *r = 0;
    if (PlayerData_IsResidentIndex(idx) == 1) {
        static ItemId tbl[4] = {ItemId(0x3884), ItemId(0x3888), ItemId(0x388c), ItemId(0x3890)};
        u16 hdr;
        u16 v[3];
        s32 i;
        PlayerData *player = PlayerAt(base, idx);
        r = (u8 *)player;
        u16 cnt = 0;
        MI_CpuFill8(v, 0, 6);
        for (i = 0; i < 4; i++) {
            if (i != idx) {
                PlayerData *q = PlayerAt(base, i);
                if (q->getPlayerId()->isValid() == 1) {
                    v[cnt] = q->getPlayerId()->getId();
                    cnt++;
                }
            }
        }
        player->reset();
        hdr = 0xfff1;
        {
            u32 s = PlayerId_GenerateUniqueId(v, cnt);
            player->setupNew(name, s, a2, NULL, 0, 0, 0, 0, 0, 0, &hdr);
        }
        idx &= 3;
        player->setBed(&tbl[idx].id);
    }
    return r;
}

GuestPlayerArray gGuestPlayers;

GuestPlayerArray::GuestPlayerArray() {}

GuestPlayerArray::~GuestPlayerArray() {}

extern "C" PlayerData *GuestPlayers_Get() { return gGuestPlayers.players; }

extern "C" void GuestPlayers_Reset(PlayerData *p) {
    s32 i;
    for (i = 0; i < 3; i++) p[i].reset();
}

extern "C" void GuestPlayers_ResetAll() { GuestPlayers_Reset(GuestPlayers_Get()); }

extern "C" s32 PlayerData_IsGuestIndex(s32 idx) {
    if (idx >= 4 && idx < 7) return 1;
    return 0;
}

extern "C" s32 PlayerData_GetGuestSlot(s32 idx) {
    s32 r = -1;
    if (PlayerData_IsGuestIndex(idx) == 1) r = idx - 4;
    return r;
}

extern "C" PlayerData *PlayerData_GetBySessionSlot(u32 a) { return PlayerData_Get(PlayerSession_GetDataIndex(a)); }

extern "C" PlayerData *PlayerData_GetCurrent() { return PlayerData_GetBySessionSlot(gCommManager->localSlot); }

extern "C" u32 PlayerData_GetCurrentIndex() { return PlayerSession_GetDataIndex(gCommManager->localSlot); }

extern "C" PlayerData *PlayerData_Get(s32 idx) {
    PlayerData *r = NULL;
    if (PlayerData_IsResidentIndex(idx) == 1) {
        r = (PlayerData *)PlayerData_GetResident(gSaveData.players, idx);
    } else if (PlayerData_IsGuestIndex(idx) == 1) {
        if (GuestPlayers_Get() != NULL) {
            r = GuestPlayers_Get() + PlayerData_GetGuestSlot(idx);
        }
    }
    return r;
}

extern "C" s32 PlayerData_IsUsedByIndex(s32 idx) {
    s32 r = 0;
    if (PlayerData_IsResidentIndex(idx) == 1) {
        r = PlayerDataArray_IsUsed(gSaveData.players, idx);
    } else if (PlayerData_IsGuestIndex(idx) == 1) {
        if (GuestPlayers_Get() != 0) {
            s32 t = PlayerData_GetGuestSlot(idx);
            r = GuestPlayers_Get()[t].isUsed();
        }
    }
    return r;
}

