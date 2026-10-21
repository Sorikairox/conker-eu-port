extern s32 D_800A7EDC;
extern s32 D_800A7EE0;
extern s32 D_800A7EE4;
extern s32 D_800A7EE8;
extern s32 D_800A7EEC;
extern s32 D_800A7EF0;
extern s32 D_800A7EA8;
extern s32 D_800A7EAC;
extern s32 D_800A7EB0;
extern s32 D_800A7EB4;
extern s32 D_800A7EB8;
extern s32 D_800A7EBC;
extern s32 D_800A7EC0;
extern s32 D_800A7EC4;
extern s32 D_800A7EC8;
extern s32 D_800A7ECC;
extern s32 D_800A7ED0;
extern s32 D_800A7ED4;
extern s32 D_800A7ED8;

s32 *func_151905AC(u8 *arg0, s32 *arg1) {
    s32 *p;

    switch (arg0[4]) {
    case 0x87:
    case 0xB0:
        p = &D_800A7EDC;
        *arg1 = 1;
        break;
    case 0xB1:
        p = &D_800A7EE0;
        *arg1 = 1;
        break;
    case 0xB4:
        p = &D_800A7EE4;
        *arg1 = 1;
        break;
    case 0x70:
    case 0xB2:
        p = &D_800A7EE8;
        *arg1 = 1;
        break;
    case 0x53:
        p = &D_800A7EEC;
        *arg1 = 1;
        break;
    case 0x96:
        p = &D_800A7EF0;
        *arg1 = 1;
        break;
    case 0x0:
    case 0x1:
    case 0x2:
    case 0x3:
    case 0x4:
        p = &D_800A7EA8;
        *arg1 = 1;
        break;
    case 0x49:
        p = &D_800A7EAC;
        *arg1 = 1;
        break;
    case 0x58:
        p = &D_800A7EB0;
        *arg1 = 1;
        break;
    case 0x50:
        p = &D_800A7EB4;
        *arg1 = 1;
        break;
    case 0x75:
        p = &D_800A7EB8;
        *arg1 = 1;
        break;
    case 0x80:
        p = &D_800A7EBC;
        *arg1 = 1;
        break;
    case 0x11:
    case 0x14:
    case 0x3B:
    case 0x98:
    case 0x99:
        p = &D_800A7EC0;
        *arg1 = 1;
        break;
    case 0x16:
        p = &D_800A7EC4;
        *arg1 = 1;
        break;
    case 0x88:
    case 0x90:
        p = &D_800A7EC8;
        *arg1 = 1;
        break;
    case 0x9C:
        p = &D_800A7ECC;
        *arg1 = 1;
        break;
    case 0x9D:
        p = &D_800A7ED0;
        *arg1 = 1;
        break;
    case 0x9F:
        p = &D_800A7ED4;
        *arg1 = 1;
        break;
    case 0xA0:
        p = &D_800A7ED8;
        *arg1 = 1;
        break;
    default:
        p = NULL;
        *arg1 = 0;
        break;
    }
    return p;
}
