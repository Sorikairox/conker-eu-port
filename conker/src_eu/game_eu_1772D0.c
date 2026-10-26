#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void effect3d_set_handlers(u8 *, u8, u8, u8, u8);
s32 spark_spawn_from_desc(f32 *, s32, s32, s32, s32, s32);
#endif


#ifdef NON_MATCHING
/* P128 */
void collision_select_area(s32);
s32 zone_tree_find_leaf(s32, s32);
s32 random_int(void);

/* P128: the two stack blocks of spark_spawn_from_desc. Spark15149AC0Wave is copied into the new record at +0x110 (0x50 bytes,
 * three wave channels read by spark_wave_update); Spark15149AC0Params is the spawn parameter block that effect3d_spawn_full
 * copies into the record at +0x18 (0x58 bytes: the last 0xC bytes are never written, as in the asm). */
typedef struct {
    f32 a0;    /* +00 rec[0xC] */
    f32 a1;    /* +04 rec[0x14] */
    f32 aMid;  /* +08 */
    s16 aT;    /* +0C */
    s16 aTMax; /* +0E */
    f32 aRate; /* +10 */
    f32 b0;    /* +14 rec[0x10] */
    f32 b1;    /* +18 rec[0x18] */
    f32 b2;    /* +1C rec[0x1C] */
    f32 bMid;  /* +20 */
    s16 bT;    /* +24 */
    s16 bTMax; /* +26 */
    f32 bRate; /* +28 */
    s32 c0;    /* +2C rec s16 0x20 */
    s32 c1;    /* +30 rec s16 0x22 */
    s32 c2;    /* +34 */
    s16 cT;    /* +38 */
    s16 cTMax; /* +3A */
    f32 cRate; /* +3C */
    f32 d0;    /* +40 rec[0x40] */
    f32 d1;    /* +44 rec[0x44] */
    u8 d2;     /* +48 rec[0x34] */
    u8 pad49[3];
    f32 d3;    /* +4C rec[0x3C] */
} Spark15149AC0Wave; /* size 0x50 */

typedef struct {
    u8 kind;       /* +00 0x13 / 0x14 / 0x71 */
    u8 pad01;
    s16 mode;      /* +02 0x301 */
    s16 u04;       /* +04 rec s16 0x24 */
    s16 pad06;
    s32 u08;       /* +08 0 */
    s32 u0C;       /* +0C (rec s16 0x20 + s16 0x22) >> 1 */
    u8 col[4];     /* +10 rec[0x26..0x29] */
    f32 u14;       /* +14 */
    f32 u18;       /* +18 */
    f32 pos[3];    /* +1C rec[0..2] */
    f32 u28;       /* +28 */
    f32 u2C;       /* +2C */
    f32 u30;       /* +30 */
    f32 u34;       /* +34 rec[0x38] */
    f32 u38;       /* +38 */
    f32 scale;     /* +3C 1.0 */
    s32 flags;     /* +40 rec u16 0x2A | 0x40000000, bit 0x01000000 = on ground */
    u8 u44;        /* +44 rec[0x2C] */
    u8 u45;        /* +45 rec[0x2D] */
    u8 pad46[2];
    s32 ground;    /* +48 zone_tree_find_leaf result or 0 */
    u8 tail[0xC];  /* +4C never written (effect3d_spawn_full copies 0x58 bytes) */
} Spark15149AC0Params; /* size 0x58 */

// spark_spawn_from_desc: spawns a menu spark/sprite record from the 0x48-byte descriptor desc (position +0, three wave
// channels +0xC..+0x44, colour +0x26, flags +0x2A, sizes +0x2C/+0x2D/+0x2E/+0x2F, extra +0x30): builds the spawn
// parameter block (kind 0x13/0x71 by kind_sel, random 0x13/0x14 otherwise; ground lookup when area != 0), creates
// the record through effect3d_spawn_default (texture desc[0x2E], 0xE, desc[0x2F], layer, random | 2, desc[0x30] + 0x50, u4,
// owner) and copies the wave block to record + 0x110. Returns the record (0 when none was free).
/* was func_15149AC0 */
s32 spark_spawn_from_desc(f32 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u8 *desc = (u8 *) arg0;
    Spark15149AC0Wave w;
    Spark15149AC0Params p;
    u8 area = arg2;
    u8 kind_sel = arg3;
    s32 layer = arg1 & 0xFF; /* the u8 arguments are narrowed here (callers pass s32) */
    s32 u4 = arg4 & 0xFF;
    struct210 *rec;

    p.flags = *(u16 *) (desc + 0x2A) | 0x40000000;
    p.pos[0] = ((f32 *) desc)[0];
    p.pos[1] = ((f32 *) desc)[1];
    p.pos[2] = ((f32 *) desc)[2];
    if (area != 0) {
        p.flags |= 0x01000000;
        collision_select_area(0);
        p.ground = zone_tree_find_leaf((s32) p.pos[0], (s32) p.pos[2]);
    } else {
        p.flags &= ~0x01000000;
        p.ground = 0;
    }
    if (kind_sel == 1) {
        p.kind = 0x13;
    } else if (kind_sel == 2) {
        p.kind = 0x71;
    } else if (random_int() & 1) {
        p.kind = 0x13;
    } else {
        p.kind = 0x14;
    }
    p.mode = 0x301;
    p.u04 = *(s16 *) (desc + 0x24);
    p.col[0] = desc[0x26];
    p.col[1] = desc[0x27];
    p.col[2] = desc[0x28];
    p.col[3] = desc[0x29];
    p.u44 = desc[0x2C];
    p.u28 = 0.0f;
    p.u2C = 0.0f;
    p.u30 = 0.0f;
    p.u45 = desc[0x2D];
    p.u38 = 0.0f;
    p.scale = 1.0f;
    p.u34 = *(f32 *) (desc + 0x38);

    w.a0 = *(f32 *) (desc + 0xC);
    w.a1 = *(f32 *) (desc + 0x14);
    w.aT = 0;
    w.aTMax = 6;
    w.aRate = 0.186f;
    w.aMid = (w.a0 + w.a1) * 0.5f;
    w.b0 = *(f32 *) (desc + 0x10);
    w.b1 = *(f32 *) (desc + 0x18);
    w.b2 = *(f32 *) (desc + 0x1C);
    w.bT = 0;
    w.bTMax = 0x11;
    w.bRate = 0.359f;
    w.bMid = (w.b0 + w.b1) * 0.5f;
    w.c0 = *(s16 *) (desc + 0x20);
    w.c1 = *(s16 *) (desc + 0x22);
    w.c2 = 0;
    w.cT = 0;
    w.cTMax = 0xF;
    w.cRate = 0.231f;
    w.d0 = *(f32 *) (desc + 0x40);
    w.d1 = *(f32 *) (desc + 0x44);
    w.d2 = desc[0x34];
    w.d3 = *(f32 *) (desc + 0x3C);
    p.u08 = 0;
    p.u0C = (w.c0 + w.c1) >> 1;
    p.u14 = 0.0f;
    p.u18 = 0.0f;

    rec = effect3d_spawn_default((s32) &p, desc[0x2E], 0xE, desc[0x2F], layer, (random_int() & 1) | 2,
                        *(s32 *) (desc + 0x30) + 0x50, u4, arg5);
    if (rec != NULL) {
        memcpy((u8 *) rec + 0x110, &w, sizeof(w));
    }
    return (s32) rec;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/spark_spawn_from_desc.s")
#endif

#ifdef NON_MATCHING
/* was func_15149DA8 */
s32 spark_wave_update(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    s32 temp_v0;
    s32 temp_v1;
    u8 *temp_s0;
    u8 *temp_s0_2;

    (*(s16 *)((u8 *)arg0 + 0x11C)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x11C)) - D_800BE9E4);
    if ((*(s16 *)((u8 *)arg0 + 0x11C)) < 0) {
        temp_s0 = arg0 + 0x110;
        (*(s16 *)((u8 *)temp_s0 + 0xC)) = (s16) (random_int() % (u32) (*(s16 *)((u8 *)temp_s0 + 0xE)));
        temp_f2 = (*(f32 *)((u8 *)temp_s0 + 4));
        (*(f32 *)((u8 *)temp_s0 + 8)) = (f32) ((random_float() * ((*(f32 *)((u8 *)temp_s0 + 0)) - temp_f2)) + temp_f2);
    }
    temp_s0_2 = arg0 + 0x110;
    temp_f0 = (*(f32 *)((u8 *)arg0 + 0x2C));
    (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) (temp_f0 + (((*(f32 *)((u8 *)temp_s0_2 + 8)) - temp_f0) * (*(f32 *)((u8 *)temp_s0_2 + 0x10))));
    (*(s16 *)((u8 *)temp_s0_2 + 0x24)) = (s16) ((*(s16 *)((u8 *)temp_s0_2 + 0x24)) - D_800BE9E4);
    if ((*(s16 *)((u8 *)temp_s0_2 + 0x24)) < 0) {
        (*(s16 *)((u8 *)temp_s0_2 + 0x24)) = (s16) (random_int() % (u32) (*(s16 *)((u8 *)temp_s0_2 + 0x26)));
        if (random_int() & 3) {
            temp_f2_2 = (*(f32 *)((u8 *)temp_s0_2 + 0x18));
            (*(f32 *)((u8 *)temp_s0_2 + 0x20)) = (f32) ((random_float() * ((*(f32 *)((u8 *)temp_s0_2 + 0x14)) - temp_f2_2)) + temp_f2_2);
        } else {
            temp_f2_3 = (*(f32 *)((u8 *)temp_s0_2 + 0x14));
            (*(f32 *)((u8 *)temp_s0_2 + 0x20)) = (f32) ((random_float() * ((*(f32 *)((u8 *)temp_s0_2 + 0x1C)) - temp_f2_3)) + temp_f2_3);
        }
    }
    temp_f0_2 = (*(f32 *)((u8 *)arg0 + 0x30));
    (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) (temp_f0_2 + (((*(f32 *)((u8 *)temp_s0_2 + 0x20)) - temp_f0_2) * (*(f32 *)((u8 *)temp_s0_2 + 0x28))));
    (*(s16 *)((u8 *)temp_s0_2 + 0x38)) = (s16) ((*(s16 *)((u8 *)temp_s0_2 + 0x38)) - D_800BE9E4);
    if ((*(s16 *)((u8 *)temp_s0_2 + 0x38)) < 0) {
        (*(s16 *)((u8 *)temp_s0_2 + 0x38)) = (s16) (random_int() % (u32) (*(s16 *)((u8 *)temp_s0_2 + 0x3A)));
        temp_v1 = (*(s32 *)((u8 *)temp_s0_2 + 0x30));
        (*(s32 *)((u8 *)temp_s0_2 + 0x34)) = (s32) ((random_int() % (u32) (((*(s32 *)((u8 *)temp_s0_2 + 0x2C)) - temp_v1) + 1)) + temp_v1);
    }
    temp_v0 = (*(s32 *)((u8 *)arg0 + 0x24));
    (*(s32 *)((u8 *)arg0 + 0x24)) = (s32) (temp_v0 + (s32) (((f32) (*(s32 *)((u8 *)temp_s0_2 + 0x34)) - (f32) temp_v0) * (*(f32 *)((u8 *)temp_s0_2 + 0x3C))));
    if ((*(s16 *)((u8 *)arg0 + 0x1C)) < 5) {
        effect3d_set_handlers(arg0, (*(u8 *)((u8 *)arg0 + 0x70)), (*(u8 *)((u8 *)temp_s0_2 + 0x48)), (*(u8 *)((u8 *)arg0 + 0x72)), (u8) (s32) (*(u8 *)((u8 *)arg0 + 0x73)));
        (*(s16 *)((u8 *)arg0 + 0x1C)) = 0x12C;
        (*(s32 *)((u8 *)arg0 + 0x58)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x58)) & ~1);
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/spark_wave_update.s")
#endif
#ifdef NON_MATCHING
/* was func_1514A004 */
s32 spark_grow_in(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f0_2;
    s32 var_v1;
    u8 temp_t8;
    u8 var_v0;
    u8 *temp_v0;
    u8 *temp_v0_2;

    var_v0 = (*(u8 *)((u8 *)arg0 + 0x74));
    var_v1 = 1;
    if (!(var_v0 & 2)) {
        temp_v0 = arg0 + 0x110;
        temp_f0 = (*(f32 *)((u8 *)arg0 + 0x2C));
        (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) (temp_f0 + (((*(f32 *)((u8 *)temp_v0 + 8)) - temp_f0) * (*(f32 *)((u8 *)temp_v0 + 0x44))));
        if (((*(f32 *)((u8 *)temp_v0 + 8)) * 0.95f) < (*(f32 *)((u8 *)arg0 + 0x2C))) {
            temp_t8 = (*(u8 *)((u8 *)arg0 + 0x74)) | 2;
            (*(u8 *)((u8 *)arg0 + 0x74)) = temp_t8;
            var_v0 = temp_t8 & 0xFF;
        } else {
            var_v1 = 0;
            var_v0 = (*(u8 *)((u8 *)arg0 + 0x74));
        }
    }
    temp_v0_2 = arg0 + 0x110;
    if (!(var_v0 & 8)) {
        temp_f0_2 = (*(f32 *)((u8 *)arg0 + 0x30));
        (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) (temp_f0_2 + (((*(f32 *)((u8 *)temp_v0_2 + 0x20)) - temp_f0_2) * (*(f32 *)((u8 *)temp_v0_2 + 0x44))));
        if (((*(f32 *)((u8 *)temp_v0_2 + 0x20)) * 0.95f) < (*(f32 *)((u8 *)arg0 + 0x30))) {
            (*(u8 *)((u8 *)arg0 + 0x74)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x74)) | 8);
        } else {
            var_v1 = 0;
        }
    }
    if (var_v1 != 0) {
        effect3d_set_handlers(arg0, (*(u8 *)((u8 *)arg0 + 0x70)), 0xDU, (*(u8 *)((u8 *)arg0 + 0x72)), (u8) (s32) (*(u8 *)((u8 *)arg0 + 0x73)));
    }
    if ((*(s16 *)((u8 *)arg0 + 0x1C)) < 5) {
        effect3d_set_handlers(arg0, (*(u8 *)((u8 *)arg0 + 0x70)), (*(u8 *)((u8 *)arg0 + 0x158)), (*(u8 *)((u8 *)arg0 + 0x72)), (u8) (s32) (*(u8 *)((u8 *)arg0 + 0x73)));
        (*(s16 *)((u8 *)arg0 + 0x1C)) = 0x64;
        (*(s32 *)((u8 *)arg0 + 0x58)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x58)) & ~1);
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/spark_grow_in.s")
#endif
/* was func_1514A164 */
s32 spark_shrink(u8 *arg0) {
    *(f32 *)(arg0 + 0x2C) -= *(f32 *)(arg0 + 0x2C) * *(f32 *)(arg0 + 0x150);
    *(f32 *)(arg0 + 0x30) -= *(f32 *)(arg0 + 0x30) * *(f32 *)(arg0 + 0x150);
    if (*(f32 *)(arg0 + 0x2C) < 2.0f || *(f32 *)(arg0 + 0x30) < 2.0f) {
        return 0;
    }
    return 1;
}

