#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_1516D970 */
void particle_cooldowns_tick(void) {
    s32 i;
    s32 v;

    for (i = 0; i < 4; i++) {
        if ((&g_particle_cooldown)[i] < 0xFF) {
            v = (&g_particle_cooldown)[i] + g_frame_delta;
            if (v >= 0x100) {
                v = 0xFF;
            }
            (&g_particle_cooldown)[i] = v;
        }
    }
}

s32 timedfx_create_box(s32, s32, s32, s32, s32, s32, s32, u8 *, u8 *);

/* was func_1516DA58 */
void particle_sprite_spawn(s16 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD, u8 argE, u8 argF, u8 arg10, u8 arg11, u8 arg12, u8 arg13, u8 arg14, u8 arg15, u8 arg16, s16 arg17, s16 arg18, u8 arg19, s16 arg1A, s32 arg1B, s32 arg1C, u8 arg1D, s32 arg1E) {
    u8 *temp_v0;
    s32 var_a0;
    u8 *sp34;

    if (arg1B != 0) {
        var_a0 = 0x67;
    } else {
        var_a0 = 0x12;
    }
    temp_v0 = node_alloc(var_a0, arg1E, 0x34, 0, (u8) (s32) arg1D, 1U);
    if (temp_v0 != NULL) {
        (*(s16 *)((u8 *)temp_v0 + 0xE)) = arg0;
        (*(s16 *)((u8 *)temp_v0 + 0x10)) = arg1;
        (*(s16 *)((u8 *)temp_v0 + 0x12)) = arg2;
        (*(u8 *)((u8 *)temp_v0 + 0x1A)) = arg3;
        (*(u8 *)((u8 *)temp_v0 + 0x1B)) = arg4;
        (*(u8 *)((u8 *)temp_v0 + 0x1C)) = arg5;
        (*(u8 *)((u8 *)temp_v0 + 0x1D)) = arg6;
        (*(u8 *)((u8 *)temp_v0 + 0x1E)) = arg7;
        (*(u8 *)((u8 *)temp_v0 + 0x1F)) = arg8;
        (*(u8 *)((u8 *)temp_v0 + 0x20)) = arg9;
        (*(u8 *)((u8 *)temp_v0 + 0x21)) = argA;
        (*(u8 *)((u8 *)temp_v0 + 0x22)) = argB;
        (*(u8 *)((u8 *)temp_v0 + 0x23)) = argC;
        (*(s16 *)((u8 *)temp_v0 + 0x14)) = arg17;
        (*(s16 *)((u8 *)temp_v0 + 0x16)) = arg18;
        (*(u8 *)((u8 *)temp_v0 + 0x24)) = arg19;
        (*(s16 *)((u8 *)temp_v0 + 0x18)) = arg1A;
        (*(s8 *)((u8 *)temp_v0 + 0x25)) = 0;
        (*(u8 *)((u8 *)temp_v0 + 0x26)) = argD;
        (*(u8 *)((u8 *)temp_v0 + 0x27)) = argE;
        (*(u8 *)((u8 *)temp_v0 + 0x28)) = argF;
        (*(u8 *)((u8 *)temp_v0 + 0x29)) = arg10;
        (*(u8 *)((u8 *)temp_v0 + 0x2A)) = arg11;
        (*(u8 *)((u8 *)temp_v0 + 0x2B)) = arg12;
        (*(u8 *)((u8 *)temp_v0 + 0x2C)) = arg13;
        (*(u8 *)((u8 *)temp_v0 + 0x2D)) = arg14;
        (*(u8 *)((u8 *)temp_v0 + 0x2E)) = arg15;
        (*(u8 *)((u8 *)temp_v0 + 0x2F)) = arg16;
        if (arg1C != 0) {
            sp34 = temp_v0;
            (*(s32 *)((u8 *)temp_v0 + 0x30)) = timedfx_create_box(-1, 0, arg1C, 0x14, 0x14, 0x14, 0, temp_v0 + 0xE, temp_v0 + 0x14);
            return;
        }
        (*(s32 *)((u8 *)temp_v0 + 0x30)) = 0;
    }
}

extern s32 (*g_particle_sprite_tick_fns[])(u8 *); /* was D_8008CF40 */

/* was func_1516DBE8 */
void particle_sprite_tick(u8 *arg0) {
    s32 v;

    v = arg0[0x24];
    if (v != 0) {
        v -= g_frame_ticks;
        if (v < 0) {
            v = 0;
        }
        arg0[0x24] = v;
    }
    if (g_particle_sprite_tick_fns[arg0[0x23]](arg0) == 1) {
        if (*(u8 **)(arg0 + 0x30) != NULL) {
            *(s16 *)(*(u8 **)(arg0 + 0x30) + 4) = 0;
        }
        node_destroy((struct102 *)arg0);
    } else {
        s32 t;
        v = *(s16 *)(arg0 + 0x10) << 8;
        v += arg0[0x25];
        t = v;
        t += *(s16 *)(arg0 + 0x18) * g_frame_ticks;
        *(s16 *)(arg0 + 0x10) = t >> 8;
        arg0[0x25] = t & 0xFF;
    }
}

