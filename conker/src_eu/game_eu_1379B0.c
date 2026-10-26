#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct { f32 x, y, z; } V3;

/* was func_1510A1A0 */
void segment_debris_spawn(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, u8 *arg5)
{
  f32 temp_f0;
  u8 *spA0;
  struct 
  {
    f32 u20[10];
    s32 u48;
    u8 pad4C[0x8];
    f32 u54;
    f32 u58;
    f32 u5C;
    f32 u60;
    f32 u64;
    f32 u68;
    f32 u6C;
    s32 u70;
    s16 u74;
    s16 u76;
    s8 u78;
    u8 pad79[0x3];
    s32 u7C;
    u8 u80;
    s8 u81;
    s8 u82;
    s8 u83;
    s8 u84;
    s8 u85;
    s8 u86;
    s8 u87;
    s8 u88;
    u8 pad89[0x1];
    s8 u8A;
    u8 pad8B[0x1];
    u8 *u8C;
    u8 u90;
    u8 pad91[0x1];
    s16 u92;
    s16 u94;
    u8 pad96[0x6];
    f32 u9C;
  } sp;
  spA0 = *((u8 **) (((u8 *) arg0) - -0x28));
  sp.u9C = ((random_float() * 4611.0f) + 1581.0f) * 0.001f;
  sp.u20[0] = 1.0f;
  sp.u20[1] = 1.0f;
  sp.u20[3] = ((random_float() * 3522.0f) + 4599.0f) * 0.000001f;
  sp.u20[2] = sp.u20[3];
  sp.u20[4] = random_float() * 360.0f;
  sp.u20[5] = random_float() * 360.0f;
  temp_f0 = random_float();
  sp.u20[7] = 1.0f;
  sp.u20[8] = 1.0f;
  sp.u20[9] = 1.0f;
  sp.u20[6] = temp_f0 * 360.0f;
  temp_f0 = sp.u9C; // fakematch: reload u9C into the reused float temp
  *((V3 *) (&sp.u48)) = *((V3 *) arg1);
  sp.u54 = (*((f32 *) (((u8 *) arg5) + 0))) * temp_f0;
  sp.u58 = (*((f32 *) (((u8 *) arg5) + 4))) * temp_f0;
  sp.u5C = (*((f32 *) (((u8 *) arg5) + 8))) * temp_f0;
  sp.u60 = ((random_float() * 24546.0f) + (-12273.0f)) * 0.001f;
  sp.u64 = 0.0f;
  sp.u68 = ((random_float() * 24546.0f) + (-12273.0f)) * 0.001f;
  temp_f0 = (random_float() * 124.0f) + (-231.0f); // fakematch: permuter temp
  sp.u70 = 0x29E8;
  sp.u6C = temp_f0 * 0.001f;
 sp.u74 = (random_int() % 15U) + 0x14; if (random_int() & 1) { sp.u76 = 0x23; } else { sp.u76 = 0x24;
  }
  sp.u78 = 0;
  sp.u7C = 0;
  sp.u80 = 0xFF;
  sp.u81 = 8;
  sp.u82 = 0;
  sp.u83 = 0;
  sp.u84 = 0;
  sp.u85 = 0;
  sp.u86 = 0;
  sp.u87 = 0;
  sp.u88 = 2;
  if ((*((u8 *) (((u8 *) arg0) + 0x13))) == 0x1A)
  {
    sp.u8A = 1;
  }
  else
  {
    sp.u8A = 2;
  }
  sp.u8C = spA0;
  sp.u90 = *((u8 *) (((u8 *) spA0) + 0x3B));
  sp.u92 = 0xA;
  sp.u94 = 0x19;
  mdl_particle_spawn(&sp, 3, 0xFF, 0, (s32) (*((u8 *) (((u8 *) arg0) + 0xC))), (s32) (*((u8 *) (((u8 *) arg0) + 1))));
}

