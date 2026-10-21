/* ROM asset viewer: draws real Conker display lists straight from the ROM through the F3DEX2
 * interpreter, before the game's own frame builders are C (docs/port/sessions/P6.md).
 *
 * Page: ?app=game&gfxdemo=1  (default asset list) or gfxdemo=ROMOFF:DLOFF,ROMOFF:DLOFF,... (hex).
 * Each asset is one rzip file of the ROM's asset area (u32 BE size + raw DEFLATE), a Rare model
 * blob: header, Vtx array, display lists. It is inflated into wasm memory in the vbe layout, so the
 * interpreter reads it exactly like game memory. The viewer's own display list (viewport, matrices,
 * render state, segments, gsSPDisplayList into the asset) is built here with the GBI encodings.
 * Model DLs address their file through segments 0/1; bone matrices (segment 3) get copies of the
 * viewer's modelview; segment 8 (engine material DL) is an empty list.
 * Texture ids (P8): G_SETTIMG words with segment nibble 0 are texture ids, which the engine resolves
 * in place when it loads a model: func_1510D3E0 (asm) walks the DL and calls the texture cache
 * func_1510D66C (asm). tex_patch_dl() below does the same on the PC side (see its comment), so these
 * draw with their real texels and palettes. Texture-bank segments (2, 4-11) are still unresolved
 * and draw with a placeholder pattern (gfx_tex_unresolved_segs). */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "gfx.h"
#include "../ultra/pc_mem.h"

void port_log(const char *fmt, ...);
extern unsigned char *port_rom;
extern unsigned port_rom_size;
extern unsigned gfx_tex_unresolved_segs;

typedef struct { unsigned rom, dl, size; unsigned char *buf; float c[3], r; } Asset;
#define MAXA 9
static Asset A[MAXA];
static int nA, inited;
static unsigned *work;            /* viewer DL + matrices + viewport (vbe game-memory layout) */
static unsigned char *bones, *enddl;

/* defaults: rzip asset files found by a scan of the ROM (docs/port/sessions/P6.md) */
static const unsigned DEF[][2] = {
    {0x122C7A0, 0x528},  /* Conker TRI4 (0x1x) triangles, vertex colours, CI textures by id */
    {0xBA0708, 0x400},   /* skinned (segment-3 bone matrices), 5 textures */
    {0xF94550, 0x370},
    {0xB602A8, 0x350},
    {0xAF8468, 0x2FE0},  /* large model: 979 commands, 114 vertex loads */
    {0xAFA400, 0x1DC0},
};

static unsigned be32(const unsigned char *p) { return (unsigned)p[0] << 24 | p[1] << 16 | p[2] << 8 | p[3]; }

/* one rzip file of the ROM (u32 BE size + raw DEFLATE) into a new buffer in the vbe layout */
static unsigned char *inflate_rom(unsigned rom, unsigned *size) {
    if (!port_rom || rom + 8 > port_rom_size) return 0;
    unsigned n = be32(port_rom + rom);
    if (n == 0 || n > 0x400000) return 0;
    unsigned char *tmp = malloc(n);
    int got = port_inflate_raw(tmp, n, port_rom + rom + 4, port_rom_size - rom - 4);
    if (got != (int)n) { free(tmp); return 0; }
    unsigned char *buf = calloc((n + 7) & ~3u, 1);
    for (unsigned i = 0; i + 4 <= n; i += 4) *(unsigned *)(buf + i) = be32(tmp + i); /* vbe layout */
    for (unsigned i = n & ~3u; i < n; i++) vbe_st8(buf + i, tmp[i]);
    free(tmp);
    *size = n;
    return buf;
}

static int load(Asset *a) {
    a->buf = inflate_rom(a->rom, &a->size);
    return a->buf ? 0 : -1;
}

/* ---- texture ids (P8; docs/port/sessions/P8.md "Texture ids")
 * The texture bank: texture id i (0 <= i < 0x1E54) is an rzip file at ROM
 *   D_1A3B40 (0x1A3B40) + sum of D_800920D0[0..i)       (u16 compressed sizes, game_data)
 * which is func_1510D8F4 (C) + func_1510D66C (asm: cache D_800B1268[id], DMA, inflate). */
