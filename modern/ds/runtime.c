#include "types.h"

int atexit(void (*func)(void)) {
    (void)func;
    return 0;
}

