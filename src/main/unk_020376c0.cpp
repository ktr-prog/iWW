#include "uptr.h"
#include "nitro/fs.h"
#include "types.h"
#include "proto/autoload_2/unk_02119434.h"
#include "proto/main/unk_020376c0.h"


extern "C" {
BOOL FS_OpenFile(FSFile *file, const char *path);
s32 FS_ReadFile(FSFile *file, void *dst, s32 len);
BOOL FS_CloseFile(FSFile *file);
}

u8 gBuildTime[0x20];

extern "C" void Main_LoadBuildTime() {
    FSFile file;
    FS_InitFile(&file);
    if (FS_OpenFile(&file, "/BUILDTIME") == 1) {
        FS_ReadFile(&file, gBuildTime, 0x20);
        FS_CloseFile(&file);
    }
}
