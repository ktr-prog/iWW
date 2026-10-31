#include "host_labels.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

extern u32 data_021fcbf4, data_021fcc00, data_021fcc04, data_021fcc08;
typedef struct { u16 x, y, z; } T6;
extern const T6 data_02139f54[16];
#define data_02139f56 HOST_LABEL(const T6 (*)[], data_02139f56)
#define data_02139f58 HOST_LABEL(const T6 (*)[], data_02139f58)
s32 GX_ResetBankForTex(void);

void GX_BeginLoadTex(void) {
    s32 i = GX_ResetBankForTex();
    data_021fcc00 = i;
    data_021fcbf4 = (u32)data_02139f54[i].x << 12;
    data_021fcc04 = (u32)data_02139f56[i].x << 12;
    data_021fcc08 = (u32)data_02139f58[i].x << 12;
}

const T6 data_02139f54[16] = {
    {0x0000, 0x0000, 0x0000}, {0x6800, 0x0000, 0x0000}, {0x6820, 0x0000, 0x0000}, {0x6800, 0x0000, 0x0000},
    {0x6840, 0x0000, 0x0000}, {0x6800, 0x6840, 0x0020}, {0x6820, 0x0000, 0x0000}, {0x6800, 0x0000, 0x0000},
    {0x6860, 0x0000, 0x0000}, {0x6800, 0x6860, 0x0020}, {0x6820, 0x6860, 0x0020}, {0x6800, 0x6860, 0x0040},
    {0x6840, 0x0000, 0x0000}, {0x6800, 0x6840, 0x0020}, {0x6820, 0x0000, 0x0000}, {0x6800, 0x0000, 0x0000},
};

#include "host_labels.h"

HOST_LABEL_DEFINE(data_02139f56, (char *)&data_02139f54[0].y);
HOST_LABEL_DEFINE(data_02139f58, (char *)&data_02139f54[0].z);
