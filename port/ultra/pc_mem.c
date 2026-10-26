/* N64 memory model runtime (docs/port/MEMORY.md): segment loader, relocation, address
 * translation, raw-DEFLATE (rzip) inflater, and the helpers that port/tools/vbe.py calls. */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "pc_mem.h"

void port_log(const char *fmt, ...);
extern unsigned char *port_rom;
extern unsigned port_rom_size;

extern const unsigned port_reloc_count, port_functab_count, port_cdata_count;
extern const unsigned port_reloc[];
extern const PortFn port_functab[];
extern const PortCData port_cdata[];

/* ---------------------------------------------------------------- address translation */

static unsigned char *mirror(unsigned a) {
    if ((a >> 29) == 4 || (a >> 29) == 5) { /* KSEG0 / KSEG1 */
        unsigned phys = a & 0x1FFFFFFF;
        return phys < sizeof n64_rdram ? n64_rdram + phys : 0;
    }
    if (a - 0x16000000u < sizeof n64_seg16) return n64_seg16 + (a - 0x16000000u);
    return 0;
}

void *port_n64_to_wasm(unsigned a) {
    if (!a) return 0;
    unsigned lo = 0, hi = port_functab_count;
    while (lo < hi) { /* exact function start */
        unsigned mid = (lo + hi) / 2;
        if (port_functab[mid].n64 < a) lo = mid + 1; else hi = mid;
    }
    if (lo < port_functab_count && port_functab[lo].n64 == a) return port_functab[lo].fn;
    lo = 0, hi = port_cdata_count;
    while (lo < hi) { /* last C object starting <= a */
        unsigned mid = (lo + hi) / 2;
        if (port_cdata[mid].n64 <= a) lo = mid + 1; else hi = mid;
    }
    if (lo && a < port_cdata[lo - 1].n64 + port_cdata[lo - 1].size)
        return (char *)port_cdata[lo - 1].p + (a - port_cdata[lo - 1].n64);
    return mirror(a);
}

unsigned port_wasm_to_n64(const void *p) {
    uintptr_t x = (uintptr_t)p;
    if (x - (uintptr_t)n64_rdram < sizeof n64_rdram) return 0x80000000u + (unsigned)(x - (uintptr_t)n64_rdram);
    if (x - (uintptr_t)n64_seg16 < sizeof n64_seg16) return 0x16000000u + (unsigned)(x - (uintptr_t)n64_seg16);
    return 0;
}

/* ---------------------------------------------------------------- big-endian bytes -> vbe memory */

static inline uint32_t be32(const unsigned char *s) {
    return (uint32_t)s[0] << 24 | (uint32_t)s[1] << 16 | (uint32_t)s[2] << 8 | s[3];
}

/* copy n bytes of big-endian data (ROM order) to game address dst */
static void be_to_vbe(unsigned char *dst, const unsigned char *src, unsigned n) {
    unsigned i = 0;
    if (!((uintptr_t)dst & 3)) {
        for (; i + 4 <= n; i += 4) *(uint32_t *)(dst + i) = be32(src + i);
    }
    for (; i < n; i++) vbe_st8(dst + i, src[i]);
}

void port_rom_read(void *dst, unsigned off, unsigned size) {
    if (!port_rom || off + size > port_rom_size) {
        port_log("[pi] DMA rom+0x%X size 0x%X out of ROM (rom %s)\n", off, size, port_rom ? "loaded" : "missing");
        return;
    }
    be_to_vbe(dst, port_rom + off, size);
}

/* P66: the P58 TEMPORARY PC func_1000480C was removed: the port branch converted it in P62 (init_4470.c,
 * NON_MATCHING). Its CART_WORD loads (`*(vu32 *)(addr | 0xA0000000)`, KSEG1) become __port_io_read(addr) through
 * port/tools/vbe.py's P42 computed-IO_READ rule, which answers the cart domain 0xB0000000.. with the big-endian ROM
 * word (port/ultra/pc_os.c); PI_STATUS_REG reads as idle. */

/* ---------------------------------------------------------------- raw DEFLATE (rzip = BE u32 size + deflate) */

