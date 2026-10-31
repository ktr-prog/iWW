#ifndef PROTO_PROTO_OV003_UNK_OV003_022150EC_H
#define PROTO_PROTO_OV003_UNK_OV003_022150EC_H


#include "types.h"
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#include "gfx/NNSG3dRS.h"
#include "town/CountdownDigit.h"
#include "town/CountdownSign.h"
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sCountdownDigitProfile
extern ActorProfile sCountdownDigitProfile;
#endif
#ifndef PROTO_LOCAL_sCountdownSignProfile
extern ActorProfile sCountdownSignProfile;
#endif
#ifndef PROTO_LOCAL_CountdownSign_ModelCallback
void CountdownSign_ModelCallback(NNSG3dRS *o);
#endif
#ifndef PROTO_LOCAL_CountdownSign_MaterialCallback
void CountdownSign_MaterialCallback(NNSG3dRS *o);
#endif
#ifndef PROTO_LOCAL_CountdownDigit_Create
CountdownDigit *CountdownDigit_Create();
#endif
#ifndef PROTO_LOCAL_CountdownSign_Create
CountdownSign *CountdownSign_Create();
#endif
#ifndef PROTO_LOCAL_CountdownSign_SetMaterialAlpha
void CountdownSign_SetMaterialAlpha(CountdownSign *self, s32 a, NNSG3dRS *o);
#endif
}
#endif

#endif
