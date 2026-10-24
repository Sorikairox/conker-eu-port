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
