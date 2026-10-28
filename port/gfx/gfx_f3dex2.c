/* F3DEX2 (+ Conker's Rare extensions) display-list interpreter, WebGL2 backend.
 * Original code for this port; see gfx.h for the entry points and the memory rules.
 *
 * Model (Fast3D-style): the RSP part (matrices, vertex transform, clipping by the GPU in clip
 * space, culling, tex-coord scaling) runs here on the CPU; the RDP part (TMEM, tiles, texture
 * formats, the two-cycle colour combiner, alpha compare, z/blend modes, fill/texture rectangles)
 * maps to one generic WebGL2 shader whose combiner inputs are uniforms.
 * TMEM is emulated byte-exact (4 KB, LOADBLOCK dxt line swaps, odd-line xor on read), so any
 * load sequence the game uses decodes the way the RDP would see it. */
#include <stdint.h>
#include <string.h>
#include <stdio.h>
int port_flag(const char *name);
extern unsigned port_frame_count; /* P46: for ?lvlcol */
__attribute__((weak)) void port_frame_probe(unsigned task) { (void)task; }
#include <math.h>
#include <GLES3/gl3.h>
#include <emscripten.h>
#include "gfx.h"
#include "../ultra/pc_mem.h"

void port_log(const char *fmt, ...);

GfxStats gfx_stats;
int gfx_measure_only;
unsigned gfx_tex_unresolved_segs; /* viewer: segments whose textures the engine would resolve */
/* P351 option "High frame rate" (the hfr_* section before gfx_run_dl explains it): hfr_mode 0 = a normal task, 1 = a
 * game frame's task being drawn and recorded, 2 = that task drawn again (a replay) with interpolated matrices;
 * hfr_drop = during a replay, the colour image is not the screen (an offscreen / kept image): its draws are dropped. */
static int hfr_opt, hfr_mode, hfr_drop;
#include <emscripten/heap.h>
static unsigned char *hfr_addr_ok(unsigned char *p) {   /* 0 for an address a read of up to 8 KB could take outside memory */
    return p && (uintptr_t)p >= 0x1000 && (uintptr_t)p + 0x2000 <= emscripten_get_heap_size() ? p : 0;
}
static unsigned hfr_tgen0, hfr_tgen1;   /* tmem_gen before / after the recording */
static int hfr_fx;   /* the recorded task used the screen / kept images as textures (motion blur, pause frame, lens): no replay */

/* ------------------------------------------------------------------ addresses */
static unsigned segtab[16], segset;

/* Address classes (P8, MEMORY.md "Address space and RSP segments"); the game is linked with
 * -sGLOBAL_BASE=256MB so the classes are disjoint, without heuristics:
 *   >= 0x80000000              N64 KSEG0/KSEG1 pointer left in ROM data -> port_n64_to_wasm
 *   PORT_WASM_BASE..0x7FFFFFFF  wasm pointer that game C code (or the PC layer) stored
 *   0x01000000..0x0FFFFFFF      RSP segment address: segtab[a >> 24] + (a & 0xFFFFFF)
 *   < 0x01000000                segment 0: N64 physical (RDRAM mirror) unless segment 0 was set */
static unsigned char *phys(unsigned a) {
    if (a >= 0x80000000u) return (unsigned char *)port_n64_to_wasm(a);
    if (a >= PORT_WASM_BASE) return (unsigned char *)(uintptr_t)a;
    if (a < sizeof n64_rdram) return n64_rdram + a;   /* N64 physical -> RDRAM mirror */
    return 0;
}

static unsigned fr_ops[256], fr_seguse[16];  /* P23: per-frame opcode histogram and segment references */
void *gfx_addr(unsigned a) {
    if (hfr_mode == 2) {
        unsigned char *gfx_addr_raw(unsigned a);
        return hfr_addr_ok(gfx_addr_raw(a));
    }
    return gfx_addr_raw(a);
}
unsigned char *gfx_addr_raw(unsigned a) {
    if (a >= PORT_WASM_BASE) return phys(a);
    unsigned seg = a >> 24;
    if (seg < 16) fr_seguse[seg]++;
    if (segset & (1u << seg)) {
        unsigned char *b = phys(segtab[seg]);
        return b ? b + (a & 0xFFFFFF) : 0;
    }
    if (seg) { gfx_stats.unset_seg++; return 0; }      /* segment never set in this task */
    return phys(a);
}

void gfx_set_segment(int seg, const void *base) {
    segtab[seg & 15] = (unsigned)(uintptr_t)base;
    segset |= 1u << (seg & 15);
}

static inline unsigned rd32(const void *p) { return *(const unsigned *)p; }

/* ------------------------------------------------------------------ RSP state */
typedef struct { float x, y, z, w, r, g, b, a, s, t, fog; float ox, oy, oz; } V;
static V vb[64];
static float mv[4][4], proj[4][4], mp[4][4], mvstack[32][4][4];
static int mvsp;
static unsigned geom, tex_on, tex_tile, tex_level;
static float tex_sc_s = 1, tex_sc_t = 1;
static short vp_scale[4] = {640, 480, 511, 0}, vp_trans[4] = {640, 480, 511, 0};
static short fog_mul, fog_off;
static unsigned rdphalf1, rdphalf2, normal_base;
static unsigned persp_norm, clip_ratio, cur_ucode, cur_udata;
static int gfx_trace;   /* P19: dump every command of the first real frames */

/* P35 light state (DMEM model, see light_vtx()) */
static unsigned char lbuf[0x400];         /* DMEM 0x260.. (lookats, lights) */
static unsigned char rare10[0x30];        /* DMEM 0x1D0..0x200 (Rare G_MOVEWORD 0x10 block) */
static unsigned char nbuf[0x40];          /* DMEM 0x510 (G_MOVEMEM 0x0E normals, s8 x,y per vertex slot) */
static unsigned light_nls;                /* numLightsxSize (48 N) */
static int light_dirty = 1, light_seen, light_dbg, light_bg;
static float lmdir[10][3];                /* model-space directions, index 0 = lookat X, 1 = lookat Y, 2+i = light i */
static float proj_game[4][4], mp_game[4][4]; /* the game's own P and MVP (freecam replaces the view in proj) */
static const unsigned char rare10_def[0x30] = {
    0,0,0,0,0xFF,0xFF,0,0, 0,0,0,0,0xFF,0xFF,0,0, 0x95,0x98,0x77,0x60,0x02,0x8D,0,0, 0x95,0x98,0x77,0x60,0x02,0x8D,0,0,
    0,0,0,0,0,0xC9,0,0, 0,0,0,0,0,0xC9,0,0};

static void light_prepare(void) {
    int n = (int)(light_nls / 48) + 3;    /* lookats, point lights, sun (the ambient has no direction) */
    if (n > 10) n = 10;
    for (int r = 0; r < n; r++) {
        const unsigned char *d = lbuf + r * 48 + 8;
        float x = (signed char)d[0], y = (signed char)d[1], z = (signed char)d[2];
        float m0 = mv[0][0] * x + mv[0][1] * y + mv[0][2] * z;
        float m1 = mv[1][0] * x + mv[1][1] * y + mv[1][2] * z;
        float m2 = mv[2][0] * x + mv[2][1] * y + mv[2][2] * z;
        float l = sqrtf(m0 * m0 + m1 * m1 + m2 * m2);
        lmdir[r][0] = l > 0 ? m0 / l : 0; lmdir[r][1] = l > 0 ? m1 / l : 0; lmdir[r][2] = l > 0 ? m2 / l : 0;
    }
    light_dirty = 0;
}

/* P35b: the ucode's data segment is DMEM 0x000.. at task start and after every G_LOAD_UCODE, so the light
 * records, lookats and the Rare 0x10 block the DL does not send hold the ucode data image's values (the level
 * frame sends NUMLIGHT 0 and the sun only: its ambient, record 1 at DMEM 0x2F0, comes from this image). */
static void dmem_seed(unsigned data_addr, unsigned size) {
    const unsigned char *d = data_addr ? gfx_addr(data_addr) : 0;
    if (!d || size < 0x660) return;
    for (unsigned k = 0; k < sizeof lbuf; k++) lbuf[k] = vbe_ld8(d + 0x260 + k);
    for (unsigned k = 0; k < sizeof rare10; k++) rare10[k] = vbe_ld8(d + 0x1D0 + k);
    for (unsigned k = 0; k < sizeof nbuf && 0x510 + k < size; k++) nbuf[k] = vbe_ld8(d + 0x510 + k);
    light_dirty = 1;
    light_bg = 0;   /* the ucode name string in the data image (P6: "RSP Gfx ucode F3DEXBG.NoN ...") */
    for (unsigned k = 0; k + 8 < size && k < 0x800; k++)
        if (vbe_ld8(d + k) == 'F' && vbe_ld8(d + k + 1) == '3' && vbe_ld8(d + k + 5) == 'B' && vbe_ld8(d + k + 6) == 'G') { light_bg = 1; break; }
    static int logged;
    if (!logged++) {
        char b[256]; int m = 0;
        for (unsigned r = 0; r < 4; r++) {
            m = 0;
            for (unsigned k = 0; k < 48; k++) m += snprintf(b + m, sizeof b - m, "%02X%s", lbuf[48 * r + k], (k & 3) == 3 ? " " : "");
            port_log("[light] ucode data DMEM 0x%03X: %s\n", 0x260 + 48 * r, b);
        }
        m = 0;
        for (unsigned k = 0; k < sizeof rare10; k++) m += snprintf(b + m, sizeof b - m, "%02X%s", rare10[k], (k & 3) == 3 ? " " : "");
        port_log("[light] ucode data DMEM 0x1D0..0x200: %s\n", b);
    }
}

static inline float rare_s(int k) { return (short)(rare10[2 * k] << 8 | rare10[2 * k + 1]) + (rare10[0x10 + 2 * k] << 8 | rare10[0x10 + 2 * k + 1]) / 65536.0f; }
static inline float rare_t(int k) { return (short)(rare10[0x20 + 2 * k] << 8 | rare10[0x20 + 2 * k + 1]); }

static float bmin[3], bmax[3];
static int bany;

/* RDP state */
static unsigned oth_h, oth_l, combine_w0, combine_w1;
static unsigned prim_col, env_col, fog_col, blend_col, fill_col, prim_lod;
static unsigned cimg_addr, zimg_addr, cimg_width = 320, prim_z;
/* P335: set for one texture rectangle that reads a full-frame image the port keeps at canvas resolution (hx_*, below):
 * the GL texture and the offset (canvas pixels, GL orientation) from the drawn pixel to the texel it reads. */
static int hxs_on;
static unsigned hxs_tex;
static float hxs_ox, hxs_oy;
/* P349 option "Hi-res menus and 2D" (page: Options, key hires2d; port_gfx_hires_2d). The renderer draws every primitive
 * at canvas resolution already, but texture rectangles (menus, HUD, text, sprites, title and pause screens) were sampled
 * with the RDP's per-N64-pixel rule: pixel x reads s(x) = s + dsdx * (x - ulx), i.e. at the pixel's top-left corner. At a
 * 1:1 rectangle the N64 so shows exact texels; per canvas pixel the same formula reads s(x) + 0.12 .. + 0.88 (at 4.4 canvas
 * pixels per N64 pixel): the picture slid half a texel, every texel blurred into its right / lower neighbour, and the
 * last half texel of a tile read past what the N64 rectangle samples (seams between tiles, the clamped edge texel, an
 * atlas neighbour). With the option on, a rectangle's s / t move back by half a step (canvas pixel centre X reads
 * s + dsdx * (X - 0.5 - ulx), exactly s(x) at the N64 pixel centre), the texture is clamped to what the N64 rectangle
 * samples unless the tile's own texels go on past it (bordered tiles, the tile's clamp edge), filtering is 4-tap
 * bilinear with full fractions (3-point with 5-bit fractions only ever shows its in-between values when magnified), and
 * point-sampled / copy-mode rectangles become crisp texels of equal width. rect_hires_mode: 0 off, 1 bilinear, 2 point;
 * rect_hires_clamp: tile-0 texel range (s lo, t lo, s hi, t hi). Render-only: this object is outside the online hash. */
static int hires_2d;                       /* the option (page) */
static int rect_hires_mode;                /* for the texture rectangle being drawn */
static float rect_hires_clamp[4];
EMSCRIPTEN_KEEPALIVE void port_gfx_hires_2d(int on) { hires_2d = on != 0; }
/* P349: the pause screen's frozen frame kept at canvas resolution (zsnap_take, near hx_*): tex / fbo the snapshot, tw x th
 * its size, src the screen image it copies, p / w / rows the z image that holds that copy on the N64. */
static struct { GLuint tex, fbo; int tw, th, valid, due; unsigned char *src, *p; unsigned w, rows; } zsnap;
static int hx_cur;   /* P335 (defined with hx[] below) */
/* P137: offscreen colour image (render to texture, e.g. the P130 object shadow pass: SETCIMG RGBA16 64 wide).
 * While on, draws go to an FBO of cimg_width x cimg_width N64 pixels (1:1) and the canvas is that size; the FBO is
 * written back to RDRAM in the image's pixel size (8-bit: the red byte, as the RDP's 8-bit colour images; 16-bit:
 * RGBA5551 big-endian; 32-bit: RGBA8888) when the game loads the target as a texture (SETTIMG) and when
 * the colour image switches back / the task ends. Before P137 the renderer drew such passes onto the screen,
 * scaled as a 64-wide frame (white screen + black shadow polygons). ?p137nooff=1 turns it off (old behaviour). */
static int off_on, off_saved_w, off_saved_h;
static unsigned off_addr, off_w, off_fbo_w, off_siz, off_rows;
/* P161: the pause menu uses the z-buffer memory as a colour image: its first frame draws the previous screen image
 * (LOADTILE strips, 1:1) into SETCIMG = the z image, later frames texture the frozen frame from there. Before P161
 * those strips went onto the canvas and the z image stayed empty (black pause background). Now a SETCIMG of the z image
 * (16-bit, <= 320 wide) is an offscreen image too (off_zimg); its z-clear fill rectangles still clear the canvas depth,
 * and it is written back only when something was drawn into it (off_drawn), so the depth-clear passes of normal frames
 * leave RDRAM alone. ?p161nozc=1 = old behaviour. */
static int off_zimg, off_drawn;
/* P140: the FBO is always OFF_FBO_H rows (1:1, N64 row y = GL row OFF_FBO_H - 1 - y), so images need not be square.
 * The rows written back are off_rows: the image width (square, as before) unless the game sets a scissor while the
 * image is bound (the RDP cannot write below the scissor, so its lry bounds the image's height). */
#define OFF_FBO_H 256
/* P147: on screen, the rows shown are the VI's (pc_os.c port_vi_view: PAL rows 1 .. 214.7 of the 292 x 216 framebuffer),
 * stretched over the canvas; N64 row y is canvas row (y - VI_Y0) * canvas_h / CIMG_H. Before P147 it was rows
 * 0 .. 0.75 * width (219), which showed row 216 (below the scissor) as a stray line. */
static float vi_y0, vi_h;
static void vi_view_update(void) {
    int port_vi_view(float *y0, float *h);
    float y0, h;
    if (port_vi_view(&y0, &h)) { vi_y0 = y0; vi_h = h; } else { vi_y0 = 0; vi_h = 0; }
}
#define VI_Y0 (off_on ? 0.0f : vi_y0)
#define CIMG_H ((float)(off_on ? OFF_FBO_H : vi_h > 0 ? vi_h : cimg_width * 0.75f))
typedef struct { unsigned fmt, siz, line, tmem, pal, cms, cmt, masks, maskt, shifts, shiftt, uls, ult, lrs, lrt; } Tile;
static Tile tiles[8];
static struct { unsigned fmt, siz, width, raw; unsigned char *p; } timg;
static unsigned char tmem[4096];
static int p193_idx;   /* P193: draws (non-empty flushes) in this gfx task */
static unsigned tmem_gen;          /* bumped on every TMEM write (texture cache key) */

#define G_ZBUFFER 0x00000001
#define G_SHADE 0x00000004
#define G_CULL_FRONT 0x00000200
#define G_CULL_BACK 0x00000400
#define G_FOG 0x00010000
#define G_LIGHTING 0x00020000
#define G_TEXTURE_GEN 0x00040000

static void mtx_mul(float r[4][4], float a[4][4], float b[4][4]) {
    float t[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            t[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j] + a[i][3] * b[3][j];
    memcpy(r, t, sizeof t);
}

static void mtx_read(float m[4][4], const unsigned char *p) {
    for (int i = 0; i < 16; i++) {
        unsigned wi = rd32(p + (i >> 1) * 4), wf = rd32(p + 32 + (i >> 1) * 4);
        int ip = (short)((i & 1) ? (wi & 0xFFFF) : (wi >> 16));
        unsigned fp = (i & 1) ? (wf & 0xFFFF) : (wf >> 16);
        m[i >> 2][i & 3] = ip + fp / 65536.0f;
    }
}

static void mtx_ident(float m[4][4]) {
    memset(m, 0, 64);
    m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1;
}

/* ------------------------------------------------------------------ GL backend */
static GLuint prog, vbo, vao;
static GLint u_tex[6], u_tp[6], u_tm[6], u_ts[6], u_lodviz, u_splitx, u_c0, u_c1, u_a0, u_a1, u_2cyc, u_prim, u_env, u_fogc, u_blendc,
    u_primlod, u_acmp, u_mode, u_texon, u_filt, u_lod, u_pixscale, u_bl1, u_bl2, u_blfin, u_k45, u_primz, u_cvg, u_dbg, u_idx, u_hires,
    u_rhi, u_rclamp;
static int gl_ok, canvas_w = 640, canvas_h = 480;
#define VF 11
#define BATCH_TRIS 4096
static float batch[BATCH_TRIS * 3 * VF];
static int nbatch;      /* vertices in batch */
static int state_dirty = 1;
static int rect_mode;   /* 0 tris, 1 fill rect, 2 tex rect (screen-space quads) */
static unsigned k4k5;   /* G_SETCONVERT K4 (bits 9..17) / K5 (bits 0..8) */

/* P350 option "Widescreen" (page: Options, key widescreen; port_gfx_widescreen). The page gives the canvas the aspect of
 * the window (wider than 4:3); the N64 picture (cimg_width x the VI rows, shown 4:3) keeps its size and sits in the middle
 * of it, ws_ox canvas pixels from the left, ws_sx canvas pixels per N64 pixel across, and N64 x coordinates outside
 * 0 .. cimg_width reach into the side strips. ws_k = canvas width / the 4:3 width.
 *  - 3D (a perspective projection): the clip-space x is divided by ws_k and the viewport is ws_k times wider around its
 *    centre, which moves to cx + (centre - cx) * ws_k (cx = the screen centre). A full-screen view keeps every point where
 *    the N64 draws it and shows ws_k times more to the sides; a split-screen view gets its share of the wider screen.
 *    G_CULLDL tests x against +-ws_k w. The scissor of a 3D draw is mapped like its viewport, edges within 4 N64 pixels
 *    of the screen edge (the game's 2-pixel border) go to the canvas edge.
 *  - 2D (texture / fill rectangles, orthographic triangles): the N64 position in the centred 4:3 picture, no stretch.
 *    Untextured fills that touch the left / right screen edge (fades, cutscene letterbox bars, the scope mask) and
 *    rectangles that copy a full frame per canvas pixel (P335 frame-blend ghost, P349 pause snapshot) are drawn on to
 *    the canvas edge.
 * ws_on: the mapping is active for this draw target (the option on, the canvas wider than 4:3, not an offscreen N64-size
 * image). Off: ws_sx = canvas_w / cimg_width, ws_ox = 0, ws_k = 1 and the original code paths run. Render-only: this
 * object is outside the online hash. */
static float sc_box[4];   /* P35b: scissor in N64 pixels (ulx, uly, lrx, lry) (P350: declared here for ws_calc) */
static int sc_on;
static int ws_opt;                 /* the option (page) */
static int ws_on;
static float ws_k, ws_ox, ws_sx;   /* (zero-initialised: no .data, see ws_flag; set by ws_calc before use) */
static int ws_tag;                 /* HUD anchor of the commands being run: 0 centred, 1 left edge, 2 right edge, 3 the view
                                    * of the current scissor box (a player's own overlays in split screen; ws_mark) */
static float ws_dx;                /* the anchor's shift in canvas pixels */
static int proj_persp;             /* the current projection has a perspective divide (G_MTX P: m[2][3] != 0) */
static int ws_log_on;              /* DIAGNOSTIC ?p350log=F: every rectangle / triangle state of the first gfx task at or after retrace F */
/* P350 URL flags, read once (zero-initialised statics only, like the rest of P350's state here: no .data) */
static int ws_flag_val[4]; static unsigned char ws_flag_read[4];
static int ws_flag(int i, const char *name) { if (!ws_flag_read[i]) { ws_flag_read[i] = 1; ws_flag_val[i] = port_flag(name); } return ws_flag_val[i]; }
EMSCRIPTEN_KEEPALIVE void port_gfx_widescreen(int on) { ws_opt = on != 0; state_dirty = 1; }
static void ws_calc(void) {
    float base = canvas_h * (4.0f / 3.0f);
    ws_on = ws_opt && !off_on && cimg_width >= 256 && canvas_w > base + 0.5f;
    if (ws_on) { ws_k = canvas_w / base; ws_ox = (canvas_w - base) * 0.5f; ws_sx = base / (float)cimg_width; }
    else { ws_k = 1; ws_ox = 0; ws_sx = canvas_w / (float)cimg_width; }
    ws_dx = !ws_on ? 0 : ws_tag == 1 ? -ws_ox : ws_tag == 2 ? ws_ox : 0;
    if (ws_on && ws_tag == 3 && sc_on) {   /* the view's centre moves as its 3D does: (c - cx) * (k - 1) N64 pixels */
        float c = (sc_box[0] + sc_box[2]) * 0.5f, cx = cimg_width * 0.5f;
        ws_dx = (c - cx) * (ws_k - 1) * ws_sx;
    }
}
static inline float ws_x2d(float x) { return ws_ox + x * ws_sx + ws_dx; }                      /* 2D: N64 x -> canvas x */
static inline float ws_x3d(float x) { float c = cimg_width * 0.5f; return ws_ox + (c + (x - c) * ws_k) * ws_sx; }   /* 3D view edge */
/* the edge of a view at N64 x: the canvas edge within 4 pixels of the screen edge (the game's 2-pixel border), else the
 * widened view's edge */
static inline float ws_edge(float x) { return x <= 4 ? 0 : x >= cimg_width - 4.0f ? (float)canvas_w : ws_x3d(x); }
/* rect_ext bits for a rectangle x0 .. x1: an edge on the screen's edge, or (tag 3) on the view's (scissor box) edge */
static int ws_rect_edges(float x0, float x1) {
    float W = (float)cimg_width;
    int e = (x0 <= 2.5f) | (x1 >= W - 2.5f) << 1;
    if (ws_tag == 3 && sc_on) e |= (fabsf(x0 - sc_box[0]) <= 3) | (fabsf(x1 - sc_box[2]) <= 3) << 1;
    return e;
}
/* P350: the widening the game side should cull for (the canvas, read while the game builds its display list) */
static float ws_game_k(void) { float base = canvas_h * (4.0f / 3.0f); return ws_opt && canvas_w > base + 0.5f ? canvas_w / base : 1.0f; }

/* P350 widescreen, render-side culling. The game culls level geometry against its 4:3 view while it builds the frame
 * display list (level_dl_visibility_filter, mesh_dl_cull_copy), so the side strips of a wide picture would show holes.
 * Their results are also kept in game memory (per-triangle / per-vertex visibility bytes, the zone tree's per-view bits),
 * which game logic may read and which the online state hash covers, so the game's own output must stay as it is. The
 * link-time wrappers of those functions (below) therefore run the function a second time for the wider view into
 * ws_arena (renderer memory), run it once more with the game's own inputs (the same output into the game's list, and
 * the game memory it writes back exactly as after the first call) and put back the stack bytes the extra calls used.
 * ws_sub_add records "the game list [gs, ge) has a wide copy pdl"; gfx_run_dl, on reaching gs while the widescreen
 * mapping is on, runs the copy instead and goes on at ge. Entries of a DL buffer are dropped when the renderer has run
 * the task that uses it (and when a new entry overlaps them). */
#define WS_ARENA_WORDS (2u << 20)   /* 8 MB ring */
static uint32_t ws_arena[WS_ARENA_WORDS];
static unsigned ws_arena_pos;
#define WS_SUB_N 32
static struct { const unsigned char *gs, *ge; uint32_t h; const unsigned char *pdl; } ws_sub[WS_SUB_N];
static int ws_sub_n;
static uintptr_t ws_sub_lo, ws_sub_hi;   /* used only while ws_sub_n > 0 */
static unsigned ws_sub_stats[3];   /* added, used, dropped (stale) */
static void ws_sub_bounds(void) {
    ws_sub_lo = ~(uintptr_t)0; ws_sub_hi = 0;
    for (int i = 0; i < ws_sub_n; i++) {
        if ((uintptr_t)ws_sub[i].gs < ws_sub_lo) ws_sub_lo = (uintptr_t)ws_sub[i].gs;
        if ((uintptr_t)ws_sub[i].gs > ws_sub_hi) ws_sub_hi = (uintptr_t)ws_sub[i].gs;
    }
}
static void ws_sub_drop_range(const unsigned char *lo, const unsigned char *hi) {   /* entries starting in [lo, hi) */
    int j = 0;
    for (int i = 0; i < ws_sub_n; i++) if (ws_sub[i].gs < lo || ws_sub[i].gs >= hi) ws_sub[j++] = ws_sub[i];
    ws_sub_n = j; ws_sub_bounds();
}
static uint32_t *ws_arena_get(unsigned words) {
    if (words > WS_ARENA_WORDS / 4) return 0;
    if (ws_arena_pos + words > WS_ARENA_WORDS) ws_arena_pos = 0;
    uint32_t *p = ws_arena + ws_arena_pos;
    ws_arena_pos += words;
    return p;
}
/* an entry is used only while the game list still holds what it held when the entry was made: the four commands before
 * gs (the caller's setup: matrix, segment, ... ) and the range itself are hashed (an empty range is valid too) */
static uint32_t ws_sub_hash(const unsigned char *gs, const unsigned char *ge) {
    uint32_t h = 2166136261u;
    for (const unsigned char *q = gs - 32; q < ge; q += 4) h = (h ^ rd32(q)) * 16777619u;
    return h;
}
static void ws_sub_add(const void *gs, const void *ge, const uint32_t *pdl) {
    const unsigned char *s = gs, *e = ge;
    int j = 0;
    for (int i = 0; i < ws_sub_n; i++)   /* overlapping entries are from an older frame in the same buffer */
        if (!(ws_sub[i].gs < e && ws_sub[i].ge > s) && ws_sub[i].gs != s) ws_sub[j++] = ws_sub[i];
    ws_sub_n = j;
    if (ws_sub_n == WS_SUB_N) { memmove(ws_sub, ws_sub + 1, sizeof ws_sub[0] * (WS_SUB_N - 1)); ws_sub_n--; }
    ws_sub[ws_sub_n].gs = s; ws_sub[ws_sub_n].ge = e; ws_sub[ws_sub_n].pdl = (const unsigned char *)pdl;
    ws_sub[ws_sub_n].h = ws_sub_hash(s, e);
    ws_sub_n++; ws_sub_stats[0]++; ws_sub_bounds();
}
static const unsigned char *ws_sub_skip;   /* an empty range was just replaced here: run the game command at it once */
static int ws_sub_find(const unsigned char *pc) {
    if (pc == ws_sub_skip) { ws_sub_skip = 0; return -1; }
    for (int i = 0; i < ws_sub_n; i++)
        if (ws_sub[i].gs == pc) {
            if (ws_sub[i].h != ws_sub_hash(ws_sub[i].gs, ws_sub[i].ge)) { ws_sub_stats[2]++; return -1; }
            if (ws_sub[i].ge == pc) ws_sub_skip = pc;
            return i;
        }
    return -1;
}
/* P350 HUD anchors: game C (#ifdef PORT, hud_draw / hud_overlay_draw_screen) calls port_ws_hud_anchor(gdl, edge) before and
 * after the HUD elements that sit in a screen corner: from that display-list address on, the renderer shifts the 2D (and
 * the HUD's own perspective models, such as the health chocolate) by the width of the side strip, so they keep their
 * distance to the picture's edge instead of to the 4:3 picture's (edge 1 left, 2 right, 0 back to the centred layout).
 * Renderer memory only (the game's list is not changed); used while the widescreen mapping is on. */
#define WS_MARK_N 64
static struct { const unsigned char *at; int tag; } ws_mark[WS_MARK_N];
static int ws_mark_n;
static uintptr_t ws_mark_lo, ws_mark_hi;
void port_ws_hud_anchor(void *gdl, int edge) {
    const unsigned char *a = gdl;
    int j = 0;
    if (!ws_opt || !a) return;
    for (int i = 0; i < ws_mark_n; i++) if (ws_mark[i].at < a) ws_mark[j++] = ws_mark[i];   /* later ones: an older frame */
    ws_mark_n = j;
    if (ws_mark_n == WS_MARK_N) { memmove(ws_mark, ws_mark + 1, sizeof ws_mark[0] * (WS_MARK_N - 1)); ws_mark_n--; }
    ws_mark[ws_mark_n].at = a; ws_mark[ws_mark_n].tag = edge; ws_mark_n++;
    ws_mark_lo = ~(uintptr_t)0; ws_mark_hi = 0;
    for (int i = 0; i < ws_mark_n; i++) {
        if ((uintptr_t)ws_mark[i].at < ws_mark_lo) ws_mark_lo = (uintptr_t)ws_mark[i].at;
        if ((uintptr_t)ws_mark[i].at > ws_mark_hi) ws_mark_hi = (uintptr_t)ws_mark[i].at;
    }
}
static void ws_mark_drop_range(const unsigned char *lo, const unsigned char *hi) {
    int j = 0;
    for (int i = 0; i < ws_mark_n; i++) if (ws_mark[i].at < lo || ws_mark[i].at >= hi) ws_mark[j++] = ws_mark[i];
    ws_mark_n = j;
}

/* the stack bytes below the caller's stack pointer, saved around the extra calls (see gfx_run_task's GFX_SCRUB); macros,
 * so the stack pointer is the one of the function that uses them */
#include <emscripten/stack.h>
#define WS_SCRUB (64 * 1024)
static unsigned char ws_scrub_buf[WS_SCRUB];
static unsigned char *ws_scrub_lo; static size_t ws_scrub_n;
#define WS_SCRUB_SAVE() do { uintptr_t sp_ = emscripten_stack_get_current(), end_ = emscripten_stack_get_end(); \
    size_t n_ = sp_ > end_ ? sp_ - end_ : 0; if (n_ > WS_SCRUB) n_ = WS_SCRUB; \
    ws_scrub_lo = (unsigned char *)(sp_ - n_); ws_scrub_n = n_; memcpy(ws_scrub_buf, ws_scrub_lo, n_); } while (0)
#define WS_SCRUB_RESTORE() memcpy(ws_scrub_lo, ws_scrub_buf, ws_scrub_n)

static const char *VS =
    "#version 300 es\n"
    "in vec4 aPos; in vec4 aCol; in vec2 aST; in float aFog;\n"
    "out vec4 vCol; out vec2 vST; out float vFog;\n"
    /* P35: F3DEX2 does not clip at the far plane (the RDP z just saturates), so z is clamped to w here
     * instead of letting the GPU clip far geometry such as level backdrops */
    "void main() { vec4 p = aPos; if (p.w > 0.0 && p.z > p.w) p.z = p.w; gl_Position = p; vCol = aCol; vST = aST; vFog = aFog; }\n";

/* P35: the RDP texture unit and blender in the shader.
 *  - Tiles: up to 6 bound (P78; the base tile and the next ones: 2-cycle TEXEL1 and LOD levels 0..4 + 1). Each is decoded
 *    exactly (uTS.xy texels) and addressed with texelFetch, so clamp (to the tile size), mirror and wrap
 *    (mask) are the RDP's per tile: clamp first, then mirror / mask (P35.md section 5).
 *    uTP = (ul s, ul t in texels, shift scale s, shift scale t).
 *  - Filter (uFilt): 0 point, 1 the RDP 3-point (triangle) bilinear with 5-bit fractions (default),
 *    2 plain 4-tap bilinear (?filter4=1). No half-texel offset: the RDP samples texel i at s = i.
 *  - LOD (uLod: x = on (G_TL_LOD), y = max level, z = sharpen/detail): lod = texels per N64 pixel; tile
 *    base + floor(log2 lod); LOD_FRACTION = lod / 2^l - 1; magnification uses tile base and fraction 0.
 *    P78: lod = max(|ds|, |dt|) over an x and a y pixel step (the RDP's per-component max, not the vector length),
 *    scaled by canvas pixels per N64 pixel (uPixScale was the inverse, so lod was ~4.8x too small at 640 / 292:
 *    distant LOD surfaces sampled 2+ levels too fine); "distant" (l_tile >= max level) takes both texels from
 *    tile base + max with LOD_FRACTION 1 (was TEXEL1 = the tile after the max level); levels up to 4 (was 2).
 *  - Blender: uBl1 = first cycle (2-cycle mode only; its result is the second cycle's IN), uBl2 = the final
 *    cycle, selectors (P, A, M, B). uBlFin: 0 output P (no FORCE_BL), 1 blend in the shader (no memory
 *    input), 2 the GL blend does the memory term: out rgb = the non-memory colour, alpha = the A factor. */
