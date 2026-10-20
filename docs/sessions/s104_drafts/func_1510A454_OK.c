struct260 *func_1510A454(u8 *volatile arg0, s16 arg1, s8 arg2, s8 arg3, f32 arg4, s32 arg5, u8 arg6, s32 arg7) { // fakematch: volatile gives the arg0 home reload (s101 recipe)
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        f32 unk4;
        f32 unk8;
        s8 unkC;
        s8 unkD;
    } tmp;
    s16 n;
    u8 flag;

    if (arg0 == NULL) {
        return NULL;
    }
    flag = 0;
    if (arg1 < 0) {
        n = 300;
    } else {
        flag = 1;
        n = arg1;
    }
    tmp.unk4 = 0.0f;
    tmp.unk8 = arg4;
    tmp.unkC = arg2;
    tmp.unkD = arg3;
    tmp.unk0 = arg0;
    temp_v0 = func_15149130(n, -1, 0x1B, -1, flag, 0x1B, arg5 + 0x10, arg6, arg7);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x10);
    }
    return temp_v0;
}
