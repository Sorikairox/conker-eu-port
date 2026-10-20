void func_1511B4B8(u8 *arg0) {
    f32 sp1C;
    f32 t;
    f32 tg;
    f32 cur;
    f32 d;
    u32 r;
    s32 v;

    t = *(s32 *)(arg0 + 0x3C);
    cur = *(f32 *)(arg0 + 0x7C);
    tg = 75.0f * t * 0.01f;
    if (tg != cur) {
        if (fabsf((tg - cur)) < 1.0f) {
            *(f32 *)(arg0 + 0x7C) = tg;
        } else {
            v = 1;
            if ((tg - cur) < 0.0f) {
                v = -1;
            }
            *(f32 *)(arg0 + 0x7C) = cur + v;
        }
        *(f32 *)(arg0 + 0x80) = 0.0f;
    } else {
        sp1C = t;
        r = func_150ADA20() % 1000U;
        if ((s32) r < 0x1F4) {
            *(f32 *)(arg0 + 0x84) = (f32) r * 5.0f * t * 0.002f * 0.01f;
        }
        *(f32 *)(arg0 + 0x80) += (*(f32 *)(arg0 + 0x84) - *(f32 *)(arg0 + 0x80)) * 0.4f;
    }
    *(f32 *)(arg0 + 0) = *(f32 *)(arg0 + 0x7C) + *(f32 *)(arg0 + 0x80);
}
