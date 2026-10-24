#ifdef NON_MATCHING
/* func_15132FBC / func_15132BBC particle request (0x7C bytes on the stack; layout as in game_eu_E9450) */
typedef struct {
    /* 0x00 */ f32 u00;
    /* 0x04 */ f32 u04;
    /* 0x08 */ f32 u08;
    /* 0x0C */ f32 u0C;
    /* 0x10 */ f32 pos[3];
    /* 0x1C */ f32 scl[3];
    /* 0x28 */ f32 at[3];
    /* 0x34 */ f32 vel[3];
    /* 0x40 */ f32 u40;
    /* 0x44 */ f32 u44;
    /* 0x48 */ f32 u48;
    /* 0x4C */ f32 u4C;
    /* 0x50 */ s32 u50;
    /* 0x54 */ s16 life;
    /* 0x56 */ s16 u56;
    /* 0x58 */ u8 u58;
    /* 0x59 */ u8 pad59[3];
    /* 0x5C */ s32 u5C;
    /* 0x60 */ u8 u60[8];
    /* 0x68 */ u8 u68;
    /* 0x69 */ u8 pad69;
    /* 0x6A */ u8 u6A;
    /* 0x6B */ u8 pad6B;
    /* 0x6C */ struct127 *obj;
    /* 0x70 */ u8 uid;
    /* 0x71 */ u8 pad71;
    /* 0x72 */ s16 u72;
    /* 0x74 */ s16 u74;
    /* 0x76 */ u8 pad76[6];
} Spark9768;
extern u8 D_800A45A4[4];        /* 4 bit masks (one picked at random): which of the 4 corner sparks / smoke puffs */
extern s32 D_800A45A8[4];       /* spark sprite ids (0x61..0x64) */
extern s32 D_800A45B8[4];       /* smoke sprite ids (0x5D..0x60) */
extern f32 D_800A45C8[4][3];    /* smoke start points in model space */
s32 func_15132FBC(Spark9768 *, s32, s32, s32, u8, s32);
s32 func_15132BBC(Spark9768 *, s32, s32, s32, s32, u8, s32);
void func_151C64F4(s32, f32 *, f32, f32, s32, s32, f32, s32, s32, u8, s32);
void func_1503F6F4(void *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
void func_15143794(s16, s16, f32, f32 *);
s32 memcpy(u8 *, u8 *, s32);

// object_hit_sparks: hit effects on object `obj` (func_15138C80, hit types 15 / 2 with scale 0.6 / 1.0). One of
// four bit masks (D_800A45A4) is picked at random. For each set bit, a func_15132FBC spark (kind 3, sprite
// D_800A45A8[i], size (xz_scale + y_scale) / 2 * scale) whose new particle gets the extra byte 12 at +0x170.
// If the object has a model (+0x1D4) and (+0x74 & 0xF) != 0xF: 5..8 func_151C64F4 debris pieces from `pos` (random
// direction, speed 6..12) and, for each clear bit, a func_15132BBC smoke puff from the model point
// D_800A45C8[i] (model matrix +0x300, func_15143134), sprite D_800A45B8[i], life 60..160. kind (u8) and owner go to
// every spawn, `arg3` to the debris and the puffs. The asm returns a leftover v0 that no caller reads.
void func_15139768(struct127 *obj, s32 *pos, f32 scale, s32 *arg3, u8 kind, s32 owner) {
    Spark9768 smoke;
    f32 rot[3];
    f32 scl[3];
    f32 dir[3];
    Spark9768 spark;
    u8 extra;
    f32 trans[3];
    u8 *mask;
    u8 bit;
    s32 i;
    s32 n;
    s32 a;
    s32 b;
    f32 f;
    f32 size;
    u8 *p;

    mask = &D_800A45A4[func_150ADA20() & 3];
    extra = 12;
    spark.u00 = 1.0f;
    spark.u04 = 1.0f;
    size = (obj->xz_scale + obj->y_scale) * 0.5f * scale;
    spark.pos[0] = 0.0f;
    spark.pos[1] = 0.0f;
    spark.pos[2] = 0.0f;
    spark.u0C = size;
    spark.u08 = size;
    spark.at[0] = 0.0f;
    spark.at[1] = 0.0f;
    spark.at[2] = 0.0f;
    spark.vel[0] = 0.0f;
    spark.vel[1] = 0.0f;
    spark.vel[2] = 0.0f;
    spark.u40 = 0.0f;
    spark.u44 = 0.0f;
    spark.u48 = 0.0f;
    spark.u4C = 0.0f;
    spark.u50 = 0x101900;
    spark.life = 100;
    spark.u58 = 5;
    spark.u5C = 0;
    spark.u60[0] = 0xFF;
    spark.u60[1] = 0;
    spark.u60[2] = 0;
    spark.u60[3] = 0;
    spark.u60[4] = 0;
    spark.u60[5] = 0;
    spark.u60[6] = 0;
    spark.u60[7] = 0;
    spark.u68 = 5;
    spark.u6A = 1;
    spark.obj = obj;
    spark.scl[0] = 1.0f;
    spark.scl[1] = 1.0f;
    spark.scl[2] = 1.0f;
    spark.u72 = 12;
    spark.u74 = 21;
    spark.uid = obj->unique_id;
    for (i = 0, bit = 1; i < 4; i++, bit <<= 1) {
        if (*mask & bit) {
            spark.u56 = D_800A45A8[i];
            p = (u8 *) func_15132FBC(&spark, 3, 0xFF, 1, kind, owner);
            if (p != NULL) {
                memcpy(p + 0x170, &extra, 1);
            }
        }
    }

    if (obj->unk1D4 == NULL || (obj->unk74 & 0xF) == 0xF) {
        return;
    }
    for (n = (func_150ADA20() & 3) + 5; n > 0; n--) {
        a = func_150ADA20();
        b = func_150ADA20();
        f = func_150ADA68() * 6.0f + 6.0f;
        func_15143794(a & 0xFF, (u32) b % 71 - 60, f, dir);
        f = func_150ADA68();
        a = func_150ADA20();
        b = func_150ADA20();
        func_151C64F4((s32) pos, dir, f * 0.117000006f + -0.19700001f, 0.950865f, (u32) a % 66 + 190,
                      (u32) b % 45 + 44, func_150ADA68() * 20.0f + 50.0f, 0, (s32) arg3, kind, owner);
    }

    func_1503F6F4((u8 *) obj->unk1D4 + 0x300, &scl[0], &scl[1], &scl[2], &trans[0], &trans[1], &trans[2], &rot[0],
                  &rot[1], &rot[2]);
    smoke.u00 = 1.0f;
    smoke.u04 = 0.64900005f;
    size = (obj->xz_scale + obj->y_scale) * 0.5f * scale;
    smoke.u0C = size;
    smoke.u08 = size;
    smoke.pos[0] = trans[0];
    smoke.pos[1] = trans[1];
    smoke.pos[2] = trans[2];
    smoke.u44 = 0.0f;
    smoke.u58 = 0;
    smoke.u5C = 0;
    smoke.u60[0] = 0xFF;
    smoke.u60[2] = 0;
    smoke.u60[4] = 0;
    smoke.u60[5] = 0;
    smoke.u60[6] = 0;
    smoke.u60[7] = 0;
    smoke.u6A = 1;
    smoke.obj = obj;
    smoke.scl[0] = 1.0f;
    smoke.scl[1] = 1.0f;
    smoke.scl[2] = 1.0f;
    smoke.u72 = 12;
    smoke.u74 = 21;
    smoke.u50 = 0x1039E9;
    smoke.u60[1] = 13;
    smoke.u68 = 2;
    smoke.u60[3] = 9;
    smoke.uid = obj->unique_id;
    for (i = 0, bit = 1; i < 4; i++, bit <<= 1) {
        if (!(*mask & bit)) {
            smoke.u56 = D_800A45B8[i];
            func_15143134(D_800A45C8[i], smoke.at, (u8 *) obj->unk1D4 + 0x300);
            a = func_150ADA20();
            b = func_150ADA20();
            func_15143794(a & 0xFF, (u32) b % 35 - 84, func_150ADA68() * 6.12f + 3.0f, smoke.vel);
            smoke.u40 = func_150ADA68() * 30.746002f + -15.373001f;
            smoke.u48 = func_150ADA68() * 30.746002f + -15.373001f;
            smoke.u4C = func_150ADA68() * 0.208f + -0.708f;
            smoke.life = (u32) func_150ADA20() % 101 + 60;
            func_15132BBC(&smoke, 3, 0xFF, (s32) arg3, 0, kind, owner);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15139768.s")
#endif
