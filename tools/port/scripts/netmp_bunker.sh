# P341 / P344: source to set PADF0..PADF3 for a Deathmatch in Bunker (level 0x34) through the real MULTI menus
# (tools/port/scripts/netmp_pads.py's title / MULTI route with "stick down, Start" for Deathmatch instead of Total War;
# pads 2..4 join with Start on the join page (main page 4, faded in 5125 .. 5613; pad k at 5300 + 20 * (k - 2)), P1's A
# at 5600 / 5900 starts the game, gameplay from retrace 5947). Pads that are not in the session are ignored.
# Without EXTRA0..EXTRA3 the players stand still; EXTRAk (sorted, >= 6000, ?padf syntax F:BTN:X:Y) is appended to pad
# k + 1. NET_BUNKER_DEMO=1 sets EXTRA1 to the weapon demo: player 2 runs onto pickup 20 (weapon 0x14, taken ~6333),
# draws it with B at 6500 and fires with Z every 60 retraces from 6600. P344: NET_BUNKER_PLAY=SECS: every pad without
# an EXTRA moves / jumps / attacks for SECS seconds from retrace 6100 (netmp_pads.py's random play).
# Use: PADS=tools/port/scripts/netmp_bunker.sh tools/port/scripts/netpair.sh NAME SECS   (or source it before run scripts)
if [ -n "${NET_BUNKER_PLAY:-}" ]; then
  eval "$(python3 tools/port/scripts/netmp_pads.py 6100 "$NET_BUNKER_PLAY" | sed 's/^PADF/PLAYF/')"
  for k in 0 1 2 3; do
    v=EXTRA$k; p=PLAYF$k
    [ -z "${!v:-}" ] && eval "EXTRA$k=\$(echo \"\$$p\" | tr ',' '\n' | awk -F: '\$1 >= 6000' | sort -t: -k1,1n -s | paste -sd, -)"
  done
fi
eval "$(python3 tools/port/scripts/netmp_pads.py 7000 0)"
if [ -n "${NET_BUNKER_DEMO:-}" ] && [ -z "${EXTRA1:-}" ]; then
  EXTRA1="6100:0:0:80"
  for f in 6300 6330 6360 6390; do EXTRA1="$EXTRA1,$f:8000:0:80,$((f + 8)):0:0:80"; done
  EXTRA1="$EXTRA1,6420:0:0:0,6500:4000:0:0,6508:0:0:0"
  for f in 6600 6660 6720 6780 6840 6900 6960 7020; do EXTRA1="$EXTRA1,$f:2000:0:0,$((f + 12)):0:0:0"; done
fi
PADF0=$(echo "$PADF0" | sed 's/5000:4000:0:0,5008:0:0:0,5120:0:80:0,5128:0:0:0,5300:1000:0:0,5315:0:0:0/4900:0:0:-80,4908:0:0:0,5100:1000:0:0,5115:0:0:0/')
PADF0=$(echo "$PADF0" | tr ',' '\n' | awk -F: '$1 < 6000' | paste -sd, -)
PADF1=$(echo "$PADF1" | tr ',' '\n' | awk -F: '$1 < 6000' | paste -sd, - | sed 's/^5751:1000:0:0,5766:0:0:0/5300:1000:0:0,5315:0:0:0/')
PADF2=$(echo "$PADF2" | tr ',' '\n' | awk -F: '$1 < 6000' | paste -sd, - | sed 's/^5752:1000:0:0,5767:0:0:0/5320:1000:0:0,5335:0:0:0/')
PADF3=$(echo "$PADF3" | tr ',' '\n' | awk -F: '$1 < 6000' | paste -sd, - | sed 's/^5753:1000:0:0,5768:0:0:0/5340:1000:0:0,5355:0:0:0/')
[ -n "${EXTRA0:-}" ] && PADF0="$PADF0,$EXTRA0"
[ -n "${EXTRA1:-}" ] && PADF1="$PADF1,$EXTRA1"
[ -n "${EXTRA2:-}" ] && PADF2="$PADF2,$EXTRA2"
[ -n "${EXTRA3:-}" ] && PADF3="$PADF3,$EXTRA3"
export PADF0 PADF1 PADF2 PADF3
