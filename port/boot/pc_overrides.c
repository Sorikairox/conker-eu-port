/* PC replacements for game functions that cannot be C in the decomp (session P8; list from
 * docs/port/sessions/P5.md, "PC-replacement needed"). They stay GLOBAL_ASM in conker/src_eu; the
 * port's definitions here replace the weak asm stubs (port/tools/gen_stubs.py). This TU goes through
 * the vbe IR pass like the game TUs (port/Makefile BOOT_SRC), so game memory is accessed with N64
 * semantics: D_80088950 below is a big-endian u64 in virtual big-endian memory.
 *
 *   tlb_clear_entries  handwritten TLB loop (init_eu_5DA0.c)
 *   (random_int guRandom: game C since port P106, removed here in P110)
 *   (the TEMPORARY P58 / P61 / P63 versions were removed in P66 and P69; none are left)
 */
#include <ultra64.h>

/* tlb_clear_entries(lo, hi): for index = hi down to lo: Index = index, EntryHi = 0x80000000 (KSEG0, never
 * matched), EntryLo0/1 = 0, tlbwi; EntryHi is restored afterwards. That invalidates TLB entries
 * lo..hi. The PC build has no TLB: code is native wasm and the TLB-mapped data segment
 * (0x16000000) is the n64_seg16 mirror, which port_n64_to_wasm resolves statically. So this is a
 * no-op. Called once at boot (1, 31) and once per frame by the main loop. The asm leaves v0 as it
 * was; callers ignore it (one call-site signature, i32(i32,i32) in sigdb.json). */
s32 tlb_clear_entries(s32 lo, s32 hi) {
    (void)lo;
    (void)hi;
    return 0;
}

/* P110: random_int (guRandom on a u64 seed) was removed here: port P106 wrote the same formula as C in
 * game_DAE50.c (NM), which caused a duplicate symbol. The self-test below now checks the game C. */
extern u64 D_80088950;
s32 random_int(void);

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
        u32 got = (u32)random_int();
        if (got != want[i]) { port_log("[overrides] guRandom step %d: %08X, want %08X\n", i, got, want[i]); bad++; }
    }
    if (D_80088950 != 0xA90FD6A5ULL) { port_log("[overrides] seed after 3 steps wrong\n"); bad++; }
    D_80088950 = saved;
    if (bad) port_log("[overrides] guRandom FAIL (%d failures)\n", bad);
    else port_log("[overrides] guRandom PASS (0 failures)\n");
    return bad;
}

/* ROM-offset symbols (session P9): &D_1A3B40 must be the texture bank's ROM offset, not a wasm
 * address (port/tools/vbe.py ROM_ABS). The game's own C texture_rom_offset (game_eu_13A8A0.c) computes
 * texture 0xED0's ROM offset; a PI DMA of the first 16 bytes there must give the bytes Python reads
 * from the ROM at 0x6F1618 (rzip header: BE u32 size 0x300, then DEFLATE). D_800B8BB8 is the
 * inflated-size table that texture_build_size_table (game_305D0.c, C) builds from the same bank by DMA. */
s32 texture_rom_offset(s32 id);
extern s16 D_800B8BB8[];
int port_romsym_test(void) {
    static const u8 want[16] = {0x00, 0x00, 0x03, 0x00, 0xED, 0x4F, 0x21, 0x56,
                                0x43, 0x31, 0x10, 0xFC, 0x9B, 0x6C, 0x36, 0xBB};
    static u8 buf[16];
    u32 rom = (u32)texture_rom_offset(0xED0);
    int bad = 0, i;
    if (rom != 0x6F1618) { port_log("[romsym] texture_rom_offset(0xED0) = 0x%X, want 0x6F1618\n", rom); bad++; }
    osPiRawStartDma(OS_READ, rom, buf, 16);
    for (i = 0; i < 16; i++) bad += buf[i] != want[i];
    port_log("[romsym] tex 0xED0 @ROM 0x%X: %02X%02X%02X%02X %02X%02X%02X%02X, size table %d\n", rom,
             buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7], D_800B8BB8[0xED0]);
    if (bad) port_log("[romsym] FAIL (%d failures)\n", bad); /* %s args would be vbe strings */
    else port_log("[romsym] PASS (0 failures)\n");
    return bad;
}

/* P19: the P11 TEMPORARY overrides of world_update and gfx_task_submit were removed: both are
 * NON_MATCHING C on the port branch since P15-P17 (game_45B80.c, game_eu_4A070.c). */