s32 gfx_load_texture_cached(s32, s32, s32, s32, s32, s32, s32, u8, s32, u8 *, s32);
Gfx *gfx_other_mode_cached(Gfx *, s32, s32, u8 *);
u8 *sprite_draw_at_world_depth(u8 *, u8 *);
extern u8 *g_sprite_tex_descs[]; /* was D_8008CDEC */
extern s16 g_sprite_last_other_mode; /* last sprite other-mode (1 / 2 / 3), shared with sprite_billboard_draw; was D_800DD5EC */
extern s32 g_gfx_tlut_mode; /* TLUT bit of the last loaded texture; was D_800D30BC */
extern u8 g_sprite_prim_r; /* was D_800D31C8 */
extern u8 g_sprite_prim_g; /* was D_800D31C9 */
extern u8 g_sprite_prim_b; /* was D_800D31CA */
// tinted_sprite_draw: draw handler of the particle type whose tick is particle_sprite_tick (D_8008BBF8 / D_8008CD3C, same
// slot as sprite_billboard_draw). Loads the texture g_sprite_tex_descs[+0x1A] frame +0x1B (gfx_load_texture_cached), picks the combine mode
// (2 for a texture of format 5 at +0xA, else 1; set only when it differs from g_sprite_last_other_mode, after a pipe sync), sets the
// other mode 0x2C00 | TLUT | (0x100000 for mode 2), the colour g_sprite_prim_r..CA from +0x1C..+0x1E and the env colour
// +0x20..+0x22 (only when it differs from g_gfx_env_r_cached..FC; alpha 0), and draws the quad (+0xE..+0x16, alpha +0x1F)
// with sprite_draw_at_world_depth. Returns the advanced display list.
// The asm leaves its other-mode word (sp+0x5C) uninitialised when the combine mode is unchanged (a stale stack
// word); the C uses the word that belongs to the mode, i.e. what the previous draw of this mode set.
/* was func_1516DCA8 */
u8 *particle_tinted_sprite_draw(u8 *gfx, u8 *obj, s32 arg2) {
    struct {
        s16 x, y, z;
        s16 sizeX, sizeZ;
        u8 alpha;
        u8 pad[2];
        u8 flag;
    } quad; /* sp84 */
    s32 *tex;
    s32 synced; /* the s32 at sp78; gfx_load_texture_cached / gfx_other_mode_cached see it as a byte */
    s32 mode;
    s32 other;
    s32 r;
    s32 g;
    s32 b;

    synced = 0;
    g_sprite_keep_prim_colour = 0;
    tex = (s32 *) g_sprite_tex_descs[obj[0x1A]];
    gfx = (u8 *) gfx_load_texture_cached((s32) gfx, (s32) tex, obj[0x1B] << 8, 2, 0x100, 0x100, 0, 6, (s32) &quad,
                               (u8 *) &synced, 3);
    if (((u8 *) tex)[0xA] == 5) {
        mode = 2;
    } else {
        mode = 1;
    }
    other = (mode == 1) ? 0 : 0x100000;
    if (mode != g_sprite_last_other_mode) {
        if (synced == 0) {
            ((s32 *) gfx)[0] = 0xE7000000; /* gDPPipeSync */
            ((s32 *) gfx)[1] = 0;
            gfx += 8;
            synced = 1;
        }
        g_sprite_last_other_mode = mode;
        if (mode == 1) {
            ((s32 *) gfx)[0] = 0xFC30B261; /* gDPSetCombine */
            ((s32 *) gfx)[1] = 0x5566FF7F;
        } else {
            ((s32 *) gfx)[0] = 0xFC30B5FF;
            ((s32 *) gfx)[1] = 0x5FFEFE38;
        }
        gfx += 8;
    }
    gfx = (u8 *) gfx_other_mode_cached((Gfx *) gfx, other | g_gfx_tlut_mode | 0x2C00, 0x5049DC, (u8 *) &synced);

    quad.x = *(s16 *) (obj + 0xE);
    quad.y = *(s16 *) (obj + 0x10);
    quad.z = *(s16 *) (obj + 0x12);
    quad.sizeX = *(s16 *) (obj + 0x14);
    quad.sizeZ = *(s16 *) (obj + 0x16);
    quad.flag = 0;
    quad.alpha = obj[0x1F];
    g_sprite_prim_r = obj[0x1C];
    g_sprite_prim_g = obj[0x1D];
    g_sprite_prim_b = obj[0x1E];
    r = obj[0x20];
    g = obj[0x21];
    b = obj[0x22];
    if (r != g_gfx_env_r_cached || g != g_gfx_env_g_cached || b != g_gfx_env_b_cached) {
        g_gfx_env_r_cached = r;
        g_gfx_env_g_cached = g;
        g_gfx_env_b_cached = b;
        if (synced == 0) {
            ((s32 *) gfx)[0] = 0xE7000000; /* gDPPipeSync */
            ((s32 *) gfx)[1] = 0;
            gfx += 8;
        }
        ((s32 *) gfx)[0] = 0xFB000000; /* gDPSetEnvColor(r, g, b, 0) */
        ((s32 *) gfx)[1] = (r << 24) | (g << 16) | (b << 8);
        gfx += 8;
    }
    return sprite_draw_at_world_depth(gfx, (u8 *) &quad);
}

/* was func_1516DF0C */
void particle_emitter_node_spawn(s16 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD, u8 argE, u8 argF, u8 arg10, u8 arg11, u8 arg12, u8 arg13, u8 arg14, u8 arg15, u8 arg16, u8 arg17, u8 arg18, u8 arg19, u8 arg1A, s16 arg1B, s16 arg1C, s16 arg1D, s16 arg1E, u16 arg1F, u8 arg20, u8 arg21, u8 arg22, u8 arg23, s16 arg24, u16 arg25, u16 arg26, u8 arg27, u8 arg28, u8 arg29, u8 arg2A, u8 arg2B, s32 arg2C, u8 arg2D, u8 arg2E, u8 arg2F, s32 arg30) {
    s32 var_a0;
    u8 *temp_v0;

    if (arg2C != 0) {
        var_a0 = 0x66;
    } else {
        var_a0 = 0x11;
    }
    temp_v0 = node_alloc(var_a0, arg30, 0x4C, 0, arg2F, 1);
    if (temp_v0 != NULL) {
        *(s16 *)(temp_v0 + 0xE) = arg0;
        *(s16 *)(temp_v0 + 0x10) = arg1;
        *(s16 *)(temp_v0 + 0x12) = arg2;
        *(s16 *)(temp_v0 + 0x14) = arg1B;
        *(s16 *)(temp_v0 + 0x16) = arg1C;
        *(s16 *)(temp_v0 + 0x18) = arg1D;
        *(s16 *)(temp_v0 + 0x1A) = arg1E;
        *(u8 *)(temp_v0 + 0x24) = arg3;
        *(u8 *)(temp_v0 + 0x25) = arg4;
        *(u8 *)(temp_v0 + 0x26) = arg5;
        *(u8 *)(temp_v0 + 0x27) = arg6;
        *(u8 *)(temp_v0 + 0x28) = arg7;
        *(u8 *)(temp_v0 + 0x2A) = arg9;
        *(u8 *)(temp_v0 + 0x2B) = argA;
        *(u8 *)(temp_v0 + 0x2C) = argB;
        *(u8 *)(temp_v0 + 0x29) = arg8;
        *(u8 *)(temp_v0 + 0x2D) = argC;
        *(u8 *)(temp_v0 + 0x2E) = argD;
        *(u8 *)(temp_v0 + 0x2F) = argE;
        *(u8 *)(temp_v0 + 0x30) = argF;
        *(u8 *)(temp_v0 + 0x31) = arg10;
        *(u8 *)(temp_v0 + 0x32) = arg11;
        *(u8 *)(temp_v0 + 0x33) = arg12;
        *(u8 *)(temp_v0 + 0x34) = arg13;
        *(u8 *)(temp_v0 + 0x35) = arg14;
        *(u8 *)(temp_v0 + 0x36) = arg15;
        *(u8 *)(temp_v0 + 0x37) = arg16;
        *(u8 *)(temp_v0 + 0x38) = arg17;
        *(u8 *)(temp_v0 + 0x39) = arg18;
        *(u8 *)(temp_v0 + 0x3A) = arg19;
        *(u8 *)(temp_v0 + 0x3B) = arg1A;
        *(u16 *)(temp_v0 + 0x20) = arg1F;
        *(s8 *)(temp_v0 + 0x3C) = arg1F;
        *(u8 *)(temp_v0 + 0x3D) = arg20;
        *(u8 *)(temp_v0 + 0x3E) = arg21;
        *(u8 *)(temp_v0 + 0x3F) = arg22;
        *(u8 *)(temp_v0 + 0x40) = arg23;
        *(s16 *)(temp_v0 + 0x1C) = arg24;
        *(u16 *)(temp_v0 + 0x1E) = arg25;
        *(u16 *)(temp_v0 + 0x22) = arg26;
        *(u8 *)(temp_v0 + 0x41) = arg27;
        *(s8 *)(temp_v0 + 0x42) = 0;
        *(u8 *)(temp_v0 + 0x43) = arg28;
        if ((arg2C != 0) && (arg29 >= 4)) {
            arg29 = 3;
        }
        *(u8 *)(temp_v0 + 0x44) = arg29;
        *(u8 *)(temp_v0 + 0x45) = arg2A;
        *(u8 *)(temp_v0 + 0x46) = arg2B;
        *(u8 *)(temp_v0 + 0x47) = arg2D;
        *(u8 *)(temp_v0 + 0x48) = arg2E;
    }
}

