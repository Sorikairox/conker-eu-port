u8 *func_15190770(void *, s32, u8, s32);

// character_spawn_aura: for characters of type 0..4 or 0x96 (arg0's data +0x18), spawns the 12-byte-template effect
// func_15190770 (character, its +0x3B, life 300, mode 3 for type 0x96 else 0) and, when the character has a
// partner (+0x127 != 0xFF), sets the partner's +0x66 timer to 500. P124: one struct instead of m2c's 6 locals.
void func_151ABE04(u8 *arg0) {
    struct {
        u8 *u0;
        u8 u4;
        s16 u6;
        s8 u8;
        s8 u9;
        s8 uA;
    } t;
    u8 *chr;
    u8 type;

    chr = *(u8 **)(arg0 + 0x18);
    type = chr[4];
    if (type == 0 || type == 1 || type == 2 || type == 3 || type == 4 || type == 0x96) {
        t.u0 = chr;
        t.u6 = 300;
        t.u8 = 0;
        t.u9 = 0;
        t.u4 = chr[0x3B];
        if (chr[4] == 0x96) {
            t.uA = 3;
        } else {
            t.uA = 0;
        }
        if (chr[0x127] != 0xFF) {
            *(s16 *)(*(u8 **)(chr + 0x31C) + 0x66) = 500;
        }
        func_15190770(&t, 0, arg0[0xC], arg0[1]);
    }
}
