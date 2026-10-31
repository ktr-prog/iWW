#pragma define_section DTCM ".dtcm" abs32 RWX

typedef unsigned char u8;

typedef struct AlarmCallbackInfo {
    void (*func)(void *);
    void *arg;
    u8 id;
} AlarmCallbackInfo;

#pragma section DTCM begin

AlarmCallbackInfo data_027e032c[8];

#pragma section DTCM end
