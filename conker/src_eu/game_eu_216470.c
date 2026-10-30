#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
Gfx *sprite_gfx_begin_alt(Gfx *arg0);
Gfx *hud_image_draw(Gfx *, void *, s32, s32, s32, s32, f32, s32);
extern Gfx g_hud_sprite_setup_dl[]; /* was D_800903D8 */
u8 *render_fill_rect_clamped(u8 *, s32, s32, s32, s32);
extern s32 g_hud_sprite_desc; /* was D_80090410 */
extern s32 g_screen_sprite_1ba8; /* was D_80091BA8 */
Gfx *hud_image_tile_setup(Gfx *, u8 *, s32 *);
extern u8 g_tex_siz_load_block[]; /* was D_8009E28C */
extern u8 g_tex_siz_load_incr[]; /* was D_8009E280 */
extern u8 g_tex_siz_load_shift[]; /* was D_8009E284 */
extern u8 g_tex_siz_line_bytes[]; /* was D_8009E288 */


Gfx *screen_fade_rect_draw(Gfx *gdl);
/* P120: the definition (game_70200) is varargs; a fixed-arg prototype gives a different wasm signature. */
void text_printf_at(s32, s32, s32, void *, ...);
extern Gfx *(*g_hud_post_fns[])(Gfx *); /* was D_800903A4 */
extern u8 g_cont_connected_mask; /* was D_800BEB60 */

/* was func_151E8C60 */
Gfx *hud_overlay_draw_post(Gfx *gdl) {
    s32 msg;
    Gfx *(*fn)(Gfx *);

    g_dbg_crash_marker = 0x09000001;
    msg = 0;
    gdl = screen_fade_rect_draw(gdl);
    fn = g_hud_post_fns[g_game_mode];
    if (fn != NULL) {
        gdl = fn(gdl);
    }
    if (g_os_tv_type == 0) {
        if (g_mp_mode_active != 0 && g_human_player_count >= 2) {
            if ((g_cont_connected_mask & 0xF) == 0) {
                if (g_text_bank_loaded == 1) {
                    msg = 0x33;
                } else if (g_text_bank_loaded == 2) {
                    msg = 0x16;
                }
            }
        } else if ((g_cont_connected_mask & 1) == 0) {
            if (g_text_bank_loaded == 1) {
                msg = 0x32;
            } else if (g_text_bank_loaded == 2) {
                msg = 0x15;
            }
        }
    }
    if (msg != 0) {
        text_set_color(0xFF, 0xFF, 0xFF, 0xFF);
        text_printf_at(0x94, 0xC8, 0x81, ((void **)g_text_strings)[msg]);
    }
    g_dbg_crash_marker = 0;
    return gdl;
}

extern Gfx *(*g_hud_screen_fns[])(Gfx *); /* was D_80090370 */
extern s32 g_hud_cash_model; /* was D_80090408 */
extern s32 g_dl_capacity; /* was D_800BEFC4 */
extern s16 g_mp_hud_unk_10a8; /* was D_800E10A8 */
/* was func_151E8620 */
Gfx *hud_overlay_draw_screen(Gfx *arg0) {
    Gfx *(*temp_a1)(Gfx *);
    Gfx *temp_a2;
    s32 var_v0;
    u8 temp_v1;
    temp_v1 = g_game_mode;
    temp_a2 = arg0;
    g_dbg_crash_marker = 0x09000000;
    temp_a1 = g_hud_screen_fns[temp_v1];
    if (temp_a1 != NULL) {
        arg0 = temp_a1(arg0);
    }
    if (g_game_mode != 0) {
        g_hud_cash_model = 0;
        g_mp_hud_unk_10a8 = 0;
    }
    g_dbg_crash_marker = 0;
    if (g_dl_capacity < (arg0 - g_gfx_dl_buffers[g_dl_buf_index])) {
        var_v0 = 1;
    } else {
        var_v0 = 0;
    }
    if (var_v0 != 0) {
        return temp_a2;
    }
    return arg0;
}

extern f32 g_hud_scale_x; /* was D_800901BC */
extern f32 g_hud_scale_y; /* was D_800901C0 */

/* was func_151E8E94 */
u8 *hud_tex_rect_scaled(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    s16 var_t0;
    s16 var_t0_2;
    s16 var_t1;
    s16 var_t1_2;
    s32 temp_t4;
    s32 temp_t5;
    s32 temp_t6;
    s32 temp_t7;
    s32 var_a2;
    s32 var_t1_3;
    s32 var_t2;
    s32 var_v0;
    s32 var_v0_2;
    u8 *temp_a0;
    u8 *temp_a0_2;

    var_a2 = arg2;
    if (g_hud_scale_x != 1.0f) {
        arg1 = (s32) ((f32) arg1 * g_hud_scale_x);
        arg3 = (s32) ((f32) arg3 * g_hud_scale_x);
        var_a2 = (s32) ((f32) var_a2 * g_hud_scale_y);
        arg4 = (s32) ((f32) arg4 * g_hud_scale_y);
        arg8 = (s32) ((f32) arg8 / g_hud_scale_x);
        arg9 = (s32) ((f32) arg9 / g_hud_scale_y);
    }
    temp_a0_2 = arg0 + 8;
    if ((s16) arg3 > 0) {
        var_t0 = (s16) arg3;
    } else {
        var_t0 = 0;
    }
    if ((s16) arg4 > 0) {
        var_t1 = (s16) arg4;
    } else {
        var_t1 = 0;
    }
    (*(s32 *)((u8 *)arg0 + 0)) = (s32) ((var_t1 & 0xFFF) | 0xE4000000 | ((var_t0 & 0xFFF) << 0xC));
    if ((s16) arg1 > 0) {
        var_t0_2 = (s16) arg1;
    } else {
        var_t0_2 = 0;
    }
    if ((s16) var_a2 > 0) {
        var_t1_2 = (s16) var_a2;
    } else {
        var_t1_2 = 0;
    }
    (*(s32 *)((u8 *)arg0 + 4)) = (s32) ((var_t1_2 & 0xFFF) | ((arg5 & 7) << 0x18) | ((var_t0_2 & 0xFFF) << 0xC));
    (*(s32 *)((u8 *)temp_a0_2 + 0)) = 0xE1000000;
    temp_a0 = temp_a0_2 + 8;
    if ((s16) arg1 < 0) {
        if ((s16) arg8 < 0) {
            temp_t5 = (s32) ((s16) arg1 * (s16) arg8) >> 7;
            if (temp_t5 > 0) {
                var_t2 = temp_t5;
            } else {
                var_t2 = 0;
            }
        } else {
            var_v0 = 0;
            temp_t4 = (s32) ((s16) arg1 * (s16) arg8) >> 7;
            if (temp_t4 < 0) {
                var_v0 = temp_t4;
            }
            var_t2 = var_v0;
        }
    } else {
        var_t2 = 0;
    }
    if (var_a2 < 0) {
        if ((s16) arg9 < 0) {
            temp_t7 = (s32) ((s16) var_a2 * (s16) arg9) >> 7;
            if (temp_t7 > 0) {
                var_t1_3 = temp_t7;
            } else {
                var_t1_3 = 0;
            }
        } else {
            var_v0_2 = 0;
            temp_t6 = (s32) ((s16) var_a2 * (s16) arg9) >> 7;
            if (temp_t6 < 0) {
                var_v0_2 = temp_t6;
            }
            var_t1_3 = var_v0_2;
        }
    } else {
        var_t1_3 = 0;
    }
    (*(s32 *)((u8 *)temp_a0_2 + 4)) = (s32) (((arg7 - var_t1_3) & 0xFFFF) | ((arg6 - var_t2) << 0x10));
    (*(s32 *)((u8 *)temp_a0 + 0)) = 0xF1000000;
    (*(s32 *)((u8 *)temp_a0 + 4)) = (s32) ((arg8 << 0x10) | (arg9 & 0xFFFF));
    return temp_a0 + 8;
}
extern u16 g_mp_game_flags;           /* HUD state: 0x10 = a player is near the target point; was D_8009015C */
extern u16 g_mp_hud_flags;           /* HUD elements: 1 / 8 team scores, 0x4000 / 0x8000 carried item, 0x6340 timer; was D_80090160 */
extern s8 g_mp_team_count;            /* team count; was D_800E0FE0 */
extern u16 g_mp_hud_marked_players;           /* players marked on the HUD (bit per player); was D_800E0FFC */
extern u8 g_mp_team_colours[][4];       /* team colours (r, g, b); was D_800ABEA0 */
extern u8 g_mp_digit_sheet_col[4];         /* digit -> sheet column; was D_8009041C */
extern u8 g_mp_digit_sheet_row[];          /* digit -> sheet row; was D_80090420 */
extern s32 g_frame_count;           /* frame counter; was D_800BEDCC */
s32 rail_node_position(s32, f32 *, f32 *, f32 *);
s32 rail_node_find_by_tag(s32);
s32 texture_cache_lookup(s32, s32, s32, s32);
u8 *mp_team_marks_draw(u8 *, s32, s32, s32, s32);
u8 *mp_team_score_draw(u8 *, s32, s32);
#define HUD_W(g, a, b) ((g)->words.w0 = (a), (g)->words.w1 = (b), (g)++)
/* mp_hud_draw: the multiplayer HUD overlay; returns the new DL end. `alpha` is the overlay alpha (low byte), the
 * second argument is unused. Marks the players to show in g_mp_hud_marked_players (active or flagged players, players of kind
 * 0x25 near rail point 0x49: within 2500 units also sets g_mp_game_flags 0x10 and the "near" icon), remembers the last
 * flagged player's team (+0x128) as the carrier (with g_mp_hud_flags 0x8000 it becomes the left / right arrow flag
 * instead), and the bonus flag 4 for team 1 with +0x2E4. Every 32 frames the first 11 clear all of that (blink).
 * Then: the team score row (g_mp_hud_flags 8; texture 0xD16, per team its colour bar and the score in digits from the
 * g_mp_digit_sheet_col / g_mp_digit_sheet_row sheet), the team panel mp_team_marks_draw (1), the carried-item / near icons (texture 0xD18,
 * 0xD19 with 0x4000), the side arrows / bonus icon (texture 0xD12, 0xD13 with flag 4) and the timer mp_team_score_draw
 * (0x6340). */
/* was func_151E9150 */
u8 *mp_hud_markers_draw(u8 *buf, s32 unused, s32 alpha) {
    Gfx *gdl = (Gfx *) buf;
    struct127 *p;
    s32 y, pitch, x, team, score, q, div, dx, started, done, tex, id, size, w, off, row, i, sel;
    u8 near, flags;
    f32 px, py, pz, ddx, ddz;

    flags = 0;
    g_mp_game_flags &= ~0x10;
    gSPDisplayList(gdl++, g_hud_sprite_setup_dl);
    gDPSetCombine(gdl++, 0x12FE25, 0xFFFFF3F9);
    y = (g_last_player_index == 0) ? 0x320 : 0x198;
    pitch = 0x124;
    if (g_mp_team_count > 0) {
        pitch = 0x124 / g_mp_team_count;
    }
    g_mp_hud_marked_players = 0;
    near = 0;
    sel = -1;
    for (i = 0; i < g_player_count; i++) {
        p = &g_objects[i];
        if (p->unk13C != 0 || (*(u8 *) ((u8 *) p->unk31C + 0x128) & 0x20)) {
            g_mp_hud_marked_players |= 1 << i;
            sel = p->unk128;
        }
        if (sel != -1 && (g_mp_hud_flags & 0x8000)) {
            if (sel == 0) {
                flags |= 2;
            } else {
                flags |= 1;
            }
            sel = -1;
        }
        if (p->unk128 == 1 && p->unk2E4 != 0 && (g_mp_hud_flags & 0x4000)) {
            flags |= 4;
        }
        if ((*(u8 *) ((u8 *) p->unk31C + 0x75) & 0x7F) == 0x25) {
            rail_node_position(rail_node_find_by_tag(0x49), &px, &py, &pz);
            ddx = px - p->x_position;
            ddz = pz - p->z_position;
            if (ddx * ddx + ddz * ddz < 6250000.0f) {
                near = 1;
                g_mp_game_flags |= 0x10;
            }
            g_mp_hud_marked_players |= 1 << i;
        }
    }
    if ((g_frame_count & 0x1F) < 11) {
        g_mp_hud_marked_players = 0;
        near = 0;
        sel = -1;
        flags = 0;
    }
    tex = 0;
    if (g_mp_hud_flags & 9) {
        tex = texture_cache_lookup(0xD16, 0, 3, 0);
        if (tex != (s32) 0x80000000) {
            HUD_W(gdl, 0xFD180000, tex);        /* SetTImg RGBA32 */
            HUD_W(gdl, 0xF5180000, 0x07094250); /* SetTile (load) */
            gDPLoadSync(gdl++);
            HUD_W(gdl, 0xF3000000, 0x073FF000); /* LoadBlock */
            gDPPipeSync(gdl++);
            HUD_W(gdl, 0xF5181000, 0x00094250); /* SetTile (render) */
            HUD_W(gdl, 0xF2000000, 0x0007C07C); /* SetTileSize 32x32 */
            gDPSetOtherMode(gdl++, 0x002C3F, 0x504244);
        } else {
            tex = 0;
        }
    }
    if ((g_mp_hud_flags & 8) && tex != 0) {
        x = pitch >> 1;
        for (team = 0; team < g_mp_team_count; team++) {
            started = 0;
            done = 0;
            score = player_stat_get((s16) team, 6);
            gDPPipeSync(gdl++);
            gDPSetEnvColor(gdl++, g_mp_team_colours[team][0], g_mp_team_colours[team][1], g_mp_team_colours[team][2], alpha & 0xFF);
            dx = (x + 10) * 4;
            gdl = (Gfx *) hud_tex_rect_scaled((u8 *) gdl, (x + 3) * 4, y, dx, y + 0x1C, 0, 0x1C0, 0x200, 0x400, 0x400);
            div = 10000;
            do {
                q = score / div;
                if (q != 0 || started || div == 1) {
                    started = 1;
                    gdl = (Gfx *) hud_tex_rect_scaled((u8 *) gdl, dx, y, dx + 0x14, y + 0x1C, 0, g_mp_digit_sheet_col[q & 3] << 5,
                                                g_mp_digit_sheet_row[q >> 2] << 5, 0x400, 0x400);
                    dx += 0x18;
                }
                score -= q * div;
                if (div == 1) {
                    done = 1;
                }
                div /= 10;
            } while (!done);
            x += pitch;
        }
    }
    if (g_mp_hud_flags & 1) {
        gdl = (Gfx *) mp_team_marks_draw((u8 *) gdl, y, sel, 0, 1);
    }
    if (near || sel != -1) {
        id = (g_mp_hud_flags & 0x4000) ? 0xD19 : 0xD18;
        tex = texture_cache_lookup(id, 0, 3, 0);
        if (tex != (s32) 0x80000000) {
            HUD_W(gdl, 0xFD500000, tex);        /* SetTImg CI 8-bit */
            HUD_W(gdl, 0xF5500000, 0x07098260); /* SetTile (load) */
            gDPLoadSync(gdl++);
            HUD_W(gdl, 0xF3000000, 0x073FF000); /* LoadBlock */
            gDPPipeSync(gdl++);
            HUD_W(gdl, 0xF5400800, 0x00098260); /* SetTile (render) */
            HUD_W(gdl, 0xF2000000, 0x000FC0FC); /* SetTileSize 64x64 */
            HUD_W(gdl, 0xFD100000, tex + 0x800); /* SetTImg: the palette after the texels */
            gDPLoadSync(gdl++);
            HUD_W(gdl, 0xF0000000, 0x0603C000); /* LoadTLUT */
            gDPSetOtherMode(gdl++, 0x00AC3F, 0x504244);
            gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, alpha & 0xFF);
            if (near) {
                gdl = (Gfx *) hud_tex_rect_scaled((u8 *) gdl, 0x238, 0xC, 0x268, 0x48, 0, 0x640, 0x660, 0x400, 0x400);
            }
            if (sel != -1) {
                if (g_mp_hud_flags & 0x4000) {
                    gdl = (Gfx *) hud_tex_rect_scaled((u8 *) gdl, 0x220, 0xC, 0x250, 0x48, 0, 0x600, 0x540, 0x400, 0x400);
                } else {
                    if (g_mp_hud_flags & 1) {
                        row = 0x1A;
                        off = 0;
                    } else {
                        row = 0x26;
                        off = 0xB;
                    }
                    gdl = (Gfx *) hud_tex_rect_scaled((u8 *) gdl, 0x238, (off + 3) * 4, 0x268, (off + 0xE) * 4, 0, 0x640,
                                                row << 5, 0x400, 0x400);
                }
            }
        }
    }
    size = 0x20;
    if (flags != 0) {
        id = 0xD12;
        if (flags & 4) {
            id = 0xD13;
            size = 0x10;
        }
        tex = texture_cache_lookup(id, 0, 3, 0);
        if (tex != (s32) 0x80000000) {
            gDPPipeSync(gdl++);
            HUD_W(gdl, 0xFD180000, tex);        /* SetTImg RGBA32 */
            HUD_W(gdl, 0xF5180000, 0x07094250); /* SetTile (load) */
            gDPLoadSync(gdl++);
            w = size * 32 - 1;
            if (w >= 0x7FF) {
                w = 0x7FF;
            }
            HUD_W(gdl, 0xF3000000, 0x07000000 | ((w & 0xFFF) << 12)); /* LoadBlock */
            gDPPipeSync(gdl++);
            HUD_W(gdl, 0xF5180000 | ((((size * 2 + 7) >> 3) & 0x1FF) << 9), 0x00094250); /* SetTile (render) */
            HUD_W(gdl, 0xF2000000, ((((size - 1) * 4) & 0xFFF) << 12) | 0x7C);       /* SetTileSize */
            gDPSetOtherMode(gdl++, 0x000C3F, 0x504244);
            gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, 0xFF);
            if (flags & 1) {
                gdl = (Gfx *) hud_tex_rect_scaled((u8 *) gdl, 0xA0, y - 0x10, 0xE0, y + 0x30, 0, 0, 0x200, 0x400, 0x400);
            }
            if (flags & 2) {
                gdl = (Gfx *) hud_tex_rect_scaled((u8 *) gdl, 0x3B0, y - 0x10, 0x3F0, y + 0x30, 0, 0x200, 0x200, 0x400, 0x400);
            }
            if (flags & 4) {
                gdl = (Gfx *) hud_tex_rect_scaled((u8 *) gdl, 0x250, 0xC, 0x280, 0x48, 0, 0, 0x200, 0x400, 0x400);
            }
        }
    }
    if (g_mp_hud_flags & 0x6340) {
        gdl = (Gfx *) mp_team_score_draw((u8 *) gdl, y, 1);
    }
    return (u8 *) gdl;
}
#undef HUD_W

