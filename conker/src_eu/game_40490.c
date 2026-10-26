#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15012FE0 */
void level_clear_be570(void) {
    D_800BE570 = 0;
    D_800BE574 = 0;
    D_800BE575 = 0;
}

typedef struct {
    u8 pad0[0x15];
    u8 unk15;
    u8 pad16[0x1E];
} struct_eu_40490_obj; // size 0x34

extern void (*D_800831C0[])();

#ifdef NON_MATCHING
/* was func_15013000 */
void hotspots_start_all(void) {
    s32 var_s0;
    u32 var_s1;
    void (*temp_a1)(u8 *, s32);

    D_800DCDC4 = 0;
    D_800DCD90 = 0.0f;
    var_s1 = 0;
    var_s0 = 0;
    if (D_800D3094 != 0) {
        do {
            temp_a1 = D_800831C0[((s32) (*(u8 *)((u8 *)(&D_800D34B8[var_s0]) + 0x15)) >> 2) & 0xFF];
            if (temp_a1 != NULL) {
                temp_a1(&D_800D34B8[var_s0], temp_a1);
            }
            var_s1 += 1;
            var_s0 += 0x34;
        } while (var_s1 < (u32) D_800D3094);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/hotspots_start_all.s")
#endif
// NON-MATCHING: global stores/loads scheduled differently, regalloc
// void hotspots_start_all(void) {
//     u32 i;
//     void (*func)();
//     struct_eu_40490_obj *obj;
//
//     D_800DCDC4 = 0;
//     D_800DCD90 = 0.0f;
//     for (i = 0; i < D_800D3094; i++) {
//         obj = &((struct_eu_40490_obj *)D_800D34B8)[i];
//         func = D_800831C0[(u8)(obj->unk15 >> 2)];
//         if (func != NULL) {
//             func(obj, func);
//         }
//     }
// }

#ifdef NON_MATCHING
extern s32 D_80096930[3];
extern s32 D_8009693C[];
extern s32 D_80096950[];
extern s32 D_80096960[];
extern f32 D_80096984;
extern f32 D_80096988;
extern f32 D_8009698C;
extern f32 D_80096990;
extern f32 D_800969E0;
extern f32 D_800969E4;
extern f32 D_800969E8;
extern u8 D_80083228[6];
void collision_select_area(s32);
u8 *world_record_find(u8);
u8 *particle_emitter_spawn(void *emit, s32 emitSize, void *spawn, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s8 arg7, u8 arg8,
                  s32 arg9);

/* the record record_particle_emitter_start reads (D_80082EA0 start handlers get the level record) */
typedef struct {
    s16 x, y, z;        /* 0x00 */
    s16 rangeX;         /* 0x06 */
    s16 rangeY;         /* 0x08 */
    u8 pad0A[2];
    f32 angX;           /* 0x0C */
    f32 angY;           /* 0x10 */
    u8 pad14[2];
    u8 flags16;         /* 0x16 */
    u8 pad17;
    u32 colour;         /* 0x18: r / g / b in bytes 0..2, kind index in the top byte */
    s32 type;           /* 0x1C: 1..19 */
    u32 opts;           /* 0x20: top byte: with sound, byte 2: flag 0x10, bytes 1 / 0: spread x / y (/ 255) */
} Rec150130B4;

/* spawn block (sp+0xDC, 0x58 bytes) and emitter block (sp+0x134): N64 layout as in game_3E890.c. The emitter
 * size passed is 0x60 / 0x70 / 0x78; on N64 only 0x5C bytes lie in this frame (the rest is the caller's stack). */
typedef struct {
    struct {
        u8 kind;            /* 0x00 */
        u8 u1;              /* 0x01 */
        u16 flags;          /* 0x02 */
        u16 life;           /* 0x04 */
        u8 pad6[2];
        s32 u8_;            /* 0x08 */
        s32 uC;             /* 0x0C */
        u8 rgba[4];         /* 0x10 */
        f32 size[2];        /* 0x14 */
        f32 pos0[3];        /* 0x1C */
        f32 pos1[3];        /* 0x28 */
        f32 scale[3];       /* 0x34 */
        s32 u40;            /* 0x40 */
        u8 u44[4];          /* 0x44 */
        s32 sound;          /* 0x48 */
        u8 pad4C[0xC];
    } spawn;
    struct {
        f32 range[4];       /* 0x00 */
        f32 u10;            /* 0x10 */
        f32 u14;            /* 0x14 */
        f32 spreadX;        /* 0x18 */
        f32 spreadY;        /* 0x1C */
        f32 u20;            /* 0x20 */
        u8 pad24[0x24];
        f32 u48;            /* 0x48 */
        u8 pad4C[8];
        u8 u54[5];          /* 0x54 */
        u8 pad59[0x1F];
    } emit;
} Blk150130B4;

/*
 * record_particle_emitter_start: P230: start handler of a particle-emitter record. Marks the record started
 * (+0x16 |= 4) and fills a spawn block: position from the record, the "to" point = position + (0, 0, -500)
 * rotated by the record's angles (mtxf_rotate_xyz_deg / mtxf_transform_point), kind D_8009693C[colour >> 24], flags
 * D_80096950[colour >> 24] + 3, life 300, colour from +0x18, scale 1, and an optional sound
 * (opts top byte: collision_select_area(0); zone_tree_find_leaf(x, z)). The emitter block gets the ranges +6 / +8, the spreads
 * (opts bytes 1 / 0) / 255 and a per-type sub kind (+0x58); type 8 and 13..18 emitters also get a tail at +0x170
 * (types 13..18: the target object world_record_find(D_80083228[type - 13]) and its position; none -> no emitter).
 */
/* was func_150130B4 */
s32 record_particle_emitter_start(Rec150130B4 *rec) {
    f32 m[4][4];
    Blk150130B4 b;
    union {                 /* copied to the new emitter's +0x170 */
        f32 t8[4];          /* type 8 */
        struct {            /* types 13..18 */
            f32 a;
            f32 b;
            u8 *obj;
            f32 pos[3];
        } t13;
    } tail;
    u8 *e;
    s32 type;
    s32 flags;
    u8 snd;
    u32 idx;

    rec->flags16 |= 4;
    snd = rec->opts >> 24;
    type = rec->type;
    b.spawn.pos0[0] = rec->x;
    b.spawn.pos0[1] = rec->y;
    b.spawn.pos0[2] = rec->z;
    mtxf_rotate_xyz_deg(m, rec->angX, rec->angY, 0.0f);
    mtxf_transform_point(m, 0.0f, 0.0f, -500.0f, &b.spawn.pos1[0], &b.spawn.pos1[1], &b.spawn.pos1[2]);
    b.spawn.pos1[0] += b.spawn.pos0[0];
    b.spawn.pos1[1] += b.spawn.pos0[1];
    b.spawn.pos1[2] += b.spawn.pos0[2];

    b.emit.range[1] = rec->rangeX;
    b.emit.range[0] = b.emit.range[1];
    b.emit.range[3] = rec->rangeY;
    b.emit.range[2] = b.emit.range[3];
    b.emit.spreadX = ((rec->opts >> 8) & 0xFF) * D_80096984;
    b.emit.spreadY = (rec->opts & 0xFF) * D_80096984;
    b.emit.u10 = D_80096988;
    b.emit.u14 = D_8009698C;
    b.emit.u20 = D_80096990;
    b.emit.u48 = 1.0f;
    b.emit.u54[0] = 0;
    b.emit.u54[1] = 0;
    b.emit.u54[2] = 0;
    b.emit.u54[3] = 0;

    idx = rec->colour >> 24;
    b.spawn.kind = D_8009693C[idx];
    b.spawn.u1 = 3;
    b.spawn.flags = D_80096950[idx] + 3;
    b.spawn.life = 300;
    b.spawn.u8_ = 0;
    b.spawn.uC = 0;
    b.spawn.rgba[0] = rec->colour;
    b.spawn.rgba[1] = rec->colour >> 8;
    b.spawn.rgba[2] = rec->colour >> 16;
    b.spawn.rgba[3] = 0xFF;
    b.spawn.size[0] = 0.0f;
    b.spawn.size[1] = 0.0f;
    b.spawn.scale[0] = 1.0f;
    b.spawn.scale[1] = 1.0f;
    b.spawn.scale[2] = 1.0f;
    b.spawn.u44[1] = 0xFF;
    b.spawn.u44[0] = 0xFF;
    b.spawn.u44[2] = 0;
    b.spawn.u44[3] = 6;

    if (snd != 0) {
        collision_select_area(0);
        b.spawn.sound = zone_tree_find_leaf((s32) b.spawn.pos0[0], (s32) b.spawn.pos0[2]);
    } else {
        b.spawn.sound = 0;
    }
    b.emit.u54[4] = 0;
    flags = (snd != 0) ? 0x01002006 : 0x2006;
    if ((rec->opts >> 16) & 0xFF) {
        flags |= 0x10;
    }
    flags |= 0x40000 | 0x80000 | 0x10000 | 0x400000;
    b.spawn.u40 = flags;

    switch (type) {
        case 1:
        case 2:
        case 3:
        case 4:
            b.emit.u54[4] = D_80096960[type];
            particle_emitter_spawn(&b.emit, 0x60, &b.spawn, 0, 0, 0, 0, -1, 0xFF, 1);
            break;
        case 5:
        case 6:
        case 7:
            b.emit.u54[4] = D_80096930[type - 5]; /* the asm indexes a stack copy of the table */
            particle_emitter_spawn(&b.emit, 0x60, &b.spawn, 0, 0, 0, 0, -1, 0xFF, 1);
            break;
        case 8:
            tail.t8[0] = D_800969E0;
            tail.t8[1] = D_800969E4;
            tail.t8[2] = 0.0f;
            tail.t8[3] = D_800969E8;
            e = particle_emitter_spawn(&b.emit, 0x70, &b.spawn, 0, 0x29, 0, 0, -1, 0xFF, 1);
            if (e != NULL) {
                memcpy(e + 0x170, tail.t8, 0x10);
            }
            break;
        case 9:
        case 10:
        case 11:
        case 12:
            b.emit.u54[4] = D_80096950[type];
            particle_emitter_spawn(&b.emit, 0x60, &b.spawn, 0, 0, 0, 0, -1, 0xFF, 1);
            break;
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
            tail.t13.obj = world_record_find(D_80083228[type - 13]); /* the asm indexes a stack copy */
            if (tail.t13.obj == NULL) {
                break;
            }
            tail.t13.a = -80.0f;
            tail.t13.b = 0.0125f;
            tail.t13.pos[0] = *(s16 *) (tail.t13.obj + 0x10);
            tail.t13.pos[1] = *(s16 *) (tail.t13.obj + 0x12);
            tail.t13.pos[2] = *(s16 *) (tail.t13.obj + 0x14);
            b.emit.u54[4] = 0;
            e = particle_emitter_spawn(&b.emit, 0x78, &b.spawn, 0x25, 0, 0, 0, -1, 0xFF, 1);
            if (e != NULL) {
                memcpy(e + 0x170, &tail.t13, 0x18);
            }
            break;
        case 19:
            b.emit.u54[4] = 0x11;
            b.spawn.u40 = flags & ~2;
            particle_emitter_spawn(&b.emit, 0x60, &b.spawn, 0, 0, 0, 0, -1, 0xFF, 1);
            break;
        default:
            particle_emitter_spawn(&b.emit, 0x60, &b.spawn, 0, 0, 0, 0, -1, 0xFF, 1);
            break;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/record_particle_emitter_start.s")
#endif

// record_start_dispatch: runs the record's start handler D_80082EA0[rec->unk17] (EU 0x80083230) on the record.
/* was func_1501370C */
s32 record_start_dispatch(struct16 *arg0) {
    u8 idx = arg0->unk17;
#ifdef NON_MATCHING
    /* P164 (P161 null+0x14 writer): the handlers take the record (asm 150136BC keeps a0 = arg0 at the jalr) */
    void (*func)(struct16 *) = (void (*)(struct16 *)) D_80082EA0[idx];

    if (func != NULL) {
        func(arg0);
    }
#else
    void (*func)(void) = D_80082EA0[idx];

    if (func != NULL) {
        func();
    }
#endif
    return 1;
}

/* was func_1501374C */
s32 record_start_15d088(struct16 *arg0) {
    arg0->unk16 |= 4;
    fx_source_emitter_spawn(arg0);
    return 1;
}

#ifdef NON_MATCHING
extern f32 D_800969F0;
extern f32 D_800969F4;

/*
 * P80: effect spawn from a record (s16 x, y, z at +0 / +2 / +4, s16 +6, s16 radius +8, f32 angles +0xC / +0x10):
 * nothing for radius 0. Else an effect (effect_node_create type 0x19) gets a 0x34-byte block: position, the unit
 * direction (0, 2r, 0) rotated by the angles (mtxf_rotate_xyz_deg / mtxf_transform_point) times 1 / 2r, 2r, (f32) +6, the two
 * angles, 0 and D_800969F0 / D_800969F4; then a sound / particle (sfx_emitter_start 0x67C) at (x, y + r, z).
 */
/* was func_15013778 */
s32 effect_spawn_record(s16 *rec) {
    f32 m[4][4];
    struct {
        f32 pos[3];
        f32 dir[3];
        f32 size;
        f32 height;
        f32 angX;
        f32 angY;
        f32 zero;
        f32 k1;
        f32 k2;
    } blk;
    f32 inv;
    u8 *e;
    s32 r = rec[4];

    if (r == 0) {
        return 1;
    }
    blk.size = (f32) r + (f32) r;
    inv = 1.0f / blk.size;
    blk.height = rec[3];
    blk.angX = *(f32 *) (rec + 6);
    blk.angY = *(f32 *) (rec + 8);
    blk.zero = 0.0f;
    blk.k1 = D_800969F0;
    blk.k2 = D_800969F4;
    blk.pos[0] = rec[0];
    blk.pos[1] = rec[1];
    blk.pos[2] = rec[2];
    mtxf_rotate_xyz_deg(m, *(f32 *) (rec + 6), *(f32 *) (rec + 8), 0.0f);
    mtxf_transform_point(m, 0.0f, blk.size, 0.0f, &blk.dir[0], &blk.dir[1], &blk.dir[2]);
    blk.dir[0] *= inv;
    blk.dir[1] *= inv;
    blk.dir[2] *= inv;
    e = (u8 *) effect_node_create(0x12C, -1, 0x19, -1, 0, 0x17, (struct37 *) 0x34, 0xFF, 0);
    if (e != NULL) {
        memcpy(e + 0x28, &blk, 0x34);
    }
    r = rec[4];
    sfx_emitter_start(0x67C, rec[0], rec[1] + r, rec[2], 0x2EE0, r * 2, r / 2, (s32) sfx_cb_keep_until_silent, NULL, 0, 8, 0);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/effect_spawn_record.s")
#endif

/* was func_1501396C */
s32 record_dispatch_82ecc(struct16 *arg0) {
    u8 idx = arg0->unk17;
    /* P76: the handlers take the record (a0 still holds arg0 at the jalr; record_emitter_start writes arg0->unk16) */
    void (*func)(struct16 *) = (void (*)(struct16 *)) D_80082ECC[idx];

    if (func != NULL) {
        func(arg0);
    }
    return 1;
}

// another struct
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    s16 unk14;
    s16 unk16;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    u8 unk30;
    u8 unk31;
    u8 unk32;
    u8 unk33;
    u8 unk34;
    u8 pad35[3];
} Ent150139AC;
extern Ent150139AC D_80096350[];
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s32 unkC;
    s32 unk10;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
    s32 unk18;
} Obj150139AC;
extern f32 D_800969F8;
extern f32 D_800969FC;

/* was func_150139AC */
s32 record_ambient_effect_start(Obj150139AC *arg0) {
    struct {
        Obj150139AC *unk0;
        f32 unk4;
        f32 unk8;
        f32 unkC;
        f32 unk10;
        f32 unk14;
        f32 unk18;
        f32 unk1C;
        f32 unk20;
        s16 unk24;
        s16 unk26;
        f32 unk28;
        f32 unk2C;
        f32 unk30;
        f32 unk34;
        f32 unk38;
        f32 unk3C;
        u8 unk40;
        u8 unk41;
        u8 unk42;
        u8 pad43;
        s16 unk44;
        u8 pad46[2];
        f32 unk48;
        u8 pad4C[0x14];
        s32 unk60;
        u8 unk64;
        u8 unk65;
        u8 pad66[2];
        s32 unk68;
        s32 unk6C;
    } tmp;
    Ent150139AC *e;
    s32 idx;

    arg0->unk16 |= 4;
    idx = arg0->unk18;
    tmp.unk0 = arg0;
    tmp.unkC = 0.0f;
    switch (arg0->unk15 & 3) {
    case 2:
        tmp.unk4 = arg0->unk6 * arg0->unkA * 4.0f;
        tmp.unk10 = arg0->unk2 + arg0->unk8;
        break;
    case 0:
    case 1:
        tmp.unk4 = arg0->unk6 * arg0->unk6 * D_800969F8;
        tmp.unk10 = arg0->unk2 + arg0->unk8;
        break;
    default:
        tmp.unk4 = 1.0f;
        tmp.unk10 = 1000.0f;
        break;
    }
    e = &D_80096350[idx];
    tmp.unk14 = e->unk4;
    tmp.unk18 = e->unk8;
    tmp.unk1C = e->unkC;
    tmp.unk20 = e->unk10;
    tmp.unk24 = e->unk14;
    tmp.unk26 = e->unk16;
    tmp.unk28 = e->unk18;
    tmp.unk2C = e->unk1C;
    tmp.unk30 = e->unk20;
    tmp.unk34 = e->unk24;
    tmp.unk38 = e->unk28;
    tmp.unk3C = e->unk2C;
    tmp.unk8 = e->unk0;
    tmp.unk40 = e->unk30;
    tmp.unk41 = e->unk31;
    tmp.unk42 = e->unk32;
    tmp.unk48 = D_800969FC;
    tmp.unk60 = 0;
    tmp.unk64 = 0;
    tmp.unk65 = 0;
    tmp.unk68 = 0;
    if (e->unk34) {
        collision_select_area(0);
        tmp.unk6C = zone_tree_find_leaf(arg0->unk0, arg0->unk4);
    } else {
        tmp.unk6C = 0;
    }
    if (e->unk33) {
        tmp.unk44 = sfx_emitter_start(0x4D, arg0->unk0, arg0->unk2, arg0->unk4, 0x5DC0, 0x3E8, 0x12C, 0, 0, 0, 0, 0);
    } else {
        tmp.unk44 = 0;
    }
    e = (Ent150139AC *)effect_node_create_nodraw(300, -1, 6, 0, 10, 0x70, 0xFF, 0);
    if (e != NULL) {
        memcpy((u8 *)e + 0x28, &tmp, sizeof(tmp));
    }
    return 1;
}

extern void (*D_800832B8[])(struct134 *, f32);

/* was func_15013C38 */
s32 record_scripted_dispatch(struct134 *arg0) {
    s32 idx = arg0->unk18;
    void (*func)(struct134 *, f32);

    arg0->unk16 |= 4;
    if ((((u8 *)D_800D2E4C)[0x11] & 4) && (D_800BE9F0 == 19)) {
        return 1;
    }
    if ((D_800C35EA == 1) && ((D_800C3A08 == 15) || (D_800C3A08 == 16) || (D_800C3A08 == 17))) {
        return 1;
    }
    if (idx >= 6) {
        return 1;
    }
    func = D_800832B8[idx];
    if (func != NULL) {
        f32 val = (u32)arg0->unk1C * D_80096A00;
        func(arg0, val);
    }
    return 1;
}

/* was func_15013D38 */
s32 record_emitter_start(struct134 *arg0) {
    f32 pos[3];
    s32 temp_v0;

    arg0->unk16 |= 4;
    pos[0] = arg0->unk0;
    pos[1] = (s16)arg0->unk2;
    pos[2] = arg0->unk4;
    temp_v0 = arg0->unk18;
#ifdef NON_MATCHING
    life_pickup_spawn(pos, *(f32 *)&arg0->unk10, temp_v0 ? temp_v0 : 1, ((u8 *)arg0)[0x1F], 1, 255, 1);
#else
    life_pickup_spawn(pos, arg0->unk10, temp_v0 ? temp_v0 : 1, ((u8 *)arg0)[0x1F], 1, 255, 1);
#endif
    return 1;
}

s32 spark_spawn_from_desc(f32 *, s32, s32, s32, s32, s32);
extern f32 D_80096A04;
extern f32 D_80096A08;
extern f32 D_80096A0C;
extern f32 D_80096A10;
extern f32 D_80096A14;
extern f32 D_80096A18;
extern f32 D_80096A1C;
extern f32 D_80096A20;
extern f32 D_80096A24;
extern f32 D_80096A28;

/* was func_15013DE8 */
s32 record_particle_burst_start(u8 *arg0) {
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
    f32 b;
    f32 c;

    arg0[0x16] |= 4;
    b = *(s16 *)(arg0 + 6) * D_80096A04;
    c = *(s16 *)(arg0 + 8) * D_80096A08;
    sp.u50 = 0x6231; sp.u52 = 0x1A4D;
    sp.u56 = 0;
    sp.u57 = 0;
    sp.u58 = 0;
    sp.u59 = 0xFF;
    sp.u5A = 0;
    sp.u5D = 0xFF;
    sp.u60 = 0;
    sp.u5E = 0;
    sp.u5F = 0;
    sp.u64 = 0;
    sp.u6C = D_80096A0C;
    sp.u30 = *(s16 *)(arg0 + 0);
    sp.u34 = *(s16 *)(arg0 + 2);
    sp.u38 = *(s16 *)(arg0 + 4);
    sp.u54 = 0x12C;
    sp.u68 = 0.0f;
    sp.u70 = D_80096A10;
    sp.u74 = D_80096A14;
    sp.u5C = (random_int() % 56U) + 0xC8;
    sp.u3C = D_80096A18 * b;
    sp.u44 = D_80096A1C * b;
    sp.u40 = D_80096A20 * c; sp.u48 = D_80096A24 * c; sp.u4C = D_80096A28 * c;

    spark_spawn_from_desc(&sp.u30, 0xA, 1, (u8)((*(s32 *)(arg0 + 0x18) != 0) ? 2 : 1), 0xFF, 1);
    return 1;
}


/* was func_15013F9C */
s32 record_start_1cd2c0(s32 arg0) {
    spout_ctrl_spawn(arg0, 0xFF, 1);
    return 1;
}

/* was func_15013FC4 */
s32 record_dispatch_82f40(struct133 *arg0) {
    s32 idx = ((u8 *)arg0)[0x1B];
    void (*func)(void) = D_80082F40[idx];

    if (func != NULL) {
        func();
    }
    return 1;
}

/* was func_15014004 */
s32 record_register_e0900(struct134 *arg0) {
    s32 temp_v1 = arg0->unk1C;
    if (temp_v1 < 0) {
        return 1;
    }
    if (temp_v1 >= 6) {
        return 1;
    }
    D_800E0900[temp_v1] = arg0;
    return 1;
}

/* was func_15014040 */
s32 record_register_d9a20(struct134 *arg0) {
    s32 temp_v0 = arg0->unk18;
    arg0->unk16 |= 4;
    if (temp_v0 == 0) {
        D_800D9A20 = arg0;
    } else if (temp_v0 == 1) {
        D_800D9A24 = arg0;
    }
    return 1;
}

/* was func_1501407C */
s32 record_clear_d987c(s32 arg0) {
    D_800D987C = (u8)0;
    return 1;
}

/* was func_15014094 */
s32 record_effect33_start(struct134 *arg0) {
    struct {
        struct134 *unk0;
        f32 unk4;
        f32 unk8;
        s32 unkC;
        u8  pad10[0x1C];
        s8  unk2C;
        u8  pad2D[0x7];
    } tmp;
    struct37 *temp_v0;

    arg0->unk16 |= 4;
    tmp.unk0 = arg0;
    tmp.unk4 = spawn_region_area(arg0);
    tmp.unk8 = 0.0f;
    collision_select_area(0);
    tmp.unkC = zone_tree_find_leaf(arg0->unk0, arg0->unk4);
    tmp.unk2C = 0;
    temp_v0 = effect_node_create(300, -1, 33, -1, 0, 0, 52, 255, 1);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk28, &tmp, sizeof(tmp));
    }
}

/* was func_15014144 */
s32 record_kind_effect_start(struct134 *arg0) {
    s32 flags = arg0->unk18;
    s32 f8 = (flags & 8) ? 8 : 0;
    s32 f4 = (flags & 4) ? 4 : 0;
    s32 f2 = (flags & 2) ? 0 : 2;
    s32 f1 = (flags & 1) ? 1 : 0;
    s32 f10 = (flags & 0x10) ? 0x10 : 0;

    kind_effect_spawn(f10 | f1 | f2 | f4 | f8, ((u8 *)arg0)[0x1F], arg0, 0, D_80096A2C, 100.0f, -1, 255, 1);
    return 1;
}

/* was func_15014220 */
s32 record_effect38_start(struct134 *arg0) {
    struct {
        f32 unk0;
        struct134 *unk4;
        s8 unk8;
    } tmp;
    struct37 *temp_v0;

    arg0->unk16 |= 4;
    tmp.unk8 = 1;
    tmp.unk4 = arg0;
    tmp.unk0 = 0.0f;
    temp_v0 = effect_node_create(300, -1, 38, -1, 0, 36, 12, 255, 0);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk28, &tmp, 12);
    }
    return 1;
}
/* was func_150142AC */
s32 record_register_d9aa0(struct134 *arg0) {
    s32 idx = ((u8 *)arg0)[0x1B];
    arg0->unk16 |= 4;
    if (idx < 0 || idx >= 3) {
        return 1;
    }
    D_800D9AA0[idx] = arg0;
    return 1;
}

