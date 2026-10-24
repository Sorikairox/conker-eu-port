#ifdef NON_MATCHING
/* P247: the record func_151D1510 builds at self + 0x28 (same layout as its stack copy). */
typedef struct {
    u8 *obj;                /* 0x00 followed object */
    u8 id;                  /* 0x04 the object's +0x3B id when the record was made */
    void *effect;           /* 0x08 attached effect (func_151D19F8 creates it, func_151D1990 releases it) */
    Vec3_151D1510 prev;     /* 0x0C last point */
    Vec3_151D1510 cur;      /* 0x18 this frame's point */
    Vec3_151D1510 delta;    /* 0x24 cur - prev */
    f32 dist;               /* 0x30 |delta| */
    u8 point;               /* 0x34 D_8008FFD0 index (which point of the object) */
} ObjPointTrail;

s32 func_1510FE4C(s32);
void func_151D19F8(u8 *);

// object_point_trail_update: per-frame handler (D_8008A980[0x21], void (u8 *)) of an effect that follows a
// point of an object: kills itself (+0xE = -1) when the object is gone or was replaced (id byte changed);
// else moves the point (D_8008FFD0[point]; keeps the old one when the query fails), stores the step and its
// length, and releases the effect (func_151D1990) when the query failed, the step is longer than 300 or zero,
// the object's +0x28 is non-zero, its +0xAD is set, or its state (func_1510FE4C of +0x184) is 5, 6, 9, 13 or
// 14; otherwise it (re)creates the effect when there is none (func_151D19F8).
void func_151D16E8(u8 *self) {
    ObjPointTrail *t = (ObjPointTrail *) (self + 0x28);
    u8 *obj = t->obj;
    s32 stop = 0;
    s32 state;

    if (*(s32 *) obj == 0 || t->id != obj[0x3B]) {
        *(s16 *) (self + 0xE) = -1;
        return;
    }
    t->prev = t->cur;
    if (D_8008FFD0[t->point](obj, &t->cur) == 0) {
        t->cur = t->prev;
        stop = 1;
    }
    t->delta.x = t->cur.x - t->prev.x;
    t->delta.y = t->cur.y - t->prev.y;
    t->delta.z = t->cur.z - t->prev.z;
    t->dist = func_15143E64(&t->delta.x);
    state = func_1510FE4C(*(s32 *) (obj + 0x184));
    if (t->dist > 300.0f || t->dist <= 0.0f || *(f32 *) (obj + 0x28) != 0.0f || obj[0xAD] != 0
        || state == 5 || state == 6 || state == 9 || state == 13 || state == 14) {
        stop = 1;
    }
    if (stop) {
        func_151D1990(self);
    } else if (t->effect == NULL) {
        func_151D19F8(self);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D16E8.s")
#endif
