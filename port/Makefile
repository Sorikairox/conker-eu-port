# Browser (wasm32) build of the Conker source port. Run inside the conker-emsdk container:
#   port/web/run.sh build            (= make -C port all)
# Targets: demo (scheduler demo), objs (compile + census of conker/src_eu), game, web, clean.
B      := build
WEB    := $(B)/web
GEN    := stubs
LIBDIR := $(shell em-config CACHE 2>/dev/null)/sysroot/lib/wasm32-emscripten

ULTRA_CFLAGS := -O2 -g0 -std=gnu11 -I../conker/include/2.0L -D_LANGUAGE_C \
                -D_MIPS_SZLONG=32 -D_MIPS_SZINT=32 -DF3DEX_GBI_2 -DPORT -Wall -Wno-unused-parameter
# same flags as port/tools/census.py (build mode) for TUs that include the game headers
GAME_CFLAGS  := -O1 -g0 -std=gnu89 -nostdinc -fno-builtin -fno-strict-aliasing -fwrapv -fsigned-char \
                -include ultra/port_prefix.h -DPORT -D_LANGUAGE_C -D_FINALROM -DF3DEX_GBI_2 \
                -D_MIPS_SZLONG=32 -D_MIPS_SZINT=32 -I../conker -I../conker/include -I../conker/include/2.0L \
                -I../conker/include/2.0L/PR -I../conker/include/libc -Wno-unknown-pragmas \
                -Wno-error=int-conversion -Wno-error=incompatible-pointer-types -Wno-error=implicit-int \
                -Wno-error=implicit-function-declaration

LINK_COMMON := -sUSE_SDL=2 -sASYNCIFY -sASYNCIFY_STACK_SIZE=65536 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 \
               -sALLOW_MEMORY_GROWTH=1 -sINITIAL_MEMORY=128MB -sSTACK_SIZE=1MB -sMODULARIZE=1 -sINVOKE_RUN=0 -sEXIT_RUNTIME=0 \
               -sEXPORTED_FUNCTIONS=_main,_malloc,_free,_port_set_rom,_port_dump_threads,_port_dump_stubs,_port_gfx_demo_test \
               -sEXPORTED_RUNTIME_METHODS=HEAPU8,HEAP32,callMain,stringToNewUTF8 -sENVIRONMENT=web,node --profiling-funcs

ULTRA_SRC := ultra/pc_sched.c ultra/pc_os.c ultra/pc_pif.c ultra/pc_video.c ultra/pc_mem.c ultra/pc_icall.c ultra/pc_gu.c ultra/pc_libc.c ultra/pc_tables.c
ULTRA_OBJ := $(patsubst ultra/%.c,$(B)/ultra/%.o,$(ULTRA_SRC))
# P327: -MMD depfiles so a header edit (e.g. port_options.h, included by pc_os.c) rebuilds the PC-side objects using it
ULTRA_CFLAGS += -MMD -MP
# F3DEX2 interpreter + WebGL2 backend + ROM asset viewer (docs/port/sessions/P6.md)
GFX_SRC := gfx/gfx_f3dex2.c gfx/gfx_demo.c gfx/p49_walk.c gfx/p58_model.c gfx/p61_checks.c gfx/p66_checks.c gfx/p69_checks.c gfx/p75_checks.c gfx/p81_checks.c gfx/p84_checks.c gfx/p103_boot.c gfx/p144_hits.c gfx/p165_hits.c gfx/p171_tb.c gfx/p174_ev.c gfx/p202_fx.c gfx/p205_obj.c gfx/p326_probe.c gfx/p223_hit.c gfx/p268_nodes.c
GFX_OBJ := $(patsubst gfx/%.c,$(B)/gfx/%.o,$(GFX_SRC))
# audio HLE (n_audio ABI interpreter) + SDL output (docs/port/sessions/P9.md)
AUD_SRC := audio/aud_abi.c audio/aud_out.c
AUD_OBJ := $(patsubst audio/%.c,$(B)/audio/%.o,$(AUD_SRC))

