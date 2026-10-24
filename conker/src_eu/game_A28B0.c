#include <ultra64.h>

#include "functions.h"
#include "variables.h"


void func_15075400(s32 arg0) {
    s32 tmp;
    u8 i;

    if (arg0 < 247) {
        D_800D154C->unk218 += arg0;
        return;
    }

    for (i = 0; i < 100; i++) {
        if (D_800D154C->unk218->unk0 < 247) {
            D_800D154C->unk218++;
        } else {
            tmp = D_800D154C->unk218->unk0 & 0xFF;
            ((u8*)D_800D154C->unk218) += 1;
            if (arg0 == tmp) {
                D_800D154C->unk218 -= 1;
                return;
            }
        }
    }
}

void func_15075498(void) {
    s32 tmp = D_800D1893 & 0x7F;

    if (tmp != 0x7F) {
        D_800D154C->unk244 = tmp;
    }
    D_800D154C->unkF4 &= ~0x143E;
    if (D_800D1890 == 0xFA) {
        D_800D154C->unkF4 |= 0x22;
    } else if (D_800D1890 == 0xFB) {
        D_800D154C->unkF4 |= 4;
    }
    if ((D_800D1893 & 0x80) != 0) {
        D_800D154C->unkF4 |= 16;
    }
}

void func_15075548(void) {
    f32 temp_f6;
    u8 temp_a0;

    D_800D154C->unk223 = 0;
    D_800D154C->unk21C = D_800D1890 * 100;
    temp_a0 = D_800D1892;
    if (temp_a0 != 0xFF) {
        temp_f6 = temp_a0;
        D_800D154C->unk44 = temp_f6;
        if (D_800D154C->unk44 == 1.0f) {
            D_800D154C->unk44 = 0.5f;
        }
        if (D_800BE616 != 0) {
            if ((D_800D154C->id == 40) && ((D_800D154C->unk31C->unk128 & 1) != 0)) {
                D_800D154C->unk44 *= D_8009A13C;
            }
        }
    }
    func_15075498();
}

