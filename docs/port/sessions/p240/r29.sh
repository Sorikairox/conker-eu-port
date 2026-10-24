#!/bin/bash
# P236: chR3 level route (new game -> level 0x29 scene 5) in Chrome.  r29.sh DIR SECS [EXTRA_QUERY]
H=/Users/sorikairo/conker-wt/web/docs/port/sessions/p240
source $H/chR3.env
$H/shots.sh "$1" "$Q${3:-}" "${2:-730}"
