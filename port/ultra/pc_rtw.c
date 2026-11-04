/* P376 retrowser.app build (make -C port rtw, tools/eu_port/build_rtw.sh; never linked into port/build/web).
 * The module interface of the retrowser v1 standard (~/Code/retrowser spec/retrowser-v1.md §4-5): the host runs this
 * module in a dedicated Web Worker with no DOM, no network and no AudioContext, and talks to it only through these
 * rtw_* exports and the env.rtw_* imports (port/web/rtw/rtw_lib.js forwards them to the host's Module.rtw).
 *
 *   rtw_rom_buffer(size)        a malloc'ed buffer for the ROM (.z64 order); it becomes port_rom (port_set_rom)
 *   rtw_save_ptr/size/generation, rtw_save_load   the 2048-byte EEPROM image exactly as the cartridge holds it
 *                               (pc_pif.c eeprom[]); the generation counts the writes the page used to persist
 *   rtw_start()                 the worker glue's start (conker_netx.txt exclusions, recorder, input tick), then main():
 *                               boot, then the Emscripten main loop (pc_sched.c frame) runs on the worker's rAF
 *   rtw_pause(on)               port_set_paused (+ rumble off)
 *   rtw_input(port, buttons, sx, sy), rtw_mouse(dx, dy, buttons)   raw host input; the glue's tick (rtw_glue.js, the
 *                               worker twin of main.js pollInput) turns it into the PIF pads / camera stick / photo camera
 *   rtw_rstick(port, rx, ry)    P378 (standard 1.1) the right analog stick, raw too (the glue's camera stick)
 *   rtw_wheel(dy)               P378 (standard 1.1) the mouse wheel, raw too (photo mode's zoom, menu rows)
 *   rtw_resize(w, h, dpr)       the view size; the glue sizes the OffscreenCanvas like main.js layoutScreen
 *   rtw_audio_rate/drain/buffer the game's 22020 Hz stereo s16, pulled once per display frame (aud_out.c)
 *   rtw_option(id, value)       game options (PORT_OPT_* ids, as main.js port_set_option) and page-side options (ids
 *                               >= RTW_PAGE_OPT_BASE: renderer switches, input toggles, the recorder), see retrowser.json
 * Everything here is port-only state: port/tools/net_regions.py leaves pc_rtw.o out of the state hash and the photo
 * mode snapshot (like pc_photo.o). */
#include <emscripten.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "pc_ultra.h"
#include "port_options.h"

/* host imports (spec §4.10), JS in port/web/rtw/rtw_lib.js */
int rtw_log(const char *text, int len);
int rtw_build_id(uint8_t *out32);
int rtw_export_file(const char *name, const char *mime, const void *bytes, int len);
int rtw_rumble(int port, int on);
int rtw_pointer_lock(int on);
/* worker glue hooks (port/web/rtw/rtw_lib.js -> rtw_glue.js) */
void port_rtw_glue_start(void);
void port_rtw_glue_option(int id, int value);
void port_rtw_glue_resize(int width, int height, int dpr100);
void port_rtw_glue_pause(int on);

void port_set_rom(unsigned char *p, unsigned size);
void port_set_paused(int p);
void port_set_option(int id, int value);
unsigned char *port_eeprom_ptr(void);
int port_eeprom_size(void);
int __main_void(void);   /* boot/game_main.c main(void) as clang names it for wasm (a main(argc, argv) reference would be __main_argc_argv) */
int port_rtw_audio_rate(void);           /* aud_out.c (PORT_RTW) */
int port_rtw_audio_drain(void);
int16_t *port_rtw_audio_buffer(void);

#define RTW_PAGE_OPT_BASE 100

