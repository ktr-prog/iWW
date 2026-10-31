#include "types.h"
#include "actor/NpcActor.h"
#include "actor/VillagerActor.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_020815f8.h"
#include "proto/main/unk_0204cc1c.h"



extern "C" {
s32 SaveVillagers_IsValidIndex(s32);
s32 Item_IsFurniture(u16 *);
s32 Item_GetFurnitureIndex(u16 *);
}

struct NpcRegistrySpNpcSlot {
    NpcActor *actor;
    u16 npcHandle;
    ~NpcRegistrySpNpcSlot();
    NpcRegistrySpNpcSlot();
};

struct NpcRegistryVillagerSlot {
    NpcActor *actor;
    u16 npcHandle;
    ~NpcRegistryVillagerSlot();
    NpcRegistryVillagerSlot();
};

struct NpcActorRegistry {
    NpcRegistryVillagerSlot villagers[8];
    NpcRegistrySpNpcSlot spNpcs[4];

    void clear();
    ~NpcActorRegistry();
    BOOL isSpNpcSlotUsed(NpcRegistrySpNpcSlot *s);
    BOOL isVillagerSlotUsed(NpcRegistryVillagerSlot *s);
    void clearSpNpcSlots(NpcRegistrySpNpcSlot *s, s32 n);
    void clearVillagerSlots(NpcRegistryVillagerSlot *s, s32 n);
    s32 findSpNpcSlot(u16 *p);
    s32 findVillagerSlot(u16 *p);
    NpcActor *getSpNpc(s32 i);
    NpcActor *findSpNpcByHandle(u16 *p);
    NpcActor *findSpNpcAt(s32 a, s32 b);
    NpcActor *findSpNpcByIndex(u32 v);
    BOOL removeSpNpc(u16 *p);
    BOOL addSpNpc(NpcActor *o, u16 *p);
    NpcActor *pickRandomVillager(s32 *idx);
    NpcActor *getVillager(s32 i);
    NpcActor *findVillagerByHandle(u16 *p);
    NpcActor *findVillagerAt(s32 a, s32 b);
    NpcActor *findVillagerByIndex(u32 v);
    BOOL removeVillager(u16 *p);
    BOOL addVillager(NpcActor *o, u16 *p);
};

NpcActorRegistry gNpcActorRegistry;


NpcRegistryVillagerSlot::NpcRegistryVillagerSlot() { npcHandle = 0xfff1; }

NpcRegistryVillagerSlot::~NpcRegistryVillagerSlot() {}

NpcRegistrySpNpcSlot::NpcRegistrySpNpcSlot() { npcHandle = 0xfff1; }

NpcRegistrySpNpcSlot::~NpcRegistrySpNpcSlot() {}

NpcActorRegistry::~NpcActorRegistry() {}

void NpcActorRegistry::clear() {
    clearVillagerSlots(villagers, 8);
    clearSpNpcSlots(spNpcs, 4);
}

void NpcActorRegistry::clearVillagerSlots(NpcRegistryVillagerSlot *s, s32 n) {
    s32 i = 0;
    for (; i < n; i++) {
        s->actor = 0;
        s->npcHandle = 0xfff1;
        s++;
    }
}

BOOL NpcActorRegistry::isVillagerSlotUsed(NpcRegistryVillagerSlot *s) {
    if (s->actor != 0 && ((s->npcHandle & 0xf000) >> 12) == 0xe) {
        return TRUE;
    }
    return FALSE;
}

s32 NpcActorRegistry::findVillagerSlot(u16 *p) {
    s32 i = 0;
    s32 found = -1;
    BOOL z1 = FALSE;
    BOOL z2 = FALSE;
    for (; i < 8; i++) {
        NpcRegistryVillagerSlot *s = &villagers[i];
        BOOL r;
        if (Item_IsFurniture(&s->npcHandle)) {
            r = (Item_GetFurnitureIndex(&s->npcHandle) == Item_GetFurnitureIndex(p)) ? TRUE : z1;
        } else {
            r = (s->npcHandle == *p) ? TRUE : z2;
        }
        if (r) {
            found = i;
            break;
        }
    }
    return found;
}

BOOL NpcActorRegistry::addVillager(NpcActor *o, u16 *p) {
    BOOL r = FALSE;
    if (findVillagerSlot(p) == -1) {
        u16 t = 0xfff1;
        s32 i = findVillagerSlot(&t);
        if (i >= 0 && i < 8) {
            villagers[i].actor = o;
            villagers[i].npcHandle = *p;
            r = TRUE;
        }
    }
    return r;
}

BOOL NpcActorRegistry::removeVillager(u16 *p) {
    s32 i = findVillagerSlot(p);
    BOOL r = FALSE;
    if (i >= 0 && i < 8) {
        villagers[i].actor = 0;
        villagers[i].npcHandle = 0xfff1;
        r = TRUE;
    }
    return r;
}

