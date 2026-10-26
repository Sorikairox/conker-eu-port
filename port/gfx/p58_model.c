/* P58: runtime checks of P51's model path (link-time wraps), and a posed-skeleton preview.
 *
 * ?p58model=N  log the first N calls (then every 256th) of
 *   - func_1503D210 (P51 C model load): arguments, result, D_800D19A0[id] / D_800C5000[id] after;
 *   - func_150A86B0 (P51 C skeleton evaluator, nm_asm/D5E90_anim.c): object, animation state, joint count, remap
 *     slots and the callback table entries they select, the adjustment buffer (how far the 0x1000 scan runs), the
 *     asm stubs reached inside (the callbacks), and a sanity check of the n joint matrices written: finite, the
 *     row norms (scale), the orthogonality of the 3x3 part, the distance to the parent joint against the skeleton's
 *     bone offset (all in the root matrix's frame, i.e. with the root matrix undone).
 * ?p58dump=K   at evaluator call K (of record 0), dump the root matrix and every joint matrix in full.
 * (P61: ?p58noterm is gone with the terminator; see below.)
 * ?p58pose=1   preview: after every game gfx task, draw Conker's ROM model (the P6/P14 viewer asset whose bone table
 *              equals D_800C5000[id]) in a box on the right with the joint matrices of record 0's last evaluation
 *              (gfx_demo.c gfx_pose_overlay). Diagnostic only (P61: the game draws its own model through func_1502CFEC now).
 *
 * P61: the P58 TEMPORARY 0x1000 terminator written before func_150342D0 is removed: func_150342D0 and
 * func_15034B50 are C since port P57 (`*func_15034B50(...) = 0x1000`). The wrap only remembers the record for the
 * evaluator check below, which still measures how far the 0x1000 scan runs (`adjust scan N`). */
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "../ultra/pc_mem.h"

int port_flag(const char *name);
void port_log(const char *fmt, ...);
extern unsigned port_frame_count;
extern void (*port_stub_trace_hook)(const char *name);
extern unsigned D_800D19A0[], D_800C5000[], D_800D1C90[];
extern unsigned char D_800CC2D0[];
extern unsigned D_800C42A8;
extern int D_8008891C;
void func_15036FD8(void);
int func_15037224(void);
void func_1503A8FC(void);
int func_1503A968(void);
void func_1503AAE0(void);
void gfx_pose_overlay_set(const float (*J)[16], int n, const float *root, const unsigned char *skel);

#define REC 0x32C  /* sizeof(struct127), D_800CC2D0[] */
static int fl_model = -1, fl_dump, fl_pose, fl_anim, fl_speed;
static void p58_flags(void) {
    if (fl_model >= 0) return;
    fl_model = port_flag("p58model"); fl_dump = port_flag("p58dump"); 
    fl_pose = port_flag("p58pose"); fl_anim = port_flag("p58anim"); fl_speed = port_flag("p58speed");
}

/* ---- func_1503D210 */
int __real_func_1503D210(int id, int a1, int a2, int a3, int a4);
int __wrap_func_1503D210(int id, int a1, int a2, int a3, int a4) {
    static unsigned calls;
    int r;
    p58_flags();
    r = __real_func_1503D210(id, a1, a2, a3, a4);
    calls++;
    if (fl_model && (calls <= (unsigned)fl_model || calls % 256 == 0)) {
        unsigned id8 = (unsigned)id & 0xFF;
        port_log("[p58] func_1503D210 call %u frame %u: id %d a1 %d a2 %08X a3 %d a4 %d -> %d | D_800D19A0[id] %08X "
                 "D_800C5000[id] %08X D_800D1C90[id] %08X\n", calls, port_frame_count, id, a1, a2, a3, a4, r,
                 D_800D19A0[id8], D_800C5000[id8], D_800D1C90[id8]);
    }
    return r;
}