#define TEX_IDS 0x1E54
#define TEX_ROM 0x1A3B40u
static unsigned char *tex_buf[TEX_IDS];
static unsigned tex_size[TEX_IDS], *tex_rom, tex_loaded, tex_missing;

static unsigned char *tex_get(unsigned id, unsigned *size) {
    if (id >= TEX_IDS) return 0;
    if (!tex_rom) {
        /* prefix sums of D_800920D0, read from a private inflate of game_data (ROM 0x188688, vram
         * 0x80082EB0; same constants as pc_mem.c SEGS) so that the viewer also works before
         * port_mem_load() and whatever state the game is in */
        unsigned gsz;
        unsigned char *gd = inflate_rom(0x188688, &gsz);
        if (!gd || gsz < 0x800920D0u - 0x80082EB0u + 2 * TEX_IDS) { free(gd); return 0; }
        unsigned char *t = gd + (0x800920D0u - 0x80082EB0u);
        tex_rom = malloc(TEX_IDS * 4);
        unsigned o = TEX_ROM;
        for (unsigned i = 0; i < TEX_IDS; i++) { tex_rom[i] = o; o += vbe_ld16(t + 2 * i); }
        free(gd);
    }
    if (!tex_buf[id]) {
        tex_buf[id] = inflate_rom(tex_rom[id], &tex_size[id]);
        if (!tex_buf[id]) { tex_missing++; return 0; }
        tex_loaded++;
    }
    *size = tex_size[id];
    return tex_buf[id];
}

/* PC equivalent of func_1510D3E0 (asm, game_eu_13A8A0), the engine's model-DL texture resolver,
 * applied once at load. For every G_SETTIMG (0xFD) up to G_ENDDL whose w1 has segment nibble 0 and
 * top byte < 0x06: id = w1 & 0xF03FFFFF, flags = w1 >> 22; w1 := texture address (cache, loaded on
 * demand), then flags & 1: + size - 0x200 (256-colour TLUT at the end of the texture), flags & 2:
 * + size - 0x20 (16-colour TLUT). The engine runs it per model DL; the viewer also follows
 * G_DL (0xDE) calls into the model file (segments 0/1) so that sub-lists get the same treatment. */
static unsigned tex_patch_dl(Asset *a, unsigned off, int depth) {
    unsigned n = 0;
    for (; off + 8 <= a->size && depth < 8; off += 8) {
        unsigned *c = (unsigned *)(a->buf + off), op = c[0] >> 24, w1 = c[1];
        if (op == 0xDF) break;
        if (op == 0xDE && (w1 >> 24) <= 1 && (w1 & 0xFFFFFF) < a->size)
            n += tex_patch_dl(a, w1 & 0xFFFFFF, depth + 1);
        if (op != 0xFD || (w1 >> 24) >= 0x06 || (w1 & 0x0F000000u)) continue;
        unsigned size, fl = w1 >> 22;
        unsigned char *t = tex_get(w1 & 0xF03FFFFFu, &size);
        if (!t) continue;
        if (fl & 1) t += size - 0x200;
        else if (fl & 2) t += size - 0x20;
        c[1] = (unsigned)(uintptr_t)t;   /* a wasm pointer (>= PORT_WASM_BASE): never read as a segment */
        n++;
    }
    return n;
}

/* Mtx (s15.16, N64 layout: 8 words of integer halves, 8 words of fraction halves) */
static void put_mtx(unsigned *w, float m[4][4]) {
    for (int i = 0; i < 16; i += 2) {
        int a = (int)lrintf(m[i >> 2][i & 3] * 65536.0f), b = (int)lrintf(m[(i + 1) >> 2][(i + 1) & 3] * 65536.0f);
        w[i / 2] = ((unsigned)a & 0xFFFF0000u) | ((unsigned)b >> 16);
        w[8 + i / 2] = ((unsigned)a << 16) | ((unsigned)b & 0xFFFF);
    }
}

static void mul(float r[4][4], float a[4][4], float b[4][4]) {
    float t[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) t[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j] + a[i][3] * b[3][j];
    memcpy(r, t, sizeof t);
}
static void ident(float m[4][4]) { memset(m, 0, 64); m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1; }

