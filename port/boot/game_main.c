/* PC entry point for the game (wasm32). Compiled with the game's headers and flags.
 *
 * N64 boot: entrypoint (asm boot_entrypoint) -> boot_entry_main (clear bss, osInitialize, create
 * thread 1 = boot_idle_thread_main) -> thread 1 creates the message queues and the main thread
 * (boot_game_thread_main, pri 10), then drops to idle priority.
 *
 * On the PC:
 *  - boot_entry_main is not called: its bss clear spans &D_80043B40 - &D_8002D4B0, which is not a
 *    contiguous range in the wasm build (data symbols are separate stub arrays until Phase 2b).
 *    port_boot() does the rest of it.
 *  - boot_game_thread_main (main thread) is still GLOBAL_ASM; the version below follows the commented
 *    draft in init_1050.c, minus the rzip code decompression and TLB mapping (no-ops on the PC:
 *    the game code is native wasm) and minus the game-data DMA (needs the Phase 2b data layout).
 */
#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void port_run(void (*boot)(void));
void port_glog(const char *fmt, ...);
#define port_log port_glog /* format strings live in vbe game memory */

extern u32 D_80000318; /* osMemSize */
/* asm-only callees are left undeclared on purpose: the game's other callers use implicit `int f()`
 * declarations, and the generated stub takes the majority wasm signature. */
void heap_init(void);
void game_thread_main(void); /* port/boot/game_entry.c */

/* P11 (PC fix-up, port-only): mem_init_region_bounds (C, init_3930.c) stores the heap / scratch bounds as
 * KSEG0 constants (0x803F5000 / 0x803FE000). heap_init then computes the heap size as
 * D_80038098 - &D_800EA140, which mixes a K0 constant with a wasm address (gap "address constants"
 * in P4.md): the size came out ~1.9 GB and the first top-down allocation wrote out of bounds.
 * Rebase the four words into the n64_rdram mirror, where &D_800EA140 lives. */
extern u8 n64_rdram[];
extern u32 D_80038090, D_80038094, D_80038098, D_8003809C;
void *port_n64_to_wasm(unsigned n64addr);
static void port_fix_heap_bounds(void) {
    u32 base = (u32)n64_rdram;
    D_80038090 = base + (D_80038090 & 0x7FFFFF);
    D_80038094 = base + (D_80038094 & 0x7FFFFF);
    D_80038098 = base + (D_80038098 & 0x7FFFFF);
    D_8003809C = base + (D_8003809C & 0x7FFFFF);
    port_log("[boot] heap bounds rebased: end %08X (n64_rdram %08X)\n", D_80038098, base);
}

void boot_game_thread_main(s32 arg0) {
    s32 *fb;

    port_log("[boot] main thread: boot_game_thread_main (PC version)\n");
    prenmi_thread_start();
    port_log("[boot] memory init\n");
    mem_clear_expansion_flag();
    mem_init_region_bounds();
    port_fix_heap_bounds(); /* P11: K0 constants from mem_init_region_bounds -> n64_rdram mirror */
    heap_init();
    /* P37: the inflater's fixed huffman tables (D_8003C230). The asm jal target is 0x1000738C (EU); the commented C
     * in init_1050.c names it func_1000709C (the US name, a "missing" stub until now). Now that Rare's inflater is C
     * (init_eu_5DA0.c, port P36) a fixed block needs these tables: without them inf_codes read wild pointers. */
    { void rzip_build_fixed_tables(void); rzip_build_fixed_tables(); }
    fb = g_framebuffers;
    fb[0] = heap_alloc_tagged(126144, 0xFF, 3, 1, 0);
    fb[1] = heap_alloc_tagged(126144, 0xFF, 3, 1, 0);
    port_log("[boot] framebuffers %08X %08X\n", fb[0], fb[1]);
    osCreateViManager(OS_PRIORITY_VIMGR);
    /* P11: the asm (cold-boot branch at 0x100012D8) creates the scheduler queue (EU 0x8003B578, the C
     * name is D_8003B218) with 8 slots at 0x8003BC10, sets the VI mode, blacks the screen and makes
     * every retrace post message 0 to it. The P4 PC version had left this out, so the C scheduler
     * sched_thread_main never woke up. (os_create_vi_manager = osCreateViManager(0xFE), PC no-op above.) */
    {
        extern OSMesgQueue D_8003B218;
        extern OSViMode D_8002AF20;
        OSMesg *buf = (OSMesg *)port_n64_to_wasm(0x8003BC10);
        if ((void *)&D_8003B218 != port_n64_to_wasm(0x8003B578)) port_log("[boot] WARNING: D_8003B218 is not EU 0x8003B578\n");
        osCreateMesgQueue(&D_8003B218, buf, 8);
        osViSetMode(&D_8002AF20);
        osViBlack(1);
        osViSetEvent(&D_8003B218, (OSMesg)0, 1);
    }
    /* N64: DMA + rzip-decompress the game code/data segments, map TLB 0x15000000. Skipped (PLAN 3.2). */
    D_8003BE74 = 0;
    tlb_area_init(0xEB);
    port_log("[boot] boot_clear_low_block\n");
    boot_clear_low_block();
    port_log("[boot] tlb_page_bitmap_reset\n");
    tlb_page_bitmap_reset();
    { void port_sched_test_start(void); int port_selftest_on(void); if (port_selftest_on()) port_sched_test_start(); } /* P11: C scheduler runtime check */
    port_log("[boot] entering game: game_thread_main\n");
    game_thread_main();
    port_log("[boot] game_thread_main returned\n");
}

int port_mem_load(void);
int port_memtest(void);
int port_icalltest(void);
int port_overrides_test(void);
int port_romsym_test(void);
int port_gu_test(void); /* P25 */

static void port_boot(void) {
    /* N64 data segments from the user's ROM into the RDRAM mirror + pointer relocation
     * (docs/port/MEMORY.md); on the N64 the IPL3 / boot_game_thread_main load these. */
    if (port_mem_load() == 0) { port_memtest(); port_icalltest(); port_overrides_test(); port_romsym_test(); port_gu_test(); { void port_tables_check(void); port_tables_check(); } }
    /* libultra boot globals the IPL3 leaves in low RDRAM */
    D_80000300 = 1;          /* osTvType: NTSC=1 / PAL=0; EU ROM -> PAL */
    D_80000300 = 0;
    { extern int port_tv_type; port_tv_type = 0; } /* P147: VI pacing 50 Hz (pc_sched.c) */
    D_80000308 = (s32)0xB0000000; /* osRomBase: the cart in KSEG1, as the IPL3 leaves it (P66: the C rom_read_direct reads
                              * CART_WORD(devAddr | osRomBase); with 0 it read KSEG1 RDRAM 0xA0xxxxxx, not the ROM) */
    D_8000030C = 0;          /* osResetType: cold */
    D_80000310 = 0x17D9;     /* osCicId 6105: gates the main-thread start in boot_idle_thread_main */
    D_80000318 = 0x800000;   /* osMemSize: 8 MB (expansion pak) */
    port_log("[boot] tlb_clear_entries(1, 31)\n");
    tlb_clear_entries(1, 31);
    __osInitialize_common();
    osCreateThread(&D_800318B0, 1, (void *)boot_idle_thread_main, 0, &D_8002D8B0, 5);
    osStartThread(&D_800318B0);
}

int main(void) {
    port_log("Conker port: game entry\n");
    port_run(port_boot);
    return 0;
}
