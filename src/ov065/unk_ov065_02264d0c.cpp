#include "types.h"
#include "net/IpFragEntry.h"
#include "nitro/math.h"
#include "net/IpStackConfig.h"
#include "net/SslConnection.h"
#include "net/SslSession.h"
#include "net/IpSocket.h"
#include "net/SslSha1Context.h"
#include "nitro/os_rtc.h"
#include "proto/autoload_2/unk_02113088.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/itcm/unk_01ffa4a0.h"
#include "proto/main/unk_02000b44.h"
#include "proto/ov065/unk_ov065_02264d0c.h"
#include "proto/ov065/unk_ov065_022671a0.h"
#include "proto/ov065/unk_ov065_0226795c.h"
extern "C" {
void MI_CpuFill8(void *dst, u32 data, u32 size);
void MI_CpuCopy8(const void *src, void *dst, u32 size);
}

namespace Unk_ov065_0226650c_Ns {



typedef SslConnection Ctx;
typedef SslRsaPrivateKey Rsa;
typedef SslRootCa Key;

extern "C" {
extern void *(*sIpAlloc)(u32);
extern void (*sIpFree)(void *);
extern u16 sSslCipherSuites[2];
extern u8 sSslNoSession[];
extern u32 gSslRsaThreadPriority;
extern char *sSslCertOidTable[6];
extern OSThreadInfo data_021fcc2c;

s32 _s32_div_f(s32, s32);
u32 strlen(const char *);
void RTC_GetDate(RTCDate *);
u32 OS_GetThreadPriority(OSThread *);
void OS_SetThreadPriority(OSThread *, u32);


void Ssl_DeriveMasterSecret(Ctx *);
void Ssl_DeriveSecretPart(u8 *, char *, Ctx *);
void SslRsa_PrivateDecrypt(u8 *, u8 *, Rsa *);
void Ssl_HandleClientHello(Ctx *, u8 *);
void Ssl_HandleClientHelloV2(Ctx *, u8 *);
s32 Ssl_IsVersion3(u32, u32);
u32 Ssl_ChooseCipherSuite(u8 *, s32, s32);
s32 Ssl_ListContains(u8 *, s32, s32, u32);
void Ssl_HandleServerHello(Ctx *, u8 *);
void Ssl_HandleCertificate(Ctx *, u8 *);
s32 SslCert_MatchHostName(char *, char *);
s32 SslCert_LabelLength(char *);
u32 SslCert_Verify(Ctx *);
s32 SslCert_VerifySignature(Ctx *, Key *);
s32 SslCert_ParseAsn1(Ctx *, u8 **, s32, s32, s32);

s32 SslCert_ParseAsn1(Ctx *c, u8 **pp, s32 depth, s32 idx, s32 mode) {
    u8 *p;
    u32 tag;
    s32 len;
    s32 i;
    u8 *end;
    char **tbl;
    u8 *send;
    s32 oi;
    u8 *op;
    char *oe;
    p = *pp;
    tag = *p++;
    len = SslCert_ReadDerLength(&p);
    if (len < 0 || len > 0x7d0) {
        return 1;
    }
    switch (tag & 0x1f) {
    case 0:
    case 1:
        goto def;
    case 2:
        if (c->inPublicKey != 0) {
            if (idx == 0) {
                if (*p == 0) {
                    do {
                        p++;
                        len--;
                    } while (*p == 0);
                }
                switch (mode) {
                case 0:
                    if (len <= 0x100) {
                        MI_CpuCopy8(p, c->peerModulus, len);
                        c->peerModulusLen = len;
                    }
                    break;
                case 2:
                    c->issuerKey.modulusLen = len;
                    c->issuerKey.modulus = p;
                    break;
                }
            } else if (idx == 1) {
                if (*p == 0) {
                    do {
                        p++;
                        len--;
                    } while (*p == 0);
                }
                switch (mode) {
                case 0:
                    if (len <= 8) {
                        MI_CpuCopy8(p, c->peerExponent, len);
                        c->peerExponentLen = len;
                    }
                    break;
                case 2:
                    c->issuerKey.exponentLen = len;
                    c->issuerKey.exponent = p;
                    break;
                }
            }
        }
        p += len;
        break;
    case 3:
        if (depth == 1 && mode != 2) {
            c->certSignature = p + 1;
            c->certSignatureLen = len - 1;
        }
        if (c->inPublicKey != 0) {
            p++;
            if (SslCert_ParseAsn1(c, &p, depth, 0, mode) != 0) {
                return 1;
            }
            c->inPublicKey = 0;
        } else {
            p += len;
        }
        break;
    case 6:
        oi = 0;
        tbl = sSslCertOidTable;
        op = p;
        do {
            oe = *tbl;
            if (memcmp(op, oe, strlen(oe)) == 0) {
                switch (oi) {
                case 0:
                    break;
                case 1:
                case 2:
                    if (mode == 0) {
                        c->peerKeyAlgorithm = oi;
                    }
                    c->inPublicKey = oi;
                    break;
                case 3:
                case 4:
                    if (mode != 2) {
                        c->certSigAlgorithm = oi;
                    }
                    break;
                case 5:
                    if (mode != 2) {
                        c->pendingAttrOid = oi;
                    }
                    break;
                }
                break;
            }
            tbl++;
            oi++;
        } while (oi < 6);
        p += len;
        break;
    case 12:
    case 19:
    case 20:
    case 22:
        if (mode != 2) {
            if (c->inSubject != 0) {
                SslCert_AppendName(c->subjectName, (const char *)p, len);
                if (c->pendingAttrOid == 5 && len <= 0x4f) {
                    MI_CpuCopy8(p, c->commonName, len);
                    (c->commonName)[len] = 0;
                }
            } else {
                SslCert_AppendName(c->issuerName, (const char *)p, len);
            }
        }
        c->pendingAttrOid = 0;
        p += len;
        break;
    case 23:
    case 24:
        if (mode != 2) {
            u32 t = SslCert_ParseTime(p, tag & 0x1f);
            if (idx == 0) {
                if (c->currentDate >= t) {
                    c->isDateValid = 1;
                }
            } else {
                if (c->currentDate > t) {
                    c->isDateValid = 0;
                }
            }
        }
        p += len;
        c->inSubject = 1;
        break;
    case 16:
        if (depth == 0 && idx == 0 && mode != 2) {
            c->tbsStart = p;
        }
        send = p + len;
        for (i = 0; p < send;) {
            s32 r = SslCert_ParseAsn1(c, &p, depth + 1, i, mode);
            i++;
            if (r != 0) {
                return 1;
            }
        }
        if (depth == 1 && idx == 0 && mode != 2) {
            c->tbsEnd = p;
        }
        break;
    case 17:
        end = p + len;
        while (p < end) {
            if (SslCert_ParseAsn1(c, &p, depth + 1, 0, mode) != 0) {
                return 1;
            }
        }
        break;
    default:
    def:
        if (tag == 0xa0) {
            end = p + len;
            while (p < end) {
                if (SslCert_ParseAsn1(c, &p, depth + 1, 0, mode) != 0) {
                    return 1;
                }
            }
        } else {
            p += len;
        }
        break;
    }
    *pp = p;
    return 0;
}

s32 SslCert_VerifySignature(Ctx *c, Key *k) {
    if (c->certSignature == 0 || c->certSignatureLen == 0 || k->exponent == 0 || k->exponentLen == 0 || k->modulus == 0 || k->modulusLen == 0) {
        return 2;
    }
    s32 n = (k->modulusLen * 2) / 2;
    u16 *buf = (u16 *)sIpAlloc(n * 8);
    if (buf == 0) {
        return 2;
    }
    u16 *b1 = buf + n;
    u16 *b2 = b1 + n;
    u16 *b3 = b2 + n;
    SslBigNum_FromBytes(b1, c->certSignature, c->certSignatureLen, n);
    SslBigNum_FromBytes(b2, k->exponent, k->exponentLen, n);
    SslBigNum_FromBytes(b3, k->modulus, k->modulusLen, n);
    if (gSslRsaThreadPriority < 0x20) {
        OSThread *th = data_021fcc2c.current;
        u32 pr = OS_GetThreadPriority(th);
        OS_SetThreadPriority(th, gSslRsaThreadPriority);
        SslBigNum_ModExp(buf, b1, b2, n, b3);
        OS_SetThreadPriority(th, pr);
    } else {
        SslBigNum_ModExp(buf, b1, b2, n, b3);
    }
    SslBigNum_ToBytes((u8 *)b1, buf, k->modulusLen);
    s32 r = 0;
    u8 *q = (u8 *)b1;
    if (q[0] != 0 || q[1] != 1) {
        r = 2;
    } else {
        s32 i = 2;
        s32 len = k->modulusLen;
        if (len > 2) {
            do {
                if (q[i] != 0xff) {
                    break;
                }
                i++;
            } while (i < len);
        }
        s32 j = i + 1;
        if (j < len && q[i] == 0 && q[j] == 0x30 && memcmp(c->tbsDigest, q + len - c->tbsDigestLen, c->tbsDigestLen) == 0) {
        } else {
            r = 2;
        }
    }
    sIpFree(buf);
    return r;
}

u32 SslCert_Verify(Ctx *c) {
    u32 r;
    if (c->isDateValid != 0) {
        r = 0;
    } else {
        r = 0x8000;
    }
    if (c->peerKeyAlgorithm == -1) {
        r |= 4;
        return r;
    }
    switch (c->certSigAlgorithm) {
    case 3: {
        SslMd5Context *md5 = &c->md5Work;
        SslMd5_Init(md5);
        u8 *s = c->tbsStart;
        SslMd5_Update(md5, s, c->tbsEnd - s);
        SslMd5_Final(md5, c->tbsDigest);
        c->tbsDigestLen = 0x10;
        break;
    }
    case 4: {
        SslSha1Context *sha1 = &c->sha1Work;
        SslSha1_Init(sha1);
        u8 *s = c->tbsStart;
        SslSha1_Update(sha1, s, c->tbsEnd - s);
        SslSha1_Final(sha1, c->tbsDigest);
        c->tbsDigestLen = 0x14;
        break;
    }
    default:
        r |= 3;
        return r;
    }
    Key *k = SslCert_FindRootCa(c, c->issuerName);
    if (k == 0) {
        r |= 1;
        return r;
    }
    r |= SslCert_VerifySignature(c, k);
    return r;
}

s32 SslCert_LabelLength(char *s) {
    char *o = s;
    while (*(s8 *)s != '.' && *(s8 *)s != 0) {
        s++;
    }
    return s - o;
}

s32 SslCert_MatchHostName(char *a, char *b) {
    s8 x, y;
    for (;;) {
        while (x = *(s8 *)b++, y = *(s8 *)a++, y == x) {
            if (y == 0) {
                return 0;
            }
        }
        if (x != '*') {
            return 1;
        }
        a--;
        s32 la = SslCert_LabelLength(a);
        s32 lb = SslCert_LabelLength(b);
        if (lb > la) {
            return 1;
        }
        a += la - lb;
    }
}

void Ssl_HandleCertificate(Ctx *c, u8 *p) {
    u32 len;
    u32 rl;
    u32 ty;
    u32 r4;
    s32 i;
    s32 k;
    RTCDate d;
    len = (((p[0] << 8) + p[1]) << 8) + p[2];
    p += 3;
    c->peerKeyAlgorithm = -1;
    RTC_GetDate(&d);
    c->currentDate = d.day + (((d.year + 0x7d0) << 16) + (d.month << 8));
    c->subjectName[0] = 0;
    c->peerModulusLen = c->peerExponentLen = 0;
    i = k = 0;
    for (;;) {
        rl = (((p[0] << 8) + p[1]) << 8) + p[2];
        p += 3;
        len -= rl + 3;
        c->certSigAlgorithm = -1;
        c->inPublicKey = 0;
        c->inSubject = 0;
        c->isDateValid = 0;
        c->subjectName[0] = 0;
        c->issuerName[0] = 0;
        c->commonName[0] = 0;
        c->certData = p;
        c->certLen = rl;
        if (SslCert_ParseAsn1(c, &p, 0, 0, k) != 0 || (u32)c->peerModulusLen < 0x33 || c->peerExponentLen == 0) {
            c->handshakeState = 9;
            return;
        }
        r4 = SslCert_Verify(c);
        if (i == 0 && c->hostName != 0 && SslCert_MatchHostName(c->hostName, c->commonName) != 0) {
            r4 |= 0x4000;
        }
        ty = r4 & 0xff;
        if (ty == 1 && len != 0) {
            u8 *q = p + 3;
            c->inPublicKey = 0;
            if (SslCert_ParseAsn1(c, &q, 0, 0, 2) != 0) {
                c->handshakeState = 9;
                return;
            }
            r4 = (r4 & ~0xff) | SslCert_VerifySignature(c, &c->issuerKey);
        }
        if (c->certVerifyCallback != 0) {
            r4 = c->certVerifyCallback(r4, c, i);
        }
        i++;
        if (ty != 0 && r4 == 0 && len != 0) {
            k = 1;
            continue;
        }
        break;
    }
    if (r4 == 0) {
        c->handshakeState = 3;
    } else {
        c->handshakeState = 9;
    }
}

void Ssl_HandleServerHello(Ctx *c, u8 *p) {
    u8 n;
    u8 *old;
    MI_CpuCopy8(p + 2, c->serverRandom, 0x20);
    p += 0x22;
    n = *p++;
    old = (u8 *)c->session;
    if (old != 0 && n == 0x20 && memcmp(old, p, 0x20) == 0) {
        c->resumed = 1;
    } else {
        if (old != 0) {
            old[0x5a] = 0;
        }
        if (n == 0) {
            c->session = (SslSession *)sSslNoSession;
        } else {
            c->session = SslSession_Add(p);
        }
        c->resumed = 0;
    }
    p += n;
    c->cipherSuite = (p[0] << 8) + p[1];
    c->handshakeState = 2;
}

s32 Ssl_ListContains(u8 *p, s32 cnt, s32 size, u32 key) {
    s32 i;
    for (i = 0; i < cnt; p += size, i++) {
        u32 v = (p[0] << 8) + p[1];
        if (size == 3) {
            v = (v << 8) + p[2];
        }
        if (v == key) {
            return TRUE;
        }
    }
    return FALSE;
}

u32 Ssl_ChooseCipherSuite(u8 *p, s32 cnt, s32 size) {
    u32 i;
    u16 *t;
    for (i = 0, t = sSslCipherSuites; i < 2; t++, i++) {
        if (Ssl_ListContains(p, cnt, size, *t)) {
            return sSslCipherSuites[i];
        }
    }
    return 0;
}

s32 Ssl_IsVersion3(u32 a, u32 b) {
    if (a == 3) {
        return TRUE;
    }
    return FALSE;
}

void Ssl_HandleClientHelloV2(Ctx *c, u8 *p) {
    if (Ssl_IsVersion3(p[0], p[1])) {
        s32 a = (p[2] << 8) + p[3];
        u16 r = Ssl_ChooseCipherSuite(p + 8, a / 3, 3);
        if (r != 0) {
            c->cipherSuite = r;
            s32 b = (p[4] << 8) + p[5];
            s32 n = (p[6] << 8) + p[7];
            c->session = 0;
            a += 8;
            u8 *q = p + (a + b);
            if (n >= 0x20) {
                MI_CpuCopy8(q, c->clientRandom, 0x20);
            } else {
                MI_CpuFill8(c->clientRandom, 0, 0x20 - n);
                MI_CpuCopy8(q, c->serverRandom - n, n);
            }
            c->handshakeState = 1;
        }
    }
}

void Ssl_HandleClientHello(Ctx *c, u8 *p) {
    if (Ssl_IsVersion3(p[0], p[1])) {
        MI_CpuCopy8(p + 2, c->clientRandom, 0x20);
        u32 n = p[0x22];
        u8 *q = p + 0x23;
        if (n != 0x20) {
            c->session = 0;
        } else {
            c->session = SslSession_FindById(q);
        }
        q += n;
        u16 r = Ssl_ChooseCipherSuite(q + 2, ((q[0] << 8) + q[1]) / 2, 2);
        c->cipherSuite = r;
        if (r != 0) {
            c->handshakeState = 1;
        }
    }
}

void SslRsa_PrivateDecrypt(u8 *out, u8 *in, Rsa *k) {
    if (k != 0 && k->modulusLen != 0) {
        s32 n = (k->modulusLen * 2) / 2 + 1;
        u16 *b0 = (u16 *)sIpAlloc(n * 20);
        if (b0 != 0) {
            u16 *b1 = b0 + n;
            u16 *b2 = b1 + n;
            u16 *b3 = b2 + n;
            u16 *b4 = b3 + n;
            u16 *b5 = b4 + n;
            u16 *b6 = b5 + n;
            u16 *b7 = b6 + n;
            SslBigNum_FromBytes(b0, in, k->modulusLen, n);
            SslBigNum_FromBytes(b1, k->exponentP, k->exponentPLen, n);
            SslBigNum_FromBytes(b5, k->primeP, k->primePLen, n);
            SslBigNum_ModExpMontgomery(b3, b0, b1, n, b5);
            SslBigNum_FromBytes(b1, k->exponentQ, k->exponentQLen, n);
            SslBigNum_FromBytes(b5, k->primeQ, k->primeQLen, n);
            SslBigNum_ModExpMontgomery(b4, b0, b1, n, b5);
            SslBigNum_Sub(b0, b3, b4, n);
            SslBigNum_FromBytes(b1, k->coefficient, k->coefficientLen, n);
            SslBigNum_Mul(b2, b0, b1, n);
            SslBigNum_FromBytes(b1, k->primeQ, k->primeQLen, n);
            SslBigNum_Mul(b0, b2, b1, n);
            SslBigNum_Add(b2, b0, b4, n);
            SslBigNum_FromBytes(b1, k->modulus, k->modulusLen, n);
            if (SslBigNum_Sign(b2, n) < 0) {
                SslBigNum_Negate(b2, n);
                SslBigNum_DivMod(0, b2, b1, b6, n, b7);
                SslBigNum_Sub(b6, b1, b6, n);
            } else {
                SslBigNum_DivMod(0, b2, b1, b6, n, b7);
            }
            SslBigNum_ToBytes(out, b6, 0x30);
            sIpFree(b0);
        }
    }
}

void Ssl_DeriveSecretPart(u8 *out, char *label, Ctx *c) {
    u8 tmp[0x14];
    SslSha1Context *sha1 = &c->sha1Work;
    SslSha1_Init(sha1);
    SslSha1_Update(sha1, (const u8 *)label, strlen(label));
    SslSha1_Update(sha1, c->session->masterSecret, 0x30);
    SslSha1_Update(sha1, c->clientRandom, 0x20);
    SslSha1_Update(sha1, c->serverRandom, 0x20);
    SslSha1_Final(sha1, tmp);
    SslMd5Context *md5 = &c->md5Work;
    SslMd5_Init(md5);
    SslMd5_Update(md5, c->session->masterSecret, 0x30);
    SslMd5_Update(md5, tmp, 0x14);
    SslMd5_Final(md5, out);
}

void Ssl_DeriveMasterSecret(Ctx *c) {
    u8 buf[0x30];
    Ssl_DeriveSecretPart(buf, "A", c);
    Ssl_DeriveSecretPart(buf + 0x10, "BB", c);
    Ssl_DeriveSecretPart(buf + 0x20, "CCC", c);
    MI_CpuCopy8(buf, c->session->masterSecret, 0x30);
}
}

}