extern f32 D_80096A30;
extern f32 D_80096A34;

/* was func_150142EC */
s32 record_effect29_start(struct134 *arg0) {
    struct {
        struct134 *unk0;
        f32 unk4;
        f32 unk8;
        f32 unkC;
        f32 unk10;
        f32 unk14;
    } tmp;
    struct260 *temp_v0;
    f32 a;
    f32 b;
    f32 c;
    f32 d;
    f32 r;

    arg0->unk16 |= 4;
    if (D_80082FA0 >= 2) {
        return 1;
    }
    if ((((u8 *)D_800D2E4C)[0x11] & 4) && (D_800BE9F0 == 19)) {
        return 1;
    }
    a = ((u32)arg0->unk1C & 0xFFFF) * D_80096A30;
    b = (((u32)arg0->unk1C >> 16) & 0xFFFF) * D_80096A30;
    c = ((u32)arg0->unk20 & 0xFFFF) * D_80096A30;
    d = (((u32)arg0->unk20 >> 16) & 0xFFFF) * D_80096A30;
    r = spawn_region_volume((struct_eu_15144598 *)arg0);
    tmp.unk0 = arg0;
    tmp.unk4 = a * r * D_80096A34;
    tmp.unk8 = b * r * D_80096A34;
    tmp.unkC = c;
    tmp.unk10 = d;
    tmp.unk14 = 0.0f;
    temp_v0 = effect_node_create(300, -1, 0x29, -1, 0, 0, 0x18, 0xFF, 0);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x18);
    }
    return 1;
}
#ifdef NON_MATCHING
void vec3_to_yaw_pitch_deg(void *, f32 *, f32 *);
/* the 0x38-byte parameter block screen_effect_start copies to the effect at +0x28 */
typedef struct {
    u8 *rec;          /* 0x00 */
    s32 count;        /* 0x04 min + rand % (range + 1) */
    s32 min;          /* 0x08 */
    s32 range;        /* 0x0C */
    s16 b2;           /* 0x10 */
    s16 b3;           /* 0x12 */
    f32 scale0;       /* 0x14 */
    f32 scale1;       /* 0x18 */
    f32 screen_x;     /* 0x1C */
    f32 screen_y;     /* 0x20 */
    f32 angle;        /* 0x24 */
    f32 spin;         /* 0x28 */
    f32 frames;       /* 0x2C */
    f32 inv_frames;   /* 0x30 */
    f32 step;         /* 0x34 */
} Effect150144B8;
// screen_effect_start: P259: start handler of a level record `rec` (s16 +6 / +8, f32 +0xC / +0x10, flags +0x16,
// packed bytes +0x18 / +0x1C): sets flag 4; in single player (D_80082FA0 < 2) projects the point 100 above
// (+0xC, 0, +0x10) to the screen (mtxf_rotate_xyz_deg / mtxf_transform_point / vec3_to_yaw_pitch_deg, scaled by pi/180) and spawns effect
// 300 / 0x2A (effect_node_create) with a parameter block from the packed bytes: count min + rand % (range + 1), two s16,
// two scales / 64, angle math_atan2f(+6, +8), spin byte / 256 * pi/4, a frame count with its inverse and
// +8 / frames. Always returns 1.
/* was func_150144B8 */
s32 screen_effect_start(u8 *rec) {
    f32 mtx[4][4];
    f32 pos[3];
    Effect150144B8 e;
    struct260 *fx;
    u32 lo;
    u32 hi;

    rec[0x16] |= 4;
    if (D_80082FA0 >= 2) {
        return 1;
    }
    mtxf_rotate_xyz_deg(mtx, *(f32 *) (rec + 0xC), *(f32 *) (rec + 0x10), 0.0f);
    mtxf_transform_point(mtx, 0.0f, 100.0f, 0.0f, &pos[0], &pos[1], &pos[2]);
    vec3_to_yaw_pitch_deg(pos, &e.screen_x, &e.screen_y);
    e.screen_x *= 0.017453292f;
    e.screen_y *= 0.017453292f;
    e.min = *(u32 *) (rec + 0x18) & 0xFF;
    e.range = (*(u32 *) (rec + 0x18) >> 8) & 0xFF;
    lo = e.min;
    hi = e.range;
    e.rec = rec;
    e.count = (u32) random_int() % (hi + 1) + lo;
    e.b2 = (*(u32 *) (rec + 0x18) >> 16) & 0xFF;
    e.b3 = (*(u32 *) (rec + 0x18) >> 24) & 0xFF;
    e.scale0 = (f32) (*(u32 *) (rec + 0x1C) & 0xFF) * 0.015625f;
    e.scale1 = (f32) ((*(u32 *) (rec + 0x1C) >> 8) & 0xFF) * 0.015625f;
    e.frames = (f32) ((*(u32 *) (rec + 0x1C) >> 24) & 0xFF);
    e.inv_frames = 1.0f / e.frames;
    e.step = (f32) *(s16 *) (rec + 8) * e.inv_frames;
    e.angle = math_atan2f((f32) *(s16 *) (rec + 6), (f32) *(s16 *) (rec + 8));
    e.spin = (f32) ((*(u32 *) (rec + 0x1C) >> 16) & 0xFF) * 0.00390625f * 0.7853982f;
    fx = effect_node_create(300, -1, 0x2A, -1, 0, 0, (struct37 *) sizeof(e), 0xFF, 0);
    if (fx != NULL) {
        memcpy((u8 *) fx + 0x28, &e, sizeof(e));
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/screen_effect_start.s")
#endif
#ifdef NON_MATCHING
/* the level record record_zone_box_start reads */
typedef struct {
    s16 x, y, z;        /* 0x00 */
    s16 halfX;          /* 0x06 */
    s16 height;         /* 0x08 */
    s16 halfZ;          /* 0x0A */
    f32 angX;           /* 0x0C */
    f32 angY;           /* 0x10 */
    u8 pad14[2];
    u8 flags16;         /* 0x16 */
    u8 pad17;
    u32 colour;         /* 0x18: bytes 0..3 copied little end first */
    u32 params;         /* 0x1C: four 0..255 parameters, low byte first */
} Rec1501474C;
extern f32 D_80096A40;
extern f32 D_80096A44;
f32 sinf(f32);
f32 cosf(f32);
#endif

#ifdef NON_MATCHING
// record_zone_box_start: start handler (s32, returns 1) of a box-zone level record: marks it started (+0x16 |= 4),
// rotates the rectangle (+-halfX, +-halfZ) by the record's yaw (sinf(angY * D_80096A40), cosf(angY * D_80096A44))
// around (x, z) and hands a 0x40-byte block to a new effect_node_create object (type 0x12C, 0x2C; +0x28): two opposite
// corners, the two edge vectors from them, the top (y + height) and bottom y, parameters 0 / 1 as (p / 256) * 0.5,
// 0, parameters 2 / 3 as (p / 256) * 250, and the colour bytes in reverse order.
/* was func_1501474C */
s32 record_zone_box_start(Rec1501474C *rec) {
    struct {
        f32 c1[2];          /* 0x00 */
        f32 c2[2];          /* 0x08 */
        f32 e0[2];          /* 0x10: c0 - c1 */
        f32 e1[2];          /* 0x18: c3 - c2 */
        f32 top;            /* 0x20 */
        f32 bottom;         /* 0x24 */
        f32 p0;             /* 0x28 */
        f32 p1;             /* 0x2C */
        f32 zero;           /* 0x30 */
        f32 p2;             /* 0x34 */
        f32 p3;             /* 0x38 */
        u8 colour[4];       /* 0x3C */
    } blk;
    f32 c[4][2];
    f32 cx;
    f32 cz;
    f32 sn;
    f32 cs;
    u8 *e;

    rec->flags16 |= 4;
    cx = rec->x;
    cz = rec->z;
    sn = sinf(rec->angY * D_80096A40);
    cs = cosf(rec->angY * D_80096A44);
    c[0][0] = rec->halfX * cs + cx + rec->halfZ * sn;
    c[0][1] = rec->halfZ * cs + cz - rec->halfX * sn;
    c[1][0] = rec->halfX * cs + cx + (f32) -rec->halfZ * sn;
    c[1][1] = (f32) -rec->halfZ * cs + cz - rec->halfX * sn;
    c[2][0] = (f32) -rec->halfX * cs + cx + (f32) -rec->halfZ * sn;
    c[2][1] = (f32) -rec->halfZ * cs + cz - (f32) -rec->halfX * sn;
    c[3][0] = (f32) -rec->halfX * cs + cx + rec->halfZ * sn;
    c[3][1] = rec->halfZ * cs + cz - (f32) -rec->halfX * sn;
    blk.c1[0] = c[1][0];
    blk.c1[1] = c[1][1];
    blk.c2[0] = c[2][0];
    blk.c2[1] = c[2][1];
    blk.e0[0] = c[0][0] - c[1][0];
    blk.e0[1] = c[0][1] - c[1][1];
    blk.e1[0] = c[3][0] - c[2][0];
    blk.e1[1] = c[3][1] - c[2][1];
    blk.top = rec->y + rec->height;
    blk.bottom = rec->y;
    blk.p0 = (rec->params & 0xFF) * 0.00390625f * 0.5f;
    blk.p1 = ((rec->params >> 8) & 0xFF) * 0.00390625f * 0.5f;
    blk.zero = 0.0f;
    blk.p2 = ((rec->params >> 16) & 0xFF) * 0.00390625f * 250.0f;
    blk.p3 = ((rec->params >> 24) & 0xFF) * 0.00390625f * 250.0f;
    blk.colour[0] = rec->colour;
    blk.colour[1] = rec->colour >> 8;
    blk.colour[2] = rec->colour >> 16;
    blk.colour[3] = rec->colour >> 24;
    e = (u8 *) effect_node_create(0x12C, -1, 0x2C, -1, 0, 0, (struct37 *) 0x40, 0xFF, 0);
    if (e != NULL) {
        memcpy(e + 0x28, &blk, 0x40);
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/record_zone_box_start.s")
#endif
#ifdef NON_MATCHING
/* the level record record_light_ring_start reads */
typedef struct {
    s16 x, y, z;        /* 0x00 */
    u8 pad06[0x10];
    u8 flags16;         /* 0x16 */
    u8 pad17;
    u32 sizeXY;         /* 0x18: two u16 sizes, low half first */
    u32 sizeZW;         /* 0x1C: two more u16 values */
} Rec15014B60;
extern f32 D_80096A48;
extern f32 D_80096A4C;
extern f32 D_80096A50;
extern f32 D_80096A54;
extern f32 D_80096A58;
extern f32 D_80096A5C;
extern f32 D_80096A60;
extern u8 D_800A0D08[]; /* 6 rgb triples */
#endif

#ifdef NON_MATCHING
// record_light_ring_start: start handler (s32, returns 1) of a level record: marks it started (+0x16 |= 4) and
// builds a 0x48-byte block for a new effect_node_create object (type 0x12C, 0x2E, kind 0x29; +0x28): the position, three
// random angles ((u16) (random_int() * osGetCount()) scaled by D_80096A48 / 4C / 58 and 360), three sizes from the
// record's u16 halves (* D_80096A50 * D_80096A54), six lights (light_create_with_ctrl at the record position, colour
// D_800A0D08[i], red in level 0x40), a fourth value (* D_80096A5C * D_80096A60), the record and a 1 byte. When
// no object is free the lights are freed again (node_destroy).
/* was func_15014B60 */
s32 record_light_ring_start(Rec15014B60 *rec) {
    struct {
        f32 pos[3];         /* 0x00 */
        f32 ang[3];         /* 0x0C */
        f32 size[3];        /* 0x18 */
        void *light[6];     /* 0x24 */
        f32 u3C;            /* 0x3C */
        Rec15014B60 *rec;   /* 0x40 */
        u8 u44;             /* 0x44 */
    } blk;
    struct {
        u8 u0;
        s8 u1;
        s16 life;
        u8 u4;
    } req;
    s32 ipos[3];
    u32 t;
    s32 i;
    s32 r;
    s32 g;
    s32 b;
    u8 *e;

    rec->flags16 |= 4;
    blk.u44 = 1;
    blk.rec = rec;
    blk.pos[0] = rec->x;
    blk.pos[1] = rec->y;
    blk.pos[2] = rec->z;
    t = osGetCount();
    blk.ang[0] = (u16) (random_int() * t) * D_80096A48 * 360.0f;
    t = osGetCount();
    blk.ang[1] = (u16) (random_int() * t) * D_80096A4C * 360.0f;
    t = osGetCount();
    blk.ang[2] = (u16) (random_int() * t) * D_80096A58 * 360.0f;
    blk.size[0] = (rec->sizeXY & 0xFFFF) * D_80096A50 * D_80096A54;
    blk.size[1] = ((rec->sizeXY >> 16) & 0xFFFF) * D_80096A50 * D_80096A54;
    blk.size[2] = (rec->sizeZW & 0xFFFF) * D_80096A50 * D_80096A54;
    blk.u3C = ((rec->sizeZW >> 16) & 0xFFFF) * D_80096A5C * D_80096A60;
    ipos[0] = rec->x;
    ipos[1] = rec->y;
    ipos[2] = rec->z;
    for (i = 0; i < 6; i++) {
        req.u0 = 2;
        req.u1 = -1;
        req.life = 300;
        req.u4 = 0;
        if (D_800BE9F0 == 0x40) {
            r = 0xFF;
            g = 0;
            b = 0;
        } else {
            r = D_800A0D08[i * 3];
            g = D_800A0D08[i * 3 + 1];
            b = D_800A0D08[i * 3 + 2];
        }
        blk.light[i] = light_create_with_ctrl((Header *) &req, (Header2 *) ipos, 5, r, g, b, 0xFF, 0, 0, 0xFF, 0);
    }
    e = (u8 *) effect_node_create(0x12C, -1, 0x2E, -1, 0, 0x29, (struct37 *) 0x48, 0xFF, 0);
    if (e != NULL) {
        memcpy(e + 0x28, &blk, 0x48);
        return 1;
    }
    for (i = 0; i < 6; i++) {
        if (blk.light[i] != NULL) {
            node_destroy((struct102 *) blk.light[i]);
        }
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/record_light_ring_start.s")
#endif
/* was func_15014F6C */
s32 record_effect49_start(struct134 *arg0) {
    struct {
        struct134 *unk0;
        u32 unk4;
        u32 unk8;
        u32 unkC;
        u8  unk10[0x30];
        f32 unk40;
        f32 unk44;
        f32 unk48;
        u8  pad4C[0x4];
        s8  unk50;
        s8  unk51;
    } tmp;
    struct37 *temp_v0;
    s8 flag = 0;

    arg0->unk16 |= 4;
    tmp.unk51 = arg0->unk20;
    flag = (arg0->unk1C & 1) ? 1 : 0;
    tmp.unk50 = flag;
    tmp.unk0 = arg0;
    tmp.unk4 = arg0->unk18 & 0xFFFF;
    tmp.unk8 = ((u32)arg0->unk18 >> 16) & 0xFFFF;
    tmp.unkC = (random_int() % (tmp.unk8 + 1)) + tmp.unk4;
    mtxf_rotate_xyz_deg((void *)tmp.unk10, *(f32 *)&arg0->unkC, *(f32 *)&arg0->unk10, 0.0f);
    tmp.unk40 = arg0->unk0;
    tmp.unk44 = (s16)arg0->unk2;
    tmp.unk48 = arg0->unk4;
    temp_v0 = effect_node_create(300, -1, 49, -1, 0, 42, 84, 255, 0);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk28, &tmp, sizeof(tmp));
    }
    return 1;
}

/* was func_150150A4 */
s32 record_light_list_add(s32 arg0) {   /* P76: a0 passes through to spawn_region_entry_alloc */
    struct17 *temp_v0 = spawn_region_entry_alloc(arg0);
    if (temp_v0 == NULL) {
        return 1;
    }

    spawn_region_list_push(&D_800DCDC4, temp_v0);
    D_800DCD90 += temp_v0->unk8;
    return 1;
}

/* was func_15015104 */
s32 record_effect44_start(struct134 *arg0) {
    struct {
        struct134 *unk0;
        s8  unk4;
        s32 unk8;
        s8  unkC;
        s32 unk10;
    } tmp;
    struct37 *temp_v0;
    s32 f1;
    s32 f2;

    *(u8 *)&arg0->unk14 = 1;
    tmp.unk0 = arg0;
    tmp.unk4 = arg0->unk1C;
    collision_select_area(0);
    tmp.unk8 = zone_tree_find_leaf(arg0->unk0, arg0->unk4);
    f1 = arg0->unk20 ? 1 : 0;
    f2 = arg0->unk20 ? 2 : 0;
    tmp.unkC = f2 | f1;
    tmp.unk10 = 0;
    temp_v0 = effect_node_create(300, -1, -1, -1, 0, 44, 20, 255, 0);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk28, &tmp, sizeof(tmp));
    }
    return 1;
}
/* was func_150151D4 */
s32 record_effect60_start(struct134 *arg0) {
    struct {
        struct134 *unk0;
        f32 unk4;
        s16 unk8;
        f32 unkC;
        f32 unk10;
        f32 unk14;
        f32 unk18;
        f32 unk1C;
        f32 unk20;
        u8  pad24[0x14];
        s32 unk38;
        s8  unk3C;
        s8  unk3D;
        s32 unk40;
        s32 unk44;
    } tmp;
    struct37 *temp_v0;

    arg0->unk16 |= 4;
    *(u8 *)&arg0->unk14 = 1;
    tmp.unk0 = arg0;
    tmp.unk8 = -1;
    tmp.unk4 = 0.0f;
    tmp.unkC = arg0->unk0;
    tmp.unk10 = (s16)arg0->unk2;
    tmp.unk14 = arg0->unk4;
    tmp.unk18 = (s16)arg0->unk6;
    tmp.unk1C = (s16)arg0->unk8;
    tmp.unk40 = 0;
    tmp.unk3D = 0;
    tmp.unk3C = 0;
    tmp.unk38 = 0;
    tmp.unk20 = D_80096A64;
    collision_select_area(0);
    tmp.unk44 = zone_tree_find_leaf(arg0->unk0, arg0->unk4);
    temp_v0 = effect_node_create(300, -1, 60, -1, 0, 45, 72, 255, 0);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk28, &tmp, sizeof(tmp));
    }
    return 1;
}

