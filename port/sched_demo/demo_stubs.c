/* The scheduler demo links the PC libultra layer without the game: weak empty versions of the
 * generated memory-model tables (port/stubs/n64mem_*) so pc_mem.c and port/gfx link. */
#include "../ultra/pc_mem.h"
__attribute__((weak)) unsigned char n64_rdram[0x800000];
__attribute__((weak)) unsigned char n64_seg16[0x10000];
__attribute__((weak)) const unsigned port_reloc_count, port_functab_count, port_cdata_count;
__attribute__((weak)) const unsigned port_reloc[1];
__attribute__((weak)) const PortFn port_functab[1];
__attribute__((weak)) const PortCData port_cdata[1];
/* P357 the input recorder's game state (port/ultra/pc_net.c section 5) */
__attribute__((weak)) unsigned char g_objects[26 * 0x32C];
__attribute__((weak)) unsigned char g_game_mode;
__attribute__((weak)) int g_level_id, g_world_obj_count;
__attribute__((weak)) long long g_random_seed;
