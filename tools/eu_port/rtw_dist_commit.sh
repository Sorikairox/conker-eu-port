#!/bin/bash
# P376: commit the retrowser build (port/build/rtw/dist, tools/eu_port/build_rtw.sh) to the local branch rtw-dist, the
# branch retrowser.app fetches (link: owner/repo@rtw-dist; the manifest sits at the branch root). The branch holds only
# retrowser.json + the files it lists (no history of the port). Plumbing only: no checkout, no stash, the working
# tree and the current branch are untouched. Never pushes (tools/eu_port/backup_push.sh pushes all branches).
# P379: it also refreshes the copy on the integration branch itself (port-web, and eu = port-web, the GitHub default
# branch): retrowser.json at the repo root (the manifest retrowser.app reads for the plain link owner/repo; its paths
# point into retrowser/) and retrowser/<the built files>, re-hashed and checked with --rom. Commit those two yourself
# (git add retrowser.json retrowser). --no-root skips that step. P384: the manifest's picture (cover.png, the
# cartridge picture of standard 1.2) goes along: cover.png at rtw-dist's root, retrowser/cover.png for the root manifest.
# P385: likewise the icon (icon.png, standard 1.2): icon.png at rtw-dist's root, retrowser/icon.png for the root manifest.
#   tools/eu_port/rtw_dist_commit.sh --rom ROM ["message"] [--no-root]
# The ROM leak scan (retrowser rtw-check --rom: every listed file is searched for 4 KiB runs of the ROM) must pass first.
set -euo pipefail
ROOT=$(cd "$(dirname "$0")/../.." && pwd)
RTW_REPO=${RETROWSER_DIR:-$HOME/Code/retrowser}
DIST=$ROOT/port/build/rtw/dist
[ "${1:-}" = --rom ] && [ -n "${2:-}" ] || { sed -n '2,15p' "$0"; exit 2; }
rom=$2; shift 2
refresh_root=1
if [ "${1:-}" = --no-root ]; then refresh_root=0; shift; fi
msg=${1:-"retrowser build of $(git -C "$ROOT" rev-parse --short HEAD)"}
[ "${2:-}" = --no-root ] && refresh_root=0
node "$RTW_REPO/tools/rtw-check.ts" "$DIST" --rom "$rom" || { echo "rtw_dist_commit: rtw-check failed, nothing committed"; exit 1; }
files=$(cd "$DIST" && node -e '
  const m = JSON.parse(require("fs").readFileSync("retrowser.json", "utf8"));
  console.log(["retrowser.json", m.files.wasm.path, m.files.js && m.files.js.path, ...(m.files.data || []).map((f) => f.path),
    m.picture && m.picture.path, m.icon && m.icon.path].filter(Boolean).join("\n"));')   # P384: + the cartridge picture; P385: + the icon (standard 1.2)
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
if [ -n "$parent" ] && [ "$(git -C "$ROOT" rev-parse "$parent^{tree}")" = "$tree" ]; then echo "rtw-dist already holds this build ($parent)"
else
  commit=$(printf '%s\n' "$msg" | git -C "$ROOT" commit-tree "$tree" ${parent:+-p "$parent"})
  git -C "$ROOT" update-ref refs/heads/rtw-dist "$commit" ${parent:+"$parent"}
  echo "rtw-dist -> $commit"
  git -C "$ROOT" ls-tree -l rtw-dist
fi
unset GIT_INDEX_FILE
[ "$refresh_root" = 1 ] || exit 0
# P379: the same files on this branch: retrowser/<file> + a root retrowser.json whose paths are moved into retrowser/
mkdir -p "$ROOT/retrowser"
rm -f "$ROOT"/retrowser/*
for f in $files; do [ "$f" = retrowser.json ] || cp "$DIST/$f" "$ROOT/retrowser/$f"; done
node -e '
  const fs = require("fs"), m = JSON.parse(fs.readFileSync(process.argv[1], "utf8"));
  const into = (e) => { e.path = "retrowser/" + e.path; };
  into(m.files.wasm); if (m.files.js) into(m.files.js); (m.files.data || []).forEach(into); if (m.picture) into(m.picture); if (m.icon) into(m.icon);
  fs.writeFileSync(process.argv[2], JSON.stringify(m, null, 2) + "\n");' "$DIST/retrowser.json" "$ROOT/retrowser.json"
node "$RTW_REPO/tools/rtw-hash.ts" "$ROOT"
node "$RTW_REPO/tools/rtw-check.ts" "$ROOT" --rom "$rom" || { echo "rtw_dist_commit: rtw-check of the root manifest failed"; exit 1; }
for f in $files; do [ "$f" = retrowser.json ] || cmp -s "$DIST/$f" "$ROOT/retrowser/$f" || { echo "rtw_dist_commit: retrowser/$f differs"; exit 1; }; done
echo "root manifest refreshed: commit with git add retrowser.json retrowser"
