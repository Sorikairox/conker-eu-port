typedef struct { f32 x, y, z; } V3_1B80;
typedef struct {
    V3_1B80 pos;
    f32 len;
    f32 inv;
    u8 unk14;
    u8 pad15[3];
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
} Seg1B80;
typedef struct { f32 x, z; } V2_1B80;

f32 func_15144528(f32 arg0, f32 arg1, f32 arg2);

s32 func_151D1B80(u8 *arg0) {
    u8 *def = *(u8 **)(arg0 + 0x98);
    Seg1B80 *segs = *(Seg1B80 **)(arg0 + 0x94);
    u8 *p;
    Seg1B80 *seg;
    Seg1B80 *pb;
    Seg1B80 *pc;
    f32 d;
    f32 vx, vz;
    s16 a, b, c;
    V2_1B80 u;
    V2_1B80 v;
    f32 dd[1];
    f32 dd2[1];
    f32 inv;
    f32 sx, sz;

    if (D_800BE9E4 > 0) {
        p = *(u8 **)def + 0x28;
        *(V3_1B80 *)(arg0 + 0x10) = *(V3_1B80 *)(p + 0x18);
        *(u16 *)(arg0 + 0x1E) |= 4;
        seg = &segs[*(s8 *)(arg0 + 0x2E)];
        seg->pos = *(V3_1B80 *)(arg0 + 0x10);
        seg->len = *(f32 *)(p + 0x30);
        vx = *(f32 *)(p + 0x24);
        vz = *(f32 *)(p + 0x2C);
        d = sqrtf(vx * vx + vz * vz);
        if (d == 0.0f) {
            seg->inv = 1.0f;
        } else {
            seg->inv = 1.0f / d;
        }
        seg->unk1C = 100.0f;
        seg->unk14 = 0xFF;
        seg->unk18 = *(f32 *)(def + 4);
        *(f32 *)(def + 4) += seg->len * 21.85f;
        *(f32 *)(def + 4) = func_15144528(*(f32 *)(def + 4), 8192.0f, 0.0f);
        if (d != 0.0f) {
            inv = seg->inv;
            seg->unk20 = -*(f32 *)(p + 0x2C) * inv;
            seg->unk24 = *(f32 *)(p + 0x24) * inv;
        } else {
            seg->unk20 = 0.0f;
            seg->unk24 = 0.0f;
        }
        (*(s8 *)(arg0 + 0x2E))++;
        if (arg0[0x25] == *(s8 *)(arg0 + 0x2E)) {
            *(s8 *)(arg0 + 0x2E) = 0;
        }
        (*(s8 *)(arg0 + 0x2C))++;
        if (*(s8 *)(arg0 + 0x2D) == *(s8 *)(arg0 + 0x2E)) {
            (*(s8 *)(arg0 + 0x2D))++;
            if (arg0[0x25] == *(s8 *)(arg0 + 0x2D)) {
                *(s8 *)(arg0 + 0x2D) = 0;
            }
            (*(s8 *)(arg0 + 0x2C))--;
        }
        if (*(s8 *)(arg0 + 0x2C) >= 3) {
            a = *(s8 *)(arg0 + 0x2E) - 1;
            if (a < 0) {
                a = arg0[0x25] - 1;
            }
            b = a - 1;
            if (b < 0) {
                b = arg0[0x25] - 1;
            }
            c = b - 1;
            if (c < 0) {
                c = arg0[0x25] - 1;
            }
            if (seg->len != 0.0f) {
                pb = &segs[b];
                if (pb->len != 0.0f) {
                    pc = &segs[c];
                    sx = (seg->pos.x - pb->pos.x) * seg->inv;
                    sz = (seg->pos.z - pb->pos.z) * seg->inv;
                    u.x = (pc->pos.x - pb->pos.x) * pb->inv;
                    u.z = (pc->pos.z - pb->pos.z) * pb->inv;
                    v.z = sx - u.x;
                    v.x = -(sz - u.z);
                    dd[0] = dd2[0] = v.x * v.x + v.z * v.z;
                    if (dd[0] > 0.0001f) {
                        inv = 1.0f / sqrtf(dd[0]);
                        v.x *= inv;
                        v.z *= inv;
                        *(V2_1B80 *)&pb->unk20 = v;
                    } else {
                        pb->unk20 = 0.0f;
                        pb->unk24 = 0.0f;
                    }
                }
            }
        }
    }
    return 1;
}
