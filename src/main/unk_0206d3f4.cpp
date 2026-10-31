#include "types.h"
#include "sys/StackPad.h"
#include "nitro/fs.h"
#include "talk/MsgStringAttr.h"
#include "talk/EncodedStringBase.h"
#include "talk/EncodedString.h"
#include "talk/EncodedString40.h"
#include "ui/LetterRenderer.h"
#include "ui/LetterTextLine.h"
#include "proto/autoload_2/unk_020e8208.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020e9a08.h"
#include "proto/autoload_2/unk_0210f154.h"
#include "proto/autoload_2/unk_02113088.h"
#include "proto/autoload_2/unk_02114cd8.h"
#include "proto/autoload_2/unk_02119434.h"
#include "proto/main/unk_02000c2c.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_020116e0.h"
#include "proto/main/unk_02037734.h"
#include "proto/main/unk_0203cbc0.h"
#include "proto/main/unk_0204eeb4.h"
#include "proto/main/unk_020501d4.h"
#include "proto/main/unk_02051218.h"
#include "proto/main/unk_020536dc.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_0206d3f4.h"
#include "proto/main/unk_0206d5b8.h"
#include "proto/main/unk_0206d988.h"
#include "proto/main/unk_020720f8.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_0209c390.h"
#include "proto/main/unk_020a427c.h"
#include "proto/main/unk_020af258.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov002/unk_ov002_022025cc.h"


LetterRenderer::LetterRenderer() {}

LetterRenderer::~LetterRenderer() {}

void LetterRenderer::loadLetterScreen(u32 v) {
    Gfx2d_LoadScreenFile("menu/letter/b_ltr_a_bg.bsc", gCurrentHeap, v);
}
