
#include "host.h"
#include "host_mem.h"
#include "guards.h"

void host_vram_init(void);

__attribute__((constructor(101))) static void early_init(void) {
    HostMem_Init();
    host_map_memory();
    host_vram_init();
    host_guards_init();
    host_highmem_init();
}
