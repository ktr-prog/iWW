#include "types.h"
#include "host_labels.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/autoload_2/unk_0212703c.h"
#include "proto/autoload_2/unk_02133b68.h"
#include "proto/autoload_2/unk_02133d04.h"
#include "proto/autoload_2/unk_0213510c.h"
#include "sys/std_terminate.h"

#define try if (1)
#define catch(x) else
#define throw

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

#define p__sinit_020c2cd0 HOST_LABEL(VoidFunc (*)[], p__sinit_020c2cd0)

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

DestructorChain *data_0220066c;

VoidFunc data_0213c6b0 = msl::dthandler;

extern "C" void func_021358a8(char *start, char *ptr, size_t size, ObjFunc dtor) {
    try {
        while (ptr > start) {
            ptr -= size;
            dtor(ptr);
        }
    } catch (...) {
        msl::terminate();
    }
}

extern "C" void *__cxa_vec_new(size_t count, size_t size, size_t padding, ObjFunc ctor, ObjFunc dtor) {
    char *block = (char *)Mem_AllocForNew(count * size + padding);
    char *array;
    char *ptr;

    if (block == 0) {
        return 0;
    }
    if (padding) {
        ((size_t *)(block + padding))[-1] = count;
        if (padding >= 8) {
            ((size_t *)(block + padding))[-2] = size;
        }
    }
    if (ctor) {
        array = block + padding;
        ptr = array;
        try {
            for (; count; count--) {
                ctor(ptr);
                ptr += size;
            }
        } catch (...) {
            if (dtor) {
                func_021358a8(array, ptr, size, dtor);
            }
            Mem_FreeForDelete(block);
            throw;
        }
    }
    return block + padding;
}

extern "C" void __cxa_vec_ctor(void *array, size_t count, size_t size, ObjFunc ctor, ObjFunc dtor) {
    char *ptr;

    if (ctor) {
        if (dtor) {
            try {
                ptr = (char *)array;
                for (; count; count--) {
                    ctor(ptr);
                    ptr += size;
                }
            } catch (...) {
                func_021358a8((char *)array, ptr, size, dtor);
                throw;
            }
        } else {
            for (; count; count--) {
                ctor(array);
                array = (char *)array + size;
            }
        }
    }
}

extern "C" void __cxa_vec_dtor(void *array, size_t count, size_t size, ObjFunc dtor) {
    char *ptr;

    if (dtor) {
        ptr = (char *)array + count * size;
        try {
            for (; count; count--) {
                ptr -= size;
                dtor(ptr);
            }
        } catch (...) {
            try {
                while (--count) {
                    ptr -= size;
                    dtor(ptr);
                }
            } catch (...) {
                msl::terminate();
            }
            throw;
        }
    }
}

extern "C" void __cxa_vec_cleanup(void *array, size_t count, size_t size, ObjFunc dtor) {
    char *ptr;

    if (dtor) {
        try {
            ptr = (char *)array + count * size;
            for (; count; count--) {
                ptr -= size;
                dtor(ptr);
            }
        } catch (...) {
            msl::terminate();
        }
    }
}

extern "C" void __cxa_vec_delete(void *array, size_t size, size_t padding, ObjFunc dtor) {
    if (array) {
        if (dtor) {
            __cxa_vec_dtor(array, ((size_t *)array)[-1], size, dtor);
        }
        Mem_FreeForDelete((char *)array - padding);
    }
}

void msl::dthandler() {
    abort();
}

void msl::terminate() {
    data_0213c6b0();
}

extern "C" void *__register_global_object(void *object, void *destructor, void *regmem) {
    ((DestructorChain *)regmem)->next = data_0220066c;
    ((DestructorChain *)regmem)->destructor = destructor;
    ((DestructorChain *)regmem)->object = object;
    data_0220066c = (DestructorChain *)regmem;
    return object;
}