/* was func_1510A454 */
struct260 *segment_effect_spawn(u8 *volatile arg0, s16 arg1, s8 arg2, s8 arg3, f32 arg4, s32 arg5, u8 arg6, s32 arg7) { // fakematch: volatile gives the arg0 home reload (s101 recipe)
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        f32 unk4;
        f32 unk8;
        s8 unkC;
        s8 unkD;
    } tmp;
    s16 n;
    u8 flag;

    if (arg0 == NULL) {
        return NULL;
    }
    flag = 0;
    if (arg1 < 0) {
        n = 300;
    } else {
        flag = 1;
        n = arg1;
    }
    tmp.unk4 = 0.0f;
    tmp.unk8 = arg4;
    tmp.unkC = arg2;
    tmp.unkD = arg3;
    tmp.unk0 = arg0;
    temp_v0 = func_15149130(n, -1, 0x1B, -1, flag, 0x1B, arg5 + 0x10, arg6, arg7);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x10);
    }
    return temp_v0;
}

#ifdef NON_MATCHING
extern f32 D_800A28EC;          /* emission rate scale */
extern f32 D_800A28D4[];        /* segment weights; [6] = total */
extern f32 D_800A2938[];        /* segment start / end points (12-byte points, read as start = [i], end = [i + 1]) */
extern f32 D_800A298C[];        /* per-segment target points */
extern void *D_80089000[];      /* end handlers (s8 +0x34) */
extern void *D_80089004[];      /* point handlers (s8 +0x35) */
f32 random_float(void);
void world_record_build_matrix(f32 (*)[4], u8 *);
void mtxf_transform_point(f32 (*)[4], f32, f32, f32, f32 *, f32 *, f32 *);
s32 vec3_normalize_len(f32 *, f32 *, s32 *, s32 *);

// segment_effect_update: P232. Update callback of effect type 0x1B (segment_effect_spawn fills its +0x28 data: owner object,
// accumulator, rate, end handler +0x34, point handler +0x35). The accumulator grows by rate * D_800A28EC * frame step;
// for every whole unit, when there is a point handler: picks a segment of the owner's model by the weights
// D_800A28D4, a random point on it, and transforms it, the segment ends and the segment's target point by the
// owner's matrix (world_record_build_matrix); the direction from the start to a random point between the end and the target is
// normalised (vec3_normalize_len), then D_80089004[handler](fx, point, start, end, target, dir) runs. Without a point
// handler the units are dropped. Finally the end handler D_80089000[+0x34](fx) runs unless it is -1. Sibling of
// obj_point_effect_emitter_update (game_eu_1371A0, effect 0x1A).
/* was func_1510A538 */
void segment_effect_update(u8 *fx) {
    u8 *rec = fx + 0x28;
    f32 mtx[4][4];
    f32 pt[3];
    f32 start[3];
    f32 end[3];
    f32 target[3];
    f32 dir[3];
    f32 *seg;
    f32 *w;
    f32 r;
    f32 sel;
    f32 wt;
    s32 i;

    *(f32 *) (rec + 4) += *(f32 *) (rec + 8) * D_800A28EC * D_800BE9A4;
    if ((s8) rec[0xD] != -1) {
        while (*(f32 *) (rec + 4) > 1.0f) {
            world_record_build_matrix(mtx, *(u8 **) rec);
            i = 0;
            sel = D_800A28D4[6] * random_float();
            w = D_800A28D4;
            if (D_800A28D4[0] < sel) {
                wt = D_800A28D4[0];
                do {
                    sel -= wt;
                    wt = w[1];
                    i++;
                    w++;
                } while (wt < sel);
            }
            r = random_float();
            seg = &D_800A2938[i * 3];
            mtxf_transform_point(mtx, (seg[3] - seg[0]) * r + seg[0], (seg[4] - seg[1]) * r + seg[1],
                          (seg[5] - seg[2]) * r + seg[2], &pt[0], &pt[1], &pt[2]);
            mtxf_transform_point(mtx, seg[0], seg[1], seg[2], &start[0], &start[1], &start[2]);
            mtxf_transform_point(mtx, seg[3], seg[4], seg[5], &end[0], &end[1], &end[2]);
            mtxf_transform_point(mtx, D_800A298C[i * 3], D_800A298C[i * 3 + 1], D_800A298C[i * 3 + 2], &target[0],
                          &target[1], &target[2]);
            r = random_float();
            dir[0] = ((target[0] - end[0]) * r + end[0]) - start[0];
            dir[1] = ((target[1] - end[1]) * r + end[1]) - start[1];
            dir[2] = ((target[2] - end[2]) * r + end[2]) - start[2];
            vec3_normalize_len(dir, dir, NULL, NULL);
            ((void (*)(u8 *, f32 *, f32 *, f32 *, f32 *, f32 *)) D_80089004[(s8) rec[0xD]])(fx, pt, start, end,
                                                                                          target, dir);
            *(f32 *) (rec + 4) -= 1.0f;
        }
    } else {
        while (*(f32 *) (rec + 4) > 1.0f) {
            *(f32 *) (rec + 4) -= 1.0f;
        }
    }
    if ((s8) rec[0xC] != -1) {
        ((void (*)(u8 *)) D_80089000[(s8) rec[0xC]])(fx);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1379B0/segment_effect_update.s")
#endif

/* was func_1510A8C4 */
struct260 *vent_smoke_emitter_spawn(u8 *arg0, s16 arg1, u8 arg2, s32 arg3) {
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        u8 unk4;
        u8 pad5[3];
        f32 unk8;
        f32 unkC;
        f32 unk10;
    } tmp;

    if (arg0 == NULL) {
        return NULL;
    }
    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    tmp.unkC = 0.20400001f;
    tmp.unk10 = 0.822f;
    temp_v0 = func_15149130(arg1, -1, 0x1C, -1, 1, 0x1C, 0x14, arg2, arg3);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x14);
    }
    return temp_v0;
}

