/* P367 native menus: the game's own menu sounds for the page's game-style menus (port/web/gmenu.js GSound: GMenu,
 * GPhoto, GNet), played by the page, never by the game's sound player.
 *
 * Why not sound_play_2d: the game's sound player keeps its voices, its event queue and the sound bank cache in game
 * memory, which the online desync hash, the recorder's replay check and photo mode's snapshot all cover. A menu sound
 * started from the page through it would change that state (and nothing plays while the page pauses the game for its
 * menu anyway: the game's AudioContext is suspended then).
 *
 * So the page decodes the sound itself, read-only: port_sfx_decode(id, cents) finds sound `id` (the number the game
 * passes to sound_play_2d, e.g. 0x500 = the menus' "choose", 0x62D = the pause menu's cursor, 0x4FF = the settings
 * list's move / change) the way n_sndp_play_sound -> snd_cache_load_on_demand do:
 *   - g_sound_bank0 (the first bank of the instrument bank file, init_8180.c) -> instrument 0 (bank +0xC) -> its sound
 *     slot id - 1 (instrument +0x10 + 4 * (id - 1)); the slot holds either the packed ROM reference of the sound's
 *     record (bit 0 set: ROM address = (ref >> 5) & ~7, size = (ref & 0xFF) + 1) or, once the game has loaded it, a
 *     sound cache entry (SndCacheEntry, init_8F90.c) whose +8 keeps that reference;
 *   - the record (ALSound, its offsets relative to the record: envelope, key map, wave table, ADPCM book / loop) is read
 *     from the player's ROM (port_rom), the samples from the ROM's sound table (wave table base + the table's ROM
 *     address, g_sndp_player +0x54, what n_bnkf_patch_sound adds);
 *   - the VADPCM frames are decoded like the audio HLE does (port/audio/aud_abi.c cmd_adpcm), the envelope (attack /
 *     decay volumes and times) applied, and the volume computed like the sound player's SND_VOL155 (play volume x
 *     envelope x sample volume / 127^2 x the sound group's volume g_sndp_group_volumes[keyMin & 0x1F], i.e. the game's
 *     own sound-effects level and the port's "Sound effects" slider), centre pan (x 0.707).
 * The playback rate is the synth's output rate (22020 Hz, init_8180.c) x the key map's base pitch (keyBase / detune as
 * in the sound player's event 0x4000) x the asked pitch in cents.
 *
 * Nothing in game memory is written: the bank / instrument / cache entry words are only read, the ROM is the page's
 * copy, and the output goes to a port buffer (port_sfx_pcm). The page still plays no menu sound during an online
 * session, a recording / replay or under ?netdet (gmenu.js GSound), so those runs are untouched by construction.
 *
 * Page API: n = port_sfx_decode(id, cents) (frames, 0 = not available: no game yet, bad id, not ADPCM), then
 * port_sfx_info() -> float[4] { rate Hz, gain, frames, sound record ROM address } and port_sfx_pcm() -> float frames. */
#include <emscripten.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "pc_mem.h"

void port_log(const char *fmt, ...);
extern unsigned char *port_rom;
extern unsigned port_rom_size;

#define SFX_MAX (22020 * 4)            /* at most 4 s at the base rate (the menu sounds are well under 1 s) */
static float sfx_pcm[SFX_MAX];
static float sfx_info[4];

static uint32_t rbe32(unsigned off) {   /* big-endian ROM word */
    const unsigned char *s = port_rom + off;
    return (uint32_t)s[0] << 24 | (uint32_t)s[1] << 16 | (uint32_t)s[2] << 8 | s[3];
}
static int rbe16(unsigned off) { return (int16_t)(port_rom[off] << 8 | port_rom[off + 1]); }
static uint32_t word(uint32_t wasmAddr) { return wasmAddr >= PORT_WASM_BASE ? *(const uint32_t *)(uintptr_t)wasmAddr : 0; }
static uint32_t gameWord(unsigned n64) { const uint32_t *p = port_n64_to_wasm(n64); return p ? *p : 0; }
static int16_t clamp16(int32_t v) { return v > 32767 ? 32767 : v < -32768 ? -32768 : (int16_t)v; }

