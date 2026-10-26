#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
// P251: readable C for the MP3 Huffman group (hand-written asm func_151F9060 / func_151F911C / func_151F9184 /
// func_151F933C). The two leaf routines used a private register ABI (a0 = byte pointer, t0 = bit position, s1 = bit
// count, s0 = tree, s5 = lookup base, a2 = table; results in v0 / t1) and were only called by 9184 / 933C, so they
// are static helpers on a bit reader here. The asm's a0 is always buf + (t0 >> 3), so only the bit position is kept.
typedef struct {
    u8 *buf;    /* stream start */
    u32 pos;    /* bit position */
} HuffReader;

extern u8 **D_800E0E20;     /* per table: Huffman tree (NULL for the unused tables), 4-byte nodes {u8 left, u8 right,
                               s8 x, s8 y}; child = node + 4 * offset; x == -1 marks an inner node */
extern u8 *D_800E0E24;      /* [table][256] fast lookup by the next 8 bits: +0 = (y << 4) | x, +0x2200 = code
                               length (0 = longer than 8 bits: walk the tree) */

// huff_get_bits (func_151F911C): the next n bits MSB first from the unaligned big-endian word at the read
// position (lwl / lwr); the shifts are mod 32 like sllv / srlv.
static u32 huff_get_bits(HuffReader *r, s32 n) {
    u8 *p = r->buf + (r->pos >> 3);
    u32 w = ((u32) p[0] << 24) | ((u32) p[1] << 16) | ((u32) p[2] << 8) | p[3];

    w <<= r->pos & 7;
    r->pos += n;
    return w >> ((32 - n) & 0x1F);
}

// huff_get_bit: one bit (the sign-bit reads inlined in func_151F9184).
static s32 huff_get_bit(HuffReader *r) {
    s32 b = (r->buf[r->pos >> 3] >> (7 - (r->pos & 7))) & 1;

    r->pos++;
    return b;
}

