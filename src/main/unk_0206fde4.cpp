#include "types.h"
#include "gfx/Mtx43.h"
#include "save/MuseumData.h"
#include "proto/main/unk_02052b50.h"
#include "proto/main/unk_0206fc44.h"
#include "proto/main/unk_0206fde4.h"




extern "C" {
}

Mtx43 sCpuMtxStack[31];

static inline u32 Unk_0206fe34_Id(u32 i) {
    if (i < 0x34) {
        return i * 4 + 0x450c;
    }
    return 0x450c;
}

extern "C" s32 Museum_CountDonatedFossilsInGroup(MuseumData *a, s32 b) {
    s32 cnt = 0;
    u32 i;
    for (i = 0; i < 0x34; i++) {
        u16 v = Unk_0206fe34_Id(i);
        if (b == Item_GetFossilGroup(&v)) {
            if (a->isDonated(&v)) {
                cnt++;
            }
        }
    }
    return cnt;
}

extern "C" void CpuMtx_StoreToStack(u32 i) {
    sCpuMtxStack[i] = *(Mtx43 *)&data_021cb69c;
}

extern "C" void CpuMtx_RestoreFromStack(u32 i) {
    *(Mtx43 *)&data_021cb69c = sCpuMtxStack[i];
}
