
#define FILL_WORD unsigned int
#define cpd (*(unsigned char **)&dst)
#define lpd (*(FILL_WORD **)&dst)
#define deref_auto_inc(p) *(p)++
void __fill_mem(void *dst, int val, unsigned long n) {
    unsigned long v = (unsigned char)val;
    unsigned long i;

    if (n >= 32) {
        i = (-(__UINTPTR_TYPE__)dst) & 3;
        if (i) {
            n -= i;
            do
                deref_auto_inc(cpd) = v;
            while (--i);
        }
        if (v) v |= v << 24 | v << 16 | v << 8;

        i = n >> 5;
        if (i)
            do {
                deref_auto_inc(lpd) = v;
                deref_auto_inc(lpd) = v;
                deref_auto_inc(lpd) = v;
                deref_auto_inc(lpd) = v;
                deref_auto_inc(lpd) = v;
                deref_auto_inc(lpd) = v;
                deref_auto_inc(lpd) = v;
                deref_auto_inc(lpd) = v;
            } while (--i);
        i = (n & 31) >> 2;
        if (i)
            do
                deref_auto_inc(lpd) = v;
            while (--i);

        n &= 3;
    }
    if (n)
        do
            deref_auto_inc(cpd) = v;
        while (--n);
    return;
}
