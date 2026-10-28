/* CPU interpreter for Conker's RSP audio microcode (Rare's n_audio ABI, "naudio" with the
 * Conker / MP3 command table). Written for this port in session P9; command semantics follow the
 * RSP behaviour as documented by mupen64plus-rsp-hle (alist_naudio.c / alist.c, GPL-2.0). No code
 * was copied: see port/audio/LICENSES.md.
 *
 * DMEM model: a 4 KB big-endian byte array, exactly like the RSP. Every DMEM operand in the
 * command list is relative to NAUDIO_MAIN (0x4F0). The fixed buffers, relative to MAIN:
 *   0x000 MAIN (resample / envmixer input, interleave output), 0x170 MAIN2,
 *   0x4E0 dry L, 0x650 dry R, 0x7C0 wet L, 0x930 wet R   (each 0x170 bytes = 184 samples).
 * Conker's C code uses exactly these offsets (init_1FB40.c, init_1E530.c, init_210C0.c).
 *
 * DRAM: game memory in vbe layout (word-swapped, pc_mem.h), accessed through vbe_ld8/16. */
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "aud.h"
#include "../ultra/pc_mem.h"

void port_log(const char *fmt, ...);
extern unsigned char *port_rom;
extern unsigned port_rom_size;

enum { MAIN = 0x4F0, MAIN2 = 0x660, COUNT = 0x170,
       DRY_L = 0x9D0, DRY_R = 0xB40, WET_L = 0xCB0, WET_R = 0xE20 };

struct aud_stats aud_stats;
int aud_trace; /* >0: log that many commands (debug) */

static uint8_t dmem[0x1000];
static int16_t adpcm_table[0x80]; /* up to 8 predictors x 2 x 8 */
static uint32_t loop_addr;
static int16_t vol[2], target[2], dry, wet;
static int32_t rate[2];
static int16_t lut[64 * 4];
static int lut_ok;

/* ---------------- memory helpers ---------------- */
static inline int16_t d16(unsigned a) { a &= 0xFFE; return (int16_t)(dmem[a] << 8 | dmem[a + 1]); }
static inline void d16w(unsigned a, int v) { a &= 0xFFE; dmem[a] = (uint8_t)(v >> 8); dmem[a + 1] = (uint8_t)v; }
static inline int16_t clamp16(int32_t v) { return v > 32767 ? 32767 : v < -32768 ? -32768 : (int16_t)v; }

/* A DRAM operand: the game builds them with osVirtualToPhysical (identity in the port) and often
 * masks them to 24 bits (the per-voice states of ADPCM, RESAMPLE, ENVMIXER, FILTER, the loop state and
 * the ADPCM book). The audio heap, DMA buffers and synth state are in the n64_rdram mirror, so a 24-bit
 * value gets the top byte that puts it inside n64_rdram (8 MB, so only one of the two candidates can be).
 * P348 fix: this was a fixed 0x10 top byte, right while the mirror sat at 0x102xxxxx..0x10Axxxxx. P337's
 * fiber-stack pools (12 MB of .bss in pc_sched.o) moved the mirror to 0x11711000, and since then the
 * voice states were read and written in the unused pool instead of the game's audio heap: the sound was
 * the same (each state went back and forth to the same wrong place), but that memory is outside the game
 * state the online hash and photo mode's snapshot cover. */
static inline uint8_t *aud_dram(uint32_t a) {
    if (a < 0x01000000u) {
        uint32_t base = (uint32_t)(uintptr_t)n64_rdram;
        a |= base & 0xFF000000u;
        if (a < base) a += 0x01000000u;
    }
    return (uint8_t *)(uintptr_t)a;
}
static inline int16_t m16(uint8_t *p) { return (int16_t)vbe_ld16(p); }
static inline void m16w(uint8_t *p, int v) { vbe_st16(p, (unsigned)(uint16_t)v); }
static inline uint32_t vbe_ld32w(const uint8_t *p) { return *(const uint32_t *)(uintptr_t)p; } /* 4-aligned word: native */

