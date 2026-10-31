#ifndef UPTR_H
#define UPTR_H

typedef __UINTPTR_TYPE__ uptr;
typedef __INTPTR_TYPE__ sptr;

#if __SIZEOF_POINTER__ == 8
#define HOST64 1
#define HOST_ALIGN8 __attribute__((aligned(8)))
#else
#define HOST_ALIGN8
#endif

#define HOST_SIZED(n, type) (sizeof(type) > (n) ? sizeof(type) : (n))
#define HOST_AT(p, off, m, rem) ((u8 *)&(p)->m + (rem))
#define HOST_AT_A(a, T, off, m, rem) ((u8 *)&((T *)(a))->m + (rem))

#define VILLAGER_ROUTE_HOST_SIZE 0xa0

#ifdef __cplusplus
extern "C"
#endif
unsigned char *HostActor_Pos(void *actor);
#define ACTOR_POS_AT(p) (HostActor_Pos((void *)(p)))

#endif
