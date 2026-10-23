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
#include "gfx.h"
#include "../ultra/pc_mem.h"

void port_log(const char *fmt, ...);

GfxStats gfx_stats;
int gfx_measure_only;
unsigned gfx_tex_unresolved_segs; /* viewer: segments whose textures the engine would resolve */

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
/* P137: offscreen colour image (render to texture, e.g. the P130 object shadow pass: SETCIMG RGBA16 64 wide).
 * While on, draws go to an FBO of cimg_width x cimg_width N64 pixels (1:1) and the canvas is that size; the FBO is
 * written back to RDRAM in the image's pixel size (8-bit: the red byte, as the RDP's 8-bit colour images; 16-bit:
 * RGBA5551 big-endian; 32-bit: RGBA8888) when the game loads the target as a texture (SETTIMG) and when
 * the colour image switches back / the task ends. Before P137 the renderer drew such passes onto the screen,
 * scaled as a 64-wide frame (white screen + black shadow polygons). ?p137nooff=1 turns it off (old behaviour). */
static int off_on, off_saved_w, off_saved_h;
static unsigned off_addr, off_w, off_fbo_w, off_siz, off_rows;
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
    u_primlod, u_acmp, u_mode, u_texon, u_filt, u_lod, u_pixscale, u_bl1, u_bl2, u_blfin, u_k45, u_primz, u_cvg;
static int gl_ok, canvas_w = 640, canvas_h = 480;
#define VF 11
#define BATCH_TRIS 4096
static float batch[BATCH_TRIS * 3 * VF];
static int nbatch;      /* vertices in batch */
static int state_dirty = 1;
static int rect_mode;   /* 0 tris, 1 fill rect, 2 tex rect (screen-space quads) */
static unsigned k4k5;   /* G_SETCONVERT K4 (bits 9..17) / K5 (bits 0..8) */

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
    "uniform ivec4 uC0, uC1, uA0, uA1, uBl1, uBl2, uLod; uniform int u2cyc, uAcmp, uMode, uTexOn, uFilt, uBlFin, uCvg;\n"
    "uniform vec4 uPrim, uEnv, uFogC, uBlendC; uniform vec2 uK45; uniform float uPrimLod, uPixScale, uPrimZ;\n"
    "out vec4 frag;\n"
    "vec4 T0, T1, SH; float LF;\n"
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
    "  SH = vCol; LF = 0.0;\n"
    "  gl_FragDepth = uPrimZ >= 0.0 ? uPrimZ : gl_FragCoord.z;\n"
    "  if (uMode == 1) { frag = vCol; return; }\n"
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
    "  T0 = samp(lt);\n"
    "  T1 = !distant && (uTexOn & (2 << lt)) != 0 ? samp(lt + 1) : T0;\n"
    "  if (uMode == 3) { if (T0.a < 0.5) discard; frag = vec4(T0.rgb, 1.0); return; }\n"
    "  vec3 c = vec3(0.0); float a = 0.0;\n"
    "  vec3 c1 = (cA(uC0.x, c) - cB(uC0.y, c)) * cC(uC0.z, c, a) + cD(uC0.w, c);\n"
    "  float a1 = (aX(uA0.x, a) - aX(uA0.y, a)) * aC(uA0.z, a) + aX(uA0.w, a);\n"
    "  if (u2cyc == 1) { c = clamp(c1, 0.0, 1.0); a = clamp(a1, 0.0, 1.0);\n"
    "    c1 = (cA(uC1.x, c) - cB(uC1.y, c)) * cC(uC1.z, c, a) + cD(uC1.w, c);\n"
    "    a1 = (aX(uA1.x, a) - aX(uA1.y, a)) * aC(uA1.z, a) + aX(uA1.w, a); }\n"
    "  c1 = clamp(c1, 0.0, 1.0); a1 = clamp(a1, 0.0, 1.0);\n"
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
    U(u_bl1, "uBl1"); U(u_bl2, "uBl2"); U(u_blfin, "uBlFin"); U(u_k45, "uK45"); U(u_primz, "uPrimZ"); U(u_cvg, "uCvg");
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

/* ---- textures: decode a tile out of TMEM into RGBA8, cached by (TMEM generation, tile params) */
typedef struct { unsigned key[6]; GLuint tex; } TexEnt;
static TexEnt tcache[256];
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
    if (t->siz != 3 && (y & 1)) a ^= 4;
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

static GLuint tex_for(int ti, unsigned *w, unsigned *h) {
    const Tile *t = &tiles[ti & 7];
    tile_dims(t, w, h);
    if ((size_t)*w * *h * 4 > sizeof texbuf) *h = sizeof texbuf / 4 / *w;
    unsigned key[6] = {tmem_gen, t->fmt | t->siz << 4 | t->pal << 8 | (oth_h >> 14 & 3) << 20,
                       t->tmem | t->line << 12, *w | *h << 16, 0, 2};
    unsigned hsh = (key[0] * 2654435761u ^ key[1] * 40503u ^ key[2] * 97u ^ key[3]) & 255;
    TexEnt *e = &tcache[hsh];
    if (e->tex && !memcmp(e->key, key, sizeof key)) return e->tex;
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
    return e->tex;
}

static float shiftscale(unsigned sh) { return sh == 0 ? 1.0f : sh <= 10 ? 1.0f / (1 << sh) : (float)(1 << (16 - sh)); }

static void rgba(GLint u, unsigned c) {
    glUniform4f(u, (c >> 24) / 255.0f, (c >> 16 & 255) / 255.0f, (c >> 8 & 255) / 255.0f, (c & 255) / 255.0f);
}

static float sc_box[4];   /* P35b: scissor in N64 pixels (ulx, uly, lrx, lry) */
static int sc_on;
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

