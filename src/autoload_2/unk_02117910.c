#include "uptr.h"
#include "proto/autoload_2/unk_02114410.h"
#include "proto/autoload_2/unk_02116c0c.h"
#include "proto/autoload_2/unk_02116d24.h"
#include "proto/autoload_2/unk_02117518.h"
#include "proto/autoload_2/unk_02117910.h"
#include "proto/autoload_2/unk_02117e8c.h"
#include "proto/itcm/unk_01ffa3cc.h"
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct Cmd {
    struct Cmd *next;
    u32 id;
    uptr arg[4];
} Cmd;

typedef struct SndWork {
    u32 f0;
    u32 f4;
    u16 f8;
    u16 fa;
    u8 pad[0x14];
    struct {
        s16 v[16];
        u32 w;
    } t[16];
    s16 u[16];
} SndWork;

typedef struct Slot {
    void *a;
    struct Slot *next;
} Slot;

typedef struct Obj {
    u8 pad[0x18];
    Slot s[4];
} Obj;

typedef struct Pair {
    u32 a;
    u32 b;
} Pair;

typedef struct Bank {
    u8 pad[0x38];
    u32 count;
    u32 ent[1];
} Bank;

typedef struct H5 {
    u16 h[5];
} H5;

typedef struct H6 {
    u16 h[6];
} H6;

typedef union InstOut {
    u8 type;
    u16 h[6];
} InstOut;

typedef struct TrackOut {
    u16 a;
    u8 b;
    u8 c;
    s8 d;
    u8 e;
    u8 f;
    s8 g;
    u8 pad8;
    u8 cnt;
    u8 list[1];
} TrackOut;

typedef struct ChOut {
    u32 bit0 : 1;
    u32 bit1 : 1;
    u16 mask;
    u16 h6;
    u8 b8;
} ChOut;

typedef struct ChRec {
    u8 f0_0 : 1;
    u8 f0_1 : 1;
    u8 f0_2 : 1;
    u8 pad1[4];
    u8 b5;
    u8 pad6[2];
    u8 x[16];
    u16 h24;
    u8 pad26[10];
} ChRec;

typedef struct SlotEnt {
    uptr a;
    uptr b;
    u8 cnt;
} SlotEnt;

extern Cmd data_021fd260[256];
extern Cmd *data_021fcf88;
extern u32 data_021fcf8c;
extern Cmd *data_021fcf90;
extern Cmd *data_021fcf94;
extern Cmd *data_021fcf98;
extern s32 data_021fcf9c;
extern s32 data_021fcfa0;
extern s32 data_021fcfa4;
extern u32 data_021fcfa8;
extern Cmd *data_021fcfac[];
extern u32 data_021fcf6c;
extern u32 data_021fcf70;
extern SndWork data_021fcfe0;
extern SndWork *data_021fea60;
extern const u8 data_0213a0b4[724];
extern SlotEnt data_027e032c[];

extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32);
extern void OS_SpinWait(u32);
extern void PxiFifoCallback(void);
extern void DC_InvalidateRange(void *, u32);
extern void DC_StoreRange(void *, u32);
extern void DC_FlushRange(void *, u32);
extern void SNDi_SetPlayerParam(u32, u32, u32, u32);
extern void PushCommand_impl(u32, uptr, uptr, uptr, uptr);

typedef union PxiMsg {
    u32 raw;
    struct {
        u32 tag : 5;
        u32 err : 1;
        u32 data : 26;
    } b;
} PxiMsg;

#define reg_IPCSYNC (*(volatile u16 *)0x04000180)
#define reg_IPCFIFOCNT (*(volatile u16 *)0x04000184)
#define reg_IPCFIFOSEND (*(volatile u32 *)0x04000188)

s32 PXI_SendWordByFifo(u32 tag, u32 data, u32 err);
Cmd *AllocCommand(void);
u32 IsCommandAvailable(void);
u32 SND_CountWaitingCommand(void);
u32 SND_CountReservedCommand(void);
u32 SND_CountFreeCommand(void);
u32 SND_IsFinishedCommandTag(u32 t);
Cmd *SND_RecvCommandReply(u32 flags);
u32 SND_FlushCommand(u32 flags);
void SND_PushCommand(Cmd *c);
Cmd *SND_AllocCommand(u32 flags);
void SNDi_InitSharedWork(SndWork *w);
u32 SNDi_GetFinishedCommandTag(void);
extern void PXI_SetFifoRecvCallback(u32 tag, void (*cb)(void));
extern u32 PXI_IsCallbackReady(u32 tag, u32 proc);u16 SND_CalcChannelVolume(s32 x) {
    u32 r;
    u32 v;
    if (x < -723) {
        x = -723;
    } else if (x > 0) {
        x = 0;
    }
    v = data_0213a0b4[x + 723];
    if (x < -240) {
        r = 3;
    } else if (x < -120) {
        r = 2;
    } else if (x < -60) {
        r = 1;
    } else {
        r = 0;
    }
    return v | (r << 8);
}

