#include <ultra64.h>

#include "functions.h"
#include "variables.h"


s32 allocate_memory(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return func_10003C6C(arg0, arg1, arg2, 0, arg3);
}

#ifdef NON_MATCHING
/* P7: difftest EQUIV for valid inputs; DIFFER only when arg2 >= 5 (out-of-range alignment index: the asm reads its stack copy of the tables, this reads past the global). 24 seeds x 64 trials. Runtime check advised. */
/* heap allocator. Blocks are address-ordered (next/prev) and the free ones are also on a free list
 * (freeNext/freePrev, which overlap the data of an allocated block).
 * arg0 size, arg1 tag (top byte of info), arg2 alignment class (index into D_8002AF74/D_8002AF80; 2 = 16 bytes),
 * arg3 0: first fit from the free-list head (allocate at the bottom of the block) / 1: from the tail (allocate at the top),
 * arg4 0: out-of-memory is fatal / 1: may fail (and fails early when D_8002AC30 < 0x7800). Returns the data or 0. */
typedef struct HeapBlock {
    /* 0x00 */ struct HeapBlock *next;
    /* 0x04 */ struct HeapBlock *prev;
    /* 0x08 */ u32 info;                    /* tag << 24 | data size */
    /* 0x0C */ struct HeapBlock *freeNext;  /* the data starts here */
    /* 0x10 */ struct HeapBlock *freePrev;
} HeapBlock;
#define HEAP_HDR 0xC
#define HEAP_FREE_HEAD (*(HeapBlock **)&D_800380B8)
#define HEAP_FREE_TAIL (*(HeapBlock **)&D_8003841C)
#define HEAP_LAST      (*(HeapBlock **)&D_800380B4)
extern s16 D_8002AF74[5];   /* alignment: added to the data address */
extern s16 D_8002AF80[5];   /* alignment: mask */
extern struct54 *D_8003841C;
extern s32 D_80038420;      /* the last request (debug) */
extern s32 D_80038424;
extern s32 D_80038428;
extern s32 D_8003842C;
extern s32 D_80038430;
void func_150ADC50(void);
OSIntMask osSetIntMask(OSIntMask);   /* (repeated so difftest knows its arity) */

