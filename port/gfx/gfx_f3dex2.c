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
/* lights (P14): directional lights 0..n-1, ambient = colour of light n (F3DEX2 convention) */
static int num_lights;
static float light_col[8][3], light_dir[8][3];
static float bmin[3], bmax[3];
static int bany;

/* RDP state */
static unsigned oth_h, oth_l, combine_w0, combine_w1;
static unsigned prim_col, env_col, fog_col, blend_col, fill_col, prim_lod;
static unsigned cimg_addr, zimg_addr, cimg_width = 320;
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
static GLint u_tex0, u_tex1, u_tile0, u_tile1, u_c0, u_c1, u_a0, u_a1, u_2cyc, u_prim, u_env, u_fogc,
    u_primlod, u_acmp, u_blenda, u_fog, u_mode, u_texon;
static int gl_ok, canvas_w = 640, canvas_h = 480;
#define VF 11
#define BATCH_TRIS 4096
static float batch[BATCH_TRIS * 3 * VF];
static int nbatch;      /* vertices in batch */
static int state_dirty = 1;
static int rect_mode;   /* 0 tris, 1 fill rect, 2 tex rect (screen-space quads) */

static const char *VS =
    "#version 300 es\n"
    "in vec4 aPos; in vec4 aCol; in vec2 aST; in float aFog;\n"
    "out vec4 vCol; out vec2 vST; out float vFog;\n"
    "void main() { gl_Position = aPos; vCol = aCol; vST = aST; vFog = aFog; }\n";

