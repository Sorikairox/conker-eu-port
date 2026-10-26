#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#include "macros.h"

void __osInitialize_common(void);

/* was func_10001050 */
void boot_entry_main(void) {
    bzero(&g_boot_idle_stack_alias, (s32) &g_frame_counter_block_alias - (s32) &g_boot_idle_stack_alias); // zero out bss
    tlb_clear_entries(1, 31);
    __osInitialize_common(); // EU: libultra osInitialize() macro
    __osSetSR(__osGetSR() | SR_CU1 | SR_FR);
    __osSetFpcCsr(FPCSR_FS);
    osCreateThread(&g_boot_idle_thread, 1, (void*) boot_idle_thread_main, 0, &g_boot_thread_stack_4000_alias, 5);
    osStartThread(&g_boot_idle_thread);
}

/* was func_100010F8 */
void boot_idle_thread_main(s32 arg0) {
    pi_init_dma_queues(); // create message queues
    osCreateThread(&g_game_thread, 3, (void*) boot_game_thread_main, (void *) arg0, &g_boot_idle_thread, 10);
    if (g_os_cic_id == 0x17D9) { // EU: no g_eeprom_writes_disabled check
        osStartThread(&g_game_thread);
    }
    osSetThreadPri(&g_boot_idle_thread, NULL);
    do {} while(1);
}

/* P281: readable C for boot_game_thread_main (compiled C, 210 insns; EU version of the commented US draft below). It ends
   in game_thread_main, which never returns (difftest stubs it, so the whole body is compared). */