.PHONY: all demo objs game web clean
all: demo game web

$(B)/ultra/%.o: ultra/%.c ultra/pc_ultra.h ultra/pc_mem.h ultra/pc_icall.h
	@mkdir -p $(@D)
	emcc $(ULTRA_CFLAGS) -c $< -o $@

$(B)/gfx/%.o: gfx/%.c gfx/gfx.h ultra/pc_mem.h
	@mkdir -p $(@D)
	emcc $(ULTRA_CFLAGS) -c $< -o $@

$(B)/audio/%.o: audio/%.c audio/aud.h ultra/pc_mem.h
	@mkdir -p $(@D)
	emcc $(ULTRA_CFLAGS) -sUSE_SDL=2 -c $< -o $@

# ---- scheduler demo
$(B)/demo.o: sched_demo/demo.c ultra/pc_ultra.h
	@mkdir -p $(@D)
	emcc $(ULTRA_CFLAGS) -c $< -o $@
$(B)/demo_stubs.o: sched_demo/demo_stubs.c ultra/pc_mem.h
	emcc $(ULTRA_CFLAGS) -c $< -o $@

demo: $(WEB)/sched_demo.js
$(WEB)/sched_demo.js: $(B)/demo.o $(B)/demo_stubs.o $(ULTRA_OBJ) $(GFX_OBJ) $(AUD_OBJ)
	@mkdir -p $(@D)
	emcc $^ -o $@ $(LINK_COMMON) -sEXPORT_NAME=createSchedDemo

# ---- game: every src_eu TU that clang accepts + PC libultra + boot + generated stubs
objs:
	cd .. && python3 port/tools/census.py

# TUs that still fail under clang (see census) are left out; their functions get stubs.
# Game TUs (and port/boot) are compiled through the vbe IR pass (virtual big-endian memory,
# docs/port/MEMORY.md): port/tools/vbe_build.py -> $(B)/vobj/*.o
GAME_OBJS = $(shell awk -F'\t' 'FNR==NR {if ($$0 !~ /^\#/) ex[$$1]=1; next} FNR>1 && $$4=="ok" && !($$1 in ex) {gsub("/","__",$$1); print "$(B)/vobj/" $$1 ".o"}' exclude.txt $(B)/census/files.tsv 2>/dev/null)
# GLOBAL_BASE=256MB (P8, docs/port/MEMORY.md "Address space and RSP segments"): wasm addresses below
# 0x10000000 are never data, so (1) 0..16 MB is a "null zone" that absorbs writes through the NULL
# pointers that asm stubs return (port_mem_null_report; on the N64 these would TLB-miss) and (2) the
# renderer can tell RSP segment addresses (0x01..0x0F << 24) from wasm pointers exactly. The untouched
# zone costs address space only (pages are committed on first write); INITIAL_MEMORY covers it +
# ~10 MB data + the 64 MB ROM copy + heap.
BOOT_SRC  := boot/game_main.c boot/game_entry.c boot/game_icalltest.c boot/pc_overrides.c boot/p69_pcold.c boot/sched_test.c boot/gu_test.c audio/aud_test.c audio/mp3_pc.c
BOOT_OBJS := $(patsubst %.c,$(B)/vobj/port__%.o,$(notdir $(BOOT_SRC)))
STUB_OBJS := $(B)/stubs/asm_stubs.o $(B)/stubs/data_stubs.o $(B)/stubs/n64mem_tab.o $(B)/stubs/n64mem_labels.o $(B)/stubs/icall_tab.o

