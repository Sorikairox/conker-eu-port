/* PC entry point for the game (wasm32). Compiled with the game's headers and flags.
 *
 * N64 boot: entrypoint (asm func_10001000) -> func_10001050 (clear bss, osInitialize, create
 * thread 1 = func_100010F8) -> thread 1 creates the message queues and the main thread
 * (func_10001194, pri 10), then drops to idle priority.
 *
 * On the PC:
 *  - func_10001050 is not called: its bss clear spans &D_80043B40 - &D_8002D4B0, which is not a
 *    contiguous range in the wasm build (data symbols are separate stub arrays until Phase 2b).
 *    port_boot() does the rest of it.
 *  - func_10001194 (main thread) is still GLOBAL_ASM; the version below follows the commented
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
void func_10003BD0(void);
void func_15007830(void); /* port/boot/game_entry.c */

void func_10001194(s32 arg0) {
    s32 *fb;

    port_log("[boot] main thread: func_10001194 (PC version)\n");
    func_10005218();
    port_log("[boot] memory init\n");
    func_10003920();
    func_10003930();
    func_10003BD0();
    func_1000709C();
    fb = D_8002AAE8;
    fb[0] = func_10003C6C(126144, 0xFF, 3, 1, 0);
    fb[1] = func_10003C6C(126144, 0xFF, 3, 1, 0);
    port_log("[boot] framebuffers %08X %08X\n", fb[0], fb[1]);
    osCreateViManager(OS_PRIORITY_VIMGR);
    /* N64: DMA + rzip-decompress the game code/data segments, map TLB 0x15000000. Skipped (PLAN 3.2). */
    D_8003BE74 = 0;
    func_10005B04(0xEB);
    port_log("[boot] func_10001420\n");
    func_10001420();
    port_log("[boot] func_10005BE0\n");
    func_10005BE0();
    port_log("[boot] entering game: func_15007830\n");
    func_15007830();
    port_log("[boot] func_15007830 returned\n");
}

int port_mem_load(void);
int port_memtest(void);
int port_icalltest(void);
int port_overrides_test(void);
int port_romsym_test(void);

static void port_boot(void) {
    /* N64 data segments from the user's ROM into the RDRAM mirror + pointer relocation
     * (docs/port/MEMORY.md); on the N64 the IPL3 / func_10001194 load these. */
    if (port_mem_load() == 0) { port_memtest(); port_icalltest(); port_overrides_test(); port_romsym_test(); }
    /* libultra boot globals the IPL3 leaves in low RDRAM */
    D_80000300 = 1;          /* osTvType: NTSC=1 / PAL=0; EU ROM -> PAL */
    D_80000300 = 0;
    D_8000030C = 0;          /* osResetType: cold */
    D_80000310 = 0x17D9;     /* osCicId 6105: gates the main-thread start in func_100010F8 */
    D_80000318 = 0x800000;   /* osMemSize: 8 MB (expansion pak) */
    port_log("[boot] func_100061F8(1, 31)\n");
    func_100061F8(1, 31);
    __osInitialize_common();
    osCreateThread(&D_800318B0, 1, (void *)func_100010F8, 0, &D_8002D8B0, 5);
    osStartThread(&D_800318B0);
}

int main(void) {
    port_log("Conker port: game entry\n");
    port_run(port_boot);
    return 0;
}
