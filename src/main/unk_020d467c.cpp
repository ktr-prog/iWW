#include "types.h"

struct DataRef12 {
    const void *data;
    u32 count;
    u32 unk_8;
};
struct DataRef8 {
    const void *data;
    u32 count;
};

extern DataRef12 data_020d20b0[1];
extern DataRef12 data_020d2e04[4];

extern DataRef8 data_020d467c[2];

DataRef8 data_020d467c[2] = {
    {data_020d20b0, 1}, {data_020d2e04, 4},
};

extern DataRef8 data_020d468c[1];
extern DataRef8 data_020d4694[29];
extern DataRef8 data_020d477c[1];
extern DataRef8 data_020d4784[1];
extern DataRef8 data_020d478c[1];
extern DataRef8 data_020d4794[1];
extern DataRef8 data_020d479c[1];
extern DataRef8 data_020d47a4[8];

extern void *const gSpriteSeqTable[45];
void *const gSpriteSeqTable[45] = {
    &data_020d467c[0], &data_020d467c[1], &data_020d468c[0],
    &data_020d4694[0], &data_020d4694[1], &data_020d4694[2], &data_020d4694[3], &data_020d4694[4],
    &data_020d4694[5], &data_020d4694[6], &data_020d4694[7], &data_020d4694[8], &data_020d4694[9],
    &data_020d4694[10], &data_020d4694[11], &data_020d4694[12], &data_020d4694[13], &data_020d4694[14],
    &data_020d4694[15], &data_020d4694[16], &data_020d4694[17], &data_020d4694[18], &data_020d4694[19],
    &data_020d4694[20], &data_020d4694[21], &data_020d4694[22], &data_020d4694[23], &data_020d4694[24],
    &data_020d4694[25], &data_020d4694[26], &data_020d4694[27], &data_020d4694[28],
    &data_020d477c[0], &data_020d4784[0], &data_020d478c[0], &data_020d4794[0], &data_020d479c[0],
    &data_020d47a4[0], &data_020d47a4[1], &data_020d47a4[2], &data_020d47a4[3], &data_020d47a4[4],
    &data_020d47a4[5], &data_020d47a4[6], &data_020d47a4[7],
};
