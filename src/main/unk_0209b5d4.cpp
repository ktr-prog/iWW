#include "types.h"
#include "town/TownAcreGrid.h"
#include "sys/RecordFile.h"
#include "town/TownAcreCell.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0209b5d4.h"


extern "C" {
}


s32 sTownGenCandidateIndex;

void TownAcreGrid::loadCandidate(s32 seed) {
    u8 *p;
    u32 y, x;
    s32 v;
    if (seed < 0) {
        v = Random_GlobalBelow(0x20c);
    } else {
        v = (u32)seed % 0x20c;
    }
    sTownGenCandidateIndex = v;
    p = (u8 *)((RecordFile *)(&candidates))->getRecord(v);
    if (p) {
        for (y = 1; y < 5; y++) {
            for (x = 1; x < 5; x++) {
                (getCell(x, y))->setType(*p++);
            }
        }
    }
}
