typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef int BOOL;
typedef u16 wchar_t;
#include "ds_div.h"
#include "types64.h"
#define NULL ((void *)0)
#include "ds_stdarg.h"
#include "proto/autoload_2/unk_0212c11c.h"

/* MSL C FILE (layout recovered from the code, see S020a) */
typedef struct {
    u32 open_mode : 2;
    u32 io_mode : 3;
    u32 buffer_mode : 2;
    u32 file_kind : 3;
    u32 file_orientation : 2;
    u32 binary_io : 1;
} file_modes;
typedef struct {
    u32 io_state : 3;
    u32 free_buffer : 1;
} file_state;
typedef struct _FILE {
    u32 handle;
    file_modes mode;
    file_state state;
    u8 eof;
    u8 error;
    u8 pad0e[4];
    u8 ungetc_buffer[2];
    u16 ungetc_wide_buffer[2];
    u32 position;
    u8 *buffer;
    u32 buffer_size;
    u8 *buffer_ptr;
    u32 buffer_len;
    u32 buffer_alignment;
    u32 save_buffer_len;
    u32 buffer_pos;
    int (*position_proc)();
    int (*read_proc)(u32 handle, u8 *buf, u32 *count, void *ref);
    int (*write_proc)(u32 handle, u8 *buf, u32 *count, void *ref);
    int (*close_proc)();
    void *ref_con;
} FILE;

typedef struct {
    u8 justification_options;
    u8 sign_options;
    u8 precision_specified;
    u8 alternate_form;
    u8 argument_options;
    wchar_t conversion_char;
    s32 field_width;
    s32 precision;
} print_format;

enum { left_justification, right_justification, zero_fill };
enum { only_minus, sign_always, space_holder };
enum { normal_argument, char_argument, short_argument, long_argument, long_long_argument, long_double_argument, wchar_argument };

typedef struct {
    wchar_t *CharStr;
    u32 MaxCharCount;
    u32 CharsWritten;
} __wOutStr;

extern void *memcpy(void *, const void *, u32);
extern void *memchr(const void *s, s32 c, u32 n);
extern s32 mbtowc(wchar_t *pwc, const char *s, u32 n);
extern s32 mbstowcs(wchar_t *dst, const char *src, u32 n);
extern u32 strlen(const char *s);
extern wchar_t *wcschr(const wchar_t *s, wchar_t c);
extern u32 wcslen(const wchar_t *s);
extern wchar_t *parse_format__wide(wchar_t *format_string, va_list *arg, print_format *format);

typedef struct {
    unsigned char sign;
    char unused;
    short exp;
    struct {
        unsigned char length;
        unsigned char text[32];
        unsigned char unused;
    } sig;
} decimal;
typedef struct {
    char style;
    short digits;
} decform;

extern u16 data_0213a610[]; /* ctype table (u16 per char) */
extern void __num2dec(decform *form, double x, decimal *d); /* __num2dec */
extern wchar_t *wcscpy(wchar_t *dst, const wchar_t *src); /* wcscpy */
#define iswupper(c) (((c) >= 128) ? 0 : (data_0213a610[c] & 0x200))

extern void *wmemchr(const wchar_t *s, s32 c, u32 n);
extern void *wmemcpy(void *d, const void *s, u32 n);

extern s32 __wpformatter(void *(*)(void *, const wchar_t *, u32), void *, const wchar_t *, va_list);

wchar_t *long2str__wide(s32 num, wchar_t *buff, print_format format) {
    u32 unsigned_num, base;
    wchar_t *p;
    s32 n, digits;
    s32 minus = 0;
    unsigned_num = num;
    minus = 0;
    p = buff;
    n = 0;
    *--p = 0;
    digits = 0;
    if (!num && !format.precision && !(format.alternate_form && format.conversion_char == 'o'))
        return p;
    switch (format.conversion_char) {
    case 'd':
    case 'i':
        base = 10;
        if (num < 0) {
            unsigned_num = -unsigned_num;
            minus = 1;
        }
        break;
    case 'o':
        base = 8;
        format.sign_options = only_minus;
        break;
    case 'u':
        base = 10;
        format.sign_options = only_minus;
        break;
    case 'x':
    case 'X':
        base = 16;
        format.sign_options = only_minus;
        break;
    }
    do {
        s32 digit = DS_UMOD(unsigned_num, base);
        unsigned_num = DS_UDIV(unsigned_num, base);
        if (digit < 10) digit += '0';
        else if (format.conversion_char == 'x') digit += 'a' - 10;
        else digit += 'A' - 10;
        *--p = digit;
        ++n;
    } while (unsigned_num != 0);
    if (base == 8 && format.alternate_form && *p != '0') {
        *--p = '0';
        ++n;
    }
    if (format.justification_options == zero_fill) {
        format.precision = format.field_width;
        if (minus || format.sign_options != only_minus) --format.precision;
        if (base == 16 && format.alternate_form) format.precision -= 2;
    }
    if (((buff - p) + format.precision) > 509) return 0;
    while (n < format.precision) {
        *--p = '0';
        ++n;
    }
    if (base == 16 && format.alternate_form) {
        *--p = format.conversion_char;
        *--p = '0';
    }
    if (minus) *--p = '-';
    else if (format.sign_options == sign_always) *--p = '+';
    else if (format.sign_options == space_holder) *--p = ' ';
    return p;
}

