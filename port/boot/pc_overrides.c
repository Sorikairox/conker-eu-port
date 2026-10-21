/* PC replacements for game functions that cannot be C in the decomp (session P8; list from
 * docs/port/sessions/P5.md, "PC-replacement needed"). They stay GLOBAL_ASM in conker/src_eu; the
 * port's definitions here replace the weak asm stubs (port/tools/gen_stubs.py). This TU goes through
 * the vbe IR pass like the game TUs (port/Makefile BOOT_SRC), so game memory is accessed with N64
 * semantics: D_80088950 below is a big-endian u64 in virtual big-endian memory.
 *
 *   func_100061F8  handwritten TLB loop (init_eu_5DA0.c)
 *   func_150ADA20  libultra guRandom on 64-bit registers (game_DAE50.c)
 */
#include <ultra64.h>

/* func_100061F8(lo, hi): for index = hi down to lo: Index = index, EntryHi = 0x80000000 (KSEG0, never
 * matched), EntryLo0/1 = 0, tlbwi; EntryHi is restored afterwards. That invalidates TLB entries
 * lo..hi. The PC build has no TLB: code is native wasm and the TLB-mapped data segment
 * (0x16000000) is the n64_seg16 mirror, which port_n64_to_wasm resolves statically. So this is a
 * no-op. Called once at boot (1, 31) and once per frame by the main loop. The asm leaves v0 as it
 * was; callers ignore it (one call-site signature, i32(i32,i32) in sigdb.json). */
s32 func_100061F8(s32 lo, s32 hi) {
    (void)lo;
    (void)hi;
    return 0;
}

/* guRandom with the seed as a u64 (the asm uses ld/dsll32/dsrl/sd; difftest has no 64-bit shifts,
 * see P5.md). Instruction by instruction:
 *   a2 = x << 63 >> 31 | x << 31 >> 32;  a2 ^= x << 44 >> 32;  x = a2 ^ (a2 >> 20 & 0xFFF);
 *   return (s32)x   (dsll32/dsra32 sign-extends the low word)
 * The seed is set by func_150ADACC: D_80088950 = (s64)arg0 + 1. */
extern u64 D_80088950;

s32 func_150ADA20(void) {
    u64 x = D_80088950;
    u64 t = (x << 63 >> 31) | (x << 31 >> 32);
    t ^= x << 44 >> 32;
    x = t ^ ((t >> 20) & 0xFFF);
    D_80088950 = x;
    return (s32)(u32)x;
}

/* self-test: three guRandom steps from a known seed (expected values from the u64 formula in
 * Python, docs/port/sessions/P8.md); checks the vbe 64-bit load/store of the seed too */
void port_glog(const char *fmt, ...);
#define port_log port_glog /* format strings live in vbe game memory */
int port_overrides_test(void) {
    static const u32 want[3] = {0x780B1177, 0x0D12F86A, 0xA90FD6A5};
    u64 saved = D_80088950;
    int bad = 0, i;
    D_80088950 = 0x0123456789ABCDEFULL;
    for (i = 0; i < 3; i++) {
        u32 got = (u32)func_150ADA20();
        if (got != want[i]) { port_log("[overrides] guRandom step %d: %08X, want %08X\n", i, got, want[i]); bad++; }
    }
    if (D_80088950 != 0xA90FD6A5ULL) { port_log("[overrides] seed after 3 steps wrong\n"); bad++; }
    D_80088950 = saved;
    if (bad) port_log("[overrides] guRandom FAIL (%d failures)\n", bad);
    else port_log("[overrides] guRandom PASS (0 failures)\n");
    return bad;
}

/* ROM-offset symbols (session P9): &D_1A3B40 must be the texture bank's ROM offset, not a wasm
 * address (port/tools/vbe.py ROM_ABS). The game's own C func_1510D8F4 (game_eu_13A8A0.c) computes
 * texture 0xED0's ROM offset; a PI DMA of the first 16 bytes there must give the bytes Python reads
 * from the ROM at 0x6F1618 (rzip header: BE u32 size 0x300, then DEFLATE). D_800B8BB8 is the
 * inflated-size table that func_15003570 (game_305D0.c, C) builds from the same bank by DMA. */
