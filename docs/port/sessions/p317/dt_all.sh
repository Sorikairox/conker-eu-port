#!/bin/bash
# P317: random difftest (dt.sh) of the functions changed by the table-signature and volatile-zero fixes, plus reverify of
# the ones with a registry row.
D=~/conker-wt/portb/docs/port/sessions/p317
for f in func_15141A7C func_150BD498 func_151A79EC func_150B3B8C func_15133F44 func_15133FC0 func_150C06DC func_150C0B48 func_15019F20 func_1510E004 func_15051558; do
  echo "$f: $($D/dt.sh $f DIFFTEST_ROMDATA=1 | tr '\n' ' ')"
done
cd ~/conker-wt/portb && eval "$(tools/eu_port/wt.sh env portb)" && tools/port/reverify.sh func_1512A1A0 func_15133E04 func_1513334C