namespace Unk_ov065_02265a5c_Ns {



typedef SslConnection St;
typedef IpSocket Sess;

extern "C" {
extern void *(*sIpAlloc)(u32);
extern void (*sIpFree)(void *);


u8 *Tcp_Read(u32 *, Sess *);
void Tcp_Consume(u32, Sess *);
void Ssl_HandleClientHelloV2(St *, u8 *);
void Ssl_HandleClientHello(St *, u8 *);
void Ssl_HandleServerHello(St *, u8 *);
void Ssl_HandleCertificate(St *, u8 *);
void SslRsa_PrivateDecrypt(u8 *, u8 *, SslRsaPrivateKey *);
void Ssl_DeriveMasterSecret(St *);

u8 Ssl_ReadRecord(Sess *);
void Ssl_ProcessRecord(St *, u8 *);
s32 Ssl_ReadExact(u8 *, s32, Sess *);
s32 Ssl_EncryptRecord(St *, u8 *);
s32 Ssl_DecryptRecord(St *, u8 *);
s32 Ssl_DecryptInPlace(St *, u8 *, s32);
void Ssl_IncrementSeqNum(u8 *);
void Ssl_HandleFinished(St *, u8 *);
void Ssl_CalcFinishedSha1(St *, u8 *, u32);
void Ssl_CalcFinishedMd5(St *, u8 *, u32);
void Ssl_HandleClientKeyExchange(St *, u8 *);
void Ssl_DeriveKeyBlock(St *);

void Ssl_DeriveKeyBlock(St *st) {
    s32 a, b, c;
    s32 total;
    s32 i;
    s32 off;
    u8 tmp[0x1c];

    switch (st->cipherSuite) {
    case 4:
        a = 0x10;
        b = 0x10;
        c = 0;
        break;
    case 5:
        a = 0x14;
        b = 0x10;
        c = 0;
        break;
    }
    total = (a + b + c) * 2;
    i = 0;
    if (total > 0) {
        s32 off = 0;
        do {
            s32 j;
            SslSha1Context *sha1 = &st->sha1Work;
            SslSha1_Init(sha1);
            tmp[0] = 0x41 + i;
            j = 0;
            while (j < i + 1) {
                SslSha1_Update(sha1, tmp, 1);
                j++;
            }
            SslSha1_Update(sha1, st->session->masterSecret, 0x30);
            SslSha1_Update(sha1, st->serverRandom, 0x20);
            SslSha1_Update(sha1, st->clientRandom, 0x20);
            SslSha1_Final(sha1, tmp + 1);
            SslMd5Context *md5 = &st->md5Work;
            SslMd5_Init(md5);
            SslMd5_Update(md5, st->session->masterSecret, 0x30);
            SslMd5_Update(md5, tmp + 1, 0x14);
            SslMd5_Final(md5, st->keyBlock + off);
            off += 0x10;
            i++;
        } while (off < total);
    }
    if (st->isServer != 0) {
        st->readMacSecret = st->keyBlock;
        st->readKey = st->readMacSecret + a * 2;
        st->readIv = st->readKey + b * 2;
        st->writeMacSecret = st->keyBlock + a;
        st->writeKey = st->writeMacSecret + a + b;
        st->writeIv = st->writeKey + b + c;
    } else {
        st->writeMacSecret = st->keyBlock;
        st->writeKey = st->writeMacSecret + a * 2;
        st->writeIv = st->writeKey + b * 2;
        st->readMacSecret = st->keyBlock + a;
        st->readKey = st->readMacSecret + a + b;
        st->readIv = st->readKey + b + c;
    }
    SslRc4_Init(st->readCipher, st->readKey, 0x10);
    SslRc4_Init(st->writeCipher, st->writeKey, 0x10);
}

void Ssl_HandleClientKeyExchange(St *st, u8 *p) {
    SslRsa_PrivateDecrypt(st->session->masterSecret, p, st->serverKey);
    Ssl_DeriveMasterSecret(st);
    Ssl_DeriveKeyBlock(st);
    st->handshakeState = 5;
}

void Ssl_CalcFinishedMd5(St *st, u8 *out, u32 who) {
    u8 pad[0x30];
    SslMd5Context *md5 = &st->handshakeMd5;

    if ((st->isServer ^ who) != 0) {
        SslMd5_Update(md5, (const u8 *)"SRVR", 4);
    } else {
        SslMd5_Update(md5, (const u8 *)"CLNT", 4);
    }
    SslMd5_Update(md5, st->session->masterSecret, 0x30);
    MI_CpuFill8(pad, 0x36, 0x30);
    SslMd5_Update(md5, pad, 0x30);
    SslMd5_Final(md5, out);
    SslMd5_Init(md5);
    SslMd5_Update(md5, st->session->masterSecret, 0x30);
    MI_CpuFill8(pad, 0x5c, 0x30);
    SslMd5_Update(md5, pad, 0x30);
    SslMd5_Update(md5, out, 0x10);
    SslMd5_Final(md5, out);
}

void Ssl_CalcFinishedSha1(St *st, u8 *out, u32 who) {
    u8 pad[0x28];
    SslSha1Context *sha1 = &st->handshakeSha1;

    if ((st->isServer ^ who) != 0) {
        SslSha1_Update(sha1, (const u8 *)"SRVR", 4);
    } else {
        SslSha1_Update(sha1, (const u8 *)"CLNT", 4);
    }
    SslSha1_Update(sha1, st->session->masterSecret, 0x30);
    MI_CpuFill8(pad, 0x36, 0x28);
    SslSha1_Update(sha1, pad, 0x28);
    SslSha1_Final(sha1, out);
    SslSha1_Init(sha1);
    SslSha1_Update(sha1, st->session->masterSecret, 0x30);
    MI_CpuFill8(pad, 0x5c, 0x28);
    SslSha1_Update(sha1, pad, 0x28);
    SslSha1_Update(sha1, out, 0x14);
    SslSha1_Final(sha1, out);
}

void Ssl_HandleFinished(St *st, u8 *in) {
    u8 out[0x14];

    MI_CpuCopy8(&st->handshakeMd5, &st->md5Work, sizeof(SslMd5Context));
    Ssl_CalcFinishedMd5(st, out, 1);
    MI_CpuCopy8(&st->md5Work, &st->handshakeMd5, sizeof(SslMd5Context));
    if (memcmp(in, out, 0x10) != 0) {
        st->handshakeState = 9;
        return;
    }
    MI_CpuCopy8(&st->handshakeSha1, &st->sha1Work, sizeof(SslSha1Context));
    Ssl_CalcFinishedSha1(st, out, 1);
    MI_CpuCopy8(&st->sha1Work, &st->handshakeSha1, sizeof(SslSha1Context));
    if (memcmp(in + 0x10, out, 0x14) != 0) {
        st->handshakeState = 9;
        return;
    }
    st->handshakeState = 6;
}

void Ssl_IncrementSeqNum(u8 *p) {
    s32 i = 8;
    do {
        u32 v;
        p--;
        v = (u8)(*p + 1);
        *p = v;
        if (v != 0) {
            return;
        }
        i--;
    } while (i != 0);
}

s32 Ssl_DecryptInPlace(St *st, u8 *buf, s32 len) {
    SslRc4_Crypt(st->readCipher, buf, len);
    return len;
}

s32 Ssl_DecryptRecord(St *st, u8 *buf) {
    u8 digest[0x14];
    u8 pad[0x30];
    s32 len;
    s32 n;
    SslMd5Context *md5;
    SslSha1Context *sha1;

    len = Ssl_DecryptInPlace(st, buf + 5, (buf[3] << 8) + buf[4]);
    switch (st->cipherSuite) {
    case 4:
        len -= 0x10;
        buf[3] = len >> 8;
        buf[4] = len;
        md5 = &st->md5Work;
        SslMd5_Init(md5);
        SslMd5_Update(md5, st->readMacSecret, 0x10);
        MI_CpuFill8(pad, 0x36, 0x30);
        SslMd5_Update(md5, pad, 0x30);
        SslMd5_Update(md5, st->readSeqNum, 8);
        SslMd5_Update(md5, buf, 1);
        SslMd5_Update(md5, buf + 3, 2);
        SslMd5_Update(md5, buf + 5, len);
        SslMd5_Final(md5, digest);
        SslMd5_Init(md5);
        SslMd5_Update(md5, st->readMacSecret, 0x10);
        MI_CpuFill8(pad, 0x5c, 0x30);
        SslMd5_Update(md5, pad, 0x30);
        SslMd5_Update(md5, digest, 0x10);
        SslMd5_Final(md5, digest);
        n = 0x10;
        break;
    case 5:
        len -= 0x14;
        buf[3] = len >> 8;
        buf[4] = len;
        sha1 = &st->sha1Work;
        SslSha1_Init(sha1);
        SslSha1_Update(sha1, st->readMacSecret, 0x14);
        MI_CpuFill8(pad, 0x36, 0x28);
        SslSha1_Update(sha1, pad, 0x28);
        SslSha1_Update(sha1, st->readSeqNum, 8);
        SslSha1_Update(sha1, buf, 1);
        SslSha1_Update(sha1, buf + 3, 2);
        SslSha1_Update(sha1, buf + 5, len);
        SslSha1_Final(sha1, digest);
        SslSha1_Init(sha1);
        SslSha1_Update(sha1, st->readMacSecret, 0x14);
        MI_CpuFill8(pad, 0x5c, 0x28);
        SslSha1_Update(sha1, pad, 0x28);
        SslSha1_Update(sha1, digest, 0x14);
        SslSha1_Final(sha1, digest);
        n = 0x14;
        break;
    }
    if (memcmp(buf + 5 + len, digest, n) != 0) {
        st->handshakeState = 9;
    }
    Ssl_IncrementSeqNum(st->readSeqNum + 8);
    return len + 5;
}

s32 Ssl_EncryptRecord(St *st, u8 *buf) {
    u8 *mac = 0;
    u8 pad[0x30];
    s32 len;
    SslMd5Context *md5;
    SslSha1Context *sha1;

    len = (buf[3] << 8) + buf[4];
    mac = buf + 5 + len;
    switch (st->cipherSuite) {
    case 4:
        md5 = &st->md5Work;
        SslMd5_Init(md5);
        SslMd5_Update(md5, st->writeMacSecret, 0x10);
        MI_CpuFill8(pad, 0x36, 0x30);
        SslMd5_Update(md5, pad, 0x30);
        SslMd5_Update(md5, st->writeSeqNum, 8);
        SslMd5_Update(md5, buf, 1);
        SslMd5_Update(md5, buf + 3, 2);
        SslMd5_Update(md5, buf + 5, len);
        SslMd5_Final(md5, mac);
        SslMd5_Init(md5);
        SslMd5_Update(md5, st->writeMacSecret, 0x10);
        MI_CpuFill8(pad, 0x5c, 0x30);
        SslMd5_Update(md5, pad, 0x30);
        SslMd5_Update(md5, mac, 0x10);
        SslMd5_Final(md5, mac);
        len += 0x10;
        break;
    case 5:
        sha1 = &st->sha1Work;
        SslSha1_Init(sha1);
        SslSha1_Update(sha1, st->writeMacSecret, 0x14);
        MI_CpuFill8(pad, 0x36, 0x28);
        SslSha1_Update(sha1, pad, 0x28);
        SslSha1_Update(sha1, st->writeSeqNum, 8);
        SslSha1_Update(sha1, buf, 1);
        SslSha1_Update(sha1, buf + 3, 2);
        SslSha1_Update(sha1, buf + 5, len);
        SslSha1_Final(sha1, mac);
        SslSha1_Init(sha1);
        SslSha1_Update(sha1, st->writeMacSecret, 0x14);
        MI_CpuFill8(pad, 0x5c, 0x28);
        SslSha1_Update(sha1, pad, 0x28);
        SslSha1_Update(sha1, mac, 0x14);
        SslSha1_Final(sha1, mac);
        len += 0x14;
        break;
    }
    buf[3] = len >> 8;
    buf[4] = len;
    SslRc4_Crypt(st->writeCipher, buf + 5, len);
    Ssl_IncrementSeqNum(st->writeSeqNum + 8);
    return len + 5;
}

s32 Ssl_ReadExact(u8 *dst, s32 n, Sess *s) {
    u32 len;
    u8 *p;
    do {
        p = Tcp_Read(&len, s);
        if (len == 0) {
            return -1;
        }
        if (len > (u32)n) {
            len = n;
        }
        MI_CpuCopy8(p, dst, len);
        Tcp_Consume(len, s);
        dst += len;
        n -= len;
    } while (n > 0);
    return 0;
}

void Ssl_ProcessRecord(St *st, u8 *buf) {
    u32 len;
    u32 type;
    u8 *p;
    s32 h;
    u32 n;
    u32 n4;

    if (st->handshakeState == 9) {
        sIpFree(buf);
        return;
    }
    type = buf[0];
    len = (buf[3] << 8) + buf[4] + 5;
    if ((((u8)(st->handshakeState + 0xf9) <= 1) && type != 0x15) || (type == 0x15 && len > 7)) {
        len = Ssl_DecryptRecord(st, buf);
    }
    p = buf + 5;
    len -= 5;
    switch (type - 0x14) {
    case 0:
        MI_CpuFill8(st->readSeqNum, 0, 8);
        st->handshakeState = 7;
        break;
    case 1:
        if (p[0] == 2) {
            st->handshakeState = 9;
        }
        break;
    case 2:
        do {
            h = p[0];
            n = p[3] + ((p[1] << 16) + (p[2] << 8));
            p += 4;
            if (h > 0xb) goto hi;
            if (h >= 0xb) goto c11;
            if (h > 2) goto dflt;
            if (h < 1) goto dflt;
            if (h == 1) goto c1;
            switch (h) { case 2: goto c2; }
            goto dflt;
        hi:
            if (h > 0x14) goto dflt;
            if (h < 0xe) goto dflt;
            if (h == 0xe) goto c14;
            if (h == 0x10) goto c16;
            switch (h) { case 0x14: goto c20; }
            goto dflt;
        c1:
            if (st->isServer != 0 && st->handshakeState == 0) {
                Ssl_HandleClientHello(st, p);
            }
            goto join;
        c16:
            Ssl_HandleClientKeyExchange(st, p);
            goto join;
        c2:
            Ssl_HandleServerHello(st, p);
            goto join;
        c11:
            Ssl_HandleCertificate(st, p);
            goto join;
        c14:
            st->handshakeState = 4;
            goto join;
        c20:
            Ssl_HandleFinished(st, p);
            goto join;
        dflt:
            st->handshakeState = 9;
        join:
            n4 = n + 4;
            SslSha1_Update(&st->handshakeSha1, p - 4, n4);
            SslMd5_Update(&st->handshakeMd5, p - 4, n4);
            p += n;
            len -= n + 4;
            if (len == 0) {
                break;
            }
        } while (st->handshakeState != 9);
        break;
    case 3:
        st->recordBuf = buf;
        st->recordPos = 5;
        st->recordLen = len + 5;
        st->recordReady = 1;
        return;
    default:
        st->handshakeState = 9;
        break;
    }
    sIpFree(buf);
}

u8 Ssl_ReadRecord(Sess *s) {
    St *st = s->sslCtx;
    u32 len;
    u8 *p;
    u8 *buf;

    do {
        p = Tcp_Read(&len, s);
        if (len == 0) {
            st->handshakeState = 9;
            return 9;
        }
    } while (len < 5);

    if (p[0] == 0x80) {
        if (st->isServer != 0 && st->handshakeState == 0) {
            len = p[1];
            Tcp_Consume(2, s);
            buf = (u8 *)sIpAlloc(len);
            if (buf == 0) {
                st->handshakeState = 9;
                return 9;
            }
            if (Ssl_ReadExact(buf, len, s) == 0 && buf[0] == 1) {
                Ssl_HandleClientHelloV2(st, buf + 1);
            } else {
                st->handshakeState = 9;
            }
            SslSha1_Update(&st->handshakeSha1, buf, len);
            SslMd5_Update(&st->handshakeMd5, buf, len);
            sIpFree(buf);
        } else {
            st->handshakeState = 9;
        }
    } else {
        len = ((p[3] << 8) + p[4]) + 5;
        if (len > 0x4805) {
            st->handshakeState = 9;
            return 9;
        }
        buf = (u8 *)sIpAlloc(len);
        if (buf == 0) {
            st->handshakeState = 9;
            return 9;
        }
        if (Ssl_ReadExact(buf, len, s) != 0) {
            sIpFree(buf);
            st->handshakeState = 9;
            return 9;
        }
        Ssl_ProcessRecord(st, buf);
    }
    return st->handshakeState;
}
}

}

