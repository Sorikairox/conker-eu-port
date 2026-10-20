f32 func_150ADA68(void);

typedef struct { f32 x, y, z; s32 pad[3]; } E18;
typedef struct {
    u8 pad0[0x10];
    u8 pad10[2];
    s16 s12;
    u8 pad14[0x4C];
    E18 *end;
    E18 *tbl;
    f32 f68;
    u8 b6C[0x10];
    s32 u7C;
} O7F00;

void func_151A88F0(O7F00 *arg0, s16 lo, s16 hi, f32 amp, s16 depth) {
    E18 *a;
    E18 *b;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 mid;

    if ((hi - lo) < 2 || depth <= 0) {
        return;
    }
    mid = lo + ((hi - lo) >> 1);
    a = &arg0->tbl[lo];
    dx = arg0->tbl[hi].x - arg0->tbl[lo].x;
    dy = arg0->tbl[hi].y - arg0->tbl[lo].y;
    dz = arg0->tbl[hi].z - arg0->tbl[lo].z;
    arg0->tbl[mid].x = (func_150ADA68() * (amp + amp) + -amp) + (a->x + dx * 0.5f);
    arg0->tbl[mid].y = (func_150ADA68() * (amp + amp) + -amp) + (a->y + dy * 0.5f);
    arg0->tbl[mid].z = a->z + dz * 0.5f;
    func_151A88F0(arg0, lo, mid, amp, depth - 1);
    func_151A88F0(arg0, mid, hi, amp, depth - 1);
}