extern s8 g_mp_team_mark_count;            /* score marks per team; was D_80087608 */
extern s16 g_mp_team_scores[];         /* team score; was D_800E0ED0 */
u8 *hud_tex_rect_scaled(u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 player_stat_get(s16, s32);
#define TM_W(g, a, b) ((g)->words.w0 = (a), (g)->words.w1 = (b), (g)++)
/* mp_team_marks_draw: the team panel of the multiplayer HUD at row `y`; returns the new DL end (the end so far when
 * a texture is missing). g_mp_team_count teams share 0x124 pixels. With `loadTex` (s8) it loads texture 0xD16 (32 x 32
 * RGBA32); with `refresh` (u8) it finds the teams out of the game (bit per team: 0xF minus the teams g_mp_player_team[i] of
 * the g_player_count players for which player_stat_get(i, 3) is set) and re-reads the scores (player_stat_get(team, 6)) into
 * g_mp_team_scores. Each live team draws g_mp_team_mark_count marks in its colour (g_mp_team_colours), 8 pixels apart around its column,
 * the marks from its score on (one more for `sel`) greyed (0x40404040). With any team out, texture 0xD19 (64 x 64
 * colour-indexed sheet + TLUT) draws a 16 x 0x40 cross in that team's colour over each team out. Ends with a pipe
 * sync. */
/* was func_151E9E1C */
u8 *mp_team_marks_draw(u8 *buf, s32 y, s32 sel, s32 loadTex, s32 refresh) {
    Gfx *gdl = (Gfx *) buf;
    s32 tex;
    s32 pitch;
    s32 x;
    s32 i;
    s32 j;
    s32 score;
    s32 mx;
    s8 out = 0;

    if ((s8) loadTex != 0) {
        tex = texture_cache_lookup(0xD16, 0, 3, 0);
        if (tex == (s32) 0x80000000) {
            return (u8 *) gdl;
        }
        gDPPipeSync(gdl++);
        TM_W(gdl, 0xFC12FE25, 0xFFFFF3F9); /* SetCombine */
        TM_W(gdl, 0xFD180000, tex);        /* SetTImg RGBA32 */
        TM_W(gdl, 0xF5180000, 0x07094250); /* SetTile (load) */
        gDPLoadSync(gdl++);
        TM_W(gdl, 0xF3000000, 0x073FF000); /* LoadBlock */
        gDPPipeSync(gdl++);
        TM_W(gdl, 0xF5181000, 0x00094250); /* SetTile (render) */
        TM_W(gdl, 0xF2000000, 0x0007C07C); /* SetTileSize 32x32 */
        gDPSetOtherMode(gdl++, 0x002C3F, 0x504244);
    }
    pitch = 0x124;
    if (g_mp_team_count > 0) {
        pitch = 0x124 / g_mp_team_count;
    }
    if ((u8) refresh != 0) {
        out = 0xF;
        for (i = 0; i < g_player_count; i++) {
            if (player_stat_get((s16) i, 3) != 0) {
                out &= ~(1 << g_mp_player_team[i]);
            }
        }
    }
    x = pitch >> 1;
    for (i = 0; i < g_mp_team_count; i++, x += pitch) {
        if ((u8) refresh != 0) {
            score = player_stat_get((s16) i, 6);
            g_mp_team_scores[i] = score;
        } else {
            score = g_mp_team_scores[i];
        }
        if (out & (1 << i)) {
            continue;
        }
        if (i == sel) {
            score++;
        }
        gDPPipeSync(gdl++);
        gDPSetEnvColor(gdl++, g_mp_team_colours[i][0], g_mp_team_colours[i][1], g_mp_team_colours[i][2], 0xFF);
        mx = x - g_mp_team_mark_count * 4;
        for (j = 0; j < g_mp_team_mark_count; j++, mx += 8) {
            if (j == score) {
                gDPPipeSync(gdl++);
                TM_W(gdl, 0xFB000000, 0x40404040); /* SetEnvColor grey */
            }
            gdl = (Gfx *) hud_tex_rect_scaled((u8 *) gdl, mx * 4, y, (mx + 7) * 4, y + 0x1C, 0, 0x1C0, 0x200, 0x400, 0x400);
        }
    }
    if (out != 0) {
        tex = texture_cache_lookup(0xD19, 0, 3, 0);
        if (tex == (s32) 0x80000000) {
            return (u8 *) gdl;
        }
        gDPPipeSync(gdl++);
        TM_W(gdl, 0xFD500000, tex);        /* SetTImg RGBA16 (load as 16b) */
        TM_W(gdl, 0xF5500000, 0x07098260); /* SetTile (load) */
        gDPLoadSync(gdl++);
        TM_W(gdl, 0xF3000000, 0x073FF000); /* LoadBlock */
        gDPPipeSync(gdl++);
        TM_W(gdl, 0xF5400800, 0x00098260); /* SetTile (render, palette) */
        TM_W(gdl, 0xF2000000, 0x000FC0FC); /* SetTileSize 64x64 */
        TM_W(gdl, 0xFD100000, tex + 0x800); /* SetTImg TLUT */
        gDPLoadSync(gdl++);
        TM_W(gdl, 0xF0000000, 0x0603C000); /* LoadTLUT */
        gDPSetOtherMode(gdl++, 0x00AC3F, 0x504244);
        x = pitch >> 1;
        for (i = 0; i < g_mp_team_count; i++, x += pitch) {
            if (out & (1 << i)) {
                gDPPipeSync(gdl++);
                gDPSetEnvColor(gdl++, g_mp_team_colours[i][0], g_mp_team_colours[i][1], g_mp_team_colours[i][2], 0xFF);
                gdl = (Gfx *) hud_tex_rect_scaled((u8 *) gdl, (x - 8) * 4, y - 0x18, (x + 8) * 4, y + 0x28, 0, 0x600, 0x280,
                                            0x400, 0x400);
            }
        }
    }
    gDPPipeSync(gdl++);
    return (u8 *) gdl;
}

extern s16 g_mp_team_scores[];         /* team score; was D_800E0ED0 */
extern char g_str_mp_fmt_team1_score[], g_str_mp_fmt_team0_score[]; /* was D_800ABEB0; was D_800ABEB4 */
s32 texture_cache_lookup(s32, s32, s32, s32);
u8 *hud_tex_rect_scaled(u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
#define TW_W(g, a, b) ((g)->words.w0 = (a), (g)->words.w1 = (b), (g)++)
/* mp_team_score_draw: P237. The two-team score panel (Total War and the other team modes; mp_hud_markers_draw /
 * mp_scoreboard_draw call it with g_mp_hud_flags 0x6340) at screen row `y` - 16; returns the new DL end (`buf` unchanged
 * when the texture is not loaded). Texture: 0xD12 (32 x 32) normally, 16 x 16 0xD13 with g_mp_hud_flags 0x4000 or 0xD14
 * in barrel mode 8 (g_menu_state + 0x42); loaded as RGBA32 with an env colour of white. With `update` the scores are
 * recomputed and stored in g_mp_team_scores[0] / [1]: with 0x6040 the team totals player_stat_get(team, 6); with 0x100 the
 * sum of player_stat_get(player, 3) (negative = 0) per team (+0x128 of g_objects[player]); else the barrel rows'
 * s16 +0x46 (negative = 0) by g_mp_player_team team, and the icons use the lower half of the sheet (t + 0x200). Without
 * `update` the stored scores are drawn. Two icons (x 0x108 and 0x318, 0x40 high; 32 x 32: the right half of the sheet
 * then the left; 16 x 16: the upper then the lower), then the scores in grey (g_str_mp_fmt_team1_score team 1 at x 0x4F,
 * g_str_mp_fmt_team0_score team 0 at x 0xD3, text row y / 4 - 3). */
/* was func_151EA4C8 */
u8 *mp_team_score_draw(u8 *buf, s32 y, s32 update) {
    Gfx *gdl = (Gfx *) buf;
    s32 top, size, tex, ls, lt, score0, score1, i, n, v, lrs, row;

    top = y - 0x10;
    if (!(g_mp_hud_flags & 0x4000) && *(s8 *) (g_menu_state + 0x42) != 8) {
        tex = 0xD12;
        size = 0x20;
        ls = 0x200;
        lt = 0;
    } else {
        tex = 0xD13;
        size = 0x10;
        if (*(s8 *) (g_menu_state + 0x42) == 8) {
            tex = 0xD14;
        }
        ls = 0;
        lt = 0x200;
    }
    tex = texture_cache_lookup(tex, 0, 3, 0);
    if (tex == (s32) 0x80000000) {
        return buf;
    }
    gDPPipeSync(gdl++);
    TW_W(gdl, 0xFD180000, tex);                                     /* SetTImg RGBA32 */
    TW_W(gdl, 0xF5180000, 0x07094250);                              /* SetTile (load) */
    gDPLoadSync(gdl++);
    lrs = size * 32 - 1;
    if (lrs >= 0x7FF) {
        lrs = 0x7FF;
    }
    TW_W(gdl, 0xF3000000, 0x07000000 | ((lrs & 0xFFF) << 12));      /* LoadBlock */
    gDPPipeSync(gdl++);
    TW_W(gdl, 0xF5180000 | ((((size * 2 + 7) >> 3) & 0x1FF) << 9), 0x00094250); /* SetTile (render) */
    TW_W(gdl, 0xF2000000, ((((size - 1) * 4) & 0xFFF) << 12) | 0x7C);  /* SetTileSize */
    TW_W(gdl, 0xEF000C3F, 0x00504244);                              /* SetOtherMode */
    TW_W(gdl, 0xFB000000, 0xFFFFFFFF);                              /* SetEnvColor white */

    row = 0;
    score0 = 0;
    score1 = 0;
    if (update) {
        if (g_mp_hud_flags & 0x6040) {
            score0 = player_stat_get(0, 6);
            score1 = player_stat_get(1, 6);
        } else if (g_mp_hud_flags & 0x100) {
            for (i = 0; i < g_player_count; i++) {
                v = player_stat_get((s16) i, 3);
                if (v < 0) {
                    v = 0;
                }
                if (g_objects[i].unk128 != 0) {
                    score1 += v;
                } else {
                    score0 += v;
                }
            }
        } else {
            row = 0x200;
            n = g_player_count;
            for (i = 0; i < n; i++) {
                v = *(s16 *) (g_menu_state + 0x46 + i * 2);
                if (v < 0) {
                    v = 0;
                }
                if (g_mp_player_team[i] != 0) {
                    score1 += v;
                } else {
                    score0 += v;
                }
            }
        }
        g_mp_team_scores[0] = score0;
        g_mp_team_scores[1] = score1;
    } else {
        score0 = g_mp_team_scores[0];
        score1 = g_mp_team_scores[1];
    }
    gdl = (Gfx *) hud_tex_rect_scaled((u8 *) gdl, 0x108, top, 0x148, top + 0x40, 0, ls, row, 0x400, 0x400);
    gdl = (Gfx *) hud_tex_rect_scaled((u8 *) gdl, 0x318, top, 0x358, top + 0x40, 0, 0, row + lt, 0x400, 0x400);
    text_set_color(0xC0, 0xC0, 0xC0, 0xFF);
    text_printf_at(0x4F, (top >> 2) + 1, 0x80, g_str_mp_fmt_team1_score, score1);
    text_printf_at(0xD3, (top >> 2) + 1, 0x80, g_str_mp_fmt_team0_score, score0);
    return (u8 *) gdl;
}
#undef TW_W

extern s8 g_menu_player_queue[4];         /* player queue (controller numbers, -1 empty); was D_800901E4 */
extern s8 g_mp_placings[];          /* placing per team / player (1 = first); was D_800E0EF0 */
extern s16 g_mp_team_scores[];         /* team score; was D_800E0ED0 */
extern s16 g_mp_hits_taken[];         /* per player value (last column); was D_800E0F00 */
extern s8 g_mp_p0_start_state; /* was D_8009011C */
extern char g_str_mp_fmt_placing[], g_str_mp_fmt_team_score[], g_str_mp_fmt_hit_pct[], g_str_mp_fmt_score[], g_str_mp_out_mark[], g_str_mp_fmt_lives[], g_str_mp_fmt_hits[]; /* was D_800ABEB8; was D_800ABEBC; was D_800ABEC0; was D_800ABEC8; was D_800ABECC; was D_800ABED0; was D_800ABED4 */
s32 texture_cache_lookup(s32, s32, s32, s32);
u8 *mp_team_marks_draw(u8 *, s32, s32, s32, s32);
u8 *mp_team_score_draw(u8 *, s32, s32);
#define BAR_W(g, a, b) ((g)->words.w0 = (a), (g)->words.w1 = (b), (g)++)
#define BAR_MODE() (*(s8 *) (g_menu_state + 0x42))
#define BAR_ROW(i, off) (*(s16 *) (g_menu_state + (i) * 12 + (off)))
/* mp_scoreboard_draw: the multiplayer score table (barrel menu mode 3 bar of barrel_menu_draw, and the in-match HUD
 * with `hud` set); returns the new DL end. Menu modes 11 / 12: only the controller icons of the player queue
 * g_menu_player_queue (texture 0x843; nothing in the HUD). Otherwise one row per queued player that is not a spectator
 * (g_player_start_state != 10) and has a team (g_mp_player_team; team 0 too in mode 8): the header (textures 0x887 / 0x888:
 * columns, team column with g_mp_hud_flags 1, no kills column in mode 1) before the first row, then the controller icon
 * in the team colour g_mp_team_colours, the placing name (g_text_strings strings from g_mp_placings, the second table with
 * g_text_bank_loaded == 2), the team score g_mp_team_scores, the hit percentage (+0x66 * 100 / shots, shots from the player's
 * +0x1AA in the HUD, else +0x6C; at most 9999), the score +0x46, the lives +0x6A (or the g_str_mp_out_mark mark for
 * player state 9) unless mode 1, and g_mp_hits_taken. Rows start at `y` (40 higher with g_game_mode and g_mp_free_for_all) and
 * are 15 apart. Ends with the timer mp_team_score_draw (g_mp_hud_flags 0x6340) and, in the HUD, the team panel. */
/* was func_151EA90C */
u8 *mp_scoreboard_draw(Gfx *gdl, s32 y, s16 alpha, s32 hud) {
    s8 *q;
    s32 tex, yy, k, i, team, base, fmt, x, hy, v, pct, r;
    s8 wide, hdr, all;

    if (BAR_MODE() == 11 || BAR_MODE() == 12) {
        if (hud) {
            return (u8 *) gdl;
        }
        gDPPipeSync(gdl++);
        gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, alpha & 0xFF);
        gDPSetCombine(gdl++, 0x12D225, 0xFFA7FFFF);
        tex = texture_cache_lookup(0x843, 0, 3, 0);
        if (tex == (s32) 0x80000000) {
            return (u8 *) gdl;
        }
        BAR_W(gdl, 0xFD180000, tex);        /* SetTImg RGBA32 */
        BAR_W(gdl, 0xF5180000, 0x07094250); /* SetTile (load) */
        gDPLoadSync(gdl++);
        BAR_W(gdl, 0xF3000000, 0x073FF000); /* LoadBlock */
        gDPPipeSync(gdl++);
        BAR_W(gdl, 0xF5181000, 0x00094250); /* SetTile (render) */
        BAR_W(gdl, 0xF2000000, 0x0007C07C); /* SetTileSize 32x32 */
        gDPSetOtherMode(gdl++, 0x002C3F, 0x504244);
        yy = 0x48;
        for (q = g_menu_player_queue; q != g_menu_player_queue + 4; q++) {
            if (*q >= 0) {
                k = *q & 3;
                gdl = (Gfx *) hud_tex_rect_scaled((u8 *) gdl, 0x120, (yy - 2) * 4, 0x160, (yy + 0xE) * 4, 0, (k & 1) << 9,
                                            (k >> 1) << 9, 0x400, 0x400);
                yy += 0x12;
            }
        }
        return (u8 *) gdl;
    }
    base = (g_mp_hud_flags & 1) ? 0x1A : 0x34;
    if (g_game_mode != 0 && g_mp_free_for_all != 0) {
        y -= 0x28;
    }
    text_set_color(0xFF, 0xFF, 0xFF, alpha & 0xFF);
    if (g_text_bank_loaded == 2) {
        fmt = 9;
        wide = 1;
    } else {
        fmt = 0x5E;
        wide = 0;
    }
    all = (BAR_MODE() == 8) ? 0 : 1;
    gDPPipeSync(gdl++);
    gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, alpha & 0xFF);
    gDPSetCombine(gdl++, 0x12D225, 0xFFA7FFFF);
    hdr = 0;
    for (i = 0; i < 4; i++) {
        if (g_menu_player_queue[i] < 0 || g_player_start_state[i] == 10) {
            continue;
        }
        team = g_mp_player_team[i];
        if (team == 0 && !all) {
            continue;
        }
        if (!hdr) {
            tex = texture_cache_lookup(0x887, 0, 3, 0);
            if (tex == (s32) 0x80000000) {
                return (u8 *) gdl;
            }
            BAR_W(gdl, 0xFD180000, tex);
            BAR_W(gdl, 0xF5180000, 0x07094250);
            gDPLoadSync(gdl++);
            BAR_W(gdl, 0xF3000000, 0x073FF000);
            gDPPipeSync(gdl++);
            BAR_W(gdl, 0xF5181000, 0x00094250);
            BAR_W(gdl, 0xF2000000, 0x0007C07C);
            gDPSetOtherMode(gdl++, 0x000C3F, 0x504244);
            x = (base - 0x28) * 4;
            hy = (y - 0x11) * 4;
            if (g_mp_hud_flags & 1) {
                gdl = (Gfx *) hud_tex_rect_scaled((u8 *) gdl, x + 0x1D4, hy, x + 0x214, hy + 0x40, 0, 0x200, 0, 0x400, 0x400);
                x += 0x78;
            }
            x += 0x1D4;
            if (BAR_MODE() == 1) {
                x -= 0x78;
            }
            gdl = (Gfx *) hud_tex_rect_scaled((u8 *) gdl, x + 0x164, hy, x + 0x1A4, hy + 0x3C, 0, 0, 0x200, 0x400, 0x400);
            if (BAR_MODE() == 1) {
                x += 0x78;
            }
            gDPPipeSync(gdl++);
            tex = texture_cache_lookup(0x888, 0, 3, 0);
            if (tex == (s32) 0x80000000) {
                return (u8 *) gdl;
            }
            BAR_W(gdl, 0xFD180000, tex);
            BAR_W(gdl, 0xF5180000, 0x07094250);
            gDPLoadSync(gdl++);
            BAR_W(gdl, 0xF3000000, 0x073FF000);
            gDPPipeSync(gdl++);
            BAR_W(gdl, 0xF5181000, 0x00094250);
            BAR_W(gdl, 0xF2000000, 0x0007C07C);
            gdl = (Gfx *) hud_tex_rect_scaled((u8 *) gdl, x, hy, x + 0x40, hy + 0x40, 0, 0x200, 0, 0x400, 0x400);
            x += 0x74;
            gdl = (Gfx *) hud_tex_rect_scaled((u8 *) gdl, x, hy, x + 0x40, hy + 0x40, 0, 0, 0, 0x400, 0x400);
            if (BAR_MODE() != 1) {
                gdl = (Gfx *) hud_tex_rect_scaled((u8 *) gdl, x + 0x4C, hy, x + 0xCC, hy + 0x40, 0, 0, 0x200, 0x400, 0x400);
            }
            gDPPipeSync(gdl++);
            tex = texture_cache_lookup(0x843, 0, 3, 0);
            if (tex == (s32) 0x80000000) {
                return (u8 *) gdl;
            }
            BAR_W(gdl, 0xFD180000, tex);
            BAR_W(gdl, 0xF5180000, 0x07094250);
            gDPLoadSync(gdl++);
            BAR_W(gdl, 0xF3000000, 0x073FF000);
            gDPPipeSync(gdl++);
            hdr = 1;
            BAR_W(gdl, 0xF5181000, 0x00094250);
            BAR_W(gdl, 0xF2000000, 0x0007C07C);
            gDPSetOtherMode(gdl++, 0x002C3F, 0x504244);
        }
        text_set_color(g_mp_team_colours[team][0], g_mp_team_colours[team][1], g_mp_team_colours[team][2], alpha & 0xFF);
        k = g_menu_player_queue[i] & 3;
        gdl = (Gfx *) hud_tex_rect_scaled((u8 *) gdl, (base + 8) * 4, (y - 2) * 4, (base + 0x18) * 4, (y + 0xE) * 4, 0,
                                    (k & 1) << 9, (k >> 1) << 9, 0x400, 0x400);
        pct = 0;
        if (hud) {
            v = g_objects[i].unk31C->unk1AA;
        } else {
            v = BAR_ROW(i, 0x6C);
        }
        if (v > 0) {
            pct = (BAR_ROW(i, 0x66) * 100) / v;
        }
        if (pct >= 10000) {
            pct = 9999;
        }
        if (g_mp_free_for_all != 0) {
            team = i;
        }
        r = (s8) (g_mp_placings[team] - 1);
        if (r < 0) {
            r = 0;
        }
        text_printf_at(base + 0x3C, y, 0x81, g_str_mp_fmt_placing, ((s32 *) g_text_strings)[r + fmt]);
        x = base;
        if (g_mp_hud_flags & 1) {
            text_printf_at(base + 0x54, y, 0x81, g_str_mp_fmt_team_score, g_mp_team_scores[team]);
            x = base + 0x1E;
        }
        x += 0x58;
        text_printf_at(x, y, 0x81, g_str_mp_fmt_hit_pct, pct);
        x += 0x1A;
        text_printf_at(x, y, 0x81, g_str_mp_fmt_score, *(s16 *) (g_menu_state + i * 2 + 0x46));
        x += 0x1E;
        if (BAR_MODE() != 1) {
            if (g_player_start_state[i] == 9 || (i == 0 && g_mp_p0_start_state == 9)) {
                text_printf_at(x, y, 0x81, g_str_mp_out_mark);
            } else {
                text_printf_at(x, y, 0x81, g_str_mp_fmt_lives, BAR_ROW(i, 0x6A));
            }
            x += 0x1E;
        }
        text_printf_at(x, y, 0x81, g_str_mp_fmt_hits, g_mp_hits_taken[i]);
        y += 0xF;
    }
    if (g_mp_hud_flags & 0x6340) {
        gSPDisplayList(gdl++, g_hud_sprite_setup_dl);
        gDPSetCombine(gdl++, 0x12FE25, 0xFFFFF3F9);
        gdl = (Gfx *) mp_team_score_draw((u8 *) gdl, 0x320, wide);
    }
    if (hud && (g_mp_hud_flags & 1)) {
        gdl = (Gfx *) mp_team_marks_draw((u8 *) gdl, 0x320, -1, 1, wide);
    }
    return (u8 *) gdl;
}
#undef BAR_W
#undef BAR_MODE
#undef BAR_ROW

