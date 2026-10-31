#ifndef NET_SSLCONNECTION_H
#define NET_SSLCONNECTION_H

#include "types.h"
#include "net/SslRootCa.h"
#include "net/SslSession.h"
#include "net/SslMd5Context.h"
#include "net/SslSha1Context.h"


typedef struct SslConnection SslConnection;

typedef struct SslRsaPrivateKey SslRsaPrivateKey;
struct SslRsaPrivateKey {
    /* 0x00 */ s32 modulusLen;
    /* 0x04 */ u8 *modulus;
    /* 0x08 */ s32 primePLen;
    /* 0x0c */ u8 *primeP;
    /* 0x10 */ s32 primeQLen;
    /* 0x14 */ u8 *primeQ;
    /* 0x18 */ s32 exponentPLen;
    /* 0x1c */ u8 *exponentP;
    /* 0x20 */ s32 exponentQLen;
    /* 0x24 */ u8 *exponentQ;
    /* 0x28 */ s32 coefficientLen;
    /* 0x2c */ u8 *coefficient;
};

typedef struct SslServerCert SslServerCert;
struct SslServerCert {
    /* 0x00 */ u32 length;
    /* 0x04 */ u8 *data;
};

typedef u32 (*SslCertVerifyCallback)(u32, SslConnection *, s32);

struct SslConnection {
    /* 0x000 */ SslSession *session;
    /* 0x004 */ u8 resumed;
    /* 0x005 */ u8 unk_005;
    /* 0x006 */ u16 cipherSuite;
    /* 0x008 */ u8 clientRandom[0x20];
    /* 0x028 */ u8 serverRandom[0x20];
    /* 0x048 */ u8 keyBlock[0x48];
    /* 0x090 */ u8 *writeMacSecret;
    /* 0x094 */ u8 *writeKey;
    /* 0x098 */ u8 *writeIv;
    /* 0x09c */ u8 writeCipher[0x104];
    /* 0x1a0 */ u8 writeSeqNum[8];
    /* 0x1a8 */ u8 *readMacSecret;
    /* 0x1ac */ u8 *readKey;
    /* 0x1b0 */ u8 *readIv;
    /* 0x1b4 */ u8 readCipher[0x104];
    /* 0x2b8 */ u8 readSeqNum[8];
    /* 0x2c0 */ SslSha1Context handshakeSha1;
    /* 0x31c */ SslSha1Context sha1Work;
    /* 0x378 */ SslMd5Context handshakeMd5;
    /* 0x3d0 */ SslMd5Context md5Work;
    /* 0x428 */ u8 isServer;
    /* 0x429 */ u8 handshakeState;
    /* 0x42a */ u8 recordReady;
    /* 0x42b */ u8 pad_42b;
    /* 0x42c */ s32 certSigAlgorithm;
    /* 0x430 */ s32 peerKeyAlgorithm;
    /* 0x434 */ u8 *tbsStart;
    /* 0x438 */ u8 *tbsEnd;
    /* 0x43c */ u8 tbsDigest[0x14];
    /* 0x450 */ s32 tbsDigestLen;
    /* 0x454 */ SslRootCa issuerKey;
    /* 0x468 */ u8 peerModulus[0x100];
    /* 0x568 */ s32 peerModulusLen;
    /* 0x56c */ u8 peerExponent[8];
    /* 0x574 */ s32 peerExponentLen;
    /* 0x578 */ u8 *certSignature;
    /* 0x57c */ s32 certSignatureLen;
    /* 0x580 */ u8 inSubject;
    /* 0x581 */ u8 inPublicKey;
    /* 0x582 */ u8 pendingAttrOid;
    /* 0x583 */ u8 isDateValid;
    /* 0x584 */ char issuerName[0x100];
    /* 0x684 */ char subjectName[0x100];
    /* 0x784 */ char commonName[0x50];
    /* 0x7d4 */ char *hostName;
    /* 0x7d8 */ u8 *certData;
    /* 0x7dc */ s32 certLen;
    /* 0x7e0 */ u32 currentDate;
    /* 0x7e4 */ SslCertVerifyCallback certVerifyCallback;
    /* 0x7e8 */ SslRootCa **rootCaList;
    /* 0x7ec */ s32 numRootCas;
    /* 0x7f0 */ SslRsaPrivateKey *serverKey;
    /* 0x7f4 */ SslServerCert *serverCert;
    /* 0x7f8 */ u8 *recordBuf;
    /* 0x7fc */ u32 recordLen;
    /* 0x800 */ u32 recordPos;
};

#endif
