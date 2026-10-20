#include <ultra64.h>

#include "functions.h"
#include "variables.h"
typedef struct { s32 x; s32 y; s32 z; s32 ex; s32 ey; s32 ez; f32 f; } SfxListener; // size 0x1C
extern SfxListener D_80042308[];
typedef struct {
    u16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    u16 unk8;
    s16 unkA;
    s32 unkC;
    s32 unk10;
    s32 (*unk14)(struct15 *, s32 *, u32 *, s32 *, s32 *, s32 *, u16 *);
    s32 unk18;
    s32 unk1C;
    s16 unk20;
    u8 unk22;
    u8 unk23;
    u16 unk24;
    u16 unk26;
    u16 unk28;
    u16 pad2A;
    f32 unk2C;
} SfxEnt; // size 0x30
extern u8 D_800BEA35;
s32 func_1000A750(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 *argA, u32 *argB, u32 *argC);

extern s32 D_80042B00;
void func_10011310(void);
void func_10011624(struct15 *arg0, s32 *arg1, s32 arg2, s32 arg3);
typedef struct { s32 unk0; u8 pad4[0x10]; f32 unk14; f32 unk18; f32 unk1C; u8 pad20[0x64]; u16 unk84; u8 pad86[0xFE]; u32 unk184; } SfxObj;


s32 func_1000EB00(struct04 *arg0, s32 arg1, s32 *arg2, s32 *arg3, s32 arg6, s32 arg7, u16 *arg8) {
    if (arg0->unk24 != 0) {
        arg0->unk24 = 0;
    }
    *arg3 = 64;
    if (D_800CC37D || (*arg2 == 0)) {
        *arg2 = 0;
        *arg8 = 0;
        return 0;
    }
    arg0->unk18 -= D_800BE9E4;
    if (arg0->unk18 > 0) {
        *arg2 = 0;
        *arg8 = 0;
    } else {
        arg0->unk18 = (func_150ADA20() & 0x7F) + 0x80;
        arg0->unk0 = (func_150ADA20() % 3U) + 0x6C;
    }
    return 0;
}

s32 func_1000EBC4(struct00 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0 = arg0->unkC;
    s32 temp_v1 = arg0->unk18;
    temp_v1 -= D_800BE9E4;

    if (temp_v1 <= 0) {
        temp_v0 = temp_v0 - D_800BE9E4 * 1000;
        if (temp_v0 < 0) {
            return 1;
        }
        arg0->unkC = temp_v0;
    }
    arg0->unk18 = temp_v1;
    return 0;
}

s32 func_1000EC24(struct251 *arg0, s32 arg1, s32 *arg2, struct11 *arg3, struct04 *arg4, s32 *arg5, u16 *arg6) {
    s16 temp_v1 = arg0->unk18.h[1];

    if (*arg6 != 0) {
        arg0->unk1C = *arg6;
        arg0->unk0 = 0;
        *arg6 = 0;
    }

    temp_v1 -= D_800BE9E4;

    if (temp_v1 <= 0) {
        if (*arg2 != 0) {
            func_10010F30(arg0->unk1C, *arg2, arg3->unk3, arg4->unk2, *arg5);
        }
        return 1;
    }
    arg0->unk18.w = temp_v1;
    return 0;
}