typedef struct {
    const unsigned char *in; unsigned inlen, inpos;
    unsigned bitbuf, bitcnt;
    unsigned char *out; unsigned outlen, outpos;
    int err;
    int vbe; /* P33: game memory in the vbe layout (byte A at A ^ 3); P37: bit 0 = in, bit 1 = out */
} Inf;
#define INB(s, i)  (*(((s)->vbe & 1) ? (const unsigned char *)(((unsigned long)((s)->in + (i))) ^ 3) : (s)->in + (i)))
#define OUTB(s, i) (*(((s)->vbe & 2) ? (unsigned char *)(((unsigned long)((s)->out + (i))) ^ 3) : (s)->out + (i)))
typedef struct { short count[16], symbol[288]; } Huff;

static int bits(Inf *s, int need) {
    unsigned val = s->bitbuf;
    while (s->bitcnt < (unsigned)need) {
        if (s->inpos >= s->inlen) { s->err = 1; return 0; }
        val |= (unsigned)INB(s, s->inpos) << s->bitcnt; s->inpos++;
        s->bitcnt += 8;
    }
    s->bitbuf = val >> need;
    s->bitcnt -= need;
    return (int)(val & ((1u << need) - 1));
}

static int decode(Inf *s, const Huff *h) {
    int code = 0, first = 0, index = 0;
    for (int len = 1; len < 16; len++) {
        code |= bits(s, 1);
        int count = h->count[len];
        if (code - count < first) return h->symbol[index + (code - first)];
        index += count; first += count; first <<= 1; code <<= 1;
        if (s->err) return -1;
    }
    s->err = 2;
    return -1;
}

static void construct(Huff *h, const short *length, int n) {
    short offs[16];
    memset(h->count, 0, sizeof h->count);
    for (int i = 0; i < n; i++) h->count[length[i]]++;
    offs[1] = 0;
    for (int len = 1; len < 15; len++) offs[len + 1] = offs[len] + h->count[len];
    h->count[0] = 0;
    for (int i = 0; i < n; i++) if (length[i]) h->symbol[offs[length[i]]++] = (short)i;
}

static const short LBASE[29] = {3,4,5,6,7,8,9,10,11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227,258};
static const short LEXT[29] = {0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0};
static const short DBASE[30] = {1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193,257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577};
static const short DEXT[30] = {0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13};

static void codes(Inf *s, const Huff *lc, const Huff *dc) {
    for (;;) {
        int sym = decode(s, lc);
        if (s->err) return;
        if (sym < 256) {
            if (s->outpos >= s->outlen) { s->err = 3; return; }
            OUTB(s, s->outpos) = (unsigned char)sym; s->outpos++;
        } else if (sym == 256) {
            return;
        } else {
            sym -= 257;
            if (sym >= 29) { s->err = 4; return; }
            int len = LBASE[sym] + bits(s, LEXT[sym]);
            int ds = decode(s, dc);
            if (ds < 0 || ds >= 30) { s->err = 5; return; }
            unsigned dist = DBASE[ds] + bits(s, DEXT[ds]);
            if (dist > s->outpos || s->outpos + len > s->outlen) { s->err = 6; return; }
            while (len--) { OUTB(s, s->outpos) = OUTB(s, s->outpos - dist); s->outpos++; }
        }
    }
}

