#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
typedef struct {
    f32 f[4];        // 0x00
    s16 u10;         // 0x10
    s16 u12;         // 0x12
    struct127 *obj;  // 0x14
    u8 id;           // 0x18 obj[0x3B]
    u8 u19;          // 0x19
    u8 u1A;          // 0x1A
} ObjEffect1FSpec;   // 0x1C bytes, copied by func_1518C240
u8 *func_1518C240(s32, u8, s32);

// obj_effect1F_attach: the type-0x1F effect node (lists D_800DD280[0..1][0x1F]) that belongs to `obj` (+0x24) or has
// its id (+0x28 == obj[0x3B]); if there is none, spawns one with func_1518C240 (`arg1`, `arg2` passed on) whose
// parameters depend on the object's kind obj[4]: 0..4 -> 10.0 x4 / 5 / 0, 7 -> (2.76, 5.96, 3.21, 5.0) / 4 / 0x37.
// Nothing for a NULL object or another kind. void: the asm returns the node, but the only caller (game_eu_C5530,
// a void prototype) ignores it.
void func_1518C000(struct127 *obj, s32 arg1, s32 arg2) {
    ObjEffect1FSpec spec;
    struct_eu_node *node;
    s32 i;

    if (obj == NULL) {
        return;
    }
    for (i = 0; i < 2; i++) {
        for (node = D_800DD280[i][0x1F]; node != NULL; node = node->next) {
            if (*(struct127 **) ((u8 *) node + 0x24) == obj || ((u8 *) obj)[0x3B] == *((u8 *) node + 0x28)) {
                return;
            }
        }
    }
    switch (((u8 *) obj)[4]) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            spec.u12 = 0;
            spec.u10 = 5;
            spec.u19 = 5;
            spec.u1A = 0x13;
            spec.f[0] = 10.0f;
            spec.f[1] = 10.0f;
            spec.f[2] = 10.0f;
            spec.f[3] = 10.0f;
            break;
        case 7:
            spec.u12 = 0x37;
            spec.u10 = 4;
            spec.u19 = 5;
            spec.u1A = 0x13;
            spec.f[0] = 2.76f;
            spec.f[1] = 5.96f;
            spec.f[2] = 3.21f;
            spec.f[3] = 5.0f;
            break;
        default:
            return;
    }
    spec.obj = obj;
    spec.id = ((u8 *) obj)[0x3B];
    func_1518C240((s32) &spec, arg1, arg2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B9810/func_1518C000.s")
#endif

void func_1518C164(u8 *arg0) {
    s32 i;
    struct_eu_node *node;

    if (arg0 != NULL) {
        for (i = 0; i < 2; i++) {
            u8 *new_var; // fakematch: permuter temp, turns the loop tail into bnel
            node = D_800DD280[i][0x1F];
            D_800DD5C0++;
            while (node != NULL) {
                D_800DD5C8[D_800DD5C0] = node->next;
                new_var = (u8 *)node;
                *(u8 **)(new_var + 0x24) = arg0;
                if ((arg0 != NULL) || (arg0[0x3B] == *((u8 *)node + 0x28))) {
                    node_destroy((struct102 *)node);
                }
                node = D_800DD5C8[D_800DD5C0];
            }
            D_800DD5C0--;
        }
    }
}

s32 memcpy(u8 *, s32, s32);

u8 *func_1518C240(s32 arg0, u8 arg1, s32 arg2) {
    u8 *temp_v0;

    temp_v0 = node_alloc(0x1F, arg2, 0x44, 1, (u8) (s32) arg1, 1U);
    if (temp_v0 == NULL) {
        return NULL;
    }
    memcpy(temp_v0 + 0x10, arg0, 0x1C);
    (*(s32 *)((u8 *)temp_v0 + 0x2C)) = (s32) (random_int() & 0x1F);
    (*(s32 *)((u8 *)temp_v0 + 0x30)) = (s32) (random_int() & 0x1F);
    return temp_v0;
}

#ifdef NON_MATCHING
u8 *func_15148310(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 *argB, s32 argC, u8 argD, s32 argE);

void func_1518C2D0(u8 *arg0) {
    struct {
        s32 uB8;
        s32 uBC;
        s32 uC0;
        s32 uC4;
        s32 uC8;
        s32 uCC;
        s32 uD0;
        s8 uD4;
        s8 uD5;
        u8 padD6[0x6];
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
        u8 padF0[0x4];
        s8 uF4;
        u8 uF5;
        s8 uF6;
        s8 uF7;
        u8 padF8[0x4];
        s32 uFC;
        u8 pad100[0x8];
        s16 u108;
        s16 u10A;
        s32 u10C;
        u8 pad110[0x1];
        u8 u111;
    } sp;
    f32 temp_f0;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    s32 temp_t9;
    s32 temp_v0_2;
    s8 temp_t7;
    s8 var_s3;
    u32 temp_hi;
    u8 *temp_s2;
    u8 *temp_v0;
    u8 *temp_v1;
    u8 *temp_v1_2;

    var_s3 = 0;
    do {
        temp_s2 = arg0 + (var_s3 * 4);
        temp_t9 = (*(s32 *)((u8 *)temp_s2 + 0x2C)) - D_800BE9E4;
        (*(s32 *)((u8 *)temp_s2 + 0x2C)) = temp_t9;
        temp_v1 = (*(u8 **)((u8 *)arg0 + 0x24));
        if ((temp_v1 != NULL) && ((*(s32 *)((u8 *)temp_v1 + 0)) != 0) && ((*(s32 *)((u8 *)temp_v1 + 0x1D4)) != 0) && ((*(u8 *)((u8 *)arg0 + 0x28)) == (*(u8 *)((u8 *)temp_v1 + 0x3B)))) {
            if (temp_t9 < 0) {
                temp_hi = random_int() % (u32) ((*(s16 *)((u8 *)arg0 + 0x22)) + 1);
                temp_f22 = angle_byte_cos(temp_hi & 0xFF);
                temp_f24 = angle_byte_cos((temp_hi - 0x40) & 0xFF);
                temp_f20 = (random_float() * (*(f32 *)((u8 *)arg0 + 0x14))) + (*(f32 *)((u8 *)arg0 + 0x10));
                (*(s32 *)((u8 *)temp_s2 + 0x2C)) = (s32) ((random_int() % 23U) + 5);
                sp.uB8 = 0;
                sp.uBC = 1;
                sp.uC0 = 0x160600;
                sp.uC4 = 3;
                sp.uC8 = 0x10;
                sp.uCC = 0x80;
                sp.uD0 = 0x20;
                sp.uD4 = 0;
                sp.uD5 = 9;
                sp.u111 = (random_int() % (u32) ((*(s16 *)((u8 *)arg0 + 0x20)) + 1)) + 3;
                sp.u10C = 1;
                sp.u10A = 1;
                sp.u108 = (random_int() % 21U) + 0x50;
                sp.uF5 = (*(u8 *)((u8 *)arg0 + 0x29));
                temp_f0 = random_float();
                sp.uE4 = 0.0f;
                sp.uEC = 0.654f;
                sp.uE0 = temp_f20 * temp_f24;
                sp.uDC = (temp_f0 * (*(f32 *)((u8 *)arg0 + 0x1C))) + (*(f32 *)((u8 *)arg0 + 0x18));
                sp.uE8 = temp_f20 * temp_f22;
                sp.uF4 = (*(u8 *)((u8 *)arg0 + 0x2A)) | 8;
                sp.uF7 = 0xFF;
                sp.uF6 = 0xFF - (((u32) (*(u32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x24))) + 0x184)) >> 5) << 6);
                temp_v0 = func_15148310(&sp.uFC, &sp.uDC, (sp.u111 * 0xC) + 8, 5, 1, 0, 2, 1, 0, 0, 0, &sp.uB8, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                if (temp_v0 != NULL) {
                    temp_v1_2 = (*(s32 *)((u8 *)temp_v0 + 0x98)) + 0x48;
                    (*(u8 **)((u8 *)temp_v1_2 + 0)) = arg0;
                    (*(s8 *)((u8 *)temp_v1_2 + 4)) = var_s3;
                }
            }
            temp_v0_2 = var_s3 * 6;
            (*(f32 *)((u8 *)temp_s2 + 0x34)) = (f32) (*(s16 *)((u8 *)(((*(u8 **)((u8 *)arg0 + 0x24)) + temp_v0_2)) + 0x1AC));
            (*(f32 *)((u8 *)temp_s2 + 0x3C)) = (f32) (*(s16 *)((u8 *)(((*(u8 **)((u8 *)arg0 + 0x24)) + temp_v0_2)) + 0x1B0));
        }
        temp_t7 = (var_s3 + 1) & 0xFF;
        var_s3 = temp_t7;
    } while (temp_t7 < 2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B9810/func_1518C2D0.s")
#endif
#ifdef NON_MATCHING
s32 func_1518C628(u8 *arg0) {
    struct {
        f32 u40;
        f32 u44;
        f32 u48;
        u8 pad4C[0x14];
    } sp;
    f32 sp20;
    f32 sp1C;
    f32 sp10;
    f32 sp4;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f18;
    f32 temp_f8;
    f32 temp_f8_2;
    f32 temp_f8_3;
    f32 var_f12;
    f32 var_f2;
    s16 var_a1;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_v0;
    s32 var_t1;
    s8 temp_a3;
    s8 var_a3;
    s8 var_a3_2;
    u8 *temp_a1;
    u8 *temp_a2;
    u8 *temp_a2_2;
    u8 *temp_t0;
    u8 *temp_t0_2;
    u8 *temp_t0_3;
    u8 *temp_t1;
    u8 *temp_t7;
    u8 *temp_v0_2;
    u8 *temp_v1;

    temp_v1 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_v0 = (*(s32 *)((u8 *)arg0 + 0x94));
    var_a3 = (*(s8 *)((u8 *)arg0 + 0x2D));
    temp_a1 = temp_v1 + 0x48;
    if (((*(s32 *)((u8 *)((*(u8 **)((u8 *)temp_v1 + 0x48))) + 0x24)) == 0) || (temp_a2 = (*(u8 **)((u8 *)temp_a1 + 0)), temp_t0 = (*(u8 **)((u8 *)temp_a2 + 0x24)), ((*(s32 *)((u8 *)temp_t0 + 0)) == 0)) || ((*(s32 *)((u8 *)temp_t0 + 0x1D4)) == 0) || ((*(u8 *)((u8 *)temp_a2 + 0x28)) != (*(u8 *)((u8 *)temp_t0 + 0x3B)))) {
        return 0;
    }
    sp.u40 = (f32) (*(s16 *)((u8 *)((temp_t0 + ((*(s8 *)((u8 *)temp_a1 + 4)) * 6))) + 0x1AC));
    sp.u44 = (f32) (*(s16 *)((u8 *)(((*(u8 **)((u8 *)((*(u8 **)((u8 *)temp_a1 + 0))) + 0x24)) + ((*(s8 *)((u8 *)temp_a1 + 4)) * 6))) + 0x1AE));
    sp.u48 = (f32) (*(s16 *)((u8 *)(((*(u8 **)((u8 *)((*(u8 **)((u8 *)temp_a1 + 0))) + 0x24)) + ((*(s8 *)((u8 *)temp_a1 + 4)) * 6))) + 0x1B0));
    temp_t0_2 = (*(u8 **)((u8 *)((*(u8 **)((u8 *)temp_a1 + 0))) + 0x24));
    temp_f14 = (f32) (*(s8 *)((u8 *)temp_t0_2 + 0x1B8)) * 0.00390625f;
    temp_f16 = (f32) (*(s8 *)((u8 *)temp_t0_2 + 0x1BA)) * 0.00390625f;
    temp_f18 = (temp_f14 * temp_f14) + (temp_f16 * temp_f16);
    if (temp_f18 != 0.0f) {
        temp_f8 = 1.0f / sqrtf(temp_f18);
        var_f2 = temp_f14 * temp_f8;
        sp4 = temp_f8;
        var_f12 = temp_f16 * temp_f8;
    } else {
        var_f2 = 0.0f;
        var_f12 = 0.0f;
    }
    if (var_a3 != (*(s8 *)((u8 *)arg0 + 0x2E))) {
        do {
            temp_t0_3 = temp_v0 + (var_a3 * 0x14);
            temp_f8_2 = (*(f32 *)((u8 *)temp_t0_3 + 0xC));
            temp_lo = var_a3 * 0xC;
            var_a3 += 1;
            (*(f32 *)((u8 *)temp_t0_3 + 0xC)) = (f32) (temp_f8_2 - ((*(f32 *)((u8 *)temp_v1 + 0x10)) * D_800BE9A4));
            temp_t1 = temp_v1 + 0x50 + temp_lo;
            (*(f32 *)((u8 *)temp_t1 + 0)) = (f32) ((*(f32 *)((u8 *)temp_t1 + 0)) + ((*(f32 *)((u8 *)temp_v1 + 4)) * D_800BE9A4));
            (*(f32 *)((u8 *)temp_t1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_t1 + 4)) + (*(f32 *)((u8 *)temp_t0_3 + 0xC)));
            (*(f32 *)((u8 *)temp_t1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_t1 + 8)) + ((*(f32 *)((u8 *)temp_v1 + 0xC)) * D_800BE9A4));
            (*(f32 *)((u8 *)temp_t0_3 + 0)) = (f32) (((*(f32 *)((u8 *)temp_t1 + 8)) * var_f2) + (sp.u40 + ((*(f32 *)((u8 *)temp_t1 + 0)) * var_f12)));
            (*(f32 *)((u8 *)temp_t0_3 + 4)) = (f32) ((*(f32 *)((u8 *)temp_t1 + 4)) + sp.u44);
            (*(f32 *)((u8 *)temp_t0_3 + 8)) = (f32) ((sp.u48 + ((*(f32 *)((u8 *)temp_t1 + 8)) * var_f12)) - ((*(f32 *)((u8 *)temp_t1 + 0)) * var_f2));
            if (var_a3 == (*(u8 *)((u8 *)arg0 + 0x25))) {
                var_a3 = 0;
            }
        } while (var_a3 != (*(s8 *)((u8 *)arg0 + 0x2E)));
    }
    temp_a3 = (*(s8 *)((u8 *)arg0 + 0x2C));
    if (temp_a3 < ((*(u8 *)((u8 *)arg0 + 0x25)) - 1)) {
        var_a1 = 0;
        var_t1 = 0;
        temp_a2_2 = temp_v1 + 0x50;
        if (temp_a3 != 0) {
            var_t1 = (0x1000 / temp_a3) & 0xFFFF;
        }
        temp_t7 = temp_v0 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x14);
        (*(f32 *)((u8 *)temp_t7 + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u40) + 0));
        (*(s32 *)((u8 *)temp_t7 + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u40) + 4));
        (*(s32 *)((u8 *)temp_t7 + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u40) + 8));
        (*(f32 *)((u8 *)((temp_v0 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x14))) + 0xC)) = 0.0f;
        (*(f32 *)((u8 *)((temp_a2_2 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0xC))) + 0)) = 0.0f;
        (*(f32 *)((u8 *)((temp_a2_2 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0xC))) + 4)) = 0.0f;
        (*(f32 *)((u8 *)((temp_a2_2 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0xC))) + 8)) = 0.0f;
        (*(s8 *)((u8 *)arg0 + 0x2E)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2E)) + 1);
        (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) + 1);
        if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2E))) {
            (*(s8 *)((u8 *)arg0 + 0x2E)) = 0;
        }
        var_a3_2 = (*(s8 *)((u8 *)arg0 + 0x2D));
        if (var_a3_2 != (*(s8 *)((u8 *)arg0 + 0x2E))) {
            do {
                temp_lo_2 = var_a3_2 * 0x14;
                var_a3_2 += 1;
                (*(s16 *)((u8 *)((temp_v0 + temp_lo_2)) + 0x10)) = var_a1;
                var_a1 = (var_a1 + var_t1) & 0xFFFF;
                if (var_a3_2 == (*(u8 *)((u8 *)arg0 + 0x25))) {
                    var_a3_2 = 0;
                }
            } while (var_a3_2 != (*(s8 *)((u8 *)arg0 + 0x2E)));
        }
    } else {
        temp_f0 = (*(f32 *)((u8 *)temp_v1 + 4));
        temp_f14_2 = (*(f32 *)((u8 *)temp_v1 + 0xC));
        temp_f16_2 = 1.0f / D_800BE9A4;
        sp10 = (temp_f14_2 * var_f12) - (temp_f0 * var_f2);
        temp_v0_2 = (*(u8 **)((u8 *)temp_a1 + 0)) + ((*(s8 *)((u8 *)temp_a1 + 4)) * 4);
        temp_f10 = (sp.u40 - (*(f32 *)((u8 *)temp_v0_2 + 0x34))) * temp_f16_2;
        sp20 = temp_f10;
        temp_f8_3 = (sp.u48 - (*(f32 *)((u8 *)temp_v0_2 + 0x3C))) * temp_f16_2;
        sp1C = temp_f8_3;
        (*(f32 *)((u8 *)temp_v1 + 4)) = (f32) ((temp_f0 * var_f12) + (temp_f14_2 * var_f2) + temp_f10);
        (*(f32 *)((u8 *)temp_v1 + 0xC)) = (f32) (sp10 + temp_f8_3);
        if ((*(u8 *)((u8 *)temp_v1 + 0x18)) & 0x17) {
            (*(s8 *)((u8 *)temp_v1 + 0x20)) = 3;
        } else {
            (*(s8 *)((u8 *)temp_v1 + 0x20)) = 2;
        }
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B9810/func_1518C628.s")
#endif
s32 func_1518CAB0(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    s32 var_v1 = *(s16 *)(arg0 + 0x1C) * 8;

    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }
    temp_v0[0x1B] = var_v1;
    if (temp_v0[0x1B] < 0) {
        return 0;
    }
    return 1;
}

