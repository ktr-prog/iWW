#include "types.h"
#include "game/Unk_02034014.h"
#include "gfx/DebugColor.h"


extern "C" void FieldScene_DebugDraw()
{
}

s32 sDebugHappyRoomScore;
s32 sDebugHappyRoomBonusFlags;

extern "C" void Debug_SetHappyRoomScore(s32 v)
{
    sDebugHappyRoomScore = v;
}

extern "C" void Debug_SetHappyRoomBonusFlags(s32 v)
{
    sDebugHappyRoomBonusFlags = v;
}

Unk_02034014::Unk_02034014()
{
    clear();
    setDefaults();
}

Unk_02034014::~Unk_02034014()
{
}

DebugColor sDebugColorRed(31, 20, 20, 31);
DebugColor sDebugColorBlue(20, 20, 31, 31);
DebugColor sDebugColorYellow(31, 31, 20, 31);
DebugColor sDebugColorGreen(20, 31, 20, 31);
DebugColor sDebugColorCyan(20, 31, 31, 31);
DebugColor sDebugColorGrey(20, 24, 24, 31);
Unk_02034014 data_021c1a30;
