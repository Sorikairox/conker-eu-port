typedef struct { s16 cmd; s16 val; } Pair;
Pair *func_150344AC(Pair *p, s32 arg1) {
    struct127 *v;
    struct126 *s;
    s16 ang;
    s32 k;
    u16 id;

    v = &D_800CC2D0[arg1];
    s = v->unk31C;
    if ((s != NULL) && !(v->unk2F8 & 0x80)) {
        id = v->unk84.uh;
        ang = v->unk54 * 182.04445f;
        if ((id != 0x42) && (id != 0x14) && (id != 0x76)) {
            k = 4;
            if (s->unk78 == 0xA) {
                k = 0;
            }
            p->cmd = k + 6;
            p->val = ang;
        } else {
            p->cmd = 0xA;
            p->val = ang;
            p++;
            p->cmd = 4;
            p->val = -ang;
        }
        p++;
    }
    if (v->unk1D1 != 0) {
        p->cmd = 6;
        (p++)->val = v->unk1D1 * 200;
    }
    if ((D_800CC2D0[D_800C3E78].unk31C != NULL) && (D_800CC2D0[D_800C3E78].unk31C->unk12 != 0)) {
        p->cmd = 8;
        (p++)->val = -D_800CC2D0[D_800C3E78].unk31C->unk12;
    }
    return p;
}
