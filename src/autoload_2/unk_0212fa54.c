typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;
#include "types64.h"
#include "proto/autoload_2/unk_0212ef04.h"
#include "proto/autoload_2/unk_0212fa54.h"
typedef struct {
    u8 sign;
    char unused;
    short exp;
    struct {
        u8 length;
        u8 text[32];
        u8 unused;
    } sig;
} decimal;
typedef struct {
    short style;
    short digits;
} decform;

extern u8 data_0213a410[];
extern int __must_round(const decimal *, int);
extern void __dorounddecup(decimal *, int);
extern void __rounddec(decimal *, int);
extern void __ull2dec(decimal *, u64);
extern void __timesdec(decimal *, const decimal *, const decimal *);
extern void __str2dec(decimal *, const u8 *, short);
extern void __two_exp(decimal *, int);
extern int __count_trailing_zeros(u32);
extern int __equals_dec(const decimal *, const decimal *);
extern int __less_dec(const decimal *, const decimal *);
extern void __minus_dec(decimal *, const decimal *, const decimal *);
extern void __num2dec_internal(decimal *, double);

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

int stricmp(const char *s1, const char *s2) {
    u8 c1, c2;
    int t;
    do {
        t = (u8)*s1++;
        c1 = (t < 0 || t >= 128) ? t : data_0213a410[t];
        t = (u8)*s2++;
        c2 = (t < 0 || t >= 128) ? t : data_0213a410[t];
        if (c1 < c2) return -1;
        if (c1 > c2) return 1;
    } while (c1 != 0);
    return 0;
}

int func_02130b04(const char *s1, const char *s2) {
    return stricmp(s1, s2);
}

int __count_trailing_zeros(u32 x) {
    u8 *p;
    int n;
    if (x != 0) {
        p = (u8 *)&x;
        n = 0;
        while (*p == 0) {
            p++;
            n += 8;
        }
        *p = ~*p;
        while (*p & 1) {
            n++;
            *p >>= 1;
        }
        return n;
    }
    return 32;
}

int __must_round(const decimal *d, int digits) {
    const u8 *p, *q;
    q = d->sig.text + digits;
    p = d->sig.text;
    if (*q > 5) return 1;
    if (*q < 5) return -1;
    p += d->sig.length;
    for (q++; q < p; q++)
        if (*q != 0) return 1;
    if (d->sig.text[digits - 1] & 1) return 1;
    return -1;
}

void __dorounddecup(decimal *d, int digits) {
    u8 *t = d->sig.text;
    u8 *p = t + digits;
    p--;
    for (;;) {
        if (*p < 9) {
            (*p)++;
            return;
        }
        if (p == t) {
            *p = 1;
            d->exp++;
            return;
        }
        *p-- = 0;
    }
}

void __rounddec(decimal *d, int digits) {
    int rv;
    if (digits <= 0) return;
    if (digits >= d->sig.length) return;
    rv = __must_round(d, digits);
    d->sig.length = digits;
    if (rv < 0) return;
    __dorounddecup(d, digits);
}

void __ull2dec(decimal *d, u64 v) {
    u8 *a, *b;
    d->sign = 0;
    d->sig.length = 0;
    while (v != 0) {
        d->sig.text[d->sig.length++] = (u8)(v % 10);
        v /= 10;
    }
    a = d->sig.text;
    b = a + d->sig.length - 1;
    for (; a < b; a++, b--) {
        u8 t = *a;
        *a = *b;
        *b = t;
    }
    d->exp = d->sig.length - 1;
}

void __timesdec(decimal *result, const decimal *x, const decimal *y) {
    u32 accum = 0;
    u8 buf[64];
    int i;
    u8 *p, *end;
    int j, k, n;
    const u8 *xp, *yp;
    i = x->sig.length + y->sig.length - 1;
    p = buf + i + 1;
    end = p;
    result->sign = 0;
    for (; i > 0; i--) {
        int yl = y->sig.length;
        int xl = x->sig.length;
        int yi = yl - 1;
        int xs = i - yi - 1;
        if (xs < 0) {
            xs = 0;
            yi = i - 1;
        }
        xp = x->sig.text + xs;
        n = xl - xs;
        yp = y->sig.text + yi;
        k = yi + 1;
        if (k > n) k = n;
        if (k > 0) {
            do {
                accum += *xp * *yp;
                --k;
                xp++;
                yp--;
            } while (k > 0);
        }
        *--p = (u8)(accum % 10);
        accum /= 10;
    }
    result->exp = x->exp + y->exp;
    if (accum != 0) {
        *--p = (u8)accum;
        result->exp++;
    }
    for (j = 0; j < 32 && p < end; p++) result->sig.text[j++] = *p;
    result->sig.length = j;
    if (p >= end) return;
    if (*p < 5) return;
    if (*p == 5) {
        const u8 *q = p + 1;
        while (q < end) {
            if (*q != 0) goto up;
            q++;
        }
        if ((p[-1] & 1) == 0) return;
    }
up:
    __dorounddecup(result, result->sig.length);
}

