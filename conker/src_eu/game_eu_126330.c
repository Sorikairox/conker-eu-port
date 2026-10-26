#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted forward declaration(s) for fire_handle_event
void fire_burn_update(u8 *arg0);

typedef struct { s32 x, y, z; } V3i;
s32 func_151530A8(s32 *, u8, s32);

/* was func_150F8B20 */
void fire_flash_burst_spawn(s32 arg0, u8 *arg1, s32 arg2) {

    f32 pos[3];
    Header header;
    Header2 header2;
    struct {
        s32 u3C;
        s32 u40;
        s32 u44;
        u8 pad48[0x8];
        f32 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        s16 u68;
        s16 u6A;
        s16 u6C;
        s16 u6E;
        s32 u70;
        s32 u74;
        s16 u78;
        s16 u7A;
        s16 u7C;
        s8 u7E;
        s8 u7F;
        s8 u80;
        u8 u81;
        u8 u82;
        u8 u83;
        u8 u84;
        s8 u85;
        s8 u86;
        s8 u87;
        s8 u88;
        u8 u89;
        u8 u8A;
        u8 u8B;
        u8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
        s8 u90;
        u8 u91;
        s8 u92;
        s8 u93;
        s8 u94;
        u8 pad95[0x3];
        s32 u98;
        s32 u9C;
        s16 uA0;
        s16 uA2;
        s16 uA4;
        s8 uA6;
        u8 padA7[0x1];
        f32 uA8;
        s8 uAC;
        s8 uAD;
        s8 uAE;
        s8 uAF;
    } sp;

    pos[0] = (*(f32 *)((u8 *)arg1 + 0x14));
    pos[1] = (*(f32 *)((u8 *)arg1 + 0x18)) + 50.0f;
    pos[2] = (*(f32 *)((u8 *)arg1 + 0x1C));
    if ((arg1 && arg1) && arg1) {
    } // fakematch: scheduling barrier (pos stores before header stores)
    header.unk0 = 3;
    if ((arg1 && arg1) && arg1) {
    } // fakematch
    header.unk1 = -1;
    header.unk2 = (random_int() % 9U) + 5;
    header.unk4 = 0;
    header2.unk0 = pos[0];
    header2.unk4 = pos[1];
    header2.unk8 = pos[2];
    light_create_with_ctrl(&header, &header2, (random_int() % 31U) + 0x5A, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0xFF, 1);
    sp.u3C = 8;
    sp.u40 = 0xC;
    *(V3i *) &sp.u44 = *(V3i *) pos;
    sp.u50 = 3.07f;
    sp.u54 = 6.2f;
    sp.u58 = -0.96900004f;
    sp.u5C = 0.71800005f;
    sp.u60 = 15.0f;
    sp.u64 = 30.0f;
    sp.u68 = 0;
    sp.u6A = 0xFF;
    sp.u6C = -0x40;
    sp.u6E = 0x50;
    sp.u70 = 3;
    sp.u74 = 1;
    sp.u78 = 0x14;
    sp.u7A = 0xF;
    sp.u7C = 1;
    sp.u7E = 4;
    sp.u7F = 2;
    sp.u80 = 3;
    sp.u81 = 0xFF;
    sp.u82 = 0xFF;
    sp.u83 = 0xFF;
    sp.u84 = 0xFF;
    sp.u85 = 0;
    sp.u86 = 0;
    sp.u87 = 0;
    sp.u88 = 0;
    sp.u89 = 0xFF;
    sp.u8A = 0xFF;
    sp.u8B = 0xFF;
    sp.u8C = 0xFF;
    sp.u8D = 0;
    sp.u8E = 0;
    sp.u8F = 0;
    sp.u90 = 0;
    sp.u91 = 0xFF;
    sp.u92 = 0;
    sp.u93 = 3;
    sp.u94 = 0x24;
    sp.u98 = 0x200005;
    sp.u9C = 0x60600;
    sp.uA0 = 8;
    sp.uA2 = 0x1F;
    sp.uA4 = 1;
    sp.uA6 = 0;
    sp.uA8 = 1.0f;
    sp.uAC = -1;
    sp.uAD = 0;
    sp.uAE = -1;
    sp.uAF = -1;
    func_151530A8(&sp.u3C, 0xFF, 1);
}

