/* PC versions of the hand-written asm in Conker's MP3 voice decoder (session P14).
 *
 * The decoder itself (game_221290.c, Perfect Dark's mp3 library) is matched C. Its inner loops are
 * hand-written asm in game_eu_226870 / game_eu_227BF0, which the port links as stubs. Without them a
 * voice stream decodes to nothing, so this file supplies C equivalents:
 *
 *   func_151F9150  get bits            (P199: now game C, game_eu_226870.c)
 *   func_151F9184  Huffman big_values  translated from the asm (fast byte table + tree walk)
 *   func_151F933C  Huffman count1      translated from the asm
 *   func_151F94E0  IMDCT, long blocks  written from the MPEG-1 Layer III description (ISO 11172-3)
 *   func_151FA3E0  IMDCT, short blocks idem
 *
 * The register-level helpers func_151F9060 (one Huffman symbol) and func_151F911C (bits for a
 * caller-held bit position) use private register conventions and are folded in here.
 *
 * Compiled through the vbe pass (port/Makefile BOOT_SRC), so game memory reads are plain C.
 * TEMPORARY, like the overrides in port/boot/pc_overrides.c: remove a function here when the port
 * branch converts its asm (game_eu_226870.c / game_eu_227BF0.c), or the link sees two definitions.
 *
 * Asm semantics checked against the IMDCT asm: frequency inversion (odd subbands, odd outputs) is
 * done inside func_151F94E0 / func_151FA3E0 (`andi a1, 1`), the window is arg4 (long blocks), the
 * output is window * imdct + overlap (arg3) and the new overlap goes back to arg3. */
#include <ultra64.h>
#include <math.h>

extern u8 **D_800E0E20; /* Huffman trees, per table (asset 0x17,4 relocated onto asset 0x17,6) */
extern u8 *D_800E0E24;  /* fast table: [tbl << 8 | next 8 bits] = y << 4 | x, +0x2200 = code length */

/* ---- bit reader: buf is the stream buffer, pos an absolute bit position ---- */
static u32 peek32(u8 *buf, s32 pos) {
    u8 *p = buf + ((u32)pos >> 3);
    return ((u32)p[0] << 24 | (u32)p[1] << 16 | (u32)p[2] << 8 | p[3]) << (pos & 7);
}
/* srlv uses the low 5 bits of the shift: n == 0 gives the whole word, as in the asm */
static u32 getbits(u8 *buf, s32 *pos, s32 n) {
    u32 v = peek32(buf, *pos) >> ((32 - n) & 31);
    *pos += n;
    return v;
}

/* func_151F9150 (get bits): removed in P199, the game C (P190, game_eu_226870.c mp3util_get_bits) defines it now */

/* P258: port-b P251 made func_151F9184 / func_151F933C (Huffman, with the static helpers 9060 / 911C) and func_151F94E0
 * (IMDCT 36) game C (game_eu_226870.c, bit-exact with the asm). These P14 PC versions are kept for A/B runs only:
 * build with -DP258_MP3_PC_OLD and without the game C ones. */
#ifdef P258_MP3_PC_OLD
/* func_151F9060: one Huffman symbol of table `tbl`. Returns the first value, *second gets the other. */
static s32 huff(u8 *buf, s32 *pos, s32 tbl, s32 *second) {
    u8 *p = buf + ((u32)*pos >> 3);
    s32 sh = *pos & 7;
    u32 byte8 = (((u32)p[0] << 8 | p[1]) >> (8 - sh)) & 0xFF;
    u32 idx = ((u32)tbl << 8) + byte8;
    u32 len = D_800E0E24[0x2200 + idx];
    u8 *node;
    u32 cur, mask;

    if (len != 0) {
        u32 v = D_800E0E24[idx];
        *pos += len;
        *second = v >> 4;
        return v & 0xF;
    }
    /* tree walk, one bit per step: node[0] / node[1] = child offset in 4-byte units for bit 0 / 1,
     * node[2] = first value (-1: internal node), node[3] = second value */
    node = D_800E0E20[tbl];
    cur = p[0];
    mask = 0x80u >> sh;
    for (;;) {
        node += (u32)((cur & mask) ? node[1] : node[0]) << 2;
        mask >>= 1;
        if (mask == 0) { mask = 0x80; p++; cur = p[0]; }
        *pos += 1;
        if ((s8)node[2] != -1) break;
    }
    *second = (s8)node[3];
    return (s8)node[2];
}

/* big_values region: pairs (x, y) with optional linbits and sign bits; values go to *out (s16
 * pairs), sign flags to *sgn (bytes). Returns the new sample index. */