s32 func_1510D8F4(s32 id);
extern s16 D_800B8BB8[];
int port_romsym_test(void) {
    static const u8 want[16] = {0x00, 0x00, 0x03, 0x00, 0xED, 0x4F, 0x21, 0x56,
                                0x43, 0x31, 0x10, 0xFC, 0x9B, 0x6C, 0x36, 0xBB};
    static u8 buf[16];
    u32 rom = (u32)func_1510D8F4(0xED0);
    int bad = 0, i;
    if (rom != 0x6F1618) { port_log("[romsym] func_1510D8F4(0xED0) = 0x%X, want 0x6F1618\n", rom); bad++; }
    osPiRawStartDma(OS_READ, rom, buf, 16);
    for (i = 0; i < 16; i++) bad += buf[i] != want[i];
    port_log("[romsym] tex 0xED0 @ROM 0x%X: %02X%02X%02X%02X %02X%02X%02X%02X, size table %d\n", rom,
             buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7], D_800B8BB8[0xED0]);
    if (bad) port_log("[romsym] FAIL (%d failures)\n", bad); /* %s args would be vbe strings */
    else port_log("[romsym] PASS (0 failures)\n");
    return bad;
}

/* ---- P11: TEMPORARY PC override of func_15019130 (game_45B80.c, still GLOBAL_ASM) ----
 * The per-frame world update ("few loops"). func_1501878C (C since P10) returns before building the
 * frame when this returns 0, which the asm stub always did, so no gfx task was ever sent.
 * Written by hand from asm/nonmatchings/game_45B80/func_15019130.s (EU, 0x150190E0); delay-slot
 * arguments resolved. Remove when the port branch converts func_15019130.
 * Callee prototypes are as called; port/tools/sigs.py adapts call sites to the definitions. */
extern u8 D_800BEAC0, D_800BE616, D_800CC2B0, D_800DD157, D_800BE9C0;
extern s32 D_80082FA0, D_800BE9F0;
extern u32 D_80043ED0[], D_80044B20[];
void *port_n64_to_wasm(unsigned n64addr);
void func_1510DDE4(void); void func_1509BA04(s32); void func_1509BBA0(s32); void func_10004250(void);
void func_1501E46C(s32); void func_15035210(void); void func_1510BC10(void); void func_1510F800(s32);
void func_15113700(void); void func_151143D4(s32); void func_15114708(void); void func_15044D18(void);
void func_15018DFC(void); void func_1502457C(s32, s32); void func_1501ECA4(s32); void func_15020F6C(s32);
void func_1501E364(s32); void func_15088130(void); void func_15122AE0(void); void func_1504ADD0(void);
void func_151101B4(s32); void func_150952B0(s32); void func_15113000(s32); void func_15174F68(s32, s32);
void func_1501C860(void); void func_1511FC20(s32); void func_151890E4(s32); void func_1516706C(void);
void func_151671E8(void); void func_1502C1D4(void); void func_150A126C(void); void func_15113798(void);
void func_15173E34(s32); void func_1502C494(void); void func_15114208(void); void func_15063AA0(void);
void func_15184298(void); void func_151670C0(void); void func_15178004(void); void func_15181A6C(void);
void func_1517FCCC(void); void func_1517FD24(void); void func_15036438(void); void func_1515DC38(void);

