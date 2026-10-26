#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15040350 */
void dl_validate(void *arg0, u32 arg1) {
    s32 i;

    D_800C68A0 = D_800848B0 = 0;
    D_800C68A1 = 0;

    for (i = 0; i < 16; i++) {
        D_800C6860[i] = -1;
    }
    D_800C6860[0] = 0;
    dl_validate_list(arg0, arg1, 0);
}

// contains jump relative
#ifdef NON_MATCHING
void func_150ADC50(void);
void debug_syscall_trap(void);
void dl_dump_around(u8 *arg0);
s32 dlcheck_vtx_invalid(struct148 *arg0);

/* debug trap: error code 0x0C00005B in D_8003C8E0, then the break handler */
#define DL_TRAP() (D_8003C8E0 = 0x0C00005B, func_150ADC50())
/* trap, dump the command (dl_dump_around) and stop in debug_syscall_trap with the frame index D_800BE9C0 flipped */
#define DL_STOP(c) (dl_dump_around((u8 *) (c)), DL_TRAP(), D_800BE9C0 = 1 - D_800BE9C0, debug_syscall_trap(), \
                    D_800BE9C0 = 1 - D_800BE9C0)

// dl_validate: debug walk over a display list of 8-byte commands until `end` (or, with end 0, until G_ENDDL 0xDF),
// following G_DL (0xDE) branches through the segment table D_800C6860 (at most 20 deep, target must be a cached
// 8-aligned KSEG0 address) and tracking G_MOVEWORD segment writes (index 6) and G_SETTIMG (D_800848B0). Primitives
// (0xE4 / 0xE5 / 0xF6, 1, 5, 6, 7, 0x10-0x1F) mark D_800C68A0 "drawn since pipe sync", G_RDPPIPESYNC clears it; an
// RDP state command (0xE2 / 0xE3 / 0xEA-0xEE / 0xF7-0xF9 / 0xFB-0xFF) while it is set, a failed command check
// (dlcheck_dl_invalid / dlcheck_tri_invalid / dlcheck_vtx_invalid) or a bad branch stops in the debugger; unknown opcodes trap.
/* was func_150403C8 */
void dl_validate_list(void *list, u32 end, s32 parent) {
    u32 *dl = list;
    s32 bad = 0;
    s32 needSync;
    u32 w1;
    u32 addr;

    while (end == 0 ? *(s8 *) dl != (s8) 0xDF : (u32) dl < end) {
        needSync = 0;
        switch (*(u8 *) dl) {
            case 0xDE:
                w1 = dl[1];
                bad = dlcheck_dl_invalid((struct148 *) dl);
                addr = ((w1 & 0xFFFFFF) + D_800C6860[(w1 >> 24) & 0xF]) | 0x80000000;
                if (++D_800C68A1 == 20) {
                    dl_dump_around((u8 *) dl);
                    DL_TRAP();
                }
                if (addr >= 0x80000001 && addr < 0xA0000000 && !(addr & 7)) {
                    dl_validate_list((void *) addr, 0, (s32) dl);
                } else {
                    DL_STOP(dl);
                }
                if (D_800C68A1 != 0) {
                    D_800C68A1--;
                } else {
                    DL_TRAP();
                    D_800BE9C0 = 1 - D_800BE9C0;
                    debug_syscall_trap();
                    D_800BE9C0 = 1 - D_800BE9C0;
                }
                break;
            case 0xE7:
                D_800C68A0 = 0;
                break;
            case 0xE4:
            case 0xE5:
            case 0xF6:
            case 6:
            case 7:
            case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
            case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31:
                D_800C68A0 = 1;
                break;
            case 5:
                bad = dlcheck_tri_invalid(dl);
                D_800C68A0 = 1;
                break;
            case 1:
                bad = dlcheck_vtx_invalid((struct148 *) dl);
                break;
            case 0xFD:
                D_800848B0 = dl[1];
                break;
            case 0xFF:
            case 0xE2:
            case 0xE3:
            case 0xEC:
            case 0xED:
            case 0xEE:
            case 0xF7:
            case 0xF8:
            case 0xF9:
            case 0xFB:
            case 0xFC:
            case 0xFE:
            case 0xEA:
            case 0xEB:
                needSync = 1;
                break;
            case 0xDB:
                if (((dl[0] >> 16) & 0xFF) == 6) {
                    D_800C6860[(s32) (dl[0] & 0xFFFF) / 4] = dl[1];
                }
                break;
            case 0xD3: case 0xD4: case 0xD5: case 0xD6:
            case 0xD7: case 0xD8: case 0xD9: case 0xDA:
            case 0xDC: case 0xDD: case 0xDF: case 0xE0: case 0xE1:
            case 0xE6: case 0xE8: case 0xE9:
            case 0xEF: case 0xF0: case 0xF1: case 0xF2: case 0xF3:
            case 0xF4: case 0xF5: case 0xFA:
            case 0: case 2: case 3: case 4: case 8:
                break;
            default:
                DL_TRAP();
                break;
        }
        if (needSync && D_800C68A0) {
            dl_dump_around((u8 *) dl);
            D_800C68A0 = 0;
            DL_TRAP();
            D_800BE9C0 = 1 - D_800BE9C0;
            debug_syscall_trap();
            D_800BE9C0 = 1 - D_800BE9C0;
        }
        if (bad) {
            bad = 0;
            DL_STOP(dl);
        }
        dl += 2;
    }
}
#undef DL_STOP
#undef DL_TRAP
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_6D800/dl_validate_list.s")
#endif

