s32 func_15046F70(f32 *, s32, f32, u8 *);
/* landing handlers by +0x73 (entry 0 is NULL); they take (particle, old x, old y, old z, floor height, floor info),
   several are declared with s32 / fewer parameters (o32 passes them alike; the port's icall layer converts) */
extern s32 (*D_80089CD4[])(u8 *, f32, f32, f32, f32, u8 *);

// particle_fall_update: moves the particle (func_15133D30). When it has gravity (+0x60 bit 0), a landing kind (+0x73)
// and moved down, it probes the floor from the old height (+0x10 offset) down to the new one (func_15046F70, floor
// height at +0x110, info from +0x114); on a hit, unless its owner object (+0x130) is in state 0x40 (+0x4F & 0x60),
// the kind's landing handler decides the result. Returns 1 (keep the particle) or the handler's verdict (as s8).
s32 func_15133E04(u8 *p) {
    s8 keep;
    f32 old[3];
    f32 probe[3];
    u8 *owner;
    s32 skip;

    keep = 1;
    old[0] = *(f32 *) (p + 0x38);
    old[1] = *(f32 *) (p + 0x3C);
    old[2] = *(f32 *) (p + 0x40);
    func_15133D30(p);
    if ((*(s32 *) (p + 0x60) & 1) && p[0x73] != 0 && *(f32 *) (p + 0x3C) < old[1]) {
        probe[0] = *(f32 *) (p + 0x38);
        probe[1] = *(f32 *) (p + 0x10) + old[1];
        probe[2] = *(f32 *) (p + 0x40);
        if (func_15046F70(probe, 0, *(f32 *) (p + 0x3C) - *(f32 *) (p + 0x10), p + 0x110) != 0) {
            owner = *(u8 **) (p + 0x130);
            skip = FALSE;
            if (owner != NULL && (owner[0x4F] & 0x60) == 0x40) {
                skip = TRUE;
            }
            if (!skip) {
                keep = D_80089CD4[p[0x73]](p, old[0], old[1], old[2], *(f32 *) (p + 0x110), p + 0x114);
            }
        }
    }
    return keep;
}
