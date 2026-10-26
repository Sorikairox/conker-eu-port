#include <ultra64.h>

#include "functions.h"
#include "variables.h"

/* was func_10003930 */
void mem_init_region_bounds(void) {
    if (g_mem_expansion_pak) {
        g_mem_rdp_fifo_start = 0x807F5000;
        g_mem_rdp_fifo_end = 0x807FE000;
        g_mem_scratch_area = 0x807FE000;
        g_mem_heap_end = 0x807F5000;
    } else {
        g_mem_rdp_fifo_start = 0x803F5000;
        g_mem_rdp_fifo_end = 0x803FE000;
        g_mem_scratch_area = 0x803FE000;
        g_mem_heap_end = 0x803F5000;
    }
}
