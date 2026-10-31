typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
#include "types64.h"
#include "host_labels.h"

#include "ds_stdarg.h"

#include "sys/OSThread.h"
#include "proto/autoload_2/unk_02114410.h"
#include "proto/autoload_2/unk_02128c60.h"
#include "proto/autoload_2/unk_0212a454.h"
#include "proto/autoload_2/unk_0212b770.h"

typedef struct scan_format {
    u8 suppress_assignment;
    u8 field_width_specified;
    u8 argument_options;
    u8 conversion_char;
    int field_width;
    u8 char_set[32];
} scan_format;

typedef int (*ReadProc)(void *, int, int);

extern u32 data_0213c4fc;
extern scan_format data_0213c500;
extern const u16 data_0213a510[];
#define data_02200324 HOST_LABEL(OSMutex *, data_02200324)
extern u32 data_02200250[];
extern s32 data_02200274[];
extern OSThreadInfo data_021fcc2c;
u32 data_02200650[7];

int OS_TryLockMutex(OSMutex *);
void exit(int);
int mbtowc(u16 *, const char *, u32);
const char *parse_format(const char *format_string, scan_format *format);
u32 __strtoul(int base, int max_width, ReadProc read, void *arg, int *num_chars, int *negative, int *overflow);
float _d2f(double);
int __sformatter(ReadProc read, void *arg, const char *format_str, va_list ap);
int vsscanf(const char *s, const char *fmt, va_list ap);

static inline int isspace_(int c) {
    return (c < 0 || c >= 128) ? 0 : (data_0213a510[c] & 0x100);
}
#define ISSPACE(c) isspace_(c)
#define IS_NUM(c) (((c) < 0 || (c) >= 128) ? 0 : (data_0213a510[c] & 8))

u32 strcspn(const char *str, const char *set) {
    u8 tset[32] = {0};
    const u8 *p;
    u32 c;

    p = (const u8 *)set;
    c = *p++;
    while (c != 0) {
        tset[(u8)c >> 3] |= (u8)(1 << (c & 7));
        c = *p++;
    }
    p = (const u8 *)str;
    c = *p++;
    while (c != 0) {
        if (tset[(u8)c >> 3] & (u8)(1 << (c & 7))) break;
        c = *p++;
    }
    return (u32)(p - (const u8 *)str - 1);
}

char *strstr(const char *str, const char *pat) {
    const u8 *s1 = (const u8 *)str;
    const u8 *p1 = (const u8 *)pat;
    u32 firstc, c1, c2;
    if (pat == 0 || (firstc = *p1++) == 0) return (char *)str;
    while ((c1 = *s1++) != 0) {
        if (c1 == firstc) {
            const u8 *s2 = s1;
            const u8 *p2 = p1;
            while ((c1 = *s2++) == (c2 = *p2++) && c1 != 0) {
            }
            if (c2 == 0) return (char *)(s1 - 1);
        }
    }
    return 0;
}

int raise(int sig) {
    u32 handler;
    OSThread *t;
    if (sig < 1 || sig > 7) return -1;
    if (OS_TryLockMutex(&data_02200324) == 0) {
        data_02200250[7] = data_021fcc2c.list->id;
        data_02200274[7] = 1;
    } else if (data_02200250[7] == (t = data_021fcc2c.list)->id) {
        data_02200274[7]++;
    } else {
        OS_LockMutex(&data_02200324);
        data_02200250[7] = data_021fcc2c.list->id;
        data_02200274[7] = 1;
    }
    handler = data_02200650[sig - 1];
    if (handler != 1) data_02200650[sig - 1] = 0;
    if (--data_02200274[7] == 0) OS_UnlockMutex(&data_02200324);
    if (handler == 1 || (handler == 0 && sig == 1)) return 0;
    if (handler == 0) exit(0);
    ((void (*)(int))(uptr)handler)(sig);
    return 0;
}

