void NNSi_G3dGetJointScaleBasic();
void NNSi_G3dGetJointScaleMaya();
void NNSi_G3dGetJointScaleSi3d();
void NNSi_G3dSendJointSRTBasic();
void NNSi_G3dSendJointSRTMaya();
void NNSi_G3dSendJointSRTSi3d();
void NNSi_G3dSendTexSRTSi3d();
void NNSi_G3dSendTexSRTMaya();
void NNSi_G3dSendTexSRT3dsMax();
void NNSi_G3dSendTexSRTXsi();

void (*data_0213bd40[4])() = {
    NNSi_G3dSendTexSRTMaya,
    NNSi_G3dSendTexSRTSi3d,
    NNSi_G3dSendTexSRT3dsMax,
    NNSi_G3dSendTexSRTXsi,
};
void (*data_0213bd28[3])() = {
    NNSi_G3dSendJointSRTBasic,
    NNSi_G3dSendJointSRTMaya,
    NNSi_G3dSendJointSRTSi3d,
};
void (*data_0213bd34[3])() = {
    NNSi_G3dGetJointScaleBasic,
    NNSi_G3dGetJointScaleMaya,
    NNSi_G3dGetJointScaleSi3d,
};
