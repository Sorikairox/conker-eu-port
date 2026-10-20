typedef struct {
    f32 x, y, z;
    f32 len;
    f32 unk10;
    u8 unk14;
    u8 pad15[7];
    f32 unk1C;
    u8 pad20[8];
} Seg1F2C;

s32 func_151D1F2C(u8 *arg0) {
    u8 *def = *(u8 **)(arg0 + 0x98);
    Seg1F2C *segs = *(Seg1F2C **)(arg0 + 0x94);
    s32 i;
    s32 prev;
    f32 total;
    f32 l;
    f32 frac;
    f32 inv;
    f32 max;
    f32 x, y, z;
    s8 j;
    f32 d;
    u16 flags;

    if (*(u8 **)def != NULL) {
        *(f32 *)(def + 0x1C) = *(f32 *)(*(u8 **)(*(u8 **)def + 0x28) + 0x14C);
    }
    if (*(s8 *)(arg0 + 0x2C) >= 2) {
        total = 0.0f;
        i = *(s8 *)(arg0 + 0x2E) - 1;
        if (i < 0) {
            i = arg0[0x25] - 1;
        }
        max = *(f32 *)(def + 0xC);
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
                    x = segs[i].x;
                    y = segs[i].y;
                    z = segs[i].z;
                    segs[i].x = x - (x - segs[prev].x) * frac;
                    segs[i].y = y - (y - segs[prev].y) * frac;
                    segs[i].z = z - (z - segs[prev].z) * frac;
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
        if (total != 0.0f) {
            inv = 1.0f / total;
        } else {
            inv = 0.0f;
        }
    }
    if (*(s8 *)(arg0 + 0x2C) >= 2) {
        j = *(s8 *)(arg0 + 0x2E);
        d = total;
        do {
            j--;
            if (j < 0) {
                j = arg0[0x25] - 1;
            }
            segs[j].unk1C = *(f32 *)(def + 0x10) * *(f32 *)(def + 0x1C) + d * (*(f32 *)(def + 0x14) * *(f32 *)(def + 0x1C) * inv);
            segs[j].unk14 = d * (*(f32 *)(def + 0x18) * inv);
            d -= segs[j].len;
        } while (j != *(s8 *)(arg0 + 0x2D));
    }
    flags = *(u16 *)(arg0 + 0x1E);
    if ((flags & 1) && (flags & 8)) {
        *(s8 *)(def + 8) = *(s16 *)(arg0 + 0x1C) * 6;
    }
    return 1;
}
