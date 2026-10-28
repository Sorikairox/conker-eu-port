/* PIF model: controllers and the 16 Kbit EEPROM (P19, moved here and extended in P27).
 *
 * Two ways into it, both through the same command interpreter pif_run():
 *  - the game's own libultra SI code (EEPROM probe/read/write in game_eu_20B220.c etc., pak writes)
 *    writes SI_DRAM_ADDR and then SI_PIF_ADDR_WR64B / RD64B; pc_os.c __port_io_write calls
 *    port_pif_dma(), which copies the 64-byte block, runs it and posts OS_EVENT_SI;
 *  - the PC osContStartReadData packs the libultra controller-read block (cmd 0x01 on channels 0-3)
 *    into PIF RAM and runs it; osContGetReadData unpacks the replies like libultra's
 *    __osContGetReadData (button, stick, errno = CHNL_ERR). The game's per-frame read cont_read_frame
 *    (game_eu_49310.c, C) calls both.
 *
 * Input comes from the page (port/web/main.js): it writes port_pads[] in the wasm heap directly
 * (pointer from port_pad_state()), so no wasm call happens from input or rAF callbacks. In node the
 * pads stay idle unless node_run.js writes them (PADTEST).
 *
 * EEPROM: eeprom[] holds the 2048 bytes as the cartridge stores them. The page loads a saved image
 * before callMain (port_eeprom_ptr) and is told about every write that changed it
 * (Module.portEepDirty, debounced into IndexedDB by main.js). */
#include <emscripten.h>
#include <stdint.h>
#include <string.h>
#include "pc_ultra.h"
#include "pc_mem.h"
#include <PR/os_cont.h>
#include <PR/os_message.h>
#include "port_options.h"

void port_log(const char *fmt, ...);
int port_flag(const char *name);
int port_flag_hex(const char *name);
void *port_n64_to_wasm(unsigned n64addr);

/* ---- input state written by the page: per pad {present, buttons (N64 bits), stick_x, stick_y} */
static int32_t port_pads[MAXCONTROLLERS][4] = { { 1, 0, 0, 0 } };
EMSCRIPTEN_KEEPALIVE int32_t *port_pad_state(void) { return &port_pads[0][0]; }
/* P321: pad 0 buttons as last delivered to the game (the game's own copy is edge-triggered; port_skip_hold needs
 * "held"). Taken at the controller read, after ?padf, since the page rewrites port_pads every animation frame. */
static u32 pad0_delivered;
int port_pad0_held(void) { return (int)pad0_delivered; }

/* ---- P347 option "Free camera" (PORT_OPT_FREE_CAMERA). With the option on, the page sends the camera stick (gamepad
 * right stick, or the IJKL keys as full deflection) here as an analog value instead of turning it into the four C
 * buttons, plus the mouse movement under pointer lock (summed until the next controller read). At each controller
 * read (osContStartReadData) this becomes what the game sees:
 *  - while the game's free camera holds the player's camera (port_free_camera_engage, refreshed every camera frame by
 *    free_camera_update in game_eu_1501C0.c: single player, normal follow camera, no cutscene / aim / look / swim / ride
 *    ...), the stick and mouse go to the camera (port_free_camera_axis) and give no C buttons;
 *  - anywhere else (menus, cutscenes, aim and look views, swimming, vehicles, multiplayer) the stick is the C buttons,
 *    as the page made them with the option off (|axis| >= 40 counts = half deflection). A stick that is still deflected
 *    when the free camera lets go gives no C button until it has been back in the centre (so an orbit held into a
 *    cutscene does not turn into C presses).
 * Off (the default) and in online sessions the page sends C bits as before and nothing here changes the pads.
 * ?padf entries may carry the camera stick as F:BTN:X:Y:RX:RY. */
