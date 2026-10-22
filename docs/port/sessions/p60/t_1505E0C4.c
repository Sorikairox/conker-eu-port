//DROP s32 func_1505E0C4(struct127 *, s32, u8 *, s32, s32, s32, s32, f32, f32, f32, f32, s32);
s32 *func_1502AF04(s32, u8 *, s32, s32);
s32 func_1502B110(u8 *, s32, s32, u32, ...);
extern s32 D_800866AC[];
extern u16 D_800997B8[];

/* P60: start / restart animation `id` on the animation state `anim` (struct_eu_anim) of object `obj` (may be NULL;
 * func_1503F8A8 passes NULL / NULL). entry: the object's animation table entry (u16 file id, u16 callback index,
 * s32 value for obj +0x1C4), NULL = file id 2 * id.
 * The animation restarts when `restart` is set (no blend then), the id differs from anim +4 (low 15 bits) or, with
 * an object, from obj +0x84 (or that is 0xFFFF, or obj +0x103 is set). Else only the speed and the hold flag change
 * (and the frame, when D_800C35EA == 1 and the animation holds).
 * Restart: the previous animation is kept for blending (anim +6..+0x2C and the 0x1D0 block copied to +0x210) unless
 * the blend countdown +0x3C is >= 600; the countdown restarts at 0x3FF (blend >= 1: step +0x3A = 500 / blend; a
 * blend into the same animation reverses the countdown); the animation header (file `entry[0]`, 2 words: data
 * address / size, +0x28 = the next word) is looked up with func_1502AF04 (object model +0x58) or func_1502B110,
 * then DMAed to anim +0x40 (no header: func_1505DFDC). +0x18 = last frame (header byte 3; 0xFF: per type).
 * With an object, its contact / flag state is reset and func_150627D4(obj) runs. */
void func_1505E0C4(struct127 *obj, s32 entry_addr, u8 *anim_addr, s32 unused, s32 restart, s32 id, s32 set,
                  f32 speed, f32 blend, f32 frame, f32 loop_start, s32 hold) {
    struct_eu_anim *anim = (struct_eu_anim *) anim_addr;
    u16 *entry = (u16 *) entry_addr;
    s32 start = 0;
    s32 kind;
    s32 index;
    s32 file;
    s32 *hdr;
    s32 data = 0;
    s32 size = 0;
    s16 count;
    s32 size16;
    u32 flags;
    u8 buf[0x38];

    if (restart != 0) {
        start = 1;
        blend = 0.0f;
    } else if (id != (anim->unk4 & 0x7FFF)) {
        start = 1;
    } else if (obj != NULL && (id != obj->unk84.uh || obj->unk84.uh == 0xFFFF || obj->unk103 != 0)) {
        start = 1;
    }

    if (start == 0) {
        if (obj != NULL) {
            obj->animation_speed = speed;
        }
        anim->unk10 = speed;
        if (hold != 0) {
            anim->unk4 |= 0x8000;
        } else {
            anim->unk4 &= 0x7FFF;
        }
        if (D_800C35EA == 1 && (anim->unk4 & 0x8000)) {
            anim->unk8 = frame;
        }
    } else {
        kind = 10;
        if (obj != NULL) {
            index = (s32) ((u8 *) obj - (u8 *) D_800CC2D0) / (s32) sizeof(struct127);
            set = obj->unk6;
            kind = 2;
        }
        file = (entry != NULL) ? entry[0] : id * 2;
        if (obj != NULL) {
            obj->unk84.uh = id;
            obj->animation_speed = speed;
            obj->unk138 = 0;
            obj->unk103 = 0;
            obj->unkB4 = 0.0f;
            obj->unk1C4 = *(s32 *) (entry + 2);
            if (index < D_8008FD8C) {
                D_800CC2D0[index].unk31C->unk58 = 0;
                D_800CC2D0[index].unk31C->unk5A = 0;
                D_800CC2D0[index].unk31C->unk59 = 0;
            }
        }
        if (anim->unk28 != 0) {
            count = anim->unk3C;
            if (1.0f <= blend) {
                anim->unk3A = 500 / (s16) (s32) blend;
                if (anim->unk3C > 0 && id == (anim->unk6 & 0x7FFF)) {
                    anim->unk3C = 0x3FF - anim->unk3C;
                    count = 0;
                } else if (count < 600) {
                    anim->unk3C = 0x3FF;
                }
            } else {
                anim->unk3C = 0;
            }
            if (count < 600) {
                anim->unk6 = anim->unk4;
                anim->unkC = anim->unk8;
                anim->unk14 = anim->unk10;
                anim->unk24 = anim->unk20;
                anim->unk1C = anim->unk18;
                anim->unk39 = anim->unk38;
                anim->unk2C = anim->unk28;
                bcopy(anim->unk40, anim->unk210, 0x1D0);
            }
        }
        anim->unk4 = id;
        if (hold != 0) {
            anim->unk4 = id | 0x8000;
        }
        anim->unk8 = frame;
        anim->unk10 = speed;
        anim->unk20 = loop_start;
        anim->unk0 = (entry != NULL) ? D_800866AC[entry[1]] : 0;

        if (obj != NULL && obj->unk58 != 0) {
            hdr = func_1502AF04(obj->unk58, buf, file, 2);
        } else {
            hdr = (s32 *) func_1502B110(NULL, 2, (s32) buf, 3, kind, set, file);
        }
        /* asm: with no header, data / size are stack leftovers; 0 here (= no animation) */
        if (hdr != NULL) {
            anim->unk28 = hdr[2];
            size = hdr[1];
            data = hdr[0];
        }
        if (size == 0) {
            func_1505DFDC(obj);
            return;
        }
        size16 = (size + 15) & ~15;
        if (size16 < 200) {
            func_1000480C(data, anim->unk40, size16);
        } else {
            func_10004514(data, anim->unk40, size16, 1);
        }

        anim->unk18 = anim->unk40[3];
        if (anim->unk40[3] == 0xFF && obj != NULL) {
            switch (obj->id) {
                case 0x92:
                    anim->unk18 = D_800997B8[obj->unk84.uh];
                    break;
                case 0xB7:
                case 0xB8:
                case 0xB9:
                    anim->unk18 = 641.0f;
                    break;
            }
        }
        if (obj != NULL) {
            obj->unk24E = 0;
            obj->unk1FC = (obj->unk1FC | 2) & ~1;
            flags = (obj->stunned == 0) ? 0x30B : 0x303;
            obj->unkF4 &= ~flags;
            if (obj->unkF4 & 0x20) {
                obj->unkF4 |= 2;
                obj->unkF4 &= ~0x20;
            }
            obj->unk1FD = (anim->unk40[7] & 0x20) ? anim->unk40[0xB] : 0;
        }
        if (anim->unk40[5] == 0) {
            anim->unk28 = 1;
        }
    }
    if (obj != NULL && start != 0) {
        func_150627D4(obj);
    }
    return;
}
