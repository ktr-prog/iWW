#include "types.h"
#include "proto/autoload_2/unk_02133b68.h"
#include "proto/autoload_2/unk_02133d04.h"

typedef struct ExceptionTableIndex {
    char *function;
    u32 size;
    u8 *data;
} ExceptionTableIndex;

typedef struct ExceptionInfo {
    char *current_function;
    u8 *exception_record;
    u8 *action_pointer;
    char *exception_table_start;
    char *exception_table_end;
    u32 unk14;
} ExceptionInfo;

typedef struct FrameState {
    u32 regs[16];
    char *throwSP;
    u32 frame_size;
    u32 frame_adjust;
    u16 regmask;
    u8 has_fp_area;
    u8 has_fp;
    u8 fp_is_r7;
} FrameState;

typedef struct ThrowContext {
    char *throwtype;
    void *location;
    void *dtor;
    void *catchinfo;
    char *returnaddr;
    char *SP;
    char *FP;
    FrameState state;
} ThrowContext;



extern "C" u32 __PopStackFrame(ThrowContext *context, ExceptionInfo *info) {
    u32 size = context->state.frame_size;
    u32 *p = (u32 *)(context->FP + size - (context->state.has_fp_area ? 16 : 0));
    int i;

    for (i = 15; i >= 0; i--) {
        if (context->state.regmask & (1 << i)) {
            context->state.regs[i] = *--p;
        }
    }
    context->SP = context->FP + size;
    return context->state.regs[14];
}

extern "C" void __SetupFrameInfo(ThrowContext *context, ExceptionInfo *info) {
    u8 *p = info->exception_record;
    u8 flags = p[0];
    u32 has_fp = flags & 0x40;
    u32 fp_is_r7;

    context->state.has_fp = has_fp ? 1 : 0;
    context->state.has_fp_area = (flags & 0x20) ? 1 : 0;
    fp_is_r7 = flags & 0x80;
    context->state.fp_is_r7 = fp_is_r7 ? 1 : 0;
    context->state.regmask = p[1] << 4;
    context->state.regmask |= 0x4000;
    p = __DecodeUnsignedNumber(p + 2, &context->state.frame_size);
    if (has_fp) {
        __DecodeUnsignedNumber(p, &context->state.frame_adjust);
    }
    if (has_fp) {
        if (fp_is_r7) {
            context->FP = (char *)(uptr)context->state.regs[7];
        } else {
            context->FP = (char *)(uptr)context->state.regs[11];
        }
    } else {
        context->FP = context->SP;
    }
}

extern "C" int __FindExceptionTable(ExceptionInfo *info, char *retaddr) {
    info->exception_table_start = NULL;
    info->exception_table_end = NULL;
    return 1;
}

extern "C" u8 *__SkipUnwindInfo(u8 *p) {
    u8 flags = *p;
    u32 value;

    p += 2;
    p = __DecodeUnsignedNumber(p, &value);
    if (flags & 0x40) {
        p = __DecodeUnsignedNumber(p, &value);
    }
    return p;
}
