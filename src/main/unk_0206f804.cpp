#include "types.h"
#include "talk/EncodedString41.h"
#include "proto/main/unk_02051218.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0206f4f0.h"
#include "proto/main/unk_0206f804.h"


extern "C" {
typedef void (*CommSubHandler)(u8 *, u32);
}

static void RecvBbsPost(u8 *p, u32) { CommSub_RecvBbsPost(p); }
static void RecvItemList15(u8 *p, u32) { CommSub_RecvItemList15(p); }
static void RecvBottleLetter(u8 *p, u32) { CommSub_RecvBottleLetter(p); }
static void ClearBottleLetter(u8 *, u32) { CommSub_ClearBottleLetter(); }
static void RecvPostReply(u8 *p, u32) { CommSub_RecvPostReply(p); }
static void RecvTownTune(u8 *p, u32) { CommSub_RecvTownTune(p); }
static void RecvCountdownRequest(u8 *p, u32) { CommSub_RecvCountdownRequest(p); }
static void StartCountdown(u8 *p, u32) { CommSub_StartCountdown(p); }
static void RecvClearPendingUnit(u8 *p, u32) { CommSub_RecvClearPendingUnit(p); }

CommSubHandler sCommSubHandlers[24] = {
    RecvBbsPost, CommSub_RecvInsectRelease, CommSub_RecvReleaseOrThrow, RecvItemList15, RecvItemList15, CommSub_RecvReleaseOrThrow,
    RecvBottleLetter, ClearBottleLetter, CommSub_RecvPostLetter, RecvPostReply, RecvPostReply, RecvPostReply,
    RecvTownTune, RecvCountdownRequest, RecvCountdownRequest, RecvCountdownRequest, RecvCountdownRequest, RecvCountdownRequest,
    StartCountdown, StartCountdown, StartCountdown, StartCountdown, StartCountdown, RecvClearPendingUnit,
};

s32 EncodedString41::getLength() { return Text_GetLength(text, 0x29); }

extern "C" void CommSub_ResetPostReply() { sCommSubPostReply = 0x18; }

extern "C" void CommSub_Dispatch(u8 *p, u32 x) { sCommSubHandlers[p[0]](p, x); }