# P328: names and addresses come from the frozen table symbols/symbols.tsv (n64mem.py, gen_stubs.py, icall_gen.py,
# romabs_check.py); nothing here reads the byte-matching build (conker/build, conker/asm, *_auto.txt) any more.
# P327 incremental build: the census (--incremental) and vbe_build.py run on every make but only recompile the TUs
# whose source or included headers changed (content keys, port/tools/depkey.py). files.tsv and vbe.stamp keep their
# mtime when nothing changed (make re-reads mtimes after a recipe), so a no-op build relinks nothing. Before P327 a
# game-C edit needed `run.sh census` (or deleting vbe.stamp) and header edits were missed by the .ll cache.
FORCE:
.PHONY: FORCE
$(B)/vbe.stamp: $(B)/census/files.tsv exclude.txt $(GEN)/memtest_expect.h $(GEN)/gutest_expect.h FORCE
	cd .. && python3 port/tools/vbe_build.py $(addprefix port/,$(BOOT_SRC))
	# P233: D_<small hex> link symbols in NM C must be in vbe.py ROM_ABS / RAM_ALIAS (else zero data stubs)
	cd .. && CONKER_ROOT=$$(pwd) python3 port/tools/romabs_check.py --quiet
	@if [ -e $(B)/vbe.dirty ] || [ ! -e $@ ]; then touch $@; rm -f $(B)/vbe.dirty; fi

$(GEN)/memtest_expect.h: tools/n64mem.py
	cd .. && python3 port/tools/n64mem.py port/$(GEN)

$(B)/stubs/%.o: $(GEN)/%.c ultra/pc_mem.h ultra/pc_icall.h
	@mkdir -p $(@D)
	emcc -O1 -g0 -Wno-incompatible-library-redeclaration -c $< -o $@
$(B)/stubs/n64mem_labels.o: $(GEN)/n64mem_labels.s
	@mkdir -p $(@D)
	emcc -c $< -o $@

$(GEN)/asm_stubs.c $(GEN)/data_stubs.c $(GEN)/n64mem_tab.c $(GEN)/n64mem_labels.s &: $(B)/vbe.stamp $(ULTRA_OBJ) $(GFX_OBJ) $(AUD_OBJ) tools/gen_stubs.py tools/n64mem.py symbols/symbols.tsv symbols/global_asm.tsv
	cd .. && python3 port/tools/gen_stubs.py port/$(GEN) $(LIBDIR) $(addprefix port/,$(GAME_OBJS) $(BOOT_OBJS) $(ULTRA_OBJ) $(GFX_OBJ) $(AUD_OBJ))

# indirect calls: signature table of the non-vbe objects + mismatch dispatcher (tools/icall.py)
$(GEN)/icall_tab.c: $(B)/vbe.stamp $(B)/stubs/asm_stubs.o $(B)/stubs/n64mem_tab.o $(ULTRA_OBJ) $(GFX_OBJ) $(AUD_OBJ) tools/icall_gen.py tools/icall.py symbols/symbols.tsv
	cd .. && python3 port/tools/icall_gen.py port/$@ $(addprefix port/,$(B)/stubs/asm_stubs.o $(B)/stubs/n64mem_tab.o $(ULTRA_OBJ) $(GFX_OBJ) $(AUD_OBJ))

$(B)/census/files.tsv: FORCE
	@mkdir -p $(@D)
	cd .. && python3 port/tools/census.py --incremental

