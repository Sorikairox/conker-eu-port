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

static int game_rate = 22020; /* P252: the game's AI rate (for the ?det virtual AI clock) */
int aud_out_open(int rate) {
    if (rate > 0) game_rate = rate;
    if (opened) return 0;
#ifdef PORT_RTW
    /* P376 retrowser build: no AudioContext in the worker; the host pulls the ring (port_rtw_audio_drain) */
    opened = 1; out_rate = rate;
    port_log("[aud] retrowser output: ring at %d Hz, stereo, pulled by the host\n", rate);
    return 0;
#endif
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

#ifdef PORT_RTW
static double rtw_game_pushed_at_ms;   /* P377: when the game last made sound (the menu sounds play alone while it is quiet) */
#endif
void aud_out_push_game(const void *buf, unsigned frames) {
    const uint8_t *p = (const uint8_t *)buf;
    pushed += frames;
#ifdef PORT_RTW
    rtw_game_pushed_at_ms = emscripten_get_now();
#endif
    { extern unsigned det_vq_push(unsigned); det_vq_push(frames); }
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
    { /* P258 DIAGNOSTIC ?p258pcm=N: from retrace N, one line per 25 pushes (~1 s): FNV-1a hash of the PCM, rms, peak,
       * nonzero %, RSP mp3 commands so far. With ?det=2 two builds can be compared on the same frames. */
        static int f = -1; static unsigned h = 2166136261u, n, pushes, nz, pk, first; static double e;
        if (f < 0) f = port_flag("p258pcm");
        if (f > 0 && port_frame_count >= (unsigned)f) {
            if (!pushes) first = port_frame_count;
            for (unsigned i = 0; i < 2 * frames; i++) {
                int v = (int16_t)vbe_ld16(p + 2 * i);
                h = (h ^ (unsigned)(v & 0xFFFF)) * 16777619u; e += (double)v * v; nz += v != 0;
                if ((unsigned)(v < 0 ? -v : v) > pk) pk = v < 0 ? -v : v;
            }
            n += frames;
            if (++pushes == 25) {
                port_log("[p258pcm] frames %u-%u: %u samples hash %08x rms %.1f peak %u nonzero %u%% mp3 %u\n", first,
                         port_frame_count, n, h, __builtin_sqrt(e / (2.0 * n)), pk, nz * 50 / n, aud_stats.mp3);
                h = 2166136261u; n = 0; pushes = 0; nz = 0; pk = 0; e = 0;
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

/* P147: AI_LEN as the game sees it. The audio manager (init_8F90.c audio_do_frame) makes a short audio frame
 * (736 instead of 920 samples at 22020 Hz, 25 audio frames/s at PAL 50 Hz VI) when AI_LEN >= 249 samples, so it
 * keeps AI_LEN near 249: on the N64 that is the rest of the DMA in flight. Here the ring is drained by a
 * ScriptProcessor in 2048-frame bursts, so reporting the whole ring would hold it near empty and every burst would
 * underrun. Report the queued frames minus a target latency instead (default 3072 frames, ~140 ms at 22020 Hz;
 * ?ailat=N / PORT_AILAT=N): the ring then settles at ~latency and the burst always finds its 2048 frames. */
/* P252: under ?det (any value) AI_LEN comes from a virtual queue instead of the Web Audio ring: game pushes add to it and
 * it drains at the AI rate per VI retrace (1/50 s PAL, 1/60 otherwise), so the audio manager's frame sizes (and anything
 * timed by them) depend only on the retrace count, not on when the browser's ScriptProcessor ran. */
static int det_on = -1; static double det_vq; static unsigned det_vf;
static void det_vq_drain(void) {
    extern int port_tv_type;
    if (port_frame_count != det_vf) {
        det_vq -= (double)(port_frame_count - det_vf) * game_rate / (port_tv_type == 0 ? 50.0 : 60.0);
        if (det_vq < 0) det_vq = 0;
        det_vf = port_frame_count;
    }
}
unsigned det_vq_push(unsigned frames) {
    if (det_on < 0) det_on = port_flag("det");
    if (!det_on) return 0;
    det_vq_drain(); det_vq += frames;
    if (det_vq > RING - 1) det_vq = RING - 1; /* the real ring drops beyond this too */
    return (unsigned)det_vq;
}
#ifdef PORT_RTW
/* P376 retrowser build: the pull model of spec §4.8. The host calls port_rtw_audio_drain (rtw_audio_drain) once per
 * display frame, plays the frames from its own queue (about 85 ms, with its own rate control) and never calls back.
 * AI_LEN (below) therefore counts what is still to be played: the ring plus a model of the host's queue (the frames
 * handed over, minus the wall time since then at the output rate), so the audio manager's frame sizes follow the
 * real playback as they follow the ScriptProcessor on the page. */
#define RTW_OUT_MAX 8192   /* stereo frames per drain (~370 ms at 22020 Hz; a display frame needs ~370 frames) */
static int16_t rtw_out_buffer[RTW_OUT_MAX][2];
static double rtw_host_queued_frames, rtw_host_aged_at_ms;
static unsigned rtw_drained_total;
static void rtw_host_queue_age(void) {
    double now = emscripten_get_now();
    if (rtw_host_aged_at_ms > 0) {
        rtw_host_queued_frames -= (now - rtw_host_aged_at_ms) * out_rate / 1000.0;
        if (rtw_host_queued_frames < 0) rtw_host_queued_frames = 0;
    }
    rtw_host_aged_at_ms = now;
}
int port_rtw_audio_rate(void) { return game_rate; }
int16_t *port_rtw_audio_buffer(void) { return &rtw_out_buffer[0][0]; }
/* P377 the menu sounds of the worker's game-style menus (rtw_overlay.js rtwSound, the page's gmenu.js GSound): the page
 * plays them on its own AudioContext; the worker has none, so they are mixed into the frames the host pulls. The sound
 * is decoded read-only from the player's ROM by pc_sfx.c port_sfx_decode (never through the game's sound player, whose
 * state is game memory); port_rtw_menu_sound_play copies that PCM into one of four voices, each resampled from its own
 * rate to the output rate. While the game makes no sound (the menu paused it, photo mode) the drain adds silent frames
 * for the wall time since the last drain (port_rtw_audio_drain), so a playing voice is heard on its own. */
#define RTW_MENU_VOICES 4
#define RTW_MENU_VOICE_MAX 32768   /* frames (1.5 s at 22020 Hz; the game's menu sounds are well under 1 s) */
static struct { float pcm[RTW_MENU_VOICE_MAX]; unsigned frames; double pos, step; float gain; } rtw_menu_voice[RTW_MENU_VOICES];
static unsigned rtw_menu_voice_next, rtw_menu_sounds_played;
static double rtw_drained_at_ms;
float *port_sfx_pcm(void);   /* pc_sfx.c */
EMSCRIPTEN_KEEPALIVE int port_rtw_menu_sound_play(int frames, float rate, float gain) {
    if (frames <= 0 || rate <= 0) return 0;
    if (frames > RTW_MENU_VOICE_MAX) frames = RTW_MENU_VOICE_MAX;
    unsigned v = rtw_menu_voice_next++ % RTW_MENU_VOICES;   /* never a pile of clicks: the oldest of four makes room */
    memcpy(rtw_menu_voice[v].pcm, port_sfx_pcm(), (size_t)frames * sizeof(float));
    rtw_menu_voice[v].frames = (unsigned)frames; rtw_menu_voice[v].pos = 0;
    rtw_menu_voice[v].step = rate / (double)out_rate; rtw_menu_voice[v].gain = gain;
    rtw_menu_sounds_played++;
    return 1;
}
EMSCRIPTEN_KEEPALIVE unsigned port_rtw_menu_sounds_played(void) { return rtw_menu_sounds_played; }   /* tests */
static int rtw_menu_voices_playing(void) {
    for (int v = 0; v < RTW_MENU_VOICES; v++) if (rtw_menu_voice[v].pos < rtw_menu_voice[v].frames) return 1;
    return 0;
}
static void rtw_menu_voices_mix(unsigned n) {
    for (int v = 0; v < RTW_MENU_VOICES; v++) {
        if (rtw_menu_voice[v].pos >= rtw_menu_voice[v].frames) continue;
        for (unsigned i = 0; i < n && rtw_menu_voice[v].pos < rtw_menu_voice[v].frames; i++) {
            unsigned k = (unsigned)rtw_menu_voice[v].pos;
            double frac = rtw_menu_voice[v].pos - k;
            float a = rtw_menu_voice[v].pcm[k], b = k + 1 < rtw_menu_voice[v].frames ? rtw_menu_voice[v].pcm[k + 1] : 0.0f;
            int add = (int)((a + (b - a) * (float)frac) * rtw_menu_voice[v].gain * 32767.0f);
            for (int c = 0; c < 2; c++) {
                int s = rtw_out_buffer[i][c] + add;
                rtw_out_buffer[i][c] = (int16_t)(s > 32767 ? 32767 : s < -32768 ? -32768 : s);
            }
            rtw_menu_voice[v].pos += rtw_menu_voice[v].step;
        }
    }
}
int port_rtw_audio_drain(void) {
    unsigned n = aud_out_queued();
    if (n > RTW_OUT_MAX) n = RTW_OUT_MAX;
    for (unsigned i = 0; i < n; i++) {
        rtw_out_buffer[i][0] = ring[rd][0]; rtw_out_buffer[i][1] = ring[rd][1];
        rd = (rd + 1) & (RING - 1);
    }
    {   /* P377: menu sounds (above). While the game makes no sound at all (the menu paused it, photo mode) the host gets
         * silence at the output rate: its queue keeps playing (an empty queue stops, then waits for 85 ms before playing
         * again, which the AI_LEN model above does not know: the game's sound after the pause overfilled it and the host
         * dropped 117 ms), and a menu sound is heard on its own */
        double now = emscripten_get_now();
        if (!n && rtw_game_pushed_at_ms > 0 && now - rtw_game_pushed_at_ms > 120.0 && rtw_drained_at_ms > 0) {
            double since_ms = now - rtw_drained_at_ms;   /* at most 50 ms: after a gap the host's queue would overflow */
            double want = (since_ms > 50.0 ? 50.0 : since_ms) * out_rate / 1000.0;
            n = want > RTW_OUT_MAX ? RTW_OUT_MAX : (unsigned)want;
            memset(rtw_out_buffer, 0, (size_t)n * sizeof rtw_out_buffer[0]);
        }
        if (rtw_menu_voices_playing()) rtw_menu_voices_mix(n);
        rtw_drained_at_ms = now;
    }
    rtw_host_queue_age();
    rtw_host_queued_frames += n;
    if (!rtw_drained_total && n) port_log("[aud] retrowser: first %u frames pulled by the host\n", n);
    rtw_drained_total += n;
    return (int)n;
}
EMSCRIPTEN_KEEPALIVE unsigned port_rtw_audio_drained(void) { return rtw_drained_total; }   /* tests: frames the host pulled */
#endif
unsigned aud_out_ai_len(void) {
    static int lat = -1;
#ifdef PORT_RTW
    if (lat < 0) { lat = port_flag("ailat"); if (lat <= 0) lat = 2048; }   /* ~93 ms: the host's queue + one display frame */
    if (det_on < 0) det_on = port_flag("det");
    if (!det_on) {
        rtw_host_queue_age();
        unsigned q = aud_out_queued() + (unsigned)rtw_host_queued_frames;
        return q > (unsigned)lat ? q - (unsigned)lat : 0;
    }
#endif
    if (lat < 0) { lat = port_flag("ailat"); if (lat <= 0) lat = 3072; }
    if (det_on < 0) det_on = port_flag("det");
    unsigned q = det_on ? (det_vq_drain(), (unsigned)det_vq) : aud_out_queued();
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
