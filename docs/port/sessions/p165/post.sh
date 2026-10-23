#!/bin/bash
# P149: after checks.sh: remove census files.tsv + vbe.stamp, clean web build, census, arity_scan, m2c_sanity (they read port/build/ll)
cd /Users/sorikairo/conker-wt/web || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
eval "$(tools/eu_port/wt.sh env web)"
L=port_work/p165
rm -f port/build/census/files.tsv port/build/vbe.stamp
port/web/run.sh build > $L/build.log 2>&1; echo "build rc=$? errors $(grep -c -i ' error' $L/build.log) linkwarn $(wc -l < port/build/link_warnings.txt)"
grep -m5 -i 'error' $L/build.log | cut -c1-200
port/web/run.sh census > $L/census.log 2>&1; echo "census rc=$?"; cat port/build/census/summary.txt | head -5
python3 tools/port/arity_scan.py > $L/arity.log 2>&1; echo "arity rc=$? tsv lines $(wc -l < docs/port/arity_scan.tsv)"; tail -2 $L/arity.log
python3 port/tools/m2c_sanity.py > $L/m2c.log 2>&1; echo "m2c rc=$? rows $(wc -l < docs/port/m2c_sanity.tsv)"; tail -3 $L/m2c.log