static int32_t port_cam_pads[MAXCONTROLLERS][4];   /* page: camera stick x, y (N64 counts, y up), mouse dx, dy (summed) */
EMSCRIPTEN_KEEPALIVE int32_t *port_cam_state(void) { return &port_cam_pads[0][0]; }
static int cam_delivered[MAXCONTROLLERS][4];      /* what port_free_camera_axis answers until the next read */
static int cam_engaged_ttl[MAXCONTROLLERS];       /* controller reads the free camera still holds the stick */
static u8 cam_stick_wait_centre[MAXCONTROLLERS];  /* stick held over the end of the free camera: no C buttons yet */
int port_free_camera_axis(int ch, int axis) { return ch >= 0 && ch < MAXCONTROLLERS && axis >= 0 && axis < 4 ? cam_delivered[ch][axis] : 0; }
void port_free_camera_engage(int ch) { if (ch >= 0 && ch < MAXCONTROLLERS) cam_engaged_ttl[ch] = 2; }
extern unsigned port_frame_count;
int port_free_camera_enabled(void) { extern int port_net_on; return port_option(PORT_OPT_FREE_CAMERA) && !port_net_on; }
/* test aid ?freecamlog=N: every Nth free camera frame, the yaw / pitch / horizontal distance / eye height it ended with */
void port_free_camera_log(int ch, int engaged, float yaw, float pitch, float dist, float height) {
    static int every = -1; static unsigned n;
    if (every < 0) every = port_flag("freecamlog");
    if (every > 0 && n++ % (unsigned)every == 0)
        port_log("[freecam] retrace %u pad %d %s yaw %.1f pitch %+.1f dist %.0f height %.0f stick %d,%d mouse %d,%d\n", port_frame_count, ch + 1,
                 engaged ? "free" : "game", yaw, pitch, dist, height, cam_delivered[ch & 3][0], cam_delivered[ch & 3][1], cam_delivered[ch & 3][2], cam_delivered[ch & 3][3]);
}
/* ?freecamlog: who holds the camera when it changes (free_camera_allowed's reason: 0 = the free camera) */
void port_free_camera_note(int ch, int reason) {
    static const char *why[] = { "free camera", "option off / online", "multiplayer", "cutscene", "paused / snap",
                                 "not the follow camera", "look / aim view", "swimming", "riding / vehicle", "scripted camera" };
    static int every = -1, last[MAXCONTROLLERS] = { -1, -1, -1, -1 };
    if (every < 0) every = port_flag("freecamlog");
    ch &= 3;
    if (every > 0 && reason != last[ch])
        port_log("[freecam] retrace %u pad %d: %s\n", port_frame_count, ch + 1, reason >= 0 && reason < 10 ? why[reason] : "?");
    last[ch] = reason;
}
static void free_camera_pads(void) {
    int on = port_free_camera_enabled();
    for (int ch = 0; ch < MAXCONTROLLERS; ch++) {
        int x = port_cam_pads[ch][0], y = port_cam_pads[ch][1], mx = port_cam_pads[ch][2], my = port_cam_pads[ch][3];
        port_cam_pads[ch][2] = port_cam_pads[ch][3] = 0;   /* the mouse movement is used once */
        memset(cam_delivered[ch], 0, sizeof cam_delivered[ch]);
        if (!on) { cam_engaged_ttl[ch] = 0; cam_stick_wait_centre[ch] = 0; continue; }
        int moved = x <= -40 || x >= 40 || y <= -40 || y >= 40;
        if (cam_engaged_ttl[ch] > 0) {
            cam_engaged_ttl[ch]--;
            cam_delivered[ch][0] = x; cam_delivered[ch][1] = y; cam_delivered[ch][2] = mx; cam_delivered[ch][3] = my;
            cam_stick_wait_centre[ch] = moved;
            continue;
        }
        if (cam_stick_wait_centre[ch] && moved) continue;
        cam_stick_wait_centre[ch] = 0;
        int c = (x >= 40 ? 0x0001 : 0) | (x <= -40 ? 0x0002 : 0) | (y <= -40 ? 0x0004 : 0) | (y >= 40 ? 0x0008 : 0);
        port_pads[ch][1] |= c;   /* CR CL CD CU, as main.js's gamepadPad makes them with the option off */
    }
}

/* ---- P149: frame-based pad script for test runs (50 Hz retraces made wall-clock scripts drift).
 * ?padf=F:BTN:X:Y,F:BTN:X:Y,...  (node: PORT_PADF=...): from VI retrace F (port_frame_count) on, pad 0 reports
 * buttons BTN (hex N64 bits: START 1000, A 8000, B 4000, Z 2000) and stick X / Y (decimal, y > 0 = up) instead of the
 * page's keyboard / gamepad state; before the first entry the page state is used. Entries in frame order.
 * P337: ?padf1= / ?padf2= / ?padf3= (node PORT_PADF1..3) script controllers 2..4 the same way (each channel that has a
 * script is reported present from its first entry on), and ?padmask=HEX fixes which controllers are plugged in at
 * boot (bit i = channel i; osContInit and every read). Under forced online determinism (pc_net.c ?netdet) the page
 * writes no pad state at all, so a channel without a script reads neutral input, and the mask defaults to 1 (pad 1). */
