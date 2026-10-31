#include "host_mem.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef int BOOL;

u32 OS_DisableInterrupts(void);
void OS_RestoreInterrupts(u32 e);
u32 OS_GetLockID(void);
u16 OS_ReadOwnerOfLockWord(void *p);
u32 OS_TryLockCartridge(u32 id);
void OS_UnlockCartridge(u32 id);

u32 OSi_DetectDeviceType(void) {
    u32 result;
    BOOL done;
    u32 id;
    s32 lockResult;
    u32 e;
    done = 0;
    id = (u16)OS_GetLockID();
    result = 0;
    while (!done) {
        lockResult = -1;
        e = OS_DisableInterrupts();
        if ((OS_ReadOwnerOfLockWord(HW_SYSWORK(void, ctrdgLock)) & 0x40) != 0 || (lockResult = OS_TryLockCartridge(id)) == 0) {
            static const u32 kNoCartridge[2] = {0xffffffff, 0xffffffff};
            if (kNoCartridge[0] == 0x544e494e && kNoCartridge[1] == 0x4f444e45) {
                result = 0x01000000;
            } else {
                result = 0x02000000;
            }
            if (lockResult == 0) {
                OS_UnlockCartridge(id);
                done = 1;
            }
        }
        OS_RestoreInterrupts(e);
    }
    return result;
}