/* was func_15015300 */
s32 record_dispatch_82f70(struct134 *arg0) {
    void (*func)(void);
    s32 idx = arg0->unk1C;

    if ((idx < 0) || (idx >= 2)) {
        return 1;
    }

    func = D_80082F70[idx];
    if (func != NULL) {
        func();
    }

    return 1;
}


#ifdef NON_MATCHING
/* the level record record_quad_zone_start reads (D_80082EA0 entry 0x34) */
typedef struct {
    s16 x, y, z;        /* 0x00 */
    s16 halfX;          /* 0x06 */
    s16 pad08;
    s16 halfZ;          /* 0x0A */
    f32 angX;           /* 0x0C */
    f32 angY;           /* 0x10 */
    u8 started;         /* 0x14 */
} Rec15015354;

// record_quad_zone_start: start handler (void, D_80082EA0 entry 0x34) of a rectangular zone record: marks it started
// (+0x14 = 1), turns the rectangle (+-halfX, 0, +-halfZ) around the record's position by its angles (mtxf_rotate_xyz_deg /
// mtxf_transform_point) into 4 world corners, stores the 4 edge vectors (next corner - corner) and the sound id of the spot
// (collision_select_area(0); zone_tree_find_leaf(x, z)), and hands that 0x74-byte block to a new effect_node_create object (+0x28).
/* was func_15015354 */
void record_quad_zone_start(Rec15015354 *src) {
    struct {
        Rec15015354 *src;   /* 0x00 */
        s16 u4;             /* 0x04 */
        f32 u8;             /* 0x08 */
        f32 corner[4][3];   /* 0x0C */
        f32 edge[4][3];     /* 0x3C */
        s32 sound;          /* 0x6C */
        s32 u70;            /* 0x70 */
    } blk;
    f32 m[4][4];
    f32 local[4][3];
    f32 pos[3];
    u8 *e;
    u8 i;
    u8 j;

    blk.src = src;
    blk.u4 = -1;
    blk.u8 = 0.0f;
    src->started = 1;
    pos[0] = src->x;
    pos[1] = src->y;
    pos[2] = src->z;
    local[0][0] = src->halfX;
    local[0][1] = 0.0f;
    local[0][2] = src->halfZ;
    local[1][0] = src->halfX;
    local[1][1] = 0.0f;
    local[1][2] = -src->halfZ;
    local[2][0] = -src->halfX;
    local[2][1] = 0.0f;
    local[2][2] = -src->halfZ;
    local[3][0] = -src->halfX;
    local[3][1] = 0.0f;
    local[3][2] = src->halfZ;
    mtxf_rotate_xyz_deg(m, src->angX, src->angY, 0.0f);
    m[3][0] = pos[0];
    m[3][1] = pos[1];
    m[3][2] = pos[2];
    for (i = 0; i < 4; i++) {
        mtxf_transform_point(m, local[i][0], local[i][1], local[i][2], &blk.corner[i][0], &blk.corner[i][1],
                      &blk.corner[i][2]);
    }
    for (i = 0; i < 4; i++) {
        j = (i + 1) & 3;
        blk.edge[i][0] = blk.corner[j][0] - blk.corner[i][0];
        blk.edge[i][1] = blk.corner[j][1] - blk.corner[i][1];
        blk.edge[i][2] = blk.corner[j][2] - blk.corner[i][2];
    }
    collision_select_area(0);
    blk.sound = zone_tree_find_leaf(src->x, src->z);
    blk.u70 = 0;
    e = (u8 *) effect_node_create(0x12C, -1, 0x3D, -1, 0, 0x2E, (struct37 *) 0x74, 0xFF, 0);
    if (e != NULL) {
        memcpy(e + 0x28, &blk, 0x74);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/record_quad_zone_start.s")
#endif
/* was func_15015644 */
s32 record_effect68_start(struct134 *arg0) {
    struct {
        struct134 *unk0;
        f32 unk4;
        s32 unk8;
        s8 unkC;
    } tmp;
    struct37 *temp_v0;

    arg0->unk16 |= 4;
    *(u8 *)&arg0->unk14 = 1;
    tmp.unk0 = arg0;
    tmp.unk4 = spawn_region_area(arg0);
    collision_select_area(0);
    tmp.unk8 = zone_tree_find_leaf(arg0->unk0, arg0->unk4);
    tmp.unkC = 0;
    temp_v0 = effect_node_create(300, -1, 68, -1, 0, 47, 16, 255, 0);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk28, &tmp, 16);
    }
    return 1;
}
#ifdef NON_MATCHING
s32 rope_create(s8 *, s32);