static const char *FS =
    "#version 300 es\n"
    "precision highp float; precision highp int;\n"
    "in vec4 vCol; in vec2 vST; in float vFog;\n"
    "uniform highp sampler2D uT0, uT1, uT2, uT3, uT4, uT5; uniform vec4 uTP[6]; uniform ivec4 uTM[6], uTS[6]; uniform int uLodViz; uniform float uSplitX;\n"
    "uniform ivec4 uC0, uC1, uA0, uA1, uBl1, uBl2, uLod; uniform int u2cyc, uAcmp, uMode, uTexOn, uFilt, uBlFin, uCvg, uDbg, uIdx;\n"
    "uniform vec4 uPrim, uEnv, uFogC, uBlendC, uHiRes; uniform vec2 uK45; uniform float uPrimLod, uPixScale, uPrimZ;\n"
    "uniform int uRHi; uniform vec4 uRClamp;\n"
    "out vec4 frag;\n"
    "vec4 T0, T1, SH; float LF; vec2 RFW;\n"
    "int wrapc(int c, int cl, int mi, int mk, int mx) {\n"
    "  if (cl != 0) c = clamp(c, 0, mx);\n"
    "  if (mk > 0) { if (mi != 0 && ((c >> mk) & 1) != 0) c = ~c; c &= (1 << mk) - 1; }\n"
    "  return c; }\n"
    "vec4 fetch(int k, ivec2 c) {\n"
    "  ivec4 m = uTM[k], z = uTS[k];\n"
    "  c.x = wrapc(c.x, m.x & 1, m.x & 2, m.y, z.z); c.y = wrapc(c.y, m.x & 4, m.x & 8, m.z, z.w);\n"
    "  c = clamp(c, ivec2(0), z.xy - 1);\n"
    "  if (k == 0) return texelFetch(uT0, c, 0); if (k == 1) return texelFetch(uT1, c, 0);\n"
    "  if (k == 2) return texelFetch(uT2, c, 0); if (k == 3) return texelFetch(uT3, c, 0);\n"
    "  if (k == 4) return texelFetch(uT4, c, 0); return texelFetch(uT5, c, 0); }\n"
    "vec4 samp(int k) {\n"
    "  if (((uTexOn >> k) & 1) == 0) return vec4(1.0);\n"
    "  vec2 tc = vST * uTP[k].zw - uTP[k].xy;\n"
    /* P349 option "Hi-res menus and 2D" (rect_hires_*): a texture rectangle at canvas resolution. The CPU moved vST back by
     * half a texel step, so tc is the texel position this canvas pixel shows (texel i at tc = i, as the RDP samples it at
     * an N64 pixel); uRClamp keeps tile 0 inside the texels the N64 rectangle reads (no bleeding from an atlas neighbour
     * or a wrapped edge). uRHi 1: 4-tap bilinear with full fractions; 2 (copy mode / point filter): crisp texels whose
     * edges are blended over one canvas pixel (RFW = texels per canvas pixel), so every texel gets the same width. */
    "  if (uRHi != 0) {\n"
    "    if (k == 0) tc = clamp(tc, uRClamp.xy, uRClamp.zw);\n"
    "    vec2 b = floor(tc), f = tc - b; ivec2 i = ivec2(b);\n"
    "    if (uRHi == 2) f = clamp((f - 0.5) / RFW + 0.5, 0.0, 1.0);\n"
    "    return mix(mix(fetch(k, i), fetch(k, i + ivec2(1, 0)), f.x), mix(fetch(k, i + ivec2(0, 1)), fetch(k, i + ivec2(1, 1)), f.x), f.y); }\n"
    "  if (uFilt == 0 || uMode == 3) return fetch(k, ivec2(floor(tc)));\n"
    "  vec2 fl = floor(tc), f = floor((tc - fl) * 32.0) / 32.0; ivec2 b = ivec2(fl);\n"
    "  vec4 t00 = fetch(k, b), t10 = fetch(k, b + ivec2(1, 0)), t01 = fetch(k, b + ivec2(0, 1));\n"
    "  if (uFilt == 2) { vec4 t11 = fetch(k, b + ivec2(1, 1)); return mix(mix(t00, t10, f.x), mix(t01, t11, f.x), f.y); }\n"
    "  if (f.x + f.y < 1.0) return t00 + f.x * (t10 - t00) + f.y * (t01 - t00);\n"
    "  vec4 t11 = fetch(k, b + ivec2(1, 1));\n"
    "  return t11 + (1.0 - f.x) * (t01 - t11) + (1.0 - f.y) * (t10 - t11); }\n"
    "vec3 cA(int i, vec3 c) { if (i == 0) return c; if (i == 1) return T0.rgb; if (i == 2) return T1.rgb;"
    "  if (i == 3) return uPrim.rgb; if (i == 4) return SH.rgb; if (i == 5) return uEnv.rgb; if (i == 6) return vec3(1.0);"
    "  if (i == 7) return vec3(fract(sin(dot(gl_FragCoord.xy, vec2(12.9898, 78.233))) * 43758.5453)); return vec3(0.0); }\n"
    "vec3 cB(int i, vec3 c) { if (i == 0) return c; if (i == 1) return T0.rgb; if (i == 2) return T1.rgb;"
    "  if (i == 3) return uPrim.rgb; if (i == 4) return SH.rgb; if (i == 5) return uEnv.rgb; if (i == 7) return vec3(uK45.x); return vec3(0.0); }\n"
    "vec3 cC(int i, vec3 c, float ca) { if (i == 0) return c; if (i == 1) return T0.rgb; if (i == 2) return T1.rgb;"
    "  if (i == 3) return uPrim.rgb; if (i == 4) return SH.rgb; if (i == 5) return uEnv.rgb; if (i == 6) return vec3(1.0);"
    "  if (i == 7) return vec3(ca); if (i == 8) return vec3(T0.a); if (i == 9) return vec3(T1.a);"
    "  if (i == 10) return vec3(uPrim.a); if (i == 11) return vec3(SH.a); if (i == 12) return vec3(uEnv.a);"
    "  if (i == 13) return vec3(LF); if (i == 14) return vec3(uPrimLod); if (i == 15) return vec3(uK45.y); return vec3(0.0); }\n"
    "vec3 cD(int i, vec3 c) { if (i == 0) return c; if (i == 1) return T0.rgb; if (i == 2) return T1.rgb;"
    "  if (i == 3) return uPrim.rgb; if (i == 4) return SH.rgb; if (i == 5) return uEnv.rgb; if (i == 6) return vec3(1.0);"
    "  return vec3(0.0); }\n"
    "float aX(int i, float a) { if (i == 0) return a; if (i == 1) return T0.a; if (i == 2) return T1.a;"
    "  if (i == 3) return uPrim.a; if (i == 4) return SH.a; if (i == 5) return uEnv.a; if (i == 6) return 1.0; return 0.0; }\n"
    "float aC(int i, float a) { if (i == 0) return LF; if (i == 1) return T0.a; if (i == 2) return T1.a;"
    "  if (i == 3) return uPrim.a; if (i == 4) return SH.a; if (i == 5) return uEnv.a; if (i == 6) return uPrimLod; return 0.0; }\n"
    "vec3 bP(int i, vec3 c) { if (i == 2) return uBlendC.rgb; if (i == 3) return uFogC.rgb; return c; }\n"
    "float bA(int i, float a) { if (i == 0) return a; if (i == 1) return uFogC.a; if (i == 2) return SH.a; return 0.0; }\n"
    "float bB(int i, float a) { if (i == 0) return 1.0 - a; if (i == 3) return 0.0; return 1.0; }\n"
    "void main() {\n"
    "  SH = vCol; LF = 0.0; RFW = max(fwidth(vST * uTP[0].zw), vec2(1.0 / 256.0));\n"
    "  gl_FragDepth = uPrimZ >= 0.0 ? uPrimZ : gl_FragCoord.z;\n"
    /* P193 DIAGNOSTIC ?p193idx=F: draw index as colour (r = idx & 7, g = idx >> 3 & 7, b = idx >> 6 & 7, 32 per step + 16) */
    "  vec4 IC = vec4(vec3(float(uIdx & 7), float((uIdx >> 3) & 7), float((uIdx >> 6) & 7)) * 32.0 + 16.0, 255.0) / 255.0;\n"
    "  if (uMode == 1) { frag = uIdx >= 0 ? IC : vCol; return; }\n"
    "  int lt = 0; bool distant = false;\n"
    "  if (uTexOn != 0) {\n"
    /* P78: the RDP's LOD is the largest of |ds|, |dt| over one N64 pixel step in x and in y (tile 0 texels,
     * unshifted). dFdx is per canvas pixel, so uPixScale = canvas pixels per N64 pixel (was the inverse). */
    "    vec2 tc = vST * uTP[0].zw, gx = abs(dFdx(tc)), gy = abs(dFdy(tc));\n"
    "    float l = max(max(gx.x, gx.y), max(gy.x, gy.y)) * uPixScale;\n"
    /* DIAGNOSTIC ?p78split=1: left of uSplitX the pre-P78 LOD (vector length, inverse scale), for a same-frame comparison */
    "    if (gl_FragCoord.x < uSplitX) l = max(length(dFdx(tc)), length(dFdy(tc))) / uPixScale;\n"
    "    if (l >= 1.0) { float e = floor(log2(l)); LF = l / exp2(e) - 1.0; if (uLod.x != 0) { lt = int(e);"
    /* distant (l_tile at the max level): both texels come from tile base + max, LOD_FRACTION 0xFF */
    "      if (lt >= uLod.y) { lt = uLod.y; LF = 1.0; distant = true; } } }\n"
    "    else if (uLod.z != 0) LF = l;\n"
    "    lt = min(lt, 4);\n"
    "  }\n"
    /* P335: a texture rectangle that reads a full-frame image kept at canvas resolution (hx_*: the frame-blend ghost):
     * unit 0 is that image, read 1:1 per canvas pixel at uHiRes.xy (canvas px) from this pixel, alpha 1 */
    "  if (uHiRes.z != 0.0) { ivec2 hc = clamp(ivec2(floor(gl_FragCoord.xy + uHiRes.xy)), ivec2(0), textureSize(uT0, 0) - 1);\n"
    "    T0 = vec4(texelFetch(uT0, hc, 0).rgb, 1.0); T1 = T0; }\n"
    "  else { T0 = samp(lt);\n"
    "  T1 = !distant && (uTexOn & (2 << lt)) != 0 ? samp(lt + 1) : T0; }\n"
    "  if (uMode == 3) { if (T0.a < 0.5) discard; frag = vec4(T0.rgb, 1.0); return; }\n"
    "  vec3 c = vec3(0.0); float a = 0.0;\n"
    "  vec3 c1 = (cA(uC0.x, c) - cB(uC0.y, c)) * cC(uC0.z, c, a) + cD(uC0.w, c);\n"
    "  float a1 = (aX(uA0.x, a) - aX(uA0.y, a)) * aC(uA0.z, a) + aX(uA0.w, a);\n"
    "  if (u2cyc == 1) { c = clamp(c1, 0.0, 1.0); a = clamp(a1, 0.0, 1.0);\n"
    "    c1 = (cA(uC1.x, c) - cB(uC1.y, c)) * cC(uC1.z, c, a) + cD(uC1.w, c);\n"
    "    a1 = (aX(uA1.x, a) - aX(uA1.y, a)) * aC(uA1.z, a) + aX(uA1.w, a); }\n"
    "  c1 = clamp(c1, 0.0, 1.0); a1 = clamp(a1, 0.0, 1.0);\n"
    /* P193 DIAGNOSTIC ?p193dbg=F: views of one material (see apply_state) */
    "  if (uDbg == 8) discard;\n"
    "  if (uDbg != 0) { frag = vec4(uDbg == 1 ? T0.rgb : uDbg == 2 ? SH.rgb : uDbg == 3 ? vec3(1.0, 0.0, 1.0) : uDbg == 4 ? vec3(LF) :"
    "    uDbg == 5 ? vec3(float(lt) / 4.0, float(uTexOn) / 63.0, distant ? 1.0 : 0.0) : uDbg == 6 ? vec3(a1) : vec3(T0.a, T1.a, 0.0), 1.0); return; }\n"
    "  if (uAcmp == 1 && a1 < uBlendC.a) discard;\n"
    "  if (uAcmp == 3 && a1 < fract(sin(dot(gl_FragCoord.xy, vec2(41.31, 17.77))) * 1531.7)) discard;\n"
    "  if (uCvg > 0 && a1 < (uCvg == 1 ? 0.5 : 0.125)) discard;\n"
    "  if (uBl1.x >= 0) { float A = bA(uBl1.y, a1);\n"
    "    c1 = clamp(bP(uBl1.x, c1) * A + bP(uBl1.z, c1) * bB(uBl1.w, A), 0.0, 1.0); }\n"
    "  float A = bA(uBl2.y, a1);\n"
    "  if (uBlFin == 0) frag = vec4(bP(uBl2.x, c1), 1.0);\n"
    "  else if (uBlFin == 1) frag = vec4(clamp(bP(uBl2.x, c1) * A + bP(uBl2.z, c1) * bB(uBl2.w, A), 0.0, 1.0), 1.0);\n"
    "  else frag = vec4(bP(uBl2.x == 1 ? uBl2.z : uBl2.x, c1), A);\n"
    /* P78 DIAGNOSTIC ?p78lodviz=1: tint by the LOD tile (0 none, 1 red, 2 green, 3 blue, 4 magenta; LOD materials) */
    "  if (uIdx >= 0) frag = IC;\n"
    "  if (uLodViz != 0 && uLod.x != 0 && lt > 0) frag.rgb = mix(frag.rgb, lt == 1 ? vec3(1,0,0) : lt == 2 ? vec3(0,1,0) : lt == 3 ? vec3(0,0,1) : vec3(1,0,1), 0.5);\n"
    "}\n";

static GLuint sh(GLenum t, const char *src) {
    GLuint s = glCreateShader(t);
    glShaderSource(s, 1, &src, 0);
    glCompileShader(s);
    GLint ok = 0;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetShaderInfoLog(s, sizeof log, 0, log);
        port_log("[gfx] shader: %s\n", log);
    }
    return s;
}

int gfx_init(void) {
    prog = glCreateProgram();
    glAttachShader(prog, sh(GL_VERTEX_SHADER, VS));
    glAttachShader(prog, sh(GL_FRAGMENT_SHADER, FS));
    glBindAttribLocation(prog, 0, "aPos");
    glBindAttribLocation(prog, 1, "aCol");
    glBindAttribLocation(prog, 2, "aST");
    glBindAttribLocation(prog, 3, "aFog");
    glLinkProgram(prog);
    GLint ok = 0;
    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if (!ok) { port_log("[gfx] program link failed\n"); return -1; }
    glUseProgram(prog);
#define U(v, n) v = glGetUniformLocation(prog, n)
    static const char *tn[6] = {"uT0", "uT1", "uT2", "uT3", "uT4", "uT5"};
    char nm[16];
    for (int k = 0; k < 6; k++) {
        u_tex[k] = glGetUniformLocation(prog, tn[k]);
        snprintf(nm, sizeof nm, "uTP[%d]", k); u_tp[k] = glGetUniformLocation(prog, nm);
        snprintf(nm, sizeof nm, "uTM[%d]", k); u_tm[k] = glGetUniformLocation(prog, nm);
        snprintf(nm, sizeof nm, "uTS[%d]", k); u_ts[k] = glGetUniformLocation(prog, nm);
        glUniform1i(u_tex[k], k);
    }
    U(u_c0, "uC0"); U(u_c1, "uC1"); U(u_a0, "uA0"); U(u_a1, "uA1"); U(u_2cyc, "u2cyc"); U(u_prim, "uPrim");
    U(u_env, "uEnv"); U(u_fogc, "uFogC"); U(u_blendc, "uBlendC"); U(u_primlod, "uPrimLod"); U(u_acmp, "uAcmp");
    U(u_mode, "uMode"); U(u_texon, "uTexOn"); U(u_filt, "uFilt"); U(u_lod, "uLod"); U(u_pixscale, "uPixScale"); U(u_lodviz, "uLodViz"); U(u_splitx, "uSplitX");
    U(u_bl1, "uBl1"); U(u_bl2, "uBl2"); U(u_blfin, "uBlFin"); U(u_k45, "uK45"); U(u_primz, "uPrimZ"); U(u_cvg, "uCvg"); U(u_dbg, "uDbg"); U(u_idx, "uIdx"); U(u_hires, "uHiRes");
    U(u_rhi, "uRHi"); U(u_rclamp, "uRClamp");
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0); glVertexAttribPointer(0, 4, GL_FLOAT, 0, VF * 4, (void *)0);
    glEnableVertexAttribArray(1); glVertexAttribPointer(1, 4, GL_FLOAT, 0, VF * 4, (void *)16);
    glEnableVertexAttribArray(2); glVertexAttribPointer(2, 2, GL_FLOAT, 0, VF * 4, (void *)32);
    glEnableVertexAttribArray(3); glVertexAttribPointer(3, 1, GL_FLOAT, 0, VF * 4, (void *)40);
    GLint vpd[4];
    glGetIntegerv(GL_VIEWPORT, vpd);
    canvas_w = vpd[2]; canvas_h = vpd[3];
    gl_ok = 1;
    port_log("[gfx] F3DEX2 interpreter ready (canvas %dx%d)\n", canvas_w, canvas_h);
    return 0;
}
/* P348 photo mode: the page resized the canvas's drawing buffer (a capture at 2x the canvas resolution, then back);
 * every draw scales N64 pixels by canvas_w / cimg_width, and the framebuffer-copy textures follow the size. */
EMSCRIPTEN_KEEPALIVE void port_gfx_resize(int w, int h) {
    if (w > 0 && h > 0) { canvas_w = w; canvas_h = h; state_dirty = 1; port_log("[gfx] canvas %dx%d\n", w, h); }
}

/* ---- textures: decode a tile out of TMEM into RGBA8, cached by (TMEM generation, tile params) */
/* P193: the texture cache. Before P193 it was direct-mapped on (k0 * 2654435761 ^ k1 * 40503 ^ k2 * 97 ^ k3) & 255, and in a
 * standard mip chain tile 1 (tmem 080 line 2, 32x16) and tile 3 (tmem 0A8 line 1, 8x4) always land in the same slot (the
 * low 8 bits of k2 * 97 ^ k3 are A0 for both, whatever the TMEM generation): binding tile 3 re-uploaded the GL texture
 * already bound to unit 1, so LOD level 1 sampled an 8x4 image with 32x16 addressing, texelFetch outside it returned
 * 0 (alpha 0) and the ALPHA_CVG_SEL ground of level 0x29 (CI4 64x32 mips, cc 26A004/151092FF) was cut away where it
 * used level 1: the sky quad (first draw) showed through as a green patch. Now: a better mixed hash, 8-way probing,
 * and an entry bound by the current apply_state (stamp) is never evicted. ?p193oldtc=1 = the old direct-mapped cache. */
typedef struct { unsigned key[6]; GLuint tex; unsigned stamp, used; } TexEnt;   /* P351: used = last use (LRU victim with High frame rate) */
/* P351: 2048 entries; 256 of them (the P193 cache) are used unless the High frame rate option is on: a game frame decodes
 * a few hundred textures (every TMEM load is a new generation), and its replays find them only if they are still cached */
static TexEnt tcache[2048];
static unsigned tc_stamp = 1;   /* bumped by apply_state: entries bound for the pending draw carry it */
static unsigned char texbuf[1024 * 1024 * 4 / 4];

static inline unsigned tmem8(unsigned a) { return tmem[a & 0xFFF]; }

static void tlut(unsigned idx, unsigned char *o) {
    unsigned a = 0x800 + idx * 2, c = tmem8(a) << 8 | tmem8(a + 1);
    if ((oth_h >> 14 & 3) == 3) { o[0] = o[1] = o[2] = c >> 8; o[3] = c & 0xFF; return; } /* IA16 TLUT */
    o[0] = (c >> 11 & 31) * 255 / 31; o[1] = (c >> 6 & 31) * 255 / 31; o[2] = (c >> 1 & 31) * 255 / 31;
    o[3] = (c & 1) ? 255 : 0;
}

static void texel(const Tile *t, unsigned x, unsigned y, unsigned char *o) {
    unsigned stride = t->line * 8 * (t->siz == 3 ? 2 : 1);
    unsigned bx = t->siz == 0 ? x >> 1 : x << (t->siz - 1);
    unsigned a = t->tmem * 8 + y * stride + bx;
    /* odd rows: the RDP swaps the 32-bit halves of each 64-bit TMEM word. P158: 32-bit texels (kept here as 4 linear
     * bytes, a TMEM word = 2 texels of each half) swap texel pairs, i.e. bytes ^ 8; before P158 they were not swapped,
     * so 32-bit textures stored pre-swizzled for LOAD_BLOCK dxt 0 (pause-menu letters) showed shifted odd rows */
    if (y & 1) a ^= t->siz == 3 ? 8 : 4;
    unsigned b0 = tmem8(a), v, fmt = t->fmt;
    /* 4/8-bit texels are palette indices when TLUT mode is on (the RDP ignores the tile format then).
     * RGBA4/RGBA8 do not exist: Conker's model DLs use them for CI textures and rely on the engine's
     * material DL (segment 8) to turn TLUT mode on, so they are read as CI as well (P8). */
    if (t->siz <= 1 && (fmt == 0 || (oth_h >> 14 & 3))) fmt = 2;
    switch (fmt << 2 | t->siz) {
    case 0 << 2 | 2: v = b0 << 8 | tmem8(a + 1); /* RGBA16 */
        o[0] = (v >> 11 & 31) * 255 / 31; o[1] = (v >> 6 & 31) * 255 / 31; o[2] = (v >> 1 & 31) * 255 / 31;
        o[3] = (v & 1) ? 255 : 0; return;
    case 0 << 2 | 3: o[0] = b0; o[1] = tmem8(a + 1); o[2] = tmem8(a + 2); o[3] = tmem8(a + 3); return;
    case 2 << 2 | 0: tlut((t->pal << 4) + ((x & 1) ? b0 & 15 : b0 >> 4), o); return;  /* CI4 */
    case 2 << 2 | 1: tlut(b0, o); return;                                                /* CI8 */
    case 3 << 2 | 0: v = (x & 1) ? b0 & 15 : b0 >> 4;                                    /* IA4 */
        o[0] = o[1] = o[2] = (v >> 1) * 255 / 7; o[3] = (v & 1) ? 255 : 0; return;
    case 3 << 2 | 1: o[0] = o[1] = o[2] = (b0 >> 4) * 17; o[3] = (b0 & 15) * 17; return; /* IA8 */
    case 3 << 2 | 2: o[0] = o[1] = o[2] = b0; o[3] = tmem8(a + 1); return;              /* IA16 */
    case 4 << 2 | 0: v = (x & 1) ? b0 & 15 : b0 >> 4; o[0] = o[1] = o[2] = o[3] = v * 17; return; /* I4 */
    case 4 << 2 | 1: o[0] = o[1] = o[2] = o[3] = b0; return;                            /* I8 */
    case 2 << 2 | 2: case 2 << 2 | 3: tlut(b0, o); return;                              /* CI16/32: as CI8 */
    case 0 << 2 | 1: case 4 << 2 | 2: o[0] = o[1] = o[2] = b0; o[3] = 255; return;      /* RGBA8 / I16 */
    case 3 << 2 | 3: o[0] = o[1] = o[2] = b0; o[3] = tmem8(a + 1); return;              /* IA32: as IA16 */
    default: o[0] = 255; o[1] = 0; o[2] = 255; o[3] = 255; return;                      /* YUV etc: magenta */
    }
}

/* P35: the decoded image covers every texel the RDP can address after clamp / mirror / mask: 2^mask when
 * masked, else the tile size (clamped). The shader does the addressing (texelFetch), so the GL wrap mode and
 * filter are unused. */
static void tile_dims(const Tile *t, unsigned *w, unsigned *h) {
    unsigned tw = ((t->lrs - t->uls) >> 2) + 1, th = ((t->lrt - t->ult) >> 2) + 1;
    if (t->masks) tw = 1u << (t->masks > 10 ? 10 : t->masks);
    if (t->maskt) th = 1u << (t->maskt > 10 ? 10 : t->maskt);
    if (tw > 1024) tw = 1024;
    if (th > 1024) th = 1024;
    if (!tw) tw = 1;
    if (!th) th = 1;
    *w = tw; *h = th;
}

static unsigned p193_bind[6][6];   /* P193 DIAGNOSTIC: per unit of the last apply_state: tile, GL tex, hash, hit, first texel, w | h << 16 */
static int p193_k = -1;
static GLuint tex_for(int ti, unsigned *w, unsigned *h) {
    const Tile *t = &tiles[ti & 7];
    tile_dims(t, w, h);
    if ((size_t)*w * *h * 4 > sizeof texbuf) *h = sizeof texbuf / 4 / *w;
    unsigned key[6] = {tmem_gen, t->fmt | t->siz << 4 | t->pal << 8 | (oth_h >> 14 & 3) << 20,
                       t->tmem | t->line << 12, *w | *h << 16, 0, 2};
    static int oldtc = -1; if (oldtc < 0) oldtc = port_flag("p193oldtc");
    unsigned hsh;
    TexEnt *e;
    if (oldtc) { hsh = (key[0] * 2654435761u ^ key[1] * 40503u ^ key[2] * 97u ^ key[3]) & 255; e = &tcache[hsh]; }
    else {
        unsigned m = key[0];
        for (int i = 1; i < 4; i++) m = (m ^ key[i]) * 2654435761u, m ^= m >> 15;
        unsigned tmask = hfr_opt ? 2047 : 255;   /* P351 */
        hsh = hfr_opt ? m >> 21 : m >> 24;
        TexEnt *victim = 0;
        e = 0;
        static unsigned tc_clock;
        for (unsigned i = 0; i < (hfr_opt ? 16u : 8u); i++) {
            TexEnt *c = &tcache[(hsh + i) & tmask];
            if (c->tex && !memcmp(c->key, key, sizeof key)) { e = c; break; }
            if (hfr_opt) { if (c->stamp != tc_stamp && (!victim || !c->tex || (victim->tex && c->used < victim->used))) victim = c; }   /* P351: least recently used */
            else if (!victim && c->stamp != tc_stamp) victim = c;   /* first free / not used by the pending draw */
        }
        if (!e) e = victim ? victim : &tcache[hsh];
        e->stamp = tc_stamp; e->used = ++tc_clock;
    }
    if (p193_k >= 0 && p193_k < 6) { p193_bind[p193_k][0] = ti; p193_bind[p193_k][2] = hsh; p193_bind[p193_k][5] = *w | *h << 16; }
    if (e->tex && !memcmp(e->key, key, sizeof key)) { if (p193_k >= 0 && p193_k < 6) { p193_bind[p193_k][1] = e->tex; p193_bind[p193_k][3] = 1; } return e->tex; }
    if (!e->tex) glGenTextures(1, &e->tex);
    memcpy(e->key, key, sizeof key);
    for (unsigned y = 0; y < *h; y++)
        for (unsigned x = 0; x < *w; x++) texel(t, x, y, texbuf + (y * *w + x) * 4);
    glBindTexture(GL_TEXTURE_2D, e->tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *w, *h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texbuf);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    gfx_stats.tex_uploads++;
    if (p193_k >= 0 && p193_k < 6) { p193_bind[p193_k][1] = e->tex; p193_bind[p193_k][3] = 0;
        p193_bind[p193_k][4] = (unsigned)texbuf[0] << 24 | texbuf[1] << 16 | texbuf[2] << 8 | texbuf[3]; }
    return e->tex;
}

static float shiftscale(unsigned sh) { return sh == 0 ? 1.0f : sh <= 10 ? 1.0f / (1 << sh) : (float)(1 << (16 - sh)); }

static void rgba(GLint u, unsigned c) {
    glUniform4f(u, (c >> 24) / 255.0f, (c >> 16 & 255) / 255.0f, (c >> 8 & 255) / 255.0f, (c & 255) / 255.0f);
}

static int filt_mode = -1;   /* P35: 1 = RDP 3-point (default), 2 = ?filter4=1 4-tap bilinear, 0 = ?filter0=1 point */
/* P35 blender (othermode L): cycle-1 selectors at bits 30/26/22/18, cycle-2 at 28/24/20/16 (P, A, M, B);
 * P/M: 0 IN, 1 MEM, 2 BLEND colour, 3 FOG colour; A: 0 IN alpha, 1 FOG alpha, 2 SHADE alpha, 3 zero;
 * B: 0 1-A, 1 MEM alpha (coverage, taken as 1), 2 one, 3 zero. In 2-cycle mode the first cycle always runs
 * (fog) and feeds IN of the second; the final cycle blends only with FORCE_BL (else the RDP keeps P). */
static int bl_last_gl = -1;
static void blend_state(unsigned cyc, int mode) {
    unsigned L = oth_l;
    int c1[4] = {(int)(L >> 30 & 3), (int)(L >> 26 & 3), (int)(L >> 22 & 3), (int)(L >> 18 & 3)};
    int c2[4] = {(int)(L >> 28 & 3), (int)(L >> 24 & 3), (int)(L >> 20 & 3), (int)(L >> 16 & 3)};
    int *fin = cyc == 1 ? c2 : c1;
    if (cyc == 1) glUniform4i(u_bl1, c1[0] == 1 ? 0 : c1[0], c1[1], c1[2] == 1 ? 0 : c1[2], c1[3]);
    else glUniform4i(u_bl1, -1, 0, 0, 0);
    glUniform4i(u_bl2, fin[0], fin[1], fin[2], fin[3]);
    int fb = (L & 0x4000) != 0, fm = 0, gl = 0;
    GLenum sf = GL_ONE, df = GL_ZERO;
    if (mode == 1 || cyc >= 2) fm = 0;
    else if (!fb) { fm = 0; if (fin[0] == 1) fin[0] = 0; glUniform4i(u_bl2, fin[0], fin[1], fin[2], fin[3]); }
    else if (fin[0] != 1 && fin[2] != 1) fm = 1;
    else {
        fm = 2; gl = 1;
        if (fin[0] == 1 && fin[2] == 1) { sf = GL_ZERO; df = GL_ONE; }
        else if (fin[2] == 1) { sf = GL_SRC_ALPHA; df = fin[3] == 0 ? GL_ONE_MINUS_SRC_ALPHA : fin[3] == 3 ? GL_ZERO : GL_ONE; }
        else { df = GL_SRC_ALPHA; sf = fin[3] == 0 ? GL_ONE_MINUS_SRC_ALPHA : fin[3] == 3 ? GL_ZERO : GL_ONE; }
    }
    glUniform1i(u_blfin, fm);
    if (gl) { glEnable(GL_BLEND); glBlendFunc(sf, df); } else glDisable(GL_BLEND);
    bl_last_gl = gl;
}