static unsigned cc(unsigned a, unsigned b, unsigned c, unsigned d, unsigned Aa, unsigned Ab, unsigned Ac, unsigned Ad, unsigned *w1) {
    *w1 = b << 28 | b << 24 | Aa << 21 | Ac << 18 | d << 15 | Ab << 12 | Ad << 9 | d << 6 | Ab << 3 | Ad;
    return 0xFC000000u | a << 20 | c << 15 | Aa << 12 | Ac << 9 | a << 5 | c;
}

/* viewer DL for asset k in grid cell (cx, cy) of size (cw, ch) N64 pixels; returns the DL */
static unsigned *build(Asset *a, float cx, float cy, float cw, float ch, float ang) {
    unsigned *vp = work, *mp = work + 4, *mm = work + 20, *dl = work + 64, *d = dl;
    unsigned char *v = (unsigned char *)vp;
    short sc[4] = {(short)(cw * 2), (short)(ch * 2), 511, 0}, tr[4] = {(short)(cx * 4), (short)(cy * 4), 511, 0};
    for (int i = 0; i < 4; i++) { vbe_st16(v + 2 * i, (unsigned short)sc[i]); vbe_st16(v + 8 + 2 * i, (unsigned short)tr[i]); }
    float r = a->r > 1 ? a->r : 1, dist = r / sinf(0.35f) * 1.05f;
    float P[4][4] = {{0}}, n = dist - r * 1.6f, f = dist + r * 1.6f, fy = 1 / tanf(0.35f);
    if (n < 1) n = 1;
    P[0][0] = fy * ch / cw; P[1][1] = fy; P[2][2] = (n + f) / (n - f); P[2][3] = -1; P[3][2] = 2 * n * f / (n - f);
    put_mtx(mp, P);
    float T[4][4], Ry[4][4], Rx[4][4], T2[4][4], M[4][4];
    ident(T); T[3][0] = -a->c[0]; T[3][1] = -a->c[1]; T[3][2] = -a->c[2];
    ident(Ry); Ry[0][0] = cosf(ang); Ry[0][2] = -sinf(ang); Ry[2][0] = sinf(ang); Ry[2][2] = cosf(ang);
    float ax = 0.35f;
    ident(Rx); Rx[1][1] = cosf(ax); Rx[1][2] = sinf(ax); Rx[2][1] = -sinf(ax); Rx[2][2] = cosf(ax);
    ident(T2); T2[3][2] = -dist;
    mul(M, T, Ry); mul(M, M, Rx); mul(M, M, T2);
    put_mtx(mm, M);
    for (int i = 0; i < 64; i++) put_mtx((unsigned *)(bones + 64 * i), M); /* skinned parts: bind pose */
    unsigned w1;
#define G(a, b) (*d++ = (a), *d++ = (b))
    G(0xE7000000, 0);
    G(0xDC080008, (unsigned)(uintptr_t)vp);                     /* gsSPViewport */
    G(0xDA380007, (unsigned)(uintptr_t)mp);                     /* gsSPMatrix projection|load */
    G(0xDA380003, (unsigned)(uintptr_t)mm);                     /* gsSPMatrix modelview|load */
    G(0xD9000000, 0x00200405);                                  /* geometry: zbuffer shade smooth cull_back */
    G(0xEF002000, 0x00000030);                                  /* 1-cycle, bilerp; z compare + update */
    unsigned w0 = cc(1, 15, 4, 7, 7, 7, 7, 4, &w1);             /* TEXEL0 * SHADE, alpha SHADE */
    G(w0, w1);
    G(0xD7000002, 0xFFFFFFFF);                                  /* gsSPTexture on */
    G(0xFA000000, 0xFFFFFFFF);                                  /* prim / env colours: the engine sets */
    G(0xFB000000, 0xFFFFFFFF);                                  /*   these per object; white here */
    G(0xDB060000, (unsigned)(uintptr_t)a->buf);                 /* segment 0 = model file */
    G(0xDB060004, (unsigned)(uintptr_t)a->buf);                 /* segment 1 = model file */
    G(0xDB06000C, (unsigned)(uintptr_t)bones);                  /* segment 3 = bone matrices */
    G(0xDB060020, (unsigned)(uintptr_t)enddl);                  /* segment 8 = engine material DL */
    G(0xDE000000, (unsigned)(uintptr_t)(a->buf + a->dl));       /* gsSPDisplayList(model) */
    G(0xDF000000, 0);
    return dl;
}

