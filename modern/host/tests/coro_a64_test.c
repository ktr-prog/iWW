
#if !defined(__aarch64__)
#error "coro_a64_test.c: for arm64"
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "coro.h"

void a64_regcheck(void **save, void *to, uint64_t *out);
void a64_clobber(void **save, void *to);
uint64_t a64_pattern[11 + 8];

#define SAVE_ALL \
    "  stp x29, x30, [sp, #-176]!\n  mov x29, sp\n" \
    "  stp x19, x20, [sp, #16]\n  stp x21, x22, [sp, #32]\n  stp x23, x24, [sp, #48]\n  stp x25, x26, [sp, #64]\n" \
    "  stp x27, x28, [sp, #80]\n  stp d8, d9, [sp, #96]\n  stp d10, d11, [sp, #112]\n  stp d12, d13, [sp, #128]\n" \
    "  stp d14, d15, [sp, #144]\n"
#define RESTORE_ALL \
    "  ldp x19, x20, [sp, #16]\n  ldp x21, x22, [sp, #32]\n  ldp x23, x24, [sp, #48]\n  ldp x25, x26, [sp, #64]\n" \
    "  ldp x27, x28, [sp, #80]\n  ldp d8, d9, [sp, #96]\n  ldp d10, d11, [sp, #112]\n  ldp d12, d13, [sp, #128]\n" \
    "  ldp d14, d15, [sp, #144]\n  ldp x29, x30, [sp], #176\n"

__asm__(
    ".text\n"
    ".globl a64_regcheck\n"
    "a64_regcheck:\n"
    SAVE_ALL
    "  str x2, [sp, #160]\n"
    "  adrp x9, a64_pattern\n  add x9, x9, :lo12:a64_pattern\n"
    "  ldp x19, x20, [x9, #0]\n  ldp x21, x22, [x9, #16]\n  ldp x23, x24, [x9, #32]\n  ldp x25, x26, [x9, #48]\n"
    "  ldp x27, x28, [x9, #64]\n  ldr x29, [x9, #80]\n"
    "  ldp d8, d9, [x9, #88]\n  ldp d10, d11, [x9, #104]\n  ldp d12, d13, [x9, #120]\n  ldp d14, d15, [x9, #136]\n"
    "  bl host_coro_switch\n"
    "  ldr x9, [sp, #160]\n"
    "  stp x19, x20, [x9, #0]\n  stp x21, x22, [x9, #16]\n  stp x23, x24, [x9, #32]\n  stp x25, x26, [x9, #48]\n"
    "  stp x27, x28, [x9, #64]\n  str x29, [x9, #80]\n"
    "  stp d8, d9, [x9, #88]\n  stp d10, d11, [x9, #104]\n  stp d12, d13, [x9, #120]\n  stp d14, d15, [x9, #136]\n"
    RESTORE_ALL
    "  ret\n"
    ".globl a64_clobber\n"
    "a64_clobber:\n"
    SAVE_ALL
    "  mov x19, #0xb1\n  mov x20, #0xb2\n  mov x21, #0xb3\n  mov x22, #0xb4\n  mov x23, #0xb5\n  mov x24, #0xb6\n"
    "  mov x25, #0xb7\n  mov x26, #0xb8\n  mov x27, #0xb9\n  mov x28, #0xba\n  mov x29, #0xbb\n"
    "  movi d8, #0xffffffffffffffff\n  movi d9, #0xffffffffffffffff\n  movi d10, #0xffffffffffffffff\n"
    "  movi d11, #0xffffffffffffffff\n  movi d12, #0xffffffffffffffff\n  movi d13, #0xffffffffffffffff\n"
    "  movi d14, #0xffffffffffffffff\n  movi d15, #0xffffffffffffffff\n"
    "  bl host_coro_switch\n"
    RESTORE_ALL
    "  ret\n");

