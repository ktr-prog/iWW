#include "types.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_020a6914.h"


extern "C" {
}

extern "C" void NetSceneMsg_Init(void) {}

extern "C" void NetSceneMsg_Fini(void) {}

extern "C" void NetSceneMsg_Set(u8 *a, u8 b) { *a = b; }

extern "C" void NetSceneMsg_Get(u8 *a, u8 *b) { *b = *a; }

extern "C" void NetStatusMsgBase_Init(void) {}

extern "C" void NetStatusMsgBase_Fini(void) {}

extern "C" void NetStatusMsgBase_Pack(u8 *p, int a, int b, int c, u8 d, int e) {
    u8 flags = 0;
    if (c) flags |= 1;
    if (d) flags |= 2;
    CommRecord_PackSource(p, b, flags);
    p[1] = e;
    p[1] |= (a << 6) & 0xc0;
}