s32 func_1000ECCC(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u16 *arg6) {
    struct_eu_sfx *sfx = arg0;
    s16 timer = sfx->unk18;

    if (*arg6 != 0) {
        sfx->unk18 = (*arg6 << 16) | (sfx->unk18 & 0xFFFF);
        sfx->unk0 = 0;
        *arg6 = 0;
    }
    timer -= D_800BE9E4;
    if (timer <= 0) {
        *arg6 = sfx->unk18 >> 16;
        sfx->unk0 = *arg6;
        if (func_10010894((struct127 *)sfx->unk1C) == 0) {
            func_10010344(*arg6, (struct127 *)sfx->unk1C, sfx->unkC, sfx->unkA, sfx->unk8);
        }
        return 1;
    }
    sfx->unk18 = (sfx->unk18 & 0xFFFF0000) | timer;
    return 0;
}
// ? func_1000ECCC(void *arg0, ? arg1, ? arg2, ? arg3, void *arg6) {
//     s16 temp_a1;
//     s32 temp_t4;
//     s32 temp_v1;
//     u16 temp_v0;
//
//     temp_v1 = arg0->unk18;
//     temp_v0 = *arg6;
//     if (temp_v0 != 0) {
//         arg0->unk18 = (s32) ((temp_v0 << 0x10) | (temp_v1 & 0xFFFF));
//         arg0->unk0 = (u16)0;
//         *arg6 = (u16)0U;
//     }
//     temp_a1 = (s16) temp_v1 - *(void *)0x800BE9E4;
//     if ((s32) temp_a1 <= 0) {
//         temp_t4 = arg0->unk18 >> 0x10;
//         *arg6 = (u16) temp_t4;
//         arg0->unk0 = (s16) temp_t4;
//         if (func_10010894(arg0->unk1C, temp_a1, arg6) == 0) {
//             func_10010344(*arg6, arg0->unk1C, arg0->unkC, arg0->unkA, (?32) arg0->unk8);
//         }
//         return 1;
//     }
//     arg0->unk18 = (s32) ((arg0->unk18 & 0xFFFF0000) | temp_a1);
//     return 0;
// }

