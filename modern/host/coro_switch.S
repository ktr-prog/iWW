
#if defined(__APPLE__)
#define SYM(x) _##x
#else
#define SYM(x) x
#endif

    .text

#if defined(__i386__)

    .globl SYM(host_coro_switch)
SYM(host_coro_switch):
    movl 4(%esp), %eax
    movl 8(%esp), %edx
    pushl %ebp
    pushl %ebx
    pushl %esi
    pushl %edi
    movl %esp, (%eax)
    movl %edx, %esp
    popl %edi
    popl %esi
    popl %ebx
    popl %ebp
    ret

    .globl SYM(host_coro_boot)
SYM(host_coro_boot):
    subl $12, %esp
    pushl %esi
    call *%ebx
    ud2

#elif defined(__x86_64__) && !defined(_WIN32)

    .globl SYM(host_coro_switch)
SYM(host_coro_switch):
    pushq %rbp
    pushq %rbx
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15
    movq %rsp, (%rdi)
    movq %rsi, %rsp
    popq %r15
    popq %r14
    popq %r13
    popq %r12
    popq %rbx
    popq %rbp
    ret

    .globl SYM(host_coro_boot)
SYM(host_coro_boot):
    movq %r13, %rdi
    callq *%r12
    ud2

#elif defined(__aarch64__)

    .globl SYM(host_coro_switch)
SYM(host_coro_switch):
    sub sp, sp, #176
    stp x19, x20, [sp, #0]
    stp x21, x22, [sp, #16]
    stp x23, x24, [sp, #32]
    stp x25, x26, [sp, #48]
    stp x27, x28, [sp, #64]
    stp x29, x30, [sp, #80]
    stp d8, d9, [sp, #96]
    stp d10, d11, [sp, #112]
    stp d12, d13, [sp, #128]
    stp d14, d15, [sp, #144]
    mov x9, sp
    str x9, [x0]
    mov sp, x1
    ldp x19, x20, [sp, #0]
    ldp x21, x22, [sp, #16]
    ldp x23, x24, [sp, #32]
    ldp x25, x26, [sp, #48]
    ldp x27, x28, [sp, #64]
    ldp x29, x30, [sp, #80]
    ldp d8, d9, [sp, #96]
    ldp d10, d11, [sp, #112]
    ldp d12, d13, [sp, #128]
    ldp d14, d15, [sp, #144]
    add sp, sp, #176
    ret

    .globl SYM(host_coro_boot)
SYM(host_coro_boot):
    mov x0, x20
    blr x19
    brk #0

#elif !(defined(__x86_64__) && defined(_WIN32))
#error "coro_switch.S: no stack switch for this CPU yet"
#endif

#if (defined(__x86_64__) && defined(_WIN32)) || (defined(__x86_64__) && defined(HOST_CORO_WIN64_TEST))

#if defined(_WIN32)
#define W64(x) x
#define LOAD_TEB(r) movq %gs:0x30, r   /* NT_TIB.Self: the TIB's linear address */
#else
#define W64(x) x##_w64
#define LOAD_TEB(r) movq host_coro_test_teb(%rip), r
#endif

    .globl W64(host_coro_switch)
W64(host_coro_switch):
    pushq %rbp
    pushq %rbx
    pushq %rsi
    pushq %rdi
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15
    subq $184, %rsp
    movaps %xmm6, 0(%rsp)
    movaps %xmm7, 16(%rsp)
    movaps %xmm8, 32(%rsp)
    movaps %xmm9, 48(%rsp)
    movaps %xmm10, 64(%rsp)
    movaps %xmm11, 80(%rsp)
    movaps %xmm12, 96(%rsp)
    movaps %xmm13, 112(%rsp)
    movaps %xmm14, 128(%rsp)
    movaps %xmm15, 144(%rsp)
    LOAD_TEB(%r10)
    movq 0x10(%r10), %rax
    movq %rax, 160(%rsp)
    movq 0x08(%r10), %rax
    movq %rax, 168(%rsp)
    movq 0x1478(%r10), %rax
    movq %rax, 176(%rsp)
    movq %rsp, (%rcx)
    movq %rdx, %rsp
    movq 160(%rsp), %rax
    movq %rax, 0x10(%r10)
    movq 168(%rsp), %rax
    movq %rax, 0x08(%r10)
    movq 176(%rsp), %rax
    movq %rax, 0x1478(%r10)
    movaps 0(%rsp), %xmm6
    movaps 16(%rsp), %xmm7
    movaps 32(%rsp), %xmm8
    movaps 48(%rsp), %xmm9
    movaps 64(%rsp), %xmm10
    movaps 80(%rsp), %xmm11
    movaps 96(%rsp), %xmm12
    movaps 112(%rsp), %xmm13
    movaps 128(%rsp), %xmm14
    movaps 144(%rsp), %xmm15
    addq $184, %rsp
    popq %r15
    popq %r14
    popq %r13
    popq %r12
    popq %rdi
    popq %rsi
    popq %rbx
    popq %rbp
    ret

    .globl W64(host_coro_boot)
W64(host_coro_boot):
    subq $32, %rsp
    movq %r13, %rcx
    callq *%r12
    ud2

#endif

#if defined(__linux__) && defined(__ELF__)
    .section .note.GNU-stack, "", @progbits
#endif