#ifdef NON_MATCHING
void mtx_transform_point_or_origin(void *arg0, void *arg1, void *arg2);
s32 particle_spawn_basic(void *, u8, s32, u8, s32);

/* vent_smoke_emitter_update's model-space vent points (D_800A29D4 / D_800A29E0) and aim points (D_800A29EC / D_800A29F8) */
static const f32 sVentPoints[4][3] = {
    { -11.0f, -24.0f, 43.0f }, { 31.0f, -24.0f, 43.0f },  /* vents 0 / 1 */
    { -51.0f, -24.0f, 43.0f }, { 81.0f, -24.0f, 43.0f },  /* their aim points */
};

/* vent_smoke_emitter_update's puff request (particle_spawn_basic) */
typedef struct {
    /* 0x00 */ s32 kind;
    /* 0x04 */ s32 u04;
    /* 0x08 */ s16 sprite;
    /* 0x0A */ s16 life;
    /* 0x0C */ s32 u0C;
    /* 0x10 */ s32 u10;
    /* 0x14 */ u8  color[10];
    /* 0x1E */ s16 u1E;
    /* 0x20 */ s16 u20;
    /* 0x22 */ s16 u22;
    /* 0x24 */ f32 growth;
    /* 0x28 */ f32 sizeX;
    /* 0x2C */ f32 sizeY;
    /* 0x30 */ f32 pos[3];
    /* 0x3C */ f32 rot[3];
    /* 0x48 */ f32 vel[3];
    /* 0x54 */ f32 u54;
    /* 0x58 */ s32 flags;
    /* 0x5C */ s32 u5C;
    /* 0x60 */ u8  u60[6];
} VentPuff;

