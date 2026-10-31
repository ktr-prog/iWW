#include "types.h"


extern "C" void Fatal_SaveRegisters(void);

extern "C" void Fatal_Trap(void) {
    Fatal_SaveRegisters();
}
