typedef unsigned short u16;
typedef unsigned int u32;
typedef u16 wchar_t;
#define NULL ((void *)0)

u32 wcslen(const wchar_t *s) {
    const wchar_t *p = s;
    u32 len = -1;
    do {
        len++;
    } while (*p++);
    return len;
}

wchar_t *wcscpy(wchar_t *dst, const wchar_t *src) {
    wchar_t *d = dst;
    while ((*d++ = *src++) != 0) {
    }
    return dst;
}

wchar_t *wcschr(const wchar_t *s, wchar_t c) {
    wchar_t ch;
    while ((ch = *s++) != 0) {
        if (ch == c) return (wchar_t *)(s - 1);
    }
    if (c != 0) return NULL;
    return (wchar_t *)(s - 1);
}
