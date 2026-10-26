#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <ultra64.h>

#include "structs.h"

extern f32 fabsf(f32);
#pragma intrinsic (fabsf)

/* matching */
void func_10001050(void);
void func_100010F8(s32 arg0);
void func_10001444(void);
void func_100014A0(void);
s32  func_10002070(s32 arg0, s32 arg1, s32 arg2);
void func_1000349C(s32 arg0);
s32  func_1000390C(void);
void func_10003930(void);
void func_100039B0(void);
void func_100039C0(void);
void func_10004250(void);
void func_10004308(void);
void func_1000440C(void);
void func_10004470(void);
s32  func_10004514(s32 devAddr, void *dramAddr, u32 size, s32 arg3);
void func_10004674(void);
void func_10004F00(void);
void func_10004FE0(void);
void func_10005020(void);
void func_100051C8(OSPfs *pfs, OSMesgQueue *queue);
void func_100051E8(void);
void func_10005218(void);
void func_10005298(void);
void func_100084D8(u8 arg0);
s32  func_1000853C(u8 arg0);
void func_10008570(u8 arg0, s32 arg1);
void func_100085A4(s32 arg0, s32 arg1, s32 arg2);
void func_100085B8(u8 arg0, s32 arg1, u8 arg2);
void func_100085F8(u8 arg0, s32 arg1);
void func_1000862C(u8 arg0, s32 arg1);
void func_10008660(u8 arg0, u8 arg1, u8 arg2, s32 arg3);
void func_100086FC(u8 arg0, u8 arg1, u8 arg2);
void func_10008744(u8 arg0, u8 arg1, u8 arg2);
void func_10008790(u8 arg0, s32 arg1, u8 arg2, s32 arg3);
void func_10008824(u8 arg0, u8 arg1, u8 arg2);
void func_1000886C(u8 arg0, s32 arg1, u8 arg2);
void func_100088F0(u8 arg0, s32 arg1, s32 arg2);
void func_10008988(u8 idx, s32 mask, s32 enable);
u8   func_10008A4C(u8 idx, u8 chan);
void func_10008A94(u8 arg0, s32 arg1, s32 arg2);
void func_10008B2C(u8 arg0);
void func_10008B60(u8 arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4);
void func_10008BC0(u8 arg0, f32 arg1, f32 arg2);
void func_10008EE0(u8 arg0, s32 arg1);
void func_10008F24(u8 arg0);
void func_10008F58(u8 arg0);
void func_100093CC(void);
s32  func_10009980(s32 *arg0);
void func_10009B2C(struct54 *arg0);
void func_10009B4C(struct54 *arg0);
void func_10009B90(struct54 *arg0);
s32  func_1000BA18(u32 arg0, u8 arg1, f32 arg2, f32 arg3, f32 arg4);
struct151 *func_1000B1B0(s32 arg0);
s32  func_1000B830(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32  func_1000B8B8(s32 arg0, u8 arg1, f32 arg2, f32 arg3, f32 arg4);
s32  func_1000BBE8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32  func_1000BC28(s32 arg0, u8 arg1, s32 arg2, s32 arg3);
void func_1000CBA8(s32 arg0);
s32  func_1000CD40(s32 arg0, s32 arg1, s32 arg2);
void func_1000E054(s32 arg0, s32 arg1);
s32  func_1000E0F8(s32 arg0);
void func_1000E40C(s32 arg0, s32 arg1);
s32  func_1000E654(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32  func_1000E704(s32 arg0, s32 arg1, s32 arg2);
void func_1000E75C(s32 arg0);
s32  func_1000E770(s32 *arg0, s32 *arg1);
u16  func_1000EA94(s32 arg0);
s32  func_1000EB00(struct04 *arg0, s32 arg1, s32 *arg2, s32 *arg3, s32 arg6, s32 arg7, u16 *arg8);
s32  func_1000EBC4(struct00 *arg0, s32 arg1, s32 arg2, s32 arg3);
s32  func_1000EF40(struct57 *arg0, struct57 *arg1, s32 *arg2, s32 arg3, s32 arg4, s32 arg5, u16 *arg6);
void func_1000F248(s32 arg0);
s32  func_1000F3D0(u16 arg0);
s32  func_1000F44C(u16 arg0);
void func_1000F91C(u16 arg0, u16 arg1, s16 arg2, u8 arg3, s32 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9);
void func_1000F9D4(u16 arg0, s16 arg1, s16 arg2, s16 arg3);
void func_10010720(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4, s32 arg5) ;
s32  func_100107F8(struct127 *arg0);
s32  func_10010894(struct127 *arg0);
void func_100109D0(struct127 *arg0);
void func_10010A3C(struct127 *arg0);
void func_10010AA8(struct127 *arg0);
u16 func_10010F30(s32 arg0, u16 arg1, u8 arg2, s16 arg3, u8 arg4);
void func_100111C8(u16 arg0);
void func_1001123C(u16 arg0);
s32  func_100112BC(s32 arg0, s32 arg1);
s32  func_1001147C(u16 arg0);
void func_10011E88(s32 arg0);
void func_10011E94(s32 arg0);
void func_10011FA0(s32 *arg0);
void func_10011FB0(s32 arg0);
void func_10011FDC(s32 arg0);
void func_10011FEC(void);
#ifdef NON_MATCHING
void func_10012560(s32 arg0, u8 *arg1, s32 arg2);
#else
void func_10012560(s32 arg0);
#endif
void func_10012588(s32 arg0);
void func_100125CC(s32 arg0);
void func_1001263C(s32 arg0, s32 arg1, s32 arg2);
s32 func_100126E8(s32 arg0, s32 arg1);
s32  func_10012718(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4);
s32  func_100127D0(void);
void func_10012A28(struct121 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_10012B84(struct11 *arg0, s32 arg1);
void func_10012BD0(struct11 *arg0, s32 arg1);
void func_10012C5C(struct9 *arg0, s32 arg1, s32 arg2);
void func_10012CFC(struct12 *arg0, s32 arg1, s32 arg2);
f32  func_10012D80(u8 arg0);
s32  func_10012E04(s32 *arg0, f32 *arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5);
s32  func_10012F94(struct124 *arg0, f32 *arg1);
void func_100131D8(s32 *arg0);
void func_100131FC(struct13 *arg0, s32 arg1);
void func_10015550(struct26 *arg0, s32 arg1);
s32  func_10015878(struct04 *arg0);
void func_10016E90(struct31 *arg0);
void func_10016F00(struct154 *arg0);
struct31 *func_10017100(s32 arg0, s16 arg1);
void func_10017298(struct31 *arg0);
s32  func_100173C4(struct31 **arg0);
void func_10017594(struct31 *arg0);
void func_100176C4(void);
void func_100176EC(void);
void func_10017714(s32 arg0, s16 arg1, s32 arg2);
void func_10017870(u8 arg0);
void func_10017944(s32 arg0, u32 arg1);
s32  func_10017A80(struct26 *arg0);
void func_10017AA0(struct26 *arg0);
void func_10017AF0(struct26 *arg0, s32 arg1);
void func_10017B04(struct26 *arg0, s32 arg1, u8 arg2);
void func_10017B30(struct26 *arg0);
void func_10017BB8(struct26 *arg0, s32 arg1);

void func_10017D80(struct26 *arg0, u8 arg1, u8 arg2);
void func_10017DF0(struct26 *arg0, f32 arg1, f32 arg2);
void func_10017E4C(struct26 *arg0, u8 arg1, u8 arg2);
void func_10017F10(struct26 *arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4);

void n_alInit(struct07 *arg0, s32 arg1);
void n_alClose(s32 arg0);
s32  _n_timeToSamplesNoRound(s32 micros);
s32  _n_timeToSamples(s32 micros);
f32  alCents2Ratio(s32 arg0);
void func_10019B50(struct26 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_10019C28(struct26 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_10019CD0(struct26 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_10019D6C(struct26 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_10019ED8(struct26 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_10019F38(struct26 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_10019F98(struct26 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_1001A224(struct26 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_1001A2F8(struct26 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_1001A39C(struct26 *arg0, s32 arg1, s32 arg2, u32 arg3);
void func_1001A3E0(struct24 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_1001A3FC(struct26 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_1001A9DC(struct26 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_1001AA08(struct26 *arg0, s32 arg1, s32 arg2, s32 arg3);
s32  __n_vsDelta(struct07 *arg0, s32 arg1);
void func_1001B620(struct26 *arg0, s32 arg1);
void func_1001CBF0(f32 arg0, f32 arg1, f32 arg2, struct17 *arg3, struct17 *arg4);
void func_1001CD54(struct125 *arg0);
f32  func_1001CEA4(s32 arg0);
void func_1001D6E8(struct42 *arg0, s32 (*arg1)(s32 arg), struct15 *arg2);
s32  func_1001D9B0(s16 arg0);
s32  func_1001DA28(s16 arg0);
void func_1001DAA0(s32 arg0, s16 arg1, s32 arg2);
void func_1001DAE4(struct139 *arg0, s16 arg1, s32 *arg2);
// void func_1001E170(struct22 *arg0, s32 *w, f32 pitch, s16 vol, u8 pan, u8 fxmix, u8 arg6, f32 arg7, u8 arg8, s32 arg9);
// void func_1001E400(struct26 *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4);
s32  func_1001E4A0(s16 arg0, s32 arg1, s32 arg2);
f32  func_1001FA78(f32 arg0[4][4], s32 arg1);
/* chunk0 */
void game_init_message_queues(void);
void level_music_stop_all(void);
void texture_scroll_clear(void);
void func_15001B08(void);
u16* func_15001B10(void);
void func_15001BC8(s32 arg0, s16 *arg1, s16 *arg2);
void func_15001970(void);
void func_150026C4(s32 arg0);
void func_150026E8(s32 arg0);
void func_15002724(s32 arg0);
void func_15002F40(s32 arg0);
s32  func_15002FA0(s32 arg0);
void func_15002FB4(s32 arg0);
void func_1500310C(void);
s32  texture_table_reset(void);
void collision_build_quadtrees(void);
s32  texture_table_find(s32 arg0);
void collision_noop(s32 arg0);
void collision_set_tri_flags_table(s32 arg0);
void world_objects_noop(void);
void func_15004E00(void);
void func_15004E80(void);
void func_15004F00(void);
void func_15004F10(void);
void func_15004F30(void);
void func_15005270(void);
void func_15005A60(struct108 *arg0, s32 arg1);
void func_15005AB0(struct108 *arg0);
void func_15005AF0(s32 arg0);
void func_15005B00(s32 arg0);
void func_15005B10(struct108 *arg0);
void func_15005B50(s32 arg0);
void func_15005B60(s32 arg0);
void func_15005B70(s32 arg0);
void func_15005BD0(struct108 *arg0);
void func_15005C30(struct108 *arg0);
void func_15005C80(struct108 *arg0);
void func_15005CF0(s32 arg0);
void func_15005D00(struct108 *arg0);
void func_15005D60(struct108 *arg0);
void func_15005DB0(struct108 *arg0);
void func_15005E30(struct108 *arg0);
void func_15005E70(struct108 *arg0);
void func_15005EA0(struct108 *arg0);
void func_15005EE0(struct108 *arg0);
void func_15005F20(struct108 *arg0);
void func_15005F60(struct108 *arg0);
void func_15005FA0(s32 arg0);
void func_15005FB0(struct108 *arg0);
void func_15006010(struct108 *arg0);
void func_15006140(struct108 *arg0);
void func_15006170(struct108 *arg0);
void controller_init_si_queue(void);
void save_game_defaults(void);
void controller_init_hook_noop(void);
void save_request_options_load(void);
void save_request_options_write(void);
void save_request_config_load(void);
void save_request_config_write(void);
void save_request_slot_load(s32 arg0);
void save_request_slot_write(s32 arg0);
void save_request_slot_erase(s32 arg0);
void func_15007A20(void);
void level_start_game(s16 arg0, s16 arg1, s16 arg2);
void level_reset_globals(void);
void cutscene_clear_pending(void);
void cutscene_reset_state(s32 arg0);
void cutscene_start_pending(void);
void func_15008840(void);
void func_15008A10(void);
void func_15008B90(void);
void func_15008BB0(void);
void func_15008BE0(void);
void func_15008DD0(void);
void area_points_reset(void);
void func_15009150(s32 arg0);
void hotspot_fx_type01(s32 arg0, s32 arg1);
void hotspot_fx_type02(s32 arg0, s32 arg1);
void hotspot_fx_type07(s32 arg0, s32 arg1);
void hotspot_fx_type13(s32 arg0, s32 arg1);
void hotspot_fx_type14(s32 arg0, s32 arg1);
void hotspot_fx_type15(s32 arg0, s32 arg1);
void hotspot_fx_type16(s32 arg0, s32 arg1);
void hotspot_fx_type17(s32 arg0, s32 arg1);
void hotspot_fx_type18(s32 arg0, s32 arg1);
void hotspot_fx_type19(s32 arg0, s32 arg1);
void hotspot_fx_type20(s32 arg0, s32 arg1);
void hotspot_fx_type21(s32 arg0, s32 arg1);
void hotspot_fx_type22(s32 arg0, s32 arg1);
void hotspot_fx_type23(s32 arg0, s32 arg1);
void hotspot_fx_type28(s32 arg0, s32 arg1);
void hotspot_fx_type29(s32 arg0, s32 arg1);
void hotspot_fx_type76(s32 arg0, s32 arg1);
void hotspot_fx_type30(s32 arg0, s32 arg1);
void hotspot_fx_type33(s32 arg0, s32 arg1);
void hotspot_fx_type34(s32 arg0, s32 arg1);
void hotspot_fx_type35(s32 arg0, s32 arg1);
void hotspot_fx_type36(s32 arg0, s32 arg1);
void hotspot_fx_type37(s32 arg0, s32 arg1);
void hotspot_fx_type38(s32 arg0, s32 arg1);
void hotspot_fx_type39(s32 arg0, s32 arg1);
void hotspot_fx_type40(s32 arg0, s32 arg1);
void hotspot_fx_type41(s32 arg0, s32 arg1);
void hotspot_fx_type43(s32 arg0, s32 arg1);
void hotspot_fx_type44(s32 arg0, s32 arg1);
void hotspot_fx_type45(s32 arg0, s32 arg1);
void hotspot_fx_type46(s32 arg0, s32 arg1);
void hotspot_fx_type47(s32 arg0, s32 arg1);
void hotspot_fx_type48(s32 arg0, s32 arg1);
void hotspot_fx_type49(s32 arg0, s32 arg1);
void hotspot_fx_type50(s32 arg0, s32 arg1);
void hotspot_fx_type55(s32 arg0, s32 arg1);
void hotspot_fx_type58(s32 arg0, s32 arg1);
void hotspot_fx_type59(s32 arg0, s32 arg1);
void hotspot_fx_type60(s32 arg0, s32 arg1);
void hotspot_fx_type61(s32 arg0, s32 arg1);
void hotspot_fx_type62(s32 arg0, s32 arg1);
void hotspot_fx_type63(s32 arg0, s32 arg1);
void hotspot_fx_type64(s32 arg0, s32 arg1);
void hotspot_fx_type77(s32 arg0, s32 arg1);
void hotspot_fx_type65(s32 arg0, s32 arg1);
void hotspot_fx_type66(s32 arg0, s32 arg1);
void hotspot_fx_type67(s32 arg0, s32 arg1);
void hotspot_fx_type68(s32 arg0, s32 arg1);
void hotspot_fx_type78(s32 arg0, s32 arg1);
void hotspot_fx_type79(s32 arg0, s32 arg1);
void hotspot_fx_type86(s32 arg0, s32 arg1);
void hotspot_fx_type87_88(s32 arg0, s32 arg1);
void hotspot_fx_dispatch(s32 arg0, s32 arg1);
void ambient_fx_spawn_type2(s32 arg0);
void ambient_fx_dispatch(s32 arg0);
void func_1500ABA0(s32 arg0);
void func_1500BE40(s32 arg0);
void func_1500BE68(void);

void func_1500EB20(void);
void func_1500EB30(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_1500EBC4(void);
void func_1500ED80(void);
void func_1500EE18(struct127 *arg0, s32 arg1, s32 arg2);
void func_1500EE94(struct16 *arg0);
void func_1500EF20(void);

void func_15010240(void);
void func_150102C0(void);
void func_150102D0(void);
void func_150103E0(void);
void obj_spawn_effect_80(struct127 *arg0);
void func_15010680(void);
void func_150106A0(void);
void func_150106B0(void);
s32  func_150106D0(struct39 *arg0);
void level_obj_init_vertex_lights(void);
void func_15010FB0(void);
void func_150110F0(void);
void func_15011170(void);
void func_15011330(void);
void func_15011360(void);
void obj_spawn_effect_85(struct127 *arg0, u8 arg1, s32 arg2);
void func_15011B00(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_15011B94(void);
void func_15011C40(void);
void func_15011C70(void);
void func_15011CA0(void);
void func_15011CC0(void);
void func_15011F20(s32 arg0);
void func_15011FA0(s32 arg0);
void func_15012020(s32 arg0, s32 arg1);
u8   func_15012720(void);
void func_15012770(void);
void func_15012780(void);
s32  record_light_list_add(s32);
s32  record_dispatch_82f70(struct134 *arg0);
void func_15016370(void);
void level_globals_reset(void);
void level_lights_init(s16 arg0, s16 arg1);
void render_set_detail_level(void);
void level_state_clear(void);
void level_state_init(void);
void func_1501C860(void);
void func_1501C870(void);

void dl_validate(void *arg0, u32 arg1);
s32  dlcheck_tri_invalid(u32 *arg0);
s32 dlcheck_dl_invalid(struct148 *arg0);
void text_queue_reset(void);
void text_set_flags(u8 arg0);
void text_set_scale(f32 arg0);
void text_set_box(s32 arg0, s32 arg1);
void text_set_pos(s16 arg0, s16 arg1);
void text_set_color(u8 arg0, u8 arg1, u8 arg2, u8 arg3);
void ring_buffer_init(struct105 *arg0, s32 arg1, s32 arg2);
void mtx_build_rot_scale_trans(Mtx *m, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9);
void mtx_build_rot_trans(Mtx *m, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void mtxf_scale_set_trans(f32 mtx[4][4], f32 x, f32 y, f32 z, f32 arg4, f32 arg5, f32 arg6);
void vec_from_fixed_pos(vertex *arg0, struct113 *arg1);
void mtxf_translate_local(f32 arg0[4][4], f32 x, f32 y, f32 z);
void func_15047F00(f32 mtx[4][4], u16 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void func_15048134(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
f32  func_150484A0(f32 arg0, f32 arg1);
u16  func_15048664(s16 arg0);
s16  func_150486B8(s16 arg0);
f32  func_15048360(f32 arg0);
f32  func_15048408(f32 arg0);
f32  func_15048720(f32 arg0, f32 arg1, f32 arg2);
void func_15048758(f32 *arg0);
f32  math_asin_scaled(f32 arg0);
f32  math_asin_u8(f32 arg0);
f32 math_sin_u8(u8 arg0);
f32  math_angle_diff_deg(f32 arg0, f32 arg1);
s32  math_angle_diff_deg_int(s32 arg0, s32 arg1);
void obj_build_inverse_mtx(s32 arg0, s32 arg1);
void vec3_add(struct17 *arg0, struct17 *arg1, struct17 *arg2);
void vec3_sub(struct17 *arg0, struct17 *arg1, struct17 *arg2);
void vec3_diff(struct17 *arg0, struct17 *arg1, struct17 *arg2);
void vec3_scale(struct17 *arg0, f32 arg1, struct17 *arg2);
void vec3_normalize(struct17 *arg0, struct17 *arg1);
void vec3_dir_to(struct17 *arg0, struct17 *arg1, struct17 *arg2);
void quadtree_set_test_box(f32 arg0, f32 arg1, f32 arg2);
s32 func_15049440(f32 arg0[4][4], f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9);
f32  func_1504A5E0(f32 arg0);
s32  func_1504AEF4(s32 arg0, s32 arg1);
s32  func_1504C078(void);
s32  func_1504C0B8(void);
void func_1504C854(struct127 *arg0);

void func_15052408(struct127 *arg0);
void func_15052458(s32 arg0);
void func_15052464(struct127 *arg0);
void func_15052490(struct127 *arg0, u16 arg1, f32 arg2, f32 arg3);
void func_15052EF0(struct127 *arg0);
struct127 *func_15052F58(s32 arg0, s32 arg1);
void func_15053694(struct127 *arg0);
void func_150536D0(struct127 *arg0);
void func_150536E8(struct127 *arg0);
void func_1505371C(struct127 *arg0);
void func_15055D48(struct127 *arg0);
void obj_leash_to_spawn(struct127 *arg0);
void obj_follow_water_level(struct127 *arg0);
s32  obj_in_spawn_radius(struct127 *arg0, s32 arg1);
void obj_set_gravity_band(struct127 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void obj_physics_step(struct127 *arg0);
void obj_blend_push_velocity(struct127 *arg0, u16 arg1, f32 arg2, f32 arg3);
void obj_apply_level_current(struct127 *arg0);
void obj_attach_to_carrier(struct127 *arg0, s32 arg1);
f32  pad_stick_speed(struct49 *arg0);
u16  math_atan2_u16(f32 arg0, f32 arg1, s32 arg2);
f32  obj_dist_xz(struct127 *arg0, struct127 *arg1);
s16  obj_facing_angle_diff(struct127 *arg0, struct127 *arg1);
void obj_start_knockback(struct127 *arg0, u8 arg1);
f32  math_rotate_offset_deg(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4);

void obj_sfx_play_simple(s32 arg0, void *arg1);
void obj_fade_reset(struct127 *arg0);
void obj_model_reset(struct127 *arg0);
void obj_update_inner_extent_ratios(struct127 *arg0);
void obj_set_inner_extent_width(struct127 *arg0, f32 arg1);
void obj_set_inner_extent_height(struct127 *arg0, f32 arg1);
void obj_update_outer_extent_ratios(struct127 *arg0);
void obj_set_scale(struct127 *arg0, f32 arg1, f32 arg2);
void objev_anim_38(void);
void objev_anim_48(void);
void objev_anim_39(void);
void objev_nop_1506b070(void);
void objev_anim_d1_by_depth(void);
void objev_play_anim(s32 arg0, f32 arg1, f32 arg2);
void objev_anim_next(void);
void objev_anim_next_flagged(void);
void objev_anim_3c(void);
void objev_anim_54(void);
void objev_anim_f_allow_run(void);
void objev_release_if_player_link(void);
void objev_anim_3e(void);
void objev_nop_1506b368(void);
void objev_player_lose_life(void);
void objev_nop_1506b3b0(void);
void objev_pick_turn_to_player_wrap(void);
void objev_clear_21c(void);
void objev_hurt_or_die(void);
void objev_nop_1506b5a4(void);
void objev_nop_1506b5ac(void);
void objev_set_1cb(void);
void objev_set_1cb_b(void);
void objev_stop_anim(void);
void objev_random_idle_or_swim(void);
void objev_allow_run_pick_idle(void);
void objev_allow_run_idle(void);
void objev_anim_b5(void);
void objev_anim_b6(void);
void objev_reset_state_idle(void);
void objev_anim_de(void);
void objev_anim_bf(void);
void objev_anim_c5_allow_run(void);
void objev_anim_af(void);
void objev_clear_244(void);
void objev_sound_or_stop(s32 arg0, s32 arg1);
void objev_sound_alt_or_stop(s32 arg0, s32 arg1);
void objev_sound_hi_word_3(s32 arg0, s32 arg1);
void objev_sound_hi_word(s32 arg0, s32 arg1);
void objev_sound_hi_word_alt(s32 arg0, s32 arg1);
void objev_set_y_velocity(void);
void objev_jump_if_low(void);
void objev_set_gravity(void);
void objev_set_gravity_tenth(void);
void objev_allow_run(void);
void objev_set_target_speed(void);
void objev_set_disable_run(void);
void objev_set_d0_114(void);
void objev_sound_if_above_water(void);
void objev_stop_sound_alt(void);
void objev_stop_sound(void);
void objev_nop_1506d4ec(void);
void objev_anim_slow(void);
void objev_lose_life_cur_player(void);
void objev_clear_6e(void);
void objev_set_103(void);
void objev_nop_1506d950(void);
void objev_set_immune(void);
void objev_screen_effect_stop(void);
void objev_set_1890_update(void);
void objev_set_xz_velocity(void);
void objev_set_239(void);
void objev_link_nearby_object(void);
void objev_set_2e8(void);
void objev_set_2ec(void);
void objev_set_health(void);
void objev_nop_1506dcf8(void);
void objev_clear_flags_f8(void);
void objev_set_matrix_physics(void);
void objev_nop_1506ddb8(void);
void objev_level_screen_effect(void);
void objev_screen_effect_twice(void);
void objev_sound_300_1800(void);
void objev_sound_100_800(void);
void objev_sound_190_1300(void);
void objev_sound_300_3000(void);
void objev_sound_700_4000(void);
void objev_sound_3000_8000(void);
void objev_sound_hi_300_1800(void);
void objev_sound_hi_300_3000(void);
void objev_sound_if_grounded(void);
void objev_sound_if_not_playing(void);
void objev_sound_global_300_1800(void);
void objev_sound_alt_300_1800(void);
void objev_sound_alt_100_800(void);
void objev_sound_alt_190_1300(void);
void objev_sound_alt_300_3000(void);
void objev_sound_alt_700_4000(void);
void objev_sound_alt_3000_8000(void);
void objev_sound_alt_hi_300_3000(void);
void objev_hold_frame_airborne(void);
void objev_anim_set_flag_8000(void);
void objev_set_3a(void);
void objev_set_83_lock(void);
void objev_set_100(void);
void objev_unlock_a9(void);
void objev_set_21c(void);
void objev_set_flags_f4(void);
void objev_clear_flags_f4(void);
void objev_or_flags_f4(void);
void objev_or_flags_25c(void);
void objev_clear_flags_25c(void);
void objev_trail_set(void);
void objev_set_24e(void);
void objev_clear_282(void);
void objfx_bb760_unless_8c(s32 arg0);
void objfx_bcbbc(s32 arg0);
void objfx_ba4c0(s32 arg0);
void objfx_dust_50(s32 arg0);
void objfx_dust_default(s32 arg0);
void objfx_c1260_0(s32 arg0);
void objfx_c1260_1(s32 arg0);
void objfx_spray_0(s32 arg0);
void objfx_spray_1(s32 arg0);
void objfx_aeeb0(s32 arg0);
void objfx_197a7c(s32 arg0);
void objfx_19ef70(s32 arg0);
void objfx_gun_shot(s32 arg0);
void objfx_1a0a10_70(s32 arg0);
void objfx_1a0a10_40(s32 arg0);
void objfx_buddy_marker_clear(s32 arg0);
void objfx_buddy_marker_create(s32 arg0);
void objfx_b3ab0(s32 arg0);
void objfx_emitter_kind6(s32 arg0);
void objfx_emitter_kind5(s32 arg0);
void objfx_1aabc4_0(s32 arg0);
void objfx_1aabc4_1(s32 arg0);
void objfx_1aabc4_0_b(s32 arg0);
void objfx_1aabc4_1_b(s32 arg0);
void objfx_1aabc4_2(s32 arg0);
void objfx_1aabc4_3(s32 arg0);
void objfx_1ab920_0(s32 arg0);
void objfx_1ab920_1(s32 arg0);
void objfx_1ab930(s32 arg0);
void objfx_cbf80_0(s32 arg0);
void objfx_cbf80_1(s32 arg0);
void objfx_cbf80_2(s32 arg0);
void objfx_ca150(s32 arg0);
void objfx_1b01b8_1b09bc(s32 arg0);
void objfx_1aeca0(s32 arg0);
void objfx_1b03b8(s32 arg0);
void objfx_193660(s32 arg0);
void objfx_1937f4(s32 arg0);
void objfx_shot_self(s32 arg0);
void objfx_1c5280(s32 arg0);
void objfx_1c9740(s32 arg0);
void objfx_eee00(s32 arg0);
void objfx_eef40(s32 arg0);
void objfx_f03f8_both(s32 arg0);
void objfx_ebec0_0(s32 arg0);
void objfx_ebec0_1(s32 arg0);
void objfx_fdda0(s32 arg0);
void objfx_fdf38(s32 arg0);
void objfx_fe320(s32 arg0);
void objfx_fe49c(s32 arg0);
void objfx_199834(s32 arg0);
void objfx_hit_at_self_1(s32 arg0);
void objfx_hit_at_self_0(s32 arg0);
void objfx_sparks_shake_2(s32 arg0);
void objfx_sparks_shake_1(s32 arg0);
void objfx_fc438(s32 arg0);
void objfx_ff840_1_0(s32 arg0);
void objfx_ff840_0_0(s32 arg0);
void objfx_ff840_0_1(s32 arg0);
void objfx_1d5714_a(s32 arg0);
void objfx_1d469c_4(s32 arg0);
void objfx_1d469c_2(s32 arg0);
void objfx_1d469c_3(s32 arg0);
void objfx_nop_1507161c(s32 arg0);
void objfx_1d0058(s32 arg0);
void objfx_1d0024(s32 arg0);
void objfx_b5c38(s32 arg0);
void objfx_shake_large(s32 arg0);
void objfx_kind18_activate(s32 arg0);
void objfx_f9bb0(s32 arg0);
void objfx_19072c(s32 arg0);
void objfx_1d5714_b(s32 arg0);
void objfx_fa520_0(s32 arg0);
void objfx_fa520_1(s32 arg0);
void objfx_fa520_2(s32 arg0);
void objfx_1d09a8(s32 arg0);
void objfx_f2230(s32 arg0);
void objev_run_action(void);
void objev_run_action_on_child(void);
void objev_141a7c(void);
void objev_192800(void);
void objev_set_247(void);
void objev_set_248(void);
void objev_anim_at_frame(void);
void objev_anim_59(void);
void objev_anim_24(void);
void objev_7c8e0(void);
void objev_skip_if_cutscene(void);
void objev_clear_10c_grounded(void);
struct127 *obj_find_child(struct127 *arg0);
void objev_set_mask_94(void);
void objev_clear_mask_94(void);
void objev_or_mask_94(void);
void objev_remove_kind(void);
void objev_remove_kind_owned(void);
void objev_set_anim_speed(void);
void objev_remove_self(void);
void objev_kill_self(void);
void objev_anim_2c_lock_run(void);
void objev_set_2e4(void);
void objev_action21_idle(void);
void objev_clear_66_idle(void);
void objev_clear_19b_idle(void);
void objev_maybe_anim_18a(void);
void objev_anim_next_blend6(void);
void objev_loop_sound_start(void);
void objev_loop_sound_stop(void);
void objev_set_10c(void);
void objev_scale_anim_speed(void);
void objev_clear_10c_if_slow(void);
void objev_set_stunned(void);
void func_1507304C(void);
void objev_set_22e(void);
void objev_nop_15073070(void);
void objev_12d748(void);
void objev_set_1ff_200(void);
void objev_set_wait_timer(void);
void objev_wait_timer(void);
void objev_set_44(void);
void objev_idle(void);
void objev_nop_15073c48(void);
void objev_release_kind53_wait(void);
void objev_set_inner_extent_width(void);
void objev_set_inner_extent_height(void);
void objev_unlink_kind(void);
void objev_camera_view_close(void);
void objev_camera_view_mode11(void);
void objev_camera_view_mode12(void);
void objev_set_timer_3c_2000(void);
void objev_nop_15073f54(void);
void objev_set_2cb(void);
void objev_clear_flags_10b(void);
void objev_set_31c_11a(void);
void objev_add_31c_1aa(void);
void objev_set_24f(void);
void objev_set_cc3d7(void);
void objev_set_31c_26(void);
void objev_skip_if_not_carrying(void);
void objev_hold_frame(void);
void objhit_nop_15074bd8(s32 arg0, s32 arg1, s32 arg2);
void objhit_nop_15074bec(s32 arg0, s32 arg1, s32 arg2);
void objhit_burst_state5(s32 arg0, struct127 *arg1, s32 arg2);
void objhit_set_2e8(struct127 *arg0, s32 arg1, s32 arg2);
void objhit_screen_flash_b(s32 arg0, s32 arg1, s32 arg2);
void objhit_grab_player_6(struct127 *arg0, struct127 *arg1, s32 arg2);
void objhit_grab_player_7(struct127 *arg0, struct127 *arg1, s32 arg2);
void objhit_take_state_from_b(struct127 *arg0, struct127 *arg1, s32 arg2);
void objhit_grab_player_and_hit(struct127 *arg0, struct127 *arg1, s32 arg2);
void objhit_bounce(struct127 *arg0, s32 arg1, s32 arg2);
void objhit_set_gravity(struct127 *arg0, s32 arg1, s32 arg2);
void objhit_kill_b(struct127 *arg0, struct127 *arg1, u8 *arg2);

void aiscript_apply_move_flags(void);
void aiscript_if_path_point(void);
void aiscript_mode10(void) ;

void hud_health_add_piece(void);

void hud_clock_set_enabled(s32 arg0);
void hud_clock_load(void);
void event_start_level_events(s32 arg0, s32 arg1);
void event_dispatch_alt(s32 num, s32, s32, ...);
void particle_fall_step(struct42 *arg0);
void sprite_grow_step(struct114 *arg0);
s32  checksum_key_offset(s32 arg0);
void func_150CEF10(struct108 *arg0);

void func_150DE310(s32 arg0);
void func_150DE32C(void); // dummy
void func_150DEC90(s32 arg0);
void target_volume_hit_check_offset(void *arg0, void *arg1, s32 arg2);
void func_150EC4B0(struct108 *arg0);
void func_150F51A0(s32 arg0, s32 arg1);
s32  func_150F51BC(void);
void func_150F51E8(s32 arg0);
void func_150FCA00(struct108 *arg0);

void func_15100330(s32 arg0);
void sfx_cooldown_clear(void);
void sfx_cooldown_tick(void);
void fx_free_on_msg_4b(struct102 *arg0, s32 arg1, u8 arg2);
void fx_quad_bolts_on_msg(struct207 *arg0, s32 *arg1, u8 arg2);
void fx_sparks_on_msg(struct207 *arg0, s32 arg1, u8 arg2);
void func_1511FC20(s32 arg0);
#ifdef NON_MATCHING
/* P183: debug position hooks, the arguments their only caller (world_mesh_draw) passes: gdl in a0, three f32 in
 * a1..a3 (mfc1), then an f32 / s32 on the stack; both return gdl. Same o32 registers as the 4 x s32 form. */
Gfx *func_1511FC2C(Gfx *gdl, f32 x, f32 y, f32 z, f32 w, s32 player);
Gfx *func_1511FC44(Gfx *gdl, f32 x, f32 y, f32 z, s32 player);
#else
s32  func_1511FC2C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32  func_1511FC44(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
#endif
void camera_update_all(void);
void camera_apply_zoom_level(struct108 *arg0);
void camera_read_side_input(struct108 *arg0);
void camera_set_second_target(struct108 *arg0, s32 arg1);
void camera_calc_view_dir(struct108 *arg0);
void camera_calc_pitch(struct108 *arg0);
void camera_calc_yaw(struct108 *arg0);
void camera_update_mode_index(struct108 *arg0);
s32  camera_update_locked_mode(struct108 *arg0);
void camera_sync_angles(struct108 *arg0);
void camera_reset_rates(struct108 *arg0);
void camera_raise_timer(struct108 *arg0, s32 arg1);
void camera_update_follow(struct108 *arg0);
void camera_start_transition(struct108 *arg0, s32 arg1, s32 arg2);
void camera_noop(struct108 *arg0);
void camera_init_controller(struct108 *arg0);
void camera_snap_to_object(struct108 *arg0, struct127 *arg1);
void func_1512D380(s32 arg0);
s32  fx_fade_alpha_by_life(struct102 *arg0);

struct210 *sprite_fx_spawn_at(s32 arg0, s32 arg1, u8 arg2, u8 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, s32 argC, s32 argD, u8 argE, s32 argF);
struct210 *sprite_fx_spawn_quad(s32 arg0, s32 arg1, u8 arg2, u8 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, u8 argC, s32 argD);
struct210 *sprite_fx_spawn_cam_at(s32 arg0, u8 arg1, u8 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, s32 argC, s32 argD, u8 argE, s32 argF);
struct210 *sprite_fx_spawn_cam(s32 arg0, u8 arg1, u8 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, u8 argC, s32 argD);
struct210 *sprite_fx_spawn_cam_ex(s32 arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u8 argA, u8 argB, s32 argC, u8 argD, s32 argE);
void sprite_fx_retire(struct210 *arg0);
void sprite_fx_free(struct210 *arg0);
void sprite_fx_free_buffers(struct210 *arg0);
void sprite_fx_dispatch_a(struct210 *arg0);
void sprite_fx_dispatch_b(struct210 *arg0);
void effect3d_release_slot(struct210 *arg0);
void effect3d_retire(struct210 *arg0);
void effect3d_free(struct210 *arg0);
void effect3d_free_buffers(struct210 *arg0);
void effect3d_dispatch_a(struct210 *arg0);
void effect3d_dispatch_b(struct210 *arg0);
#ifdef NON_MATCHING
struct210 *effect3d_spawn(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9);
#else
void effect3d_spawn(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9);
#endif
#ifdef NON_MATCHING
/* P128/P131: the NM definition (game_169510.c) returns effect3d_spawn_full's record (the asm leaves it in v0) */
struct210 *effect3d_spawn_default(s32 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s32 arg6, u8 arg7, s32 arg8);
#else
void effect3d_spawn_default(s32 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s32 arg6, u8 arg7, s32 arg8);
#endif
s32  effect3d_spawn_oriented(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s16 arg6, f32 arg7, f32 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, u8 argD, s32 argE, u8 argF, s32 arg10);
#ifdef NON_MATCHING
struct210 *effect3d_spawn_oriented_simple(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s16 arg6, f32 arg7, f32 arg8, s32 arg9, s32 argA, u8 argB, s32 argC, u8 argD, s32 argE);
#else
void effect3d_spawn_oriented_simple(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s16 arg6, f32 arg7, f32 arg8, s32 arg9, s32 argA, u8 argB, s32 argC, u8 argD, s32 argE);
#endif
void effect3d_msg_stub(s32 arg0, s32 arg1, s32 arg2);
void effect3d_on_msg_owner(struct210 *arg0, struct212 *arg1, u8 arg2);
void sprite_quad_stub_a(void);
void sprite_quad_stub_b(void);
#ifdef NON_MATCHING /* P224: D_8008A1BC entries return the callee's v0 */
s32 sprite_quad_build_screen_a(s32 arg0, s16 arg1);
#else
void sprite_quad_build_screen_a(s32 arg0, s16 arg1);
#endif
s32 sprite_quad_build_screen_b(s32 arg0, s16 arg1);
#ifdef NON_MATCHING
u8 *sprite_quad_build_axes_entry(struct210 *arg0, s16 arg1);
#else
void sprite_quad_build_axes_entry(struct210 *arg0, s16 arg1);
#endif
void fx_lists_broadcast_a(s32 arg0, u8 arg1);
void fx_lists_broadcast_b(s32 arg0, u8 arg1);
void effect_free_buffers_retire(struct210 *arg0);
void effect_free_buffers_delete(struct210 *arg0);
s32  effect_check_false(s32 arg0, s32 arg1);
void interact_fx_detach(struct37 *arg0);
void interact_fx_destroy(void *arg0);
void interact_fx_delete(void *arg0);
void obj_interaction_start_timed(void *arg0, s32 arg1, s32 arg2);
s32  debug_tweak_int_mid(s32 arg0, s32 arg1, s32 arg2, s32 arg3, char *arg4, s32 arg5);
s32  debug_tweak_int(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
s32  debug_tweak_value(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32  func_15143E08(struct127 *arg0);
s32  func_15144C2C(s16 arg0);
f32  func_15144C8C(f32 arg0, f32 arg1);
void func_151450B4(struct17 *arg0, struct17 *arg1, struct17 *arg2);
s32  func_151454BC(u8 arg0, f32 arg1, struct17 *arg2);
f32  func_15145A0C(f32 arg0, f32 arg1, f32 arg2);
void func_15145A50(struct127 *arg0);
void func_15146508(struct127 *arg0, struct127 *arg1);
void func_151467A4(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 *arg7);
struct260 *func_15149130(s16 arg0, s8 arg1, s8 arg2, s8 arg3, u8 arg4, u8 arg5, struct37 *arg6, u8 arg7, s32 arg8);
struct260 *func_151491F4(s16 arg0, s8 arg1, s8 arg2, u8 arg3, u8 arg4, s32 arg5, u8 arg6, s32 arg7);
void func_15149318(struct260 *arg0);
void func_1514933C(struct260 *arg0);
void func_15149368(struct260 *arg0);
void func_15149394(struct260 *arg0);
void func_151493E4(struct260 *arg0);
void func_15149434(struct260 *arg0, s32 arg1, u8 arg2);
s32  func_15149490(s32 arg0, struct260 *arg1, s16 arg2);
void func_151494E0(s32 arg0, u8 arg1);
void func_15149514(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_15165F70(void);
void node_destroy(struct102 *arg0);
void node_delete(struct102 *arg0);
void node_retire(struct102 *arg0);
void node_unlink_free(struct102 *arg0);
void func_1519EF70(struct127 *arg0, s32 arg1, s32 arg2);

void impact_tint_red(struct218 *arg0);
void impact_tint_yellow(struct218 *arg0);
void impact_tint_red_green_a(struct218 *arg0);
void impact_tint_red_green_b(struct218 *arg0);
void impact_tint_red_green_c(struct218 *arg0);
void impact_tint_white(struct218 *arg0);
void impact_tint_green_fixed(struct218 *arg0);
void impact_tint_green(struct218 *arg0);
void impact_tint_brown(struct218 *arg0);
void impact_tint_cyan(struct218 *arg0);
void impact_tint_magenta(struct218 *arg0);
void impact_spawn_debris_up(struct17 *arg0, s32 arg1, u8 *arg2, u8 arg3, s32 arg4);
void func_151F0080(f32 arg0[4][4], s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_151F00E0(f32 arg0[4][4], f32 arg1[4][4], f32 arg2[4][4]);

void func_16000000(void);
s32  func_16000028(void);
void func_16000058(void);
s32  func_16000224(void);
void func_16000304(void);
void func_1600030C(void);
void func_16000314(void);
s32  func_16000384(void);
void func_16000424(struct118 *arg0);
void func_160012B0(s32 arg0, u8 *arg1);
void func_16001338(u8 arg0, u8 arg1, u8 arg2);
s32  func_160016F4(s32 arg0);
s32  debug_si_device_busy();
s32  debug_si_raw_start_dma(s32 direction, void *dramAddr);
void debug_stub(void);
s32  debug_float_is_denorm_or_nan(f32 arg0);
void debug_stub_4args(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
u8*  debug_memcpy(u8 *arg0, u8 *arg1, u32 arg2);
s32  debug_sprintf_put(u8 *arg0, u8 *arg1, u32 arg2);


/* non-matching */

void func_10001194(s32 arg0);
void func_10001420(void);
void func_100014C4(s32 arg0);
void func_10001550(void *arg0, u8 arg1);
// s16  func_100019F0(s16 *arg0, struct05 *arg1);
//func_10001AA8
// s32  func_100020D0(s32 *arg0, s32 arg1, s32 *arg2, s32 arg3);
//func_10002718
// s32  func_10002DB0(s32 arg0, s32 arg1);
//func_10002E50
void func_100030A0(OSPri priority, OSMesgQueue *mesgQueue, OSMesg *arg2, s32 arg3);
struct00* func_10003220(struct00 *arg0);
void func_10003330(struct00 *arg0);
//func_100034E0
//func_10003658
// void func_100038C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
// void func_100038E0(void);
void func_10003920(void);
// void func_10003BD0(void);
//func_10003ACC
s32 func_10003C6C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
//func_10004074
void func_100043B4(s32 *arg0, u32 arg1);
//func_100046E4
void func_1000480C(s32 devAddr, void *dramAddr, u32 size);
void func_100049E0(s32 arg0);
//func_10004DB0
void func_100050A0(OSMesgQueue *arg0);
void func_100052A0(s32 arg0);
//func_10005570
//func_100056A0
//func_100057E0
//func_10005948
//func_10005AB0
void func_10005B04(s32 arg0);
//func_10005BE0
//func_10005C2C
void func_1000709C(void);
//func_10007C74
//func_10007CC4
//func_10007D28
//func_10007DA0
//func_10007DAC
//func_10008120
//func_10008180
//func_10008B60
//func_10008BC0
//func_10008C04
void func_10008C6C(u8 arg0, u8 arg1);
//func_10008CE8
//func_10008F90
void func_10009400(s32 arg0);
//func_100095A0
s32 func_100097CC(u32 arg0, s32 arg1, s32 arg2);
//func_100099BC
void func_10009BE4(struct54 *arg0);
s32 func_10009CBC(void *arg0, s32 arg1);
s32  func_10009FFC(void);
//func_1000A03C
//func_1000A348
//func_1000A420
//func_1000A750
//func_1000B060
struct151 *func_1000B1FC(s32 arg0);
//func_1000B294
//func_1000B2F4
//func_1000B3D4
//func_1000B548
//func_1000B638
//func_1000B8B8
//func_1000BAFC
//func_1000BCBC
//func_1000BF60
//func_1000C350
s32 func_1000C530(s32, u8, f32, f32, f32);
//func_1000C7E8
//func_1000C934
//func_1000CA18
//func_1000CAE4
//func_1000CBF0
//func_1000CC54
//func_1000CDA0
//func_1000CEAC
//func_1000D2F8
void func_1000D758(f32 arg0, f32 arg1, s32 arg2);
//func_1000D96C
//func_1000DE1C
//func_1000DEC4
void func_1000DF68(s32 arg0, s32 arg1, s32 arg2);
//func_1000E134
//func_1000E17C
//func_1000E2F4
s32 func_1000E46C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_1000E588(s32 arg0, s32 arg1, s32 arg2);
//func_1000E654
//func_1000E7A0
//func_1000E8C4
//func_1000E8F0
//func_1000E934
//func_1000EC24
//func_1000ECCC
s32  func_1000EDA0(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u16 *arg6);
s32  func_1000EE70(void *arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4, void *arg5);
//func_1000EFB4
//func_1000F1A8
//func_1000F44C
//func_1000F4D8
//func_1000F568
//func_1000F6B8
void func_1000F85C(u16 arg0, s16 arg1, s32 arg2);
void func_1000F91C(u16 arg0, u16 arg1, s16 arg2, u8 arg3, s32 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9);
u16  func_1000FA64(u16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4, u16 arg5, s16 arg6, s32 arg7, void *arg8, s32 arg9, s32 argA, s32 argB);
//func_1000FC18
//func_1000FD38
//func_1000FDF4
//func_1000FE88
//func_1000FEF0
s32  func_1000FF90(s32 arg0, s32 arg1, s32 arg2);
//func_1001001C
//func_100100E0
u16 func_10010154(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4);
u16 func_10010344(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4);
//func_10010558
void func_10010630(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4);
//func_1001091C
u16  func_10010BE8(u16 arg0, s32 arg1, u16 arg2, u8 arg3, s16 arg4, u8 arg5, u8 arg6);
//func_10010E78
#ifdef NON_MATCHING
u16 func_10010F88(s32 arg0, u16 arg1, s16 arg2, u8 arg3, s32 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9);
#else
void func_10010F88(s32 arg0, u16 arg1, s16 arg2, u8 arg3, s32 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9);
#endif
//func_10010FFC
//func_10011310
s32 func_100114D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 *arg6, s32 *arg7, s32 *arg8);
//func_10011624
//func_10011BB8
//func_10011EB8
//func_10012020
//func_1001263C
//func_100126E8
// void func_10017870(u8 arg0);
void func_100186DC(void *arg0, void *arg1);
void func_10018790(void *arg0, s32 arg1, u32 arg2, u32 arg3);
// void func_10019D98(struct26 *arg0, u8 arg1);
// void func_1001A030(struct26 *arg0, s32 arg1, s32 arg2, u32 arg3);
// void func_1001A508(struct26 *arg0, struct25 *arg1, s32 arg2, s32 arg3);
//func_1001AAE0
//func_1001ADA4
//func_1001AFEC
//func_1001B07C
//func_1001B200
// s32  func_1001B310(void *arg0, void *arg1);
// u8   func_1001B450(void *arg0, void *arg1);
Acmd *func_1001E530(s32 arg0, Acmd *arg1, s32 arg2);
//func_1019EA88
//func_1019EAB0
//func_1019EAE0
//func_1019ECAC
//func_1019ED8C
//func_1019ED94
//func_1019ED9C
//func_1019EE0C
//func_1019EEAC
//func_1019F018
//func_1019F154
//func_1019F214
//func_1019F4E4
//func_1019F59C
//func_1019FA14
//func_1019FACC
//func_1019FD38
//func_1019FDC0
//func_1019FE18
//func_1019FF78
//func_101A0094
//func_101A0100
//func_101A017C
//func_101A0188
//func_101A02B8
//func_101A0344
//func_101A040C
//func_101A0430
//func_101A04EC
//func_101A04F4
//func_101A0538
void func_1001C224(void *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_1001CF38(struct139 *arg0, f32 arg1);

u16 *func_15001DE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void level_lights_stub(s16 arg0);

s32  render_set_scissor(s32 arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
s32  asset_load_ptr(s32 *, s32, ...);
struct126 *func_1503195C(struct127 *, s32, s32);
void dl_validate_list(void *arg0, u32 arg1, s32 arg2);
#ifdef NON_MATCHING
s32 ring_buffer_put_record(struct105 *arg0, u8 *arg1, s32 arg2); /* P98: the asm reads a1 / a2 (callback args left in place by func_10012560) */
#else
s32 ring_buffer_put_record(struct105*arg0);
#endif
f32  func_15047C00(f32 arg0);
f32  func_15047D60(f32 arg0);
f32  math_asinf_table(f32 arg0);
f32  math_asinf(f32 arg0);
f32  vec3_heading_deg(struct17 *arg0);
void func_15049688(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5);
void obj_update_move_anim(struct127 *arg0, f32 arg1);
void obj_update_floor(struct127 *, f32);
void vec_from_yaw_pitch(u16 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5);
f32  obj_dist_3d(struct127 *arg0, struct127 *arg1);
void obj_land_on_floor(struct127 *arg0, f32 arg1);
void obj_start_anim(struct127 *arg0, u16 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6);
u32  obj_find_reaction_row(s32, struct127*);
#ifdef NON_MATCHING
void obj_hit_reaction_advance(u8, struct127*); /* P209: the asm ignores a0 (home slot only) and returns nothing */
#else
f32 obj_hit_reaction_advance(u8, struct127*);
#endif
struct127* obj_find_by_id(s32);
void obj_sfx_play_attached(s32 arg0, struct127 *arg1, u16 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void obj_remove(struct127 *arg0, s32 arg1);
void obj_fade_command(struct127*, u8, u8, u8, u8);
void obj_set_inner_extent_width(struct127 *arg0, f32 arg1);
void obj_set_inner_extent_height(struct127 *arg0, f32 arg1);
s32 camera_object_spawn(f32, f32, f32, f32, u8, s32, f32, f32, s32, s32, s32);
struct127 *obj_find_child_nth(struct127 *, s32);
void aiscript_set_flags_fc(void);
s32  func_15081574(s32, f32, f32, s32, s32, s32);
s32 func_15083568(struct127*, s32, f32, s32);
s32  func_15083E0C(u8);
struct127 *func_15083E90(u8);
void func_15085710(s16, s16, s32);
s32  func_150859AC(s16 arg0, s32 arg1); // a guess
void func_1508B20C(f32, f32, f32, f32);
s32 func_150A29C8(s32, s32);
void mtxf_scale(f32 mtx[4][4], s32 x, s32 y, s32 z);
void mtxf_rotate_xyz_deg(f32 mtx[4][4], f32 arg1, f32 arg2, f32 arg3);
void func_150A9B0C(f32 mtx[4][4], f32, f32, f32, f32, f32, f32);
void func_150AD770(void);
f32  func_150AD780(f32);
f32  func_150AD78C(f32);
f32  func_150AD900(f32 *arg0, f32 *arg1);
f32  func_150AD930(f32 *arg0);
s32  random_int(void);
f32  random_float(void);
void beam_effect_spawn_attached_ex(struct127*, u8, s16, s32, f32, f32, f32, f32, f32, f32, s16, s16, u16, f32, f32, u8, f32);
void world_obj_hit_activate(s32 arg0, s32 arg1);
void func_1510B32C(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_1510B958(s32 arg0);
s32  func_1510B9D0(s32 arg0, s16 arg1);
s32  zone_tree_find_leaf(s32 arg0, s32 arg1);
s32  camera_push_mode(struct108 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32  camera_pop_mode(struct108 *arg0, s32 arg1);
void camera_exit_aim_mode(struct108 *arg0);
s32 camera_shake_start(struct108*, s32, s32);
struct210 *sprite_fx_spawn(struct210 *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6, struct167 *arg7, s32 arg8, u8 arg9, s32 argA);
void *effect3d_spawn_full(void *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7, s32 arg8, s32 arg9, u8 argA, s32 argB);
s32  effect3d_build_axes(struct211 *arg0, s16 arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5, u8 arg6);
void  sprite_quad_place(struct210 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6);
s32 sprite_quad_place_cam(s32, s32, s32, f32, f32, f32, f32, f32, u8);
f32  angle_byte_cos(u8);
f32  func_15144598(struct_eu_15144598 *arg0);
f32  func_1514462C(struct_eu_15144598 *arg0);
f32  func_15144B68(f32 arg0);
#ifdef NON_MATCHING
s32 func_1514D3B0(s32, s16, s32, s32); /* P218: the asm passes the event values (a2 / a3) through unmasked */
#else
s32 func_1514D3B0(s32, s16, u8, u8);   /* the s32 version changes the C callers' default codegen */
#endif
s32  func_1515D6D0(s32 arg0, s32 arg1);
void func_1515D4D4(s32, s32, s32, u8);
void node_broadcast_types(void *, s32, s32, u8);
void node_broadcast_type(s32, s32, u8);
s32 node_handle_link_message(s32, u8, s32, s32, s32);
void func_15174690(s32, s32, s32, s32, s32, s32, s32, u8, s32);
void func_15177410(u8 arg0, u8 arg1, s16 arg2, s16 arg3, s16 arg4, f32 arg5, u16 arg6, f32 arg7, s8 arg8, s8 arg9, u8 argA, u8 argB, u8 argC, u8 argD, u8 argE, u8 argF);
s32  func_1517EFAC(s32 arg0);
void func_15178E14(u8);
s32  func_15187EC0(s32 arg0, f32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
void *func_15195AA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void func_151B8DB0(s32 arg0, u8 arg1, u8 arg2, u8 arg3);
void func_151D5404(struct17*, f32, f32, f32, s16, s16, s32, s32);
void func_151D5714(struct127*, f32*, f32*, u8, f32, u8, s32);
s32 impact_debris_spawn(u8 arg0, f32 arg1, u8 arg2, s32 arg3, struct17 *arg4, s16 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, s32 argA);
s32 impact_smoke_puff_spawn(u8 arg0, f32 arg1, f32 arg2, u8 arg3, s16 arg4, s32 arg5, void *arg6, s32 arg7, s32 arg8);
void impact_dust_particle_spawn(u8 arg0, f32 arg1, s16 arg2, s32 arg3, void *arg4, u8 arg5, s32 arg6);
void func_151EF954(f32 arg0[4][4], f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
s32 func_151F3C4C(s32, void *, s32, s32);
void func_151FA130(void);
void func_1019EA88(void);

/* EU: new decompilation */
void node_set_type(s32 arg0, s32 arg1);
void node_broadcast_range(s32 arg0, s32 arg1, s32 arg2, u8 arg3);
void func_151BCB54(void *arg0, void *arg1, u8 arg2);
void impact_burst(s32 arg0, u8 arg1, s32 arg2);
void func_15166F10(s32 arg0, s32 arg1, s32 arg2, f32 arg3, u8 arg4, s32 arg5);
void func_1517E6A4(f32 *arg0, structEU_16DC80 *arg1);
void effect_set_orbit_pos(structEU_16DC80 *arg0, void *arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5);
void swing_lamp_handle_event(u8 *arg0, s32 arg1, u8 arg2);
void func_151BAA18(u8 *arg0, s32 arg1, u8 arg2);
#ifdef NON_MATCHING
s32 func_150AB278(struct_eu_bytes24 arg0);
#else
void func_150AB278(struct_eu_bytes24 arg0);
#endif
void func_160006CC(struct118 *arg0);
void func_16000590(struct118 *arg0);
s32  asset_rec_read_cached(u8 *arg0, s32 arg1, s32 *arg2);
void node_list_insert(struct_eu_node *arg0, s32 arg1);
void node_list_unlink(struct_eu_node *arg0);
s32  func_150A2FCC(); // 3 params (u32, s32, s32 *); the caller in game_16EE20 passes a 4th
s32 func_150027F8(Gfx *arg0);
u16  func_10010E78(u16 arg0, s32 arg1, u16 arg2, s16 arg3, u8 arg4, s32 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, s16 argA);
#ifdef NON_MATCHING
void objev_start_anim_cmd(void);
#else
s32 objev_start_anim_cmd(void);
#endif
void ground_explosion(struct127 *arg0, struct127 *arg1, f32 *arg2, u8 arg3, s32 arg4, u8 arg5, s32 arg6);
void *node_alloc(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5);
s32  func_151452C4(struct17 *arg0, struct17 *arg1, struct17 *arg2, f32 arg3, s32 arg4, s32 arg5, f32 *arg6, f32 *arg7);
void func_150A7E40(f32 mf[4][4], f32 x, f32 y, f32 z, f32 *outX, f32 *outY, f32 *outZ);
void func_151B6150(struct127 *arg0, struct127 *arg1);
s32  func_1514563C(struct17 *arg0, struct17 *arg1, struct17 *arg2, struct17 *arg3, f32 *arg4);
struct225 *light_create_with_ctrl(Header *header, Header2 *header2, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, u8 arg7, s32 offset, u8 arg9, s32 argA);
s32 func_151D8E18(structEU_151D8E18 *arg0, s32 arg1, u8 arg2, s32 arg3);
s32  held_obj_byte7d_get(void);
void object_beam_fire(struct127 *arg0, u8 arg1, s32 arg2);
void object_bolt_fire(struct127 *arg0, u8 arg1, s32 arg2);
void character_smoke_puff(struct127 *arg0, u8 arg1, s32 arg2);
s32 point_emitter_spawn(struct_eu_EF410 *arg0, s32 arg1, u8 arg2, s32 arg3);
void *func_15147FF0(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 arg9, s32 argA);
void func_15143134(void *arg0, void *arg1, void *arg2);
void func_151C384C(void *arg0, u8 arg1, s32 arg2);
void impact_blast_spawn_small(void *arg0, void *arg1, u8 arg2, u8 arg3, s32 arg4);
void func_15154488(struct_eu_15154488 *arg0, struct17 *arg1, s32 arg2, u8 arg3, s32 arg4);
void obj_start_hit_reaction(struct127 *arg0, s32 arg1, u8 arg2);
void func_15002560(struct_eu_qnode *arg0, struct_eu_qnode *arg1);
s32 func_1514F250(struct_eu_link *arg0, s16 arg1, struct_eu_link **arg2);
s32 func_1514F18C(void *arg0, struct127 *arg1, s16 arg2);
void obj_interaction_attach_timed(struct127 *arg0, s32 arg1);
s32 impact_dust_cloud_spawn(void *arg0, f32 *arg1, u8 arg2, f32 arg3, s16 arg4, u8 arg5, f32 arg6, u8 arg7, f32 arg8, f32 arg9, u8 argA, s32 argB, u8 argC, u8 argD, u8 argE, s32 argF);
s32  func_1000ECCC(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u16 *arg6);
#ifdef NON_MATCHING
s32 func_151BEE00(f32 *arg0, f32 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6); /* P98: asm reloads a1 with lwc1 */
#else
s32 func_151BEE00(f32 *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6);
#endif
void func_151A9940(u8 arg0, u8 arg1, void *arg2, s32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, s32 arg8);
void func_1000DEC4(void);
s32  asset_dma_into(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_15194978(struct127 *arg0, struct127 *arg1);
void func_15152700(void *arg0, void *arg1, void *arg2, s32 arg3, f32 arg4, u8 arg5, u8 arg6, s32 arg7);
f32 *func_15144B34(s32 arg0);
s32 func_151DD4A0(OSMesgQueue *mq, u8 address, void *buffer, s32 nbytes); // osEepromLongWrite
s32 func_151DD950(OSMesgQueue *mq, u8 address, void *buffer, s32 nbytes); // osEepromLongRead
s32 func_151DDA90(OSMesgQueue *mq, u8 address, u8 *buffer); // osEepromWrite
s32 impact_dust_cloud_wobble(struct_eu_2062D0_d *arg0, s32 arg1);
struct_eu_C8950_blk *event_block_relocate(struct_eu_C8950_blk *arg0);
void func_1514C9E0(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, u8 arg7, s32 arg8, f32 arg9, s32 argA, u8 argB);
void func_15001A08(void);
void attach_fx_asset_release(s32 arg0);
void func_150B1138(u8 *arg0, u8 arg1, s32 arg2);
void func_1519D320(s32 arg0, f32 arg1, s32 arg2);
f32  scenery_swing_angle_step(f32 *arg0, f32 arg1);
f32  scenery_pendulum_angle_step(f32 *arg0, f32 arg1);
void func_150D27E4(s32 arg0);
void func_15145740(struct127 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4);
void func_1503EE68(s32 arg0, f32 arg1, f32 arg2, s32 arg3);
void func_15155C9C(void *arg0, u8 arg1);
void func_151D43B4(s32 arg0, s32 arg1, void *arg2, u8 arg3, f32 arg4);
void func_1507EB4C(struct127 *arg0, s32 arg1);
struct127 *obj_find_by_spawn();
s32 func_15095EA0(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
void func_1518B818(s32 arg0, f32 arg1, f32 arg2, s32 arg3, u16 arg4, s32 arg5, u8 arg6);
s32 attack_spawn_at_point(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, u16 arg5, s32 arg6, s32 arg7);
void func_151C40BC(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, u8 arg5, u8 arg6, u8 arg7);
void func_1507F298(u8 arg0, u8 *arg1);
#ifdef NON_MATCHING
/* P221: NM only (game_981E0's objfx_fc438 called it undeclared: implicit int, a wasm signature mismatch) */
void gunfire_burst_spawn(struct127 *arg0, struct127 *arg1, u8 arg2, u8 arg3);
#endif
/* EU: end new */
#endif
