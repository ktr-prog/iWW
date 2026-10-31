
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "host.h"
#include "plat.h"
#include "savestate.h"

#define ROMCTRL 0x040001a4u
static const u8 *sRom;
static u32 sRomSize;
static const char *sRomPath;
static u32 sAddr, sLeft, sIsData;
HOST_STATE_KEEP(sRom)
HOST_STATE_KEEP(sRomSize)
HOST_STATE_KEEP(sRomPath)

void card_init(const char *path) {
    sRomPath = path;
    size_t n;
    sRom = host_plat_read_file(path, &n);
    if (!sRom) { perror(path); exit(1); }
    if (n > 0xffffffffu) host_fatal("the ROM file is larger than 4 GB");
    sRomSize = (u32)n;
    void *fixed = host_plat_arena_top(n);
    if (fixed) {
        memcpy(fixed, sRom, n);
        free((void *)sRom);
        sRom = fixed;
    }
}

const u8 *host_rom(u32 *size) { *size = sRomSize; return sRom; }
const char *host_rom_path(void) { return sRomPath; }

void host_card_dma(void);

void card_control_written(u32 ctrl) {
    if (!(ctrl >> 31)) return;
    const u8 *cmd = host_io(0x040001a8);
    u32 blk = ctrl >> 24 & 7;
    sLeft = blk == 0 ? 0 : blk == 7 ? 4 : 0x100u << blk;
    sIsData = cmd[0] == 0xb7;
    sAddr = (u32)cmd[1] << 24 | cmd[2] << 16 | cmd[3] << 8 | cmd[4];
    if (sLeft == 0) { *(u32 *)host_io(ROMCTRL) = ctrl & ~0x80800000u; return; }
    *(u32 *)host_io(ROMCTRL) = ctrl | 0x00800000;
    host_card_dma();
}

void host_card_read(u32 addr, void *dst, u32 n) {
    for (u32 i = 0; i < n; i++) ((u8 *)dst)[i] = addr + i < sRomSize ? sRom[addr + i] : 0xff;
}

u32 card_read_data(void) {
    u32 v = 0xffffffff;
    if (sLeft) {
        if (sIsData) {
            v = 0;
            for (int i = 0; i < 4; i++) {
                u32 a = sAddr + i;
                if (a < 0x8000) a = 0x8000 + (a & 0x1ff);
                v |= (a < sRomSize ? sRom[a] : 0xff) << (i * 8);
            }
        }
        sAddr += 4;
        sLeft -= 4;
        if (sLeft == 0) {
            u32 c = *(u32 *)host_io(ROMCTRL) & ~0x80800000u;
            *(u32 *)host_io(ROMCTRL) = c;
            if (*(u16 *)host_io(0x040001a0) & 0x4000) host_irq_raise(1u << 19);
        }
    }
    return v;
}
