/* Audio test path (session P9). The scheduler thread that would send the audio thread its retrace
 * messages is still asm, so no M_AUDTASK arrives yet. This drives the game's C n_audio synthesizer
 * directly and runs the command lists it builds through the audio HLE (aud_abi.c):
 *
 *   heap (alHeapInit) -> n_alInit / n_alSynNew (config values from func_10008180 / func_10008F90's asm, two type-6 fx busses)
 *   -> one sound record from the ROM's sound bank -> n_alSynAllocVoice + n_alSynStartVoiceParams
 *   -> n_alAudioFrame (C command-list builder) -> aud_run_alist -> PCM -> WAV / SDL.
 *
 * Sound bank (asset table at ROM 0xAB2240, docs/port/sessions/P9.md): asset (0x17,0) is the ctl
 * (rzip), (0x17,1) the sound records Rare loads on demand, (0x17,2) the sample table. A record is
 * ALSound(+0) / ALEnvelope(+0x10) / ALKeyMap(+0x20) / ALWaveTable(+0x28) / ALADPCMBook with
 * record-relative pointers; the wavetable base is relative to the sample table. The game's loader
 * (func_10009CBC) is asm, so the record is loaded and relocated here the same way func_10012C5C does.
 *
 * Compiled through the vbe pass (port/Makefile BOOT_SRC): game memory semantics. Entry:
 * port_audio_test(record_offset, frames), exported; node: AUDTEST=<hex record> in boot.sh,
 * browser: ?audtest=<hex record>. */
#include <ultra64.h>

void port_glog(const char *fmt, ...);
#define port_log port_glog
void n_alInit(void *g, void *c);
void n_alSynAddPlayer(void *client);
s32 n_alSynAllocVoice(void *voice, void *vc);
void n_alSynStartVoiceParams(void *v, void *w, f32 pitch, s16 vol, u8 pan, u8 fxmix, u8 arg6, f32 arg7, u8 arg8, s32 t);
void n_alSynSetVol(void *v, s16 vol, s32 t);
u64 *n_alAudioFrame(u64 *cmdList, s32 *cmdLen, s16 *outBuf, s32 outLen);
extern u8 D_8003E9E0[]; /* N_ALGlobals of the audio manager */
extern void *n_alGlobals;
extern u8 D_8002B1A4[];

void aud_run_alist(const u32 *cmds, u32 nbytes);
extern int aud_trace;
void aud_wav_append(const void *buf, unsigned frames);
void aud_wav_finish(int rate);

#define ASSET_TABLE 0xAB2240u
#define OUT_RATE 22020 /* func_10008180: 0x5604 */
#define FRAME 736      /* 4 x 184 samples per n_alAudioFrame call */

typedef struct {
    s32 maxVVoices, maxPVoices, maxUpdates, maxFXbusses;
    void *dmaproc;
    void *unk14, *unk18, *unk1C, *unk20;
    s32 unk24; /* sample table ROM address (asset 0x17,2) */
    void *heap;
    s32 outputRate;
    u8 fxTypes[4];
    void *params0, *params1;
} SynConfig;

typedef struct { void *next, *clientData, *handler; s32 callTime, samplesLeft; } Player;

static u8 heap_buf[0x60000] __attribute__((aligned(16)));
static u32 heap[8];
static u8 dma_buf[16][0x400] __attribute__((aligned(16)));
static s32 dma_next;
static u8 record[0x200] __attribute__((aligned(16)));
static u32 voice[16], vconf[4];
static Player player;
static u64 cmds[0x800];
static s16 out[FRAME * 2] __attribute__((aligned(16)));
static u32 sbuf[4] __attribute__((aligned(16)));

/* asset table walk (func_1502AC88 without its cache): entry i of the table at p is {s32 offset, u32
 * info}; the next table / the data is at p + offset */
static u32 asset(u32 a, u32 b, u32 *info) {
    u32 p = ASSET_TABLE;
    osPiRawStartDma(OS_READ, p + 8 * a, sbuf, 8); p += sbuf[0];
    osPiRawStartDma(OS_READ, p + 8 * b, sbuf, 8); p += sbuf[0];
    if (info) *info = sbuf[1];
    return p;
}