s32 texture_cache_lookup(s32, s32, s32, s32);
u8 *hud_tex_rect_scaled(u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 g_hud_digit_tex_ids; /* was D_80090424 */
extern s32 g_hud_digit_divisors; /* was D_8009044C */

/* was func_151EB5AC */
u8 *hud_counter_digits_draw(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct {
        s32 u7C;
        u8 pad80[0x14];
        s32 u94;
    } sp;
    s32 *var_s1;
    s32 temp_t4;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    u8 *temp_s0;
    u8 *temp_s0_2;
    u8 *temp_s0_3;
    u8 *temp_s0_4;
    u8 *temp_s0_5;
    u8 *temp_s0_6;
    u8 *var_s0;

    var_s0 = arg0;
    var_s3 = arg3;
    (*(s32 *)((u8 *)(&sp.u7C) + 0)) = (s32) (*(s32 *)((u8 *)(&g_hud_digit_divisors) + 0));
    (*(s32 *)((u8 *)(&sp.u7C) + 4)) = (s32) (*(s32 *)((u8 *)(&g_hud_digit_divisors) + 4));
    (*(s32 *)((u8 *)(&sp.u7C) + 8)) = (s32) (*(s32 *)((u8 *)(&g_hud_digit_divisors) + 8));
    (*(s32 *)((u8 *)(&sp.u7C) + 0xC)) = (s32) (*(s32 *)((u8 *)(&g_hud_digit_divisors) + 0xC));
    (*(s32 *)((u8 *)(&sp.u7C) + 0x10)) = (s32) (*(s32 *)((u8 *)(&g_hud_digit_divisors) + 0x10));
    temp_t4 = arg2 * 4;
    (*(s32 *)((u8 *)(&sp.u7C) + 0x18)) = (s32) (*(s32 *)((u8 *)(&g_hud_digit_divisors) + 0x18));
    var_s2 = arg1 * 4;
    (*(s32 *)((u8 *)(&sp.u7C) + 0x14)) = (s32) (*(s32 *)((u8 *)(&g_hud_digit_divisors) + 0x14));
    if (var_s3 >= 0x989680) {
        var_s3 = 0x98967F;
    }
    var_s4 = 0;
    if (var_s3 < 0) {
        var_s3 = 0;
    }
    var_s1 = &sp.u94;
    do {
        temp_v0 = *var_s1;
        temp_v1 = var_s3 / temp_v0;
        var_s3 = var_s3 % temp_v0;
        if ((temp_v1 > 0) || (var_s4 != 0) || (var_s1 == &sp.u7C)) {
            var_s4 = 1;
            temp_v0_2 = texture_cache_lookup(*(s32 *)((u8 *)&g_hud_digit_tex_ids + (temp_v1 * 4)), 0, 3, 0);
            if (temp_v0_2 != 0x80000000) {
                (*(s32 *)((u8 *)var_s0 + 0)) = 0xFD180000;
                (*(s32 *)((u8 *)var_s0 + 4)) = temp_v0_2;
                temp_s0 = var_s0 + 8;
                (*(s32 *)((u8 *)temp_s0 + 0)) = 0xF5180000;
                (*(s32 *)((u8 *)temp_s0 + 4)) = 0x07094250;
                temp_s0_2 = temp_s0 + 8;
                (*(s32 *)((u8 *)temp_s0_2 + 0)) = 0xE6000000;
                (*(s32 *)((u8 *)temp_s0_2 + 4)) = 0;
                temp_s0_3 = temp_s0_2 + 8;
                (*(s32 *)((u8 *)temp_s0_3 + 4)) = 0x073FF000;
                (*(s32 *)((u8 *)temp_s0_3 + 0)) = 0xF3000000;
                temp_s0_4 = temp_s0_3 + 8;
                (*(s32 *)((u8 *)temp_s0_4 + 0)) = 0xE7000000;
                (*(s32 *)((u8 *)temp_s0_4 + 4)) = 0;
                temp_s0_5 = temp_s0_4 + 8;
                (*(s32 *)((u8 *)temp_s0_5 + 0)) = 0xF5181000;
                (*(s32 *)((u8 *)temp_s0_5 + 4)) = 0x94250;
                temp_s0_6 = temp_s0_5 + 8;
                (*(s32 *)((u8 *)temp_s0_6 + 0)) = 0xF2000000;
                (*(s32 *)((u8 *)temp_s0_6 + 4)) = 0x7C07C;
                var_s0 = hud_tex_rect_scaled(temp_s0_6 + 8, var_s2, temp_t4, var_s2 + 0x80, temp_t4 + 0x80, 0, 0, 0, 0x400, 0x400);
            }
            var_s2 += 0x60;
        }
        var_s1 = (s32 *)((u8 *)var_s1 - (4));
    } while ((u32) var_s1 >= (u32) &sp.u7C);
    return var_s0;
}
#ifdef PORT
s32 event_dispatch(s32, s32, ...);
u8 *event_get_vars(s32);
Gfx *hud_image_draw(Gfx *gdl, void *descArg, s32 x, s32 y, s32 cols, s32 rows, f32 scale, s32 idOffset);

#define CASH_DOLLAR_TEX 0x7F6   /* the pause screen's "$" image (hud_ingame_draw) */
#define CASH_DIGIT_W 0x40       /* quarter pixels: 16 px, half of the pause screen's 32 px digits */
#define CASH_DIGIT_STEP 0x30    /* 12 px per digit (pause screen: 24 px) */
#define CASH_MARGIN 16          /* px: gap between the counter and the right edge of the screen */
#define CASH_TOP_Y 12           /* px: top of the digits */

/* hud_cash_total: the cash amount as the pause screen shows it (hud_ingame_draw): player stat 6, where 0x7D00 means
 * 1000000; while event 0x5082 runs without 0x5083 it is scaled by event 0x83's count (+0x64) / 3. */
static s32 hud_cash_total(void) {
    s32 cash;
    s32 count;
    u8 *vars;

    cash = player_stat_get(0, 6);
    if (cash == 0x7D00) {
        cash = 1000000;
    }
    if (event_dispatch(0, 0x5082, 0x1A) != 0 && event_dispatch(0, 0x5083, 0x1A) == 0) {
        vars = event_get_vars(0x83);
        count = vars != NULL ? *(s32 *) (vars + 0x64) : 0;
        if (count == 0) {
            cash = 0;
        } else if (count < 3) {
            cash = cash * count / 3;
        }
    }
    return cash;
}

/* hud_cash_digits_draw_half: hud_counter_digits_draw at half size: the same digit textures (g_hud_digit_tex_ids,
 * 32x32) and the same load commands, drawn as 16x16 rectangles (texture step 0x800 = 2 texels per pixel) 12 px
 * apart. x, y: top left in pixels. A digit whose texture is not loaded yet is skipped (as in the original). */
static u8 *hud_cash_digits_draw_half(u8 *gdl, s32 x, s32 y, s32 value) {
    s32 *divisors = &g_hud_digit_divisors;   /* 1, 10, ... 1000000 */
    s32 started = 0;
    s32 i, digit, tex;
    s32 sx = x * 4;
    s32 sy = y * 4;
    s32 *g;

    if (value > 9999999) {
        value = 9999999;
    }
    if (value < 0) {
        value = 0;
    }
    for (i = 6; i >= 0; i--) {
        digit = value / divisors[i];
        value = value % divisors[i];
        if (digit == 0 && !started && i != 0) {
            continue;
        }
        started = 1;
        tex = texture_cache_lookup((&g_hud_digit_tex_ids)[digit], 0, 3, 0);
        if (tex != (s32) 0x80000000) {
            g = (s32 *) gdl;
            g[0] = 0xFD180000; g[1] = tex;          /* SetTImg */
            g[2] = 0xF5180000; g[3] = 0x07094250;   /* SetTile (load) */
            g[4] = 0xE6000000; g[5] = 0;            /* LoadSync */
            g[6] = 0xF3000000; g[7] = 0x073FF000;   /* LoadBlock */
            g[8] = 0xE7000000; g[9] = 0;            /* PipeSync */
            g[10] = 0xF5181000; g[11] = 0x94250;    /* SetTile (render) */
            g[12] = 0xF2000000; g[13] = 0x7C07C;    /* SetTileSize 32x32 */
            gdl = hud_tex_rect_scaled((u8 *) (g + 14), sx, sy, sx + CASH_DIGIT_W, sy + CASH_DIGIT_W, 0, 0, 0,
                                      0x800, 0x800);
        }
        sx += CASH_DIGIT_STEP;
    }
    return gdl;
}

/* hud_cash_counter_draw: P330 option "Always show cash" (off by default; replaces P325's green "$ N" text). The
 * original shows the cash total only on the pause screen (hud_ingame_draw: the "$" image 0x7F6 and the big digit
 * textures) and in a short pop-up when a script hands Conker cash. With the option on, the same images are drawn
 * every frame at half size in the top right corner. Not in multiplayer, during cutscenes, on the pause screen
 * (which shows its own), on HUD-less frames (g_pause_open) or on the title level 0x1D: the cases where hud_draw
 * hides the health HUD. The textures are requested every frame (texture_cache_lookup with an out pointer, as the
 * pause screen does), so they appear once loaded. */
static u8 *hud_cash_counter_draw(u8 *gdl) {
    s32 cash, digits, limit, x, i, unused;
    s32 saved_desc;
    s32 *g;

    if (!port_option(PORT_OPT_CASH_ALWAYS) || g_mp_mode_active != 0 || g_cutscene_slot_state == 1 ||
        g_game_paused != 0 || g_pause_open != 0 || g_level_id == 0x1D) {
        return gdl;
    }
    for (i = 0; i < 10; i++) {
        texture_cache_lookup((&g_hud_digit_tex_ids)[i], (s32) &unused, 3, 0);
    }
    texture_cache_lookup(CASH_DOLLAR_TEX, (s32) &unused, 3, 0);
    cash = hud_cash_total();
    for (digits = 1, limit = 10; limit <= cash && digits < 7; limit *= 10) {
        digits++;
    }
    /* HUD coordinates are multiplied by the hi-res factor g_hud_scale_x on the way to the screen */
    x = (s32) ((f32) g_framebuffer_width / g_hud_scale_x) - CASH_MARGIN - digits * (CASH_DIGIT_STEP / 4) - 4;
    g = (s32 *) gdl;
    g[0] = 0xDE000000; g[1] = (s32) g_hud_sprite_setup_dl;   /* the pause screen's 2D setup */
    g[2] = 0xFB000000; g[3] = -1;                               /* env colour: opaque white */
    saved_desc = g_hud_sprite_desc;
    g_hud_sprite_desc = CASH_DOLLAR_TEX;
    gdl = (u8 *) hud_image_draw((Gfx *) (g + 4), &g_hud_sprite_desc, x - 5, CASH_TOP_Y + 8, 1, 1, 0.5f, 0);
    g_hud_sprite_desc = saved_desc;
    g = (s32 *) gdl;
    g[0] = 0xDE000000; g[1] = (s32) g_hud_sprite_setup_dl;
    g[2] = 0xEF002C3F; g[3] = 0x504244;                         /* other modes, as before the pause digits */
    g[4] = 0xE7000000; g[5] = 0;
    g[6] = 0xFB000000; g[7] = -1;
    return hud_cash_digits_draw_half((u8 *) (g + 8), x, CASH_TOP_Y, cash);
}
#undef CASH_DOLLAR_TEX
#undef CASH_DIGIT_W
#undef CASH_DIGIT_STEP
#undef CASH_MARGIN
#undef CASH_TOP_Y
#endif

/* Table g_hud_screen_fns slot 0 (the in-game HUD pass): pause/fade overlay, and with g_game_paused set the
 * money/lives counter screen (texture ids 0x7D3.. loaded through texture_cache_lookup, counters drawn by
 * hud_counter_digits_draw). */
u8 * hud_health_draw(Gfx *, s32);
void hud_anim_model_free(u8 *arg0);
void game_gu_ortho(void *, float, float, float, float, float, float, float);
s8 mp_is_free_for_all(void);
void texture_unref_age3(s32);
u8 *event_get_vars(s32);
u8 *hud_counter_digits_draw(u8 *, s32, s32, s32);
s32 event_dispatch(s32, s32, ...);
u8 * mp_hud_markers_draw(u8 *, s32, s32);
u8 * mp_scoreboard_draw(Gfx *, s32, s16, s32);
s32 hud_anim_model_load(s32, s32, s32, f32);
u8 * hud_anim_model_draw(u8 *, s32, f32, f32, f32);
extern s32 g_sky_tex_sets; /* was D_8008955C */
extern s8 g_pause_unpause_timer; /* was D_8009029C */
extern s32 g_hud_pause_model_a2; /* was D_8009040C */
extern s8 g_pause_hud_delay; /* was D_80090468 */
extern s16 g_cutscene_cash_offset; /* was D_800C40BE */
extern s16 g_hud_model_env_alpha; /* was D_800E1060 */
extern s32 g_hud_model_proj_mtx; /* was D_800E1068 */

/* was func_151EB81C */
u8 *hud_ingame_draw(u8 *arg0) {
    struct {
        s32 u70;
        u8 pad74[0x8];
        s32 u7C;
        u8 pad80[0x4];
        s32 u84;
        s32 u88;
        s32 u8C;
        s32 u90;
    } sp;
    u8 *var_s0_2;
    u8 *gdl;   /* the display-list pointer; was var_s0 */
    u8 *temp_v0_2;
    u8 *temp_s0_6;
    u8 *temp_s0_5;
    u8 *temp_s0;
    u8 temp_v1;
    s32 var_v1_4;
    s32 var_v1_3;
    s32 var_v1;
    s32 var_v0_3;
    s32 var_v0_2;
    s32 var_v0;
    s32 var_t0;
    s32 var_a3;
    s32 var_a0;
    s32 temp_v1_2;
    s32 temp_v0_3;
    s32 temp_v0;
    s32 temp_t9;
    f32 temp_f2;
    f32 temp_f0;
    Gfx *temp_s0_4;
    Gfx *temp_s0_3;
    Gfx *temp_s0_2;
    Gfx *sp34;
    s32 sp3C;

    gdl = arg0;
    temp_t9 = (g_save_progress_bits->unk19 & 4) != 0;
    sp3C = temp_t9;
    if (temp_t9 == 0) {
        sp3C = g_save_cur_slot < 0;
    }
    if ((g_mp_mode_active != 0) && (g_game_paused == 0) && (g_pause_open == 0)) {
        if ((mp_is_free_for_all() == 0) || ((*(s8 *)((u8 *)g_menu_state + 0x42)) == 1)) {
            gdl = mp_hud_markers_draw(gdl, 0, 0xFF);
        }
    } else {
        g_mp_hud_unk_10a8 = 0;
    }
    if ((g_game_paused == 0) || (g_pause_unpause_timer != 0)) {
        if (g_hud_cash_model != 0) {
            hud_anim_model_free((u8 *) g_hud_cash_model);
            hud_anim_model_free((u8 *) g_hud_pause_model_a2);
            g_hud_cash_model = 0;
        }
        g_hud_fade_alpha = 0;
        g_pause_hud_delay = 0;
    } else {
        if ((g_level_header->unk8 == 4) && (g_pause_hud_delay == 0)) {
            var_v1 = 0;
            if (g_level_id == 0x13) {
                var_a0 = (*(s32 *)((u8 *)(*(s32 *)((u8 *)&g_sky_tex_sets + (g_level_header->unk9 * 4))) + 8));
                /* texture ids 0x1649-0x164B and 0x1655-0x1657 stay loaded */
                for (var_v0 = 0; var_v0 != 0x48; var_v0++, var_a0++) {
                    if (var_a0 != 0x1649 && var_a0 != 0x164A && var_a0 != 0x164B && var_a0 != 0x1655 &&
                        var_a0 != 0x1656 && var_a0 != 0x1657) {
                        texture_unref_age3(var_a0);
                    }
                }
                var_v1 = 0x4E;
            }
            var_v0_2 = var_v1;
            if (var_v1 < 0x168) {
                do {
                    sp.u84 = var_v0_2;
                    texture_unref_age3((*(s32 *)((u8 *)(*(s32 *)((u8 *)&g_sky_tex_sets + (g_level_header->unk9 * 4))) + 8)) + var_v0_2);
                    var_v0_2 = sp.u84 + 1;
                } while (var_v0_2 != 0x168);
            }
        }
        if (g_pause_hud_delay < 5) {
            g_pause_hud_delay += 1;
        } else {
            temp_s0 = gdl + 8;
            g_hud_fade_alpha += 0x20;
            if (g_hud_fade_alpha >= 0x100) {
                g_hud_fade_alpha = 0xFF;
            }
            (*(s32 *)((u8 *)gdl + 0)) = 0xDE000000;
            (*(Gfx **)((u8 *)gdl + 4)) = g_hud_sprite_setup_dl;
            (*(s32 *)((u8 *)temp_s0 + 0)) = 0xFB000000;
            temp_s0_2 = temp_s0 + 8;
            (*(s32 *)((u8 *)temp_s0 + 4)) = (s32) ((g_hud_fade_alpha & 0xFF) | ~0xFF);
            g_hud_sprite_desc = 0x891;
            sp34 = g_hud_sprite_setup_dl;
            texture_cache_lookup(0x7D3, (s32) &sp.u70, 3, 0);
            texture_cache_lookup(0x7D4, (s32) &sp.u70, 3, 0);
            texture_cache_lookup(0x7FC, (s32) &sp.u70, 3, 0);
            texture_cache_lookup(0x7FD, (s32) &sp.u70, 3, 0);
            texture_cache_lookup(0x7F1, (s32) &sp.u70, 3, 0);
            texture_cache_lookup(0x7F2, (s32) &sp.u70, 3, 0);
            texture_cache_lookup(0x82F, (s32) &sp.u70, 3, 0);
            texture_cache_lookup(0x830, (s32) &sp.u70, 3, 0);
            temp_v1 = g_mp_mode_active;
            if (temp_v1 != 0) {
                texture_cache_lookup(0x80E, (s32) &sp.u70, 3, 0);
                texture_cache_lookup(0x80F, (s32) &sp.u70, 3, 0);
            }
            if (temp_v1 == 0) {
                temp_v0 = player_stat_get(0, 6);
                var_v1_3 = temp_v0;
                if (temp_v0 == 0x7D00) {
                    var_v1_3 = 0xF4240;
                }
                sp.u90 = var_v1_3;
                if ((event_dispatch(0, 0x5082, 0x1A) != 0) && (event_dispatch(0, 0x5083, 0x1A) == 0)) {
                    temp_v0_2 = event_get_vars(0x83);
                    if (temp_v0_2 != NULL) {
                        temp_v1_2 = (*(s32 *)((u8 *)temp_v0_2 + 0x64));
                        if (temp_v1_2 == 0) {
                            sp.u90 = 0;
                        } else if (temp_v1_2 < 3) {
                            sp.u90 = (s32) (sp.u90 * temp_v1_2) / 3;
                        }
                    } else {
                        sp.u90 = 0;
                    }
                }
                var_v1_4 = sp.u90;
                if ((g_cutscene_slot_state == 1) && (g_cutscene_cash_offset != -1)) {
                    if (g_cutscene_cash_offset == 0) {
                        var_v1_4 = 0;
                    } else {
                        var_v1_4 -= g_cutscene_cash_offset;
                        if (g_cutscene_cash_offset == 0x7D00) {
                            var_v1_4 = 0xF4240;
                        }
                    }
                }
                if (var_v1_4 > 0) {
                    sp.u88 = 1;
                } else {
                    sp.u88 = 0;
                }
                sp.u90 = var_v1_4;
                temp_s0_3 = hud_image_draw(temp_s0_2, &g_hud_sprite_desc, 0x94, 0x3C, 3, 1, 1.0f, 0);
                if (g_hud_cash_model == 0) {
                    g_hud_cash_model = hud_anim_model_load(0xA4, 0x17, 0, 1.0f);
                    g_hud_pause_model_a2 = hud_anim_model_load(0xA2, 8, 0, 1.0f);
                }
                temp_s0_3->words.w0 = 0xD9FFFFFF;
                temp_s0_3->words.w1 = 0x220404;
                temp_s0_4 = temp_s0_3 + 1;
                temp_s0_4->words.w1 = -1U;
                temp_s0_4->words.w0 = 0xFB000000;
                temp_f0 = (*(f32 *)((u8 *)g_player_cams + 4)) * 0.5f;
                temp_f2 = (*(f32 *)((u8 *)g_player_cams + 8)) * 0.5f;
                var_s0_2 = hud_health_draw(temp_s0_4 + 1, 1);
                game_gu_ortho(&g_hud_model_proj_mtx, -temp_f0, temp_f0, -temp_f2, temp_f2, 1.0f, 20000.0f, 1.0f);
                g_hud_model_env_alpha = g_hud_fade_alpha;
                if (g_hud_cash_model != 0) {
                    var_v0_3 = 0xA;
                    if (sp.u88 != 0) {
                        var_t0 = -0x10;
                        if (sp.u90 >= 0xB) {
                            do {
                                var_t0 -= 0x10;
                                var_v0_3 *= 0xA;
                            } while (var_v0_3 < sp.u90);
                        }
                        sp.u8C = var_t0;
                        var_s0_2 = hud_anim_model_draw(var_s0_2, g_hud_cash_model, (f32) var_t0 + -10.0f, -83.0f, 0.26999998f);
                    }
                }
                if ((g_hud_pause_model_a2 != 0) && (sp3C != 0)) {
                    var_s0_2 = hud_anim_model_draw(var_s0_2, g_hud_pause_model_a2, 70.0f, 80.0f, 0.3f);
                }
                (*(s32 *)((u8 *)var_s0_2 + 0)) = 0xDE000000;
                temp_s0_5 = var_s0_2 + 8;
                (*(Gfx **)((u8 *)var_s0_2 + 4)) = sp34;
                (*(s32 *)((u8 *)temp_s0_5 + 0)) = 0xEF002C3F;
                (*(s32 *)((u8 *)temp_s0_5 + 4)) = 0x504244;
                gdl = temp_s0_5 + 8;
                if (sp3C != 0) {
                    temp_v0_3 = player_stat_get(0, 3);
                    var_a3 = temp_v0_3;
                    if (temp_v0_3 != 0) {
                        var_a3 = temp_v0_3 - 1;
                    }
                    if (var_a3 >= 0x64) {
                        var_a3 = 0x63;
                    }
                    (*(s32 *)((u8 *)gdl + 0)) = 0xFB000000;
                    (*(s32 *)((u8 *)gdl + 4)) = (s32) ((g_hud_fade_alpha & 0xFF) | ~0xFF);
                    gdl = hud_counter_digits_draw(gdl + 8, 0xEC, 0x1E, var_a3);
                }
                if (sp.u88 != 0) {
                    (*(s32 *)((u8 *)gdl + 0)) = 0xE7000000;
                    temp_s0_6 = gdl + 8;
                    (*(s32 *)((u8 *)gdl + 4)) = 0;
                    (*(s32 *)((u8 *)temp_s0_6 + 0)) = 0xFB000000;
                    (*(s32 *)((u8 *)temp_s0_6 + 4)) = (s32) ((g_hud_fade_alpha & 0xFF) | ~0xFF);
                    g_hud_sprite_desc = 0x7F6;
                    gdl = hud_counter_digits_draw(hud_image_draw(temp_s0_6 + 8, &g_hud_sprite_desc, sp.u8C + 0xA5, 0xAA, 1, 1, 1.0f, 0), sp.u8C + 0xAD, 0x9B, sp.u90);
                }
            } else {
                gdl = mp_scoreboard_draw(hud_image_draw(temp_s0_2, &g_hud_sprite_desc, 0x94, 0x12, 3, 1, 1.0f, 0), 0x85, g_hud_fade_alpha, 1);
            }
        }
    }
#ifdef PORT
    port_ws_hud_anchor(gdl, 2);   /* P350 widescreen: the cash counter keeps to the right edge */
    gdl = hud_cash_counter_draw(gdl);
    port_ws_hud_anchor(gdl, 0);
#endif
    return gdl;
}
/* was func_151EC0E0 */
s32 mp_scoreboard_draw_fading(s32 arg0) {
    if (g_hud_fade_alpha != 0) {
        arg0 = mp_scoreboard_draw(arg0, 0x6A, g_hud_fade_alpha, 0);
    }
    return arg0;
}

extern s16 g_credits_line; /* was D_800E0EB0 */

/* Table g_hud_screen_fns slot 21: centred text screen. Lines g_text_strings[g_credits_line...] up to a "*" line;
 * the first line is red, an extra 12 px gap follows it. Fades in over g_game_mode_timer 0..63, out at 287..350. */
/* was func_151EC11C */
Gfx *screen_centred_text_draw(Gfx *gdl) {
    s32 pad[2];
    s16 a;
    s16 i;
    s32 n;
    s32 step;
    s32 y;
    s32 y0;
    u8 *s;

    if (g_credits_line < 0) {
        return gdl;
    }
    if (g_game_mode_timer < 300) {
        a = g_game_mode_timer << 2;
        if (a >= 0x100) {
            a = 0xFF;
        }
    } else {
        a = (350 - g_game_mode_timer) << 2;
        if (a < 0) {
            a = 0;
        }
        if (a >= 0x100) {
            a = 0xFF;
        }
    }
    n = 0;
    for (i = g_credits_line; ((u8 **)g_text_strings)[i][0] != '*'; i++) {
        n++;
    }
    if (n < 14) {
        step = 0x11;
    } else {
        step = 0xB;
    }
    text_set_color(0xFF, 0, 0, a);
    i = g_credits_line;
    y0 = y = (0xD0 - n * step) >> 1;
    while ((s = ((u8 **)g_text_strings)[i])[0] != '*') {
        text_printf_at(0x94, y, 1, s);
        text_set_color(0xFF, 0xFF, 0xFF, a);
        if (y == y0) {
            y += 0xC;
        }
        i++;
        y += step;
    }
    return gdl;
}
extern s32 g_screen_sprite_1b9c; /* was D_80091B9C */
extern f32 g_screen_k_bef8; /* was D_800ABEF8 */
extern u8 D_85D[];
extern u8 D_89C[];


/* Table g_hud_screen_fns slot 11: three-phase intro/credits screen on a black background, driven by the timer
 * g_game_mode_timer. t < 200: one red text line (g_text_strings + 0x238), zooming from scale 0.75 to 1.5.
 * 200 <= t < 450: two sprites (g_screen_sprite_1ba8 at 1/4 alpha, g_screen_sprite_1b9c), 14 text lines, the 16x16 D_89C icon.
 * t >= 450: the 64x64 D_85D image. g_hud_sprite_desc is a shared sprite descriptor (texture, size, format)
 * that is reset to its 32x32 default afterwards. Skipped (after the clear) when g_os_tv_type != 0. */
/* was func_151EC300 */
Gfx *screen_intro_credits_draw(Gfx *gdl) {
    s32 t;
    s32 a;
    s32 i;
    f32 scale;
    s32 envcol;
    u8 *desc = (u8 *) &g_hud_sprite_desc;

    gDPPipeSync(gdl++);
    gDPSetOtherMode(gdl++, 0x082C3F, 0x504340);
    gDPSetCombine(gdl++, 0xFFFFFF, 0xFFFEFB7D);
    gDPSetEnvColor(gdl++, 0, 0, 0, 0xFF);
    gdl = (Gfx *) render_fill_rect_clamped((u8 *) gdl, 0, 0, g_framebuffer_width, g_framebuffer_height);
    if (g_os_tv_type != 0) {
        return gdl;
    }
    gSPDisplayList(gdl++, g_hud_sprite_setup_dl);
    t = g_game_mode_timer;
    if (t < 200) {
        a = 0xFF - (t - 150) * 8;
        if (a < 0) {
            a = 0;
        }
        if (a >= 0x100) {
            a = 0xFF;
        }
        scale = (f32) t / 180.0f + 0.75f;
        if (scale > 1.5f) {
            scale = 1.5f;
        }
        text_set_scale(scale);
        text_set_color(0xFF, 0, 0, a & 0xFF);
        text_printf_at(0x94, 0x69, 1, *(u8 **) ((u8 *) g_text_strings + 0x238));
        text_set_scale(1.0f);
    } else if (t < 450) {
        if (t < 250) {
            a = (t - 200) * 8;
            if (a >= 0x100) {
                a = 0xFF;
            }
        } else {
            a = 0xFF - (t - 400) * 8;
            if (a < 0) {
                a = 0;
            }
            if (a >= 0x100) {
                a = 0xFF;
            }
        }
        gDPPipeSync(gdl++);
        gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, (a >> 2) & 0xFF);
        gdl = hud_image_draw(gdl, &g_screen_sprite_1ba8, 0x92, 0x67, 5, 6, 1.0f, 0);
        envcol = (a & 0xFF) | ~0xFF;
        gDPPipeSync(gdl++);
        gdl->words.w0 = 0xFB000000;
        gdl->words.w1 = envcol;
        gdl++;
        gdl = hud_image_draw(gdl, &g_screen_sprite_1b9c, 0x92, 0x1C, 2, 1, 1.0f, 0);
        text_set_color(0xFF, 0xFF, 0xFF, a & 0xFF);
        text_printf_at(0x94, 0x9D, 1, *(u8 **) ((u8 *) g_text_strings + 0x204));
        text_printf_at(0x94, 0xAA, 1, *(u8 **) ((u8 *) g_text_strings + 0x208));
        text_printf_at(0x94, 0xBC, 1, *(u8 **) ((u8 *) g_text_strings + 0x20C));
        text_set_scale(g_screen_k_bef8);
        for (i = 0; i < 10; i++) {
            text_printf_at(0x94, 0x2D + i * 10, 1, *(u8 **) ((u8 *) g_text_strings + 0x210 + i * 4));
        }
        text_set_scale(1.0f);
        gDPPipeSync(gdl++);
        gdl->words.w0 = 0xFB000000;
        gdl->words.w1 = envcol;
        gdl++;
        *(u8 **) (desc + 0) = D_89C;
        *(s16 *) (desc + 6) = 0x10;
        *(s16 *) (desc + 8) = 0x10;
        gdl = hud_image_draw(gdl, desc, 0xC7, 0xB0, 1, 1, 1.0f, 0);
        *(s16 *) (desc + 6) = 0x20;
        *(s16 *) (desc + 8) = 0x20;
    } else {
        if (t < 500) {
            a = (t - 450) * 8;
            if (a >= 0x100) {
                a = 0xFF;
            }
        } else {
            a = 0xFF - (t - 650) * 8;
            if (a < 0) {
                a = 0;
            }
            if (a >= 0x100) {
                a = 0xFF;
            }
        }
        gdl->words.w0 = 0xFB000000;
        gdl->words.w1 = (a & 0xFF) | 0xFF000000;
        gdl++;
        desc[0xA] = 4;
        desc[0xB] = 1;
        *(u8 **) (desc + 0) = D_85D;
        *(s16 *) (desc + 6) = 0x40;
        *(s16 *) (desc + 8) = 0x40;
        gdl = hud_image_draw(gdl, desc, 0x94, 0x69, 3, 1, 1.0f, 0);
        *(s16 *) (desc + 6) = 0x20;
        *(s16 *) (desc + 8) = 0x20;
        desc[0xA] = 0;
        desc[0xB] = 3;
    }
    return gdl;
}
/* was func_151EC928 */
s32 screen_late_caption_draw(s32 arg0) {
    s32 temp_t6;
    s32 var_v0;

    if (g_game_mode_timer >= 0x5DD) {
        temp_t6 = (g_game_mode_timer - 0x5DC) * 8;
        var_v0 = temp_t6;
        if (temp_t6 >= 0x100) {
            var_v0 = 0xFF;
        }
        text_set_color(0xFFU, 0xFFU, 0xFFU, var_v0 & 0xFF);
        text_printf_at(0xDC, 0x130, 1, (*(u8 **)((u8 *)g_text_strings + 0x1D0)));
    }
    return arg0;
}
extern s32 g_screen_sprite_1ba8; /* was D_80091BA8 */
extern s32 g_screen_sprite_1bb4; /* was D_80091BB4 */
extern s32 g_screen_sprite_1bc0; /* was D_80091BC0 */
extern s32 g_demo_input_index; /* was D_800E0EA4 */
#define MW(g, a, b) { Gfx *_g = (g); _g->words.w0 = (a); _g->words.w1 = (b); }