// Particle emitter record (handler table entry 0 at 0x8008BBBC / 0x8008CD00, a0 = the record).
typedef struct {
    u8 kind;          // 0x00: 0x11 = emitter whose particles get arg 0x1B = 0
    u8 owner;         // 0x01
    u8 pad02[0xA];
    u8 unk0C;         // 0x0C
    u8 pad0D;
    s16 posX;         // 0x0E: x / table index (object mode) / high half of the position pointer (flags 0x10 / 0x20)
    s16 posY;         // 0x10: y / low half of the position pointer
    s16 posZ;         // 0x12: z / y offset (pointer modes)
    s16 parmA;        // 0x14 \ two s16 particle parameters (args 0x17 / 0x18), each with a random range
    s16 parmB;        // 0x16 /
    s16 parmRandAB;   // 0x18: random added to both (flag 1) or to parmA only
    s16 parmRandB;    // 0x1A: random added to parmB (flag 1 clear)
    s16 riseBase;     // 0x1C: arg 0x1A (vertical speed) when no velocity mode is set
    u16 riseRand;     // 0x1E
    u16 timer;        // 0x20: frames left, 0xFFFF = forever
    u16 flags;        // 0x22
    u8 parm[10];      // 0x24..0x2D: args 3..0xC
    u8 col[4];        // 0x2E..0x31: args 0xD..0x10 base (colour)
    u8 parm2[6];      // 0x32..0x37: args 0x11..0x16
    u8 colRand[4];    // 0x38..0x3B
    u8 lifeTotal;     // 0x3C: flag 4 fades the spawn chance with timer / lifeTotal
    u8 scatterXZ;     // 0x3D
    u8 scatterY;      // 0x3E
    u8 obj;           // 0x3F: g_objects object index, 0xFF = none
    u8 parm40;        // 0x40: arg 0x19
    u8 period;        // 0x41
    u8 countdown;     // 0x42
    u8 chance;        // 0x43: spawn chance out of 256 (0 = always)
    u8 count;         // 0x44: particles per burst
    u8 speedScale;    // 0x45: flag 8 velocity * 16 * this
    u8 offsetScale;   // 0x46: flag 8 start offset along the velocity
    u8 mtx;           // 0x47: object matrix index
    u8 parm48;        // 0x48: arg 0x1C
} ParticleEmitter;

extern s16 g_particle_emitter_points[][7]; /* object-attached emitter points: a xyz, b xyz, random z mask; was D_800A7210 */
f32 math_cos_u8(s32 angle); // defined (u8); the file's unprototyped declaration rules out u8 here
s32 particle_random_direction(s32 flags, f32 *vx, f32 *vy, f32 *vz);

