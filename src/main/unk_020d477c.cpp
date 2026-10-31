#include "types.h"
#include "proto/main/unk_020d477c.h"

struct DataRef12 {
    const void *data;
    u32 count;
    u32 unk_8;
};
struct DataRef8 {
    const void *data;
    u32 count;
};

extern DataRef12 data_020d20a4[1];
extern DataRef12 data_020d221c[2];
extern DataRef12 data_020d3540[5];
extern DataRef12 data_020d357c[5];
extern DataRef12 data_020d35f4[5];
extern DataRef12 data_020d3900[5];
extern DataRef12 data_020d3978[5];
extern DataRef12 data_020d3af4[6];
extern DataRef12 data_020d3b84[6];
extern DataRef12 data_020d3bcc[6];
extern DataRef12 data_020d3c5c[6];
extern DataRef12 data_020d3ca4[6];
extern DataRef12 data_020d41cc[20];

extern DataRef8 data_020d47a4[8];
extern DataRef8 data_020d4794[1];
extern DataRef8 data_020d478c[1];
extern DataRef8 data_020d479c[1];
extern DataRef8 data_020d477c[1];
extern DataRef8 data_020d4784[1];

DataRef8 data_020d47a4[8] = {
    {data_020d221c, 2}, {data_020d3ca4, 6}, {data_020d357c, 5}, {data_020d41cc, 20},
    {data_020d3bcc, 6}, {data_020d3978, 5}, {data_020d3af4, 6}, {data_020d3900, 5},
};

u16 sDefaultToonTable[32] = {
    0x3dcd, 0x3dcd, 0x39ac, 0x39ac, 0x356a, 0x356a, 0x314a, 0x314a,
    0x314a, 0x314a, 0x318b, 0x318b, 0x3a11, 0x3a11, 0x46b8, 0x46b8,
    0x535d, 0x535d, 0x77ff, 0x77ff, 0x7bff, 0x7bff, 0x7fff, 0x7fff,
    0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff,
};

DataRef8 data_020d4794[1] = {
    {data_020d3b84, 6},
};

DataRef8 data_020d478c[1] = {
    {data_020d20a4, 1},
};

DataRef8 data_020d479c[1] = {
    {data_020d3c5c, 6},
};

DataRef8 data_020d477c[1] = {
    {data_020d3540, 5},
};

DataRef8 data_020d4784[1] = {
    {data_020d35f4, 5},
};