static int inflate_raw2(unsigned char *out, unsigned outlen, const unsigned char *in, unsigned inlen, int vbe) {
    static Huff lc, dc;
    Inf st = {in, inlen, 0, 0, 0, out, outlen, 0, 0, vbe}, *s = &st;
    int last;
    do {
        last = bits(s, 1);
        int type = bits(s, 2);
        if (type == 0) {
            s->bitbuf = s->bitcnt = 0;
            if (s->inpos + 4 > s->inlen) return -1;
            unsigned len = INB(s, s->inpos) | INB(s, s->inpos + 1) << 8;
            s->inpos += 4;
            if (s->inpos + len > inlen || s->outpos + len > outlen) return -1;
            while (len--) { OUTB(s, s->outpos) = INB(s, s->inpos); s->outpos++; s->inpos++; }
        } else if (type == 1) {
            static short l[288 + 30];
            int i;
            for (i = 0; i < 144; i++) l[i] = 8;
            for (; i < 256; i++) l[i] = 9;
            for (; i < 280; i++) l[i] = 7;
            for (; i < 288; i++) l[i] = 8;
            construct(&lc, l, 288);
            for (i = 0; i < 30; i++) l[i] = 5;
            construct(&dc, l, 30);
            codes(s, &lc, &dc);
        } else if (type == 2) {
            static const short order[19] = {16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15};
            short lengths[320];
            int nlen = bits(s, 5) + 257, ndist = bits(s, 5) + 1, ncode = bits(s, 4) + 4, idx;
            for (idx = 0; idx < ncode; idx++) lengths[order[idx]] = (short)bits(s, 3);
            for (; idx < 19; idx++) lengths[order[idx]] = 0;
            construct(&lc, lengths, 19);
            for (idx = 0; idx < nlen + ndist;) {
                int sym = decode(s, &lc), len = 0, rep;
                if (s->err) return -1;
                if (sym < 16) { lengths[idx++] = (short)sym; continue; }
                if (sym == 16) { if (!idx) return -1; len = lengths[idx - 1]; rep = 3 + bits(s, 2); }
                else if (sym == 17) rep = 3 + bits(s, 3);
                else rep = 11 + bits(s, 7);
                if (idx + rep > nlen + ndist) return -1;
                while (rep--) lengths[idx++] = (short)len;
            }
            construct(&lc, lengths, nlen);
            construct(&dc, lengths + nlen, ndist);
            codes(s, &lc, &dc);
        } else {
            return -1;
        }
        if (s->err) return -1;
    } while (!last);
    return (int)s->outpos;
}
static int inflate_raw(unsigned char *out, unsigned outlen, const unsigned char *in, unsigned inlen) {
    return inflate_raw2(out, outlen, in, inlen, 0);
}

/* ---------------------------------------------------------------- segment loader */

static const struct { const char *name; unsigned vram, size, rom; int rzip; } SEGS[] = {
    {"init_data", 0x80029400, 0x4410, 0x29400, 0},
    {"game_data", 0x80082EB0, 0x2E320, 0x427B0 + 0x145ED8, 1},
    {"debugger_data", 0x16003700, 0x1658, 0x19EDE8 + (0x259B50 - 0x256450), 0},
};

int port_mem_load(void) {
    if (!port_rom) { port_log("[mem] no ROM\n"); return -1; }
    if ((uintptr_t)n64_rdram < PORT_WASM_BASE || (uintptr_t)port_rom < PORT_WASM_BASE) {
        port_log("[mem] FATAL: wasm data below PORT_WASM_BASE (n64_rdram %p, rom %p): link with -sGLOBAL_BASE=256MB\n",
                 (void *)n64_rdram, (void *)port_rom);
        return -1;
    }
    port_log("[mem] address space: n64_rdram %p, n64_seg16 %p, rom %p (all >= 0x%X; below is null zone + RSP segments)\n",
             (void *)n64_rdram, (void *)n64_seg16, (void *)port_rom, PORT_WASM_BASE);
    for (unsigned i = 0; i < sizeof SEGS / sizeof SEGS[0]; i++) {
        unsigned char *dst = mirror(SEGS[i].vram);
        if (!SEGS[i].rzip) {
            be_to_vbe(dst, port_rom + SEGS[i].rom, SEGS[i].size);
        } else {
            const unsigned char *z = port_rom + SEGS[i].rom;
            unsigned n = be32(z);
            unsigned char *tmp = malloc(n);
            int got = inflate_raw(tmp, n, z + 4, port_rom_size - SEGS[i].rom - 4);
            if (got != (int)SEGS[i].size || n != SEGS[i].size) {
                port_log("[mem] %s: inflate failed (%d of 0x%X)\n", SEGS[i].name, got, n);
                free(tmp);
                return -1;
            }
            be_to_vbe(dst, tmp, n);
            free(tmp);
        }
        port_log("[mem] %s 0x%08X+0x%X -> wasm %p\n", SEGS[i].name, SEGS[i].vram, SEGS[i].size, (void *)dst);
    }
    unsigned bad = 0, nf = 0;
    for (unsigned i = 0; i < port_reloc_count; i++) {
        uint32_t *p = (uint32_t *)mirror(port_reloc[i]);
        void *t = port_n64_to_wasm(*p);
        if (!t) { if (bad++ < 5) port_log("[mem] reloc @%08X: %08X unresolved\n", port_reloc[i], *p); continue; }
        if ((uintptr_t)t < 0x10000) nf++; /* wasm function-table index */
        *p = (uint32_t)(uintptr_t)t;
    }
    port_log("[mem] %u relocations (%u function pointers, %u unresolved), %u C objects, rdram mirror %p\n",
             port_reloc_count, nf, bad, port_cdata_count, (void *)n64_rdram);
    return 0;
}