// particle_emitter_update: emitter tick. The countdown +0x42 runs down by g_frame_ticks frames; each time it passes 0
// it is re-armed with +0x41 (0 = once) and a burst of +0x44 particles is rolled (+0x43 = chance out of 256, scaled
// by timer / +0x3C with flag 4). A particle starts at the emitter's xyz, at a s16 / f32 position behind a pointer
// (flags 0x10 / 0x20), or (object +0x3F) at two points of g_particle_emitter_points moved by the object's matrix +0x1D4[+0x47],
// whose difference (minus the object's movement) is its velocity. Flag 8 gives a random direction
// (particle_random_direction), +0x3D / +0x3E scatter the start, then particle_sprite_spawn spawns it. Velocities are passed as
// hi / lo bytes in the colour args. Finally the timer +0x20 runs down and the emitter is freed (node_destroy).
/* was func_1516E100 */
void particle_emitter_update(u8 *arg0) {
    ParticleEmitter *e = (ParticleEmitter *) arg0;
    s32 notKind11;
    s32 n;
    s32 i;
    u8 roll;
    s32 chance;
    s16 x, y, z;
    s16 parmA, parmB;
    u32 r;
    s32 rise;
    s32 a0D, a0E, a0F, a10; // colour bytes, or velocity x / z as hi / lo bytes
    s32 vi;
    f32 ax, ay, az, bx, by, bz;
    f32 vx, vy, vz;
    f32 speed, offset, dist, dirA, dirB;
    s16 *pt;
    u8 *obj;
    s32 ang;
    s32 left;

    notKind11 = (e->kind == 0x11) ? 0 : 1;
    n = e->countdown - g_frame_ticks;
    while (n < 0) {
        if (e->period != 0) {
            n += e->period;
        } else {
            n = 0;
        }
        for (i = 0; i < e->count; i++) {
            if (e->chance != 0) {
                roll = random_int();
                if (e->flags & 4) {
                    chance = (s32) (e->timer * e->chance) / e->lifeTotal;
                } else {
                    chance = e->chance;
                }
            }
            if (e->chance != 0 && roll >= chance) {
                continue;
            }
            if (e->obj == 0xFF) {
                if (e->flags & 0x10) {
                    pt = (s16 *) ((e->posX << 16) | (u16) e->posY);
                    x = pt[0];
                    z = pt[2];
                    y = pt[1] + e->posZ;
                } else if (e->flags & 0x20) {
                    f32 *pf = (f32 *) ((e->posX << 16) | (u16) e->posY);
                    x = (s32) pf[0];
                    z = (s32) pf[2];
                    y = (s32) (pf[1] + (f32) e->posZ);
                } else {
                    x = e->posX;
                    y = e->posY;
                    z = e->posZ;
                }
            } else {
                obj = (u8 *) g_objects + e->obj * 0x32C;
                if (*(u8 **) (obj + 0x1D4) == NULL) {
                    continue;
                }
                ax = g_particle_emitter_points[e->posX][0];
                ay = g_particle_emitter_points[e->posX][1];
                az = g_particle_emitter_points[e->posX][2];
                bx = g_particle_emitter_points[e->posX][3];
                by = g_particle_emitter_points[e->posX][4];
                bz = g_particle_emitter_points[e->posX][5];
                if (g_particle_emitter_points[e->posX][6] != 0) {
                    bz += (f32) (u32) (random_int() & g_particle_emitter_points[e->posX][6]);
                }
                obj = (u8 *) g_objects + e->obj * 0x32C;
                mtxf_transform_point((f32 (*)[4]) (*(u8 **) (obj + 0x1D4) + e->mtx * 64), ax, ay, az, &ax, &ay, &az);
                obj = (u8 *) g_objects + e->obj * 0x32C;
                mtxf_transform_point((f32 (*)[4]) (*(u8 **) (obj + 0x1D4) + e->mtx * 64), bx, by, bz, &bx, &by, &bz);
                vx = (bx - ax) * 8.0f;
                vy = (by - ay) * 8.0f;
                rise = (s32) vy;
                vz = (bz - az) * 8.0f;
                obj = (u8 *) g_objects + e->obj * 0x32C;
                ang = (0x40 - *(u16 *) (obj + 0x76)) & 0xFF;
                vx -= *(f32 *) (obj + 0x3C) * math_sin_u8(ang) * 64.0f;
                obj = (u8 *) g_objects + e->obj * 0x32C;
                vz -= *(f32 *) (obj + 0x3C) * math_cos_u8(ang) * 64.0f;
                vi = (s32) vx;
                a0D = (vi >> 8) & 0xFF;
                a0E = vi & 0xFF;
                vi = (s32) vz;
                a0F = (vi >> 8) & 0xFF;
                a10 = vi & 0xFF;
                x = (s32) ax;
                y = (s32) ay;
                z = (s32) az;
            }
            if (e->flags & 8) {
                particle_random_direction(e->flags, &vx, &vy, &vz);
                speed = (s32) (e->speedScale * 16);
                offset = e->offsetScale;
                y = (s32) ((f32) y + offset * vy);
                vy = speed * vy;
                rise = (s32) vy;
                random_int();
                x = (s32) ((f32) x + vx * offset);
                z = (s32) ((f32) z + vz * offset);
                vx = vx * speed;
                vz = vz * speed;
                vi = (s32) vx;
                a0D = (vi >> 8) & 0xFF;
                a0E = vi & 0xFF;
                vi = (s32) vz;
                a0F = (vi >> 8) & 0xFF;
                a10 = vi & 0xFF;
            }
            if (e->scatterXZ != 0) {
                r = random_int();
                dirA = math_sin_u8(r & 0xFF);
                dirB = math_cos_u8(r & 0xFF);
                dist = (f32) (u32) ((random_int() & 0xFFFF) * e->scatterXZ) * 1.52587890625e-05f;
                x = (s32) ((f32) x + dist * dirA);
                z = (s32) ((f32) z + dist * dirB);
            }
            if (e->scatterY != 0) {
                r = random_int();
                dirA = math_sin_u8(r & 0xFF);
                dist = (f32) (u32) ((random_int() & 0xFFFF) * e->scatterY) * 1.52587890625e-05f;
                y += (s32) (dist * dirA);
            }
            parmA = e->parmA;
            parmB = e->parmB;
            r = 0;
            if (e->parmRandAB != 0) {
                r = (u32) random_int() % (u32) e->parmRandAB;
            }
            if (e->flags & 1) {
                parmA += r;
                parmB += r;
            } else {
                parmA += r;
                if (e->parmRandB != 0) {
                    parmB += (u32) random_int() % (u32) e->parmRandB;
                }
            }
            if (!(e->flags & 8) && !(e->flags & 0x80)) {
                rise = e->riseBase;
                if (e->riseRand != 0) {
                    rise += (u32) random_int() % e->riseRand;
                }
                a0D = e->col[0];
                if (e->colRand[0] != 0) {
                    a0D += (u32) random_int() % e->colRand[0];
                    if (a0D >= 0x100) {
                        a0D = 0xFF;
                    }
                }
                a0E = e->col[1];
                if (e->colRand[1] != 0) {
                    a0E += (u32) random_int() % e->colRand[1];
                    if (a0E >= 0x100) {
                        a0E = 0xFF;
                    }
                }
                a0F = e->col[2];
                if (e->colRand[2] != 0) {
                    a0F += (u32) random_int() % e->colRand[2];
                    if (a0F >= 0x100) {
                        a0F = 0xFF;
                    }
                }
                a10 = e->col[3];
                if (e->colRand[3] != 0) {
                    a10 += (u32) random_int() % e->colRand[3];
                    if (a10 >= 0x100) {
                        a10 = 0xFF;
                    }
                }
            }
            particle_sprite_spawn(x, y, z, e->parm[0], e->parm[1], e->parm[2], e->parm[3], e->parm[4], e->parm[5],
                          e->parm[6], e->parm[7], e->parm[8], e->parm[9], a0D, a0E, a0F, a10, e->parm2[0],
                          e->parm2[1], e->parm2[2], e->parm2[3], e->parm2[4], e->parm2[5], parmA, parmB, e->parm40,
                          rise, notKind11, e->parm48, e->unk0C, e->owner);
        }
    }
    e->countdown = n;
    if (e->timer != 0xFFFF) {
        left = e->timer - g_frame_ticks;
        if (left > 0) {
            e->timer = left;
        } else {
            node_destroy((struct102 *) e);
        }
    }
}

/* was func_1516ECE8 */
void particle_emitter_preset_packed_pos(u32 arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4) {
    if (arg1) { // fakematch: permuter, forces arg1 home/reload order
    }
    particle_emitter_node_spawn(arg0 >> 0x10, arg0 & 0xFFFF, 0, arg2, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0, 8, 8, 1, 0, 0, 0, 0, 0x155, 0x155, 0x155, 0x155, arg1, 0x1E, 0, 0xFF, 0x28, 0x168, 0x18, 0x21, 4, 0, 1, 0, 0, 0, 0, 0, arg3, arg4);
}

extern u8 g_particle_glow_thresholds[]; /* glow level thresholds (descending); was D_800A71E0 */
extern u8 g_particle_glow_colours[]; /* rgb per threshold; was D_800A71EC */
// glow_colour_update: handler 0 of g_particle_sprite_tick_fns (`s32 (u8 *)`). While +0x24 (the glow level) is set the fade +0x1F
// rises by g_frame_ticks * 32 up to 0xFF, else it falls by g_frame_ticks * 16 down to 0; returns 1 (done) when both are 0.
// The phase +0x14 advances by g_frame_ticks * 10 (copied to +0x16). The level (+0x24 + 8, or fade >> 5 while fading
// out) picks, from index +0x26 for 8 entries, the first threshold of g_particle_glow_thresholds at or below it, and the colour
// +0x1C..+0x1E is that entry's rgb (g_particle_glow_colours) blended with the previous entry's by the level's position between
// the two thresholds. Returns 0.
/* was func_1516EE3C */
s32 particle_glow_colour_tick(u8 *arg0) {
    u8 on = arg0[0x24];
    s32 fade = arg0[0x1F];
    s32 level;
    s32 i;
    u8 *rgb;
    f32 t;
    f32 u;

    if (on != 0) {
        if (fade != 0xFF) {
            fade += g_frame_ticks << 5;
            if (fade >= 0x100) {
                fade = 0xFF;
            }
            arg0[0x1F] = fade;
            on = arg0[0x24];
        }
    } else if (fade != 0) {
        fade -= g_frame_ticks << 4;
        if (fade < 0) {
            fade = 0;
        }
        arg0[0x1F] = fade;
        on = arg0[0x24];
    }
    if (on == 0 && fade == 0) {
        return 1;
    }
    *(s16 *) (arg0 + 0x14) += g_frame_ticks * 10;
    *(s16 *) (arg0 + 0x16) = *(s16 *) (arg0 + 0x14);
    if (on == 0) {
        level = arg0[0x1F] >> 5;
    } else {
        level = on + 8;
    }
    for (i = arg0[0x26]; i < arg0[0x26] + 8; i++) {
        if (level >= g_particle_glow_thresholds[i]) {
            t = (f32) (level - g_particle_glow_thresholds[i]) / (f32) (g_particle_glow_thresholds[i - 1] - g_particle_glow_thresholds[i]);
            u = 1.0f - t;
            rgb = &g_particle_glow_colours[i * 3];
            arg0[0x1C] = (u32) (rgb[-3] * t + rgb[0] * u);
            arg0[0x1D] = (u32) (rgb[-2] * t + rgb[1] * u);
            arg0[0x1E] = (u32) (rgb[-1] * t + rgb[2] * u);
            break;
        }
    }
    return 0;
}

