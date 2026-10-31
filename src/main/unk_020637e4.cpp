#include "types.h"
#include "talk/MsgStringBase.h"
#include "talk/EncodedString.h"
#include "talk/MsgString.h"
#include "talk/MsgString9C.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_020637e4.h"

extern "C" const u16 data_020cb6f4;

extern "C" {
void MI_CpuCopy8(void *, void *, u32);
BOOL EncodedString_SetRaw(void *, const void *, s32);
}

class EncodedString8B : public EncodedString {
public:
    EncodedString8B();
    virtual ~EncodedString8B();
    virtual u32 capacity();
    virtual u8 *data();
    void copyBytesTo(void *p, u32 n);

    /* 0x0e */ u8 text[14];
};

extern "C" void TownId_GetNameString(void *src, MsgString *dst) {
    EncodedString8B buf;
    EncodedString_SetRaw(&buf, (u8 *)src + 2, 8);
    dst->fromEncoded(&buf, 0, 0);
}

extern "C" void TownId_SetNameString(u8 *dst, MsgString *src) {
    EncodedString8B buf;
    buf.fromMsgString(src);
    buf.copyBytesTo(dst + 2, 8);
}

MsgString9C::MsgString9C() {}

MsgString9C::~MsgString9C() {}

u32 MsgString9C::capacity() { return 9; }

u8 *MsgString9C::data() { return text; }

EncodedString8B::EncodedString8B() {}

EncodedString8B::~EncodedString8B() {}

u32 EncodedString8B::capacity() { return 8; }

void EncodedString8B::copyBytesTo(void *p, u32 n) { MI_CpuCopy8(text, p, n); }

u8 *EncodedString8B::data() { return text; }



const u16 data_020cb6f4 = 0xffff;
