#include "types.h"
#include "item/ItemPickSpec.h"
#include "npc/VillagerId.h"
#include "player/ForeignVillagerRecord.h"
#include "proto/main/unk_020030d8.h"
#include "proto/main/unk_0206269c.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02098d20.h"

extern const u32 sForeignLetterPresentKinds[];
const u32 sForeignLetterPresentKinds[] = {0, 4, 3};




extern "C" void Comm_OnFriendDeletedNop() {}

ForeignVillagerRecord::ForeignVillagerRecord() {
    TownId_Construct();
    VillagerId_Construct(&villager);
    present = 0xfff1;
}

ForeignVillagerRecord::~ForeignVillagerRecord() {
    VillagerId_Destruct(&villager);
    TownId_Destruct();
}

void ForeignVillagerRecord::clear() {
    TownId_Clear(&town.townId);
    VillagerId_Clear(&villager);
    present = 0xfff1;
    friendship = -0x80;
}

BOOL ForeignVillagerRecord::isSet() {
    if (TownId_IsValid(&town.townId) && villager.isValid()) return TRUE;
    return FALSE;
}

void ForeignVillagerRecord::set(void *a1, s32 a2, void *a3, u16 *p) {
    TownId_Assign(&town, a3);
    VillagerId_Copy(&villager, (VillagerId *)a1);
    present = *p;
    friendship = a2;
}

BOOL ForeignVillagerRecord::offer(void *a1, s32 a2, void *a3) {
    if (((VillagerId *)a1)->isValid() && TownId_IsValid((u16 *)a3)) {
        u16 local = 0xfff1;
        u16 out;
        if (Random_GlobalBelow(4) == 0) {
            ItemPickSpec t1;
            t1.set(sForeignLetterPresentKinds[Random_GlobalBelow(3)], 0);
            ItemPickSpec t2(t1);
            ItemPick_One(&out, &t2, 0, 0, 1, 1, 0);
            local = out;
        }
        if (isSet()) {
            if (a2 >= friendship) {
                set(a1, a2, a3, &local);
                return TRUE;
            }
        } else {
            set(a1, a2, a3, &local);
            return TRUE;
        }
    }
    return FALSE;
}

