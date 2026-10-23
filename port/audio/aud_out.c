/* PC audio output (session P9): a ring buffer of stereo s16 frames drained by the browser.
 * P9 used emscripten's built-in SDL 1.2 audio, P11 switched to the SDL2 port; P14 found with a
 * headless-Chrome probe (port/web/audprobe.sh) that the SDL2 build never created an AudioContext
 * (SDL_OpenAudio "succeeded" with 0 Hz / 0 channels: the SDL2 port in the image has no Emscripten
 * audio driver linked, so SDL fell back to a dummy device) and nothing was played. Since P14 the
 * output is a direct Web Audio ScriptProcessorNode (EM_JS below) that reads the ring straight
 * from the wasm heap and advances the read index, so no wasm call happens on the audio callback
 * (safe while ASYNCIFY fibers are suspended). In node (no AudioContext) the device stays closed and
 * pushed audio is only counted. */
#include <stdint.h>
#include <string.h>
#include <emscripten.h>
#include "aud.h"
#include "../ultra/pc_mem.h"

void port_log(const char *fmt, ...);
int port_flag(const char *name);
extern unsigned port_frame_count;

#define RING (1u << 17) /* stereo frames, ~6 s at 22 kHz */
static int16_t ring[RING][2];
static volatile unsigned rd, wr;
static int opened, out_rate = 22020;
static unsigned pushed, dropped;
static volatile unsigned underrun; /* P147: output frames the Web Audio callback found the ring empty (JS increments) */
static unsigned ringin;            /* P147: frames written into the ring (consumed = ringin - queued) */

/* Web Audio sink: ScriptProcessorNode(2048 frames, stereo) pulling from ring[rd..wr). The page's
 * first click / key resumes a context that the autoplay policy started suspended. Returns the
 * context's rate (Web Audio resamples from `rate` when it cannot run at it) or 0. */
/* The __port_ prefix keeps port/tools/gen_stubs.py from stubbing this EM_JS import as "missing". */
EM_JS(int, __port_web_audio_open, (int rate, int ring, int rdp, int wrp, int mask, int urp), {
  try {
    var G = globalThis, C = G.AudioContext || G.webkitAudioContext;
    if (!C) return 0;
    var ctx;
    try { ctx = new C({ sampleRate: rate }); } catch (e) { ctx = new C(); }
    var node = ctx.createScriptProcessor(2048, 0, 2);
    var src = ctx.sampleRate === rate ? 1 : rate / ctx.sampleRate;
    var pos = 0, started = 0;
    node.onaudioprocess = function (e) {
        var L = e.outputBuffer.getChannelData(0), R = e.outputBuffer.getChannelData(1);
        var r = HEAPU32[rdp >> 2], w = HEAPU32[wrp >> 2], base = ring >> 1;
        for (var i = 0; i < L.length; i++) {
            if (r === w) { L[i] = R[i] = 0; if (started) HEAPU32[urp >> 2]++; continue; }
            started = 1;
            L[i] = HEAP16[base + 2 * r] / 32768; R[i] = HEAP16[base + 2 * r + 1] / 32768;
            pos += src;
            while (pos >= 1 && r !== w) { pos -= 1; r = (r + 1) & mask; }
        }
        HEAPU32[rdp >> 2] = r;
    };
    /* P27: volume (the page's slider sets globalThis.portVolume and gain.gain) */
    var gain = ctx.createGain();
    gain.gain.value = typeof G.portVolume === 'number' ? G.portVolume : 1;
    node.connect(gain); gain.connect(ctx.destination);
    globalThis.portAudio = { ctx: ctx, node: node, gain: gain };
    /* P27: the page (main.js armAudio) resumes it on the first click / key press; a context created
     * after that gesture starts at once (sticky user activation). */
    if (ctx.state !== 'running') ctx.resume().catch(function () {});
    if (typeof G.portAudioReady === 'function') G.portAudioReady(ctx);
    return ctx.sampleRate | 0;
  } catch (e) { globalThis.portAudioErr = String(e && e.stack || e); return -1; }
});

int aud_out_open(int rate) {
    if (opened) return 0;
    int has_ctx = EM_ASM_INT({ return (typeof AudioContext !== 'undefined' || typeof webkitAudioContext !== 'undefined') ? 1 : 0; });
    if (!has_ctx) { port_log("[aud] no AudioContext (node): output disabled, %d Hz\n", rate); opened = -1; return -1; }
    int got = __port_web_audio_open(rate, (int)(uintptr_t)ring, (int)(uintptr_t)&rd, (int)(uintptr_t)&wr, (int)(RING - 1), (int)(uintptr_t)&underrun);
    if (got <= 0) {
        port_log("[aud] Web Audio open failed (%d): %s\n", got, got < 0 ? "exception, see globalThis.portAudioErr" : "no AudioContext");
        opened = -1; return -1;
    }
    opened = 1; out_rate = rate;
    port_log("[aud] Web Audio open: ring at %d Hz, context %d Hz, stereo, ScriptProcessor 2048\n", rate, got);
    return 0;
}

