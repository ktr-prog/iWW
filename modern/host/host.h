#ifndef HOST_HOST_H
#define HOST_HOST_H

#include <stddef.h>
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int32_t s32;
typedef unsigned long long u64;

void host_fatal(const char *msg) __attribute__((noreturn));
void host_unimplemented(const char *what);
extern int gHostVerbose;
extern const char *gHostRomPath;

#ifndef HOST_DEBUG_POSIX
#if defined(_WIN32)
#define HOST_DEBUG_POSIX 0
#else
#define HOST_DEBUG_POSIX 1
#endif
#endif

void host_map_memory(void);
int host_highmem(void);
void host_highmem_init(void);
void HostMem_Init(void);
void HostMem_Check(void);
void *HostMem_AlignedBlock(size_t size, size_t align);
u8 *host_io(u32 addr);
unsigned long long HostIo_Read(uintptr_t addr, unsigned int size);
unsigned long long HostIo_Write(uintptr_t addr, unsigned int size, unsigned long long value);
void host_io_ring_dump(void);
void host_quit(void) __attribute__((noreturn));
void host_set_paused(int paused);
void host_exit_dumps(void);

void host_debug_init(void);
void host_debug_crash_handlers(void);
void host_debug_exit_dumps(void);
u32 host_irq_pending(void);
void host_irq_ack(u32 mask);
void host_irq_raise(u32 mask);
void host_irq_call(int bit);
void host_advance_to_next_event(void);
u64 host_frame(void);
u64 host_cycles(void);
void host_spend_cycles(u64 n);

void *host_stack_alloc(size_t n);
void host_deliver_irqs(void);

void pxi7_init(void);
void pxi7_receive(u32 word);
void pxi7_send(u32 word);
void pxi7_sync_written(u32 value);

void card_init(const char *rom);
void card_control_written(u32 romctrl);
u32 card_read_data(void);

#endif