static void dma_in(unsigned d, uint32_t addr, unsigned n) {   /* DRAM -> DMEM */
    uint8_t *p = aud_dram(addr & ~7u);
    d &= ~3u; n = (n + 7) & ~7u;
    for (unsigned i = 0; i < n; i++) dmem[(d + i) & 0xFFF] = (uint8_t)vbe_ld8(p + i);
}
static void dma_out(unsigned d, uint32_t addr, unsigned n) {  /* DMEM -> DRAM */
    uint8_t *p = aud_dram(addr & ~7u);
    d &= ~3u; n = (n + 7) & ~7u;
    for (unsigned i = 0; i < n; i++) vbe_st8(p + i, dmem[(d + i) & 0xFFF]);
}

/* ---------------- tables ---------------- */
int aud_init_tables(void) {
    /* The ucode data (g_audio_ucode_data, 0x800 bytes) holds the 4-tap resample table; its first row is
     * 0C39 66AD 0D46 FFDF. Found at ROM 0x2CD80 in the EU ROM; searched so other versions work. */
    static const uint8_t sig[8] = {0x0C, 0x39, 0x66, 0xAD, 0x0D, 0x46, 0xFF, 0xDF};
    if (lut_ok) return 0;
    if (!port_rom) return -1;
    for (unsigned off = 0x1000; off + 512 < port_rom_size && off < 0x100000; off += 8) {
        if (memcmp(port_rom + off, sig, 8) == 0) {
            for (int i = 0; i < 256; i++) lut[i] = (int16_t)(port_rom[off + 2 * i] << 8 | port_rom[off + 2 * i + 1]);
            lut_ok = 1;
            port_log("[aud] resample table at ROM 0x%X\n", off);
            return 0;
        }
    }
    port_log("[aud] resample table not found in ROM\n");
    return -1;
}

/* ---------------- commands ---------------- */

/* VADPCM: each 9-byte frame (4-bit) is a header (scale << 4 | predictor) and 16 residuals. The
 * predictor is 2 x 8 coefficients: row 0 weights the sample two back, row 1 the previous one;
 * within an 8-sample half the earlier residuals feed forward through row 1. */
static void cmd_adpcm(uint32_t w0, uint32_t w1) {
    unsigned flags = w1 >> 28, count = (w1 >> 16) & 0xFFF;
    unsigned di = MAIN + ((w1 >> 12) & 0xF), dout = MAIN + (w1 & 0xFFF);
    uint8_t *state = aud_dram(w0 & 0xFFFFFF);
    int16_t last[16];
    count = (count + 0x1F) & ~0x1Fu;
    if (flags & 1) memset(last, 0, sizeof last);
    else {
        uint8_t *src = (flags & 2) ? aud_dram(loop_addr) : state;
        for (int i = 0; i < 16; i++) last[i] = m16(src + 2 * i);
    }
    for (int i = 0; i < 16; i++, dout += 2) d16w(dout, last[i]);
    while (count) {
        unsigned hdr = dmem[di++ & 0xFFF];
        int scale = hdr >> 4;
        const int16_t *book = adpcm_table + ((hdr & 0xF) << 4);
        int32_t r[16];
        for (int i = 0; i < 8; i++) {
            unsigned b = dmem[di++ & 0xFFF];
            int hi = (int)(int8_t)(b & 0xF0) >> 4, lo = (int)(int8_t)(b << 4) >> 4;
            r[2 * i] = scale <= 12 ? hi << scale : hi << 12;
            r[2 * i + 1] = scale <= 12 ? lo << scale : lo << 12;
        }
        for (int h = 0; h < 2; h++) {
            int32_t p2 = h ? last[6] : last[14], p1 = h ? last[7] : last[15];
            const int32_t *rr = r + 8 * h;
            for (int i = 0; i < 8; i++) {
                int32_t acc = book[i] * p2 + book[8 + i] * p1 + (rr[i] << 11);
                for (int k = 0; k < i; k++) acc += book[8 + i - 1 - k] * rr[k];
                last[8 * h + i] = clamp16(acc >> 11);
            }
        }
        for (int i = 0; i < 16; i++, dout += 2) d16w(dout, last[i]);
        count -= 32;
    }
    for (int i = 0; i < 16; i++) m16w(state + 2 * i, last[i]);
}

/* 4-tap interpolating resampler, Q16 pitch accumulator; the state keeps the 4 input samples
 * under the read position and the fraction. Output: 184 samples at MAIN or MAIN2. */