/* was func_1514A1C8 */
s32 spark_shrink_rise(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;

    temp_f0 = (*(f32 *)((u8 *)arg0 + 0x2C));
    temp_f2 = (*(f32 *)((u8 *)arg0 + 0x150));
    temp_f12 = (*(f32 *)((u8 *)arg0 + 0x30));
    (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) (temp_f0 - (temp_f0 * temp_f2));
    (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) (temp_f12 - (temp_f12 * temp_f2));
    (*(f32 *)((u8 *)arg0 + 0x50)) += ((*(f32 *)((u8 *)arg0 + 0x4C)) * D_800BE9A4);
    (*(f32 *)((u8 *)arg0 + 0x38)) += ((*(f32 *)((u8 *)arg0 + 0x50)) * D_800BE9A4);
    if ((*(f32 *)((u8 *)arg0 + 0x15C)) < (*(f32 *)((u8 *)arg0 + 0x38))) {
        return 0;
    }
    if (((*(f32 *)((u8 *)arg0 + 0x2C)) < 4.0f) || ((*(f32 *)((u8 *)arg0 + 0x30)) < 4.0f)) {
        return 0;
    }
    return 1;
}

s32 vtx_slot_buffer_get(s32, s16, s32, u8 **, u8 *);
extern f32 D_800DD608[];
extern f32 D_800DD618[];

/* was func_1514A288 */
u8 *spark_build_quad_vtx_a(u8 *arg0, s16 arg1) {
    u8 *sp44;
    u8 *sp40;
    f32 temp_f12;
    f32 temp_f2;
    u8 sp37;

    vtx_slot_buffer_get((s32)(arg0 + 0x100), arg1, 0x40, &sp44, &sp37);
    sp40 = sp44;
    if (sp44 != NULL) {
        if (sp37 != 0) {
            memcpy(((u8 **)(arg0 + 0x100))[arg1], arg0 + 0xC0, 0x40);
            memcpy(((u8 **)(arg0 + 0x100))[arg1] + 0x40, arg0 + 0xC0, 0x40);
        }
    } else {
        return NULL;
    }
    temp_f2 = *(f32 *)(arg0 + 0x2C) * D_800DD608[arg1];
    temp_f12 = *(f32 *)(arg0 + 0x2C) * D_800DD618[arg1];
    *(s16 *)(sp44 + 0) = *(s16 *)(sp44 + 0x30) = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f12);
    *(s16 *)(sp44 + 2) = *(s16 *)(sp44 + 0x12) = (s32) (*(f32 *)((u8 *)arg0 + 0x38));
    *(s16 *)(sp44 + 4) = *(s16 *)(sp44 + 0x34) = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - temp_f2);
    *(s16 *)(sp44 + 0x10) = *(s16 *)(sp44 + 0x20) = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - temp_f12);
    *(s16 *)(sp44 + 0x22) = *(s16 *)(sp44 + 0x32) = (s32) ((*(f32 *)((u8 *)arg0 + 0x30)) + (*(f32 *)((u8 *)arg0 + 0x38)));
    *(s16 *)(sp44 + 0x14) = *(s16 *)(sp44 + 0x24) = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + temp_f2);
    return sp40;
}

typedef struct { f32 x, y, z; } V3A434;
typedef struct {
    V3A434 pos;
    u8 unkC[0xA];
    s16 h16;
    s16 h18;
    s16 h1A;
    s16 h1C;
    s16 h1E;
    s16 h20;
    s16 h22;
    s16 h24;
    s16 h26;
    u8 c0[3];
    u8 c1[3];
    u8 b2E;
    u8 b2F;
    u8 b30;
    u8 b31;
} SpawnA434;
void fx_pick_random_color(u8, u8 *, u8 *, u8 *);
void puff_sprite_spawn(SpawnA434 *, s32);
/* was func_1514A434 */
s32 spark_die_spawn_burst(u8 *arg0) {
    SpawnA434 s;

    s.pos = *(V3A434 *)(arg0 + 0x34);
    s.h16 = 0;
    s.h18 = 0;
    s.h1A = s.h1C = random_int() % 6U + 8;
    s.h1E = 0;
    s.h20 = 0;
    s.h22 = random_int() % 201U + 100;
    s.h24 = random_int() % 5U + 3;
    s.h26 = 600;
    fx_pick_random_color(3, &s.c0[0], &s.c0[1], &s.c0[2]);
    fx_pick_random_color(4, &s.c1[0], &s.c1[1], &s.c1[2]);
    s.b2E = 0xFF;
    s.b2F = random_int() % 65U + 0x5C;
    s.b30 = random_int() % 3U + 1;
    s.b31 = 0;
    puff_sprite_spawn(&s, 1);
    return 0;
}