/* was func_151EC9A0 */
Gfx *screen_sprite_fade_draw(Gfx *gdl) {
    s32 temp_v1;
    s32 var_v1;
    s32 var_v1_2;
    s32 temp_t0;
    s32 temp_a;

    if (g_level_id == 0x21) {
        return gdl;
    }
    gSPDisplayList(gdl++, g_hud_sprite_setup_dl);
    if (g_game_mode_timer >= 0x12D) {
        temp_v1 = 0x1AC - g_game_mode_timer;
        temp_a = temp_v1 * 2;
        var_v1 = temp_a;
        if (temp_a < 0) {
            var_v1 = 0;
        }
    } else {
        var_v1 = g_game_mode_timer * 8;
        if (var_v1 >= 0x100) {
            var_v1 = 0xFF;
        }
    }
    if (var_v1 != 0) {
        gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, var_v1);
        gdl = hud_image_draw(gdl, &g_screen_sprite_1ba8, 0x92, 0x63, 5, 6, 1.0f, 0);
    }
    gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, 0xFF);
    gdl = hud_image_draw(gdl, &g_screen_sprite_1bb4, 0x92, 0xCB, 5, 2, 1.0f, 0);
    MW(gdl++, 0xFCFFD3FF, 0xFFA6FF7F);
    MW(gdl++, 0xFB000000, (u8) g_menu_blink_alpha | 0x20FF2000);
    gdl = hud_image_draw(gdl, &g_screen_sprite_1bc0, 0x92, 0xCB, 5, 2, 1.0f, 0);
    gdl = sprite_gfx_begin_alt(gdl);
    temp_v1 = 0x1EA - g_demo_input_index;
    if (temp_v1 < 0) {
        var_v1_2 = 0;
    } else {
        temp_t0 = temp_v1 * 0x10;
        var_v1_2 = temp_t0;
        if (temp_t0 >= 0x100) {
            var_v1_2 = 0xFF;
        }
    }
    g_screen_fade_alpha = 0xFF - var_v1_2;
        return gdl;
}
Gfx *hud_image_draw(Gfx *, void *, s32, s32, s32, s32, f32, s32);
Gfx *barrel_menu_draw(Gfx *);
Gfx *cheat_entry_draw(Gfx *);
Gfx *save_screen_frame_draw(Gfx *, s32);
extern Gfx g_hud_sprite_setup_dl[]; /* was D_800903D8 */
extern u8 g_menu_fade_alpha; /* was D_80090484 */
extern s8 g_title_info_screen; /* was D_800902A4 */
extern s8 g_title_screen_adjust; /* was D_800902A8 */
extern u8 g_menu_page_alpha; /* was D_800E0EC5 */
extern s32 g_hud_sprite_desc; /* was D_80090410 */
extern s32 g_menu_page_title_tex[]; /* was D_8009046C */

