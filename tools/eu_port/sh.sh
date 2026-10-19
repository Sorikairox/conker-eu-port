#!/bin/bash
_top=$(git rev-parse --show-toplevel 2>/dev/null); if [ -n "$_top" ] && [ "$_top" != "${CONKER_ROOT:-$HOME/conker}" ]; then echo "refusing: cwd repo $_top != CONKER_ROOT ${CONKER_ROOT:-$HOME/conker} (run: eval \"\$(tools/eu_port/wt.sh env <name>)\")" >&2; exit 3; fi
# usage: sh.sh <func>   -> asm (one line) + fresh draft
f=$1; F=${CONKER_ROOT:-$HOME/conker}/tools/decomp-permuter/repair/fresh
grep -h -A80 "glabel $f\$" ${CONKER_ROOT:-$HOME/conker}/conker/asm/nonmatchings/*/$f.s | sed 's|.*\*/ *||;s/  */ /g' | tr '\n' ';' ; echo; echo ----; cat $F/$f.c
