#include "types.h"
#include "proto/autoload_2/unk_02133d04.h"
#include "proto/autoload_2/unk_02134d70.h"
#include "proto/autoload_2/unk_0213510c.h"
#include "sys/std_terminate.h"

typedef struct ExceptionInfo {
    char *current_function;
    u8 *exception_record;
    u8 *action_pointer;
    char *exception_table_start;
    char *exception_table_end;
    u32 unk14;
} ExceptionInfo;

typedef struct CatchInfo CatchInfo;

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

#define EXCEPTION_ACTION_MASK 0x1f
#define GET_LONG(p) ((p)[0] | ((p)[1] << 8) | ((p)[2] << 16) | ((p)[3] << 24))
#define GET_PTR(p) ((uptr)(u32)GET_LONG(p))

extern "C" {
void __SetupFrameInfo(ThrowContext *context, ExceptionInfo *info);
u32 __PopStackFrame(ThrowContext *context, ExceptionInfo *info);
void FindExceptionRecord(char *retaddr, ExceptionInfo *info);
}

inline void Branch(ExceptionInfo *info, ThrowContext *context) {
    s32 target;
    __DecodeSignedNumber(info->action_pointer + 1, &target);
    info->action_pointer += target;
}

extern "C" u8 NextAction(ActionIterator *iter) {
    ExceptionInfo *info = &iter->info;
    ThrowContext *context = &iter->context;
    u8 action;

    for (;;) {
        if (!info->action_pointer || *info->action_pointer & 0x80) {
            FindExceptionRecord((char *)(uptr)__PopStackFrame(context, info), info);
            if (info->exception_record == 0) {
                msl::terminate();
            }
            __SetupFrameInfo(context, info);
            if (info->action_pointer == 0) {
                continue;
            }
            break;
        }
        switch (*info->action_pointer & EXCEPTION_ACTION_MASK) {
        case 2: {
            s32 local;
            info->action_pointer = __DecodeSignedNumber(info->action_pointer + 1, &local) + 4;
            break;
        }
        case 3: {
            s32 cond;
            s32 local;
            info->action_pointer =
                __DecodeSignedNumber(__DecodeSignedNumber(info->action_pointer + 1, &cond), &local) + 4;
            break;
        }
        case 4: {
            s32 pointer;
            info->action_pointer = __DecodeSignedNumber(info->action_pointer + 1, &pointer) + 4;
            break;
        }
        case 5: {
            s32 local;
            u32 count;
            u32 size;
            info->action_pointer =
                __DecodeUnsignedNumber(__DecodeUnsignedNumber(__DecodeSignedNumber(info->action_pointer + 1, &local), &count), &size) + 4;
            break;
        }
        case 6: {
            s32 object;
            s32 offset;
            info->action_pointer =
                __DecodeSignedNumber(__DecodeSignedNumber(info->action_pointer + 1, &object), &offset) + 4;
            break;
        }
        case 7: {
            s32 object;
            s32 offset;
            info->action_pointer =
                __DecodeSignedNumber(__DecodeSignedNumber(info->action_pointer + 1, &object), &offset) + 4;
            break;
        }
        case 8: {
            s32 cond;
            s32 object;
            s32 offset;
            info->action_pointer = __DecodeSignedNumber(
                __DecodeSignedNumber(__DecodeSignedNumber(info->action_pointer + 1, &cond), &object), &offset) + 4;
            break;
        }
        case 9: {
            s32 object;
            s32 offset;
            u32 count;
            u32 size;
            info->action_pointer = __DecodeUnsignedNumber(__DecodeUnsignedNumber(
                __DecodeSignedNumber(__DecodeSignedNumber(info->action_pointer + 1, &object), &offset), &count), &size) + 4;
            break;
        }
        case 10: {
            s32 pointer;
            info->action_pointer = __DecodeSignedNumber(info->action_pointer + 1, &pointer) + 4;
            break;
        }
        case 11: {
            s32 cond;
            s32 pointer;
            info->action_pointer =
                __DecodeSignedNumber(__DecodeSignedNumber(info->action_pointer + 1, &cond), &pointer) + 4;
            break;
        }
        case 12: {
            u32 catch_pcoffset;
            s32 cinfo_ref;
            info->action_pointer =
                __DecodeSignedNumber(__DecodeUnsignedNumber(info->action_pointer + 5, &catch_pcoffset), &cinfo_ref);
            break;
        }
        case 13: {
            s32 cinfo_ref;
            info->action_pointer = __DecodeSignedNumber(info->action_pointer + 1, &cinfo_ref);
            break;
        }
        case 15: {
            u32 specs;
            u32 pcoffset;
            s32 cinfo_ref;
            u8 *p = __DecodeSignedNumber(
                __DecodeUnsignedNumber(__DecodeUnsignedNumber(info->action_pointer + 1, &specs), &pcoffset), &cinfo_ref);
            info->action_pointer = p + specs * 4;
            break;
        }
        case 16: {
            s32 object;
            s32 offset;
            struct {
                s32 offset2;
                u32 base2;
            } s;
            u8 *p = __DecodeSignedNumber(__DecodeSignedNumber(info->action_pointer + 1, &object), &offset);
            s.base2 = GET_LONG(p);
            info->action_pointer = __DecodeSignedNumber(p + 4, &s.offset2) + 4;
            break;
        }
        case 17: {
            s32 object1;
            s32 object2;
            s32 offset1;
            s32 offset2;
            u8 *p = __DecodeSignedNumber(__DecodeSignedNumber(info->action_pointer + 1, &object1), &offset1);
            info->action_pointer = __DecodeSignedNumber(__DecodeSignedNumber(p + 1, &object2), &offset2) + 4;
            break;
        }
        case 18: {
            s32 object;
            s32 bytes;
            u32 size;
            u8 *p = __DecodeSignedNumber(info->action_pointer + 1, &object);
            info->action_pointer = __DecodeUnsignedNumber(__DecodeSignedNumber(p + 1, &bytes), &size) + 4;
            break;
        }
        case 19: {
            s32 offset;
            info->action_pointer = __DecodeSignedNumber(info->action_pointer + 1, &offset);
            break;
        }
        default:
            msl::terminate();
            break;
        }
        break;
    }

    while ((action = *info->action_pointer & EXCEPTION_ACTION_MASK) == 1) {
        Branch(info, context);
    }
    return action;
}
