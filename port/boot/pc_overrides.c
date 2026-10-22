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
        port_glog("[camrec] screen D_800D9F40 %g D_800D9F3C %g C3A70 %g C3A74 %g C3A6C %g\n", D_800D9F40, D_800D9F3C,
                  D_800C3A70, D_800C3A74, D_800C3A6C);
    }
}

/* P31, TEMPORARY until the port branch converts it: func_1501A8C0 (game_476D0.c, asm, 379 lines),
 * the per-player camera record init, called by the C func_1501A220 at level start as
 * func_1501A8C0(player, players - 1, 0x3FF, 0). Without it the record D_800BE628 + p * 0x180 stays zero
 * (field of view 0, scale 0) and guPerspectiveF in func_1510BB78 gives inf * 0 = NaN -> a saturated
 * projection. Written instruction by instruction from the asm (symbols here are the asm's names, which the
 * link maps to the EU addresses like the asm build does). Offsets: +4/+8 viewport w/h, +0xC/+0x10 half
 * w/h, +0x14/+0x18 scale x/y, +0x24..0x30 clip rect, +0x34/+0x38 centre, +0x40 Vp[2], +0x60 aspect,
 * +0x64/+0x68, +0x6C/+0x70 base fov x/y (degrees), +0x74/+0x78 fov, +0x7C/+0x80, +0x84 projection scale. */
extern s32 D_800BEA58[], D_800BEA70[], D_800BEA4C;
extern f32 D_80083338[], D_800BEAD8, D_80096C94, D_80096C98, D_80096C9C, D_80096CA0;
extern s16 D_800BEA88[];
extern u8 D_800BEA50[];
s32 func_1501AE94(s32);
void func_1501AF44(f32 *, f32 *, f32 *, f32 *);
void func_1501B0A0(s32, s32);
void func_1510B8AC(s32, f32, f32, f32);
float sinf(float);
float cosf(float);
s32 func_1501A8C0(s32 p, s32 n, s32 a2, s32 a3) {
#define CF(o) (*(f32 *)((u8 *)D_800BE628 + p * 0x180 + (o)))
    s16 *t, *vp;
    s32 *src, *dst;
    f32 a, s, c, f0, f2, f4, f6;
    s32 buf, k;

    CF(4) = (f32)D_800BEA58[n];
    CF(8) = (f32)D_800BEA70[n];
    if (n != 0) {
        CF(4) = CF(4) - 2.0f;
        CF(8) = CF(8) - 2.0f;
    }
    CF(0x64) = D_80083338[n];
    CF(0x68) = 2.0f;
    if (n == 1) {
        CF(4) = CF(4) * D_800BEAD8;
        CF(0x6C) = D_80096C94 * D_800BEAD8;
        CF(0x70) = 50.0f;
    } else {
        CF(0x6C) = D_80096C98;
        CF(0x70) = 50.0f;
    }
    CF(0x74) = CF(0x6C);
    CF(0x78) = CF(0x70);
    CF(0x60) = CF(4) / CF(8);
    CF(0xC) = CF(4) * 0.5f;
    CF(0x10) = CF(8) * 0.5f;
    t = (s16 *)((u8 *)D_800BEA88 + n * 20 + p * 4);
    CF(0x34) = (f32)t[0];
    CF(0x38) = (f32)t[1];
    CF(0x2C) = CF(0x34) - CF(0xC);
    CF(0x24) = CF(0x38) - CF(0x10);
    CF(0x30) = CF(0xC) + CF(0x34);
    CF(0x28) = CF(0x10) + CF(0x38);
    if ((s16)a3 != 0) {
        func_1501B0A0(p, n);
    } else {
        f2 = (f32)D_800BEA58[0];
        f4 = (f32)D_800BEA70[0];
        f0 = CF(4);
        f6 = CF(8);
        CF(0x14) = (f0 / f2) * ((f2 / f4) / (f0 / f6));
        CF(0x18) = CF(8) / f4;
    }
    a = CF(0x6C) * 0.5f * D_80096C9C;
    s = sinf(a);
    c = cosf(a);
    CF(0x7C) = s / (CF(0xC) * c);
    a = CF(0x70) * 0.5f * D_80096CA0;
    s = sinf(a);
    c = cosf(a);
    CF(0x80) = s / (CF(0x10) * c);
    vp = (s16 *)(D_800BEA4C + p * 16);
    vp[0] = (s32)((CF(4) + 10.0f) + (CF(4) + 10.0f));
    vp[1] = (s32)((CF(8) + 10.0f) + (CF(8) + 10.0f));
    vp[2] = a2 >> 1;
    vp[3] = 0;
    vp[4] = (s32)(CF(0x34) * 4.0f);
    vp[5] = (s32)(CF(0x38) * 4.0f);
    vp[6] = a2 >> 1;
    vp[7] = 0;
    buf = D_800BE9C0;
    src = (s32 *)vp;
    dst = (s32 *)((u8 *)D_800BE628 + p * 0x180 + 0x40 + buf * 16);
    for (k = 0; k < 4; k++) dst[k] = src[k];
    buf = D_800BE9C0;
    src = (s32 *)((u8 *)D_800BE628 + p * 0x180 + 0x40 + buf * 16);
    dst = (s32 *)((u8 *)D_800BE628 + p * 0x180 + 0x40 + (buf == 0) * 16);
    for (k = 0; k < 4; k++) dst[k] = src[k];
    CF(0x84) = 1.0f;
    *((u8 *)D_800BE628 + p * 0x180 + 1) = (u8)func_1501AE94(p);
    func_1501AF44(&CF(0x2C), &CF(0x24), &CF(0x30), &CF(0x28));
    func_1510B8AC(p, 0.0f, 0.0f, CF(0x84));
    D_800BEA50[p] = (u8)p;
    return 0;
#undef CF
}