/* was func_150F8DCC */
void fire_post_tick_event(s32 arg0, s32 arg1) {
    s32 tmp[2];
    tmp[0] = arg1;
    func_151494E0(tmp, 0x3F);
}

/* was func_150F8DFC */
void fire_handle_event(struct102 *arg0, u8 *arg1, u8 arg2)
{
  u8 *w = (u8 *) arg0;
  u8 *v = w + 0x28;
  u8 i;
  if (arg2 == 0x42)
  {
    s32 blk_t; // fakematch: block-local declaration = basic-block boundary (s69)
    if (arg1[4] == v[4])
    {
      unsigned int blk_t; // fakematch: unsigned index temp (permuter)
      for (i = 0; i < 7; i++)
      {
        blk_t = i;
        (*((u8 **) ((v + 0xC) + (blk_t * 4))))[0x6E] = 1;
      }

      (*((u8 **) (v + 0x28)))[0x6E] = 0;
      v[8] = 7;
    }
  }
  else
    if ((arg2 ^ 0) == 0x3F) // fakematch: ^ 0 (permuter)
  {
    if ((*((s32 *) arg1)) == (*((s32 *) (w + 0x28))))
    {
      fire_burn_update(arg0);
    }
  }
}

#ifdef NON_MATCHING
u8 *func_1516547C(u8 kind, u8 view, u8 *data, u8 arg3, s32 arg4);
void func_15143874(s16 arg0, f32 arg1, f32 *arg2, f32 *arg3);
void func_15143794(s16 arg0, s16 arg1, f32 arg2, struct17 *arg3);
u8 *func_15132BBC(u8 *req, s32 nTrails, s32 arg2, s32 *bounds, s32 extraSize, u8 arg5, s32 owner);
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
s32 impact_tinted_particle_spawn(u8 arg0, u8 *arg1, u8 *arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s16 arg7, u8 arg8, s16 arg9, s16 argA, u8 argB, u8 argC, s32 argD);

/* fire_handle_event's object from +0x28 on (the fire state) */
typedef struct {
    s32 unk0;
    u8 unk4;
    u8 flags;       /* +0x05: bit 0 = mirrored (angles negated) */
    s16 timer;      /* +0x06: next stage change */
    u8 stage;       /* +0x08: 0..7 */
    u8 pad9[3];
    u8 *parts[8];   /* +0x0C: stage objects (s16 position at +0x10, visible flag at +0x6E) */
    f32 sparkAcc;   /* +0x2C */
    f32 smokeAcc;   /* +0x30 */
    f32 flameAcc;   /* +0x34 */
    f32 emberAcc;   /* +0x38 */
    s16 crackle;    /* +0x3C: next crackle sound */
    u8 pad3E[2];
    f32 x;          /* +0x40 */
    f32 z;          /* +0x44 */
    f32 radius;     /* +0x48 */
} FireState;

