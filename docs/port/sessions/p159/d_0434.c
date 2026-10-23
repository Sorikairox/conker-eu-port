s32 func_15144E80(u8 *, f32 *, f32 *, f32 *);
void func_1515016C(void *, u8, s32);
// impact_effects_spawn: the effects of a hit at pos (func_151C09C8, func_151C0AA8, func_151C0B54, func_151C0BA0).
// With `full` set: when hit (an 0x12-byte surface record) has a downward-facing third axis (func_15144E80) also
// func_151C0BF4, a burst along it (func_151C0910), and a spray against dir (func_1515016C with the surface, else
// func_15150108 without one), its parameters from func_151C01F0.
void func_151C0434(u8 *hit, f32 *pos, f32 *dir, u8 full, u8 arg4, s32 arg5) {
    typedef struct {
        f32 u0;
        s32 u4;
        f32 pos[3];
        u8 rest[0x40];
    } SprayParams; /* filled by func_151C01F0 (0x54 bytes) */
    struct {
        f32 dir[3];
        u8 hit[0x12];
        u8 pad1E[2];
        f32 range;
        SprayParams p;
    } a; /* func_1515016C */
    struct {
        f32 dir[3];
        f32 range;
        SprayParams p;
    } b; /* func_15150108 */
    f32 ax0[3];
    f32 ax1[3];
    f32 ax2[3];
    s32 i;

    func_151C09C8((u8 *)pos, arg4, arg5);
    func_151C0AA8((u8 *)pos, arg4, arg5);
    func_151C0B54((s32)pos, arg4, arg5);
    func_151C0BA0((struct17 *)pos, arg4, arg5);
    if (hit != NULL && full != 0) {
        if (func_15144E80(hit, ax0, ax1, ax2) != 0 && ax2[1] < 0.0f) {
            func_151C0BF4((s32)pos, arg4, arg5);
        }
    }
    if (hit != NULL && full != 0) {
        func_151C0910((s32)hit, (s32)pos, arg4, arg5);
    }
    if (full == 0) {
        return;
    }
    if (hit != NULL) {
        a.dir[0] = -dir[0];
        a.dir[1] = -dir[1];
        a.dir[2] = -dir[2];
        for (i = 0; i < 0x12; i++) {
            a.hit[i] = hit[i];
        }
        a.p.pos[0] = pos[0];
        a.p.pos[1] = pos[1];
        a.p.pos[2] = pos[2];
        func_151C01F0((f32 *)&a.p, &a.range);
        func_1515016C(&a, arg4, arg5);
    } else {
        b.dir[0] = -dir[0];
        b.dir[1] = -dir[1];
        b.dir[2] = -dir[2];
        func_151C01F0((f32 *)&b.p, &b.range);
        b.p.pos[0] = pos[0];
        b.p.pos[1] = pos[1];
        b.p.pos[2] = pos[2];
        func_15150108((f32 *)&b, arg4, arg5);
    }
}