#ifdef NON_MATCHING
void func_15075650(void) {
    u8 sp1F;
    u8 sp1D;
    f32 var_f6;
    s32 var_a0;
    struct127 *var_v1;
    u8 temp_a1;
    u8 temp_t2;
    u8 temp_t4;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 temp_v0_3;
    u8 var_a2;

    var_v1 = D_800D154C;
    temp_v0 = var_v1->unk21F;
    var_a0 = (D_800D2528[var_v1->unk13F] - 1) & 0xFF;
    if (temp_v0 != 0) {
        var_a0 = temp_v0 & 0xFF;
    }
    temp_a1 = var_v1->unk220;
    temp_t2 = (var_a0 - temp_a1) & 0xFF;
    if (D_800D1891 == 0xFF) {
        if (var_v1->unk223 != 0xD) {
            sp1F = temp_t2;
            D_800D154C->unk21E = (func_150ADA20() % sp1F) + D_800D154C->unk220;
            goto block_14;
        }
    } else if (D_800D1891 == 0xFE) {
        if (var_v1->unk223 != 0xD) {
            temp_v0_2 = var_v1->unk21E;
            var_a2 = (temp_v0_2 - 1) & 0xFF;
            if ((s32) temp_a1 >= (s32) temp_v0_2) {
                var_a2 = (var_a0 - 1) & 0xFF;
            }
            sp1D = var_a2;
            sp1F = temp_t2;
            var_v1 = D_800D154C;
            temp_t4 = ((func_150ADA20() % temp_t2) + var_v1->unk220) & 0xFF;
            if (var_a2 != temp_t4) {
                var_v1->unk21E = temp_t4;
                var_v1 = D_800D154C;
            }
        }
    } else {
        if (D_800D1891 == 0xFF) {
            var_v1->unk21E = var_a0 - 1;
        } else {
            var_v1->unk21E = D_800D1891;
        }
block_14:
        var_v1 = D_800D154C;
    }
    var_v1->unk223 = 0;
    D_800D154C->unk21C = D_800D1890 * 0x64;
    if (D_800D1892 != 0xFF) {
        var_f6 = (f32) D_800D1892;
        if ((s32) D_800D1892 < 0) {
            var_f6 += 4294967296.0f;
        }
        D_800D154C->unk44 = var_f6;
        if (D_800D154C->unk44 == 1.0f) {
            D_800D154C->unk44 = 0.5f;
        }
    }
    temp_v0_3 = D_800D154C->unk220;
    if ((s32) D_800D154C->unk21E < (s32) temp_v0_3) {
        D_800D154C->unk21E = temp_v0_3;
    }
    func_15075498();
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075650.s")
#endif
// NON-MATCHING: 95% there
// void func_15075650(void) {
//     u8 phi_a0;
//     u8 phi_a2;
//
//     phi_a0 = D_800D2108[D_800D154C->unk13F] - 1;
//     if (D_800D154C->unk21F != 0) {
//         phi_a0 = D_800D154C->unk21F;
//     }
//     phi_a0 = phi_a0 - D_800D154C->unk220;
//     if (D_800D1891 == 0xFF) { // -1
//         if (D_800D154C->unk223 != 0xD) {
//             D_800D154C->unk21E = (func_150ADA20() % (u32) phi_a0) + D_800D154C->unk220;
//         }
//     } else if (D_800D1891 == 0xFE) { // -2
//         if (D_800D154C->unk223 != 0xD) {
//             phi_a2 = D_800D154C->unk21E - 1;
//             if (D_800D154C->unk21E <= D_800D154C->unk220) {
//                 phi_a2 = phi_a0 - 1;
//             }
//             phi_a0 = (func_150ADA20() % (u32) phi_a0) + D_800D154C->unk220;
//             if (phi_a0 != phi_a2) {
//                 D_800D154C->unk21E = phi_a0;
//             }
//         }
//     } else {
//         if (D_800D1891 == 0xFF) { // impossible?
//             D_800D154C->unk21E = phi_a0 - 1;
//         } else {
//             D_800D154C->unk21E = D_800D1891;
//         }
//     }
//
//     D_800D154C->unk223 = 0;
//     D_800D154C->unk21C = D_800D1890 * 0x64;
//
//     if (D_800D1892 != 0xFF) {
//         D_800D154C->unk44 = D_800D1892;
//         if (D_800D154C->unk44 == 1.0f) {
//             D_800D154C->unk44 = 0.5f;
//         }
//     }
//
//     if (D_800D154C->unk21E < D_800D154C->unk220) {
//         D_800D154C->unk21E = D_800D154C->unk220;
//     }
//     func_15075498();
// }

#ifdef NON_MATCHING
void func_15075884(void) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;
    f32 var_f2;
    u8 *temp_v1;

    func_15075548();
    temp_v1 = D_800D2104[D_800D154C->unk13F] + (D_800D154C->unk21E * 8);
    temp_f2 = (f32) (*(s16 *)((u8 *)temp_v1 + 8)) - D_800D154C->x_position;
    temp_f12 = (f32) (*(s16 *)((u8 *)temp_v1 + 0xC)) - D_800D154C->z_position;
    var_f2 = (f32) D_800D1891;
    temp_f0 = sqrtf((temp_f2 * temp_f2) + (temp_f12 * temp_f12));
    if ((s32) D_800D1891 < 0) {
        var_f2 += 4294967296.0f;
    }
    D_800D154C->unk44 = 2.0f * (temp_f0 / var_f2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075884.s")
#endif
// NON-MATCHING: array index is wrong
// void func_15075884(void) {
//     f32 temp_f0;
//     f32 temp_f12;
//     f32 temp_f2;
//     struct169 *temp_v1;
//     f32 phi_f2;
//
//     func_15075548();
//     temp_v1 = D_800D2104[(D_800D154C->unk13F) + (D_800D154C->unk21E)];
//     temp_f2 = temp_v1->unk8 - D_800D154C->x_position;
//     temp_f12 = temp_v1->unkC - D_800D154C->z_position;
//     temp_f0 = sqrtf((temp_f2 * temp_f2) + (temp_f12 * temp_f12));
//     D_800D154C->unk44 = 2.0f * (temp_f0 / D_800D1891);
// }

#ifdef NON_MATCHING
void func_15075938(void) {
    s32 var_a0;
    s32 var_a2;
    u8 var_v0;
    u8 var_v1;

    var_a2 = 0;
    var_a0 = D_800D154C->unk21E - D_800D154C->unk221;
    if (var_a0 < 0) {
        var_v0 = D_800D2528[D_800D154C->unk13F];
        var_a0 = (var_a0 + var_v0) - 1;
    } else {
        var_v0 = D_800D2528[D_800D154C->unk13F];
        if (var_a0 >= (var_v0 - 1)) {
            var_a0 = (var_a0 - var_v0) + 1;
        }
    }
    var_v1 = D_800D1891;
    if (D_800D1891 == 0xFF) {
        var_v1 = var_v0 - 2;
    }
    if (D_800D1892 == 0) {
        if (var_v1 == var_a0) {
            goto block_16;
        }
    } else if (D_800D1892 == 1) {
        if (var_v1 != var_a0) {
            goto block_16;
        }
    } else if (D_800D1892 == 2) {
        if ((s32) var_v1 < var_a0) {
            goto block_16;
        }
    } else if (var_a0 < (s32) var_v1) {
block_16:
        var_a2 = 1;
    }
    if (var_a2 != 0) {
        func_15075400((s32) D_800D1890);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075938.s")
#endif
// NON-MATCHING: 2nd half ok, 1st is a mystery
// void func_15075938(void) {
//     u8 tmp;
//     u8 changed;
//     s32 temp_a0;
//     s32 phi_v1;
//     u8 temp_v0;
//
//     changed = 0;
//
//     temp_a0 = D_800D154C->unk21E - D_800D154C->unk221;
//     if (temp_a0 < 0) {
//         temp_v0 = D_800D154C->unk13F + D_800D2108;
//         temp_a0 = (temp_a0 + temp_v0) - 1;
//     } else {
//         temp_v0 = D_800D154C->unk13F + D_800D2108;
//         if ((temp_v0 - 1) <= temp_a0) {
//             temp_a0 = (temp_a0 - temp_v0) + 1;
//         }
//     }
//
//     if (D_800D1891 == 0xFF) {
//         phi_v1 = temp_v0 - 2;
//     } else {
//         phi_v1 = D_800D1891;
//     }
//
//     if (D_800D1892 == 0) {
//         if (phi_v1 == temp_a0) {
//             changed = 1;
//         }
//     } else if (D_800D1892 == 1) {
//         if (phi_v1 != temp_a0) {
//             changed = 1;
//         }
//     } else if (D_800D1892 == 2) {
//         if (phi_v1 < temp_a0) {
//             changed = 1;
//         }
//     } else {
//         if (phi_v1 > temp_a0) {
//             changed = 1;
//         }
//     }
//
//     if (changed) {
//         func_15075400(D_800D1890);
//     }
// }

void func_15075A50(void) {
    u8 temp_v0 = D_800D154C->unk21E;
    if (((D_800D1892 == 0) && (D_800D1891 == temp_v0)) ||
       ((D_800D1892 == 1) && (D_800D1891 != temp_v0))) {
        func_15075400(D_800D1890);
    }
}

void func_15075AAC(void) {
    f32 dx;
    f32 dz;
    s16 *temp_v0;

    func_15075548();
    temp_v0 = ((s16 (*)[4])D_800D2104[D_800D154C->unk13F])[D_800D1891];
    dx = temp_v0[0] - D_800D154C->x_position;
    dz = temp_v0[2] - D_800D154C->z_position;
    if ((fabsf(dx) + fabsf(dz)) < 40.0f) {
        D_800D154C->unk21C = 0;
        D_800D154C->xz_velocity = 0.0f;
    }
}

void func_15075B60(void) {
    func_15075548();
    D_800D154C->unk223 = 10;
}

void func_15075B8C(void) {
    func_15075650();
    D_800D154C->unk223 = 10;
}

void func_15075BB8(void) {
    func_15075548();
    D_800D154C->unk22C |= 2;
}

void func_15075BE8(void) {
    if (D_800D1893 != 0) {
        D_800D154C->unk22C |= 0x80;
    }
    D_800D154C->unk233 = D_800D1890;
}

void func_15075C24(void) {
    if (D_800D1893 != 1) {
        D_800D154C->y_velocity = (s16)((D_800D1892 << 8) | D_800D1890);
    }
    if (D_800D1893 != 2) {
        D_800D154C->gravity = (s16)(s8)D_800D1891;
    }
}

void func_15075CA0(void) {
    func_15075548();
    D_800D154C->unk223 = 1;
}

void func_15075CCC(void) {
    func_15075548();
    D_800D154C->unk223 = 16;
    D_800D154C->unk231 = D_800D1891;
}

void func_15075D0C(void) {
    func_15075548();
    D_800D154C->unk223 = 15;
}

void func_15075D38(void) {
    func_15075CA0();
    D_800D154C->unk223 = 14;
}

void func_15075D64(void) {
    func_15075548();
    D_800D154C->unk223 = 12;
    D_800D154C->unk222 = 0;
}

void func_15075D9C(void) {
    func_15075548();
    D_800D154C->unk223 = 9;
}

void func_15075DC8(void) {
    func_15075CA0();
}

void func_15075DE8(void) {
    if (D_800D1891 == 0) {
        D_800D1891 = D_800D154C->unk232;
    }
    if (D_800D1893 != 0) {
        D_800D154C->unk232 = D_800D1893;
    }
    D_800D154C->unk218 = func_1507BB28(0, D_800D1891);
    D_800D154C->unk218 -= 1;
}

void func_15075E6C(void) {
    func_15075548();
    D_800D154C->unk223 = 2;
}

void func_15075E98(void) {
    D_800D154C->unk235 = D_800D1890;
}

void func_15075EB4(void) {
    if ((func_150ADA20() % 0x64U) < D_800D1892) {
        func_15075400(D_800D1890);
    }
}

void func_15075F00(void) {
    D_800D154C->unk234 = D_800D1890;
    D_800D154C->unk236 = D_800D1891;
    D_800D154C->unk237 = D_800D1892;
}

void func_15075F40(void) {
    func_15075548();
    D_800D154C->unk223 = 3;
}

void func_15075F6C(void) {
    if (D_800D1890 != 0) {
        if (D_800D1892 == 0) {
            D_800D154C->y_velocity = D_800D1890;
        } else {
            D_800D154C->y_velocity = -D_800D1890;
        }
    }
    if (D_800D1891 != 0) {
        D_800D154C->gravity = D_800D1891;
    }
    D_800D154C->unk3A = D_800D1893;
}

#ifdef NON_MATCHING
extern f32 D_8009A500; /* 1 / 12 */

// path_jump_to_point: P210: script command: jump (ballistic) to point D_800D1891 of the object's path
// (D_800D2104[unk13F]); unk21E = that point. Flight time t = 2 * distance / speed (unk44); below 12 the speed is
// scaled by t / 12 and t = 12. unk21C = t * 100, upward velocity = gravity * t / 2, unk223 = 4.
void func_1507602C(void) {
    s16 *pt;
    f32 dx, dz;
    f32 t;

    func_15075548();
    D_800D154C->unk21E = D_800D1891;
    pt = (s16 *)(D_800D2104[D_800D154C->unk13F] + D_800D1891 * 8 + 8);
    dx = pt[0] - D_800D154C->x_position;
    dz = pt[2] - D_800D154C->z_position;
    t = sqrtf(dx * dx + dz * dz) / D_800D154C->unk44;
    t = t + t;
    if (t < 12.0f) {
        D_800D154C->unk44 = D_800D154C->unk44 * (t * D_8009A500);
        t = 12.0f;
    }
    D_800D154C->unk21C = t * 100.0f;
    D_800D154C->y_velocity = D_800D154C->gravity * t * 0.5f;
    D_800D154C->unk223 = 4;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507602C.s")
#endif
// NON-MATCHING: indexing is wrong
// void func_1507602C(void) {
//     f32 temp_f12;
//     f32 temp_f14;
//     f32 temp_f2;
//     struct169 *temp_v1;
//
//     func_15075548();
//     D_800D154C->unk21E = D_800D1891;
//     temp_v1 = D_800D2104[D_800D154C->unk13F + D_800D1891]; // wrong
//     temp_f2 = temp_v1->unk8 - D_800D154C->x_position;
//     temp_f12 = temp_v1->unkC - D_800D154C->z_position;
//     temp_f14 = 2.0f * (sqrtf((temp_f2 * temp_f2) + (temp_f12 * temp_f12)) / D_800D154C->unk44);
//     if (temp_f14 < 12.0f) {
//         D_800D154C->unk44 *= temp_f14 * D_8009A140;
//         temp_f14 = 12.0f;
//     }
//     D_800D154C->unk21C = temp_f14 * 100.0f;
//     D_800D154C->y_velocity = D_800D154C->gravity * temp_f14 * 0.5f;
//     D_800D154C->unk223 = 4;
// }

void func_150761C8(void) {
    func_15075650();
    D_800D154C->unk223 = 5;
}

void func_150761F4(void) {

    D_800D154C->unk223 = 6;
    D_800D154C->unk22C &= 0xFFFE;
}

void func_15076220(void) {
    func_150761F4();
    D_800D154C->unk22C |= 1;
}

void func_15076250(void) {
    s32 tmp = (D_800D1890 << 8) | D_800D1891;
    func_15060778(tmp, D_800D154C, 0x7D00, -0x64, 0x1F4, 0x9C4, D_800D1892);
}

void func_150762B0(void) {
    func_1000CBA8(D_800D1890);
}

void func_150762D4(void) {
    func_15166F10(D_800D154C->x_position, D_800D154C->y_position + 100.0f, D_800D154C->z_position, 0.45f, 0xFF, 0);
}

void func_15076340(void) {
    if (D_800D154C->unk107 == 0) {
        func_15075400(D_800D1890);
    }
    if (D_800D1891 != 0) {
        D_800D154C->unk107 = 0;
    }
}

void func_15076394(void) {
    D_800D154C->unk236 = D_800D1890;
}

void func_150763B0(void) {

    if (D_800D1890 == 128) {
        D_800D154C->unk1E5 = D_800D154C->unk144->unkF;
    } else {
        D_800D154C->unk1E5 = D_800D1890;
    }
    D_800D154C->unk1E7 = 0;

    if (D_800D1892 != 0) {
        D_800D154C->unk1E5 += (func_150ADA20() % (u32) D_800D1892);
    }
    if (D_800D1893 == 1) {
        D_800D154C->unk1E6 = 0;
        D_800D154C->unk1E8 = 0;
        return;
    }
    if (D_800D1893 == 2) {
        D_800D154C->unk1E6 = D_800D1891;
        D_800D154C->unk1E8 = 0;
        return;
    }
    if (D_800D1891 == 0) {
        D_800D154C->unk1E6 = D_800D154C->unk1E5;
        D_800D154C->unk1E8 = 0;
    }
}

void func_150764C8(void) {
    D_800D154C->unk238 = D_800D1890;
}

void func_150764E4(void) {
    D_800D154C->unk239 = D_800D1890;
}

void func_15076500(void) {
    D_800D154C->unk22E = (D_800D1890 << 8) | D_800D1891;
}

void func_1507652C(void) {
    if (D_800D1891 != 0) {
        D_800CC3F5[D_800D154C->unk124 * 0x32C] = D_800D1890;
    } else {
        D_800D154C->immune = D_800D1890;
    }
}

void func_1507659C(void) {
    D_800D154C->y_position = D_800D154C->y_position + D_800D1890 * 100;
    if (D_800D1893 != 0) {
        D_800D154C->y_position = 1800.0f;
    }
}

void func_15076600(void) {
}

void func_15076608(void) {
    D_800D154C->unk24A = D_800D1890;
}

void func_15076624(void) {
    s32 tmp = (D_800D1890 << 0x18) | (D_800D1891 << 0x10) | (D_800D1892 << 8) | D_800D1893;
    D_800D154C->unkF8 |= tmp;
}

s32 func_15076678(void) {
    s32 tmp = (D_800D1890 << 0x18) | (D_800D1891 << 0x10) | (D_800D1892 << 8) | D_800D1893;
    D_800D154C->unkF8 &= ~tmp;
}

void func_150766D0(void) {
    if (((D_800D154C->unk28 > 0.0f) && (D_800D1890 == 0)) ||
        (((D_800D1890 * 0x32) < D_800D154C->unk28) && (D_800D1890 != 0))) {
        D_800D154C->unk21C = 99;
        D_800D154C->unk218 -= 1;
    }
}

void func_15076760(void) {
}

// ???
void func_1504715C(f32 *, struct127 *);
#ifdef NON_MATCHING
s32 func_1514B8D4(f32 *, f32 *, s32, s32); /* P183: s32 as its C definition (stale v0, unused) */
#else
void func_1514B8D4(f32 *, f32 *, s32, s32);
#endif
void func_15197A7C(struct127 *);

void func_15076768(void) {
    f32 pos[3];

    switch (D_800D1890) {
    case 0:
        func_15197A7C(D_800D154C);
        break;
    case 1:
        pos[0] = *(f32 *)((u8 *)D_800D154C + 0x14);
        pos[1] = -390.0f;
        pos[2] = *(f32 *)((u8 *)D_800D154C + 0x1C);
        {
            f32 buf[9];
            func_1504715C(buf, D_800D154C);
            func_1514B8D4(pos, buf, 0xFF, 0);
        }
        break;
    }
}


void func_150767F4(void) {
    struct127 *temp_v1 = &D_800CC2D0[D_800D154C->unk222];
    u8 temp_t0 = func_1505A630(temp_v1->x_position - D_800D154C->x_position, D_800D154C->z_position - temp_v1->z_position, 0) >> 8;

    if ((((temp_t0 - (D_800CC2D0[D_800D154C->unk222].unk7A >> 8)) + D_800D1891) & 0xFF) < (D_800D1891 * 2)) {
        func_15075400(D_800D1890);
    }
}

#ifdef NON_MATCHING
int func_1507BB28(s32, s32);

// find_visible_target: P210: script command: looks for the nearest object the current one can see: live (state,
// health), targetable (unkF8 bit 0x20), not itself, of another id unless D_800D1891 is set, within 50 in height,
// closer than D_800D1890 * 8 (func_1505A72C), and inside its view cone (width byte 0x17 of its type record
// D_800D1C90[id], in 1/256 turns around heading unk76 >> 8 + unk2CA). The nearest one is stored as unkA8 =
// 0x80 + its number; then the object's script jumps to D_800D1893 and, when D_800D1892 is set, the target's
// script to D_800D1892 with unk222 = the current object's number.
void func_150768DC(void) {
    s32 self = ((s32)D_800D154C - (s32)D_800CC2D0) / 0x32C;
    f32 best = D_800D1890 * 8;
    struct127 *o = D_800CC2D0;
    struct127 *t;
    s32 i;
    f32 d;
    s32 fov;
    u16 ang;

    D_800D154C->unkA8 = 0;
    for (i = 0; i < 25; i++, o++) {
        if (o->interaction_state == 0 || o->health == 0 || !(o->unkF8 & 0x20) || i == self) {
            continue;
        }
        if (D_800D1891 == 0 && D_800D154C->id == o->id) {
            continue;
        }
        if (50.0f < fabsf(D_800D154C->y_position - o->y_position)) {
            continue;
        }
        d = func_1505A72C(D_800D154C, o);
        if (!(d < best)) {
            continue;
        }
        fov = D_800D1C90[D_800D154C->id]->unk17;
        ang = func_1505A630(o->x_position - D_800D154C->x_position, D_800D154C->z_position - o->z_position, 0);
        if (((((D_800D154C->unk76 >> 8) + D_800D154C->unk2CA) - (ang >> 8) + fov / 2) & 0xFF) < fov) {
            D_800D154C->unkA8 = i + 0x80;
            best = d;
        }
    }
    if (D_800D154C->unkA8 != 0) {
        D_800D154C->unk218 = (struct216 *)func_1507BB28(0, D_800D1893);
        D_800D154C->unk218--;
        if (D_800D1892 != 0) {
            t = &D_800CC2D0[D_800D154C->unkA8 & 0x7F];
            t->unk218 = NULL;
            t->unk232 = D_800D1892;
            t->unk222 = self;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150768DC.s")
#endif
// NON-MATCHING: almost JUSTREG
// void func_150768DC(void) {
//     u8 temp_s2;
//     f32 temp_f20;
//     s32 temp_fp;
//     struct127 *temp_v0;
//     struct127 *current;
//     f32 phi_f22;
//     s32 i;
//     u8 tmp0;
//     struct124 *foo;
//     u8 tmp1;
//
//
//     phi_f22 = D_800D1890 * 8;
//     D_800D154C->unkA8 = 0;
//     temp_fp = ((s32)D_800D154C - (s32)D_800CC2D0) / (s32)sizeof(struct127);
//
//     for (i = 0; i < 25; i++) {
//         current = &D_800CC2D0[i];
//         if ((current->unk0 != 0) && (current->health != 0) && ((current->unkF8 & 0x20) != 0) && (i != temp_fp)) {
//             if ((D_800D1891 != 0) || (D_800D154C->id != current->id)) {
//                 if (!(fabsf(D_800D154C->y_position - current->y_position) > 50.0f)) {
//                     temp_f20 = func_1505A72C(D_800D154C, current);
//                     if (temp_f20 < phi_f22) {
//                         foo = D_800D1C90[D_800D154C->id];
//                         temp_s2 = foo->unk17;
//                         tmp1 = func_1505A630(current->x_position - D_800D154C->x_position, D_800D154C->z_position - current->z_position, 0) >> 8;
//                         if ((((((D_800D154C->unk76 >> 8) + D_800D154C->unk2CA) - tmp1) + (temp_s2 / 2)) & 0xFF) < temp_s2) {
//                             D_800D154C->unkA8 = i;
//                             phi_f22 = temp_f20;
//                         }
//                     }
//                 }
//             }
//         }
//     }
//
//     if (D_800D154C->unkA8 != 0) {
//         D_800D154C->unk218 = func_1507BB28(0, D_800D1893);
//         D_800D154C->unk218 -= 1;
//         tmp0 = D_800D1892;
//         if (tmp0 != 0) {
//             temp_v0 = &D_800CC2D0[D_800D154C->unkA8 & 0x7F];
//             temp_v0->unk218 = 0;
//             temp_v0->unk232 = tmp0;
//             temp_v0->unk222 = temp_fp;
//         }
//     }
// }

void func_15076B5C(void) {
    D_800D154C->unk222 = (D_800D154C->unkA8 & 0x7F);
}

void func_15076B78(void) {
    D_800D154C->unk5 = D_800D1890;
}

void func_15076B94(void) {
    s32 idx = ((s32)D_800D154C - (s32)D_800CC2D0) / (s32)sizeof(struct127);

    if (D_800D1891) {
        idx = 25;
    }
    while (idx != 0) {
        if ((D_800D1890 == D_800CC2D0[idx-1].id) && (D_800CC2D0[idx-1].health != 0)) {
            func_15075548();
            D_800D154C->unk223 = 9;
            D_800D154C->unk222 = idx - 1;
            D_800D154C->unk21C = 1000;
            return;
        }
        idx--;
    };
}

void func_15076C7C(void) {
    func_1506160C(D_800D154C, 1, D_800D1890, 0, 0);
}

void func_15076CB4(void) {
    D_800D154C->unk76 = D_800D154C->unk78;
}

void func_15076CCC(void) {
    D_800D154C->unk21C = 10000;
    func_15060F28(D_800D154C, 1);
}

void func_15076D04(void) {
    D_800D154C->xz_velocity = D_800D1890;
}

#ifdef NON_MATCHING
// object_set_scale: P210: script command: sets the current object's scale from the command bytes (two s16 in
// hundredths: D_800D1890 / D_800D1891 = xz, D_800D1892 / D_800D1893 = y, low byte first; D_8009A504 = 0.01),
// copies it to unk154 / unk158 and applies it with func_15062BDC.
void func_15076D3C(void) {
    s16 xz = D_800D1890 | (D_800D1891 << 8);
    s16 y = D_800D1892 | (D_800D1893 << 8);

    D_800D154C->xz_scale = xz * D_8009A504;
    D_800D154C->y_scale = y * D_8009A504;
    D_800D154C->unk154 = D_800D154C->xz_scale;
    D_800D154C->unk158 = D_800D154C->y_scale;
    func_15062BDC(D_800D154C, D_800D154C->xz_scale, D_800D154C->y_scale);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076D3C.s")
#endif
// ???
// void func_15076D3C(void) {
//     s32 temp_a3;
//     s32 tmp2;
//
//     temp_a3 = D_800D1892 | (D_800D1893 << 8);
//     tmp2 = D_800D1890 | (D_800D1891 << 8);
//     D_800D154C->xz_scale = (s16)tmp2 * D_8009A144;
//     D_800D154C->y_scale = (s16)temp_a3 * D_8009A144;
//     D_800D154C->unk154 = D_800D154C->xz_scale;
//     D_800D154C->unk158 = D_800D154C->y_scale;
//     func_15062BDC(&D_800D154C, D_800D154C->xz_scale, D_800D154C->y_scale);
// }

void func_15076DF4(void) {
    D_800D154C->interaction_state = D_800D1890;
}

void func_15076E10(void) {
    D_800D154C->unk1D0 = D_800D1890;
    D_800D154C->unk22C |= D_800D1891;
}

void func_15076E48(void) {
}

void func_15076E50(void) {
    func_15075548();
    D_800D154C->y_velocity = ((f32) (u32) (func_150ADA20() % 0x14U) + 55.0f);
    D_800D154C->gravity = 2.0f;
    D_800D154C->unk78 = func_150ADA20() % 0xFFFFU;
    D_800D154C->xz_velocity = (u32) ((func_150ADA20() % 0x14U) + 0xF);
    D_800D154C->unk44 = D_800D154C->xz_velocity;
    D_800D154C->unk223 = 7;
}

void func_15076F40(void) {
    D_800D154C->unk21C = 1000;
    func_15060F28(D_800D154C, 1);
}

void func_15076F78(void) {
    s8 tmp;
    tmp = D_800D1890;
    D_800D154C->unkCC = tmp;
    tmp = D_800D1891;
    D_800D154C->unkCE = tmp;
}

void func_15076FA8(void) {
    if (D_800D1893 == 0) {
        s16 tmp;
        tmp = (func_150ADA20() % (u32) D_800D1890) - (D_800D1890 / 2);
        D_800D154C->x_position += tmp * 3.0f;
        tmp = (func_150ADA20() % (u32) D_800D1891) - (D_800D1891 / 2);
        D_800D154C->z_position += tmp * 3.0f;
    } else {
        if (D_800D154C->xz_velocity < D_800D1893) {
            D_800D154C->xz_velocity = D_800D1893;
        }
    }
}

void func_150770E4(void) {
    if (D_800CC2D0[D_800D154C->unk222].xz_velocity < (f32)(u32)D_800D1892) {
        func_15075400(D_800D1893);
    }
}

void func_15077174(void) {
    D_800D154C->unk10E = D_800D1890;
}

void func_15077190(void) {
    s32 tmp0 = (D_800D1890 << 8) | D_800D1891;
    if (tmp0 != 0) {
        s32 tmp1 = D_800D1892 << 7;
        func_10010630(tmp0, D_800D154C, tmp1, 0x1F4, 0x9C4);
    }
}

void func_150771F0(void) {
    u8 var_a1;
    u8 a2, a3;

    if (D_800D1893 == 0) {
        a2 = D_800D1890;
        a3 = D_800D1891;
        if (D_800D1892 != 0) {
            var_a1 = 1;
        } else {
            var_a1 = 2;
        }
        func_1506160C(D_800D154C, var_a1, a2, a3, 0);
    } else if (D_800D1892 == 0) {
        func_1502ED50(D_800D154C, D_800D1890);
    } else {
        func_1502ED6C(D_800D154C, D_800D1890);
    }
}

void func_15077294(void) {
    switch (D_800D1891) {
        case 0:
            D_800D154C->health = D_800D1890;
            break;
        case 1:
            D_800D154C->health--;
            break;
    }
}

void func_150772E8(void) {
    func_1503DE70(D_800D154C, D_800D1890, -1);
}

void func_15077318(void) {
    if (D_800D1890 != 0) {
        D_800D154C->unk101 |= 1;
    } else {
        D_800D154C->unk101 &= 0xFFFE;
    }
}

void func_1507735C(void) {

}

void func_15077364(void) {
    if (D_800D1893 != 0) {
        D_800D1890 += func_150ADA20() % (u32) D_800D1893;
    }
    D_800D154C->unk246 = (u8) D_800D1890;
    D_800D154C->unk249 = (u8) 0;
    D_800D154C->unk247 = (u8) D_800D1891;
    D_800D154C->unk248 = (u8) D_800D1892;
}

// ??
#ifdef NON_MATCHING
void func_15077404(void) {
    s16 var_v0;

    if (D_800D1893 != 0) {
        var_v0 = ((D_800D154C->unk246 & 0x1F) << 8) + D_800D154C->unk249 + ((s16) ((D_800D1891 << 8) + D_800D1892) * D_800BE9E4);
        if (var_v0 < 0) {
            var_v0 = 0;
        }
        D_800D154C->unk246 = (var_v0 >> 8) | 0x80;
        D_800D154C->unk249 = (u8) var_v0;
        return;
    }
    D_800D154C->unk246 = D_800D1890;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077404.s")
#endif
void func_150774B4(void) {
    if ((D_800D154C->unk20F == D_800D154C->unk211) || (D_800D154C->unk211 == 0xFF)) {
        D_800D154C->unk25C |= 0x800;
        func_15075400(D_800D1890);
    }
}

#ifdef NON_MATCHING
s32 func_15086508(f32, f32, f32, s8, s8, u8 *, u8 *); /* P98: from the asm (f12, f14, a2 = z bits, a3, 3 stack words) */
s32 func_150867D4(u8, s8, s8, u8 *, u8 *);
s32 func_1508712C(s32, f32 *, f32 *, f32 *);
extern s32 D_800D277C;

void func_15077508(void) {
    struct {
        f32 u78;
        f32 u7C;
        f32 u80;
        s32 u84;
    } sp;
    s8 sp76;
    s32 sp70;
    s32 sp6C;
    f32 sp58;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    struct_eu_800D2778 *sp3C;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 var_f2;
    f32 var_f2_2;
    s32 var_a0;
    s32 var_a1_2;
    s32 var_v0;
    s32 var_v1_2;
    s8 var_a1;
    struct127 *temp_v0_2;
    struct_eu_800D2778 *var_v1;
    u8 temp_t2;
    u8 temp_v0;
    u8 temp_v1;
    u8 temp_v1_2;

    sp.u84 = 0xFF;
    if (D_800D1890 != 1) {
        temp_v1 = D_800D154C->unk211;
        if (temp_v1 == D_800D154C->unk20F) {
            (*(s16 *)((u8 *)D_800D154C + 0x216)) = 0;
            D_800D154C->unk25C |= 0x800;
            return;
        }
        if (temp_v1 == 0xFF) {
            (*(s16 *)((u8 *)D_800D154C + 0x216)) = 0;
        }
        goto block_5;
    }
block_5:
    D_800D154C->unk25C &= ~0x800;
    if ((D_800D2528[D_800D154C->unk13F] - 1) > 0) {
        sp76 = 0;
        var_a1 = 0;
        if (D_800D154C->unk211 != 0xFF) {
            var_a1 = 1;
        }
        if (D_800D154C->pad212 != 0xFF) {
            sp76 = 1;
        }
        temp_v1_2 = D_800D154C->unk20F;
        if (temp_v1_2 == 0xFF) {
            if (D_800D1890 == 1) {
                sp76 = 0;
                var_a1 = 0;
                sp.u84 = (s32) D_800D154C->unk210;
            }
            if (sp.u84 == 0xFF) {
                var_v0 = func_15086508(D_800D154C->x_position, D_800D154C->y_position, D_800D154C->z_position, var_a1, sp76, &D_800D154C->unk211, &D_800D154C->pad212);
                goto block_28;
            }
        } else if (temp_v1_2 != 0xFF) {
            if (D_800D1890 == 1) {
                var_a1_2 = 0xFF;
                if (D_800D154C->unk210 != 0xFF) {

                }
                var_f2 = 10.0f;
                var_a0 = 0;
                var_v1 = &D_800D2778[temp_v1_2];
                do {
                    temp_v0 = var_v1->pad8[1];
                    if ((temp_v0 != 0xFF) && (D_800D154C->unk210 != temp_v0)) {
                        sp3C = var_v1;
                        sp70 = var_a0;
                        sp6C = var_a1_2;
                        sp58 = var_f2;
                        temp_f0 = func_150ADA68();
                        if (temp_f0 < var_f2) {
                            var_f2 = temp_f0;
                            var_a1_2 = (s32) var_v1->pad8[1];
                        }
                    }
                    var_a0 += 1;
                    var_v1 = (struct_eu_800D2778 *)((u8 *)var_v1 + (1));
                } while (var_a0 != 5);
                var_v1_2 = var_a1_2;
                if (var_a1_2 == 0xFF) {
                    D_800D154C->unk25C |= 0x800;
                    var_v1_2 = (s32) D_800D154C->unk210;
                }
                sp.u84 = var_v1_2;
            } else {
                var_v0 = func_150867D4(temp_v1_2, var_a1, sp76, &D_800D154C->unk211, &D_800D154C->pad212);
block_28:
                sp.u84 = var_v0;
            }
        }
        if (sp.u84 != 0xFF) {
            D_800D154C->unk21E = 0;
            if (func_1508712C(sp.u84, &sp.u80, &sp.u7C, &sp.u78) != 0) {
                (*(s16 *)((u8 *)D_800D154C + 0x216)) = (s16) D_800D277C;
                D_800D154C->unk210 = D_800D154C->unk20F;
                D_800D154C->unk20F = (u8) sp.u84;
                temp_t2 = D_800D2778[sp.u84].pad8[0];
                var_f2_2 = (f32) temp_t2;
                if ((s32) temp_t2 < 0) {
                    var_f2_2 += 4294967296.0f;
                }
                temp_v0_2 = D_800D154C;
                temp_f14 = sp.u80 - temp_v0_2->x_position;
                temp_f16 = sp.u78 - temp_v0_2->z_position;
                temp_f18 = 2.0f * var_f2_2;
                temp_f12 = sqrtf((temp_f14 * temp_f14) + (temp_f16 * temp_f16));
                if (temp_f12 > 1.0f) {
                    sp40 = temp_f12;
                    sp48 = temp_f14;
                    sp44 = temp_f16;
                    sp4C = temp_f18;
                    temp_f12_2 = (func_150ADA68() * temp_f18) / temp_f12;
                    sp.u80 -= temp_f16 * temp_f12_2;
                    sp.u78 += temp_f14 * temp_f12_2;
                }
                (*(s16 *)((u8 *)(D_800D2104[temp_v0_2->unk13F]) + 8)) = (s16) (s32) sp.u80;
                (*(s16 *)((u8 *)(D_800D2104[D_800D154C->unk13F]) + 0xA)) = (s16) (s32) sp.u7C;
                (*(s16 *)((u8 *)(D_800D2104[D_800D154C->unk13F]) + 0xC)) = (s16) (s32) sp.u78;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077508.s")
#endif
void func_150778F0(void) {
    u8 var_v0 = D_800D2528[D_800D154C->unk13F] - 1;

    if (D_800D154C->unk21F != 0) {
        var_v0 = D_800D154C->unk21F;
    }
    D_800D154C->unk21E += D_800D154C->unk221;
    D_800D154C->unk21E += var_v0;
    D_800D154C->unk21E %= var_v0;
    if (D_800D154C->unk21E < D_800D154C->unk220) {
        D_800D154C->unk21E = D_800D154C->unk220;
    }
}

void func_150779A8(void) {
    func_15075650();
    D_800D154C->unk223 = 0xB;
}

void func_150779D4(void) {
    u8 var_v0 = 0;
    struct127 *temp_a1;
    f32 dist;
    f32 range;

    if (D_800D1892 != 0) {
        var_v0 = D_800D154C->unk222;
    }
    if (D_800C3E78 != var_v0) {
        temp_a1 = &D_800CC2D0[var_v0];
        if ((temp_a1->interaction_state != 1) || (temp_a1->unk65 == 0)) {
            dist = func_1505A6F8(D_800D154C, temp_a1);
            range = D_800D1893 * 8;
            if (dist < range) {
                func_15075400(D_800D1890);
            }
        }
    }
}

void func_15077AA0(void) {
    D_800D154C->unk239 = D_800D1890;
}

void func_15077ABC(void) {
    D_800D154C->unk258 = D_800D1890;
    D_800D154C->unk257 = D_800D1891;
    D_800D154C->unk86 = func_150ADA20() % 0xFFU;
}

void func_15077B14(void) {
    D_800D154C->unk24C = D_800D1890;
    D_800D154C->unk24D = D_800D1891;
}

void func_15077B44(void) {
    func_15060A30((D_800D1890 << 8) + D_800D1891, D_800D154C);
}

void func_15077B80(void) {
    s32 tmp = (D_800D1890 << 8) + D_800D1891;
    D_800D154C->unk25C |= tmp;
}

void func_15077BB4(void) {
    struct127 *tmp = func_1505F0AC(D_800D1891);
    tmp->unk218 = 0;
    tmp->unk232 = D_800D1890;
}

void func_15077BE4(void) {
    s32 tmp = ~((D_800D1890 << 8) + D_800D1891);
    D_800D154C->unk25C &= tmp;
}

void func_15077C1C(void) {
    D_800D154C->unk23D = D_800D1890;
}

void func_15077C38(void) {
    struct127 *phi_s0;
    f32 tmp0;
    f32 distance;
    s32 i;

    tmp0 = D_8009A148;
    D_800D154C->unk222 = (u8)0;

    for (i = 0; i < 25; i++) {
        phi_s0 = &D_800CC2D0[i];
        if (((phi_s0->interaction_state != 0) && (phi_s0->health != 0)) &&
            ((phi_s0->immune == 0) || (phi_s0->immune == 0xFF)) &&
            ((phi_s0->unk65 == 0) || (D_800D1892 != 0)) &&
            ((phi_s0->id == D_800D1890) || ((phi_s0->interaction_state == D_800D1891) &&
            (phi_s0->stunned == 0)))) {
            if (D_800D1893 == 0) {
                D_800D154C->unk222 = i;
                return;
            }
            distance = func_1505A72C(D_800D154C, phi_s0);
            if (tmp0 > distance) {
                D_800D154C->unk222 = i;
                tmp0 = distance;
            }
        }
    }
}

void func_15077DA0(void) {
    D_800D154C->unk21E = D_800D1890;
}

void func_15077DBC(void) {
    if (D_800D1890 != 0xFA) {
        D_800D154C->unk21E = D_800D1890;
    }
    D_800D154C->x_position = ((s16 (*)[4])D_800D2104[D_800D154C->unk13F])[D_800D154C->unk21E][4];
    D_800D154C->y_position = ((s16 (*)[4])D_800D2104[D_800D154C->unk13F])[D_800D154C->unk21E][5];
    D_800D154C->z_position = ((s16 (*)[4])D_800D2104[D_800D154C->unk13F])[D_800D154C->unk21E][6];
}

void func_15077E9C(void) {
    s32 tmp = ((D_800D1890 << 8) + D_800D1891);
    func_10012718(tmp, D_800D154C, 0x5DC0, 0x1F4, 0x9C4);
}

void func_15077EEC(void) {
    D_800D154C->unk254 = D_800D1890;
}

void func_15077F08(void) {
    D_800D154C->unk1EA = (D_800D1890 << 8) | D_800D1891;
}

void func_15077F34(void) {
    D_800D154C->unk24F = D_800D1890;
    D_800D154C->unk250 = D_800D1891;
}

#ifdef NON_MATCHING
void func_15077F64(void) {
    u8 sp1E;
    s32 temp_t3;
    s32 var_a0;
    s32 var_a1;
    u8 temp_t6;
    u8 *temp_v0;

    temp_t6 = D_800D1890 - 1;
    temp_v0 = D_800D2104[D_800D154C->unk13F] + (D_800D154C->unk21E * 8);
    sp1E = temp_t6;
    D_800D154C->unk78 = func_1505A630((f32) (*(s16 *)((u8 *)temp_v0 + 8)) - D_800D154C->x_position, D_800D154C->z_position - (f32) (*(s16 *)((u8 *)temp_v0 + 0xC)), 0);
    temp_t3 = ((s32) (D_800D154C->unk78 - D_800D154C->unk76) >> 8) & 0xFF;
    var_a1 = temp_t3;
    var_a0 = temp_t3;
    if (temp_t3 & 0x80) {
        var_a0 = -temp_t3 & 0xFF;
        var_a1 = var_a0;
    }
    if ((s32) *D_80099DFC[temp_t6] < var_a0) {
        D_800D154C->unk250 = D_800D1891;
        func_15056A00(D_800D154C, var_a1, temp_t6 & 0xFF);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077F64.s")
#endif
// NON-MATCHING: what is D_800D2104 ???
// void func_15056A00(s32, s32, u8);
// void func_15077F64(void) {
//     u8 temp_t6;
//     struct169 *temp_v0;
//     s32 phi_a0;
//     s32 phi_a1;
//
//     temp_t6 = D_800D1890 - 1;
//     temp_v0 = D_800D2104[D_800D154C->unk13F] + (D_800D154C->unk21E);
//     D_800D154C->unk78 = func_1505A630(temp_v0->unk8 - D_800D154C->x_position, D_800D154C->z_position - temp_v0->unkC, 0);
//     phi_a0 = phi_a1 = ((s32) (D_800D154C->unk78 - D_800D154C->unk76) >> 8) & 0xff;
//     if ((phi_a0 & 0x80) != 0) {
//         phi_a1 = phi_a0 = -phi_a0 & 0xFF;
//     }
//     if ((u8)D_80099A3C[temp_t6 * 0xA] < phi_a0) {
//         D_800D154C->unk250 = (u8) D_800D1891;
//         func_15056A00(D_800D154C, phi_a1, temp_t6);
//     }
// }

void func_15078074(void) {
    f32 temp_f20;
    struct127 *tmp;
    s32 i;

    temp_f20 = 8 * D_800D1893;

    for (i = 0; i < 25; i++) {
        tmp = &D_800CC2D0[i];
        if ((tmp->interaction_state != 0) && (D_800C3E78 != i)) {
            if (func_1505A6F8(D_800D154C, tmp) < temp_f20) {
                func_15075400(D_800D1890);
                return;
            }
        }
    }
}

void func_1507813C(void) {
    s32 idx = D_800D154C->unk222;
    if (D_800CC2D0[idx].interaction_state == 0) {
        func_15075400(D_800D1890);
    }
}

void func_150781A4(void) {
    D_800D154C->unk23F = D_800D1891;
    D_800D154C->unk240 = D_800D1892;
    D_800D154C->unk241 = D_800D1890;
    D_800D154C->unk242 = D_800D1893;
}

// another function with D_800D2104
void func_150781F4(void) {
    f32 dx;
    f32 dz;
    f32 dist;
    s16 *temp_v1;
    s32 idx = D_800D1891 + 1;

    temp_v1 = ((s16 (*)[4])D_800D2104[D_800D154C->unk13F])[idx];
    dx = temp_v1[0] - D_800D154C->x_position;
    dz = temp_v1[2] - D_800D154C->z_position;
    dist = sqrtf((dx * dx) + (dz * dz));
    dx = D_800D1893 * 8;
    if (((D_800D1892 == 0) && (dist < dx)) || ((D_800D1892 != 0) && (dx < dist))) {
        func_15075400(D_800D1890);
    }
}

void func_150782CC(void) {
    D_800D154C->unk23E = D_800D1890;
}

void func_150782E8(void) {
    if (((D_800D1892 == 0) && (D_800D154C->unique_id == D_800D1891)) ||
        ((D_800D1892 == 1) && (D_800D154C->unique_id != D_800D1891))) {
        func_15075400(D_800D1890);
    }
}

void func_15078358(void) {
    s32 tmp = func_15083FB0(D_800D1890);
    D_800D154C->unk222 = tmp;
    if (tmp == -1) {
        D_800D154C->unk222 = 0;
    }
}

void func_1507839C(void) {
    f32 var_f0;
    f32 var_f2;

    if (D_800D1892 == 0) {
        var_f0 = func_1505A6F8(D_800D154C, &D_800CC2D0[D_800D154C->unk222]);
    } else if (D_800D1892 == 1) {
        var_f0 = func_1505A72C(D_800D154C, &D_800CC2D0[D_800D154C->unk222]);
    } else {
        var_f0 = fabsf(D_800D154C->y_position - *(f32 *)((u8 *)D_800CC2E8 + D_800D154C->unk222 * 0x32C));
    }
    var_f2 = (f32) (D_800D1893 * 8);
    if (D_800D1893 == 0xFF) {
        var_f2 = (f32) (D_800D154C->unk23D * 8);
    }
    if (((D_800D1891 == 0) && (var_f0 < var_f2)) || ((D_800D1891 == 1) && (var_f2 < var_f0))) {
        func_15075400((s32) D_800D1890);
    }
}
// NON-MATCHING: JUSTREG
// void func_1507839C(void) {
//     struct127 *tmp;
//     f32 phi_f0;
//     f32 phi_f2;
//
//     if (D_800D1892 == 0) {
//         tmp = &D_800CC2D0[D_800D154C->unk222];
//         phi_f0 = func_1505A6F8(D_800D154C, tmp);
//     } else if (D_800D1892 == 1) {
//         tmp = &D_800CC2D0[D_800D154C->unk222];
//         phi_f0 = func_1505A72C(D_800D154C, tmp);
//     } else {
//         phi_f0 = fabsf(D_800D154C->y_position - D_800CC2D0[D_800D154C->unk222].y_position);
//     }
//
//     phi_f2 = D_800D1893 * 8;
//     if (D_800D1893 == 0xFF) {
//         phi_f2 = D_800D154C->unk23D * 8;
//     }
//     if (((D_800D1891 == 0) && (phi_f0 > phi_f2)) ||
//         ((D_800D1891 == 1) && (phi_f0 > phi_f2))) {
//         func_15075400(D_800D1890);
//     }
// }

void func_15078520(void) {
    func_15075400(D_800D1890);
}

#ifdef NON_MATCHING
f32 func_150489B0(u8);

// path_point_from_object: P210: script command: sets point D_800D1890 & 0x3F of the current object's path
// (D_800D2104[unk13F], s16 x / y / z after an 8-byte header) to an offset from object unk222 (D_800CC2D0). The
// offset is x = 8 * (s8 D_800D1891 << 4 | D_800D1893 >> 4), z = 8 * (s8 D_800D1892 << 4 | D_800D1893 & 0xF),
// rotated by the object's heading (D_800D1890 bits 6-7 = 0), not rotated (1), or by the direction from the
// object to the current one (2, 3); y is the object's height. D_800D1890 keeps the masked point number.
void func_15078544(void) {
    u8 cmd = D_800D1890;
    struct127 *o;
    s32 mode;
    f32 ox, oz;
    f32 x, y, z;
    f32 s, c;
    s16 *pt;

    D_800D1890 = cmd & 0x3F;
    o = &D_800CC2D0[D_800D154C->unk222];
    ox = (((s8)D_800D1891 << 4) | (D_800D1893 >> 4)) << 3;
    oz = (((s8)D_800D1892 << 4) | (D_800D1893 & 0xF)) << 3;
    mode = cmd >> 6;
    y = o->y_position;
    x = o->x_position;
    z = o->z_position;
    if (mode == 0) {
        u8 a = (o->unk7A >> 8) - 0x40;

        s = func_15048A40(a);
        c = func_150489B0(a);
    } else if (mode == 1) {
        s = 0.0f;
        c = 1.0f;
    } else {
        f32 ang = func_150484A0(D_800D154C->x_position - x, D_800D154C->z_position - z);

        s = sinf(ang);
        c = cosf(ang);
    }
    x += ox * c + oz * s;
    z += oz * c - ox * s;
    pt = (s16 *)(D_800D2104[D_800D154C->unk13F] + D_800D1890 * 8 + 8);
    pt[0] = x;
    pt = (s16 *)(D_800D2104[D_800D154C->unk13F] + D_800D1890 * 8 + 8);
    pt[1] = y;
    pt = (s16 *)(D_800D2104[D_800D154C->unk13F] + D_800D1890 * 8 + 8);
    pt[2] = z;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15078544.s")
#endif
void func_1507879C(void) {
    struct197 *temp_v0 = D_800CC2D0[D_800D154C->unk222].unk2D0;
    f32 temp_f0 = temp_v0->unk8;

    if (((D_800D1892 == 0) && (temp_f0 < (u32)D_800D1891)) || ((D_800D1892 == 1) && ((u32)D_800D1891 < temp_f0))) {
        func_15075400(D_800D1890);
    }
}

void func_15078874(void) {
    D_800D154C->unk251 = D_800D1890;
}

void func_15078890(void) {
    if (((D_800D1892 == 0) && (D_800D154C->unk251 == D_800D1891)) ||
        ((D_800D1892 == 1) && (D_800D154C->unk251 != D_800D1891))) {
        func_15075400(D_800D1890);
    }
}

void func_15078900(void) {
    if (D_800D1893 != 0) {
        if (D_800D154C->unk222 == 0) {
            func_15075400(D_800D1890);
        }
    } else {
        if (((D_800D1892 == 0) && (D_800D1891 == D_800CC521[D_800D154C->unk222 * 0x32C])) ||
            ((D_800D1892 == 1) && (D_800D1891 != D_800CC521[D_800D154C->unk222 * 0x32C]))) {
            func_15075400(D_800D1890);
        }
    }
}

void func_15078A08(void) {
    struct197 *temp_a0;
    struct197 *temp_v0;

    temp_v0 = D_800D154C->unk2D0;
    temp_a0 = D_800CC5A0[D_800D154C->unk222].interaction_state; // wtf
    temp_v0->unk8 = (f32) temp_a0->unk8;
    temp_v0->unkC = (f32) temp_a0->unkC;
}

// requires jump table
#ifdef NON_MATCHING
/* P183 */
f32 func_150484A0(f32, f32);
extern u8 D_800CC9D4[];
extern u8 D_800CC9D8[];
extern u8 D_800CC9DC[];
extern u8 D_800CC734[];
extern u8 D_800CC82C[];
extern u8 D_800CC718[];
extern u8 D_800CC7F2;
extern u8 D_800BEE0C;
extern u8 D_800CC8BA[];
extern u8 D_800CC922[];
extern u8 D_800CC779[];

// script_test_object_value: P183: script condition: reads value D_800D1892 (0..18) of object `idx` (0x32C-byte
// records of D_800CC2D0; some values come from the global object D_800CCA0C or the player's +0x222 object) and
// compares it with D_800D1893 by operator D_800D1891 (0 ==, 1 !=, 2 <, 3 >, 4 <=, 5 >=). Value 6 is the angle
// difference 0..128 (256 per turn) between the object's heading (+0x7A >> 8, - 0x40) and its direction to the
// player D_800D154C; value 9 is 2 when the object's +0xCA0C record has +0x8 and +0x16 set. Returns 1 when true.
// For a value kind above 18 the asm compares an unset stack slot (kept: `v` uninitialised there).
s32 func_15078A60(s32 idx) {
    s32 v;
    s32 off = idx * 0x32C;
    u8 *obj;
    u8 *rec;
    u8 heading;
    u8 diff;

    switch (D_800D1892) {
        case 0:
            v = *(f32 *) ((u8 *) D_800CC30C + off);
            break;
        case 1:
            v = *(s32 *) (D_800CC9D4 + off);
            break;
        case 2:
            v = *(s32 *) (D_800CC9D8 + off);
            break;
        case 3:
            v = *(s32 *) (D_800CC9DC + off);
            break;
        case 4:
            v = *(f32 *) ((u8 *) D_800CC2E8 + off);
            break;
        case 5:
            v = *(f32 *) (D_800CC734 + off);
            break;
        case 6:
            obj = (u8 *) D_800CC2D0 + off;
            heading = (*(u16 *) (obj + 0x7A) >> 8) - 0x40;
            diff = (u32) (func_150484A0(*(f32 *) (obj + 0x14) - *(f32 *) ((u8 *) D_800D154C + 0x14),
                                        *(f32 *) (obj + 0x1C) - *(f32 *) ((u8 *) D_800D154C + 0x1C)) *
                          40.743664f) -
                   heading;
            v = diff;
            if (diff > 0x80) {
                v = 0x100 - diff;
            }
            break;
        case 7:
            v = D_800CC82C[off];
            break;
        case 8:
            v = D_800CC3D4[off];
            break;
        case 9:
            rec = *(u8 **) ((u8 *) &D_800CCA0C + off);
            v = 0;
            if (*(s16 *) (rec + 0x8) != 0 && rec[0x16] != 0) {
                v = 2;
            }
            break;
        case 10:
            v = *(f32 *) (D_800CC718 + off);
            break;
        case 11:
            v = D_800CCA0C[0x78];
            break;
        case 12:
            v = D_800CCA0C[0x7D];
            break;
        case 13:
            v = D_800CC7F2;
            break;
        case 14:
            v = D_800BEE0C;
            break;
        case 15:
            v = D_800CC2D4[((u8 *) D_800D154C)[0x222] * 0x32C];
            break;
        case 16:
            v = D_800CC8BA[off];
            break;
        case 17:
            v = D_800CC922[((u8 *) D_800D154C)[0x222] * 0x32C];
            break;
        case 18:
            v = D_800CC779[off];
            break;
    }
    if ((D_800D1891 == 0 && v == D_800D1893) || (D_800D1891 == 1 && v != D_800D1893) ||
        (D_800D1891 == 2 && v < D_800D1893) || (D_800D1891 == 3 && D_800D1893 < v) ||
        (D_800D1891 == 4 && !(D_800D1893 < v)) || (D_800D1891 == 5 && !(v < D_800D1893))) {
        return 1;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15078A60.s")
#endif

void func_1507900C(void) {
    if (func_15078A60(0) != 0) {
        func_15075400(D_800D1890);
    }
}

void func_1507903C(void) {
    if (func_15078A60(0) != 0) {
        D_800D154C->unk218 = func_1507BB28(0, D_800D1890);
        D_800D154C->unk218 -= 1;
    }
}

void func_15079090(void) {
    if (func_15078A60(D_800C3E78) != 0) {
        func_15075400(D_800D1890);
    }
}

void func_150790C4(void) {
    if (func_15078A60(D_800C3E78) != 0) {
        D_800D154C->unk218 = func_1507BB28(0, D_800D1890);
        D_800D154C->unk218 -= 1;
    }
}

u8 func_1507911C(void) {
    s16 temp_a2;
    s16 phi_a0;
    u8 idx;

    temp_a2 = (D_800D1891 << 8) | D_800D1892;
    idx =  D_800D1893 & 1;
    if (idx != 0) {
        idx = D_800C3E78;
    }
    phi_a0 = D_800CC2D0[idx].y_position;
    if ((D_800D1893 & 2) != 0) {
        phi_a0 = D_800CC2D0[idx].x_position;
    }
    if (phi_a0 < temp_a2) {
        func_15075400(D_800D1890);
    }
}

void func_150791F0(void) {
    if ((s32) D_800D154C->unk2C9 < (s32) D_800D1890) {
        D_800D154C->unk1C9 = (u8)0xFFU;
    } else {
        D_800D154C->unk1C9 = D_800D1890;
    }
}

// ???
void func_15079228(void) {
    s16 *temp_v0 = ((s16 (*)[26])D_800D34B8)[D_800D154C->unk251];
    f32 px = temp_v0[0];
    f32 pz = temp_v0[2];
    s32 temp_v0_2 = func_1505A630(D_800D154C->x_position - px, pz - D_800D154C->z_position, 0);
    s32 var_a2 = temp_v0_2 & 0xFFFF;

    if (temp_v0_2 == 0) {
        var_a2 = 1;
    }
    func_1505D024(D_800D154C, D_800D1890, var_a2, -1);
    D_800D154C->unk218--;
    D_800D154C->unk21C = 1;
}

void func_150792E0(void) {
    D_800D154C->unk232 = D_800D1890;
}

void func_150792FC(void) {
    D_800D154C->unk2F8 &= 0xFFF8;
    D_800D154C->unk2F8 |= D_800D1890;
}

void func_15079334(void) {
    struct127 *tmp;

    if (D_800D154C->unkA8 != 0) {
        tmp = &D_800CC2D0[D_800D154C->unkA8 & 0x7F];
        tmp->unk218 = 0;
        tmp->unk232 = D_800D1890;
    }
}

void func_15079390(void) {
    u16 tmp0 = D_800D1890;
    u8 tmp1 = D_800D1891;
    u8 tmp2 = D_800D1892;
    func_1514D3B0(D_800D154C, tmp0, tmp1, tmp2);
}

#ifdef NON_MATCHING
void func_150793D8(void) {
    struct {
        f32 u2C;
        f32 u30;
        f32 u34;
    } sp;
    s16 sp24;
    s16 sp22;
    s16 var_t0;
    s16 var_t0_2;
    s16 var_v1;
    s16 var_v1_2;
    s32 temp_f10;
    s32 temp_f6;

    temp_f6 = (s32) D_800CC2D0->x_position;
    temp_f10 = (s32) D_800CC2D0->z_position;
    var_v1 = (s16) temp_f6;
    var_t0 = (s16) temp_f10;
    if (((s16) temp_f6 < -0x49C) || ((s16) temp_f6 >= 0x49D) || ((s16) temp_f10 < -0x49C) || ((s16) temp_f10 >= 0x49D)) {
        var_v1 = 0;
        var_t0 = 0;
    }
    sp24 = var_v1;
    sp22 = var_t0;
    func_1505A184(func_150ADA20() & 0xFFFF, 550.0f, 0.0f, &sp.u34, &sp.u30, &sp.u2C);
    var_v1_2 = (s16) (s32) ((f32) sp24 + sp.u34);
    var_t0_2 = (s16) (s32) ((f32) sp22 + sp.u30);
    if (var_v1_2 < -0x4B0) {
        var_v1_2 = -0x4B0;
    }
    if (var_v1_2 >= 0x4B1) {
        var_v1_2 = 0x4B0;
    }
    if (var_t0_2 < -0x4B0) {
        var_t0_2 = -0x4B0;
    }
    if (var_t0_2 >= 0x4B1) {
        var_t0_2 = 0x4B0;
    }
    (*(s16 *)((u8 *)((D_800D2104[D_800D154C->unk13F] + (D_800D1890 * 8))) + 8)) = var_v1_2;
    (*(s16 *)((u8 *)((D_800D2104[D_800D154C->unk13F] + (D_800D1890 * 8))) + 0xC)) = var_t0_2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150793D8.s")
#endif
void func_15079570(void) {
    f32 dist;
    f32 time;

    dist = func_1505A6F8(D_800D154C, &D_800CC2D0[D_800D154C->unk222]);
    D_800D154C->unk44 = D_800D154C->xz_velocity;
    time = 2.0f * (dist / D_800D154C->unk44);
    D_800D154C->y_velocity = D_800D154C->gravity * time * 0.5f;
    D_800D154C->y_velocity += 2.0f * ((D_800CC2D0[D_800D154C->unk222].y_position - D_800D154C->y_position) / time);
}

void func_1507965C(void) {
    s32 idx;
    struct127 *temp_v1;

    idx = func_15083FB0(D_800D1890);
    if (idx != -1) {
        temp_v1 = &D_800CC2D0[idx];
        temp_v1->unk232 = D_800D1891;
        temp_v1->unk218 = 0;
        temp_v1->unk23A = 0;
    }
}

void func_150796CC(void) {
    s32 idx = func_15083FB0(D_800D1890);
    if (D_800D1892 != 0) {
        if (idx != -1) {
            D_800CC3F5[idx * sizeof(struct127)] = D_800D1891;
        }
    } else if ((idx != -1) && (D_800CC3D4[idx * sizeof(struct127)] != 0)) {
        func_15075400(D_800D1891);
    }
}

void func_15079790(void) {
    s16 sp1E;
    s16 temp_t0;

    if (D_800D1892 != 0) {
        D_800D154C->id = 0xFF;
    } else {
        D_800D154C->id = 0x3A;
        sp1E = (func_150ADA20() % 500U) - 250;
        temp_t0 = (func_150ADA20() % 500U) - 250;
        D_800D154C->x_position = ((s16 *)D_800D2104[D_800D154C->unk13F])[0] + sp1E;
        D_800D154C->z_position = ((s16 *)D_800D2104[D_800D154C->unk13F])[2] + temp_t0;
    }
}

void func_15079880(void) {
    s32 tmp = D_800CC30C[0] + (s8)D_800D1892;

    if (tmp < D_800D1891) {
        tmp = D_800D1891;
    } else if (tmp >= 251) {
        tmp = 250;
    }
    D_800D1892 = tmp;
    func_15075548();
}

void func_150798F8(void) {
    D_800D1891 = D_800D154C->unk21E;
    func_150781F4();
}

void func_15079928(void) {
    s32 phi_a3;

    phi_a3 = ((D_800D1891 << 0x10) + D_800D1892) & 0xFFFF;
    if (phi_a3 == 0) {
        phi_a3 = 0xFFFF;
    }
    func_1507E7E4(D_800D154C, D_800D1890, D_800D1893, phi_a3, 0);
}

void func_15079988(void) {
    func_1507EB4C(D_800D154C, D_800D1890);
}

void func_150799B4(void) {
    s32 temp_a0 = (D_800D1890 << 8) + D_800D1891;
    if (D_800D1892 != 0) {
        temp_a0 += func_150ADA20() % (u32) D_800D1892;
    }
    func_15060A30(temp_a0, D_800D154C);
}

void func_15079A28(void) {
    D_800D154C->unk252 = D_800D1890;
    D_800D154C->unk253 = D_800D1891;
}

void func_15079A58(void) {
    D_800D2530[D_800D154C->unk13F] = (D_800D1890 << 8) + D_800D1891;
}

// path_point_angle: angle (u16, func_1505A630) from object arg0 (D_800CC2D0) to the current path point of the
// active character (D_800D2104[D_800D154C +0x13F]: x at +0, z at +4). P179: was `void` and dropped the return; its
// asm caller func_15079B30 stores / subtracts the two results (`sh v0` / `subu` after the jal).
u16 func_15079A98(s32 arg0) {
    s16 *temp_v0 = (s16 *)D_800D2104[D_800D154C->unk13F];
    struct127 *temp_v1 = &D_800CC2D0[arg0];

    return func_1505A630(temp_v0[0] - temp_v1->x_position, temp_v1->z_position - temp_v0[2], 0);
}

// requires jump table
#ifdef NON_MATCHING
/* func_15083FB0 (s32 (u8), game_eu_AF2A0) is used undeclared in this file, like its other callers here */
int func_1507BB28(s32, s32);
u16 func_15079A98(s32 arg0);

// object_var_cmd: P210: script command on object `idx` (D_800D1891 0 / 1: the current one D_800C3E78, else
// func_15083FB0(D_800D1891 - 2); -1 = none). D_800D1892 selects: 1..3 counter unk2E4 / unk2E8 / unk2EC, updated by
// D_800D1893 (0 = D_800D1890, 1 -1, 2 + frame time D_800BE9E4, 3 +1, 4 - frame time, 5 - D_800CC264,
// 6 + D_800CC264); 4 / 5 start script D_800D1890 on the object (when it is not running it already); 6 unkC8 =
// D_800D1890; 7 unkB8 = 0; for the current object: 8 unk221 = D_800D1890 when the path point angle
// (func_15079A98) from object D_800C3E78 minus the one from object unk222 has bit 15 set, 9 unk244 = D_800D1893 << 8 | D_800D1890, 10 unk236 = unk23D + (s8)D_800D1890, 11 unk22A = D_800D1890.
// Other D_800D1892 values: the asm then updates a counter through an unset stack pointer; here nothing happens.
void func_15079B30(void) {
    s32 idx;
    s32 *var;
    struct127 *saved;
    u8 savedNum;
    u16 a;

    if (D_800D1891 == 0 || D_800D1891 == 1) {
        idx = D_800C3E78;
    } else {
        idx = func_15083FB0(D_800D1891 - 2);
        if (idx == -1) {
            return;
        }
    }
    switch (D_800D1892) {
        case 1:
            var = &D_800CC2D0[idx].unk2E4;
            break;
        case 2:
            var = &D_800CC2D0[idx].unk2E8;
            break;
        case 3:
            var = &D_800CC2D0[idx].unk2EC;
            break;
        case 4:
        case 5:
            saved = D_800D154C;
            savedNum = D_800C3E78;
            D_800D154C = &D_800CC2D0[idx];
            D_800C3E78 = idx;
            if (D_800D1890 != D_800D154C->unk232) {
                D_800D154C->unk232 = D_800D1890;
                D_800D154C->unk218 = (struct216 *)func_1507BB28(0, D_800D154C->unk232);
                D_800D154C->unk21C = 0;
            }
            D_800C3E78 = savedNum;
            D_800D154C = saved;
            return;
        case 6:
            D_800CC2D0[idx].unkC8 = D_800D1890;
            return;
        case 7:
            D_800CC2D0[idx].unkB8 = 0.0f;
            return;
        case 8:
            a = func_15079A98(D_800D154C->unk222);
            if ((func_15079A98(D_800C3E78) - a) & 0x8000) {
                D_800D154C->unk221 = D_800D1890;
            }
            return;
        case 9:
            D_800D154C->unk244 = (D_800D1893 << 8) | D_800D1890;
            return;
        case 10:
            D_800D154C->unk236 = D_800D154C->unk23D + (s8)D_800D1890;
            return;
        case 11:
            D_800D154C->unk22A = D_800D1890;
            return;
        default:
            return;
    }
    switch (D_800D1893) {
        case 0:
            *var = D_800D1890;
            break;
        case 1:
            *var -= 1;
            break;
        case 2:
            *var += D_800BE9E4;
            break;
        case 3:
            *var += 1;
            break;
        case 4:
            *var -= D_800BE9E4;
            break;
        case 5:
            *var -= D_800CC264;
            break;
        case 6:
            *var += D_800CC264;
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079B30.s")
#endif

void func_15079F24(void) {
    D_800D154C->unk48 = D_800D1898[D_800D1890];
}

void func_15079F50(void) {
    D_800D154C->unk23B = D_800D1890;
}

void func_15079F6C(void) {
    u8 temp_v0 = D_800D1890; s32 temp_v1 = D_800D1891 & 0xFF;

    D_800D154C->unk224 = (temp_v0 << 8) | temp_v1;
    D_800D154C->unk22B = D_800D1892;
    D_800D154C->unk226 = D_800D1893;
}

#ifdef NON_MATCHING
int func_1507BB28(s32, s32);
extern f32 D_8009A5A4; /* 0.7 */

// follow_player_speed: P210: script command: when player 1 (D_800CC2D0[0]) rides nothing (unk65 0) or is slower
// than 5, jumps the current object's script to D_800D1891 (unk232, script pointer func_1507BB28 - one entry);
// otherwise copies the player's controller heading (unk31C +0x4C) into unk78 and starts func_15075F40 with speed
// parameter D_800D1892 = player speed (times 0.7 unless the player is chased), D_800D1893 + 1 and D_800D1890 = 8
// below 17; sets flag 0x40 in unkF4.
void func_15079FBC(void) {
    struct127 *player = &D_800CC2D0[0];
    s16 speed;

    if (player->unk65 == 0 || player->unk44 < 5.0f) {
        D_800D154C->unk232 = D_800D1891;
        D_800D154C->unk218 = (struct216 *)func_1507BB28(0, D_800D154C->unk232);
        D_800D154C->unk218--;
        return;
    }
    D_800D154C->unk78 = player->unk31C->unk4C;
    if (player->unk31C->chased != 0) {
        speed = player->unk44;
    } else {
        speed = player->unk44 * D_8009A5A4;
    }
    if (speed < 17) {
        D_800D1893++;
        D_800D1890 = 8;
    }
    D_800D1892 = speed;
    func_15075F40();
    D_800D154C->unkF4 |= 0x40;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079FBC.s")
#endif
// NON-MATCHING: JUSTREG
// void func_15079FBC(void) {
//     s16 phi_v1;
//
//     if ((D_800CC2D0->unk65 == 0) || (D_800CC2D0->unk44 < 5.0f)) {
//         D_800D154C->unk232 = D_800D1891;
//         D_800D154C->unk218 = func_1507BB28(0, D_800D154C->unk232, D_800D154C);
//         D_800D154C->unk218 -= 1;
//         return;
//     }
//
//     D_800D154C->unk78 = D_800CC2D0->unk31C->unk4C;
//
//     if (D_800CC2D0->unk31C->unk4A) {
//         phi_v1 = D_800CC2D0->unk44;
//     } else {
//         phi_v1 = D_800CC2D0->unk44 * D_8009A1E4;
//     }
//     if (phi_v1 < 17) {
//         D_800D1893 += 1;
//         D_800D1890 = 8;
//     }
//     D_800D1892 = phi_v1;
//     func_15075F40();
//     D_800D154C->unkF4 |= 0x40;
// }

// D_800D2104!
void func_1507A100(void) {
    s32 temp_v0 = ((s8)D_800D1892 << 8) | D_800D1893;

    ((s16 (*)[4])D_800D2104[D_800D154C->unk13F])[D_800D1890][D_800D1891 + 4] = temp_v0;
}

s32 func_1507A164(void) {
    s32 tmp = D_800CC30C[0] + (s8)D_800D1892;

    if (tmp < D_800D1891) {
        tmp = D_800D1891;
    } else if (tmp > D_800D1890) {
        tmp = D_800D1890;
    }
    D_800D154C->unk44 = tmp;
    if (D_800D154C->unk44 == 1.0f) {
        D_800D154C->unk44 = 0.5f;
    }
}

void func_1507A210(void) {
    D_800D154C->unk223 = 0;
    D_800D154C->unk21C = D_800D1890 * 0x64;
    D_800D154C->unk22C &= 0xFD;
    func_15075498();
}

void func_1507A270(void) {
    func_1503DE70(D_800D154C, D_800D1890, (s8)D_800D1891);
}

void func_1507A2A4(void) {
    D_800D1893 = (func_150ADA20() % (u32) D_800D1891) + D_800D1893;
    func_15075CA0();
}

void func_1507A2F8(void) {
    s32 i;
    u32 used;
    u8 sp1C[25];

    used = 0;
    for (i = 0; i < 25; i++) {
        if ((D_800CC2D0[i].interaction_state != 0) && (D_800CC2D0[i].id == D_800D1890)) {
            sp1C[used] = i;
            used++;
        }
    }
    if (used != 0) {
        i = func_150ADA20();
        D_800D154C->unkA8 = D_800D154C->unk222;
        D_800D154C->unk222 = sp1C[i % used];
    }
}

void func_1507A3B4(void) {
    D_800D154C->unk222 = D_800D154C->unkA8;
}

void func_1507A3CC(void) {
    D_800D154C->unk229 = D_800D1890;
}

//  what is up with these??
s32 func_1507A3E8(void) {
    return ((D_800D1890 & 0xFF) << 24) | ((D_800D1891 & 0xFF) << 16) | ((D_800D1892 & 0xFF) << 8) | (D_800D1893 & 0xFF);
}

void func_1507A428(void) {
    s32 temp_v0 = ((D_800D1890 & 0xFF) << 24) | ((D_800D1891 & 0xFF) << 16) | ((D_800D1892 & 0xFF) << 8) | (D_800D1893 & 0xFF);

    D_800D154C->unk94 = ~(temp_v0 | 1);
}
void func_1507A47C(void) {
    s32 temp_v0 = ((D_800D1890 & 0xFF) << 24) | ((D_800D1891 & 0xFF) << 16) | ((D_800D1892 & 0xFF) << 8) | (D_800D1893 & 0xFF);

    D_800D154C->unk94 &= ~temp_v0;
}
void func_1507A4D4(void) {
    s32 temp_v0 = ((D_800D1890 & 0xFF) << 24) | ((D_800D1891 & 0xFF) << 16) | ((D_800D1892 & 0xFF) << 8) | (D_800D1893 & 0xFF);

    D_800D154C->unk94 |= temp_v0;
}

void func_1507A528(void) {
    s32 count;
    s32 pos;

    if (D_800D1890 == 0) {
        D_800D154C->unk221 = D_800D1891;
    } else if (D_800D1890 == 1) {
        D_800D154C->unk221 = -D_800D154C->unk221;
    } else if (D_800D1890 == 2) {
        if (D_800D1892 != 0) {
            count = D_800D1892;
        } else {
            count = D_800D2528[D_800D154C->unk13F] - 1;
        }
        D_800D154C->unk221 = -D_800D154C->unk221;
        pos = D_800D154C->unk21E + D_800D154C->unk221;
        if (D_800D154C->unk221 > 0) {
            pos += D_800D1893;
        } else {
            pos -= D_800D1893;
        }
        if (pos >= count) {
            pos -= count;
        } else if (pos < 0) {
            pos += count;
        }
        D_800D154C->unk21E = pos;
    }
}

void func_1507A620(void) {
    u8 idx;
    u16 tmp;

    idx = D_800D154C->unk222;
    if (D_800D1891 != 0) {
        tmp = D_800D154C->unk78 >> 8;
    } else {
        tmp = (D_800D154C->unk7A - func_1505A630(D_800CC2D0[idx].x_position - D_800D154C->x_position, D_800D154C->z_position - D_800CC2D0[idx].z_position, 0)) >> 8;
    }
    if ((u8)(tmp - D_800D1892) < (u8)(D_800D1893 - D_800D1892)) {
        func_15075400(D_800D1890);
    }
}

s32 func_1507A6FC(s32 arg0) {
    // really??
    u32 tmp0 = (3 * arg0) & 0xFFFFFFFFFFFFFFFF;
    u32 tmp1 = tmp0 & 0xFFFFFFFFFFFFFFFF;
    return D_800BE748[tmp1 & 0xFFFFFFFFFFFFFFFF];
}

void func_1507A71C(void) {
    u16 tmp0 = func_1507A6FC(D_800D1890);
    u16 tmp1 = ((D_800D1891 << 8) | D_800D1892);

    if ((tmp0 & tmp1) == tmp1) {
        func_15075400(D_800D1893);
    }
}

void func_1507A774(void) {
    u16 temp_v0 = (D_800D1891 << 8) | D_800D1892;
    if (D_800BE9F0 == temp_v0) {
        func_15075400(D_800D1890);
    }
}

void func_1507A7C0(void) {
    D_800D154C->disable_run = (u8) D_800D1890;
}

void func_1507A7DC(void) {
    func_150836CC(D_800D154C, D_800D1890);
}

void func_1507A808(void) {
    D_800D154C->unk22C = (D_800D154C->unk22C & D_800D1890) | D_800D1891;
}

void func_1507A838(void) {
    if (D_800D154C->health == D_800D1891) {
        func_15075400(D_800D1890);
    }
}

void func_1507A878(void) {
    func_1512D748(0, D_800D1890, D_800D1891);
}

void func_1507A8A8(void) {
    if ((D_800CC335 != 0) || (D_800BE616 != 0)) {
        func_15075400(D_800D1890);
    }
}

void func_1507A8EC(void) {
    if (D_800D1891 == D_800CC2D4[D_800D154C->unk222 * sizeof(struct127)]) {
        D_800D1892 ^= 1;
    }
    if (D_800D1892 != 0) {
        func_15075400(D_800D1890);
    }
}

void func_1507A984(void) {
    s32 temp_v0;

    if (D_800D1890 != 0) {
        temp_v0 = func_15083E90(D_800D1890);
        if (temp_v0 != 0) {
            if (D_800D1892 == 0) {
                D_800D154C->unk101 |= 4;
            }
            if (D_800D1893 != 0) {
                D_800D154C->unk101 |= 0x40;
            }
            D_800D154C->unk65 = ((s32) (temp_v0 - (s32)&D_800CC2D0) / 0x32C) + 1;
            D_800D154C->unk5C = D_800D1891;
        }
    } else {
        D_800D154C->unk65 = 0;
    }
}

// requires jump table
#ifdef NON_MATCHING
extern f32 D_8009A5CC; /* 65536 / (2 pi) */
/* IDO's f32 -> u32 conversion (cvt.w.s, then 2^31 offset): -1 for NaN, values <= -1 and >= 2^32 */
#define P210_F2U(v) (((v) > -1.0f && (v) < 4294967296.0f) ? (u32)(v) : 0xFFFFFFFF)

// set_heading_cmd: P210: script command: sets the current object's target heading unk78 (or its heading unk76)
// from the 16-bit value D_800D1890 << 8 | D_800D1891 by mode D_800D1892: 0 heading + value, 1 heading - value,
// 2 value, 3 turn now (unk76 = unk7A = unk78), 4 direction from path point D_800D1890 to point D_800D1891
// (D_800D2104[unk13F]) + D_800D1893 << 8 + 0x4000, 5 random (func_150ADA20), 6 keep the heading, 7 unk76 = object
// unk222's facing + value, 8 unk76 = own facing unk7A.
void func_1507AA48(void) {
    u16 v = (D_800D1890 << 8) | D_800D1891;

    switch (D_800D1892) {
        case 0:
            D_800D154C->unk78 = D_800D154C->unk76 + v;
            break;
        case 1:
            D_800D154C->unk78 = D_800D154C->unk76 - v;
            break;
        case 2:
            D_800D154C->unk78 = v;
            break;
        case 3:
            D_800D154C->unk76 = D_800D154C->unk78;
            D_800D154C->unk7A = D_800D154C->unk78;
            break;
        case 4: {
            u8 *path = (u8 *)D_800D2104[D_800D154C->unk13F];
            s16 *from = (s16 *)(path + D_800D1890 * 8 + 8);
            s16 *to = (s16 *)(path + D_800D1891 * 8 + 8);
            f32 ang = func_150484A0(to[0] - from[0], to[2] - from[2]);

            D_800D154C->unk78 = P210_F2U(ang * D_8009A5CC) + (D_800D1893 << 8) + 0x4000;
            break;
        }
        case 5:
            D_800D154C->unk78 = func_150ADA20();
            break;
        case 6:
            D_800D154C->unk78 = D_800D154C->unk76;
            break;
        case 7:
            D_800D154C->unk76 = D_800CC2D0[D_800D154C->unk222].unk7A + v;
            break;
        case 8:
            D_800D154C->unk76 = D_800D154C->unk7A;
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507AA48.s")
#endif

void func_1507ACB0(void) {
    D_800D154C->unk220 = D_800D1890;
    D_800D154C->unk21F = D_800D1891;
}

void func_1507ACE0(void) {
    D_800D154C->unk1E5 = D_800D1890;
    D_800D154C->unk1E6 = D_800D1890;
    D_800D154C->unk1E7 = D_800D1891;
    D_800D154C->unk1E8 = D_800D1891;
}

void func_1507AD30(void) {
    D_800D154C->unk255 = D_800D1890;
    D_800D154C->unk256 = D_800D1891;
}

void func_1507AD60(void) {
    D_800D154C->unk1E4 = D_800D1890;
}

void func_1507AD7C(void) {
    D_800D154C->unkF4 |= func_1507A3E8();
}

void func_1507ADAC(void) {
    D_800D154C->unkF4 &= ~func_1507A3E8();
}

void func_1507ADE0(void) {
    s32 res;
    s32 temp_lo;
    s32 b = D_800D154C->unk7A;
    s32 a = D_800D154C->unk78;

    res = a - b;
    if (res < 0) {
        res = -res;
    }
    if (res >= 32769) {
        res = res + 0xFFFF0000;
    }
    if (res < 0) {
        res = -res;
    }
    temp_lo = res / (s32)D_800D1890;
    D_800D154C->unk1E6 = temp_lo >> 8;
    D_800D154C->unk1E8 = temp_lo & 0xFF;
}

void func_1507AE78(void) {
    D_800D154C->unk229 = D_800D1890;
}

void func_1507AE94(void) {
    D_800D154C->unkD2 = (D_800D1890 << 8) | D_800D1891;
    D_800D154C->unkD4 = (D_800D1892 << 8) | D_800D1893;
    D_800D154C->unkD2 *= D_800D154C->xz_scale;
    D_800D154C->unkD4 *= D_800D154C->y_scale;
}

void func_1507AF3C(void) {
    D_800D154C->unkD6 = (D_800D1890 << 8) | D_800D1891;
    D_800D154C->unkD6 *= D_800D154C->y_scale;
}

void func_1507AF98(void) {
    D_800D154C->unkD8 = (D_800D1890 << 8) | D_800D1891;
    D_800D154C->unkDA = (D_800D1892 << 8) | D_800D1893;
    D_800D154C->unkD8 *= D_800D154C->xz_scale;
    D_800D154C->unkDA *= D_800D154C->xz_scale;
}

void func_1507B040(void) {
    D_800D154C->unk76 = D_800D154C->unk7A;
}

void func_1507B058(void) {
    struct127 *sp24 = D_800D154C;
    s32 sp20 = D_800C3E78;

    D_800D154C = func_15072208(D_800D154C, 0);
    D_800C3E78 = ((s32)D_800D154C - (s32)&D_800CC2D0) / 0x32C;

    if (D_800D154C != 0) {
        switch (D_800D1890) {
            case 0:
                func_1506160C(D_800D154C, 1, D_800D1891, 0, 0);
                break;
            case 1:
                D_800D154C->unk232 = D_800D1891;
            case 2:
                D_800D154C->unk218 = func_1507BB28(0, D_800D1891);
                D_800D154C->unk21C = 0;
        }
    }
    D_800C3E78 = sp20;
    D_800D154C = sp24;
}

void func_1507B15C(void) {
    D_800D154C->disable_jump = D_800D1890;
}

void func_1507B178(void) {
    s16 tmp  = (D_800D1891 << 8) | D_800D1890;
    if (D_800D1893 == 2) {
        D_800D154C->unkE8 = (s16) (tmp * D_800D154C->y_scale);
    } else if (D_800D1893 == 1) {
        func_15062B50(D_800D154C, tmp);
    } else {
        func_15062B1C(D_800D154C, tmp);
    }
}

void func_1507B234(void) {
    D_800D1580 = func_1507A3E8();
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(300, 1800);
    }
}

void func_1507B280(void) {
    D_800D1580 = func_1507A3E8();
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(300, 3000);
    }
}

void func_1507B2CC(void) {
    D_800D1580 = func_1507A3E8();
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(300, 1800);
    }
}

void func_1507B318(void) {
    D_800D1580 = func_1507A3E8();
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(300, 0xBB8);
    }
}

void func_1507B364(void) {
    D_800D1580 = func_1507A3E8();
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(0x2BC, 0xFA0);
    }
}

void func_1507B3B0(void) {
    D_800D1580 = func_1507A3E8();
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(0x2BC, 0xFA0);
    }
}

void func_1507B3FC(void) {
    D_800D1580 = func_1507A3E8();
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(0xBB8, 0x1F40);
    }
}

void func_1507B448(void) {
    D_800D1580 = func_1507A3E8();
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(0xBE, 0x514);
    }
}

void func_1507B494(void) {
    D_800D1580 = func_1507A3E8();
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(0xBE, 0x514);
    }
}

void func_1507B4E0(void) {
    D_800D1580 = func_1507A3E8();
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(100, 800);
    }
}

void func_1507B52C(void) {
    D_800D1580 = func_1507A3E8();
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(100, 800);
    }
}

void func_1507B578(void) {
    D_800D154C->unkD0 = D_800D1890;
    D_800D154C->unk114 = D_800D1891;
}

void func_1507B5C4(void) {
    if (D_800D154C->unk31C->unk75 == D_800D1891) {
        D_800D1892 ^= 1;
    }
    if (D_800D1892 != 0) {
        func_15075400(D_800D1890);
    }
}

void func_1507B630(void) {
    if ((D_800D154C->disable_run == 0) && (D_800D154C->unk28 == 0.0f)) {
        if (D_800D154C->unk31C->unk78 != 0) {
            D_800D1890 ^= 1;
        }
        if (D_800D1890 != 0) {
            D_800D154C->unk31C->unk8C |= 0x4000;
            D_800D154C->unk31C->unk8F = 0;
        }
    } else {
        D_800D154C->unk218 -= 1;
    }
    D_800D154C->unk21C = 100;
}

void func_1507B6E0(void) {
    if ((D_800D154C->disable_run != 0) || (D_800D154C->unk28 > 5.0f)) {
        D_800D154C->unk218 -= 1;
        D_800D154C->unk21C = 0x64;
    }
}

void func_1507B734(void) {
    u16 tmp = ((D_800D1890 << 8) | D_800D1891);
    if (D_800D1893 != 0) {
        D_800D154C->unk31C->unk8C = tmp;
        D_800D154C->unk31C->unk8F = D_800D1892;
    } else {
        D_800D154C->unk31C->unk8A = tmp;
        D_800D154C->unk31C->unk8E = D_800D1892;
    }
}

void func_1507B7BC(void) {
    func_15075548();
    D_800D154C->unk223 = 17;
}

void func_1507B7E8(void) {
    struct127 *tmp = &D_800CC2D0[D_800D154C->unk222];
    if ((tmp->stunned != 0) || (tmp->health == 0)) {
        D_800D1891 ^= 1;
    }
    if (D_800D1891 != 0) {
        func_15075400(D_800D1890);
    }
}

u8 func_1507B884(void) {
    s32 tmp0;
    s32 tmp1;
    u8 temp_v0;
    void (*func)(s32);

    temp_v0 = D_800D1890;
    func = D_80086150[temp_v0];
    if (func != 0) {
        tmp0 = D_800D154C;
        tmp1 = D_800C3E78;
        func(temp_v0);
        D_800D154C = tmp0;
        D_800C3E78 = tmp1;
    }
}

void func_1507B8F4(void) {

    if (D_800BE616 != 0) {
        if ((D_800D1891 != 0) || ((D_800D154C->unk31C != 0) && (D_800D154C->unk31C->unk84 != 0))) {
            func_15075400(D_800D1890);
        }
    }
}

void func_1507B958(void) {
    D_800D154C->unkB0 = D_800D1890;
}

void func_1507B974(void) {
    struct127 *var_v1 = D_800D154C;

    if (D_800D154C->unk65 != 0) {
        var_v1 = &D_800CC2D0[D_800D154C->unk65 - 1];
    }
    if (D_800D1891 == ((u16 (*)[4])D_800D2104[var_v1->unk13F])[var_v1->unk21E + D_800D1893][3]) {
        D_800D1892 ^= 1;
    }
    if (D_800D1892 != 0) {
        func_15075400(D_800D1890);
    }
}

void func_1507BA48(void) {
    u16 tmp = ((D_800D1892 << 8) | D_800D1893);
    if (D_800D1890 != 0) {
        tmp += func_150ADA20() % (u32) D_800D1890;
    }
    func_15060A9C(tmp, D_800D154C);
}

void func_1507BAD0(void) {
    D_800D154C->unkFC = func_1507A3E8();
}

void func_1507BAF8(void) {
    D_800D154C->unk2CC = func_1507A3E8();
}

void func_1507BB20(void) {
}

// scary loops
#ifdef NON_MATCHING
/* P102 draft (game_A28B0.c is not a port-b file): producer of the script pointer that func_15097E9C (cases 0x14,
 * 0x35, 0x60) and func_1507B... (game_A28B0.c line ~423) store in object +0x218. */
extern u8 D_8009A4E0[];          /* empty script */
extern u8 D_80086E28[];          /* default script list, 8-byte entries {script, kind} */

// object_find_script: returns the current object's script of a given kind (type list, then the default list).
/* (int: game_A28B0.c calls it before any prototype, i.e. as implicit int.) The script of kind `kind` for the current object D_800D154C: its type's list (pointer 0x10 bytes before the
 * type's D_800D1588 entry) is searched first; a list without that kind (a NULL script ends it) falls back to the
 * default list D_80086E28, which must contain it (the asm spins forever otherwise). No type entry / list: the
 * empty script D_8009A4E0. */
int func_1507BB28(s32 unused, s32 kind) {
    u8 *type;
    u8 *list;
    s32 i;

    type = ((u8 **)D_800D1588)[*((u8 *)D_800D154C + 4)];
    if (type == NULL) {
        return (s32)D_8009A4E0;
    }
    list = *(u8 **)(type - 0x10);
    if (list == NULL) {
        return (s32)D_8009A4E0;
    }
    for (i = 0; list[i * 8 + 4] != kind; i++) {
        if (*(u8 **)(list + i * 8) == NULL) {
            for (i = 0; D_80086E28[i * 8 + 4] != kind; i++) {
                if (*(u8 **)(D_80086E28 + i * 8) == NULL) {
                    for (;;) {
                    }
                }
            }
            return *(s32 *)(D_80086E28 + i * 8);
        }
    }
    return *(s32 *)(list + i * 8);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507BB28.s")
#endif
void func_1507BC14(struct127 *arg0) {

    if (arg0->unk21C != 0) {
        if (arg0->unk218 != 0) {
            if (arg0->unk21C != 25500) {
                arg0->unk21C = arg0->unk21C - D_800CC264;
            }
            if ((arg0->unk21C >= 50000) || (arg0->unk21C == 0)) {
                arg0->unk21C = 0;
                if ((arg0->unkF4 & 0x400) != 0) {
                    arg0->unk21C = 20000;
                    arg0->unkF4 &= ~0x400;
                    arg0->unkF4 |= 4;
                }
            } else {
                return;
            }
        }
    }

    if (arg0->unk218 == 0) {
        arg0->unk218 = func_1507BB28(0, arg0->unk232);
        arg0->unk21C = 0;
    }

    while (arg0->unk21C == 0) {
        if (arg0->unk218->unk0 >= 0xF7) {
            arg0->unk218 = (u8 *)(arg0->unk218) + 1;
        } else {
            D_800D1890 = arg0->unk218->unk1;
            D_800D1891 = arg0->unk218->unk2;
            D_800D1892 = arg0->unk218->unk3;
            D_800D1893 = arg0->unk218->unk4;
            D_80086730[arg0->unk218->unk0]();
            arg0->unk218 = (u8 *)(arg0->unk218) + 5;
        }
    }
}
