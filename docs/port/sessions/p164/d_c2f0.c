s32 func_15008340(struct_eu_15144598 *, f32 *, f32 *, f32 *, f32 *);
void func_1510F800(s32);
s32 func_1510FD20(s32, s32);
s32 func_15132FBC(f32 *, s32, s32, s32, s32, s32);
extern u16 D_800964A0[9]; /* sound ids; the heavy ones (0x48, 0x4B, 0x4E..0x51) get smaller pieces */
extern f32 D_800964D0;    /* pieces per unit of record length x scale */
extern f32 D_800964D4;    /* 1 / 65535 */
extern f32 D_800964D8;    /* pi */
extern f32 D_800964DC;
extern f32 D_800964E0;
extern f32 D_800964E4;
extern f32 D_800964E8;

// record_debris_spawn: D_80082EA0 entry 0x22 (level-start record). With n = length x scale x D_800964D0
// (length = func_1514462C(rec)), spawns a piece while n > 1 (n -= 1 each): at a random point of the record
// (func_15008340: x / z and the height range lo..hi), at a random height in the middle half of the range, with
// a random radius (up to the distance to the nearer end), angle, spins and one of the D_800964A0 sounds, on the
// ground level of (x, z) (func_1510FD20), spawned by func_15132FBC (kind 3). The start dispatcher passes no scale
// (N64: a1 = the dispatcher's own address as an f32, ~3e-26), so nothing is spawned from there.
void func_1500C2F0(struct_eu_15144598 *rec, f32 scale) {
    struct {
        f32 u00;            /* 0x00 = 1 */
        f32 u04;            /* 0x04 = 1 */
        f32 size[2];        /* 0x08 */
        f32 spin[3];        /* 0x10, degrees */
        f32 u1C[3];         /* 0x1C = 1 */
        f32 pos[3];         /* 0x28 */
        f32 angle;          /* 0x34 */
        f32 y2;             /* 0x38 */
        f32 u3C;            /* 0x3C */
        f32 u40;            /* 0x40 */
        f32 u44;            /* 0x44 = 0 */
        f32 u48;            /* 0x48 */
        f32 radius;         /* 0x4C */
        s32 u50;            /* 0x50 = 0x5D40 */
        s16 u54;            /* 0x54 = 300 */
        u16 sound;          /* 0x56 */
        u8 u58;             /* 0x58 = 0 */
        s32 ground;         /* 0x5C, func_1510FD20 */
        u8 u60[8];          /* 0x60: FF, E, 0.. */
        u8 u68;             /* 0x68 = 2 */
        u8 pad69;
        u8 u6A;             /* 0x6A = 0 */
        s32 u6C;            /* 0x6C = 0 */
        u8 u70;             /* 0x70 = 0 */
        s16 u72;            /* 0x72 = 1 */
        s16 u74;            /* 0x74 = 0xFF */
    } blk;
    f32 n;
    f32 hi;
    f32 lo;
    f32 h;
    f32 y;
    f32 da;
    f32 db;
    f32 near;
    u32 c;
    u16 id;
    s32 i;

#define RND() (c = osGetCount(), (f32) ((c * func_150ADA20()) & 0xFFFF) * D_800964D4)
    n = func_1514462C(rec) * scale * D_800964D0;
    if (!(1.0f < n)) {
        return;
    }
    blk.u00 = 1.0f;
    blk.u04 = 1.0f;
    blk.u1C[0] = 1.0f;
    blk.u1C[1] = 1.0f;
    blk.u1C[2] = 1.0f;
    blk.u50 = 0x5D40;
    blk.u54 = 300;
    blk.u58 = 0;
    blk.u60[0] = 0xFF;
    blk.u60[1] = 0xE;
    for (i = 2; i < 8; i++) {
        blk.u60[i] = 0;
    }
    blk.u68 = 2;
    blk.u6A = 0;
    blk.u6C = 0;
    blk.u70 = 0;
    blk.u72 = 1;
    blk.u74 = 0xFF;
    blk.u44 = 0.0f;
    do {
        func_15008340(rec, &blk.pos[0], &blk.pos[2], &hi, &lo);
        h = hi - lo;
        y = RND() * (h * 0.5f) + (lo + h * 0.25f);
        blk.y2 = y;
        blk.pos[1] = y;
        da = y - hi;
        da = (da < 0.0f) ? -da : da;
        db = y - lo;
        db = (db < 0.0f) ? -db : db;
        near = (db < da) ? db : da;
        blk.radius = (RND() * 0.75f + 0.25f) * near;
        blk.angle = (RND() * 2.0f) * D_800964D8;
        blk.u3C = RND() * D_800964DC + D_800964E0;
        blk.spin[0] = RND() * 360.0f;
        blk.spin[1] = RND() * 360.0f;
        blk.spin[2] = RND() * 360.0f;
        blk.u40 = RND() * D_800964E4;
        blk.u48 = RND() * D_800964E8;
        c = osGetCount();
        id = D_800964A0[(c * func_150ADA20()) % 9];
        blk.sound = id;
        if (id == 0x4B || id == 0x48 || id == 0x4E || id == 0x4F || id == 0x50 || id == 0x51) {
            blk.size[0] = RND() * 0.25f + 0.5f;
        } else {
            blk.size[0] = RND() * 0.25f + 1.0f;
        }
        blk.size[1] = blk.size[0];
        func_1510F800(0);
        blk.ground = func_1510FD20((s32) blk.pos[0], (s32) blk.pos[2]);
        func_15132FBC((f32 *) &blk, 3, 0xFF, 0, 0xFF, 1);
        n -= 1.0f;
    } while (1.0f < n);
#undef RND
}
