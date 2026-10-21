/* PC audio output (session P9): a ring buffer of stereo s16 frames drained by an SDL audio
 * callback. Under Emscripten this is emscripten's built-in SDL audio (library_sdl.js, Web Audio):
 * the pinned conker-emsdk image has no SDL2 port in its cache and the build must not download one.
 * The calls below are the SDL 1.2 subset that SDL2 also provides (SDL_OpenAudio/SDL_PauseAudio), so
 * moving to -sUSE_SDL=2 is a flag change once the image carries SDL2. In node (no AudioContext) the
 * device stays closed and pushed audio is only counted. */
#include <stdint.h>
#include <string.h>
#include <SDL/SDL.h>
#include <emscripten.h>
#include "aud.h"
#include "../ultra/pc_mem.h"

void port_log(const char *fmt, ...);

#define RING (1u << 17) /* stereo frames, ~6 s at 22 kHz */
static int16_t ring[RING][2];
static volatile unsigned rd, wr;
static int opened;
static unsigned pushed, dropped;

static void cb(void *u, Uint8 *stream, int len) {
    (void)u;
    int16_t *o = (int16_t *)stream;
    int frames = len / 4;
    for (int i = 0; i < frames; i++) {
        if (rd != wr) { o[2 * i] = ring[rd][0]; o[2 * i + 1] = ring[rd][1]; rd = (rd + 1) & (RING - 1); }
        else o[2 * i] = o[2 * i + 1] = 0;
    }
}

int aud_out_open(int rate) {
    if (opened) return 0;
    int has_ctx = EM_ASM_INT({ return (typeof AudioContext !== 'undefined' || typeof webkitAudioContext !== 'undefined') ? 1 : 0; });
    if (!has_ctx) { port_log("[aud] no AudioContext (node): output disabled, %d Hz\n", rate); opened = -1; return -1; }
    if (SDL_Init(SDL_INIT_AUDIO) < 0) { port_log("[aud] SDL_Init audio failed\n"); opened = -1; return -1; }
    SDL_AudioSpec want, have;
    memset(&want, 0, sizeof want);
    want.freq = rate; want.format = AUDIO_S16; want.channels = 2; want.samples = 1024; want.callback = cb;
    if (SDL_OpenAudio(&want, &have) < 0) { port_log("[aud] SDL_OpenAudio failed\n"); opened = -1; return -1; }
    SDL_PauseAudio(0);
    opened = 1;
    port_log("[aud] SDL audio open: %d Hz, %d ch, %d samples\n", have.freq, have.channels, have.samples);
    return 0;
}

void aud_out_push_game(const void *buf, unsigned frames) {
    const uint8_t *p = (const uint8_t *)buf;
    pushed += frames;
    for (unsigned i = 0; i < frames; i++) {
        unsigned nx = (wr + 1) & (RING - 1);
        if (nx == rd) { dropped += frames - i; break; }
        ring[wr][0] = (int16_t)vbe_ld16(p + 4 * i);
        ring[wr][1] = (int16_t)vbe_ld16(p + 4 * i + 2);
        wr = nx;
    }
    if (opened != 1) rd = wr; /* no device: discard */
}

unsigned aud_out_queued(void) { return (wr - rd) & (RING - 1); }

/* ---------------- test capture (aud_test.c): accumulate, check, write a WAV / play ---------------- */
#define CAP (22050 * 20)
static int16_t cap[CAP][2];
static unsigned ncap;

void aud_wav_append(const void *buf, unsigned frames) {
    const uint8_t *p = (const uint8_t *)buf;
    for (unsigned i = 0; i < frames && ncap < CAP; i++, ncap++) {
        cap[ncap][0] = (int16_t)vbe_ld16(p + 4 * i);
        cap[ncap][1] = (int16_t)vbe_ld16(p + 4 * i + 2);
    }
}

void aud_wav_finish(int rate) {
    double e = 0, d = 0; int peak = 0; unsigned nz = 0;
    for (unsigned i = 0; i < ncap; i++) {
        int v = cap[i][0];
        e += (double)v * v;
        if (i) { double t = v - cap[i - 1][0]; d += t * t; }
        if ((v < 0 ? -v : v) > peak) peak = v < 0 ? -v : v;
        nz += v != 0;
    }
    double rms = ncap ? __builtin_sqrt(e / ncap) : 0;
    /* white noise gives diff/energy ~2, silence gives rms 0; tonal audio is well below 1 */
    port_log("[audtest] %u frames: L rms %.0f peak %d nonzero %u%%, diff/energy %.3f -> %s\n", ncap, rms, peak,
             ncap ? nz * 100 / ncap : 0, e > 0 ? d / e : 0.0,
             rms > 100 && e > 0 && d / e < 1.0 ? "PASS (audio, not silence or noise)" : "FAIL");
    port_log("[audtest] ops: adpcm %u resample %u envmix %u loadbuf %u savebuf %u mix %u filter %u overload %u mp3 %u\n",
             aud_stats.by_op[1], aud_stats.by_op[5], aud_stats.by_op[3], aud_stats.by_op[4], aud_stats.by_op[6],
             aud_stats.by_op[12], aud_stats.by_op[14], aud_stats.by_op[0], aud_stats.mp3);
    /* WAV: node writes it to $AUDTEST_WAV; the page plays it */
    static uint8_t hdr[44];
    uint32_t bytes = ncap * 4;
    memcpy(hdr, "RIFF", 4); uint32_t v = 36 + bytes; memcpy(hdr + 4, &v, 4); memcpy(hdr + 8, "WAVEfmt ", 8);
    v = 16; memcpy(hdr + 16, &v, 4); uint16_t s = 1; memcpy(hdr + 20, &s, 2); s = 2; memcpy(hdr + 22, &s, 2);
    v = (uint32_t)rate; memcpy(hdr + 24, &v, 4); v = (uint32_t)rate * 4; memcpy(hdr + 28, &v, 4);
    s = 4; memcpy(hdr + 32, &s, 2); s = 16; memcpy(hdr + 34, &s, 2); memcpy(hdr + 36, "data", 4); memcpy(hdr + 40, &bytes, 4);
    EM_ASM({
        if (typeof process !== 'undefined' && process.env && process.env.AUDTEST_WAV) {
            const fs = require('fs');
            fs.writeFileSync(process.env.AUDTEST_WAV, Buffer.concat([Buffer.from(HEAPU8.subarray($0, $0 + 44)), Buffer.from(HEAPU8.subarray($1, $1 + $2))]));
            console.log('[audtest] wrote ' + process.env.AUDTEST_WAV);
        }
    }, hdr, cap, bytes);
    if (aud_out_open(rate) == 0) {
        for (unsigned i = 0; i < ncap; i++) {
            unsigned nx = (wr + 1) & (RING - 1);
            if (nx == rd) break;
            ring[wr][0] = cap[i][0]; ring[wr][1] = cap[i][1]; wr = nx;
        }
    }
}
