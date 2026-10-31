typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef int BOOL;
#include "types64.h"
#include "proto/autoload_2/unk_020fe848.h"
#include "proto/autoload_2/unk_0211d20c.h"
#include "proto/autoload_2/unk_0212703c.h"
#include "proto/itcm/unk_01ffa4a0.h"
#include "proto/main/unk_02000b44.h"
#include "proto/main/unk_0206d49c.h"

typedef struct { u32 w0, w1, w2; } FD;
typedef struct {
    u32 size;
    FD id;
    FD fr;
    u32 v1c;
    u32 flags;
    u32 key;
    u32 pad28[5];
    u32 crc;
} UserData;
typedef struct { u64 a; u64 b; u32 valid; u32 pad; } Rec;
typedef struct { u64 a; u64 b; u16 f16; u16 f18; } S;
typedef struct { u32 year, month, day; s32 week; } Date;
typedef struct { u32 hour, minute, second; } Time;

extern void MI_CpuFill8(void *dst, u32 val, u32 len);
extern u64 func_02133100(u64 a, u64 b);
extern s32 OS_SNPrintf(char *buf, u32 size, const char *fmt, ...);

extern const u32 data_0213bba8[];
extern const u8 data_02135ca8[];
extern const u8 data_02135ca0[];
extern u8 data_021f5c5c[];
#define data_021f5c61 (data_021f5c5c + 5)
#define data_021f5c62 (data_021f5c5c + 6)
#define data_021f5c66 (data_021f5c5c + 10)
#define data_021f5c68 (data_021f5c5c + 12)
extern u32 data_021f5c58;
extern volatile u16 data_021f5c50;
extern volatile u32 data_021f5c54;
extern u8 data_021f5c80[];
extern const u8 data_02135c9c[];
extern int memcmp(const void *a, const void *b, u32 n);
extern s32 PXI_IsCallbackReady(u32 tag, u32 x);
extern void PXI_SetFifoRecvCallback(u32 tag, void *cb);
extern void DC_StoreRange(void *p, u32 n);
extern void DC_InvalidateRange(void *p, u32 n);
extern void MIi_CpuClear16(u16 v, void *dst, u32 n);
extern void WaitByLoop(u32 n);
extern s32 PXI_SendWordByFifo(u32 tag, u32 data, s32 err);
extern void MI_CpuCopy8(const void *src, void *dst, u32 len);
extern const char data_0213bbdc[];
extern const char data_0213bbec[];

u32 DWCi_Acc_GetFlags(FD *p);
u32 DWCi_Acc_GetFlag_DataType(FD *p);
BOOL DWCi_Acc_SetMaskBits(u32 *p, u32 v, u32 shift, u32 mask);
void DWCi_Acc_SetFlags(FD *p, u32 v);
void DWCi_Acc_SetFlag_DataType(FD *p, u32 v);
u64 DWCi_Acc_GetUserId(FD *p);
u64 DWCi_Acc_GetFriendKey(FD *p);
u32 DWCi_Acc_GetGsProfileId(FD *p);
u32 DWCi_Acc_GetPlayerId(FD *p);
void DWCi_Acc_SetGsProfileId(FD *p, u32 v);
void DWCi_Acc_SetFriendKey(FD *p, u32 a, u32 b);
void DWCi_Acc_SetPlayerId(FD *p, u32 v);
void DWCi_Acc_SetUserId(FD *p, u64 v);
BOOL DWC_Acc_CheckFriendKey(u64 v, u32 key);
u64 DWC_Acc_CreateFriendKey(u32 lo, u32 key);
BOOL DWC_Auth_CheckWiFiIDNeedCreate(void);
u16 Callback_NVRAM(u32 tag, u32 data, u32 err);
BOOL writeDisable(void);
BOOL verify(void *ref, u32 addr, u32 size, void *tmp);
void writeNvram(u32 addr, u16 size, void *src);
BOOL readNvram(u32 addr, u32 size, void *dst);
u32 NVRAMm_ExecuteCommand(u32 cmd, u32 a1, u16 a2, void *data);
BOOL DWC_BACKUPlCheckAddress(u8 *p);
BOOL DWC_BACKUPlCheckIp(u8 *a, u8 *b);
BOOL DWC_BACKUPlCheckSsid(u8 *p);
void DWCi_BACKUPlConvMaskAddr(u32 n, u8 *out);
u8 DWCi_BACKUPlConvMaskCidr(u8 *p);
void DWCi_BACKUPlSetWiFi(u8 *p);
BOOL DWCi_BACKUPlWriteAll(u8 *buf);
BOOL DWCi_BACKUPlWritePage(u8 *buf, u32 *flags, u8 *tmp);
BOOL DWCi_BACKUPlRead(u8 *dst);
BOOL DWCi_BACKUPlInit(u16 *p);
BOOL DWCi_BM_GetApInfo(u8 *dst);
void initPage(u8 *buf, u32 idx);
BOOL init__DwcBm(u8 *buf);
BOOL checkAp(u8 *page);
s32 DWC_BM_Init(u8 *p);
u8 *DWCi_BACKUPlConvWifiInfo(S *p);
s32 DWC_BM_Init(u8 *p);
BOOL DWCi_AUTH_MakeWiFiID(u8 *buf);
BOOL DWCi_AUTH_UpDateWiFiID(S *p, u8 *buf);
extern s32 RTC_GetDate(Date *d);
extern s32 RTC_GetTime(Time *t);
extern s32 OS_IsTickAvailable(void);
extern void OS_GetMacAddress(u8 *mac);
void DWCi_BM_GetWiFiInfo(S *out);
BOOL DWCi_BM_SetWiFiInfo(S *p, u8 *buf);
u64 DWCi_Util_WiFiId_scrambleUid(u32 a, u32 b, u32 c, u32 d);
s64 DWCi_Util_ConvertDateTimeToSecond(Date *d, Time *t);
s32 DWCi_Util_ConvertTimeToSecond(Time *t);
s32 DWCi_Util_ConvertDateToDay(Date *d);
u32 DWC_Acc_FriendKeyToGsProfileId(u64 v, u32 key);
void DWCi_Acc_U64ToString32(u64 v, s32 nbits, char *out);
void DWCi_Acc_LoginIdToUserName(FD *fd, u32 gamecode, char *out);
void DWCi_Acc_CreateTempLoginId(FD *p);
void DWC_Auth_GetId(Rec *out);
BOOL DWCi_AUTH_GetNewWiFiInfo(S *p);
BOOL DWCi_Acc_IsAuthentic(UserData *p);
BOOL DWCi_Acc_IsValidLoginId(FD *p);
void DWCi_Acc_CreateUserData(UserData *p, u32 key);
BOOL DWC_IsValidFriendData(FD *p);

