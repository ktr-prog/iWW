#include "types.h"
#include "gfx/VecFx32.h"
#include "actor/CharacterListNode.h"
#include "talk/TalkRequestEntry.h"
#include "game/CharacterList.h"
#include "net/CommManager.h"
#include "sys/ProcBase.h"
#include "actor/Character.h"
#include "proto/main/unk_02002b1c.h"
#include "proto/main/unk_0203e7d0.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_020a427c.h"
#include "proto/main/unk_020b0e60.h"








extern CharacterList gCharacterList;



extern "C" {
extern TalkRequestEntry *gTalkRequestCurrent;
}

extern "C" {
extern u32 sTalkTargetId;
}

extern "C" {
extern u32 sTalkRequestFlags;
}

extern "C" {
extern u32 sTalkRequestList;
}

extern "C" {
extern CommManager *volatile gCommManager;
}

extern "C" {
extern s16 data_020c905c;
}

extern "C" {
}

extern "C" {
void PrioList_Init(void *);
}

extern "C" {
void TalkRequestPool_Reset(void);
}

extern "C" {
void TalkRequestFlags_Clear(u32);
}

extern "C" {
}

extern "C" {
void TalkRequest_SetTalkTarget(u32);
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
TalkRequestEntry *TalkRequestPool_Alloc(void);
}

extern "C" {
void List_Remove(void *, void *);
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
long long Vec_MagSqXZ(VecFx32 *);
}

extern "C" {
void *PrioList_FindById(void *, u32);
}

extern "C" {
void PrioList_PushBack(void *, void *);
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
void TalkRequestQueue_Reset(void);
}

extern "C" {
}

extern "C" {
Character *Character_FindByCharId(u32 id);
}


extern "C" void CharInteractSync_Reset(void) {
    for (s32 i = 0; i < 4; i++) {
        sCharInteractLockIds[i] = 0;
    }
    sCharInteractReservedId = 0;
    sCharInteractSyncResult = 6;
}

extern "C" void CharInteractSync_SendReply(u8 a, u32 aid, ...) {
    CommManager *o = gCommManager;
    ((CommManager *)(o))->beginRecord();
    ((CommManager *)(o))->writeRecord((u8 *)(&a), 1);
    ((CommManager *)(o))->endRecord(0x17, aid);
}

extern "C" u32 CharInteractSync_IsFree(u32 idx, u32 id) {
    if (sCharInteractLockIds[idx] != 0) {
        return 0;
    }
    if (sCharInteractReservedId == id) {
        return 0;
    }
    for (s32 i = 0; i < 4; i++) {
        if (id == sCharInteractLockIds[i]) {
            return 0;
        }
    }
    return 1;
}

extern "C" void CharInteractSync_ClearLock(u32 idx) {
    sCharInteractLockIds[idx] = 0;
}

extern "C" s32 CharInteractSync_Check(u32 id) {
    CommManager *o = gCommManager;
    if (!((CommManager *)(o))->isOnline()) {
        return 2;
    }
    if (o->myAid == 0) {
        if (CharInteractSync_IsFree((u8)o->myAid, id)) {
            return 2;
        }
        return 0;
    }
    return 1;
}

extern "C" void CharInteractSync_RequestLock(u32 id) {
    CommManager *o = gCommManager;
    if (((CommManager *)(o))->isOnline()) {
        if (o->myAid == 0) {
            sCharInteractLockIds[o->myAid] = id;
        } else {
            u8 buf[5];
            sCharInteractSyncResult = 0;
            buf[0] = 0;
            buf[1] = id;
            buf[2] = id >> 8;
            buf[3] = id >> 16;
            buf[4] = id >> 24;
            CommManager *p = gCommManager;
            ((CommManager *)(p))->beginRecord();
            ((CommManager *)(p))->writeRecord((u8 *)(buf), 5);
            ((CommManager *)(p))->endRecord(0x17, 0);
        }
    }
}