NpcActor *NpcActorRegistry::findVillagerByIndex(u32 v) {
    NpcActor *r;
    u16 t = 0xfff1;
    r = 0;
    t = (v & 0xfff) | 0xe000;
    s32 i = findVillagerSlot(&t);
    if (i >= 0 && i < 8) {
        r = villagers[i].actor;
    }
    return r;
}

NpcActor *NpcActorRegistry::findVillagerAt(s32 a, s32 b) {
    NpcActor *r = 0;
    NpcRegistryVillagerSlot *s = villagers;
    s32 x = 0;
    s32 y = 0;
    s32 i;
    for (i = 0; i < 8; s++, i++) {
        if (isVillagerSlotUsed(s)) {
            FieldPos_ToUnit(&x, &y, &s->actor->position);
            if (x == a && y == b) {
                r = s->actor;
                break;
            }
        }
    }
    return r;
}

NpcActor *NpcActorRegistry::findVillagerByHandle(u16 *p) {
    NpcActor *r = 0;
    if (((*p & 0xf000) >> 12) == 0xe) {
        s32 i = findVillagerSlot(p);
        if (i >= 0 && i < 8) {
            r = villagers[i].actor;
        }
    }
    return r;
}

NpcActor *NpcActorRegistry::getVillager(s32 i) {
    NpcActor *r = 0;
    if (SaveVillagers_IsValidIndex(i)) {
        NpcRegistryVillagerSlot *s = &villagers[i];
        if (isVillagerSlotUsed(s)) {
            r = s->actor;
        }
    }
    return r;
}

NpcActor *NpcActorRegistry::pickRandomVillager(s32 *idx) {
    s32 cnt = 0;
    NpcActor *r = 0;
    s32 i = cnt;
    for (; i < 8; i++) {
        NpcRegistryVillagerSlot *s = &villagers[i];
        if (isVillagerSlotUsed(s) && ((VillagerActor *)s->actor)->isPickable()) {
            cnt++;
        }
    }
    if (cnt > 0) {
        s32 n = Random_GlobalBelow(cnt);
        for (i = 0; i < 8; i++) {
            NpcRegistryVillagerSlot *s = &villagers[i];
            if (isVillagerSlotUsed(s) && ((VillagerActor *)s->actor)->isPickable()) {
                if (n == 0) {
                    r = s->actor;
                    if (idx) {
                        *idx = i;
                    }
                    break;
                }
                n--;
            }
        }
    }
    return r;
}

void NpcActorRegistry::clearSpNpcSlots(NpcRegistrySpNpcSlot *s, s32 n) {
    s32 i = 0;
    for (; i < n; i++) {
        s[i].actor = 0;
        s[i].npcHandle = 0xfff1;
    }
}

BOOL NpcActorRegistry::isSpNpcSlotUsed(NpcRegistrySpNpcSlot *s) {
    if (s->actor != 0 && ((s->npcHandle & 0xf000) >> 12) == 0xd) {
        return TRUE;
    }
    return FALSE;
}

s32 NpcActorRegistry::findSpNpcSlot(u16 *p) {
    s32 i = 0;
    s32 found = -1;
    BOOL z1 = FALSE;
    BOOL z2 = FALSE;
    for (; i < 4; i++) {
        BOOL r;
        if (Item_IsFurniture(&spNpcs[i].npcHandle)) {
            r = (Item_GetFurnitureIndex(&spNpcs[i].npcHandle) == Item_GetFurnitureIndex(p)) ? TRUE : z1;
        } else {
            u32 a = spNpcs[i].npcHandle;
            u32 b = *p;
            r = (a == b) ? TRUE : z2;
        }
        if (r) {
            found = i;
            break;
        }
    }
    return found;
}

BOOL NpcActorRegistry::addSpNpc(NpcActor *o, u16 *p) {
    if (findSpNpcSlot(p) == -1) {
        u16 t = 0xfff1;
        s32 i = findSpNpcSlot(&t);
        if (i >= 0 && i < 4) {
            spNpcs[i].actor = o;
            spNpcs[i].npcHandle = *p;
            return TRUE;
        }
    }
    return FALSE;
}

BOOL NpcActorRegistry::removeSpNpc(u16 *p) {
    s32 i = findSpNpcSlot(p);
    BOOL r = FALSE;
    if (i >= 0 && i < 4) {
        spNpcs[i].actor = 0;
        spNpcs[i].npcHandle = 0xfff1;
        r = TRUE;
    }
    return r;
}

