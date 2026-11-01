#include "types.h"
#include "host_mem.h"
#include "nitro/io_access.h"
#include "proto/autoload_2/unk_02113088.h"
#include "proto/dtcm/unk_027e0434.h"
#include "proto/itcm/unk_01ffcc60.h"
#include "proto/main/unk_02060b7c.h"

extern "C" {
extern s32 sVBlankCount;
extern u16 gMainWaitingFrame;
extern OSThreadQueue gFrameWaitQueue;
extern OSThreadQueue gVBlankQueue;

void VramQueueTex_Run(void);
void HBlank_RunVBlank(void);
}

extern "C" void Sky_HBlankNone(void) {
}

extern "C" void MenuScreen_WipeHBlank(void) {
    u32 i = sMenuWipeLine;
    u32 j = (i >= 24) ? 47 - i : i;
    u32 w = sMenuWipeEdge[j];
    vu16 *reg = (vu16 *)0x04000000;
    u32 v = ((w << 8) & 0xff00) | 0xff;
    if (IO_R(&reg[2]) & 2) {
        IO_W(&reg[0x21], v);
    }
    i++;
    if (i >= 48) {
        i -= 48;
    }
    sMenuWipeLine = (u8)i;
}

#ifdef HOST
extern "C" int host_input_wants_turn(void);
#define HOST_INPUT_WANTS_TURN() host_input_wants_turn()
extern "C" BOOL HostTick_Native(void);
#define VBLANKS_PER_TICK (HostTick_Native() ? 1 : gVBlanksPerFrame)
#else
#define VBLANKS_PER_TICK gVBlanksPerFrame
#define HOST_INPUT_WANTS_TURN() 0
#endif
extern "C" void Main_VBlankCallback(void) {
    sVBlankCount++;
    if (sVBlankCount >= VBLANKS_PER_TICK || (gMainWaitingFrame != 0 && HOST_INPUT_WANTS_TURN())) {
        if (gMainWaitingFrame != 0) {
            OS_WakeupThread(&gFrameWaitQueue);
            sVBlankCount = 0;
            VramQueueTex_Run();
        }
    }
    HBlank_RunVBlank();
    OS_WakeupThread(&gVBlankQueue);
    *HW_INTR_CHECK_BUF |= 1;
}

