/*
 * P53: collision cylinder of a record for the wall tests: D_800CC1F8 = height, D_800CC1FC = lift above the feet,
 * from func_1507C7C0's height (sp2E) and the record kind / state. arg2 is the y the record moves to.
 * For kinds 0x2C-0x2E the asm reads an uninitialised stack word (sp+0x20) as the record index; it only matters
 * for kinds other than 5 / 0x53 / 0x28 / 0x25 with no in-water flag, where the C uses -1 (index check fails).
 */
s32 func_1507C7C0(u8 *, s16 *, s16 *, s16 *);
extern f32 D_800CC1F8;
extern f32 D_800CC1FC;
extern s8 D_8008FD8C;

void func_15044950(u8 *arg0, f32 arg1, f32 arg2, s32 arg3) {
    s16 h;
    s16 w0;
    s16 w1;
    s32 idx;
    s32 half;
    s32 kind;

    func_1507C7C0(arg0, &h, &w0, &w1);
    kind = *(s32 *)arg0;
    if (kind == 0x2D || kind == 0x2E || kind == 0x2C) {
        idx = -1;
        D_800CC1FC = 0.0f;
        D_800CC1F8 = (f32)h;
    } else {
        idx = (struct127 *)arg0 - D_800CC2D0;
        h = (s32)((f32)h + fabsf(arg2 - *(f32 *)(arg0 + 0x18)));
    }
    if (arg0[5] == 5) {
        D_800CC1FC = 0.0f;
        D_800CC1F8 = (f32)h;
        return;
    }
    if (arg0[0xAD] != 0) {
        D_800CC1F8 = (f32)h;
        D_800CC1FC = (f32)(h >> 1);
        return;
    }
    if (arg0[4] == 0x53) {
        D_800CC1F8 = (f32)h;
        D_800CC1FC = (f32)(h >> 1);
        return;
    }
    if (arg0[4] == 0x28) {
        D_800CC1F8 = (f32)(h - 20);
        D_800CC1FC = 20.0f + D_800CC1F8 * 0.5f;
        return;
    }
    if (idx >= 0 && idx < D_8008FD8C && *(f32 *)(arg0 + 0x28) != 0.0f) {
        D_800CC1F8 = (f32)h;
        D_800CC1FC = (f32)(h >> 1);
        return;
    }
    if (arg0[4] == 0x25) {
        half = h / 2;
        D_800CC1F8 = (f32)(h - half);
        D_800CC1FC = (f32)half + D_800CC1F8 * 0.5f;
        return;
    }
    D_800CC1F8 = (f32)h;
    D_800CC1FC = (f32)(h >> 1);
}
