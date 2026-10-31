typedef unsigned char u8;
typedef unsigned int u32;

extern const u32 data_02135cd8[4][4];

u32 OBJSizeToShape(const u8 *p)
{
    return data_02135cd8[p[1]][p[0]];
}

const u32 data_02135cd8[4][4] = {
    {0x00000000, 0x00004000, 0x40004000, 0x00000000},
    {0x00008000, 0x40000000, 0x80004000, 0x00000000},
    {0x40008000, 0x80008000, 0x80000000, 0xc0004000},
    {0x00000000, 0x00000000, 0xc0008000, 0xc0000000},
};
