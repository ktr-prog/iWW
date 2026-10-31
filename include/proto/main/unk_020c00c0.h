#ifndef PROTO_PROTO_MAIN_UNK_020C00C0_H
#define PROTO_PROTO_MAIN_UNK_020C00C0_H


#include "types.h"
#include "game/WeatherRecord.h"
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWeatherPrevDayRain
extern u8 sWeatherPrevDayRain;
#endif
#ifndef PROTO_LOCAL_sWeatherRolledAtLoad
extern s32 sWeatherRolledAtLoad;
#endif
#ifndef PROTO_LOCAL_Weather_Construct
void Weather_Construct();
#endif
#ifndef PROTO_LOCAL_Weather_Destruct
void Weather_Destruct();
#endif
#ifndef PROTO_LOCAL_Weather_SetDateToday
void Weather_SetDateToday(void *p);
#endif
#ifndef PROTO_LOCAL_Weather_PickPattern
u8 Weather_PickPattern(void *self, void *p);
#endif
#ifndef PROTO_LOCAL_Weather_GetPrevDayRain
u8 Weather_GetPrevDayRain();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Weather_InitNew
void Weather_InitNew(WeatherRecord *self);
#endif
#ifndef PROTO_LOCAL_Weather_Apply
void Weather_Apply(WeatherRecord *self);
#endif
#ifndef PROTO_LOCAL_Weather_UpdateDaily
BOOL Weather_UpdateDaily(WeatherRecord *self, void *arg);
#endif
}
#endif

#endif
