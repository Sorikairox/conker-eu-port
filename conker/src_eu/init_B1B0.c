#include <ultra64.h>

#include "functions.h"
#include "variables.h"


struct151 *func_1000B1B0(s32 arg0) {
    s32 i;

    for(i = 0; i < 3; i++)
    {
        if ((D_800417B0[i] != 0) && (arg0 == D_800417B0[i]->unk4)) {
            return D_800417B0[i];
        }
    }

    return NULL;
}

struct151 *func_1000B1FC(s32 arg0) {
    s32 i;
    struct151 *tmp;

    for (i = 0; i < 3; i++) {
        if (D_800417B0[i] != NULL && arg0 == D_800417B0[i]->unk4) {
            return D_800417B0[i];
        }
    }
    for (i = 0; i < 3; i++) {
        if (D_800417B0[i] != NULL) {
            tmp = (struct151 *)D_800417B0[i]->unk60;
            if (tmp != NULL && arg0 == tmp->unk4) {
                return tmp;
            }
        }
    }
    return NULL;
}

void func_1000B294(s32 *arg0) {
    s32 i;
    struct151 *tmp;

    for (i = 0; i < 3; i++) {
        if (D_800417B0[i] != NULL) {
            if (arg0 == D_800417B0[i]->unk10) {
                D_800417B0[i]->unk10 = (s32 *)D_800417B0[i];
            }
            tmp = (struct151 *)D_800417B0[i]->unk60;
            if (tmp != NULL && arg0 == tmp->unk10) {
                tmp->unk10 = (s32 *)tmp;
            }
        }
    }
}

struct137 *func_1000B2F4(s32 arg0) {
    s32 i;

    for (i = 0; i < 12; i++)
    {
        if (D_800419A8[i].unk4 == -1) {

            bzero(&D_800419A8[i], 100);

            D_800419A8[i].unk0 = -1;

            if (arg0 < 150) {
                D_800419A8[i].unk2C = D_8002B074[arg0].unk0; // (s32)(u16)
            } else {
                D_800419A8[i].unk2C = 26000;
            }
            D_800419A8[i].unk30 = D_800419A8[i].unk2C;
            D_800419A8[i].unk4E = D_800419A8[i].unk4C = D_800419A8[i].unk52 = D_800419A8[i].unk54 = D_800419A8[i].unk58 = D_800419A8[i].unk5A = 32768;
            D_800419A8[i].unk4 = arg0;
            D_800419A8[i].unk8 = &D_8002B9D4;
            D_800419A8[i].unkC = &D_8002B9F4;
            D_800419A8[i].unk10 = &D_800419A8[i];
            return &D_800419A8[i];
        }
    }
    return NULL;
}

void func_1000B3D4(struct00 *arg0, struct151 *arg1) {
    s32 i;
    struct151 *p;

    p = NULL;
    i = 0;
    if ((&arg1)[0] != NULL) { // fakematch: keeps arg1 in its stack home
        if (arg1->unk60 != NULL && arg0 != arg1->unk60) {
            if (arg1->unk60->unk4 == arg0->unk4) {
                arg0->unk4 = -1;
                return;
            }
            arg1->unk60->unk4 = -1;
        }
        arg1->unk60 = arg0;
        return;
    }
    for (; i != 3; i++) {
        if (p == NULL && (D_800417B0[i] == NULL || (D_800417B0[i]->unk4 <= 0 && D_800417B0[i]->unk60 == NULL))) {
            p = (struct151 *)func_1000B2F4(0);
            if (p != NULL) {
                p->unk0 = i;
                p->unk60 = arg0;
                D_800417B0[i] = p;
            } else {
                arg0->unk4 = -1;
                return;
            }
        } else if (p == NULL && D_800417B0[i] != NULL && D_800417B0[i]->unk60 != NULL && D_800417B0[i]->unk60->unk4 == 0) {
            p = (struct151 *)-1;
            func_1000B294(D_800417B0[i]->unk60);
            D_800417B0[i]->unk60->unk4 = -1;
            D_800417B0[i]->unk60->unk0 = -1;
            D_800417B0[i]->unk60 = arg0;
        }
    }
}