NpcActor *NpcActorRegistry::findSpNpcByIndex(u32 v) {
    NpcActor *r;
    u16 t = 0xfff1;
    r = 0;
    t = (v & 0xfff) | 0xd000;
    s32 i = findSpNpcSlot(&t);
    if (i >= 0 && i < 4) {
        r = spNpcs[i].actor;
    }
    return r;
}

NpcActor *NpcActorRegistry::findSpNpcAt(s32 a, s32 b) {
    NpcActor *r = 0;
    NpcRegistrySpNpcSlot *s = spNpcs;
    s32 x = 0;
    s32 y = 0;
    s32 i;
    for (i = 0; i < 4; s++, i++) {
        if (isSpNpcSlotUsed(s)) {
            FieldPos_ToUnit(&x, &y, &s->actor->position);
            if (x == a && y == b) {
                r = s->actor;
                break;
            }
        }
    }
    return r;
}

NpcActor *NpcActorRegistry::findSpNpcByHandle(u16 *p) {
    NpcActor *r = 0;
    if (((*p & 0xf000) >> 12) == 0xd) {
        s32 i = findSpNpcSlot(p);
        if (i >= 0 && i < 4) {
            r = spNpcs[i].actor;
        }
    }
    return r;
}

NpcActor *NpcActorRegistry::getSpNpc(s32 i) {
    NpcActor *r = 0;
    if (i >= 0 && i < 4) {
        NpcRegistrySpNpcSlot *s = &spNpcs[i];
        if (isSpNpcSlotUsed(s)) {
            r = s->actor;
        }
    }
    return r;
}

extern "C" void NpcRegistry_Clear() { gNpcActorRegistry.clear(); }

extern "C" s32 NpcRegistry_GetSlotCount() { return 12; }

extern "C" NpcActor *NpcRegistry_GetVillager(s32 i) {
    if (SaveVillagers_IsValidIndex(i)) {
        return gNpcActorRegistry.getVillager(i);
    }
    return 0;
}

extern "C" NpcActor *NpcRegistry_GetBySlot(s32 n) {
    NpcActor *r = NULL;
    if (n >= 0) {
        if (SaveVillagers_IsValidIndex(n)) {
            r = gNpcActorRegistry.getVillager(n);
        } else if (n < NpcRegistry_GetSlotCount()) {
            r = gNpcActorRegistry.getSpNpc(n - 8);
        }
    }
    return r;
}

extern "C" NpcActor *NpcRegistry_FindVillager(u32 idx) {
    return gNpcActorRegistry.findVillagerByIndex(idx);
}

extern "C" NpcActor *NpcRegistry_FindSpNpc(u32 idx) {
    return gNpcActorRegistry.findSpNpcByIndex(idx);
}

extern "C" NpcActor *NpcRegistry_FindByKind(s32 kind, u32 x) {
    NpcActor *r = NULL;
    switch (kind) {
    case 2:
        r = NpcRegistry_FindVillager(x);
        break;
    case 3:
        r = NpcRegistry_FindSpNpc(x);
        break;
    }
    return r;
}

extern "C" NpcActor *NpcRegistry_FindByHandle(u16 *p) {
    NpcActor *r = NULL;
    s32 t = (s32)(*p & 0xf000) >> 12;
    if (t != 13) {
        if (t == 14) r = NpcRegistry_FindVillagerByHandle(p);
    } else {
        r = NpcRegistry_FindSpNpcByHandle(p);
    }
    return r;
}

extern "C" NpcActor *NpcRegistry_FindVillagerByHandle(u16 *p) {
    return gNpcActorRegistry.findVillagerByHandle(p);
}

extern "C" NpcActor *NpcRegistry_FindSpNpcByHandle(u16 *p) {
    return gNpcActorRegistry.findSpNpcByHandle(p);
}

extern "C" NpcActor *NpcRegistry_FindAt(s32 x, s32 y) {
    NpcActor *r = gNpcActorRegistry.findVillagerAt(x, y);
    if (r == 0) r = gNpcActorRegistry.findSpNpcAt(x, y);
    return r;
}

extern "C" NpcActor *NpcRegistry_PickRandomVillager(s32 *idx) {
    return gNpcActorRegistry.pickRandomVillager(idx);
}

extern "C" s32 NpcRegistry_AddVillager(NpcActor *actor, u16 *handle) {
    return gNpcActorRegistry.addVillager(actor, handle);
}

extern "C" s32 NpcRegistry_RemoveVillager(u16 *handle) {
    return gNpcActorRegistry.removeVillager(handle);
}

extern "C" s32 NpcRegistry_AddSpNpc(NpcActor *actor, u16 *handle) {
    return gNpcActorRegistry.addSpNpc(actor, handle);
}

extern "C" s32 NpcRegistry_RemoveSpNpc(u16 *handle) {
    return gNpcActorRegistry.removeSpNpc(handle);
}

