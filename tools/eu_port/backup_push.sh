#!/bin/sh
# Back up the work to the user's PRIVATE repo (origin = Sorikairox/conker-eu-port).
# Never pushes to upstream (mkst/conker). Uses gh's credentials without changing global git config.
# port-web is the integration branch and must hold the latest of everything (user rule, 2026-10-26):
# eu is fast-forwarded to it, and any other local branch with commits port-web lacks is reported
# (except exact-byte-decomp-wip, the matching-build branch split off in P328).
set -e
cd "$(dirname "$0")/../.."
url=$(git remote get-url origin)
case "$url" in *Sorikairox/conker-eu-port*) ;; *) echo "origin is not the private backup repo: $url" >&2; exit 1;; esac
if git merge-base --is-ancestor eu port-web; then
  if [ "$(git rev-parse eu)" != "$(git rev-parse port-web)" ]; then
    if [ "$(git branch --show-current)" = eu ]; then git merge --ff-only --quiet port-web; else git branch -f eu port-web; fi
    echo "eu fast-forwarded to port-web"
  fi
else
  echo "WARNING: eu has commits port-web lacks: merge eu into port-web" >&2
fi
for b in $(git for-each-ref --format='%(refname:short)' refs/heads); do
  [ "$b" = master ] && continue
  # exact-byte-decomp-wip keeps the byte-matching decomp build (IDO/splat/asm) frozen at the P328 split; it
  # diverges from port-web on purpose, so it is pushed but never reported as unmerged.
  [ "$b" = exact-byte-decomp-wip ] && continue
  # rtw-dist holds only the retrowser.app build output (retrowser.json + built files, P376); it is pushed, never merged.
  [ "$b" = rtw-dist ] && continue
  n=$(git rev-list --count "port-web..$b")
  [ "$n" = 0 ] || echo "WARNING: $b has $n commits port-web lacks: merge it into port-web" >&2
done
git -c credential.helper= -c credential.helper='!gh auth git-credential' \
  push --quiet origin eu port-web exact-byte-decomp-wip $(git show-ref --verify --quiet refs/heads/rtw-dist && echo rtw-dist) 2>&1 | tail -3
echo "backup push done: $(date '+%F %T')"
