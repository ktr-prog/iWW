#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_0212703C_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_0212703C_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL___convert_from_newlines
void __convert_from_newlines(u8 *buf, u32 *count);
#endif
#ifndef PROTO_LOCAL___convert_to_newlines
void __convert_to_newlines(u8 *buf, u32 *count);
#endif
#ifndef PROTO_LOCAL_abs
s32 abs(s32 x);
#endif
#ifndef PROTO_LOCAL___flush_all
s32 __flush_all(void);
#endif
#ifndef PROTO_LOCAL___flush_line_buffered_output_files
s32 __flush_line_buffered_output_files(void);
#endif
#ifndef PROTO_LOCAL_nan
double nan(const char *unused);
#endif
#ifndef PROTO_LOCAL_abort
void abort(void);
#endif
#ifndef PROTO_LOCAL_exit
void exit(s32 status);
#endif
#ifndef PROTO_LOCAL___exit
void __exit(s32 status);
#endif
#ifndef PROTO_LOCAL_STD_CopyString
char *STD_CopyString(char *dst, const char *src);
#endif
#ifndef PROTO_LOCAL_STD_CopyLString
void STD_CopyLString(char *dst, const char *src, s32 n);
#endif
#ifndef PROTO_LOCAL_STD_GetStringLength
u32 STD_GetStringLength(const char *s);
#endif
#ifndef PROTO_LOCAL_STD_ConcatenateString
char *STD_ConcatenateString(char *dst, const char *src);
#endif
#ifndef PROTO_LOCAL_MATH_CalcChecksum8
u8 MATH_CalcChecksum8(const u8 *p, u32 len);
#endif
#ifndef PROTO_LOCAL_MATHi_CRC8InitTable
void MATHi_CRC8InitTable(u8 *table, u32 poly);
#endif
#ifndef PROTO_LOCAL_MATHi_CRC8Update
void MATHi_CRC8Update(const u8 *table, u8 *crc, const u8 *data, u32 len);
#endif
#ifndef PROTO_LOCAL_MATHi_CRC16InitTableRev
void MATHi_CRC16InitTableRev(u16 *table, u32 poly);
#endif
#ifndef PROTO_LOCAL_MATHi_CRC16UpdateRev
void MATHi_CRC16UpdateRev(const u16 *table, u16 *crc, const u8 *data, u32 len);
#endif
#ifndef PROTO_LOCAL_MATHi_CRC32InitTableRev
void MATHi_CRC32InitTableRev(u32 *table, u32 poly);
#endif
#ifndef PROTO_LOCAL_MATHi_CRC32UpdateRev
void MATHi_CRC32UpdateRev(const u32 *table, u32 *crc, const u8 *data, u32 len);
#endif
#ifndef PROTO_LOCAL_MATH_CalcCRC8
u8 MATH_CalcCRC8(const u8 *table, const void *data, u32 len);
#endif
#ifndef PROTO_LOCAL_MATH_CalcCRC16
u16 MATH_CalcCRC16(const u16 *table, const void *data, u32 len);
#endif
#ifndef PROTO_LOCAL_MATH_CalcCRC32
u32 MATH_CalcCRC32(const u32 *table, const void *data, u32 len);
#endif
#ifndef PROTO_LOCAL_MATH_CalcSHA1
void MATH_CalcSHA1(void *digest, const void *data, u32 len);
#endif
#ifndef PROTO_LOCAL_MATH_CountPopulation
u32 MATH_CountPopulation(u32 x);
#endif
#ifndef PROTO_LOCAL_CTRDG_Init
void CTRDG_Init(void);
#endif
#ifndef PROTO_LOCAL_CTRDGi_InitModuleInfo
void CTRDGi_InitModuleInfo(void);
#endif
#ifndef PROTO_LOCAL_CTRDGi_CallbackForInitModuleInfo
void CTRDGi_CallbackForInitModuleInfo(u32 tag, u32 data);
#endif
#ifndef PROTO_LOCAL_CTRDGi_PulledOutCallback
void CTRDGi_PulledOutCallback(u32 tag, u32 data);
#endif
#ifndef PROTO_LOCAL_CTRDG_TerminateForPulledOut
void CTRDG_TerminateForPulledOut(void);
#endif
#ifndef PROTO_LOCAL_CTRDGi_InitCommon
void CTRDGi_InitCommon(void);
#endif
#ifdef __cplusplus
}
#endif

#endif
