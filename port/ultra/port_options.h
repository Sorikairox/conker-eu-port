/* P324: options set by the page's Options panel (port/web/index.html + main.js). The page calls
 * port_set_option(id, value) (port/ultra/pc_os.c) at start and whenever a toggle changes; game C reads the value with
 * port_option(id), only inside `#ifdef PORT` blocks, so the N64 builds never see this. Ids are shared with the
 * `game:` field of the OPTIONS list in main.js. Included by port_prefix.h (every game TU) and pc_os.c. */
#ifndef PORT_OPTIONS_H
#define PORT_OPTIONS_H

enum {
    PORT_OPT_CUTSCENE_SKIP = 0, /* cutscenes skippable from the first viewing by holding L for 3 s (P320/P321) */
    PORT_OPT_COUNT = 16
};
int port_option(int id);
void port_set_option(int id, int value);

#endif