s32 func_1000EDA0(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u16 *arg6) {
    struct_eu_sfx *sfx = arg0;
    s16 timer = sfx->unk18;

    if (*arg6 != 0) {
        sfx->unk18 = (*arg6 << 16) | (sfx->unk18 & 0xFFFF);
        sfx->unk0 = 0;
        *arg6 = 0;
    }
    timer -= D_800BE9E4;
    if (timer <= 0) {
        sfx->unk0 = *arg6 = sfx->unk18 >> 16;
        func_10010630(*arg6, (struct127 *)sfx->unk1C, sfx->unkC, sfx->unkA, sfx->unk8);
        return 1;
    }
    sfx->unk18 = (sfx->unk18 & 0xFFFF0000) | timer;
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_1000EE70.s")

s32 func_1000EF40(struct57 *arg0, struct57 *arg1, s32 *arg2, s32 arg3, s32 arg4, s32 arg5, u16 *arg6) {
    if (arg0->unk10 & 0x80) {
        arg0->unk10 = (s32) (arg0->unk10 & -0x81);
    }
    if (*arg2 == 0) {
        if (arg0->unk24 != 0) {
            func_100111C8(arg0->unk24);
            arg0->unk24 = 0;
        }
        *arg6 = 0;
    }
    return 0;
}

s32 func_1000EFB4(struct_eu_sfx *arg0, s32 arg1, s32 *arg2, struct11 *arg3, s32 arg4, s32 *arg5, u16 *arg6) {
    SfxObj *obj = (SfxObj *)arg0->unk18;
    u16 *p;
    s32 id;

    if (obj != NULL && (id = *arg2) != 0) {
        if (obj->unk0 != 0) {
            for (p = (u16 *)arg0->unk1C; *p != 0; p++) {
                if (obj->unk84 == *p || !(arg0->unk10 & 1)) {
                    *arg5 = ((obj->unk184 >> 3) & 0x30) * 2;
                    arg0->unk2 = obj->unk14;
                    arg0->unk4 = obj->unk18;
                    arg0->unk6 = obj->unk1C;
                    return 0;
                }
            }
        }
        if (*arg6 == 0xCA) {
            func_10010F30(0xCB, id, arg3->unk3, 0, *arg5);
        } else if (*arg6 == 0x2CF) {
            func_10010F30(0x2D7, id, arg3->unk3, 0, *arg5);
            func_10010F30((func_150ADA20() % 3U) + 0x2EB, 0x3E80, arg3->unk3, 0, *arg5);
        } else if (*arg6 == 0x2D2) {
            func_10010F30(0x2DA, id, arg3->unk3, 0, *arg5);
            func_10010F30((func_150ADA20() % 3U) + 0x2EB, 0x3E80, arg3->unk3, 0, *arg5);
        }
    }
    return 1;
}
void func_1000F1A8(void) {
    s32 i;

    D_80042760 = 0;
    D_80041FD9 = 1;
    D_80041FD8 = 0;
    bzero(D_800425E0, 0x180);
    for (i = 0; i < 16; i++) {
        D_800425E0[i].unk2 = i + 16;
    }
    D_80041F50 = 0;
    func_100176EC();
    D_80041F60 = D_80041F61 = 0;
}

void func_10017780(u8 arg0, u16 arg1);
s32* allocate_memory(s32, s32, s32, s32);
void func_1000F248(s32 arg0) {
    u16 tmp;

    func_1000F1A8();
    if (arg0 == 4) {
        D_80041F54 = 0;
        D_80041F58 = 0.01f; // 0.009999999776482582
    } else {
        D_80041F54 = 23000;
        D_80041F58 = 0.1f; // 0.10000000149011612
    }

    if (arg0 == 0x35) {
        D_80041FD9 = 0;
    } else if (arg0 == 0x36) {
        D_80041FD9 = 0;
    } else if (arg0 == 0x3C) {
        D_80041FD9 = 0;
        D_80041FD8 = 0x3C;
    } else if (arg0 == 0x27) {
        D_80041FD9 = 0;
        D_80041FD8 = 0x28;
    } else if ((arg0 == 0x3A) || (arg0 == 0x40)) {
        D_80041FD9 = 0;
        D_80041FD8 = 0x3C;
    }

    D_80041F5C = allocate_memory(1762, 1, 0, 0);

    bzero(D_80041F5C, 1762);

    if (arg0 == 0x31) {
        D_80041FDC = 14000;
    } else {
        D_80041FDC = 23000;
    }
    func_10011E88(arg0);
    D_80041F60 = D_80041F61 = 0;
    func_10017780(0, D_80041F56);
    func_10017780(1, D_80041F56);
    func_10017780(2, 23000);
    // fakematch
    if (arg0) {}
}

s32 func_1000F3D0(u16 arg0) {
    struct120 *temp_v1;

    temp_v1 = &D_800425E0[arg0 & 0xF];
    if (temp_v1->unk8 != 0) {
        if ((temp_v1->unk0 == arg0) || (arg0 == (arg0 & 0xF))) {
            if (func_100173C4(&temp_v1->unk8) != 0) {
                return 1;
            }
        }
    }
    return 0;
}

s32 func_1000F44C(u16 arg0) {
    u32 mask;
    struct120 *temp_a1;
    struct31 *temp_a2;

    mask = __osDisableInt();
    temp_a1 = &D_800425E0[arg0 & 0xF];
    temp_a2 = temp_a1->unk8;
    if ((temp_a2 != 0) && (temp_a1->unk0 == arg0) && ((temp_a2->unk53 & 2) != 0)) {
        __osRestoreInt(mask);
        return 1;
    }
    __osRestoreInt(mask);
    return 0;
}

s32 func_1000F4D8(u16 arg0) {
    s32 i;

    arg0 &= 0x7FFF;
    for (i = 0; i < 16; i++) {
        if (D_800425E0[i].unk8 != NULL && arg0 == (D_800425E0[i].unk4 & 0x7FFF) &&
            func_100173C4(&D_800425E0[i].unk8)) {
            return 1;
        }
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_1000F568.s")
#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_1000F6B8.s")
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} EU42988;
extern EU42988 D_80042988[];
void func_1000F85C(u16 arg0, s16 arg1, s32 arg2) {
    if (arg0 >= 0x10) {
        if (func_1000F3D0(arg0) != 0) {
            if (arg1 == 0x10) {
                f32 sp1C;
                sp1C = alCents2Ratio(arg2);
                arg2 = *(s32 *)&sp1C;
            } else if (arg1 == 0x11) {
                arg1 = 0x10;
            }
            func_10017714(D_80042988[arg0 & 0xF].unk0, arg1, arg2);
        }
    }
}
// NON-MATCHING: not even close
// void func_1000F85C(s32 arg0, s16 arg1, s32 arg2) {
//     f32 sp1C;
//     s32 sp18;
//     s16 temp_a1;
//     s16 temp_a1_2;
//     s32 temp_t6;
//     s16 phi_a1;
//
//     temp_t6 = arg0 & 0xFFFF;
//     temp_a1 = arg1;
//     if (temp_t6 >= 16) {
//         sp18 = temp_t6;
//         arg1 = temp_a1;
//         temp_a1_2 = arg1;
//         if (func_1000F3D0(temp_t6) != 0) {
//             if (temp_a1_2 == 16) {
//                 sp18 = sp18;
//                 arg1 = temp_a1_2;
//                 sp1C = alCents2Ratio(arg2, temp_a1_2);
//                 arg2 = (s32) sp1C;
//                 phi_a1 = arg1;
//             } else {
//                 phi_a1 = temp_a1_2;
//                 if (temp_a1_2 == 0x11) {
//                     phi_a1 = (u16)0x10;
//                 }
//             }
//             func_10017714((((sp18 & 0xF) * 0xC) + 0x80040000) - 0x25E8, phi_a1, arg2);
//         }
//     }
// }

void func_1000F91C(u16 arg0, u16 arg1, s16 arg2, u8 arg3, s32 arg4,
                   s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9) {
    s32 sp2C;
    s32 tmp = func_1000F6B8(arg4, arg5, arg6, arg7, &sp2C, (s32) arg8, (s32) arg9);

    func_1000F85C(arg0, 8, (u32) (tmp * arg1) >> 0xF);
    func_1000F85C(arg0, 4, sp2C & 0x7F);
    func_1000F85C(arg0, 256, (sp2C & 0x80) | arg3);
    func_1000F85C(arg0, 16, arg2);
}

void func_1000F9D4(u16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    u32 tmp;

    func_1000F6B8(-1, arg1, arg2, arg3, &tmp, 32760, 32765);
    func_1000F85C(arg0, 4, tmp & 0x7F);
    func_1000F85C(arg0, 256, tmp & 0x80);
}

#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_1000FA64.s")
void func_1000FC18(u16 arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4) {
    s32 i;

    for (i = 0; i < D_80042B00; i++) {
        if (arg0 == ((SfxEnt *)D_80041FE0)[i].unk0 && arg1 == ((SfxEnt *)D_80041FE0)[i].unk2 && arg2 == ((SfxEnt *)D_80041FE0)[i].unk4 && arg3 == ((SfxEnt *)D_80041FE0)[i].unk6 && arg4 == (((SfxEnt *)D_80041FE0)[i].unk8 & 0x7FFF)) {
            if (((SfxEnt *)D_80041FE0)[i].unk24 != 0) {
                func_100111C8(((SfxEnt *)D_80041FE0)[i].unk24);
            }
            ((SfxEnt *)D_80041FE0)[i].unk10 |= 0x80;
        }
    }
}
void func_1000FD38(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;

    for (i = 0; i < D_80042760; i++) {
        if (arg0 == D_80041FE0[i].unk14 && arg1 == D_80041FE0[i].unk18 && arg2 == D_80041FE0[i].unk1C) {
            if (D_80041FE0[i].unk24) {
                func_100111C8(D_80041FE0[i].unk24);
            }
            D_80041FE0[i].unk10 = D_80041FE0[i].unk10 | 0x80;
        }
    }
}
void func_1000FDF4(u16 arg0) {
    s32 i;

    for (i = 0; i < D_80042760; i++) {
        if (arg0 == D_80041FE0[i].unk24) {
            if (D_80041FE0[i].unk24) {
                func_100111C8(D_80041FE0[i].unk24);
            }
            D_80041FE0[i].unk10 = D_80041FE0[i].unk10 | 0x80;
        }
    }
}
s32 func_1000FE88(struct15 *arg0, s32 arg1, s32 *arg2) {
    if (arg1 < *arg2) {
        if (arg0[arg1].unk24 != 0) {
            func_100111C8(arg0[arg1].unk24);
        }
        arg0[arg1].unk10 |= 0x80;
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_1000FEF0.s")
// NON-MATCHING: needs a re-work
// s32 func_1000FEF0(u16 arg0, struct127 *arg1, s32 arg2) {
//     s32 i;
//     struct15 *tmp;
//
//     if (arg0 == 0) {
//         // nothing
//     } else {
//         for (i = 0; i < D_80042760; i++) {
//             tmp = &D_80041FE0[i];
//             if ((arg0 == tmp->unk24) &&
//                 (arg1 == tmp->unk18) &&
//                 (arg2 == tmp->unk1C) &&
//                 ((tmp->unk10 & 0x80) == 0)) {
//                 return i;
//             }
//         }
//     }
//     return -1;
// }

extern s32 D_80042B00;
s32 func_1000FF90(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;
    u32 new_var; // fakematch: -1 kept in its own register

    for (i = 0; i < D_80042B00; i++) {
        new_var = -1;
        if ((arg0 == D_80041FE0[i].unk14) &&
            ((arg1 == D_80041FE0[i].unk18) || (arg1 == new_var)) &&
            ((arg2 == D_80041FE0[i].unk1C) || (arg2 == -1)) &&
            ((D_80041FE0[i].unk10 & 0x80) == 0)) {
            return i;
        }
    }
    return -1;
}
void func_1001001C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 i;

    for (i = 0; i < D_80042760; i++) {
        if (arg0 == D_80041FE0[i].unk14 && arg1 == D_80041FE0[i].unk18 && arg2 == D_80041FE0[i].unk1C) {
            *(f32 *)&D_80041FE0[i].unk2C = alCents2Ratio(arg4);
            D_80041FE0[i].unkC = arg3;
        }
    }
}
void func_100100E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 i;

    for (i = 0; i < D_80042760; i++) {
        if (arg0 == D_80041FE0[i].unk14 && arg1 == D_80041FE0[i].unk18 && arg2 == D_80041FE0[i].unk1C) {
            D_80041FE0[i].unk14 = arg3;
            D_80041FE0[i].unk18 = arg4;
            D_80041FE0[i].unk1C = arg5;
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_10010154.s")
#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_10010344.s")
void func_10010558(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4, s32 arg5) {
    if (arg5 <= 0) {
        func_10010344(arg0, arg1, arg2, arg3, arg4);
    } else {
        func_1000FA64(arg0, arg1->x_position, arg1->y_position, arg1->z_position, arg2, arg4, arg3, func_1000ECCC, arg5, arg1, 0, 0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_10010630.s")
// void func_10010630(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4) {
//     if (arg1->interaction_state != 0) {
//         if (arg1->camera != 0) {
//             func_10010F30(arg0, arg2 & 0xFFFF, 64, 0, (((u32) arg1->unk184 >> 3) & 0x30) * 2); //
//         } else {
//             func_1000FA64(arg0, arg1->x_position, arg1->y_position, arg1->z_position, arg2, arg4, arg3, (void *)func_1000EE70, arg1, arg1->unique_id, 0, 0);
//         }
//     }
// }

void func_10010720(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4, s32 arg5) {
    if (arg5 <= 0) {
        func_10010630(arg0, arg1, arg2, arg3, arg4);
    } else {
        func_1000FA64(arg0, arg1->x_position, arg1->y_position, arg1->z_position, arg2, arg4, arg3, func_1000EDA0, arg5, arg1, 0, 0);
    }
}

s32 func_100107F8(struct127 *arg0) {
    if (arg0->interaction_state == 0) {
        return 0;
    } else {
        if (arg0->camera != 0) {
            if (arg0->unk8E != 0) {
                if (func_1000F3D0(arg0->unk8E) != 0) {
                    return 1;
                }
            }
        } else {
            if (func_1000FF90(func_1000EE70, arg0, arg0->unique_id | 0x10000) != -1) {
                return 1;
            }
        }
        arg0->unk8E = 0;
    }
    return 0;
}

s32 func_10010894(struct127 *arg0) {
    if (arg0->camera != 0) {
        if (arg0->unk8C != 0) {
            if (func_1000F3D0(arg0->unk8C) != 0) {
                return 1;
            }
        }
    } else {
        if (func_1000FF90(func_1000EE70, arg0, arg0->unique_id | 0x20000) != -1) {
            return 1;
        }
    }
    arg0->unk8C = 0;
    return 0;
}

extern s32 D_8004238C;

void func_1001091C(u8 *arg0, s32 arg1) {
    s32 temp_v0;

    if (arg1 == 0) return;
    if (*(s32 *)arg0 == 0) return;
    if ((*(s32 *)((u8 *)arg0 + 0x318)) != 0) {
        if ((*(u16 *)((u8 *)arg0 + 0x8E)) != 0) {
            func_1000F85C((*(u16 *)((u8 *)arg0 + 0x8E)), 8, arg1);
        }
    } else {
        temp_v0 = func_1000FF90((s32) func_1000EE70, (s32) arg0, (*(u8 *)((u8 *)arg0 + 0x3B)) | 0x10000);
        if (temp_v0 != -1) {
            *(s32 *)((u8 *)&D_8004238C + (temp_v0 * 0x30)) = arg1;
            return;
        }
        (*(u16 *)((u8 *)arg0 + 0x8E)) = 0U;
    }
}
// NON-MATCHING: something isnt right...
// void func_1001091C(struct127 *arg0, struct15 *arg1) {
//     s32 temp_v0;
//
//     if ((arg1 != NULL) && (arg0->unk0 != 0)) {
//         if (arg0->camera != 0) {
//             if (arg0->unk8E != 0) {
//                 func_1000F85C(arg0->unk8E, 8, arg1->unk1C); // help
//             }
//         } else {
//             temp_v0 = func_1000FF90(func_1000EE70, arg0, arg0->unique_id | 0x10000);
//             if (temp_v0 != -1) {
//                 D_80041FEC[temp_v0][0] = arg1;
//             } else {
//                 arg0->unk8E = 0;
//             }
//         }
//     }
// }

void func_100109D0(struct127 *arg0) {
    if (arg0->camera) {
        if (arg0->unk8E) {
            func_100111C8(arg0->unk8E);
        }
    } else {
        func_1000FD38(func_1000EE70, arg0, arg0->unique_id | 0x10000);
    }
    arg0->unk8E = 0;
}

void func_10010A3C(struct127 *arg0) {
    if (arg0->camera) {
        if (arg0->unk8C) {
            func_100111C8(arg0->unk8C);
        }
    } else {
        func_1000FD38(func_1000EE70, arg0, arg0->unique_id | 0x20000);
    }
    arg0->unk8C = 0;
}

void func_10010AA8(struct127 *arg0) {
    s32 sp24;
    struct15 *tmp;

    if (arg0->camera != 0) {
        if (arg0->unk8C && func_1000F44C(arg0->unk8C)) {
            func_100111C8(arg0->unk8C);
        }
        if (arg0->unk8E && func_1000F44C(arg0->unk8E)) {
            func_100111C8(arg0->unk8E);
        }
    } else {
        sp24 = func_1000FEF0(arg0->unk8C, arg0, arg0->unique_id);
        if (sp24 != -1) {
            if (func_1000F44C(arg0->unk8C)) {
                func_100111C8(arg0->unk8C);
            }
            tmp = &D_80041FE0[sp24];
            tmp->unk10 |= 0x80;
        }
        sp24 = func_1000FEF0(arg0->unk8E, arg0, arg0->unique_id);
        if (sp24 != -1) {
            if (func_1000F44C(arg0->unk8E)) {
                func_100111C8(arg0->unk8E);
            }
            tmp = &D_80041FE0[sp24];
            tmp->unk10 |= 0x80;
        }
    }
    arg0->unk8C = 0;
    arg0->unk8E = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_10010BE8.s")
u16 func_10010E78(u16 arg0, s32 arg1, u16 arg2, s16 arg3, u8 arg4, s32 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, s16 argA)
{
  s32 sp2C;
  u32 temp_t1;
  temp_t1 = (u32) func_1000F6B8(arg5, arg6, arg7, arg8, &sp2C, (s32) arg9, (s32) argA);
  temp_t1 = (((u32) arg2) * temp_t1) >> 0xF;
  if (temp_t1 != 0)
  {
    return func_10010BE8(arg0, arg1, temp_t1, sp2C & 0x7F, (s16) ((s32) arg3), (sp2C & 0x80) | arg4, (u8) ((s32) D_80041FD9));
  }
  return 0;
}

void func_10010F30(s32 arg0, u16 arg1, u8 arg2, s16 arg3, u8 arg4) {
    func_10010BE8(0, arg0, arg1, arg2, arg3, arg4, D_80041FD9);
}

void func_10010F88(s32 arg0, u16 arg1, s16 arg2, u8 arg3, s32 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9) {
    func_10010E78(0, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
}
#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_10010FFC.s")

void func_100111C8(u16 arg0) {
    struct120 *tmp = &D_800425E0[arg0 & 0xF];

    if ((tmp->unk8 != 0) && (tmp->unk0 == arg0)) {
        tmp->unk0 = 0;
        tmp->unk4 = 0;
        func_10017594(tmp->unk8);
        tmp->unk8 = 0;
    }
}

void func_1001123C(u16 arg0) {
    struct120 *tmp = &D_800425E0[arg0 & 0xF];

    if ((tmp->unk8 != 0) && (tmp->unk0 == arg0)) {
        if (func_100112BC(arg0, 1) == 0) {
            func_10017594(tmp->unk8);
            tmp->unk8 = 0;
        }
    }
}

s32 func_100112BC(s32 arg0, s32 arg1) {
    struct49 *temp_a0;
    s32 temp_v1 = D_80041F50;

    if (temp_v1 < 16) {
        temp_a0 = &D_80041F10[temp_v1];
        temp_a0->unk0 = arg0;
        temp_a0->unk2 = arg1;
        temp_a0->unk3 = arg0 & 0xF;
        D_80041F50 = temp_v1 + 1;
        return 1;
    } else {
        return 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_10011310.s")

s32 func_1001147C(u16 arg0) {
    struct120 *tmp;

    if (arg0 != 0) {
        tmp = &D_800425E0[arg0 & 0xF];
        if (tmp->unk0 == arg0) {
            return tmp->unk4 & 0x7FFF;
        }
    }
    return -1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_100114D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_10011624.s")
void func_10011BB8(void) {
    s32 i;
    s32 j;
    s32 step;

    if (D_80041F60 == 0 && D_80041F61 == 0) {
        for (i = 0; i <= D_80082FA0; i++) {
            u8 *obj = (u8 *)&D_800DBFF0[i];

            if (D_80082FA0 != 0 || (*(s32 *)(obj + 0x2C) & 0x80000)) {
                D_80042308[i].x = *(f32 *)(obj + 0x2F8);
                D_80042308[i].y = *(f32 *)(obj + 0x2FC);
                D_80042308[i].z = *(f32 *)(obj + 0x300);
            } else {
                D_80042308[i].x = *(f32 *)(obj + 0x2A4);
                D_80042308[i].y = *(f32 *)(obj + 0x2A8);
                D_80042308[i].z = *(f32 *)(obj + 0x2AC);
            }
            D_80042308[i].ex = *(f32 *)(obj + 0x2F8);
            D_80042308[i].ey = *(f32 *)(obj + 0x2FC);
            D_80042308[i].ez = *(f32 *)(obj + 0x300);
            D_80042308[i].f = *(f32 *)(obj + 0x380);
        }
        func_10011310();
        func_10011624(D_80041FE0, &D_80042B00, 0, D_80042B00);
        for (i = 0, j = 0; i < D_80042B00; i++) {
            D_80041FE0[j] = D_80041FE0[i];
            if (!(D_80041FE0[j].unk10 & 0x80)) {
                j++;
            }
        }
        D_80042B00 = j;
    }
    if (D_80041F54 != D_80041FDC || D_80041F60 != D_80041F61) {
        if (D_80041F61 == 1) {
            func_10017780(0, 0);
            func_10017780(1, 0);
        } else {
            func_10017780(0, D_80041F54);
            func_10017780(1, D_80041F54);
            step = (D_80041FDC - D_80041F54) * D_80041F58;
            if (step != 0) {
                D_80041F54 += step;
            } else {
                D_80041F54 = D_80041FDC;
            }
        }
        D_80041F60 = D_80041F61;
    }
}

void func_10011E88(s32 arg0) {
}

void func_10011E94(s32 arg0) {
    if (arg0) {
        D_80041F61 = 1;
    } else {
        D_80041F61 = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_10011EB8.s")
// NON-MATCHING: whats going on here
// u16 func_10011EB8(s32 arg0, s16 *arg1, s32 arg2, s32 arg3) {
//     struct120 *temp_v1_2;
//     s32 temp_v0;
//     s32 temp_a0;
//
//     temp_v0 = func_1510F8CC(arg0);
//     if (arg1 != NULL) {
//         if (D_80082FA0 != 0) {
//             *arg1 = 0x7FFF / (D_80082FA0 + 1);
//         } else {
//             *arg1 = 0x7FFF;
//         }
//     }
//     temp_v1_2 = &D_8002C240[temp_v0 + arg2];
//     temp_a0 = temp_v1_2->unk0;
//     if (temp_v1_2->unk2 >= 2) {
//         temp_a0 = func_1000F568(temp_v0, temp_v1_2->unk2);
//     }
//     return temp_a0;
// }