int gfx_demo_init(const char *spec) {
    work = calloc(4096, 4);
    bones = calloc(64, 64);
    enddl = calloc(0x10000, 1); /* any offset into segment 8 reads gsSPEndDisplayList */
    for (int i = 0; i < 0x10000; i += 8) *(unsigned *)(enddl + i) = 0xDF000000;
    gfx_tex_unresolved_segs = 0xFFFF;
    nA = 0;
    if (spec && *spec && *spec != '1') {
        const char *p = spec;
        while (*p && nA < MAXA) {
            char *e;
            A[nA].rom = strtoul(p, &e, 16);
            if (*e != ':') break;
            A[nA].dl = strtoul(e + 1, &e, 16);
            nA++;
            p = *e == ',' ? e + 1 : e;
        }
    } else
        for (unsigned i = 0; i < sizeof DEF / sizeof DEF[0]; i++) { A[nA].rom = DEF[i][0]; A[nA].dl = DEF[i][1]; nA++; }
    int ok = 0;
    for (int k = 0; k < nA; k++) {
        Asset *a = &A[k];
        if (load(a)) { port_log("[gfxdemo] asset rom+0x%X: cannot inflate\n", a->rom); a->buf = 0; continue; }
        unsigned np = tex_patch_dl(a, a->dl, 0);
        port_log("[gfxdemo] asset rom+0x%X: %u G_SETTIMG texture ids resolved (%u textures loaded, %u missing)\n", a->rom, np,
                 tex_loaded, tex_missing);
        /* measure pass: walk the DL once for the object-space bounds */
        float mn[3], mx[3];
        gfx_measure_only = 1;
        gfx_frame_begin(0, 0, 0);
        gfx_bounds_reset();
        gfx_run_dl(build(a, 160, 120, 320, 240, 0));
        gfx_measure_only = 0;
        if (!gfx_bounds(mn, mx)) { port_log("[gfxdemo] asset rom+0x%X: no vertices\n", a->rom); a->buf = 0; continue; }
        float r = 0;
        for (int i = 0; i < 3; i++) { a->c[i] = (mn[i] + mx[i]) / 2; if ((mx[i] - mn[i]) / 2 > r) r = (mx[i] - mn[i]) / 2; }
        a->r = r * 1.2f;
        port_log("[gfxdemo] asset rom+0x%X (%u bytes), DL +0x%X: bounds (%.0f %.0f %.0f)..(%.0f %.0f %.0f)\n", a->rom, a->size, a->dl,
                 mn[0], mn[1], mn[2], mx[0], mx[1], mx[2]);
        ok++;
    }
    inited = 1;
    port_log("[gfxdemo] %d of %d assets ready\n", ok, nA);
    return ok ? 0 : -1;
}

void gfx_demo_frame(void) {
    static unsigned frame;
    if (!inited) return;
    gfx_frame_begin(0.08f, 0.09f, 0.13f);
    int cols = nA <= 1 ? 1 : nA <= 4 ? 2 : 3, rows = (nA + cols - 1) / cols;
    float cw = 320.0f / cols, ch = 240.0f / rows;
    GfxStats before = gfx_stats;
    for (int k = 0; k < nA; k++) {
        if (!A[k].buf) continue;
        float cx = cw * (k % cols) + cw / 2, cy = ch * (k / cols) + ch / 2;
        gfx_run_dl(build(&A[k], cx, cy, cw, ch, 0.6f + frame * 0.02f));
    }
    gfx_frame_end();
    if (frame++ == 2)
        port_log("[gfxdemo] frame: %u commands, %u triangles (%u from Conker TRI4), %u draws, %u texture uploads, %u texture ids unresolved, %u bad addresses\n",
                 gfx_stats.cmds - before.cmds, gfx_stats.tris - before.tris, (gfx_stats.tri4 - before.tri4) * 4,
                 gfx_stats.draws - before.draws, gfx_stats.tex_uploads - before.tex_uploads, gfx_stats.tex_ids - before.tex_ids,
                 gfx_stats.bad_addr + gfx_stats.unset_seg - before.bad_addr - before.unset_seg);
}

/* node / test hook: the viewer without a GL context (interpreter + stats only) */
void port_gfx_demo_test(const char *spec) {
    if (gfx_demo_init(spec)) return;
    for (int i = 0; i < 3; i++) gfx_demo_frame();
}
