f32 func_15052F9C(struct127 *arg0, f32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);
s32 func_1505327C(struct127 *arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4);
u16 func_1505A630(f32 arg0, f32 arg1, s32 arg2);
u16 func_10010154(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4);
void func_1505A184(u16 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5);
void func_1508B20C(f32, f32, f32, f32);

/* menu_object_update: per-frame extras of some menu / scene objects by id.
 * 0x0C: unless the object's target (D_800CC2D0[unk124]) has +0x65 == D_800C3E78 + 1: in state 0x12 run the
 *   func_15052F9C move step (speed 50); else on odd D_800CC268 frames with flag 0x400 retarget to object 0 and
 *   start func_1505327C (39, 3, state 0x12).
 * 0x4B: point unk2EC (packed s16 x << 16 | s16 z) 500 units behind its facing, turn a third of the way towards
 *   object 0 (or 0x800 off its facing when unk84 is 0xF), scale 2 and unk40 90.
 * 0x1B / 0x7E with a timer unk2E4: optional func_1508B20C at its position; the timer counts down by the frame
 *   step D_800BE9E4 (sound 0x3A1 when it passes 100); when it runs out, state 6 and unk218 = NULL. */
void func_15054F74(struct127 *arg0) {
    f32 dx, dz, dy;
    f32 x, z;
    s16 angle;
    s32 step;

    if (arg0->id == 0xC) {
        if ((D_800C3E78 + 1) != D_800CC2D0[arg0->unk124].unk65) {
            if (arg0->unk232 == 0x12) {
                func_15052F9C(arg0, 50.0f, 0, 4, 0, 0xC, 0, 8, 0, 0);
            } else if ((D_800CC268 & 1) && (arg0->unk25C & 0x400)) {
                arg0->unk124 = 0;
                func_1505327C(arg0, 39.0f, 3.0f, 0x12, 0);
            }
        }
    } else if (arg0->id == 0x4B) {
        func_1505A184(arg0->unk7A ^ 0x8000, 500.0f, 0.0f, &dx, &dz, &dy);
        x = arg0->x_position;
        z = arg0->z_position;
        arg0->unk2EC = ((s32) ((s16) x + dx) << 16) | ((s32) ((s16) z + dz) & 0xFFFF);
        if (arg0->unk84.uh != 0xF) {
            angle = func_1505A630(D_800CC2D0->x_position - x, z - D_800CC2D0->z_position, 0);
        } else {
            angle = arg0->unk7A - 0x800;
        }
        arg0->unk7A += (s16) (angle - arg0->unk7A) / 3;
        arg0->xz_scale = 2.0f;
        arg0->y_scale = 2.0f;
        arg0->unk40 = 90.0f;
    } else if ((arg0->id == 0x1B || arg0->id == 0x7E) && arg0->unk2E4 != 0) {
        if (D_800BE616 != 0) {
            func_1508B20C(arg0->x_position, arg0->y_position, arg0->z_position, 900.0f);
        }
        step = D_800BE9E4;
        if (step < arg0->unk2E4) {
            if (arg0->unk2E4 >= 100 && arg0->unk2E4 < step + 100) {
                func_10010154(0x3A1, arg0, 0x7D00, 500, 1000);
            }
            arg0->unk2E4 -= step;
        } else {
            arg0->unk232 = 6;
            arg0->unk218 = NULL;
        }
    }
}
