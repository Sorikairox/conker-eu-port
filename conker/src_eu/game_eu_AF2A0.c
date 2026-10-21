#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern s32 D_8008704C;
void func_15036F60(u8 *arg0);
#endif

typedef struct {
    /* 0x000 */ u8 pad0[0x1C9];
    /* 0x1C9 */ u8 unk1C9;
    /* 0x1CA */ u8 pad1CA[0xFA];
    /* 0x2C4 */ u8 *unk2C4;
    /* 0x2C8 */ u8 unk2C8;
} struct_eu_AF2A0;


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15081A90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15082020.s")

void func_1507DF10(u8 *, s32, u8);
void func_1508220C(u8 *arg0, u16 v, u8 arg2) {
    if (D_800BE616 == 0) {
        if (arg0[0x1CA] != 0) {
            arg0[0x1CA] = 7;
        }
        if (arg2 == 0 || v != 10) {
            func_1507DF10(arg0, v, arg2);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15082278.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_150829C0.s")

s32 func_150829C0(s32, s32);
extern u8 D_800D2520;
extern u8 D_800D2521;
void func_15082D5C(s32 arg0, s32 arg1, s32 arg2) {
    s32 lo;
    s32 hi;
    s32 i;
    if (arg2 != 0) {
        lo = 0;
        hi = D_800D2521;
    } else {
        lo = D_800D2521;
        hi = D_800D2520;
    }
    i = lo;
    if (lo < hi) {
        do {
            func_150829C0(i, arg1);
            i += 1;
        } while (i != hi);
    }
}

void func_15082DD8(u8 *arg0) {
    u8 *temp_v0;

    *(s32 *)(arg0 + 0xF8) &= 0xF7FFFFFD;
    temp_v0 = *(u8 **)(arg0 + 0x31C);
    *(s32 *)(arg0 + 0xF8) |= 4;
    if ((temp_v0 != NULL) && (temp_v0[0x56] == 0)) {
        switch (D_800BE9F0) {
        case 0x0:
        case 0xA:
        case 0xE:
        case 0x12:
        case 0x13:
        case 0x19:
        case 0x1B:
        case 0x2C:
        case 0x3C:
        case 0x3D:
        case 0x42:
        case 0x43:
        case 0x44:
            break;
        default:
            *(s32 *)(arg0 + 0xF8) |= 2;
            break;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15082E44.s")

typedef struct {
    u8 pad0[0x127];
    u8 unk127;
    u8 pad128[0x1C];
    u8 *unk144;
    u8 pad148[0x1B8];
    u8 unk300;
    u8 unk301;
    u8 pad302[2];
    s32 unk304[4];
    s32 unk314;
} S836AC;
s32 func_1515D9F0(s32);
s32 func_1515D9B0(void);
void func_150836AC(S836AC *arg0)
{
    s32 i;
    s32 sel;
    u8 tmp;

    if (arg0->unk144 != NULL) {
        tmp = arg0->unk144[0x2F];
        if (tmp == 0) { if (arg0->unk127 == 0) sel = 5; else sel = 3; } else { sel = tmp; }
        for (i = 0; i <= D_80082FA0; i++) {
            arg0->unk304[i] = func_1515D9F0(sel);
        }
        if (arg0->unk304[i - 1] != 0) {
            arg0->unk301 = sel;
        }
        arg0->unk314 = func_1515D9B0();
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083784.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083568.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_150836CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083C3C.s")

#ifdef NON_MATCHING
struct197 *allocate_memory(s32, s32, s32, s32);

s32 func_15083D54(struct127 *arg0, u16 arg1, s32 arg2, f32 arg3) {
    struct197 *temp_v0_2;
    u8 temp_v0;

    temp_v0 = arg0->id;
    if (D_800D1588[temp_v0] == 0) {
        goto block_7;
    }
    if ((u16) D_800C5A90[temp_v0] == 0) {
        goto block_7;
    }
    temp_v0_2 = allocate_memory(0x3E0, 1, 2, 0);
    arg0->unk2D0 = temp_v0_2;
    if (temp_v0_2 == NULL) {
        return 1;
    }
    bzero(arg0->unk2D0, 0x40);
    func_1505E650(arg0, arg1, arg3, 0.0f, 0.0f, 0.0f, arg2);
block_7:
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083D54.s")
#endif
#ifdef NON_MATCHING
/* Copy an object's per-type parameters from its type record D_800D1C90[type] (P15, hand C). */
void func_15083E20(u8 *arg0, u16 type, u8 *arg2) {
    u8 *t;

    if (type == 0xFF) {
        return;
    }
    t = (u8 *)D_800D1C90[type];
    if (arg2 != NULL) {
        u16 v = *(u16 *)(arg2 + 0x2C);

        if (v == 0) {
            *(u16 *)(arg0 + 0x10) = *(u16 *)(t + 0x2A);
        } else if (v == 1) {
            *(u16 *)(arg0 + 0x10) = 0;
        } else {
            *(u16 *)(arg0 + 0x10) = v;
        }
        if (D_800BE9F0 == 0x1D) {
            *(u16 *)(arg0 + 0x10) = 1000;
        }
    } else {
        *(u16 *)(arg0 + 0x10) = 0;
    }
    arg0[0x13B] = t[0x39];
    *(s8 *)(arg0 + 0x2CB) = *(s8 *)(t + 0x33);
    *(s32 *)(arg0 + 0x2CC) = *(s32 *)(t + 0x34);
    arg0[5] = t[0x12];
    arg0[0x68] = t[0x3B];
    arg0[0x69] = t[0x3C];
    *(s16 *)(arg0 + 0x160) = *(s16 *)(t + 2);
    if (t[4] != 0) {
        *(s32 *)(arg0 + 0x2C4) = (&D_8008704C)[t[5]];
        arg0[0x2C8] = t[4];
    }
    arg0[0x2C9] = arg0[0x2C8] + t[0x38];
    if (t[0x29] != 0) {
        func_15036F60(arg0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083E20.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083F30.s")

s32 func_15084208(void) {
    s32 id;
    s32 i;
    id = 1;
    i = 0;
    if (D_800D2520 > 0) {
        do {
            if (id == *((u8 *)D_800D20FC + i * 0x30 + 0x28)) {
                id++;
                i = 0;
            }
            i++;
        } while (i < D_800D2520);
    }
    if (id >= 0x100) {
        id = 0xFF;
    }
    return id;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083E0C.s")

#ifdef NON_MATCHING
extern u8 D_800CC72B;
extern struct127 D_800CCA1C;

struct127 *func_15083E90(u8 arg0) {
    s32 temp_t6;
    s32 var_a0;
    struct127 *temp_v1;
    struct127 *temp_v1_2;
    struct127 *temp_v1_3;
    struct127 *var_v1;

    temp_t6 = arg0 & 0xFF;
    if (temp_t6 == 0) {
        return NULL;
    }
    if ((D_800CC2D0->interaction_state != 0) && (temp_t6 == D_800CC72B)) {
        return D_800CC2D0;
    }
    var_a0 = 2;
    if ((D_800CCA1C.interaction_state != 0) && (temp_t6 == D_800CCA1C.unique_id)) {
        return &D_800CCA1C;
    }
    var_v1 = ((struct127 *)((u8 *)&D_800CCA1C + 0x32C));
loop_9:
    if ((var_v1->interaction_state != 0) && (temp_t6 == var_v1->unique_id)) {
        return var_v1;
    }
    temp_v1_3 = ((struct127 *)((u8 *)var_v1 + 0x32C));
    if ((var_v1[1].interaction_state != 0) && (temp_t6 == temp_v1_3->unique_id)) {
        return temp_v1_3;
    }
    temp_v1_2 = ((struct127 *)((u8 *)temp_v1_3 + 0x32C));
    if ((temp_v1_3[1].interaction_state != 0) && (temp_t6 == temp_v1_2->unique_id)) {
        return temp_v1_2;
    }
    temp_v1 = ((struct127 *)((u8 *)temp_v1_2 + 0x32C));
    var_a0 += 4;
    if ((temp_v1_2[1].interaction_state != 0) && (temp_t6 == temp_v1->unique_id)) {
        return temp_v1;
    }
    var_v1 = ((struct127 *)((u8 *)temp_v1 + 0x32C));
    if (var_a0 == 0x1A) {
        return NULL;
    }
    goto loop_9;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083E90.s")
#endif
s32 func_15083FB0(u8 arg0) {
    struct127 *p = func_15083E90(arg0);

    if (p != NULL) {
        return p - D_800CC2D0;
    }
    return -1;
}

s32 func_15084000(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct127 *temp_v0 = func_1505EEF4(arg0, arg1, arg2, arg3);

    if (temp_v0 != NULL) {
        return temp_v0 - D_800CC2D0;
    }
    return -1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_150844AC.s")

void func_15084814(struct127 *, s32);

void func_150847B4(u8 *arg0) {
    s32 var_s0;
    u8 var_s1;

    var_s1 = (*(u8 *)((u8 *)arg0 + 0x2C9));
    if (var_s1 == 0) {
        var_s1 = 1;
    }
    var_s0 = 0;
    if ((s32) var_s1 > 0) {
        do {
            func_15084814(arg0, var_s0);
            var_s0 += 1;
        } while (var_s0 != var_s1);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15084814.s")

s32 func_1503D950(s32, s32);
s32 func_1503DA64(s32, s32);
extern s32 D_8008704C;

void func_150848F0(u8 *arg0, s32 arg1, s32 arg2) {
    s32 var_s1;
    struct124 *temp_v0;
    u8 *var_s0;
    u8 *var_v1;
    u8 temp_s0;
    s32 var_s2;

    temp_s0 = arg0[4];
    if (temp_s0 != 0xFF) {
        func_1503DA64(temp_s0, arg2);
        temp_v0 = D_800D1C90[temp_s0];
        var_v1 = arg0 + 4;
        var_s2 = temp_v0->unk4;
        if (var_s2 == 0) {
            var_s2 = 1;
        } else {
            var_v1 = *(u8 **)(&D_8008704C + (u8) temp_v0->unk5);
        }
        var_s1 = 0;
        var_s0 = var_v1;
        var_s2 += *(u8 *)((u8 *)temp_v0 + 0x38);
        if (var_s2 > 0) {
            do {
                func_1503DA64(*var_s0, arg2);
                func_1503D950(*var_s0, arg2);
                var_s1 += 1;
                var_s0 += 1;
            } while (var_s1 != var_s2);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_150849C0.s")

u8 func_15084E08(struct_eu_AF2A0 *arg0) {
    s32 temp_v1 = arg0->unk1C9;

    if (temp_v1 != 0) {
        return arg0->unk2C4[temp_v1 - 1];
    }
    return arg0->unk2C4[0];
}

u8 func_15084E34(struct_eu_AF2A0 *arg0, s32 *arg1) {
    s32 temp_v1;

    if (arg0->unk1C9 != 0) {
        temp_v1 = arg0->unk1C9 - 1;
    } else {
        temp_v1 = (arg0->unk2C8 != 0) ? arg0->unk2C8 - 1 : 0;
    }
    if (arg1 != NULL) {
        *arg1 = temp_v1;
    }
    return arg0->unk2C4[temp_v1];
}

#ifdef NON_MATCHING
/* Per-frame countdown of the 187 resource slots (P15, hand C from the asm). D_800D2040 holds one
 * byte timer per slot (0 = idle, 0xFF = pinned). When a timer reaches 1 and the slot owns a block
 * (D_800D19A0[i]) that is not locked (D_800C5C08[i] == 0), the block is released: object references to
 * it (struct127 words 0x28C.., two per entry, unk2C9 entries) are cleared, objects whose entry list
 * (unk2C4) names slot i are notified through func_15084814, the slot's 12-byte records
 * (D_800C5758[i], D_800C5A48[i] of them) free their texture through func_1510DCA0, then the block
 * (minus its 0x38-byte header) goes back to the allocator. */
void func_1510DCA0(s32);
extern u16 D_800C5A48[];         /* record count per slot */
extern u8 *D_800C5758[];         /* 12-byte records per slot */
void func_15084E80(void) {
    u8 *timers = (u8 *)D_800D2040;
    s32 *blocks = &D_800D19A0;
    u16 *counts = D_800C5A48;
    u8 **records = D_800C5758;
    s32 i;

    for (i = 0; i != 187; i++) {
        u8 t = timers[i];

        if (t == 0xFF || t == 0) {
            continue;
        }
        if (t == 1 && blocks[i] != 0 && D_800C5C08[i] == 0) {
            struct127 *obj;
            u8 *rec;
            s32 j;

            for (obj = D_800CC2D0; (u32)obj < (u32)&D_800D121C; obj++) {
                if (obj->interaction_state == 0) {
                    continue;
                }
                for (j = 0; j < obj->unk2C9; j++) {
                    s32 *ref = &obj->unk28C + j * 2;

                    if (ref[0] == blocks[i]) {
                        ref[0] = 0;
                    }
                    if (ref[1] == blocks[i]) {
                        ref[1] = 0;
                    }
                    if (((u8 *)obj->unk2C4)[j] == i) {
                        func_15084814(obj, j);
                    }
                }
            }
            rec = records[i];
            for (j = 0; j < counts[i]; j++, rec += 0xC) {
                if (*(u32 *)rec >= 0x10000000U) {
                    func_1510DCA0(*(s32 *)(rec + 4));
                }
            }
            func_10004074(blocks[i] - 0x38);
            ((u8 *)D_800D1F80)[i] = 0;
            blocks[i] = 0;
            t = timers[i];
        }
        timers[i] = t - 1;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15084E80.s")
#endif
void func_15085098(u8 *arg0) {
    u8 *p;
    f32 r;
    if (arg0[4] == 0x94) {
        p = *(u8 **)(arg0 + 0x2D0);
        r = (f32)((u32)func_150ADA20() % (u32)(s32)*(f32 *)(p + 0x18));
        *(f32 *)(p + 8) = r;
    }
}

extern u8 D_800BE9B0;
extern u16 D_800BE9B8[];
s32 func_15085118(s32 arg0) {
    s32 ret = 0;
    s32 i;

    for (i = 0; i < D_800BE9B0; i++) {
        if (arg0 == D_800BE9B8[i]) {
            ret = i;
            break;
        }
    }
    return ret;
}
