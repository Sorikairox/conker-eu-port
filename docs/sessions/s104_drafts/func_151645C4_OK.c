extern u8 D_80088A90[];
extern u8 D_80088A94[];
extern u8 D_80088A98[];
void func_15111CAC(s32);
void func_1515F170(s32, s32);

void func_151645C4(u8 arg0) {
    D_800DCDD0 = arg0;
    if (arg0) {
        switch (D_800BE9F0) {
        case 0xB:
            func_15111CAC(4);
            break;
        case 0x6:
            func_1515F170(0xA, 1);
            func_15111CAC(4);
        case 0x39:
            ((u8 *)&D_800DCD20)[0] = D_80088A90[0];
            ((u8 *)&D_800DCD20)[1] = D_80088A90[1];
            ((u8 *)&D_800DCD20)[2] = D_80088A90[2];
            D_800B0DF0->unk5 = D_80088A94[0];
            D_800B0DF0->unk6 = D_80088A94[1];
            D_800B0DF0->unk7 = D_80088A94[2];
            break;
        case 0x7:
        case 0xC:
            break;
        }
    } else {
        switch (D_800BE9F0) {
        case 0x6:
            func_1515F170(0xA, 0);
        case 0x7:
        case 0xC:
        case 0x39:
            func_15111CAC(6);
            ((u8 *)&D_800DCD20)[0] = D_80088A98[0];
            ((u8 *)&D_800DCD20)[1] = D_80088A98[1];
            ((u8 *)&D_800DCD20)[2] = D_80088A98[2];
            D_800B0DF0->unk5 = 0xFF;
            D_800B0DF0->unk6 = 0xFF;
            D_800B0DF0->unk7 = 0xFF;
            break;
        case 0xB:
            func_15111CAC(6);
            break;
        case 0x29:
            func_15111CAC(1);
            break;
        }
    }
}
