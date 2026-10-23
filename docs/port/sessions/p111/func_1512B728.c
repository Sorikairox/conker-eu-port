s32 func_1512BBA0(u8 *cam, u8 *out, s32 lo, s32 hi, s32 value, s32 second);
extern s16 D_800DC630[4][4][4];
extern u8 D_800DC4F0[];
extern s32 D_800899D0[8][2];   /* z-buffer decode per exponent (code >> 13): {shift, add} */

/* free_camera_scan_depth: free-camera depth scan of camera `cam` at screen column `x` (called by func_1512B2C4;
 * `y` is not used). The scan width +0x60C and height +0x610 ease (0.05) toward the player's viewport rect
 * (D_800DC630[player][+0x1B4 slot], w / h); n = round(+0x60C). For i from n / 4 to n, left (x - i, while right of
 * the viewport's +0x2C) and then right (x + i, while left of +0x30): the z-buffer row +0x8BC is decoded
 * (D_800899D0) and depth - z goes to func_1512BBA0 with the left / right axis record of D_800DC4F0[player]
 * (+0 / +0xC; threshold 3n / 4); a hit ends that side. (The asm also keeps every depth - z in a stack array
 * nobody reads; dropped.) */
void func_1512B728(u8 *cam, s32 x, s32 y, s32 depth) {
    s16 *rect = D_800DC630[cam[0x23D]][*(s16 *)(cam + 0x1B4)];
    u8 *e;
    s32 n;
    s32 start;
    s32 i;
    u16 code;
    s32 lo;

    *(f32 *)(cam + 0x60C) += ((f32)rect[0] - *(f32 *)(cam + 0x60C)) * 0.05f;
    n = (s16)((f32)(s16)*(f32 *)(cam + 0x60C) + 0.5f);
    *(f32 *)(cam + 0x610) += ((f32)rect[1] - *(f32 *)(cam + 0x610)) * 0.05f;
    start = n / 4;
    for (i = start; i < n; i++) {
        e = (u8 *)D_800BE628 + cam[0x23D] * 0x180;
        if (*(f32 *)(e + 0x2C) < (f32)(x - i)) {
            code = (*(u16 **)(cam + 0x8BC))[x - i];
            lo = depth - ((u32)(D_800899D0[code >> 13][1] + (((code >> 2) & 0x7FF) << D_800899D0[code >> 13][0])) >> 3);
            if (func_1512BBA0(cam, D_800DC4F0 + cam[0x23D] * 0x4C, lo, i, n * 3 / 4, 0) != 0) {
                i = n;
            }
        }
    }
    for (i = start; i < n; i++) {
        e = (u8 *)D_800BE628 + cam[0x23D] * 0x180;
        if ((f32)(x + i) < *(f32 *)(e + 0x30)) {
            code = (*(u16 **)(cam + 0x8BC))[x + i];
            lo = depth - ((u32)(D_800899D0[code >> 13][1] + (((code >> 2) & 0x7FF) << D_800899D0[code >> 13][0])) >> 3);
            if (func_1512BBA0(cam, D_800DC4F0 + cam[0x23D] * 0x4C + 0xC, lo, i, n * 3 / 4, 0) != 0) {
                i = n;
            }
        }
    }
}
