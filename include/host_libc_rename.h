#ifndef HOST_LIBC_RENAME_H
#define HOST_LIBC_RENAME_H


#define HOST_LIBC_STR_(x) #x
#define HOST_LIBC_STR(x) HOST_LIBC_STR_(x)
#define HOST_LIBC_SYMBOL(name) __asm__(HOST_LIBC_STR(__USER_LABEL_PREFIX__) #name)

#ifdef __cplusplus
extern "C" int atexit(void (*func)(void)) HOST_LIBC_SYMBOL(ds_atexit);
#endif

#define abort ds_abort
#define abs ds_abs
#define atexit ds_atexit
#define atol ds_atol
#define exit ds_exit
#define qsort ds_qsort
#define raise ds_raise
#define rand ds_rand
#define srand ds_srand
#define strtol ds_strtol
#define strtoul ds_strtoul
#define __strtold ds___strtold
#define time ds_time
#define fclose ds_fclose
#define fflush ds_fflush
#define fread ds_fread
#define fseek ds_fseek
#define ftell ds_ftell
#define rewind ds_rewind
#define fwide ds_fwide
#define sscanf ds_sscanf
#define vsscanf ds_vsscanf
#define swprintf ds_swprintf
#define vswprintf ds_vswprintf
#define mbstowcs ds_mbstowcs
#define mbtowc ds_mbtowc
#define memchr ds_memchr
#define memcmp ds_memcmp
#define memcpy ds_memcpy
#define memmove ds_memmove
#define memset ds_memset
#define strcat ds_strcat
#define strchr ds_strchr
#define strcmp ds_strcmp
#define strcpy ds_strcpy
#define strcspn ds_strcspn
#define strlen ds_strlen
#define strncmp ds_strncmp
#define strncpy ds_strncpy
#define _strlwr ds__strlwr
#define strspn ds_strspn
#define strstr ds_strstr
#define wcschr ds_wcschr
#define wcscpy ds_wcscpy
#define wcslen ds_wcslen
#define wmemchr ds_wmemchr
#define wmemcpy ds_wmemcpy
#define copysign ds_copysign
#define fabs ds_fabs
#define frexp ds_frexp
#define ldexp ds_ldexp
#define nan ds_nan
#define pow ds_pow
#define scalbn ds_scalbn
#define accept ds_accept
#define bind ds_bind
#define closesocket ds_closesocket
#define connect ds_connect
#define getsockname ds_getsockname
#define getsockopt ds_getsockopt
#define inet_addr ds_inet_addr
#define listen ds_listen
#define recv ds_recv
#define recvfrom ds_recvfrom
#define send ds_send
#define sendto ds_sendto
#define setsockopt ds_setsockopt
#define shutdown ds_shutdown
#define socket ds_socket
#define __cxa_vec_new ds___cxa_vec_new
#define __cxa_vec_ctor ds___cxa_vec_ctor
#define __cxa_vec_dtor ds___cxa_vec_dtor
#define __cxa_vec_delete ds___cxa_vec_delete
#define __cxa_vec_cleanup ds___cxa_vec_cleanup

#endif
