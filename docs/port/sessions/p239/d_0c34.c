#ifdef NON_MATCHING
// bone_sparks_owner_release: D_8008DA1C [1] (func_1518FDC8's release handler, also reachable as a tick handler from
// func_1518FD34): clears byte +0x1AC of the owner's (+0x10) attachment +0x31C, if any. Returns that pointer (the asm
// leaves it in v0, and func_1518FD34 returns a tick handler's v0), so the table has one signature s32 (u8 *).
s32 func_15190C34(u8 *self) {
    u8 *att = *(u8 **)(*(u8 **)(self + 0x10) + 0x31C);

    if (att != NULL) {
        att[0x1AC] = 0;
    }
    return (s32)att;
}
#else
void func_15190C34(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)((*(u8 **)((u8 *)arg0 + 0x10))) + 0x31C));
    if (temp_v0 != NULL) {
        (*(s8 *)((u8 *)temp_v0 + 0x1AC)) = 0;
    }
}
#endif
