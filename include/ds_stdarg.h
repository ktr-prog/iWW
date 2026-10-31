#ifndef DS_STDARG_H
#define DS_STDARG_H

typedef __builtin_va_list va_list;
#define va_start(ap, parm) __builtin_va_start(ap, parm)
#define va_end(ap) __builtin_va_end(ap)
#define va_arg(ap, t) __builtin_va_arg(ap, t)
#define DS_VA_LIST va_list
#define DS_VA_ARG(ap, T, N) \
    (sizeof(T) < sizeof(int) ? (T)(__UINTPTR_TYPE__)__builtin_va_arg(ap, int) : __builtin_va_arg(ap, T))
#define DS_VA_ARG_C(ap, T, N) DS_VA_ARG(ap, T, N)

#endif