// fire_burn_update: P206: a fire that burns while any object of id 0x98 with model 0x1EB is still unlit
// (unk222 == 0; `count` of them scales the rates; none = nothing). Every D_800BE9E4 * count frames the next stage
// object takes over (the old one hidden through +0x6E, sound 0x2B3..0x2B5 at its position, event 7 and a
// func_151D8E18 burst; up to stage 7); a crackle every 150..300 frames (burst, sound 0x6D6..0x6D9). Four
// accumulators grow by (base + randf * spread) * D_800BE9A4 * count and spawn one batch per whole unit at a random
// point on the ring (angle (rng % 126 - 220) mirrored by flags bit 0, `radius`, around x / z, height 30..180):
// embers (func_151C384C), 5..11 flame particles (func_15132BBC), 7..19 smoke sprites (func_151307F0, random
// flips) and sparks (impact_tinted_particle_spawn).
/* was func_150F8EAC */
void fire_burn_update(u8 *arg0) {
    FireState *st = (FireState *)(arg0 + 0x28);
    structEU_151D8E18 burst;
    structEU_151D8E18 crackle;
    struct {
        f32 scale[2];   /* +0x00 */
        f32 size[2];    /* +0x08 */
        f32 rot[3];     /* +0x10 */
        f32 one[3];     /* +0x1C */
        f32 pos[3];     /* +0x28 */
        f32 vel[3];     /* +0x34 */
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        s32 u50;
        s16 life;       /* +0x54 */
        s16 texture;    /* +0x56 */
        u8 u58;
        s32 u5C;
        u8 u60;
        u8 u61;
        u8 u62[7];
        u8 pad69;
        u8 u6A;
        s32 u6C;
        u8 u70;
        s16 u72;
        s16 u74;
        s32 u78;
    } flame;
    struct {
        s32 handlers;   /* +0x00 */
        s32 u04;
        s16 texSet;     /* +0x08 */
        s16 life;       /* +0x0A */
        s32 u0C;
        s32 u10;
        u8 color[4];    /* +0x14 */
        u8 u18[3];
        u8 alpha;       /* +0x1B */
        u8 u1C;
        u8 texture;     /* +0x1D */
        s16 fadeStart;  /* +0x1E */
        s16 fadeRate;   /* +0x20 */
        s16 u22;
        f32 u24;
        f32 halfW;      /* +0x28 */
        f32 halfH;      /* +0x2C */
        f32 pos[3];     /* +0x30 */
        s32 angle[3];   /* +0x3C */
        f32 vel[3];     /* +0x48 */
        f32 value;      /* +0x54 */
        s32 flags;      /* +0x58 */
        s32 u5C;
        u8 draw;        /* +0x60 */
        u8 update;      /* +0x61 */
        u8 blend;       /* +0x62 */
        s8 u63;
        s8 u64;
        u8 u65;
        u8 u66;
        s16 u68;
        f32 range;      /* +0x6C */
    } smoke;
    f32 pos[3];
    f32 vel[3];
    f32 ember[3];
    f32 countf, size, speed, spread;
    s32 count, i, n, dir, base, r1, r2, flipA, flipB;
    s16 angle, k;
    u8 *part;

    count = 0;
    for (i = 0; i < 25; i++) {
        if (D_800CC2D0[i].id == 0x98 && *(u16 *)((u8 *)&D_800CC2D0[i] + 0x84) == 0x1EB &&
            *((u8 *)&D_800CC2D0[i] + 0x222) == 0) {
            count++;
        }
    }
    if (count == 0) {
        return;
    }

    /* next stage */
    if (st->stage < 7) {
        st->timer -= D_800BE9E4 * count;
        if (st->timer < 0) {
            part = st->parts[st->stage];
            func_10010F88((random_int() % 3U) + 0x2B3, 0x5DC0, 0, 0, -1, *(s16 *)(part + 0x10),
                          *(s16 *)(part + 0x12), *(s16 *)(part + 0x14), 500, 1000);
            st->parts[st->stage][0x6E] = 1;
            st->stage++;
            st->parts[st->stage][0x6E] = 0;
            func_1516547C(7, 0, NULL, arg0[0xC], arg0[1]);
            burst.unk0 = 1;
            burst.unk2 = 0x19;
            burst.unk5 = 1;
            burst.unk4 = 8;
            burst.unk6 = -1;
            func_151D8E18(&burst, 0, arg0[0xC], arg0[1]);
            st->timer = (random_int() % 31U) + 70;
        }
    }

    /* crackle */
    st->crackle -= D_800BE9E4 * count;
    if (st->crackle < 0) {
        crackle.unk0 = 1;
        crackle.unk2 = (random_int() % 21U) + 10;
        crackle.unk5 = 1;
        crackle.unk4 = (random_int() & 3) + 1;
        crackle.unk6 = -1;
        func_151D8E18(&crackle, 0, arg0[0xC], arg0[1]);
        part = st->parts[st->stage];
        func_10010F88((random_int() & 3) + 0x6D6, 0x5DC0, 0, 0, -1, *(s16 *)(part + 0x10),
                      *(s16 *)(part + 0x12), *(s16 *)(part + 0x14), 500, 1000);
        st->crackle = (random_int() % 151U) + 150;
    }

    /* embers */
    countf = count;
    st->emberAcc += (0.020000001f + random_float() * 0.025f) * (D_800BE9A4 * countf);
    if (1.0f < st->emberAcc) {
        dir = (st->flags & 1) ? -1 : 1;
        do {
            angle = ((s32)(random_int() % 126U) - 0xDC) * dir;
            func_15143874(angle, st->radius, &ember[0], &ember[2]);
            ember[1] = random_float() * 150.0f + 30.0f;
            ember[0] += st->x;
            ember[2] += st->z;
            func_151C384C(ember, arg0[0xC], arg0[1]);
            st->emberAcc -= 1.0f;
        } while (1.0f < st->emberAcc);
    }

    /* flames */
    st->flameAcc += (0.020000001f + random_float() * 0.060000002f) * (D_800BE9A4 * countf);
    if (1.0f < st->flameAcc) {
        dir = (st->flags & 1) ? -1 : 1;
        flame.scale[0] = 1.0f;
        flame.scale[1] = 1.0f;
        flame.one[0] = 1.0f;
        flame.one[1] = 1.0f;
        flame.one[2] = 1.0f;
        flame.u50 = 0x39E8;
        flame.texture = 0x86;
        flame.u58 = 0;
        flame.u5C = 0;
        flame.u60 = 0xFF;
        flame.u61 = 8;
        flame.u62[0] = 0;
        flame.u62[1] = 0;
        flame.u62[2] = 0;
        flame.u62[3] = 0;
        flame.u62[4] = 0;
        flame.u62[5] = 0;
        flame.u62[6] = 0;
        flame.u6A = 2;
        flame.u6C = 0;
        flame.u70 = 0;
        flame.u72 = 0xC;
        flame.u74 = 0x15;
        flame.u78 = 0;
        flame.u44 = 0.0f;
        do {
            k = (random_int() % 7U) + 5;
            angle = ((s32)(random_int() % 126U) - 0xDC) * dir;
            func_15143874(angle, st->radius, &flame.pos[0], &flame.pos[2]);
            flame.pos[1] = random_float() * 150.0f + 30.0f;
            flame.pos[0] += st->x;
            flame.pos[2] += st->z;
            base = angle - 7;
            while (k > 0) {
                flame.life = (random_int() & 0xF) + 0x23;
                size = random_float() * 0.012f + 0.005f;
                flame.size[0] = size;
                flame.size[1] = size;
                flame.rot[0] = random_float() * 360.0f;
                flame.rot[1] = random_float() * 360.0f;
                flame.rot[2] = random_float() * 360.0f;
                r1 = random_int();
                r2 = random_int();
                speed = random_float() * 8.0f + 10.0f;
                func_15143794((r1 & 0xF) + base, ((u32)r2 % 37U) - 0x3F, speed, (struct17 *)flame.vel);
                flame.u40 = random_float() * 32.41f + -16.205f;
                flame.u48 = random_float() * 32.41f + -16.205f;
                flame.u4C = random_float() * 0.337f + -1.177f;
                func_15132BBC((u8 *)&flame, 3, 1, NULL, 0, 0xFF, 1);
                k--;
            }
            st->flameAcc -= 1.0f;
        } while (1.0f < st->flameAcc);
    }

    /* smoke */
    st->smokeAcc += (0.055000003f + random_float() * 0.05f) * (D_800BE9A4 * countf);
    if (1.0f < st->smokeAcc) {
        dir = (st->flags & 1) ? -1 : 1;
        smoke.texture = 0x86;
        smoke.handlers = 0x200005;
        smoke.texSet = 0x4404;
        smoke.u04 = 0x9F0600;
        smoke.u0C = 0;
        smoke.u10 = 0;
        smoke.color[0] = 0xFF;
        smoke.color[1] = 0xFF;
        smoke.color[2] = 0xFF;
        smoke.color[3] = 0xFF;
        smoke.u18[0] = 0xFF;
        smoke.u18[1] = 0xFF;
        smoke.u18[2] = 0xFF;
        smoke.angle[0] = ((s32 *)D_800A5860)[0];
        smoke.angle[1] = ((s32 *)D_800A5860)[1];
        smoke.angle[2] = ((s32 *)D_800A5860)[2];
        smoke.fadeStart = 8;
        smoke.fadeRate = 0x1F;
        smoke.u22 = 1;
        smoke.flags = 0x1C207;
        smoke.draw = 6;
        smoke.update = 5;
        smoke.blend = 0xFF;
        smoke.u63 = -1;
        smoke.u64 = -1;
        smoke.u65 = 0;
        smoke.u5C = 0;
        smoke.u66 = 0xFF;
        smoke.u68 = 0;
        smoke.range = 0.0f;
        smoke.u24 = 1.0f;
        do {
            n = (random_int() % 13U) + 7;
            angle = ((s32)(random_int() % 126U) - 0xDC) * dir;
            func_15143874(angle, st->radius, &smoke.pos[0], &smoke.pos[2]);
            smoke.pos[1] = random_float() * 150.0f + 30.0f;
            smoke.pos[0] += st->x;
            smoke.pos[2] += st->z;
            base = angle - 4;
            while (n > 0) {
                smoke.life = (random_int() % 21U) + 0x1E;
                smoke.alpha = (random_int() % 156U) + 100;
                size = random_float() * 110.0f + 70.0f;
                smoke.flags &= ~0xC0;
                smoke.halfW = size;
                smoke.halfH = size;
                flipB = (random_int() & 1) ? 0x80 : 0;
                flipA = (random_int() & 1) ? 0x40 : 0;
                smoke.flags |= flipA | flipB;
                r1 = random_int();
                r2 = random_int();
                speed = random_float() * 10.0f + 6.0f;
                func_15143794(((u32)r1 % 9U) + base, (r2 & 7) - 0x10, speed, (struct17 *)smoke.vel);
                smoke.value = random_float() * 0.268f + -0.38700002f;
                func_151307F0((s32)&smoke, 1, 0, 0, 0xFF, 1);
                n--;
            }
            st->smokeAcc -= 1.0f;
        } while (1.0f < st->smokeAcc);
    }

    /* sparks */
    st->sparkAcc += (0.33600003f + random_float() * 0.126f) * (D_800BE9A4 * countf);
    if (1.0f < st->sparkAcc) {
        dir = (st->flags & 1) ? -1 : 1;
        do {
            angle = ((s32)(random_int() % 126U) - 0xDC) * dir;
            func_15143874(angle, st->radius, &pos[0], &pos[2]);
            pos[1] = random_float() * 150.0f + 30.0f;
            pos[0] += st->x;
            pos[2] += st->z;
            r1 = random_int();
            r2 = random_int();
            speed = random_float() * 6.0f + 4.0f;
            func_15143794(((u32)r1 % 9U) + angle - 4, (r2 & 7) - 0x10, speed, (struct17 *)vel);
            size = random_float();
            spread = random_float();
            r1 = random_int();
            r2 = random_int();
            impact_tinted_particle_spawn(8, (u8 *)pos, (u8 *)vel, size * 200.0f + 200.0f, 1.025439f, 0.938816f,
                          spread * 0.20700002f + -0.16900001f, ((u32)r1 % 21U) + 0x23, ((u32)r2 % 121U) + 100, 0x32,
                          5, 0, 0xFF, 1);
            st->sparkAcc -= 1.0f;
        } while (1.0f < st->sparkAcc);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_126330/fire_burn_update.s")
#endif

extern u8 D_800A2010[][2];

/* was func_150F9CA0 */
void fire_post_finish_events(u8 arg0) {
    struct {
        s32 unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = 0;
    tmp.unk4 = D_800A2010[arg0][0];
    func_151494E0(&tmp, 0x42);
    tmp.unk4 = D_800A2010[arg0][1];
    func_151494E0(&tmp, 0x42);
}

/* was func_150F9D08 */
void fire_free(s32 arg0) {
}

/* was func_150F9D14 */
void fire_retire(struct260 *arg0) {
    fire_free(arg0);
    func_1514933C(arg0);
}

/* was func_150F9D40 */
void fire_delete(struct260 *arg0) {
    fire_free(arg0);
    func_15149368(arg0);
}

s32 attached_particle_spawn(u8 *, u8, f32 *, f32 *, f32 *, s32, s32, f32, s32 *, s32, s32, s32, s32, s32);
s32 func_15145EA4(f32 **, s32 **, s32, s32);
extern u8 D_80088EF0;
extern f32 D_800A2018[];
extern f32 D_800A2024[];

/* was func_150F9D6C */
void obj_bone_spark_spray(u8 *arg0, u8 arg1, s32 arg2)
{
  s32 sp64[3];
  f32 sp58[3];
  f32 *sp54;
  s32 *sp50;
  s32 m;
  if (*(s32 *)(arg0 + 0x1D4) == 0)
  {
    return;
  }
  sp54 = D_800A2018;
  sp50 = sp64;
  m = *(s32 *)(arg0 + 0x1D4) + (D_80088EF0 << 6);
  func_15145EA4((0, &sp54), &sp50, (0, m), 1); // fakematch: permuter comma operands fix the 0x48/0x4C spill slot
  sp58[1] = (random_float() * 1) + 2.0f; // fakematch: int * 1 keeps the result scheduling
  sp58[0] = (random_float() * 14.0f) + 28.0f;
  attached_particle_spawn(arg0, D_80088EF0, D_800A2018, D_800A2024, sp58, (random_int() % 3U) + 4, (random_int() % 156U) + 0x64, (random_float() * 300.0f) + 400.0f, sp64, 0xFF, 0, -1, arg1, arg2);
}

u8 *obj_muzzle_node_get(u8 *);
s32 beam_impact_sparks(s32 *, s32 *, u8, s32);
s32 model_points_find(f32 *, f32 *, f32 *, f32 *, f32 *, u8 *, s32); /* P210: port P209's prototype (game_eu_12CAC0) */
s32 func_151D44C4(s32 *, u8, s32);
s32 func_151D49B8(s32 *, s32 *, s32, u8 *, f32, s32, s32);

/* was func_150F9ED0 */
void obj_muzzle_blast(u8 *arg0, u8 arg1, s32 arg2) {
    s32 pad[15]; // fakematch: frame is 0xA8, pad first keeps the vectors at 0x30-0x60
    s32 sp60[3];
    s32 sp54[3];
    s32 sp48[3];
    s32 sp3C[3];
    s32 sp30[3];
    u8 *temp_v0;
    u8 *sp2C;

    temp_v0 = obj_muzzle_node_get(arg0);
    if (temp_v0 != NULL) {
        sp2C = temp_v0;
        if (model_points_find((f32 *)sp60, (f32 *)sp54, (f32 *)sp48, (f32 *)sp3C, (f32 *)sp30, arg0, (s32)temp_v0) != 0) {
            func_151D44C4(sp54, arg1, arg2);
            func_151D49B8(sp48, sp3C, (*(u8 *)(sp2C + 2) << 6) + *(s32 *)(arg0 + 0x1D4), arg0, 1.0f, arg1, arg2);
            beam_impact_sparks(sp54, sp60, arg1, arg2);
        }
    }
}