static unsigned dl_st[10];   /* P193: see draw_log_line */
static void apply_state(void) {
    ws_calc();   /* P350 */
    unsigned cyc = oth_h >> 20 & 3; /* 0 1CYC, 1 2CYC, 2 COPY, 3 FILL */
    unsigned w0 = combine_w0, w1 = combine_w1;
    if (filt_mode < 0) filt_mode = port_flag("filter0") ? 0 : port_flag("filter4") ? 2 : 1;
    glUniform4i(u_c0, w0 >> 20 & 15, w1 >> 28 & 15, w0 >> 15 & 31, w1 >> 15 & 7);
    glUniform4i(u_a0, w0 >> 12 & 7, w1 >> 12 & 7, w0 >> 9 & 7, w1 >> 9 & 7);
    glUniform4i(u_c1, w0 >> 5 & 15, w1 >> 24 & 15, w0 & 31, w1 >> 6 & 7);
    glUniform4i(u_a1, w1 >> 21 & 7, w1 >> 3 & 7, w1 >> 18 & 7, w1 & 7);
    glUniform1i(u_2cyc, cyc == 1);
    rgba(u_prim, prim_col); rgba(u_env, env_col); rgba(u_fogc, fog_col); rgba(u_blendc, blend_col);
    glUniform1f(u_primlod, prim_lod / 255.0f);
    glUniform2f(u_k45, (float)(signed char)(k4k5 >> 9 & 0xFF) / 255.0f, (k4k5 & 0x1FF) / 255.0f);
    glUniform1f(u_primz, (oth_l & 4) && rect_mode == 0 ? (prim_z & 0x7FFF) / 32767.0f : -1.0f);
    unsigned ac = oth_l & 3;
    glUniform1i(u_acmp, ac == 1 ? 1 : ac == 3 ? 3 : 0);
    /* ALPHA_CVG_SEL + CVG_X_ALPHA (TEX_EDGE etc.): coverage = coverage * alpha, low-alpha texels are cut out.
     * P273: ALPHA_CVG_SEL alone (RM_AA_ZB_OPA_SURF, 0x2078) only puts the coverage into the blender's alpha; the
     * combiner alpha never touches coverage, so nothing is cut. Before P273 every ALPHA_CVG_SEL draw discarded
     * alpha < 0.5: Berri's I8 hand texture (alpha = intensity) lost its dark texels and looked transparent.
     * ?p273oldcvg=1 restores the old behaviour. */
    { static int oc = -1; if (oc < 0) oc = port_flag("p273oldcvg");
      glUniform1i(u_cvg, (oth_l & 0x2000) && (oc || (oth_l & 0x1000)) ? ((oth_l & 0x4000) ? 2 : 1) : 0); }
    /* P144: CVG_X_ALPHA + CLR_ON_CVG without FORCE_BL (e.g. the logo-end iris, hud_sniper_scope_draw / hud_scope_lens_draw: black
     * combiner, I8 lens alpha): coverage = pixel coverage * alpha and the colour is written only on coverage
     * overflow, so texels with low alpha leave the framebuffer alone (approximated as "discard below 0.5"). Before,
     * the whole lens square was drawn opaque black. ?p144nocvgx=1 restores the old behaviour. */
    { static int nx = -1; if (nx < 0) nx = port_flag("p144nocvgx");
      if (!nx && !(oth_l & 0x2000) && (oth_l & 0x1080) == 0x1080 && !(oth_l & 0x4000)) glUniform1i(u_cvg, 1); }
    int mode = rect_mode == 1 || cyc == 3 ? 1 : cyc == 2 ? 3 : 0;
    glUniform1i(u_mode, mode);
    int texon = 0;
    { unsigned st[10] = {geom, oth_h, oth_l, combine_w0, combine_w1, tex_on, tex_tile, prim_col, env_col, fog_col}; memcpy(dl_st, st, sizeof st); }
    tc_stamp++;   /* P193: a new set of bound textures */
    if (mode != 1 && (tex_on || rect_mode == 2)) {
        /* tiles base .. base+3: TEXEL1 of 2-cycle mode and the LOD levels (G_TL_LOD, tex_level) */
        int ntile = cyc == 1 ? 2 : 1, lod = (oth_h & 0x10000) && cyc == 1 && rect_mode == 0;
        if (lod) ntile = (int)tex_level + 2 > 6 ? 6 : (int)tex_level + 2;   /* P78: up to 6 tiles (levels 0..4 + 1) */
        for (int k = 0; k < ntile; k++) {
            unsigned w, h;
            int ti = (tex_tile + k) & 7;
            glActiveTexture(GL_TEXTURE0 + k);
            p193_k = k; glBindTexture(GL_TEXTURE_2D, tex_for(ti, &w, &h)); p193_k = -1;
            const Tile *t = &tiles[ti];
            glUniform4f(u_tp[k], t->uls / 4.0f, t->ult / 4.0f, shiftscale(t->shifts), shiftscale(t->shiftt));
            int cls = (t->cms & 2) || !t->masks, clt = (t->cmt & 2) || !t->maskt;
            glUniform4i(u_tm[k], cls | (t->cms & 1) << 1 | clt << 2 | (t->cmt & 1) << 3, t->masks, t->maskt, 0);
            int mxs = (int)((t->lrs >> 2) - (t->uls >> 2)), mxt = (int)((t->lrt >> 2) - (t->ult >> 2));
            glUniform4i(u_ts[k], (int)w, (int)h, mxs < 0 ? 0 : mxs, mxt < 0 ? 0 : mxt);
            texon |= 1 << k;
        }
        glActiveTexture(GL_TEXTURE0);
        glUniform4i(u_lod, lod, (int)tex_level, (oth_h & 0x60000) != 0, 0);
    } else glUniform4i(u_lod, 0, 0, 0, 0);
    if (hxs_on) {   /* P335 */
        glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, hxs_tex);
        texon |= 1; glUniform4f(u_hires, hxs_ox, hxs_oy, 1, 0);
    } else glUniform4f(u_hires, 0, 0, 0, 0);
    {   /* P349 */
        int rh = rect_mode == 2 && !hxs_on ? rect_hires_mode : 0;
        glUniform1i(u_rhi, rh);
        if (rh) glUniform4f(u_rclamp, rect_hires_clamp[0], rect_hires_clamp[1], rect_hires_clamp[2], rect_hires_clamp[3]);
    }
    glUniform1i(u_texon, texon);
    unsigned tf = oth_h >> 12 & 3;   /* G_TF_POINT 0, G_TF_BILERP 2, G_TF_AVERAGE 3 */
    glUniform1i(u_filt, tf == 0 || cyc >= 2 ? 0 : filt_mode);
    { static int ol = -1; if (ol < 0) ol = port_flag("p78oldlod");   /* DIAGNOSTIC ?p78oldlod=1: the pre-P78 (inverted) scale */
      glUniform1f(u_pixscale, ol ? (float)cimg_width / canvas_w : ws_on ? ws_sx : (float)canvas_w / cimg_width); }   /* P78: canvas px per N64 px (P350: of the 4:3 picture) */
    { static int lv = -1; if (lv < 0) lv = port_flag("p78lodviz"); glUniform1i(u_lodviz, lv); }
    { /* P193 DIAGNOSTIC ?p193dbg=F[&p193cc=W1hex]: from retrace F, draws with combiner 26A004/<W1> (default 15FC92F8) cycle
       * through views every 100 retraces: 0 normal, 1 T0, 2 shade, 3 magenta, 4 LOD_FRACTION, 5 (lt/4, texon/63, distant),
       * 6 final alpha, 7 (T0.a, T1.a, 0); P193b: 3 = magenta, 8 = hidden (discard); ?p193cc0 / ?p193cc = the combiner words
       * (decimal: the flags are integers) */
      static int df = -1; static unsigned dcc, dcc0, lastk = ~0u; if (df < 0) { df = port_flag("p193dbg"); dcc = (unsigned)port_flag("p193cc"); if (!dcc) dcc = 0x15FC92F8;
                                                                       dcc0 = (unsigned)port_flag("p193cc0"); if (!dcc0) dcc0 = 0x26A004; }
      int k = 0;
      if (df > 0 && port_frame_count >= (unsigned)df && combine_w0 == dcc0 && combine_w1 == dcc) {
          k = (int)((port_frame_count - df) / 100 % 9);
          if ((unsigned)k != lastk) { lastk = k; port_log("[p193] view %d at frame %u\n", k, port_frame_count); } }
      glUniform1i(u_dbg, k); }
    { static int sp = -1; if (sp < 0) sp = port_flag("p78split"); glUniform1f(u_splitx, sp ? canvas_w / 2.0f : -1.0f); }
    /* depth: Z_CMP / Z_UPD; ZMODE (bits 10-11) DEC -> polygon offset (the RDP's z-delta compare) */
    int zcmp = (geom & G_ZBUFFER) && (oth_l & 0x10) && rect_mode == 0, zupd = (oth_l & 0x20) && rect_mode == 0;
    if (zcmp || zupd) { glEnable(GL_DEPTH_TEST); glDepthFunc(zcmp ? GL_LEQUAL : GL_ALWAYS); } else glDisable(GL_DEPTH_TEST);
    glDepthMask(zupd ? GL_TRUE : GL_FALSE);
    if (zupd && !off_on && hx_cur < 0) zsnap.valid = 0;   /* P349: the RDP would write depth over the frozen frame */
    /* P158: overlays that compare z but do not write it (projected shadows, ZMODE_XLU, coplanar with the floor) get the
     * decal offset too: the RDP's depth compare has a dz tolerance, GL's LEQUAL on differently clipped coplanar
     * triangles z-fights (hatched floor patches under the shadow). ?p158nozofs=1: the old behaviour */
    { static int nz = -1; if (nz < 0) nz = port_flag("p158nozofs");
      if ((oth_l >> 10 & 3) == 3 || (!nz && zcmp && !zupd)) { glEnable(GL_POLYGON_OFFSET_FILL); glPolygonOffset(-1, -2); }
      else glDisable(GL_POLYGON_OFFSET_FILL); }
    blend_state(cyc, mode);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE);  /* the blend factor goes through alpha; keep the canvas opaque */
    /* viewport */
    float sx = canvas_w / (float)cimg_width, sy = canvas_h / CIMG_H;
    if (ws_log_on && !rect_mode) port_log("[p350] task %u tris persp %d vp %d %d %d %d sc %d %.1f,%.1f..%.1f,%.1f\n", gfx_stats.tasks, proj_persp, vp_scale[0], vp_scale[1], vp_trans[0], vp_trans[1],
                                         sc_on, sc_box[0], sc_box[1], sc_box[2], sc_box[3]);
    if (ws_on) {   /* P350: see ws_calc */
        int is3d = !rect_mode && proj_persp;
        float W = (float)cimg_width;
        if (rect_mode) glViewport(0, 0, canvas_w, canvas_h);
        else {
            float w = 2 * vp_scale[0] / 4.0f, h = 2 * vp_scale[1] / 4.0f;
            float x0 = (vp_trans[0] - vp_scale[0]) / 4.0f, y0 = (vp_trans[1] - vp_scale[1]) / 4.0f;
            float d3 = ws_tag == 1 || ws_tag == 2 ? ws_dx : 0;   /* a corner HUD model (health chocolate) moves with its anchor */
            float X0 = is3d ? ws_x3d(x0) + d3 : ws_x2d(x0), X1 = is3d ? ws_x3d(x0 + w) + d3 : ws_x2d(x0 + w);
            glViewport((GLint)floorf(X0 + 0.5f), (GLint)(canvas_h - (y0 + h - VI_Y0) * sy), (GLint)floorf(X1 - X0 + 0.5f), (GLint)(h * sy));
        }
        if (sc_on) {
            float X0, X1, full = sc_box[0] <= 4 && sc_box[2] >= W - 4;
            if (is3d) { X0 = sc_box[0] <= 4 ? 0 : ws_x3d(sc_box[0]); X1 = sc_box[2] >= W - 4 ? canvas_w : ws_x3d(sc_box[2]); }
            else { X0 = full ? 0 : ws_x2d(sc_box[0]); X1 = full ? canvas_w : ws_x2d(sc_box[2]); }
            glEnable(GL_SCISSOR_TEST);
            glScissor((GLint)floorf(X0 + 0.5f), (GLint)(canvas_h - (sc_box[3] - VI_Y0) * sy), (GLint)floorf(X1 - X0 + 0.5f), (GLint)((sc_box[3] - sc_box[1]) * sy + 0.5f));
        } else glDisable(GL_SCISSOR_TEST);
        return;
    }
    if (rect_mode) glViewport(0, 0, canvas_w, canvas_h);
    else {
        float w = 2 * vp_scale[0] / 4.0f, h = 2 * vp_scale[1] / 4.0f;
        float x0 = (vp_trans[0] - vp_scale[0]) / 4.0f, y0 = (vp_trans[1] - vp_scale[1]) / 4.0f;
        glViewport((GLint)(x0 * sx), (GLint)(canvas_h - (y0 + h - VI_Y0) * sy), (GLint)(w * sx), (GLint)(h * sy));
    }
    /* P35b: G_SETSCISSOR (the RDP clips every primitive to it; the level frames use x 2..290, y 0..216) */
    if (sc_on) {
        glEnable(GL_SCISSOR_TEST);
        glScissor((GLint)(sc_box[0] * sx), (GLint)(canvas_h - (sc_box[3] - VI_Y0) * sy), (GLint)((sc_box[2] - sc_box[0]) * sx + 0.5f), (GLint)((sc_box[3] - sc_box[1]) * sy + 0.5f));
    } else glDisable(GL_SCISSOR_TEST);
}

/* P193: the state the pending batch was drawn with (saved by apply_state). Before P193 the [draw] line printed the
 * globals at flush time, i.e. the NEXT draw's state (flush runs after the new state commands): P189 took the ground
 * draw for the CI8 leaf cut-out because of that. */
static int draw_log; /* P33: ?drawlog=N: one line per draw call of gfx task N (state + NDC box) */
static void draw_log_line(void) {
    float x0 = 1e9f, x1 = -1e9f, y0 = 1e9f, y1 = -1e9f, z0 = 1e9f, z1 = -1e9f; int behind = 0;
    for (int i = 0; i < nbatch; i++) {
        const float *o = batch + i * VF;
        if (o[3] <= 0) { behind++; continue; }
        float x = o[0] / o[3], y = o[1] / o[3], z = o[2] / o[3];
        if (x < x0) x0 = x; if (x > x1) x1 = x; if (y < y0) y0 = y; if (y > y1) y1 = y; if (z < z0) z0 = z; if (z > z1) z1 = z;
    }
    const float *o = batch;
    unsigned ao = 0x60 + light_nls + (light_bg ? 0 : 48);   /* P35b: BG ambient = record M, else M + 1 */
    port_log("[draw] lights %s %s nls %u ambient %02X%02X%02X L0 %02X%02X%02X dir %d %d %d att %02X pos %d %d %d | rare10 S %.4f %.4f %.4f T %.0f %.0f %.0f | blfin %d gl %d filt %d\n",
             light_bg ? "BG" : "other", light_seen ? "set" : "none", light_nls, lbuf[ao % sizeof lbuf], lbuf[(ao + 1) % sizeof lbuf], lbuf[(ao + 2) % sizeof lbuf],
             lbuf[0x60], lbuf[0x61], lbuf[0x62], (signed char)lbuf[0x68], (signed char)lbuf[0x69], (signed char)lbuf[0x6A], lbuf[0x6C],
             (short)(lbuf[0x80] << 8 | lbuf[0x81]), (short)(lbuf[0x82] << 8 | lbuf[0x83]), (short)(lbuf[0x84] << 8 | lbuf[0x85]),
             rare_s(0), rare_s(1), rare_s(2), rare_t(0), rare_t(1), rare_t(2), -1, bl_last_gl, filt_mode);
    port_log("[draw] vp scale %d %d %d trans %d %d %d cimg %u canvas %dx%d\n", vp_scale[0], vp_scale[1], vp_scale[2], vp_trans[0], vp_trans[1], vp_trans[2], cimg_width, canvas_w, canvas_h);
    port_log("[draw] #%d %d verts (%d w<=0) rm %d ndc x %.2f..%.2f y %.2f..%.2f z %.3f..%.3f | geom %06X oth %06X/%08X cc %06X/%08X tex %d tile %d prim %08X env %08X fog %08X v0 rgba %.2f %.2f %.2f %.2f st %.1f %.1f fog %.2f\n",
             p193_idx, nbatch, behind, rect_mode, x0, x1, y0, y1, z0, z1, dl_st[0], dl_st[1], dl_st[2], dl_st[3], dl_st[4], dl_st[5], dl_st[6],
             dl_st[7], dl_st[8], dl_st[9], o[4], o[5], o[6], o[7], o[8], o[9], o[10]);
}
/* P78: ?p78tex=N: per-material dump of gfx task N (node too: no GL needed). At each state change before
 * triangles: othermode, combiner, G_TEXTURE, the tiles base..base+4 (fmt siz line tmem pal cm mask shift, tile
 * size in texels), and once per distinct (TMEM generation, tile) the decoded texels as hex rows
 * ([p78hex], port/tools/p78tex.py turns them into PNGs). At the flush: the batch's texel density in N64 pixels
 * per axis (|ds/dx| etc. from each triangle's screen-space gradients, tile 0 units): what the RDP's LOD sees. */
static int p78_task = -1, p78_on, p78_mat, p78_ntex;
static int p158_on;   /* P158: ?p158f dump task (also logs texture loads) */
static void p78_material(void) {
    if (!p78_on || !tex_on) return;
    p78_mat++;
    port_log("[p78] mat %d: oth %06X/%08X cc %06X/%08X tex lvl %u tile %u on %u sc %.4f %.4f prim %08X env %08X lodfrac %02X\n",
             p78_mat, oth_h, oth_l, combine_w0, combine_w1, tex_level, tex_tile, tex_on, tex_sc_s, tex_sc_t, prim_col, env_col, prim_lod);
    unsigned nt = tex_level + 2; if (nt > 6) nt = 6;
    for (unsigned k = 0; k < nt; k++)   /* P193 DIAGNOSTIC: what apply_state bound */
        port_log("[p193] mat %d unit %u: tile %u gl %u hash %u %s texel0 %08X %ux%u\n", p78_mat, k, p193_bind[k][0], p193_bind[k][1], p193_bind[k][2],
                 p193_bind[k][3] ? "hit" : "miss", p193_bind[k][4], p193_bind[k][5] & 0xFFFF, p193_bind[k][5] >> 16);
    for (unsigned k = 0; k < nt; k++) {
        const Tile *t = &tiles[(tex_tile + k) & 7];
        port_log("[p78]   tile %u: fmt %u siz %u line %u tmem %03X pal %u cms %u cmt %u mask %u/%u shift %u/%u ul %.2f %.2f lr %.2f %.2f\n",
                 (tex_tile + k) & 7, t->fmt, t->siz, t->line, t->tmem, t->pal, t->cms, t->cmt, t->masks, t->maskt, t->shifts,
                 t->shiftt, t->uls / 4.0, t->ult / 4.0, t->lrs / 4.0, t->lrt / 4.0);
        if (k == 0 && p158_on && t->siz == 1 && (t->fmt == 2 || (oth_h >> 14 & 3))) {   /* P189 DIAGNOSTIC: CI8 palette */
            static unsigned pgen = ~0u;
            if (pgen != tmem_gen) {
                char pb[256 * 4 + 1]; int m = 0; pgen = tmem_gen;
                for (unsigned e = 0; e < 256; e++) m += snprintf(pb + m, sizeof pb - m, "%02X%02X", tmem8(0x800 + e * 2), tmem8(0x801 + e * 2));
                port_log("[p189pal] mat %d tlut mode %u: %s\n", p78_mat, oth_h >> 14 & 3, pb);
            }
        }
        static unsigned seen[1024][3]; static unsigned nseen;
        unsigned key0 = tmem_gen, key1 = t->tmem | t->line << 12 | t->siz << 24 | t->fmt << 28, key2 = t->masks | t->maskt << 4 | t->pal << 8;
        int dup = 0;
        for (unsigned j = 0; j < nseen; j++) if (seen[j][0] == key0 && seen[j][1] == key1 && seen[j][2] == key2) dup = 1;
        if (dup || nseen >= 1024 || p78_ntex >= (p158_on ? 600 : 60)) continue;   /* P273: p158 dumps 600 */
        seen[nseen][0] = key0; seen[nseen][1] = key1; seen[nseen][2] = key2; nseen++;
        unsigned w, h; tile_dims(t, &w, &h);
        if (p158_on ? w > 256 || h > (w <= 8 ? 256u : 128u) : w > 64 || h > (w <= 8 ? 256u : 64u)) continue;   /* P202: p158 narrow strips up to 256 rows (backdrop 4x256) */   /* P94: narrow gradient strips (sky 4x256) too; P158: up to 256x128 */
        p78_ntex++;
        port_log("[p78hex] T%d mat %d tile %u %ux%u\n", p78_ntex, p78_mat, (tex_tile + k) & 7, w, h);
        for (unsigned y = 0; y < h; y++) {
            char b[256 * 8 + 1]; int m = 0;
            for (unsigned x = 0; x < w; x++) { unsigned char o[4]; texel(t, x, y, o); m += snprintf(b + m, sizeof b - m, "%02X%02X%02X%02X", o[0], o[1], o[2], o[3]); }
            port_log("[p78hex] %s\n", b);
        }
    }
}
static void p78_density(void) {
    if (!p78_on || !tex_on || nbatch < 3) return;
    float dmin = 1e9f, dmax = 0, ssum = 0; int n = 0;
    const Tile *t0 = &tiles[tex_tile & 7];
    float shs = t0->shifts == 0 ? 1.0f : t0->shifts <= 10 ? 1.0f / (1 << t0->shifts) : (float)(1 << (16 - t0->shifts));
    for (int i = 0; i + 2 < nbatch; i += 3) {
        const float *p[3] = {batch + i * VF, batch + (i + 1) * VF, batch + (i + 2) * VF};
        if (p[0][3] <= 0 || p[1][3] <= 0 || p[2][3] <= 0) continue;
        float X[3], Y[3];
        for (int k = 0; k < 3; k++) { X[k] = (p[k][0] / p[k][3] * 0.5f + 0.5f) * cimg_width; Y[k] = (p[k][1] / p[k][3] * 0.5f + 0.5f) * CIMG_H; }
        float a = (X[1] - X[0]) * (Y[2] - Y[0]) - (X[2] - X[0]) * (Y[1] - Y[0]);
        if (a > -0.5f && a < 0.5f) continue;
        float ds1 = (p[1][8] - p[0][8]) * shs, ds2 = (p[2][8] - p[0][8]) * shs, dt1 = p[1][9] - p[0][9], dt2 = p[2][9] - p[0][9];
        float dsdx = (ds1 * (Y[2] - Y[0]) - ds2 * (Y[1] - Y[0])) / a, dsdy = (ds2 * (X[1] - X[0]) - ds1 * (X[2] - X[0])) / a;
        float dtdx = (dt1 * (Y[2] - Y[0]) - dt2 * (Y[1] - Y[0])) / a, dtdy = (dt2 * (X[1] - X[0]) - dt1 * (X[2] - X[0])) / a;
        float m = fabsf(dsdx); if (fabsf(dsdy) > m) m = fabsf(dsdy); if (fabsf(dtdx) > m) m = fabsf(dtdx); if (fabsf(dtdy) > m) m = fabsf(dtdy);
        if (m < dmin) dmin = m; if (m > dmax) dmax = m; ssum += m; n++;
        if (fabsf(a) > 2000)   /* big (near) triangles: the gradients and the vertices */
            port_log("[p78]     big tri area %.0f: ds/dx %.3f ds/dy %.3f dt/dx %.3f dt/dy %.3f | (%.0f,%.0f s %.1f t %.1f w %.0f) (%.0f,%.0f s %.1f t %.1f w %.0f) (%.0f,%.0f s %.1f t %.1f w %.0f)\n",
                     fabsf(a) / 2, dsdx, dsdy, dtdx, dtdy, X[0], Y[0], p[0][8], p[0][9], p[0][3], X[1], Y[1], p[1][8], p[1][9], p[1][3],
                     X[2], Y[2], p[2][8], p[2][9], p[2][3]);
    }
    if (n) port_log("[p78]   draw %d tris (%d front): texels per N64 pixel (affine, tile %u) min %.3f mean %.3f max %.3f\n",
                    nbatch / 3, n, tex_tile, dmin, ssum / n, dmax);
}
static void flush(void) {
    if (hfr_drop) { nbatch = 0; return; }   /* P351: a replay draws only on the screen */
    if (draw_log && nbatch) draw_log_line();
    if (nbatch) p78_density();
    if (nbatch) p193_idx++;
    if (!nbatch || !gl_ok) { nbatch = 0; return; }
    { static int f = -1; if (f < 0) f = port_flag("p193idx");   /* P193 DIAGNOSTIC: draw index colours for 100 retraces from F */
      int ix = f > 0 && port_frame_count >= (unsigned)f && port_frame_count < (unsigned)f + 100 ? p193_idx - 1 : -1;
      /* ?p193bucket=F: from retrace F, window k (100 retraces each, 10 windows) shows draws k*16 .. k*16+15 in their index colour */
      static int bf = -1; if (bf < 0) bf = port_flag("p193bucket");
      if (bf > 0 && port_frame_count >= (unsigned)bf && port_frame_count < (unsigned)bf + 1000) {
          int k = (int)((port_frame_count - bf) / 100);
          static int lastk = -1; if (k != lastk) { lastk = k; port_log("[p193] bucket %d (draws %d..%d) at frame %u task %u\n", k, k * 16, k * 16 + 15, port_frame_count, gfx_stats.tasks); }
          if (p193_idx - 1 >= k * 16 && p193_idx - 1 < k * 16 + 16) ix = p193_idx - 1; }
      glUniform1i(u_idx, ix);
      /* ?p193pick=F[&p193d=D]: from retrace F, 100-retrace windows: 0 normal, 1 draw 0 hidden, 2 draw 0 magenta (no discard),
       * 3 draw 0 shade, 4 draw D (default 48) hidden, 5 draw D T0, 6 draw D shade, 7 draw D final alpha */
      static int pf = -1, pd; if (pf < 0) { pf = port_flag("p193pick"); pd = port_flag("p193d"); if (!pd) pd = 48; }
      if (pf > 0 && port_frame_count >= (unsigned)pf && port_frame_count < (unsigned)pf + 800) {
          static const int vw[8] = {0, 8, 3, 2, 8, 1, 2, 6};
          int k = (int)((port_frame_count - pf) / 100), tgt = k == 0 ? -1 : k <= 3 ? 0 : pd;
          static int lastk = -1; if (k != lastk) { lastk = k; port_log("[p193] pick window %d at frame %u\n", k, port_frame_count); }
          glUniform1i(u_dbg, p193_idx - 1 == tgt ? vw[k] : 0); } }
    if (off_on) off_drawn = 1;   /* P161 */
    glBufferData(GL_ARRAY_BUFFER, nbatch * VF * 4, batch, GL_STREAM_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, nbatch);
    gfx_stats.draws++;
    nbatch = 0;
}

static void need_state(int rm) {
    if (rm != rect_mode) { flush(); rect_mode = rm; state_dirty = 1; }
    if (state_dirty) { flush(); if (gl_ok) apply_state(); if (p78_on && rm == 0) p78_material(); state_dirty = 0; }
    if (nbatch + 6 > BATCH_TRIS * 3) flush();
}

static void put(const V *v, float sshift, float tshift) {
    float *o = batch + nbatch++ * VF;
    o[0] = v->x; o[1] = v->y; o[2] = v->z; o[3] = v->w;
    o[4] = v->r; o[5] = v->g; o[6] = v->b; o[7] = v->a;
    o[8] = v->s * sshift; o[9] = v->t * tshift; o[10] = v->fog;
}

/* P61 ?p61model=N: the game's own model DL. obj_draw_model_dl (port P57 C) emits, per visible sub-DL k of a model,
 * G_MTX (MV load) g_model_draw_ident_mtx + G_DL g_model_dl_tables[model][k]. Its G_MTX word is `&g_model_draw_ident_mtx & 0x1FFFFFFF` like the asm's
 * physical D_C42B8; in wasm the label is a mirror address (< 0x20000000), so the mask keeps it and gfx_addr takes the
 * wasm class; a true N64 physical value (< 8 MB) takes the segment-0 / RDRAM-mirror class. That G_MTX word marks the
 * model DL: the next G_DL is a model sub-DL, and everything below it (until it returns) is counted here. */
extern unsigned char g_model_draw_ident_mtx[] __attribute__((weak));   /* weak: sched_demo links the renderer without the game; was D_800C42B8 */
static int p61_flag = -1, p61_depth = -1, p61_pend, p61_tr, p61_trn;
static unsigned p61_mark, p61_mtx, p61_dl, p61_tris, p61_verts, p61_imtx, p61_bad0, p61_bad, p61_cmds, p61_frames;
static unsigned p61_icls[4], p61_vbad;
static float p61_mn[2], p61_mx[2];
static unsigned p61_cls(unsigned a) { return a >= 0x80000000u ? 0 : a >= PORT_WASM_BASE ? 1 : a >> 24 ? 2 : 3; }

static void tri(unsigned i0, unsigned i1, unsigned i2) {
    gfx_stats.tris++;
    if (p61_depth >= 0) p61_tris++;
    if (gfx_measure_only) return;
    const V *a = &vb[i0 & 63], *b = &vb[i1 & 63], *c = &vb[i2 & 63];
    if (geom & (G_CULL_FRONT | G_CULL_BACK)) {
        float dx1 = a->x / a->w - b->x / b->w, dy1 = a->y / a->w - b->y / b->w;
        float dx2 = c->x / c->w - b->x / b->w, dy2 = c->y / c->w - b->y / b->w;
        float cross = dx1 * dy2 - dy1 * dx2;
        if ((a->w < 0) ^ (b->w < 0) ^ (c->w < 0)) cross = -cross;
        if ((geom & G_CULL_FRONT) && (geom & G_CULL_BACK)) return;
        if ((geom & G_CULL_FRONT) && cross <= 0) return;
        if ((geom & G_CULL_BACK) && cross >= 0) return;
    }
    if (off_on && off_zimg) zsnap.valid = 0;   /* P349: the z image gets more than the copied frame */
    need_state(0);
    put(a, 1, 1); put(b, 1, 1); put(c, 1, 1);   /* P35: the tile shift is applied per tile in the shader */
    if (ws_on && proj_persp) { float *o = batch + (nbatch - 3) * VF; o[0] /= ws_k; o[VF] /= ws_k; o[2 * VF] /= ws_k; }   /* P350 */
}

/* P337 (port/ultra/pc_nethash.c): every RDRAM range written from GPU pixels is reported before the write, so the
 * online-multiplayer state hash leaves it out (GPU bytes may differ between browsers); 1 = ?netgpujunk, write a fixed
 * pattern instead (proves the game logic never reads them). */
int port_net_gpu_write(void *p, unsigned len);
/* P137: offscreen colour image helpers (see off_on) */
static GLuint off_fbo, off_tex, off_zfbo, off_ztex, off_cur;   /* P161: own FBO for the z image, off_cur = bound one */
static void off_writeback(void) {
    static unsigned char px[320 * 256 * 4];
    unsigned char *dst = gfx_addr(off_addr);
    unsigned w = off_w, h = off_rows, x, y;
    flush();
    if (off_zimg && !off_drawn) return;    /* P161: only depth clears since the z image became the colour image */
    off_drawn = 0;
    if (off_zimg) { static unsigned nz; nz++; if (!(nz & (nz - 1))) port_log("[p161] z image written back as a colour image (%u times, frame %u)\n", nz, port_frame_count); }
    if (!dst || w > 320 || h == 0 || h > OFF_FBO_H) return;
    glReadPixels(0, OFF_FBO_H - h, w, h, GL_RGBA, GL_UNSIGNED_BYTE, px);
    if (port_net_gpu_write(dst, w * h * (off_siz == 1 ? 1 : off_siz == 2 ? 2 : 4))) memset(px, 0x5A, sizeof px); /* P337 */
    for (y = 0; y < h; y++)                 /* GL row 0 is the bottom: N64 row y = read row h - 1 - y (P140) */
        for (x = 0; x < w; x++) {
            const unsigned char *q = px + ((h - 1 - y) * w + x) * 4;
            unsigned i = y * w + x;
            if (off_siz == 1) *VBE8(dst + i) = q[0];       /* the shadow pass: CI/I 8-bit, 64 wide (4 KB) */
            else if (off_siz == 2) {
                unsigned v = (q[0] >> 3) << 11 | (q[1] >> 3) << 6 | (q[2] >> 3) << 1 | 1;
                *VBE8(dst + 2 * i) = v >> 8; *VBE8(dst + 2 * i + 1) = v & 0xFF;
            } else if (off_siz == 3) {
                *VBE8(dst + 4 * i) = q[0]; *VBE8(dst + 4 * i + 1) = q[1]; *VBE8(dst + 4 * i + 2) = q[2]; *VBE8(dst + 4 * i + 3) = 0xFF;
            }
        }
}
static void off_begin(unsigned addr, unsigned w, unsigned siz) {
    flush();
    if (addr == zimg_addr) {   /* P161: the z image as a colour image (pause frozen frame), 320 x OFF_FBO_H, allocated once */
        if (!off_zfbo) {
            glGenFramebuffers(1, &off_zfbo); glGenTextures(1, &off_ztex);
            glBindTexture(GL_TEXTURE_2D, off_ztex);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 320, OFF_FBO_H, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
            glBindFramebuffer(GL_FRAMEBUFFER, off_zfbo);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, off_ztex, 0);
        }
        off_cur = off_zfbo;
    } else if (!off_fbo || off_fbo_w != w) {
        if (!off_fbo) { glGenFramebuffers(1, &off_fbo); glGenTextures(1, &off_tex); }
        glBindTexture(GL_TEXTURE_2D, off_tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, OFF_FBO_H, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, off_fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, off_tex, 0);
        off_fbo_w = w;
    }
    if (addr != zimg_addr) off_cur = off_fbo;
    glBindFramebuffer(GL_FRAMEBUFFER, off_cur);
    off_saved_w = canvas_w; off_saved_h = canvas_h;
    canvas_w = w; canvas_h = OFF_FBO_H;
    off_on = 1; off_addr = addr; off_w = w; off_siz = siz; off_rows = w > OFF_FBO_H ? OFF_FBO_H : w; state_dirty = 1;
    off_drawn = 0; off_zimg = addr == zimg_addr;
    if (off_zimg) { zsnap.valid = 0; zsnap.due = hires_2d || ws_opt; }   /* P349: a new picture in the z image (P350: widescreen too) */
    if (off_zimg) { unsigned r = (unsigned)(vi_y0 + (vi_h > 0 ? vi_h : w * 0.75f) + 0.999f); off_rows = r > OFF_FBO_H ? OFF_FBO_H : r; }
    { static unsigned n; if (n++ < 4) port_log("[p137] offscreen colour image %08X %u wide siz %u (frame %u)\n", addr, w, siz, port_frame_count); }
}
static void off_end(void) {
    if (!off_on) return;
    off_writeback();
    { static unsigned n; if (n++ < 4) port_log("[p140] offscreen image %08X written back as %ux%u siz %u (frame %u)\n", off_addr, off_w, off_rows, off_siz, port_frame_count); }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    canvas_w = off_saved_w; canvas_h = off_saved_h;
    off_on = 0; state_dirty = 1;
}

/* P335: full-frame images the game draws into besides the screen. fb_ghost_render (the frame-blend "ghost" / motion
 * blur, g_fb_ghost_image) selects a second 292-wide RGBA16 colour image in the same task, copies the screen image into
 * it with 1:1 texture rectangles (LOADTILE strips of the screen), selects the screen again, and the next frame draws
 * that image back over the new frame with an alpha (LOADBLOCK strips, blender IN * a + MEM * (1 - a)). The RDP does
 * all of it in RDRAM at the framebuffer's resolution. Before P335 the port took the ghost image for a screen image
 * (P161): the copy's texture reads of the screen wrote the canvas copy of two frames ago into RDRAM and drew it at
 * N64 resolution over the canvas, and the ghost image was never written: one pixelated frame frozen for the whole
 * effect. Now a second >= 256-wide 16-bit colour image in a task that is not one of the screen images is an FBO
 * texture at canvas resolution (hx[]): draws into it render into the texture, texture reads of the screen image while
 * it is bound come from a snapshot of the canvas (taken at the first such read), and later texture rectangles that
 * read it sample the texture per canvas pixel (uHiRes). Its RDRAM is not written (only the RDP reads the ghost). The
 * camera's depth-row buffer (camera_read_depth_row, a 292 x 1 copy of a z row) takes this path too; its RDRAM was not
 * written before either, and its copy rectangle no longer lands on the canvas.
 * ?p335off=1 = the old behaviour; ?p335log=F logs from retrace F. */
#define HX_N 2
static struct { unsigned char *p; unsigned w, rows; GLuint tex, fbo; int tw, th; unsigned task; } hx[HX_N];
static int hx_cur = -1;                  /* slot bound as the colour image, -1 none */
static GLuint hx_snap; static int hx_snap_w, hx_snap_h, hx_snap_due;
/* texture source: kind 0 none, 1 the screen image (snapshot), 2 hx slot, P349: 3 the z image holding the pause frame
 * (zsnap), 4 a screen image copied into that z image; idx = texel index of timg in the image */
static struct { int kind, slot; unsigned char *p; unsigned idx, w; } hx_src;
static struct { int kind, slot; unsigned char *p; float x, y; unsigned tmem, gen; } hx_load;   /* source px of the first TMEM texel */
static unsigned hx_nrect[2];
static GLuint bound_fb(void) { return off_on ? off_cur : hx_cur >= 0 ? hx[hx_cur].fbo : 0; }
static int hx_disabled(void) { static int f = -1; if (f < 0) f = port_flag("p335off"); return f; }
static int hx_logging(void) { static int f = -1, n; if (f < 0) f = port_flag("p335log");
    return f > 0 && port_frame_count >= (unsigned)f && n++ < 300; }

/* P161: write-back of the on-screen frame into the game's colour image when the game reads it as a texture
 * (the pause menu draws the frozen frame from the last colour image, LOADTILE strips of a 292-wide RGBA16 image).
 * The port renders the main frame only on the GL canvas, so RDRAM held an empty image (black pause background).
 * At the end of each gfx task whose colour image is a screen image (>= 256 wide, not the z-buffer, not offscreen)
 * the canvas is copied into a GL texture kept per colour-image address (GPU copy, FBC_N slots). A SETTIMG inside
 * one of those images, other than the image being drawn, reads the copy back once (glReadPixels only then) and writes
 * it as RGBA5551 big-endian in the image's N64 pixel size (rows of the VI view, P147; rows outside left as they are).
 * ?p161nofb=1 turns it off (old behaviour). */
#define FBC_N 4
static struct { unsigned char *p; unsigned w, rows; GLuint tex, fbo; int tw, th, dirty; float y0, h; unsigned age; float ox, bw; } fbc[FBC_N];   /* P350: ox / bw the 4:3 picture in the copy */
static unsigned char *fbc_task_p; static unsigned fbc_task_w, fbc_clock;
/* P351: with the High frame rate option, fbc_task_end keeps the copy it replaces (what that image held before its last
 * task: the picture the task started from, fbc_restore) for the replays of that task */
static struct { GLuint tex; int tw, th; unsigned char *p; } fbc_pre[FBC_N];
static int fbc_off = -1, fbc_log = -1;   /* ?p161log=F: log copies / hits from retrace F (200 lines) */
static int fbc_logging(void) { static int n; if (fbc_log < 0) fbc_log = port_flag("p161log");
    return fbc_log > 0 && port_frame_count >= (unsigned)fbc_log && n++ < 200; }
