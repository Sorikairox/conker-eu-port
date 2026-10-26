#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15004E00 */
void breakable_slots_clear(void) {
    u32 i;

    for (i = 0; i < 25; i++)
    {
        D_800C6660[i].unk0 = 0;
        D_800C6660[i].unk4 = 0;
        D_800C6660[i].unk8 = 0;
        D_800C6660[i].unkF = 0;
    }
}

/* was func_15004E80 */
void level_matrix_arenas_alloc(void) {
    g_matrix_arena_count = g_level_header->unk1A;
    D_800C3E80 = allocate_memory(g_matrix_arena_count << 6, 1, 3, 0);
    g_matrix_arena_b = allocate_memory(g_matrix_arena_count << 6, 1, 3, 0);
}
