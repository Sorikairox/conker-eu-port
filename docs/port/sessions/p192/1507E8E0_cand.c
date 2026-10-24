void func_150305E0(s32 arg0, s32 arg1);
void func_1507E9A8(struct127 *, s32);

// obj_anim_set: switches the object to animation `anim` (+0x6F) if it is inside the object's table (func_1507ED48):
// plays the old animation's first-frame sound (func_150305E0), applies the new one (func_1507E9A8) and sets the
// animation variant +0x135 to `variant`, or to the new entry's default (+3) when `variant` is 0. `void` under NM:
// the callers ignore the result.
void func_1507E8E0(u8 *arg0, s32 anim, s32 variant) {
    struct127 *obj = (struct127 *)arg0;
    u8 *entry;
    u8 *sounds;

    if (!(anim < (s32)func_1507ED48((s32)obj))) {
        return;
    }
    entry = (u8 *)func_1507ECE8((s32)obj, obj->unk6F);
    if (entry[4] != 0) {
        sounds = (u8 *)func_1507EDD8((s32)obj, NULL);
        if (sounds != NULL) {
            func_150305E0((s32)obj, sounds[entry[4] - 1]);
        }
    }
    obj->unk6F = anim;
    func_1507E9A8(obj, variant);
    if (variant != 0) {
        obj->unk135 = variant;
    } else {
        obj->unk135 = ((u8 *)func_1507ECE8((s32)obj, anim))[3];
    }
}
