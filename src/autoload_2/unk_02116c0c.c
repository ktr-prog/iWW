#include "types.h"
#include "sys/OSThread.h"
#include "proto/autoload_2/unk_02114410.h"
#include "proto/autoload_2/unk_02116c0c.h"
#include "proto/autoload_2/unk_02116d24.h"
#include "proto/autoload_2/unk_02117518.h"

extern u32 data_021fcf6c;
extern OSMutex data_021fcf70;

extern void PushCommand_impl(u32 cmd, uptr a, uptr b, uptr c, uptr d);
extern void SNDi_SetPlayerParam(u32 player, u32 offset, u32 data, u32 size);

void SND_Init(void) {
    if (data_021fcf6c != 0) {
        return;
    }
    data_021fcf6c = 1;
    OS_InitMutex(&data_021fcf70);
    SND_CommandInit();
    SND_AlarmInit();
}

void SNDi_LockMutex(void) {
    OS_LockMutex(&data_021fcf70);
}

void SNDi_UnlockMutex(void) {
    OS_UnlockMutex(&data_021fcf70);
}

void SND_StopSeq(u32 a) {
    PushCommand_impl(1, a, 0, 0, 0);
}

void SND_PrepareSeq(u32 a, uptr b, u32 c, uptr d) {
    PushCommand_impl(2, a, b, c, d);
}

void SND_StartPreparedSeq(u32 a) {
    PushCommand_impl(3, a, 0, 0, 0);
}

void SND_SetPlayerTempoRatio(u32 a, u32 b) {
    SNDi_SetPlayerParam(a, 26, b, 2);
}

u32 data_021fcf6c;
OSMutex data_021fcf70;
