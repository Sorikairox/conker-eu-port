BASENAME := conker

# NON_MATCHING=1: compile the C side of `#ifdef NON_MATCHING` blocks (functionally equivalent,
# not byte-identical bodies) into a separate build tree, without the sha1 verify
ifeq ($(NON_MATCHING),1)
BUILD_DIR = build_nm
else
BUILD_DIR = build
endif
VERSION   := us

### Split configuration

OFFSETS_LENGTH      := 2048
TEXT_SECTION_LENGTH := 1335000
DATA_SECTION_LENGTH := 92000

### Version differences

ifeq ($(VERSION),us)
SRC_DIR  := src
else
ifeq ($(VERSION),eu)
SRC_DIR := src_eu
else
ifeq ($(VERSION),ects)
SRC_DIR := src_ects
else
SRC_DIR := src_debug
OFFSETS_LENGTH      := 2112
TEXT_SECTION_LENGTH := 1380000
COMPRESS_DIR_ARGS   := --num-offsets 528 --total-size 1380000
endif
endif
endif

### Directories

ASM_DIRS  = asm \
            asm/libultra asm/libultra/audio asm/libultra/gu asm/libultra/io asm/libultra/libc asm/libultra/os \
			asm/data asm/data/init asm/data/init/data asm/data/game asm/data/libultra

BIN_DIRS  = assets

SPLIT_DIR := $(BUILD_DIR)/split

DEBUGGER_SRC_DIRS := $(SRC_DIR)/debugger $(SRC_DIR)/debugger/data
INIT_SRC_DIRS     := $(SRC_DIR)/init $(SRC_DIR)/init/data
GAME_SRC_DIRS     := $(SRC_DIR)/game $(SRC_DIR)/game/data $(SRC_DIR)/game/done
LIBULTRA_SRC_DIRS := $(SRC_DIR)/libultra $(SRC_DIR)/libultra/audio $(SRC_DIR)/libultra/gu \
            				 $(SRC_DIR)/libultra/io $(SRC_DIR)/libultra/libc $(SRC_DIR)/libultra/os

SRC_DIRS := $(SRC_DIR) \
						$(DEBUGGER_SRC_DIRS) \
						$(INIT_SRC_DIRS) \
						$(GAME_SRC_DIRS) \
						$(LIBULTRA_SRC_DIRS)

# P22: NON_MATCHING C for functions of raw asm files (splat `asm` segments; the file must not contain the word G-L-O-B-A-L_ASM, which the GLOBAL_ASM_C_FILES grep would pick up). src_eu/nm_asm/X.c
# holds C for functions of asm/X.s; it is compiled and linked only with NON_MATCHING=1, and the asm copies of
# the functions listed in NM_ASM_C_FUNCS_X are weakened in X.s.o so the C definitions win.
NM_ASM_SRC_DIR := $(SRC_DIR)/nm_asm
NM_ASM_C_FUNCS_D5E90 := func_150AB278 func_150AD780 func_150AD78C
NM_ASM_C_FUNCS_D5E90 += func_150AB6D0 func_150AC8C4 func_150ACEA0
ifeq ($(NON_MATCHING),1)
SRC_DIRS += $(NM_ASM_SRC_DIR)
endif


