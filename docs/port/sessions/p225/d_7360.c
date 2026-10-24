#ifdef NON_MATCHING
void func_150A7A48(f32 a[4][4], f32 b[4][4], f32 c[4][4]);
Gfx *func_15142FBC(Gfx *gfx, s32 arg1, s32 arg2, u8 *arg3);
extern u8 D_800A7550[4];
extern Row20 D_800DE2BC[];

// prop_model_draw: draws the object's model (kinds 1..3 of func_15177638) unless its row of D_800DDE80 / D_800DDF78
// (index obj[0xED]) is empty: matrix = yaw (+0xAC) after pitch / roll (+0xA8 / +0xB0), scaled by +0xC0, at +0x98..+0xA0
// (into the object's per-frame matrix slot +0x10 + D_800BE9C0 * 0x40), segment 1 = +0x94, render mode
// (func_15142FBC) and env colour (v, v, v, obj[0xF0]) where v (obj[0xEC]) fades by 4 per frame towards
// D_800A7550[(+0xE8 >> 5) & 3], then the row's display list (D_800DE2BC).
Gfx *func_15177360(Gfx *gdl, u8 *obj, s16 arg2) {
    f32 mf[4][4];
    f32 rot[4][4];
    s32 v;
    s32 target;
    u8 flag;

    if (((Row20 *)D_800DDE80)[obj[0xED]].x0 == 0 || D_800DDF78[obj[0xED]] == 0) {
        return gdl;
    }
    func_150A8050(mf, 0.0f, *(f32 *)(obj + 0xAC), 0.0f);
    func_150A8050(rot, *(f32 *)(obj + 0xA8), 0.0f, *(f32 *)(obj + 0xB0));
    func_150A7A48(rot, mf, mf);
    mf[3][0] = *(f32 *)(obj + 0x98);
    mf[3][1] = *(f32 *)(obj + 0x9C);
    mf[3][2] = *(f32 *)(obj + 0xA0);
    mf[0][0] *= *(f32 *)(obj + 0xC0);
    mf[0][1] *= *(f32 *)(obj + 0xC0);
    mf[0][2] *= *(f32 *)(obj + 0xC0);
    mf[1][0] *= *(f32 *)(obj + 0xC0);
    mf[1][1] *= *(f32 *)(obj + 0xC0);
    mf[1][2] *= *(f32 *)(obj + 0xC0);
    mf[2][0] *= *(f32 *)(obj + 0xC0);
    mf[2][1] *= *(f32 *)(obj + 0xC0);
    mf[2][2] *= *(f32 *)(obj + 0xC0);
    guMtxF2L(mf, (Mtx *)(obj + 0x10 + (D_800BE9C0 << 6)));
    gSPMatrix(gdl++, obj + 0x10 + (D_800BE9C0 << 6), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(gdl++, 1, *(s32 *)(obj + 0x94));
    gDPPipeSync(gdl++);

    v = obj[0xEC];
    target = D_800A7550[(*(u32 *)(obj + 0xE8) >> 5) & 3];
    if (v != target) {
        if (v < target) {
            v += D_800BE9E4 * 4;
            if (v > target) {
                v = target;
            }
        } else {
            v -= D_800BE9E4 * 4;
            if (v < 0) {
                v = 0;
            }
        }
        obj[0xEC] = v;
    }
    flag = 0;
    gdl = func_15142FBC(gdl, 0x82CA0, 0x504A50, &flag);
    gDPSetEnvColor(gdl++, v, v, v, obj[0xF0]);
    gSPDisplayList(gdl++, D_800DE2BC[obj[0xED]].x0);
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/func_15177360.s")
#endif