static const char *FS =
    "#version 300 es\n"
    "precision highp float;\n"
    "in vec4 vCol; in vec2 vST; in float vFog;\n"
    "uniform sampler2D uT0, uT1; uniform vec4 uTile0, uTile1;\n"
    "uniform ivec4 uC0, uC1, uA0, uA1; uniform int u2cyc, uAcmp, uFog, uMode, uTexOn;\n"
    "uniform vec4 uPrim, uEnv, uFogC; uniform float uPrimLod, uBlendA;\n"
    "out vec4 frag;\n"
    "vec4 T0, T1, SH;\n"
    "vec3 cA(int i, vec3 c) { if (i == 0) return c; if (i == 1) return T0.rgb; if (i == 2) return T1.rgb;"
    "  if (i == 3) return uPrim.rgb; if (i == 4) return SH.rgb; if (i == 5) return uEnv.rgb; if (i == 6) return vec3(1.0);"
    "  if (i == 7) return vec3(0.5); return vec3(0.0); }\n"
    "vec3 cB(int i, vec3 c) { if (i == 0) return c; if (i == 1) return T0.rgb; if (i == 2) return T1.rgb;"
    "  if (i == 3) return uPrim.rgb; if (i == 4) return SH.rgb; if (i == 5) return uEnv.rgb; return vec3(0.0); }\n"
    "vec3 cC(int i, vec3 c, float ca) { if (i == 0) return c; if (i == 1) return T0.rgb; if (i == 2) return T1.rgb;"
    "  if (i == 3) return uPrim.rgb; if (i == 4) return SH.rgb; if (i == 5) return uEnv.rgb; if (i == 6) return vec3(1.0);"
    "  if (i == 7) return vec3(ca); if (i == 8) return vec3(T0.a); if (i == 9) return vec3(T1.a);"
    "  if (i == 10) return vec3(uPrim.a); if (i == 11) return vec3(SH.a); if (i == 12) return vec3(uEnv.a);"
    "  if (i == 13) return vec3(1.0); if (i == 14) return vec3(uPrimLod); return vec3(0.0); }\n"
    "vec3 cD(int i, vec3 c) { if (i == 0) return c; if (i == 1) return T0.rgb; if (i == 2) return T1.rgb;"
    "  if (i == 3) return uPrim.rgb; if (i == 4) return SH.rgb; if (i == 5) return uEnv.rgb; if (i == 6) return vec3(1.0);"
    "  return vec3(0.0); }\n"
    "float aX(int i, float a) { if (i == 0) return a; if (i == 1) return T0.a; if (i == 2) return T1.a;"
    "  if (i == 3) return uPrim.a; if (i == 4) return SH.a; if (i == 5) return uEnv.a; if (i == 6) return 1.0; return 0.0; }\n"
    "float aC(int i, float a) { if (i == 0) return 1.0; if (i == 1) return T0.a; if (i == 2) return T1.a;"
    "  if (i == 3) return uPrim.a; if (i == 4) return SH.a; if (i == 5) return uEnv.a; if (i == 6) return uPrimLod; return 0.0; }\n"
    "void main() {\n"
    "  SH = vCol;\n"
    "  if (uMode == 1) { frag = vCol; return; }\n"
    "  T0 = (uTexOn & 1) != 0 ? texture(uT0, (vST - uTile0.xy) * uTile0.zw) : vec4(1.0);\n"
    "  T1 = (uTexOn & 2) != 0 ? texture(uT1, (vST - uTile1.xy) * uTile1.zw) : T0;\n"
    "  if (uMode == 3) { if (T0.a < 0.5) discard; frag = T0; return; }\n"
    "  vec3 c = vec3(0.0); float a = 0.0;\n"
    "  vec3 c1 = (cA(uC0.x, c) - cB(uC0.y, c)) * cC(uC0.z, c, a) + cD(uC0.w, c);\n"
    "  float a1 = (aX(uA0.x, a) - aX(uA0.y, a)) * aC(uA0.z, a) + aX(uA0.w, a);\n"
    "  if (u2cyc == 1) { c = clamp(c1, 0.0, 1.0); a = clamp(a1, 0.0, 1.0);\n"
    "    c1 = (cA(uC1.x, c) - cB(uC1.y, c)) * cC(uC1.z, c, a) + cD(uC1.w, c);\n"
    "    a1 = (aX(uA1.x, a) - aX(uA1.y, a)) * aC(uA1.z, a) + aX(uA1.w, a); }\n"
    "  c1 = clamp(c1, 0.0, 1.0); a1 = clamp(a1, 0.0, 1.0);\n"
    "  if (uAcmp == 1 && a1 < uBlendA) discard;\n"
    "  if (uAcmp == 2 && a1 < 0.5) discard;\n"
    "  if (uFog == 1) c1 = mix(c1, uFogC.rgb, vFog);\n"
    "  frag = vec4(c1, a1);\n"
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
    U(u_tex0, "uT0"); U(u_tex1, "uT1"); U(u_tile0, "uTile0"); U(u_tile1, "uTile1"); U(u_c0, "uC0"); U(u_c1, "uC1");
    U(u_a0, "uA0"); U(u_a1, "uA1"); U(u_2cyc, "u2cyc"); U(u_prim, "uPrim"); U(u_env, "uEnv"); U(u_fogc, "uFogC");
    U(u_primlod, "uPrimLod"); U(u_acmp, "uAcmp"); U(u_blenda, "uBlendA"); U(u_fog, "uFog"); U(u_mode, "uMode");
    U(u_texon, "uTexOn");
    glUniform1i(u_tex0, 0);
    glUniform1i(u_tex1, 1);
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

static void tile_dims(const Tile *t, unsigned *w, unsigned *h) {
    unsigned tw = ((t->lrs - t->uls) >> 2) + 1, th = ((t->lrt - t->ult) >> 2) + 1;
    if (t->masks && !(t->cms & 2)) tw = 1u << t->masks;
    if (t->maskt && !(t->cmt & 2)) th = 1u << t->maskt;
    if (tw > 1024) tw = 1024;
    if (th > 1024) th = 1024;
    *w = tw; *h = th;
}

