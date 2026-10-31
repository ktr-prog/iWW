#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_0210C084_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_0210C084_H


#include "types.h"
#include "nnsys/snd_arcstrm.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_02135e80
extern const s8 data_02135e80[16];
#endif
#ifndef PROTO_LOCAL_data_02135e90
extern const s16 data_02135e90[89];
#endif
#ifndef PROTO_LOCAL_MakeWaveData
void MakeWaveData(NNSSndStrmLoadCommand *command);
#endif
#ifndef PROTO_LOCAL_StrmThreadProc
void StrmThreadProc(void *arg);
#endif
#ifndef PROTO_LOCAL_NNS_SndArcPlayerSetup
BOOL NNS_SndArcPlayerSetup(void *heap);
#endif
#ifndef PROTO_LOCAL_NNS_SndArcPlayerStartSeq
u32 NNS_SndArcPlayerStartSeq(void *handle, u32 seqNo);
#endif
#ifndef PROTO_LOCAL_NNS_SndArcPlayerStartSeqArc
u32 NNS_SndArcPlayerStartSeqArc(void *handle, u32 arcNo, u32 idx);
#endif
#ifndef PROTO_LOCAL_NNS_SndArcPlayerStartSeqArcEx
u32 NNS_SndArcPlayerStartSeqArcEx(void *handle, s32 player, s32 bank, s32 prio, u32 arcNo, u32 idx);
#endif
#ifndef PROTO_LOCAL_NNS_SndArcLoadGroup
BOOL NNS_SndArcLoadGroup(u32 a, void *heap);
#endif
#ifndef PROTO_LOCAL_NNS_SndArcLoadSeqArc
BOOL NNS_SndArcLoadSeqArc(u32 id, void *heap);
#endif
#ifndef PROTO_LOCAL_NNS_SndArcLoadBank
BOOL NNS_SndArcLoadBank(u32 id, void *heap);
#endif
#ifndef PROTO_LOCAL_NNS_SndArcLoadWaveArc
BOOL NNS_SndArcLoadWaveArc(u32 id, void *heap);
#endif
#ifndef PROTO_LOCAL_NNSi_SndArcLoadGroup
u32 NNSi_SndArcLoadGroup(u32 grp, void *heap);
#endif
#ifndef PROTO_LOCAL_NNSi_SndArcLoadSeq
u32 NNSi_SndArcLoadSeq(u32 id, u32 flags, void *heap, u32 flag, void **out);
#endif
#ifndef PROTO_LOCAL_NNSi_SndArcLoadSeqArc
u32 NNSi_SndArcLoadSeqArc(u32 id, u32 flags, void *heap, u32 flag, void **out);
#endif
#ifndef PROTO_LOCAL_NNSi_SndArcLoadBank
u32 NNSi_SndArcLoadBank(u32 id, u32 flags, void *heap, u32 flag, void **out);
#endif
#ifndef PROTO_LOCAL_NNSi_SndArcLoadWaveArc
u32 NNSi_SndArcLoadWaveArc(u32 id, u32 flags, void *heap, u32 flag, void **out);
#endif
#ifndef PROTO_LOCAL_LoadSeq
void *LoadSeq(u32 file, void *heap, u32 flag);
#endif
#ifndef PROTO_LOCAL_LoadSeqArc
void *LoadSeqArc(u32 file, void *heap, u32 flag);
#endif
#ifndef PROTO_LOCAL_LoadBank
void *LoadBank(u32 file, void *heap, u32 flag);
#endif
#ifndef PROTO_LOCAL_LoadWaveArc
void *LoadWaveArc(u32 file, void *heap, u32 flag);
#endif
#ifndef PROTO_LOCAL_LoadWaveArcTable
void *LoadWaveArcTable(u32 file, void *heap, u32 flag);
#endif
#ifndef PROTO_LOCAL_DisposeCallback
void DisposeCallback(void *mem, void *arc, u32 idx);
#endif
#ifndef PROTO_LOCAL_SeqDisposeCallback
void SeqDisposeCallback(void *mem, u32 size, void *arc, u32 idx);
#endif
#ifndef PROTO_LOCAL_BankDisposeCallback
void BankDisposeCallback(void *mem, u32 size, void *arc, u32 idx);
#endif
#ifndef PROTO_LOCAL_WaveArcDisposeCallback
void WaveArcDisposeCallback(void *mem, u32 size, void *arc, u32 idx);
#endif
#ifndef PROTO_LOCAL_WaveArcTableDisposeCallback
void WaveArcTableDisposeCallback(void *mem, u32 size, void *arc, u32 idx);
#endif
#ifndef PROTO_LOCAL_SingleWaveDisposeCallback
void SingleWaveDisposeCallback(void *mem, u32 size, void *waveArc, u32 idx);
#endif
#ifndef PROTO_LOCAL_LoadSingleWave
u32 LoadSingleWave(u8 *wa, u32 idx, u32 file, void *heap);
#endif
#ifndef PROTO_LOCAL_LoadSingleWaves
u32 LoadSingleWaves(void *wa, void *bank, u32 arcNo, u32 file, void *heap);
#endif
#ifdef __cplusplus
}
#endif

#endif