static void fbc_task_end(void) {
    unsigned char *p = fbc_task_p; int i, s = -1;
    fbc_task_p = 0;
    if (!p || !gl_ok || gfx_measure_only || fbc_off) return;
    for (i = 0; i < FBC_N; i++) if (fbc[i].p == p) s = i;
    if (s < 0) { s = 0; for (i = 1; i < FBC_N; i++) if (fbc[i].age < fbc[s].age) s = i; fbc[s].p = p; }
    flush();
    if (hfr_opt && fbc[s].tex) {   /* P351: the copy the next task of this image starts from goes on in fbc_pre (replays start from it) */
        GLuint tx = fbc_pre[s].tex; int tw = fbc_pre[s].tw, th = fbc_pre[s].th;
        fbc_pre[s].tex = fbc[s].tex; fbc_pre[s].tw = fbc[s].tw; fbc_pre[s].th = fbc[s].th; fbc_pre[s].p = fbc[s].p;
        fbc[s].tex = tx; fbc[s].tw = tw; fbc[s].th = th;
    }
    if (!fbc[s].fbo) glGenFramebuffers(1, &fbc[s].fbo);
    if (!fbc[s].tex) { glGenTextures(1, &fbc[s].tex); fbc[s].tw = fbc[s].th = 0; }
    glBindTexture(GL_TEXTURE_2D, fbc[s].tex);
    if (fbc[s].tw != canvas_w || fbc[s].th != canvas_h) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, canvas_w, canvas_h, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        fbc[s].tw = canvas_w; fbc[s].th = canvas_h;
    }
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, canvas_w, canvas_h);   /* default framebuffer (RGB8, no alpha) */
    ws_calc(); fbc[s].ox = ws_on ? ws_ox : 0; fbc[s].bw = ws_on ? ws_sx * cimg_width : 0;   /* P350 */
    fbc[s].w = fbc_task_w; fbc[s].y0 = vi_y0; fbc[s].h = vi_h > 0 ? vi_h : fbc_task_w * 0.75f;
    fbc[s].rows = (unsigned)(fbc[s].y0 + fbc[s].h + 0.999f); if (fbc[s].rows > 288) fbc[s].rows = 288;
    fbc[s].dirty = 1; fbc[s].age = ++fbc_clock;
    if (fbc_logging()) port_log("[p161] task %u frame %u: canvas copied for %p (slot %d)\n", gfx_stats.tasks, port_frame_count, (void *)p, s);
    state_dirty = 1;   /* texture binding changed */
}
/* P161: the RDP colour image keeps its pixels between frames, the GL canvas is cleared at every task start
 * (gfx_frame_begin). The pause menu relies on that: it draws the darkened frozen frame into each screen image once
 * (first paused frame, task N and N+1) and later frames only draw the menu on top. So when a task first selects a
 * screen image that has a copy (same canvas size), the copy is blitted onto the canvas before any draw: the canvas
 * starts with what the image held when its last task ended (normal frames overdraw it). ?p161norestore=1 = off. */
static void fbc_restore(const unsigned char *p) {
    static int norestore = -1; int i;
    if (norestore < 0) norestore = port_flag("p161norestore");
    if (norestore || !gl_ok || gfx_measure_only || fbc_off || off_on) return;
    for (i = 0; i < FBC_N; i++) {
        GLuint tex = fbc[i].tex; int tw = fbc[i].tw, th = fbc[i].th;
        if (hfr_mode == 2) {   /* P351: a replay starts from what the recorded task started from */
            if (fbc_pre[i].p != p) continue;
            tex = fbc_pre[i].tex; tw = fbc_pre[i].tw; th = fbc_pre[i].th;
        }
        if (fbc[i].p != p || !tex || tw != canvas_w || th != canvas_h) continue;
        flush();
        glBindFramebuffer(GL_READ_FRAMEBUFFER, fbc[i].fbo);
        glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glDisable(GL_SCISSOR_TEST);
        glBlitFramebuffer(0, 0, canvas_w, canvas_h, 0, 0, canvas_w, canvas_h, GL_COLOR_BUFFER_BIT, GL_NEAREST);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        state_dirty = 1;
        return;
    }
}
static void fbc_check_timg(const unsigned char *t) {
    static unsigned char px[1280 * 960 * 4];
    int i;
    if (hfr_mode == 2) return;   /* P351: a replay changes no game memory */
    for (i = 0; i < FBC_N; i++) {
        unsigned char *dst = fbc[i].p; unsigned w = fbc[i].w, H = fbc[i].rows, x, y;
        if (!dst || t < dst || t >= dst + 2 * w * H) continue;
        if (fbc_logging()) port_log("[p161] task %u frame %u: texture read %p in slot %d (%p) dirty %d, drawing into %p\n", gfx_stats.tasks,
                                    port_frame_count, (void *)t, i, (void *)dst, fbc[i].dirty, (void *)fbc_task_p);
        if (!fbc[i].dirty || dst == fbc_task_p) continue;
        fbc[i].dirty = 0;
        hfr_fx = 1;   /* P351 */
        /* P351: a canvas larger than px (the Full-resolution option) is first scaled down on the GPU (nearest) into
         * fbc_small, and read at that size; the row / column mapping below works on the read size (rw x rh) */
        int rw = fbc[i].tw, rh = fbc[i].th;
        float rs = 1;
        flush();
        glBindFramebuffer(GL_FRAMEBUFFER, fbc[i].fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbc[i].tex, 0);
        if ((size_t)rw * rh * 4 > sizeof px) {
            static GLuint fbc_small_tex, fbc_small_fbo; static int sw, sh;
            rs = fminf(1280.0f / rw, 960.0f / rh); rw = (int)(rw * rs); rh = (int)(rh * rs);
            if (!fbc_small_tex) { glGenTextures(1, &fbc_small_tex); glGenFramebuffers(1, &fbc_small_fbo); }
            if (sw != rw || sh != rh) {
                glBindTexture(GL_TEXTURE_2D, fbc_small_tex);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, rw, rh, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
                glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbc_small_fbo);
                glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbc_small_tex, 0);
                sw = rw; sh = rh;
            }
            glBindFramebuffer(GL_READ_FRAMEBUFFER, fbc[i].fbo);
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbc_small_fbo);
            glDisable(GL_SCISSOR_TEST);
            glBlitFramebuffer(0, 0, fbc[i].tw, fbc[i].th, 0, 0, rw, rh, GL_COLOR_BUFFER_BIT, GL_NEAREST);
            glBindFramebuffer(GL_FRAMEBUFFER, fbc_small_fbo);
        }
        glReadPixels(0, 0, rw, rh, GL_RGBA, GL_UNSIGNED_BYTE, px);
        glBindFramebuffer(GL_FRAMEBUFFER, bound_fb());   /* P335: or the hx image */
        if (port_net_gpu_write(dst, 2 * w * H)) memset(px, 0x5A, sizeof px);   /* P337 */
        for (y = 0; y < H; y++) {
            float cy = (y + 0.5f - fbc[i].y0) * rh / fbc[i].h;   /* canvas row from the top */
            if (cy < 0 || cy >= rh) continue;
            const unsigned char *row = px + (size_t)(rh - 1 - (int)cy) * rw * 4;
            for (x = 0; x < w; x++) {
                const unsigned char *q = row + (fbc[i].bw > 0 ? (unsigned)(fbc[i].ox * rs + (x + 0.5f) * fbc[i].bw * rs / w) : (unsigned)((x + 0.5f) * rw / w)) * 4;   /* P350 */
                unsigned v = (q[0] >> 3) << 11 | (q[1] >> 3) << 6 | (q[2] >> 3) << 1 | 1, k = 2 * (y * w + x);
                *VBE8(dst + k) = v >> 8; *VBE8(dst + k + 1) = v & 0xFF;
            }
        }
        state_dirty = 1;
        { static unsigned n; unsigned long sum = 0; unsigned j;
          for (j = 0; j < (unsigned)(rw * rh); j++) sum += px[4 * j] + px[4 * j + 1] + px[4 * j + 2];
          if (n++ < 8) port_log("[p161] frame copy %p (%ux%u) written back for a texture read at +0x%X (frame %u), mean rgb %.1f\n",
                                (void *)dst, w, H, (unsigned)(t - dst), port_frame_count, sum / 3.0 / (rw * rh)); }
    }
}

/* P335: hx_* (see hx[] above) */
extern int g_framebuffers[2] __attribute__((weak));   /* the game's two screen images (weak: sched_demo has no game) */
static int hx_is_screen(const unsigned char *p) {
    for (int i = 0; i < FBC_N; i++) if (fbc[i].p == p) return 1;
    if (g_framebuffers) for (int i = 0; i < 2; i++) if (g_framebuffers[i] && phys((unsigned)g_framebuffers[i]) == p) return 1;
    return 0;
}
static void hx_tex_alloc(GLuint tex, GLenum ifmt, GLenum fmt) {
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, ifmt, canvas_w, canvas_h, 0, fmt, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
static void hx_end(void) {
    if (hx_cur < 0) return;
    flush();
    hx_cur = -1;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    state_dirty = 1;
}
static void hx_begin(unsigned char *p, unsigned w) {
    int i, s = -1;
    flush();
    for (i = 0; i < HX_N; i++) if (hx[i].p == p) s = i;
    if (s < 0) { s = 0; for (i = 1; i < HX_N; i++) if (hx[i].task < hx[s].task) s = i; hx[s].p = p; }
    hx_snap_due = 1;   /* the screen is snapshot when the first texture rectangle reads it (hx_texrect) */
    if (!hx[s].tex) { glGenTextures(1, &hx[s].tex); glGenFramebuffers(1, &hx[s].fbo); }
    if (hx[s].tw != canvas_w || hx[s].th != canvas_h) {
        hx_tex_alloc(hx[s].tex, GL_RGBA8, GL_RGBA);
        glBindFramebuffer(GL_FRAMEBUFFER, hx[s].fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, hx[s].tex, 0);
        hx[s].tw = canvas_w; hx[s].th = canvas_h;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, hx[s].fbo);
    hx[s].w = w; hx[s].task = gfx_stats.tasks; hx_cur = s; state_dirty = 1;
    hx[s].rows = (unsigned)(vi_y0 + (vi_h > 0 ? vi_h : w * 0.75f) + 0.999f); if (hx[s].rows > 288) hx[s].rows = 288;
    { static unsigned n; if (n++ < 4 || hx_logging()) port_log("[p335] task %u frame %u: colour image %p (%u wide) kept at canvas resolution %dx%d (slot %d)\n",
                                                              gfx_stats.tasks, port_frame_count, (void *)p, w, canvas_w, canvas_h, s); }
}
/* P349 option "Hi-res menus and 2D": the pause screen (P161) copies the last frame's screen image 1:1 into the z image
 * (LOADTILE strips, the z image as a colour image) on its first frame and draws that z image back as the background of
 * every paused frame. The port keeps the copy at N64 size (offscreen FBO + RDRAM write-back, 15-bit colour), so the
 * frozen picture was N64-resolution blocky behind the hi-res menu. With the option on, the first copy rectangle that
 * reads a screen image with a canvas copy (fbc[]) takes a GPU snapshot of that copy; while the z image holds nothing
 * but 1:1 copies of it, texture rectangles that read the z image 1:1 sample the snapshot per canvas pixel (hx kind 3,
 * the P335 uHiRes path). It ends when the z image gets anything else (another rectangle, a triangle) or depth writes,
 * and is unused when the canvas size changed (photo mode capture). The N64-size copy is still made (option off later). */
static void zsnap_take(int i) {
    zsnap.due = 0; zsnap.valid = 0;
    hfr_fx = 1;   /* P351 */
    if (fbc[i].tw <= 0 || fbc[i].th <= 0) return;
    flush();
    if (!zsnap.tex) { glGenTextures(1, &zsnap.tex); glGenFramebuffers(1, &zsnap.fbo); }
    if (zsnap.tw != fbc[i].tw || zsnap.th != fbc[i].th) {
        glBindTexture(GL_TEXTURE_2D, zsnap.tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, fbc[i].tw, fbc[i].th, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBindFramebuffer(GL_FRAMEBUFFER, zsnap.fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, zsnap.tex, 0);
        zsnap.tw = fbc[i].tw; zsnap.th = fbc[i].th;
    }
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbc[i].fbo);
    glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbc[i].tex, 0);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, zsnap.fbo);
    glDisable(GL_SCISSOR_TEST);
    glBlitFramebuffer(0, 0, zsnap.tw, zsnap.th, 0, 0, zsnap.tw, zsnap.th, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, bound_fb());
    zsnap.valid = 1; zsnap.src = fbc[i].p; zsnap.p = gfx_addr(off_addr); zsnap.w = off_w; zsnap.rows = off_rows;
    state_dirty = 1;
    { static unsigned n; if (n++ < 4) port_log("[p349] pause frame snapshot %dx%d of screen image %p for z image %p (frame %u)\n",
                                               zsnap.tw, zsnap.th, (void *)zsnap.src, (void *)zsnap.p, port_frame_count); }
}
/* SETTIMG: is the texture image the screen image while an hx image is bound, or a recent hx image? */
static void hx_settimg(void) {
    unsigned char *base = 0; unsigned w = 0;
    hx_src.kind = 0;
    if (!timg.p || !gl_ok || gfx_measure_only || hx_disabled() || timg.siz != 2 || hfr_mode == 2) return;   /* P351: not in a replay */
    if ((hires_2d || ws_opt) && off_on && off_zimg) {   /* P349: drawing into the z image (pause): a copy of a screen image? */
        for (int i = 0; i < FBC_N; i++) {
            unsigned char *b = fbc[i].p;
            if (!b || !fbc[i].tex || timg.p < b || timg.p >= b + 2 * fbc[i].w * fbc[i].rows) continue;
            if (zsnap.due) zsnap_take(i);
            if (zsnap.valid && zsnap.src == b) { hx_src.kind = 4; hx_src.p = b; hx_src.w = fbc[i].w; hx_src.idx = (unsigned)(timg.p - b) / 2; }
            break;
        }
        return;
    }
    if (hx_cur >= 0 && fbc_task_p && timg.p >= fbc_task_p && timg.p < fbc_task_p + 2 * fbc_task_w * hx[hx_cur].rows) {
        hx_src.kind = 1; base = fbc_task_p; w = fbc_task_w;
    } else for (int i = 0; i < HX_N; i++)
        if (i != hx_cur && hx[i].p && hx[i].tex && gfx_stats.tasks - hx[i].task <= 4 && timg.p >= hx[i].p && timg.p < hx[i].p + 2 * hx[i].w * hx[i].rows) {
            hx_src.kind = 2; hx_src.slot = i; base = hx[i].p; w = hx[i].w; break; }
    if (!hx_src.kind && (hires_2d || ws_opt) && zsnap.valid && timg.p >= zsnap.p && timg.p < zsnap.p + 2 * zsnap.w * zsnap.rows) {   /* P349 */
        hx_src.kind = 3; base = zsnap.p; w = zsnap.w; }
    if (hx_src.kind) { hx_src.p = base; hx_src.w = w; hx_src.idx = (unsigned)(timg.p - base) / 2; }
}
/* LOADTILE / LOADBLOCK: remember which source pixel the first loaded texel is (texel index first = row * timg width + col) */
static void hx_loaded(const Tile *t, unsigned first) {
    hx_load.kind = hx_src.kind;
    if (!hx_src.kind) return;
    unsigned i = hx_src.idx + first;
    hx_load.slot = hx_src.slot; hx_load.p = hx_src.p; hx_load.x = (float)(i % hx_src.w); hx_load.y = (float)(i / hx_src.w);
    hx_load.tmem = t->tmem; hx_load.gen = tmem_gen;
}
/* TEXRECT: set hxs_* when the rectangle reads the last hx load 1:1 (s, t at the upper-left corner ulx, uly) */
static void hx_texrect(int ti, float ulx, float uly, float s, float t, float ds, float dt) {
    const Tile *T = &tiles[ti & 7];
    hxs_on = 0;
    if (off_on && off_zimg && (zsnap.valid || hx_load.kind == 4)) {   /* P349: only 1:1 copies of the snapshot keep it */
        float cx = hx_load.x + s - T->uls / 4.0f, cy = hx_load.y + t - T->ult / 4.0f;
        if (hx_load.kind != 4 || hx_load.gen != tmem_gen || T->tmem != hx_load.tmem || fabsf(ds - 1) > 0.01f || fabsf(dt - 1) > 0.01f ||
            fabsf(cx - ulx) > 0.01f || fabsf(cy - uly) > 0.01f) zsnap.valid = 0;
        return;
    }
    if (hx_load.kind == 3 && (!zsnap.valid || !(hires_2d || ws_opt) || zsnap.tw != canvas_w || zsnap.th != canvas_h)) return;
    if (!hx_load.kind || hx_load.gen != tmem_gen || T->tmem != hx_load.tmem || fabsf(ds - 1) > 0.01f || fabsf(dt - 1) > 0.01f) return;
    if (hx_load.kind == 2 && (hx[hx_load.slot].p != hx_load.p || hx_load.slot == hx_cur)) return;
    float sx = hx_load.x + s - T->uls / 4.0f, sy = hx_load.y + t - T->ult / 4.0f;   /* source N64 pixel at (ulx, uly) */
    if (hx_load.kind == 1 && hx_snap_due) {   /* the screen so far (nothing draws on it while an hx image is bound) */
        flush();
        if (!hx_snap) glGenTextures(1, &hx_snap);
        if (hx_snap_w != canvas_w || hx_snap_h != canvas_h) { hx_tex_alloc(hx_snap, GL_RGB8, GL_RGB); hx_snap_w = canvas_w; hx_snap_h = canvas_h; }
        else glBindTexture(GL_TEXTURE_2D, hx_snap);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
        glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, canvas_w, canvas_h);
        glBindFramebuffer(GL_FRAMEBUFFER, bound_fb());
        hx_snap_due = 0; state_dirty = 1;
    }
    hxs_on = 1; hxs_tex = hx_load.kind == 1 ? hx_snap : hx_load.kind == 3 ? zsnap.tex : hx[hx_load.slot].tex;
    hfr_fx = 1;   /* P351 */
    ws_calc();
    if (ws_on) hxs_ox = (sx - ulx) * ws_sx; else   /* P350 */
    hxs_ox = (sx - ulx) * canvas_w / cimg_width;
    hxs_oy = -(sy - uly) * canvas_h / CIMG_H;
    if (hx_load.kind <= 2) hx_nrect[hx_load.kind - 1]++;
}
static void hx_task_end(void) {
    hx_end();
    if ((hx_nrect[0] || hx_nrect[1]) && hx_logging())
        port_log("[p335] task %u frame %u: %u rects copied the screen into the hx image, %u rects drew an hx image\n",
                 gfx_stats.tasks, port_frame_count, hx_nrect[0], hx_nrect[1]);
    hx_nrect[0] = hx_nrect[1] = 0; hx_src.kind = 0; hx_load.kind = 0;
}

/* screen-space rectangle in N64 pixels (fill / texture rectangles). P350: with the widescreen mapping (ws_on) the x
 * coordinates go through ws_x2d; rect_ext bit 0 / 1 puts the left / right edge on the canvas edge instead (the caller
 * decides, see ws_calc), and is cleared here. */
static int rect_ext;
static void rect(float x0, float y0, float x1, float y1, float s0, float t0, float s1, float t1, unsigned col, int rm) {
    need_state(rm);
    float W = cimg_width, H = CIMG_H;
    V q[4];
    float xs[4] = {x0, x1, x0, x1}, ys[4] = {y0, y0, y1, y1}, ss[4] = {s0, s1, s0, s1}, ts[4] = {t0, t0, t1, t1};
    int ext = rect_ext;
    rect_ext = 0;
    if (ws_log_on) port_log("[p350] task %u rect rm %d %.1f,%.1f..%.1f,%.1f ext %d sc %d %.1f,%.1f..%.1f,%.1f vp %d %d %d %d oth %06X cc %06X/%08X timg %08X\n", gfx_stats.tasks, rm, x0, y0, x1, y1, ext,
                            sc_on, sc_box[0], sc_box[1], sc_box[2], sc_box[3], vp_scale[0], vp_scale[1], vp_trans[0], vp_trans[1], oth_h, combine_w0, combine_w1, timg.raw);
    for (int i = 0; i < 4; i++) {
        if (ws_on) { float X = (i & 1) ? ((ext & 2) ? ws_edge(xs[i]) : ws_x2d(xs[i])) : ((ext & 1) ? ws_edge(xs[i]) : ws_x2d(xs[i])); q[i].x = X / canvas_w * 2 - 1; }
        else
        q[i].x = xs[i] / W * 2 - 1;
        q[i].y = 1 - (ys[i] - VI_Y0) / H * 2; q[i].z = 0; q[i].w = 1;
        q[i].r = (col >> 24) / 255.0f; q[i].g = (col >> 16 & 255) / 255.0f; q[i].b = (col >> 8 & 255) / 255.0f;
        q[i].a = (col & 255) / 255.0f; q[i].s = ss[i]; q[i].t = ts[i]; q[i].fog = 0;
    }
    put(&q[0], 1, 1); put(&q[1], 1, 1); put(&q[2], 1, 1);
    put(&q[1], 1, 1); put(&q[3], 1, 1); put(&q[2], 1, 1);
}

/* P349: the tile-0 texel range (tc = s * shift - ul, the shader's units) one axis of a hi-res texture rectangle may read.
 * The N64 rectangle samples s0 at its first pixel and s0 + ds * (npix - 1) at its last; a canvas pixel in the outer half
 * of an edge pixel reads up to half a step further. That is allowed only where the tile itself goes on by at most one
 * texel (a 1-texel border that repeats the next tile, image_draw_tiled flags & 1, or the tile's clamp edge): the filter
 * then joins the tiles or holds the edge texel. Where the tile goes on further (a font / icon atlas) the range stops at
 * what the N64 reads, so no neighbour bleeds in; a wrapping (masked) tile never reads past its ends. */
static void rect_hires_axis(float s0, float ds, float npix, const Tile *t, int axis, float *lo_out, float *hi_out) {
    unsigned ul = axis ? t->ult : t->uls, lr = axis ? t->lrt : t->lrs, mask = axis ? t->maskt : t->masks, cm = axis ? t->cmt : t->cms;
    float sh = shiftscale(axis ? t->shiftt : t->shifts), u0 = ul / 4.0f;
    float a = s0 * sh - u0, b = (s0 + ds * (npix > 1 ? npix - 1 : 0)) * sh - u0;
    float lo = a < b ? a : b, hi = a < b ? b : a;
    int clamped = (cm & 2) || !mask, mirror = !clamped && (cm & 1);
    int mx = (int)(lr >> 2) - (int)(ul >> 2);
    float last = clamped ? (float)(mx < 0 ? 0 : mx) : (float)((1 << (mask > 10 ? 10 : mask)) - 1);
    int wrap = !clamped && !mirror;
    *lo_out = lo <= 1.0f ? (wrap ? 0.0f : -1e9f) : lo;
    *hi_out = hi >= last - 1.0f ? (wrap ? last : 1e9f) : hi;
}
static void rect_hires_setup(int ti, float s0, float t0, float ds, float dt, float w, float h, unsigned cyc) {
    const Tile *t = &tiles[ti & 7];
    rect_hires_mode = cyc >= 2 || (oth_h >> 12 & 3) == 0 ? 2 : 1;   /* copy mode / G_TF_POINT: point sampling */
    rect_hires_axis(s0, ds, w, t, 0, &rect_hires_clamp[0], &rect_hires_clamp[2]);
    rect_hires_axis(t0, dt, h, t, 1, &rect_hires_clamp[1], &rect_hires_clamp[3]);
}

/* ------------------------------------------------------------------ RSP commands */
/* Conker lighting (P14, rewritten in P35 from the ROM's F3DEX2 lighting overlay).
 * The RSP code is the overlay at text offset 0x1188 (0x388 bytes, IMEM 0x12D8) of the gfx ucodes in the
 * ROM table g_gfx_ucode_rom_table (text ROM 0x2D810 + 0x4560, data + 0x10460; P35.md section 2). DMEM layout from
 * the ucode's movemem/moveword tables (data +0x550):
 *   G_MOVEMEM 0x0A -> DMEM 0x260 + offset. Records are 48 bytes: 0x260 lookat X, 0x290 lookat Y,
 *     0x2C0 + 48 i light i (i < N), light N = ambient. G_MOVEMEM 0x0E -> DMEM 0x510 (normal x,y per slot).
 *   G_MOVEWORD 2 (NUMLIGHT) w1 = 48 M; 0x0A (LIGHTCOL) -> 0x2C0 + offset; 0x10 (Rare) -> 0x1D0 + offset.
 *   Record: +0 colour rgb, +8 direction s8 xyz, +0x0C attenuation (4.4), +0x18 the direction in model
 *   space (ucode-written), +0x20 position s16 xyz (eye space).
 * Per vertex (two at a time in the ucode):
 *   n = (nx, ny from 0x510 + 2 slot, nz = Vtx flag low byte), raw s8 / 128, NOT normalised;
 *   d_i = normalise(MV * dir_i) (row-vector MV, i.e. the light in model space);
 *   NUMLIGHT w1 = 48 M: lights 0..M-1 are point lights.
 *   P35b, checked in the F3DEXBG overlay (IMEM 0x13D8: luv $v29, 0x170($9), $9 = 0x150 + numLightsxSize):
 *   record M (0x2C0 + numLightsxSize) is the start colour with no direction (the "ambient"); there is no
 *   directional light and no normal in BG (the level DLs send no 0x0E normals). The level frames send M = 0
 *   and record 0 = white, so the level keeps its prelit vertex colours. For the other ucodes (F3DEX/BS,
 *   characters, with normals) P35's unchecked model stays: record M = directional sun, M + 1 = ambient,
 *   c = ambient + col[M] * max(0, n.d[M])
 *   for the point lights i = M-1 .. 0 (in pairs; an odd M also reads the lookat Y record):
 *     att = min(1, 32768 * K_i / |pos_i - e|^2), K_i = byte +0x0C as 4.4, e = eye-space vertex position
 *     c += col_i * att * (G_LIGHTING_POSITIONAL (0x400000) ? max(0, n.d_i) : 1)
 *   rgb = vertex rgb * min(1, c); alpha = vertex alpha. Vtx flag high byte < 0: lighting skipped.
 *   e = (clip + T) * S per component, clip = the vertex after the game's MVP, S = s16.16 at DMEM 0x1D0
 *   (int) / 0x1E0 (frac), T = s16 at 0x1F0: Rare's G_MOVEWORD 0x10 block is the inverse projection.
 *   G_TEXTURE_GEN: s = 512 (1 + n.lookatX) * scale_s, t = 512 (1 + n.lookatY) * scale_t (linear mode is
 *   approximated by the same formula). */
static void light_vtx(V *v, const unsigned char *n, const unsigned char *vtx, float ox, float oy, float oz) {
    if ((signed char)vbe_ld8(vtx + 6) < 0) { gfx_stats.unlit_flag++; return; } /* flag high byte < 0: unlit */
    if (light_dirty) light_prepare();
    float nx = (signed char)n[0] / 128.0f, ny = (signed char)n[1] / 128.0f, nz = (signed char)vbe_ld8(vtx + 7) / 128.0f;
    int M = (int)(light_nls / 48);                                   /* point lights; record M = sun, M + 1 = ambient */
    if (M > 6) M = 6;
    /* P35b: F3DEXBG (the level ucode, checked in its overlay at IMEM 0x13D8): the accumulator starts at the colour
     * of record M (0x2C0 + numLightsxSize) with no direction and no normal ("ambient"); only point lights follow.
     * The other ucodes keep P35's model (record M = directional sun, M + 1 = ambient), not checked. */
    /* P94: the character ucode (F3DEX.NoN, loaded by G_LOAD_UCODE) was disassembled too (port_work/p94/f3dex_light.dis,
     * IMEM 0x12D8..): 0x13F8 `luv $v29, 0x170($9)` = the colour of record M is the start ("ambient") as in BG;
     * 0x1418..0x1468: record M - 1 is DIRECTIONAL, c += col[M-1] * max(0, n.d[M-1]) (vmulu/vmacu clamp at 0);
     * 0x1474..0x1590: records M - 2 .. 0 are point lights in pairs (an even M also reads the lookat Y record), times
     * max(0, n.d) when geom has 0x400000; 0x1594..: rgb = vertex rgb * min(1, c). P35's model (record M = sun with
     * the n.d, M + 1 = ambient) read the game's ambient (gSPSetLights1 sends Ambient{7380B1 x4} as record 1) as a sun
     * whose direction is the colour bytes, ignored the white key light (record 0, K = 0 -> attenuation 0) and took the
     * start colour from record 2, which nobody writes. ?p94oldlight=1 restores P35's model for comparison. */
    static int oldl = -1;
    if (oldl < 0) oldl = port_flag("p94oldlight");
    const unsigned char *amb = lbuf + 0x60 + 48 * (M + (!light_bg && oldl)), *sun = lbuf + 0x60 + 48 * (oldl ? M : M - 1);
    float c[3] = {amb[0] / 255.0f, amb[1] / 255.0f, amb[2] / 255.0f};
    {   /* P42 DIAGNOSTIC ?lvlwhite=1: the level's start colour (record M) is light_apply_object_lights's `arg8` = the colour that the
         * still-asm light_get_zone_colour should write into its uninitialised local `col`; with the stub it is stack garbage
         * (P39: a green tint, P42: 000000 = a black level). The flag makes a black BG start colour white. */
        static int lw = -1;
        if (lw < 0) lw = port_flag("lvlwhite");
        /* P44: ?lvlwhite=2 forces white for any BG start colour (the stack garbage can be a dim green, not 000000) */
        if (lw && light_bg && (lw >= 2 || (!amb[0] && !amb[1] && !amb[2]))) c[0] = c[1] = c[2] = 1.0f;
        /* P46: ?lvlcol=N logs the first N changes of the BG start colour (P43: light_get_zone_colour is C and fills it) */
        static int lc = -1, lcn;
        static unsigned lcprev = 0xFFFFFFFFu;
        if (lc < 0) lc = port_flag("lvlcol");
        if (lc && light_bg && lcn < lc) {
            unsigned cur = (unsigned)amb[0] << 16 | (unsigned)amb[1] << 8 | amb[2];
            if (cur != lcprev) { lcprev = cur; lcn++; port_log("[lvlcol] BG start colour %06X (M %d), frame %u\n", cur, M, port_frame_count); }
        }
    }
    int np = M;                                                      /* point lights M - 1 .. 0 (BG) */
    if (!light_bg && (oldl || M >= 1)) {
        const float *d = lmdir[2 + (oldl ? M : M - 1)];
        float dot = nx * d[0] + ny * d[1] + nz * d[2];
        if (dot > 0) for (int k = 0; k < 3; k++) c[k] += sun[k] / 255.0f * dot;
        if (!oldl) np = M - 1;                                       /* F3DEX: point lights M - 2 .. 0 */
    }
    if (np >= 1) {
        float e[3];
        for (int k = 0; k < 3; k++) {
            float cl = k == 0 ? ox * mp_game[0][0] + oy * mp_game[1][0] + oz * mp_game[2][0] + mp_game[3][0]
                     : k == 1 ? ox * mp_game[0][1] + oy * mp_game[1][1] + oz * mp_game[2][1] + mp_game[3][1]
                              : ox * mp_game[0][2] + oy * mp_game[1][2] + oz * mp_game[2][2] + mp_game[3][2];
            e[k] = (cl + rare_t(k)) * rare_s(k);
        }
        for (int i = np - 1; i >= (np & 1 ? -1 : 0); i--) {
            const unsigned char *L = lbuf + 0x60 + 48 * i;          /* i = -1: the lookat Y record (odd M) */
            float px = (short)(L[0x20] << 8 | L[0x21]) - e[0], py = (short)(L[0x22] << 8 | L[0x23]) - e[1], pz = (short)(L[0x24] << 8 | L[0x25]) - e[2];
            float d2 = px * px + py * py + pz * pz, K = L[0x0C] / 16.0f;
            float att = d2 > 0 ? 32768.0f * K / d2 : 1;
            if (att > 1) att = 1;
            float f = att;
            if (!light_bg && (geom & 0x00400000)) {                                   /* G_LIGHTING_POSITIONAL: times n.d */
                const float *d = lmdir[2 + i];
                float dot = nx * d[0] + ny * d[1] + nz * d[2];
                f *= dot > 0 ? dot : 0;
            }
            for (int k = 0; k < 3; k++) c[k] += L[k] / 255.0f * f;
        }
    }
    if (p78_on) {   /* P94: ?p78tex also logs every light state change (records 0..M+1, lookats) and its first 2 lit vertices */
        static unsigned p94_h, p94_n;
        unsigned h = 2166136261u ^ light_nls ^ (unsigned)light_bg << 20 ^ geom;
        for (int k = 0; k < 48 * (M + 4) && k < (int)sizeof lbuf; k++) h = (h ^ lbuf[k]) * 16777619u;
        for (int k = 0; k < 9; k++) h = (h ^ (unsigned)(lmdir[k][0] * 1000)) * 16777619u;
        if (h != p94_h) {
            p94_h = h; p94_n = 0;
            port_log("[p94light] %s nls %u M %d geom %06X cc %06X/%08X prim %08X env %08X fog %08X\n", light_bg ? "BG" : "other",
                     light_nls, M, geom, combine_w0, combine_w1, prim_col, env_col, fog_col);
            for (int r = -2; r <= M + 1; r++) {
                const unsigned char *L = lbuf + 0x60 + 48 * r;
                port_log("[p94light]   rec %2d (DMEM %03X): col %02X%02X%02X/%02X%02X%02X dir %4d %4d %4d att %02X mdir %.2f %.2f %.2f%s\n",
                         r, 0x2C0 + 48 * r, L[0], L[1], L[2], L[4], L[5], L[6], (signed char)L[8], (signed char)L[9], (signed char)L[10], L[12],
                         lmdir[r + 2][0], lmdir[r + 2][1], lmdir[r + 2][2], r < 0 ? " (lookat)" : oldl ? (r == M ? " <- P35 sun" : r == M + 1 ? " <- P35 ambient" : " (point)")
                         : r == M ? " <- start (ambient)" : r == M + 1 ? " (unused)" : r == M - 1 && !light_bg ? " <- directional" : " (point)");
            }
        }
        if (p94_n++ < 2) port_log("[p94light]   vtx n %.2f %.2f %.2f c %.3f %.3f %.3f rgb %02X%02X%02X -> %.3f %.3f %.3f\n", nx, ny, nz, c[0], c[1], c[2],
                                  vbe_ld8(vtx + 12), vbe_ld8(vtx + 13), vbe_ld8(vtx + 14), v->r * (c[0] > 1 ? 1 : c[0]), v->g * (c[1] > 1 ? 1 : c[1]), v->b * (c[2] > 1 ? 1 : c[2]));
    }
    if (gfx_trace && light_dbg++ < 6) port_log("[light] vtx n %.2f %.2f %.2f sun %.2f %.2f %.2f M %d c %.2f %.2f %.2f rgb %.2f %.2f %.2f\n",
        nx, ny, nz, lmdir[2 + M][0], lmdir[2 + M][1], lmdir[2 + M][2], M, c[0], c[1], c[2], v->r, v->g, v->b);
    v->r *= c[0] > 1 ? 1 : c[0]; v->g *= c[1] > 1 ? 1 : c[1]; v->b *= c[2] > 1 ? 1 : c[2];
    if (geom & G_TEXTURE_GEN) {
        float dx = nx * lmdir[0][0] + ny * lmdir[0][1] + nz * lmdir[0][2];
        float dy = nx * lmdir[1][0] + ny * lmdir[1][1] + nz * lmdir[1][2];
        v->s = 512.0f * (1 + dx) * tex_sc_s; v->t = 512.0f * (1 + dy) * tex_sc_t;
    }
    gfx_stats.lit++;
}

