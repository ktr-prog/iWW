#include "types.h"
#include "game/Unk_020dd30c_Buf.h"
#include "talk/MsgStringBase.h"
#include "talk/MsgStringAttr.h"
#include "talk/EncodedStringBase.h"
#include "talk/MsgString.h"
#include "talk/EncodedString.h"
#include "item/ItemName.h"
#include "talk/EncodedString16Buf.h"
#include "proto/main/unk_02062498.h"

extern "C" void MI_CpuFill8(void *p, u32 v, u32 n);


EncodedString16Buf::EncodedString16Buf() {
    u32 n = capacity();
    MI_CpuFill8(data(), 0, n);
}

EncodedString16Buf::EncodedString16Buf(u8 *src) {
    u32 n = capacity();
    MI_CpuFill8(data(), 0, n);
    *(Unk_020dd30c_Buf *)text = *(Unk_020dd30c_Buf *)src;
}

EncodedString16Buf::~EncodedString16Buf() {}

u32 EncodedString16Buf::capacity() { return 0x10; }

u8 *EncodedString16Buf::data() { return text; }

