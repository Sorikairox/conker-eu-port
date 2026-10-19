typedef struct { f32 x, y, z; } V3BCD;
typedef struct BCDEnt { V3BCD pos; s16 unkC; s8 unkE; u8 padF; f32 unk10; } BCDEnt;
typedef struct BCDTgt { s32 unk0; u8 pad4[0x10]; V3BCD pos; u8 pad20[0x1B]; u8 unk3B; } BCDTgt;
typedef struct BCDSrc { BCDTgt *tgt; u8 unk4; u8 pad5[3]; V3BCD pos; f32 unk14; f32 unk18; f32 unk1C; f32 unk20; } BCDSrc;
f32 func_15143E64(V3BCD *, void *, void *);
s32 func_151BCD44(u8 *arg0) {
    BCDSrc *p = *(BCDSrc **)(arg0 + 0x98);
    BCDEnt *buf = *(BCDEnt **)(arg0 + 0x94);
    BCDTgt *t = p->tgt;
    V3BCD d;
    f32 f0, inv, a, b0;
    V3BCD cur;
    f32 b, c, dx, dy, dz, df; // fakematch: unused slot
    volatile f32 dist; // fakematch: ref spills the distance and reloads it for the divide
    if (t->unk0 == 0 || t->unk3B != p->unk4) {
        *(u16 *)(arg0 + 0x1E) |= 8;
        return 1;
    }
    *(f32 *)(arg0 + 0x10) = t->pos.x;
    *(f32 *)(arg0 + 0x14) = t->pos.y;
    *(f32 *)(arg0 + 0x18) = t->pos.z;
    d.x = *(f32 *)(arg0 + 0x10) - p->pos.x;
    d.y = *(f32 *)(arg0 + 0x14) - p->pos.y;
    d.z = *(f32 *)(arg0 + 0x18) - p->pos.z;
    f0 = func_15143E64(&d, arg0, p);
    p->unk14 += f0 * 0.048708f * D_800BE9A4;
    p->unk1C += f0 * 9.708836f;
    if (p->unk14 > 1.0f) {
        dist = p->unk14;
        inv = 1.0f / dist;
        cur = p->pos;
        a = p->unk18 + D_800BE9A4;
        b0 = p->unk20;
        b = b0;
        c = -(a * inv);
        dx = d.x * inv;
        dy = d.y * inv;
        dz = d.z * inv;
        df = (p->unk1C - b0) * inv;
        do {
            BCDEnt *e = &buf[*(s8 *)(arg0 + 0x2E)];
            e->pos = cur;
            e->unkC = 0xC;
            e->unkE = 0x64;
            e->unk10 = b;
            if (b > 16384.0f) {
                do {
                    e->unk10 -= 32768.0f;
                } while (e->unk10 > 16384.0f);
            }
            (*(s8 *)(arg0 + 0x2E))++;
            if (*(u8 *)(arg0 + 0x25) == *(s8 *)(arg0 + 0x2E)) {
                *(s8 *)(arg0 + 0x2E) = 0;
            }
            (*(s8 *)(arg0 + 0x2C))++;
            if (*(s8 *)(arg0 + 0x2D) == *(s8 *)(arg0 + 0x2E)) {
                (*(s8 *)(arg0 + 0x2D))++;
                if (*(u8 *)(arg0 + 0x25) == *(s8 *)(arg0 + 0x2D)) {
                    *(s8 *)(arg0 + 0x2D) = 0;
                }
                (*(s8 *)(arg0 + 0x2C))--;
            }
            b += df;
            cur.x += dx;
            cur.y += dy;
            a += c;
            cur.z += dz;
            p->unk14 -= 1.0f;
        } while (p->unk14 > 1.0f);
        p->pos = cur;
        p->unk20 = b;
        p->unk18 = a;
    }
    return 1;
}
