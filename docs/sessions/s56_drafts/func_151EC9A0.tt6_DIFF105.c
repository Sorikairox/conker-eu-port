Gfx *func_151EDBE8(Gfx *, s32 *, s32, s32, s32, s32, f32, s32);
extern s32 D_800903D8;
extern s32 D_80091BA8;
extern s32 D_80091BB4;
extern s32 D_80091BC0;
extern s32 D_800E0EA4;
#define MW(g, a, b) { Gfx *_g = (g); _g->words.w0 = (a); _g->words.w1 = (b); }

Gfx *func_151EC9A0(Gfx *gdl) {
    s32 temp_v1;
    s32 var_v1;
    s32 var_v1_2;
    s32 temp_t0;
    s32 temp_a;

    if (D_800BE9F0 == 0x21) {
        return gdl;
    }
    gSPDisplayList(gdl++, &D_800903D8);
    if (D_800E0EC0 >= 0x12D) {
        temp_v1 = 0x1AC - D_800E0EC0;
        temp_a = temp_v1 * 2;
        var_v1 = temp_a;
        if (temp_a < 0) {
            var_v1 = 0;
        }
    } else {
        var_v1 = D_800E0EC0 * 8;
        if (var_v1 >= 0x100) {
            var_v1 = 0xFF;
        }
    }
    if (var_v1 != 0) {
        gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, var_v1);
        gdl = func_151EDBE8(gdl, &D_80091BA8, 0x92, 0x63, 5, 6, 1.0f, 0);
    }
    gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, 0xFF);
    gdl = func_151EDBE8(gdl, &D_80091BB4, 0x92, 0xCB, 5, 2, 1.0f, 0);
    MW(gdl++, 0xFCFFD3FF, 0xFFA6FF7F);
    MW(gdl++, 0xFB000000, (u8) D_800E0FC7 | 0x20FF2000);
    gdl = func_151EDBE8(gdl, &D_80091BC0, 0x92, 0xCB, 5, 2, 1.0f, 0);
    gdl = func_15096D44(gdl);
    temp_v1 = 0x1EA - D_800E0EA4;
    if (temp_v1 < 0) {
        var_v1_2 = 0;
    } else {
        temp_t0 = temp_v1 * 0x10;
        var_v1_2 = temp_t0;
        if (temp_t0 >= 0x100) {
            var_v1_2 = 0xFF;
        }
    }
    D_800E0FC6 = 0xFF - var_v1_2;
        return gdl;
}
