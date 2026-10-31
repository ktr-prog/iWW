typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "types64.h"
#include "nitro/io_access.h"
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;
typedef int BOOL;
#define TRUE 1
#define FALSE 0
#define NULL 0

typedef s32 fx32;
typedef s16 fx16;
typedef s64 fx64;
typedef s64 fx64c;
typedef u16 REGType16;
typedef u32 REGType32;
typedef vu16 REGType16v;

#define REG_SQRTCNT_ADDR       0x040002b0
#define REG_SQRT_RESULT_ADDR   0x040002b4
#define reg_CP_SQRTCNT         (*(REGType16v *)REG_SQRTCNT_ADDR)
#define REG_CP_SQRTCNT_BUSY_MASK 0x8000

static inline s32 CP_IsSqrtBusy(void) {
    return (IO_R(&reg_CP_SQRTCNT) & REG_CP_SQRTCNT_BUSY_MASK);
}

static inline void CP_WaitSqrt(void) {
    while (CP_IsSqrtBusy()) {
    }
}

static inline u32 CP_GetSqrtResultImm32(void) {
    return (u32)(IO_R(((REGType32 *)REG_SQRT_RESULT_ADDR)));
}

static inline u32 CP_GetSqrtResult32(void) {
    CP_WaitSqrt();
    return CP_GetSqrtResultImm32();
}

void func_01ffc3d8(fx32 x);
void FX_InvAsync(fx32 x);
fx64c FX_GetDivResultFx64c(void);

fx32 FX_InvSqrt(fx32 x) {
    if (x > 0) {
        fx64c inv;
        fx64c sqrt;
        FX_InvAsync(x);
        func_01ffc3d8(x);
        inv = FX_GetDivResultFx64c();
        sqrt = CP_GetSqrtResult32();
        return (fx32)((inv * sqrt + (1LL << 41)) >> 42);
    }
    return 0;
}
