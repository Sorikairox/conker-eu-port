/* P247 DRAFT (not inserted, not compiled, UNVERIFIED): readable C for the MP3 Huffman group of game_eu_226870.
 *
 * Findings (P247):
 * - func_151F9184 and func_151F933C use the normal C ABI: game_221290 (C) calls them with 8 / 7 arguments
 *   (prototypes at game_221290.c:2663). Only func_151F9060 / func_151F911C use the private register ABI
 *   (a0 = byte pointer, t0 = bit position, s1 = bit count, s0 = tree, s5 = table base, a2 = table number; results in
 *   v0 / t1), and their only callers are func_151F9184 / func_151F933C. So the two leaf helpers become static
 *   functions on a small reader state, and 9184 / 933C keep their prototypes.
 * - Invariant used below: the asm's a0 is always buf + (t0 >> 3) (table path: a0 += ((t0 & 7) + len) >> 3; tree
 *   path: a0++ when the bit mask wraps; get-bits: a0 += ((t0 & 7) + n) >> 3; sign bit: a0 += ((t0 & 7) + 1) >> 3;
 *   933C's give-back: a0-- when (t0 & 7) < unused), so the C keeps only the bit position.
 * - func_151F94E0 is NOT part of this group: it is compiled code (no hand-written markers, no calls), the float
 *   IMDCT / hybrid step called by game_221290 (`func_151F94E0(&stream->unk4f64[ch][i], i, ..., sine_block[..])`).
 *   It can be written and difftested on its own (960 words, floats only).
 * Verification plan: difftest cannot test 9184 / 933C directly (the reference's jal to 9060 / 911C is stubbed and
 * the stub does not follow the register ABI). Use a whole-function harness (nmasm_*.py style): run the ROM code of
 * 9184 / 933C with the real helpers (map 0x151F9060..0x151F94E0) against the compiled C, on the real tables
 * (D_800E0E20 trees / D_800E0E24 lookup, filled at runtime: dump them or build them with the game's init code) and
 * real bit streams (MP3 frames of the ROM's music / speech assets), plus random streams; then mutants.
 */

typedef struct {
    u8 *buf;    /* stream start (a0 of the callers) */
    u32 pos;    /* bit position (t0) */
} HuffReader;

extern u8 **D_800E0E20;     /* per table: Huffman tree, 4-byte nodes {u8 left, u8 right, s8 x, s8 y}; child =
                               node + 4 * offset; x == -1 marks an inner node */
extern u8 *D_800E0E24;      /* [table][256] fast lookup: +0 = (y << 4) | x, +0x2200 = code length (0 = longer
                               than 8 bits: walk the tree) */

// huff_get_bits (func_151F911C): the next n bits MSB first from the unaligned big-endian word at the read
// position (lwl / lwr); shifts are mod 32 like sllv / srlv.
static u32 huff_get_bits(HuffReader *r, s32 n) {
    u8 *p = r->buf + (r->pos >> 3);
    u32 w = ((u32) p[0] << 24) | ((u32) p[1] << 16) | ((u32) p[2] << 8) | p[3];

    w <<= r->pos & 7;
    r->pos += n;
    return w >> ((32 - n) & 0x1F);
}

// huff_get_bit: one bit (the sign-bit reads inlined in 9184; lb + srlv + andi 1).
static s32 huff_get_bit(HuffReader *r) {
    s32 b = (r->buf[r->pos >> 3] >> (7 - (r->pos & 7))) & 1;

    r->pos++;
    return b;
}

// huff_decode_pair (func_151F9060): decodes one Huffman code of table `table` into (x, y). Fast path: the next 8
// bits index the lookup; a non-zero length consumes that many bits. Else walk the tree bit by bit from the root.
static void huff_decode_pair(HuffReader *r, s32 table, s32 *x, s32 *y) {
    u8 *p = r->buf + (r->pos >> 3);
    u32 k = (table << 8) + ((((p[0] << 8) | p[1]) >> (8 - (r->pos & 7))) & 0xFF);
    u8 len = D_800E0E24[0x2200 + k];
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

// huff_decode_big_values (func_151F9184): decodes (x, y) pairs from index i up to `end` (exclusive, step 2) with
// table `table`; a value 15 with linbits extends by linbits raw bits (+15); each non-zero value is followed by
// its sign bit. Writes the values to *out (s16 pairs) and the sign flags to *signs (one byte per value, 0 for a
// zero value), advances both pointers and *bitpos, returns the new index.
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

// huff_decode_count1 (func_151F933C): decodes quadruples (v, w, x, y of one bit each, table `table`) from index i
// while i < 576 and the bit position is before `endBit`; reads 4 bits ahead for the signs, takes one per non-zero
// value (MSB first) and gives the unused ones back. Writes 4 s16 values and 4 sign flags per quadruple, advances
// *bitpos / *out / *signs, returns the new index.
s32 func_151F933C(u8 *buf, s32 *bitpos, s32 table, s32 i, s32 endBit, s16 **out, u8 **signs) {
    HuffReader r;
    s16 *o = *out;
    u8 *s = *signs;
    s32 q, unused;
    s32 v[4];
    u32 sb;
    s32 k, n;

    r.buf = buf;
    r.pos = *bitpos;
    while (endBit - (s32) r.pos > 0 && i < 576) {
        huff_decode_pair(&r, table, &q, &unused);
        for (k = 0; k < 4; k++) {
            v[k] = (q >> (3 - k)) & 1;
            o[k] = v[k];
        }
        sb = huff_get_bits(&r, 4);
        n = 3;
        for (k = 0; k < 4; k++) {
            if (v[k]) {
                v[k] &= sb >> n;
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
/* Open points for the next session: (1) check the asm loop entry of 933C (`endBit - t0 > 0` and `i - 576 < 0`
 * before the first quad; same in the loop); (2) 9184's first test is `end - i > 0` (no do-while); (3) types of
 * D_800E0E20 / D_800E0E24 in variables.h; (4) the `(s8)` sign of the 4 sign bits: `v[k] &= sb >> n` keeps bit 0
 * only because v[k] is 0 / 1. */
