extern u8 D_800D34B0;
extern s8 D_800DA2D8[][3];
void func_150A2AB4(Unk34B8 *arg0, struct127 *arg1, s32 arg2, s64 arg3) {
    switch (arg0->unk17) {
    case 0:
        break;
    case 1:
        if (arg2 != 0xFF) {
            func_150E7810(arg2, 0xFF, 0);
        }
        break;
    case 2:
        if (arg2 != 0xFF) {
            D_800DA2D8[arg2][0] = arg0->unk18;
            D_800DA2D8[arg2][1] = arg0->unk1C;
            D_800DA2D8[arg2][2] = arg0->unk20;
        }
        break;
    case 3:
        if (arg2 != 0xFF) {
            func_150E6E30(arg1, arg2, arg0, (u8)arg0->unk18);
        }
        break;
    case 6:
        if (!(arg3 & 1)) {
            D_800D34B0 = 0x19;
            func_10010344(0x66F, arg1, 0x5DC0, 0x190, 0x1F4);
        }
        D_800D34B0 += D_800BE9E4;
        if (D_800D34B0 >= 0x1A) {
            if (arg1->unkB2 > 0x5A0) {
                arg1->unkB2 = 0x4B0;
            } else if (arg1->unkB2 < 0xF1) {
                arg1->unkB2 = 0x5A;
            } else {
                arg1->unkB2 -= 0xF0;
            }
            D_800D34B0 = 0;
        }
        break;
    case 8:
        func_151C8C24(arg1, arg0);
        break;
    case 9:
        func_1515F7E0(arg1, arg0);
        break;
    case 10:
        func_151CEACC(arg1, arg0);
        break;
    }
}
