#include "uptr.h"
#include "host_mem.h"
#include "proto/autoload_2/unk_021122b0.h"
#include "proto/autoload_2/unk_02112360.h"
#include "proto/autoload_2/unk_02112458.h"
#include "proto/autoload_2/unk_02113b6c.h"
#include "proto/autoload_2/unk_02114624.h"
#include "proto/autoload_2/unk_02114940.h"
#include "proto/autoload_2/unk_02114cd8.h"
#include "proto/autoload_2/unk_021153f8.h"
#include "proto/autoload_2/unk_02115468.h"
#include "proto/autoload_2/unk_021157c0.h"
#include "proto/autoload_2/unk_021163b0.h"
#include "proto/autoload_2/unk_02117984.h"
#include "proto/autoload_2/unk_0211c8e8.h"
#include "proto/autoload_2/unk_0211dc4c.h"
#include "proto/autoload_2/unk_0212703c.h"
typedef unsigned int u32;
typedef int s32;

extern s32 data_021fce88;
extern s32 data_021fce84;

u32 OS_GetConsoleType(void);
void OS_SetProtectionRegion1(u32 v);
void OS_SetProtectionRegion2(u32 v);


void OS_SetArenaLo(s32 id, void *lo);
void OS_SetArenaHi(s32 id, void *hi);
void *OS_GetInitArenaLo(s32 id);
void *OS_GetInitArenaHi(s32 id);
void *OS_GetArenaLo(s32 id);
void *OS_GetArenaHi(s32 id);

#define ARENA_LO(id) (gHostSysWork.arenaLo[id])
#define ARENA_HI(id) (gHostSysWork.arenaHi[id])

void OS_SetArenaHi(s32 id, void *hi) {
    ARENA_HI(id) = hi;
}

void OS_SetArenaLo(s32 id, void *lo) {
    ARENA_LO(id) = lo;
}

void *OS_AllocFromArenaLo(s32 id, u32 size, u32 align) {
    uptr arenaLo = (uptr)OS_GetArenaLo(id);
    uptr arenaHi;
    uptr ptr;
    if (arenaLo == 0) return 0;
    arenaLo = ptr = ((arenaLo) + (align) - 1) & ~(uptr)((align) - 1);
    arenaLo += size;
    arenaLo = ((arenaLo) + (align) - 1) & ~(uptr)((align) - 1);
    arenaHi = (uptr)OS_GetArenaHi(id);
    if (arenaLo > arenaHi) return 0;
    OS_SetArenaLo(id, (void *)arenaLo);
    return (void *)ptr;
}

void OS_Init(void) {
    OS_InitArena();
    PXI_Init();
    OS_InitLock();
    OS_InitArenaEx();
    OS_InitIrqTable();
    OS_SetIrqStackChecker();
    OS_InitException();
    MI_Init();
    OS_InitVAlarm();
    OSi_InitVramExclusive();
    OS_InitThread();
    OS_InitReset();
    CTRDG_Init();
    CARD_Init();
    PM_Init();
}