namespace Unk_ov065_02265130_Ns {



typedef IpSocket Sess;
typedef SslConnection Ctx;

extern "C" {
extern void *(*sIpAlloc)(u32);
extern void (*sIpFree)(void *);
extern u32 gSslRsaThreadPriority;
extern u16 sSslCipherSuites[2];
extern IpRandStateSigned sIpRandState;
extern u32 sSslSessionIdCounter;
extern u8 sSslRandPool[20];
extern u8 sSslRandSeeded;
extern OSThreadInfo data_021fcc2c;

u32 OS_DisableInterrupts();
void OS_RestoreInterrupts(u32);
s32 _s32_div_f(s32, s32);
s64 _ll_mul(s64, s64);
u32 OS_GetThreadPriority(OSThread *);
void OS_SetThreadPriority(OSThread *, u32);

s32 Tcp_Connect(Sess *);
void Tcp_Listen(Sess *);
void Tcp_Shutdown(Sess *);
u32 Tcp_Write(u8 *, u32, u8 *, u32, Sess *);
void Ssl_DeriveKeyBlock(Ctx *);
void Ssl_DeriveMasterSecret(Ctx *);
void Ssl_CalcFinishedMd5(Ctx *, u8 *, u32);
void Ssl_CalcFinishedSha1(Ctx *, u8 *, u32);
u8 Ssl_ReadRecord(Sess *);
s32 Ssl_EncryptRecord(Ctx *, u8 *);

s32 Ssl_Connect(Sess *);
s32 Ssl_ClientHandshake(Sess *);
void Ssl_Accept(Sess *);
s32 Ssl_ServerHandshake(Sess *);
s32 Ssl_WaitPeerFinished(Sess *);
void Ssl_SendClientKeyExchange(Sess *);
void Ssl_SendClientHello(Sess *);
void Ssl_SendFinished(Sess *);
s32 Ssl_SendServerHello(Sess *);
void SslRand_AddSeed(u8 *, u32);
void SslRand_GetNonZeroBytes(u8 *, s32);

void SslRand_GetNonZeroBytes(u8 *out, s32 n) {
    u32 seed;
    u8 buf[20];
    SslSha1Context h;
    s32 i;
    s32 j;
    u32 z;
    if (sSslRandSeeded == 0) {
        sIpRandState.x = sIpRandState.add + _ll_mul(sIpRandState.mul, sIpRandState.x);
        seed = (u32)(sIpRandState.x >> 32);
        SslRand_AddSeed((u8 *)&seed, 4);
    }
    j = 0x14;
    i = 0;
    for (; i < n;) {
        if (j == 0x14) {
            u32 th;
            s32 k;
            u32 c;
            u8 *b;
            u8 *a;
            u32 v;
            SslSha1_Init(&h);
            th = OS_DisableInterrupts();
            SslSha1_Update(&h, sSslRandPool, 0x14);
            SslSha1_FinalRaw(&h, buf);
            c = 1;
            k = 0x13;
            b = buf + 0x13;
            a = sSslRandPool + 0x13;
            for (; k >= 0; k--) {
                v = *a + *b + c;
                *a = v;
                c = v >> 8;
                b--;
                a--;
            }
            seed = v;
            OS_RestoreInterrupts(th);
            j = 0;
        }
        if (buf[j] != 0) {
            out[i] = buf[j];
            i++;
        }
        j++;
    }
}

void SslRand_AddSeed(u8 *p, u32 n) {
    SslSha1Context h;
    u32 th;
    SslSha1_Init(&h);
    th = OS_DisableInterrupts();
    SslSha1_Update(&h, sSslRandPool, 0x14);
    SslSha1_Update(&h, p, n);
    SslSha1_Final(&h, sSslRandPool);
    OS_RestoreInterrupts(th);
    sSslRandSeeded = 1;
}

s32 Ssl_SendServerHello(Sess *s) {
    Ctx *ctx = s->sslCtx;
    SslServerCert *cert = ctx->serverCert;
    s32 cl;
    u32 t;
    u8 *buf;
    u8 *q;
    s32 len;
    if (cert) {
        cl = cert->length;
    } else {
        cl = 0;
    }
    t = Ssl_GetUnixTime();
    ctx->serverRandom[0] = t >> 24;
    ctx->serverRandom[1] = t >> 16;
    ctx->serverRandom[2] = t >> 8;
    ctx->serverRandom[3] = t;
    SslRand_GetNonZeroBytes(ctx->serverRandom + 4, 0x1c);
    buf = (u8 *)sIpAlloc(cl + 0x9d);
    if (buf == 0) {
        ctx->handshakeState = 9;
        return 1;
    }
    q = buf + 5;
    q[0] = 2;
    q[1] = 0;
    q[2] = 0;
    q[3] = 0x46;
    q[4] = 3;
    q[5] = 0;
    MI_CpuCopy8(ctx->serverRandom, q + 6, 0x20);
    q[0x26] = 0x20;
    if (ctx->session) {
        MI_CpuCopy8(ctx->session, q + 0x27, 0x20);
        q += 0x47;
        ctx->resumed = 1;
    } else {
        SslRand_GetNonZeroBytes(q + 0x27, 0x1c);
        t = sSslSessionIdCounter;
        q[0x43] = t >> 24;
        q[0x44] = t >> 16;
        q[0x45] = t >> 8;
        q += 0x46;
        *q++ = t;
        ctx->session = SslSession_Add(q - 0x20);
        sSslSessionIdCounter++;
        ctx->resumed = 0;
    }
    q[0] = ctx->cipherSuite >> 8;
    q[1] = ctx->cipherSuite;
    q += 2;
    *q++ = 0;
    if (ctx->resumed == 0) {
        if (cl != 0) {
            q[0] = 0xb;
            q[1] = (cl + 6) >> 16;
            q[2] = (cl + 6) >> 8;
            q[3] = cl + 6;
            q[4] = (cl + 3) >> 16;
            q[5] = (cl + 3) >> 8;
            q[6] = cl + 3;
            q[7] = cl >> 16;
            q[8] = cl >> 8;
            q += 9;
            *q++ = cl;
            MI_CpuCopy8(cert->data, q, cl);
            q += cl;
        }
        q[0] = 0xe;
        q[1] = 0;
        q[2] = 0;
        q += 3;
        *q++ = 0;
    }
    len = q - buf - 5;
    buf[0] = 0x16;
    buf[1] = 3;
    buf[2] = 0;
    buf[3] = len >> 8;
    buf[4] = len;
    SslSha1_Update(&ctx->handshakeSha1, buf + 5, len);
    SslMd5_Update(&ctx->handshakeMd5, buf + 5, len);
    Tcp_Write(buf, len + 5, 0, 0, s);
    sIpFree(buf);
    return ctx->resumed;
}

void Ssl_SendFinished(Sess *s) {
    Ctx *ctx = s->sslCtx;
    u8 *b;
    b = (u8 *)sIpAlloc(0x83);
    if (b == 0) {
        ctx->handshakeState = 9;
        return;
    }
    b[0] = 0x14;
    b[1] = 3;
    b[2] = 0;
    b[3] = 0;
    b[4] = 1;
    b[5] = 1;
    MI_CpuFill8(ctx->writeSeqNum, 0, 8);
    b[6] = 0x16;
    b[7] = 3;
    b[8] = 0;
    b[9] = 0;
    b[10] = 0x28;
    b[11] = 0x14;
    b[12] = 0;
    b[13] = 0;
    b[14] = 0x24;
    MI_CpuCopy8(&ctx->handshakeMd5, &ctx->md5Work, sizeof(SslMd5Context));
    Ssl_CalcFinishedMd5(ctx, b + 0xf, 0);
    MI_CpuCopy8(&ctx->md5Work, &ctx->handshakeMd5, sizeof(SslMd5Context));
    MI_CpuCopy8(&ctx->handshakeSha1, &ctx->sha1Work, sizeof(SslSha1Context));
    Ssl_CalcFinishedSha1(ctx, b + 0x1f, 0);
    MI_CpuCopy8(&ctx->sha1Work, &ctx->handshakeSha1, sizeof(SslSha1Context));
    SslSha1_Update(&ctx->handshakeSha1, b + 0xb, 0x28);
    SslMd5_Update(&ctx->handshakeMd5, b + 0xb, 0x28);
    Tcp_Write(b, Ssl_EncryptRecord(ctx, b + 6) + 6, 0, 0, s);
    sIpFree(b);
}

void Ssl_SendClientHello(Sess *s) {
    Ctx *ctx = s->sslCtx;
    u8 *buf;
    u8 *q;
    u32 t;
    s32 len;
    u32 i;
    u16 *tp;
    buf = (u8 *)sIpAlloc(0x98);
    if (buf == 0) {
        ctx->handshakeState = 9;
        return;
    }
    q = buf + 9;
    buf[9] = 3;
    q[1] = 0;
    t = Ssl_GetUnixTime();
    ctx->clientRandom[0] = t >> 24;
    ctx->clientRandom[1] = t >> 16;
    ctx->clientRandom[2] = t >> 8;
    ctx->clientRandom[3] = t;
    SslRand_GetNonZeroBytes(&ctx->clientRandom[4], 0x1c);
    MI_CpuCopy8(ctx->clientRandom, q + 2, 0x20);
    ctx->session = SslSession_FindByPeer(s->remoteAddr, s->remotePort);
    if (ctx->session) {
        q[0x22] = 0x20;
        MI_CpuCopy8(ctx->session, q + 0x23, 0x20);
        q += 0x43;
    } else {
        q += 0x22;
        *q++ = 0;
    }
    i = 0;
    *q++ = 0;
    *q++ = 4;
    tp = sSslCipherSuites;
    for (; i < 2; i++) {
        *q++ = *tp >> 8;
        *q++ = *tp;
        tp++;
    }
    q[0] = 1;
    q[1] = 0;
    q += 2;
    len = q - buf - 5;
    buf[0] = 0x16;
    buf[1] = 3;
    buf[2] = 0;
    buf[3] = len >> 8;
    buf[4] = len;
    buf[5] = 1;
    buf[6] = (len - 4) >> 16;
    buf[7] = (len - 4) >> 8;
    buf[8] = len - 4;
    Tcp_Write(buf, len + 5, 0, 0, s);
    SslMd5_Update(&ctx->handshakeMd5, buf + 5, len);
    SslSha1_Update(&ctx->handshakeSha1, buf + 5, len);
    sIpFree(buf);
}

void Ssl_SendClientKeyExchange(Sess *s) {
    Ctx *ctx = s->sslCtx;
    s32 n;
    s32 cnt;
    u16 *p0;
    u16 *p1;
    u16 *p2;
    u8 *buf1;
    u16 *p3;
    u8 *buf2;
    u8 *q;
    ctx->session->masterSecret[0] = 3;
    ctx->session->masterSecret[1] = 0;
    SslRand_GetNonZeroBytes(ctx->session->masterSecret + 2, 0x2e);
    n = ctx->peerModulusLen;
    cnt = _s32_div_f(n * 2, 2);
    buf1 = (u8 *)sIpAlloc(n);
    if (buf1 == 0) {
        ctx->handshakeState = 9;
        return;
    }
    buf1[0] = 0;
    buf1[1] = 2;
    SslRand_GetNonZeroBytes(buf1 + 2, n - 0x33);
    buf1[n - 0x31] = 0;
    MI_CpuCopy8(ctx->session->masterSecret, buf1 + n - 0x30, 0x30);
    p0 = (u16 *)sIpAlloc(cnt * 8);
    if (p0 == 0) {
        sIpFree(buf1);
        ctx->handshakeState = 9;
        return;
    }
    p1 = p0 + cnt;
    p2 = p1 + cnt;
    p3 = p2 + cnt;
    SslBigNum_FromBytes(p1, buf1, n, cnt);
    SslBigNum_FromBytes(p2, ctx->peerExponent, ctx->peerExponentLen, cnt);
    SslBigNum_FromBytes(p3, ctx->peerModulus, n, cnt);
    if (gSslRsaThreadPriority < 0x20) {
        OSThread *th = data_021fcc2c.current;
        u32 pr = OS_GetThreadPriority(th);
        OS_SetThreadPriority(th, gSslRsaThreadPriority);
        SslBigNum_ModExp(p0, p1, p2, cnt, p3);
        OS_SetThreadPriority(th, pr);
    } else {
        SslBigNum_ModExp(p0, p1, p2, cnt, p3);
    }
    buf2 = (u8 *)sIpAlloc(n + 0x49);
    if (buf2 == 0) {
        sIpFree(buf1);
        sIpFree(p0);
        ctx->handshakeState = 9;
        return;
    }
    buf2[0] = 0x16;
    buf2[1] = 3;
    buf2[2] = 0;
    buf2[3] = (n + 4) >> 8;
    buf2[4] = n + 4;
    buf2[5] = 0x10;
    buf2[6] = n >> 16;
    buf2[7] = n >> 8;
    q = buf2 + 9;
    buf2[8] = n;
    if ((n & 1) != 0) {
        *q = p0[_s32_div_f(n, 2)];
        q++;
    }
    {
        s32 i;
        u16 *pp;
        i = _s32_div_f(n, 2) - 1;
        if (i >= 0) {
            pp = p0 + i;
            do {
                *q++ = *pp >> 8;
                *q++ = *pp;
                pp--;
                i--;
            } while (i >= 0);
        }
    }
    Tcp_Write(buf2, n + 9, 0, 0, s);
    SslMd5_Update(&ctx->handshakeMd5, buf2 + 5, (u32)n + 4);
    SslSha1_Update(&ctx->handshakeSha1, buf2 + 5, n + 4);
    sIpFree(buf2);
    sIpFree(p0);
    sIpFree(buf1);
}

s32 Ssl_WaitPeerFinished(Sess *s) {
    if (Ssl_ReadRecord(s) != 7) {
        return 1;
    }
    if (Ssl_ReadRecord(s) != 6) {
        return 1;
    }
    return 0;
}

s32 Ssl_ServerHandshake(Sess *s) {
    if (Ssl_ReadRecord(s) != 1) {
        return 1;
    }
    if (Ssl_SendServerHello(s)) {
        Ssl_DeriveKeyBlock(s->sslCtx);
        Ssl_SendFinished(s);
        if (Ssl_WaitPeerFinished(s)) {
            return 1;
        }
    } else {
        if (Ssl_ReadRecord(s) != 5) {
            return 1;
        }
        if (Ssl_WaitPeerFinished(s)) {
            return 1;
        }
        Ssl_SendFinished(s);
    }
    return 0;
}

void Ssl_Accept(Sess *s) {
    Ctx *ctx = s->sslCtx;
    for (;;) {
        Tcp_Listen(s);
        ctx->handshakeState = 0;
        ctx->isServer = 1;
        SslSha1_Init(&ctx->handshakeSha1);
        SslMd5_Init(&ctx->handshakeMd5);
        if (Ssl_ServerHandshake(s) == 0) {
            ctx->handshakeState = 8;
            return;
        }
        Tcp_Shutdown(s);
        s->remotePort = s->boundRemotePort;
        s->remoteAddr = s->boundRemoteAddr;
    }
}

s32 Ssl_ClientHandshake(Sess *s) {
    Ctx *ctx = s->sslCtx;
    s32 r;
    Ssl_SendClientHello(s);
    do {
        r = Ssl_ReadRecord(s);
        if (r == 9) {
            return 1;
        }
    } while (r != 4 && ctx->resumed == 0);
    if (ctx->resumed != 0) {
        Ssl_DeriveKeyBlock(ctx);
        if (Ssl_WaitPeerFinished(s)) {
            return 1;
        }
        Ssl_SendFinished(s);
    } else {
        ctx->session->peerAddr = s->remoteAddr;
        ctx->session->peerPort = s->remotePort;
        Ssl_SendClientKeyExchange(s);
        Ssl_DeriveMasterSecret(ctx);
        Ssl_DeriveKeyBlock(ctx);
        Ssl_SendFinished(s);
        if (Ssl_WaitPeerFinished(s)) {
            return 1;
        }
    }
    ctx->handshakeState = 8;
    return 0;
}

s32 Ssl_Connect(Sess *s) {
    Ctx *ctx = s->sslCtx;
    if (s->state != 4) {
        if (Tcp_Connect(s)) {
            return 1;
        }
    }
    ctx->handshakeState = 0;
    ctx->isServer = 0;
    SslSha1_Init(&ctx->handshakeSha1);
    SslMd5_Init(&ctx->handshakeMd5);
    return Ssl_ClientHandshake(s);
}
}

}

