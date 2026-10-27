/* --- callees: C definitions elsewhere (signatures copied) --- */
void mp3_voice_play(s32 arg0, s32 arg1, s32 arg2);
void mp3_stream_set_volume(s32, s32);
void mp3_stream_stop(void);
void mp3_stream_pause(void);
void mp3_stream_resume(void);
void particle_emitter_node_spawn(s16 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA,
                   u8 argB, u8 argC, u8 argD, u8 argE, u8 argF, u8 arg10, u8 arg11, u8 arg12, u8 arg13, u8 arg14, u8 arg15,
                   u8 arg16, u8 arg17, u8 arg18, u8 arg19, u8 arg1A, s16 arg1B, s16 arg1C, s16 arg1D, s16 arg1E, u16 arg1F,
                   u8 arg20, u8 arg21, u8 arg22, u8 arg23, s16 arg24, u16 arg25, u16 arg26, u8 arg27, u8 arg28, u8 arg29,
                   u8 arg2A, u8 arg2B, s32 arg2C, u8 arg2D, u8 arg2E, u8 arg2F, s32 arg30);
void spark_sprite_burst_spawn(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9,
                   s16 argA, s16 argB, s16 argC, s32 argD, u8 argE, s32 argF);
void node_spawn_sprite_quad(void *arg0, u8 arg1, s32 arg2);
void beam_effect_spawn_attached(s32 arg0, u8 arg1, s16 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9,
                   s16 argA, s16 argB, u16 argC, u8 argD);
void particle_emitter_preset_packed_pos(u32 arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4);
void twin_particle_emitters_spawn(s32 arg0);
f32 math_sin_u8(u8 arg0);
void flash_smoke_emitter_spawn(u8 *arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5);
void crumble_emitter_spawn(u8 *arg0, u8 arg1, s32 arg2);
void obj_burning_fx_start(u8 *arg0, u8 arg1);
void water_ring_spawn(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s32 arg8);
void obj_blast_fx_spawn(u8 *arg0, s32 arg1, s32 arg2);
void point_emitter_spawn_preset(s32 arg0, s32 arg1, s32 arg2, s16 arg3, u8 arg4, s32 arg5);
s32 fb_zoom_fx_spawn(u8 *arg0, s16 arg1, s32 arg2, s32 arg3);
void bouncing_sprites_broadcast_drop(f32 arg0);
void effect_nodes_broadcast(s32, u8);
struct260 *segment_effect_spawn(u8 *arg0, s16 arg1, s8 arg2, s8 arg3, f32 arg4, s32 arg5, u8 arg6, s32 arg7);
struct260 *vent_smoke_emitter_spawn(u8 *arg0, s16 arg1, u8 arg2, s32 arg3);
struct225 *light_create_scripted(s32 arg0, s16 arg1, u8 arg2, s32 arg3);
void swing_lamp_post_target(s32 arg0, s32 arg1, u8 arg2);
void kind_effect_spawn(u8 arg0, u8 arg1, void *arg2, s32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, s32 arg8);
u8 *model_drip_create(u8 **arg0, s32 arg1, u8 arg2, s32 arg3);
void fb_fx_spawn_simple(s16 arg0, u8 arg1, s32 arg2);
struct260 *effect_node_create(s16 arg0, s8 arg1, s8 arg2, s8 arg3, u8 arg4, u8 arg5, struct37 *arg6, u8 arg7, s32 arg8);
void obj_bone_glow_emitter_spawn(u8 *arg0, s16 arg1, u8 arg2, s32 arg3);
void seqfx_track_effect_spawn(u8 *arg0, u16 arg1, s16 arg2, u8 arg3, s32 arg4);
void obj_bone_spark_emitter_spawn(u8 *arg0, s16 arg1, u8 arg2, u8 arg3);
void text_pager_spawn_caption(u8 arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4);
void text_pager_spawn_console(u8 arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4);
void text_pager_spawn_title(u8 arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4);
void seqfx_track_sprite_spawn(u8 *arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4);
s32 collision_floor_probe(u8 *arg0, u16 arg1, f32 arg2, u8 *arg3);
f32 random_float(void);
s32 random_int(void);
s32 fx_splash_spawn(f32 arg0, f32 arg1, u8 arg2, u8 arg3, s16 arg4, s32 arg5, struct17 *arg6, u8 arg7, u8 arg8, u8 arg9,
                  s32 argA);