extern unsigned port_frame_count;
int port_net_det(void);
extern int port_net_on;                       /* P338 pc_net.c: an online (lockstep) session runs */
void port_net_fill_pads(int32_t *pads);       /* P338 pc_net.c: buttons / sticks of this retrace from the input ring */
EM_JS(int, __port_padf_char, (int ch, int i), {
    var v = null, k = ch ? 'padf' + ch : 'padf';
    if (typeof location !== 'undefined') { var m = new RegExp('[?&]' + k + '=([^&]*)').exec(location.search); if (m) v = decodeURIComponent(m[1]); }
    else if (typeof process !== 'undefined' && process.env && process.env['PORT_' + k.toUpperCase()] !== undefined) v = process.env['PORT_' + k.toUpperCase()];
    return v === null || i >= v.length ? 0 : v.charCodeAt(i);
});
#define PADF_MAX 16384 /* P154: 128 -> 2048 (long new-game scripts); P228: 16384 (human recordings, ?padrec); P337: all 4 channels */
static struct { unsigned f; int b, x, y, rx, ry; } padf[PADF_MAX];   /* P347: rx / ry = camera stick (free camera) */
static int padf_n = -1;                                  /* entries of all channels; -1 = not parsed yet */
static int padf_first[MAXCONTROLLERS], padf_end[MAXCONTROLLERS], padf_cur[MAXCONTROLLERS]; /* per channel: [first, end), current */
static char padf_text[524288];                           /* P228: 64K -> 512K; was padf_apply's local s */
static void padf_parse_channel(int ch) {
    int len = 0, c;
    while (len < (int)sizeof padf_text - 1 && (c = __port_padf_char(ch, len)) != 0) padf_text[len++] = (char)c;
    padf_text[len] = 0;
    padf_first[ch] = padf_n; padf_cur[ch] = -1;
    for (char *p = padf_text; *p && padf_n < PADF_MAX;) {
        unsigned f = 0; int b = 0, x = 0, y = 0, neg;
        while (*p >= '0' && *p <= '9') f = f * 10 + (unsigned)(*p++ - '0');
        if (*p == ':' && (p[1] == 'P' || p[1] == 'p')) { b = -1; p += 2; }   /* P228: F:P = hand back to the page */
        else if (*p == ':') { p++; while ((c = *p) && c != ':' && c != ',') { b = b * 16 + (c <= '9' ? c - '0' : (c | 0x20) - 'a' + 10); p++; } }
        if (*p == ':') { p++; neg = *p == '-'; if (neg) p++; while (*p >= '0' && *p <= '9') x = x * 10 + (*p++ - '0'); if (neg) x = -x; }
        if (*p == ':') { p++; neg = *p == '-'; if (neg) p++; while (*p >= '0' && *p <= '9') y = y * 10 + (*p++ - '0'); if (neg) y = -y; }
        int rx = 0, ry = 0;   /* P347: optional F:BTN:X:Y:RX:RY = the camera stick (right stick) for the free camera */
        if (*p == ':') { p++; neg = *p == '-'; if (neg) p++; while (*p >= '0' && *p <= '9') rx = rx * 10 + (*p++ - '0'); if (neg) rx = -rx; }
        if (*p == ':') { p++; neg = *p == '-'; if (neg) p++; while (*p >= '0' && *p <= '9') ry = ry * 10 + (*p++ - '0'); if (neg) ry = -ry; }
        padf[padf_n].f = f; padf[padf_n].b = b; padf[padf_n].x = x; padf[padf_n].y = y; padf[padf_n].rx = rx; padf[padf_n].ry = ry; padf_n++;
        while (*p && *p != ',') p++;
        if (*p == ',') p++;
    }
    padf_end[ch] = padf_n;
    if (padf_end[ch] > padf_first[ch])
        port_log("[padf] pad %d: %d entries, first at retrace %u\n", ch + 1, padf_end[ch] - padf_first[ch], padf[padf_first[ch]].f);
}
/* P337 ?padmask: -1 = not given (presence comes from the page) */
static int pad_mask = -2;
static int padmask_get(void) {
    if (pad_mask == -2) {
        int v = port_flag_hex("padmask");
        pad_mask = v > 0 ? v & 0xF : port_net_det() ? 1 : -1;
        if (pad_mask >= 0) port_log("[padf] controller presence mask %X\n", pad_mask);
    }
    return pad_mask;
}
static void pads_apply_mask(void) {
    int m = padmask_get();
    if (m >= 0) for (int ch = 0; ch < MAXCONTROLLERS; ch++) port_pads[ch][0] = (m >> ch) & 1;
}
static void padf_parse_all(void) {
    if (padf_n < 0) { padf_n = 0; for (int ch = 0; ch < MAXCONTROLLERS; ch++) padf_parse_channel(ch); }
}
/* P338: random access into a channel's ?padf script for the online session (pc_net.c): the input that ?padf would
 * deliver at retrace `frame` (neutral before the first entry and for an F:P entry). Used as the local input source of a
 * test session (?netscript) and by the page's loopback peer. */
