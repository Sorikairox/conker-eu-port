typedef struct { u8 pad0[0xE]; s16 x; u8 pad10[2]; s16 y; u8 pad14[0x12]; s8 vxh; u8 vxl; s8 vyh; u8 vyl; u8 xf; u8 yf; } Mov_1516FDD4;
extern s32 D_800BE9E4;
void func_1516FDD4(u8 *arg0) {
    Mov_1516FDD4 *a = (Mov_1516FDD4 *)arg0;
    s32 x;
    s32 y;
    s32 v;

    v = a->vxh;
    v = (v << 8) + a->vxl;
    x = a->x;
    x = (x << 8) + a->xf;
    x += v * D_800BE9E4;
    a->x = x >> 8;
    a->xf = x;
    v = a->vyh;
    v = (v << 8) + a->vyl;
    y = a->y;
    y = (y << 8) + a->yf;
    y += v * D_800BE9E4;
    a->y = y >> 8;
    a->yf = y;
}