wchar_t *longlong2str__wide(s64 num, wchar_t *buff, print_format format) {
    u64 unsigned_num;
    u64 base;
    wchar_t *p;
    s32 n, digits;
    s32 minus = 0;
    unsigned_num = num;
    minus = 0;
    p = buff;
    n = 0;
    *--p = 0;
    digits = 0;
    if (!num && !format.precision && !(format.alternate_form && format.conversion_char == 'o'))
        return p;
    switch (format.conversion_char) {
    case 'd':
    case 'i':
        base = 10;
        if (num < 0) {
            unsigned_num = -unsigned_num;
            minus = 1;
        }
        break;
    case 'o':
        base = 8;
        format.sign_options = only_minus;
        break;
    case 'u':
        base = 10;
        format.sign_options = only_minus;
        break;
    case 'x':
    case 'X':
        base = 16;
        format.sign_options = only_minus;
        break;
    }
    do {
        s32 digit = DS_UMOD64(unsigned_num, base);
        unsigned_num = DS_UDIV64(unsigned_num, base);
        if (digit < 10) digit += '0';
        else if (format.conversion_char == 'x') digit += 'a' - 10;
        else digit += 'A' - 10;
        *--p = digit;
        ++n;
    } while (unsigned_num != 0);
    if (base == 8 && format.alternate_form && *p != '0') {
        *--p = '0';
        ++n;
    }
    if (format.justification_options == zero_fill) {
        format.precision = format.field_width;
        if (minus || format.sign_options != only_minus) --format.precision;
        if (base == 16 && format.alternate_form) format.precision -= 2;
    }
    if (((buff - p) + format.precision) > 509) return 0;
    while (n < format.precision) {
        *--p = '0';
        ++n;
    }
    if (base == 16 && format.alternate_form) {
        *--p = format.conversion_char;
        *--p = '0';
    }
    if (minus) *--p = '-';
    else if (format.sign_options == sign_always) *--p = '+';
    else if (format.sign_options == space_holder) *--p = ' ';
    return p;
}

void round_decimal__wide(decimal *dec, s32 new_length) {
    u8 c;
    u8 *p, *t;
    s32 carry;
    s32 length;
    if (new_length < 0) {
    zero:
        dec->exp = 0;
        dec->sig.length = 1;
        dec->sig.text[0] = '0';
        return;
    }
    length = dec->sig.length;
    if (new_length >= length) return;
    t = dec->sig.text;
    p = t + new_length + 1;
    c = *--p - '0';
    if (c == 5) {
        u8 *q = t + length;
        do {
            --q;
        } while (q > p && *q == '0');
        if (q == p) carry = p[-1] & 1;
        else carry = 1;
    } else {
        carry = c > 5;
    }
    if (new_length != 0) {
        do {
            c = *--p - '0' + carry;
            carry = c > 9;
            if (carry || c == 0) {
                --new_length;
            } else {
                *p = c + '0';
                break;
            }
        } while (new_length != 0);
    }
    if (carry) {
        dec->exp++;
        dec->sig.length = 1;
        dec->sig.text[0] = '1';
        return;
    }
    if (new_length == 0) goto zero;
    dec->sig.length = new_length;
}