s32 func_1000B548(s32 *arg0) {
    s32 ret = 0;
    s32 i;

    for (i = 0; i < 12; i++) {
        if ((D_800419A8[i].unk4 != -1) && (D_800419A8[i].unk0 != -1)) {
            if (ret < 3) {
                *arg0++ = D_800419A8[i].unk4;
                ret++;
            }
        }
    }
    return ret;
}

s32 func_1000B638(s32 arg0, u8 arg1, s32 arg2, s32 arg3) {
    s32 sp1C = arg0 & 2;
    struct151 *temp_v0;

    arg0 = arg0 & 1;
    temp_v0 = D_800417B0[arg1];

    if ((temp_v0 == NULL) || (temp_v0->unk30 < 0x1F4)) {
        D_80041F04 &= ~1;
    }
    if (D_80041F04 & 1) {
        if (arg0 == 0) {
            func_100088F0(arg1, 0x8000, 1);
            if ((D_800BE9F0 == 1) || (D_800BE9F0 == 0xC)) {
                func_10008790(arg1, 0x7000, 0U, 0);
            } else if (D_800BE9F0 != 7) {
                func_10008790(arg1, 0xCA, 0U, 0);
            }
            func_100085B8(arg1, 0xF, 1U);
        }
        arg0 = 1;
    } else if (arg0 != 0) {
        func_100088F0(arg1, 0x8000, 0);
        if ((D_800BE9F0 == 1) || (D_800BE9F0 == 0xC)) {
            func_10008790(arg1, 0x7000, 0xFFU, 0);
        } else if (D_800BE9F0 != 7) {
            func_10008790(arg1, 0xCA, 0xFFU, 0);
        }
        func_100085B8(arg1, 0xF, 0U);
        arg0 = 0;
    }
    if (D_800BE9F0 == 0x27) {
        func_10011FA0((s32 *)4);
        if (sp1C == 0) {
            sp1C = 2;
            func_1000E704(1, 1, 0xFFFF);
        }
    } else if (sp1C != 0) {
        func_1000E704(1, 0, 0xFFFF);
        sp1C = 0;
    }
    return sp1C | arg0;
}


s32 func_1000B830(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 tmp = D_800DBFF0->unk5F0 & 1;
    if ((tmp != 0) && (arg0 == 0)) {
        arg0 = 1;
        func_1000E40C(16, 1000);
    } else if ((tmp == 0) && (arg0 != 0)) {
        arg0 = 0;
        func_1000E40C(16, 18000);
    }
    return arg0;
}

s32 func_1000B8B8(s32 arg0, u8 arg1, f32 arg2, f32 arg3, f32 arg4) {
    s32 tmp;

    if (D_800BE9F0 == 4) {
        if (((arg0 & 1) != 0) && (D_80041F0C == 0)) {
            func_1000E46C(19, 0, 4096, 0);
            arg0 = arg0 & ~1;
        } else {
            if (D_80041F0C != 0) {
                tmp = D_80041F08 / D_80041F0C / 80;
                if (tmp >= 101) {
                    tmp = 100;
                }
                func_1000E588(19, tmp, 4096);
                arg0 |= 1;
            }
        }
        D_80041F08 = 0;
        D_80041F0C = 0;
        if ((arg0 & 2) == 0) {
            func_1000DF68(19, 0, 1);
            func_1000DF68(19, 32768, 0);
            arg0 |= 2;
        }
        return arg0;
    }
    return func_1000C530(arg0, arg1, arg2, arg3, arg4);
}

