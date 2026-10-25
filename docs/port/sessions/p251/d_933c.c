#ifdef NON_MATCHING
// huff_decode_count1: P251 readable C for func_151F933C (hand asm). Decodes quadruples (four one-bit values
// v, w, x, y packed in the low nibble of table `table`'s result) from line i while i < 576 and the bit position
// is before `endBit` (both tested before every quadruple). Reads 4 bits ahead for the signs, takes one per non-zero
// value (MSB first) and gives the unused ones back. Writes 4 s16 values and 4 sign flags per quadruple, advances
// *bitpos, *out and *signs, returns the new line index. Caller: func_151F63C4 (game_221290).
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
