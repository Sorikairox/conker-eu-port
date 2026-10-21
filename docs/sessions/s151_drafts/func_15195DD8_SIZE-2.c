extern s32 D_800B1268[];

s32 func_15195DD8(u8 *arg0, s32 arg1, s32 arg2, s32 *arg3) {
    s32 i;
    s32 j;
    s8 type;
    s8 a;
    s32 *p;

    p = &D_800B1268[arg1];
    *arg3 = 0;
    i = -1;
loop_1:
    i++;
loop_2:
    type = *(s8 *)((i << 3) + arg0);
    if (-3 != type && -0x21 != type) {
loop_3:
        i++;
        type = *(s8 *)((i << 3) + arg0);
        if (-3 != type) {
            if (-0x21 != type) {
                goto loop_3;
            }
        }
    }
    if (-0x21 == type) {
        return -1;
    }
    if (*(s32 *)(arg0 + (i << 3) + 4) != *p) {
        if (arg1 != 0) {
            i++;
            goto loop_2;
        }
    }
    if (arg2-- >= 1) {
        goto loop_1;
    }
    if (type != -0xE) {
        do {
            i++;
        } while (*(s8 *)((i << 3) + arg0) != -0xE);
    }
    j = i;
loop_13:
    j++;
    (*arg3)++;
    a = *(s8 *)((j << 3) + arg0);
    j++;
    if (a == -0xB) {
        if (*(s8 *)((j << 3) + arg0) == -0xE) {
            goto loop_13;
        }
    }
    return i;
}