extern "C" void CharInteractSync_ReleaseLock(void) {
    CommManager *o = gCommManager;
    if (((CommManager *)(o))->isOnline()) {
        if (o->myAid == 0) {
            CharInteractSync_ClearLock(0);
        } else {
            CharInteractSync_SendReply(3, 0);
        }
    }
}

extern "C" s32 CharInteractSync_CheckArea(void) {
    if (!((CommManager *)(gCommManager))->isOnline()) {
        return 2;
    }
    if (NetArea_IsLocalOwner()) {
        return 2;
    }
    return 1;
}

extern "C" void CharInteractSync_SendQuery(u32 id, u8 x) {
    CharInteractSync_SendCharMsg(id, x, 4);
}

extern "C" void CharInteractSync_SendEvent(u32 id, u8 x) {
    CharInteractSync_SendCharMsg(id, x, 5);
}

extern "C" void CharInteractSync_SendCharMsg(u32 id, u8 x, u8 mode) {
    if (((CommManager *)(gCommManager))->isOnline()) {
        u8 buf[6];
        sCharInteractSyncResult = mode;
        buf[0] = mode;
        buf[1] = id;
        buf[2] = id >> 8;
        buf[3] = id >> 16;
        buf[4] = id >> 24;
        buf[5] = x;
        CommManager *o = gCommManager;
        ((CommManager *)(o))->beginRecord();
        ((CommManager *)(o))->writeRecord((u8 *)(buf), 6);
        ((CommManager *)(o))->endRecord(0x17, 6);
    }
}

extern "C" void CharInteractSync_OnLockRequest(u8 *msg, u32 aid) {
    u32 id = (msg[4] << 24) | ((msg[3] << 16) | (msg[1] | (msg[2] << 8)));
    if (CharInteractSync_IsFree((u8)aid, id)) {
        sCharInteractLockIds[aid] = id;
        CharInteractSync_SendReply(1, aid);
    } else {
        CharInteractSync_SendReply(2, aid);
    }
}

extern "C" void CharInteractSync_OnReply(u8 *msg) {
    sCharInteractSyncResult = msg[0];
}

extern "C" void CharInteractSync_OnRelease(void *msg, u32 aid) {
    CharInteractSync_ClearLock((u8)aid);
}

extern "C" void CharInteractSync_OnCharMsg(u8 *msg, u32 aid) {
    u32 r6 = msg[5];
    Character *o = Character_FindByCharId((msg[4] << 24) | ((msg[3] << 16) | (msg[1] | (msg[2] << 8))));
    void *w = PlayerActor_GetActor(aid);
    if (!o || !w) {
        if (msg[0] == 4) {
            if (!((CommManager *)(gCommManager))->isMyAid(aid)) {
                CharInteractSync_SendReply(2, aid);
            } else {
                sCharInteractSyncResult = 2;
            }
        }
    } else if (msg[0] == 5) {
        o->onInteractionEvent(r6, (u8)aid);
    } else {
        BOOL r5 = FALSE;
        switch (r6) {
        case 0:
            r5 = o->acceptsInteraction(w);
            break;
        case 5:
            r5 = o->acceptsInteractionOutOfRange(w);
            break;
        case 1:
            r5 = o->acceptsSelfRequestedInteraction(w);
            break;
        }
        if (!((CommManager *)(gCommManager))->isMyAid(aid)) {
            if (r5) {
                o->onInteractionEvent(3, (u8)aid);
                CharInteractSync_SendReply(1, aid);
            } else {
                CharInteractSync_SendReply(2, aid);
            }
        } else {
            if (r5) {
                o->onInteractionEvent(3, 4);
                sCharInteractSyncResult = 1;
            } else {
                sCharInteractSyncResult = 2;
            }
        }
    }
}


u8 sCharInteractSyncResult = 6;
u32 sCharInteractReservedId;
u32 sCharInteractLockIds[4];