s32 func_10003C6C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 size = arg0;
    s32 alignAdd;
    s32 alignMask;
    u32 mask;
    HeapBlock *block;
    HeapBlock *newb;      /* the allocated block */
    HeapBlock *rest;      /* the block after it */
    HeapBlock *prev;
    HeapBlock *freeNext;
    HeapBlock *freePrev;
    HeapBlock *next;
    u32 restSize;
    u32 aligned;
    u32 end;

    D_80038420 = arg0;
    D_80038424 = arg1;
    D_80038428 = arg2;
    D_8003842C = arg3;
    D_80038430 = arg4;
    if (arg2 == 2) {
        size = (size + 15) & ~15;
    }
    if (size < 8) {
        size = 8;
    }
    size = (size + 3) & ~3;
    alignAdd = D_8002AF74[arg2];
    alignMask = D_8002AF80[arg2];
    if (arg4 == 1 && D_8002AC30 < 0x7800) {
        return 0;
    }
    mask = osSetIntMask(OS_IM_NONE);

    block = (arg3 == 0) ? HEAP_FREE_HEAD : HEAP_FREE_TAIL;
    for (;;) {
        if (block == NULL) {
            osSetIntMask(mask);
            if (arg4 == 0) {
                D_8003C8E0 = 0x0C000042;
                func_150ADC50();
            }
            return 0;
        }
        aligned = ((u32)block + alignAdd + HEAP_HDR) & alignMask;
        end = (u32)block + block->info + HEAP_HDR;
        if (end >= aligned + size) {
            break;
        }
        block = (arg3 == 0) ? block->freeNext : block->freePrev;
    }

    if (arg3 == 0) {
        newb = (HeapBlock *)(aligned - HEAP_HDR);
        rest = (HeapBlock *)((u32)newb + size + HEAP_HDR);
        restSize = ((u32)block + block->info) - ((u32)newb + size);
    } else {
        newb = (HeapBlock *)(((((u32)block + block->info) - size + HEAP_HDR) & alignMask) - HEAP_HDR);
        rest = block->next;
        restSize = (u32)newb - (u32)block;
    }
    prev = block->prev;
    freeNext = block->freeNext;
    freePrev = block->freePrev;

    if (arg3 == 0) {
        next = block->next;
        if (restSize >= 0x14) {
            /* split: the rest becomes a free block in place of this one */
            rest->next = next;
            rest->info = restSize - HEAP_HDR;
            if (next != NULL) {
                next->prev = rest;
            }
            restSize = 0;
            rest->freeNext = freeNext;
            rest->freePrev = freePrev;
            if (freeNext != NULL) {
                freeNext->freePrev = rest;
            } else {
                HEAP_FREE_TAIL = rest;
            }
            if (freePrev != NULL) {
                freePrev->freeNext = rest;
            } else {
                HEAP_FREE_HEAD = rest;
            }
        } else {
            /* take the whole block: unlink it from the free list */
            rest = next;
            if (freeNext != NULL) {
                freeNext->freePrev = freePrev;
            } else {
                HEAP_FREE_TAIL = freePrev;
            }
            if (freePrev != NULL) {
                freePrev->freeNext = freeNext;
            } else {
                HEAP_FREE_HEAD = freeNext;
            }
        }
        /* the alignment gap before the new block goes to the previous block */
        if (prev == NULL) {
            HEAP_LAST = newb;
        } else {
            prev->next = newb;
            prev->info = (prev->info & 0xFF000000) | ((u32)newb - (u32)prev - HEAP_HDR);
        }
        newb->next = rest;
        newb->prev = prev;
        newb->info = (arg1 << 24) | (restSize + size);
        if (rest != NULL) {
            rest->prev = newb;
        }
    } else if (restSize >= 0x14) {
        /* split: the new block is cut from the top; the bottom stays free */
        next = block->next;
        newb->prev = block;
        newb->next = next;
        newb->info = (arg1 << 24) | (end - (u32)newb - HEAP_HDR);
        if (newb->next != NULL) {
            newb->next->prev = newb;
        }
        block->next = newb;
        block->info = restSize - HEAP_HDR;
    } else {
        /* take the whole block, aligned from its bottom */
        newb = (HeapBlock *)((((u32)block + alignAdd + HEAP_HDR) & alignMask) - HEAP_HDR);
        newb->next = rest;
        newb->prev = prev;
        newb->info = (arg1 << 24) | (end - (u32)newb - HEAP_HDR);
        if (freeNext != NULL) {
            freeNext->freePrev = freePrev;
        } else {
            HEAP_FREE_TAIL = freePrev;
        }
        if (freePrev != NULL) {
            freePrev->freeNext = freeNext;
        } else {
            HEAP_FREE_HEAD = freeNext;
        }
        if (prev == NULL) {
            HEAP_LAST = newb;
        } else {
            prev->next = newb;
            prev->info = (prev->info & 0xFF000000) | ((u32)newb - (u32)prev - HEAP_HDR);
        }
        if (newb->next != NULL) {
            newb->next->prev = newb;
        }
        if (newb->prev != NULL) {
            newb->prev->next = newb;
        }
    }
    if (block == (HeapBlock *)D_800380B0) {
        func_1000440C();
    }
    osSetIntMask(mask);
    return (s32)newb + HEAP_HDR;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/init_3C40/func_10003C6C.s")
#endif
#ifdef NON_MATCHING
extern struct54 *D_8003841C;

