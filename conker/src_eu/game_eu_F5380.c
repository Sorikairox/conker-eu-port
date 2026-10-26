#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 g_fx_parent_alpha_k_0890; /* was D_800A0890 */
/* was func_150C7B70 */
s32 fx_alpha_from_parent_rec(u8 *arg0) {
    f32 t = (u32)(*(u8 **)(*(u8 **)(arg0 + 0x170) + 0x14))[0x2F];
    arg0[0x70] = t * g_fx_parent_alpha_k_0890;
    if (!arg0 && !arg0 && !arg0) { // fakematch: permuter; gives the early `li v0,1` and the unfilled `sb; nop; jr ra; nop` tail
    }
    return 1;
}

/* was func_150C7C3C */
s32 fx_copy_default_mtx(void *arg0, s32 arg1) {
    memcpy(arg0, &g_identity_mtx, 0x40);
    return 1;
}
