#include "ds_div.h"
#include "types.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/autoload_2/unk_0212703c.h"
#include "proto/autoload_2/unk_02133b68.h"
#include "proto/autoload_2/unk_02133d04.h"
#include "proto/autoload_2/unk_0213510c.h"
#include "sys/std_terminate.h"

typedef void (*VoidFunc)(void);
typedef void (*DtorFunc)(void *, int);
typedef void (*ObjFunc)(void *);
typedef void (*PairFunc)(void *, void *);

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

typedef struct CatchInfo {
    void *location;
    void *typeinfo;
    void *dtor;
    void *sublocation;
    s32 pointercopy;
    void *stacktop;
} CatchInfo;

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
    CatchInfo *catchinfo;
    char *returnaddr;
    char *SP;
    char *FP;
    FrameState state;
} ThrowContext;

typedef struct ActionIterator {
    ExceptionInfo info;
    ThrowContext context;
} ActionIterator;

typedef struct DestructorChain {
    struct DestructorChain *next;
    void *destructor;
    void *object;
} DestructorChain;

typedef struct ExCatchBlock {
    char *catch_type;
    u32 catch_pcoffset;
    s32 cinfo_ref;
} ExCatchBlock;

typedef struct ExSpecification {
    u32 specs;
    u32 pcoffset;
    s32 cinfo_ref;
    u8 *spec;
} ExSpecification;

#define EXCEPTION_ACTION_MASK 0x1f
#define GET_LONG(p) ((p)[0] | ((p)[1] << 8) | ((p)[2] << 16) | ((p)[3] << 24))
#define GET_PTR(p) ((uptr)(u32)GET_LONG(p))

extern VoidFunc p__sinit_020c2cd0[];
extern DestructorChain *data_0220066c;
extern VoidFunc data_0213c6b0;

extern "C" {
void sys_writec(const u8 *p);
int sys_readc(void);
int __FindExceptionTable(ExceptionInfo *info, char *retaddr);
void __SetupFrameInfo(ThrowContext *context, ExceptionInfo *info);
u32 __PopStackFrame(ThrowContext *context, ExceptionInfo *info);
void __TransferControl(ThrowContext *context, ExceptionInfo *info, char *pc);
void __cxa_vec_dtor(void *array, size_t count, size_t size, ObjFunc dtor);
void func_021358a8(char *start, char *ptr, size_t size, ObjFunc dtor);
u8 NextAction(ActionIterator *iter);
u8 CurrentAction(ActionIterator *iter);
void FindExceptionRecord(char *retaddr, ExceptionInfo *info);
ExceptionTableIndex *BinarySearch(ExceptionTableIndex *table, int count, char *addr);
void UnwindStack(ThrowContext *context, ExceptionInfo *info, u8 *catcher);
CatchInfo *FindMostRecentException(ThrowContext *context, ExceptionInfo *info);
int IsInSpecification(const char *throwtype, ExSpecification *spec);
void HandleUnexpected(ThrowContext *context, ExceptionInfo *info, ExSpecification *spec, u8 *unexp);
u8 *FindExceptionHandler(ThrowContext *context, ExceptionInfo *info, s32 *result_offset);
void SetupCatchInfo(ThrowContext *context, s32 cinfo_ref, s32 offset);
}

#define FRAME_VALUE(context, flag, off) ((flag) ? (context)->state.regs[off] : *(u32 *)((context)->FP + (off)))