/* was func_1516F21C */
s32 particle_fade_scale_tick(u8 *arg0) {
    s32 v;
    s32 t;
    s32 hl;
    s32 m;

    v = arg0[0x1F];
    if (arg0[0x24] != 0) {
        if (v != 0xFF) {
            v += g_frame_ticks << 7;
            if (v >= 0x100) {
                v = 0xFF;
            }
            arg0[0x1F] = v;
        }
    } else if (v != 0) {
        v -= g_frame_ticks * arg0[0x26];
        if (v < 0) {
            v = 0;
        }
        arg0[0x1F] = v;
    }
    if ((arg0[0x24] == 0) && (v == 0)) {
        return 1;
    }
    hl = arg0[0x2D] | (arg0[0x2C] << 8);
    m = hl * v;
    t = m >> 7;
    *(s16 *)(arg0 + 0x16) = t;
    *(s16 *)(arg0 + 0x14) = t;
    return 0;
}

/* was func_1516F2D8 */
void particle_emitter_preset_obj3a(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    u8 t;

    t = g_obj_tab_id[arg0 * 0x32C];
    if (t == 0x3A) {
        particle_emitter_node_spawn(5, 0, 0, 4, 0, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0x124, 0x124, 0, 0, arg1, 0, 0, arg0, 0xC, 0, 0, 0x81, 2, 0, 1, 0, 0, 0, 5, 0, arg2, arg3);
    }
}

/* was func_1516EED4 */
void particle_emitter_preset_cooldown(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    if ((arg0 < 4) && ((&g_particle_cooldown)[arg0 ^ 0] >= arg1)) { // fakematch: ^ 0 (permuter), keeps one arg0 reload
        (&g_particle_cooldown)[arg0 ^ 0] = 0;
        particle_emitter_node_spawn(0, 0, 0, 4, 0, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x200, 0x200, 0, 0, 0x1E, 0, 0, arg0, 0x14, 0, 0, 0x81, 8, 0, 1, 0, 0, 0, 0xC, 0, arg2, arg3);
    }
}

void particle_move_xz(u8 *arg0);
void particle_scale_vel_xz(s32 arg0, s32 arg1);

// sprite_fade_grow_kind_tick: particle tick (handler at 0x8008CF48, sibling of particle_fade_shrink_tick) with per-kind
// parameters (+0x2C = kind 0..10, tables copied from D_8008CF64 / CF70 / CF7C / CF88). While +0x24 (fading in) is
// set, alpha +0x1F rises by 16 per frame (g_frame_ticks) up to the kind's maximum; otherwise it falls by the kind's
// rate per frame down to 0. Returns 1 (done) once fading out reached 0. Else moves the particle
// (particle_move_xz), grows the size +0x14 / +0x16 by the kind's step per frame (kind 3 also sets +0x18 = 100),
// scales its velocity by the kind's factor / 256 (particle_scale_vel_xz) and returns 0.
/* was func_1516F594 */
s32 particle_fade_grow_kind_tick(u8 *arg0) {
    static const u8 scale[11] = { 0xFA, 0xFA, 0xEB, 0xEB, 0xFA, 0xFA, 0xDC, 0xD2, 0xD2, 0xDC, 0xD2 };
    static const u8 grow[11] = { 0x10, 0x07, 0x07, 0x07, 0x14, 0x08, 0x28, 0x28, 0x28, 0x14, 0x14 };
    static const u8 maxAlpha[11] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xBE, 0xAA, 0x78, 0xC8, 0x3C, 0x78, 0xC8 };
    static const u8 fadeRate[11] = { 0x08, 0x02, 0x0A, 0x01, 0x08, 0x0A, 0xFF, 0x0A, 0x02, 0xFF, 0x0A };
    s32 kind = arg0[0x2C];
    s32 v = arg0[0x1F];
    s32 size;

    if (arg0[0x24] != 0) {
        if (v != maxAlpha[kind]) {
            v += g_frame_ticks << 4;
            if (v > maxAlpha[kind]) {
                v = maxAlpha[kind];
            }
            arg0[0x1F] = v;
        }
    } else if (v != 0) {
        v -= g_frame_ticks * fadeRate[kind];
        if (v < 0) {
            v = 0;
        }
        arg0[0x1F] = v;
    }
    if (arg0[0x24] == 0 && v == 0) {
        return 1;
    }
    particle_move_xz(arg0);
    size = *(s16 *) (arg0 + 0x14) + g_frame_ticks * grow[kind];
    *(s16 *) (arg0 + 0x16) = size;
    *(s16 *) (arg0 + 0x14) = size;
    if (kind == 3) {
        *(s16 *) (arg0 + 0x18) = 100;
    }
    particle_scale_vel_xz((s32) arg0, scale[kind]);
    return 0;
}

void particle_emitter_node_spawn(s16 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD, u8 argE, u8 argF, u8 arg10, u8 arg11, u8 arg12, u8 arg13, u8 arg14, u8 arg15, u8 arg16, u8 arg17, u8 arg18, u8 arg19, u8 arg1A, s16 arg1B, s16 arg1C, s16 arg1D, s16 arg1E, u16 arg1F, u8 arg20, u8 arg21, u8 arg22, u8 arg23, s16 arg24, u16 arg25, u16 arg26, u8 arg27, u8 arg28, u8 arg29, u8 arg2A, u8 arg2B, s32 arg2C, u8 arg2D, u8 arg2E, u8 arg2F, s32 arg30);

/* was func_1516F730 */
void particle_emitter_preset_obj_burst(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    particle_emitter_node_spawn(2, 0, 0, 0x2D, 0, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0x50, 0x50, 0, 0, arg1, 0xA, 0xA, arg0, 0x3C, 0, 0, 0x81, 4, 0, 1, 0, 0, 0, 4, 2, (s32) arg2, arg3);
}

/* was func_1516F868 */
void particle_emitter_preset_obj_pair(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    particle_emitter_node_spawn(3, 0, 0, 0x2B, 0, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0x50, 0x50, 0, 0, arg1, 4, 4, arg0, 0x10, 0, 0, 0x81, 4, 0, 1, 0, 0, 0, 1, 0, arg4, arg5);
    particle_emitter_node_spawn(3, 0, 0, 0x2B, 0, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0x50, 0x50, 0, 0, 7, 4, 4, arg0, arg2, 0, 0, 0x81, 5, 0, 1, 0, 0, 0, 1, arg3, arg4, arg5);
}