s32 func_151F9184(u8 *buf, s32 *bitpos, s32 tbl, s32 idx, s32 linbits, s32 end, s16 **out, u8 **sgn) {
    s32 pos = *bitpos;
    s16 *o = *out;
    u8 *s = *sgn;

    while (end - idx > 0) {
        s32 y, x = huff(buf, &pos, tbl, &y);
        if (linbits != 0 && x == 15) x = (s32)getbits(buf, &pos, linbits) + 15;
        s[0] = x != 0 ? (u8)getbits(buf, &pos, 1) : 0;
        if (linbits != 0 && y == 15) y = (s32)getbits(buf, &pos, linbits) + 15;
        o[0] = (s16)x;
        o[1] = (s16)y;
        o += 2;
        s[1] = y != 0 ? (u8)getbits(buf, &pos, 1) : 0;
        idx += 2;
        s += 2;
    }
    *bitpos = pos;
    *out = o;
    *sgn = s;
    return idx;
}

/* count1 region: quadruples (v, w, x, y) of 0/1 from table 32/33, then up to 4 sign bits. The asm
 * reads 4 bits and gives back the unused ones. Stops at bit `endbit` or sample 576. */
s32 func_151F933C(u8 *buf, s32 *bitpos, s32 tbl, s32 idx, s32 endbit, s16 **out, u8 **sgn) {
    s32 pos = *bitpos;
    s16 *o = *out;
    u8 *s = *sgn;

    while (endbit - pos > 0 && idx < 0x240) {
        s32 dummy, v = huff(buf, &pos, tbl, &dummy);
        s32 q[4], k, used = 0;
        u32 bits;
        q[0] = (v >> 3) & 1; q[1] = (v >> 2) & 1; q[2] = (v >> 1) & 1; q[3] = v & 1;
        for (k = 0; k < 4; k++) o[k] = (s16)q[k];
        bits = getbits(buf, &pos, 4);
        for (k = 0; k < 4; k++) {
            if (q[k]) { s[k] = (u8)((bits >> (3 - used)) & 1); used++; }
            else s[k] = 0;
        }
        pos -= 4 - used;
        o += 4;
        s += 4;
        idx += 4;
    }
    *bitpos = pos;
    *out = o;
    *sgn = s;
    return idx;
}

#endif /* P258_MP3_PC_OLD */

/* ---- IMDCT + windowing + overlap-add + frequency inversion ---- */
static f32 cos36[36][18], cos12[12][6], win12[12];
static s32 tabs_ok;

static void imdct_tables(void) {
    s32 i, k;
    for (i = 0; i < 36; i++)
        for (k = 0; k < 18; k++) cos36[i][k] = (f32)cos(M_PI / 72.0 * (2 * i + 1 + 18) * (2 * k + 1));
    for (i = 0; i < 12; i++) {
        for (k = 0; k < 6; k++) cos12[i][k] = (f32)cos(M_PI / 24.0 * (2 * i + 1 + 6) * (2 * k + 1));
        win12[i] = (f32)sin(M_PI / 12.0 * (i + 0.5));
    }
    tabs_ok = 1;
}

static void overlap_out(const f32 *z, s32 sb, f32 *out, f32 *prev) {
    s32 i;
    for (i = 0; i < 18; i++) {
        f32 v = z[i] + prev[i];
        out[i] = (sb & 1) && (i & 1) ? -v : v;
        prev[i] = z[18 + i];
    }
}

#ifdef P258_MP3_PC_OLD
void func_151F94E0(f32 *in, s32 sb, f32 *out, f32 *prev, f32 *win) {
    f32 z[36];
    s32 i, k;
    if (!tabs_ok) imdct_tables();
    for (i = 0; i < 36; i++) {
        f32 acc = 0.0f;
        for (k = 0; k < 18; k++) acc += in[k] * cos36[i][k];
        z[i] = acc * win[i];
    }
    overlap_out(z, sb, out, prev);
}

#endif /* P258_MP3_PC_OLD */

/* three 12-point IMDCTs over the interleaved short-block values in[w + 3k], each windowed and
 * placed at 6 + 6w in the 36-sample block */
void func_151FA3E0(f32 *in, s32 sb, f32 *out, f32 *prev) {
    f32 z[36];
    s32 i, k, w;
    if (!tabs_ok) imdct_tables();
    for (i = 0; i < 36; i++) z[i] = 0.0f;
    for (w = 0; w < 3; w++)
        for (i = 0; i < 12; i++) {
            f32 acc = 0.0f;
            for (k = 0; k < 6; k++) acc += in[w + 3 * k] * cos12[i][k];
            z[6 + 6 * w + i] += acc * win12[i];
        }
    overlap_out(z, sb, out, prev);
}
