#ifndef HOST_MEM_H
#define HOST_MEM_H


#ifdef __cplusplus
extern "C" {
#endif

typedef struct HostSysWork {
    unsigned char sharedArena[0x680];
    unsigned char reserved_680[0x400];
    unsigned char cardRomHeader[0x160];
    unsigned char reserved_be0[0x20];
    unsigned char bootCheckInfo[0x20];
    unsigned int resetParameter;
    unsigned char reserved_c24[8];
    unsigned int romBaseOffset;
    unsigned char ctrdgModuleInfo[0xc];
    unsigned int vblankCount;
    unsigned char wmBootBuf[0x40];
    unsigned char nvramUserInfo[0x100];
    unsigned char biosExcpStack[0x10];
    unsigned char reserved_d90[0xc];
    void *excpVector;
    void *arenaLo[9];
    void *arenaHi[9];
    unsigned int realTimeClock[2];
    unsigned char dmaClearData[0x10];
    unsigned char romHeader[0x160];
    unsigned char isdReserved[0x20];
    unsigned int pxiSignalParam[2];
    unsigned int pxiHandleChecker[2];
    unsigned int micLastAddress;
    unsigned short micSamplingData;
    unsigned short wmCallbackControl;
    unsigned short wmRssiPool;
    unsigned char reserved_f9a[2];
    unsigned int componentParam;
    void *threadInfoMain;
    unsigned int threadInfoSub;
    unsigned short buttonXY;
    unsigned short touchPanel[2];
    unsigned short autoloadSync;
    unsigned int lockIdFlagMain[2];
    unsigned int lockIdFlagSub[2];
    unsigned int vramCLock[2];
    unsigned int vramDLock[2];
    unsigned int wram0Lock[2];
    unsigned int wram1Lock[2];
    unsigned int cardLock[2];
    unsigned int ctrdgLock[2];
    unsigned int initLock[2];
    unsigned short mmemCheckerMain;
    unsigned short mmemCheckerSub;
    unsigned char reserved_ffc[4];
} HostSysWork;

extern HostSysWork gHostSysWork;
#define HW_SYSWORK(T, m) ((T *)&gHostSysWork.m)
#define HW_SYSWORK_AT(T, m, o) ((T *)((unsigned char *)&gHostSysWork.m + (o)))

#if defined(_WIN32) || defined(__APPLE__)
#define HOST_MEM_RUNTIME_ALIGN 1
#else
#define HOST_MEM_RUNTIME_ALIGN 0
#endif

#if HOST_MEM_RUNTIME_ALIGN
extern unsigned char (*gHostDtcmBlock)[0x4000], (*gHostItcmBlock)[0x8000];
#define gHostDtcm (*gHostDtcmBlock)
#define gHostItcm (*gHostItcmBlock)
#else
extern unsigned char gHostDtcm[0x4000];
extern unsigned char gHostItcm[0x8000];
#endif
#define HW_DTCM_BLOCK (gHostDtcm)
#define HW_ITCM_BLOCK (gHostItcm)
#define HW_INTR_CHECK_BUF ((volatile unsigned int *)(gHostDtcm + 0x3ff8))

extern unsigned char gHostPltt[0x800];
extern unsigned char gHostOam[0x800];
#define HW_PLTT (gHostPltt)
#define HW_OAM (gHostOam)

void *HostVram_CpuPtr(unsigned int dsaddr);

#define HOST_MAIN_RAM_LO 0x02200000u
#define HOST_MAIN_RAM_HI 0x02400000u
#if HOST_MEM_RUNTIME_ALIGN
extern unsigned char (*gHostMainRamBlock)[HOST_MAIN_RAM_HI - HOST_MAIN_RAM_LO];
#define gHostMainRam (*gHostMainRamBlock)
#else
extern unsigned char gHostMainRam[HOST_MAIN_RAM_HI - HOST_MAIN_RAM_LO];
#endif
void *HostMainRam_Ptr(unsigned int dsaddr);

extern unsigned char gHostWramArena[32];

extern char gHostGameDataBegin[1], gHostGameDataEnd[1], gHostGameBssBegin[1], gHostGameBssEnd[1];
char *host_game_static_bss_begin(void);
char *host_game_static_bss_end(void);

int HostMem_IsGameRam(const void *p, unsigned int n);

#ifdef __cplusplus
}
#endif

#endif