EMSCRIPTEN_KEEPALIVE float *port_sfx_info(void) { return sfx_info; }
EMSCRIPTEN_KEEPALIVE float *port_sfx_pcm(void) { return sfx_pcm; }

EMSCRIPTEN_KEEPALIVE int port_sfx_decode(int id, int cents) {
    uint32_t bank, inst, ref, player, tbl, groups, rec, wt, env, km, book, loop, base, len;
    unsigned size, count, order, npred, frames, n, i;
    int16_t coef[8 * 16 * 2];
    int16_t last[16];
    double rate, gain, attack, decay, t, envAt, envDecay;
    int keyBase, detune, keyMax, keyMin, sampleVol, attackVol, decayVol, group;
    int32_t attackTime, decayTime;
    uint32_t loopStart = 0, loopEnd = 0, loopCount = 0;

    memset(sfx_info, 0, sizeof sfx_info);
    if (!port_rom || id <= 0) return 0;
    bank = gameWord(0x8003E708);                 /* g_sound_bank0 */
    inst = word(bank + 0xC);                     /* instArray[0] */
    if (!inst) return 0;
    count = vbe_ld16((const void *)(uintptr_t)(inst + 0xE));
    if ((unsigned)id > count) return 0;
    ref = word(inst + 0x10 + 4 * (id - 1));
    if (!(ref & 1)) ref = word(ref + 8);          /* loaded: the cache entry keeps the ROM reference (romRef) */
    if (!(ref & 1)) return 0;
    rec = (ref >> 5) & ~7u & 0x0FFFFFFF;
    size = (ref & 0xFF) + 1;
    if (rec + size > port_rom_size || size < 0x10) return 0;
    player = gameWord(0x8002BD7C);               /* g_sndp_player */
    tbl = word(player + 0x54);                   /* the sound table's ROM address (SndPlayer155 unk54) */
    groups = gameWord(0x80042C58);               /* g_sndp_group_volumes */

    env = rec + rbe32(rec + 0);
    km = rec + rbe32(rec + 4);
    wt = rec + rbe32(rec + 8);
    sampleVol = port_rom[rec + 0xD];
    if (env + 0xE > rec + size || km + 6 > rec + size || wt + 0x14 > rec + size) return 0;
    attackTime = (int32_t)rbe32(env + 0);
    decayTime = (int32_t)rbe32(env + 4);
    attackVol = port_rom[env + 0xC];
    decayVol = port_rom[env + 0xD];
    keyMin = port_rom[km + 2];
    keyMax = port_rom[km + 3];
    keyBase = port_rom[km + 4];
    detune = (int8_t)port_rom[km + 5];
    base = ((rbe32(wt + 0) + tbl) & 0x0FFFFFFF);
    len = rbe32(wt + 4);
    if (port_rom[wt + 8] != 0) return 0;          /* AL_ADPCM_WAVE only */
    if (rbe32(wt + 0xC)) {
        loop = rec + rbe32(wt + 0xC);
        loopStart = rbe32(loop + 0); loopEnd = rbe32(loop + 4); loopCount = rbe32(loop + 8);
    }
    book = rec + rbe32(wt + 0x10);
    order = rbe32(book + 0); npred = rbe32(book + 4);
    if (order != 2 || npred == 0 || npred > 8 || base + len > port_rom_size) return 0;
    for (i = 0; i < npred * 16; i++) coef[i] = (int16_t)rbe16(book + 8 + 2 * i);

    /* pitch: the sound player's base pitch (key map) x the asked one; flag 0x20 of keyMax's high nibble ignores detune */
    rate = 22020.0 * pow(2.0, ((keyMax & 0x20 ? keyBase * 100 : keyBase * 100 + detune) - 6000 + cents) / 1200.0);
    group = groups ? (int)vbe_ld16((const void *)(uintptr_t)(groups + 2 * (keyMin & 0x1F))) : 0x7FFF;
    gain = (double)sampleVol / 127.0 * (group / 32767.0) * 0.7071 / 32768.0;

    /* decode the whole sample (16 samples per 9-byte frame), then (a loop) repeat the loop part up to 1.5 s */
    frames = len / 9 * 16;
    if (frames > SFX_MAX) frames = SFX_MAX;
    memset(last, 0, sizeof last);
    for (n = 0; n < frames; n += 16) {
        unsigned f = base + n / 16 * 9, hdr = port_rom[f];
        int scale = hdr >> 4;
        const int16_t *bk = coef + ((hdr & 0xF) % npred) * 16;
        int32_t r[16];
        for (i = 0; i < 8; i++) {
            unsigned b = port_rom[f + 1 + i];
            int hi = (int)(int8_t)(b & 0xF0) >> 4, lo = (int)(int8_t)(b << 4) >> 4;
            r[2 * i] = scale <= 12 ? hi << scale : hi << 12;
            r[2 * i + 1] = scale <= 12 ? lo << scale : lo << 12;
        }
        for (int h = 0; h < 2; h++) {
            int32_t p2 = h ? last[6] : last[14], p1 = h ? last[7] : last[15];
            const int32_t *rr = r + 8 * h;
            for (i = 0; i < 8; i++) {
                int32_t acc = bk[i] * p2 + bk[8 + i] * p1 + (rr[i] << 11);
                for (unsigned k = 0; k < i; k++) acc += bk[8 + i - 1 - k] * rr[k];
                last[8 * h + i] = clamp16(acc >> 11);
            }
        }
        for (i = 0; i < 16 && n + i < SFX_MAX; i++) sfx_pcm[n + i] = last[i];
    }
    if (loopCount && loopEnd > loopStart && loopEnd <= frames) {
        unsigned want = (unsigned)(rate * 1.5);
        if (want > SFX_MAX) want = SFX_MAX;
        for (n = loopEnd; n < want; n++) sfx_pcm[n] = sfx_pcm[loopStart + (n - loopEnd) % (loopEnd - loopStart)];
        frames = n;
    }
    /* envelope: 0 -> attackVolume over attackTime, -> decayVolume over decayTime (-1 = hold), in microseconds of
     * playback; after a loop ends a 50 ms release */
    attack = attackTime > 0 ? attackTime / 1e6 : 0;
    decay = decayTime > 0 ? decayTime / 1e6 : -1;
    for (n = 0; n < frames; n++) {
        t = n / rate;
        if (t < attack) envAt = attackVol * t / attack;
        else if (decay < 0) envAt = attackVol;
        else if (t < attack + decay) envDecay = (t - attack) / decay, envAt = attackVol + (decayVol - attackVol) * envDecay;
        else envAt = decayVol;
        if (loopCount && frames - n < (unsigned)(rate * 0.05)) envAt *= (frames - n) / (rate * 0.05);
        sfx_pcm[n] = (float)(sfx_pcm[n] * gain * envAt / 127.0);
    }
    sfx_info[0] = (float)rate;
    sfx_info[1] = (float)gain;
    sfx_info[2] = (float)frames;
    sfx_info[3] = (float)rec;
    {
        static int nlog;
        if (nlog++ < 16)
            port_log("[sfx] 0x%X: record rom %X (%u bytes), table %X + %X len %u (%u frames%s), rate %.0f Hz, vol %d / env %d->%d "
                     "(%d / %d us) / group %d\n", id, rec, size, tbl, base - tbl, len, frames, loopCount ? ", looped" : "", rate,
                     sampleVol, attackVol, decayVol, attackTime, decayTime, group);
    }
    return (int)frames;
}
