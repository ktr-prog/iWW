#include "proto/autoload_2/unk_0212ef04.h"
typedef unsigned int u32;
typedef int s32;

extern double __ieee754_pow(double, double);

static inline int __fpclassifyd(double x) {
    switch (*(1 + (s32 *)&x) & 0x7ff00000) {
    case 0x7ff00000:
        if ((*(1 + (s32 *)&x) & 0x000fffff) || *(s32 *)&x) return 1;
        return 2;
    case 0:
        if ((*(1 + (s32 *)&x) & 0x000fffff) || *(s32 *)&x) return 5;
        return 3;
    default:
        return 4;
    }
}

double pow(double x, double y) {
    return __ieee754_pow(x, y);
}

double ldexp(double x, int n) {
    static const double two54 = 1.80143985094819840000e+16;
    static const double twom54 = 5.55111512312578270212e-17;
    static const double huge = 1.0e+300;
    static const double tiny = 1.0e-300;
    s32 k, hx, lx;
    if (__fpclassifyd(x) <= 2 || x == 0.0) return x;
    hx = *(1 + (s32 *)&x);
    lx = *(s32 *)&x;
    k = (hx & 0x7ff00000) >> 20;
    if (k == 0) {
        if ((lx | (hx & 0x7fffffff)) == 0) return x;
        x *= two54;
        hx = *(1 + (s32 *)&x);
        k = ((hx & 0x7ff00000) >> 20) - 54;
        if (n < -50000) return tiny * x;
    }
    if (k == 0x7ff) return x + x;
    k = k + n;
    if (k > 0x7fe) return huge * copysign(huge, x);
    if (k > 0) {
        *(1 + (s32 *)&x) = (hx & 0x800fffff) | (k << 20);
        return x;
    }
    if (k <= -54) {
        if (n > 50000) return huge * copysign(huge, x);
        else return tiny * copysign(tiny, x);
    }
    k += 54;
    *(1 + (s32 *)&x) = (hx & 0x800fffff) | (k << 20);
    return x * twom54;
}

double frexp(double x, int *eptr) {
    static const double two54 = 1.80143985094819840000e+16;
    s32 hx, ix, lx;
    hx = *(1 + (s32 *)&x);
    ix = 0x7fffffff & hx;
    lx = *(s32 *)&x;
    *eptr = 0;
    if (ix >= 0x7ff00000 || ((ix | lx) == 0)) return x;
    if (ix < 0x00100000) {
        x *= two54;
        hx = *(1 + (s32 *)&x);
        ix = hx & 0x7fffffff;
        *eptr = -54;
    }
    *eptr += (ix >> 20) - 1022;
    hx = (hx & 0x800fffff) | 0x3fe00000;
    *(1 + (s32 *)&x) = hx;
    return x;
}

double fabs(double x) {
    *(1 + (s32 *)&x) &= 0x7fffffff;
    return x;
}

double copysign(double x, double y) {
    *(1 + (s32 *)&x) = (*(1 + (s32 *)&x) & 0x7fffffff) | (*(1 + (s32 *)&y) & 0x80000000);
    return x;
}
