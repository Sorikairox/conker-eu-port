s32 func_15190770(u8 **, s32, u8, u8);

void func_151ABE04(u8 *arg0) {
    s8 sp2A;
    s8 sp29;
    s8 sp28;
    s16 sp26;
    u8 sp24;
    u8 *sp20;
    u8 temp_v0;
    u8 *temp_v1;

    temp_v1 = (*(u8 **)((u8 *)arg0 + 0x18));
    temp_v0 = (*(u8 *)((u8 *)temp_v1 + 4));
    if ((temp_v0 == 0) || (temp_v0 == 1) || (temp_v0 == 2) || (temp_v0 == 3) || (temp_v0 == 4) || (temp_v0 == 0x96)) {
        sp20 = temp_v1;
        sp26 = 0x12C;
        sp28 = 0;
        sp29 = 0;
        sp24 = (*(u8 *)((u8 *)temp_v1 + 0x3B));
        if ((*(u8 *)((u8 *)temp_v1 + 4)) == 0x96) {
            sp2A = 3;
        } else {
            sp2A = 0;
        }
        if ((*(u8 *)((u8 *)temp_v1 + 0x127)) != 0xFF) {
            (*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_v1 + 0x31C))) + 0x66)) = 0x1F4;
        }
        func_15190770(&sp20, 0, (*(u8 *)((u8 *)arg0 + 0xC)), (*(u8 *)((u8 *)arg0 + 1)));
    }
}