/* ---- func_150342D0 (P57 C; record for the scan check) */
static int cur_rec = -1;
static unsigned g_scan, g_scan_max, g_edit_ang, g_edit_scl, g_scan_long;
void __real_func_150342D0(void *buf, int rec);
void __wrap_func_150342D0(void *buf, int rec) {
    p58_flags();
    cur_rec = rec;
    __real_func_150342D0(buf, rec);
}

/* ---- func_150A86B0 */
#define NSTUB 16
static const char *st_name[NSTUB];
static unsigned st_n[NSTUB], st_count;
static void p58_hook(const char *name) {
    unsigned i;
    for (i = 0; i < st_count; i++) if (st_name[i] == name || !strcmp(st_name[i], name)) { st_n[i]++; return; }
    if (st_count < NSTUB) { st_name[st_count] = name; st_n[st_count++] = 1; }
}

static float pose_J[72][16], pose_root[16];
static int pose_n;

static void p58_inv_affine(const float *m, float *o) { /* row-vector affine: rows 0-2 = 3x3, row 3 = translation */
    float a = m[0], b = m[1], c = m[2], d = m[4], e = m[5], f = m[6], g = m[8], h = m[9], i = m[10];
    float A = e * i - f * h, B = -(d * i - f * g), C = d * h - e * g;
    float det = a * A + b * B + c * C, k = det != 0 ? 1 / det : 0;
    o[0] = A * k; o[1] = -(b * i - c * h) * k; o[2] = (b * f - c * e) * k; o[3] = 0;
    o[4] = B * k; o[5] = (a * i - c * g) * k;  o[6] = -(a * f - c * d) * k; o[7] = 0;
    o[8] = C * k; o[9] = -(a * h - b * g) * k; o[10] = (a * e - b * d) * k; o[11] = 0;
    for (int j = 0; j < 3; j++) o[12 + j] = -(m[12] * o[j] + m[13] * o[4 + j] + m[14] * o[8 + j]);
    o[15] = 1;
}
static void p58_mul4(const float *a, const float *b, float *r) {
    float t[16];
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++)
        t[i * 4 + j] = a[i * 4] * b[j] + a[i * 4 + 1] * b[4 + j] + a[i * 4 + 2] * b[8 + j] + a[i * 4 + 3] * b[12 + j];
    memcpy(r, t, sizeof t);
}

/* ?p58anim=K (diagnostic): the animation driver anim_start_entry (asm) is a stub, so record 0's animation state
 * (+0x2D0) never gets a header and the evaluator always decodes an empty animation (bind pose). With p58anim, before
 * each evaluation of record 0 the state is filled the way anim_start_entry fills a fresh state for animation K - 1 of
 * the object's bank (from tools/port/difftest/anim_inputs.py, P51): A+0x40 <- the header record dir[key] read raw
 * from the ROM ((size + 15) & ~15 bytes, dir = obj +0x58, key = D_800D1588[id][anim].key), A+0x28 <- the ROM address
 * of the key-frame stream dir[key + 1] (1 when A[0x45] = 0), A+8 = the frame time (advanced by p58speed / 10 per
 * evaluation, default 0.5, wrapping at A[0x43]), A+0x10 = 1, A+0x18 = (f32)A[0x43], A+0x3C = 0. Then the game's C
 * func_1502DB14(A, 0, buf) copies the two key frames by DMA, as func_1502DE74 does just before the evaluator. */
