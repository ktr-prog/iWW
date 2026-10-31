#ifndef SYS_PMCBINFO_H
#define SYS_PMCBINFO_H


typedef struct PMCbInfo PMCbInfo;
struct PMCbInfo {
    /* 0x0 */ void (*cb)(void *);
    /* 0x4 */ void *arg;
    /* 0x8 */ PMCbInfo *next;
};

typedef struct PMRegInfo {
    /* 0x0 */ volatile unsigned short flag;
    /* 0x4 */ unsigned short *ptr;
} PMRegInfo;

#endif
