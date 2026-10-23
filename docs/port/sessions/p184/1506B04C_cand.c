extern f32 D_800CC674[3];   /* vector copied to D_eu_800D1990 for the effect handlers */
typedef void (*ObjEffectHandler)(u8 *obj, void *arg);
extern ObjEffectHandler D_800864B0[15];   /* .data: func_1506A9B0 .. func_1506AF84 */
// obj_effect_dispatch: effect `type` (0..14) on obj: publishes obj's vector at +0x2C as the effect point D_800D1980 and
// D_800CC674 as the effect vector D_eu_800D1990, then runs the type's handler D_800864B0[type](obj, arg) (NULL = none).
void func_1506B04C(u8 *obj, s32 type, void *arg) {
    f32 *point = (f32 *) D_800D1980;
    f32 *vec = (f32 *) D_eu_800D1990;
    void (*handler)(u8 *obj, void *arg);

    if (type < 0 || type >= 15) {
        return;
    }
    point[0] = *(f32 *) (obj + 0x2C);
    point[1] = *(f32 *) (obj + 0x30);
    point[2] = *(f32 *) (obj + 0x34);
    vec[0] = D_800CC674[0];
    vec[1] = D_800CC674[1];
    vec[2] = D_800CC674[2];
    handler = D_800864B0[type];
    if (handler != NULL) {
        handler(obj, arg);
    }
}
