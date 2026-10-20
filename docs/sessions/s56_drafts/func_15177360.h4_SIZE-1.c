void func_150A7A48(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
Gfx *func_15142FBC(Gfx *, s32, s32, s8 *);
extern s32 D_800A7550;
extern s32 D_800DE2BC;
#define MTX_7360(a) (((f32 (*)[16])((a) + 0x10))[D_800BE9C0])
Gfx *func_15177360(Gfx *gdl, u8 *arg1, s32 arg2) {
    f32 sp94[16];
    f32 sp54[16];
    s32 pad;
    volatile s32 sp50;
    volatile s32 sp4C;
    volatile s32 sp48;
    s8 sp33;
    s32 temp_a2;
    s32 var_v0;
    u8 temp_v0_2;

    temp_v0_2 = (*(u8 *)((u8 *)arg1 + 0xED));
    if ((*(s32 *)((u8 *)D_800DDE80 + (temp_v0_2 * 0x14)) == 0) || (D_800DDF78[temp_v0_2] == 0)) {
        return gdl;
    }
    func_150A8050((f32 (*)[4]) sp54, 0.0f, (*(f32 *)((u8 *)arg1 + 0xAC)), 0.0f);
    func_150A8050((f32 (*)[4]) sp94, (*(f32 *)((u8 *)arg1 + 0xA8)), 0.0f, (*(f32 *)((u8 *)arg1 + 0xB0)));
    func_150A7A48((f32 (*)[4]) sp94, (f32 (*)[4]) sp54, (f32 (*)[4]) sp54);
    sp54[12] = (*(f32 *)((u8 *)arg1 + 0x98));
    sp54[13] = (*(f32 *)((u8 *)arg1 + 0x9C));
    sp54[14] = (*(f32 *)((u8 *)arg1 + 0xA0));
    sp54[0] *= (*(f32 *)((u8 *)arg1 + 0xC0));
    sp54[1] *= (*(f32 *)((u8 *)arg1 + 0xC0));
    sp54[2] *= (*(f32 *)((u8 *)arg1 + 0xC0));
    sp54[4] *= (*(f32 *)((u8 *)arg1 + 0xC0));
    sp54[5] *= (*(f32 *)((u8 *)arg1 + 0xC0));
    sp54[6] *= (*(f32 *)((u8 *)arg1 + 0xC0));
    sp54[8] *= (*(f32 *)((u8 *)arg1 + 0xC0));
    sp54[9] *= (*(f32 *)((u8 *)arg1 + 0xC0));
    sp54[10] *= (*(f32 *)((u8 *)arg1 + 0xC0));
    guMtxF2L((f32 (*)[4]) sp54, (Mtx *)MTX_7360(arg1));
    gSPMatrix(gdl++, MTX_7360(arg1), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(gdl++, 1, *(s32 *)(arg1 + 0x94));
    gDPPipeSync(gdl++);
    var_v0 = (*(u8 *)((u8 *)arg1 + 0xEC));
    temp_a2 = *((u8 *)&D_800A7550 + (((u32) (*(u32 *)((u8 *)arg1 + 0xE8)) >> 5) & 3));
    if (var_v0 != temp_a2) {
        if ((s32) var_v0 < (s32) temp_a2) {
            var_v0 += D_800BE9E4 * 4;
            if ((s32) temp_a2 < (s32) var_v0) {
                var_v0 = temp_a2;
            }
        } else {
            var_v0 -= D_800BE9E4 * 4;
            if ((s32) var_v0 < 0) {
                var_v0 = 0;
            }
        }
        (*(u8 *)((u8 *)arg1 + 0xEC)) = var_v0;
    }
    sp4C = (s32) var_v0;
    sp48 = (s32) var_v0;
    sp33 = 0;
    sp50 = (s32) var_v0;
    gdl = func_15142FBC(gdl, 0x82CA0, 0x504A50, &sp33);
    gDPSetEnvColor(gdl++, sp48, sp4C, sp50, *(u8 *)(arg1 + 0xF0));
    gSPDisplayList(gdl++, *(s32 *)((u8 *)&D_800DE2BC + ((*(u8 *)((u8 *)arg1 + 0xED)) * 0x14)));
    return gdl;
}
