#ifdef NON_MATCHING
void func_1514470C(u8 *node, u8 *pos);
void func_150F4AF0(u8 *arg0, u8 *arg1, u8 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9);
extern u8 D_80088ECC;   /* number of bolt styles */
extern u8 *D_80088ED0;  /* per style: 2 bytes, [1] = colour index */
extern f32 *D_80088ED4; /* per style: width */
// arc_bolts_emit: handler 25 of D_8008A980 (`void (u8 *)`). Accumulates (0.08 + 0.18 * random) * D_800BE9A4 bolts
// per frame in +0x30; for each whole bolt it spawns one (func_150F4AF0) between the positions of the nodes +0x28 and
// +0x2C (func_1514470C), with a random style (D_80088ECC styles: colour D_80088ED0[2 * i + 1], width D_80088ED4[i] *
// (1..2)), length 30..55 (and 1 / length), life 750..752, and the object's +0x0C / +0x01 bytes.
void func_150FB06C(u8 *arg0) {
    u8 *ends = arg0 + 0x28;
    f32 from[3];
    f32 to[3];
    u32 style;
    f32 len;
    f32 width;

    ((f32 *) ends)[2] += (0.0800000057f + func_150ADA68() * 0.18f) * D_800BE9A4;
    while (1.0f < ((f32 *) ends)[2]) {
        func_1514470C(((u8 **) ends)[0], (u8 *) from);
        func_1514470C(((u8 **) ends)[1], (u8 *) to);
        style = (u8) ((u32) func_150ADA20() % D_80088ECC);
        len = func_150ADA68() * 25.0f + 30.0f;
        width = func_150ADA68();
        func_150F4AF0((u8 *) from, (u8 *) to, D_80088ED0[style * 2 + 1], len, 1.0f / len,
                      (width * 1.0f + 1.0f) * D_80088ED4[style], 1, (u32) func_150ADA20() % 3 + 750, arg0[0xC], arg0[1]);
        ((f32 *) ends)[2] -= 1.0f;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FB06C.s")
#endif
