#include "types.h"

extern "C" void sys_exit(void);

extern "C" void _ExitProcess(void) {
    sys_exit();
}

extern "C" u32 func_02133ad8(void) {
    return 0x40000000;
}

extern "C" u32 func_02133ad0(void) {
    return 0;
}

