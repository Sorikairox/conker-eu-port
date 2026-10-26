#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/*
 * P106: the level event script VM, hand C.
 *
 * Rare wrote event_vm_run in assembly (the .s is marked "Handwritten function": it saves gp / fp, keeps its own sp in
 * D_800D3858 for the abort entry event_vm_abort, uses `add` / `sub` / `neg`, and dispatches through five jump tables).
 * This is a readable interpreter of the same machine, not a register-level translation.
 *
 * Event block (loaded by event_load, relocated by event_block_relocate), u16 header:
 *   +0x08 offset of the data area (operand mode 2), +0x0A offset of the variables (mode 1),
 *   +0x0E / +0x10 / +0x12 / +0x14 entry points 1..4; entry 0 starts at +0x20.
 * Instruction: one u16 opcode word, then up to three operands of one u16 each:
 *   bits 0-5 opcode, bit 6 "the first immediate operand is 32 bits (two u16, high first)",
 *   bits 13-15 / 10-12 / 7-9 addressing mode of operand 1 / 2 / 3.
 *   D_800876F8[opcode] = number of operands + 1.
 * Modes: 0 frame slot (frame + s16), 1 variable (vars + s16), 2 data address (data + s16; the value is the offset),
 *   3 / 4 / 6 immediate (4 = code offset, 6 = native function index), 5 the result register D_800D3C68.
 * Operand stack: D_800D3C80, growing down from +0x17FC. A script call pushes the return pc; `enter n` pushes the
 * frame pointer and reserves n bytes; `return` pops both and ends the run when the stack is empty again.
 * Native calls (call with a mode-6 operand) run D_80088A44[index](stack pointer); the pushed arguments are not
 * popped (as in the asm: the stack is reset by the next `return`).
 *
 * Abort: event_vm_abort (called only by the game-state handler event_action_game_state, as `event_vm_abort(); return 0;`) makes
 * the asm reload D_800D3858 into sp, clear it, and leave through the VM's epilogue. Here it is a flag: event_vm_abort
 * stores EV_ABORTED in D_800D3858 (nothing but event_vm_abort reads that word; the TU cannot have its own .bss in the
 * NM link), and the VM checks it right after every native call returns, clears it to 0 as the asm does, and leaves
 * before storing the result. A flag is enough because the only caller aborts in tail position (nothing it does after
 * the call is observable); setjmp/longjmp is not available in the N64 NM build. Divergence only where the N64 itself
 * breaks: an abort after a nested VM run has returned (D_800D3858 then points into the dead inner frame on N64).
 *
 * Quirks of the asm that are kept: operand 1 in mode 5 has no value load (it reads as 6, the shift count left in
 * t2); operand 3 in mode 2 has no offset load (it reads as 5, the shift count left in t4);
 * div / mod by zero give the VR4300 results; add / sub / neg wrap (the asm's `add` would trap on overflow).
 * Not reproduced (no valid script has them; the asm jumps into another operand's decoder or to address 0):
 * addressing mode 7, opcodes 0 and >= 0x1F, entry kinds > 4. The VM stops on them.
 */
f32 wrap_angle_rad(f32);
f32 sinf(f32);
s32 random_int(void);

typedef s32 (*EvNative)(s32 *args, s32 mode, s32 *operand);
typedef s32 (*EvHandlerA)(s32 id, s32 *args, s32 *operand);
typedef s32 (*EvHandlerB)(s32 id, s32 arg, s32 *args);

extern u8 D_800876F8[];         /* operand count + 1 per opcode */
extern EvNative D_80088A44[];   /* native functions */
extern EvHandlerA D_800887C0[];
extern EvHandlerA D_800887FC[];
extern EvHandlerB D_80088838[];
extern EvHandlerB D_80088874[];
extern s32 D_800D3C60;          /* argument count of the native call in progress */
extern s32 D_800D3C64;          /* arguments pushed since the last call */
extern s32 D_800D3C68;          /* result register */
extern s32 *D_800D3C6C;         /* -> D_800D3C68 once a result was used */
extern s32 D_800D3C80[];        /* operand stack */
extern u8 D_800BE9A0;           /* frames since the last update */

enum { EV_FRAME, EV_VAR, EV_DATA, EV_IMM, EV_LABEL, EV_RESULT, EV_NATIVE };

#define EV_ABORTED -1   /* D_800D3858 after event_vm_abort */

/* event_vm_run: run the event block `blk` from entry `entry` (0: +0x20, 1..4: header +0x0E..+0x14) until its outermost return.
 * The asm leaves v0 as it is (the last native result or return value, else the caller's v0); no caller reads it, so
 * this is void. One function (no decoding helper) so that the whole interpreter is one unit for difftest. */
/* was func_150ADFD0 */
void event_vm_run(struct249 *blk, s32 entry) {
    u16 *hdr = (u16 *) blk;
    u8 *base = (u8 *) blk;      /* code offsets are relative to the block */
    u8 *vars = base + hdr[5];
    u8 *data = base + hdr[4];
    s32 *top = (s32 *) ((u8 *) D_800D3C80 + 0x17FC);
    s32 *frame = top;
    s32 *sp = top;
    u16 *pc;
    s32 result;
    s32 *addr[3];               /* operand addresses */
    s32 val[3];                 /* operand values */
    s32 nops;
    s32 n;
    s32 mode;
    s32 wide;
    s16 off;
    u16 op;

    D_800D3858 = (s32) &frame;
    D_800D3C60 = 0;
    D_800D3C64 = 0;
    if (entry == 0) {
        pc = (u16 *) (base + 0x20);
    } else if (entry <= 4) {
        pc = (u16 *) (base + hdr[6 + entry]);
    } else {
        return;
    }

    for (;;) {
        op = *pc++;
        /* D_800876F8 holds operands + 1; the asm decodes three operands for any other count */
        nops = D_800876F8[op & 0x3F] - 1;
        if (nops < 0 || nops > 3) {
            nops = 3;
        }
        wide = (op >> 6) & 1;
        for (n = 0; n < nops; n++) {
            mode = (op >> (13 - 3 * n)) & 7;
            switch (mode) {
                case EV_IMM:
                case EV_LABEL:
                case EV_NATIVE:
                    addr[n] = (s32 *) pc;
                    if (wide) {
                        val[n] = ((u32) pc[0] << 16) | pc[1];
                        pc += 2;
                        wide = 0;
                    } else {
                        val[n] = (s16) pc[0];
                        pc++;
                    }
                    break;
                case EV_RESULT:
                    pc++;
                    D_800D3C6C = &D_800D3C68;
                    addr[n] = &D_800D3C68;
                    /* operand 1 has no load in the asm: the register still holds 6 (a shift count) */
                    val[n] = (n == 0) ? 6 : D_800D3C68;
                    break;
                case EV_FRAME:
                    off = pc[0];
                    pc++;
                    addr[n] = (s32 *) ((u8 *) frame + off);
                    val[n] = *addr[n];
                    break;
                case EV_VAR:
                    off = pc[0];
                    pc++;
                    addr[n] = (s32 *) (vars + off);
                    val[n] = *addr[n];
                    break;
                case EV_DATA:
                    if (n == 2) {
                        /* operand 3 has no offset load in the asm: it reads as 5 (the shift count left in t4) */
                        pc++;
                        addr[n] = (s32 *) (data + 5);
                        val[n] = 5;
                    } else {
                        off = pc[0];
                        pc++;
                        addr[n] = (s32 *) (data + off);
                        val[n] = off;
                    }
                    break;
                default:
                    return;
            }
        }

        switch (op & 0x3F) {
            case 0x01: *addr[0] = (u32) val[1] + (u32) val[2]; break;
            case 0x02: *addr[0] = (u32) val[1] - (u32) val[2]; break;
            case 0x03: *addr[0] = (u32) val[1] * (u32) val[2]; break;
            case 0x04: /* VR4300: x / 0 = (x < 0 ? 1 : -1), INT_MIN / -1 = INT_MIN */
                if (val[2] == 0) {
                    *addr[0] = (val[1] < 0) ? 1 : -1;
                } else if (val[2] == -1) {
                    *addr[0] = -(u32) val[1];
                } else {
                    *addr[0] = val[1] / val[2];
                }
                break;
            case 0x05: /* VR4300: x % 0 = x */
                if (val[2] == 0) {
                    *addr[0] = val[1];
                } else if (val[2] == -1) {
                    *addr[0] = 0;
                } else {
                    *addr[0] = val[1] % val[2];
                }
                break;
            case 0x06: *addr[0] = -(u32) val[1]; break;
            case 0x07: *addr[0] = (val[1] == 0); break;
            case 0x08: *addr[0] = ~val[1]; break;
            case 0x09: *addr[0] = val[1] & val[2]; break;
            case 0x0A: *addr[0] = val[1] | val[2]; break;
            case 0x0B: *addr[0] = val[1] ^ val[2]; break;
            case 0x0C: *addr[0] = (u32) val[1] << (val[2] & 31); break;
            case 0x0D: *addr[0] = val[1] >> (val[2] & 31); break;
            case 0x0E: *addr[0] = val[1]; break;
            case 0x0F: pc = (u16 *) (base + val[0]); break;
            case 0x10: if (val[0] == 0) { pc = (u16 *) (base + val[1]); } break;
            case 0x11: if (val[0] != 0) { pc = (u16 *) (base + val[1]); } break;
            case 0x12: *addr[0] = (val[1] < val[2]); break;
            case 0x13: *addr[0] = (val[2] < val[1]); break;
            case 0x14: *addr[0] = !(val[2] < val[1]); break;
            case 0x15: *addr[0] = !(val[1] < val[2]); break;
            case 0x16: *addr[0] = (val[1] == val[2]); break;
            case 0x17: *addr[0] = (val[1] != val[2]); break;
            case 0x18: /* push (a data operand pushes its address) */
                sp--;
                D_800D3C64++;
                *sp = ((op >> 13) == EV_DATA) ? (s32) addr[0] : val[0];
                break;
            case 0x19: /* call: native function or script subroutine */
                D_800D3C60 = D_800D3C64;
                if ((op >> 13) == EV_NATIVE) {
                    D_800D3C64 = 0;
                    result = D_80088A44[val[0]](sp, EV_NATIVE, addr[0]);
                    if (D_800D3858 == EV_ABORTED) {
                        D_800D3858 = 0;
                        return;
                    }
                    D_800D3C68 = result;
                    D_800D3C6C = &D_800D3C68;
                } else {
                    sp--;
                    *sp = (s32) pc;
                    D_800D3C64 = 0;
                    pc = (u16 *) (base + val[0]);
                }
                break;
            case 0x1B: /* enter: new frame with val[0] bytes of locals */
                sp--;
                *sp = (s32) frame;
                frame = sp;
                sp = (s32 *) ((u8 *) sp - val[0]);
                break;
            case 0x1A: /* return a value */
                D_800D3C68 = val[0];
                D_800D3C6C = &D_800D3C68;
                /* fallthrough */
            case 0x1C: /* return */
                sp = frame;
                frame = (s32 *) *sp++;
                pc = (u16 *) *sp++;
                D_800D3C60 = 0;
                D_800D3C64 = 0;
                if (sp >= top) {
                    return;
                }
                break;
            case 0x1D: *addr[0] = addr[1][val[2]]; break;
            case 0x1E: addr[1][val[2]] = val[0]; break;
            default:
                return;
        }
    }
}

/* Native functions 3..12 of D_80088A44 (code inside the asm VM; separate functions here). args = the VM stack
 * pointer: args[0] is the last value pushed. 3..6 call handler (args[0] >> 12 & 0xF) - 1 of their table with the
 * id word minus that nibble; the asm passes on the VM's a2 (the call operand's address) to the first two kinds. */
/* event_native_call_tab_7C0: handler of D_800887C0 by the id word's nibble */
/* was func_150AE5D8 */
s32 event_native_start_cmd(s32 *args, s32 mode, s32 *operand) {
    s32 id = args[0];
    s32 n = (id & 0xF000) >> 12;

    if (n == 0) {
        return 0;
    }
    return D_800887C0[n - 1](id & 0xFFFF0FFF, args, operand);
}

/* event_native_call_tab_7FC: handler of D_800887FC */
/* was func_150AE5E8 */
s32 event_native_stop_cmd(s32 *args, s32 mode, s32 *operand) {
    s32 id = args[0];
    s32 n = (id & 0xF000) >> 12;

    if (n == 0) {
        return 0;
    }
    return D_800887FC[n - 1](id & 0xFFFF0FFF, args, operand);
}

/* event_native_call_tab_838: handler of D_80088838 (id, args[1], args) */
/* was func_150AE5F8 */
s32 event_native_query(s32 *args) {
    s32 id = args[0];
    s32 n = (id & 0xF000) >> 12;

    if (n == 0) {
        return 0;
    }
    return D_80088838[n - 1](id & 0xFFFF0FFF, args[1], args);
}

/* event_native_game_state: handler of D_80088874 (game-state actions; id, args[1], args) */
/* was func_150AE60C */
s32 event_native_action(s32 *args) {
    s32 id = args[0];
    s32 n = (id & 0xF000) >> 12;

    if (n == 0) {
        return 0;
    }
    return D_80088874[n - 1](id & 0xFFFF0FFF, args[1], args);
}

/* event_native_random: random number below args[0] (unsigned; VR4300 x % 0 = x) */
/* was func_150AE674 */
s32 event_native_random(s32 *args) {
    u32 r = random_int();
    u32 n = args[0];

    return (n == 0) ? r : r % n;
}

/* event_native_frame_time: frames since the last update */
/* was func_150AE690 */
s32 event_native_frame_time(s32 *args) {
    return D_800BE9A0;
}

/* event_native_fixed_mul: 16.16 fixed-point product (64-bit intermediate) */
/* was func_150AE6A0 */
s32 event_native_fixed_mul(s32 *args) {
    return (s32) ((u64) ((s64) args[0] * args[1]) >> 16);
}

/* event_native_fixed_div: 16.16 fixed-point quotient (64-bit intermediate) */
/* was func_150AE6BC */
s32 event_native_fixed_div(s32 *args) {
    s64 n = (s64) args[0] << 16;

    if (args[1] == 0) { /* VR4300 ddiv by 0 */
        return (n < 0) ? 1 : -1;
    }
    return (s32) (n / args[1]);
}

/* event_native_timer_up: timer counting up by the frame time: negative timers stop at 0 when they cross it, 0 becomes 1 */
/* was func_150AE6D4 */
s32 event_native_timer_up(s32 *args) {
    s32 t = args[0];
    s32 next = (u32) t + D_800BE9A0;

    if (t < 0 && next >= 0) {
        return 0;
    }
    if (t == 0) {
        return 1;
    }
    return next;
}

/* event_native_timer_down: timer counting down by the frame time: stops at 1 when it crosses below 2, 1 becomes 0 */
/* was func_150AE714 */
s32 event_native_timer_down(s32 *args) {
    s32 t = args[0];
    s32 next = (u32) t - D_800BE9A0;

    if (t >= 2 && next < 2) {
        return 1;
    }
    if (t == 1) {
        return 0;
    }
    return next;
}

/* event_vm_abort: abort the running event script (see the VM comment). */
/* was func_150AE760 */
void event_vm_abort(void) {
    D_800D3858 = EV_ABORTED;
}

/* object_sway_update: the rest of event_vm_abort's asm (from 0x150AE780) is an ordinary function, an entry of the table at 0x80089C70:
 * two phases advance with the frame time, are wrapped by wrap_angle_rad, and drive a sine sway (+0x20 / +0x28). */
/* was func_150AE780 */
s32 object_sway_update(u8 *obj) {
    f32 *phase = (f32 *) (obj + 0x178);

    phase[0] += 0.065f * D_800BE9A4;
    phase[1] += 0.0484f * D_800BE9A4;
    phase[0] = wrap_angle_rad(phase[0]);
    phase[1] = wrap_angle_rad(phase[1]);
    *(f32 *) (obj + 0x20) = sinf(phase[0]) * 3.0860002f;
    *(f32 *) (obj + 0x28) = sinf(phase[1]) * 5.9140005f;
    return 1;
}

/* was func_150AE83C */
s32 object_handler_true(s32 arg0) {
    return 1;
}

void mtxf_rot_scale2_trans(s32, f32, f32, f32, f32, f32, f32, f32, f32);
void vtx_slot_buffer_get(s32 *, s16, s32, s32 *, u8 *);
s32 memcpy(s32, s32, s32);
extern s32 D_800DD608;
extern s32 D_800DD618;

/* was func_150AE84C */
u8 *object_quad_vtx_build(u8 *arg0, s16 arg1) {
    struct {
        u8 u43;
        u8 * u44;
        u8 pad48[0x44];
        f32 u8C;
        f32 u90;
        f32 u94;
        u8 pad98[0x8];
        u8 * uA0;
        u8 * uA4;
    } sp;
    u8 *sp3C;                                     /* compiler-managed */
    s32 sp38;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;
    s32 temp_a1;
    s32 temp_f10;
    s32 temp_f10_2;
    s32 temp_f18;
    s32 temp_f18_2;
    s32 temp_f4;
    s32 temp_f8;
    u8 *temp_v0;
    u8 *temp_v0_2;

    vtx_slot_buffer_get(arg0 + 0x100, arg1, 0x40, &sp.uA4, &sp.u43);
    sp.uA0 = sp.uA4;
    if (sp.uA4 != NULL) {
        if (sp.u43 != 0) {
            temp_v0 = arg0 + (arg1 * 4);
            temp_a1 = arg0 + 0xC0;
            sp38 = temp_a1;
            sp3C = temp_v0;
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)), temp_a1, 0x40);
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)) + 0x40, temp_a1, 0x40);
        }
        temp_v0_2 = (*(u8 **)((u8 *)arg0 + 0x160));
        sp3C = arg1 * 4;
        mtxf_rot_scale2_trans((f32 (*)[4]) &sp.u44[0], (*(s32 *)((u8 *)temp_v0_2 + 0x18)), (*(s32 *)((u8 *)temp_v0_2 + 0x1C)), (*(s32 *)((u8 *)temp_v0_2 + 0x20)), (*(f32 *)((u8 *)temp_v0_2 + 0x24)), (*(f32 *)((u8 *)temp_v0_2 + 0x28)), (*(f32 *)((u8 *)temp_v0_2 + 0x38)), (*(f32 *)((u8 *)temp_v0_2 + 0x3C)), (*(f32 *)((u8 *)temp_v0_2 + 0x40)));
        mtxf_transform_point((f32 (*)[4]) &sp.u44[0], (*(f32 *)((u8 *)arg0 + 0x34)), (*(f32 *)((u8 *)arg0 + 0x38)), (*(f32 *)((u8 *)arg0 + 0x3C)), &sp.u8C, &sp.u90, &sp.u94);
        temp_f0 = (*(f32 *)((u8 *)arg0 + 0x2C));
        (*(s16 *)((u8 *)sp.uA4 + 6)) = 0;
        temp_f2 = *(s32 *)((s32)&D_800DD618 + (s32)sp3C) * (s32)temp_f0;
        (*(s16 *)((u8 *)sp.uA4 + 0x16)) = 0;
        temp_f12 = *(s32 *)((s32)&D_800DD608 + (s32)sp3C) * (s32)temp_f0;
        (*(s16 *)((u8 *)sp.uA4 + 0x26)) = 0;
        (*(s16 *)((u8 *)sp.uA4 + 0x36)) = 0;
        temp_f10 = (s32) (sp.u8C + temp_f2);
        (*(s16 *)((u8 *)sp.uA4 + 0x30)) = (s16) temp_f10;
        (*(s16 *)((u8 *)sp.uA4 + 0)) = (s16) temp_f10;
        temp_f18 = (s32) sp.u90;
        (*(s16 *)((u8 *)sp.uA4 + 0x12)) = (s16) temp_f18;
        (*(s16 *)((u8 *)sp.uA4 + 2)) = (s16) temp_f18;
        temp_f8 = (s32) (sp.u94 - temp_f12);
        (*(s16 *)((u8 *)sp.uA4 + 0x34)) = (s16) temp_f8;
        (*(s16 *)((u8 *)sp.uA4 + 4)) = (s16) temp_f8;
        temp_f18_2 = (s32) (sp.u8C - temp_f2);
        (*(s16 *)((u8 *)sp.uA4 + 0x20)) = (s16) temp_f18_2;
        (*(s16 *)((u8 *)sp.uA4 + 0x10)) = (s16) temp_f18_2;
        temp_f10_2 = (s32) ((*(f32 *)((u8 *)arg0 + 0x30)) + sp.u90);
        (*(s16 *)((u8 *)sp.uA4 + 0x32)) = (s16) temp_f10_2;
        (*(s16 *)((u8 *)sp.uA4 + 0x22)) = (s16) temp_f10_2;
        temp_f4 = (s32) (sp.u94 + temp_f12);
        (*(s16 *)((u8 *)sp.uA4 + 0x24)) = (s16) temp_f4;
        (*(s16 *)((u8 *)sp.uA4 + 0x14)) = (s16) temp_f4;
        return sp.uA0;
    }
    return NULL;
}