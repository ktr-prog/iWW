#ifndef NITRO_PXI_PTR_H
#define NITRO_PXI_PTR_H

#ifdef __cplusplus
extern "C" {
#endif
void HostPxi_PutPointer(unsigned int tag, const void *p);
void *HostPxi_TakeArm7Pointer(unsigned int tag);
#ifdef __cplusplus
}
#endif
static inline unsigned int PXI_PointerWord(unsigned int tag, const void *p) {
    HostPxi_PutPointer(tag, p);
    return (unsigned int)(__UINTPTR_TYPE__)p;
}

#endif