typedef struct { f32 x, y, z; s32 a, b; } Node14;
typedef struct {
    u8 pad0[0x80];
    s32 u80;
    u8 pad84[6];
    s16 u8A;
    s16 u8C;
    s16 u8E;
    s16 u90;
    s16 u92;
    s16 u94;
    s16 u96;
    s16 u98;
    u8 pad9A[6];
    s8 uA0;
    s8 uA1;
    s8 uA2;
    u8 padA3[5];
} SpawnCAEC;
s32 sprite_vtx_quads_init(SpawnCAEC *, s32, s32, s32, s32);
s32 node_spawn_vtx_sprite(SpawnCAEC *, u8, u8);

s32 func_1518CAEC(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    SpawnCAEC sp;
    u8 *obj;
    u8 *tbl;

    obj = *(u8 **)(arg0 + 0x98);
    tbl = *(u8 **)(arg0 + 0x94);
    arg2 = arg4; // fakematch: the unused arg2 holds the truncated arg4 (spill slot layout, permuter)
    sp.u80 = 0;
    sp.u8A = 0x100;
    sp.u8C = ((Node14 *)tbl)[*(s8 *)(arg0 + 0x2D)].x;
    sp.u8E = arg2;
    sp.u90 = ((Node14 *)tbl)[*(s8 *)(arg0 + 0x2D)].z;
    sp.u92 = sp.u94 = random_int() % 21U + 0x23;
    sp.uA2 = -1;
    sp.uA0 = 0x12;
    sp.u98 = 0xC;
    sp.uA1 = 0;
    sp.u96 = arg2;
    sprite_vtx_quads_init(&sp, 0xFF, 0xFF, 0xFF, 0xFF);
    node_spawn_vtx_sprite(&sp, *(u8 *)(arg0 + 0xC), *(u8 *)(arg0 + 1));
    *(s8 *)(obj + 0x20) = 4;
    return 1;
}

