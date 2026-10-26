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
    PORT_OPT_CASH_ALWAYS = 3,   /* cash total always on screen (hud_cash_always_draw, P325) */
    PORT_OPT_LONG_BREATH = 4,   /* air under water lasts twice as long (swim_water_physics, P326) */
    PORT_OPT_LONG_TAILSPIN = 5, /* helicopter tail spin hovers twice as long (obj_jump_swim_glide_update, P326) */
    PORT_OPT_COUNT = 16
};
int port_option(int id);
void port_set_option(int id, int value);

#endif
