#include <ultra64.h>

#include "functions.h"
#include "variables.h"

void func_151D3354(struct224 *arg0);
void func_151D3308(struct224 *arg0);

void func_151D2AB0(s32 arg0) {
    u32 tmp;

    (&D_800E0950)[arg0] = (&D_800E0950)[arg0] + 1;

    if ((&D_800E0950)[arg0] < 2) {
        D_800E0990[arg0] = func_1502B5C8(&tmp, 2, 9, D_800AB140[arg0]);
        D_800E0968[arg0] = tmp >> 4;
    }
}

void func_151D2B4C(s32 arg0) {
    if ((&D_800E0950)[arg0] != 0) {
        (&D_800E0950)[arg0] = (&D_800E0950)[arg0] - 1;
        if ((&D_800E0950)[arg0] == 0) {
            func_100043B4(D_800E0990[arg0], 4);
        }
    }
}

struct224 *func_151D2BA4(void *arg0, struct17 *arg1, s32 arg2, u8 arg3, s32 arg4) {
    struct224 *tmp = func_15167A68(0x3D, arg4, arg2 + 0x48, 1, arg3, 1);

    if (tmp == NULL) {
        return NULL;
    }
    memcpy(&tmp->unk10, arg0, 0x24);
    *(struct17 *)&tmp->unk34 = *arg1;
    func_151D3308(tmp);
    return tmp;
}

void func_151D2C40(struct_eu_1FFF60_child *arg0) {
    struct_eu_1FFF60_parent *parent = arg0->unk10;
    struct17 pos;

    if (parent->unk0 == 0 || parent->unk4 == 0xFF || parent->unk3B != arg0->unk14 || parent->unk1D4 == NULL ||
        (parent->unk74 & 0xF) == 0xF) {
        func_1516972C(arg0);
        return;
    }
    func_15143134(&arg0->unk18, &pos, parent->unk1D4 + (arg0->unk24 << 6));
    if (arg0->unk28 & 1) {
        arg0->unk26 -= D_800BE9E4;
        if (arg0->unk26 < 0) {
            if (arg0->unk2A != -1) {
                D_8008FFE8[arg0->unk2A](arg0, &pos);
            }
            arg0->unk2C = 0;
            func_1516972C(arg0);
            return;
        }
    }
    if (arg0->unk29 != -1) {
        if (D_8008FFE0[arg0->unk29](arg0, &pos) == 0) {
            func_1516972C(arg0);
            return;
        }
    }
    arg0->unk34 = pos;
}

void func_151D2DAC(struct102 *arg0) {
    func_151D3354(arg0);
}

void func_151D2DCC(struct102 *arg0) {
    struct102 *tmp = arg0;

    func_151D2DAC(tmp);

    if (tmp->unk2C != 0) {
        func_1516972C(tmp->unk2C);
    }
    func_15169804(tmp);
}

void func_151D2E14(struct102 *arg0) {
    struct102 *tmp = arg0;

    func_151D2DAC(tmp);

    if (tmp->unk2C != 0) {
        func_1516979C(tmp->unk2C);
    }
    func_15169824(tmp);
}

void func_151D2E5C(struct102 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_v0;
    s32 temp_v1;
    u8 t14;
    u8 t4;

    if (arg2 == 0) {
        temp_v0 = *(s32 *)((u8 *)arg0 + 0x10);
        temp_v1 = *(s32 *)(arg1 + 0);
        t14 = *((u8 *)arg0 + 0x14);
        t4 = *(arg1 + 4);
        if ((temp_v0 == temp_v1) || (t14 == t4)) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        temp_v0 = *(s32 *)(arg1 + 0);
        temp_v1 = *(s32 *)((u8 *)arg0 + 0x10);
        if (temp_v0 == *(s32 *)((u8 *)arg0 + 0x10)) { // fakematch: reread of the field flips the cmp operands
            *(s32 *)((u8 *)arg0 + 0x10) = *(s32 *)(arg1 + 4);
            *((u8 *)arg0 + 0x14) = *(arg1 + 9);
            return;
        }
        if (*(s32 *)(arg1 + 4) == *(s32 *)((u8 *)arg0 + 0x10)) { // fakematch: reread
            *(s32 *)((u8 *)arg0 + 0x10) = temp_v0;
            *((u8 *)arg0 + 0x14) = *(arg1 + 8);
        }
    }
}
// NON-MATCHING: one bnel has its operands swapped (bnel t9, v1)
// void func_151D2E5C(struct224 *arg0, struct223 *arg1, u8 arg2) {
//     s32 temp_v0;
//     s32 temp_v1;
//     u8 temp_a2;
//     u8 temp_a3;
//
//     if (arg2 == 0) {
//         temp_v0 = arg0->unk10;
//         temp_v1 = arg1->unk0;
//         temp_a2 = arg0->unk14;
//         temp_a3 = arg1->unk4.ub;
//         if (temp_v0 == temp_v1 || temp_a2 == temp_a3) {
//             func_1516972C(arg0);
//         }
//     } else if (arg2 == 0x2D) {
//         temp_v0 = arg1->unk0;
//         temp_v1 = arg0->unk10;
//         if (temp_v0 == temp_v1) {
//             arg0->unk10 = arg1->unk4.w;
//             arg0->unk14 = arg1->unk9;
//         } else if (arg1->unk4.w == temp_v1) {
//             arg0->unk10 = temp_v0;
//             arg0->unk14 = arg1->unk8;
//         }
//     }
// }