static void cmd_resample(uint32_t w0, uint32_t w1) {
    unsigned flags = w1 >> 30;
    uint32_t pitch = ((w1 >> 14) & 0xFFFF) << 1;
    unsigned ipos = ((MAIN + ((w1 >> 2) & 0xFFF)) >> 1) - 4, opos = ((w1 & 3) ? MAIN2 : MAIN) >> 1;
    uint8_t *state = aud_dram(w0 & 0xFFFFFF);
    uint32_t acc;
    if (flags & 1) { for (int i = 0; i < 4; i++) d16w((ipos + i) * 2, 0); acc = 0; }
    else { for (int i = 0; i < 4; i++) d16w((ipos + i) * 2, m16(state + 2 * i)); acc = (uint16_t)m16(state + 8); }
    for (int n = 0; n < COUNT / 2; n++) {
        const int16_t *t = lut + ((acc & 0xFC00) >> 8);
        int32_t v = d16(ipos * 2) * t[0] + d16(ipos * 2 + 2) * t[1] + d16(ipos * 2 + 4) * t[2] + d16(ipos * 2 + 6) * t[3];
        d16w(opos++ * 2, clamp16(v >> 15));
        acc += pitch;
        ipos += acc >> 16;
        acc &= 0xFFFF;
    }
    for (int i = 0; i < 4; i++) m16w(state + 2 * i, d16((ipos + i) * 2));
    m16w(state + 8, (int)acc);
}

/* Linear envelope mixer: two volume ramps (Q16, step = rate/8 per sample) times dry and wet gains,
 * mixing MAIN into dry L/R and wet L/R. The state (80 bytes in DRAM) is private to the ucode;
 * here: wet, dry, target[2] as halfwords, step[2] and value[2] as words. */
static void cmd_envmixer(uint32_t w0, uint32_t w1) {
    uint8_t *st = aud_dram(w1 & 0xFFFFFF);
    int64_t val[2], step[2], tgt[2];
    int16_t d = dry, w = wet;
    vol[1] = (int16_t)w0;
    if ((w0 >> 16) & 1) {
        for (int c = 0; c < 2; c++) { step[c] = rate[c] / 8; val[c] = (int64_t)vol[c] << 16; tgt[c] = (int64_t)target[c] << 16; }
    } else {
        w = m16(st); d = m16(st + 2);
        for (int c = 0; c < 2; c++) {
            tgt[c] = (int64_t)m16(st + 4 + 2 * c) << 16;
            step[c] = (int32_t)((uint16_t)m16(st + 8 + 4 * c) << 16 | (uint16_t)m16(st + 10 + 4 * c));
            val[c] = (int32_t)((uint16_t)m16(st + 16 + 4 * c) << 16 | (uint16_t)m16(st + 18 + 4 * c));
        }
    }
    static const unsigned out[4] = {DRY_L, DRY_R, WET_L, WET_R};
    for (int k = 0; k < COUNT / 2; k++) {
        int16_t v[2];
        for (int c = 0; c < 2; c++) {
            val[c] += step[c];
            if (step[c] <= 0 ? val[c] <= tgt[c] : val[c] >= tgt[c]) { val[c] = tgt[c]; step[c] = 0; }
            v[c] = (int16_t)(val[c] >> 16);
        }
        int16_t g[4] = {clamp16((v[0] * d + 0x4000) >> 15), clamp16((v[1] * d + 0x4000) >> 15),
                        clamp16((v[0] * w + 0x4000) >> 15), clamp16((v[1] * w + 0x4000) >> 15)};
        int32_t in = d16(MAIN + 2 * k);
        for (int b = 0; b < 4; b++) d16w(out[b] + 2 * k, clamp16(d16(out[b] + 2 * k) + ((in * g[b]) >> 15)));
    }
    m16w(st, w); m16w(st + 2, d);
    for (int c = 0; c < 2; c++) {
        m16w(st + 4 + 2 * c, (int)(tgt[c] >> 16));
        m16w(st + 8 + 4 * c, (int)((uint32_t)step[c] >> 16)); m16w(st + 10 + 4 * c, (int)(uint32_t)step[c]);
        m16w(st + 16 + 4 * c, (int)((uint32_t)val[c] >> 16)); m16w(st + 18 + 4 * c, (int)(uint32_t)val[c]);
    }
}

