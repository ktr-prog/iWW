#include "types.h"
#include "sys/ProcProfile.h"
#include "Unk_020d8c7c.h"
#include "sys/SceneBase.h"


class DummyScene4 : public SceneBase {
public:
};

extern "C" DummyScene4 *DummyScene4_Create(void) { return new DummyScene4; }

ProcProfile sDummyScene4Profile = {(void *(*)())DummyScene4_Create, 0x4, 0x3};