typedef struct {
    f32 x0;
    f32 x4;
    f32 x8;
    u8 padC[0x20];
    s8 x2C;
    u8 pad2D[0x11];
    s8 x3E;
} Ent174;

/* was func_151ECB98 */
Gfx *frontend_menu_draw(Gfx *gdl) {
    Ent174 *p;
    s32 a;
    s32 v;
    s32 k;
    s32 t;
    SaveSlotSummary *e;

    if (g_cutscene_slot_state == 1) {
        g_menu_fade_alpha = 0;
        return gdl;
    }
    a = g_menu_fade_alpha + g_frame_ticks * 4;
    if (a >= 0x100) {
        a = 0xFF;
    }
    g_menu_fade_alpha = a;
    gSPDisplayList(gdl++, g_hud_sprite_setup_dl);
    p = (Ent174 *)g_menu_state;
    k = p->x3E;
    if (k == 1) {
        return barrel_menu_draw(gdl);
    }
    if (k != 0) {
        return gdl;
    }
    t = p->x2C;
    if (t == 1 && g_title_info_screen != 0) {
        gdl = cheat_entry_draw(gdl);
    } else if (t != 1 || g_title_screen_adjust == 0) {
        v = (p->x0 - 0.5f) * 512.0f;
        if (v < 0) {
            v = -v;
        }
        if (v >= 0x100) {
            v = 0xFF;
        }
        if (g_menu_fade_alpha < v) {
            v = g_menu_fade_alpha;
        }
        if (t == 1) {
            v = (g_menu_page_alpha * v) >> 8;
            if (v >= 0xFE) {
                v = 0xFF;
            }
        }
        gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, v);
        gDPSetOtherMode(gdl++, 0x002C3F, 0x504244);
        g_hud_sprite_desc = g_menu_page_title_tex[((Ent174 *)g_menu_state)->x2C];
        gdl = hud_image_draw(gdl, &g_hud_sprite_desc, 0x94, 0x1E, 3, 1, 1.0f, 0);
    }
    p = (Ent174 *)g_menu_state;
    if (0.5f <= p->x8) {
        if (p->x2C >= 3) {
            e = &g_save_slot_summaries[p->x2C - 3];
            if (e->stamp != -1) {
                gdl = save_screen_frame_draw(gdl, e->resumeLevel);
            }
        }
    }
    return gdl;
}
typedef struct {
    /* 0x00 */ f32 slide;        /* menu slide position (0.5 = centre) */
    /* 0x04 */ f32 x4;
    /* 0x08 */ f32 fade;         /* 0 = fully shown */
    /* 0x0C */ f32 vel;          /* slide velocity */
    /* 0x10 */ u8 pad10[0x1C];
    /* 0x2C */ s8 page;
    /* 0x2D */ u8 pad2D[0x13];
    /* 0x40 */ s8 mode;          /* 0 barrel, 3 single bar, 4 player slots */
    /* 0x41 */ s8 sel;           /* selected barrel */
} BarrelMenu174;
extern s8 g_menu_banner_page;            /* page whose banner is shown; was D_800904A8 */
extern s32 g_menu_page_banner_tex[];         /* banner sprite per page; was D_80090488 */
extern s32 g_menu_barrel_tex[];         /* barrel sprite per item (5); was D_800904AC */
extern u8 g_menu_slot_fill[4];         /* player slot fill (0..255); was D_800E10B8 */
extern u8 g_menu_alpha; /* was D_800E0EC4 */
extern f32 g_menu_slide_phase;           /* barrel rotation phase; was D_80090188 */
extern s8 g_menu_cursor; /* was D_800901CC */
extern s32 g_frame_count;           /* frame counter; was D_800BEDCC */
extern s8 g_menu_joined_count;            /* joined players; was D_800901E0 */
extern s8 g_menu_player_queue[];          /* player queue (controller numbers); was D_800901E4 */
extern s8 g_menu_player_chars[];          /* character per joined player; was D_800E0FC0 */
extern struct127 *g_menu_char_objs[4]; /* character object per controller; was D_800E0FD0 */
extern u8 D_87B[];
extern u8 D_88C[];
extern char g_str_menu_fmt_slot[];         /* "#"; was D_800ABED8 */
extern char g_str_menu_fmt_char[];         /* "#"; was D_800ABEDC */
extern char g_str_menu_fmt_number[];         /* "%d"; was D_800ABEE0 */
s8 mp_slot_query(s32);
void menu_spawn_character(s32 slot, s32 character);
/* barrel_menu_draw: draws the multiplayer barrel menu (g_menu_state mode 1 of frontend_menu_draw) into gdl and returns
 * the new end. A pipe sync, then (unless mode 3) the page banner g_menu_page_banner_tex[g_menu_banner_page] faded by the slide offset
 * and the title D_88C faded by +0x08. Mode 0: once faded in on page 4, the ring of five item barrels (g_menu_barrel_tex,
 * cos ring from the selection +0x41 and the rotation g_menu_slide_phase), the front one pulsing when at rest; mode 3: the
 * single bar mp_scoreboard_draw; mode 4: two or four player slots (page 7: two) that fill while the controller is
 * joined (spawning its character with menu_spawn_character) and empty otherwise (removing the object), each with its
 * frame D_89C, a pulsing highlight, the fill bar D_87B, the slot number and the player's score from
 * mp_slot_query. */
