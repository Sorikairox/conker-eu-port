/* F3DEX2 display-list interpreter for the browser build (WebGL2). Written for this port
 * (docs/port/sessions/P6.md); no third-party code (port/gfx/LICENSES.md).
 *
 * Entry points
 *   gfx_run_task()  the RSP gfx task path: osSpTaskStartGo(M_GFXTASK) -> here (pc_os.c), so real
 *                   game frames are drawn as soon as the frame builders are C.
 *   gfx_run_dl()    interpret one display list directly (ROM-asset viewer, tests).
 * Memory: display lists, vertices, matrices and textures are read from game memory, which is
 * virtual big-endian (pc_mem.h): Gfx/Mtx words are plain 32-bit loads, Vtx s16 fields vbe_ld16,
 * texture bytes vbe_ld8.
 * Addresses: segmented (seg << 24 | off) through the segment table, N64 KSEG0 pointers through
 * port_n64_to_wasm(), N64 physical (< 8 MB) into the RDRAM mirror, anything >= 16 MB is a wasm
 * pointer that game C code stored (see gfx_addr()). */
#ifndef PORT_GFX_H
#define PORT_GFX_H

typedef struct {
    unsigned tasks, dls, cmds, tris, verts, draws, tex_uploads, unknown_ops, frames;
    unsigned ucode_loads, bad_addr, tri4, tex_ids;
} GfxStats;
extern GfxStats gfx_stats;

int gfx_init(void);                         /* needs the current WebGL2 context (pc_video.c); 0 = ok */
void gfx_frame_begin(float r, float g, float b);
void gfx_frame_end(void);
void gfx_set_segment(int seg, const void *base); /* preset a segment (wasm pointer) */
void gfx_run_dl(const void *dl);
void gfx_run_task(void *task);              /* OSTask * in game memory */
void *gfx_addr(unsigned a);                 /* resolve a display-list address, 0 if invalid */

/* object-space bounds of every vertex loaded since gfx_bounds_reset() (viewer framing) */
void gfx_bounds_reset(void);
int gfx_bounds(float mn[3], float mx[3]);
/* when set, gfx_run_dl only walks the list (vertices, bounds), no drawing */
extern int gfx_measure_only;

/* ROM asset viewer (gfx_demo.c): ?gfxdemo=1 on the page */
void gfx_demo_frame(void);
int gfx_demo_init(const char *spec);

#endif