void port_padf_value(int ch, unsigned frame, int *buttons, int *stick_x, int *stick_y) {
    padf_parse_all();
    *buttons = *stick_x = *stick_y = 0;
    for (int k = padf_first[ch]; k < padf_end[ch] && padf[k].f <= frame; k++)
        if (padf[k].b == -1) *buttons = *stick_x = *stick_y = 0;
        else { *buttons = padf[k].b; *stick_x = padf[k].x; *stick_y = padf[k].y; }
}
/* P338: the online session's presence mask (pc_net.c port_net_session, before callMain) */
void port_pads_set_mask(int mask) { pad_mask = mask & 0xF; port_log("[padf] controller presence mask %X (online session)\n", pad_mask); }
static void padf_apply(void) {
    padf_parse_all();
    pads_apply_mask();
    for (int ch = 0; ch < MAXCONTROLLERS; ch++) {
        if (padf_end[ch] == padf_first[ch]) continue;
        int k = padf_cur[ch] < 0 ? padf_first[ch] - 1 : padf_cur[ch];
        while (k >= padf_first[ch] && padf[k].f > port_frame_count) k--;   /* P348: photo frames ran retraces that were undone */
        while (k + 1 < padf_end[ch] && padf[k + 1].f <= port_frame_count) k++;
        if (k < padf_first[ch]) continue;
        if (k != padf_cur[ch]) { padf_cur[ch] = k; port_log("[padf] retrace %u: %sbuttons %X stick %d,%d%s\n", port_frame_count, ch ? (ch == 1 ? "pad 2 " : ch == 2 ? "pad 3 " : "pad 4 ") : "", padf[k].b, padf[k].x, padf[k].y, padf[k].rx || padf[k].ry ? " + camera stick" : ""); if (padf[k].rx || padf[k].ry) port_log("[padf]   camera stick %d,%d\n", padf[k].rx, padf[k].ry); }
        /* P228 F:P entry: keyboard / gamepad from here on (record with ?padrec=1). Once a P entry has been reached the
         * ?p205goto autopilot is off for good, so a replay (prefix, F:P, then the recorded entries) is not disturbed by
         * the autopilot's after-arrival taps. */
        static int handed;
        if (padf[k].b == -1) { if (!ch) handed = 1; continue; }
        if (pad_mask < 0) port_pads[ch][0] = 1;   /* a scripted pad is plugged in, unless ?padmask says otherwise */
        port_pads[ch][1] = padf[k].b; port_pads[ch][2] = padf[k].x; port_pads[ch][3] = padf[k].y;
        port_cam_pads[ch][0] = padf[k].rx; port_cam_pads[ch][1] = padf[k].ry;   /* P347 camera stick */
        if (!ch && !handed) { extern void p205_goto_apply(int *, int *, int *); p205_goto_apply(&port_pads[0][1], &port_pads[0][2], &port_pads[0][3]); } /* P205 TEST ?p205goto */
    }
}

/* ---- P228: ?padrec=1 logs every change of pad 0 (after ?padf, i.e. what the game reads) as
 * "[padrec] F:BTN:X:Y" in ?padf syntax. A human route played in Chrome (keyboard / gamepad) becomes a frame
 * script: join the [padrec] fields with commas. Use with a ?padf prefix that ends in an F:P entry (page input from
 * retrace F on) to record only the part after a scripted start. The page also collects them in window.__padrec
 * (DevTools console: copy(__padrec.join(',')) puts the whole script on the clipboard). */