static void load_vtx(unsigned w0, unsigned w1) {
    unsigned n = w0 >> 12 & 0xFF, end = w0 >> 1 & 0x7F, v0 = end - n;
    const unsigned char *p = gfx_addr(w1);
    if (!p || v0 + n > 64) { gfx_stats.bad_addr++; return; }
    if (p78_on && (tex_on || p158_on)) {   /* P78: raw Vtx records (x y z flag s t rgba) of the dumped task (P193: p158 dumps also untextured) */
        port_log("[p78vtx] G_VTX %08X %08X: %u at slot %u, ucode %08X geom %06X\n", w0, w1, n, v0, cur_ucode, geom);
        for (unsigned i = 0; i < n; i++)
            port_log("[p78vtx]   %2u: %6d %6d %6d  flag %04X  st %6d %6d (%.2f %.2f)  rgba %08X\n", v0 + i, (short)vbe_ld16(p + 16 * i),
                     (short)vbe_ld16(p + 16 * i + 2), (short)vbe_ld16(p + 16 * i + 4), vbe_ld16(p + 16 * i + 6),
                     (short)vbe_ld16(p + 16 * i + 8), (short)vbe_ld16(p + 16 * i + 10), (short)vbe_ld16(p + 16 * i + 8) / 32.0,
                     (short)vbe_ld16(p + 16 * i + 10) / 32.0, (unsigned)vbe_ld16(p + 16 * i + 12) << 16 | vbe_ld16(p + 16 * i + 14));
    }
    for (unsigned i = 0; i < n; i++, p += 16) {
        V *v = &vb[v0 + i];
        float x = (short)vbe_ld16(p), y = (short)vbe_ld16(p + 2), z = (short)vbe_ld16(p + 4);
        v->ox = x; v->oy = y; v->oz = z;
        {   /* bounds after the modelview (the viewer measures with an identity model matrix, so
             * skinned parts are placed by their bone matrices) */
            float bx = x * mv[0][0] + y * mv[1][0] + z * mv[2][0] + mv[3][0];
            float by = x * mv[0][1] + y * mv[1][1] + z * mv[2][1] + mv[3][1];
            float bz = x * mv[0][2] + y * mv[1][2] + z * mv[2][2] + mv[3][2];
            if (!bany) { bmin[0] = bmax[0] = bx; bmin[1] = bmax[1] = by; bmin[2] = bmax[2] = bz; bany = 1; }
            if (bx < bmin[0]) bmin[0] = bx; if (bx > bmax[0]) bmax[0] = bx;
            if (by < bmin[1]) bmin[1] = by; if (by > bmax[1]) bmax[1] = by;
            if (bz < bmin[2]) bmin[2] = bz; if (bz > bmax[2]) bmax[2] = bz;
        }
        v->x = x * mp[0][0] + y * mp[1][0] + z * mp[2][0] + mp[3][0];
        v->y = x * mp[0][1] + y * mp[1][1] + z * mp[2][1] + mp[3][1];
        v->z = x * mp[0][2] + y * mp[1][2] + z * mp[2][2] + mp[3][2];
        v->w = x * mp[0][3] + y * mp[1][3] + z * mp[2][3] + mp[3][3];
        v->s = (short)vbe_ld16(p + 8) / 32.0f * tex_sc_s;
        v->t = (short)vbe_ld16(p + 10) / 32.0f * tex_sc_t;
        /* Conker (F3DEX2 + Rare): the vertex rgba stays a colour even with G_LIGHTING; normals come
         * from a separate array (MOVEMEM index 0x0E, normal_base), see light_vtx(). */
        v->r = vbe_ld8(p + 12) / 255.0f; v->g = vbe_ld8(p + 13) / 255.0f; v->b = vbe_ld8(p + 14) / 255.0f;
        v->a = vbe_ld8(p + 15) / 255.0f;
        if (geom & G_LIGHTING) light_vtx(v, nbuf + ((2 * (v0 + i)) & 0x3F), p, x, y, z);
        if (!(geom & G_SHADE)) v->r = v->g = v->b = 1;
        v->fog = 0;
        if (geom & G_FOG) {   /* the RSP writes the fog factor into the shade alpha; the blender reads it (P35) */
            float f = v->w != 0 ? v->z / v->w * fog_mul + fog_off : 0;
            v->fog = (f < 0 ? 0 : f > 255 ? 255 : f) / 255.0f;
            v->a = v->fog;
        }
    }
    gfx_stats.verts += n;
    if (p61_depth >= 0) {   /* P61: NDC extent of the model's vertices (w > 0) */
        p61_verts += n;
        for (unsigned k = v0; k < v0 + n; k++) {
            const V *q = &vb[k];
            if (!(q->w > 0) || q->x != q->x || q->y != q->y) { p61_vbad++; continue; }
            float x = q->x / q->w, y = q->y / q->w;
            if (x < p61_mn[0]) p61_mn[0] = x; if (x > p61_mx[0]) p61_mx[0] = x;
            if (y < p61_mn[1]) p61_mn[1] = y; if (y > p61_mx[1]) p61_mx[1] = y;
        }
    }
}

static void load_block(unsigned w0, unsigned w1) {
    Tile *t = &tiles[w1 >> 24 & 7];
    unsigned uls = w0 >> 12 & 0xFFF, ult = w0 & 0xFFF, lrs = w1 >> 12 & 0xFFF, dxt = w1 & 0xFFF;
    unsigned bytes = ((lrs - uls + 1) << timg.siz) >> 1, dst = t->tmem * 8;
    if (p158_on) port_log("[p158] LOADBLOCK tile %u tmem %03X uls %u ult %u lrs %u dxt %u | timg %08X fmt %u siz %u width %u\n",
                          w1 >> 24 & 7, t->tmem, uls, ult, lrs, dxt, timg.raw, timg.fmt, timg.siz, timg.width);
    if (timg.siz == 0) bytes = (lrs - uls + 2) >> 1;
    if (dst + bytes > 4096) bytes = 4096 - dst;
    const unsigned char *src = timg.p ? timg.p + ((((ult * timg.width + uls) << timg.siz) >> 1)) : 0;
    for (unsigned i = 0; i < bytes; i++)
        tmem[dst + i] = src ? vbe_ld8(src + i) : (unsigned char)(((i >> 3) ^ (i >> 8)) & 1 ? 0x30 + (timg.raw & 0x7F) : 0xC0 - (timg.raw & 0x3F));
    for (unsigned k = 0; k * 8 < bytes; k++)
        if (((k * dxt) >> 11) & 1) {
            if (timg.siz != 3) { /* odd line: swap the 32-bit halves */
                unsigned char *q = tmem + dst + k * 8, tmp[4];
                memcpy(tmp, q, 4); memcpy(q, q + 4, 4); memcpy(q + 4, tmp, 4);
            } else if (!(k & 1) && dst + k * 8 + 16 <= 4096) { /* P158: 32-bit: swap texel pairs (source words k, k + 1) */
                unsigned char *q = tmem + dst + k * 8, tmp[8];
                memcpy(tmp, q, 8); memcpy(q, q + 8, 8); memcpy(q + 8, tmp, 8);
            }
        }
    tmem_gen++;
    hx_loaded(t, ult * timg.width + uls);   /* P335 */
    state_dirty = 1;
}

static void load_tile(unsigned w0, unsigned w1) {
    Tile *t = &tiles[w1 >> 24 & 7];
    unsigned x0 = (w0 >> 12 & 0xFFF) >> 2, y0 = (w0 & 0xFFF) >> 2, x1 = (w1 >> 12 & 0xFFF) >> 2, y1 = (w1 & 0xFFF) >> 2;
    unsigned stride = t->line * 8 * (timg.siz == 3 ? 2 : 1);
    unsigned rowb = timg.siz == 0 ? (x1 - x0 + 2) >> 1 : (x1 - x0 + 1) << (timg.siz - 1);
    if (p158_on) port_log("[p158] LOADTILE tile %u tmem %03X line %u x %u..%u y %u..%u | timg %08X fmt %u siz %u width %u\n",
                          w1 >> 24 & 7, t->tmem, t->line, x0, x1, y0, y1, timg.raw, timg.fmt, timg.siz, timg.width);
    for (unsigned y = y0; y <= y1 && (y - y0) * stride < 4096; y++) {
        const unsigned char *src = timg.p ? timg.p + (((y * timg.width + x0) << timg.siz) >> 1) : 0;
        for (unsigned i = 0; i < rowb && i < 4096; i++) {
            unsigned a = t->tmem * 8 + (y - y0) * stride + i;
            if ((y - y0) & 1) a ^= timg.siz == 3 ? 8 : 4;   /* P158: 32-bit rows swap texel pairs (see texel()) */
            tmem[a & 0xFFF] = src ? vbe_ld8(src + i) : (unsigned char)((((i >> 1) ^ (y >> 2)) & 1) ? 0xF0 : 0x40);
        }
    }
    t->uls = w0 >> 12 & 0xFFF; t->ult = w0 & 0xFFF; t->lrs = w1 >> 12 & 0xFFF; t->lrt = w1 & 0xFFF;
    tmem_gen++;
    hx_loaded(t, y0 * timg.width + x0);   /* P335 */
    state_dirty = 1;
}

static void load_tlut(unsigned w0, unsigned w1) {
    Tile *t = &tiles[w1 >> 24 & 7];
    unsigned n = ((w1 >> 14 & 0x3FF) - (w0 >> 14 & 0x3FF)) + 1, dst = t->tmem * 8;
    if (p158_on) port_log("[p189] LOADTLUT tile %u tmem %03X entries %u | timg %08X resolved %d\n", w1 >> 24 & 7, t->tmem, n,
                          (unsigned)(uintptr_t)timg.p, timg.p != 0);   /* P189 DIAGNOSTIC (p158 dumps) */
    for (unsigned i = 0; i < n * 2 && dst + i < 4096; i++) {
        unsigned v;
        if (timg.p) v = vbe_ld8(timg.p + i);
        else { /* unresolved texture (Conker texture id): a hue ramp, so models stay readable */
            unsigned e = i >> 1, h = (e * 37 + timg.raw * 11) & 0xFF;
            unsigned r = h < 85 ? 31 - h * 31 / 85 : h < 170 ? 0 : (h - 170) * 31 / 85;
            unsigned g = h < 85 ? h * 31 / 85 : h < 170 ? 31 - (h - 85) * 31 / 85 : 0;
            unsigned b = h < 85 ? 0 : h < 170 ? (h - 85) * 31 / 85 : 31 - (h - 170) * 31 / 85;
            unsigned c = (r / 2 + 15) << 11 | (g / 2 + 15) << 6 | (b / 2 + 15) << 1 | 1;
            v = (i & 1) ? c & 0xFF : c >> 8;
        }
        tmem[dst + i] = v;
    }
    tmem_gen++;
    state_dirty = 1;
}

static unsigned unk_seen[256 / 32];
/* P55: the last G_DL / G_BRANCH_DL jumps (from, w0, w1), logged once at the first unknown opcode of a task */
static unsigned dl_ring[8][3], dl_ring_n, dl_ring_logged_task = ~0u;

static void unknown(unsigned op, unsigned w0, unsigned w1) {
    gfx_stats.unknown_ops++;
    if (!(unk_seen[op >> 5] & (1u << (op & 31)))) {
        unk_seen[op >> 5] |= 1u << (op & 31);
        port_log("[gfx] unknown command %02X: %08X %08X\n", op, w0, w1);
    }
    if (dl_ring_logged_task != gfx_stats.tasks) {
        unsigned i;
        dl_ring_logged_task = gfx_stats.tasks;
        for (i = 0; i < 8 && i < dl_ring_n; i++) {
            unsigned *e = dl_ring[(dl_ring_n - 1 - i) & 7];
            port_log("[gfx] task %u first unknown op %02X: G_DL[-%u] at %08X: %08X %08X\n", gfx_stats.tasks, op, i, e[0], e[1], e[2]);
        }
    }
}

/* P33 DIAGNOSTIC: ?freecam=1 replaces the world camera's view matrix (the G_MTX "P mul" that follows the
 * projection load; the game multiplies its view into the projection) by a fly camera driven by pad 0,
 * i.e. P27's input layer: stick (WASD) = move/strafe, C-buttons (IJKL) = look, R (E) / Z (Q) = up/down,
 * Ctrl = half speed. Start pose: ?fcx=&fcy=&fcz= (world units), ?fcyaw=&fcpitch= (degrees; yaw 0 looks
 * down -Z); without fcx/fcy/fcz the camera starts outside the bounds of the vertices of the previous frame.
 * The game is not told: it still gets the pad, and its own view is only replaced in the renderer. */
static int fc_on = -1, fc_init, fc_moved;
static float fc_ibmin[3], fc_ibmax[3];
static float fc_pos[3], fc_yaw, fc_pitch, fc_speed = 20;
static float fbmin[3], fbmax[3];
static int fbany;
int32_t *port_pad_state(void);
static void freecam_update(void) {
    if (fc_on < 0) fc_on = port_flag("freecam");
    if (!fc_on) return;
    /* until the first input, follow the scene (the level changes at the switch from 0x25 to 0x21) */
    if (fc_init && !fc_moved && fbany && (memcmp(fc_ibmin, fbmin, sizeof fbmin) || memcmp(fc_ibmax, fbmax, sizeof fbmax))) fc_init = 0;
    if (!fc_init && fbany) {
        memcpy(fc_ibmin, fbmin, sizeof fbmin); memcpy(fc_ibmax, fbmax, sizeof fbmax);
        float size = 0;
        for (int k = 0; k < 3; k++) { float d = fbmax[k] - fbmin[k]; if (d > size) size = d; }
        int px = port_flag("fcx"), py = port_flag("fcy"), pz = port_flag("fcz");
        if (px || py || pz) { fc_pos[0] = (float)px; fc_pos[1] = (float)py; fc_pos[2] = (float)pz; }
        else {
            fc_pos[0] = (fbmin[0] + fbmax[0]) / 2;
            fc_pos[1] = (fbmin[1] + fbmax[1]) / 2 + size * 0.35f;
            fc_pos[2] = fbmax[2] + size * 0.6f;
        }
        fc_yaw = port_flag("fcyaw") * 3.14159265f / 180;
        fc_pitch = port_flag("fcpitch") * 3.14159265f / 180;
        if (!px && !py && !pz && !port_flag("fcpitch")) fc_pitch = -0.35f;
        fc_speed = size > 0 ? size / 300 : 20;
        fc_init = 1;
        port_log("[freecam] bounds %.0f %.0f %.0f .. %.0f %.0f %.0f; start %.0f %.0f %.0f yaw %.1f pitch %.1f speed %.1f\n",
                 fbmin[0], fbmin[1], fbmin[2], fbmax[0], fbmax[1], fbmax[2], fc_pos[0], fc_pos[1], fc_pos[2],
                 fc_yaw * 57.29578f, fc_pitch * 57.29578f, fc_speed);
    }
    if (!fc_init) return;
    const int32_t *pad = port_pad_state();
    unsigned b = (unsigned)pad[1];
    float sx = pad[2] / 80.0f, sy = pad[3] / 80.0f;
    if (b || pad[2] || pad[3]) fc_moved = 1;
    if (b & 0x0002) fc_yaw -= 0.03f;   /* C left */
    if (b & 0x0001) fc_yaw += 0.03f;   /* C right */
    if (b & 0x0008) fc_pitch += 0.03f; /* C up */
    if (b & 0x0004) fc_pitch -= 0.03f; /* C down */
    if (fc_pitch > 1.5f) fc_pitch = 1.5f; if (fc_pitch < -1.5f) fc_pitch = -1.5f;
    float fx = sinf(fc_yaw) * cosf(fc_pitch), fy = sinf(fc_pitch), fz = -cosf(fc_yaw) * cosf(fc_pitch);
    float rx = cosf(fc_yaw), rz = sinf(fc_yaw);
    fc_pos[0] += (fx * sy + rx * sx) * fc_speed; fc_pos[1] += fy * sy * fc_speed; fc_pos[2] += (fz * sy + rz * sx) * fc_speed;
    if (b & 0x0010) fc_pos[1] += fc_speed; /* R */
    if (b & 0x2000) fc_pos[1] -= fc_speed; /* Z */
    if (gfx_stats.tasks % 120 == 0)
        port_log("[freecam] pos %.0f %.0f %.0f yaw %.1f pitch %.1f\n", fc_pos[0], fc_pos[1], fc_pos[2], fc_yaw * 57.29578f, fc_pitch * 57.29578f);
}
/* the view in the N64 row-vector convention (as guLookAtF): v' = v * m */
static void freecam_view(float m[4][4]) {
    float lx = -sinf(fc_yaw) * cosf(fc_pitch), ly = -sinf(fc_pitch), lz = cosf(fc_yaw) * cosf(fc_pitch); /* look = -forward */
    float ux = 0, uy = 1, uz = 0;
    float rx = uy * lz - uz * ly, ry = uz * lx - ux * lz, rz = ux * ly - uy * lx, l = sqrtf(rx * rx + ry * ry + rz * rz);
    rx /= l; ry /= l; rz /= l;
    ux = ly * rz - lz * ry; uy = lz * rx - lx * rz; uz = lx * ry - ly * rx;
    const float *e = fc_pos;
    m[0][0] = rx; m[1][0] = ry; m[2][0] = rz; m[3][0] = -(e[0] * rx + e[1] * ry + e[2] * rz);
    m[0][1] = ux; m[1][1] = uy; m[2][1] = uz; m[3][1] = -(e[0] * ux + e[1] * uy + e[2] * uz);
    m[0][2] = lx; m[1][2] = ly; m[2][2] = lz; m[3][2] = -(e[0] * lx + e[1] * ly + e[2] * lz);
    m[0][3] = m[1][3] = m[2][3] = 0; m[3][3] = 1;
}

/* the game's two frame display-list buffers (g_gfx_dl_buffers[i], g_dl_capacity commands each). The game side
 * (port/boot/pc_overrides.c) defines port_gfx_dl_buffer; this weak default serves sched_demo, which links the renderer
 * without the game (P351: was weak data references in gfx_run_task_body). */
__attribute__((weak)) unsigned port_gfx_dl_buffer(int i, unsigned *len) { (void)i; *len = 0; return 0; }
static const unsigned char *gfx_dl_buffer(int i, unsigned *len) {
    unsigned a = port_gfx_dl_buffer(i, len);
    return a ? gfx_addr(a) : 0;
}
/* ------------------------------------------------------------------ P351 High frame rate (interpolated) */
/* The option "High frame rate" (page key hfr, port_gfx_hfr). The game builds a frame every 2..4 retraces of its 50 Hz VI
 * (12.5..25 frames per second); the canvas showed each one until the next. With the option, the renderer shows a new
 * picture on every browser animation frame (60 / 120 / 144 Hz) and moves the camera and every object smoothly between
 * the last two game frames. No game code runs for those pictures:
 *  - Recording (hfr_mode 1). The game frame's gfx task is drawn as always. Each G_MTX gets a key that names "the same
 *    matrix" in consecutive frames although the game keeps two copies of everything (one per display-list buffer, so
 *    the addresses alternate): hfr_sig = the command's address when it lies in a model's own display list (bone
 *    matrices: static model DL + segment-relative matrix), else 0 (the frame DL buffer alternates), the G_MTX flags, the
 *    matrix address when segment-relative, and an anchor: the first G_DL / G_VTX target after it that is not in the
 *    frame buffers (the model DL the matrix is for). key = sig + its occurrence count in the task (2 crates with the
 *    same model: the first is the first). The matrix, its key, and its match in the previous frame are recorded
 *    (hfr_m[set]), as is every G_CULLDL / G_BRANCH_Z decision (hfr_cull), the task record, and the P350 wide-copy /
 *    HUD-anchor entries the task used.
 *  - Matching and snapping (hfr_frame_end). Matched pairs are checked: rigid matrices (rotation x scale + translation)
 *    that turn by more than 100 deg or move more than HFR_JUMP units in one game frame are drawn as recorded (a
 *    teleport, a respawn, an object reused for another one); a view matrix (projection stack) that turns by more than
 *    45 deg or whose eye moves more than HFR_JUMP is a camera cut: the whole frame is shown as drawn (snap), as is a
 *    frame whose task read the screen or a kept picture back (motion blur ghost, pause frozen frame, lens effects:
 *    hfr_fx), the first frame after a reset (level load, photo mode, option switch), two tasks in one retrace, a gap of
 *    more than 8 retraces, a frame where fewer than half of the matrices match (a new scene), and a frame where no
 *    matched matrix changed (menus, pause: nothing to interpolate, and the drawn frame is exact).
 *  - Replay (hfr_mode 2, port_gfx_hfr_present from pc_sched.c frame() at the end of every main-loop tick). The display
 *    time is pos = retraces run + the part of the next one already elapsed; t = (pos - retrace of the newest frame) /
 *    the smoothed game-frame interval (hfr_ival), 0..1. The newest frame's task is drawn again from its display list,
 *    which is still intact in game memory (the game builds the next frame into the other buffer), with every matched
 *    matrix replaced by the interpolation between the previous and the newest frame (rotation slerp, scale and
 *    translation lerp; for a view the eye position is interpolated; projections / non-rigid matrices element-wise),
 *    the recorded cull decisions (so the command stream is the recorded one: keys stay in step, checked per G_MTX), the
 *    texture generations of the recording (its GL textures are found in the cache: no decode / upload), and only the
 *    screen drawn (offscreen shadow passes and kept images are dropped; their recorded results are in game memory /
 *    the canvas copies). A replay writes no game memory and takes no GPU read-back.
 *  So the picture runs up to one game frame behind the game (t = 0 shows the previous frame when the newest arrives):
 *  about 40..80 ms more latency. 2D (texture rectangles: HUD, text, menus) and geometry the game moves itself on the CPU
 *  (particles, shadows, trails) show the newest frame. Render-only and outside the online hash (gfx_f3dex2.o); the
 *  replay runs between retraces on the main loop's stack, never on a game fiber. ?hfrlog=1 statistics every 2 s,
 *  ?hfrtrace=F the first 150 presents from retrace F; port_gfx_hfr_test(t) redraws the newest frame at t (test aid). */
#define HFR_NM 4096           /* matrices per game frame */
#define HFR_HT 8192           /* hash slots (key -> older set index, occurrence counts) */
#define HFR_NC 32768          /* cull / branch decisions per game frame */
#define HFR_JUMP 1500.0f      /* units per game frame: a teleport / camera cut beyond this */
typedef struct {
    uint32_t sig, key;
    float m[4][4];
    int16_t old;              /* index of the matched matrix in the previous frame's set, -1 none */
    uint8_t kind;             /* bit 0 projection stack (a view / projection), bit 1 rigid (q, s, tr valid) */
    uint8_t ok;               /* interpolate with old (set by hfr_frame_end) */
    float q[4], s[3], tr[3];  /* rigid: rotation quaternion, row scales, translation (projection stack: the eye) */
} HfrMtx;
static HfrMtx hfr_m[2][HFR_NM];
static int hfr_mn[2], hfr_cur;                         /* hfr_cur: the newest frame's set */
static int16_t hfr_ht[HFR_HT];                         /* key -> index in the older set (+1; 0 empty) */
static uint32_t hfr_ht_key[HFR_HT];
static struct { uint32_t sig, gen; int n; } hfr_occ[HFR_HT];
static uint32_t hfr_occ_gen;
static uint8_t hfr_cull[HFR_NC];
static int hfr_nc, hfr_ci, hfr_mk;                     /* decisions recorded / replay cursors */
static unsigned char hfr_task[64];                     /* the newest frame's OSTask (copied) */
static uint32_t hfr_dl_hash;                           /* its top-level display list (data_ptr, data_size bytes) */
static const unsigned char *hfr_rec_b[2];              /* the frame DL buffers when it was recorded */
static int hfr_frames;                                 /* frames recorded since the last reset (0, 1, 2+) */
static unsigned hfr_rnew, hfr_rold;                    /* retrace of the newest / previous game frame */
static float hfr_ival = 2.5f;                          /* smoothed game-frame interval (retraces) */
static int hfr_snap;                                   /* the newest frame is shown as drawn: HFR_SNAP_* reason */
enum { HFR_SNAP_NONE, HFR_SNAP_FIRST, HFR_SNAP_CUT, HFR_SNAP_FX, HFR_SNAP_MULTI, HFR_SNAP_GAP, HFR_SNAP_SCENE, HFR_SNAP_STATIC, HFR_SNAP_N };
static const char *const hfr_snap_name[HFR_SNAP_N] = {"none", "first", "cut", "fx", "multi", "gap", "scene", "static"};
static float hfr_vi[2];                                /* vi_y0 / vi_h of the recording */
static float hfr_t;                                    /* the replay's interpolation factor */
static int hfr_bad, hfr_moving, hfr_matched;           /* replay key mismatches; moving / matched matrices of the newest frame */
static float hfr_shown_t = -1; static unsigned hfr_shown_r;   /* what the canvas shows: frame retrace and t (1 = as drawn) */
static const unsigned char *hfr_b[2]; static unsigned hfr_blen;   /* the frame DL buffers during a task */
static unsigned hfr_vsync, hfr_vsync_seen;             /* online: one present per browser animation frame */
/* the P350 widescreen entries the recorded task used (the live lists are dropped after a task) */
static struct { const unsigned char *gs, *ge; uint32_t h; const unsigned char *pdl; } hfr_ws_sub[WS_SUB_N];
static struct { const unsigned char *at; int tag; } hfr_ws_mark[WS_MARK_N];
static int hfr_ws_sub_n, hfr_ws_mark_n;
/* statistics (?hfrlog) */
static struct { unsigned shown, drawn, kept, frames, snaps[HFR_SNAP_N], bad; double t_replay, t_replay_max, t_task, t0; unsigned uploads; } hfr_st;
static int hfr_log = -1, hfr_trace = -1, hfr_trace_n;

EMSCRIPTEN_KEEPALIVE void port_gfx_hfr(int on) {
    hfr_opt = on != 0; hfr_frames = 0; hfr_shown_t = -1;
    for (int i = 0; i < FBC_N; i++) fbc_pre[i].p = 0;
    port_log("[hfr] high frame rate %s\n", hfr_opt ? "on" : "off");
}
EMSCRIPTEN_KEEPALIVE void port_gfx_hfr_vsync(void) { hfr_vsync++; }
EMSCRIPTEN_KEEPALIVE unsigned port_gfx_hfr_frame(void) { return hfr_frames ? hfr_rnew : 0; }

