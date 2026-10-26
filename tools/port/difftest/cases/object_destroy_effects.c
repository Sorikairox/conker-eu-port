extern u8 D_800BE616;
extern s32 g_level_id; /* was D_800BE9F0 */
extern u8 D_800C35EA;
void obj_impact_burst_spawn(u8 *arg0, u8 arg1, s32 arg2);
void object_land_puff(u8 *obj);
void explosion_ground_effect(struct127 *arg0);
void fx_big_explosion_at_obj(u8 *arg0, s32 arg1, s32 arg2);
void object_explode_big(struct127 *obj, u8 arg1, s32 arg2);
void object_shatter_effects(u8 *obj, u8 flag, s32 arg2);
void obj_debris_dust_burst(u8 *arg0, s32 arg1, s32 arg2);
void object_set_all_flags(s32 arg0, s32 arg1);
void owner_spawn_children(u8 *owner);
s32 player_hit_reaction(struct127 *obj, s32 kind);
void object_model_shatter(u8 *obj, u8 arg1, s32 arg2);
void obj_set_destroyed(struct127 *arg0);
u8 *world_record_find(u8 id);
struct127 *player_find_owned_object(struct127 *owner); // test copy: callee ignores a1 / a2
s32 object_hit_effects(u8 *obj, u8 smoke, u8 splats, u8 debris, u8 finish, u8 fewer, u8 arg6, s32 arg7);
void object_break_effects(u8 *obj, u8 owner, s32 arg2);
void object_impact_debris_hard(u8 *obj);
void object_impact_debris(u8 *obj);
void object_explosion_effects(u8 *obj, u8 arg1, s32 arg2);
void object_explode(u8 *obj, u8 owner, s32 arg2);
void destroy_burst_spawn(struct127 *arg0, u8 arg1, s32 arg2);
/* object_destroy_effects: the break / death effects of an object by its type (byte +4): one effect function per
 * type (owner 0xFF, flag 1), the type-0x20 crate picks the hard / soft debris by its y speed +0x20. Types 5 /
 * 0xAD..0xAF clear +0x328, release (object_set_all_flags / owner_spawn_children) and return 1. Types 0x28 / 0x77 shatter the
 * model, drop the held item and spawn a pickup record (world_record_find: multiplayer id obj[0x127] + 11 after
 * player_hit_reaction(obj, 6), else id 1 in level 0x23) placed at the object; multiplayer types 0x28 / 0x77 / 0x53 /
 * 0x90 (level 0x33 only) return 2 (respawn), everything else 0. */
s32 object_destroy_effects(struct127 *arg0) {
    u8 *obj = (u8 *) arg0;
    u8 *rec;
    struct127 *item;

    switch (obj[4]) {
        case 0x05:
        case 0xAD:
        case 0xAE:
        case 0xAF:
            obj[0x328] = 0;
            object_set_all_flags((s32) obj, 0);
            owner_spawn_children(obj);
            return 1;
        case 0x0D:
            object_break_effects(obj, 0xFF, 1);
            break;
        case 0x10:
        case 0x38:
        case 0x91:
            object_land_puff(obj);
            break;
        case 0x20:
            if (*(f32 *) (obj + 0x20) < -20.0f) {
                object_impact_debris_hard(obj);
            } else {
                object_impact_debris(obj);
            }
            break;
        case 0x25:
            if (*(s32 *) (obj + 0x2EC) != 0 || g_level_id == 6 || g_level_id == 0x3B) {
                object_shatter_effects(obj, 0xFF, 1);
            }
            break;
        case 0x28:
        case 0x77:
            rec = NULL;
            object_model_shatter(obj, 0xFF, 1);
            obj_set_destroyed(arg0);
            if (D_800BE616 != 0) {
                player_hit_reaction(arg0, 6);
                rec = world_record_find(obj[0x127] + 0xB);
            } else {
                if (g_level_id == 0x23) {
                    rec = world_record_find(1);
                }
                item = player_find_owned_object(arg0);
                if (item != NULL && D_800C35EA != 1) {
                    object_hit_effects((u8 *) item, 1, 1, 1, 1, 0, 0xFF, 1);
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
            object_explode(obj, 0xFF, 1);
            break;
        case 0x3A:
        case 0x3D:
            explosion_ground_effect(arg0);
            break;
        case 0x44:
            destroy_burst_spawn(arg0, 0xFF, 1);
            break;
        case 0x47:
            object_explode_big((struct127 *) obj, 0xFF, 1);
            break;
        case 0x4A:
            fx_big_explosion_at_obj(obj, 0xFF, 1);
            break;
        case 0x4F:
        case 0x83:
            object_explosion_effects(obj, 0xFF, 1);
            break;
        case 0x53:
            if (D_800BE616 != 0) {
                player_hit_reaction(arg0, 10);
                return 2;
            }
            break;
        case 0x79:
            obj_debris_dust_burst(obj, 0xFF, 1);
            break;
        case 0x7F:
            obj_impact_burst_spawn(obj, 0xFF, 1);
            break;
        case 0x90:
            if (D_800BE616 != 0 && g_level_id == 0x33) {
                player_hit_reaction(arg0, 8);
                return 2;
            }
            break;
    }
    return 0;
}