/* ---------------------------------------------------------------- helpers called by vbe.py-rewritten IR */

unsigned short __vbe_ld16u(const unsigned char *p) { return (unsigned short)(vbe_ld8(p) << 8 | vbe_ld8(p + 1)); }
void __vbe_st16u(unsigned char *p, unsigned short v) { vbe_st8(p, v >> 8); vbe_st8(p + 1, v); }
unsigned __vbe_ld32u(const unsigned char *p) {
    return vbe_ld8(p) << 24 | vbe_ld8(p + 1) << 16 | vbe_ld8(p + 2) << 8 | vbe_ld8(p + 3);
}
void __vbe_st32u(unsigned char *p, unsigned v) { vbe_st8(p, v >> 24); vbe_st8(p + 1, v >> 16); vbe_st8(p + 2, v >> 8); vbe_st8(p + 3, v); }

void __vbe_memcpy(unsigned char *d, const unsigned char *s, unsigned n) {
    unsigned i = 0;
    if (((uintptr_t)d & 3) == ((uintptr_t)s & 3)) {
        for (; i < n && ((uintptr_t)(d + i) & 3); i++) vbe_st8(d + i, vbe_ld8(s + i));
        for (; i + 4 <= n; i += 4) *(uint32_t *)(d + i) = *(const uint32_t *)(s + i);
    }
    for (; i < n; i++) vbe_st8(d + i, vbe_ld8(s + i));
}
void __vbe_memmove(unsigned char *d, const unsigned char *s, unsigned n) {
    if (d <= s || d >= s + n) { __vbe_memcpy(d, s, n); return; }
    while (n--) vbe_st8(d + n, vbe_ld8(s + n));
}
void __vbe_memset(unsigned char *d, unsigned c, unsigned n) {
    unsigned i = 0;
    for (; i < n && ((uintptr_t)(d + i) & 3); i++) vbe_st8(d + i, c);
    for (; i + 4 <= n; i += 4) *(uint32_t *)(d + i) = (c & 0xFF) * 0x01010101u;
    for (; i < n; i++) vbe_st8(d + i, c);
}

/* Convert the 1/2/8-byte scalars of a game global's initialiser (laid out little-endian by clang)
 * to the vbe layout. desc = n x {offset, size, count, stride}. */
void __vbe_fix(unsigned char *g, const unsigned *desc, unsigned n) {
    unsigned end = 0, mysize = desc[0], llsize = desc[1];
    desc += 2;
    if (mysize > ((llsize + 3) & ~3u)) {
        port_log("[vbe] layout mismatch for global at %p: vbe.py %u bytes, LLVM %u; not converted\n", (void *)g, mysize, llsize);
        return;
    }
    for (unsigned i = 0; i < n; i++) {
        const unsigned *d = desc + 4 * i;
        unsigned e = d[0] + (d[2] - 1) * d[3] + d[1];
        if (e > end) end = e;
    }
    end = (end + 3) & ~3u;
    if (end > ((llsize + 3) & ~3u)) {
        port_log("[vbe] descriptor past the end of global at %p (%u > %u); not converted\n", (void *)g, end, llsize);
        return;
    }
    unsigned char *tmp = malloc(end);
    memcpy(tmp, g, end);
    for (unsigned pass = 0; pass < 2; pass++)
        for (unsigned i = 0; i < n; i++) {
            const unsigned *d = desc + 4 * i;
            for (unsigned k = 0; k < d[2]; k++) {
                unsigned o = d[0] + k * d[3], sz = d[1];
                if (pass == 0) { memset(g + (o & ~3u), 0, ((o + sz + 3) & ~3u) - (o & ~3u)); continue; }
                if (sz == 1) vbe_st8(g + o, tmp[o]);
                else if (sz == 2) { unsigned v = tmp[o] | tmp[o + 1] << 8; vbe_st8(g + o, v >> 8); vbe_st8(g + o + 1, v); }
                else { uint64_t v; memcpy(&v, tmp + o, 8); *(uint32_t *)(g + o) = (uint32_t)(v >> 32); *(uint32_t *)(g + o + 4) = (uint32_t)v; }
            }
        }
    free(tmp);
}

