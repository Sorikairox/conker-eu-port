#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_1000D96C(s32 arg0, s32 arg1, s32 arg2);
void func_1000B294(s32 *arg0);
void func_1000B3D4(struct00 *arg0, struct151 *arg1);
void func_1000CC54(s32 arg0);
s32 func_1000CDA0(u8 arg0, s32 *arg1);
#endif


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
s32 func_1000C350(s32 arg0, u8 arg1, s32 arg2, s32 arg3) {
    if (!(arg0 & 0x80)) {
        arg0 |= 0x80;
        if (D_800C35EA != 1) {
            func_1000886C(arg1, 0x1E, 1U);
            func_1000886C(arg1, 1, 1U);
            func_1000E40C(0x23, 0x61A8);
        } else if (D_800C3A08 == 3) {
            func_1000E40C(0x23, 0xFA);
            func_1517946C(2);
        } else if (D_800C3A08 == 6) {
            func_1000886C(arg1, 0x1E, 1U);
            func_1000886C(arg1, 1, 0x40U);
            func_1517946C(2);
        } else {
            func_1000E40C(0x23, 0x61A8);
        }
        return arg0;
    } else if (D_800BE9F0 != 0x1D) {
        func_10008F24(arg1);
    } else if (D_80041F08 != (arg0 & 0x7FU)) {
        switch (D_80041F08) {
        case 1:
            func_10008790(arg1, 0x1E, 0U, 0);
            func_10008790(arg1, 1, 0x40U, 0);
            break;
        case 2:
            func_10008790(arg1, 0x18, 0xFFU, 0);
            func_10008790(arg1, 6, 0U, 0);
            func_10008790(arg1, 1, 1U, 0);
            break;
        }
        arg0 = D_80041F08 | 0x80;
    }
    return arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/init_B1B0/func_1000C530.s")
#ifdef NON_MATCHING
s32 func_1000C7E8(s32 arg0, s32 arg1, f32 arg2, s32 arg3, f32 arg4) {
    f32 temp_f12;
    f32 temp_f14;
    f32 var_f2;
    s32 var_a2;
    s32 var_v0;

    var_a2 = arg0;
    if (D_800BE9F0 == 0x31) {
        if (var_a2 != 2) {
            if (func_1000B1B0(9) == NULL) {
                func_1000E704(0x3E, 0, 0xFFFF);
                func_1000E40C(0x3E, 0x7FFF);
                func_1000D96C(0x3D, 0x3E, 4);
            }
            return 2;
        }
        return 0;
    }
    var_v0 = D_8002B070;
    if (var_v0 == 0) {
        var_v0 = 1;
        D_8002B070 = 1;
    }
    if (var_a2 != var_v0) {
        var_a2 = var_v0;
    }
    temp_f14 = arg2 - -4000.0f;
    temp_f12 = 24000.0f - (sqrtf((temp_f14 * temp_f14) + (arg4 * arg4)) * 10.0f);
    var_f2 = temp_f12;
    if (temp_f12 < 100.0f) {
        var_f2 = 100.0f;
    } else if (temp_f12 > 24000.0f) {
        var_f2 = 24000.0f;
    }
    arg0 = var_a2;
    func_1000E40C(0x3E, (s32) var_f2);
    return arg0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/init_B1B0/func_1000C7E8.s")
#endif
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
#ifdef NON_MATCHING
extern s32 D_80041C20[];
extern s32 D_80041C30[];
extern s32 D_80041C40[];
extern s32 D_80041B60[][16];
extern s32 D_80041C50[][16];
extern u8 D_80041D10[][16];
extern u8 D_80041D40;
void func_1507E7E4(struct127 *, u8, u8, u16, s32);

/* Music player slot arg0: drain its message queue (beat / marker messages from the sequencer)
 * and update the per-channel fade state, then step the channel volume ramps. */
void func_1000CEAC(s32 arg0) {
    struct151 *pl = D_800417B0[arg0];
    u16 *masks;
    s32 *types;
    OSMesg msg;
    u32 m;
    s32 kind;
    u32 bits;
    s32 i;
    /* The asm keeps this in a stack slot it never initialises (in practice the value left by the previous
     * call, func_1000D758 calls this for slots 0..2 back to back) until the first beat message sets 0x514.
     * NM builds have no .data, so start from the beat value. */
    s32 len = 0x514;
    s32 t;

    if (pl == NULL) {
        return;
    }
    masks = (u16 *)pl->unkC;
    types = (s32 *)pl->unk8;
    D_800418AC[arg0] = 0;
    while (osRecvMesg(&D_80041E58[arg0], &msg, OS_MESG_NOBLOCK) == 0) {
        m = (u32)msg;
        kind = m & 7;
        if (m & 0x10) {
            if ((u32)kind < 2) {
                t = (s32)m >> 5;
                len = 0x514;
                if (D_80041C30[arg0] != 0) {
                    D_80041C40[arg0] = t - D_80041C30[arg0];
                }
                D_80041C30[arg0] = t;
                D_80041C20[arg0] = t;
            }
            bits = masks[kind];
            if (bits != 0) {
                D_800418AC[arg0] |= bits & 0x7F;
                for (i = 0; bits != 0 && i < 16; i++, bits >>= 1) {
                    if (!(bits & 1)) {
                        continue;
                    }
                    switch (types[i]) {
                        case 0:
                            D_80041D10[arg0][i] ^= 1;
                            D_80041C50[arg0][i] = 0x8000;
                            D_80041B60[arg0][i] = len;
                            break;
                        case 1:
                            D_80041D10[arg0][i] ^= 1;
                            len >>= 1;
                            if (D_80041D10[arg0][i] == 0) {
                                D_80041C50[arg0][i] = len * D_800BE9E4 + 0x8000;
                            }
                            D_80041B60[arg0][i] = len;
                            break;
                        case 2:
                            D_80041D10[arg0][i & 7] ^= 1;
                            D_80041D10[arg0][i | 8] = D_80041D10[arg0][i & 7] ^ 1;
                            D_80041C50[arg0][i & 7] = 0x8000;
                            D_80041C50[arg0][i | 8] = 0x8000;
                            D_80041B60[arg0][i] = 0;
                            break;
                        default:
                            D_80041D10[arg0][i] |= 1;
                            D_80041C50[arg0][i] = len * D_800BE9E4;
                            D_80041B60[arg0][i] = len;
                            break;
                    }
                }
            }
            D_80041D40 = arg0;
        } else if (D_80041F04 & 1) {
            func_1507E7E4(D_800CC2D0, 0x44, 1, 0x12, 5);
        }
    }
    pl = D_800417B0[arg0];
    if (pl->unk30 == 0) {
        D_800418AC[arg0] |= 0x80;
        if (pl->unk15 == 0) {
            func_10008F58(arg0);
            D_800417B0[arg0]->unk15 = 1;
        }
    } else if (pl->unk15 == 1) {
        func_100084D8(arg0);
        D_800417B0[arg0]->unk15 = 0;
    }
    for (i = 0; i < 16; i++) {
        if (D_80041C50[arg0][i] != 0) {
            t = D_80041C50[arg0][i] - D_80041B60[arg0][i] * D_800BE9E4;
            D_80041C50[arg0][i] = (t < 0) ? 0 : t;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/init_B1B0/func_1000CEAC.s")
#endif
#ifdef NON_MATCHING
extern s32 D_80041C20[];
extern s32 D_80041C30[];
extern s32 D_80041C40[];
void func_10008C04(u8 idx, u8 arg1, s32 arg2);
s32 func_10008CE8(u8 idx, s32 arg1);

/* Song-table record (D_8002B074, 16 bytes): +8 per-frame callback, +0xC initial tempo/volume byte. */
typedef s32 (*NmSongCallback)(s32, u8, f32, f32, s32);
#define NM_SONG_CB(id) (*(NmSongCallback *)((u8 *)D_8002B074 + (id) * 16 + 8))
#define NM_PL34(p) (*(s32 *)((u8 *)(p) + 0x34)) /* the song callback's state */
#define NM_SONG_B(id) (*((u8 *)D_8002B074 + (id) * 16 + 0xC))

/* Music player slot arg0, once per frame: start a pending fade, switch to the queued song (unk60) when it
 * may start, run the song's callback, step the three volume ramps and resync a linked player. */
void func_1000D2F8(s32 arg0, f32 arg1, f32 arg2, s32 arg3) {
    struct151 **slot = &D_800417B0[arg0];
    struct151 *pl;
    struct151 *nx;
    NmSongCallback cb;
    s32 state = func_1000853C(arg0);
    s32 v;
    s32 i;

    pl = *slot;
    if (pl == NULL) {
        return;
    }
    if (pl->unk24 != 0 && func_1000CDA0(pl->unk20, pl->unk10) != 0) {
        func_10008C6C(arg0, (*slot)->unk24 - 1);
        pl = *slot;
        v = pl->unk28;
        if (v != 0) {
            pl->unk30 = v;
            (*slot)->unk2C = v;
            pl = *slot;
        }
        pl->unk4C = 0x7FFF;
        (*slot)->unk4E = 0x7FFF;
        func_1000CC54(arg0);
        (*slot)->unk24 = 0;
        (*slot)->unk20 = 0;
    }
    pl = *slot;
    if (state == 0) {
        pl->unk4 = 0;
        pl = *slot;
    }
    nx = (struct151 *)pl->unk60;
    if (nx != NULL) {
        if (pl->unk4 == 0) {
            if (func_1000CDA0(nx->unk18, nx->unk10) != 0) {
                (*slot)->unk4 = -1;
                func_1000B294((s32 *)*slot);
                nx = (struct151 *)(*slot)->unk60;
                v = nx->unk4;
                if (v <= 0) {
                    nx->unk4 = -1;
                    ((struct151 *)(*slot)->unk60)->unk10 = NULL;
                    ((struct151 *)(*slot)->unk60)->unk18 = 0;
                    (*slot)->unk0 = -1;
                    *slot = NULL;
                } else if (func_10008CE8(arg0, v) == -1) {
                    ((struct151 *)(*slot)->unk60)->unk10 = NULL;
                    ((struct151 *)(*slot)->unk60)->unk18 = 0;
                    func_1000B3D4((*slot)->unk60, NULL);
                    (*slot)->unk60 = NULL;
                    *slot = NULL;
                } else {
                    nx = (struct151 *)(*slot)->unk60;
                    *slot = nx;
                    nx->unk0 = arg0;
                    (*slot)->unk18 = 0;
                    D_80041C40[arg0] = 0;
                    D_80041C30[arg0] = 0;
                    D_80041C20[arg0] = 0;
                    pl = *slot;
                    if (NM_SONG_B(pl->unk4) != 0) {
                        func_10008C04(arg0, NM_SONG_B(pl->unk4), 100);
                        pl = *slot;
                    }
                    if (pl->unk24 != 0) {
                        func_10008C6C(arg0, pl->unk24 - 1);
                        (*slot)->unk24 = 0;
                        pl = *slot;
                    }
                    pl->unk30 = 0;
                    func_1000CC54(arg0);
                    func_100084D8(arg0);
                    if ((*slot)->unk38 != 0) {
                        func_100088F0(arg0, (*slot)->unk38, 0);
                    }
                    for (i = 0; i < 16; i++) {
                        if ((*slot)->unk3C[i] != 0) {
                            func_10008660(arg0, i, (*slot)->unk3C[i], 1);
                            (*slot)->unk3C[i] = 0;
                        }
                    }
                }
            }
        } else if (func_1000CDA0(nx->unk18, nx->unk10) != 0) {
            (*slot)->unk15 = 0;
            func_10008F24(arg0);
        }
        pl = *slot;
    } else if (pl->unk4 == 0) {
        func_1000B294((s32 *)pl);
        (*slot)->unk4 = -1;
        (*slot)->unk0 = -1;
        *slot = NULL;
        pl = NULL;
    }
    if (pl == NULL) {
        return;
    }
    if (pl->unk4 > 0) {
        cb = NM_SONG_CB(pl->unk4);
        if (cb != NULL) {
            NM_PL34(*slot) = (*cb)(NM_PL34(pl), arg0, arg1, arg2, arg3);
            pl = *slot;
        }
    }
    if (func_1000CDA0(pl->unk1C, pl->unk10) != 0) {
        pl = *slot;
        (*slot)->unk4C = func_1000CD40(pl->unk4C, pl->unk4E, pl->unk50);
        pl = *slot;
        (*slot)->unk52 = func_1000CD40(pl->unk52, *(u16 *)((u8 *)pl + 0x54), *(u16 *)((u8 *)pl + 0x56));
        pl = *slot;
        (*slot)->unk58 = func_1000CD40(pl->unk58, (u16)pl->unk5A, (u16)pl->unk5C);
        (*slot)->unk1C = 0;
    }
    func_1000CC54(arg0);
    pl = *slot;
    if (pl->unk14 != 0) {
        nx = (struct151 *)pl->unk10;
        if (nx == NULL || nx == pl || nx->unk4 <= 0 || pl->unk4 <= 0 || nx->unk0 < 0) {
            pl->unk14 = 0;
            (*slot)->unk10 = (s32 *)*slot;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/init_B1B0/func_1000D2F8.s")
#endif
#ifdef NON_MATCHING
void func_1000CBF0(s32, s32, s32);
void func_1000CEAC(s32);
void func_1000D2F8(s32, f32, f32, s32);
s32 func_151F2CDC(void);
extern s8 D_800422A0;

void func_1000D758(f32 arg0, f32 arg1, s32 arg2) {
    s32 m5 = 0;
    s32 m40 = 0;
    s32 m34 = 0;
    s32 m12 = 0;
    s32 i;
    s32 idx;
    s32 w;
    s32 t;
    u16 lvl;

    if ((u8)D_800422A0 != 0) {
        return;
    }
    for (i = 0; i < 3; i++) {
        if (D_800417B0[i] == NULL) {
            continue;
        }
        idx = *(s32 *)((u8 *)D_800417B0[i] + 4);
        if (idx <= 0) {
            continue;
        }
        w = *(s32 *)((u8 *)D_8002B074 + idx * 16 + 4);
        t = w & ~0xF0;
        if (w & 0x40) {
            m40 |= 1 << i;
        }
        if (t == 5) {
            m5 |= 1 << i;
        } else if (t == 4 || t == 3) {
            m34 |= 1 << i;
        } else if (t == 1 || t == 2) {
            m12 |= 1 << i;
        }
    }
    if (m5 != 0) {
        func_1000CBF0(0x1770, 0x400, m5 ^ 0xFF ^ m40);
        func_1000CBF0(0x8000, 0x6400, m5);
    } else if (m34 != 0) {
        func_1000CBF0(0x1F4, 0x400, m34 ^ 0xFF);
        func_1000CBF0(0x8000, 0x800, m34);
    } else {
        lvl = D_800427F4;
        if (func_151F2CDC() == 1) {
            lvl = D_800427F4;
            if ((lvl < 0x7D || lvl >= 0x81) && lvl < 0x1C9 && lvl != 0x170 && lvl != 0x171) {
                func_1000CBF0(0x36B0, 0x200, m12 ^ 0xFF);
                goto done;
            }
        }
        func_1000CBF0(0x8000, 0x800, 0xFF);
    }
done:
    for (i = 0; i < 3; i++) {
        func_1000CEAC(i);
    }
    for (i = 0; i < 3; i++) {
        func_1000D2F8(i, arg0, arg1, arg2);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/init_B1B0/func_1000D758.s")
#endif
#ifdef NON_MATCHING
void func_1000D96C(s32 arg0, s32 arg1, s32 arg2) {
    struct137 *sp2C;
    s32 sp24;
    s32 temp_t7;
    struct00 *temp_v1;
    struct137 *temp_v0_3;
    struct137 *temp_v0_4;
    struct137 *var_a3;
    struct137 *var_s0;
    struct138 *temp_v0_2;
    struct151 *temp_v0;

    var_a3 = NULL;
    temp_t7 = arg0 & 0xFFF;
    var_s0 = NULL;
    sp24 = 0;
    arg0 = temp_t7;
    arg1 &= 0xFFF;
    if ((temp_t7 != 0) && (sp2C = NULL, var_a3 = sp2C, (func_1000B1FC(temp_t7) != NULL))) {
        temp_v0 = func_1000B1B0(arg0);
        if (temp_v0 != NULL) {
            temp_v1 = temp_v0->unk60;
            if (temp_v1 != NULL) {
                if (temp_v1->unk0 == -1) {
                    (*(u16 *)((u8 *)temp_v0 + 0x54)) = 0x8000U;
                    (*(s16 *)((u8 *)temp_v0 + 0x56)) = 0x400;
                    temp_v1->unk4 = -1;
                    temp_v0->unk60->unk0 = -1;
                    temp_v0->unk60 = NULL;
                }
                arg0 = 0;
                if (arg1 == 0) {
                    return;
                }
                goto block_12;
            }
            if ((temp_v0->unk15 != 0) || ((*(u16 *)((u8 *)temp_v0 + 0x54)) == 0)) {
                (*(u16 *)((u8 *)temp_v0 + 0x54)) = 0x8000U;
                temp_v0->unk52 = 0;
                (*(s16 *)((u8 *)temp_v0 + 0x56)) = 0x400;
                arg0 = 0;
                if (arg1 == 0) {
                    return;
                }
                goto block_12;
            }
        }
    } else {
block_12:
        if (arg1 != 0) {
            var_a3 = func_1000B1B0(arg1);
        }
        if (var_a3 != NULL) {
            if ((var_a3 != NULL) && (var_a3->unk60 != 0)) {
                if (arg0 != 0) {

                }
            } else if ((arg2 == 4) || (arg2 == 6)) {
                if (arg0 != 0) {
                    sp2C = var_a3;
                    var_s0 = func_1000B2F4(arg0);
                }
                if ((var_s0 != NULL) || (arg0 == 0)) {
                    if (arg0 != 0) {
                        temp_v0_2 = &D_8002B074[arg0];
                        if (((*(s32 *)((u8 *)temp_v0_2 + 4)) & 0x20) && ((*(s32 *)((u8 *)(&D_8002B074[arg1]) + 4)) & 0x20)) {
                            sp24 = 1;
                        }
                        (*(s8 *)((u8 *)var_s0 + 0x14)) = (s8) sp24;
                        if ((*(s32 *)((u8 *)temp_v0_2 + 4)) & 8) {
                            var_s0->unk54 = 0x8000;
                            var_s0->unk52 = 0;
                            var_s0->pad56 = 0x3C;
                        } else if (sp24 != 0) {
                            var_s0->unk54 = 0x8000;
                            var_s0->unk52 = 0;
                            var_s0->pad56 = 0x100;
                        }
                        var_s0->unk10 = var_a3;
                        var_s0->pad18 = 2;
                        sp2C = var_a3;
                        func_1000B3D4((struct00 *) var_s0, NULL);
                    }
                    if (arg2 == 6) {
                        if (arg0 != 0) {
                            var_a3->pad1C = 2;
                        }
                        (*(s8 *)((u8 *)var_a3 + 0x14)) = 0;
                        var_a3->unk10 = var_a3;
                        var_a3->unk54 = 0;
                        if ((*(s32 *)((u8 *)(&D_8002B074[arg1]) + 4)) & 8) {
                            var_a3->pad56 = 0x28;
                            return;
                        }
                        var_a3->pad56 = 0xA0;
                        return;
                    }
                    sp2C = var_a3;
                    temp_v0_3 = func_1000B2F4(0);
                    if (temp_v0_3 != NULL) {
                        if (arg0 != 0) {
                            var_a3->pad1C = 2;
                        }
                        (*(s8 *)((u8 *)var_a3 + 0x14)) = 0;
                        var_a3->unk10 = var_a3;
                        var_a3->unk54 = 0;
                        if (sp24 != 0) {
                            var_a3->pad56 = 0x80;
                        } else {
                            var_a3->pad56 = 0x200;
                        }
                        temp_v0_3->pad18 = 0x80;
                        temp_v0_3->unk10 = var_a3;
                        func_1000B3D4((struct00 *) temp_v0_3, (struct151 *) var_a3);
                    }
                }
            } else {
                goto block_56;
            }
        } else {
            if (arg1 != 0) {
                temp_v0_4 = func_1000B1FC(arg1);
                var_a3 = temp_v0_4;
                if (temp_v0_4 != NULL) {
                    if (arg0 != 0) {
                        sp2C = var_a3;
                        bzero(var_a3, 0x64);
                        var_a3->unk0 = -1;
                        if (arg0 < 0x96) {
                            var_a3->unk2C = (s32) D_8002B074[arg0].unk0;
                        } else {
                            var_a3->unk2C = 0x6590;
                        }
                        var_a3->unk5A = 0x8000;
                        var_a3->unk58 = 0x8000;
                        var_a3->unk54 = 0x8000;
                        var_a3->unk52 = 0x8000;
                        var_a3->unk4C = 0x8000;
                        var_a3->unk4E = 0x8000;
                        var_a3->unk8 = (s32) &D_8002B9D4;
                        var_a3->unkC = (s32) &D_8002B9F4;
                        var_a3->unk10 = var_a3;
                        var_a3->unk30 = (u32) var_a3->unk2C;
                    } else {
                        temp_v0_4->pad18 = 0x80;
                    }
                    var_a3->unk4 = arg0;
                    return;
                }
            }
block_56:
            if ((arg0 != 0) || (var_a3 != NULL)) {
                sp2C = var_a3;
                var_s0 = func_1000B2F4(arg0);
            }
            if (var_s0 != NULL) {
                if (arg2 == 3) {
                    var_s0->unk54 = 0x8000;
                    var_s0->unk52 = 0;
                    var_s0->pad56 = 0x400;
                } else if (arg2 == 2) {
                    var_s0->pad18 = 1;
                    var_s0->unk10 = var_a3;
                } else if (arg2 == 1) {
                    var_s0->pad18 = 2;
                    var_s0->unk10 = var_a3;
                } else if (arg2 == 5) {
                    var_s0->pad18 = 0x80;
                    var_s0->unk10 = var_a3;
                    if (var_a3 != NULL) {
                        var_a3->unk54 = 0;
                        var_a3->pad56 = 0x200;
                    }
                }
                func_1000B3D4((struct00 *) var_s0, (struct151 *) var_a3);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/init_B1B0/func_1000D96C.s")
#endif
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

void func_1000E17C(void) {
    s32 i;

    for (i = 0; i < 12; i++) {
        if (D_800419A8[i].unk4 > 0) {
            if (((((s32 *)&D_8002B074[D_800419A8[i].unk4])[1] & ~0xF0) == 1 || (((s32 *)&D_8002B074[D_800419A8[i].unk4])[1] & ~0xF0) == 3) && D_800419A8[i].unk0 == -1) {
                D_800419A8[i].unk4 = -1;
            }
        }
    }
    for (i = 0; i < 12; i++) {
        if (D_800419A8[i].unk4 > 0) {
            if (D_800419A8[i].unk60 != 0 && ((struct137 *)D_800419A8[i].unk60)->unk4 == -1) {
                D_800419A8[i].unk60 = 0;
            }
            if (D_800419A8[i].unk10 != NULL && D_800419A8[i].unk10->unk4 == -1) {
                D_800419A8[i].unk10 = NULL;
            }
        }
    }
    for (i = 0; i < 12; i++) {
        if (D_800419A8[i].unk4 > 0) {
            if (((((s32 *)&D_8002B074[D_800419A8[i].unk4])[1] & ~0xF0) == 1 || (((s32 *)&D_8002B074[D_800419A8[i].unk4])[1] & ~0xF0) == 3) && D_800419A8[i].unk0 != -1) {
                func_1000DE1C(D_800419A8[i].unk4, 4);
            }
        }
    }
}
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
