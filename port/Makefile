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

LINK_COMMON := -sASYNCIFY -sASYNCIFY_STACK_SIZE=65536 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 \
               -sALLOW_MEMORY_GROWTH=1 -sINITIAL_MEMORY=128MB -sSTACK_SIZE=1MB -sMODULARIZE=1 -sINVOKE_RUN=0 -sEXIT_RUNTIME=0 \
               -sEXPORTED_FUNCTIONS=_main,_malloc,_free,_port_set_rom,_port_dump_threads \
               -sEXPORTED_RUNTIME_METHODS=HEAPU8,callMain -sENVIRONMENT=web,node --profiling-funcs

ULTRA_SRC := ultra/pc_sched.c ultra/pc_os.c ultra/pc_video.c
ULTRA_OBJ := $(patsubst ultra/%.c,$(B)/ultra/%.o,$(ULTRA_SRC))

.PHONY: all demo objs game web clean
all: demo game web

$(B)/ultra/%.o: ultra/%.c ultra/pc_ultra.h
	@mkdir -p $(@D)
	emcc $(ULTRA_CFLAGS) -c $< -o $@

# ---- scheduler demo
$(B)/demo.o: sched_demo/demo.c ultra/pc_ultra.h
	@mkdir -p $(@D)
	emcc $(ULTRA_CFLAGS) -c $< -o $@

demo: $(WEB)/sched_demo.js
$(WEB)/sched_demo.js: $(B)/demo.o $(ULTRA_OBJ)
	@mkdir -p $(@D)
	emcc $^ -o $@ $(LINK_COMMON) -sEXPORT_NAME=createSchedDemo

# ---- game: every src_eu TU that clang accepts + PC libultra + boot + generated stubs
objs:
	cd .. && python3 port/tools/census.py

# TUs that still fail under clang (see census) are left out; their functions get stubs
GAME_OBJS = $(shell awk -F'\t' 'FNR==NR {if ($$0 !~ /^\#/) ex[$$1]=1; next} FNR>1 && $$4=="ok" && !($$1 in ex) {gsub("/","__",$$1); print "$(B)/obj/" $$1 ".o"}' exclude.txt $(B)/census/files.tsv 2>/dev/null)

$(B)/boot.o: boot/game_main.c
	@mkdir -p $(@D)
	emcc $(GAME_CFLAGS) -c $< -o $@

$(B)/stubs/asm_stubs.o $(B)/stubs/data_stubs.o: $(B)/stubs/%.o: $(GEN)/%.c
	@mkdir -p $(@D)
	emcc -O1 -g0 -c $< -o $@

$(GEN)/asm_stubs.c $(GEN)/data_stubs.c &: $(B)/census/files.tsv exclude.txt $(B)/boot.o $(ULTRA_OBJ) tools/gen_stubs.py
	cd .. && python3 port/tools/gen_stubs.py port/$(GEN) $(LIBDIR) $(addprefix port/,$(GAME_OBJS) $(B)/boot.o $(ULTRA_OBJ))

$(B)/census/files.tsv:
	cd .. && python3 port/tools/census.py

game: $(WEB)/conker.js
$(WEB)/conker.js: $(B)/census/files.tsv $(B)/boot.o $(ULTRA_OBJ) $(B)/stubs/asm_stubs.o $(B)/stubs/data_stubs.o
	@mkdir -p $(@D)
	emcc $(GAME_OBJS) $(B)/boot.o $(ULTRA_OBJ) $(B)/stubs/asm_stubs.o $(B)/stubs/data_stubs.o -o $@ \
	  $(LINK_COMMON) -sEXPORT_NAME=createConker -Wl,--error-limit=0 2> $(B)/link_warnings.txt \
	  || (tail -40 $(B)/link_warnings.txt; exit 1)
	@echo "link warnings: $$(grep -c warning $(B)/link_warnings.txt) (port/build/link_warnings.txt)"
	@ls -l $(WEB)/conker.wasm

# ---- page
web: $(WEB)/index.html $(WEB)/main.js
$(WEB)/%: web/%
	@mkdir -p $(@D)
	cp $< $@

clean:
	rm -rf $(B)/obj $(B)/ultra $(B)/stubs $(B)/census $(B)/*.o $(WEB) $(GEN)/asm_stubs.c $(GEN)/data_stubs.c

print-objs:
	@echo $(GAME_OBJS)