wchar_t *float2str__wide(double num, wchar_t *buff, print_format format) {
    decform form;
    decimal dec;
    char tbuf[512];
    char *p;
    s32 exp;
    s32 n;
    s32 sign;
    s32 digits;
    u8 *q;
    if (format.precision > 509) return 0;
    form.style = 0;
    form.digits = 32;
    __num2dec(&form, num, &dec);
    q = dec.sig.text + dec.sig.length;
    while (dec.sig.length > 1 && *--q == '0') {
        --dec.sig.length;
        ++dec.exp;
    }
    switch (dec.sig.text[0]) {
    case '0':
        dec.exp = 0;
        break;
    case 'I':
        if (num < 0) {
            p = (char *)buff - 10;
            if (iswupper(format.conversion_char)) wcscpy((wchar_t *)p, L"-INF");
            else wcscpy((wchar_t *)p, L"-inf");
        } else {
            p = (char *)buff - 8;
            if (iswupper(format.conversion_char)) wcscpy((wchar_t *)p, L"INF");
            else wcscpy((wchar_t *)p, L"inf");
        }
        return (wchar_t *)p;
    case 'N':
        p = (char *)buff - 8;
        wcscpy((wchar_t *)p, L"NaN");
        return (wchar_t *)p;
    }
    dec.exp += dec.sig.length - 1;
    p = tbuf + 512;
    *--p = 0;
    switch (format.conversion_char) {
    case 'g':
    case 'G':
        if (dec.sig.length > format.precision) round_decimal__wide(&dec, format.precision);
        if (dec.exp < -4 || dec.exp >= format.precision) {
            if (format.alternate_form) --format.precision;
            else format.precision = dec.sig.length - 1;
            if (format.conversion_char == 'g') format.conversion_char = 'e';
            else format.conversion_char = 'E';
            goto e_format;
        } else {
            if (format.alternate_form) format.precision -= dec.exp + 1;
            else {
                format.precision = dec.sig.length - (dec.exp + 1);
                if (format.precision < 0) format.precision = 0;
            }
            goto f_format;
        }
    case 'e':
    case 'E':
    e_format:
        if (dec.sig.length > format.precision + 1) round_decimal__wide(&dec, format.precision + 1);
        {
            exp = dec.exp;
            sign = '+';
            if (exp < 0) {
                exp = -exp;
                sign = '-';
            }
            n = 0;
            while (exp != 0 || n < 2) {
                *--p = (exp % 10) + '0';
                exp /= 10;
                ++n;
            }
            *--p = sign;
            *--p = format.conversion_char;
            if ((tbuf - p) + format.precision > 509) return 0;
            if (dec.sig.length < format.precision + 1) {
                digits = format.precision + 2 - dec.sig.length;
                while (--digits) {
                    *--p = '0';
                }
            }
            q = dec.sig.text + dec.sig.length;
            digits = dec.sig.length - 1;
            if (digits) {
                do {
                    *--p = *--q;
                } while (--digits);
            }
            if (format.precision || format.alternate_form) *--p = '.';
            *--p = dec.sig.text[0];
            if (dec.sign) *--p = '-';
            else if (format.sign_options == sign_always) *--p = '+';
            else if (format.sign_options == space_holder) *--p = ' ';
        }
        break;
    case 'f':
    case 'F':
    f_format: {
        s32 intd, frac, nn, i;
        frac = dec.sig.length - dec.exp - 1;
        if (frac < 0) frac = 0;
        if (frac > format.precision) {
            round_decimal__wide(&dec, dec.sig.length - (frac - format.precision));
            frac = dec.sig.length - dec.exp - 1;
            if (frac < 0) frac = 0;
        }
        intd = dec.exp + 1;
        if (intd < 0) intd = 0;
        if (intd + frac > 509) return 0;
        q = dec.sig.text + dec.sig.length;
        nn = format.precision - frac;
        for (i = 0; i < nn; i++) *--p = '0';
        for (i = 0; i < frac && i < dec.sig.length; i++) *--p = *--q;
        for (; i < frac; i++) *--p = '0';
        if (format.precision || format.alternate_form) *--p = '.';
        if (intd) {
            for (i = 0; i < intd - dec.sig.length; i++) *--p = '0';
            for (; i < intd; i++) *--p = *--q;
        } else {
            *--p = '0';
        }
        if (dec.sign) *--p = '-';
        else if (format.sign_options == sign_always) *--p = '+';
        else if (format.sign_options == space_holder) *--p = ' ';
        break;
    }
    }
    {
        u32 len = strlen(p);
        wchar_t *out = (wchar_t *)((char *)buff - len * 2) - 1;
        mbstowcs(out, p, strlen(p));
        return out;
    }
}