/* was func_1504072C */
s32 dlcheck_addr_misaligned(s32 arg0) {
    if ((arg0 & 7) != 0) {
        return 1;
    }
    return 0;
}

/* was func_15040748 */
void dldump_unknown(s32 arg0) {
}

/* was func_15040754 */
s32 dlcheck_vtx_invalid(struct148 *arg0) { // overly simple
    s32 temp_a2;
    s32 temp_a1;

    temp_a1 = (arg0->unk0 >> 1) & 0x7F;
    temp_a2 = (arg0->unk0 >> 12) & 0xFF;
    temp_a1 = temp_a1 - temp_a2;

    if (temp_a1 < 0) {
        return 1;
    }
    return dlcheck_addr_misaligned(arg0->unk4);
}

/* was func_150407A0 */
void dldump_vtx(void) {
}

/* was func_150407A8 */
void dldump_modifyvtx(s32 arg0) {
}

/* was func_150407B4 */
void dldump_culldl(s32 arg0) {
}

/* was func_150407C0 */
void dldump_branch_z(s32 arg0) {
}

/* was func_150407CC */
void dldump_line3d(s32 arg0) {
}

/* was func_150407D8 */
void dldump_rdphalf_1(s32 arg0) {
}

/* was func_150407E4 */
void dldump_rdphalf_2(s32 arg0) {
}

/* was func_150407F0 */
void dldump_setkeygb(s32 arg0) {
}

/* was func_150407FC */
void dldump_setkeyr(s32 arg0) {
}

/* was func_15040808 */
void dldump_quad(s32 arg0) {
}

/* was func_15040814 */
void dldump_tri2(s32 arg0) {
}

/* was func_15040820 */
void dldump_tri_ext(s32 arg0) {
}

/* was func_1504082C */
s32 dlcheck_tri_invalid(u32 *arg0) {
    s32 tmp0 = (*arg0 >> 16) & 0xff;
    s32 tmp1 = (*arg0 >> 8) & 0xff;
    s32 tmp2 = (*arg0 >> 0) & 0xff;

    if ((tmp0 & 1) || (tmp1 & 1) || (tmp2 & 1)) {
        return 1;
    } else {
        return 0;
    }
}

/* was func_1504086C */
void dldump_tri1(s32 arg0) {
}

