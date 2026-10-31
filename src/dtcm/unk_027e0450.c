#pragma define_section DTCM ".dtcm" abs32 RWX

#define NULL 0

typedef struct OSThread OSThread;
typedef struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;

#pragma section DTCM begin

OSThreadQueue data_027e0450 = {NULL, NULL};

#pragma section DTCM end
