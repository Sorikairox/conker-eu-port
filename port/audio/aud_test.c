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

/* ---------------- voice clip test (session P14) ----------------
 * Drives Conker's voice stream handler func_151F2E88 (matched C) on one clip from the ROM: the
 * game's MP3 decoder (game_221290.c, with port/audio/mp3_pc.c for its asm inner loops) decodes the
 * frames on the CPU and emits MP3ADDY/MP3 (8/7) for the synthesis filterbank, then LOADBUFF, the
 * envelope mixer setup and ENVMIXER. Each call covers 184 samples; the test appends INTERLEAVE +
 * SAVEBUFF and runs the list through the audio HLE (aud_abi.c), like the game's func at init_1FB40.c.
 *
 * Voice clips are asset (0x16, id) (func_1001263C: func_1502B020(&size, 2, 22, id)); the decoder's
 * tables are assets (0x17,4) Huffman tree index, (0x17,5) fast table, (0x17,6) trees, which
 * func_151F2960 loads with the asm asset loader; here they are DMA'd directly. The game's stream
 * DMA callback func_151F3C4C uses the audio DMA table (asm-initialised), so a PC one reads the ROM.
 * Entry: port_voice_test(id, max_calls); node: VOICETEST=<hex id>[:calls]. */
s32 func_151F2E88(s32 count, u64 **cmdp);
void func_151F2960(s32 rom, s32 size);
s32 func_151F3DE0(void);
void func_151F2D6C(s32 vol, s32 t);
void func_151F2DFC(s32 pan, s32 now);
void func_151F2E4C(s32 a, s32 b);
extern u8 **D_800E0E20;
extern u8 *D_800E0E24;
extern s32 D_800E0E28;
extern u8 D_800E0E2C;
extern f32 *D_800E0E30;
extern s32 D_800E0DFC;
extern s32 D_800E0E04;
extern void *D_800E1224;
extern void *D_800E11B8;
extern void *D_800E120C;
extern s16 D_800E11C4, D_800E11C6;
extern void **D_8002BA44;

static u8 mp3_tree_idx[0x100] __attribute__((aligned(16)));
static u8 mp3_fast[0x4400] __attribute__((aligned(16)));
static u8 mp3_trees[0xA800] __attribute__((aligned(16)));
static f32 mp3_pow[0x2000] __attribute__((aligned(16)));
static u8 mp3_state[0x440] __attribute__((aligned(16)));
static u8 env_state[0x80] __attribute__((aligned(16)));
static u8 flt_state[0x40] __attribute__((aligned(16)));
static s16 vout[184 * 2] __attribute__((aligned(16)));
static void *fake_audio_tbl[16];
static u32 voice_rom, voice_size, voice_pos;

static s32 voice_dma(s32 ctx, u8 *dst, s32 len, s32 off) {
    (void)ctx;
    if (off != -1) voice_pos = (u32)off;
    if (voice_pos >= voice_size) return 0;
    if ((u32)len > voice_size - voice_pos) len = (s32)(voice_size - voice_pos);
    if (len <= 0) return 0;
    /* byte copy: dst may be unaligned and is game memory (vbe layout) */
    {
        static u8 tmp[0x1000] __attribute__((aligned(16)));
        s32 done = 0;
        while (done < len) {
            s32 n = len - done > 0x800 ? 0x800 : len - done;
            u32 a = voice_rom + voice_pos + done, a8 = a & ~7u, skip = a - a8;
            s32 i;
            osPiRawStartDma(OS_READ, a8, tmp, (n + skip + 7) & ~7u);
            for (i = 0; i < n; i++) dst[done + i] = tmp[skip + i];
            done += n;
        }
    }
    voice_pos += len;
    return len;
}

int port_voice_test(u32 id, int calls) {
    u32 info, a4, a5, a6, clips;
    s32 i, played = 0;
    void **saved_tbl = D_8002BA44;

    clips = asset(0x16, id, &info);
    voice_rom = clips; voice_size = info & 0xFFFFFF; voice_pos = 0;
    a4 = asset(0x17, 4, &info); osPiRawStartDma(OS_READ, a4, mp3_tree_idx, ((info & 0xFFFFFF) + 7) & ~7u);
    a5 = asset(0x17, 5, &info); osPiRawStartDma(OS_READ, a5, mp3_fast, ((info & 0xFFFFFF) + 7) & ~7u);
    a6 = asset(0x17, 6, &info); osPiRawStartDma(OS_READ, a6, mp3_trees, ((info & 0xFFFFFF) + 7) & ~7u);
    port_log("[voicetest] clip 0x%X: ROM 0x%X size 0x%X; tables 0x%X 0x%X 0x%X (trees 0x%X bytes)\n",
             id, voice_rom, voice_size, a4, a5, a6, info & 0xFFFFFF);

    D_800E0E20 = (u8 **)mp3_tree_idx;
    D_800E0E24 = mp3_fast;
    D_800E0E28 = (s32)mp3_trees;
    D_800E0E30 = mp3_pow;
    if (!func_151F3DE0()) { port_log("[voicetest] mp3dec init failed\n"); return 1; }
    D_800E0E2C = 1; /* tables loaded: func_151F2960 skips its loader */

    D_800E1224 = mp3_state;
    D_800E11B8 = env_state;
    D_800E120C = flt_state;
    fake_audio_tbl[9] = (void *)pc_dma_new; /* func_151F3D78's prefetch DMA */
    D_8002BA44 = fake_audio_tbl;
    D_800E0DFC = (s32)voice_dma;
    func_151F2D6C(0x7FFF, 0);   /* volume */
    func_151F2DFC(64, 1);       /* centre pan */
    func_151F2E4C(0, 0);        /* no filter */
    D_800E11C4 = 0x7FFF;        /* dry */
    D_800E11C6 = 0;             /* wet */
    func_151F2960((s32)voice_rom, (s32)voice_size);

    for (i = 0; i < calls; i++) {
        u64 *p = cmds;
        s32 r;
        if (D_800E0E04 == 3 || D_800E0E04 == 0) break; /* end of stream (state 3 frees the tables) */
        r = func_151F2E88(0xB8, &p);
        if (!r) continue;
        ((u32 *)p)[0] = 0x0D000000; ((u32 *)p)[1] = 0; p++;
        ((u32 *)p)[0] = 0x06000000 | (0x2E0 << 12); ((u32 *)p)[1] = (u32)vout; p++;
        if (played < 3) port_log("[voicetest] call %d: %d commands\n", i, (s32)(p - cmds));
        aud_run_alist((const u32 *)cmds, (u32)(p - cmds) * 8);
        aud_wav_append(vout, 184);
        played++;
    }
    D_8002BA44 = saved_tbl;
    port_log("[voicetest] %d calls, %d played (%d samples), state %d\n", i, played, played * 184, D_800E0E04);
    aud_wav_finish(22050);
    return 0;
}