static inline uint32_t hfr_mix(uint32_t h, uint32_t v) { h ^= v; h *= 16777619u; h ^= h >> 13; return h; }
static int hfr_in_dlbuf(const unsigned char *p) {
    for (int i = 0; i < 2; i++) if (hfr_b[i] && p >= hfr_b[i] && p < hfr_b[i] + hfr_blen) return 1;
    return 0;
}
/* the key's signature of the G_MTX at `at` (see above) */
static uint32_t hfr_sig(const unsigned char *at, unsigned w0, unsigned w1) {
    uint32_t h = 2166136261u;
    h = hfr_mix(h, hfr_in_dlbuf(at) ? 0 : (uint32_t)(uintptr_t)at);
    h = hfr_mix(h, w0 & 0xFF);
    h = hfr_mix(h, w1 < PORT_WASM_BASE ? w1 : 0);
    for (int k = 1; k <= 32; k++) {
        const unsigned char *q = at + 8 * k;
        unsigned op = rd32(q) >> 24, a = rd32(q + 4);
        if (op == 0xDF) break;
        if (op != 0xDE && op != 0x01) continue;
        if (a < PORT_WASM_BASE && a >> 24) { h = hfr_mix(h, a); break; }   /* segment-relative */
        const unsigned char *p = gfx_addr(a);
        if (p && !hfr_in_dlbuf(p)) { h = hfr_mix(h, a); break; }
    }
    return h;
}
static int hfr_occ_next(uint32_t sig) {
    unsigned i = (sig * 2654435761u) >> 19;   /* 13 bits */
    for (unsigned n = 0; n < HFR_HT; n++, i = (i + 1) & (HFR_HT - 1)) {
        if (hfr_occ[i].gen != hfr_occ_gen) { hfr_occ[i].gen = hfr_occ_gen; hfr_occ[i].sig = sig; hfr_occ[i].n = 1; return 0; }
        if (hfr_occ[i].sig == sig) return hfr_occ[i].n++;
    }
    return 0;
}
/* rigid decomposition: rows = s_i * R_i (R orthonormal, det > 0) */
static int hfr_rigid(HfrMtx *r) {
    float (*m)[4] = r->m, R[3][3];
    if (fabsf(m[0][3]) > 1e-5f || fabsf(m[1][3]) > 1e-5f || fabsf(m[2][3]) > 1e-5f || fabsf(m[3][3] - 1) > 1e-5f) return 0;
    for (int i = 0; i < 3; i++) {
        float l = sqrtf(m[i][0] * m[i][0] + m[i][1] * m[i][1] + m[i][2] * m[i][2]);
        if (!(l > 1e-6f)) return 0;
        r->s[i] = l; R[i][0] = m[i][0] / l; R[i][1] = m[i][1] / l; R[i][2] = m[i][2] / l;
    }
    for (int i = 0; i < 3; i++) for (int j = i + 1; j < 3; j++)
        if (fabsf(R[i][0] * R[j][0] + R[i][1] * R[j][1] + R[i][2] * R[j][2]) > 0.02f) return 0;   /* sheared */
    float det = R[0][0] * (R[1][1] * R[2][2] - R[1][2] * R[2][1]) - R[0][1] * (R[1][0] * R[2][2] - R[1][2] * R[2][0])
              + R[0][2] * (R[1][0] * R[2][1] - R[1][1] * R[2][0]);
    if (det < 0.9f) return 0;   /* mirrored */
    float tr = R[0][0] + R[1][1] + R[2][2], *q = r->q;   /* quaternion of R (w, x, y, z) */
    if (tr > 0) { float S = sqrtf(tr + 1) * 2; q[0] = 0.25f * S; q[1] = (R[2][1] - R[1][2]) / S; q[2] = (R[0][2] - R[2][0]) / S; q[3] = (R[1][0] - R[0][1]) / S; }
    else if (R[0][0] > R[1][1] && R[0][0] > R[2][2]) { float S = sqrtf(1 + R[0][0] - R[1][1] - R[2][2]) * 2; q[0] = (R[2][1] - R[1][2]) / S; q[1] = 0.25f * S; q[2] = (R[0][1] + R[1][0]) / S; q[3] = (R[0][2] + R[2][0]) / S; }
    else if (R[1][1] > R[2][2]) { float S = sqrtf(1 + R[1][1] - R[0][0] - R[2][2]) * 2; q[0] = (R[0][2] - R[2][0]) / S; q[1] = (R[0][1] + R[1][0]) / S; q[2] = 0.25f * S; q[3] = (R[1][2] + R[2][1]) / S; }
    else { float S = sqrtf(1 + R[2][2] - R[0][0] - R[1][1]) * 2; q[0] = (R[1][0] - R[0][1]) / S; q[1] = (R[0][2] + R[2][0]) / S; q[2] = (R[1][2] + R[2][1]) / S; q[3] = 0.25f * S; }
    if (r->kind & 1) {   /* a view: the eye = -T * R^T * S^-1 */
        for (int j = 0; j < 3; j++)
            r->tr[j] = -(m[3][0] * R[j][0] + m[3][1] * R[j][1] + m[3][2] * R[j][2]) / r->s[j];
    } else { r->tr[0] = m[3][0]; r->tr[1] = m[3][1]; r->tr[2] = m[3][2]; }
    return 1;
}
static float hfr_qdot(const float *a, const float *b) { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3]; }
static float hfr_dist(const float *a, const float *b) { float x = a[0] - b[0], y = a[1] - b[1], z = a[2] - b[2]; return sqrtf(x * x + y * y + z * z); }
/* o = the matrix between a (t = 0) and b (t = 1) */
static void hfr_interp(float o[4][4], const HfrMtx *a, const HfrMtx *b, float t) {
    if ((a->kind & b->kind & 2)) {
        float q[4], d = hfr_qdot(a->q, b->q), sb = 1, wa, wb;
        if (d < 0) { d = -d; sb = -1; }
        if (d > 0.9995f) { wa = 1 - t; wb = t; }
        else { float th = acosf(d), sn = sinf(th); wa = sinf((1 - t) * th) / sn; wb = sinf(t * th) / sn; }
        for (int i = 0; i < 4; i++) q[i] = wa * a->q[i] + wb * sb * b->q[i];
        float l = sqrtf(hfr_qdot(q, q)); for (int i = 0; i < 4; i++) q[i] /= l;
        float w = q[0], x = q[1], y = q[2], z = q[3], R[3][3] = {
            {1 - 2 * (y * y + z * z), 2 * (x * y - z * w), 2 * (x * z + y * w)},
            {2 * (x * y + z * w), 1 - 2 * (x * x + z * z), 2 * (y * z - x * w)},
            {2 * (x * z - y * w), 2 * (y * z + x * w), 1 - 2 * (x * x + y * y)}};
        float s[3], tr[3];
        for (int i = 0; i < 3; i++) { s[i] = a->s[i] + (b->s[i] - a->s[i]) * t; tr[i] = a->tr[i] + (b->tr[i] - a->tr[i]) * t; }
        for (int i = 0; i < 3; i++) { for (int j = 0; j < 3; j++) o[i][j] = s[i] * R[i][j]; o[i][3] = 0; }
        if (a->kind & 1) for (int j = 0; j < 3; j++) o[3][j] = -(tr[0] * o[0][j] + tr[1] * o[1][j] + tr[2] * o[2][j]);   /* T = -eye * S R */
        else for (int j = 0; j < 3; j++) o[3][j] = tr[j];
        o[3][3] = 1;
        return;
    }
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) o[i][j] = a->m[i][j] + (b->m[i][j] - a->m[i][j]) * t;
}
/* G_MTX: record (mode 1) or replace m by the interpolated matrix (mode 2); prm = the G_MTX parameter bits */
static void hfr_mtx(const unsigned char *at, unsigned w0, unsigned w1, unsigned prm, float m[4][4]) {
    uint32_t sig = hfr_sig(at, w0, w1);
    if (hfr_mode == 1) {
        int n = hfr_mn[hfr_cur];
        if (n >= HFR_NM) return;
        HfrMtx *r = &hfr_m[hfr_cur][n];
        r->sig = sig; r->key = hfr_mix(sig, (uint32_t)hfr_occ_next(sig) * 0x9E3779B9u + 1);
        memcpy(r->m, m, sizeof r->m);
        r->kind = prm & 4 ? 1 : 0; r->ok = 0; r->old = -1;
        if (hfr_rigid(r)) r->kind |= 2;
        if (hfr_frames > 0)
            for (unsigned i = r->key >> 19, k = 0; k < HFR_HT && hfr_ht[i]; k++, i = (i + 1) & (HFR_HT - 1))
                if (hfr_ht_key[i] == r->key) { r->old = hfr_ht[i] - 1; break; }
        hfr_mn[hfr_cur] = n + 1;
        return;
    }
    int k = hfr_mk++;
    const HfrMtx *r = k < hfr_mn[hfr_cur] ? &hfr_m[hfr_cur][k] : 0;
    if (!r || r->sig != sig) { hfr_bad++; return; }   /* the stream is not the recorded one: memory as it is */
    if (r->ok) hfr_interp(m, &hfr_m[hfr_cur ^ 1][r->old], r, hfr_t);
    else memcpy(m, r->m, sizeof r->m);
}
/* G_CULLDL / G_BRANCH_Z: record the decision (mode 1) or take the recorded one (mode 2) */
static int hfr_decide(int d) {
    if (hfr_mode == 1) { if (hfr_nc < HFR_NC) hfr_cull[hfr_nc++] = (uint8_t)d; return d; }
    if (hfr_mode == 2 && hfr_ci < hfr_nc) return hfr_cull[hfr_ci++];
    return d;
}
/* SETCIMG in a replay: only the screen is drawn (mirrors the SETCIMG case: off = an offscreen image, hx = a kept one) */
static void hfr_setcimg(unsigned w0, unsigned w1) {
    unsigned w = (w0 & 0xFFF) + 1, siz = w0 >> 19 & 3;
    unsigned char *p = gfx_addr(w1);
    int off = w >= 16 && w <= 256 && w1 != zimg_addr && p;
    if (w1 == zimg_addr && w >= 16 && w <= 320 && siz == 2 && p) off = 1;
    int screen = !off && w >= 256 && w1 != zimg_addr && siz == 2 && p &&
                 !(!hx_disabled() && fbc_task_p && p != fbc_task_p && !hx_is_screen(p));
    flush();
    cimg_addr = w1; cimg_width = w; if (cimg_width < 64 && !off) cimg_width = 320;
    hfr_drop = !screen;
    if (screen) { if (!fbc_task_p) fbc_restore(p); fbc_task_p = p; fbc_task_w = w; }
    state_dirty = 1;
}
/* hash of the recorded task's top-level display list as it is now in game memory (0 if it is not readable) */
static uint32_t hfr_task_hash(void) {
    unsigned data = rd32(hfr_task + 48), size = rd32(hfr_task + 52);
    const unsigned char *p = gfx_addr_raw(data);
    if (!p || size > 0x100000 || !hfr_addr_ok((unsigned char *)p + size)) return 0;
    uint32_t h = 2166136261u;
    for (unsigned i = 0; i + 4 <= size; i += 4) h = (h ^ rd32(p + i)) * 16777619u;
    return h | 1;
}
/* is the newest frame still replayable: same DL buffers, its display list unchanged */
static int hfr_valid(void) {
    unsigned len;
    if (gfx_dl_buffer(0, &len) != hfr_rec_b[0] || gfx_dl_buffer(1, &len) != hfr_rec_b[1]) return 0;
    return hfr_task_hash() == hfr_dl_hash;
}
/* a game frame's task starts: the newest set becomes the older one (hash table), the recording starts */
static void hfr_frame_begin(void) {
    unsigned len;
    hfr_b[0] = gfx_dl_buffer(0, &len); hfr_b[1] = gfx_dl_buffer(1, &hfr_blen);
    if (hfr_frames > 0 && port_frame_count == hfr_rnew) {   /* a second task in the same retrace: not one game frame per task */
        hfr_frames = 0; hfr_st.snaps[HFR_SNAP_MULTI]++;
    }
    hfr_cur ^= 1;
    memset(hfr_ht, 0, sizeof hfr_ht);
    if (hfr_frames > 0)
        for (int i = 0; i < hfr_mn[hfr_cur ^ 1]; i++) {
            unsigned h = hfr_m[hfr_cur ^ 1][i].key >> 19;
            while (hfr_ht[h]) h = (h + 1) & (HFR_HT - 1);
            hfr_ht[h] = (int16_t)(i + 1); hfr_ht_key[h] = hfr_m[hfr_cur ^ 1][i].key;
        }
    hfr_mn[hfr_cur] = 0; hfr_nc = 0; hfr_occ_gen++; hfr_fx = 0;
    hfr_tgen0 = tmem_gen;
    hfr_mode = 1;
}
/* the recording ends: checks, snap decision */
static void hfr_frame_end(const void *task) {
    hfr_mode = 0;
    hfr_tgen1 = tmem_gen; hfr_vi[0] = vi_y0; hfr_vi[1] = vi_h;
    memcpy(hfr_task, task, sizeof hfr_task);
    hfr_dl_hash = hfr_task_hash(); hfr_rec_b[0] = hfr_b[0]; hfr_rec_b[1] = hfr_b[1];
    memcpy(hfr_ws_sub, ws_sub, sizeof ws_sub); hfr_ws_sub_n = ws_sub_n;
    memcpy(hfr_ws_mark, ws_mark, sizeof ws_mark); hfr_ws_mark_n = ws_mark_n;
    unsigned gap = hfr_frames > 0 ? port_frame_count - hfr_rnew : 0;
    hfr_rold = hfr_rnew; hfr_rnew = port_frame_count;
    int cut = 0, n = hfr_mn[hfr_cur];
    hfr_moving = hfr_matched = 0;
    for (int i = 0; i < n; i++) {
        HfrMtx *r = &hfr_m[hfr_cur][i];
        if (r->old < 0 || hfr_frames == 0) continue;
        const HfrMtx *a = &hfr_m[hfr_cur ^ 1][r->old];
        hfr_matched++;
        if (!memcmp(a->m, r->m, sizeof r->m)) continue;   /* the same matrix: nothing to do */
        if ((a->kind ^ r->kind) & 1) continue;
        if (a->kind & r->kind & 2) {
            float d = fabsf(hfr_qdot(a->q, r->q)), ang = 2 * acosf(d > 1 ? 1 : d) * 57.29578f, mv = hfr_dist(a->tr, r->tr);
            if (r->kind & 1) { if (ang > 45 || mv > HFR_JUMP) { if (!cut && hfr_log > 0) port_log("[hfr]   cut: view %d (old %d) turns %.1f deg, eye moves %.1f: %.3f %.3f %.3f %.3f / %.3f %.3f %.3f %.3f T %.1f %.1f %.1f / %.1f %.1f %.1f\n",
                                   i, r->old, ang, mv, a->q[0], a->q[1], a->q[2], a->q[3], r->q[0], r->q[1], r->q[2], r->q[3], a->m[3][0], a->m[3][1], a->m[3][2], r->m[3][0], r->m[3][1], r->m[3][2]);
                                   cut = 1; } else r->ok = 1; }
            else if (ang <= 100 && mv <= HFR_JUMP) r->ok = 1;
        } else if (!((a->kind | r->kind) & 2)) {   /* projections, sheared: element-wise unless very different */
            float dd = 0, nn = 0;
            for (int j = 0; j < 4; j++) for (int k = 0; k < 4; k++) { float e = r->m[j][k] - a->m[j][k]; dd += e * e; nn += r->m[j][k] * r->m[j][k]; }
            if (dd <= 4.0f * 4.0f * nn) r->ok = 1;   /* a perspective x view product: element-wise = the product with the view lerped */
        }
        hfr_moving += r->ok;
    }
    if (hfr_frames > 0 && gap > 0) hfr_ival += (((float)gap > 6 ? 6.0f : (float)gap) - hfr_ival) * 0.25f;
    hfr_snap = hfr_frames == 0 ? HFR_SNAP_FIRST : hfr_fx ? HFR_SNAP_FX : cut ? HFR_SNAP_CUT : gap > 8 ? HFR_SNAP_GAP :
               hfr_matched * 2 < n ? HFR_SNAP_SCENE : !hfr_moving ? HFR_SNAP_STATIC : HFR_SNAP_NONE;
    hfr_st.frames++; hfr_st.snaps[hfr_snap]++;
    if (hfr_log > 0 && hfr_snap != HFR_SNAP_NONE && hfr_snap != HFR_SNAP_STATIC) {
        static unsigned nl; if (nl++ < 200) port_log("[hfr] frame at retrace %u: snap (%s), %d matrices, %d matched, %d interpolated\n",
                                                      hfr_rnew, hfr_snap_name[hfr_snap], n, hfr_matched, hfr_moving); }
    hfr_frames++;
    hfr_shown_t = 1; hfr_shown_r = hfr_rnew;   /* the canvas shows the frame as drawn */
}
static void gfx_run_task_body(void *task);
/* redraw the newest game frame at t (0 = the previous frame's matrices, 1 = as drawn) */
static void hfr_replay(float t) {
    GfxStats st = gfx_stats;
    unsigned gen = tmem_gen;
    int sub_n = ws_sub_n, mark_n = ws_mark_n; const unsigned char *skip = ws_sub_skip;
    static struct { const unsigned char *gs, *ge; uint32_t h; const unsigned char *pdl; } sub[WS_SUB_N];
    static struct { const unsigned char *at; int tag; } mark[WS_MARK_N];
    memcpy(sub, ws_sub, sizeof sub); memcpy(mark, ws_mark, sizeof mark);
    memcpy(ws_sub, hfr_ws_sub, sizeof ws_sub); ws_sub_n = hfr_ws_sub_n; ws_sub_bounds(); ws_sub_skip = 0;
    memcpy(ws_mark, hfr_ws_mark, sizeof ws_mark); ws_mark_n = hfr_ws_mark_n;
    uintptr_t mlo = ws_mark_lo, mhi = ws_mark_hi;
    ws_mark_lo = ~(uintptr_t)0; ws_mark_hi = 0;
    for (int i = 0; i < ws_mark_n; i++) {
        if ((uintptr_t)ws_mark[i].at < ws_mark_lo) ws_mark_lo = (uintptr_t)ws_mark[i].at;
        if ((uintptr_t)ws_mark[i].at > ws_mark_hi) ws_mark_hi = (uintptr_t)ws_mark[i].at;
    }
    float vy = vi_y0, vh = vi_h;
    unsigned len;
    hfr_b[0] = gfx_dl_buffer(0, &len); hfr_b[1] = gfx_dl_buffer(1, &hfr_blen);
    hfr_mode = 2; hfr_t = t; hfr_ci = hfr_mk = 0; hfr_bad = 0; hfr_drop = 0;
    tmem_gen = hfr_tgen0; vi_y0 = hfr_vi[0]; vi_h = hfr_vi[1];
    gfx_run_task_body(hfr_task);
    hfr_mode = 0; hfr_drop = 0;
    tmem_gen = gen; vi_y0 = vy; vi_h = vh;
    hfr_st.uploads += gfx_stats.tex_uploads - st.tex_uploads;
    gfx_stats = st;
    memcpy(ws_sub, sub, sizeof sub); ws_sub_n = sub_n; ws_sub_bounds(); ws_sub_skip = skip;
    memcpy(ws_mark, mark, sizeof mark); ws_mark_n = mark_n; ws_mark_lo = mlo; ws_mark_hi = mhi;
    if (hfr_bad) { hfr_st.bad++; hfr_snap = HFR_SNAP_SCENE; }   /* the display list changed under us: stop replaying this frame */
}
static void hfr_log_stats(double now) {
    double el = (now - hfr_st.t0) / 1000;
    if (hfr_log > 0 && el >= 2.0) {
        unsigned d = hfr_st.drawn ? hfr_st.drawn : 1;
        port_log("[hfr] %.2f s: %u shown (%.1f /s: %u redrawn between game frames, %u as drawn), %u game frames (%.1f /s, interval %.2f retraces); "
                 "snaps first %u cut %u fx %u multi %u gap %u scene %u static %u; replay %.2f ms cpu (max %.2f), game task %.2f ms; "
                 "key mismatches %u, uploads in replays %u; newest: %d matrices, %d matched, %d interpolated\n",
                 el, hfr_st.shown, hfr_st.shown / el, hfr_st.drawn, hfr_st.kept, hfr_st.frames, hfr_st.frames / el, hfr_ival,
                 hfr_st.snaps[1], hfr_st.snaps[2], hfr_st.snaps[3], hfr_st.snaps[4], hfr_st.snaps[5], hfr_st.snaps[6], hfr_st.snaps[7],
                 hfr_st.t_replay / d, hfr_st.t_replay_max, hfr_st.frames ? hfr_st.t_task / hfr_st.frames : 0.0,
                 hfr_st.bad, hfr_st.uploads, hfr_mn[hfr_cur], hfr_matched, hfr_moving);
        memset(&hfr_st, 0, sizeof hfr_st);
    }
    if (!hfr_st.t0) hfr_st.t0 = now;
}
/* pc_sched.c frame(), at the end of every main-loop tick (not while paused / in photo mode): pos = the display time in
 * retraces; online (net) only once per browser animation frame */
void port_gfx_hfr_present(double pos, int net) {
    if (!hfr_opt || !gl_ok || hfr_frames == 0) return;
    if (net) { if (hfr_vsync == hfr_vsync_seen) return; hfr_vsync_seen = hfr_vsync; }
    if (hfr_log < 0) { hfr_log = port_flag("hfrlog"); hfr_trace = port_flag("hfrtrace"); }
    double now = emscripten_get_now();
    hfr_log_stats(now);
    hfr_st.shown++;
    float t = hfr_snap ? 1.0f : (float)((pos - hfr_rnew) / hfr_ival);
    if (t < 0) t = 0; if (t > 1) t = 1;
    int draw = !hfr_snap && !(hfr_shown_r == hfr_rnew && fabsf(hfr_shown_t - t) < 0.002f);
    if (hfr_trace > 0 && pos >= hfr_trace && hfr_trace_n < 150) { hfr_trace_n++;
        port_log("[hfr] present pos %.3f: newest frame %u (previous %u, interval %.2f), t %.3f, %s\n", pos, hfr_rnew, hfr_rold, hfr_ival, t,
                 draw ? "redrawn" : hfr_snap ? hfr_snap_name[hfr_snap] : "unchanged"); }
    if (!draw) { hfr_st.kept++; return; }
    if (!hfr_valid()) { hfr_snap = HFR_SNAP_SCENE; hfr_frames = 0; hfr_st.bad++; hfr_st.kept++; return; }   /* level change: the list is gone */
    hfr_replay(t);
    { static int fin = -1; if (fin < 0) fin = port_flag("hfrfinish"); if (fin) glFinish(); }   /* ?hfrfinish=1: the time includes the GPU's work */
    double dt = emscripten_get_now() - now;
    hfr_st.drawn++; hfr_st.t_replay += dt; if (dt > hfr_st.t_replay_max) hfr_st.t_replay_max = dt;
    hfr_shown_r = hfr_rnew; hfr_shown_t = t;
}
/* test aid: redraw the newest frame at t (returns 0 when drawn, else the snap reason) */
EMSCRIPTEN_KEEPALIVE int port_gfx_hfr_test(float t) {
    if (!gl_ok || hfr_frames == 0) return -1;
    if (hfr_snap) return hfr_snap;
    if (!hfr_valid()) return -2;
    hfr_replay(t < 0 ? 0 : t > 1 ? 1 : t);
    hfr_shown_r = hfr_rnew; hfr_shown_t = t;
    return 0;
}

/* P351 DIAGNOSTIC ?p351log=F: every G_MTX of 3 tasks from retrace F (where the command and the matrix live) */
static int p351_logn = -1;
static void p351_cls(const void *p, char *o) {
    unsigned len;
    for (int i = 0; i < 2; i++) {
            const unsigned char *b = gfx_dl_buffer(i, &len);
            if (b && (const unsigned char *)p >= b && (const unsigned char *)p < b + len) {
                sprintf(o, "B%d+%05X", i, (unsigned)((const unsigned char *)p - b)); return; }
        }
    sprintf(o, "%08X", (unsigned)(uintptr_t)p);
}
static void p351_mtx_log(const unsigned char *at, unsigned w0, unsigned w1, const unsigned char *p, float m[4][4], int sp) {
    char a[24], b[24], c[24] = "-";
    p351_cls(at, a); p351_cls(p, b);
    unsigned nx = 0;
    for (int k = 1; k < 24; k++) { unsigned op = rd32(at + 8 * k) >> 24; if (op == 0xDE || op == 0x01 || op == 0xDF || op == 0xDA) { nx = rd32(at + 8 * k + 4); if (op == 0xDE || op == 0x01) { const unsigned char *q = gfx_addr(nx); if (q) p351_cls(q, c); } sprintf(c + strlen(c), "/%02X", op); break; } }
    port_log("[p351] mtx sp%d at %s %08X %08X -> %s T %.1f %.1f %.1f r %.3f %.3f | next %08X %s\n", sp, a, w0, w1, b, m[3][0], m[3][1], m[3][2], m[0][0], m[0][1], nx, c);
}

void gfx_run_dl(const void *dl) {
    const unsigned char *stack[32], *pc = dl;
    int sp = 0, guard = 0;
    gfx_stats.dls++;
    while (pc && ++guard < 1000000) {
        if (ws_mark_n && (uintptr_t)pc >= ws_mark_lo && (uintptr_t)pc <= ws_mark_hi) {   /* P350: a HUD anchor */
            int t = -1;
            for (int i = 0; i < ws_mark_n; i++) if (ws_mark[i].at == pc) t = ws_mark[i].tag;
            if (t >= 0 && t != ws_tag) { flush(); ws_tag = t; state_dirty = 1; }
        }
        if (ws_sub_n && (uintptr_t)pc >= ws_sub_lo && (uintptr_t)pc <= ws_sub_hi && sp < 32) {   /* P350: a wide copy */
            int i = ws_sub_find(pc);
            ws_calc();
            if (i >= 0 && ws_on) { stack[sp++] = ws_sub[i].ge; pc = ws_sub[i].pdl; ws_sub_stats[1]++; }
        }
        if (hfr_mode == 2 && !hfr_addr_ok((unsigned char *)pc)) { hfr_bad++; break; }   /* P351: a replay never reads outside memory */
        unsigned w0 = rd32(pc), w1 = rd32(pc + 4), op = w0 >> 24;
        if (gfx_trace) port_log("[gfx]   %p: %08X %08X\n", (const void *)pc, w0, w1);
        pc += 8;
        gfx_stats.cmds++;
        if (p61_depth >= 0) p61_cmds++;
        fr_ops[op]++;
        if (op >= 0x10 && op <= 0x1F) {
            /* Conker (Rare F3DEX2 variant): four triangles in one command, 12 five-bit indices */
            gfx_stats.tri4++;
            tri(w0 >> 23 & 31, w0 >> 18 & 31, (w0 >> 15 & 7) << 2 | w1 >> 30);
            tri(w0 >> 10 & 31, w0 >> 5 & 31, w0 & 31);
            tri(w1 >> 25 & 31, w1 >> 20 & 31, w1 >> 15 & 31);
            tri(w1 >> 10 & 31, w1 >> 5 & 31, w1 & 31);
            continue;
        }
        switch (op) {
        case 0x00: break;                                     /* G_NOOP */
        case 0x01: load_vtx(w0, w1); break;                   /* G_VTX */
        case 0x02: {                                          /* G_MODIFYVTX */
            V *v = &vb[(w0 & 0xFFFF) / 2 & 63];
            unsigned where = w0 >> 16 & 0xFF;
            if (where == 0x10) { v->r = (w1 >> 24) / 255.0f; v->g = (w1 >> 16 & 255) / 255.0f; v->b = (w1 >> 8 & 255) / 255.0f; v->a = (w1 & 255) / 255.0f; }
            else if (where == 0x14) { v->s = (short)(w1 >> 16) / 32.0f; v->t = (short)w1 / 32.0f; }
            if (p78_on) port_log("[p78vtx] G_MODIFYVTX %08X %08X: vertex %u where %02X\n", w0, w1, (w0 & 0xFFFF) / 2, where); /* P88 */
            break;
        }
        case 0x03: {                                          /* G_CULLDL (P35) */
            /* F3DEX2: end this DL when every vertex vstart..vend is outside one and the same plane of the
             * view volume (x, y against +-w, w <= 0 behind the eye, z > w beyond far). Vertices are those
             * already loaded (clip space, after the renderer's MVP, so freecam culls for its own view). */
            unsigned a0 = (w0 & 0xFFFF) / 2, a1 = (w1 & 0xFFFF) / 2, all = 0x7F;
            ws_calc();
            if (a1 > 63) a1 = 63;
            for (unsigned i = a0; i <= a1; i++) {
                const V *v = &vb[i];
                float xw = ws_on && proj_persp ? v->w * ws_k : v->w;   /* P350: the wider view */
                unsigned c = (v->x < -xw) | (v->x > xw) << 1 | (v->y < -v->w) << 2 | (v->y > v->w) << 3 |
                             (v->w <= 0) << 4 | (v->z > v->w) << 5;
                all &= c;
            }
            gfx_stats.culldl++;
            if (hfr_mode ? hfr_decide(all && a0 <= a1) : all && a0 <= a1) {   /* P351: a replay takes the recorded decision */ gfx_stats.culled++; pc = sp ? stack[--sp] : 0;
                if (p61_depth >= 0 && sp <= p61_depth) { p61_depth = -1; if (p61_tr) { p61_tr = 0; gfx_trace = 0; } } }
            break;
        }
        case 0x04: {                                          /* G_BRANCH_Z (P35) */
            /* branch to RDPHALF_1 when the vertex's screen z (16.16, viewport-mapped as the RSP stores it)
             * is <= w1, the gSPBranchLessZ value (G_DEPTOZS: depth 0..0x3FF in 16.16); else fall through
             * to the following (coarser) DL. */
            const V *v = &vb[((w0 & 0xFFF) / 2) & 63];
            float zs = v->w != 0 ? (v->z / v->w) * vp_scale[2] + vp_trans[2] : 0;
            double z16 = (double)zs * 65536.0;
            gfx_stats.branchz++;
            if (hfr_mode ? hfr_decide(v->w > 0 && z16 <= (double)(int)w1) : v->w > 0 && z16 <= (double)(int)w1) {   /* P351 */
                const unsigned char *t = gfx_addr(rdphalf1);
                if (t) { pc = t; gfx_stats.branchz_taken++; }
            }
            break;
        }
        case 0x05: tri((w0 >> 16 & 0xFF) / 2, (w0 >> 8 & 0xFF) / 2, (w0 & 0xFF) / 2); break;
        case 0x06: case 0x07:                                 /* G_TRI2 / G_QUAD */
            tri((w0 >> 16 & 0xFF) / 2, (w0 >> 8 & 0xFF) / 2, (w0 & 0xFF) / 2);
            tri((w1 >> 16 & 0xFF) / 2, (w1 >> 8 & 0xFF) / 2, (w1 & 0xFF) / 2);
            break;
        case 0xD7:                                            /* G_TEXTURE */
            tex_level = w0 >> 11 & 7; tex_tile = w0 >> 8 & 7; tex_on = w0 >> 1 & 0x7F;
            tex_sc_s = (w1 >> 16) / 65536.0f; tex_sc_t = (w1 & 0xFFFF) / 65536.0f;
            if ((w1 >> 16) == 0xFFFF) tex_sc_s = 1; if ((w1 & 0xFFFF) == 0xFFFF) tex_sc_t = 1;
            state_dirty = 1; break;
        case 0xD8: mvsp -= w1 / 64; if (mvsp < 0) mvsp = 0;  /* G_POPMTX */
            memcpy(mv, mvstack[mvsp], sizeof mv); mtx_mul(mp, mv, proj); mtx_mul(mp_game, mv, proj_game); light_dirty = 1; break;
        case 0xD9: geom = (geom & (w0 & 0xFFFFFF)) | w1; state_dirty = 1; break; /* G_GEOMETRYMODE */
        case 0xDA: {                                          /* G_MTX */
            const unsigned char *p = gfx_addr(w1);
            if (p61_flag && g_model_draw_ident_mtx && w1 == ((unsigned)(uintptr_t)g_model_draw_ident_mtx & 0x1FFFFFFF)) {   /* P61: obj_draw_model_dl's G_MTX */
                p61_mtx++; p61_pend = 1;
                if (!p61_mark++) {
                    port_log("[p61] first model G_MTX %08X %08X at %p (task %u): resolves to %p, &D_800C42B8 %p (%s)\n", w0, w1,
                             (const void *)(pc - 8), gfx_stats.tasks, (const void *)p, (const void *)g_model_draw_ident_mtx,
                             p == g_model_draw_ident_mtx ? "same" : "DIFFERENT");
                    for (int k = -24; k < 0; k++)   /* obj_draw_model_dl's setup before it */
                        port_log("[p61]   %p: %08X %08X\n", (const void *)(pc - 8 + 8 * k), rd32(pc - 8 + 8 * k), rd32(pc - 4 + 8 * k));
                }
            } else if (p61_depth >= 0) p61_icls[p61_cls(w1)]++, p61_imtx++;
            if (!p) { gfx_stats.bad_addr++; break; }
            unsigned prm = (w0 & 0xFF) ^ 1;                  /* ^ G_MTX_PUSH */
            float m[4][4];
            mtx_read(m, p);
            if (p351_logn > 0) p351_mtx_log(pc - 8, w0, w1, p, m, sp);
            if (hfr_mode) hfr_mtx(pc - 8, w0, w1, prm, m);   /* P351: recorded, or interpolated in a replay */
            if (p61_tr && p61_trn < 40) { p61_trn++;
                port_log("[p61] G_MTX %08X %08X %s%s%s: %.4f %.4f %.4f %.4f | %.4f %.4f %.4f %.4f | %.4f %.4f %.4f %.4f | %.2f %.2f %.2f %.4f\n",
                         w0, w1, prm & 4 ? "P" : "MV", prm & 2 ? " load" : " mul", prm & 1 ? " push" : "",
                         m[0][0], m[0][1], m[0][2], m[0][3], m[1][0], m[1][1], m[1][2], m[1][3],
                         m[2][0], m[2][1], m[2][2], m[2][3], m[3][0], m[3][1], m[3][2], m[3][3]); }
            { static int md = -1; if (md < 0) md = port_flag("mtxdump"); /* P25: ?mtxdump=1 + dltrace: G_MTX contents */
              if (md && gfx_trace)
                  port_log("[mtx] %08X %s%s%s: %.4f %.4f %.4f %.4f | %.4f %.4f %.4f %.4f | %.4f %.4f %.4f %.4f | %.4f %.4f %.4f %.4f\n",
                           w1, prm & 4 ? "P" : "MV", prm & 2 ? " load" : " mul", prm & 1 ? " push" : "",
                           m[0][0], m[0][1], m[0][2], m[0][3], m[1][0], m[1][1], m[1][2], m[1][3],
                           m[2][0], m[2][1], m[2][2], m[2][3], m[3][0], m[3][1], m[3][2], m[3][3]); }
            if (prm & 4) { if (prm & 2) memcpy(proj_game, m, sizeof m); else mtx_mul(proj_game, m, proj_game); }
            if ((prm & 6) == 4 && fc_on > 0 && fc_init) freecam_view(m); /* P33 ?freecam=1: the world view */
            if (prm & 4) { if (prm & 2) memcpy(proj, m, sizeof m); else mtx_mul(proj, m, proj); }
            if (prm & 4) {   /* P350: perspective (widened with the option) or orthographic (2D-like) */
                int pp = fabsf(proj[0][3]) > 1e-6f || fabsf(proj[1][3]) > 1e-6f || fabsf(proj[2][3]) > 1e-6f;
                if (pp != proj_persp) { proj_persp = pp; state_dirty = 1; }
            }
            else {
                light_dirty = 1;
                if ((prm & 1) && mvsp < 31) memcpy(mvstack[mvsp++], mv, sizeof mv);
                if (prm & 2) memcpy(mv, m, sizeof m); else mtx_mul(mv, m, mv);
            }
            mtx_mul(mp, mv, proj); mtx_mul(mp_game, mv, proj_game);
            break;
        }
        case 0xDB: {                                          /* G_MOVEWORD */
            unsigned idx = w0 >> 16 & 0xFF, off = w0 & 0xFFFF;
            if (idx == 6) { segtab[(off / 4) & 15] = w1; segset |= 1u << ((off / 4) & 15); }
            else if (idx == 8) { fog_mul = (short)(w1 >> 16); fog_off = (short)w1; }
            else if (idx == 2) { light_nls = w1 & 0xFFFF; light_dirty = 1; light_seen = 1; } /* G_MW_NUMLIGHT (48 N) */
            else if (idx == 0x0A && 0x60 + off + 4 <= sizeof lbuf) {          /* G_MW_LIGHTCOL -> DMEM 0x2C0 + off */
                for (int k = 0; k < 4; k++) lbuf[0x60 + off + k] = w1 >> (24 - 8 * k);
            } else if (idx == 0x10 && off + 4 <= sizeof rare10) {             /* Rare: inverse projection block (DMEM 0x1D0) */
                for (int k = 0; k < 4; k++) rare10[off + k] = w1 >> (24 - 8 * k);
            } else if (idx == 0x0E) persp_norm = w1 & 0xFFFF;                /* G_MW_PERSPNORM (float math: unused) */
            else if (idx == 4) clip_ratio = w1;                               /* G_MW_CLIP (GPU clips; unused) */
            break;
        }
        case 0xDC: {                                          /* G_MOVEMEM */
            unsigned idx = w0 & 0xFF;
            const unsigned char *p = gfx_addr(w1);
            if (idx == 8 && p) {                              /* G_MV_VIEWPORT */
                for (int i = 0; i < 4; i++) { vp_scale[i] = (short)vbe_ld16(p + 2 * i); vp_trans[i] = (short)vbe_ld16(p + 8 + 2 * i); }
                state_dirty = 1;
            } else if (idx == 0x0E) {                         /* Conker: vertex normals -> DMEM 0x510 (copied now) */
                unsigned len = ((w0 >> 19 & 0x1F) + 1) * 8, off = (w0 >> 8 & 0xFF) * 8;
                normal_base = w1;
                for (unsigned k = 0; k < len && off + k < sizeof nbuf; k++) nbuf[off + k] = p ? vbe_ld8(p + k) : 0;
            }
            else if (idx == 0x0A && p) {                      /* G_MV_LIGHT -> DMEM 0x260 + offset, see light_vtx() */
                unsigned off = (w0 >> 8 & 0xFF) * 8, len = ((w0 >> 19 & 0x1F) + 1) * 8;
                for (unsigned k = 0; k < len && off + k < sizeof lbuf; k++) lbuf[off + k] = vbe_ld8(p + k);
                light_dirty = 1; light_seen = 1;
                if (gfx_trace) { char b[160]; int m = 0;   /* P35: record bytes under dltrace */
                    for (unsigned k = 0; k < len && k < 48; k++) m += snprintf(b + m, sizeof b - m, "%02X%s", lbuf[off + k], (k & 3) == 3 ? " " : "");
                    port_log("[light] off 0x%02X: %s\n", off, b); }
            }
            break;
        }
        case 0xDD:   /* G_LOAD_UCODE: w1 = ucode TEXT, the preceding RDPHALF_1 = DATA (gSPLoadUcodeEx: gDma0p(G_RDPHALF_1,
                      * uc_dstart), gDma1p(G_LOAD_UCODE, uc_start, uc_dsize - 1)). P94: before, the two were swapped, so DMEM
                      * (light records, Rare block, normals) was seeded from the ucode TEXT: record 2 (DMEM 0x320) read the
                      * RSP instructions 4B6B58F2 4B6A58B1 as a green-grey "ambient" 4B6B58 for every character. */
            if (gfx_stats.ucode_loads++ < 4) port_log("[gfx] G_LOAD_UCODE text %08X data %08X size 0x%X\n", w1, rdphalf1, (w0 & 0xFFFF) + 1);
            { static int oldseed = -1; if (oldseed < 0) oldseed = port_flag("p94oldseed");   /* ?p94oldseed=1: the pre-P94 (wrong) seed */
              flush(); dmem_seed(oldseed ? w1 : rdphalf1, (w0 & 0xFFFF) + 1); light_nls = 0; }   /* P35b: DMEM data reloaded */
            { static int ud2;   /* P94 ?udump=2: hex dump of the loaded ucode text (0x1800) + data (0x800), once */
              const unsigned char *ut = gfx_addr(w1), *uda = gfx_addr(rdphalf1);
              if (!ud2 && ut && uda && port_flag("udump") == 2) { ud2 = 1;
                for (unsigned w = 0; w < 2; w++) for (unsigned o = 0; o < (w ? 0x800u : 0x1800u); o += 32) {
                    char b[80]; int m = 0;
                    for (unsigned k = 0; k < 32; k++) m += snprintf(b + m, sizeof b - m, "%02X", vbe_ld8((w ? uda : ut) + o + k));
                    port_log("[udump2] %c %04X %s\n", w ? 'D' : 'T', o, b); } } }
            { static int cmpd; const unsigned char *a = gfx_addr(cur_ucode), *b = gfx_addr(w1), *da = gfx_addr(cur_udata), *db = gfx_addr(rdphalf1);
              if (!cmpd++ && a && b && da && db) { int dt = 0, dd = 0, first = -1;
                for (int k = 0; k < 0x1400; k++) if (vbe_ld8(a + k) != vbe_ld8(b + k)) { dt++; if (first < 0) first = k; }
                for (int k = 0; k < 0x800; k++) dd += vbe_ld8(da + k) != vbe_ld8(db + k);
                for (int w = 0; w < 2; w++) { const unsigned char *q = w ? db : da; char nm[64]; int j = 0;
                    for (int k = 0; k < 0x7C0 && !j; k++) if (vbe_ld8(q + k) == 'R' && vbe_ld8(q + k + 1) == 'S' && vbe_ld8(q + k + 2) == 'P')
                        for (; j < 63 && vbe_ld8(q + k + j) >= 32; j++) nm[j] = vbe_ld8(q + k + j);
                    nm[j] = 0; port_log("[ucode] %s data: '%s'\n", w ? "loaded" : "task", nm); }
                port_log("[ucode] task ucode %08X vs loaded %08X: %d of 0x1400 text bytes differ (first 0x%X), %d of 0x800 data bytes\n", cur_ucode, w1, dt, first, dd); } }
            break;
        case 0xDE: {                                          /* G_DL / G_BRANCH_DL */
            const unsigned char *t = gfx_addr(w1);
            if (!t) { gfx_stats.bad_addr++; break; }
            if (w1 == 0) { /* P55: G_DL 0 only comes from an asm stub that returned a NULL DL (hud_health_draw draws
                            * g_hud_health_piece_dl = stub shared_dl_acquire(0xB8)); RDRAM 0 is code, running it crashed the renderer */
                static int logged;
                gfx_stats.bad_addr++;
                if (!logged++) port_log("[gfx] G_DL to address 0 at %p skipped (a stub returned a NULL display list)\n", (const void *)(pc - 8));
                break;
            }
            { unsigned *e = dl_ring[dl_ring_n++ & 7]; e[0] = (unsigned)(uintptr_t)(pc - 8); e[1] = w0; e[2] = w1; }
            if (p61_pend && p61_depth < 0) {   /* P61: a model sub-DL g_model_dl_tables[model][k] */
                p61_pend = 0; p61_dl++; p61_depth = sp; p61_bad0 = gfx_stats.bad_addr + gfx_stats.unset_seg;
                if (p61_flag && p61_mark == 1 && p61_dl == 1) { p61_tr = 1; gfx_trace = 1; port_log("[p61] sub-DL %08X:\n", w1); }
            }
            if (!(w0 >> 16 & 0xFF)) { if (sp >= 32) break; stack[sp++] = pc; }
            pc = t;
            break;
        }
        case 0xDF: pc = sp ? stack[--sp] : 0;                 /* G_ENDDL */
            if (p61_depth >= 0 && sp <= p61_depth) {   /* P61: back from the model sub-DL */
                p61_depth = -1; p61_bad += gfx_stats.bad_addr + gfx_stats.unset_seg - p61_bad0;
                if (p61_tr) { p61_tr = 0; gfx_trace = 0; }
            }
            break;
        case 0xE0: break;                                     /* G_SPNOOP */
        case 0xE1: rdphalf1 = w1; break;
        case 0xF1: rdphalf2 = w1; break;
        case 0xE2: case 0xE3: {                               /* G_SETOTHERMODE_L / _H */
            unsigned len = (w0 & 0xFF) + 1, shift = 32 - (w0 >> 8 & 0xFF) - len;
            unsigned mask = (len >= 32 ? 0xFFFFFFFFu : ((1u << len) - 1)) << shift;
            if (op == 0xE2) oth_l = (oth_l & ~mask) | (w1 & mask); else oth_h = (oth_h & ~mask) | (w1 & mask);
            state_dirty = 1; break;
        }
        case 0xEF: oth_h = w0 & 0xFFFFFF; oth_l = w1; state_dirty = 1; break; /* G_RDPSETOTHERMODE */
        case 0xE4: case 0xE5: {                               /* G_TEXRECT(FLIP) + RDPHALF_1/_2 */
            unsigned st_word = rd32(pc + 4), dsdt_word = rd32(pc + 12);   /* RDPHALF_1 / _2 words; were h1, h2 */
            pc += 16;
            float lrx = (w0 >> 12 & 0xFFF) / 4.0f, lry = (w0 & 0xFFF) / 4.0f, ulx = (w1 >> 12 & 0xFFF) / 4.0f, uly = (w1 & 0xFFF) / 4.0f;
            float s = (short)(st_word >> 16) / 32.0f, t = (short)st_word / 32.0f, ds = (short)(dsdt_word >> 16) / 1024.0f, dt = (short)dsdt_word / 1024.0f;
            unsigned cyc = oth_h >> 20 & 3;
            if (cyc >= 2) { lrx += 1; lry += 1; if (cyc == 2) ds /= 4; }
            unsigned saved_tile = tex_tile;   /* was keep */
            tex_tile = w1 >> 24 & 7; state_dirty = 1;
            { static int lf = -1, ln; if (lf < 0) lf = port_flag("p349log");   /* P349 DIAGNOSTIC ?p349log=F: texture rectangles from retrace F */
              if (lf > 0 && port_frame_count >= (unsigned)lf && ln < 400) { const Tile *T = &tiles[tex_tile]; ln++;
                port_log("[p349] task %u rect %.2f,%.2f..%.2f,%.2f s %.3f t %.3f ds %.4f dt %.4f cyc %u tf %u tile %u fmt %u siz %u cm %u/%u mask %u/%u ul %.2f,%.2f lr %.2f,%.2f oth %06X/%08X cc %06X/%08X\n",
                         gfx_stats.tasks, ulx, uly, lrx, lry, s, t, ds, dt, cyc, oth_h >> 12 & 3, tex_tile, T->fmt, T->siz, T->cms, T->cmt, T->masks, T->maskt,
                         T->uls / 4.0, T->ult / 4.0, T->lrs / 4.0, T->lrt / 4.0, oth_h, oth_l, combine_w0, combine_w1); } }
            hx_texrect(tex_tile, ulx, uly, s, t, ds, dt);   /* P335 */
            float sv = s, tv = t;   /* s / t at the rectangle's upper-left corner as the vertices carry them */
            if (hires_2d && !off_on && !hxs_on) {   /* P349: centred on the N64 pixel (offscreen N64-size images stay as the RDP draws them) */
                rect_hires_setup(tex_tile, s, t, ds, dt, lrx - ulx, lry - uly, cyc);
                sv -= 0.5f * ds; tv -= 0.5f * dt;
            }
            if (hxs_on && ws_opt) { ws_calc(); if (ws_on) rect_ext = ws_rect_edges(ulx, lrx); }   /* P350: a full frame, per canvas pixel */
            if (!gfx_measure_only) rect(ulx, uly, lrx, lry, sv, tv, sv + ds * (lrx - ulx), tv + dt * (lry - uly), 0xFFFFFFFF, 2);
            tex_tile = saved_tile; hxs_on = 0; rect_hires_mode = 0; state_dirty = 1;
            break;
        }
        case 0xE6: case 0xE7: case 0xE8: case 0xE9: break;   /* syncs */
        case 0xED:                                            /* G_SETSCISSOR (P35b) */
            sc_box[0] = (w0 >> 12 & 0xFFF) / 4.0f; sc_box[1] = (w0 & 0xFFF) / 4.0f;
            sc_box[2] = (w1 >> 12 & 0xFFF) / 4.0f; sc_box[3] = (w1 & 0xFFF) / 4.0f;
            sc_on = sc_box[2] > sc_box[0] && sc_box[3] > sc_box[1]; state_dirty = 1;
            if (off_on && sc_on) { unsigned r = (unsigned)(sc_box[3] + 0.75f); off_rows = r < 1 ? 1 : r > OFF_FBO_H ? OFF_FBO_H : r; }  /* P140 */
            if (hx_cur >= 0 && sc_on) { unsigned r = (unsigned)(sc_box[3] + 0.75f); hx[hx_cur].rows = r < 1 ? 1 : r > 288 ? 288 : r; }   /* P335: as P140 (depth row: 1) */
            break;
        case 0xEE: prim_z = w1 >> 16; state_dirty = 1; break; /* G_SETPRIMDEPTH (used with G_ZS_PRIM) */
        case 0xEC: k4k5 = w1 & 0x3FFFF; state_dirty = 1; break;  /* G_SETCONVERT (YUV coefficients, K4/K5). P26: the frame sends EC000000 000000FF
                            * (K5 = 0xFF) twice; no YUV texture or K4/K5 combiner input is used yet. */
        case 0xF0: load_tlut(w0, w1); break;
        case 0xF2: {                                          /* G_SETTILESIZE */
            Tile *t = &tiles[w1 >> 24 & 7];
            t->uls = w0 >> 12 & 0xFFF; t->ult = w0 & 0xFFF; t->lrs = w1 >> 12 & 0xFFF; t->lrt = w1 & 0xFFF;
            state_dirty = 1; break;
        }
        case 0xF3: load_block(w0, w1); break;
        case 0xF4: load_tile(w0, w1); break;
        case 0xF5: {                                          /* G_SETTILE */
            Tile *t = &tiles[w1 >> 24 & 7];
            t->fmt = w0 >> 21 & 7; t->siz = w0 >> 19 & 3; t->line = w0 >> 9 & 0x1FF; t->tmem = w0 & 0x1FF;
            t->pal = w1 >> 20 & 15; t->cmt = w1 >> 18 & 3; t->maskt = w1 >> 14 & 15; t->shiftt = w1 >> 10 & 15;
            t->cms = w1 >> 8 & 3; t->masks = w1 >> 4 & 15; t->shifts = w1 & 15;
            state_dirty = 1; break;
        }
        case 0xF6: {                                          /* G_FILLRECT */
            float lrx = (w0 >> 12 & 0xFFF) / 4.0f, lry = (w0 & 0xFFF) / 4.0f, ulx = (w1 >> 12 & 0xFFF) / 4.0f, uly = (w1 & 0xFFF) / 4.0f;
            if (gfx_measure_only) break;
            if (cimg_addr && cimg_addr == zimg_addr) { flush(); if (gl_ok) { if (off_on) glBindFramebuffer(GL_FRAMEBUFFER, 0);   /* P161: canvas depth */
                glDepthMask(GL_TRUE); glClear(GL_DEPTH_BUFFER_BIT); if (off_on) glBindFramebuffer(GL_FRAMEBUFFER, off_cur); } state_dirty = 1; break; }
            unsigned c = fill_col >> 16, cyc = oth_h >> 20 & 3;
            unsigned col = cyc == 3 ? ((c >> 11 & 31) * 255 / 31) << 24 | ((c >> 6 & 31) * 255 / 31) << 16 | ((c >> 1 & 31) * 255 / 31) << 8 | 255 : prim_col;
            if (cyc >= 2) { lrx += 1; lry += 1; }
            /* P35b: in 1/2-cycle mode the RDP draws a fill rectangle through the combiner and blender, with no
             * shade and no texture coefficients (shade 0, s = t = 0): the boot screen's fade quad (TEXEL0 x ENV,
             * FORCE_BL alpha blend) covered the frame in opaque prim colour before */
            { static int nfr = -1; if (nfr < 0) nfr = port_flag("nofillrect");   /* diagnostic: skip them */
              if (cyc < 2 && nfr) break; }
            if (ws_opt) { ws_calc(); if (ws_on) rect_ext = ws_rect_edges(ulx, lrx); }   /* P350: fills reach the canvas / view edge */
            if (cyc < 2) { (void)col; rect(ulx, uly, lrx, lry, 0, 0, 0, 0, 0, 2); }
            else rect(ulx, uly, lrx, lry, 0, 0, 0, 0, col, 1);
            break;
        }
        case 0xF7: fill_col = w1; break;
        case 0xF8: fog_col = w1; state_dirty = 1; break;
        case 0xF9: blend_col = w1; state_dirty = 1; break;
        case 0xFA: prim_col = w1; prim_lod = w0 & 0xFF; state_dirty = 1; break;
        case 0xFB: env_col = w1; state_dirty = 1; break;
        case 0xFC: combine_w0 = w0 & 0xFFFFFF; combine_w1 = w1; state_dirty = 1; break;
        case 0xFD:                                            /* G_SETTIMG */
            timg.fmt = w0 >> 21 & 7; timg.siz = w0 >> 19 & 3; timg.width = (w0 & 0xFFF) + 1; timg.raw = w1;
            /* Conker texture ids (small values with no segment, e.g. 0x00000ED0 / 0x00400ED0) are
             * patched by the engine before submission; left raw they read a placeholder pattern. */
            timg.p = (w1 & ~0x00400000u) < 0x10000 || (w1 < 0x10000000u && (gfx_tex_unresolved_segs >> (w1 >> 24) & 1)) ? 0 : gfx_addr(w1);
            if (!timg.p) gfx_stats.tex_ids++;
            if (off_on && timg.p && timg.p == gfx_addr(off_addr)) off_writeback();   /* P137: texture = render target */
            hx_settimg();                                                           /* P335: a frame kept at canvas resolution */
            if (timg.p && fbc_clock && (!hx_src.kind || hx_src.kind == 4)) fbc_check_timg(timg.p);   /* P161: texture = an earlier frame (P349: kind 4 too) */
            if (timg.width >= 256 && fbc_logging()) port_log("[p161] task %u: SETTIMG %08X -> %p width %u siz %u\n", gfx_stats.tasks, w1, (void *)timg.p, timg.width, timg.siz);
            break;
        case 0xFE: zimg_addr = w1; break;
        case 0xFF: {
            if (hfr_mode == 2) { hfr_setcimg(w0, w1); break; }   /* P351: a replay draws the screen only */
            static int nooff = -1; if (nooff < 0) nooff = port_flag("p137nooff");
            unsigned w = (w0 & 0xFFF) + 1;
            static int nozc = -1; if (nozc < 0) nozc = port_flag("p161nozc");
            int off = gl_ok && !nooff && !gfx_measure_only && w >= 16 && w < 320 && w <= 256 && w1 != zimg_addr && gfx_addr(w1);
            if (gl_ok && !nooff && !nozc && !gfx_measure_only && w1 == zimg_addr && w >= 16 && w <= 320 && (w0 >> 19 & 3) == 2 && gfx_addr(w1)) off = 1;   /* P161 */
            hx_end();   /* P335 */
            if (off_on && (!off || w1 != off_addr)) off_end();
            cimg_addr = w1; cimg_width = w; if (cimg_width < 64 && !off) cimg_width = 320;   /* P140: !off (16..63 wide offscreen images keep their width) */
            if (off && !off_on) off_begin(w1, w, w0 >> 19 & 3);
            if (fbc_off < 0) fbc_off = port_flag("p161nofb");
            if (fbc_logging()) port_log("[p161] task %u: SETCIMG %08X -> %p width %u siz %u (z %08X, off %d)\n", gfx_stats.tasks, w1, gfx_addr(w1), w, w0 >> 19 & 3, zimg_addr, off);
            if (!off && w >= 256 && w1 != zimg_addr && (w0 >> 19 & 3) == 2 && gl_ok && !gfx_measure_only && !hx_disabled() && fbc_task_p &&
                gfx_addr(w1) && gfx_addr(w1) != fbc_task_p && !hx_is_screen(gfx_addr(w1)))
                hx_begin(gfx_addr(w1), w);                                      /* P335: a second full-frame image (ghost) */
            else if (!off && w >= 256 && w1 != zimg_addr && (w0 >> 19 & 3) == 2) {   /* P161: the screen image of this task */
                if (!fbc_task_p) fbc_restore(gfx_addr(w1));
                fbc_task_p = gfx_addr(w1); fbc_task_w = w;
                { static unsigned n; static unsigned char *last[4]; int k, seen = 0; for (k = 0; k < 4; k++) seen |= last[k] == fbc_task_p;
                  if (!seen && n < 4) { last[n++] = fbc_task_p; port_log("[p161] screen colour image %08X -> %p, %u wide (frame %u)\n", w1, (void *)fbc_task_p, w, port_frame_count); } }
            }
            break;
        }
        default: unknown(op, w0, w1); break;
        }
    }
    if (guard >= 1000000) port_log("[gfx] display list did not end after 1M commands (last pc %p)\n", (void *)pc);
    flush();
}