s32 func_15019130(void) {
    s32 i;
    u32 *p;
    func_1510DDE4();
    func_1509BA04(0);
    func_1509BBA0(2);
    D_800DD157 = 0;
    func_10004250();
    func_1501E46C(0);
    func_15035210();
    func_1510BC10();
    func_1510F800(0);
    func_15113700();
    if (D_800BEAC0 == 0) func_151143D4(1);
    if (D_800BEAC0 == 0) func_15114708();
    func_15044D18();
    func_15018DFC();
    func_1502457C(1, 0);
    func_1501ECA4(0);
    func_1502457C(0, 0);
    func_15020F6C(0);
    func_1501E364(0);
    if (*(s8 *)port_n64_to_wasm(0x800D27C9) != 0) func_15088130();
    func_15122AE0();
    func_1504ADD0();
    func_1510F800(0);
    for (i = 0; i <= D_80082FA0; i++) func_151101B4(i);
    func_1510BC10();
    if (D_80082FA0 >= 0) {
        u8 j = 0;
        do { func_150952B0(j); j++; } while (j <= D_80082FA0);
    }
    func_15113000(0);
    func_15174F68(D_800BE9F0, 0);
    func_1501C860();
    func_1511FC20(D_800BE9C0);
    func_151890E4(0);
    if (D_800BEAC0 == 0) { func_1516706C(); func_151671E8(); }
    func_1502C1D4();
    if (D_800BE616 == 0) func_150A126C();
    func_15113798();
    func_151890E4(1);
    func_15173E34(D_800BE9F0);
    func_1502C494();
    func_15114208();
    if (D_800CC2B0 != 0) func_15063AA0();
    if (D_800BEAC0 == 0) { func_15184298(); func_151670C0(); func_15178004(); }
    if (D_800BEAC0 == 0) func_15181A6C();
    func_1517FCCC();
    func_1517FD24();
    func_15036438();
    func_1515DC38();
    for (p = D_80043ED0; p != D_80044B20; p += 8) { p[1]++; p[3]++; p[5]++; p[7]++; }
    return 1;
}

/* ---- P11: TEMPORARY PC override of func_eu_1501C860 (game_eu_4A070.c, still GLOBAL_ASM) ----
 * End of frame: closes the DL (rolls back to the reserve when it overflows), fills the gfx OSScTask
 * D_800BEEF8[idx] (stride 0x60) and sends it to the scheduler's gfx queue (EU 0x8003B548 = C name
 * D_8003B1E8). Hand-translated from asm/nonmatchings/game_eu_4A070/func_eu_1501C860.s (EU 0x1501C860).
 * Data are addressed through port_n64_to_wasm (vbe TU: N64 semantics) at the address the asm's symbol
 * resolves to: names listed in conker/undefined_syms.eu.txt are US names remapped to EU addresses
 * (D_800BE9C0 -> 0x800BEDE0, D_800BE9D0 -> 0x800BEDF0, D_800BE9D8 -> 0x800BEDF8, D_80038090/94 ->
 * 0x800383F0/F4, D_80082FA0 -> 0x80083330, D_8002AAE8 -> 0x8002AE1C); the others are literal.
 * Remove when the port branch converts it. */
