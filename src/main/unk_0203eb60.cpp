#include "types.h"
#include "proto/main/unk_0203e7d0.h"
#include "proto/main/unk_0203eb60.h"


typedef void (*CharInteractSyncRecvFn)(u8 *msg, u32 aid);

extern "C" CharInteractSyncRecvFn sCharInteractSyncRecvFns[6] = {
    CharInteractSync_OnLockRequest,
    (CharInteractSyncRecvFn)CharInteractSync_OnReply,
    (CharInteractSyncRecvFn)CharInteractSync_OnReply,
    (CharInteractSyncRecvFn)CharInteractSync_OnRelease,
    CharInteractSync_OnCharMsg,
    CharInteractSync_OnCharMsg,
};

extern "C" void CharInteractSync_Dispatch(u8 *p, s32 x) {
    sCharInteractSyncRecvFns[*p](p, x);
}
