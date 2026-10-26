#include <ultra64.h>
#include "functions.h"
#include "variables.h"


Gfx *allocate_memory(s32, s32, s32, s32);
extern s32 g_dl_capacity; /* was D_800BEFC4 */

/* two display-list buffers of N Gfx each (N = the u16 at +0x1C of g_level_header, default 8000, plus 400) */
/* was func_15015E30 */
void gfx_alloc_dl_buffers(void) {
    u16 *count = (u16 *)((u8 *)g_level_header + 0x1C);
    Gfx **bufs = (Gfx **)&D_800BEDE8;
    Gfx *b;

    if (*count == 0) {
        *count = 8000;
    }
    *count += 400;
    count = (u16 *)((u8 *)g_level_header + 0x1C);
    bufs[0] = allocate_memory(*count * sizeof(Gfx), 0xFF, 2, 0);
    count = (u16 *)((u8 *)g_level_header + 0x1C);   /* reloaded: the call may move it */
    b = allocate_memory(*count * sizeof(Gfx), 0xFF, 2, 0);
    bufs[1] = b;
    g_dl_capacity = (((u8 *)b - (u8 *)bufs[0]) >> 3) - 400;
}