/* P31 DIAGNOSTIC, not a conversion: func_150A5858 (game_eu_D2DB0.c, hand-written asm with private register
 * conventions, 228 lines + helpers) is the level-geometry visibility walk: it culls the node tree D_800DC278
 * against the view (a2 = D_800DA030[player]) and emits the visible parts of the level DL a0 = D_800B0E00[0].
 * The weak stub returns a1 (gdl) unchanged. With ?dlapprox=1 (PORT_FLAG=dlapprox=1) this instead emits
 * gSPDisplayList(a0), which is exactly what the C caller func_1510BF50 itself does for levels 0x14/0x32/0x33:
 * the whole level DL, no culling. Default (flag 0): identical to the stub. */
int port_flag_dlapprox(void);
Gfx *func_150A5858(s32 dl, Gfx *gdl, u8 *mtx, s32 a3, s32 a4, s32 mask) {
    (void)mtx; (void)a3; (void)a4; (void)mask;
    { static int n; if (n++ < 2) port_glog("[dlapprox] func_150A5858 dl %08X gdl %08X mask %X flag %d\n", dl, (u32)gdl, mask, port_flag_dlapprox()); }
    if (port_flag_dlapprox() && dl != 0) {
        gdl->words.w0 = 0xDE000000;
        gdl->words.w1 = (u32)dl;
        gdl++;
    }
    return gdl;
}

/* P31, TEMPORARY until the port branch converts them: the level-model loader func_150031EC (game_305D0.c, asm,
 * 191 lines) and its helper func_15003120 (55 lines), written instruction by instruction from the asm.
 * func_150031EC(level) is called by the C func_15007B3C path (game_34F20.c:217) at level start. It loads the
 * level's model file list (func_1502B6BC asset (2, level), up to 4 levels of detail / parts), relocates each
 * model header, and sets D_800B0E00[i] (the level DL that func_1510BF50 hands to func_150A5858), D_800B1220[i]
 * (vertex base), D_800B1250[i], D_800B1230[i], then func_150049A4 / func_1510D3E0 (texture ids) and the level's
 * texture preload list D_80082EB0[D_800B0DF0->0x4B]. Without it D_800B0E00[0] stays 0: no level geometry. */
