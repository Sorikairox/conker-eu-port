#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/func_10005DA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/func_10005B04.s")

#ifdef NON_MATCHING
extern s16 D_8003C218;
extern u8 *D_8003C21C;

/* fill the bitmap [D_8003BE70, D_8003C21C] with 0xFF, then mask the bits past the end in the last byte */
void func_10005BE0(void) {
    u8 *p = (u8 *)D_8003BE70;
    s32 n;

    do {
        *p = 0xFF;
    } while (p++ != D_8003C21C);
    n = D_8003C218 & 7;
    if (n != 0) {
        *D_8003C21C = (2 << (n - 1)) - 1;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/func_10005BE0.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/func_10005F1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/func_100061F8.s")

#ifdef NON_MATCHING
/* thin wrapper: a0..a2 pass through untouched, v0 comes back from func_1000654C */
s32 func_1000654C();

s32 func_10006530(s32 arg0, s32 arg1, u32 arg2) {
    return func_1000654C(arg0, arg1, arg2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/func_10006530.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/func_1000654C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/func_1000661C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/func_10006670.s")

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/func_10006714.s")

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/func_10006B18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/func_10006C1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/func_10006C5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/func_100070F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/func_1000738C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/__osExceptionPreamble.s")

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/func_10007AA8.s")

#ifdef NON_MATCHING
void func_10007CC8(s32 *arg0, s32 *arg1) {
    s32 *var_t8;
    s32 *var_t9;
    s32 temp_t7;

    var_t9 = arg0;
    var_t8 = *arg0;
    temp_t7 = (*(s32 *)((u8 *)arg1 + 4));
    if ((*(s32 *)((u8 *)var_t8 + 4)) >= temp_t7) {
        do {
            var_t9 = var_t8;
            var_t8 = *var_t8;
        } while ((*(s32 *)((u8 *)var_t8 + 4)) >= temp_t7);
    }
    (*(s32 **)((u8 *)arg1 + 0)) = *var_t9;
    *var_t9 = arg1;
    (*(s32 **)((u8 *)arg1 + 8)) = arg0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/func_10007CC8.s")
#endif
#ifdef NON_MATCHING
/* __osPopThread: unlink and return the head of a thread queue */
OSThread *func_10007D14(OSThread **queue) {
    OSThread *t = *queue;

    *queue = t->next;
    return t;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/func_10007D14.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/func_10007D28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/__osCleanupThread.s")

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/func_10007F64.s")

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/func_10007FB4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/func_10008018.s")

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/func_10008090.s")

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_5DA0/func_1000809C.s")