s32 __wpformatter(void *(*WriteProc)(void *, const wchar_t *, u32), void *WriteProcArg, const wchar_t *format_str, va_list arg_in) {
    va_list arg;
    __builtin_va_copy(arg, arg_in);
    s32 num_chars, chars_written, field_width;
    const wchar_t *format_ptr;
    const wchar_t *curr_format;
    print_format format;
    s32 long_num;
    s64 long_long_num;
    double long_double_num;
    wchar_t buff[512];
    wchar_t *buff_ptr;
    wchar_t *wcs_ptr;
    char *s, *cp;
    s32 n;
    wchar_t fill_char = L' ';
    char cc;

    format_ptr = format_str;
    chars_written = 0;

    while (*format_ptr) {
        if (!(curr_format = wcschr(format_ptr, '%'))) {
            num_chars = wcslen(format_ptr);
            chars_written += num_chars;
            if (num_chars && !WriteProc(WriteProcArg, format_ptr, num_chars)) return -1;
            break;
        }
        num_chars = curr_format - format_ptr;
        chars_written += num_chars;
        if (num_chars && !WriteProc(WriteProcArg, format_ptr, num_chars)) return -1;
        format_ptr = curr_format;
        format_ptr = parse_format__wide((wchar_t *)format_ptr, &arg, &format);
        switch (format.conversion_char) {
        case 'd':
        case 'i':
            if (format.argument_options == long_argument) {
                long_num = DS_VA_ARG_C(arg, s32, 4);
            } else if (format.argument_options == long_long_argument) {
                long_long_num = DS_VA_ARG_C(arg, s64, 8);
            } else {
                long_num = DS_VA_ARG_C(arg, s32, 4);
            }
            if (format.argument_options == short_argument) long_num = (s16)long_num;
            if (format.argument_options == long_long_argument) {
                if (!(buff_ptr = longlong2str__wide(long_long_num, buff + 512, format))) goto conversion_error;
            } else {
                if (!(buff_ptr = long2str__wide(long_num, buff + 512, format))) goto conversion_error;
            }
            num_chars = buff + 511 - buff_ptr;
            break;
        case 'o':
        case 'u':
        case 'x':
        case 'X':
            if (format.argument_options == long_argument) {
                long_num = DS_VA_ARG_C(arg, s32, 4);
            } else if (format.argument_options == long_long_argument) {
                long_long_num = DS_VA_ARG_C(arg, s64, 8);
            } else {
                long_num = DS_VA_ARG_C(arg, s32, 4);
            }
            if (format.argument_options == short_argument) long_num = (u16)long_num;
            if (format.argument_options == long_long_argument) {
                if (!(buff_ptr = longlong2str__wide(long_long_num, buff + 512, format))) goto conversion_error;
            } else {
                if (!(buff_ptr = long2str__wide(long_num, buff + 512, format))) goto conversion_error;
            }
            num_chars = buff + 511 - buff_ptr;
            break;
        case 'f':
        case 'F':
        case 'e':
        case 'E':
        case 'g':
        case 'G':
            if (format.argument_options == long_double_argument) {
                long_double_num = DS_VA_ARG_C(arg, long double, 8);
            } else {
                long_double_num = DS_VA_ARG_C(arg, double, 8);
            }
            if (!(buff_ptr = float2str__wide(long_double_num, buff + 512, format))) goto conversion_error;
            num_chars = buff + 511 - buff_ptr;
            break;
        case 's':
            if (format.argument_options == wchar_argument) {
                buff_ptr = DS_VA_ARG_C(arg, wchar_t *, 4);
                if (buff_ptr == 0) buff_ptr = L"";
                if (format.alternate_form) {
                    num_chars = (u8)*buff_ptr++;
                    if (format.precision_specified && num_chars > format.precision) num_chars = format.precision;
                } else if (format.precision_specified) {
                    num_chars = format.precision;
                    if ((wcs_ptr = wmemchr(buff_ptr, 0, num_chars)) != 0) num_chars = wcs_ptr - buff_ptr;
                } else {
                    num_chars = wcslen(buff_ptr);
                }
            } else {
                s = DS_VA_ARG_C(arg, char *, 4);
                if (s == 0) s = "";
                if (format.alternate_form) {
                    n = (u8)*buff_ptr;
                    if (format.precision_specified && n > format.precision) n = format.precision;
                } else if (format.precision_specified) {
                    n = format.precision;
                    if ((cp = memchr(s, 0, n)) != 0) n = cp - s;
                } else {
                    n = strlen(s);
                }
                if ((num_chars = mbstowcs(buff, s, n)) < 0) goto conversion_error;
                buff_ptr = buff;
            }
            break;
        case 'n':
            buff_ptr = DS_VA_ARG_C(arg, wchar_t *, 4);
            switch (format.argument_options) {
            case normal_argument: *(s32 *)buff_ptr = chars_written; break;
            case short_argument: *(s16 *)buff_ptr = chars_written; break;
            case long_argument: *(s32 *)buff_ptr = chars_written; break;
            case long_long_argument: *(s64 *)buff_ptr = chars_written; break;
            }
            continue;
        case 'c':
            buff_ptr = buff;
            if (format.argument_options == wchar_argument) {
                num_chars = 1;
                *buff_ptr = DS_VA_ARG_C(arg, s32, 4);
            } else {
                cc = DS_VA_ARG_C(arg, s32, 4);
                num_chars = mbtowc(buff_ptr, &cc, 1);
            }
            break;
        case '%':
            buff_ptr = buff;
            *buff_ptr = '%';
            num_chars = 1;
            break;
        case 0xFFFF:
        default:
        conversion_error:
            num_chars = wcslen(curr_format);
            chars_written += num_chars;
            if (num_chars && !WriteProc(WriteProcArg, curr_format, num_chars)) return -1;
            return chars_written;
        }
        field_width = num_chars;
        if (format.justification_options != left_justification) {
            fill_char = (format.justification_options == zero_fill) ? L'0' : L' ';
            if ((*buff_ptr == '+' || *buff_ptr == '-' || *buff_ptr == ' ') && fill_char == '0') {
                if (!WriteProc(WriteProcArg, buff_ptr, 1)) return -1;
                ++buff_ptr;
                --num_chars;
            }
            for (; field_width < format.field_width; ++field_width) {
                if (!WriteProc(WriteProcArg, &fill_char, 1)) return -1;
            }
        }
        if (num_chars && !WriteProc(WriteProcArg, buff_ptr, num_chars)) return -1;
        if (format.justification_options == left_justification) {
            for (; field_width < format.field_width; ++field_width) {
                wchar_t sp = L' ';
                if (!WriteProc(WriteProcArg, &sp, 1)) return -1;
            }
        }
        chars_written += field_width;
    }
    return chars_written;
}

