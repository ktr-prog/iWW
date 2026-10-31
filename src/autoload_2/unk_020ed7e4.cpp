#include "types.h"
#include "sys/CmdSeq.h"
#include "proto/autoload_2/unk_020ed7e4.h"
#include "proto/autoload_2/unk_020ed81c.h"


extern "C" {
}

extern "C" BOOL CmdSeq_Poll(CmdSeq *o) {
    if (o->state == 1) {
        o->state = CmdSeq_Run(o, 0);
    }
    if (o->state == 1) return FALSE;
    return TRUE;
}
