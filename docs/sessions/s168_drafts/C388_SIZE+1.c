typedef struct {
    u8 pad0[0x4];
    f32 unk4;
    u8 pad8[0xC - 0x8];
    f32 unkC;
    f32 unk10;
    u8 pad14[0x38 - 0x14];
    s8 unk38;
} Mover388;

typedef struct {
    u8 pad0[0x25];
    u8 unk25;
    u8 pad26[0x2C - 0x26];
    s8 unk2C;
    s8 unk2D;
    s8 unk2E;
    u8 pad2F[0x54 - 0x2F];
    struct17 unk54;
    u8 pad60[0x94 - 0x60];
    struct_eu_1897A0_entry *unk94;
    Mover388 *unk98;
} Trail388;

extern s32 (*D_8008B420[])(Trail388 *, Mover388 *);

s32 func_1515C388(Trail388 *arg0) {
    struct_eu_1897A0_entry *entries;
    struct17 sp28;
    struct_eu_1897A0_entry *e;
    Mover388 *b;
    s32 i;
    f32 vy;
    u8 done;
    s32 ret;

    b = arg0->unk98;
    done = 0;
    entries = arg0->unk94;
    if (arg0->unk2C != 0) {
        sp28 = entries[arg0->unk2D].unk0;
        i = arg0->unk2D;
        if (i != arg0->unk2E) {
            do {
                e = &entries[i];
                vy = e->unkC;
                i++;
                e->unk0.unk0 += b->unk4 * D_800BE9A4;
                e->unk0.unk4 += vy * D_800BE9A4 + b->unk10 * D_800BE9A4 * D_800BE9A4 * 0.5f;
                e->unk0.unk8 += b->unkC * D_800BE9A4;
                e->unkC = vy + b->unk10 * D_800BE9A4;
                if (i == arg0->unk25) {
                    i = 0;
                }
            } while (i != arg0->unk2E);
        }
    }
    if (b->unk38 != -1) {
        done = D_8008B420[b->unk38](arg0, b) == 0;
    }
    if (arg0->unk2C > 0) {
        arg0->unk54 = entries[arg0->unk2D].unk0;
    } else {
        arg0->unk54.unk0 = 0.0f;
        arg0->unk54.unk4 = 0.0f;
        arg0->unk54.unk8 = 0.0f;
    }
    ret = 1;
    if (done) {
        ret = 0;
    }
    return ret;
}
