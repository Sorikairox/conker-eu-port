s32 func_151616D0(u8, s32, s32);
extern s32 D_80088F60;
extern u8 D_800DD835;

typedef struct { u8 b[5]; } S5;
void func_151008C0(s32 arg0) {
    s32 pad;
    S5 ids;
    s32 i;
    u8 *p;
    u32 chance;

    *(s32 *)&ids = *(s32 *)&D_80088F60;
    ids.b[4] = ((u8 *)&D_80088F60)[4];
    if (arg0 == 0) {
        p = D_800BE500;
        D_800DD835++;
        for (i = 0; i < 5; i++, p++) {
            chance = 35;
            if (*p != 0) {
                chance = 70;
            }
            if (func_150ADA20() % 1000U < chance) {
                if (*p ^= 1) {
                    func_151616D0(ids.b[i], 0x18, 0);
                } else {
                    func_151616D0(ids.b[i], 0x1C, 0);
                    func_151616D0(ids.b[i], 0x17, 0);
                }
            }
        }
    }
}
