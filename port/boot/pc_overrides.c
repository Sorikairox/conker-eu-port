/* PC replacements for game functions that cannot be C in the decomp (session P8; list from
 * docs/port/sessions/P5.md, "PC-replacement needed"). They stay GLOBAL_ASM in conker/src_eu; the
 * port's definitions here replace the weak asm stubs (port/tools/gen_stubs.py). This TU goes through
 * the vbe IR pass like the game TUs (port/Makefile BOOT_SRC), so game memory is accessed with N64
 * semantics: D_80088950 below is a big-endian u64 in virtual big-endian memory.
 *
 *   func_100061F8  handwritten TLB loop (init_eu_5DA0.c)
 *   func_150ADA20  libultra guRandom on 64-bit registers (game_DAE50.c)
 *   func_15059C84  P49 TEMPORARY: position integrator of the walk handler (game_83300.c; remove when converted)
 *   func_1504C0E8  P49 TEMPORARY, PARTIAL: prefix of the walk handler's animation choice (game_eu_78230.c)
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

/* P49 TEMPORARY: func_15059C84 (game_83300.c, GLOBAL_ASM, 341 lines), the per-frame position integrator of the
 * player walk handler func_1504CB98 (P47). With the asm stub the walk handler set the speed (+0x3C rises to 35)
 * and the heading (+0x76), but x / z never changed. This is an instruction-by-instruction C version of the asm,
 * written in the port only so movement can be observed; REMOVE it when the port branch converts the function
 * (the faithful order below is a good starting point for its NON_MATCHING body). Not difftested.
 *   - D_800D1968 == 1: return.  +0x1FC bit 8: clear it, return.
 *   - +0x127 != 0xFF and unk31C+0x46 (s16) > 0: heading = +0x76 + unk31C+0x10 (u16), also stored to +0x7A.
 *   - 0 <= speed < 1 and !(+0x1FC & 1): +0x7E counts up to 0xFA; if the push vectors +0x164..+0x170 are all 0,
 *     +0x1F4 = 0 and return. Otherwise +0x7E = 0.
 *   - pitch (a2 of func_1505A184) = clamp(+0xB8, -90, 90) when (+0x22C & 8), or in water with unk31C+0x21 != 0
 *     (or no unk31C); else 0.
 *   - +0x1FC bit 1: clear it, speed = 2 * (+0x1F4 * +0x14C / D_800D1550[0]) (if the frame scale is not 0),
 *     heading = +0x7A.  +0x1F4 = speed.
 *   - func_1505A184(heading, speed, pitch, &dx, &dz, &dy); dx += +0x164 + +0x16C; dz += +0x168 + +0x170;
 *     +0xAD == 10: dy = 0.
 *   - slope: on the ground (+0x28 <= 0), not in water, !(+0x22C & 8), and (state != 1 or unk31C+0x4F == 0): the
 *     floor triangle (s16 x3 x3 at +0x18C) -> func_15049350 -> normal D_800CC630/634/638; if ny != 0,
 *     dy' = (-nx dx - nz dz) / ny and, unless (dy' <= 4 and state 1 and unk31C+0x4E == 2), (dx, dy', dz) is
 *     rescaled to the horizontal length.
 *   - pos += (dx, dy, dz) * D_800D1550[0]. */
