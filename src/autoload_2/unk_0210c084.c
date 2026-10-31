#include "ds_div.h"
#include "uptr.h"
#include "types.h"
#include "nitro/fs.h"
#include "sys/OSThread.h"
#include "nnsys/snd_arcstrm.h"
#include "proto/autoload_2/unk_0210c084.h"
#include "proto/autoload_2/unk_0210da28.h"
#include "proto/autoload_2/unk_02113088.h"
#include "proto/autoload_2/unk_02114410.h"

typedef struct Pair { u32 a; u32 b; } Pair;
typedef struct InstOut { u8 type; u8 pad; u16 h1; u16 h2; u16 h3; u16 h4; u16 h5; } InstOut;
typedef struct FileRec { u32 fileId : 24; u32 loadFlag : 8; u16 wa[4]; } FileRec;
typedef struct SeqRec { u32 fileId; u16 bank; u8 vol; u8 chPrio; u8 prio; u8 player; } SeqRec;
typedef struct PlayerRec { u8 count; u8 pad; u16 bankNo; u32 heapSize; } PlayerRec;
typedef struct GrpEnt { u8 type; u8 flags; u16 pad; u32 id; } GrpEnt;
typedef struct GrpRec { u32 count; GrpEnt ent[1]; } GrpRec;
typedef struct BankRec { u32 fileId; u16 wa[4]; } BankRec;
typedef struct SeqArcRec { u32 fileId; } SeqArcRec;

typedef void (*SndHeapDisposeCallback)(void *mem, u32 size, void *data1, u32 data2);

extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32);
extern void DC_StoreRange(const void *p, u32 n);
extern void DC_FlushRange(const void *p, u32 n);
extern void MI_CpuFill8(void *dst, u32 v, u32 n);
extern void MI_CpuCopy8(const void *src, void *dst, u32 n);
extern BOOL FS_SeekFile(FSFile *file, s32 pos, u32 origin);
extern s32 FS_ReadFile(FSFile *file, void *dst, s32 len);
extern void SND_InvalidateWaveData(uptr start, uptr end);
extern void SND_InvalidateBankData(uptr start, uptr end);
extern void SND_InvalidateSeqData(uptr start, uptr end);
extern void SND_GetFirstInstDataPos(Pair *pos);
extern u32 SND_GetNextInstData(void *bank, InstOut *out, u32 *pos);
extern void *SND_GetWaveDataAddress(u8 *waveArc, s32 idx);
extern void SND_SetWaveDataAddress(u8 *waveArc, s32 idx, const void *addr);
extern u32 SND_GetWaveDataCount(void *waveArc);
extern void SND_DestroyWaveArc(void *waveArc);
extern void SND_DestroyBank(void *bank);
extern void SND_AssignWaveArc(void *bank, s32 idx, void *waveArc);
extern void *NNS_SndArcGetFileAddress(u32 idx);
extern void NNS_SndArcSetFileAddress(u32 idx, void *addr);
extern s32 NNS_SndArcReadFile(u32 idx, void *buf, u32 len, u32 offset);
extern u32 NNS_SndArcGetFileSize(u32 idx);
extern void *NNS_SndArcGetGroupInfo(s32 idx);
extern void *NNS_SndArcGetPlayerInfo(s32 idx);
extern void *NNS_SndArcGetWaveArcInfo(s32 idx);
extern void *NNS_SndArcGetBankInfo(s32 idx);
extern void *NNS_SndArcGetSeqArcInfo(s32 idx);
extern void *NNS_SndArcGetSeqInfo(s32 idx);
extern void *NNS_SndArcGetCurrent(void);
extern void *NNS_SndArcSetCurrent(void *arc);
extern void *NNS_SndHeapAlloc(void *heap, u32 size, SndHeapDisposeCallback cb, void *data1, u32 data2);
extern void *NNSi_SndSeqArcGetSeqInfo(void *seqArc, s32 idx);
extern void *NNSi_SndPlayerAllocSeqPlayer(void *handle, s32 playerNo, s32 prio);
extern void *NNSi_SndPlayerAllocHeap(s32 playerNo, void *seq);
extern void NNSi_SndPlayerFreeSeqPlayer(void *seq);
extern void NNSi_SndPlayerStartSeq(void *seq, const void *seqBase, u32 seqOffset, const void *bank);
extern void NNS_SndPlayerSetInitialVolume(void *handle, u8 vol);
extern void NNS_SndPlayerSetChannelPriority(void *handle, u32 prio);
extern void NNS_SndPlayerSetSeqArcNo(void *handle, u16 arcNo, u16 idx);
extern void NNS_SndPlayerSetSeqNo(void *handle, u16 seqNo);
extern BOOL NNS_SndPlayerCreateHeap(s32 playerNo, void *heap, u32 size);
extern void NNS_SndPlayerSetAllocatableChannel(s32 playerNo, u32 mask);
extern void NNS_SndPlayerSetPlayableSeqCount(s32 playerNo, u32 count);

