s32 func_1510D66C(s32, s32 *, s32, s32);
void func_1503F7A0(void *);
extern void guMtxIdentF(float mf[4][4]);
extern f32 D_800901BC;
extern f32 D_800901C0;
extern u8 D_800E1068[];
extern Gfx D_800904C0[];
extern Gfx D_800904D8[];
extern s16 D_800E1060;
extern u8 D_507[];
extern u8 D_508[];

typedef struct {
    u8 pad[0x3E0];
    void *m0;
    void *m1;
    s32 seg[2];
} DlObj3E0;

typedef struct {
    Gfx **dls;
    Gfx *copy[4];
    u8 count;
    u8 flag;
    u8 pad16[6];
    s32 u1C;
    s32 u20;
    DlObj3E0 *obj;
    f32 m[2][4][4];
} DlCopy;

Gfx *func_151EE394(Gfx *gdl, DlCopy *s, f32 x, f32 y, f32 scale) {
    s32 i;
    Gfx *start = gdl;
    s32 tex;
    u8 t;

    if (D_800901BC != 1.0f) {
        x *= D_800901BC;
        y *= D_800901C0;
        scale *= D_800901BC;
    }
    guMtxIdentF(s->m[D_800BE9C0]);
    s->m[D_800BE9C0][3][0] = x;
    s->m[D_800BE9C0][3][1] = y;
    s->m[D_800BE9C0][3][2] = -100.0f;
    s->m[D_800BE9C0][0][0] = scale;
    s->m[D_800BE9C0][1][1] = scale;
    s->m[D_800BE9C0][2][2] = scale;
    func_1503F7A0(s->obj);
    gSPMatrix(gdl++, D_80089810, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(gdl++, D_800E1068, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPDisplayList(gdl++, D_800904C0);
    gDPSetCombine(gdl++, 0x12FE25, 0xFFFFFBFD);
    gSPGeometryMode(gdl++, 0xFFFFFF, 0);
    gSPGeometryMode(gdl++, 0, 0x200404);
    gDPSetPrimColor(gdl++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, D_800E1060);
    gDPSetFogColor(gdl++, 0, 0, 0, 0xFF);
    gSPSegment(gdl++, 3, s->obj->seg[D_800BE9C0]);
    gSPSegment(gdl++, 1, s->u1C);
    if ((s32)s == D_80090408) {
        t = --s->flag;
        if (t == 0) {
            s->flag = (func_150ADA20() & 0x7F) + 0xF;
            t = s->flag;
        }
        tex = func_1510D66C(t < 7 ? (s32)D_507 : (s32)D_508, NULL, 3, 0);
        if (tex == 0x80000000) {
            return start;
        }
        gSPSegment(gdl++, 6, tex);
        gSPSegment(gdl++, 7, tex);
    }
    for (i = 0; i < s->count; i++) {
        gSPDisplayList(gdl++, s->copy[i]);
    }
    gSPDisplayList(gdl++, D_800904D8);
    return gdl;
}