enum { STACK = 64 * 1024, CANARY = 64, ROUNDS = 1000 };
struct Co { unsigned char *mem; void *base, *sp; uintptr_t lo, top; int id; };
static struct Co sA, sB;
static void *sMainSp;
static int sFail;
static long sSteps;

#define CHECK(c, ...) do { if (!(c)) { sFail++; fprintf(stderr, "FAIL: " __VA_ARGS__); fputc('\n', stderr); } } while (0)

static __attribute__((noinline)) void co_b(void *arg) {
    struct Co *me = arg;
    uintptr_t fp = (uintptr_t)__builtin_frame_address(0);
    CHECK(me == &sB, "B: argument %p", arg);
    CHECK(fp % 16 == 0, "B: stack not aligned (fp %#lx)", (unsigned long)fp);
    CHECK(fp > me->lo && fp < me->top, "B: not on its stack");
    double acc = 1.0;
    for (;;) {
        acc = acc * 1.0001 + 0.5;
        a64_clobber(&sB.sp, sA.sp);
        sSteps++;
        CHECK(acc > 1.0, "B: lost its double");
    }
}

static __attribute__((noinline)) void co_a(void *arg) {
    struct Co *me = arg;
    uintptr_t fp = (uintptr_t)__builtin_frame_address(0);
    CHECK(me == &sA, "A: argument %p", arg);
    CHECK(fp % 16 == 0, "A: stack not aligned (fp %#lx)", (unsigned long)fp);
    CHECK(fp > me->lo && fp < me->top, "A: not on its stack");
    double x = 3.0, y = 0.25;
    void *first = sB.base;
    for (int i = 0; i < ROUNDS; i++) {
        a64_clobber(&sA.sp, i ? sB.sp : first);
        x = x * 0.999 + y;
    }
    CHECK(x > 0.25 && x < 1000, "A: lost its doubles (%g)", x);
    a64_clobber(&sA.sp, sMainSp);
    CHECK(0, "A resumed after the end");
    abort();
}

static void make(struct Co *c, int id, void (*fn)(void *)) {
    c->mem = malloc(STACK + CANARY);
    memset(c->mem, 0xcc, STACK + CANARY);
    c->id = id;
    c->lo = (uintptr_t)c->mem;
    c->top = ((uintptr_t)c->mem + STACK) & ~(uintptr_t)15;
    c->base = host_coro_prepare(c->mem, STACK, fn, c);
}

int main(void) {
    for (int i = 0; i < 11 + 8; i++) a64_pattern[i] = 0x0123456789abcdefull ^ ((uint64_t)(i + 1) * 0x1111111111111111ull);
    make(&sA, 1, co_a);
    make(&sB, 2, co_b);
    uint64_t out[11 + 8];
    memset(out, 0, sizeof out);
    a64_regcheck(&sMainSp, sA.base, out);
    for (int i = 0; i < 11; i++)
        CHECK(out[i] == a64_pattern[i], "x%d not preserved (%#llx)", 19 + i, (unsigned long long)out[i]);
    for (int i = 0; i < 8; i++)
        CHECK(out[11 + i] == a64_pattern[11 + i], "d%d not preserved (%#llx)", 8 + i, (unsigned long long)out[11 + i]);
    CHECK(sSteps == ROUNDS - 1, "B ran %ld times, want %d", sSteps, ROUNDS - 1);
    struct Co *both[2] = {&sA, &sB};
    for (int k = 0; k < 2; k++)
        for (int i = 0; i < CANARY; i++)
            if (both[k]->mem[STACK + i] != 0xcc) {
                CHECK(0, "coroutine %d wrote above its stack's top (+%d)", both[k]->id, i);
                break;
            }
    if (sFail) { fprintf(stderr, "coro_a64_test: %d failures\n", sFail); return 1; }
    printf("coro_a64_test: OK (%d switches)\n", 2 * ROUNDS + 1);
    return 0;
}
