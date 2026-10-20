s32 func_1513F4E4(s32, u8, s8 *);
s32 func_15142B7C(Gfx *, s32, s32);
s32 func_15142C10(s32, s16, s16, s16, s32, s8 *);
s32 func_15142CF0(s32, s32, s32, s16, s32, s32, s32, s8 *);
Gfx *func_15142FBC(s32, s32, s32, s8 *);
s32 func_151441A4(s16 *, s16 *, s16 *, s16 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_151442FC(s16 *, s16 *, s16 *, s16 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
Gfx *func_151462C8(Gfx *, u8 *, u8, s32, s32, s32, u8 *, s32, s32);
extern s32 (*D_8008B1AC[])(f32 *, u8 *);
extern s32 D_8008B358[];
extern s32 D_800A4EA8[][2];
#define MTX_8838(a) (((f32 (*)[16])((a) + 0x58))[D_800BE9C0])
Gfx *func_15158838(Gfx *arg0, u8 *arg1, s16 arg2) {
    s16 sp6A;
    s16 sp68;
    s16 sp66;
    s16 sp64;
    s16 sp62;
    s16 sp60;
    s16 sp5E;
    s16 sp5C;
    s8 sp5B;
    s32 var_v0;
    s8 temp_v0;
    u8 temp_v1_2;
    Gfx *var_s1;

    var_s1 = arg0;
    sp5B = 1;
    temp_v0 = (*(s8 *)((u8 *)arg1 + 0x13));
    if ((temp_v0 != -1) && (D_8008B1AC[temp_v0](MTX_8838(arg1), arg1) == 0)) {
        return var_s1;
    }
    var_s1 = (Gfx *)func_15142B7C(var_s1, (*(s32 *)((u8 *)arg1 + 0x1C)), (*(s32 *)((u8 *)arg1 + 0x20)));
    func_151441A4(&sp6A, &sp68, &sp66, &sp64, (s32) (*(u8 *)((u8 *)arg1 + 0x3C)), (s32) (*(u8 *)((u8 *)arg1 + 0x3D)), (s32) (*(u8 *)((u8 *)arg1 + 0x3E)), (s32) (*(u8 *)((u8 *)arg1 + 0x3F)), (s32) (*(u8 *)((u8 *)arg1 + 0x38)), (s32) (*(u8 *)((u8 *)arg1 + 0x39)), (s32) (*(u8 *)((u8 *)arg1 + 0x3A)), (s32) (*(u8 *)((u8 *)arg1 + 0x3B)), 0xFF, (s32) (*(s8 *)((u8 *)arg1 + 0x34)));
    func_151442FC(&sp62, &sp60, &sp5E, &sp5C, (s32) (*(u8 *)((u8 *)arg1 + 0x3C)), (s32) (*(u8 *)((u8 *)arg1 + 0x3D)), (s32) (*(u8 *)((u8 *)arg1 + 0x3E)), (s32) (*(u8 *)((u8 *)arg1 + 0x3F)), (s32) (*(u8 *)((u8 *)arg1 + 0x38)), (s32) (*(u8 *)((u8 *)arg1 + 0x39)), (s32) (*(u8 *)((u8 *)arg1 + 0x3A)), (s32) (*(u8 *)((u8 *)arg1 + 0x3B)), 0xFF, (s32) (*(s8 *)((u8 *)arg1 + 0x35)));
    var_s1 = func_15142FBC(func_1513F4E4(func_15142CF0(func_15142C10((s32)var_s1, sp62, sp60, sp5E, (s32) sp5C, &sp5B), 0, 0, sp6A, (s32) sp68, (s32) sp66, (s32) sp64, &sp5B), (*(u8 *)((u8 *)arg1 + 0x2B)), &sp5B), *(s32 *)(arg1 + 0x18) | 0x80000 | 0x2C00 | *(s32 *)(arg1 + 0x2C) | *(s32 *)(arg1 + 0x30), D_800A4EA8[*(s32 *)(arg1 + 0x24)][1] | D_800A4EA8[*(s32 *)(arg1 + 0x24)][0], &sp5B);
    temp_v1_2 = (*(u8 *)((u8 *)arg1 + 0x10));
    if (temp_v1_2 & 2) {
        if (temp_v1_2 & 4) {
            var_v0 = 1;
        } else {
            var_v0 = 0;
        }
        var_s1 = func_151462C8(var_s1, arg1 + 0xD8, (*(u8 *)((u8 *)arg1 + 0x45)), (*(s32 *)((u8 *)arg1 + 0x40)), (s32) (*(u8 *)((u8 *)arg1 + 0x44)), (s32) arg2, arg1 + 0x48, var_v0, 0);
    }
    gSPMatrix(var_s1++, MTX_8838(arg1), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(var_s1++, D_8008B358[*(u8 *)(arg1 + 0x16)]);
    return var_s1;
}
