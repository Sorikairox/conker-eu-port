#include <ultra64.h>

#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
u8 *debugger_draw_char(s16 *arg0, s32 arg1);
void debugger_clear_screen(void);

s32 debugger_cell_to_fb(s32);
void debugger_print_number(s32 arg0, s32 arg1, s32 arg2);


/* was func_16000000 */
void debugger_page_title_draw(void) {
    debugger_print_string(278, &g_dbg_str_title);
}

/* was func_16000028 */
s32 debugger_page_title_input(void) {
    if (g_dbg_buttons_pressed & 0xC000) {
        g_dbg_page = 1;
        return 3;
    }
    return 0;
}

/* was func_16000058 */
void debugger_main_menu_draw(void) {
    s32 i;
    s32 phi_s2;

    debugger_set_color(255, 255, 255);
    debugger_print_string(44, &g_dbg_str_main_menu); // "MAIN MENU"
    phi_s2 = 108;
    for(i = 0; i < 2; i++) {
        if (g_dbg_menu_cursor == i) {
            debugger_set_color(255, 0, 0);     // red
        } else {
            debugger_set_color(255, 255, 255); // white
        }
        debugger_print_string(phi_s2, g_dbg_menu_item_strs[i]);
        phi_s2 += 32;
    }
    if (g_dbg_menu_cursor == 2) {
        debugger_set_color(255, 0, 0);     // red
    } else {
        debugger_set_color(255, 255, 255); // white
    }
    if (g_dbg_fault_not_retryable != 0) {
        if ((g_dbg_fault_thread->unk120 == 32) && (g_dbg_is_lockup == 0)) {
            debugger_print_string(phi_s2, &g_dbg_str_menu_continue);
        } else if (g_dbg_fault_not_retryable != 0) {
            debugger_print_string(phi_s2, &g_dbg_str_menu_no_retry);
        }
    } else {
        debugger_print_string(phi_s2, &g_dbg_str_retry_code); // "RETRY CODE"
    }
    debugger_set_color(255, 255, 255);
    debugger_print_string(611, &g_dbg_str_version); // "Version"
    debugger_print_number(619, 1, 19);
    debugger_print_string(643, &g_dbg_str_built); // "Built"
    debugger_print_string(651, &g_dbg_str_build_date); // "Dec 19 2000"
    debugger_print_string(663, &g_dbg_str_build_time); // "09:57:42"
}

/* was func_16000224 */
s32 debugger_main_menu_input(void) {
    s32 res = 0;

    if (g_dbg_buttons_pressed & 0x40000) { // D_JPAD is 0x0400
        g_dbg_menu_cursor -= 1;
        res = 1;
    }
    if (g_dbg_buttons_pressed & 0x80000) { // U_JPAD is 0x0800
        g_dbg_menu_cursor += 1;
        res = 1;
    }
    if (g_dbg_menu_cursor >= 3) {
        g_dbg_menu_cursor = 0;
    }
    if (g_dbg_menu_cursor < 0) {
        g_dbg_menu_cursor = 2;
    }
    if (g_dbg_buttons_pressed & A_BUTTON) {
        switch(g_dbg_menu_cursor) {
            case 0:
                res = 3;
                g_dbg_page = 2;
                break;
            case 1:
                res = 3;
                g_dbg_page = 3;
                break;
            case 2:
                res = 4;
                break;
        }
    }
    return res;
}

/* was func_16000304 */
void debugger_page_nop_draw(void) {
}

/* was func_1600030C */
void debugger_page_nop_input(void) {
}

/* was func_16000314 */
void debugger_regs_page_draw(void) {
    switch(g_dbg_regs_subpage) {
        case 0:
            debugger_draw_exception(g_dbg_fault_thread);
            debugger_draw_gprs(g_dbg_fault_thread);
            break;
        case 1:
        case 2:
            debugger_draw_fpu_regs(g_dbg_fault_thread);
            break;
    }
}

/* was func_16000384 */
s32 debugger_regs_page_input(void) {
    s32 res = 0;

    if (g_dbg_buttons_pressed & (R_CBUTTONS | D_CBUTTONS)) {
        g_dbg_regs_subpage += 1;
        if (g_dbg_regs_subpage >= 3) {
            g_dbg_regs_subpage = 0;
        }
        return 3;
    }
    if (g_dbg_buttons_pressed & (L_CBUTTONS | U_CBUTTONS)) {
        g_dbg_regs_subpage -= 1;
        if (g_dbg_regs_subpage < 0) {
            g_dbg_regs_subpage = 2;
        }
        return 3;
    }
    if (g_dbg_buttons_pressed & B_BUTTON) {
        g_dbg_page = 1;
        res = 3;
    }
    return res;
}

