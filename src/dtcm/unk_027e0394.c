#pragma define_section DTCM ".dtcm" abs32 RWX

typedef unsigned int u32;
typedef int BOOL;
typedef void (*PXIFifoCallback)(u32 tag, u32 data, BOOL err);

#pragma section DTCM begin

PXIFifoCallback data_027e0394[32];

#pragma section DTCM end