/* writes through NULL (+offset) pointers land in wasm 0..GLOBAL_BASE (256 MB, see port/Makefile); only the
 * first 16 MB are scanned, so that the report doesn't fault in the rest of the zone */
void port_mem_null_report(void) {
    const unsigned char *z = (const unsigned char *)0;
    unsigned dirty = 0, first = 0, last = 0;
    for (unsigned a = 0x10; a < PORT_NULL_SCAN; a += 4)
        if (*(const volatile uint32_t *)(z + a)) { if (!dirty++) first = a; last = a; }
    port_log("[mem] null zone: %u dirty words (0x%X..0x%X)\n", dirty, first, last);
    if (dirty && dirty <= 16) /* P11: list them (storage order; game words are native u32) */
        for (unsigned a = 0x10; a < PORT_NULL_SCAN; a += 4)
            if (*(const volatile uint32_t *)(z + a)) port_log("[mem]   null+0x%X = %08X\n", a, *(const volatile uint32_t *)(z + a));
}

/* raw DEFLATE for other PC-side users (ROM asset viewer, port/gfx/gfx_demo.c); returns bytes out */
int port_inflate_raw(unsigned char *out, unsigned outlen, const unsigned char *in, unsigned inlen) {
    return inflate_raw(out, outlen, in, inlen);
}

/* P37: the P33 TEMPORARY PC func_1000654C is gone: Rare's inflater is the game's C (init_eu_5DA0.c, port P36).
 * ?infcheck=1 checks it at run time through a link-time wrapper of its entry func_10006530(src, dst, work)
 * (-Wl,--wrap=func_10006530, port/Makefile; the callers are in other TUs): before the call the stream is inflated
 * here into a host buffer (independent decoder, input read through the vbe layout), then the game's C runs and
 * its return value and output bytes (vbe) are compared with it and with the rzip header's BE u32 size.
 * Lines: [infcheck] per call (first 12 and every mismatch), and a running total every 64 calls. */
