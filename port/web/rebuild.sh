#!/bin/bash
# P11: rebuild + boot with compact output.  port/web/rebuild.sh [SECONDS] [clean]
#   clean: drop census/vbe stamps first (after a merge or a game C change)
cd "$(dirname "$0")/../.." || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
eval "$(tools/eu_port/wt.sh env web)"
[ "${2:-}" = clean ] && rm -f port/build/census/files.tsv port/build/vbe.stamp
port/web/run.sh build > port/build/rebuild.log 2>&1 || { grep -E "error|Error" port/build/rebuild.log | head -20; echo BUILD FAILED; exit 1; }
grep -E "link warnings" port/build/rebuild.log
port/web/boot.sh "${1:-10}"