s32 vtx_slot_buffer_get(s32, s16, s32, u8 **, u8 *);
extern f32 D_800DD608[];
extern f32 D_800DD618[];

/* was func_1514A540 */
u8 *spark_build_quad_vtx_b(u8 *arg0, s16 arg1) {
    u8 *sp44;
    u8 *sp40;
    f32 temp_f12;
    f32 temp_f2;
    u8 sp37;

    vtx_slot_buffer_get((s32)(arg0 + 0x100), arg1, 0x40, &sp44, &sp37);
    sp40 = sp44;
    if (sp44 != NULL) {
        if (sp37 != 0) {
            memcpy(((u8 **)(arg0 + 0x100))[arg1], arg0 + 0xC0, 0x40);
            memcpy(((u8 **)(arg0 + 0x100))[arg1] + 0x40, arg0 + 0xC0, 0x40);
        }
    } else {
        return NULL;
    }
    temp_f2 = *(f32 *)(arg0 + 0x2C) * D_800DD608[arg1];
    temp_f12 = *(f32 *)(arg0 + 0x2C) * D_800DD618[arg1];
    *(s16 *)(sp44 + 6) = 0;
    *(s16 *)(sp44 + 0x16) = 0;
    *(s16 *)(sp44 + 0x26) = 0;
    *(s16 *)(sp44 + 0x36) = 0;
    *(s16 *)(sp44 + 0) = *(s16 *)(sp44 + 0x30) = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f12);
    *(s16 *)(sp44 + 2) = *(s16 *)(sp44 + 0x12) = (s32) (*(f32 *)((u8 *)arg0 + 0x38));
    *(s16 *)(sp44 + 4) = *(s16 *)(sp44 + 0x34) = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - temp_f2);
    *(s16 *)(sp44 + 0x10) = *(s16 *)(sp44 + 0x20) = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - temp_f12);
    *(s16 *)(sp44 + 0x22) = *(s16 *)(sp44 + 0x32) = (s32) ((*(f32 *)((u8 *)arg0 + 0x30)) + (*(f32 *)((u8 *)arg0 + 0x38)));
    *(s16 *)(sp44 + 0x14) = *(s16 *)(sp44 + 0x24) = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + temp_f2);
    return sp40;
}

/* was func_1514A70C */
s32 spark_flicker_update(u8 *arg0) {
    u8 *p;

    p = arg0 + 0x110;
    *(s16 *)(arg0 + 0x12E) -= D_800BE9E4;
    if (*(s16 *)(arg0 + 0x12E) < 0) {
        *(s16 *)(p + 0x1E) = random_int() % 6U;
        if (random_int() & 3) {
            *(f32 *)(p + 0x18) = *(f32 *)(p + 0x10) + ((*(f32 *)(p + 0xC) - *(f32 *)(p + 0x10)) * random_float());
        } else {
            *(f32 *)(p + 0x18) = *(f32 *)(p + 0xC) + ((*(f32 *)(p + 0x14) - *(f32 *)(p + 0xC)) * random_float());
        }
    }
    *(f32 *)(arg0 + 0x30) += (*(f32 *)(p + 0x18) - *(f32 *)(arg0 + 0x30)) * 0.359f;
    *(s16 *)(p + 0x1C) -= D_800BE9E4;
    if (*(s16 *)(p + 0x1C) < 0) {
        *(s16 *)(p + 0x1C) = random_int() % 17U;
        *(f32 *)(p + 8) = *(f32 *)(p + 4) + ((*(f32 *)(p + 0) - *(f32 *)(p + 4)) * random_float());
    }
    *(f32 *)(arg0 + 0x2C) += (*(f32 *)(p + 8) - *(f32 *)(arg0 + 0x2C)) * 0.186f;
    *(s16 *)(p + 0x44) -= D_800BE9E4;
    if (*(s16 *)(p + 0x44) < 0) {
        *(s16 *)(p + 0x44) = random_int() % 15U;
        *(f32 *)(p + 0x40) = *(f32 *)(p + 0x3C) + ((*(f32 *)(p + 0x38) - *(f32 *)(p + 0x3C)) * random_float());
    }
    *(s32 *)(arg0 + 0x24) += (s32)((*(f32 *)(p + 0x40) - (f32)*(s32 *)(arg0 + 0x24)) * 0.231f);
    return 1;
}

void effect3d_set_handlers(u8 *, u8, u8, u8, u8);
/* was func_1514A8F0 */
s32 spark_grow_in_fast(u8 *arg0) {
    u8 *p;
    s32 done;

    p = arg0 + 0x110;
    done = 1;
    if (!(arg0[0x74] & 2)) {
        *(f32 *)(arg0 + 0x2C) += (*(f32 *)(p + 8) - *(f32 *)(arg0 + 0x2C)) * 0.7f;
        if (*(f32 *)(p + 8) * 0.95f < *(f32 *)(arg0 + 0x2C)) {
            arg0[0x74] |= 2;
        } else {
            done = 0;
        }
    }
    if (!(arg0[0x74] & 8)) {
        *(f32 *)(arg0 + 0x30) += (*(f32 *)(p + 0x18) - *(f32 *)(arg0 + 0x30)) * 0.7f;
        if (*(f32 *)(p + 0x18) * 0.95f < *(f32 *)(arg0 + 0x30)) {
            arg0[0x74] |= 8;
        } else {
            done = 0;
        }
    }
    if (done) {
        effect3d_set_handlers(arg0, arg0[0x70], 4, arg0[0x72], arg0[0x73]);
    }
    return 1;
}

typedef struct {
    u8 pad0[0x1C];
    s16 unk1C;
    u8 pad1E[0xE];
    f32 unk2C;
    f32 unk30;
    u8 pad34[0x28];
    u8 unk5C;
    u8 pad5D[0xE7];
    f32 unk144;
    u8 pad148[0xE];
    s16 unk156;
    s16 unk158;
} struct_1514AA08;

/* was func_1514AA08 */
s32 spark_shrink_fade(struct_1514AA08 *arg0) {
    arg0->unk30 -= arg0->unk30 * arg0->unk144;
    arg0->unk2C -= arg0->unk2C * arg0->unk144;
    if (arg0->unk1C < arg0->unk156) {
        arg0->unk5C = arg0->unk1C * arg0->unk158;
    }
    return 1;
}

