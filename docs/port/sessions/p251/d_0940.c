#ifdef NON_MATCHING
void func_15163DEC(u8 *arg0, u8 *arg1);
s32 func_15163F50(u8 *arg0, u8 *arg1);

// light_effect_update_18: handler 18 of D_8008B490 (P251): the dispatcher func_151603FC tests the result, which is
// func_15163F50's v0 left in place by the matched void C; s32 here (as func_15161F2C), one signature for wasm
s32 func_15190940(u8 *arg0) {
    func_15163DEC(arg0, arg0 + 0x20);
    return func_15163F50(arg0, arg0 + 0x18);
}
#else
void func_15190940(u8 *arg0) {
    func_15163DEC(arg0, arg0 + 0x20);
    func_15163F50(arg0, arg0 + 0x18);
}
#endif
