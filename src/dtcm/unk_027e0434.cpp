#pragma define_section DTCM ".dtcm" abs32 RWX

#include "types.h"

#pragma section DTCM begin

u8 sMenuWipeLine;
u8 sMenuWipeEdge[24];

#pragma section DTCM end