extern s32 D_800D1968;
extern f32 D_800D1550[];
extern f32 D_800CC630, D_800CC634, D_800CC638;
void func_1505A184(u16, f32, f32, f32 *, f32 *, f32 *);
void func_15049350(s32, f32, f32, f32, f32, f32, f32, f32, f32);
s32 func_15059C84(u8 *r) {
#define RF(o) (*(f32 *)(r + (o)))
    u8 *u;
    f32 speed = RF(0x3C), f0 = speed, pitch, dx, dz, dy, ny, nd, h2, tot, h;
    u16 yaw = *(u16 *)(r + 0x76);
    u8 v;
    f32 tri[9];
    s32 i;
    if (D_800D1968 == 1) return 0;
    v = r[0x1FC];
    if (v & 8) { r[0x1FC] = v & 0xF7; return 0; }
    if (r[0x127] != 0xFF) {
        u = *(u8 **)(r + 0x31C);
        if (*(s16 *)(u + 0x46) > 0) {
            yaw = yaw + *(u16 *)(u + 0x10);
            f0 = RF(0x3C);
            *(u16 *)(r + 0x7A) = yaw;
        }
    }
    if (f0 < 1.0f && 0.0f <= f0 && !(r[0x1FC] & 1)) {
        if (r[0x7E] < 0xFA) r[0x7E] = r[0x7E] + 1;
        if (RF(0x164) == 0.0f && RF(0x168) == 0.0f && RF(0x16C) == 0.0f && RF(0x170) == 0.0f) {
            RF(0x1F4) = 0.0f;
            return 0;
        }
    } else {
        r[0x7E] = 0;
    }
    u = *(u8 **)(r + 0x31C);
    if ((r[0xAD] != 0 && (u == NULL || u[0x21] == 0)) || (*(u16 *)(r + 0x22C) & 8)) {
        pitch = RF(0xB8);
        if (90.0f < pitch) pitch = 90.0f;
        else if (pitch < -90.0f) pitch = -90.0f;
    } else {
        pitch = 0.0f;
    }
    v = r[0x1FC];
    if (v & 1) {
        r[0x1FC] = v & 0xFE;
        if (D_800D1550[0] != 0.0f) speed = (RF(0x1F4) * RF(0x14C)) / D_800D1550[0] * 2.0f;
        yaw = *(u16 *)(r + 0x7A);
    }
    RF(0x1F4) = speed;
    dx = pitch;
    func_1505A184(yaw, speed, pitch, &dx, &dz, &dy);
    dx = dx + (RF(0x164) + RF(0x16C));
    dz = dz + (RF(0x168) + RF(0x170));
    if (r[0xAD] == 10) dy = 0.0f;
    if (!(*(s32 *)r == 1 && (*(u8 **)(r + 0x31C))[0x4F] != 0) && RF(0x28) <= 0.0f && r[0xAD] == 0 &&
        !(*(u16 *)(r + 0x22C) & 8)) {
        for (i = 0; i < 9; i++) tri[i] = (f32) *(s16 *)(r + 0x18C + i * 2);
        func_15049350(*(s32 *)&tri[0], tri[1], tri[2], tri[3], tri[4], tri[5], tri[6], tri[7], tri[8]);
        ny = D_800CC634;
        if (ny != 0.0f) {
            nd = ((-D_800CC630 * dx) - (D_800CC638 * dz)) / ny;
            if (4.0f < nd || *(s32 *)r != 1 || (*(u8 **)(r + 0x31C))[0x4E] != 2) {
                h2 = dx * dx + dz * dz;
                tot = sqrtf(h2 + nd * nd);
                if (tot != 0.0f) {
                    h = sqrtf(h2);
                    dx = dx * h / tot;
                    dy = nd * h / tot;
                    dz = dz * h / tot;
                }
            }
        }
    }
    dx = dx * D_800D1550[0];
    dz = dz * D_800D1550[0];
    dy = dy * D_800D1550[0];
    RF(0x14) = RF(0x14) + dx;
    RF(0x1C) = RF(0x1C) + dz;
    RF(0x18) = RF(0x18) + dy;
    return 0;
#undef RF
}

/* P49 TEMPORARY, PARTIAL: func_1504C0E8 (game_eu_78230.c, GLOBAL_ASM, 531 lines), the walk handler's last call
 * (animation choice). Only its prefix is here, up to the first animation call; the rest (func_15064F50,
 * func_1505E650, func_1504C078 / func_1504C0B8 ...) is NOT done. Why: with the stub, record +0x80 was never set,
 * so func_150599C8 never turned the body yaw +0x7A toward the heading +0x76; it then returned an angle >= 0x5B
 * and the walk handler cut the target speed to 0 whenever +0x3C > 12 (speed saw-toothed 7..14 instead of 35).
 *   - unk31C+0x12 (s16) eases toward D_800CC6D2 (snaps to 0 when D_800CC6D2 == 0 and |+0x12| is small);
 *   - unk31C+0x6B != 0: return;  +0x65 != 0 and not stunned: (func_15064DD0, not called here) return;
 *   - on the ground path (+0x81, +0x104, +0xAD, +0x83 all 0, unk31C+0x11A != 3): +0x80 = 1, +0x100 &= 0xF3,
 *     D_800CC6DC |= 0x80.  REMOVE when the port branch converts func_1504C0E8. */
extern s16 D_800CC6D2;
extern f32 D_800CC6D4;
extern s32 D_800CC6DC;
s32 func_1504C0E8(u8 *r, s32 arg1, f32 arg2) {
    u8 *u = *(u8 **)(r + 0x31C);
    s16 a2 = D_800CC6D2, v = *(s16 *)(u + 0x12);
    (void)arg1;
    (void)arg2;
    if (a2 == 0 && !(v < -0x1D) && v < 0x1E) {
        *(s16 *)(u + 0x12) = 0;
    } else {
        *(s16 *)(u + 0x12) = v + (s32)((D_800D1550[0] / D_800CC6D4) * (f32)(a2 - v));
    }
    u = *(u8 **)(r + 0x31C);
    if (u[0x6B] != 0) return 0;
    if (r[0x65] != 0 && r[0x104] == 0) return 0;
    if (r[0x81] != 0 || r[0x104] != 0 || r[0xAD] != 0 || r[0x83] != 0 || u[0x11A] == 3) return 0;
    r[0x80] = 1;
    r[0x100] = r[0x100] & 0xF3;
    D_800CC6DC |= 0x80;
    return 0;
}
