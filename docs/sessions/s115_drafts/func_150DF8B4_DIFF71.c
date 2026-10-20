typedef struct { f32 x, y, z; } V3f;
s32 func_15046C6C(V3f *, s32, f32, f32 *);
s32 func_150E892C(V3f *, s16, u8, u8);
s32 func_151A9DE4(V3f *, f32, s32, f32 *, s32, s32, s32, s32, s32);

void func_150DF8B4(u8 *arg0) {
    s32 pad[9];
    f32 h;
    u8 hit;
    V3f g;
    V3f q;
    V3f c;

    hit = 0;
    q.x = ((V3f *)(arg0 + 0x28))->x;
    q.y = ((V3f *)(arg0 + 0x28))->y + 500.0f;
    q.z = ((V3f *)(arg0 + 0x28))->z;
    if (func_15046C6C(&q, 0, q.y - 1000.0f, &h) != 0) {
        V3f *src = (V3f *)(arg0 + 0x28);
        g.x = src->x;
        g.y = h;
        g.z = src->z;
        hit = 1;
    }
    func_150E892C(hit ? &g : (V3f *)(arg0 + 0x28), func_150ADA20() % 62U + 0x78, arg0[0xC], arg0[1]);
    c = *(hit ? &g : (V3f *)(arg0 + 0x28));
    c.y += 500.0f;
    func_151A9DE4(&c, c.y - 1000.0f, 0x437A0000, &h, func_150ADA20() % 3U + 3, 1, 0, arg0[0xC], arg0[1]);
}
