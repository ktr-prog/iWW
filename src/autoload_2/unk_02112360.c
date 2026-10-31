#include "host_labels.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

typedef struct { void *head, *tail; } ThreadQueue;
void OS_EnableIrqMask(u32 mask);
typedef struct { void *func; u32 enable; void *arg; } IrqCb;
#define data_027e0088 HOST_LABEL(IrqCb (*)[], data_027e0088)

void OS_InitIrqTable(void) {
    extern ThreadQueue data_027e0450;
    ThreadQueue *p = &data_027e0450;
    p->tail = 0;
    p->head = 0;
}

void OSi_EnterTimerCallback(u32 n, void *func, void *arg) {
    data_027e0088[n].func = func;
    data_027e0088[n].arg = arg;
    OS_EnableIrqMask(1 << (n + 3));
    data_027e0088[n].enable = 1;
}

