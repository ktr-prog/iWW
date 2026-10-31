typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "ds_div.h"
#include "types64.h"
#include "proto/autoload_2/unk_02128c60.h"
#include "proto/autoload_2/unk_0212b770.h"

extern u16 data_0213a510[];
extern u8 data_0213a490[];
extern int data_0220064c;
u32 _u32_div_f(u32 a, u32 b);

#define isspace_(c) (((c) < 0 || (c) >= 128) ? 0 : (data_0213a510[(c)] & 0x100))
#define isdigit_(c) (((c) < 0 || (c) >= 128) ? 0 : (data_0213a510[(c)] & 0x8))
#define isalpha_(c) (((c) < 0 || (c) >= 128) ? 0 : (data_0213a510[(c)] & 0x1))
#define toupper_(c) (((c) < 0 || (c) >= 128) ? (c) : data_0213a490[(c)])

enum { start = 0x01, check_for_zero = 0x02, leading_zero = 0x04, need_digit = 0x08, digit_loop = 0x10, finished = 0x20, failure = 0x40 };
#define fetch() (count++, (*ReadProc)(ReadProcArg, 0, 0))

u32 __strtoul(int base, int max_width, int (*ReadProc)(void *, int, int), void *ReadProcArg,
                  int *chars_scanned, int *negative, int *overflow) {
    int c;
    int scan_state = start;
    int count = 0;
    int spaces = 0;
    u32 value = 0;
    u32 value_max = 0;
    *negative = *overflow = 0;
    if (base < 0 || base == 1 || base > 36 || max_width < 1)
        scan_state = failure;
    else
        c = fetch();
    if (base) value_max = _u32_div_f(0xffffffff, base);
    while (count <= max_width && c != -1 && !(scan_state & (finished | failure))) {
        switch (scan_state) {
        case start:
            if (isspace_(c)) {
                c = (*ReadProc)(ReadProcArg, 0, 0);
                spaces++;
                break;
            }
            if (c == '+')
                c = fetch();
            else if (c == '-') {
                c = fetch();
                *negative = 1;
            }
            scan_state = check_for_zero;
            break;
        case check_for_zero:
            if ((base == 0 || base == 16) && c == '0') {
                scan_state = leading_zero;
                c = fetch();
            } else
                scan_state = need_digit;
            break;
        case leading_zero:
            if (c == 'X' || c == 'x') {
                base = 16;
                scan_state = need_digit;
                c = fetch();
            } else {
                if (base == 0) base = 8;
                scan_state = digit_loop;
            }
            break;
        case need_digit:
        case digit_loop:
            if (base == 0) base = 10;
            if (!value_max) value_max = _u32_div_f(0xffffffff, base);
            if (isdigit_(c)) {
                c -= '0';
                if (c >= base) {
                    scan_state = (scan_state == digit_loop) ? finished : failure;
                    c += '0';
                    break;
                }
            } else if (!isalpha_(c) || toupper_(c) - 'A' + 10 >= base) {
                scan_state = (scan_state == digit_loop) ? finished : failure;
                break;
            } else {
                c = toupper_(c) - 'A' + 10;
            }
            if (value > value_max) *overflow = 1;
            value *= base;
            if (c > 0xffffffff - value) *overflow = 1;
            value += c;
            scan_state = digit_loop;
            c = fetch();
            break;
        }
    }
    if (!(scan_state & (leading_zero | digit_loop | finished))) {
        value = 0;
        *chars_scanned = 0;
    } else
        *chars_scanned = count - 1 + spaces;
    (*ReadProc)(ReadProcArg, c, 1);
    return value;
}

u64 __strtoull(int base, int max_width, int (*ReadProc)(void *, int, int), void *ReadProcArg,
                  int *chars_scanned, int *negative, int *overflow) {
    int c;
    int scan_state = start;
    int count = 0;
    int spaces = 0;
    u64 value = 0;
    u64 value_max = 0;
    *negative = *overflow = 0;
    if (base < 0 || base == 1 || base > 36 || max_width < 1)
        scan_state = failure;
    else
        c = fetch();
    if (base) value_max = DS_UDIV64(0xffffffffffffffffULL, base);
    while (count <= max_width && c != -1 && !(scan_state & (finished | failure))) {
        switch (scan_state) {
        case start:
            if (isspace_(c)) {
                c = (*ReadProc)(ReadProcArg, 0, 0);
                spaces++;
                break;
            }
            if (c == '+')
                c = fetch();
            else if (c == '-') {
                c = fetch();
                *negative = 1;
            }
            scan_state = check_for_zero;
            break;
        case check_for_zero:
            if ((base == 0 || base == 16) && c == '0') {
                scan_state = leading_zero;
                c = fetch();
            } else
                scan_state = need_digit;
            break;
        case leading_zero:
            if (c == 'X' || c == 'x') {
                base = 16;
                scan_state = need_digit;
                c = fetch();
            } else {
                if (base == 0) base = 8;
                scan_state = digit_loop;
            }
            break;
        case need_digit:
        case digit_loop:
            if (base == 0) base = 10;
            if (!value_max) value_max = DS_UDIV64(0xffffffffffffffffULL, base);
            if (isdigit_(c)) {
                c -= '0';
                if (c >= base) {
                    scan_state = (scan_state == digit_loop) ? finished : failure;
                    c += '0';
                    break;
                }
            } else if (!isalpha_(c) || toupper_(c) - 'A' + 10 >= base) {
                scan_state = (scan_state == digit_loop) ? finished : failure;
                break;
            } else {
                c = toupper_(c) - 'A' + 10;
            }
            if (value > value_max) *overflow = 1;
            value *= base;
            if (c > 0xffffffffffffffffULL - value) *overflow = 1;
            value += c;
            scan_state = digit_loop;
            c = fetch();
            break;
        }
    }
    if (!(scan_state & (leading_zero | digit_loop | finished))) {
        value = 0;
        *chars_scanned = 0;
    } else
        *chars_scanned = count - 1 + spaces;
    (*ReadProc)(ReadProcArg, c, 1);
    return value;
}

typedef struct {
    char *NextChar;
    int NullCharDetected;
} __InStrCtrl;

u32 strtoul(const char *str, char **end, int base) {
    u32 value;
    int count, negative, overflow;
    __InStrCtrl isc;
    isc.NextChar = (char *)str;
    isc.NullCharDetected = 0;
    value = __strtoul(base, 0x7fffffff, (int (*)(void *, int, int))__StringRead, &isc, &count, &negative, &overflow);
    if (end) *end = (char *)str + count;
    if (overflow) {
        value = 0xffffffff;
        data_0220064c = 34;
    } else if (negative) {
        value = -value;
    }
    return value;
}

int strtol(const char *str, char **end, int base) {
    u32 value;
    int count, negative, overflow;
    __InStrCtrl isc;
    isc.NextChar = (char *)str;
    isc.NullCharDetected = 0;
    value = __strtoul(base, 0x7fffffff, (int (*)(void *, int, int))__StringRead, &isc, &count, &negative, &overflow);
    if (end) *end = (char *)str + count;
    if (overflow || (!negative && value > 0x7fffffff) || (negative && value > 0x80000000)) {
        value = negative ? 0x80000000 : 0x7fffffff;
        data_0220064c = 34;
    } else if (negative) {
        value = -value;
    }
    return value;
}

int atol(const char *str) {
    return strtol(str, 0, 10);
}
