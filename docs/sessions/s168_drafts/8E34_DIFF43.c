typedef struct {
    struct17 pos;
    f32 vy;
    u16 tex;
    u8 pad12[2];
} Pt8E34;

s32 func_15148E34(u8 *arg0) {
    u16 step;
    u16 tex;
    s32 i;
    s8 n;
    Pt8E34 *pts;
    u8 *b;

    i = ((s8 *)arg0)[0x2D];
    pts = *(Pt8E34 **)(arg0 + 0x94);
    b = *(u8 **)(arg0 + 0x98);
    while (i != ((s8 *)arg0)[0x2E]) {
        pts[i].vy -= *(f32 *)(b + 0x10) * D_800BE9A4;
        pts[i].pos.unk0 += *(f32 *)(b + 4) * D_800BE9A4;
        pts[i].pos.unk4 += pts[i].vy * D_800BE9A4;
        pts[i].pos.unk8 += *(f32 *)(b + 0xC) * D_800BE9A4;
        i++;
        if (i == arg0[0x25]) {
            i = 0;
        }
    }
    n = ((s8 *)arg0)[0x2C];
    if (n < arg0[0x25] - 1) {
        if (b[0x18] & 0x20) {
            tex = 0x1000;
        } else {
            tex = 0;
        }
        if (n != 0) {
            step = 0x1000 / n;
        }
        ((s8 *)arg0)[0x2C] = n + 1;
        pts[((s8 *)arg0)[0x2E]].pos = *(struct17 *)(arg0 + 0x10);
        pts[((s8 *)arg0)[0x2E]].vy = *(f32 *)(b + 8);
        ((s8 *)arg0)[0x2E]++;
        if (arg0[0x25] == ((s8 *)arg0)[0x2E]) {
            ((s8 *)arg0)[0x2E] = 0;
        }
        i = ((s8 *)arg0)[0x2D];
        while (i != ((s8 *)arg0)[0x2E]) {
            pts[i].tex = tex;
            if (b[0x18] & 0x20) {
                tex -= step;
            } else {
                tex += step;
            }
            i++;
            if (i == arg0[0x25]) {
                i = 0;
            }
        }
    } else if (b[0x18] & 0x17) {
        b[0x20] = 3;
    } else {
        b[0x20] = 2;
    }
    return 1;
}