/* was func_151ECE00 */
Gfx *barrel_menu_draw(Gfx *gdl) {
    BarrelMenu174 *m;
    s32 scores[8];
    s32 alpha, a, x, k, mul, prev, cur, mid, v, i, j, slot, dir, nslots, nscores, si, pulse, step, y;
    f32 ang, sc, sizef;
    u8 *fill;

    alpha = (s32) ((((BarrelMenu174 *) g_menu_state)->slide - 0.5f) * 512.0f);
    if (alpha < 0) {
        alpha = -alpha;
    }
    if (alpha >= 0x100) {
        alpha = 0xFF;
    }
    gDPPipeSync(gdl++);
    m = (BarrelMenu174 *) g_menu_state;
    if (m->fade == 0.0f && m->vel == 0.0f) {
        g_menu_banner_page = m->page;
    } else if (m->page == 0 && m->vel < 0.0f) {
        g_menu_banner_page = 4;
    }
    if (m->page == 0) {
        y = 0x6A;
        a = 0xFF - (s32) (m->fade * 300.0f);
    } else {
        a = alpha;
        y = 0x6A - (s32) (m->fade * (g_menu_banner_page == 4 ? 68.0f : 76.0f));
    }
    if (m->mode != 3) {
        if (a > 0 && g_menu_page_banner_tex[g_menu_banner_page] != 0) {
            gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, a);
            if (g_menu_banner_page == 4) {
                sc = 0.8f;
                k = 2;
                mul = 2;
            } else {
                sc = 1.0f;
                k = 2;
                mul = 1;
                if (g_menu_banner_page != 0) {
                    k = 3;
                }
            }
            g_hud_sprite_desc = g_menu_page_banner_tex[g_menu_banner_page];
            gdl = hud_image_draw(gdl, &g_hud_sprite_desc, 0x94, y, k, mul, sc, 0);
            m = (BarrelMenu174 *) g_menu_state;
        }
        a = 0xFF - (s32) (m->fade * 300.0f);
        if (a > 0) {
            gDPPipeSync(gdl++);
            gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, a);
            g_hud_sprite_desc = (s32) D_88C;
            gdl = hud_image_draw(gdl, &g_hud_sprite_desc, 0x94, 0x1E, 3, 1, 1.0f, 0);
            m = (BarrelMenu174 *) g_menu_state;
        }
    }
    switch (m->mode) {
        case 0:
            g_menu_slot_fill[0] = 0;
            g_menu_slot_fill[1] = 0xFF;
            g_menu_slot_fill[2] = 0xFF;
            g_menu_slot_fill[3] = 0xFF;
            if (!(m->fade >= 0.5f) || m->page != 4) {
                break;
            }
            alpha = (g_menu_alpha * g_menu_page_alpha) >> 8;
            if (alpha >= 0xFE) {
                alpha = 0xFF;
            }
            ang = 0.62831855f + (0.62831855f + 0.62831855f * g_menu_slide_phase);
            prev = 0x7E - (s32) (cosf(ang) * 52.0f);
            i = ((BarrelMenu174 *) g_menu_state)->sel - 4;
            if (i < 0) {
                i += 5;
            }
            for (j = 1; j != 8; j++) {
                ang -= 0.62831855f;
                cur = 0x7E - (s32) (cosf(ang) * 52.0f);
                if (prev < cur) {
                    gDPPipeSync(gdl++);
                    gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, alpha);
                    mid = ((cur - prev) >> 1) + prev;
                    sizef = (f32) (cur - prev) * 0.03125f;
                    g_hud_sprite_desc = g_menu_barrel_tex[i];
                    gdl = hud_image_draw(gdl, &g_hud_sprite_desc, 0x53, mid, 2, 1, sizef, -1);
                    if (g_menu_slide_phase == 0.0f && j == 5 && g_menu_cursor == 0) {
                        v = (g_frame_count * 2) & 0x7F;
                        if (v >= 0x40) {
                            v = 0x7F - v;
                        }
                        v = (alpha * (v * 3 + 0x3F)) >> 8;
                        if (v >= 0x100) {
                            v = 0xFF;
                        }
                        gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, v);
                        g_hud_sprite_desc = g_menu_barrel_tex[i] + 2;
                        gdl = hud_image_draw(gdl, &g_hud_sprite_desc, 0x53, mid, 2, 1, sizef, -1);
                    }
                }
                i++;
                if (i >= 5) {
                    i -= 5;
                }
                prev = cur;
            }
            break;
        case 4:
            x = 0x28;
            pulse = (s32) (g_menu_page_alpha * (s32) ((sinf((f32) (g_frame_count & 0x3F) * 0.09817469f + 0.7853975f) + 1.0f) * 127.0f)) >> 8;
            if (((BarrelMenu174 *) g_menu_state)->page == 7) {
                x = 0x70;
                nslots = 2;
            } else {
                nslots = 4;
            }
            nscores = mp_slot_query((s32) scores);
            if (nscores != 0) {
                si = 0;
            }
            fill = g_menu_slot_fill;
            for (slot = 0; slot != nslots; slot++, fill++, x += 0x48) {
                j = -1;
                dir = 1;
                for (i = 0; i < g_menu_joined_count; i++) {
                    if (slot == g_menu_player_queue[i]) {
                        j = i;
                        dir = -1;
                        break;
                    }
                }
                if (slot != 0 && g_menu_char_objs[0] != NULL) {
                    if (*fill != 0xFF) {
                        if (g_menu_char_objs[slot] == NULL && j != -1) {
                            menu_spawn_character(slot, g_menu_player_chars[j]);
                        }
                    } else if (g_menu_char_objs[slot] != NULL) {
                        obj_remove(g_menu_char_objs[slot], 1);
                        g_menu_char_objs[slot] = NULL;
                    }
                }
                v = *fill + dir * (g_frame_ticks * 8);
                if (v >= 0x100) {
                    v = 0xFF;
                } else if (v < 0) {
                    v = 0;
                }
                *fill = v;
                gDPPipeSync(gdl++);
                gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, g_menu_page_alpha);
                g_hud_sprite_desc = (s32) (D_89C + 2);
                y = 0x8C - (s32) ((f32) v * 0.14285715f);
                gdl = hud_image_draw(gdl, &g_hud_sprite_desc, x, y, 1, 1, 1.0f, 0);
                if (v > 0) {
                    gDPPipeSync(gdl++);
                    gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, pulse);
                    gdl = hud_image_draw(gdl, &g_hud_sprite_desc, x, y, 1, 1, 1.0f, 1);
                    gDPPipeSync(gdl++);
                    step = (g_menu_page_alpha * v) >> 8;
                    if (step >= 0xFE) {
                        step = 0xFF;
                    }
                    gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, step);
                    g_hud_sprite_desc = (s32) D_87B;
                    gdl = hud_image_draw(gdl, &g_hud_sprite_desc, x, 0x82, 1, 1, 1.0f, 0);
                }
                text_set_color(0xFF, 0xFF, 0xFF, g_menu_page_alpha);
                text_printf_at(x, 0x41, 0x80, g_str_menu_fmt_slot, slot + 1);
                if (nscores != 0 && j >= 0 && g_menu_player_queue[j] >= 0) {
                    nscores--;
                    text_printf_at(x, 0xA8, 0, g_str_menu_fmt_char, 0x38);
                    text_printf_at(x, 0xA2, 0x81, g_str_menu_fmt_number, scores[si] + 1);
                    si++;
                }
            }
            break;
        case 3:
            gdl = (Gfx *) mp_scoreboard_draw(gdl, 0x6A, 0xFF, 0);
            break;
    }
    return gdl;
}

Gfx *hud_image_draw(Gfx *, void *, s32, s32, s32, s32, f32, s32);
extern Gfx g_hud_sprite_setup_dl[]; /* was D_800903D8 */
extern u8 g_screen_logo_sprite[]; /* was D_80091BCC */
extern u8 g_screen_logo_glow_sprite[]; /* was D_80091BD8 */

/* Table g_hud_screen_fns slot 17. The original is void in C but its v0 is sprite_gfx_begin_alt's return value, which
 * hud_overlay_draw_screen uses as the new display-list pointer: under NON_MATCHING it returns it explicitly. */
/* was func_151ED854 */
Gfx *screen_logo_glow_draw(Gfx *gdl) {
    s32 a;

    gSPDisplayList(gdl++, g_hud_sprite_setup_dl);
    a = g_game_mode_timer * 4;
    if (a >= 0x100) {
        a = 0xFF;
    }
    gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, a);
    gdl = hud_image_draw(gdl, g_screen_logo_sprite, 0x92, 0x6C, 8, 3, 1.0f, 0);
    gDPPipeSync(gdl++);
    gDPSetCombine(gdl++, 0xFFD3FF, 0xFFA6FF7F);
    gDPSetEnvColor(gdl++, 0xFF, 0x80, 0x20, ((u8)g_menu_blink_alpha * (a + 1)) >> 8);
    return sprite_gfx_begin_alt(hud_image_draw(gdl, g_screen_logo_glow_sprite, 0x92, 0x6C, 8, 3, 1.0f, 0));
}

u8 *render_fill_rect_clamped(u8 *, s32, s32, s32, s32);
/* was func_151ED998 */
Gfx *screen_fade_rect_draw(Gfx *gdl) {
    if ((u8)g_screen_fade_alpha == 0) {
        return gdl;
    }
    gDPPipeSync(gdl++);
    gDPSetOtherMode(gdl++, 0x082C3F, 0x504340);
    gDPSetCombine(gdl++, 0xFFFFFF, 0xFFFEFB7D);
    gDPSetEnvColor(gdl++, 0, 0, 0, (u8)g_screen_fade_alpha);
    return (Gfx *)render_fill_rect_clamped((u8 *)gdl, 0, 0, g_framebuffer_width, g_framebuffer_height);
}

/* Tile setup for hud_image_draw: LoadBlock word count (*outBlock, from the g_tex_siz_load_incr/84 size tables), then
 * SetTile (load tile 7) / SetTile (render tile 0, line = w * g_tex_siz_line_bytes[siz] bytes / 8, masks = ceil(log2(w/h)), wrap)
 * and SetTileSize. desc: +6 width, +8 height, +0xA format, +0xB size. */
/* was func_151EDA54 */
Gfx *hud_image_tile_setup(Gfx *gdl, u8 *desc, s32 *outBlock) {
    s32 w = *(u16 *)(desc + 6);
    s32 h;
    s32 maskS = 1, maskT = 1;
    s32 p;
    u32 fmt;
    u32 *g = (u32 *)gdl;

    *outBlock = (s32)(g_tex_siz_load_incr[desc[0xB]] + w * *(u16 *)(desc + 8)) >> g_tex_siz_load_shift[desc[0xB]];
    w = *(u16 *)(desc + 6);
    if (w >= 3) {
        p = 2;
        do {
            p <<= 1;
            maskS++;
        } while (p < w);
    }
    h = *(u16 *)(desc + 8);
    if (h >= 3) {
        p = 2;
        do {
            p <<= 1;
            maskT++;
        } while (p < h);
    }
    g[0] = 0xE7000000;
    g[1] = 0;
    fmt = ((desc[0xA] & 7) << 21) | 0xF5000000;
    g[2] = ((g_tex_siz_load_block[desc[0xB]] & 3) << 19) | fmt;
    g[3] = 0x07000000;
    g[4] = ((((g_tex_siz_line_bytes[desc[0xB]] * *(u16 *)(desc + 6) + 7) >> 3) & 0x1FF) << 9) | fmt | ((desc[0xB] & 3) << 19);
    g[5] = ((maskT & 0xF) << 14) | 0x80200 | ((maskS & 0xF) << 4);
    g[6] = 0xF2000000;
    g[7] = ((((*(u16 *)(desc + 6) - 1) * 4) & 0xFFF) << 12) | (((*(u16 *)(desc + 8) - 1) * 4) & 0xFFF);
    return (Gfx *)(g + 8);
}
/* HUD image drawn as cols x rows tiles: each tile's texture comes from the texture cache (texture_cache_lookup, id
 * desc+0 + idOffset, consecutive ids unless a block is larger than 0x1000 bytes and is split in halves), then
 * SetTImg / LoadBlock / scissored TextureRectangle (gSPScisTextureRectangle) at the scaled screen position.
 * desc: +0 base texture id, +6 tile width, +8 tile height (u16), +0xA format, +0xB size. idOffset < 0: x scale 1. */
