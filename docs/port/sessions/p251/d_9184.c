#ifdef NON_MATCHING
// huff_decode_big_values: P251 readable C for func_151F9184 (hand asm). Decodes (x, y) pairs with table `table`
// from line i up to `end` (exclusive, two lines per pair; nothing when end <= i). A value 15 of a table with
// linbits is extended by `linbits` raw bits (+ 15); each non-zero value is followed by its sign bit (x's sign is
// read before y's extension). Writes the values to *out (s16 pairs) and the sign flags to *signs (one byte per
// value, 0 for a zero value), advances *bitpos, *out and *signs, returns the new line index. Caller:
// func_151F63C4 (game_221290), once per region.
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
