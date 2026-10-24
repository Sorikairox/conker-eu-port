#ifdef NON_MATCHING
void *memcpy(void *, const void *, s32);
s32 func_150ACEA0(f32, f32, f32, f32, f32, f32, void *, void *, f32 *, f32 *, f32 *, f32 *, s32, s32, f32);
f32 func_15143E64(struct17 *);
f32 func_15144528(f32, f32, f32);
void func_15143794(s16, s16, f32, void *);
void func_1508B20C(f32, f32, f32, f32);
f32 func_150ADA68(void);
s32 func_150ADA20(void);
void *func_1513D2F0(void *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7, s32 arg8, s32 arg9, u8 argA, s32 argB);
extern s32 (*D_8008FC48[])(u8 *); /* func_1519CEB8 / func_1519CEE0 / func_1519CF08: all take the trail object only */

/* One point of a trail ring (obj +0x94, obj +0x25 entries). */
typedef struct {
    /* 0x00 */ f32 x, y, z;
    /* 0x0C */ f32 dir[3];    /* spark velocity direction */
    /* 0x18 */ f32 width;     /* spark rate weight / spread */
    /* 0x1C */ f32 len;       /* length of the segment to the newer neighbour */
    /* 0x20 */ u8 alpha;
    /* 0x21 */ u8 pad21[3];
    /* 0x24 */ f32 angle;
} TrailPoint;

/* Motion block copied to the new spark +0x110 (stack +0x108, directly below the spec). */
typedef struct {
    /* 0x00 */ f32 vel0[3];
    /* 0x0C */ f32 vel1[3];
    /* 0x18 */ f32 spin;
    /* 0x1C */ f32 u1C, u20, u24;
    /* 0x28 */ s16 u28, u2A;
} TrailSparkMotion;

/* func_1513D2F0 spec (stack +0x134). */
typedef struct {
    /* 0x00 */ u8 kind;
    /* 0x01 */ u8 u01;
    /* 0x02 */ s16 flags;
    /* 0x04 */ s16 life;
    /* 0x06 */ s16 pad06;
    /* 0x08 */ s32 u08;
    /* 0x0C */ s32 u0C;
    /* 0x10 */ u8 rgba[4];
    /* 0x14 */ f32 sizeA;
    /* 0x18 */ f32 sizeB;
    /* 0x1C */ f32 p0[3];
    /* 0x28 */ f32 p1[3];
    /* 0x34 */ f32 u34, u38, u3C, u40;
    /* 0x44 */ u8 frame;
    /* 0x45 */ u8 u45, u46, u47;
    /* 0x48 */ s32 u48;
} TrailSparkSpec;

/* Ring index before i (obj +0x25 = ring size). */
#define TRAIL_PREV(i, obj) ((i) - 1 >= 0 ? (i) - 1 : (obj)[0x25] - 1)

