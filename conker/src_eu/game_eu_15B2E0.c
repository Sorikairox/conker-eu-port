#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x00 */ u8 pad0[0xA8];
    /* 0xA8 */ s32 unkA8;
    /* 0xAC */ s32 unkAC;
} struct_eu_15B2E0; // size 0xB0

extern struct_eu_15B2E0 *D_800DC6E0;


#ifdef NON_MATCHING
/* camera_queue_event: appends event (type, data) to camera cam's event queue D_800DC6E0[cam +0x23D]: 20 slots of
 * { s32 type; void *data; } at +0x00, write index +0xAC (wraps at 20; the read index +0xA8 is func_1512DB74's).
 * The camera event pump func_15129220 drains it. Nothing checks for a full queue (as in the asm). */
void func_1512DAD0(u8 *cam, s32 type, void *data) {
    struct_eu_15B2E0 *q = &D_800DC6E0[cam[0x23D]];
    s32 *slot = (s32 *) ((u8 *) q + q->unkAC * 8);

    slot[0] = type;
    *(void **) (slot + 1) = data;
    q->unkAC++;
    if (q->unkAC == 20) {
        q->unkAC = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15B2E0/func_1512DAD0.s")
#endif

#ifdef NON_MATCHING
u8 *func_1512DB74(u8 *arg0) {
    s32 temp_a1;
    struct_eu_15B2E0 *temp_v0;
    struct_eu_15B2E0 *temp_v0_2;

    temp_v0 = &D_800DC6E0[(*(u8 *)((u8 *)arg0 + 0x23D))];
    temp_a1 = temp_v0->unkA8;
    temp_v0->unkA8 = temp_a1 + 1;
    temp_v0_2 = &D_800DC6E0[(*(u8 *)((u8 *)arg0 + 0x23D))];
    if (temp_v0_2->unkA8 == 0x14) {
        temp_v0_2->unkA8 = 0;
    }
    return ((struct_eu_15B2E0 *)((u8 *)temp_v0 + (temp_a1 * 8)));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15B2E0/func_1512DB74.s")
#endif
void func_1512DBDC(u8 *arg0) {
    D_800DC6E0[arg0[0x23D]].unkA8 = 0;
    D_800DC6E0[arg0[0x23D]].unkAC = 0;
}

s32 func_1512DC20(u8 *arg0) {
    return D_800DC6E0[arg0[0x23D]].unkA8 == D_800DC6E0[arg0[0x23D]].unkAC;
}