// spray_pair_spawn: spawns two particle sprays at (x, y, z) through particle_emitter_node_spawn (same parameters except the second
// one's +0x13 byte (rate11 instead of rate10) and +0x27 = 6), then plays sound 7 there with `span` as the sound's user
// value. Speeds speedA / speedB go through a 20.12 fixed-point round trip ((v << 12) / 4096) as in the asm.
/* was func_1516FAB8 */
void particle_spray_pair_spawn(s32 x, s32 y, s32 z, s32 span, s32 dx, s32 spread, s32 dz, s32 speedA, s32 speedB, s32 size,
                   s32 rate10, s32 rate11, s32 unused12, s32 unused13, s32 unused14, s32 flag, s32 owner) {
    s16 a = (s16)((speedA << 12) / 4096);
    s16 b = (s16)((speedB << 12) / 4096);

    particle_emitter_node_spawn(x, y, z, 0xD, 0, 0x67, 0x17, 0xD, 0, 0, 0x12, 0, 2, dx, 0, dz, 0, 0, 0, rate10, 0, 0, 0, 0, 0, 0, 0,
                  a, a, b, b, span, size, 0x14, 0xFF, 0x10, spread, 0xC8, 1, 0, 0, 1, 0, 0, 0, 0, 0, flag, owner);
    particle_emitter_node_spawn(x, y, z, 0xD, 0, 0x67, 0x17, 0xD, 0, 0, 0x12, 0, 2, dx, 0, dz, 0, 0, 0, rate11, 0, 0, 0, 0, 0, 0, 0,
                  a, a, b, b, span, size, 0x14, 0xFF, 0x10, spread, 0xC8, 1, 6, 0, 1, 0, 0, 0, 0, 0, flag, owner);
    sfx_emitter_start(7, x, y, z, 0x36B0, 0x3E8, 0x64, (s32)&sfx_cb_fade_out, (void *)span, 0, 0, 0);
}