// trail_update: per-frame update of a ribbon trail (object handler table D_8008A624 / D_8008A5DC, returns 1).
// obj +0x94 = ring of 0x28-byte TrailPoint, obj +0x98 = state, obj +0x2C = point count, +0x2D = tail (oldest),
// +0x2E = head (next free), +0x25 = ring size; obj +0x1E bit 1: the newest end is the object position (+0x10)
// instead of the point before the head. State: +0x28 max length, +0x14C current length, +0x150 flags.
// 1. flag 4: a ray from the owner (state +0, position +0x14 raised by 48) to the newest end (func_150ACEA0) can
//    shorten the max length to the hit distance (+0x1D4 out).
// 2. Walks from the newest end to the tail: segment lengths (+0x1C) and the total; once the total passes the max
//    length the segment is cut back to fit and the tail moves up (count decremented) to that point.
// 3. Alpha (+0x20): the oldest (1 - state +0x3C) part of the length fades as state +0x140 * the remaining fraction,
//    the rest gets state +0x3A. 4. Angle: state +0x144 spins by state +0x40 per frame, each point gets it plus the
//    distance from the head * state +0x44, wrapped to -16384..16383 (func_15144528).
// 5. With 3+ points (unless state +0x150 bits 0x20 and 0x10 are both set) and the trail at full length, spark
//    credit (+0x134) grows by (+0x4C + rand * +0x50) * tail width * frame time; per whole unit one spark
//    (func_1513D2F0 kind 0x13 / 0x14, motion block at +0x110) starts at the point state +0x84 of the way from the
//    head (interpolated between the two points around it), jittered by func_15143794.
// 6. State +0x35 (if not -1) picks a D_8008FC48 handler (called with obj only: all three handlers take one
//    argument; the asm leaves a stale a1 there). 7. Flag 2: func_1508B20C at the midpoint of newest end and tail with
//    radius half the length.
s32 func_1519AF14(u8 *obj) {
    u8 *st = *(u8 **)(obj + 0x98);
    TrailPoint *pts = *(TrailPoint **)(obj + 0x94);
    f32 maxLen = *(f32 *)(st + 0x28);
    f32 *newest;
    TrailPoint *pt;
    TrailPoint *prev;
    struct17 d;
    struct17 jit;
    f32 hit;
    f32 hx, hy, hz;
    f32 acc;
    f32 cut;
    f32 seglen;
    f32 fadeLen;
    f32 fadeSpan;
    f32 fadeInv;
    f32 at;
    f32 where;
    f32 width;
    f32 spread;
    f32 sizeA;
    f32 sizeB;
    f32 speed;
    struct17 pos;
    struct17 seg;
    TrailSparkMotion mot;
    TrailSparkSpec spec;
    TrailPoint *pNew;
    TrailPoint *pOld;
    u8 *spark;
    s32 i;
    s32 found;
    s32 tail;
    s32 next;
    s32 r1;
    s8 h;

    /* 1. ray-shortened max length */
    if ((st[0x150] & 4) && (s8)obj[0x2C] >= 2) {
        u8 *owner = *(u8 **)st;
        f32 sx = *(f32 *)(owner + 0x14);
        f32 sy = *(f32 *)(owner + 0x18) + 48.0f;
        f32 sz = *(f32 *)(owner + 0x1C);
        f32 o1, o2, o3;

        if (*(u16 *)(obj + 0x1E) & 2) {
            newest = (f32 *)(obj + 0x10);
        } else {
            newest = &pts[TRAIL_PREV((s8)obj[0x2E], obj)].x;
        }
        if (func_150ACEA0(sx, sy, sz, newest[0] - sx, newest[1] - sy, newest[2] - sz, NULL, NULL, &o1, &o2, &o3,
                          &hit, 0, 0, 0.0f) != 0 &&
            hit < maxLen) {
            maxLen = hit;
        }
    }

    /* 2. segment lengths, cut at the max length */
    if ((s8)obj[0x2C] >= 2) {
        i = (s8)obj[0x2E];
        *(f32 *)(st + 0x14C) = 0.0f;
        if (*(u16 *)(obj + 0x1E) & 2) {
            newest = (f32 *)(obj + 0x10);
        } else {
            i = TRAIL_PREV(i, obj);
            newest = &pts[i].x;
        }
        do {
            i = TRAIL_PREV(i, obj);
            pt = &pts[i];
            d.unk0 = pt->x - newest[0];
            d.unk4 = pt->y - newest[1];
            d.unk8 = pt->z - newest[2];
            pt->len = func_15143E64(&d);
            *(f32 *)(st + 0x14C) += pt->len;
            if (maxLen < *(f32 *)(st + 0x14C)) {
                seglen = pt->len;
                if (seglen != 0.0f) {
                    cut = (*(f32 *)(st + 0x14C) - maxLen) / seglen;
                    pt->x -= d.unk0 * cut;
                    pt->y -= d.unk4 * cut;
                    pt->z -= d.unk8 * cut;
                    pt->len = seglen * (1.0f - cut);
                }
                while (i != (s8)obj[0x2D]) {
                    obj[0x2D] = (s8)obj[0x2D] + 1;
                    if ((s8)obj[0x2D] == obj[0x25]) {
                        obj[0x2D] = 0;
                    }
                    obj[0x2C] = (s8)obj[0x2C] - 1;
                }
                *(f32 *)(st + 0x14C) = maxLen;
            }
            newest = &pt->x;
        } while (i != (s8)obj[0x2D]);
    }

    /* 3. alpha fade over the oldest part */
    if ((s8)obj[0x2C] >= 2) {
        fadeLen = *(f32 *)(st + 0x14C) * *(f32 *)(st + 0x3C);
        fadeSpan = *(f32 *)(st + 0x14C) - fadeLen;
        fadeInv = 1.0f / fadeSpan;
        acc = 0.0f;
        i = (s8)obj[0x2E];
        do {
            i = TRAIL_PREV(i, obj);
            pt = &pts[i];
            acc += pt->len;
            if (fadeLen < acc) {
                pt->alpha = (u32)(*(f32 *)(st + 0x140) * ((fadeSpan - (acc - fadeLen)) * fadeInv));
            } else {
                pt->alpha = st[0x3A];
            }
        } while (i != (s8)obj[0x2D]);
    }

    /* 4. twist angle */
    if ((s8)obj[0x2C] >= 2) {
        *(f32 *)(st + 0x144) += *(f32 *)(st + 0x40) * D_800BE9A4;
        *(f32 *)(st + 0x144) = func_15144528(*(f32 *)(st + 0x144), 16383.0f, -16384.0f);
        acc = 0.0f;
        i = (s8)obj[0x2E];
        do {
            i = TRAIL_PREV(i, obj);
            pt = &pts[i];
            acc += pt->len;
            pt->angle = func_15144528(*(f32 *)(st + 0x144) + acc * *(f32 *)(st + 0x44), 16383.0f, -16384.0f);
        } while (i != (s8)obj[0x2D]);
    }

    /* 5. sparks */
    if ((s8)obj[0x2C] >= 3 && !((st[0x150] & 0x20) && (st[0x150] & 0x10)) && maxLen <= *(f32 *)(st + 0x14C)) {
        *(f32 *)(st + 0x134) += (*(f32 *)(st + 0x4C) + func_150ADA68() * *(f32 *)(st + 0x50)) *
                                pts[(s8)obj[0x2D]].width * D_800BE9A4;
        if (1.0f < *(f32 *)(st + 0x134)) {
            tail = (s8)obj[0x2D];
            next = tail + 1;
            if (next == obj[0x25]) {
                next = 0;
            }
            /* the point `where` (state +0x84 of the length) from the newest end. If it is never reached
               (+0x84 > 1) pos / seg stay unset, as in the asm. */
            width = 0.0f;
            acc = 0.0f;
            found = 0;
            prev = NULL;
            where = *(f32 *)(st + 0x14C) * *(f32 *)(st + 0x84);
            i = (s8)obj[0x2E];
            do {
                i = TRAIL_PREV(i, obj);
                pt = &pts[i];
                seglen = pt->len;
                acc += seglen;
                if (where <= acc) {
                    found = 1;
                    if (prev != NULL && seglen != 0.0f) {
                        at = (acc - where) / seglen;
                        pos.unk0 = pt->x + (prev->x - pt->x) * at;
                        pos.unk4 = pt->y + (prev->y - pt->y) * at;
                        pos.unk8 = pt->z + (prev->z - pt->z) * at;
                        width = pt->width + (prev->width - pt->width) * at;
                        seg.unk0 = pt->x - prev->x;
                        seg.unk4 = pt->y - prev->y;
                        seg.unk8 = pt->z - prev->z;
                    } else {
                        pos.unk0 = pt->x;
                        pos.unk4 = pt->y;
                        pos.unk8 = pt->z;
                        width = pt->width;
                        seg.unk0 = 0.0f;
                        seg.unk4 = 0.0f;
                        seg.unk8 = 0.0f;
                    }
                }
                prev = pt;
            } while (i != tail && !found);

            spec.u08 = 0;
            spec.u0C = 0;
            mot.u1C = *(f32 *)(st + 0x78);
            mot.u20 = *(f32 *)(st + 0x7C);
            mot.u24 = *(f32 *)(st + 0x8C);
            mot.u28 = *(s16 *)(st + 0x80);
            mot.u2A = *(s16 *)(st + 0x82);
            spec.flags = 0x2203;
            spec.rgba[0] = 0xFF;
            spec.u01 = 0;
            spec.rgba[1] = 0xFF;
            spec.rgba[2] = 0xFF;
            spec.rgba[3] = 0xFF;
            spec.u38 = 0.0f;
            spec.u34 = 1.0f;
            spec.u3C = 1.0f;
            spec.u40 = 6.3757176f;
            spec.u45 = 0xFF;
            spec.u46 = 0;
            spec.u47 = 7;
            spec.u48 = 0;
            pOld = &pts[tail];
            pNew = &pts[next];
            do {
                sizeA = func_150ADA68() * *(f32 *)(st + 0x60) + *(f32 *)(st + 0x58);
                sizeB = func_150ADA68() * *(f32 *)(st + 0x64) + *(f32 *)(st + 0x5C);
                speed = func_150ADA68() * *(f32 *)(st + 0x6C) + *(f32 *)(st + 0x68);
                spec.sizeA = 24.222889f * sizeA;
                spec.sizeB = 3.4404585f * sizeB;
                mot.vel0[0] = pNew->dir[0] * speed;
                mot.vel0[1] = pNew->dir[1] * speed;
                mot.vel0[2] = pNew->dir[2] * speed;
                mot.vel1[0] = pOld->dir[0] * speed;
                mot.vel1[1] = pOld->dir[1] * speed;
                mot.vel1[2] = pOld->dir[2] * speed;
                mot.spin = func_150ADA68() * *(f32 *)(st + 0x74) + *(f32 *)(st + 0x70);
                spec.kind = (func_150ADA20() & 1) ? 0x13 : 0x14;
                spec.life = (u32)func_150ADA20() % (u32)(*(s16 *)(st + 0x56) + 1) + *(s16 *)(st + 0x54);
                r1 = func_150ADA20();
                func_15143794(r1 & 0xFF, (func_150ADA20() & 0x7F) - 0x3F, width, &jit);
                spec.p0[0] = pos.unk0 + jit.unk0;
                spec.p0[1] = pos.unk4 + jit.unk4;
                spec.p0[2] = pos.unk8 + jit.unk8;
                spec.p1[0] = spec.p0[0] + seg.unk0;
                spec.p1[1] = spec.p0[1] + seg.unk4;
                spec.p1[2] = spec.p0[2] + seg.unk8;
                spec.frame = (u32)func_150ADA20() % (u32)(st[0x89] + 1) + st[0x88];
                spark = func_1513D2F0(&spec, (s32)&D_800A4AA0, 0x1F, 0x22, 0, 0x1A, (func_150ADA20() & 1) | 2, 0, 0,
                                      0x2C, obj[0xC], obj[1]);
                if (spark != NULL) {
                    memcpy(spark + 0x110, &mot, 0x2C);
                }
                *(f32 *)(st + 0x134) -= 1.0f;
            } while (1.0f < *(f32 *)(st + 0x134));
        }
    }

    /* 6. per-kind handler */
    h = (s8)st[0x35];
    if (h != -1) {
        D_8008FC48[h](obj);
    }

    /* 7. bounding sphere */
    if ((st[0x150] & 2) && (s8)obj[0x2C] >= 2) {
        if (*(u16 *)(obj + 0x1E) & 2) {
            newest = (f32 *)(obj + 0x10);
        } else {
            newest = &pts[TRAIL_PREV((s8)obj[0x2E], obj)].x;
        }
        pt = &pts[(s8)obj[0x2D]];
        hx = (pt->x + newest[0]) * 0.5f;
        hy = (pt->y + newest[1]) * 0.5f;
        hz = (pt->z + newest[2]) * 0.5f;
        func_1508B20C(hx, hy, hz, *(f32 *)(st + 0x14C) * 0.5f);
    }
    return 1;
}
#undef TRAIL_PREV
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519AF14.s")
#endif