void zap_bolt_spawn_path(u8 *arg0, u8 *arg1, s32 arg2, s16 arg3);
s32 rumble_request(structEU_151D8E18 *arg0, s32 arg1, u8 arg2, s32 arg3);
struct260 *electric_bolt_spawn(s16 arg0, u8 arg1, s32 arg2);
struct260 *body_dust_effect_start(u8 *arg0, s16 arg1, u8 arg2, s32 arg3);
s32 *bone_sparks_presets_for_kind(u8 *arg0, s32 *arg1);
s32 bone_sparks_attach_preset(s32 arg0, u8 arg1, s16 arg2, s8 arg3, s8 arg4, s8 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9);
s32 point_emitter_spawn(struct_eu_EF410 *arg0, s32 arg1, u8 arg2, s32 arg3);
s32 anim_fx_bone_emitter_spawn(u8 *arg0, s16 arg1, u8 arg2, u8 arg3);
void anim_fx_trail_spawn(u8 *arg0, s16 arg1, u8 arg2, u8 arg3);
void obj_bone_emitters_restart(u8 *arg0, s16 arg1, s32 arg2, s32 arg3);
u8 *seqfx_timer_create(s16 arg0, s32 arg1, u8 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6);
void particle_emitter_preset_obj_pair(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
void particle_emitter_preset_obj_burst(s32 arg0, s32 arg1, u8 arg2, s32 arg3);
void fx_ground_splats_around(struct127 *arg0, f32 arg1, u8 arg2, s32 arg3);
void hitinfo_from_obj_floor(void *out, u8 *obj);
void landing_dust_spray(u8 *arg0);
void swing_lamp_post_toggle(void);
u8 *attachment_find_by_slot(u8 *arg0, s32 arg1, s32 arg2);
void gun_muzzle_sparks_spawn(s32 arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4);
void gun_muzzle_flash_light(u8 *arg0, u8 arg1, s32 arg2);
void obj_bone14_spark_burst(u8 *arg0, u8 arg1, s32 arg2);
void obj_joint_spark_spray(u8 *arg0, u8 arg1, u8 arg2, s32 arg3);
void obj_bone_spark_spray(u8 *arg0, u8 arg1, s32 arg2);
void obj_muzzle_blast(u8 *arg0, u8 arg1, s32 arg2);
s32 life_pickup_spawn(f32 *arg0, f32 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6); /* P98 */
void obj_heavy_impact_fx(u8 *arg0, u8 arg1, s32 arg2);
void explosion_smoke_flash_spawn(u8 *arg0, u8 arg1, s32 arg2);
void mtx_transform_point_or_origin(void *arg0, void *arg1, void *arg2);
void fire_embers_spawn(void *arg0, u8 arg1, s32 arg2);
void laser_switch_broadcast(s32 arg0, s32 arg1);
void obj_angle_point_effect(u8 *arg0, s16 arg1, s16 arg2, u8 arg3, s32 arg4);
void aim_hud_send_flash(s32 arg0);
void seqfx_burst_spawn(f32 *arg0, u16 arg1, f32 arg2, u8 arg3, s32 arg4);
s32 object_arc_to_surface_spawn(u8 *, s16, s16, s16, s32, f32, f32, s32, s32, s8 *, s32, s32);
s32 particle_spawn_smoke_puff(u8 *arg0, f32 arg1, u8 arg2, s32 arg3);
void obj_set_dying_flags(struct127 *arg0);
void object_hit_effect(struct127 *arg0, s32 arg1, s32 arg2);
void obj_head_particle_burst(u8 *arg0, u8 arg1, s32 arg2);
void ground_dust_spawn(u8 *arg0, s16 arg1, u8 arg2, s32 arg3);
void emit_sparks_in_angle_range(struct_eu_15154488 *arg0, struct17 *arg1, s32 arg2, u8 arg3, s32 arg4);
void impact_spawn_debris_burst(struct17 *arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4);
void obj_bone_beam_impact(u8 *arg0, u8 arg1, u8 arg2, s32 arg3);
void smoke_column_spawn_far(s32 arg0);
void fx_twin_beams_spawn(u8 arg0);
void rubble_scatter_spawn(s32 arg0, f32 arg1, f32 arg2, s32 arg3, u8 arg4);
void rubble_scatter_spawn_ex(s32 arg0, f32 arg1, f32 arg2, s32 arg3, u16 arg4, s32 arg5, u8 arg6);
void debris_sparks_rect_by_type(u8 *arg0, u8 arg1, s32 arg2);
void debris_obj_destroy_by_id(struct127 *arg0, u8 arg1);
void debris_crate_break_by_level(s32 arg0, u8 arg1, s32 arg2);
void debris_obj_remove_explode(u8 *arg0);
void rubble_burst_with_dust(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4);
void particle_emitter_preset_obj3a(s32 arg0, s32 arg1, u8 arg2, s32 arg3);
void fx_point_emitter_spawn(s32 arg0, s32 arg1, s32 arg2, s16 arg3, u8 arg4, s32 arg5);
void *memcpy(void *s1, const void *s2, size_t n);
/* --- callees still in asm: declared from this function's call sites (arity and widths from the asm) --- */
void swarm_spawn(u8 kind, u8 *pos, s32, s32 x, s32 y, s32 z, s32, s32 span, s32 flag, s32, s32 w6);
void beam_trail_spawn(f32 *from, f32 *to, u8 flag, s32);
f32 math_cos_u8(u8 angle);
void particle_spray_pair_spawn(s32 x, s32 y, s32 z, s32 span, s32 dx, s32, s32 dz, s32, s32, s32, s32, s32, s32, s32, s32, s32 flag, s32);
s32 beam_effect_spawn(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32, s32, struct127 *, s32, s32,
                  s32, s32, s32, f32, f32, f32, f32, f32, f32);
void event_object_effect_spawn(u8 *obj, s16 span, s32, s32, f32, s32, s32 flag, s32);
void trail_follower_spawn(u8 *rec, s16 span, u8 flag, s32);
void damage_smoke_spawn(u8 *obj, s16 span, u8 flag, s32);
void screen_bar_spawn(s16 span, u8 flag, s32);
void obj_dust_effect(u8 *obj, s16 span, u8 flag, s32);
void score_banner_spawn(s16 span, u8 flag, s32);
s32 object_link_effect_spawn(u8 *obj, s32, s16 span, u8 flag, s32);
u8 *character_effect_attach(u8 *obj, s16 kind, s16 span, s32, s32 flag, s32, char *name);
void blood_splash_spawn(f32 *offset, f32, f32, f32, s32, s32, s32, s32 span, s32, s32, s32 flag, s32);
void beam_spawn_points(u8 *pos, u8 *, u8 *, u8 *, u8 *, s32 span, s32 flag, s32);
s32 char_fx_slot_derives(s16, s16);
s32 model_node_points_to_world(u8 *obj, u8 *att, s32, f32 **, u8 **, s32);
void object_shatter_effects(u8 *obj, u8 flag, s32);
void object_gun_fire(u8 *obj, u8 b5, s32, u8 *att, s32 kind, s32 flag, s32);
void object_explode(u8 *obj, u8 flag, s32);
s32 object_hit_effects(struct127 *, s32, s32, s32, s32, s32, s32, s32);
void obj_limb_muzzle_burst(u8 *obj, u8, u8, u8 flag, s32);
void debris_crate_break_pieces(void *pos, s32, s32, s32, s32 flag, s32);
s32 debris_spray_spawn(void *spray, s32, u8 flag, s32);
void smoke_columns_spawn(u8 flag);
void joint_beam_spawn(u8 *obj, s32, u8 flag, s32);
void trail_spawn_directed(u8 n, f32 x, f32 y, f32 z, s32, s32, s32, f32, s32, f32, f32, s32 flag);
void spark_effect_on_event(u8 *obj, s32, u8 flag);

/* one 8-byte script event (scene_event_run's table entry) */
typedef struct {
    s8  type;    /* 0x0B sound, 0x11 table byte, 0x05 effect */
    u8  delta;
    s16 id;      /* sound id / table index / effect sub-type */
    s8  b4;      /* mostly 0 = start, else stop / variant */
    s8  b5;
    s16 w6;
} ScriptEvent;

/* particle spray of sub-types 0x4D / 0x4E (debris_spray_spawn); 0x28 / 0x2C are left unset */
typedef struct {
    s16 count;
    f32 pos[3];
    s16 unk10;
    f32 unk14;
    s16 unk18, unk1A, unk1C, unk1E;
    f32 unk20, unk24, unk28, unk2C;
    f32 unk30, unk34, unk38, unk3C, unk40, unk44, unk48, unk4C, unk50;
    u8  unk54, unk55;
    s16 unk56, unk58;
} ScriptSpray;

extern u8  *g_cutscene_actor_blocks[4][30];      /* per player and track: byte table written by type 0x11; was D_800C3D80 */
extern s16 *D_eu_800C3C88[4][30];   /* per player and track: s16 x, y, z */
extern s32 *g_cutscene_words[4];          /* per player: word table indexed by w6; was D_800C3A00 */
extern s32 g_scene_ev0c_quad_word; /* was D_8008CDF0 */
extern u8 *g_char_fx_states[]; /* was D_8008AF88 */
extern f32 g_gun_smoke_start_pt[]; /* was D_800AAE70 */
extern char g_str_cutscene_2[];          /* "Cutscene 2"; was D_80096DEC */

extern u8 g_scene_ev11_colour_sets[3][6];         /* sub 0x11 colour sets (.data); was D_800844D8 */
/* bone offset tables of sub 0x5F (copied to the stack before use, as the N64 code does: their address is passed on) */
typedef struct { f32 v[3][3]; } ScriptOffsets3;
typedef struct { f32 v[4][3]; } ScriptOffsets4;
typedef struct { f32 v[6][3]; } ScriptOffsets6;
typedef struct { f32 v[2][3]; } ScriptOffsets2;
typedef struct { f32 v[8][3]; } ScriptOffsets8;
static const ScriptOffsets3 sOffsets5F10a = { { { 73, 14, 0 }, { 68, -10, 8 }, { 62, 1, -5 } } };            /* D_80096DF8 */
static const ScriptOffsets4 sOffsets5F10b = { { { -55, -6, -1 }, { -47, -1, -10 }, { -53, -14, 6 }, { -57, 10, 6 } } }; /* D_80096E1C */
static const ScriptOffsets6 sOffsets5F10c = { { { -1, 123, 10 }, { -10, 116, -1 }, { -36, 88, 6 },
                                                { 4, 112, 6 },  { -6, 112, -18 }, { -14, 101, 34 } } };   /* D_80096E4C */
static const s32 sBones5F10[3] = { 0x15, 0x20, 3 };                                                         /* D_80096E94 */
static const s32 sLights5F11[4] = { 6, 7, 8, 9 };                                                           /* D_80096EA0 */
static const ScriptOffsets2 sOffsets5F18 = { { { -65, 172, 9 }, { 15, 63, 9 } } };                          /* D_80096EB0 */
static const ScriptOffsets8 sOffsets5F19 = { { { 0, -14, 18 }, { 0, -14, 18 }, { 0, -14, 18 }, { 0, -14, 18 },
                                               { -5, 25, -7 }, { -11, 28, -5 }, { -4, 30, -4 }, { 3, 30, -8 } } }; /* D_80096EC8 */
static const u8 sBones5F19[8] = { 7, 8, 9, 10, 13, 14, 15, 16 };                                            /* D_80096F28 */

#define O_U8(o, off)  (*(u8 *) ((u8 *) (o) + (off)))
#define O_U16(o, off) (*(u16 *) ((u8 *) (o) + (off)))
#define O_S16(o, off) (*(s16 *) ((u8 *) (o) + (off)))
#define O_S32(o, off) (*(s32 *) ((u8 *) (o) + (off)))
#define O_F32(o, off) (*(f32 *) ((u8 *) (o) + (off)))
#define O_PTR(o, off) (*(u8 **) ((u8 *) (o) + (off)))

/* frames until the next event of this type and id on the track: the effect's duration */
#define SPAN(ev, out) (scene_event_find_next((u32) (ev), (ev)->type, track, (out), 1, (ev)->id, 0, 0, 0, 0, player) - now)
#define REC(player, track) ((u8 *) &(&g_cutscene_track_recs)[player][track])
#define OBJ_INDEX(obj) ((s32) ((u8 *) (obj) - (u8 *) g_objects) / 812)

/* Script event interpreter (middle handler of scene_event_run). `arg0` is one 8-byte ScriptEvent of track `track` of
 * player `player`; `now` = the current frame, `value` = the byte type 0x11 stores, `obj` / `rec` = the object or the
 * player's g_cutscene_track_recs record the track drives, `data` = its position (f32 x, y, z), `flag` = passed on to the effects.
 * Type 0x0B plays / fades / stops a sound, type 0x11 sets a per-track byte, type 0x05 starts effect `id` (most only
 * when b4 == 0; "span" = frames until the next event with the same type and id). Returns 1 when handled, else 0. */
s32 scene_event_run_b(s32 arg0, u8 track, u16 value, s32 now, s32 player, struct127 *obj, u8 *rec, u8 *data, s32 flag) {
    ScriptEvent *ev = (ScriptEvent *) arg0;
    f32 *pos = (f32 *) data;
    u8 *r;
    u8 *next;   /* out slot of scene_event_find_next (never read) */
    s32 span;
    s32 vol;
    s32 i;

    if (ev->type == 0x0B) {   /* sound */
        if (ev->b4 == 0) {
            mp3_voice_play(ev->id, ev->w6 == 0 ? 0x10000 : (ev->w6 << 16) / 255, 0x40);
        } else if (ev->b4 == 1) {
            span = scene_event_find_next((u32) ev, ev->type, track, &next, 1, ev->id, 1, 2, 0, 0, player) - now;
            vol = ev->w6 == 0 ? 0x10000 : (ev->w6 << 16) / 255;
            mp3_stream_set_volume(vol, (span * 0x5604) / 50);
        } else if (ev->b4 == 3) {
            mp3_stream_stop();
        } else if (ev->b4 == 4) {
            mp3_stream_pause();
        } else if (ev->b4 == 5) {
            mp3_stream_resume();
        }
        return 1;
    }
    if (ev->type == 0x11) {
        g_cutscene_actor_blocks[player][track][ev->id] = ev->b4 != 0 ? (u8) value : 0xFF;
        return 1;
    }
    if (ev->type != 5) {
        return 0;
    }

    switch (ev->id) {
    case 0x11: {   /* coloured burst: colour set b5, size w6 */
        const u8 *c;
        s32 size;
        s32 k;
        u8 grow;

        span = SPAN(ev, &next);
        if (ev->b4 != 0) {
            break;
        }
        if (ev->w6 == 0) {
            size = 0x1000;
        } else if (ev->w6 > 200) {
            size = ev->w6;
        } else {
            size = 200;
        }
        k = ev->b5 < 3 ? ev->b5 : 0;
        c = g_scene_ev11_colour_sets[k];   /* N64: from a stack copy of the table taken before the span call */
        grow = (size * 40) / 4096;
        /* a0 / a1: the two halves of the `data` pointer, as the N64 code passes them */
        particle_emitter_node_spawn((s16) ((s32) data >> 16), (s16) (s32) data, 0, 0x1B, 0, c[0], c[1], c[2], c[3], c[4], c[5], 0, 1,
                      6, 0, 0, 0, 0, 0, (size >> 3) >> 8, (size >> 3) & 0xFF, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, span, grow,
                      grow, 0xFF, 14, 8, 8, 0x25, 0, 0xFF, 8, 0, 0, player, 0, 0, flag, 0);
        break;
    }
    case 0x0A:
        span = SPAN(ev, &next);
        if (ev->b4 == 0) {
            spark_sprite_burst_spawn(3, 3, 0, 0, 0, 800, 1200, 400, 200, 0x66, 0x1C7, 2, span, (s32) data, flag, 0);
        }
        break;
    case 0x0B:
        span = SPAN(ev, &next);
        if (ev->b4 == 0) {
            spark_sprite_burst_spawn(0x2F, 1, 0, 0, 0, 2000, 1000, 400, 200, 0x400, 0x400, 6, span, (s32) data, flag, 0);
        }
        break;
    case 0x0C: {
        struct {
            s32 unk0;
            s16 unk4, unk6, x, y, z, unkE, unk10;
            s8 unk12;
            s8 unk13;
            s8 unk14;
        } s;
        s.unk4 = 0;
        s.unk6 = 0x100;
        s.unk0 = g_scene_ev0c_quad_word;
        s.x = pos[0];
        s.y = pos[1] + ev->b4;
        s.unkE = 1500;
        s.unk10 = 1500;
        s.unk12 = -10;
        s.unk14 = 0;
        s.z = pos[2];
        node_spawn_sprite_quad(&s, (u8) flag, 1);
        break;
    }
    case 0x19:
        span = SPAN(ev, &next);
        if (ev->b4 == 0) {
            swarm_spawn(ev->b5 != 0 ? ev->b5 : 12, data, 0xFF, pos[0], pos[1], pos[2], 0, span, flag, 0, ev->w6);
        }
        break;
    case 0x1A: {
        s16 *p = D_eu_800C3C88[player][track];
        f32 from[3], to[3];
        if (ev->b4 == 1) {
            from[0] = p[0];
            from[1] = p[1];
            r = REC(player, track);
            from[2] = p[2];
            to[0] = O_F32(r, 0);
            to[1] = O_F32(r, 0x38) + O_F32(r, 4);
            to[2] = O_F32(r, 8);
            beam_trail_spawn(from, to, (u8) flag, 1);
        } else {
            r = REC(player, track);
            beam_effect_spawn(0, p[0], p[1], p[2], O_F32(r, 0), O_F32(r, 0x38) + O_F32(r, 4), O_F32(r, 8), 40.0f, 0.0f, 8.0f,
                          60.0f, 600, 35, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
        }
        break;
    }
    case 0x1C:
        if (obj != NULL && (ev->b4 == 0 || ev->b4 == 1)) {
            beam_effect_spawn_attached((s32) obj, O_U8(obj, 0x3B), ev->b4 == 0 ? 3 : 2, -1, 0.0f, 0.0f, 156.0f, 0.0f, 0.0f, 636.0f, 3,
                          10, 0xF0, 0);
        }
        break;
    case 0x1B:
        span = SPAN(ev, &next);
        if (ev->b4 == 0) {
            switch ((u16) ev->w6) {
            case 0:
                particle_emitter_preset_packed_pos((u32) data, span, ev->b5, (u8) flag, 0);
                break;
            case 1:
                twin_particle_emitters_spawn(span);
                break;
            case 2: {   /* two sprays either side of the object, along its yaw */
                f32 x = O_F32(obj, 0x14);
                f32 y = O_F32(obj, 0x18);
                f32 z = O_F32(obj, 0x1C);
                u8 angle = O_U16(obj, 0x7A) >> 8;
                f32 sn = math_sin_u8(angle);
                f32 cs = math_cos_u8(angle);
                particle_spray_pair_spawn(x + 20.0f, y + 475.0f, z, span, 14.0f * sn, 0xB00, 14.0f * cs, 200, 50, 10, 6, 7, 0xBE,
                              0xBE, 0xBE, (u8) flag, 0);
                particle_spray_pair_spawn(x - 24.0f, y + 476.0f, z, span, -23.0f * sn, 0x800, -23.0f * cs, 200, 50, 10, 6, 7, 0xBE,
                              0xBE, 0xBE, (u8) flag, 0);
                break;
            }
            case 3:
                flash_smoke_emitter_spawn(data, span, 1, 1, flag, 0);
                break;
            case 4:
                flash_smoke_emitter_spawn(data, span, 0, 0, flag, 0);
                break;
            }
        }
        break;
    case 0x1F:
        if (obj != NULL) {
            crumble_emitter_spawn((u8 *) obj, (u8) flag, 1);
        }
        break;
    case 0x00:
        if (obj != NULL) {
            obj_burning_fx_start((u8 *) obj, (u8) flag);
        }
        break;
    case 0x20:
        water_ring_spawn(-1, pos[0], pos[1], pos[2], 20, 20, 1, flag, 1);
        break;
    case 0x06:
    case 0x3E:
    case 0x3F:
    case 0x2A:
        break;
    case 0x07:
        obj_blast_fx_spawn((u8 *) obj, 9, -1);
        break;
    case 0x21:
        if (ev->b4 == 0) {
            point_emitter_spawn_preset((s32) data, (s32) (data + 4), (s32) (data + 8), SPAN(ev, &next), flag, 0);
        }
        break;
    case 0x60:
        if (ev->b4 == 0) {
            fb_zoom_fx_spawn((u8 *) obj, SPAN(ev, &next), (u8) flag, 0);   /* 4th argument 0 (P80) */
        }
        break;
    case 0x65:
        if (ev->b4 == 2) {
            if (ev->b5 == 0x11 || ev->b5 == 0x12 || ev->b5 == 0x15) {
                s8 level = ev->w6;
                effect_nodes_broadcast((s32) &level, 0x51);
            } else if (ev->b5 == 0x13) {
                bouncing_sprites_broadcast_drop(ev->w6 * 0.01f * 300.0f - 150.0f);
            }
        }
        if (ev->b4 != 0) {
            break;
        }
        span = scene_event_find_next((u32) ev, ev->type, track, &next, 1, ev->id, 1, 1, 1, ev->b5, player) - now;
        switch (ev->b5) {
        case 1:
            event_object_effect_spawn((u8 *) obj, span, -1, 0, 0.00071f, 0, flag, 1);
            break;
        case 2:
            event_object_effect_spawn((u8 *) obj, span, -1, 1, 0.006125f, 0, flag, 1);
            break;
        case 3:
            segment_effect_spawn(rec, span, -1, 0, 0.006125f, 0, flag, 1);
            break;
        case 4:
            segment_effect_spawn(rec, span, -1, 1, 0.006125f, 0, flag, 1);
            break;
        case 5:
            vent_smoke_emitter_spawn((u8 *) obj, span, (u8) flag, 1);
            break;
        case 6:
            light_create_scripted(track, span, (u8) flag, 1);
            break;
        case 7:
            swing_lamp_post_target(track, span, (u8) flag);
            break;
        case 8: {
            f32 p[3];
            r = REC(player, track);
            p[0] = O_F32(r, 0);
            p[1] = O_F32(r, 4);
            p[2] = O_F32(r, 8);
            kind_effect_spawn(5, 1, NULL, (s32) p, -10000.0f, 100.0f, span, (u8) flag, 1);
            break;
        }
        case 9: {
            struct {
                struct127 *obj;
                u8 index;
                s16 span;
                u8 unk8, unk9, kind;
            } s;
            s.obj = obj;
            s.span = span;
            s.unk8 = 1;
            s.unk9 = 0;
            s.index = O_U8(obj, 0x3B);
            switch (O_U8(obj, 4)) {
            case 0x57:
            case 0x71:
                s.kind = 1;
                break;
            case 0x96:
                s.kind = 3;
                break;
            default:
                s.kind = 0;
                break;
            }
            model_drip_create((u8 **) &s, 0, (u8) flag, 1);
            break;
        }
        case 10:
            trail_follower_spawn(REC(player, track), span, (u8) flag, 1);
            break;
        case 11: {
            struct260 *e;
            s16 zero[2];
            fb_fx_spawn_simple(span, (u8) flag, 1);
            zero[0] = 0;
            zero[1] = 0;
            e = effect_node_create(span, -1, 0x4B, -1, 1, 0, (struct37 *) 4, (u8) flag, 1);
            if (e != NULL) {
                memcpy((u8 *) e + 0x28, zero, 4);
            }
            break;
        }
        case 12:
            obj_bone_glow_emitter_spawn((u8 *) obj, span, (u8) flag, 1);
            break;
        case 13:
            seqfx_track_effect_spawn(REC(player, track), (u16) ev->w6 < 0xE9 ? ev->w6 : 0, span, (u8) flag, 1);
            break;
        case 15:
            if (obj != NULL && span > 0) {
                O_S32(obj, 0x2EC) = 1;
                O_F32(obj, 0x2D8) = span * 0.5f;
                O_F32(obj, 0x2DC) = 1.0f / O_F32(obj, 0x2D8);
                damage_smoke_spawn((u8 *) obj, span, (u8) flag, 1);
            }
            break;
        case 16:
            if (obj != NULL && span > 0) {
                obj_bone_spark_emitter_spawn((u8 *) obj, span, (u8) flag, 1);
            }
            break;
        case 17:
            text_pager_spawn_caption(ev->w6 & 0xFF, g_cutscene_words[player][ev->w6], span, (u8) flag, 1);
            break;
        case 18:
            text_pager_spawn_console(ev->w6 & 0xFF, g_cutscene_words[player][ev->w6], span, (u8) flag, 1);
            break;
        case 19:
            screen_bar_spawn(span, (u8) flag, 1);
            break;
        case 20:
            obj_dust_effect((u8 *) obj, span, (u8) flag, 1);
            break;
        case 21:
            text_pager_spawn_title(ev->w6 & 0xFF, g_cutscene_words[player][ev->w6], span, (u8) flag, 1);
            break;
        case 22:
            seqfx_track_sprite_spawn(REC(player, track), (u16) ev->w6 < 0xCF ? (u16) ev->w6 : 0, span, (u8) flag, 1);
            break;
        case 23:
            score_banner_spawn(span, (u8) flag, 1);
            break;
        case 24: {   /* splash on the floor below the record, unless the surface is of kind 3 */
            f32 p[3];
            f32 probe[3];
            struct {
                f32 y;
                u8 pos[0x18];
                u8 flags;
                u8 surface;   /* +0x1D */
                u8 pad[0x6];
            } hit;
            s32 found;
            f32 ra;
            f32 rb;
            r = REC(player, track);
            p[0] = O_F32(r, 0);
            p[1] = O_F32(r, 4) + 100.0f;
            p[2] = O_F32(r, 8);
            probe[0] = p[0];
            probe[1] = p[1] + 100.0f;
            probe[2] = p[2];
            if (collision_floor_probe((u8 *) probe, 0, p[1] - 1000.0f, (u8 *) &hit) != 0 && hit.surface != 3) {
                found = 1;
                p[1] = hit.y;
            } else {
                found = 0;
            }
            if (found) {
                ra = random_float();
                rb = random_float();
                fx_splash_spawn(ra * 0.020000001f + 0.09f, rb * 0.00043999997f + 0.00087999995f,
                              (u32) random_int() % 101 + 0x9B, 0xFF, span, (s32) hit.pos, (struct17 *) p,
                              ev->w6 == 0, 1, flag, 1);
            }
            break;
        }
        case 25: {
            s16 *q = D_eu_800C3C88[player][track];
            f32 from[3];
            s32 to[3];
            r = REC(player, track);
            from[0] = q[0];
            from[1] = q[1];
            from[2] = q[2];
            to[0] = O_F32(r, 0);
            to[1] = O_F32(r, 4);
            to[2] = O_F32(r, 8);
            zap_bolt_spawn_path((u8 *) from, (u8 *) to, (s32) r, span);
            break;
        }
        case 26: {
            structEU_151D8E18 s;
            s.flags = 1;
            s.strength = 8;
            s.player_mask = 1;
            s.update_fn = -1;
            s.life = span;
            rumble_request(&s, 0, (u8) flag, 1);
            break;
        }
        }
        break;
    case 0x5B:
        if (ev->b4 == 0) {
            electric_bolt_spawn(SPAN(ev, &next), (u8) flag, 0);
        }
        break;
    case 0x5D:
        if (ev->b4 == 0) {
            body_dust_effect_start((u8 *) obj, SPAN(ev, &next), (u8) flag, 0);
        }
        break;
    case 0x5E:
        if (ev->b5 == 1) {
            object_link_effect_spawn((u8 *) obj, 0, 1000, (u8) flag, 0);
        } else if (ev->b4 == 0) {
            object_link_effect_spawn((u8 *) obj, 0, SPAN(ev, &next), (u8) flag, 0);
        }
        break;
    case 0x4C:
        if (ev->b4 == 0) {
            u8 kind = O_U8(obj, 4);
            span = SPAN(ev, &next);
            if (kind == 0x49 || kind == 0x58) {
                s32 n;
                u8 *list = (u8 *) bone_sparks_presets_for_kind((u8 *) obj, &n);
                if (list != NULL && ev->w6 < n) {
                    bone_sparks_attach_preset((s32) obj, list[ev->w6], span, -1, -1, -1, 0, 0, flag, 1);
                }
            } else {
                character_effect_attach((u8 *) obj, ev->b5, span, 0, flag, 1, g_str_cutscene_2);
            }
        }
        break;
    case 0x53:
        if (ev->b4 == 0) {
            struct_eu_EF410 s;
            span = SPAN(ev, &next);
            s.unk4 = (s32) (data + 4);
            s.unk8 = (s32) (data + 8);
            s.unk0 = (s32) data;
            s.unk14 = span;
            s.unk16 = 1;
            s.unk17 = 2;
            s.unkC = 2.0f;
            s.unk10 = 1.0f;
            point_emitter_spawn(&s, 0, (u8) flag, 0);
        }
        break;
    case 0x50:
        if (ev->b4 == 0) {
            anim_fx_bone_emitter_spawn((u8 *) obj, SPAN(ev, &next), (u8) flag, 0);
        }
        break;
    case 0x51:
        if (ev->b4 == 0) {
            anim_fx_trail_spawn((u8 *) obj, SPAN(ev, &next), (u8) flag, 0);
        }
        break;
    case 0x48:
        if (ev->b4 == 0) {
            f32 offset[2];
            f32 ra, rb, rc;
            u32 rd;
            span = scene_event_find_next((u32) ev, ev->type, track, &next, 1, ev->id, 0, 0, 1, ev->b5, player) - now;
            offset[0] = random_float() * 200.0f + -100.0f;
            offset[1] = random_float() * 300.0f + -150.0f;
            ra = random_float();
            rb = random_float();
            rc = random_float();
            rd = random_int();
            blood_splash_spawn(offset, ra * 20.0f + 10.0f, (rb * 65.0f + 35.0f) * 0.001f, (rc * 160.0f + 200.0f) * 0.001f,
                          rd % 101 + 100, 0xFF, (u32) random_int() % 3 + 4, span, 4, 0x40, flag, 1);
        }
        break;
    case 0x0F:
        span = SPAN(ev, &next);
        if (ev->b4 == 0) {
            obj_bone_emitters_restart((u8 *) obj, span, (u8) flag, 1);
        }
        break;
    case 0x32:
        span = SPAN(ev, &next);
        if (ev->b4 == 0) {
            r = REC(player, track);
            beam_spawn_points(data, r + 0x10, r + 0x18, r + 0x1C, r + 0x20, span, flag, 0);
        }
        break;
    case 0x34:
        span = SPAN(ev, &next);
        if (ev->b4 == 0) {
            u8 idx = 0;   /* N64: an uninitialised stack byte when b5 < 0 */
            u8 *node;
            if (ev->b5 >= 0) {
                idx = 13;
            }
            for (node = O_PTR(obj, 0x2F4); node != NULL; node = O_PTR(node, 0x14)) {
                if (idx == O_S16(node, 0x1C) || char_fx_slot_derives(O_S16(g_char_fx_states[idx], 4), O_S16(node, 0x1C)) != 0) {
                    r = REC(player, track);
                    O_S32(O_PTR(node, 0x10), 0x30) =
                        (s32) seqfx_timer_create(span, (s32) O_PTR(node, 0x10), 0, (s32) (r + 0x30), (s32) (r + 0x20), flag, 0);
                }
            }
        }
        break;
    case 0x23:
        if (obj != NULL) {
            span = SPAN(ev, &next);
            if (ev->b4 == 0) {
                particle_emitter_preset_obj_pair(OBJ_INDEX(obj), span, span, 0, flag, 0);
            }
        }
        break;
    case 0x22:
        if (obj != NULL) {
            span = SPAN(ev, &next);
            if (ev->b4 == 0) {
                particle_emitter_preset_obj_burst(OBJ_INDEX(obj), span, (u8) flag, 0);
            }
        }
        break;
    case 0x52:
        if (obj != NULL) {
            fx_ground_splats_around(obj, 90.0f, (u8) flag, 1);
        }
        break;
    case 0x5F:
        switch ((u8) ev->b4) {
        case 0:   /* drop on the floor below the object */
            if (obj != NULL) {
                struct {
                    f32 y;
                    u8 rest[0x20];
                } hit;
                f32 probe[3];
                f32 p[3];
                hitinfo_from_obj_floor(&hit, (u8 *) obj);
                probe[0] = O_F32(obj, 0x14);
                probe[1] = O_F32(obj, 0x18) + 100.0f;
                probe[2] = O_F32(obj, 0x1C);
                if (collision_floor_probe((u8 *) probe, 0, O_F32(obj, 0x18) - 300.0f, (u8 *) &hit) != 0) {
                    p[0] = probe[0];
                    p[1] = hit.y;
                    p[2] = probe[2];
                    landing_dust_spray((u8 *) p);
                }
            }
            break;
        case 1:
            swing_lamp_post_toggle();
            break;
        case 2:
            if (obj != NULL) {
                switch (O_U8(obj, 4)) {
                case 0x4A:
                    obj_joint_spark_spray((u8 *) obj, ev->b5, (u8) flag, 1);
                    break;
                case 0x5A:
                case 0x74:
                case 0x75:
                case 0x7A: {
                    u8 *att = attachment_find_by_slot((u8 *) obj, 0x46, 0);
                    if (att != NULL) {
                        u8 buf[16];
                        f32 *src = g_gun_smoke_start_pt;
                        u8 *dst = buf;
                        if (model_node_points_to_world((u8 *) obj, att, 0, &src, &dst, 1) != 0) {
                            gun_muzzle_sparks_spawn((s32) obj, (s32) buf, 0x46, (u8) flag, 1);
                            gun_muzzle_flash_light(buf, (u8) flag, 1);
                        }
                    }
                    break;
                }
                case 0x86:
                    obj_bone14_spark_burst((u8 *) obj, (u8) flag, 1);
                    break;
                case 0x97:
                    obj_bone_spark_spray((u8 *) obj, (u8) flag, 1);
                    break;
                case 0x98:
                    obj_muzzle_blast((u8 *) obj, (u8) flag, 1);
                    break;
                }
            }
            break;
        case 3: {
            f32 p[3];
            r = REC(player, track);
            p[0] = O_F32(r, 0);
            p[1] = O_F32(r, 4);
            p[2] = O_F32(r, 8);
            life_pickup_spawn(p, O_F32(r, 0x10), 1, 0, 2, flag, 1);
            break;
        }
        case 4:
            object_shatter_effects((u8 *) obj, (u8) flag, 1);
            break;
        case 5:
            if (obj != NULL) {
                u8 *att = NULL;
                if (ev->w6 != 0) {
                    att = attachment_find_by_slot((u8 *) obj, ev->b5 != 0 ? 0xA4 : 0xA5, 0);
                }
                object_gun_fire((u8 *) obj, ev->b5, 1, att, ev->b5 != 0 ? 0xA4 : 0xA5, flag, 1);
            }
            break;
        case 6:
            obj_heavy_impact_fx((u8 *) obj, 9, -1);
            break;
        case 7:
            object_explode((u8 *) obj, (u8) flag, 1);
            break;
        case 8: {
            f32 p[3];
            p[0] = pos[0];
            p[1] = pos[1];
            p[2] = pos[2];
            explosion_smoke_flash_spawn((u8 *) p, (u8) flag, 1);
            break;
        }
        case 9:
            object_hit_effects(obj, 1, 1, 1, 1, 0, flag, 1);
            break;
        case 10:   /* random offset from one of three bones */
            if (O_PTR(obj, 0x1D4) != NULL) {
                ScriptOffsets3 a = sOffsets5F10a;
                ScriptOffsets4 b = sOffsets5F10b;
                ScriptOffsets6 c = sOffsets5F10c;
                f32 *entry = a.v[0];   /* N64: uninitialised when b5 is not 0..2 */
                f32 out[3];
                switch (ev->b5) {
                case 0:
                    entry = a.v[(u32) random_int() % 3];
                    break;
                case 1:
                    entry = b.v[random_int() & 3];
                    break;
                case 2:
                    entry = c.v[(u32) random_int() % 6];
                    break;
                }
                mtx_transform_point_or_origin(entry, out, O_PTR(obj, 0x1D4) + (sBones5F10[ev->b5] << 6));
                fire_embers_spawn(out, (u8) flag, 1);
            }
            break;
        case 11: {
            u8 k = 0;
            do {
                laser_switch_broadcast(1, (s32) (g_level_zones + sLights5F11[k] * 0x34));
                k++;
            } while (k < 4);
            break;
        }
        case 12: {
            s32 ra = random_int();
            obj_angle_point_effect((u8 *) obj, ra & 0xFF, (random_int() & 0x7F) - 0x40, (u8) flag, 1);
            break;
        }
        case 13:
            aim_hud_send_flash((s32) g_player_views);
            break;
        case 14: {
            f32 p[3];
            p[0] = pos[0];
            p[1] = pos[1];
            p[2] = pos[2];
            seqfx_burst_spawn(p, (u16) ev->b5 < 0xE9 ? (u16) ev->b5 : 0, ev->w6 != 0 ? ev->w6 * 0.01f : 1.0f, (u8) flag, 1);
            break;
        }
        case 15: {   /* blue-white sparks */
            s8 colour[4];
            f32 size;
            s32 ra;
            u32 rb;
            colour[0] = 0xAE;
            colour[1] = 0xD2;
            colour[2] = 0xFF;
            colour[3] = (u32) random_int() % 61 + 150;
            size = random_float() * 20.0f + 25.0f;
            if (ev->b5 != 0) {
                size *= 0.35f;
            }
            ra = random_int();
            rb = random_int();
            object_arc_to_surface_spawn((u8 *) obj, ra & 0xFF, rb % 129 - 63, (u32) random_int() % 21 + 10, 4, 40.0f, size, 0, 2,
                          colour, flag, 1);
            break;
        }
        case 16:
            obj_limb_muzzle_burst((u8 *) obj, ev->b5, ((u8 *) ev)[7], (u8) flag, 1);
            break;
        case 17: {
            structEU_151D8E18 s;
            s.flags = 1;
            s.life = 50;
            s.strength = 8;
            s.player_mask = 1;
            s.update_fn = -1;
            rumble_request(&s, 0, (u8) flag, 1);
            break;
        }
        case 18:
            if (O_PTR(obj, 0x1D4) != NULL) {
                ScriptOffsets2 t = sOffsets5F18;
                f32 out[3];
                mtx_transform_point_or_origin(t.v[ev->b5], out, O_PTR(obj, 0x1D4));
                particle_spawn_smoke_puff((u8 *) out, 0.646f, (u8) flag, 0);
            }
            break;
        case 19:
            if (O_PTR(obj, 0x1D4) != NULL) {
                ScriptOffsets8 t = sOffsets5F19;
                f32 out[3];
                mtx_transform_point_or_origin(t.v[ev->b5], out, O_PTR(obj, 0x1D4) + (sBones5F19[ev->b5] << 6));
                particle_spawn_smoke_puff((u8 *) out, 6.9900002f, (u8) flag, 0);
            }
            break;
        case 20: {
            struct {
                u8 unk0[0x10];   /* not set */
                s16 x, y, z;
            } s;
            r = REC(player, track);
            s.x = O_F32(r, 0);
            s.y = O_F32(r, 4) + 50.0f;
            s.z = O_F32(r, 8);
            debris_crate_break_pieces(&s, 1, 1, 2, flag, 0);
            break;
        }
        case 21:
            if (obj != NULL) {
                obj_set_dying_flags(obj);
                object_hit_effect(obj, (u8) flag, 0);
            }
            break;
        case 22:
            if (obj != NULL) {
                obj_head_particle_burst((u8 *) obj, (u8) flag, 0);
            }
            break;
        }
        break;
    case 0x40:
        ground_dust_spawn((u8 *) obj, 0x28, (u8) flag, 1);
        break;
    case 0x4D: {
        ScriptSpray s;
        s.count = (u32) random_int() % 5 + 5;
        s.pos[0] = pos[0];
        s.pos[1] = pos[1];
        s.pos[2] = pos[2];
        s.unk14 = 4.7000003f;
        s.unk24 = 15.5f;
        s.unk20 = 24.800001f;
        s.unk3C = 0.26700002f;
        s.unk10 = 90;
        s.unk18 = -7;
        s.unk1A = 45;
        s.unk1C = -52;
        s.unk1E = 32;
        s.unk54 = 0;
        s.unk55 = 0;
        s.unk56 = 50;
        s.unk58 = 25;
        s.unk40 = 0.24300002f;
        s.unk44 = -2.0410001f;
        s.unk30 = 0.0f;
        s.unk34 = 0.0f;
        s.unk38 = 0.0f;
        s.unk4C = -3.0f;
        s.unk48 = 0.0f;
        s.unk50 = 6.0f;
        debris_spray_spawn(&s, 1, (u8) flag, 1);
        break;
    }
    case 0x4E: {
        ScriptSpray s;
        s.count = (u32) random_int() % 6 + 6;
        s.pos[0] = pos[0];
        s.pos[1] = pos[1];
        s.pos[2] = pos[2];
        s.unk14 = 151.5f;
        s.unk24 = 25.2f;
        s.unk20 = 15.1f;
        s.unk3C = 0.388f;
        s.unk10 = 90;
        s.unk1A = 0xFF;
        s.unk18 = 0;
        s.unk1C = -64;
        s.unk1E = 40;
        s.unk54 = 0;
        s.unk55 = 0;
        s.unk56 = 50;
        s.unk58 = 25;
        s.unk40 = 0.24300002f;
        s.unk44 = -1.0200001f;
        s.unk30 = 0.0f;
        s.unk34 = 0.0f;
        s.unk38 = 0.0f;
        s.unk4C = -4.0f;
        s.unk48 = 0.0f;
        s.unk50 = 8.0f;
        debris_spray_spawn(&s, 1, (u8) flag, 1);
        break;
    }
    case 0x4F: {
        struct_eu_15154488 s;
        s.unk8.unk0 = pos[0];
        s.unk8.unk4 = pos[1];
        s.unk8.unk8 = pos[2];
        s.unk2C = 15;
        s.unk2E = 10;
        s.unk0 = -20;
        s.unk14 = 2.9f;
        s.unk2 = 49;
        s.unk4 = -52;
        s.unk6 = 43;
        s.unk30 = 3;
        s.unk18 = 17.0f;
        s.unk32 = 4;
        s.unk34 = 40;
        s.unk36 = 30;
        s.unk38 = 100;
        s.unk3A = 100;
        s.unk3C = 0;
        s.unk44 = 16;
        s.unk46 = 15;
        s.unk48 = 0;
        s.unk1C = 2.5f;
        s.unk20 = 0.577f;
        s.unk24 = 25.0f;
        s.unk28 = 20.2f;
        s.unk40 = 0.5f;
        emit_sparks_in_angle_range(&s, &s.unk8, 0, (u8) flag, 1);
        break;
    }
    case 0x24: {
        f32 p[3];
        u8 kind;
        p[0] = pos[0];
        p[1] = pos[1];
        p[2] = pos[2];
        kind = ev->b5;
        if (kind >= 13) {
            kind = 0;
        }
        impact_spawn_debris_burst((struct17 *) p, ev->b4 != 0 ? ev->b4 : 10, kind, (u8) flag, 0);
        break;
    }
    case 0x10: {
        u8 kind = ev->b4;
        if (kind >= 27) {
            kind = 0;
        }
        obj_bone_beam_impact((u8 *) obj, kind, (u8) flag, 0);
        break;
    }
    case 0x47:
        obj_dust_effect((u8 *) obj, 50, (u8) flag, 0);
        break;
    case 0x2E:
        smoke_columns_spawn((u8) flag);
        smoke_column_spawn_far((u8) flag);
        fx_twin_beams_spawn((u8) flag);
        break;
    case 0x31:
        joint_beam_spawn((u8 *) obj, 0, (u8) flag, 0);
        break;
    case 0x33: {
        u8 n = ev->b4 >= 16 ? 15 : (u8) ev->b4;
        f32 scale;
        s32 b5;
        r = REC(player, track);
        b5 = 100;
        scale = O_F32(r, 0x1C) * 0.1f;
        if (ev->b5 != 0) {
            b5 = ev->b5;
        }
        trail_spawn_directed(n, pos[0], pos[1], pos[2], O_F32(r, 0x20) * 0.05f, (O_F32(r, 0x10) + 180.0f) * 0.7111111f,
                      O_F32(r, 0xC) * 0.7111111f, O_F32(r, 0x38) * 0.1f + 0.5f, b5, O_F32(r, 0x18) * 0.1f + 1.0f, scale,
                      flag);
        break;
    }
    case 0x35:
        spark_effect_on_event((u8 *) obj, ev->b4 >= 2 ? 1 : ev->b4, (u8) flag);
        break;
    case 0x26:
        if (obj != NULL) {
            span = SPAN(ev, &next);
            if (ev->b4 == 0) {
                O_U8(obj, 0x276) = 1;
                O_S16(obj, 0x282) = span;
            }
        }
        break;
    case 0x27:
    case 0x02: {
        f32 speed = 1.0f;
        f32 len = 30.0f;
        s32 n = 1;
        if (ev->b4 != 0) {
            n = ev->b4;
        }
        if (ev->b5 != 0) {
            speed = ev->b5 * 0.1f;
        }
        if (ev->w6 >= 0) {
            len = ev->w6;
        }
        if (ev->id == 0x27) {
            rubble_scatter_spawn((s32) data, len, speed, n, flag);
        } else {
            rubble_scatter_spawn_ex((s32) data, len, speed, n, 30, 100, (u8) flag);
        }
        break;
    }
    case 0x28:
        if (rec != NULL) {
            debris_sparks_rect_by_type(rec, (u8) flag, 0);
        } else if (obj != NULL) {
            debris_obj_destroy_by_id(obj, (u8) flag);
        }
        break;
    case 0x29:
        if (rec != NULL) {
            debris_crate_break_by_level((s32) rec, (u8) flag, 0);
        } else if (obj != NULL) {
            debris_obj_remove_explode((u8 *) obj);
        }
        break;
    case 0x2B:
        rubble_burst_with_dust(pos[0], pos[1], pos[2], (u8) flag, 0);
        break;
    case 0x2C:
        SPAN(ev, &next);
        break;
    case 0x2F:
        if (obj != NULL && ev->b4 == 0) {
            particle_emitter_preset_obj3a(OBJ_INDEX(obj), SPAN(ev, &next), (u8) flag, 0);
        }
        break;
    case 0x39:
        if (ev->b4 == 0) {
            fx_point_emitter_spawn((s32) data, (s32) (data + 4), (s32) (data + 8), SPAN(ev, &next), (u8) flag, 0);
        }
        break;
    case 0x3A: {
        f32 p[3];
        p[0] = pos[0];
        p[1] = pos[1];
        p[2] = pos[2];
        impact_spawn_debris_burst((struct17 *) p, ev->b4 != 0 ? ev->b4 : 10, 6, (u8) flag, 0);
        break;
    }
    default:
        return 0;
    }
    return 1;
}
