
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define HOST_CORO_IMPL
#include "coro.h"

void host_coro_boot(void);

#if defined(__x86_64__) && (defined(_WIN32) || defined(HOST_CORO_WIN64_TEST))
static void *prepare_win64(void *stack, size_t size, void (*fn)(void *), void *arg, void (*boot)(void)) {
    uintptr_t top = ((uintptr_t)stack + size) & ~(uintptr_t)15;
    uint64_t *sp = (uint64_t *)top - 32;
    memset(sp, 0, 32 * sizeof *sp);
    sp[20] = (uint64_t)(uintptr_t)stack;
    sp[21] = (uint64_t)top;
    sp[22] = (uint64_t)(uintptr_t)stack;
    sp[25] = (uint64_t)(uintptr_t)arg;
    sp[26] = (uint64_t)(uintptr_t)fn;
    sp[31] = (uint64_t)(uintptr_t)boot;
    return sp;
}
#endif
#if defined(__x86_64__) && defined(HOST_CORO_WIN64_TEST)
void host_coro_boot_w64(void);
void *host_coro_prepare_w64(void *stack, size_t size, void (*fn)(void *), void *arg) {
    return prepare_win64(stack, size, fn, arg, host_coro_boot_w64);
}
#endif

#ifdef HOST_ASAN
#include <sanitizer/common_interface_defs.h>

typedef struct AsanStack {
    struct AsanStack *next;
    const char *lo;
    size_t size;
    void (*fn)(void *);
    void *arg;
} AsanStack;
static AsanStack *sAsanStacks;
static const void *sAsanOuterLo;
static size_t sAsanOuterSize;

static void asan_stack_of(const void *sp, const void **lo, size_t *size) {
    for (AsanStack *s = sAsanStacks; s; s = s->next)
        if ((const char *)sp >= s->lo && (const char *)sp < s->lo + s->size) {
            *lo = s->lo;
            *size = s->size;
            return;
        }
    *lo = sAsanOuterLo;
    *size = sAsanOuterSize;
}

static void asan_note_from(const void *lo, size_t size) {
    if (!lo) return;
    for (AsanStack *s = sAsanStacks; s; s = s->next)
        if ((const char *)lo >= s->lo && (const char *)lo < s->lo + s->size) return;
    sAsanOuterLo = lo;
    sAsanOuterSize = size;
}

static void asan_boot(void *arg) {
    AsanStack *s = arg;
    const void *lo;
    size_t size;
    __sanitizer_finish_switch_fiber(0, &lo, &size);
    asan_note_from(lo, size);
    s->fn(s->arg);
}

void host_coro_switch_asan(void **save, void *to) {
    const void *lo, *from_lo;
    size_t size, from_size;
    void *fake = 0;
    asan_stack_of(to, &lo, &size);
    __sanitizer_start_switch_fiber(&fake, lo, size);
    host_coro_switch(save, to);
    __sanitizer_finish_switch_fiber(fake, &from_lo, &from_size);
    asan_note_from(from_lo, from_size);
}

static void *prepare_raw(void *stack, size_t size, void (*fn)(void *), void *arg);
void *host_coro_prepare(void *stack, size_t size, void (*fn)(void *), void *arg) {
    AsanStack *s = calloc(1, sizeof *s);
    if (!s) abort();
    s->lo = stack;
    s->size = size;
    s->fn = fn;
    s->arg = arg;
    s->next = sAsanStacks;
    sAsanStacks = s;
    return prepare_raw(stack, size, asan_boot, s);
}
#define host_coro_prepare prepare_raw
static
#endif
void *host_coro_prepare(void *stack, size_t size, void (*fn)(void *), void *arg) {
#if defined(__x86_64__) && defined(_WIN32)
    return prepare_win64(stack, size, fn, arg, host_coro_boot);
#else
    uintptr_t top = ((uintptr_t)stack + size) & ~(uintptr_t)15;
#if defined(__i386__)
    uint32_t *sp = (uint32_t *)top - 5;
    sp[0] = 0;
    sp[1] = (uint32_t)(uintptr_t)arg;
    sp[2] = (uint32_t)(uintptr_t)fn;
    sp[3] = 0;
    sp[4] = (uint32_t)(uintptr_t)host_coro_boot;
    return sp;
#elif defined(__x86_64__)
    uint64_t *sp = (uint64_t *)top - 7;
    memset(sp, 0, 7 * sizeof *sp);
    sp[2] = (uint64_t)(uintptr_t)arg;
    sp[3] = (uint64_t)(uintptr_t)fn;
    sp[6] = (uint64_t)(uintptr_t)host_coro_boot;
    return sp;
#elif defined(__aarch64__)
    uint64_t *sp = (uint64_t *)top - 22;
    memset(sp, 0, 22 * sizeof *sp);
    sp[0] = (uint64_t)(uintptr_t)fn;
    sp[1] = (uint64_t)(uintptr_t)arg;
    sp[11] = (uint64_t)(uintptr_t)host_coro_boot;
    return sp;
#else
#error "coro.c: no stack switch for this CPU yet"
#endif
#endif
}