void func_10004074(s32 arg0) {
    struct54 *sp2C;
    s32 sp20;
    u32 sp1C;
    struct54 *sp18;
    s32 temp_t8;
    s32 temp_v0_2;
    s32 temp_v1_2;
    s32 var_a3;
    struct54 *temp_a0;
    struct54 *temp_a0_2;
    struct54 *temp_t3;
    struct54 *temp_t7;
    struct54 *temp_v1;
    struct54 *var_a1;
    struct54 *var_v1;
    u32 temp_v0;
    u32 temp_v0_3;

    temp_v1 = arg0 - 0xC;
    if (arg0 != 0) {
        sp18 = temp_v1;
        sp2C = temp_v1;
        sp20 = 0;
        sp1C = osSetIntMask(1U);
        var_a1 = sp2C;
        temp_a0 = sp18->unk4;
        var_a3 = sp20;
        (*(s8 *)((u8 *)sp18 + 8)) = 0;
        if (temp_a0 != NULL) {
            temp_v0 = temp_a0->unk8;
            if ((temp_v0 >> 0x18) == 0) {
                temp_t7 = sp18->unk0;
                var_a1 = temp_a0;
                var_a3 = 1;
                temp_a0->unk0 = temp_t7;
                temp_a0->unk8 = temp_v0 + sp18->unk8 + 0xC;
                if (temp_t7 != NULL) {
                    temp_t7->unk4 = temp_a0;
                }
            }
        }
        temp_a0_2 = var_a1->unk0;
        if ((temp_a0_2 != NULL) && (((u32) temp_a0_2->unk8 >> 0x18) == 0)) {
            temp_t3 = temp_a0_2->unk0;
            var_a1->unk0 = temp_t3;
            var_a3 = 1;
            var_a1->unk8 = var_a1->unk8 + temp_a0_2->unk8 + 0xC;
            if (temp_t3 != NULL) {
                temp_t3->unk4 = var_a1;
            }
            temp_t8 = temp_a0_2->unkC;
            var_a1->unkC = temp_t8;
            if (temp_t8 != 0) {
                (*(struct54 **)((u8 *)temp_t8 + 0x10)) = var_a1;
            }
            temp_v1_2 = temp_a0_2->unk10;
            if (temp_v1_2 == 0) {
                D_800380B8 = var_a1;
                var_a1->unk10 = 0;
            } else if (temp_v1_2 != (s32)var_a1) {
                var_a1->unk10 = temp_v1_2;
                if (temp_v1_2 != 0) {
                    (*(struct54 **)((u8 *)temp_v1_2 + 0xC)) = var_a1;
                }
            }
        }
        if (var_a3 == 0) {
            var_v1 = D_800380B8;
            if (var_v1 == NULL) {
                var_a1->unkC = 0;
                var_a1->unk10 = 0;
                D_800380B8 = var_a1;
            } else if ((u32) var_a1 < (u32) var_v1) {
                var_a1->unkC = (s32) var_v1;
                var_a1->unk10 = 0;
                var_v1->unk10 = (s32) var_a1;
                D_800380B8 = var_a1;
            } else {
loop_21:
                temp_v0_2 = var_v1->unkC;
                if (temp_v0_2 == 0) {
                    var_a1->unkC = 0;
                    var_a1->unk10 = (s32) var_v1;
                    var_v1->unkC = (s32) var_a1;
                } else if ((u32) var_a1 < (u32) temp_v0_2) {
                    var_a1->unkC = temp_v0_2;
                    var_a1->unk10 = (s32) var_v1;
                    (*(struct54 **)((u8 *)temp_v0_2 + 0x10)) = var_a1;
                    var_v1->unkC = (s32) var_a1;
                } else {
                    var_v1 = (struct54 *) temp_v0_2;
                    goto loop_21;
                }
            }
        }
        if (var_a1->unkC == 0) {
            D_8003841C = var_a1;
        }
        temp_v0_3 = var_a1->unk8;
        if ((u32) D_8002AC30 < temp_v0_3) {
            D_8002AC30 = (s32) temp_v0_3;
            D_800380B0 = var_a1;
        }
        osSetIntMask(sp1C);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/init_3C40/func_10004074.s")
#endif
void func_10004250(void) {
    s32 temp_v0;
    u32 temp_v1;
    OSIntMask mask;
    struct54 *phi_s0;

    mask = osSetIntMask(1);

    if (phi_s0 = D_800380B4) {
        do {
            temp_v1 = phi_s0->unk8;
            temp_v0 = temp_v1 >> 0x18;
            if (2 == temp_v0) {
                func_10004074(&phi_s0->unkC);
            } else if ((temp_v0 == 3) || (temp_v0 == 4)) {
                phi_s0->unk8 = ((temp_v0 - 1) << 0x18) | (temp_v1 & 0xFFFFFF);
            }
        } while(phi_s0 = phi_s0->unk0);
    }
    osSetIntMask(mask);
}

void func_10004308(void) {
    u32 temp_t6;
    struct54 *phi_s0;
    OSIntMask mask;

    mask = osSetIntMask(1);
    phi_s0 = D_800380B4;
    func_15042D50();

    if (phi_s0) {
        do {
            temp_t6 = phi_s0->unk8 >> 24;
            if (temp_t6 == 1 || temp_t6 == 2 || temp_t6 == 3 || temp_t6 == 4) {
                func_10004074(&phi_s0->unkC);
            }
        }
        while (phi_s0 = phi_s0->unk0);
    }
    osSetIntMask(mask);
}

typedef struct { s32 a; s32 b; u32 c; } Hdr43B4; /* 12-byte header before the block */

void func_100043B4(s32 *arg0, u32 arg1) {
    Hdr43B4 *h = (Hdr43B4 *)arg0 - 1;
    u32 mask = osSetIntMask(1);

    h->c = (h->c & 0xFFFFFF) | (arg1 << 24);
    osSetIntMask(mask);
}
// NON-MATCHING: missing an addiu
// void func_100043B4(s32 *arg0, u32 arg1) {
//     OSIntMask mask = osSetIntMask(1);
//     *(arg0 - 1) = (arg1 << 24) | *(arg0 - 1) & 0xFFFFFF;
//     osSetIntMask(mask);
// }

void func_1000440C(void) {
    struct54 *foo;
    struct54 *last_good_foo;
    s32 tmp0;

    for (foo = D_800380B8, tmp0 = NULL; foo != NULL; foo = (struct54 *)foo->unkC) {
        if (tmp0 < (s32) foo->unk8) {
            tmp0 = foo->unk8;
            last_good_foo = foo;
        }
    }

    D_800380B0 = last_good_foo;
    D_8002AC30 = tmp0;
}
