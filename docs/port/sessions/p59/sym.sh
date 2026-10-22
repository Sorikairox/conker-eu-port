#!/bin/bash
# usage: sym.sh NAME... -> EU ELF addresses (names are not addresses, P56)
cd "$(dirname "$0")/../../../.." && eval "$(tools/eu_port/wt.sh env portb)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
docker exec $CONKERDEV mips-linux-gnu-nm /conker/conker/build/conker.eu.elf | grep -E " ($(echo "$@" | tr ' ' '|'))$"