namespace Unk_ov065_0226482c_Ns {












extern "C" {
extern u32 sGateway;
extern u32 sNetmask;
extern u32 gOwnIp;
extern u32 sIpThreadPriority;
extern u8 sIpRecvThread[];
extern u8 sIpTimerThread[];
extern void *sRecvRingWaiter;
extern u8 *sRecvRingBuf;
extern u32 sRecvRingSize;
extern void (*sIpIdleCallback)(void);
extern u32 sIpTimerStopRequest;
extern u32 sIpStackStatus;
extern u32 sDnsServers[2];
extern u32 sDhcpServerId;
extern u8 sArpCache[];
extern OSThreadInfo data_021fcc2c;
extern IpFragEntry sIpFragTable[8];
extern void (*sIpFree)(void *);
extern u32 sIpYieldMode;
extern SslSession sSslSessionCache[4];
extern void *(*sIpAlloc)(u32);
extern void *(*sAddrConfiguredCallback)(void);
extern s32 (*sIpLinkCheckCallback)(void);
extern u32 sIpStackFlags;
extern u16 sMss;
extern u32 sDhcpRequestedIp;
extern u32 sRecvRingRead;
extern u32 sRecvRingWrite;
extern u16 sNextEphemeralPort;
extern u8 sOwnMac[];
extern u8 sArpConflict;
extern u8 sIpRecvThreadStack[];

void IpStack_RecvThreadMain(void);
void IpStack_TimerThreadMain(void);
s32 Ssl_EncryptRecord(SslConnection *, u8 *);
u32 Tcp_Write(u8 *, u32, u8 *, u32, IpSocket *);
u8 *Tcp_Read(u32 *, IpSocket *);
void Tcp_Consume(u32, IpSocket *);
void Ssl_ProcessRecord(SslConnection *, u8 *);
s32 Ssl_ReadExact(u8 *, s32, IpSocket *);
u8 Ssl_ReadRecord(IpSocket *);

u32 OS_DisableInterrupts(void);
void OS_RestoreInterrupts(u32);
void OS_SetThreadPriority(OSThread *, u32);
void OS_JoinThread(void *);
void OS_DestroyThread(void *);
s32 OS_IsThreadTerminated(void *);
void OS_WakeupThreadDirect(void *);
void OS_Sleep(void);
void OS_CreateThread(void *, void *, u32, void *, u32, u32);
void OS_GetMacAddress(void *);

u32 Ip_ChecksumAdd(u8 *p, u32 len, u32 sum);
s32 Ip_IsOnLocalNet(u32 a);
void IpStack_ResetAddress(u32 a);
s32 IpStack_RequestStop(void);
void Ssl_ClearSessionCache(void);
void Ssl_ReceiveRecordPart(IpSocket *o);
s32 IpStack_ReturnTrue(void);
void IpStack_Nop(void);
}

extern "C" {

u8 *Ssl_Read(u32 *out, IpSocket *o) {
    SslConnection *c = o->sslCtx;
    u8 **pb;
    if (c->recordBuf != 0 && c->recordReady == 0) {
        if (Ssl_ReadExact(c->recordBuf + c->recordPos, c->recordLen - c->recordPos, o) != 0) {
            sIpFree(c->recordBuf);
            c->recordBuf = 0;
            *out = 0;
            return 0;
        }
        Ssl_ProcessRecord(c, c->recordBuf);
        if (c->recordReady == 0) {
            c->recordBuf = 0;
        }
    }
    pb = &c->recordBuf;
    if (*pb == 0) {
        do {
            if (Ssl_ReadRecord(o) == 9) {
                *out = 0;
                return 0;
            }
        } while (*pb == 0);
    }
    *out = c->recordLen - c->recordPos;
    return c->recordBuf + c->recordPos;
}

void Ssl_Consume(u32 n, IpSocket *o) {
    SslConnection *c = o->sslCtx;
    if (n >= c->recordLen - c->recordPos) {
        if (c->recordBuf != 0) {
            sIpFree(c->recordBuf);
        }
        c->recordBuf = 0;
    } else {
        c->recordPos += n;
    }
}

void Ssl_ReceiveRecordPart(IpSocket *o) {
    SslConnection *c = o->sslCtx;
    u32 len;
    u8 *src;
    BOOL flag;
    if (c->recordBuf == 0) {
        if (o->rxLen < 5) {
            return;
        }
        src = Tcp_Read(&len, o);
        len = (src[3] << 8) + src[4] + 5;
        if (len > 0x4805) {
            c->handshakeState = 9;
            return;
        }
        c->recordBuf = (u8 *)sIpAlloc(len);
        if (c->recordBuf == 0) {
            c->handshakeState = 9;
            return;
        }
        c->recordLen = len;
        c->recordPos = 0;
        c->recordReady = 0;
    } else {
        if (o->rxLen == 0) {
            return;
        }
    }
    src = Tcp_Read(&len, o);
    {
        u32 avail = c->recordLen - c->recordPos;
        if (len >= avail) {
            len = avail;
            flag = TRUE;
        } else {
            flag = FALSE;
        }
    }
    MI_CpuCopy8(src, c->recordBuf + c->recordPos, len);
    Tcp_Consume(len, o);
    if (flag) {
        Ssl_ProcessRecord(c, c->recordBuf);
        if (c->recordReady != 0) {
            return;
        }
        c->recordBuf = 0;
        return;
    }
    c->recordPos += len;
    return;
}

s32 Ssl_GetReadLength(IpSocket *o) {
    SslConnection *c = o->sslCtx;
    if (c->recordBuf == 0 || c->recordReady == 0) {
        Ssl_ReceiveRecordPart(o);
    }
    if (c->recordBuf != 0 && c->recordReady != 0) {
        return c->recordLen - c->recordPos;
    }
    if (c->recordBuf == 0) {
        if (o->state != 4 || c->handshakeState == 9) {
            return -1;
        }
    }
    return 0;
}

u32 Ssl_Write(u8 *p1, u32 n1, u8 *p2, u32 n2, IpSocket *o) {
    SslConnection *c = o->sslCtx;
    s32 total = n1 + n2;
    u32 c2;
    u32 sent = 0;
    u32 z1 = 0, z2 = 0, z3 = 0;
    u8 *rec;
    s32 chunk;
    for (;;) {
        u32 c1, len;
        if (total > 0xb4f) {
            chunk = 0xb4f;
        } else {
            chunk = total;
        }
        rec = (u8 *)sIpAlloc(chunk + 0x19);
        if (rec == 0) {
            break;
        }
        c1 = n1 >= chunk ? chunk : n1;
        c2 = chunk - c1;
        MI_CpuCopy8(p1, rec + 5, c1);
        p1 += c1;
        n1 -= c1;
        MI_CpuCopy8(p2, rec + 5 + c1, c2);
        p2 += c2;
        rec[0] = 0x17;
        rec[1] = 3;
        rec[2] = z1;
        rec[3] = chunk >> 8;
        rec[4] = chunk;
        len = Ssl_EncryptRecord(c, rec);
        if (Tcp_Write(rec, len, NULL, z2, o) < len) {
            chunk = z3;
        }
        sIpFree(rec);
        total -= chunk;
        sent += chunk;
        if (total == 0) {
            break;
        }
        if (chunk == 0) {
            break;
        }
    }
    return sent;
}

void Ssl_Shutdown(IpSocket *o) {
    SslConnection *c = o->sslCtx;
    if (c->handshakeState == 8) {
        u8 b[32];
        u32 n;
        b[0] = 0x15;
        b[1] = 3;
        b[2] = 0;
        b[3] = 0;
        b[4] = 2;
        b[5] = 1;
        b[6] = 0;
        n = Ssl_EncryptRecord(c, b);
        Tcp_Write(b, n, 0, 0, o);
    }
    c->handshakeState = 0;
}

void Ssl_EnableOnCurrentSocket(u32 v) {
    OSi_ReferSymbol(0);
    IpSocket *s = (IpSocket *)data_021fcc2c.current->specific[0];
    if (s != 0) {
        s->useSsl = v;
    }
}

void Ssl_ExpireSessions(s32 now) {
    s32 i;
    SslSession *e;
    for (i = 0, e = sSslSessionCache; i < 4; e++, i++) {
        if (e->inUse != 0) {
            if ((s32)(now - e->lastUsed) > 0xef) {
                e->inUse = 0;
            }
        }
    }
}

void Ssl_ClearSessionCache(void) {
    MI_CpuFill8(sSslSessionCache, 0, sizeof(sSslSessionCache));
}
}

}