extern u8 *data_021fbdb0;
extern OSMutex data_021fbdc0;
extern u8 data_021fbd6c[0x3c];

static inline void *GetFileAddress(u32 file) { return NNS_SndArcGetFileAddress(file); }
static inline void SetFileAddress(u32 file, const void *p) { NNS_SndArcSetFileAddress(file, (void *)p); }
static inline uptr SndAddr(const void *p) { return NNSi_SndArm7Addr(p); }

#define cAdpcmIndexTable data_02135e80
#define cAdpcmStepSizeTable data_02135e90
#define sDecodeBuffer data_021fbdb0
#define sDecodeBufferMutex data_021fbdc0
static inline void MI_CpuClear8(void *dest, u32 size) { MI_CpuFill8(dest, 0, size); }

u32 StartSeq(void *handle, s32 player, s32 bank, s32 prio, SeqRec *rec, u32 seqNo);
u32 StartSeqArc(void *handle, s32 player, s32 bank, s32 prio, SeqRec *rec, u8 *data, u32 arcNo, u32 idx);

const s8 data_02135e80[16] = {
    -1, -1, -1, -1, 2, 4, 6, 8, -1, -1, -1, -1, 2, 4, 6, 8,
};

const s16 data_02135e90[89] = {
    7,     8,     9,     10,    11,    12,    13,    14,    16,    17,    19,    21,    23,    25,    28,
    31,    34,    37,    41,    45,    50,    55,    60,    66,    73,    80,    88,    97,    107,   118,
    130,   143,   157,   173,   190,   209,   230,   253,   279,   307,   337,   371,   408,   449,   494,
    544,   598,   658,   724,   796,   876,   963,   1060,  1166,  1282,  1411,  1552,  1707,  1878,  2066,
    2272,  2499,  2749,  3024,  3327,  3660,  4026,  4428,  4871,  5358,  5894,  6484,  7132,  7845,  8630,
    9493,  10442, 11487, 12635, 13899, 15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767,
};

static inline s16 DecodeAdpcm(int code, NNSSndStrmAdpcmState *state)
{
    int step;
    int sample;
    int index;
    int d;

    sample = state->prevSample;
    index  = state->prevIndex;

    step = cAdpcmStepSizeTable[index];

    d = step >> 3;
    if (code & 4)
        d += step;
    if (code & 2)
        d += step >> 1;
    if (code & 1)
        d += step >> 2;

    if (code & 8)
    {
        sample -= d;
        if (sample < -32768)
            sample = -32768;
    }
    else
    {
        sample += d;
        if (sample > 32767)
            sample = 32767;
    }

    index += cAdpcmIndexTable[code];

    if (index < 0)
        index = 0;
    else if (index > 89 - 1)
        index = 89 - 1;

    state->prevSample = (s16)sample;
    state->prevIndex  = (u8)index;

    return (s16)sample;
}

