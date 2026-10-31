#include "types.h"
#include "sys/CmdSeq.h"
#include "proto/autoload_2/unk_020ed81c.h"

extern "C" s16 CmdSeq_Run(CmdSeq *o, s32 loop) {
    if (o->cmds == NULL || o->state == 2) return 2;
    while (o->cmds[o->cmdIndex] != NULL) {
        o->state = o->vfunc_08(o->cmds[o->cmdIndex]);
        if (o->state != 2) break;
        o->cmdIndex++;
        o->cmdStep = 0;
        if (loop == 0) break;
    }
    return o->state;
}