extern "C" u8 sSslNoSession[0x5c] = {0};
extern "C" u8 sSslRandPool[0x14] = {0};
extern "C" u32 sSslSessionIdCounter = 0;
extern "C" u8 sSslOidNone[4] = {0xff, 0xff, 0xff, 0};
extern "C" u8 sSslOidCommonName[4] = {0x55, 4, 3, 0};
extern "C" u32 gSslRsaThreadPriority = 0xffffffff;
extern "C" u16 sSslCipherSuites[2] = {4, 5};
extern "C" u8 sSslOidRsaX500[8] = {0x55, 8, 1, 1, 0, 0, 0, 0};
extern "C" u8 sSslOidRsaEncryption[12] = {0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 1, 1, 1, 0, 0, 0};
extern "C" u8 sSslOidMd5WithRsa[12] = {0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 1, 1, 4, 0, 0, 0};
extern "C" u8 sSslRandSeeded = 0;
extern "C" u8 sSslOidSha1WithRsa[12] = {0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 1, 1, 5, 0, 0, 0};
extern "C" char *sSslCertOidTable[6] = {(char *)sSslOidNone, (char *)sSslOidRsaEncryption, (char *)sSslOidRsaX500, (char *)sSslOidMd5WithRsa, (char *)sSslOidSha1WithRsa, (char *)sSslOidCommonName};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov065_02264d0c) {
    HOST_OVERLAY_VAR(sSslNoSession),
    HOST_OVERLAY_VAR(sSslRandPool),
    HOST_OVERLAY_VAR(sSslSessionIdCounter),
    HOST_OVERLAY_VAR(sSslOidNone),
    HOST_OVERLAY_VAR(sSslOidCommonName),
    HOST_OVERLAY_VAR(gSslRsaThreadPriority),
    HOST_OVERLAY_VAR(sSslCipherSuites),
    HOST_OVERLAY_VAR(sSslOidRsaX500),
    HOST_OVERLAY_VAR(sSslOidRsaEncryption),
    HOST_OVERLAY_VAR(sSslOidMd5WithRsa),
    HOST_OVERLAY_VAR(sSslRandSeeded),
    HOST_OVERLAY_VAR(sSslOidSha1WithRsa),
    HOST_OVERLAY_VAR(sSslCertOidTable),
    HOST_OVERLAY_VARS_END
};