void MakeWaveData(NNSSndStrmLoadCommand *command)
{
    NNSSndStrmPlayer *player = command->player;
    BOOL loopFlag;
    u32 destOffset;
    u32 restSize;
    u32 blockNo;
    u32 blockSize;
    u32 blockSamples;
    u32 blockOffsetSample;
    u32 blockOffset;
    u32 offset;
    u32 samples;
    u32 size;
    u32 readSize;
    int ch;

    if (player->finishFlag && player->finishCounter > 0)
    {
        player->finishCounter--;
    }

    destOffset = 0;

    restSize = command->bufLen;
    while (restSize > 0)
    {
        if (player->finishFlag)
        {
            for (ch = 0; ch < command->numChannels; ch++)
            {
                MI_CpuClear8((u8 *)NNSi_SndStrmBufPtr(command->buffer[ch]) + destOffset, restSize);
            }
            break;
        }

        blockNo = DS_UDIV(player->curSample, player->info.blockSamples);

        if (blockNo < player->info.numBlocks - 1)
        {
            blockSize    = player->info.blockSize;
            blockSamples = player->info.blockSamples;
        }
        else
        {
            blockSize    = player->info.lastBlockSize;
            blockSamples = player->info.lastBlockSamples;
        }

        blockOffsetSample = player->curSample;
        blockOffsetSample -= blockNo * player->info.blockSamples;

        samples = restSize;
        if (player->info.format != STRM_FORMAT_PCM8)
        {
            samples >>= 1;
        }

        if (player->dirtyFlag)
        {
            if (blockOffsetSample == 0)
            {
                player->dirtyFlag = FALSE;
            }
            else
            {
                samples           = blockOffsetSample;
                blockOffsetSample = 0;
            }
        }

        loopFlag = FALSE;
        if (blockOffsetSample + samples >= blockSamples)
        {
            samples = blockSamples - blockOffsetSample;

            if (blockNo >= player->info.numBlocks - 1)
            {
                if (player->info.loopFlag)
                {
                    loopFlag = TRUE;
                }
                else
                {
                    player->finishFlag = TRUE;
                }
            }
        }

        blockOffset = blockOffsetSample;
        size        = samples;
        switch (player->info.format)
        {
            case STRM_FORMAT_PCM8:
                readSize = size;
                break;

            case STRM_FORMAT_PCM16:
                blockOffset <<= 1;
                size <<= 1;
                readSize = size;
                break;

            case STRM_FORMAT_ADPCM: {
                u32 endSample = blockOffsetSample + samples;
                blockOffset >>= 1;
                endSample++;
                endSample >>= 1;
                readSize = endSample - blockOffset;
                if (blockOffsetSample == 0)
                {
                    readSize += sizeof(NNSSndStrmAdpcmState);
                }
                else
                {
                    blockOffset += sizeof(NNSSndStrmAdpcmState);
                }
                size <<= 1;

                break;
            }
        }

        offset = blockOffset;
        offset += blockNo * player->info.blockSize * player->info.numChannels;
        offset += player->info.dataOffset;
        offset += player->fileOffset;

        for (ch = 0; ch < command->numChannels; ch++)
        {
            void *dest;
            void *read_dest;

            dest = read_dest = (u8 *)NNSi_SndStrmBufPtr(command->buffer[ch]) + destOffset;

            if (ch < player->info.numChannels)
            {
                s32 resultSize;

                if (player->info.format == STRM_FORMAT_ADPCM)
                {
                    OS_LockMutex(&sDecodeBufferMutex);
                    read_dest = sDecodeBuffer;
                }

                FS_SeekFile(&player->file, (s32)(offset + ch * blockSize), 0);
                resultSize = FS_ReadFile(&player->file, read_dest, (s32)readSize);

                if (resultSize != readSize)
                {
                    size               = 0;
                    samples            = 0;
                    loopFlag           = FALSE;
                    player->finishFlag = TRUE;
                    if (player->info.format == STRM_FORMAT_ADPCM)
                    {
                        OS_UnlockMutex(&sDecodeBufferMutex);
                    }
                    break;
                }

                if (player->info.format == STRM_FORMAT_ADPCM)
                {
                    NNSSndStrmAdpcmState *state = &player->adpcmState[ch];
                    u8 *srcp          = sDecodeBuffer;
                    s16 *destp        = dest;
                    u32 i;
                    u32 end;

                    if (blockOffsetSample == 0)
                    {
                        *state = *(NNSSndStrmAdpcmState *)srcp;
                        srcp += sizeof(NNSSndStrmAdpcmState);
                    }

                    end = blockOffsetSample + samples;

                    i = blockOffsetSample;
                    if (i & 0x01)
                    {
                        *destp++ = DecodeAdpcm((*srcp >> 4) & 0x0f, state);
                        i++;
                        srcp++;
                    }
                    while (i < (end & ~0x01))
                    {
                        *destp++ = DecodeAdpcm(*srcp & 0x0f, state);
                        i++;
                        *destp++ = DecodeAdpcm((*srcp >> 4) & 0x0f, state);
                        i++;
                        srcp++;
                    }
                    if (i < end)
                    {
                        *destp++ = DecodeAdpcm(*srcp & 0x0f, state);
                        i++;
                    }
                    OS_UnlockMutex(&sDecodeBufferMutex);
                }
            }
            else
            {
                if (player->monoFlag)
                {
                    MI_CpuClear8(dest, size);
                }
                else
                {
                    MI_CpuCopy8((u8 *)NNSi_SndStrmBufPtr(command->buffer[0]) + destOffset, dest, size);
                }
            }
        }

        if (player->dirtyFlag)
        {
            player->dirtyFlag = FALSE;
            continue;
        }

        if (loopFlag)
        {
            player->curSample = player->info.loopStart;
        }
        else
        {
            player->curSample += samples;
        }

        destOffset += size;

        restSize -= size;

        if (player->finishFlag && player->sndArcStrmCallback)
        {
            RequestNextStrm(player);
        }
    }

    if (player->strmCallback != NULL)
    {
        player->strmCallback(command->status, command->numChannels, command->buffer, command->bufLen,
                             player->info.format == STRM_FORMAT_PCM8 ? NNS_SND_STRM_FORMAT_PCM8 : NNS_SND_STRM_FORMAT_PCM16, player->strmCallbackArg);
    }

    for (ch = 0; ch < command->numChannels; ch++)
    {
        DC_FlushRange(NNSi_SndStrmBufPtr(command->buffer[ch]), command->bufLen);
    }

    if (command->status == 0)
    {
        player->prepareFlag = TRUE;
    }
}

