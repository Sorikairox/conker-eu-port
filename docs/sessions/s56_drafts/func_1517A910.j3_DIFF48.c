s32 func_1510B460(void *, f32, f32, f32, f32, f32, f32, f32, s32, s32);
s32 func_1517AF18(s32, s32);
Gfx *func_15142FBC(Gfx *, s32, s32, s8 *);
extern s32 D_8008D190;
extern s32 D_800D30BC;
extern f32 D_800D3A00;
extern f32 D_800D3A04;
extern f32 D_800D9F3C;
extern f32 D_800D9F40;
extern s32 D_800DA030;
#define MTX_A910(a) (((f32 (*)[16])((a) + 0x10))[D_800BE9C0])
#define MW(g, a, b) { Gfx *_g = (g); _g->words.w0 = (a); _g->words.w1 = (b); }

Gfx *func_1517A910(Gfx *gdl, u8 *arg1, s16 arg2) {
    s8 sp43;
    s32 var_a2;
    f32 temp_f0;
    u8 temp_v0_2;
    u8 temp_v0_3;
    u8 temp_v0_4;

    temp_v0_2 = (*(u8 *)((u8 *)arg1 + 0));
    if ((temp_v0_2 != 0xC) && (temp_v0_2 != 0x59) && (func_1510B460((u8 *)&D_800DA030 + (arg2 << 6), (f32) (*(s16 *)((u8 *)arg1 + 0x90)), (f32) (*(s16 *)((u8 *)arg1 + 0x92)), (f32) (*(s16 *)((u8 *)arg1 + 0x94)), D_800D9F40, D_800D9F3C, D_800D3A00, D_800D3A04, 0, 0) != 0)) {
        if ((*(u8 *)((u8 *)arg1 + 0)) == 8) {
            temp_v0_3 = (*(u8 *)((u8 *)arg1 + 0xB2));
            if (temp_v0_3 & (1 << arg2)) {
                (*(u8 *)((u8 *)arg1 + 0xB2)) = (u8) (temp_v0_3 | (0x10 << arg2));
            }
        }
        return gdl;
    }
    if ((*(u8 *)((u8 *)arg1 + 0)) != 9) {
        (*(u8 *)((u8 *)arg1 + 0xB2)) = (u8) ((*(u8 *)((u8 *)arg1 + 0xB2)) | (1 << arg2));
    }
    gdl = (Gfx *)func_1517AF18((s32)gdl, (*(u8 *)((u8 *)arg1 + 0x9F)));
    temp_f0 = (*(f32 *)((u8 *)arg1 + 0xA8));
    func_15043D90((Mtx *)MTX_A910(arg1), (f32) (*(s16 *)((u8 *)arg1 + 0x96)), (f32) (*(s16 *)((u8 *)arg1 + 0x98)), (f32) (*(s16 *)((u8 *)arg1 + 0x9A)), temp_f0, temp_f0, temp_f0, (f32) (*(s16 *)((u8 *)arg1 + 0x90)), (f32) (*(s16 *)((u8 *)arg1 + 0x92)), (f32) (*(s16 *)((u8 *)arg1 + 0x94)));
    gSPMatrix(gdl++, MTX_A910(arg1), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if ((*(u8 *)((u8 *)arg1 + 0xB3)) != D_800DD880) {
        gDPPipeSync(gdl++);
        MW(gdl++, 0xFA000000, (*(u8 *)((u8 *)arg1 + 0xB3)));
        D_800DD880 = (s16) (*(u8 *)((u8 *)arg1 + 0xB3));
    }
    sp43 = 0;
    temp_v0_4 = (*(u8 *)((u8 *)arg1 + 0));
    if ((temp_v0_4 == 8) || (temp_v0_4 == 9)) {
        var_a2 = 0x5049D8;
    } else {
        var_a2 = 0x504240;
    }
    gdl = func_15142FBC(gdl, D_800D30BC | 0x80000 | 0x2CA0, var_a2, &sp43);
    gSPDisplayList(gdl++, &D_8008D190);
    return gdl;
}
