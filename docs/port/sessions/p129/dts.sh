#!/bin/bash
# P129: tools/port/difftest.sh with the test copy difftest_stk.py (adds DIFFTEST_STKFILL); same env forwarding.
cd /Users/sorikairo/conker-wt/portb; eval "$(tools/eu_port/wt.sh env portb)"
sed -e 's#python3 ../tools/port/difftest/difftest.py#python3 ../port_work/p129/difftest_stk.py#' \
    -e 's#exec docker exec #exec docker exec -e DIFFTEST_STKFILL="${DIFFTEST_STKFILL:-}" -e DIFFTEST_UNICORN=/conker/port_work/pyuc201 #' \
    -e 's#"$(dirname "${BASH_SOURCE\[0\]}")/portguard.sh"#tools/port/portguard.sh#' tools/port/difftest.sh > port_work/p129/.dts_run.sh
exec bash port_work/p129/.dts_run.sh "$@"
