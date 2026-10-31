#include "types.h"
#include "host_labels.h"
#include "player/PlayerActor.h"
#include "actor/Actor.h"
#include "gfx/VecFx32.h"
#include "talk/MsgStringBase.h"
#include "talk/MsgStringAttr.h"
#include "save/TownId.h"
#include "talk/EncodedStringBase.h"
#include "player/PlayerId.h"
#include "gfx/EffectSlot.h"
#include "gfx/EffectSplEmitter.h"
#include "talk/MsgString.h"
#include "game/GroundInfo.h"
#include "talk/EncodedString.h"
#include "talk/MsgString9B.h"
#include "talk/EncodedString8.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0208f268.h"
#include "proto/main/unk_02090268.h"
#include "proto/main/unk_02093ff0.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_0204cc1c.h"


extern "C" {
s32 MI_CpuCopy8(const void *src, void *dst, u32 n);
s32 MI_CpuFill8(void *dst, u32 v, u32 n);
}




class MsgString;


extern "C" BOOL EncodedString_SetRaw(void *, const void *, s32);




extern "C" {
#define gSaveTownId HOST_LABEL(TownId *, gSaveTownId)
#define gSavePlayers HOST_LABEL(u8 (*)[], gSavePlayers)
s32 Scene_GetCurrent();
s32 Area_PlaceItem(s32, s32, s32, s32, s32);
}

extern "C" void PlayerSession_RemovePitfallOnClimbOut(s32 *a, u8 *b, s32 *c, s32 *d, s32 *e, s32 *f)
{
    if (*b == Scene_GetCurrent()) {
        if (*c != 0x75 || *d == 0x75) return;
        if (PlayerActor_GetActor(*a) != 0 && PlayerActor_IsInAction(0x75, *a) != 0) return;
    } else {
        if (*d != 0x75 || *c == 0x75) return;
    }
    {
        s32 o1, o2;
        VecFx32 s;
        s32 fv = *f;
        s.x = *e;
        s.y = 0;
        s.z = fv;
        FieldPos_ToUnit(&o1, &o2, &s);
        Area_PlaceItem(0, o1, o2, 0xfff1, 0);
    }
}

extern "C" s32 PlayerActor_GetLocalSessionSlot()
{
    return PlayerActor_Get(4)->sessionSlot;
}

extern "C" s32 PlayerActor_GetObjectSize() { return sizeof(PlayerActor); }

extern "C" s32 PlayerActor_GetObjectAlign() { return 4; }

extern "C" void *PlayerActor_Spawn(u32 slot, VecFx32 *pos, void *rot, u32 param)
{
    return Actor::spawn(9, (((slot << 30) & 0xc0000000) | (param & 0x3fffffff)), pos, rot, NULL);
}

PlayerId::PlayerId(void *o) { TownId_Construct(); }

PlayerId::PlayerId(const PlayerId &o) { TownId_Construct(); copyFrom((PlayerId *)&o); }

PlayerId::PlayerId() { TownId_Destruct(); }

void PlayerId::setRaw(void *src) { MI_CpuCopy8(src, this, 0x16); }

void PlayerId::clear()
{
    MI_CpuFill8(playerName, 0, 8);
    playerId = 0;
    gender = 2;
    TownId_Clear(&townId);
}

void PlayerId::copyFrom(PlayerId *o)
{
    MI_CpuCopy8(o->playerName, playerName, 8);
    playerId = o->playerId;
    gender = o->gender;
    TownId_CopyFrom(&townId, &o->townId);
}

void PlayerId::copyTo(PlayerId *o)
{
    MI_CpuCopy8(playerName, o->playerName, 8);
    o->playerId = playerId;
    o->gender = gender;
    TownId_CopyTo(&townId, &o->townId);
}

BOOL PlayerId::isValid()
{
    if (TownId_IsValid(&townId) == 1 && playerId != 0) return TRUE;
    return FALSE;
}

BOOL PlayerId::equals(PlayerId *o)
{
    if (playerId == o->playerId && gender == o->gender && memcmp(playerName, o->playerName, 8) == 0) return TRUE;
    return FALSE;
}

void PlayerId::set(void *src, u16 a, s8 b, TownId *p)
{
    MI_CpuCopy8(src, playerName, 8);
    playerId = a;
    gender = b;
    if (p == NULL) p = &gSaveTownId;
    TownId_Assign(this, p);
}

extern "C" BOOL PlayerId_ListContainsId(u16 v, u16 *arr, s32 n)
{
    BOOL r = FALSE;
    if (n != 0 && arr != NULL) {
        s32 i = 0;
        for (; i < n; arr++, i++) {
            if (v == *arr) {
                r = TRUE;
                break;
            }
        }
    }
    return r;
}

extern "C" u16 PlayerId_GenerateUniqueId(u16 *arr, s32 n)
{
    u16 t;
    t = PlayerId_GenerateRandomId();
    while (t == 0 || PlayerId_ListContainsId(t, arr, n) == 1) {
        t = PlayerId_GenerateRandomId();
    }
    return t;
}

extern "C" u16 PlayerId_GenerateRandomId()
{
    return (u16)((u16)Random_GlobalBelow(0x7ffc) | 0x8000);
}

u16 PlayerId::getId() { return playerId; }

void PlayerId::setId(u16 v) { playerId = v; }

void PlayerId::setGender(u8 v) { gender = v; }

s8 PlayerId::getGender() { return gender; }

void PlayerId::setName(void *src) { MI_CpuCopy8(src, playerName, 8); }

u8 *PlayerId::getName() { return playerName; }

void PlayerId::getNameString(MsgString *x)
{
    EncodedString8 buf;
    EncodedString_SetRaw(&buf, playerName, 8);
    x->fromEncoded(&buf, 0, 0);
}

void PlayerId::setNameString(MsgString *x)
{
    EncodedString8 buf;
    buf.fromMsgString(x);
    buf.copyTo(playerName, 8);
}

extern "C" void *PlayerId_GetTownId(void *p) { return p; }

void TownId::setTown(TownId *o) { TownId_Assign(this, o); }

s32 TownId::getTownRelation()
{
    s32 r = 2;
    if (TownId_IsValid(&townId) != 0) {
        TownId *p = &gSaveTownId;
        if (townId == p->townId && memcmp(townName, p->townName, 8) == 0) {
            r = 0;
        } else {
            r = 1;
        }
    }
    return r;
}

extern "C" s32 PlayerId_FindResidentIndex(void *x)
{
    return PlayerDataArray_FindById(gSavePlayers, (u16 *)x);
}

MsgString9B::MsgString9B() {}

MsgString9B::~MsgString9B() {}

u32 MsgString9B::capacity() { return 9; }

u8 *MsgString9B::data() { return text; }