/* was func_16000424 */
void debugger_draw_exception(struct118 *arg0) {
    // TODO is this a RGB struct?
    u32 tmp0;
    u32 tmp1;
    s32 pad;

    debugger_set_color(255, 255, 255);
    debugger_print_string(35, &g_dbg_str_pc);     // "Pc"
    debugger_print_number(43, 0, arg0->unk11C);
    debugger_print_string(67, &g_dbg_str_cause);     // "Cause"
    debugger_print_number(75, 0, arg0->unk120);
    debugger_set_color(128, 128, 255);
    tmp0 = arg0->unk120;
    tmp1 = (tmp0 >> 2) & 0xF;

    debugger_print_string(107, g_dbg_exc_cause_names[tmp1]);
    if (tmp1 == 11) {
        debugger_print_number(111, 1, (tmp0 >> 28) & 3);
    }
    debugger_set_color(255, 255, 255);
    debugger_print_string(131, &g_dbg_str_sr);      // "Sr"
    debugger_print_number(139, 0, arg0->unk118);
    debugger_print_string(163, &g_dbg_str_badvaddr);      // "Badvadr"
    debugger_print_number(171, 0, arg0->unk124);
    debugger_print_string(195, &g_dbg_str_thread);      // "Thread"
    debugger_print_number(203, 1, arg0->unk14);
    if (g_dbg_is_lockup != 0) {
        debugger_print_string(52, &g_dbg_str_lockup_now);   // "Lockup_Now"
    }
}

/* was func_16000590 */
void debugger_draw_fpu_regs(struct118 *arg0) {
    s32 temp_s2;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s2_2;
    s32 var_s4;
    s32 var_v0;
    u32 var_s2;
    u8 *var_s3;

    var_s4 = 0;
    temp_s2 = (*(s32 *)((u8 *)arg0 + 0x12C));
    debugger_print_string(3, g_dbg_str_fpcsr);
    debugger_print_number(0xA, 0, temp_s2);
    var_s2 = (u32) temp_s2 >> 0xC;
    var_s0 = 0x2C;
    var_s1 = 0;
    do {
        if (var_s2 & 1) {
            debugger_print_string(var_s0, (u8 *) g_dbg_fpcsr_flag_names[var_s1]);
            var_s0 += 0x20;
        }
        var_s1 += 1;
        var_s2 = var_s2 >> 1;
    } while (var_s1 < 6);
    var_s1_2 = 0;
    var_s0_2 = 0xC3;
    if (g_dbg_regs_subpage == 1) {
        var_v0 = 0x4C;
    } else {
        var_v0 = 0x6C;
        var_s4 = 0x10;
    }
    var_s2_2 = var_s4;
    var_s3 = ((struct118 *)((u8 *)arg0 + (var_v0 * 4)));
    do {
        debugger_print_string(var_s0_2, g_dbg_str_fpr_prefix);
        debugger_print_number(var_s0_2 + 2, 1, var_s2_2);
        debugger_print_number(var_s0_2 + 5, 2, (*(s32 *)((u8 *)var_s3 + 4)));
        var_s1_2 += 1;
        var_s3 += 8;
        var_s0_2 += 0x20;
        var_s2_2 += 1;
    } while (var_s1_2 < 0x10);
}
typedef struct {
    u8 c[4];
} struct_16003B48;
extern struct_16003B48 g_dbg_gpr_name_template; /* was D_16003B48 */
extern u8 g_dbg_gpr_name_table[]; /* was D_160037F0 */

/* was func_160006CC */
void debugger_draw_gprs(struct118 *arg0) {
    struct_16003B48 name;
    s32 pad;
    s32 pos = 0x123;
    u8 *p = g_dbg_gpr_name_table;
    s32 idx;

    name = g_dbg_gpr_name_template;
    debugger_set_color(0xC0, 0xC0, 0xFF);
    do {
        name.c[0] = p[0];
        name.c[1] = p[1];
        debugger_print_string(pos, name.c);
        pos += 3;
        idx = p[2];
        debugger_print_number(pos, 0, ((s32 *)arg0)[idx + 1]);
        pos += 0xD;
        p += 3;
    } while (p[0] != 0);
}
extern u8 g_boot_idle_stack[]; /* was D_8002D810 */
extern u8 g_boot_thread_stack_4000[]; /* was D_8002DC10 */

