#include "types.h"
#include "npc/VillagerId.h"
#include "save/SaveData.h"
#include "proto/main/unk_02002b1c.h"
#include "proto/main/unk_02003008.h"
#include "proto/main/unk_02063904.h"

extern "C" {
void MI_CpuFill8(void *p, u32 v, u32 n);
}
extern SaveData gSaveData;



extern const u32 sPersonalityVoiceTypes[];

u32 VillagerId::isValid() {
    if (TownId_IsValid(&townId) == 1 && VillagerId_IsValidSpecies(species) == 1) return TRUE;
    return FALSE;
}

void VillagerId::set(u32 id, u32 type, void *s) {
    species = id;
    personality = type;
    if (s == 0) s = gSaveData.townId;
    TownId_Assign(this, s);
}

extern "C" u32 VillagerId_GetPersonality(VillagerId *o) { return o->personality; }

extern "C" u32 Villager_PersonalityToGender(u32 t) {
    u32 r = 2;
    if (t < 3) r = 0;
    else if (t < 6) r = 1;
    return r;
}

u32 VillagerId::getGender() {
    return Villager_PersonalityToGender(VillagerId_GetPersonality(this));
}

extern "C" void Villager_MakePersonalityFileName(void *buf, u32 size, const char *key, u32 idx) {
    MI_CpuFill8(buf, 0, size);
    Str_SPrintf((char *)buf, "%s%s", sPersonalityPrefixes[idx], key);
}

void VillagerId::makeFileName(void *buf, u32 size, const char *arg) {
    Villager_MakePersonalityFileName(buf, size, arg, VillagerId_GetPersonality(this));
}

extern "C" u32 Villager_PersonalityToVoiceType(u32 t) {
    u32 r = 5;
    if (t < 6) r = sPersonalityVoiceTypes[t];
    return r;
}

extern const u32 sPersonalityVoiceTypes[6];

char sPersonalityPrefixSnooty[] = "ta_";

char sPersonalityPrefixJock[] = "ha_";

const u32 sPersonalityVoiceTypes[6] = {0, 0, 2, 1, 1, 1};

char sPersonalityPrefixNormal[] = "fu_";

char sPersonalityPrefixPeppy[] = "ge_";

char sPersonalityPrefixCranky[] = "ko_";

char *sPersonalityPrefixes[6] = {sPersonalityPrefixLazy, sPersonalityPrefixJock, sPersonalityPrefixCranky, sPersonalityPrefixNormal, sPersonalityPrefixPeppy, sPersonalityPrefixSnooty};

char sPersonalityPrefixLazy[] = "bo_";
