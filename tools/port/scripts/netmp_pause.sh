# P381: source after netmp_pads.py (netpair.sh PADS=) to append pauses to player 1's Total War pads (PLAY_SECS=20, the
# default: play ends at retrace 8000): Start at 8100, 8401, 8702, 9003, 9304, 9605, Start again 150 retraces later. Each
# pause frame is a GPU read-back of the framebuffer on screen (gfx_f3dex2.c fbc_check_timg, P161), so the write-back
# ranges of both framebuffers get registered: 803D6300 (+1EA78) at 8117, then 803B7600 at 8417, which share page
# 803D6000. Regression test of the P381 state-hash fix (pc_nethash.c net_gpu_lowest_overlap): with the own view (the
# room default) or other canvas sizes the peers' pause pictures differ, and the old code reported a false DESYNC at 8420.
#   PLAYERS=4 PADS=tools/port/scripts/netmp_pause.sh VIEWPORTS=1920x1080,800x600,1280x720,1024x768 HOSTQ='&opt=fullres:1' \
#     tools/port/scripts/netpair.sh NAME 205
NETMP_PAUSES=""
for f in 8100 8401 8702 9003 9304 9605; do NETMP_PAUSES="$NETMP_PAUSES,$f:1000:0:0,$((f + 10)):0:0:0,$((f + 150)):1000:0:0,$((f + 160)):0:0:0"; done
PADF0="$PADF0$NETMP_PAUSES"; unset NETMP_PAUSES
