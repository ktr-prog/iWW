#ifndef NITRO_IO_ACCESS_H
#define NITRO_IO_ACCESS_H


#ifdef __cplusplus
extern "C" {
#endif
unsigned long long HostIo_Read(__UINTPTR_TYPE__ addr, unsigned int size);
unsigned long long HostIo_Write(__UINTPTR_TYPE__ addr, unsigned int size, unsigned long long value);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
template <class T> struct IoUnqual_ { typedef T type; };
template <class T> struct IoUnqual_<volatile T> { typedef T type; };
#define IO_T_(p) IoUnqual_<__typeof__(*(p))>::type
#else
#define IO_T_(p) __typeof__(((void)0, *(p)))
#endif
#define IO_ADDR_(p) ((__UINTPTR_TYPE__)(p))
#define IO_R(p) ((IO_T_(p))HostIo_Read(IO_ADDR_(p), sizeof(*(p))))
#define IO_W(p, v) ((IO_T_(p))HostIo_Write(IO_ADDR_(p), sizeof(*(p)), (unsigned long long)(IO_T_(p))(v)))
#define IO_RMW_(p, op, v) IO_W(p, IO_R(p) op (v))
#define IO_OR(p, v) IO_RMW_(p, |, v)
#define IO_AND(p, v) IO_RMW_(p, &, v)
#define IO_XOR(p, v) IO_RMW_(p, ^, v)
#define IO_ADD(p, v) IO_RMW_(p, +, v)
#define IO_SUB(p, v) IO_RMW_(p, -, v)


#endif
