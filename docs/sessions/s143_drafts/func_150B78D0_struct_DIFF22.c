typedef struct { u8 pad0[0x18]; s16 x0; s16 y0; s32 d; s16 x1; s16 y1; s16 t; u8 pad26[6]; f32 fx; f32 fy; } S78D0;
void func_150B78D0(S78D0 *arg0)
{
    s32 x0 = arg0->x0;
    s32 y0 = arg0->y0;
    s32 r = (arg0->t << 16) / arg0->d;
    arg0->fx = (((arg0->x1 - x0) * r) >> 16) + x0;
    arg0->fy = (((arg0->y1 - y0) * r) >> 16) + y0;
}
