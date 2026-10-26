#include <ultra64.h>

#include "functions.h"
#include "variables.h"


extern struct54 *g_heap_free_tail; /* was D_8003841C */

// heap init: one free block spanning g_heap_start .. g_mem_heap_end
/* was func_10003BD0 */
void heap_init(void) {
    g_heap_head = &g_heap_start;
    g_heap_head->unk0 = NULL;
    g_heap_head->unk4 = NULL;
    g_heap_head->unk8 = g_mem_heap_end - (u32)&g_heap_start - 0x14;
    g_heap_head->unkC = 0;
    g_heap_head->unk10 = 0;
    g_heap_free_head = g_heap_free_tail = g_heap_head;
    g_heap_largest_block = g_heap_head;
}
