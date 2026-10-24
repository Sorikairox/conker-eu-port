#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_129650/func_150FBE40.s")

#ifdef NON_MATCHING
void func_150FC8E8(u8 *arg0) {
    s32 var_v0;
    u8 *temp_v0;
    u8 *temp_v1;
    u8 *temp_v1_2;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x1A0));
    if ((temp_v0 == NULL) || ((*(s32 *)((u8 *)temp_v0 + 0)) == 0) || ((*(u8 *)((u8 *)temp_v0 + 4)) == 0xFF) || ((*(u8 *)((u8 *)arg0 + 0x1A4)) != (*(u8 *)((u8 *)temp_v0 + 0x3B))) || (temp_v1 = (*(u8 **)((u8 *)temp_v0 + 0x31C)), (temp_v1 == NULL)) || ((*(u8 *)((u8 *)temp_v1 + 0x84)) != 0) || ((*(u8 *)((u8 *)temp_v0 + 0x127)) == 0xFF) || (temp_v1_2 = (*(u8 **)((u8 *)temp_v0 + 0x318)), (temp_v1_2 == NULL))) {
        var_v0 = 0xFF;
    } else {
        var_v0 = ~(1 << (*(u8 *)((u8 *)temp_v1_2 + 0x23D))) & 0xFF;
    }
    func_151C40BC((s32) arg0, 1.0f, 1.0f, 0.6f, 0.0f, 0xFFU, 0xFFU, (u8) var_v0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_129650/func_150FC8E8.s")
#endif
#ifdef NON_MATCHING
extern f32 D_800A2280, D_800A2284, D_800A2288, D_800A228C, D_800A2290, D_800A2294, D_800A2298, D_800A229C, D_800A22A0;
u8 *func_15164CF0(u8 *arg0, s32 arg1, u8 arg2, s32 arg3);

// effect27_spawn_with_screen_effect: starts an effect record of kind 0x27 (300 frames, func_15149130) whose 32-byte
// data (rec + 0x28) holds `obj` and its id (+0x3B), the flag `a`, `other`, its id (0xFF without one) and its player
// (+0x318 -> +0x23D, -1 without one) and the value `b`. When `other` has a player record, a kind-4 screen effect of
// 300 frames for that player is started too (func_15164CF0, scales 12 / 20 / 19 and the D_800A2280.. table); its record
// goes to data + 0x10. Called by the B-pad item action func_15065E18 and by func_15071278 (game_981E0).
void func_150FC438(struct127 *obj, struct127 *other, u8 a, u8 b) {
    struct {
        u8 kind;    // 0x00
        s8 u1;      // 0x01
        s8 u2;      // 0x02
        s16 time;   // 0x04
        u8 player;  // 0x06
        f32 f[12];  // 0x08
    } fx;
    struct {
        struct127 *obj;   // 0x00
        u8 objId;         // 0x04
        f32 f8;           // 0x08
        u8 uC;            // 0x0C
        u8 a;             // 0x0D
        s32 screen;       // 0x10: the screen effect record
        s16 u14;          // 0x14
        s8 player;        // 0x16
        struct127 *other; // 0x18
        u8 otherId;       // 0x1C
        u8 b;             // 0x1D
    } data;
    u8 *rec;
    u8 *pl;

    data.obj = obj;
    data.objId = ((u8 *) obj)[0x3B];
    data.f8 = 0.0f;
    data.uC = 0;
    data.a = a;
    data.screen = 0;
    data.u14 = 0;
    data.b = b;
    if (other != NULL && (pl = *(u8 **) ((u8 *) other + 0x318)) != NULL) {
        data.player = pl[0x23D];
    } else {
        data.player = -1;
    }
    data.other = other;
    data.otherId = (other != NULL) ? ((u8 *) other)[0x3B] : 0xFF;

    rec = (u8 *) func_15149130(0x12C, -1, 0x27, -1, 0, 0x25, (struct37 *) 0x20, 0xFF, 1);
    if (rec == NULL) {
        return;
    }
    memcpy(rec + 0x28, &data, 0x20);
    if (other == NULL || *(u8 **) ((u8 *) other + 0x318) == NULL) {
        return;
    }
    fx.kind = 4;
    fx.u1 = -1;
    fx.u2 = -1;
    fx.time = 0x12C;
    fx.player = (*(u8 **) ((u8 *) other + 0x318))[0x23D];
    fx.f[0] = 12.0f;
    fx.f[1] = 20.0f;
    fx.f[2] = 19.0f;
    fx.f[3] = D_800A2280;
    fx.f[4] = D_800A2284;
    fx.f[5] = D_800A2288;
    fx.f[6] = D_800A228C;
    fx.f[7] = D_800A2290;
    fx.f[8] = D_800A2294;
    fx.f[9] = D_800A2298;
    fx.f[10] = D_800A229C;
    fx.f[11] = D_800A22A0;
    *(u8 **) (rec + 0x28 + 0x10) = func_15164CF0((u8 *) &fx, 0, 0xFF, 1);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_129650/func_150FC438.s")
#endif

#ifdef NON_MATCHING
s32 func_150FBE40(u8 *, u8, f32, u8, s32, s32);

void func_150FCB94(u8 *arg0) {
    struct {
        s8 u50;
        u8 pad51[0x1];
        s16 u52;
        s8 u54;
        s8 u55;
        s8 u56;
    } sp;
    u8 *temp_s0;
    u8 *temp_s1;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_s1 = (*(u8 **)((u8 *)arg0 + 0x28));
    if (((*(s32 *)((u8 *)temp_s1 + 0)) == 0) || (temp_s0 = arg0 + 0x28, ((*(u8 *)((u8 *)temp_s1 + 4)) == 0xFF)) || ((*(u8 *)((u8 *)temp_s0 + 4)) != (*(u8 *)((u8 *)temp_s1 + 0x3B))) || (D_800C35EA == 1)) {
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
        return;
    }
    if ((*(u8 *)((u8 *)temp_s0 + 0x1D)) != (*(u16 *)((u8 *)temp_s1 + 0x84))) {
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
        return;
    }
    (*(f32 *)((u8 *)temp_s0 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 8)) - D_800BE9A4);
    if ((*(f32 *)((u8 *)temp_s0 + 8)) < 0.0f) {
        do {
            func_150FBE40(temp_s1, (*(u8 *)((u8 *)temp_s0 + 0xC)), -(*(f32 *)((u8 *)temp_s0 + 8)), (*(u8 *)((u8 *)temp_s0 + 0xD)), (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            temp_v1 = (*(u8 **)((u8 *)temp_s0 + 0x18));
            (*(u8 *)((u8 *)temp_s0 + 0xC)) = (u8) ((*(u8 *)((u8 *)temp_s0 + 0xC)) ^ 1);
            if (temp_v1 != NULL) {
                temp_v0 = (*(u8 **)((u8 *)temp_v1 + 0x31C));
                if (temp_v0 != NULL) {
                    (*(s16 *)((u8 *)temp_v0 + 0x1AA)) = (s16) ((*(s16 *)((u8 *)temp_v0 + 0x1AA)) + 1);
                }
            }
            (*(f32 *)((u8 *)temp_s0 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 8)) + (4.0f + (func_150ADA68() * 4.0f)));
        } while ((*(f32 *)((u8 *)temp_s0 + 8)) < 0.0f);
    }
    if ((*(s8 *)((u8 *)temp_s0 + 0x16)) != -1) {
        (*(s16 *)((u8 *)temp_s0 + 0x14)) = (s16) ((*(s16 *)((u8 *)temp_s0 + 0x14)) - D_800BE9E4);
        if ((*(s16 *)((u8 *)temp_s0 + 0x14)) < 0) {
            sp.u50 = 1;
            func_150ADA20();
            sp.u52 = 0x1E;
            sp.u55 = 1 << (*(s8 *)((u8 *)temp_s0 + 0x16));
            sp.u54 = (func_150ADA20() % 6U) + 3;
            sp.u56 = -1;
            func_151D8E18((structEU_151D8E18 *) &sp.u50, 0, (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            func_150ADA20();
            (*(s16 *)((u8 *)temp_s0 + 0x14)) = 0xFA;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_129650/func_150FCB94.s")
#endif
void func_150FCD98(struct102 *arg0, u8 *arg1, u8 arg2) {
    s32 new_var; // fakematch: permuter temp
    u8 *v = (u8 *)arg0 + 0x28;
    if (arg2 == 0) {
        s32 t = *(s32 *)arg1;
        if (t == (new_var = *(s32 *)v) || arg1[4] == v[4]) {
            func_1516972C(arg0);
        } else if (*(s32 *)(v + 0x18) != 0) {
            if (t == *(s32 *)(v + 0x18) || arg1[4] == v[0x1C]) {
                func_1516972C(arg0);
            }
        }
    } else if (arg2 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)v) {
            *(s32 *)v = *(s32 *)(arg1 + 4);
            v[4] = arg1[9];
        } else if (*(s32 *)(arg1 + 4) == *(s32 *)v) {
            *(s32 *)v = *(s32 *)arg1;
            v[4] = arg1[8];
        } else if (*(s32 *)(v + 0x18) != 0) {
            if (*(s32 *)arg1 == *(s32 *)(v + 0x18)) {
                *(s32 *)(v + 0x18) = *(s32 *)(arg1 + 4);
                v[0x1C] = arg1[9];
            } else if (*(s32 *)(arg1 + 4) == *(s32 *)(v + 0x18)) {
                *(s32 *)(v + 0x18) = *(s32 *)arg1;
                v[0x1C] = arg1[8];
            }
        }
    }
}

s32 func_150FCEB0(u8 *arg0, s32 arg1, s32 arg2) {
    switch (arg0[4]) {
        case 0x12:
        case 0x23:
        case 0x73:
        case 0x8A:
            return 0;
        default:
            return 1;
    }
}

void func_150FCEF4(u8 *arg0) {
    if (*(s32 *)(arg0 + 0x38) != 0) {
        func_1516972C(*(struct102 **)(arg0 + 0x38));
    }
}

void func_150FCF24(void *arg0) {
    func_150FCEF4(arg0);
    func_1514933C(arg0);
}

void func_150FCF50(void *arg0) {
    func_150FCEF4(arg0);
    func_15149368(arg0);
}
