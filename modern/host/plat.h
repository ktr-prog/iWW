#ifndef HOST_PLAT_H
#define HOST_PLAT_H

#include <stddef.h>
#include <stdint.h>
#include <time.h>

uint64_t host_plat_time_ns(void);
void host_plat_sleep_until_ns(uint64_t t);
void host_plat_sleep_ms(unsigned ms);
int host_plat_localtime(struct tm *out);

void host_plat_restart(char **argv);

int host_plat_thread_start(void (*fn)(void *), void *arg);

void *host_plat_stack_alloc(size_t n, int flags);
void host_plat_stack_free(void *stack, size_t n);
void *host_plat_pages_alloc(size_t n);
int host_plat_arena(uintptr_t *base, size_t *used);
int host_plat_arena_set_used(size_t used);
int host_plat_commit(void *p, size_t n);
void *host_plat_arena_top(size_t n);

int host_plat_image_bounds(uintptr_t *lo, uintptr_t *hi);

void *host_plat_read_file(const char *path, size_t *size);

int host_plat_backtrace(void **pcs, int n);
void host_plat_print_backtrace(void);

#endif
