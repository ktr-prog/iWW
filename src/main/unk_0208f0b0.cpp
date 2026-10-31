#include "types.h"
#include "host_labels.h"
#include "save/TownExchangeRecord.h"
#include "game/ConstellationRecord.h"
#include "item/Letter.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_02085940.h"
#include "proto/main/unk_0208f0b0.h"
#include "proto/main/unk_020b0774.h"

extern "C" {
s32 func_02065578();
void VillagerTransfer_DestructVillager(void *p);
void VillagerTransfer_ConstructVillager(void *p);
void MI_CpuFill8(void *p, s32 v, u32 n);
}

#define data_021e7f8c HOST_LABEL(u8 (*)[], data_021e7f8c)

struct TownExchangeFlagBits {
    u8 b0 : 1;
};


class TownExchangeRemoteRecords {
public:
    TownExchangeRemoteRecords();
    ~TownExchangeRemoteRecords();
    TownExchangeRecord records[3];
};

static_assert(sizeof(ConstellationRecord) <= sizeof(((TownExchangeRecord *)0)->constellation), "ConstellationRecord");

TownExchangeRemoteRecords sTownExchangeRemoteRecords;


TownExchangeRecord::TownExchangeRecord() {
    new (this) Letter();
    new (constellation) ConstellationRecord();
    VillagerTransfer_ConstructVillager(villager);
    LostChildRecord_Construct(lostChild);
}

TownExchangeRecord::~TownExchangeRecord() {
    LostChildRecord_Destruct(lostChild);
    VillagerTransfer_DestructVillager(villager);
    ((ConstellationRecord *)constellation)->~ConstellationRecord();
    ((Letter *)(this))->Letter::~Letter();
}

extern "C" void TownExchange_InitNop() {}

extern "C" void TownExchange_Clear(void *p) {
    TownExchangeRecord *r = (TownExchangeRecord *)p;
    MI_CpuFill8(r, 0, sizeof(TownExchangeRecord));
    Letter_Clear((LetterView *)r);
    ConstellationRecord_Clear((ConstellationRecord *)r->constellation);
}

void TownExchangeRecord::setChecksum(u32 v) { checksum = v; }

u32 TownExchangeRecord::getChecksum() { return checksum; }

s32 TownExchangeRecord::isValid() { return 1; }

void TownExchangeRecord::setUnkFlag(u32 v) { flags = (flags & ~1) | (v & 1); }

u32 TownExchangeRecord::getUnkFlag() { return ((TownExchangeFlagBits *)&flags)->b0; }

void *TownExchangeRecord::getLostChildRecord() { return lostChild; }

void TownExchangeRecord::incrementCounter() {
    s32 v = counter + 1;
    if (v > 5) {
        v = 5;
    }
    counter = v;
}

void TownExchangeRecord::resetCounter() { counter = 0; }

u32 TownExchangeRecord::getCounter() { return counter; }

extern "C" void *TownExchange_GetLetter(void *p) { return p; }

void *TownExchangeRecord::getConstellation() { return constellation; }

void *TownExchangeRecord::getVillager() { return villager; }

TownExchangeRemoteRecords::TownExchangeRemoteRecords() {}

TownExchangeRemoteRecords::~TownExchangeRemoteRecords() {}

extern "C" void *TownExchange_GetRemote(s32 i) { return &sTownExchangeRemoteRecords.records[i]; }

extern "C" void *TownExchange_GetForAid(s32 i) {
    switch (i) {
    case 1:
        return TownExchange_GetRemote(0);
    case 2:
        return TownExchange_GetRemote(1);
    case 3:
        return TownExchange_GetRemote(2);
    default:
        return data_021e7f8c;
    }
}