const char *parse_format(const char *format_string, scan_format *format) {
    const u8 *s = (const u8 *)format_string;
    int c;
    int flag;
    int i;
    int invert;
    int e;
    u8 *cs;
    int k;
    scan_format f = data_0213c500;

    if ((c = *++s) == '%') {
        f.conversion_char = (u8)c;
        *format = f;
        return (const char *)s + 1;
    }
    if (c == '*') {
        f.suppress_assignment = 1;
        c = *++s;
    }
    if (IS_NUM(c)) {
        f.field_width = 0;
        do {
            f.field_width = f.field_width * 10 + (c - '0');
            c = *++s;
        } while (IS_NUM(c));
        if (f.field_width == 0) {
            f.conversion_char = 0xFF;
            *format = f;
            return (const char *)s + 1;
        }
        f.field_width_specified = 1;
    }
    flag = 1;
    switch (c) {
    case 'h':
        f.argument_options = 2;
        if (s[1] == 'h') {
            f.argument_options = 1;
            c = *++s;
        }
        break;
    case 'l':
        f.argument_options = 3;
        if (s[1] == 'l') {
            f.argument_options = 7;
            c = *++s;
        }
        break;
    case 'L':
        f.argument_options = 9;
        break;
    case 'j':
        f.argument_options = 4;
        break;
    case 'z':
        f.argument_options = 5;
        break;
    case 't':
        f.argument_options = 6;
        break;
    default:
        flag = 0;
        break;
    }
    if (flag) c = *++s;
    f.conversion_char = (u8)c;

    switch (c) {
    case 'd':
    case 'i':
    case 'o':
    case 'u':
    case 'x':
    case 'X':
        if (f.argument_options == 9) f.conversion_char = 0xFF;
        break;
    case 'a':
    case 'A':
    case 'e':
    case 'E':
    case 'f':
    case 'F':
    case 'g':
    case 'G':
        if (f.argument_options == 1 || f.argument_options == 2 || (u8)(f.argument_options + 252) <= 3) {
            f.conversion_char = 0xFF;
        } else if (f.argument_options == 3) {
            f.argument_options = 8;
        }
        break;
    case 'p':
        f.argument_options = 3;
        f.conversion_char = 'x';
        break;
    case 'c':
        if (f.argument_options == 3) {
            f.argument_options = 10;
        } else if (f.argument_options != 0) {
            f.conversion_char = 0xFF;
        }
        break;
    case 'n':
        break;
    case 's':
        if (f.argument_options == 3) {
            f.argument_options = 10;
        } else if (f.argument_options != 0) {
            f.conversion_char = 0xFF;
        }
        cs = f.char_set;
        for (i = 32; i > 0; i--) *cs++ = 0xFF;
        f.char_set[1] = 0xC1;
        f.char_set[4] = 0xFE;
        break;
    case '[':
        if (f.argument_options == 3) {
            f.argument_options = 10;
        } else if (f.argument_options != 0) {
            f.conversion_char = 0xFF;
        }
        c = *++s;
        invert = 0;
        if (c == '^') {
            c = *++s;
            invert = 1;
        }
        if (c == ']') {
            f.char_set[11] |= 0x20;
            c = *++s;
        }
        while (c != 0 && c != ']') {
            f.char_set[(u8)c >> 3] |= 1 << (c & 7);
            if (s[1] == '-' && (e = s[2]) != 0 && e != ']') {
                for (c++; c <= e; c++) f.char_set[(u8)c >> 3] |= 1 << (c & 7);
                c = *(s += 3);
            } else {
                c = *++s;
            }
        }
        if (c == 0) {
            f.conversion_char = 0xFF;
        } else if (invert) {
            cs = f.char_set;
            for (k = 32; k > 0; k--) {
                *cs = ~*cs;
                cs++;
            }
        }
        break;
    default:
        f.conversion_char = 0xFF;
        break;
    }
    *format = f;
    return (const char *)s + 1;
}