static GLuint tex_for(int ti, unsigned *w, unsigned *h) {
    const Tile *t = &tiles[ti & 7];
    tile_dims(t, w, h);
    unsigned key[6] = {tmem_gen, t->fmt | t->siz << 4 | t->pal << 8 | t->cms << 12 | t->cmt << 16 | (oth_h >> 12 & 0xF) << 20,
                       t->tmem | t->line << 12, *w | *h << 16, t->masks | t->maskt << 8, 1};
    unsigned hsh = (key[0] * 2654435761u ^ key[1] * 40503u ^ key[2] * 97u ^ key[3]) & 255;
    TexEnt *e = &tcache[hsh];
    if (e->tex && !memcmp(e->key, key, sizeof key)) return e->tex;
    if (!e->tex) glGenTextures(1, &e->tex);
    memcpy(e->key, key, sizeof key);
    if ((size_t)*w * *h * 4 > sizeof texbuf) *h = sizeof texbuf / 4 / *w;
    for (unsigned y = 0; y < *h; y++)
        for (unsigned x = 0; x < *w; x++) texel(t, x, y, texbuf + (y * *w + x) * 4);
    glBindTexture(GL_TEXTURE_2D, e->tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *w, *h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texbuf);
    GLint f = (oth_h >> 12 & 3) == 2 ? GL_LINEAR : GL_NEAREST; /* G_TF_BILERP */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, f);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, f);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (t->cms & 2) || !t->masks ? GL_CLAMP_TO_EDGE : (t->cms & 1) ? GL_MIRRORED_REPEAT : GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (t->cmt & 2) || !t->maskt ? GL_CLAMP_TO_EDGE : (t->cmt & 1) ? GL_MIRRORED_REPEAT : GL_REPEAT);
    gfx_stats.tex_uploads++;
    return e->tex;
}

static float shiftscale(unsigned sh) { return sh == 0 ? 1.0f : sh <= 10 ? 1.0f / (1 << sh) : (float)(1 << (16 - sh)); }

static void rgba(GLint u, unsigned c) {
    glUniform4f(u, (c >> 24) / 255.0f, (c >> 16 & 255) / 255.0f, (c >> 8 & 255) / 255.0f, (c & 255) / 255.0f);
}

static void apply_state(void) {
    unsigned cyc = oth_h >> 20 & 3; /* 0 1CYC, 1 2CYC, 2 COPY, 3 FILL */
    unsigned w0 = combine_w0, w1 = combine_w1;
    glUniform4i(u_c0, w0 >> 20 & 15, w1 >> 28 & 15, w0 >> 15 & 31, w1 >> 15 & 7);
    glUniform4i(u_a0, w0 >> 12 & 7, w1 >> 12 & 7, w0 >> 9 & 7, w1 >> 9 & 7);
    glUniform4i(u_c1, w0 >> 5 & 15, w1 >> 24 & 15, w0 & 31, w1 >> 6 & 7);
    glUniform4i(u_a1, w1 >> 21 & 7, w1 >> 3 & 7, w1 >> 18 & 7, w1 & 7);
    glUniform1i(u_2cyc, cyc == 1);
    rgba(u_prim, prim_col); rgba(u_env, env_col); rgba(u_fogc, fog_col);
    glUniform1f(u_primlod, prim_lod / 255.0f);
    glUniform1f(u_blenda, (blend_col & 255) / 255.0f);
    unsigned ac = oth_l & 3;
    glUniform1i(u_acmp, ac == 1 ? 1 : (oth_l & 0x2000) && (oth_l & 0x1000) ? 2 : 0); /* threshold / cvg x alpha */
    glUniform1i(u_fog, (geom & G_FOG) && (oth_l >> 30) == 3);
    int mode = rect_mode == 1 || cyc == 3 ? 1 : cyc == 2 ? 3 : 0;
    glUniform1i(u_mode, mode);
    int texon = 0;
    if (mode != 1 && (tex_on || rect_mode == 2)) {
        for (int k = 0; k < 2; k++) {
            unsigned w, h;
            int ti = (tex_tile + k) & 7;
            if (k == 1 && cyc != 1) break;
            glActiveTexture(GL_TEXTURE0 + k);
            glBindTexture(GL_TEXTURE_2D, tex_for(ti, &w, &h));
            const Tile *t = &tiles[ti];
            /* shader: uv = (st * shift - ul) / size; the shift is folded into st per vertex (below) */
            glUniform4f(k ? u_tile1 : u_tile0, t->uls / 4.0f, t->ult / 4.0f, 1.0f / w, 1.0f / h);
            texon |= 1 << k;
        }
        glActiveTexture(GL_TEXTURE0);
    }
    glUniform1i(u_texon, texon);
    /* depth */
    int zcmp = (geom & G_ZBUFFER) && (oth_l & 0x10) && rect_mode == 0, zupd = (oth_l & 0x20) && rect_mode == 0;
    if (zcmp || zupd) { glEnable(GL_DEPTH_TEST); glDepthFunc(zcmp ? GL_LEQUAL : GL_ALWAYS); } else glDisable(GL_DEPTH_TEST);
    glDepthMask(zupd ? GL_TRUE : GL_FALSE);
    if ((oth_l >> 10 & 3) == 3) { glEnable(GL_POLYGON_OFFSET_FILL); glPolygonOffset(-1, -2); }
    else glDisable(GL_POLYGON_OFFSET_FILL);
    /* blending: FORCE_BL with an alpha blender (XLU render modes) */
    if ((oth_l & 0x4000) && mode != 1 && cyc < 2) { glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); }
    else glDisable(GL_BLEND);
    /* viewport */
    float sx = canvas_w / (float)cimg_width, sy = canvas_h / (cimg_width * 0.75f);
    if (rect_mode) glViewport(0, 0, canvas_w, canvas_h);
    else {
        float w = 2 * vp_scale[0] / 4.0f, h = 2 * vp_scale[1] / 4.0f;
        float x0 = (vp_trans[0] - vp_scale[0]) / 4.0f, y0 = (vp_trans[1] - vp_scale[1]) / 4.0f;
        glViewport((GLint)(x0 * sx), (GLint)(canvas_h - (y0 + h) * sy), (GLint)(w * sx), (GLint)(h * sy));
    }
}

