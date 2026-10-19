#!/bin/bash
# Parallel-agent worktrees: one git worktree + one dev container per agent.
#   wt.sh new <name>    worktree ~/conker-wt/<name> on branch eu-wt-<name> (from eu), copies submodules / ROM /
#                       permuter code / m2c venv, starts container conkerdev-<name> (conker-arm) mounting it at /conker
#   wt.sh env <name>    print the export lines every tool needs (eval "$(tools/eu_port/wt.sh env a)")
#   wt.sh merge <name>  merge eu-wt-<name> into eu in the MAIN checkout. Only when no agent is working in main!
#   wt.sh rm <name>     remove the container and the worktree (branch is kept)
# Env: WT_MAIN main checkout (default $HOME/conker), WT_DIR worktree parent (default $HOME/conker-wt).
set -euo pipefail
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
MAIN=${WT_MAIN:-$HOME/conker}; WTDIR=${WT_DIR:-$HOME/conker-wt}
cmd=${1:-}; name=${2:-}
[ -n "$cmd" ] && [ -n "$name" ] || { sed -n '2,8p' "$0"; exit 2; }
case $name in *[!a-zA-Z0-9_]*) echo "bad name: $name"; exit 2;; esac
wt=$WTDIR/$name; br=eu-wt-$name; ct=conkerdev-$name
case $cmd in
env)
  echo "export CONKER_ROOT=$wt CONKERDEV=$ct";;
new)
  [ -e "$wt" ] && { echo "$wt exists"; exit 1; }
  mkdir -p "$WTDIR"
  git -C "$MAIN" worktree add "$wt" -b "$br" eu
  # submodules (drop the .git pointer files: they would point into the main checkout's modules dir)
  for s in n64splat asm-processor asm-differ mips_to_c; do
    rm -rf "$wt/tools/$s"; cp -R "$MAIN/tools/$s" "$wt/tools/$s"; rm -f "$wt/tools/$s/.git"
  done
  cp "$MAIN/baserom.eu.z64" "$wt/"
  # permuter code only (no nm/ sweep/ repair/ s34/ data)
  mkdir -p "$wt/tools/decomp-permuter"
  rsync -a --exclude=/nm --exclude=/sweep --exclude=/repair --exclude=/s34 "$MAIN/tools/decomp-permuter/" "$wt/tools/decomp-permuter/"
  # m2c: generated function list + rodata cache (ctx/ is regenerated on demand); venv has absolute paths, so recreate it
  for x in all.txt rod; do [ -e "$MAIN/tools/eu_port/m2c/$x" ] && cp -R "$MAIN/tools/eu_port/m2c/$x" "$wt/tools/eu_port/m2c/"; done
  /usr/bin/python3 -m venv "$wt/tools/eu_port/m2c/venv"
  "$wt/tools/eu_port/m2c/venv/bin/pip" install -q 'pycparser<3' >/dev/null 2>&1 || echo "WARN: pycparser install failed"
  docker run -d --name "$ct" --platform linux/arm64 -v "$wt":/conker -w /conker conker-arm sleep infinity >/dev/null
  echo "worktree $wt  branch $br  container $ct"
  echo "next: eval \"\$($wt/tools/eu_port/wt.sh env $name)\"; cd \$CONKER_ROOT; tools/eu_port/verify_all.sh   (populates asm/ and build/)";;
merge)
  [ -d "$wt" ] || { echo "no worktree $wt"; exit 1; }
  git -C "$wt" diff --quiet && git -C "$wt" diff --cached --quiet || { echo "uncommitted changes in $wt"; exit 1; }
  [ "$(git -C "$MAIN" branch --show-current)" = eu ] || { echo "main checkout is not on eu"; exit 1; }
  git -C "$MAIN" merge --no-edit "$br";;
rm)
  docker rm -f "$ct" >/dev/null 2>&1 || true
  [ -d "$wt" ] && git -C "$MAIN" worktree remove --force "$wt"
  echo "removed $ct and $wt (branch $br kept; git branch -d $br after merging)";;
*) echo "unknown command $cmd"; exit 2;;
esac
