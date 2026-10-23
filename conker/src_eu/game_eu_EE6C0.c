#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_150C0F48(void *);


void func_150C0EB0(u8 *arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, (s32)(arg0 + 0x20), (s32)(arg0 + 0x24), (s32)arg0);
}

void func_150C0EF0(void *arg0) {
    func_150C0F48(arg0);
    func_15169804(arg0);
}

void func_150C0F1C(void *arg0) {
    func_150C0F48(arg0);
    func_15169824(arg0);
}

void func_150C0F48(void *arg0) {
    s16 var_s0;
    s32 temp_s2;
    var_s0 = (*(s16 *)((u8 *)arg0 + 0x44));
    if (var_s0 != -1) {
        do {
            temp_s2 = var_s0 * 8;
            func_1516972C(*(void **)((*(u8 **)((u8 *)arg0 + 0x40)) + temp_s2));
            var_s0 = (*(s16 *)((u8 *)(*(u8 **)((u8 *)arg0 + 0x40)) + temp_s2 + 4));
        } while (var_s0 != -1);
    }
}

#ifdef NON_MATCHING
void * memcpy(void *, const void *, s32);

u8 *func_150C0FC0(u8 *arg0, u8 arg1, s32 arg2) {
    u8 *temp_v0_4;
    u8 *temp_v0_3;
    u8 *temp_v0;
    s32 *temp_v0_2;
    s16 var_v1;
    s16 temp_v0_5;
    s32 sp28;
    u8 *sp2C;

    sp28 = ((*(s16 *)((u8 *)arg0 + 0x14)) * 8) + 0x48;
    if (!((*(u8 *)((u8 *)arg0 + 0x18)) & 2)) {
        temp_v0_2 = (*(s32 **)((u8 *)arg0 + 8));
        if (temp_v0_2 == NULL) {
            return NULL;
        }
        if (*temp_v0_2 == 0) {
            return NULL;
        }
        goto block_5;
    }
block_5:
    temp_v0 = func_15167A68(0x25, arg2, sp28, 1, (u8) (s32) arg1, 1U);
    if (temp_v0 == NULL) {
        return NULL;
    }
    sp2C = temp_v0;
    memcpy(temp_v0 + 0x18, arg0, 0x1C);
    (*(u8 **)((u8 *)temp_v0 + 0x40)) = (u8 *) (temp_v0 + 0x48);
    if ((*(u8 *)((u8 *)arg0 + 0x18)) & 2) {
        temp_v0_3 = (*(u8 **)((u8 *)temp_v0 + 0x18));
        (*(f32 *)((u8 *)temp_v0 + 0x34)) = (f32) (*(f32 *)((u8 *)temp_v0_3 + 0));
        (*(f32 *)((u8 *)temp_v0 + 0x38)) = (f32) (*(f32 *)((u8 *)temp_v0_3 + 8));
    } else {
        temp_v0_4 = (*(u8 **)((u8 *)temp_v0 + 0x20));
        (*(f32 *)((u8 *)temp_v0 + 0x34)) = (f32) (*(f32 *)((u8 *)temp_v0_4 + 0x14));
        (*(f32 *)((u8 *)temp_v0 + 0x38)) = (f32) (*(f32 *)((u8 *)temp_v0_4 + 0x1C));
    }
    (*(f32 *)((u8 *)temp_v0 + 0x3C)) = 0.0f;
    (*(s16 *)((u8 *)temp_v0 + 0x44)) = -1;
    (*(s16 *)((u8 *)temp_v0 + 0x46)) = 0;
    var_v1 = 0;
    if (((*(s16 *)((u8 *)arg0 + 0x14)) - 1) > 0) {
        do {
            temp_v0_5 = var_v1 + 1;
            (*(s16 *)((u8 *)(((*(u8 **)((u8 *)temp_v0 + 0x40)) + (var_v1 * 8))) + 4)) = temp_v0_5;
            var_v1 = temp_v0_5;
        } while (temp_v0_5 < ((*(s16 *)((u8 *)arg0 + 0x14)) - 1));
    }
    (*(s16 *)((u8 *)(((*(u8 **)((u8 *)temp_v0 + 0x40)) + ((*(s16 *)((u8 *)arg0 + 0x14)) * 8))) + -4)) = -1;
    (*(s32 *)((u8 *)temp_v0 + 0x10)) = 1;
    (*(s32 *)((u8 *)temp_v0 + 0x14)) = 0;
    return temp_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EE6C0/func_150C0FC0.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EE6C0/func_150C1138.s")

#ifdef NON_MATCHING
/*
 * pool_slot_release: particle death handler 0 (D_80089BA0, called by func_1513095C before the free). The owner
 * at +0xA8 keeps 8-byte slots at +0x40 (object pointer, s16 next) in a used list (head +0x44) and a free list
 * (head +0x46); the slot holding this particle is unlinked from the used list and pushed on the free list.
 */
void func_150C1698(u8 *arg0) {
    u8 *pool = *(u8 **)(arg0 + 0xA8);
    s16 head = *(s16 *)(pool + 0x44);
    s16 prev = -1;
    s16 cur = head;
    s32 found = FALSE;
    u8 *slots;
    u8 *e;

    if (cur != -1) {
        slots = *(u8 **)(pool + 0x40);
        do {
            e = slots + cur * 8;
            if (*(u8 **)e == arg0) {
                found = TRUE;
            } else {
                prev = cur;
                cur = *(s16 *)(e + 4);
            }
        } while (cur != -1 && !found);
    }
    if (found) {
        e = *(u8 **)(pool + 0x40) + cur * 8;
        if (cur == head) {
            *(s16 *)(pool + 0x44) = *(s16 *)(e + 4);
        } else {
            *(s16 *)(*(u8 **)(pool + 0x40) + prev * 8 + 4) = *(s16 *)(e + 4);
            e = *(u8 **)(pool + 0x40) + cur * 8;
        }
        *(s16 *)(e + 4) = *(s16 *)(pool + 0x46);
        *(s16 *)(pool + 0x46) = cur;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EE6C0/func_150C1698.s")
#endif
