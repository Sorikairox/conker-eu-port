void func_150A7A48(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
s32 func_150A7DA0(f32 *, s32, f32, f32);
s32 func_151882DC(f32 (*)[4], f32, f32, f32);
s32 guMtxF2L2(f32 *, void *);
extern Vtx D_8008D8D8[];
#define MTX_8008(a) (((f32 (*)[16])((a) + 0x10))[D_800BE9C0])
#define EL_MTX(a, i) (((f32 (*)[16])(*(u8 **)((a) + 0xA4) + (i) * 0xA0))[D_800BE9C0])

Gfx *func_15188008(Gfx *gdl, u8 *arg1, s32 arg2) {
    f32 spB8[16];
    f32 sp78[16];
    s16 var_s2;
    s32 var_s3;
    u8 *temp_v0;
    s16 temp_a1;

    if ((*(s16 *)((u8 *)arg1 + 0xA8)) >= 0) {
        func_150A7DA0(spB8, (*(s32 *)((u8 *)arg1 + 0x90)), (*(f32 *)((u8 *)arg1 + 0x94)), (*(f32 *)((u8 *)arg1 + 0x98)));
        guMtxF2L2(spB8, MTX_8008(arg1));
        var_s2 = 0;
        var_s3 = 0;
        do {
            gSPMatrix(gdl++, MTX_8008(arg1), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            func_150A7DA0(spB8, (*(s32 *)((u8 *)(((*(s32 *)((u8 *)arg1 + 0xA4)) + var_s3)) + 0x90)), 0.0f, 0.0f);
            spB8[0] *= (*(f32 *)((u8 *)arg1 + 0xA0));
            spB8[5] *= (*(f32 *)((u8 *)arg1 + 0x9C));
            spB8[10] *= (*(f32 *)((u8 *)arg1 + 0x9C));
            temp_v0 = (u8 *)((*(s32 *)((u8 *)arg1 + 0xA4)) + var_s3);
            if ((*(u8 *)((u8 *)temp_v0 + 0x98)) == 0) {
                func_150A8050((f32 (*)[4]) sp78, (*(f32 *)((u8 *)temp_v0 + 0x80)), (*(f32 *)((u8 *)temp_v0 + 0x84)), (*(f32 *)((u8 *)temp_v0 + 0x88)));
            } else {
                func_151882DC((f32 (*)[4]) sp78, (*(f32 *)((u8 *)temp_v0 + 0x80)), (*(f32 *)((u8 *)temp_v0 + 0x84)), (*(f32 *)((u8 *)temp_v0 + 0x88)));
            }
            func_150A7A48((f32 (*)[4]) spB8, (f32 (*)[4]) sp78, (f32 (*)[4]) spB8);
            guMtxF2L((f32 (*)[4]) spB8, (Mtx *)EL_MTX(arg1, var_s2));
            temp_v0 = (u8 *)((*(s32 *)((u8 *)arg1 + 0xA4)) + var_s3);
            temp_a1 = (*(s16 *)((u8 *)temp_v0 + 0x96));
            gDPSetPrimColor(gdl++, 1, 0, 0xFF, 0xFF, 0xFF, ((temp_a1 - (*(s16 *)((u8 *)temp_v0 + 0x94))) * 0xFF) / temp_a1);
            gSPMatrix(gdl++, EL_MTX(arg1, var_s2), G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
            gSPVertex(gdl++, D_8008D8D8, 4, 0);
            gSP1Triangle(gdl++, 0, 1, 2, 0);
            gSP1Triangle(gdl++, 0, 1, 3, 0);
            gSP1Triangle(gdl++, 0, 2, 3, 0);
            var_s2 += 1;
            var_s3 += 0xA0;
        } while (var_s2 != 0xC);
    }
    return gdl;
}