/* DMA callback: ROM -> a ring of 1 KB buffers; returns the buffer (a DRAM address for the ucode) */
static s32 pc_dma(s32 addr, s32 len, void *state) {
    u8 *b = dma_buf[dma_next++ & 15];
    (void)state;
    if (len > 0x400) len = 0x400;
    osPiRawStartDma(OS_READ, (u32)addr, b, (u32)len);
    return (s32)b;
}
static void *pc_dma_new(s32 *state) { *state = 0; return (void *)pc_dma; }
static s32 handler(void *client) { (void)client; return 1000000; }
static s32 cb_none(void) { return 0; }

int port_audio_test(u32 rec_off, int frames) {
    SynConfig c;
    u32 info, recs = asset(0x17, 1, &info), tbl = asset(0x17, 2, 0), rec = recs + rec_off;
    u8 *wt;
    s32 len, i, total = 0;

    port_log("[audtest] sound records ROM 0x%X, sample table 0x%X, record +0x%X\n", recs, tbl, rec_off);
    if (n_alGlobals) { port_log("[audtest] synth already initialised; skipped\n"); return 1; }
    alHeapInit(heap, heap_buf, sizeof heap_buf);
    c.maxVVoices = 0x2C; c.maxPVoices = 0x28; c.maxUpdates = 0x40; c.maxFXbusses = 2;
    c.dmaproc = (void *)pc_dma_new;
    c.unk14 = c.unk18 = c.unk1C = c.unk20 = (void *)cb_none;
    c.unk24 = (s32)tbl; c.heap = heap; c.outputRate = OUT_RATE;
    c.fxTypes[0] = c.fxTypes[1] = 6; c.fxTypes[2] = c.fxTypes[3] = 0;
    /* fx parameter tables: func_10008F90 copies D_8002B1A4 (2 x 0x108 bytes) to its stack */
    c.params0 = D_8002B1A4; c.params1 = D_8002B1A4 + 0x108;
    n_alInit(D_8003E9E0, &c);

    /* the record: ALSound / envelope / keymap / wavetable / book, relocated like func_10012C5C */
    osPiRawStartDma(OS_READ, rec, record, sizeof record);
    for (i = 0; i < 3; i++) ((u32 *)record)[i] += (u32)record;
    wt = (u8 *)((u32 *)record)[2];
    len = *(s32 *)(wt + 4);
    *(u32 *)wt += tbl;
    if (*(u32 *)(wt + 0xC)) *(u32 *)(wt + 0xC) += (u32)record;
    *(u32 *)(wt + 0x10) += (u32)record;
    port_log("[audtest] wavetable ROM 0x%X len 0x%X type %d, book order %d npred %d\n", *(u32 *)wt, len, wt[8],
             *(s32 *)*(u32 *)(wt + 0x10), ((s32 *)*(u32 *)(wt + 0x10))[1]);

    player.handler = (void *)handler;
    n_alSynAddPlayer(&player);
    vconf[0] = 0x00400000; /* priority 0x40, fxBus 0 */
    vconf[1] = 0x01000000; /* unityPitch 1 */
    vconf[2] = 0;
    if (!n_alSynAllocVoice(voice, vconf)) { port_log("[audtest] no voice\n"); return 1; }
    n_alSynStartVoiceParams(voice, wt, 1.0f, 0x7FFF, 64, 0, 0, 0.0f, 0, 0);

    for (i = 0; i < frames; i++) {
        s32 n = 0;
        n_alAudioFrame(cmds, &n, out, FRAME);
        if (n > (s32)(sizeof cmds / 8)) { port_log("[audtest] command list overflow (%d)\n", n); return 1; }
        if (i < 2) port_log("[audtest] frame %d: %d commands\n", i, n);
        total += n;
        aud_run_alist((const u32 *)cmds, (u32)n * 8);
        aud_wav_append(out, FRAME);
    }
    port_log("[audtest] %d frames, %d commands\n", frames, total);
    aud_wav_finish(OUT_RATE);
    return 0;
}
