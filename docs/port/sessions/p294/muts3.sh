#!/bin/bash
S=docs/port/sessions/p294; cd ~/conker-wt/pe
$S/muts.sh $S/ray_gap_hmuts.txt $S/hmut_ray_gap.log 300 -- --only ray
$S/muts.sh $S/ledge_gap_hmuts.txt $S/hmut_ledge_gap.log 300 -- --only ac8c4
