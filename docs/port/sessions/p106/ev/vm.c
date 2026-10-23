f32 func_15144B68(f32);
f32 sinf(f32);
s32 func_150ADA20(void);

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

#define EV_ABORTED -1   /* D_800D3858 after func_150AE760 */

/* Run the event block `blk` from entry `entry` (0: +0x20, 1..4: header +0x0E..+0x14) until its outermost return.
 * The asm leaves v0 as it is (the last native result or return value, else the caller's v0); no caller reads it, so
 * this is void. One function (no decoding helper) so that the whole interpreter is one unit for difftest. */
void func_150ADFD0(struct249 *blk, s32 entry) {
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
s32 func_150AE5D8(s32 *args, s32 mode, s32 *operand) {
    s32 id = args[0];
    s32 n = (id & 0xF000) >> 12;

    if (n == 0) {
        return 0;
    }
    return D_800887C0[n - 1](id & 0xFFFF0FFF, args, operand);
}

s32 func_150AE5E8(s32 *args, s32 mode, s32 *operand) {
    s32 id = args[0];
    s32 n = (id & 0xF000) >> 12;

    if (n == 0) {
        return 0;
    }
    return D_800887FC[n - 1](id & 0xFFFF0FFF, args, operand);
}

s32 func_150AE5F8(s32 *args) {
    s32 id = args[0];
    s32 n = (id & 0xF000) >> 12;

    if (n == 0) {
        return 0;
    }
    return D_80088838[n - 1](id & 0xFFFF0FFF, args[1], args);
}

s32 func_150AE60C(s32 *args) {
    s32 id = args[0];
    s32 n = (id & 0xF000) >> 12;

    if (n == 0) {
        return 0;
    }
    return D_80088874[n - 1](id & 0xFFFF0FFF, args[1], args);
}

/* random number below args[0] (unsigned; VR4300 x % 0 = x) */
s32 func_150AE674(s32 *args) {
    u32 r = func_150ADA20();
    u32 n = args[0];

    return (n == 0) ? r : r % n;
}

s32 func_150AE690(s32 *args) {
    return D_800BE9A0;
}

/* 16.16 fixed-point product and quotient (64-bit intermediate) */
s32 func_150AE6A0(s32 *args) {
    return (s32) ((u64) ((s64) args[0] * args[1]) >> 16);
}

s32 func_150AE6BC(s32 *args) {
    s64 n = (s64) args[0] << 16;

    if (args[1] == 0) { /* VR4300 ddiv by 0 */
        return (n < 0) ? 1 : -1;
    }
    return (s32) (n / args[1]);
}

/* timer counting up by the frame time: negative timers stop at 0 when they cross it, 0 becomes 1 */
s32 func_150AE6D4(s32 *args) {
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

/* timer counting down by the frame time: stops at 1 when it crosses below 2, 1 becomes 0 */
s32 func_150AE714(s32 *args) {
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
