typedef struct { f32 x, y, z; u8 padC[0xC]; } E5128;
s32 func_151B5128(u8 *arg0)
{
    s32 i;
    
    f32 x = -1000.0f;
    i = 0;
    do {
        ((E5128 *)(arg0 + 0x48))[i].x = x;
        ((E5128 *)(arg0 + 0x48))[i].y = 0.0f;
        ((E5128 *)(arg0 + 0x48))[i].z = 0.0f;
        x += 222.22223f;
    } while (++i < 10);
    arg0[0x10] &= ~2;
    return 1;
}