s32 func_1000BA18(u32 arg0, u8 arg1, f32 arg2, f32 arg3, f32 arg4) {
    u32 sp44;
    s32 sp40;
    s32 sp3C;

    sp44 = 0;
    sp3C = arg0 & 0x00FFFFFF;
    arg0 = arg0 & 0xFF000000;
    func_100114D0(0, -377, 8227, 32767, 4000, 3000, &sp40, &sp44, 0);
    sp44 = (sp44 << 16) & 0xFF000000;
    if (arg0 != sp44) {
        arg0 = sp44;
        func_1000E588(0x4D, arg0 >> 24, 0x6000);
    }
    sp3C = func_1000C530(sp3C, arg1, arg2, arg3, arg4) & 0xFFFFFF;
    // fakematch
    sp44 = sp3C & 0xFFFFFFFFFFFFFFFF;
    return arg0 | sp44;
}

s32 func_1000BAFC(u32 arg0, u8 arg1, f32 arg2, f32 arg3, f32 arg4) {
    u32 sp44;
    s32 sp40;
    s32 sp3C;

    sp44 = 0;
    sp3C = arg0 & 0x00FFFFFF;
    arg0 = arg0 & 0xFF000000;
    func_100114D0(0, 0, 0, 0x7FF8, 0xE74, 0xA28, &sp40, &sp44, 0);
    sp44 = ((0x7FFF - sp44) << 16) & 0xFF000000;
    if (arg0 != sp44) {
        arg0 = sp44;
        func_1000E588(0x93, arg0 >> 24, 0x6000);
    }
    sp3C = func_1000C530(sp3C, arg1, arg2, arg3, arg4) & 0xFFFFFF;
    // fakematch (same as func_1000BA18)
    sp44 = sp3C & 0xFFFFFFFFFFFFFFFF;
    return arg0 | sp44;
}

s32 func_1000BBE8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg0 == 0) {
        func_1000E704(20, 1, 0xFFFF);
        arg0 = 1;
    }
    return arg0;
}

s32 func_1000BC28(s32 arg0, u8 arg1, s32 arg2, s32 arg3) {
    s32 tmp = func_10008A4C(arg1, 0) + func_10008A4C(arg1, 6) + 1;
    if (tmp >= 256) {
        tmp = 255;
    } else {
        if (tmp < 16) {
            tmp = 1;
        }
    }
    if (tmp != arg0) {
        func_150C851C(tmp - 1);
        arg0 = tmp;
    }
    return arg0;
}


#pragma GLOBAL_ASM("asm/nonmatchings/init_B1B0/func_1000BCBC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/init_B1B0/func_1000BF60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/init_B1B0/func_1000C350.s")
#pragma GLOBAL_ASM("asm/nonmatchings/init_B1B0/func_1000C530.s")
#pragma GLOBAL_ASM("asm/nonmatchings/init_B1B0/func_1000C7E8.s")

s32 func_1000C934(s32 arg0, u8 arg1, f32 arg2, f32 arg3) {
    s32 vol;
    s32 max;
    s32 flag;

    vol = 0;
    flag = D_800DBFF0->unk5F0 & 1;
    if (flag) {
        max = 0x7FFF;
    } else {
        max = 0x2EE0;
    }
    if (D_800BE9F0 == 0x37 && !flag) {
        func_100114D0(2200, 1066, -1600, max, 3000, 1500, NULL, &vol, NULL);
        vol &= 0xFF00;
        vol = max - vol;
    }
    if ((u16)(vol != arg0)) {
        func_1000E40C(0x54, vol);
    }
    return vol | 0x80000000;
}
// NON-MATCHING: close but last part isn't quite right
// s32 func_1000C934(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
//     s32 sp3C;
//     s32 sp38;
//     s32 temp_a1;
//     s32 temp_t7;
//
//     sp3C = 0;
//     temp_t7 = D_800DBFF0->unk5F0 & 1;
//     if (temp_t7 != 0) {
//         sp38 = 0x7FFF;
//     } else {
//         sp38 = 12000;
//     }
//     if ((D_800BE9F0 == 0x37) && (temp_t7 == 0)) {
//         func_100114D0(2200, 1066, -1600, sp38, 3000, 1500, 0, &sp3C, 0);
//         sp3C = sp38 - (sp3C & 0xFF00);
//     }
//     temp_a1 = sp3C;
//     if ((sp3C != arg0) & 0xFFFF) {
//         sp3C = temp_a1;
//         func_1000E40C(84, sp3C);
//     }
//     return sp3C | 0x80000000;
// }

