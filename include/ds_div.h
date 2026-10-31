#ifndef DS_DIV_H
#define DS_DIV_H


#ifdef __cplusplus
extern "C++" {
#endif

static inline int DS_DIV(int a, int b) { return b == 0 ? a : b == -1 ? (int)(0u - (unsigned int)a) : a / b; }
static inline int DS_MOD(int a, int b) { return b == 0 || b == -1 ? 0 : a % b; }
static inline unsigned int DS_UDIV(unsigned int a, unsigned int b) { return b == 0 ? a : a / b; }
static inline unsigned int DS_UMOD(unsigned int a, unsigned int b) { return b == 0 ? 0 : a % b; }

static inline long long DS_DIV64(long long a, long long b) {
    return b == 0 ? a : b == -1 ? (long long)(0ull - (unsigned long long)a) : a / b;
}
static inline long long DS_MOD64(long long a, long long b) { return b == 0 ? a : b == -1 ? 0 : a % b; }
static inline unsigned long long DS_UDIV64(unsigned long long a, unsigned long long b) { return b == 0 ? a : a / b; }
static inline unsigned long long DS_UMOD64(unsigned long long a, unsigned long long b) { return b == 0 ? a : a % b; }

#ifdef __cplusplus
}
#endif

#endif