/* Command 0x0E: filter in place on 184 samples at MAIN (w1 top byte 0) or MAIN2, coefficients from
 * the last LOADADPCM (16 halfwords t), gain = low halfword of w0, flags A_INIT.
 *  - t0 = t1 = 0: pole filter. Per 8-sample block, with h1 = t[0..7], h2 = t[8..15] and the last
 *    two outputs l1, l2 of the previous block:
 *      y[i] = (g x[i] + h1[i] l1 + h2[i] l2 + sum_{k<i} (h2[k] g >> 14) x[i-1-k]) >> 14
 *  - otherwise: biquad y = t0 x0 + t1 x1 + t0 x2 + 2 t8 y1 + 2 t9 y2 (Q15).
 * The DRAM state (8 halfwords) is private to the ucode; layout here: y1, y2, x1, x2. */
static void cmd_filter(uint32_t w0, uint32_t w1) {
    unsigned flags = (w0 >> 16) & 0xFF, d = (w1 >> 24) ? MAIN2 : MAIN;
    int32_t gain = (int32_t)(w0 & 0xFFFF);
    uint8_t *st = aud_dram(w1 & 0xFFFFFF);
    int32_t y1 = 0, y2 = 0, x1 = 0, x2 = 0;
    const int16_t *t = adpcm_table;
    if (!(flags & 1)) { y1 = m16(st); y2 = m16(st + 2); x1 = m16(st + 4); x2 = m16(st + 6); }
    if (t[0] == 0 && t[1] == 0) {
        int32_t h2g[8];
        for (int i = 0; i < 8; i++) h2g[i] = (t[8 + i] * gain) >> 14;
        for (int blk = 0; blk < COUNT / 16; blk++) {
            int32_t x[8];
            unsigned a = d + 16 * blk;
            for (int i = 0; i < 8; i++) x[i] = d16(a + 2 * i);
            for (int i = 0; i < 8; i++) {
                int32_t acc = x[i] * gain + t[i] * y2 + t[8 + i] * y1;
                for (int k = 0; k < i; k++) acc += h2g[k] * x[i - 1 - k];
                d16w(a + 2 * i, clamp16(acc >> 14));
            }
            y2 = d16(a + 12); y1 = d16(a + 14); /* l1 = sample 6, l2 = sample 7 */
        }
    } else {
        for (int i = 0; i < COUNT / 2; i++) {
            int32_t x0 = d16(d + 2 * i);
            int64_t acc = (int64_t)t[0] * x0 + (int64_t)t[1] * x1 + (int64_t)t[0] * x2;
            acc += 2 * (int64_t)t[8] * y1 + 2 * (int64_t)t[9] * y2;
            int16_t y = clamp16((int32_t)(acc >> 15));
            d16w(d + 2 * i, y);
            x2 = x1; x1 = x0; y2 = y1; y1 = y;
        }
    }
    m16w(st, y1); m16w(st + 2, y2); m16w(st + 4, x1); m16w(st + 6, x2);
}

/* ---------------- MP3 synthesis (commands 7 and 8, session P14) ----------------
 *
 * Conker's voice clips are MPEG-2 Layer III. The CPU (game_221290.c) does everything up to the
 * hybrid filterbank and leaves one granule in DRAM as
 *   +0  s32 gain << 16 (0x00100000) and its negation
 *   +8  18 time slots x 32 subband samples, s16, sample = float value * 2048
 * The RSP's part is the polyphase synthesis filterbank (ISO 11172-3 2.4.3.2): per time slot,
 * matrixing into the 64-sample V vector, a 16-vector V FIFO and the 512-tap window. Output: 576
 * s16 PCM samples written from the start of the same buffer.
 *   MP3ADDY (8): w1 = DRAM address of the channel's synthesis state (the game zeroes 0x440 bytes
 *                there when a stream starts).
 *   MP3 (7):     w0 & 0x1E = FIFO position (the game steps it by -0x24 per granule, i.e. -2 per
 *                slot, mod 0x20), w1 = the granule buffer.
 * The FIFO is kept here in float, keyed by the state address; a marker word in the DRAM state ties
 * it to the game's buffer, so the game's bzero at stream start resets it, as it would the RSP's.
 * The window is read from the user's ROM (ucode data, 0x2CFD0 in the EU ROM). Written from the ISO
 * description; mupen64plus-rsp-hle's mp3.c was only used to confirm the command fields and the
 * in-place buffer layout (see LICENSES.md). */
static uint32_t mp3_addr;
static float mp3_win[512];
static float mp3_cos[32][32]; /* X[i] = sum_k cos((2k+1) i pi / 64) S[k] */
static int mp3_ok;
static struct { uint32_t key, marker; float x[16][32]; } mp3_st[4];
static uint32_t mp3_gen;

