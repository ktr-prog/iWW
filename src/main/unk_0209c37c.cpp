#include "types.h"


extern "C" {

u16 sDebugVarTable[0x82];

u32 DebugVar_GetStub() {
    return 0;
}

u16 *DebugVar_GetPtr(u32 a, u32 b) {
    return &sDebugVarTable[(a << 7) + b];
}

}