static inline u32 clr(u32 v, u32 m) { return v & ~m; }
static inline u64 fld(u64 v, u64 mask, s32 shift) { return (v & mask) << shift; }
































































static inline u32 orr(u32 a, u32 b) { return a | b; }

BOOL readNvram(u32 addr, u32 size, void *dst) {
    DC_InvalidateRange(dst, size);
    while (!PXI_IsCallbackReady(4, 1)) {
    }
    PXI_SetFifoRecvCallback(4, Callback_NVRAM);
    for (;;) {
        if (NVRAMm_ExecuteCommand(1, addr, size, dst) == 1) {
            break;
        }
        WaitByLoop(0x40000);
    }
    DC_InvalidateRange(dst, size);
    return 1;
}

void writeNvram(u32 addr, u16 size, void *src) {
    while (!PXI_IsCallbackReady(4, 1)) {
    }
    PXI_SetFifoRecvCallback(4, Callback_NVRAM);
    DC_StoreRange(src, size);
    for (;;) {
        if (NVRAMm_ExecuteCommand(2, addr, size, src) == 1) {
            break;
        }
        WaitByLoop(0x40000);
    }
}

BOOL verify(void *ref, u32 addr, u32 size, void *tmp) {
    if (!readNvram(addr, size, tmp)) {
        return 0;
    }
    if (memcmp(ref, tmp, size) == 0) {
        return 1;
    }
    return 0;
}

BOOL writeDisable(void) {
    while (!PXI_IsCallbackReady(4, 1)) {
    }
    PXI_SetFifoRecvCallback(4, Callback_NVRAM);
    for (;;) {
        if (NVRAMm_ExecuteCommand(7, 0, 0, 0) == 1) {
            break;
        }
        WaitByLoop(0x40000);
    }
    return 1;
}

u16 Callback_NVRAM(u32 tag, u32 data, u32 err) {
    data_021f5c50 = (u16)(data & 0xff);
    data_021f5c54 = 1;
    if (err) {
        data_021f5c50 = 0xff;
    }
    return data_021f5c50;
}

u8 *DWCi_BACKUPlConvWifiInfo(S *p) {
    u64 t = *(volatile u64 *)&p->b;
    MI_CpuCopy8(p, data_021f5c5c, 5);
    data_021f5c5c[5] = (((u32)(p->a >> 32) >> 8) & 7) | ((t & 0x1f) << 3);
    t >>= 5;
    MI_CpuCopy8(&t, data_021f5c62, 4);
    data_021f5c5c[10] = ((u32)(t >> 32) & 0x3f) | ((p->f16 & 3) << 6);
    data_021f5c5c[11] = p->f16 >> 2;
    MI_CpuCopy8(&p->f18, data_021f5c68, 2);
    return data_021f5c5c;
}

u8 *DWCi_BACKUPlGetWifi(void) {
    return data_021f5c5c;
}
