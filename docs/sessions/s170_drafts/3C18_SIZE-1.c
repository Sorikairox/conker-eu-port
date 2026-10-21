s32 func_1510D3E0(s32, s32, s32, s32, s32 *);
void func_15168E54(s32, s32 *);
extern s32 D_800A3C60[];
s32 func_15133C18(s32 arg0, s32 **arg1, s32 arg2) {
    s32 sp2C;
    s32 sp28;

    *arg1 = (s32 *)func_1502B6BC(&sp2C, 0, &sp28, 2, 9, D_800A3C60[arg0]);
    if (*arg1 == NULL) {
        return 0;
    }
    func_1510D3E0(**arg1, 0, 1, 0x3E, &D_800DCA70[arg0]);

    func_15168E54(**arg1, *arg1);
    return 1;
}
