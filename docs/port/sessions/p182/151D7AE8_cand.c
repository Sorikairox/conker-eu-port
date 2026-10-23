// linked_obj_event_3d: event handler of an object whose link record sits at +0x40 ({ s32 id, u8 key }): event 0x3D removes the
// object (func_1516972C) when the event's record matches by id or by key; any other event goes to the common
// handler func_15149514.
void func_151D7AE8(struct102 *obj, u8 *ev, u8 type) {
    u8 *link = (u8 *) obj + 0x40;

    if (type == 0x3D) {
        if (*(s32 *) link == *(s32 *) ev || link[4] == ev[4]) {
            func_1516972C(obj);
        }
    } else {
        func_15149514((s32) ev, type, (s32) link, (s32) (link + 4), (s32) obj);
    }
}