int __sformatter(ReadProc read, void *arg, const char *format_str, va_list ap) {
    s32 s;
    s64 sll;
    int items_assigned, conversions;
    int num_chars, chars_read;
    int base, negative, overflow;
    const u8 *format_ptr;
    u8 format_char;
    u8 c;
    scan_format format;
    u32 u;
    u64 ull;
    int r;
    u8 *arg_ptr;

    format_ptr = (const u8 *)format_str;
    chars_read = 0;
    items_assigned = 0;
    conversions = 0;

    while ((format_char = *format_ptr) != 0) {
        if (ISSPACE(format_char)) {
            do {
                format_char = *++format_ptr;
            } while (ISSPACE(format_char));
            while (ISSPACE(c = (*read)(arg, 0, 0))) chars_read++;
            (*read)(arg, c, 1);
            continue;
        }
        if (format_char != '%') {
            c = (*read)(arg, 0, 0);
            if (format_char != c) {
                (*read)(arg, c, 1);
                break;
            }
            chars_read++;
            format_ptr++;
            continue;
        }
        format_ptr = (const u8 *)parse_format((const char *)format_ptr, &format);
        if (!format.suppress_assignment && format.conversion_char != '%') {
            arg_ptr = va_arg(ap, u8 *);
        } else {
            arg_ptr = 0;
        }
        if (format.conversion_char != 'n') {
            if ((*read)(arg, 0, 2)) break;
        }
        switch (format.conversion_char) {
        case 'd':
            base = 10;
            goto signed_int;
        case 'i':
            base = 0;
        signed_int:
            if (format.argument_options == 7) {
                ull = __strtoull(base, format.field_width, read, arg, &num_chars, &negative, &overflow);
            } else {
                u = __strtoul(base, format.field_width, read, arg, &num_chars, &negative, &overflow);
            }
            if (!num_chars) goto end;
            chars_read += num_chars;
            if (format.argument_options == 7) {
                if (!negative) sll = ull;
                else sll = -ull;
            } else {
                if (negative) s = -u;
                else s = u;
            }
            if (arg_ptr) {
                switch (format.argument_options) {
                case 0:
                    *(s32 *)arg_ptr = s;
                    break;
                case 1:
                    *(s8 *)arg_ptr = s;
                    break;
                case 2:
                    *(s16 *)arg_ptr = s;
                    break;
                case 3:
                    *(s32 *)arg_ptr = s;
                    break;
                case 4:
                    *(s64 *)arg_ptr = s;
                    break;
                case 5:
                    *(s32 *)arg_ptr = s;
                    break;
                case 6:
                    *(s32 *)arg_ptr = s;
                    break;
                case 7:
                    *(s64 *)arg_ptr = sll;
                    break;
                }
                items_assigned++;
            }
            conversions++;
            break;
        case 'o':
            base = 8;
            goto unsigned_int;
        case 'u':
            base = 10;
            goto unsigned_int;
        case 'x':
        case 'X':
            base = 16;
        unsigned_int:
            if (format.argument_options == 7) {
                ull = __strtoull(base, format.field_width, read, arg, &num_chars, &negative, &overflow);
            } else {
                u = __strtoul(base, format.field_width, read, arg, &num_chars, &negative, &overflow);
            }
            if (!num_chars) goto end;
            chars_read += num_chars;
            if (negative) {
                if (format.argument_options != 7) u = -u;
                else ull = -ull;
            }
            if (arg_ptr) {
                switch (format.argument_options) {
                case 0:
                    *(u32 *)arg_ptr = u;
                    break;
                case 1:
                    *(u8 *)arg_ptr = u;
                    break;
                case 2:
                    *(u16 *)arg_ptr = u;
                    break;
                case 3:
                    *(u32 *)arg_ptr = u;
                    break;
                case 4:
                    *(u64 *)arg_ptr = u;
                    break;
                case 5:
                    *(u32 *)arg_ptr = u;
                    break;
                case 6:
                    *(u32 *)arg_ptr = u;
                    break;
                case 7:
                    *(u64 *)arg_ptr = ull;
                    break;
                }
                items_assigned++;
            }
            conversions++;
            break;
        case 'a':
        case 'A':
        case 'e':
        case 'E':
        case 'f':
        case 'F':
        case 'g':
        case 'G': {
            double ld = __strtold(format.field_width, read, arg, &num_chars, &overflow);
            if (!num_chars) goto end;
            chars_read += num_chars;
            if (arg_ptr) {
                switch (format.argument_options) {
                case 0:
                    *(float *)arg_ptr = (float)ld;
                    break;
                case 8:
                    *(double *)arg_ptr = ld;
                    break;
                case 9:
                    *(double *)arg_ptr = ld;
                    break;
                }
                items_assigned++;
            }
            conversions++;
            break;
        }
        case 'c':
            if (!format.field_width_specified) format.field_width = 1;
            if (arg_ptr) {
                num_chars = 0;
                while (format.field_width-- && (r = (*read)(arg, 0, 0)) != -1) {
                    c = r;
                    if (format.argument_options != 10) {
                        *arg_ptr++ = c;
                    } else {
                        mbtowc((u16 *)arg_ptr, (const char *)&c, 1);
                        arg_ptr++;
                    }
                    num_chars++;
                }
                c = r;
                if (!num_chars) goto end;
                chars_read += num_chars;
                items_assigned++;
            } else {
                num_chars = 0;
                while (format.field_width-- && (r = (*read)(arg, 0, 0)) != -1) {
                    c = r;
                    num_chars++;
                }
                c = r;
                if (!num_chars) goto end;
            }
            conversions++;
            break;
        case '%':
            while (ISSPACE(c = (*read)(arg, 0, 0))) chars_read++;
            if (c != '%') {
                (*read)(arg, c, 1);
                goto end;
            }
            chars_read++;
            break;
        case 's': {
            c = (*read)(arg, 0, 0);
            while (ISSPACE(c)) {
                chars_read++;
                c = (*read)(arg, 0, 0);
            }
            (*read)(arg, c, 1);
        }
        case '[': {
            if (arg_ptr) {
                num_chars = 0;
                while (format.field_width-- && (r = (*read)(arg, 0, 0)) != -1) {
                    c = r;
                    if (!(format.char_set[c >> 3] & (1 << (c & 7)))) break;
                    if (format.argument_options != 10) {
                        *arg_ptr++ = c;
                    } else {
                        mbtowc((u16 *)arg_ptr, (const char *)&c, 1);
                        arg_ptr += 2;
                    }
                    num_chars++;
                }
                c = r;
                if (!num_chars) {
                    (*read)(arg, c, 1);
                    goto end;
                }
                chars_read += num_chars;
                if (format.argument_options == 10) *(u16 *)arg_ptr = 0;
                else *arg_ptr = 0;
                items_assigned++;
            } else {
                num_chars = 0;
                while (format.field_width-- && (r = (*read)(arg, 0, 0)) != -1) {
                    c = r;
                    if (!(format.char_set[c >> 3] & (1 << (c & 7)))) break;
                    num_chars++;
                }
                c = r;
                if (!num_chars) {
                    (*read)(arg, c, 1);
                    continue;
                }
                chars_read += num_chars;
            }
            if (format.field_width >= 0) (*read)(arg, c, 1);
            conversions++;
            break;
        }
        case 'n':
            if (arg_ptr) {
                switch (format.argument_options) {
                case 0:
                    *(s32 *)arg_ptr = chars_read;
                    break;
                case 2:
                    *(s16 *)arg_ptr = chars_read;
                    break;
                case 3:
                    *(s32 *)arg_ptr = chars_read;
                    break;
                case 1:
                    *(s8 *)arg_ptr = chars_read;
                    break;
                case 7:
                    *(s64 *)arg_ptr = chars_read;
                    break;
                }
            }
            break;
        case 0xFF:
            goto end;
        default:
            goto end;
        }
    }
end:
    if ((*read)(arg, 0, 2)) {
        if (conversions == 0) return -1;
    }
    return items_assigned;
}

int __StringRead(void *ctx, int ch, int action) {
    struct { const u8 *cur; int flag; } *c = ctx;
    switch (action) {
    case 0: {
        u8 b = *c->cur;
        if (b == 0) {
            c->flag = 1;
            return -1;
        }
        c->cur++;
        return b;
    }
    case 1:
        if (c->flag == 0) {
            c->cur--;
        } else {
            c->flag = 0;
        }
        return ch;
    case 2:
        return c->flag;
    }
    return 0;
}

int vsscanf(const char *s, const char *fmt, va_list ap) {
    struct { const char *cur; int flag; } ctx;
    ctx.cur = s;
    if (s == 0 || *(u8 *)s == 0) return -1;
    ctx.flag = 0;
    return __sformatter(__StringRead, &ctx, fmt, ap);
}

int sscanf(const char *s, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    return vsscanf(s, fmt, ap);
}

int rand(void) {
    data_0213c4fc = data_0213c4fc * 0x41c64e6d + 0x3039;
    return (data_0213c4fc >> 16) & 0x7fff;
}

void srand(u32 seed) {
    data_0213c4fc = seed;
}

u32 data_0213c4fc = 1;
scan_format data_0213c500 = {0, 0, 0, 0, 0x7fffffff};
