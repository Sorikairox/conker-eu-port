#!/bin/bash
# Merge a worktree branch into eu from the main checkout, resolve the usual append-only
# conflicts by union, run the full verify, set HANDOFF's "Current state" line from it, and
# commit only if everything matches. Run only when no agent is active in the main checkout.
#   merge_wt.sh [branch=eu-wt-a]        (repo root)
#   merge_wt.sh --continue              finish an already-started, conflicted merge
set -uo pipefail
cd "$(dirname "$0")/../.."
B=${1:-eu-wt-a}
if [ "$B" = --continue ]; then
  B=$(sed -n "s/^Merge branch '\([^']*\)'.*/\1/p" .git/MERGE_MSG 2>/dev/null | head -1); B=${B:-eu-wt-a}
else
  # --no-commit: even a clean merge must not land before verify_all.sh passes
  git merge --no-commit --no-ff "$B" >/dev/null 2>&1
fi
conf=$(git diff --name-only --diff-filter=U)
if [ -n "$conf" ]; then
  bad=$(echo "$conf" | grep -vE '^(HANDOFF\.md|docs/IDO_SHAPES\.md|docs/sessions/.*|tools/eu_port/repair_log\.tsv|conker/undefined_syms\.eu\.txt|conker/symbol_addrs\.eu\.txt)$')
  if [ -n "$bad" ]; then echo "STOP: non-append conflicts need a human:"; echo "$bad"; exit 1; fi
  echo "$conf" | while read -r f; do python3 tools/eu_port/merge_union.py "$f"; done
  echo "$conf" | while read -r f; do git add "$f"; done
fi
out=$(tools/eu_port/verify_all.sh); rc=$?
echo "$out"
[ $rc -eq 0 ] || { echo "STOP: merged tree does not verify; merge left uncommitted"; exit 1; }
tot=$(echo "$out" | awk '$1=="total"{print $3, $4, $6, $7}')   # 3239/ 5913 (54.8%) bytes 358236/2253856 (15.9%)
python3 - "$out" <<'EOF'
import re, sys
out = sys.argv[1]
t = re.search(r"total\s+funcs\s+(\d+)/\s*(\d+)\s+\(([\d.]+)%\)\s+bytes\s+(\d+)/\s*(\d+)\s+\(([\d.]+)%\)", out)
seg = {m.group(1): m for m in re.finditer(r"(init|game|debugger)\s+funcs\s+(\d+)/\s*(\d+).*?bytes.*?\(([\d.]+)%\)", out)}
line = (f"- **{t.group(1)} / {t.group(2)} functions in C ({t.group(3)}%)**, code bytes "
        f"{int(t.group(4)):,} / {int(t.group(5)):,} ({t.group(6)}%) (merged state, from `verify_all.sh`). "
        + ", ".join(f"{k} {seg[k].group(2)}/{seg[k].group(3)} ({seg[k].group(4)}% of bytes)" for k in ("init", "game", "debugger") if k in seg) + ".")
L = open("HANDOFF.md").read().split("\n")
out_lines, done = [], False
for l in L:
    if re.match(r"- \*\*\d+ / 5913 functions in C", l):
        if not done:
            out_lines.append(line); done = True
        continue
    out_lines.append(l)
open("HANDOFF.md", "w").write("\n".join(out_lines))
EOF
git add HANDOFF.md
git commit -q -m "Merge $B (verified: $(echo "$out" | awk '$1=="total"{print $3$4}'))

Append-only conflicts resolved by union (merge_union.py). verify_all.sh: code build OK,
check_files OK, full ROM OK.

Co-Authored-By: Claude Opus 5.5 <noreply@anthropic.com>" && git log --oneline -1