/* Raw host input, read by the glue tick through port_rtw_raw_state() (HEAP32):
 *   [0..15]  per port: calls (rtw_input calls so far, so the glue sees which ports the host still sends), buttons, sx, sy
 *   [16..18] mouse dx, dy (summed since the glue last took them), buttons
 *   [20..27] P378 (standard 1.1) per port: the right analog stick rx, ry (-127..127, up positive; rtw_rstick)
 *   [28]     P378 (standard 1.1) the mouse wheel, 1/100 notch, positive towards the player (summed until the glue takes it) */
enum { RTW_RAW_MOUSE = 16, RTW_RAW_RSTICK = 20, RTW_RAW_WHEEL = 28, RTW_RAW_WORDS = 32 };
static int32_t rtw_raw_input[RTW_RAW_WORDS];
EMSCRIPTEN_KEEPALIVE int32_t *port_rtw_raw_state(void) { return rtw_raw_input; }

static unsigned rtw_save_generation_count;   /* EEPROM blocks the game wrote (pc_pif.c calls port_rtw_eeprom_written) */
void port_rtw_eeprom_written(void) { rtw_save_generation_count++; }

static int rtw_game_options_locked;           /* the recorder fixed the game options for its run (main.js optionsLocked) */
EMSCRIPTEN_KEEPALIVE void port_rtw_lock_game_options(void) { rtw_game_options_locked = 1; }

static uint8_t rtw_rumble_on[4];
/* pc_pif.c (PORT_RTW): a controller's Rumble Pak motor started / stopped */
void port_rtw_rumble(int channel, int on) {
    if (channel < 0 || channel > 3) return;
    rtw_rumble_on[channel] = on != 0;
    rtw_rumble(channel, on != 0);
}

/* port_log lines go to stdout (the host's print); this one is for the glue's own messages */
EMSCRIPTEN_KEEPALIVE void port_rtw_log(const char *text) { rtw_log(text, (int)strlen(text)); }
/* the glue's way to the other host imports, so every one of them is a real env.rtw_* import of conker.wasm:
 * photos (photo mode's A / Save) and input recordings go to the host's "Saved files" */
EMSCRIPTEN_KEEPALIVE int port_rtw_export_file(const char *name, const char *mime, const void *bytes, int len) {
    return rtw_export_file(name, mime, bytes, len);
}
/* the 32-byte build id (SHA-256 of retrowser.json), written into recordings */
EMSCRIPTEN_KEEPALIVE int port_rtw_build_id(uint8_t *out32) { return rtw_build_id(out32); }
/* free camera / photo mode want the mouse (main.js requested pointer lock on a click on the canvas) */
EMSCRIPTEN_KEEPALIVE int port_rtw_set_pointer_lock(int on) { return rtw_pointer_lock(on != 0); }

EMSCRIPTEN_KEEPALIVE int rtw_rom_buffer(int size) {
    if (size <= 0) return 0;
    unsigned char *rom = malloc((size_t)size);
    if (!rom) return 0;
    port_set_rom(rom, (unsigned)size);   /* the host copies the bytes in before rtw_start; port_set_rom only keeps the pointer */
    return (int)(uintptr_t)rom;
}

/* the recorder's header holds the ROM's SHA-1 (main.js romSha1), computed by the glue from these */
extern unsigned char *port_rom;   /* pc_os.c */
extern unsigned port_rom_size;
EMSCRIPTEN_KEEPALIVE int port_rtw_rom_ptr(void) { return (int)(uintptr_t)port_rom; }
EMSCRIPTEN_KEEPALIVE int port_rtw_rom_size(void) { return (int)port_rom_size; }

EMSCRIPTEN_KEEPALIVE int rtw_save_ptr(void) { return (int)(uintptr_t)port_eeprom_ptr(); }
EMSCRIPTEN_KEEPALIVE int rtw_save_size(void) { return port_eeprom_size(); }
EMSCRIPTEN_KEEPALIVE int rtw_save_generation(void) { return (int)rtw_save_generation_count; }
/* the host has copied `size` bytes of the stored image to `ptr` (normally rtw_save_ptr() itself) */
EMSCRIPTEN_KEEPALIVE int rtw_save_load(int ptr, int size) {
    unsigned char *eeprom = port_eeprom_ptr();
    int n = size < port_eeprom_size() ? size : port_eeprom_size();
    if (n < 0) n = 0;
    if ((unsigned char *)(uintptr_t)ptr != eeprom && ptr) memmove(eeprom, (void *)(uintptr_t)ptr, (size_t)n);
    port_log("[rtw] save: %d bytes of EEPROM from the host\n", n);
    return 0;
}