// vent_smoke_emitter_update: update handler of the emitter made by vent_smoke_emitter_spawn (data at +0x28: owner object,
// its unique id, an accumulator, base rate, random rate). Kills the emitter (+0xE = -1) when the owner is gone or
// was replaced; otherwise adds (base + random * rand) * D_800BE9A4 to the accumulator and, while it is above 1,
// spawns one puff from one of the two vents of the owner's model (bone matrix +0x240), blowing outward at
// 0.096..0.299 with a random size 60..120 and life 20..35 and random flip flags. Without a model the
// accumulator is just drained (P156).
/* was func_1510A98C */
void vent_smoke_emitter_update(u8 *arg0) {
    struct {
        u8 *obj;
        u8 uid;
        f32 accum;
        f32 rate;
        f32 rateRand;
    } *rec = (void *)(arg0 + 0x28);
    f32 pts[2][3];
    f32 dirs[2][3];
    VentPuff puff;
    f32 fade;
    f32 speed;
    s32 side;
    u8 *model;
    u8 *e;

    if (*(s32 *)rec->obj == 0 || rec->uid != rec->obj[0x3B]) {
        *(s16 *)(arg0 + 0xE) = -1;
        return;
    }
    rec->accum += (rec->rate + random_float() * rec->rateRand) * D_800BE9A4;
    if (1.0f < rec->accum && *(u8 **)(rec->obj + 0x1D4) != NULL) {
        model = *(u8 **)(rec->obj + 0x1D4) + 0x240;
        mtx_transform_point_or_origin((void *)sVentPoints[0], pts[0], model);
        mtx_transform_point_or_origin((void *)sVentPoints[1], pts[1], model);
        mtx_transform_point_or_origin((void *)sVentPoints[2], dirs[0], model);
        mtx_transform_point_or_origin((void *)sVentPoints[3], dirs[1], model);
        dirs[0][0] -= pts[0][0];
        dirs[0][1] -= pts[0][1];
        dirs[0][2] -= pts[0][2];
        dirs[1][0] -= pts[1][0];
        dirs[1][1] -= pts[1][1];
        dirs[1][2] -= pts[1][2];

        fade = 0.91080099f;
        puff.kind = 0x200005;
        puff.u04 = 0;
        puff.sprite = 0xE03;
        puff.u0C = 0;
        puff.u10 = 0;
        puff.color[0] = 0xDD;
        puff.color[1] = 0xD3;
        puff.color[2] = 0xCD;
        puff.color[3] = 0xFF;
        puff.color[4] = 0x57;
        puff.color[5] = 0x55;
        puff.color[6] = 0x5A;
        puff.color[7] = 0xFF;
        puff.color[8] = 0xFF;
        puff.color[9] = 0x29;
        puff.u1E = 0x19;
        puff.u20 = 0xA;
        puff.u22 = 0x19;
        puff.growth = 1.043206f;
        puff.rot[0] = 0.0f;
        puff.rot[1] = 0.0f;
        puff.rot[2] = 0.0f;
        puff.u54 = 0.0f;
        puff.flags = 0xCE05;
        puff.u60[0] = 3;
        puff.u60[1] = 3;
        puff.u60[2] = 0x10;
        puff.u60[3] = 0xFF;
        puff.u60[4] = 0xFF;
        puff.u60[5] = 0;
        do {
            if (random_int() & 1) {
                puff.flags |= 0x40;
            } else {
                puff.flags &= ~0x40;
            }
            if (random_int() & 1) {
                puff.flags |= 0x80;
            } else {
                puff.flags &= ~0x80;
            }
            side = random_int() & 1;
            speed = (random_float() * 203.0f + 96.0f) * 0.001f;
            puff.life = (random_int() & 0xF) + 20;
            puff.sizeX = puff.sizeY = random_float() * 60.0f + 60.0f;
            puff.pos[0] = pts[side][0];
            puff.pos[1] = pts[side][1];
            puff.pos[2] = pts[side][2];
            puff.vel[0] = dirs[side][0] * speed;
            puff.vel[1] = dirs[side][1] * speed;
            puff.vel[2] = dirs[side][2] * speed;
            e = (u8 *)particle_spawn_basic(&puff, 1, 4, arg0[0xC], arg0[1]);
            if (e != NULL) {
                memcpy(e + 0xA8, &fade, 4);
            }
            rec->accum -= 1.0f;
        } while (1.0f < rec->accum);
        return;
    }
    while (1.0f < rec->accum) {
        rec->accum -= 1.0f;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1379B0/vent_smoke_emitter_update.s")
#endif

/* was func_1510ADF0 */
void segment_effect_handle_event(u8 *arg0, struct212 *arg1, u8 arg2) {
    struct212 *temp_v0 = (struct212 *)(arg0 + 0x28);
    if (arg2 == 0x2D) {
        if (temp_v0->unk0 == arg1->unk0) {
            temp_v0->unk0 = arg1->unk4.i.unk0;
            temp_v0->unk4.b.unk0 = arg1->unk9;
        } else if (temp_v0->unk0 == arg1->unk4.i.unk0) {
            temp_v0->unk0 = arg1->unk0;
            temp_v0->unk4.b.unk0 = arg1->unk8;
        }
    }
}

/* was func_1510AE4C */
void vent_smoke_emitter_handle_event(u8 *arg0, struct212 *arg1, u8 arg2) {
    struct212 *temp_v0 = (struct212 *)(arg0 + 0x28);
    if (arg2 == 0x2D) {
        if (temp_v0->unk0 == arg1->unk0) {
            temp_v0->unk0 = arg1->unk4.i.unk0;
            temp_v0->unk4.b.unk0 = arg1->unk9;
        } else if (temp_v0->unk0 == arg1->unk4.i.unk0) {
            temp_v0->unk0 = arg1->unk0;
            temp_v0->unk4.b.unk0 = arg1->unk8;
        }
    }
}
