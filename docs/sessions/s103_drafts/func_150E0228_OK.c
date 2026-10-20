typedef struct {
    u8 pad0[4];
    f32 u4;
    u8 pad8[0x5C];
    f32 u64;
    u8 pad68[0x14];
    f32 u7C;
} SE0228;

void func_150E0228(SE0228 *arg0) {
    f32 t;
    f32 d;
    f32 m;

    m = 0.55f;
    d = arg0->u64 * D_800BE9E4;
    arg0->u4 += d;
    if (arg0->u4 < 11.0f) {
        t = m;
        arg0->u7C = t;
    } else if (arg0->u4 > 55.0f) {
        t = -m;
        arg0->u7C = t;
    } else {
        t = arg0->u7C;
    }
    if (arg0->u64 < t) {
        arg0->u64 += 0.05f;
        if (t < arg0->u64) {
            arg0->u64 = t;
        }
    } else if (t < arg0->u64) {
        arg0->u64 -= 0.05f;
        if (arg0->u64 < t) {
            arg0->u64 = t;
        }
    }
}
