#ifndef HOST_CORO_H
#define HOST_CORO_H

#include <stddef.h>

void host_coro_switch(void **save, void *to);

void *host_coro_prepare(void *stack, size_t size, void (*fn)(void *), void *arg);

#if defined(HOST_ASAN) && !defined(HOST_CORO_IMPL)
void host_coro_switch_asan(void **save, void *to);
#define host_coro_switch host_coro_switch_asan
#endif

#endif
