/* PIF model: controllers and the 16 Kbit EEPROM (P19, moved here and extended in P27).
 *
 * Two ways into it, both through the same command interpreter pif_run():
 *  - the game's own libultra SI code (EEPROM probe/read/write in game_eu_20B220.c etc., pak writes)
 *    writes SI_DRAM_ADDR and then SI_PIF_ADDR_WR64B / RD64B; pc_os.c __port_io_write calls
 *    port_pif_dma(), which copies the 64-byte block, runs it and posts OS_EVENT_SI;
 *  - the PC osContStartReadData packs the libultra controller-read block (cmd 0x01 on channels 0-3)
 *    into PIF RAM and runs it; osContGetReadData unpacks the replies like libultra's
 *    __osContGetReadData (button, stick, errno = CHNL_ERR). The game's per-frame read func_1501BBB8
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

void port_log(const char *fmt, ...);
int port_flag(const char *name);
void *port_n64_to_wasm(unsigned n64addr);

/* ---- input state written by the page: per pad {present, buttons (N64 bits), stick_x, stick_y} */
static int32_t port_pads[MAXCONTROLLERS][4] = { { 1, 0, 0, 0 } };
EMSCRIPTEN_KEEPALIVE int32_t *port_pad_state(void) { return &port_pads[0][0]; }

/* ---- EEPROM */
#define EEP_SIZE 2048
static u8 eeprom[EEP_SIZE];
static unsigned eep_writes;
EMSCRIPTEN_KEEPALIVE u8 *port_eeprom_ptr(void) { return eeprom; }
EMSCRIPTEN_KEEPALIVE int port_eeprom_size(void) { return EEP_SIZE; }
EM_JS(void, __port_eep_dirty, (void), { if (typeof Module !== 'undefined' && Module.portEepDirty) Module.portEepDirty(); });

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
                r[2] = (u8)(s8)port_pads[ch][2]; r[3] = (u8)(s8)port_pads[ch][3];
            }
            else ok = 0;                                /* pak commands: no pak */
        } else if (ch == 4) {                           /* EEPROM 16K */
            if (c[0] == 0x00 || c[0] == 0xFF) { if (rx >= 3) { r[0] = 0x00; r[1] = 0xC0; r[2] = 0x00; } }
            else if (c[0] == 0x04 && tx >= 2) memcpy(r, &eeprom[(c[1] & 0xFF) * 8], rx < 8 ? rx : 8);
            else if (c[0] == 0x05 && tx >= 10) {
                u8 *blk = &eeprom[(c[1] & 0xFF) * 8];
                if (memcmp(blk, &c[2], 8)) { memcpy(blk, &c[2], 8); eep_writes++; __port_eep_dirty(); }
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

s32 osContInit(OSMesgQueue *mq, u8 *bits, OSContStatus *st) {
    (void)mq;
    u8 present = 0;
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
    pif_run();
    memcpy(cont_ram, pif_ram, sizeof cont_ram);         /* the RD64B DMA into libultra's __osContPifRam */
    s32 r = mq ? osSendMesg(mq, NULL, OS_MESG_NOBLOCK) : -1; /* SI transfer done at once */
    { static int n; if (n++ < 3) port_log("[os] osContStartReadData %p: send %d, queue %d/%d\n", (void *)mq, r, mq ? mq->validCount : 0, mq ? mq->msgCount : 0); }
    return 0;
}

/* P27: log what the game's per-frame read func_1501BBB8 gets (first changes of pad 0), and on the
 * next read what it made of it: D_800BED38[0] (dead-zoned pad) and D_800BED50[0] (new presses).
 * Weak: the scheduler demo links this file without the game. ?padlog=N raises the limit (default 8). */
extern OSContPad D_800BED38[4] __attribute__((weak));
extern u16 D_800BED50[4] __attribute__((weak));
static unsigned pad_reads;
static void pad_log(const OSContPad *pad) {
    static int lim = -1, n, game_n; static u32 last = 0xFFFFFFFFu, last_game = 0;
    if (lim < 0) { lim = port_flag("padlog"); if (!lim) lim = 8; }
    if (D_800BED38 && game_n < lim) {
        u32 g = vbe_ld16(&D_800BED38[0].button) << 16 | (u8)vbe_ld8(&D_800BED38[0].stick_x) << 8 | (u8)vbe_ld8(&D_800BED38[0].stick_y);
        if (g != last_game) {
            game_n++; last_game = g;
            port_log("[pad] game after read #%u: D_800BED38[0] buttons %04X stick %d,%d (dead-zoned), D_800BED50[0] new %04X\n",
                     pad_reads - 1, g >> 16, (s8)(g >> 8), (s8)g, D_800BED50 ? vbe_ld16(&D_800BED50[0]) : 0);
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
 * The game's own save path (osEepromLongWrite func_151DD4A0, pumped per frame by func_151DD588) only
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