static int mp3_tables(void) {
    /* window rows: 16 halfwords per row, row 2j = D[j + 32i] (i = 0..15) for j = 0..16, scaled so
     * that D[256] = 1.144989014 is 32767 */
    static const uint8_t sig[16] = {0x00, 0x00, 0xFF, 0xF3, 0x00, 0x5D, 0xFF, 0x38, 0x03, 0x7A, 0xF7, 0x36, 0x0B, 0x37, 0xC0, 0x0E};
    if (mp3_ok) return mp3_ok > 0 ? 0 : -1;
    mp3_ok = -1;
    if (!port_rom) return -1;
    for (unsigned off = 0x1000; off + 0x880 < port_rom_size && off < 0x100000; off += 8) {
        if (memcmp(port_rom + off, sig, 16) != 0) continue;
        const double s = 1.144989014 / 32767.0;
        for (int j = 0; j <= 16; j++)
            for (int i = 0; i < 16; i++) {
                const uint8_t *p = port_rom + off + 2 * (32 * j + i);
                mp3_win[j + 32 * i] = (float)((int16_t)(p[0] << 8 | p[1]) * s);
            }
        /* j = 17..31 from the prototype's symmetry: D[k] = D[512 - k] * (-1)^(k/64 + (512-k)/64) */
        for (int j = 17; j < 32; j++)
            for (int i = 0; i < 16; i++) {
                int k = j + 32 * i, m = 512 - k;
                mp3_win[k] = (((k >> 6) + (m >> 6)) & 1) ? -mp3_win[m] : mp3_win[m];
            }
        for (int i = 0; i < 32; i++)
            for (int k = 0; k < 32; k++) mp3_cos[i][k] = (float)cos(3.14159265358979 / 64.0 * (2 * k + 1) * i);
        port_log("[aud] mp3 window at ROM 0x%X\n", off);
        mp3_ok = 1;
        return 0;
    }
    port_log("[aud] mp3 window not found in ROM\n");
    return -1;
}

static void mp3_synth(unsigned index, uint32_t addr) {
    uint8_t *st = aud_dram(mp3_addr), *buf = aud_dram(addr);
    uint32_t *mark = (uint32_t *)(uintptr_t)((uintptr_t)st & ~(uintptr_t)3);
    int slot = -1, pos = (int)(index >> 1);
    int16_t in[576];
    float gain;

    if (mp3_tables() < 0) return;
    for (int i = 0; i < 4; i++) if (mp3_st[i].key == mp3_addr) slot = i;
    if (slot < 0) { slot = (int)(mp3_gen & 3); mp3_st[slot].key = mp3_addr; mp3_st[slot].marker = 0; }
    if (*mark != mp3_st[slot].marker || mp3_st[slot].marker == 0) {   /* new stream (or new buffer) */
        memset(mp3_st[slot].x, 0, sizeof mp3_st[slot].x);
        mp3_st[slot].marker = 0x50330000u | (++mp3_gen & 0xFFFF);
        *mark = mp3_st[slot].marker;
    }
    gain = (float)(int32_t)vbe_ld32w(buf) / 65536.0f;
    for (int n = 0; n < 576; n++) in[n] = m16(buf + 8 + 2 * n);

    for (int t = 0; t < 18; t++, pos = (pos - 1) & 15) {
        float *x = mp3_st[slot].x[pos];
        const int16_t *s = in + 32 * t;
        for (int i = 0; i < 32; i++) {
            float acc = 0.0f;
            for (int k = 0; k < 32; k++) acc += mp3_cos[i][k] * s[k];
            x[i] = acc;
        }
        for (int j = 0; j < 32; j++) {
            float acc = 0.0f;
            for (int i = 0; i < 16; i++) {
                const float *v = mp3_st[slot].x[(pos + i) & 15]; /* the vector from i slots ago */
                float vv;
                if (!(i & 1)) vv = j <= 16 ? (j == 16 ? 0.0f : v[j + 16]) : -v[48 - j]; /* V[j] */
                else vv = j <= 15 ? -v[16 - j] : -v[j - 16];                           /* V[32 + j] */
                acc += mp3_win[j + 32 * i] * vv;
            }
            m16w(buf + 2 * (32 * t + j), clamp16((int32_t)lrintf(acc * gain)));
        }
    }
}

