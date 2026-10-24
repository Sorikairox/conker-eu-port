#ifdef NON_MATCHING
/* func_151559FC's sprite spec (0x58 bytes; same layout as game_eu_127840's SpriteSpecFB398). */
typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 scaleA;
    /* 0x0C */ f32 scaleB;
    /* 0x10 */ u8 kind;
    /* 0x12 */ s16 span;
    /* 0x14 */ u16 flags;
    /* 0x16 */ s16 u16;
    /* 0x18 */ s16 u18;
    /* 0x1A */ u8 u1A;
    /* 0x1B */ u8 col[9];
    /* 0x24 */ s32 u24;
    /* 0x28 */ s32 u28;
    /* 0x2C */ s32 u2C;
    /* 0x30 */ s32 u30;
    /* 0x34 */ s32 u34;
    /* 0x38 */ s32 u38;
    /* 0x3C */ s32 u3C;
    /* 0x40 */ u8 u40;
    /* 0x41 */ u8 u41;
    /* 0x44 */ u8 player;
    /* 0x48 */ f32 u48;
    /* 0x4C */ f32 u4C;
    /* 0x50 */ f32 u50;
    /* 0x54 */ f32 u54;
} SpriteSpec356D4;

typedef struct {
    u8 kind[2];
} KindPair356D4;

s32 func_151559FC(void *spec, s32 list, void *, s32, s32, s32, s32);
f32 func_151423D8(u8);
s32 func_150ADA20(void);
f32 func_150ADA68(void);
s32 memcpy(u8 *, u8 *, s32); /* as declared earlier in game_161520 */
extern KindPair356D4 D_80089F40; /* main sprite kinds */
extern s32 D_80089F44;
extern KindPair356D4 D_80089F48; /* spark kinds */

// sprite_splash_spawn: spawns a screen sprite (list 3, kind D_80089F40[random], flags 9 | random 2 (| random 4 for
// kind 0x3A), colour bytes `colA` / `colB`) at `pos` (x, y) with scale `scale`, for `span`; its +0x70 gets a 0x18
// block (`life`, random growth (100..200) x scale x 0.001, random drift 0..6 x pos x 0.001, `fadeA`, `fadeB`). When it
// exists, adds (100..400) x scale x 0.001 spark sprites (list 0, kind D_80089F48[random], random flip bits 2 / 4)
// spread around `pos` at random angles and distances, sized from the main sprite's scale.
void func_151356D4(f32 *pos, f32 scale, f32 fadeA, f32 fadeB, u8 colA, u8 colB, s16 life, s16 span, s16 u16,
                   s16 u18, u8 flag, s32 owner) {
    SpriteSpec356D4 sprite;
    struct {
        s32 u00;
        KindPair356D4 kinds;
        u8 pad06[2];
        s16 life;   /* +0x08: from here 0x18 bytes go to the sprite's +0x70 */
        f32 grow;
        f32 driftX;
        f32 driftY;
        f32 fadeA;
        f32 fadeB;
    } blk;
    SpriteSpec356D4 spark;
    KindPair356D4 sparkKinds;
    s32 rec;
    f32 mid;
    f32 n;
    f32 s;
    f32 c;
    f32 d;
    u8 a;

    blk.kinds = D_80089F40;
    blk.u00 = D_80089F44;
    blk.life = life;
    blk.grow = (func_150ADA68() * 100.0f + 100.0f) * scale * 0.001f;
    blk.driftX = func_150ADA68() * 6.0f * pos[0] * 0.001f;
    blk.driftY = func_150ADA68() * 6.0f * pos[1] * 0.001f;
    blk.fadeA = fadeA;
    blk.fadeB = fadeB;
    sprite.x = pos[0];
    sprite.y = pos[1];
    sprite.scaleA = scale;
    sprite.scaleB = scale;
    sprite.kind = blk.kinds.kind[func_150ADA20() & 1];
    sprite.span = span;
    sprite.flags = (func_150ADA20() & 1) ? 2 : 0;
    sprite.flags |= ((sprite.kind == 0x3A) ? ((func_150ADA20() & 1) ? 4 : 0) : 0) | 9;
    sprite.u16 = u16;
    sprite.u18 = u18;
    sprite.u1A = 2;
    sprite.col[0] = 0xFF;
    sprite.col[1] = 0xFF;
    sprite.col[2] = 0xFF;
    sprite.col[3] = colA;
    sprite.col[4] = 0xFF;
    sprite.col[5] = 0xFF;
    sprite.col[6] = 0xFF;
    sprite.col[7] = 0xFF;
    sprite.col[8] = colB;
    sprite.u24 = 0;
    sprite.u28 = 0;
    sprite.u2C = 0;
    sprite.u40 = 0;
    sprite.u41 = 9;
    sprite.u30 = 7;
    sprite.u34 = 0x3C;
    sprite.u38 = 0x80;
    sprite.u3C = 0x20;
    rec = func_151559FC(&sprite, 3, &blk, 1, 0x18, flag, owner);
    if (rec == 0) {
        return;
    }
    memcpy((u8 *)rec + 0x70, (u8 *)&blk.life, 0x18);

    mid = (sprite.scaleA + sprite.scaleB) * 0.5f;
    n = (func_150ADA68() * 300.0f + 100.0f) * scale * 0.001f;
    spark.span = 0x32;
    spark.flags = 9;
    spark.u16 = 0x10;
    spark.u18 = 0xF;
    spark.u1A = 3;
    spark.col[0] = 0xFF;
    spark.col[1] = 0xFF;
    spark.col[2] = 0xFF;
    spark.col[3] = colA;
    spark.col[4] = 0xFF;
    spark.col[5] = 0xFF;
    spark.col[6] = 0xFF;
    spark.col[7] = 0xFF;
    spark.col[8] = colB;
    spark.u24 = 0;
    spark.u28 = 0;
    spark.u2C = 0;
    spark.u40 = 0;
    spark.u41 = 9;
    spark.u30 = 7;
    spark.u34 = 0x3C;
    spark.u38 = 0x40;
    spark.u3C = 0;
    spark.scaleA = (func_150ADA68() * 120.0f + 80.0f) * (scale * mid) * 0.0001f;
    spark.scaleB = (func_150ADA68() * 120.0f + 80.0f) * (scale * mid) * 0.0001f;
    for (; n > 1.0f; n -= 1.0f) {
        sparkKinds = D_80089F48;
        a = func_150ADA20();
        c = func_151423D8(a - 0x40);
        s = func_151423D8(a);
        d = (func_150ADA68() * 300.0f + 1300.0f) * mid * 0.001f;
        spark.x = pos[0] + d * s;
        spark.y = pos[1] + d * c;
        spark.flags &= ~6;
        spark.kind = sparkKinds.kind[func_150ADA20() & 1];
        if (func_150ADA20() & 1) {
            spark.flags |= 2;
        }
        if (func_150ADA20() & 1) {
            spark.flags |= 4;
        }
        func_151559FC(&spark, 0, 0, 0, 0, flag, owner);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_151356D4.s")
#endif
