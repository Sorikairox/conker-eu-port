extern s32 D_80091914[];
extern s32 D_800918C4;
extern s32 D_80091960;
/* Texture address of a material: kind (arg3) selects the source table. */
s32 func_1514306C(s32 arg0, s32 arg1, s32 arg2, u8 arg3) {
    s32 v;

    switch (arg3) {
    case 1:
        v = 0;
        break;
    case 2:
        v = D_80091914[arg1];
        break;
    case 3:
        v = D_800918C4;
        break;
    case 4:
        v = D_80091960;
        break;
    case 5:
        v = arg1;
        break;
    case 6:
        v = *(s32 *)arg0;
        if ((u32)v >= 0x10000000U) {
            v = ((s32 *)v)[arg2];
        }
        break;
    default:
        v = (*(s32 **)&D_80090F10[arg1])[arg2];
        break;
    }
    return v;
}
