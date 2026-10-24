// pickup_spin_update: world mesh record (D_800DBEF4, 0xA0 bytes) handler for a spinning, bobbing pickup (P195). The phase
// +0x7C advances by 5 degrees * D_800BE9A4 (wrapping at 6 pi) and drives the tilt +0x0 / +0x8 (15 * sin / cos), the
// spin +0x4 (phase * 60 / pi) and the bob of y +0x12 around the base +0x80 (latched from y). While +0x84 (respawn
// timer, in ticks) is 0, the first live player (D_800CC2D0, D_8008FD8C of them; +0x3C >= 0) within 80 units on the
// ground plane and in its height band fades it in by distance; touching it with +0x1CA set gives the item
// (func_15060BA4): respawning pickups (+0x3C high half = respawn time / 50) start their timer and set +0x70 bit 2,
// others are marked taken (+0x6E) and saved through func_1508F26C(2, index); then sound 0x1CF and the effect
// func_151D6F64. +0x8A is the alpha, +0x4F the draw flags (0x21 idle, 0x31 fading, 0x20 taken).
s32 func_1507C7C0(struct127 *, s16 *, s16 *, s16 *);
s32 func_15060BA4(struct127 *arg0, s32 arg1);
void func_1508F26C(s32 arg0, s32 arg1);
u16 func_10010344(u16 sfx, struct127 *obj, s32 vol, s16 arg3, u16 arg4);
void func_151D6F64(s16 *arg0, struct127 *arg1);

void func_1511A540(u8 *rec) {
    u8 *p;
    f32 phase;
    f32 d2;
    f32 dx;
    f32 dz;
    f32 y;
    s16 height;
    s16 unk4C;
    s16 unk4A;
    s32 v;

    if (*(s32 *) (rec + 0x84) < 0x20) {
        if (*(s32 *) (rec + 0x80) == 0) {
            *(s32 *) (rec + 0x80) = *(s16 *) (rec + 0x12);
        }
        *(f32 *) (rec + 0) = sinf(*(f32 *) (rec + 0x7C)) * 15.0f;
        *(f32 *) (rec + 4) = *(f32 *) (rec + 0x7C) * 19.098593f;
        *(f32 *) (rec + 8) = cosf(*(f32 *) (rec + 0x7C)) * 15.0f;
        *(f32 *) (rec + 0x7C) += 0.08726647f * D_800BE9A4;
        phase = *(f32 *) (rec + 0x7C);
        if (18.849556f <= phase) {
            *(f32 *) (rec + 0x7C) = phase - 18.849556f;
            phase = *(f32 *) (rec + 0x7C);
        }
        *(s16 *) (rec + 0x12) = (s32) (cosf(phase + phase) * 10.0f) + *(s32 *) (rec + 0x80) + 10;
        if (*(s32 *) (rec + 0x84) != 0) {
            rec[0x4F] = 0x31;
            rec[0x8A] = (0x20 - *(s32 *) (rec + 0x84)) << 3;
        } else {
            for (p = (u8 *) D_800CC2D0; p < (u8 *) D_800CC2D0 + D_8008FD8C * 0x32C; p += 0x32C) {
                if (*(s32 *) p == 0 || p[0x127] == 0xFF || *(s32 *) (rec + 0x3C) < 0) {
                    continue;
                }
                dz = *(s16 *) (rec + 0x14) - *(f32 *) (p + 0x1C);
                dx = *(s16 *) (rec + 0x10) - *(f32 *) (p + 0x14);
                d2 = dz * dz + dx * dx;
                if (!(d2 < 6400.0f)) {
                    rec[0x8A] = 0xFF;
                    rec[0x4F] = 0x21;
                    continue;
                }
                func_1507C7C0((struct127 *) p, &height, &unk4C, &unk4A);
                rec[0x4F] = 0x31;
                y = *(s16 *) (rec + 0x12);
                if (*(f32 *) (p + 0x18) < y + 80.0f && y - 80.0f < *(f32 *) (p + 0x18) + height && p[0x1CA] != 0) {
                    if (func_15060BA4((struct127 *) p, 1) != 0) {
                        v = *(s32 *) (rec + 0x3C);
                        if (v != 0) {
                            *(s32 *) (rec + 0x84) = ((v >> 16) & 0xFFFF) * 50;
                            rec[0x70] |= 4;
                        } else {
                            rec[0x6E] = 1;
                            func_1508F26C(2, ((rec - (u8 *) D_800DBEF4) / 0xA0) & 0xFFFF);
                        }
                        rec[0x4F] = 0x20;
                        func_10010344(0x1CF, (struct127 *) p, 0x7D00, 0xC8, 0x9C4);
                        func_151D6F64((s16 *) rec, (struct127 *) p);
                    } else {
                        rec[0x4F] = 0x31;
                        rec[0x8A] = (u32) ((0.25f + d2 * 0.0001171875f) * 255.0f);
                    }
                    break;
                }
            }
        }
    }
    if (*(s32 *) (rec + 0x84) > 0) {
        *(s32 *) (rec + 0x84) -= D_800BE9E4;
        if (*(s32 *) (rec + 0x84) <= 0) {
            *(s32 *) (rec + 0x84) = 0;
            rec[0x8A] = 0xFF;
            rec[0x4F] = 0x21;
        }
    }
}