/* was func_15040878 */
void dldump_loadtlut(s32 arg0) {
}

/* was func_15040884 */
void dldump_loadtile(s32 arg0) {
}

/* was func_15040890 */
void dldump_rdptilesync(s32 arg0) {
}

/* was func_1504089C */
void dldump_rdpfullsync(s32 arg0) {
}

/* was func_150408A8 */
void dldump_rdppipesync(s32 arg0) {
}

/* was func_150408B4 */
void dldump_rdploadsync(s32 arg0) {
}

/* was func_150408C0 */
void dldump_setcombine(s32 arg0) {
}

/* was func_150408CC */
s32 dlcheck_dl_invalid(struct148 *arg0) {
    return dlcheck_addr_misaligned(arg0->unk4);
}

/* was func_150408F0 */
void dldump_dl(s32 arg0) {
}

/* was func_150408FC */
void dldump_setothermode_h(s32 arg0) {
}

/* was func_15040908 */
void dldump_setothermode_l(s32 arg0) {
}

/* was func_15040914 */
void dldump_setconvert(s32 arg0) {
}

/* was func_15040920 */
void dldump_setscissor(s32 arg0) {
}

/* was func_1504092C */
void dldump_spnoop(s32 arg0) {
}

/* was func_15040938 */
void dldump_noop(s32 arg0) {
}

/* was func_15040944 */
void dldump_setcimg(s32 arg0) {
}

/* was func_15040950 */
void dldump_setzimg(s32 arg0) {
}

/* was func_1504095C */
void dldump_settimg(s32 arg0) {
}

/* was func_15040968 */
void dldump_setenvcolor(s32 arg0) {
}

/* was func_15040974 */
void dldump_setprimcolor(s32 arg0) {
}

/* was func_15040980 */
void dldump_setblendcolor(s32 arg0) {
}

/* was func_1504098C */
void dldump_setfogcolor(s32 arg0) {
}

/* was func_15040998 */
void dldump_special_3(s32 arg0) {
}

/* was func_150409A4 */
void dldump_special_2(s32 arg0) {
}

/* was func_150409B0 */
void dldump_special_1(s32 arg0) {
}

/* was func_150409BC */
void dldump_dma_io(s32 arg0) {
}

/* was func_150409C8 */
void dldump_setfillcolor(s32 arg0) {
}

/* was func_150409D4 */
void dldump_fillrect(s32 arg0) {
}

/* was func_150409E0 */
void dldump_texrect(s32 arg0) {
}

/* was func_150409EC */
void dldump_texrectflip(s32 arg0) {
}

/* was func_150409F8 */
void dldump_loadblock(s32 arg0) {
}

/* was func_15040A04 */
void dldump_settile(s32 arg0) {
}

/* was func_15040A10 */
void dldump_settilesize(s32 arg0) {
}

/* was func_15040A1C */
void dldump_enddl(s32 arg0) {
}

/* was func_15040A28 */
void dldump_popmtx(s32 arg0) {
}

/* was func_15040A34 */
void dldump_mtx(s32 arg0) {
}

/* was func_15040A40 */
void dldump_geometrymode(s32 arg0) {
}

/* was func_15040A4C */
void dlcheck_stub(void) {
}

/* was func_15040A54 */
void dldump_load_ucode(s32 arg0) {
}

/* was func_15040A60 */
void dldump_movemem(s32 arg0) {
}

/* was func_15040A6C */
void dldump_moveword(s32 arg0) {
}