// huff_decode_pair (func_151F9060): decodes one Huffman code of table `table` into (x, y). Fast path: the next 8
// bits index the lookup; a non-zero length consumes that many bits. Else walk the tree bit by bit from the root.
static void huff_decode_pair(HuffReader *r, s32 table, s32 *x, s32 *y) {
    u8 *p = r->buf + (r->pos >> 3);
    s32 k = (table << 8) + ((((p[0] << 8) | p[1]) >> (8 - (r->pos & 7))) & 0xFF);
    s32 len = D_800E0E24[0x2200 + k];
    u8 *node;

    if (len != 0) {
        r->pos += len;
        *x = D_800E0E24[k] & 0xF;
        *y = D_800E0E24[k] >> 4;
        return;
    }
    node = D_800E0E20[table];
    do {
        node += (huff_get_bit(r) ? node[1] : node[0]) * 4;
    } while ((s8) node[2] == -1);
    *x = (s8) node[2];
    *y = (s8) node[3];
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_226870/func_151F9060.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_226870/func_151F911C.s")
#endif

#ifdef NON_MATCHING
/*
 * mp3util_get_bits: P190 readable C for the hand-written func_151F9150.s. Returns the next `numbits` bits of buffer
 * at bit *offset (MSB first; the asm reads the big-endian word at byte *offset >> 3 unaligned with lwl / lwr) and
 * advances *offset. The right shift is (32 - numbits) mod 32 (srlv), so numbits 0 returns the whole shifted word.
 */
s32 func_151F9150(u8 *buffer, s32 *offset, s32 numbits) {
    u32 pos = *offset;
    u8 *p = buffer + (pos >> 3);
    u32 word = ((u32)p[0] << 24) | ((u32)p[1] << 16) | ((u32)p[2] << 8) | p[3];

    word <<= pos & 7;
    *offset = pos + numbits;
    return word >> ((32 - numbits) & 0x1F);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_226870/func_151F9150.s")
#endif

#ifdef NON_MATCHING
// huff_decode_big_values: P251 readable C for func_151F9184 (hand asm). Decodes (x, y) pairs with table `table`
// from line i up to `end` (exclusive, two lines per pair; nothing when end <= i). A value 15 of a table with
// linbits is extended by `linbits` raw bits (+ 15); each non-zero value is followed by its sign bit (x's sign is
// read before y's extension). Writes the values to *out (s16 pairs) and the sign flags to *signs (one byte per
// value, 0 for a zero value), advances *bitpos, *out and *signs, returns the new line index. Caller:
// mp3dec_read_granule (game_221290), once per region.
s32 func_151F9184(u8 *buf, s32 *bitpos, s32 table, s32 i, s32 linbits, s32 end, s16 **out, u8 **signs) {
    HuffReader r;
    s16 *o = *out;
    u8 *s = *signs;
    s32 x, y;

    r.buf = buf;
    r.pos = *bitpos;
    while (end - i > 0) {
        huff_decode_pair(&r, table, &x, &y);
        if (linbits != 0 && x == 15) {
            x = huff_get_bits(&r, linbits) + 15;
        }
        s[0] = (x != 0) ? huff_get_bit(&r) : 0;
        if (linbits != 0 && y == 15) {
            y = huff_get_bits(&r, linbits) + 15;
        }
        o[0] = x;
        o[1] = y;
        o += 2;
        s[1] = (y != 0) ? huff_get_bit(&r) : 0;
        i += 2;
        s += 2;
    }
    *bitpos = r.pos;
    *out = o;
    *signs = s;
    return i;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_226870/func_151F9184.s")
#endif

#ifdef NON_MATCHING
// huff_decode_count1: P251 readable C for func_151F933C (hand asm). Decodes quadruples (four one-bit values
// v, w, x, y packed in the low nibble of table `table`'s result) from line i while i < 576 and the bit position
// is before `endBit` (both tested before every quadruple). Reads 4 bits ahead for the signs, takes one per non-zero
// value (MSB first) and gives the unused ones back. Writes 4 s16 values and 4 sign flags per quadruple, advances
// *bitpos, *out and *signs, returns the new line index. Caller: mp3dec_read_granule (game_221290).
s32 func_151F933C(u8 *buf, s32 *bitpos, s32 table, s32 i, s32 endBit, s16 **out, u8 **signs) {
    HuffReader r;
    s16 *o = *out;
    u8 *s = *signs;
    s32 q, unused;
    s32 v[4];
    u32 bits;
    s32 k, n;

    r.buf = buf;
    r.pos = *bitpos;
    while (endBit - (s32) r.pos > 0 && i < 576) {
        huff_decode_pair(&r, table, &q, &unused);
        for (k = 0; k < 4; k++) {
            v[k] = (q >> (3 - k)) & 1;
            o[k] = v[k];
        }
        bits = huff_get_bits(&r, 4);
        n = 3;
        for (k = 0; k < 4; k++) {
            if (v[k] != 0) {
                v[k] &= bits >> n;
                n--;
            }
            s[k] = v[k];
        }
        r.pos -= n + 1;     /* give back the sign bits not used */
        o += 4;
        s += 4;
        i += 4;
    }
    *bitpos = r.pos;
    *out = o;
    *signs = s;
    return i;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_226870/func_151F933C.s")
#endif

#ifdef NON_MATCHING
// mp3_imdct36_hybrid: P251 readable C for func_151F94E0. Long-block (36-point) IMDCT of one subband for the MP3
// hybrid synthesis, then windowing and overlap-add (the fast algorithm of maplay / JLayer's inv_mdct, 9-point DCTs
// on the even and odd inputs). `in` holds the 18 dequantised spectral lines of subband `sb` and is used as scratch
// (prefix sums). `out` gets the 18 output samples (window * IMDCT + the previous granule's overlap `prev`; the odd
// samples of odd subbands are negated: frequency inversion), `prev` gets the new overlap. `win` is one of the
// game's four sine_block[36] windows. Caller: mp3dec_decode_frame (game_221290).
// The expressions keep the asm's evaluation order and its (signed) constants so the float results are bit-exact.
void func_151F94E0(f32 *in, s32 sb, f32 *out, f32 *prev, f32 *win) {
    f32 t[18];      /* 0x00 9-point DCT results: even part t[0..8], odd part t[9..17] */
    f32 res[18];    /* 0x48 the 18 independent IMDCT outputs */
    f32 i00, iip12, i66;
    f32 a, b;
    s32 i;

    for (i = 17; i > 0; i--) {
        in[i] += in[i - 1];
    }
    for (i = 17; i > 1; i -= 2) {
        in[i] += in[i - 2];
    }

    /* 9-point IDCT of the even inputs */
    i00 = in[0] + in[0];
    iip12 = i00 + in[12];
    t[0] = in[4] * 1.87938523f + in[8] * 1.53208888f + in[16] * 0.347296357f + iip12;
    t[2] = in[4] * -0.347296357f + in[8] * -1.87938523f + in[16] * 1.53208888f + iip12;
    t[3] = in[4] * -1.53208888f + in[8] * 0.347296357f + in[16] * -1.87938523f + iip12;
    t[1] = i00 + in[4] - in[8] - in[12] - in[12] - in[16];
    t[4] = in[0] - in[4] + in[8] - in[12] + in[16];
    i66 = in[6] * 1.73205078f;
    t[5] = in[2] * 1.96961546f + in[10] * 1.28557527f + in[14] * 0.684040308f + i66;
    i66 = -i66;
    t[6] = in[2] * 1.28557527f + in[10] * -0.684040308f + in[14] * 1.96961546f + i66;
    t[7] = in[2] * 0.684040308f + in[10] * 1.96961546f + in[14] * -1.28557527f + i66;
    t[8] = (in[2] - in[10] - in[14]) * 1.73205078f;

    /* 9-point IDCT of the odd inputs */
    i00 = in[1] + in[1];
    iip12 = i00 + in[13];
    t[9] = in[5] * 1.87938523f + in[9] * 1.53208888f + in[17] * 0.347296357f + iip12;
    t[11] = in[5] * -0.347296357f + in[9] * -1.87938523f + in[17] * 1.53208888f + iip12;
    t[12] = in[5] * -1.53208888f + in[9] * 0.347296357f + in[17] * -1.87938523f + iip12;
    t[10] = i00 + in[5] - in[9] - in[13] - in[13] - in[17];
    t[13] = in[1] - in[5] + in[9] - in[13] + in[17];
    i66 = in[7] * 1.73205078f;
    t[14] = in[3] * 1.96961546f + in[11] * 1.28557527f + in[15] * 0.684040308f + i66;
    i66 = -i66;
    t[15] = in[3] * 1.28557527f + in[11] * -0.684040308f + in[15] * 1.96961546f + i66;
    t[16] = in[3] * 0.684040308f + in[11] * 1.96961546f + in[15] * -1.28557527f + i66;
    t[17] = (in[3] - in[11] - in[15]) * 1.73205078f;

    /* butterflies: res[k] and res[17 - k] from the even (a) and scaled odd (b) parts */
    a = t[0] + t[5];
    b = (t[9] + t[14]) * 0.501909912f;
    res[0] = (a + b) * -0.25023818f;
    res[17] = (a - b) * -5.7313962f;
    a = t[1] + t[8];
    b = (t[10] + t[17]) * 0.517638087f;
    res[1] = (a + b) * -0.252157241f;
    res[16] = (a - b) * -1.91532445f;
    a = t[2] + t[6];
    b = (t[11] + t[15]) * 0.551688969f;
    res[2] = (a + b) * -0.256069869f;
    res[15] = (a - b) * -1.1550566f;
    a = t[3] + t[7];
    b = (t[12] + t[16]) * 0.610387266f;
    res[3] = (a + b) * -0.262132287f;
    res[14] = (a - b) * -0.831377387f;
    a = t[3] - t[7];
    b = (t[12] - t[16]) * 0.871723413f;
    res[5] = (a + b) * -0.28184548f;
    res[12] = (a - b) * -0.541420162f;
    a = t[2] - t[6];
    b = (t[11] - t[15]) * 1.18310082f;
    res[6] = (a + b) * -0.296422273f;
    res[11] = (a - b) * -0.465289742f;
    a = t[1] - t[8];
    b = (t[10] - t[17]) * 1.93185163f;
    res[7] = (a + b) * -0.315118104f;
    res[10] = (a - b) * -0.410669893f;
    a = t[0] - t[5];
    b = (t[9] - t[14]) * 5.73685646f;
    res[8] = (a + b) * -0.33908543f;
    res[9] = (a - b) * -0.370046794f;
    b = t[13] * 0.707106769f;
    res[4] = (t[4] + b) * -0.541196108f;
    res[13] = (t[4] - b) * -1.30656302f;

    /* window the first half and add the previous overlap (odd samples of odd subbands negated) */
    if (sb & 1) {
        for (i = 0; i < 9; i++) {
            if (i & 1) {
                out[i] = res[9 + i] * win[i] - prev[i];
            } else {
                out[i] = -res[9 + i] * win[i] + prev[i];
            }
        }
        for (i = 9; i < 18; i++) {
            if (i & 1) {
                out[i] = -res[26 - i] * win[i] - prev[i];
            } else {
                out[i] = res[26 - i] * win[i] + prev[i];
            }
        }
    } else {
        for (i = 0; i < 9; i++) {
            out[i] = -res[9 + i] * win[i] + prev[i];
        }
        for (i = 9; i < 18; i++) {
            out[i] = res[26 - i] * win[i] + prev[i];
        }
    }

    /* window the second half: the overlap for the next granule */
    for (i = 0; i < 9; i++) {
        prev[i] = res[8 - i] * win[18 + i];
    }
    for (i = 9; i < 18; i++) {
        prev[i] = res[i - 9] * win[18 + i];
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_226870/func_151F94E0.s")
#endif