EMSCRIPTEN_KEEPALIVE int rtw_start(void) {
    static int started;
    if (started) return 0;
    started = 1;
    port_rtw_glue_start();
    __main_void();   /* main(): boots and starts the main loop (pc_sched.c port_run); returns, the loop runs on the worker's timers */
    return 0;
}

EMSCRIPTEN_KEEPALIVE int rtw_pause(int on) {
    port_set_paused(on != 0);
    if (on)
        for (int ch = 0; ch < 4; ch++)
            if (rtw_rumble_on[ch]) rtw_rumble(ch, 0);   /* main.js applyPause: no vibration while paused */
    port_rtw_glue_pause(on != 0);
    return 0;
}

EMSCRIPTEN_KEEPALIVE int rtw_input(int port, int buttons, int stick_x, int stick_y) {
    if (port < 0 || port > 3) return 0;
    rtw_raw_input[port * 4]++;
    rtw_raw_input[port * 4 + 1] = buttons;
    rtw_raw_input[port * 4 + 2] = stick_x;
    rtw_raw_input[port * 4 + 3] = stick_y;
    return 0;
}

/* P378 standard 1.1 (spec §4.11): the right analog stick, called by the host right after rtw_input for each port. The
 * glue's tick turns it into the camera stick the way main.js gamepadPad does (option 113; the host also still sets the
 * C buttons from it) */
EMSCRIPTEN_KEEPALIVE int rtw_rstick(int port, int rx, int ry) {
    if (port < 0 || port > 3) return 0;
    rtw_raw_input[RTW_RAW_RSTICK + port * 2] = rx;
    rtw_raw_input[RTW_RAW_RSTICK + port * 2 + 1] = ry;
    return 0;
}

EMSCRIPTEN_KEEPALIVE int rtw_mouse(int dx, int dy, int buttons) {
    rtw_raw_input[RTW_RAW_MOUSE] += dx;
    rtw_raw_input[RTW_RAW_MOUSE + 1] += dy;
    rtw_raw_input[RTW_RAW_MOUSE + 2] = buttons;
    return 0;
}

/* P378 standard 1.1 (spec §4.11): the mouse wheel over the picture (hundredths of a notch since the last call; never
 * while paused). The glue's tick: photo mode's zoom as main.js (canvas wheel), the customisation settings' rows (option 114) */
EMSCRIPTEN_KEEPALIVE int rtw_wheel(int dy) {
    rtw_raw_input[RTW_RAW_WHEEL] += dy;
    return 0;
}

EMSCRIPTEN_KEEPALIVE int rtw_resize(int width, int height, int dpr100) {
    port_rtw_glue_resize(width, height, dpr100);
    return 0;
}

EMSCRIPTEN_KEEPALIVE int rtw_audio_rate(void) { return port_rtw_audio_rate(); }
EMSCRIPTEN_KEEPALIVE int rtw_audio_drain(void) { return port_rtw_audio_drain(); }
EMSCRIPTEN_KEEPALIVE int rtw_audio_buffer(void) { return (int)(uintptr_t)port_rtw_audio_buffer(); }

EMSCRIPTEN_KEEPALIVE int rtw_option(int id, int value) {
    if (id >= 0 && id < PORT_OPT_COUNT && !rtw_game_options_locked) port_set_option(id, value);
    port_rtw_glue_option(id, value);   /* the glue keeps every value (photo mode, free camera and the page-side ones act there) */
    return 0;
}
