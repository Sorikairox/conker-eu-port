#include "structs.h"
extern struct_eu_node *D_800DD280[][104];
extern u8 D_800A5B40[];
u8 *func_151CEBE4(s32 id) {
    u8 i;
    s32 group;
    u8 *node;

    for (i = 0; i < 2; i++) {
        for (group = 0; group < 2; group++) {
            for (node = (u8 *)D_800DD280[group][((s32 *)D_800A5B40)[i]]; node != NULL; node = *(u8 **)(node + 8)) {
                if (*(s32 *)(node + 0x20) == 11 && *(s32 *)(*(u8 **)(node + 0x98) + 0x48) == id) {
                    return node;
                }
            }
        }
    }
    return NULL;
}
