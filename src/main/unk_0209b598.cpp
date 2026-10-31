#include "town/TownAcreGrid.h"
#include "types.h"
#include "proto/main/unk_0209b598.h"


s32 sTownGenGateMode = 3;

extern "C" void Town_SetGenGateMode(s32 v) {
    sTownGenGateMode = v;
}

extern "C" void Town_GenerateAcres(u8 *acres) {
    TownAcreGenerator gen;
    gen.generate(sTownGenGateMode);
    gen.writeAcreIds(acres);
}
