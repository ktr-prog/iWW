#include "proto/dtcm/unk_027e0000.h"
#include "proto/itcm/unk_01ff8000.h"
#include "proto/itcm/unk_01ff8228.h"
#pragma define_section DTCM ".dtcm" abs32 RWX

typedef unsigned int u32;
typedef void (*OSIrqFunction)(void);

typedef struct OSIrqCallbackInfo {
    void (*func)(void *);
    u32 enable;
    void *arg;
} OSIrqCallbackInfo;


#pragma section DTCM begin

OSIrqFunction data_027e0000[22] = {
    OS_IrqDummy,
    OS_IrqDummy,
    OS_IrqDummy,
    OSi_IrqTimer0,
    OSi_IrqTimer1,
    OSi_IrqTimer2,
    OSi_IrqTimer3,
    OS_IrqDummy,
    OSi_IrqDma0,
    OSi_IrqDma1,
    OSi_IrqDma2,
    OSi_IrqDma3,
    OS_IrqDummy,
    OS_IrqDummy,
    OS_IrqDummy,
    OS_IrqDummy,
    OS_IrqDummy,
    OS_IrqDummy,
    OS_IrqDummy,
    OS_IrqDummy,
    OS_IrqDummy,
    OS_IrqDummy,
};

OSIrqCallbackInfo data_027e0058[8];

#pragma section DTCM end

#include "host_labels.h"

HOST_LABEL_DEFINE(data_027e0088, (char *)&data_027e0058[4].func);