s32 func_1000CA18(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 tmp;

    if (D_800BE9F0 == 55) {
        if ((D_800DBFF0->unk5F0 & 1) != 0) {
            tmp = 0;
        } else {
            func_100114D0(2200, 1066, -1600, 24000, 3000, 1500, 0, &tmp, 0);
            tmp &= 0xFF00;
        }
    } else {
        tmp = 24000;
    }

    if ((tmp != arg0) & 0xFFFF) {
        func_1000E40C(84, tmp);
    }
    return tmp | 0x80000000;
}

s32 func_1000CAE4(s32 arg0, u8 arg1, s32 arg2, s32 arg3) {
    s32 sp24 = arg0 & 2;

    arg0 &= 1;
    if (D_800BE9F0 == 0x42) {
        func_10011FA0((s32 *)4);
        if (arg0 == 0) {
            arg0 = 1;
            func_1000E704(0x58, 1, 0xFFFF);
        }
    } else if (arg0 != 0) {
        func_1000E704(0x58, 0, 0xFFFF);
        func_1000E40C(0x58, 16000);
        arg0 = 0;
    }
    if (sp24 == 0) {
        func_10008790(arg1, 0x1000, 0, 1);
        sp24 = 2;
    }
    return sp24 | arg0;
}

void func_1000CBA8(s32 arg0) {
    if (D_800417B0[0] != NULL) {
        D_800417B0[0]->unk4E = arg0;
        D_800417B0[0]->unk50 = (u16)0x500;
    }
    if (D_800417B0[1] != NULL) {
        D_800417B0[1]->unk4E = arg0;
        D_800417B0[1]->unk50 = (u16)0x500;
    }
}

void func_1000CBF0(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (arg2 & (1 << i)) {
            if (D_800417B0[i] != NULL) {
                D_800417B0[i]->unk5A = arg0;
                D_800417B0[i]->unk5C = arg1;
                if (arg1 == 0) {
                    D_800417B0[i]->unk58 = arg0;
                }
            }
        }
    }
}

// #pragma GLOBAL_ASM("asm/nonmatchings/init_B1B0/func_1000CC54.s")
void func_1000CC54(s32 arg0) {
    s32 phi_a3;
    struct151 *temp_v0;

    temp_v0 = D_800417B0[arg0];
    if (temp_v0 != 0) {
        phi_a3 = (((u32) (temp_v0->unk58 * ((u32) (temp_v0->unk4C * temp_v0->unk52) >> 0xF)) >> 0xF) * temp_v0->unk2C) >> 0xF;
        if (phi_a3 != temp_v0->unk30) {
            if (temp_v0->unk30 == 0) {
                func_10008988(arg0, temp_v0->unk38 ^ 0xFFFF, 1);
            } else {
                if (phi_a3 == 0) {
                    func_10008988(arg0, temp_v0->unk38 ^ 0xFFFF, 0);
                }
            }
            temp_v0->unk30 = phi_a3;
            func_10008EE0(arg0, phi_a3);
        }
    }
}

s32 func_1000CD40(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 != arg0) {
        arg2 = arg2 * D_800BE9E4;
        if (arg0 < arg1) {
            arg0 = arg0 + arg2;
            if (arg1 < arg0) {
                arg0 = arg1;
            }
        } else {
            arg0 = arg0 - arg2;
            if ((arg0 < arg1) || (arg0 < 0)) {
                arg0 = arg1;
            }
        }
    }
    return arg0;
}

