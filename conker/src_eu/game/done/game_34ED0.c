#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15007A20 */
void game_bss_clear(void) {
    // zero out bss (?)
    bzero(&g_collision_buf_cursor, (s32)&g_cheat_flags - (s32)&g_collision_buf_cursor);
    // zero out (?)
    bzero(&g_audio_heap_arena, 0x3E000); // 253952 bytes
}