EM_JS(void, __port_padrec_push, (unsigned f, unsigned b, int x, int y), {
    var g = typeof window !== 'undefined' ? window : globalThis;   /* DevTools: copy(__padrec.join(',')) */
    (g.__padrec = g.__padrec || []).push(f + ':' + b.toString(16).toUpperCase() + ':' + x + ':' + y);
});
static void padrec_log(void) {
    static int on = -1; static int32_t lb = 0, lx = 0, ly = 0;
    if (on < 0) on = port_flag("padrec") > 0;
    if (!on) return;
    if (port_pads[0][1] == lb && port_pads[0][2] == lx && port_pads[0][3] == ly) return;
    lb = port_pads[0][1]; lx = port_pads[0][2]; ly = port_pads[0][3];
    port_log("[padrec] %u:%X:%d:%d\n", port_frame_count, (unsigned)lb & 0xFFFF, (int)lx, (int)ly);
    __port_padrec_push(port_frame_count, (unsigned)lb & 0xFFFF, (int)lx, (int)ly);
}

/* ---- EEPROM */
#define EEP_SIZE 2048
static u8 eeprom[EEP_SIZE];
static unsigned eep_writes;
EMSCRIPTEN_KEEPALIVE u8 *port_eeprom_ptr(void) { return eeprom; }
EMSCRIPTEN_KEEPALIVE int port_eeprom_size(void) { return EEP_SIZE; }
EM_JS(void, __port_eep_dirty, (void), { if (typeof Module !== 'undefined' && Module.portEepDirty) Module.portEepDirty(); });

/* ---- P333 option "Rumble" (PORT_OPT_RUMBLE): a Rumble Pak in every connected controller.
 * libultra talks to a pak with two PIF commands on the controller's channel: 0x02 read 32 bytes (tx 3: cmd + address
 * word, rx 33: data + data CRC) and 0x03 write 32 bytes (tx 35: cmd + address + data, rx 1: data CRC). The address
 * word is (address >> 5) << 5 | address CRC, i.e. the game's block number in the top 11 bits. A Rumble Pak answers:
 *   block 0x400 (bytes 0x8000..): the probe. os_motor_init writes 32 x 0x80 and reads back; the last byte must be 0x80.
 *   block 0x600 (bytes 0xC000..): the motor. os_motor_start writes 32 x 0x01 (expects data CRC 0xEB), os_motor_stop
 *   32 x 0x00 (CRC 0).
 * Option off (the default): pak commands get no response, exactly as before (no pak, g_rumble_pak_present stays 0).
 * Option on: those two blocks answer as above; every other pak address still gets no response, so the Controller
 * Pak code and the EEPROM saves (channel 4) see what they always saw. Motor changes go to the page
 * (Module.portRumble(channel, on)), which drives the gamepad's vibration. P335: rumble_update re-probes when the
 * option changes, so a toggle takes effect at once (not at the next level load). */
EM_JS(void, __port_rumble, (int ch, int on), { if (typeof Module !== 'undefined' && Module.portRumble) Module.portRumble(ch, on); });
static u8 rumble_probe[MAXCONTROLLERS];   /* last byte written to the probe block (0x80 = rumble pak selected) */
static u8 rumble_motor[MAXCONTROLLERS];
static unsigned rumble_events;
/* libultra __osContDataCrc: CRC-8 (poly 0x85) of the 32 data bytes plus 8 zero bits */
static u8 pak_data_crc(const u8 *d) {
    u8 t = 0;
    for (int i = 0; i <= 32; i++)
        for (int j = 7; j >= 0; j--) {
            u8 x = (t & 0x80) ? 0x85 : 0;
            t = (u8)(t << 1) | (i < 32 && (d[i] >> j & 1));
            t ^= x;
        }
    return t;
}
/* 1 = handled (reply written), 0 = no pak there */
static int rumble_pak_cmd(int ch, const u8 *c, int tx, u8 *r, int rx) {
    if (!port_option(PORT_OPT_RUMBLE)) {   /* P335: option off = no pak; forget the probe / motor state for the next "on" */
        rumble_probe[ch] = 0; rumble_motor[ch] = 0;
        return 0;
    }
    unsigned block = ((unsigned)c[1] << 8 | c[2]) >> 5;
    if (c[0] == 0x03 && tx >= 35 && rx >= 1) {
        if (block >= 0x400 && block < 0x600) rumble_probe[ch] = c[34];
        else if (block >= 0x600 && block < 0x800) {
            u8 on = c[34] != 0;
            if (on != rumble_motor[ch]) {
                rumble_motor[ch] = on;
                if (rumble_events++ < 400) port_log("[rumble] frame %u ch %d motor %s\n", port_frame_count, ch, on ? "start" : "stop");
                if (!port_photo_sandbox) __port_rumble(ch, on);   /* P348: not from a photo frame (undone afterwards) */
            }
        } else return 0;
        r[0] = pak_data_crc(&c[3]);
        return 1;
    }
    if (c[0] == 0x02 && tx >= 3 && rx >= 33) {
        if (block >= 0x400 && block < 0x600) memset(r, rumble_probe[ch] == 0x80 ? 0x80 : 0x00, 32);
        else if (block >= 0x600 && block < 0x800) memset(r, 0, 32);
        else return 0;
        r[32] = pak_data_crc(r);
        return 1;
    }
    return 0;
}