void *__wStringWrite(void *osc, const wchar_t *buf, u32 n) {
    __wOutStr *s = (__wOutStr *)osc;
    u32 chars;
    chars = ((s->CharsWritten + n) <= s->MaxCharCount) ? n : s->MaxCharCount - s->CharsWritten;
    void *r = wmemcpy(s->CharStr + s->CharsWritten, buf, chars);
    s->CharsWritten += chars;
    return r;
}

s32 vswprintf(wchar_t *s, u32 n, const wchar_t *fmt, va_list args);

s32 swprintf(wchar_t *s, u32 n, const wchar_t *fmt, ...) {
    va_list va;
    va_start(va, fmt);
    return vswprintf(s, n, fmt, va);
}

s32 vswprintf(wchar_t *s, u32 n, const wchar_t *fmt, va_list args) {
    s32 end;
    __wOutStr osc;
    osc.CharStr = s;
    osc.MaxCharCount = n;
    osc.CharsWritten = 0;
    end = __wpformatter(__wStringWrite, &osc, fmt, args);
    if (end < 0) return end;
    if (end < n) {
        s[end] = 0;
    } else {
        (s + n)[-1] = 0;
        end = -1;
    }
    return end;
}

void *wmemcpy(void *d, const void *s, u32 n) {
    return memcpy(d, s, n * 2);
}

void *wmemchr(const wchar_t *s, s32 c, u32 n) {
    if (n) {
        do {
            if (*s == c) return (void *)s;
            s++;
        } while (--n);
    }
    return NULL;
}

s32 fwide(FILE *f, s32 mode) {
    if (f == NULL || f->mode.file_kind == 0) return 0;
    switch (f->mode.file_orientation) {
    case 0:
        if (mode > 0) f->mode.file_orientation = 2;
        else if (mode < 0) f->mode.file_orientation = 1;
        break;
    case 1: mode = -1; break;
    case 2: mode = 1; break;
    }
    return mode;
}
