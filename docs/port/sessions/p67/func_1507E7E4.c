//HOIST s32 func_1507ECE8(s32 arg0, s32 arg1);
//HOIST u32 func_1507ED48(s32 arg0);
//HOIST s32 *func_1507EDD8(s32 arg0, s32 *arg1);
//HOIST void func_1507E7E4(struct127 *obj, u8 anim, u8 prio, u16 time, s32 arg4);
void func_150305E0(s32 arg0, s32 arg1);
void func_1507E9A8(struct127 *, s32);

/* P67: start animation `anim` (obj +0x6F) with priority `prio` (+0x71) for `time` frames (+0x72, 0xFFFF = until
 * replaced). Priority 3 always wins; otherwise a running timed animation of equal or higher priority is kept unless
 * it is the default one (+0x70) or `anim` itself. Animations past the object's table (func_1507ED48) are ignored.
 * The first frame's sound of the new animation is played (func_150305E0). `void` under NM: callers ignore the
 * result and the asm leaves v0 undefined on the early returns. */
void func_1507E7E4(struct127 *obj, u8 anim, u8 prio, u16 time, s32 arg4) {
    u8 *entry;
    u8 *sounds;

    if (obj->unk6F == anim && obj->unk71 == prio && obj->unk72 == time) {
        return;
    }
    if (prio != 3 && obj->unk70 != obj->unk6F && anim != obj->unk6F && obj->unk72 != 0 && obj->unk71 >= prio) {
        return;
    }
    if (!((s32)anim < (s32)func_1507ED48((s32)obj))) {
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
    obj->unk72 = time;
    obj->unk71 = prio;
    func_1507E9A8(obj, arg4);
}
