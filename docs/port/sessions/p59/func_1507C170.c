f32 func_1506AD30(struct127 *arg0, f32 arg1, s32 arg2);
extern u8 D_800BEE2C;
extern u8 D_800C3A82[];
extern f32 D_8009B860;

/* Advances an animation (anim: +4 flags (0x8000 = hold the last frame), +8 frame, +0x10 speed, +0x18 end,
 * +0x20 loop start, +0x28 current animation, +0 end-of-animation callback, +0x3A / +0x3C a countdown) by one
 * frame. With a record, the step is scaled by the frame time D_800BE9A4 (x 1.2, at most 2 frames), the record
 * becomes the current one (D_800C3E78 / D_800D154C), its flags +0xF4 (2 / 4 / 8) change the looping, and
 * func_1506AD30 (the record's frame hook) may replace the frame. The final frame is copied to rec->unkB4.
 * The callback's arguments are not set up by the asm (it sees anim / player, or scratch after the hook): it is
 * called with anim here (UNVERIFIED). */
void func_1507C170(struct197 *anim, f32 step, struct127 *rec, s32 player) {
    void (*cb)(struct197 *);
    f32 frame, end, f;
    s32 hold;
    s32 resync = 0;
    s32 prev;
    u16 turn;

    if (*(s32 *)((u8 *)anim + 0x28) == 0) {
        return;
    }
    if (rec != NULL) {
        if (D_800C35EA == 0) {
            step = ((D_800BE9A4 < 2.0f) ? D_800BE9A4 * step : step + step) * D_8009B860; /* 1.2 */
        } else {
            step = D_800BE9A4;
        }
    }
    if (D_800BEE2C != 0) {
        step = 0.0f;
    }
    frame = anim->unk10 * step;
    if (anim->unk18 < frame) {
        frame = anim->unk18 + anim->unk8;
    } else {
        frame = frame + anim->unk8;
    }
    hold = anim->unk4 & 0x8000;
    if (rec != NULL) {
        rec->unk1FC &= ~4;
        D_800C3E78 = rec - D_800CC2D0;
        hold |= rec->unkF4 & 0xE;
        D_800D154C = rec;
    }
    if (rec != NULL && ((&D_800C35EA)[player] != 1 || D_800C3A82[player] != 0)) {
        f = func_1506AD30(D_800D154C, frame, 0);
        if (f != 0.0f) {
            frame = f;
        }
    }
    if (anim->unk10 >= 0.0f) {
        end = anim->unk18 - 1.0f;
        cb = *(void (**)(struct197 *))anim;
        if (end <= frame && anim->unk8 < end && cb != NULL) {
            prev = *(s32 *)((u8 *)anim + 0x28);
            if (rec != NULL && (rec->unkF4 & 8)) {
                rec->unk10C = 0;
                rec->unk1C4 = 0;
                anim->unk10 = 0.0f;
            }
            if (D_800C35EA == 0) {
                cb(anim);
                if (rec != NULL && rec->interaction_state == 0) {
                    return;
                }
            }
            if (prev != *(s32 *)((u8 *)anim + 0x28)) {
                /* the callback started another animation */
                frame = anim->unk8;
                resync = 1;
            }
        }
        if (rec != NULL && rec->unk1FD != 0 && anim->unk18 - 1.0f <= frame) {
            /* end of a turning animation: apply the turn (unk1FD x 256) to the facing angles */
            turn = rec->unk76 + (rec->unk1FD << 8);
            rec->unk76 = turn;
            rec->unk7A = turn;
            rec->unk78 = turn;
            anim->unk8 = *(f32 *)((u8 *)anim + 0x20);
            if (rec->unkF4 & 4) {
                rec->unk21C = 0;
            }
        } else if (hold == 0 && anim->unk18 <= frame) {
            /* loop */
            resync = 1;
            anim->unk8 = (frame - anim->unk18) + *(f32 *)((u8 *)anim + 0x20);
            if (rec != NULL) {
                rec->unk1FC |= 4;
            }
        } else if (hold != 0 && (end = anim->unk18 - 1.0f) <= frame) {
            /* hold the last frame */
            if ((rec != NULL && (rec->unkF4 & 0xA)) || (anim->unk4 & 0x8000)) {
                anim->unk8 = end;
            } else if (anim->unk8 < end) {
                anim->unk8 = end;
                if (rec != NULL && (rec->unkF4 & 4)) {
                    rec->unk21C = 0;
                }
            } else {
                anim->unk8 = *(f32 *)((u8 *)anim + 0x20);
                if (rec != NULL) {
                    rec->unk138 = 0;
                    rec->unk1FC |= 2;
                }
            }
            if (rec != NULL && (rec->unkF4 & 8)) {
                rec->unk10C = 0;
                rec->unk1C4 = 0;
                anim->unk10 = 0.0f;
            }
            if (anim->unk8 < 0.0f) {
                anim->unk8 = 0.0f;
            }
        } else {
            anim->unk8 = frame;
        }
    } else if (frame < *(f32 *)((u8 *)anim + 0x20)) {
        /* playing backwards past the loop start */
        anim->unk8 = (frame - *(f32 *)((u8 *)anim + 0x20)) + anim->unk18;
    } else {
        anim->unk8 = frame;
    }
    if (*(s16 *)((u8 *)anim + 0x3C) > 0) {
        *(s16 *)((u8 *)anim + 0x3C) -= *(s16 *)((u8 *)anim + 0x3A) * D_800BE9E4;
    }
    if (rec != NULL) {
        if (resync) {
            func_1506AD30(D_800D154C, anim->unk8, 0);
        }
        rec->unkB4 = anim->unk8;
    }
}