/* ---- PIF RAM and the command interpreter */
static u8 pif_ram[64];
static void pif_run(void) {
    int ch = 0, i = 0;
    static int nlog;
    while (i < 63) {
        u8 t = pif_ram[i];
        if (t == 0xFE) break;
        if (t == 0xFF || t == 0xFD) { i++; continue; }
        if (t == 0) { ch++; i++; continue; }
        if (i + 1 >= 63) break;
        int tx = t & 0x3F, rx = pif_ram[i + 1] & 0x3F;
        u8 *c = &pif_ram[i + 2], *r = &pif_ram[i + 2 + tx];
        if (i + 2 + tx + rx > 64) break;
        int ok = 1;
        if (c[0] != 0x01 && nlog++ < 6) port_log("[pif] ch %d cmd %02X tx %d rx %d\n", ch, c[0], tx, rx);
        if (ch < MAXCONTROLLERS && port_pads[ch][0]) {   /* standard controller, no pak */
            if (c[0] == 0x00 || c[0] == 0xFF) { if (rx >= 3) { r[0] = 0x05; r[1] = 0x00; r[2] = 0x02; } }
            else if (c[0] == 0x01 && rx >= 4) {
                u32 b = (u32)port_pads[ch][1];
                r[0] = (u8)(b >> 8); r[1] = (u8)b;
                if (ch == 0) pad0_delivered = b;
                r[2] = (u8)(s8)port_pads[ch][2]; r[3] = (u8)(s8)port_pads[ch][3];
            }
            else ok = rumble_pak_cmd(ch, c, tx, r, rx);  /* pak commands: no pak, or the P333 Rumble Pak */
        } else if (ch == 4) {                           /* EEPROM 16K */
            if (c[0] == 0x00 || c[0] == 0xFF) { if (rx >= 3) { r[0] = 0x00; r[1] = 0xC0; r[2] = 0x00; } }
            else if (c[0] == 0x04 && tx >= 2) memcpy(r, &eeprom[(c[1] & 0xFF) * 8], rx < 8 ? rx : 8);
            else if (c[0] == 0x05 && tx >= 10) {
                u8 *blk = &eeprom[(c[1] & 0xFF) * 8];
                if (memcmp(blk, &c[2], 8)) { memcpy(blk, &c[2], 8); eep_writes++; if (!port_net_det() && !port_photo_sandbox) __port_eep_dirty(); } /* P337: online saves stay in this session (sandbox) */
                if (rx) r[0] = 0;
            }
            else ok = 0;
        } else ok = 0;
        if (!ok) pif_ram[i + 1] |= 0x80;                /* no response */
        i += 2 + tx + rx;
        ch++;
    }
    pif_ram[63] = 0;
}

/* SI DMA of a 64-byte PIF block (pc_os.c __port_io_write); d is game (vbe) memory */
void port_pif_dma(int write, void *d) {
    if (write) { for (int k = 0; k < 64; k++) pif_ram[k] = (u8)vbe_ld8((u8 *)d + k); pif_run(); }
    else for (int k = 0; k < 64; k++) vbe_st8((u8 *)d + k, pif_ram[k]);
}

/* ---------------- controllers ---------------- */

/* P236: libultra's osContInit (init_eu_256E0.c) ends with osCreateMesgQueue(&__osEepromTimerQ, &__osEepromTimerMsg, 1)
 * (EU g_eep_timer_queue / g_eep_timer_msg). This replacement skipped it, so the queue stayed zeroed (msgCount 0): the EEPROM
 * long write's timer message (osEepromLongWrite eeprom_async_write_start -> osSetTimer) was dropped by osSendMesg, the per-frame
 * pump eeprom_async_write_step(0) never advanced, and the NEXT save blocked for good in eeprom_async_write_start's
 * `while (eeprom_async_write_step(1))` (osRecvMesg OS_MESG_BLOCK on a queue nobody can fill). Seen after P232 made
 * save_slot_write save_slot_pack C: first save at the level 6 entry (frame 17824), the game thread froze at the next one
 * (level 0x18 scene 2 request, frame 19116). Created once, as libultra does (guarded by __osContinitialized). */
