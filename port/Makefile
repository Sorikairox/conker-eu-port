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
                -include ultra/port_prefix.h -DNON_MATCHING -DPORT -D_LANGUAGE_C -D_FINALROM -DF3DEX_GBI_2 \
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
# F3DEX2 interpreter + WebGL2 backend + ROM asset viewer (docs/port/sessions/P6.md)
GFX_SRC := gfx/gfx_f3dex2.c gfx/gfx_demo.c gfx/p49_walk.c gfx/p58_model.c gfx/p61_checks.c gfx/p66_checks.c gfx/p69_checks.c gfx/p75_checks.c gfx/p81_checks.c gfx/p84_checks.c gfx/p103_boot.c gfx/p144_hits.c gfx/p165_hits.c gfx/p171_tb.c gfx/p174_ev.c gfx/p202_fx.c gfx/p205_obj.c gfx/p223_hit.c gfx/p268_nodes.c
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

$(B)/vbe.stamp: $(B)/census/files.tsv exclude.txt tools/vbe.py tools/vbe_build.py tools/sigs.py tools/icall.py $(BOOT_SRC) ultra/pc_mem.h $(GEN)/memtest_expect.h $(GEN)/gutest_expect.h
	cd .. && python3 port/tools/vbe_build.py $(addprefix port/,$(BOOT_SRC))
	# P233: D_<small hex> link symbols in NM C must be in vbe.py ROM_ABS / RAM_ALIAS (else zero data stubs)
	cd .. && CONKER_ROOT=$$(pwd) python3 port/tools/romabs_check.py --quiet
	@touch $@

$(GEN)/memtest_expect.h: tools/n64mem.py
	cd .. && python3 port/tools/n64mem.py port/$(GEN)

$(B)/stubs/%.o: $(GEN)/%.c ultra/pc_mem.h ultra/pc_icall.h
	@mkdir -p $(@D)
	emcc -O1 -g0 -Wno-incompatible-library-redeclaration -c $< -o $@
$(B)/stubs/n64mem_labels.o: $(GEN)/n64mem_labels.s
	@mkdir -p $(@D)
	emcc -c $< -o $@

$(GEN)/asm_stubs.c $(GEN)/data_stubs.c $(GEN)/n64mem_tab.c $(GEN)/n64mem_labels.s &: $(B)/vbe.stamp $(ULTRA_OBJ) $(GFX_OBJ) $(AUD_OBJ) tools/gen_stubs.py tools/n64mem.py
	cd .. && python3 port/tools/gen_stubs.py port/$(GEN) $(LIBDIR) $(addprefix port/,$(GAME_OBJS) $(BOOT_OBJS) $(ULTRA_OBJ) $(GFX_OBJ) $(AUD_OBJ))

# indirect calls: signature table of the non-vbe objects + mismatch dispatcher (tools/icall.py)
$(GEN)/icall_tab.c: $(B)/vbe.stamp $(B)/stubs/asm_stubs.o $(B)/stubs/n64mem_tab.o $(ULTRA_OBJ) $(GFX_OBJ) $(AUD_OBJ) tools/icall_gen.py tools/icall.py
	cd .. && python3 port/tools/icall_gen.py port/$@ $(addprefix port/,$(B)/stubs/asm_stubs.o $(B)/stubs/n64mem_tab.o $(ULTRA_OBJ) $(GFX_OBJ) $(AUD_OBJ))

$(B)/census/files.tsv:
	cd .. && python3 port/tools/census.py

