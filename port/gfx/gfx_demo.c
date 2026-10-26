/* ROM asset viewer: draws real Conker display lists straight from the ROM through the F3DEX2
 * interpreter, before the game's own frame builders are C (docs/port/design/P6.md).
 *
 * Page: ?app=game&gfxdemo=1  (default asset list) or gfxdemo=ROMOFF:DLOFF,ROMOFF:DLOFF,... (hex).
 * Each asset is one rzip file of the ROM's asset area (u32 BE size + raw DEFLATE), a Rare model
 * blob: header, Vtx array, display lists. It is inflated into wasm memory in the vbe layout, so the
 * interpreter reads it exactly like game memory. The viewer's own display list (viewport, matrices,
 * render state, segments, gsSPDisplayList into the asset) is built here with the GBI encodings.
 * Model DLs address their file through segments 0/1; bone matrices (segment 3) get copies of the
 * viewer's modelview; segment 8 (engine material DL) is an empty list.
 * Texture ids (P8): G_SETTIMG words with segment nibble 0 are texture ids, which the engine resolves
 * in place when it loads a model: texture_resolve_dl_ids (asm) walks the DL and calls the texture cache
 * texture_cache_lookup (asm). tex_patch_dl() below does the same on the PC side (see its comment), so these
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

typedef struct { unsigned rom, dl, size; unsigned char *buf; float c[3], r; int nbones; float bone[64][3]; } Asset;
#define MAXA 9
static Asset A[MAXA];
static int nA, inited;
static unsigned *work;            /* viewer DL + matrices + viewport (vbe game-memory layout) */
static unsigned char *bones, *enddl;

/* defaults: rzip asset files found by a scan of the ROM (docs/port/design/P6.md) */
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

/* Skeleton (P14). Skinned model files start with a header whose word +0x10 is the offset of the
 * bone table and +0x14 its size; an entry is 16 bytes {u8 parent (0xFF = root), u8 index, u8 index,
 * u8 0, f32 x, y, z}, the joint's offset from its parent. Vertices of a skinned part are relative to
 * their bone's joint and are drawn with G_MTX(segment 3 + 64 * bone). The bind pose is therefore
 * joint position (sum of the offsets up the parent chain) then the model matrix. Checked on the
 * four skinned viewer models (9, 2, 28 and 28 bones). */
static void load_bones(Asset *a) {
    unsigned off = *(unsigned *)(a->buf + 0x10), sz = *(unsigned *)(a->buf + 0x14), n = sz / 16;
    a->nbones = 0;
    if (a->size < 0x18 || !off || sz % 16 || n > 64 || off + sz > a->size || (off & 3)) return;
    for (unsigned i = 0; i < n; i++) {
        const unsigned char *e = a->buf + off + 16 * i;
        unsigned par = vbe_ld8(e), idx = vbe_ld8(e + 1);
        if (i == 0 ? par != 0xFF : (par >= i || idx != i)) { a->nbones = 0; return; }
        for (int k = 0; k < 3; k++) {
            unsigned w = *(const unsigned *)(e + 4 + 4 * k);
            float f;
            memcpy(&f, &w, 4);
            a->bone[i][k] = (i ? a->bone[par][k] : 0) + f;
        }
    }
    a->nbones = (int)n;
}

static int load(Asset *a) {
    a->buf = inflate_rom(a->rom, &a->size);
    if (a->buf) load_bones(a);
    return a->buf ? 0 : -1;
}

/* ---- texture ids (P8; docs/port/design/P8.md "Texture ids")
 * The texture bank: texture id i (0 <= i < 0x1E54) is an rzip file at ROM
 *   D_1A3B40 (0x1A3B40) + sum of g_texture_rom_sizes[0..i)       (u16 compressed sizes, game_data)
 * which is texture_rom_offset (C) + texture_cache_lookup (asm: cache g_texture_cache_data[id], DMA, inflate). */
#define TEX_IDS 0x1E54
#define TEX_ROM 0x1A3B40u
static unsigned char *tex_buf[TEX_IDS];
static unsigned tex_size[TEX_IDS], *tex_rom, tex_loaded, tex_missing;