s32 func_1000CDA0(u8 arg0, s32 *arg1) {
    if (arg0 == 0) {
        return 1;
    }
    if (arg1 != NULL) {
        if (arg1[0] >= 0) {
            if ((D_800417B0[arg1[0]] == NULL) || (arg1[1] <= 0)) {
                return 1;
            }
            if (func_1000853C(arg1[0]) == 3) {
                return 1;
            }
            if (!(D_8002B078[arg1[1]][0] & 0x20)) {
                D_800418AC[arg1[0]] |= 3;
            }
            arg0 &= ~D_800418AC[arg1[0]];
        } else {
            return 1;
        }
    } else {
        return 1;
    }
    return arg0 == 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/init_B1B0/func_1000CEAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/init_B1B0/func_1000D2F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/init_B1B0/func_1000D758.s")
#pragma GLOBAL_ASM("asm/nonmatchings/init_B1B0/func_1000D96C.s")
void func_1000DE1C(s32 arg0, s32 arg1) {
    s32 n;
    s32 i;
    s32 ids[3];

    arg0 &= 0xFFF;
    if (arg0 == 0) {
        func_1000DEC4();
        n = func_1000B548(ids);
        for (i = 0; i < n; i++) {
            if (ids[i] > 0) {
                func_1000D96C(0, ids[i], arg1);
            }
        }
    } else {
        func_1000D96C(0, arg0, arg1);
    }
}
void func_1000DEC4(void) {
    s32 i;

    for (i = 0; i < 12; i++) {
        if (D_800419A8[i].unk0 == -1) {
            if (D_800419A8[i].unk4 != -1) {
                D_800419A8[i].unk4 = -1;
            }
        } else if (func_1000853C(D_800419A8[i].unk0) == 0) {
            D_800417B0[D_800419A8[i].unk0] = NULL;
            D_800419A8[i].unk0 = -1;
            D_800419A8[i].unk4 = -1;
        }
        D_800419A8[i].unk60 = 0;
    }
}
void func_1000DF68(s32 arg0, s32 arg1, s32 arg2) {
    struct151 *p;

    p = func_1000B1FC(arg0);
    if (p != NULL) {
        p->unk4E = arg1;
        if (arg2 == 1) {
            p->unk4C = arg1;
            if (p->unk0 >= 0) {
                func_1000CC54(p->unk0);
            }
        }
        if (arg2 >= 2) {
            s32 d = p->unk4C - arg1;
            if (d < 0) {
                d = -d;
            }
            d /= arg2;
            if (d <= 0) {
                d = 2;
            } else if (d >= 0x8000) {
                d = 0x7FFF;
            }
            p->unk50 = d;
        } else {
            p->unk50 = 0x200;
        }
    }
}

void func_1000E054(s32 arg0, s32 arg1) {
    struct151 *sp1C;

    sp1C = func_1000B1B0(arg0);
    if (sp1C != 0) {
        if ((2 == sp1C->unk15) && (arg1 == 0)) {
            func_100084D8(sp1C->unk0);
            sp1C->unk15 = 0;
            sp1C->unk30 = -1;
            func_1000CC54(sp1C->unk0);
            return;
        }
        if ((2 != sp1C->unk15) && (arg1 != 0)) {
            if (sp1C->unk15 != 1) {
                func_10008F58(sp1C->unk0);
            }
            sp1C->unk15 = 2;
        }
    }
}

s32 func_1000E0F8(s32 arg0) {
    struct151 *tmp;

    arg0 &= 0xFFF;
    tmp = func_1000B1FC(arg0);

    if (tmp && tmp->unk60 == 0) {
        return 1;
    } else {
        return 0;
    }
}

s32 func_1000E134(s32 arg0) {
    s32 tmp;

    if (arg0 < 150) {
        tmp = D_8002B078[arg0][0] & ~0xF0;
        if ((tmp == 1) || (tmp == 3)) {
            return 1;
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/init_B1B0/func_1000E17C.s")
extern s8 D_800422A0;

void func_1000E2F4(s32 arg0) {
    s32 i;
    u8 id;

    for (i = 0; i != 3; i++) {
        if (D_800417B0[i] != NULL && D_800417B0[i]->unk4 > 0 && D_800417B0[i]->unk15 == 0) {
            if (arg0 != 0) {
                id = i;
                func_10008EE0(id, 0);
                if (!(*(s32 *)&D_8002B074[D_800417B0[i]->unk4].unk4 & 0x10)) {
                    func_10008F58(id);
                }
            } else {
                if (!(*(s32 *)&D_8002B074[D_800417B0[i]->unk4].unk4 & 0x10)) {
                    func_100084D8(i);
                }
                D_800417B0[i]->unk30 = -1;
                func_1000CC54(i);
            }
        }
    }
    D_800422A0 = arg0;
}

void func_1000E40C(s32 arg0, s32 arg1) {
    struct151 *temp_v0;

    if (arg1 >= 0x8000) {
        arg1 = 0x7FFF;
    } else if (arg1 < 0) {
        arg1 = 0;
    }
    temp_v0 = func_1000B1FC(arg0);
    if (temp_v0 != NULL) {
        if (temp_v0->unk0 < 0) {
            temp_v0->unk30 = arg1;
        }
        temp_v0->unk2C = arg1;
    }
}

s32 func_1000E46C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct151 *p;
    s32 i;

    p = func_1000B1FC(arg0);
    arg1 = (arg1 * 0xFF) / 100;
    if (arg1 > 0xFF) {
        arg1 = 0xFF;
    } else if (arg1 < 0) {
        arg1 = 0;
    }
    if (p != NULL) {
        if (p->unk0 >= 0) {
            if (arg3 < 0) {
                func_1000886C(((u8 *)p)[3], arg2, arg1);
            } else {
                func_10008790(((u8 *)p)[3], arg2, arg1, arg3);
            }
            return 1;
        }
        if (arg1 == 0) {
            p->unk38 |= arg2;
        } else if (arg1 > 0) {
            p->unk38 &= ~arg2;
        }
        for (i = 0; arg2 != 0; i++) {
            if (arg2 & 1) {
                p->unk3C[i] = arg1;
            }
            arg2 >>= 1;
        }
        return 1;
    }
    return 0;
}
s32 func_1000E588(s32 arg0, s32 arg1, s32 arg2) {
    struct151 *tmp = func_1000B1FC(arg0);

    if (tmp != NULL) {
        if (tmp->unk0 >= 0) {
            if (arg1 > 100) {
                arg1 = 100;
            } else if (arg1 < 0) {
                arg1 = 0;
            }
            func_1000886C(tmp->unk0, arg2, (arg1 * 255) / 100);
            return 1;
        }
        if (arg1 <= 0) {
            tmp->unk38 |= arg2;
            return 1;
        }
        if (arg1 > 0) {
            tmp->unk38 &= ~arg2;
            return 1;
        }
    }
    return 0;
}

s32 func_1000E654(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct151 *sp1C;
    struct151 *phi_a0;

    sp1C = func_1000B1FC(arg0);
    phi_a0 = NULL;
    if (arg3 >= 0) {
        phi_a0 = func_1000B1FC(arg3);
    }

    if (sp1C != NULL) {
        if (arg2 == 0) {
            if (sp1C->unk0 >= 0) {
                func_10008C6C(sp1C->unk0, arg1 - 1);
                return 1;
            }
        }
        sp1C->unk24 = arg1;
        sp1C->unk20 = arg2;
        if (phi_a0 != NULL) {
            sp1C->unk10 = phi_a0;
        }
        return 1;
    }
    return 0;
}

s32 func_1000E704(s32 arg0, s32 arg1, s32 arg2) {
    struct151 *tmp = func_1000B1B0(arg0);
    if (tmp && tmp->unk0 >= 0) {
        func_10008A94(tmp->unk0, arg2, arg1);
        return 1;
    }
    return 0;
}

void func_1000E75C(s32 arg0) {
    D_8002B070 = arg0 >> 1;
}

s32 func_1000E770(s32 *arg0, s32 *arg1) {
    if (arg0 != 0) {
        *arg0 = D_80041F08;
    }
    if (arg1 != 0) {
        *arg1 = D_80041F0C;
    }
    return D_80041F04;
}

void func_1000E7A0(u32 arg0, s32 arg1) {
    if (arg0 % 2 == 1) {
        D_80041F04 |= 1;
    } else if (arg0 & 2) {
        D_80041F08 += arg1;
        D_80041F0C++;
    } else if (arg0 & 4) {
        D_80041F08 = arg1 + 1;
        D_80041F04 |= 4;
    } else if (arg0 & 8) {
        D_80041F0C = arg1 >> 8;
        arg1 &= 0xFF;
        if (arg1 == 0 || arg1 == 4 || arg1 == 5) {
            D_80041F08 = 2;
        } else if (arg1 == 10) {
            D_80041F08 = 1;
        } else {
            D_80041F08 = 3;
        }
    } else if (arg0 & 0x10) {
        D_80041F04 |= 0x10;
    }
}
// NON-MATCHING: mostly just wrong registers
// void func_1000E7A0(u32 arg0, s32 arg1) {
//     if ((arg0 & 1) == 1) {
//         D_80041F04 |= 1;
//     } else if (arg0 & 2) {
//         D_80041F08 += arg1;
//         D_80041F0C += 1;
//     } else if (arg0 & 4) {
//         D_80041F08 = 1 + arg1;
//         D_80041F04 |= 4;
//     } else if (arg0 & 8) {
//         D_80041F0C = (arg1 >> 8) & 0xff;
//         if ((D_80041F0C == 0) || (D_80041F0C == 4) || (D_80041F0C == 5))  {
//             D_80041F08 = 2;
//         } else if (D_80041F0C == 10) {
//             D_80041F08 = 1;
//         } else {
//             D_80041F08 = 3;
//         }
//     } else if (arg0 & 16) {
//         D_80041F04 |= 16;
//     }
// }

void func_1000E8C4(s32 arg0) {
    if ((arg0 & 1) == 1) {
        D_80041F04 &= -2; // truncate odd to even
    }
}

u8 func_1000E8F0(s32 arg0) {
    struct151 *temp_v0 = func_1000B1B0(arg0);
    if ((temp_v0 != 0) && (temp_v0->unk0 >= 0)) {
        return D_800418AC[temp_v0->unk0];
    } else {
        return 0;
    }
}

// initialising with grim loops
extern s32 D_80041C50[3][16];
extern s32 D_80041B60[3][16];
extern s32 D_80041C40[3];
extern s32 D_80041C30[3];
extern s32 D_80041C20[3];
extern u8 D_80041D40;

void func_1000E934(void) {
    u32 i;
    s32 j;
    s32 k;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 16; j++) {
            D_80041C50[i][j] = 0x8000;
            D_80041B60[i][j] = 0x100;
        }
        func_10008F24(i);
        D_800417B0[i] = NULL;
        D_80041C40[i] = 0;
        D_80041C30[i] = 0;
        D_80041C20[i] = 0;
    }
    bzero(D_800419A8, sizeof(D_800419A8));
    D_80041D40 = 0;
    for (k = 0; k < 12; k++) {
        D_800419A8[k].unk4 = -1;
    }
}

u16 func_1000EA94(s32 arg0) {
    u16 tmp;

    if (arg0 == 0) {
        tmp = 82;
    } else if (arg0 == 2) {
        tmp = 81;
    } else if (arg0 == 1) {
        tmp = 83;
    }
    func_1000D96C(tmp, 0, 0);
    return tmp;
}