/* was func_1600078C */
void debugger_draw_stack(void)
{
    u32 mask;
  s32 base;
  u32 addr;
  u32 lo;
  s32 x;
  u32 i;
  u32 val;
  u8 prefix;
  base = *((s32 *) (((u8 *) g_dbg_fault_thread) + 0xF4));
  debugger_set_color(0, 255, 0);
  debugger_print_string(11, g_dbg_str_stack_title);
  addr = 4;
  addr = (g_dbg_stack_scroll * addr) + base;
  i = 3;
  if ((((((char) addr) & i) == 0) && (addr >= 0x80000000U)) && (addr < 0x80800001U))
  {
    if (g_dbg_stack_scroll == 0)
    {
      debugger_set_color(255, 0, 0);
      lo = (u32) g_boot_idle_stack;
    }
    else
    {
      lo = (u32) g_boot_idle_stack;
      if ((addr >= lo) && (addr < (lo + 0x400)))
      {
        debugger_set_color(128, 128, 255);
      }
      else
        if ((addr >= ((u32) g_boot_thread_stack_4000)) && (addr < (((u32) g_boot_thread_stack_4000) + 0x4000)))
      {
        debugger_set_color(255, 128, 128);
      }
      else
      {
        debugger_set_color(255, 255, 255);
      }
    }
    x = 0x61;
    for (i = 0; i < 22; i++)
    {
      debugger_print_number(x, 0, addr);
      debugger_print_string(x + 8, g_dbg_str_stack_addr_sep);
      val = *((u32 *) addr);
      prefix = val >> 24;
      if (prefix == 0x80)
      {
        debugger_set_color(128, 128, 255);
      }
      else
        if (prefix == 0x15)
      {
        debugger_set_color(255, 0, 0);
      }
      else
        if (prefix == 0x16)
      {
        debugger_set_color(128, 255, 128);
      }
      else
        if (prefix == 0x10)
      {
        debugger_set_color(255, 0, 0);
      }
      else
      {
        debugger_set_color(255, 255, 255);
      }
      mask = 0xFFFFFFFFu; // fakematch: an all-ones mask in a register (permuter)
      debugger_print_number(x + 0xC, 0, val);
      debugger_print_string((x + 0x16) & mask, g_dbg_str_stack_val_sep);
      debugger_set_color(255, 255, 255);
      debugger_print_number(x + 0x16, 1, val);
      if ((addr >= lo) && (addr < (lo + 0x400)))
      {
        debugger_set_color(128, 128, 255);
      }
      else
        if ((addr >= ((u32) g_boot_thread_stack_4000)) && (addr < (((u32) g_boot_thread_stack_4000) + 0x4000)))
      {
        debugger_set_color(255, 128, 128);
      }
      else
      {
        debugger_set_color(255, 255, 255);
      }
      x += 0x20;
      addr += 4;
    }

 dummy_label_509389: ; // fakematch: permuter label
  }
}
// NON-MATCHING: close but still some stuff to figure out
// void debugger_draw_stack(void) {
//     s32 temp_s0;
//     u8 range_prefix;
//     u32 temp_s2;
//     s32 temp_s5;
//     s32 phi_s1;
//     u32 *phi_s2;
//     u32 phi_s5;
//     s32 i;
//
//     temp_s0 = g_dbg_fault_thread->unkF4;
//     debugger_set_color(0, 255, 0); // green
//     debugger_print_string(11, &g_dbg_str_stack_title);
//     temp_s2 = (g_dbg_stack_scroll * 4) + temp_s0;
//     if (((temp_s2 & 3) == 0) && (temp_s2 >= 0x80000000U) && (temp_s2 < 0x80800001U)) {
//         if (g_dbg_stack_scroll == 0) {
//             debugger_set_color(255, 0, 0); // red
//             phi_s5 = &D_8002D4B0;
//         } else {
//             temp_s5 = &D_8002D4B0 - 0x2B50; // 11088 ?
//             if ((temp_s2 >= temp_s5) && (temp_s2 < (temp_s5 + 0x400))) {
//                 debugger_set_color(128, 128, 255); // purple
//                 phi_s5 = temp_s5;
//             } else if ((temp_s2 >= (u32) &D_8002D8B0) && (temp_s2 < ((u32)&D_8002D8B0 + 0x4000))) {
//                 debugger_set_color(255, 128, 128); // light red
//                 phi_s5 = temp_s5;
//             } else {
//                 debugger_set_color(255, 255, 255);
//                 phi_s5 = temp_s5;
//             }
//         }
//         phi_s1 = 97; // "a"
//         phi_s2 = temp_s2;
//         for (i = 0; i < 22; i++) {
//             debugger_print_number(phi_s1, 0, phi_s2);
//             debugger_print_string(phi_s1 + 8, &g_dbg_str_stack_addr_sep);
//             range_prefix = (*phi_s2 >> 24);
//             if (range_prefix == 0x80) {                   // 0x80000000
//                 debugger_set_color(128, 128, 255);
//             } else if (range_prefix == 0x15) {            // 0x15000000
//                 debugger_set_color(255, 0, 0);
//             } else if (range_prefix == 0x16) {            // 0x16000000
//                 debugger_set_color(128, 255, 128);
//             } else if (range_prefix == 0x10) {            // 0x10000000
//                 debugger_set_color(255, 0, 0);
//             } else {
//                 debugger_set_color(255, 255, 255);
//             }
//             debugger_print_number(phi_s1 + 0xC, 0, *phi_s2);
//             debugger_print_string(phi_s1 + 0x16, &g_dbg_str_stack_val_sep);
//             debugger_set_color(255, 255, 255);
//             debugger_print_number(phi_s1 + 0x16, 1, *phi_s2);
//             if (((u32) phi_s2 >= phi_s5) && ((u32) phi_s2 < (phi_s5 + 0x400))) {
//                 debugger_set_color(128, 128, 0xFF);
//             } else if (((u32) phi_s2 >= (u32) &D_8002D8B0) && ((u32) phi_s2 < ((u32)&D_8002D8B0 + 0x4000))) {
//                 debugger_set_color(255, 128, 128);
//             } else {
//                 debugger_set_color(255, 255, 255);
//             }
//             phi_s1 += 0x20;
//             phi_s2 += 4;
//         }
//     }
// }

