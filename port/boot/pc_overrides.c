/* PC replacements for game functions that cannot be C in the decomp (session P8; list from
 * docs/port/sessions/P5.md, "PC-replacement needed"). They stay GLOBAL_ASM in conker/src_eu; the
 * port's definitions here replace the weak asm stubs (port/tools/gen_stubs.py). This TU goes through
 * the vbe IR pass like the game TUs (port/Makefile BOOT_SRC), so game memory is accessed with N64
 * semantics: D_80088950 below is a big-endian u64 in virtual big-endian memory.
 *
 *   func_100061F8  handwritten TLB loop (init_eu_5DA0.c)
 *   func_150ADA20  libultra guRandom on 64-bit registers (game_DAE50.c)
 *   TEMPORARY (until the port branch converts them): func_150A9B0C (P58), func_150A9E64 and func_150844AC (P61),
 *   func_1502AF04, func_150A69E0 and func_1510E908 (P63)
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

/* P23: the P19 TEMPORARY overrides of func_1502B350, func_1502B4A8 and func_15002248 were removed:
 * the port branch converted them in P20 (game_57FA0.c, game_eu_2F180.c). */

/* P23: ?dlstat=N probe of the frame builder's state (logged with the gfx frame statistics). */
extern unsigned char D_800BEA35, D_800BEAC0, D_800E0B94;
extern unsigned D_800BE9D0, D_800BE9D8[2], D_800BEDE8[2];
extern unsigned char D_800BE9C0; /* u8 (P31: was short, read the wrong byte) */
void port_cam_probe(unsigned task);
void port_frame_probe(unsigned task) {
    port_glog("[probe] task %u: BEA35 %u BEAC0 %u E0B94 %u GDL %08X BE9D8 %08X %08X BEDE8 %08X %08X BE9C0 %d\n", task,
              D_800BEA35, D_800BEAC0, D_800E0B94, D_800BE9D0, D_800BE9D8[0], D_800BE9D8[1],
              D_800BEDE8[0], D_800BEDE8[1], (int)D_800BE9C0); /* vbe TU: plain accesses are game memory */
    port_cam_probe(task);
}

/* P26: camera / view-matrix state and the P24 / P22 runtime checks (logged with ?dlstat=N).
 *   VIEW  D_800DC6D0[2]: per DL buffer, player view matrices (allocated by asm func_15005290, filled by
 *         asm func_1512C490 via func_15047E70 + guMtxCatL); the frame DL multiplies them onto the projection.
 *   CAMREC D_800BE628: camera records (0x180 per player); +0x100 + buf * 0x40 = projection Mtx, written by
 *         func_1510BB78 (guPerspectiveF + guMtxF2L) from asm func_1510B6A8 / func_1510B9D8 or the request
 *         queue D_800D9F18 drained by func_1510BA9C.
 *   CAM   D_800DBFF0: struct108 camera-controller records (0x9A0 each, func_15122AE0 / func_15122C5C). */
