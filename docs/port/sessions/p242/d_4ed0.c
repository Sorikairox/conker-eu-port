#ifdef NON_MATCHING
u8 *func_15031C4C(struct127 *, s32, s32);

// object_fire_message: message handler of the func_150D3870 effect object (D_8008A760 handler table). data = +0x98
// ({owner object, its room byte, effect handle, ...}). Messages 0, 0x2E and 3: when the message names the owner
// (msg +0 == owner, or msg +4 byte == room) the effect object removes itself (func_1516972C). Message 0x2D (object
// replaced, msg = {old, new, ..., room of old (+8), room of new (+9)}): when the owner is msg +0, it moves to msg +4
// (room +9), when it is msg +4 it moves to msg +0 (room +8); either way it takes a new effect handle for the new
// owner (func_15031C4C 0x79, 0x7A when the owner's id is 0x48).
void func_150D4ED0(u8 *obj, u8 *msg, u8 event) {
    u8 *data = *(u8 **) (obj + 0x98);
    struct127 *owner;

    if (event == 0 || event == 0x2E || event == 3) {
        if (*(struct127 **) msg == *(struct127 **) data || data[4] == msg[4]) {
            func_1516972C((struct102 *) obj);
        }
    } else if (event == 0x2D) {
        if (*(struct127 **) msg == *(struct127 **) data) {
            owner = *(struct127 **) (msg + 4);
            *(struct127 **) data = owner;
            data[4] = msg[9];
        } else if (*(struct127 **) (msg + 4) == *(struct127 **) data) {
            owner = *(struct127 **) msg;
            *(struct127 **) data = owner;
            data[4] = msg[8];
        } else {
            return;
        }
        *(u8 **) (data + 8) = func_15031C4C(owner, (owner->id == 0x48) ? 0x7A : 0x79, 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D4ED0.s")
#endif