#ifdef NON_MATCHING
extern void (*D_80084840[])(u8 *);
// dl_walk_call_handlers: P259: walks the display list from `dl` (8-byte F3DEX2 commands) while the command pointer
// is <= `end` or a G_DL call is open, and passes every command from `from` up to `end` to its opcode handler
// D_80084840[op]. It resets the segment table D_800C6860 (all -1, segment 0 = 0), records G_MOVEWORD segment
// writes (G_MW_SEGMENT), follows G_DL (0xDE) calls into known segments (unknown segment: skipped) and returns on
// G_ENDDL (0xDF) to the saved command; G_VTX (1) only steps (the asm counts its vertices in an empty loop).
// No callers in the ROM (only the symbol table names it).
/* was func_15040A78 */
void dl_trace_segments(u8 *dl, u8 *from, u8 *end) {
    u8 *stack[21];
    u8 *cmd;
    u32 w0;
    u32 w1;
    s32 seg;
    s32 depth;
    s32 active;
    s32 i;
    u8 op;

    for (i = 0; i < 16; i++) {
        D_800C6860[i] = -1;
    }
    D_800C6860[0] = 0;
    depth = 0;
    active = FALSE;
    cmd = dl;
    if (end < cmd) {
        return;
    }
    do {
        if (cmd == from) {
            active = TRUE;
        }
        op = cmd[0];
        if (active) {
            D_80084840[op](cmd);
        }
        if (cmd == end) {
            active = FALSE;
        }
        switch (op) {
        case 0xDE: // G_DL
            stack[depth++] = cmd + 8;
            w1 = ((u32 *) cmd)[1];
            seg = (w1 >> 24) & 0xF;
            cmd += 8;
            if (D_800C6860[seg] == -1) {
                depth--;
            } else {
                cmd = (u8 *) (((w1 & 0xFFFFFF) + D_800C6860[seg]) | 0x80000000);
            }
            break;
        case 0xDF: // G_ENDDL
            cmd = stack[--depth];
            break;
        case 0xDB: // G_MOVEWORD
            w0 = ((u32 *) cmd)[0];
            w1 = ((u32 *) cmd)[1];
            if (((w0 >> 16) & 0xFF) == 6) { // G_MW_SEGMENT
                D_800C6860[(s32) (w0 & 0xFFFF) >> 2] = w1;
            }
            cmd += 8;
            break;
        default:
            cmd += 8;
            break;
        }
    } while (cmd <= end || depth > 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_6D800/dl_trace_segments.s")
#endif

extern void (*D_80084840[])(u8 *);

/* was func_15040CC8 */
void dl_dump_around(u8 *arg0)
{
  u8 *new_var2;
  s32 i;
  short new_var3;
  u8 *p;
  u8 *new_var;
  i = 0;
  do
  {
    do
    {
      i += 1;
    }
    while (0);
 } while (i < 0x10); i = -0x14; do { new_var2 = (new_var = arg0 + (i * 8)); p = new_var2; D_80084840[*p](p); new_var3 = 1; i += new_var3;
  }
  while (i < 0xA);
  if (D_800848B0 != 0)
  {
    texture_table_find(D_800848B0);
  }
}
// NON-MATCHING: todo
// void dl_dump_around(s32 *arg0) {
//     s32 temp_a0_2;
//     s32 temp_s0;
//     s32 temp_s0_2;
//     s32 *temp_a0;
//     s32 phi_s0;
//     s32 phi_s0_2;
//
//     for (phi_s0 = 0; phi_s0 < 16; phi_s0++)
//     {
//         // just waste time?
//     }
//
//     phi_s0_2 = -0x14;
// loop_3:
//     temp_a0 = arg0[phi_s0_2]; // * 8) + arg0;
//     D_800844B0[*temp_a0](temp_a0);
//     temp_s0_2 = phi_s0_2 + 1;
//     phi_s0_2 = temp_s0_2;
//     if (temp_s0_2 < 0xA) {
//         goto loop_3;
//     }
//     temp_a0_2 = D_800848B0;
//     if (temp_a0_2 != 0) {
//         texture_table_find(temp_a0_2);
//     }
// }

/* was func_15040D60 */
void dldump_setprimdepth(s32 arg0) {
}

/* was func_15040D6C */
void dldump_texture(s32 arg0) {
}

/* was func_15040D78 */
void dldump_rdpsetothermode(s32 arg0) {
}
