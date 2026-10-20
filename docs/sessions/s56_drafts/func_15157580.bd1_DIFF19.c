s32 func_1503F8A8(u8 *, s32, s32, s32, f32, s32);
s32 func_1503F91C(s32, s32, u8 *, u8 *, u8 *, u8 *, u8 *);

u8 *func_15157580(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, s32 arg7) {
    f32 (*temp_s0)[4];
    f32 (*temp_s1)[4];
    s32 var_s0;
    s32 var_s1;
    s32 var_s1_2;
    u8 temp_v0_2;
    u8 *temp_v0;
    u8 *var_s0_2;
    u8 *var_s0_3;

    temp_v0_2 = *arg0;
    var_s0 = 0x36;
    if (temp_v0_2 & 0x80) {
        var_s0 = 0x5B;
    } else if (temp_v0_2 & 0x10) {
        var_s0 = 0x4C;
    }
    temp_v0 = func_15167A68(var_s0, arg7, arg5 + 0x120, 1, (u8) (s32) arg6, 1U);
    if (temp_v0 == NULL) {
        return NULL;
    }
    memcpy(temp_v0 + 0x10, arg0, 0x58);
    func_1503F91C((*(s32 *)((u8 *)temp_v0 + 0x18)), (*(s32 *)((u8 *)temp_v0 + 0x1C)), temp_v0 + 0x6C, temp_v0 + 0x70, temp_v0 + 0x74, temp_v0 + 0x78, temp_v0 + 0x68);
    temp_s0 = temp_v0 + 0x7C;
    guMtxIdentF(temp_s0);
    temp_s1 = temp_v0 + 0xBC;
    guMtxIdentF(temp_s1);
    (*(f32 (**)[4])((u8 *)((*(u8 **)((u8 *)temp_v0 + 0x68))) + 0x3E0)) = temp_s0;
    (*(f32 (**)[4])((u8 *)((*(u8 **)((u8 *)temp_v0 + 0x68))) + 0x3E4)) = temp_s1;
    func_1503F8A8((*(u8 **)((u8 *)temp_v0 + 0x68)), 1, arg1, arg2, 0.0f, 0);
    (*(s32 *)((u8 *)temp_v0 + 0xFC)) = arg3;
    (*(s8 *)((u8 *)temp_v0 + 0x100)) = 0;
    var_s1 = 0;
    var_s0_2 = temp_v0;
    (*(s32 *)((u8 *)temp_v0 + 0x118)) = arg4;
loop_a:
    var_s1 += 1;
    var_s0_2 += 4;
    (*(s32 *)((u8 *)var_s0_2 + 0x100)) = 0;
    if (var_s1 < 4) goto loop_a; // fakematch: keeps the loop rolled
    (*(s32 *)((u8 *)temp_v0 + 0x114)) = 0;
    if (arg3 != 0) {
        var_s1_2 = 0;
        var_s0_3 = temp_v0;
        if (D_80082FA0 >= 0) {
            do {
                (*(s32 *)((u8 *)var_s0_3 + 0x104)) = func_1515D9F0(arg3);
                var_s1_2 += 1;
                var_s0_3 += 4;
            } while (D_80082FA0 >= var_s1_2);
        }
        (*(s32 *)((u8 *)temp_v0 + 0x114)) = func_1515D9B0();
    }
    return temp_v0;
}