game: $(WEB)/conker.js
$(WEB)/conker.js: $(B)/vbe.stamp $(ULTRA_OBJ) $(GFX_OBJ) $(AUD_OBJ) $(STUB_OBJS)
	@mkdir -p $(@D)
	emcc $(GAME_OBJS) $(BOOT_OBJS) $(ULTRA_OBJ) $(GFX_OBJ) $(AUD_OBJ) $(STUB_OBJS) -o $@ \
	  $(LINK_COMMON) -sGLOBAL_BASE=256MB -sINITIAL_MEMORY=352MB -sSTACK_OVERFLOW_CHECK=0 -sEXPORT_NAME=createConker -sEXPORTED_FUNCTIONS=_main,_malloc,_free,_port_set_rom,_port_dump_threads,_port_dump_stubs,_port_gfx_demo_test,_port_audio_test,_port_voice_test,_port_audio_prepare,_port_pad_state,_port_eeprom_ptr,_port_eeprom_size,_port_eep_test,_port_set_paused,_port_skip_progress -Wl,--error-limit=0 -Wl,--wrap=func_150A5858 -Wl,--wrap=func_10006530 -Wl,--wrap=func_1510D66C -Wl,--wrap=func_150031EC -Wl,--wrap=func_1512C490 -Wl,--wrap=func_15186D04 -Wl,--wrap=func_1504A730 -Wl,--wrap=func_150A6840 -Wl,--wrap=func_1502BDC0 -Wl,--wrap=func_15196560 -Wl,--wrap=func_1504CB98 -Wl,--wrap=func_1505A770 -Wl,--wrap=func_1502C1D4 -Wl,--wrap=func_1510EE3C -Wl,--wrap=func_1505A9AC -Wl,--wrap=func_150A3F50 -Wl,--wrap=func_150A48C0 -Wl,--wrap=func_150A5480 -Wl,--wrap=func_150A4ED4 -Wl,--wrap=func_1503D210 -Wl,--wrap=func_150342D0 -Wl,--wrap=func_150A86B0 -Wl,--wrap=func_1507D4F8 -Wl,--wrap=func_1501C710 -Wl,--wrap=func_1505D6F0 -Wl,--wrap=func_1000D96C -Wl,--wrap=func_1000DE1C -Wl,--wrap=func_1000E7A0 -Wl,--wrap=func_1000E8C4 -Wl,--wrap=func_1507C170 -Wl,--wrap=func_1505E650 -Wl,--wrap=func_1505F298 -Wl,--wrap=func_15085710 -Wl,--wrap=func_15030758 -Wl,--wrap=func_1503AB20 -Wl,--wrap=func_150028BC -Wl,--wrap=func_1505C7D8 -Wl,--wrap=func_150D5F7C -Wl,--wrap=func_1507E7E4 -Wl,--wrap=func_15046C6C -Wl,--wrap=func_10004074 -Wl,--wrap=func_1502AF04 -Wl,--wrap=func_150A69E0 -Wl,--wrap=func_1510E908 -Wl,--wrap=func_15036FD8 -Wl,--wrap=func_150D71D4 -Wl,--wrap=func_15000AD0 -Wl,--wrap=func_1503BCAC -Wl,--wrap=func_1503E238 -Wl,--wrap=func_150310F8 -Wl,--wrap=func_15031284 -Wl,--wrap=func_151E5928 -Wl,--wrap=camera_update_target_height -Wl,--wrap=impact_spark_spawn -Wl,--wrap=func_15148428 -Wl,--wrap=func_151485AC -Wl,--wrap=func_150000B0 -Wl,--wrap=func_1509CBD4 -Wl,--wrap=func_1509B4A0 -Wl,--wrap=func_1509B5AC -Wl,--wrap=func_1501D348 -Wl,--wrap=func_15084814 -Wl,--wrap=func_15060F28 -Wl,--wrap=func_15035210 -Wl,--wrap=func_1510BC10 -Wl,--wrap=func_1510F800 -Wl,--wrap=func_15113700 -Wl,--wrap=func_15044D18 -Wl,--wrap=func_1502457C -Wl,--wrap=func_1501ECA4 -Wl,--wrap=func_15020F6C -Wl,--wrap=func_1501E364 -Wl,--wrap=camera_update_all -Wl,--wrap=func_1504ADD0 -Wl,--wrap=func_151101B4 -Wl,--wrap=func_15174F68 -Wl,--wrap=func_1501C860 -Wl,--wrap=func_1511FC20 -Wl,--wrap=func_151890E4 -Wl,--wrap=func_1502C494 -Wl,--wrap=func_15114208 -Wl,--wrap=func_15173E34 -Wl,--wrap=func_15083568 -Wl,--wrap=func_15083E90 -Wl,--wrap=func_15083FB0 -Wl,--wrap=func_151DECB4 -Wl,--wrap=func_151EE704 -Wl,--wrap=func_1517F3B0 -Wl,--wrap=func_1510D3E0 -Wl,--wrap=func_1502B6BC -Wl,--wrap=func_15082E44 -Wl,--wrap=func_1502B8E0 -Wl,--wrap=func_1518010C -Wl,--wrap=func_15160310 -Wl,--wrap=func_151CB6C0 -Wl,--wrap=func_150CE960 -Wl,--wrap=func_150AFC70 -Wl,--wrap=func_1513095C -Wl,--wrap=func_151A4DEC -Wl,--wrap=func_150C1698 -Wl,--wrap=node_destroy -Wl,--wrap=func_15111DD8 -Wl,--wrap=func_151432BC -Wl,--wrap=func_15096144 -Wl,--wrap=func_150966AC -Wl,--wrap=func_15144CEC -Wl,--wrap=func_15129EA4 -Wl,--wrap=func_151BF678 -Wl,--wrap=func_151BEE00 -Wl,--wrap=func_15053430 -Wl,--wrap=func_151152A4 -Wl,--wrap=func_151BF490 -Wl,--wrap=func_15095F18 -Wl,--wrap=func_15146078 -Wl,--wrap=func_15159C2C -Wl,--wrap=func_1514654C -Wl,--wrap=func_151148C8 -Wl,--wrap=effect3d_update -Wl,--wrap=effect3d_draw -Wl,--wrap=func_1513100C -Wl,--wrap=func_1517B270 -Wl,--wrap=func_150A7EE0 -Wl,--wrap=func_1501A764 -Wl,--wrap=func_151928C8 -Wl,--wrap=func_15153BA4 -Wl,--wrap=func_151848D8 -Wl,--wrap=func_1514D6CC -Wl,--wrap=func_10010154 -Wl,--wrap=func_10010344 -Wl,--wrap=func_1000F568 -Wl,--wrap=func_15064F50 -Wl,--wrap=func_15064668 -Wl,--wrap=func_1516AFE0 -Wl,--wrap=func_1516AD20 -Wl,--wrap=func_150AE5F8 -Wl,--wrap=func_150AE60C -Wl,--wrap=func_150619A8 -Wl,--wrap=func_150ADFD0 -Wl,--wrap=func_150511E8 -Wl,--wrap=func_150CA150 -Wl,--wrap=func_1518D1C0 -Wl,--wrap=effect3d_spawn_default -Wl,--wrap=func_1505C1E4 -Wl,--wrap=func_150877C0 -Wl,--wrap=func_151B61A0 -Wl,--wrap=func_1506AD30 -Wl,--wrap=node_lists_run_update -Wl,--wrap=node_render_layers_draw -Wl,--wrap=func_151D7EDC -Wl,--wrap=func_151D7FE8 -Wl,--wrap=func_151D8280 -Wl,--wrap=func_150186D0 2> $(B)/link_warnings.txt \
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