/* was func_16000A5C */
s32 debugger_stack_page_input(void) {
    s32 res = 0;

    if ((g_dbg_stick_y >= 41) || (g_dbg_buttons_pressed & U_CBUTTONS)) {
        g_dbg_stack_scroll -= 1;
        if (g_dbg_stack_scroll < 0) {
            g_dbg_stack_scroll = 0;
        } else {
            res = 3;
        }
    } else if ((g_dbg_stick_y < -40) || (g_dbg_buttons_pressed & D_CBUTTONS)) {
        g_dbg_stack_scroll += 1;
        if (g_dbg_stack_scroll >= 201) {
            g_dbg_stack_scroll = 200;
        }
        res = 3;
    }
    if ((g_dbg_buttons_pressed & B_BUTTON)) {
        g_dbg_page = 1;
        res = 3;
    }
    return res;
}

// called from func_10007DAC
s32 debug_cont_read(void);
void debug_cont_get_read_data(void *);
s32 debug_dump_tlb();
extern s32 g_dbg_buttons_held; /* was D_16003894 */
extern s32 g_dbg_buttons_prev; /* was D_16003898 */
extern s32 g_dbg_tlb_entrylo0; /* was D_160038AC */
extern s32 g_dbg_tlb_entrylo1; /* was D_1600392C */
extern s32 g_dbg_tlb_entryhi; /* was D_160039AC */
extern s32 g_dbg_tlb_entryhi_15; /* was D_160039E8 */
extern s32 g_dbg_tlb_pagemask; /* was D_16003A2C */
extern s32 g_dbg_tlb_pagemask_15; /* was D_16003A68 */
extern s32 g_dbg_page_draw_fns; /* was D_16003AF8 */
extern s32 g_dbg_page_input_fns; /* was D_16003B08 */
extern u8 *D_8002C130;
extern s32 g_tlb_entry15_saved; /* was D_8003CC88 */
void func_150ADC50(void); /* code (asm/D5E90.s), compared by address below */
extern s32 debug_cont_pad_buf;

