#ifndef NITRO_MI_GXDMA_H
#define NITRO_MI_GXDMA_H

typedef struct MIGXDmaParams {
    volatile int isBusy;
    unsigned int dmaNo;
    __UINTPTR_TYPE__ src;
    unsigned int length;
    void (*callback)(void *);
    void *arg;
    unsigned int fifoCond;
    void (*fifoFunc)(void);
} MIGXDmaParams;

#endif
