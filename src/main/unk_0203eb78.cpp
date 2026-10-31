#include "uptr.h"
#include "host_labels.h"
#include "item/Letter.h"
#include "types.h"
#include "Unk_020d8c7c.h"
#include "talk/TalkRequestList.h"
#include "game/SceneInfo.h"
#include "game/EventScheduleRule.h"
#include "game/EventDayEntry.h"
#include "talk/TalkRequestEntry.h"
#include "gfx/WorldCurve.h"
#include "player/PlayerData.h"
#include "save/BbsBoard.h"
#include "proto/main/unk_0203eb78.h"
#include "proto/main/unk_0203ecec.h"
#include "item/LetterView.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_02095cdc.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_0209eb94.h"


extern "C" {
#define data_021e87d8 HOST_LABEL(u8 (*)[], data_021e87d8)
s32 MI_CpuFill8(void *dst, s32 v, s32 n);
s32 List_Remove(void *list, void *node);
}

static inline BOOL IsOne(u8 v) { return v == 1 ? TRUE : FALSE; }
static inline BOOL IsZero(u8 v) { return v == 0 ? TRUE : FALSE; }
TalkRequestEntry sTalkRequestPool[15];

extern "C" void *AxMail_Construct(void *p) {
    new (p) Letter();
    return p;
}

extern "C" void *AxMail_Destruct(void *p) {
    ((Letter *)(p))->Letter::~Letter();
    return p;
}

extern "C" u8 *AxMail_GetDigest(u8 *p) { return p + 0xf6; }

extern "C" BOOL AxMail_Deliver(u8 *p) {
    Letter l;
    PlayerData *h = PlayerData_GetCurrent();
    if (*(u16 *)(p + 0xf4) != PlayerData_GetLastWifiMailId(h)) {
        Letter_Copy((LetterView *)&l, (LetterView *)p);
        s32 q = h->getIndex();
        Letter_SetRecipientResident((LetterView *)&l, q);
        Letter_MarkReceived((LetterView *)&l);
        if (LetterDelivery_PutInMailbox(&l, q, 0)) {
            PlayerData_SetLastWifiMailId(h, *(u16 *)(p + 0xf4));
            return TRUE;
        }
    }
    return FALSE;
}

extern "C" void AxBbsNotice_Construct(void) {}

extern "C" void AxBbsNotice_Destruct(void) {}

extern "C" u8 *AxBbsNotice_GetDigest(u8 *p) { return p + 0xc2; }

extern "C" BOOL AxBbsNotice_Post(u8 *p) {
    u8 *g = data_021e87d8;
    u32 v = *(u16 *)(p + 0xc0);
    if (v != ((BbsBoard *)(g))->getNoticeId()) {
        ((BbsBoard *)(g))->setNoticeId(v);
        Bbs_AddPost(p);
        return TRUE;
    }
    return FALSE;
}

TalkRequestEntry::TalkRequestEntry() {
    prev = 0;
    next = 0;
    priority = 0xff;
}

extern "C" void TalkRequestEntry_Free(TalkRequestEntry *e) {
    e->phase = 0;
    e->requesterId = 0;
    e->targetId = 0;
}

extern "C" void TalkRequestList_FreeAll(TalkRequestList *l) {
    TalkRequestEntry *p = l->head;
    while (p) {
        TalkRequestEntry *next = p->next;
        List_Remove(l, p);
        TalkRequestEntry_Free(p);
        p = next;
    }
}

extern "C" void TalkRequestPool_Reset(void) {
    for (s32 i = 0; i < 15; i++) {
        TalkRequestEntry_Free(&sTalkRequestPool[i]);
    }
    MI_CpuFill8(sTalkRequestPool, 0, 15);
}

extern "C" TalkRequestEntry *TalkRequestPool_Alloc(void) {
    for (s32 i = 0; i < 15; i++) {
        TalkRequestEntry *e = &sTalkRequestPool[i];
        if (IsZero(e->phase)) {
            return e;
        }
    }
    return NULL;
}

