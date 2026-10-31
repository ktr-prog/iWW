#include "types.h"
#include "Unk_020d8c7c.h"
#include "sys/ProcProfile.h"
#include "proto/ov056/unk_ov056_02258de0.h"

class DummyProcCD : public GameProc {
public:
    DummyProcCD() {}
};



extern "C" ProcProfile sDummyProcCDProfile = {(void *(*)())DummyProcCD_Create, 0xcd, 0xc9};


extern "C" DummyProcCD *DummyProcCD_Create() {
    return new DummyProcCD;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov056_02258de0) {
    HOST_OVERLAY_VAR(sDummyProcCDProfile),
    HOST_OVERLAY_VARS_END
};