extern "C" void UnwindStack(ThrowContext *context, ExceptionInfo *info, u8 *catcher) {
    u8 *p;
    u8 *next;
    u8 action;

#pragma exception_terminate
    for (;;) {
        if (info->action_pointer == 0) {
            FindExceptionRecord((char *)(uptr)__PopStackFrame(context, info), info);
            if (info->exception_record == 0) {
                msl::terminate();
            }
            __SetupFrameInfo(context, info);
            if (info->action_pointer == 0) {
                continue;
            }
        }
        p = info->action_pointer;
        action = *p;
        switch (action & EXCEPTION_ACTION_MASK) {
        case 1: {
            s32 offset;
            __DecodeSignedNumber(p + 1, &offset);
            info->action_pointer += offset;
            break;
        }
        case 2: {
            s32 local;
            p = __DecodeSignedNumber(p + 1, &local);
            ((DtorFunc)GET_PTR(p))(context->FP + local, -1);
            info->action_pointer = p + 4;
            break;
        }
        case 3: {
            u32 inreg = *info->action_pointer & 0x40;
            s32 cond;
            s32 local;
            DtorFunc dtor;
            p = __DecodeSignedNumber(__DecodeSignedNumber(p + 1, &cond), &local);
            dtor = (DtorFunc)GET_PTR(p);
            next = p + 4;
            if (inreg ? (u8)context->state.regs[cond] : *(u8 *)(context->FP + cond)) {
                dtor(context->FP + local, -1);
            }
            info->action_pointer = next;
            break;
        }
        case 4: {
            u32 inreg = *info->action_pointer & 0x20;
            s32 pointer;
            DtorFunc dtor;
            p = __DecodeSignedNumber(p + 1, &pointer);
            dtor = (DtorFunc)GET_PTR(p);
            next = p + 4;
            dtor((void *)(uptr)FRAME_VALUE(context, inreg, pointer), -1);
            info->action_pointer = next;
            break;
        }
        case 5: {
            s32 local;
            u32 count;
            u32 size;
            DtorFunc dtor;
            u32 n;
            char *ptr;
            p = __DecodeUnsignedNumber(__DecodeUnsignedNumber(__DecodeSignedNumber(p + 1, &local), &count), &size);
            dtor = (DtorFunc)GET_PTR(p);
            next = p + 4;
            ptr = context->FP + local;
            n = count;
            for (ptr += n * size; n; n--) {
                ptr -= size;
                dtor(ptr, -1);
            }
            info->action_pointer = next;
            break;
        }
        case 6: {
            u32 inreg = *info->action_pointer & 0x20;
            s32 object;
            s32 offset;
            DtorFunc dtor;
            p = __DecodeSignedNumber(__DecodeSignedNumber(p + 1, &object), &offset);
            dtor = (DtorFunc)GET_PTR(p);
            next = p + 4;
            dtor((char *)(uptr)FRAME_VALUE(context, inreg, object) + offset, 0);
            info->action_pointer = next;
            break;
        }
        case 7: {
            u32 inreg = *info->action_pointer & 0x20;
            s32 object;
            s32 offset;
            DtorFunc dtor;
            p = __DecodeSignedNumber(__DecodeSignedNumber(p + 1, &object), &offset);
            dtor = (DtorFunc)GET_PTR(p);
            next = p + 4;
            dtor((char *)(uptr)FRAME_VALUE(context, inreg, object) + offset, -1);
            info->action_pointer = next;
            break;
        }
        case 8: {
            u32 inreg = *info->action_pointer & 0x20;
            s32 cond;
            s32 object;
            s32 offset;
            DtorFunc dtor;
            p = __DecodeSignedNumber(__DecodeSignedNumber(__DecodeSignedNumber(p + 1, &cond), &object), &offset);
            dtor = (DtorFunc)GET_PTR(p);
            next = p + 4;
            if ((action & 0x40) ? (s16)context->state.regs[cond] : *(s16 *)(context->FP + cond)) {
                dtor((char *)(uptr)FRAME_VALUE(context, inreg, object) + offset, -1);
            }
            info->action_pointer = next;
            break;
        }
        case 9: {
            u32 inreg = *info->action_pointer & 0x20;
            s32 object;
            s32 offset;
            u32 count;
            u32 size;
            DtorFunc dtor;
            u32 n;
            char *ptr;
            p = __DecodeUnsignedNumber(__DecodeUnsignedNumber(__DecodeSignedNumber(__DecodeSignedNumber(p + 1, &object), &offset), &count), &size);
            dtor = (DtorFunc)GET_PTR(p);
            next = p + 4;
            if (inreg) {
                ptr = (char *)(uptr)context->state.regs[object] + offset;
            } else {
                ptr = (char *)(uptr)*(u32 *)(context->FP + object) + offset;
            }
            n = count;
            for (ptr += n * size; n; n--) {
                ptr -= size;
                dtor(ptr, -1);
            }
            info->action_pointer = next;
            break;
        }
        case 10: {
            u32 inreg = *info->action_pointer & 0x20;
            s32 pointer;
            ObjFunc del;
            p = __DecodeSignedNumber(p + 1, &pointer);
            del = (ObjFunc)GET_PTR(p);
            next = p + 4;
            del((void *)(uptr)FRAME_VALUE(context, inreg, pointer));
            info->action_pointer = next;
            break;
        }
        case 11: {
            u32 inreg = *info->action_pointer & 0x20;
            s32 cond;
            s32 pointer;
            ObjFunc del;
            p = __DecodeSignedNumber(__DecodeSignedNumber(p + 1, &cond), &pointer);
            del = (ObjFunc)GET_PTR(p);
            next = p + 4;
            if ((action & 0x40) ? (u8)context->state.regs[cond] : *(u8 *)(context->FP + cond)) {
                del((void *)(uptr)FRAME_VALUE(context, inreg, pointer));
            }
            info->action_pointer = next;
            break;
        }
        case 12: {
            u32 catch_pcoffset;
            s32 cinfo_ref;
            if (catcher == p) {
                return;
            }
            info->action_pointer = __DecodeSignedNumber(__DecodeUnsignedNumber(p + 5, &catch_pcoffset), &cinfo_ref);
            break;
        }
        case 13: {
            s32 cinfo_ref;
            CatchInfo *ci;
            p = __DecodeSignedNumber(p + 1, &cinfo_ref);
            ci = (CatchInfo *)(context->FP + cinfo_ref);
            if (ci->dtor) {
                if (context->location == ci->location) {
                    context->dtor = ci->dtor;
                } else {
                    ((DtorFunc)ci->dtor)(ci->location, -1);
                }
            }
            info->action_pointer = p;
            break;
        }
        case 15: {
            u32 specs;
            u32 pcoffset;
            s32 cinfo_ref;
            if (catcher == p) {
                return;
            }
            p = __DecodeSignedNumber(__DecodeUnsignedNumber(__DecodeUnsignedNumber(p + 1, &specs), &pcoffset), &cinfo_ref);
            info->action_pointer = p + specs * 4;
            break;
        }
        case 16: {
            u32 inreg = *info->action_pointer & 0x20;
            s32 object;
            s32 offset;
            struct {
                s32 offset2;
                u32 base2;
            } s;
            PairFunc func;
            p = __DecodeSignedNumber(__DecodeSignedNumber(p + 1, &object), &offset);
            s.base2 = GET_LONG(p);
            p = __DecodeSignedNumber(p + 4, &s.offset2);
            func = (PairFunc)GET_PTR(p);
            next = p + 4;
            func((char *)(uptr)FRAME_VALUE(context, inreg, object) + offset, (char *)(uptr)s.base2 + s.offset2);
            info->action_pointer = next;
            break;
        }
        case 17: {
            u32 inreg = *info->action_pointer & 0x20;
            u32 inreg2;
            s32 object1;
            s32 object2;
            s32 offset1;
            s32 offset2;
            PairFunc func;
            p = __DecodeSignedNumber(__DecodeSignedNumber(p + 1, &object1), &offset1);
            inreg2 = *p++ & 0x20;
            p = __DecodeSignedNumber(__DecodeSignedNumber(p, &object2), &offset2);
            func = (PairFunc)GET_PTR(p);
            next = p + 4;
            {
                u32 v1 = FRAME_VALUE(context, inreg, object1);
                u32 v2 = FRAME_VALUE(context, inreg2, object2);
                func((char *)(uptr)v1 + offset1, (char *)(uptr)v2 + offset2);
            }
            info->action_pointer = next;
            break;
        }
        case 18: {
            u32 inreg = *info->action_pointer & 0x20;
            u32 inreg2;
            s32 object;
            s32 bytes;
            u32 size;
            DtorFunc dtor;
            u32 n;
            char *ptr;
            u32 total;
            p = __DecodeSignedNumber(p + 1, &object);
            inreg2 = *p++ & 0x20;
            p = __DecodeUnsignedNumber(__DecodeSignedNumber(p, &bytes), &size);
            dtor = (DtorFunc)GET_PTR(p);
            next = p + 4;
            if (inreg) {
                ptr = (char *)(uptr)context->state.regs[object];
            } else {
                ptr = *(char **)(context->FP + object);
            }
            if (inreg2) {
                total = context->state.regs[bytes];
            } else {
                total = *(u32 *)(context->FP + bytes);
            }
            ptr += total;
            for (n = DS_UDIV(total, size); n; n--) {
                ptr -= size;
                dtor(ptr, -1);
            }
            info->action_pointer = next;
            break;
        }
        case 19: {
            s32 offset;
            info->action_pointer = __DecodeSignedNumber(p + 1, &offset);
            break;
        }
        default:
            msl::terminate();
            break;
        }
        if (action & 0x80) {
            info->action_pointer = 0;
        }
    }
}