/* was func_151EDBE8 */
Gfx *hud_image_draw(Gfx *gdl, void *descArg, s32 x, s32 y, s32 cols, s32 rows, f32 scale, s32 idOffset) {
    u8 *desc = descArg;
    s32 blockSize; /* spB0, from hud_image_tile_setup */
    s32 texSize;   /* sp98 */
    s32 haveTex;
    s32 tex;
    f32 xscale;
    s32 tileW, tileH, dsdx, dtdy;
    s32 texId;
    s32 tx, ty, tyStart;
    s32 c, r;

    haveTex = 0;
    tex = 0;
    texSize = 0;
    gdl = hud_image_tile_setup(gdl, desc, &blockSize);
    if (idOffset < 0) {
        xscale = 1.0f;
        idOffset = 0;
    } else {
        xscale = scale;
    }
    texId = *(s32 *)(desc + 0) + idOffset;
    tileW = (s32)((f32)*(u16 *)(desc + 6) * xscale * g_hud_scale_x);
    tileH = (s32)((f32)*(u16 *)(desc + 8) * scale * g_hud_scale_y);
    dtdy = (s32)(1024.0f / (scale * g_hud_scale_y));
    dsdx = (s32)(1024.0f / (xscale * g_hud_scale_x));
    tx = (s32)((f32)x * g_hud_scale_x) - ((tileW * cols) >> 1);
    tyStart = (s32)((f32)y * g_hud_scale_y) - ((tileH * rows) >> 1);
    for (c = 0; c < cols; c++) {
        ty = tyStart;
        for (r = 0; r < rows; r++) {
            if (haveTex == 0) {
                tex = texture_cache_lookup(texId, &texSize, 3, 0);
            }
            if (tex != (s32)0x80000000) {
                s32 xl4 = (s16)(tx * 4), xh4 = (s16)((tx + tileW) * 4);
                s32 yl4 = (s16)(ty * 4), yh4 = (s16)((ty + tileH) * 4);
                s32 lrs = blockSize - 1;
                s32 s, t;

                gdl->words.w0 = 0xE7000000;
                gdl->words.w1 = 0;
                gdl++;
                gdl->words.w0 = 0xFD000000 | ((g_tex_siz_load_block[desc[0xB]] & 3) << 19) | ((desc[0xA] & 7) << 21);
                gdl->words.w1 = tex;
                gdl++;
                gdl->words.w0 = 0xF3000000;
                if (lrs >= 0x7FF) {
                    lrs = 0x7FF;
                }
                gdl->words.w1 = 0x07000000 | ((lrs & 0xFFF) << 12);
                gdl++;
                gdl->words.w0 = 0xE4000000 | (((xh4 > 0 ? xh4 : 0) & 0xFFF) << 12) | ((yh4 > 0 ? yh4 : 0) & 0xFFF);
                gdl->words.w1 = (((xl4 > 0 ? xl4 : 0) & 0xFFF) << 12) | ((yl4 > 0 ? yl4 : 0) & 0xFFF);
                gdl++;
                gdl->words.w0 = 0xE1000000;
                s = 0;
                if (xl4 < 0) {
                    s32 v = (xl4 * (s16)dsdx) >> 7;
                    if ((s16)dsdx < 0) {
                        s = v > 0 ? v : 0;
                    } else {
                        s = v < 0 ? v : 0;
                    }
                }
                t = 0;
                if ((ty * 4) < 0) {
                    s32 v = (yl4 * (s16)dtdy) >> 7;
                    if ((s16)dtdy < 0) {
                        t = v > 0 ? v : 0;
                    } else {
                        t = v < 0 ? v : 0;
                    }
                }
                gdl->words.w1 = ((-s) << 16) | (-t & 0xFFFF);
                gdl++;
                gdl->words.w0 = 0xF1000000;
                gdl->words.w1 = (dsdx << 16) | (dtdy & 0xFFFF);
                gdl++;
            }
            ty += tileH;
            haveTex = 0;
            if (texSize > 0x1000) {
                haveTex = 1;
                if (tex != 0) {
                    tex += (blockSize << desc[0xB]) >> 1;
                }
                texSize -= (blockSize << desc[0xB]) >> 1;
            } else {
                texId++;
            }
        }
        tx += tileW;
    }
    gdl->words.w0 = 0xE7000000;
    gdl->words.w1 = 0;
    gdl++;
    return gdl;
}
/* HUD model (0xA8 bytes; hud_anim_model_load builds it, hud_anim_model_draw draws it, hud_anim_model_free frees it). The pause /
 * counter screen keeps two: g_hud_cash_model (file 0xA4, the blinking head) and g_hud_pause_model_a2 (file 0xA2). */
typedef struct {
    Gfx **dls;          /* 0x00 the model's display lists (animmodel_create) */
    Gfx *copies[4];     /* 0x04 HUD copies of the display lists (count entries) */
    u8 count;           /* 0x14 display list count */
    u8 blink;           /* 0x15 frames until the next blink (g_hud_cash_model only) */
    u8 pad16[6];
    s32 seg6;           /* 0x1C segment 6 base of the model data */
    s32 u20;
    u8 *inst;           /* 0x24 animated model instance (0x3F8 bytes) */
    f32 mtx[2][4][4];   /* 0x28 model matrix, one per frame buffer (g_dl_buf_index) */
} HudModel;

s32 animmodel_create(s32, s32, void *, void *, void *, void *, void *);
void animmodel_start_anim(u8 *, s32, s32, f32, f32, s32);
void animmodel_update_matrices(u8 *);
void heap_free(void *);
u8 *allocate_memory(s32, s32, s32, s32);

/* hud_model_load: allocates a HudModel, loads model `file` with animation table entry `entry` (animmodel_create),
 * starts animation `anim` at `speed`, and makes a HUD copy of each of its display lists: every
 * G_RDPSETOTHERMODE (0xEF) gets bit 16 of w0 cleared and render mode 0x5041C8, every G_SETCOMBINE (0xFC) becomes a
 * no-op, so the caller's combiner applies. Returns the HudModel, or 0 when an allocation or the load fails. */
/* was func_151EE0C4 */
s32 hud_anim_model_load(s32 file, s32 entry, s32 anim, f32 speed) {
    HudModel *m;
    Gfx *src;
    Gfx *dst;
    u32 w0;
    u32 op;
    s32 size;
    s32 i;
    s32 j;

    m = (HudModel *) allocate_memory(sizeof(HudModel), 1, 0, 1);
    if (m == NULL) {
        return 0;
    }
    m->blink = 1;
    if (animmodel_create(file, entry, &m->dls, &m->count, &m->seg6, &m->u20, &m->inst) != 0) {
        heap_free(m);
        return 0;
    }
    guMtxIdentF(m->mtx[0]);
    guMtxIdentF(m->mtx[1]);
    *(f32 **) (m->inst + 0x3E0) = (f32 *) m->mtx[0];
    *(f32 **) (m->inst + 0x3E4) = (f32 *) m->mtx[1];
    animmodel_start_anim(m->inst, 1, anim, speed, 0.0f, 0);

    /* size of each display list, up to and including its G_ENDDL (0xDF) */
    for (i = 0; i < m->count; i++) {
        src = m->dls[i];
        size = 0;
        do {
            size += sizeof(Gfx);
        } while (((src++)->words.w0 >> 24) != 0xDF);
        m->copies[i] = (Gfx *) allocate_memory(size, 1, 1, 1);
        if (m->copies[i] == NULL) {
            for (j = 0; j < i; j++) {
                heap_free(m->copies[j]);
            }
            heap_free(m);
            return 0;
        }
    }

    for (i = 0; i < m->count; i++) {
        src = m->dls[i];
        dst = m->copies[i];
        do {
            w0 = src->words.w0;
            dst->words.w0 = w0;
            dst->words.w1 = src->words.w1;
            op = w0 >> 24;
            if (op == 0xEF) {
                dst->words.w0 = w0 & ~0x10000;
                dst->words.w1 = 0x5041C8;
            }
            if (op == 0xFC) {
                dst->words.w0 = 0;
            }
            src++;
            dst++;
        } while (op != 0xDF);
    }
    return (s32) m;
}

/* was func_151EE310 */
void hud_anim_model_free(u8 *arg0) {
    s32 i;

    if (arg0 != NULL) {
        animmodel_free(*(s32 *)(arg0 + 0x24));
        heap_set_block_tag(arg0, 4);
        for (i = 0; i < arg0[0x14]; i++) {
            heap_set_block_tag(((s32 **)(arg0 + 4))[i], 4);
        }
    }
}

extern Gfx g_hud_model_setup_dl[]; /* was D_800904C0 */
extern Gfx g_hud_model_end_dl[]; /* was D_800904D8 */

/* hud_model_draw: draws a HudModel (hud_anim_model_load) at screen position (x, y), z -100, with uniform `scale` (x and
 * scale times g_hud_scale_x, y times g_hud_scale_y): sets this frame buffer's model matrix, advances the animation
 * (animmodel_update_matrices), loads the HUD matrices and render state (g_hud_model_setup_dl, env alpha g_hud_model_env_alpha), segment 3 = the
 * instance's matrices for this frame buffer, segment 1 = the model data, then calls the HUD display list copies and
 * g_hud_model_end_dl. g_hud_cash_model (the head) blinks: a random 15..142 frame timer, texture 0x507 for its last 6 frames, else
 * 0x508, bound to segments 6 / 7; when that texture is not loaded yet (texture_cache_lookup returns 0x80000000) nothing
 * is drawn and gdl is returned unchanged. */
/* was func_151EE394 */
u8 *hud_anim_model_draw(u8 *gdl, s32 model, f32 x, f32 y, f32 scale) {
    HudModel *m = (HudModel *) model;
    Gfx *g = (Gfx *) gdl;
    s32 tex;
    s32 i;

    if (g_hud_scale_x != 1.0f) {
        x *= g_hud_scale_x;
        y *= g_hud_scale_y;
        scale *= g_hud_scale_x;
    }
    guMtxIdentF(m->mtx[g_dl_buf_index]);
    m->mtx[g_dl_buf_index][3][0] = x;
    m->mtx[g_dl_buf_index][3][1] = y;
    m->mtx[g_dl_buf_index][3][2] = -100.0f;
    m->mtx[g_dl_buf_index][0][0] = scale;
    m->mtx[g_dl_buf_index][1][1] = scale;
    m->mtx[g_dl_buf_index][2][2] = scale;
    animmodel_update_matrices(m->inst);

    g->words.w0 = 0xDA380003; /* gSPMatrix: load modelview */
    g->words.w1 = (u32) g_identity_mtx;
    g++;
    g->words.w0 = 0xDA380007; /* gSPMatrix: load projection */
    g->words.w1 = (u32) &g_hud_model_proj_mtx;
    g++;
    g->words.w0 = 0xDE000000;
    g->words.w1 = (u32) g_hud_model_setup_dl;
    g++;
    g->words.w0 = 0xFC12FE25; /* combiner */
    g->words.w1 = 0xFFFFFBFD;
    g++;
    g->words.w0 = 0xD9000000; /* geometry mode: clear all ... */
    g->words.w1 = 0;
    g++;
    g->words.w0 = 0xD9FFFFFF; /* ... then set 0x200404 */
    g->words.w1 = 0x200404;
    g++;
    g->words.w0 = 0xFA000000; /* prim color white */
    g->words.w1 = 0xFFFFFFFF;
    g++;
    g->words.w0 = 0xFB000000; /* env color white, alpha g_hud_model_env_alpha */
    g->words.w1 = (g_hud_model_env_alpha & 0xFF) | ~0xFF;
    g++;
    g->words.w0 = 0xF8000000; /* fog color */
    g->words.w1 = 0xFF;
    g++;
    g->words.w0 = 0xDB06000C; /* segment 3 */
    g->words.w1 = *(u32 *) (m->inst + 0x3E8 + g_dl_buf_index * 4);
    g++;
    g->words.w0 = 0xDB060004; /* segment 1 */
    g->words.w1 = m->seg6;
    g++;
    if (m == (HudModel *) g_hud_cash_model) {
        m->blink--;
        if (m->blink == 0) {
            m->blink = (random_int() & 0x7F) + 15;
        }
        tex = texture_cache_lookup(m->blink < 7 ? 0x507 : 0x508, 0, 3, 0);
        if (tex == (s32) 0x80000000) {
            return gdl;
        }
        g->words.w0 = 0xDB060018; /* segment 6 */
        g->words.w1 = tex;
        g++;
        g->words.w0 = 0xDB06001C; /* segment 7 */
        g->words.w1 = tex;
        g++;
    }
    for (i = 0; i < m->count; i++) {
        g->words.w0 = 0xDE000000;
        g->words.w1 = (u32) m->copies[i];
        g++;
    }
    g->words.w0 = 0xDE000000;
    g->words.w1 = (u32) g_hud_model_end_dl;
    g++;
    return (u8 *) g;
}

extern u8 *g_menu_sprite_entries;   /* menu sprite entries (12 bytes each); was D_800904E8 */
extern u8 *g_menu_sprite_block;   /* menu sprite block (0x1A8 bytes); was D_800E10AC */
extern s8 g_cheat_cursor_col; /* was D_800E10B0 */
extern s8 g_cheat_cursor_row; /* was D_800E10B1 */
extern s8 g_cheat_letter_tilt; /* was D_800E10B2 */
extern s8 g_cheat_text_len; /* was D_800E10B3 */
extern s8 g_cheat_key_repeat; /* was D_800E10B4 */
u8 *allocate_memory(s32, s32, s32, s32);
s32 asset_load_with_subfiles(s32 *, s32, s32 *, s32, ...);  /* varargs, as its definition (game_57FA0) */
s32 texture_resolve_dl_ids(s32, s32, s32, s32, s32 *);
// menu_sprites_load: mode 3's first frame. Allocates the 0x1A8-byte menu sprite block g_menu_sprite_block (0x40 header bytes,
// then 30 entries of 12 bytes at g_menu_sprite_entries: display list, asset, +8 filled by texture_resolve_dl_ids), loads the menu
// sprite assets 0x1C5..0x1E2 (asset_load_with_subfiles(0, 1, 0, 2, 9, id)) and patches each display list up to its
// G_ENDDL (0xDF): G_VTX (1) addresses are relocated into the asset and the first two vertices get colour 0,0,0,0xFF,
// G_SETCOMBINE (0xFC) becomes 0xFC127E05 / 0xFFFFF3F8, G_SETOTHERMODE_H (0xEF) gets bit 0x100000 and w1 0x0F0A4000.
// Then clears g_cheat_cursor_col..B4 and the block's bytes 0 and 0x20. On allocation failure g_menu_sprite_entries stays NULL.
/* was func_151EE704 */
void menu_sprites_load(void) {
    u8 *block;
    s32 *asset;
    u32 *dl;
    u8 *vtx;
    s32 id;
    s32 off;
    u32 cmd;

    g_menu_sprite_entries = NULL;
    block = allocate_memory(0x1A8, 1, 0, 0);
    g_menu_sprite_block = block;
    if (block == NULL) {
        return;
    }
    g_menu_sprite_entries = block + 0x40;
    for (id = 0x1C5, off = 0; id != 0x1E3; id++, off += 0xC) {
        asset = (s32 *) asset_load_with_subfiles(NULL, 1, NULL, 2, 9, id);
        *(s32 **) (g_menu_sprite_entries + off + 4) = asset;
        *(s32 *) (g_menu_sprite_entries + off) = *asset;
        texture_resolve_dl_ids(*(s32 *) (g_menu_sprite_entries + off), 0, 1, 0x3E, (s32 *) (g_menu_sprite_entries + off + 8));
        dl = *(u32 **) (g_menu_sprite_entries + off);
        do {
            cmd = (dl[0] >> 24) & 0xFF;
            if (cmd == 1) {
                dl[1] += (u32) asset;
                vtx = (u8 *) dl[1];   /* P121/P120: the asm ORs 0x80000000, a no-op for the KSEG0 asset address (w1 += asset); kept out: it breaks wasm addresses */
                vtx[0xC] = 0;
                vtx[0xD] = 0;
                vtx[0xE] = 0;
                vtx[0xF] = 0xFF;
                vtx += 0x10;
                vtx[0xC] = 0;
                vtx[0xD] = 0;
                vtx[0xE] = 0;
                vtx[0xF] = 0xFF;
            }
            if (cmd == 0xFC) {
                dl[0] = 0xFC127E05;
                dl[1] = 0xFFFFF3F8;
            }
            if (cmd == 0xEF) {
                dl[1] = 0x0F0A4000;
                dl[0] |= 0x100000;
            }
            dl += 2;
        } while (cmd != 0xDF);
    }
    g_cheat_cursor_col = 0;
    g_cheat_cursor_row = 0;
    g_cheat_letter_tilt = 0;
    g_cheat_text_len = 0;
    g_menu_sprite_block[0] = 0;
    g_menu_sprite_block[0x20] = 0;
    g_cheat_key_repeat = 0;
}