struct PendingF2_ { float x, y; };
extern unsigned D_800DC6D0[2], D_800DBFF0, D_800DDD64;
extern int D_800BE628, D_80082FA0, D_800D2DB4, D_80041C30[3];
extern unsigned D_800417B0[3];
extern unsigned char D_800DE1BB, D_800DE1BC, D_800C35EA;
extern struct PendingF2_ D_800D9F18[];
extern int D_800BE9F0; extern unsigned D_800CC2D0[];
extern float D_800D9F40, D_800D9F3C, D_800C3A70, D_800C3A74, D_800C3A6C;
void port_cam_probe(unsigned task) {
    int buf = D_800BE9C0 & 1;
    unsigned *proj = D_800BE628 ? (unsigned *)(D_800BE628 + 0x100 + buf * 0x40) : 0;
    unsigned *view = D_800DC6D0[buf] ? (unsigned *)D_800DC6D0[buf] : 0;
    port_glog("[cam] task %u: players %d VIEW %08X %08X CAM %08X CAMREC %08X proj w0,w2,w5,w13 %08X %08X %08X %08X "
              "view w0,w2 %08X %08X req0 %08X BEAC0 %u C35EA %u D2DB4 %d\n", task, D_80082FA0, D_800DC6D0[0], D_800DC6D0[1],
              D_800DBFF0, D_800BE628, proj ? proj[0] : 0, proj ? proj[2] : 0, proj ? proj[5] : 0, proj ? proj[5 + 8] : 0,
              view ? view[0] : 0, view ? view[2] : 0, *(unsigned *)&D_800D9F18[0].x, D_800BEAC0, D_800C35EA, D_800D2DB4);
    port_glog("[chk] task %u: music players %08X %08X %08X beat C30 %d %d %d | FAD4 DE1BB %u DE1BC %u | E7FC DDD64 %08X\n",
              task, D_800417B0[0], D_800417B0[1], D_800417B0[2], D_80041C30[0], D_80041C30[1], D_80041C30[2],
              D_800DE1BB, D_800DE1BC, D_800DDD64);
    if (D_800BE628) { /* P31: camera record 0 as floats, 0x00..0xB4 (fov 0x6C..0x78, scale 0x84) */
        const float *f = (const float *)D_800BE628;
        int k;
        for (k = 0; k < 0xB8 / 4; k += 8)
            port_glog("[camrec] +%02X: %g %g %g %g %g %g %g %g\n", k * 4, f[k], f[k + 1], f[k + 2], f[k + 3],
                      f[k + 4], f[k + 5], f[k + 6], f[k + 7]);
        if (D_800DBFF0) {
            const unsigned char *cp = (const unsigned char *)D_800DBFF0;
            const float *ob = *(float *const *)(cp + 0x3D4);
            const int *vw = D_800DC6D0[buf] ? (const int *)D_800DC6D0[buf] : 0;
            port_glog("[camobj] 2C %08X 23C %u 23D %u obj %08X eye %g %g %g at %g %g %g | 2F8 %g %g %g 2BC %g %g %g"
                      " | view %08X %08X %08X %08X %08X %08X %08X %08X\n", *(const int *)(cp + 0x2C), cp[0x23C],
                      cp[0x23D], (unsigned)ob, ob ? ob[0x13C / 4] : 0, ob ? ob[0x140 / 4] : 0, ob ? ob[0x144 / 4] : 0,
                      ob ? ob[0x148 / 4] : 0, ob ? ob[0x14C / 4] : 0, ob ? ob[0x150 / 4] : 0,
                      *(const float *)(cp + 0x2F8), *(const float *)(cp + 0x2FC), *(const float *)(cp + 0x300),
                      *(const float *)(cp + 0x2BC), *(const float *)(cp + 0x2C0), *(const float *)(cp + 0x2C4),
                      vw ? vw[0] : 0, vw ? vw[1] : 0, vw ? vw[2] : 0, vw ? vw[3] : 0, vw ? vw[8] : 0, vw ? vw[9] : 0,
                      vw ? vw[10] : 0, vw ? vw[11] : 0);
        }
        port_glog("[camlvl] level D_800BE9F0 %d D_800CC2D0 %08X %08X\n", D_800BE9F0, D_800CC2D0[0], D_800CC2D0[1]);
        { /* P37: camera target = the character record at player object 0 + 0x31C (func_15082E44 sets it for character
           * slots), the enabled-player mask D_800D2340, the character func_150859AC(0, 1), the slot count D_8008FD8C,
           * the setup entry count D_800D2520 and the spawned flag of entry 0 (D_800D252C[0]). */
            extern s16 D_800D2340; extern s8 D_8008FD8C; extern u8 D_800D2520; extern u8 *D_800D252C;
            extern u8 *D_800D20FC;
            s32 func_150859AC(s16, s32);
            u8 *e = D_800D20FC;
            port_glog("[camtgt] level %d: D_800CC2D0[0]+0x31C = %08X, mask D_800D2340 %04X, slots %d, char(0) %d, setup entries %d, "
                      "entry0 type %02X placeholder %d spawned %d\n", D_800BE9F0, *(unsigned *)((u8 *)D_800CC2D0 + 0x31C),
                      (u16)D_800D2340, D_8008FD8C, func_150859AC(0, 1), D_800D2520, e ? e[4] : 0, e ? e[2] : 0,
                      D_800D252C ? D_800D252C[0] : -1);
        }
        port_glog("[camrec] screen D_800D9F40 %g D_800D9F3C %g C3A70 %g C3A74 %g C3A6C %g\n", D_800D9F40, D_800D9F3C,
                  D_800C3A70, D_800C3A74, D_800C3A6C);
    }
}