extern "C" CatchInfo *FindMostRecentException(ThrowContext *context, ExceptionInfo *info) {
    s32 cinfo_ref;
    ActionIterator iter;
    CatchInfo *catchinfo;
    u8 action;

    iter.info = *info;
    iter.context = *context;
    for (action = CurrentAction(&iter);; action = NextAction(&iter)) {
        switch (action) {
        case 13:
            break;
        case 0:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 15:
        case 16:
        case 17:
        case 18:
            continue;
        case 1:
        case 14:
        default:
            msl::terminate();
            break;
        }
        break;
    }
    __DecodeSignedNumber(iter.info.action_pointer + 1, &cinfo_ref);
    catchinfo = (CatchInfo *)(iter.context.FP + cinfo_ref);
    context->throwtype = (char *)catchinfo->typeinfo;
    context->location = catchinfo->location;
    context->dtor = 0;
    context->catchinfo = catchinfo;
    return catchinfo;
}

extern "C" int IsInSpecification(const char *throwtype, ExSpecification *spec) {
    struct {
        char *catch_type;
        s32 offset;
    } s;
    u8 *p = spec->spec;
    u32 i;

    for (i = 0; i < spec->specs; i++) {
        s.catch_type = (char *)GET_PTR(p);
        if (__throw_catch_compare(throwtype, s.catch_type, &s.offset)) {
            return 1;
        }
        p += 4;
    }
    return 0;
}