void gfx_bounds_reset(void) { bany = 0; }
int gfx_bounds(float mn[3], float mx[3]) {
    memcpy(mn, bmin, sizeof bmin); memcpy(mx, bmax, sizeof bmax);
    return bany;
}

void gfx_frame_begin(float r, float g, float b) {
    mtx_ident(mv); mtx_ident(proj); mtx_ident(mp); mtx_ident(proj_game); mtx_ident(mp_game); mvsp = 0;
    segset = 0; geom = 0; oth_h = oth_l = 0; tex_on = 0;
    normal_base = 0; memset(nbuf, 0, sizeof nbuf);
    /* lights persist in DMEM across tasks on the N64 only until the ucode reloads its data; without any light
     * command in this task the ambient is white (unlit look, as before P35) */
    memset(lbuf, 0, sizeof lbuf); light_nls = 0; light_dirty = 1; light_seen = 0;
    lbuf[0x90] = lbuf[0x91] = lbuf[0x92] = 0xFF;   /* M = 0: ambient = record 1 */
    memcpy(rare10, rare10_def, sizeof rare10);
    state_dirty = 1; rect_mode = 0; nbatch = 0; proj_persp = 0;
    gfx_stats.frames++;
    sc_on = 0;
    if (!gl_ok) return;
    glDisable(GL_SCISSOR_TEST);
    glViewport(0, 0, canvas_w, canvas_h);
    glDepthMask(GL_TRUE);
    glClearColor(r, g, b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void gfx_frame_end(void) { flush(); }

/* P58: a diagnostic drawn after the game's frame DL (p58_model.c ?p58pose, gfx_demo.c gfx_pose_overlay_draw); it
 * starts with gfx_overlay_begin(): pending triangles drawn, no scissor, depth cleared */
void (*gfx_post_task_hook)(void);
void gfx_overlay_begin(void) {
    flush();
    sc_on = 0; rect_mode = 0; state_dirty = 1;
    if (!gl_ok) return;
    glDisable(GL_SCISSOR_TEST);
    glDepthMask(GL_TRUE);
    glClear(GL_DEPTH_BUFFER_BIT);
}

/* The RSP gfx task (OSTask in game memory): t.data_ptr is the display list. Field offsets of
 * OSTask_t: type 0, flags 4, ucode_boot 8, ucode_boot_size 12, ucode 16, ucode_size 20,
 * ucode_data 24, ucode_data_size 28, dram_stack 32, dram_stack_size 36, output_buff 40,
 * output_buff_size 44, data_ptr 48, data_size 52, yield_data_ptr 56, yield_data_size 60. */
static __attribute__((noinline)) void gfx_run_task_body(void *task);   /* P350: was gfx_run_task; noinline: its frame must lie below the scrubbed stack pointer */
/* P350: the renderer runs on the game thread that submits the task (the RCP scheduler's fiber), and its stack frames
 * leave bytes below that thread's stack pointer. The online state hash covers whole fiber stacks (pc_nethash.c), and
 * game C reads stale stack bytes as uninitialised locals, so what the renderer does (an option such as Widescreen or
 * Hi-res 2D on one player's side) must not show there: the GFX_SCRUB bytes below the stack pointer are saved before the
 * task and put back after it, as if the renderer had used no stack. ?p350noscrub=1 turns it off (old behaviour). */
#include <emscripten/stack.h>
#define GFX_SCRUB (64 * 1024)
static unsigned char gfx_scrub_buf[GFX_SCRUB];
void gfx_run_task(void *task) {
    int off = ws_flag(0, "p350noscrub");
    hfr_mode = 0; hfr_drop = 0;   /* P351: a game task (never left in replay mode, even after a trap in one) */
    uintptr_t sp = emscripten_stack_get_current(), end = emscripten_stack_get_end();
    size_t n = sp > end ? sp - end : 0;
    if (n > GFX_SCRUB) n = GFX_SCRUB;
    unsigned char *lo = (unsigned char *)(sp - n);
    if (!off) memcpy(gfx_scrub_buf, lo, n);
    gfx_run_task_body(task);
    if (!off) memcpy(lo, gfx_scrub_buf, n);
}
static __attribute__((noinline)) void gfx_run_task_body(void *task) {
    const unsigned char *t = task;
    unsigned ucode = rd32(t + 16), data = rd32(t + 48), size = rd32(t + 52);
    if (hfr_mode == 2) {   /* P351: a replay of the newest game frame (hfr_replay): the drawing part only */
        const void *dl = gfx_addr(data);
        if (!dl) return;
        int sv_trace = gfx_trace, sv_p78 = p78_on, sv_p158 = p158_on, sv_dlog = draw_log, sv_p61 = p61_depth, sv_log = p351_logn;
        gfx_trace = p78_on = p158_on = draw_log = 0; p61_depth = -1; p351_logn = 0;
        gfx_frame_begin(0, 0, 0);
        ws_tag = 0; cur_ucode = ucode; cur_udata = rd32(t + 24);
        dmem_seed(rd32(t + 24), rd32(t + 28));
        gfx_run_dl(dl);
        ws_tag = 0; hfr_drop = 0;
        hx_task_end(); fbc_task_p = 0;
        gfx_frame_end();
        gfx_trace = sv_trace; p78_on = sv_p78; p158_on = sv_p158; draw_log = sv_dlog; p61_depth = sv_p61; p351_logn = sv_log;
        return;
    }
    gfx_stats.tasks++;
    vi_view_update(); /* P147 */
    if (gfx_stats.tasks <= 4)
        port_log("[gfx] task %u: ucode %08X ucode_data %08X dl %08X (%u bytes)\n", gfx_stats.tasks, ucode, rd32(t + 24), data, size);
    const void *dl = gfx_addr(data);
    if (!dl) { gfx_stats.bad_addr++; return; }
    /* P19: per-frame statistics (first 6 tasks, then every 120th): commands, triangles, unknown ops */
    unsigned c0 = gfx_stats.cmds, t0 = gfx_stats.tris, u0 = gfx_stats.unknown_ops, d0 = gfx_stats.dls;
    int logf = gfx_stats.tasks <= 6 || gfx_stats.tasks % 120 == 0;
    static int dltrace = -1, dlstat = -1;
    if (dltrace < 0) { dltrace = port_flag("dltrace"); dlstat = port_flag("dlstat"); }
    /* P23: ?dltrace=N dumps every command of gfx task N too; ?dlstat=N logs the opcode histogram every N tasks */
    gfx_trace = gfx_stats.tasks <= 2 || (dltrace && gfx_stats.tasks == (unsigned)dltrace);
    { /* P147 ?dltracef=F: trace the first gfx task at or after retrace F (task numbers differ from run to run) */
        static int tf = -1, done; if (tf < 0) tf = port_flag("dltracef");
        if (tf > 0 && !done && port_frame_count >= (unsigned)tf) { done = 1; gfx_trace = 1; port_log("[p147] dltracef: task %u at frame %u\n", gfx_stats.tasks, port_frame_count); } }
    if (p78_task < 0) p78_task = port_flag("p78tex");
    p78_on = p78_task > 0 && gfx_stats.tasks == (unsigned)p78_task; p78_mat = 0; p193_idx = 0;
    { /* P158 DIAGNOSTIC ?p158f=F[,?p158f2=F2]: the p78 material / texel dump plus the draw log (and texture-load lines) of the
       * first gfx task at or after retrace F (and F2): task numbers differ from run to run */
        static int f1 = -1, f2, d1, d2; if (f1 < 0) { f1 = port_flag("p158f"); f2 = port_flag("p158f2"); }
        int hit = 0;
        if (f1 > 0 && !d1 && port_frame_count >= (unsigned)f1) d1 = hit = 1;
        else if (f2 > 0 && !d2 && port_frame_count >= (unsigned)f2) d2 = hit = 1;
        if (hit) { p78_on = 1; p78_ntex = 0; /* P189: each p158 dump gets its own 60-texture budget */
                   port_log("[p158] dump: task %u at frame %u\n", gfx_stats.tasks, port_frame_count); }
        p158_on = hit; }
    if (dlstat && gfx_stats.tasks % (unsigned)dlstat == 0) logf = 2;
    { static int done; int f = ws_flag(1, "p350log");   /* P350 DIAGNOSTIC */
      ws_log_on = f > 0 && !done && port_frame_count >= (unsigned)f; if (ws_log_on) done = 1; }
    memset(fr_ops, 0, sizeof fr_ops); memset(fr_seguse, 0, sizeof fr_seguse);
    freecam_update();
    { static int dlg = -1; if (dlg < 0) dlg = port_flag("drawlog"); draw_log = (dlg && gfx_stats.tasks == (unsigned)dlg) || p158_on; }
    gfx_bounds_reset();
    gfx_frame_begin(0, 0, 0);
    ws_tag = 0;   /* P350 */
    cur_ucode = ucode; cur_udata = rd32(t + 24);
    if (port_flag("udump") && gfx_stats.tasks == 10) {   /* P35b ?udump=1: hex dump of the task ucode text + data */
        const unsigned char *a = gfx_addr(ucode), *d = gfx_addr(cur_udata);
        unsigned ts = 0x1800, ds = rd32(t + 28);
        port_log("[udump] text size 0x%X data size 0x%X\n", ts, ds);
        for (int w = 0; w < 2 && a && d; w++) { const unsigned char *q = w ? d : a; unsigned n = w ? ds : ts; 
            for (unsigned o = 0; o < n; o += 32) { char b[80]; int m = 0;
                for (unsigned k = 0; k < 32; k++) m += snprintf(b + m, sizeof b - m, "%02X", vbe_ld8(q + o + k));
                port_log("[udump] %c %04X %s\n", w ? 'D' : 'T', o, b); } }
    }
    dmem_seed(rd32(t + 24), rd32(t + 28));   /* P35b: DMEM data image (lights, Rare block) */
    if (p61_flag < 0) p61_flag = port_flag("p61model");
    p61_mtx = p61_dl = p61_tris = p61_verts = p61_imtx = p61_bad = p61_cmds = p61_vbad = 0; p61_depth = -1; p61_pend = 0;
    memset(p61_icls, 0, sizeof p61_icls); p61_mn[0] = p61_mn[1] = 1e30f; p61_mx[0] = p61_mx[1] = -1e30f;
    { static int f = -1, left = 3; if (f < 0) f = port_flag("p351log");
      p351_logn = f > 0 && port_frame_count >= (unsigned)f && left > 0 ? left-- : 0;
      if (p351_logn) { char a[24]; p351_cls(dl, a); port_log("[p351] task %u frame %u dl %s size %u\n", gfx_stats.tasks, port_frame_count, a, size); } }
    extern int port_photo_sandbox;   /* P348: photo frames are not game frames */
    int hfr_rec = hfr_opt && gl_ok && !gfx_measure_only && !port_photo_sandbox;   /* P351: record this game frame */
    double hfr_t0 = hfr_rec ? emscripten_get_now() : 0;
    if (hfr_rec) hfr_frame_begin(); else if (port_photo_sandbox) hfr_frames = 0;
    gfx_run_dl(dl);
    if (hfr_rec) { hfr_frame_end(task); hfr_st.t_task += emscripten_get_now() - hfr_t0; }
    {   /* P350: the wide copies of this task's display-list buffer are used up */
        unsigned len;
        ws_tag = 0;
        if (ws_sub_n || ws_mark_n)
            for (int i = 0; i < 2; i++) {
                const unsigned char *b = gfx_dl_buffer(i, &len);
                if (b && (const unsigned char *)dl >= b && (const unsigned char *)dl < b + len) {
                    ws_sub_drop_range(b, b + len); ws_mark_drop_range(b, b + len); }
            }
    }
    if (off_on) off_end();   /* P137 */
    hx_task_end();           /* P335 */
    fbc_task_end();          /* P161 */
    if (p61_flag && p61_mtx && (++p61_frames <= (unsigned)p61_flag || p61_frames % 256 == 0))
        port_log("[p61] task %u: model G_MTX %u, sub-DLs %u: %u commands, %u vertices, %u triangles, inner G_MTX %u "
                 "(K0 %u wasm %u seg %u phys %u), bad/unset addresses %u, NDC x %.2f..%.2f y %.2f..%.2f (%u verts w<=0/NaN)\n",
                 gfx_stats.tasks, p61_mtx, p61_dl, p61_cmds, p61_verts, p61_tris, p61_imtx, p61_icls[0], p61_icls[1],
                 p61_icls[2], p61_icls[3], p61_bad, p61_mn[0], p61_mx[0], p61_mn[1], p61_mx[1], p61_vbad);
    if (gfx_post_task_hook) gfx_post_task_hook();
    gfx_frame_end();
    if (draw_log && gl_ok) { /* P33: sample the framebuffer on a 5 x 5 grid (RGBA) */
        unsigned char px[4]; char b[512]; int n = 0;
        for (int gy = 0; gy < 5; gy++) for (int gx = 0; gx < 5; gx++) {
            glReadPixels(canvas_w * (2 * gx + 1) / 10, canvas_h * (2 * gy + 1) / 10, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px);
            n += snprintf(b + n, sizeof b - n, " %02X%02X%02X%02X", px[0], px[1], px[2], px[3]);
        }
        port_log("[draw] pixels (bottom row first):%s glError %X\n", b, glGetError());
    }
    draw_log = 0;
    if (bany) { memcpy(fbmin, bmin, sizeof bmin); memcpy(fbmax, bmax, sizeof bmax); fbany = 1; }
    gfx_trace = 0;
    { /* P123 ?p123tri=N: every N tasks (and on a zero/non-zero change) the game frame, commands and triangles of the task */
        static int ptri = -1, lastz = -1; extern unsigned port_frame_count;
        if (ptri < 0) ptri = port_flag("p123tri");
        unsigned nt = gfx_stats.tris - t0; int z = nt == 0;
        if (ptri > 0 && (gfx_stats.tasks % (unsigned)ptri == 0 || z != lastz))
            port_log("[p123] task %u frame %u: %u commands, %u triangles, %u sub-DLs\n", gfx_stats.tasks, port_frame_count,
                     gfx_stats.cmds - c0, nt, gfx_stats.dls - d0);
        lastz = z;
    }
    if (logf)
        port_log("[gfx] frame %u: %u DLs, %u commands, %u triangles, %u unknown commands; culldl %u (%u culled), branch_z %u (%u taken), lit %u, unlit-flag %u\n", gfx_stats.tasks,
                 gfx_stats.dls - d0, gfx_stats.cmds - c0, gfx_stats.tris - t0, gfx_stats.unknown_ops - u0,
                 gfx_stats.culldl, gfx_stats.culled, gfx_stats.branchz, gfx_stats.branchz_taken, gfx_stats.lit, gfx_stats.unlit_flag);
    if (logf && ws_opt) port_log("[p350] widescreen k %.3f: wide copies added %u, used %u, stale %u, live %d, arena at %u words\n", ws_game_k(),
                                 ws_sub_stats[0], ws_sub_stats[1], ws_sub_stats[2], ws_sub_n, ws_arena_pos);
    if (logf) {  /* P23: opcode histogram and segment use of this frame */
        char b[1024]; int n = 0;
        for (int i = 0; i < 256 && n < (int)sizeof b - 32; i++)
            if (fr_ops[i]) n += snprintf(b + n, sizeof b - n, " %02X:%u", i, fr_ops[i]);
        n += snprintf(b + n, sizeof b - n, " | seg refs");
        for (int i = 0; i < 16 && n < (int)sizeof b - 32; i++)
            if (fr_seguse[i]) n += snprintf(b + n, sizeof b - n, " %X:%u%s", i, fr_seguse[i], (segset >> i & 1) || !i ? "" : "(unset)");
        port_log("[gfx] frame %u ops:%s\n", gfx_stats.tasks, b);
        if (logf == 2) port_frame_probe(gfx_stats.tasks);
    }
}

/* P37: ?dlapprox=1 and the visibility-walk check, as a link-time wrapper (-Wl,--wrap=level_dl_visibility_filter, port/Makefile)
 * of the game's C level_dl_visibility_filter (game_eu_D2DB0.c, port P34; the P31 PC stand-in is gone). The level loader is the
 * game's C level_load_models (P34), so the P33 ?nolvlload flag is gone too.
 *   default: call the game C; with ?vislog=N log the first N calls: source tris (0x05: 1, 0x06: 2, 0x10-0x1F: 4 vis
 *            slots), kept tris and commands in the emitted DL, visible tri slots, and once the leaf-list check below.
 *   dlapprox: emit gSPDisplayList(dl) instead (the whole level DL, no culling; diagnostic only).
 * Game memory: words are native, bytes / halfwords go through vbe_ld8 / vbe_ld16. */
uint32_t *__real_level_dl_visibility_filter(int dl, uint32_t *gdl, unsigned char *mtx, int a3, int a4, int mask);
extern unsigned g_level_tri_vis_flags, g_level_tri_vis_flags_end, g_zone_tree; /* was D_800D3668; was D_800D3A8C; was D_800DC278 */
static int vis_tris(const uint32_t *p, const uint32_t *end, unsigned *ncmd) {
    int t = 0; unsigned n = 0;
    for (; end ? p < end : 1; p += 2, n++) {
        unsigned op = p[0] >> 24;
        if (!end && op == 0xDF) break;
        if (op == 0x05) t += 1; else if (op == 0x06) t += 2; else if (op >= 0x10 && op <= 0x1F) t += 4;
        if (n > 200000) break;
    }
    if (ncmd) *ncmd = n;
    return t;
}
/* P350 widescreen: the level geometry for the wider view (see ws_sub_add): a second run with the horizontal zoom factor
 * g_cam_zoom_factors[0] (the filter's side planes: |x'| * zoom <= depth) divided by the widening, into ws_arena, then a
 * third with the game's inputs into the game's list (the same bytes; the per-triangle visibility bytes and the zone tree's
 * bits for this view end as after the first run: the walk clears and rebuilds them from the inputs). Output <= 2 commands
 * per input command (a state flush emits each deferred command once). */
extern float g_cam_zoom_factors[2];   /* was D_800D3A00 */
static int ws_noculls(void) { return ws_flag(2, "p350noculls"); }   /* DIAGNOSTIC: no wide copies */
static __attribute__((noinline)) void ws_level_widen(int dl, uint32_t *gdl, uint32_t *r, unsigned char *mtx, int a3, int a4, int mask) {
    const uint32_t *p = (const uint32_t *)(uintptr_t)dl;
    unsigned n = 0;
    while ((p[0] >> 24) != 0xDF && n < 400000) { p += 2; n++; }
    uint32_t *buf = ws_arena_get(4 * n + 64), *we, *r2;
    if (!buf) return;
    float z0 = g_cam_zoom_factors[0];
    g_cam_zoom_factors[0] = z0 / ws_game_k();
    we = __real_level_dl_visibility_filter(dl, buf, mtx, a3, a4, mask);
    g_cam_zoom_factors[0] = z0;
    r2 = __real_level_dl_visibility_filter(dl, gdl, mtx, a3, a4, mask);
    if (r2 != r || we > buf + 4 * n + 62) { static int nl; if (nl++ < 4) port_log("[p350] level copy dropped: %p != %p or %u words\n", (void *)r2, (void *)r, (unsigned)(we - buf)); return; }
    we[0] = 0xDF000000; we[1] = 0;
    ws_sub_add(gdl, r, buf);
}
/* P350 widescreen: mesh_dl_cull_copy (world objects with +0x70 & 2, game_eu_13DC30.c) drops the triangles of a mesh whose
 * vertices are all outside the same side plane (|x'| * zoom > depth, the same zoom factor) or behind: the same three runs
 * as the level (its per-vertex flags g_mesh_vtx_cull_flags are rebuilt by every G_VTX it copies). Output <= input. */
uint32_t *__real_mesh_dl_cull_copy(int dl, uint32_t *gdl, unsigned char *mtx, int a3, int a4, int base);
static __attribute__((noinline)) void ws_mesh_widen(int dl, uint32_t *gdl, uint32_t *r, unsigned char *mtx, int a3, int a4, int base) {
    const uint32_t *p = (const uint32_t *)(uintptr_t)dl;
    unsigned n = 0;
    while ((p[0] >> 24) != 0xDF && n < 400000) { p += 2; n++; }
    uint32_t *buf = ws_arena_get(2 * n + 8), *we, *r2;
    if (!buf) return;
    float z0 = g_cam_zoom_factors[0];
    g_cam_zoom_factors[0] = z0 / ws_game_k();
    we = __real_mesh_dl_cull_copy(dl, buf, mtx, a3, a4, base);
    g_cam_zoom_factors[0] = z0;
    r2 = __real_mesh_dl_cull_copy(dl, gdl, mtx, a3, a4, base);
    if (r2 != r || we > buf + 2 * n + 6) { static int nl; if (nl++ < 4) port_log("[p350] mesh copy dropped: %p != %p or %u words\n", (void *)r2, (void *)r, (unsigned)(we - buf)); return; }
    we[0] = 0xDF000000; we[1] = 0;
    ws_sub_add(gdl, r, buf);
}
uint32_t *__wrap_mesh_dl_cull_copy(int dl, uint32_t *gdl, unsigned char *mtx, int a3, int a4, int base) {
    uint32_t *r = __real_mesh_dl_cull_copy(dl, gdl, mtx, a3, a4, base);
    if (dl && !gfx_measure_only && ws_game_k() > 1.001f && !ws_noculls()) { WS_SCRUB_SAVE(); ws_mesh_widen(dl, gdl, r, mtx, a3, a4, base); WS_SCRUB_RESTORE(); }
    return r;
}
uint32_t *__wrap_level_dl_visibility_filter(int dl, uint32_t *gdl, unsigned char *mtx, int a3, int a4, int mask) {
    static int dla = -1, vlog = -1, calls;
    uint32_t *r;
    if (dla < 0) { dla = port_flag("dlapprox"); vlog = port_flag("vislog"); }
    if (dla && dl != 0) {
        gdl[0] = 0xDE000000;
        gdl[1] = (uint32_t)dl;
        return gdl + 2;
    }
    static int npre;
    if (npre++ < vlog)
        port_log("[vis] pre %d: dl %08X gdl %08X mtx %08X mask %X vis [%08X, %08X) tree %08X\n", npre - 1, (unsigned)dl,
                 (unsigned)(uintptr_t)gdl, (unsigned)(uintptr_t)mtx, mask, g_level_tri_vis_flags, g_level_tri_vis_flags_end, g_zone_tree);
    (void)npre;
    if (g_level_tri_vis_flags_end <= g_level_tri_vis_flags || (g_level_tri_vis_flags_end - g_level_tri_vis_flags) & 7 || !g_zone_tree) {
        /* P37 GUARD (not a stand-in): the walk's inputs are missing. The visibility-byte range [g_level_tri_vis_flags, g_level_tri_vis_flags_end)
         * (EU 0x800D3A88 / 0x800D3A8C) is sized by collision_build_level_tris from collision_max_area_tris() = the largest per-area triangle
         * count g_coll_area_tri_counts[], which the still-asm collision_scan_level_dl (game_2DF70, the level-DL triangle walk) counts in
         * g_collision_area_tri_count; the node tree g_zone_tree = g_quadtree_roots[area] (func_150A4ED4) is built from those triangles.
         * With collision_scan_level_dl stubbed the range is empty, and the clear loop (a do-while, as in the asm) runs off the end
         * of memory. Do what the old stub did: emit nothing. */
        static int nlog;
        if (nlog++ < 2) port_log("[vis] skipped (inputs missing): vis [%08X, %08X) tree %08X\n", g_level_tri_vis_flags, g_level_tri_vis_flags_end, g_zone_tree);
        return gdl;
    }
    r = __real_level_dl_visibility_filter(dl, gdl, mtx, a3, a4, mask);
    if (dl && !gfx_measure_only && ws_game_k() > 1.001f && !ws_noculls()) { WS_SCRUB_SAVE(); ws_level_widen(dl, gdl, r, mtx, a3, a4, mask); WS_SCRUB_RESTORE(); }   /* P350 */
    { /* P42: the first vlog calls of every (dl, tree) pair, so the level after the boot level is logged too */
        static int lastdl, lasttree;
        if (dl != lastdl || (int)g_zone_tree != lasttree) {
            if (lastdl || lasttree) port_log("[vis] new dl/tree %08X / %08X after %d calls\n", (unsigned)dl, g_zone_tree, calls);
            lastdl = dl; lasttree = g_zone_tree; calls = 0;
        }
    }
    if (calls++ < vlog && dl) {
        unsigned nsrc, nout, nvis = 0, nb = g_level_tri_vis_flags_end - g_level_tri_vis_flags;
        int tsrc = vis_tris((const uint32_t *)(uintptr_t)dl, NULL, &nsrc);
        int tout = vis_tris((const uint32_t *)gdl, (const uint32_t *)r, &nout);
        for (unsigned i = 0; i < nb && i < 0x100000; i++) nvis += vbe_ld8((void *)(uintptr_t)(g_level_tri_vis_flags + i)) != 0;
        port_log("[vis] call %d dl %08X mask %X: src %u cmds %d tri slots; out %u cmds %d tri slots; vis bytes %u/%u\n",
                 calls - 1, (unsigned)dl, mask, nsrc, tsrc, nout, tout, nvis, nb);
        if (calls == 1) { /* P42: first G_VTX of the source DL: its first 2 vertices (x y z f | s t | rgba) */
            const uint32_t *c = (const uint32_t *)(uintptr_t)dl;
            int k;
            for (k = 0; k < 400 && (c[0] >> 24) != 0x01; k++) c += 2;
            { const uint32_t *L = (const uint32_t *)port_n64_to_wasm(0x800D9FB0u);   /* light / Vp records g_cam_lookat_bufs */
              port_log("[vis] D_800D9FB0: %08X %08X %08X %08X | %08X %08X %08X %08X | %08X %08X %08X %08X | %08X %08X %08X %08X\n",
                       L[0], L[1], L[2], L[3], L[4], L[5], L[6], L[7], L[8], L[9], L[10], L[11], L[12], L[13], L[14], L[15]); }
            if (k < 400) {
                const uint32_t *v = (const uint32_t *)(uintptr_t)c[1];
                port_log("[vis] first VTX %08X: %08X %08X %08X %08X | %08X %08X %08X %08X\n", c[1], v[0], v[1], v[2], v[3],
                         v[4], v[5], v[6], v[7]);
            }
        }
        if (calls == 1 && vlog >= 3) { /* P42: dump the emitted commands of the first call per (dl, tree) */
            const uint32_t *c;
            for (c = gdl; c < r && c < gdl + 2 * 400; c += 2)
                port_log("[vis]   out %08X %08X\n", c[0], c[1]);
        }
        if (calls == 1) { /* P34 UNVERIFIED: prev index starts at 0 (asm: the caller's $gp). It matters only when the first
                           * visible leaf of a frame starts with a relative byte (1..0x7F). Count such leaves. */
            unsigned node = g_zone_tree, leaves = 0, rel = 0, nodes = 0, firstrel = 0, ents = 0, maxents = 0;
            while (node && nodes < 100000) {
                int ch = (int16_t)vbe_ld16((void *)(uintptr_t)(node + 0xC)), off;
                nodes++;
                if (ch) { node += ch; continue; }
                leaves++;
                { unsigned b0 = vbe_ld8((void *)(uintptr_t)(node + 0xE)), q = node + 0xE, e = 0, b;
                  if (b0 && b0 < 0x80) { if (!rel) firstrel = node; rel++; }
                  /* P42: leaf list length (halfword | 0x8000 or a 1-byte delta, 0 ends) */
                  while ((b = vbe_ld8((void *)(uintptr_t)q)) != 0 && e < 100000) { q += (b & 0x80) ? 2 : 1; e++; }
                  ents += e; if (e > maxents) maxents = e; }
                off = (int16_t)vbe_ld16((void *)(uintptr_t)(node + 4));
                if (!off) break;
                node += off;
            }
            port_log("[vis] tree %08X: %u nodes, %u leaves, %u leaves start with a relative index (first %08X); "
                     "leaf entries %u (max %u per leaf); pool counters (all areas) nodes %d leaves %d\n", g_zone_tree, nodes, leaves, rel, firstrel, ents, maxents,
                     *(const int *)port_n64_to_wasm(0x800B11DCu), *(const int *)port_n64_to_wasm(0x800B11E0u));
        }
    }
    return r;
}

/* P39: ?camwatch=N: write watch on the camera chain, checked at every asm-stub entry (port_stub_hit) and around
 * every camera_build_view_matrix call (-Wl,--wrap). Watched: the camera target g_player_views[0]+0x3D4 (= g_objects[0]+0x31C)
 * +0x130..+0x154 (dir / eye / at), the controller's smoothed target 0x2A4..0x2AC, at 0x2BC..0x2C4, eye
 * 0x2F8..0x300, orbit 0x18C..0x198 and yaw 0x3A0, and the followed record (+0x3D0) position +0x14..+0x1C.
 * The first N changes are logged with the stub (or wrapper point) that saw them and a JS stack; camera_build_view_matrix
 * calls are counted, and its inputs / outputs are logged at the first call and every 64th. */
#define CW_N 36
extern unsigned port_frame_count;
void port_js_stack(int skip, int n);
extern unsigned g_player_views; /* was D_800DBFF0 */
static unsigned cw_prev[CW_N], cw_have, cw_logged, cw_calls;
static int cw_flag = -1;
static int cw_snap(unsigned *v) {
    const unsigned char *p = (const unsigned char *)g_player_views, *o, *r;
    int i, n = 0;
    if (!p) return 0;
    o = *(const unsigned char *const *)(p + 0x3D4);
    r = *(const unsigned char *const *)(p + 0x3D0);
    /* P99: the obj / rec pointers can be stale or garbage (a death); reading them trapped (memory access out of bounds) */
    if ((unsigned)o < 0x1000 || (unsigned)o > 0x15FF0000) o = 0;
    if ((unsigned)r < 0x1000 || (unsigned)r > 0x15FF0000) r = 0;
    for (i = 0; i < 10; i++) v[n++] = o ? *(const unsigned *)(o + 0x130 + i * 4) : 0;   /* 0..9 */
    for (i = 0; i < 3; i++) v[n++] = *(const unsigned *)(p + 0x2A4 + i * 4);            /* 10..12 */
    for (i = 0; i < 3; i++) v[n++] = *(const unsigned *)(p + 0x2BC + i * 4);            /* 13..15 */
    for (i = 0; i < 3; i++) v[n++] = *(const unsigned *)(p + 0x2F8 + i * 4);            /* 16..18 */
    for (i = 0; i < 4; i++) v[n++] = *(const unsigned *)(p + 0x18C + i * 4);            /* 19..22 */
    v[n++] = *(const unsigned *)(p + 0x3A0);                                            /* 23 */
    for (i = 0; i < 3; i++) v[n++] = r ? *(const unsigned *)(r + 0x14 + i * 4) : 0;     /* 24..26 */
    v[n++] = (unsigned)o; v[n++] = (unsigned)r; v[n++] = *(const unsigned *)(p + 0x2C); /* 27..29 */
    while (n < CW_N) v[n++] = 0;
    return 1;
}
static const char *cw_name(int i) {
    static const char *nm[] = {"obj+130 dir.x", "obj+134 dir.y", "obj+138 dir.z", "obj+13C eye.x", "obj+140 eye.y",
        "obj+144 eye.z", "obj+148 at.x", "obj+14C at.y", "obj+150 at.z", "obj+154", "cam+2A4", "cam+2A8", "cam+2AC",
        "cam+2BC at.x", "cam+2C0 at.y", "cam+2C4 at.z", "cam+2F8 eye.x", "cam+2FC eye.y", "cam+300 eye.z", "cam+18C",
        "cam+190", "cam+194", "cam+198", "cam+3A0 yaw", "rec+14 x", "rec+18 y", "rec+1C z", "cam+3D4 obj",
        "cam+3D0 rec", "cam+2C mode"};
    return i < 30 ? nm[i] : "?";
}
void port_camwatch(const char *where) {
    unsigned v[CW_N];
    int i;
    if (cw_flag < 0) cw_flag = port_flag("camwatch");
    if (!cw_flag) return;
    { /* first hit of the camera-path stubs: who calls them */
        static const char *const who[] = {"obj_state_walk", "camera_update_target", "camera_update_eye_orbit", "camera_dispatch_mode", "camera_update_target_height",
                                          "camera_update_transition", "camera_update_aim_mode"};
        static unsigned seen;
        for (i = 0; i < (int)(sizeof who / sizeof who[0]); i++)
            if (!(seen & (1u << i)) && !strcmp(where, who[i])) {
                seen |= 1u << i;
                port_log("[camwatch] first %s, frame %u, stack:\n", where, port_frame_count);
                port_js_stack(3, 8);
            }
    }
    if (!cw_snap(v)) return;
    if (cw_have && cw_logged < (unsigned)cw_flag) {
        for (i = 0; i < CW_N; i++)
            if (v[i] != cw_prev[i]) {
                cw_logged++;
                port_log("[camwatch] #%u frame %u at %s: %s %08X -> %08X (%g)\n", cw_logged, port_frame_count, where,
                          cw_name(i), cw_prev[i], v[i], *(float *)&v[i]);
                if (cw_logged <= 8) port_js_stack(2, 8);
            }
    }
    for (i = 0; i < CW_N; i++) cw_prev[i] = v[i];
    cw_have = 1;
}
void __real_camera_build_view_matrix(void *arg0);
void music_play_song(int, int, int);
void __wrap_camera_build_view_matrix(void *arg0) {
    { /* P99 DIAGNOSTIC ?p99snd=F: at frame >= F start sound 0x15 once through the game's own entry (the floor-material
       * ambient loop obj_surface_effects_update starts), to tell "no sound requested" from "audio path broken" */
        static int sf = -1, done = 0;
        if (sf < 0) sf = port_flag("p99snd");
        if (sf > 0 && !done && port_frame_count >= (unsigned)sf) { done = 1; music_play_song(0x15, 0, 0); }
    }
    if (cw_flag < 0) cw_flag = port_flag("camwatch");
    if (cw_flag) {
        port_camwatch("camera_build_view_matrix entry");
        if (cw_calls == 0) { port_log("[camwatch] first camera_build_view_matrix(%08X) call, stack:\n", (unsigned)arg0); port_js_stack(1, 10); }
    }
    __real_camera_build_view_matrix(arg0);
    if (cw_flag) {
        unsigned v[CW_N];
        static int every = -1; /* P44: ?camevery=N logs the summary line every N calls (default 64) */
        if (every < 0) { every = port_flag("camevery"); if (every <= 0) every = 64; }
        port_camwatch("camera_build_view_matrix exit");
        if (cw_calls % (unsigned)every == 0 && cw_snap(v))
            port_log("[camwatch] camera_build_view_matrix call %u frame %u: mode %08X rec %08X pos %g %g %g | cam 2A4 %g %g %g at %g %g %g eye %g %g %g "
                      "orbit 18C %g 190 %g 194 %g 198 %g yaw %g | obj %08X eye %g %g %g at %g %g %g\n", cw_calls, port_frame_count,
                      v[29], v[28], *(float *)&v[24], *(float *)&v[25], *(float *)&v[26], *(float *)&v[10], *(float *)&v[11],
                      *(float *)&v[12], *(float *)&v[13], *(float *)&v[14], *(float *)&v[15], *(float *)&v[16], *(float *)&v[17],
                      *(float *)&v[18], *(float *)&v[19], *(float *)&v[20], *(float *)&v[21], *(float *)&v[22], *(float *)&v[23],
                      v[27], *(float *)&v[3], *(float *)&v[4], *(float *)&v[5], *(float *)&v[6], *(float *)&v[7], *(float *)&v[8]);
        if (cw_calls % (unsigned)every == 0 && g_player_views) { /* P46: the eye-height state of P43's camera_update_eye_height / camera_update_eye_base */
            const unsigned char *c = (const unsigned char *)g_player_views;
#define CWF(o) (*(const float *)(c + (o)))
            port_log("[camwatch]   height: 344 dy %g 348 h %g 354 base %g 360 water %g 364 %g 6F0 %g 6F4 %g | 84 %08X 5F0 %08X "
                     "920 %08X 92C %08X 23C %02X 7F4 %08X 5CC %g 384 %g\n", CWF(0x344), CWF(0x348), CWF(0x354), CWF(0x360),
                     CWF(0x364), CWF(0x6F0), CWF(0x6F4), *(const unsigned *)(c + 0x84), *(const unsigned *)(c + 0x5F0),
                     *(const unsigned *)(c + 0x920), *(const unsigned *)(c + 0x92C), c[0x23C ^ 3], *(const unsigned *)(c + 0x7F4),
                     CWF(0x5CC), CWF(0x384));
#undef CWF
        }
        if ((cw_calls & 63) == 0 && v[28]) { /* P39: the object array g_objects[] (EU 0x800CC6F0, 0x32C each): pos, +0x31C */
            int k;
            for (k = 0; k < 8; k++) {
                const unsigned char *r = (const unsigned char *)v[28] + k * 0x32C;
                port_log("[camwatch]   obj[%d] %08X pos %g %g %g +31C %08X w0 %08X w4 %08X\n", k, (unsigned)r,
                         *(const float *)(r + 0x14), *(const float *)(r + 0x18), *(const float *)(r + 0x1C),
                         *(const unsigned *)(r + 0x31C), *(const unsigned *)r, *(const unsigned *)(r + 4));
            }
        }
    }
    cw_calls++;
}

/* P39: ?p38check=N runtime checks of the P38 C (link-time wraps; N = how many calls to log in detail).
 *  - shadow_draw_all (shadows): opcode histogram of what it appends to the frame DL (VTX 01, TRI1 05, TRI2 06,
 *    Rare TRI4 10..1F, DL / ENDDL), and per call the triangle slots per vertex load (the strip splitter output).
 *  - objects_run_state_handlers (per-frame object update): g_cur_pad after the call, and whether it is left pointing into
 *    the dead stack frame (the 6-byte buffer used for objects >= 4).
 *  - camera_view_test_sphere (view test): every call is checked against an independent double-precision version of the
 *    asm (c.ule / c.olt / c.ult NaN rules, cvt.w.s round-to-nearest-even), with an exit histogram. */
static int p38_flag = -1;
static int p38_on(void) { if (p38_flag < 0) p38_flag = port_flag("p38check"); return p38_flag; }
uint8_t *__real_shadow_draw_all(uint8_t *gdl, int arg1);
/* P158 DIAGNOSTIC ?p158null=1: character_spawn_handlers char_fx_init (game_eu_17A800) dispatches g_char_fx_init_fns handlers by
 * the indices of character_handler_indices char_fx_handler_indices (C, side-effect free). Logs the call when the null zone word
 * null+0x14 changes across it (the 0x400 written at the new-game scene start, frame 4560), with the indices / handlers. */
/* P161 ?p161fix=1 test wrap of record_start_dispatch removed in P171: port-b P164 passes the record in the game C. */
int __real_char_fx_init(void *arg0);
int char_fx_handler_indices(void *arg0, int *outSub, int *outMode, int *outType);
int __wrap_char_fx_init(void *arg0) {
    static int on = -1; static unsigned logged;
    if (on < 0) on = port_flag("p158null");
    if (on <= 0) return __real_char_fx_init(arg0);
    unsigned before = *(volatile unsigned *)(uintptr_t)0x14;
    int sub = -1, mode = -1, type = -1, fl = char_fx_handler_indices(arg0, &sub, &mode, &type);
    int r = __real_char_fx_init(arg0);
    unsigned after = *(volatile unsigned *)(uintptr_t)0x14;
    if ((before != after || logged < 6) && logged < 40) {
        extern unsigned char g_char_fx_type_table[], g_char_fx_mode_table[], g_objects[]; extern unsigned g_char_fx_init_fns[]; extern unsigned char g_char_fx_mode_tables[];
        int vt = (fl & 4) ? vbe_ld8(g_char_fx_type_table + type) : -1, vm = (fl & 2) ? vbe_ld8(g_char_fx_mode_table + mode) : -1;
        logged++;
        port_log("[p158null] frame %u obj %d ret %d flags %d sub %d mode %d type %d -> handler idx type %d (%08X) mode %d (%08X) | null+0x14 %08X -> %08X\n",
                 port_frame_count, (int)(((unsigned char *)arg0 - g_objects) / 0x32C), r, fl, sub, mode, type,
                 vt, vt >= 0 ? g_char_fx_init_fns[vt] : 0, vm, vm >= 0 ? g_char_fx_init_fns[vm] : 0, before, after);
        (void)g_char_fx_mode_tables;
    }
    return r;
}
/* P158 DIAGNOSTIC ?p158light=N: every Nth call of shadow_light_projection shadow_light_projection (game_eu_1B1ED0): object, slot,
 * the returned light distance, the slot's smoothed light position g_shadow_light_pos[slot], the object position and the default
 * light direction g_shadow_light_dir (why the shadow streak is long). */
float __real_shadow_light_projection(int obj, int slot, float sx, float sy, float sz, float prev);
float __wrap_shadow_light_projection(int obj, int slot, float sx, float sy, float sz, float prev) {
    static int n = -1; static unsigned calls, logged;
    float r = __real_shadow_light_projection(obj, slot, sx, sy, sz, prev);
    if (n < 0) n = port_flag("p158light");
    static int from = -1; if (from < 0) from = port_flag("p158f");
    if (n > 0 && port_frame_count >= (unsigned)from && calls++ % (unsigned)n == 0 && logged < 400) {
        extern float g_shadow_light_pos[][3], g_shadow_light_dir[3], g_shadow_proj_scale[2], g_shadow_far_depth, g_shadow_near_depth, g_shadow_world_scale; extern int g_shadow_no_point_lights;
        extern unsigned char g_objects[];
        const float *o = (const float *)(g_objects + obj * 0x32C + 0x14);
        logged++;
        port_log("[p158light] frame %u obj %d slot %d box %.1f %.1f %.1f prev %.1f -> dist %.1f | light %.1f %.1f %.1f obj %.1f %.1f %.1f "
                 "| default %.1f %.1f %.1f nolights %d scale %.3f | proj %.3f %.3f far %.1f near %.1f\n",
                 port_frame_count, obj, slot, sx, sy, sz, prev, r, g_shadow_light_pos[slot & 7][0], g_shadow_light_pos[slot & 7][1], g_shadow_light_pos[slot & 7][2],
                 o[0], o[1], o[2], g_shadow_light_dir[0], g_shadow_light_dir[1], g_shadow_light_dir[2], g_shadow_no_point_lights, g_shadow_world_scale, g_shadow_proj_scale[0], g_shadow_proj_scale[1],
                 g_shadow_far_depth, g_shadow_near_depth);
    }
    return r;
}
uint8_t *__wrap_shadow_draw_all(uint8_t *gdl, int arg1) {
    static unsigned calls, tot_vtx, tot_t1, tot_t2, tot_t4, tot_cmd, tot_other;
    static int p137 = -1;
    if (p137 < 0) p137 = port_flag("p137noshadow");
    if (p137 > 0) return gdl; /* P137 DIAGNOSTIC ?p137noshadow=1: skip the object shadow DL (render-to-texture pass) */
    uint8_t *r = __real_shadow_draw_all(gdl, arg1);
    if (p38_on()) {
        unsigned vtx = 0, t1 = 0, t2 = 0, t4 = 0, other = 0, n = 0, slots = 0, maxslots = 0;
        const uint32_t *w;
        char seq[160]; int sl = 0;
        seq[0] = 0;
        for (w = (const uint32_t *)gdl; (const uint8_t *)w < r && n < 100000; w += 2, n++) {
            unsigned op = w[0] >> 24;
            if (op == 0x01) { vtx++; if (slots > maxslots) maxslots = slots;
                              if (slots && sl < 140) sl += snprintf(seq + sl, sizeof seq - sl, "%u ", slots); slots = 0; }
            else if (op == 0x05) { t1++; slots += 1; }
            else if (op == 0x06) { t2++; slots += 2; }
            else if (op >= 0x10 && op <= 0x1F) { t4++; slots += 4; }
            else other++;
        }
        if (slots && sl < 140) sl += snprintf(seq + sl, sizeof seq - sl, "%u", slots);
        if (calls % 128 == 0) { /* why objects are skipped: the filter fields of objects 0..1 (vbe bytes: address ^ 3) */
            extern unsigned char g_objects[]; extern unsigned g_shadow_skip_players;
            int k;
            for (k = 0; k < 2; k++) {
                const unsigned char *o = g_objects + k * 0x32C;
                #define VB(off) (*(const unsigned char *)((uintptr_t)(o + (off)) ^ 3))
                unsigned t31c = *(const unsigned *)(o + 0x31C);
                port_log("[shadow] obj[%d]: state %d 1D4 %08X 74 %02X 5 %02X 66 %02X 84 %04X 65 %02X id %02X 31C %08X (95 %02X 98 %02X) mask DF510 %08X\n",
                         k, *(const int *)o, *(const unsigned *)(o + 0x1D4), VB(0x74), VB(5), VB(0x66),
                         *(const unsigned short *)((uintptr_t)(o + 0x84) ^ 2), VB(0x65), VB(4), t31c,
                         t31c ? *(const unsigned char *)((uintptr_t)(t31c + 0x95) ^ 3) : 0,
                         t31c ? *(const unsigned char *)((uintptr_t)(t31c + 0x98) ^ 3) : 0, g_shadow_skip_players);
                #undef VB
            }
        }
        calls++; tot_vtx += vtx; tot_t1 += t1; tot_t2 += t2; tot_t4 += t4; tot_cmd += n; tot_other += other;
        if (calls <= (unsigned)p38_flag || (n > 1 && calls % 256 == 0))
            port_log("[shadow] call %u frame %u arg1 %d: %u cmds (VTX %u TRI1 %u TRI2 %u TRI4 %u other %u), tri slots per VTX: %s\n",
                     calls, port_frame_count, arg1, n, vtx, t1, t2, t4, other, seq);
        if (calls % 64 == 0)
            port_log("[shadow] totals after %u calls: %u cmds, VTX %u TRI1 %u TRI2 %u TRI4 %u other %u\n", calls, tot_cmd,
                     tot_vtx, tot_t1, tot_t2, tot_t4, tot_other);
    }
    return r;
}
extern unsigned g_cur_pad; /* was D_800CC6A4 */
void __real_objects_run_state_handlers(void);
void __wrap_objects_run_state_handlers(void) {
    static unsigned calls, stack_left;
    volatile unsigned char here = 0;
    unsigned before = g_cur_pad, after, sp = (unsigned)(uintptr_t)&here;
    __real_objects_run_state_handlers();
    { extern void p340_probe(void); p340_probe(); }   /* P340 ?p340=F multiplayer pickup probe */
    after = g_cur_pad;
    if (p38_on()) {
        int in_stack = after < sp && sp - after < 0x10000; /* below our frame = the callee's dead frame */
        calls++;
        if (in_stack) stack_left++;
        if (calls <= (unsigned)p38_flag || (in_stack && stack_left <= 4) || calls % 512 == 0)
            port_log("[a730] call %u frame %u: D_800CC6A4 %08X -> %08X (sp %08X)%s; left in the dead stack %u of %u calls\n",
                     calls, port_frame_count, before, after, sp, in_stack ? " DEAD STACK" : "", stack_left, calls);
    }
}
extern float g_cam_near_plane; /* was D_800D9F40 */
int __real_camera_view_test_sphere(int cam, int *mtx, float x, float y, float z, float r, float ry, float far);
static int v6840_ref(int cam, const float *m, float x, float y, float z, float r, float ry, float far, int *exitno) {
    /* the asm order and grouping, in float (every product / sum rounded to f32 as on the FPU) */
    const float *c = (const float *)(uintptr_t)cam;
    float u, v, w, t;
    w = (float)((float)(m[2] * x) + (float)(m[6] * y)) + (float)((float)(m[10] * z) + m[14]);
    if (!(w - r <= -g_cam_near_plane)) { *exitno = 0; return 0; }
    if (w + r < -far) { *exitno = 1; return 0; }
    u = (float)((float)(m[0] * x) + (float)(m[4] * y)) + (float)((float)(m[8] * z) + m[12]);
    t = (float)(u * c[0x88 / 4]) + (float)(w * c[0x90 / 4]); if (!(t >= -r)) { *exitno = 2; return 0; }
    t = (float)(u * c[0x94 / 4]) + (float)(w * c[0x9C / 4]); if (!(t >= -r)) { *exitno = 3; return 0; }
    v = (float)((float)(m[1] * x) + (float)(m[5] * y)) + (float)((float)(m[9] * z) + m[13]);
    t = (float)(v * c[0xA4 / 4]) + (float)(w * c[0xA8 / 4]); if (!(t >= -ry)) { *exitno = 4; return 0; }
    t = (float)(v * c[0xB0 / 4]) + (float)(w * c[0xB4 / 4]); if (!(t >= -ry)) { *exitno = 5; return 0; }
    *exitno = 6;
    { int k = (int)lrintf(w); return k ? k : 1; }
}
int __wrap_camera_view_test_sphere(int cam, int *mtx, float x, float y, float z, float r, float ry, float far) {
    static unsigned calls, bad, ex[7];
    int got = __real_camera_view_test_sphere(cam, mtx, x, y, z, r, ry, far);
    if (p38_on()) {
        int e, want = v6840_ref(cam, (const float *)mtx, x, y, z, r, ry, far, &e);
        calls++; ex[e]++;
        if (got != want) {
            bad++;
            if (bad <= 8) port_log("[view6840] MISMATCH call %u: cam %08X m %08X p (%g %g %g) r %g ry %g far %g: C %d, reference %d\n",
                                   calls, cam, (unsigned)(uintptr_t)mtx, x, y, z, r, ry, far, got, want);
        }
        if (calls <= (unsigned)p38_flag)
            port_log("[view6840] call %u frame %u: cam %08X p (%g %g %g) r %g ry %g far %g -> %d (exit %d)\n", calls,
                     port_frame_count, cam, x, y, z, r, ry, far, got, e);
        if (calls % 1024 == 0 || calls == 64)
            port_log("[view6840] %u calls, %u mismatches; exits near %u far %u planes %u %u %u %u inside %u\n", calls, bad,
                     ex[0], ex[1], ex[2], ex[3], ex[4], ex[5], ex[6]);
    }
    return got;
}

/* P46: ?p46check=N runtime checks of P43's frame-DL C (link-time wraps; N = how many calls to log in detail).
 *  - objects_draw_pass (object list draw; calls the now-C obj_draw_part per object part): commands it appends per mode.
 *  - texscroll_update (texture scrolling): the g_texscroll_tail list, scroll position (+0xE / +0x10) and speed (+0x12 / +0x13). */
static int p46_flag = -1;
extern unsigned char g_objects[], g_cutscene_in_progress, g_cutscene_show_all_objs; /* was D_800CC2D0; was D_800C3638; was D_800C3A7A */
int obj_get_player_alpha(void *rec, int part);
static unsigned p46_bdc0_calls, p46_bdc0_cmds[4], p46_bdc0_n[4], p46_6560_calls;
void *__real_objects_draw_pass(void *gdl, int mode, short player);
void *__wrap_objects_draw_pass(void *gdl, int mode, short player) {
    void *r;
    if (p46_flag < 0) p46_flag = port_flag("p46check");
    r = __real_objects_draw_pass(gdl, mode, player);
    if (p46_flag) {
        unsigned d = (unsigned)((char *)r - (char *)gdl) / 8, k = (unsigned)mode & 3;
        p46_bdc0_cmds[k] += d; p46_bdc0_n[k]++;
        if (p46_bdc0_calls < (unsigned)p46_flag || (p46_bdc0_calls & 255) == 0) {
            const unsigned char *r0 = g_objects;
            port_log("[p46] objects_draw_pass #%u frame %u mode %d player %d: %u commands appended | rec0 state %u id %02X "
                     "unk5 %02X +74 %02X +1D4 %08X +1C8 %02X alpha(obj_get_player_alpha) %d | D_800C3638 %u D_800C3A7A %u\n",
                     p46_bdc0_calls, port_frame_count, mode, player, d, *(const unsigned *)r0, vbe_ld8(r0 + 4),
                     vbe_ld8(r0 + 5), vbe_ld8(r0 + 0x74), *(const unsigned *)(r0 + 0x1D4), vbe_ld8(r0 + 0x1C8),
                     obj_get_player_alpha((void *)r0, player), vbe_ld8(&g_cutscene_in_progress), vbe_ld8(&g_cutscene_show_all_objs));
        }
        if ((p46_bdc0_calls & 1023) == 1023)
            port_log("[p46] objects_draw_pass %u calls: mode1 %u calls %u cmds, mode2 %u calls %u cmds, other %u calls %u cmds\n",
                     p46_bdc0_calls + 1, p46_bdc0_n[1], p46_bdc0_cmds[1], p46_bdc0_n[2], p46_bdc0_cmds[2],
                     p46_bdc0_n[0] + p46_bdc0_n[3], p46_bdc0_cmds[0] + p46_bdc0_cmds[3]);
    }
    p46_bdc0_calls++;
    return r;
}
extern unsigned g_texscroll_tail; /* was D_800E0D18 */
int __real_texscroll_update(int a0, int a1);
int __wrap_texscroll_update(int a0, int a1) {
    int r;
    if (p46_flag < 0) p46_flag = port_flag("p46check");
    r = __real_texscroll_update(a0, a1);
    if (p46_flag && (p46_6560_calls < (unsigned)p46_flag || (p46_6560_calls & 255) == 0)) {
        const unsigned char *e = (const unsigned char *)g_texscroll_tail;
        int n = 0;
        port_log("[p46] texscroll_update #%u frame %u (DLs %08X %08X):\n", p46_6560_calls, port_frame_count, a0, a1);
        while (e && n < 6) {
            port_log("[p46]   ent %08X pos %u %u size %u %u speed %d %d levels %u\n", (unsigned)e, vbe_ld16(e + 0xE),
                     vbe_ld16(e + 0x10), vbe_ld16(e + 0xA), vbe_ld16(e + 0xC), (signed char)vbe_ld8(e + 0x12),
                     (signed char)vbe_ld8(e + 0x13), vbe_ld8(e + 0x14));
            e = *(const unsigned char *const *)(e + 4);
            n++;
        }
        if (!n) port_log("[p46]   (list empty)\n");
    }
    p46_6560_calls++;
    return r;
}
