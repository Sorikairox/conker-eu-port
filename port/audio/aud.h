/* Conker audio HLE (session P9): CPU interpreter for the Rare n_audio ABI ("naudio", Conker variant)
 * and the PC audio output. See port/audio/LICENSES.md and docs/port/sessions/P9.md. */
#ifndef PORT_AUD_H
#define PORT_AUD_H
#include <stdint.h>

/* Run one audio command list. `cmds` points to game memory (vbe layout, 64-bit commands = two
 * 32-bit words, which read natively). DRAM addresses in the list are wasm pointers, possibly
 * masked to 24 bits by the game (see aud_dram()). */
void aud_run_alist(const uint32_t *cmds, uint32_t nbytes);

/* Resample LUT: 64 x 4 Q15 taps, read once from the audio ucode data in the user's ROM. */
int aud_init_tables(void);

/* statistics for the log / tests */
struct aud_stats {
    unsigned lists, cmds, unknown, mp3, saves;
    unsigned by_op[16];
};
extern struct aud_stats aud_stats;

/* PC output (aud_out.c): stereo s16 frames at `rate` Hz. aud_out_push reads `frames` stereo
 * frames from a game-memory buffer (big-endian halfwords, vbe layout). */
int aud_out_open(int rate);
void aud_out_push_game(const void *buf, unsigned frames);
unsigned aud_out_queued(void);
#endif
