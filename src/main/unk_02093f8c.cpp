#include "types.h"
#include "talk/MsgStringBase.h"
#include "talk/MsgStringAttr.h"
#include "talk/EncodedStringBase.h"
#include "talk/MsgString.h"
#include "talk/EncodedString.h"
#include "talk/EncodedString8.h"
#include "proto/main/unk_02093f8c.h"

extern "C" const s32 data_020d03cc;
extern "C" const s32 data_020d03d0;
extern "C" const s32 data_020d03d4;

extern "C" {
void MI_CpuCopy8(const void *src, void *dst, u32 n);
}

EncodedString8::EncodedString8() {}

EncodedString8::~EncodedString8() {}

u32 EncodedString8::capacity() { return 8; }

void EncodedString8::copyTo(void *dst, u32 n) { MI_CpuCopy8(text, dst, n); }

u8 *EncodedString8::data() { return text; }

extern const s32 data_020d03d4;
extern const s32 data_020d03d0;
extern const s32 data_020d03cc;

const s32 data_020d03d4 = 0x7ffc;

const s32 data_020d03d0 = 0x7fff;

const s32 data_020d03cc = 0x7ffd;
