typedef unsigned long size_t;
typedef unsigned char char_map[32];
#define set_char_map(map, ch) map[(unsigned char)(ch) >> 3] |= (unsigned char)(1 << ((ch)&7))
#define tst_char_map(map, ch) (map[(unsigned char)(ch) >> 3] & (unsigned char)(1 << ((ch)&7)))

size_t strspn(const char *str, const char *set) {
    const unsigned char *p;
    unsigned long c;
    char_map map = {0};

    p = (unsigned char *)set;
    while ((c = *p++) != 0) set_char_map(map, c);

    p = (unsigned char *)str;
    while ((c = *p++) != 0)
        if (!tst_char_map(map, c)) break;

    return (p - (unsigned char *)str) - 1;
}