void aud_out_push_game(const void *buf, unsigned frames) {
    const uint8_t *p = (const uint8_t *)buf;
    pushed += frames;
    { /* P110 DIAGNOSTIC ?p110aud=1 (node PORT_P110AUD=1): game output level per ~1 s window (left channel) */
        static int f = -1; static double e; static int pk; static unsigned n, nz;
        if (f < 0) f = port_flag("p110aud");
        if (f) {
            for (unsigned i = 0; i < frames; i++) {
                int v = (int16_t)vbe_ld16(p + 4 * i); e += (double)v * v; nz += v != 0;
                if ((v < 0 ? -v : v) > pk) pk = v < 0 ? -v : v;
            }
            n += frames;
            if (n >= 22020) {
                port_log("[p110aud] frame %u: %u samples rms %.0f peak %d nonzero %u%%\n", port_frame_count, n,
                         __builtin_sqrt(e / n), pk, nz * 100 / n);
                e = 0; pk = 0; n = 0; nz = 0;
            }
        }
    }
    for (unsigned i = 0; i < frames; i++) {
        unsigned nx = (wr + 1) & (RING - 1);
        if (nx == rd) { dropped += frames - i; break; }
        ring[wr][0] = (int16_t)vbe_ld16(p + 4 * i);
        ring[wr][1] = (int16_t)vbe_ld16(p + 4 * i + 2);
        wr = nx; ringin++;
    }
    if (opened != 1) rd = wr; /* no device: discard */
}

unsigned aud_out_queued(void) { return (wr - rd) & (RING - 1); }

/* P147: AI_LEN as the game sees it. The audio manager (init_8F90.c func_100095A0) makes a short audio frame
 * (736 instead of 920 samples at 22020 Hz, 25 audio frames/s at PAL 50 Hz VI) when AI_LEN >= 249 samples, so it
 * keeps AI_LEN near 249: on the N64 that is the rest of the DMA in flight. Here the ring is drained by a
 * ScriptProcessor in 2048-frame bursts, so reporting the whole ring would hold it near empty and every burst would
 * underrun. Report the queued frames minus a target latency instead (default 3072 frames, ~140 ms at 22020 Hz;
 * ?ailat=N / PORT_AILAT=N): the ring then settles at ~latency and the burst always finds its 2048 frames. */
unsigned aud_out_ai_len(void) {
    static int lat = -1;
    if (lat < 0) { lat = port_flag("ailat"); if (lat <= 0) lat = 3072; }
    unsigned q = aud_out_queued();
    return q > (unsigned)lat ? q - (unsigned)lat : 0;
}

/* P147 DIAGNOSTIC ?p147pace=N (node PORT_P147PACE=N): every N retraces (1 = 250) log the retrace rate against the
 * wall clock and the audio clock (frames the Web Audio callback consumed), the ring level range in the window,
 * underrun output frames and dropped input frames. Target: ~50.0 retraces per audio second (PAL), stable ring. */
void port_pace_report(void) {
    static int f = -1; static unsigned v0, c0, u0, d0, p0, qmin = ~0u, qmax, nwin; static double t0;
    if (f < 0) { f = port_flag("p147pace"); if (f == 1) f = 250; }
    if (f <= 0) return;
    unsigned q = aud_out_queued();
    if (q < qmin) qmin = q;
    if (q > qmax) qmax = q;
    if (port_frame_count % (unsigned)f) return;
    double t = emscripten_get_now();
    unsigned cons = ringin - q;
    if (nwin++ && t > t0) {
        double vs = (port_frame_count - v0) * 1000.0 / (t - t0), as = (cons - c0) / (double)out_rate;
        static double tstart; if (!tstart) tstart = t0;
        port_log("[p147] vi %u t %.1f s: %.2f vi/s wall, audio %u frames consumed = %.2f vi per audio s, pushed %u (%.1f/vi), ring %u (min %u max %u), "
                 "underrun %u, dropped %u\n", port_frame_count, (t - tstart) / 1000.0, vs, cons - c0, as > 0 ? (port_frame_count - v0) / as : 0.0,
                 pushed - p0, (double)(pushed - p0) / (port_frame_count - v0), q, qmin, qmax, underrun - u0, dropped - d0);
    }
    v0 = port_frame_count; c0 = cons; u0 = underrun; d0 = dropped; p0 = pushed; t0 = t; qmin = ~0u; qmax = 0;
}

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

/* Page test mode &audonly=1 (P14, port/web/audprobe.sh): load the game's data segments without
 * starting the game threads, so an audio test can run on a page that stays responsive. */
int port_mem_load(void);
int port_audio_prepare(void) {
    static int state;
    if (!state) state = port_mem_load() == 0 ? 1 : -1;
    return state;
}
