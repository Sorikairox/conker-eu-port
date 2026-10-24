// landing_dust_burst: P201: the burst of effects under the character `obj` (the only caller, func_15070014, passes
// D_800D154C) when it lands / stamps: position = obj x, y + 100, z; the ground below it (func_15046F70 down to
// y - 300, HitInfo started by func_1504715C) gives y, else the floor height obj +0x180. Rumbles the current
// player's pad (func_1512D748(view, 7, 1)), takes the ground colour at the position (func_150CD2A0, three floats
// -> bytes), shakes the camera (func_151D5404) and creates a 13-point dust ring (func_150C8DD0, view 0xFF, group 1).
// On real ground it also throws four dust puffs (func_1513C5B0 kinds 0x51..0x54) at the corners of a square of
// half-size (rand * 96 + 352) / 2 turned by the character's yaw (obj +0x7A), then func_150CAE30 and a debris spray
// func_1514CBE8 in the ground colour. The N64 code also sums the code words func_15194210..func_151942B0 and on a
// mismatch (anti-tamper) clears the matrix count D_800C3E7C; the port has no MIPS code there, so the
// NON_MATCHING build skips the check (as func_150AEB9C, func_151E86A4).
s32 func_15046F70(u8 *, u16, f32, u8 *);
void func_1504715C(void *, u8 *);
u8 *func_150C8DD0(u8 *spec, s32 extra, s32 view, s32 arg3);
void func_150CAE30(u8 *arg0);
void func_1514CBE8(f32, f32, f32, f32, s16, s16, s16, u8, s32, f32, s32, u8);
extern s32 D_800BEE08;

typedef struct {
    s16 rgb[3];
    s16 a;
    s16 z;
} DustColour;           /* 10 bytes, 4 of them (one per corner) */

typedef struct {
    s32 w0;             /* +0x00 0x701 */
    s16 h4;             /* +0x04 0x408 */
    u8 kind;            /* +0x06 0x51..0x54 */
    u8 pad7;
    s32 w8, wC;         /* +0x08 0 */
    u8 life;            /* +0x10 rand % 41 + 0xB4 */
    u8 b11, b12, b13, b14, b15, b16, b17;
    s32 w18;            /* +0x18 0x260001 */
} DustPuff;

typedef struct {
    f32 pos[3];         /* +0x00 */
    u8 b0C;             /* +0x0C 1 */
    s8 b0D;             /* +0x0D -1 */
    u8 pad0E[2];
    f32 f10;            /* +0x10 43.2 */
    s32 n;              /* +0x14 13 points */
    s16 s18, s1A;       /* +0x18 0x65, 0x58 */
    f32 f1C;            /* +0x1C */
    s16 s20;            /* +0x20 0x13 */
    u8 pad22[2];
    f32 f24, f28;       /* +0x24 */
    u8 b2C, b2D;        /* +0x2C 1, 0 */
    u8 pad2E[2];
} DustRing;

void func_150CA150(u8 *obj) {
    f32 pos[3];
    f32 r, g, b;
    u8 cr, cg, cb;
    f32 hit[9];
    DustRing ring;
    DustPuff puff;
    DustColour col[4];
    u8 rgb[4];
    f32 s, c, size;
    f32 ps, pc, nc, ns;
    u8 found, angle;
    s32 i;

    found = 0;
    if (obj == NULL) {
        return;
    }
    func_1504715C(hit, obj);
    func_1512D748((struct108 *) ((u8 *) D_800DBFF0 + D_800BEE08 * 0x9A0), 7, 1);
    pos[0] = *(f32 *) (obj + 0x14);
    pos[1] = *(f32 *) (obj + 0x18) + 100.0f;
    pos[2] = *(f32 *) (obj + 0x1C);
    if (func_15046F70((u8 *) pos, 0, *(f32 *) (obj + 0x18) - 300.0f, (u8 *) hit)) {
        found = 1;
        pos[1] = hit[0];
    } else {
        pos[1] = *(f32 *) (obj + 0x180);
    }
    func_150CD2A0(pos[2], &r, &g, &b);
    cr = (u32) r;
    cg = (u32) g;
    cb = (u32) b;
    func_151D5404((struct17 *) pos, 500.0f, 5000.0f, 0.0002f, 0xC, 0xF, 0xFF, 0);

    ring.pos[0] = pos[0];
    ring.pos[1] = pos[1];
    ring.pos[2] = pos[2];
    ring.b0C = 1;
    ring.b0D = -1;
    ring.f10 = 43.2f;
    ring.n = 13;
    ring.s18 = 0x65;
    ring.s1A = 0x58;
    ring.f1C = 21.800001f / 13.0f;
    ring.s20 = 0x13;
    ring.f24 = 21.800001f / 19.0f;
    ring.f28 = 8e-05f;
    ring.b2C = 1;
    ring.b2D = 0;
    func_150C8DD0((u8 *) &ring, 0, 0xFF, 1);
    if (!found) {
        return;
    }

    angle = -0x40 - (*(u16 *) (obj + 0x7A) >> 8);
    s = func_151423D8(angle);
    c = func_151423D8((u8) (angle - 0x40));
    size = (func_150ADA68() * 96.0f + 352.0f) * 0.5f;
    puff.w0 = 0x701;
    func_150ADA20();
    puff.h4 = 0x408;
    puff.w8 = 0;
    puff.wC = 0;
    puff.life = func_150ADA20() % 41U + 0xB4;
    puff.b11 = puff.b12 = puff.b13 = 0xFF;
    puff.b14 = 0xFF;
    puff.b15 = 0xFF;
    puff.b16 = 0;
    puff.b17 = 6;
    puff.w18 = 0x260001;
    for (i = 0; i < 4; i++) {
        col[i].rgb[0] = cr;
        col[i].rgb[1] = cg;
        col[i].rgb[2] = cb;
        col[i].a = 0xFF;
        col[i].z = 0;
    }
    /* the four corners: ps / pc = size * sin / cos of the yaw, ns / nc = -size * sin / cos */
    ps = size * s;
    pc = size * c;
    puff.kind = 0x51;
    func_1513C5B0((s32) &puff, (s32) col, 0xC, 0, (ps + pos[0]) - pc, pos[1] + 10.0f, (ps + pos[2]) + pc, size, size,
                  angle, 0, 0, 0xFF, 0);
    nc = (-1.0f * size) * c;
    ns = (-1.0f * size) * s;
    puff.kind = 0x52;
    func_1513C5B0((s32) &puff, (s32) col, 0xC, 0, (ps + pos[0]) - nc, pos[1] + 10.0f, (ns + pos[2]) + pc, size, size,
                  angle, 0, 0, 0xFF, 0);
    puff.kind = 0x53;
    func_1513C5B0((s32) &puff, (s32) col, 0xC, 0, (ns + pos[0]) - pc, pos[1] + 10.0f, (ps + pos[2]) + nc, size, size,
                  angle, 0, 0, 0xFF, 0);
    puff.kind = 0x54;
    func_1513C5B0((s32) &puff, (s32) col, 0xC, 0, (ns + pos[0]) - nc, pos[1] + 10.0f, (ns + pos[2]) + nc, size, size,
                  angle, 0, 0, 0xFF, 0);
    func_150CAE30((u8 *) pos);
    i = func_150ADA20() % 21U + 0xA;
    rgb[0] = cr;
    rgb[1] = cg;
    rgb[2] = cb;
    func_1514CBE8(pos[0], pos[1], pos[2], func_150ADA68() * 81.0f + 150.0f, 0, 0xFF, (s16) i, 0x14, 0, 0.0f,
                  (s32) rgb, 0xFF);
}
