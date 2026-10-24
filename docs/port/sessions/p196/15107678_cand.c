f32 func_150ADA68(void);

// bolt_subdivide: fills the points between `lo` and `hi` of a bolt record's point list (rec + 0x28 + 0xC, 12-byte
// x / y / z) by midpoint displacement: each midpoint lies on the segment at a random fraction 0.5 +- `jitter`
// (func_150ADA68), then the left half recurses and the right half loops.
void func_15107678(u8 *rec, s16 lo, s16 hi, f32 jitter) {
    f32 *a;
    f32 *b;
    f32 *m;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 t;
    s16 mid;

    while (hi - lo >= 2) {
        mid = lo + ((hi - lo) >> 1);
        a = *(f32 **) (rec + 0x34) + lo * 3;
        b = *(f32 **) (rec + 0x34) + hi * 3;
        dx = b[0] - a[0];
        dy = b[1] - a[1];
        dz = b[2] - a[2];
        t = func_150ADA68() * (jitter + jitter) + (0.5f - jitter);
        m = *(f32 **) (rec + 0x34) + mid * 3;
        m[0] = a[0] + dx * t;
        m = *(f32 **) (rec + 0x34) + mid * 3;
        m[1] = a[1] + dy * t;
        m = *(f32 **) (rec + 0x34) + mid * 3;
        m[2] = a[2] + dz * t;
        func_15107678(rec, lo, mid, jitter);
        lo = mid;
    }
}
