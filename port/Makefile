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

ULTRA_SRC := ultra/pc_sched.c ultra/pc_os.c ultra/pc_pif.c ultra/pc_video.c ultra/pc_mem.c ultra/pc_icall.c ultra/pc_gu.c ultra/pc_libc.c
ULTRA_OBJ := $(patsubst ultra/%.c,$(B)/ultra/%.o,$(ULTRA_SRC))
# F3DEX2 interpreter + WebGL2 backend + ROM asset viewer (docs/port/sessions/P6.md)
GFX_SRC := gfx/gfx_f3dex2.c gfx/gfx_demo.c
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
BOOT_SRC  := boot/game_main.c boot/game_entry.c boot/game_icalltest.c boot/pc_overrides.c boot/sched_test.c boot/gu_test.c audio/aud_test.c audio/mp3_pc.c
BOOT_OBJS := $(patsubst %.c,$(B)/vobj/port__%.o,$(notdir $(BOOT_SRC)))
STUB_OBJS := $(B)/stubs/asm_stubs.o $(B)/stubs/data_stubs.o $(B)/stubs/n64mem_tab.o $(B)/stubs/n64mem_labels.o $(B)/stubs/icall_tab.o

$(B)/vbe.stamp: $(B)/census/files.tsv exclude.txt tools/vbe.py tools/vbe_build.py tools/sigs.py tools/icall.py $(BOOT_SRC) ultra/pc_mem.h $(GEN)/memtest_expect.h $(GEN)/gutest_expect.h
	cd .. && python3 port/tools/vbe_build.py $(addprefix port/,$(BOOT_SRC))
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
	  $(LINK_COMMON) -sGLOBAL_BASE=256MB -sINITIAL_MEMORY=352MB -sSTACK_OVERFLOW_CHECK=0 -sEXPORT_NAME=createConker -sEXPORTED_FUNCTIONS=_main,_malloc,_free,_port_set_rom,_port_dump_threads,_port_dump_stubs,_port_gfx_demo_test,_port_audio_test,_port_voice_test,_port_audio_prepare,_port_pad_state,_port_eeprom_ptr,_port_eeprom_size,_port_eep_test,_port_set_paused -Wl,--error-limit=0 2> $(B)/link_warnings.txt \
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
