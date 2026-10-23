#ifdef NON_MATCHING
s32 func_1502B5C8(s32 *arg0, s32 arg1, ...);
void func_10024190(void *, s32); /* osWritebackDCache */
extern u8 *D_800BE810;           /* bit widths of the 69 packed save fields (asset 1/7, +8) */
extern s32 D_800BE804;

/* save_slot_unpack: reads EEPROM save slot arg0 (block arg0 * 16 + 4, 0x80 bytes into D_800BE778) and checks the
 * checksum (0xCC + sum of bytes 2..0x7F shifted left by index & 3, 16 bits) against the first u16. Bad block:
 * func_150064E0 (defaults) and, if a slot is loaded (D_800BE7FC >= 0) while D_80082F50 is set, the 27-byte state
 * at D_800D2E4C is put back. Good block: byte 2 = slot kind (sp+0x7F), bytes 3..6 = a time stamp (big-endian),
 * 27 bytes of D_800D2E4C, 9 bytes of D_800D2E60, D_800BE3DF, D_800BE800, D_800BE804 (u16, also passed to
 * func_15085710(0, 9, .)), D_800BE3E8, then the 69 bit fields of D_800C3A60 (u64 each, widths D_800BE810, MSB
 * first). While D_80082F50 is set and the kind is < 3, the slot record D_800BE818[kind] is refreshed when the stamp
 * is newer (count of set bits in D_800D2E4C, D_800BE3E8, D_800BE3DF, stamp, slot, D_800BE804); D_800BE7FC keeps the
 * best count (D_800BE7FE = 1 when D_800D2E68 bit 5 is set), otherwise the old D_800D2E4C state is put back.
 * Block 0x34 (slot 3) clears D_80082F50 at the end. */
void func_15006590(s8 arg0) {
    u8 saved[27];   /* sp+0x5C */
    u8 kind;        /* sp+0x7F */
    s32 stamp;      /* sp+0x78 */
    s32 block;      /* sp+0x48 */
    u64 bit;        /* sp+0xA8 */
    u8 *p;
    u8 *rec;
    s32 i, j;
    s32 sum;
    s32 bits;
    u8 mask;
    u8 cur;
    u8 v;

    for (i = 0; i < 27; i++) {
        saved[i] = ((u8 *) D_800D2E4C)[i];
    }
    if (D_800BE810 == NULL) {
        D_800BE810 = (u8 *) func_1502B5C8(NULL, 1, 7) + 8;
    }
    func_10024190(D_800BE778, 0x80);
    osInvalDCache(D_800BE778, 0x80);
    block = arg0 * 16 + 4;
    func_151DD950(&D_800BE900, block, D_800BE778, 0x80);
    sum = 0xCC;
    for (i = 2; i < 0x80; i++) {
        sum = (sum + (D_800BE778[i] << (i & 3))) & 0xFFFF;
    }
    if (sum != *(u16 *) D_800BE778) {
        func_150064E0();
        if (D_800BE7FC >= 0 && D_80082F50 != 0) {
            for (i = 0; i < 27; i++) {
                ((u8 *) D_800D2E4C)[i] = saved[i];
            }
        }
        if (block == 0x34) {
            D_80082F50 = 0;
        }
        return;
    }

    p = &D_800BE778[2];
    kind = p[0];
    stamp = (p[1] << 24) | (p[2] << 16) | (p[3] << 8) | p[4];
    p += 5;
    for (i = 0; i < 27; i++) {
        ((u8 *) D_800D2E4C)[i] = *p++;
    }
    for (i = 0; i < 9; i++) {
        D_800D2E60[i] = *p++;
    }
    D_800BE3DF = p[0];
    D_800BE800 = p[1];
    D_800BE804 = p[2] << 8;
    D_800BE804 = (p[2] << 8) | p[3];
    p += 4;
    func_15085710(0, 9, D_800BE804);
    D_800BE3E8 = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
    cur = p[4];
    p += 5;
    mask = 0x80;
    for (i = 0; i < 69; i++) {
        D_800C3A60[i] = 0;
        bit = 1LL << (D_800BE810[i] - 1);
        for (j = 0; j < D_800BE810[i]; j++) {
            if (cur & mask) {
                D_800C3A60[i] |= bit;
            }
            if (mask == 1) {
                cur = *p++;
                mask = 0x80;
            } else {
                mask >>= 1;
            }
            bit >>= 1;
        }
    }

    if (D_80082F50 != 0 && kind < 3) {
        D_800BE7F8[arg0] = kind;
        rec = (u8 *) &D_800BE818[kind];
        if (*(s32 *) (rec + 8) < stamp) {
            bits = 0;
            for (i = 0; i < 27; i++) {
                v = ((u8 *) D_800D2E4C)[i];
                for (j = 0; j < 8; j++) {
                    if (v & 1) {
                        bits++;
                    }
                    v >>= 1;
                }
            }
            rec[0xD] = bits;
            *(s32 *) (rec + 0) = D_800BE3E8;
            rec[0xC] = (s8) D_800BE3DF;
            *(s32 *) (rec + 8) = stamp;
            rec[0xE] = arg0;
            *(s32 *) (rec + 4) = D_800BE804;
            if ((u8) bits >= D_800BE7FC) {
                D_800BE7FC = (u8) bits;
                if (D_800D2E68 & 0x20) {
                    D_800BE7FE = 1;
                }
            } else {
                for (i = 0; i < 27; i++) {
                    ((u8 *) D_800D2E4C)[i] = saved[i];
                }
            }
        } else {
            for (i = 0; i < 27; i++) {
                ((u8 *) D_800D2E4C)[i] = saved[i];
            }
        }
    }
    if (block == 0x34) {
        D_80082F50 = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15006590.s")
#endif
