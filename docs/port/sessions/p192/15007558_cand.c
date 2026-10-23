// save_options_write: copies the 0x1C option bytes D_800E1010..D_800E102C to D_800BE778 + 2, stores their checksum
// (0xCC + sum of byte i << (i & 3) over bytes 2..29, 16 bits) in the first halfword and, unless EEPROM writes are
// off (D_8002AC5C), writes the 0x20-byte block to EEPROM block 0 (func_151DD4A0 = osEepromLongWrite).
void func_15007558(void) {
    s8 *src;
    u8 *dst = &D_800BE778[2];
    u16 sum;
    s32 i;

    for (src = D_800E1010; (u8 *)src < (u8 *)&D_800E102C; src++) {
        *dst++ = *src;
    }
    sum = 0xCC;
    for (i = 2; i < 30; i++) {
        sum += D_800BE778[i] << (i & 3);
    }
    *(u16 *)D_800BE778 = sum;
    if (D_8002AC5C == 0) {
        func_151DD4A0(&D_800BE900, 0, D_800BE778, 0x20);
    }
}
