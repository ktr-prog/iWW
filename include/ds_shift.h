#ifndef DS_SHIFT_H
#define DS_SHIFT_H


#ifdef __cplusplus
extern "C++" {
#endif

static inline int DS_ASR(int v, unsigned int n) {
    n &= 0xff;
    return n >= 32 ? (v < 0 ? -1 : 0) : v >> n;
}
static inline unsigned int DS_LSR(unsigned int v, unsigned int n) {
    n &= 0xff;
    return n >= 32 ? 0 : v >> n;
}
static inline unsigned int DS_LSL(unsigned int v, unsigned int n) {
    n &= 0xff;
    return n >= 32 ? 0 : v << n;
}

#ifdef __cplusplus
}
#endif

#endif