extern "C" void HandleUnexpected(ThrowContext *context, ExceptionInfo *info, ExSpecification *spec, u8 *unexp) {
    CatchInfo *catchinfo;

#pragma exception_terminate
    UnwindStack(context, info, unexp);
    catchinfo = (CatchInfo *)(context->FP + spec->cinfo_ref);
    catchinfo->location = context->location;
    catchinfo->typeinfo = context->throwtype;
    catchinfo->dtor = context->dtor;
    catchinfo->stacktop = unexp;
    __TransferControl(context, info, info->current_function + spec->pcoffset);
}

extern "C" u8 *FindExceptionHandler(ThrowContext *context, ExceptionInfo *info, s32 *result_offset) {
    ExCatchBlock catchblock;
    ExSpecification spec;
    ActionIterator iter;
    u8 action;

    iter.info = *info;
    iter.context = *context;
    for (action = CurrentAction(&iter);; action = NextAction(&iter)) {
        switch (action) {
        case 12:
            catchblock.catch_type = (char *)GET_PTR(iter.info.action_pointer + 1);
            __DecodeSignedNumber(__DecodeUnsignedNumber(iter.info.action_pointer + 5, &catchblock.catch_pcoffset),
                          &catchblock.cinfo_ref);
            if (!__throw_catch_compare(context->throwtype, catchblock.catch_type, result_offset)) {
                continue;
            }
            break;
        case 15:
            spec.spec = __DecodeSignedNumber(
                __DecodeUnsignedNumber(__DecodeUnsignedNumber(iter.info.action_pointer + 1, &spec.specs), &spec.pcoffset),
                &spec.cinfo_ref);
            if (IsInSpecification(context->throwtype, &spec) == 0) {
                HandleUnexpected(context, info, &spec, iter.info.action_pointer);
            }
            continue;
        case 0:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 13:
        case 16:
        case 17:
        case 18:
        case 19:
            continue;
        case 1:
        case 14:
        default:
            msl::terminate();
            break;
        }
        break;
    }
    return iter.info.action_pointer;
}