static void flush(void) {
    if (!nbatch || !gl_ok) { nbatch = 0; return; }
    glBufferData(GL_ARRAY_BUFFER, nbatch * VF * 4, batch, GL_STREAM_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, nbatch);
    gfx_stats.draws++;
    nbatch = 0;
}

static void need_state(int rm) {
    if (rm != rect_mode) { flush(); rect_mode = rm; state_dirty = 1; }
    if (state_dirty) { flush(); if (gl_ok) apply_state(); state_dirty = 0; }
    if (nbatch + 6 > BATCH_TRIS * 3) flush();
}

static void put(const V *v, float sshift, float tshift) {
    float *o = batch + nbatch++ * VF;
    o[0] = v->x; o[1] = v->y; o[2] = v->z; o[3] = v->w;
    o[4] = v->r; o[5] = v->g; o[6] = v->b; o[7] = v->a;
    o[8] = v->s * sshift; o[9] = v->t * tshift; o[10] = v->fog;
}

static void tri(unsigned i0, unsigned i1, unsigned i2) {
    gfx_stats.tris++;
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
    const Tile *t = &tiles[tex_tile & 7];
    float ss = shiftscale(t->shifts), ts = shiftscale(t->shiftt);
    put(a, ss, ts); put(b, ss, ts); put(c, ss, ts);
}

/* screen-space rectangle in N64 pixels (fill / texture rectangles) */
static void rect(float x0, float y0, float x1, float y1, float s0, float t0, float s1, float t1, unsigned col, int rm) {
    need_state(rm);
    float W = cimg_width, H = cimg_width * 0.75f;
    V q[4];
    float xs[4] = {x0, x1, x0, x1}, ys[4] = {y0, y0, y1, y1}, ss[4] = {s0, s1, s0, s1}, ts[4] = {t0, t0, t1, t1};
    for (int i = 0; i < 4; i++) {
        q[i].x = xs[i] / W * 2 - 1; q[i].y = 1 - ys[i] / H * 2; q[i].z = 0; q[i].w = 1;
        q[i].r = (col >> 24) / 255.0f; q[i].g = (col >> 16 & 255) / 255.0f; q[i].b = (col >> 8 & 255) / 255.0f;
        q[i].a = (col & 255) / 255.0f; q[i].s = ss[i]; q[i].t = ts[i]; q[i].fog = 0;
    }
    put(&q[0], 1, 1); put(&q[1], 1, 1); put(&q[2], 1, 1);
    put(&q[1], 1, 1); put(&q[3], 1, 1); put(&q[2], 1, 1);
}