/*
 * P85: spawn handler: a vertical zone from record rec (s16 position +0 / +2 / +4, s16 length +8, angles +0xC / +0x10
 * as f32 bits, kind +0x18). Kinds below 6 / 7 / 2 are skipped on levels 0xB / 0x2C / 0x26. The far end is the
 * (0, length, 0) direction rotated by the angles (not added to the position, as in the original); the upper / lower
 * point (by y) and the height |dy| go to rope_create with the kind. Always returns 1.
 */
/* was func_150156F4 */
s32 record_rope_zone_start(u8 *rec) {
    f32 m[4][4];
    f32 pos[3];
    f32 pts[2][3];
    struct {
        s8 kind;
        u8 pad1[3];
        f32 top[3];    /* the point with the larger y */
        f32 bottom[3];
        f32 height;
        s8 flag;
    } zone;
    s32 i;

    if (D_800BE9F0 == 0xB) {
        if (*(u32 *) (rec + 0x18) < 6) {
            return 1;
        }
    } else if (D_800BE9F0 == 0x2C) {
        if (*(u32 *) (rec + 0x18) < 7) {
            return 1;
        }
    } else if (D_800BE9F0 == 0x26) {
        if (*(u32 *) (rec + 0x18) < 2) {
            return 1;
        }
    }
    mtxf_rotate_xyz_deg(m, *(f32 *) (rec + 0xC), *(f32 *) (rec + 0x10), 0.0f);
    pos[0] = *(s16 *) (rec + 0);
    pos[1] = *(s16 *) (rec + 2);
    pos[2] = *(s16 *) (rec + 4);
    mtxf_transform_point(m, 0.0f, *(s16 *) (rec + 8), 0.0f, &pts[1][0], &pts[1][1], &pts[1][2]);
    pts[0][0] = *(s16 *) (rec + 0);
    pts[0][1] = *(s16 *) (rec + 2);
    pts[0][2] = *(s16 *) (rec + 4);
    zone.kind = *(s32 *) (rec + 0x18);
    i = (pts[0][1] < pts[1][1]) ? 1 : 0;
    zone.top[0] = pts[i][0];
    zone.top[1] = pts[i][1];
    zone.top[2] = pts[i][2];
    i = (pts[1][1] < pts[0][1]) ? 1 : 0;
    zone.bottom[0] = pts[i][0];
    zone.bottom[1] = pts[i][1];
    zone.bottom[2] = pts[i][2];
    zone.flag = 0;
    zone.height = fabsf(pts[1][1] - pts[0][1]);
    rope_create(&zone.kind, 0);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/record_rope_zone_start.s")
#endif
