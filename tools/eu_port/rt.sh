#!/bin/bash
# usage: rt.sh <func> <draft.c>  -> repair_try + opcode-level shifts + first ** lines (compact)
# only inside a worktree (~/conker-wt/<name>) adopt that worktree's env; never switch from main
_top=$(git -C "$(dirname "$0")" rev-parse --show-toplevel 2>/dev/null)
case $_top in */conker-wt/*) eval "$("$(dirname "$0")"/wt.sh env "${_top##*/}")" ;; esac
$(dirname $0)/repair_try.sh $1 $2 | head -${3:-3}
R=${CONKER_ROOT:-$HOME/conker}/tools/decomp-permuter/repair
python3 $(dirname $0)/opshift.py $R/$1.diff | head -${4:-12}