/* was func_16000B14 */
s32 debugger_main(OSThread *arg0) {
    s32 sp40;
    s32 (*temp_v0)();
    s32 *var_a0;
    s32 (*temp_v1)();
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_t4;
    s32 temp_t5;
    s32 var_s3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v1;
    u32 temp_t1;

    var_s3 = 0;
    sp40 = 1;
    if (D_8002AC5C != 0) {
        return 0;
    }
    g_dbg_fb_index = 0;
    if (((*(s32 *)((u8 *)D_8002AAE8 + 0)) == 0) || (D_8002AAE8[1] == 0)) {
        (*(s32 *)((u8 *)D_8002AAE8 + 0)) = 0x80350000;
        D_8002AAE8[1] = 0x80350000;
        return 0;
    }
    debug_dump_tlb();
    (*(s32 *)((u8 *)(&g_dbg_tlb_entrylo0) + 0x3C)) = (s32) (*(s32 *)((u8 *)(&g_tlb_entry15_saved) + 0));
    (*(s32 *)((u8 *)(&g_dbg_tlb_entrylo1) + 0x3C)) = (s32) (*(s32 *)((u8 *)(&g_tlb_entry15_saved) + 4));
    g_dbg_tlb_entryhi_15 = (*(s32 *)((u8 *)(&g_tlb_entry15_saved) + 8));
    g_dbg_tlb_pagemask_15 = (*(s32 *)((u8 *)(&g_tlb_entry15_saved) + 0xC));
    temp_t1 = arg0->context.pc;
    if ((temp_t1 & 0xFF000000) != 0x15000000) {
        g_dbg_fault_not_retryable = 1;
    } else {
        temp_a1 = temp_t1 & ~0xFFF;
        temp_a2 = temp_a1 & 0x1000;
        temp_t4 = temp_a1 & ~0x1000;
        g_dbg_fault_not_retryable = 0;
        var_a0 = &g_dbg_tlb_entryhi;
        var_v1 = 0;
        do {
            if (temp_t4 == (*(s32 *)((u8 *)var_a0 + 0))) {
                if (temp_a2 != 0) {
                    var_v0_2 = *(s32 *)((u8 *)&g_dbg_tlb_entrylo1 + var_v1);
                } else {
                    var_v0_2 = *(s32 *)((u8 *)&g_dbg_tlb_entrylo0 + var_v1);
                }
                if (var_v0_2 & 2) {
                    g_dbg_fault_not_retryable = 1;
                }
            }
            if (temp_t4 == (*(s32 *)((u8 *)var_a0 + 4))) {
                if (temp_a2 != 0) {
                    var_v0_3 = (*(s32 *)((u8 *)((u8 *)&g_dbg_tlb_entrylo1 + var_v1) + 4));
                } else {
                    var_v0_3 = (*(s32 *)((u8 *)((u8 *)&g_dbg_tlb_entrylo0 + var_v1) + 4));
                }
                if (var_v0_3 & 2) {
                    g_dbg_fault_not_retryable = 1;
                }
            }
            if (temp_t4 == (*(s32 *)((u8 *)var_a0 + 8))) {
                if (temp_a2 != 0) {
                    var_v0_4 = (*(s32 *)((u8 *)((u8 *)&g_dbg_tlb_entrylo1 + var_v1) + 8));
                } else {
                    var_v0_4 = (*(s32 *)((u8 *)((u8 *)&g_dbg_tlb_entrylo0 + var_v1) + 8));
                }
                if (var_v0_4 & 2) {
                    g_dbg_fault_not_retryable = 1;
                }
            }
            temp_t5 = (*(s32 *)((u8 *)var_a0 + 0xC));
            var_a0 += 4;   /* 0x10 bytes */
            if (temp_t4 == temp_t5) {
                if (temp_a2 != 0) {
                    var_v0_5 = (*(s32 *)((u8 *)((u8 *)&g_dbg_tlb_entrylo1 + var_v1) + 0xC));
                } else {
                    var_v0_5 = (*(s32 *)((u8 *)((u8 *)&g_dbg_tlb_entrylo0 + var_v1) + 0xC));
                }
                if (var_v0_5 & 2) {
                    g_dbg_fault_not_retryable = 1;
                }
            }
            var_v1 += 0x10;
        } while (var_a0 != &g_dbg_tlb_pagemask);
    }
    if ((((u32) D_8003C8E0 >> 0x18) & 0xFF) == 0xC) {
        arg0 = &D_80031AE0;
    }
    if ((*(s32 *)((u8 *)D_8002C130 + 4)) == D_8002AAE8[1]) {
        g_dbg_fb_index = 1;
    }
    g_dbg_fault_thread = (struct118 *) arg0;
    g_dbg_is_lockup = 0;
    if ((arg0->context.cause == 0x20) && ((s32)func_150ADC50 == arg0->context.pc)) {
        g_dbg_is_lockup = 1;
    }
    do {
        if ((sp40 == 0) && (var_s3 & 2)) {
            debugger_clear_screen();
        }
        temp_v0 = *(s32 *)((u8 *)&g_dbg_page_draw_fns + (g_dbg_page * 4));
        if (temp_v0 != NULL) {
            temp_v0();
        }
        osWritebackDCacheAll();
loop_47:
        var_s3 = 0;
        g_dbg_buttons_prev = g_dbg_buttons_held;
        debug_cont_read();
        debug_cont_get_read_data(&debug_cont_pad_buf);
        if (sp40 != 0) {
            g_dbg_buttons_prev = g_dbg_buttons_held;
        }
        g_dbg_buttons_held = (s32) (*(u16 *)((u8 *)(&debug_cont_pad_buf) + 0));
        if ((*(s8 *)((u8 *)(&debug_cont_pad_buf) + 2)) >= 0x33) {
            g_dbg_buttons_held = (*(u16 *)((u8 *)(&debug_cont_pad_buf) + 0)) | 0x20000;
        }
        if ((*(s8 *)((u8 *)(&debug_cont_pad_buf) + 2)) < -0x32) {
            g_dbg_buttons_held |= 0x10000;
        }
        if ((*(s8 *)((u8 *)(&debug_cont_pad_buf) + 3)) >= 0x33) {
            g_dbg_buttons_held |= 0x40000;
        }
        if ((*(s8 *)((u8 *)(&debug_cont_pad_buf) + 3)) < -0x32) {
            g_dbg_buttons_held |= 0x80000;
        }
        g_dbg_buttons_pressed = (g_dbg_buttons_held ^ g_dbg_buttons_prev) & g_dbg_buttons_held;
        temp_v1 = *(s32 *)((u8 *)&g_dbg_page_input_fns + (g_dbg_page * 4));
        if (temp_v1 != NULL) {
            var_s3 = temp_v1();
        }
        if (!(var_s3 & 5)) {
            goto loop_47;
        }
        sp40 = 0;
    } while (!(var_s3 & 4));
    if (g_dbg_fault_not_retryable == 0) {
        arg0->state = 4;
        arg0->flags = 0;
        return 1;
    }
    var_v0 = 0;
    if ((arg0->context.cause == 0x20) && (g_dbg_is_lockup == 0)) {
        var_v0 = 1;
        arg0->context.pc += 4;
    }
    return var_v0;
}
s32 debug_sprintf(u8 *, u8 *, u8 *, u8 *, f64);
/* was func_16000F8C */
void debugger_print_float(s32 arg0, f32 arg1)
{
  f32 sp54;
  s32 bits;
  u8 sp28[0x28];
  u32 exp;
  if ((arg0 >= (g_dbg_first_text_row << 5)) && (arg0 < 0x341))
  {
    sp54 = arg1;
    bits = *((s32 *) (&sp54));
    exp = ((u32) (bits & 0x7F800000)) >> 0x17;
    do { } while (0); // fakematch: permuter register assignment
    if (((exp == 0) || (exp >= 0xFFU)) && ((bits * 2) != 0))
    {
      if ((!bits) && (!bits)) { } // fakematch: permuter register assignment
      debugger_print_string(arg0, g_dbg_str_float_bad);
      return;
    }
    debug_sprintf(sp28, g_dbg_str_float_fmt, g_dbg_str_float_arg_a, g_dbg_str_float_arg_b, (f64) arg1);
    debugger_print_string(arg0, sp28);
  }
}
// NON-MATCHING: lots to figure out
// void debugger_print_float(s32 arg0, f32 arg1) {
//     struct165 tmp;
//     s32 temp_v1;
//     u32 temp_t9;
//
//     if ((arg0 >= (g_dbg_first_text_row << 5)) && (arg0 < 833)) {
//         tmp.unk18 = arg1;
//         temp_v1 = *(s32*)&tmp.unk18;
//         temp_t9 = (u32) (temp_v1 & 0x7F800000) >> 0x17;
//         if ((temp_t9 == 0) || (temp_t9 >= 0x255U)) {
//             if ((temp_v1 * 2) != 0) {
//                 debugger_print_string(arg1, &g_dbg_str_float_bad); // arg0,
//                 return;
//             }
//         }
//         debug_sprintf(&arg0, &tmp.unk0, &g_dbg_str_float_fmt, &g_dbg_str_float_arg_a, &g_dbg_str_float_arg_b); // , (f64) arg1
//         debugger_print_string(arg0, &tmp.unk0);
//     }
// }

