extern u8 D_800BE616;
extern s32 D_800BE9F0;
extern u8 D_800C35EA;
void func_150B0828(u8 *arg0, u8 arg1, s32 arg2);
void func_150C04E0(u8 *obj);
void func_150D8ABC(struct127 *arg0);
void func_150F2290(u8 *arg0, s32 arg1, s32 arg2);
void func_151C9740(struct127 *obj, u8 arg1, s32 arg2);
void func_151CFFFC(u8 *obj, u8 flag, s32 arg2);
void func_150BE994(u8 *arg0, s32 arg1, s32 arg2);
void func_1507DB44(s32 arg0, s32 arg1);
void func_150AEB9C(u8 *owner);
s32 func_1507CD64(struct127 *obj, s32 kind);
void func_151BAAC8(u8 *obj, u8 arg1, s32 arg2);
void func_15145A50(struct127 *arg0);
u8 *func_151149AC(u8 id);
struct127 *func_1507515C(struct127 *owner); // test copy: callee ignores a1 / a2
s32 func_15136C3C(u8 *obj, u8 smoke, u8 splats, u8 debris, u8 finish, u8 fewer, u8 arg6, s32 arg7);
void func_150B8020(u8 *obj, u8 owner, s32 arg2);
void func_150BC968(u8 *obj);
void func_150BC03C(u8 *obj);
void func_151A7240(u8 *obj, u8 arg1, s32 arg2);
void func_150E0DF0(u8 *obj, u8 owner, s32 arg2);
void func_151D2860(struct127 *arg0, u8 arg1, s32 arg2);
/* object_destroy_effects: the break / death effects of an object by its type (byte +4): one effect function per
 * type (owner 0xFF, flag 1), the type-0x20 crate picks the hard / soft debris by its y speed +0x20. Types 5 /
 * 0xAD..0xAF clear +0x328, release (func_1507DB44 / func_150AEB9C) and return 1. Types 0x28 / 0x77 shatter the
 * model, drop the held item and spawn a pickup record (func_151149AC: multiplayer id obj[0x127] + 11 after
 * func_1507CD64(obj, 6), else id 1 in level 0x23) placed at the object; multiplayer types 0x28 / 0x77 / 0x53 /
 * 0x90 (level 0x33 only) return 2 (respawn), everything else 0. */
s32 func_1507D754(struct127 *arg0) {
    u8 *obj = (u8 *) arg0;
    u8 *rec;
    struct127 *item;

    switch (obj[4]) {
        case 0x05:
        case 0xAD:
        case 0xAE:
        case 0xAF:
            obj[0x328] = 0;
            func_1507DB44((s32) obj, 0);
            func_150AEB9C(obj);
            return 1;
        case 0x0D:
            func_150B8020(obj, 0xFF, 1);
            break;
        case 0x10:
        case 0x38:
        case 0x91:
            func_150C04E0(obj);
            break;
        case 0x20:
            if (*(f32 *) (obj + 0x20) < -20.0f) {
                func_150BC968(obj);
            } else {
                func_150BC03C(obj);
            }
            break;
        case 0x25:
            if (*(s32 *) (obj + 0x2EC) != 0 || D_800BE9F0 == 6 || D_800BE9F0 == 0x3B) {
                func_151CFFFC(obj, 0xFF, 1);
            }
            break;
        case 0x28:
        case 0x77:
            rec = NULL;
            func_151BAAC8(obj, 0xFF, 1);
            func_15145A50(arg0);
            if (D_800BE616 != 0) {
                func_1507CD64(arg0, 6);
                rec = func_151149AC(obj[0x127] + 0xB);
            } else {
                if (D_800BE9F0 == 0x23) {
                    rec = func_151149AC(1);
                }
                item = func_1507515C(arg0);
                if (item != NULL && D_800C35EA != 1) {
                    func_15136C3C((u8 *) item, 1, 1, 1, 1, 0, 0xFF, 1);
                }
            }
            if (rec != NULL) {
                rec[0x6E] = 0;
                *(s16 *) (rec + 0x10) = *(f32 *) (obj + 0x14);
                *(s16 *) (rec + 0x12) = *(f32 *) (obj + 0x18);
                *(s16 *) (rec + 0x14) = *(f32 *) (obj + 0x1C);
                *(f32 *) (rec + 0x0) = *(f32 *) (obj + 0xB8);
                *(f32 *) (rec + 0x4) = *(f32 *) (obj + 0x40);
                *(f32 *) (rec + 0x8) = *(f32 *) (obj + 0xC4);
                rec[0x8A] = 0xFF;
                *(s32 *) (rec + 0x7C) = 0;
                *(s32 *) (rec + 0x80) = 0;
                *(s32 *) (rec + 0x84) = 0;
            }
            return (D_800BE616 != 0) ? 2 : 0;
        case 0x34:
            func_150E0DF0(obj, 0xFF, 1);
            break;
        case 0x3A:
        case 0x3D:
            func_150D8ABC(arg0);
            break;
        case 0x44:
            func_151D2860(arg0, 0xFF, 1);
            break;
        case 0x47:
            func_151C9740((struct127 *) obj, 0xFF, 1);
            break;
        case 0x4A:
            func_150F2290(obj, 0xFF, 1);
            break;
        case 0x4F:
        case 0x83:
            func_151A7240(obj, 0xFF, 1);
            break;
        case 0x53:
            if (D_800BE616 != 0) {
                func_1507CD64(arg0, 10);
                return 2;
            }
            break;
        case 0x79:
            func_150BE994(obj, 0xFF, 1);
            break;
        case 0x7F:
            func_150B0828(obj, 0xFF, 1);
            break;
        case 0x90:
            if (D_800BE616 != 0 && D_800BE9F0 == 0x33) {
                func_1507CD64(arg0, 8);
                return 2;
            }
            break;
    }
    return 0;
}
