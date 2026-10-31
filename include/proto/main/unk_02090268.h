#ifndef PROTO_PROTO_MAIN_UNK_02090268_H
#define PROTO_PROTO_MAIN_UNK_02090268_H


#include "types.h"
struct EffectKindEntry;
#ifndef __cplusplus
typedef struct EffectKindEntry EffectKindEntry;
#endif
#ifdef __cplusplus
#include "gfx/EffectSlot.h"
#include "gfx/EffectSplEmitter.h"
#include "gfx/VecFx32.h"
class EffectManager;
class EffectModel;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Effect_EndDefault
void Effect_EndDefault(s32 id);
#endif
#ifndef PROTO_LOCAL_Effect_EndKind3D
void Effect_EndKind3D(s32 id);
#endif
#ifndef PROTO_LOCAL_Effect_EndKind56
void Effect_EndKind56(s32 id);
#endif
#ifndef PROTO_LOCAL_Effect_ResetAll
void Effect_ResetAll();
#endif
#ifndef PROTO_LOCAL_Effect_End
void Effect_End(s32 id);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_EffectCb_TintOnly
void EffectCb_TintOnly(EffectSplEmitter *o);
#endif
#ifndef PROTO_LOCAL_EffectCb_InitOneShot
void EffectCb_InitOneShot(EffectSplEmitter *o);
#endif
#ifndef PROTO_LOCAL_EffectCb_PlaceFacing
void EffectCb_PlaceFacing(EffectSplEmitter *o, EffectSlot *e);
#endif
#ifndef PROTO_LOCAL_EffectCb_InitOneShotFacing
void EffectCb_InitOneShotFacing(EffectSplEmitter *o);
#endif
#ifndef PROTO_LOCAL_EffectCb_PlaceFacingBack
void EffectCb_PlaceFacingBack(EffectSplEmitter *o, EffectSlot *e);
#endif
#ifndef PROTO_LOCAL_EffectCb_InitOneShotFacingBack
void EffectCb_InitOneShotFacingBack(EffectSplEmitter *o);
#endif
#ifndef PROTO_LOCAL_EffectCb_InitOneShotSetUnk54
void EffectCb_InitOneShotSetUnk54(EffectSplEmitter *o, s32 x);
#endif
#ifndef PROTO_LOCAL_EffectCb_PlaceEmitter
void EffectCb_PlaceEmitter(EffectSplEmitter *o, EffectSlot *e, const VecFx32 *a, const VecFx32 *b);
#endif
#ifndef PROTO_LOCAL_EffectCb_InitOneShotOffset
void EffectCb_InitOneShotOffset(EffectSplEmitter *o, const VecFx32 *a, const VecFx32 *b);
#endif
#ifndef PROTO_LOCAL_Effect_StartOneShot
s32 Effect_StartOneShot(s32 p0, s32 p1, VecFx32 *p2, s16 *p3, s16 *e, EffectOneShotCb const *f);
#endif
#ifndef PROTO_LOCAL_EffectCb_CountdownTracked
s32 EffectCb_CountdownTracked(EffectEmitterEntry *o);
#endif
#ifndef PROTO_LOCAL_EffectCb_InitTrackedOffset
void EffectCb_InitTrackedOffset(EffectEmitterEntry *o, const VecFx32 *a, const VecFx32 *b);
#endif
#ifndef PROTO_LOCAL_EffectCb_FollowTrackedOffset
s32 EffectCb_FollowTrackedOffset(EffectEmitterEntry *o, const VecFx32 *a, const VecFx32 *b);
#endif
#ifndef PROTO_LOCAL_EffectCb_InitTracked
void EffectCb_InitTracked(EffectEmitterEntry *o);
#endif
#ifndef PROTO_LOCAL_EffectCb_FollowTracked
s32 EffectCb_FollowTracked(EffectEmitterEntry *o);
#endif
#ifndef PROTO_LOCAL_Effect_StartTracked
s32 Effect_StartTracked(s32 p0, s32 p1, VecFx32 *p2, s16 *p3, s16 *e, EffectEmitterCbs *f);
#endif
#ifndef PROTO_LOCAL_Effect_SpawnParticleLandings
s32 Effect_SpawnParticleLandings(EffectSplEmitter *o, s32 p1, EffectOneShotCb const *p2, s32 p3, EffectOneShotCb const *s0, s32 p5, EffectOneShotCb const *s2, s32 p6, EffectOneShotCb const *s4);
#endif
#ifndef PROTO_LOCAL_EffectModel_InitDefault
void EffectModel_InitDefault(EffectModel *m);
#endif
#ifndef PROTO_LOCAL_Effect_StartModel
s32 Effect_StartModel(s32 kind, s32 a, VecFx32 *b, s16 *c, s16 *d, void (*fn)(EffectModel *));
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind00
s32 Effect_CreateKind00(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind01
s32 Effect_CreateKind01(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind02
s32 Effect_CreateKind02(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind03
s32 Effect_CreateKind03(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind06
s32 Effect_CreateKind06(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind07_InitEmitter0
void EffectKind07_InitEmitter0(EffectSplEmitter *a);
#endif
#ifndef PROTO_LOCAL_EffectKind07_InitEmitter1
void EffectKind07_InitEmitter1(EffectSplEmitter *a);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind07
s32 Effect_CreateKind07(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind08
s32 Effect_CreateKind08(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind09_InitEmitter0
void EffectKind09_InitEmitter0(EffectSplEmitter *a);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind09
s32 Effect_CreateKind09(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind0A
s32 Effect_CreateKind0A(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectModel_InitUnitScale
void EffectModel_InitUnitScale(EffectModel *m);
#endif
#ifndef PROTO_LOCAL_Effect_StartWaterColumn
s32 Effect_StartWaterColumn(s32 a, VecFx32 *b, s16 *c, s16 *d, EffectEmitterCbs *e, EffectOneShotCb const *f, void (*fn)(EffectModel *));
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind0B
s32 Effect_CreateKind0B(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind0C
s32 Effect_CreateKind0C(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind0D
s32 Effect_CreateKind0D(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind0F
s32 Effect_CreateKind0F(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind10
s32 Effect_CreateKind10(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind0E_InitEmitter0
void EffectKind0E_InitEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_EffectKind0E_UpdateEmitter0
s32 EffectKind0E_UpdateEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind0E
s32 Effect_CreateKind0E(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind11_UpdateEmitter2
s32 EffectKind11_UpdateEmitter2(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind11
s32 Effect_CreateKind11(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind12
s32 Effect_CreateKind12(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind13_InitEmitter0
void EffectKind13_InitEmitter0(EffectSplEmitter *p);
#endif
#ifndef PROTO_LOCAL_EffectKind13_InitEmitter1
void EffectKind13_InitEmitter1(EffectSplEmitter *p);
#endif
#ifndef PROTO_LOCAL_EffectKind13_UpdateEmitter0
s32 EffectKind13_UpdateEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind13
s32 Effect_CreateKind13(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind14_InitEmitter0B
void EffectKind14_InitEmitter0B(EffectSplEmitter *p);
#endif
#ifndef PROTO_LOCAL_EffectKind14_InitEmitter2
void EffectKind14_InitEmitter2(EffectSplEmitter *p);
#endif
#ifndef PROTO_LOCAL_EffectKind14_InitEmitter0A
void EffectKind14_InitEmitter0A(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind14
s32 Effect_CreateKind14(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind15_InitEmitter0
void EffectKind15_InitEmitter0(EffectSplEmitter *p);
#endif
#ifndef PROTO_LOCAL_EffectKind15_InitEmitter2
void EffectKind15_InitEmitter2(EffectSplEmitter *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind15
s32 Effect_CreateKind15(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind16_InitEmitter0B
void EffectKind16_InitEmitter0B(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_EffectKind16_InitEmitter0A
void EffectKind16_InitEmitter0A(EffectSplEmitter *p);
#endif
#ifndef PROTO_LOCAL_EffectKind16_InitModel
void EffectKind16_InitModel(EffectModel *m);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind16
s32 Effect_CreateKind16(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind17_InitEmitter0B
void EffectKind17_InitEmitter0B(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_EffectKind17_InitEmitter0A
void EffectKind17_InitEmitter0A(EffectSplEmitter *p);
#endif
#ifndef PROTO_LOCAL_EffectKind17_InitModel
void EffectKind17_InitModel(EffectModel *m);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind17
s32 Effect_CreateKind17(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind19_InitEmitter0B
void EffectKind19_InitEmitter0B(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_EffectKind19_InitEmitter0A
void EffectKind19_InitEmitter0A(EffectSplEmitter *p);
#endif
#ifndef PROTO_LOCAL_EffectKind19_InitModel
void EffectKind19_InitModel(EffectModel *m);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind19
s32 Effect_CreateKind19(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind1A_InitEmitter0
void EffectKind1A_InitEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind1A
s32 Effect_CreateKind1A(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind1B_InitEmitter0
void EffectKind1B_InitEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind1B
s32 Effect_CreateKind1B(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind1C_InitEmitter0
void EffectKind1C_InitEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind1C
s32 Effect_CreateKind1C(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind1D_InitEmitter0
void EffectKind1D_InitEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind1D
s32 Effect_CreateKind1D(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind1E_InitEmitter0
void EffectKind1E_InitEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind1E
s32 Effect_CreateKind1E(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind1F_InitEmitter0
void EffectKind1F_InitEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind1F
s32 Effect_CreateKind1F(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind21
s32 Effect_CreateKind21(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind22
s32 Effect_CreateKind22(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind23_InitEmitter0
void EffectKind23_InitEmitter0(EffectSplEmitter *a);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind23
s32 Effect_CreateKind23(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind24_InitEmitter0
void EffectKind24_InitEmitter0(EffectSplEmitter *a);
#endif
#ifndef PROTO_LOCAL_EffectKind24_InitModel
void EffectKind24_InitModel(EffectModel *m);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind24
s32 Effect_CreateKind24(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind25_UpdateEmitter0
s32 EffectKind25_UpdateEmitter0(EffectEmitterEntry *o);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind25
s32 Effect_CreateKind25(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind26_InitEmitter0
void EffectKind26_InitEmitter0(EffectEmitterEntry *a);
#endif
#ifndef PROTO_LOCAL_EffectKind26_UpdateEmitter0
s32 EffectKind26_UpdateEmitter0(EffectEmitterEntry *o);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind26
s32 Effect_CreateKind26(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind27
s32 Effect_CreateKind27(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind28
s32 Effect_CreateKind28(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectCb_AlignFirstParticle
void EffectCb_AlignFirstParticle(EffectSplEmitter *o, s32 flag);
#endif
#ifndef PROTO_LOCAL_EffectCb_PlaceRotatedOffset
void EffectCb_PlaceRotatedOffset(EffectSplEmitter *o, const VecFx32 *v, s32 ang);
#endif
#ifndef PROTO_LOCAL_EffectKind29_InitEmitter0
void EffectKind29_InitEmitter0(EffectSplEmitter *o);
#endif
#ifndef PROTO_LOCAL_Effect_StartOnSandOrSnow
s32 Effect_StartOnSandOrSnow(s32 a, VecFx32 *b, s16 *c, s16 *d, s32 e, EffectOneShotCb const *f);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind29
s32 Effect_CreateKind29(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind2A_InitEmitter0
void EffectKind2A_InitEmitter0(EffectSplEmitter *o);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind2A
s32 Effect_CreateKind2A(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind2B_InitEmitter0B
void EffectKind2B_InitEmitter0B(EffectSplEmitter *o);
#endif
#ifndef PROTO_LOCAL_EffectKind2B_InitEmitter0A
void EffectKind2B_InitEmitter0A(EffectSplEmitter *o);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind2B
s32 Effect_CreateKind2B(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind2C_InitEmitter0B
void EffectKind2C_InitEmitter0B(EffectSplEmitter *o);
#endif
#ifndef PROTO_LOCAL_EffectKind2C_InitEmitter0A
void EffectKind2C_InitEmitter0A(EffectSplEmitter *o);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind2C
s32 Effect_CreateKind2C(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind2D_InitEmitter0
void EffectKind2D_InitEmitter0(EffectSplEmitter *a);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind2D
s32 Effect_CreateKind2D(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind2E_InitEmitter0
void EffectKind2E_InitEmitter0(EffectSplEmitter *a);
#endif
#ifndef PROTO_LOCAL_EffectKind2E_InitEmitter1
void EffectKind2E_InitEmitter1(EffectSplEmitter *a);
#endif
#ifndef PROTO_LOCAL_EffectKind2E_InitEmitter2
void EffectKind2E_InitEmitter2(EffectSplEmitter *a);
#endif
#ifndef PROTO_LOCAL_EffectKind2E_Start
s32 EffectKind2E_Start(s32 a, VecFx32 *b, s16 *c, s16 *d, s32 e);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind2E
s32 Effect_CreateKind2E(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind2F
s32 Effect_CreateKind2F(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind30
s32 Effect_CreateKind30(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind31_InitEmitter0
void EffectKind31_InitEmitter0(EffectEmitterEntry *a);
#endif
#ifndef PROTO_LOCAL_EffectKind31_UpdateEmitter0
s32 EffectKind31_UpdateEmitter0(EffectEmitterEntry *a);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind31
s32 Effect_CreateKind31(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind32_InitEmitter0
void EffectKind32_InitEmitter0(EffectSplEmitter *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind32
s32 Effect_CreateKind32(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind33_InitEmitter0
void EffectKind33_InitEmitter0(EffectEmitterEntry *a);
#endif
#ifndef PROTO_LOCAL_EffectKind33_UpdateEmitter0
s32 EffectKind33_UpdateEmitter0(EffectEmitterEntry *a);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind33
s32 Effect_CreateKind33(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind34
s32 Effect_CreateKind34(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind35_InitParams
void EffectKind35_InitParams(EffectEmitterEntry *o, u8 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_EffectKind35_InitEmitter1
void EffectKind35_InitEmitter1(EffectEmitterEntry *o);
#endif
#ifndef PROTO_LOCAL_EffectKind35_InitEmitter3
void EffectKind35_InitEmitter3(EffectEmitterEntry *o);
#endif
#ifndef PROTO_LOCAL_EffectKind35_InitEmitter4
void EffectKind35_InitEmitter4(EffectEmitterEntry *o);
#endif
#ifndef PROTO_LOCAL_EffectKind35_UpdateRamp
s32 EffectKind35_UpdateRamp(EffectEmitterEntry *p, s32 a, s32 b, s32 c, s32 d0, s16 e1, s16 e2, s16 e3, s32 d4, s16 e5, s16 e6, s16 e7);
#endif
#ifndef PROTO_LOCAL_EffectKind35_UpdateEmitter1
s32 EffectKind35_UpdateEmitter1(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_EffectKind35_UpdateEmitter3
s32 EffectKind35_UpdateEmitter3(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_EffectKind35_UpdateEmitter4
s32 EffectKind35_UpdateEmitter4(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind35
s32 Effect_CreateKind35(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind36_InitEmitter2
void EffectKind36_InitEmitter2(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_EffectKind36_UpdateEmitter2
s32 EffectKind36_UpdateEmitter2(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind36
s32 Effect_CreateKind36(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectCb_AlignFirstParticle2
void EffectCb_AlignFirstParticle2(EffectSplEmitter *o, s32 k);
#endif
#ifndef PROTO_LOCAL_EffectKind37_InitEmitter0
void EffectKind37_InitEmitter0(EffectSplEmitter *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind37
s32 Effect_CreateKind37(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind38
s32 Effect_CreateKind38(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind39_InitEmitter0
void EffectKind39_InitEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_EffectKind39_UpdateEmitter0B
s32 EffectKind39_UpdateEmitter0B(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_EffectKind39_UpdateEmitter0A
s32 EffectKind39_UpdateEmitter0A(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind39
s32 Effect_CreateKind39(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind3A_InitEmitter0
void EffectKind3A_InitEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_EffectKind3A_UpdateEmitter0
s32 EffectKind3A_UpdateEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind3A
s32 Effect_CreateKind3A(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind3B_InitEmitter0
void EffectKind3B_InitEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_EffectKind3B_UpdateEmitter0
s32 EffectKind3B_UpdateEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind3B
s32 Effect_CreateKind3B(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind3C
s32 Effect_CreateKind3C(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind3D_InitEmitter0
void EffectKind3D_InitEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_EffectKind3D_UpdateEmitter0
s32 EffectKind3D_UpdateEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind3D
s32 Effect_CreateKind3D(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind3E_InitEmitter0B
void EffectKind3E_InitEmitter0B(EffectSplEmitter *o);
#endif
#ifndef PROTO_LOCAL_EffectKind3E_InitEmitter0A
void EffectKind3E_InitEmitter0A(EffectSplEmitter *o);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind3E
s32 Effect_CreateKind3E(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind3F_InitEmitter0B
void EffectKind3F_InitEmitter0B(EffectEmitterEntry *o);
#endif
#ifndef PROTO_LOCAL_EffectKind3F_InitEmitter0A
void EffectKind3F_InitEmitter0A(EffectSplEmitter *p);
#endif
#ifndef PROTO_LOCAL_EffectKind3F_InitModel
void EffectKind3F_InitModel(EffectModel *m);
#endif
#ifndef PROTO_LOCAL_EffectKind3F_UpdateEmitter0
s32 EffectKind3F_UpdateEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind3F
s32 Effect_CreateKind3F(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind40_InitEmitter0
void EffectKind40_InitEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_EffectKind40_UpdateEmitter0
s32 EffectKind40_UpdateEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind40
s32 Effect_CreateKind40(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind41_InitEmitter0
void EffectKind41_InitEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_EffectKind41_InitEmitter1
void EffectKind41_InitEmitter1(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_EffectKind41_InitEmitter2
void EffectKind41_InitEmitter2(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_EffectKind41_UpdateEmitter0
s32 EffectKind41_UpdateEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_EffectKind41_UpdateEmitter1
s32 EffectKind41_UpdateEmitter1(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_EffectKind41_UpdateEmitter2
s32 EffectKind41_UpdateEmitter2(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind41
s32 Effect_CreateKind41(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind42
s32 Effect_CreateKind42(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind43
s32 Effect_CreateKind43(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind44
s32 Effect_CreateKind44(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind45
s32 Effect_CreateKind45(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind46
s32 Effect_CreateKind46(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind47
s32 Effect_CreateKind47(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind48
s32 Effect_CreateKind48(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind49_InitEmitter0
void EffectKind49_InitEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_EffectKind49_UpdateEmitter0
s32 EffectKind49_UpdateEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind49
s32 Effect_CreateKind49(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind4A_InitEmitter0
void EffectKind4A_InitEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_EffectKind4A_UpdateEmitter0
s32 EffectKind4A_UpdateEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind4A
s32 Effect_CreateKind4A(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind4B
s32 Effect_CreateKind4B(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind4C
s32 Effect_CreateKind4C(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind4D
s32 Effect_CreateKind4D(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind4E_InitEmitter0
void EffectKind4E_InitEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_EffectKind4E_InitEmitter1
void EffectKind4E_InitEmitter1(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_EffectKind4E_UpdateEmitter0
s32 EffectKind4E_UpdateEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_EffectKind4E_UpdateEmitter1
s32 EffectKind4E_UpdateEmitter1(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind4E
s32 Effect_CreateKind4E(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind4F
s32 Effect_CreateKind4F(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind50
s32 Effect_CreateKind50(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind51
s32 Effect_CreateKind51(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind52_InitEmitter0
void EffectKind52_InitEmitter0(EffectSplEmitter *o);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind52
s32 Effect_CreateKind52(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind53
s32 Effect_CreateKind53(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind54_InitEmitter0
void EffectKind54_InitEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_EffectKind54_InitEmitter1
void EffectKind54_InitEmitter1(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_EffectKind54_UpdateEmitter0
s32 EffectKind54_UpdateEmitter0(EffectEmitterEntry *p);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind54
s32 Effect_CreateKind54(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind55
s32 Effect_CreateKind55(s32 p0, VecFx32 *p1, s16 *p2, s16 *p3, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind56
s32 Effect_CreateKind56(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind57
s32 Effect_CreateKind57(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind58
s32 Effect_CreateKind58(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind59
s32 Effect_CreateKind59(s32 p0, VecFx32 *p1, s16 *p2, s16 *p3, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind5A_InitEmitter0
void EffectKind5A_InitEmitter0(EffectSplEmitter *x);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind5A
s32 Effect_CreateKind5A(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind5B
s32 Effect_CreateKind5B(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind5C
s32 Effect_CreateKind5C(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind5D
s32 Effect_CreateKind5D(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind5E
s32 Effect_CreateKind5E(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind5F_InitEmitter0
void EffectKind5F_InitEmitter0(EffectSplEmitter *x);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind5F
s32 Effect_CreateKind5F(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_EffectKind60_InitEmitter0
void EffectKind60_InitEmitter0(EffectSplEmitter *x);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind60
s32 Effect_CreateKind60(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind61
s32 Effect_CreateKind61(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateKind62
s32 Effect_CreateKind62(s32 a, VecFx32 *b, s16 *c, s16 *d, s32);
#endif
#ifndef PROTO_LOCAL_Effect_CreateNone
s32 Effect_CreateNone(s32 a, VecFx32 *b, s16 *c, s16 *d, s32 id);
#endif
#ifndef PROTO_LOCAL_Effect_CreateOneShotRes
s32 Effect_CreateOneShotRes(s32 a, VecFx32 *b, s16 *c, s16 *d, s32 id);
#endif
#ifndef PROTO_LOCAL_Effect_CreateTrackedRes
s32 Effect_CreateTrackedRes(s32 a, VecFx32 *b, s16 *c, s16 *d, s32 id);
#endif
#ifndef PROTO_LOCAL_Effect_Create
s32 Effect_Create(u32 kind, VecFx32 *a, s16 *b, s16 *c);
#endif
#ifndef PROTO_LOCAL_Effect_CreateWithParam
s32 Effect_CreateWithParam(u32 kind, s16 v0, VecFx32 *a, s16 *b);
#endif
#ifndef PROTO_LOCAL_Effect_SetPosition
void Effect_SetPosition(s32 id, VecFx32 *pos, s16 *a, s16 *b);
#endif
#ifndef PROTO_LOCAL_Effect_PlayById
s32 Effect_PlayById(s32 a, VecFx32 *b, s16 *c, s16 *d);
#endif
#ifndef PROTO_LOCAL_Effect_PlayById2
s32 Effect_PlayById2(s32 a, VecFx32 *b, s16 *c, s16 *d);
#endif
#ifndef PROTO_LOCAL_Effect_CreateById
s32 Effect_CreateById(s32 a, VecFx32 *b, s16 *c, s16 *d);
#endif
}
#ifndef PROTO_LOCAL_data_020e14a4
extern EffectOneShotCb data_020e14a4[1];
#endif
#ifndef PROTO_LOCAL_data_020e147c
extern EffectOneShotCb data_020e147c[1];
#endif
#ifndef PROTO_LOCAL_data_020e1490
extern EffectOneShotCb data_020e1490[1];
#endif
#ifndef PROTO_LOCAL_data_020e14a0
extern EffectOneShotCb data_020e14a0[1];
#endif
#ifndef PROTO_LOCAL_data_020e148c
extern EffectOneShotCb data_020e148c[1];
#endif
#ifndef PROTO_LOCAL_data_020e1494
extern EffectOneShotCb data_020e1494[1];
#endif
#ifndef PROTO_LOCAL_data_020e1484
extern EffectOneShotCb data_020e1484[1];
#endif
#ifndef PROTO_LOCAL_data_020e14bc
extern EffectOneShotCb data_020e14bc[1];
#endif
#ifndef PROTO_LOCAL_data_020e1474
extern EffectOneShotCb data_020e1474[1];
#endif
#ifndef PROTO_LOCAL_data_020e149c
extern EffectOneShotCb data_020e149c[1];
#endif
#ifndef PROTO_LOCAL_data_020e14b4
extern EffectOneShotCb data_020e14b4[1];
#endif
#ifndef PROTO_LOCAL_data_020e14ac
extern EffectOneShotCb data_020e14ac[1];
#endif
#ifndef PROTO_LOCAL_data_020e14b0
extern EffectOneShotCb data_020e14b0[1];
#endif
#ifndef PROTO_LOCAL_data_020e14c4
extern EffectOneShotCb data_020e14c4[1];
#endif
#ifndef PROTO_LOCAL_data_020e14c8
extern EffectOneShotCb data_020e14c8[1];
#endif
#ifndef PROTO_LOCAL_data_020e14a8
extern EffectOneShotCb data_020e14a8[1];
#endif
#ifndef PROTO_LOCAL_data_020e1478
extern EffectOneShotCb data_020e1478[1];
#endif
#ifndef PROTO_LOCAL_data_020e14c0
extern EffectOneShotCb data_020e14c0[1];
#endif
#ifndef PROTO_LOCAL_data_020e14b8
extern EffectOneShotCb data_020e14b8[1];
#endif
#ifndef PROTO_LOCAL_data_020e1480
extern EffectOneShotCb data_020e1480[1];
#endif
#ifndef PROTO_LOCAL_data_020e1498
extern EffectOneShotCb data_020e1498[1];
#endif
#ifndef PROTO_LOCAL_data_020e1488
extern EffectOneShotCb data_020e1488[1];
#endif
#ifndef PROTO_LOCAL_data_020e15b4
extern EffectEmitterCbs data_020e15b4[1];
#endif
#ifndef PROTO_LOCAL_data_020e14f4
extern EffectEmitterCbs data_020e14f4[1];
#endif
#ifndef PROTO_LOCAL_data_020e14fc
extern EffectEmitterCbs data_020e14fc[1];
#endif
#ifndef PROTO_LOCAL_data_020e150c
extern EffectOneShotCb data_020e150c[2];
#endif
#ifndef PROTO_LOCAL_data_020e15f4
extern EffectEmitterCbs data_020e15f4[1];
#endif
#ifndef PROTO_LOCAL_data_020e1564
extern EffectOneShotCb data_020e1564[2];
#endif
#ifndef PROTO_LOCAL_data_020e152c
extern EffectEmitterCbs data_020e152c[1];
#endif
#ifndef PROTO_LOCAL_data_020e1544
extern EffectEmitterCbs data_020e1544[1];
#endif
#ifndef PROTO_LOCAL_data_020e1574
extern EffectEmitterCbs data_020e1574[1];
#endif
#ifndef PROTO_LOCAL_data_020e151c
extern EffectEmitterCbs data_020e151c[1];
#endif
#ifndef PROTO_LOCAL_data_020e157c
extern EffectEmitterCbs data_020e157c[1];
#endif
#ifndef PROTO_LOCAL_data_020e156c
extern EffectEmitterCbs data_020e156c[1];
#endif
#ifndef PROTO_LOCAL_data_020e1514
extern EffectEmitterCbs data_020e1514[1];
#endif
#ifndef PROTO_LOCAL_data_020e1524
extern EffectEmitterCbs data_020e1524[1];
#endif
#ifndef PROTO_LOCAL_data_020e154c
extern EffectEmitterCbs data_020e154c[1];
#endif
#ifndef PROTO_LOCAL_data_020e155c
extern EffectEmitterCbs data_020e155c[1];
#endif
#ifndef PROTO_LOCAL_data_020e14ec
extern EffectEmitterCbs data_020e14ec[1];
#endif
#ifndef PROTO_LOCAL_data_020e1554
extern EffectEmitterCbs data_020e1554[1];
#endif
#ifndef PROTO_LOCAL_data_020e1534
extern EffectEmitterCbs data_020e1534[1];
#endif
#ifndef PROTO_LOCAL_data_020e153c
extern EffectEmitterCbs data_020e153c[1];
#endif
#ifndef PROTO_LOCAL_data_020e14e4
extern EffectEmitterCbs data_020e14e4[1];
#endif
#ifndef PROTO_LOCAL_data_020e1584
extern EffectEmitterCbs data_020e1584[1];
#endif
#ifndef PROTO_LOCAL_data_020e158c
extern EffectEmitterCbs data_020e158c[1];
#endif
#ifndef PROTO_LOCAL_data_020e1594
extern EffectEmitterCbs data_020e1594[1];
#endif
#ifndef PROTO_LOCAL_data_020e14dc
extern EffectEmitterCbs data_020e14dc[1];
#endif
#ifndef PROTO_LOCAL_data_020e159c
extern EffectEmitterCbs data_020e159c[1];
#endif
#ifndef PROTO_LOCAL_data_020e15a4
extern EffectOneShotCb data_020e15a4[2];
#endif
#ifndef PROTO_LOCAL_data_020e15ac
extern EffectEmitterCbs data_020e15ac[1];
#endif
#ifndef PROTO_LOCAL_data_020e14d4
extern EffectEmitterCbs data_020e14d4[1];
#endif
#ifndef PROTO_LOCAL_data_020e15bc
extern EffectEmitterCbs data_020e15bc[1];
#endif
#ifndef PROTO_LOCAL_data_020e15c4
extern EffectOneShotCb data_020e15c4[2];
#endif
#ifndef PROTO_LOCAL_data_020e15cc
extern EffectEmitterCbs data_020e15cc[1];
#endif
#ifndef PROTO_LOCAL_data_020e15d4
extern EffectEmitterCbs data_020e15d4[1];
#endif
#ifndef PROTO_LOCAL_data_020e15dc
extern EffectEmitterCbs data_020e15dc[1];
#endif
#ifndef PROTO_LOCAL_data_020e15e4
extern EffectEmitterCbs data_020e15e4[1];
#endif
#ifndef PROTO_LOCAL_data_020e15ec
extern EffectEmitterCbs data_020e15ec[1];
#endif
#ifndef PROTO_LOCAL_data_020e1504
extern EffectEmitterCbs data_020e1504[1];
#endif
#ifndef PROTO_LOCAL_data_020e14cc
extern EffectEmitterCbs data_020e14cc[1];
#endif
#ifndef PROTO_LOCAL_data_020e15fc
extern EffectOneShotCb data_020e15fc[3];
#endif
#ifndef PROTO_LOCAL_data_020e1608
extern EffectOneShotCb data_020e1608[3];
#endif
#ifndef PROTO_LOCAL_data_020e1614
extern EffectOneShotCb data_020e1614[3];
#endif
#ifndef PROTO_LOCAL_data_020e1620
extern EffectOneShotCb data_020e1620[3];
#endif
#ifndef PROTO_LOCAL_data_020e162c
extern EffectEmitterCbs data_020e162c[2];
#endif
#ifndef PROTO_LOCAL_data_020e163c
extern EffectEmitterCbs data_020e163c[2];
#endif
#ifndef PROTO_LOCAL_data_020e164c
extern EffectEmitterCbs data_020e164c[2];
#endif
#ifndef PROTO_LOCAL_data_020e165c
extern EffectOneShotCb data_020e165c[4];
#endif
#ifndef PROTO_LOCAL_data_020e166c
extern EffectEmitterCbs data_020e166c[2];
#endif
#ifndef PROTO_LOCAL_data_020e167c
extern EffectEmitterCbs data_020e167c[2];
#endif
#ifndef PROTO_LOCAL_data_020e168c
extern EffectEmitterCbs data_020e168c[3];
#endif
#ifndef PROTO_LOCAL_data_020e16a4
extern EffectEmitterCbs data_020e16a4[3];
#endif
#ifndef PROTO_LOCAL_data_020e16bc
extern EffectEmitterCbs data_020e16bc[3];
#endif
#ifndef PROTO_LOCAL_data_020e16d4
extern EffectOneShotCb data_020e16d4[8];
#endif
#ifndef PROTO_LOCAL_sEffectDefaultOneShotCbs
extern EffectOneShotCb sEffectDefaultOneShotCbs[8];
#endif
#ifndef PROTO_LOCAL_data_020e1714
extern EffectEmitterCbs data_020e1714[4];
#endif
#ifndef PROTO_LOCAL_data_020e1734
extern EffectEmitterCbs data_020e1734[5];
#endif
#ifndef PROTO_LOCAL_data_020e175c
extern EffectEmitterCbs data_020e175c[5];
#endif
#ifndef PROTO_LOCAL_data_020e1784
extern EffectEmitterCbs data_020e1784[7];
#endif
#ifndef PROTO_LOCAL_sEffectDefaultTrackedCbs
extern EffectEmitterCbs sEffectDefaultTrackedCbs[8];
#endif
#ifndef PROTO_LOCAL_data_020e17fc
extern EffectEmitterCbs data_020e17fc[8];
#endif
#ifndef PROTO_LOCAL_data_020e18a8
extern VecFx32 data_020e18a8[9];
#endif
#ifndef PROTO_LOCAL_data_020e183c
extern VecFx32 data_020e183c[9];
#endif
#ifndef PROTO_LOCAL_sEffectKindTable
extern EffectKindEntry sEffectKindTable[0x66];
#endif
#ifndef PROTO_LOCAL_gEffectManager
extern EffectManager gEffectManager;
#endif
#endif

#endif
