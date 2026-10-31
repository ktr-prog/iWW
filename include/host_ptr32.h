#ifndef HOST_PTR32_H
#define HOST_PTR32_H

#if __SIZEOF_POINTER__ == 8
#define HOST_PTR32_HANDLE 0xf0000000u
#ifdef __cplusplus
extern "C" {
#endif
unsigned int HostPtr32_Handle(const void *p);
void *HostPtr32_Lookup(unsigned int handle);
unsigned int HostPtr32_Export(const void *const **ptrs);
void HostPtr32_Import(const void *const *ptrs, unsigned int n);
#ifdef __cplusplus
}
#endif
static inline unsigned int HostPtr32_Of(const void *p) {
    __UINTPTR_TYPE__ a = (__UINTPTR_TYPE__)p;
    return a < HOST_PTR32_HANDLE ? (unsigned int)a : HostPtr32_Handle(p);
}
static inline void *HostPtr32_Get(unsigned int v) {
    return v < HOST_PTR32_HANDLE ? (void *)(__UINTPTR_TYPE__)v : HostPtr32_Lookup(v);
}
#else
static inline unsigned int HostPtr32_Of(const void *p) { return (unsigned int)(__UINTPTR_TYPE__)p; }
static inline void *HostPtr32_Get(unsigned int v) { return (void *)(__UINTPTR_TYPE__)v; }
#endif

#endif
