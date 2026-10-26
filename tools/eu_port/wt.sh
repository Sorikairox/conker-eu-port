#!/bin/bash
# Parallel-agent worktrees: one git worktree + one dev container per agent.
#   wt.sh new <name>    worktree ~/conker-wt/<name> on branch eu-wt-<name> (from eu), copies the ROM, starts
#                       container conkerdev-<name> (conker-arm image, Dockerfile.arm: IDO for difftest) at /conker
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
  cp "$MAIN/baserom.eu.z64" "$wt/"
  docker run -d --name "$ct" --platform linux/arm64 -v "$wt":/conker -w /conker conker-arm sleep infinity >/dev/null
  echo "worktree $wt  branch $br  container $ct"
  echo "next: eval \"\$($wt/tools/eu_port/wt.sh env $name)\"; cd \$CONKER_ROOT; tools/eu_port/check.sh";;
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