#ifdef NON_MATCHING
s32 func_1518CC0C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5) {
    struct {
        f32 u38;
        f32 u3C;
        f32 u40;
        u8 pad44[0x3];
        u8 u47;
        s32 u48;
        u8 * u4C;
        SpawnCAEC u50;
    } sp;
    s32 sp30;
    s16 temp_t4;
    s32 temp_f10;
    s32 temp_v1;

    sp.u4C = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_v1 = (*(s32 *)((u8 *)arg0 + 0x94));
    sp.u50.u80 = 0;
    sp.u50.u8A = 0x100;
    temp_f10 = (s32) arg4;
    sp.u50.u8E = (s16) temp_f10;
    sp.u50.u8C = (s16) (s32) *(s32 *)(temp_v1 + ((*(s8 *)((u8 *)arg0 + 0x2D)) * 0x14));
    sp.u48 = temp_v1;
    sp30 = temp_f10;
    sp.u50.u90 = (s16) (s32) (*(f32 *)((u8 *)((temp_v1 + ((*(s8 *)((u8 *)arg0 + 0x2D)) * 0x14))) + 8));
    temp_t4 = (random_int() % 21U) + 0x23;
    sp.u50.u92 = temp_t4;
    sp.u50.uA2 = -1;
    sp.u50.uA0 = 0x12;
    sp.u50.u98 = 0xC;
    sp.u50.uA1 = 0;
    sp.u50.u94 = temp_t4;
    sp.u50.u96 = (s16) temp_f10;
    sprite_vtx_quads_init(&sp.u50, 0xFF, 0xFF, 0xFF, 0xFF);
    node_spawn_vtx_sprite(&sp.u50, (*(u8 *)((u8 *)arg0 + 0xC)), (*(u8 *)((u8 *)arg0 + 1)));
    (*(s8 *)((u8 *)sp.u4C + 0x20)) = 4;
    sp.u3C = arg4;
    sp.u38 = *(s32 *)(sp.u48 + ((*(s8 *)((u8 *)arg0 + 0x2D)) * 0x14));
    sp.u40 = (*(f32 *)((u8 *)((sp.u48 + ((*(s8 *)((u8 *)arg0 + 0x2D)) * 0x14))) + 8));
    sp.u47 = impact_current_kind(0x14);
    impact_dust_particle_spawn(sp.u47, (random_float() * 40.0f) + 100.0f, 0xFF, arg5, &sp.u38, (u8) (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B9810/func_1518CC0C.s")
#endif
void func_1518CDC0(struct102 *arg0, u8 *arg1, u8 arg2) {
    s32 id;
    if (arg2 == 0x2D) {
        if (*(s32 *)(arg1 + 0) == *(s32 *)((u8 *)arg0 + 0x24)) {
            (*(s32 *)((u8 *)arg0 + 0x24)) = (s32) (*(s32 *)((u8 *)arg1 + 4));
            arg0->unk28 = (*(u8 *)((u8 *)arg1 + 9));
        } else if (*(s32 *)(arg1 + 4) == *(s32 *)((u8 *)arg0 + 0x24)) {
            (*(s32 *)((u8 *)arg0 + 0x24)) = *(s32 *)(arg1 + 0);
            arg0->unk28 = (*(u8 *)((u8 *)arg1 + 8));
        }
        goto dummy_label; dummy_label: ; // fakematch: b + target-copied delay slot
    } else if (arg2 == 0) {
        id = *(s32 *)(arg1 + 0);
        if ((id == (*(s32 *)((u8 *)arg0 + 0x24))) || (arg0->unk28 == *(u8 *)(arg1 + 4))) {
            node_destroy(arg0);
        }
    }
}
