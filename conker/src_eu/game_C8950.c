#include <ultra64.h>
#include "functions.h"
#include "variables.h"


struct249 *event_find(s16 arg0);
void save_block_realloc_random(void);
void game_over_apply_pending(void);
struct249 *event_start(s32 id, s32 arg1);


/* was func_1509B4A0 */
void event_start_level_events(s32 arg0, s32 arg1) {
    s32 i;

    if(0) {};

    g_dbg_crash_marker = 0x5000000;
    save_block_realloc_random();
    camera_timed_records_clear();

    for (i = 0; i < g_level_event_count; i++) {
        if (event_prereqs_met(g_level_event_ids[i])) {
            event_start(g_level_event_ids[i], arg1);
        }
    }

    game_over_apply_pending();
    g_dbg_crash_marker = 0;
}

/* was func_1509B570 */
u16 *event_get_vars(s32 arg0) {
    struct248 *temp_v0;
    u16 res;

    temp_v0 = event_find(arg0);
    if (temp_v0 != 0) {
        res = temp_v0->unkA;
        return (s32)temp_v0 + (res & 0xFFFF);
    }
    return NULL;
}

struct249 *event_find(s16 arg0);
struct249 *event_load(s16 arg0);
void event_link_sorted(struct249 *arg0);
void event_vm_run(struct249 *, s32);

/* event_start: start event `id` (arg1 = 0: level start, skipped when the event's own save bit is set). An event not yet in the
 * list is loaded (event_load), linked (event_link_sorted) and run once from entry 0 unless the save bit of its flags
 * (flags & 0x3FF) is set; flag 0x4000 marks it started (always at level start, else only with flag 0x400). An event
 * already in the list with flag 0x1000 and not 0x800 gets its variables cleared when arg1 != 0. */
/* was func_1509B5AC */
struct249 *event_start(s32 id, s32 arg1) {
    struct249 *e = event_find(id);
    u8 *save = (u8 *) g_save_progress_bits;
    u16 flags;
    s32 bit;

    if (arg1 == 0 && (save[id >> 3] & (1 << (id & 7)))) {
        return NULL;
    }
    if (e == NULL) {
        e = event_load(id);
        event_link_sorted(e);
        flags = e->unk0;
        bit = flags & 0x3FF;
        if (!(save[bit >> 3] & (1 << (bit & 7)))) {
            g_dbg_crash_marker = 0x6000000;
            event_vm_run(e, 0);
            g_dbg_crash_marker = 0;
            flags = e->unk0;
        }
        if (arg1 == 0 || (flags & 0x400)) {
            e->unk0 = flags | 0x4000;
        }
        return e;
    }
    if (arg1 != 0) {
        flags = e->unk0;
        if ((flags & 0x1000) && !(flags & 0x800)) {
            bzero((u8 *) e + ((struct_eu_C8950_blk *) e)->unkA, ((struct_eu_C8950_blk *) e)->unk6);
        }
    }
    return e;
}