#define P11W(a) ((u32 *)port_n64_to_wasm(a))
void func_1501A39C(void);
void func_1501CC1C(s32);
s32 func_eu_1501C860(s32 a0, s32 a1) {
    u8 *idx = (u8 *)port_n64_to_wasm(0x800BEDE0);
    u32 *gdlp = P11W(0x800BEDF0);          /* current DL pointer */
    u32 *bufs = P11W(0x800BEDE8);          /* DL buffers [2] */
    u32 *rsv = P11W(0x800BEDF8);           /* reserve position per buffer */
    u32 *task, *g;
    s32 cap, n;
    (void)a0;
    { static int nlog; if (nlog++ < 3) port_log("[frame] submit: idx %d gdl %08X bufs %08X %08X reserve %08X %08X\n", *idx, *gdlp, bufs[0], bufs[1], rsv[0], rsv[1]); }
    if (!bufs[0] || !bufs[1] || *gdlp < bufs[0]) { port_log("[frame] no DL buffers: frame dropped\n"); return 0; }
    task = (u32 *)((u8 *)P11W(0x800BEEF8) + *idx * 0x60);
    *P11W(0x800BEEF4) = (u32)task;
    task[0] = 0;
    cap = (s32)(bufs[1] - bufs[0]) >> 3;
    n = (s32)(*gdlp - bufs[*idx]) >> 3;
    if (n < 0 || cap < n) {                 /* overflowed: reset to the reserve, close it */
        func_1501A39C();
        *gdlp = rsv[*idx];
        g = (u32 *)*gdlp; *gdlp += 8; g[1] = 0; g[0] = 0xE9000000;
        g = (u32 *)*gdlp; *gdlp += 8; g[1] = 0; g[0] = 0xDF000000;
        n = (s32)(*gdlp - bufs[*idx]) >> 3;
    }
    if (n < 0 || cap - 0x190 < n) {         /* past the safety margin: cut at cap - 0x190 */
        *gdlp = bufs[*idx] + (cap - 0x190) * 8;
        g = (u32 *)*gdlp; *gdlp += 8; g[1] = 0; g[0] = 0xE9000000;
        g = (u32 *)*gdlp; *gdlp += 8; g[1] = 0; g[0] = 0xDF000000;
    }
    task[0x48 / 4] = bufs[*idx];                                    /* data_ptr */
    task[0x4C / 4] = ((*gdlp - bufs[*idx]) >> 3) << 3;              /* data_size */
    func_1501CC1C(n);
    task[0x18 / 4] = M_GFXTASK;
    task[0x1C / 4] = 4;                                             /* OS_TASK_LOADABLE */
    task[0x20 / 4] = 0x10029400;                                    /* ucode_boot (D_10029400) */
    task[0x24 / 4] = 0xD0;                                          /* D_100294D0 - D_10029400 */
    if (*(u8 *)port_n64_to_wasm(0x800BEFC0) == 0) {
        task[0x28 / 4] = (u32)port_n64_to_wasm(0x800C1480);         /* ucode text */
        task[0x30 / 4] = *P11W(0x800BEFBC);                         /* ucode data */
    } else {
        task[0x28 / 4] = (u32)port_n64_to_wasm(0x800BEFD0);
        task[0x30 / 4] = *P11W(0x800BEEF0);
    }
    task[0x34 / 4] = 0x800;
    task[0x38 / 4] = (u32)port_n64_to_wasm(0x800CC230);             /* dram_stack */
    task[0x3C / 4] = 0x400;
    task[0x40 / 4] = *P11W(0x800383F0);                             /* output_buff */
    task[0x44 / 4] = *P11W(0x800383F4);                             /* output_buff_size (end) */
    task[0x50 / 4] = (u32)port_n64_to_wasm(0x8003A948);             /* yield_data_ptr */
    task[0x54 / 4] = 0xC00;
    task[0x0C / 4] = 0x23;                                          /* OSScTask flags */
    if (a1 != 0) task[0x0C / 4] |= 0x40;
    if (*(u8 *)port_n64_to_wasm(0x800BEA37) != 0) {
        task[0x0C / 4] |= (u32)(*P11W(0x80083330) + 1) << 16;
        *(u8 *)port_n64_to_wasm(0x800BEA37) = 0;
    }
    task[0x58 / 4] = (u32)port_n64_to_wasm(0x800BEE30);             /* msgQ: the main loop's queue */
    task[0x5C / 4] = (u32)((u8 *)port_n64_to_wasm(0x800BEE88) + *idx * 0x20);
    task[0x10 / 4] = P11W(0x8002AE1C)[*idx];                        /* framebuffer */
    osWritebackDCacheAll();
    osSendMesg((OSMesgQueue *)port_n64_to_wasm(0x8003B548), (OSMesg)task, OS_MESG_BLOCK);
    if (a1 != 0) *idx ^= 1;
    (*(s16 *)port_n64_to_wasm(0x800BEEC8))++;
    return 0;
}
