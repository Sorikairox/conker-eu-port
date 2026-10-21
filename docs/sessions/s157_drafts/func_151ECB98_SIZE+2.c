Gfx *func_151EDBE8(Gfx *, void *, s32, s32, s32, s32, f32, s32);
Gfx *func_151ECE00(Gfx *);
Gfx *func_151EE93C(Gfx *);
Gfx *func_151EF3A0(Gfx *, s32);
extern Gfx D_800903D8[];
extern u8 D_80090484;
extern s8 D_800902A4;
extern s8 D_800902A8;
extern u8 D_800E0EC5;
extern s32 D_80090410;
extern s32 D_8009046C[];

typedef struct {
    f32 x0;
    f32 x4;
    f32 x8;
    u8 padC[0x20];
    s8 x2C;
    u8 pad2D[0x11];
    s8 x3E;
} Ent174;

Gfx *func_151ECB98(Gfx *gdl) {
    Ent174 *p;
    s32 a;
    s32 v;
    s32 k;
    s32 t;
    struct_eu_BE818 *e;

    if (D_800C35EA == 1) {
        D_80090484 = 0;
        return gdl;
    }
    a = D_80090484 + D_800BE9E4 * 4;
    if (a >= 0x100) {
        a = 0xFF;
    }
    D_80090484 = a;
    gSPDisplayList(gdl++, D_800903D8);
    p = (Ent174 *)D_80090174;
    k = p->x3E;
    if (k == 1) {
        return func_151ECE00(gdl);
    }
    if (k != 0) {
        return gdl;
    }
    t = p->x2C;
    if (t == 1 && D_800902A4 != 0) {
        gdl = func_151EE93C(gdl);
    } else if (t != 1 || D_800902A8 == 0) {
        v = (p->x0 - 0.5f) * 512.0f;
        if (v < 0) {
            v = -v;
        }
        if (v >= 0x100) {
            v = 0xFF;
        }
        if (D_80090484 < v) {
            v = D_80090484;
        }
        if (t == 1) {
            v = (D_800E0EC5 * v) >> 8;
            if (v >= 0xFE) {
                v = 0xFF;
            }
        }
        gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, v);
        gDPSetOtherMode(gdl++, 0x002C3F, 0x504244);
        D_80090410 = D_8009046C[((Ent174 *)D_80090174)->x2C];
        gdl = func_151EDBE8(gdl, &D_80090410, 0x94, 0x1E, 3, 1, 1.0f, 0);
    }
    p = (Ent174 *)D_80090174;
    if (0.5f <= p->x8) {
        if (p->x2C >= 3) {
            e = &D_800BE818[p->x2C - 3];
            if (e->unk8 != -1) {
                gdl = func_151EF3A0(gdl, e->padC[0]);
            }
        }
    }
    return gdl;
}
