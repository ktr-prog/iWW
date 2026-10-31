#include "types.h"

#pragma thumb off

extern "C" void OSi_ReferSymbol(void *symbol)
{
#pragma unused(symbol)
}

#pragma thumb reset