void *func_151D2F00(void *arg0, s32 arg1, u8 arg2, s32 arg3) {
    u8 *temp_v0 = func_15167A68(0x3E, arg3, arg1 + 0x30, 1, arg2, 1);

    if (temp_v0 == NULL) {
        return NULL;
    }
    memcpy(temp_v0 + 0x10, arg0, 0x10);
    *(s16 *)(temp_v0 + 0x20) = 0;
    *(s32 *)(temp_v0 + 0x24) = 0;
    *(s32 *)(temp_v0 + 0x28) = 0;
    temp_v0[0x18] &= ~2;
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2F90.s")

void func_151D3130(struct_eu_1FFF60 *arg0) {
    struct_eu_1FFF60_child *child;

    if (D_8008FFFC[arg0->unk1D] != NULL) {
        D_8008FFFC[arg0->unk1D](arg0);
    }
    child = arg0->unk24;
    while (child != NULL) {
        struct_eu_1FFF60_child *next = child->unk40;
        if (child->unk2A != -1) {
            D_8008FFE8[child->unk2A](child, &child->unk34);
        }
        child->unk2C = 0;
        func_1516972C(child);
        child = next;
    }
    func_1514EDF0(arg0, arg0->unk10);
}

void func_151D31F4(struct102 *arg0) {
    func_151D3130(arg0);
    func_15169804(arg0);
}

void func_151D3220(struct102 *arg0) {
    func_151D3130(arg0);
    func_15169824(arg0);
}

extern s32 D_80090004[];
void func_151D33FC(struct224 *, struct223 *);
void func_151D324C(struct224 *arg0, struct223 *arg1, u8 arg2) {
    s32 (*temp_v0_2)(struct224 *, struct223 *, u8);
    if (arg2 == 0) {
        func_151D33FC(arg0, arg1);
        goto dummy_label; dummy_label: ;
    } else if (arg2 == 0x2D) {
        if (arg0->unk10 == arg1->unk0) {
            arg0->unk10 = arg1->unk4.w;
            arg0->unk14 = arg1->unk9;
        } else if (arg0->unk10 == arg1->unk4.w) {
            arg0->unk10 = arg1->unk0;
            arg0->unk14 = arg1->unk8;
        }
    }
    temp_v0_2 = (void *)D_80090004[arg0->pad15[8]];
    if (temp_v0_2 != NULL) {
        temp_v0_2(arg0, arg1, arg2);
    }
}

void func_151D3308(struct224 *arg0) {
    struct224 *temp_v0;
    struct224 *temp_v1;

    temp_v0 = arg0->unk30;
    if (temp_v0 != 0) {
        arg0->unk40 = temp_v0->unk24;
        temp_v1 = temp_v0->unk24;
        if (temp_v1 != 0) {
            temp_v1->unk44 = arg0;
        } else {
            temp_v0->unk28 = arg0;
        }
        arg0->unk44 = 0;
        temp_v0->unk24 = arg0;
        temp_v0->unk20 += 1;
        arg0->unk30 = temp_v0;
    }
}

void func_151D3354(struct224 *arg0) {
    struct224 *temp_v0;
    struct224 *temp_v1;
    struct224 *temp_v2;

    if (arg0->unk30) {
        temp_v0 = arg0->unk30;
        if (temp_v1 = arg0->unk44) {
            temp_v1->unk40 = arg0->unk40;
        } else {
            temp_v0->unk24 = arg0->unk40;
        }

        if (temp_v2 = arg0->unk40) {
            temp_v2->unk44 = arg0->unk44;
        } else {
            temp_v0->unk28 = arg0->unk44;
        }

        temp_v0->unk20 -= 1;
    }
}

void func_151D33B8(struct224 *arg0) {
    while (arg0->unk20 > 0) {
        func_1516972C(arg0->unk24);
    };
}

void func_151D33FC(struct224 *arg0, struct223 *arg1) {
    s32 tmp0;
    s32 tmp1;
    s32 tmp2;
    s32 tmp3;

    tmp0 = arg0->unk10;
    tmp1 = arg0->unk14;
    tmp2 = arg1->unk4.ub;
    tmp3 = arg1->unk0;
    if ((tmp0 == tmp3) || (tmp2 == tmp1)) {
        func_1516972C(arg0);
    }
}

void func_151D343C(s32 arg0, u8 arg1) {
    const s32 sp1C[1] = {0x3E};

    func_15169260(sp1C, 0x1, arg0, arg1);
}
