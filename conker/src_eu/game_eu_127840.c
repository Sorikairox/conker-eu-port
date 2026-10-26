#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void camera_view_rotation_matrix(s32 arg0, f32 (*arg1)[4], f32 arg2, f32 arg3, f32 arg4);
Gfx *gfx_fill_rect_colour(Gfx *gdl, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 r, u8 g, u8 b);
Gfx *star_field_draw(Gfx *gdl, f32 (*mtx)[4]);

// camera_view_clear_draw: camera callback (D_80089578[1], called by view_background_draw with the D_80089578 signature):
// builds the current player's view matrix from yaw / pitch / roll (camera_view_rotation_matrix), clears the player's viewport
// (D_800BE628[D_80082FA4] +0x24..0x30) to black (gfx_fill_rect_colour), sets pipe sync, other modes 0xEF002C0F / 0x0F0A4004
// and combiner 0xFC357E6A / 0xFFFFFFFF, and draws with the matrix (star_field_draw, which returns the new list end).
// The position and handle arguments are unused.
/* was func_150FA030 */
Gfx *camera_view_clear_draw(Gfx *gdl, f32 x, f32 y, f32 z, f32 yaw, f32 pitch, f32 roll, s32 handle) {
    f32 mtx[4][4];
    u8 *cam;

    camera_view_rotation_matrix(D_80082FA4, mtx, yaw, pitch, roll);
    cam = (u8 *) D_800BE628 + D_80082FA4 * 0x180;
    gdl = gfx_fill_rect_colour(gdl, (s32) *(f32 *) (cam + 0x2C), (s32) *(f32 *) (cam + 0x24),
                        (s32) (*(f32 *) (cam + 0x30) - 1.0f), (s32) *(f32 *) (cam + 0x28), 0, 0, 0);
    gdl[0].words.w0 = 0xE7000000;
    gdl[0].words.w1 = 0;
    gdl[1].words.w0 = 0xEF002C0F;
    gdl[1].words.w1 = 0x0F0A4004;
    gdl[2].words.w0 = 0xFC357E6A;
    gdl[2].words.w1 = 0xFFFFFFFF;
    return star_field_draw(gdl + 3, mtx);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/camera_view_clear_draw.s")
#endif

#ifdef NON_MATCHING
/* effect3d_spawn_full's particle spec and particle_emitter_spawn's spawn block (0x58 bytes). */
typedef struct {
    /* 0x00 */ u8 texture;
    /* 0x01 */ u8 u01;
    /* 0x02 */ s16 texSet;
    /* 0x04 */ s16 life;
    /* 0x08 */ s32 u08;
    /* 0x0C */ s32 u0C;
    /* 0x10 */ u8 color[4];
    /* 0x14 */ f32 halfW;
    /* 0x18 */ f32 halfH;
    /* 0x1C */ s32 angle[3];
    /* 0x28 */ s32 vel[3];
    /* 0x34 */ f32 scale[3];
    /* 0x40 */ s32 flags;
    /* 0x44 */ u8 u44;
    /* 0x45 */ u8 u45;
    /* 0x46 */ u8 u46;
    /* 0x47 */ u8 u47;
    /* 0x48 */ s32 u48;
    /* 0x4C */ u8 u4C;
    /* 0x4D */ u8 pad4D[0xB];
} PartSpecF9BB0;

/* particle_emitter_spawn's emitter block (filled up to 0x5A; the call passes size 0x78). */
typedef struct {
    /* 0x00 */ f32 u00;
    /* 0x04 */ f32 u04;
    /* 0x08 */ f32 u08;
    /* 0x0C */ f32 u0C;
    /* 0x10 */ f32 u10;
    /* 0x14 */ f32 u14;
    /* 0x18 */ f32 u18;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 u20;
    /* 0x24 */ s32 u24[8];
    /* 0x44 */ s32 u44;
    /* 0x48 */ f32 u48;
    /* 0x4C */ s16 u4C[4];
    /* 0x54 */ u8 u54[4];
    /* 0x58 */ u8 u58;
    /* 0x59 */ s8 u59;
    /* 0x5A */ u8 pad5A[2];
} EmitF9BB0;

/* 0x5C bytes copied to each particle's +0x110. */
typedef struct {
    /* 0x00 */ u8 *obj;
    /* 0x04 */ u8 room;
    /* 0x05 */ u8 index;
    /* 0x08 */ f32 u08;
    /* 0x0C */ f32 u0C;
    /* 0x10 */ f32 u10;
    /* 0x14 */ f32 u14;
    /* 0x18 */ f32 u18;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 u20;
    /* 0x24 */ f32 u24;
    /* 0x28 */ f32 u28;
    /* 0x2C */ f32 u2C;
    /* 0x30 */ f32 u30;
    /* 0x34 */ f32 u34;
    /* 0x38 */ f32 u38;
    /* 0x3C */ f32 u3C;
    /* 0x40 */ f32 scale[4];
    /* 0x50 */ u8 *group;
    /* 0x54 */ f32 midY;
    /* 0x58 */ u8 u58;
} PartExtraF9BB0;

/* 0x18 bytes copied to each emitter's +0x170. */
typedef struct {
    /* 0x00 */ s16 u00;
    /* 0x04 */ f32 u04;
    /* 0x08 */ u8 *group;
    /* 0x0C */ u8 index;
    /* 0x10 */ u8 *obj;
    /* 0x14 */ u8 room;
} EmitExtraF9BB0;

/* 0x18 bytes copied to the group object's +0x28; the effects are recorded in it. */
typedef struct {
    /* 0x00 */ u8 *obj;
    /* 0x04 */ u8 room;
    /* 0x08 */ u8 *part[2];
    /* 0x10 */ u8 *emit[2];
} GroupF9BB0;

struct260 *func_15149130(s16 arg0, s8 arg1, s8 arg2, s8 arg3, u8 arg4, u8 arg5, struct37 *arg6, u8 arg7, s32 arg8);
void *effect3d_spawn_full(void *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7, s32 arg8, s32 arg9, u8 argA, s32 argB);
u8 *particle_emitter_spawn(void *emit, s32 emitSize, void *spawn, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s8 arg7, u8 arg8, s32 arg9);
s32 func_151D8E18(structEU_151D8E18 *arg0, s32 arg1, u8 arg2, s32 arg3);
s32 light_create_obj_joint(u8 *, u8, void *, u8, s16, s32, s32, s32, s32, s32, s32, s8, s32, u8, u8, s32);
s32 random_int(void);
void *memcpy(void *, const void *, size_t);
extern s32 D_800A4AA0;
extern s32 D_800A2090;
extern f32 D_800A2130;
extern f32 D_800A2134;
extern f32 D_800A2138;
extern f32 D_800A213C;
extern f32 D_800A2140;
extern f32 D_800A2144;
extern f32 D_eu_800A2148;
extern f32 D_800A214C;
extern f32 D_800A2150;
extern f32 D_eu_800A2154;
extern f32 D_800A2158;
extern f32 D_800A215C;
extern f32 D_800A2160;

// object_aura_spawn: creates a group object (func_15149130 kind 0x46, 0x18-byte block {obj, obj+0x3B}) and, when it
// exists, two particles (effect3d_spawn_full texture 0x5F, D_800A4AA0 list, random blend 1 / 3) and two emitters
// (particle_emitter_spawn texture 0x60, 0x2A) around `obj`, each told its index, the object, its room byte and the group
// (particles at +0x110 also get the mid height (obj +0x14C + +0x150) / 2); the group records them at +0x30 / +0x38.
// Always then calls func_151D8E18 {1, 0x46, 8, 1, -1} and light_create_obj_joint (D_800A2090, 3, 0x46, 0x28).
// `alpha` / `owner` are passed to every spawner.
/* was func_150F9BB0 */
void aura_group_spawn(u8 *obj, u8 alpha, s32 owner) {
    structEU_151D8E18 shake;
    EmitExtraF9BB0 ee;
    PartSpecF9BB0 spawn;
    struct {
        EmitF9BB0 emit; /* particle_emitter_spawn reads 0x78 bytes: on into spec */
        PartSpecF9BB0 spec;
        PartExtraF9BB0 extra; /* kept next to spec as in the asm frame */
    } fr;
    GroupF9BB0 init;
    u8 *group;
    GroupF9BB0 *g;

    init.obj = obj;
    init.room = obj[0x3B];
    init.part[0] = NULL;
    init.part[1] = NULL;
    init.emit[0] = NULL;
    init.emit[1] = NULL;
    group = (u8 *)func_15149130(0x46, -1, 0x4D, -1, 1, 0x33, (struct37 *)0x18, alpha, owner);
    if (group != NULL) {
        g = (GroupF9BB0 *)(group + 0x28);
        memcpy(g, &init, 0x18);

        fr.extra.u58 = 0;
        fr.extra.obj = obj;
        fr.extra.midY = (*(f32 *)(obj + 0x14C) + *(f32 *)(obj + 0x150)) * 0.5f;
        fr.extra.u08 = D_800A2130;
        fr.extra.u10 = D_800A2134;
        fr.extra.u18 = D_800A2138;
        fr.extra.u0C = D_800A213C;
        fr.extra.room = obj[0x3B];
        fr.extra.u24 = 0.0f;
        fr.extra.u28 = 0.0f;
        fr.extra.u38 = 0.0f;
        fr.spec.halfW = 0.0f;
        fr.spec.halfH = 0.0f;
        fr.extra.u3C = 0.0f;
        fr.extra.scale[2] = 1.0f;
        fr.extra.scale[0] = 1.0f;
        fr.extra.scale[3] = 1.0f;
        fr.extra.scale[1] = 1.0f;
        fr.spec.texture = 0x5F;
        fr.spec.u01 = 8;
        fr.spec.texSet = 0x2203;
        fr.spec.life = 300;
        fr.spec.u08 = 0;
        fr.spec.u0C = 0;
        fr.spec.color[0] = 0xFF;
        fr.spec.color[1] = 0xFF;
        fr.spec.color[2] = 0xFF;
        fr.spec.color[3] = 0xFF;
        fr.extra.u14 = D_800A2140;
        fr.extra.u20 = D_800A2144;
        fr.extra.u1C = D_eu_800A2148;
        fr.extra.u2C = 160.0f;
        fr.extra.u30 = 95.0f;
        fr.extra.u34 = D_800A214C;
        fr.extra.group = group;
        fr.spec.angle[0] = ((s32 *)D_800A5860)[0];
        fr.spec.angle[1] = ((s32 *)D_800A5860)[1];
        fr.spec.angle[2] = ((s32 *)D_800A5860)[2];
        fr.spec.vel[0] = ((s32 *)D_800A5860)[0];
        fr.spec.vel[1] = ((s32 *)D_800A5860)[1];
        fr.spec.vel[2] = ((s32 *)D_800A5860)[2];
        fr.spec.scale[0] = 1.0f;
        fr.spec.scale[1] = 1.0f;
        fr.spec.scale[2] = 1.0f;
        fr.spec.flags = 0x40EC0000;
        fr.spec.u44 = 0;
        fr.spec.u45 = 0xFF;
        fr.spec.u46 = 0;
        fr.spec.u47 = 7;
        fr.spec.u48 = 0;
        for (fr.extra.index = 0; fr.extra.index < 2; fr.extra.index++) {
            g->part[fr.extra.index] = effect3d_spawn_full(&fr.spec, (s32)&D_800A4AA0, 0, 0x25, 0, 0x1D,
                                              ((random_int() & 1) ? 2 : 0) + 1, 0, 0, 0x5C,
                                              alpha, owner);
            if (g->part[fr.extra.index] != NULL) {
                memcpy(g->part[fr.extra.index] + 0x110, &fr.extra, 0x5C);
            }
        }

        ee.u00 = 0;
        ee.u04 = 1.0f;
        ee.obj = obj;
        ee.group = group;
        ee.room = obj[0x3B];
        fr.emit.u24[0] = -1;
        fr.emit.u24[4] = -1;
        fr.emit.u24[1] = -1;
        fr.emit.u24[5] = -1;
        fr.emit.u24[2] = -1;
        fr.emit.u24[6] = -1;
        fr.emit.u24[3] = -1;
        fr.emit.u24[7] = -1;
        fr.emit.u59 = -1;
        fr.emit.u00 = D_800A2150;
        fr.emit.u04 = D_800A2150;
        fr.emit.u08 = D_eu_800A2154;
        fr.emit.u0C = D_eu_800A2154;
        fr.emit.u10 = D_800A2158;
        fr.emit.u14 = D_800A2158;
        fr.emit.u18 = 1.0f;
        fr.emit.u44 = 0;
        fr.emit.u48 = 1.0f;
        fr.emit.u4C[0] = 0;
        fr.emit.u4C[1] = 0;
        fr.emit.u4C[2] = 0;
        fr.emit.u4C[3] = 0;
        fr.emit.u54[0] = 0;
        fr.emit.u54[1] = 0;
        fr.emit.u54[2] = 0;
        fr.emit.u54[3] = 0;
        fr.emit.u58 = 0xF;
        spawn.texture = 0x60;
        spawn.u01 = 3;
        spawn.texSet = 0x2203;
        spawn.life = 300;
        spawn.u08 = 0;
        spawn.u0C = 0;
        spawn.color[0] = 0xFF;
        spawn.color[1] = 0xFF;
        spawn.color[2] = 0xFF;
        spawn.color[3] = 0xFF;
        spawn.halfW = 100.0f;
        spawn.halfH = 100.0f;
        fr.emit.u1C = D_800A215C;
        fr.emit.u20 = D_800A2160;
        spawn.angle[0] = ((s32 *)D_800A5860)[0];
        spawn.angle[1] = ((s32 *)D_800A5860)[1];
        spawn.angle[2] = ((s32 *)D_800A5860)[2];
        spawn.vel[0] = ((s32 *)D_800A5860)[0];
        spawn.vel[1] = ((s32 *)D_800A5860)[1];
        spawn.vel[2] = ((s32 *)D_800A5860)[2];
        spawn.scale[0] = 1.0f;
        spawn.scale[1] = 1.0f;
        spawn.scale[2] = 1.0f;
        spawn.flags = 0xCD2002;
        spawn.u44 = 0xFF;
        spawn.u45 = 0xFF;
        spawn.u46 = 0;
        spawn.u47 = 7;
        spawn.u48 = 0;
        spawn.u4C = 0xFF;
        for (ee.index = 0; ee.index < 2; ee.index++) {
            g->emit[ee.index] = particle_emitter_spawn(&fr.emit, 0x78, &spawn, 0, 0x2A, 0, 0, -1, alpha, owner);
            if (g->emit[ee.index] != NULL) {
                memcpy(g->emit[ee.index] + 0x170, &ee, 0x18);
            }
        }
    }
    shake.unk0 = 1;
    shake.unk2 = 0x46;
    shake.unk5 = 1;
    shake.unk4 = 8;
    shake.unk6 = -1;
    func_151D8E18(&shake, 0, alpha, owner);
    light_create_obj_joint(obj, 1, &D_800A2090, 3, 0x46, 0x28, 0xFF, 0xFF, 0xFF, 0xFF, 0, -1, 0, 0, alpha, owner);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/aura_group_spawn.s")
#endif

#ifdef NON_MATCHING
void func_15145EA4(f32 **, f32 **, void *, s32);
extern f32 D_800A209C[3]; /* the two emitter offsets (bone space) */
extern f32 D_800A20A8[3];
extern f32 D_800A20B4[3]; /* the two direction points */
extern f32 D_800A20C0[3];
extern f32 D_800A2164;
// twin_emitters_follow_owner: handler 15 of D_8008A980 (`void (u8 *)`). Ends the effect (+0xE = -1) when the owner
// (+0x28) is gone or its id +0x3B no longer matches +0x2C. With the owner's bone matrices (+0x1D4) it transforms the
// four offsets D_800A209C..C0 by the first matrix (func_15145EA4) and gives each of the two emitter pairs (+0x30 / +0x38
// and +0x34 / +0x3C) its position and direction: the first kind gets the flag 1 at +0x168, the second the flag 2 (and
// loses 4) at +0x58. Without matrices both flags are cleared. Then the first kind's +0x158 / +0x15C become 0 / 0 while
// +0xE < 10, else 6 / 15, and the second kind's +0x174 becomes 0, else D_800A2164 (1.306).
/* was func_150FA738 */
void aura_group_follow_owner(u8 *arg0) {
    u8 *owner = *(u8 **) (arg0 + 0x28);
    u8 **a = (u8 **) (arg0 + 0x30);
    u8 **b = (u8 **) (arg0 + 0x38);
    f32 *src[4];
    f32 *dst[4];
    f32 pos[2][3]; /* sp88, sp94 */
    f32 dir[2][3]; /* sp70, sp7C */
    u8 *p;
    u8 i;

    if (*(s32 *) owner == 0 || arg0[0x2C] != owner[0x3B]) {
        *(s16 *) (arg0 + 0xE) = -1;
        return;
    }
    if (*(u8 **) (owner + 0x1D4) != NULL) {
        src[0] = D_800A209C;
        src[1] = D_800A20A8;
        src[2] = D_800A20B4;
        src[3] = D_800A20C0;
        dst[0] = pos[0];
        dst[1] = pos[1];
        dst[2] = dir[0];
        dst[3] = dir[1];
        func_15145EA4(src, dst, *(u8 **) (owner + 0x1D4) + 0x40, 4);
        for (i = 0; i < 2; i++) {
            p = a[i];
            if (p != NULL) {
                p[0x168] |= 1;
                ((f32 *) (p + 0x34))[0] = pos[i][0];
                ((f32 *) (p + 0x34))[1] = pos[i][1];
                ((f32 *) (p + 0x34))[2] = pos[i][2];
                ((f32 *) (p + 0x40))[0] = dir[i][0];
                ((f32 *) (p + 0x40))[1] = dir[i][1];
                ((f32 *) (p + 0x40))[2] = dir[i][2];
            }
            p = b[i];
            if (p != NULL) {
                *(s32 *) (p + 0x58) |= 2;
                *(s32 *) (p + 0x58) &= ~4;
                ((f32 *) (p + 0x34))[0] = pos[i][0];
                ((f32 *) (p + 0x34))[1] = pos[i][1];
                ((f32 *) (p + 0x34))[2] = pos[i][2];
                ((f32 *) (p + 0x40))[0] = dir[i][0];
                ((f32 *) (p + 0x40))[1] = dir[i][1];
                ((f32 *) (p + 0x40))[2] = dir[i][2];
            }
        }
    } else {
        for (i = 0; i < 2; i++) {
            if (a[i] != NULL) {
                a[i][0x168] &= ~1;
            }
            if (b[i] != NULL) {
                *(s32 *) (b[i] + 0x58) &= ~2;
            }
        }
    }
    for (i = 0; i < 2; i++) {
        p = a[i];
        if (p != NULL) {
            if (*(s16 *) (arg0 + 0xE) < 10) {
                *(f32 *) (p + 0x158) = 0.0f;
                *(f32 *) (p + 0x15C) = 0.0f;
            } else {
                *(f32 *) (p + 0x158) = 6.0f;
                *(f32 *) (p + 0x15C) = 15.0f;
            }
        }
        p = b[i];
        if (p != NULL) {
            if (*(s16 *) (arg0 + 0xE) < 10) {
                *(f32 *) (p + 0x174) = 0.0f;
            } else {
                *(f32 *) (p + 0x174) = D_800A2164;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/aura_group_follow_owner.s")
#endif

/* was func_150FA9E8 */
void screen_flash_handle_event(u8 *arg0, s32 arg1, u8 arg2) {
    s32 temp_t6;

    temp_t6 = arg2;
    if (temp_t6 == 0x4C) {
        (*(s8 *)((u8 *)arg0 + 0x11)) = -1;
        func_1515D4D4(0U, 0U, 0U, 0xFF);
        return;
    }
    if (temp_t6 == 0x4D) {
        (*(s8 *)((u8 *)arg0 + 0x11)) = 0x1E;
        return;
    }
    if (temp_t6 == 0x4E) {
        (*(s8 *)((u8 *)arg0 + 0x11)) = -1;
        return;
    }
    if (temp_t6 == 0x4F) {
        (*(s8 *)((u8 *)arg0 + 0x11)) = -1;
        func_1515D4D4(0xFFU, 0xFFU, 0xFFU, 0xFF);
    }
}

#ifdef NON_MATCHING
/* func_151506E8's spec (same layout as game_2062D0's S06E8). */
typedef struct {
    /* 0x00 */ s16 u0[4];
    /* 0x08 */ struct17 pos;
    /* 0x14 */ s16 u14;
    /* 0x16 */ s16 u16;
    /* 0x18 */ f32 u18;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ s16 u20;
    /* 0x22 */ s16 u22;
    /* 0x24 */ f32 u24;
    /* 0x28 */ f32 u28;
    /* 0x2C */ u8 u2C;
    /* 0x2D */ u8 u2D;
    /* 0x30 */ f32 u30;
    /* 0x34 */ f32 u34;
    /* 0x38 */ u8 u38;
    /* 0x39 */ u8 u39;
    /* 0x3C */ f32 u3C;
    /* 0x40 */ u8 u40;
    /* 0x44 */ f32 u44;
} RingSpecFA520;

/* func_151307F0's particle request (same layout as game_2062D0's impact_dust_cloud_spawn request). */
typedef struct {
    /* 0x00 */ s32 handlers;
    /* 0x04 */ s32 u04;
    /* 0x08 */ s16 texSet;
    /* 0x0A */ s16 life;
    /* 0x0C */ s32 u0C;
    /* 0x10 */ s32 u10;
    /* 0x14 */ u8 color[4];
    /* 0x18 */ u8 u18[3];
    /* 0x1B */ u8 alpha;
    /* 0x1C */ u8 u1C;
    /* 0x1D */ u8 texture;
    /* 0x1E */ s16 fadeStart;
    /* 0x20 */ s16 fadeRate;
    /* 0x22 */ s16 u22;
    /* 0x24 */ f32 u24;
    /* 0x28 */ f32 halfW;
    /* 0x2C */ f32 halfH;
    /* 0x30 */ s32 pos[3];
    /* 0x3C */ s32 angle[3];
    /* 0x48 */ s32 vel[3];
    /* 0x54 */ f32 value;
    /* 0x58 */ s32 flags;
    /* 0x5C */ s32 u5C;
    /* 0x60 */ u8 draw;
    /* 0x61 */ u8 update;
    /* 0x62 */ u8 blend;
    /* 0x63 */ s8 u63;
    /* 0x64 */ s8 u64;
    /* 0x65 */ u8 u65;
    /* 0x66 */ u8 u66;
    /* 0x68 */ s16 u68;
    /* 0x6C */ f32 range;
} ParticleReqFA520;

void func_15143134(void *arg0, void *arg1, void *arg2);
void func_1504715C(void *, u8 *);
void func_15154488(struct_eu_15154488 *arg0, struct17 *arg1, s32 arg2, u8 arg3, s32 arg4);
s32 func_151506E8(RingSpecFA520 *, struct17 *, s32, u8, s32);
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
void func_151C384C(void *arg0, u8 arg1, s32 arg2);
s32 random_int(void);
f32 random_float(void);
void *memcpy(void *, const void *, size_t);
extern struct17 D_800A20CC[]; /* model-space points, indexed by `point` */
extern f32 D_800A2168;
extern f32 D_800A216C;
extern f32 D_800A2170;
extern f32 D_800A2174;
extern f32 D_800A2178;
extern f32 D_800A217C;
extern f32 D_800A2180;
extern f32 D_800A2184;

// object_point_burst_spawn: when `obj` has a matrix list (+0x1D4), takes model point D_800A20CC[point] through
// matrix 5 and spawns there: a func_15154488 burst and a func_151506E8 ring (both clipped to the object's bounds from
// func_1504715C), a glow particle (func_151307F0, texture 0x79, life 300, blend 0x27, random flip flags 0x40 / 0x80,
// alpha = size = 100..200 random) whose +0xA8 gets a 0x14-byte growth block (0, rate 10..13, D_800A2184, size,
// size / rate^2), and func_151C384C at the point. `alpha` / `owner` are passed to every spawner.
/* was func_150FA520 */
void obj_point_burst_spawn(u8 *obj, u8 point, u8 alpha, s32 owner) {
    struct {
        f32 u00;
        f32 rate;
        f32 u08;
        f32 size;
        f32 accel;
    } extra;
    ParticleReqFA520 req;
    RingSpecFA520 ring;
    struct_eu_15154488 burst;
    s32 bounds[9];
    struct17 pos;
    u8 *mtx;
    s32 fx;
    s32 flipA;
    s32 flipB;
    f32 rate;
    f32 size;

    mtx = *(u8 **)(obj + 0x1D4);
    if (mtx == NULL) {
        return;
    }
    func_15143134(&D_800A20CC[point], &pos, mtx + 0x140);
    func_1504715C(bounds, obj);

    burst.unk8 = pos;
    burst.unk14 = 4.0f;
    burst.unk18 = D_800A2168;
    burst.unk1C = D_800A216C;
    burst.unk20 = D_800A2170;
    burst.unk24 = 12.0f;
    burst.unk28 = D_800A2174;
    burst.unk6 = 0x32;
    burst.unk2C = 9;
    burst.unk2E = 6;
    burst.unk2 = 0xFF;
    burst.unk4 = -0x28;
    burst.unk0 = 0;
    burst.unk30 = 3;
    burst.unk32 = 1;
    burst.unk34 = 0x1E;
    burst.unk36 = 0x32;
    burst.unk38 = 0x64;
    burst.unk3A = 0x64;
    burst.unk44 = 0x10;
    burst.unk46 = 0xF;
    burst.unk48 = 0;
    burst.unk3C = 1;
    burst.unk40 = 1.0f;
    func_15154488(&burst, &burst.unk8, (s32)bounds, alpha, owner);

    ring.pos = pos;
    ring.u18 = 8.0f;
    ring.u1C = 10.0f;
    ring.u24 = D_800A2178;
    ring.u28 = D_800A217C;
    ring.u30 = 123.0f;
    ring.u34 = 104.0f;
    ring.u3C = 1.0f;
    ring.u44 = D_800A2180;
    ring.u0[1] = 0xFF;
    ring.u14 = 7;
    ring.u16 = 6;
    ring.u0[0] = 0;
    ring.u0[2] = -0x3F;
    ring.u0[3] = 0x18;
    ring.u20 = 0x23;
    ring.u22 = 0xB;
    ring.u2C = 0x64;
    ring.u2D = 0x64;
    ring.u38 = 1;
    ring.u39 = 1;
    ring.u40 = 1;
    func_151506E8(&ring, &ring.pos, (s32)bounds, alpha, owner);

    extra.u00 = 0.0f;
    extra.u08 = D_800A2184;
    rate = random_float() * 3.0f + 10.0f;
    extra.rate = rate;
    size = random_float() * 100.0f + 100.0f;
    extra.accel = size / (rate * rate);
    req.alpha = (u32)size;
    req.texture = 0x79;
    req.handlers = 0x200005;
    req.texSet = 0x4403;
    req.u04 = 0;
    req.u0C = 0;
    req.u10 = 0;
    req.u18[0] = 0xDC;
    req.u18[1] = 0xDC;
    req.u18[2] = 0xFF;
    req.color[3] = 0xFF;
    req.color[0] = 0xFF;
    req.color[1] = 0xFF;
    req.color[2] = 0xFF;
    req.u1C = 0xFF;
    req.pos[0] = ((s32 *)&pos)[0];
    req.pos[1] = ((s32 *)&pos)[1];
    req.pos[2] = ((s32 *)&pos)[2];
    req.angle[0] = ((s32 *)D_800A5860)[0];
    req.angle[1] = ((s32 *)D_800A5860)[1];
    req.angle[2] = ((s32 *)D_800A5860)[2];
    req.fadeStart = 1;
    req.fadeRate = 0xFF;
    req.u22 = 1;
    extra.size = size;
    req.u24 = 1.0f;
    flipA = (random_int() & 1) ? 0x40 : 0;
    flipB = (random_int() & 1) ? 0x80 : 0;
    req.flags = flipB | 0x4C000 | flipA;
    req.draw = 6;
    req.update = 6;
    req.blend = 0x27;
    req.u63 = -1;
    req.u64 = -1;
    req.u65 = 0;
    req.u5C = 0;
    req.u66 = 0xFF;
    req.vel[0] = ((s32 *)D_800A5860)[0];
    req.vel[1] = ((s32 *)D_800A5860)[1];
    req.vel[2] = ((s32 *)D_800A5860)[2];
    req.life = 300;
    req.halfW = 0.0f;
    req.halfH = 0.0f;
    req.value = 0.0f;
    fx = func_151307F0((s32)&req, 1, 0, 0x14, alpha, owner);
    if (fx != 0) {
        memcpy((u8 *)fx + 0xA8, &extra, 0x14);
    }
    func_151C384C(&pos, alpha, owner);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/obj_point_burst_spawn.s")
#endif

extern u8 D_80088F00;

/* was func_150FAFC0 */
void arc_bolts_spawn_once(u8 arg0, s32 arg1) {
    struct {
        u8 *unk0;
        u8 *unk4;
        f32 unk8;
    } tmp;
    struct260 *temp_v0;

    if (D_80088F00 == 0) {
        tmp.unk0 = D_800D34B8 + 0x71C;
        tmp.unk4 = D_800D34B8 + 0x6E8;
        tmp.unk8 = 0.0f;
        temp_v0 = func_15149130(300, -1, 0x57, -1, 0, 0x46, 0xC, arg0, arg1);
        if (temp_v0 != NULL) {
            D_80088F00 = 1;
        }
        if (temp_v0 != NULL) {
            memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
        }
    }
}

#ifdef NON_MATCHING
void func_1514470C(u8 *node, u8 *pos);
void lightning_bolt_spawn(u8 *arg0, u8 *arg1, u8 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9);
extern u8 D_80088ECC;   /* number of bolt styles */
extern u8 *D_80088ED0;  /* per style: 2 bytes, [1] = colour index */
extern f32 *D_80088ED4; /* per style: width */
// arc_bolts_emit: handler 25 of D_8008A980 (`void (u8 *)`). Accumulates (0.08 + 0.18 * random) * D_800BE9A4 bolts
// per frame in +0x30; for each whole bolt it spawns one (lightning_bolt_spawn) between the positions of the nodes +0x28 and
// +0x2C (func_1514470C), with a random style (D_80088ECC styles: colour D_80088ED0[2 * i + 1], width D_80088ED4[i] *
// (1..2)), length 30..55 (and 1 / length), life 750..752, and the object's +0x0C / +0x01 bytes.
/* was func_150FB06C */
void arc_bolts_emit(u8 *arg0) {
    u8 *ends = arg0 + 0x28;
    f32 from[3];
    f32 to[3];
    u32 style;
    f32 len;
    f32 width;

    ((f32 *) ends)[2] += (0.0800000057f + random_float() * 0.18f) * D_800BE9A4;
    while (1.0f < ((f32 *) ends)[2]) {
        func_1514470C(((u8 **) ends)[0], (u8 *) from);
        func_1514470C(((u8 **) ends)[1], (u8 *) to);
        style = (u8) ((u32) random_int() % D_80088ECC);
        len = random_float() * 25.0f + 30.0f;
        width = random_float();
        lightning_bolt_spawn((u8 *) from, (u8 *) to, D_80088ED0[style * 2 + 1], len, 1.0f / len,
                      (width * 1.0f + 1.0f) * D_80088ED4[style], 1, (u32) random_int() % 3 + 750, arg0[0xC], arg0[1]);
        ((f32 *) ends)[2] -= 1.0f;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/arc_bolts_emit.s")
#endif

/* was func_150FB264 */
void arc_bolts_handle_event(struct102 *arg0, s32 arg1, u8 arg2) {
    if ((arg2 == 0x4E) || (arg2 == 0x4F)) {
        node_destroy(arg0);
    }
}

/* was func_150FB2A8 */
void level_cue_switch_on(void) {
    func_1515F170(8, 0);
    func_1515F170(0xB, 1);
    func_151494E0((s32)(D_800D34B8 + 0x514), 0x30);
    func_151494E0(0, 0x4D);
}

/* was func_150FB2F8 */
void level_cue_switch_off(void) {
    func_1515F170(8, 1);
    func_1515F170(7, 0);
    func_151494E0((s32)(D_800D34B8 + 0x514), 0x31);
    func_151494E0(0, 0x4C);
}

/* was func_150FB348 */
void effect_flag2_handle_event(u8 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x53) {
        *(s32 *)(arg0 + 0x58) |= 2;
    } else if (arg2 == 0x54) {
        *(s32 *)(arg0 + 0x58) &= ~2;
    }
}

#ifdef NON_MATCHING
/* func_15157580's spec (0x58 bytes, the model effect it spawns). */
typedef struct {
    /* 0x00 */ u8 u00;
    /* 0x01 */ u8 u01;
    /* 0x02 */ u8 u02;
    /* 0x03 */ u8 u03;
    /* 0x04 */ u8 u04;
    /* 0x06 */ s16 span;
    /* 0x08 */ s32 u08;
    /* 0x0C */ s32 u0C;
    /* 0x10 */ s32 u10;
    /* 0x14 */ s32 flagsA;
    /* 0x18 */ s32 flagsB;
    /* 0x1C */ s32 u1C;
    /* 0x20 */ s32 u20;
    /* 0x24 */ s32 u24;
    /* 0x28 */ s32 u28;
    /* 0x2C */ u8 u2C;
    /* 0x2D */ u8 u2D;
    /* 0x2E */ u8 pad2E[2];
    /* 0x30 */ u8 col[8];
    /* 0x38 */ u8 u38;
    /* 0x3C */ s32 u3C;
    /* 0x40 */ u8 u40;
    /* 0x41 */ u8 u41;
    /* 0x44 */ struct { s32 x, y, z; } angle;
    /* 0x50 */ u8 pad50[4];
    /* 0x54 */ s16 u54;
    /* 0x56 */ s16 u56;
} ModelFxSpecFB398;

/* func_151559FC's spec (0x58 bytes; same layout as game_eu_FCE60's SpawnSpecCFB90). */
typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 scaleA;
    /* 0x0C */ f32 scaleB;
    /* 0x10 */ u8 kind;
    /* 0x12 */ s16 span;
    /* 0x14 */ s16 u14;
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
    /* 0x42 */ u8 pad42[2];
    /* 0x44 */ u8 player;
    /* 0x48 */ f32 u48;
    /* 0x4C */ f32 u4C;
    /* 0x50 */ f32 u50;
    /* 0x54 */ f32 u54;
} SpriteSpecFB398;

s32 func_15157580(void *spec, s32, f32, s32, s32, s32, s32, s32);
s32 func_151559FC(void *spec, s32 list, s32, s32, s32, s32, s32);
extern s16 D_800A20F0[]; /* 8 sprite kinds: 0xCE, 0xC5, then 0xC4 */

// score_banner_spawn: spawns the model effect 0x61 (func_15157580) and a row of 8 sprites (list 0xE, kinds
// D_800A20F0, x = -65 + 24.75 * i, y = 62, scale 16) for `span`, copying `span` into each new record (+0x120 for the
// model effect, +0x70 for the sprites). `flag` / `owner` are passed through to both spawners.
/* was func_150FB398 */
void score_banner_spawn(s16 span, u8 flag, s32 owner) {
    ModelFxSpecFB398 fx;
    SpriteSpecFB398 spr;
    s32 rec;
    u8 i;

    fx.u00 = 0x61;
    fx.u01 = 3;
    fx.u02 = 4;
    fx.u03 = 2;
    fx.u04 = 0;
    fx.span = span;
    fx.u08 = 0xA5;
    fx.u0C = 0x17;
    fx.u10 = 0;
    fx.flagsA = 0x200405;
    fx.flagsB = 0x60200;
    fx.u1C = 1;
    fx.u20 = 0x38;
    fx.u24 = 0x80;
    fx.u28 = 0x20;
    fx.u2C = 0;
    fx.u2D = 8;
    for (i = 0; i < 8; i++) {
        fx.col[i] = 0xFF;
    }
    fx.u38 = 0;
    fx.u3C = 0;
    fx.u40 = 0;
    fx.u41 = 1;
    fx.angle.x = ((s32 *)D_800A5860)[0];
    fx.angle.y = ((s32 *)D_800A5860)[1];
    fx.angle.z = ((s32 *)D_800A5860)[2];
    fx.u54 = 0xA;
    fx.u56 = 0x19;
    rec = func_15157580(&fx, 0, 1.0f, 0, 0, 2, flag, owner);
    if (rec != 0) {
        memcpy((u8 *)rec + 0x120, &span, sizeof(span));
    }

    spr.y = 62.0f;
    spr.scaleA = 16.0f;
    spr.scaleB = 16.0f;
    spr.span = span;
    spr.u14 = 0x29;
    spr.u16 = 0xA;
    spr.u18 = 0x19;
    spr.u1A = 0;
    for (i = 0; i < 9; i++) {
        spr.col[i] = 0xFF;
    }
    spr.u24 = 0;
    spr.u28 = 0x200405;
    spr.u2C = 0x60200;
    spr.u30 = 0x19;
    spr.u34 = 0x22;
    spr.u38 = 0x80;
    spr.u3C = 0x20;
    spr.u40 = 0;
    spr.u41 = 7;
    spr.player = 0;
    spr.u48 = 1.0f;
    spr.u4C = 1.0f;
    spr.u50 = 0.0f;
    spr.u54 = 0.0f;
    for (i = 0; i < 8; i++) {
        spr.x = i * 24.75f + -65.0f;
        spr.kind = D_800A20F0[i];
        rec = func_151559FC(&spr, 0xE, 0, 0, 2, flag, owner);
        if (rec != 0) {
            memcpy((u8 *)rec + 0x70, &span, sizeof(span));
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/score_banner_spawn.s")
#endif

#ifdef NON_MATCHING
void func_1515835C(u8 *arg0, u8 *arg1);

/* was func_150FB708 */
s32 score_banner_model_update(u8 *arg0) {
    struct {
        f32 u1C;
        f32 u20;
        f32 u24;
        f32 u28;
        f32 u2C;
    } sp;

    (*(f32 *)((u8 *)arg0 + 0x5C)) = 0.0f;
    (*(f32 *)((u8 *)arg0 + 0x54)) = -95.0f;
    (*(f32 *)((u8 *)arg0 + 0x58)) = -80.0f;
    sp.u1C = 0.0f;
    sp.u20 = 0.0f;
    sp.u24 = 0.0f;
    sp.u28 = 0.3f;
    sp.u2C = 0.3f;
    func_1515835C(arg0, &sp.u1C);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/score_banner_model_update.s")
#endif
s32 func_151584F0(s32, s32, s32, s32, s32);
s32 func_151D76BC(s32, s32, s32, s32, s32);
/* was func_150FB768 */
void banner_sprite_draw(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_151584F0(func_151D76BC(arg0, arg1, arg2, arg3, arg4), arg1, arg2, arg3, arg4);
}

/* was func_150FB7C0 */
void fade_alpha_from_timer(u8 *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    if ((arg2 - arg3) < arg1) {
        *arg0 = (arg2 - arg1) * arg4;
        return;
    }
    *arg0 = 0xFF;
}

/* was func_150FB81C */
s32 banner_model_fade_update(u8 *arg0) {
    fade_alpha_from_timer(arg0 + 0x43, *(s16 *)(arg0 + 0x16), *(s16 *)(arg0 + 0x120), *(s16 *)(arg0 + 0x64), *(s16 *)(arg0 + 0x66));
    return 1;
}

/* was func_150FB860 */
s32 banner_sprite_fade_update(u8 *arg0) {
    fade_alpha_from_timer(arg0 + 0x2E, *(s16 *)(arg0 + 0x22), *(s16 *)(arg0 + 0x70), *(s16 *)(arg0 + 0x26), *(s16 *)(arg0 + 0x28));
    return 1;
}

#ifdef NON_MATCHING
void bone_point_spark_spray(s32, u8, s32, s32, s32, u8, s32);
void func_15145EA4(f32 **, f32 **, void *, s32);
void func_151D49B8(u8 *, u8 *, s32, u8 *, f32, u8, s32);
extern s32 D_800A2100;
extern s32 D_800A210C;
extern s32 D_800A2118;
extern s32 D_800A2124;

/* was func_150FB8A4 */
void obj_bone14_spark_burst(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        s32 * u2C;
        f32 * u30;
        f32 * u34;
        s32 * u38;
        s32 * u3C;
        s32 * u40;
        s32 u44;
        u8 pad48[0x8];
        s32 u50;
        u8 pad54[0x8];
        s32 u5C;
        u8 pad60[0x8];
        s32 u68;
        u8 pad6C[0xC];
        s32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        s32 u94;
    } sp;
    s32 temp_a2;

    (*(s32 *)((u8 *)(&sp.u68) + 0)) = (s32) (*(s32 *)((u8 *)(&D_800A2100) + 0));
    (*(s32 *)((u8 *)(&sp.u68) + 4)) = (s32) (*(s32 *)((u8 *)(&D_800A2100) + 4));
    (*(s32 *)((u8 *)(&sp.u68) + 8)) = (s32) (*(s32 *)((u8 *)(&D_800A2100) + 8));
    (*(s32 *)((u8 *)(&sp.u5C) + 0)) = (s32) (*(s32 *)((u8 *)(&D_800A210C) + 0));
    (*(s32 *)((u8 *)(&sp.u5C) + 4)) = (s32) (*(s32 *)((u8 *)(&D_800A210C) + 4));
    (*(s32 *)((u8 *)(&sp.u5C) + 8)) = (s32) (*(s32 *)((u8 *)(&D_800A210C) + 8));
    (*(s32 *)((u8 *)(&sp.u50) + 0)) = (s32) (*(s32 *)((u8 *)(&D_800A2118) + 0));
    (*(s32 *)((u8 *)(&sp.u50) + 4)) = (s32) (*(s32 *)((u8 *)(&D_800A2118) + 4));
    (*(s32 *)((u8 *)(&sp.u50) + 8)) = (s32) (*(s32 *)((u8 *)(&D_800A2118) + 8));
    (*(s32 *)((u8 *)(&sp.u44) + 0)) = (s32) (*(s32 *)((u8 *)(&D_800A2124) + 0));
    (*(s32 *)((u8 *)(&sp.u44) + 4)) = (s32) (*(s32 *)((u8 *)(&D_800A2124) + 4));
    (*(s32 *)((u8 *)(&sp.u44) + 8)) = (s32) (*(s32 *)((u8 *)(&D_800A2124) + 8));
    if ((*(s32 *)((u8 *)arg0 + 0x1D4)) != 0) {
        sp.u38 = &sp.u68;
        sp.u3C = &sp.u50;
        sp.u40 = &sp.u44;
        sp.u2C = &sp.u94;
        sp.u30 = &sp.u88;
        sp.u34 = &sp.u7C;
        temp_a2 = (*(s32 *)((u8 *)arg0 + 0x1D4)) + 0x380;
        sp.u78 = temp_a2;
        func_15145EA4(&sp.u38, &sp.u2C, temp_a2, 3);
        sp.u7C -= sp.u88;
        sp.u80 -= sp.u8C;
        sp.u84 -= sp.u90;
        bone_point_spark_spray(arg0, 0xE, &sp.u68, &sp.u5C, &sp.u94, (s32) arg1, arg2);
        func_151D49B8(&sp.u88, &sp.u7C, sp.u78, arg0, 1.0f, (s32) arg1, arg2);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/obj_bone14_spark_burst.s")
#endif