extern s32 *D_800B1240;
extern u8 *D_800B1244;
extern u8 D_800B1248;
extern s32 D_800B1214[], D_800B1224[], D_800B1254[], D_800B1260;
extern s32 D_800B0E00[], D_800B1220[], D_800B1250[], D_800B1230[];
extern u8 *D_800B0DF0;
extern s32 *D_80082EB0[];
s32 func_1502B6BC(s32 *arg0, s32 arg1, s32 *arg2, s32 arg3, ...);
s32 func_150034B4(void);
void func_150039BC(s32 arg0);
void func_150049A4(Gfx *arg0, s32 arg1, s32 arg2);
s32 func_1510D3E0(Gfx *dl, s32 skipResolved, s32 addRef, s32 age, s16 **outList);
s32 func_1510D66C(s32 id, s32 *outSize, s32 age, s32 addRef);
s32 allocate_memory(s32, s32, s32, s32);

void func_15003120(s32 idx, s32 base, s32 table) {
    s32 n, off;
    s32 *e;

    D_800B1240[idx] = table;
    D_800B1244[idx] = 0;
    if (table == 0) {
        return;
    }
    D_800B1240[idx] += base;
    n = 0;
    off = 0;
    e = (s32 *)D_800B1240[idx];
    if (e[0] != 0) {
        do {
            e = (s32 *)(D_800B1240[idx] + off);
            e[0] += base;
            n++;
            e[1] += base;
            off += 12;
            e = (s32 *)(D_800B1240[idx] + off);
        } while (e[0] != 0);
    }
    D_800B1244[idx] = n;
}

int port_flag_lvlload(void);
void func_150031EC(s32 level) {
    s32 found, count, i, k;
    s32 *list, *ent;
    u8 *hdr;
    s32 size;

    if (!port_flag_lvlload()) {
        return; /* default: the stub behaviour (P31: the second level load at VI frame 722 broke the heap in Chrome) */
    }
    if (level >= 0x45) {
        level = 0;
    }
    list = (s32 *)func_1502B6BC(&found, 0, &count, 2, 4, level);
    D_800B1260 = (s32)list;
    for (k = 0; k < 3; k++) {
        D_800B1214[k] = 0;
        D_800B1224[k] = 0;
        D_800B1254[k] = 0;
    }
    func_150034B4();
    if (found != 0) {
        D_800B1240 = (s32 *)allocate_memory(count * 4, 1, 0, 0);
        D_800B1244 = (u8 *)allocate_memory(count, 1, 0, 0);
        bzero(D_800B1244, count);
        bzero(D_800B1240, count);
        D_800B1248 = (u8)count;
        for (i = 0, ent = list; i < count; i++, ent += 2) {
            hdr = (u8 *)ent[0];
            if (hdr == NULL || ent[1] == 0) {
                continue;
            }
            if (*(s32 *)(hdr + 0x0) != 0) *(s32 *)(hdr + 0x0) += (s32)hdr;
            if (*(s32 *)(hdr + 0x8) != 0) *(s32 *)(hdr + 0x8) += (s32)hdr;
            if (*(s32 *)(hdr + 0x10) != 0) *(s32 *)(hdr + 0x10) += (s32)hdr;
            func_15003120(i, (s32)hdr, *(s32 *)(hdr + 0x20));
            if ((u32)i < 4) {
                D_800B1220[i] = (s32)(hdr + 0x28);
                D_800B0E00[i] = *(s32 *)(hdr + 0x0);
                D_800B1250[i] = (u32)(*(s32 *)(hdr + 0x0) - (s32)(hdr + 0x28)) >> 4;
                D_800B1230[i] = *(s32 *)(hdr + 0x8);
                if (i == 0) {
                    func_150039BC(*(s32 *)(hdr + 0x10));
                }
                func_150049A4((Gfx *)D_800B0E00[i], D_800B1220[i] + 0xFF000000, (s32)hdr);
                func_1510D3E0((Gfx *)D_800B0E00[i], 0, 1, 0x3F, 0);
            } else {
                func_150049A4((Gfx *)*(s32 *)(hdr + 0x0), 0, (s32)hdr);
            }
        }
    }
    k = D_800B0DF0[0x4B];
    if (k != 0) {
        s32 *tl = D_80082EB0[k];
        s32 id = tl[0];
        s32 o = 4;
        while (id != 0) {
            func_1510D66C(id, &size, 0x3E, 0);
            id = *(s32 *)((u8 *)D_80082EB0[D_800B0DF0[0x4B]] + o);
            o += 4;
        }
    }
    port_glog("[lvlload] func_150031EC level %d: found %d count %d D_800B0E00 %08X %08X %08X %08X\n", level, found,
              count, D_800B0E00[0], D_800B0E00[1], D_800B0E00[2], D_800B0E00[3]);
}