extern OSMesgQueue g_sched_event_queue;   /* VI retrace queue (reset path); was D_8003B578 */
extern OSMesg g_sched_event_msgs[8]; /* was D_8003BC10 */
extern OSViMode g_vi_mode; /* was D_8002AF20 */
extern u8 g_frame_counter_block[];          /* start of the memory cleared at boot (up to 0x80400000); was D_80043ED0 */
extern u8 D_427B0[];             /* ROM: compressed game segment (header word: offset of the code blob) */
extern u8 D_19EDE8[];            /* ROM: end of the compressed game code */
extern u32 g_level_tex_preload_lists;           /* header word read from D_427B0; was D_80082EB0 */
extern u8 g_boot_aligned_buf_raw[]; /* was D_80033690 */
extern u8 g_boot_page_table_raw[]; /* was D_80032E90 */
extern u8 *g_boot_aligned_buf; /* was D_80035858 */
extern u32 *g_boot_page_offsets;          /* per-4 KB-page offsets of the compressed game code; was D_8003585C */
extern u8 g_game_code_end[];          /* end of the game segment's code; was D_151FA920 */
void game_init_message_queues(void);
void game_thread_main(void);
void os_create_vi_manager(OSPri pri);
void heap_init(void);
void rzip_build_fixed_tables(void);
void tlb_page_bitmap_reset(void);
s32 allocate_memory(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 rzip_inflate(s32 arg0, s32 arg1, u32 arg2);
void heap_free(s32 arg0);
// boot_thread_main: game boot thread. After a reset (osResetType != 0) the VI manager starts first, otherwise after
// the memory clear; clears memory up to 0x80400000 (after a reset only from the heap), sets up the heap and two
// frame buffers, reads and decompresses the game code's first part, reads the page offset table of the rest
// (decrypted: xor 0x8039CCCA, plus the segment's ROM address), sets up the TLB area (tlb_area_init) and enters
// the game (game_thread_main, no return).
/* was func_10001194 */
void boot_game_thread_main(s32 arg0) {
    u32 len;
    u32 src;
    s32 size;
    s32 dst;
    u32 npages;
    u32 i;

    if (g_os_reset_type != 0) {
        osCreateMesgQueue(&g_sched_event_queue, g_sched_event_msgs, 8);
        os_create_vi_manager(OS_PRIORITY_VIMGR);
        osViSetMode(&g_vi_mode);
        osViBlack(TRUE);
        osViSetEvent(&g_sched_event_queue, NULL, 1);
    }
    prenmi_thread_start();
    if (g_os_reset_type == 0) {
        len = 0x80400000 - (u32) g_frame_counter_block;
        bzero(g_frame_counter_block, len);
    } else {
        bzero(&g_heap_start, 0x80400000 - (u32) &g_heap_start);
        len = 0x80400000 - (u32) g_frame_counter_block;
    }
    osInvalICache(g_frame_counter_block, len);
    osInvalDCache(g_frame_counter_block, len);
    mem_clear_expansion_flag();
    mem_init_region_bounds();
    heap_init();
    rzip_build_fixed_tables();
    g_framebuffers[0] = heap_alloc_tagged(0x1ECC0, 0xFF, 3, 1, 0);
    g_framebuffers[1] = heap_alloc_tagged(0x1ECC0, 0xFF, 3, 1, 0);
    if (g_os_reset_type == 0) {
        osCreateMesgQueue(&g_sched_event_queue, g_sched_event_msgs, 8);
        os_create_vi_manager(OS_PRIORITY_VIMGR);
        osViSetMode(&g_vi_mode);
        osViBlack(TRUE);
        osViSetEvent(&g_sched_event_queue, NULL, 1);
    }
    rom_dma_read((s32) D_427B0, &g_level_tex_preload_lists, 16, 1);
    src = g_level_tex_preload_lists + (u32) D_427B0;
    size = (u32) D_19EDE8 - src;
    dst = allocate_memory(size, 1, 2, 0);
    rom_dma_read(src, (void *) dst, size, 1);
    rzip_inflate(dst, (s32) &g_level_tex_preload_lists, g_mem_scratch_area);
    heap_free(dst);
    npages = ((u32) g_game_code_end - (u32) game_init_message_queues + 0xFFF) >> 12;
    g_boot_aligned_buf = (u8 *) (((u32) g_boot_aligned_buf_raw + 0xF) & ~0xF);
    g_boot_page_offsets = (u32 *) (((u32) g_boot_page_table_raw + 0xF) & ~0xF);
    rom_dma_read((s32) D_427B0 + 4, g_boot_page_offsets, (((npages + 2) * 4 + 0xF) | 0xF) ^ 0xF, 1);
    for (i = 0; i < npages + 1; i++) {
        g_boot_page_offsets[i] = (g_boot_page_offsets[i] ^ 0x8039CCCA) + (u32) D_427B0;
    }
    g_tlb_area_phys = 0;
    tlb_area_init(0xEB);
    boot_clear_low_block();
    tlb_page_bitmap_reset();
    game_thread_main();
}
// NON-MATCHING: start/end mostly ok, middle, not-so-much.
// s32 *allocate_memory(s32, s32, s32, s32);
// void boot_game_thread_main(s32 arg0) {
//     u32 block_count;
//     s32 sp44;
//     s32 sp40;
//     u32 sp28;
//     s32 offset;
//     s32 phi_s0;
//     s32 i;
//     s32 *fb;
//
//     offset = D_80042450;
//
//     prenmi_thread_start();
//     phi_s0 = 0x80400000 - (s32)&g_frame_counter_block_alias;
//     if (g_os_reset_type == 0) { // osResetType
//         bzero(&g_frame_counter_block_alias, phi_s0);
//     } else {
//         bzero(&D_800E9D10, 0x80400000 - (s32)&D_800E9D10);
//     }
//     osInvalICache(&g_frame_counter_block_alias, phi_s0);
//     osInvalDCache(&g_frame_counter_block_alias, phi_s0);
//     mem_clear_expansion_flag();
//     mem_init_region_bounds();
//     heap_init();
//     rzip_build_fixed_tables();
//     fb = g_framebuffers;
//     *(fb + 0) = heap_alloc_tagged(126144, 0xFF, 3, 1, 0);
//     *(fb + 1) = heap_alloc_tagged(126144, 0xFF, 3, 1, 0);
//     osCreateViManager(OS_PRIORITY_VIMGR);
//
//     // permuter...
//     if (!phi_s0) {};
//
//     rom_dma_read(offset, &D_80082B20, 16, 1);
//     if (0) {};
//     sp44 = D_80082B20 + offset;         // D_80082B20 + first
//     sp28 = (s32)func_1019EA88 - sp44;   // second TLB offset - temp_v0 // func_1600000 ?
//     sp40 = allocate_memory(sp28, 1, 2, 0);
//     rom_dma_read(sp44, sp40, sp28, 1);
//     if (0) {};
//     func_10006240(sp40, &D_80082B20, g_mem_scratch_area);
//     heap_free(sp40);
//     // D_80033330 is the current compressed item
//     block_count = (u32) (((s32)func_151FA130 - (s32)game_init_message_queues) + 4095) >> 12; // 2072880 bytes / 4096 = 506 offsets
//     D_800354F8 = ALIGN16(&D_80033330);
//     // D_800354FC holds compressed code offsets (encrypted/unencrypted)
//     D_800354FC = ALIGNU16(&D_80032B30);
//     rom_dma_read(offset + 4, D_800354FC, (((((block_count + 2)) + 0xF) | 0xF) ^ 0xF) , 1); //
//
//     for (i = 0; i < block_count; i++) {
//         D_800354FC[i] = (D_800354FC[i] ^ 0x8039CCCA) + offset;
//     }
//
//     g_tlb_area_phys = 0;
//     tlb_area_init(0xEB);
//     boot_clear_low_block();
//     tlb_page_bitmap_reset();
//     game_thread_main();
// }
