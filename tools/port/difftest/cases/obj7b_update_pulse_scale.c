#ifdef NON_MATCHING
extern u16 g_obj7b_pulse_speeds[3]; /* was D_80088EA0 */

/*
 * object_7B_pulse_scale: per-frame "breathing" of object type 0x7B (obj_postprocess_joints's case 0x7B; obj7b_joint_swing_entries below
 * builds the same object's joint entries). A shared phase (the s16 at g_obj_anim_shared + 0x14) advances by
 * g_obj7b_pulse_speeds[sel] * g_frame_ticks (speeds 720 / 2000 / 3000: sel 1 when the object's +0x2E4 flags have both bits 0-1
 * set, sel 2 when both bits 2-3 are set, else 0); the scale 0.9 + 0.35 * (cos(phase) + 1) / 2 (0.9 .. 1.25, the
 * phase in 1/65536 turns) multiplies the 3x3 part of the 4x4 float matrix at the model's (+0x1D4) +0xF80.
 * The asm leaves a pointer in v0; no caller reads it (void).
 */
void obj7b_update_pulse_scale(struct127 *object) {
    u8 *obj = (u8 *) object;
    s16 *phase = (s16 *)((u8 *)&g_obj_anim_shared + 0x14);
    u16 speeds[3];
    s32 flags;
    s32 sel;
    f32 scale;
    f32 *m;
    s32 r;
    s32 c;

    speeds[0] = g_obj7b_pulse_speeds[0];
    speeds[1] = g_obj7b_pulse_speeds[1];
    speeds[2] = g_obj7b_pulse_speeds[2];
    flags = *(s32 *)(obj + 0x2E4);
    sel = 0;
    if ((flags & 3) == 3) {
        sel = 1;
    }
    if ((flags & 0xC) == 0xC) {
        sel = 2;
    }
    *phase += speeds[sel] * g_frame_ticks;
    /* 0.35000002f: the ROM constant is 0x3EB33334, one ulp above 0.35f */
    scale = (cosf(*phase * (6.2831855f / 65536.0f)) + 1.0f) * 0.5f * 0.35000002f + 0.9f;
    m = (f32 *)(*(u8 **)(obj + 0x1D4) + 0xF80);
    for (r = 0; r < 3; r++) {
        for (c = 0; c < 3; c++) {
            m[r * 4 + c] *= scale;
        }
    }
}
#endif
