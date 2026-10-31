#ifndef PROTO_PROTO_MAIN_UNK_020B7D10_H
#define PROTO_PROTO_MAIN_UNK_020B7D10_H


#include "types.h"
#include "sys/ProcProfile.h"
#ifdef __cplusplus
class DummyProcC8;
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_DummyProcC8_Create
DummyProcC8 *DummyProcC8_Create();
#endif
}
#ifndef PROTO_LOCAL_gTouchPrevHeld
extern u8 gTouchPrevHeld;
#endif
#ifndef PROTO_LOCAL_gTouchPrevChanged
extern u8 gTouchPrevChanged;
#endif
#ifndef PROTO_LOCAL_gTouchHoldFrames
extern u8 gTouchHoldFrames;
#endif
#ifndef PROTO_LOCAL_sDummyProcC8Profile
extern ProcProfile sDummyProcC8Profile;
#endif
#endif

#endif
