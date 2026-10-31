
#include <stdlib.h>

#include "host.h"
#include "host_ptr32.h"

#if __SIZEOF_POINTER__ == 8

static const void **sPtrs;
static u32 sCount, sCap;
static u32 *sHash;
static u32 sHashCap;

static u32 hash_of(const void *p) {
    u64 a = (u64)(uintptr_t)p;
    a ^= a >> 33;
    a *= 0xff51afd7ed558ccdull;
    a ^= a >> 33;
    return (u32)a;
}

static void rehash(u32 cap) {
    free(sHash);
    sHash = calloc(cap, sizeof *sHash);
    if (!sHash) host_fatal("HostPtr32: no memory");
    sHashCap = cap;
    for (u32 i = 0; i < sCount; i++) {
        u32 h = hash_of(sPtrs[i]) & (cap - 1);
        while (sHash[h]) h = (h + 1) & (cap - 1);
        sHash[h] = i + 1;
    }
}

unsigned int HostPtr32_Handle(const void *p) {
    if (sHashCap == 0) rehash(1024);
    u32 h = hash_of(p) & (sHashCap - 1);
    for (; sHash[h]; h = (h + 1) & (sHashCap - 1))
        if (sPtrs[sHash[h] - 1] == p) return HOST_PTR32_HANDLE + sHash[h] - 1;
    if (sCount >= ~HOST_PTR32_HANDLE) host_fatal("HostPtr32: too many pointers");
    if (sCount == sCap) {
        sCap = sCap ? sCap * 2 : 1024;
        sPtrs = realloc(sPtrs, sCap * sizeof *sPtrs);
        if (!sPtrs) host_fatal("HostPtr32: no memory");
    }
    sPtrs[sCount] = p;
    sHash[h] = ++sCount;
    if (sCount * 2 > sHashCap) rehash(sHashCap * 2);
    return HOST_PTR32_HANDLE + sCount - 1;
}

void *HostPtr32_Lookup(unsigned int handle) {
    u32 i = handle - HOST_PTR32_HANDLE;
    if (i >= sCount) host_fatal("HostPtr32: not a handle");
    return (void *)sPtrs[i];
}

unsigned int HostPtr32_Export(const void *const **ptrs) {
    *ptrs = sPtrs;
    return sCount;
}
void HostPtr32_Import(const void *const *ptrs, unsigned int n) {
    sCount = 0;
    if (n > sCap) {
        const void **b = realloc(sPtrs, n * sizeof *sPtrs);
        if (!b) host_fatal("HostPtr32: no memory");
        sPtrs = b, sCap = n;
    }
    for (u32 i = 0; i < n; i++) sPtrs[i] = ptrs[i];
    sCount = n;
    u32 cap = 1024;
    while (cap < 2 * n + 2) cap *= 2;
    rehash(cap);
}
#else
unsigned int HostPtr32_Export(const void *const **ptrs) { *ptrs = 0; return 0; }
void HostPtr32_Import(const void *const *ptrs, unsigned int n) { (void)ptrs; (void)n; }

#endif
