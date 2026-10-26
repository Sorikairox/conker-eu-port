extern f32 g_obj_effect_vec[3];   /* vector copied to D_eu_800D1990 for the effect handlers; was D_800CC674 */
typedef void (*ObjEffectHandler)(u8 *obj, void *arg);
extern ObjEffectHandler g_obj_effect_fns[15];   /* .data: obj_effect_debris_spray .. obj_effect_ground_blast_alt; was D_800864B0 */
// obj_effect_dispatch: effect `type` (0..14) on obj: publishes obj's vector at +0x2C as the effect point g_obj_effect_pos and
// g_obj_effect_vec as the effect vector D_eu_800D1990, then runs the type's handler g_obj_effect_fns[type](obj, arg) (NULL = none).
void obj_effect_run_handler(u8 *obj, s32 type, void *arg) {
    f32 *point = (f32 *) g_obj_effect_pos;
    f32 *vec = (f32 *) D_eu_800D1990;
    void (*handler)(u8 *obj, void *arg);

    if (type < 0 || type >= 15) {
        return;
    }
    point[0] = *(f32 *) (obj + 0x2C);
    point[1] = *(f32 *) (obj + 0x30);
    point[2] = *(f32 *) (obj + 0x34);
    vec[0] = g_obj_effect_vec[0];
    vec[1] = g_obj_effect_vec[1];
    vec[2] = g_obj_effect_vec[2];
    handler = g_obj_effect_fns[type];
    if (handler != NULL) {
        handler(obj, arg);
    }
}