extern OSMesgQueue g_eep_timer_queue; /* __osEepromTimerQ; was D_80042E08 */
extern OSMesg g_eep_timer_msg;      /* __osEepromTimerMsg; was D_80042E20 */
s32 osContInit(OSMesgQueue *mq, u8 *bits, OSContStatus *st) {
    (void)mq;
    u8 present = 0;
    static int eep_q_done;
    if (!eep_q_done) { osCreateMesgQueue(&g_eep_timer_queue, &g_eep_timer_msg, 1); eep_q_done = 1; }
    pads_apply_mask();                                 /* P337 ?padmask / online presence mask */
    for (int i = 0; i < MAXCONTROLLERS; i++) {
        int on = port_pads[i][0] != 0;
        present |= on << i;
        /* sub-word fields of game memory: vbe accessors (port/ultra/pc_mem.h) */
        vbe_st16(&st[i].type, on ? CONT_TYPE_NORMAL : 0);
        vbe_st8(&st[i].status, 0);
        vbe_st8(&st[i].errno, on ? 0 : CONT_NO_RESPONSE_ERROR);
    }
    vbe_st8(bits, present);
    return 0;
}

/* the controller block as read back into DRAM: other SI users (EEPROM, pak writes) reuse PIF RAM
 * between osContStartReadData and osContGetReadData, so the replies are kept here */
static u8 cont_ram[64];
/* libultra __osPackReadData: per channel {0xFF dummy, tx 1, rx 4, cmd 0x01, 4 reply bytes}, then 0xFE */
s32 osContStartReadData(OSMesgQueue *mq) {
    int i = 0;
    memset(pif_ram, 0, sizeof pif_ram);
    for (int ch = 0; ch < MAXCONTROLLERS; ch++) {
        pif_ram[i++] = 0xFF; pif_ram[i++] = 1; pif_ram[i++] = 4; pif_ram[i++] = 0x01;
        pif_ram[i++] = 0xFF; pif_ram[i++] = 0xFF; pif_ram[i++] = 0xFF; pif_ram[i++] = 0xFF;
    }
    pif_ram[i] = 0xFE;
    pif_ram[63] = 1;
    if (port_net_on) { pads_apply_mask(); port_net_fill_pads(&port_pads[0][0]); }   /* P338 online: the input ring */
    else padf_apply();                                 /* P149 ?padf frame script */
    free_camera_pads();                                /* P347 free camera: camera stick -> camera or C buttons */
    if (!port_photo_sandbox) padrec_log();             /* P228 ?padrec=1 (P348: not the photo frames' retraces) */
    pif_run();
    memcpy(cont_ram, pif_ram, sizeof cont_ram);         /* the RD64B DMA into libultra's __osContPifRam */
    s32 r = mq ? osSendMesg(mq, NULL, OS_MESG_NOBLOCK) : -1; /* SI transfer done at once */
    { static int n; if (n++ < 3) port_log("[os] osContStartReadData %p: send %d, queue %d/%d\n", (void *)mq, r, mq ? mq->validCount : 0, mq ? mq->msgCount : 0); }
    return 0;
}

/* P27: log what the game's per-frame read cont_read_frame gets (first changes of pad 0), and on the
 * next read what it made of it: g_cont_pads[0] (dead-zoned pad) and g_cont_pressed[0] (new presses).
 * Weak: the scheduler demo links this file without the game. ?padlog=N raises the limit (default 8). */