static void apply_state(void) {
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
    glUniform1i(u_cvg, (oth_l & 0x2000) ? ((oth_l & 0x4000) ? 2 : 1) : 0); /* ALPHA_CVG_SEL: coverage from alpha */
    /* P144: CVG_X_ALPHA + CLR_ON_CVG without FORCE_BL (e.g. the logo-end iris, func_15180AF0 / func_1518010C: black
     * combiner, I8 lens alpha): coverage = pixel coverage * alpha and the colour is written only on coverage
     * overflow, so texels with low alpha leave the framebuffer alone (approximated as "discard below 0.5"). Before,
     * the whole lens square was drawn opaque black. ?p144nocvgx=1 restores the old behaviour. */
    { static int nx = -1; if (nx < 0) nx = port_flag("p144nocvgx");
      if (!nx && !(oth_l & 0x2000) && (oth_l & 0x1080) == 0x1080 && !(oth_l & 0x4000)) glUniform1i(u_cvg, 1); }
    int mode = rect_mode == 1 || cyc == 3 ? 1 : cyc == 2 ? 3 : 0;
    glUniform1i(u_mode, mode);
    int texon = 0;
    if (mode != 1 && (tex_on || rect_mode == 2)) {
        /* tiles base .. base+3: TEXEL1 of 2-cycle mode and the LOD levels (G_TL_LOD, tex_level) */
        int ntile = cyc == 1 ? 2 : 1, lod = (oth_h & 0x10000) && cyc == 1 && rect_mode == 0;
        if (lod) ntile = (int)tex_level + 2 > 6 ? 6 : (int)tex_level + 2;   /* P78: up to 6 tiles (levels 0..4 + 1) */
        for (int k = 0; k < ntile; k++) {
            unsigned w, h;
            int ti = (tex_tile + k) & 7;
            glActiveTexture(GL_TEXTURE0 + k);
            glBindTexture(GL_TEXTURE_2D, tex_for(ti, &w, &h));
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
    glUniform1i(u_texon, texon);
    unsigned tf = oth_h >> 12 & 3;   /* G_TF_POINT 0, G_TF_BILERP 2, G_TF_AVERAGE 3 */
    glUniform1i(u_filt, tf == 0 || cyc >= 2 ? 0 : filt_mode);
    { static int ol = -1; if (ol < 0) ol = port_flag("p78oldlod");   /* DIAGNOSTIC ?p78oldlod=1: the pre-P78 (inverted) scale */
      glUniform1f(u_pixscale, ol ? (float)cimg_width / canvas_w : (float)canvas_w / cimg_width); }   /* P78: canvas px per N64 px */
    { static int lv = -1; if (lv < 0) lv = port_flag("p78lodviz"); glUniform1i(u_lodviz, lv); }
    { static int sp = -1; if (sp < 0) sp = port_flag("p78split"); glUniform1f(u_splitx, sp ? canvas_w / 2.0f : -1.0f); }
    /* depth: Z_CMP / Z_UPD; ZMODE (bits 10-11) DEC -> polygon offset (the RDP's z-delta compare) */
    int zcmp = (geom & G_ZBUFFER) && (oth_l & 0x10) && rect_mode == 0, zupd = (oth_l & 0x20) && rect_mode == 0;
    if (zcmp || zupd) { glEnable(GL_DEPTH_TEST); glDepthFunc(zcmp ? GL_LEQUAL : GL_ALWAYS); } else glDisable(GL_DEPTH_TEST);
    glDepthMask(zupd ? GL_TRUE : GL_FALSE);
    if ((oth_l >> 10 & 3) == 3) { glEnable(GL_POLYGON_OFFSET_FILL); glPolygonOffset(-1, -2); }
    else glDisable(GL_POLYGON_OFFSET_FILL);
    blend_state(cyc, mode);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE);  /* the blend factor goes through alpha; keep the canvas opaque */
    /* viewport */
    float sx = canvas_w / (float)cimg_width, sy = canvas_h / CIMG_H;
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
    port_log("[draw] %d verts (%d w<=0) rm %d ndc x %.2f..%.2f y %.2f..%.2f z %.3f..%.3f | geom %06X oth %06X/%08X cc %06X/%08X tex %d tile %d prim %08X env %08X fog %08X v0 rgba %.2f %.2f %.2f %.2f st %.1f %.1f fog %.2f\n",
             nbatch, behind, rect_mode, x0, x1, y0, y1, z0, z1, geom, oth_h, oth_l, combine_w0, combine_w1, tex_on, tex_tile,
             prim_col, env_col, fog_col, o[4], o[5], o[6], o[7], o[8], o[9], o[10]);
}
/* P78: ?p78tex=N: per-material dump of gfx task N (node too: no GL needed). At each state change before
 * triangles: othermode, combiner, G_TEXTURE, the tiles base..base+4 (fmt siz line tmem pal cm mask shift, tile
 * size in texels), and once per distinct (TMEM generation, tile) the decoded texels as hex rows
 * ([p78hex], port/tools/p78tex.py turns them into PNGs). At the flush: the batch's texel density in N64 pixels
 * per axis (|ds/dx| etc. from each triangle's screen-space gradients, tile 0 units): what the RDP's LOD sees. */
static int p78_task = -1, p78_on, p78_mat, p78_ntex;
static void p78_material(void) {
    if (!p78_on || !tex_on) return;
    p78_mat++;
    port_log("[p78] mat %d: oth %06X/%08X cc %06X/%08X tex lvl %u tile %u on %u sc %.4f %.4f prim %08X env %08X lodfrac %02X\n",
             p78_mat, oth_h, oth_l, combine_w0, combine_w1, tex_level, tex_tile, tex_on, tex_sc_s, tex_sc_t, prim_col, env_col, prim_lod);
    unsigned nt = tex_level + 2; if (nt > 6) nt = 6;
    for (unsigned k = 0; k < nt; k++) {
        const Tile *t = &tiles[(tex_tile + k) & 7];
        port_log("[p78]   tile %u: fmt %u siz %u line %u tmem %03X pal %u cms %u cmt %u mask %u/%u shift %u/%u ul %.2f %.2f lr %.2f %.2f\n",
                 (tex_tile + k) & 7, t->fmt, t->siz, t->line, t->tmem, t->pal, t->cms, t->cmt, t->masks, t->maskt, t->shifts,
                 t->shiftt, t->uls / 4.0, t->ult / 4.0, t->lrs / 4.0, t->lrt / 4.0);
        static unsigned seen[256][3]; static unsigned nseen;
        unsigned key0 = tmem_gen, key1 = t->tmem | t->line << 12 | t->siz << 24 | t->fmt << 28, key2 = t->masks | t->maskt << 4 | t->pal << 8;
        int dup = 0;
        for (unsigned j = 0; j < nseen; j++) if (seen[j][0] == key0 && seen[j][1] == key1 && seen[j][2] == key2) dup = 1;
        if (dup || nseen >= 256 || p78_ntex >= 60) continue;
        seen[nseen][0] = key0; seen[nseen][1] = key1; seen[nseen][2] = key2; nseen++;
        unsigned w, h; tile_dims(t, &w, &h);
        if (w > 64 || h > (w <= 8 ? 256u : 64u)) continue;   /* P94: narrow gradient strips (sky 4x256) too */
        p78_ntex++;
        port_log("[p78hex] T%d mat %d tile %u %ux%u\n", p78_ntex, p78_mat, (tex_tile + k) & 7, w, h);
        for (unsigned y = 0; y < h; y++) {
            char b[64 * 8 + 1]; int m = 0;
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
    if (draw_log && nbatch) draw_log_line();
    if (nbatch) p78_density();
    if (!nbatch || !gl_ok) { nbatch = 0; return; }
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

/* P61 ?p61model=N: the game's own model DL. func_1502CFEC (port P57 C) emits, per visible sub-DL k of a model,
 * G_MTX (MV load) D_800C42B8 + G_DL D_800C48A8[model][k]. Its G_MTX word is `&D_800C42B8 & 0x1FFFFFFF` like the asm's
 * physical D_C42B8; in wasm the label is a mirror address (< 0x20000000), so the mask keeps it and gfx_addr takes the
 * wasm class; a true N64 physical value (< 8 MB) takes the segment-0 / RDRAM-mirror class. That G_MTX word marks the
 * model DL: the next G_DL is a model sub-DL, and everything below it (until it returns) is counted here. */
extern unsigned char D_800C42B8[] __attribute__((weak));   /* weak: sched_demo links the renderer without the game */
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
    need_state(0);
    put(a, 1, 1); put(b, 1, 1); put(c, 1, 1);   /* P35: the tile shift is applied per tile in the shader */
}

/* P137: offscreen colour image helpers (see off_on) */
static GLuint off_fbo, off_tex;
static void off_writeback(void) {
    static unsigned char px[256 * 256 * 4];
    unsigned char *dst = gfx_addr(off_addr);
    unsigned w = off_w, h = off_rows, x, y;
    flush();
    if (!dst || w > 256 || h == 0 || h > OFF_FBO_H) return;
    glReadPixels(0, OFF_FBO_H - h, w, h, GL_RGBA, GL_UNSIGNED_BYTE, px);
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
    if (!off_fbo || off_fbo_w != w) {
        if (!off_fbo) { glGenFramebuffers(1, &off_fbo); glGenTextures(1, &off_tex); }
        glBindTexture(GL_TEXTURE_2D, off_tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, OFF_FBO_H, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, off_fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, off_tex, 0);
        off_fbo_w = w;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, off_fbo);
    off_saved_w = canvas_w; off_saved_h = canvas_h;
    canvas_w = w; canvas_h = OFF_FBO_H;
    off_on = 1; off_addr = addr; off_w = w; off_siz = siz; off_rows = w; state_dirty = 1;
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

/* screen-space rectangle in N64 pixels (fill / texture rectangles) */
static void rect(float x0, float y0, float x1, float y1, float s0, float t0, float s1, float t1, unsigned col, int rm) {
    need_state(rm);
    float W = cimg_width, H = CIMG_H;
    V q[4];
    float xs[4] = {x0, x1, x0, x1}, ys[4] = {y0, y0, y1, y1}, ss[4] = {s0, s1, s0, s1}, ts[4] = {t0, t0, t1, t1};
    for (int i = 0; i < 4; i++) {
        q[i].x = xs[i] / W * 2 - 1; q[i].y = 1 - (ys[i] - VI_Y0) / H * 2; q[i].z = 0; q[i].w = 1;
        q[i].r = (col >> 24) / 255.0f; q[i].g = (col >> 16 & 255) / 255.0f; q[i].b = (col >> 8 & 255) / 255.0f;
        q[i].a = (col & 255) / 255.0f; q[i].s = ss[i]; q[i].t = ts[i]; q[i].fog = 0;
    }
    put(&q[0], 1, 1); put(&q[1], 1, 1); put(&q[2], 1, 1);
    put(&q[1], 1, 1); put(&q[3], 1, 1); put(&q[2], 1, 1);
}

/* ------------------------------------------------------------------ RSP commands */
/* Conker lighting (P14, rewritten in P35 from the ROM's F3DEX2 lighting overlay).
 * The RSP code is the overlay at text offset 0x1188 (0x388 bytes, IMEM 0x12D8) of the gfx ucodes in the
 * ROM table D_80084408 (text ROM 0x2D810 + 0x4560, data + 0x10460; P35.md section 2). DMEM layout from
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
    {   /* P42 DIAGNOSTIC ?lvlwhite=1: the level's start colour (record M) is func_1515DE84's `arg8` = the colour that the
         * still-asm func_1515E7E8 should write into its uninitialised local `col`; with the stub it is stack garbage
         * (P39: a green tint, P42: 000000 = a black level). The flag makes a black BG start colour white. */
        static int lw = -1;
        if (lw < 0) lw = port_flag("lvlwhite");
        /* P44: ?lvlwhite=2 forces white for any BG start colour (the stack garbage can be a dim green, not 000000) */
        if (lw && light_bg && (lw >= 2 || (!amb[0] && !amb[1] && !amb[2]))) c[0] = c[1] = c[2] = 1.0f;
        /* P46: ?lvlcol=N logs the first N changes of the BG start colour (P43: func_1515E7E8 is C and fills it) */
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
    if (p78_on && tex_on) {   /* P78: raw Vtx records (x y z flag s t rgba) of the dumped task */
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
    if (timg.siz == 0) bytes = (lrs - uls + 2) >> 1;
    if (dst + bytes > 4096) bytes = 4096 - dst;
    const unsigned char *src = timg.p ? timg.p + ((((ult * timg.width + uls) << timg.siz) >> 1)) : 0;
    for (unsigned i = 0; i < bytes; i++)
        tmem[dst + i] = src ? vbe_ld8(src + i) : (unsigned char)(((i >> 3) ^ (i >> 8)) & 1 ? 0x30 + (timg.raw & 0x7F) : 0xC0 - (timg.raw & 0x3F));
    for (unsigned k = 0; k * 8 < bytes; k++)
        if (((k * dxt) >> 11) & 1 && timg.siz != 3) { /* odd line: swap the 32-bit halves */
            unsigned char *q = tmem + dst + k * 8, tmp[4];
            memcpy(tmp, q, 4); memcpy(q, q + 4, 4); memcpy(q + 4, tmp, 4);
        }
    tmem_gen++;
    state_dirty = 1;
}

static void load_tile(unsigned w0, unsigned w1) {
    Tile *t = &tiles[w1 >> 24 & 7];
    unsigned x0 = (w0 >> 12 & 0xFFF) >> 2, y0 = (w0 & 0xFFF) >> 2, x1 = (w1 >> 12 & 0xFFF) >> 2, y1 = (w1 & 0xFFF) >> 2;
    unsigned stride = t->line * 8 * (timg.siz == 3 ? 2 : 1);
    unsigned rowb = timg.siz == 0 ? (x1 - x0 + 2) >> 1 : (x1 - x0 + 1) << (timg.siz - 1);
    for (unsigned y = y0; y <= y1 && (y - y0) * stride < 4096; y++) {
        const unsigned char *src = timg.p ? timg.p + (((y * timg.width + x0) << timg.siz) >> 1) : 0;
        for (unsigned i = 0; i < rowb && i < 4096; i++) {
            unsigned a = t->tmem * 8 + (y - y0) * stride + i;
            if (timg.siz != 3 && ((y - y0) & 1)) a ^= 4;
            tmem[a & 0xFFF] = src ? vbe_ld8(src + i) : (unsigned char)((((i >> 1) ^ (y >> 2)) & 1) ? 0xF0 : 0x40);
        }
    }
    t->uls = w0 >> 12 & 0xFFF; t->ult = w0 & 0xFFF; t->lrs = w1 >> 12 & 0xFFF; t->lrt = w1 & 0xFFF;
    tmem_gen++;
    state_dirty = 1;
}

static void load_tlut(unsigned w0, unsigned w1) {
    Tile *t = &tiles[w1 >> 24 & 7];
    unsigned n = ((w1 >> 14 & 0x3FF) - (w0 >> 14 & 0x3FF)) + 1, dst = t->tmem * 8;
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

void gfx_run_dl(const void *dl) {
    const unsigned char *stack[32], *pc = dl;
    int sp = 0, guard = 0;
    gfx_stats.dls++;
    while (pc && ++guard < 1000000) {
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
            if (a1 > 63) a1 = 63;
            for (unsigned i = a0; i <= a1; i++) {
                const V *v = &vb[i];
                unsigned c = (v->x < -v->w) | (v->x > v->w) << 1 | (v->y < -v->w) << 2 | (v->y > v->w) << 3 |
                             (v->w <= 0) << 4 | (v->z > v->w) << 5;
                all &= c;
            }
            gfx_stats.culldl++;
            if (all && a0 <= a1) { gfx_stats.culled++; pc = sp ? stack[--sp] : 0;
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
            if (v->w > 0 && z16 <= (double)(int)w1) {
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
            if (p61_flag && D_800C42B8 && w1 == ((unsigned)(uintptr_t)D_800C42B8 & 0x1FFFFFFF)) {   /* P61: func_1502CFEC's G_MTX */
                p61_mtx++; p61_pend = 1;
                if (!p61_mark++) {
                    port_log("[p61] first model G_MTX %08X %08X at %p (task %u): resolves to %p, &D_800C42B8 %p (%s)\n", w0, w1,
                             (const void *)(pc - 8), gfx_stats.tasks, (const void *)p, (const void *)D_800C42B8,
                             p == D_800C42B8 ? "same" : "DIFFERENT");
                    for (int k = -24; k < 0; k++)   /* func_1502CFEC's setup before it */
                        port_log("[p61]   %p: %08X %08X\n", (const void *)(pc - 8 + 8 * k), rd32(pc - 8 + 8 * k), rd32(pc - 4 + 8 * k));
                }
            } else if (p61_depth >= 0) p61_icls[p61_cls(w1)]++, p61_imtx++;
            if (!p) { gfx_stats.bad_addr++; break; }
            unsigned prm = (w0 & 0xFF) ^ 1;                  /* ^ G_MTX_PUSH */
            float m[4][4];
            mtx_read(m, p);
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
            if (w1 == 0) { /* P55: G_DL 0 only comes from an asm stub that returned a NULL DL (func_150900F0 draws
                            * D_800D29A8 = stub func_1518C900(0xB8)); RDRAM 0 is code, running it crashed the renderer */
                static int logged;
                gfx_stats.bad_addr++;
                if (!logged++) port_log("[gfx] G_DL to address 0 at %p skipped (a stub returned a NULL display list)\n", (const void *)(pc - 8));
                break;
            }
            { unsigned *e = dl_ring[dl_ring_n++ & 7]; e[0] = (unsigned)(uintptr_t)(pc - 8); e[1] = w0; e[2] = w1; }
            if (p61_pend && p61_depth < 0) {   /* P61: a model sub-DL D_800C48A8[model][k] */
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
            unsigned h1 = rd32(pc + 4), h2 = rd32(pc + 12);
            pc += 16;
            float lrx = (w0 >> 12 & 0xFFF) / 4.0f, lry = (w0 & 0xFFF) / 4.0f, ulx = (w1 >> 12 & 0xFFF) / 4.0f, uly = (w1 & 0xFFF) / 4.0f;
            float s = (short)(h1 >> 16) / 32.0f, t = (short)h1 / 32.0f, ds = (short)(h2 >> 16) / 1024.0f, dt = (short)h2 / 1024.0f;
            unsigned cyc = oth_h >> 20 & 3;
            if (cyc >= 2) { lrx += 1; lry += 1; if (cyc == 2) ds /= 4; }
            unsigned keep = tex_tile;
            tex_tile = w1 >> 24 & 7; state_dirty = 1;
            if (!gfx_measure_only) rect(ulx, uly, lrx, lry, s, t, s + ds * (lrx - ulx), t + dt * (lry - uly), 0xFFFFFFFF, 2);
            tex_tile = keep; state_dirty = 1;
            break;
        }
        case 0xE6: case 0xE7: case 0xE8: case 0xE9: break;   /* syncs */
        case 0xED:                                            /* G_SETSCISSOR (P35b) */
            sc_box[0] = (w0 >> 12 & 0xFFF) / 4.0f; sc_box[1] = (w0 & 0xFFF) / 4.0f;
            sc_box[2] = (w1 >> 12 & 0xFFF) / 4.0f; sc_box[3] = (w1 & 0xFFF) / 4.0f;
            sc_on = sc_box[2] > sc_box[0] && sc_box[3] > sc_box[1]; state_dirty = 1;
            if (off_on && sc_on) { unsigned r = (unsigned)(sc_box[3] + 0.75f); off_rows = r < 1 ? 1 : r > OFF_FBO_H ? OFF_FBO_H : r; }  /* P140 */
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
            if (cimg_addr && cimg_addr == zimg_addr) { flush(); if (gl_ok) { glDepthMask(GL_TRUE); glClear(GL_DEPTH_BUFFER_BIT); } state_dirty = 1; break; }
            unsigned c = fill_col >> 16, cyc = oth_h >> 20 & 3;
            unsigned col = cyc == 3 ? ((c >> 11 & 31) * 255 / 31) << 24 | ((c >> 6 & 31) * 255 / 31) << 16 | ((c >> 1 & 31) * 255 / 31) << 8 | 255 : prim_col;
            if (cyc >= 2) { lrx += 1; lry += 1; }
            /* P35b: in 1/2-cycle mode the RDP draws a fill rectangle through the combiner and blender, with no
             * shade and no texture coefficients (shade 0, s = t = 0): the boot screen's fade quad (TEXEL0 x ENV,
             * FORCE_BL alpha blend) covered the frame in opaque prim colour before */
            { static int nfr = -1; if (nfr < 0) nfr = port_flag("nofillrect");   /* diagnostic: skip them */
              if (cyc < 2 && nfr) break; }
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
            break;
        case 0xFE: zimg_addr = w1; break;
        case 0xFF: {
            static int nooff = -1; if (nooff < 0) nooff = port_flag("p137nooff");
            unsigned w = (w0 & 0xFFF) + 1;
            int off = gl_ok && !nooff && !gfx_measure_only && w >= 16 && w < 320 && w <= 256 && w1 != zimg_addr && gfx_addr(w1);
            if (off_on && (!off || w1 != off_addr)) off_end();
            cimg_addr = w1; cimg_width = w; if (cimg_width < 64 && !off) cimg_width = 320;   /* P140: !off (16..63 wide offscreen images keep their width) */
            if (off && !off_on) off_begin(w1, w, w0 >> 19 & 3);
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
    state_dirty = 1; rect_mode = 0; nbatch = 0;
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
void gfx_run_task(void *task) {
    const unsigned char *t = task;
    unsigned ucode = rd32(t + 16), data = rd32(t + 48), size = rd32(t + 52);
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
    p78_on = p78_task > 0 && gfx_stats.tasks == (unsigned)p78_task; p78_mat = 0;
    if (dlstat && gfx_stats.tasks % (unsigned)dlstat == 0) logf = 2;
    memset(fr_ops, 0, sizeof fr_ops); memset(fr_seguse, 0, sizeof fr_seguse);
    freecam_update();
    { static int dlg = -1; if (dlg < 0) dlg = port_flag("drawlog"); draw_log = dlg && gfx_stats.tasks == (unsigned)dlg; }
    gfx_bounds_reset();
    gfx_frame_begin(0, 0, 0);
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
    gfx_run_dl(dl);
    if (off_on) off_end();   /* P137 */
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

/* P37: ?dlapprox=1 and the visibility-walk check, as a link-time wrapper (-Wl,--wrap=func_150A5858, port/Makefile)
 * of the game's C func_150A5858 (game_eu_D2DB0.c, port P34; the P31 PC stand-in is gone). The level loader is the
 * game's C func_150031EC (P34), so the P33 ?nolvlload flag is gone too.
 *   default: call the game C; with ?vislog=N log the first N calls: source tris (0x05: 1, 0x06: 2, 0x10-0x1F: 4 vis
 *            slots), kept tris and commands in the emitted DL, visible tri slots, and once the leaf-list check below.
 *   dlapprox: emit gSPDisplayList(dl) instead (the whole level DL, no culling; diagnostic only).
 * Game memory: words are native, bytes / halfwords go through vbe_ld8 / vbe_ld16. */
uint32_t *__real_func_150A5858(int dl, uint32_t *gdl, unsigned char *mtx, int a3, int a4, int mask);
extern unsigned D_800D3668, D_800D3A8C, D_800DC278;
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
uint32_t *__wrap_func_150A5858(int dl, uint32_t *gdl, unsigned char *mtx, int a3, int a4, int mask) {
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
                 (unsigned)(uintptr_t)gdl, (unsigned)(uintptr_t)mtx, mask, D_800D3668, D_800D3A8C, D_800DC278);
    (void)npre;
    if (D_800D3A8C <= D_800D3668 || (D_800D3A8C - D_800D3668) & 7 || !D_800DC278) {
        /* P37 GUARD (not a stand-in): the walk's inputs are missing. The visibility-byte range [D_800D3668, D_800D3A8C)
         * (EU 0x800D3A88 / 0x800D3A8C) is sized by func_15003668 from func_15002878() = the largest per-area triangle
         * count D_800DBE18[], which the still-asm func_15001460 (game_2DF70, the level-DL triangle walk) counts in
         * D_800DBE38; the node tree D_800DC278 = D_800DBE08[area] (func_150A4ED4) is built from those triangles.
         * With func_15001460 stubbed the range is empty, and the clear loop (a do-while, as in the asm) runs off the end
         * of memory. Do what the old stub did: emit nothing. */
        static int nlog;
        if (nlog++ < 2) port_log("[vis] skipped (inputs missing): vis [%08X, %08X) tree %08X\n", D_800D3668, D_800D3A8C, D_800DC278);
        return gdl;
    }
    r = __real_func_150A5858(dl, gdl, mtx, a3, a4, mask);
    { /* P42: the first vlog calls of every (dl, tree) pair, so the level after the boot level is logged too */
        static int lastdl, lasttree;
        if (dl != lastdl || (int)D_800DC278 != lasttree) {
            if (lastdl || lasttree) port_log("[vis] new dl/tree %08X / %08X after %d calls\n", (unsigned)dl, D_800DC278, calls);
            lastdl = dl; lasttree = D_800DC278; calls = 0;
        }
    }
    if (calls++ < vlog && dl) {
        unsigned nsrc, nout, nvis = 0, nb = D_800D3A8C - D_800D3668;
        int tsrc = vis_tris((const uint32_t *)(uintptr_t)dl, NULL, &nsrc);
        int tout = vis_tris((const uint32_t *)gdl, (const uint32_t *)r, &nout);
        for (unsigned i = 0; i < nb && i < 0x100000; i++) nvis += vbe_ld8((void *)(uintptr_t)(D_800D3668 + i)) != 0;
        port_log("[vis] call %d dl %08X mask %X: src %u cmds %d tri slots; out %u cmds %d tri slots; vis bytes %u/%u\n",
                 calls - 1, (unsigned)dl, mask, nsrc, tsrc, nout, tout, nvis, nb);
        if (calls == 1) { /* P42: first G_VTX of the source DL: its first 2 vertices (x y z f | s t | rgba) */
            const uint32_t *c = (const uint32_t *)(uintptr_t)dl;
            int k;
            for (k = 0; k < 400 && (c[0] >> 24) != 0x01; k++) c += 2;
            { const uint32_t *L = (const uint32_t *)port_n64_to_wasm(0x800D9FB0u);   /* light / Vp records D_800D9FB0 */
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
            unsigned node = D_800DC278, leaves = 0, rel = 0, nodes = 0, firstrel = 0, ents = 0, maxents = 0;
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
                     "leaf entries %u (max %u per leaf); pool counters (all areas) nodes %d leaves %d\n", D_800DC278, nodes, leaves, rel, firstrel, ents, maxents,
                     *(const int *)port_n64_to_wasm(0x800B11DCu), *(const int *)port_n64_to_wasm(0x800B11E0u));
        }
    }
    return r;
}

/* P39: ?camwatch=N: write watch on the camera chain, checked at every asm-stub entry (port_stub_hit) and around
 * every func_1512C490 call (-Wl,--wrap). Watched: the camera target D_800DBFF0[0]+0x3D4 (= D_800CC2D0[0]+0x31C)
 * +0x130..+0x154 (dir / eye / at), the controller's smoothed target 0x2A4..0x2AC, at 0x2BC..0x2C4, eye
 * 0x2F8..0x300, orbit 0x18C..0x198 and yaw 0x3A0, and the followed record (+0x3D0) position +0x14..+0x1C.
 * The first N changes are logged with the stub (or wrapper point) that saw them and a JS stack; func_1512C490
 * calls are counted, and its inputs / outputs are logged at the first call and every 64th. */
#define CW_N 36
extern unsigned port_frame_count;
void port_js_stack(int skip, int n);
extern unsigned D_800DBFF0;
static unsigned cw_prev[CW_N], cw_have, cw_logged, cw_calls;
static int cw_flag = -1;
static int cw_snap(unsigned *v) {
    const unsigned char *p = (const unsigned char *)D_800DBFF0, *o, *r;
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
        static const char *const who[] = {"func_1504CB98", "func_151247C0", "func_15123A54", "func_151283B8", "func_15124C38",
                                          "func_15128030", "func_15126378"};
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
void __real_func_1512C490(void *arg0);
void func_1000D96C(int, int, int);
void __wrap_func_1512C490(void *arg0) {
    { /* P99 DIAGNOSTIC ?p99snd=F: at frame >= F start sound 0x15 once through the game's own entry (the floor-material
       * ambient loop func_1508000C starts), to tell "no sound requested" from "audio path broken" */
        static int sf = -1, done = 0;
        if (sf < 0) sf = port_flag("p99snd");
        if (sf > 0 && !done && port_frame_count >= (unsigned)sf) { done = 1; func_1000D96C(0x15, 0, 0); }
    }
    if (cw_flag < 0) cw_flag = port_flag("camwatch");
    if (cw_flag) {
        port_camwatch("func_1512C490 entry");
        if (cw_calls == 0) { port_log("[camwatch] first func_1512C490(%08X) call, stack:\n", (unsigned)arg0); port_js_stack(1, 10); }
    }
    __real_func_1512C490(arg0);
    if (cw_flag) {
        unsigned v[CW_N];
        static int every = -1; /* P44: ?camevery=N logs the summary line every N calls (default 64) */
        if (every < 0) { every = port_flag("camevery"); if (every <= 0) every = 64; }
        port_camwatch("func_1512C490 exit");
        if (cw_calls % (unsigned)every == 0 && cw_snap(v))
            port_log("[camwatch] func_1512C490 call %u frame %u: mode %08X rec %08X pos %g %g %g | cam 2A4 %g %g %g at %g %g %g eye %g %g %g "
                      "orbit 18C %g 190 %g 194 %g 198 %g yaw %g | obj %08X eye %g %g %g at %g %g %g\n", cw_calls, port_frame_count,
                      v[29], v[28], *(float *)&v[24], *(float *)&v[25], *(float *)&v[26], *(float *)&v[10], *(float *)&v[11],
                      *(float *)&v[12], *(float *)&v[13], *(float *)&v[14], *(float *)&v[15], *(float *)&v[16], *(float *)&v[17],
                      *(float *)&v[18], *(float *)&v[19], *(float *)&v[20], *(float *)&v[21], *(float *)&v[22], *(float *)&v[23],
                      v[27], *(float *)&v[3], *(float *)&v[4], *(float *)&v[5], *(float *)&v[6], *(float *)&v[7], *(float *)&v[8]);
        if (cw_calls % (unsigned)every == 0 && D_800DBFF0) { /* P46: the eye-height state of P43's func_1512E6B0 / func_1512A390 */
            const unsigned char *c = (const unsigned char *)D_800DBFF0;
#define CWF(o) (*(const float *)(c + (o)))
            port_log("[camwatch]   height: 344 dy %g 348 h %g 354 base %g 360 water %g 364 %g 6F0 %g 6F4 %g | 84 %08X 5F0 %08X "
                     "920 %08X 92C %08X 23C %02X 7F4 %08X 5CC %g 384 %g\n", CWF(0x344), CWF(0x348), CWF(0x354), CWF(0x360),
                     CWF(0x364), CWF(0x6F0), CWF(0x6F4), *(const unsigned *)(c + 0x84), *(const unsigned *)(c + 0x5F0),
                     *(const unsigned *)(c + 0x920), *(const unsigned *)(c + 0x92C), c[0x23C ^ 3], *(const unsigned *)(c + 0x7F4),
                     CWF(0x5CC), CWF(0x384));
#undef CWF
        }
        if ((cw_calls & 63) == 0 && v[28]) { /* P39: the object array D_800CC2D0[] (EU 0x800CC6F0, 0x32C each): pos, +0x31C */
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
 *  - func_15186D04 (shadows): opcode histogram of what it appends to the frame DL (VTX 01, TRI1 05, TRI2 06,
 *    Rare TRI4 10..1F, DL / ENDDL), and per call the triangle slots per vertex load (the strip splitter output).
 *  - func_1504A730 (per-frame object update): D_800CC6A4 after the call, and whether it is left pointing into
 *    the dead stack frame (the 6-byte buffer used for objects >= 4).
 *  - func_150A6840 (view test): every call is checked against an independent double-precision version of the
 *    asm (c.ule / c.olt / c.ult NaN rules, cvt.w.s round-to-nearest-even), with an exit histogram. */
static int p38_flag = -1;
static int p38_on(void) { if (p38_flag < 0) p38_flag = port_flag("p38check"); return p38_flag; }
uint8_t *__real_func_15186D04(uint8_t *gdl, int arg1);
uint8_t *__wrap_func_15186D04(uint8_t *gdl, int arg1) {
    static unsigned calls, tot_vtx, tot_t1, tot_t2, tot_t4, tot_cmd, tot_other;
    static int p137 = -1;
    if (p137 < 0) p137 = port_flag("p137noshadow");
    if (p137 > 0) return gdl; /* P137 DIAGNOSTIC ?p137noshadow=1: skip the object shadow DL (render-to-texture pass) */
    uint8_t *r = __real_func_15186D04(gdl, arg1);
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
            extern unsigned char D_800CC2D0[]; extern unsigned D_800DF510;
            int k;
            for (k = 0; k < 2; k++) {
                const unsigned char *o = D_800CC2D0 + k * 0x32C;
                #define VB(off) (*(const unsigned char *)((uintptr_t)(o + (off)) ^ 3))
                unsigned t31c = *(const unsigned *)(o + 0x31C);
                port_log("[shadow] obj[%d]: state %d 1D4 %08X 74 %02X 5 %02X 66 %02X 84 %04X 65 %02X id %02X 31C %08X (95 %02X 98 %02X) mask DF510 %08X\n",
                         k, *(const int *)o, *(const unsigned *)(o + 0x1D4), VB(0x74), VB(5), VB(0x66),
                         *(const unsigned short *)((uintptr_t)(o + 0x84) ^ 2), VB(0x65), VB(4), t31c,
                         t31c ? *(const unsigned char *)((uintptr_t)(t31c + 0x95) ^ 3) : 0,
                         t31c ? *(const unsigned char *)((uintptr_t)(t31c + 0x98) ^ 3) : 0, D_800DF510);
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
extern unsigned D_800CC6A4;
void __real_func_1504A730(void);
void __wrap_func_1504A730(void) {
    static unsigned calls, stack_left;
    volatile unsigned char here = 0;
    unsigned before = D_800CC6A4, after, sp = (unsigned)(uintptr_t)&here;
    __real_func_1504A730();
    after = D_800CC6A4;
    if (p38_on()) {
        int in_stack = after < sp && sp - after < 0x10000; /* below our frame = the callee's dead frame */
        calls++;
        if (in_stack) stack_left++;
        if (calls <= (unsigned)p38_flag || (in_stack && stack_left <= 4) || calls % 512 == 0)
            port_log("[a730] call %u frame %u: D_800CC6A4 %08X -> %08X (sp %08X)%s; left in the dead stack %u of %u calls\n",
                     calls, port_frame_count, before, after, sp, in_stack ? " DEAD STACK" : "", stack_left, calls);
    }
}
extern float D_800D9F40;
int __real_func_150A6840(int cam, int *mtx, float x, float y, float z, float r, float ry, float far);
static int v6840_ref(int cam, const float *m, float x, float y, float z, float r, float ry, float far, int *exitno) {
    /* the asm order and grouping, in float (every product / sum rounded to f32 as on the FPU) */
    const float *c = (const float *)(uintptr_t)cam;
    float u, v, w, t;
    w = (float)((float)(m[2] * x) + (float)(m[6] * y)) + (float)((float)(m[10] * z) + m[14]);
    if (!(w - r <= -D_800D9F40)) { *exitno = 0; return 0; }
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
int __wrap_func_150A6840(int cam, int *mtx, float x, float y, float z, float r, float ry, float far) {
    static unsigned calls, bad, ex[7];
    int got = __real_func_150A6840(cam, mtx, x, y, z, r, ry, far);
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
 *  - func_1502BDC0 (object list draw; calls the now-C func_1502CC64 per object part): commands it appends per mode.
 *  - func_15196560 (texture scrolling): the D_800E0D18 list, scroll position (+0xE / +0x10) and speed (+0x12 / +0x13). */
static int p46_flag = -1;
extern unsigned char D_800CC2D0[], D_800C3638, D_800C3A7A;
int func_1506196C(void *rec, int part);
static unsigned p46_bdc0_calls, p46_bdc0_cmds[4], p46_bdc0_n[4], p46_6560_calls;
void *__real_func_1502BDC0(void *gdl, int mode, short player);
void *__wrap_func_1502BDC0(void *gdl, int mode, short player) {
    void *r;
    if (p46_flag < 0) p46_flag = port_flag("p46check");
    r = __real_func_1502BDC0(gdl, mode, player);
    if (p46_flag) {
        unsigned d = (unsigned)((char *)r - (char *)gdl) / 8, k = (unsigned)mode & 3;
        p46_bdc0_cmds[k] += d; p46_bdc0_n[k]++;
        if (p46_bdc0_calls < (unsigned)p46_flag || (p46_bdc0_calls & 255) == 0) {
            const unsigned char *r0 = D_800CC2D0;
            port_log("[p46] func_1502BDC0 #%u frame %u mode %d player %d: %u commands appended | rec0 state %u id %02X "
                     "unk5 %02X +74 %02X +1D4 %08X +1C8 %02X alpha(func_1506196C) %d | D_800C3638 %u D_800C3A7A %u\n",
                     p46_bdc0_calls, port_frame_count, mode, player, d, *(const unsigned *)r0, vbe_ld8(r0 + 4),
                     vbe_ld8(r0 + 5), vbe_ld8(r0 + 0x74), *(const unsigned *)(r0 + 0x1D4), vbe_ld8(r0 + 0x1C8),
                     func_1506196C((void *)r0, player), vbe_ld8(&D_800C3638), vbe_ld8(&D_800C3A7A));
        }
        if ((p46_bdc0_calls & 1023) == 1023)
            port_log("[p46] func_1502BDC0 %u calls: mode1 %u calls %u cmds, mode2 %u calls %u cmds, other %u calls %u cmds\n",
                     p46_bdc0_calls + 1, p46_bdc0_n[1], p46_bdc0_cmds[1], p46_bdc0_n[2], p46_bdc0_cmds[2],
                     p46_bdc0_n[0] + p46_bdc0_n[3], p46_bdc0_cmds[0] + p46_bdc0_cmds[3]);
    }
    p46_bdc0_calls++;
    return r;
}
extern unsigned D_800E0D18;
int __real_func_15196560(int a0, int a1);
int __wrap_func_15196560(int a0, int a1) {
    int r;
    if (p46_flag < 0) p46_flag = port_flag("p46check");
    r = __real_func_15196560(a0, a1);
    if (p46_flag && (p46_6560_calls < (unsigned)p46_flag || (p46_6560_calls & 255) == 0)) {
        const unsigned char *e = (const unsigned char *)D_800E0D18;
        int n = 0;
        port_log("[p46] func_15196560 #%u frame %u (DLs %08X %08X):\n", p46_6560_calls, port_frame_count, a0, a1);
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
