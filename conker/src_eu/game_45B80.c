#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
s32 game_frame_step(void);
void camera_player_update(s16 arg0);
void game_frame_begin(void);
void game_frame_end_update(void);
Gfx *render_overlay_pass(u8 *arg0);
Gfx *render_player_hud(Gfx *gdl, s32 arg1);
Gfx *render_final_overlay(Gfx *arg0);
void game_update_frame_timing(void);
#endif


void* node_render_layers_draw(void *arg0, s32 arg1, s16 arg2, s32 arg3);


/* was func_150186D0 */
void game_main_loop(void) {
    func_10001444();
    render_dl_buffers_init();
    func_151E6BFC();

    *(s16 *)&D_800BE5E0 = 1; // s16 in EU, u8 in US
    D_800D18A0 = 0;
    D_800D18A2 = 0;
    D_800D18A4 = 0;
    D_800D23A9 = 0;

    while (game_frame_step() != 0) {};

    D_8002AC60 = 1;
    D_8002AC64 = 3500;
    *D_800BE728 = func_1501BBB8();

    while (func_151DCFD8(1) != 0) {};
}

// something big and interesting
#ifdef NON_MATCHING
extern OSMesgQueue D_800BEE30;
extern u8 D_8002AFA0;
extern s16 D_8002AFA4;
extern u8 D_800BEA34;
extern u8 D_800BEA35;
extern s16 D_800BEEC8;
extern u8 D_800BEA50[];
extern u8 D_800BEFC0;
extern u8 D_800D9F38;
extern u8 D_800D9F10;
extern void *D_800BEFBC;
extern u8 D_800C1480[];
extern u8 D_80089810[];
extern s32 D_800BEFC4;
extern u8 D_800BEEE2;
extern Vp D_800D9FB0[][2];
void func_10004074(s32);
void effect_sample_zbuffer_cells(void);
void camera_projection_apply_pending_fov(void);
void func_1517D534(void);
void func_151E5928(void);
void camera_projection_apply_pending_viewport(void);
s32 world_update(void);
Gfx *render_player_frame_setup(Gfx *, s16);
Gfx *func_1515DC40(Gfx *, s32);
Gfx *render_player_scene(Gfx *, s16);
Gfx *render_player_3d_setup(Gfx *, s32);
Gfx *text_queue_draw(Gfx *);
void func_15084E80(void);
void texture_cache_age_tick(void);
void world_records_release_blocks(void);
void func_eu_1501C860(s32, s32);
void func_151F2BE8(void);
void func_151F2C4C(void);

/* Per-frame main step: wait for the frame message, then build and submit the frame's display list
 * (message 1), release the DL buffers when the game is torn down (message 2) or halt (message 4).
 * Returns 0 once the buffers were released, 1 otherwise. D_800BE9D0 is the DL write pointer. */