/* P37: the P31 TEMPORARY overrides func_1501A8C0 (camera record), func_150031EC / func_15003120 (level model
 * loader), func_150479F0 (lookat) and the P31 diagnostic func_150A5858 were removed: the port branch converted
 * all of them in P34 (game_476D0.c, game_305D0.c, game_eu_71E70.c, game_eu_D2DB0.c). ?dlapprox=1 is now a
 * link-time wrapper of the game's C func_150A5858 (port/gfx/gfx_f3dex2.c, -Wl,--wrap). */

/* P39: the ?camwatch write watch lives in port/gfx/gfx_f3dex2.c (a host TU: port_flag / %s need host strings). */

/* P52: the P49 TEMPORARY overrides func_15059C84 (position integrator) and func_1504C0E8 (partial animation
 * choice) were removed: the port-b branch converted both in P50 (game_83300.c, game_eu_78230.c, NON_MATCHING). */

/* P66: the TEMPORARY PC func_150A9B0C (P58), func_150A9E64 and func_150844AC (P61) were removed: the port branch
 * converted all three in P62 (nm_asm/D5E90_mtx.c, game_eu_AF2A0.c, NON_MATCHING). */

/* P63: TEMPORARY PC func_1502AF04 (game_57FA0.c, asm, 76 lines; remove when the port branch converts it). The
 * animation header lookup of func_1505E0C4 (object model +0x58 path) and the last step of func_1502B110 (the
 * other path): reads n 8-byte records {offset, size} at base + index * 8 from ROM and makes their first words
 * absolute (+= base). As a gen_stubs stub it returned base itself, so func_1505E0C4 read garbage / no header and
 * Conker stayed in the bind pose. Read from the asm:
 *   src = base + index * 8;  dst = (buf + 8) & ~15;
 *   func_10004514(src & ~15, dst, ((src & 0xE) + n * 8 + 15) & ~15, 1);
 *   rec = dst + (src & 0xF);  for i < n: rec[2 * i] += base;  return rec. */
s32 func_10004514(s32, void *, u32, s32);
s32 func_1502AF04(s32 base, s32 buf, s32 index, s32 n) {
    u32 src = (u32)base + (u32)index * 8;
    u32 dst = ((u32)buf + 8) & ~15u;
    s32 *rec;
    s32 i;

    func_10004514(src & ~15u, (void *)dst, ((src & 0xE) + (u32)n * 8 + 15) & ~15u, 1);
    rec = (s32 *)(dst + (src & 0xF));
    for (i = 0; i < n; i++) {
        rec[i * 2] += base;
    }
    return (s32)rec;
}

/* P63: TEMPORARY PC func_150A69E0 (game_eu_D3880.c, asm, 13 instructions; remove when the port branch converts it):
 *   return func_150A6A48(a0, a1, a2, a3, a0, a1, -10000, 20000);
 * (the asm stores a0 / a1 / -10000 / 0x4E20 as the 5th..8th stack arguments and jumps to the C func_150A6A48). Its
 * caller func_15045A04 (game_eu_71E70.c) passes a2 = &count; as a gen_stubs stub the count stayed uninitialised
 * stack, and func_1504627C -> func_150A49D0(count, ...) walked a garbage id list: a "memory access out of bounds"
 * that came and went with the stack layout (seen in P63 with ?p49walk, frame 723). */
