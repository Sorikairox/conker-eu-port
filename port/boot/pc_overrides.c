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

/* P19: the P11 TEMPORARY overrides of func_15019130 and func_eu_1501C860 were removed: both are
 * NON_MATCHING C on the port branch since P15-P17 (game_45B80.c, game_eu_4A070.c). */

/* ---- P19: TEMPORARY PC override of func_1502B350 (game_57FA0.c, still GLOBAL_ASM) ----
 * The asset load behind func_1502B6BC / func_1502B5C8 / func_1502B020 callers: allocate, DMA the
 * record, and when (info & 0x70000000) == 0x10000000 inflate it into a second buffer (rzip; the first
 * word is the inflated size, rejected when 0 or >= 1000000) and free the packed copy. *ok receives the
 * loaded size (0 on failure). Hand-translated from the EU asm at 0x1502B640 (48 insns). Without it the
 * stub returned 0 and the level record D_800B0DF0 (EU 0x800B1200) was never loaded, so
 * func_15174B48 called through D_8008D11C[garbage]. The 3rd func_10006530 argument is the word at
 * EU 0x80038404 (US name D_800380A4). Remove when the port branch converts func_1502B350. */
void *port_n64_to_wasm(unsigned n64addr);
int port_heap_check(void);
s32 *allocate_memory(s32, s32, s32, s32);
s32 func_10004514(s32 devAddr, void *dramAddr, u32 size, s32 arg3);
s32 func_10006530(s32 *, s32 *, u32);
void func_10004074(s32 *);
s32 func_1502B350(u8 *rom, s32 info, s32 *ok) {
    u32 size = ((info & 0x0FFFFFFF) + 1) & ~1;
    s32 *buf = allocate_memory(size, 1, 2, 2);
    s32 *out;
    s32 n, got;
    static int ncall; int dbg = ncall++ < 4;
    if (dbg) { port_glog("[b350] #%d rom %X info %X size %X buf %X\n", ncall, (u32)rom, info, size, (u32)buf); port_heap_check(); }
    if (buf == NULL) return 0;
    func_10004514((s32)rom, buf, (size + 15) & ~15, 1);
    if (dbg) port_heap_check();
    if ((info & 0x70000000) != 0x10000000) {
        *ok = size;
        return (s32)buf;
    }
    n = buf[0] & 0x7FFFFFFF;
    *ok = n;
    out = NULL; got = 0;
    if (n != 0 && (u32)n < 1000000) {
        out = allocate_memory(n, 1, 2, 2);
        if (out != NULL) got = func_10006530(buf, out, *(u32 *)port_n64_to_wasm(0x80038404));
        if (dbg) { port_glog("[b350] n %X out %X got %X\n", n, (u32)out, got); port_heap_check(); }
    }
    func_10004074(buf);
    *ok = got;
    return (s32)out;
}

/* ---- P19: TEMPORARY PC override of func_15002248 (game_eu_2F180.c, still GLOBAL_ASM) ----
 * Quadtree build helper of func_15001DE0: keeps the entries of the u16 index list `in` (in[0] = count)
 * whose triangle passes the box test, writes them to a new list *out (allocate_memory; the caller frees
 * it), and returns the count plus the grid-snapped x min / z max of the kept entries in *xmin / *zmax.
 * The stub left *out as stack garbage, so func_15001DE0 freed a garbage pointer and the heap free list
 * went cyclic (func_10004074 then spun forever). Hand-translated from the EU asm at 0x15002248
 * (200 insns). Data at EU addresses: grid shift 0x80083330 (US D_80082FA0), triangle table
 * 0x800DC26C (3 vertex pointers per entry, s16 xyz), grid table 0x800DC274 (s16 x, z per entry).
 * The box test: func_15049260 is declared void in C, but this caller uses its v0 (the result of
 * func_150AB278, still asm). Until both are C every entry is kept, as the stub's v0 = 0 implies.
 * Vertex pointers are valid when >= 0x10000000 (wasm data) instead of the asm's > 0x80000000. */
typedef struct { s32 unk0[9]; } P19Tri;
void func_150492CC(f32, f32, f32);
void func_15049260(P19Tri);
s32 func_15002248(s32 x0, s32 x1, s32 z0, s32 z1, s32 *xmin, s32 *zmax, u16 *in, u16 **out) {
    s32 shift = *(s32 *)port_n64_to_wasm(0x80083330) + 1;
    s32 step = 1 << shift, lo = step - 1, mask = -step;
    s32 n = in[0] + 1, cnt = 0, found = 0, i, k;
    u16 *list;
    func_150492CC((f32)(x1 - x0), 32000.0f, (f32)(z1 - z0));
    list = (u16 *)allocate_memory(n * 2, 1, 0, 0);
    *out = list;
    *xmin = 0;
    *zmax = 0;
    for (i = 1; i < n; i++) {
        u16 idx = in[i];
        u32 *tri = (u32 *)(*(u32 *)port_n64_to_wasm(0x800DC26C) + idx * 12);
        f32 v[9];
        P19Tri t;
        for (k = 0; k < 3; k++) {
            s16 *p = (s16 *)tri[k];
            if ((u32)p >= 0x10000000) {
                v[k * 3 + 0] = (f32)(p[0] - ((x0 + x1) >> 1));
                v[k * 3 + 1] = (f32)p[1];
                v[k * 3 + 2] = (f32)(p[2] - ((z0 + z1) >> 1));
            } else {
                v[k * 3 + 0] = v[k * 3 + 1] = v[k * 3 + 2] = 0.0f;
            }
        }
        for (k = 0; k < 9; k++) t.unk0[k] = *(s32 *)&v[k];
        func_15049260(t);
        {
            s16 *g = (s16 *)(*(u32 *)port_n64_to_wasm(0x800DC274) + idx * 4);
            s32 a = (g[0] - lo) & mask, b = ((g[1] + lo) & mask) + lo;
            list[++cnt] = idx;
            if (!found) { found = 1; *xmin = a; *zmax = b; }
            else { if (a < *xmin) *xmin = a; if (*zmax < b) *zmax = b; }
        }
    }
    list[0] = cnt;
    return cnt;
}

/* ---- P19: TEMPORARY PC override of func_1502B4A8 (game_57FA0.c, still GLOBAL_ASM) ----
 * Relocates a loaded asset's sub-file table: entries are {s32 offset, u32 info}. With n == 0, n is the
 * index of the first entry whose info has bit 31 set, plus one. For each entry info &= 0x0FFFFFFF and
 * offset becomes base + offset (0 when offset == -1 or info == 0). Returns n. Hand-translated from the
 * EU asm at 0x1502B798. The stub's 0 left the level record D_800B0DF0 (EU 0x800B1200) NULL in
 * func_15002FB4, so func_15174B48 indexed D_8008D11C with a null-zone byte. */
s32 func_1502B4A8(s32 *base, s32 n) {
    s32 i;
    if (n == 0) {
        do { n++; } while (!(base[(n - 1) * 2 + 1] & 0x80000000));
    }
    for (i = 0; i < n; i++) {
        s32 *e = &base[i * 2];
        e[1] &= 0x0FFFFFFF;
        e[0] = (e[0] == -1 || e[1] == 0) ? 0 : e[0] + (s32)base;
    }
    return n;
}
