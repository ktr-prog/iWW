#include "types.h"
#include "sys/ProcProfile.h"
#include "Unk_020d8c7c.h"

extern "C" { extern u8 gTouchPrevHeld; }
u8 gTouchPrevHeld;

extern "C" { extern u8 gTouchPrevChanged; }
u8 gTouchPrevChanged;

extern "C" { extern u8 gTouchHoldFrames; }
u8 gTouchHoldFrames;

class DummyProcC8 : public GameProc {
public:
    DummyProcC8() {}
};

extern "C" DummyProcC8 *DummyProcC8_Create() {
    return new DummyProcC8();
}

ProcProfile sDummyProcC8Profile = {(void *(*)())DummyProcC8_Create, 0xc8, 0xc6};
