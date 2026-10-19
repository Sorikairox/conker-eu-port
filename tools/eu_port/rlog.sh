#!/bin/bash
_top=$(git rev-parse --show-toplevel 2>/dev/null); if [ -n "$_top" ] && [ "$_top" != "${CONKER_ROOT:-$HOME/conker}" ]; then echo "refusing: cwd repo $_top != CONKER_ROOT ${CONKER_ROOT:-$HOME/conker} (run: eval \"\$(tools/eu_port/wt.sh env <name>)\")" >&2; exit 3; fi
# usage: rlog.sh func start attempts end y|n perm y|n "note"   -> appends a row to repair_log.tsv
printf '%s\t%s\t%s\t%s\t%s\t%s\t%s\n' "$@" >> ${CONKER_ROOT:-$HOME/conker}/tools/eu_port/repair_log.tsv
