#!/bin/sh
# Back up all work branches to the user's PRIVATE repo (origin = Sorikairox/conker-eu-port).
# Never pushes to upstream (mkst/conker). Uses gh's credentials without changing global git config.
set -e
cd "$(dirname "$0")/../.."
url=$(git remote get-url origin)
case "$url" in *Sorikairox/conker-eu-port*) ;; *) echo "origin is not the private backup repo: $url" >&2; exit 1;; esac
git -c credential.helper= -c credential.helper='!gh auth git-credential' \
  push --quiet origin eu eu-wt-a port port-b port-web port-web-b port-c port-d port-e port-f 2>&1 | tail -3
echo "backup push done: $(date '+%F %T')"
