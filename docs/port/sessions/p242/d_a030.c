#ifdef NON_MATCHING
void func_151108E0(s32 arg0, f32 (*arg1)[4], f32 arg2, f32 arg3, f32 arg4);
Gfx *func_15110AC4(Gfx *gdl, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 r, u8 g, u8 b);
Gfx *func_150FBA40(Gfx *gdl, f32 (*mtx)[4]);

// camera_view_clear_draw: camera callback (D_80089578[1], called by func_15110420 with the D_80089578 signature):
// builds the current player's view matrix from yaw / pitch / roll (func_151108E0), clears the player's viewport
// (D_800BE628[D_80082FA4] +0x24..0x30) to black (func_15110AC4), sets pipe sync, other modes 0xEF002C0F / 0x0F0A4004
// and combiner 0xFC357E6A / 0xFFFFFFFF, and draws with the matrix (func_150FBA40, which returns the new list end).
// The position and handle arguments are unused.
Gfx *func_150FA030(Gfx *gdl, f32 x, f32 y, f32 z, f32 yaw, f32 pitch, f32 roll, s32 handle) {
    f32 mtx[4][4];
    u8 *cam;

    func_151108E0(D_80082FA4, mtx, yaw, pitch, roll);
    cam = (u8 *) D_800BE628 + D_80082FA4 * 0x180;
    gdl = func_15110AC4(gdl, (s32) *(f32 *) (cam + 0x2C), (s32) *(f32 *) (cam + 0x24),
                        (s32) (*(f32 *) (cam + 0x30) - 1.0f), (s32) *(f32 *) (cam + 0x28), 0, 0, 0);
    gdl[0].words.w0 = 0xE7000000;
    gdl[0].words.w1 = 0;
    gdl[1].words.w0 = 0xEF002C0F;
    gdl[1].words.w1 = 0x0F0A4004;
    gdl[2].words.w0 = 0xFC357E6A;
    gdl[2].words.w1 = 0xFFFFFFFF;
    return func_150FBA40(gdl + 3, mtx);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FA030.s")
#endif
