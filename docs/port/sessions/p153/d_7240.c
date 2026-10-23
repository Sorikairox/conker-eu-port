s32 func_151A74B0(void *spray, s32 arg1, u8 arg2, s32 arg3);
void func_151D58E4(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, s32 arg6);
void func_151D45A4(u8 *, u8, s32);
void func_151D5AC4(u8 *, u8, s32);
void func_15154728(u8 *, f32, f32, f32, f32, u8, s32);

/* the stack blocks of func_151A7240 (sp40 spray block for func_151A74B0, then the position at sp9C) */
typedef struct {
    struct {
        s16 count;        /* 0x00: 6..9 */
        u8 pad2[2];
        f32 pos[3];       /* 0x04 */
        s16 u10;          /* 0x10 */
        u8 pad12[2];
        f32 u14;          /* 0x14 */
        s16 u18[4];       /* 0x18 */
        f32 u20[12];      /* 0x20 */
        f32 u50;          /* 0x50 */
        u8 u54;           /* 0x54 */
        u8 u55;           /* 0x55 */
        s16 u56;          /* 0x56 */
        s16 u58;          /* 0x58 */
        u8 pad5A[2];
    } spray;
    f32 pos[3];           /* sp9C */
} Frame7240;

// object_explosion_effects: P153: the effect set of an exploding object at obj's position (+0x14): a spray of 6..9
// pieces (func_151A74B0), the flash / sparks / smoke spawners func_151D58E4 (506, 1013, 0.000987, 5),
// func_151D45A4 and func_151D5AC4, a random-sized burst (func_15154728: size 12..16, 1.641, brightness 200..255)
// and the screen shake func_151D5404 (1502, 3000, 1/3000, 12, 15). The original reads the position before its
// NULL test.
void func_151A7240(u8 *obj, u8 arg1, s32 arg2) {
    Frame7240 f;
    f32 r;
    f32 size;

    f.pos[0] = *(f32 *) (obj + 0x14);
    f.pos[1] = *(f32 *) (obj + 0x18);
    f.pos[2] = *(f32 *) (obj + 0x1C);
    if (obj == NULL) {
        return;
    }
    f.spray.count = (func_150ADA20() & 3) + 6;
    f.spray.pos[0] = f.pos[0];
    f.spray.pos[1] = f.pos[1];
    f.spray.pos[2] = f.pos[2];
    f.spray.u14 = 60.0f;
    f.spray.u20[0] = 0.0f;
    f.spray.u20[1] = 35.0f;
    f.spray.u10 = 0x50;
    f.spray.u18[0] = 0;
    f.spray.u18[1] = 0xFF;
    f.spray.u18[2] = -0x3F;
    f.spray.u18[3] = 0x50;
    f.spray.u54 = 0;
    f.spray.u55 = 0;
    f.spray.u56 = 0x32;
    f.spray.u58 = 0x19;
    f.spray.u20[9] = -1.0f;
    f.spray.u20[10] = -1.0f;
    f.spray.u20[4] = 0.0f;
    f.spray.u20[5] = 0.0f;
    f.spray.u20[6] = 0.0f;
    f.spray.u20[2] = 10.0f;
    f.spray.u20[3] = 40.0f;
    f.spray.u20[7] = 0.2f;
    f.spray.u20[8] = 0.5f;
    f.spray.u20[11] = -2.0f;
    f.spray.u50 = 4.0f;
    func_151A74B0(&f.spray, 0, arg1, arg2);
    func_151D58E4((u8 *) f.pos, 506.0f, 1013.0f, 0.0009871669f, 5, arg1, arg2);
    func_151D45A4((u8 *) f.pos, arg1, arg2);
    func_151D5AC4((u8 *) f.pos, arg1, arg2);
    r = func_150ADA68();
    size = r * 4.0f + 12.0f;
    func_15154728((u8 *) f.pos, size, 1.6409999f, (f32) ((u32) func_150ADA20() % 56 + 200), 0.0f, arg1, arg2);
    func_151D5404((struct17 *) f.pos, 1502.0f, 3000.0f, 0.00033333333f, 0xC, 0xF, 0xFF, 0);
}