game: $(WEB)/conker.js
$(WEB)/conker.js: $(B)/vbe.stamp $(ULTRA_OBJ) $(GFX_OBJ) $(AUD_OBJ) $(STUB_OBJS)
	@mkdir -p $(@D)
	emcc $(GAME_OBJS) $(BOOT_OBJS) $(ULTRA_OBJ) $(GFX_OBJ) $(AUD_OBJ) $(STUB_OBJS) -o $@ \
	  $(LINK_COMMON) -sGLOBAL_BASE=256MB -sINITIAL_MEMORY=352MB -sSTACK_OVERFLOW_CHECK=0 -sEXPORT_NAME=createConker -sEXPORTED_FUNCTIONS=_main,_malloc,_free,_port_set_rom,_port_dump_threads,_port_dump_stubs,_port_gfx_demo_test,_port_audio_test,_port_voice_test,_port_audio_prepare,_port_pad_state,_port_eeprom_ptr,_port_eeprom_size,_port_eep_test,_port_set_paused,_port_skip_progress,_port_set_option -Wl,--error-limit=0 -Wl,--wrap=level_dl_visibility_filter -Wl,--wrap=rzip_inflate -Wl,--wrap=texture_cache_lookup -Wl,--wrap=level_load_models -Wl,--wrap=camera_build_view_matrix -Wl,--wrap=shadow_draw_all -Wl,--wrap=objects_run_state_handlers -Wl,--wrap=camera_view_test_sphere -Wl,--wrap=objects_draw_pass -Wl,--wrap=texscroll_update -Wl,--wrap=obj_state_walk -Wl,--wrap=obj_apply_gravity -Wl,--wrap=objects_update_all -Wl,--wrap=collision_find_floor_no_fallback -Wl,--wrap=obj_ctrl_floor_contact -Wl,--wrap=floor_collect_level_tris -Wl,--wrap=floor_collect_world_obj_tris -Wl,--wrap=floor_collect_record_tris -Wl,--wrap=func_150A4ED4 -Wl,--wrap=model_load -Wl,--wrap=obj_adjust_list_build -Wl,--wrap=anim_eval_joint_matrices -Wl,--wrap=player_lose_life -Wl,--wrap=game_request_transition -Wl,--wrap=obj_contact_pass -Wl,--wrap=music_play_song -Wl,--wrap=music_stop_song -Wl,--wrap=music_post_event_request -Wl,--wrap=music_clear_event_flag1 -Wl,--wrap=anim_advance_frame -Wl,--wrap=obj_start_anim -Wl,--wrap=obj_jump_swim_glide_update -Wl,--wrap=player_stat_modify -Wl,--wrap=attachment_update_all -Wl,--wrap=look_aim_head_eyes -Wl,--wrap=model_build_collision_tables -Wl,--wrap=attack_hit_test -Wl,--wrap=debris_burst_destroyed_object -Wl,--wrap=face_anim_start -Wl,--wrap=collision_floor_all -Wl,--wrap=heap_free -Wl,--wrap=asset_rec_fetch_block -Wl,--wrap=world_objects_at_point -Wl,--wrap=floor_triangle_slope -Wl,--wrap=look_frame_cb_current -Wl,--wrap=debris_follow_owner_update -Wl,--wrap=level_setup_sky_backdrop -Wl,--wrap=tail_update_conker -Wl,--wrap=breakable_update_slot -Wl,--wrap=attachment_draw_all_for_player -Wl,--wrap=attachment_draw_for_object -Wl,--wrap=game_mode_frame_step -Wl,--wrap=camera_update_target_height -Wl,--wrap=impact_spark_spawn -Wl,--wrap=trail_step -Wl,--wrap=trail_draw -Wl,--wrap=level_start_music -Wl,--wrap=event_prereqs_met -Wl,--wrap=event_start_level_events -Wl,--wrap=event_start -Wl,--wrap=cutscene_scene_load -Wl,--wrap=obj_model_refs_release -Wl,--wrap=obj_remove -Wl,--wrap=reflect_queue_reset -Wl,--wrap=camera_matrices_refresh_all -Wl,--wrap=collision_select_area -Wl,--wrap=world_records_flag_active -Wl,--wrap=timedfx_update_all -Wl,--wrap=scene_event_track_pass -Wl,--wrap=cutscene_camera_track_pass -Wl,--wrap=cutscene_apply_cameras -Wl,--wrap=cutscene_check_finished -Wl,--wrap=camera_update_all -Wl,--wrap=objects_update_tank_views -Wl,--wrap=player_zone_update -Wl,--wrap=level_update_frame -Wl,--wrap=frame_hook_nop_1501c860 -Wl,--wrap=frame_hook_nop_1511fc20 -Wl,--wrap=afterimage_list_update -Wl,--wrap=objects_update_blob_shadows -Wl,--wrap=world_records_update_shadows -Wl,--wrap=fog_apply_level_default -Wl,--wrap=obj_setup_run -Wl,--wrap=obj_find_by_setup_id -Wl,--wrap=obj_slot_by_setup_id -Wl,--wrap=menu_reset_and_enter -Wl,--wrap=menu_sprites_load -Wl,--wrap=screen_fade_start -Wl,--wrap=texture_resolve_dl_ids -Wl,--wrap=asset_load_with_subfiles -Wl,--wrap=setup_entry_spawn -Wl,--wrap=asset_load_into -Wl,--wrap=hud_scope_lens_draw -Wl,--wrap=fb_fx_apply_all -Wl,--wrap=fb_lens_warp_draw -Wl,--wrap=fb_zoom_fx_apply -Wl,--wrap=fb_fx_gray_callback -Wl,--wrap=particle_sprite_update -Wl,--wrap=spark_burst_update -Wl,--wrap=pool_slot_release -Wl,--wrap=node_destroy -Wl,--wrap=star_field_generate -Wl,--wrap=spawn_region_random_point -Wl,--wrap=sprite_draw_rect -Wl,--wrap=image_draw_tiled -Wl,--wrap=world_to_screen -Wl,--wrap=camera_pivot_follow_update -Wl,--wrap=pickup_burst_spawn -Wl,--wrap=life_pickup_spawn -Wl,--wrap=obj_death_resolve -Wl,--wrap=world_object_sound_play -Wl,--wrap=life_pickup_ring_spawn -Wl,--wrap=sprite_screen_rect -Wl,--wrap=vec3_make_basis -Wl,--wrap=smoke_wobble_step -Wl,--wrap=model_node_points_to_world -Wl,--wrap=world_object_rotate_point -Wl,--wrap=effect3d_update -Wl,--wrap=effect3d_draw -Wl,--wrap=particle_draw_sprite -Wl,--wrap=player_morph_blend -Wl,--wrap=mtxf_transform_point_w -Wl,--wrap=camera_world_to_screen -Wl,--wrap=water_drop_splash_update -Wl,--wrap=emit_particle_burst_req -Wl,--wrap=shadow_light_projection -Wl,--wrap=char_fx_init -Wl,--wrap=actor_sound_play -Wl,--wrap=actor_sound_play2 -Wl,--wrap=sound_pick_variant -Wl,--wrap=player_move_animation -Wl,--wrap=player_context_action -Wl,--wrap=text_box_update -Wl,--wrap=text_box_open -Wl,--wrap=event_native_query -Wl,--wrap=event_native_action -Wl,--wrap=objects_update_visibility -Wl,--wrap=event_vm_run -Wl,--wrap=obj_floor_push_turn -Wl,--wrap=landing_dust_burst -Wl,--wrap=character_effect_attach -Wl,--wrap=effect3d_spawn_default -Wl,--wrap=obj_receive_hit -Wl,--wrap=rail_track_update -Wl,--wrap=ripple_spawn_flat -Wl,--wrap=anim_events_run -Wl,--wrap=node_lists_run_update -Wl,--wrap=node_render_layers_draw -Wl,--wrap=glow_trail_points_update -Wl,--wrap=glow_trail_emit_points -Wl,--wrap=glow_trail_limit_length -Wl,--wrap=game_main_loop 2> $(B)/link_warnings.txt \
	  || (tail -40 $(B)/link_warnings.txt; exit 1)
	@echo "link warnings: $$(grep -c warning $(B)/link_warnings.txt) (port/build/link_warnings.txt)"
	@ls -l $(WEB)/conker.wasm

# ---- page
web: $(WEB)/index.html $(WEB)/main.js
$(WEB)/%: web/%
	@mkdir -p $(@D)
	cp $< $@

clean:
	rm -rf $(B)/obj $(B)/vobj $(B)/ll $(B)/vbe.stamp $(B)/ultra $(B)/gfx $(B)/audio $(B)/stubs $(B)/census $(B)/*.o $(WEB) $(GEN)/asm_stubs.c $(GEN)/data_stubs.c $(GEN)/icall_tab.c

print-objs:
	@echo $(GAME_OBJS)

# P327: header dependencies of the PC-side objects (-MMD); at the end so they never become the default goal
-include $(wildcard $(B)/ultra/*.d $(B)/gfx/*.d $(B)/audio/*.d $(B)/*.d)