void StrmThreadProc(void *arg)
{
    NNSSndStrmThread *t = arg;
    NNSSndStrmLoadCommand *item;
    for (;;) {
        OS_SleepThread(&t->queue);
        for (;;) {
            OS_LockMutex(&t->mutex);
            item = PopCommandBuffer(&t->commandList);
            if (item == 0) {
                OS_UnlockMutex(&t->mutex);
                break;
            }
            MakeWaveData(item);
            FreeCommandBuffer(item);
            OS_UnlockMutex(&t->mutex);
        }
    }
}

BOOL NNS_SndArcPlayerSetup(void *heap)
{
    s32 i;
    PlayerRec *info;
    s32 j;
    NNS_SndArcGetCurrent();
    for (i = 0; i < 32; i++) {
        info = NNS_SndArcGetPlayerInfo(i);
        if (info != 0) {
            NNS_SndPlayerSetPlayableSeqCount(i, info->count);
            NNS_SndPlayerSetAllocatableChannel(i, info->bankNo);
            if (info->heapSize != 0 && heap != 0) {
                for (j = 0; j < info->count; j++) {
                    if (NNS_SndPlayerCreateHeap(i, heap, info->heapSize) == 0) {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

u32 NNS_SndArcPlayerStartSeq(void *handle, u32 seqNo)
{
    SeqRec *rec = NNS_SndArcGetSeqInfo(seqNo);
    if (rec == 0) {
        return 0;
    }
    return StartSeq(handle, rec->player, rec->bank, rec->prio, rec, seqNo);
}

u32 NNS_SndArcPlayerStartSeqArc(void *handle, u32 arcNo, u32 idx)
{
    SeqArcRec *rec = NNS_SndArcGetSeqArcInfo(arcNo);
    u8 *data;
    SeqRec *info;
    if (rec == 0) {
        return 0;
    }
    data = GetFileAddress(rec->fileId);
    if (data == 0) {
        return 0;
    }
    info = NNSi_SndSeqArcGetSeqInfo(data, idx);
    if (info == 0) {
        return 0;
    }
    return StartSeqArc(handle, info->player, info->bank, info->prio, info, data, arcNo, idx);
}

u32 NNS_SndArcPlayerStartSeqArcEx(void *handle, s32 player, s32 bank, s32 prio, u32 arcNo, u32 idx)
{
    SeqArcRec *rec = NNS_SndArcGetSeqArcInfo(arcNo);
    u8 *data;
    SeqRec *info;
    if (rec == 0) {
        return 0;
    }
    data = GetFileAddress(rec->fileId);
    if (data == 0) {
        return 0;
    }
    info = NNSi_SndSeqArcGetSeqInfo(data, idx);
    if (info == 0) {
        return 0;
    }
    if (prio < 0) {
        prio = info->prio;
    }
    if (bank < 0) {
        bank = info->bank;
    }
    if (player < 0) {
        player = info->player;
    }
    return StartSeqArc(handle, player, bank, prio, info, data, arcNo, idx);
}

u32 StartSeq(void *handle, s32 player, s32 bank, s32 prio, SeqRec *rec, u32 seqNo)
{
    void *seq;
    void *heap;
    u8 *seqData;
    void *bankData;
    seq = NNSi_SndPlayerAllocSeqPlayer(handle, player, prio);
    if (seq == 0) {
        return 0;
    }
    heap = NNSi_SndPlayerAllocHeap(player, seq);
    if (NNSi_SndArcLoadBank(bank, 6, heap, 0, &bankData) != 0) {
        NNSi_SndPlayerFreeSeqPlayer(seq);
        return 0;
    }
    if (NNSi_SndArcLoadSeq(seqNo, 1, heap, 0, (void **)&seqData) != 0) {
        NNSi_SndPlayerFreeSeqPlayer(seq);
        return 0;
    }
    NNSi_SndPlayerStartSeq(seq, seqData + *(u32 *)(seqData + 0x18), 0, bankData);
    NNS_SndPlayerSetInitialVolume(handle, rec->vol);
    NNS_SndPlayerSetChannelPriority(handle, rec->chPrio);
    NNS_SndPlayerSetSeqNo(handle, seqNo);
    return 1;
}

u32 StartSeqArc(void *handle, s32 player, s32 bank, s32 prio, SeqRec *rec, u8 *data, u32 arcNo, u32 idx)
{
    void *seq;
    void *heap;
    void *bankData;
    seq = NNSi_SndPlayerAllocSeqPlayer(handle, player, prio);
    if (seq == 0) {
        return 0;
    }
    heap = NNSi_SndPlayerAllocHeap(player, seq);
    if (NNSi_SndArcLoadBank(bank, 6, heap, 0, &bankData) != 0) {
        NNSi_SndPlayerFreeSeqPlayer(seq);
        return 0;
    }
    NNSi_SndPlayerStartSeq(seq, data + *(u32 *)(data + 0x18), rec->fileId, bankData);
    NNS_SndPlayerSetInitialVolume(handle, rec->vol);
    NNS_SndPlayerSetChannelPriority(handle, rec->chPrio);
    NNS_SndPlayerSetSeqArcNo(handle, arcNo, idx);
    return 1;
}

BOOL NNS_SndArcLoadGroup(u32 a, void *heap)
{
    return NNSi_SndArcLoadGroup(a, heap) == 0;
}

BOOL NNS_SndArcLoadSeqArc(u32 id, void *heap)
{
    return NNSi_SndArcLoadSeqArc(id, 255, heap, 1, 0) == 0;
}

BOOL NNS_SndArcLoadBank(u32 id, void *heap)
{
    return NNSi_SndArcLoadBank(id, 255, heap, 1, 0) == 0;
}

BOOL NNS_SndArcLoadWaveArc(u32 id, void *heap)
{
    return NNSi_SndArcLoadWaveArc(id, 255, heap, 1, 0) == 0;
}

u32 NNSi_SndArcLoadGroup(u32 grp, void *heap)
{
    GrpRec *g = NNS_SndArcGetGroupInfo(grp);
    u32 i;
    GrpEnt *e;
    u32 r;
    if (g == 0) {
        return 1;
    }
    for (i = 0; i < g->count; i++) {
        e = &g->ent[i];
        switch (e->type) {
        case 0:
            r = NNSi_SndArcLoadSeq(e->id, e->flags, heap, 1, 0);
            if (r != 0) {
                return r;
            }
            break;
        case 3:
            r = NNSi_SndArcLoadSeqArc(e->id, e->flags, heap, 1, 0);
            if (r != 0) {
                return r;
            }
            break;
        case 1:
            r = NNSi_SndArcLoadBank(e->id, e->flags, heap, 1, 0);
            if (r != 0) {
                return r;
            }
            break;
        case 2:
            r = NNSi_SndArcLoadWaveArc(e->id, e->flags, heap, 1, 0);
            if (r != 0) {
                return r;
            }
            break;
        }
    }
    return 0;
}

u32 NNSi_SndArcLoadSeq(u32 id, u32 flags, void *heap, u32 flag, void **out)
{
    SeqRec *rec = NNS_SndArcGetSeqInfo(id);
    u32 r;
    void *p;
    if (rec == 0) {
        return 2;
    }
    r = NNSi_SndArcLoadBank(rec->bank, flags, heap, flag, 0);
    if (r != 0) {
        return r;
    }
    if (flags & 1) {
        p = LoadSeq(rec->fileId, heap, flag);
        if (p == 0) {
            return 6;
        }
    } else {
        p = GetFileAddress(rec->fileId);
    }
    if (out != 0) {
        *out = p;
    }
    return 0;
}

u32 NNSi_SndArcLoadSeqArc(u32 id, u32 flags, void *heap, u32 flag, void **out)
{
    SeqArcRec *rec = NNS_SndArcGetSeqArcInfo(id);
    void *p;
    if (rec == 0) {
        return 3;
    }
    if (flags & 8) {
        p = LoadSeqArc(rec->fileId, heap, flag);
        if (p == 0) {
            return 7;
        }
    } else {
        p = GetFileAddress(rec->fileId);
    }
    if (out != 0) {
        *out = p;
    }
    return 0;
}

u32 NNSi_SndArcLoadBank(u32 id, u32 flags, void *heap, u32 flag, void **out)
{
    BankRec *rec = NNS_SndArcGetBankInfo(id);
    void *bank;
    void *wave;
    s32 i;
    u32 load;
    u32 r;
    if (rec == 0) {
        return 4;
    }
    if (flags & 2) {
        bank = LoadBank(rec->fileId, heap, flag);
        if (bank == 0) {
            return 8;
        }
    } else {
        bank = GetFileAddress(rec->fileId);
    }
    load = flags & 4;
    for (i = 0; i < 4; i++) {
        FileRec *w;
        if (rec->wa[i] == 0xffff) {
            continue;
        }
        w = NNS_SndArcGetWaveArcInfo(rec->wa[i]);
        if (w == 0) {
            return 5;
        }
        r = NNSi_SndArcLoadWaveArc(rec->wa[i], flags, heap, flag, &wave);
        if (r != 0) {
            return r;
        }
        if (w->loadFlag & 1) {
            if (load != 0) {
                if (LoadSingleWaves(wave, bank, i, w->fileId, heap) == 0) {
                    return 9;
                }
            }
        }
        if (bank != 0 && wave != 0) {
            SND_AssignWaveArc(bank, i, wave);
        }
    }
    if (out != 0) {
        *out = bank;
    }
    return 0;
}

u32 NNSi_SndArcLoadWaveArc(u32 id, u32 flags, void *heap, u32 flag, void **out)
{
    FileRec *rec = NNS_SndArcGetWaveArcInfo(id);
    void *p;
    if (rec == 0) {
        return 5;
    }
    if (flags & 4) {
        if (rec->loadFlag & 1) {
            p = LoadWaveArcTable(rec->fileId, heap, flag);
        } else {
            p = LoadWaveArc(rec->fileId, heap, flag);
        }
        if (p == 0) {
            return 9;
        }
    } else {
        p = GetFileAddress(rec->fileId);
    }
    if (out != 0) {
        *out = p;
    }
    return 0;
}

void *NNSi_SndArcLoadFile(u32 file, SndHeapDisposeCallback cb, void *arg1, u32 arg2, void *heap)
{
    u32 size = NNS_SndArcGetFileSize(file);
    u8 *mem;
    if (size == 0) {
        return 0;
    }
    if (heap == 0) {
        return 0;
    }
    mem = NNS_SndHeapAlloc(heap, size + 32, cb, arg1, arg2);
    if (mem == 0) {
        return 0;
    }
    if (size != NNS_SndArcReadFile(file, mem, size, 0)) {
        return 0;
    }
    DC_StoreRange(mem, size);
    return mem;
}

void *LoadSeq(u32 file, void *heap, u32 flag)
{
    void *p = GetFileAddress(file);
    void *arc;
    if (p == 0) {
        arc = flag ? NNS_SndArcGetCurrent() : 0;
        p = NNSi_SndArcLoadFile(file, SeqDisposeCallback, arc, file, heap);
        if (flag != 0 && p != 0) {
            SetFileAddress(file, p);
        }
    }
    return p;
}

void *LoadSeqArc(u32 file, void *heap, u32 flag)
{
    void *p = GetFileAddress(file);
    void *arc;
    if (p == 0) {
        arc = flag ? NNS_SndArcGetCurrent() : 0;
        p = NNSi_SndArcLoadFile(file, SeqDisposeCallback, arc, file, heap);
        if (flag != 0 && p != 0) {
            SetFileAddress(file, p);
        }
    }
    return p;
}

void *LoadBank(u32 file, void *heap, u32 flag)
{
    void *p = GetFileAddress(file);
    void *arc;
    if (p == 0) {
        arc = flag ? NNS_SndArcGetCurrent() : 0;
        p = NNSi_SndArcLoadFile(file, BankDisposeCallback, arc, file, heap);
        if (flag != 0 && p != 0) {
            SetFileAddress(file, p);
        }
    }
    return p;
}

void *LoadWaveArc(u32 file, void *heap, u32 flag)
{
    void *p = GetFileAddress(file);
    void *arc;
    if (p == 0) {
        arc = flag ? NNS_SndArcGetCurrent() : 0;
        p = NNSi_SndArcLoadFile(file, WaveArcDisposeCallback, arc, file, heap);
        if (flag != 0 && p != 0) {
            SetFileAddress(file, p);
        }
    }
    return p;
}

void *LoadWaveArcTable(u32 file, void *heap, u32 flag)
{
    u8 *p;
    u32 size;
    u32 n;
    void *arc;
    u32 r;
    p = GetFileAddress(file);
    if (p == 0) {
        if (NNS_SndArcReadFile(file, data_021fbd6c, 0x3c, 0) != 0x3c) {
            return 0;
        }
        n = *(u32 *)(data_021fbd6c + 0x38) * 4;
        size = n * 2 + 0x3c;
        if (heap == 0) {
            return 0;
        }
        arc = flag ? NNS_SndArcGetCurrent() : 0;
        p = NNS_SndHeapAlloc(heap, size + 32, WaveArcTableDisposeCallback, arc, file);
        if (p == 0) {
            return 0;
        }
        r = NNS_SndArcReadFile(file, p, n + 0x3c, 0);
        if (r != n + 0x3c) {
            return 0;
        }
        MI_CpuCopy8(p + 0x3c, p + 0x3c + *(u32 *)(p + 0x38) * 4, n);
        MI_CpuFill8(p + 0x3c, 0, n);
        DC_StoreRange(p, size);
        if (flag != 0) {
            SetFileAddress(file, p);
        }
    }
    return p;
}

void DisposeCallback(void *mem, void *arc, u32 idx)
{
    void *old;
    u32 irq;
    if (arc == 0) {
        return;
    }
    irq = OS_DisableInterrupts();
    old = NNS_SndArcSetCurrent(arc);
    if (mem == GetFileAddress(idx)) {
        SetFileAddress(idx, 0);
    }
    NNS_SndArcSetCurrent(old);
    OS_RestoreInterrupts(irq);
}

void SeqDisposeCallback(void *mem, u32 size, void *arc, u32 idx)
{
    DisposeCallback(mem, arc, idx);
    SND_InvalidateSeqData(SndAddr(mem), SndAddr((u8 *)mem + size));
}

void BankDisposeCallback(void *mem, u32 size, void *arc, u32 idx)
{
    DisposeCallback(mem, arc, idx);
    SND_InvalidateBankData(SndAddr(mem), SndAddr((u8 *)mem + size));
    SND_DestroyBank(mem);
}

void WaveArcDisposeCallback(void *mem, u32 size, void *arc, u32 idx)
{
    DisposeCallback(mem, arc, idx);
    SND_InvalidateWaveData(SndAddr(mem), SndAddr((u8 *)mem + size));
    SND_DestroyWaveArc(mem);
}

void WaveArcTableDisposeCallback(void *mem, u32 size, void *arc, u32 idx)
{
    DisposeCallback(mem, arc, idx);
    SND_DestroyWaveArc(mem);
}

void SingleWaveDisposeCallback(void *mem, u32 size, void *waveArc, u32 idx)
{
    if (mem == SND_GetWaveDataAddress(waveArc, idx)) {
        SND_SetWaveDataAddress(waveArc, idx, 0);
    }
    SND_InvalidateWaveData(SndAddr(mem), SndAddr((u8 *)mem + size));
}

u32 LoadSingleWave(u8 *wa, u32 idx, u32 file, void *heap)
{
    u32 size;
    u32 start;
    u32 end;
    u32 cnt;
    u32 *ent;
    u8 *mem;
    if (SND_GetWaveDataAddress(wa, idx) != 0) {
        return 1;
    }
    cnt = SND_GetWaveDataCount(wa);
    ent = (u32 *)(wa + (*(u32 *)(wa + 0x38) + idx) * 4);
    start = ent[0x3c / 4];
    end = (idx < cnt - 1) ? ent[0x40 / 4] : *(u32 *)(wa + 8);
    size = end - start;
    if (heap == 0) {
        return 0;
    }
    mem = NNS_SndHeapAlloc(heap, size + 32, SingleWaveDisposeCallback, wa, idx);
    if (mem == 0) {
        return 0;
    }
    if (size != NNS_SndArcReadFile(file, mem, size, start)) {
        return 0;
    }
    DC_StoreRange(mem, size);
    SND_SetWaveDataAddress(wa, idx, mem);
    return 1;
}

u32 LoadSingleWaves(void *wa, void *bank, u32 arcNo, u32 file, void *heap)
{
    Pair pos;
    InstOut inst;
    SND_GetFirstInstDataPos(&pos);
    if (bank == 0) {
        return 0;
    }
    while (SND_GetNextInstData(bank, &inst, &pos.a)) {
        if (inst.type == 1 && arcNo == inst.h2) {
            if (LoadSingleWave(wa, inst.h1, file, heap) == 0) {
                return 0;
            }
        }
    }
    return 1;
}

u8 data_021fbd6c[0x3c];
