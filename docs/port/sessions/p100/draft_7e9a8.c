#ifdef NON_MATCHING
void func_1507EE24(s32, s32, s32);

/* Apply the current animation (+0x6F) of `obj`: its entry (func_1507ECE8) gives a model / frame pair for
 * func_1507EE24 (entry +4 / +6), the animation set (+0x134, with +0x135 = `variant`, or the entry's default +3 when
 * `variant` is 0, only when the set changes), two bytes +0x6C / +0x6D = entry +0 / +1 plus 10, and +0x68 / +0x69
 * from entry +8 / +9, or the object type's defaults (D_800D1C90[id] +0x3B / +0x3C) when those are 0. */
void func_1507E9A8(struct127 *obj, s32 variant) {
    u8 *entry = (u8 *) func_1507ECE8((s32) obj, obj->unk6F);
    u8 *ob = (u8 *) obj;

    if (entry == NULL) {
        return;
    }
    func_1507EE24((s32) obj, entry[4], *(u16 *) (entry + 6));
    if (entry[2] != obj->unk134) {
        obj->unk134 = entry[2];
        if (variant != 0) {
            obj->unk135 = variant;
        } else {
            obj->unk135 = entry[3];
        }
    }
    ob[0x6C] = entry[0] + 10;
    ob[0x6D] = entry[1] + 10;
    if (entry[8] != 0) {
        obj->unk68 = entry[8];
    } else {
        obj->unk68 = ((u8 *) D_800D1C90[obj->id])[0x3B];
    }
    if (entry[9] != 0) {
        obj->unk69 = entry[9];
    } else {
        obj->unk69 = ((u8 *) D_800D1C90[obj->id])[0x3C];
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ABEA0/func_1507E9A8.s")
#endif
