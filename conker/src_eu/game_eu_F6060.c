#include <ultra64.h>
#include "functions.h"
#include "variables.h"

/* P162: E10 / D_eu_800BE900 moved up from below wobblers_update_view0 (used by wobblers_update's NM C) */
typedef struct { u8 u0; u8 pad1[3]; s16 u4; u8 pad6[4]; } E10;
extern E10 *D_eu_800BE900;

// wobblers_update: the 10 records at D_eu_800BE900 (s8 dir +2, s16 pos +4, s16 speed +6, s16 target speed +8):
// speed moves toward the target (sign follows the current speed) by at most g_frame_ticks * 16, then pos advances by
// speed * dir * g_frame_delta and bounces inside 0 .. 0x4FF (dir flips)
/* was func_150C8850 */
void wobblers_update(void) {
    s32 i;
    u8 *r;
    s32 speed;
    s32 target;
    s32 diff;
    s32 step;
    s32 pos;

    for (i = 0; i < 10; i++) {
        r = (u8 *)&D_eu_800BE900[i];
        speed = *(s16 *)(r + 6);
        if (speed != *(s16 *)(r + 8)) {
            target = *(s16 *)(r + 8);
            if (speed < 0) {
                target = -target;
            }
            diff = target - speed;
            step = g_frame_ticks * 16;
            if ((diff < 0 ? -diff : diff) < step) {
                *(s16 *)(r + 6) = target;
            } else {
                *(s16 *)(r + 6) = speed + step * (diff >= 0 ? 1 : -1);
            }
            speed = *(s16 *)(r + 6);
        }
        *(s16 *)(r + 4) += speed * *(s8 *)(r + 2) * g_frame_delta;
        pos = *(s16 *)(r + 4);
        if (pos >= 0x500) {
            *(s16 *)(r + 4) = 0x500 - (s16)(pos - 0x500);
            *(s8 *)(r + 2) = -*(s8 *)(r + 2);
            if (*(s16 *)(r + 4) >= 0x500) {
                *(s16 *)(r + 4) = 0x4FF;
            }
        } else if (pos < 0) {
            *(s16 *)(r + 4) = -pos;
            *(s8 *)(r + 2) = -*(s8 *)(r + 2);
            if (*(s16 *)(r + 4) < 0) {
                *(s16 *)(r + 4) = 0;
            }
        }
    }
}

/* was func_150C89F4 */
void wobblers_update_view0(s32 arg0) {
    if (arg0 == 0) {
        wobblers_update();
    }
}

s32 shooting_star_set_rate(s32);
/* was func_150C851C */
void wobblers_set_intensity(s32 arg0) {
    s32 i;
    s32 v;
    s32 lo;
    s32 range;

    if (D_eu_800BE900 != NULL) {
        shooting_star_set_rate(arg0);
        range = ((arg0 * 50) >> 8) + 50;
        lo = (arg0 * 300) >> 8;
        for (i = 0; i < 10; i++) {
            v = lo;
            v += random_int() % (u32)range;
            *(s16 *)&D_eu_800BE900[i].pad6[2] = v;
        }
    }
}

typedef struct { s32 *a[2]; } P2;
extern P2 D_eu_80088BB0;
s32 texture_cache_lookup(s32, s32 *, s32, s32);
/* was func_150C8B00 */
Gfx *wobblers_set_tex_segments(Gfx *gfx) {
    s32 i;
    s32 buf[3];
    s32 lvl;
    P2 tabs = D_eu_80088BB0;

    for (i = 0; i < 10; i++) {
        lvl = D_eu_800BE900[i].u4 >> 8;
        if (lvl < 0) {
            lvl = 0;
        } else if (lvl >= 5) {
            lvl = 4;
        }
        if (D_eu_800BE900[i].u0 >= 2) {
            D_eu_800BE900[i].u0 = 0;
        }
        lvl = texture_cache_lookup(tabs.a[D_eu_800BE900[i].u0][lvl], buf, 3, 0);
        gSPSegment(gfx++, i + 1, lvl);
    }
    return gfx;
}