/* was func_1509B704 */
struct249 *event_find(s16 arg0) {
    struct249 *tmp;
    s32 mask = 0xFFFF03FF;
    s32 i;

    tmp = g_event_list.unk4;
    for (i = 0; i < g_event_list.length; i++) {
        if (arg0 == (tmp->unk0 & mask)) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}


/* was func_1509B764 */
void event_unlink_free(struct249 *arg0) {
    if (g_event_list.length == 1) {
        g_event_list.unk4 = NULL;
        g_event_list.unk8 = NULL;
    } else {
        if (arg0 == g_event_list.unk4) {
            g_event_list.unk4 = arg0->next;
            arg0->next->prev = NULL;
        } else {
            arg0->prev->next = arg0->next;
        }
        if (arg0 == g_event_list.unk8) {
            g_event_list.unk8 = arg0->prev;
            arg0->prev->next = NULL;
        } else {
            arg0->next->prev = arg0->prev;
        }
    }
    heap_free(arg0);
    g_event_list.length--;
}

/* was func_1509B810 */
void event_link_sorted(struct249 *arg0) {
    s32 var_a3;
    struct249 *temp_v0;
    struct249 *var_v0;
    s32 key;
    var_v0 = g_event_list.unk8;
    key = arg0->unk0 & ~0xFC00;
    if (g_event_list.length == 0) {
        g_event_list.unk4 = arg0;
        g_event_list.unk8 = arg0;
        arg0->next = NULL;
        arg0->prev = NULL;
        g_event_list.length += 1;
        return;
    }
    var_a3 = 0;
    if ((s32) g_event_list.length > 0) {
        do {
            var_a3 += 1;
            if ((var_v0->unk0 & ~0xFC00) < key) {
                if (var_v0 == g_event_list.unk8) {
                    arg0->prev = var_v0;
                    arg0->next = NULL;
                    var_v0->next = arg0;
                    g_event_list.unk8 = arg0;
                    g_event_list.length += 1;
                    return;
                }
                arg0->prev = var_v0;
                arg0->next = var_v0->next;
                var_v0->next->prev = arg0;
                var_v0->next = arg0;
                g_event_list.length += 1;
                return;
            }
            var_v0 = var_v0->prev;
        } while (var_a3 < (s32) g_event_list.length);
    }
    temp_v0 = g_event_list.unk4;
    g_event_list.unk4 = arg0;
    arg0->prev = NULL;
    arg0->next = temp_v0;
    temp_v0->prev = arg0;
    g_event_list.length += 1;
}

/* event_load: load event block `arg0` (asset 20) and relocate it; the caller event_start uses the result (the matching
 * void version leaves it in v0). */
/* was func_1509B8FC */
struct249 *event_load(s16 arg0) {
    struct248 *temp_v0;
    s16 sp18[2];

    temp_v0 = asset_load(&sp18, 2, 20, arg0);
    temp_v0->unk0 |= arg0;
    temp_v0->unk2 = g_level_id;
    return (struct249 *) event_block_relocate((struct_eu_C8950_blk *) temp_v0);
}

/* event_block_relocate: relocate a loaded event block: the variable area (unk6 bytes) goes after the script at an 8-aligned offset
 * (unkA), the block size is rounded up to 8, the block is copied to a new allocation with the variables cleared,
 * and the old block is freed. */
/* was func_1509B950 */
struct_eu_C8950_blk *event_block_relocate(struct_eu_C8950_blk *blk) {
    struct_eu_C8950_blk *new;
    u16 pos;

    pos = blk->unk4 + (8 - (((s32) blk + blk->unk4) & 7));
    blk->unk4 = pos + blk->unk6;
    blk->unkA = pos;
    blk->unk4 = blk->unk4 - (((s32) blk + blk->unk4) & 7) + 8;
    new = (struct_eu_C8950_blk *) allocate_memory(blk->unk4, 0xFF, 2, 0);
    if (new == NULL) {
        while (1) {
        }
    }
    bcopy((void *) blk, (void *) new, blk->unk4);
    bzero((u8 *) new + new->unkA, new->unk6);
    heap_free((s32) blk);
    return new;
}
// NON-MATCHING: register allocation of pad/pos swapped (v1/t0)
// struct_eu_C8950_blk *event_block_relocate(struct_eu_C8950_blk *arg0) {
//     u16 pos;
//     s32 pad;
//     struct_eu_C8950_blk *new;
//
//     pad = 8 - (((s32)arg0 + arg0->unk4) & 7);
//     pos = arg0->unk4 + pad;
//     arg0->unk4 = pos + arg0->unk6;
//     arg0->unkA = pos;
//     arg0->unk4 = arg0->unk4 - (((s32)arg0 + arg0->unk4) & 7) + 8;
//     new = allocate_memory(arg0->unk4, 0xFF, 2, 0);
//     if (new == NULL) {
//         while (1) {
//         }
//     }
//     bcopy(arg0, new, arg0->unk4);
//     bzero((u8 *)new + new->unkA, new->unk6);
//     heap_free(arg0);
//     return new;
// }

void event_vm_run(struct249 *, s32);
void event_unlink_free(struct249 *);
void event_send_cmd36(void);

/* was func_1509BA04 */
void event_list_unload(s32 arg0) {
    s32 count;
    s32 i;
    s32 id;
    s32 byte;
    s32 bit;
    u16 flags;
    struct249 *e;
    struct249 *next;
    u8 *state = (u8 *)&g_event_states;

    e = g_event_list.unk4;
    count = g_event_list.length;
    if (g_game_flags_dirty != 0) {
        event_send_cmd36();
        g_game_flags_dirty = 0;
    }
    for (i = 0; i < count; i++) {
        flags = e->unk0;
        id = flags & 0xFFFF03FF;
        byte = id >> 3;
        bit = 1 << (id & 7);
        next = e->next;
        if ((((u8 *)g_save_progress_bits)[byte] & bit) && arg0 == 0) {
            event_unlink_free(e);
            state[id] = 3;
        } else if (arg0 != 0 || (flags & 0x8000) ||
                   ((flags & 0x1000) && g_level_id != *(u16 *)((u8 *)e + 2))) {
            g_dbg_crash_marker = 0x06000001;
            event_vm_run(e, 3);
            g_dbg_crash_marker = 0;
            event_unlink_free(e);
            if (((u8 *)g_save_progress_bits)[byte] & bit) {
                state[id] = 3;
            } else {
                state[id] = 0;
            }
        }
        e = next;
    }
}
s32 event_dispatch(s32, s32, ...);
void event_vm_run(struct249 *, s32);
extern s16 g_level_start_mode; /* was D_800BEE12 */
extern s32 g_event_cur_id; /* was D_800D3268 */
extern s32 g_save_bits_changed; /* was D_800D3378 */

/* was func_1509BBA0 */
void event_list_run_phase(s32 arg0) {
    s32 temp_v0;
    s32 var_a1;
    s32 var_s5;
    struct249 *var_s0;
    u16 temp_a2;
    u16 temp_t1;
    u16 var_v1;

    var_s0 = g_event_list.unk4;
    camera_timed_records_update();
    if ((g_mp_mode_active != 0) || (g_level_id == 0x32) || (event_dispatch(0, 0x2000, 0x93) != 0) || (arg0 != 2)) {
        event_send_cmd36();
        temp_a2 = g_event_list.length;
        var_s5 = 0;
        if ((s32) temp_a2 > 0) {
            do {
                temp_v0 = var_s0->unk0 & 0x3FF;
                g_event_cur_id = temp_v0;
                var_v1 = var_s0->unk0;
                var_a1 = var_v1 & 0x8000;
                if (var_a1 != 0) {
                    goto block_26;
                }
                if (arg0 == 4) {
                    if (((u8 *)g_save_progress_bits)[temp_v0 >> 3] & (1 << (temp_v0 & 7))) {
                        g_dbg_crash_marker = 0x06000002;
                        event_vm_run(var_s0, 4);
                        g_dbg_crash_marker = 0;
                        ((u8 *)&g_event_states)[temp_v0] = 3;
                        var_s0->unk0 |= 0x8000;
                        var_s0 = var_s0->next;
                    } else {
                        goto block_26;
                    }
                } else if (!(((u8 *)g_save_progress_bits)[temp_v0 >> 3] & (1 << (temp_v0 & 7)))) {
                    if (var_v1 & 0x4000) {
                        g_dbg_crash_marker = 0x06000003;
                        event_vm_run(var_s0, 1);
                        g_dbg_crash_marker = 0;
                        temp_t1 = var_s0->unk0 & 0xBFFF;
                        var_v1 = temp_t1 & 0xFFFF;
                        var_a1 = var_v1 & 0x8000;
                        var_s0->unk0 = temp_t1;
                    }
                    if (var_a1 != 0) {
                        var_s0 = var_s0->next;
                    } else {
                        if (!(var_v1 & 0x2000) || (g_level_id == (*(u16 *)((u8 *)var_s0 + 2)))) {
                            if ((arg0 == 2) || ((arg0 == 1) && !(var_v1 & 0x400))) {
                                g_dbg_crash_marker = 0x06000004;
                                event_vm_run(var_s0, arg0);
                                g_dbg_crash_marker = 0;
                            }
                            if (arg0 == 2) {
                                ((u8 *)&g_event_states)[temp_v0] = 1;
                            }
                        } else {
                            ((u8 *)&g_event_states)[temp_v0] = 2;
                        }
                        goto block_26;
                    }
                } else {
                    ((u8 *)&g_event_states)[temp_v0] = 3;
block_26:
                    var_s0 = var_s0->next;
                }
                var_s5 += 1;
            } while (var_s5 < (s32) temp_a2);
        }
        if (g_save_bits_changed != 0) {
    s32 pad;
            g_save_bits_changed = 0;
            event_start_level_events((s32) g_level_start_mode, 0);
        }
        g_event_vm_abort = 0;
    }
}
//
#include <stdarg.h>
extern s32 g_event_dispatch_args[]; /* was D_800D3380 */
extern s32 g_event_arg_count; /* was D_800D3C60 */
extern s32 (*g_event_query_fns[])(s32, s32, s32 *); /* was D_80088838 */

/* P43: variadic event dispatch. event_dispatch(n, id, arg, x1 .. xn): g_event_dispatch_args = {id & 0xFFF, arg, x1 .. xn},
 * g_event_arg_count = n + 2 during the call (restored after), returns g_event_query_fns[(id >> 12 & 0xF) - 1](id & 0xFFF, arg,
 * g_event_dispatch_args). Callers pass 3 to 8 words; every caller's NON_MATCHING prototype is now `(s32, s32, ...)`. */
/* was func_1509BE40 */
s32 event_dispatch(s32 n, s32 id, ...) {
    va_list ap;
    s32 saved;
    s32 arg;
    s32 i;
    s32 r;

    va_start(ap, id);
    saved = g_event_arg_count;
    arg = va_arg(ap, s32);
    g_event_dispatch_args[0] = id & 0xFFF;
    g_event_dispatch_args[1] = arg;
    for (i = 0; i < n; i++) {
        g_event_dispatch_args[i + 2] = va_arg(ap, s32);
    }
    va_end(ap);
    g_event_arg_count = n + 2;
    r = g_event_query_fns[((id & 0xF000) >> 12) - 1](id & 0xFFF, arg, g_event_dispatch_args);
    g_event_arg_count = saved;
    return r;
}

extern void (*g_event_action_fns[])(s32, s32, s32 *); /* was D_80088874 */

/* Variadic event dispatch like event_dispatch, on the second handler table: event_dispatch_alt(n, id, arg, x1 .. xn) sets
 * g_event_dispatch_args = {id & 0xFFF, arg, x1 .. xn} and g_event_arg_count = n + 2 for the call (restored after), then calls
 * g_event_action_fns[(id >> 12 & 0xF) - 1](id & 0xFFF, arg, g_event_dispatch_args). */
/* was func_1509BFB0 */
void event_dispatch_alt(s32 n, s32 id, s32 arg, ...) {
    va_list ap;
    s32 saved;
    s32 i;

    va_start(ap, arg);
    saved = g_event_arg_count;
    g_event_dispatch_args[0] = id & 0xFFF;
    g_event_dispatch_args[1] = arg;
    for (i = 0; i < n; i++) {
        g_event_dispatch_args[i + 2] = va_arg(ap, s32);
    }
    va_end(ap);
    g_event_arg_count = n + 2;
    g_event_action_fns[((id & 0xF000) >> 12) - 1](id & 0xFFF, arg, g_event_dispatch_args);
    g_event_arg_count = saved;
}

// need a bigger brain
/* was func_1509C120 */
void save_block_realloc_random(void) {
    s32 n;
    s32 i;
    struct102 *sp38[4];
    struct102 *sp34;
    n = random_int() & 3;
    sp34 = g_save_progress_bits;
    if (sp34 == NULL || (random_int() & 4)) {
        for (i = 0; i <= n; i++) {
            sp38[i] = (struct102 *)allocate_memory(0x1B, 0xFF, 2, 0);
        }
        for (i = 0; i <= n; i++) {
            if (i != n) {
                heap_free(sp38[i]);
            }
        }
        g_save_progress_bits = sp38[n];
        if (sp34 != NULL) {
            bcopy(sp34, g_save_progress_bits, 0x1B);
            heap_free(sp34);
        }
    }
}

/* was func_1509C228 */
void event_send_cmd36(void) {
    if ((g_hints_seen_b8 & 8) || (g_save_progress_bits->unkF & 1)) {
        event_dispatch_alt(2, 0x2000, 0x36, 0, 1);
        return;
    }
    event_dispatch_alt(2, 0x2000, 0x36, 1, 1);
}

/* was func_1509C2A4 */
s32 level_is_game_over_level(void) {
    s32 temp_v0 = g_level_id;
    if ((temp_v0 == 3) ||
        (temp_v0 == 5) ||
        (temp_v0 == 9) ||
        (temp_v0 == 13) ||
        (temp_v0 == 15) ||
        (temp_v0 == 17) ||
        (temp_v0 == 21) ||
        (temp_v0 == 22) ||
        (temp_v0 == 24) ||
        (temp_v0 == 26) ||
        (temp_v0 == 29) ||
        (temp_v0 == 31) ||
        (temp_v0 == 32) ||
        (temp_v0 == 33) ||
        (temp_v0 == 34) ||
        (temp_v0 == 36) ||
        (temp_v0 == 37) ||
        (temp_v0 == 42) ||
        (temp_v0 == 43) ||
        (temp_v0 == 45) ||
        (temp_v0 == 48) ||
        (temp_v0 == 51) ||
        (temp_v0 == 52) ||
        (temp_v0 == 56) ||
        (temp_v0 == 62) ||
        (temp_v0 == 63) ||
        (g_game_over_disabled != 0)
      ) {
        return 0;
    }
    return 1;
}

/* was func_1509C3A0 */
void game_over_apply_pending(void) {
    if ((g_game_over_pending != 0) && (g_game_over_disabled == 0) && (level_is_game_over_level() != 0)) {
        g_save_resume_level = (s8) g_level_load_id;
        if (g_cutscene_pending == 0) {
            save_request_slot_write(g_save_cur_slot);
        }
        g_game_over_pending = 0;
    }
}


/* was func_1509C414 */
s32 event_make_bank_id(s32 arg0) {
    return ((g_save_progress_bits->unk3 & 1) << 0xA) + arg0 + 0x1400;
}