/* ------------------------------------------------------------------ RSP commands */
/* Conker lighting (session P14). Conker's F3DEX2 variant keeps the Vtx rgba as the vertex colour
 * when G_LIGHTING is on and takes the normal from a separate array:
 *   G_MOVEMEM index 0x0E sets the array base for the following G_VTX loads; vertex slot k (the
 *   index in the 32-entry vertex buffer, not the index in the Vtx array) has its normal's x and y
 *   as s8 at base + 2k, and z is the low byte of the Vtx flag halfword (+7).
 * Checked on the ROM models: one array chunk is 0x40 bytes (32 slots x 2) per vertex batch, and a
 * flat panel at x = 1 has (127, 0, flag 0), i.e. +X. The colour is then
 *   rgb = vertex rgb * min(1, ambient + sum_l max(0, n . dir_l) * col_l)
 * with n rotated by the modelview and normalised, and the lights in the F3DEX2 Light layout
 * (G_MOVEMEM index 0x0A, col at +0, dir s8 at +8; numlights by G_MOVEWORD index 2). Rare's records
 * are 48 bytes (light n at offset (n + 2) * 48, numlights word = n * 48); their point-light fields
 * are not interpreted. Without any light command the ambient is 1 (unlit look, as before). */
static void light_vtx(V *v, const unsigned char *n, const unsigned char *vtx) {
    float nx = (signed char)vbe_ld8(n), ny = (signed char)vbe_ld8(n + 1), nz = (signed char)vbe_ld8(vtx + 7);
    float ex = nx * mv[0][0] + ny * mv[1][0] + nz * mv[2][0];
    float ey = nx * mv[0][1] + ny * mv[1][1] + nz * mv[2][1];
    float ez = nx * mv[0][2] + ny * mv[1][2] + nz * mv[2][2];
    float len = sqrtf(ex * ex + ey * ey + ez * ez);
    float c[3];
    int nl = num_lights > 7 ? 7 : num_lights;
    if (len > 0) { ex /= len; ey /= len; ez /= len; }
    for (int k = 0; k < 3; k++) c[k] = light_col[nl][k];
    for (int l = 0; l < nl; l++) {
        float d = ex * light_dir[l][0] + ey * light_dir[l][1] + ez * light_dir[l][2];
        if (d > 0) for (int k = 0; k < 3; k++) c[k] += d * light_col[l][k];
    }
    v->r *= c[0] > 1 ? 1 : c[0]; v->g *= c[1] > 1 ? 1 : c[1]; v->b *= c[2] > 1 ? 1 : c[2];
    gfx_stats.lit++;
}

static void load_vtx(unsigned w0, unsigned w1) {
    unsigned n = w0 >> 12 & 0xFF, end = w0 >> 1 & 0x7F, v0 = end - n;
    const unsigned char *p = gfx_addr(w1);
    const unsigned char *nrm = normal_base ? gfx_addr(normal_base) : 0;
    if (!p || v0 + n > 64) { gfx_stats.bad_addr++; return; }
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
        if ((geom & G_LIGHTING) && nrm) light_vtx(v, nrm + 2 * (v0 + i), p);
        if (!(geom & G_SHADE)) v->r = v->g = v->b = 1;
        v->fog = 0;
        if (geom & G_FOG) {
            float f = v->w != 0 ? v->z / v->w * fog_mul + fog_off : 0;
            v->fog = (f < 0 ? 0 : f > 255 ? 255 : f) / 255.0f;
        }
    }
    gfx_stats.verts += n;
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

