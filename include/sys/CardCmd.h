#ifndef SYS_CARDCMD_H
#define SYS_CARDCMD_H

typedef struct {
    unsigned int result;
    unsigned int command;
    unsigned int f8;
    __UINTPTR_TYPE__ srcBuf;
    __UINTPTR_TYPE__ dstBuf;
    unsigned int len;
    unsigned int f18;
    unsigned int f1c, f20, f24, f28, f2c, f30, f34, f38, f3c;
} CARDCmd;

#endif
