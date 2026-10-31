typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
#include "sdk_linker_symbols.h"
#include "host_mem.h"

extern s32 data_021fce88;

#define ARENA_MAIN_LO HostMainRam_Ptr(SDK_MAIN_ARENA_LO)
#define ARENA_ITCM_LO ((void *)HW_ITCM_BLOCK)
#define ARENA_DTCM_LO ((void *)HW_DTCM_BLOCK)

u32 OS_GetConsoleType(void);

void *OS_GetInitArenaLo(s32 id) {
    switch (id) {
    case 0: return ARENA_MAIN_LO;
    case 2:
        return 0;
    case 3: return ARENA_ITCM_LO;
    case 4: return ARENA_DTCM_LO;
    case 5: return HW_SYSWORK(void, sharedArena);
    case 6: return gHostWramArena;
    default: return 0;
    }
}