extern "C" int __throw_catch_compare(const char *throwtype, const char *catchtype, s32 *offset_result) {
    const char *cptr1;
    const char *cptr2;

    cptr1 = throwtype;
    cptr2 = catchtype;
    *offset_result = 0;
    if (catchtype == 0) {
        return 1;
    }
    if (*catchtype == 'P') {
        cptr2++;
        if (*cptr2 == 'V') {
            cptr2++;
        }
        if (*cptr2 == 'K') {
            cptr2++;
        }
        if (*cptr2 == 'v') {
            if (*cptr1 == 'P' || *cptr1 == '*') {
                return 1;
            }
        }
        cptr2 = catchtype;
    }
    switch (*(const unsigned char *)throwtype) {
    case '*':
    case '!':
        cptr1++;
        if (*throwtype != *cptr2++) {
            return 0;
        }
        for (;;) {
            if (*cptr1 == *cptr2++) {
                if (*cptr1++ == '!') {
                    s32 offset;

                    for (offset = 0; *cptr1 != '!';) {
                        offset = offset * 10 + *cptr1++ - '0';
                    }
                    *offset_result = offset;
                    return 1;
                }
            } else {
                while (*cptr1++ != '!') {
                }
                while (*cptr1++ != '!') {
                }
                if (*cptr1 == 0) {
                    return 0;
                }
                cptr2 = catchtype + 1;
            }
        }
        return 0;
    }
    while ((*cptr1 == 'P' || *cptr1 == 'R') && *cptr1 == *cptr2) {
        cptr1++;
        cptr2++;
        if (*cptr2 == 'K') {
            if (*cptr1 == 'K') {
                cptr1++;
            }
            cptr2++;
        }
        if (*cptr1 == 'K') {
            return 0;
        }
        if (*cptr2 == 'V') {
            if (*cptr1 == 'V') {
                cptr1++;
            }
            cptr2++;
        }
        if (*cptr1 == 'V') {
            return 0;
        }
    }
    for (; *cptr1 == *cptr2; cptr1++, cptr2++) {
        if (*cptr1 == 0) {
            return 1;
        }
    }
    return 0;
}

extern "C" void __call_static_initializers(void) {
    VoidFunc *ctor;

    for (ctor = p__sinit_020c2cd0; ctor && *ctor; ctor++) {
        (*ctor)();
    }
}

extern "C" void __destroy_global_chain(void) {
    DestructorChain *gdc;

    while ((gdc = data_0220066c) != 0) {
        data_0220066c = gdc->next;
        ((DtorFunc)gdc->destructor)(gdc->object, -1);
    }
}

extern "C" ExceptionTableIndex *BinarySearch(ExceptionTableIndex *table, int count, char *addr) {
    int lo = 0;
    int hi = count - 1;
    int mid;
    ExceptionTableIndex *entry;

    while (lo <= hi) {
        mid = (lo + hi) >> 1;
        entry = &table[mid];
        if (addr < entry->function) {
            hi = mid - 1;
        } else if (addr > entry->function + (entry->size & ~1)) {
            lo = mid + 1;
        } else {
            return entry;
        }
    }
    return 0;
}

extern "C" void FindExceptionRecord(char *retaddr, ExceptionInfo *info) {
    ExceptionTableIndex *entry;
    u8 *p;
    u32 offset;
    u32 pc;
    u32 range[3];

    info->exception_record = 0;
    info->action_pointer = 0;
    if (__FindExceptionTable(info, retaddr) == 0) {
        return;
    }
    entry = BinarySearch((ExceptionTableIndex *)info->exception_table_start,
                          (info->exception_table_end - info->exception_table_start) / 12, retaddr);
    if (entry == 0) {
        return;
    }
    if (entry->size & 1) {
        info->exception_record = (u8 *)&entry->data;
    } else {
        info->exception_record = entry->data;
    }
    info->current_function = entry->function;
    offset = retaddr - entry->function;
    p = __SkipUnwindInfo(info->exception_record);
    pc = 0;
    for (;;) {
        p = __DecodeUnsignedNumber(p, &range[0]);
        if (range[0] == 0) {
            return;
        }
        p = __DecodeUnsignedNumber(p, &range[1]);
        p = __DecodeUnsignedNumber(p, &range[2]);
        pc += range[0];
        if (offset < pc) {
            return;
        }
        pc += range[1];
        if (offset <= pc) {
            break;
        }
    }
    info->action_pointer = info->exception_record + range[2];
}

extern "C" u8 CurrentAction(ActionIterator *iter) {
    return iter->info.action_pointer ? (*iter->info.action_pointer & EXCEPTION_ACTION_MASK) : 0;
}