/* P31, TEMPORARY until the port branch converts it: func_150479F0 (game_eu_71E70.c, asm, 303 lines), Rare's
 * guLookAtReflectF variant used by func_15047E70 (the view matrix of func_1512C490). Written instruction by
 * instruction from the asm (not from libultra): degenerate look direction -> (0, 0, 1), degenerate right ->
 * (1, 0, 0), degenerate up -> (0, 1, 0); the LookAt bytes are min(v * 128, 127) truncated, with no lower clamp;
 * bytes 0x0B / 0x1B are not written. As a stub it left func_15047E70's float matrix uninitialised, and the frame's
 * view multiply (D_800DC6D0[buf]) was all zero. */
void guMtxIdentF(float mf[4][4]);
float sqrtf(float);
static s8 p31_lk(f32 v) {
    f32 x = v * 128.0f;
    return (s8)(s32)(x < 127.0f ? x : 127.0f);
}
void func_150479F0(f32 mf[4][4], u8 *l, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp,
                   f32 zUp) {
    f32 xL, yL, zL, xR, yR, zR, len;

    guMtxIdentF(mf);
    xL = xAt - xEye;
    yL = yAt - yEye;
    zL = zAt - zEye;
    if (xAt == xEye && yL == 0.0f && zL == 0.0f) {
        zL = 1.0f;
        xL = 0.0f;
        yL = 0.0f;
    }
    len = -1.0f / sqrtf(xL * xL + yL * yL + zL * zL);
    xL *= len;
    yL *= len;
    zL *= len;
    xR = yUp * zL - zUp * yL;
    yR = zUp * xL - xUp * zL;
    zR = xUp * yL - yUp * xL;
    len = xR * xR + yR * yR + zR * zR;
    if (len == 0.0f) {
        xR = 1.0f;
        yR = 0.0f;
        zR = 0.0f;
    } else {
        len = 1.0f / sqrtf(len);
        xR *= len;
        yR *= len;
        zR *= len;
    }
    xUp = yL * zR - zL * yR;
    yUp = zL * xR - xL * zR;
    zUp = xL * yR - yL * xR;
    len = xUp * xUp + yUp * yUp + zUp * zUp;
    if (len == 0.0f) {
        xUp = 0.0f;
        zUp = 0.0f;
        yUp = 1.0f;
    } else {
        len = 1.0f / sqrtf(len);
        xUp *= len;
        yUp *= len;
        zUp *= len;
    }
    l[0x8] = p31_lk(xR);
    l[0x9] = p31_lk(yR);
    l[0xA] = p31_lk(zR);
    l[0x18] = p31_lk(xUp);
    l[0x19] = p31_lk(yUp);
    l[0x1A] = p31_lk(zUp);
    l[0x0] = l[0x1] = l[0x2] = l[0x3] = l[0x4] = l[0x5] = l[0x6] = l[0x7] = 0;
    l[0x10] = 0; l[0x11] = 0x80; l[0x12] = 0; l[0x13] = 0;
    l[0x14] = 0; l[0x15] = 0x80; l[0x16] = 0; l[0x17] = 0;
    mf[0][0] = xR;
    mf[1][0] = yR;
    mf[0][1] = xUp;
    mf[2][0] = zR;
    mf[3][0] = -(xEye * xR + yEye * yR + zEye * zR);
    mf[2][1] = zUp;
    mf[1][1] = yUp;
    mf[0][2] = xL;
    mf[1][2] = yL;
    mf[2][2] = zL;
    mf[3][1] = -(xEye * xUp + yEye * yUp + zEye * zUp);
    mf[0][3] = 0.0f;
    mf[1][3] = 0.0f;
    mf[2][3] = 0.0f;
    mf[3][2] = -(xEye * xL + yEye * yL + zEye * zL);
    mf[3][3] = 1.0f;
}
