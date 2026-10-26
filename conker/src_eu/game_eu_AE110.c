#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
// context_action_set: offers the context action `action` to the player obj (live, +0x127 != 0xFF) for slot 0 (B
// button, player +0x31C byte +0x74) or slot != 0 (+0x75, with +0x7A = the D_800D34B8 hotspot index of target, 0x34-byte
// entries); a slot whose bit 7 is set is locked. Actions 0x2B / 0x2C remember the hotspot in D_800D1DBC and show as
// 0x2A; other actions known to func_15080B38 are recorded in D_800D1940 and show as 0x1A until their D_800D2E60 bit is
// set (first use). arg4 is not used (P195).
s32 func_15080B38(s32 arg0);
extern u8 *D_800D1DBC;

void func_15080900(struct127 *obj, u8 *target, s32 slot, s32 action, s32 arg4) {
    u8 *ctl;

    if (obj == NULL || *(s32 *) obj == 0 || ((u8 *) obj)[0x127] == 0xFF) {
        return;
    }
    if (action == 0x2B || action == 0x2C) {
        D_800D1940 = action;
        D_800D1DBC = target;
        action = 0x2A;
    } else if (func_15080B38(action) != 0) {
        D_800D1940 = action;
        if (!(D_800D2E60[action >> 3] & (1 << (action & 7)))) {
            action = 0x1A;
        }
    }
    ctl = *(u8 **) ((u8 *) obj + 0x31C);
    if (slot == 0) {
        if (!(ctl[0x74] & 0x80)) {
            ctl[0x74] = action;
        }
    } else if (!(ctl[0x75] & 0x80)) {
        ctl[0x75] = action;
        (*(u8 **) ((u8 *) obj + 0x31C))[0x7A] = (target - D_800D34B8) / 0x34;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AE110/func_15080900.s")
#endif

void func_15080A20(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg2 != 0) {
        arg2 |= 0x80;
    }
    if (arg1 == 0) {
        (*(u8 **)((u8 *)&D_800CCA0C + arg0 * 0x32C))[0x74] = arg2;
        return;
    }
    (*(u8 **)((u8 *)&D_800CCA0C + arg0 * 0x32C))[0x75] = arg2;
}

void func_15080AA8(s32 arg0) {
    struct127 *p;
    u8 b;
    p = &D_800CC2D0[arg0];
    if ((p->unk31C->pad6C[8] != 0) && (!(p->unk31C->pad6C[8] & 0x80))) {
        p->unk31C->pad6C[8] = 0;
    }
    b = p->unk31C->unk75;
    if ((b != 0) && (!(b & 0x80))) {
        p->unk31C->unk75 = 0;
    }
}

void func_15080B18(s32 arg0, s32 *arg1, s32 *arg2) {
    *arg2 = 1 << (arg0 & 7);
    *arg1 = arg0 >> 3;
}

s32 func_15080B38(s32 arg0) {
    s32 sp1C;
    s32 sp18;

    func_15080B18(arg0, &sp1C, &sp18);
    if (D_eu_800BE9A0[sp1C] & sp18) {
        return 1;
    }
    return 0;
}

void func_15080B84(void) {
    u16 new_var; // fakematch: permuter temp
    u16 *q;
    u16 temp_a0;
    q = (u16 *) D_800D1998;
    if (q != 0) {
        if (((unsigned short) D_800D1994) != D_800D1995) {
            temp_a0 = q[D_800D1994];
            new_var = temp_a0; // fakematch
            if (0 != temp_a0) {
                func_1001263C((s32) new_var, 0x7FFF, 0x40);
            }
            D_800D1994++;
        }
    }
}

void func_15080BF4(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 == 0x20) {
        func_15080B84();
    }
}

#ifdef NON_MATCHING
s32 allocate_memory(s32, s32, s32, s32);
s32 asset_load_with_subfiles(s32, s32, s32, s32, s32, s32, s32);
s32 func_1516AD20(s32, s32, s32, void (*)(s32, s32, s32), s32 *, s32);
s32 strlen(u8 *);
extern u8 D_800BEECB;
extern u8 D_800D3260;