s32 func_150A6A48(s32, s32, s32 *, s32, s32, s32, s32, s32);
s32 func_150A69E0(s32 a0, s32 a1, s32 a2, s32 a3) {
    return func_150A6A48(a0, a1, (s32 *)a2, a3, a0, a1, -10000, 20000);
}

/* P63: TEMPORARY PC func_1510E908 (game_eu_13B700.c, asm, 188 lines; remove when the port branch converts it). The
 * floor-slope solver behind func_1510FDA0 (P60's func_15051558 floor push): for the floor triangle given either as
 * 3 vertex pointers (tris, s16 x/y/z each) or, when tris is NULL, as 3 packed s16 x/y/z vertices (verts, stride 6,
 * the record's +0x18C copy), it tries the edge pairs (P1 = v[i], P0 = v[i+1], P2 = v[i+2], i = 0..2, then the same
 * three with the two edges swapped) until one gives a non-degenerate system, and returns
 *   *outB = (e2.x * e1.y - e1.x * e2.y) / (e2.x * e1.z - e1.x * e2.z),  *outA = (e2.y - *outB * e2.z) / e2.x
 * (e1 = P0 - P1, e2 = P2 - P1), result 1; all degenerate (or the 6th try reached), or both inputs NULL: 0 / 0, result
 * 0. As a gen_stubs stub it wrote nothing, so func_1510FDA0's dx / dz were stack leftovers: on the flat start floor
 * of level 0x21 func_15051558 saw a "strong push" (dx^2 + dz^2 > 1) every frame, started a slide (D_800CC69C = 1,
 * +0x110 = 3, animation 0x28E) and pushed the player off the level (P63). Read from the asm instruction by instruction
 * (the 6th try forces "fail" even when it is not degenerate, as the asm does). */
s32 func_1510E908(s32 tris, s32 verts, f32 *outA, f32 *outB) {
    s32 t = 0, ok, i0, i1, i2, first;
    f32 e1x, e1y, e1z, e2x, e2y, e2z, sw, p, q;
    const s16 *P0, *P1, *P2;

    if (tris == 0 && verts == 0) {
        *outB = 0.0f;
        *outA = 0.0f;
        return 0;
    }
    for (;;) {
        ok = 1;
        i0 = (t < 3) ? t : t - 3;
        first = t < 3;
        i1 = (i0 == 2) ? 0 : i0 + 1;
        t++;
        i2 = (i1 == 2) ? 0 : i1 + 1;
        if (verts != 0) {
            P0 = (const s16 *)(verts + i1 * 6);
            P1 = (const s16 *)(verts + i0 * 6);
            P2 = (const s16 *)(verts + i2 * 6);
        } else {
            P0 = ((const s16 **)tris)[i1];
            P1 = ((const s16 **)tris)[i0];
            P2 = ((const s16 **)tris)[i2];
        }
        e1x = (f32)(P0[0] - P1[0]);
        e1y = (f32)(P0[1] - P1[1]);
        e1z = (f32)(P0[2] - P1[2]);
        e2x = (f32)(P2[0] - P1[0]);
        e2y = (f32)(P2[1] - P1[1]);
        e2z = (f32)(P2[2] - P1[2]);
        if (!first) {
            sw = e1x; e1x = e2x; e2x = sw;
            sw = e1y; e1y = e2y; e2y = sw;
            sw = e1z; e1z = e2z; e2z = sw;
        }
        p = e1x * e2z;
        q = e2x * e1z;
        if (p == q) ok = 0;
        if (e2x == 0.0f) ok = 0;
        if (t == 6) ok = 2;
        if (ok != 0) break;
    }
    if (ok == 2) {
        *outA = 0.0f;
        *outB = 0.0f;
        return 0;
    }
    *outB = (e2x * e1y - e1x * e2y) / (q - p);
    *outA = (e2y - *outB * e2z) / e2x;
    return 1;
}
