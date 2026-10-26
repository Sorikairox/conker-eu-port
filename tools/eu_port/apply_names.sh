#!/bin/bash
# Apply naming proposals (docs/names/PROPOSING.md) in one step, on port-web:
#   tools/eu_port/apply_names.sh 03 04 05      chunks docs/names/proposals/chunkNN.tsv
# validate (format, duplicates against each other and names.tsv) -> append to tools/eu_port/names.tsv (non-high
# confidence kept as "(med)"/"(low)" in the description) -> rename.py --check, apply, --verify -> full checks ->
# census + web build -> browser hold-L test (opening must end at retrace 5789) -> commit -> backup_push.
# Stops at the first red step; nothing is committed then (fix, or `git checkout -- . && git clean` the rename).
set -euo pipefail
cd ~/conker-wt/web
eval "$(tools/eu_port/wt.sh env web)"
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
[ $# -gt 0 ] || { sed -n '2,7p' "$0"; exit 2; }
L=port_work/apply_names_$(echo "$@" | tr ' ' _); mkdir -p "$L"
[ -z "$(git status --porcelain --untracked-files=no)" ] || { echo "tree not clean"; exit 1; }

python3 -I - "$@" <<'EOF'
import re, sys, collections
have = {}
for line in open('tools/eu_port/names.tsv'):
    if line.startswith('#') or line.startswith('old\t') or not line.strip(): continue
    o, n = line.split('\t')[:2]; have[o] = n
used = set(have.values()); rows = []
for c in sys.argv[1:]:
    for line in open(f'docs/names/proposals/chunk{c}.tsv'):
        if line.startswith('#') or line.startswith('old\t') or not line.strip(): continue
        f = line.rstrip('\n').split('\t')
        if len(f) < 4: sys.exit(f'chunk{c}: bad row {f}')
        o, n, conf, d = f[:4]
        n = n.lower()   # names that embed an address use lowercase hex
        if not re.fullmatch(r'func_(eu_)?[0-9A-F]{8}', o) or not re.fullmatch(r'[a-z][a-z0-9_]{2,47}', n): sys.exit(f'chunk{c}: bad name {o} {n}')
        if o in have: print(f'skip {o}: already in names.tsv'); continue
        rows.append((o, n, conf, d.replace('\t', ' ')))
dn = [n for n, k in collections.Counter(r[1] for r in rows).items() if k > 1] + [r[1] for r in rows if r[1] in used]
do = [o for o, k in collections.Counter(r[0] for r in rows).items() if k > 1]
if dn or do: sys.exit(f'duplicates: new {dn[:10]} old {do[:10]}')
with open('tools/eu_port/names.tsv', 'a') as out:
    for o, n, conf, d in rows:
        out.write(f'{o}\t{n}\t{d if conf == "high" else f"({conf}) {d}"}\n')
print(f'{len(rows)} rows appended')
EOF

tools/eu_port/rename.py --check > $L/check.txt 2>&1 || { tail -3 $L/check.txt; echo "rename --check failed"; exit 1; }
tail -1 $L/check.txt
tools/eu_port/rename.py > $L/apply.txt 2>&1 || { tail -3 $L/apply.txt; exit 1; }
tools/eu_port/rename.py --verify > $L/verify.txt 2>&1 || { tail -5 $L/verify.txt; echo "verify failed"; exit 1; }
echo "verify OK"
docs/port/sessions/p322/check.sh > $L/checks.txt 2>&1
grep -E " rc [1-9]" $L/checks.txt && { echo "checks red"; exit 1; }
grep -q "selftest: 152 ok, 0 failed" $L/checks.txt || { echo "selftest red"; exit 1; }
echo "checks OK"
(port/web/run.sh census && port/web/run.sh build) > $L/build.txt 2>&1 || { tail -5 $L/build.txt; echo "web build failed"; exit 1; }
echo "web build OK"
D=$L/hold; rm -rf $D
PADF='3386:1000:0:0,3401:0:0:0,4458:1000:0:0,4473:0:0:0,5600:20:0:0,5800:0:0:0' SHOTS="150000" \
  docs/port/sessions/p320/run.sh $D 200 > $D.out 2>&1 || true
grep -q "^\[p88\] scene frame 5789:" $D/chrome.log || { echo "browser hold test changed (see $D/chrome.log)"; exit 1; }
! grep -q "Aborted\|RuntimeError" $D/chrome.log || { echo "browser trap"; exit 1; }
echo "browser OK"
n=$(git diff --stat | tail -1)
git add -A conker/src_eu conker/include conker port tools && git add -u   # -u: difftest inputs under docs/ too
for c in "$@"; do git add docs/names/proposals/chunk$c.tsv; done
git commit -q -m "rename: chunks $* of docs/names/chunks.tsv named via tools/eu_port/names.tsv

$n. verify_all byte-identical, NM link, protocheck, implicit_scan, romabs, arity, selftest 152/152, census + web
build, browser hold-L skip unchanged (opening ends at 5789). Applied with tools/eu_port/apply_names.sh.

Co-Authored-By: Claude Opus 5.5 <noreply@anthropic.com>
Claude-Session: https://claude.ai/code/session_014MU6B4SSHUBUyCXqLySTxn"
git log -1 --oneline
~/conker/tools/eu_port/backup_push.sh
