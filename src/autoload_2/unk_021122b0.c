typedef unsigned char u8;
typedef unsigned int u32;
#include "uptr.h"
#include "host_mem.h"
typedef signed int s32;
#include "sdk_linker_symbols.h"

extern u32 data_021fcc0c;

#define HW_DTCM ((uptr)HW_DTCM_BLOCK)
#define OSi_IRQ_STACK_BOTTOM (HW_DTCM + 0x3f80)
#define OSi_IRQ_STACK_TOP (OSi_IRQ_STACK_BOTTOM - SDK_IRQ_STACKSIZE)

void OS_SetIrqStackChecker(void) {
    *(u32 *)(HW_DTCM + 0x3f7c) = 0xfddb597d;
    *(u32 *)(OSi_IRQ_STACK_TOP) = 0x7bf9dd5b;
}

s32 OS_GetIrqStackStatus(void) {
    if (*(u32 *)(OSi_IRQ_STACK_TOP) != 0x7bf9dd5b) {
        return 1;
    }
    if (data_021fcc0c != 0 && *(u32 *)(OSi_IRQ_STACK_TOP + data_021fcc0c) != 0x597dfbd9) {
        return 2;
    }
    if (*(u32 *)(HW_DTCM + 0x3f7c) != 0xfddb597d) {
        return 3;
    }
    return 0;
}

u32 data_021fcc0c;
