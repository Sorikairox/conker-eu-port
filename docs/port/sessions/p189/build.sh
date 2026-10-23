#!/bin/bash
# P189 (from P185) (from P178) (from P174) P171 (from P152) (from p113): build port/build/web (port-only changes: no vbe.stamp removal needed; pass "clean" to remove it)
cd /Users/sorikairo/conker-wt/web || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
eval "$(tools/eu_port/wt.sh env web)"
[ "$1" = clean ] && rm -f port/build/vbe.stamp
port/web/run.sh build > port_work/p189/build.log 2>&1; rc=$?
echo "build rc=$rc; errors: $(grep -c -i ' error' port_work/p189/build.log); link warnings: $(wc -l < port/build/link_warnings.txt)"
grep -m5 -i 'error' port_work/p189/build.log | cut -c1-200
