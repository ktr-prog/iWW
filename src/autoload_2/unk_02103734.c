

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef int s32;
typedef struct BitReader { const u8 *src; s8 availableBits; u8 bits; u8 padding_[2]; } BitReader;

static inline void BitReaderReload(BitReader *reader)
{
    reader->bits = *(reader->src)++;
    reader->availableBits = 8;
}

u32 NNSi_G2dBitReaderRead(BitReader *reader, int nBits)
{
    u32 val = reader->bits;
    int nAvlBits = reader->availableBits;

    if (nAvlBits < nBits) {
        int lack = nBits - nAvlBits;
        val <<= lack;
        BitReaderReload(reader);
        val |= NNSi_G2dBitReaderRead(reader, lack);
    } else {
        int rest = nAvlBits - nBits;
        val >>= rest;
        reader->availableBits = (s8)rest;
    }
    val &= 0xff >> (8 - nBits);
    return val;
}
