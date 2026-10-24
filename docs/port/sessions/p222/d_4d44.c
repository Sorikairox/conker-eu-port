/* P222: readable C for func_151D4D44 (game_eu_201240, 297 words). */
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
f32 func_15143E64(struct17 *arg0);

typedef struct {
    s32 w00;        /* 0x00 0x200005 */
    s32 w04;        /* 0x04 0 */
    s16 h08;        /* 0x08 0x5103 */
    s16 life;       /* 0x0A rand % 11 + 0x46 */
    s32 w0C, w10;   /* 0x0C 0 */
    u8 rgba0[4];    /* 0x14 DD D3 CD FF */
    u8 rgba1[4];    /* 0x18 57 55 5A, alpha rand % 61 + 0x3C */
    u8 b1C, b1D;    /* 0x1C FF 6C */
    s16 h1E, h20, h22; /* 0x1E 0x46, 3, 0x46 */
    f32 f24;        /* 0x24 1.02555 */
    f32 size[2];    /* 0x28 rand * 40 + 40 (both) */
    f32 pos[3];     /* 0x30 */
    f32 f3C[3];     /* 0x3C 0 */
    f32 vel[3];     /* 0x48 */
    f32 f54;        /* 0x54 rand * 0.18 + 0.13 */
    s32 flags;      /* 0x58 0x90DE07, bits 0x80 / 0x40 random */
    u8 pad5C[4];
    u8 b60, b61, b62, b63, b64, b65; /* 0x60 8 6 0x20 0xFF 0xFF 0 */
} SmokeSpec_151D4D44;

typedef struct {
    u8 b0, b1, b2, b3;  /* rand, rand, rand % 5 + 4, rand % 5 + 4 */
    f32 f4, f8;         /* rand * 6 */
    f32 fC;             /* 0.915686 */
} SmokeData_151D4D44;   /* copied to the particle's +0xA8 */

// object_trail_smoke_update: update handler (table D_8008A980) of the event record that func_151D469C spawns (kind
// 0x35, its 0x20-byte object record at +0x28: object, id, sound, point kind, accumulator +0x34, flags +0x38, point
// +0x3C). Ends the event (+0xE = -1) when the object is gone or reused (id +0x2C != obj[0x3B]). Re-reads the point from
// the object's D_80090010 handler (bone matrices present and obj[0x74] low nibble != 0xF). When the old point was
// valid and the point moved at most 5 units, the accumulator grows by (0.2 + rand * 0.209) per second and each whole
// unit emits one smoke particle (func_151307F0, layer ev[0xC] / ev[1]) at a random spot on the move segment, with
// random size / alpha / life and its 16-byte data at +0xA8.
void func_151D4D44(u8 *ev) {
    ObjEffectRec_151D469C *rec = (ObjEffectRec_151D469C *) (ev + 0x28);
    u8 *obj;
    struct17 old;
    struct17 d;
    SmokeSpec_151D4D44 spec;
    SmokeData_151D4D44 data;
    u8 *p;
    f32 t;
    s32 b80, b40;
    u8 valid;

    old = *(struct17 *) rec->point;
    obj = rec->obj;
    valid = rec->flags & 1;
    if (*(s32 *) obj == 0 || rec->objId != obj[0x3B]) {
        *(s16 *) (ev + 0xE) = -1;
        return;
    }
    if (*(u8 **) (obj + 0x1D4) != NULL && (obj[0x74] & 0xF) != 0xF) {
        D_80090010[rec->kind](obj, rec->sound, rec->point);
        rec->flags |= 1;
    }
    if (!valid) {
        return;
    }
    d.unk0 = rec->point[0] - old.unk0;
    d.unk4 = rec->point[1] - old.unk4;
    d.unk8 = rec->point[2] - old.unk8;
    if (func_15143E64(&d) > 5.0f) {
        return;
    }
    rec->unkC += (0.2f + func_150ADA68() * 0.209f) * D_800BE9A4;
    if (!(rec->unkC > 1.0f)) {
        return;
    }
    data.fC = 0.915686f;
    spec.w00 = 0x200005;
    spec.w04 = 0;
    spec.h08 = 0x5103;
    spec.w0C = 0;
    spec.w10 = 0;
    spec.rgba0[0] = 0xDD;
    spec.rgba0[1] = 0xD3;
    spec.rgba0[2] = 0xCD;
    spec.rgba0[3] = 0xFF;
    spec.rgba1[0] = 0x57;
    spec.rgba1[1] = 0x55;
    spec.rgba1[2] = 0x5A;
    spec.b1C = 0xFF;
    spec.b1D = 0x6C;
    spec.h1E = 0x46;
    spec.h20 = 3;
    spec.h22 = 0x46;
    spec.f24 = 1.02555f;
    spec.f3C[0] = spec.f3C[1] = spec.f3C[2] = 0.0f;
    spec.flags = 0x90DE07;
    spec.b60 = 8;
    spec.b61 = 6;
    spec.b62 = 0x20;
    spec.b63 = 0xFF;
    spec.b64 = 0xFF;
    spec.b65 = 0;
    do {
        t = func_150ADA68();
        spec.pos[0] = d.unk0 * t + old.unk0;
        spec.pos[1] = d.unk4 * t + old.unk4;
        spec.pos[2] = d.unk8 * t + old.unk8;
        spec.vel[0] = d.unk0 * D_800BEDC8 * 0.298f;
        spec.vel[1] = d.unk4 * D_800BEDC8 * 0.298f;
        spec.vel[2] = d.unk8 * D_800BEDC8 * 0.298f;
        data.b0 = func_150ADA20();
        data.b1 = func_150ADA20();
        data.b2 = (u32) func_150ADA20() % 5 + 4;
        data.b3 = (u32) func_150ADA20() % 5 + 4;
        data.f4 = func_150ADA68() * 6.0f;
        data.f8 = func_150ADA68() * 6.0f;
        spec.f54 = func_150ADA68() * 0.18f + 0.13000001f;
        b80 = (func_150ADA20() & 1) ? 0x80 : 0;
        b40 = (func_150ADA20() & 1) ? 0x40 : 0;
        spec.flags = (spec.flags & ~0xC0) | b40 | b80;
        spec.rgba1[3] = (u32) func_150ADA20() % 61 + 0x3C;
        spec.life = (u32) func_150ADA20() % 11 + 0x46;
        spec.size[0] = spec.size[1] = func_150ADA68() * 40.0f + 40.0f;
        p = (u8 *) func_151307F0((s32) &spec, 1, 0, 0x10, ev[0xC], ev[1]);
        if (p != NULL) {
            memcpy(p + 0xA8, &data, 0x10);
        }
        rec->unkC -= 1.0f;
    } while (rec->unkC > 1.0f);
}
