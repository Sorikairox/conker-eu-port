#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_151927C0 */
void sprite_node_init_fade(u8 *arg0) {
    s16 y;
    y = (*(s32 *)(arg0 + 0x14) & 0xFF) >> 1;
    *(s16 *)(arg0 + 0x38) = 0x12C;
    *(s8 *)(arg0 + 0x3A) = 0xA;
    *(s32 *)(arg0 + 0x14) = (y << 16) + y;
    *(s8 *)(arg0 + 0x3B) = 0;
}
// JUSTREG: using t2 not t3
// void sprite_node_init_fade(struct114 *arg0) {
//     s32 tmp0;
//     tmp0 = (s16)((arg0->unk14 & 0xFF) >> 1);
//     arg0->unk38 = 300;
//     arg0->unk3A = 10;
//     arg0->unk14 = tmp0 * 65537;
//     arg0->unk3B = 0;
// }