void __str2dec(decimal *d, const u8 *s, short exp) {
    int i;
    d->exp = exp;
    d->sign = 0;
    for (i = 0; i < 32 && *s;) d->sig.text[i++] = *s++ - '0';
    d->sig.length = i;
    if (*s == 0) return;
    if (*s < 5) return;
    if (*s <= 5) {
        const u8 *p = s + 1;
        while (*p) {
            if (*p != '0') goto up;
            p++;
        }
        if ((d->sig.text[i - 1] & 1) == 0) return;
    }
up:
    __dorounddecup(d, d->sig.length);
}

void __two_exp(decimal *result, int exp) {
    decimal temp, temp2;
    switch (exp) {
    case -64: __str2dec(result, (u8 *)"542101086242752217003726400434970855712890625", -20); break;
    case -53: __str2dec(result, (u8 *)"11102230246251565404236316680908203125", -16); break;
    case -32: __str2dec(result, (u8 *)"23283064365386962890625", -10); break;
    case -16: __str2dec(result, (u8 *)"152587890625", -5); break;
    case -8: __str2dec(result, (u8 *)"390625", -3); break;
    case -7: __str2dec(result, (u8 *)"78125", -3); break;
    case -6: __str2dec(result, (u8 *)"15625", -2); break;
    case -5: __str2dec(result, (u8 *)"3125", -2); break;
    case -4: __str2dec(result, (u8 *)"625", -2); break;
    case -3: __str2dec(result, (u8 *)"125", -1); break;
    case -2: __str2dec(result, (u8 *)"25", -1); break;
    case -1: __str2dec(result, (u8 *)"5", -1); break;
    case 0: __str2dec(result, (u8 *)"1", 0); break;
    case 1: __str2dec(result, (u8 *)"2", 0); break;
    case 2: __str2dec(result, (u8 *)"4", 0); break;
    case 3: __str2dec(result, (u8 *)"8", 0); break;
    case 4: __str2dec(result, (u8 *)"16", 1); break;
    case 5: __str2dec(result, (u8 *)"32", 1); break;
    case 6: __str2dec(result, (u8 *)"64", 1); break;
    case 7: __str2dec(result, (u8 *)"128", 2); break;
    case 8: __str2dec(result, (u8 *)"256", 2); break;
    default:
        __two_exp(&temp, (s32)(exp + ((exp & 0x80000000) >> 31)) >> 1);
        __timesdec(result, &temp, &temp);
        if (exp & 1) {
            temp2 = *result;
            if (exp > 0)
                __str2dec(&temp, (u8 *)"2", 0);
            else
                __str2dec(&temp, (u8 *)"5", -1);
            __timesdec(result, &temp2, &temp);
        }
        break;
    }
}

int __equals_dec(const decimal *x, const decimal *y) {
    int i, length;
    if (x->sig.text[0] == 0) return y->sig.text[0] == 0;
    if (y->sig.text[0] == 0) return x->sig.text[0] == 0;
    if (x->exp == y->exp) {
        length = x->sig.length;
        if (length > y->sig.length) length = y->sig.length;
        for (i = 0; i < length; i++)
            if (x->sig.text[i] != y->sig.text[i]) return 0;
        if (length == x->sig.length) x = y;
        for (; i < x->sig.length; i++)
            if (x->sig.text[i] != 0) return 0;
        return 1;
    }
    return 0;
}

int __less_dec(const decimal *x, const decimal *y) {
    int i, length;
    if (x->sig.text[0] == 0) return y->sig.text[0] != 0;
    if (y->sig.text[0] == 0) return 0;
    if (x->exp == y->exp) {
        length = x->sig.length;
        if (length > y->sig.length) length = y->sig.length;
        for (i = 0; i < length; i++) {
            if (x->sig.text[i] < y->sig.text[i]) return 1;
            if (y->sig.text[i] < x->sig.text[i]) return 0;
        }
        if (length == x->sig.length)
            for (; i < y->sig.length; i++)
                if (y->sig.text[i] != 0) return 1;
        return 0;
    }
    return x->exp < y->exp;
}

