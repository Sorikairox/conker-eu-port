u8 *func_1518E934(u8 **arg0, u8 arg1);
// character_effect_attach: attaches effect `type` (1..18: fire, smoke, impacts, ...) to obj: a kind-0x21 effect record
/* (func_1518E934, for view `view`) holding obj, obj's id byte +0x3B, a duration, a flag byte, a direction byte and the
 * effect number. With `clear`, first frees (func_1516972C) every kind-0x21 record of both groups that belongs to obj
 * or to obj's id (the list walk keeps the next pointer in D_800DD5C8[depth] like the other list walks).
 * Types 13, 14, 15, 16 and 18 take `time` as the duration (13, 15, 16: flag 0 for time 999 = endless); types 10..12
 * set the flag from obj +0x1CA. Returns the record, NULL for no obj, an unknown type or no record.
 * `arg5` and `name` (the effect's debug name) are not used. */
u8 *func_1518D1C0(u8 *obj, s16 type, s16 time, u8 clear, u8 view, s32 arg5, char *name) {
    struct {
        u8 *owner;  /* 0x0 */
        u8 id;      /* 0x4 obj +0x3B */
        u8 pad5;
        s16 time;   /* 0x6 */
        u8 flag;    /* 0x8 */
        s8 dir;     /* 0x9 */
        u8 effect;  /* 0xA */
        u8 padB;
    } e;
    struct_eu_node *node;
    s32 i;

    if (obj == NULL) {
        return NULL;
    }
    if (clear) {
        for (i = 0; i < 2; i++) {
            D_800DD5C0++;
            node = D_800DD280[i][0x21];
            while (node != NULL) {
                D_800DD5C8[D_800DD5C0] = node->next;
                if (*(u8 **)((u8 *)node + 0x18) == obj || obj[0x3B] == ((u8 *)node)[0x1C]) {
                    func_1516972C((struct102 *)node);
                }
                node = D_800DD5C8[D_800DD5C0];
            }
            D_800DD5C0--;
        }
    }
    e.owner = obj;
    e.id = obj[0x3B];
    switch (type) {
    case 1: e.time = 500; e.flag = 1; e.dir = 0; e.effect = 1; break;
    case 2: e.time = 3000; e.flag = 1; e.dir = 1; e.effect = 7; break;
    case 3: e.time = 200; e.flag = 1; e.dir = -1; e.effect = 8; break;
    case 4: e.time = 200; e.flag = 1; e.dir = -1; e.effect = 9; break;
    case 5: e.time = 3000; e.flag = 0; e.dir = -1; e.effect = 2; break;
    case 6: e.time = 3000; e.flag = 0; e.dir = -1; e.effect = 3; break;
    case 7: e.time = 3000; e.flag = 0; e.dir = -1; e.effect = 4; break;
    case 8: e.time = 3000; e.flag = 0; e.dir = -1; e.effect = 5; break;
    case 9: e.time = 3000; e.flag = 0; e.dir = -1; e.effect = 6; break;
    case 10: e.time = 75; e.flag = obj[0x1CA] ? 1 : 0; e.dir = 1; e.effect = 7; break;
    case 11: e.time = 75; e.flag = obj[0x1CA] ? 1 : 0; e.dir = 0; e.effect = 1; break;
    case 12: e.time = 75; e.flag = obj[0x1CA] ? 1 : 0; e.dir = 1; e.effect = 7; break;
    case 13: e.time = time; e.flag = (time == 999) ? 0 : 1; e.dir = -1; e.effect = 10; break;
    case 14: e.time = time; e.flag = 1; e.dir = -1; e.effect = 11; break;
    case 15: e.time = time; e.flag = (time == 999) ? 0 : 1; e.dir = -1; e.effect = 12; break;
    case 16: e.time = time; e.flag = (time == 999) ? 0 : 1; e.dir = -1; e.effect = 13; break;
    case 17: e.time = 300; e.flag = 1; e.dir = -1; e.effect = 14; break;
    case 18: e.time = time; e.flag = 1; e.dir = -1; e.effect = 15; break;
    default: return NULL;
    }
    return func_1518E934((u8 **)&e, view);
}
