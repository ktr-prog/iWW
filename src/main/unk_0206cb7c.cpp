#include "types.h"
#include "text/Unk_02050288.h"
#include "talk/MsgStringBase.h"
#include "talk/MsgStringAttr.h"
#include "ui/LetterLayout.h"
#include "talk/BmgReader.h"
#include "talk/EncodedStringBase.h"
#include "talk/MsgString.h"
#include "talk/TalkBmgReader.h"
#include "talk/EncodedString.h"
#include "talk/MsgString513.h"
#include "talk/MsgString33B.h"
#include "talk/MsgString129.h"
#include "talk/MsgString25B.h"
#include "ui/LetterTextLine.h"
#include "talk/EncodedString40.h"
#include "talk/EncodedString512.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020027b4.h"
#include "proto/main/unk_02051218.h"
#include "proto/main/unk_0206c768.h"
#include "proto/main/unk_0206cb7c.h"
#include "proto/main/unk_020b2c50.h"

MsgString25B::MsgString25B() { clear(); }

MsgString25B::~MsgString25B() {}

u32 MsgString25B::capacity() { return 0x19; }

u8 *MsgString25B::data() { return text; }