int port_flag(const char *name);
void port_js_stack(int skip, int n);
int __real_func_10006530(int src, int dst, unsigned work);
int __wrap_func_10006530(int src, int dst, unsigned work) {
    static int on = -1;
    static unsigned calls, ok, bad, bytes;
    unsigned hw, hdr, cap, i, diff = 0, firstdiff = 0;
    unsigned char *ref;
    int got, ret, good;
    if (on < 0) on = port_flag("infcheck");
    if (!on) return __real_func_10006530(src, dst, work);
    if ((unsigned)src < 0x10000000u || (unsigned)dst < 0x10000000u) { /* not game memory: report, don't decode */
        static int nbad;
        if (nbad++ < 4) {
            extern signed char D_800BC860[]; extern unsigned D_800B1268[];
            unsigned k, nf = 0;
            port_log("[infcheck] bad pointers: src %08X dst %08X work %08X; texture cache entries with flag 0x40:\n",
                     (unsigned)src, (unsigned)dst, work);
            for (k = 0; k < 0x1E54; k++) {
                int age = (signed char)vbe_ld8(&D_800BC860[k]);
                if (age & 0x40 && nf++ < 12)
                    port_log("[infcheck]   id 0x%X age %02X slot %08X\n", k, age & 0xFF, D_800B1268[k]);
            }
            port_log("[infcheck]   %u entries\n", nf);
            { extern int D_800DA378, D_800DA37C; extern unsigned D_800B1268[];
              port_log("[infcheck]   range D_800DA378 %d D_800DA37C %d; D_800BC860 at %p, D_800B1268 at %p\n", D_800DA378, D_800DA37C,
                       (void *)D_800BC860, (void *)D_800B1268);
              for (k = 0; k < 0x200000; k++) if (D_800B1268[k] == (unsigned)dst) {
                  port_log("[infcheck]   slot index %u (age byte %02X)\n", k, vbe_ld8(&D_800BC860[k])); break; } }
            port_js_stack(1, 6);
        }
        return __real_func_10006530(src, dst, work);
    }
    hw = vbe_ld8((void *)(uintptr_t)src) << 8 | vbe_ld8((void *)(uintptr_t)(src + 1));
    hdr = hw == 0x1172 ? 0 : (unsigned)vbe_ld8((void *)(uintptr_t)src) << 24 | vbe_ld8((void *)(uintptr_t)(src + 1)) << 16 |
                             vbe_ld8((void *)(uintptr_t)(src + 2)) << 8 | vbe_ld8((void *)(uintptr_t)(src + 3));
    cap = hdr && hdr < 0x800000 ? hdr : 0x400000;
    ref = malloc(cap);
    got = inflate_raw2(ref, cap, (const unsigned char *)(uintptr_t)(src + (hw == 0x1172 ? 2 : 4)), 0x1000000u, 1);
    ret = __real_func_10006530(src, dst, work);
    if (got > 0 && ret == got)
        for (i = 0; i < (unsigned)got; i++)
            if (vbe_ld8((void *)(uintptr_t)(dst + i)) != ref[i]) { if (!diff++) firstdiff = i; }
    calls++;
    good = got > 0 && ret == got && !diff && (!hdr || (unsigned)ret == hdr);
    if (good) { ok++; bytes += ret; }
    else bad++;
    if (calls <= (on > 1 ? 100000u : 12u) || !good)
        port_log("[infcheck] #%u src %08X dst %08X work %08X: header %u, game C %d, reference %d, %u byte diffs (first +%u)%s\n",
                 calls, (unsigned)src, (unsigned)dst, work, hdr, ret, got, diff, firstdiff,
                 good ? " ok" : " MISMATCH");
    if (calls % 64 == 0) port_log("[infcheck] %u calls: %u ok, %u mismatch, %u bytes\n", calls, ok, bad, bytes);
    free(ref);
    return ret;
}

/* P37 (diagnostic, ?infcheck=1): texture ids outside the cache (>= 0x1E54). texture_cache_lookup stores the id in the dirty
 * range D_800DA378 / D_800DA37C before its range check, and texture_cache_age_tick then walks past the end of its tables. */
int __real_texture_cache_lookup(int id, int *outSize, int age, int addRef);
int __wrap_texture_cache_lookup(int id, int *outSize, int age, int addRef) {
    static int on = -1, n;
    if (on < 0) on = port_flag("infcheck");
    if (on && ((unsigned)id >= 0x1E54) && n++ < 6) {
        port_log("[texid] texture_cache_lookup id 0x%X age %d addRef %d\n", (unsigned)id, age, addRef);
        port_js_stack(1, 5);
    }
    return __real_texture_cache_lookup(id, outSize, age, addRef);
}
/* P37: ?infcheck=2 also logs which level asset level_load_models asks for (to tie inflate calls to the level model list) */
void __real_level_load_models(int level);
void __wrap_level_load_models(int level) {
    static int on = -1;
    if (on < 0) on = port_flag("infcheck");
    if (on > 1) port_log("[infcheck] level loader level_load_models(0x%X) begins\n", level);
    __real_level_load_models(level);
    if (on > 1) port_log("[infcheck] level loader level_load_models(0x%X) ends\n", level);
    if (on && level == 0x21) { /* texture 0xED0 through the game's own cache once the level is loaded (slots are -1 now);
                                * the func_10006530 wrapper checks the C inflater's output against the 768-byte header */
        extern unsigned D_800B1268[];
        int sz = 0, had = D_800B1268[0xED0] != 0xFFFFFFFFu, p = __wrap_texture_cache_lookup(0xED0, &sz, 3, 0);
        port_log("[infcheck] texture 0xED0 via texture_cache_lookup: %s, data %08X size %d\n", had ? "already cached" : "loaded", p, sz);
    }
}
int port_infcheck_on(void) { return port_flag("infcheck"); } /* for the vbe TU game_entry.c (its literals are vbe) */
