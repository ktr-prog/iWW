#include "types.h"
#include "host_labels.h"
#include "gfx/VecFx32.h"
#include "net/CommManager.h"
#include "save/TownExchangeRecord.h"
#include "ui/HudController.h"
#include "actor/Actor.h"
#include "item/Letter.h"
#include "item/LetterView.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_0206d988.h"
#include "proto/main/unk_0206f4f0.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_02089fbc.h"
#include "proto/main/unk_0208f0b0.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02095cdc.h"
#include "proto/main/unk_02096c10.h"
#include "proto/ov003/unk_ov003_0221ffb8.h"
#include "proto/ov003/unk_ov003_02225800.h"



extern "C" {
#define gSaveTownTune HOST_LABEL(u32 (*)[], gSaveTownTune)
extern CommManager *gCommManager;
#define gSaveVillagers HOST_LABEL(u32 (*)[], gSaveVillagers)
#define data_021eceac HOST_LABEL(u8 (*)[], data_021eceac)
#define data_021e7f8c HOST_LABEL(u8 (*)[], data_021e7f8c)
#define gSaveLostAndFound HOST_LABEL(u8 (*)[], gSaveLostAndFound)
#define gSaveRecycleBin HOST_LABEL(u8 (*)[], gSaveRecycleBin)
extern u8 gFieldSceneKind;
extern u32 data_020c7c1c;

s32 MI_CpuCopy8(const void *src, void *dst, u32 n);
void SaveVillagers_ClearTuneRequester(void *a);
void BottleThrow_SetTarget(VecFx32 *pos, s32 idx);
}

u8 sCommSubPostReply = 0x18;
u32 sCommCountdownKinds[5] = {0, 1, 2, 3, 4};


static inline BOOL Unk_0206f6fc_IsZero(u8 v) { return v == 0 ? TRUE : FALSE; }

extern "C" void CommSub_RecvBbsPost(u8 *p) {
    Heap *heap = gCurrentHeap;
    void *buf = Heap_AllocTail(heap, 0xc0);
    MI_CpuCopy8(p + 1, buf, 0xc0);
    Bbs_AddPost(buf);
    Heap_Free(heap, buf);
}

extern "C" void CommSub_RecvInsectRelease(u8 *p, u32 id) {
    if (Unk_0206f6fc_IsZero(gFieldSceneKind)) {
        u8 id8;
        s16 off;
        u8 *q;
        q = p + 1;
        id8 = id;
        off = (p[2] - 0x1e) * 0xb6;
        Actor *r = (Actor *)PlayerActor_GetActor(id8);
        if (r != NULL) {
            off = off + r->rotY;
            if (HeldInsect_GetStage(id8) == 0) {
                HeldInsect_Start(q[0], id8);
                HeldInsect_Release(id8, off);
            }
        }
    }
}

extern "C" void CommSub_RecvReleaseOrThrow(u8 *p, u32 id) {
    u8 buf[5];
    VecFx32 pos;
    if (Unk_0206f6fc_IsZero(gFieldSceneKind)) {
        u8 id8 = id;
        MI_CpuCopy8(p + 2, buf, 5);
        NetBuf_UnpackPair20(buf, (u32 *)&pos.x, (u32 *)&pos.z);
        pos.y = data_020c7c1c;
        if (p[0] == 2) {
            u32 v = p[1];
            u16 x;
            if (v < 0x38) {
                x = v + 0x12e8;
            } else {
                x = 0x12e8;
            }
            FishCatch_StartRelease(id8, x, &pos);
        } else {
            BottleThrow_SetTarget(&pos, id8);
        }
    }
}

extern "C" void CommSub_RecvItemList15(u8 *p) {
    u8 tmp[0x1e];
    MI_CpuCopy8(p + 1, tmp, 0x1e);
    switch (p[0]) {
    case 3:
        MI_CpuCopy8(tmp, gSaveLostAndFound, 0x1e);
        break;
    case 4:
        MI_CpuCopy8(tmp, gSaveRecycleBin, 0x1e);
        break;
    }
}

extern "C" void CommSub_RecvBottleLetter(u8 *p) {
    Heap *heap = gCurrentHeap;
    LetterView *buf = (LetterView *)Heap_AllocTail(heap, 0xf4);
    MI_CpuCopy8(p + 1, buf, 0xf4);
    TownExchangeRecord *g = (TownExchangeRecord *)data_021e7f8c;
    LetterView *t = (LetterView *)TownExchange_GetLetter(g);
    Letter_Copy(t, buf);
    g->resetCounter();
    g->setUnkFlag(0);
    Heap_Free(heap, buf);
}

extern "C" void CommSub_ClearBottleLetter() {
    Letter_Clear((LetterView *)BottleLetterRecord_GetLetter(data_021eceac));
}

extern "C" u8 CommSub_GetPostReply() { return sCommSubPostReply; }

extern "C" void CommSub_SetPostReply(u8 v) { sCommSubPostReply = v; }

extern "C" void CommSub_Send(u32 a, u32 b, ...) {
    CommManager *g = gCommManager;
    g->beginRecord();
    g->writeRecord((u8 *)(&a), 1);
    g->endRecord(0x16, b);
}

extern "C" void CommSub_RecvPostLetter(u8 *p, u32 code) {
    Heap *heap = gCurrentHeap;
    Letter *buf = (Letter *)Heap_AllocTail(heap, 0xf4);
    s32 r = 0xb;
    MI_CpuCopy8(p + 1, buf, 0xf4);
    if (LetterDelivery_QueueOutgoing(buf, 1)) {
        if (LetterDelivery_HasFreeOutgoingSlot()) {
            r = 9;
        } else {
            r = 0xa;
        }
    }
    Heap_Free(heap, buf);
    CommSub_Send(r, code);
}

extern "C" void CommSub_RecvPostReply(u8 *p) { sCommSubPostReply = *p; }

extern "C" void CommSub_RecvTownTune(u8 *p) {
    MI_CpuCopy8(p + 1, gMelodyEditPattern, 0x10);
    Melody_Pack(gSaveTownTune, gMelodyEditPattern);
    Melody_ApplyEditPattern();
    SaveVillagers_ClearTuneRequester(gSaveVillagers);
}

extern "C" void HudCountdown_StartWithSe(u32 x) {
    if (x == 0) {
        Snd_PlaySe(0x67);
    } else {
        Snd_PlaySe(0x66);
    }
    HudCountdown *r = (HudCountdown *)Hud_GetCountdown();
    r->start(sCommCountdownKinds[x], 0);
}

extern "C" void CommSub_RecvCountdownRequest(u8 *p) {
    s32 i = p[0] - 0xd;
    if (i == 0) {
        if (!((HudCountdown *)(Hud_GetCountdown()))->isStopped()) {
            HudCountdown_StartWithSe(i);
            CommSub_Send(0x12, 4);
        }
    } else {
        if (((HudCountdown *)(Hud_GetCountdown()))->isStopped()) {
            HudCountdown_StartWithSe(i);
            CommSub_Send((u8)(i + 0x12), 4);
        }
    }
}
