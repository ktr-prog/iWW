
#if !defined(__x86_64__) || defined(_WIN32)
#error "coro_win64_test.c: for x86-64 Linux (it tests the Windows code there)"
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "coro.h"

#define MS __attribute__((ms_abi))

void *host_coro_test_teb;
MS void host_coro_switch_w64(void **save, void *to);
void *host_coro_prepare_w64(void *stack, size_t size, void (*fn)(void *), void *arg);

MS void w64_regcheck(void **save, void *to, uint64_t *out);
MS void w64_clobber(void **save, void *to);
uint64_t w64_pattern[8 + 20];

__asm__(
    ".text\n"
    ".globl w64_regcheck\n"
    "w64_regcheck:\n"
    "  pushq %rbx\n  pushq %rbp\n  pushq %rdi\n  pushq %rsi\n  pushq %r12\n  pushq %r13\n  pushq %r14\n  pushq %r15\n"
    "  subq $216, %rsp\n"
    "  movups %xmm6, 32(%rsp)\n  movups %xmm7, 48(%rsp)\n  movups %xmm8, 64(%rsp)\n  movups %xmm9, 80(%rsp)\n"
    "  movups %xmm10, 96(%rsp)\n  movups %xmm11, 112(%rsp)\n  movups %xmm12, 128(%rsp)\n  movups %xmm13, 144(%rsp)\n"
    "  movups %xmm14, 160(%rsp)\n  movups %xmm15, 176(%rsp)\n"
    "  movq %r8, 192(%rsp)\n"
    "  leaq w64_pattern(%rip), %rax\n"
    "  movq 0(%rax), %rbx\n  movq 8(%rax), %rbp\n  movq 16(%rax), %rdi\n  movq 24(%rax), %rsi\n"
    "  movq 32(%rax), %r12\n  movq 40(%rax), %r13\n  movq 48(%rax), %r14\n  movq 56(%rax), %r15\n"
    "  movups 64(%rax), %xmm6\n  movups 80(%rax), %xmm7\n  movups 96(%rax), %xmm8\n  movups 112(%rax), %xmm9\n"
    "  movups 128(%rax), %xmm10\n  movups 144(%rax), %xmm11\n  movups 160(%rax), %xmm12\n  movups 176(%rax), %xmm13\n"
    "  movups 192(%rax), %xmm14\n  movups 208(%rax), %xmm15\n"
    "  callq host_coro_switch_w64\n"
    "  movq 192(%rsp), %rax\n"
    "  movq %rbx, 0(%rax)\n  movq %rbp, 8(%rax)\n  movq %rdi, 16(%rax)\n  movq %rsi, 24(%rax)\n"
    "  movq %r12, 32(%rax)\n  movq %r13, 40(%rax)\n  movq %r14, 48(%rax)\n  movq %r15, 56(%rax)\n"
    "  movups %xmm6, 64(%rax)\n  movups %xmm7, 80(%rax)\n  movups %xmm8, 96(%rax)\n  movups %xmm9, 112(%rax)\n"
    "  movups %xmm10, 128(%rax)\n  movups %xmm11, 144(%rax)\n  movups %xmm12, 160(%rax)\n  movups %xmm13, 176(%rax)\n"
    "  movups %xmm14, 192(%rax)\n  movups %xmm15, 208(%rax)\n"
    "  movups 32(%rsp), %xmm6\n  movups 48(%rsp), %xmm7\n  movups 64(%rsp), %xmm8\n  movups 80(%rsp), %xmm9\n"
    "  movups 96(%rsp), %xmm10\n  movups 112(%rsp), %xmm11\n  movups 128(%rsp), %xmm12\n  movups 144(%rsp), %xmm13\n"
    "  movups 160(%rsp), %xmm14\n  movups 176(%rsp), %xmm15\n"
    "  addq $216, %rsp\n"
    "  popq %r15\n  popq %r14\n  popq %r13\n  popq %r12\n  popq %rsi\n  popq %rdi\n  popq %rbp\n  popq %rbx\n"
    "  ret\n"
    ".globl w64_clobber\n"
    "w64_clobber:\n"
    "  pushq %rbx\n  pushq %rbp\n  pushq %rdi\n  pushq %rsi\n  pushq %r12\n  pushq %r13\n  pushq %r14\n  pushq %r15\n"
    "  subq $200, %rsp\n"
    "  movups %xmm6, 32(%rsp)\n  movups %xmm7, 48(%rsp)\n  movups %xmm8, 64(%rsp)\n  movups %xmm9, 80(%rsp)\n"
    "  movups %xmm10, 96(%rsp)\n  movups %xmm11, 112(%rsp)\n  movups %xmm12, 128(%rsp)\n  movups %xmm13, 144(%rsp)\n"
    "  movups %xmm14, 160(%rsp)\n  movups %xmm15, 176(%rsp)\n"
    "  movabsq $0xdead0000000000b1, %rbx\n  movabsq $0xdead0000000000b2, %rbp\n  movabsq $0xdead0000000000b3, %rdi\n"
    "  movabsq $0xdead0000000000b4, %rsi\n  movabsq $0xdead0000000000b5, %r12\n  movabsq $0xdead0000000000b6, %r13\n"
    "  movabsq $0xdead0000000000b7, %r14\n  movabsq $0xdead0000000000b8, %r15\n"
    "  pcmpeqd %xmm6, %xmm6\n  pcmpeqd %xmm7, %xmm7\n  pcmpeqd %xmm8, %xmm8\n  pcmpeqd %xmm9, %xmm9\n"
    "  pcmpeqd %xmm10, %xmm10\n  pcmpeqd %xmm11, %xmm11\n  pcmpeqd %xmm12, %xmm12\n  pcmpeqd %xmm13, %xmm13\n"
    "  pcmpeqd %xmm14, %xmm14\n  pcmpeqd %xmm15, %xmm15\n"
    "  callq host_coro_switch_w64\n"
    "  movups 32(%rsp), %xmm6\n  movups 48(%rsp), %xmm7\n  movups 64(%rsp), %xmm8\n  movups 80(%rsp), %xmm9\n"
    "  movups 96(%rsp), %xmm10\n  movups 112(%rsp), %xmm11\n  movups 128(%rsp), %xmm12\n  movups 144(%rsp), %xmm13\n"
    "  movups 160(%rsp), %xmm14\n  movups 176(%rsp), %xmm15\n"
    "  addq $200, %rsp\n"
    "  popq %r15\n  popq %r14\n  popq %r13\n  popq %r12\n  popq %rsi\n  popq %rdi\n  popq %rbp\n  popq %rbx\n"
    "  ret\n");

