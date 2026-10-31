#include "types.h"
#include "snd/Player.h"
#include "proto/autoload_2/unk_020edd58.h"
#include "proto/autoload_2/unk_020ede18.h"
#include "proto/main/unk_0206d49c.h"

extern "C" {
void NNS_SndHandleInit(SndSeqHandle *h);
void NNS_FndInitList(FndList *list, u16 offset);
}

extern "C" BOOL SndSeSystem_Setup(Player *o, u32 a, u32 b, Bytes4 s) {
    if (o->active != 0) Fatal_Trap();
    if (s.b0 == 255) Fatal_Trap();
    o->groupParams = s;
    if (s.b3 == 0) {
        if (SndSeSystem_LoadGroup(o) == 0) return FALSE;
    } else {
        o->heapLevel = 255;
    }
    o->unk_10 = a;
    o->unk_14 = b;
    NNS_SndHandleInit(&o->unk_20);
    NNS_SndHandleInit(&o->unk_24);
    NNS_FndInitList(&o->list, 0);
    o->active = 1;
    return TRUE;
}