#ifdef NON_MATCHING
/* was func_1514AA5C */
s32 streak_move(u8 *arg0) {
    f32 temp_f0;

    temp_f0 = (*(f32 *)((u8 *)arg0 + 0x140));
    (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) (*(f32 *)((u8 *)arg0 + 0x34));
    (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) (*(f32 *)((u8 *)arg0 + 0x38));
    (*(f32 *)((u8 *)arg0 + 0x48)) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C));
    (*(f32 *)((u8 *)arg0 + 0x130)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x130)) * temp_f0);
    (*(f32 *)((u8 *)arg0 + 0x138)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x138)) * temp_f0);
    (*(f32 *)((u8 *)arg0 + 0x134)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x134)) + ((*(f32 *)((u8 *)arg0 + 0x13C)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x34)) + ((*(f32 *)((u8 *)arg0 + 0x130)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + ((*(f32 *)((u8 *)arg0 + 0x134)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + ((*(f32 *)((u8 *)arg0 + 0x138)) * D_800BE9A4));
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/streak_move.s")
#endif
#ifdef NON_MATCHING
/* was func_1514AB04 */
s32 streak_move_lag_tail(u8 *arg0) {
    f32 sp4;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f6;

    temp_f0 = (*(f32 *)((u8 *)arg0 + 0x140));
    (*(f32 *)((u8 *)arg0 + 0x130)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x130)) * temp_f0);
    (*(f32 *)((u8 *)arg0 + 0x134)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x134)) + ((*(f32 *)((u8 *)arg0 + 0x13C)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x138)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x138)) * temp_f0);
    temp_f12 = (*(f32 *)((u8 *)arg0 + 0x130)) * D_800BE9A4;
    temp_f14 = (*(f32 *)((u8 *)arg0 + 0x134)) * D_800BE9A4;
    temp_f16 = (*(f32 *)((u8 *)arg0 + 0x138)) * D_800BE9A4;
    (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f12);
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + temp_f14);
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + temp_f16);
    (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x40)) + temp_f12);
    temp_f6 = (*(f32 *)((u8 *)arg0 + 0x54));
    temp_f18 = (*(f32 *)((u8 *)arg0 + 0x34));
    (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x44)) + temp_f14);
    (*(f32 *)((u8 *)arg0 + 0x48)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x48)) + temp_f16);
    sp4 = temp_f6;
    temp_f0_2 = (*(f32 *)((u8 *)arg0 + 0x38));
    temp_f2 = (*(f32 *)((u8 *)arg0 + 0x3C));
    (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) (temp_f18 + (((*(f32 *)((u8 *)arg0 + 0x40)) - temp_f18) * sp4));
    (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) (temp_f0_2 + (((*(f32 *)((u8 *)arg0 + 0x44)) - temp_f0_2) * temp_f6));
    (*(f32 *)((u8 *)arg0 + 0x48)) = (f32) (temp_f2 + (((*(f32 *)((u8 *)arg0 + 0x48)) - temp_f2) * sp4));
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/streak_move_lag_tail.s")
#endif
#ifdef NON_MATCHING
/* was func_1514AC10 */
u8 *streak_build_vtx(u8 *arg0, s16 arg1) {
    struct {
        u8 u7F;
        u8 pad80[0x8];
        f32 u88;
        u8 pad8C[0x24];
        f32 uB0;
        f32 uB4;
        f32 uB8;
        u8 padBC[0x4];
        u8 * uC0;
        u8 * uC4;
    } sp;
    f32 sp74;
    u8 *sp6C;
    s32 sp68;                                       /* compiler-managed */
    f32 sp64;
    f32 *temp_v0_2;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f16_3;
    f32 temp_f18;
    f32 temp_f18_2;
    f32 temp_f18_3;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f20_3;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f22_3;
    f32 temp_f24;
    f32 temp_f24_2;
    f32 temp_f26;
    f32 temp_f26_2;
    f32 temp_f26_3;
    f32 temp_f28;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f30;
    f32 var_f12;
    f32 var_f14;
    f32 var_f22;
    f32 var_f22_2;
    f32 var_f24;
    f32 var_f24_2;
    f32 var_f26;
    f32 var_f26_2;
    f32 var_f2;
    s32 temp_a1;
    u8 *temp_v0;

    vtx_slot_buffer_get(arg0 + 0x100, arg1, 0x40, &sp.uC4, &sp.u7F);
    sp.uC0 = sp.uC4;
    if (sp.uC4 != NULL) {
        if (sp.u7F != 0) {
            temp_v0 = arg0 + (arg1 * 4);
            temp_a1 = arg0 + 0xC0;
            sp68 = temp_a1;
            sp6C = temp_v0;
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)), temp_a1, 0x40);
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)) + 0x40, temp_a1, 0x40);
        }
        temp_f30 = (*(f32 *)((u8 *)arg0 + 0x34));
        temp_f20 = (*(f32 *)((u8 *)arg0 + 0x38));
        temp_f0 = (*(f32 *)((u8 *)arg0 + 0x30));
        temp_f22 = (*(f32 *)((u8 *)arg0 + 0x3C));
        temp_f26 = temp_f30 + (((*(f32 *)((u8 *)arg0 + 0x40)) - temp_f30) * temp_f0);
        temp_f28 = temp_f20 + (((*(f32 *)((u8 *)arg0 + 0x44)) - temp_f20) * temp_f0);
        var_f2 = temp_f26 - temp_f30;
        sp.uB8 = temp_f22 + (((*(f32 *)((u8 *)arg0 + 0x48)) - temp_f22) * temp_f0);
        var_f12 = temp_f28 - temp_f20;
        temp_f18 = (*(f32 *)((u8 *)arg0 + 0x4C));
        var_f14 = sp.uB8 - temp_f22;
        temp_v0_2 = &D_800DBFF0[arg1].unk2F8;
        sp.uB4 = temp_f28;
        sp.uB0 = temp_f26;
        sp68 = temp_f20;
        sp64 = temp_f22;
        temp_f0_2 = (var_f2 * var_f2) + (var_f12 * var_f12) + (var_f14 * var_f14);
        if (temp_f0_2 < (temp_f18 * temp_f18)) {
            temp_f16 = 1.0f - (sqrtf(temp_f0_2) / temp_f18);
            var_f2 += var_f2 * temp_f16;
            var_f12 += var_f12 * temp_f16;
            var_f14 += var_f14 * temp_f16;
            sp68 = temp_f20;
            sp64 = temp_f22;
        }
        temp_f0_3 = temp_f30 - (*(f32 *)((u8 *)temp_v0_2 + 0));
        temp_f24 = sp64 - (*(f32 *)((u8 *)temp_v0_2 + 8));
        temp_f22_2 = sp68 - (*(f32 *)((u8 *)temp_v0_2 + 4));
        temp_f16_2 = (var_f12 * temp_f24) - (temp_f22_2 * var_f14);
        temp_f18_2 = (var_f14 * temp_f0_3) - (temp_f24 * var_f2);
        temp_f20_2 = (var_f2 * temp_f22_2) - (temp_f0_3 * var_f12);
        temp_f26_2 = (temp_f16_2 * temp_f16_2) + (temp_f18_2 * temp_f18_2) + (temp_f20_2 * temp_f20_2);
        sp.u88 = temp_f26_2;
        if (temp_f26_2 == 0.0f) {
            var_f22 = 0.0f;
            var_f24 = 0.0f;
            var_f26 = 0.0f;
        } else {
            sp74 = (*(f32 *)((u8 *)arg0 + 0x2C)) / sqrtf(sp.u88);
            var_f22 = temp_f16_2 * sp74;
            var_f24 = temp_f18_2 * sp74;
            var_f26 = temp_f20_2 * sp74;
        }
        temp_f12 = -var_f12;
        temp_f14 = -var_f14;
        temp_f2 = -var_f2;
        (*(s16 *)((u8 *)sp.uC4 + 0)) = (s16) (s32) (temp_f30 + var_f22);
        (*(s16 *)((u8 *)sp.uC4 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + var_f24);
        (*(s16 *)((u8 *)sp.uC4 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + var_f26);
        (*(s16 *)((u8 *)sp.uC4 + 6)) = 0;
        sp.uC4 += 0x10;
        sp.uC4[0x10] = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - var_f22);
        (*(s16 *)((u8 *)sp.uC4 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) - var_f24);
        (*(s16 *)((u8 *)sp.uC4 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - var_f26);
        (*(s16 *)((u8 *)sp.uC4 + 6)) = 0;
        sp.uC4 += 0x10;
        temp_f0_4 = sp.uB0 - (*(f32 *)((u8 *)temp_v0_2 + 0));
        temp_f22_3 = sp.uB4 - (*(f32 *)((u8 *)temp_v0_2 + 4));
        temp_f24_2 = sp.uB8 - (*(f32 *)((u8 *)temp_v0_2 + 8));
        temp_f16_3 = (temp_f12 * temp_f24_2) - (temp_f22_3 * temp_f14);
        temp_f18_3 = (temp_f14 * temp_f0_4) - (temp_f24_2 * temp_f2);
        temp_f20_3 = (temp_f2 * temp_f22_3) - (temp_f0_4 * temp_f12);
        temp_f26_3 = (temp_f16_3 * temp_f16_3) + (temp_f18_3 * temp_f18_3) + (temp_f20_3 * temp_f20_3);
        sp.u88 = temp_f26_3;
        if (temp_f26_3 == 0.0f) {
            var_f22_2 = 0.0f;
            var_f24_2 = 0.0f;
            var_f26_2 = 0.0f;
        } else {
            temp_f2_2 = (*(f32 *)((u8 *)arg0 + 0x2C)) / sqrtf(sp.u88);
            var_f22_2 = temp_f16_3 * temp_f2_2;
            var_f24_2 = temp_f18_3 * temp_f2_2;
            var_f26_2 = temp_f20_3 * temp_f2_2;
        }
        (*(s16 *)((u8 *)sp.uC4 + 0)) = (s16) (s32) (sp.uB0 + var_f22_2);
        (*(s16 *)((u8 *)sp.uC4 + 2)) = (s16) (s32) (sp.uB4 + var_f24_2);
        (*(s16 *)((u8 *)sp.uC4 + 4)) = (s16) (s32) (sp.uB8 + var_f26_2);
        (*(s16 *)((u8 *)sp.uC4 + 6)) = 0;
        sp.uC4 += 0x10;
        sp.uC4[0x10] = (s16) (s32) (sp.uB0 - var_f22_2);
        (*(s16 *)((u8 *)sp.uC4 + 2)) = (s16) (s32) (sp.uB4 - var_f24_2);
        (*(s16 *)((u8 *)sp.uC4 + 4)) = (s16) (s32) (sp.uB8 - var_f26_2);
        (*(s16 *)((u8 *)sp.uC4 + 6)) = 0;
        return sp.uC0;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/streak_build_vtx.s")
#endif
#ifdef NON_MATCHING
/* was func_1514B0CC */
void spark_spawn_burst(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, s16 arg9, s16 argA, u8 argB) {
    struct {
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        f32 uA0;
        f32 uA4;
        s16 uA8;
        s16 uAA;
        s16 uAC;
        s8 uAE;
        s8 uAF;
        s8 uB0;
        s8 uB1;
        s16 uB2;
        s8 uB4;
        s8 uB5;
        s8 uB6;
        u8 uB7;
        s32 uB8;
        s8 uBC;
        u8 padBD[0x3];
        f32 uC0;
        u8 padC4[0x4];
        f32 uC8;
        f32 uCC;
    } sp;
    f32 temp_f0;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f2;
    s16 var_s1;
    s32 temp_v0;

    var_s1 = arg4;
    if (var_s1 > 0) {
        sp.uAA = 0x1A4D;
        sp.uA8 = 0x6231;
        sp.uAE = 0;
        sp.uAF = 0;
        sp.uB0 = 0;
        sp.uB1 = 0xFF;
        sp.uB2 = 1;
        sp.uB4 = 0xFF;
        sp.uB5 = 0xFF;
        sp.uB8 = 0;
        sp.uB6 = 0;
        sp.uBC = 0xF;
        sp.u8C = arg1;
        sp.uC8 = 0.045f;
        sp.uB7 = argB;
        sp.uC0 = 0.0f;
        sp.uCC = 0.7f;
        do {
            temp_v0 = random_int();
            temp_f24 = angle_byte_cos((temp_v0 - 0x40) & 0xFF);
            temp_f26 = angle_byte_cos(temp_v0 & 0xFF & 0xFF);
            temp_f20 = random_float() * arg3;
            temp_f22 = (random_float() * arg6) + arg5;
            temp_f0 = random_float();
            sp.u88 = (temp_f20 * temp_f24) + arg0;
            sp.u90 = (temp_f20 * temp_f26) + arg2;
            sp.u94 = 22.6f * temp_f22;
            sp.u9C = 13.786f * temp_f22;
            temp_f2 = (temp_f0 * arg8) + arg7;
            sp.u98 = 57.969f * temp_f2;
            sp.uA0 = 42.714f * temp_f2;
            sp.uA4 = 118.763f * temp_f2;
            sp.uAC = (random_int() % (u32) (argA + 1)) + arg9;
            spark_spawn_from_desc(&sp.u88, 0xA, 0, 0, 0xFF, 1);
            var_s1 -= 1;
        } while (var_s1 != 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/spark_spawn_burst.s")
#endif
s32 spark_spawn_from_desc(f32 *, s32, s32, s32, s32, s32);
extern f32 D_800A5BAC;
extern f32 D_800A5BB0;
extern f32 D_800A5BB4;
extern f32 D_800A5BB8;
extern f32 D_800A5BBC;
extern f32 D_800A5BC0;
extern f32 D_800A5BC4;
extern f32 D_800A5BC8;
extern f32 D_800A5BCC;
extern f32 D_800A5BD0;
extern f32 D_800A5BD4;
extern f32 D_800A5BD8;
extern f32 D_800A5BDC;
extern f32 D_800A5BE0;
extern f32 D_800A5BE4;

/* was func_1514B30C */
void spark_spawn_random(f32 *arg0, u8 arg1, s32 arg2) {
    struct {
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        s16 u50;
        s16 u52;
        s16 u54;
        u8 u56;
        u8 u57;
        u8 u58;
        u8 u59;
        s16 u5A;
        u8 u5C;
        u8 u5D;
        u8 u5E;
        u8 u5F;
        s32 u60;
        u8 u64;
        u8 pad65[3];
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
    } sp;
    f32 a;
    f32 b;
    s32 pad[2]; // fakematch: frame

    do { sp.u50 = 0x6231; sp.u52 = 0x1A4D; } while (0); // fakematch: block boundary flips the two sh stores (permuter)
    *(V3A434 *)&sp.u30 = *(V3A434 *)arg0;
    sp.u56 = 0;
    sp.u57 = 0;
    sp.u58 = 0;
    sp.u59 = 0xFF;
    sp.u5D = 0xFF;
    sp.u5E = 0;
    sp.u5F = 1;
    sp.u60 = 0;
    sp.u5A = 1;
    sp.u64 = 0x1C;
    sp.u6C = 0.0f;
    sp.u70 = D_800A5BAC;
    sp.u74 = D_800A5BB0;
    a = (random_float() * D_800A5BB4 + D_800A5BB8) * D_800A5BBC;
    b = random_float();
    sp.u3C = D_800A5BC0 * a;
    sp.u44 = D_800A5BC4 * a;
    b = (b * D_800A5BC8 + D_800A5BCC) * D_800A5BD0;
    sp.u40 = D_800A5BD4 * b;
    sp.u48 = D_800A5BD8 * b;
    sp.u4C = D_800A5BDC * b;
    sp.u54 = random_int() % 17U + 16;
    sp.u68 = (random_float() * D_800A5BE0 + 50.0f) * D_800A5BE4;
    sp.u5C = random_int() % 156U + 100;
    spark_spawn_from_desc(&sp.u30, 0xA, 0, 0, arg1, arg2);
}

/* was func_1514B4E4 */
s32 spark_shrink_fall(struct_eu_EF410_b *arg0) {
    arg0->unk2C -= arg0->unk2C * arg0->unk150;
    arg0->unk30 -= arg0->unk30 * arg0->unk150;
    arg0->unk38 += arg0->unk50 * D_800BE9A4 + 0.5f * arg0->unk4C * D_800BE9A4 * D_800BE9A4;
    arg0->unk50 += arg0->unk4C * D_800BE9A4;
    if (arg0->unk2C < 10.0f || arg0->unk30 < 10.0f) {
        return 0;
    }
    return 1;
}

#ifdef NON_MATCHING
void vec2_from_angle_byte(s16, f32, f32 *, f32 *);

/* was func_1514B5A4 */
void lava_spark_fountain(u8 *arg0, s32 arg1, s32 arg2) {
    struct {
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        f32 uA0;
        s16 uA4;
        s16 uA6;
        s16 uA8;
        s8 uAA;
        s8 uAB;
        s8 uAC;
        s8 uAD;
        s16 uAE;
        s8 uB0;
        s8 uB1;
        s8 uB2;
        s8 uB3;
        s32 uB4;
        s8 uB8;
        u8 padB9[0x3];
        f32 uBC;
        f32 uC0;
        f32 uC4;
        f32 uC8;
    } sp;
    f32 temp_f16;
    f32 temp_f20;
    f32 temp_f2;
    f32 var_f24;
    s32 temp_s0;

    var_f24 = ((random_float() * 20.0f) + 29.0f) * 0.0001f * 5541.7695f;
    if (var_f24 > 1.0f) {
        sp.uA4 = 0x6231;
        sp.uA6 = 0x1A4D;
        sp.uAA = 0;
        sp.uAB = 0;
        sp.uAC = 0;
        sp.uAD = 0xFF;
        sp.uB1 = 0xFF;
        sp.uB2 = 0;
        sp.uB3 = 1;
        sp.uB4 = 0;
        sp.uAE = 1;
        sp.uB8 = 0x1C;
        sp.u88 = (*(f32 *)((u8 *)arg0 + 4));
        sp.uC0 = 0.0f;
        do {
            temp_s0 = random_int();
            vec2_from_angle_byte((s16) (temp_s0 & 0xFF), random_float() * 42.0f, &sp.u84, &sp.u8C);
            sp.u84 += (*(f32 *)((u8 *)arg0 + 0));
            sp.u8C += (*(f32 *)((u8 *)arg0 + 8));
            sp.uC4 = ((random_float() * 16.0f) + 29.0f) * 0.001f;
            sp.uC8 = ((random_float() * 600.0f) + 400.0f) * 0.001f;
            temp_f20 = ((random_float() * 1205.0f) + 304.0f) * 0.001f;
            temp_f16 = random_float() * 1006.0f;
            sp.u90 = 22.6f * temp_f20;
            sp.u98 = 13.786f * temp_f20;
            temp_f2 = (temp_f16 + 504.0f) * 0.001f;
            sp.u94 = 57.969f * temp_f2;
            sp.u9C = 42.714f * temp_f2;
            sp.uA0 = 118.763f * temp_f2;
            sp.uA8 = (random_int() % 31U) + 0x14;
            sp.uBC = random_float() * 497.0f * 0.001f;
            sp.uB0 = (random_int() % 156U) + 0x64;
            spark_spawn_from_desc(&sp.u84, 0xA, 0, 0, arg1 & 0xFF, arg2);
            var_f24 -= 1.0f;
        } while (var_f24 > 1.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/lava_spark_fountain.s")
#endif
#ifdef NON_MATCHING
/* P183 */
s32 collision_floor_probe(u8 *arg0, u16 arg1, f32 arg2, u8 *arg3);
s32 emit_streaks_from_spec(s32 *arg0, u8 arg1, s32 arg2);
void emit_sparks_by_angles_b(u8 *arg0, s32 arg1);
void lava_spark_fountain(u8 *arg0, s32 arg1, s32 arg2);
s32 random_int(void);

// lava_splash_effect: P183: when the point `pos` has ground within +-200 units below/above it (collision_floor_probe with
// `owner`), spawns the lava impact effects there: a 10-particle burst from spec A (emit_streaks_from_spec, owner byte
// arg2, extra arg3), a spark burst from spec B (emit_sparks_by_angles_b, alpha 0x9B + rand 0..100), the third burst
// lava_spark_fountain (pos, arg2, arg3), and one 0x38-type particle 10 units above pos (effect3d_spawn_oriented_simple, size 100 x 100,
// random colour / frame bits, link owner + 4). The asm returns the stale effect3d_spawn_oriented_simple v0 (callers ignore it);
// kept s32 for the callers' prototype (returns 0).
/* was func_1514B8D4 */
s32 lava_splash_effect(f32 *pos, u8 *owner, u8 arg2, s32 arg3) {
    struct {
        s32 countBase;      /* 0x00 */
        s32 countExtra;     /* 0x04 */
        s32 pos[3];         /* 0x08 */
        f32 aBase;          /* 0x14 */
        f32 aRange;         /* 0x18 */
        f32 bBase;          /* 0x1C */
        f32 bRange;         /* 0x20 */
        f32 lenBase;        /* 0x24 */
        f32 lenRange;       /* 0x28 */
        s16 angXBase;       /* 0x2C */
        s16 angXExtra;      /* 0x2E */
        s16 angYBase;       /* 0x30 */
        s16 angYExtra;      /* 0x32 */
        s32 flagBase;       /* 0x34 */
        s32 flagExtra;      /* 0x38 */
        s16 lifeBase;       /* 0x3C */
        s16 lifeExtra;      /* 0x3E */
        u16 u40;            /* 0x40 */
        u8 u42[3];          /* 0x42 */
        u8 colABase[4];     /* 0x45 */
        u8 colAExtra[4];    /* 0x49 */
        u8 colBBase[4];     /* 0x4D */
        u8 colBExtra[4];    /* 0x51 */
        u8 u55Base;         /* 0x55 */
        u8 u55Extra;        /* 0x56 */
        u8 u57[2];          /* 0x57 */
        s32 u5C;            /* 0x5C */
        s32 u60;            /* 0x60 */
        s16 u64;            /* 0x64 */
        s16 u66;            /* 0x66 */
        s16 u68;            /* 0x68 */
        u8 u6A;             /* 0x6A */
        f32 u6C;            /* 0x6C */
        s8 u70;             /* 0x70 */
        s8 u71;             /* 0x71 */
        s8 u72[2];          /* 0x72 */
    } specA;
    struct {
        s32 pos[3];         /* 0x00 */
        f32 f0C[6];         /* 0x0C */
        s16 h24[10];        /* 0x24 */
        u8 b38[2];          /* 0x38 */
        s32 w3C[6];         /* 0x3C */
        u8 b54[2];          /* 0x54 */
    } specB;
    struct {
        u8 type;            /* 0x00 */
        s16 u02;            /* 0x02 */
        s16 u04;            /* 0x04 */
        s32 u08;            /* 0x08 */
        s32 u0C;            /* 0x0C */
        u8 col[4];          /* 0x10 */
        f32 u14[2];         /* 0x14 */
        f32 pos[3];         /* 0x1C */
        f32 u28[3];         /* 0x28 */
        f32 u34;            /* 0x34 */
        f32 u38[2];         /* 0x38 */
        s32 flags;          /* 0x40 */
        u8 u44[4];          /* 0x44 */
    } part;
    f32 probe[3];
    s32 at[3];
    s32 r6, r7, r8;

    at[0] = ((s32 *) pos)[0];
    at[1] = ((s32 *) pos)[1];
    at[2] = ((s32 *) pos)[2];
    probe[0] = pos[0];
    probe[1] = pos[1] + 200.0f;
    probe[2] = pos[2];
    if (collision_floor_probe((u8 *) probe, 0, pos[1] - 200.0f, owner) == 0) {
        return 0;
    }

    specA.countBase = 10;
    specA.countExtra = 0;
    specA.aBase = 9.900001f;
    specA.aRange = 21.0f;
    specA.bBase = -3.0000002f;
    specA.bRange = 1.016f;
    specA.lenBase = 30.0f;
    specA.lenRange = 30.4f;
    specA.angXBase = 0;
    specA.angXExtra = 0xFF;
    specA.angYBase = -0x3F;
    specA.angYExtra = 0x2B;
    specA.flagBase = 4;
    specA.flagExtra = 5;
    specA.lifeBase = 30;
    specA.lifeExtra = 30;
    specA.u40 = 1;
    specA.u42[0] = 0xC;
    specA.u42[1] = 2;
    specA.u42[2] = 3;
    specA.colABase[0] = 0xB4;
    specA.colABase[1] = 0;
    specA.colABase[2] = 0;
    specA.colABase[3] = 0x9B;
    specA.colAExtra[0] = 0x32;
    specA.colAExtra[1] = 0x64;
    specA.colAExtra[2] = 0;
    specA.colAExtra[3] = 0x64;
    specA.colBBase[0] = 0xFF;
    specA.colBBase[1] = 0xFF;
    specA.colBBase[2] = 0xFF;
    specA.colBBase[3] = 0xFF;
    specA.colBExtra[0] = 0;
    specA.colBExtra[1] = 0;
    specA.colBExtra[2] = 0;
    specA.colBExtra[3] = 0;
    specA.u55Base = 0xFF;
    specA.u55Extra = 0;
    specA.u57[0] = 1;
    specA.u57[1] = 0x24;
    specA.u5C = 0x200005;
    specA.u60 = 0x60600;
    specA.u64 = 20;
    specA.u66 = 12;
    specA.u68 = 1;
    specA.u6A = 0;
    specA.u6C = 1.0f;
    specA.u70 = -1;
    specA.u71 = 0;
    specA.u72[0] = -1;
    specA.u72[1] = -1;
    specA.pos[0] = at[0];
    specA.pos[1] = at[1];
    specA.pos[2] = at[2];
    emit_streaks_from_spec((s32 *) &specA, arg2, arg3);

    specB.pos[0] = at[0];
    specB.pos[1] = at[1];
    specB.pos[2] = at[2];
    specB.f0C[0] = 3.99f;
    specB.f0C[1] = 8.11f;
    specB.f0C[2] = 0.60200006f;
    specB.f0C[3] = 0.407f;
    specB.f0C[4] = 10.139999f;
    specB.f0C[5] = 10.2699995f;
    specB.h24[0] = 8;
    specB.h24[1] = 8;
    specB.h24[2] = 0;
    specB.h24[3] = 0xFF;
    specB.h24[4] = -0x40;
    specB.h24[5] = 0x2C;
    specB.h24[6] = 5;
    specB.h24[7] = 4;
    specB.h24[8] = 0x42;
    specB.h24[9] = 30;
    specB.b38[0] = 10;
    specB.b38[1] = 0x21;
    specB.w3C[0] = 1;
    specB.w3C[1] = 12;
    specB.w3C[2] = 0;
    specB.w3C[3] = 0;
    specB.w3C[4] = 0;
    specB.w3C[5] = 0;
    specB.b54[0] = 0xFF;
    specB.b54[1] = (u32) random_int() % 101 + 0x9B;
    emit_sparks_by_angles_b((u8 *) &specB, 0xFF);

    lava_spark_fountain((u8 *) at, arg2, arg3);

    part.type = 0x38;
    part.u02 = 1;
    part.u04 = 50;
    part.u08 = 0;
    part.u0C = 0x6666;
    part.col[3] = 0xFF;
    part.u14[0] = 1.0f;
    part.u14[1] = 1.0f;
    part.pos[0] = *(f32 *) &at[0];
    part.pos[1] = *(f32 *) &at[1] + 10.0f;
    part.pos[2] = *(f32 *) &at[2];
    part.u28[0] = 0.0f;
    part.u28[1] = 0.0f;
    part.u28[2] = 0.0f;
    part.u34 = 0.2f;
    part.u38[0] = 1.0f;
    part.u38[1] = 1.0f;
    part.flags = 0x400C0001;
    part.u44[0] = (u32) random_int() % 101 + 100;
    part.u44[1] = 0xFF;
    part.u44[2] = 0;
    part.u44[3] = 6;
    part.col[0] = (u32) random_int() % 51 + 0xB4;
    part.col[1] = (u32) random_int() % 101;
    random_int();
    part.col[2] = 0;
    r6 = random_int();
    r7 = random_int();
    r8 = random_int();
    effect3d_spawn_oriented_simple((s32) &part, 0, 0x12, 0x1D, 0, (r7 & 1) + (r6 & 1), r8 & 0xFF, 100.0f, 100.0f, 0, (s32) (owner + 4),
                  0, 0, arg2, arg3);
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/lava_splash_effect.s")
#endif
/* was func_1514BDB4 */
s32 trail_fade_out(u8 *arg0) {
    u8 *temp_v0;
    s16 temp_v1;
    temp_v0 = *(u8 **)(arg0 + 0x98);
    temp_v1 = *(s16 *)(arg0 + 0x1C);
    if (temp_v1 < 16) {
        if ((temp_v1 << 4) < temp_v0[0x1B]) {
            temp_v0[0x1B] = temp_v1 << 4;
        }
    }
    return 1;
}

/* was func_1514BDEC */
s32 effect3d_grow_size(f32 *arg0) {
    f32 temp_f0 = arg0[0x4C / 4] * D_800BE9A4;
    arg0[0x2C / 4] += temp_f0;
    arg0[0x30 / 4] += temp_f0;
    return 1;
}

/* was func_1514BE20 */
s32 effect3d_fade_out(u8 *arg0) {
    s16 temp_v0 = *(s16 *)(arg0 + 0x1C);
    if (temp_v0 < 16) {
        if ((temp_v0 << 4) < arg0[0x5C]) {
            arg0[0x5C] = temp_v0 << 4;
        }
    }
    return 1;
}

#ifdef NON_MATCHING
/* was func_1514BE54 */
u8 *flame_spawn(u8 *arg0, u8 *arg1, s16 arg2, u8 arg3, u8 *arg4, f32 arg5, f32 arg6, f32 arg7, u8 arg8, u8 arg9, u8 argA, s32 argB, u8 argC, s16 argD, s16 argE, s32 argF, u8 arg10, s32 arg11) {
    struct {
        f32 u4C;
        f32 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        s32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        s8 u9C;
        s8 u9D;
        s16 u9E;
        s16 uA0;
        u8 padA2[0x2];
        s32 uA4;
        s32 uA8;
        s8 uAC;
        s8 uAD;
        s8 uAE;
        s8 uAF;
        f32 uB0;
        f32 uB4;
        s32 uB8;
        u8 padBC[0x8];
        s32 uC4;
        f32 uC8;
        s32 uCC;
        f32 uD0;
        f32 uD4;
        f32 uD8;
        s32 uDC;
        u8 uE0;
        s8 uE1;
        s8 uE2;
        s8 uE3;
        s32 uE4;
        u8 padE8[0x8];
        s16 uF0;
        s16 uF2;
        u8 * uF4;
    } sp;
    s32 var_a0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1_2;
    u8 *temp_v0;
    u8 *var_v1;

    if (arg4 != NULL) {
        (*(s32 *)((u8 *)(&sp.u84) + 0)) = (*(s32 *)((u8 *)arg4 + 0));
        (*(s32 *)((u8 *)(&sp.u84) + 4)) = (s32) (*(s32 *)((u8 *)arg4 + 4));
        (*(s32 *)((u8 *)(&sp.u84) + 8)) = (s32) (*(s32 *)((u8 *)arg4 + 8));
    } else {
        sp.u84 = 0;
        sp.u88 = 0.0f;
        sp.u8C = 0.0f;
    }
    sp.u90 = arg5;
    sp.u68 = 0.0f;
    sp.u6C = 0.0f;
    sp.u7C = 0.0f;
    sp.uA8 = 0x3E3F;
    sp.u80 = 15935.0f;
    sp.u78 = 15935.0f;
    sp.u70 = 6733.0f;
    sp.u94 = arg6;
    sp.u98 = arg7;
    sp.u74 = 18404.0f;
    sp.u4C = (*(f32 *)((u8 *)arg1 + 0)) * 15.045272f;
    sp.u54 = (*(f32 *)((u8 *)arg1 + 0)) * 5.8676558f;
    sp.uB0 = 0.0f;
    sp.u5C = (*(f32 *)((u8 *)arg1 + 0)) * 12.111444f;
    sp.u50 = (*(f32 *)((u8 *)arg1 + 4)) * 0.396174f;
    sp.u58 = (*(f32 *)((u8 *)arg1 + 4)) * 0.1042563f;
    sp.u64 = (*(f32 *)((u8 *)arg1 + 4)) * 0.5197371f;
    sp.uB4 = 0.0f;
    sp.u9D = 0;
    sp.u9E = 0x2203;
    sp.u9C = (s8) argB;
    sp.u60 = (*(f32 *)((u8 *)arg1 + 4)) * 0.34404588f;
    if (arg2 == -1) {
        sp.uA0 = 0x12C;
    } else {
        sp.uA0 = arg2;
    }
    sp.uA4 = 0;
    sp.uAC = 0xFF;
    sp.uAD = 0xFF;
    sp.uAE = 0xFF;
    sp.uAF = 0xFF;
    var_v1_2 = 0;
    (*(s32 *)((u8 *)(&sp.uB8) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
    (*(f32 *)((u8 *)(&sp.uB8) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.uB8) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    sp.uC4 = (*(s32 *)((u8 *)arg0 + 0));
    sp.uC8 = (*(f32 *)((u8 *)arg0 + 4)) + 100.0f;
    sp.uD0 = 1.0f;
    sp.uD4 = 1.0f;
    sp.uD8 = 1.0f;
    sp.uCC = (*(s32 *)((u8 *)arg0 + 8));
    if (argC & 1) {
        var_v1_2 = 0x800000;
    }
    if (arg2 == -1) {
        var_a0 = 0;
    } else {
        var_a0 = 1;
    }
    var_v0 = 0;
    if (argC & 2) {
        var_v0 = 0x02000000;
    }
    sp.uDC = var_v0 | var_a0 | 0x40000 | 0x80000 | 0x200000 | 0x400000 | var_v1_2 | 0x40000000;
    sp.uE1 = 0xFF;
    sp.uE2 = 0;
    sp.uE3 = 7;
    sp.uE4 = 0;
    sp.uE0 = arg3;
    sp.uF0 = argD;
    sp.uF2 = argE;
    if (random_int() & 1) {
        var_v0_2 = 1;
    } else {
        var_v0_2 = 0;
    }
    temp_v0 = effect3d_spawn_full(&sp.u9C, (s32) ((u8 *)&D_800A4AA0), arg8, arg9, (u8) (s32) argA, 0x1CU, (u8) (var_v0_2 | 2), 0, 0, argF + 0x50, (u8) (s32) arg10, arg11);
    var_v1 = temp_v0;
    if (temp_v0 != NULL) {
        sp.uF4 = temp_v0;
        memcpy(temp_v0 + 0x110, &sp.u4C, 0x50);
        var_v1 = sp.uF4;
    }
    return var_v1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/flame_spawn.s")
#endif
/* was func_1514C178 */
s32 flame_flicker_update(u8 *arg0, u8 *arg1) {

    (*(f32 *)((u8 *)arg1 + 0x1C)) = (f32) ((*(f32 *)((u8 *)arg1 + 0x1C)) - D_800BE9A4);
    if ((*(f32 *)((u8 *)arg1 + 0x1C)) < 0.0f) {
        (*(f32 *)((u8 *)arg1 + 0x1C)) = (f32) (random_float() * 4.0f);
        (*(f32 *)((u8 *)arg1 + 0x10)) = (f32) ((*(f32 *)((u8 *)arg1 + 0)) + ((*(f32 *)((u8 *)arg1 + 8)) * random_float()));
    }
    (*(f32 *)((u8 *)arg0 + 0x2C)) += ((*(f32 *)((u8 *)arg1 + 0x10)) - (*(f32 *)((u8 *)arg0 + 0x2C))) * 0.35f;
    (*(f32 *)((u8 *)arg1 + 0x20)) = (f32) ((*(f32 *)((u8 *)arg1 + 0x20)) - D_800BE9A4);
    if ((*(f32 *)((u8 *)arg1 + 0x20)) < 0.0f) {
        (*(f32 *)((u8 *)arg1 + 0x20)) = (f32) (random_float() * 9.0f);
        if (random_int() & 1) {
            (*(f32 *)((u8 *)arg1 + 0x14)) = (f32) ((*(f32 *)((u8 *)arg1 + 4)) + ((*(f32 *)((u8 *)arg1 + 0xC)) * random_float()));
        } else {
            (*(f32 *)((u8 *)arg1 + 0x14)) = (f32) ((*(f32 *)((u8 *)arg1 + 4)) + ((*(f32 *)((u8 *)arg1 + 0x18)) * random_float()));
        }
    }
    (*(f32 *)((u8 *)arg0 + 0x30)) += ((*(f32 *)((u8 *)arg1 + 0x14)) - (*(f32 *)((u8 *)arg0 + 0x30))) * 0.4f;
    (*(f32 *)((u8 *)arg1 + 0x30)) = (f32) ((*(f32 *)((u8 *)arg1 + 0x30)) - D_800BE9A4);
    if ((*(f32 *)((u8 *)arg1 + 0x30)) < 0.0f) {
        (*(f32 *)((u8 *)arg1 + 0x30)) = (f32) (random_float() * 7.0f);
        (*(f32 *)((u8 *)arg1 + 0x2C)) = (f32) ((*(f32 *)((u8 *)arg1 + 0x24)) + ((*(f32 *)((u8 *)arg1 + 0x28)) * random_float()));
    }
    (*(f32 *)((u8 *)arg1 + 0x34)) += ((*(f32 *)((u8 *)arg1 + 0x2C)) - (*(f32 *)((u8 *)arg1 + 0x34))) * 0.4f;
    (*(s32 *)((u8 *)arg0 + 0x24)) = (s32) (*(f32 *)((u8 *)arg1 + 0x34));
    return 1;
}

/* was func_1514C370 */
void flame_flicker(u8 *arg0) {
    flame_flicker_update(arg0, arg0 + 0x110);
}

#ifdef NON_MATCHING
/* P133 */
s32 vec3_normalize_len(f32 *, f32 *, s32 *, s32 *);

/*
 * camera_look_follow: moves the look point (cam + 0x40, 3 floats) towards the point 100 above the position
 * (cam + 0x34) by the factor at cam + 0x15C, then puts it back at distance 100 from the position along that
 * direction (normalised by vec3_normalize_len); when the direction cannot be normalised the look point becomes the
 * position.
 */
/* was func_1514C390 */
void effect3d_look_follow(u8 *cam) {
    f32 *pos = (f32 *) (cam + 0x34);
    f32 *look = (f32 *) (cam + 0x40);
    f32 t = *(f32 *) (cam + 0x15C);
    f32 goal[3];
    f32 lerp[3];
    f32 dir[3];
    s32 len, unused;

    goal[1] = pos[1] + 100.0f;
    goal[2] = pos[2];
    lerp[0] = look[0] + (pos[0] - look[0]) * t;
    lerp[1] = look[1] + (goal[1] - look[1]) * t;
    lerp[2] = look[2] + (goal[2] - look[2]) * t;
    dir[0] = lerp[0] - pos[0];
    dir[1] = lerp[1] - pos[1];
    dir[2] = lerp[2] - pos[2];
    if (vec3_normalize_len(dir, dir, &len, &unused) != 0) {
        look[0] = pos[0] + dir[0] * 100.0f;
        look[1] = pos[1] + dir[1] * 100.0f;
        look[2] = pos[2] + dir[2] * 100.0f;
    } else {
        look[0] = pos[0];
        look[1] = pos[1];
        look[2] = pos[2];
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/effect3d_look_follow.s")
#endif

/* was func_1514C4C0 */
void effect3d_look_set_up(f32 *arg0) {
    arg0[0x40 / 4] = arg0[0x34 / 4];
    arg0[0x44 / 4] = arg0[0x38 / 4] + 100.0f;
    arg0[0x48 / 4] = arg0[0x3C / 4];
}

/* was func_1514C4EC */
void flame_flicker_b(u8 *arg0) {
    flame_flicker_update(arg0, arg0 + 0x110);
}

#ifdef NON_MATCHING
/* was func_1514C50C */
void flame_drift_update(u8 *arg0) {
    struct {
        f32 u20;
        f32 u24;
        f32 u28;
        u8 pad2C[0x4];
    } sp;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 var_f16;
    f32 var_f18;
    s32 temp_a1;
    s32 temp_a2;
    s32 var_v1;
    s32 var_v1_2;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;

    (*(f32 *)((u8 *)(&sp.u20) + 0)) = (*(f32 *)((u8 *)arg0 + 0x148));
    (*(s32 *)((u8 *)(&sp.u20) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 0x14C));
    (*(s32 *)((u8 *)(&sp.u20) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0x150));
    var_v1 = D_800BE9E4;
    if (var_v1 != 0) {
        temp_a2 = -(var_v1 & 3);
        temp_a1 = temp_a2 + var_v1;
        if (temp_a2 != 0) {
            temp_v0 = arg0 + 0x110;
            temp_f0 = (*(f32 *)((u8 *)temp_v0 + 0x48));
            var_v1 -= 1;
            var_f18 = (*(f32 *)((u8 *)temp_v0 + 0x38)) * temp_f0;
            if (temp_a1 != var_v1) {
                do {
                    (*(f32 *)((u8 *)temp_v0 + 0x38)) = var_f18;
                    var_v1 -= 1;
                    var_f18 = (*(f32 *)((u8 *)temp_v0 + 0x38)) * temp_f0;
                    (*(f32 *)((u8 *)temp_v0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x3C)) * temp_f0);
                    (*(f32 *)((u8 *)temp_v0 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x40)) * temp_f0);
                } while (temp_a1 != var_v1);
            }
            (*(f32 *)((u8 *)temp_v0 + 0x38)) = var_f18;
            (*(f32 *)((u8 *)temp_v0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x3C)) * temp_f0);
            (*(f32 *)((u8 *)temp_v0 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x40)) * temp_f0);
            if (var_v1 != 0) {
                goto block_5;
            }
        } else {
block_5:
            temp_v0_2 = arg0 + 0x110;
            temp_f0_2 = (*(f32 *)((u8 *)temp_v0_2 + 0x48));
            var_v1_2 = var_v1 - 4;
            var_f16 = (*(f32 *)((u8 *)temp_v0_2 + 0x38)) * temp_f0_2;
            if (var_v1_2 != 0) {
                do {
                    (*(f32 *)((u8 *)temp_v0_2 + 0x38)) = var_f16;
                    var_v1_2 -= 4;
                    (*(f32 *)((u8 *)temp_v0_2 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x3C)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v0_2 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x40)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v0_2 + 0x38)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x38)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v0_2 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x3C)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v0_2 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x40)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v0_2 + 0x38)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x38)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v0_2 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x3C)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v0_2 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x40)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v0_2 + 0x38)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x38)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v0_2 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x3C)) * temp_f0_2);
                    var_f16 = (*(f32 *)((u8 *)temp_v0_2 + 0x38)) * temp_f0_2;
                    (*(f32 *)((u8 *)temp_v0_2 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x40)) * temp_f0_2);
                } while (var_v1_2 != 0);
            }
            (*(f32 *)((u8 *)temp_v0_2 + 0x38)) = var_f16;
            (*(f32 *)((u8 *)temp_v0_2 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x3C)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v0_2 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x40)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v0_2 + 0x38)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x38)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v0_2 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x3C)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v0_2 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x40)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v0_2 + 0x38)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x38)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v0_2 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x3C)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v0_2 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x40)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v0_2 + 0x38)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x38)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v0_2 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x3C)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v0_2 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x40)) * temp_f0_2);
        }
    }
    temp_v0_3 = arg0 + 0x110;
    (*(f32 *)((u8 *)temp_v0_3 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0_3 + 0x3C)) + ((*(f32 *)((u8 *)temp_v0_3 + 0x44)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x34)) + ((sp.u20 + (0.5f * (((*(f32 *)((u8 *)temp_v0_3 + 0x38)) - sp.u20) * D_800BEDC8) * D_800BE9A4)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + ((sp.u24 + (0.5f * (((*(f32 *)((u8 *)temp_v0_3 + 0x3C)) - sp.u24) * D_800BEDC8) * D_800BE9A4)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + ((sp.u28 + (0.5f * (((*(f32 *)((u8 *)temp_v0_3 + 0x40)) - sp.u28) * D_800BEDC8) * D_800BE9A4)) * D_800BE9A4));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/flame_drift_update.s")
#endif
/* was func_1514C7C8 */
s32 flame_drift_look_follow(void *arg0) {
    flame_drift_update(arg0);
    effect3d_look_follow(arg0);
    return 1;
}

/* was func_1514C7F8 */
s32 flame_drift_look_up(void *arg0) {
    flame_drift_update(arg0);
    effect3d_look_set_up(arg0);
    return 1;
}

/* was func_1514C828 */
s32 flame_start_end(u8 *arg0) {
    arg0[0x72] = 0;
    arg0[0x71] = 0x24;
    *(s16 *)(arg0 + 0x1C) = *(s16 *)(arg0 + 0x164);
    *(s32 *)(arg0 + 0x58) |= 0x08000000;
    *(f32 *)(arg0 + 0x154) = *(f32 *)(arg0 + 0x160);
    return 1;
}

#ifdef NON_MATCHING
/* P136 */
extern s32 D_8008ADA0;

/*
 * spawn_ring_emit: emits count (s16) points on a circle of radius r around (x, y, z) in the x/z plane, starting at
 * the byte angle angle0 and stepping by the signed byte step (wrapping at 256). Each point goes to the spawn
 * handler kind of D_8008ADA0 as (1, i, x + r * sin(a - 0x40), y, z + r * sin(a), x, y, z, a, angle0, r, arg8,
 * arg9, argA, argB) (angle_byte_cos = byte-angle sine); the walk stops early when a handler returns 0, a missing
 * handler skips the point. Returns 0 (callers declare s32 and ignore it; the asm leaves no defined value).
 */
/* was func_1514C860 */
s32 spawn_ring_emit(f32 x, f32 y, f32 z, f32 r, u8 angle0, s8 step, s16 count, u8 kind, s32 arg8, f32 arg9, s32 argA,
                  u8 argB) {
    s32 (*handler)(s32, s16, f32, f32, f32, f32, f32, f32, s32, s32, f32, s32, f32, s32, s32);
    s32 a = angle0;
    f32 c, s;
    s16 i;

    for (i = 0; i < count; i++) {
        c = angle_byte_cos((a - 0x40) & 0xFF);
        s = angle_byte_cos(a & 0xFF);
        handler = ((void **) &D_8008ADA0)[kind];
        if (handler != NULL && handler(1, i, x + r * c, y, z + r * s, x, y, z, a, angle0, r, arg8, arg9, argA, argB) == 0) {
            break;
        }
        a = (a + step) & 0xFF;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/spawn_ring_emit.s")
#endif

#ifdef NON_MATCHING
/* P139 */
extern s32 D_8008ADA0;

/*
 * spawn_line_emit: emits count (a float, at least 2) evenly spaced points on the segment from (x0, y0, z0) to
 * (x1, y1, z1), step = (end - start) * (1 / (count - 1)) per axis. Each point goes to the spawn handler kind of
 * D_8008ADA0 as (0, i, x, y, z, x0, y0, z0, 0, 0, 0.0f, arg8, arg9, argA, argB) (mode 0 = line; the ring emitter
 * spawn_ring_emit uses mode 1); the walk stops early when a handler returns 0, a missing handler skips the point.
 * The loop counts count down by 1 while it stays > 0. (The asm tests the parity of (s32) count and computes the
 * same step in both branches.)
 */
/* was func_1514C9E0 */
void spawn_line_emit(f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, f32 count, u8 kind, s32 arg8, f32 arg9, s32 argA,
                   u8 argB) {
    s32 (*handler)(s32, s16, f32, f32, f32, f32, f32, f32, s32, s32, f32, s32, f32, s32, s32);
    f32 inv;
    f32 dx, dy, dz;
    f32 x, y, z;
    s16 i = 0;

    if (count < 2.0f) {
        return;
    }
    inv = 1.0f / (count - 1.0f);
    dx = (x1 - x0) * inv;
    dy = (y1 - y0) * inv;
    dz = (z1 - z0) * inv;
    x = x0;
    y = y0;
    z = z0;
    do {
        handler = ((void **) &D_8008ADA0)[kind];
        if (handler != NULL && handler(0, i, x, y, z, x0, y0, z0, 0, 0, 0.0f, arg8, arg9, argA, argB) == 0) {
            break;
        }
        count -= 1.0f;
        x += dx;
        i++;
        y += dy;
        z += dz;
    } while (count > 0.0f);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/spawn_line_emit.s")
#endif

#ifdef NON_MATCHING
extern s32 D_8008ADA0;

/* was func_1514CBE8 */
void spawn_circle_random_emit(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5, s16 arg6, u8 arg7, s32 arg8, f32 arg9, s32 argA, u8 argB) {
    f32 temp_f20;
    f32 temp_f2;
    s16 var_s1;
    s16 var_v0;
    s16 var_v1;
    s32 (*temp_v0)(s32, s16, f32, f32, f32, f32, f32, f32, s32, s32, f32, s32, f32, s32, s32);
    s32 temp_a0;
    s32 temp_s0;

    if (arg5 < arg4) {
        var_v0 = (arg4 - arg5) + 1;
        var_v1 = arg5;
    } else {
        var_v0 = (arg5 - arg4) + 1;
        var_v1 = arg4;
    }
    var_s1 = 0;
    if (arg6 > 0) {
loop_5:
        temp_a0 = (random_int() % (u32) var_v0) + var_v1;
        temp_s0 = temp_a0 & 0xFF;
        temp_f20 = angle_byte_cos((temp_a0 - 0x40) & 0xFF);
        temp_v0 = *(((s32 *)((u8 *)&D_8008ADA0 + (arg7 * 4))));
        temp_f2 = (arg3 * angle_byte_cos(temp_s0 & 0xFF)) + arg2;
        if (temp_v0 != NULL) {
            if (temp_v0(2, var_s1, (arg3 * temp_f20) + arg0, arg1, temp_f2, arg0, arg1, arg2, temp_s0, (s32) arg4, arg3, arg8, arg9, argA, (s32) argB) != 0) {
                goto block_9;
            }
            return;
        }
block_9:
        var_s1 += 1;
        if (var_s1 >= arg6) {

        } else {
            goto loop_5;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/spawn_circle_random_emit.s")
#endif
#ifdef NON_MATCHING
/* P139 */
extern s32 D_8008ADA0;

/*
 * spawn_arc_emit: emits count random points on a vertical circle of radius r around (x, y, z) whose plane faces
 * the byte angle yaw: each point takes a random byte angle a in [min(a0, a1), max(a0, a1)] and goes to the spawn
 * handler kind of D_8008ADA0 as (3, i, x + r * sin(yaw - 0x40) * sin(a), y - r * sin(a - 0x40),
 * z + r * sin(yaw) * sin(a), x, y, z, a & 0xFF, yaw, r, arg9, argA, argB, argC) (mode 3 = arc; angle_byte_cos =
 * byte-angle sine). The walk stops when a handler returns 0; a missing handler skips the point.
 */
/* was func_1514CDC8 */
void spawn_arc_emit(f32 x, f32 y, f32 z, f32 r, s16 yaw, s16 a0, s16 a1, s16 count, u8 kind, s32 arg9, f32 argA,
                   s32 argB, u8 argC) {
    s32 (*handler)(s32, s16, f32, f32, f32, f32, f32, f32, s32, s32, f32, s32, f32, s32, s32);
    f32 cosYaw = angle_byte_cos((yaw - 0x40) & 0xFF);
    f32 sinYaw = angle_byte_cos(yaw & 0xFF);
    f32 rc;
    f32 rs;
    f32 c, s;
    f32 px, pz;
    s16 n;
    s16 lo;
    s16 i;
    s32 a;
    s32 b;

    if (a1 < a0) {
        n = a0 - a1 + 1;
        lo = a1;
    } else {
        n = a1 - a0 + 1;
        lo = a0;
    }
    if (count <= 0) {
        return;
    }
    rc = r * cosYaw;
    rs = r * sinYaw;
    i = 0;
    do {
        a = (u32) random_int() % (u32) n + lo;
        b = a & 0xFF;
        c = angle_byte_cos((a - 0x40) & 0xFF);
        s = angle_byte_cos(b);
        handler = ((void **) &D_8008ADA0)[kind];
        px = rc * s + x;
        pz = rs * s + z;
        if (handler != NULL && handler(3, i, px, y - r * c, pz, x, y, z, b, yaw, r, arg9, argA, argB, argC) == 0) {
            return;
        }
        i++;
    } while (i < count);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/spawn_arc_emit.s")
#endif