/* P23: the P19 TEMPORARY overrides of asset_load_alloc, asset_relocate_subfiles and quadtree_filter_box_tris were removed:
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
 *   VIEW  D_800DC6D0[2]: per DL buffer, player view matrices (allocated by asm camera_level_init, filled by
 *         asm camera_build_view_matrix via mtx_look_at_reflect + guMtxCatL); the frame DL multiplies them onto the projection.
 *   CAMREC D_800BE628: camera records (0x180 per player); +0x100 + buf * 0x40 = projection Mtx, written by
 *         camera_perspective_build (guPerspectiveF + guMtxF2L) from asm camera_projection_update / camera_projection_set_viewport or the request
 *         queue D_800D9F18 drained by camera_projection_apply_pending_viewport.
 *   CAM   D_800DBFF0: struct108 camera-controller records (0x9A0 each, camera_update_all / camera_update_controller). */
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
        { /* P37: camera target = the character record at player object 0 + 0x31C (setup_entry_spawn sets it for character
           * slots), the enabled-player mask D_800D2340, the character player_stat_get(0, 1), the slot count D_8008FD8C,
           * the setup entry count D_800D2520 and the spawned flag of entry 0 (D_800D252C[0]). */
            extern s16 D_800D2340; extern s8 D_8008FD8C; extern u8 D_800D2520; extern u8 *D_800D252C;
            extern u8 *D_800D20FC;
            s32 player_stat_get(s16, s32);
            u8 *e = D_800D20FC;
            port_glog("[camtgt] level %d: D_800CC2D0[0]+0x31C = %08X, mask D_800D2340 %04X, slots %d, char(0) %d, setup entries %d, "
                      "entry0 type %02X placeholder %d spawned %d\n", D_800BE9F0, *(unsigned *)((u8 *)D_800CC2D0 + 0x31C),
                      (u16)D_800D2340, D_8008FD8C, player_stat_get(0, 1), D_800D2520, e ? e[4] : 0, e ? e[2] : 0,
                      D_800D252C ? D_800D252C[0] : -1);
        }
        port_glog("[camrec] screen D_800D9F40 %g D_800D9F3C %g C3A70 %g C3A74 %g C3A6C %g\n", D_800D9F40, D_800D9F3C,
                  D_800C3A70, D_800C3A74, D_800C3A6C);
    }
}

/* P37: the P31 TEMPORARY overrides camera_record_setup (camera record), level_load_models / level_model_relocate_table (level model
 * loader), mtxf_look_at_reflect (lookat) and the P31 diagnostic level_dl_visibility_filter were removed: the port branch converted
 * all of them in P34 (game_476D0.c, game_305D0.c, game_eu_71E70.c, game_eu_D2DB0.c). ?dlapprox=1 is now a
 * link-time wrapper of the game's C level_dl_visibility_filter (port/gfx/gfx_f3dex2.c, -Wl,--wrap). */

/* P39: the ?camwatch write watch lives in port/gfx/gfx_f3dex2.c (a host TU: port_flag / %s need host strings). */

/* P52: the P49 TEMPORARY overrides obj_update_ground_tilt (position integrator) and walk_select_move_anim (partial animation
 * choice) were removed: the port-b branch converted both in P50 (game_83300.c, game_eu_78230.c, NON_MATCHING). */

/* P66: the TEMPORARY PC func_150A9B0C (P58), func_150A9E64 and obj_model_vertex_blocks_get (P61) were removed: the port branch
 * converted all three in P62 (nm_asm/D5E90_mtx.c, game_eu_AF2A0.c, NON_MATCHING). */

/* P69: the TEMPORARY PC asset_rec_fetch_block, world_objects_at_point and floor_triangle_slope (P63) were removed: the port branch
 * converted all three in P65 (game_57FA0.c, game_eu_D3880.c, game_eu_13B700.c, NON_MATCHING). */

/* P88: the TEMPORARY PC settings_clamp_to_range (P84, settings clamp) was removed: the port branch converted it in P85
 * (game_eu_20B730.c, NON_MATCHING, void (void)). */

/* P205: the P199 --wrap of object_state_dispatch_a / object_state_dispatch_b (dropped object argument of the D_80089AAC / D_80089AD4
 * handlers) was removed: port P200 made the NON_MATCHING game C (game_161520.c) pass the object and return the
 * handler's result. ?p199nowrap is gone with it. */
