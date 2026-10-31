#ifndef TYPES_H
#define TYPES_H

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
#include "types64.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;

#include "uptr.h"

typedef __SIZE_TYPE__ size_t;

#undef __declspec
#define __declspec(x) __attribute__((x))
#define __builtin__clear(p, n) __builtin_memset((p), 0, (n))

#define MODERN_EMIT __attribute__((used))

#define MODERN_VOLATILE volatile

#if defined(MODERN) && defined(__cplusplus)
struct MwccLayoutEmpty {};
struct MwccLayout {
protected:
    [[no_unique_address]] MwccLayoutEmpty empty_;
};
#define MWCC_LAYOUT [[no_unique_address]] MwccLayout mwccLayout_;
#define MWCC_TAIL [[no_unique_address]]
#else
#define MWCC_LAYOUT
#define MWCC_TAIL
#endif

typedef int BOOL;
#define TRUE 1
#define FALSE 0

#ifndef NULL
#define NULL 0
#endif

#ifdef __cplusplus
#include "sys/new.h"
#endif

#endif
