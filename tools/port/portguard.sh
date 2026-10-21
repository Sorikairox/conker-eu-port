# Wrong-checkout guard for tools/port shell scripts (P7). Source it first:
#   . "$(dirname "${BASH_SOURCE[0]}")/portguard.sh"        (difftest/: .../../portguard.sh)
# Refuses (exit 3) unless CONKER_ROOT is set explicitly, the checkout holding this file is CONKER_ROOT,
# and the git toplevel of the cwd (if any) is CONKER_ROOT. No-op inside a build container.
if [ ! -f /.dockerenv ]; then
  _pg_msg='(run: eval "$(tools/eu_port/wt.sh env port)" in the same shell)'
  if [ -z "${CONKER_ROOT:-}" ]; then echo "refusing: CONKER_ROOT is not set $_pg_msg" >&2; exit 3; fi
  _pg_root=$(cd "$CONKER_ROOT" 2>/dev/null && pwd -P) || { echo "refusing: CONKER_ROOT $CONKER_ROOT does not exist" >&2; exit 3; }
  _pg_here=$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd -P)
  if [ "$_pg_here" != "$_pg_root" ]; then echo "refusing: script checkout $_pg_here != CONKER_ROOT $_pg_root $_pg_msg" >&2; exit 3; fi
  _pg_top=$(git rev-parse --show-toplevel 2>/dev/null)
  if [ -n "$_pg_top" ] && [ "$(cd "$_pg_top" && pwd -P)" != "$_pg_root" ]; then echo "refusing: cwd repo $_pg_top != CONKER_ROOT $_pg_root $_pg_msg" >&2; exit 3; fi
  unset _pg_msg _pg_root _pg_here _pg_top
fi