extern unsigned char *port_rom;
extern unsigned port_rom_size;
extern unsigned D_800D1588[];
void func_1502DB14(void *a, int arg1, int arg2);
static unsigned char p58_dbuf[0x340] __attribute__((aligned(16)));
static float p58_t;
static unsigned rom32(unsigned o) { return o + 4 <= port_rom_size ? (unsigned)port_rom[o] << 24 | port_rom[o + 1] << 16 | port_rom[o + 2] << 8 | port_rom[o + 3] : 0; }
static int p58_anim_setup(unsigned char *A, const unsigned char *obj) {
    static int logged;
    unsigned id = vbe_ld8(obj + 4), k = (unsigned)fl_anim - 1;
    const unsigned char *tb = (const unsigned char *)(uintptr_t)D_800D1588[id];
    unsigned dir = *(const unsigned *)(obj + 0x58), key, sfx, hoff, hinfo, soff, hsz, i;
    if (!tb || !dir || !port_rom) return -1;
    key = vbe_ld16(tb + 8 * k); sfx = vbe_ld16(tb + 8 * k + 2);
    if (key == 999 || key >= 30000) return -1;
    hoff = rom32(dir + 8 * key); hinfo = rom32(dir + 8 * key + 4); soff = rom32(dir + 8 * key + 8);
    hsz = (hinfo + 15) & ~15u;
    if (hsz > 0x1D0) hsz = 0x1D0;
    for (i = 0; i < hsz && dir + hoff + i < port_rom_size; i++) vbe_st8(A + 0x40 + i, port_rom[dir + hoff + i]);
    vbe_st16(A + 4, k);
    *(float *)(A + 0x10) = 1.0f;
    *(float *)(A + 0x18) = (float)vbe_ld8(A + 0x43);
    *(float *)(A + 0x20) = 0.0f;
    *(unsigned *)(A + 0x28) = vbe_ld8(A + 0x45) ? dir + soff : 1;
    vbe_st16(A + 0x3C, 0);
    if (p58_t >= (float)vbe_ld8(A + 0x43)) p58_t = 0;
    *(float *)(A + 8) = p58_t;
    p58_t += (fl_speed > 0 ? fl_speed : 5) / 10.0f;
    func_1502DB14(A, 0, (int)(uintptr_t)p58_dbuf);
    if (logged < 4) {
        char hb[200], db[200]; int q = 0, r = 0;
        const unsigned char *d = (const unsigned char *)(uintptr_t)*(unsigned *)(A + 0x30);
        for (i = 0; i < 48; i++) q += snprintf(hb + q, sizeof hb - q, "%02X", vbe_ld8(A + 0x40 + i));
        for (i = 0; i < 48 && d; i++) r += snprintf(db + r, sizeof db - r, "%02X", vbe_ld8(d + i));
        port_log("[p58] anim t %g: header %s | +30 data %s\n", *(float *)(A + 8), hb, db);
    }
    if (!logged++)
        port_log("[p58] anim setup: id %02X anim %u key %u sfx %u dir rom %08X header rom %08X size %u stream rom %08X | "
                 "A[0x41] channels+1 %u A[0x43] frames %u A[0x45] key bytes %u A[0x47] %02X A[0x48] %u | +30 %08X +38 %u\n",
                 id, k, key, sfx, dir, dir + hoff, hinfo, dir + soff, vbe_ld8(A + 0x41), vbe_ld8(A + 0x43), vbe_ld8(A + 0x45),
                 vbe_ld8(A + 0x47), vbe_ld8(A + 0x48), *(unsigned *)(A + 0x30), vbe_ld8(A + 0x38));
    return 0;
}

