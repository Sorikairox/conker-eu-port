#!/bin/bash
# asm.sh FUNC : full asm of FUNC from the ELF disassembly
awk -v f="<$1>:" '$2==f{p=1;next} p && /^[0-9a-f]+ </{exit} p' /Users/sorikairo/conker-wt/web/port/build/arity/eu_elf.dis
