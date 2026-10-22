#!/bin/bash
# usage: p68_sym.sh SYM...  -> EU addresses from build/conker.eu.elf (knob addresses)
cd /Users/sorikairo/conker-wt/portb && eval "$(tools/eu_port/wt.sh env portb)" >/dev/null; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
pat=$(printf "|%s" "$@"); docker exec -w /conker/conker $CONKERDEV sh -c "mips-linux-gnu-nm build/conker.eu.elf | grep -E ' (${pat:1})\$'"