void __real_func_150A86B0(int *arena, float (*m)[4], int anim, int skel, int n, unsigned char *buf, unsigned char *remap, int h);
void __wrap_func_150A86B0(int *arena, float (*m)[4], int anim, int skel, int n, unsigned char *buf, unsigned char *remap, int h) {
    static unsigned calls, rec0calls;
    unsigned char *a0 = (unsigned char *)(uintptr_t)*(unsigned *)arena;
    const unsigned char *sk = (const unsigned char *)(uintptr_t)skel;
    int rec = cur_rec, log, i, j;
    unsigned scan = 0, ang = 0, scl = 0, maxoff = 0;
    float root[16];
    p58_flags();
    cur_rec = -1;
    calls++;
    if (rec == 0) rec0calls++;
    log = fl_model && (calls <= (unsigned)fl_model || calls % 256 == 0);
    if (log && calls == 1) { void p58_check_cbtable(void); p58_check_cbtable(); }
    if (fl_anim && rec == 0 && anim) p58_anim_setup((unsigned char *)(uintptr_t)anim, D_800CC2D0);
    memcpy(root, m, 64);
    /* the adjustment scan exactly as the evaluator does it (u16 pairs until 0x1000), bounded */
    if (buf) {
        for (scan = 0; scan < 65536; scan++) {
            unsigned o = vbe_ld16(buf + 4 * scan);
            if (o == 0x1000) break;
            if (o < 0x800) ang++; else scl++;
            if ((o & 0x7FF) > maxoff) maxoff = o & 0x7FF;
        }
        g_scan += scan; if (scan > g_scan_max) g_scan_max = scan; g_edit_ang += ang; g_edit_scl += scl;
        if (scan >= 65536) g_scan_long++;
    }
    st_count = 0;
    { void (*prev_hook)(const char *) = port_stub_trace_hook; /* P88: restore, don't clear (?p88watch) */
    port_stub_trace_hook = p58_hook;
    __real_func_150A86B0(arena, m, anim, skel, n, buf, remap, h);
    port_stub_trace_hook = prev_hook; }
    if (!fl_model && !fl_pose) return;
    /* the joint matrices: model space (root matrix undone); column 3 is never written by the evaluator */
    {
        float inv[16], L[72][16], W[16];
        int bad = 0, nn = n > 72 ? 72 : n, parent_ok = 0, parent_n = 0;
        float wmin = 1e30f, wmax = 0, smin = 1e30f, smax = 0, orth = 0, derr = 0, rootlen = 0;
        int nf = anim ? nn : 1;
        p58_inv_affine(root, inv);
        rootlen = sqrtf(root[0] * root[0] + root[1] * root[1] + root[2] * root[2]);
        for (i = 0; i < nf; i++) {
            memcpy(W, a0 + 64 * i, 64);
            W[3] = W[7] = W[11] = 0; W[15] = 1;
            for (j = 0; j < 16; j++) if (!isfinite(W[j])) bad++;
            for (j = 0; j < 3; j++) {
                float s = sqrtf(W[4 * j] * W[4 * j] + W[4 * j + 1] * W[4 * j + 1] + W[4 * j + 2] * W[4 * j + 2]);
                if (s < wmin) wmin = s;
                if (s > wmax) wmax = s;
            }
            p58_mul4(W, inv, L[i]);
            for (j = 0; j < 3; j++) {
                float *r = L[i] + 4 * j, s = sqrtf(r[0] * r[0] + r[1] * r[1] + r[2] * r[2]);
                if (s < smin) smin = s;
                if (s > smax) smax = s;
            }
            for (j = 0; j < 3; j++) {
                float *p = L[i] + 4 * j, *q = L[i] + 4 * ((j + 1) % 3);
                float sp = sqrtf(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]), sq = sqrtf(q[0] * q[0] + q[1] * q[1] + q[2] * q[2]);
                float d = sp > 0 && sq > 0 ? fabsf(p[0] * q[0] + p[1] * q[1] + p[2] * q[2]) / (sp * sq) : 1;
                if (d > orth) orth = d;
            }
        }
        /* bone length check: skeleton entry k {u8 parent slot, u8 slot, u8 channel, 0, f32 x y z}: the distance from
         * the parent's joint origin to this joint's equals |offset| x the parent's scale (when the animation adds no
         * translation offset to the bone) */
        if (anim && sk) for (i = 1; i < nn; i++) {
            const unsigned char *e = sk + 16 * i;
            unsigned ps = vbe_ld8(e), s = vbe_ld8(e + 1);
            float ox = *(const float *)(e + 4), oy = *(const float *)(e + 8), oz = *(const float *)(e + 12);
            float ol = sqrtf(ox * ox + oy * oy + oz * oz);
            if (ps >= (unsigned)nn || s >= (unsigned)nn) continue;
            float dx = L[s][12] - L[ps][12], dy = L[s][13] - L[ps][13], dz = L[s][14] - L[ps][14];
            float dl = sqrtf(dx * dx + dy * dy + dz * dz);
            float *pr = L[ps];
            float psc = sqrtf(pr[0] * pr[0] + pr[1] * pr[1] + pr[2] * pr[2]);
            float err = fabsf(dl - ol * psc);
            parent_n++;
            if (err <= 0.01f * (ol * psc) + 0.05f) parent_ok++;
            if (err > derr) derr = err;
        }
        {   /* model-space rotation of each joint against the root (bind pose = 0) and its change since the last
             * evaluation of record 0 (a continuous animation changes little per step) */
            static float prevL[72][16]; static int prevn;
            float amax = 0, dmax = 0;
            for (i = 0; i < nf && anim; i++) {
                float *q = L[i], sc[3], tr = 0, td = 0;
                for (j = 0; j < 3; j++) { sc[j] = sqrtf(q[4*j]*q[4*j] + q[4*j+1]*q[4*j+1] + q[4*j+2]*q[4*j+2]); if (sc[j] == 0) sc[j] = 1; }
                for (j = 0; j < 3; j++) tr += q[5 * j] / sc[j];
                float c = (tr - 1) / 2; c = c > 1 ? 1 : c < -1 ? -1 : c;
                if (acosf(c) > amax) amax = acosf(c);
                if (rec == 0 && prevn == nf) {
                    for (j = 0; j < 3; j++) { float *pp = prevL[i] + 4 * j, *qq = q + 4 * j;
                        float ps = sqrtf(pp[0]*pp[0] + pp[1]*pp[1] + pp[2]*pp[2]); if (ps == 0) ps = 1;
                        td += (pp[0]*qq[0] + pp[1]*qq[1] + pp[2]*qq[2]) / (ps * sc[j]); }
                    c = (td - 1) / 2; c = c > 1 ? 1 : c < -1 ? -1 : c;
                    if (acosf(c) > dmax) dmax = acosf(c);
                }
            }
            if (rec == 0 && anim) { memcpy(prevL, L, sizeof(float) * 16 * nf); prevn = nf; }
            if (log) port_log("[p58]   rotation: max joint angle vs root %.1f deg, max change since the previous record-0 "
                              "evaluation %.2f deg, frame time %g\n", amax * 57.29578f, dmax * 57.29578f,
                              anim ? *(float *)(uintptr_t)(anim + 8) : 0);
        }
        if (log) {
            const unsigned char *ob = rec >= 0 ? D_800CC2D0 + REC * rec : 0;
            char rb[200]; int k = 0;
            if (remap) for (i = 0; i < nn && k < 180; i++) if (vbe_ld8(remap + i))
                k += snprintf(rb + k, sizeof rb - k, " slot%d->%u", i, vbe_ld8(remap + i));
            rb[k] = 0;
            char sb[300]; int q = 0;
            for (i = 0; i < (int)st_count && q < 280; i++) q += snprintf(sb + q, sizeof sb - q, " %s x%u", st_name[i], st_n[i]);
            sb[q] = 0;
            port_log("[p58] func_150A86B0 call %u frame %u: rec %d id %02X anim %08X (cnt %u, time %g, desc b6/7 %02X%02X) "
                     "skel %08X n %d arena %08X h %d | adjust scan %u (angle %u, scale %u, max off %X)%s | remap%s | "
                     "stubs inside:%s\n", calls, port_frame_count, rec, ob ? vbe_ld8(ob + 4) : 0xFF, anim,
                     anim ? vbe_ld8((unsigned char *)(uintptr_t)anim + 0x41) : 0, anim ? *(float *)(uintptr_t)(anim + 8) : 0,
                     anim ? vbe_ld8((unsigned char *)(uintptr_t)anim + 0x46) : 0, anim ? vbe_ld8((unsigned char *)(uintptr_t)anim + 0x47) : 0,
                     skel, n, (unsigned)(uintptr_t)a0, h, scan, ang, scl, maxoff, "",
                     rb[0] ? rb : " none", q ? sb : " none");
            port_log("[p58]   joints: %d non-finite floats; model-space row norms %.4f..%.4f, max |cos| between axes %.5f; "
                     "bone lengths %d/%d match the skeleton (max err %.3f); root scale %.4f, root pos %.2f %.2f %.2f; "
                     "joint0 model pos %.2f %.2f %.2f; world row norms %.4f..%.4f; root rows %g %g %g | %g %g %g | %g %g %g\n", bad, smin, smax, orth, parent_ok, parent_n, derr, rootlen,
                     root[12], root[13], root[14], L[0][12], L[0][13], L[0][14], wmin, wmax, root[0], root[1], root[2], root[4],
                     root[5], root[6], root[8], root[9], root[10]);
        }
        if (fl_dump && rec == 0 && rec0calls == (unsigned)fl_dump) {
            port_log("[p58dump] record 0 evaluation %u frame %u: root matrix (rows) | then per skeleton entry: parent slot "
                     "channel offset | world rows 0-2, translation\n", rec0calls, port_frame_count);
            port_log("[p58dump] root %g %g %g | %g %g %g | %g %g %g | %g %g %g\n", root[0], root[1], root[2], root[4],
                     root[5], root[6], root[8], root[9], root[10], root[12], root[13], root[14]);
            for (i = 0; i < nn && sk; i++) {
                const unsigned char *e = sk + 16 * i;
                const float *w = (const float *)(a0 + 64 * vbe_ld8(e + 1));
                port_log("[p58dump] e%02d par %3u slot %2u ch %2u off %8.3f %8.3f %8.3f | %8.4f %8.4f %8.4f | %8.4f %8.4f %8.4f | "
                         "%8.4f %8.4f %8.4f | %9.3f %9.3f %9.3f\n", i, vbe_ld8(e), vbe_ld8(e + 1), vbe_ld8(e + 2),
                         *(const float *)(e + 4), *(const float *)(e + 8), *(const float *)(e + 12), w[0], w[1], w[2], w[4],
                         w[5], w[6], w[8], w[9], w[10], w[12], w[13], w[14]);
            }
        }
        if (rec == 0 && anim && nn > 1) {
            memcpy(pose_J, L, sizeof(float) * 16 * nn);
            memcpy(pose_root, root, sizeof pose_root);
            pose_n = nn;
            if (fl_pose) gfx_pose_overlay_set((const float (*)[16])pose_J, pose_n, pose_root, sk);
        }
    }
    if (fl_model && calls % 1024 == 0)
        port_log("[p58] after %u evaluator calls: adjustment scans total %u entries, longest %u, %u angle / %u scale edits, "
                 "%u scans past 65536 entries\n", calls, g_scan, g_scan_max, g_edit_ang, g_edit_scl, g_scan_long);
}

/* the callback table: one log line at the first evaluator log, from the table words in game memory */
void p58_check_cbtable(void) {
    static const struct { void *f; const char *n; } fn[] = {
        {(void *)func_15036FD8, "func_15036FD8"}, {(void *)func_15037224, "func_15037224"},
        {(void *)func_1503A8FC, "func_1503A8FC"}, {(void *)func_1503A968, "func_1503A968"},
        {(void *)func_1503AAE0, "func_1503AAE0"}};
    const unsigned *t = (const unsigned *)&D_8008891C;
    for (int k = 1; k <= 5; k++) {
        const char *nm = "?";
        for (unsigned i = 0; i < 5; i++) if ((unsigned)(uintptr_t)fn[i].f == t[2 * k]) nm = fn[i].n;
        port_log("[p58] jtbl_8008891C_game[%d] = {%08X, %u} -> %s\n", k, t[2 * k], t[2 * k + 1], nm);
    }
}
