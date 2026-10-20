s32 func_1518B140(u8 *arg0, s32 arg1, u8 arg2) {
    u8 *a1;
    u8 *n;
    u8 *nx;
    u8 k;
    if (arg0 == NULL) {
        if (arg2 != 0) { ((void (**)(s32))&D_8008D960)[arg2](arg1); }
        return 0;
    }
    n = func_1518B0D0(arg1, arg2);
    if (n == NULL) {
        if (arg2 != 0) { ((void (**)(s32))&D_8008D960)[arg2](arg1); }
        return 0;
    }
    *(u8 **)(n + 0x14) = *(u8 **)(arg0 + 0x10);
    if (*(u8 **)(n + 0x14) != NULL) {
        *(u8 **)(*(u8 **)(n + 0x14) + 0x18) = n;
    } else {
        *(u8 **)(arg0 + 0x14) = n;
    }
    *(u8 **)(arg0 + 0x10) = n;
    *(s32 *)(n + 0x18) = 0;
    *(s16 *)(arg0 + 0x22) = *(s16 *)(arg0 + 0x20);
    *(s32 *)(arg0 + 0x1C) = *(s32 *)(arg0 + 0x1C) + 1;
    if (*(s32 *)(arg0 + 0x18) < *(s32 *)(arg0 + 0x1C)) {
        a1 = *(u8 **)(arg0 + 0x14);
        *(s32 *)(arg0 + 0x1C) = *(s32 *)(arg0 + 0x1C) - 1;
        nx = *(u8 **)(a1 + 0x18);
        if (nx == NULL) {
            *(s32 *)(arg0 + 0x10) = 0;
            *(s32 *)(arg0 + 0x14) = 0;
        } else {
            *(s32 *)(nx + 0x14) = 0;
            *(s32 *)(arg0 + 0x14) = *(s32 *)(a1 + 0x18);
        }
        k = *(u8 *)(a1 + 0x1C);
        if (k != 0) {
            ((void (**)(s32))&D_8008D960)[k](*(s32 *)(a1 + 0x10));
        }
        func_1516972C(a1);
    }
    return 1;
}
