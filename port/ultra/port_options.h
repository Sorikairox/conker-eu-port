/* P324: options set by the page's Options panel (port/web/index.html + main.js). The page calls
 * port_set_option(id, value) (port/ultra/pc_os.c) at start and whenever a toggle changes; game C reads the value with
 * port_option(id), only inside `#ifdef PORT` blocks, so the N64 builds never see this. Ids are shared with the
 * `game:` field of the OPTIONS list in main.js. Included by port_prefix.h (every game TU) and pc_os.c. */
#ifndef PORT_OPTIONS_H
#define PORT_OPTIONS_H

enum {
    PORT_OPT_CUTSCENE_SKIP = 0, /* cutscenes skippable from the first viewing by holding L for 3 s (P320/P321) */
    PORT_OPT_SKIP_INTRO = 1,    /* boot straight into the title menu (intro_mode_update, P324) */
    PORT_OPT_HEALTH_ALWAYS = 2, /* HUD health pieces stay on screen (hud_health_update, P325) */
    PORT_OPT_CASH_ALWAYS = 3,   /* cash total always on screen, pause-screen digit images (hud_cash_counter_draw, P330) */
    PORT_OPT_LONG_BREATH = 4,   /* air under water lasts twice as long (swim_water_physics, P326) */
    PORT_OPT_LONG_TAILSPIN = 5, /* helicopter tail spin hovers twice as long (obj_jump_swim_glide_update, P326) */
    PORT_OPT_NO_DRUNK_FX = 6,   /* no frame-blend blur, no drunk camera sway (fb_ghost_set_mode, camera_update_shake,
                                 * camera_wobble_apply, P331) */
    PORT_OPT_CONKER_FULL_LOD = 7, /* Conker always drawn with his most detailed model (obj_select_lod, P331) */
    PORT_OPT_AIR_BAR = 8,       /* bar of the air left while under water (hud_air_bar_draw, P332) */
    PORT_OPT_SWIM_INVERT = 12,  /* swim state: stick y flipped, up rises / down dives (player_swim_update, P333) */
    PORT_OPT_RUMBLE = 13,       /* controllers report a Rumble Pak; motor start/stop -> gamepad vibration (pc_pif.c, P333) */
    PORT_OPT_AIM_CROSSHAIR = 14, /* centred crosshair in first-person aim kinds that have no aim HUD (aim_hud_spawn_for_mode, P334) */
    PORT_OPT_FREE_CAMERA = 15,  /* right stick / IJKL / mouse orbit the follow camera (free_camera_update, P347); never online */
    PORT_OPT_PHOTO_MODE = 16,   /* photo mode: freeze, free camera, no HUD, PNG (pc_photo.c, P348); never online */
    PORT_OPT_LEDGE_GRAB = 17,   /* single player: Conker catches any ledge, not only the ones the level marks; Z lets go,
                                 * stick left / right shimmies (collision_ledge_probe, ledge_shimmy_step, P352) */
    /* P332 sliders: the value is a percentage 0..100 (default 100 = N64); game C scales with port_volume_scale */
    PORT_OPT_VOL_MUSIC = 9,     /* sequenced music: __n_vsVol */
    PORT_OPT_VOL_SFX = 10,      /* sound player effects: SND_VOL155 (n_sndp_handle_event) */
    PORT_OPT_VOL_SPEECH = 11,   /* MP3 voice streams: mp3_stream_update_vol_pan / the stream's first envelope */
    PORT_OPT_COUNT = 24
};
int port_option(int id);
/* P332: v * port_option(id) / 100 for the volume sliders; exactly v at 100 % (the default). */
int port_volume_scale(int id, int v);
/* P327 test aids (URL flags, port/ultra/pc_os.c), 0 when the flag is absent so they do nothing unless given:
 * port_warp_level() = ?warp=29 (hex level id), port_warp_scene() = ?warpscene=N (decimal, or 0x..). */
int port_warp_level(void);
int port_warp_scene(void);
void port_set_option(int id, int value);
/* P333: stick y for the swim controls, sign flipped when PORT_OPT_SWIM_INVERT is on, else y unchanged. */
int port_swim_stick_y(int y);
/* P347 free camera (pc_pif.c): the camera input of controller ch taken at the last controller read, while the free
 * camera holds the camera stick: axis 0 / 1 = camera stick x / y (N64 counts -80..80, y > 0 = up), 2 / 3 = mouse
 * movement x / y since the previous read (pixels, y > 0 = down). 0 when the option is off or online.
 * port_free_camera_engage(ch): the game's free camera is in control of player ch's camera this frame, so the next
 * controller reads give the camera stick to it instead of turning it into C buttons. */
int port_free_camera_axis(int ch, int axis);
int port_free_camera_enabled(void);   /* the option is on and no online session runs */
void port_free_camera_engage(int ch);
/* P348 photo mode (pc_photo.c): port_photo_sandbox is 1 while a photo frame's retraces run (the game is frozen; each
 * photo frame starts from the same snapshot and is undone), port_photo_nohud 1 while that frame is built without the
 * HUD. port_photo_camera fills the photo camera (eye, look-at point, roll in degrees, wanted fields of view x / y or 0)
 * and returns 1 inside a photo frame; port_photo_camera_applied: the game wrote it into the view;
 * port_photo_scene_drawn: the game drew player 1's 3D scene this frame (photo mode may start). */
extern int port_photo_sandbox, port_photo_nohud;
int port_photo_camera(float *eye, float *at, float *roll, float *fov);
/* P350 option "Widescreen" (renderer, gfx_f3dex2.c): the commands the game writes from display-list address gdl on belong to
 * a HUD element in a screen corner, anchored to the left (edge 1) or right (2) edge of the wide picture, or again to the
 * centred 4:3 layout (0). Only recorded on the renderer's side (no game memory changes), so the call is harmless online. */
void port_ws_hud_anchor(void *gdl, int edge);
void port_photo_camera_applied(void);
void port_photo_scene_drawn(void);

/* P363 native menus: a CUSTOMISATION SETTINGS row (P369; was "OPTIONS") in the game's own pause menu (game_pause_update)
 * that opens the page's game-style menu, the customisation settings (port/web/gmenu.js). The page turns the row on with
 * port_set_gmenu_row(1) only when the game is local (P369: always then; the option "Game-style menu" is gone) (no online session, recording, replay or ?netdet: the pause menu's
 * state is hashed there); port_gmenu_row_shown() also says 0 whenever an online / recorded session or netdet runs.
 * Choosing the row calls port_gmenu_request_open(); the page takes the request with port_gmenu_take_request(). */
int port_gmenu_row_shown(void);
void port_gmenu_request_open(void);
/* P364: the same row on the title menu's save slot pages and MULTI mode pages; the request reads 2 instead of 1. */
void port_gmenu_request_title(void);

#endif
