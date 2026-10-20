typedef struct {
    f32 x, y, z;
    f32 len;
    f32 unk10;
    f32 unk14;
    u8 pad18[0x10];
} SegF6D0;

s32 func_151CF6D0(u8 *arg0) {
    u8 *def = *(u8 **)(arg0 + 0x98);
    SegF6D0 *segs = *(SegF6D0 **)(arg0 + 0x94);
    s32 i;
    s32 prev;
    f32 total;
    f32 l;
    f32 frac;
    s8 j;
    f32 amp;
    f32 ph;
    f32 max;

    if (*(s8 *)(arg0 + 0x2C) >= 2) {
        total = 0.0f;
        max = *(f32 *)(def + 0x20);
        i = *(s8 *)(arg0 + 0x2E) - 1;
        if (i < 0) {
            i = arg0[0x25] - 1;
        }
        while (i != *(s8 *)(arg0 + 0x2D)) {
            prev = i;
            i--;
            if (i < 0) {
                i = arg0[0x25] - 1;
            }
            l = segs[prev].len;
            total += l;
            if (max < total) {
                if (l != 0.0f) {
                    frac = (total - max) / l;
                    segs[i].x -= (segs[i].x - segs[prev].x) * frac;
                    segs[i].y -= (segs[i].y - segs[prev].y) * frac;
                    segs[i].z -= (segs[i].z - segs[prev].z) * frac;
                    segs[prev].len *= 1.0f - frac;
                }
                while (i != *(s8 *)(arg0 + 0x2D)) {
                    (*(s8 *)(arg0 + 0x2D))++;
                    if (arg0[0x25] == *(s8 *)(arg0 + 0x2D)) {
                        *(s8 *)(arg0 + 0x2D) = 0;
                    }
                    (*(s8 *)(arg0 + 0x2C))--;
                }
                total = max;
            }
        }
    }
    if (*(s8 *)(arg0 + 0x2C) >= 2) {
        amp = 0.0f;
        j = *(s8 *)(arg0 + 0x2E);
        ph = *(f32 *)(def + 0x24);
        do {
            j--;
            if (j < 0) {
                j = arg0[0x25] - 1;
            }
            segs[j].unk14 = sinf(ph) * amp;
            amp += segs[j].len * 0.037499998f;
            ph += segs[j].len * 0.0122f;
        } while (j != *(s8 *)(arg0 + 0x2D));
    }
    *(f32 *)(def + 0x24) += -0.70900005f * D_800BE9A4;
    return 1;
}