void aud_run_alist(const uint32_t *cmds, uint32_t nbytes) {
    unsigned n = nbytes / 8;
    aud_stats.lists++;
    if (!lut_ok) aud_init_tables();
    for (unsigned i = 0; i < n; i++) {
        uint32_t w0 = cmds[2 * i], w1 = cmds[2 * i + 1];
        unsigned op = w0 >> 24;
        aud_stats.cmds++;
        aud_stats.by_op[op & 15]++;
        if (aud_trace > 0) { aud_trace--; port_log("[aud] %08X %08X\n", w0, w1); }
        switch (op) {
        case 0x00: { /* OVERLOAD: amplify with clipping, then attenuate (Rare distortion) */
            unsigned d = MAIN + (w0 & 0xFFF);
            int16_t gain = (int16_t)w1; uint16_t att = (uint16_t)(w1 >> 16);
            for (int k = 0; k < COUNT; k++) {
                int16_t a = clamp16(d16(d + 2 * k) * gain);
                d16w(d + 2 * k, (int16_t)((a * (int32_t)att) >> 16));
            }
            break;
        }
        case 0x01: cmd_adpcm(w0, w1); break;
        case 0x02: { unsigned d = MAIN + (w0 & 0xFFFF), c = w1 & 0xFFF;
            for (unsigned k = 0; k < c; k++) dmem[(d + k) & 0xFFF] = 0; break; }
        case 0x03: cmd_envmixer(w0, w1); break;
        case 0x04: dma_in(MAIN + (w0 & 0xFFF), w1, (w0 >> 12) & 0xFFF); break;
        case 0x05: cmd_resample(w0, w1); break;
        case 0x06: dma_out(MAIN + (w0 & 0xFFF), w1, (w0 >> 12) & 0xFFF); aud_stats.saves++; break;
        case 0x07: aud_stats.mp3++; mp3_synth(w0 & 0x1E, w1); break;
        case 0x08: mp3_addr = w1; break; /* MP3ADDY: DRAM address of the synthesis state */
        case 0x09: { unsigned f = (w0 >> 16) & 0xFF;
            if (f & 4) {
                if (f & 2) { vol[0] = (int16_t)w0; dry = (int16_t)(w1 >> 16); wet = (int16_t)w1; }
                else { target[1] = (int16_t)w0; rate[1] = (int32_t)w1; }
            } else { target[0] = (int16_t)w0; rate[0] = (int32_t)w1; }
            break; }
        case 0x0A: { unsigned s = MAIN + (w0 & 0xFFFF), d = MAIN + (w1 >> 16), c = ((w1 & 0xFFFF) + 3) & ~3u;
            uint8_t tmp[0x1000]; for (unsigned k = 0; k < c && k < 0x1000; k++) tmp[k] = dmem[(s + k) & 0xFFF];
            for (unsigned k = 0; k < c && k < 0x1000; k++) dmem[(d + k) & 0xFFF] = tmp[k];
            break; }
        case 0x0B: { uint8_t *p = aud_dram(w1 & 0xFFFFFF); unsigned c = (w0 & 0xFFFF) >> 1;
            for (unsigned k = 0; k < c && k < 0x80; k++) adpcm_table[k] = m16(p + 2 * k); break; }
        case 0x0C: { int16_t g = (int16_t)w0; unsigned s = MAIN + (w1 >> 16), d = MAIN + (w1 & 0xFFFF);
            for (int k = 0; k < COUNT / 2; k++) d16w(d + 2 * k, clamp16(d16(d + 2 * k) + ((d16(s + 2 * k) * g) >> 15)));
            break; }
        case 0x0D: { int16_t l[COUNT / 2], r[COUNT / 2];
            for (int k = 0; k < COUNT / 2; k++) { l[k] = d16(DRY_L + 2 * k); r[k] = d16(DRY_R + 2 * k); }
            for (int k = 0; k < COUNT / 2; k++) { d16w(MAIN + 4 * k, l[k]); d16w(MAIN + 4 * k + 2, r[k]); }
            break; }
        case 0x0E: cmd_filter(w0, w1); break;
        case 0x0F: loop_addr = w1 & 0xFFFFFF; break;
        default:
            if (aud_stats.unknown++ < 4) port_log("[aud] unknown command %08X %08X\n", w0, w1);
        }
    }
}