extern "C" void SetupCatchInfo(ThrowContext *context, s32 cinfo_ref, s32 offset) {
    CatchInfo *catchinfo = (CatchInfo *)(context->FP + cinfo_ref);

    catchinfo->location = context->location;
    catchinfo->typeinfo = context->throwtype;
    catchinfo->dtor = context->dtor;
    if (*context->throwtype == '*') {
        catchinfo->sublocation = &catchinfo->pointercopy;
        catchinfo->pointercopy = *(s32 *)context->location + offset;
    } else {
        catchinfo->sublocation = (char *)context->location + offset;
    }
}

extern "C" void __ThrowHandler(ThrowContext *context) {
    s32 offset;
    ExceptionInfo info;
    ExCatchBlock catchblock;
    u8 *p;

    FindExceptionRecord(context->returnaddr, &info);
    if (info.exception_record == 0) {
        msl::terminate();
    }
    __SetupFrameInfo(context, &info);
    if (context->throwtype == 0) {
        context->catchinfo = FindMostRecentException(context, &info);
    } else {
        context->catchinfo = 0;
    }
    p = FindExceptionHandler(context, &info, &offset);
    catchblock.catch_type = (char *)GET_PTR(p + 1);
    __DecodeSignedNumber(__DecodeUnsignedNumber(p + 5, &catchblock.catch_pcoffset), &catchblock.cinfo_ref);
    UnwindStack(context, &info, p);
    SetupCatchInfo(context, catchblock.cinfo_ref, offset);
    __TransferControl(context, &info, info.current_function + catchblock.catch_pcoffset);
}

extern "C" void __end__catch(CatchInfo *catchinfo) {
    if (catchinfo->location && catchinfo->dtor) {
        ((DtorFunc)catchinfo->dtor)(catchinfo->location, -1);
    }
}

extern "C" void *func_02133ef8(void *ptr, size_t size) {
    u8 *p = (u8 *)ptr;

    if (ptr && size) {
        do {
            *p++ = 0;
        } while (--size);
    }
    return ptr;
}

extern "C" u8 *__DecodeSignedNumber(u8 *p, s32 *value) {
    s32 b0 = (s8)p[0];
    s32 b1;
    s32 b2;

    if (!(b0 & 1)) {
        *value = b0 >> 1;
        return p + 1;
    }
    b1 = p[1];
    if (!(b0 & 2)) {
        *value = ((b0 >> 2) << 8) | b1;
        return p + 2;
    }
    b2 = p[2];
    if (!(b0 & 4)) {
        *value = ((b0 >> 3) << 16) | (b1 << 8) | b2;
        return p + 3;
    }
    *value = ((b0 >> 3) << 24) | (b1 << 16) | (b2 << 8) | p[3];
    return p + 4;
}

extern "C" u8 *__DecodeUnsignedNumber(u8 *p, u32 *value) {
    u32 b0 = p[0];
    u32 b1;
    u32 b2;

    if (!(b0 & 1)) {
        *value = b0 >> 1;
        return p + 1;
    }
    b1 = p[1];
    if (!(b0 & 2)) {
        *value = ((b0 >> 2) << 8) | b1;
        return p + 2;
    }
    b2 = p[2];
    if (!(b0 & 4)) {
        *value = ((b0 >> 3) << 16) | (b1 << 8) | b2;
        return p + 3;
    }
    *value = ((b0 >> 3) << 24) | (b1 << 16) | (b2 << 8) | p[3];
    return p + 4;
}

extern "C" int __read_console(u32 handle, u8 *buffer, size_t *count, void *idle_proc) {
    size_t i;
    size_t n = *count;

    for (i = 0; i < n; i++) {
        buffer[i] = sys_readc();
        if (buffer[i] == '\r' || buffer[i] == '\n') {
            *count = i + 1;
            break;
        }
    }
    return 0;
}

extern "C" int __write_console(u32 handle, u8 *buffer, size_t *count, void *idle_proc) {
    size_t i;
    size_t n = *count;

    for (i = 0; i < n; i++) {
        sys_writec(buffer + i);
    }
    return 0;
}

extern "C" int __close_console(u32 handle) {
    return 0;
}
