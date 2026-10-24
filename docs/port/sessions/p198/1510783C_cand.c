typedef struct {
    u8 *rec;      // 0x00 copied into the arc object (its +0x60 data) after the spawn
    s16 life;     // 0x04 <- passed to func_15106260 from here
    u8 u06;       // 0x06
    f32 a[3];     // 0x08 segment start
    f32 c1[3];    // 0x14 start + random offset
    f32 c2[3];    // 0x20 end + random offset
    f32 b[3];     // 0x2C segment end
    s8 u38;       // 0x38
    s32 u3C;      // 0x3C
    f32 u40;      // 0x40
    f32 u44;      // 0x44
    s16 u48;      // 0x48
    s16 u4A;      // 0x4A
    u8 rgb[3];    // 0x4C
    u8 u4F;       // 0x4F
    u8 u50;       // 0x50
} BoltArcSpawn;
s32 func_15106260(s16 *, s32, u8, u8);
s32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_15143794(s16, s16, f32, u8 *);
void *memcpy(void *, const void *, unsigned int);

// bolt_record_update: record handler of the bolt spawned by func_15107518 (type 0x3E). While no arc is alive
// (+0x30 == 0) it spawns the next segment arc (func_15106260 kind 4) between points +0x2C and +0x2D of the point list,
// with two control points pushed sideways by func_15143794 (random angle, random pitch around -0x40) and life,
// colour, width and the other values from the bolt parameters (+0x38..); the arc gets the record pointer. When the
// last segment is done it marks the record finished (+0xE = -1, +0xD bit 0).
void func_1510783C(u8 *rec) {
    u8 *spec = rec + 0x28;  // BoltSpec: +0 count, +4 segment, +8 live arc, +0xC points, +0x10 params
    u8 *p = spec + 0x10;
    BoltArcSpawn s;
    f32 off[3];
    f32 *pt;
    u32 r1;
    u32 r2;
    s16 spread;
    u8 *arc;

    if (*(s32 *) (rec + 0x30) != 0) {
        return;
    }
    if (*(s32 *) (spec + 4) >= *(s32 *) spec - 1) {
        *(s16 *) (rec + 0xE) = -1;
        rec[0xD] |= 1;
        return;
    }
    s.rec = rec;
    s.u06 = 1;
    s.u38 = -1;
    s.u44 = func_150ADA68() * *(f32 *) (p + 4) + *(f32 *) p;
    s.u40 = *(f32 *) (p + 8);
    s.u48 = *(s16 *) (p + 0x16);
    s.u4A = *(s16 *) (p + 0x18);
    pt = *(f32 **) (spec + 0xC) + *(s32 *) (spec + 4) * 3;
    s.a[0] = pt[0];
    s.a[1] = pt[1];
    s.a[2] = pt[2];
    pt = *(f32 **) (spec + 0xC) + *(s32 *) (spec + 4) * 3;
    s.b[0] = pt[3];
    s.b[1] = pt[4];
    s.b[2] = pt[5];

    r1 = func_150ADA20();
    r2 = func_150ADA20();
    spread = *(s16 *) (p + 0x14);
    func_15143794((u8) r1, r2 % (u32) (spread + 1) - (spread >> 1) - 0x40,
                  func_150ADA68() * *(f32 *) (p + 0x10) + *(f32 *) (p + 0xC), (u8 *) off);
    s.c1[0] = s.a[0] + off[0];
    s.c1[1] = s.a[1] + off[1];
    s.c1[2] = s.a[2] + off[2];

    r1 = func_150ADA20();
    r2 = func_150ADA20();
    spread = *(s16 *) (p + 0x14);
    func_15143794((u8) r1, r2 % (u32) (spread + 1) - (spread >> 1) - 0x40,
                  func_150ADA68() * *(f32 *) (p + 0x10) + *(f32 *) (p + 0xC), (u8 *) off);
    s.c2[0] = s.b[0] + off[0];
    s.c2[1] = s.b[1] + off[1];
    s.c2[2] = s.b[2] + off[2];

    s.rgb[0] = p[0x28];
    s.rgb[1] = p[0x29];
    s.rgb[2] = p[0x2A];
    s.life = (u32) func_150ADA20() % (u32) (*(s16 *) (p + 0x1C) + 1) + *(s16 *) (p + 0x1A);
    s.u4F = (u32) func_150ADA20() % (u32) (p[0x2C] + 1) + p[0x2B];
    s.u50 = 1;
    s.u3C = (u32) func_150ADA20() % (u32) (*(s32 *) (p + 0x24) + 1) + *(s32 *) (p + 0x20);
    arc = (u8 *) func_15106260(&s.life, 4, rec[0xC], rec[1]);
    *(u8 **) (spec + 8) = arc;
    if (arc != NULL) {
        memcpy(*(u8 **) (arc + 0x60), &s.rec, 4);
    }
    *(s32 *) (spec + 4) += 1;
}
