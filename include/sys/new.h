#ifndef SYS_NEW_H
#define SYS_NEW_H

#include "types.h"

inline void *operator new(size_t, void *p) { return p; }
inline void *operator new[](size_t, void *p) { return p; }

extern "C" void *Mem_AllocForNew(u32 size);
struct GameHeapNew {};
static const GameHeapNew kGameHeap = {};
inline void *operator new(size_t size, GameHeapNew) throw() { return Mem_AllocForNew(size); }
inline void *operator new[](size_t size, GameHeapNew) throw() { return Mem_AllocForNew(size); }

#endif
