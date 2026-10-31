#include "nitro/os_rtc.h"
#include "uptr.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
#include "types64.h"
typedef int BOOL;

#include "sys/OSThread.h"
#include "proto/autoload_2/unk_02113088.h"
#include "proto/autoload_2/unk_02117984.h"
#include "proto/autoload_2/unk_0211d680.h"
#include "proto/autoload_2/unk_0211da74.h"
#include "proto/autoload_2/unk_0211dc4c.h"
#include "proto/autoload_2/unk_0211e558.h"
#include "proto/autoload_2/unk_0211ea4c.h"
#include "proto/main/unk_02000b44.h"
#include "proto/main/unk_0206d49c.h"
typedef OSThreadQueue OSQ;
typedef OSThread OST;

typedef struct {
    u32 lock;
    uptr f4, f8, fc, f10;
    u32 command;
    u32 f18;
    uptr f1c;
    u32 result;
} RTCWork;

#include "sys/CardCmd.h"

typedef struct CARDCommon {
    CARDCmd *cmd;
    u32 f4;
    volatile u32 lockOwner;
    volatile u32 lockCount;
    OSQ queue;
    u32 lockType;
    uptr src;
    uptr dst;
    u32 len;
    u32 op;
    u32 f2c, f30, f34;
    void (*callback)(void *);
    void *cbArg;
    void (*task)(struct CARDCommon *);
    OST thread;
    OST *curThread;
    u32 priority;
    OSQ tq;
    volatile u32 flag;
    u32 f118, f11c;
    u8 buf[0x100];
} CARDCommon;

typedef struct {
    void (*fn)(void *);
    u32 f4;
    u32 f8;
    u32 fc;
    u32 f10, f14, f18, f1c;
    u32 buf[512];
} RomDev;

extern RTCWork data_021feb90;
extern u16 data_021feb8c;
extern CARDCommon data_021fec00;
extern u32 data_021febb4;
extern u8 data_021febc0[];
extern u32 data_021ff220;
extern RomDev data_021ff240;
extern OSThreadInfo data_021fcc2c;

u32 OS_DisableInterrupts(void);
void OS_RestoreInterrupts(u32);
void OS_UnlockCard(u32);
void OS_LockCard(u32);
void OS_SetThreadPriority(void *, u32);
void OS_WakeupThreadDirect(void *);
void OS_CreateThread(void *, void (*)(void *), void *, void *, u32, u32);
void DC_InvalidateRange(void *, u32);
void DC_FlushRange(void *, u32);
void DC_WaitWriteBufferEmpty(void);
void MI_StopDma(u32);
void MIi_CpuClearFast(u32, void *, u32);
void MI_CpuFill8(void *, u32, u32);
void MI_CpuCopy8(const void *, void *, u32);
BOOL PXI_IsCallbackReady(u32, u32);
s32 PXI_SendWordByFifo(u32, u32, u32);
void PXI_SetFifoRecvCallback(u32, void *);
void RtcWaitBusy(void);
void RtcGetResultCallback(void);
void RtcCommonCallback(void);
void CARDi_OnFifoRecv(void);
BOOL CARDi_Request(void *, u32, u32);
void CARDi_SetRomOp(u32, u32);
BOOL CARDi_ReadFromCache(void *);
BOOL CARDi_TryReadCardDma(void *);

u32 RTC_GetDateTimeAsync(void *, void *, void (*)(void), void *);
u32 RTC_GetTimeAsync(void *, void (*)(void), void *);
u32 RTC_GetDateAsync(void *, void (*)(void), void *);
BOOL RtcSendPxiCommand(u32);
BOOL RTCi_ReadRawDateAsync(void);
BOOL RTCi_ReadRawTimeAsync(void);
BOOL RTCi_ReadRawDateTimeAsync(void);
s32 RTCi_ConvertTimeToSecond(RTCTime *);
s32 RTC_ConvertDateToDay(RTCDate *);
void CARD_Enable(u32);
u32 CARD_IsEnabled(void);
void CARDi_UnlockResource(u32, u32);
void CARDi_LockResource(u32, u32);
void CARDi_SetTask(void (*)(CARDCommon *));
void CARDi_IdentifyBackupCore(s32);
void CARDi_RequestStreamCommandCore(CARDCommon *);
BOOL CARD_WaitRomAsync(void);
void CARDi_ReadRomSyncCore(CARDCommon *);
BOOL CARDi_TryWaitAsync(void);
BOOL CARDi_WaitAsync(void);

#define REG_MCCNT1 (*(volatile u32 *)0x040001a4)
typedef struct {
    u32 total_size, sect_size, page_size, addr_width, program_page, write_page, write_page_total, erase_chip, erase_chip_total, erase_sector;
} Spec;
typedef struct { u32 result; s32 type; u32 id; uptr src, dst; u32 len; Spec spec; } Arg;
void CARDi_IdentifyBackupCore(s32 type) {
    Arg *const p = (Arg *)data_021fec00.cmd;
    MI_CpuFill8(&p->spec, 0, sizeof(p->spec));
    p->type = type;
    if (type != 0) {
        const u32 size = (u32)(1 << ((type >> 8) & 0xff));
        const s32 device = type & 0xff;
        p->spec.total_size = size;
        if (device == 1) {
            switch (size) {
            default:
                goto invalid_type;
            case 0x200:
                p->spec.page_size = 0x10; p->spec.addr_width = 1; p->spec.program_page = 0x4f;
                break;
            case 0x2000:
                p->spec.page_size = 0x20; p->spec.addr_width = 2; p->spec.program_page = 0x4f;
                break;
            case 0x10000:
                p->spec.page_size = 0x80; p->spec.addr_width = 2; p->spec.program_page = 0x9e;
                break;
            }
        } else if (device == 2) {
            switch (size) {
            default:
                goto invalid_type;
            case 0x40000:
                p->spec.write_page = 0x18b; p->spec.write_page_total = 0x127f; p->spec.erase_sector = 0x127f; p->spec.erase_chip_total = 0x13435; p->spec.erase_chip = 0x13435;
                break;
            case 0x80000:
            case 0x100000:
                p->spec.write_page = 0x18b; p->spec.write_page_total = 0; p->spec.erase_sector = 0x127f; p->spec.erase_chip_total = 0x13435;
                break;
            }
            p->spec.sect_size = 0x10000; p->spec.page_size = 0x100; p->spec.addr_width = 3; p->spec.program_page = 0x4f;
        } else if (device == 3) {
            switch (size) {
            default:
                goto invalid_type;
            case 0x2000:
            case 0x8000:
                break;
            }
            p->spec.page_size = size; p->spec.addr_width = 2;
        } else {
          invalid_type:
            p->type = 0;
            p->spec.total_size = 0;
            data_021fec00.cmd->result = 3;
            return;
        }
    }
}