static unsigned char sTeb[0x1800];
static uint64_t teb(unsigned off) { uint64_t v; memcpy(&v, sTeb + off, 8); return v; }
static void set_teb(unsigned off, uint64_t v) { memcpy(sTeb + off, &v, 8); }

enum { STACK = 64 * 1024, CANARY = 64, ROUNDS = 1000 };
struct Co { unsigned char *mem; void *base, *sp; uintptr_t lo, top; int id; };
static struct Co sA, sB;
static void *sMainSp;
static int sFail;
static long sSteps;

#define CHECK(c, ...) do { if (!(c)) { sFail++; fprintf(stderr, "FAIL: " __VA_ARGS__); fputc('\n', stderr); } } while (0)

static void check_bounds(const struct Co *c, const char *where) {
    CHECK(teb(0x08) == c->top, "%s: StackBase %#llx, want %#llx", where, (unsigned long long)teb(0x08), (unsigned long long)c->top);
    CHECK(teb(0x10) == c->lo, "%s: StackLimit %#llx, want %#llx", where, (unsigned long long)teb(0x10), (unsigned long long)c->lo);
    CHECK(teb(0x1478) == c->lo, "%s: DeallocationStack %#llx", where, (unsigned long long)teb(0x1478));
}

static void use_home_space(uintptr_t fp) {
    for (int i = 0; i < 4; i++) ((volatile uint64_t *)(fp + 16))[i] = 0x5a5a5a5a5a5a5a5aull;
}

