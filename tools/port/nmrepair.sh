#!/bin/bash
# usage: tools/port/nmrepair.sh FUNC [draft.c] [--trials N] [--wide W]
# One view for hand repair of a NON_MATCHING body:
#   1. the draft (default: the newest port_work/*/best/FUNC.c that convert.py left, with its results.tsv row)
#   2. the difftest verdict; on DIFFER the diverging trial: inputs, both call traces (a0-a3, '*' = differs),
#      the final memory bytes that differ, return values
#   3. the draft and the asm side by side (numbered draft lines | asm without the address/word columns)
# Edit a copy of the draft and re-run with it as the second argument until EQUIV; then
# tools/port/insert_nm.py FUNC draft.c and verify_all.sh.
. "$(dirname "${BASH_SOURCE[0]}")/portguard.sh"  # wrong-checkout guard (P7)
R=${CONKER_ROOT:-$HOME/conker}
exec python3 "$R/tools/port/nmrepair.py" "$@"
