#!/bin/bash
# P376: commit the retrowser build (port/build/rtw/dist, tools/eu_port/build_rtw.sh) to the local branch rtw-dist, the
# branch retrowser.app fetches (link: owner/repo@rtw-dist; the manifest sits at the branch root). The branch holds only
# retrowser.json + the files it lists (no history of the port). Plumbing only: no checkout, no stash, the working
# tree and the current branch are untouched. Never pushes (tools/eu_port/backup_push.sh pushes all branches).
#   tools/eu_port/rtw_dist_commit.sh --rom ROM ["message"]
# The ROM leak scan (retrowser rtw-check --rom: every listed file is searched for 4 KiB runs of the ROM) must pass first.
set -euo pipefail
ROOT=$(cd "$(dirname "$0")/../.." && pwd)
RTW_REPO=${RETROWSER_DIR:-$HOME/Code/retrowser}
DIST=$ROOT/port/build/rtw/dist
[ "${1:-}" = --rom ] && [ -n "${2:-}" ] || { sed -n '2,8p' "$0"; exit 2; }
rom=$2; msg=${3:-"retrowser build of $(git -C "$ROOT" rev-parse --short HEAD)"}
node "$RTW_REPO/tools/rtw-check.ts" "$DIST" --rom "$rom" || { echo "rtw_dist_commit: rtw-check failed, nothing committed"; exit 1; }
files=$(cd "$DIST" && node -e '
  const m = JSON.parse(require("fs").readFileSync("retrowser.json", "utf8"));
  console.log(["retrowser.json", m.files.wasm.path, m.files.js && m.files.js.path, ...(m.files.data || []).map((f) => f.path)].filter(Boolean).join("\n"));')
export GIT_INDEX_FILE
idx_dir=$(mktemp -d "${TMPDIR:-/tmp}/rtw-dist-index.XXXXXX")
GIT_INDEX_FILE=$idx_dir/index   # a separate index: the worktree's own index is never touched
trap 'rm -rf "$idx_dir"' EXIT
git -C "$ROOT" read-tree --empty
for f in $files; do
  blob=$(git -C "$ROOT" hash-object -w "$DIST/$f")
  git -C "$ROOT" update-index --add --cacheinfo 100644,"$blob","$f"
done
tree=$(git -C "$ROOT" write-tree)
parent=$(git -C "$ROOT" rev-parse -q --verify refs/heads/rtw-dist || true)
if [ -n "$parent" ] && [ "$(git -C "$ROOT" rev-parse "$parent^{tree}")" = "$tree" ]; then echo "rtw-dist already holds this build ($parent)"; exit 0; fi
commit=$(printf '%s\n' "$msg" | git -C "$ROOT" commit-tree "$tree" ${parent:+-p "$parent"})
git -C "$ROOT" update-ref refs/heads/rtw-dist "$commit" ${parent:+"$parent"}
echo "rtw-dist -> $commit"
git -C "$ROOT" ls-tree -l rtw-dist