#define GDL (*(Gfx **)&D_800BE9D0)
/* was func_1501878C */
s32 game_frame_step(void) {
    OSMesg msg = NULL;
    s16 i;
    Gfx *saved;

    osRecvMesg(&D_800BEE30, &msg, OS_MESG_BLOCK);
    D_8002AFA0 = 0;
    D_8002AFA4 = 800;
    switch (*(s16 *)msg) {
        case 1:
            break;
        case 2:
            func_1517E71C();
            if (D_800DCE20 != 0) {
                effect_sample_zbuffer_cells();
            }
            D_800BEEC8--;
            if (D_800BEA35 == 0 || D_800BEEC8 != 0) {
                return 1;
            }
            func_10004074((s32)D_800BEDE8[0]);
            func_10004074((s32)D_800BEDE8[1]);
            D_800BEDE8[0] = NULL;
            return 0;
        case 4:
            while (func_151DD588(1) != 0) {
            }
            for (;;) {
            }
        default:
            return 1;
    }

    if (D_800BEA35 != 0) {
        return 1;
    }
    func_151E5928();
    if (D_800BEA35 != 0) {
        return 1;
    }
    if (D_800BEA34 != 0) {
        render_dl_buffers_init();
        D_800BEA34 = 0;
    }
    if (D_800D9F10 != 0) {
        camera_projection_apply_pending_fov();
    }
    if (D_800D9F38 != 0) {
        camera_projection_apply_pending_viewport();
    }
    game_frame_begin();
    if (D_800BEAC0 == 0 && world_update() == 0) {
        return 1;
    }

    GDL = render_set_color_image(GDL);
    func_1515DC0C();
    node_lists_run_view_update();
    for (i = 0; i <= D_80082FA0; i++) {
        D_80082FA4 = D_800BEA50[i];
        camera_player_update(D_80082FA4);
        GDL = render_player_frame_setup(GDL, D_80082FA4);
    }

    if (D_800BEFC0 == 0) {
        /* Back to the main microcode (text D_800C1480, data D_800BEFBC), then the base render state. */
        gSPLoadUcodeEx(GDL++, D_800C1480, D_800BEFBC, 0x800);
        gSPGeometryMode(GDL++, 0x3D0605, 0);
        gSPSetGeometryMode(GDL++, 0x220005);
        gSPMatrix(GDL++, D_80089810, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gDma2p(GDL++, G_MOVEMEM, &D_800D9FB0[D_800BE9C0][0], sizeof(Vp), G_MV_LIGHT, 0);
        gDma2p(GDL++, G_MOVEMEM, &D_800D9FB0[D_800BE9C0][1], sizeof(Vp), G_MV_LIGHT, 48);
    }

    for (i = 0; i <= D_80082FA0; i++) {
        saved = GDL;
        D_80082FA4 = D_800BEA50[i];
        GDL = func_1515DC40(GDL, D_80082FA4);
        GDL = render_player_scene(GDL, D_80082FA4);
        /* Out of DL space: drop this player's view. */
        if (D_800BEFC4 < GDL - D_800BEDE8[D_800BE9C0]) {
            GDL = saved;
        }
    }
    D_80082FA4 = 0;
    game_frame_end_update();
    GDL = render_overlay_pass((u8 *)GDL);

    for (i = 0; i <= D_80082FA0; i++) {
        D_80082FA4 = D_800BEA50[i];
        GDL = func_1515DC40(GDL, D_80082FA4);
        GDL = render_player_3d_setup(GDL, D_80082FA4);
        if (D_800BEAC0 == 0 && D_80082FA0 > 0) {
            GDL = render_player_hud(GDL, D_80082FA4);
        }
    }
    GDL = render_final_overlay(GDL);
    if (D_800BEAC0 == 0 && D_80082FA0 == 0) {
        for (i = 0; i <= D_80082FA0; i++) {
            D_80082FA4 = D_800BEA50[i];
            GDL = render_player_hud(GDL, D_80082FA4);
        }
    }
    GDL = func_151E8C60(GDL);
    GDL = text_queue_draw(GDL);
    func_15034AD8();
    func_1502E764();
    func_15189688(0);
    func_15084E80();
    camera_tick_timers();
    gDPFullSync(GDL++);
    gSPEndDisplayList(GDL++);
    func_10004674();
    texture_cache_age_tick();
    world_records_release_blocks();
    func_1517D534();
    func_eu_1501C860(0, 1);
    D_800BE9B4 = 0;

    if (D_800BEAC0 != 0) {
        D_800BEEE2 = 2;
    } else if (D_800BEEE2 > 0) {
        D_800BEEE2--;
    }
    if (D_800BEAC1 != D_800BEAC0) {
        D_800BEAC0 = D_800BEAC1;
        if (D_800BEAC0 != 0) {
            func_1000E2F4(1);
            func_10011E94(1);
            if (func_151F2CDC() != 0) {
                func_151F2BE8();
            }
        } else {
            func_1000E2F4(0);
            func_10011E94(0);
            if (func_151F2CDC() != 0) {
                func_151F2C4C();
            }
        }
    }
    return 1;
}
#undef GDL
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/game_frame_step.s")
#endif
/* was func_15018DFC */
void world_update_objects(void) {
    func_150A09D0(D_800BE9E4);
    objects_update_visibility();
    func_1501C870();
    if (D_800BEAC0 == 0) {
        if (D_800C35EA == 1) {
            func_1502378C();
        } else {
            func_1504A730();
        }
        func_15085ABC(D_800D2340);
    }
    func_1507C370();
    player_update_life_states();
}

#ifdef NON_MATCHING
/* P13: returns the DL pointer. The matching C is void, but the asm leaves func_15174AA4's result in v0 and
 * render_player_scene uses it as the new GDL. */
/* was func_15018E88 */
void *render_scene_layers_pre(void *arg0, s16 arg1) {
    if (D_800BE616 == 0) {
        func_1517D7B0(&arg0, 1);
    }
    arg0 = node_render_layers_draw(arg0, 0, arg1, 0);
    arg0 = node_render_layers_draw(arg0, 0, arg1, 1);
    return func_15174AA4(arg0, D_800BE9F0, arg1);
}
#else
void render_scene_layers_pre(void *arg0, s16 arg1) {
    if (D_800BE616 == 0) {
        func_1517D7B0(&arg0, 1);
    }
    arg0 = node_render_layers_draw(arg0, 0, arg1, 0);
    arg0 = node_render_layers_draw(arg0, 0, arg1, 1);
    func_15174AA4(arg0, D_800BE9F0, arg1);
}
#endif

/* was func_15018F08 */
void *render_scene_layers_post(void *arg0, s16 arg1) {
    arg0 = func_15174B48(arg0, D_800BE9F0, arg1);
    arg0 = node_render_layers_draw(arg0, 1, arg1, 0);
    arg0 = node_render_layers_draw(arg0, 1, arg1, 1);

    func_1517D7B0(&arg0, 2);

    return arg0;
}

/* was func_15018F80 */
void camera_player_update(s16 arg0) {
    struct108 *sp24 = &D_800DBFF0[arg0];
    D_8003C8E0 = 0xA000000;
    if ((func_1517F40C(arg0) == 0) && (D_800BEAC0 == 0)) {
        func_1517F448(arg0);
    }
    func_1501B640(arg0);
    D_800D3674 = (sp24->unk388 < 0.0f) ? -1000 : 5000;
    func_15172D80(arg0);
    D_8003C8E0 = 0;
}

/* was func_1501905C */
void game_frame_begin(void) {
    D_800BE9D0 = D_800BE9D8[D_800BE9C0];
    *D_800BE728 = func_1501BBB8();
    game_update_frame_timing();
    if ((D_800BEAC1 != 0) && (D_800BEAC0 == 0)) {
        node_broadcast_all(0, 0x47);
    }
    func_1501C1B0();
    func_1501BB20();
    func_1502C380();
    if (0) {};
    func_1000D758(D_800DBFF0->unk2A4, D_800DBFF0->unk2A8, D_800DBFF0->unk2AC);
    func_10011BB8();
    if (D_800E0B94 == 2) {
        random_seed(0x81280783); // 2166884227
    }
    func_10012020();
}

// few loops
#ifdef NON_MATCHING
// Per-frame world update (P13 from the P12 convert.py EQUIV, prototypes cleaned): camera/objects/players/effects
// steps, then ages the 0x20-byte records D_80043ED0..D_80044B20 (four counters each). Returns 1 (game_frame_step
// builds the frame only when this is nonzero).
extern s32 D_80043ED0;
extern s8 D_800D27C9;
void func_10004250(void);
void world_update_objects(void);
void func_1501C860(void);
void func_1501E364(s32 arg0);
void func_1501E46C(s32 arg0);
void func_1501ECA4(s32 arg0);
void func_15020F6C(s32 arg0);
void func_1502457C(s32 arg0, s32 arg1);
void func_1502C1D4(void);
void func_1502C494(void);
void func_15035210(void);
void func_15036438(void);
void func_15044D18(void);
void func_1504ADD0(void);
void func_15063AA0(void);
void func_15088130(void);
void func_150952B0(s32 arg0);
void event_list_unload(s32 arg0);
void event_list_run_phase(s32 arg0);
void func_150A126C(void);
void camera_matrices_refresh_all(void);
void segment_override_clear(void);
void collision_select_area(s32 arg0);
void player_zone_update(s32 arg0);
void world_records_build_visible(s32 arg0);
void world_records_flag_active(void);
void world_records_update_matrices(void);
void world_records_update_shadows(void);
void world_records_run_callbacks(s32 arg0);
void world_records_dispatch_touches(void);
void func_1511FC20(s32 arg0);
void camera_update_all(void);
void func_1515DC38(void);
void node_run_global_hooks(void);
void node_lists_run_update(void);
void node_lists_run_update2(void);
void func_15173E34(s32 arg0);
void func_15174F68(s32 arg0, s32 arg1);
void func_15178004(void);
void func_1517FCCC(void);
void func_1517FD24(void);
void func_15181A6C(void);
void func_15184298(void);
void func_151890E4(s32 arg0);

/* was func_15019130 */
s32 world_update(void) {
    s32 i;
    u8 j;
    s32 *p;

    segment_override_clear();
    event_list_unload(0);
    event_list_run_phase(2);
    D_800DD157 = 0;
    func_10004250();
    func_1501E46C(0);
    func_15035210();
    camera_matrices_refresh_all();
    collision_select_area(0);
    world_records_flag_active();
    if (D_800BEAC0 == 0) {
        world_records_run_callbacks(1);
    }
    if (D_800BEAC0 == 0) {
        world_records_dispatch_touches();
    }
    func_15044D18();
    world_update_objects();
    func_1502457C(1, 0);
    func_1501ECA4(0);
    func_1502457C(0, 0);
    func_15020F6C(0);
    func_1501E364(0);
    if (D_800D27C9 != 0) {
        func_15088130();
    }
    camera_update_all();
    func_1504ADD0();
    collision_select_area(0);
    for (i = 0; i <= D_80082FA0; i++) {
        player_zone_update(i);
    }
    camera_matrices_refresh_all();
    for (j = 0; j <= D_80082FA0; j++) {
        func_150952B0(j);
    }
    world_records_build_visible(0);
    func_15174F68(D_800BE9F0, 0);
    func_1501C860();
    func_1511FC20(D_800BE9C0);
    func_151890E4(0);
    if (D_800BEAC0 == 0) {
        node_run_global_hooks();
        node_lists_run_update2();
    }
    func_1502C1D4();
    if (D_800BE616 == 0) {
        func_150A126C();
    }
    world_records_update_matrices();
    func_151890E4(1);
    func_15173E34(D_800BE9F0);
    func_1502C494();
    world_records_update_shadows();
    if (D_800CC2B0 != 0) {
        func_15063AA0();
    }
    if (D_800BEAC0 == 0) {
        func_15184298();
        node_lists_run_update();
        func_15178004();
    }
    if (D_800BEAC0 == 0) {
        func_15181A6C();
    }
    func_1517FCCC();
    func_1517FD24();
    func_15036438();
    func_1515DC38();
    p = &D_80043ED0;
    do {
        p[1]++;
        p[3]++;
        p[5]++;
        p[7]++;
        p += 8;
    } while (p != &D_80044B20);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/world_update.s")
#endif
/* was func_15019414 */
void game_frame_end_update(void) {
    if (D_800BEAC0 == 0) {
        node_types_run_frame_hooks();
    }
    func_1517ABB0();
    if (D_800BE616 == 0) {
        hud_health_air_update();
    }
}

#ifdef NON_MATCHING
// Per-player frame setup: camera update, viewport, the player's view DL (render_set_scissor) and,
// in normal play (not paused, no cutscene flag, player view active), the light words and player_view_dl_build.
extern s16 D_80084810;
void camera_zoom_factors_calc(s16 player);
Gfx *view_background_draw(Gfx *gdl, s32 arg1);
s32 func_1517F51C(s32 player);
Gfx *player_view_dl_build(Gfx *gdl, s16 player);

/* was func_15019464 */
Gfx *render_player_frame_setup(Gfx *gdl, s16 player) {
    camera_zoom_factors_calc(player);
    gSPViewport(gdl++, (u8 *)D_800BE628 + player * 0x180 + D_800BE9C0 * 16 + 0x40);
    gdl = (Gfx *)render_set_scissor((s32)gdl, player, 0, 0, 0, 0);
    if (D_800BEAC0 != 0) {
        return gdl;
    }
    if (D_80084810 != 0) {
        return gdl;
    }
    gdl = view_background_draw(gdl, D_800BE9F0);
    if (func_1517F51C(player) != 0 || (D_800D18A0 & (1 << player))) {
        return gdl;
    }
    gdl = func_1515DC40(gdl, player);
    return player_view_dl_build(gdl, player);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/render_player_frame_setup.s")
#endif
// NON-MATCHING: 70% of the way there... maybe.
// s32 render_player_frame_setup(Gfx *arg0, s16 arg1) {
//     s32 temp_s0;
//     s32 ret;
//
//     func_1510B958(arg1);
//     gSPViewport(arg0++, (D_800BE628 + (arg1 * 0x180) + (D_800BE9C0 * 0x10) + 0x40));
//     // arg0->unk0 = 0xDC080008;
//     // arg0->unk4 = (s32) (D_800BE628 + (temp_t6 * 0x180) + (D_800BE9C0 * 0x10) + 0x40);
//     temp_s0 = render_set_scissor(arg0, arg1, 0, 0, 0, 0);
//     if ((D_800BEAC0 != 0) || (D_80084480 != 0)) {
//         return temp_s0;
//     }
//
//     temp_s0 = func_1510FEA0(temp_s0, D_800BE9F0);
//     if ((func_1517EFAC(arg1) != 0) || ((D_800D18A0 & (1 << arg1)) != 0)){
//         return temp_s0;
//     }
//
//     temp_s0 = func_1515D6D0(temp_s0, arg1);
//     temp_s0 = func_1510B9D0(temp_s0, arg1);
//     return temp_s0;
//
// }

#ifdef NON_MATCHING
/* Per-player scene pass (P13, hand C). Skipped (returns gdl) while paused (D_800BEAC0), during D_80084810, when
 * func_1517F51C(player) says so or the player's bit in D_800D18A0 is set. In split screen it first sets the
 * player's viewport/projection; then the layers in order: sky (world_meshes_draw_player 1), the D_800BE575 == 2 pass,
 * model group 6, func_15186D04, the projection again, func_1502BDC0 1, func_150362D8, the fixed matrix, the
 * world (render_scene_layers_pre / world_meshes_draw_player 0 / render_scene_layers_post, order by player flag 0x5F0 bit 0), func_15189270 0/1,
 * func_1502BDC0 2 and model group 2. */
void *render_scene_layers_pre(void *arg0, s16 arg1);
Gfx *view_dl_begin(Gfx *arg0, s32 arg1);
Gfx *world_meshes_draw_player(Gfx *arg0, s32 arg1, s16 arg2);
Gfx *func_15186D04(Gfx *arg0, s32 arg1);
Gfx *func_150362D8(Gfx *arg0, s32 arg1);
Gfx *func_1502BDC0(Gfx *arg0, s32 arg1, s16 arg2);
Gfx *func_15189270(Gfx *gfx, s32 arg1, s16 arg2);
u8 *func_151D6D28(u8 *);

/* was func_150195A0 */
Gfx *render_player_scene(Gfx *arg0, s16 arg1) {
    s32 player = arg1;
    u8 *pl = (u8 *)D_800DBFF0 + player * 0x9A0;
    Gfx *gdl = arg0;

    if (D_800BEAC0 != 0) {
        return gdl;
    }
    if (D_80084810 != 0) {
        return gdl;
    }
    if (func_1517F51C(player) != 0 || (D_800D18A0 & (1 << player))) {
        return gdl;
    }
    if (D_80082FA0 > 0) {
        gdl = view_dl_begin(gdl, player);
        gdl = func_1515DC40(gdl, player);
        camera_zoom_factors_calc(player);
        gdl->words.w0 = 0xDC080008;
        gdl->words.w1 = D_800BE628 + player * 0x180 + D_800BE9C0 * 16 + 0x40;
        gdl = (Gfx *)render_set_scissor((s32)(gdl + 1), player, 0, 0, 0, 0);
    }
    gdl = world_meshes_draw_player(gdl, 1, player);
    if (D_800BE575 == 2) {
        gdl = (Gfx *)func_151D6D28((u8 *)gdl);
    }
    gdl = node_render_layers_draw(gdl, 6, player, 0);
    gdl = node_render_layers_draw(gdl, 6, player, 1);
    gdl = func_15186D04(gdl, player);
    gdl = (Gfx *)render_set_scissor((s32)gdl, player, 0, 0, 0, 0);
    gdl = func_1502BDC0(gdl, 1, player);
    gdl = func_150362D8(gdl, player);
    gdl->words.w0 = 0xDA380003;
    gdl->words.w1 = (u32)D_80089810;
    gdl++;
    if (*(s32 *)(pl + 0x5F0) & 1) {
        gdl = render_scene_layers_pre(gdl, player);
        gdl = world_meshes_draw_player(gdl, 0, player);
        gdl = render_scene_layers_post(gdl, player);
    } else {
        gdl = render_scene_layers_post(gdl, player);
        gdl = world_meshes_draw_player(gdl, 0, player);
        gdl = render_scene_layers_pre(gdl, player);
    }
    gdl = func_15189270(gdl, 0, player);
    gdl = func_15189270(gdl, 1, player);
    gdl = func_1502BDC0(gdl, 2, player);
    gdl = node_render_layers_draw(gdl, 2, player, 0);
    gdl = node_render_layers_draw(gdl, 2, player, 1);
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/render_player_scene.s")
#endif
#ifdef NON_MATCHING
u8 * hud_draw(u8 *);
s32 func_151734E0(s32);
s32 func_1517E7FC(s32, s32);
u8 * func_1517FAD4(s32);
s32 func_15182450(s32);
s32 func_151D6440(u8 *, s32, s32, s32);
void func_151D6760(s32);
u8 * func_151D6D28(u8 *);
extern s32 D_8002AE20;
extern s8 D_80083320;

/* was func_150198FC */
Gfx *render_overlay_pass(u8 *arg0) {
    s32 var_s0_3;
    u8 *temp_s0;
    u8 *temp_v0;
    u8 *var_s0;
    u8 *var_s0_2;
    u8 *var_s0_4;

    var_s0 = arg0;
    if (D_800BE575 == 1) {
        var_s0 = func_151D6D28(var_s0);
    }
    if (D_80082FA0 != 0) {
        D_80082FA4 = D_80082FA0 + 1;
        (*(s32 *)((u8 *)var_s0 + 0)) = 0xDC080008;
        (*(s32 *)((u8 *)var_s0 + 4)) = (s32) ((D_80082FA4 * 0x180) + D_800BE628 + 0x40);
        var_s0_2 = var_s0 + 8;
    } else {
        (*(s32 *)((u8 *)var_s0 + 0)) = 0xDC080008;
        var_s0_2 = var_s0 + 8;
        (*(s32 *)((u8 *)var_s0 + 4)) = (s32) (D_800BE628 + 0x40);
    }
    var_s0_3 = render_set_scissor((s32) var_s0_2, 0xFF, 0, 0, 0, 0);
    if (D_800BEAC0 != 0) {
        if (D_80083320 == 0) {
            (*(s32 *)((u8 *)var_s0_3 + 0)) = (s32) (((D_800BE620 - 1) & 0xFFF) | 0xFF100000);
            temp_s0 = var_s0_3 + 8;
            (*(s32 *)((u8 *)var_s0_3 + 4)) = (s32) D_800BEDE4;
            (*(s32 *)((u8 *)temp_s0 + 0)) = 0xED000000;
            (*(s32 *)((u8 *)temp_s0 + 4)) = (s32) ((((s32) ((f32) D_800BE620 * 4.0f) & 0xFFF) << 0xC) | ((s32) ((f32) D_800BE624 * 4.0f) & 0xFFF));
            var_s0_3 = render_set_color_image(func_151D6440(temp_s0 + 8, *(((s32 *)((u8 *)&D_8002AE20 + -(D_800BE9C0 * 4)))), 0, 1));
            D_80083320 = 1;
        } else if (D_80083320 < 5) {
            D_80083320 += 1;
            func_151D6760(D_800BEDE4);
        }
        var_s0_3 = func_151D6440((u8 *) var_s0_3, D_800BEDE4, 0, 1);
    } else {
        D_80083320 = 0;
    }
    if (func_1517F51C(0) == 0) {
        var_s0_3 = func_15182450(func_151734E0(func_1517E7FC(var_s0_3, D_800BE9F0)));
    }
    temp_v0 = func_1517FAD4(var_s0_3);
    var_s0_4 = temp_v0;
    if ((D_800BEAC0 == 0) && (D_800BEAC1 == 0)) {
        var_s0_4 = hud_draw(temp_v0);
    }
    return (Gfx *)func_15096D44(node_render_layers_draw(node_render_layers_draw(var_s0_4, 3, 0, 0), 3, 0, 1));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/render_overlay_pass.s")
#endif
extern u16 D_800D1CC2;
#ifdef NON_MATCHING
void func_15151FA8(u8 *arg0, s32 arg1, s32 arg2);
#else
Gfx *func_15151FA8();
#endif
/* was func_15019BB8 */
Gfx *render_player_hud(Gfx *gdl, s32 arg1) {
    gSPViewport(gdl++, (u8 *)D_800BE628 + arg1 * 0x180 + 0x40 + D_800BE9C0 * 0x10);
    gdl = render_set_scissor(gdl, (s16)arg1, 0, 0, 0, 0);
    gdl = func_1517FA48(gdl, arg1);
    gdl = func_1517F910(gdl, arg1);
    gdl = func_15180AF0(gdl, arg1);
    if ((D_800D18A0 & (1 << arg1)) || (D_800D1CC2 & (1 << arg1))) {
        gdl = player_draw_out_overlay(gdl, arg1);
    }
    gdl = node_render_layers_draw(gdl, 4, (s16)arg1, 0);
    return node_render_layers_draw(gdl, 4, (s16)arg1, 1);
}
// NON-MATCHING: need to figure out what is going on
// void render_player_hud(struct14 *arg0, s32 arg1) {
//     s32 temp_v0;
//     s32 sp2A;
//     s16 sp28;
//
//     arg0->unk0 = 0xDC080008;
//     arg0->unk4 = &D_800BE628[arg1].unk40[D_800BE9C0];
//     sp28 = arg1;
//
//     temp_v0 = render_set_scissor(&arg0->unk8, &sp28, 0, 0, 0, 0);
//     temp_v0 = func_1517F4D8(temp_v0, arg1);
//     temp_v0 = func_1517F3A0(temp_v0, arg1);
//     temp_v0 = func_15180580(temp_v0, arg1);
//     // temp_v1 = 1 << arg1;
//     if (((D_800D18A0 & (1 << arg1)) != 0) || ( ((D_800D18A2 & (1 << arg1)) != 0))) {
//         temp_v0 = player_draw_out_overlay(temp_v0, arg1);
//     }
//     temp_v0 = node_render_layers_draw(temp_v0, 4, sp2A, 0);
//     node_render_layers_draw(temp_v0, 4, sp2A, 1);
// }

#ifdef NON_MATCHING
/* Per-player 3D setup (P13, hand C): viewport and projection of camera record D_800BE628 + player * 0x180
 * (double-buffered by the DL buffer index D_800BE9C0), the fixed matrix D_80089810, level 0x1D's extra pass
 * (func_1502BDC0), the two model layers of group 5, then the view matrix and the player's model matrix from
 * D_800DC6D0[idx] (0x40 per player). */
extern s32 D_800DC6D0[];
Gfx *func_1502BDC0(Gfx *arg0, s32 arg1, s16 arg2);

/* was func_15019CC8 */
Gfx *render_player_3d_setup(Gfx *arg0, s32 arg1) {
    Gfx *gdl;
    s16 player = arg1;

    arg0->words.w0 = 0xDC080008;
    arg0->words.w1 = D_800BE628 + arg1 * 0x180 + D_800BE9C0 * 16 + 0x40;
    gdl = (Gfx *)render_set_scissor((s32)(arg0 + 1), player, 0, 0, 0, 0);
    gdl[0].words.w0 = 0xDA380003;
    gdl[0].words.w1 = (u32)D_80089810;
    gdl[1].words.w0 = 0xDA380007;
    gdl[1].words.w1 = D_800BE628 + arg1 * 0x180 + D_800BE9C0 * 64 + 0x100;
    gdl += 2;
    if (D_800BE9F0 == 0x1D) {
        gdl = func_1502BDC0(gdl, 6, player);
    }
    gdl = node_render_layers_draw(gdl, 5, 0, 0);
    gdl = node_render_layers_draw(gdl, 5, 0, 1);
    gdl[0].words.w0 = 0xDA380007;
    gdl[0].words.w1 = D_800BE628 + arg1 * 0x180 + D_800BE9C0 * 64 + 0x100;
    gdl[1].words.w0 = 0xDA380005;
    gdl[1].words.w1 = D_800DC6D0[D_800BE9C0] + arg1 * 64;
    return gdl + 2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/render_player_3d_setup.s")
#endif
/* was func_15019E60 */
Gfx *render_final_overlay(Gfx *arg0) {
    if (D_80082FA0 != 0) {
        D_80082FA4 = D_80082FA0 + 1;
        gSPViewport(arg0++, (D_80082FA4 * 0x180) + D_800BE628 + 64);
    } else {
        gSPViewport(arg0++, D_800BE628 + 64);
    }
    return (Gfx *)text_queue_draw(func_151E8620(render_set_scissor(arg0, 0xFF, 0, 0, 0, 0)));
}

#ifdef NON_MATCHING
void func_150A067C(void);
extern u32 D_800BEA30;
extern u8 D_800BEA39;
extern u8 D_800BEA3A;
extern s32 D_800BEDCC;
extern s32 D_800BEDD0;
extern f32 D_800BEDD8;
extern f32 D_800BEDDC;
extern u8 D_800BEE2C;
extern f32 D_eu_800BEA08;

/* was func_15019F20 */
void game_update_frame_timing(void) {
    OSMesgQueue *var_v0;
    OSThread *temp_f6;
    f32 temp_f0;
    f32 var_f0;
    s32 temp_f10;
    s32 temp_f18;
    s32 temp_t7;
    s32 temp_t9;
    s32 var_v1;
    u16 temp_t3;
    u16 temp_t5;
    u32 temp_a0;
    u32 temp_lo;
    u8 temp_t4;
    u8 var_a3;

    var_v1 = D_800BE9E4;
    D_800BEA08 = var_v1;
    if (D_800BEE2C != 0) {
        if (D_800BEE2C == 1) {
            D_800BE9E4 = 0;
            *(u16 *)D_800BEA00 = 0;
            var_v1 = 0;
            D_800BE9A4 = 0.0f;
        } else {
            temp_a0 = D_800BEA30 + var_v1;
            (void)D_800BEE2C;
            D_800BE9A4 = (f32) var_v1 / (f32) D_800BEE2C;
            temp_t7 = (s32) D_800BE9A4;
            D_800BE9A4 *= 0.5f;
            D_800BE9E4 = temp_t7;
            if (temp_a0 >= (u8) D_800BEE2C) {
                temp_lo = temp_a0 / (u8) D_800BEE2C;
                D_800BE9E4 = (s32) temp_lo;
                var_v1 = (s32) temp_lo;
                D_800BEA30 = temp_a0 - (temp_lo * temp_a0);
            } else {
                D_800BEA30 = temp_a0;
                D_800BE9E4 = 0;
                var_v1 = 0;
            }
        }
    } else {
        D_800BE9A4 = (f32) var_v1 * 0.5f;
    }
    temp_t3 = *(u16 *)D_800BEA00 & 0x3FF;
    temp_t5 = temp_t3 + (var_v1 * 0x266);
    *(u16 *)D_800BEA00 = temp_t3;
    *(u16 *)D_800BEA00 = temp_t5;
    D_800BE9A0 = (u8) ((s32) (temp_t5 & 0xFFFF) >> 0xA);
    if (D_800BE9A4 != 0.0f) {
        D_800BEDC8 = (1.0f / D_800BE9A4) / 1.2f;
    } else {
        D_800BE9A4 = 0.0f;
        D_800BEDC8 = 0.0f;
    }
    temp_t9 = D_800BEDCC + var_v1;
    D_800BEDCC = temp_t9;
    D_800BEDD0 = temp_t9 % 30;
    (&D_eu_800BEA08)[D_800BEA39] = D_800BE9A4;
    temp_t4 = D_800BEA39 + 1;
    D_800BEA39 = temp_t4;
    if ((temp_t4 & 0xFF) == 0xA) {
        D_800BEA39 = 0;
    }
    if ((s32) D_800BEA3A < 0xA) {
        D_800BEA3A += 1;
        D_800BEDD8 = D_800BE9A4;
        D_800BEDDC = D_800BEDC8;
    } else {
        {
            f32 *fp = (f32 *)&D_800BEA10;
            { /* P317: volatile zero: IDO folds `0.0f + x` (the asm adds, -0.0 -> +0.0; P310) */
                volatile f32 p317z = 0.0f;
                var_f0 = p317z + D_eu_800BEA08 + (&D_eu_800BEA08)[1];
            }
            do {
                var_f0 = var_f0 + fp[0] + fp[1] + fp[2] + fp[3];
                fp += 4;
            } while (fp != (f32 *)&D_800BEA30);
        }
        D_800BEDD8 = var_f0 * 0.1f;
        if (D_800BEDD8 != 0.0f) {
    s32 pad;
            D_800BEDDC = 1.0f / D_800BEDD8;
        } else {
            D_800BEDDC = 0.0f;
        }
    }
    func_150A067C();
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/game_update_frame_timing.s")
#endif