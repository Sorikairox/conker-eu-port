/* Script command: play a sound for the current object D_800D154C. Command word D_800D1580:
 *   bits 0..10 sound id, 11..13 how to play it, 14..15 actor condition, 16 "defer", 24..31 actor type.
 * Condition 0x4000: only when the object's actor type (its id, or the alias D_8008704C[...] when
 * D_800D1C90[id]->unk4 is set) equals bits 24..31; 0x8000: only when it differs. With bit 16 the command
 * word + 1 is stored in D_800D1C9C (which is cleared otherwise) and nothing plays.
 * Modes (volume 0x7D00, 500 / 2500 = the distance / time arguments of the sound calls):
 *   0x0000 func_10010154, 0x1000 func_10010344, 0x3000 func_10010630,
 *   0x3800 func_10010154 unless func_1001147C(obj->unk8E) already returns that sound,
 *   0x2000 footstep (at most 1 player, D_80082FA0 < 2): the sound comes from the floor surface
 *          (func_1510FE4C(obj->unk184) -> func_10011EB8, which may also lower the volume; in the air: surface 8;
 *          surface 12 = water while obj->unkCC > -17: func_1000F568(0x9C, 2)); the volume scales with the
 *          fall speed (obj->unk31C's first float, else y_velocity), 0.5 .. 1.0 over 0 .. 10 (water) or 30.
 *          Surface 8 plays with func_10010630, the others with func_10010154. */
extern s32 D_800D1C9C;
extern u8 *D_8008704C[];
s32 func_1000F568(s32, s32);
s32 func_10011EB8(s32 surface, u16 *volume, s32 sound);

void func_1506BF5C(void) {
    s32 cmd = D_800D1580;
    struct127 *obj = D_800D154C;
    s32 sound = cmd & 0x7FF;          /* sp4C, played as its low half */
    s32 want = (u32)cmd >> 24;
    s32 type = obj->id;
    s32 mode;
    s32 surface;
    u16 volume;                       /* sp46 */
    f32 speed;
    f32 limit;
    f32 scale;

    if (D_800D1C90[type]->unk4 != 0) {
        type = *D_8008704C[D_800D1C90[type]->unk5];
    }
    D_800D1C9C = 0;
    if ((cmd & 0xC000) == 0x4000) {
        if (type != want) {
            return;
        }
    } else if ((cmd & 0xC000) == 0x8000) {
        if (type == want) {
            return;
        }
    }
    if (cmd & 0x10000) {
        D_800D1C9C = cmd + 1;
        return;
    }

    volume = 0x7D00;
    mode = cmd & 0x3800;
    if (mode == 0x0000) {
        func_10010154(sound, obj, volume, 500, 2500);
        return;
    }
    if (mode == 0x1000) {
        func_10010344(sound, obj, 0x7D00, 500, 2500);
        return;
    }
    if (mode == 0x3000) {
        func_10010630(sound, obj, 0x7D00, 500, 2500);
        return;
    }
    if (mode == 0x3800) {
        if (func_1001147C(obj->unk8E) != sound) {
            func_10010154(sound, D_800D154C, volume, 500, 2500);
        }
        return;
    }
    if (mode != 0x2000) {
        return;
    }

    /* footstep */
    if (D_80082FA0 >= 2) {
        return;
    }
    surface = func_1510FE4C(obj->unk184);
    if (surface == 12 && -17.0f < D_800D154C->unkCC) {
        sound = func_1000F568(0x9C, 2);
    } else if (D_800D154C->unk118 != -10000.0f && D_800D154C->unk118 >= D_800D154C->y_position) {
        sound = func_10011EB8(8, NULL, sound);
        surface = 8;
    } else {
        sound = func_10011EB8(surface, &volume, sound);
    }
    if (sound == 0) {
        return;
    }
    obj = D_800D154C;
    if (obj->unk31C != NULL) {
        speed = *(f32 *)obj->unk31C;
    } else {
        speed = obj->y_velocity;
    }
    limit = (surface == 12) ? 10.0f : 30.0f;
    if (limit < speed) {
        speed = limit;
    }
    scale = 0.5f / limit;
    if (speed < 0.0f) {
        speed = 0.0f;
    }
    volume = (u32)volume * (speed * scale + 0.5f);
    if (surface == 8) {
        func_10010630(sound, obj, volume, 500, 2500);
        return;
    }
    func_10010154(sound, obj, volume, 500, 2500);
}