extern const s16 data_02139fb4[128];
const s16 data_02139fb4[128] = {
    -723, -421, -361, -325, -300, -281, -265, -252, -240, -230, -221, -212, -205, -198, -192, -186,
    -180, -175, -170, -165, -161, -156, -152, -148, -145, -141, -138, -134, -131, -128, -125, -122,
    -120, -117, -114, -112, -110, -107, -105, -103, -100, -98, -96, -94, -92, -90, -88, -86,
    -85, -83, -81, -79, -78, -76, -74, -73, -71, -70, -68, -67, -65, -64, -62, -61,
    -60, -58, -57, -56, -54, -53, -52, -51, -49, -48, -47, -46, -45, -43, -42, -41,
    -40, -39, -38, -37, -36, -35, -34, -33, -32, -31, -30, -29, -28, -27, -26, -25,
    -24, -23, -23, -22, -21, -20, -19, -18, -17, -17, -16, -15, -14, -13, -12, -12,
    -11, -10, -9, -9, -8, -7, -6, -6, -5, -4, -3, -3, -2, -1, -1, 0,
};
const u8 data_0213a0b4[724] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10,
    10, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 14,
    14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 18, 18,
    18, 18, 18, 19, 19, 19, 19, 20, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 22, 23, 23, 23, 24,
    24, 24, 24, 25, 25, 25, 25, 26, 26, 26, 27, 27, 27, 28, 28, 28, 29, 29, 29, 30, 30, 30, 31, 31,
    31, 32, 32, 32, 33, 33, 34, 34, 34, 35, 35, 36, 36, 36, 37, 37, 38, 38, 39, 39, 39, 40, 40, 41,
    41, 42, 42, 43, 43, 44, 44, 45, 45, 46, 46, 47, 47, 48, 49, 49, 50, 50, 51, 51, 52, 53, 53, 54,
    54, 55, 56, 56, 57, 58, 58, 59, 60, 60, 61, 62, 63, 63, 64, 65, 66, 66, 67, 68, 69, 69, 70, 71,
    72, 73, 74, 74, 75, 76, 77, 78, 79, 80, 81, 82, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 93, 94,
    95, 96, 97, 98, 99, 100, 101, 103, 104, 105, 106, 107, 109, 110, 111, 113, 114, 115, 117, 118, 119, 121, 122, 123,
    125, 126, 127, 32, 33, 33, 33, 34, 34, 35, 35, 35, 36, 36, 37, 37, 38, 38, 38, 39, 39, 40, 40, 41,
    41, 42, 42, 43, 43, 44, 44, 45, 45, 46, 46, 47, 47, 48, 48, 49, 49, 50, 51, 51, 52, 52, 53, 54,
    54, 55, 55, 56, 57, 57, 58, 59, 59, 60, 61, 62, 62, 63, 64, 64, 65, 66, 67, 67, 68, 69, 70, 71,
    71, 72, 73, 74, 75, 76, 77, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93,
    94, 95, 96, 98, 99, 100, 101, 102, 103, 105, 106, 107, 108, 109, 111, 112, 113, 115, 116, 117, 119, 120, 121, 123,
    124, 126, 126, 64, 65, 66, 67, 67, 68, 69, 70, 71, 71, 72, 73, 74, 75, 76, 76, 77, 78, 79, 80, 81,
    82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 100, 101, 102, 103, 104, 105, 107,
    108, 109, 110, 112, 113, 114, 116, 117, 118, 120, 121, 123, 124, 125, 126, 64, 65, 66, 66, 67, 68, 69, 70, 70,
    71, 72, 73, 74, 75, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93,
    94, 95, 96, 97, 98, 99, 101, 102, 103, 104, 105, 106, 108, 109, 110, 111, 113, 114, 115, 117, 118, 119, 121, 122,
    124, 125, 126, 127,
};