void __minus_dec(decimal *z, const decimal *x, const decimal *y) {
    int zdigits, diff, n, round;
    u8 *zt, *zp, *yt, *yp, *q, *p;
    *z = *x;
    if (y->sig.text[0] == 0) return;
    zdigits = z->sig.length;
    if (zdigits < y->sig.length) zdigits = y->sig.length;
    diff = z->exp - y->exp;
    zdigits += diff;
    if (zdigits > 32) zdigits = 32;
    while (z->sig.length < zdigits) z->sig.text[z->sig.length++] = 0;
    zt = z->sig.text;
    zp = zt + zdigits;
    n = y->sig.length + diff;
    if (n < zdigits) zp = zt + n;
    yt = (u8 *)y->sig.text;
    yp = yt + ((zp - zt) - diff);
    q = yp;
    while (zp > zt && yp > yt) {
        zp--;
        yp--;
        if (*zp < *yp) {
            p = zp - 1;
            if (*p == 0) {
                do {
                    p--;
                } while (*p == 0);
            }
            if (p != zp) {
                do {
                    (*p)--;
                    p++;
                    *p += 10;
                } while (p != zp);
            }
        }
        *zp -= *yp;
    }
    n = q - yt;
    if (n < y->sig.length) {
        round = 0;
        if (*q < 5) {
            round = 1;
        } else if (*q == 5) {
            p = (u8 *)y->sig.text + y->sig.length;
            q++;
            while (q < p) {
                if (*q != 0) goto done;
                q++;
            }
            zp = zt + n + diff - 1;
            if (*zp & 1) round = 1;
        }
        if (round) {
            if (*zp < 1) {
                p = zp - 1;
                if (*p == 0) {
                    do {
                        p--;
                    } while (*p == 0);
                }
                if (p != zp) {
                    do {
                        (*p)--;
                        p++;
                        *p += 10;
                    } while (p != zp);
                }
            }
            (*zp)--;
        }
    }
done:
    {
        u8 *e;
        u8 *s = zt;
        u8 k;
        if (*s == 0) {
            do {
                s++;
            } while (*s == 0);
        }
        if (s > zt) {
            k = (u8)(s - zt);
            z->exp -= k;
            e = zt + z->sig.length;
            if (s < e) {
                do {
                    *zt++ = *s++;
                } while (s < e);
            }
            z->sig.length -= k;
        }
    }
    zt = z->sig.text;
    p = zt + z->sig.length;
    while (p > zt) {
        if (*--p != 0) break;
    }
    z->sig.length = (p - zt) + 1;
}

static inline int __cnt(double x) {
    u32 *p = (u32 *)&x;
    if (p[0]) return __count_trailing_zeros(p[0]);
    return __count_trailing_zeros(p[1] | 0x100000) + 32;
}

void __num2dec_internal(decimal *d, double x) {
    int exp;
    u8 sign = (u8)((*(1 + (s32 *)&x) & 0x80000000) != 0);
    if (x == 0.0) {
        d->sign = sign;
        d->exp = 0;
        d->sig.length = 1;
        d->sig.text[0] = 0;
        return;
    }
    if (__fpclassifyd(x) <= 2) {
        d->sign = sign;
        d->exp = 0;
        d->sig.length = 1;
        d->sig.text[0] = (__fpclassifyd(x) == 1) ? 'N' : 'I';
        return;
    }
    {
        double frac;
        int bits;
        unsigned long long ull;
        decimal int_d, pow2_d;
        if (sign) x = -x;
        frac = frexp(x, &exp);
        bits = __cnt(frac);
        bits = 53 - bits;
        __two_exp(&pow2_d, exp - bits);
        ull = (unsigned long long)ldexp(frac, bits);
        __ull2dec(&int_d, ull);
        __timesdec(d, &int_d, &pow2_d);
        d->sign = sign;
    }
}

void __num2dec(const decform *f, double x, decimal *d) {
    short digits = f->digits;
    int i;
    __num2dec_internal(d, x);
    if (d->sig.text[0] > 9) return;
    if (digits > 32) digits = 32;
    __rounddec(d, digits);
    while (d->sig.length < digits) d->sig.text[d->sig.length++] = 0;
    d->exp -= d->sig.length - 1;
    for (i = 0; i < d->sig.length; i++) d->sig.text[i] += '0';
}
