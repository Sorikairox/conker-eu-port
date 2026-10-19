#!/bin/bash
_top=$(git rev-parse --show-toplevel 2>/dev/null); if [ -n "$_top" ] && [ "$_top" != "${CONKER_ROOT:-$HOME/conker}" ]; then echo "refusing: cwd repo $_top != CONKER_ROOT ${CONKER_ROOT:-$HOME/conker} (run: eval \"\$(tools/eu_port/wt.sh env <name>)\")" >&2; exit 3; fi
# usage: fctx.sh <func>  -> copy the fresh gen40 draft (dir from fresh.txt) into repair/fresh/ and show repair_ctx
R=${CONKER_ROOT:-$HOME/conker}/tools/decomp-permuter/repair; f=$1
d=$(awk -v f=$f '$3==f{print $4; exit}' $R/fresh.txt)
[ -n "$d" ] && [ -f $d/$f.c ] && cp $d/$f.c $R/fresh/$f.c
MAXT=${MAXT:-60} ${CONKER_ROOT:-$HOME/conker}/tools/eu_port/repair_ctx.sh $f 2>&1 | cut -c1-110