/* P281: readable C for debugger_print_number (compiled C, 155 insns). */
extern s32 g_dbg_pow10_table[10]; /* powers of ten 1 .. 1000000000 (the asm copies them to the stack first); was D_16003B50 */
extern u8 g_dbg_str_nan[]; /* "NaN"; was D_160047E4 */
extern u8 g_dbg_str_number_float_fmt[]; /* "%s%s%f"; was D_160047E8 */
extern u8 g_dbg_str_empty_a[]; /* ""; was D_160047F0 */
extern u8 g_dbg_str_empty_b[]; /* ""; was D_160047F4 */
// debug_print_value: prints `value` at text cell `cell` (rows from g_dbg_first_text_row to 0x340): kind 0 = 8 hex digits
// (written right to left), kind 1 = signed decimal without leading zeros, kind 2 = the float whose bits are `value`
// ("NaN" for infinities, NaNs and denormals).
/* was func_16001044 */
void debugger_print_number(s32 cell, s32 kind, s32 value) {
    u8 buf[0x24];
    u8 *pos;
    s32 *p;
    s32 i;
    s32 digit;
    s32 started;
    u8 c;
    s32 exp;

    if (cell < g_dbg_first_text_row * 32 || cell >= 0x341) {
        return;
    }
    pos = (u8 *) debugger_cell_to_fb(cell);
    switch (kind) {
        case 0:
            pos += 0x70;
            for (i = 0; i < 8; i++) {
                c = value & 0xF;
                if (c >= 10) {
                    c += 7;
                }
                c += '0';
                debugger_draw_char((s16 *) pos, c);
                value >>= 4;
                pos -= 0x10;
            }
            break;
        case 1:
            if (value < 0) {
                pos = debugger_draw_char((s16 *) pos, '-');
                value = -value;
            }
            started = 0;
            for (p = &g_dbg_pow10_table[9]; p >= g_dbg_pow10_table; p--) {
                digit = value / *p;
                value = value % *p;
                if (digit > 0 || started || p == g_dbg_pow10_table) {
                    pos = debugger_draw_char((s16 *) pos, (u8) (digit + '0'));
                    started = 1;
                }
            }
            break;
        case 2:
            exp = (value & 0x7F800000) >> 23;
            if ((exp <= 0 || exp >= 0xFF) && (exp != 0 || (value << 9) != 0)) {
                debugger_print_string(cell, g_dbg_str_nan);
                return;
            }
            debug_sprintf(buf, g_dbg_str_number_float_fmt, g_dbg_str_empty_a, g_dbg_str_empty_b, *(f32 *) &value); /* sprintf */
            debugger_print_string(cell, buf);
            break;
    }
}