extern OSContPad g_cont_pads[4] __attribute__((weak)); /* was D_800BED38 */
extern u16 g_cont_pressed[4] __attribute__((weak)); /* was D_800BED50 */
static unsigned pad_reads;
static void pad_log(const OSContPad *pad) {
    static int lim = -1, n, game_n; static u32 last = 0xFFFFFFFFu, last_game = 0;
    if (lim < 0) { lim = port_flag("padlog"); if (!lim) lim = 8; }
    if (g_cont_pads && game_n < lim) {
        u32 g = vbe_ld16(&g_cont_pads[0].button) << 16 | (u8)vbe_ld8(&g_cont_pads[0].stick_x) << 8 | (u8)vbe_ld8(&g_cont_pads[0].stick_y);
        if (g != last_game) {
            game_n++; last_game = g;
            port_log("[pad] game after read #%u: D_800BED38[0] buttons %04X stick %d,%d (dead-zoned), D_800BED50[0] new %04X\n",
                     pad_reads - 1, g >> 16, (s8)(g >> 8), (s8)g, g_cont_pressed ? vbe_ld16(&g_cont_pressed[0]) : 0);
        }
    }
    u32 v = vbe_ld16(&pad[0].button) << 16 | (u8)vbe_ld8(&pad[0].stick_x) << 8 | (u8)vbe_ld8(&pad[0].stick_y);
    if (v != last && n < lim) {
        n++; last = v;
        port_log("[pad] read #%u (frame %u): pad0 buttons %04X stick %d,%d errno %d\n", pad_reads, port_frame_count,
                 v >> 16, (s8)(v >> 8), (s8)v, (int)vbe_ld8(&pad[0].errno));
    }
}

/* libultra __osContGetReadData: unpack the replies of the block osContStartReadData ran */
void osContGetReadData(OSContPad *pad) {
    { static int n; if (n++ < 3) { u32 *r = (u32 *)port_n64_to_wasm(0x800B1200); u32 *q = r ? (u32 *)(uintptr_t)*r : 0;
        port_log("[os] osContGetReadData #%d; D_800B0DF0 (EU 800B1200) = %08X", n, r ? *r : 0);
        if ((uintptr_t)q >= 0x10000000u) port_log(" -> %08X %08X %08X %08X", q[0], q[1], q[2], q[3]);
        port_log("\n"); } }
    pad_reads++;
    const u8 *p = cont_ram;
    for (int ch = 0; ch < MAXCONTROLLERS; ch++, p += 8) {
        int err = (p[2] & 0xC0) >> 4;                   /* CHNL_ERR(rx byte) */
        vbe_st8(&pad[ch].errno, err);
        if (err == 0) {
            vbe_st16(&pad[ch].button, (u16)(p[4] << 8 | p[5]));
            vbe_st8(&pad[ch].stick_x, p[6]);
            vbe_st8(&pad[ch].stick_y, p[7]);
        } else {
            vbe_st16(&pad[ch].button, 0); vbe_st8(&pad[ch].stick_x, 0); vbe_st8(&pad[ch].stick_y, 0);
        }
    }
    pad_log(pad);
}

/* ---------------- P27 save test: EEPROM write/read through PIF commands 0x05 / 0x04 ----------------
 * The game's own save path (osEepromLongWrite eeprom_async_write_start, pumped per frame by eeprom_async_write_step) only
 * runs from its save menus, which are still asm. This drives the same PIF device with the same command
 * blocks libultra's __osPackEepWriteData / __osPackEepReadData build, on channel 4.
 * mode 1: write 64 bytes derived from `seed` to blocks 0x38..0x3F; mode 2: read them back and compare. */
static void eep_cmd(int write, int block, u8 *buf) {
    memset(pif_ram, 0, sizeof pif_ram);
    int i = 4;                                          /* channels 0-3 skipped (0x00) */
    pif_ram[i++] = write ? 10 : 2; pif_ram[i++] = write ? 1 : 8;
    pif_ram[i++] = write ? 0x05 : 0x04; pif_ram[i++] = (u8)block;
    if (write) memcpy(&pif_ram[i], buf, 8);
    i += write ? 9 : 8;
    pif_ram[i] = 0xFE; pif_ram[63] = 1;
    pif_run();
    if (!write) memcpy(buf, &pif_ram[8], 8);
}
EMSCRIPTEN_KEEPALIVE int port_eep_test(int mode, int seed) {
    u8 b[8]; int bad = 0;
    for (int blk = 0x38; blk < 0x40; blk++) {
        u8 want[8];
        for (int k = 0; k < 8; k++) want[k] = (u8)(seed * 31 + blk * 7 + k * 13 + (seed >> 8));
        if (mode == 1) eep_cmd(1, blk, want);
        else { eep_cmd(0, blk, b); bad += memcmp(b, want, 8) != 0; }
    }
    if (mode == 1) port_log("[eeptest] wrote blocks 38-3F (seed %d), %u EEPROM writes so far\n", seed, eep_writes);
    else port_log("[eeptest] %s: read blocks 38-3F back (seed %d), %d of 8 differ\n", bad ? "FAIL" : "PASS", seed, bad);
    return bad;
}
