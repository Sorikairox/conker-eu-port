// obj_texture_anim_step: steps the animated texture of a scenery object. The first D_800896C4 entry that applies
// (level filter -1 or the current level D_800BE9F0; id 0xFF = any, else the object's +0x54 type, with 0x8000 set for
// level-filtered entries) gives the frame table, frame count, ticks per frame and ping-pong flag. *slots holds the
// object's texture slot (looked up once from its +0x1C texture list by func_1511A998: index << 16 | slot) and
// *state the playing direction (high half) and the tick counter (low half). The frame texture is loaded
// (func_1510D66C, age 3 on levels 6 / 0x3B else 0x3E) and patched into the display list (func_1510DDF4).
typedef struct {
    /* 0x0 */ s32 *frames;
    /* 0x4 */ u8 count;
    /* 0x5 */ u8 id;
    /* 0x6 */ s8 level;
    /* 0x7 */ u8 ticks;
    /* 0x8 */ u8 pingpong;
} TexAnim; // 0xC
extern TexAnim D_800896C4[24];
s32 func_1511A998(s8 *arg0, s32 *arg1);
s32 func_1510D66C(s32 id, s32 *outSize, s32 age, s32 addRef);
void func_1510DDF4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_1511AA1C(u8 *obj, s32 *slots, s32 *state) {
    TexAnim *e;
    TexAnim *found = NULL;
    s32 id;
    s32 second;
    s32 dir;
    s32 tick;
    s32 tex;
    s32 size;
    s32 end;

    for (e = D_800896C4; e != D_800896C4 + 24; e++) {
        id = e->id;
        if (e->level != -1) {
            if (D_800BE9F0 != e->level) {
                continue;
            }
            if (id != 0xFF) {
                id |= 0x8000;
            }
        }
        if (id == 0xFF || id == *(u16 *)(obj + 0x54)) {
            found = e;
            break;
        }
    }
    if (found == NULL) {
        return;
    }
    if (*slots == 0) {
        *slots = func_1511A998(*(s8 **)(obj + 0x1C), &second);
        *slots |= second << 16;
    } else {
        second = (*slots >> 16) & 0xFFFF;
    }
    dir = (s16)(*state >> 16);
    if (dir == 0) {
        dir = 1;
    }
    tick = (*state & 0xFFFF) + dir;
    if (found->pingpong) {
        if (tick < 0) {
            dir = 1;
            tick = found->ticks;
        } else if (tick >= found->count * found->ticks) {
            dir = -1;
            tick = (found->count - 1) * found->ticks;
        }
    } else if (tick >= found->count * found->ticks) {
        tick -= found->count * found->ticks;
        dir = 1;
    }
    tex = func_1510D66C(found->frames[tick / found->ticks], &size,
                        (D_800BE9F0 == 6 || D_800BE9F0 == 0x3B) ? 3 : 0x3E, 0);
    end = 0;
    if (second != 0) {
        end = size + tex - 0x20;
    }
    func_1510DDF4((s32)obj, tex, end, 4, 5);
    *state = (dir << 16) | tick;
}