void func_15080C28(s32 arg0) {
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 sp30;
    u32 sp2C;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v1;
    s32 var_t3;
    u32 temp_t6;

    if (arg0 == 0) {
        if (!(D_800D2E68 & 0x10)) {
            sp40 = 1;
        } else {
            goto block_4;
        }
    } else {
block_4:
        sp40 = 0;
    }
    temp_v0 = asset_load_with_subfiles(0, 0, 0, 3, 0x1A, (s32) D_800BEECB, (s32) D_800D1940);
    D_800D1944 = temp_v0;
    if (temp_v0 != 0) {
        D_800D1994 = 0;
        D_800D1998 = (*(s32 *)((u8 *)temp_v0 + 8));
        D_800D1995 = (u8) ((u32) (*(u32 *)((u8 *)temp_v0 + 0xC)) >> 1);
        if (sp40 != 0) {
            temp_v0_2 = asset_load_with_subfiles(0, 0, 0, 3, 0x1A, (s32) D_800BEECB, 0x43);
            D_800D1948 = temp_v0_2;
            if (D_800D1944 != 0) {
                sp3C = strlen(*(s32 *)temp_v0_2) + 1;
                temp_v0_3 = strlen((*(u8 **)((u8 *)D_800D1944 + 0)));
                sp38 = temp_v0_3 + 1;
                temp_v0_4 = allocate_memory(sp3C + temp_v0_3 + 2, 1, 0, 0);
                D_800D194C = temp_v0_4;
                bcopy((*(u8 **)((u8 *)D_800D1948 + 0)), (u8 *) temp_v0_4, sp3C);
                (*(s8 *)((u8 *)((D_800D194C + sp3C)) + -1)) = 0xBD;
                bcopy((*(u8 **)((u8 *)D_800D1944 + 0)), D_800D194C + sp3C, sp38);
                temp_t6 = (u32) (*(u32 *)((u8 *)D_800D1948 + 0xC)) >> 1;
                temp_v1 = D_800D1995 + temp_t6;
                sp30 = temp_v1;
                sp2C = temp_t6;
                temp_v0_5 = allocate_memory(temp_v1 * 2, 1, 0, 0);
                D_800D1998 = temp_v0_5;
                bcopy((*(u8 **)((u8 *)D_800D1948 + 8)), (u8 *) temp_v0_5, sp2C * 2);
                bcopy((*(u8 **)((u8 *)D_800D1944 + 8)), (temp_t6 * 2) + D_800D1998, D_800D1995 * 2);
                D_800D1995 = (u8) sp30;
                goto block_10;
            }
        } else {
            D_800D1948 = 0;
block_10:
            D_800D1941 = 1;
            if (sp40 != 0) {
                var_t3 = D_800D194C;
            } else {
                var_t3 = (s32) (*(u8 **)((u8 *)D_800D1944 + 0));
            }
            (*(s32 *)((u8 *)D_800D1958 + 0)) = 0x38013;
            if (((sp40 != 0) || (arg0 != 0) || !(D_800D2E60[(s32) D_800D1940 >> 3] & (1 << (D_800D1940 & 7)))) && (D_800D3260 == 0)) {
                (*(s32 *)((u8 *)D_800D1958 + 0)) |= 0x60;
            }
            if ((arg0 != 0) || (D_800D1940 == 0x42)) {
                (*(s32 *)((u8 *)D_800D1958 + 0)) |= 0x80;
            }
            D_800D1958[1] = var_t3;
            (*(s16 *)((u8 *)D_800D1958 + 0x26)) = 0x64;
            (*(s8 *)((u8 *)D_800D1958 + 8)) = 1;
            (*(s16 *)((u8 *)D_800D1958 + 0x24)) = 0;
            (*(s8 *)((u8 *)D_800D1958 + 0x2B)) = 0;
            D_800D1958[6] = (s32) &D_800D1988;
            D_800D1958[7] = (s32) &D_800D198C;
            D_800D1958[8] = (s32) &D_800D1990;
            (*(s8 *)((u8 *)D_800D1958 + 0x28)) = 0xFF;
            (*(s8 *)((u8 *)D_800D1958 + 0x29)) = 0xFF;
            (*(s8 *)((u8 *)D_800D1958 + 0x2A)) = 0xFF;
            D_800D1988 = 78.0f;
            D_800D198C = 48.0f;
            D_800D1990 = 9.0f;
            temp_v0_6 = func_1516AD20(0, 0, 0, func_15080BF4, D_800D1958, 0);
            D_800D1950 = temp_v0_6;
            (*(s8 *)((u8 *)temp_v0_6 + 0x14)) = 0;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AE110/func_15080C28.s")
#endif
#ifdef NON_MATCHING // the definition is void (asm: v0 is not a result); one signature for wasm
void func_10004074(s32);
#else
s32 func_10004074(s32);
#endif
void func_1516D850(s32);
void func_151F2D6C(s32, s32);

void func_15080FE8(void) {
    s32 r;
    D_800D1941 = 0;
    func_1516D850(D_800D1950);
    func_10004074(D_800D1944);
    if (D_800D1948 != 0) {
        r = D_800D1948;
        func_10004074(r);
        func_10004074(D_800D194C);
        func_10004074(D_800D1998);
        D_800D1948 = 0;
    }
    func_151F2D6C(0, 0x5622);
}

extern u8 *D_800D1DBC;

void func_15081064(void) {
    if ((D_800D1941 != 0) && ((*(u8 *)((u8 *)D_800D1950 + 0x15)) == 0)) {
        func_15080FE8();
        if ((D_800BE9F0 != 0x29) && (D_800BE9F0 != 0x2E)) {
            (*(u8 *)((u8 *)D_800D2E60 + 8)) = (u8) ((*(u8 *)((u8 *)D_800D2E60 + 8)) | 0x10);
        }
        if (D_800D1DBC != NULL) {
            (*(s8 *)((u8 *)D_800D1DBC + 0x14)) = 1;
            D_800D1DBC = NULL;
        }
    }
}

s32 func_150810F4(void) {
    if (D_800D1941 == 0) {
        return 1;
    }
    return 0;
}