extern u8 g_str_cheat_cursor[];          /* "-": the blinking text cursor; was D_800ABEE4 */
void mtx_translate_fixed(Mtx *, f32, f32, f32);
s32 aiscript_find_by_kind(s32, s32);
void text_measure_string(u8 *, s32 *, s32 *, s32 *);
// cheat_entry_draw: the cheat-code entry screen (barrel menu page 1 while g_title_info_screen is set, from frontend_menu_draw).
// Pad bits at g_menu_state + 0x20 (1 up, 2 down, 4 left, 8 right, 0x10 select) move the cursor over the letter wheel
// (row g_cheat_cursor_row 0..5 wrapping, column g_cheat_cursor_col clamped to 0 / last: rows 0-3 'A'..'X', row 4 delete / '.' / 'Y' /
// 'Z' / enter, row 5 space) with sound 0x62D; g_cheat_letter_tilt tilts the selected letter (+8 / -8 a frame within 0..12
// while g_pad_states[0] bit 0x8000 is set / clear). Select (sound 0x500) appends to the typed text g_menu_sprite_block (19 chars
// max, length g_cheat_text_len) or deletes / enters. Enter: column k of the 19 strings g_text_strings[0x90..0xA2] holds char k
// (space padded) of 32 cheat codes; the highest code equal to the text sets its g_cheat_flags bit (0x400 / 0x800 clear
// each other), sound 0xC3 / 0xC4, message kind 0x10. Else (kind 0x11) the whole-word phrases g_text_strings[0xA3..0xC7]
// are searched in the text (sound 0xC1 / 0xC2); else 0xC5 / 0xC6, or 0xC7 when the same text is entered a second
// time in a row (g_cheat_key_repeat counts repeats). The text is kept at g_menu_sprite_block + 0x20, an object of type 9
// (obj_find_by_setup_id) gets the kind at +0x232 and becomes g_cur_obj, and the text is cleared. Then the wheel is drawn:
// the 30 sprite display lists of g_menu_sprite_entries (12-byte entries) under the matrix built by mtx_build_rot_trans and the
// projection g_hud_model_proj_mtx, the selected one magenta with the tilt matrix, and the text at (75 - width / 2, min 10;
// 180) with a '-' cursor shown 22 frames out of 32. Returns the display list end.
/* was func_151EE93C */
Gfx *cheat_entry_draw(Gfx *gdl) {
    s32 moved;
    s32 row;
    s32 col;
    s32 cols;
    s32 sel;
    s32 ch;
    s32 sfx;
    s32 kind;
    s32 cheat;
    s32 bit;
    s32 len;
    s32 i;
    s32 n;
    u32 match;
    u8 c;
    u8 *str;
    u8 *in;
    u8 *pat;
    u8 *text;
    Mtx *mtx;
    struct127 *obj;
    u16 persp;
    s32 w;
    s32 h;
    s32 d;
    s32 x;
    s32 off;

    sfx = 0;
    if (g_menu_sprite_entries == NULL) {
        return gdl;
    }

    /* cursor movement over the wheel */
    moved = FALSE;
    if (*(u16 *) (g_menu_state + 0x20) & 1) {
        g_cheat_cursor_row--;
        moved = TRUE;
    }
    if (*(u16 *) (g_menu_state + 0x20) & 2) {
        g_cheat_cursor_row++;
        moved = TRUE;
        if (g_cheat_cursor_row == 4 && g_cheat_cursor_col >= 5) {
            g_cheat_cursor_col = 4;
        }
    }
    row = g_cheat_cursor_row;
    col = g_cheat_cursor_col;
    if (row < 0) {
        g_cheat_cursor_row = 5;
        row = g_cheat_cursor_row;
    }
    if (row >= 6) {
        g_cheat_cursor_row = 0;
        row = g_cheat_cursor_row;
    }
    if (*(u16 *) (g_menu_state + 0x20) & 8) {
        g_cheat_cursor_col = col + 1;
        col = g_cheat_cursor_col;
        moved = TRUE;
    }
    if (*(u16 *) (g_menu_state + 0x20) & 4) {
        g_cheat_cursor_col = col - 1;
        col = g_cheat_cursor_col;
        moved = TRUE;
    }
    if (row == 4) {
        cols = 5;
    } else if (row == 5) {
        cols = 1;
    } else {
        cols = 6;
    }
    if (col < 0) {
        g_cheat_cursor_col = cols - 1;
        col = g_cheat_cursor_col;
    }
    if (col >= cols) {
        g_cheat_cursor_col = 0;
    }
    if (moved) {
        sound_play_2d(0x62D, 0x4650, 0x40, 0, 0);
    }
    sel = g_cheat_cursor_row * 6 + g_cheat_cursor_col;
    if (g_cheat_cursor_row == 5) {
        sel--;
    }

    mtx = (Mtx *) allocate_memory(0x80, 4, 2, 0);
    if (g_pad_states[0] & 0x8000) {
        g_cheat_letter_tilt += 8;
    } else {
        g_cheat_letter_tilt -= 8;
    }
    if (g_cheat_letter_tilt < 0) {
        g_cheat_letter_tilt = 0;
    }
    if (g_cheat_letter_tilt >= 13) {
        g_cheat_letter_tilt = 12;
    }

    if (*(u16 *) (g_menu_state + 0x20) & 0x10) {
        sound_play_2d(0x500, 0x7D00, 0x40, 0, 0);
        ch = sel + 'A';
        if (g_cheat_cursor_row == 5) {
            ch = ' ';
        } else if (g_cheat_cursor_row == 4) {
            if (g_cheat_cursor_col == 0) {
                /* delete */
                if (g_cheat_text_len > 0) {
                    g_cheat_text_len--;
                }
                g_menu_sprite_block[g_cheat_text_len] = '\0';
                ch = 0;
            } else if (g_cheat_cursor_col == 1) {
                ch = '.';
            } else if (g_cheat_cursor_col != 4) {
                ch = sel + 'A' - 2;
            } else {
                /* enter: cheat codes, one column string per text position */
                match = 0xFFC3FFFE;
                len = g_cheat_text_len;
                for (i = 0x90; i < 0xA3; i++) {
                    str = ((u8 **) g_text_strings)[i];
                    if (i - 0x90 < len) {
                        c = g_menu_sprite_block[i - 0x90];
                    } else {
                        c = ' ';
                    }
                    for (n = 0; n < 32; n++) {
                        if (c != str[n]) {
                            match &= ~(1 << n);
                        }
                    }
                }
                cheat = -1;
                for (n = 0; n < 33; n++) {
                    if (match & 1) {
                        cheat = n;
                    }
                    match >>= 1;
                }
                if (cheat >= 0) {
                    bit = 1 << cheat;
                    g_cheat_flags |= bit;
                    if (bit == 0x400) {
                        g_cheat_flags &= ~0x800;
                    } else if (bit == 0x800) {
                        g_cheat_flags &= ~0x400;
                    }
                    kind = 0x10;
                    sfx = (random_int() & 1) + 0xC3;
                } else {
                    /* phrases: a phrase must equal a whole space-separated word run of the text */
                    kind = 0x11;
                    for (i = 0xA3; i < 0xC8 && sfx == 0; i++) {
                        in = g_menu_sprite_block;
                        if (in == NULL) {
                            continue;
                        }
                        while ((pat = ((u8 **) g_text_strings)[i]) != NULL) {
                            n = 0;
                            while (pat[n] == *in && *in != '\0' && pat[n] != '\0') {
                                in++;
                                n++;
                            }
                            if (pat[n] == '\0' && (*in == ' ' || *in == '\0')) {
                                in = NULL;
                                sfx = (random_int() & 1) + 0xC1;
                            } else if (*in == ' ') {
                                in++;
                            } else {
                                while (*in != '\0' && *in != ' ') {
                                    in++;
                                }
                                if (*in == '\0') {
                                    in = NULL;
                                }
                            }
                            if (in == NULL) {
                                break;
                            }
                        }
                    }
                    if (sfx == 0) {
                        sfx = (random_int() & 1) + 0xC5;
                        text = g_menu_sprite_block;
                        n = 0;
                        while (text[n + 0x20] != '\0' && text[n] != '\0' && text[n + 0x20] == text[n]) {
                            n++;
                        }
                        if (text[n + 0x20] == '\0' && text[n] == '\0') {
                            g_cheat_key_repeat++;
                            if (g_cheat_key_repeat == 1) {
                                sfx = 0xC7;
                            }
                        } else {
                            g_cheat_key_repeat = 0;
                        }
                    } else {
                        g_cheat_key_repeat = 0;
                    }
                }
                /* keep the text as the previous entry */
                for (n = 0; g_menu_sprite_block[n] != '\0'; n++) {
                    g_menu_sprite_block[n + 0x20] = g_menu_sprite_block[n];
                }
                g_menu_sprite_block[n + 0x20] = '\0';
                if (sfx != 0) {
                    mp3_voice_play(sfx, 0x7D00, 0x40);
                }
                obj = obj_find_by_setup_id(9);
                if (obj != NULL) {
                    obj->unk232 = kind;
                    g_cur_obj = obj;
                    g_cur_obj_index = ((u8 *) obj - (u8 *) g_objects) / 0x32C;
                    obj->unk218 = (struct216 *) aiscript_find_by_kind(0, obj->unk232);
                    obj->unk21C = 0;
                }
                g_cheat_text_len = 0;
                g_menu_sprite_block[g_cheat_text_len] = '\0';
                ch = 0;
            }
        }
        if (ch > 0) {
            g_menu_sprite_block[g_cheat_text_len] = ch;
            if (g_cheat_text_len < 19) {
                g_cheat_text_len++;
            }
            g_menu_sprite_block[g_cheat_text_len] = '\0';
        }
    }

    /* the wheel */
    mtx_build_rot_trans(mtx, -30.0f, -10.0f, 0.0f, -115.0f, 10.0f, -530.0f);
    mtx_translate_fixed(mtx + 1, 0.0f, 0.0f, -(f32) g_cheat_letter_tilt);
    guPerspective((Mtx *) &g_hud_model_proj_mtx, &persp, 50.0f, 60.6f, 53.0f, 20000.0f, 1.0f);
    gSPPerspNormalize(gdl++, persp);
    gSPMatrix(gdl++, &g_hud_model_proj_mtx, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPClearGeometryMode(gdl++, 0xFFFFFFFF);
    gSPSetGeometryMode(gdl++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gSPMatrix(gdl++, mtx, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    for (off = 0; off < 30 * 12; off += 12) {
        gDPPipeSync(gdl++);
        if (off == sel * 12) {
            gDPSetEnvColor(gdl++, 0xFF, 0x00, 0xFF, g_menu_page_alpha);
            gSPMatrix(gdl++, mtx + 1, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        } else {
            gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, g_menu_page_alpha);
        }
        gSPDisplayList(gdl++, *(Gfx **) (g_menu_sprite_entries + off));
        if (off == sel * 12) {
            gSPMatrix(gdl++, mtx, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        }
    }

    /* the text and its cursor */
    text_set_color(0xFF, 0xB1, 0x1E, g_menu_page_alpha);
    text_measure_string(g_menu_sprite_block, &w, &h, &d);
    x = 75 - (w >> 1);
    if (x < 10) {
        x = 10;
    }
    text_printf_at(x, 180, 0x80, g_menu_sprite_block);
    if ((g_frame_count & 0x1F) >= 10) {
        w = x + w + 2;
        text_set_color(0xFF, 0xFF, 0xFF, 0xFF);
        text_printf_at(w, 180, 0x80, g_str_cheat_cursor);
    }
    return gdl;
}

/* save_screen_frame_draw: draws the save / load screen frame (g_menu_state mode of frontend_menu_draw, padC[0] = selected
 * entry): environment alpha g_menu_alpha, two halves of texture 0x7FB (RGBA16, second half mirrored in S), two pieces of
 * texture 0x887 (RGBA32), then the caption string. The caption id comes from asset table 0x1D (u16 per entry), reloaded
 * only when the entry changes (g_save_caption_entry = entry + 1) and cached in g_save_caption_str (0 = no caption). Returns the DL end. */
extern u8 g_menu_alpha; /* was D_800E0EC4 */
extern u8 g_save_caption_entry; /* was D_800E10B5 */
extern s32 g_save_caption_str; /* was D_800904EC */
s32 asset_load_ptr(s32 *, s32, ...);
void heap_free(void *);
s32 texture_cache_lookup(s32, s32, s32, s32);
u8 *hud_tex_rect_scaled(u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
Gfx *hud_image_draw(Gfx *, void *, s32, s32, s32, s32, f32, s32);
#define SAVE_W(g, a, b) ((g)->words.w0 = (a), (g)->words.w1 = (b), (g)++)

/* was func_151EF3A0 */
Gfx *save_screen_frame_draw(Gfx *gdl, s32 entry) {
    s32 tex;
    u16 *table;
    u32 size;

    gDPPipeSync(gdl++);
    SAVE_W(gdl, 0xFB000000, g_menu_alpha | 0xFFFFFF00); /* SetEnvColor 255, 255, 255, alpha */
    tex = texture_cache_lookup(0x7FB, 0, 3, 0);
    if (tex != (s32) 0x80000000) {
        SAVE_W(gdl, 0xFD100000, tex);        /* SetTImg RGBA16 */
        SAVE_W(gdl, 0xF5100000, 0x07054260); /* SetTile (load) */
        gDPLoadSync(gdl++);
        SAVE_W(gdl, 0xF3000000, 0x075FF000); /* LoadBlock */
        gDPPipeSync(gdl++);
        SAVE_W(gdl, 0xF5101800, 0x00054260); /* SetTile (render) */
        SAVE_W(gdl, 0xF2000000, 0x000BC07C); /* SetTileSize 48x32 */
        gDPSetOtherMode(gdl++, 0x002C3F, 0x504244);
        gdl = (Gfx *) hud_tex_rect_scaled((u8 *) gdl, 0x190, 0x100, 0x250, 0x200, 0, 0, 0, 0x400, 0x400);
        gdl = (Gfx *) hud_tex_rect_scaled((u8 *) gdl, 0x250, 0x100, 0x310, 0x200, 0, 0x5E0, 0, -0x400, 0x400);
    }
    gDPPipeSync(gdl++);
    tex = texture_cache_lookup(0x887, 0, 3, 0);
    if (tex != (s32) 0x80000000) {
        SAVE_W(gdl, 0xFD180000, tex);        /* SetTImg RGBA32 */
        SAVE_W(gdl, 0xF5180000, 0x07094250); /* SetTile (load) */
        gDPLoadSync(gdl++);
        SAVE_W(gdl, 0xF3000000, 0x073FF000); /* LoadBlock */
        gDPPipeSync(gdl++);
        SAVE_W(gdl, 0xF5181000, 0x00094250); /* SetTile (render) */
        SAVE_W(gdl, 0xF2000000, 0x0007C07C); /* SetTileSize 32x32 */
        gdl = (Gfx *) hud_tex_rect_scaled((u8 *) gdl, 0x250, 0xBC, 0x290, 0xFC, 0, 0, 0, 0x400, 0x400);
        gdl = (Gfx *) hud_tex_rect_scaled((u8 *) gdl, 0x180, 0xBC, 0x1D0, 0xFC, 0, 0x200, 0x200, 0x400, 0x400);
    }
    if (entry + 1 != g_save_caption_entry) {
        table = NULL;
        size = asset_load_ptr((s32 *) &table, 1, 0x1D);
        if ((u32) entry < (size >> 1)) {
            g_save_caption_str = table[entry];
        } else {
            g_save_caption_str = 0;
        }
        heap_free(table);
        g_save_caption_entry = entry + 1;
    }
    if (g_save_caption_str != 0) {
        gDPPipeSync(gdl++);
        gdl = hud_image_draw(gdl, &g_save_caption_str, 0x94, 0x60, 1, 2, 1.0f, 0);
    }
    return gdl;
}
#undef SAVE_W
