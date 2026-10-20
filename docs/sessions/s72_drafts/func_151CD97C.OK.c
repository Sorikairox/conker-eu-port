s32 func_151CDA70(s32, u8, s32, u8, u8);
void func_151CEA2C(u8 *);
void func_151CD97C(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *v = arg0 + 0x28;
    if (arg2 == 0x17) {
    s32 blk_t; // fakematch: block-local declaration = basic-block boundary (s69)
        if ((*(s32 *)(v + 4) == *arg1) && (*(s32 *)(v + 8) == 0)) {
            *(s32 *)(v + 8) = func_151CDA70(*(s32 *)v, v[0xC], *(s32 *)(v + 4), arg0[0xC], arg0[1]);
            (*(u8 **)v)[0x14] = 0;
        }
    } else if (arg2 == 0x18) {
    s32 blk_t; // fakematch: block-local declaration = basic-block boundary (s69)
        if (*(s32 *)(v + 4) == *arg1) {
            u8 *p = *(u8 **)(v + 8);
            if (p != NULL) { func_151CEA2C(p); }
        }
    } else if (arg2 == 0x23) {
        if ((*(s32 *)(v + 4) == *arg1)) {
            *(s32 *)(v + 8) = 0;
            (*(u8 **)v)[0x14] = 1;
        }
    }
}
