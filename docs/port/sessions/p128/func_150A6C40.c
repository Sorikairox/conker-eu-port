extern s32 D_eu_800BE9F4; /* PVS row index: per row {u16 byte index, s16 bit} (func_150183D0) */
extern s32 D_eu_800BE9F8; /* Huffman tree: 6-byte nodes {s16 symbol (< 0: inner), s16 child 0, s16 child 1} */
extern s16 D_800DC260[]; /* current PVS row per view (func_151101B4) */
extern s32 D_800DC278; /* record list head (func_150A4ED4) */

// pvs_row_apply: (hand asm) decodes PVS row D_800DC260[view] from the Huffman bit stream D_800BE5D0 and writes
// bit `view` of the s16 visibility word (+0) of every record in the D_800DC278 list (next record at +0xC, else +4,
// byte offsets; 0 ends the list). One decoded symbol gives 8 records, LSB first. Bits are read MSB first; the row
// start {byte, bit} comes from D_eu_800BE9F4 (byte 0xFFFF = none loaded yet: read as u16, as in the asm).
// Shift counts use the low 5 bits (srlv).
void func_150A6C40(s32 view) {
    u8 *p;
    u8 *rec;
    s16 *node;
    s16 *row;
    s32 cur;
    s32 bit;
    s32 k;
    s32 sym;
    s32 keep;

    if (D_800BE5D0 == 0) {
        return;
    }
    keep = ~(1 << view);
    rec = (u8 *) D_800DC278;
    k = 0;
    row = (s16 *) (D_eu_800BE9F4 + D_800DC260[view] * 4);
    bit = row[1];
    p = (u8 *) D_800BE5D0 + *(u16 *) row;
    cur = *p;
    if (rec == NULL) {
        return;
    }
    for (;;) {
        if (k == 0) {
            node = (s16 *) D_eu_800BE9F8;
            while ((sym = node[0]) < 0) {
                if (bit == 0) {
                    p++;
                    cur = *p;
                    bit = 7;
                } else {
                    bit--;
                }
                node = (s16 *) (D_eu_800BE9F8 + (((cur >> (bit & 0x1F)) & 1) ? node[2] : node[1]));
            }
        }
        *(s16 *) rec = (*(s16 *) rec & keep) | (((sym >> k) & 1) << view);
        if (k < 7) {
            k++;
        } else {
            k = 0;
        }
        if (*(s16 *) (rec + 0xC) != 0) {
            rec += *(s16 *) (rec + 0xC);
        } else if (*(s16 *) (rec + 4) != 0) {
            rec += *(s16 *) (rec + 4);
        } else {
            return;
        }
    }
}
