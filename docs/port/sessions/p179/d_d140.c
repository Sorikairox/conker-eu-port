extern s16 D_800A22B0[];
s32 func_15154728(f32 *, f32, f32, f32, f32, s32, s32);
void func_15143874(s16, f32, f32 *, f32 *);
void func_15150258(u8 *, u8, s32);

// view_sparkle_burst: P179: one flash plus 3..4 spark sprays at view `view`'s spot (D_800D9AA0[view], 0..2: s16 x, y,
/* z, radius +6, height +8; nothing when the slot is NULL). The flash (func_15154728) sits at the middle of the
 * height: size random * 4 + 12, brightness 200..255. Each spray (func_15150258 block, layout of func_15150258 in
 * game_eu_17D3C0) starts on the circle of the spot's radius at angle base + random [0, range] (D_800A22B0[view]:
 * s16 base, range; angle byte), at a random height in [y, y + height], and fans out from that angle - 40 over 80. */
void func_150FD140(u8 view) {
    s16 *spot;
    s16 *arc;
    f32 pos[3];
    f32 size;
    u32 r;
    s16 n;
    struct {
        s16 angle;      /* +0x00 */
        s16 angleRange; /* +0x02 */
        s16 pitch;      /* +0x04 */
        s16 pitchRange; /* +0x06 */
        s32 count;      /* +0x08 */
        s32 countRange; /* +0x0C */
        f32 pos[3];     /* +0x10 */
        f32 f1C;
        f32 f20;
        f32 f24;
        f32 f28;
        f32 f2C;
        f32 f30;
        s32 i34;
        s32 i38;
        f32 f3C;
        f32 f40;
        f32 f44;
        f32 f48;
        s16 h4C;
        s16 h4E;
        s16 h50;
        s16 h52;
        s16 h54;
        s16 h56;
        s8 b58;
    } spray;
    u8 a;

    if (view >= 3) {
        return;
    }
    spot = (s16 *) D_800D9AA0[view];
    if (spot == NULL) {
        return;
    }
    pos[0] = spot[0];
    pos[1] = spot[1] + spot[4] * 0.5f;
    pos[2] = spot[2];
    size = func_150ADA68();
    r = func_150ADA20();
    func_15154728(pos, size * 4.0f + 12.0f, 6.6943097f, r % 56 + 200, 2.6090002f, 0xFF, 1);
    n = (func_150ADA20() & 1) + 3;
    if (n <= 0) {
        return;
    }
    spray.angleRange = 0x50;
    spray.pitch = -0x20;
    spray.pitchRange = 0x2B;
    spray.count = 1;
    spray.countRange = 8;
    spray.f1C = 249.0f;
    spray.f20 = 451.0f;
    spray.f24 = 506.0f;
    spray.f28 = 100.0f;
    spray.f2C = 1505.0f;
    spray.f30 = 1511.0f;
    spray.i34 = 3;
    spray.i38 = 2;
    spray.f3C = 90.0f;
    spray.f40 = 0.813f;
    spray.f44 = -2.0f;
    spray.f48 = 1.085f;
    spray.h4C = 0xC;
    spray.h4E = 0x32;
    spray.h50 = 0x64;
    spray.h52 = 0x64;
    spray.h54 = 0xC;
    spray.h56 = 0xC;
    spray.b58 = -1;
    arc = &D_800A22B0[view * 2];
    do {
        a = func_150ADA20() % (u32) (arc[1] + 1) + arc[0];
        spray.angle = a - 0x28;
        func_15143874(a, spot[3], &spray.pos[0], &spray.pos[2]);
        spray.pos[0] += spot[0];
        spray.pos[2] += spot[2];
        spray.pos[1] = func_150ADA68() * spot[4] + spot[1];
        func_15150258((u8 *) &spray, 0xFF, 1);
        n--;
    } while (n > 0);
}