static void unknown(unsigned op, unsigned w0, unsigned w1) {
    gfx_stats.unknown_ops++;
    if (!(unk_seen[op >> 5] & (1u << (op & 31)))) {
        unk_seen[op >> 5] |= 1u << (op & 31);
        port_log("[gfx] unknown command %02X: %08X %08X\n", op, w0, w1);
    }
}

static int gfx_trace;   /* P19: dump every command of the first real frames */
void gfx_run_dl(const void *dl) {
    const unsigned char *stack[32], *pc = dl;
    int sp = 0, guard = 0;
    gfx_stats.dls++;
    while (pc && ++guard < 1000000) {
        unsigned w0 = rd32(pc), w1 = rd32(pc + 4), op = w0 >> 24;
        if (gfx_trace) port_log("[gfx]   %p: %08X %08X\n", (const void *)pc, w0, w1);
        pc += 8;
        gfx_stats.cmds++;
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
            break;
        }
        case 0x03: break;                                     /* G_CULLDL: no culling (draw everything) */
        case 0x04: {                                          /* G_BRANCH_Z: take the near (detailed) branch */
            const unsigned char *t = gfx_addr(rdphalf1);
            if (t) pc = t;
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
            memcpy(mv, mvstack[mvsp], sizeof mv); mtx_mul(mp, mv, proj); break;
        case 0xD9: geom = (geom & (w0 & 0xFFFFFF)) | w1; state_dirty = 1; break; /* G_GEOMETRYMODE */
        case 0xDA: {                                          /* G_MTX */
            const unsigned char *p = gfx_addr(w1);
            if (!p) { gfx_stats.bad_addr++; break; }
            unsigned prm = (w0 & 0xFF) ^ 1;                  /* ^ G_MTX_PUSH */
            float m[4][4];
            mtx_read(m, p);
            { static int md = -1; if (md < 0) md = port_flag("mtxdump"); /* P25: ?mtxdump=1 + dltrace: G_MTX contents */
              if (md && gfx_trace)
                  port_log("[mtx] %08X %s%s%s: %.4f %.4f %.4f %.4f | %.4f %.4f %.4f %.4f | %.4f %.4f %.4f %.4f | %.4f %.4f %.4f %.4f\n",
                           w1, prm & 4 ? "P" : "MV", prm & 2 ? " load" : " mul", prm & 1 ? " push" : "",
                           m[0][0], m[0][1], m[0][2], m[0][3], m[1][0], m[1][1], m[1][2], m[1][3],
                           m[2][0], m[2][1], m[2][2], m[2][3], m[3][0], m[3][1], m[3][2], m[3][3]); }
            if (prm & 4) { if (prm & 2) memcpy(proj, m, sizeof m); else mtx_mul(proj, m, proj); }
            else {
                if ((prm & 1) && mvsp < 31) memcpy(mvstack[mvsp++], mv, sizeof mv);
                if (prm & 2) memcpy(mv, m, sizeof m); else mtx_mul(mv, m, mv);
            }
            mtx_mul(mp, mv, proj);
            break;
        }
        case 0xDB: {                                          /* G_MOVEWORD */
            unsigned idx = w0 >> 16 & 0xFF, off = w0 & 0xFFFF;
            if (idx == 6) { segtab[(off / 4) & 15] = w1; segset |= 1u << ((off / 4) & 15); }
            else if (idx == 8) { fog_mul = (short)(w1 >> 16); fog_off = (short)w1; }
            else if (idx == 2) num_lights = (int)(w1 / 48);  /* G_MW_NUMLIGHT, Rare 48-byte lights */
            break;
        }
        case 0xDC: {                                          /* G_MOVEMEM */
            unsigned idx = w0 & 0xFF;
            const unsigned char *p = gfx_addr(w1);
            if (idx == 8 && p) {                              /* G_MV_VIEWPORT */
                for (int i = 0; i < 4; i++) { vp_scale[i] = (short)vbe_ld16(p + 2 * i); vp_trans[i] = (short)vbe_ld16(p + 8 + 2 * i); }
                state_dirty = 1;
            } else if (idx == 0x0E) normal_base = w1;         /* Conker: vertex normal array (not G_MV_MATRIX) */
            else if (idx == 0x0A && p) {                      /* G_MV_LIGHT: see light_vtx() */
                int n = (int)((w0 >> 8 & 0xFF) * 8 / 48) - 2;
                if (n >= 0 && n < 8) {
                    for (int k = 0; k < 3; k++) light_col[n][k] = vbe_ld8(p + k) / 255.0f;
                    float d[3], l;
                    for (int k = 0; k < 3; k++) d[k] = (signed char)vbe_ld8(p + 8 + k);
                    l = sqrtf(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
                    for (int k = 0; k < 3; k++) light_dir[n][k] = l > 0 ? d[k] / l : 0;
                }
            }
            break;
        }
        case 0xDD:                                            /* G_LOAD_UCODE (+ RDPHALF_1 = text) */
            if (gfx_stats.ucode_loads++ < 4) port_log("[gfx] G_LOAD_UCODE text %08X data %08X size 0x%X\n", rdphalf1, w1, (w0 & 0xFFFF) + 1);
            break;
        case 0xDE: {                                          /* G_DL / G_BRANCH_DL */
            const unsigned char *t = gfx_addr(w1);
            if (!t) { gfx_stats.bad_addr++; break; }
            if (!(w0 >> 16 & 0xFF)) { if (sp >= 32) break; stack[sp++] = pc; }
            pc = t;
            break;
        }
        case 0xDF: pc = sp ? stack[--sp] : 0; break;          /* G_ENDDL */
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
        case 0xED: case 0xEE: break;                          /* scissor, prim depth */
        case 0xEC: break;  /* G_SETCONVERT (YUV coefficients, K4/K5). P26: the frame sends EC000000 000000FF
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
            rect(ulx, uly, lrx, lry, 0, 0, 0, 0, col, 1);
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
            break;
        case 0xFE: zimg_addr = w1; break;
        case 0xFF: cimg_addr = w1; cimg_width = (w0 & 0xFFF) + 1; if (cimg_width < 64) cimg_width = 320; break;
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
    mtx_ident(mv); mtx_ident(proj); mtx_ident(mp); mvsp = 0;
    segset = 0; geom = 0; oth_h = oth_l = 0; tex_on = 0;
    normal_base = 0; num_lights = 0; light_col[0][0] = light_col[0][1] = light_col[0][2] = 1;
    state_dirty = 1; rect_mode = 0; nbatch = 0;
    gfx_stats.frames++;
    if (!gl_ok) return;
    glViewport(0, 0, canvas_w, canvas_h);
    glDepthMask(GL_TRUE);
    glClearColor(r, g, b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void gfx_frame_end(void) { flush(); }

/* The RSP gfx task (OSTask in game memory): t.data_ptr is the display list. Field offsets of
 * OSTask_t: type 0, flags 4, ucode_boot 8, ucode_boot_size 12, ucode 16, ucode_size 20,
 * ucode_data 24, ucode_data_size 28, dram_stack 32, dram_stack_size 36, output_buff 40,
 * output_buff_size 44, data_ptr 48, data_size 52, yield_data_ptr 56, yield_data_size 60. */
void gfx_run_task(void *task) {
    const unsigned char *t = task;
    unsigned ucode = rd32(t + 16), data = rd32(t + 48), size = rd32(t + 52);
    gfx_stats.tasks++;
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
    if (dlstat && gfx_stats.tasks % (unsigned)dlstat == 0) logf = 2;
    memset(fr_ops, 0, sizeof fr_ops); memset(fr_seguse, 0, sizeof fr_seguse);
    gfx_frame_begin(0, 0, 0);
    gfx_run_dl(dl);
    gfx_frame_end();
    gfx_trace = 0;
    if (logf)
        port_log("[gfx] frame %u: %u DLs, %u commands, %u triangles, %u unknown commands\n", gfx_stats.tasks,
                 gfx_stats.dls - d0, gfx_stats.cmds - c0, gfx_stats.tris - t0, gfx_stats.unknown_ops - u0);
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