u8 *obj_spawn_child_at_joint(struct127 *, s32, s32, f32, f32, f32, f32, f32, f32, f32, s32);
void mtxf_decompose(f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
extern f32 g_part_at_mtx_k_08c0; /* was D_800A08C0 */
extern f32 g_part_at_mtx_k_08c4; /* was D_800A08C4 */
extern f32 g_part_at_mtx_k_08c8; /* was D_800A08C8 */
extern f32 g_part_at_mtx_k_08cc; /* was D_800A08CC */
/* was func_150C8C30 */
s32 obj_spawn_part_at_mtx(u8 *arg0, struct127 *arg1) {
    u8 *v;
    u8 *e;
    u8 i;
    u8 *p;
    s16 t;
    s32 pad[2]; // fakematch: frame 8 bytes (unknown named locals)
    f32 m[4][4];
    f32 x;
    f32 y;
    f32 z;
    f32 u0;
    f32 u1;
    f32 u2;
    f32 r0;
    f32 r1;
    f32 r2;

    v = *(u8 **)((u8 *)arg1 + 0x2D0);
    if (v == NULL) {
        return 0;
    }
    if ((*(u16 *)((u8 *)arg1 + 0x84) == 0x14 && 10.0f < *(f32 *)(v + 8)) || *(u16 *)((u8 *)arg1 + 0x84) == 0x23) {
        i = g_dl_buf_index;
        p = *(u8 **)(arg0 + 0x34);
        p += (i == 0) << 6;
        guMtxL2F(m, (Mtx *)p);
        m[0][3] = 0.0f;
        m[1][3] = 0.0f;
        m[2][3] = 0.0f;
        m[3][3] = 1.0f;
        mtxf_decompose((f32 *)m, &x, &y, &z, &r0, &r1, &r2, &u0, &u1, &u2);
        e = obj_spawn_child_at_joint(arg1, -1, 0x4E, 0.0f, 0.0f, 0.0f, 0.0f, g_part_at_mtx_k_08c0, g_part_at_mtx_k_08c4, g_part_at_mtx_k_08c8, 0xC8);
        *(f32 *)(e + 0x14) = x;
        *(f32 *)(e + 0x18) = y;
        *(f32 *)(e + 0x1C) = z;
        *(f32 *)(e + 0xB8) = r0;
        *(f32 *)(e + 0x40) = r1;
        *(f32 *)(e + 0xC4) = r2;
        t = (*(f32 *)(e + 0x40) - 90.0f) * g_part_at_mtx_k_08cc;
        *(s16 *)(e + 0x76) = t;
        *(s16 *)(e + 0x7A) = t;
        return 1;
    }
    return 0;
}

/* P197 */
s32 memcpy(u8 *, u8 *, s32);
f32 sinf(f32);
f32 cosf(f32);

// ring_effect_create: P197: creates a kind-0x31 record (node_alloc, view `view`, group arg3) for the 0x30-byte
// spec `spec` (copied to +0x10; spec +0x14 = n points) with `extra` more bytes: a table of n (sin, cos) pairs at
// +0x368 (+0x360 points at it) for angles 0, 2pi/n, ... (step at +0x48), then areas at +0x54 (+0x368 + 8n),
// +0x58 (+0x3B8 + 0x58n) and +0x364 (+0x408 + 0xA8n); +0x40 / +0x44 / +0x50 = 0, s16 +0x4C = s16 +0x28.
// Returns the record, NULL when there is none.
/* was func_150C8DD0 */
u8 *ring_effect_create(u8 *spec, s32 extra, s32 view, s32 arg3) {
    u8 *rec;
    s32 i;
    f32 a;

    rec = (u8 *) node_alloc(0x31, arg3, extra + *(s32 *) (spec + 0x14) * 0xA8 + 0x408, 1, view & 0xFF, 1);
    if (rec == NULL) {
        return NULL;
    }
    memcpy(rec + 0x10, spec, 0x30);
    *(u8 **) (rec + 0x360) = rec + 0x368;
    *(u8 **) (rec + 0x54) = rec + 0x368 + *(s32 *) (spec + 0x14) * 8;
    *(u8 **) (rec + 0x58) = rec + 0x3B8 + *(s32 *) (spec + 0x14) * 0x58;
    *(f32 *) (rec + 0x40) = 0.0f;
    *(f32 *) (rec + 0x44) = 0.0f;
    *(u8 **) (rec + 0x364) = rec + 0x408 + *(s32 *) (spec + 0x14) * 0xA8;
    *(f32 *) (rec + 0x50) = 0.0f;
    *(s16 *) (rec + 0x4C) = *(s16 *) (rec + 0x28);
    *(f32 *) (rec + 0x48) = 6.2831855f / (f32) *(s32 *) (rec + 0x24);
    for (i = 0, a = 0.0f; i < *(s32 *) (rec + 0x24); i++, a += *(f32 *) (rec + 0x48)) {
        (*(f32 **) (rec + 0x360))[i * 2] = sinf(a);
        (*(f32 **) (rec + 0x360))[i * 2 + 1] = cosf(a);
    }
    return rec;
}

/* P220: readable C for ring_effect_update (game_eu_F6060, 212 words): update of the kind-0x31 ring effect (descriptor
 * at D_8008C238: update ring_effect_update, draw ring_effect_draw). */
extern void (*g_ring_spawn_fns[])(u8 *, f32 *, u8, f32, f32); /* spawn handlers: ring_spawn_particle, ring_spawn_debris; was D_80088BF8 */
extern s32 (*g_ring_node_fns[])(u8 *);                        /* node handlers (0 = free the node): [1] shockwave_hit_objects; was D_80088C00 */
extern s32 (*g_ring_node_fns_1[])(u8 *);                        /* = g_ring_node_fns + 1: [0] shockwave_hit_objects; was D_80088C00; was D_80088C04 */
extern f32 g_ring_two_pi; /* 2 pi; was D_800A08FC */
extern f32 g_ring_spawn_max_dist_sq; /* max squared horizontal distance of a spawn point: 10894295 (3300.6^2); was D_800A0900 */
extern f32 g_ring_deg_to_angle; /* 256 / 360: degrees -> angle byte; was D_800A0904 */
f32 angle_byte_cos(u8);
s32 random_int(void);
void node_destroy(struct102 *arg0);

// ring_effect_update: per frame for a ring effect node: counts the life timer (+0x28, flag +0x1C & 1) down, grows
// the radius +0x44 by +0x20 per second, sets the fade value +0x40 (+0x2C per tick after +0x2A, +0x34 per tick before
// +0x30), spawns handler +0x3C's particles at a rate of +0x38 per radian of ring per second (each at a random angle
// around the camera's view direction, only within g_ring_spawn_max_dist_sq of the world origin), calls handler +0x3D with the old
// radius (the only entry ignores it) and handler +0x1D; frees the node when the timer runs out or +0x1D returns 0.
/* was func_150C8F68 */
void ring_effect_update(u8 *node) {
    u8 dead = 0;

    if (node[0x1C] & 1) {
        *(s16 *)(node + 0x28) -= g_frame_ticks;
        if (*(s16 *)(node + 0x28) < 0) {
            dead = 1;
        }
    }
    if (!dead) {
        f32 oldRadius = *(f32 *)(node + 0x44);
        s16 t;
        *(f32 *)(node + 0x44) = oldRadius + *(f32 *)(node + 0x20) * g_frame_step_f;
        t = *(s16 *)(node + 0x28);
        if (*(s16 *)(node + 0x2A) < t) {
            *(f32 *)(node + 0x40) = (f32)(s16)(*(s16 *)(node + 0x4C) - t) * *(f32 *)(node + 0x2C);
        }
        if (t < *(s16 *)(node + 0x30)) {
            *(f32 *)(node + 0x40) = (f32)t * *(f32 *)(node + 0x34);
        }
        if ((s8)node[0x3C] != -1) {
            *(f32 *)(node + 0x50) += *(f32 *)(node + 0x38) * g_frame_step_f * (g_ring_two_pi * *(f32 *)(node + 0x44));
            while (1.0f < *(f32 *)(node + 0x50)) {
                s32 view = (s32)(*(f32 *)((u8 *)g_player_views + g_cur_view_player * 0x9A0 + 0x380) * g_ring_deg_to_angle);
                s32 a = (u32)random_int() % 81 + view - 0x28;
                f32 s = angle_byte_cos((u8)(a - 0x40));
                f32 c = angle_byte_cos((u8)a);
                f32 pos[3]; /* sp74 */
                pos[0] = *(f32 *)(node + 0x10) + s * *(f32 *)(node + 0x44);
                pos[1] = *(f32 *)(node + 0x14);
                pos[2] = *(f32 *)(node + 0x18) + c * *(f32 *)(node + 0x44);
                if (pos[0] * pos[0] + pos[2] * pos[2] < g_ring_spawn_max_dist_sq) {
                    g_ring_spawn_fns[(s8)node[0x3C]](node, pos, (u8)a, s, c);
                }
                *(f32 *)(node + 0x50) -= 1.0f;
            }
        }
        if ((s8)node[0x3D] != -1) {
            /* the asm also passes oldRadius in a1; the table's only entry (shockwave_hit_objects) takes the node alone */
            g_ring_node_fns_1[(s8)node[0x3D]](node);
        }
        if ((s8)node[0x1D] != -1) {
            if (g_ring_node_fns[(s8)node[0x1D]](node) == 0) {
                dead = 1;
            }
        }
    }
    if (dead) {
        node_destroy((struct102 *)node);
    }
}

/* P222: readable C for ring_effect_draw (game_eu_F6060, 767 words): draw callback of render layer 0x31 (the ring
 * effect; layer at g_node_type_table + 0x31 * 0x34: update ring_effect_update, draw ring_effect_draw). */
typedef struct {
    s32 n;          /* 5 */
    f32 (*pt)[2];   /* D_800A08D0: (radial offset, height) */
} RingProfile;
extern RingProfile g_ring_profile; /* was D_80088BC0 */
extern s32 *g_ring_tex_id_ptr;  /* the ring texture's id; was D_80091234 */
extern s32 g_render_mode_pairs[]; /* render mode pairs (2 words each); was D_800A4EA8 */
s32 texture_cache_lookup(s32, s32 *, s32, s32);
Gfx *gfx_geometry_mode_cached(Gfx *gfx, s32 set, s32 clear);
Gfx *gfx_env_color_cached(Gfx *gfx, s32 r, s32 g, s32 b, s32 a, u8 *arg5);
Gfx *gfx_prim_color_cached(Gfx *gfx, s32 m, s32 l, s32 r, s32 g, s32 b, s32 a, u8 *arg7);
Gfx *gfx_other_mode_cached(Gfx *gfx, s32 arg1, s32 arg2, u8 *arg3);
Gfx *gfx_set_combine_mode(Gfx *arg0, u8 arg1, u8 *arg2);
void ground_colour_by_depth(f32, f32 *, f32 *, f32 *);

#define RING_DL(a, b) (gdl->words.w0 = (a), gdl->words.w1 = (b), gdl++)

// ring_effect_draw: draws a ring effect node: render state (geometry mode, colours, combiner 0x21, render mode
// g_render_mode_pairs entry 14), the ring texture (texture_cache_lookup(*g_ring_tex_id_ptr): CI4 with 6 mip levels in tiles 0..5, its TLUT is
// the last 0x20 bytes) and a surface of revolution: the cross-section g_ring_profile (radial offset, height, scaled by
// +0x40) swept around the centre +0x10 / +0x14 / +0x18 at radius +0x44, one vertex column per direction (+0x360:
// cos / sin pairs, +0x24 of them, the last column repeats the first). Columns farther than 3300.6 from the world
// origin (x / z) are flat and transparent. Vertex colours: ground_colour_by_depth(z); texture coordinates from x / z. The
// vertices go to the node's buffer for this frame (+0x54[g_dl_buf_index]); after each new column, gSPVertex of it and
// the previous one and two triangles per cross-section edge. arg2 (the layer's argument) is unused. Returns the DL end.
/* was func_150C92B8 */
Gfx *ring_effect_draw(Gfx *gdl, u8 *node, s16 arg2) {
    u8 flag = 1;
    s32 size;
    s32 tex;
    Vtx *buf;
    Vtx *v;
    f32 *dir;
    f32 cx, cz, px, py, x, z, r, g, b;
    s32 near;
    s32 nv = 0;
    s32 col, i, n;

    gdl = gfx_geometry_mode_cached(gdl, 0x200205, 0x70400);
    gdl = gfx_env_color_cached(gdl, 0xFF, 0xFF, 0xFF, 0xFF, &flag);
    gdl = gfx_prim_color_cached(gdl, 0xF2, 0, 0xFF, 0xFF, 0xFF, 0xFF, &flag);
    gdl = gfx_set_combine_mode(gdl, 0x21, &flag);
    gdl = gfx_other_mode_cached(gdl, 0x1DACA0, g_render_mode_pairs[29] | g_render_mode_pairs[28], &flag);
    tex = texture_cache_lookup(*g_ring_tex_id_ptr, &size, 3, 0);
    gSPTexture(gdl++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    RING_DL(0xFD500000, tex);        /* texture image: CI, 16-bit words (block load) */
    RING_DL(0xF5500000, 0x07000000); /* tile 7: load tile */
    RING_DL(0xF3000000, 0x073EF000); /* load block 0x3EF+1 texels */
    RING_DL(0xF5400400, 0x01018050); /* tile 1 (mip 1) */
    RING_DL(0xF2402402, 0x0147E4FE);
    RING_DL(0xF5400280, 0x02014441); /* tile 2 */
    RING_DL(0xF2202202, 0x0223E27E);
    RING_DL(0xF54002A0, 0x03010832); /* tile 3 */
    RING_DL(0xF2102102, 0x0311E13E);
    RING_DL(0xF54002B0, 0x0400CC23); /* tile 4 */
    RING_DL(0xF2082082, 0x0408E09E);
    RING_DL(0xF54002B8, 0x05009014); /* tile 5 */
    RING_DL(0xF2042042, 0x0504604E);
    RING_DL(0xF56004BC, 0x00017C5F); /* tile 0 (mip 0) */
    RING_DL(0xF2802802, 0x0087E87E);
    RING_DL(0xFD100000, tex + size - 0x20); /* TLUT image: the texture's last 16 colours */
    RING_DL(0xF5600100, 0x06000000);         /* tile 6: TLUT at tmem 0x100 */
    gDPLoadSync(gdl++);
    gDPLoadTLUTCmd(gdl++, 6, 15);
    gSPTexture(gdl++, 0xFFFF, 0xFFFF, 4, G_TX_RENDERTILE, G_ON);

    buf = ((Vtx **) (node + 0x54))[g_dl_buf_index];
    /* column 0 is direction 0; column col > 0 is direction col (the last one, col == +0x24, wraps to 0) */
    for (col = 0; col == 0 || col <= *(s32 *) (node + 0x24); col++) {
        dir = *(f32 **) (node + 0x360) + (col == *(s32 *) (node + 0x24) ? 0 : col) * 2;
        cx = *(f32 *) (node + 0x10) + *(f32 *) (node + 0x44) * dir[0];
        cz = *(f32 *) (node + 0x18) + *(f32 *) (node + 0x44) * dir[1];
        near = (cx * cx + cz * cz < 10894295.0f);
        v = buf + nv;
        for (i = 0; i < g_ring_profile.n; i++, v++) {
            px = g_ring_profile.pt[i][0] * *(f32 *) (node + 0x40);
            py = g_ring_profile.pt[i][1] * *(f32 *) (node + 0x40);
            x = cx + px * dir[0];
            z = cz + px * dir[1];
            v->v.ob[0] = x;
            v->v.ob[1] = (near ? py : 0.0f) + *(f32 *) (node + 0x14);
            v->v.ob[2] = z;
            v->v.tc[0] = -((x * 0.03988662f + z * 0.03713737f + 110.230064f) * 32.0f);
            v->v.tc[1] = -((x * 0.054123953f + z * -0.058144543f + 50.14429f) * 32.0f);
            ground_colour_by_depth(z, &r, &g, &b);
            nv++;
            v->v.cn[0] = (u32) r;
            v->v.cn[1] = (u32) g;
            v->v.cn[2] = (u32) b;
            v->v.cn[3] = near ? 0xFF : 0;
        }
        if (col == 0) {
            continue;
        }
        n = g_ring_profile.n;
        gSPVertex(gdl++, ((Vtx **) (node + 0x54))[g_dl_buf_index] + (nv - n * 2), n * 2, 0);
        for (i = 0; i < g_ring_profile.n - 1; i++) {
            gSP1Triangle(gdl++, i, i + 1, i + g_ring_profile.n + 1, 0);
            gSP1Triangle(gdl++, i, i + g_ring_profile.n + 1, i + g_ring_profile.n, 0);
        }
    }
    return gdl;
}

s32 particle_spawn_basic(void *, s32, s32, u8, s32);
typedef struct {
    s32 x[3];
} V3i_B8AA0;
void vec3_from_angles_byte(s16, s16, f32, void *);
/* was func_150C9EB4 */
void ring_spawn_particle(u8 *arg0, f32 *arg1, u8 arg2, f32 arg3, f32 arg4) { /* P220: arg3 / arg4 = sin / cos of the spawn angle (unused) */
    struct {
        s32 u34;
        s32 u38;
        s16 u3C;
        s16 u3E;
        s32 u40;
        s32 u44;
        s8 u48;
        s8 u49;
        s8 u4A;
        u8 u4B;
        s8 u4C;
        s8 u4D;
        s8 u4E;
        s8 u4F;
        u8 u50;
        s8 u51;
        s16 u52;
        s16 u54;
        s16 u56;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64[3];
        f32 u70;
        f32 u74;
        f32 u78;
        s32 u7C[3];
        f32 u88;
        s32 u8C;
        u8 pad90[4];
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        s8 u98;
        s8 u99;
        u8 pad9A[10];
    } sp;
    s32 b;
    s16 r;
    f32 f;
    s32 a;

    sp.u51 = 0x26;
    sp.u3C = 0xC01;
    sp.u34 = 0x200005;
    sp.u38 = 0;
    sp.u3E = (random_int() % 81U) + 0x19;
    sp.u40 = 0;
    sp.u44 = 0;
    sp.u94 = 5;
    sp.u95 = 5;
    sp.u48 = 0;
    sp.u49 = 0;
    sp.u4A = 0;
    sp.u4B = 0xFF;
    sp.u4C = 0;
    sp.u4D = 0;
    sp.u4E = 0;
    sp.u4F = (random_int() % 156U) + 0x64;
    sp.u50 = 0xFF;
    sp.u5C = sp.u60 = (random_float() * 500.0f) + 500.0f;
    *(V3i_B8AA0 *)sp.u64 = *(V3i_B8AA0 *)arg1;
    sp.u70 = 0.0f;
    sp.u74 = 0.0f;
    sp.u78 = 0.0f;
    sp.u88 = ((random_float() * 550.0f) + -1416.0f) * 0.001f;
    sp.u52 = 0x14;
    sp.u54 = 0xC;
    sp.u56 = 0;
    sp.u58 = 1.0f;
    if (random_int() & 1) {
        a = 0x40;
    } else {
        a = 0;
    }
    if (random_int() & 1) {
        b = 0x80;
    } else {
        b = 0;
    }
    sp.u8C = b | 7 | a | 0x200;
    sp.u96 = -1;
    sp.u97 = -1;
    r = (random_int() % 11U) - 0x12;
    f = (*(f32 *)(arg0 + 0x20) * 0.961f) + ((*(f32 *)(arg0 + 0x20) * 0.24300002f) * random_float());
    vec3_from_angles_byte(arg2, r, f, sp.u7C);
    particle_spawn_basic(&sp, 1, 0, arg0[0xC], arg0[1]);
}

// shockwave_hit_objects: P213: handler 1 of the effect node table g_ring_node_fns (dispatched by ring_effect_update with the
/* node only; the node is freed when the result is 0). Every live object (state != 0) on the ground (unk28 < 20)
 * and not immune, that is a player (state 1) or type 0x53, is hit when the ring of radius node +0x44 has reached
 * it: ring - (horizontal distance to the node centre +0x10 / +0x18 - 100, 150 more for an unlifted type 0x53)
 * in [0, 250). Type 0x53 gets disable_run = 10, its script restarted (unk218 NULL) at command 0x13 (0x14 when its
 * holder g_objects[unk124] holds something, unk65); others the hit obj_send_hit(obj, 0x6000E, facing, -1).
 * The asm returns its leftover v0: the state of the last object, or obj_send_hit's result when that one was hit;
 * the C keeps that value. */
s32 obj_send_hit(struct127 *obj, s32 flags, u16 val, s32 arg3);
/* was func_150CA0DC */
s32 shockwave_hit_objects(u8 *node) {
    struct127 *o;
    s32 ret = 0;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 reach;

    for (o = g_objects; o != &g_objects[25]; o++) {
        ret = o->interaction_state;
        if (ret == 0 || !(o->unk28 < 20.0f) || o->immune != 0) {
            continue;
        }
        if (o->id != 0x53 && ret != 1) {
            continue;
        }
        dx = o->x_position - *(f32 *)(node + 0x10);
        dz = o->z_position - *(f32 *)(node + 0x18);
        dist = sqrtf(dx * dx + dz * dz) - 100.0f;
        if (o->id == 0x53 && o->unk13C == 0) {
            dist -= 150.0f;
        }
        reach = *(f32 *)(node + 0x44) - dist;
        if (!(0.0f <= reach) || !(reach < 250.0f)) {
            continue;
        }
        if (o->id == 0x53) {
            o->disable_run = 10;
            o->unk218 = NULL;
            o->unk232 = 0x13;
            if (g_objects[o->unk124].unk65 != 0) {
                o->unk232 = 0x14;
            }
        } else {
            ret = obj_send_hit(o, 0x6000E, o->unk7A, -1);
        }
    }
    return ret;
}

extern f32 g_ring_debris_k_0950; /* was D_800A0950 */
extern f32 g_ring_debris_k_0954; /* was D_800A0954 */
extern f32 g_ring_debris_k_0958; /* was D_800A0958 */
extern f32 g_ring_debris_k_0960; /* was D_800A0960 */
extern f32 g_ring_debris_k_0964; /* was D_800A0964 */
extern f32 g_ring_debris_k_0968; /* was D_800A0968 */
/* P201: ground_colour_by_depth was called here without a prototype, with arg0 (a pointer) as its float argument: the
 * N64 code leaves f12 (whatever the caller ring_effect_update had there) and a0 is ignored, and on wasm the call has the
 * wrong signature. The port passes the effect position's z (as landing_dust_burst does with its own position). */
void ground_colour_by_depth(f32, f32 *, f32 *, f32 *);

/* was func_150CA2C4 */
void ring_spawn_debris(u8 *arg0, u8 *arg1, u8 arg2, f32 arg3, f32 arg4) { /* P220: arg3 / arg4 = the spawn angle's sin / cos (ring_effect_update passes them; unused) */
    struct {
        s32 u28;
        s32 u2C;
        s32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        f32 u50;
        f32 u54;
        f32 u58;
        s32 u5C;
        u8 pad60[0x8];
        s32 u68;
        u8 pad6C[0x8];
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        s32 u84;
        s16 u88;
        s16 u8A;
        s8 u8C;
        u8 pad8D[0x3];
        s32 u90;
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        s8 u98;
        s8 u99;
        s8 u9A;
        s8 u9B;
        s8 u9C;
        u8 pad9D[0x1];
        s8 u9E;
        u8 pad9F[0x1];
        s32 uA0;
        s8 uA4;
        u8 padA5[0x1];
        s16 uA6;
        s16 uA8;
    } sp;
    s32 sp20;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f4;

    ground_colour_by_depth(*(f32 *) (arg1 + 8), &sp.u30, &sp.u2C, &sp.u28);
    (*(s32 *)((u8 *)(&sp.u5C) + 0)) = (s32) (*(s32 *)((u8 *)arg1 + 0));
    (*(s32 *)((u8 *)(&sp.u5C) + 4)) = (s32) (*(s32 *)((u8 *)arg1 + 4));
    (*(s32 *)((u8 *)(&sp.u5C) + 8)) = (s32) (*(s32 *)((u8 *)arg1 + 8));
    sp.u50 = 1.0f;
    sp.u54 = 1.0f;
    sp.u58 = 1.0f;
    sp.u84 = 0x29E8;
    sp.u44 = random_float() * 360.0f;
    sp.u48 = random_float() * 360.0f;
    temp_f18 = random_float() * 360.0f;
    sp.u8A = 0x20;
    sp.u38 = g_ring_debris_k_0950;
    sp.u4C = temp_f18;
    sp.u78 = 0.0f;
    sp.u34 = 1.0f;
    sp20 = random_int();
    vec3_from_angles_byte((s16) arg2, (s16) (((u32) sp20 % 26U) - 0x2D), ((random_float() * 81.0f) + 60.0f) * (*(f32 *)((u8 *)arg0 + 0x20)) * g_ring_debris_k_0954, &sp.u68);
    sp.u74 = ((random_float() * 260.0f) + -130.0f) * g_ring_debris_k_0958;
    sp.u7C = ((random_float() * 260.0f) + -130.0f) * g_ring_debris_k_0958;
    sp.u88 = (random_int() % 41U) + 0x28;
    sp.u80 = ((random_float() * g_ring_debris_k_0960) + g_ring_debris_k_0964) * g_ring_debris_k_0968;
    temp_f4 = random_float() * 400.0f;
    sp.u8C = 0;
    sp.u90 = 0;
    temp_f2 = (temp_f4 + 199.0f) * g_ring_debris_k_0968;
    sp.u3C = temp_f2;
    sp.u40 = temp_f2;
    sp.u94 = (random_int() % 101U) + 0x9B;
    sp.u95 = 7;
    sp.u96 = 0;
    sp.u97 = 0;
    sp.u98 = 0;
    sp.u99 = 0;
    sp.u9A = 0;
    sp.u9B = 0;
    sp.u9C = 0;
    sp.u9E = 2;
    sp.uA0 = 0;
    sp.uA4 = 0;
    sp.uA6 = 0x20;
    sp.uA8 = 7;
    mdl_particle_spawn(&sp.u34, 3, 0xFF, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
}
/* was func_150CA57C */
s32 particle_ballistic_update(u8 *arg0) {
    *(f32 *)(arg0 + 0x38) += *(f32 *)(arg0 + 0x44) * g_frame_step_f;
    *(f32 *)(arg0 + 0x3C) += (*(f32 *)(arg0 + 0x48) * g_frame_step_f) + (*(f32 *)(arg0 + 0x5C) * g_frame_step_f * g_frame_step_f * 0.5f);
    *(f32 *)(arg0 + 0x40) += *(f32 *)(arg0 + 0x4C) * g_frame_step_f;
    *(f32 *)(arg0 + 0x48) += *(f32 *)(arg0 + 0x5C) * g_frame_step_f;
    *(f32 *)(arg0 + 0x20) += *(f32 *)(arg0 + 0x50) * g_frame_step_f;
    *(f32 *)(arg0 + 0x24) += *(f32 *)(arg0 + 0x54) * g_frame_step_f;
    *(f32 *)(arg0 + 0x28) += *(f32 *)(arg0 + 0x58) * g_frame_step_f;
    return 1;
}

// landing_dust_burst: P201: the burst of effects under the character `obj` (the only caller, objfx_ca150, passes
// g_cur_obj) when it lands / stamps: position = obj x, y + 100, z; the ground below it (collision_floor_probe down to
// y - 300, HitInfo started by hitinfo_from_obj_floor) gives y, else the floor height obj +0x180. Rumbles the current
// player's pad (camera_shake_start(view, 7, 1)), takes the ground colour at the position (ground_colour_by_depth, three floats
// -> bytes), shakes the camera (rumble_all_players_at) and creates a 13-point dust ring (ring_effect_create, view 0xFF, group 1).
// On real ground it also throws four dust puffs (sprite_fx_spawn_quad kinds 0x51..0x54) at the corners of a square of
// half-size (rand * 96 + 352) / 2 turned by the character's yaw (obj +0x7A), then landing_dust_spray and a debris spray
// spawn_circle_random_emit in the ground colour. The N64 code also sums the code words hit_impact_effect..hit_react_impact_large and on a
// mismatch (anti-tamper) clears the matrix count g_matrix_arena_count; the port has no MIPS code there, so the
// NON_MATCHING build skips the check (as owner_spawn_children, menu_settings_apply_checked). Returns 0: game_981E0 calls it without a
// prototype (implicit int); the asm leaves a callee's v0 that nobody reads (tested as the void variant d_a150.c).
s32 collision_floor_probe(u8 *, u16, f32, u8 *);
void hitinfo_from_obj_floor(void *, u8 *);
u8 *ring_effect_create(u8 *spec, s32 extra, s32 view, s32 arg3);
void landing_dust_spray(u8 *arg0);
void spawn_circle_random_emit(f32, f32, f32, f32, s16, s16, s16, u8, s32, f32, s32, u8);
extern s32 g_view_count_minus1; /* was D_800BEE08 */

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

/* was func_150CA150 */
s32 landing_dust_burst(u8 *obj) {
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
        return 0;
    }
    hitinfo_from_obj_floor(hit, obj);
    camera_shake_start((struct108 *) ((u8 *) g_player_views + g_view_count_minus1 * 0x9A0), 7, 1);
    pos[0] = *(f32 *) (obj + 0x14);
    pos[1] = *(f32 *) (obj + 0x18) + 100.0f;
    pos[2] = *(f32 *) (obj + 0x1C);
    if (collision_floor_probe((u8 *) pos, 0, *(f32 *) (obj + 0x18) - 300.0f, (u8 *) hit)) {
        found = 1;
        pos[1] = hit[0];
    } else {
        pos[1] = *(f32 *) (obj + 0x180);
    }
    ground_colour_by_depth(pos[2], &r, &g, &b);
    cr = (u32) r;
    cg = (u32) g;
    cb = (u32) b;
    rumble_all_players_at((struct17 *) pos, 500.0f, 5000.0f, 0.0002f, 0xC, 0xF, 0xFF, 0);

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
    ring_effect_create((u8 *) &ring, 0, 0xFF, 1);
    if (!found) {
        return 0;
    }

    angle = -0x40 - (*(u16 *) (obj + 0x7A) >> 8);
    s = angle_byte_cos(angle);
    c = angle_byte_cos((u8) (angle - 0x40));
    size = (random_float() * 96.0f + 352.0f) * 0.5f;
    puff.w0 = 0x701;
    random_int();
    puff.h4 = 0x408;
    puff.w8 = 0;
    puff.wC = 0;
    puff.life = random_int() % 41U + 0xB4;
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
    sprite_fx_spawn_quad((s32) &puff, (s32) col, 0xC, 0, (ps + pos[0]) - pc, pos[1] + 10.0f, (ps + pos[2]) + pc, size, size,
                  angle, 0, 0, 0xFF, 0);
    nc = (-1.0f * size) * c;
    ns = (-1.0f * size) * s;
    puff.kind = 0x52;
    sprite_fx_spawn_quad((s32) &puff, (s32) col, 0xC, 0, (ps + pos[0]) - nc, pos[1] + 10.0f, (ns + pos[2]) + pc, size, size,
                  angle, 0, 0, 0xFF, 0);
    puff.kind = 0x53;
    sprite_fx_spawn_quad((s32) &puff, (s32) col, 0xC, 0, (ns + pos[0]) - pc, pos[1] + 10.0f, (ps + pos[2]) + nc, size, size,
                  angle, 0, 0, 0xFF, 0);
    puff.kind = 0x54;
    sprite_fx_spawn_quad((s32) &puff, (s32) col, 0xC, 0, (ns + pos[0]) - nc, pos[1] + 10.0f, (ns + pos[2]) + nc, size, size,
                  angle, 0, 0, 0xFF, 0);
    landing_dust_spray((u8 *) pos);
    i = random_int() % 21U + 0xA;
    rgb[0] = cr;
    rgb[1] = cg;
    rgb[2] = cb;
    spawn_circle_random_emit(pos[0], pos[1], pos[2], random_float() * 81.0f + 150.0f, 0, 0xFF, (s16) i, 0x14, 0, 0.0f,
                  (s32) rgb, 0xFF);
    return 0;
}

void spawn_circle_random_emit(f32, f32, f32, f32, s16, s16, s16, u8, s32, f32, s32, u8);

/* was func_150CAE30 */
void landing_dust_spray(u8 *arg0) {
    s16 sp3E;

    sp3E = (random_int() % 21U) + 0xA;
    spawn_circle_random_emit((*(f32 *)arg0), (*(f32 *)((u8 *)arg0 + 4)), (*(f32 *)((u8 *)arg0 + 8)), (random_float() * 59.0f) + 170.0f, 0, 0xFF, (s32) sp3E, 0x13, 0, 0.0f, 0, 0xFF);
}

/* was func_150CAED0 */
s32 sprite_fx_fade_in_update(u8 *arg0) {
    s16 temp_v0;
    s32 temp_v1;

    temp_v0 = (*(s16 *)((u8 *)arg0 + 0x1C));
    if (temp_v0 < 0x20) {
        temp_v1 = temp_v0 * 8;
        if (temp_v1 < (s32) (*(u8 *)((u8 *)arg0 + 0x28))) {
            (*(u8 *)((u8 *)arg0 + 0x28)) = (u8) temp_v1;
        }
    }
    return 1;
}

void vec3_from_angles_byte(s16, s16, f32, void *);
s32 particle_spawn_basic(void *, s32, s32, u8, s32);
/* was func_150CAF04 */
s32 dust_puff_spawn_dir(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s16 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
    struct {
        s32 u34;
        s32 u38;
        s16 u3C;
        s16 u3E;
        s32 u40;
        s32 u44;
        s8 u48;
        s8 u49;
        s8 u4A;
        u8 u4B;
        u8 u4C;
        u8 u4D;
        s8 u4E;
        s8 u4F;
        u8 u50;
        s8 u51;
        s16 u52;
        s16 u54;
        s16 u56;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        u8 pad70[0xC];
        s32 u7C[3];
        f32 u88;
        s32 u8C;
        u8 pad90[4];
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        u8 pad98[0x10];
    } sp;
    s32 obj;
    f32 scale;

    sp.u51 = 0x29;
    sp.u3C = 0xE03;
    sp.u34 = 0x200005;
    sp.u38 = 0;
    sp.u3E = (random_int() % 26U) + 0x19;
    sp.u40 = 0;
    sp.u44 = 0;
    sp.u4C = 0xB0;
    sp.u4D = 0xA0;
    sp.u4E = 0x2A;
    sp.u48 = 0x40;
    sp.u49 = 0xB;
    sp.u4A = 0x6A;
    sp.u4B = 0xFF;
    sp.u4F = (random_int() % 156U) + 0x64;
    sp.u50 = 0xFF;
    sp.u94 = 3;
    sp.u95 = 3;
    sp.u5C = sp.u60 = (random_float() * 401.0f) + 800.0f;
    sp.u64 = arg2;
    sp.u68 = arg3;
    sp.u6C = arg4;
    vec3_from_angles_byte(arg8, (s16) ((random_int() % 12U) - 0x15), ((random_float() * 300.0f) + 498.0f) * 0.1f, sp.u7C);
    sp.u8C = 0xE05;
    sp.u88 = 0.0f;
    if (random_int() & 1) {
        sp.u8C |= 0x40;
    }
    if (random_int() & 1) {
        sp.u8C |= 0x80;
    }
    sp.u96 = 9;
    sp.u97 = -1;
    sp.u52 = 0x19;
    sp.u54 = 0xA;
    sp.u56 = 0x20;
    sp.u58 = 1.04f;
    scale = 0.95100003f;
    obj = particle_spawn_basic(&sp, 1, 4, argE, 1);
    if (obj != 0) {
        memcpy(obj + 0xA8, &scale, 4);
    }
    return 1;
}

/* was func_150CB128 */
s32 particle_shrink_update_b(u8 *arg0, s32 arg1) {
    s32 i;
    f32 *p = (f32 *)(arg0 + 0xA8);
    for (i = g_frame_ticks; i != 0; i--) {
        *(f32 *)(arg0 + 0x58) *= *p;
        *(f32 *)(arg0 + 0x60) *= *p;
    }
    return 1;
}

void vec3_from_angles_byte(s16, s16, f32, void *);

/* was func_150CB2D0 */
s32 dust_chunk_spawn_dir(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s16 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
    struct {
        f32 u28[13];
        s32 u5C;
        u8 pad60[0x8];
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        s32 u78;
        s16 u7C;
        s16 u7E;
        s8 u80;
        u8 pad81[0x3];
        s32 u84;
        s8 u88;
        s8 u89;
        s8 u8A;
        s8 u8B;
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
        s8 u90;
        u8 pad91[0x1];
        s8 u92;
        u8 pad93[0x1];
        s32 u94;
        s8 u98;
        u8 pad99[0x1];
        s16 u9A;
        s16 u9C;
        u8 padA0[0x8];
    } sp;

    sp.u28[10] = arg2;
    sp.u28[11] = arg3;
    sp.u28[7] = 1.0f;
    sp.u28[8] = 1.0f;
    sp.u28[9] = 1.0f;
    sp.u78 = 0x29E8;
    sp.u28[4] = 0.0f;
    sp.u28[5] = 0.0f;
    sp.u28[6] = 0.0f;
    sp.u6C = 0.0f;
    sp.u28[0] = 1.0f;
    sp.u7E = 0x20;
    sp.u28[12] = arg4;
    sp.u28[1] = 0.2f;
    vec3_from_angles_byte(arg8, (s16) (((u32) random_int() % 21U) - 0x28), ((random_float() * 204.0f) + 500.0f) * 0.1f, &sp.u5C);
    sp.u68 = ((random_float() * 260.0f) + -130.0f) * 0.1f;
    sp.u70 = ((random_float() * 260.0f) + -130.0f) * 0.1f;
    sp.u7C = (random_int() % 51U) + 0x32;
    sp.u74 = ((random_float() * 1008.0f) + -3085.0f) * 0.001f;
    sp.u28[3] = ((random_float() * 601.0f) + 200.0f) * 0.001f;
    sp.u28[2] = sp.u28[3];
    sp.u80 = 0;
    sp.u84 = 0;
    sp.u88 = (random_int() % 76U) + 0xB4;
    sp.u89 = 4;
    sp.u8A = 0;
    sp.u8B = 0;
    sp.u8C = 0;
    sp.u8D = 0;
    sp.u8E = 0;
    sp.u8F = 0;
    sp.u90 = 0;
    sp.u92 = 2;
    sp.u94 = 0;
    sp.u98 = 0;
    sp.u9A = 0x20;
    sp.u9C = 7;
    mdl_particle_spawn(&sp, 3, 0xFF, 0, (s32) argE, 0);
    return 1;
}

/* was func_150CB508 */
s32 particle_ballistic_update_b(u8 *arg0) {
    *(f32 *)(arg0 + 0x38) += *(f32 *)(arg0 + 0x44) * g_frame_step_f;
    *(f32 *)(arg0 + 0x3C) += (*(f32 *)(arg0 + 0x48) * g_frame_step_f) + (*(f32 *)(arg0 + 0x5C) * g_frame_step_f * g_frame_step_f * 0.5f);
    *(f32 *)(arg0 + 0x40) += *(f32 *)(arg0 + 0x4C) * g_frame_step_f;
    *(f32 *)(arg0 + 0x48) += *(f32 *)(arg0 + 0x5C) * g_frame_step_f;
    *(f32 *)(arg0 + 0x20) += *(f32 *)(arg0 + 0x50) * g_frame_step_f;
    *(f32 *)(arg0 + 0x24) += *(f32 *)(arg0 + 0x54) * g_frame_step_f;
    *(f32 *)(arg0 + 0x28) += *(f32 *)(arg0 + 0x58) * g_frame_step_f;
    return 1;
}