/* was func_160012B0 */
void debugger_print_string(s32 arg0, u8 *arg1) {
    if (arg1 && (arg0 >= (g_dbg_first_text_row << 5)) && (arg0 < 833)) {
        s32 fb = debugger_cell_to_fb(arg0);   /* P80: a0 still holds arg0 at the jal (the text cell) */
        while (*arg1 != 0) {
            fb = debugger_draw_char(fb, *arg1 & 0xFF);
            *arg1++;
        }
    }
}
// convert rgb to rgba16
/* was func_16001338 */
void debugger_set_color(u8 arg0, u8 arg1, u8 arg2) {
    g_dbg_draw_color = ((arg0 & 0xF8) << 8) | ((arg1 & 0xF8) << 3) | ((arg2 & 0xF8) >> 2) | 1;
}

/* was func_16001390 */
void debugger_fill_rect(s16 x0, s16 y0, s16 x1, s16 y1) {
    s32 base;
    u16 *fb;
    s32 i;

    if (x1 < x0) {
        return;
    }
    if (y1 < y0) {
        return;
    }
    if (x0 < 0) {
        return;
    }
    if (y0 < 0) {
        return;
    }
    x1++;
    y1++;
    base = debugger_cell_to_fb(0);
    fb = (u16 *)base + (x0 + y0 * g_dbg_fb_width);
    x1 -= x0;
    y1 -= y0;
    for (; y1 > 0;) {
        for (i = x1; i > 0; i--) {
            *fb++ = g_dbg_draw_color;
        }
        y1--;
        fb += g_dbg_fb_width - x1;
    }
}
extern s32 g_dbg_font_glyphs; /* was D_16003CE0 */