/* was func_1516FDD4 */
void particle_move_xz(u8 *arg0) {
    s32 temp_t1;
    s32 temp_t3;

    temp_t3 = ((*(s16 *)((u8 *)arg0 + 0xE)) << 8) + (*(u8 *)((u8 *)arg0 + 0x2A)) + ((((*(s8 *)((u8 *)arg0 + 0x26)) << 8) + (*(u8 *)((u8 *)arg0 + 0x27))) * g_frame_ticks);
    (*(s16 *)((u8 *)arg0 + 0xE)) = (s16) (temp_t3 >> 8);
    (*(u8 *)((u8 *)arg0 + 0x2A)) = (u8) temp_t3;
    temp_t1 = ((*(s16 *)((u8 *)arg0 + 0x12)) << 8) + (*(u8 *)((u8 *)arg0 + 0x2B)) + ((((*(s8 *)((u8 *)arg0 + 0x28)) << 8) + (*(u8 *)((u8 *)arg0 + 0x29))) * g_frame_ticks);
    (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (temp_t1 >> 8);
    (*(u8 *)((u8 *)arg0 + 0x2B)) = (u8) temp_t1;
}
/* was func_1516FE5C */
void particle_scale_vel_x(s32 arg0, s32 arg1) {
    s32 v;

    v = ((s8 *)arg0)[0x26];
    v <<= 8;
    v += ((u8 *)arg0)[0x27];
    v *= (u32)arg1;
    v >>= 8;
    ((u8 *)arg0)[0x26] = v >> 8;
    ((u8 *)arg0)[0x27] = v & 0xFFFFu; // fakematch: the mask moves the low byte temp from t8 to t0
}

/* was func_1516FE8C */
void particle_scale_vel_z(s32 arg0, s32 arg1) {
    s32 v;

    v = ((s8 *)arg0)[0x28];
    v <<= 8;
    v += ((u8 *)arg0)[0x29];
    v *= (u32)arg1;
    v >>= 8;
    ((u8 *)arg0)[0x28] = v >> 8;
    ((u8 *)arg0)[0x29] = v & 0xFFFFu; // fakematch: the mask moves the low byte temp from t8 to t0
}

void particle_scale_vel_x(s32, s32);
void particle_scale_vel_z(s32, s32);

/* was func_1516FEBC */
void particle_scale_vel_xz(s32 arg0, s32 arg1) {
    particle_scale_vel_x(arg0, arg1);
    particle_scale_vel_z(arg0, arg1);
}

/* was func_1516FEF4 */
void particle_scale_vel_xyz(s32 arg0, s32 arg1) {
    s32 v;
    particle_scale_vel_xz(arg0, arg1);
    v = *(s16 *)((u8 *)arg0 + 0x18);
    v = v * arg1;
    *(s16 *)((u8 *)arg0 + 0x18) = v >> 8;
}

// sprite_fade_scale_tick: particle tick (same scheme as particle_fade_rise_tick): while +0x24 (fading in) is set, alpha +0x1F
// rises by 16 per frame (g_frame_ticks) up to 255; otherwise it falls by 8 per frame down to 0 and the size
// (+0x14 / +0x16) follows it (2 * alpha). Returns 1 (done) once fading out reached 0; else moves the particle
// (particle_move_xz), scales its velocity by 0xF0 / 256 (particle_scale_vel_xyz) and returns 0.
/* was func_1516FF34 */
s32 particle_fade_shrink_tick(u8 *arg0) {
    s32 v;
    s32 t;

    v = arg0[0x1F];
    if (arg0[0x24] != 0) {
        if (v != 0xFF) {
            v += g_frame_ticks * 0x10;
            if (v >= 0x100) {
                v = 0xFF;
            }
            arg0[0x1F] = v;
        }
    } else {
        if (v != 0) {
            v -= g_frame_ticks * 8;
            if (v < 0) {
                v = 0;
            }
            arg0[0x1F] = v;
        }
        t = (v << 9) >> 8;
        *(s16 *)(arg0 + 0x16) = t;
        *(s16 *)(arg0 + 0x14) = t;
    }
    if ((arg0[0x24] == 0) && (v == 0)) {
        return 1;
    }
    particle_move_xz(arg0);
    particle_scale_vel_xyz((s32) arg0, 0xF0);
    return 0;
}

/* was func_1516FFF8 */
void particle_emitter_preset_at_pos(s16 arg0, s16 arg1, s16 arg2, s32 arg3, u8 arg4, s32 arg5) {
    particle_emitter_node_spawn(arg0, arg1, arg2, 0x1B, 0, 0xFF, 0xFF, 0xFF, 0, 0xFF, 0xFF, 0xFF, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x400, 0x400, 0, 0, 2, 0, 0, 0xFF, 0xF, 0, 0, 9, 0, 0xFF, 0xA, 0x5A, 5, arg3, 0, 0, (s32) arg4, arg5);
}

// sprite_fade_drift_tint_tick: particle tick (handler at 0x8008CF50, same scheme as particle_fade_shrink_tick): while +0x24
// (fading in) is set, alpha +0x1F rises by 16 per frame (g_frame_ticks) up to 255; otherwise it falls by
// g_frame_ticks << +0x2F down to 0. Returns 1 (done) once fading out reached 0. Else the size +0x14 / +0x16 grows by
// the signed rates +0x2D / +0x2E per frame; when the width reaches 0 or below both are cleared and it returns 1.
// Else the tint step +0x2C advances by g_frame_ticks (up to 0x7F) and the colour +0x1C..+0x1E blends from
// +0x26..+0x28 towards +0x29..+0x2B by 2 * step / 256; returns 0.
/* was func_1517013C */
s32 particle_fade_drift_tint_tick(u8 *arg0) {
    s32 v = arg0[0x1F];
    s32 t;

    if (arg0[0x24] != 0) {
        if (v != 0xFF) {
            v += g_frame_ticks << 4;
            if (v >= 0x100) {
                v = 0xFF;
            }
            arg0[0x1F] = v;
        }
    } else if (v != 0) {
        v -= g_frame_ticks << arg0[0x2F];
        if (v < 0) {
            v = 0;
        }
        arg0[0x1F] = v;
    }
    if (arg0[0x24] == 0 && v == 0) {
        return 1;
    }
    *(s16 *) (arg0 + 0x14) += (s8) arg0[0x2D] * g_frame_ticks;
    *(s16 *) (arg0 + 0x16) += (s8) arg0[0x2E] * g_frame_ticks;
    if (*(s16 *) (arg0 + 0x14) <= 0) {
        *(s16 *) (arg0 + 0x16) = 0;
        *(s16 *) (arg0 + 0x14) = *(s16 *) (arg0 + 0x16);
        return 1;
    }
    v = arg0[0x2C] + g_frame_ticks;
    if (v >= 0x80) {
        v = 0x7F;
    }
    arg0[0x2C] = v;
    t = v * 2;
    arg0[0x1C] = (((arg0[0x29] - arg0[0x26]) * t) >> 8) + arg0[0x26];
    arg0[0x1D] = (((arg0[0x2A] - arg0[0x27]) * t) >> 8) + arg0[0x27];
    arg0[0x1E] = (((arg0[0x2B] - arg0[0x28]) * t) >> 8) + arg0[0x28];
    return 0;
}

void particle_move_xz(u8 *arg0);

/* was func_151702C0 */
s32 particle_fade_rise_tick(u8 *arg0) {
    s32 v;
    s32 t;

    v = arg0[0x1F];
    if (arg0[0x24] != 0) {
        if (v != 0xFF) {
            v += g_frame_ticks * 0x10;
            if (v >= 0x100) {
                v = 0xFF;
            }
            arg0[0x1F] = v;
        }
    } else {
        if (v != 0) {
            v -= g_frame_ticks * 8;
            if (v < 0) {
                v = 0;
            }
            arg0[0x1F] = v;
        }
        t = (v << 9) >> 8;
        *(s16 *)(arg0 + 0x16) = t;
        *(s16 *)(arg0 + 0x14) = t;
    }
    if ((arg0[0x24] == 0) && (v == 0)) {
        return 1;
    }
    particle_move_xz(arg0);
    *(s16 *)(arg0 + 0x18) += ((s8 *)arg0)[0x2C];
    return 0;
}

/* was func_1516FE1C */
void particle_emitter_preset_obj_twin(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    struct {
        s32 uFC;
    } sp;
    f32 *temp_fp;
    s16 var_fp;
    s16 var_s7;
    s32 var_a0;
    s32 var_a1;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    struct127 *temp_t0;

    var_a0 = arg0;
    temp_t0 = &g_objects[var_a0];
    var_s1 = 0;
    var_s0 = 0;
    if (temp_t0->interaction_state == 1) {
        var_s7 = 4;
        var_fp = 0;
        var_s2 = 0x19;
        var_a1 = 1;
    } else {
        temp_fp = &temp_t0->x_position;
        var_s7 = (s16) ((s32) temp_fp >> 0x10);
        var_fp = (s16) temp_fp;
        var_a0 = 0xFF;
        var_a1 = 0x21;
        var_s2 = sp.uFC;
    }
    do {
        if (var_s0 == 1) {
            var_s2 = 0x1B;
            var_s1 = 8;
        }
        particle_emitter_node_spawn(var_s7, var_fp, 0, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, (u8) var_s1, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0xAA, 0xAA, 0xAA, 0xAA, (u16) (arg1 & 0xFFFF), 0x1EU, 0U, (u8) (var_a0 & 0xFF), 0x1EU, 0x168, 0x18U, (u16) (var_a1 & 0xFFFF), 4U, 0U, 1U, 0U, 0U, 0, (u8) var_s2, 0U, (u8) (s32) arg2, arg3);
        var_s0 += 1;
    } while (var_s0 != 2);
}
f32 math_cos_u8();
/* was func_151705A4 */
s32 particle_random_direction(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    s32 mask;
    s32 pad; // fakematch: frame slot 0x28
    f32 s;
    f32 c;
    s32 v;
    f32 t;

    mask = (arg0 & 0x40) ? 0x3F : 0x7F;
    v = random_int() & mask;
    *arg2 = math_cos_u8(v & 0xFF);
    c = math_sin_u8(v);
    v = random_int() & 0xFF;
    s = math_cos_u8(v & 0xFF);
    t = math_sin_u8(v);
    *arg1 = c * t;
    *arg3 = c * s;
}

s32 random_int(void);
extern f32 g_particle_edge_spark_spread[3]; /* spread per variant: 571, 130, 130; was D_8008CFA0 */
extern u8 g_particle_edge_spark_colours[9];  /* colour per variant (3 bytes); was D_8008CFAC */

// quad_edge_sparks_spawn: walks the 4 edges of `quad` (4 points of 3 floats) and spawns `countA` (edges 0 / 2) or
// `countB` (edges 1 / 3) sparks evenly along each edge (particle_sprite_spawn type 0xD, variant `variant`'s colour): the
// spark's push is the edge midpoint relative to (x, z) (doubled, as hi / lo bytes), its speed 731 * size + rand
// modulo 836 * size, life 15..46, spread 143 * size + rand modulo g_particle_edge_spark_spread[variant] * size. The caller's D_8008CF94 copy is unused.
/* was func_15170648 */
void particle_quad_edge_sparks(f32 *quad, f32 x, f32 z, s32 kind, f32 size, s32 variant, s32 countA, s32 countB, s32 alpha,
                   s32 owner) {
    f32 *p;
    f32 *q;
    u8 *col;
    s32 edge;
    s32 next;
    s32 n;
    s32 i;
    s32 range;
    s32 vx, vz;
    s32 speedBase, speedRange, spreadBase;
    s32 life;
    s32 speed;
    f32 mx, mz;
    f32 step;
    f32 t;
    f32 px, py, pz;

    range = (s32)(g_particle_edge_spark_spread[variant] * size);
    p = quad;
    for (edge = 0; edge < 4; edge++, p += 3) {
        next = (edge == 3) ? 0 : edge + 1;
        n = (edge == 0 || edge == 2) ? countA : countB;
        q = &quad[next * 3];
        col = &g_particle_edge_spark_colours[variant * 3];
        mx = (q[0] + p[0]) * 0.5f - x;
        mz = (q[2] + p[2]) * 0.5f - z;
        vx = (s32)(mx + mx);
        vz = (s32)(mz + mz);
        if (n <= 0) {
            continue;
        }
        speedBase = (s32)(731.0f * size);
        speedRange = (s32)(836.0f * size);
        spreadBase = (s32)(143.0f * size);
        step = 1.0f / (f32)(n - 1);
        for (i = 0; i < n; i++) {
            t = (f32)i * step;
            px = (q[0] - p[0]) * t + p[0];
            py = (q[1] - p[1]) * t + p[1];
            pz = (q[2] - p[2]) * t + p[2];
            life = (random_int() & 0x1F) + 15;
            speed = (u32)random_int() % (u32)speedRange + speedBase;
            particle_sprite_spawn((s16)(s32)px, (s16)(s32)py, (s16)(s32)pz, 0xD, 0, col[0], col[1], col[2], 0, 0, 0, 0, 2,
                          (vx >> 8) & 0xFF, vx & 0xFF, (vz >> 8) & 0xFF, vz & 0xFF, 0, 0, kind, 0, 0, 0, speed, speed,
                          life, (u32)random_int() % (u32)range + spreadBase, 0, 0, alpha, owner);
        }
    }
}

extern u16 g_objects_facing_angle; /* was D_800CC76A */
s32 game_gu_random(void);
f32 math_cos_u8(s32 angle); // defined (u8); the file's unprototyped declaration rules out u8 here
// spark_particle_spawn: one spark at (x, y, z) thrown in direction `angle` (the camera angle g_objects_facing_angle when `flare`
// is 0) with a random pitch (rand % 50, both signs), horizontal speed from sin / cos of the angle, fixed fall -0x32;
// flare != 0: long-lived flare particle (particle_sprite_spawn), else short spark (particle_emitter_node_spawn). alpha and arg6 pass through.
// Called by ambient_emitters_update (ambient_emitters_update) for torch / fire sparks and flare-ups.
/* was func_15170A70 */
void particle_spark_spawn(s32 x, s32 y, s32 z, s32 angle, s32 flare, s32 alpha, s32 arg6) {
    s32 pitch;
    f32 dirX;
    f32 dirZ;
    f32 tilt;
    f32 dx;
    f32 dz;
    f32 dy;
    s32 vx;
    s32 vz;
    s32 vy;

    if (flare == 0) {
        angle = g_objects_facing_angle;
    }
    pitch = game_gu_random() % 50;
    dirX = math_cos_u8(angle & 0xFF);
    dirZ = -math_sin_u8(angle & 0xFF);
    tilt = math_cos_u8(pitch & 0xFF);
    dx = dirX * tilt;
    dz = dirZ * tilt;
    dy = 0.0f;
    dx = dx + dx;
    dz = dz + dz;
    dy = dy + dy;
    vx = dx * 256.0f;
    vz = dz * 256.0f;
    vy = dy * 256.0f;
    if (flare != 0) {
        particle_sprite_spawn(x, y, z, 0x2A, 0, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 6, vx >> 8, vx & 0xFF, vz >> 8, vz & 0xFF,
                      0, 0, 0, 0, 0, 1, 0x200, 0x166, 0xFF, vy - 0x32, 0, 0, alpha & 0xFF, arg6);
    } else {
        particle_emitter_node_spawn(x, y, z, 0x2A, 0, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 6, vx >> 8, vx & 0xFF, vz >> 8, vz & 0xFF,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x200, 0x166, 0, 0, 0x14, 0, 0, 0xFF, 0xFF, vy - 0x32, 0xC8, 9,
                      1, 0, 1, 0x32, 0x14, 0, 0, 0, alpha & 0xFF, arg6);
    }
}

s32 game_gu_random(void);
// sprite_flicker_drift_tick: particle tick (handler at 0x8008CF58 of g_particle_sprite_tick_fns, same scheme as particle_fade_shrink_tick).
// While +0x24 (life) is set, the alpha +0x1F rises by 64 per frame (g_frame_ticks) up to 254; a particle whose alpha is
// still 0 first gets a life of 200..224 (random_int). Otherwise the alpha falls by 16 per frame down to 0, and
// the particle is done (returns 1) once it reached 0. Else it moves (particle_move_xz) and its velocity +0x26 / +0x28
// is scaled by a random (230 + -31..31) / 256 when +0x2F is set, or by (220 + -31..31) / 256 when the 8.8
// velocity +0x26 is above sqrt(1000); +0x18 is cleared and it returns 0.
/* was func_15170D50 */
s32 particle_flicker_drift_tick(u8 *arg0) {
    s32 alpha = arg0[0x1F];
    s32 vel;

    if (arg0[0x24] != 0) {
        if (alpha == 0) {
            arg0[0x24] = (u32) random_int() % 25 + 200;
        }
        if (alpha != 0xFE) {
            alpha += g_frame_ticks << 6;
            if (alpha >= 0xFF) {
                alpha = 0xFE;
            }
            arg0[0x1F] = alpha;
        }
    } else if (alpha != 0) {
        alpha -= g_frame_ticks << 4;
        if (alpha < 0) {
            alpha = 0;
        }
        arg0[0x1F] = alpha;
    }
    if (arg0[0x24] == 0 && alpha == 0) {
        return 1;
    }
    particle_move_xz(arg0);
    if (arg0[0x2F] != 0) {
        particle_scale_vel_x((s32) arg0, game_gu_random() % 32 + 0xE6);
        particle_scale_vel_z((s32) arg0, game_gu_random() % 32 + 0xE6);
    } else {
        vel = (*(s8 *) (arg0 + 0x26) << 8) + arg0[0x27];
        // the asm squares the +0x26 velocity twice (not +0x28); u32 keeps its wrap-around at vel = -0x8000
        if ((s32) ((u32) vel * vel + (u32) vel * vel) > 2000) {
            particle_scale_vel_x((s32) arg0, game_gu_random() % 32 + 0xDC);
            particle_scale_vel_z((s32) arg0, game_gu_random() % 32 + 0xDC);
        }
    }
    *(s16 *) (arg0 + 0x18) = 0;
    return 0;
}

s32 particle_random_direction(s32, f32 *, f32 *, f32 *);
/* was func_15170F24 */
void particle_burst_random_spawn(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, u8 arg5, s32 arg6) {
    s32 q0; // fakematch: unused locals pad the frame to 0xF8
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    s32 a;
    s32 b;
    s32 p0, p1; // fakematch: unused locals pad the frame

    for (i = 0; i < arg3; i++) {
        particle_random_direction(0x40, &x, &y, &z);
        x *= arg4;
        y *= 2.0f * arg4;
        z *= arg4;
        a = x;
        b = z;
        particle_sprite_spawn(arg0, arg1, arg2, 0x2F, 0, 0xFF, 0xFF, 0xFF, 0, 0xFF, 0, 0, 7, a >> 8, a & 0xFF, b >> 8, b & 0xFF, 0, 0, 0, 0, 0, 0, 0x200, 0x200, 0x28, y, 0, 0, arg5, arg6);
    }
}
