#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_10005DA0 */

/* P281: readable C for tlb_area_init (Rare hand asm, 55 insns, with the private entry func_10005E2C = the retry
   label). The two COP0 writes (Context = 0, Wired = 2: two wired TLB entries) have no C form; the port has no TLB
   and its platform layer does the boot setup (tools/port/platform_replaced.tsv). */
extern s16 D_8003C218;           /* size of the code / TLB area in 4 KB pages */
extern u8 *D_8003C21C;           /* last byte of the page bitmap */
extern s16 D_8003C220;
extern s16 D_8003C222;
s32 allocate_memory(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
// tlb_area_init: reserves `pages` 4 KB pages (falling back to the previous page count, and retrying it for as long
// as that fails), keeps the area's physical address in D_8003BE74 and allocates its page bitmap (one bit per page,
// D_8003BE70 .. D_8003C21C).
/* was func_10005B04 */
void tlb_area_init(s32 pages) {
    s16 prev;
    s32 area;

    /* COP0: Context = 0, Wired = 2 */
    D_8003C220 = 0x1FC;
    D_8003C222 = 0x3FF;
    prev = D_8003C218;
    while (TRUE) {
        D_8003C218 = pages;
        area = heap_alloc_tagged(pages << 12, 0xFF, 4, 1, 2);
        if (area != 0) {
            break;
        }
        pages = prev;
    }
    D_8003BE74 = area & 0x0FFFFFFF;
    D_8003BE70 = allocate_memory((D_8003C218 + 7) >> 3, 0xFF, 0, 0);
    D_8003C21C = (u8 *) D_8003BE70 + ((D_8003C218 + 7) >> 3) - 1;
}

extern s16 D_8003C218;
extern u8 *D_8003C21C;

/* fill the bitmap [D_8003BE70, D_8003C21C] with 0xFF, then mask the bits past the end in the last byte */
/* was func_10005BE0 */
void tlb_page_bitmap_reset(void) {
    u8 *p = (u8 *)D_8003BE70;
    s32 n;

    do {
        *p = 0xFF;
    } while (p++ != D_8003C21C);
    n = D_8003C218 & 7;
    if (n != 0) {
        *D_8003C21C = (2 << (n - 1)) - 1;
    }
}
/* was func_10005F1C */

/* was func_100061F8 */

/* thin wrapper: a0..a2 pass through untouched, v0 comes back from rzip_inflate_impl */
s32 rzip_inflate_impl();

/* was func_10006530 */
s32 rzip_inflate(s32 arg0, s32 arg1, u32 arg2) {
    return rzip_inflate_impl(arg0, arg1, arg2);
}
/* P36: Rare's inflater (init_eu_5DA0, hand-written asm 0x1000654C-0x100074B8), C for the whole set:
 * rzip_inflate_impl (entry), rzip_inflate_loop (block loop), rzip_inflate_block (block header), rzip_inflate_dynamic (dynamic block),
 * rzip_inflate_stored (stored block), rzip_inflate_fixed (fixed block), rzip_huft_build (huft_build), rzip_inflate_codes
 * (inflate_codes) and rzip_build_fixed_tables (builds the fixed tables at D_8003C230). It is Mark Adler's gzip inflate.c
 * (huft tables, 4-byte entries {e, b, v}) with the state in registers: $s7 input pointer, $gp bit buffer, $fp bit
 * count, $f16 output base, $f17 output count, $f18 output limit, $f19 next free table entry, $s6 table base.
 * The inner glabels (func_100065E0, func_10006708, func_10006A40, func_10006B0C, func_10006F30, func_10006FA8,
 * func_10006FAC, func_10007038, func_10007064, func_100070AC, func_1000711C, func_10007120) are branch targets.
 * Differences from gzip, kept here: no "n = x[g]" and no over-subscribed check in huft_build (y < 0), the first
 * huft_build of a dynamic block is not checked, a fixed block never fails (inflate_codes' error is dropped),
 * literals are not bounds-checked, and copies / stored blocks fail unless count + n < limit (strict).
 * Tables are built at the third argument (the work area, D_8003809C in the callers); the output limit is
 * 0x70000000, src - dst when src is above dst, and work - dst when that is >= 0 and smaller.
 * Returns the output length, 0 on an error. Verified whole: tools/port/difftest/nmasm_inflate.py (P36). */
typedef struct {
    u8 e; /* 16: literal, 15: end of block, 99: invalid, > 16: link (e - 16 bits), else extra bits */
    u8 b; /* bits of this code */
    u16 v; /* literal / base value, or the link's table index (from the table base) */
} InfHuft;

/* the asm's 0xA88-byte frame of rzip_inflate_impl, shared by all helpers (huft_build reads stale v[] entries for
 * incomplete codes, so the C keeps the same single frame and layout) */
typedef struct {
    s32 c[17];         /* sp+0x000 */
    InfHuft *u[16];    /* sp+0x044 */
    s32 v[288];        /* sp+0x084 */
    s32 x[17];         /* sp+0x504 */
    s32 ll[286 + 30];  /* sp+0x548 */
} InfFrame;

typedef struct {
    InfFrame *fr;
    u8 *in;        /* $s7 */
    u32 bb;        /* $gp */
    s32 bk;        /* $fp */
    u8 *out;       /* $f16 */
    s32 outcnt;    /* $f17 */
    s32 limit;     /* $f18 */
    s32 hufts;     /* $f19 */
    InfHuft *base; /* $s6 */
} InfState;

extern u16 D_8002C420[]; /* mask_bits[17] */
extern u16 D_8002C442[]; /* cplens */
extern u16 D_8002C480[]; /* cpdist */
extern u8 D_8002C4BC[];  /* border[19] */
extern u8 D_8002C4CF[];  /* cplext */
extern u8 D_8002C4EE[];  /* cpdext */
extern InfHuft D_8003C230[]; /* fixed tables: literal at [1], distance at [0x272] (D_8003CBF8) */

#define INF_NEED(s, n) \
    while ((s)->bk < (s32)(n)) { (s)->bb |= (u32)*(s)->in++ << ((s)->bk & 31); (s)->bk += 8; }
#define INF_DUMP(s, n) \
    { (s)->bb >>= ((n) & 31); (s)->bk -= (n); }

/* rzip_huft_build: huft_build(b, n, s, d, e, t, m); t and m are the asm's $t8 / $t9. rv is the caller's $gp: the
 * value field of an e = 99 entry is whatever $gp held last (never reached: p stays below v + n). */
static s32 inf_build(InfState *s, s32 *b, s32 n, s32 sv, u16 *d, u8 *ex, u16 *t, s32 *m, u32 rv) {
    s32 *c = s->fr->c;
    InfHuft **u = s->fr->u;
    s32 *v = s->fr->v;
    s32 *x = s->fr->x;
    s32 a, f, g, h, j, k, l, w, y, z, hufts, idx;
    u32 i, re, rb;
    s32 *p;
    s32 *xp;
    InfHuft *q;
    InfHuft r;

    if (n == 0) {
        return 1;
    }
    hufts = s->hufts;
    for (j = 0; j < 17; j++) {
        c[j] = 0;
    }
    p = b;
    j = n;
    do {
        c[*p++]++;
    } while (--j != 0);
    if (c[0] == n) {
        *t = 0;
        *m = 0;
        return 0;
    }
    l = *m;
    k = 1;
    while (c[k] == 0) {
        if (k == 16) {
            k = 17;
            break;
        }
        k++;
    }
    if (l < k) {
        l = k;
    }
    i = 16;
    while (c[i] == 0) {
        if (--i == 0) {
            break;
        }
    }
    g = i;
    if ((s32) i < l) {
        l = i;
    }
    *m = l;
    y = 1 << k;
    for (j = k; j < (s32) i; j++) {
        y -= c[j];
        y <<= 1;
    }
    a = c[i];
    c[i] = y;
    y -= a;
    x[1] = 0;
    j = 0;
    p = &c[1];
    xp = &x[2];
    while (--i != 0) {
        *xp++ = (j += *p++);
    }
    p = b;
    i = 0;
    do {
        if ((j = *p++) != 0) {
            v[x[j]++] = i;
        }
    } while ((s32) ++i < n);
    x[0] = 0;
    i = 0;
    p = v;
    h = -1;
    w = -l;
    u[0] = NULL;
    z = 0;
    q = NULL;
    re = 0;
    rb = 0;
    for (; k <= g; k++) {
        a = c[k];
        while (a-- != 0) {
            while (k > w + l) {
                h++;
                w += l;
                z = g - w;
                if (l < z) {
                    z = l;
                }
                j = k - w;
                f = 1 << j;
                if (a + 1 < f) {
                    f -= a + 1;
                    xp = &c[k];
                    while (++j < z) {
                        if ((f <<= 1) <= *++xp) {
                            break;
                        }
                        f -= *xp;
                    }
                }
                z = 1 << j;
                q = s->base + hufts;
                *t = hufts + 1;
                t = &q->v;
                *t = 0;
                q++;
                u[h] = q;
                if (h != 0) {
                    x[h] = i;
                    rb = l;
                    re = j + 16;
                    rv = hufts + 1;
                    idx = i >> ((w - l) & 31);
                    u[h - 1][idx].e = re;
                    u[h - 1][idx].b = rb;
                    u[h - 1][idx].v = rv;
                }
                hufts += z + 1;
            }
            rb = k - w;
            if (p >= v + n) {
                re = 99;
            } else if (*p < sv) {
                rv = *p;
                re = (*p < 256) ? 16 : 15;
                p++;
            } else {
                re = ex[*p - sv];
                rv = d[*p - sv];
                p++;
            }
            r.e = re;
            r.b = rb;
            r.v = rv;
            f = 1 << ((k - w) & 31);
            for (j = i >> (w & 31); j < z; j += f) {
                q[j] = r;
            }
            for (j = 1 << ((k - 1) & 31); i & j; j = (u32) j >> 1) {
                i ^= j;
            }
            i ^= j;
            while ((i & ((1 << (w & 31)) - 1)) != (u32) x[h]) {
                h--;
                w -= l;
            }
        }
    }
    s->hufts = hufts;
    return (y != 0) && (g != 1);
}

/* rzip_inflate_codes: inflate_codes(tl, td, bl, bd); links index from the table base. */
static s32 inf_codes(InfState *s, InfHuft *tl, InfHuft *td, s32 bl, s32 bd) {
    u8 *out = s->out;
    s32 lim = s->limit;
    s32 w = s->outcnt;
    u32 ml = D_8002C420[bl];
    u32 md = D_8002C420[bd];
    InfHuft *t;
    s32 e, n, d;
    u8 *src;
    u8 *dp;
    u8 *end;

    for (;;) {
        INF_NEED(s, bl);
        t = tl + (s->bb & ml);
        e = t->e;
        while (e > 16) {
            if (e == 99) {
                return 1;
            }
            e -= 16;
            INF_DUMP(s, t->b);
            INF_NEED(s, e);
            t = s->base + ((s->bb & D_8002C420[e]) + t->v);
            e = t->e;
        }
        INF_DUMP(s, t->b);
        if (e == 16) {
            out[w++] = t->v;
            continue;
        }
        if (e == 15) {
            s->outcnt = w;
            return 0;
        }
        INF_NEED(s, e);
        n = (s->bb & D_8002C420[e]) + t->v;
        INF_DUMP(s, e);
        INF_NEED(s, bd);
        t = td + (s->bb & md);
        e = t->e;
        while (e > 16) {
            if (e == 99) {
                return 1;
            }
            e -= 16;
            INF_DUMP(s, t->b);
            INF_NEED(s, e);
            t = s->base + ((s->bb & D_8002C420[e]) + t->v);
            e = t->e;
        }
        INF_DUMP(s, t->b);
        INF_NEED(s, e);
        d = w - (s32) (s->bb & D_8002C420[e]) - t->v;
        INF_DUMP(s, e);
        if (!(w + n < lim)) {
            return 1;
        }
        src = out + d;
        dp = out + w;
        w += n;
        end = out + w;
        do {
            *dp++ = *src++;
        } while (dp != end);
    }
}

/* rzip_inflate_stored: stored block */
static s32 inf_stored(InfState *s) {
    s32 w = s->outcnt;
    s32 n, k;
    u8 *p;

    k = s->bk & 7;
    INF_DUMP(s, k);
    INF_NEED(s, 16);
    n = s->bb & 0xFFFF;
    INF_DUMP(s, 16);
    INF_NEED(s, 16);
    if (n != (s32) (~s->bb & 0xFFFF)) {
        return 1;
    }
    INF_DUMP(s, 16);
    if (!(w + n < s->limit)) {
        return 1;
    }
    p = s->out + w;
    w += n;
    while (n-- != 0) {
        INF_NEED(s, 8);
        *p++ = s->bb;
        INF_DUMP(s, 8);
    }
    s->outcnt = w;
    return 0;
}

/* rzip_inflate_fixed: fixed block (tables from rzip_build_fixed_tables); the asm returns 0 whatever inflate_codes returns */
static s32 inf_fixed(InfState *s) {
    InfHuft *save = s->base;

    s->base = D_8003C230;
    inf_codes(s, D_8003C230 + 1, D_8003C230 + 0x272, 7, 5);
    s->base = save;
    return 0;
}

/* rzip_inflate_dynamic: dynamic block (code lengths at the asm's sp+0x548, tl / td / bl / bd at sp+0xA38..0xA40) */
static s32 inf_dynamic(InfState *s) {
    s32 *ll = s->fr->ll;
    s32 nl, nd, nb, n, i, j, l, idx;
    u16 tl, td;
    s32 bl, bd;
    u32 mask;
    InfHuft *t;

    INF_NEED(s, 14);
    nl = (s->bb & 0x1F) + 257;
    nd = ((s->bb & 0x3E0) >> 5) + 1;
    nb = ((s->bb & 0x3C00) >> 10) + 4;
    INF_DUMP(s, 14);
    if (nl >= 287 || nd >= 31) {
        return 1;
    }
    j = 0;
    do {
        INF_NEED(s, 3);
        ll[D_8002C4BC[j]] = s->bb & 7;
        INF_DUMP(s, 3);
        j++;
    } while (j < nb);
    for (; j < 19; j++) {
        ll[D_8002C4BC[j]] = 0;
    }
    bl = 7;
    inf_build(s, ll, 19, 19, NULL, NULL, &tl, &bl, s->bb); /* result not checked */
    mask = D_8002C420[bl];
    n = nl + nd;
    i = 0;
    l = 0;
    idx = 0;
    while (i < n) {
        INF_NEED(s, bl);
        idx = (s->bb & mask) + tl;
        t = s->base + idx;
        INF_DUMP(s, t->b);
        j = t->v;
        if (j < 16) {
            ll[i++] = l = j;
        } else if (j == 16) {
            INF_NEED(s, 2);
            j = (s->bb & 3) + 3;
            INF_DUMP(s, 2);
            if (n < i + j) {
                return 1;
            }
            do {
                ll[i++] = l;
            } while (--j != 0);
        } else if (j == 17) {
            INF_NEED(s, 3);
            j = (s->bb & 7) + 3;
            INF_DUMP(s, 3);
            if (n < i + j) {
                return 1;
            }
            do {
                ll[i++] = 0;
            } while (--j != 0);
            l = 0;
        } else {
            INF_NEED(s, 7);
            j = (s->bb & 0x7F) + 11;
            INF_DUMP(s, 7);
            if (n < i + j) {
                return 1;
            }
            do {
                ll[i++] = 0;
            } while (--j != 0);
            l = 0;
        }
    }
    td = idx;
    bl = 9;
    if (inf_build(s, ll, nl, 257, D_8002C442, D_8002C4CF, &tl, &bl, s->bb) != 0) {
        return 1;
    }
    bd = 6;
    if (inf_build(s, ll + nl, nd, 0, D_8002C480, D_8002C4EE, &td, &bd, s->bb) != 0) {
        return 1;
    }
    if (inf_codes(s, s->base + tl, s->base + td, bl, bd) != 0) {
        return 1;
    }
    return 0;
}

/* rzip_inflate_block: one block (header bits: last, type) */
static s32 inf_block(InfState *s, s32 *last) {
    s32 type;

    INF_NEED(s, 3);
    *last = s->bb & 1;
    type = (s->bb >> 1) & 3;
    INF_DUMP(s, 3);
    if (type == 2) {
        return inf_dynamic(s);
    }
    if (type == 0) {
        return inf_stored(s);
    }
    if (type == 1) {
        return inf_fixed(s);
    }
    return 2;
}

/* rzip_inflate_impl (+ rzip_inflate_loop): src = packed record (BE u32 size, or the BE halfword 0x1172), dst, work area */
/* was func_1000654C */
s32 rzip_inflate_impl(s32 src, s32 dst, u32 work) {
    InfFrame fr;
    InfState st;
    s32 lim, d, last;
    u8 *in = (u8 *) src;

    st.fr = &fr;
    st.in = in + 2;
    if (((in[0] << 8) | in[1]) != 0x1172) {
        st.in += 2;
    }
    st.out = (u8 *) dst;
    st.base = (InfHuft *) work;
    lim = 0x70000000;
    d = src - dst;
    if (d > 0) {
        lim = d;
    }
    d = work - dst;
    if (d >= 0 && d < lim) {
        lim = d;
    }
    st.limit = lim;
    st.outcnt = 0;
    st.bb = 0;
    st.bk = 0;
    do {
        st.hufts = 0;
        if (inf_block(&st, &last) != 0) {
            return 0;
        }
    } while (last == 0);
    return st.outcnt;
}

/* rzip_build_fixed_tables: the fixed literal / distance tables at D_8003C230 (inflate_fixed's setup, run once at boot) */
/* was func_1000738C */
void rzip_build_fixed_tables(void) {
    InfFrame fr;
    InfState st;
    s32 *l = fr.ll;
    u16 t;
    s32 m;
    s32 i;

    st.fr = &fr;
    st.hufts = 0;
    st.base = D_8003C230;
    for (i = 0; i < 144; i++) {
        l[i] = 8;
    }
    for (; i < 256; i++) {
        l[i] = 9;
    }
    for (; i < 280; i++) {
        l[i] = 7;
    }
    for (; i < 288; i++) {
        l[i] = 8;
    }
    m = 7;
    inf_build(&st, l, 288, 257, D_8002C442, D_8002C4CF, &t, &m, 0);
    for (i = 0; i < 30; i++) {
        l[i] = 5;
    }
    m = 5;
    inf_build(&st, l, 30, 0, D_8002C480, D_8002C4EE, &t, &m, 0);
}

/* C: see rzip_inflate_impl above (P36) */

/* C: see rzip_inflate_impl above (P36) */

/* C: see rzip_inflate_impl above (P36) */

/* C: see rzip_inflate_impl above (P36) */

/* C: see rzip_inflate_impl above (P36) */

/* C: see rzip_inflate_impl above (P36) */

/* C: see rzip_inflate_impl above (P36) */

/* C: see rzip_inflate_impl above (P36) */


/* was func_10007AA8 */

/* was func_10007CC8 */
void os_enqueue_thread(s32 *arg0, s32 *arg1) {
    s32 *var_t8;
    s32 *var_t9;
    s32 temp_t7;

    var_t9 = arg0;
    var_t8 = *arg0;
    temp_t7 = (*(s32 *)((u8 *)arg1 + 4));
    if ((*(s32 *)((u8 *)var_t8 + 4)) >= temp_t7) {
        do {
            var_t9 = var_t8;
            var_t8 = *var_t8;
        } while ((*(s32 *)((u8 *)var_t8 + 4)) >= temp_t7);
    }
    (*(s32 **)((u8 *)arg1 + 0)) = *var_t9;
    *var_t9 = arg1;
    (*(s32 **)((u8 *)arg1 + 8)) = arg0;
}
/* __osPopThread: unlink and return the head of a thread queue */
/* was func_10007D14 */
OSThread *os_pop_thread(OSThread **queue) {
    OSThread *t = *queue;

    *queue = t->next;
    return t;
}
/* was func_10007D28 */


/* was func_10007F64 */

/* was func_10007FB4 */

/* was func_10008018 */

/* was func_10008090 */

/* was func_1000809C */