static unsigned char *tex_get(unsigned id, unsigned *size) {
    if (id >= TEX_IDS) return 0;
    if (!tex_rom) {
        /* prefix sums of g_texture_rom_sizes, read from a private inflate of game_data (ROM 0x188688, vram
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

/* PC equivalent of texture_resolve_dl_ids (asm, game_eu_13A8A0), the engine's model-DL texture resolver,
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
static int measuring;
static float pose_L[72][16];  /* P58: posed joint matrices in model space (gfx_pose_overlay_set); 0 joints = bind pose */
static int pose_nn, pose_on;
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
    if (measuring) ident(M);                           /* bounds in model space */
    put_mtx(mm, M);
    for (int i = 0; i < 64; i++) {                     /* skinned parts: bind pose, see load_bones() */
        float B[4][4], BM[4][4];
        ident(B);
        if (i < a->nbones) { B[3][0] = a->bone[i][0]; B[3][1] = a->bone[i][1]; B[3][2] = a->bone[i][2]; }
        if (pose_on && i < pose_nn) memcpy(B, pose_L[i], 64);   /* P58: the evaluator's joint matrix */
        mul(BM, B, M);
        put_mtx((unsigned *)(bones + 64 * i), BM);
    }
    /* one directional light (upper left front, in eye space) + ambient, Light records at 48-byte
     * stride as Rare's ucode reads them (gfx_f3dex2.c light_vtx) */
    unsigned char *L = (unsigned char *)(work + 3072);
    memset(L, 0, 4 * 48);
    static const unsigned char dcol[3] = {0xE0, 0xDC, 0xD0}, acol[3] = {0x60, 0x60, 0x68};
    for (int k = 0; k < 3; k++) { vbe_st8(L + k, dcol[k]); vbe_st8(L + 4 + k, dcol[k]); vbe_st8(L + 48 + k, acol[k]); vbe_st8(L + 52 + k, acol[k]); }
    vbe_st8(L + 8, (unsigned)(signed char)-50); vbe_st8(L + 9, 60); vbe_st8(L + 10, 80);
    unsigned w1;
#define G(a, b) (*d++ = (a), *d++ = (b))
    G(0xE7000000, 0);
    G(0xDC080008, (unsigned)(uintptr_t)vp);                     /* gsSPViewport */
    G(0xDA380007, (unsigned)(uintptr_t)mp);                     /* gsSPMatrix projection|load */
    G(0xDA380003, (unsigned)(uintptr_t)mm);                     /* gsSPMatrix modelview|load */
    G(0xD9000000, 0x00220405);                                  /* geometry: zbuffer shade lighting smooth cull_back */
    G(0xDC08000E, 0);                                           /* no normal array until the model sets one */
    G(0xDB020000, 48);                                          /* 1 light */
    G(0xDC080C0A, (unsigned)(uintptr_t)L);                      /* light 0 (offset 2 * 48) */
    G(0xDC08120A, (unsigned)(uintptr_t)(L + 48));               /* ambient (offset 3 * 48) */
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
        gfx_measure_only = 1; measuring = 1;
        gfx_frame_begin(0, 0, 0);
        gfx_bounds_reset();
        gfx_run_dl(build(a, 160, 120, 320, 240, 0));
        gfx_measure_only = 0; measuring = 0;
        if (!gfx_bounds(mn, mx)) { port_log("[gfxdemo] asset rom+0x%X: no vertices\n", a->rom); a->buf = 0; continue; }
        float r = 0;
        for (int i = 0; i < 3; i++) { a->c[i] = (mn[i] + mx[i]) / 2; if ((mx[i] - mn[i]) / 2 > r) r = (mx[i] - mn[i]) / 2; }
        a->r = r * 1.2f;
        if (a->nbones) port_log("[gfxdemo] asset rom+0x%X: %d bones\n", a->rom, a->nbones);
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
        port_log("[gfxdemo] frame: %u commands, %u triangles (%u from Conker TRI4), %u draws, %u texture uploads, %u texture ids unresolved, %u bad addresses, %u lit vertices\n",
                 gfx_stats.cmds - before.cmds, gfx_stats.tris - before.tris, (gfx_stats.tri4 - before.tri4) * 4,
                 gfx_stats.draws - before.draws, gfx_stats.tex_uploads - before.tex_uploads, gfx_stats.tex_ids - before.tex_ids,
                 gfx_stats.bad_addr + gfx_stats.unset_seg - before.bad_addr - before.unset_seg, gfx_stats.lit - before.lit);
}

/* node / test hook: the viewer without a GL context (interpreter + stats only) */
void port_gfx_demo_test(const char *spec) {
    if (gfx_demo_init(spec)) return;
    for (int i = 0; i < 3; i++) gfx_demo_frame();
}

/* P58 ?p58pose=1: preview of the game's posed skeleton. p58_model.c passes record 0's joint matrices (model space)
 * after each evaluation; after each game gfx task the matching ROM model (the viewer asset whose bone table equals the
 * skeleton D_800C5000[id] entry for entry) is drawn in a box on the right with them. Framing from the bind-pose joints. */
static Asset PA;
static int pa_state; /* 0 not tried, 1 ready, -1 none */
static float pa_ang, pa_err;
extern void (*gfx_post_task_hook)(void);
int port_flag(const char *name);
void gfx_overlay_begin(void);
static void p58_pose_draw(void) {
    if (pa_state != 1) return;
    gfx_overlay_begin();
    pose_on = 1;
    gfx_run_dl(build(&PA, 224, 120, 184, 236, pa_ang));
    pose_on = 0;
}
void gfx_pose_overlay_set(const float (*J)[16], int n, const float *root, const unsigned char *skel) {
    (void)root;
    if (n > 72) n = 72;
    memcpy(pose_L, J, sizeof(float) * 16 * n);
    pose_nn = n;
    if (pa_state) return;
    pa_state = -1;
    if (!work) work = calloc(4096, 4);
    if (!bones) bones = calloc(64, 64);
    if (!enddl) { enddl = calloc(0x10000, 1); for (int i = 0; i < 0x10000; i += 8) *(unsigned *)(enddl + i) = 0xDF000000; }
    for (unsigned k = 0; k < sizeof DEF / sizeof DEF[0]; k++) {
        Asset t; memset(&t, 0, sizeof t);
        t.rom = DEF[k][0]; t.dl = DEF[k][1];
        if (load(&t) || t.nbones != n) { free(t.buf); continue; }
        unsigned off = *(unsigned *)(t.buf + 0x10);
        float err = 0;
        for (int i = 0; i < n; i++)
            for (int c = 0; c < 3; c++) {
                float d = fabsf(*(float *)(t.buf + off + 16 * i + 4 + 4 * c) - *(const float *)(skel + 16 * i + 4 + 4 * c));
                if (d > err) err = d;
            }
        port_log("[p58] pose preview: ROM asset 0x%X has %d bones, max bone-offset difference to the game skeleton %g\n",
                 t.rom, t.nbones, err);
        /* the game's skeleton (model asset (1, id)) is not one of these files exactly; the two 28-bone viewer Conkers
         * differ from it by up to 0.006 / 0.003 units, so take the closest one under 0.05 */
        if (err > 0.05f || (pa_state == 1 && err >= pa_err)) { free(t.buf); continue; }
        if (pa_state == 1) free(PA.buf);
        pa_err = err;
        PA = t;
        tex_patch_dl(&PA, PA.dl, 0);
        float mn[3] = {1e9f, 1e9f, 1e9f}, mx[3] = {-1e9f, -1e9f, -1e9f}, r = 0;
        for (int i = 0; i < n; i++) for (int c = 0; c < 3; c++) {
            if (PA.bone[i][c] < mn[c]) mn[c] = PA.bone[i][c];
            if (PA.bone[i][c] > mx[c]) mx[c] = PA.bone[i][c];
        }
        for (int c = 0; c < 3; c++) { PA.c[c] = (mn[c] + mx[c]) / 2; if ((mx[c] - mn[c]) / 2 > r) r = (mx[c] - mn[c]) / 2; }
        PA.r = r * 2.2f + 10;   /* room for poses that reach past the bind-pose bounds */
        pa_state = 1;
        pa_ang = (float)(port_flag("p58ang")) * 0.0174533f;
        gfx_post_task_hook = p58_pose_draw;
        port_log("[p58] pose preview: drawing ROM asset 0x%X DL +0x%X (centre %.1f %.1f %.1f, radius %.1f)\n", PA.rom, PA.dl,
                 PA.c[0], PA.c[1], PA.c[2], PA.r);
    }
    if (pa_state != 1) port_log("[p58] pose preview: no viewer asset matches the %d-joint skeleton\n", n);
}