static MS __attribute__((noinline)) void co_b(void *arg) {
    struct Co *me = arg;
    uintptr_t fp = (uintptr_t)__builtin_frame_address(0);
    use_home_space(fp);
    CHECK(me == &sB, "B: argument %p", arg);
    CHECK(fp % 16 == 0, "B: stack not aligned at entry (rbp %#lx)", (unsigned long)fp);
    CHECK(fp > me->lo && fp < me->top, "B: not on its stack");
    double acc = 1.0;
    for (;;) {
        check_bounds(me, "B");
        acc = acc * 1.0001 + 0.5;
        w64_clobber(&sB.sp, sA.sp);
        sSteps++;
        CHECK(acc > 1.0, "B: lost its double");
    }
}

static MS __attribute__((noinline)) void co_a(void *arg) {
    struct Co *me = arg;
    uintptr_t fp = (uintptr_t)__builtin_frame_address(0);
    use_home_space(fp);
    CHECK(me == &sA, "A: argument %p", arg);
    CHECK(fp % 16 == 0, "A: stack not aligned at entry (rbp %#lx)", (unsigned long)fp);
    CHECK(fp > me->lo && fp < me->top, "A: not on its stack");
    check_bounds(me, "A start");
    double x = 3.0, y = 0.25;
    void *first = sB.base;
    for (int i = 0; i < ROUNDS; i++) {
        w64_clobber(&sA.sp, i ? sB.sp : first);
        check_bounds(me, "A");
        x = x * 0.999 + y;
    }
    CHECK(x > 0.25 && x < 1000, "A: lost its doubles (%g)", x);
    w64_clobber(&sA.sp, sMainSp);
    CHECK(0, "A resumed after the end");
    abort();
}

static void make(struct Co *c, int id, void (*fn)(void *)) {
    c->mem = malloc(STACK + CANARY);
    memset(c->mem, 0xcc, STACK + CANARY);
    c->id = id;
    c->lo = (uintptr_t)c->mem;
    c->top = ((uintptr_t)c->mem + STACK) & ~(uintptr_t)15;
    c->base = host_coro_prepare_w64(c->mem, STACK, fn, c);
}

int main(void) {
    host_coro_test_teb = sTeb;
    for (int i = 0; i < 8 + 20; i++) w64_pattern[i] = 0x0123456789abcdefull ^ ((uint64_t)(i + 1) * 0x1111111111111111ull);
    set_teb(0x08, 0x7ff000000000ull);
    set_teb(0x10, 0x7fe000000000ull);
    set_teb(0x1478, 0x7fd000000000ull);
    make(&sA, 1, (void (*)(void *))co_a);
    make(&sB, 2, (void (*)(void *))co_b);
    uint64_t out[8 + 20];
    memset(out, 0, sizeof out);
    w64_regcheck(&sMainSp, sA.base, out);
    static const char *names[8] = {"rbx", "rbp", "rdi", "rsi", "r12", "r13", "r14", "r15"};
    for (int i = 0; i < 8; i++)
        CHECK(out[i] == w64_pattern[i], "%s not preserved (%#llx)", names[i], (unsigned long long)out[i]);
    for (int i = 0; i < 10; i++)
        CHECK(out[8 + 2 * i] == w64_pattern[8 + 2 * i] && out[9 + 2 * i] == w64_pattern[9 + 2 * i], "xmm%d not preserved", 6 + i);
    CHECK(teb(0x08) == 0x7ff000000000ull && teb(0x10) == 0x7fe000000000ull && teb(0x1478) == 0x7fd000000000ull,
          "the thread's stack bounds not restored");
    CHECK(sSteps == ROUNDS - 1, "B ran %ld times, want %d", sSteps, ROUNDS - 1);
    struct Co *both[2] = {&sA, &sB};
    for (int k = 0; k < 2; k++)
        for (int i = 0; i < CANARY; i++)
            if (both[k]->mem[STACK + i] != 0xcc) {
                CHECK(0, "coroutine %d wrote above its stack's top (+%d)", both[k]->id, i);
                break;
            }
    if (sFail) { fprintf(stderr, "coro_win64_test: %d failures\n", sFail); return 1; }
    printf("coro_win64_test: OK (%d switches)\n", 2 * ROUNDS + 1);
    return 0;
}
