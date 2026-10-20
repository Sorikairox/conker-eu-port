extern s8 D_800DCE50;
extern f32 D_800DCE54;
extern s8 D_800DCE58;
extern f32 D_800DCE5C;

void func_1500E738(void) {
    if (D_80082FA0 == 0) {
        D_800DCE50 = 0;
        D_800DCE54 = 1.0f;
    } else if (D_80082FA0 == 1) {
        D_800DCE50 = 1;
        D_800DCE54 = 0.5f;
    } else if ((D_80082FA0 == 2) || (D_80082FA0 == 3)) {
        D_800DCE50 = 2;
        D_800DCE54 = 0.25f;
    }
    switch (D_8008FD8C) {
    case 2:
        D_800DCE58 = 1;
        D_800DCE5C = 0.5f;
        return;
    case 3:
    case 4:
        D_800DCE58 = 2;
        D_800DCE5C = 0.25f;
        return;
    case 5:
    case 6:
    case 7:
    case 8:
        D_800DCE58 = 3;
        D_800DCE5C = 0.125f;
        return;
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
        D_800DCE58 = 4;
        D_800DCE5C = 0.0625f;
        return;
    default:
        D_800DCE58 = 0;
        D_800DCE5C = 1.0f;
        return;
    }
}