/* was func_160014F0 */
u8 *debugger_draw_char(s16 *arg0, s32 arg1) {
    s16 *temp_v0;
    s16 *temp_v0_2;
    s16 *temp_v0_3;
    s16 *var_v0;
    s16 var_t2;
    s16 var_t2_2;
    s16 var_t2_3;
    s16 var_t2_4;
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_t1_3;
    s32 temp_t6;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    u8 *var_t0;
    u8 var_a2_2;

    temp_t6 = arg1 & 0xFF;
    var_v0 = arg0;
    var_a2 = temp_t6;
    if (temp_t6 < 0x20) {
        var_a2 = 0x20;
    }
    var_t0 = ((s32 *)((u8 *)&g_dbg_font_glyphs + ((var_a2 - 0x20) * 8)));
    var_a3 = 0;
    do {
        var_a1 = 0;
        var_a2_2 = *var_t0;
loop_4:
        if (var_a2_2 & 0x80) {
            var_t2 = g_dbg_draw_color & 0xFFFF;
        } else {
            var_t2 = 1;
        }
        temp_t1 = (var_a2_2 * 2) & 0xFFFF;
        *var_v0 = var_t2;
        temp_v0 = ((s16 *)((u8 *)var_v0 + 2));
        if (temp_t1 & 0x80) {
            var_t2_2 = g_dbg_draw_color & 0xFFFF;
        } else {
            var_t2_2 = 1;
        }
        temp_t1_2 = (temp_t1 * 2) & 0xFFFF;
        *temp_v0 = var_t2_2;
        temp_v0_2 = ((s16 *)((u8 *)temp_v0 + 2));
        if (temp_t1_2 & 0x80) {
            var_t2_3 = g_dbg_draw_color & 0xFFFF;
        } else {
            var_t2_3 = 1;
        }
        temp_t1_3 = (temp_t1_2 * 2) & 0xFFFF;
        *temp_v0_2 = var_t2_3;
        temp_v0_3 = ((s16 *)((u8 *)temp_v0_2 + 2));
        if (temp_t1_3 & 0x80) {
            var_t2_4 = g_dbg_draw_color & 0xFFFF;
        } else {
            var_t2_4 = 1;
        }
        var_a1 += 4;
        var_a2_2 = (temp_t1_3 * 2) & 0xFFFF;
        *temp_v0_3 = var_t2_4;
        var_v0 = ((s16 *)((u8 *)temp_v0_3 + 2));
        if (var_a1 != 8) {
            goto loop_4;
        }
        var_a3 += 1;
        var_t0 += 1;
        var_v0 = (s16 *)((u8 *)var_v0 + ((g_dbg_fb_width - 8) * 2));
    } while (var_a3 != 8);
    return ((s16 *)((u8 *)arg0 + 0x10));
}
// NON-MATCHING: only glyph/j registers swapped (t0/a1)
// extern u8 g_dbg_font_glyphs[];
//
// u16 *debugger_draw_char(fb, c)
//     u16 *fb;
//     u8 c;
// {
//     u16 *p = fb;
//     s32 color = g_dbg_draw_color;
//     u16 bits;
//     u16 val;
//     s32 ch;
//     s32 i;
//     u8 *glyph;
//     s32 j;
//
//     ch = c;
//     if (ch < 0x20) {
//         ch = 0x20;
//     }
//     glyph = g_dbg_font_glyphs + ((ch - 0x20) << 3);
//     for (i = 0; i < 8; i++) {
//         bits = *glyph;
//         for (j = 0; j < 8; j++) {
//             if (bits & 0x80) {
//                 val = color;
//             } else {
//                 val = 1;
//             }
//             bits <<= 1;
//             *p++ = val;
//         }
//         glyph++;
//         p += g_dbg_fb_width - 8;
//     }
//     return fb + 8;
// }

// framebuffer address of a text cell
/* was func_1600160C */
s32 debugger_cell_to_fb(s32 arg0) {
    s32 y = arg0 & 0xFFE0;
    s32 v1 = y;

    if (g_dbg_fb_width != 0x124) {
        v1 = (y >> 2) + y;
    }
    v1 = (u32)(v1 >> 2) * (g_dbg_fb_width * 2);
    v1 += (arg0 & 0x1F) * 16;
    v1 += g_dbg_fb_width * 4;
    v1 += 0x10;
    return D_8002AAE8[g_dbg_fb_index] + v1;
}

// clear the framebuffer
/* was func_16001678 */
void debugger_clear_screen(void) {
    u32 *fb = D_8002AAE8[g_dbg_fb_index];
    s32 h;
    u32 *end;

    if (g_dbg_fb_width == 0x124) {
        h = 0xD7;
    } else {
        h = 0x108;
    }
    end = (u32 *)(((u32)(g_dbg_fb_width >> 1) * h * 4) + (u32)fb);
    while (fb < end) {
        fb[0] = 0x10001;
        fb[1] = 0x10001;
        fb[2] = 0x10001;
        fb[3] = 0x10001;
        fb += 4;
    }
}

/* was func_160016F4 */
s32 debugger_identity(s32 arg0) {
    return arg0;
}