S_FILES   = $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)/*.s))
C_FILES   = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
H_FILES   = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.h))
BIN_FILES = $(foreach dir,$(BIN_DIRS),$(wildcard $(dir)/*.bin))

O_FILES := $(foreach file,$(S_FILES),$(BUILD_DIR)/$(file:.s=.s.o)) \
           $(foreach file,$(C_FILES),$(BUILD_DIR)/$(file:.c=.c.o)) \
           $(foreach file,$(BIN_FILES),$(BUILD_DIR)/$(file:.bin=.bin.o))

TARGET = $(BUILD_DIR)/$(BASENAME).$(VERSION)

LD_SCRIPT = $(BASENAME).ld

# IDO_DIR is overridden by the arm64 image (Dockerfile.arm) with a native build
IDO_DIR ?= ../ido/ido5.3_recomp
CC     := $(IDO_DIR)/cc

CROSS   = mips-linux-gnu-
AS      = $(CROSS)as
CPP     = cpp
LD      = $(CROSS)ld
OBJDUMP = $(CROSS)objdump
OBJCOPY = $(CROSS)objcopy
PYTHON  = python3

RZIP    := $(PYTHON) ../tools/rarezip.py
RZIPDIR := $(PYTHON) ../tools/compress_dir.py
SPLIT := split -b 4096 -d --additional-suffix=.bin --suffix-length=4

OPT_FLAGS := -O2 -g3
MIPSBIT := -mips2 -o32

ASM_PROCESSOR_DIR := ../tools/asm-processor

# Target version differences

ifeq ($(VERSION),ects)
TARGET_GAME_BIN = $(TARGET).game.bin
TARGET_ROOT_GAME_BIN = ../assets/game.$(VERSION).bin
else
TARGET_GAME_BIN = $(TARGET).game.rzip.bin
TARGET_ROOT_GAME_BIN = ../assets/game.$(VERSION).rzip.bin
endif

# Files requiring pre/post-processing
GREP := grep -rl
GLOBAL_ASM_C_FILES := $(shell $(GREP) GLOBAL_ASM $(SRC_DIR) </dev/null)
GLOBAL_ASM_O_FILES := $(foreach file,$(GLOBAL_ASM_C_FILES),$(BUILD_DIR)/$(file:.c=.c.o))

INCLUDE_CFLAGS := -I . -I include -I include/2.0L -I include/2.0L/PR -I include/libc -I src/libultra/os -I src/libultra/audio -I src/libultra/io

ASFLAGS = -EB -mtune=vr4300 -march=vr4300 -mabi=32 -I include

CFLAGS := -G 0 -Xfullwarn -Xcpluscomm -signed -nostdinc -non_shared -Wab,-r4300_mul
CFLAGS += -D_LANGUAGE_C -D_FINALROM -DF3DEX_GBI_2 -D_MIPS_SZLONG=32
# ignore compiler warnings about anonymous structs
CFLAGS += -woff 649,838
CFLAGS += $(INCLUDE_CFLAGS)
ifeq ($(NON_MATCHING),1)
CFLAGS += -DNON_MATCHING
endif

LDFLAGS = -T $(BUILD_DIR)/$(LD_SCRIPT) -Map $(TARGET).map -T undefined_syms.$(VERSION).txt -T undefined_funcs.$(VERSION).txt -T undefined_syms_auto.txt -T undefined_funcs_auto.txt --no-check-sections

### Overrides

$(BUILD_DIR)/$(SRC_DIR)/libultra/audio/%.o: OPT_FLAGS := -g

# TODO: blindly move all of this into libultra/audio
$(BUILD_DIR)/$(SRC_DIR)/init_17F10.c.o: OPT_FLAGS := -g
$(BUILD_DIR)/$(SRC_DIR)/init_17F80.c.o: OPT_FLAGS := -g
$(BUILD_DIR)/$(SRC_DIR)/init_19B50.c.o: OPT_FLAGS := -g
$(BUILD_DIR)/$(SRC_DIR)/init_1AAE0.c.o: OPT_FLAGS := -g
$(BUILD_DIR)/$(SRC_DIR)/init_1C060.c.o: OPT_FLAGS := -g
$(BUILD_DIR)/$(SRC_DIR)/init_1E480.c.o: OPT_FLAGS := -g
$(BUILD_DIR)/$(SRC_DIR)/init_1E4A0.c.o: OPT_FLAGS := -g
$(BUILD_DIR)/$(SRC_DIR)/init_1E530.c.o: OPT_FLAGS := -g
$(BUILD_DIR)/$(SRC_DIR)/init_1FB40.c.o: OPT_FLAGS := -g
$(BUILD_DIR)/$(SRC_DIR)/init_20000.c.o: OPT_FLAGS := -g
$(BUILD_DIR)/$(SRC_DIR)/init_210C0.c.o: OPT_FLAGS := -g
$(BUILD_DIR)/$(SRC_DIR)/init_214F0.c.o: OPT_FLAGS := -g
$(BUILD_DIR)/$(SRC_DIR)/init_22040.c.o: OPT_FLAGS := -g
$(BUILD_DIR)/$(SRC_DIR)/init_22460.c.o: OPT_FLAGS := -g


# EU only: n_cspgetstate is optimised there
$(BUILD_DIR)/src_eu/libultra/audio/n_cspgetstate.c.o: OPT_FLAGS := -O2
$(BUILD_DIR)/src_eu/libultra/gu/guNormalize.c.o: OPT_FLAGS := -O2
$(BUILD_DIR)/src_eu/libultra/io/pfsisplug2.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/libultra/os/initialize.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/game_221290.c.o: OPT_FLAGS := -g
$(BUILD_DIR)/src_eu/game_eu_21D010.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/game_eu_21D050.c.o: OPT_FLAGS := -O2
$(BUILD_DIR)/src_eu/game_eu_21DCD0.c.o: OPT_FLAGS := -O2
$(BUILD_DIR)/src_eu/game_21D5F0.c.o: OPT_FLAGS := -O3
$(BUILD_DIR)/src_eu/libultra/io/crc2.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/libultra/io/pfschecker2.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_289A0.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/game_eu_21D610.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/game_eu_21D5E0.c.o: OPT_FLAGS := -O3
$(BUILD_DIR)/src_eu/init_eu_23590.c.o: OPT_FLAGS := -O2
$(BUILD_DIR)/src_eu/init_eu_24880.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_24320.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_23400.c.o: OPT_FLAGS := -O2
$(BUILD_DIR)/src_eu/init_eu_23CC0.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_27C40.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_27990.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_25370.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_25C10.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_25FC0.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_25AA0.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_256E0.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_24ED0.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_26370.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_26A30.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_27950.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_27960.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_277D0.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_24BF0.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_24DF0.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_251D0.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_26AD0.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_252D0.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_24870.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_265F0.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_25360.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_242F0.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_24260.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_24220.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_24210.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_23050.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_22FE0.c.o: OPT_FLAGS := -O1

# libultra ll.c: 64-bit long long helpers need -mips3 (then the o32 ABI bit, like ultralib)
$(BUILD_DIR)/src_eu/init_eu_26B30.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_26DF0.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_26B30.c.o: MIPSBIT := -mips3 -32
$(BUILD_DIR)/src_eu/init_eu_23360.c.o: OPT_FLAGS := -O2
$(BUILD_DIR)/src_eu/init_eu_232A0.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_22D70.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_23A20.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_238E0.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_23860.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/game_eu_21E320.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/game_eu_21E520.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/game_eu_21D060.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/game_eu_21D420.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/game_eu_21D990.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/game_eu_21DA70.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/game_eu_21DF40.c.o: OPT_FLAGS := -O2
$(BUILD_DIR)/src_eu/game_eu_21D7D0.c.o: OPT_FLAGS := -O3
$(BUILD_DIR)/src_eu/game_eu_21E490.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/game_eu_220050.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/game_eu_220400.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src_eu/init_eu_23B70.c.o: OPT_FLAGS := -O1

$(BUILD_DIR)/$(SRC_DIR)/libultra/io/ai.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/$(SRC_DIR)/libultra/io/aigetstat.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/$(SRC_DIR)/libultra/io/aisetfreq.c.o: OPT_FLAGS := -O1

$(BUILD_DIR)/$(SRC_DIR)/libultra/os/getthreadpri.c.o: OPT_FLAGS := -O1

$(BUILD_DIR)/$(SRC_DIR)/init_3920.c.o: OPT_FLAGS := -O2

# $(BUILD_DIR)/$(SRC_DIR)/init_B1B0.o: OPT_FLAGS := -O2

# $(BUILD_DIR)/$(SRC_DIR)/game_14FF90.o: OPT_FLAGS := -O3

### Non-matching
ifeq ($(NON_MATCHING),1)
VERIFY :=
else
VERIFY := verify
endif

### Targets

default: all

all: dirs $(TARGET).bin $(VERIFY)

dirs:
	$(foreach dir,$(SRC_DIRS) $(ASM_DIRS) $(BIN_DIRS) ,$(shell mkdir -p $(BUILD_DIR)/$(dir)))

clean:
	rm -rf build

really-clean: clean
	rm -rf asm
	rm -rf bin
	rm -rf assets
	rm -rf $(BASENAME).*.ok
	rm -f *auto.txt
	rm -rf conker.us.bin conker.eu.bin conker.ects.bin conker.debug.bin

extract: $(BUILD_DIR)/splat

# sanity check base bin
check: $(BASENAME).$(VERSION).ok

# check built bin
verify: $(TARGET).ok

progress: $(VERIFY) progress.csv

# replace original binaries
replace: $(VERIFY) $(TARGET).header.bin $(TARGET).boot.bin $(TARGET).init.bin $(TARGET_GAME_BIN) $(TARGET).debugger.bin
	cp $(TARGET).header.bin ../assets/header.$(VERSION).bin
	cp $(TARGET).boot.bin ../assets/boot.$(VERSION).bin
	cp $(TARGET).init.bin ../assets/init.$(VERSION).bin
	cp $(TARGET).debugger.bin ../assets/debugger.$(VERSION).bin
	cp $(TARGET_GAME_BIN) $(TARGET_ROOT_GAME_BIN)


### Recipes

$(BUILD_DIR)/$(LD_SCRIPT): $(LD_SCRIPT)
	$(CPP) -P -DBUILD_DIR=$(BUILD_DIR) $< | sed 's#\bbuild/#$(BUILD_DIR)/#g' > $@
ifeq ($(NON_MATCHING),1)
# the C .rodata of NON_MATCHING bodies (literals) has no home in the blob layout: park it NOLOAD at the
# expansion-pak address so the ELF links (the NON_MATCHING ROM is not bootable yet: PLAN Phase 2)
	sed -i '/\/DISCARD\/ :/i\    .nm_rodata 0x80400000 (NOLOAD) : { $(BUILD_DIR)/src_eu/*.o(.rodata*) $(BUILD_DIR)/src_eu/nm_asm/*.o(.rodata*) }' $@
	sed -i 's#^\(\s*\)$(BUILD_DIR)/asm/D5E90.s.o(.text);#&\n\1$(BUILD_DIR)/$(NM_ASM_SRC_DIR)/D5E90.c.o(.text);#' $@
endif

$(TARGET).elf: $(O_FILES) $(BUILD_DIR)/$(LD_SCRIPT) $(GLOBAL_ASM_O_FILES)
	$(LD) $(LDFLAGS) -o $@

ifndef PERMUTER
$(GLOBAL_ASM_O_FILES): $(BUILD_DIR)/%.c.o: %.c include/variables.h include/structs.h include/functions.h
	$(PYTHON) $(ASM_PROCESSOR_DIR)/asm_processor.py $(OPT_FLAGS) $< > $(BUILD_DIR)/$<
	$(CC) -c -32 $(CFLAGS) $(OPT_FLAGS) $(LOOP_UNROLL) $(MIPSBIT) -o $@ $(BUILD_DIR)/$<
	$(PYTHON) $(ASM_PROCESSOR_DIR)/asm_processor.py $(OPT_FLAGS) $< --post-process $@ \
		--assembler "$(AS) $(ASFLAGS)" --asm-prelude $(ASM_PROCESSOR_DIR)/prelude.inc
endif

$(BUILD_DIR)/%.c.o: %.c
	$(CC) -c -32 $(CFLAGS) $(OPT_FLAGS) $(MIPSBIT) -o $@ $<

# libultra ll.c (init_eu_26B30): -mips3 object gets the o32 ABI bit, like ultralib
$(BUILD_DIR)/src_eu/init_eu_26B30.c.o: src_eu/init_eu_26B30.c
	$(CC) -c -32 $(CFLAGS) $(OPT_FLAGS) $(MIPSBIT) -o $@ $<
	$(PYTHON) tools/set_o32abi_bit.py $@

$(BUILD_DIR)/%.s.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

ifeq ($(NON_MATCHING),1)
$(BUILD_DIR)/asm/D5E90.s.o: asm/D5E90.s
	$(AS) $(ASFLAGS) -o $@ $<
	$(OBJCOPY) $(foreach f,$(NM_ASM_C_FUNCS_D5E90),--weaken-symbol=$(f)) $@
endif

$(BUILD_DIR)/%.bin.o: %.bin
	$(LD) -r -b binary -o $@ $<

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) $(OBJCOPYFLAGS) -O binary $< $@

# extract
$(BUILD_DIR)/splat: check $(BASENAME).$(VERSION).yaml
	$(PYTHON) ../tools/n64splat/split.py $(BASENAME).$(VERSION).yaml
ifeq ($(VERSION),eu)
	$(PYTHON) ../tools/eu_port/rodata_inject.py
endif

%.ok: %.bin
	@echo "$$(cat $(BASENAME).$(VERSION).sha1)  $<" | sha1sum --check
	@touch $@

conker.$(VERSION).bin:
	make extract -C ..

# dump sections
$(TARGET).header.bin: $(TARGET).elf
	$(OBJCOPY) -O binary --only-section .header $< $@

$(TARGET).boot.bin: $(TARGET).elf
	$(OBJCOPY) -O binary --only-section .boot $< $@

$(TARGET).init.bin: $(TARGET).init.code.bin $(TARGET).init.data.bin
	cat $^ > $@

$(TARGET).init.code.bin: $(TARGET).elf
	$(OBJCOPY) -O binary --only-section .init $< $@

$(TARGET).init.data.bin: $(TARGET).elf
	$(OBJCOPY) -O binary --only-section .init_data $< $@

#ects only
$(TARGET).game.bin: $(TARGET).game.code.bin $(TARGET).game.data.bin
	cat $^ > $@

$(TARGET).game.code.bin: $(TARGET).elf
	$(OBJCOPY) -O binary --only-section .game $< $@

$(TARGET).game.data.bin: $(TARGET).elf
	$(OBJCOPY) -O binary --only-section .game_data $< $@

$(TARGET).debugger.bin: $(TARGET).debugger.code.bin $(TARGET).debugger.data.bin
	cat $^ > $@

$(TARGET).debugger.code.bin: $(TARGET).elf
	$(OBJCOPY) -O binary --only-section .debugger $< $@

$(TARGET).debugger.data.bin: $(TARGET).elf
	$(OBJCOPY) -O binary --only-section .debugger_data $< $@

# split code section
$(SPLIT_DIR)/0000.bin: $(TARGET).game.code.bin
	mkdir -p $(SPLIT_DIR)
	$(SPLIT) $< $(SPLIT_DIR)/

# create offsets file
$(SPLIT_DIR)/offsets.bin: $(SPLIT_DIR)/0000.bin
	$(RZIPDIR) $(SPLIT_DIR) $(SPLIT_DIR) --offsets-file $@ $(COMPRESS_DIR_ARGS)

# concatenate compressed code blocks
$(TARGET).game.code.rzip.bin: $(TARGET).game.code.bin $(SPLIT_DIR)/offsets.bin
	cat $(SPLIT_DIR)/*.gz > $@

# compressed data section
$(TARGET).game.data.rzip.bin: $(TARGET).game.data.bin
	$(RZIP) $< $@

# create padding
$(TARGET).game.code.padding.bin:
	cp ../assets/game/code_padding.bin $@

$(TARGET).game.data.padding.bin: $(TARGET).game.data.rzip.bin
	dd if=/dev/zero of=$@ bs=1 count=$$(($(DATA_SECTION_LENGTH)-$$(wc -c <$<)))

$(TARGET).game.rzip.bin: $(SPLIT_DIR)/offsets.bin $(TARGET).game.code.rzip.bin $(TARGET).game.code.padding.bin $(TARGET).game.data.rzip.bin $(TARGET).game.data.padding.bin
	cat $^ > $@

progress.csv: progress.init.csv progress.game.csv progress.debugger.csv
	cat $^ > $@

progress.init.csv: $(TARGET).elf
	$(PYTHON) ../tools/progress.py . $(TARGET).map .init --version $(VERSION) > $@
progress.game.csv: $(TARGET).elf
	$(PYTHON) ../tools/progress.py . $(TARGET).map .game --version $(VERSION) > $@
progress.debugger.csv: $(TARGET).elf
	$(PYTHON) ../tools/progress.py . $(TARGET).map .debugger --version $(VERSION) > $@


# settings
.PHONY: all clean default
SHELL = /bin/bash -e -o pipefail
